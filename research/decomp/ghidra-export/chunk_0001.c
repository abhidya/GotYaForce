// ==== 8000b300  FUN_8000b300 ====

void FUN_8000b300(byte *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  ushort *puVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  
  bVar1 = param_1[1];
  uVar9 = (uint)bVar1;
  switch(bVar1) {
  case 0:
    param_1[1] = bVar1 + 1;
    *param_1 = *param_1 & 0x7f;
  case 1:
    DAT_803af140 = 0;
    DAT_803af144 = -1;
    DAT_803af158 = -1;
    DAT_803af159 = 0;
    DAT_803af15c = 0;
    DAT_803c06cc = 0;
    DAT_803c064c = 0;
    DAT_803c06d0 = 0;
    DAT_803c0650 = 0;
    DAT_803c06d4 = 0;
    DAT_803c0654 = 0;
    DAT_803c06d8 = 0;
    DAT_803c0658 = 0;
    DAT_803c06dc = 0;
    DAT_803c065c = 0;
    DAT_803c06e0 = 0;
    DAT_803c0660 = 0;
    DAT_803c06e4 = 0;
    DAT_803c0664 = 0;
    DAT_803c06e8 = 0;
    DAT_803c0668 = 0;
    DAT_803c06ec = 0;
    DAT_803c066c = 0;
    DAT_803c06f0 = 0;
    DAT_803c0670 = 0;
    DAT_803c06f4 = 0;
    DAT_803c0674 = 0;
    DAT_803c06f8 = 0;
    DAT_803c0678 = 0;
    DAT_803c06fc = 0;
    DAT_803c067c = 0;
    DAT_803c0700 = 0;
    DAT_803c0680 = 0;
    DAT_803c0704 = 0;
    DAT_803c0684 = 0;
    DAT_803c0708 = 0;
    DAT_803c0688 = 0;
    param_1[1] = param_1[1] + 1;
switchD_8000b348_caseD_2:
    uVar9 = 0x800;
    param_4 = 1;
    iVar6 = zz_00f19f8_(0x803c0740,*(int *)(param_1 + 0x10),0x800,1);
    if (iVar6 == 0) {
      return;
    }
    param_1[1] = param_1[1] + 1;
    param_1[0x1a] = 0;
    param_1[0x1b] = 0;
switchD_8000b348_caseD_3:
    uVar7 = DAT_803c0740;
    if (*(char *)(DAT_804360d0 + 0xd) == '\x01') {
      param_1[1] = 0xfe;
      return;
    }
    if (DAT_803af144 < 0) {
      iVar6 = 0;
      DAT_803af144 = 0;
      puVar11 = &DAT_803c068c;
      DAT_803af148 = &DAT_803c0744;
      DAT_803af140 = DAT_803c0740;
      DAT_803af154 = 0;
      DAT_803af15c = 0;
      DAT_803af160 = 1;
      if (0 < (int)DAT_803c0740) {
        uVar9 = DAT_803c0740 >> 3;
        if (uVar9 != 0) {
          do {
            *puVar11 = *(undefined4 *)(*(int *)(param_1 + 0xc) + iVar6);
            puVar11[1] = *(undefined4 *)(*(int *)(param_1 + 0xc) + iVar6 + 4);
            puVar11[2] = *(undefined4 *)(*(int *)(param_1 + 0xc) + iVar6 + 8);
            puVar11[3] = *(undefined4 *)(*(int *)(param_1 + 0xc) + iVar6 + 0xc);
            puVar11[4] = *(undefined4 *)(*(int *)(param_1 + 0xc) + iVar6 + 0x10);
            puVar11[5] = *(undefined4 *)(*(int *)(param_1 + 0xc) + iVar6 + 0x14);
            iVar10 = iVar6 + 0x1c;
            puVar11[6] = *(undefined4 *)(*(int *)(param_1 + 0xc) + iVar6 + 0x18);
            iVar6 = iVar6 + 0x20;
            puVar11[7] = *(undefined4 *)(*(int *)(param_1 + 0xc) + iVar10);
            puVar11 = puVar11 + 8;
            uVar9 = uVar9 - 1;
          } while (uVar9 != 0);
          uVar7 = uVar7 & 7;
          if (uVar7 == 0) goto LAB_8000b574;
        }
        do {
          puVar2 = (undefined4 *)(*(int *)(param_1 + 0xc) + iVar6);
          iVar6 = iVar6 + 4;
          *puVar11 = *puVar2;
          puVar11 = puVar11 + 1;
          uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
      }
LAB_8000b574:
      *param_1 = *param_1 | 0x80;
    }
    else {
      if ((DAT_803af159 & 0x40) != 0) {
        DAT_803af154 = zz_0048588_((ushort *)(DAT_80436238 + 0x4800),DAT_803af14c,uVar9,param_4);
      }
      gnt4_DCFlushRange_bl((uint)DAT_803af14c,DAT_803af154);
      uVar9 = DAT_803af154 + 0x7ff;
      iVar10 = ((int)uVar9 >> 0xb) + (uint)((int)uVar9 < 0 && (uVar9 & 0x7ff) != 0);
      iVar6 = iVar10 * 0x800;
      DAT_803af154 = iVar6;
      if (-1 < DAT_803af158) {
        iVar3 = (int)DAT_803af158;
        (&DAT_803c06cc)[iVar3] = DAT_803af14c + iVar10 * 0x400;
        (&DAT_803c064c)[iVar3] = iVar6;
      }
    }
    iVar6 = 0;
    while (DAT_803af144 < (int)DAT_803af140) {
      puVar5 = DAT_803af148 + 1;
      DAT_803af15c = DAT_803af15c + DAT_803af160;
      uVar9 = *DAT_803af148;
      DAT_803af160 = uVar9 & 0x3fffffff;
      DAT_803af159 = (byte)(uVar9 >> 0x18) & 0xc0;
      DAT_803af148 = puVar5;
      if (DAT_803af160 == 0) {
        puVar8 = *(ushort **)(*(int *)(param_1 + 0xc) + DAT_803af144 * 4);
        if (puVar8 != (ushort *)0x0) {
          DAT_803af158 = DAT_803af158 + '\x01';
          DAT_803af14c = puVar8;
        }
        *(undefined4 *)(*(int *)(param_1 + 0xc) + DAT_803af144 * 4) = 0;
        DAT_803af154 = 0;
        DAT_803af144 = DAT_803af144 + 1;
      }
      else {
        DAT_803af150 = *(uint *)(*(int *)(param_1 + 0xc) + DAT_803af144 * 4);
        if (DAT_803af150 == 0) {
          if (iVar6 == 0) {
            DAT_803af150 = (int)DAT_803af14c + DAT_803af154;
            *(uint *)(*(int *)(param_1 + 0xc) + DAT_803af144 * 4) = DAT_803af150;
LAB_8000b73c:
            DAT_803af14c = (ushort *)DAT_803af150;
            if (DAT_803af159 != 0) {
              DAT_803af150 = DAT_80436238 + 0x4800;
            }
            DAT_803af154 = uVar9 << 0xb;
            DAT_803af144 = DAT_803af144 + 1;
            param_1[1] = param_1[1] + 1;
            return;
          }
          DAT_803af144 = DAT_803af144 + 1;
          iVar6 = iVar6 + DAT_803af160;
        }
        else {
          if ((DAT_803af150 & 0xf0000000) != 0xf0000000) {
            DAT_803af158 = DAT_803af158 + '\x01';
            goto LAB_8000b73c;
          }
          DAT_803af144 = DAT_803af144 + 1;
          iVar6 = iVar6 + DAT_803af160;
          DAT_803af158 = DAT_803af158 + '\x01';
        }
      }
    }
    *(int *)(DAT_804360d0 + 8) = *(int *)(DAT_804360d0 + 8) + *(int *)(param_1 + 4);
    zz_000b26c_(param_1);
    break;
  case 2:
    goto switchD_8000b348_caseD_2;
  case 3:
    goto switchD_8000b348_caseD_3;
  case 4:
    iVar6 = zz_00f19f8_(DAT_803af150,*(int *)(param_1 + 0x10) + DAT_803af15c * 0x800,DAT_803af154,1)
    ;
    if (iVar6 != 0) {
      param_1[1] = param_1[1] - 1;
    }
    break;
  case 0xfe:
    *(undefined1 *)(DAT_804360d0 + 0xd) = 2;
    zz_000b26c_(param_1);
    break;
  case 0xff:
    param_1[1] = 1;
    if ((*param_1 & 0x80) != 0) {
      puVar11 = &DAT_803c068c;
      iVar6 = 0;
      for (iVar10 = 0; iVar10 < (int)DAT_803af140; iVar10 = iVar10 + 1) {
        uVar4 = *puVar11;
        puVar11 = puVar11 + 1;
        *(undefined4 *)(*(int *)(param_1 + 0xc) + iVar6) = uVar4;
        iVar6 = iVar6 + 4;
      }
    }
  }
  return;
}



// ==== 8000b830  FUN_8000b830 ====

void FUN_8000b830(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined1 *param_9,undefined4 param_10,uint param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  char cVar3;
  short sVar4;
  int iVar5;
  
  iVar5 = -0x7fc50000;
  cVar3 = param_9[1];
  if (cVar3 == '\x01') {
LAB_8000b894:
    DAT_804361c0 = zz_0273000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,
                               *(int *)(param_9 + 0x10));
    if (DAT_804361c0 == (undefined1 *)0x0) {
      param_9[1] = 0xff;
      return;
    }
    DAT_803af140 = 0;
    DAT_803af150 = DAT_80436238 + 0x4800;
    DAT_803af144 = 0xffffffff;
    DAT_803af158 = 0xff;
    DAT_803af159 = 0;
    DAT_803af15c = 0;
    DAT_803af154 = *(uint *)(param_9 + 4);
    param_9[1] = param_9[1] + '\x01';
  }
  else {
    if (cVar3 < '\x01') {
      if (cVar3 == -1) {
        param_9[1] = 1;
        return;
      }
      if (cVar3 < -1) {
        if (cVar3 < -2) {
          return;
        }
        iVar5 = zz_02722d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int)DAT_804361c0,0x803b0000,param_11,param_12,param_13,param_14,
                            param_15,param_16);
        if (iVar5 != 1) {
          return;
        }
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        *(undefined1 *)(DAT_804360d0 + 0xd) = 2;
        zz_000b26c_(param_9);
        return;
      }
      param_9[1] = cVar3 + '\x01';
      goto LAB_8000b894;
    }
    if (cVar3 == '\x03') goto LAB_8000b948;
    if ('\x02' < cVar3) {
      return;
    }
  }
  param_9[1] = param_9[1] + '\x01';
  *(undefined2 *)(param_9 + 0x1a) = 0;
  if ((int)DAT_803af154 < 0x80001) {
    bVar1 = (int)DAT_803af154 < 0;
    uVar2 = DAT_803af154 & 0x7ff;
    iVar5 = (int)DAT_803af154 >> 0xb;
    DAT_803af154 = 0;
    iVar5 = iVar5 + (uint)(bVar1 && uVar2 != 0);
  }
  else {
    DAT_803af154 = DAT_803af154 - 0x80000;
    iVar5 = 0x100;
  }
  param_11 = DAT_803af150;
  DAT_803af160 = iVar5;
  zz_02729e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_804361c0,
              iVar5,DAT_803af150,param_12,param_13,param_14,param_15,param_16);
LAB_8000b948:
  iVar5 = zz_02722d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)DAT_804361c0,iVar5,param_11,param_12,param_13,param_14,param_15,param_16)
  ;
  if (iVar5 == 3) {
    iVar5 = zz_00f19f8_(DAT_803af150,*(int *)(param_9 + 0xc) + DAT_803af15c * 0x800,
                        DAT_803af160 << 0xb,0);
    if (iVar5 != 0) {
      DAT_803af15c = DAT_803af15c + DAT_803af160;
      if ((int)DAT_803af154 < 1) {
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        *(int *)(DAT_804360d0 + 8) = *(int *)(DAT_804360d0 + 8) + *(int *)(param_9 + 4);
        zz_000b26c_(param_9);
      }
      else {
        param_9[1] = param_9[1] + -1;
      }
    }
  }
  else if (iVar5 < 3) {
    if (iVar5 == 1) {
      sVar4 = *(short *)(param_9 + 0x1a);
      *(short *)(param_9 + 0x1a) = sVar4 + 1;
      if (0x3c < (short)(sVar4 + 1)) {
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        param_9[1] = 0xff;
      }
    }
    else if (0 < iVar5) {
      if (*(char *)(DAT_804360d0 + 0xd) == '\x01') {
        zz_0272868_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    (int)DAT_804361c0);
        param_9[1] = 0xfe;
      }
      else {
        *(undefined2 *)(param_9 + 0x1a) = 0;
      }
    }
  }
  else if (iVar5 < 5) {
    zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
    DAT_804361c0 = (undefined1 *)0x0;
    param_9[1] = 0xff;
  }
  return;
}



// ==== 8000bad8  FUN_8000bad8 ====

void FUN_8000bad8(undefined1 *param_1)

{
  int iVar1;
  
  iVar1 = zz_00f19f8_(*(uint *)(param_1 + 0x10),*(int *)(param_1 + 0xc),*(int *)(param_1 + 4),0);
  if (iVar1 != 0) {
    zz_000b26c_(param_1);
  }
  return;
}



// ==== 8000bb24  FUN_8000bb24 ====

void FUN_8000bb24(undefined1 *param_1)

{
  int iVar1;
  
  iVar1 = zz_00f19f8_(*(uint *)(param_1 + 0x10),*(int *)(param_1 + 0xc),*(int *)(param_1 + 4),1);
  if (iVar1 != 0) {
    zz_000b26c_(param_1);
  }
  return;
}



// ==== 8000bb70  zz_000bb70_ ====

/* WARNING: Removing unreachable block (ram,0x8000bd80) */
/* WARNING: Removing unreachable block (ram,0x8000bb80) */

void zz_000bb70_(void)

{
  char cVar1;
  undefined1 *__s;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  __s = &DAT_803c73b0;
  iVar2 = 0;
  local_2c = DAT_802b0200;
  dVar5 = (double)FLOAT_80436aa8;
  local_28 = DAT_802b0204;
  local_24 = DAT_802b0208;
  local_38 = DAT_802b020c;
  local_34 = DAT_802b0210;
  local_30 = DAT_802b0214;
  local_44 = DAT_802b0218;
  local_40 = DAT_802b021c;
  local_3c = DAT_802b0220;
  do {
    gnt4_memset(__s,0,0x3e4);
    cVar1 = (char)(iVar2 / 6);
    *__s = 0;
    __s[0x10] = (char)iVar2;
    __s[0x2e5] = (char)iVar2 + cVar1 * -6;
    __s[0x11] = cVar1;
    __s[0x83] = 0x20;
    *(float *)(__s + 0x2e8) = local_2c;
    *(undefined4 *)(__s + 0x2ec) = local_28;
    *(undefined4 *)(__s + 0x2f0) = local_24;
    *(float *)(__s + 0x300) = local_44;
    *(undefined4 *)(__s + 0x304) = local_40;
    *(undefined4 *)(__s + 0x308) = local_3c;
    *(float *)(__s + 0x9c) = local_38;
    *(undefined4 *)(__s + 0xa0) = local_34;
    *(undefined4 *)(__s + 0xa4) = local_30;
    dVar3 = gnt4_PSVECSquareDistance_bl((float *)(__s + 0x2e8),(float *)(__s + 0x300));
    if (dVar5 < dVar3) {
      dVar4 = 1.0 / SQRT(dVar3);
      dVar4 = DOUBLE_80436ab0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8);
      dVar4 = DOUBLE_80436ab0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8);
      dVar3 = (double)(float)(dVar3 * DOUBLE_80436ab0 * dVar4 *
                                      -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8));
    }
    *(float *)(__s + 0x348) = (float)dVar3;
    gnt4_C_MTXLookAt_bl((float *)(__s + 0x394),&local_2c,&local_38,&local_44);
    gnt4_PSMTXIdentity_bl((float *)(__s + 0x114));
    iVar2 = iVar2 + 1;
    __s = __s + 0x3e4;
  } while (iVar2 < 0xd);
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
  zz_0010b50_();
  return;
}



// ==== 8000bda4  zz_000bda4_ ====

void zz_000bda4_(void)

{
  float fVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  puVar2 = &DAT_803c73b0;
  iVar3 = 0;
  do {
    fVar1 = FLOAT_80436ac0;
    iVar4 = (&DAT_803c4e84)[(char)puVar2[0x2e5]];
    if ('\0' < *(char *)(iVar4 + 0x18)) {
      if ((PTR_DAT_80433934[0x15db] & *(byte *)(iVar4 + 0x3e5)) == 0) {
        *puVar2 = 0;
      }
      else {
        *puVar2 = 1;
        *(float *)(puVar2 + 0x354) = FLOAT_80436ac4 * (*(float *)(iVar4 + 0xb4) - fVar1) + fVar1;
        if (puVar2[0x2e4] == '\0') {
          puVar2[0x2e4] = 1;
          *(undefined1 **)(puVar2 + 0x90) = puVar2;
          *(float *)(puVar2 + 0xb4) = fVar1;
          *(float *)(puVar2 + 0xc0) = fVar1;
          *(float *)(puVar2 + 0x58) = fVar1;
          *(float *)(puVar2 + 0x5c) = fVar1;
          *(float *)(puVar2 + 0x60) = fVar1;
          zz_008ae10_((int)puVar2,0x3d);
          *(undefined2 *)(puVar2 + 0x1c8) = 0x7fff;
          *(undefined2 *)(puVar2 + 0x1c4) = 0x7fff;
        }
        *(undefined2 *)(puVar2 + 0x1c6) = *(undefined2 *)(puVar2 + 0x1c4);
        if (puVar2[0x11] == '\0') {
          zz_000c5f8_((int)puVar2,iVar4);
        }
        else {
          zz_000d46c_(puVar2,iVar4);
        }
      }
    }
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 0x3e4;
  } while (iVar3 < 0xc);
  if (PTR_DAT_80433930[0x40] != '\0') {
    zz_0010b64_();
  }
  return;
}



// ==== 8000bef4  zz_000bef4_ ====

void zz_000bef4_(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined *puVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  
  if (PTR_DAT_80433930[0x40] == '\0') {
    uVar9 = 0;
    if (((((((PTR_DAT_80433930[2] & 1) == 0) || (*DAT_803c4e84 == '\0')) &&
          ((uVar9 = 1, (PTR_DAT_80433930[2] & 2) == 0 || (*DAT_803c4e88 == '\0')))) &&
         ((uVar9 = 2, (PTR_DAT_80433930[2] & 4) == 0 || (*DAT_803c4e8c == '\0')))) &&
        ((uVar9 = 3, (PTR_DAT_80433930[2] & 8) == 0 || (*DAT_803c4e90 == '\0')))) &&
       (((uVar9 = 4, (PTR_DAT_80433930[2] & 0x10) == 0 || (*DAT_803c4e94 == '\0')) &&
        ((uVar9 = 5, (PTR_DAT_80433930[2] & 0x20) == 0 || (*DAT_803c4e98 == '\0')))))) {
      uVar9 = 6;
    }
    if (5 < uVar9) {
      uVar9 = 0;
    }
    cVar1 = PTR_DAT_80433930[0x29];
    if (cVar1 == '\x02') {
      iVar2 = 0;
      iVar10 = 0;
      do {
        uVar8 = (uint)(char)PTR_DAT_80433934[iVar2 + 0xc0];
        if ((uVar8 == 0xffffffff) || (((uint)(byte)PTR_DAT_80433934[0x15db] & 1 << uVar8) == 0)) {
          uVar8 = uVar9;
        }
        uVar3 = zz_0010514_(uVar8);
        uVar5 = uVar8;
        if ((uVar3 & 0x7fffffff) != 0) {
          uVar5 = uVar8 + 6;
        }
        iVar4 = iVar10 + 0x14;
        iVar10 = iVar10 + 4;
        *(undefined **)(PTR_DAT_80433930 + iVar4) = &DAT_803c7744 + uVar5 * 0x3e4;
        PTR_DAT_80433930[iVar2 + 0xc] = (&DAT_803c73c0)[uVar5 * 0x3e4];
        *(char *)((int)(&DAT_803c4e84)[uVar8] + 0x487) = (char)iVar2;
        iVar2 = iVar2 + 1;
      } while (iVar2 < 4);
    }
    else if ((cVar1 < '\x02') && ('\0' < cVar1)) {
      iVar2 = 0;
      iVar10 = 0;
      do {
        uVar8 = (uint)(char)PTR_DAT_80433934[iVar2 + 0xc0];
        if ((uVar8 == 0xffffffff) || (((uint)(byte)PTR_DAT_80433934[0x15db] & 1 << uVar8) == 0)) {
          uVar8 = uVar9;
        }
        uVar3 = zz_0010514_(uVar8);
        uVar5 = uVar8;
        if ((uVar3 & 0x7fffffff) != 0) {
          uVar5 = uVar8 + 6;
        }
        iVar4 = uVar5 * 0x3e4;
        iVar6 = iVar10 + 0x1c;
        *(undefined **)(PTR_DAT_80433930 + iVar10 + 0x14) = &DAT_803c7744 + iVar4;
        iVar10 = iVar10 + 4;
        PTR_DAT_80433930[iVar2 + 0xc] = (&DAT_803c73c0)[iVar4];
        *(undefined **)(PTR_DAT_80433930 + iVar6) = &DAT_803c7744 + iVar4;
        PTR_DAT_80433930[iVar2 + 0xe] = (&DAT_803c73c0)[iVar4];
        *(char *)((int)(&DAT_803c4e84)[uVar8] + 0x487) = (char)iVar2;
        iVar2 = iVar2 + 1;
      } while (iVar2 < 2);
    }
    else {
      uVar8 = (uint)(char)PTR_DAT_80433934[0xc0];
      if ((uVar8 == 0xffffffff) || (((uint)(byte)PTR_DAT_80433934[0x15db] & 1 << uVar8) == 0)) {
        uVar8 = uVar9;
      }
      uVar5 = zz_0010514_(uVar8);
      uVar9 = uVar8;
      if ((uVar5 & 0x7fffffff) != 0) {
        uVar9 = uVar8 + 6;
      }
      iVar2 = uVar9 * 0x3e4;
      puVar7 = &DAT_803c7744 + iVar2;
      *(undefined **)(PTR_DAT_80433930 + 0x14) = puVar7;
      PTR_DAT_80433930[0xc] = (&DAT_803c73c0)[iVar2];
      *(undefined **)(PTR_DAT_80433930 + 0x18) = puVar7;
      PTR_DAT_80433930[0xd] = (&DAT_803c73c0)[iVar2];
      *(undefined **)(PTR_DAT_80433930 + 0x1c) = puVar7;
      PTR_DAT_80433930[0xe] = (&DAT_803c73c0)[iVar2];
      *(undefined **)(PTR_DAT_80433930 + 0x20) = puVar7;
      PTR_DAT_80433930[0xf] = (&DAT_803c73c0)[iVar2];
      *(undefined1 *)((int)(&DAT_803c4e84)[uVar8] + 0x487) = 0;
    }
  }
  else {
    iVar2 = (int)DAT_804360dc;
    *(undefined **)(PTR_DAT_80433930 + 0x14) = &DAT_803ca5f4;
    PTR_DAT_80433930[0xc] = DAT_803ca270;
    *(undefined **)(PTR_DAT_80433930 + 0x18) = &DAT_803ca5f4;
    PTR_DAT_80433930[0xd] = DAT_803ca270;
    *(undefined **)(PTR_DAT_80433930 + 0x1c) = &DAT_803ca5f4;
    PTR_DAT_80433930[0xe] = DAT_803ca270;
    *(undefined **)(PTR_DAT_80433930 + 0x20) = &DAT_803ca5f4;
    PTR_DAT_80433930[0xf] = DAT_803ca270;
    *(undefined1 *)((int)(&DAT_803c4e84)[iVar2] + 0x487) = 0;
  }
  return;
}



// ==== 8000c314  FUN_8000c314 ====

/* WARNING: Removing unreachable block (ram,0x8000c544) */

void FUN_8000c314(int param_1)

{
  char cVar1;
  float afStack_48 [3];
  float afStack_3c [3];
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x2e8),&local_30);
  if (local_28 * local_28 + local_30 * local_30 + local_2c * local_2c <= FLOAT_80436ac8) {
    local_30 = *(float *)(param_1 + 0x36c);
    local_2c = *(float *)(param_1 + 0x37c);
    local_28 = *(float *)(param_1 + 0x38c);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x2e8),&local_30,(float *)(param_1 + 0x300));
  }
  local_10 = -local_30;
  local_18 = local_28;
  local_14 = FLOAT_80436aa8;
  if (local_10 * local_10 + local_28 * local_28 + FLOAT_80436aa8 * FLOAT_80436aa8 <= FLOAT_80436ac8)
  {
    gnt4_PSVECCrossProduct_bl((float *)(param_1 + 0x330),&local_30,&local_18);
  }
  gnt4_PSVECCrossProduct_bl(&local_30,&local_18,&local_24);
  gnt4_PSVECNormalize_bl(&local_18,&local_18);
  gnt4_PSVECNormalize_bl(&local_24,&local_24);
  gnt4_PSVECNormalize_bl(&local_30,&local_30);
  *(float *)(param_1 + 0x364) = local_18;
  *(float *)(param_1 + 0x374) = local_14;
  *(float *)(param_1 + 900) = local_10;
  *(float *)(param_1 + 0x368) = local_24;
  *(undefined4 *)(param_1 + 0x378) = local_20;
  *(undefined4 *)(param_1 + 0x388) = local_1c;
  *(float *)(param_1 + 0x36c) = local_30;
  *(float *)(param_1 + 0x37c) = local_2c;
  *(float *)(param_1 + 0x38c) = local_28;
  *(undefined4 *)(param_1 + 0x370) = *(undefined4 *)(param_1 + 0x2e8);
  *(undefined4 *)(param_1 + 0x380) = *(undefined4 *)(param_1 + 0x2ec);
  *(undefined4 *)(param_1 + 0x390) = *(undefined4 *)(param_1 + 0x2f0);
  if (*(char *)(param_1 + 0x360) == '\0') {
    *(undefined2 *)(param_1 + 0x74) = 0;
  }
  else {
    if (*(char *)(param_1 + 0x10) < '\x06') {
      if ((*(short *)(param_1 + 0x74) != 0x7fff) &&
         (*(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x800,
         *(short *)(param_1 + 0x74) < 0)) {
        *(undefined2 *)(param_1 + 0x74) = 0x7fff;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x74) = (&DAT_803c7424)[*(char *)(param_1 + 0x2e5) * 0x1f2];
    }
    zz_0045e74_((float *)(param_1 + 0x364),&local_30,*(short *)(param_1 + 0x74));
    local_24 = *(float *)(param_1 + 0x368);
    local_20 = *(undefined4 *)(param_1 + 0x378);
    local_1c = *(undefined4 *)(param_1 + 0x388);
  }
  *(float *)(param_1 + 0x330) = local_24;
  *(undefined4 *)(param_1 + 0x334) = local_20;
  *(undefined4 *)(param_1 + 0x338) = local_1c;
  cVar1 = *(char *)(param_1 + 0x35d);
  if (cVar1 == '\0') {
    gnt4_C_MTXLookAt_bl((float *)(param_1 + 0x394),(float *)(param_1 + 0x2e8),
                        (float *)(param_1 + 0x330),(float *)(param_1 + 0x300));
  }
  else {
    *(char *)(param_1 + 0x35d) = cVar1 + -1;
    gnt4_PSQUATScale_bl((double)((longlong)(double)(char)(&DAT_802c38ac)[cVar1] * 0x3ff0000000000000
                                ),&local_24,&local_24);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x2e8),&local_24,afStack_3c);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),&local_24,afStack_48);
    gnt4_C_MTXLookAt_bl((float *)(param_1 + 0x394),afStack_3c,(float *)(param_1 + 0x330),afStack_48)
    ;
  }
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x2e8);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x2ec);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x2f0);
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x2f4);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x2f8);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x2fc);
  gnt4_PSMTXCopy_bl((float *)(param_1 + 0x364),(float *)(param_1 + 0x114));
  zz_0010980_(param_1);
  return;
}



// ==== 8000c5f8  zz_000c5f8_ ====

void zz_000c5f8_(int param_1,int param_2)

{
  if (*(char *)(param_2 + 0x3f1) == '\0') {
    *(undefined1 *)(param_1 + 0x18) = 0;
  }
  (*(code *)(&PTR_FUN_802c38cc)[*(char *)(param_1 + 0x18)])(param_1);
  FUN_8000c314(param_1);
  return;
}



// ==== 8000c660  FUN_8000c660 ====

/* WARNING: Removing unreachable block (ram,0x8000c8f8) */
/* WARNING: Removing unreachable block (ram,0x8000c670) */

void FUN_8000c660(int param_1,int param_2)

{
  float fVar1;
  undefined4 uVar2;
  double dVar3;
  double dVar4;
  float local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  float local_30;
  float local_2c;
  float local_28;
  
  *(undefined1 *)(param_1 + 0x18) = 1;
  fVar1 = FLOAT_80436acc;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x19) = 0;
  *(undefined1 *)(param_2 + 0x3f1) = 1;
  *(float *)(param_1 + 0x348) = fVar1 * *(float *)(param_2 + *(char *)(param_2 + 0x582) * 8 + 0x898)
  ;
  *(undefined4 *)(param_1 + 0x350) =
       *(undefined4 *)(param_2 + *(char *)(param_2 + 0x582) * 4 + 0x88c);
  fVar1 = FLOAT_80436ad4;
  if (((PTR_DAT_80433930[0x29] == '\x01') && (PTR_DAT_80433930[0x3d] == '\0')) ||
     (PTR_DAT_80433930[0x29] == '\x02')) {
    *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x348) * FLOAT_80436ad0;
    *(float *)(param_1 + 0x350) = *(float *)(param_1 + 0x350) * fVar1;
  }
  uVar2 = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x30c) = uVar2;
  *(undefined4 *)(param_1 + 0x300) = uVar2;
  fVar1 = *(float *)(param_2 + 0x6d0) + *(float *)(param_2 + 0x24) + *(float *)(param_1 + 0x350);
  *(float *)(param_1 + 0x310) = fVar1;
  *(float *)(param_1 + 0x304) = fVar1;
  uVar2 = *(undefined4 *)(param_2 + 0x28);
  *(undefined4 *)(param_1 + 0x314) = uVar2;
  *(undefined4 *)(param_1 + 0x308) = uVar2;
  *(undefined2 *)(param_1 + 0x70) = 0x600;
  *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_2 + 0x72);
  *(undefined2 *)(param_1 + 0x74) = 0;
  *(short *)(param_2 + 0x5b0) = *(short *)(param_1 + 0x72) + -0x8000;
  dVar3 = zz_0045204_(*(short *)(param_2 + 0x5b0));
  *(float *)(param_1 + 0x318) =
       (float)((double)*(float *)(param_1 + 0x348) * dVar3 + (double)*(float *)(param_1 + 0x300));
  *(undefined4 *)(param_1 + 0x31c) = *(undefined4 *)(param_1 + 0x304);
  dVar3 = zz_0045238_(*(short *)(param_2 + 0x5b0));
  *(float *)(param_1 + 800) =
       (float)((double)*(float *)(param_1 + 0x348) * dVar3 + (double)*(float *)(param_1 + 0x308));
  dVar3 = zz_0045238_(*(short *)(param_1 + 0x70));
  dVar4 = (double)(float)((double)*(float *)(param_1 + 0x348) * dVar3);
  dVar3 = zz_0045204_(*(short *)(param_2 + 0x5b0));
  fVar1 = (float)(dVar3 * dVar4 + (double)*(float *)(param_1 + 0x300));
  *(float *)(param_1 + 0x2f4) = fVar1;
  *(float *)(param_1 + 0x2e8) = fVar1;
  dVar3 = zz_0045204_(*(short *)(param_1 + 0x70));
  fVar1 = (float)((double)*(float *)(param_1 + 0x348) * dVar3 + (double)*(float *)(param_1 + 0x304))
  ;
  *(float *)(param_1 + 0x2f8) = fVar1;
  *(float *)(param_1 + 0x2ec) = fVar1;
  dVar3 = zz_0045238_(*(short *)(param_1 + 0x70));
  dVar4 = (double)(float)((double)*(float *)(param_1 + 0x348) * dVar3);
  dVar3 = zz_0045238_(*(short *)(param_2 + 0x5b0));
  fVar1 = (float)(dVar3 * dVar4 + (double)*(float *)(param_1 + 0x308));
  *(float *)(param_1 + 0x2fc) = fVar1;
  *(float *)(param_1 + 0x2f0) = fVar1;
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x2e8),&local_48);
  local_28 = -local_48;
  local_30 = local_40;
  local_2c = FLOAT_80436aa8;
  gnt4_PSVECCrossProduct_bl(&local_48,&local_30,&local_3c);
  gnt4_PSVECNormalize_bl(&local_30,&local_30);
  gnt4_PSVECNormalize_bl(&local_3c,&local_3c);
  gnt4_PSVECNormalize_bl(&local_48,&local_48);
  *(float *)(param_1 + 0x364) = local_30;
  *(float *)(param_1 + 0x374) = local_2c;
  *(float *)(param_1 + 900) = local_28;
  *(float *)(param_1 + 0x368) = local_30;
  *(float *)(param_1 + 0x378) = local_2c;
  *(float *)(param_1 + 0x388) = local_28;
  *(float *)(param_1 + 0x36c) = local_48;
  *(undefined4 *)(param_1 + 0x37c) = local_44;
  *(float *)(param_1 + 0x38c) = local_40;
  *(undefined4 *)(param_1 + 0x370) = *(undefined4 *)(param_1 + 0x2e8);
  *(undefined4 *)(param_1 + 0x380) = *(undefined4 *)(param_1 + 0x2ec);
  *(undefined4 *)(param_1 + 0x390) = *(undefined4 *)(param_1 + 0x2f0);
  *(float *)(param_1 + 0x330) = local_3c;
  *(undefined4 *)(param_1 + 0x334) = local_38;
  *(undefined4 *)(param_1 + 0x338) = local_34;
  return;
}



// ==== 8000c918  FUN_8000c918 ====

void FUN_8000c918(int param_1,int param_2)

{
  *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0x2e8);
  *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x2ec);
  *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0x2f0);
  *(undefined4 *)(param_1 + 0x30c) = *(undefined4 *)(param_1 + 0x300);
  *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_1 + 0x304);
  *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(param_1 + 0x308);
  (*(code *)(&PTR_caseD_4_802c3894)[*(char *)(param_2 + 0x3f1)])();
  return;
}



// ==== 8000c988  FUN_8000c988 ====

void FUN_8000c988(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  float local_18 [2];
  float local_10;
  
  *(undefined4 *)(param_1 + 0x30c) = *(undefined4 *)(param_1 + 0x300);
  *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_1 + 0x304);
  *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(param_1 + 0x308);
  *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0x2e8);
  *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x2ec);
  *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0x2f0);
  if (*(char *)(param_1 + 0x19) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300),(float *)(param_1 + 0x33c));
    iVar4 = FUN_800452e4((double)FLOAT_80436ad8,(float *)(param_1 + 0x33c),
                         *(short *)(param_2 + 0x5b0));
    if (iVar4 == 0) {
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c));
    }
    *(float *)(param_1 + 0x340) = FLOAT_80436aa8;
    *(undefined1 *)(param_1 + 0x2e7) = 0;
    dVar5 = gnt4_PSVECMag_bl((float *)(param_1 + 0x33c));
    *(float *)(param_1 + 0x348) = (float)dVar5;
    fVar1 = FLOAT_80436adc;
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x2ec);
    *(float *)(param_1 + 0x38) = fVar1 * *(float *)(param_2 + 0x668);
  }
  fVar1 = FLOAT_80436ac4;
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_2 + 0x20);
  fVar2 = FLOAT_80436ae0;
  *(float *)(param_1 + 0x304) =
       (*(float *)(param_2 + 0x6d0) +
       *(float *)(param_1 + 0x350) + *(float *)(param_1 + 0x310) + *(float *)(param_2 + 0x24)) *
       fVar1;
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_2 + 0x28);
  if (*(float *)(param_1 + 0x348) <= fVar2) {
    *(float *)(param_1 + 0x348) = fVar2;
  }
  else {
    *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x348) * FLOAT_80436ae4;
  }
  zz_00453fc_('y',(float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c),0x200);
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c));
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),(float *)(param_1 + 0x33c),local_18);
  fVar1 = *(float *)(param_1 + 0x3c);
  if (fVar1 - *(float *)(param_1 + 0x304) <= *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x3c) = fVar1 + FLOAT_80436acc;
  }
  else {
    *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x304) + *(float *)(param_1 + 0x38);
  }
  fVar3 = FLOAT_80436ae8;
  fVar2 = FLOAT_80436acc;
  *(float *)(param_1 + 0x2e8) =
       (FLOAT_80436acc * *(float *)(param_1 + 0x2f4) + local_18[0] + *(float *)(param_1 + 0x300)) /
       FLOAT_80436ae8;
  *(float *)(param_1 + 0x2f0) =
       (fVar2 * *(float *)(param_1 + 0x2fc) + local_10 + *(float *)(param_1 + 0x308)) / fVar3;
  *(float *)(param_1 + 0x2ec) = (fVar2 * *(float *)(param_1 + 0x2f8) + fVar1) / fVar3;
  return;
}



// ==== 8000cb8c  FUN_8000cb8c ====

void FUN_8000cb8c(int param_1,int param_2)

{
  char cVar1;
  float afStack_28 [2];
  float local_20;
  float afStack_1c [2];
  float local_14;
  
  cVar1 = *(char *)(param_1 + 0x2e6);
  if (cVar1 == '\x04') {
    if (*(char *)(param_2 + 0x7c9) == '\0') {
      if (*(int *)(param_2 + 0x508) == 0) {
        *(undefined1 *)(param_1 + 0x2e6) = 2;
        *(undefined1 *)(param_1 + 0x1b) = 0;
        *(undefined1 *)(param_1 + 0x1a) = 0;
        *(undefined1 *)(param_1 + 0x19) = 0;
      }
      else {
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x2e8),afStack_28);
        gnt4_PSVECSubtract_bl((float *)(param_2 + 0x50c),(float *)(param_1 + 0x2e8),afStack_1c);
        FUN_800452e4((double)FLOAT_80436aec,afStack_28,*(short *)(param_1 + 0x72));
        FUN_800452e4((double)FLOAT_80436aec,afStack_1c,*(short *)(param_1 + 0x72));
        zz_00453fc_('y',afStack_28,afStack_28,-*(short *)(param_1 + 0x72));
        zz_00453fc_('y',afStack_1c,afStack_1c,-*(short *)(param_1 + 0x72));
        if (local_14 < local_20) {
          *(undefined1 *)(param_1 + 0x2e6) = 3;
          *(undefined1 *)(param_1 + 0x19) = 1;
          *(undefined1 *)(param_1 + 0x1b) = 0;
          *(undefined1 *)(param_1 + 0x1a) = 0;
        }
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x2e6) = 5;
      *(undefined1 *)(param_1 + 0x1b) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined1 *)(param_1 + 0x19) = 0;
    }
  }
  else {
    if (cVar1 < '\x04') {
      if ('\x02' < cVar1) {
        if (*(char *)(param_2 + 0x7c9) == '\0') {
          if (*(int *)(param_2 + 0x508) == 0) {
            *(undefined1 *)(param_1 + 0x2e6) = 2;
            *(undefined1 *)(param_1 + 0x1b) = 0;
            *(undefined1 *)(param_1 + 0x1a) = 0;
            *(undefined1 *)(param_1 + 0x19) = 0;
            *(undefined1 *)(param_2 + 0x73c) = 0;
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x2e6) = 5;
          *(undefined1 *)(param_1 + 0x1b) = 0;
          *(undefined1 *)(param_1 + 0x1a) = 0;
          *(undefined1 *)(param_1 + 0x19) = 0;
        }
        goto LAB_8000cd7c;
      }
    }
    else if (cVar1 < '\x06') goto LAB_8000cd7c;
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x2e6) = 2;
    }
    if (*(char *)(param_2 + 0x7c9) == '\0') {
      if (*(int *)(param_2 + 0x508) != 0) {
        *(undefined1 *)(param_1 + 0x2e6) = 3;
        *(undefined1 *)(param_1 + 0x1b) = 0;
        *(undefined1 *)(param_1 + 0x1a) = 0;
        *(undefined1 *)(param_1 + 0x19) = 0;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x2e6) = 5;
      *(undefined1 *)(param_1 + 0x1b) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined1 *)(param_1 + 0x19) = 0;
    }
  }
LAB_8000cd7c:
  (*(code *)(&PTR_caseD_4_802c3894)[*(char *)(param_1 + 0x2e6)])(param_1,param_2);
  return;
}



// ==== 8000cdc0  FUN_8000cdc0 ====

/* WARNING: Removing unreachable block (ram,0x8000cf08) */
/* WARNING: Removing unreachable block (ram,0x8000cdd0) */

void FUN_8000cdc0(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_28;
  float local_24;
  float local_20;
  
  FUN_8000fc2c(param_1,param_2);
  *(undefined2 *)(param_1 + 0x70) = 0x600;
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),&local_28);
  local_24 = FLOAT_80436aa8;
  iVar4 = FUN_800452e4((double)FLOAT_80436ad8,&local_28,*(short *)(param_1 + 0x72));
  if (iVar4 == 0) {
    gnt4_PSVECNormalize_bl(&local_28,&local_28);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_28,&local_28);
  dVar7 = (double)(*(float *)(param_1 + 0x300) + local_28);
  dVar5 = zz_004526c_(*(short *)(param_1 + 0x70));
  fVar3 = FLOAT_80436af0;
  fVar2 = FLOAT_80436ae8;
  fVar1 = FLOAT_80436adc;
  dVar6 = (double)FLOAT_80436acc;
  *(float *)(param_1 + 0x318) =
       (float)(dVar6 * (double)*(float *)(param_1 + 0x318) + dVar7) / FLOAT_80436ae8;
  *(float *)(param_1 + 0x31c) =
       (fVar3 * *(float *)(param_1 + 0x31c) +
       (float)((double)*(float *)(param_1 + 0x348) * dVar5 + (double)*(float *)(param_1 + 0x304))) /
       fVar1;
  *(float *)(param_1 + 800) =
       (float)(dVar6 * (double)*(float *)(param_1 + 800) +
              (double)(*(float *)(param_1 + 0x308) + local_20)) / fVar2;
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),&local_28);
  gnt4_PSVECNormalize_bl(&local_28,&local_28);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_28,&local_28);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),&local_28,(float *)(param_1 + 0x2e8));
  FUN_800101c8(param_1,param_2);
  FUN_8001063c(param_1);
  FUN_8000fffc(param_1,param_2);
  return;
}



// ==== 8000cf28  FUN_8000cf28 ====

void FUN_8000cf28(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  double dVar4;
  float fStack_38;
  float local_34;
  float afStack_2c [3];
  float local_20;
  float local_1c;
  float local_18;
  
  FUN_8000fc2c(param_1,param_2);
  FUN_8000fe60(param_1,param_2);
  if (*(char *)(param_1 + 0x19) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined1 *)(param_2 + 0x503) = 1;
  }
  if (*(int *)(param_2 + 0x508) == 0) {
    bVar3 = true;
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300),(float *)(param_1 + 0x33c));
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x324),&fStack_38);
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300),(float *)(param_1 + 0x33c));
    local_34 = FLOAT_80436aa8;
    dVar4 = (double)FLOAT_80436af4;
    *(float *)(param_1 + 0x340) = FLOAT_80436aa8;
    bVar3 = FUN_80045460(dVar4,(float *)(param_1 + 0x33c),&fStack_38);
    if (bVar3) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
  }
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c));
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),(float *)(param_1 + 0x33c),
                      (float *)(param_1 + 0x33c));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x33c),&local_20);
  fVar2 = FLOAT_80436afc;
  fVar1 = FLOAT_80436af8;
  *(float *)(param_1 + 0x318) =
       *(float *)(param_1 + 0x318) * FLOAT_80436af8 + local_20 * FLOAT_80436afc;
  *(float *)(param_1 + 800) = *(float *)(param_1 + 800) * fVar1 + local_18 * fVar2;
  *(float *)(param_1 + 0x31c) = *(float *)(param_1 + 0x31c) * fVar1 + local_1c * fVar2;
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),afStack_2c);
  gnt4_PSVECNormalize_bl(afStack_2c,afStack_2c);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),afStack_2c,afStack_2c);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),afStack_2c,(float *)(param_1 + 0x318));
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x318);
  *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x31c);
  *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 800);
  FUN_800101c8(param_1,param_2);
  FUN_8001063c(param_1);
  FUN_8000fffc(param_1,param_2);
  if (bVar3) {
    *(undefined1 *)(param_2 + 0x503) = 0;
    *(undefined1 *)(param_2 + 0x3f1) = 1;
    *(undefined1 *)(param_1 + 0x2e6) = 4;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_2 + 0x73c) = 0;
  }
  return;
}



// ==== 8000d11c  FUN_8000d11c ====

void FUN_8000d11c(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  float afStack_28 [3];
  float local_1c;
  float local_18;
  float local_14;
  
  FUN_8000fc2c(param_1,param_2);
  FUN_8000fe60(param_1,param_2);
  if (*(int *)(param_2 + 0x508) == 0) {
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),(float *)(param_1 + 0x33c));
  }
  else {
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0x300),(float *)(param_1 + 0x324),(float *)(param_1 + 0x33c));
  }
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c));
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),(float *)(param_1 + 0x33c),
                      (float *)(param_1 + 0x33c));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x33c),&local_1c);
  fVar2 = FLOAT_80436afc;
  fVar1 = FLOAT_80436af8;
  if ((*(uint *)(param_2 + 0x5e0) & 0x100020) == 0) {
    fVar1 = FLOAT_80436b00;
    if (((*(int *)(param_2 + 0x508) != 0) &&
        (dVar3 = gnt4_PSVECMag_bl((float *)(param_1 + 0x33c)), fVar1 = FLOAT_80436b00,
        dVar3 < (double)FLOAT_80436b04)) && (fVar1 = FLOAT_80436b0c, (double)FLOAT_80436b08 < dVar3)
       ) {
      fVar1 = FLOAT_80436b10 * (float)(dVar3 - (double)FLOAT_80436b08) + FLOAT_80436b0c;
    }
    fVar2 = FLOAT_80436ac0 - fVar1;
    *(float *)(param_1 + 0x318) = *(float *)(param_1 + 0x318) * fVar2 + local_1c * fVar1;
    *(float *)(param_1 + 800) = *(float *)(param_1 + 800) * fVar2 + local_14 * fVar1;
    *(float *)(param_1 + 0x31c) = *(float *)(param_1 + 0x31c) * fVar2 + local_18 * fVar1;
  }
  else {
    *(float *)(param_1 + 0x318) =
         *(float *)(param_1 + 0x318) * FLOAT_80436af8 + local_1c * FLOAT_80436afc;
    *(float *)(param_1 + 800) = *(float *)(param_1 + 800) * fVar1 + local_14 * fVar2;
    *(float *)(param_1 + 0x31c) = *(float *)(param_1 + 0x31c) * fVar1 + local_18 * fVar2;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),afStack_28);
  gnt4_PSVECNormalize_bl(afStack_28,afStack_28);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),afStack_28,afStack_28);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),afStack_28,(float *)(param_1 + 0x2e8));
  FUN_800101c8(param_1,param_2);
  FUN_8001063c(param_1);
  FUN_8000fffc(param_1,param_2);
  return;
}



// ==== 8000d318  FUN_8000d318 ====

void FUN_8000d318(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  short sVar4;
  
  if (*(char *)(param_1 + 0x19) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    if (*(char *)(param_2 + 0x7c9) == '\x03') {
      *(undefined2 *)(param_1 + 0x1e) = 10;
    }
    else {
      *(undefined2 *)(param_1 + 0x1e) = 0x1e;
    }
    *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(param_1 + 0x1e);
  }
  else {
    if (*(char *)(param_2 + 0x7c9) != '\0') {
      *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(param_1 + 0x1e);
    }
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      *(undefined1 *)(param_1 + 0x2e6) = 2;
      *(undefined1 *)(param_1 + 0x1b) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined1 *)(param_1 + 0x19) = 0;
    }
  }
  fVar3 = FLOAT_80436af0;
  fVar2 = FLOAT_80436adc;
  fVar1 = FLOAT_80436ac4;
  *(float *)(param_1 + 0x350) =
       (*(float *)(param_2 + *(char *)(param_2 + 0x582) * 4 + 0x88c) * *(float *)(param_1 + 0x354) +
       *(float *)(param_1 + 0x350)) * FLOAT_80436ac4;
  *(float *)(param_1 + 0x300) =
       (fVar3 * *(float *)(param_1 + 0x30c) + *(float *)(param_2 + 0x20)) / fVar2;
  *(float *)(param_1 + 0x304) =
       (*(float *)(param_2 + 0x6d0) +
       *(float *)(param_1 + 0x350) + *(float *)(param_1 + 0x310) + *(float *)(param_2 + 0x24)) *
       fVar1;
  *(float *)(param_1 + 0x308) =
       (fVar3 * *(float *)(param_1 + 0x314) + *(float *)(param_2 + 0x28)) / fVar2;
  FUN_800101c8(param_1,param_2);
  FUN_8001063c(param_1);
  *(undefined1 *)(param_1 + 0x35e) = 1;
  return;
}



// ==== 8000d46c  zz_000d46c_ ====

void zz_000d46c_(undefined1 *param_1,int param_2)

{
  if ((*(byte *)(param_2 + 0x43d) == 0) && (PTR_DAT_80433934[0x1f] == '\0')) {
    *param_1 = 0;
    param_1[0x18] = 0;
    param_1[0x19] = 0;
    param_1[0x1a] = 0;
    param_1[0x1b] = 0;
    return;
  }
  if (*(char *)(param_2 + 0x3f1) == '\0') {
    *(undefined1 *)(param_2 + 0x43d) = 0;
    param_1[0x18] = 0;
    param_1[0x19] = 0;
    param_1[0x1a] = 0;
    param_1[0x1b] = 0;
  }
  else {
    if ((*(byte *)(param_2 + 0x43d) & 0x80) != 0) {
      *(byte *)(param_2 + 0x43d) = *(byte *)(param_2 + 0x43d) & 0x7f;
      param_1[0x18] = 0;
      param_1[0x19] = 0;
      param_1[0x1a] = 0;
      param_1[0x1b] = 0;
    }
    (*(code *)(&PTR_FUN_804335b0)[(char)param_1[0x18]])(param_1,param_2);
    if (*(char *)(param_2 + 0x43d) != '\0') {
      FUN_8000c314((int)param_1);
    }
  }
  return;
}



// ==== 8000d560  FUN_8000d560 ====

void FUN_8000d560(int param_1,int param_2)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  switch(*(undefined1 *)(param_2 + 0x43d)) {
  case 1:
  case 2:
    *(undefined1 *)(param_1 + 0x2e6) = 0;
    if ((*(uint *)(param_2 + 0x5e0) & 3) == 0) {
      if ((*(uint *)(param_2 + 0x5e0) & 0x1000000) == 0) {
        if (*(char *)(param_2 + 0x4a1) == '\0') {
          *(undefined1 *)(param_1 + 0x3d8) = 3;
        }
        else {
          *(undefined1 *)(param_1 + 0x3d8) = 2;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x3d8) = 1;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x3d8) = 0;
    }
    break;
  case 3:
    *(undefined1 *)(param_1 + 0x2e6) = 1;
    break;
  case 4:
    *(undefined1 *)(param_1 + 0x2e6) = 2;
    break;
  case 5:
    *(undefined1 *)(param_1 + 0x2e6) = 3;
    break;
  case 6:
    *(undefined1 *)(param_1 + 0x2e6) = 4;
    break;
  case 7:
    *(undefined1 *)(param_1 + 0x2e6) = 5;
    break;
  case 8:
    *(undefined1 *)(param_1 + 0x2e6) = 6;
    break;
  case 9:
    *(undefined1 *)(param_1 + 0x2e6) = 7;
  }
  zz_000d658_(param_1);
  return;
}



// ==== 8000d658  zz_000d658_ ====

void zz_000d658_(int param_1)

{
  (**(code **)(&DAT_802c3900 + *(char *)(param_1 + 0x2e6) * 4))();
  return;
}



// ==== 8000d990  FUN_8000d990 ====

/* WARNING: Removing unreachable block (ram,0x8000dcd0) */
/* WARNING: Removing unreachable block (ram,0x8000dcc8) */
/* WARNING: Removing unreachable block (ram,0x8000dcc0) */
/* WARNING: Removing unreachable block (ram,0x8000dabc) */
/* WARNING: Removing unreachable block (ram,0x8000d9b0) */
/* WARNING: Removing unreachable block (ram,0x8000d9a8) */
/* WARNING: Removing unreachable block (ram,0x8000d9a0) */

void FUN_8000d990(int param_1,int param_2)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double in_f29;
  double in_f30;
  double in_f31;
  
  if (*(char *)(*(int *)(param_1 + 0x3c4) + 3) == '\0') {
    if (*(char *)(*(int *)(param_1 + 0x3c4) + 4) == '\0') {
      dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_2 + 0x518),(float *)(param_2 + 0x20));
      if ((double)FLOAT_80436aa8 < dVar5) {
        dVar6 = 1.0 / SQRT(dVar5);
        dVar6 = DOUBLE_80436ab0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436ab8);
        dVar6 = DOUBLE_80436ab0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436ab8);
        dVar5 = (double)(float)(dVar5 * DOUBLE_80436ab0 * dVar6 *
                                        -(dVar5 * dVar6 * dVar6 - DOUBLE_80436ab8));
      }
      if ((double)(FLOAT_80436adc * *(float *)(param_2 + 0x770)) < dVar5) {
        return;
      }
    }
    else if ((*(byte *)(param_2 + 0x1d9) & 0x10) == 0) {
      return;
    }
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined1 *)(param_2 + 0x43d) = 2;
  iVar4 = *(int *)(param_2 + 0xcc);
  if (iVar4 != 0) {
    if (*(char *)(iVar4 + 0x83) == '\0') {
      in_f29 = (double)*(float *)(iVar4 + 0x770);
    }
    else {
      in_f29 = (double)*(float *)(param_2 + 0x770);
    }
  }
  bVar1 = *(byte *)(*(int *)(param_1 + 0x3c4) + 3);
  if (bVar1 == 1) {
    in_f31 = (double)(FLOAT_80436b18 *
                     ((FLOAT_80436b1c * *(float *)(param_2 + 0x770)) / FLOAT_80436b20));
    in_f30 = (double)(FLOAT_80436b18 *
                     ((FLOAT_80436b1c * *(float *)(param_2 + 0x668)) / FLOAT_80436b20));
  }
  else if (bVar1 == 0) {
    fVar2 = FLOAT_80436aa8;
    if (iVar4 != 0) {
      fVar2 = *(float *)(param_2 + 0x20) - *(float *)(iVar4 + 0x20);
      fVar3 = *(float *)(param_2 + 0x28) - *(float *)(iVar4 + 0x28);
      dVar5 = (double)(fVar2 * fVar2 + fVar3 * fVar3);
      if ((double)FLOAT_80436aa8 < dVar5) {
        dVar6 = 1.0 / SQRT(dVar5);
        dVar6 = DOUBLE_80436ab0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436ab8);
        dVar6 = DOUBLE_80436ab0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436ab8);
        dVar5 = (double)(float)(dVar5 * DOUBLE_80436ab0 * dVar6 *
                                        -(dVar5 * dVar6 * dVar6 - DOUBLE_80436ab8));
      }
      dVar6 = (double)FLOAT_80436ac4;
      fVar2 = FLOAT_80436b18 *
              ((float)((double)(float)((double)FLOAT_80436b1c * (double)(float)(in_f29 * dVar6) +
                                      (double)(float)((double)FLOAT_80436b1c *
                                                      (double)(float)((double)*(float *)(param_2 +
                                                                                        0x770) *
                                                                     dVar6) + dVar5)) * dVar6) /
              FLOAT_80436b20);
    }
    in_f31 = (double)fVar2;
    in_f30 = (double)(FLOAT_80436b18 *
                     ((FLOAT_80436b1c * *(float *)(param_2 + 0x668)) / FLOAT_80436b20));
  }
  else if (bVar1 < 3) {
    if (iVar4 == 0) {
      zz_000df08_(param_1,param_2);
      return;
    }
    in_f31 = (double)(FLOAT_80436b18 *
                     ((FLOAT_80436b1c * *(float *)(param_2 + 0x770)) / FLOAT_80436b20));
    in_f30 = (double)(FLOAT_80436b18 *
                     ((FLOAT_80436b1c * *(float *)(param_2 + 0x668)) / FLOAT_80436b20));
  }
  if (in_f31 < in_f30) {
    *(float *)(param_1 + 0x348) = (float)in_f30;
  }
  else {
    *(float *)(param_1 + 0x348) = (float)in_f31;
  }
  fVar2 = FLOAT_80436ac0;
  *(float *)(param_1 + 0x3cc) = (float)(in_f30 * (double)FLOAT_80436ac4);
  fVar2 = fVar2 / *(float *)(param_1 + 0x354);
  *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x348) * fVar2;
  *(float *)(param_1 + 0x3cc) = *(float *)(param_1 + 0x3cc) * fVar2;
  *(float *)(param_1 + 0x348) =
       *(float *)(param_1 + 0x348) * *(float *)(*(int *)(param_1 + 0x3c4) + 0x10);
  if (*(float *)(param_1 + 0x348) < *(float *)(param_1 + 0x3cc)) {
    *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x3cc);
  }
  *(float *)(param_1 + 0x34c) =
       (*(float *)(param_1 + 0x348) / FLOAT_80436b24) * *(float *)(*(int *)(param_1 + 0x3c4) + 0x14)
  ;
  zz_000df28_(param_1,param_2,(float *)(param_1 + 0x300),(float *)(param_1 + 0x2e8),1);
  return;
}



// ==== 8000dcf0  FUN_8000dcf0 ====

/* WARNING: Removing unreachable block (ram,0x8000ddc4) */

void FUN_8000dcf0(int param_1,int param_2)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  *(undefined4 *)(param_1 + 0x30c) = *(undefined4 *)(param_1 + 0x300);
  *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_1 + 0x304);
  *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(param_1 + 0x308);
  *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0x2e8);
  *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x2ec);
  *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0x2f0);
  zz_000df28_(param_1,param_2,&local_38,&local_2c,0);
  fVar3 = FLOAT_80436ae8;
  fVar2 = FLOAT_80436acc;
  *(float *)(param_1 + 0x2e8) =
       (FLOAT_80436acc * *(float *)(param_1 + 0x2f4) + local_2c) / FLOAT_80436ae8;
  *(float *)(param_1 + 0x2f0) = (fVar2 * *(float *)(param_1 + 0x2fc) + local_24) / fVar3;
  *(float *)(param_1 + 0x2ec) = (fVar2 * *(float *)(param_1 + 0x2f8) + local_28) / fVar3;
  *(float *)(param_1 + 0x300) = local_38;
  *(undefined4 *)(param_1 + 0x304) = local_34;
  *(undefined4 *)(param_1 + 0x308) = local_30;
  bVar1 = *(byte *)(*(int *)(param_1 + 0x3c4) + 3);
  if (bVar1 == 1) {
    local_20 = *(float *)(param_2 + 0x20);
    local_1c = *(undefined4 *)(param_1 + 0x304);
    local_18 = *(undefined4 *)(param_2 + 0x28);
    iVar4 = zz_00105b4_((int)*(char *)(param_1 + 0x10),&local_20);
    if (iVar4 == 0) {
      zz_000df08_(param_1,param_2);
    }
  }
  else if (bVar1 == 0) {
    local_20 = *(float *)(param_2 + 0x20);
    local_1c = *(undefined4 *)(param_1 + 0x304);
    local_18 = *(undefined4 *)(param_2 + 0x28);
    iVar4 = zz_00105b4_((int)*(char *)(param_1 + 0x10),&local_20);
    if (iVar4 == 0) {
      zz_000df08_(param_1,param_2);
    }
    else if (*(int *)(param_2 + 0xcc) == 0) {
      zz_000df08_(param_1,param_2);
    }
    else {
      local_20 = *(float *)(param_2 + 0x518);
      local_1c = *(undefined4 *)(param_1 + 0x304);
      local_18 = *(undefined4 *)(param_2 + 0x520);
      iVar4 = zz_00105b4_((int)*(char *)(param_1 + 0x10),&local_20);
      if (iVar4 == 0) {
        zz_000df08_(param_1,param_2);
      }
    }
  }
  else if (bVar1 < 3) {
    if (*(int *)(param_2 + 0xcc) == 0) {
      zz_000df08_(param_1,param_2);
    }
    else {
      iVar4 = zz_00105b4_((int)*(char *)(param_1 + 0x10),(float *)(param_2 + 0x518));
      if (iVar4 == 0) {
        zz_000df08_(param_1,param_2);
      }
    }
  }
  return;
}



// ==== 8000df08  zz_000df08_ ====

void zz_000df08_(int param_1,int param_2)

{
  *(undefined1 *)(param_1 + 0x18) = 0;
  *(undefined1 *)(param_1 + 0x19) = 0;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  *(undefined1 *)(param_2 + 0x43d) = 0;
  *(undefined1 *)(param_2 + 0x6f8) = 0;
  return;
}



// ==== 8000df28  zz_000df28_ ====

/* WARNING: Removing unreachable block (ram,0x8000e270) */
/* WARNING: Removing unreachable block (ram,0x8000df70) */
/* WARNING: Removing unreachable block (ram,0x8000df38) */

void zz_000df28_(int param_1,int param_2,float *param_3,float *param_4,int param_5)

{
  byte bVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_48;
  float local_44;
  float local_40;
  undefined4 local_38;
  uint uStack_34;
  longlong local_30;
  
  fVar2 = FLOAT_80436b28;
  bVar1 = *(byte *)(*(int *)(param_1 + 0x3c4) + 3);
  if (bVar1 == 1) {
    *param_3 = *(float *)(param_2 + 0x20);
    param_3[1] = fVar2 * *(float *)(param_2 + 0x668) + *(float *)(param_2 + 0x24);
    param_3[2] = *(float *)(param_2 + 0x28);
    local_48 = *(float *)(param_2 + 0x8dc);
    local_44 = *(float *)(param_2 + 0x8ec);
    local_40 = *(float *)(param_2 + 0x8fc);
  }
  else if (bVar1 == 0) {
    if (*(int *)(param_2 + 0xcc) == 0) {
      fVar2 = *(float *)(param_1 + 0x304);
      *param_3 = *(float *)(param_1 + 0x300);
      param_3[1] = fVar2;
      param_3[2] = *(float *)(param_1 + 0x308);
      local_48 = *(float *)(param_2 + 0x8dc);
      local_44 = *(float *)(param_2 + 0x8ec);
      local_40 = *(float *)(param_2 + 0x8fc);
    }
    else {
      *param_3 = *(float *)(param_2 + 0x20);
      param_3[1] = fVar2 * *(float *)(param_2 + 0x668) + *(float *)(param_2 + 0x24);
      param_3[2] = *(float *)(param_2 + 0x28);
      gnt4_PSVECSubtract_bl((float *)(param_2 + 0x518),param_3,&local_48);
      local_44 = FLOAT_80436aa8;
      gnt4_PSQUATScale_bl((double)FLOAT_80436ac4,&local_48,&local_48);
      gnt4_PSVECAdd_bl(param_3,&local_48,param_3);
      FUN_800452e4((double)FLOAT_80436aec,&local_48,*(short *)(param_2 + 0x72));
    }
  }
  else if (bVar1 < 3) {
    iVar3 = *(int *)(param_2 + 0xcc);
    if (iVar3 == 0) {
      *param_3 = *(float *)(param_2 + 0x20);
      param_3[1] = fVar2 * *(float *)(param_2 + 0x668) + *(float *)(param_2 + 0x24);
      param_3[2] = *(float *)(param_2 + 0x28);
      local_48 = *(float *)(param_2 + 0x8dc);
      local_44 = *(float *)(param_2 + 0x8ec);
      local_40 = *(float *)(param_2 + 0x8fc);
    }
    else if (*(char *)(iVar3 + 0x83) == '\0') {
      *param_3 = *(float *)(iVar3 + 0x20);
      param_3[1] = fVar2 * *(float *)(iVar3 + 0x668) + *(float *)(iVar3 + 0x24);
      param_3[2] = *(float *)(iVar3 + 0x28);
      local_48 = *(float *)(param_2 + 0x8dc);
      local_44 = *(float *)(param_2 + 0x8ec);
      local_40 = *(float *)(param_2 + 0x8fc);
    }
    else {
      fVar2 = *(float *)(param_2 + 0x51c);
      *param_3 = *(float *)(param_2 + 0x518);
      param_3[1] = fVar2;
      param_3[2] = *(float *)(param_2 + 0x520);
      local_48 = *(float *)(iVar3 + 0x11c);
      local_44 = *(float *)(iVar3 + 300);
      local_40 = *(float *)(iVar3 + 0x13c);
    }
  }
  if (param_5 == 0) {
    local_38 = 0x43300000;
    uStack_34 = (int)*(short *)(param_1 + 0x3d6) ^ 0x80000000;
    iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80436b30) *
                 *(float *)(param_2 + 0x1dc8));
    local_30 = (longlong)iVar3;
    zz_00453fc_('y',(float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c),(short)iVar3);
  }
  else {
    zz_00453fc_('y',&local_48,(float *)(param_1 + 0x33c),*(short *)(param_1 + 0x3d4));
  }
  local_48 = *(float *)(param_1 + 0x33c);
  local_44 = *(float *)(param_1 + 0x340);
  local_40 = *(float *)(param_1 + 0x344);
  dVar4 = zz_004526c_(*(short *)(*(int *)(param_1 + 0x3c4) + 8));
  dVar5 = gnt4_PSVECMag_bl(&local_48);
  local_44 = (float)(dVar5 * dVar4 + (double)local_44);
  gnt4_PSVECNormalize_bl(&local_48,&local_48);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_48,&local_48);
  gnt4_PSVECAdd_bl(param_3,&local_48,param_4);
  *(float *)(param_1 + 0x348) =
       *(float *)(param_1 + 0x34c) * *(float *)(param_2 + 0x1dc8) + *(float *)(param_1 + 0x348);
  if (*(float *)(param_1 + 0x348) < *(float *)(param_1 + 0x3cc)) {
    *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x3cc);
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x2e8),&local_48);
  FUN_800452e4((double)FLOAT_80436ad8,&local_48,*(short *)(param_1 + 0x72));
  iVar3 = FUN_800452a0(-(double)local_44,(double)*(float *)(param_1 + 0x348));
  *(short *)(param_1 + 0x70) = (short)iVar3;
  iVar3 = FUN_800452a0((double)local_48,(double)local_40);
  *(short *)(param_1 + 0x72) = (short)iVar3;
  return;
}



// ==== 8000e28c  FUN_8000e28c ====

void FUN_8000e28c(int param_1)

{
  (*(code *)(&PTR_FUN_804335b8)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 8000e2c4  FUN_8000e2c4 ====

void FUN_8000e2c4(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  float local_18;
  float local_14;
  undefined4 local_10;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  iVar5 = *(int *)(PTR_DAT_80433934 + 0xb8);
  if (iVar5 == 0) {
    *(int *)(param_1 + 0x3c8) = param_2;
    iVar5 = param_2;
  }
  else {
    *(int *)(param_1 + 0x3c8) = iVar5;
  }
  iVar6 = *(int *)(PTR_DAT_80433934 + 0xb4);
  if (iVar6 == 0) {
    *(int *)(param_1 + 0x3c4) = iVar5;
    iVar6 = iVar5;
  }
  else {
    *(int *)(param_1 + 0x3c4) = iVar6;
  }
  fVar1 = FLOAT_80436ac4;
  *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(iVar5 + 0x8a0);
  fVar4 = FLOAT_80436b20;
  fVar3 = FLOAT_80436b1c;
  fVar2 = FLOAT_80436b18;
  *(float *)(param_1 + 0x350) =
       fVar1 * *(float *)(iVar5 + *(char *)(param_2 + 0x582) * 4 + 0x88c) *
       (*(float *)(iVar5 + 0x668) / *(float *)(*(int *)(iVar5 + 0x4b0) + 0x4c));
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(iVar5 + 0x20);
  *(float *)(param_1 + 0x304) = *(float *)(iVar5 + 0x24) + *(float *)(param_1 + 0x350);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(iVar5 + 0x28);
  *(float *)(param_1 + 0x348) = fVar2 * ((fVar3 * *(float *)(iVar5 + 0x668)) / fVar4);
  if (iVar6 == 0) {
    local_18 = *(float *)(param_2 + 0x8dc);
    local_10 = *(undefined4 *)(param_2 + 0x8fc);
    local_14 = FLOAT_80436aa8;
    FUN_800452e4((double)FLOAT_80436aec,&local_18,*(short *)(iVar5 + 0x72));
    zz_00453fc_('y',&local_18,&local_18,0x4000);
    gnt4_PSVECNormalize_bl(&local_18,&local_18);
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_18,&local_18);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),&local_18,(float *)(param_1 + 0x2e8));
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(iVar6 + 0x20),(float *)(iVar5 + 0x20),&local_18);
    local_14 = FLOAT_80436aa8;
    gnt4_PSQUATScale_bl((double)FLOAT_80436ac4,&local_18,&local_18);
    FUN_800452e4((double)FLOAT_80436aec,&local_18,*(short *)(iVar5 + 0x72));
    zz_00453fc_('y',&local_18,&local_18,0x4000);
    gnt4_PSVECNormalize_bl(&local_18,&local_18);
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_18,&local_18);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),&local_18,(float *)(param_1 + 0x2e8));
  }
  *(undefined4 *)(param_1 + 0x30c) = *(undefined4 *)(param_1 + 0x300);
  *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_1 + 0x304);
  *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(param_1 + 0x308);
  *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0x2e8);
  *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x2ec);
  *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0x2f0);
  return;
}



// ==== 8000e4f4  FUN_8000e4f4 ====

void FUN_8000e4f4(int param_1)

{
  *(undefined4 *)(param_1 + 0x30c) = *(undefined4 *)(param_1 + 0x300);
  *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_1 + 0x304);
  *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(param_1 + 0x308);
  *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0x2e8);
  *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x2ec);
  *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0x2f0);
  (*(code *)(&PTR_FUN_802c392c)[*(char *)(param_1 + 0x1a)])();
  return;
}



// ==== 8000e560  FUN_8000e560 ====

void FUN_8000e560(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  
  fVar4 = FLOAT_80436ae8;
  fVar3 = FLOAT_80436acc;
  if (PTR_DAT_80433934[0x52] == '\x04') {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined1 *)(param_1 + 0x1b) = 0;
    zz_000e5f8_(param_1,param_2);
  }
  else {
    iVar5 = *(int *)(param_1 + 0x3c8);
    fVar1 = *(float *)(iVar5 + 0x24);
    fVar2 = *(float *)(iVar5 + 0x28);
    *(float *)(param_1 + 0x300) =
         (FLOAT_80436acc * *(float *)(param_1 + 0x30c) + *(float *)(iVar5 + 0x20)) / FLOAT_80436ae8;
    *(float *)(param_1 + 0x308) = (fVar3 * *(float *)(param_1 + 0x314) + fVar2) / fVar4;
    *(float *)(param_1 + 0x304) =
         (fVar3 * *(float *)(param_1 + 0x310) + fVar1 + *(float *)(param_1 + 0x350)) / fVar4;
  }
  return;
}



// ==== 8000e5f8  zz_000e5f8_ ====

void zz_000e5f8_(int param_1,int param_2)

{
  float fVar1;
  short sVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float afStack_54 [3];
  float local_48;
  float local_44;
  float local_40;
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
  undefined4 local_10;
  uint uStack_c;
  
  iVar3 = *(int *)(param_1 + 0x3c4);
  if (*(char *)(param_1 + 0x1b) == '\0') {
    *(undefined1 *)(param_1 + 0x1b) = 1;
    fVar1 = FLOAT_80436b28;
    *(undefined2 *)(param_1 + 0x1c) = 0x28;
    *(float *)(param_1 + 0x350) =
         fVar1 * *(float *)(iVar3 + *(char *)(param_2 + 0x582) * 4 + 0x88c) *
         (*(float *)(iVar3 + 0x668) / *(float *)(*(int *)(iVar3 + 0x4b0) + 0x4c));
    local_48 = *(float *)(iVar3 + 0x20);
    local_44 = *(float *)(iVar3 + 0x24) + *(float *)(param_1 + 0x350);
    local_40 = *(float *)(iVar3 + 0x28);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x300),&local_48,afStack_54);
    dVar4 = gnt4_PSVECMag_bl(afStack_54);
    if ((double)*(float *)(param_2 + 0x894) <= dVar4) {
      *(undefined4 *)(param_1 + 0x3cc) = *(undefined4 *)(param_1 + 0x300);
      *(undefined4 *)(param_1 + 0x3d0) = *(undefined4 *)(param_1 + 0x304);
      *(undefined4 *)(param_1 + 0x3d4) = *(undefined4 *)(param_1 + 0x308);
    }
    else {
      gnt4_PSVECNormalize_bl(afStack_54,afStack_54);
      gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x894),afStack_54,afStack_54);
      gnt4_PSVECAdd_bl(&local_48,afStack_54,(float *)(param_1 + 0x3cc));
      zz_0010664_(param_1);
    }
  }
  else {
    local_48 = *(float *)(iVar3 + 0x20);
    local_44 = *(float *)(iVar3 + 0x24) + *(float *)(param_1 + 0x350);
    local_40 = *(float *)(iVar3 + 0x28);
  }
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  dVar4 = DOUBLE_80436b30;
  if (sVar2 == 0) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x3cc);
    *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x3d0);
    *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x3d4);
    *(float *)(param_1 + 0x300) = local_48;
    *(float *)(param_1 + 0x304) = local_44;
    *(float *)(param_1 + 0x308) = local_40;
  }
  else {
    local_38 = 0x43300000;
    uStack_34 = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    local_30 = 0x43300000;
    local_28 = 0x43300000;
    local_20 = 0x43300000;
    local_18 = 0x43300000;
    local_10 = 0x43300000;
    *(float *)(param_1 + 0x2e8) =
         *(float *)(param_1 + 0x2f4) +
         (*(float *)(param_1 + 0x3cc) - *(float *)(param_1 + 0x2f4)) /
         (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80436b30);
    uStack_2c = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    *(float *)(param_1 + 0x2ec) =
         *(float *)(param_1 + 0x2f8) +
         (*(float *)(param_1 + 0x3d0) - *(float *)(param_1 + 0x2f8)) /
         (float)((double)CONCAT44(0x43300000,uStack_2c) - dVar4);
    uStack_24 = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    *(float *)(param_1 + 0x2f0) =
         *(float *)(param_1 + 0x2fc) +
         (*(float *)(param_1 + 0x3d4) - *(float *)(param_1 + 0x2fc)) /
         (float)((double)CONCAT44(0x43300000,uStack_24) - dVar4);
    uStack_1c = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    *(float *)(param_1 + 0x300) =
         *(float *)(param_1 + 0x30c) +
         (local_48 - *(float *)(param_1 + 0x30c)) /
         (float)((double)CONCAT44(0x43300000,uStack_1c) - dVar4);
    uStack_14 = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    *(float *)(param_1 + 0x304) =
         *(float *)(param_1 + 0x310) +
         (local_44 - *(float *)(param_1 + 0x310)) /
         (float)((double)CONCAT44(0x43300000,uStack_14) - dVar4);
    uStack_c = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    *(float *)(param_1 + 0x308) =
         *(float *)(param_1 + 0x314) +
         (local_40 - *(float *)(param_1 + 0x314)) /
         (float)((double)CONCAT44(0x43300000,uStack_c) - dVar4);
  }
  zz_00106fc_(param_1,param_2,(float *)(param_1 + 0x2e8));
  dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
  if ((double)FLOAT_80436aa8 < dVar4) {
    dVar5 = 1.0 / SQRT(dVar4);
    dVar5 = DOUBLE_80436ab0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8);
    dVar5 = DOUBLE_80436ab0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8);
    dVar4 = (double)(float)(dVar4 * DOUBLE_80436ab0 * dVar5 *
                                    -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8));
  }
  *(float *)(param_1 + 0x348) = (float)dVar4;
  return;
}



// ==== 8000e950  FUN_8000e950 ====

/* WARNING: Removing unreachable block (ram,0x8000ead4) */
/* WARNING: Removing unreachable block (ram,0x8000eacc) */
/* WARNING: Removing unreachable block (ram,0x8000e968) */
/* WARNING: Removing unreachable block (ram,0x8000e960) */

void FUN_8000e950(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float afStack_44 [3];
  float local_38;
  float local_34;
  float local_30;
  
  iVar3 = *(int *)(param_1 + 0x3c4);
  dVar4 = (double)*(float *)(iVar3 + 0x898);
  dVar5 = (double)*(float *)(iVar3 + 0x894);
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(iVar3 + 0x20);
  *(float *)(param_1 + 0x304) = *(float *)(iVar3 + 0x24) + *(float *)(param_1 + 0x350);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(iVar3 + 0x28);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300),afStack_44);
  gnt4_PSVECNormalize_bl(afStack_44,afStack_44);
  gnt4_PSQUATScale_bl(dVar5,afStack_44,afStack_44);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),afStack_44,&local_38);
  if ((*(char *)(param_1 + 0x1b) != '\0') || ((double)*(float *)(param_1 + 0x348) < dVar4)) {
    *(undefined1 *)(param_1 + 0x1b) = 1;
    zz_0010664_(param_1);
  }
  fVar2 = FLOAT_80436ae8;
  fVar1 = FLOAT_80436acc;
  *(float *)(param_1 + 0x2e8) =
       (FLOAT_80436acc * *(float *)(param_1 + 0x2f4) + local_38) / FLOAT_80436ae8;
  *(float *)(param_1 + 0x2f0) = (fVar1 * *(float *)(param_1 + 0x2fc) + local_30) / fVar2;
  *(float *)(param_1 + 0x2ec) = (fVar1 * *(float *)(param_1 + 0x2f8) + local_34) / fVar2;
  zz_00106fc_(param_1,param_2,(float *)(param_1 + 0x2e8));
  dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
  if ((double)FLOAT_80436aa8 < dVar4) {
    dVar5 = 1.0 / SQRT(dVar4);
    dVar5 = DOUBLE_80436ab0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8);
    dVar5 = DOUBLE_80436ab0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8);
    dVar4 = (double)(float)(dVar4 * DOUBLE_80436ab0 * dVar5 *
                                    -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8));
  }
  *(float *)(param_1 + 0x348) = (float)dVar4;
  return;
}



// ==== 8000eaf4  FUN_8000eaf4 ====

void FUN_8000eaf4(int param_1)

{
  (*(code *)(&PTR_FUN_804335c0)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 8000eb2c  FUN_8000eb2c ====

void FUN_8000eb2c(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  iVar6 = *(int *)(param_2 + 0x4ac);
  fVar1 = *(float *)(iVar6 + 400) *
          (*(float *)(param_2 + 0x668) / *(float *)(*(int *)(param_2 + 0x4b0) + 0x4c));
  *(float *)(param_1 + 0x3d4) = fVar1;
  fVar4 = FLOAT_80436b40;
  fVar3 = FLOAT_80436b38;
  fVar2 = FLOAT_80436ac4;
  if (((int)(char)PTR_DAT_80433934[0x1f] & 1 << (int)*(char *)(param_2 + 0x88)) == 0) {
    if (*(char *)(param_2 + 0x18) == '\x01') {
      fVar2 = FLOAT_80436b38 * fVar1;
      *(undefined1 *)(param_1 + 0x1a) = 1;
      fVar5 = FLOAT_80436b48;
      fVar3 = FLOAT_80436b44;
      *(float *)(param_1 + 0x350) = fVar2;
      *(float *)(param_1 + 0x3d8) = fVar4 * fVar1;
      *(float *)(param_1 + 0x3d0) = fVar3 * fVar1;
      *(undefined2 *)(param_1 + 0x3e2) = 0;
      *(undefined2 *)(param_1 + 0x3e0) = 0;
      *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(iVar6 + 0x194);
      *(undefined4 *)(param_1 + 0x3dc) = *(undefined4 *)(iVar6 + 0x198);
      *(float *)(param_1 + 0x34c) =
           (*(float *)(param_1 + 0x3dc) - *(float *)(param_1 + 0x348)) / fVar5;
    }
    else {
      *(undefined1 *)(param_1 + 0x1a) = 2;
      fVar2 = FLOAT_80436aa8;
      *(float *)(param_1 + 0x350) = fVar3 * fVar1;
      *(float *)(param_1 + 0x3d8) = fVar2;
      *(float *)(param_1 + 0x3d0) = fVar3 * fVar1;
      *(undefined2 *)(param_1 + 0x3e2) = 0;
      *(undefined2 *)(param_1 + 0x3e0) = 0;
      *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(iVar6 + 0x194);
      *(undefined4 *)(param_1 + 0x3dc) = *(undefined4 *)(iVar6 + 0x198);
      *(float *)(param_1 + 0x34c) = fVar2;
    }
  }
  else {
    fVar3 = FLOAT_80436b38 * fVar1;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(float *)(param_1 + 0x350) = fVar3;
    *(float *)(param_1 + 0x3d8) = fVar1;
    *(float *)(param_1 + 0x3d0) = fVar2 * fVar1;
    if ((*(uint *)(PTR_DAT_80433934 + 0xac) & 1) == 0) {
      *(undefined2 *)(param_1 + 0x3e0) = *(undefined2 *)(iVar6 + 0x19e);
    }
    else {
      *(undefined2 *)(param_1 + 0x3e0) = *(undefined2 *)(iVar6 + 0x19c);
    }
    if (*(short *)(param_1 + 0x3e0) < 0) {
      *(undefined2 *)(param_1 + 0x3e2) = 0x7800;
    }
    else {
      *(undefined2 *)(param_1 + 0x3e2) = 0x8800;
    }
    fVar1 = FLOAT_80436ac4;
    *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(iVar6 + 0x194);
    fVar2 = FLOAT_80436b3c;
    *(float *)(param_1 + 0x3dc) = *(float *)(iVar6 + 0x198) * fVar1;
    *(float *)(param_1 + 0x34c) =
         (*(float *)(param_1 + 0x3dc) - *(float *)(param_1 + 0x348)) / fVar2;
  }
  FUN_8000ee04(param_1,param_2);
  return;
}



// ==== 8000ece4  FUN_8000ece4 ====

void FUN_8000ece4(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  
  *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x348) + *(float *)(param_1 + 0x34c);
  if (*(float *)(param_1 + 0x348) < *(float *)(param_1 + 0x3dc)) {
    *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x3dc);
  }
  fVar2 = FLOAT_80436b50;
  fVar4 = FLOAT_80436b4c;
  dVar3 = DOUBLE_80436b30;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x01') {
    *(float *)(param_1 + 0x3d8) =
         FLOAT_80436ac4 * *(float *)(param_2 + 0x7fc) + *(float *)(param_1 + 0x3d8);
    fVar2 = fVar2 * *(float *)(param_1 + 0x3d4);
    if (fVar2 < *(float *)(param_1 + 0x3d8)) {
      *(float *)(param_1 + 0x3d8) = fVar2;
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(float *)(param_1 + 0x3d8) = *(float *)(param_1 + 0x3d8) * FLOAT_80436b4c;
      *(short *)(param_1 + 0x3e2) =
           (short)(int)(fVar4 * (float)((double)CONCAT44(0x43300000,
                                                         (int)*(short *)(param_1 + 0x3e2) ^
                                                         0x80000000) - dVar3));
    }
  }
  else if (cVar1 < '\x03') {
    *(float *)(param_1 + 0x3d8) =
         FLOAT_80436b54 * *(float *)(param_2 + 0x7fc) + *(float *)(param_1 + 0x3d8);
    if (*(float *)(param_1 + 0x3d4) < *(float *)(param_1 + 0x3d8)) {
      *(float *)(param_1 + 0x3d8) = *(float *)(param_1 + 0x3d4);
    }
    *(short *)(param_1 + 0x3e2) = *(short *)(param_1 + 0x3e2) + 0x10;
  }
  FUN_8000ee04(param_1,param_2);
  return;
}



// ==== 8000ee04  FUN_8000ee04 ====

/* WARNING: Removing unreachable block (ram,0x8000eec8) */
/* WARNING: Removing unreachable block (ram,0x8000ee14) */

void FUN_8000ee04(int param_1,int param_2)

{
  undefined4 uVar1;
  short sVar2;
  double dVar3;
  double dVar4;
  
  uVar1 = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x2e8) = uVar1;
  *(undefined4 *)(param_1 + 0x300) = uVar1;
  uVar1 = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)(param_1 + 0x2ec) = uVar1;
  *(undefined4 *)(param_1 + 0x304) = uVar1;
  uVar1 = *(undefined4 *)(param_2 + 0x28);
  *(undefined4 *)(param_1 + 0x2f0) = uVar1;
  *(undefined4 *)(param_1 + 0x308) = uVar1;
  *(float *)(param_1 + 0x304) = *(float *)(param_1 + 0x304) + *(float *)(param_1 + 0x350);
  dVar4 = (double)(*(float *)(param_1 + 0x348) * *(float *)(param_1 + 0x354));
  sVar2 = *(short *)(param_2 + 0x72) + *(short *)(param_1 + 0x3e0) + *(short *)(param_1 + 0x3e2);
  dVar3 = zz_0045204_(sVar2);
  *(float *)(param_1 + 0x2e8) = (float)(dVar4 * dVar3 + (double)*(float *)(param_1 + 0x2e8));
  *(float *)(param_1 + 0x2ec) =
       *(float *)(param_1 + 0x2ec) +
       *(float *)(param_1 + 0x3d8) * *(float *)(param_1 + 0x354) + *(float *)(param_1 + 0x3d0);
  dVar3 = zz_0045238_(sVar2);
  *(float *)(param_1 + 0x2f0) = (float)(dVar4 * dVar3 + (double)*(float *)(param_1 + 0x2f0));
  zz_0010664_(param_1);
  return;
}



// ==== 8000eee8  FUN_8000eee8 ====

void FUN_8000eee8(int param_1)

{
  (*(code *)(&PTR_FUN_804335c8)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 8000ef20  FUN_8000ef20 ====

void FUN_8000ef20(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  if (*(char *)(param_1 + 0x12) != '\0') {
    zz_008b038_('\x02');
  }
  PTR_DAT_80433934[0x1829] = 1;
  FUN_801fe050(0);
  iVar2 = (int)*(char *)(param_2 + 0x3e4);
  *(undefined2 *)(param_1 + 0x1c) = 0x1e;
  uVar1 = (&DAT_803c769c)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x2f4) = (&DAT_803c7698)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x2f8) = uVar1;
  *(undefined4 *)(param_1 + 0x2fc) = (&DAT_803c76a0)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x2f4);
  *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x2f8);
  *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x2fc);
  uVar1 = (&DAT_803c76b4)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x30c) = (&DAT_803c76b0)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x310) = uVar1;
  *(undefined4 *)(param_1 + 0x314) = (&DAT_803c76b8)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_1 + 0x30c);
  *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(param_1 + 0x310);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_1 + 0x314);
  uVar1 = (&DAT_803c76e4)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x330) = (&DAT_803c76e0)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x334) = uVar1;
  *(undefined4 *)(param_1 + 0x338) = (&DAT_803c76e8)[iVar2 * 0xf9];
  FUN_8000f02c(param_1,param_2);
  return;
}



// ==== 8000f02c  FUN_8000f02c ====

void FUN_8000f02c(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  short sVar5;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  if (*(char *)(*(int *)(param_1 + 0xcc) + 0x18) != '\x01') {
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_2 + 0x43d) = 0;
    *(undefined1 *)(param_2 + 0x6f8) = 0;
    if (*(char *)(param_1 + 0x12) != '\0') {
      zz_008b038_('\0');
    }
    PTR_DAT_80433934[0x1829] = 0;
    FUN_801fe134();
    zz_0066350_((int)(char)PTR_DAT_80433930[2]);
    return;
  }
  iVar4 = *(int *)(param_1 + 0xcc) + *(char *)(param_1 + 0x89) * 0x30;
  local_18 = *(float *)(iVar4 + 0x8e0);
  local_14 = *(undefined4 *)(iVar4 + 0x8f0);
  local_10 = *(undefined4 *)(iVar4 + 0x900);
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x03') {
LAB_8000f22c:
    sVar5 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar5;
    fVar2 = FLOAT_80436adc;
    if (0 < sVar5) {
      return;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(float *)(param_1 + 0xd4) = fVar2;
  }
  else {
    if (cVar1 < '\x03') {
      if (cVar1 == '\x01') {
LAB_8000f138:
        zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),&local_18,
                    (float *)(param_1 + 0x300),(float *)(param_1 + 0x300));
        fVar2 = FLOAT_80436aa8;
        *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - FLOAT_80436ac0;
        fVar3 = FLOAT_80436adc;
        if (fVar2 < *(float *)(param_1 + 0xd4)) {
          return;
        }
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(float *)(param_1 + 0xd4) = fVar3;
        *(float *)(param_1 + 0x300) = local_18;
        *(undefined4 *)(param_1 + 0x304) = local_14;
        *(undefined4 *)(param_1 + 0x308) = local_10;
        gnt4_PSVECSubtract_bl
                  ((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300),(float *)(param_1 + 0x38));
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x38));
      }
      else if (cVar1 < '\x01') {
        if (cVar1 < '\0') {
          return;
        }
        sVar5 = *(short *)(param_1 + 0x1c) + -1;
        *(short *)(param_1 + 0x1c) = sVar5;
        fVar2 = FLOAT_80436adc;
        if (0 < sVar5) {
          return;
        }
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(float *)(param_1 + 0xd4) = fVar2;
        goto LAB_8000f138;
      }
      zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),(float *)(param_1 + 0x38),
                  (float *)(param_1 + 0x2e8),(float *)(param_1 + 0x2e8));
      fVar2 = FLOAT_80436aa8;
      *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - FLOAT_80436ac0;
      if (fVar2 < *(float *)(param_1 + 0xd4)) {
        return;
      }
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(param_1 + 0x1e);
      goto LAB_8000f22c;
    }
    if (cVar1 == '\x05') goto LAB_8000f2f0;
    if ('\x04' < cVar1) {
      return;
    }
  }
  zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),(float *)(param_1 + 0x2f4),
              (float *)(param_1 + 0x2e8),(float *)(param_1 + 0x2e8));
  zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),(float *)(param_1 + 0x30c),
              (float *)(param_1 + 0x300),(float *)(param_1 + 0x300));
  fVar2 = FLOAT_80436aa8;
  *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - FLOAT_80436ac0;
  if (fVar2 < *(float *)(param_1 + 0xd4)) {
    return;
  }
  *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x2f4);
  *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x2f8);
  *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x2fc);
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_1 + 0x30c);
  *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(param_1 + 0x310);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_1 + 0x314);
  *(undefined2 *)(param_1 + 0x1c) = 2;
LAB_8000f2f0:
  sVar5 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar5;
  if (sVar5 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_2 + 0x43d) = 0;
    *(undefined1 *)(param_2 + 0x6f8) = 0;
    if (*(char *)(param_1 + 0x12) != '\0') {
      zz_008b038_('\0');
    }
    PTR_DAT_80433934[0x1829] = 0;
    FUN_801fe134();
    zz_0066350_((int)(char)PTR_DAT_80433930[2]);
  }
  return;
}



// ==== 8000f36c  FUN_8000f36c ====

void FUN_8000f36c(int param_1)

{
  (*(code *)(&PTR_FUN_804335d0)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 8000f3a4  FUN_8000f3a4 ====

void FUN_8000f3a4(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  
  fVar2 = FLOAT_80436ae8;
  cVar1 = *(char *)(param_2 + 0x3e4);
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  iVar4 = (int)cVar1;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(float *)(param_1 + 0x3d0) = fVar2;
  uVar3 = (&DAT_803c76e4)[iVar4 * 0xf9];
  *(undefined4 *)(param_1 + 0x330) = (&DAT_803c76e0)[iVar4 * 0xf9];
  *(undefined4 *)(param_1 + 0x334) = uVar3;
  *(undefined4 *)(param_1 + 0x338) = (&DAT_803c76e8)[iVar4 * 0xf9];
  FUN_8000f604(param_1,param_2);
  if (FLOAT_80436ae8 < *(float *)(param_1 + 0x350)) {
    *(float *)(param_1 + 0x3d0) = *(float *)(param_1 + 0x350);
    FUN_8000f604(param_1,param_2);
  }
  return;
}



// ==== 8000f448  FUN_8000f448 ====

void FUN_8000f448(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  undefined4 uVar3;
  short sVar5;
  int iVar4;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_8000f5bc;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(undefined2 *)(param_1 + 0x1c) = 0x118;
    }
    else if (cVar1 < '\0') {
      return;
    }
    FUN_8000f604(param_1,param_2);
    sVar5 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar5;
    fVar2 = FLOAT_80436adc;
    if (0 < sVar5) {
      return;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(float *)(param_1 + 0xd4) = fVar2;
    iVar4 = (int)*(char *)(param_2 + 0x3e4);
    uVar3 = (&DAT_803c769c)[iVar4 * 0xf9];
    *(undefined4 *)(param_1 + 0x2f4) = (&DAT_803c7698)[iVar4 * 0xf9];
    *(undefined4 *)(param_1 + 0x2f8) = uVar3;
    *(undefined4 *)(param_1 + 0x2fc) = (&DAT_803c76a0)[iVar4 * 0xf9];
    uVar3 = (&DAT_803c76b4)[iVar4 * 0xf9];
    *(undefined4 *)(param_1 + 0x30c) = (&DAT_803c76b0)[iVar4 * 0xf9];
    *(undefined4 *)(param_1 + 0x310) = uVar3;
    *(undefined4 *)(param_1 + 0x314) = (&DAT_803c76b8)[iVar4 * 0xf9];
  }
  zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),(float *)(param_1 + 0x2f4),
              (float *)(param_1 + 0x2e8),(float *)(param_1 + 0x2e8));
  zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),(float *)(param_1 + 0x30c),
              (float *)(param_1 + 0x300),(float *)(param_1 + 0x300));
  fVar2 = FLOAT_80436aa8;
  *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - FLOAT_80436ac0;
  if (fVar2 < *(float *)(param_1 + 0xd4)) {
    return;
  }
  *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x2f4);
  *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x2f8);
  *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x2fc);
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_1 + 0x30c);
  *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(param_1 + 0x310);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_1 + 0x314);
  *(undefined2 *)(param_1 + 0x1c) = 2;
LAB_8000f5bc:
  sVar5 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar5;
  if (sVar5 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_2 + 0x43d) = 0;
    *(undefined1 *)(param_2 + 0x6f8) = 0;
  }
  return;
}



// ==== 8000f604  FUN_8000f604 ====

void FUN_8000f604(int param_1,int param_2)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  double dVar7;
  
  fVar5 = FLOAT_80436b58;
  fVar4 = FLOAT_80436b40;
  fVar3 = FLOAT_80436acc;
  fVar2 = FLOAT_80436ac4;
  iVar6 = *(int *)(param_2 + 0x4ac);
  *(float *)(param_1 + 0x354) =
       FLOAT_80436ae8 * *(float *)(param_2 + 0xb4) +
       FLOAT_80436ac4 * (*(float *)(param_2 + 0xb4) - FLOAT_80436ac0) + FLOAT_80436ac0;
  *(float *)(param_1 + 0x350) = fVar5 * *(float *)(iVar6 + 400) * *(float *)(param_2 + 0xb4);
  *(float *)(param_1 + 0x348) =
       fVar4 * *(float *)(iVar6 + 0x198) * fVar2 * *(float *)(param_1 + 0x354);
  if (*(float *)(param_1 + 0x350) < fVar3) {
    *(float *)(param_1 + 0x350) = fVar3;
  }
  if (*(float *)(param_1 + 0x348) < FLOAT_80436b5c) {
    *(float *)(param_1 + 0x348) = FLOAT_80436b5c;
  }
  uVar1 = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x2e8) = uVar1;
  *(undefined4 *)(param_1 + 0x300) = uVar1;
  uVar1 = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)(param_1 + 0x2ec) = uVar1;
  *(undefined4 *)(param_1 + 0x304) = uVar1;
  uVar1 = *(undefined4 *)(param_2 + 0x28);
  *(undefined4 *)(param_1 + 0x2f0) = uVar1;
  *(undefined4 *)(param_1 + 0x308) = uVar1;
  *(float *)(param_1 + 0x304) = *(float *)(param_1 + 0x304) + *(float *)(param_1 + 0x350);
  dVar7 = zz_0045204_(*(short *)(param_2 + 0x72));
  *(float *)(param_1 + 0x2e8) =
       (float)((double)*(float *)(param_1 + 0x348) * dVar7 + (double)*(float *)(param_1 + 0x2e8));
  *(float *)(param_1 + 0x2ec) = *(float *)(param_1 + 0x2ec) + *(float *)(param_1 + 0x3d0);
  dVar7 = zz_0045238_(*(short *)(param_2 + 0x72));
  *(float *)(param_1 + 0x2f0) =
       (float)((double)*(float *)(param_1 + 0x348) * dVar7 + (double)*(float *)(param_1 + 0x2f0));
  return;
}



// ==== 8000f72c  FUN_8000f72c ====

void FUN_8000f72c(int param_1)

{
  (*(code *)(&PTR_FUN_804335d8)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 8000f764  FUN_8000f764 ====

void FUN_8000f764(int param_1,int param_2)

{
  if (*(int *)(PTR_DAT_80433934 + 0xbc) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_2 + 0x43d) = 0;
    *(undefined1 *)(param_2 + 0x6f8) = 0;
  }
  else {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined1 *)(param_1 + 0x1a) = 0;
    FUN_801fe050(0);
    FUN_8000f9e0((double)FLOAT_80436aa8,(double)FLOAT_80436b1c,param_1,param_2,-0x8000);
  }
  return;
}



// ==== 8000f7fc  FUN_8000f7fc ====

void FUN_8000f7fc(int param_1,int param_2)

{
  char cVar1;
  short sVar2;
  
  if (((*(byte *)(param_2 + 0x3e5) & PTR_DAT_80433930[2]) != 0) &&
     (((&DAT_803c7204)[*(char *)(param_2 + 0x3e4) * 8] & 0x1000) != 0)) {
    *(undefined1 *)(DAT_803c4e84 + 0x43d) = 0;
    *(undefined1 *)(DAT_803c4e88 + 0x43d) = 0;
    *(undefined1 *)(DAT_803c4e8c + 0x43d) = 0;
    *(undefined1 *)(DAT_803c4e90 + 0x43d) = 0;
    *(undefined1 *)(DAT_803c4e94 + 0x43d) = 0;
    *(undefined1 *)(DAT_803c4e98 + 0x43d) = 0;
    FUN_801fe134();
    return;
  }
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_8000f964;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(undefined2 *)(param_1 + 0x1c) = 0x154;
    }
    else if (cVar1 < '\0') {
      return;
    }
    sVar2 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (0 < sVar2) {
      return;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0x348;
    *(undefined2 *)(param_1 + 0x7e) = 0;
  }
  FUN_8000f9e0((double)FLOAT_80436b60,(double)FLOAT_80436b38,param_1,
               *(int *)(PTR_DAT_80433934 + 0xbc),*(short *)(param_1 + 0x7e) + 0x2000);
  *(short *)(param_1 + 0x7e) = *(short *)(param_1 + 0x7e) + 0x40;
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (0 < sVar2) {
    return;
  }
  *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  *(undefined2 *)(param_1 + 0x1c) = 0x168;
LAB_8000f964:
  FUN_8000f9e0((double)FLOAT_80436b64,(double)FLOAT_80436b44,param_1,
               *(int *)(PTR_DAT_80433934 + 0xbc),*(short *)(param_1 + 0x7e) + 0x2000);
  *(short *)(param_1 + 0x7e) = *(short *)(param_1 + 0x7e) + 0x40;
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_2 + 0x43d) = 0;
    *(undefined1 *)(param_2 + 0x6f8) = 0;
    FUN_801fe134();
  }
  return;
}



// ==== 8000f9e0  FUN_8000f9e0 ====

/* WARNING: Removing unreachable block (ram,0x8000fc10) */
/* WARNING: Removing unreachable block (ram,0x8000f9f0) */

void FUN_8000f9e0(double param_1,double param_2,int param_3,int param_4,short param_5)

{
  float fVar1;
  undefined4 uVar2;
  double dVar3;
  double dVar4;
  float local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  float local_30;
  float local_2c;
  float local_28;
  
  *(float *)(param_3 + 0x348) =
       (float)((double)*(float *)(param_4 + *(char *)(param_4 + 0x582) * 8 + 0x898) * param_2);
  *(float *)(param_3 + 0x350) =
       (float)((double)*(float *)(param_4 + *(char *)(param_4 + 0x582) * 4 + 0x88c) + param_1);
  fVar1 = FLOAT_80436ad4;
  if (((PTR_DAT_80433930[0x29] == '\x01') && (PTR_DAT_80433930[0x3d] == '\0')) ||
     (PTR_DAT_80433930[0x29] == '\x02')) {
    *(float *)(param_3 + 0x348) = *(float *)(param_3 + 0x348) * FLOAT_80436ad0;
    *(float *)(param_3 + 0x350) = *(float *)(param_3 + 0x350) * fVar1;
  }
  uVar2 = *(undefined4 *)(param_4 + 0x20);
  *(undefined4 *)(param_3 + 0x30c) = uVar2;
  *(undefined4 *)(param_3 + 0x300) = uVar2;
  fVar1 = *(float *)(param_4 + 0x6d0) + *(float *)(param_4 + 0x24) + *(float *)(param_3 + 0x350);
  *(float *)(param_3 + 0x310) = fVar1;
  *(float *)(param_3 + 0x304) = fVar1;
  uVar2 = *(undefined4 *)(param_4 + 0x28);
  *(undefined4 *)(param_3 + 0x314) = uVar2;
  *(undefined4 *)(param_3 + 0x308) = uVar2;
  *(undefined2 *)(param_3 + 0x70) = 0x600;
  *(short *)(param_3 + 0x72) = *(short *)(param_4 + 0x72) + param_5;
  *(undefined2 *)(param_3 + 0x74) = 0;
  dVar3 = zz_0045238_(*(short *)(param_3 + 0x70));
  dVar4 = (double)(float)((double)*(float *)(param_3 + 0x348) * dVar3);
  dVar3 = zz_0045204_(*(short *)(param_3 + 0x72));
  fVar1 = (float)(dVar3 * dVar4 + (double)*(float *)(param_3 + 0x300));
  *(float *)(param_3 + 0x2f4) = fVar1;
  *(float *)(param_3 + 0x2e8) = fVar1;
  dVar3 = zz_0045204_(*(short *)(param_3 + 0x70));
  fVar1 = (float)((double)*(float *)(param_3 + 0x348) * dVar3 + (double)*(float *)(param_3 + 0x304))
  ;
  *(float *)(param_3 + 0x2f8) = fVar1;
  *(float *)(param_3 + 0x2ec) = fVar1;
  dVar3 = zz_0045238_(*(short *)(param_3 + 0x70));
  dVar4 = (double)(float)((double)*(float *)(param_3 + 0x348) * dVar3);
  dVar3 = zz_0045238_(*(short *)(param_3 + 0x72));
  fVar1 = (float)(dVar3 * dVar4 + (double)*(float *)(param_3 + 0x308));
  *(float *)(param_3 + 0x2fc) = fVar1;
  *(float *)(param_3 + 0x2f0) = fVar1;
  gnt4_PSVECSubtract_bl((float *)(param_3 + 0x300),(float *)(param_3 + 0x2e8),&local_48);
  local_28 = -local_48;
  local_30 = local_40;
  local_2c = FLOAT_80436aa8;
  gnt4_PSVECCrossProduct_bl(&local_48,&local_30,&local_3c);
  gnt4_PSVECNormalize_bl(&local_30,&local_30);
  gnt4_PSVECNormalize_bl(&local_3c,&local_3c);
  gnt4_PSVECNormalize_bl(&local_48,&local_48);
  *(float *)(param_3 + 0x364) = local_30;
  *(float *)(param_3 + 0x374) = local_2c;
  *(float *)(param_3 + 900) = local_28;
  *(float *)(param_3 + 0x368) = local_30;
  *(float *)(param_3 + 0x378) = local_2c;
  *(float *)(param_3 + 0x388) = local_28;
  *(float *)(param_3 + 0x36c) = local_48;
  *(undefined4 *)(param_3 + 0x37c) = local_44;
  *(float *)(param_3 + 0x38c) = local_40;
  *(undefined4 *)(param_3 + 0x370) = *(undefined4 *)(param_3 + 0x2e8);
  *(undefined4 *)(param_3 + 0x380) = *(undefined4 *)(param_3 + 0x2ec);
  *(undefined4 *)(param_3 + 0x390) = *(undefined4 *)(param_3 + 0x2f0);
  *(float *)(param_3 + 0x330) = local_3c;
  *(undefined4 *)(param_3 + 0x334) = local_38;
  *(undefined4 *)(param_3 + 0x338) = local_34;
  return;
}



// ==== 8000fc2c  FUN_8000fc2c ====

void FUN_8000fc2c(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  float fStack_20;
  float local_1c;
  
  fVar1 = FLOAT_80436ac4;
  *(float *)(param_1 + 0x350) =
       (*(float *)(param_2 + *(char *)(param_2 + 0x582) * 4 + 0x88c) * *(float *)(param_1 + 0x354) +
       *(float *)(param_1 + 0x350)) * FLOAT_80436ac4;
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_2 + 0x20);
  *(float *)(param_1 + 0x304) =
       (*(float *)(param_2 + 0x6d0) +
       *(float *)(param_1 + 0x350) + *(float *)(param_1 + 0x310) + *(float *)(param_2 + 0x24)) *
       fVar1;
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_2 + 0x28);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_2 + 0x20),&fStack_20);
  local_1c = FLOAT_80436aa8;
  dVar3 = gnt4_PSVECSquareMag_bl(&fStack_20);
  if (*(char *)(param_2 + 0x582) == '\0') {
    fVar1 = *(float *)(param_2 + 0x898);
    fVar2 = *(float *)(param_2 + 0x894);
  }
  else {
    fVar1 = *(float *)(param_2 + 0x8a0);
    fVar2 = *(float *)(param_2 + 0x89c);
  }
  dVar5 = (double)(fVar1 * *(float *)(param_1 + 0x354));
  dVar4 = (double)(fVar2 * *(float *)(param_1 + 0x354));
  if (((PTR_DAT_80433930[0x29] == '\x01') && (PTR_DAT_80433930[0x3d] == '\0')) ||
     (PTR_DAT_80433930[0x29] == '\x02')) {
    dVar5 = (double)(float)(dVar5 * (double)FLOAT_80436ad0);
    dVar4 = (double)(float)(dVar4 * (double)FLOAT_80436ad0);
  }
  if (dVar3 <= (double)(float)(dVar5 * dVar5)) {
    if ((double)(float)(dVar4 * dVar4) <= dVar3) {
      if ((double)FLOAT_80436aa8 < dVar3) {
        dVar4 = 1.0 / SQRT(dVar3);
        dVar4 = DOUBLE_80436ab0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8);
        dVar4 = DOUBLE_80436ab0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8);
        dVar3 = (double)(float)(dVar3 * DOUBLE_80436ab0 * dVar4 *
                                        -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8));
      }
      *(float *)(param_1 + 0x348) = (float)dVar3;
      *(undefined1 *)(param_1 + 0x35e) = 0;
    }
    else {
      *(float *)(param_1 + 0x348) = (float)dVar4;
      *(undefined1 *)(param_1 + 0x35e) = 0;
    }
  }
  else if ((*(char *)(param_1 + 0x35e) == '\0') && (*(char *)(param_2 + 0x7c9) == '\0')) {
    *(float *)(param_1 + 0x348) = (float)dVar5;
  }
  else {
    if ((double)FLOAT_80436aa8 < dVar3) {
      dVar4 = 1.0 / SQRT(dVar3);
      dVar4 = DOUBLE_80436ab0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8);
      dVar4 = DOUBLE_80436ab0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8);
      dVar3 = (double)(float)(dVar3 * DOUBLE_80436ab0 * dVar4 *
                                      -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8));
    }
    *(float *)(param_1 + 0x348) =
         (float)((double)FLOAT_80436b38 * (double)(float)(dVar3 - dVar5) + dVar5);
    *(undefined1 *)(param_1 + 0x35e) = 1;
  }
  return;
}



// ==== 8000fe60  FUN_8000fe60 ====

/* WARNING: Removing unreachable block (ram,0x8000ffdc) */
/* WARNING: Removing unreachable block (ram,0x8000ffd4) */
/* WARNING: Removing unreachable block (ram,0x8000fe78) */
/* WARNING: Removing unreachable block (ram,0x8000fe70) */

undefined4 FUN_8000fe60(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  undefined4 uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  
  uVar5 = 0;
  if (*(int *)(param_2 + 0x508) == 0) {
    local_34 = FLOAT_80436aa8;
    local_3c = FLOAT_80436aa8;
    local_38 = FLOAT_80436b70;
    FUN_800450e0(-(double)(FLOAT_80436b18 * *(float *)(param_1 + 0x348)),(double)FLOAT_80436b6c,
                 (float *)(param_1 + 0x394),&local_3c,(float *)(param_1 + 0x324));
  }
  else {
    if ((*(uint *)(param_2 + 0x5e0) & 0x40) == 0) {
      sVar3 = (short)*(char *)(param_2 + 0x582) << 1;
    }
    else {
      sVar3 = *(char *)(param_2 + 0x582) * 2 + 4;
    }
    if (*(char *)(param_1 + 0x360) == '\0') {
      iVar4 = param_2 + sVar3 * 4;
      fVar1 = *(float *)(iVar4 + 0x8a4);
      fVar2 = *(float *)(iVar4 + 0x8a8);
    }
    else {
      iVar4 = param_2 + sVar3 * 4;
      fVar1 = FLOAT_80436b68 * *(float *)(iVar4 + 0x8a8);
      fVar2 = FLOAT_80436b68 * *(float *)(iVar4 + 0x8a4);
    }
    dVar8 = (double)fVar1;
    dVar7 = (double)fVar2;
    FUN_8004503c((double)FLOAT_80436b6c,(float *)(param_1 + 0x394),(float *)(param_2 + 0x50c),
                 &local_3c);
    dVar6 = (double)local_38;
    if (dVar6 <= dVar8) {
      if (dVar7 <= dVar6) {
        local_44 = FLOAT_80436aa8;
      }
      else {
        local_44 = (float)(dVar6 - dVar7);
        uVar5 = 1;
      }
    }
    else {
      local_44 = (float)(dVar6 - dVar8);
      uVar5 = 1;
    }
    local_48 = local_3c;
    local_40 = FLOAT_80436aa8;
    FUN_800450e0(-(double)(FLOAT_80436b18 * *(float *)(param_1 + 0x348)),(double)FLOAT_80436b6c,
                 (float *)(param_1 + 0x394),&local_48,(float *)(param_1 + 0x324));
  }
  return uVar5;
}



// ==== 8000fffc  FUN_8000fffc ====

undefined4 FUN_8000fffc(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  double dVar4;
  float local_18;
  float local_14;
  float local_10;
  
  if (*(char *)(param_1 + 0x35e) == '\0') {
    if (*(char *)(param_1 + 0x35f) == '\x01') {
      uVar3 = 0;
    }
    else {
      if (*(char *)(param_2 + 0x582) == '\0') {
        fVar1 = *(float *)(param_2 + 0x898);
        fVar2 = *(float *)(param_2 + 0x894);
      }
      else {
        fVar1 = *(float *)(param_2 + 0x8a0);
        fVar2 = *(float *)(param_2 + 0x89c);
      }
      fVar1 = fVar1 * *(float *)(param_1 + 0x354);
      fVar2 = fVar2 * *(float *)(param_1 + 0x354);
      if (((PTR_DAT_80433930[0x29] == '\x01') && (PTR_DAT_80433930[0x3d] == '\0')) ||
         (PTR_DAT_80433930[0x29] == '\x02')) {
        fVar1 = fVar1 * FLOAT_80436ad0;
        fVar2 = fVar2 * FLOAT_80436ad0;
      }
      if (fVar2 <= *(float *)(param_1 + 0x348)) {
        if (*(float *)(param_1 + 0x348) <= fVar1) {
          return 0;
        }
        *(float *)(param_1 + 0x348) = fVar1;
      }
      else {
        *(float *)(param_1 + 0x348) = fVar2;
      }
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),&local_18);
      local_14 = FLOAT_80436aa8;
      gnt4_PSVECNormalize_bl(&local_18,&local_18);
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_18,&local_18);
      local_18 = local_18 + *(float *)(param_1 + 0x300);
      dVar4 = zz_004526c_(*(short *)(param_1 + 0x70));
      fVar2 = FLOAT_80436b74;
      fVar1 = FLOAT_80436b0c;
      local_14 = (float)((double)*(float *)(param_1 + 0x348) * dVar4 +
                        (double)*(float *)(param_1 + 0x304));
      local_10 = local_10 + *(float *)(param_1 + 0x308);
      *(float *)(param_1 + 0x318) =
           (FLOAT_80436b74 * *(float *)(param_1 + 0x318) + local_18) * FLOAT_80436b0c;
      *(float *)(param_1 + 0x31c) = (fVar2 * *(float *)(param_1 + 0x31c) + local_14) * fVar1;
      *(float *)(param_1 + 800) = (fVar2 * *(float *)(param_1 + 800) + local_10) * fVar1;
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),&local_18);
      gnt4_PSVECNormalize_bl(&local_18,&local_18);
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_18,&local_18);
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),&local_18,(float *)(param_1 + 0x2e8));
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 800101c8  FUN_800101c8 ====

void FUN_800101c8(int param_1,int param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  int iVar5;
  short sVar6;
  double dVar7;
  double dVar8;
  float local_40;
  float local_3c;
  float local_38;
  undefined4 local_30;
  undefined *puStack_2c;
  longlong local_28;
  undefined4 local_20;
  undefined4 uStack_1c;
  longlong local_18;
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x318),&local_40);
  FUN_800452e4((double)FLOAT_80436ad8,&local_40,*(short *)(param_1 + 0x72));
  dVar8 = (double)(local_40 * local_40 + local_38 * local_38);
  if ((double)FLOAT_80436aa8 < dVar8) {
    dVar7 = 1.0 / SQRT(dVar8);
    dVar7 = DOUBLE_80436ab0 * dVar7 * -(dVar8 * dVar7 * dVar7 - DOUBLE_80436ab8);
    dVar7 = DOUBLE_80436ab0 * dVar7 * -(dVar8 * dVar7 * dVar7 - DOUBLE_80436ab8);
    dVar8 = (double)(float)(dVar8 * DOUBLE_80436ab0 * dVar7 *
                                    -(dVar8 * dVar7 * dVar7 - DOUBLE_80436ab8));
  }
  *(float *)(param_1 + 0x348) = (float)dVar8;
  iVar5 = FUN_800452a0(-(double)local_3c,(double)*(float *)(param_1 + 0x348));
  *(short *)(param_1 + 0x70) = (short)iVar5;
  iVar5 = FUN_800452a0((double)local_40,(double)local_38);
  *(short *)(param_1 + 0x72) = (short)iVar5;
  dVar8 = gnt4_PSVECSquareDistance_bl((float *)(param_2 + 0x50c),(float *)(param_1 + 0x300));
  if ((double)FLOAT_80436aa8 < dVar8) {
    dVar7 = 1.0 / SQRT(dVar8);
    dVar7 = DOUBLE_80436ab0 * dVar7 * -(dVar8 * dVar7 * dVar7 - DOUBLE_80436ab8);
    dVar7 = DOUBLE_80436ab0 * dVar7 * -(dVar8 * dVar7 * dVar7 - DOUBLE_80436ab8);
    dVar8 = (double)(float)(dVar8 * DOUBLE_80436ab0 * dVar7 *
                                    -(dVar8 * dVar7 * dVar7 - DOUBLE_80436ab8));
  }
  fVar2 = FLOAT_80436b44 * ((float)((double)FLOAT_80436b1c * dVar8) / *(float *)(param_2 + 0x668));
  fVar3 = FLOAT_80436ac0;
  if ((fVar2 <= FLOAT_80436ac0) && (fVar3 = fVar2, fVar2 < FLOAT_80436b44)) {
    fVar3 = FLOAT_80436b44;
  }
  puStack_2c = &DAT_80003000;
  local_30 = 0x43300000;
  uStack_1c = 0x7fffd000;
  local_20 = 0x43300000;
  iVar5 = (int)((float)(4503601774866432.0 - DOUBLE_80436b30) * fVar3);
  local_28 = (longlong)iVar5;
  iVar1 = (int)((float)(4503601774841856.0 - DOUBLE_80436b30) * fVar3);
  local_18 = (longlong)iVar1;
  sVar6 = (short)iVar5;
  if (sVar6 < *(short *)(param_1 + 0x70)) {
    *(short *)(param_1 + 0x70) = sVar6;
    bVar4 = true;
  }
  else {
    sVar6 = (short)iVar1;
    if (*(short *)(param_1 + 0x70) < sVar6) {
      *(short *)(param_1 + 0x70) = sVar6;
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
  }
  if (bVar4) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),&local_40);
    local_3c = FLOAT_80436aa8;
    gnt4_PSVECNormalize_bl(&local_40,&local_40);
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_40,&local_40);
    local_40 = local_40 + *(float *)(param_1 + 0x300);
    dVar8 = zz_004526c_(*(short *)(param_1 + 0x70));
    fVar3 = FLOAT_80436b74;
    fVar2 = FLOAT_80436b0c;
    local_3c = (float)((double)*(float *)(param_1 + 0x348) * dVar8 +
                      (double)*(float *)(param_1 + 0x304));
    local_38 = local_38 + *(float *)(param_1 + 0x308);
    *(float *)(param_1 + 0x318) =
         (FLOAT_80436b74 * *(float *)(param_1 + 0x318) + local_40) * FLOAT_80436b0c;
    *(float *)(param_1 + 0x31c) = (fVar3 * *(float *)(param_1 + 0x31c) + local_3c) * fVar2;
    *(float *)(param_1 + 800) = (fVar3 * *(float *)(param_1 + 800) + local_38) * fVar2;
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),&local_40);
    gnt4_PSVECNormalize_bl(&local_40,&local_40);
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_40,&local_40);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),&local_40,(float *)(param_1 + 0x2e8));
  }
  *(short *)(param_2 + 0x5b0) = *(short *)(param_1 + 0x72) + -0x8000;
  return;
}



// ==== 80010514  zz_0010514_ ====

uint zz_0010514_(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((&DAT_803c73c8)[param_1 * 0x3e4] == '\x02') {
    uVar1 = 0x80000000;
  }
  switch(*(byte *)((&DAT_803c4e84)[param_1] + 0x43d) & 0x7f) {
  case 2:
    uVar1 = uVar1 | 1;
    break;
  case 3:
    uVar1 = uVar1 | 2;
    break;
  case 4:
    uVar1 = uVar1 | 4;
    break;
  case 5:
    uVar1 = uVar1 | 8;
    break;
  case 6:
    uVar1 = uVar1 | 0x10;
    break;
  case 7:
    uVar1 = uVar1 | 0x20;
    break;
  case 8:
    uVar1 = uVar1 | 0x40;
    break;
  case 9:
    uVar1 = uVar1 | 0x80;
  }
  return uVar1;
}



// ==== 800105b4  zz_00105b4_ ====

undefined4 zz_00105b4_(int param_1,float *param_2)

{
  undefined4 uVar1;
  float local_18;
  float local_14;
  float local_10;
  
  zz_0067d70_(param_1,param_2,&local_18);
  uVar1 = 0;
  if ((((FLOAT_80436aa8 <= local_18) && (local_18 <= FLOAT_80436b78)) &&
      (FLOAT_80436aa8 <= local_14)) &&
     (((local_14 <= FLOAT_80436b7c && (FLOAT_80436aa8 < local_10)) && (local_10 < FLOAT_80436ac0))))
  {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 8001063c  FUN_8001063c ====

void FUN_8001063c(int param_1)

{
  *(undefined1 *)(param_1 + 0x35f) = 0;
  zz_0010664_(param_1);
  return;
}



// ==== 80010664  zz_0010664_ ====

void zz_0010664_(int param_1)

{
  double dVar1;
  
  if ((((*(float *)(param_1 + 0x2e8) < *(float *)(DAT_8043625c + 0x3c)) ||
       (*(float *)(DAT_8043625c + 0x38) < *(float *)(param_1 + 0x2e8))) ||
      (*(float *)(param_1 + 0x2f0) < *(float *)(DAT_8043625c + 0x44))) ||
     (*(float *)(DAT_8043625c + 0x40) < *(float *)(param_1 + 0x2f0))) {
    *(undefined1 *)(param_1 + 0x2e7) = 0;
  }
  else {
    dVar1 = FUN_8003dd34((float *)(param_1 + 0x2e8));
    if (dVar1 <= (double)*(float *)(param_1 + 0x2ec)) {
      *(undefined1 *)(param_1 + 0x2e7) = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x2e7) = 1;
    }
  }
  return;
}



// ==== 800106fc  zz_00106fc_ ====

bool zz_00106fc_(int param_1,int param_2,float *param_3)

{
  bool bVar1;
  double dVar2;
  
  dVar2 = FUN_8003d964((double)*(float *)(param_2 + 0x668),param_1,param_3);
  bVar1 = (double)(float)((double)param_3[1] - (double)FLOAT_80436b80) < dVar2;
  if (bVar1) {
    param_3[1] = (float)((double)FLOAT_80436b80 + dVar2);
  }
  return bVar1;
}



// ==== 80010760  zz_0010760_ ====

void zz_0010760_(int param_1,int param_2)

{
  if ((param_2 == 1) && (PTR_DAT_80433934[0x1f] != '\0')) {
    return;
  }
  *(byte *)(param_1 + 0x43d) = (byte)param_2 | 0x80;
  return;
}



// ==== 80010784  zz_0010784_ ====

void zz_0010784_(int param_1)

{
  if (PTR_DAT_80433934[0x1f] != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0x43d) = 0;
  return;
}



// ==== 800107a0  zz_00107a0_ ====

void zz_00107a0_(int param_1,undefined1 param_2)

{
  uint uVar1;
  
  uVar1 = zz_0010514_((int)*(char *)(param_1 + 0x3e4));
  if (((uVar1 & 0x20) == 0) && (PTR_DAT_80433934[0x1f] == '\0')) {
    *(undefined1 *)(param_1 + 0x43d) = 0x81;
    *(undefined1 *)(param_1 + 0x6f8) = param_2;
    *(undefined1 *)(param_1 + 0x6f9) = 0xff;
  }
  return;
}



// ==== 8001080c  zz_001080c_ ====

void zz_001080c_(double param_1,int param_2,undefined4 param_3,undefined1 param_4,undefined2 param_5
                ,undefined1 param_6)

{
  uint uVar1;
  char cVar3;
  int iVar2;
  
  uVar1 = zz_0010514_((int)*(char *)(param_2 + 0x3e4));
  if (((((uVar1 & 1) == 0) && (cVar3 = zz_008b480_(), cVar3 == '\0')) &&
      (cVar3 = zz_008b290_(), cVar3 == '\0')) && (PTR_DAT_80433934[0x1f] == '\0')) {
    *(undefined1 *)(param_2 + 0x43d) = 0x87;
    iVar2 = (*(char *)(param_2 + 0x3e4) + 6) * 0x3e4;
    (&DAT_803c7439)[iVar2] = param_4;
    *(float *)(&DAT_803c73f4 + iVar2) = (float)param_1;
    *(undefined4 *)(&DAT_803c747c + iVar2) = param_3;
    *(undefined2 *)(&DAT_803c73ce + iVar2) = param_5;
    (&DAT_803c73c2)[iVar2] = param_6;
  }
  return;
}



// ==== 800108c8  FUN_800108c8 ====

void FUN_800108c8(int param_1)

{
  char cVar1;
  
  cVar1 = zz_008b480_();
  if (((cVar1 == '\0') && (cVar1 = zz_008b290_(), cVar1 == '\0')) &&
     (PTR_DAT_80433934[0x1f] == '\0')) {
    *(undefined1 *)(param_1 + 0x43d) = 0x88;
  }
  return;
}



// ==== 80010924  FUN_80010924 ====

void FUN_80010924(int param_1)

{
  char cVar1;
  
  cVar1 = zz_008b480_();
  if (((cVar1 == '\0') && (cVar1 = zz_008b290_(), cVar1 == '\0')) &&
     (PTR_DAT_80433934[0x1f] == '\0')) {
    *(undefined1 *)(param_1 + 0x43d) = 0x89;
  }
  return;
}



// ==== 80010980  zz_0010980_ ====

void zz_0010980_(int param_1)

{
  char cVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x1da) == '\0') {
    *(char *)(param_1 + 0x35b) =
         (char)(int)((float)((double)CONCAT44(0x43300000,(uint)*(byte *)(param_1 + 0x35b)) -
                            DOUBLE_80436b88) * FLOAT_80436ae4);
  }
  else {
    iVar2 = *(int *)(param_1 + 0x290);
    cVar1 = *(char *)(iVar2 + 0x10);
    if (cVar1 == '\a') {
      *(undefined1 *)(param_1 + 0x358) = 0;
      *(undefined1 *)(param_1 + 0x359) = 0;
      *(undefined1 *)(param_1 + 0x35a) = 0;
      *(undefined1 *)(param_1 + 0x35b) = 0xc0;
    }
    else if ((cVar1 == 'I') || (cVar1 == '\v')) {
      *(undefined1 *)(param_1 + 0x358) = 0xff;
      *(undefined1 *)(param_1 + 0x359) = 0xff;
      *(undefined1 *)(param_1 + 0x35a) = 0xff;
      *(undefined1 *)(param_1 + 0x35b) = 0xc0;
    }
    else if (cVar1 == ':') {
      cVar1 = *(char *)(iVar2 + 0x11);
      if (cVar1 == '\x01') {
        *(undefined1 *)(param_1 + 0x358) = 0xff;
        *(undefined1 *)(param_1 + 0x359) = 0;
        *(undefined1 *)(param_1 + 0x35a) = 0x66;
        *(undefined1 *)(param_1 + 0x35b) = 0x33;
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(undefined1 *)(param_1 + 0x358) = 0;
          *(undefined1 *)(param_1 + 0x359) = 0;
          *(undefined1 *)(param_1 + 0x35a) = 0xff;
          *(undefined1 *)(param_1 + 0x35b) = 0x33;
        }
      }
      else if (cVar1 < '\x03') {
        *(undefined1 *)(param_1 + 0x358) = 0;
        *(undefined1 *)(param_1 + 0x359) = 0;
        *(undefined1 *)(param_1 + 0x35a) = 0x33;
        *(undefined1 *)(param_1 + 0x35b) = 0x33;
      }
    }
    else if (cVar1 == '\x03') {
      cVar1 = *(char *)(iVar2 + 0x11);
      if (cVar1 == '\x01') {
        *(undefined1 *)(param_1 + 0x358) = 0;
        *(undefined1 *)(param_1 + 0x359) = 0xff;
        *(undefined1 *)(param_1 + 0x35a) = 0;
        *(undefined1 *)(param_1 + 0x35b) = 0x33;
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(undefined1 *)(param_1 + 0x358) = 0xff;
          *(undefined1 *)(param_1 + 0x359) = 0;
          *(undefined1 *)(param_1 + 0x35a) = 0;
          *(undefined1 *)(param_1 + 0x35b) = 0x33;
        }
      }
      else if (cVar1 < '\x03') {
        *(undefined1 *)(param_1 + 0x358) = 0;
        *(undefined1 *)(param_1 + 0x359) = 0;
        *(undefined1 *)(param_1 + 0x35a) = 0xff;
        *(undefined1 *)(param_1 + 0x35b) = 0x33;
      }
    }
  }
  return;
}



// ==== 80010b50  zz_0010b50_ ====

void zz_0010b50_(void)

{
  DAT_804360dc = 0;
  DAT_804360da = 0;
  DAT_804360d8 = 0;
  return;
}



// ==== 80010b64  zz_0010b64_ ====

void zz_0010b64_(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  
  DAT_804360d8 = DAT_804360d8 + -1;
  if (DAT_804360d8 < 1) {
    iVar2 = 0;
    iVar5 = 5;
    do {
      if (iVar2 == 0) {
        pcVar3 = *(char **)((&DAT_803c4e84)[DAT_804360dc] + 0xcc);
        if (pcVar3 != (char *)0x0) {
          if (pcVar3[0x83] == '\0') {
            DAT_804360dc = pcVar3[0x3e4];
            goto LAB_80010c10;
          }
        }
      }
      else {
        iVar4 = DAT_804360dc + 1;
        cVar1 = (char)(iVar4 >> 0x1f);
        DAT_804360dc = (cVar1 * '\x04' |
                       (byte)((uint)(iVar4 * 0x40000000 + (iVar4 >> 0x1f)) >> 0x1e)) - cVar1;
        pcVar3 = (char *)(&DAT_803c4e84)[DAT_804360dc];
LAB_80010c10:
        if ((((*pcVar3 != '\0') && (pcVar3[1000] != '\x0e')) && (pcVar3[0x18] == '\x01')) &&
           (pcVar3[0x19] == '\x02')) break;
      }
      iVar2 = iVar2 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    DAT_804360d8 = 300;
    DAT_804360db = 1;
    DAT_803ca278 = 0;
  }
  zz_0010c7c_();
  return;
}



// ==== 80010c7c  zz_0010c7c_ ====

void zz_0010c7c_(void)

{
  uint uVar1;
  int iVar2;
  
  DAT_803ca260 = 1;
  iVar2 = (&DAT_803c4e84)[DAT_804360dc];
  DAT_803ca554 = DAT_803ca548;
  DAT_803ca558 = DAT_803ca54c;
  DAT_803ca55c = DAT_803ca550;
  DAT_803ca56c = DAT_803ca560;
  DAT_803ca570 = DAT_803ca564;
  DAT_803ca574 = DAT_803ca568;
  DAT_803ca5b4 = *(undefined4 *)(iVar2 + 0xb4);
  if (DAT_803ca278 != '\x01') {
    if (('\0' < DAT_803ca278) || (DAT_803ca278 < '\0')) {
      if (((DAT_803ca271 == -1) || (DAT_804360db == '\x01')) || ('\x02' < *(char *)(iVar2 + 0x18)))
      {
        DAT_803ca260 = 1;
        DAT_803ca554 = DAT_803ca548;
        DAT_803ca558 = DAT_803ca54c;
        DAT_803ca55c = DAT_803ca550;
        DAT_803ca56c = DAT_803ca560;
        DAT_803ca570 = DAT_803ca564;
        DAT_803ca574 = DAT_803ca568;
        DAT_804360d8 = 1;
        return;
      }
      (*(code *)(&PTR_FUN_802c3970)[DAT_803ca271])(&DAT_803ca260,iVar2);
      goto LAB_80010e2c;
    }
    DAT_803ca278 = DAT_803ca278 + '\x01';
    DAT_803ca27a = 0;
    DAT_803ca279 = 0;
    DAT_803ca27c = 10;
    DAT_803ca545 = *(undefined1 *)(iVar2 + 0x3e4);
    uVar1 = zz_00055fc_();
    DAT_804360db = '\0';
    DAT_803ca271 = (&DAT_802c3960)[uVar1 & 0xf];
  }
  DAT_803ca27c = DAT_803ca27c + -1;
  if (DAT_803ca27c < 1) {
    DAT_803ca278 = DAT_803ca278 + '\x01';
  }
  if (((DAT_803ca271 == -1) || (DAT_804360db == '\x01')) || ('\x02' < *(char *)(iVar2 + 0x18))) {
    DAT_804360d8 = 1;
    return;
  }
  (*(code *)(&PTR_FUN_802c3970)[DAT_803ca271])(&DAT_803ca260,iVar2);
LAB_80010e2c:
  if (DAT_804360db == '\0') {
    FUN_8000c314(-0x7fc35da0);
  }
  return;
}



// ==== 80010e58  FUN_80010e58 ====

void FUN_80010e58(int param_1,int param_2)

{
  float fVar1;
  ushort uVar2;
  uint uVar3;
  byte bVar4;
  double dVar5;
  float local_28;
  float local_24;
  float local_20;
  
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_2 + 0x910);
  *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(param_2 + 0x920);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_2 + 0x930);
  fVar1 = FLOAT_80436b1c;
  if (*(char *)(param_1 + 0x19) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(float *)(param_1 + 0x348) = fVar1 * *(float *)(param_2 + 0x898);
    uVar3 = zz_00055fc_();
    if ((uVar3 & 3) == 0) {
      *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x348) * FLOAT_80436b90;
    }
    fVar1 = FLOAT_80436b94;
    if (*(float *)(param_1 + 0x348) < FLOAT_80436b94) {
      fVar1 = *(float *)(param_1 + 0x348);
    }
    *(float *)(param_1 + 0x348) = fVar1;
    if (*(int *)(param_2 + 0xcc) == 0) {
      uVar3 = zz_00055fc_();
      uVar2 = (ushort)(uVar3 << 8) & 0xf000;
      dVar5 = zz_0045204_(uVar2);
      fVar1 = FLOAT_80436b98;
      *(float *)(param_1 + 0x2e8) =
           (float)((double)*(float *)(param_1 + 0x348) * dVar5 + (double)*(float *)(param_2 + 0x20))
      ;
      *(float *)(param_1 + 0x2ec) = fVar1 + *(float *)(param_2 + 0x24);
      dVar5 = zz_0045238_(uVar2);
      *(float *)(param_1 + 0x2f0) =
           (float)((double)*(float *)(param_1 + 0x348) * dVar5 + (double)*(float *)(param_2 + 0x28))
      ;
    }
    else {
      gnt4_PSVECSubtract_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x518),&local_28);
      local_24 = FLOAT_80436aa8;
      if (local_20 * local_20 + local_28 * local_28 + FLOAT_80436aa8 * FLOAT_80436aa8 <=
          FLOAT_80436ac8) {
        dVar5 = zz_0045204_(*(short *)(param_2 + 0x72));
        local_28 = (float)-dVar5;
        dVar5 = zz_0045238_(*(short *)(param_2 + 0x72));
        local_20 = (float)-dVar5;
      }
      uVar3 = zz_00055fc_();
      zz_00453fc_('y',&local_28,&local_28,((ushort)(uVar3 << 8) & 0x7f00) + 0xc000);
      gnt4_PSVECNormalize_bl(&local_28,&local_28);
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_28,&local_28);
      local_24 = FLOAT_80436b98;
      gnt4_PSVECAdd_bl((float *)(param_2 + 0x20),&local_28,(float *)(param_1 + 0x2e8));
    }
    dVar5 = FUN_8003d964((double)*(float *)(param_2 + 0x668),param_1,(float *)(param_1 + 0x2e8));
    if ((double)*(float *)(param_1 + 0x2ec) < dVar5) {
      *(float *)(param_1 + 0x2ec) = (float)dVar5;
    }
  }
  else {
    bVar4 = zz_00118d0_(param_1,param_2,(float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
    if ((bVar4 & 2) != 0) {
      DAT_804360db = 1;
    }
  }
  return;
}



// ==== 8001105c  FUN_8001105c ====

void FUN_8001105c(int param_1,int param_2)

{
  float fVar1;
  ushort uVar2;
  float fVar3;
  uint uVar4;
  uint uVar5;
  byte bVar6;
  
  fVar3 = FLOAT_80436ac4;
  *(float *)(param_1 + 0x350) =
       (*(float *)(param_2 + 0x88c) * *(float *)(param_1 + 0x354) + *(float *)(param_1 + 0x350)) *
       FLOAT_80436ac4;
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_2 + 0x20);
  *(float *)(param_1 + 0x304) =
       (*(float *)(param_2 + 0x6d0) +
       *(float *)(param_1 + 0x350) + *(float *)(param_1 + 0x310) + *(float *)(param_2 + 0x24)) *
       fVar3;
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_2 + 0x28);
  fVar3 = FLOAT_80436b74;
  if (*(char *)(param_1 + 0x19) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    fVar1 = FLOAT_80436b94;
    *(float *)(param_1 + 0x348) = fVar3 * *(float *)(param_2 + 0x898);
    if (*(float *)(param_1 + 0x348) < fVar1) {
      fVar1 = *(float *)(param_1 + 0x348);
    }
    *(float *)(param_1 + 0x348) = fVar1;
    uVar4 = zz_00055fc_();
    uVar2 = (ushort)(uVar4 << 8) & 0xf000;
    uVar4 = zz_00055fc_();
    uVar5 = zz_00055fc_();
    fVar3 = FLOAT_80436aa8;
    *(float *)(param_1 + 0x340) = FLOAT_80436aa8;
    fVar1 = FLOAT_80436ac0;
    *(float *)(param_1 + 0x33c) = fVar3;
    *(float *)(param_1 + 0x344) = fVar1;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x33c);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x340);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x344);
    zz_00453fc_('y',(float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c),uVar2);
    zz_00453fc_('x',(float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c),
                -(((ushort)(uVar5 << 8) & 0x1f00) + 0x800));
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),(float *)(param_1 + 0x33c),
                        (float *)(param_1 + 0x33c));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x33c),
                     (float *)(param_1 + 0x2e8));
    bVar6 = zz_00118d0_(param_1,param_2,(float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
    if ((bVar6 & 2) == 0) {
      *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(param_2 + 0x894);
      zz_00453fc_('y',(float *)(param_1 + 0x38),(float *)(param_1 + 0x38),
                  uVar2 + ((ushort)(uVar4 << 8) & 0x3f00));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      gnt4_PSVECSubtract_bl
                ((float *)(param_1 + 0x38),(float *)(param_1 + 0x33c),(float *)(param_1 + 0x38));
      DAT_804360d8 = 0x96;
      gnt4_PSQUATScale_bl((double)FLOAT_80436b9c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38)
                         );
    }
    else {
      DAT_804360db = 1;
    }
  }
  else {
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x33c),(float *)(param_1 + 0x38),(float *)(param_1 + 0x33c)
                    );
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x33c),
                     (float *)(param_1 + 0x2e8));
    bVar6 = zz_00118d0_(param_1,param_2,(float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
    if ((bVar6 & 2) != 0) {
      DAT_804360db = 1;
    }
  }
  return;
}



// ==== 80011280  zz_0011280_ ====

void zz_0011280_(int param_1,int param_2)

{
  float fVar1;
  short sVar2;
  uint uVar3;
  byte bVar4;
  ushort uVar5;
  double dVar6;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_18;
  uint uStack_14;
  
  fVar1 = FLOAT_80436ac4;
  *(float *)(param_1 + 0x350) =
       (*(float *)(param_2 + 0x88c) * *(float *)(param_1 + 0x354) + *(float *)(param_1 + 0x350)) *
       FLOAT_80436ac4;
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_2 + 0x20);
  *(float *)(param_1 + 0x304) =
       (*(float *)(param_2 + 0x6d0) +
       *(float *)(param_1 + 0x350) + *(float *)(param_1 + 0x310) + *(float *)(param_2 + 0x24)) *
       fVar1;
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_2 + 0x28);
  if (*(char *)(param_1 + 0x19) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(param_2 + 0x898);
    uVar3 = zz_00055fc_();
    if ((uVar3 & 3) == 0) {
      *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x348) * FLOAT_80436b90;
    }
    fVar1 = FLOAT_80436b94;
    if (*(float *)(param_1 + 0x348) < FLOAT_80436b94) {
      fVar1 = *(float *)(param_1 + 0x348);
    }
    *(float *)(param_1 + 0x348) = fVar1;
    uVar3 = zz_00055fc_();
    uVar5 = (ushort)(uVar3 << 8) & 0xf000;
    uVar3 = zz_00055fc_();
    sVar2 = uVar5 + ((ushort)(uVar3 << 8) & 0x7f00) + 0x1000;
    dVar6 = zz_0045204_(uVar5);
    fVar1 = FLOAT_80436aa8;
    *(float *)(param_1 + 0x2e8) =
         (float)((double)*(float *)(param_1 + 0x348) * dVar6 + (double)*(float *)(param_2 + 0x20));
    *(float *)(param_1 + 0x2ec) = fVar1;
    dVar6 = zz_0045238_(uVar5);
    *(float *)(param_1 + 0x2f0) =
         (float)((double)*(float *)(param_1 + 0x348) * dVar6 + (double)*(float *)(param_2 + 0x28));
    dVar6 = zz_0045204_(sVar2);
    local_28 = (float)((double)*(float *)(param_1 + 0x348) * dVar6 +
                      (double)*(float *)(param_2 + 0x20));
    local_24 = FLOAT_80436aa8;
    dVar6 = zz_0045238_(sVar2);
    local_20 = (float)((double)*(float *)(param_1 + 0x348) * dVar6 +
                      (double)*(float *)(param_2 + 0x28));
    gnt4_PSVECSubtract_bl(&local_28,(float *)(param_1 + 0x2e8),(float *)(param_1 + 0x38));
    local_18 = 0x43300000;
    uStack_14 = (int)DAT_804360d8 ^ 0x80000000;
    gnt4_PSQUATScale_bl((double)(FLOAT_80436ac0 /
                                (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80436b30)),
                        (float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    dVar6 = FUN_8003d964((double)*(float *)(param_2 + 0x668),param_1,(float *)(param_1 + 0x2e8));
    *(float *)(param_1 + 0x2ec) = (float)((double)FLOAT_80436b98 + dVar6);
    bVar4 = zz_00118d0_(param_1,param_2,(float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
    if ((bVar4 & 2) != 0) {
      DAT_804360db = 1;
    }
  }
  else {
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x38),(float *)(param_1 + 0x2e8)
                    );
    dVar6 = FUN_8003d964((double)*(float *)(param_2 + 0x668),param_1,(float *)(param_1 + 0x2e8));
    *(float *)(param_1 + 0x2ec) = (float)((double)FLOAT_80436b98 + dVar6);
    bVar4 = zz_00118d0_(param_1,param_2,(float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
    if ((bVar4 & 2) != 0) {
      DAT_804360db = 1;
    }
    if ((((FLOAT_80436b94 < *(float *)(param_1 + 0x2e8)) ||
         (*(float *)(param_1 + 0x2e8) < FLOAT_80436ba0)) ||
        (FLOAT_80436b94 < *(float *)(param_1 + 0x2f0))) ||
       (*(float *)(param_1 + 0x2f0) < FLOAT_80436ba0)) {
      DAT_804360db = 1;
    }
  }
  return;
}



// ==== 80011510  FUN_80011510 ====

void FUN_80011510(int param_1,int param_2)

{
  float fVar1;
  short sVar2;
  uint uVar3;
  byte bVar4;
  int iVar5;
  double dVar6;
  float afStack_28 [7];
  
  fVar1 = FLOAT_80436ac4;
  if ((*(uint *)(param_2 + 0x5e0) & 0x81000000) == 0) {
    *(float *)(param_1 + 0x350) =
         FLOAT_80436b38 *
         (*(float *)(param_2 + 0x88c) * *(float *)(param_1 + 0x354) + *(float *)(param_1 + 0x350)) *
         FLOAT_80436ac4;
    *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_2 + 0x20);
    *(float *)(param_1 + 0x304) =
         (*(float *)(param_2 + 0x6d0) +
         *(float *)(param_1 + 0x350) + *(float *)(param_1 + 0x310) + *(float *)(param_2 + 0x24)) *
         fVar1;
    *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_2 + 0x28);
    fVar1 = FLOAT_80436b28;
    iVar5 = *(int *)(param_2 + 0x4ac);
    if (*(char *)(param_1 + 0x19) == '\0') {
      *(undefined1 *)(param_1 + 0x19) = 1;
      *(float *)(param_1 + 0x348) = fVar1 * *(float *)(iVar5 + 0x198);
      uVar3 = zz_00055fc_();
      sVar2 = ((ushort)(uVar3 << 8) & 0x3f00) + 0xe000;
      dVar6 = zz_0045204_(sVar2);
      fVar1 = FLOAT_80436aa8;
      *(float *)(param_1 + 0x33c) = (float)((double)*(float *)(param_1 + 0x348) * dVar6);
      *(float *)(param_1 + 0x340) = fVar1;
      dVar6 = zz_0045238_(sVar2);
      *(float *)(param_1 + 0x344) = (float)((double)*(float *)(param_1 + 0x348) * dVar6);
      DAT_804360d8 = 0x3c;
    }
    zz_00453fc_('y',(float *)(param_1 + 0x33c),afStack_28,*(short *)(param_2 + 0x72));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),afStack_28,(float *)(param_1 + 0x2e8));
    bVar4 = zz_00118d0_(param_1,param_2,(float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
    if ((bVar4 & 2) != 0) {
      DAT_804360db = 1;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x11) = 2;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    zz_0011280_(param_1,param_2);
  }
  return;
}



// ==== 80011688  FUN_80011688 ====

void FUN_80011688(int param_1,int param_2)

{
  float fVar1;
  short sVar2;
  float fVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  short sVar8;
  double dVar9;
  
  fVar1 = FLOAT_80436ac4;
  *(float *)(param_1 + 0x350) =
       FLOAT_80436b38 *
       (*(float *)(param_2 + 0x88c) * *(float *)(param_1 + 0x354) + *(float *)(param_1 + 0x350)) *
       FLOAT_80436ac4;
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_2 + 0x20);
  *(float *)(param_1 + 0x304) =
       (*(float *)(param_2 + 0x6d0) +
       *(float *)(param_1 + 0x350) + *(float *)(param_1 + 0x310) + *(float *)(param_2 + 0x24)) *
       fVar1;
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_2 + 0x28);
  if (*(char *)(param_1 + 0x19) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    uVar4 = zz_00055fc_();
    uVar5 = zz_00055fc_();
    *(float *)(param_1 + 0x348) = FLOAT_80436b1c * *(float *)(param_2 + 0x898);
    uVar6 = zz_00055fc_();
    if ((uVar6 & 3) == 0) {
      *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x348) * FLOAT_80436b18;
    }
    fVar1 = FLOAT_80436b94;
    if (*(float *)(param_1 + 0x348) < FLOAT_80436b94) {
      fVar1 = *(float *)(param_1 + 0x348);
    }
    *(float *)(param_1 + 0x348) = fVar1;
    fVar3 = FLOAT_80436ac0;
    fVar1 = FLOAT_80436aa8;
    sVar8 = (short)((uVar4 & 0xf0) << 8);
    *(float *)(param_1 + 0x340) = FLOAT_80436aa8;
    *(float *)(param_1 + 0x33c) = fVar1;
    *(float *)(param_1 + 0x344) = fVar3;
    zz_00453fc_('y',(float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c),sVar8);
    zz_00453fc_('x',(float *)(param_1 + 0x33c),(float *)(param_1 + 0x33c),
                -(((ushort)(uVar5 << 8) & 0x700) + 0xc00));
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),(float *)(param_1 + 0x33c),
                        (float *)(param_1 + 0x33c));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x33c),
                     (float *)(param_1 + 0x2e8));
    bVar7 = zz_00118d0_(param_1,param_2,(float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
    if ((bVar7 & 2) == 0) {
      uVar4 = zz_00055fc_();
      sVar2 = sVar8 + -0x7e00;
      if ((uVar4 & 1) != 0) {
        sVar2 = sVar8 + 0x7e00;
      }
      dVar9 = zz_0045204_(sVar2);
      fVar1 = FLOAT_80436aa8;
      *(float *)(param_1 + 0x38) = (float)((double)FLOAT_80436ae8 * dVar9);
      *(float *)(param_1 + 0x3c) = fVar1;
      dVar9 = zz_0045238_(sVar2);
      *(float *)(param_1 + 0x40) = (float)((double)FLOAT_80436ae8 * dVar9);
      uVar4 = zz_00055fc_();
      *(byte *)(param_1 + 0x1a) = (byte)uVar4 & 2;
      DAT_804360d8 = 0x96;
    }
    else {
      DAT_804360db = 1;
    }
  }
  else {
    if (*(char *)(param_1 + 0x1a) != '\0') {
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x38),
                       (float *)(param_1 + 0x2e8));
    }
    bVar7 = zz_00118d0_(param_1,param_2,(float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
    if ((bVar7 & 2) != 0) {
      DAT_804360db = 1;
    }
  }
  return;
}



// ==== 800118d0  zz_00118d0_ ====

byte zz_00118d0_(int param_1,int param_2,float *param_3,float *param_4)

{
  int iVar1;
  byte bVar2;
  double dVar3;
  float fStack_28;
  float local_24;
  
  dVar3 = FUN_8003d964((double)*(float *)(param_2 + 0x668),param_1,param_3);
  local_24 = (float)dVar3;
  bVar2 = (double)(param_3[1] - FLOAT_80436b80) < dVar3;
  if ((bool)bVar2) {
    param_3[1] = FLOAT_80436b80 + (float)dVar3;
  }
  iVar1 = zz_003e978_(param_4,param_3,&fStack_28);
  if (iVar1 != 0) {
    bVar2 = bVar2 | 2;
  }
  if (FLOAT_80436b08 + *(float *)(DAT_8043625c + 0x34) < param_3[1]) {
    bVar2 = bVar2 | 2;
  }
  if ((((*param_3 < *(float *)(DAT_8043625c + 0x3c) - FLOAT_80436b98) ||
       (FLOAT_80436b98 + *(float *)(DAT_8043625c + 0x38) < *param_3)) ||
      (param_3[2] < *(float *)(DAT_8043625c + 0x44) - FLOAT_80436b98)) ||
     (FLOAT_80436b98 + *(float *)(DAT_8043625c + 0x40) < param_3[2])) {
    bVar2 = bVar2 | 2;
  }
  return bVar2;
}



// ==== 800119d4  zz_00119d4_ ====

void zz_00119d4_(undefined1 *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar1 = (int)(char)param_1[2];
  if (iVar1 < 9) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar1 + -8;
    iVar1 = 8;
  }
  puVar2 = zz_008893c_(2,(int)(char)param_1[4],0,iVar4);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar5 = (undefined4 *)(puVar2 + 0x144);
    iVar4 = 0;
    puVar2[0x11] = *param_1;
    puVar2[0x12] = param_1[1];
    *(code **)(puVar2 + 0xc) = FUN_80011d48;
    *(code **)(puVar2 + 0x10c) = FUN_8001212c;
    puVar2[0x176] = PTR_DAT_80433930[0x29];
    puVar2[0x173] = 0;
    puVar2[0x171] = param_1[5];
    do {
      if (iVar1 == 0) {
        *puVar5 = 0;
      }
      else {
        uVar3 = zz_0006d4c_();
        *puVar5 = uVar3;
        iVar1 = iVar1 + -1;
      }
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar4 < 8);
  }
  return;
}



// ==== 80011abc  zz_0011abc_ ====

void zz_0011abc_(void)

{
  char *pcVar1;
  
  DAT_804360e0 = 0;
  uRam804360e1 = 0;
  uRam804360e2 = 0;
  uRam804360e3 = 0;
  uRam804360e4 = 0;
  uRam804360e5 = 0;
  PTR_DAT_80433934[0x1832] = 0;
  if (PTR_DAT_80433930[0x40] == '\0') {
    if (PTR_DAT_80433930[0x29] == '\x02') {
      zz_009cac0_();
    }
    else if (PTR_DAT_80433930[0x29] == '\x01') {
      zz_00a9768_();
    }
    else {
      pcVar1 = &DAT_802c3bc8;
      while( true ) {
        if (*pcVar1 < '\0') break;
        zz_00119d4_(pcVar1);
        pcVar1 = pcVar1 + 6;
      }
    }
  }
  return;
}



// ==== 80011b68  zz_0011b68_ ====

void zz_0011b68_(void)

{
  char *pcVar1;
  
  if (PTR_DAT_80433930[0x29] == '\x02') {
    zz_009cb0c_();
  }
  else {
    pcVar1 = &DAT_802c3c28;
    while( true ) {
      if (*pcVar1 < '\0') break;
      zz_00119d4_(pcVar1);
      pcVar1 = pcVar1 + 6;
    }
  }
  return;
}



// ==== 80011bcc  zz_0011bcc_ ====

void zz_0011bcc_(void)

{
  undefined4 local_8;
  undefined2 local_4;
  
  local_8 = DAT_80436ba8;
  local_4 = DAT_80436bac;
  if (PTR_DAT_80433930[0x40] == '\0') {
    zz_00119d4_((undefined1 *)&local_8);
    zz_00f03c0_(0,0x76);
  }
  return;
}



// ==== 80011c1c  zz_0011c1c_ ====

void zz_0011c1c_(void)

{
  undefined4 local_8;
  undefined2 local_4;
  
  local_8 = DAT_80436bb0;
  local_4 = DAT_80436bb4;
  if (PTR_DAT_80433930[0x40] == '\0') {
    zz_00119d4_((undefined1 *)&local_8);
  }
  return;
}



// ==== 80011c60  zz_0011c60_ ====

void zz_0011c60_(void)

{
  undefined4 local_8;
  undefined2 local_4;
  
  local_8 = DAT_80436bb8;
  local_4 = DAT_80436bbc;
  if (PTR_DAT_80433930[0x40] == '\0') {
    if ((PTR_DAT_80433934[0x15dd] != '\0') && ((char)PTR_DAT_80433934[0x45] < '\x05')) {
      zz_00119d4_((undefined1 *)&local_8);
    }
  }
  return;
}



// ==== 80011cc4  zz_0011cc4_ ====

void zz_0011cc4_(int param_1,int param_2)

{
  (&DAT_804360e0)[param_1] = (&DAT_804360e0)[param_1] | (byte)(1 << param_2);
  return;
}



// ==== 80011ce0  zz_0011ce0_ ====

undefined4 zz_0011ce0_(int param_1)

{
  char cVar1;
  
  cVar1 = (&PTR_s_CKPT00_CP000_B_802c3990)[param_1][0xd];
  if (cVar1 == 'C') {
    return 2;
  }
  if (cVar1 < 'C') {
    if (cVar1 == 'A') {
      return 0;
    }
    if ('@' < cVar1) {
      return 1;
    }
  }
  else if (cVar1 < 'E') {
    return 3;
  }
  return 0;
}



// ==== 80011d48  FUN_80011d48 ====

void FUN_80011d48(int param_1)

{
  if (((*(char *)(param_1 + 0x18) < '\x02') && (PTR_DAT_80433934[0x45] == '\x05')) &&
     ('\x01' < (char)PTR_DAT_80433934[0x52])) {
    *(undefined1 *)(param_1 + 0x82) = 0;
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  (*(code *)(&PTR_FUN_802c45c0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80011dc4  FUN_80011dc4 ====

void FUN_80011dc4(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int extraout_r4;
  int extraout_r4_00;
  int extraout_r4_01;
  int extraout_r4_02;
  int extraout_r4_03;
  int extraout_r4_04;
  int extraout_r4_05;
  int extraout_r4_06;
  int extraout_r4_07;
  int extraout_r4_08;
  int extraout_r4_09;
  int extraout_r4_10;
  int extraout_r4_11;
  int extraout_r4_12;
  
  if (('\x02' < (char)PTR_DAT_80433934[0x45]) || (*(char *)(param_9 + 0x11) == '\n')) {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined1 *)(param_9 + 0x82) = 0x11;
    iVar1 = (&DAT_803c4e84)[(char)PTR_DAT_80433934[0xc0]];
    *(int *)(param_9 + 0x90) = iVar1;
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(iVar1 + 0x3e4);
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(iVar1 + 1000);
    *(undefined1 *)(param_9 + 0x174) = *(undefined1 *)(iVar1 + 0x491);
    *(undefined1 *)(param_9 + 0x172) = 0xff;
    switch(*(undefined1 *)(param_9 + 0x11)) {
    case 0:
      param_1 = (double)zz_00122c8_(param_9,iVar1,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      iVar1 = extraout_r4;
      break;
    case 2:
      param_1 = (double)zz_0012d08_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,iVar1,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      iVar1 = extraout_r4_00;
      break;
    case 3:
      param_1 = (double)zz_0013304_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,iVar1,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      iVar1 = extraout_r4_01;
      break;
    case 4:
      param_1 = (double)zz_0013608_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,iVar1,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      iVar1 = extraout_r4_02;
      break;
    case 5:
      param_1 = (double)zz_00139e0_(param_9);
      iVar1 = extraout_r4_03;
      break;
    case 6:
      param_1 = (double)zz_0013e54_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,iVar1,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      iVar1 = extraout_r4_04;
      break;
    case 7:
      param_1 = (double)zz_00149f8_(param_9);
      iVar1 = extraout_r4_05;
      break;
    case 8:
      param_1 = (double)zz_0015bf0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,iVar1,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      iVar1 = extraout_r4_06;
      break;
    case 9:
      param_1 = (double)zz_00162b0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9);
      iVar1 = extraout_r4_07;
      break;
    case 10:
      param_1 = (double)zz_0016528_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,iVar1,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      iVar1 = extraout_r4_08;
      break;
    case 0xb:
      param_1 = (double)zz_0016934_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,iVar1,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      iVar1 = extraout_r4_09;
      break;
    case 0xf:
      param_1 = (double)zz_0016ed8_(param_9);
      iVar1 = extraout_r4_10;
      break;
    case 0x10:
      param_1 = (double)zz_00172cc_(param_9,iVar1,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      iVar1 = extraout_r4_11;
      break;
    case 0x11:
      param_1 = (double)zz_0017610_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,iVar1,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      iVar1 = extraout_r4_12;
    }
    zz_0011f30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar1,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80011f30  zz_0011f30_ ====

void zz_0011f30_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if (((*(char *)(param_9 + 0x171) == '\0') &&
      (param_10 = (&DAT_803c4e84)[(char)PTR_DAT_80433934[0xc0]],
      *(char *)(param_10 + 0x18) == '\x01')) &&
     ((*(short *)(param_9 + 0x94) != *(short *)(param_10 + 1000) ||
      ((*(char *)(param_9 + 0x96) != *(char *)(param_10 + 0x3e4) ||
       (*(char *)(param_9 + 0x174) != *(char *)(param_10 + 0x491))))))) {
    *(undefined1 *)(param_9 + 0x172) = 0xff;
    *(int *)(param_9 + 0x90) = param_10;
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(param_10 + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(param_10 + 0x3e4);
    *(undefined1 *)(param_9 + 0x174) = *(undefined1 *)(param_10 + 0x491);
  }
  switch(*(undefined1 *)(param_9 + 0x11)) {
  case 0:
    zz_00122e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 2:
    zz_0012e4c_(param_9,param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 5:
    zz_0013a28_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 6:
    zz_00141d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 7:
    zz_00156cc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
    break;
  case 8:
    zz_0015ca8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 9:
    zz_0016364_(param_9);
    break;
  case 10:
    zz_00165cc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 0xb:
    FUN_800169f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 0xf:
    zz_0016f38_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 0x10:
    zz_0017380_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 0x11:
    zz_0017708_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800120b0  FUN_800120b0 ====

void FUN_800120b0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800120c4  FUN_800120c4 ====

void FUN_800120c4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9,
                 undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
                 undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = 0;
  puVar2 = (undefined4 *)(param_9 + 0x144);
  do {
    if ((int *)*puVar2 != (int *)0x0) {
      param_1 = zz_0006d80_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int *)*puVar2,param_10,param_11,param_12,param_13,param_14,param_15,
                            param_16);
      param_10 = extraout_r4;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 8);
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8001212c  FUN_8001212c ====

void FUN_8001212c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined *param_12,undefined4 *param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  if ((((-1 < *(short *)(param_9 + 0x94)) && (-1 < *(char *)(param_9 + 0x96))) &&
      (cVar1 = zz_008b290_(), cVar1 == '\0')) &&
     (((PTR_DAT_80433934[0x1833] == '\0' && (PTR_DAT_80433934[0x1832] == '\0')) &&
      (PTR_DAT_80433930[0x33] == '\0')))) {
    switch(*(undefined1 *)(param_9 + 0x11)) {
    case 0:
      zz_0012984_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 2:
      zz_00131b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 3:
      zz_00133f4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 4:
      zz_0013690_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      break;
    case 5:
      zz_0013d80_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 6:
      zz_00147e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 7:
      zz_0015a30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 8:
      FUN_80015ef0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 9:
      zz_00164e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 10:
      zz_0016844_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xb:
      FUN_80016c70(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xf:
      zz_00171e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0x10:
      zz_0017558_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0x11:
      zz_001783c_(param_9);
    }
  }
  return;
}



// ==== 80012274  FUN_80012274 ====

void FUN_80012274(int param_1)

{
  FUN_80047aa4(param_1);
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + 0x114),(float *)(param_1 + 0x164),(float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 800122c8  zz_00122c8_ ====

void zz_00122c8_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  zz_0012308_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 800122e8  zz_00122e8_ ====

void zz_00122e8_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  zz_0012638_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80012308  zz_0012308_ ====

void zz_0012308_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  undefined *puVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  undefined8 uVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  *(code **)(param_1 + 0x100) = FUN_80012274;
  zz_0089100_(param_1,0x21,1);
  *(undefined1 *)(param_1 + 0x84) = 3;
  *(undefined2 *)(param_1 + 0x70) = 0;
  dVar13 = DOUBLE_80436bd0;
  *(undefined2 *)(param_1 + 0x7c) = 0x444;
  fVar2 = FLOAT_80436bc0;
  dVar14 = (double)FLOAT_80436bc0;
  *(undefined2 *)(param_1 + 0x1c) = 0x14;
  fVar4 = FLOAT_80436bc8;
  fVar3 = FLOAT_80436bc4;
  dVar10 = (double)FLOAT_80436bc4;
  dVar12 = -(double)(float)(dVar14 / (double)(float)((double)CONCAT44(0x43300000,
                                                                      (int)*(short *)(param_1 + 0x1c
                                                                                     ) ^ 0x80000000)
                                                    - dVar13));
  *(float *)(param_1 + 0x38) = (float)dVar12;
  *(float *)(param_1 + 100) = fVar3;
  *(float *)(param_1 + 0x68) = fVar3;
  *(float *)(param_1 + 0x6c) = fVar4;
  *(float *)(param_1 + 0x164) = fVar2;
  *(float *)(param_1 + 0x16c) = fVar3;
  *(float *)(param_1 + 0x168) = fVar3;
  iVar1 = DAT_804361fc;
  uVar11 = zz_0006fb4_(dVar10,dVar12,dVar13,dVar14,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
                       *(int *)(param_1 + 0x144),(int)*(char *)(param_1 + 0x12),param_4,param_5,
                       param_6,param_7,param_8);
  iVar8 = *(int *)(param_1 + 0x148);
  zz_0006fb4_(uVar11,dVar12,dVar13,dVar14,in_f5,in_f6,in_f7,in_f8,iVar1,iVar8,
              (int)*(char *)(param_1 + 0x12),param_4,param_5,param_6,param_7,param_8);
  zz_0007cd0_(iVar8,0xff,0xea,0);
  uVar7 = 0;
  uVar11 = zz_0007cf4_(iVar8,0xe5,0xb2,0);
  iVar8 = 0;
  iVar9 = param_1 + 0x144;
  do {
    uVar11 = zz_0006fb4_(uVar11,dVar12,dVar13,dVar14,in_f5,in_f6,in_f7,in_f8,iVar1,
                         *(int *)(iVar9 + 8),*(char *)(param_1 + 0x12) * 2 + 2,uVar7,param_5,param_6
                         ,param_7,param_8);
    iVar8 = iVar8 + 1;
    iVar9 = iVar9 + 4;
  } while (iVar8 < 6);
  cVar5 = PTR_DAT_80433930[0x29];
  if (cVar5 == '\x02') goto LAB_800125b0;
  if (cVar5 < '\x02') {
    if (cVar5 == '\0') {
      if (*(char *)(param_1 + 0x12) == '\0') {
        cVar5 = '\0';
        iVar8 = (int)(char)PTR_DAT_80433934[0x53];
        puVar6 = PTR_DAT_80433934;
        if (0 < iVar8) {
          do {
            if (puVar6[0xf4] == PTR_DAT_80433934[(char)PTR_DAT_80433934[0xc0] + 0xcb]) {
              *(char *)(param_1 + 400) = cVar5;
              break;
            }
            puVar6 = puVar6 + 0x3c;
            cVar5 = cVar5 + '\x01';
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
      }
      else {
        cVar5 = '\0';
        iVar8 = (int)(char)PTR_DAT_80433934[0x53];
        puVar6 = PTR_DAT_80433934;
        if (0 < iVar8) {
          do {
            if (puVar6[0xf4] != PTR_DAT_80433934[(char)PTR_DAT_80433934[0xc0] + 0xcb]) {
              *(char *)(param_1 + 400) = cVar5;
              break;
            }
            puVar6 = puVar6 + 0x3c;
            cVar5 = cVar5 + '\x01';
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
      }
      goto LAB_800125b0;
    }
    if (cVar5 < '\0') goto LAB_800125b0;
  }
  else if ('\x03' < cVar5) goto LAB_800125b0;
  if (*(char *)(param_1 + 0x12) == '\0') {
    cVar5 = '\0';
    iVar8 = (int)(char)PTR_DAT_80433934[0x53];
    puVar6 = PTR_DAT_80433934;
    if (0 < iVar8) {
      do {
        if (puVar6[0xf4] ==
            PTR_DAT_80433934[(char)PTR_DAT_80433934[*(char *)(param_1 + 0x173) + 0xc0] + 0xcb]) {
          *(char *)(param_1 + 400) = cVar5;
          break;
        }
        puVar6 = puVar6 + 0x3c;
        cVar5 = cVar5 + '\x01';
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  else {
    cVar5 = '\0';
    iVar8 = (int)(char)PTR_DAT_80433934[0x53];
    puVar6 = PTR_DAT_80433934;
    if (0 < iVar8) {
      do {
        if (puVar6[0xf4] !=
            PTR_DAT_80433934[(char)PTR_DAT_80433934[*(char *)(param_1 + 0x173) + 0xc0] + 0xcb]) {
          *(char *)(param_1 + 400) = cVar5;
          break;
        }
        puVar6 = puVar6 + 0x3c;
        cVar5 = cVar5 + '\x01';
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
LAB_800125b0:
  fVar2 = FLOAT_80436bcc;
  *(float *)(param_1 + 0x180) = FLOAT_80436bcc;
  *(float *)(param_1 + 0x17c) = fVar2;
  iVar8 = *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 400) * 0x3c + 0x118);
  *(int *)(param_1 + 0x18c) = iVar8 + -1;
  *(int *)(param_1 + 0x184) = iVar8 + -1;
  uVar11 = zz_0006fb4_(uVar11,dVar12,dVar13,dVar14,in_f5,in_f6,in_f7,in_f8,iVar1,
                       *(int *)(param_1 + 0xe0),*(char *)(param_1 + 0x12) * 2 + 3,uVar7,param_5,
                       param_6,param_7,param_8);
  if (*(char *)(param_1 + 0x12) == '\0') {
    zz_0006fb4_(uVar11,dVar12,dVar13,dVar14,in_f5,in_f6,in_f7,in_f8,iVar1,*(int *)(param_1 + 0xe4),
                0x57,uVar7,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 80012638  zz_0012638_ ====

void zz_0012638_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  bool bVar2;
  undefined *puVar3;
  float fVar4;
  short sVar6;
  int iVar5;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined4 extraout_r4;
  uint uVar10;
  float *pfVar11;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar12;
  int iVar13;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  
  if (*(char *)(param_9 + 0x176) != '\x02') {
    cVar1 = *(char *)(param_9 + 0x19);
    if (((cVar1 != '\x01') && (cVar1 < '\x01')) && (-1 < cVar1)) {
      sVar6 = *(short *)(param_9 + 0x1c) + -1;
      *(short *)(param_9 + 0x1c) = sVar6;
      fVar4 = FLOAT_80436bc4;
      if (sVar6 < 1) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
        *(float *)(param_9 + 0x164) = fVar4;
      }
      else {
        *(float *)(param_9 + 0x164) = *(float *)(param_9 + 0x164) + *(float *)(param_9 + 0x38);
      }
    }
  }
  *(short *)(param_9 + 0x70) = *(short *)(param_9 + 0x70) - *(short *)(param_9 + 0x7c);
  puVar3 = PTR_DAT_80433934;
  iVar5 = *(char *)(param_9 + 400) * 0x3c;
  if (*(int *)(PTR_DAT_80433934 + iVar5 + 0x114) < 1) {
    *(float *)(param_9 + 0x17c) = FLOAT_80436bc4;
    *(undefined1 *)(param_9 + 0x170) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0x170) = 1;
    *(float *)(param_9 + 0x17c) =
         (float)((double)CONCAT44(0x43300000,*(uint *)(puVar3 + iVar5 + 0x118) ^ 0x80000000) -
                DOUBLE_80436bd0) /
         (float)((double)CONCAT44(0x43300000,*(uint *)(puVar3 + iVar5 + 0x114) ^ 0x80000000) -
                DOUBLE_80436bd0);
    iVar7 = *(int *)(puVar3 + iVar5 + 0x118);
    if (*(int *)(param_9 + 0x184) != iVar7) {
      if (iVar7 != *(int *)(param_9 + 0x18c)) {
        *(int *)(param_9 + 0x18c) = iVar7;
        uVar10 = *(int *)(param_9 + 0x184) - *(int *)(puVar3 + iVar5 + 0x118);
        uVar8 = (int)uVar10 >> 0x1f;
        iVar7 = (uVar8 ^ uVar10) - uVar8;
        if (iVar7 < 0x3d) {
          *(undefined4 *)(param_9 + 0x188) = 1;
        }
        else {
          iVar7 = iVar7 / 0x3c + (iVar7 >> 0x1f);
          *(int *)(param_9 + 0x188) = (iVar7 - (iVar7 >> 0x1f)) + 1;
        }
      }
      iVar7 = *(int *)(param_9 + 0x184);
      iVar9 = *(int *)(puVar3 + iVar5 + 0x118);
      if (iVar7 < iVar9) {
        iVar13 = iVar9 - iVar7;
        if (*(int *)(param_9 + 0x188) < iVar9 - iVar7) {
          iVar13 = *(int *)(param_9 + 0x188);
        }
        *(int *)(param_9 + 0x184) = *(int *)(param_9 + 0x184) + iVar13;
      }
      else {
        iVar13 = iVar7 - iVar9;
        if (*(int *)(param_9 + 0x188) < iVar7 - iVar9) {
          iVar13 = *(int *)(param_9 + 0x188);
        }
        *(int *)(param_9 + 0x184) = *(int *)(param_9 + 0x184) - iVar13;
      }
      dVar16 = DOUBLE_80436bd0;
      pfVar11 = (float *)0x43300000;
      uVar8 = *(uint *)(param_9 + 0x184) ^ 0x80000000;
      *(float *)(param_9 + 0x180) =
           (float)((double)CONCAT44(0x43300000,uVar8) - DOUBLE_80436bd0) /
           (float)((double)CONCAT44(0x43300000,*(uint *)(puVar3 + iVar5 + 0x114) ^ 0x80000000) -
                  DOUBLE_80436bd0);
      iVar5 = *(int *)(param_9 + 0x184);
      if (999999 < *(int *)(param_9 + 0x184)) {
        iVar5 = 999999;
      }
      if (iVar5 < 0) {
        iVar5 = 0;
      }
      bVar2 = false;
      iVar7 = 100000;
      iVar13 = param_9 + 0x144;
      for (iVar9 = 0; iVar9 < 6; iVar9 = iVar9 + 1) {
        if ((!bVar2) && ((iVar5 / iVar7 != 0 || (iVar7 == 1)))) {
          bVar2 = true;
          *(char *)(param_9 + 0x1b) = '\x06' - (char)iVar9;
        }
        dVar15 = DOUBLE_80436bd0;
        iVar12 = *(int *)(iVar13 + 8);
        if (bVar2) {
          *(undefined1 *)(iVar12 + 0x10) = 1;
          uVar14 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                                iVar5 / iVar7 ^ 0x80000000) - dVar15
                                              ),dVar16,param_3,param_4,param_5,param_6,param_7,
                               param_8,DAT_804361fc,iVar12,pfVar11,uVar8,in_r7,in_r8,in_r9,in_r10);
          zz_0007c30_(uVar14,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,iVar12,
                      extraout_r4,pfVar11,uVar8,in_r7,in_r8,in_r9,in_r10);
        }
        else {
          *(undefined1 *)(iVar12 + 0x10) = 0;
        }
        iVar13 = iVar13 + 4;
        iVar12 = iVar7 / 10 + (iVar7 >> 0x1f);
        iVar5 = iVar5 - (iVar5 / iVar7) * iVar7;
        iVar7 = iVar12 - (iVar12 >> 0x1f);
      }
      iVar7 = *(int *)(param_9 + 0xe0);
      dVar15 = (double)(float)((double)CONCAT44(0x43300000,
                                                (int)*(char *)(param_9 + 0x1b) ^ 0x80000000) -
                              DOUBLE_80436bd0);
      iVar5 = iVar7;
      zz_0008614_(dVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,iVar7,
                  pfVar11,uVar8,in_r7,in_r8,in_r9,in_r10);
      zz_0007c30_(dVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,iVar5,pfVar11,
                  uVar8,in_r7,in_r8,in_r9,in_r10);
    }
  }
  return;
}



// ==== 80012984  zz_0012984_ ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zz_0012984_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [13];
  undefined4 local_18;
  uint uStack_14;
  
  if (*(char *)(param_9 + 0x12) == '\0') {
    dVar9 = (double)FLOAT_80436bd8;
    param_11 = &local_58;
    local_58 = FLOAT_80436bd8;
    local_54 = FLOAT_80436bdc;
    local_50 = FLOAT_80436bc4;
    iVar5 = *(int *)(param_9 + 0xe4);
    uVar8 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),param_11,param_11);
    zz_0007834_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,&local_58,
                (char *)param_11,param_12,param_13,param_14,param_15,param_16);
    iVar2 = zz_0011ce0_(*(int *)(iVar5 + 0x14));
    zz_0009958_(iVar5,iVar2);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    cVar1 = *(char *)(param_9 + 400);
    iVar2 = (int)*(char *)(param_9 + 0x12);
    if ((double)FLOAT_80436be0 < (double)*(float *)(param_9 + 0x17c)) {
      iVar6 = *(int *)(param_9 + 0x144);
      zz_020b520_((double)*(float *)(param_9 + 0x17c),(double)FLOAT_80436bcc,(double)FLOAT_80436bcc,
                  (float *)(param_9 + 0x114),afStack_4c);
      iVar5 = iVar2 * 8;
      dVar10 = (double)FLOAT_80436bc4;
      param_12 = &DAT_802c46a8;
      param_11 = (float *)(&DAT_802c46a8 + iVar5);
      dVar9 = (double)*(float *)(&DAT_802c46ac + iVar5);
      uVar8 = zz_020b4ac_((double)*(float *)(&DAT_802c46a8 + iVar5),dVar9,dVar10,afStack_4c,
                          afStack_4c);
      zz_00076d0_(uVar8,dVar9,dVar10,param_4,param_5,param_6,param_7,param_8,iVar6,afStack_4c,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      iVar5 = zz_0011ce0_(*(int *)(iVar6 + 0x14));
      zz_0009958_(iVar6,iVar5);
    }
    if (*(int *)(param_9 + 0x184) != *(int *)(PTR_DAT_80433934 + cVar1 * 0x3c + 0x118)) {
      iVar5 = *(int *)(param_9 + 0x148);
      local_50 = FLOAT_80436bc4;
      local_54 = FLOAT_80436bc4;
      zz_020b520_((double)(*(float *)(param_9 + 0x180) - *(float *)(param_9 + 0x17c)),
                  (double)FLOAT_80436bcc,(double)FLOAT_80436bcc,(float *)(param_9 + 0x114),
                  afStack_4c);
      if (iVar2 == 0) {
        dVar9 = (double)_DAT_802c46ac;
        dVar10 = (double)FLOAT_80436bc4;
        uVar8 = zz_020b4ac_((double)(FLOAT_80436be4 * *(float *)(param_9 + 0x17c) + _DAT_802c46a8),
                            dVar9,dVar10,afStack_4c,afStack_4c);
      }
      else {
        dVar9 = (double)*(float *)(&DAT_802c46ac + iVar2 * 8);
        dVar10 = (double)FLOAT_80436bc4;
        uVar8 = zz_020b4ac_(-(double)(FLOAT_80436be4 * *(float *)(param_9 + 0x17c) -
                                     *(float *)(&DAT_802c46a8 + iVar2 * 8)),dVar9,dVar10,afStack_4c,
                            afStack_4c);
      }
      zz_00076d0_(uVar8,dVar9,dVar10,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_4c,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      iVar6 = zz_0011ce0_(*(int *)(iVar5 + 0x14));
      zz_0009958_(iVar5,iVar6);
    }
    iVar5 = *(int *)(param_9 + 0xe0);
    if (iVar2 == 0) {
      local_58 = FLOAT_80436be4 * *(float *)(param_9 + 0x180) + _DAT_802c46a8;
      local_54 = FLOAT_80436be8;
    }
    else {
      local_58 = -(FLOAT_80436be4 * *(float *)(param_9 + 0x180) -
                  *(float *)(&DAT_802c46a8 + iVar2 * 8));
      local_54 = FLOAT_80436bec;
    }
    pfVar4 = &local_58;
    local_50 = FLOAT_80436bc4;
    gnt4_PSVECAdd_bl(pfVar4,(float *)(param_9 + 0x20),pfVar4);
    dVar9 = (double)local_54;
    dVar10 = (double)local_50;
    uVar8 = gnt4_PSMTXTrans_bl((double)local_58,dVar9,dVar10,afStack_4c);
    zz_00076d0_(uVar8,dVar9,dVar10,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_4c,
                (undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
    iVar6 = zz_0011ce0_(*(int *)(iVar5 + 0x14));
    zz_0009958_(iVar5,iVar6);
    iVar5 = iVar2 * 0xc;
    dVar10 = (double)FLOAT_80436bc4;
    dVar9 = (double)*(float *)(&DAT_802c46bc + iVar5);
    uVar8 = zz_020b4ac_((double)*(float *)(&DAT_802c46b8 + iVar5),dVar10,dVar9,afStack_4c,afStack_4c
                       );
    if (iVar2 == 1) {
      param_12 = (undefined *)0x43300000;
      dVar10 = (double)FLOAT_80436bc4;
      uStack_14 = (int)*(char *)(param_9 + 0x1b) ^ 0x80000000;
      pfVar4 = (float *)0x802c46c4;
      local_18 = 0x43300000;
      dVar9 = dVar10;
      param_4 = DOUBLE_80436bd0;
      uVar8 = zz_020b4ac_(-(double)((float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80436bd0
                                           ) * fRam802c46cc),dVar10,dVar10,afStack_4c,afStack_4c);
    }
    iVar6 = param_9 + 0x158;
    iVar2 = 5;
    do {
      iVar7 = *(int *)(iVar6 + 8);
      zz_00076d0_(uVar8,dVar10,dVar9,param_4,param_5,param_6,param_7,param_8,iVar7,afStack_4c,
                  (undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
      iVar3 = zz_0011ce0_(*(int *)(iVar7 + 0x14));
      zz_0009958_(iVar7,iVar3);
      dVar10 = (double)FLOAT_80436bc4;
      dVar9 = dVar10;
      uVar8 = zz_020b4ac_((double)*(float *)(&DAT_802c46c0 + iVar5),dVar10,dVar10,afStack_4c,
                          afStack_4c);
      iVar2 = iVar2 + -1;
      iVar6 = iVar6 + -4;
    } while (-1 < iVar2);
  }
  return;
}



// ==== 80012d08  zz_0012d08_ ====

void zz_0012d08_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  undefined8 uVar6;
  
  iVar4 = DAT_804361fc;
  if (PTR_DAT_80433934[0x50] == '\0') {
    *(code **)(param_9 + 0x100) = FUN_80012274;
    zz_0089100_(param_9,0x21,1);
    fVar1 = FLOAT_80436bf0;
    *(undefined1 *)(param_9 + 0x84) = 9;
    fVar2 = FLOAT_80436bf4;
    *(float *)(param_9 + 100) = fVar1;
    fVar3 = FLOAT_80436bf8;
    dVar5 = (double)FLOAT_80436bf8;
    *(float *)(param_9 + 0x68) = fVar2;
    fVar1 = FLOAT_80436bc4;
    *(float *)(param_9 + 0x6c) = fVar3;
    *(undefined2 *)(param_9 + 0x74) = 0;
    *(float *)(param_9 + 0x16c) = fVar1;
    *(float *)(param_9 + 0x168) = fVar1;
    *(float *)(param_9 + 0x164) = fVar1;
    *(undefined4 *)(*(int *)(param_9 + 0x14c) + 0x14) = 0xffffffff;
    *(undefined4 *)(*(int *)(param_9 + 0x148) + 0x14) = 0xffffffff;
    *(undefined4 *)(*(int *)(param_9 + 0x144) + 0x14) = 0xffffffff;
    *(undefined1 *)(param_9 + 0x192) = 0xff;
    *(undefined1 *)(param_9 + 0x191) = 0xff;
    *(undefined1 *)(param_9 + 400) = 0xff;
    uVar6 = zz_0006fb4_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                        *(int *)(param_9 + 0x15c),0xf,param_12,param_13,param_14,param_15,param_16);
    zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                *(int *)(param_9 + 0x160),0xe,param_12,param_13,param_14,param_15,param_16);
    *(undefined4 *)(param_9 + 0x188) = 0;
    iVar4 = *(int *)(PTR_DAT_80433934 + 0x4c) - *(int *)(param_9 + 0x188);
    if (iVar4 < 0x51) {
      *(undefined4 *)(param_9 + 0x18c) = 1;
    }
    else {
      iVar4 = iVar4 / 0x50 + (iVar4 >> 0x1f);
      *(int *)(param_9 + 0x18c) = (iVar4 - (iVar4 >> 0x1f)) + 1;
    }
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 80012e4c  zz_0012e4c_ ====

void zz_0012e4c_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  FUN_80012e74(param_1,-0x7fd3c480,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80012e74  FUN_80012e74 ====

/* WARNING: Removing unreachable block (ram,0x8001319c) */
/* WARNING: Removing unreachable block (ram,0x80012e84) */

void FUN_80012e74(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  float *pfVar10;
  int *piVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar17;
  double local_58;
  undefined8 local_50;
  undefined8 local_48;
  
  iVar5 = *(int *)(PTR_DAT_80433934 + 0x4c);
  if (*(char *)(param_1 + 0x19) == '\0') {
    iVar5 = *(int *)(param_1 + 0x188);
    if (*(int *)(param_1 + 0x18c) != 0) {
      iVar1 = *(int *)(PTR_DAT_80433934 + 0x48);
      iVar5 = *(int *)(param_1 + 0x188) + *(int *)(param_1 + 0x18c);
      if (iVar1 <= iVar5) {
        *(undefined4 *)(param_1 + 0x18c) = 0;
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        iVar5 = iVar1;
      }
    }
  }
  local_58 = (double)(CONCAT44(0x43300000,iVar5) ^ 0x80000000);
  local_50 = (double)CONCAT44(0x43300000,*(uint *)(PTR_DAT_80433934 + 0x48) ^ 0x80000000);
  *(short *)(param_1 + 0x74) =
       (short)(int)-(FLOAT_80436bfc *
                     ((float)(local_58 - DOUBLE_80436bd0) / (float)(local_50 - DOUBLE_80436bd0)) -
                    FLOAT_80436bfc);
  if (*(int *)(param_1 + 0x188) != iVar5) {
    *(int *)(param_1 + 0x188) = iVar5;
    iVar5 = iVar5 / 0x3c + (iVar5 >> 0x1f);
    iVar5 = iVar5 - (iVar5 >> 0x1f);
    if (999 < iVar5) {
      iVar5 = 999;
    }
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
    if (((*(char *)(param_1 + 0x19) == '\0') || (0x1d < iVar5)) ||
       ((*(ushort *)(param_1 + 0x1c) & 8) == 0)) {
      *(undefined1 *)(param_1 + 0x193) = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x193) = 1;
    }
    iVar1 = *(int *)(param_1 + 0x160);
    local_48 = (double)(CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x193)) ^ 0x80000000);
    dVar16 = (double)(float)(local_48 - DOUBLE_80436bd0);
    dVar13 = DOUBLE_80436c00 * DOUBLE_80436c08 * dVar16;
    dVar14 = (double)(longlong)(int)(DOUBLE_80436c00 * dVar16);
    dVar17 = (double)(float)((double)FLOAT_80436c14 * dVar16 + (double)FLOAT_80436c10);
    dVar15 = DOUBLE_80436c00;
    zz_0007cd0_(iVar1,(int)(DOUBLE_80436c00 * dVar16) & 0xff,(int)dVar13 & 0xff,0);
    uVar12 = zz_0007cac_(dVar17,iVar1);
    iVar1 = 0;
    for (psVar2 = &DAT_802c3b68; iVar5 < *psVar2; psVar2 = psVar2 + 4) {
      iVar1 = iVar1 + 1;
    }
    iVar6 = iVar1 * 6;
    pfVar4 = (float *)(iVar1 * 8);
    piVar11 = (int *)(param_1 + 0x144);
    pfVar10 = pfVar4 + -0x1ff4f126;
    iVar1 = iVar1 * 0x18;
    iVar8 = 0;
    uVar9 = 100;
    do {
      piVar11[0xe] = param_2 + iVar1;
      iVar3 = (int)*(short *)((int)pfVar10 + 2);
      if (*(int *)(*piVar11 + 0x14) != iVar3) {
        *(int *)(piVar11[3] + 0x14) = iVar3;
        *(int *)(*piVar11 + 0x14) = iVar3;
        pfVar4 = *(float **)(*piVar11 + 0x14);
        if (-1 < (int)pfVar4) {
          uVar12 = zz_0006fb4_(uVar12,dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,in_f8,DAT_804361fc,
                               *piVar11,(int)pfVar4,iVar6,param_5,param_6,param_7,param_8);
          pfVar4 = (float *)(*(int *)(*piVar11 + 0x14) + 4);
          uVar12 = zz_0006fb4_(uVar12,dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,in_f8,DAT_804361fc,
                               piVar11[3],(int)pfVar4,iVar6,param_5,param_6,param_7,param_8);
        }
      }
      dVar17 = DOUBLE_80436bd0;
      if (-1 < *(int *)(*piVar11 + 0x14)) {
        uVar7 = iVar5 / (int)uVar9;
        if (*(char *)(param_1 + iVar8 + 400) != (char)uVar7) {
          local_48 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
          *(char *)(param_1 + iVar8 + 400) = (char)uVar7;
          zz_00086b8_((double)(float)(local_48 - dVar17),dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,
                      in_f8,DAT_804361fc,*piVar11,pfVar4,iVar6,param_5,param_6,param_7,param_8);
          local_50 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
          uVar12 = zz_00086b8_((double)(float)(local_50 - DOUBLE_80436bd0),dVar13,dVar14,dVar15,
                               dVar16,in_f6,in_f7,in_f8,DAT_804361fc,piVar11[3],pfVar4,iVar6,param_5
                               ,param_6,param_7,param_8);
          uVar12 = zz_0007c30_(uVar12,dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,in_f8,*piVar11,
                               extraout_r4,pfVar4,iVar6,param_5,param_6,param_7,param_8);
          uVar12 = zz_0007c30_(uVar12,dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,in_f8,piVar11[3],
                               extraout_r4_00,pfVar4,iVar6,param_5,param_6,param_7,param_8);
        }
      }
      iVar8 = iVar8 + 1;
      iVar1 = iVar1 + 8;
      piVar11 = piVar11 + 1;
      pfVar10 = (float *)((int)pfVar10 + 2);
      iVar3 = (iVar5 / (int)uVar9) * uVar9;
      uVar9 = uVar9 / 10;
      iVar5 = iVar5 - iVar3;
    } while (iVar8 < 3);
  }
  return;
}



// ==== 800131b8  zz_00131b8_ ====

void zz_00131b8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [12];
  float afStack_4c [15];
  
  iVar3 = *(int *)(param_9 + 0x15c);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  iVar3 = *(int *)(param_9 + 0x160);
  pfVar2 = &local_88;
  local_88 = FLOAT_80436bc4;
  local_84 = FLOAT_80436bc4;
  local_80 = FLOAT_80436c18;
  uVar6 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_0007834_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,&local_88,
              (char *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  iVar1 = 0;
  piVar5 = (int *)(param_9 + 0x144);
  do {
    if (-1 < *(int *)(*piVar5 + 0x14)) {
      iVar4 = *(int *)(param_9 + (iVar1 + *(char *)(param_9 + 0x193) * 3) * 4 + 0x144);
      gnt4_PSMTXTrans_bl((double)*(float *)piVar5[0xe],(double)((float *)piVar5[0xe])[1],
                         (double)FLOAT_80436bc8,afStack_4c);
      dVar7 = (double)FLOAT_80436c1c;
      dVar8 = (double)FLOAT_80436bcc;
      gnt4_PSMTXScale_bl(dVar7,dVar7,dVar8,afStack_7c);
      pfVar2 = afStack_4c;
      uVar6 = gnt4_PSMTXConcat_bl(pfVar2,afStack_7c,pfVar2);
      zz_00076d0_(uVar6,dVar7,dVar8,param_4,param_5,param_6,param_7,param_8,iVar4,afStack_4c,
                  (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
      iVar3 = zz_0011ce0_(*(int *)(iVar4 + 0x14));
      zz_0009958_(iVar4,iVar3);
    }
    iVar1 = iVar1 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar1 < 3);
  return;
}



// ==== 80013304  zz_0013304_ ====

void zz_0013304_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  double dVar3;
  undefined8 uVar4;
  
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  fVar1 = FLOAT_80436c20;
  *(undefined1 *)(param_9 + 0x84) = 1;
  fVar2 = FLOAT_80436c24;
  dVar3 = (double)FLOAT_80436c24;
  *(float *)(param_9 + 100) = fVar1;
  fVar1 = FLOAT_80436c28;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar1;
  uVar4 = zz_0006fb4_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe0),7,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe4),8,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe8),10,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x144),6,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x148),0xb,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x14c),0xb,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x150),0xc,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x154),0xc,param_12,param_13,param_14,param_15,param_16);
  zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0x158),0xc,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800133f4  zz_00133f4_ ====

/* WARNING: Removing unreachable block (ram,0x800135e4) */
/* WARNING: Removing unreachable block (ram,0x800135dc) */
/* WARNING: Removing unreachable block (ram,0x8001340c) */
/* WARNING: Removing unreachable block (ram,0x80013404) */

void zz_00133f4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float afStack_a8 [12];
  float afStack_78 [12];
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  iVar3 = *(int *)(param_9 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  dVar7 = (double)FLOAT_80436c2c;
  dVar9 = (double)((float)(dVar7 * (double)*(float *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] +
                                                     0x20)) / *(float *)(DAT_8043625c + 0x38));
  local_48 = 0x43300000;
  uStack_44 = 0x10000U - (int)(short)(&DAT_803c7422)[(char)PTR_DAT_80433930[0x28] * 0x1f2] ^
              0x80000000;
  dVar8 = (double)(-(float)(dVar7 * (double)*(float *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] +
                                                      0x28)) / *(float *)(DAT_8043625c + 0x40));
  iVar4 = *(int *)(param_9 + 0xe4);
  iVar1 = DAT_8043625c;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80436c30 *
                              (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80436bd0)),
                      afStack_a8,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_a8,afStack_a8);
  dVar6 = (double)FLOAT_80436c34;
  gnt4_PSMTXTrans_bl(dVar9,dVar8,dVar6,afStack_78);
  pfVar2 = afStack_78;
  uVar5 = gnt4_PSMTXConcat_bl(afStack_a8,pfVar2,pfVar2);
  zz_00076d0_(uVar5,dVar8,dVar6,dVar7,param_5,param_6,param_7,param_8,iVar4,afStack_78,
              (undefined *)pfVar2,iVar1,param_13,param_14,param_15,param_16);
  iVar3 = zz_0011ce0_(*(int *)(iVar4 + 0x14));
  zz_0009958_(iVar4,iVar3);
  iVar3 = *(int *)(param_9 + 0xe8);
  dVar6 = (double)FLOAT_80436bcc;
  gnt4_PSMTXTrans_bl((double)FLOAT_80436bc4,(double)FLOAT_80436bc4,dVar6,afStack_78);
  gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_78,afStack_78);
  local_40 = 0x43300000;
  dVar8 = (double)FLOAT_80436c30;
  uStack_3c = 0x10000U - (int)(short)(&DAT_803c7422)[(char)PTR_DAT_80433930[0x28] * 0x1f2] ^
              0x80000000;
  gnt4_PSMTXRotRad_bl((double)(float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,uStack_3c)
                                                             - DOUBLE_80436bd0)),afStack_a8,0x7a);
  pfVar2 = afStack_78;
  uVar5 = gnt4_PSMTXConcat_bl(pfVar2,afStack_a8,pfVar2);
  zz_00076d0_(uVar5,dVar8,dVar6,dVar7,param_5,param_6,param_7,param_8,iVar3,afStack_78,
              (undefined *)pfVar2,iVar1,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  return;
}



// ==== 80013608  zz_0013608_ ====

void zz_0013608_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  double dVar3;
  undefined8 uVar4;
  
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  fVar1 = FLOAT_80436c20;
  *(undefined1 *)(param_9 + 0x84) = 9;
  fVar2 = FLOAT_80436c24;
  dVar3 = (double)FLOAT_80436c24;
  *(float *)(param_9 + 100) = fVar1;
  fVar1 = FLOAT_80436c38;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar1;
  *(undefined2 *)(param_9 + 0x74) = 0;
  uVar4 = zz_0006fb4_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x158),6,param_12,param_13,param_14,param_15,param_16);
  zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0x15c),9,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80013690  zz_0013690_ ====

/* WARNING: Removing unreachable block (ram,0x800139c4) */
/* WARNING: Removing unreachable block (ram,0x800139bc) */
/* WARNING: Removing unreachable block (ram,0x800136a8) */
/* WARNING: Removing unreachable block (ram,0x800136a0) */

void zz_0013690_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  int in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int *piVar13;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  float afStack_b8 [12];
  float afStack_88 [12];
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  
  puVar6 = &DAT_803c73b0;
  puVar5 = &DAT_803c4e84;
  local_58 = 0x43300000;
  dVar15 = (double)FLOAT_80436c30;
  iVar9 = (&DAT_803c4e84)[(char)(&DAT_803c7695)[(char)PTR_DAT_80433930[0x28] * 0x3e4]];
  uStack_54 = (int)(short)(*(short *)(iVar9 + 0x72) -
                          (&DAT_803c7422)[(char)PTR_DAT_80433930[0x28] * 0x1f2]) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,uStack_54
                                                                               ) - DOUBLE_80436bd0))
                      ,afStack_88,0x7a);
  pfVar3 = afStack_88;
  uVar14 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar3,pfVar3);
  iVar7 = *(int *)(param_9 + 0x158);
  zz_00076d0_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,afStack_88,
              (undefined *)pfVar3,puVar5,puVar6,in_r8,in_r9,in_r10);
  iVar2 = zz_0011ce0_(*(int *)(iVar7 + 0x14));
  uVar14 = zz_0009958_(iVar7,iVar2);
  iVar7 = *(int *)(param_9 + 0x15c);
  zz_00076d0_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,afStack_88,
              (undefined *)pfVar3,puVar5,puVar6,in_r8,in_r9,in_r10);
  iVar2 = zz_0011ce0_(*(int *)(iVar7 + 0x14));
  uVar14 = zz_0009958_(iVar7,iVar2);
  iVar2 = 0;
  cVar1 = *(char *)(iVar9 + 0x88);
  uVar8 = 1 << (int)*(char *)(iVar9 + 0x3e4) & 0xff;
  piVar13 = &DAT_803c4e6c;
  piVar12 = (int *)(param_9 + 0x144);
  iVar7 = 0;
  while ((iVar7 < DAT_80436260 && (iVar2 < 5))) {
    iVar10 = *piVar13;
    if (((uVar8 & 1 << (int)*(char *)(iVar10 + 0x3e4)) == 0) && (*(char *)(iVar10 + 0x18) == '\x01')
       ) {
      iVar11 = *piVar12;
      if (*(char *)(iVar10 + 0x88) == cVar1) {
        iVar4 = 0xb;
      }
      else if (*(char *)(iVar10 + 0x88) == '\x02') {
        iVar4 = 0xd;
      }
      else {
        iVar4 = 0xc;
      }
      zz_0006fb4_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,iVar11,
                  iVar4,puVar5,puVar6,in_r8,in_r9,in_r10);
      param_4 = (double)FLOAT_80436c2c;
      puVar6 = (undefined1 *)((char)PTR_DAT_80433930[0x28] * 0x3e4);
      dVar16 = (double)((float)(param_4 *
                               -(double)(*(float *)(iVar10 + 0x20) - *(float *)(iVar9 + 0x20))) /
                       *(float *)(DAT_8043625c + 0x38));
      local_58 = 0x43300000;
      dVar15 = (double)((float)(param_4 *
                               (double)(*(float *)(iVar10 + 0x28) - *(float *)(iVar9 + 0x28))) /
                       *(float *)(DAT_8043625c + 0x40));
      uStack_54 = (int)(short)-(&DAT_803c7422)[(char)PTR_DAT_80433930[0x28] * 0x1f2] ^ 0x80000000;
      in_r8 = DAT_8043625c;
      gnt4_PSMTXRotRad_bl((double)(FLOAT_80436c30 *
                                  (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80436bd0))
                          ,afStack_b8,0x7a);
      gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_b8,afStack_b8);
      param_3 = (double)FLOAT_80436c34;
      gnt4_PSMTXTrans_bl(dVar16,dVar15,param_3,afStack_88);
      gnt4_PSMTXConcat_bl(afStack_b8,afStack_88,afStack_b8);
      local_50 = 0x43300000;
      dVar15 = (double)FLOAT_80436c30;
      puVar5 = (undefined4 *)(&DAT_803c73b0 + (char)PTR_DAT_80433930[0x28] * 0x3e4);
      uStack_4c = (int)(short)(*(short *)(iVar10 + 0x72) -
                              (&DAT_803c7422)[(char)PTR_DAT_80433930[0x28] * 0x1f2]) ^ 0x80000000;
      gnt4_PSMTXRotRad_bl((double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                    uStack_4c) -
                                                                  DOUBLE_80436bd0)),afStack_88,0x7a)
      ;
      pfVar3 = afStack_88;
      uVar14 = gnt4_PSMTXConcat_bl(afStack_b8,pfVar3,pfVar3);
      zz_00076d0_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,iVar11,afStack_88,
                  (undefined *)pfVar3,puVar5,puVar6,in_r8,in_r9,in_r10);
      iVar4 = zz_0011ce0_(*(int *)(iVar11 + 0x14));
      uVar14 = zz_0009958_(iVar11,iVar4);
      piVar12 = piVar12 + 1;
      iVar2 = iVar2 + 1;
      uVar8 = uVar8 | 1 << (int)*(char *)(iVar10 + 0x3e4) & 0xffU;
    }
    piVar13 = piVar13 + 1;
    iVar7 = iVar7 + 1;
  }
  return;
}



// ==== 800139e0  zz_00139e0_ ====

void zz_00139e0_(int param_1)

{
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0x20,1);
  *(undefined1 *)(param_1 + 0x84) = 1;
  return;
}



// ==== 80013a28  zz_0013a28_ ====

/* WARNING: Removing unreachable block (ram,0x80013d64) */
/* WARNING: Removing unreachable block (ram,0x80013d5c) */
/* WARNING: Removing unreachable block (ram,0x80013a40) */
/* WARNING: Removing unreachable block (ram,0x80013a38) */

void zz_0013a28_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined1 uVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  char *pcVar5;
  float *pfVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x172) = 0;
    iVar4 = *(int *)(param_9 + 0x90);
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(iVar4 + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(iVar4 + 0x3e4);
    cVar3 = *(char *)(iVar4 + 0x7cd);
    iVar4 = *(int *)(iVar4 + 0x4ac);
    *(char *)(param_9 + 0x17a) = cVar3;
    dVar13 = DOUBLE_80436bd0;
    if (cVar3 == '\0') {
      uVar1 = *(undefined1 *)(iVar4 + 0x9f);
      local_58 = 0x43300000;
      *(undefined1 *)(param_9 + 0x17c) = uVar1;
      dVar16 = (double)FLOAT_80436c40;
      piVar10 = (int *)(param_9 + 0x144);
      *(undefined1 *)(param_9 + 0x17b) = uVar1;
      dVar12 = (double)FLOAT_80436c44;
      uStack_54 = (int)*(char *)(param_9 + 0x17b) - 1U ^ 0x80000000;
      param_2 = (double)(float)(dVar16 * (double)(float)((double)CONCAT44(0x43300000,uStack_54) -
                                                        dVar13));
      dVar15 = -(double)(float)(param_2 * dVar12 + (double)FLOAT_80436c3c);
      iVar4 = param_9;
      for (uVar7 = 0; (int)uVar7 < (int)*(char *)(param_9 + 0x17b); uVar7 = uVar7 + 1) {
        if ((int)uVar7 < 8) {
          iVar11 = *piVar10;
        }
        else {
          iVar11 = *(int *)(iVar4 + 0xc0);
        }
        pcVar5 = (char *)0x17;
        uVar14 = zz_0006fb4_(dVar12,param_2,dVar13,param_4,param_5,param_6,param_7,param_8,
                             DAT_804361fc,iVar11,0x17,param_12,param_13,param_14,param_15,param_16);
        (&DAT_802c3c3c)[(uVar7 & 1) * 3] = (float)dVar15;
        zz_0007834_(uVar14,param_2,dVar13,param_4,param_5,param_6,param_7,param_8,iVar11,
                    &DAT_802c3c3c + (uVar7 & 1) * 3,pcVar5,param_12,param_13,param_14,param_15,
                    param_16);
        fVar2 = FLOAT_80436c4c;
        if ((uVar7 & 1) != 0) {
          fVar2 = FLOAT_80436c48;
        }
        dVar12 = (double)zz_0007e74_((double)fVar2,param_2,dVar13,param_4,param_5,param_6,param_7,
                                     param_8,iVar11,extraout_r4,pcVar5,param_12,param_13,param_14,
                                     param_15,param_16);
        dVar15 = (double)(float)(dVar15 + dVar16);
        iVar4 = iVar4 + 4;
        piVar10 = piVar10 + 1;
      }
      *(undefined1 *)(param_9 + 0x17c) = 0xff;
      param_3 = dVar13;
    }
    else {
      param_13 = &DAT_802b0988;
      pcVar5 = (char *)0x16;
      local_68 = DAT_802b0988;
      local_64 = DAT_802b098c;
      local_60 = DAT_802b0990;
      param_12 = DAT_802b0988;
      uVar14 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,*(int *)(param_9 + 0x144),0x16,DAT_802b0988,&DAT_802b0988,
                           param_14,param_15,param_16);
      zz_0007834_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0x144),&local_68,pcVar5,param_12,param_13,param_14,param_15,
                  param_16);
    }
  }
  iVar4 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
  pfVar6 = *(float **)(iVar4 + 0x4ac);
  *(undefined1 *)(param_9 + 0x170) = 0;
  dVar13 = DOUBLE_80436bd0;
  if ((*(byte *)(iVar4 + 0x7d5) & 1) == 0) {
    if (*(char *)(iVar4 + 0x7cd) == '\0') {
      if (*(char *)(iVar4 + 0x747) == '\0') {
        *(undefined1 *)(param_9 + 0x17c) = 0xff;
      }
      else {
        *(undefined1 *)(param_9 + 0x170) = 1;
        cVar3 = *(char *)(param_9 + 0x17b) - *(char *)(iVar4 + 0x747);
        iVar4 = (int)cVar3;
        if (iVar4 != *(char *)(param_9 + 0x17c)) {
          *(undefined1 *)(param_9 + 0x17d) = 0x1e;
          *(char *)(param_9 + 0x17c) = cVar3;
        }
        if (*(char *)(param_9 + 0x17d) != '\0') {
          *(char *)(param_9 + 0x17d) = *(char *)(param_9 + 0x17d) + -1;
        }
        piVar10 = (int *)(param_9 + 0x144);
        iVar11 = param_9;
        for (iVar9 = 0; iVar9 < *(char *)(param_9 + 0x17b); iVar9 = iVar9 + 1) {
          if (iVar9 < 8) {
            iVar8 = *piVar10;
          }
          else {
            iVar8 = *(int *)(iVar11 + 0xc0);
          }
          if (iVar4 < iVar9) {
            dVar13 = (double)FLOAT_80436bcc;
          }
          else if (iVar4 == iVar9) {
            local_58 = 0x43300000;
            uStack_54 = (int)*(char *)(param_9 + 0x17d) ^ 0x80000000;
            param_3 = (double)FLOAT_80436bcc;
            dVar13 = (double)(float)(param_3 -
                                    (double)((float)((double)CONCAT44(0x43300000,uStack_54) -
                                                    DOUBLE_80436bd0) / FLOAT_80436c50));
            param_2 = DOUBLE_80436bd0;
          }
          else {
            dVar13 = (double)FLOAT_80436bc4;
          }
          uVar14 = zz_00086b8_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar8,pfVar6,param_12,param_13,param_14,param_15,
                               param_16);
          zz_0007c30_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,
                      extraout_r4_00,pfVar6,param_12,param_13,param_14,param_15,param_16);
          iVar11 = iVar11 + 4;
          piVar10 = piVar10 + 1;
        }
      }
    }
    else {
      uStack_54 = (int)*(short *)(iVar4 + 0x736) ^ 0x80000000;
      local_58 = 0x43300000;
      uStack_4c = (int)*(short *)(pfVar6 + 1) ^ 0x80000000;
      dVar16 = (double)FLOAT_80436bcc;
      dVar15 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80436bd0);
      local_50 = 0x43300000;
      dVar12 = (double)(float)(dVar16 - (double)(float)(dVar15 / (double)(float)((double)CONCAT44(
                                                  0x43300000,uStack_4c) - DOUBLE_80436bd0)));
      if ((double)FLOAT_80436bc4 != dVar12) {
        iVar4 = *(int *)(param_9 + 0x144);
        *(undefined1 *)(param_9 + 0x170) = 1;
        uVar14 = zz_00086b8_(dVar12,dVar15,dVar13,dVar16,param_5,param_6,param_7,param_8,
                             DAT_804361fc,iVar4,pfVar6,param_12,param_13,param_14,param_15,param_16)
        ;
        zz_0007c30_(uVar14,dVar15,dVar13,dVar16,param_5,param_6,param_7,param_8,iVar4,extraout_r4_01
                    ,pfVar6,param_12,param_13,param_14,param_15,param_16);
      }
    }
  }
  return;
}



// ==== 80013d80  zz_0013d80_ ====

void zz_0013d80_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_0013a28_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  uVar1 = zz_0010514_((int)*(char *)(param_9 + 0x96));
  if ((uVar1 == 0) && (*(char *)(param_9 + 0x170) != '\0')) {
    if (*(char *)(param_9 + 0x17a) == '\0') {
      piVar5 = (int *)(param_9 + 0x144);
      iVar6 = param_9;
      for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x17b); iVar3 = iVar3 + 1) {
        if (iVar3 < 8) {
          iVar4 = *piVar5;
        }
        else {
          iVar4 = *(int *)(iVar6 + 0xc0);
        }
        iVar2 = zz_0011ce0_(*(int *)(iVar4 + 0x14));
        zz_0009958_(iVar4,iVar2);
        iVar6 = iVar6 + 4;
        piVar5 = piVar5 + 1;
      }
    }
    else {
      iVar3 = *(int *)(param_9 + 0x144);
      iVar6 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
      zz_0009958_(iVar3,iVar6);
    }
  }
  return;
}



// ==== 80013e54  zz_0013e54_ ====

void zz_0013e54_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  undefined8 uVar5;
  
  *(code **)(param_9 + 0x100) = FUN_80012274;
  zz_0089100_(param_9,0x21,1);
  fVar1 = FLOAT_80436c54;
  *(undefined1 *)(param_9 + 0x84) = 5;
  fVar3 = FLOAT_80436c58;
  *(float *)(param_9 + 100) = fVar1;
  fVar2 = FLOAT_80436bc8;
  dVar4 = (double)FLOAT_80436bc8;
  *(float *)(param_9 + 0x68) = fVar3;
  fVar1 = FLOAT_80436bc4;
  *(float *)(param_9 + 0x6c) = fVar2;
  *(undefined2 *)(param_9 + 0x72) = 0xf8e4;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x7c) = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0x164) = fVar1;
  *(float *)(param_9 + 0x168) = fVar1;
  *(float *)(param_9 + 0x16c) = fVar1;
  *(undefined1 *)(param_9 + 0x170) = 0;
  *(undefined1 *)(param_9 + 0x1a3) = *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x3f0);
  uVar5 = zz_0006fb4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe0),0x18,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe4),0x18,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe8),0x1a,param_12,param_13,param_14,param_15,param_16);
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xec),0x19,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x1a5) = 1;
  *(undefined1 *)(param_9 + 0x1a6) = 0;
  return;
}



// ==== 80013f3c  zz_0013f3c_ ====

void zz_0013f3c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x1a5) = 0;
  (*(code *)(&PTR_zz_0013f80__802c46d0)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 80013f80  zz_0013f80_ ====

void zz_0013f80_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80436c5c;
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(float *)(param_1 + 0x164) = fVar1;
  zz_0013fb4_(param_1);
  return;
}



// ==== 80013fb4  zz_0013fb4_ ====

void zz_0013fb4_(int param_1)

{
  double dVar1;
  float fVar2;
  
  *(undefined1 *)(param_1 + 0x170) = 0;
  *(undefined1 *)(param_1 + 0x1a5) = 1;
  dVar1 = DOUBLE_80436bd0;
  if (*(char *)(*(int *)(param_1 + 0x90) + 0x18) == '\x01') {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    fVar2 = FLOAT_80436c5c;
    *(undefined2 *)(param_1 + 0x1e) = 0x14;
    *(float *)(param_1 + 0x44) =
         -(fVar2 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000)
                          - dVar1));
    *(undefined2 *)(param_1 + 0x178) = 0;
    *(undefined1 *)(param_1 + 0x170) = 1;
    *(undefined1 *)(param_1 + 0x1a4) = 0;
    *(undefined1 *)(param_1 + 0x1a3) = *(undefined1 *)(*(int *)(param_1 + 0x90) + 0x3f0);
  }
  return;
}



// ==== 8001403c  zz_001403c_ ====

void zz_001403c_(int param_1)

{
  float fVar1;
  short sVar2;
  
  if (*(short *)(param_1 + 0x178) != 0) {
    *(short *)(param_1 + 0x178) = *(short *)(param_1 + 0x178) + -1;
    return;
  }
  *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x164) + *(float *)(param_1 + 0x44);
  sVar2 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar2;
  fVar1 = FLOAT_80436bc4;
  if (0 < sVar2) {
    return;
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(float *)(param_1 + 0x164) = fVar1;
  return;
}



// ==== 80014090  FUN_80014090 ====

void FUN_80014090(int param_1)

{
  undefined2 uVar1;
  bool bVar2;
  double dVar3;
  float fVar4;
  int iVar5;
  
  bVar2 = false;
  iVar5 = *(int *)(param_1 + 0x90);
  if (*(char *)(iVar5 + 0x18) < '\x02') {
    if (*(char *)(iVar5 + 0x3f0) != *(char *)(param_1 + 0x1a3)) {
      *(undefined1 *)(param_1 + 0x1a4) = 1;
      bVar2 = true;
      *(undefined2 *)(param_1 + 0x178) = 0;
      *(undefined1 *)(param_1 + 0x1a3) = *(undefined1 *)(iVar5 + 0x3f0);
      uVar1 = *(undefined2 *)(iVar5 + 0x1c6);
      *(undefined2 *)(param_1 + 0x194) = uVar1;
      *(undefined2 *)(param_1 + 0x1a0) = uVar1;
      *(undefined2 *)(param_1 + 0x19c) = uVar1;
    }
  }
  else {
    bVar2 = true;
    *(undefined1 *)(param_1 + 0x1a4) = 0;
    if (*(char *)(iVar5 + 0x4a0) == '\0') {
      *(undefined2 *)(param_1 + 0x178) = 0x1e;
    }
    else {
      *(undefined2 *)(param_1 + 0x178) = 0;
    }
  }
  dVar3 = DOUBLE_80436bd0;
  if (bVar2) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    fVar4 = FLOAT_80436c5c;
    *(undefined2 *)(param_1 + 0x1e) = 0x14;
    *(float *)(param_1 + 0x44) =
         fVar4 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
                        dVar3);
  }
  return;
}



// ==== 80014164  FUN_80014164 ====

void FUN_80014164(int param_1)

{
  if ('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18)) {
    *(undefined1 *)(param_1 + 0x1a4) = 0;
  }
  zz_001403c_(param_1);
  if (*(short *)(param_1 + 0x1e) < 1) {
    *(float *)(param_1 + 0x164) = FLOAT_80436c5c;
    *(undefined1 *)(param_1 + 0x170) = 0;
    *(undefined1 *)(param_1 + 0x1a5) = 1;
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  return;
}



// ==== 800141d8  zz_00141d8_ ====

/* WARNING: Removing unreachable block (ram,0x800147c4) */
/* WARNING: Removing unreachable block (ram,0x800141e8) */

void zz_00141d8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  bool bVar2;
  short sVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int *piVar13;
  double dVar14;
  undefined8 uVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double local_88;
  undefined8 local_80;
  undefined8 local_58;
  undefined8 local_50;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x1a6) = 1;
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  if ((*(char *)(param_9 + 0x1a6) != '\0') && (*(char *)(param_9 + 0x1a5) != '\0')) {
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(*(int *)(param_9 + 0x90) + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x3e4);
    *(undefined1 *)(param_9 + 0x1a6) = 0;
    *(undefined1 *)(param_9 + 0x172) = 1;
  }
  iVar11 = *(int *)(param_9 + 0x90);
  uVar15 = zz_0013f3c_(param_9);
  if ((*(char *)(param_9 + 0x1a4) == '\0') && (*(char *)(param_9 + 0x1a6) < '\x01')) {
    if ((*(short *)(param_9 + 0x194) != *(short *)(iVar11 + 0x1c6)) ||
       (*(char *)(param_9 + 0x172) != '\0')) {
      *(short *)(param_9 + 0x194) = *(short *)(iVar11 + 0x1c6);
      dVar19 = DOUBLE_80436bd0;
      dVar16 = (double)FLOAT_80436c60;
      local_88 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar11 + 0x1c6)) ^ 0x80000000);
      dVar14 = (double)FLOAT_80436c64;
      dVar18 = (double)(float)(local_88 - DOUBLE_80436bd0);
      local_80 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar11 + 0x1c4) ^ 0x80000000);
      dVar17 = (double)(float)(local_80 - DOUBLE_80436bd0);
      dVar20 = (double)(float)(dVar18 / dVar17);
      *(float *)(param_9 + 0x198) = (float)(dVar18 / dVar17);
      iVar4 = (int)(dVar14 * dVar20);
      *(short *)(param_9 + 0x7c) = (short)(0x10000 / ((int)(dVar16 * dVar20) + 8));
      iVar8 = *(int *)(param_9 + 0xe0);
      iVar10 = *(int *)(param_9 + 0xe4);
      if (0x13 < iVar4) {
        iVar4 = 0x13;
      }
      uVar15 = zz_0006fb4_((longlong)(int)(dVar16 * dVar20),dVar17,dVar18,dVar19,param_5,param_6,
                           param_7,param_8,DAT_804361fc,iVar8,0x50 - iVar4,param_12,param_13,
                           param_14,param_15,param_16);
      zz_0006fb4_(uVar15,dVar17,dVar18,dVar19,param_5,param_6,param_7,param_8,DAT_804361fc,iVar10,
                  0x50 - iVar4,param_12,param_13,param_14,param_15,param_16);
      if (*(short *)(iVar11 + 0x1c6) == 0) {
        *(undefined1 *)(iVar8 + 0x10) = 0;
        *(undefined1 *)(iVar10 + 0x10) = 0;
      }
      iVar11 = (int)(FLOAT_80436c68 * (float)((double)FLOAT_80436c78 * dVar20));
      iVar4 = (int)(FLOAT_80436c68 *
                   -(float)((double)FLOAT_80436c6c * dVar20 - (double)FLOAT_80436bcc));
      iVar9 = (int)(FLOAT_80436c68 *
                   (float)((double)FLOAT_80436c74 * dVar20 + (double)FLOAT_80436c70));
      zz_0007cd0_(iVar8,iVar4,iVar9,iVar11);
      zz_0007cd0_(iVar10,iVar4,iVar9,iVar11);
      param_3 = -(double)(float)((double)FLOAT_80436c70 * dVar20 - (double)FLOAT_80436c70);
      param_4 = (double)FLOAT_80436c68;
      dVar19 = param_4 * param_3;
      iVar11 = (int)(param_4 * (double)(float)((double)FLOAT_80436c84 * dVar20));
      iVar4 = (int)(param_4 *
                   (double)(float)((double)FLOAT_80436c80 * dVar20 + (double)FLOAT_80436c7c));
      zz_0007cf4_(iVar8,(int)dVar19,iVar4,iVar11);
      zz_0007cf4_(iVar10,(int)dVar19,iVar4,iVar11);
      param_2 = (double)FLOAT_80436c68;
      iVar8 = *(int *)(param_9 + 0xe8);
      iVar11 = (int)(param_2 * (double)(float)((double)FLOAT_80436bcc - dVar20));
      iVar4 = (int)(param_2 *
                   -(double)(float)((double)FLOAT_80436c88 * dVar20 - (double)FLOAT_80436c88));
      zz_0007cd0_(iVar8,iVar11,iVar4,0);
      param_12 = 0;
      uVar15 = zz_0007cf4_(iVar8,iVar11,iVar4,0);
    }
    sVar3 = *(short *)(param_9 + 0x194);
    if ((*(short *)(param_9 + 0x19c) != sVar3) || (*(char *)(param_9 + 0x172) != '\0')) {
      if (*(char *)(param_9 + 0x172) != '\0') {
        *(short *)(param_9 + 0x1a0) = sVar3;
        *(short *)(param_9 + 0x19c) = sVar3;
      }
      if (*(short *)(param_9 + 0x194) != *(short *)(param_9 + 0x1a0)) {
        *(short *)(param_9 + 0x1a0) = *(short *)(param_9 + 0x194);
        sVar3 = *(short *)(param_9 + 0x19c) - *(short *)(param_9 + 0x194);
        if (sVar3 < 0) {
          sVar3 = -sVar3;
        }
        iVar11 = (int)sVar3;
        if (iVar11 < 0x1f) {
          *(undefined2 *)(param_9 + 0x19e) = 1;
        }
        else {
          iVar11 = iVar11 / 0x1e + (iVar11 >> 0x1f);
          *(short *)(param_9 + 0x19e) = ((short)iVar11 - (short)(iVar11 >> 0x1f)) + 1;
        }
      }
      if (*(short *)(param_9 + 0x194) < *(short *)(param_9 + 0x19c)) {
        sVar3 = *(short *)(param_9 + 0x19c) - *(short *)(param_9 + 0x194);
        if (*(short *)(param_9 + 0x19e) < sVar3) {
          sVar3 = *(short *)(param_9 + 0x19e);
        }
        *(short *)(param_9 + 0x19c) = *(short *)(param_9 + 0x19c) - sVar3;
      }
      if (*(short *)(param_9 + 0x19c) < *(short *)(param_9 + 0x194)) {
        sVar3 = *(short *)(param_9 + 0x194) - *(short *)(param_9 + 0x19c);
        if (*(short *)(param_9 + 0x19e) < sVar3) {
          sVar3 = *(short *)(param_9 + 0x19e);
        }
        *(short *)(param_9 + 0x19c) = *(short *)(param_9 + 0x19c) + sVar3;
      }
      iVar11 = (int)*(short *)(param_9 + 0x19c);
      if (9999 < iVar11) {
        iVar11 = 9999;
        *(undefined2 *)(param_9 + 0x19c) = 9999;
      }
      piVar12 = &DAT_802c3c84;
      piVar13 = (int *)(param_9 + 0x144);
      iVar8 = 0;
      iVar4 = 0;
      uVar7 = 1000;
      do {
        uVar6 = iVar11 / (int)uVar7;
        if (((uVar6 != 0) || (uVar7 == 1)) || (iVar4 != 0)) {
          if (iVar4 == 0) {
            *(short *)(param_9 + 0x196) = 4 - (short)iVar8;
          }
          iVar9 = *piVar13;
          iVar10 = piVar13[4];
          uVar15 = zz_0006fb4_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar9,*piVar12,param_12,param_13,param_14,param_15,
                               param_16);
          pfVar5 = (float *)piVar12[4];
          zz_0006fb4_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      iVar10,(int)pfVar5,param_12,param_13,param_14,param_15,param_16);
          local_50 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
          zz_00086b8_((double)(float)(local_50 - DOUBLE_80436bd0),param_2,param_3,param_4,param_5,
                      param_6,param_7,param_8,DAT_804361fc,iVar9,pfVar5,param_12,param_13,param_14,
                      param_15,param_16);
          local_58 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
          uVar15 = zz_00086b8_((double)(float)(local_58 - DOUBLE_80436bd0),param_2,param_3,param_4,
                               param_5,param_6,param_7,param_8,DAT_804361fc,iVar10,pfVar5,param_12,
                               param_13,param_14,param_15,param_16);
          uVar15 = zz_0007c30_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar9,
                               extraout_r4,pfVar5,param_12,param_13,param_14,param_15,param_16);
          uVar15 = zz_0007c30_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar10
                               ,extraout_r4_00,pfVar5,param_12,param_13,param_14,param_15,param_16);
          piVar13 = piVar13 + 1;
          piVar12 = piVar12 + 1;
          iVar4 = iVar4 + 1;
          iVar11 = iVar11 - (iVar11 / (int)uVar7) * uVar7;
        }
        iVar8 = iVar8 + 1;
        uVar7 = uVar7 / 10;
      } while (iVar8 < 4);
    }
    fVar1 = FLOAT_80436c8c;
    bVar2 = false;
    *(short *)(param_9 + 0x70) = *(short *)(param_9 + 0x70) + *(short *)(param_9 + 0x7c);
    *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
    if (*(float *)(param_9 + 0x198) <= fVar1) {
      bVar2 = true;
      if ((*(ushort *)(param_9 + 0x1c) & 8) == 0) {
        *(undefined1 *)(param_9 + 0x1a2) = 1;
      }
      else {
        *(undefined1 *)(param_9 + 0x1a2) = 0;
      }
    }
    else {
      *(undefined1 *)(param_9 + 0x1a2) = 0;
    }
    fVar1 = FLOAT_80436bc4;
    if (bVar2) {
      local_50 = (double)(CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x1a2)) ^ 0x80000001);
      fVar1 = (float)(local_50 - DOUBLE_80436bd0);
    }
    dVar19 = (double)fVar1;
    iVar11 = *(int *)(param_9 + 0xec);
    dVar14 = (double)(float)((double)FLOAT_80436c14 * dVar19 + (double)FLOAT_80436c10);
    zz_0007cd0_(iVar11,(int)(DOUBLE_80436c00 * dVar19) & 0xff,
                (int)(DOUBLE_80436c00 * DOUBLE_80436c08 * dVar19) & 0xff,0);
    zz_0007cac_(dVar14,iVar11);
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  return;
}



// ==== 800147e0  zz_00147e0_ ====

void zz_00147e0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  float afStack_88 [12];
  float afStack_58 [12];
  undefined4 local_28;
  uint uStack_24;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_00141d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    dVar7 = (double)FLOAT_80436bc4;
    iVar5 = *(int *)(param_9 + 0xec);
    dVar10 = (double)FLOAT_80436c90;
    gnt4_PSMTXTrans_bl(dVar7,dVar7,dVar10,afStack_58);
    pfVar4 = afStack_58;
    uVar8 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar4,pfVar4);
    zz_00076d0_(uVar8,dVar7,dVar10,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_58,
                (undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
    iVar3 = zz_0011ce0_(*(int *)(iVar5 + 0x14));
    zz_0009958_(iVar5,iVar3);
    gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_58);
    dVar9 = (double)FLOAT_80436bcc;
    if (dVar9 != (double)*(float *)(param_9 + 0x198)) {
      local_28 = 0x43300000;
      uStack_24 = (int)*(short *)(param_9 + 0x70) ^ 0x80000000;
      dVar7 = (double)FLOAT_80436c30;
      gnt4_PSMTXRotRad_bl((double)(float)(dVar7 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                   uStack_24) -
                                                                 DOUBLE_80436bd0)),afStack_58,0x78);
      pfVar4 = afStack_58;
      dVar9 = (double)gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar4,pfVar4);
    }
    zz_00076d0_(dVar9,dVar7,dVar10,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
                afStack_58,(undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
    iVar3 = zz_0011ce0_(*(int *)(*(int *)(param_9 + 0xe0) + 0x14));
    zz_0009958_(*(int *)(param_9 + 0xe0),iVar3);
    gnt4_PSMTXRotRad_bl((double)FLOAT_80436c94,afStack_88,0x78);
    pfVar4 = afStack_58;
    uVar8 = gnt4_PSMTXConcat_bl(pfVar4,afStack_88,pfVar4);
    zz_00076d0_(uVar8,dVar7,dVar10,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
                afStack_58,(undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
    iVar3 = zz_0011ce0_(*(int *)(*(int *)(param_9 + 0xe4) + 0x14));
    uVar8 = zz_0009958_(*(int *)(param_9 + 0xe4),iVar3);
    zz_00076d0_(uVar8,dVar7,dVar10,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe8),
                (float *)(param_9 + 0x114),(undefined *)pfVar4,param_12,param_13,param_14,param_15,
                param_16);
    iVar3 = zz_0011ce0_(*(int *)(*(int *)(param_9 + 0xe8) + 0x14));
    zz_0009958_(*(int *)(param_9 + 0xe8),iVar3);
    cVar1 = *(char *)(param_9 + 0x1a2);
    iVar5 = (int)*(short *)(param_9 + 0x196);
    for (iVar3 = iVar5; 0 < iVar3; iVar3 = iVar3 + -1) {
      iVar2 = iVar5 - iVar3;
      iVar6 = *(int *)(param_9 + ((((-(int)cVar1 | (int)cVar1) >> 0x1f & 4U) + iVar5) - iVar3) * 4 +
                      0x144);
      dVar7 = (double)(float)(&PTR_DAT_802c3c58)[iVar2 * 3];
      dVar9 = (double)(float)(&DAT_802c3c5c)[iVar2 * 3];
      gnt4_PSMTXTrans_bl((double)(float)(&DAT_802c3c54)[iVar2 * 3],dVar7,dVar9,afStack_58);
      pfVar4 = afStack_58;
      uVar8 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar4,pfVar4);
      zz_00076d0_(uVar8,dVar7,dVar9,param_4,param_5,param_6,param_7,param_8,iVar6,afStack_58,
                  (undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
      iVar2 = zz_0011ce0_(*(int *)(iVar6 + 0x14));
      zz_0009958_(iVar6,iVar2);
    }
  }
  return;
}



// ==== 800149f8  zz_00149f8_ ====

void zz_00149f8_(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(code **)(param_1 + 0x100) = FUN_80012274;
  zz_0089100_(param_1,0x21,1);
  *(undefined1 *)(param_1 + 0x84) = 9;
  fVar1 = FLOAT_80436bc4;
  *(undefined2 *)(param_1 + 0x17a) = 0xffff;
  *(undefined2 *)(param_1 + 0x1c) = 0;
  *(float *)(param_1 + 0x164) = fVar1;
  *(float *)(param_1 + 0x168) = fVar1;
  *(float *)(param_1 + 0x16c) = fVar1;
  fVar2 = FLOAT_80436ca8;
  fVar1 = FLOAT_80436c9c;
  if (*(char *)(param_1 + 0x12) == '\0') {
    *(float *)(param_1 + 100) = FLOAT_80436c98;
    fVar2 = FLOAT_80436ca0;
    *(float *)(param_1 + 0x68) = fVar1;
    *(float *)(param_1 + 0x6c) = fVar2;
  }
  else {
    *(float *)(param_1 + 100) = FLOAT_80436ca4;
    fVar1 = FLOAT_80436ca0;
    *(float *)(param_1 + 0x68) = fVar2;
    *(float *)(param_1 + 0x6c) = fVar1;
  }
  *(undefined2 *)(param_1 + 0x74) = 0xf000;
  *(undefined1 *)(param_1 + 0x18b) = *(undefined1 *)(*(int *)(param_1 + 0x90) + 0x3f0);
  *(undefined1 *)(param_1 + 400) = 1;
  *(undefined1 *)(param_1 + 0x191) = 0;
  return;
}



// ==== 80014ac4  zz_0014ac4_ ====

void zz_0014ac4_(int param_1)

{
  *(undefined1 *)(param_1 + 400) = 0;
  (*(code *)(&PTR_FUN_802c46e4)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 80014b08  FUN_80014b08 ====

void FUN_80014b08(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80436cac;
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(float *)(param_1 + 0x164) = fVar1;
  zz_0014b3c_(param_1);
  return;
}



// ==== 80014b3c  zz_0014b3c_ ====

void zz_0014b3c_(int param_1)

{
  double dVar1;
  float fVar2;
  
  *(undefined1 *)(param_1 + 0x170) = 0;
  *(undefined1 *)(param_1 + 400) = 1;
  dVar1 = DOUBLE_80436bd0;
  if (*(char *)(*(int *)(param_1 + 0x90) + 0x18) == '\x01') {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    fVar2 = FLOAT_80436cac;
    *(undefined2 *)(param_1 + 0x1e) = 0x14;
    *(float *)(param_1 + 0x44) =
         -(fVar2 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000)
                          - dVar1));
    *(undefined2 *)(param_1 + 0x178) = 0;
    *(undefined1 *)(param_1 + 0x170) = 1;
    *(undefined1 *)(param_1 + 0x18c) = 0;
    *(undefined1 *)(param_1 + 0x18b) = *(undefined1 *)(*(int *)(param_1 + 0x90) + 0x3f0);
  }
  return;
}



// ==== 80014bc4  zz_0014bc4_ ====

void zz_0014bc4_(int param_1)

{
  float fVar1;
  short sVar2;
  
  if (*(short *)(param_1 + 0x178) != 0) {
    *(short *)(param_1 + 0x178) = *(short *)(param_1 + 0x178) + -1;
    return;
  }
  *(undefined1 *)(param_1 + 0x170) = 1;
  *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x164) + *(float *)(param_1 + 0x44);
  sVar2 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar2;
  fVar1 = FLOAT_80436bc4;
  if (0 < sVar2) {
    return;
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(float *)(param_1 + 0x164) = fVar1;
  return;
}



// ==== 80014c20  FUN_80014c20 ====

void FUN_80014c20(int param_1)

{
  bool bVar1;
  double dVar2;
  float fVar3;
  int iVar4;
  
  bVar1 = false;
  iVar4 = *(int *)(param_1 + 0x90);
  if (*(char *)(iVar4 + 0x18) < '\x02') {
    if (*(char *)(iVar4 + 0x3f0) != *(char *)(param_1 + 0x18b)) {
      *(undefined1 *)(param_1 + 0x18c) = 1;
      bVar1 = true;
      *(undefined2 *)(param_1 + 0x178) = 0;
      *(undefined1 *)(param_1 + 0x18b) = *(undefined1 *)(iVar4 + 0x3f0);
    }
  }
  else {
    bVar1 = true;
    *(undefined1 *)(param_1 + 0x18c) = 0;
    if (*(char *)(iVar4 + 0x4a0) == '\0') {
      *(undefined2 *)(param_1 + 0x178) = 0x1e;
    }
    else {
      *(undefined2 *)(param_1 + 0x178) = 0;
    }
  }
  dVar2 = DOUBLE_80436bd0;
  if (bVar1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    fVar3 = FLOAT_80436cac;
    *(undefined2 *)(param_1 + 0x1e) = 0x14;
    *(float *)(param_1 + 0x44) =
         fVar3 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
                        dVar2);
  }
  return;
}



// ==== 80014ce4  FUN_80014ce4 ====

void FUN_80014ce4(int param_1)

{
  zz_0014bc4_(param_1);
  if (*(short *)(param_1 + 0x1e) < 1) {
    *(float *)(param_1 + 0x164) = FLOAT_80436cac;
    *(undefined1 *)(param_1 + 0x170) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 400) = 1;
  }
  return;
}



// ==== 80014d38  zz_0014d38_ ====

void zz_0014d38_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                int param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar2;
  short *psVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  if (*(short *)(param_11 + 2) == 0) {
    *(undefined2 *)(param_9 + 0x17a) = 0xffff;
  }
  else {
    iVar1 = (int)*param_12;
    if (*(short *)(param_9 + 0x17a) != iVar1) {
      local_58 = DAT_802b0994;
      local_54 = DAT_802b0998;
      local_50 = DAT_802b099c;
      if (999 < iVar1) {
        iVar1 = 999;
      }
      *(short *)(param_9 + 0x17a) = (short)iVar1;
      iVar8 = 0;
      iVar7 = 0;
      uVar9 = 100;
      psVar3 = param_12;
      do {
        uVar4 = iVar1 / (int)uVar9;
        if (((uVar4 != 0) || (uVar9 == 1)) || (iVar7 != 0)) {
          if (iVar7 == 0) {
            *(short *)(param_9 + 0x17c) = 3 - (short)iVar8;
          }
          pfVar2 = (float *)0x13;
          iVar6 = param_9 + (2 - iVar8) * 4;
          iVar5 = *(int *)(iVar6 + 0xe0);
          uVar10 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar5,0x13,psVar3,param_13,param_14,param_15,param_16);
          zz_0007ae4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,&local_58
                      ,(char *)pfVar2,psVar3,param_13,param_14,param_15,param_16);
          uStack_44 = uVar4 ^ 0x80000000;
          local_48 = 0x43300000;
          uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_44) -
                                              DOUBLE_80436bd0),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar2,psVar3,param_13,
                               param_14,param_15,param_16);
          uVar10 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                               extraout_r4,pfVar2,psVar3,param_13,param_14,param_15,param_16);
          iVar5 = *(int *)(iVar6 + 0xec);
          pfVar2 = (float *)0x15;
          uVar10 = zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar5,0x15,psVar3,param_13,param_14,param_15,param_16);
          zz_0007ae4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,&local_58
                      ,(char *)pfVar2,psVar3,param_13,param_14,param_15,param_16);
          uStack_3c = uVar4 ^ 0x80000000;
          local_40 = 0x43300000;
          uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_3c) -
                                              DOUBLE_80436bd0),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar2,psVar3,param_13,
                               param_14,param_15,param_16);
          param_1 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5
                                ,extraout_r4_00,pfVar2,psVar3,param_13,param_14,param_15,param_16);
          iVar7 = iVar7 + 1;
          iVar1 = iVar1 - (iVar1 / (int)uVar9) * uVar9;
        }
        iVar8 = iVar8 + 1;
        uVar9 = uVar9 / 10;
      } while (iVar8 < 3);
      if (*(char *)(param_9 + 0x172) == '\0') {
        if (*(short *)(param_11 + 4) == 1) {
          if (*param_12 < param_12[1]) {
            *(undefined2 *)(param_9 + 0x17e) = 10;
          }
        }
        else if (*param_12 < *(short *)(param_11 + 2)) {
          *(undefined2 *)(param_9 + 0x17e) = 10;
        }
      }
      else {
        *(undefined2 *)(param_9 + 0x17e) = 0;
        *(undefined2 *)(param_9 + 0x182) = 0;
      }
      pfVar2 = (float *)0x43300000;
      uStack_3c = (int)*(short *)(param_9 + 0x17a) ^ 0x80000000;
      iVar1 = *(int *)(param_9 + 0x154);
      uStack_44 = (int)*(short *)(param_11 + 2) ^ 0x80000000;
      local_40 = 0x43300000;
      dVar12 = (double)FLOAT_80436bcc;
      local_48 = 0x43300000;
      dVar11 = DOUBLE_80436bd0;
      uVar10 = zz_00086b8_((double)(float)(dVar12 - (double)((float)((double)CONCAT44(0x43300000,
                                                                                      uStack_3c) -
                                                                    DOUBLE_80436bd0) /
                                                            (float)((double)CONCAT44(0x43300000,
                                                                                     uStack_44) -
                                                                   DOUBLE_80436bd0))),
                           DOUBLE_80436bd0,dVar12,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar1,0x43300000,psVar3,param_13,param_14,param_15,param_16)
      ;
      zz_0007c30_(uVar10,dVar11,dVar12,param_4,param_5,param_6,param_7,param_8,iVar1,extraout_r4_01,
                  pfVar2,psVar3,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80014f90  zz_0014f90_ ====

void zz_0014f90_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  float local_28;
  float local_24;
  float local_20;
  undefined4 auStack_1c [3];
  
  iVar5 = *(int *)(param_9 + 0x15c);
  iVar6 = *(char *)(param_9 + 399) * 4;
  iVar3 = param_10 + iVar6;
  pfVar2 = (float *)(*(int *)(param_10 + 0x4ac) + iVar6);
  uVar8 = zz_00086b8_((double)(*(float *)(iVar3 + 0x648) / pfVar2[0x61]),param_2,param_3,param_4,
                      param_5,param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar2,iVar3,param_13,
                      param_14,param_15,param_16);
  zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,extraout_r4,pfVar2
              ,iVar3,param_13,param_14,param_15,param_16);
  iVar6 = *(int *)(param_9 + 0x150);
  pfVar4 = (float *)0x0;
  if (*(int *)(iVar6 + 0x14) == 100) {
    dVar7 = (double)FLOAT_80436bc4;
    *(undefined1 *)(iVar6 + 0x10) = 0;
    dVar9 = (double)*(float *)(param_10 + *(char *)(param_9 + 399) * 4 + 0x648);
    if (dVar9 != dVar7) {
      pfVar4 = (float *)0x63;
    }
  }
  else {
    dVar9 = (double)FLOAT_80436bc4;
    if (dVar9 == (double)*(float *)(param_10 + *(char *)(param_9 + 399) * 4 + 0x648)) {
      pfVar4 = (float *)0x64;
    }
  }
  if (pfVar4 != (float *)0x0) {
    uVar8 = zz_0007908_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                        auStack_1c,pfVar2,iVar3,param_13,param_14,param_15,param_16);
    pfVar2 = pfVar4;
    uVar8 = zz_0006fb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                        iVar6,(int)pfVar4,iVar3,param_13,param_14,param_15,param_16);
    zz_0007834_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,auStack_1c,
                (char *)pfVar2,iVar3,param_13,param_14,param_15,param_16);
    if (pfVar4 == (float *)0x64) {
      *(undefined1 *)(iVar6 + 0x10) = 0;
    }
  }
  iVar5 = *(int *)(param_9 + 0x160);
  iVar6 = *(char *)(param_9 + 399) * 4;
  if (*(float *)(param_10 + iVar6 + 0x648) == *(float *)(*(int *)(param_10 + 0x4ac) + iVar6 + 0x184)
     ) {
    *(undefined1 *)(iVar5 + 0x10) = 1;
    if (*(char *)(param_9 + 0x18e) == '\0') {
      *(undefined2 *)(param_9 + 0x186) = 0;
      *(undefined2 *)(param_9 + 0x188) = 0;
    }
    else {
      *(short *)(param_9 + 0x186) = *(short *)(param_9 + 0x186) + 0x444;
      *(short *)(param_9 + 0x188) = *(short *)(param_9 + 0x188) + 1;
    }
    *(undefined1 *)(param_9 + 0x18e) = 1;
    fVar1 = FLOAT_80436cb0;
    if ((*(ushort *)(param_9 + 0x188) & 4) != 0) {
      fVar1 = FLOAT_80436bcc;
    }
    uVar8 = zz_00086b8_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        DAT_804361fc,iVar5,pfVar2,iVar3,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,extraout_r4_00,
                pfVar2,iVar3,param_13,param_14,param_15,param_16);
    local_20 = FLOAT_80436bcc;
    dVar9 = zz_0045238_(*(short *)(param_9 + 0x186));
    local_28 = (float)((double)FLOAT_80436c44 * dVar9 + (double)FLOAT_80436cb4);
    local_24 = local_28;
    zz_0007ae4_(dVar9,(double)FLOAT_80436c44,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                &local_28,(char *)pfVar2,iVar3,param_13,param_14,param_15,param_16);
  }
  else {
    *(undefined1 *)(iVar5 + 0x10) = 0;
    *(undefined1 *)(param_9 + 0x18e) = 0;
  }
  return;
}



// ==== 80015194  FUN_80015194 ====

/* WARNING: Removing unreachable block (ram,0x80015580) */
/* WARNING: Removing unreachable block (ram,0x800151a4) */

int FUN_80015194(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  short sVar2;
  float fVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  float *pfVar4;
  char *pcVar5;
  short *psVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  undefined4 auStack_58 [2];
  float local_50;
  undefined8 local_48;
  undefined4 local_40;
  uint uStack_3c;
  double local_38;
  
  sVar2 = *(short *)(param_11 + 1);
  iVar9 = 0;
  if (sVar2 == 1) {
    dVar11 = (double)*(float *)(param_12 + 2);
    if ((double)FLOAT_80436bc4 < dVar11) {
      iVar8 = *(int *)(param_9 + 0x154);
      pfVar4 = (float *)((int)*(short *)((int)param_11 + 2) * (int)*(short *)((int)param_11 + 6));
      local_48 = (double)(CONCAT44(0x43300000,pfVar4) ^ 0x80000000);
      dVar12 = (double)(float)(dVar11 / (double)(float)(local_48 - DOUBLE_80436bd0));
      psVar6 = param_12;
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar8,pfVar4,param_12,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_01
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      iVar8 = *(int *)(param_9 + 0x158);
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar8,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_02
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      if (*param_12 == 0) {
        *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
        if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
          *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
        }
        iVar9 = 1;
      }
    }
  }
  else if (sVar2 < 1) {
    if (((-1 < sVar2) && (*param_12 == 0)) && (*(short *)(param_9 + 0x17e) == 0)) {
      iVar9 = *(int *)(param_9 + 0x154);
      local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)((int)param_11 + 6)) ^ 0x80000000);
      dVar11 = (double)*(float *)(param_12 + 2);
      dVar12 = (double)(float)(dVar11 / (double)(float)(local_48 - DOUBLE_80436bd0));
      pfVar4 = param_11;
      psVar6 = param_12;
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar9,param_11,param_12,param_13,param_14,param_15,param_16)
      ;
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar9,extraout_r4,
                  pfVar4,psVar6,param_13,param_14,param_15,param_16);
      iVar9 = *(int *)(param_9 + 0x158);
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar9,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar9,extraout_r4_00
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
      if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
        *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
      }
      iVar9 = 1;
    }
  }
  else if (sVar2 < 4) {
    pfVar4 = (float *)0x43300000;
    iVar8 = *(int *)(param_9 + 0x154);
    uStack_3c = (int)*(short *)((int)param_11 + 2) ^ 0x80000000;
    local_48 = (double)CONCAT44(0x43300000,(int)*param_12 ^ 0x80000000);
    param_3 = (double)FLOAT_80436bcc;
    local_40 = 0x43300000;
    dVar12 = (double)(float)(param_3 -
                            (double)((float)(local_48 - DOUBLE_80436bd0) /
                                    (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80436bd0
                                           )));
    psVar6 = param_12;
    dVar11 = DOUBLE_80436bd0;
    uVar10 = zz_00086b8_(dVar12,DOUBLE_80436bd0,param_3,param_4,param_5,param_6,param_7,param_8,
                         DAT_804361fc,iVar8,0x43300000,param_12,param_13,param_14,param_15,param_16)
    ;
    zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_03,
                pfVar4,psVar6,param_13,param_14,param_15,param_16);
    iVar8 = *(int *)(param_9 + 0x158);
    uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                         iVar8,pfVar4,psVar6,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_04,
                pfVar4,psVar6,param_13,param_14,param_15,param_16);
    if (*param_12 == 0) {
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
      if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
        *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
      }
      iVar9 = 1;
    }
  }
  fVar3 = FLOAT_80436bc4;
  if (iVar9 != 0) {
    local_40 = 0x43300000;
    uStack_3c = (int)*(char *)(param_9 + 0x180) ^ 0x80000001;
    fVar3 = (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80436bd0);
  }
  dVar12 = (double)fVar3;
  uVar7 = 0;
  iVar8 = *(int *)(param_9 + 0x144);
  local_48 = (double)(longlong)(int)(DOUBLE_80436c00 * dVar12);
  uVar1 = (uint)(DOUBLE_80436c00 * DOUBLE_80436c08 * dVar12);
  local_38 = (double)(longlong)(int)uVar1;
  pcVar5 = (char *)(uVar1 & 0xff);
  dVar11 = DOUBLE_80436c00;
  zz_0007cd0_(iVar8,(int)(DOUBLE_80436c00 * dVar12) & 0xff,pcVar5,0);
  dVar12 = (double)zz_0007cac_((double)(float)((double)FLOAT_80436cbc * dVar12 +
                                              (double)FLOAT_80436cb8),iVar8);
  *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 0;
  if (*(char *)(param_9 + 0x180) == '\0') {
    *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 1;
  }
  else {
    *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 1;
  }
  if (*(short *)(param_9 + 0x17e) == 0) {
    dVar12 = (double)*(float *)(param_12 + 2);
    if (dVar12 <= (double)FLOAT_80436bc4) {
      if (*(short *)(param_9 + 0x182) != 0) {
        *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
      }
    }
    else if ((*(short *)(param_11 + 1) != 2) && (*(short *)(param_11 + 1) != 3)) {
      *(undefined2 *)(param_9 + 0x184) = 0xf000;
      *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
    }
  }
  else {
    *(short *)(param_9 + 0x17e) = *(short *)(param_9 + 0x17e) + -1;
    *(undefined2 *)(param_9 + 0x184) = 0x1000;
    *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
  }
  zz_0007a60_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x14c),auStack_58,pcVar5,uVar7,param_13,param_14,param_15,param_16)
  ;
  local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x182)) ^ 0x80000000);
  local_50 = (float)((double)FLOAT_80436c30 * (double)(float)(local_38 - DOUBLE_80436bd0));
  zz_0007988_(DOUBLE_80436bd0,(double)FLOAT_80436c30,param_3,param_4,param_5,param_6,param_7,param_8
              ,*(int *)(param_9 + 0x14c),auStack_58,pcVar5,uVar7,param_13,param_14,param_15,param_16
             );
  return iVar9;
}



// ==== 8001559c  zz_001559c_ ====

void zz_001559c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_0014d38_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,(int)param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = zz_0014f90_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x180) = 0;
  FUN_80015194(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8001561c  zz_001561c_ ====

void zz_001561c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_0014d38_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,(int)param_11,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x180) = 0;
  FUN_80015194(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80015688  zz_0015688_ ====

void zz_0015688_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0014f90_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800156a8  zz_00156a8_ ====

void zz_00156a8_(void)

{
  return;
}



// ==== 800156ac  zz_00156ac_ ====

void zz_00156ac_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0014f90_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800156cc  zz_00156cc_ ====

void zz_00156cc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  float *pfVar5;
  int iVar6;
  short *psVar7;
  int in_r7;
  int in_r8;
  int in_r9;
  undefined4 in_r10;
  int *piVar8;
  undefined8 uVar9;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x191) = 1;
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  if ((*(char *)(param_9 + 0x191) == '\0') || (*(char *)(param_9 + 400) == '\0')) goto LAB_80015948;
  in_r8 = *(int *)(param_9 + 0x90);
  in_r9 = 0;
  iVar6 = (int)*(short *)(in_r8 + 1000);
  iVar2 = 3;
  *(short *)(param_9 + 0x94) = *(short *)(in_r8 + 1000);
  *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(in_r8 + 0x3e4);
  *(undefined2 *)(param_9 + 0x17a) = 0xffff;
  *(undefined1 *)(param_9 + 0x18e) = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined1 *)(param_9 + 399) = 0xff;
  *(undefined1 *)(param_9 + 0x18a) = 0;
  in_r7 = in_r8;
  do {
    if (*(short *)(in_r7 + 0x78e) != 0) {
      cVar1 = *(char *)(param_9 + 0x18a);
      if (*(char *)(param_9 + 0x12) == cVar1) {
        *(char *)(param_9 + 0x13) = cVar1;
        *(char *)(param_9 + 399) = (char)in_r9;
        break;
      }
      *(char *)(param_9 + 0x18a) = cVar1 + '\x01';
    }
    in_r7 = in_r7 + 8;
    in_r9 = in_r9 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  piVar8 = (int *)(param_9 + 0x144);
  *(char *)(param_9 + 399) = *(char *)(param_9 + 0x12) << 1;
  *(undefined1 *)(param_9 + 0x18d) = *(undefined1 *)(in_r8 + *(char *)(param_9 + 0x12) + 0x8d0);
  *(undefined1 *)(*(int *)(param_9 + 0x144) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x148) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x14c) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x150) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x15c) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x160) + 0x10) = 0;
  cVar1 = *(char *)(param_9 + 0x18d);
  if (cVar1 == '\x03') {
    *(undefined2 *)(param_9 + 0x17c) = 0xffff;
    piVar3 = &DAT_802c3e04;
  }
  else if (cVar1 < '\x03') {
    if (cVar1 == '\x01') {
      piVar3 = &DAT_802c40c4;
      *(undefined2 *)(param_9 + 0x17c) = 0xffff;
    }
    else if (cVar1 < '\x01') {
LAB_800158b8:
      piVar3 = (int *)0x0;
    }
    else {
      *(undefined2 *)(param_9 + 0x17c) = 0;
      piVar3 = &DAT_802c3f64;
    }
  }
  else if (cVar1 == '\x05') {
    *(undefined2 *)(param_9 + 0x17c) = 0;
    piVar3 = &DAT_802c3ca4;
  }
  else {
    if ('\x04' < cVar1) goto LAB_800158b8;
    *(undefined2 *)(param_9 + 0x17c) = 0xffff;
    piVar3 = &DAT_802c4224;
  }
  if (piVar3 != (int *)0x0) {
    iVar2 = 0;
    do {
      pcVar4 = (char *)*piVar3;
      if (-1 < (int)pcVar4) {
        if (iVar2 == 2) {
          pcVar4 = pcVar4 + *(char *)(param_9 + 0x12);
          uVar9 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              DAT_804361fc,*piVar8,(int)pcVar4,iVar6,in_r7,in_r8,in_r9,in_r10);
        }
        else {
          uVar9 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              DAT_804361fc,*piVar8,(int)pcVar4,iVar6,in_r7,in_r8,in_r9,in_r10);
        }
        uVar9 = zz_0007834_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar8,
                            piVar3 + 1,pcVar4,iVar6,in_r7,in_r8,in_r9,in_r10);
        uVar9 = zz_0007ae4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar8,
                            piVar3 + 4,pcVar4,iVar6,in_r7,in_r8,in_r9,in_r10);
        param_1 = zz_0007988_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar8,
                              piVar3 + 7,pcVar4,iVar6,in_r7,in_r8,in_r9,in_r10);
      }
      iVar2 = iVar2 + 1;
      piVar8 = piVar8 + 1;
      piVar3 = piVar3 + 0xb;
    } while (iVar2 < 8);
  }
  *(undefined1 *)(param_9 + 0x191) = 0;
LAB_80015948:
  *(undefined1 *)(param_9 + 0x172) = 0;
  uVar9 = zz_0014ac4_(param_9);
  cVar1 = *(char *)(param_9 + 0x18d);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_9 + 0x170) = 0;
  }
  else if (*(char *)(param_9 + 0x191) < '\x01') {
    iVar6 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
    iVar2 = iVar6 + *(char *)(param_9 + 399) * 8;
    pfVar5 = (float *)(iVar2 + 0x78c);
    psVar7 = (short *)(iVar2 + 0x774);
    if (cVar1 == '\x05') {
      zz_001559c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar6,pfVar5
                  ,psVar7,in_r7,in_r8,in_r9,in_r10);
    }
    else if (cVar1 == '\x03') {
      zz_0015688_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar6,pfVar5
                  ,psVar7,in_r7,in_r8,in_r9,in_r10);
    }
    else if (cVar1 == '\x02') {
      zz_001561c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar6,pfVar5
                  ,psVar7,in_r7,in_r8,in_r9,in_r10);
    }
    else if (cVar1 == '\x01') {
      zz_00156a8_();
    }
    else if (cVar1 == '\x04') {
      zz_00156ac_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar6,pfVar5
                  ,psVar7,in_r7,in_r8,in_r9,in_r10);
    }
  }
  return;
}



// ==== 80015a30  zz_0015a30_ ====

void zz_0015a30_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int *piVar6;
  undefined8 uVar7;
  undefined4 auStack_a8 [2];
  float local_a0;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float afStack_80 [12];
  float afStack_50 [15];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    param_1 = zz_00156cc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    iVar4 = 0;
    piVar6 = (int *)(param_9 + 0x144);
    do {
      iVar3 = *piVar6;
      if ((iVar3 != 0) && (*(int *)(iVar3 + 0xc) != 0)) {
        uVar7 = zz_0007bb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                            &local_98,param_11,param_12,param_13,param_14,param_15,param_16);
        uVar7 = zz_0007a60_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                            auStack_a8,param_11,param_12,param_13,param_14,param_15,param_16);
        zz_0007908_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,&local_8c,
                    param_11,param_12,param_13,param_14,param_15,param_16);
        gnt4_PSMTXScale_bl((double)local_98,(double)local_94,(double)local_90,afStack_50);
        gnt4_PSMTXRotRad_bl((double)local_a0,afStack_80,0x7a);
        gnt4_PSMTXConcat_bl(afStack_50,afStack_80,afStack_50);
        param_2 = (double)local_88;
        param_3 = (double)local_84;
        zz_020b4ac_((double)local_8c,param_2,param_3,afStack_50,afStack_50);
        param_11 = afStack_50;
        uVar7 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),param_11,param_11);
        zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_50,
                    (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
        iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
        param_1 = zz_0009958_(iVar3,iVar1);
      }
      iVar4 = iVar4 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar4 < 8);
    pfVar5 = (float *)&DAT_802c4384;
    iVar3 = 0;
    iVar4 = param_9;
    while( true ) {
      if (*(short *)(param_9 + 0x17c) <= iVar3) break;
      if (*(char *)(param_9 + 0x180) == '\0') {
        iVar1 = *(int *)(iVar4 + 0xe0);
      }
      else {
        iVar1 = *(int *)(iVar4 + 0xec);
      }
      zz_0007bb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,&local_98,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      gnt4_PSMTXScale_bl((double)local_98,(double)local_94,(double)local_90,afStack_50);
      param_2 = (double)pfVar5[1];
      param_3 = (double)pfVar5[2];
      zz_020b4ac_((double)*pfVar5,param_2,param_3,afStack_50,afStack_50);
      param_11 = afStack_50;
      uVar7 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),param_11,param_11);
      zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,afStack_50,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      iVar2 = zz_0011ce0_(*(int *)(iVar1 + 0x14));
      param_1 = zz_0009958_(iVar1,iVar2);
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + 3;
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



// ==== 80015bf0  zz_0015bf0_ ====

void zz_0015bf0_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  *(undefined1 *)(param_9 + 0x84) = 1;
  fVar3 = FLOAT_80436cc0;
  fVar1 = FLOAT_80436bc4;
  iVar6 = 0;
  dVar8 = (double)FLOAT_80436bc4;
  dVar7 = (double)FLOAT_80436cc0;
  piVar5 = (int *)(param_9 + 0x144);
  *(float *)(param_9 + 0x68) = FLOAT_80436bc4;
  fVar2 = FLOAT_80436bcc;
  iVar4 = 0;
  *(float *)(param_9 + 100) = fVar1;
  *(float *)(param_9 + 0x6c) = fVar3;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x7c) = 0x1000;
  *(float *)(param_9 + 0x17c) = fVar2;
  do {
    dVar7 = (double)zz_0006fb4_(dVar7,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,
                                DAT_804361fc,*piVar5,
                                (int)*(short *)(&DAT_802c43a8 +
                                               iVar6 + *(char *)(param_9 + 0x12) * 8),param_12,
                                param_13,param_14,param_15,param_16);
    iVar4 = iVar4 + 1;
    piVar5 = piVar5 + 1;
    iVar6 = iVar6 + 2;
  } while (iVar4 < 4);
  return;
}



// ==== 80015ca8  zz_0015ca8_ ====

void zz_0015ca8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0015cc8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80015cc8  zz_0015cc8_ ====

void zz_0015cc8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  uint uVar2;
  float *pfVar3;
  byte bVar4;
  int iVar5;
  double dVar6;
  undefined8 uVar7;
  
  iVar5 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
  uVar2 = 1 << (int)*(char *)(param_9 + 0x12);
  if (((int)*(char *)(iVar5 + 0x58d) & uVar2) == 0) {
    if (((int)*(char *)(iVar5 + 0x58c) & uVar2) == 0) {
      pfVar3 = (float *)0xffffffff;
    }
    else {
      pfVar3 = (float *)0x1;
    }
  }
  else {
    pfVar3 = (float *)0x0;
  }
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined1 *)(param_9 + 400) = 0x80;
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  bVar1 = *(byte *)(param_9 + 400);
  uVar2 = (uint)bVar1;
  bVar4 = (byte)pfVar3;
  if (bVar1 != bVar4) {
    uVar2 = 0;
    if (bVar1 == 0) {
      if (*(short *)(param_9 + 0x1c) < 1) {
        uVar2 = 1;
      }
    }
    else if (bVar1 == 1) {
      if (bVar4 == 0) {
        uVar2 = 1;
      }
      else if (*(short *)(param_9 + 0x1c) < 1) {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 1;
    }
    if ((char)uVar2 != '\0') {
      *(undefined2 *)(param_9 + 0x1c) = 0x1e;
      *(byte *)(param_9 + 400) = bVar4;
      if (bVar4 == 1) {
        param_1 = zz_0008744_((double)FLOAT_80436bc4,param_2,param_3,param_4,param_5,param_6,param_7
                              ,param_8,DAT_804361fc,*(int *)(param_9 + 0x148),pfVar3,param_12,
                              param_13,param_14,param_15,param_16);
        uVar2 = 6;
        pfVar3 = (float *)(int)*(char *)(param_9 + 0x12);
        zz_00ea2ec_(iVar5,6,(int)pfVar3);
      }
    }
  }
  dVar6 = DOUBLE_80436bd0;
  if (*(char *)(param_9 + 400) == '\0') {
    *(short *)(param_9 + 0x70) = *(short *)(param_9 + 0x70) + *(short *)(param_9 + 0x7c);
    dVar6 = gnt4_sin_bl((double)(FLOAT_80436c30 *
                                (float)((double)CONCAT44(0x43300000,
                                                         (int)*(short *)(param_9 + 0x70) ^
                                                         0x80000000) - dVar6)));
    *(float *)(param_9 + 0x17c) = (float)(DOUBLE_80436cd0 * (double)(float)dVar6 + DOUBLE_80436cc8);
  }
  else if (*(char *)(param_9 + 400) == '\x01') {
    uVar7 = zz_0007c30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x148),uVar2,pfVar3,param_12,param_13,param_14,param_15,
                        param_16);
    uVar7 = zz_0007bb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x148),(undefined4 *)(param_9 + 0x184),pfVar3,param_12,
                        param_13,param_14,param_15,param_16);
    dVar6 = zz_0008590_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x148),0,pfVar3,param_12,param_13,param_14,param_15,
                        param_16);
    *(float *)(param_9 + 0x180) = (float)dVar6;
  }
  if (*(short *)(param_9 + 0x1c) != 0) {
    *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -1;
  }
  if ('\x04' < (char)PTR_DAT_80433934[0x45]) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 80015ef0  FUN_80015ef0 ====

/* WARNING: Removing unreachable block (ram,0x80016294) */
/* WARNING: Removing unreachable block (ram,0x8001628c) */
/* WARNING: Removing unreachable block (ram,0x80015f08) */
/* WARNING: Removing unreachable block (ram,0x80015f00) */

void FUN_80015ef0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  float *pfVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  float local_d8;
  float local_d4;
  float local_d0;
  float afStack_cc [12];
  float afStack_9c [13];
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_0015ca8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if ((-1 < *(char *)(param_9 + 400)) &&
     (uVar1 = zz_0010514_((int)*(char *)(param_9 + 0x96)), uVar1 == 0)) {
    if (*(char *)(param_9 + 400) == '\0') {
      iVar10 = 0;
      uVar4 = 0x802c0000;
      dVar14 = (double)FLOAT_80436c30;
      iVar9 = 0;
      iVar7 = 0;
      iVar11 = param_9 + 0x144;
      iVar5 = 0;
      dVar13 = DOUBLE_80436bd0;
      do {
        iVar6 = *(int *)(iVar11 + 8);
        pfVar3 = &local_d8;
        uVar12 = gnt4_PSMTXMultVec_bl
                           ((float *)(param_9 + 0x114),
                            (float *)(*(char *)(param_9 + 0x12) * 0x18 + -0x7fd3bbd8 + iVar10),
                            pfVar3);
        zz_0007834_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,&local_d8,
                    (char *)pfVar3,uVar4,param_13,param_14,param_15,param_16);
        local_68 = 0x43300000;
        uStack_64 = (int)*(short *)(&DAT_802c44f8 + *(char *)(param_9 + 0x12) * 4 + iVar9) ^
                    0x80000000;
        zz_0007e74_((double)(float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,uStack_64)
                                                            - dVar13)),param_2,param_3,param_4,
                    param_5,param_6,param_7,param_8,iVar6,
                    &DAT_802c44f8 + *(char *)(param_9 + 0x12) * 4,(char *)pfVar3,uVar4,param_13,
                    param_14,param_15,param_16);
        local_60 = 0x43300000;
        uStack_5c = (int)*(short *)(&DAT_802c44e8 + *(char *)(param_9 + 0x12) * 4 + iVar9) ^
                    0x80000000;
        uVar12 = FUN_80007db0((double)(float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                        uStack_5c) -
                                                                      dVar13)),param_2,param_3,
                              param_4,param_5,param_6,param_7,param_8,iVar6,
                              &DAT_802c44e8 + *(char *)(param_9 + 0x12) * 4,(char *)pfVar3,uVar4,
                              param_13,param_14,param_15,param_16);
        local_d8 = *(float *)(param_9 + 0x17c);
        local_d0 = *(float *)(&DAT_802c44b8 + *(char *)(param_9 + 0x12) * 8 + iVar7);
        local_d4 = local_d8;
        zz_0007ae4_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,&local_d8,
                    &DAT_802c44b8 + *(char *)(param_9 + 0x12) * 8,uVar4,param_13,param_14,param_15,
                    param_16);
        iVar2 = zz_0011ce0_(*(int *)(iVar6 + 0x14));
        zz_0009958_(iVar6,iVar2);
        iVar5 = iVar5 + 1;
        iVar10 = iVar10 + 0xc;
        iVar9 = iVar9 + 2;
        iVar7 = iVar7 + 4;
        iVar11 = iVar11 + 4;
      } while (iVar5 < 2);
    }
    else {
      iVar10 = 0;
      piVar8 = (int *)(param_9 + 0x144);
      iVar5 = 0;
      iVar7 = 0;
      iVar9 = 0;
      do {
        if ((iVar10 != 0) || (FLOAT_80436cd8 <= *(float *)(param_9 + 0x180))) {
          iVar11 = *piVar8;
          pfVar3 = (float *)((int)u_________________802c43aa +
                            iVar5 + *(char *)(param_9 + 0x12) * 0x18 + 0x1e);
          gnt4_PSMTXTrans_bl((double)*pfVar3,(double)pfVar3[1],(double)pfVar3[2],afStack_9c);
          gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_9c,afStack_9c);
          local_60 = 0x43300000;
          uStack_5c = (int)*(short *)(&DAT_802c44f8 + iVar7 + *(char *)(param_9 + 0x12) * 4) ^
                      0x80000000;
          gnt4_PSMTXRotRad_bl((double)(FLOAT_80436c30 *
                                      (float)((double)CONCAT44(0x43300000,uStack_5c) -
                                             DOUBLE_80436bd0)),afStack_cc,0x7a);
          gnt4_PSMTXConcat_bl(afStack_9c,afStack_cc,afStack_9c);
          local_68 = 0x43300000;
          uStack_64 = (int)*(short *)(&DAT_802c44d8 + iVar7 + *(char *)(param_9 + 0x12) * 4) ^
                      0x80000000;
          gnt4_PSMTXRotRad_bl((double)(FLOAT_80436c30 *
                                      (float)((double)CONCAT44(0x43300000,uStack_64) -
                                             DOUBLE_80436bd0)),afStack_cc,0x79);
          gnt4_PSMTXConcat_bl(afStack_9c,afStack_cc,afStack_9c);
          if (iVar10 == 0) {
            iVar2 = *(char *)(param_9 + 0x12) * 0xc;
            local_d0 = FLOAT_80436bcc;
            local_d8 = *(float *)(&DAT_802c4488 + iVar2);
            local_d4 = *(float *)(&DAT_802c448c + iVar2);
          }
          else {
            local_d8 = *(float *)(param_9 + 0x184);
            local_d4 = *(float *)(param_9 + 0x188);
            local_d0 = *(float *)(param_9 + 0x18c);
          }
          dVar13 = (double)local_d4;
          local_d0 = local_d0 * *(float *)(&DAT_802c44b8 + iVar9 + *(char *)(param_9 + 0x12) * 8);
          dVar14 = (double)local_d0;
          gnt4_PSMTXScale_bl((double)local_d8,dVar13,dVar14,afStack_cc);
          pfVar3 = afStack_9c;
          uVar12 = gnt4_PSMTXConcat_bl(pfVar3,afStack_cc,pfVar3);
          zz_00076d0_(uVar12,dVar13,dVar14,param_4,param_5,param_6,param_7,param_8,iVar11,afStack_9c
                      ,(undefined *)pfVar3,param_12,param_13,param_14,param_15,param_16);
          iVar2 = zz_0011ce0_(*(int *)(iVar11 + 0x14));
          zz_0009958_(iVar11,iVar2);
        }
        iVar10 = iVar10 + 1;
        iVar5 = iVar5 + 0xc;
        iVar7 = iVar7 + 2;
        iVar9 = iVar9 + 4;
        piVar8 = piVar8 + 1;
      } while (iVar10 < 2);
    }
  }
  return;
}



// ==== 800162b0  zz_00162b0_ ====

void zz_00162b0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar4;
  
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar2 = *(char *)(param_9 + 0x12) * 0x18;
  iVar3 = iVar2;
  uVar4 = zz_0089100_(param_9,0x20,1);
  *(undefined1 *)(param_9 + 0x84) = 0x11;
  zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0x144),*(int *)(&DAT_802c4508 + iVar2),iVar3,in_r7,in_r8,in_r9,
              in_r10);
  uVar1 = *(undefined4 *)(&DAT_802c4518 + iVar2);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802c4514 + iVar2);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802c451c + iVar2);
  *(short *)(param_9 + 0x1c) = (short)*(undefined4 *)(&DAT_802c450c + iVar2);
  *(short *)(param_9 + 0x1e) = (short)*(undefined4 *)(&DAT_802c4510 + iVar2);
  *(undefined **)(param_9 + 0x54) = &DAT_802c4568;
  *(undefined1 *)(param_9 + 0x82) = 0;
  return;
}



// ==== 80016364  zz_0016364_ ====

void zz_0016364_(int param_1)

{
  zz_0016384_(param_1);
  return;
}



// ==== 80016384  zz_0016384_ ====

void zz_0016384_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  short sVar5;
  uint *puVar6;
  
  sVar5 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar5;
  if (sVar5 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    cVar1 = *(char *)(param_1 + 0x19);
    if (cVar1 != '\x01') {
      if ('\0' < cVar1) {
        return;
      }
      if (cVar1 < '\0') {
        return;
      }
      sVar5 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar5;
      if (0 < sVar5) {
        return;
      }
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0;
      *(undefined1 *)(param_1 + 0x82) = 0x11;
    }
    puVar6 = *(uint **)(param_1 + 0x54);
    if ((int)puVar6[2] < (int)*(short *)(param_1 + 0x1c)) {
      puVar6 = puVar6 + 2;
      *(uint **)(param_1 + 0x54) = puVar6;
    }
    fVar3 = FLOAT_80436bcc;
    uVar4 = *puVar6;
    if ((int)uVar4 < 0) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
    else if (uVar4 == (int)*(short *)(param_1 + 0x1c)) {
      uVar4 = puVar6[1];
      *(uint *)(param_1 + 0x5c) = uVar4;
      *(uint *)(param_1 + 0x58) = uVar4;
      *(float *)(param_1 + 0x60) = fVar3;
    }
    else {
      fVar2 = (((float)puVar6[3] - (float)puVar6[1]) /
              ((float)((double)CONCAT44(0x43300000,puVar6[2] ^ 0x80000000) - DOUBLE_80436bd0) -
              (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - DOUBLE_80436bd0))) *
              (float)((double)CONCAT44(0x43300000,
                                       (int)*(short *)(param_1 + 0x1c) - uVar4 ^ 0x80000000) -
                     DOUBLE_80436bd0) + (float)puVar6[1];
      *(float *)(param_1 + 0x5c) = fVar2;
      *(float *)(param_1 + 0x58) = fVar2;
      *(float *)(param_1 + 0x60) = fVar3;
    }
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  }
  return;
}



// ==== 800164e0  zz_00164e0_ ====

void zz_00164e0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0x144);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar2 + 0x14));
  zz_0009958_(iVar2,iVar1);
  return;
}



// ==== 80016528  zz_0016528_ ====

void zz_0016528_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  float *pfVar3;
  double dVar4;
  undefined8 uVar5;
  
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  fVar1 = FLOAT_80436cdc;
  *(undefined1 *)(param_9 + 0x84) = 1;
  fVar2 = FLOAT_80436ce0;
  dVar4 = (double)FLOAT_80436ce0;
  *(float *)(param_9 + 100) = fVar1;
  fVar1 = FLOAT_80436ca0;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar1;
  uVar5 = zz_0006fb4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x144),0x39,param_12,param_13,param_14,param_15,param_16);
  pfVar3 = (float *)0x3a;
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0x148),0x3a,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_00086b8_((double)FLOAT_80436bc4,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,DAT_804361fc,*(int *)(param_9 + 0x148),pfVar3,param_12,param_13,param_14,
                      param_15,param_16);
  zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x148),extraout_r4,pfVar3,param_12,param_13,param_14,param_15,
              param_16);
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  return;
}



// ==== 800165cc  zz_00165cc_ ====

void zz_00165cc_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_00165ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800165ec  zz_00165ec_ ====

void zz_00165ec_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined2 uVar1;
  float fVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  
  fVar2 = FLOAT_80436bc4;
  if (*(char *)(param_9 + 0x172) == '\0') {
    *(undefined2 *)(param_9 + 0x17a) =
         *(undefined2 *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x182) * 0x3c + 0x126);
  }
  else {
    iVar3 = *(int *)(param_9 + 0x90);
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(iVar3 + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(iVar3 + 0x3e4);
    *(undefined1 *)(param_9 + 0x182) = *(undefined1 *)(iVar3 + 0x88);
    uVar1 = *(undefined2 *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x182) * 0x3c + 0x126);
    *(undefined2 *)(param_9 + 0x180) = uVar1;
    *(undefined2 *)(param_9 + 0x17c) = uVar1;
    *(undefined2 *)(param_9 + 0x17a) = uVar1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x74) = 0;
    *(float *)(param_9 + 0x44) = fVar2;
  }
  if (*(short *)(param_9 + 0x17a) != *(short *)(param_9 + 0x17c)) {
    *(short *)(param_9 + 0x17c) = *(short *)(param_9 + 0x17a);
    *(undefined2 *)(param_9 + 0x1c) = 0x1e;
    if ((int)*(short *)(param_9 + 0x17c) ==
        (uint)*(ushort *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x182) * 0x3c + 0x124)) {
      if (*(char *)(param_9 + 0x183) == '\0') {
        *(undefined1 *)(param_9 + 0x183) = 1;
        zz_00f0468_(0,0x78,0);
      }
    }
    if ((*(char *)(param_9 + 0x183) != '\0') &&
       ((int)*(short *)(param_9 + 0x17c) !=
        (uint)*(ushort *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x182) * 0x3c + 0x124))) {
      *(undefined1 *)(param_9 + 0x183) = 0;
    }
    param_11 = (float *)((int)*(short *)(param_9 + 0x17c) ^ 0x80000000);
    param_3 = (double)(float)((double)CONCAT44(0x43300000,param_11) - DOUBLE_80436bd0);
    dVar5 = DOUBLE_80436cf0;
    uVar4 = zz_00086b8_((double)(FLOAT_80436c64 *
                                (float)(param_3 /
                                       (double)(float)((double)CONCAT44(0x43300000,
                                                                        (uint)*(ushort *)
                                                                               (PTR_DAT_80433934 +
                                                                               *(char *)(param_9 +
                                                                                        0x182) *
                                                                               0x3c + 0x124)) -
                                                      DOUBLE_80436cf0))),DOUBLE_80436cf0,param_3,
                        param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                        *(int *)(param_9 + 0x148),param_11,param_12,param_13,param_14,param_15,
                        param_16);
    zz_0007c30_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x148),extraout_r4,param_11,param_12,param_13,param_14,param_15,
                param_16);
  }
  if (*(short *)(param_9 + 0x1c) != 0) {
    *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + 0x800;
  }
  if ((int)*(short *)(param_9 + 0x17a) ==
      (uint)*(ushort *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x182) * 0x3c + 0x124)) {
    dVar5 = (double)FLOAT_80436c88;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    fVar2 = FLOAT_80436ce4;
    *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + -0x800;
    dVar6 = (double)*(float *)(param_9 + 0x44);
    *(float *)(param_9 + 0x44) = (float)(dVar6 + dVar5);
    if (fVar2 <= (float)(dVar6 + dVar5)) {
      *(float *)(param_9 + 0x44) = FLOAT_80436bc4;
    }
    uVar4 = zz_00086b8_((double)(FLOAT_80436ce8 + *(float *)(param_9 + 0x44)),dVar6,param_3,param_4,
                        param_5,param_6,param_7,param_8,DAT_804361fc,*(int *)(param_9 + 0x148),
                        param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar4,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x148),extraout_r4_00,param_11,param_12,param_13,param_14,
                param_15,param_16);
  }
  *(undefined1 *)(param_9 + 0x172) = 0;
  return;
}



// ==== 80016844  zz_0016844_ ====

void zz_0016844_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_00165cc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_9 + 0x74) ^ 0x80000000;
  dVar5 = (double)FLOAT_80436c30;
  iVar3 = *(int *)(param_9 + 0x144);
  gnt4_PSMTXRotRad_bl((double)(float)(dVar5 * (double)(float)((double)CONCAT44(0x43300000,uStack_14)
                                                             - DOUBLE_80436bd0)),afStack_48,0x7a);
  pfVar2 = afStack_48;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_48,
              (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  dVar5 = (double)FLOAT_80436bc4;
  iVar3 = *(int *)(param_9 + 0x148);
  dVar6 = (double)FLOAT_80436c44;
  gnt4_PSMTXTrans_bl(dVar5,dVar5,dVar6,afStack_48);
  pfVar2 = afStack_48;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar4,dVar5,dVar6,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_48,
              (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  return;
}



// ==== 80016934  zz_0016934_ ====

void zz_0016934_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int *piVar4;
  short *psVar5;
  double dVar6;
  
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  *(undefined1 *)(param_9 + 0x84) = 1;
  fVar1 = FLOAT_80436cfc;
  psVar5 = &DAT_802c4598;
  piVar4 = (int *)(param_9 + 0x144);
  dVar6 = (double)FLOAT_80436cfc;
  iVar3 = 0;
  *(float *)(param_9 + 100) = FLOAT_80436cf8;
  fVar2 = FLOAT_80436d00;
  *(float *)(param_9 + 0x68) = fVar1;
  *(float *)(param_9 + 0x6c) = fVar2;
  do {
    dVar6 = (double)zz_0006fb4_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                DAT_804361fc,*piVar4,(int)*psVar5,param_12,param_13,param_14,
                                param_15,param_16);
    iVar3 = iVar3 + 1;
    piVar4 = piVar4 + 1;
    psVar5 = psVar5 + 1;
  } while (iVar3 < 8);
  zz_0006fb4_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xe0),0x56,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800169f0  FUN_800169f0 ====

/* WARNING: Removing unreachable block (ram,0x80016c54) */
/* WARNING: Removing unreachable block (ram,0x80016a00) */

void FUN_800169f0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r4;
  short sVar4;
  float *pfVar5;
  int iVar6;
  uint in_r7;
  int iVar7;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  short sVar9;
  int iVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  undefined8 uVar14;
  double dVar15;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(*(int *)(param_9 + 0x90) + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x3e4);
    *(undefined2 *)(param_9 + 0x17a) = 0;
    *(undefined1 *)(param_9 + 0x182) = 0;
    *(undefined1 *)(param_9 + 0x186) = 0;
    *(undefined2 *)(param_9 + 0x17c) = 0;
    *(undefined1 *)(param_9 + 0x183) = 0;
    *(undefined1 *)(param_9 + 0x187) = 0;
    *(undefined2 *)(param_9 + 0x17e) = 0;
    *(undefined1 *)(param_9 + 0x184) = 0;
    *(undefined1 *)(param_9 + 0x188) = 0;
    *(undefined2 *)(param_9 + 0x180) = 0;
    *(undefined1 *)(param_9 + 0x185) = 0;
    *(undefined1 *)(param_9 + 0x189) = 0;
    *(undefined1 *)(param_9 + 0x18a) = 0;
  }
  pfVar11 = (float *)(param_9 + 0x144);
  iVar6 = *(int *)(param_9 + 0x90);
  iVar7 = 0;
  iVar13 = 2;
  pfVar5 = pfVar11;
  do {
    iVar3 = param_9 + iVar7;
    if (*(char *)(iVar3 + 0x186) != '\0') {
      *(char *)(iVar3 + 0x186) = *(char *)(iVar3 + 0x186) + -1;
    }
    sVar4 = *(short *)(iVar6 + 0x4f4);
    if (sVar4 != *(short *)((int)pfVar5 + 0x36)) {
      *(short *)((int)pfVar5 + 0x36) = sVar4;
      if (sVar4 == 0) {
        *(byte *)(param_9 + 0x18a) = *(byte *)(param_9 + 0x18a) & ~(byte)(1 << iVar7);
      }
      else {
        in_r7 = 1 << iVar7;
        if (((*(byte *)(param_9 + 0x18a) & in_r7) == 0) || (*(char *)(iVar3 + 0x186) == '\0')) {
          *(undefined1 *)(iVar3 + 0x186) = 8;
        }
        *(byte *)(param_9 + 0x18a) = *(byte *)(param_9 + 0x18a) | (byte)in_r7;
      }
    }
    pfVar5 = (float *)((int)pfVar5 + 2);
    iVar6 = iVar6 + 2;
    iVar7 = iVar7 + 1;
    iVar13 = iVar13 + -1;
  } while (iVar13 != 0);
  iVar13 = 0;
  *(undefined1 *)(param_9 + 0x170) = 0;
  if (*(char *)(param_9 + 0x18a) != '\0') {
    iVar3 = 0;
    *(undefined1 *)(param_9 + 0x170) = 1;
    do {
      if (((uint)*(byte *)(param_9 + 0x18a) & 1 << iVar3) != 0) {
        sVar4 = *(short *)((int)pfVar11 + 0x36);
        if (1000 < sVar4) {
          sVar4 = 999;
          *(undefined2 *)((int)pfVar11 + 0x36) = 999;
        }
        iVar12 = param_9 + iVar3;
        iVar10 = 0;
        *(undefined1 *)(iVar12 + 0x182) = 0;
        iVar8 = iVar13 << 2;
        sVar9 = 100;
        dVar15 = DOUBLE_80436bd0;
        do {
          uVar2 = (int)sVar4 / (int)sVar9;
          if (((uVar2 != 0) && (*(char *)(iVar12 + 0x182) == '\0')) ||
             ((*(char *)(iVar12 + 0x182) == '\0' && (sVar9 == 1)))) {
            *(char *)(iVar12 + 0x182) = '\x03' - (char)iVar10;
          }
          if (9 < (int)uVar2) {
            uVar2 = 9;
          }
          uVar14 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) -
                                              dVar15),param_2,param_3,param_4,param_5,param_6,
                               param_7,param_8,DAT_804361fc,*(int *)(param_9 + iVar8 + 0x148),pfVar5
                               ,iVar6,in_r7,iVar7,in_r9,in_r10);
          zz_0007c30_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + iVar8 + 0x148),extraout_r4,pfVar5,iVar6,in_r7,iVar7,in_r9,
                      in_r10);
          pfVar5 = (float *)(int)sVar4;
          iVar10 = iVar10 + 1;
          iVar8 = iVar8 + 4;
          sVar1 = (sVar4 / sVar9) * sVar9;
          sVar9 = (short)((uint)(int)sVar9 / 10);
          sVar4 = sVar4 - sVar1;
        } while (iVar10 < 3);
      }
      iVar3 = iVar3 + 1;
      iVar13 = iVar13 + 4;
      pfVar11 = (float *)((int)pfVar11 + 2);
    } while (iVar3 < 2);
  }
  *(undefined1 *)(param_9 + 0x172) = 0;
  return;
}



// ==== 80016c70  FUN_80016c70 ====

/* WARNING: Removing unreachable block (ram,0x80016ebc) */
/* WARNING: Removing unreachable block (ram,0x80016eb4) */
/* WARNING: Removing unreachable block (ram,0x80016c88) */
/* WARNING: Removing unreachable block (ram,0x80016c80) */

void FUN_80016c70(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  float fVar2;
  int iVar3;
  char *pcVar4;
  char **ppcVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined *puVar9;
  int iVar10;
  undefined4 *puVar11;
  int *piVar12;
  undefined4 *puVar13;
  double dVar14;
  undefined8 uVar15;
  double dVar16;
  double dVar17;
  char *local_68;
  float local_64;
  float local_60;
  undefined4 local_58;
  uint uStack_54;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    FUN_800169f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    puVar11 = &DAT_802c45a8;
    piVar12 = (int *)(param_9 + 0x144);
    puVar9 = &DAT_802c46f8;
    uVar7 = 0;
    iVar10 = 1;
    do {
      if (((uint)*(byte *)(param_9 + 0x18a) & 1 << uVar7) != 0) {
        uStack_54 = uVar7 ^ 0x80000000;
        iVar6 = *piVar12;
        local_58 = 0x43300000;
        pcVar4 = *(char **)(param_9 + 0x20);
        dVar14 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80436bd0);
        local_64 = (float)((double)FLOAT_80436d04 * dVar14 + (double)*(float *)(param_9 + 0x24));
        local_60 = *(float *)(param_9 + 0x28);
        local_68 = pcVar4;
        zz_0007834_(dVar14,(double)FLOAT_80436d04,param_3,param_4,param_5,param_6,param_7,param_8,
                    iVar6,&local_68,pcVar4,param_12,param_13,param_14,param_15,param_16);
        iVar3 = zz_0011ce0_(*(int *)(iVar6 + 0x14));
        zz_0009958_(iVar6,iVar3);
        if ((uVar7 == 1) && (*(char *)(param_9 + 0x183) != '\0')) {
          iVar6 = *(int *)(param_9 + 0xe0);
          uStack_54 = (int)*(char *)(param_9 + 0x183) - 1U ^ 0x80000000;
          local_58 = 0x43300000;
          dVar14 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80436bd0);
          dVar16 = (double)(float)local_68;
          local_68 = (char *)(float)(dVar16 + (double)(float)((double)FLOAT_80436d0c * dVar14 +
                                                             (double)FLOAT_80436d08));
          zz_0007834_(dVar14,dVar16,(double)FLOAT_80436d0c,param_4,param_5,param_6,param_7,param_8,
                      iVar6,&local_68,pcVar4,param_12,param_13,param_14,param_15,param_16);
          iVar3 = zz_0011ce0_(*(int *)(iVar6 + 0x14));
          zz_0009958_(iVar6,iVar3);
        }
        uStack_54 = uVar7 ^ 0x80000000;
        local_58 = 0x43300000;
        param_3 = (double)FLOAT_80436d14;
        dVar17 = (double)FLOAT_80436d18;
        dVar16 = (double)(float)(param_3 * (double)(float)((double)CONCAT44(0x43300000,uStack_54) -
                                                          DOUBLE_80436bd0) + (double)FLOAT_80436d10)
        ;
        puVar13 = puVar11;
        dVar14 = DOUBLE_80436bd0;
        for (uVar8 = 0; (int)uVar8 < (int)*(char *)(param_9 + uVar7 + 0x182); uVar8 = uVar8 + 1) {
          local_68 = (char *)*puVar13;
          iVar3 = *(int *)(param_9 + ((2 - uVar8) + iVar10) * 4 + 0x144);
          local_64 = (float)dVar16;
          local_60 = (float)dVar17;
          bVar1 = *(byte *)(param_9 + uVar7 + 0x186);
          if (bVar1 != 0) {
            fVar2 = *(float *)(puVar9 + (bVar1 & 3) * 4);
            if ((uVar8 & 1) != 0) {
              fVar2 = fVar2 * FLOAT_80436d1c;
            }
            local_64 = local_64 + fVar2;
          }
          ppcVar5 = &local_68;
          uVar15 = gnt4_PSMTXMultVec_bl
                             ((float *)(param_9 + 0x114),(float *)ppcVar5,(float *)ppcVar5);
          zz_0007834_(uVar15,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,&local_68,
                      (char *)ppcVar5,param_12,param_13,param_14,param_15,param_16);
          iVar6 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
          zz_0009958_(iVar3,iVar6);
          puVar13 = puVar13 + 1;
        }
      }
      uVar7 = uVar7 + 1;
      puVar11 = puVar11 + 3;
      iVar10 = iVar10 + 4;
      puVar9 = puVar9 + 0x10;
      piVar12 = piVar12 + 4;
    } while ((int)uVar7 < 2);
  }
  return;
}



// ==== 80016ed8  zz_0016ed8_ ====

void zz_0016ed8_(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0x20,1);
  fVar1 = FLOAT_80436d20;
  *(undefined1 *)(param_1 + 0x84) = 1;
  fVar2 = FLOAT_80436d24;
  *(float *)(param_1 + 100) = fVar1;
  fVar1 = FLOAT_80436bc8;
  *(float *)(param_1 + 0x68) = fVar2;
  *(float *)(param_1 + 0x6c) = fVar1;
  return;
}



// ==== 80016f38  zz_0016f38_ ====

void zz_0016f38_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  zz_0016f58_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80016f58  zz_0016f58_ ====

void zz_0016f58_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 in_r7;
  undefined *puVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x3e4);
    *(undefined1 *)(param_9 + 0x17a) = 0xff;
  }
  puVar5 = PTR_DAT_80433934;
  *(undefined1 *)(param_9 + 0x170) = 0;
  if (0 < *(short *)(puVar5 + *(char *)(param_9 + 0x96) * 8 + 0x159c)) {
    *(undefined1 *)(param_9 + 0x170) = 1;
    if (*(char *)(param_9 + 0x17a) != PTR_DAT_80433934[*(char *)(param_9 + 0x96) + 0x15ce]) {
      *(undefined *)(param_9 + 0x17a) = PTR_DAT_80433934[*(char *)(param_9 + 0x96) + 0x15ce];
      iVar1 = DAT_803bb334;
      iVar6 = (int)*(short *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x96) * 8 + 0x159e);
      iVar2 = *(char *)(param_9 + 0x17a) + iVar6 + -1;
      *(undefined1 *)(*(int *)(param_9 + 0x144) + 0x10) = 0;
      iVar2 = iVar2 - (iVar2 / iVar6) * iVar6;
      iVar7 = iVar6;
      if (0 < iVar6) {
        do {
          pcVar3 = PTR_DAT_80433934 + *(char *)(param_9 + 0x96) * 0x348 + iVar2 * 0x1c + 0x1e8;
          if (pcVar3[0x17] == '\0') {
            param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  iVar1,*(int *)(param_9 + 0x144),
                                  *(int *)((&PTR_DAT_80350d0c)[*pcVar3] + (uint)(byte)pcVar3[1] * 4)
                                  ,iVar2,in_r7,in_r8,in_r9,in_r10);
            break;
          }
          iVar2 = iVar2 + iVar6 + -1;
          iVar2 = iVar2 - (iVar2 / iVar6) * iVar6;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      pcVar3 = PTR_DAT_80433934 +
               *(char *)(param_9 + 0x96) * 0x348 + *(char *)(param_9 + 0x17a) * 0x1c + 0x1e8;
      puVar5 = PTR_DAT_80433934;
      uVar8 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                          *(int *)(param_9 + 0x148),
                          *(int *)((&PTR_DAT_80350d0c)[*pcVar3] + (uint)(byte)pcVar3[1] * 4),
                          *pcVar3 * 4,PTR_DAT_80433934,pcVar3,in_r9,in_r10);
      *(undefined1 *)(*(int *)(param_9 + 0x14c) + 0x10) = 0;
      iVar2 = *(char *)(param_9 + 0x17a) + iVar6 + 1;
      iVar2 = iVar2 - (iVar2 / iVar6) * iVar6;
      iVar7 = iVar6;
      if (0 < iVar6) {
        do {
          pcVar4 = PTR_DAT_80433934 + *(char *)(param_9 + 0x96) * 0x348 + iVar2 * 0x1c + 0x1e8;
          if (pcVar4[0x17] == '\0') {
            zz_0006fb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                        *(int *)(param_9 + 0x14c),
                        *(int *)((&PTR_DAT_80350d0c)[*pcVar4] + (uint)(byte)pcVar4[1] * 4),iVar2,
                        puVar5,pcVar3,in_r9,in_r10);
            break;
          }
          iVar2 = iVar2 + iVar6 + 1;
          iVar2 = iVar2 - (iVar2 / iVar6) * iVar6;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
    }
  }
  *(undefined1 *)(param_9 + 0x172) = 0;
  return;
}



// ==== 800171e8  zz_00171e8_ ====

void zz_00171e8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  int *piVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  float afStack_78 [12];
  float afStack_48 [12];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_0016f38_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    pfVar5 = (float *)&DAT_802c4718;
    piVar6 = (int *)(param_9 + 0x144);
    pfVar4 = (float *)&DAT_802c473c;
    iVar2 = 0;
    do {
      iVar3 = *piVar6;
      if (*(char *)(iVar3 + 0x10) != '\0') {
        gnt4_PSMTXTrans_bl((double)*pfVar5,(double)pfVar5[1],(double)pfVar5[2],afStack_48);
        gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_48,afStack_48);
        dVar8 = (double)pfVar4[1];
        dVar9 = (double)pfVar4[2];
        gnt4_PSMTXScale_bl((double)*pfVar4,dVar8,dVar9,afStack_78);
        pfVar1 = afStack_48;
        uVar7 = gnt4_PSMTXConcat_bl(afStack_78,pfVar1,pfVar1);
        zz_00076d0_(uVar7,dVar8,dVar9,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_48,
                    (undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
        zz_0009958_(iVar3,3);
      }
      iVar2 = iVar2 + 1;
      pfVar5 = pfVar5 + 3;
      pfVar4 = pfVar4 + 3;
      piVar6 = piVar6 + 1;
    } while (iVar2 < 3);
  }
  return;
}



// ==== 800172cc  zz_00172cc_ ====

void zz_00172cc_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  undefined8 uVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0x20,1);
  *(undefined1 *)(param_1 + 0x84) = 1;
  dVar5 = DOUBLE_80436bd0;
  *(float *)(param_1 + 100) = FLOAT_80436cd8;
  fVar2 = FLOAT_80436bc8;
  dVar6 = (double)FLOAT_80436d2c;
  dVar4 = (double)(float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x12) ^ 0x80000000) -
                         dVar5);
  fVar1 = (float)(dVar6 * dVar4 + (double)FLOAT_80436d28);
  *(float *)(param_1 + 0x68) = fVar1;
  *(float *)(param_1 + 0x6c) = fVar2;
  uVar3 = zz_0006fb4_((double)fVar1,dVar4,dVar5,dVar6,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
                      *(int *)(param_1 + 0x144),0x3c,param_4,param_5,param_6,param_7,param_8);
  zz_0006fb4_(uVar3,dVar4,dVar5,dVar6,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,*(int *)(param_1 + 0x148)
              ,*(char *)(param_1 + 0x12) + 0x66,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80017380  zz_0017380_ ====

void zz_0017380_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  FUN_800173a0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800173a0  FUN_800173a0 ====

/* WARNING: Removing unreachable block (ram,0x80017538) */
/* WARNING: Removing unreachable block (ram,0x800173b0) */

void FUN_800173a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  short sVar4;
  ushort uVar5;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar6;
  undefined8 uVar7;
  double dVar8;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(*(int *)(param_9 + 0x90) + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x3e4);
    *(undefined1 *)(param_9 + 0x19) = 0;
  }
  uVar6 = 1;
  uVar3 = 1 << ((int)*(char *)(param_9 + 0x12) << 1);
  uVar2 = uVar3 & 0xff;
  if (*(char *)(param_9 + 0x19) == '\0') {
    param_11 = (float *)0x0;
    *(undefined1 *)(param_9 + 0x170) = 0;
    fVar1 = FLOAT_80436d1c;
    if ((uVar2 & (byte)(&DAT_804360e0)[*(char *)(param_9 + 0x96)]) != 0) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(undefined2 *)(param_9 + 0x1c) = 0;
      *(undefined2 *)(param_9 + 0x1e) = 0x3c;
      *(float *)(param_9 + 0xd4) = fVar1;
      *(undefined1 *)(param_9 + 0x170) = 1;
      zz_00ea2c8_((&DAT_803c4e84)[*(char *)(param_9 + 0x96)],5);
    }
  }
  if (*(char *)(param_9 + 0x19) != '\0') {
    sVar4 = *(short *)(param_9 + 0x1e) + -1;
    *(short *)(param_9 + 0x1e) = sVar4;
    if ((sVar4 < 0) || ((uVar2 & (byte)(&DAT_804360e0)[*(char *)(param_9 + 0x96)]) == 0)) {
      *(undefined1 *)(param_9 + 0x19) = 0;
      *(undefined1 *)(param_9 + 0x170) = 0;
      (&DAT_804360e0)[*(char *)(param_9 + 0x96)] =
           (&DAT_804360e0)[*(char *)(param_9 + 0x96)] & ~(byte)uVar3;
    }
    else {
      uVar5 = *(short *)(param_9 + 0x1c) + 1;
      *(ushort *)(param_9 + 0x1c) = uVar5;
      fVar1 = FLOAT_80436bcc;
      if ((uVar5 & 8) != 0) {
        fVar1 = FLOAT_80436bc4;
      }
      dVar8 = (double)fVar1;
      if ((double)*(float *)(param_9 + 0xd4) != dVar8) {
        *(float *)(param_9 + 0xd4) = fVar1;
        zz_00086b8_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                    *(int *)(param_9 + 0x144),param_11,uVar6,param_13,param_14,param_15,param_16);
        uVar7 = zz_00086b8_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            DAT_804361fc,*(int *)(param_9 + 0x148),param_11,uVar6,param_13,param_14,
                            param_15,param_16);
        uVar7 = zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 0x144),extraout_r4,param_11,uVar6,param_13,param_14,
                            param_15,param_16);
        zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0x148),extraout_r4_00,param_11,uVar6,param_13,param_14,
                    param_15,param_16);
      }
    }
  }
  *(undefined1 *)(param_9 + 0x172) = 0;
  return;
}



// ==== 80017558  zz_0017558_ ====

void zz_0017558_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  float afStack_38 [12];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    param_1 = zz_0017380_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    iVar3 = *(int *)(param_9 + 0x144);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                (float *)(param_9 + 0x114),(undefined *)param_11,param_12,param_13,param_14,param_15
                ,param_16);
    iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
    zz_0009958_(iVar3,iVar1);
    dVar5 = (double)FLOAT_80436bc4;
    dVar6 = dVar5;
    gnt4_PSMTXTrans_bl((double)FLOAT_80436d30,dVar5,dVar5,afStack_38);
    pfVar2 = afStack_38;
    uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
    iVar3 = *(int *)(param_9 + 0x148);
    zz_00076d0_(uVar4,dVar5,dVar6,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_38,
                (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
    zz_0009958_(iVar3,iVar1);
  }
  return;
}



