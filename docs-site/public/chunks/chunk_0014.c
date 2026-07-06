// ==== 8008e7a0  THPSimpleAudioStop ====

void THPSimpleAudioStop(void)

{
  DAT_803ca851 = 0;
  return;
}



// ==== 8008e7b4  zz_008e7b4_ ====

int zz_008e7b4_(int param_1)

{
  int iVar1;
  int unaff_r30;
  
  if (DAT_803ca851 == '\x01') {
    unaff_r30 = 1;
    iVar1 = zz_008dbcc_();
    if (iVar1 == 0) {
      unaff_r30 = zz_008e0d0_(param_1);
      DAT_803ca851 = '\0';
    }
  }
  else if ((DAT_803ca851 < '\x01') && (-1 < DAT_803ca851)) {
    iVar1 = zz_008e108_((char)param_1);
    if (iVar1 == 0) {
      DAT_803ca851 = DAT_803ca851 + '\x01';
      zz_008e378_(1);
      zz_008e378_(3);
      zz_008e378_(0xf);
      zz_008e378_(2);
    }
    unaff_r30 = 1;
  }
  return unaff_r30;
}



// ==== 8008e87c  zz_008e87c_ ====

int zz_008e87c_(int param_1)

{
  int iVar1;
  int unaff_r30;
  
  if (DAT_803ca851 == '\x01') {
    unaff_r30 = 1;
    iVar1 = zz_008dbcc_();
    if (iVar1 == 0) {
      unaff_r30 = zz_008e0d0_(param_1);
      DAT_803ca851 = '\0';
    }
  }
  else if ((DAT_803ca851 < '\x01') && (-1 < DAT_803ca851)) {
    iVar1 = zz_008e108_((char)param_1);
    if (iVar1 == 0) {
      DAT_803ca851 = DAT_803ca851 + '\x01';
      zz_008e378_(1);
      zz_008e378_(3);
      zz_008e378_(0x10);
      zz_008e378_(2);
    }
    unaff_r30 = 1;
  }
  return unaff_r30;
}



// ==== 8008e944  zz_008e944_ ====

int zz_008e944_(int param_1)

{
  int iVar1;
  int unaff_r30;
  
  if (DAT_803ca851 == '\x01') {
    unaff_r30 = 1;
    iVar1 = zz_008dbcc_();
    if (iVar1 == 0) {
      unaff_r30 = zz_008e0d0_(param_1);
      DAT_803ca851 = '\0';
    }
  }
  else if ((DAT_803ca851 < '\x01') && (-1 < DAT_803ca851)) {
    iVar1 = zz_008e108_((char)param_1);
    if (iVar1 == 0) {
      DAT_803ca851 = DAT_803ca851 + '\x01';
      zz_008e12c_(s_GG4E_GOTCHA_FORCE_USA_802b0d5c);
      zz_008e378_(1);
      zz_008e378_(3);
      zz_008e378_(7);
      zz_008e378_(8);
      zz_008e378_(2);
    }
    unaff_r30 = 1;
  }
  return unaff_r30;
}



// ==== 8008ea20  zz_008ea20_ ====

int zz_008ea20_(int param_1)

{
  int iVar1;
  int unaff_r30;
  
  if (DAT_803ca851 == '\x01') {
    unaff_r30 = 1;
    iVar1 = zz_008dbcc_();
    if (iVar1 == 0) {
      unaff_r30 = zz_008e0d0_(param_1);
      DAT_803ca851 = '\0';
    }
  }
  else if ((DAT_803ca851 < '\x01') && (-1 < DAT_803ca851)) {
    iVar1 = zz_008e108_((char)param_1);
    if (iVar1 == 0) {
      DAT_803ca851 = DAT_803ca851 + '\x01';
      zz_008e378_(1);
      zz_008e378_(3);
      zz_008e378_(0x11);
      zz_008e378_(2);
    }
    unaff_r30 = 1;
  }
  return unaff_r30;
}



// ==== 8008eae8  zz_008eae8_ ====

int zz_008eae8_(int param_1,undefined4 param_2)

{
  char *pcVar1;
  char *pcVar2;
  void *pvVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined8 uVar11;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  zz_008c104_(FUN_800906d4);
  iVar8 = 1;
  if (DAT_803ca851 == '\x02') {
    iVar4 = zz_008dbcc_();
    if (iVar4 == 0) {
      iVar4 = zz_008e0d0_(param_1);
      if (iVar4 == 0) {
        iVar4 = zz_008e1c8_();
        uVar5 = zz_008df00_(iVar4,0x3f);
        if ((uVar5 & 0xffff) == 0) {
          iVar10 = 0;
          zz_0091608_((void *)(iVar4 + 0x13470),600,(uint)*(byte *)(iVar4 + 0x206f),
                      (uint)*(byte *)(iVar4 + 0x2070),(void *)(iVar4 + 0x206f),2);
          if (*(int *)(iVar4 + 0x134bc) == *(int *)((int)DAT_803ca85c + 0x4c) &&
              *(int *)(iVar4 + 0x134b8) == *(int *)((int)DAT_803ca85c + 0x48)) {
            pcVar7 = (char *)((int)DAT_803ca85c + 0x1c);
            pcVar6 = (char *)(iVar4 + 0x1348c);
            iVar4 = 8;
            do {
              if (*pcVar6 != *pcVar7) {
                iVar10 = 1;
                break;
              }
              if (pcVar6[1] != pcVar7[1]) {
                iVar10 = 1;
                break;
              }
              if (pcVar6[2] != pcVar7[2]) {
                iVar10 = 1;
                break;
              }
              if (pcVar6[3] != pcVar7[3]) {
                iVar10 = 1;
                break;
              }
              pcVar1 = pcVar6 + 4;
              pcVar6 = pcVar6 + 5;
              pcVar2 = pcVar7 + 4;
              pcVar7 = pcVar7 + 5;
              if (*pcVar1 != *pcVar2) {
                iVar10 = 1;
                break;
              }
              iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
          }
          else {
            iVar10 = 1;
          }
          if (iVar10 == 0) {
            DAT_803ca851 = DAT_803ca851 + '\x01';
          }
          else {
            DAT_803ca851 = '\0';
            zz_008e534_(iVar10);
            iVar8 = 0;
          }
        }
        else {
          iVar8 = 0;
          DAT_803ca851 = '\0';
        }
      }
      else {
        iVar8 = zz_008e0d0_(param_1);
        DAT_803ca851 = '\0';
      }
    }
  }
  else if (DAT_803ca851 < '\x02') {
    if (DAT_803ca851 == '\0') {
      iVar4 = zz_008e108_((char)param_1);
      if (iVar4 == 0) {
        DAT_803ca851 = DAT_803ca851 + '\x01';
        zz_008e258_(param_2);
        zz_008e534_(0);
        zz_008e12c_(s_GG4E_GOTCHA_FORCE_USA_802b0d5c);
        zz_008e378_(1);
        zz_008e378_(3);
        zz_008e378_(0x11);
        zz_008e378_(7);
      }
    }
    else if ((-1 < DAT_803ca851) && (iVar4 = zz_008dbcc_(), iVar4 == 0)) {
      DAT_803ca851 = DAT_803ca851 + '\x01';
      iVar4 = zz_008e0d0_(param_1);
      if (iVar4 == 0) {
        zz_008e220_(0);
        zz_008e1e8_(0x14000);
        zz_008e2b0_(0x14000);
        uVar5 = zz_008e184_(0x87000);
        gnt4_DCInvalidateRange_bl(uVar5,0x14000);
        zz_008e378_(9);
        zz_008e378_(8);
        zz_008e378_(2);
      }
      else if (iVar4 == -4) {
        if (*(int *)((int)DAT_803ca85c + 0x44) == 0) {
          uVar5 = zz_008e290_();
          zz_008e258_(uVar5 | 0x2f);
          DAT_803ca851 = '\x03';
          iVar4 = zz_008e184_(0x87000);
          *(undefined1 *)(iVar4 + 0x2042) = 0;
          *(undefined1 *)(iVar4 + 0x2043) = 0;
          *(undefined1 *)(iVar4 + 0x2044) = 0;
          *(undefined1 *)(iVar4 + 0x2045) = 0;
          *(undefined1 *)(iVar4 + 0x2046) = 0;
        }
        else {
          DAT_803ca851 = '\0';
          zz_008e534_(0xffffffff);
          iVar8 = 0;
        }
      }
      else {
        DAT_803ca851 = '\0';
        iVar8 = iVar4;
      }
    }
  }
  else if (DAT_803ca851 == '\x04') {
    iVar4 = zz_008dbcc_();
    if (iVar4 == 0) {
      iVar8 = zz_008e0d0_(param_1);
      DAT_803ca851 = '\0';
    }
  }
  else if (DAT_803ca851 < '\x04') {
    DAT_803ca851 = DAT_803ca851 + '\x01';
    zz_008e12c_(s_GG4E_GOTCHA_FORCE_USA_802b0d5c);
    uVar5 = zz_008e184_(0x87000);
    zz_00f19f8_(uVar5,0xa34000,0x2040,1);
    zz_008e220_(0);
    zz_008e1e8_(0x14000);
    zz_008e2b0_(0x14000);
    zz_008e2e8_(0xc);
    uVar11 = gnt4_OSGetTime_bl();
    gnt4_OSTicksToCalendarTime_bl((uint)((ulonglong)uVar11 >> 0x20),(uint)uVar11,&local_38);
    if (0x3b < local_38) {
      local_38 = 0x3b;
    }
    sprintf((char *)(uVar5 + 0x20),s__02d__02d__04d__02d__02d__02d_802b0d74,local_28 + 1,local_2c,
            local_24,local_30,local_34,local_38);
    pvVar3 = DAT_803ca85c;
    *(int *)((int)DAT_803ca85c + 0x1c) = local_38;
    *(undefined4 *)((int)pvVar3 + 0x20) = local_34;
    *(undefined4 *)((int)pvVar3 + 0x24) = local_30;
    *(undefined4 *)((int)pvVar3 + 0x28) = local_2c;
    *(int *)((int)pvVar3 + 0x2c) = local_28;
    *(undefined4 *)((int)pvVar3 + 0x30) = local_24;
    *(undefined4 *)((int)pvVar3 + 0x34) = local_20;
    *(undefined4 *)((int)pvVar3 + 0x38) = local_1c;
    *(undefined4 *)((int)pvVar3 + 0x3c) = local_18;
    *(undefined4 *)((int)pvVar3 + 0x40) = local_14;
    uVar11 = zz_008e4c8_((int)DAT_803ca852);
    *(undefined8 *)((int)DAT_803ca85c + 0x48) = uVar11;
    zz_008e704_(uVar5,0,0x2040,1);
    uVar9 = *(uint *)(&DAT_803ca8c0 + DAT_803ca852 * 0x98);
    if ((uVar9 & 2) != 0) {
      *(undefined1 *)(uVar5 + 0x2042) = 1;
      gnt4_memcpy((void *)(uVar5 + 0x2084),&DAT_803c4ea0,0x40);
      zz_008e704_(uVar5 + 0x2084,0,0x40,1);
    }
    if ((uVar9 & 4) != 0) {
      *(undefined1 *)(uVar5 + 0x2043) = 1;
      gnt4_memcpy((void *)(uVar5 + 0x20c8),DAT_803ca858,0xabe4);
      zz_00916c4_((void *)(uVar5 + 0x20c8),0xabe4,(byte *)(uVar5 + 0x2047),0);
      zz_008e704_(uVar5 + 0x20c8,0,0xabe4,1);
    }
    if ((uVar9 & 8) != 0) {
      *(undefined1 *)(uVar5 + 0x2044) = 1;
      gnt4_memcpy((void *)(uVar5 + 0xccb0),DAT_803ca854,0x2190);
      zz_00916c4_((void *)(uVar5 + 0xccb0),0x2190,(byte *)(uVar5 + 0x205b),1);
      zz_008e704_(uVar5 + 0xccb0,0,0x2190,1);
    }
    if ((uVar9 & 0x10) != 0) {
      *(undefined1 *)(uVar5 + 0x2045) = 1;
      gnt4_memcpy((void *)(uVar5 + 0xee44),DAT_80436354,0x4628);
      zz_008e704_(uVar5 + 0xee44,0,0x4628,1);
    }
    *(undefined1 *)(uVar5 + 0x2046) = 1;
    gnt4_memcpy((void *)(uVar5 + 0x13470),DAT_803ca85c,600);
    *(int *)(uVar5 + 0x134b4) = *(int *)(uVar5 + 0x134b4) + 1;
    zz_00916c4_((void *)(uVar5 + 0x13470),600,(byte *)(uVar5 + 0x206f),2);
    zz_008e704_(uVar5 + 0x13470,0,600,1);
    gnt4_DCFlushRange_bl(uVar5,0x14000);
    zz_008e378_(1);
    zz_008e378_(3);
    zz_008e378_(4);
    zz_008e378_(7);
    zz_008e378_(0xe);
    zz_008e378_(10);
    zz_008e378_(0xb);
    zz_008e378_(0xc);
    zz_008e378_(8);
    zz_008e378_(2);
  }
  return iVar8;
}



// ==== 8008f1b8  zz_008f1b8_ ====

int zz_008f1b8_(int param_1,uint param_2)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  bool bVar12;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  char cVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  
  zz_008c104_(FUN_800906d4);
  iVar16 = 1;
  if (DAT_803ca851 == '\x01') {
    iVar5 = zz_008dbcc_();
    if (iVar5 == 0) {
      DAT_803ca851 = DAT_803ca851 + '\x01';
      iVar16 = zz_008e0d0_(param_1);
      if (iVar16 == 0) {
        iVar16 = 1;
        zz_008e220_(0);
        zz_008e1e8_(0x14000);
        zz_008e2b0_(0x14000);
        uVar6 = zz_008e184_(0x87000);
        gnt4_DCInvalidateRange_bl(uVar6,0x14000);
        zz_008e378_(9);
        zz_008e378_(0xd);
        zz_008e378_(8);
        zz_008e378_(2);
        iVar5 = zz_008e1c8_();
        if ((param_2 & 2) != 0) {
          *(undefined1 *)(iVar5 + 0x20c4) = 0xff;
          *(undefined1 *)(iVar5 + 0x20c5) = 0xff;
        }
        if ((param_2 & 4) != 0) {
          *(undefined1 *)(iVar5 + 0xccac) = 0xff;
          *(undefined1 *)(iVar5 + 0xccad) = 0xff;
        }
        if ((param_2 & 8) != 0) {
          *(undefined1 *)(iVar5 + 0xee40) = 0xff;
          *(undefined1 *)(iVar5 + 0xee41) = 0xff;
        }
        if ((param_2 & 0x10) != 0) {
          *(undefined1 *)(iVar5 + 0x1346c) = 0xff;
          *(undefined1 *)(iVar5 + 0x1346d) = 0xff;
        }
        *(undefined1 *)(iVar5 + 0x136c8) = 0xff;
        *(undefined1 *)(iVar5 + 0x136c9) = 0xff;
      }
      else if (iVar16 < 0) {
        DAT_803ca851 = '\0';
      }
    }
  }
  else if (DAT_803ca851 < '\x01') {
    if ((-1 < DAT_803ca851) && (iVar5 = zz_008e108_((char)param_1), iVar5 == 0)) {
      DAT_803ca851 = DAT_803ca851 + '\x01';
      zz_008e258_(param_2);
      zz_008e12c_(s_GG4E_GOTCHA_FORCE_USA_802b0d5c);
      zz_008e378_(1);
      zz_008e378_(3);
      zz_008e378_(7);
      zz_008e378_(0xb);
    }
  }
  else if ((DAT_803ca851 < '\x03') && (iVar5 = zz_008dbcc_(), iVar5 == 0)) {
    iVar16 = zz_008e0d0_(param_1);
    if (iVar16 == 0) {
      iVar5 = zz_008e1c8_();
      uVar15 = *(uint *)(&DAT_803ca8c0 + DAT_803ca852 * 0x98);
      zz_008e5b4_(1,*(undefined1 *)(iVar5 + 0x2042));
      zz_008e5b4_(2,*(undefined1 *)(iVar5 + 0x2043));
      zz_008e5b4_(3,*(undefined1 *)(iVar5 + 0x2044));
      zz_008e5b4_(4,*(undefined1 *)(iVar5 + 0x2045));
      zz_008e5b4_(5,*(undefined1 *)(iVar5 + 0x2046));
      bVar1 = true;
      uVar14 = 0;
      uVar6 = zz_008e704_(iVar5,0,0x2040,0);
      zz_008e4e4_(0,(short)uVar6);
      if (*(char *)(iVar5 + 0x2042) == '\0') {
        uVar7 = 0;
        if ((uVar15 & 2) != 0) {
          bVar1 = false;
        }
      }
      else {
        uVar7 = zz_008e704_(iVar5 + 0x2084,0,0x40,0);
        zz_008e4e4_(1,(short)uVar7);
      }
      if (*(char *)(iVar5 + 0x2043) == '\0') {
        uVar8 = 0;
        if ((uVar15 & 4) != 0) {
          bVar1 = false;
        }
      }
      else {
        uVar8 = zz_008e704_(iVar5 + 0x20c8,0,0xabe4,0);
        zz_008e4e4_(2,(short)uVar8);
        bVar12 = zz_0091608_((void *)(iVar5 + 0x20c8),0xabe4,(uint)*(byte *)(iVar5 + 0x2047),
                             (uint)*(byte *)(iVar5 + 0x2048),(void *)(iVar5 + 0x2047),0);
        uVar14 = (uint)bVar12;
      }
      if (*(char *)(iVar5 + 0x2044) == '\0') {
        uVar9 = 0;
        if ((uVar15 & 8) != 0) {
          bVar1 = false;
        }
      }
      else {
        uVar9 = zz_008e704_(iVar5 + 0xccb0,0,0x2190,0);
        zz_008e4e4_(3,(short)uVar9);
        bVar12 = zz_0091608_((void *)(iVar5 + 0xccb0),0x2190,(uint)*(byte *)(iVar5 + 0x205b),
                             (uint)*(byte *)(iVar5 + 0x205c),(void *)(iVar5 + 0x205b),1);
        uVar14 = uVar14 + bVar12;
      }
      if (*(char *)(iVar5 + 0x2045) == '\0') {
        uVar10 = 0;
        if ((uVar15 & 0x10) != 0) {
          bVar1 = false;
        }
      }
      else {
        uVar10 = zz_008e704_(iVar5 + 0xee44,0,0x4628,0);
        zz_008e4e4_(4,(short)uVar10);
      }
      if (*(char *)(iVar5 + 0x2046) == '\0') {
        uVar11 = 0;
        bVar1 = false;
      }
      else {
        uVar11 = zz_008e704_(iVar5 + 0x13470,0,600,0);
        zz_008e4e4_(5,(short)uVar11);
        bVar12 = zz_0091608_((void *)(iVar5 + 0x13470),600,(uint)*(byte *)(iVar5 + 0x206f),
                             (uint)*(byte *)(iVar5 + 0x2070),(void *)(iVar5 + 0x206f),2);
        uVar14 = uVar14 + bVar12;
      }
      cVar13 = zz_008e308_();
      iVar4 = DAT_803ca9d0;
      iVar3 = DAT_803ca9c8;
      zz_008e574_(uVar14);
      uVar2 = DAT_803c4ecb;
      if ((((((((uVar6 & 0xffff) == 0) && ((uVar7 & 0xffff) == 0)) && ((uVar8 & 0xffff) == 0)) &&
            (((uVar9 & 0xffff) == 0 && ((uVar10 & 0xffff) == 0)))) &&
           (((uVar11 & 0xffff) == 0 && ((cVar13 == '\f' && (bVar1)))))) && (uVar14 == 0)) &&
         ((iVar4 != -1 && (iVar3 != -1)))) {
        if (((uVar15 & 2) != 0) && (*(char *)(iVar5 + 0x2042) != '\0')) {
          gnt4_memcpy(&DAT_803c4ea0,(void *)(iVar5 + 0x2084),0x40);
        }
        DAT_803c4ecb = uVar2;
        if (((uVar15 & 4) != 0) && (*(char *)(iVar5 + 0x2043) != '\0')) {
          gnt4_memcpy(DAT_803ca858,(void *)(iVar5 + 0x20c8),0xabe4);
        }
        if (((uVar15 & 8) != 0) && (*(char *)(iVar5 + 0x2044) != '\0')) {
          gnt4_memcpy(DAT_803ca854,(void *)(iVar5 + 0xccb0),0x2190);
        }
        if (((uVar15 & 0x10) != 0) && (*(char *)(iVar5 + 0x2045) != '\0')) {
          gnt4_memcpy(DAT_80436354,(void *)(iVar5 + 0xee44),0x4628);
        }
        if (*(char *)(iVar5 + 0x2046) != '\0') {
          gnt4_memcpy(DAT_803ca85c,(void *)(iVar5 + 0x13470),600);
        }
      }
    }
    DAT_803ca851 = '\0';
  }
  return iVar16;
}



// ==== 8008f774  zz_008f774_ ====

int zz_008f774_(int param_1)

{
  int iVar1;
  int iVar2;
  
  zz_008c104_(FUN_800906d4);
  iVar2 = 1;
  if (DAT_803ca851 == '\x01') {
    iVar1 = zz_008dbcc_();
    if (iVar1 == 0) {
      iVar2 = zz_008e0d0_(param_1);
      DAT_803ca851 = '\0';
    }
  }
  else if (((DAT_803ca851 < '\x01') && (-1 < DAT_803ca851)) &&
          (iVar1 = zz_008e108_((char)param_1), iVar1 == 0)) {
    DAT_803ca851 = DAT_803ca851 + '\x01';
    zz_008e378_(1);
    zz_008e378_(6);
    zz_008e378_(2);
  }
  return iVar2;
}



// ==== 8008f840  zz_008f840_ ====

int zz_008f840_(int param_1)

{
  int iVar1;
  int iVar2;
  
  zz_008c104_(FUN_800906d4);
  iVar2 = 1;
  if (DAT_803ca851 == '\x01') {
    iVar1 = zz_008dbcc_();
    if (iVar1 == 0) {
      iVar2 = zz_008e0d0_(param_1);
      DAT_803ca851 = '\0';
    }
  }
  else if (((DAT_803ca851 < '\x01') && (-1 < DAT_803ca851)) &&
          (iVar1 = zz_008e108_((char)param_1), iVar1 == 0)) {
    DAT_803ca851 = DAT_803ca851 + '\x01';
    zz_008e12c_(s_GG4E_GOTCHA_FORCE_USA_802b0d5c);
    zz_008e378_(1);
    zz_008e378_(3);
    zz_008e378_(5);
    zz_008e378_(2);
  }
  return iVar2;
}



// ==== 8008f920  FUN_8008f920 ====

undefined4 FUN_8008f920(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  
  if (*(char *)(param_1 + 7) == '\0') {
    *(undefined1 *)(param_1 + 7) = 1;
    zz_022161c_((int)*(char *)(param_1 + 6),DAT_804362c8,0,(undefined *)0x0);
  }
  *(undefined1 *)(param_1 + 4) = 0;
  uVar1 = zz_021e198_((int)*(char *)(param_1 + 6));
  cVar2 = (char)uVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if (cVar2 != -5) {
    if (cVar2 < -5) {
      if ((cVar2 == -0xd) || ((-0xe < cVar2 && (-7 < cVar2)))) {
LAB_8008f9d0:
        *(undefined1 *)(param_1 + 4) = 1;
        DAT_803ca853 = DAT_803ca853 | (byte)(1 << (int)*(char *)(param_1 + 6));
        return 0;
      }
    }
    else {
      if (cVar2 == -1) {
        return 1;
      }
      if ((-2 < cVar2) && (cVar2 < '\x01')) goto LAB_8008f9d0;
    }
  }
  return 0xffffffff;
}



// ==== 8008fa18  FUN_8008fa18 ====

undefined4 FUN_8008fa18(int param_1)

{
  int iVar1;
  char cVar2;
  
  if (*(char *)(param_1 + 4) == '\0') {
    *(undefined1 *)(param_1 + 0xc) = 0;
    *(undefined1 *)(param_1 + 4) = 0;
    DAT_803ca853 = DAT_803ca853 & ~(byte)(1 << (int)*(char *)(param_1 + 6));
    return 0;
  }
  iVar1 = zz_0221858_((int)*(char *)(param_1 + 6));
  cVar2 = (char)iVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if ((cVar2 != -2) && (-3 < cVar2)) {
    if (cVar2 == '\0') {
      *(undefined1 *)(param_1 + 4) = 0;
      DAT_803ca853 = DAT_803ca853 & ~(byte)(1 << (int)*(char *)(param_1 + 6));
      return 0;
    }
    if (cVar2 < '\0') {
      return 1;
    }
  }
  *(undefined1 *)(param_1 + 4) = 0;
  DAT_803ca853 = DAT_803ca853 & ~(byte)(1 << (int)*(char *)(param_1 + 6));
  return 0xffffffff;
}



// ==== 8008fb2c  FUN_8008fb2c ====

undefined4 FUN_8008fb2c(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  
  if (*(char *)(param_1 + 7) == '\0') {
    *(undefined1 *)(param_1 + 7) = 1;
    CARDCheckAsync((int)*(char *)(param_1 + 6),(undefined *)0x0);
  }
  uVar1 = zz_021e198_((int)*(char *)(param_1 + 6));
  cVar2 = (char)uVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if ((cVar2 != -4) && (-5 < cVar2)) {
    if (cVar2 == -1) {
      return 1;
    }
    if ((-2 < cVar2) && (cVar2 < '\x01')) {
      return 0;
    }
  }
  return 0xffffffff;
}



// ==== 8008fbe4  FUN_8008fbe4 ====

undefined4 FUN_8008fbe4(int param_1)

{
  undefined4 uVar1;
  char cVar3;
  size_t __n;
  int iVar2;
  
  if (*(char *)(param_1 + 7) == '\0') {
    *(undefined1 *)(param_1 + 7) = 1;
    zz_0222908_((int)*(char *)(param_1 + 6),(char *)(param_1 + 0x71),*(uint *)(param_1 + 0x40),
                (int *)&DAT_803caa04,(undefined *)0x0);
  }
  uVar1 = zz_021e198_((int)*(char *)(param_1 + 6));
  cVar3 = (char)uVar1;
  *(char *)(param_1 + 0xc) = cVar3;
  if (cVar3 != -6) {
    if (cVar3 < -6) {
      if (((cVar3 != -0xc) && (-0xd < cVar3)) && (-8 < cVar3)) {
LAB_8008fca0:
        __n = strlen((char *)(param_1 + 0x71));
        iVar2 = gnt4_strncmp((char *)(param_1 + 0x71),s_GG4E_GOTCHA_FORCE_USA_802b0d5c,__n);
        if (iVar2 != 0) {
          return 0;
        }
        *(undefined1 *)(param_1 + 0x18) = 1;
        return 0;
      }
    }
    else if ((cVar3 != -2) && (-3 < cVar3)) {
      if (cVar3 == '\0') goto LAB_8008fca0;
      if (cVar3 < '\0') {
        return 1;
      }
    }
  }
  return 0xffffffff;
}



// ==== 8008fcf4  FUN_8008fcf4 ====

undefined4 FUN_8008fcf4(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  
  if (*(char *)(param_1 + 7) == '\0') {
    *(undefined1 *)(param_1 + 7) = 1;
    CARDDeleteAsync((int)*(char *)(param_1 + 6),(char *)(param_1 + 0x71),(undefined *)0x0);
  }
  uVar1 = zz_021e198_((int)*(char *)(param_1 + 6));
  cVar2 = (char)uVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if (cVar2 == -4) {
LAB_8008fd90:
    uVar1 = 0;
    *(undefined1 *)(param_1 + 0x18) = 0;
  }
  else {
    if (-5 < cVar2) {
      if (cVar2 == -1) {
        return 1;
      }
      if ((-2 < cVar2) && (cVar2 < '\x01')) goto LAB_8008fd90;
    }
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



// ==== 8008fdb8  FUN_8008fdb8 ====

undefined4 FUN_8008fdb8(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  
  if (*(char *)(param_1 + 7) == '\0') {
    *(undefined1 *)(param_1 + 7) = 1;
    CARDFormatAsync((int)*(char *)(param_1 + 6),(undefined *)0x0);
  }
  uVar1 = zz_021e198_((int)*(char *)(param_1 + 6));
  cVar2 = (char)uVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if ((cVar2 != -3) && (-4 < cVar2)) {
    if (cVar2 == '\0') {
      *(undefined1 *)(param_1 + 0x1f) = 1;
      return 0;
    }
    if ((cVar2 < '\0') && (-2 < cVar2)) {
      return 1;
    }
  }
  return 0xffffffff;
}



// ==== 8008fe70  FUN_8008fe70 ====

undefined4 FUN_8008fe70(int param_1)

{
  char cVar1;
  
  cVar1 = zz_0222660_((int)*(char *)(param_1 + 6),(char *)(param_1 + 0x71),(int *)&DAT_803caa04);
  *(char *)(param_1 + 0xc) = cVar1;
  if ((cVar1 != -5) && (-6 < cVar1)) {
    if (cVar1 == -1) {
      return 1;
    }
    if ((-2 < cVar1) && (cVar1 < '\x01')) {
      *(undefined1 *)(param_1 + 5) = 1;
      *(undefined4 *)(param_1 + 0x44) = DAT_803caa08;
      return 0;
    }
  }
  return 0xffffffff;
}



// ==== 8008ff28  FUN_8008ff28 ====

undefined4 FUN_8008ff28(int param_1)

{
  char cVar1;
  
  if (*(char *)(param_1 + 5) == '\0') {
    *(undefined1 *)(param_1 + 0xc) = 0;
    *(undefined1 *)(param_1 + 5) = 0;
    return 0;
  }
  cVar1 = zz_022277c_((int *)&DAT_803caa04);
  *(char *)(param_1 + 0xc) = cVar1;
  if ((cVar1 != -2) && (-3 < cVar1)) {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 5) = 0;
      return 0;
    }
    if (cVar1 < '\0') {
      return 1;
    }
  }
  return 0xffffffff;
}



// ==== 8008ffc8  FUN_8008ffc8 ====

undefined4 FUN_8008ffc8(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  char cVar3;
  
  if ((*(char *)(param_1 + 7) == '\0') && (*(char *)(param_1 + 0xb) != '\0')) {
    *(undefined1 *)(param_1 + 7) = 1;
    zz_0222e10_((int *)&DAT_803caa04,*(uint *)(param_1 + 0x48),*(uint *)(param_1 + 0x38),
                *(uint *)(param_1 + 0x3c),(undefined *)0x0);
  }
  iVar1 = zz_021f8d0_((int)*(char *)(param_1 + 6));
  *(int *)(param_1 + 0x4c) = iVar1 - *(int *)(param_1 + 0x54);
  uVar2 = zz_021e198_((int)*(char *)(param_1 + 6));
  cVar3 = (char)uVar2;
  *(char *)(param_1 + 0xc) = cVar3;
  if (-10 < cVar3) {
    if (cVar3 == -1) {
      return 1;
    }
    if ((-2 < cVar3) && (cVar3 < '\x01')) {
      return 0;
    }
  }
  return 0xffffffff;
}



// ==== 800900b4  FUN_800900b4 ====

undefined4 FUN_800900b4(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  char cVar3;
  
  if ((*(char *)(param_1 + 7) == '\0') && (*(char *)(param_1 + 0xb) != '\0')) {
    *(undefined1 *)(param_1 + 7) = 1;
    zz_0223174_((int *)&DAT_803caa04,*(uint *)(param_1 + 0x48),*(uint *)(param_1 + 0x38),
                *(uint *)(param_1 + 0x3c),(undefined *)0x0);
  }
  iVar1 = zz_021f8d0_((int)*(char *)(param_1 + 6));
  *(int *)(param_1 + 0x4c) = iVar1 - *(int *)(param_1 + 0x54);
  uVar2 = zz_021e198_((int)*(char *)(param_1 + 6));
  cVar3 = (char)uVar2;
  *(char *)(param_1 + 0xc) = cVar3;
  if (-10 < cVar3) {
    if (cVar3 == -1) {
      return 1;
    }
    if ((-2 < cVar3) && (cVar3 < '\x01')) {
      return 0;
    }
  }
  return 0xffffffff;
}



// ==== 800901a0  FUN_800901a0 ====

undefined4 FUN_800901a0(int param_1)

{
  int iVar1;
  char cVar2;
  
  iVar1 = zz_0223634_((int)*(char *)(param_1 + 6),*(int *)(param_1 + 0x44),&DAT_803ca998);
  cVar2 = (char)iVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if (-6 < cVar2) {
    if (cVar2 == -1) {
      return 1;
    }
    if ((-2 < cVar2) && (cVar2 < '\x01')) {
      return 0;
    }
  }
  return 0xffffffff;
}



// ==== 80090238  FUN_80090238 ====

undefined4 FUN_80090238(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  
  if (*(char *)(param_1 + 7) == '\0') {
    *(undefined1 *)(param_1 + 7) = 1;
    DAT_803ca9d0 = 0;
    DAT_803ca9cc = DAT_803ca9cc & 0xfffc | 2;
    DAT_803ca9c6 = DAT_803ca9c6 & 0xf8 | 2;
    DAT_803ca9ce = DAT_803ca9ce & 0xfff0 | 3;
    DAT_803ca9c8 = 0x40;
    CARDSetStatusAsync((int)*(char *)(param_1 + 6),*(int *)(param_1 + 0x44),-0x7fc35668,DAT_803ca860
                      );
  }
  uVar1 = zz_021e198_((int)*(char *)(param_1 + 6));
  cVar2 = (char)uVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if (-6 < cVar2) {
    if (cVar2 == -1) {
      return 1;
    }
    if ((-2 < cVar2) && (cVar2 < '\x01')) {
      return 0;
    }
  }
  return 0xffffffff;
}



// ==== 80090354  FUN_80090354 ====

undefined4 FUN_80090354(int param_1)

{
  char cVar1;
  
  cVar1 = zz_0223cc0_((int)*(char *)(param_1 + 6),*(int *)(param_1 + 0x44),
                      (undefined1 *)(param_1 + 0x20));
  *(char *)(param_1 + 0xc) = cVar1;
  if (-5 < cVar1) {
    if (cVar1 == -1) {
      return 1;
    }
    if ((-2 < cVar1) && (cVar1 < '\x01')) {
      return 0;
    }
  }
  return 0xffffffff;
}



// ==== 800903e8  FUN_800903e8 ====

undefined4 FUN_800903e8(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  
  if (*(char *)(param_1 + 7) == '\0') {
    *(undefined1 *)(param_1 + 7) = 1;
    zz_0223d00_((int)*(char *)(param_1 + 6),*(int *)(param_1 + 0x44),*(byte *)(param_1 + 0x20),0);
  }
  uVar1 = zz_021e198_((int)*(char *)(param_1 + 6));
  cVar2 = (char)uVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if (-5 < cVar2) {
    if (cVar2 == -1) {
      return 1;
    }
    if ((-2 < cVar2) && (cVar2 < '\x01')) {
      return 0;
    }
  }
  return 0xffffffff;
}



// ==== 800904a0  FUN_800904a0 ====

undefined4 FUN_800904a0(int param_1)

{
  int iVar1;
  char cVar2;
  
  iVar1 = zz_021e318_((int)*(char *)(param_1 + 6),(undefined2 *)(param_1 + 0x22));
  cVar2 = (char)iVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if ((cVar2 != -2) && (-3 < cVar2)) {
    if (cVar2 == '\0') {
      return 0;
    }
    if (cVar2 < '\0') {
      return 1;
    }
  }
  return 0xffffffff;
}



// ==== 8009051c  FUN_8009051c ====

undefined4 FUN_8009051c(int param_1)

{
  int iVar1;
  char cVar2;
  
  iVar1 = zz_021e1c8_((int)*(char *)(param_1 + 6),(int *)(param_1 + 0x14),(int *)(param_1 + 0x10));
  cVar2 = (char)iVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if ((cVar2 != -3) && (-4 < cVar2)) {
    if (cVar2 == '\0') {
      return 0;
    }
    if ((cVar2 < '\0') && (-2 < cVar2)) {
      return 1;
    }
  }
  return 0xffffffff;
}



// ==== 800905b0  FUN_800905b0 ====

undefined4 FUN_800905b0(int param_1)

{
  int iVar1;
  char cVar2;
  
  iVar1 = zz_0223bfc_((int)*(char *)(param_1 + 6),(uint *)(param_1 + 0x28));
  cVar2 = (char)iVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if ((cVar2 != -2) && (-3 < cVar2)) {
    if (cVar2 == '\0') {
      return 0;
    }
    if (cVar2 < '\0') {
      return 1;
    }
  }
  return 0xffffffff;
}



// ==== 8009062c  FUN_8009062c ====

undefined4 FUN_8009062c(int param_1)

{
  int iVar1;
  char cVar2;
  
  iVar1 = zz_022255c_((int)*(char *)(param_1 + 6),0,(int *)&DAT_803caa04);
  cVar2 = (char)iVar1;
  *(char *)(param_1 + 0xc) = cVar2;
  if ((cVar2 != -5) && (-6 < cVar2)) {
    if (cVar2 == -1) {
      return 1;
    }
    if ((-2 < cVar2) && (cVar2 < '\x01')) {
      *(undefined1 *)(param_1 + 5) = 1;
      return 0;
    }
  }
  return 0xffffffff;
}



// ==== 800906d4  FUN_800906d4 ====

void FUN_800906d4(void)

{
  if ((PTR_DAT_80433930[0x34] == '\0') && (DAT_803c00a4 != 0)) {
    DAT_804362b8 = DAT_804362b8 + 1;
    DAT_803c115c = (DAT_804362b8 * 2 & 0x20U) + 0x802dae78;
    DAT_803c116a = 8;
    DAT_803c1140 = &DAT_802dae18;
    DAT_803c1144 = 0;
    DAT_803c1150 = &DAT_802daeb8;
    DAT_803c113c = 0;
    DAT_803c1174 = FLOAT_80437c68;
    DAT_803c1160 = &DAT_803c00a4;
    DAT_803c1164 = 5;
    DAT_803c1168 = 0xf;
    DAT_803c1170 = 1;
    DAT_803c1173 = 0xff;
    zz_00524d4_(-0x7fc3eed0);
  }
  return;
}



// ==== 800907a0  zz_00907a0_ ====

void zz_00907a0_(undefined4 *param_1)

{
  *param_1 = DAT_802dad78;
  param_1[1] = DAT_802dad7c;
  param_1[2] = DAT_802dad80;
  param_1[3] = DAT_802dad84;
  param_1[4] = DAT_802dad88;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  return;
}



// ==== 800907e0  zz_00907e0_ ====

void zz_00907e0_(uint *param_1,void *param_2,size_t param_3)

{
  uint uVar1;
  uint *__dest;
  size_t __n;
  uint auStack_158 [80];
  
  if ((param_2 != (void *)0x0) && (-1 < (int)param_3)) {
    __dest = param_1 + 5;
    param_1[0x15] = param_1[0x15] + param_3;
    uVar1 = param_1[0x16];
    if ((int)((param_3 + uVar1) - 0x40) < 1) {
      param_1[0x16] = param_3 + uVar1;
      gnt4_memcpy((void *)((int)__dest + uVar1),param_2,param_3);
    }
    else {
      __n = 0x40 - uVar1;
      gnt4_memcpy((void *)((int)__dest + uVar1),param_2,__n);
      zz_0090bb4_((int)__dest,auStack_158,0x40);
      zz_0090d04_((int)auStack_158);
      zz_0090dc8_((int *)auStack_158,param_1);
      for (; (int)__n < (int)(param_3 - 0x40); __n = __n + 0x40) {
        zz_0090bb4_((int)param_2 + __n,auStack_158,0x40);
        zz_0090d04_((int)auStack_158);
        zz_0090dc8_((int *)auStack_158,param_1);
      }
      param_1[0x16] = param_3 - __n;
      gnt4_memcpy(__dest,(void *)((int)param_2 + __n),param_1[0x16]);
    }
  }
  return;
}



// ==== 800908d4  zz_00908d4_ ====

void zz_00908d4_(int param_1,uint *param_2)

{
  uint uVar1;
  uint local_158 [83];
  
  uVar1 = param_2[0x16];
  if ((int)uVar1 < 0x38) {
    zz_0090bb4_((int)(param_2 + 5),local_158,uVar1);
    zz_0090dbc_(param_2[0x15],(int)local_158);
    zz_0090d04_((int)local_158);
    zz_0090dc8_((int *)local_158,param_2);
  }
  else {
    zz_0090bb4_((int)(param_2 + 5),local_158,uVar1);
    zz_0090d04_((int)local_158);
    zz_0090dc8_((int *)local_158,param_2);
    zz_0090cdc_(local_158);
    if (uVar1 == 0x40) {
      local_158[0] = 0x80000000;
    }
    zz_0090dbc_(param_2[0x15],(int)local_158);
    zz_0090d04_((int)local_158);
    zz_0090dc8_((int *)local_158,param_2);
  }
  zz_0090ad4_(param_2,param_1);
  return;
}



// ==== 800909b8  zz_00909b8_ ====

void zz_00909b8_(int param_1,uint *param_2,int param_3)

{
  uint uVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = 0;
  uVar1 = param_3 + 3U >> 2;
  if (param_3 < 1) {
    return;
  }
  uVar5 = param_3 + 3U >> 4;
  if (uVar5 != 0) {
    do {
      pbVar2 = (byte *)(param_1 + iVar4);
      pbVar3 = (byte *)(param_1 + iVar4 + 4);
      *param_2 = (uint)pbVar2[3] |
                 (uint)pbVar2[2] << 8 | (uint)*pbVar2 << 0x18 | (uint)pbVar2[1] << 0x10;
      pbVar2 = (byte *)(param_1 + iVar4 + 8);
      param_2[1] = (uint)pbVar3[3] |
                   (uint)pbVar3[2] << 8 | (uint)*pbVar3 << 0x18 | (uint)pbVar3[1] << 0x10;
      pbVar3 = (byte *)(param_1 + iVar4 + 0xc);
      iVar4 = iVar4 + 0x10;
      param_2[2] = (uint)pbVar2[3] |
                   (uint)pbVar2[2] << 8 | (uint)*pbVar2 << 0x18 | (uint)pbVar2[1] << 0x10;
      param_2[3] = (uint)pbVar3[3] |
                   (uint)pbVar3[2] << 8 | (uint)*pbVar3 << 0x18 | (uint)pbVar3[1] << 0x10;
      param_2 = param_2 + 4;
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
    uVar1 = uVar1 & 3;
    if (uVar1 == 0) {
      return;
    }
  }
  do {
    pbVar2 = (byte *)(param_1 + iVar4);
    iVar4 = iVar4 + 4;
    *param_2 = (uint)pbVar2[3] |
               (uint)pbVar2[2] << 8 | (uint)*pbVar2 << 0x18 | (uint)pbVar2[1] << 0x10;
    param_2 = param_2 + 1;
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  return;
}



// ==== 80090ad4  zz_0090ad4_ ====

/* WARNING: Removing unreachable block (ram,0x80090b6c) */
/* WARNING: Removing unreachable block (ram,0x80090ae8) */

void zz_0090ad4_(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  iVar5 = 2;
  do {
    puVar3 = (undefined1 *)(param_2 + iVar4);
    *puVar3 = (char)((uint)*param_1 >> 0x18);
    puVar3[1] = (char)((uint)*param_1 >> 0x10);
    puVar3[2] = (char)((uint)*param_1 >> 8);
    puVar3[3] = (char)*param_1;
    puVar3 = (undefined1 *)(param_2 + iVar4 + 4);
    iVar4 = iVar4 + 8;
    *puVar3 = (char)((uint)param_1[1] >> 0x18);
    puVar3[1] = (char)((uint)param_1[1] >> 0x10);
    puVar3[2] = (char)((uint)param_1[1] >> 8);
    puVar1 = param_1 + 1;
    param_1 = param_1 + 2;
    puVar3[3] = (char)*puVar1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  iVar5 = 1;
  do {
    puVar3 = (undefined1 *)(param_2 + iVar4);
    iVar4 = iVar4 + 4;
    *puVar3 = (char)((uint)*param_1 >> 0x18);
    puVar3[1] = (char)((uint)*param_1 >> 0x10);
    puVar3[2] = (char)((uint)*param_1 >> 8);
    uVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar3[3] = (char)uVar2;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}



// ==== 80090bb4  zz_0090bb4_ ====

void zz_0090bb4_(int param_1,uint *param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  
  gnt4_memset(param_2,0,0x40);
  if (param_3 == 0x40) {
    zz_00909b8_(param_1,param_2,0x40);
  }
  else {
    iVar1 = (int)param_3 >> 0x1f;
    iVar1 = (iVar1 * 4 | param_3 * 0x40000000 + iVar1 >> 0x1e) - iVar1;
    iVar2 = ((int)param_3 >> 2) + (uint)((int)param_3 < 0 && (param_3 & 3) != 0);
    zz_00909b8_(param_1,param_2,param_3 - iVar1);
    if (iVar1 == 2) {
      param_2[iVar2] =
           (uint)*(byte *)(param_1 + param_3 + -2) << 0x18 |
           (uint)*(byte *)(param_1 + param_3 + -1) << 0x10 | 0x8000;
    }
    else if (iVar1 < 2) {
      if (iVar1 == 0) {
        param_2[iVar2] = 0x80000000;
      }
      else if (-1 < iVar1) {
        param_2[iVar2] = (uint)*(byte *)(param_1 + param_3 + -1) << 0x18 | 0x800000;
      }
    }
    else if (iVar1 < 4) {
      iVar1 = param_1 + param_3;
      param_2[iVar2] =
           (uint)*(byte *)(iVar1 + -1) << 8 |
           (uint)*(byte *)(iVar1 + -3) << 0x18 | (uint)*(byte *)(iVar1 + -2) << 0x10 | 0x80;
    }
  }
  return;
}



// ==== 80090cdc  zz_0090cdc_ ====

void zz_0090cdc_(void *param_1)

{
  gnt4_memset(param_1,0,0x40);
  return;
}



// ==== 80090d04  zz_0090d04_ ====

void zz_0090d04_(int param_1)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  
  puVar2 = (uint *)(param_1 + 0x40);
  iVar3 = 0x10;
  do {
    uVar1 = puVar2[-0x10] ^ puVar2[-0xe] ^ puVar2[-3] ^ puVar2[-8];
    *puVar2 = uVar1 << 1 | uVar1 >> 0x1f;
    uVar1 = puVar2[-0xf] ^ puVar2[-0xd] ^ puVar2[-2] ^ puVar2[-7];
    puVar2[1] = uVar1 << 1 | uVar1 >> 0x1f;
    uVar1 = puVar2[-0xe] ^ puVar2[-0xc] ^ puVar2[-1] ^ puVar2[-6];
    puVar2[2] = uVar1 << 1 | uVar1 >> 0x1f;
    uVar1 = puVar2[-0xd] ^ puVar2[-0xb] ^ *puVar2 ^ puVar2[-5];
    puVar2[3] = uVar1 << 1 | uVar1 >> 0x1f;
    puVar2 = puVar2 + 4;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}



// ==== 80090dbc  zz_0090dbc_ ====

void zz_0090dbc_(int param_1,int param_2)

{
  *(int *)(param_2 + 0x3c) = param_1 << 3;
  return;
}



// ==== 80090dc8  zz_0090dc8_ ====

void zz_0090dc8_(int *param_1,uint *param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  
  iVar5 = 0;
  uVar11 = *param_2;
  uVar12 = param_2[1];
  uVar3 = param_2[2];
  uVar9 = param_2[3];
  uVar10 = param_2[4];
  iVar17 = 4;
  piVar6 = param_1;
  do {
    uVar15 = uVar12 << 0x1e | uVar12 >> 2;
    iVar5 = iVar5 + 5;
    uVar7 = uVar11 << 0x1e | uVar11 >> 2;
    uVar13 = (uVar11 << 5 | uVar11 >> 0x1b) +
             (uVar12 & uVar3 | uVar9 & ~uVar12) + uVar10 + *piVar6 + 0x5a827999;
    piVar1 = piVar6 + 3;
    uVar10 = uVar13 * 0x40000000 | uVar13 >> 2;
    uVar12 = (uVar13 * 0x20 | uVar13 >> 0x1b) +
             (uVar11 & uVar15 | uVar3 & ~uVar11) + uVar9 + piVar6[1] + 0x5a827999;
    piVar2 = piVar6 + 4;
    uVar11 = (uVar12 * 0x20 | uVar12 >> 0x1b) +
             (uVar13 & uVar7 | uVar15 & ~uVar13) + uVar3 + piVar6[2] + 0x5a827999;
    uVar9 = uVar12 * 0x40000000 | uVar12 >> 2;
    piVar6 = piVar6 + 5;
    uVar3 = uVar11 * 0x40000000 | uVar11 >> 2;
    uVar12 = (uVar11 * 0x20 | uVar11 >> 0x1b) +
             (uVar12 & uVar10 | uVar7 & ~uVar12) + uVar15 + *piVar1 + 0x5a827999;
    uVar11 = (uVar12 * 0x20 | uVar12 >> 0x1b) +
             (uVar11 & uVar9 | uVar10 & ~uVar11) + uVar7 + *piVar2 + 0x5a827999;
    iVar17 = iVar17 + -1;
  } while (iVar17 != 0);
  piVar6 = param_1 + iVar5;
  uVar7 = 0x28 - iVar5;
  if (iVar5 < 0x28) {
    uVar13 = uVar7 >> 1;
    uVar15 = uVar7;
    if (uVar13 == 0) goto LAB_80090fd0;
    do {
      uVar15 = uVar3;
      iVar17 = *piVar6;
      piVar1 = piVar6 + 1;
      uVar4 = uVar12 << 0x1e | uVar12 >> 2;
      piVar6 = piVar6 + 2;
      uVar12 = (uVar11 << 5 | uVar11 >> 0x1b) +
               (uVar9 ^ uVar12 ^ uVar15) + uVar10 + iVar17 + 0x6ed9eba1;
      uVar3 = uVar11 << 0x1e | uVar11 >> 2;
      uVar11 = (uVar12 * 0x20 | uVar12 >> 0x1b) +
               (uVar15 ^ uVar11 ^ uVar4) + uVar9 + *piVar1 + 0x6ed9eba1;
      uVar13 = uVar13 - 1;
      uVar9 = uVar4;
      uVar10 = uVar15;
    } while (uVar13 != 0);
    for (uVar15 = uVar7 & 1; uVar9 = uVar4, uVar15 != 0; uVar15 = uVar15 - 1) {
LAB_80090fd0:
      uVar8 = uVar12 ^ uVar3;
      iVar17 = *piVar6;
      uVar14 = uVar12 >> 2;
      uVar13 = uVar12 << 0x1e;
      piVar6 = piVar6 + 1;
      uVar4 = uVar3;
      uVar12 = uVar11;
      uVar3 = uVar13 | uVar14;
      uVar11 = (uVar11 << 5 | uVar11 >> 0x1b) + (uVar9 ^ uVar8) + uVar10 + iVar17 + 0x6ed9eba1;
      uVar10 = uVar9;
    }
    iVar5 = iVar5 + uVar7;
  }
  piVar6 = param_1 + iVar5;
  uVar7 = 0x3c - iVar5;
  if (iVar5 < 0x3c) {
    uVar13 = uVar7 >> 1;
    uVar15 = uVar7;
    if (uVar13 == 0) goto LAB_800910f0;
    do {
      uVar15 = uVar3;
      iVar17 = *piVar6;
      piVar1 = piVar6 + 1;
      uVar4 = uVar12 << 0x1e | uVar12 >> 2;
      piVar6 = piVar6 + 2;
      uVar12 = (uVar11 << 5 | uVar11 >> 0x1b) +
               (uVar15 & uVar9 | uVar12 & (uVar15 | uVar9)) + uVar10 + iVar17 + -0x70e44324;
      uVar3 = uVar11 << 0x1e | uVar11 >> 2;
      uVar11 = (uVar12 * 0x20 | uVar12 >> 0x1b) +
               (uVar4 & uVar15 | uVar11 & (uVar4 | uVar15)) + uVar9 + *piVar1 + -0x70e44324;
      uVar13 = uVar13 - 1;
      uVar9 = uVar4;
      uVar10 = uVar15;
    } while (uVar13 != 0);
    for (uVar15 = uVar7 & 1; uVar9 = uVar4, uVar15 != 0; uVar15 = uVar15 - 1) {
LAB_800910f0:
      iVar17 = *piVar6;
      uVar8 = uVar3 & uVar9;
      uVar16 = uVar12 & (uVar3 | uVar9);
      uVar14 = uVar12 >> 2;
      piVar6 = piVar6 + 1;
      uVar13 = uVar12 << 0x1e;
      uVar4 = uVar3;
      uVar12 = uVar11;
      uVar3 = uVar13 | uVar14;
      uVar11 = (uVar11 << 5 | uVar11 >> 0x1b) + (uVar8 | uVar16) + uVar10 + iVar17 + -0x70e44324;
      uVar10 = uVar9;
    }
    iVar5 = iVar5 + uVar7;
  }
  piVar6 = param_1 + iVar5;
  uVar7 = 0x50 - iVar5;
  if (iVar5 < 0x50) {
    uVar13 = uVar7 >> 1;
    uVar15 = uVar9;
    uVar4 = uVar10;
    uVar14 = uVar12;
    if (uVar13 != 0) {
      do {
        uVar10 = uVar3;
        iVar5 = *piVar6;
        piVar1 = piVar6 + 1;
        uVar9 = uVar12 << 0x1e | uVar12 >> 2;
        piVar6 = piVar6 + 2;
        uVar12 = (uVar11 << 5 | uVar11 >> 0x1b) +
                 (uVar15 ^ uVar12 ^ uVar10) + uVar4 + iVar5 + -0x359d3e2a;
        uVar3 = uVar11 << 0x1e | uVar11 >> 2;
        uVar11 = (uVar12 * 0x20 | uVar12 >> 0x1b) +
                 (uVar10 ^ uVar11 ^ uVar9) + uVar15 + *piVar1 + -0x359d3e2a;
        uVar13 = uVar13 - 1;
        uVar15 = uVar9;
        uVar4 = uVar10;
      } while (uVar13 != 0);
      uVar7 = uVar7 & 1;
      uVar14 = uVar12;
      if (uVar7 == 0) goto LAB_80091250;
    }
    do {
      uVar12 = uVar11;
      uVar10 = uVar9;
      uVar9 = uVar3;
      uVar11 = (uVar12 << 5 | uVar12 >> 0x1b) +
               (uVar10 ^ uVar14 ^ uVar9) + uVar4 + *piVar6 + -0x359d3e2a;
      uVar3 = uVar14 << 0x1e | uVar14 >> 2;
      piVar6 = piVar6 + 1;
      uVar7 = uVar7 - 1;
      uVar4 = uVar10;
      uVar14 = uVar12;
    } while (uVar7 != 0);
  }
LAB_80091250:
  *param_2 = *param_2 + uVar11;
  param_2[1] = param_2[1] + uVar12;
  param_2[2] = param_2[2] + uVar3;
  param_2[3] = param_2[3] + uVar9;
  param_2[4] = param_2[4] + uVar10;
  return;
}



// ==== 80091298  zz_0091298_ ====

void zz_0091298_(int param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  
  uVar5 = 0;
  if (param_2 != 0) {
    if (8 < param_2) {
      uVar1 = param_3 & 0xff;
      uVar6 = param_2 - 1 >> 3;
      uVar2 = param_4 & 0xff;
      if (param_2 != 8) {
        do {
          pbVar4 = (byte *)(param_1 + uVar5);
          uVar5 = uVar5 + 8;
          *pbVar4 = *pbVar4 ^ (&DAT_802daed8)[uVar1];
          *pbVar4 = *pbVar4 ^ (&DAT_802dafd8)[uVar2];
          pbVar4[1] = pbVar4[1] ^ (&DAT_802daed8)[uVar1];
          pbVar4[1] = pbVar4[1] ^ (&DAT_802dafd8)[uVar2];
          pbVar4[2] = pbVar4[2] ^ (&DAT_802daed8)[uVar1];
          pbVar4[2] = pbVar4[2] ^ (&DAT_802dafd8)[uVar2];
          pbVar4[3] = pbVar4[3] ^ (&DAT_802daed8)[uVar1];
          pbVar4[3] = pbVar4[3] ^ (&DAT_802dafd8)[uVar2];
          pbVar4[4] = pbVar4[4] ^ (&DAT_802daed8)[uVar1];
          pbVar4[4] = pbVar4[4] ^ (&DAT_802dafd8)[uVar2];
          pbVar4[5] = pbVar4[5] ^ (&DAT_802daed8)[uVar1];
          pbVar4[5] = pbVar4[5] ^ (&DAT_802dafd8)[uVar2];
          pbVar4[6] = pbVar4[6] ^ (&DAT_802daed8)[uVar1];
          pbVar4[6] = pbVar4[6] ^ (&DAT_802dafd8)[uVar2];
          pbVar4[7] = pbVar4[7] ^ (&DAT_802daed8)[uVar1];
          pbVar4[7] = pbVar4[7] ^ (&DAT_802dafd8)[uVar2];
          uVar6 = uVar6 - 1;
        } while (uVar6 != 0);
      }
    }
    iVar3 = param_2 - uVar5;
    pbVar4 = (byte *)(param_1 + uVar5);
    if (uVar5 < param_2) {
      do {
        *pbVar4 = *pbVar4 ^ (&DAT_802daed8)[param_3 & 0xff];
        *pbVar4 = *pbVar4 ^ (&DAT_802dafd8)[param_4 & 0xff];
        pbVar4 = pbVar4 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  return;
}



// ==== 80091450  zz_0091450_ ====

void zz_0091450_(int param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  
  uVar5 = 0;
  if (param_2 != 0) {
    if (8 < param_2) {
      uVar1 = param_4 & 0xff;
      uVar6 = param_2 - 1 >> 3;
      uVar2 = param_3 & 0xff;
      if (param_2 != 8) {
        do {
          pbVar4 = (byte *)(param_1 + uVar5);
          uVar5 = uVar5 + 8;
          *pbVar4 = *pbVar4 ^ (&DAT_802dafd8)[uVar1];
          *pbVar4 = *pbVar4 ^ (&DAT_802daed8)[uVar2];
          pbVar4[1] = pbVar4[1] ^ (&DAT_802dafd8)[uVar1];
          pbVar4[1] = pbVar4[1] ^ (&DAT_802daed8)[uVar2];
          pbVar4[2] = pbVar4[2] ^ (&DAT_802dafd8)[uVar1];
          pbVar4[2] = pbVar4[2] ^ (&DAT_802daed8)[uVar2];
          pbVar4[3] = pbVar4[3] ^ (&DAT_802dafd8)[uVar1];
          pbVar4[3] = pbVar4[3] ^ (&DAT_802daed8)[uVar2];
          pbVar4[4] = pbVar4[4] ^ (&DAT_802dafd8)[uVar1];
          pbVar4[4] = pbVar4[4] ^ (&DAT_802daed8)[uVar2];
          pbVar4[5] = pbVar4[5] ^ (&DAT_802dafd8)[uVar1];
          pbVar4[5] = pbVar4[5] ^ (&DAT_802daed8)[uVar2];
          pbVar4[6] = pbVar4[6] ^ (&DAT_802dafd8)[uVar1];
          pbVar4[6] = pbVar4[6] ^ (&DAT_802daed8)[uVar2];
          pbVar4[7] = pbVar4[7] ^ (&DAT_802dafd8)[uVar1];
          pbVar4[7] = pbVar4[7] ^ (&DAT_802daed8)[uVar2];
          uVar6 = uVar6 - 1;
        } while (uVar6 != 0);
      }
    }
    iVar3 = param_2 - uVar5;
    pbVar4 = (byte *)(param_1 + uVar5);
    if (uVar5 < param_2) {
      do {
        *pbVar4 = *pbVar4 ^ (&DAT_802dafd8)[param_4 & 0xff];
        *pbVar4 = *pbVar4 ^ (&DAT_802daed8)[param_3 & 0xff];
        pbVar4 = pbVar4 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  return;
}



// ==== 80091608  zz_0091608_ ====

bool zz_0091608_(void *param_1,uint param_2,uint param_3,uint param_4,void *param_5,int param_6)

{
  int iVar1;
  uint *puVar2;
  
  zz_0091450_((int)param_1,param_2,param_3,param_4);
  puVar2 = (uint *)(param_6 * 0x5c + -0x7fc35944);
  zz_00907a0_(puVar2);
  zz_00907e0_(puVar2,(&PTR_s_BNK_KEY_Foinweruia5_802dad8c)[param_6],0x13);
  zz_00907e0_(puVar2,param_1,param_2);
  zz_00908d4_((int)(&DAT_803ca680 + param_6 * 0x14),puVar2);
  iVar1 = gnt4_memcmp(&DAT_803ca680 + param_6 * 0x14,param_5,0x14);
  return iVar1 != 0;
}



// ==== 800916c4  zz_00916c4_ ====

void zz_00916c4_(void *param_1,uint param_2,byte *param_3,int param_4)

{
  int iVar1;
  uint *puVar2;
  byte *pbVar3;
  
  puVar2 = (uint *)(param_4 * 0x5c + -0x7fc35944);
  zz_00907a0_(puVar2);
  zz_00907e0_(puVar2,(&PTR_s_BNK_KEY_Foinweruia5_802dad8c)[param_4],0x13);
  zz_00907e0_(puVar2,param_1,param_2);
  iVar1 = param_4 * 0x14;
  pbVar3 = &DAT_803ca680 + iVar1;
  zz_00908d4_((int)pbVar3,puVar2);
  zz_0091298_((int)param_1,param_2,(uint)*pbVar3,(uint)(byte)(&DAT_803ca681)[iVar1]);
  *param_3 = *pbVar3;
  param_3[1] = (&DAT_803ca681)[iVar1];
  param_3[2] = (&DAT_803ca682)[iVar1];
  param_3[3] = (&DAT_803ca683)[iVar1];
  param_3[4] = (&DAT_803ca684)[iVar1];
  param_3[5] = (&DAT_803ca685)[iVar1];
  param_3[6] = (&DAT_803ca686)[iVar1];
  param_3[7] = (&DAT_803ca687)[iVar1];
  param_3[8] = (&DAT_803ca688)[iVar1];
  param_3[9] = (&DAT_803ca689)[iVar1];
  param_3[10] = (&DAT_803ca68a)[iVar1];
  param_3[0xb] = (&DAT_803ca68b)[iVar1];
  param_3[0xc] = (&DAT_803ca68c)[iVar1];
  param_3[0xd] = (&DAT_803ca68d)[iVar1];
  param_3[0xe] = (&DAT_803ca68e)[iVar1];
  param_3[0xf] = (&DAT_803ca68f)[iVar1];
  param_3[0x10] = (&DAT_803ca690)[iVar1];
  param_3[0x11] = (&DAT_803ca691)[iVar1];
  param_3[0x12] = (&DAT_803ca692)[iVar1];
  param_3[0x13] = (&DAT_803ca693)[iVar1];
  return;
}



// ==== 80091920  FUN_80091920 ====

void FUN_80091920(int param_1)

{
  *(undefined1 *)(param_1 + 0x6e8) = 0x80;
  *(byte *)(param_1 + 0x6e9) = *(byte *)(param_1 + 0x6e9) | 0x80;
  zz_0092a9c_(param_1);
  *(undefined1 *)(param_1 + 0x14e) = 0;
  return;
}



// ==== 8009196c  FUN_8009196c ====

void FUN_8009196c(int param_1)

{
  zz_0148718_(param_1,(byte *)(param_1 + 0x14c));
  zz_01485e8_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80437c78) * FLOAT_80437c70);
  }
  return;
}



// ==== 800919fc  FUN_800919fc ====

void FUN_800919fc(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_802db430)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80091a3c  FUN_80091a3c ====

void FUN_80091a3c(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x15);
  return;
}



// ==== 80091a74  FUN_80091a74 ====

void FUN_80091a74(int param_1)

{
  (*(code *)(&PTR_FUN_802db43c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80091ab0  FUN_80091ab0 ====

void FUN_80091ab0(int param_1)

{
  (*(code *)(&PTR_zz_0091e34__802db448)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80091aec  FUN_80091aec ====

void FUN_80091aec(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_802db45c)[*(char *)(param_1 + 0x544)])();
  return;
}



// ==== 80091b34  FUN_80091b34 ====

void FUN_80091b34(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80437c80;
  if ((*(char *)(param_1 + 0x7ce) == '\x0f') || (*(char *)(param_1 + 0x7ce) == '\x10')) {
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x58);
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x5c);
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x70);
    zz_0091dc0_(param_1);
    zz_0091bc0_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x581) = 2;
    zz_0091e34_(param_1);
  }
  return;
}



// ==== 80091bc0  zz_0091bc0_ ====

void zz_0091bc0_(int param_1)

{
  *(undefined1 *)(param_1 + 0x544) = 1;
  zz_0092518_(param_1);
  zz_004beb8_((double)FLOAT_80437c84,param_1,1,2,0xf,0xc,2);
  zz_004beb8_((double)FLOAT_80437c84,param_1,6,2,0x1b,0xc,2);
  return;
}



// ==== 80091c34  FUN_80091c34 ====

void FUN_80091c34(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,7);
  zz_0091dc0_(param_1);
  if ((*(char *)(param_1 + 0x1cee) == '\0') && (FLOAT_80437c80 < *(float *)(param_1 + 0x558))) {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x6ec) < '\x01') {
    dVar1 = (double)FLOAT_80437c84;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    zz_004beb8_(dVar1,param_1,1,2,0x11,0xffffffff,0xffffffff);
  }
  else {
    zz_0092534_(param_1);
    zz_004beb8_((double)FLOAT_80437c84,param_1,1,2,0x10,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80091d00  FUN_80091d00 ====

void FUN_80091d00(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,7);
  zz_0091dc0_(param_1);
  if ((*(uint *)(param_1 + 0x5d4) & 0x20) == 0) {
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a6fc_(param_1,0x10);
      dVar1 = (double)FLOAT_80437c88;
      *(undefined1 *)(param_1 + 0x540) = 1;
      zz_004beb8_(dVar1,param_1,1,0,0xb,0xffffffff,0xffffffff);
      zz_006a750_(param_1,0x10);
      *(undefined1 *)(param_1 + 0x544) = 2;
      *(undefined1 *)(param_1 + 0x588) = 1;
    }
  }
  else {
    zz_0091bc0_(param_1);
  }
  return;
}



// ==== 80091dc0  zz_0091dc0_ ====

void zz_0091dc0_(int param_1)

{
  float fVar1;
  
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,2);
  fVar1 = FLOAT_80437c80;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_80437c8c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 80091e34  zz_0091e34_ ====

void zz_0091e34_(int param_1)

{
  zz_0092480_(param_1);
  (*(code *)(&PTR_FUN_80433970)[*(char *)(param_1 + 0x545)])(param_1);
  (*(code *)(&PTR_FUN_80433968)[*(char *)(param_1 + 0x544)])(param_1);
  (*(code *)(&PTR_FUN_802db468)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 80091ec4  FUN_80091ec4 ====

void FUN_80091ec4(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80437c84;
  *(char *)(param_1 + 0x545) = *(char *)(param_1 + 0x545) + '\x01';
  zz_004beb8_(dVar1,param_1,4,2,0x1a,4,2);
  return;
}



// ==== 80091f08  FUN_80091f08 ====

void FUN_80091f08(int param_1)

{
  zz_004cd24_(param_1,4);
  return;
}



// ==== 80091f2c  FUN_80091f2c ====

void FUN_80091f2c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80437c90;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  zz_0092518_(param_1);
  zz_004beb8_((double)FLOAT_80437c84,param_1,1,2,(int)*(char *)(param_1 + 0x6ea),4,2);
  return;
}



// ==== 80091f94  FUN_80091f94 ====

void FUN_80091f94(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80437c80;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  if ((*(float *)(param_1 + 0x560) < fVar1) ||
     ((*(char *)(param_1 + 0x1cee) != '\0' && (*(short *)(param_1 + 0x54a) != 0)))) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0092534_(param_1);
    dVar2 = (double)FLOAT_80437c84;
    *(undefined2 *)(param_1 + 0x54c) = 5;
    zz_004beb8_(dVar2,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80092030  FUN_80092030 ====

void FUN_80092030(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  fVar1 = FLOAT_80437c80;
  *(undefined2 *)(param_1 + 0x54c) = 5;
  fVar2 = FLOAT_80437c94;
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    if (*(char *)(param_1 + 0x6ec) < '\x01') {
      dVar4 = (double)FLOAT_80437c84;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x55c) = fVar2;
      *(undefined2 *)(param_1 + 0x54c) = 10;
      zz_004beb8_(dVar4,param_1,7,2,*(char *)(param_1 + 0x6ea) + 10,4,2);
    }
    else {
      zz_006bf80_(param_1);
      zz_0092534_(param_1);
      zz_004beb8_((double)FLOAT_80437c84,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,
                  0xffffffff);
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    iVar3 = zz_00677b0_(param_1);
    if (iVar3 == 0) {
      zz_006a4f4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = *(float *)(param_1 + 0x558) + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80092174  FUN_80092174 ====

void FUN_80092174(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  *(undefined2 *)(param_1 + 0x54c) = 10;
  if ((*(char *)(param_1 + 0x745) != '\0') && (iVar3 = zz_006dbe0_(param_1,0,1,0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    zz_0092518_(param_1);
    zz_006bf80_(param_1);
    zz_0092534_(param_1);
    zz_004beb8_((double)FLOAT_80437c84,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,
                0xffffffff);
    return;
  }
  fVar2 = FLOAT_80437c80;
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) &&
      (fVar1 = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x55c) = fVar1, fVar2 < fVar1)) && (*(char *)(param_1 + 0x1cee) == '\0'))
  {
    return;
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 0) {
    zz_006a4f4_(param_1);
  }
  else {
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800922a0  FUN_800922a0 ====

void FUN_800922a0(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80437c80;
  *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0xff;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = 0;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_004beb8_((double)FLOAT_80437c84,param_1,2,2,*(char *)(param_1 + 0x6eb) + 0x15,0xc,2);
  zz_0092334_(param_1);
  return;
}



// ==== 80092334  zz_0092334_ ====

void zz_0092334_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  
  cVar1 = *(char *)(param_1 + 0x6eb);
  iVar3 = (int)cVar1;
  if (iVar3 == 0) {
    zz_006ed8c_((double)FLOAT_80437c98,param_1);
  }
  else {
    fVar2 = *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    if (*(float *)(param_1 + 0x44) < fVar2) {
      *(float *)(param_1 + 0x44) = fVar2;
    }
    *(float *)(param_1 + 0x4c) = FLOAT_80437c80;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
  }
  if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
    *(float *)(param_1 + 0x48) = FLOAT_80437c84;
  }
  else {
    *(float *)(param_1 + 0x48) = FLOAT_80437c80;
  }
  FUN_80067310((double)FLOAT_80437c8c,param_1,*(short *)(param_1 + 0x5ae));
  zz_0067a28_(param_1);
  if (*(char *)(param_1 + 0x6ea) == iVar3) {
    zz_004cd24_(param_1,3);
  }
  else {
    if (-1 < *(char *)(param_1 + 0x6ea)) {
      zz_004beb8_((double)*(float *)(param_1 + 0x1ae0),param_1,1,2,
                  *(short *)(param_1 + 0x54c) + iVar3,
                  (int)(FLOAT_80437c9c +
                       (float)((double)(float)((double)CONCAT44(0x43300000,
                                                                (int)*(short *)(param_1 + 0x1af8) ^
                                                                0x80000000) - DOUBLE_80437c78) -
                              (double)*(float *)(param_1 + 0x1ae0))),2);
      zz_004beb8_((double)FLOAT_80437c84,param_1,2,2,iVar3 + 0x15,0xc,2);
    }
    *(char *)(param_1 + 0x6ea) = cVar1;
  }
  return;
}



// ==== 80092480  zz_0092480_ ====

void zz_0092480_(int param_1)

{
  undefined2 uVar2;
  int iVar1;
  int iVar3;
  char cVar4;
  
  *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  uVar2 = zz_006d0dc_(param_1,0x81,0);
  *(undefined2 *)(param_1 + 0x54a) = uVar2;
  zz_006e1ac_(param_1,0xc1,1);
  iVar3 = 0;
  iVar1 = zz_0066ac0_(param_1,0);
  if (iVar1 != 0) {
    iVar3 = -1;
  }
  cVar4 = '\0';
  if (iVar3 != 0) {
    cVar4 = ((byte)((int)*(short *)(param_1 + 0x5aa) + 0x2000U >> 0xe) & 3) + 1;
  }
  *(char *)(param_1 + 0x6eb) = cVar4;
  return;
}



// ==== 80092518  zz_0092518_ ====

void zz_0092518_(int param_1)

{
  float fVar1;
  
  *(undefined1 *)(param_1 + 0x745) = 0;
  fVar1 = FLOAT_80437c94;
  *(undefined1 *)(param_1 + 0x6ec) = 5;
  *(float *)(param_1 + 0x558) = fVar1;
  return;
}



// ==== 80092534  zz_0092534_ ====

void zz_0092534_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80437ca0;
  *(char *)(param_1 + 0x6ec) = *(char *)(param_1 + 0x6ec) + -1;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x587) = 0;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    zz_0082824_(param_1,10);
  }
  return;
}



// ==== 800925a0  FUN_800925a0 ====

void FUN_800925a0(int param_1)

{
  (*(code *)(&PTR_FUN_802db478)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800925dc  FUN_800925dc ====

void FUN_800925dc(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0147e34_(param_1);
  return;
}



// ==== 8009260c  FUN_8009260c ====

void FUN_8009260c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0147e34_(param_1);
  return;
}



// ==== 8009263c  FUN_8009263c ====

void FUN_8009263c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802db48c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8009268c  FUN_8009268c ====

void FUN_8009268c(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80437c94;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80437c98,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80437c84;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80437c80;
  zz_0092dcc_(param_1,0);
  return;
}



// ==== 800927c0  FUN_800927c0 ====

void FUN_800927c0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80437c98,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_80437c80;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80437c94;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 8009287c  FUN_8009287c ====

void FUN_8009287c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x541) = 0xff;
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80437c90 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_80437c8c;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80437c90 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_80437c80;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    *(float *)(param_1 + 0x558) = fVar3;
    if (*(char *)(param_1 + 0x1b01) != '\0') {
      dVar4 = (double)FLOAT_80437c84;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 80092998  FUN_80092998 ====

void FUN_80092998(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80437c78) * FLOAT_80437c70);
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80437c70,param_1);
  FUN_80067310((double)FLOAT_80437c8c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80092a68  FUN_80092a68 ====

void FUN_80092a68(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 80092a9c  zz_0092a9c_ ====

void zz_0092a9c_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0xa00) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_80092b90;
    *(code **)(puVar1 + 0x10c) = FUN_80092d54;
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



// ==== 80092b90  FUN_80092b90 ====

void FUN_80092b90(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802dc3dc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80092be4  FUN_80092be4 ====

void FUN_80092be4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80437ca8;
  *(undefined1 *)(param_9 + 0x84) = 0x47;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),8,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  uVar2 = 8;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),8,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80437cac,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0092cc0_(param_9);
  return;
}



// ==== 80092cc0  zz_0092cc0_ ====

void zz_0092cc0_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = (int)*(char *)(*(int *)(param_1 + 0x90) + 0x14e);
  iVar1 = iVar3 * 0xc;
  *(undefined *)(param_1 + 0x89) = (&DAT_80433978)[iVar3];
  uVar2 = *(undefined4 *)(&DAT_802dc3bc + iVar1);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802dc3b8 + iVar1);
  *(undefined4 *)(param_1 + 0x68) = uVar2;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802dc3c0 + iVar1);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(&DAT_802dc3d0 + iVar3 * 6);
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_802dc3d4 + iVar3 * 6);
  return;
}



// ==== 80092d34  FUN_80092d34 ====

void FUN_80092d34(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80092d54  FUN_80092d54 ====

void FUN_80092d54(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar2 = *(int *)(param_9 + 0xe0);
    uVar1 = 1;
  }
  else {
    iVar2 = *(int *)(param_9 + 0xe4);
    uVar1 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar2,uVar1);
  return;
}



// ==== 80092dcc  zz_0092dcc_ ====

void zz_0092dcc_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 8;
    puVar1[0x11] = param_2;
    puVar1[0x12] = 0;
    *(code **)(puVar1 + 0xc) = FUN_80092f94;
    *(code **)(puVar1 + 0x10c) = FUN_80093600;
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



// ==== 80092ecc  FUN_80092ecc ====

void FUN_80092ecc(undefined1 param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  puVar1 = zz_008893c_(2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 8;
    puVar1[0x11] = param_1;
    puVar1[0x12] = 3;
    *(code **)(puVar1 + 0xc) = FUN_80092f94;
    *(code **)(puVar1 + 0x10c) = FUN_80093600;
    uVar2 = param_2[1];
    *(undefined4 *)(puVar1 + 0x20) = *param_2;
    *(undefined4 *)(puVar1 + 0x24) = uVar2;
    *(undefined4 *)(puVar1 + 0x28) = param_2[2];
    uVar2 = param_3[1];
    *(undefined4 *)(puVar1 + 0x38) = *param_3;
    *(undefined4 *)(puVar1 + 0x3c) = uVar2;
    *(undefined4 *)(puVar1 + 0x40) = param_3[2];
    *(undefined4 *)(puVar1 + 0x8c) = 0;
  }
  return;
}



// ==== 80092f94  FUN_80092f94 ====

void FUN_80092f94(int param_1)

{
  (*(code *)(&PTR_FUN_802dc5f0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80092fd0  FUN_80092fd0 ====

void FUN_80092fd0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  double dVar10;
  undefined8 uVar11;
  
  dVar10 = DOUBLE_80437cc0;
  fVar4 = FLOAT_80437cb0;
  pfVar8 = (float *)(param_9 + 0x144);
  iVar9 = *(int *)(param_9 + 0x8c);
  iVar6 = (int)*(char *)(param_9 + 0x11);
  iVar7 = iVar6 * 0x24;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(float *)(param_9 + 0xd4) = fVar4;
  *(float *)(param_9 + 0xd8) =
       (float)((double)CONCAT44(0x43300000,(int)(char)(&DAT_802dc563)[iVar7] ^ 0x80000000) - dVar10)
  ;
  *(undefined *)(param_9 + 0x189) = (&DAT_802dc562)[iVar7];
  uVar2 = DAT_802b0cb8;
  cVar1 = *(char *)(param_9 + 0x12);
  if (cVar1 == '\x02') {
    param_2 = (double)*(float *)(param_9 + 0x24);
    param_3 = (double)*(float *)(param_9 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_9 + 0x20),param_2,param_3,pfVar8);
  }
  else if (cVar1 == '\x03') {
    *(undefined4 *)(param_9 + 0x9c) = DAT_802b0cb4;
    uVar3 = DAT_802b0cbc;
    *(undefined4 *)(param_9 + 0xa0) = uVar2;
    *(undefined4 *)(param_9 + 0xa4) = uVar3;
    param_2 = (double)*(float *)(param_9 + 0x24);
    param_3 = (double)*(float *)(param_9 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_9 + 0x20),param_2,param_3,pfVar8);
    param_12 = param_9 + 0x9c;
    zz_0045ef4_(pfVar8,(int)(char)(&DAT_802dc57c)[iVar7],param_9 + 0x38,param_12);
  }
  else {
    if (cVar1 == '\0') {
      gnt4_PSMTXCopy_bl((float *)(iVar9 + (char)(&DAT_802dc561)[iVar7] * 0x30 + 0x8d4),
                        (float *)(param_9 + 0x114));
    }
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x114);
    *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x124);
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x134);
    dVar10 = gnt4_PSVECMag_bl((float *)(param_9 + 0x20));
    *(float *)(param_9 + 0x58) = (float)dVar10;
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x118);
    *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x128);
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x138);
    dVar10 = gnt4_PSVECMag_bl((float *)(param_9 + 0x20));
    *(float *)(param_9 + 0x5c) = (float)dVar10;
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x11c);
    *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 300);
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x13c);
    dVar10 = gnt4_PSVECMag_bl((float *)(param_9 + 0x20));
    *(float *)(param_9 + 0x60) = (float)dVar10;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_9 + 0x114),(float *)(iVar7 + -0x7fd23a9c),(float *)(param_9 + 0x20));
    cVar1 = (&DAT_802dc578)[iVar7];
    if (cVar1 == '\x02') {
      *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 0x11c);
      *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 300);
      *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x13c);
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 0x114);
        *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x124);
        *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x134);
      }
      else if (-1 < cVar1) {
        *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 0x118);
        *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x128);
        *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x138);
      }
    }
    else if (cVar1 < '\x04') {
      param_2 = (double)FLOAT_80437cb4;
      gnt4_PSMTXRotRad_bl((double)(float)(param_2 *
                                         (double)(float)((double)CONCAT44(0x43300000,
                                                                          (int)*(short *)(iVar9 + 
                                                  0x5ae) ^ 0x80000000) - DOUBLE_80437cc0)),pfVar8,
                          0x79);
      *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 0x14c);
      *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x15c);
      *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x16c);
    }
    if ((&DAT_802dc579)[iVar7] == '\x01') {
      gnt4_PSQUATScale_bl((double)FLOAT_80437cb8,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38)
                         );
    }
    cVar1 = (&DAT_802dc57a)[iVar7];
    if (cVar1 == '\x02') {
      *(undefined4 *)(param_9 + 0x9c) = *(undefined4 *)(param_9 + 0x11c);
      *(undefined4 *)(param_9 + 0xa0) = *(undefined4 *)(param_9 + 300);
      *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(param_9 + 0x13c);
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined4 *)(param_9 + 0x9c) = *(undefined4 *)(param_9 + 0x114);
        *(undefined4 *)(param_9 + 0xa0) = *(undefined4 *)(param_9 + 0x124);
        *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(param_9 + 0x134);
      }
      else if (-1 < cVar1) {
        *(undefined4 *)(param_9 + 0x9c) = *(undefined4 *)(param_9 + 0x118);
        *(undefined4 *)(param_9 + 0xa0) = *(undefined4 *)(param_9 + 0x128);
        *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(param_9 + 0x138);
      }
    }
    else if (cVar1 < '\x04') {
      param_2 = (double)FLOAT_80437cb4;
      gnt4_PSMTXRotRad_bl((double)(float)(param_2 *
                                         (double)(float)((double)CONCAT44(0x43300000,
                                                                          (int)*(short *)(iVar9 + 
                                                  0x5ae) ^ 0x80000000) - DOUBLE_80437cc0)),pfVar8,
                          0x79);
      *(undefined4 *)(param_9 + 0x9c) = *(undefined4 *)(param_9 + 0x148);
      *(undefined4 *)(param_9 + 0xa0) = *(undefined4 *)(param_9 + 0x158);
      *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(param_9 + 0x168);
    }
    if ((&DAT_802dc57b)[iVar7] == '\x01') {
      gnt4_PSQUATScale_bl((double)FLOAT_80437cb8,(float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c)
                         );
    }
    param_12 = param_9 + 0x9c;
    zz_0045ef4_(pfVar8,(int)(char)(&DAT_802dc57c)[iVar7],param_9 + 0x38,param_12);
    zz_00456a0_(pfVar8,pfVar8,(float *)(param_9 + 0x58));
    *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x160) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x170) = *(undefined4 *)(param_9 + 0x28);
  }
  *(undefined *)(param_9 + 0x188) = (&DAT_802dc57d)[iVar7];
  if ((*(byte *)(param_9 + 0x188) & 1) == 0) {
    uVar5 = zz_00055fc_();
    *(short *)(param_9 + 0x70) = (short)(uVar5 << 0xb);
  }
  else {
    *(undefined2 *)(param_9 + 0x70) = *(undefined2 *)(&DAT_802dc57e + iVar7);
  }
  if ((*(byte *)(param_9 + 0x188) & 2) == 0) {
    uVar5 = zz_00055fc_();
    *(short *)(param_9 + 0x72) = (short)(uVar5 << 0xb);
  }
  else {
    *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(&DAT_802dc580 + iVar7);
  }
  if ((*(byte *)(param_9 + 0x188) & 4) == 0) {
    uVar5 = zz_00055fc_();
    *(short *)(param_9 + 0x74) = (short)(uVar5 << 0xb);
  }
  else {
    *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_802dc582 + iVar7);
  }
  *(undefined2 *)(param_9 + 0x80) = 0;
  *(undefined2 *)(param_9 + 0x7e) = 0;
  *(undefined2 *)(param_9 + 0x7c) = 0;
  if ((*(byte *)(param_9 + 0x188) & 8) != 0) {
    *(undefined2 *)(param_9 + 0x7c) = *(undefined2 *)(&DAT_802dc57e + iVar7);
  }
  if ((*(byte *)(param_9 + 0x188) & 0x10) != 0) {
    *(undefined2 *)(param_9 + 0x7e) = *(undefined2 *)(&DAT_802dc580 + iVar7);
  }
  if ((*(byte *)(param_9 + 0x188) & 0x20) != 0) {
    *(undefined2 *)(param_9 + 0x80) = *(undefined2 *)(&DAT_802dc582 + iVar7);
  }
  zz_0018f88_((int *)(param_9 + 0x174),(int)(&PTR_DAT_802dc570)[iVar6 * 9],(float *)(param_9 + 0x58)
             );
  zz_0019338_((int *)(param_9 + 0x17c),(int)(&PTR_DAT_802dc574)[iVar6 * 9],
              (float *)(param_9 + 0x184));
  *(code **)(param_9 + 0x100) = FUN_80093640;
  uVar11 = zz_0089100_(param_9,1,1);
  zz_0006fb4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(int)(char)(&DAT_802dc560)[iVar7],param_12,param_13,param_14,
              param_15,param_16);
  zz_0007cac_((double)*(float *)(param_9 + 0x184),*(int *)(param_9 + 0xe0));
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



// ==== 800934d4  FUN_800934d4 ====

void FUN_800934d4(int param_1)

{
  if (*(char *)(param_1 + 0x12) == '\0') {
    *(float *)(param_1 + 0xd4) =
         *(float *)(param_1 + 0xd4) + *(float *)(*(int *)(param_1 + 0x90) + 0x768);
  }
  else {
    *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) + FLOAT_80437cc8;
  }
  if (*(float *)(param_1 + 0xd8) <= *(float *)(param_1 + 0xd4)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  if ((*(byte *)(param_1 + 0x188) & 8) != 0) {
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + *(short *)(param_1 + 0x7c);
  }
  if ((*(byte *)(param_1 + 0x188) & 0x10) != 0) {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x7e);
  }
  if ((*(byte *)(param_1 + 0x188) & 0x20) != 0) {
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) * *(short *)(param_1 + 0x80);
  }
  zz_0019178_((double)*(float *)(param_1 + 0xd4),(int *)(param_1 + 0x174),(float *)(param_1 + 0x58))
  ;
  zz_0019450_((double)*(float *)(param_1 + 0xd4),(int *)(param_1 + 0x17c),(float *)(param_1 + 0x184)
             );
  zz_0007cac_((double)*(float *)(param_1 + 0x184),*(int *)(param_1 + 0xe0));
  return;
}



// ==== 800935e0  FUN_800935e0 ====

void FUN_800935e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80093600  FUN_80093600 ====

void FUN_80093600(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),(uint)*(byte *)(param_9 + 0x189));
  return;
}



// ==== 80093640  FUN_80093640 ====

void FUN_80093640(int param_1)

{
  gnt4_PSMTXCopy_bl((float *)(param_1 + 0x144),(float *)(param_1 + 0x114));
  zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74));
  zz_00457d4_('x',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x70));
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x72));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  return;
}



// ==== 800936c0  FUN_800936c0 ====

void FUN_800936c0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,int param_13,int param_14,int param_15,
                 int param_16)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  char cVar5;
  undefined *puVar6;
  int *piVar7;
  undefined8 uVar8;
  
  if ((char)PTR_DAT_80433930[1] < '\x01') {
    param_10 = 0;
    PTR_DAT_80433930[1] = PTR_DAT_80433930[1] + '\x01';
    gnt4_memset(PTR_DAT_80433934,0,0x18b8);
  }
  iVar2 = (int)(char)*PTR_DAT_80433934;
  if (iVar2 == 3) {
    zz_0093a50_(0);
    zz_0093a50_(1);
    if ((*(char *)(DAT_804362d8 + 0x10c8) != '\0') || (*(char *)(iRam804362dc + 0x10c8) != '\0')) {
      *PTR_DAT_80433934 = *PTR_DAT_80433934 + '\x01';
      zz_0027aac_(0,0x20,1);
      zz_00e9b60_((double)FLOAT_80437cd0,2,0x20,2);
    }
  }
  else if (iVar2 < 3) {
    if (iVar2 != 1) {
      if (0 < iVar2) {
        iVar2 = zz_0027adc_();
        if (iVar2 == 0) {
          *PTR_DAT_80433934 = *PTR_DAT_80433934 + '\x01';
        }
        goto LAB_80093a38;
      }
      if (iVar2 < 0) goto LAB_80093a38;
      *PTR_DAT_80433934 = *PTR_DAT_80433934 + '\x01';
      zz_0197854_(4);
      uVar4 = 0;
      zz_0088398_(DAT_80436238 + 0xfe800,0x100000,0);
      zz_00059b8_();
      uVar8 = zz_000bb70_();
      uVar8 = zz_0044848_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1);
      zz_007fd6c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0094f5c_,0,uVar4,
                  param_12,param_13,param_14,param_15,param_16);
      uVar8 = set_global_menu_mode(8);
      param_1 = zz_0044bec_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,uVar4,
                            param_12,param_13,param_14,param_15,param_16);
    }
    iVar2 = zz_000a3c4_();
    puVar6 = PTR_DAT_80433934;
    if (iVar2 != 0) {
      return;
    }
    bVar1 = *PTR_DAT_80433934;
    *PTR_DAT_80433934 = bVar1 + 1;
    zz_0008a94_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                (uint)bVar1,puVar6,param_12,param_13,param_14,param_15,param_16);
    uVar8 = zz_0027aac_(0xe0e0e000,0x20,0);
    zz_00e99c8_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a084,
                param_12,param_13,param_14,param_15,param_16);
    piVar7 = &DAT_804362d8;
    puVar6 = &DAT_803cab60;
    iVar2 = 0;
    do {
      *piVar7 = (int)puVar6;
      gnt4_memset((void *)*piVar7,0,0x10dc);
      iVar2 = iVar2 + 1;
      puVar6 = puVar6 + 0x10dc;
      *(undefined1 *)(*piVar7 + 0x10c6) = 0xff;
      iVar3 = *piVar7;
      piVar7 = piVar7 + 1;
      *(undefined1 *)(iVar3 + 0x10c7) = 1;
    } while (iVar2 < 2);
    cVar5 = '\0';
    bVar1 = PTR_DAT_80433930[2];
    if (((((bVar1 & 1) == 0) && (cVar5 = '\x01', (bVar1 & 2) == 0)) &&
        (cVar5 = '\x02', (bVar1 & 4) == 0)) && (cVar5 = '\x03', (bVar1 & 8) == 0)) {
      cVar5 = '\x04';
    }
    if (cVar5 == '\x04') {
      cVar5 = '\0';
    }
    *(char *)(DAT_804362d8 + 0x10c6) = cVar5;
    *(int *)(DAT_804362d8 + 0x14) = DAT_80436238 + 0x2b2c00;
    *(int *)(iRam804362dc + 0x14) = DAT_80436238 + 0x2c6c00;
    *(int *)(DAT_804362d8 + 0x18) = *(int *)(DAT_804362d8 + 0x14) + 0xccb0;
    *(int *)(DAT_804362d8 + 0x1c) = *(int *)(DAT_804362d8 + 0x14) + 0x20c8;
    *(int *)(DAT_804362d8 + 0x20) = *(int *)(DAT_804362d8 + 0x14) + 0x13470;
    *(int *)(iRam804362dc + 0x18) = *(int *)(iRam804362dc + 0x14) + 0xccb0;
    *(int *)(iRam804362dc + 0x1c) = *(int *)(iRam804362dc + 0x14) + 0x20c8;
    *(int *)(iRam804362dc + 0x20) = *(int *)(iRam804362dc + 0x14) + 0x13470;
    zz_0094ec0_();
    FUN_801d9f00();
  }
  else if (iVar2 < 7) {
    if (4 < iVar2) {
      iVar2 = zz_0095f6c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2 + -5
                          ,param_10,PTR_DAT_80433934,param_12,param_13,param_14,param_15,param_16);
      if (iVar2 == 0) {
        return;
      }
      *PTR_DAT_80433934 = 3;
      return;
    }
    puVar6 = PTR_DAT_80433934;
    iVar2 = zz_0027adc_();
    if (iVar2 == 0) {
      zz_0094f5c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,param_10,puVar6,
                  param_12,param_13,param_14,param_15,param_16);
      zz_007fd5c_();
      *PTR_DAT_80433930 = 2;
      PTR_DAT_80433930[1] = 0;
      return;
    }
  }
LAB_80093a38:
  zz_0094e20_();
  return;
}



// ==== 80093a50  zz_0093a50_ ====

void zz_0093a50_(uint param_1)

{
  int iVar1;
  
  iVar1 = (&DAT_804362d8)[param_1];
  if ((*(char *)(iVar1 + 0x10c6) < '\0') ||
     (*(char *)((&DAT_804362d8)[param_1 ^ 1] + 0x10d7) != '\0')) {
    *(undefined4 *)(iVar1 + 8) = 0;
    *(undefined4 *)((&DAT_804362d8)[param_1] + 0xc) = 0;
    *(undefined4 *)((&DAT_804362d8)[param_1] + 0x10) = 0;
  }
  else {
    *(undefined4 *)(iVar1 + 8) = (&DAT_803c71fc)[*(char *)(iVar1 + 0x10c6) * 8];
    *(undefined4 *)((&DAT_804362d8)[param_1] + 0xc) =
         (&DAT_803c7204)[*(char *)((&DAT_804362d8)[param_1] + 0x10c6) * 8];
    iVar1 = (&DAT_804362d8)[param_1];
    *(uint *)(iVar1 + 0x10) =
         *(uint *)(iVar1 + 0xc) | (&DAT_803c720c)[*(char *)(iVar1 + 0x10c6) * 8];
  }
  if (((*(char *)(&DAT_804362d8)[param_1] < '\x04') && ('\x01' < *(char *)(&DAT_804362d8)[param_1]))
     && ((iVar1 = zz_008e340_(param_1), iVar1 != 1 || (iVar1 = zz_008e35c_(param_1), iVar1 != 1))))
  {
    *(undefined1 *)(&DAT_804362d8)[param_1] = 0;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 1) = 0;
  }
  (*(code *)(&PTR_FUN_802dc600)[*(char *)(&DAT_804362d8)[param_1]])(param_1);
  return;
}



// ==== 80093ba8  FUN_80093ba8 ====

void FUN_80093ba8(uint param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = (&DAT_804362d8)[param_1];
  cVar1 = *(char *)(iVar4 + 1);
  if (cVar1 == '\x01') {
LAB_80093c60:
    sVar2 = *(short *)((&DAT_804362d8)[param_1] + 4) + -1;
    *(short *)((&DAT_804362d8)[param_1] + 4) = sVar2;
    if (sVar2 < 1) {
      *(char *)((&DAT_804362d8)[param_1] + 1) = *(char *)((&DAT_804362d8)[param_1] + 1) + '\x01';
    }
    return;
  }
  if (cVar1 < '\x01') {
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(iVar4 + 1) = cVar1 + '\x01';
    *(undefined2 *)((&DAT_804362d8)[param_1] + 4) = 10;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10c9) = 0;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d0) = 0;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d1) = 0;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d3) = 0;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10ca) = 0;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cc) = 0;
    *(undefined2 *)((&DAT_804362d8)[param_1] + 0x40) = 0;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d4) = 1;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d5) = 0;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d6) = 0;
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d7) = 0;
    goto LAB_80093c60;
  }
  if ('\x02' < cVar1) {
    return;
  }
  if (param_1 == 0) {
    uVar3 = *(uint *)(iVar4 + 0xc);
    if ((uVar3 & 0x100) != 0) {
LAB_80093ca0:
      uVar3 = param_1 ^ 1;
      *(undefined1 *)(&DAT_804362d8)[param_1] = 1;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 1) = 0;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d7) = 1;
      *(undefined4 *)((&DAT_804362d8)[uVar3] + 0x10) = 0;
      *(undefined4 *)((&DAT_804362d8)[uVar3] + 0xc) = 0;
      *(undefined4 *)((&DAT_804362d8)[uVar3] + 8) = 0;
      zz_00f0468_(0,0x7a,param_1);
      return;
    }
  }
  else {
    uVar3 = param_1 ^ 1;
    if (*(char *)((&DAT_804362d8)[uVar3] + 0x10d7) != '\0') {
      return;
    }
    if (*(char *)((&DAT_804362d8)[uVar3] + 0x10c6) != '\0') {
      if ((DAT_803c7204 & 0x100) != 0) {
        *(undefined1 *)(iVar4 + 0x10c6) = 0;
        goto LAB_80093ca0;
      }
      if ((DAT_803c7204 & 0x200) != 0) goto LAB_80093d00;
    }
    if (*(char *)((&DAT_804362d8)[uVar3] + 0x10c6) != '\x01') {
      if ((DAT_803c7224 & 0x100) != 0) {
        *(undefined1 *)(iVar4 + 0x10c6) = 1;
        goto LAB_80093ca0;
      }
      if ((DAT_803c7224 & 0x200) != 0) goto LAB_80093d00;
    }
    if (*(char *)((&DAT_804362d8)[uVar3] + 0x10c6) != '\x02') {
      if ((DAT_803c7244 & 0x100) != 0) {
        *(undefined1 *)(iVar4 + 0x10c6) = 2;
        goto LAB_80093ca0;
      }
      if ((DAT_803c7244 & 0x200) != 0) goto LAB_80093d00;
    }
    if (*(char *)((&DAT_804362d8)[uVar3] + 0x10c6) == '\x03') {
      return;
    }
    uVar3 = DAT_803c7264;
    if ((DAT_803c7264 & 0x100) != 0) {
      *(undefined1 *)(iVar4 + 0x10c6) = 3;
      goto LAB_80093ca0;
    }
  }
  if ((uVar3 & 0x200) == 0) {
    return;
  }
LAB_80093d00:
  *(undefined1 *)(iVar4 + 0x10c8) = 1;
  zz_00f0468_(0,0x7b,param_1);
  return;
}



// ==== 80093e24  FUN_80093e24 ====

void FUN_80093e24(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9)

{
  char cVar1;
  int iVar2;
  undefined1 *puVar3;
  
  puVar3 = (undefined1 *)(&DAT_804362d8)[param_9];
  cVar1 = puVar3[1];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      *puVar3 = 2;
      *(undefined1 *)((&DAT_804362d8)[param_9] + 1) = 0;
      *(undefined2 *)((&DAT_804362d8)[param_9] + 0x40) = 9;
      *(undefined1 *)((&DAT_804362d8)[param_9] + 0x10d7) = 0;
      strcpy((char *)((&DAT_804362d8)[param_9] + 100),*(char **)((&DAT_804362d8)[param_9] + 0x20));
      *(undefined2 *)((&DAT_804362d8)[param_9] + 0x38) =
           *(undefined2 *)(*(int *)((&DAT_804362d8)[param_9] + 0x18) + 0x2172);
      *(undefined2 *)((&DAT_804362d8)[param_9] + 0x3a) =
           *(undefined2 *)(*(int *)((&DAT_804362d8)[param_9] + 0x1c) + 44000);
      *(undefined2 *)((&DAT_804362d8)[param_9] + 0x3c) =
           *(undefined2 *)(*(int *)((&DAT_804362d8)[param_9] + 0x1c) + 0xabe2);
      *(undefined2 *)((&DAT_804362d8)[param_9] + 0x28) = 0;
      *(undefined2 *)((&DAT_804362d8)[param_9] + 0x30) = 0;
      *(undefined2 *)((&DAT_804362d8)[param_9] + 0x2a) = 0;
      *(undefined2 *)((&DAT_804362d8)[param_9] + 0x32) = 0;
      *(undefined2 *)((&DAT_804362d8)[param_9] + 0x2c) = 0;
      *(undefined2 *)((&DAT_804362d8)[param_9] + 0x34) = 0;
      gnt4_memset((void *)((&DAT_804362d8)[param_9] + 0x48),0xff,0x1c);
      gnt4_memset((void *)((&DAT_804362d8)[param_9] + 0x42),0,6);
      gnt4_memset((void *)((&DAT_804362d8)[param_9] + 0x10bd),0,9);
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    puVar3[1] = cVar1 + '\x01';
    *(undefined1 *)((&DAT_804362d8)[param_9] + 0x10d6) = 0xff;
    *(undefined1 *)((&DAT_804362d8)[param_9] + 0x10d4) = 0;
    zz_01b1650_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                (int)*(char *)((&DAT_804362d8)[param_9] + 0x10c6));
  }
  iVar2 = zz_01b1758_();
  if (iVar2 != 1) {
    if ((iVar2 < 1) && (-1 < iVar2)) {
      *(char *)((&DAT_804362d8)[param_9] + 1) = *(char *)((&DAT_804362d8)[param_9] + 1) + '\x01';
    }
    else {
      *(undefined1 *)(&DAT_804362d8)[param_9] = 0;
      *(undefined1 *)((&DAT_804362d8)[param_9] + 1) = 0;
    }
  }
  return;
}



// ==== 80093fe0  FUN_80093fe0 ====

void FUN_80093fe0(int param_1)

{
  char cVar2;
  short sVar1;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  int iVar6;
  undefined1 *puVar7;
  int iVar8;
  int local_18;
  uint local_14;
  
  cVar2 = *(char *)((&DAT_804362d8)[param_1] + 0x10cf) + '\x01';
  *(char *)((&DAT_804362d8)[param_1] + 0x10cf) = cVar2;
  if ('w' < cVar2) {
    *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cf) = 0;
  }
  iVar3 = (&DAT_804362d8)[param_1];
  cVar2 = *(char *)(iVar3 + 1);
  if (cVar2 == '\x02') {
    sVar1 = *(short *)(iVar3 + 6) + 1;
    *(short *)(iVar3 + 6) = sVar1;
    if (7 < sVar1) {
      *(char *)((&DAT_804362d8)[param_1] + 1) = *(char *)((&DAT_804362d8)[param_1] + 1) + '\x01';
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10ca) =
           *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cb);
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cc) =
           *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cd);
      iVar3 = (&DAT_804362d8)[param_1];
      if (*(char *)(iVar3 + 3) == '\0') {
        *(undefined1 *)(iVar3 + 0x10c9) = 0;
        *(undefined2 *)((&DAT_804362d8)[param_1] + 0x40) = 0;
      }
      else {
        *(undefined1 *)(iVar3 + 0x10c9) = 1;
        *(undefined2 *)((&DAT_804362d8)[param_1] + 0x40) = 9;
      }
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d8) = 0;
      zz_0095408_(param_1);
      zz_00958c8_(param_1);
      zz_0095b94_(param_1);
    }
  }
  else {
    if (cVar2 < '\x02') {
      if (cVar2 == '\0') {
        *(undefined1 *)(iVar3 + 1) = 1;
        *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10c9) = 1;
        *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d4) = 0;
        zz_0095408_(param_1);
        zz_00958c8_(param_1);
      }
      else if (cVar2 < '\0') {
        return;
      }
      puVar7 = (undefined1 *)(&DAT_804362d8)[param_1];
      iVar8 = (int)(char)puVar7[0x10ca];
      iVar3 = iVar8 * 2;
      local_18 = (int)*(short *)(puVar7 + iVar3 + 0x28);
      local_14 = (uint)*(short *)(puVar7 + iVar3 + 0x30);
      uVar4 = *(uint *)(puVar7 + 0xc);
      iVar6 = (int)*(short *)(puVar7 + iVar3 + 0x38);
      if ((uVar4 & 0x1000) != 0) {
        if ((int)*(short *)(DAT_804362d8 + 0x42) + (int)*(short *)(iRam804362dc + 0x42) != 0) {
          *puVar7 = 3;
          *(undefined1 *)((&DAT_804362d8)[param_1] + 1) = 0;
          *(undefined2 *)((&DAT_804362d8)[param_1] + 6) = 0;
          zz_00f0468_(0,0x7a,param_1);
          return;
        }
        zz_00f0468_(0,0x7d,param_1);
        return;
      }
      if ((uVar4 & 0x100) != 0) {
        puVar7[0x10cf] = 0;
        if (((iVar6 != 0) && ((*(byte *)((&DAT_804362d8)[param_1] + local_14 + 0x1036) & 2) == 0))
           && (iVar3 = zz_00959b0_(param_1), -1 < iVar3)) {
          zz_0095b94_(param_1);
          zz_00f0468_(0,0x7a,param_1);
          return;
        }
        zz_00f0468_(0,0x7d,param_1);
        return;
      }
      if ((uVar4 & 0x200) != 0) {
        puVar7[1] = puVar7[1] + '\x01';
        *(undefined1 *)((&DAT_804362d8)[param_1] + 3) = 0;
        *(undefined2 *)((&DAT_804362d8)[param_1] + 6) = 0;
        *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cb) = 0;
        *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cd) = 0;
        zz_00f0468_(0,0x7b,param_1);
        return;
      }
      if ((uVar4 & 0x20) == 0) {
        if ((uVar4 & 0x40) == 0) {
          if ((uVar4 & 0x400) != 0) {
            puVar7[0x10cc] = puVar7[0x10cc] ^ 1;
            zz_00958c8_(param_1);
            zz_00f0468_(0,0x77,param_1);
            return;
          }
          if ((uVar4 & 0x800) != 0) {
            puVar7[0x10d8] = puVar7[0x10d8] ^ 1;
            zz_00f0468_(0,0x77,param_1);
            return;
          }
          if (iVar6 < 2) {
            return;
          }
          iVar6 = zz_017d3e0_(*(uint *)(puVar7 + 0x10),&local_18,&local_14,iVar6,
                              (int)*(short *)(puVar7 + 0x40));
          if (iVar6 == 0) {
            return;
          }
          *(short *)((&DAT_804362d8)[param_1] + iVar3 + 0x28) = (short)local_18;
          *(short *)((&DAT_804362d8)[param_1] + iVar3 + 0x30) = (short)local_14;
          *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cf) = 0;
          zz_00958c8_(param_1);
          zz_0095b94_(param_1);
          zz_00f0468_(0,0x77,param_1);
          return;
        }
        iVar8 = iVar8 + -1;
        if (iVar8 < 0) {
          iVar8 = 2;
        }
      }
      else {
        iVar8 = iVar8 + 1;
        if (2 < iVar8) {
          iVar8 = 0;
        }
      }
      puVar7[1] = puVar7[1] + '\x01';
      ((undefined1 *)(&DAT_804362d8)[param_1])[3] = *(undefined1 *)(&DAT_804362d8)[param_1];
      *(undefined2 *)((&DAT_804362d8)[param_1] + 6) = 0;
      *(char *)((&DAT_804362d8)[param_1] + 0x10cb) = (char)iVar8;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cd) =
           *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cc);
      zz_00f0468_(0,0x77,param_1);
      return;
    }
    if ('\x03' < cVar2) {
      return;
    }
    sVar1 = *(short *)(iVar3 + 6) + -1;
    *(short *)(iVar3 + 6) = sVar1;
    if (sVar1 < 1) {
      pcVar5 = (char *)(&DAT_804362d8)[param_1];
      if (pcVar5[3] == *pcVar5) {
        pcVar5[1] = '\x01';
      }
      else {
        *pcVar5 = '\0';
        *(undefined1 *)((&DAT_804362d8)[param_1] + 1) = 0;
      }
    }
  }
  uVar4 = *(short *)((&DAT_804362d8)[param_1] + 6) * 0xff;
  *(char *)((&DAT_804362d8)[param_1] + 0x10ce) =
       (char)((int)uVar4 >> 3) + ((int)uVar4 < 0 && (uVar4 & 7) != 0);
  return;
}



// ==== 80094454  FUN_80094454 ====

void FUN_80094454(uint param_1)

{
  char cVar1;
  short sVar2;
  short sVar3;
  undefined1 uVar4;
  undefined1 *puVar5;
  int iVar6;
  uint uVar7;
  short sVar8;
  
  puVar5 = (undefined1 *)(&DAT_804362d8)[param_1];
  switch(puVar5[1]) {
  case 0:
    sVar2 = *(short *)(puVar5 + 6);
    *(short *)(puVar5 + 6) = sVar2 + 1;
    if (7 < (short)(sVar2 + 1)) {
      *(char *)((&DAT_804362d8)[param_1] + 1) = *(char *)((&DAT_804362d8)[param_1] + 1) + '\x01';
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10ca) = 3;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10c9) = 2;
      *(undefined2 *)((&DAT_804362d8)[param_1] + 0x40) = 7;
      *(undefined2 *)((&DAT_804362d8)[param_1] + 0x2e) = 0;
      *(undefined2 *)((&DAT_804362d8)[param_1] + 0x36) = 0;
      *(undefined2 *)((&DAT_804362d8)[param_1] + 0x3e) =
           *(undefined2 *)((&DAT_804362d8)[param_1] + 0x42);
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d8) = 0;
      zz_00958c8_(param_1);
      gnt4_memset((void *)((&DAT_804362d8)[param_1] + 0x10bd),0,9);
    }
    goto LAB_80094530;
  case 1:
    sVar2 = *(short *)(puVar5 + 6);
    *(short *)(puVar5 + 6) = sVar2 + -1;
    if ((short)(sVar2 + -1) < 1) {
      *(char *)((&DAT_804362d8)[param_1] + 1) = *(char *)((&DAT_804362d8)[param_1] + 1) + '\x01';
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d0) = 1;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d5) = 1;
      zz_0094894_(param_1);
    }
LAB_80094530:
    uVar7 = *(short *)((&DAT_804362d8)[param_1] + 6) * 0xff;
    *(char *)((&DAT_804362d8)[param_1] + 0x10ce) =
         (char)((int)uVar7 >> 3) + ((int)uVar7 < 0 && (uVar7 & 7) != 0);
    return;
  case 2:
    puVar5[0x10d6] = 2;
    iVar6 = zz_0094894_(param_1);
    if (iVar6 != 0) {
      return;
    }
    if ((*(uint *)((&DAT_804362d8)[param_1] + 0xc) & 0x200) != 0) {
      zz_00948f4_(param_1);
      return;
    }
LAB_800945bc:
    iVar6 = (&DAT_804362d8)[param_1];
    if ((*(uint *)(iVar6 + 0xc) & 0x400) == 0) {
      sVar2 = *(short *)(iVar6 + 0x3e);
      sVar3 = *(short *)(iVar6 + 0x40);
      sVar8 = *(short *)(iVar6 + 0x2e);
      if ((int)sVar2 <= (int)sVar3) {
        return;
      }
      if ((*(uint *)(iVar6 + 0x10) & 0x40004) == 0) {
        if ((*(uint *)(iVar6 + 0x10) & 0x80008) == 0) {
          return;
        }
        if (sVar8 == 0) {
          sVar8 = sVar2 - sVar3;
        }
        else {
          sVar8 = sVar8 + -1;
        }
      }
      else if ((int)sVar8 + (int)sVar3 < (int)sVar2) {
        sVar8 = sVar8 + 1;
      }
      else {
        sVar8 = 0;
      }
      *(short *)(iVar6 + 0x2e) = sVar8;
    }
    else {
      *(byte *)(iVar6 + 0x10cc) = *(byte *)(iVar6 + 0x10cc) ^ 1;
    }
    zz_00958c8_(param_1);
    zz_00f0468_(0,0x77,param_1);
    return;
  case 3:
    sVar2 = *(short *)(puVar5 + 4);
    *(short *)(puVar5 + 4) = sVar2 + -1;
    if ((short)(sVar2 + -1) < 0) {
      *(char *)((&DAT_804362d8)[param_1] + 1) = *(char *)((&DAT_804362d8)[param_1] + 1) + '\x01';
      return;
    }
    return;
  case 4:
    if (*(char *)((&DAT_804362d8)[param_1 ^ 1] + 0x10d0) != '\0') {
      uVar7 = *(uint *)(puVar5 + 0xc);
      cVar1 = puVar5[0x10d1];
      if ((uVar7 & 0x100) == 0) {
        if ((uVar7 & 0x200) == 0) {
          if (((uVar7 & 0x20002) == 0) || (cVar1 != '\x01')) {
            if (((uVar7 & 0x10001) == 0) || (cVar1 != '\x02')) goto LAB_800945bc;
            uVar4 = 1;
          }
          else {
            uVar4 = 2;
          }
          puVar5[0x10d1] = uVar4;
          zz_00f0468_(0,0x77,param_1);
          return;
        }
      }
      else if (cVar1 == '\x01') {
        puVar5[1] = puVar5[1] + '\x01';
        *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d2) = 0x1e;
        zz_00f0468_(0,0x7a,param_1);
        return;
      }
      puVar5[0x10d0] = 0;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d1) = 0;
      zz_00948f4_(param_1);
      return;
    }
    break;
  case 5:
    if (*(char *)((&DAT_804362d8)[param_1 ^ 1] + 0x10d0) != '\0') {
      cVar1 = puVar5[0x10d2];
      puVar5[0x10d2] = cVar1 + -1;
      if ('\0' < (char)(cVar1 + -1)) {
        return;
      }
      *(char *)((&DAT_804362d8)[param_1] + 1) = *(char *)((&DAT_804362d8)[param_1] + 1) + '\x01';
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d2) = 4;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d3) = 1;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d6) = 4;
      return;
    }
    break;
  case 6:
    if ((*(uint *)(puVar5 + 0xc) & 0x200) != 0) {
      puVar5[1] = 4;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d2) = 0;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d3) = 0;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d6) = 3;
      zz_00f0468_(0,0x7b,param_1);
      return;
    }
    if (*(char *)((&DAT_804362d8)[param_1 ^ 1] + 0x10d0) != '\0') {
      if (*(char *)((&DAT_804362d8)[param_1 ^ 1] + 0x10d3) == '\0') {
        return;
      }
      *puVar5 = 4;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 1) = 0;
      *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d1) = 0;
      return;
    }
    break;
  default:
    goto switchD_800944a0_default;
  }
  puVar5[1] = 2;
  *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d6) = 2;
  *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d1) = 0;
  *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d3) = 0;
  *(undefined2 *)((&DAT_804362d8)[param_1] + 0x2e) = 0;
switchD_800944a0_default:
  return;
}



// ==== 80094894  zz_0094894_ ====

undefined4 zz_0094894_(uint param_1)

{
  if (*(char *)((&DAT_804362d8)[param_1 ^ 1] + 0x10d0) == '\0') {
    return 0;
  }
  *(undefined1 *)((&DAT_804362d8)[param_1] + 1) = 3;
  *(undefined2 *)((&DAT_804362d8)[param_1] + 4) = 10;
  *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d1) = 2;
  *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d2) = 0;
  return 1;
}



// ==== 800948f4  zz_00948f4_ ====

void zz_00948f4_(int param_1)

{
  *(undefined1 *)(&DAT_804362d8)[param_1] = 2;
  *(undefined1 *)((&DAT_804362d8)[param_1] + 1) = 2;
  *(undefined2 *)((&DAT_804362d8)[param_1] + 6) = 0;
  ((undefined1 *)(&DAT_804362d8)[param_1])[3] = *(undefined1 *)(&DAT_804362d8)[param_1];
  *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cb) = 0;
  *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10cd) = 0;
  *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d0) = 0;
  *(undefined1 *)((&DAT_804362d8)[param_1] + 0x10d5) = 0;
  zz_00f0468_(0,0x7b,param_1);
  return;
}



// ==== 80094974  FUN_80094974 ====

/* WARNING: Heritage AFTER dead removal. Example location: r0x804362d8 : 0x80094aac */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void FUN_80094974(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 uint param_9)

{
  uint uVar1;
  byte bVar4;
  short sVar3;
  int iVar2;
  undefined1 *puVar5;
  char cVar6;
  char cVar7;
  
  puVar5 = (&DAT_804362d8)[param_9];
  cVar6 = puVar5[1];
  switch(cVar6) {
  case '\0':
    if (param_9 == 0) {
      iVar2 = 0;
      PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | 0x80;
      do {
        zz_0095d4c_(iVar2);
        iVar2 = iVar2 + 1;
      } while (iVar2 < 2);
      bVar4 = zz_01cb7fc_((int *)&DAT_803cab00,(int *)&DAT_803cab30);
      if ((bVar4 & 5) == 5) {
        cVar6 = '\n';
      }
      else if ((bVar4 & 1) == 0) {
        if ((bVar4 & 4) == 0) {
          cVar6 = '\x06';
        }
        else {
          cVar6 = '\b';
        }
      }
      else {
        cVar6 = '\t';
      }
      if ((bVar4 & 10) == 10) {
        cVar7 = '\n';
      }
      else if ((bVar4 & 2) == 0) {
        if ((bVar4 & 8) == 0) {
          cVar7 = '\x06';
        }
        else {
          cVar7 = '\b';
        }
      }
      else {
        cVar7 = '\t';
      }
      if ((cVar6 == '\x06') && (cVar7 == '\x06')) {
        DAT_804362d8[1] = DAT_804362d8[1] + '\x01';
        *(undefined2 *)(DAT_804362d8 + 4) = 0;
        *(undefined2 *)(DAT_804362d8 + 6) = 0;
        zz_01cb8f0_((int *)&DAT_803cab00,(int *)&DAT_803cab30);
      }
      else {
        DAT_804362d8[1] = 10;
        if (cVar6 == '\x06') {
          cVar6 = '\v';
        }
        puRam804362dc[1] = 10;
        if (cVar7 == '\x06') {
          cVar7 = '\v';
        }
        PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] & 0x7f;
      }
      DAT_804362d8[0x10d6] = cVar6;
      DAT_804362d8[0x10d3] = 0;
      puRam804362dc[0x10d6] = cVar7;
      puRam804362dc[0x10d3] = 0;
    }
    break;
  case '\x01':
    puVar5[1] = cVar6 + '\x01';
    sVar3 = *(short *)((&DAT_804362d8)[param_9] + 6);
    uVar1 = (uint)*(short *)((&DAT_804362d8)[param_9] + 4);
    if (((sVar3 != 0) || (*(short *)((&DAT_804362d8)[uVar1] + 0x42) != 0)) &&
       ((sVar3 == 0 || (*(short *)((&DAT_804362d8)[uVar1 ^ 1] + 0x42) != 0)))) {
      zz_01b17bc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar1,
                  (int)(char)(&DAT_804362d8)[uVar1][0x10c6]);
      goto switchD_800949b8_caseD_2;
    }
    goto LAB_80094bdc;
  case '\x02':
switchD_800949b8_caseD_2:
    iVar2 = zz_01b18c8_();
    if (iVar2 == 1) {
      return;
    }
    if ((0 < iVar2) || (iVar2 < 0)) {
      DAT_804362d8[1] = 10;
      DAT_804362d8[0x10d6] = 0xb;
      puRam804362dc[1] = 10;
      puRam804362dc[0x10d6] = 0xb;
      PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] & 0x7f;
      return;
    }
LAB_80094bdc:
    sVar3 = *(short *)((&DAT_804362d8)[param_9] + 4) + 1;
    *(short *)((&DAT_804362d8)[param_9] + 4) = sVar3;
    if (sVar3 < 2) {
      (&DAT_804362d8)[param_9][1] = (&DAT_804362d8)[param_9][1] + -1;
    }
    else {
      sVar3 = *(short *)((&DAT_804362d8)[param_9] + 6) + 1;
      *(short *)((&DAT_804362d8)[param_9] + 6) = sVar3;
      if (sVar3 < 2) {
        (&DAT_804362d8)[param_9][1] = (&DAT_804362d8)[param_9][1] + -1;
        *(undefined2 *)((&DAT_804362d8)[param_9] + 4) = 0;
        zz_01cbba4_((int *)&DAT_803cab00,(int *)&DAT_803cab30);
      }
      else {
        (&DAT_804362d8)[param_9][1] = 3;
        *(undefined2 *)((&DAT_804362d8)[param_9] + 4) = 0;
        *(undefined2 *)((&DAT_804362d8)[param_9] + 6) = 0;
      }
    }
    break;
  case '\x03':
    iVar2 = zz_0095e5c_(param_9);
    if (iVar2 != 0) {
      *PTR_DAT_80433934 = (char)param_9 + '\x05';
      PTR_DAT_80433934[1] = 0;
      return;
    }
    goto LAB_80094cc8;
  case '\x04':
    puVar5[1] = cVar6 + '\x01';
    zz_01b17bc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                (int)(char)(&DAT_804362d8)[param_9][0x10c6]);
  case '\x05':
    iVar2 = zz_01b18c8_();
    if (iVar2 != 1) {
LAB_80094cc8:
      (&DAT_804362d8)[param_9][1] = 8;
      if (param_9 == 0) {
        puRam804362dc[1] = 3;
        *(undefined2 *)(puRam804362dc + 4) = 0;
        *(undefined2 *)(puRam804362dc + 6) = 0;
      }
    }
    break;
  case '\b':
    if ((&DAT_804362d8)[param_9 ^ 1][1] == '\b') {
      DAT_804362d8[1] = 9;
      DAT_804362d8[0x10d6] = 7;
      puRam804362dc[1] = 9;
      puRam804362dc[0x10d6] = 7;
      PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] & 0x7f;
    }
    break;
  case '\t':
    uVar1 = *(uint *)(puVar5 + 0xc);
    goto joined_r0x80094e08;
  case '\n':
    uVar1 = *(uint *)(puVar5 + 0xc);
joined_r0x80094e08:
    if ((uVar1 & 0x1300) != 0) {
      *DAT_804362d8 = 0;
      DAT_804362d8[1] = 0;
      DAT_804362d8[0x10d4] = 0;
      DAT_804362d8[0x10d5] = 0;
      *puRam804362dc = 0;
      puRam804362dc[1] = 0;
      puRam804362dc[0x10d4] = 0;
      puRam804362dc[0x10d5] = 0;
    }
  }
  return;
}



// ==== 80094e20  zz_0094e20_ ====

void zz_0094e20_(void)

{
  zz_0094e44_();
  zz_0094e78_();
  return;
}



// ==== 80094e44  zz_0094e44_ ====

void zz_0094e44_(void)

{
  zz_0089898_(0x39);
  zz_0089898_(0x38);
  zz_0089554_();
  zz_0089658_();
  return;
}



// ==== 80094e78  zz_0094e78_ ====

void zz_0094e78_(void)

{
  zz_008a16c_();
  zz_0089c00_(0x39);
  zz_0089c00_(0x38);
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  return;
}



// ==== 80094ec0  zz_0094ec0_ ====

void zz_0094ec0_(void)

{
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7380,(float *)&DAT_802dc65c,(float *)&DAT_802dc674,
                      (float *)&DAT_802dc668);
  *(undefined **)(PTR_DAT_80433930 + 0x14) = &DAT_803c7380;
  PTR_DAT_80433930[0xc] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x18) = &DAT_803c7380;
  PTR_DAT_80433930[0xd] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x1c) = &DAT_803c7380;
  PTR_DAT_80433930[0xe] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x20) = &DAT_803c7380;
  PTR_DAT_80433930[0xf] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x24) = &DAT_803c7380;
  PTR_DAT_80433930[0x10] = 0xff;
  return;
}



// ==== 80094f5c  zz_0094f5c_ ====

void zz_0094f5c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined8 uVar1;
  
  zz_0008b58_();
  uVar1 = zz_01978d0_();
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4_00
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,extraout_r4_01,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00f07c4_();
  return;
}



// ==== 80094f9c  FUN_80094f9c ====

void FUN_80094f9c(short *param_1,short *param_2)

{
  undefined4 uVar1;
  int iVar2;
  char *__s;
  undefined2 *puVar3;
  int *piVar4;
  undefined2 local_a8 [2];
  int local_a4 [2];
  char acStack_9c [64];
  char acStack_5c [72];
  
  piVar4 = local_a4;
  __s = acStack_9c;
  iVar2 = 0;
  local_a4[0] = DAT_804362d4 + *param_1 * 0x20 + 0x870;
  local_a4[1] = DAT_804362d4 + *param_2 * 0x20 + 0x870;
  do {
    puVar3 = (undefined2 *)*piVar4;
    local_a8[0] = *puVar3;
    uVar1 = zz_0066270_((char *)local_a8);
    sprintf(__s,s__s_d_3d_d_802b0d98,uVar1,6 - *(char *)(puVar3 + 1),
            100 - *(char *)((int)puVar3 + 3),*(undefined4 *)(puVar3 + 8));
    iVar2 = iVar2 + 1;
    __s = __s + 0x40;
    piVar4 = piVar4 + 1;
  } while (iVar2 < 2);
  gnt4_strcmp(acStack_9c,acStack_5c);
  return;
}



// ==== 80095064  zz_0095064_ ====

void zz_0095064_(int param_1)

{
  int iVar1;
  int iVar2;
  size_t __nmemb;
  int iVar3;
  short *psVar4;
  short sVar5;
  int iVar6;
  
  DAT_804362d4 = *(int *)((&DAT_804362d8)[param_1] + 0x18);
  __nmemb = (size_t)*(short *)(DAT_804362d4 + 0x2172);
  if (__nmemb != 0) {
    sVar5 = 0;
    psVar4 = (short *)(DAT_804362d4 + 0x870);
    iVar1 = 200;
    iVar6 = 0;
    iVar3 = 0;
    do {
      if ((int)__nmemb <= iVar6) break;
      if (-1 < *psVar4) {
        iVar2 = iVar3 + 0x84;
        iVar6 = iVar6 + 1;
        iVar3 = iVar3 + 2;
        *(short *)((&DAT_804362d8)[param_1] + iVar2) = sVar5;
      }
      sVar5 = sVar5 + 1;
      psVar4 = psVar4 + 0x10;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    qsort((void *)((&DAT_804362d8)[param_1] + 0x84),__nmemb,2,FUN_80094f9c);
  }
  return;
}



// ==== 8009510c  FUN_8009510c ====

void FUN_8009510c(short *param_1,short *param_2)

{
  undefined4 uVar1;
  int iVar2;
  char *__s;
  int *piVar3;
  undefined2 *puVar4;
  undefined2 local_a8 [2];
  int local_a4 [2];
  char acStack_9c [64];
  char acStack_5c [76];
  
  piVar3 = local_a4;
  __s = acStack_9c;
  iVar2 = 0;
  local_a4[0] = DAT_804362d0 + *param_1 * 0x10;
  local_a4[1] = DAT_804362d0 + *param_2 * 0x10;
  do {
    puVar4 = (undefined2 *)*piVar3;
    local_a8[0] = *puVar4;
    uVar1 = zz_0066270_((char *)local_a8);
    sprintf(__s,&DAT_80437cd4,uVar1,6 - *(char *)(puVar4 + 1),100 - *(char *)((int)puVar4 + 3));
    iVar2 = iVar2 + 1;
    __s = __s + 0x40;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 2);
  gnt4_strcmp(acStack_9c,acStack_5c);
  return;
}



// ==== 800951d8  zz_00951d8_ ====

void zz_00951d8_(int param_1)

{
  int iVar1;
  int iVar2;
  size_t __nmemb;
  short *psVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  
  psVar3 = *(short **)((&DAT_804362d8)[param_1] + 0x1c);
  __nmemb = (size_t)psVar3[22000];
  DAT_804362d0 = psVar3;
  if (__nmemb != 0) {
    sVar5 = 0;
    iVar1 = 2000;
    iVar6 = 0;
    iVar4 = 0;
    do {
      if ((int)__nmemb <= iVar6) break;
      if (-1 < *psVar3) {
        iVar2 = iVar4 + 0x84;
        iVar6 = iVar6 + 1;
        iVar4 = iVar4 + 2;
        *(short *)((&DAT_804362d8)[param_1] + iVar2) = sVar5;
      }
      sVar5 = sVar5 + 1;
      psVar3 = psVar3 + 8;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    qsort((void *)((&DAT_804362d8)[param_1] + 0x84),__nmemb,2,FUN_8009510c);
  }
  return;
}



// ==== 80095284  FUN_80095284 ====

int FUN_80095284(short *param_1,short *param_2)

{
  int iVar1;
  undefined2 *puVar2;
  int iVar3;
  uint *puVar4;
  int *piVar5;
  undefined2 local_28 [2];
  undefined2 local_24;
  int local_20 [4];
  
  piVar5 = local_20;
  puVar4 = (uint *)(local_20 + 2);
  iVar3 = 0;
  local_20[0] = DAT_804362d0 + *param_1 * 0xc + 32000;
  local_20[1] = DAT_804362d0 + *param_2 * 0xc + 32000;
  do {
    puVar2 = (undefined2 *)*piVar5;
    local_28[0] = *puVar2;
    local_24 = local_28[0];
    iVar1 = zz_00661d8_((char *)local_28);
    iVar3 = iVar3 + 1;
    piVar5 = piVar5 + 1;
    *puVar4 = (int)*(char *)(puVar2 + 1) | (6 - *(char *)((int)puVar2 + 3)) * 0x100 | iVar1 << 0x10;
    puVar4 = puVar4 + 1;
  } while (iVar3 < 2);
  return local_20[2] - local_20[3];
}



// ==== 80095358  zz_0095358_ ====

void zz_0095358_(int param_1)

{
  int iVar1;
  int iVar2;
  size_t __nmemb;
  int iVar3;
  short sVar4;
  int iVar5;
  short *psVar6;
  
  DAT_804362d0 = *(int *)((&DAT_804362d8)[param_1] + 0x1c);
  __nmemb = (size_t)*(short *)(DAT_804362d0 + 0xabe2);
  if (__nmemb != 0) {
    sVar4 = 0;
    iVar1 = 1000;
    iVar5 = 0;
    psVar6 = (short *)(*(int *)((&DAT_804362d8)[param_1] + 0x1c) + 32000);
    iVar3 = 0;
    do {
      if ((int)__nmemb <= iVar5) break;
      if (-1 < *psVar6) {
        iVar2 = iVar3 + 0x84;
        iVar5 = iVar5 + 1;
        iVar3 = iVar3 + 2;
        *(short *)((&DAT_804362d8)[param_1] + iVar2) = sVar4;
      }
      sVar4 = sVar4 + 1;
      psVar6 = psVar6 + 6;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    qsort((void *)((&DAT_804362d8)[param_1] + 0x84),__nmemb,2,FUN_80095284);
  }
  return;
}



// ==== 80095408  zz_0095408_ ====

void zz_0095408_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)((&DAT_804362d8)[param_1] + 0x10ca);
  if (cVar1 == '\x01') {
    zz_00951d8_(param_1);
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      zz_0095064_(param_1);
    }
  }
  else if (cVar1 < '\x03') {
    zz_0095358_(param_1);
  }
  return;
}



// ==== 80095470  zz_0095470_ ====

void zz_0095470_(int param_1,int param_2,int param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  short *psVar4;
  short local_18 [6];
  
  iVar3 = 0;
  psVar4 = (short *)(*(int *)((&DAT_804362d8)[param_1] + 0x18) + param_3 * 0x20 + 0x870);
  cVar2 = (char)*psVar4;
  if (((*psVar4 == 0x615) || (*psVar4 == 0x629)) || (*(int *)(psVar4 + 8) != 0)) {
    iVar3 = 1;
  }
  *(byte *)((&DAT_804362d8)[param_1] + param_2 + 0x1036) = (byte)(-iVar3 >> 0x1f) & 2;
  *(short *)((&DAT_804362d8)[param_1] + param_2 * 2 + 0x1024) = *psVar4;
  *(undefined1 *)((&DAT_804362d8)[param_1] + param_2 + 0x10ab) = *(undefined1 *)(psVar4 + 1);
  cVar1 = *(char *)((&DAT_804362d8)[param_1] + 0x10cc);
  if (cVar1 == '\x01') {
    local_18[0] = *psVar4;
    iVar3 = zz_00662c0_((char *)local_18,(int)*(char *)(psVar4 + 1));
    cVar2 = (char)iVar3;
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    cVar2 = *(char *)((int)psVar4 + 3) + '\x01';
  }
  *(char *)((&DAT_804362d8)[param_1] + param_2 + 0x10b4) = cVar2;
  return;
}



// ==== 80095588  zz_0095588_ ====

void zz_0095588_(int param_1,int param_2,int param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  short *psVar4;
  short local_18 [6];
  
  iVar3 = 0;
  psVar4 = (short *)(*(int *)((&DAT_804362d8)[param_1] + 0x1c) + param_3 * 0x10);
  cVar2 = (char)*psVar4;
  if ((*psVar4 == 0x615) || (*psVar4 == 0x629)) {
    iVar3 = 1;
  }
  *(byte *)((&DAT_804362d8)[param_1] + param_2 + 0x1036) = (byte)(-iVar3 >> 0x1f) & 2;
  *(short *)((&DAT_804362d8)[param_1] + param_2 * 2 + 0x1024) = *psVar4;
  *(undefined1 *)((&DAT_804362d8)[param_1] + param_2 + 0x10ab) = *(undefined1 *)(psVar4 + 1);
  cVar1 = *(char *)((&DAT_804362d8)[param_1] + 0x10cc);
  if (cVar1 == '\x01') {
    local_18[0] = *psVar4;
    iVar3 = zz_00662c0_((char *)local_18,(int)*(char *)(psVar4 + 1));
    cVar2 = (char)iVar3;
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    cVar2 = *(char *)((int)psVar4 + 3) + '\x01';
  }
  *(char *)((&DAT_804362d8)[param_1] + param_2 + 0x10b4) = cVar2;
  return;
}



// ==== 80095690  zz_0095690_ ====

void zz_0095690_(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 unaff_r23;
  uint uVar5;
  int iVar6;
  undefined2 *puVar7;
  int iVar8;
  undefined2 local_48 [2];
  undefined2 local_44 [2];
  undefined2 local_40;
  
  iVar8 = param_2 * 0xc;
  iVar4 = *(int *)((&DAT_804362d8)[param_1] + 0x1c);
  *(undefined1 *)((&DAT_804362d8)[param_1] + param_2 + 0x1036) = 1;
  puVar7 = (undefined2 *)(iVar4 + param_3 * 0xc + 32000);
  *(undefined2 *)((&DAT_804362d8)[param_1] + param_2 * 2 + 0x1024) = *puVar7;
  strcpy((char *)((&DAT_804362d8)[param_1] + iVar8 + 0x103f),
         (&PTR_DAT_80390a28)[*(char *)((int)puVar7 + 3)]);
  local_44[0] = *puVar7;
  uVar5 = 100;
  local_40 = local_44[0];
  iVar4 = zz_00661d8_((char *)local_44);
  iVar6 = 0;
  do {
    iVar3 = (iVar4 + 1) / (int)uVar5;
    iVar2 = iVar3 / 10 + (iVar3 >> 0x1f);
    zz_0238c90_((&DAT_804362d8)[param_1] + iVar8 + 0x103f,
                (int)(&PTR_DAT_80390a40)[iVar3 + (iVar2 - (iVar2 >> 0x1f)) * -10]);
    iVar6 = iVar6 + 1;
    uVar5 = uVar5 / 10;
  } while (iVar6 < 3);
  zz_0238c90_((&DAT_804362d8)[param_1] + iVar8 + 0x103f,
              (int)(&PTR_DAT_80390a68)[*(char *)(puVar7 + 1)]);
  *(undefined1 *)((&DAT_804362d8)[param_1] + param_2 + 0x10ab) = *(undefined1 *)((int)puVar7 + 3);
  cVar1 = *(char *)((&DAT_804362d8)[param_1] + 0x10cc);
  if (cVar1 == '\x01') {
    local_48[0] = local_40;
    iVar4 = zz_00662c0_((char *)local_48,(int)*(char *)((int)puVar7 + 3));
    unaff_r23 = (undefined1)iVar4;
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    unaff_r23 = 0xff;
  }
  *(undefined1 *)((&DAT_804362d8)[param_1] + param_2 + 0x10b4) = unaff_r23;
  return;
}



// ==== 8009582c  zz_009582c_ ====

void zz_009582c_(int param_1,int param_2)

{
  short sVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  
  psVar2 = (short *)((&DAT_804362d8)[param_1] + 0x48);
  iVar4 = 7;
  iVar3 = param_2;
  while ((sVar1 = *psVar2, sVar1 < 0 || (iVar3 = iVar3 + -1, -1 < iVar3))) {
    psVar2 = psVar2 + 2;
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      return;
    }
  }
  if (sVar1 == 1) {
    zz_0095588_(param_1,param_2,(int)psVar2[1]);
    return;
  }
  if (0 < sVar1) {
    if (2 < sVar1) {
      return;
    }
    zz_0095690_(param_1,param_2,(int)psVar2[1]);
    return;
  }
  if (sVar1 < 0) {
    return;
  }
  zz_0095470_(param_1,param_2,(int)psVar2[1]);
  return;
}



// ==== 800958c8  zz_00958c8_ ====

void zz_00958c8_(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  iVar5 = (int)*(char *)((&DAT_804362d8)[param_1] + 0x10ca);
  iVar2 = (&DAT_804362d8)[param_1] + iVar5 * 2;
  iVar4 = (int)*(short *)(iVar2 + 0x28);
  sVar1 = *(short *)(iVar2 + 0x38);
  iVar2 = iVar4 << 1;
  for (; (iVar6 < *(short *)((&DAT_804362d8)[param_1] + 0x40) && (iVar4 < sVar1)); iVar4 = iVar4 + 1
      ) {
    iVar3 = (int)*(short *)((&DAT_804362d8)[param_1] + iVar2 + 0x84);
    if (iVar5 == 2) {
      zz_0095690_(param_1,iVar6,iVar3);
    }
    else if (iVar5 < 2) {
      if (iVar5 == 0) {
        zz_0095470_(param_1,iVar6,iVar3);
      }
      else if (-1 < iVar5) {
        zz_0095588_(param_1,iVar6,iVar3);
      }
    }
    else if (iVar5 < 4) {
      zz_009582c_(param_1,iVar6);
    }
    iVar6 = iVar6 + 1;
    iVar2 = iVar2 + 2;
  }
  return;
}



// ==== 800959b0  zz_00959b0_ ====

undefined4 zz_00959b0_(int param_1)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  short *psVar6;
  uint uVar7;
  
  iVar4 = (&DAT_804362d8)[param_1];
  bVar2 = false;
  psVar5 = (short *)(iVar4 + 0x48);
  uVar7 = (uint)*(char *)(iVar4 + 0x10ca);
  iVar3 = iVar4 + uVar7 * 2;
  sVar1 = *(short *)(iVar4 + ((int)*(short *)(iVar3 + 0x28) + (int)*(short *)(iVar3 + 0x30)) * 2 +
                    0x84);
  if (((int)*(short *)(iVar4 + 0x48) == uVar7) && (*(short *)(iVar4 + 0x4a) == sVar1)) {
    bVar2 = true;
    psVar6 = psVar5;
  }
  else {
    psVar6 = (short *)(iVar4 + 0x4c);
    if (((int)*psVar6 == uVar7) && (*(short *)(iVar4 + 0x4e) == sVar1)) {
      bVar2 = true;
    }
    else {
      psVar6 = (short *)(iVar4 + 0x50);
      if (((int)*psVar6 == uVar7) && (*(short *)(iVar4 + 0x52) == sVar1)) {
        bVar2 = true;
      }
      else {
        psVar6 = (short *)(iVar4 + 0x54);
        if (((int)*psVar6 == uVar7) && (*(short *)(iVar4 + 0x56) == sVar1)) {
          bVar2 = true;
        }
        else {
          psVar6 = (short *)(iVar4 + 0x58);
          if (((int)*psVar6 == uVar7) && (*(short *)(iVar4 + 0x5a) == sVar1)) {
            bVar2 = true;
          }
          else {
            psVar6 = (short *)(iVar4 + 0x5c);
            if (((int)*psVar6 == uVar7) && (*(short *)(iVar4 + 0x5e) == sVar1)) {
              bVar2 = true;
            }
            else {
              psVar6 = (short *)(iVar4 + 0x60);
              if (((int)*psVar6 == uVar7) && (*(short *)(iVar4 + 0x62) == sVar1)) {
                bVar2 = true;
              }
              else {
                psVar6 = (short *)(iVar4 + 100);
              }
            }
          }
        }
      }
    }
  }
  if (bVar2) {
    *psVar6 = -1;
  }
  else {
    if (6 < *(short *)(iVar4 + 0x42)) {
      return 0xffffffff;
    }
    iVar3 = 7;
    do {
      if (*psVar5 < 0) {
        *psVar5 = (short)*(char *)(iVar4 + 0x10ca);
        psVar5[1] = sVar1;
        break;
      }
      psVar5 = psVar5 + 2;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  iVar3 = 2 - ((uint)(uVar7 < 2) - ((int)uVar7 >> 0x1f));
  if (bVar2) {
    iVar3 = (&DAT_804362d8)[param_1] + iVar3 * 2;
    *(short *)(iVar3 + 0x42) = *(short *)(iVar3 + 0x42) + -1;
  }
  else {
    iVar3 = (&DAT_804362d8)[param_1] + iVar3 * 2;
    *(short *)(iVar3 + 0x42) = *(short *)(iVar3 + 0x42) + 1;
  }
  iVar3 = (&DAT_804362d8)[param_1];
  *(short *)(iVar3 + 0x42) = *(short *)(iVar3 + 0x44) + *(short *)(iVar3 + 0x46);
  return 0;
}



// ==== 80095b94  zz_0095b94_ ====

void zz_0095b94_(int param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = (int)*(char *)((&DAT_804362d8)[param_1] + 0x10ca);
  gnt4_memset((void *)((&DAT_804362d8)[param_1] + 0x10bd),0,9);
  iVar5 = 0;
  iVar3 = (&DAT_804362d8)[param_1] + iVar7 * 2;
  iVar6 = (int)*(short *)(iVar3 + 0x28);
  sVar1 = *(short *)(iVar3 + 0x38);
  iVar3 = iVar6 << 1;
  iVar8 = 9;
  do {
    if (sVar1 <= iVar6) {
      return;
    }
    iVar4 = (&DAT_804362d8)[param_1];
    sVar2 = *(short *)(iVar4 + iVar3 + 0x84);
    if ((*(short *)(iVar4 + 0x48) == iVar7) && (*(short *)(iVar4 + 0x4a) == sVar2)) {
      *(undefined1 *)(iVar4 + iVar5 + 0x10bd) = 1;
    }
    else if ((*(short *)(iVar4 + 0x4c) == iVar7) && (*(short *)(iVar4 + 0x4e) == sVar2)) {
      *(undefined1 *)(iVar4 + iVar5 + 0x10bd) = 1;
    }
    else if ((*(short *)(iVar4 + 0x50) == iVar7) && (*(short *)(iVar4 + 0x52) == sVar2)) {
      *(undefined1 *)(iVar4 + iVar5 + 0x10bd) = 1;
    }
    else if ((*(short *)(iVar4 + 0x54) == iVar7) && (*(short *)(iVar4 + 0x56) == sVar2)) {
      *(undefined1 *)(iVar4 + iVar5 + 0x10bd) = 1;
    }
    else if ((*(short *)(iVar4 + 0x58) == iVar7) && (*(short *)(iVar4 + 0x5a) == sVar2)) {
      *(undefined1 *)(iVar4 + iVar5 + 0x10bd) = 1;
    }
    else if ((*(short *)(iVar4 + 0x5c) == iVar7) && (*(short *)(iVar4 + 0x5e) == sVar2)) {
      *(undefined1 *)(iVar4 + iVar5 + 0x10bd) = 1;
    }
    else if ((*(short *)(iVar4 + 0x60) == iVar7) && (*(short *)(iVar4 + 0x62) == sVar2)) {
      *(undefined1 *)(iVar4 + iVar5 + 0x10bd) = 1;
    }
    iVar5 = iVar5 + 1;
    iVar3 = iVar3 + 2;
    iVar6 = iVar6 + 1;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  return;
}



// ==== 80095d4c  zz_0095d4c_ ====

void zz_0095d4c_(int param_1)

{
  short sVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  
  iVar3 = param_1 * 0x30;
  gnt4_memset(&DAT_803cab00 + iVar3,0,0x30);
  iVar4 = (&DAT_804362d8)[param_1];
  psVar5 = (short *)(&DAT_803cab14 + iVar3);
  *(undefined4 *)(&DAT_803cab00 + iVar3) = *(undefined4 *)(iVar4 + 0x18);
  psVar2 = (short *)(iVar4 + 0x48);
  *(undefined4 *)(&DAT_803cab04 + iVar3) = *(undefined4 *)(iVar4 + 0x1c);
  *(undefined4 *)(&DAT_803cab08 + iVar3) = *(undefined4 *)(iVar4 + 0x20);
  *(int *)(&DAT_803cab0c + iVar3) = param_1 * 0x70 + -0x7fc355e0;
  iVar4 = 7;
  do {
    if (-1 < *psVar2) {
      *psVar5 = *psVar2;
      psVar5[1] = psVar2[1];
      sVar1 = *psVar5;
      if (sVar1 == 1) {
        (&DAT_803cab11)[iVar3] = (&DAT_803cab11)[iVar3] + '\x01';
      }
      else if (sVar1 < 1) {
        if (-1 < sVar1) {
          (&DAT_803cab10)[iVar3] = (&DAT_803cab10)[iVar3] + '\x01';
        }
      }
      else if (sVar1 < 3) {
        (&DAT_803cab12)[iVar3] = (&DAT_803cab12)[iVar3] + '\x01';
      }
      psVar5 = psVar5 + 2;
    }
    psVar2 = psVar2 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}



// ==== 80095e5c  zz_0095e5c_ ====

undefined4 zz_0095e5c_(int param_1)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  short sVar5;
  int iVar6;
  
  if ((*(short *)(*(int *)((&DAT_804362d8)[param_1] + 0x18) + 0x2172) < 200) ||
     (*(short *)(*(int *)((&DAT_804362d8)[param_1] + 0x1c) + 44000) < 2000)) {
    do {
      while( true ) {
        iVar6 = (&DAT_804362d8)[param_1];
        sVar5 = *(short *)(iVar6 + 4);
        sVar1 = (&DAT_8035b2dc)[sVar5 * 8];
        if (sVar1 < 0) goto LAB_80095e9c;
        sVar2 = (&DAT_8035b2de)[sVar5 * 8];
        if (1 < sVar2) break;
        *(short *)(iVar6 + 4) = sVar5 + 1;
      }
      uVar4 = zz_01cee38_(*(int *)(iVar6 + 0x1c),(int)sVar1,(int)*(short *)(iVar6 + 6));
      *(short *)((&DAT_804362d8)[param_1] + 0x24) = sVar1;
      *(char *)((&DAT_804362d8)[param_1] + 0x26) =
           (char)*(undefined2 *)((&DAT_804362d8)[param_1] + 6);
      *(byte *)((&DAT_804362d8)[param_1] + 0x27) = (byte)sVar2 | 0x10;
      sVar5 = *(short *)((&DAT_804362d8)[param_1] + 6) + 1;
      *(short *)((&DAT_804362d8)[param_1] + 6) = sVar5;
      if (5 < sVar5) {
        *(short *)((&DAT_804362d8)[param_1] + 4) = *(short *)((&DAT_804362d8)[param_1] + 4) + 1;
        *(undefined2 *)((&DAT_804362d8)[param_1] + 6) = 0;
      }
    } while (uVar4 == 0);
    uVar3 = 1;
  }
  else {
LAB_80095e9c:
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 80095f6c  zz_0095f6c_ ====

undefined4
zz_0095f6c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
           double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
           undefined *param_11,undefined4 param_12,int param_13,int param_14,int param_15,
           int param_16)

{
  char cVar1;
  undefined4 extraout_r4;
  int iVar2;
  undefined8 uVar3;
  
  cVar1 = PTR_DAT_80433934[1];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return 0;
      }
      goto LAB_8009601c;
    }
    if (cVar1 < '\0') {
      return 0;
    }
    PTR_DAT_80433934[1] = cVar1 + '\x01';
    set_global_menu_mode(0);
    param_1 = zz_0027aac_(0,4,0);
  }
  param_12 = 1;
  PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
  iVar2 = (&DAT_804362d8)[param_9];
  param_13 = (int)*(char *)(iVar2 + 0x10c6);
  param_15 = (int)*(char *)(iVar2 + 0x26);
  param_16 = (int)*(char *)(iVar2 + 0x27);
  param_11 = *(undefined **)(iVar2 + 0x18);
  param_14 = (int)*(short *)(iVar2 + 0x24);
  param_1 = zz_01ce174_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(undefined4 *)(iVar2 + 0x20),*(undefined4 *)(iVar2 + 0x1c),param_11,1,
                        *(char *)(iVar2 + 0x10c6),param_14,param_15,*(char *)(iVar2 + 0x27));
LAB_8009601c:
  iVar2 = zz_01ce444_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  if (iVar2 != 0) {
    zz_01cebe0_();
    iVar2 = zz_0095e5c_(param_9);
    if (iVar2 == 0) {
      uVar3 = set_global_menu_mode(8);
      zz_0008a94_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                  extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
      zz_0094ec0_();
      *(undefined1 *)((&DAT_804362d8)[param_9] + 1) = 4;
      return 1;
    }
    PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + -1;
  }
  return 0;
}



// ==== 800960a0  zz_00960a0_ ====

void zz_00960a0_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x102) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,4), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_80096194;
    *(code **)(puVar1 + 0x10c) = FUN_80096460;
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



// ==== 80096194  FUN_80096194 ====

void FUN_80096194(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802dc680)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800961e8  FUN_800961e8 ====

void FUN_800961e8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80437ce0;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(undefined2 *)(param_9 + 0x144) = 0;
  *(undefined2 *)(param_9 + 0x146) = 0;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),8,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),9,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  uVar2 = 8;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe8),8,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe8)
              ,extraout_r4,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  uVar5 = zz_0007cac_((double)FLOAT_80437ce4,*(int *)(param_9 + 0xe8));
  iVar3 = iVar4 + 0xc28;
  uVar2 = 9;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xec),9,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80437ce4,*(int *)(param_9 + 0xec));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_009630c_(param_9);
  return;
}



// ==== 8009630c  zz_009630c_ ====

void zz_009630c_(int param_1)

{
  float fVar1;
  double dVar2;
  undefined8 local_18;
  undefined8 local_10;
  
  fVar1 = FLOAT_80437ce8;
  *(undefined1 *)(param_1 + 0x89) = 7;
  *(float *)(param_1 + 100) = fVar1;
  *(float *)(param_1 + 0x68) = fVar1;
  *(float *)(param_1 + 0x6c) = fVar1;
  dVar2 = DOUBLE_80437d00;
  fVar1 = FLOAT_80437cf8;
  if (*(char *)(*(int *)(param_1 + 0x90) + 0x6f5) < '\x01') {
    *(short *)(param_1 + 0x146) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x146) ^ 0x80000000) -
                             DOUBLE_80437d00) * FLOAT_80437cfc);
  }
  else {
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x146)) ^ 0x80000000);
    *(short *)(param_1 + 0x146) = (short)(int)((local_18 - DOUBLE_80437d00) + DOUBLE_80437cf0);
    if ((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x146) ^ 0x80000000) - dVar2)
        < fVar1) {
      *(undefined2 *)(param_1 + 0x146) = 0xf1c8;
    }
  }
  local_10 = (double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x144) ^ 0x80000000);
  *(short *)(param_1 + 0x144) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x146) ^ 0x80000000) -
                           DOUBLE_80437d00) * *(float *)(*(int *)(param_1 + 0x90) + 0x1dc8) +
                   (float)(local_10 - DOUBLE_80437d00));
  return;
}



// ==== 80096440  FUN_80096440 ====

void FUN_80096440(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80096460  FUN_80096460 ====

void FUN_80096460(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  float afStack_78 [12];
  float afStack_48 [3];
  float local_3c;
  float local_2c;
  float local_1c;
  undefined4 local_18;
  uint uStack_14;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar1 = 0;
    uVar3 = 1;
  }
  else {
    iVar1 = 2;
    uVar3 = 0x44;
  }
  iVar4 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar4,uVar3);
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_9 + 0x144) ^ 0x80000000;
  iVar1 = *(int *)(param_9 + iVar1 * 4 + 0xe4);
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80437d08 *
                              (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80437d00)),
                      afStack_48,0x78);
  dVar6 = (double)FLOAT_80437d0c;
  pfVar2 = afStack_78;
  local_3c = FLOAT_80437d0c;
  local_2c = FLOAT_80437d10;
  local_1c = FLOAT_80437ce8;
  uVar5 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_48,pfVar2);
  zz_00076d0_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,afStack_78,
              (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar3);
  return;
}



// ==== 80096570  zz_0096570_ ====

void zz_0096570_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x104) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,4), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_80096664;
    *(code **)(puVar1 + 0x10c) = FUN_80096b3c;
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



// ==== 80096664  FUN_80096664 ====

void FUN_80096664(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802dc6b4)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800966b8  FUN_800966b8 ====

void FUN_800966b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  fVar1 = FLOAT_80437d18;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(undefined1 *)(param_9 + 0x11) = 0xff;
  *(undefined1 *)(param_9 + 0x13) = 0xff;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 400) = fVar1;
  *(float *)(param_9 + 0x18c) = fVar1;
  *(float *)(param_9 + 0x194) = fVar1;
  iVar4 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5b;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),9,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),10,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  uVar2 = 9;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe8),9,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe8)
              ,extraout_r4,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  uVar5 = zz_0007cac_((double)FLOAT_80437d1c,*(int *)(param_9 + 0xe8));
  iVar3 = iVar4 + 0xc28;
  uVar2 = 10;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xec),10,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80437d1c,*(int *)(param_9 + 0xec));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00967e0_(param_9);
  return;
}



// ==== 800967e0  zz_00967e0_ ====

void zz_00967e0_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined4 uVar6;
  
  if (*(char *)(param_1 + 0x13) != *(char *)(*(int *)(param_1 + 0x90) + 0x6e9)) {
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = *(undefined1 *)(param_1 + 0x13);
    *(undefined1 *)(param_1 + 0x13) = *(undefined1 *)(*(int *)(param_1 + 0x90) + 0x6e9);
  }
  fVar3 = FLOAT_80437d28;
  fVar2 = FLOAT_80437d18;
  cVar1 = *(char *)(param_1 + 0x13);
  if (cVar1 == '\x01') {
    *(float *)(param_1 + 0x18c) = *(float *)(param_1 + 0x18c) - FLOAT_80437d20;
    if (*(float *)(param_1 + 0x18c) <= fVar2) {
      *(float *)(param_1 + 0x18c) = fVar2;
      *(undefined1 *)(param_1 + 0x11) = 0xff;
    }
    goto LAB_80096a1c;
  }
  if ('\0' < cVar1) {
    if (cVar1 < '\x03') {
      if (*(char *)(param_1 + 0x19) == '\0') {
        if (*(char *)(param_1 + 0x11) == '\x01') {
          *(undefined1 *)(param_1 + 0x19) = 1;
        }
        else {
          if (*(char *)(param_1 + 0x11) == '\0') {
            *(float *)(param_1 + 0x18c) = *(float *)(param_1 + 0x18c) - FLOAT_80437d20;
            if (fVar2 < *(float *)(param_1 + 0x18c)) goto LAB_80096a1c;
            *(float *)(param_1 + 0x18c) = fVar2;
          }
          fVar4 = FLOAT_80437d38;
          fVar3 = FLOAT_80437d24;
          *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
          fVar2 = FLOAT_80437d18;
          *(float *)(param_1 + 400) = fVar3;
          *(float *)(param_1 + 0x194) = fVar4;
          *(float *)(param_1 + 0x48) = fVar2;
          *(float *)(param_1 + 0x50) = fVar2;
          zz_00f036c_(param_1,0xc0);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x11) = 1;
        fVar2 = FLOAT_80437d18;
        if (fVar3 < *(float *)(param_1 + 0x18c)) {
          *(float *)(param_1 + 400) = FLOAT_80437d2c;
          fVar3 = FLOAT_80437d3c;
          *(float *)(param_1 + 0x48) = fVar2;
          *(float *)(param_1 + 0x50) = fVar3;
        }
        *(float *)(param_1 + 0x18c) =
             (float)(DOUBLE_80437d30 *
                     (double)(float)((double)*(float *)(param_1 + 400) -
                                    (double)*(float *)(param_1 + 0x18c)) +
                    (double)*(float *)(param_1 + 0x18c));
      }
    }
    goto LAB_80096a1c;
  }
  if (cVar1 < '\0') goto LAB_80096a1c;
  if (*(char *)(param_1 + 0x19) == '\0') {
    if (*(char *)(param_1 + 0x11) == '\0') {
      *(undefined1 *)(param_1 + 0x19) = 1;
    }
    else {
      if (*(char *)(param_1 + 0x11) == '\x01') {
        *(float *)(param_1 + 0x18c) = *(float *)(param_1 + 0x18c) - FLOAT_80437d20;
        if (fVar2 < *(float *)(param_1 + 0x18c)) goto LAB_80096904;
        *(float *)(param_1 + 0x18c) = fVar2;
      }
      fVar2 = FLOAT_80437d24;
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(float *)(param_1 + 400) = fVar2;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x11) = 0;
    if (fVar3 < *(float *)(param_1 + 0x18c)) {
      *(float *)(param_1 + 400) = FLOAT_80437d2c;
    }
    *(float *)(param_1 + 0x18c) =
         (float)(DOUBLE_80437d30 *
                 (double)(float)((double)*(float *)(param_1 + 400) -
                                (double)*(float *)(param_1 + 0x18c)) +
                (double)*(float *)(param_1 + 0x18c));
  }
LAB_80096904:
  *(float *)(param_1 + 0x194) = FLOAT_80437d18;
LAB_80096a1c:
  fVar2 = FLOAT_80437d18;
  if (-1 < *(char *)(param_1 + 0x11)) {
    *(undefined *)(param_1 + 0x89) = (&DAT_80433980)[*(char *)(param_1 + 0x11)];
    iVar5 = *(char *)(param_1 + 0x11) * 0xc;
    uVar6 = *(undefined4 *)(&DAT_802dc694 + iVar5);
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802dc690 + iVar5);
    *(undefined4 *)(param_1 + 0x68) = uVar6;
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802dc698 + iVar5);
    iVar5 = *(char *)(param_1 + 0x11) * 6;
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(&DAT_802dc6a8 + iVar5);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_802dc6ac + iVar5);
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + *(float *)(param_1 + 0x50);
    *(float *)(param_1 + 0x194) = *(float *)(param_1 + 0x194) + *(float *)(param_1 + 0x48);
    if (*(float *)(param_1 + 0x194) < fVar2) {
      *(float *)(param_1 + 0x194) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x50) = fVar2;
      zz_00f036c_(param_1,0xc3);
    }
    *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) + *(float *)(param_1 + 0x194);
  }
  uVar6 = *(undefined4 *)(param_1 + 0x18c);
  *(undefined4 *)(param_1 + 0x60) = uVar6;
  *(undefined4 *)(param_1 + 0x5c) = uVar6;
  *(undefined4 *)(param_1 + 0x58) = uVar6;
  return;
}



// ==== 80096b1c  FUN_80096b1c ====

void FUN_80096b1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80096b3c  FUN_80096b3c ====

void FUN_80096b3c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  uint uVar3;
  
  if (-1 < *(char *)(param_9 + 0x11)) {
    puVar2 = *(undefined **)(param_9 + 0x90);
    iVar1 = (int)*(char *)(param_9 + 0x11);
    uVar3 = 1;
    if ((puVar2[0xae] != '\0') || (puVar2[0x3ec] == '\x04')) {
      uVar3 = 0x44;
      iVar1 = iVar1 + 2;
    }
    iVar1 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                (float *)(param_9 + 0x114),puVar2,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar1,uVar3);
  }
  return;
}



// ==== 80096bc4  zz_0096bc4_ ====

void zz_0096bc4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar4;
  
  DAT_80436328 = 0;
  DAT_8043631c = 0;
  DAT_80436318 = 0;
  DAT_80436314 = 0;
  zz_0096d0c_((double)FLOAT_80437d80);
  zz_0096d14_((double)FLOAT_80437d84);
  uVar4 = zz_0096d24_((double)FLOAT_80437d80);
  DAT_80436320 = param_10 + 0x2000;
  iVar2 = param_9 + 0x800;
  DAT_804362f8 = param_9 + 0x808;
  DAT_804362fc = (int *)(param_9 + (*(int *)(param_9 + 4) + 1) * 0x800);
  DAT_804362e8 = *(undefined4 *)(param_9 + 0x804);
  piVar3 = (int *)(iVar2 + *(int *)(param_9 + 0x800));
  DAT_804362e4 = 0;
  iVar1 = *piVar3;
  DAT_80436300 = piVar3;
  DAT_80436324 = param_10;
  while (iVar1 != -1) {
    in_r8 = (int *)(iVar1 + iVar2);
    *piVar3 = (int)in_r8;
    *(undefined4 *)(&DAT_803ccd5c + DAT_804362e4 * 4) = 0;
    iVar1 = *in_r8;
    while (iVar1 != -1) {
      *in_r8 = iVar1 + iVar2;
      *(int *)(&DAT_803ccd5c + DAT_804362e4 * 4) = *(int *)(&DAT_803ccd5c + DAT_804362e4 * 4) + 1;
      in_r8 = in_r8 + 1;
      iVar1 = *in_r8;
    }
    DAT_804362e4 = DAT_804362e4 + 1;
    piVar3 = piVar3 + 1;
    iVar1 = *piVar3;
  }
  zz_008bed8_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804362fc,
              &DAT_803ccd44,(uint *)&DAT_803ccd24,(uint *)&DAT_803ccd18,piVar3,in_r8,in_r9,in_r10);
  return;
}



// ==== 80096d0c  zz_0096d0c_ ====

void zz_0096d0c_(double param_1)

{
  FLOAT_804362f4 = (float)param_1;
  return;
}



// ==== 80096d14  zz_0096d14_ ====

void zz_0096d14_(double param_1)

{
  FLOAT_804362f0 = (float)(param_1 * (double)FLOAT_80437d88);
  return;
}



// ==== 80096d24  zz_0096d24_ ====

void zz_0096d24_(double param_1)

{
  FLOAT_804362ec = (float)param_1;
  return;
}



// ==== 80096d2c  zz_0096d2c_ ====

void zz_0096d2c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  undefined *puVar2;
  byte in_cr1;
  int local_78;
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
  int *local_10;
  
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
  if (param_9 == 1) {
    piVar1 = __va_arg(local_18,1);
    DAT_8043398c = *piVar1;
  }
  else if (param_9 < 1) {
    if (-1 < param_9) {
      piVar1 = __va_arg(local_18,1);
      DAT_80433988 = *piVar1;
    }
  }
  else if (param_9 < 3) {
    piVar1 = __va_arg(local_18,1);
    puVar2 = (undefined *)*piVar1;
    piVar1 = __va_arg(local_18,1);
    (&PTR_DAT_802dc7c0)[*piVar1] = puVar2;
  }
  return;
}



// ==== 80096e34  zz_0096e34_ ====

undefined4
zz_0096e34_(undefined2 param_1,undefined2 param_2,int param_3,char param_4,undefined2 param_5,
           int param_6)

{
  int iVar1;
  ushort *puVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iStack_18;
  int local_14 [3];
  
  if (*DAT_80436310 < 0x100) {
    pcVar4 = (char *)(*DAT_8043630c + *DAT_80436310 * 0x20);
    *(undefined2 *)(pcVar4 + 4) = param_1;
    *(undefined2 *)(pcVar4 + 6) = param_2;
    iVar1 = param_3 / 0x1f + (param_3 >> 0x1f);
    *pcVar4 = param_4;
    *(undefined2 *)(pcVar4 + 2) = param_5;
    *(short *)(pcVar4 + 8) = (short)param_6;
    *(int *)(pcVar4 + 0xc) = param_3 + (iVar1 - (iVar1 >> 0x1f)) * -0x1f;
    *(float *)(pcVar4 + 0x10) = FLOAT_804362f4;
    *(float *)(pcVar4 + 0x18) = FLOAT_804362f0;
    *(float *)(pcVar4 + 0x1c) = FLOAT_804362ec;
    *(undefined4 *)(pcVar4 + 0x14) =
         *(undefined4 *)(*(int *)(DAT_80436300 + *pcVar4 * 4) + *(short *)(pcVar4 + 2) * 4);
    pcVar4[1] = (char)DAT_804362e0;
    *(int *)(pcVar4 + 0x14) = *(int *)(pcVar4 + 0x14) + 6;
    puVar2 = zz_00971d4_(*(ushort **)(pcVar4 + 0x14),local_14,&iStack_18,0);
    if (puVar2 != (ushort *)0x0) {
      puVar2 = zz_00971d4_(*(ushort **)(pcVar4 + 0x14),local_14,&iStack_18,1);
      *(ushort **)(pcVar4 + 0x14) = puVar2;
      if (puVar2 != (ushort *)0x0) {
        *DAT_80436310 = *DAT_80436310 + 1;
        if (pcVar4[1] != '\0') {
          FUN_80097ac4((int)pcVar4);
        }
      }
    }
    uVar3 = 0;
    if ((param_6 == -1) || (param_6 == local_14[0])) {
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 80096f94  zz_0096f94_ ====

void zz_0096f94_(undefined2 param_1,undefined2 param_2,int param_3,byte *param_4)

{
  int iVar1;
  size_t sVar2;
  short *psVar3;
  undefined1 *puVar4;
  uint uVar5;
  int iVar6;
  
  sVar2 = strlen((char *)param_4);
  iVar6 = *DAT_80436304;
  uVar5 = *DAT_80436310;
  if (((int)(iVar6 + sVar2) < 0x801) && (uVar5 < 0x100)) {
    psVar3 = (short *)(*DAT_80436308 + iVar6 * 2);
    puVar4 = (undefined1 *)(*DAT_8043630c + uVar5 * 0x20);
    *(undefined2 *)(puVar4 + 4) = param_1;
    *(undefined2 *)(puVar4 + 6) = param_2;
    iVar1 = param_3 / 0x1f + (param_3 >> 0x1f);
    *puVar4 = 0xff;
    *(undefined2 *)(puVar4 + 2) = 0xffff;
    *(undefined2 *)(puVar4 + 8) = 0xffff;
    *(int *)(puVar4 + 0xc) = param_3 + (iVar1 - (iVar1 >> 0x1f)) * -0x1f;
    *(float *)(puVar4 + 0x10) = FLOAT_804362f4;
    *(float *)(puVar4 + 0x18) = FLOAT_804362f0;
    *(float *)(puVar4 + 0x1c) = FLOAT_804362ec;
    puVar4[1] = (char)DAT_804362e0;
    iVar1 = zz_0097e54_(param_4,psVar3,(int *)0x0);
    *(short **)(puVar4 + 0x14) = psVar3;
    iVar6 = iVar6 + iVar1;
    uVar5 = uVar5 + 1;
    if (puVar4[1] != '\0') {
      FUN_80097ac4((int)puVar4);
    }
  }
  *DAT_80436310 = uVar5;
  *DAT_80436304 = iVar6;
  return;
}



// ==== 800970b4  zz_00970b4_ ====

void zz_00970b4_(undefined2 param_1,undefined2 param_2,int param_3,char param_4,undefined2 param_5,
                int param_6)

{
  DAT_80436310 = &DAT_80436328;
  DAT_8043630c = &DAT_80436324;
  DAT_80436308 = &DAT_80436320;
  DAT_80436304 = &DAT_8043631c;
  DAT_804362e0 = 0;
  zz_0096e34_(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



// ==== 800970fc  zz_00970fc_ ====

void zz_00970fc_(undefined2 param_1,undefined2 param_2,int param_3,char param_4,undefined2 param_5,
                int param_6)

{
  DAT_80436310 = &DAT_80436328;
  DAT_8043630c = &DAT_80436324;
  DAT_80436308 = &DAT_80436320;
  DAT_80436304 = &DAT_8043631c;
  DAT_804362e0 = 1;
  zz_0096e34_(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



// ==== 80097144  zz_0097144_ ====

void zz_0097144_(undefined2 param_1,undefined2 param_2,int param_3,byte *param_4)

{
  DAT_80436310 = &DAT_80436328;
  DAT_8043630c = &DAT_80436324;
  DAT_80436308 = &DAT_80436320;
  DAT_80436304 = &DAT_8043631c;
  DAT_804362e0 = 0;
  zz_0096f94_(param_1,param_2,param_3,param_4);
  return;
}



// ==== 8009718c  FUN_8009718c ====

void FUN_8009718c(undefined2 param_1,undefined2 param_2,int param_3,byte *param_4)

{
  DAT_80436310 = &DAT_80436328;
  DAT_8043630c = &DAT_80436324;
  DAT_80436308 = &DAT_80436320;
  DAT_80436304 = &DAT_8043631c;
  DAT_804362e0 = 1;
  zz_0096f94_(param_1,param_2,param_3,param_4);
  return;
}



// ==== 800971d4  zz_00971d4_ ====

/* WARNING: Removing unreachable block (ram,0x80097270) */

ushort * zz_00971d4_(ushort *param_1,int *param_2,int *param_3,int param_4)

{
  ushort *puVar1;
  ushort uVar2;
  ushort uVar3;
  ushort *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  ushort *puVar8;
  
  if ((param_4 == 0) || (*DAT_80436304 < 0x7ff)) {
    puVar4 = (ushort *)(*DAT_80436308 + *DAT_80436304 * 2);
    puVar8 = puVar4;
    if (param_4 == 0) {
      puVar8 = (ushort *)0x0;
    }
    iVar7 = 0;
    iVar6 = 0;
    do {
      uVar2 = *param_1;
      if (uVar2 == 0x1001) break;
      if ((uVar2 & 0xf000) == 0x8000) {
        uVar3 = uVar2 & 0x7fff;
        if (uVar3 == 2) {
          if (param_4 != 0) {
            *puVar8 = 0xfff0;
            *DAT_80436304 = *DAT_80436304 + 1;
            puVar8[1] = param_1[1];
            puVar8 = puVar8 + 2;
            *DAT_80436304 = *DAT_80436304 + 1;
          }
          param_1 = param_1 + 2;
        }
        else if (uVar3 < 2) {
          if ((uVar2 & 0x7fff) == 0) {
            param_1 = param_1 + 1;
            iVar5 = zz_0097d04_(DAT_80433988,(short *)puVar8);
            if (param_4 != 0) {
              puVar8 = puVar8 + iVar5;
              *DAT_80436304 = *DAT_80436304 + iVar5;
            }
            iVar7 = iVar7 + iVar5;
            iVar6 = iVar6 + iVar5;
          }
          else {
            param_1 = param_1 + 1;
            iVar5 = zz_0097d04_(DAT_8043398c,(short *)puVar8);
            if (param_4 != 0) {
              puVar8 = puVar8 + iVar5;
              *DAT_80436304 = *DAT_80436304 + iVar5;
            }
            iVar7 = iVar7 + iVar5;
            iVar6 = iVar6 + iVar5;
          }
        }
        else if (uVar3 < 4) {
          puVar1 = param_1 + 1;
          param_1 = param_1 + 2;
          iVar5 = zz_0097d04_((&PTR_DAT_802dc7c0)[*puVar1],(short *)puVar8);
          if (param_4 != 0) {
            puVar8 = puVar8 + iVar5;
            *DAT_80436304 = *DAT_80436304 + iVar5;
          }
          iVar7 = iVar7 + iVar5;
          iVar6 = iVar6 + iVar5;
        }
      }
      else {
        if ((uVar2 & 0xf000) == 0) {
          iVar7 = iVar7 + 1;
          iVar6 = iVar6 + 1;
        }
        if ((uVar2 == 0xfffe) || (uVar2 == 0xfffd)) {
          iVar7 = iVar7 + 1;
          iVar6 = iVar6 + 1;
        }
        if (uVar2 == 0x1000) {
          if ((param_3 != (int *)0x0) && (*param_3 < iVar6)) {
            *param_3 = iVar6;
          }
          iVar6 = 0;
        }
        if (param_4 == 0) {
          param_1 = param_1 + 1;
        }
        else {
          uVar2 = *param_1;
          param_1 = param_1 + 1;
          *puVar8 = uVar2;
          puVar8 = puVar8 + 1;
          *DAT_80436304 = *DAT_80436304 + 1;
        }
      }
    } while ((param_4 == 0) || (*DAT_80436304 < 0x7ff));
    if (param_4 != 0) {
      *puVar8 = *param_1;
      *DAT_80436304 = *DAT_80436304 + 1;
    }
    if ((param_3 != (int *)0x0) && (*param_3 < iVar6)) {
      *param_3 = iVar6;
    }
    *param_2 = iVar7;
    if (0x7fe < *DAT_80436304 + *param_2) {
      puVar4 = (ushort *)0x0;
    }
  }
  else {
    puVar4 = (ushort *)0x0;
  }
  return puVar4;
}



// ==== 8009749c  zz_009749c_ ====

void zz_009749c_(int param_1,int param_2,int *param_3,uint *param_4)

{
  int iVar1;
  int aiStack_8 [2];
  
  DAT_80436310 = &DAT_80436328;
  DAT_8043630c = &DAT_80436324;
  DAT_80436308 = &DAT_80436320;
  DAT_80436304 = &DAT_8043631c;
  iVar1 = *(int *)(*(int *)(DAT_80436300 + param_1 * 4) + param_2 * 4);
  if (param_4 != (uint *)0x0) {
    *param_4 = (uint)*(ushort *)(iVar1 + 2);
  }
  if (param_3 != (int *)0x0) {
    *param_3 = 0;
    zz_00971d4_((ushort *)(iVar1 + 6),aiStack_8,param_3,0);
  }
  return;
}



// ==== 8009751c  zz_009751c_ ====

void zz_009751c_(void)

{
  DAT_80436328 = 0;
  DAT_8043631c = 0;
  return;
}



// ==== 8009752c  zz_009752c_ ====

void zz_009752c_(void)

{
  DAT_80436310 = &DAT_80436328;
  DAT_8043630c = &DAT_80436324;
  FUN_80097560();
  zz_009751c_();
  return;
}



// ==== 80097560  FUN_80097560 ====

/* WARNING: Removing unreachable block (ram,0x80097aa8) */
/* WARNING: Removing unreachable block (ram,0x80097aa0) */
/* WARNING: Removing unreachable block (ram,0x80097a98) */
/* WARNING: Removing unreachable block (ram,0x80097a90) */
/* WARNING: Removing unreachable block (ram,0x80097828) */
/* WARNING: Removing unreachable block (ram,0x80097824) */
/* WARNING: Removing unreachable block (ram,0x80097588) */
/* WARNING: Removing unreachable block (ram,0x80097580) */
/* WARNING: Removing unreachable block (ram,0x80097578) */
/* WARNING: Removing unreachable block (ram,0x80097570) */

void FUN_80097560(void)

{
  uint uVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  float afStack_b0 [12];
  undefined4 local_80;
  uint uStack_7c;
  undefined4 local_78;
  uint uStack_74;
  
  iVar12 = *DAT_80436310;
  if (iVar12 != 0) {
    uVar1 = (uint)DAT_803ccd58;
    gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
    gnt4_PSMTXIdentity_bl(afStack_b0);
    gnt4_GXLoadPosMtxImm_bl(afStack_b0,0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXSetZMode_bl(1,7,0);
    gnt4_GXSetCullMode_bl(2);
    gnt4_GXSetBlendMode_bl(1,4,5,0);
    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9,1);
    gnt4_GXSetVtxDesc_bl(0xb,1);
    gnt4_GXSetVtxDesc_bl(0xd,1);
    gnt4_GXSetVtxAttrFmt_bl(0,9,1,4,0);
    gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
    gnt4_GXSetVtxAttrFmt_bl(0,0xd,1,3,0);
    gnt4_GXSetNumChans_bl(1);
    gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
    gnt4_GXSetNumTexGens_bl(1);
    gnt4_GXSetNumTevStages_bl(1);
    gnt4_GXSetTevColorOp_bl(0,0,0,0,1,0);
    gnt4_GXSetTevColorIn_bl(0,2,0xe,8,0xf);
    gnt4_GXSetTevKColorSel_bl(0,0xc);
    gnt4_GXSetTevAlphaOp_bl(0,0,0,0,1,0);
    gnt4_GXSetTevAlphaIn_bl(0,7,4,5,7);
    gnt4_GXSetTevOrder_bl(0,0,0,4);
    if (DAT_803ccd48 != (uint *)0x0) {
      gnt4_GXLoadTlut_bl(DAT_803ccd48,0);
    }
    gnt4_GXLoadTexObj_bl(DAT_803ccd44,0);
    uStack_7c = (uint)DAT_803ccd58;
    uStack_74 = (uint)DAT_803ccd5a;
    local_80 = 0x43300000;
    dVar14 = (double)FLOAT_80437d80;
    local_78 = 0x43300000;
    gnt4_PSMTXScale_bl((double)(float)(dVar14 / (double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_7c) -
                                                               DOUBLE_80437d98)),
                       (double)(float)(dVar14 / (double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_74) -
                                                               DOUBLE_80437d98)),dVar14,afStack_b0);
    gnt4_GXLoadTexMtxImm_bl(afStack_b0,0x1e,1);
    gnt4_GXSetTexCoordGen2_bl(0,1,4,0x1e,0,0x7d);
    iVar13 = 0;
    for (iVar10 = 0; iVar10 < iVar12; iVar10 = iVar10 + 1) {
      iVar11 = *DAT_8043630c + iVar13;
      if ((*(char *)(iVar11 + 1) == '\0') && (iVar8 = *(int *)(iVar11 + 0x14), iVar8 != 0)) {
        dVar16 = (double)((longlong)(double)*(short *)(iVar11 + 4) * 0x3ff0000000000000);
        dVar15 = (double)((longlong)(double)*(short *)(iVar11 + 6) * 0x3ff0000000000000);
        dVar17 = (double)(FLOAT_80437d8c * *(float *)(iVar11 + 0x10));
        dVar14 = (double)*(float *)(iVar11 + 0x18);
        uVar3 = gnt4___cvt_fp2unsigned_bl((double)(FLOAT_80437d90 * *(float *)(iVar11 + 0x1c)));
        local_b4 = *(undefined4 *)(&DAT_802dc6c8 + *(int *)(iVar11 + 0xc) * 8);
        uVar3 = uVar3 | 0xffffff00;
        gnt4_GXSetTevKColor_bl(0,(byte *)&local_b4);
        local_b8 = *(undefined4 *)(&DAT_802dc6cc + *(int *)(iVar11 + 0xc) * 8);
        gnt4_GXSetTevColor_bl(1,(byte *)&local_b8);
        iVar9 = 0;
        iVar7 = 0;
        while ((*(short *)(iVar11 + 8) == -1 || (iVar9 < *(short *)(iVar11 + 8)))) {
          uVar4 = (uint)*(ushort *)(iVar8 + iVar7);
          iVar6 = iVar7 + 2;
          if (uVar4 == 0x1001) break;
          if (uVar4 == 0x1000) {
            local_78 = 0x43300000;
            dVar15 = (double)(float)(dVar15 + dVar17);
            uStack_74 = (int)*(short *)(iVar11 + 4) ^ 0x80000000;
            dVar16 = (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80437da0);
            iVar7 = iVar6;
          }
          else if (uVar4 == 0xfffd) {
            dVar16 = (double)(float)(dVar14 * (double)FLOAT_80437d88 + dVar16);
            iVar7 = iVar6;
          }
          else if (uVar4 == 0xfffe) {
            dVar16 = (double)(float)(dVar16 + dVar14);
            iVar7 = iVar6;
          }
          else if (uVar4 == 0xfff0) {
            if (*(ushort *)(iVar8 + iVar6) == 0xffff) {
              local_bc = *(undefined4 *)(&DAT_802dc6c8 + *(int *)(iVar11 + 0xc) * 8);
              gnt4_GXSetTevKColor_bl(0,(byte *)&local_bc);
              local_c0 = *(undefined4 *)(&DAT_802dc6cc + *(int *)(iVar11 + 0xc) * 8);
              gnt4_GXSetTevColor_bl(1,(byte *)&local_c0);
              iVar7 = iVar7 + 4;
            }
            else {
              iVar6 = (uint)*(ushort *)(iVar8 + iVar6) * 8;
              local_c4 = *(undefined4 *)(&DAT_802dc6c8 + iVar6);
              gnt4_GXSetTevKColor_bl(0,(byte *)&local_c4);
              local_c8 = *(undefined4 *)(&DAT_802dc6cc + iVar6);
              gnt4_GXSetTevColor_bl(1,(byte *)&local_c8);
              iVar7 = iVar7 + 4;
            }
          }
          else {
            sVar2 = (short)(uVar4 / (uVar1 / 0x18));
            sVar5 = (*(ushort *)(iVar8 + iVar7) - sVar2 * (short)(uVar1 / 0x18)) * 0x18;
            sVar2 = sVar2 * 0x18;
            gnt4_GXBegin_bl(0x80,0,4);
            DAT_cc008000 = (float)dVar16;
            DAT_cc008000 = (float)dVar15;
            iVar9 = iVar9 + 1;
            DAT_cc008000 = FLOAT_80437d94;
            DAT_cc008000 = uVar3;
            DAT_cc008000._0_2_ = sVar5;
            DAT_cc008000._0_2_ = sVar2;
            DAT_cc008000 = (float)(dVar16 + dVar17);
            DAT_cc008000 = (float)dVar15;
            DAT_cc008000 = FLOAT_80437d94;
            DAT_cc008000 = uVar3;
            DAT_cc008000._0_2_ = sVar5 + 0x18;
            DAT_cc008000._0_2_ = sVar2;
            DAT_cc008000 = (float)(dVar16 + dVar17);
            DAT_cc008000 = (float)(dVar15 + dVar17);
            DAT_cc008000 = FLOAT_80437d94;
            DAT_cc008000 = uVar3;
            DAT_cc008000._0_2_ = sVar5 + 0x18;
            DAT_cc008000._0_2_ = sVar2 + 0x18;
            DAT_cc008000 = (float)dVar16;
            dVar16 = (double)(float)(dVar16 + dVar14);
            DAT_cc008000 = (float)(dVar15 + dVar17);
            DAT_cc008000 = FLOAT_80437d94;
            DAT_cc008000 = uVar3;
            DAT_cc008000._0_2_ = sVar5;
            DAT_cc008000._0_2_ = sVar2 + 0x18;
            iVar7 = iVar6;
          }
        }
      }
      iVar13 = iVar13 + 0x20;
    }
  }
  return;
}



// ==== 80097ac4  FUN_80097ac4 ====

/* WARNING: Removing unreachable block (ram,0x80097ce8) */
/* WARNING: Removing unreachable block (ram,0x80097ce0) */
/* WARNING: Removing unreachable block (ram,0x80097b6c) */
/* WARNING: Removing unreachable block (ram,0x80097b68) */
/* WARNING: Removing unreachable block (ram,0x80097adc) */
/* WARNING: Removing unreachable block (ram,0x80097ad4) */

void FUN_80097ac4(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  short local_78;
  short local_76;
  short local_74;
  short local_72;
  uint local_70;
  uint local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  
  uVar1 = (uint)DAT_803ccd58;
  iVar6 = *(int *)(param_1 + 0x14);
  if (iVar6 != 0) {
    DAT_803c1140 = &local_5c;
    DAT_803c1144 = &local_68;
    DAT_803c1150 = &local_70;
    DAT_803c115c = &local_78;
    DAT_803c1160 = &DAT_803ccd44;
    DAT_803c1164 = 5;
    DAT_803c1168 = 0xf;
    DAT_803c1170 = 1;
    DAT_803c1173 = (undefined1)*(undefined4 *)(param_1 + 0xc);
    dVar7 = (double)((longlong)(double)*(short *)(param_1 + 4) * 0x3ff0000000000000);
    dVar8 = (double)((longlong)(double)*(short *)(param_1 + 6) * 0x3ff0000000000000);
    local_5c = (float)dVar7;
    local_58 = (float)dVar8;
    local_48 = FLOAT_80437d80;
    local_54 = FLOAT_80437d80;
    dVar9 = (double)(FLOAT_80437d8c * *(float *)(param_1 + 0x10));
    local_60 = FLOAT_80437d94;
    local_64 = FLOAT_80437d94;
    local_50 = (float)((double)(float)dVar7 + dVar9);
    local_4c = (float)((double)(float)dVar8 + dVar9);
    local_68 = FLOAT_80437d94;
    dVar7 = (double)*(float *)(param_1 + 0x18);
    local_70 = gnt4___cvt_fp2unsigned_bl((double)(FLOAT_80437d90 * *(float *)(param_1 + 0x1c)));
    local_70 = local_70 | 0xffffff00;
    iVar3 = 0;
    iVar5 = 0;
    local_6c = local_70;
    while ((*(short *)(param_1 + 8) == -1 || (iVar3 < *(short *)(param_1 + 8)))) {
      uVar2 = (uint)*(ushort *)(iVar6 + iVar5);
      iVar4 = iVar5 + 2;
      if (uVar2 == 0x1001) {
        return;
      }
      if (uVar2 == 0x1000) {
        local_64 = (float)((double)local_64 + dVar9);
        local_68 = FLOAT_80437d94;
        iVar5 = iVar4;
      }
      else if (uVar2 == 0xfffd) {
        local_68 = (float)(dVar7 * (double)FLOAT_80437d88 + (double)local_68);
        iVar5 = iVar4;
      }
      else if (uVar2 == 0xfffe) {
        local_68 = (float)((double)local_68 + dVar7);
        iVar5 = iVar4;
      }
      else if (uVar2 == 0xfff0) {
        if (*(short *)(iVar6 + iVar4) == -1) {
          DAT_803c1173 = (undefined1)*(undefined4 *)(param_1 + 0xc);
          iVar5 = iVar5 + 4;
        }
        else {
          DAT_803c1173 = (undefined1)*(short *)(iVar6 + iVar4);
          iVar5 = iVar5 + 4;
        }
      }
      else {
        local_76 = (short)(uVar2 / (uVar1 / 0x18));
        local_78 = (*(ushort *)(iVar6 + iVar5) - local_76 * (short)(uVar1 / 0x18)) * 0x18;
        local_76 = local_76 * 0x18;
        local_74 = local_78 + 0x18;
        local_72 = local_76 + 0x18;
        FUN_80051ef4(-0x7fc3eed0);
        iVar3 = iVar3 + 1;
        local_68 = (float)((double)local_68 + dVar7);
        iVar5 = iVar4;
      }
    }
  }
  return;
}



// ==== 80097d04  zz_0097d04_ ====

int zz_0097d04_(byte *param_1,short *param_2)

{
  int iVar1;
  byte *pbVar2;
  short sVar3;
  int iVar4;
  byte local_18;
  byte local_17;
  
  iVar4 = 0;
  do {
    if (*param_1 == 0) {
      if (param_2 != (short *)0x0) {
        *param_2 = -1;
      }
      return iVar4;
    }
    iVar1 = zz_0098044_(*param_1);
    if (iVar1 == 0) {
      local_18 = *param_1;
      local_17 = param_1[1];
      param_1 = param_1 + 2;
      iVar1 = gnt4_strncmp((char *)&local_18,&DAT_80437da8,2);
      if (iVar1 == 0) {
        if (param_2 != (short *)0x0) {
          *param_2 = -2;
        }
      }
      else {
        if (param_2 != (short *)0x0) {
          *param_2 = 0;
        }
        sVar3 = 0;
        for (pbVar2 = DAT_804362f8; *pbVar2 != 0; pbVar2 = pbVar2 + 2) {
          if (local_18 == *pbVar2) {
            if (local_17 == pbVar2[1]) {
              if (param_2 != (short *)0x0) {
                *param_2 = sVar3;
              }
              break;
            }
          }
          sVar3 = sVar3 + 1;
        }
      }
    }
    else {
      if (param_2 != (short *)0x0) {
        *param_2 = -2;
      }
      param_1 = param_1 + 1;
    }
    if (param_2 != (short *)0x0) {
      param_2 = param_2 + 1;
    }
    iVar4 = iVar4 + 1;
  } while( true );
}



