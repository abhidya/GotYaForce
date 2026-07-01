// ==== 80023234  zz_0023234_ ====

void zz_0023234_(int param_1)

{
  uint uVar1;
  undefined *puVar2;
  
  puVar2 = (&PTR_DAT_802cddc8)[*(char *)(param_1 + 0x438)];
  uVar1 = zz_00055fc_();
  *(undefined2 *)(param_1 + 0x324) =
       *(undefined2 *)(puVar2 + ((uVar1 & 7) + *(char *)(param_1 + 0x439) * 8) * 2);
  return;
}



// ==== 800232a0  zz_00232a0_ ====

void zz_00232a0_(int param_1)

{
  uint uVar1;
  undefined *puVar2;
  
  puVar2 = (&PTR_DAT_802cec10)[*(char *)(param_1 + 0x438)];
  uVar1 = zz_00055fc_();
  *(undefined2 *)(param_1 + 0x326) =
       *(undefined2 *)(puVar2 + ((uVar1 & 7) + *(char *)(param_1 + 0x439) * 8) * 2);
  return;
}



// ==== 8002330c  zz_002330c_ ====

void zz_002330c_(int param_1)

{
  char cVar1;
  
  if ((*(char *)(param_1 + 0x6fc) == '\0') && (cVar1 = zz_008b480_(), cVar1 == '\0')) {
    *(short *)(param_1 + 0x324) = *(short *)(param_1 + 0x324) + -1;
  }
  else {
    *(short *)(param_1 + 0x324) = *(short *)(param_1 + 0x324) + -2;
  }
  if (*(short *)(param_1 + 0x324) < 1) {
    *(undefined2 *)(param_1 + 0x324) = 0;
  }
  return;
}



// ==== 8002337c  zz_002337c_ ====

void zz_002337c_(int param_1)

{
  char cVar1;
  
  if ((*(char *)(param_1 + 0x6fc) == '\0') && (cVar1 = zz_008b480_(), cVar1 == '\0')) {
    *(short *)(param_1 + 0x326) = *(short *)(param_1 + 0x326) + -1;
  }
  else {
    *(short *)(param_1 + 0x326) = *(short *)(param_1 + 0x326) + -2;
  }
  if (*(short *)(param_1 + 0x326) < 1) {
    *(undefined2 *)(param_1 + 0x326) = 0;
  }
  return;
}



// ==== 800233ec  zz_00233ec_ ====

undefined4 zz_00233ec_(int param_1)

{
  char cVar1;
  
  if (*(char *)(param_1 + 0x83) == '\0') {
    cVar1 = *(char *)(param_1 + 0x5e4);
    if (cVar1 == '\a') {
      return 1;
    }
    if (cVar1 == '\x0e') {
      return 1;
    }
    if (cVar1 == '.') {
      return 1;
    }
    if (cVar1 == '\t') {
      return 1;
    }
    if (cVar1 == '\n') {
      return 1;
    }
    if (cVar1 == '\v') {
      return 1;
    }
    if ((*(uint *)(param_1 + 0x5e0) & 3) != 0) {
      return 1;
    }
  }
  return 0;
}



// ==== 8002347c  zz_002347c_ ====

undefined4 zz_002347c_(double param_1,int param_2,undefined2 param_3)

{
  if ((*(char *)(param_2 + 0x30b) != '\x02') && (*(char *)(param_2 + 0x30b) != '\x03')) {
    return 1;
  }
  if (*(char *)(param_2 + 0x373) == '\0') {
    *(undefined1 *)(param_2 + 0x373) = 1;
    *(undefined2 *)(param_2 + 0x370) = param_3;
    *(undefined1 *)(param_2 + 0x372) = *(undefined1 *)(param_2 + 0x353);
    *(undefined1 *)(param_2 + 0x376) = *(undefined1 *)(param_2 + 0x30b);
    *(float *)(param_2 + 0x378) = (float)param_1;
    *(undefined1 *)(param_2 + 0x374) = 0;
    *(undefined1 *)(param_2 + 0x375) = 0;
    return 0;
  }
  return 0;
}



// ==== 800234e4  zz_00234e4_ ====

void zz_00234e4_(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float afStack_34 [3];
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (*(char *)(param_1 + 0x373) != '\0') {
    cVar1 = *(char *)(param_1 + 0x374);
    if (cVar1 == '\x01') {
      uVar3 = zz_006ab9c_(param_1);
      if (uVar3 == 0) {
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x370);
      }
      else {
        iVar4 = *(int *)(param_1 + 0x300);
        if (iVar4 == 0) {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x370)
          ;
        }
        else if ((*(char *)(iVar4 + 0x83) == '\0') && ((*(uint *)(iVar4 + 0x5e0) & 0x80000000) != 0)
                ) {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x370)
          ;
        }
        else if ((*(char *)(iVar4 + 0x83) != '\0') ||
                ((*(float *)(iVar4 + 0x720) <= FLOAT_80436dfc &&
                 ((*(ushort *)(iVar4 + 0x272) & 2) == 0)))) {
          local_28 = *(float *)(param_1 + 0x20);
          local_20 = *(undefined4 *)(param_1 + 0x28);
          local_24 = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x66c);
          local_1c = *(float *)(param_1 + 0x50c);
          local_18 = *(undefined4 *)(param_1 + 0x510);
          local_14 = *(undefined4 *)(param_1 + 0x514);
          if (*(char *)(param_1 + 0x352) != '\n') {
            dVar5 = gnt4_PSVECSquareDistance_bl(&local_28,&local_1c);
            if ((double)FLOAT_80436dfc < dVar5) {
              dVar6 = 1.0 / SQRT(dVar5);
              dVar6 = DOUBLE_80436e00 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436e08);
              dVar6 = DOUBLE_80436e00 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436e08);
              dVar5 = (double)(float)(dVar5 * DOUBLE_80436e00 * dVar6 *
                                              -(dVar5 * dVar6 * dVar6 - DOUBLE_80436e08));
            }
            if ((double)*(float *)(param_1 + 0x378) < dVar5) {
              *(uint *)(param_1 + 0x5b4) =
                   *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x370);
              return;
            }
          }
          sVar2 = *(short *)(param_1 + 1000);
          if ((((((sVar2 == 0x503) || (sVar2 == 0x507)) || (sVar2 == 0x508)) ||
               (((sVar2 == 0x50f || (sVar2 == 0x513)) ||
                ((sVar2 == 0x514 || ((sVar2 == 0x609 || (sVar2 == 0x61d)))))))) ||
              ((sVar2 == 0x602 || (((sVar2 == 0x60a || (sVar2 == 0x60c)) || (sVar2 == 0x60e)))))) ||
             (((sVar2 == 0x615 || (sVar2 == 0x629)) ||
              ((((sVar2 == 0x62a || ((sVar2 == 0x704 || (sVar2 == 0x707)))) || (sVar2 == 0x808)) ||
               (((((sVar2 == 0xa06 || (sVar2 == 0xa07)) || (sVar2 == 0xb01)) ||
                 ((sVar2 == 0xb03 || (sVar2 == 0xc04)))) ||
                ((sVar2 == 0xe00 ||
                 ((sVar2 == 0xe05 ||
                  (iVar4 = zz_003e978_(&local_28,&local_1c,afStack_34), iVar4 == 0)))))))))))) {
            *(undefined1 *)(param_1 + 0x374) = 2;
            if (*(short *)(param_1 + 1000) == 0xb03) {
              uVar3 = zz_00055fc_();
              *(ushort *)(param_1 + 0x350) = ((ushort)uVar3 & 0x1f) + 0x78;
            }
          }
          else {
            *(uint *)(param_1 + 0x5b4) =
                 *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x370);
          }
        }
        else {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x370)
          ;
        }
      }
    }
    else if (cVar1 < '\x01') {
      if (((-1 < cVar1) &&
          (*(uint *)(param_1 + 0x5b4) =
                *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x370),
          ((int)*(char *)(param_1 + 0x655) & 1 << (int)*(char *)(param_1 + 0x372)) != 0)) &&
         (uVar3 = zz_006ab9c_(param_1), uVar3 != 0)) {
        if (*(char *)(param_1 + 0x376) == '\x02') {
          *(undefined1 *)(param_1 + 0x374) = 1;
        }
        else {
          *(undefined1 *)(param_1 + 0x374) = 2;
        }
      }
    }
    else if (cVar1 < '\x03') {
      if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
        *(undefined1 *)(param_1 + 0x373) = 0;
        *(undefined1 *)(param_1 + 0x374) = 0;
        *(undefined1 *)(param_1 + 0x375) = 0;
      }
      else if (*(short *)(param_1 + 1000) == 0xb03) {
        if (*(short *)(param_1 + 0x350) < 1) {
          *(undefined1 *)(param_1 + 0x373) = 0;
          *(undefined1 *)(param_1 + 0x374) = 0;
          *(undefined1 *)(param_1 + 0x375) = 0;
        }
        else {
          *(short *)(param_1 + 0x350) = *(short *)(param_1 + 0x350) + -1;
          if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x370)) == 0) {
            *(uint *)(param_1 + 0x5b4) =
                 *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x370);
          }
        }
      }
    }
  }
  return;
}



// ==== 800238b4  zz_00238b4_ ====

/* WARNING: Removing unreachable block (ram,0x80023af4) */
/* WARNING: Removing unreachable block (ram,0x800238c4) */

undefined4 zz_00238b4_(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  float afStack_48 [3];
  float local_3c;
  float local_38;
  undefined4 local_34;
  float local_30;
  float local_2c;
  undefined4 local_28;
  
  local_3c = *(float *)(param_1 + 0x20);
  local_34 = *(undefined4 *)(param_1 + 0x28);
  local_30 = *(float *)(param_1 + 0x2e8);
  local_28 = *(undefined4 *)(param_1 + 0x2f0);
  local_38 = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x66c);
  local_2c = local_38;
  gnt4_PSVECSubtract_bl(&local_30,&local_3c,&local_30);
  dVar5 = gnt4_PSVECMag_bl(&local_30);
  if ((double)FLOAT_80436e74 < dVar5) {
    if ((double)*(float *)(param_1 + 0x668) < dVar5) {
      dVar5 = (double)*(float *)(param_1 + 0x668);
    }
    gnt4_PSVECNormalize_bl(&local_30,&local_30);
    gnt4_PSQUATScale_bl(dVar5,&local_30,&local_30);
    gnt4_PSVECAdd_bl(&local_3c,&local_30,&local_30);
    iVar2 = zz_003e978_(&local_3c,&local_30,afStack_48);
    if ((iVar2 == 2) || (iVar2 == 1)) {
      iVar2 = zz_0023b18_(param_1,(float *)(param_1 + 0x20));
      if (iVar2 != 0) {
        return 2;
      }
      return 1;
    }
  }
  local_3c = *(float *)(param_1 + 0x20);
  local_38 = *(float *)(param_1 + 0x24);
  local_34 = *(undefined4 *)(param_1 + 0x28);
  local_30 = *(float *)(param_1 + 0x2e8);
  local_28 = *(undefined4 *)(param_1 + 0x2f0);
  local_2c = local_38;
  gnt4_PSVECSubtract_bl(&local_30,&local_3c,&local_30);
  dVar5 = gnt4_PSVECMag_bl(&local_30);
  if ((double)FLOAT_80436e74 < dVar5) {
    if ((double)*(float *)(param_1 + 0x668) < dVar5) {
      dVar5 = (double)*(float *)(param_1 + 0x668);
    }
    gnt4_PSVECNormalize_bl(&local_30,&local_30);
    gnt4_PSQUATScale_bl(dVar5,&local_30,&local_30);
    gnt4_PSVECAdd_bl(&local_3c,&local_30,&local_30);
    if (FLOAT_80436e78 <= *(float *)(param_1 + 0x668)) {
      iVar2 = 4;
      fVar1 = *(float *)(param_1 + 0x668) * FLOAT_80436e80;
    }
    else {
      iVar2 = 2;
      fVar1 = FLOAT_80436e7c;
    }
    dVar5 = (double)fVar1;
    for (iVar4 = 0; iVar4 < iVar2; iVar4 = iVar4 + 1) {
      local_38 = (float)((double)local_38 + dVar5);
      local_2c = local_38;
      iVar3 = zz_003f044_(&local_3c,&local_30,afStack_48);
      if (iVar3 != 0) {
        return 1;
      }
      iVar3 = FUN_80037814(&local_3c,&local_30,afStack_48);
      if (iVar3 != 0) {
        return 1;
      }
    }
  }
  return 0;
}



// ==== 80023b18  zz_0023b18_ ====

/* WARNING: Removing unreachable block (ram,0x80023bcc) */
/* WARNING: Removing unreachable block (ram,0x80023b28) */

undefined4 zz_0023b18_(int param_1,float *param_2)

{
  int iVar1;
  short sVar2;
  double dVar3;
  double dVar4;
  float local_38;
  float local_34;
  float local_30;
  
  dVar4 = (double)FLOAT_80436e5c;
  sVar2 = 0;
  iVar1 = 0;
  do {
    dVar3 = zz_0045204_(sVar2);
    local_38 = (float)((double)(float)((double)*(float *)(param_1 + 0x668) * dVar4) * dVar3 +
                      (double)*param_2);
    dVar3 = zz_0045238_(sVar2);
    local_30 = (float)((double)(float)((double)*(float *)(param_1 + 0x668) * dVar4) * dVar3 +
                      (double)param_2[2]);
    local_34 = param_2[1];
    dVar3 = zz_003f320_((double)local_34,&local_38);
    if ((double)*(float *)(DAT_8043625c + 0x34) != dVar3) {
      return 1;
    }
    iVar1 = iVar1 + 1;
    sVar2 = sVar2 + 0x4000;
  } while (iVar1 < 4);
  return 0;
}



// ==== 80023bf4  zz_0023bf4_ ====

/* WARNING: Removing unreachable block (ram,0x80023fe4) */
/* WARNING: Removing unreachable block (ram,0x80023c04) */

void zz_0023bf4_(int param_1)

{
  short sVar1;
  bool bVar2;
  bool bVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  float *pfVar10;
  double dVar11;
  double dVar12;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  
  fVar5 = FLOAT_80436e90;
  fVar4 = FLOAT_80436dfc;
  bVar3 = false;
  switch(*(undefined1 *)(param_1 + 0x352)) {
  case 0:
  case 4:
  case 6:
  case 7:
    iVar9 = FUN_8002400c(param_1);
    if (iVar9 != 0) {
      bVar3 = true;
    }
    break;
  case 1:
  case 2:
  case 8:
  case 9:
    bVar3 = true;
    *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x354);
    *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x358);
    *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x35c);
    zz_0024824_(param_1);
    break;
  case 3:
    iVar9 = *(int *)(param_1 + 0x304);
    bVar3 = true;
    if (iVar9 == 0) {
      *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x354);
      *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x358);
      *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x35c);
      zz_0024824_(param_1);
    }
    else {
      iVar6 = FUN_800452a0((double)(*(float *)(iVar9 + 0x20) - *(float *)(param_1 + 0x354)),
                           (double)(*(float *)(iVar9 + 0x28) - *(float *)(param_1 + 0x35c)));
      uVar7 = zz_00055fc_();
      sVar1 = (short)iVar6 + -0x2000 + ((ushort)(uVar7 << 10) & 0x3c00);
      dVar12 = zz_0045204_(sVar1);
      *(float *)(param_1 + 0x2e8) =
           (float)((double)FLOAT_80436e10 * dVar12 + (double)*(float *)(param_1 + 0x354));
      dVar12 = zz_0045238_(sVar1);
      *(float *)(param_1 + 0x2f0) =
           (float)((double)FLOAT_80436e10 * dVar12 + (double)*(float *)(param_1 + 0x35c));
      *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x358);
      FUN_800241c0(param_1,iVar9);
      zz_0024824_(param_1);
    }
    break;
  case 5:
    bVar2 = false;
    iVar9 = 2;
    pcVar8 = DAT_803c4e84;
    do {
      if (((*pcVar8 != '\0') && (pcVar8[0x88] == *(char *)(param_1 + 0x88))) &&
         (pcVar8[0x1ea] != '\0')) {
        bVar2 = true;
        break;
      }
      if (((pcVar8[0x1e00] != '\0') && (pcVar8[0x1e88] == *(char *)(param_1 + 0x88))) &&
         (pcVar8[0x1fea] != '\0')) {
        bVar2 = true;
        pcVar8 = pcVar8 + 0x1e00;
        break;
      }
      if (((pcVar8[0x3c00] != '\0') && (pcVar8[0x3c88] == *(char *)(param_1 + 0x88))) &&
         (pcVar8[0x3dea] != '\0')) {
        bVar2 = true;
        pcVar8 = pcVar8 + 0x3c00;
        break;
      }
      pcVar8 = pcVar8 + 0x5a00;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    if (bVar2) {
      bVar3 = true;
      iVar9 = FUN_800452a0((double)(*(float *)(param_1 + 0x20) - *(float *)(pcVar8 + 0x20)),
                           (double)(*(float *)(param_1 + 0x28) - *(float *)(pcVar8 + 0x28)));
      uVar7 = zz_00055fc_();
      sVar1 = (short)iVar9 + -0x2000 + ((ushort)(uVar7 << 10) & 0x3c00);
      dVar12 = zz_0045204_(sVar1);
      *(float *)(param_1 + 0x2e8) =
           (float)((double)FLOAT_80436e28 * dVar12 + (double)*(float *)(pcVar8 + 0x20));
      dVar12 = zz_0045238_(sVar1);
      *(float *)(param_1 + 0x2f0) =
           (float)((double)FLOAT_80436e28 * dVar12 + (double)*(float *)(pcVar8 + 0x28));
      *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(pcVar8 + 0x24);
      FUN_800241c0(param_1,(int)pcVar8);
      zz_0024824_(param_1);
    }
    break;
  case 10:
    if (FLOAT_80436e84 <= *(float *)(param_1 + 0x24)) {
      dVar12 = (double)FLOAT_80436e88;
      pfVar10 = (float *)&DAT_802cfb04;
      local_38 = FLOAT_80436dfc;
      iVar9 = 0;
      local_34 = FLOAT_80436dfc;
      local_30 = FLOAT_80436dfc;
      do {
        local_2c = *pfVar10;
        local_28 = pfVar10[1];
        local_24 = pfVar10[2];
        dVar11 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),&local_2c);
        if ((dVar11 <= dVar12) && ((double)FLOAT_80436e8c < dVar11)) {
          local_38 = local_2c;
          local_34 = local_28;
          local_30 = local_24;
          dVar12 = dVar11;
        }
        iVar9 = iVar9 + 1;
        pfVar10 = pfVar10 + 3;
      } while (iVar9 < 4);
      *(float *)(param_1 + 0x2e8) = local_38;
      *(float *)(param_1 + 0x2ec) = local_34;
      *(float *)(param_1 + 0x2f0) = local_30;
      zz_0024824_(param_1);
      return;
    }
    *(float *)(param_1 + 0x2e8) = FLOAT_80436dfc;
    *(float *)(param_1 + 0x2ec) = fVar5;
    *(float *)(param_1 + 0x2f0) = fVar4;
    zz_0024824_(param_1);
    return;
  }
  if (!bVar3) {
    uVar7 = zz_00055fc_();
    sVar1 = (short)(uVar7 << 0xc);
    dVar12 = zz_0045204_(sVar1);
    *(float *)(param_1 + 0x2e8) =
         (float)((double)FLOAT_80436e28 * dVar12 + (double)*(float *)(param_1 + 0x20));
    dVar12 = zz_0045238_(sVar1);
    *(float *)(param_1 + 0x2f0) =
         (float)((double)FLOAT_80436e28 * dVar12 + (double)*(float *)(param_1 + 0x28));
    *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x24);
    FUN_800241c0(param_1,param_1);
    zz_0024824_(param_1);
  }
  zz_00247b0_((float *)(param_1 + 0x2e8));
  return;
}



// ==== 8002400c  FUN_8002400c ====

/* WARNING: Removing unreachable block (ram,0x8002419c) */
/* WARNING: Removing unreachable block (ram,0x8002401c) */

undefined4 FUN_8002400c(int param_1)

{
  char cVar1;
  short sVar2;
  short sVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  
  iVar7 = *(int *)(param_1 + 0x304);
  if (iVar7 == 0) {
    uVar4 = 0;
  }
  else {
    zz_0024824_(param_1);
    if ((*(short *)(param_1 + 1000) == 0xd06) || (*(short *)(param_1 + 1000) == 0xd07)) {
      uVar4 = 1;
      *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(iVar7 + 0x20);
      *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(iVar7 + 0x28);
      *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(iVar7 + 0x24);
    }
    else if (*(char *)(param_1 + 0x38d) == '\0') {
      iVar5 = FUN_800452a0((double)(*(float *)(param_1 + 0x20) - *(float *)(iVar7 + 0x20)),
                           (double)(*(float *)(param_1 + 0x28) - *(float *)(iVar7 + 0x28)));
      sVar3 = (short)iVar5;
      uVar6 = zz_00055fc_();
      cVar1 = *(char *)(param_1 + 0x661);
      if (cVar1 == '\x03') {
        sVar3 = sVar3 + *(short *)(&DAT_802ca4b0 + (uVar6 & 0xf) * 2);
      }
      if (((cVar1 == '\x02') || (cVar1 == '\x05')) || (*(short *)(param_1 + 1000) == 0x500)) {
        sVar2 = *(short *)(&DAT_802ca4d0 + (uVar6 & 0xf) * 2);
      }
      else {
        sVar2 = *(short *)(&DAT_802ca490 + (uVar6 & 0xf) * 2);
      }
      dVar9 = (double)*(float *)(*(int *)(param_1 + 0x4b0) + 0x114);
      dVar8 = zz_0045204_(sVar3 + sVar2);
      *(float *)(param_1 + 0x2e8) = (float)(dVar9 * dVar8 + (double)*(float *)(iVar7 + 0x20));
      dVar8 = zz_0045238_(sVar3 + sVar2);
      *(float *)(param_1 + 0x2f0) = (float)(dVar9 * dVar8 + (double)*(float *)(iVar7 + 0x28));
      *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(iVar7 + 0x24);
      FUN_800241c0(param_1,iVar7);
      uVar4 = 1;
    }
    else {
      *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(iVar7 + 0x20);
      *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(iVar7 + 0x28);
      *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(iVar7 + 0x24);
      FUN_800241c0(param_1,iVar7);
      uVar4 = 1;
    }
  }
  return uVar4;
}



// ==== 800241c0  FUN_800241c0 ====

/* WARNING: Removing unreachable block (ram,0x80024340) */
/* WARNING: Removing unreachable block (ram,0x80024338) */
/* WARNING: Removing unreachable block (ram,0x800241d8) */
/* WARNING: Removing unreachable block (ram,0x800241d0) */

void FUN_800241c0(int param_1,int param_2)

{
  float fVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  
  fVar1 = FLOAT_80436dfc;
  if (*(char *)(param_2 + 0x83) == '\0') {
    fVar1 = *(float *)(param_2 + 0x668);
  }
  dVar5 = (double)fVar1;
  dVar3 = zz_003f320_((double)*(float *)(param_1 + 0x2ec),(float *)(param_1 + 0x2e8));
  dVar4 = FUN_8003d6e4((double)(float)(dVar3 - (double)(float)(dVar5 + (double)*(float *)(param_2 +
                                                                                         0x24))),
                       param_2,(float *)(param_1 + 0x2e8));
  *(float *)(param_1 + 0x2ec) = (float)dVar4;
  if (((double)*(float *)(DAT_8043625c + 0x34) != dVar3) &&
     (iVar2 = zz_003e978_((float *)(param_1 + 0x2e8),(float *)(param_2 + 0x20),&local_58),
     iVar2 == 2)) {
    *(float *)(param_1 + 0x2e8) = local_58;
    *(undefined4 *)(param_1 + 0x2ec) = local_54;
    *(undefined4 *)(param_1 + 0x2f0) = local_50;
    dVar4 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),param_2,(float *)(param_1 + 0x2e8))
    ;
    *(float *)(param_1 + 0x2ec) = (float)dVar4;
  }
  dVar4 = zz_003f320_((double)*(float *)(param_1 + 0x2ec),(float *)(param_1 + 0x2e8));
  if ((double)*(float *)(param_1 + 0x24) < dVar4) {
    iVar2 = zz_00247b0_((float *)(param_1 + 0x2e8));
    if (iVar2 != 0) {
      dVar3 = FUN_8003d6e4((double)(float)(dVar3 - (double)(float)(dVar5 + (double)*(float *)(
                                                  param_2 + 0x24))),param_2,
                           (float *)(param_1 + 0x2e8));
      *(float *)(param_1 + 0x2ec) = (float)dVar3;
    }
    local_4c = *(float *)(param_1 + 0x2e8);
    local_48 = *(float *)(param_1 + 0x2ec);
    local_44 = *(undefined4 *)(param_1 + 0x2f0);
    local_3c = local_48 + FLOAT_80436e94;
    local_40 = local_4c;
    local_38 = local_44;
    iVar2 = FUN_80037b98(param_1,&local_40,&local_4c,&local_58);
    if (iVar2 != 0) {
      *(undefined4 *)(param_1 + 0x2ec) = local_54;
    }
  }
  else {
    FUN_800245d0(param_1,(float *)(param_1 + 0x2e8));
  }
  return;
}



// ==== 80024360  FUN_80024360 ====

/* WARNING: Removing unreachable block (ram,0x800245b4) */
/* WARNING: Removing unreachable block (ram,0x800245ac) */
/* WARNING: Removing unreachable block (ram,0x800245a4) */
/* WARNING: Removing unreachable block (ram,0x8002459c) */
/* WARNING: Removing unreachable block (ram,0x80024594) */
/* WARNING: Removing unreachable block (ram,0x80024390) */
/* WARNING: Removing unreachable block (ram,0x80024388) */
/* WARNING: Removing unreachable block (ram,0x80024380) */
/* WARNING: Removing unreachable block (ram,0x80024378) */
/* WARNING: Removing unreachable block (ram,0x80024370) */

void FUN_80024360(int param_1)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  int *piVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  int local_a0 [10];
  
  dVar13 = (double)FLOAT_80436e98;
  dVar12 = (double)*(float *)(param_1 + 0x314);
  bVar2 = false;
  dVar11 = (double)*(float *)(param_1 + 0x31c);
  dVar14 = (double)FLOAT_80436e34;
  iVar3 = FUN_800452a0((double)(float)((double)*(float *)(param_1 + 0x2e8) - dVar12),
                       (double)(float)((double)*(float *)(param_1 + 0x2f0) - dVar11));
  local_a0[0] = 0;
  dVar10 = (double)FLOAT_80436e34;
  local_a0[1] = 0;
  iVar5 = 0;
  local_a0[2] = 0;
  local_a0[3] = 0;
  local_a0[4] = 0;
  local_a0[5] = 0;
  local_a0[6] = 0;
  local_a0[7] = 0;
  do {
    iVar6 = 0;
    psVar7 = &DAT_802cfab4;
    piVar8 = local_a0;
    do {
      if (*piVar8 == 0) {
        sVar1 = *(short *)(param_1 + 0x72) + *psVar7;
        dVar9 = zz_0045204_(sVar1);
        local_ac = (float)(dVar14 * dVar9 + (double)*(float *)(param_1 + 0x314));
        dVar9 = zz_0045238_(sVar1);
        local_a4 = (float)(dVar14 * dVar9 + (double)*(float *)(param_1 + 0x31c));
        local_a8 = (float)((double)*(float *)(DAT_8043625c + 0x34) - (double)FLOAT_80436e2c);
        dVar9 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),param_1,&local_ac);
        local_a8 = (float)dVar9;
        if (((float)dVar9 < *(float *)(param_1 + 0x318)) &&
           ((double)(*(float *)(param_1 + 0x318) - (float)dVar9) < dVar13)) {
          iVar4 = zz_00247b0_(&local_ac);
          if (iVar4 == 0) {
            iVar4 = FUN_800452a0((double)(float)((double)local_ac - dVar12),
                                 (double)(float)((double)local_a4 - dVar11));
            sVar1 = (short)iVar4 - (short)iVar3;
            if ((sVar1 < -0x4800) || (0x4800 < sVar1)) {
              *piVar8 = 1;
            }
            else {
              bVar2 = true;
              dVar13 = (double)(*(float *)(param_1 + 0x318) - local_a8);
              local_b8 = local_ac;
              local_b4 = local_a8;
              local_b0 = local_a4;
            }
          }
          else {
            *piVar8 = 1;
          }
        }
      }
      iVar6 = iVar6 + 1;
      psVar7 = psVar7 + 1;
      piVar8 = piVar8 + 1;
    } while (iVar6 < 8);
    iVar5 = iVar5 + 1;
    dVar14 = (double)(float)(dVar14 + dVar10);
  } while (iVar5 < 0xf);
  if (bVar2) {
    *(float *)(param_1 + 0x2e8) = local_b8;
    *(float *)(param_1 + 0x2ec) = local_b4;
    *(float *)(param_1 + 0x2f0) = local_b0;
    zz_0024824_(param_1);
    *(undefined2 *)(param_1 + 0x33a) = 0xf0;
    if (*(ushort *)(param_1 + 0x308) < *(ushort *)(param_1 + 0x33a)) {
      *(ushort *)(param_1 + 0x33a) = *(ushort *)(param_1 + 0x308);
    }
  }
  else {
    *(undefined2 *)(param_1 + 0x308) = 0;
  }
  return;
}



// ==== 800245d0  FUN_800245d0 ====

/* WARNING: Removing unreachable block (ram,0x80024794) */
/* WARNING: Removing unreachable block (ram,0x8002478c) */
/* WARNING: Removing unreachable block (ram,0x80024784) */
/* WARNING: Removing unreachable block (ram,0x800245f0) */
/* WARNING: Removing unreachable block (ram,0x800245e8) */
/* WARNING: Removing unreachable block (ram,0x800245e0) */

void FUN_800245d0(int param_1,float *param_2)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  float afStack_98 [3];
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  
  dVar7 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,param_2);
  local_7c = (float)dVar7;
  dVar9 = (double)FLOAT_80436e9c;
  local_74 = *param_2;
  bVar2 = false;
  dVar7 = (double)FLOAT_80436e88;
  iVar4 = 0;
  local_70 = FLOAT_80436e44 + param_2[1];
  local_6c = param_2[2];
  dVar10 = dVar9;
  while( true ) {
    iVar5 = 0;
    psVar6 = &DAT_802cfab4;
    do {
      sVar1 = *(short *)(param_1 + 0x72) + *psVar6;
      dVar8 = zz_0045204_(sVar1);
      local_80 = (float)(dVar9 * dVar8 + (double)*(float *)(param_1 + 0x20));
      dVar8 = zz_0045238_(sVar1);
      local_78 = (float)(dVar9 * dVar8 + (double)*(float *)(param_1 + 0x28));
      iVar3 = zz_0023b18_(param_1,&local_80);
      if (iVar3 == 0) {
        dVar8 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,&local_80);
        local_7c = (float)dVar8;
        local_68 = local_80;
        local_64 = local_7c + FLOAT_80436e44;
        local_60 = local_78;
        iVar3 = zz_003f044_(&local_74,&local_68,afStack_98);
        if (((iVar3 == 0) && (iVar3 = zz_00247b0_(&local_80), iVar3 == 0)) &&
           (dVar8 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x2e8),&local_80), dVar8 < dVar7
           )) {
          bVar2 = true;
          local_8c = local_80;
          local_88 = local_7c;
          local_84 = local_78;
          dVar7 = dVar8;
        }
      }
      iVar5 = iVar5 + 1;
      psVar6 = psVar6 + 1;
    } while (iVar5 < 8);
    if (bVar2) break;
    iVar4 = iVar4 + 1;
    dVar9 = (double)(float)(dVar9 + dVar10);
    if (7 < iVar4) {
      return;
    }
  }
  *(float *)(param_1 + 0x2e8) = local_8c;
  *(float *)(param_1 + 0x2ec) = local_88;
  *(float *)(param_1 + 0x2f0) = local_84;
  zz_0024824_(param_1);
  return;
}



// ==== 800247b0  zz_00247b0_ ====

undefined4 zz_00247b0_(float *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*param_1 <= *(float *)(DAT_8043625c + 0x48)) {
    if (*param_1 < *(float *)(DAT_8043625c + 0x4c)) {
      *param_1 = *(float *)(DAT_8043625c + 0x4c);
      uVar1 = 1;
    }
  }
  else {
    *param_1 = *(float *)(DAT_8043625c + 0x48);
    uVar1 = 1;
  }
  if (param_1[2] <= *(float *)(DAT_8043625c + 0x50)) {
    if (param_1[2] < *(float *)(DAT_8043625c + 0x54)) {
      param_1[2] = *(float *)(DAT_8043625c + 0x54);
      uVar1 = 1;
    }
  }
  else {
    param_1[2] = *(float *)(DAT_8043625c + 0x50);
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 80024824  zz_0024824_ ====

void zz_0024824_(int param_1)

{
  double dVar1;
  double dVar2;
  
  dVar1 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x20));
  if ((double)FLOAT_80436dfc < dVar1) {
    dVar2 = 1.0 / SQRT(dVar1);
    dVar2 = DOUBLE_80436e00 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_80436e08);
    dVar2 = DOUBLE_80436e00 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_80436e08);
    dVar1 = (double)(float)(dVar1 * DOUBLE_80436e00 * dVar2 *
                                    -(dVar1 * dVar2 * dVar2 - DOUBLE_80436e08));
  }
  *(short *)(param_1 + 0x308) =
       (short)(int)(dVar1 / (double)*(float *)(*(int *)(param_1 + 0x4ac) + 0x2c));
  *(short *)(param_1 + 0x308) = *(short *)(param_1 + 0x308) << 1;
  if (*(ushort *)(param_1 + 0x308) < 0x5a) {
    *(undefined2 *)(param_1 + 0x308) = 0x5a;
  }
  else if (0x168 < *(ushort *)(param_1 + 0x308)) {
    *(undefined2 *)(param_1 + 0x308) = 0x168;
  }
  return;
}



// ==== 80024900  zz_0024900_ ====

/* WARNING: Removing unreachable block (ram,0x80024a70) */
/* WARNING: Removing unreachable block (ram,0x80024910) */

void zz_0024900_(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  short sVar3;
  ushort uVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  
  if (*(char *)(param_1 + 0x38d) == '\x02') {
    iVar5 = FUN_800452a0((double)(*(float *)(param_1 + 0x2e8) - *(float *)(param_1 + 0x20)),
                         (double)(*(float *)(param_1 + 0x2f0) - *(float *)(param_1 + 0x28)));
    uVar4 = (short)iVar5 - *(short *)(param_1 + 0x5b0);
    if ((((uVar4 < 0x1000) || (fVar1 = FLOAT_80436e50, fVar2 = FLOAT_80436dfc, 0x7000 < uVar4)) &&
        (fVar1 = FLOAT_80436dfc, fVar2 = FLOAT_80436e50, 0x8fff < uVar4)) &&
       (fVar2 = FLOAT_80436e50, uVar4 < 0xf001)) {
      fVar1 = FLOAT_80436ea0;
      fVar2 = FLOAT_80436dfc;
    }
    fVar1 = fVar1 * FLOAT_80436e60;
    fVar2 = fVar2 * FLOAT_80436e60;
    *(char *)(param_1 + 0x337) = (char)(int)fVar1;
    *(char *)(param_1 + 0x338) = (char)(int)fVar2;
    zz_0024d1c_((double)fVar1,(double)fVar2,param_1,param_2);
  }
  else {
    iVar5 = FUN_800452a0((double)(*(float *)(param_1 + 0x2e8) - *(float *)(param_1 + 0x20)),
                         (double)(*(float *)(param_1 + 0x2f0) - *(float *)(param_1 + 0x28)));
    sVar3 = (short)iVar5 - *(short *)(param_1 + 0x5b0);
    dVar6 = zz_0045204_(sVar3);
    dVar7 = zz_0045238_(sVar3);
    dVar6 = dVar6 * (double)FLOAT_80436e60;
    dVar7 = -dVar7 * (double)FLOAT_80436e60;
    *(char *)(param_1 + 0x337) = (char)(int)dVar6;
    *(char *)(param_1 + 0x338) = (char)(int)dVar7;
    zz_0024d1c_((double)(float)dVar6,(double)(float)dVar7,param_1,param_2);
  }
  return;
}



// ==== 80024a94  zz_0024a94_ ====

void zz_0024a94_(int param_1)

{
  float fVar1;
  uint uVar2;
  
  uVar2 = zz_0027704_(param_1,(float *)(param_1 + 0x2e8));
  uVar2 = uVar2 & 0xffff;
  if ((((uVar2 < 0x1000) || (fVar1 = FLOAT_80436ea0, 0x8000 < uVar2)) &&
      (fVar1 = FLOAT_80436dfc, 0x8000 < uVar2)) && (uVar2 < 0xf001)) {
    fVar1 = FLOAT_80436e50;
  }
  *(char *)(param_1 + 0x337) = (char)(int)(fVar1 * FLOAT_80436e60);
  return;
}



// ==== 80024b24  zz_0024b24_ ====

void zz_0024b24_(int param_1)

{
  float fVar1;
  uint uVar2;
  
  uVar2 = zz_0027704_(param_1,(float *)(param_1 + 0x50c));
  uVar2 = uVar2 & 0xffff;
  if ((((uVar2 < 0x1000) || (fVar1 = FLOAT_80436ea0, 0x8000 < uVar2)) &&
      (fVar1 = FLOAT_80436dfc, 0x8000 < uVar2)) && (uVar2 < 0xf001)) {
    fVar1 = FLOAT_80436e50;
  }
  *(char *)(param_1 + 0x337) = (char)(int)(fVar1 * FLOAT_80436e60);
  return;
}



// ==== 80024bb4  FUN_80024bb4 ====

/* WARNING: Removing unreachable block (ram,0x80024cf8) */
/* WARNING: Removing unreachable block (ram,0x80024cf0) */
/* WARNING: Removing unreachable block (ram,0x80024ce8) */
/* WARNING: Removing unreachable block (ram,0x80024bd4) */
/* WARNING: Removing unreachable block (ram,0x80024bcc) */
/* WARNING: Removing unreachable block (ram,0x80024bc4) */

void FUN_80024bb4(int param_1)

{
  bool bVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double in_f30;
  double dVar5;
  float local_58;
  undefined4 local_54;
  float local_50;
  
  dVar3 = zz_0045204_(*(short *)(param_1 + 0x72));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x72));
  local_58 = *(float *)(param_1 + 0x20);
  bVar1 = false;
  local_54 = *(undefined4 *)(param_1 + 0x24);
  iVar2 = 0;
  dVar5 = (double)(float)(dVar3 * (double)FLOAT_80436e20);
  dVar3 = (double)(float)(dVar4 * (double)FLOAT_80436e20);
  local_50 = *(float *)(param_1 + 0x28);
  do {
    local_58 = (float)((double)local_58 + dVar5);
    local_50 = (float)((double)local_50 + dVar3);
    dVar4 = FUN_8003d964((double)*(float *)(DAT_8043625c + 0x34),param_1,&local_58);
    if ((double)*(float *)(param_1 + 0x24) < dVar4) {
      in_f30 = (double)FLOAT_80436ea0;
      bVar1 = true;
      break;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 3);
  if (!bVar1) {
    dVar3 = FUN_8003d964((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
    if (*(float *)(param_1 + 0x24) <=
        (float)(dVar3 + (double)(FLOAT_80436e7c + *(float *)(param_1 + 0x36c)))) {
      if ((float)(dVar3 + (double)(*(float *)(param_1 + 0x36c) - FLOAT_80436e7c)) <=
          *(float *)(param_1 + 0x24)) {
        in_f30 = (double)FLOAT_80436dfc;
      }
      else {
        in_f30 = (double)FLOAT_80436ea0;
      }
    }
    else {
      in_f30 = (double)FLOAT_80436e50;
    }
  }
  *(char *)(param_1 + 0x338) = (char)(int)(in_f30 * (double)FLOAT_80436e60);
  return;
}



// ==== 80024d1c  zz_0024d1c_ ====

void zz_0024d1c_(double param_1,double param_2,int param_3,int param_4)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  double dVar4;
  
  if (param_4 == 0) {
    *(char *)(param_3 + 0x5ca) = (char)(int)param_1;
    *(char *)(param_3 + 0x5cb) = (char)(int)param_2;
    bVar2 = FUN_8008b73c((char)(int)param_1,(char)(int)param_2,0x1e);
    *(uint *)(param_3 + 0x5b4) = *(uint *)(param_3 + 0x5b4) | (uint)bVar2 << 0x10;
  }
  else {
    dVar4 = (double)FLOAT_80436ea4;
    cVar3 = (char)(int)(param_1 * dVar4);
    *(char *)(param_3 + 0x5ca) = cVar3;
    cVar1 = (char)(int)(param_2 * dVar4);
    *(char *)(param_3 + 0x5cb) = cVar1;
    bVar2 = FUN_8008b73c(cVar3,cVar1,0x1e);
    *(uint *)(param_3 + 0x5b4) = *(uint *)(param_3 + 0x5b4) | (uint)bVar2 << 0x10;
  }
  return;
}



// ==== 80024dec  FUN_80024dec ====

/* WARNING: Removing unreachable block (ram,0x80024e88) */
/* WARNING: Removing unreachable block (ram,0x80024dfc) */

void FUN_80024dec(int param_1)

{
  short sVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  
  iVar2 = FUN_800452a0((double)(*(float *)(param_1 + 0x2e8) - *(float *)(param_1 + 0x20)),
                       (double)(*(float *)(param_1 + 0x2f0) - *(float *)(param_1 + 0x28)));
  sVar1 = (short)iVar2 - *(short *)(param_1 + 0x5b0);
  dVar4 = zz_0045204_(sVar1);
  dVar5 = zz_0045238_(sVar1);
  dVar3 = (double)FLOAT_80436e60;
  *(char *)(param_1 + 0x337) = (char)(int)(dVar4 * dVar3);
  *(char *)(param_1 + 0x338) = (char)(int)(-dVar5 * dVar3);
  return;
}



// ==== 80024ea8  FUN_80024ea8 ====

/* WARNING: Removing unreachable block (ram,0x80024f44) */
/* WARNING: Removing unreachable block (ram,0x80024eb8) */

void FUN_80024ea8(int param_1)

{
  short sVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  
  iVar2 = FUN_800452a0((double)(*(float *)(param_1 + 0x50c) - *(float *)(param_1 + 0x20)),
                       (double)(*(float *)(param_1 + 0x514) - *(float *)(param_1 + 0x28)));
  sVar1 = (short)iVar2 - *(short *)(param_1 + 0x5b0);
  dVar4 = zz_0045204_(sVar1);
  dVar5 = zz_0045238_(sVar1);
  dVar3 = (double)FLOAT_80436e60;
  *(char *)(param_1 + 0x337) = (char)(int)(dVar4 * dVar3);
  *(char *)(param_1 + 0x338) = (char)(int)(-dVar5 * dVar3);
  return;
}



// ==== 80024f64  FUN_80024f64 ====

/* WARNING: Removing unreachable block (ram,0x8002505c) */
/* WARNING: Removing unreachable block (ram,0x80025054) */
/* WARNING: Removing unreachable block (ram,0x80024f7c) */
/* WARNING: Removing unreachable block (ram,0x80024f74) */

void FUN_80024f64(int param_1)

{
  int iVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float local_38;
  undefined4 local_34;
  float local_30;
  
  dVar2 = zz_0045204_(*(short *)(param_1 + 0x72));
  dVar3 = zz_0045238_(*(short *)(param_1 + 0x72));
  local_38 = *(float *)(param_1 + 0x20);
  iVar1 = 0;
  local_34 = *(undefined4 *)(param_1 + 0x24);
  dVar4 = (double)(float)(dVar2 * (double)FLOAT_80436e20);
  dVar2 = (double)(float)(dVar3 * (double)FLOAT_80436e20);
  local_30 = *(float *)(param_1 + 0x28);
  do {
    local_38 = (float)((double)local_38 + dVar4);
    local_30 = (float)((double)local_30 + dVar2);
    dVar3 = FUN_8003d964((double)*(float *)(DAT_8043625c + 0x34),param_1,&local_38);
    if ((double)*(float *)(param_1 + 0x24) < dVar3) {
      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
      return;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 3);
  dVar2 = FUN_8003d964((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
  if (*(float *)(param_1 + 0x24) <
      (float)(dVar2 + (double)(*(float *)(param_1 + 0x36c) - FLOAT_80436e7c))) {
    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
  }
  return;
}



// ==== 8002507c  FUN_8002507c ====

/* WARNING: Removing unreachable block (ram,0x80025114) */
/* WARNING: Removing unreachable block (ram,0x8002508c) */

bool FUN_8002507c(double param_1,int param_2)

{
  double dVar1;
  double dVar2;
  
  dVar1 = gnt4_PSVECSquareDistance_bl((float *)(param_2 + 0x2e8),(float *)(param_2 + 0x20));
  if ((double)FLOAT_80436dfc < dVar1) {
    dVar2 = 1.0 / SQRT(dVar1);
    dVar2 = DOUBLE_80436e00 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_80436e08);
    dVar2 = DOUBLE_80436e00 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_80436e08);
    dVar1 = (double)(float)(dVar1 * DOUBLE_80436e00 * dVar2 *
                                    -(dVar1 * dVar2 * dVar2 - DOUBLE_80436e08));
  }
  return dVar1 <= param_1;
}



// ==== 8002512c  zz_002512c_ ====

bool zz_002512c_(double param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  
  fVar1 = *(float *)(param_2 + 0x2f0) - *(float *)(param_2 + 0x28);
  fVar2 = *(float *)(param_2 + 0x2e8) - *(float *)(param_2 + 0x20);
  dVar4 = (double)(fVar2 * fVar2 + fVar1 * fVar1);
  if ((double)FLOAT_80436dfc < dVar4) {
    dVar3 = 1.0 / SQRT(dVar4);
    dVar3 = DOUBLE_80436e00 * dVar3 * -(dVar4 * dVar3 * dVar3 - DOUBLE_80436e08);
    dVar3 = DOUBLE_80436e00 * dVar3 * -(dVar4 * dVar3 * dVar3 - DOUBLE_80436e08);
    dVar4 = (double)(float)(dVar4 * DOUBLE_80436e00 * dVar3 *
                                    -(dVar4 * dVar3 * dVar3 - DOUBLE_80436e08));
  }
  return dVar4 <= param_1;
}



// ==== 800251d0  FUN_800251d0 ====

/* WARNING: Removing unreachable block (ram,0x8002529c) */
/* WARNING: Removing unreachable block (ram,0x800251e0) */

void FUN_800251d0(int param_1)

{
  short sVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  
  iVar2 = FUN_800452a0((double)(*(float *)(param_1 + 0x50c) - *(float *)(param_1 + 0x20)),
                       (double)(*(float *)(param_1 + 0x514) - *(float *)(param_1 + 0x28)));
  sVar1 = (short)iVar2 - *(short *)(param_1 + 0x5b0);
  dVar3 = zz_0045204_(sVar1);
  dVar4 = zz_0045238_(sVar1);
  dVar3 = dVar3 * (double)FLOAT_80436e60;
  dVar4 = -dVar4 * (double)FLOAT_80436e60;
  *(char *)(param_1 + 0x337) = (char)(int)dVar3;
  *(char *)(param_1 + 0x338) = (char)(int)dVar4;
  zz_0024d1c_((double)(float)dVar3,(double)(float)dVar4,param_1,1);
  if ((0 < *(short *)(param_1 + 0x784)) && ((*(uint *)(param_1 + 0x5b8) & 0x400) == 0)) {
    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
  }
  return;
}



// ==== 800252bc  zz_00252bc_ ====

void zz_00252bc_(char *param_1)

{
  char *pcVar1;
  int iVar2;
  
  if (*(short *)(param_1 + 0x32a) < 1) {
    zz_002532c_(param_1);
  }
  else {
    *(short *)(param_1 + 0x32a) = *(short *)(param_1 + 0x32a) + -1;
    pcVar1 = *(char **)(param_1 + 0x508);
    if (((pcVar1 != (char *)0x0) && (pcVar1[0x83] == '\0')) &&
       (iVar2 = zz_0025cfc_(pcVar1), iVar2 == 0)) {
      zz_002532c_(param_1);
    }
  }
  return;
}



// ==== 8002532c  zz_002532c_ ====

void zz_002532c_(char *param_1)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  char cVar8;
  char cVar9;
  int iVar10;
  
  uVar4 = zz_00055fc_();
  cVar9 = '\0';
  iVar7 = 0;
  *(undefined2 *)(param_1 + 0x32a) = *(undefined2 *)(&DAT_802cfaf4 + (uVar4 & 7) * 2);
  iVar10 = 3;
  pcVar6 = param_1;
  do {
    iVar5 = *(int *)(param_1 + 0x4b0) + iVar7;
    cVar1 = *(char *)(iVar5 + 0x108);
    cVar8 = cVar9;
    if ((((((cVar1 != '\0') && (cVar8 = cVar1, *(char *)(iVar5 + 0xb8) != '\0')) &&
          (*(char *)(iVar5 + 0x10e) != '\x02')) &&
         ((*(char *)(iVar5 + 0x10e) != '\x03' && (cVar8 = cVar9, iVar7 < 3)))) &&
        (*(char *)(iVar5 + 0xb8) == '\x01')) &&
       ((0 < *(short *)(pcVar6 + 0x774) || (*(short *)(pcVar6 + 0x78e) == 0)))) {
      cVar8 = cVar1;
    }
    iVar5 = *(int *)(param_1 + 0x4b0) + iVar7 + 1;
    cVar1 = *(char *)(iVar5 + 0x108);
    cVar9 = cVar8;
    if ((((cVar1 != '\0') && (cVar9 = cVar1, *(char *)(iVar5 + 0xb8) != '\0')) &&
        (*(char *)(iVar5 + 0x10e) != '\x02')) &&
       (((*(char *)(iVar5 + 0x10e) != '\x03' && (cVar9 = cVar8, iVar7 + 1 < 3)) &&
        ((*(char *)(iVar5 + 0xb8) == '\x01' &&
         ((0 < *(short *)(pcVar6 + 0x77c) || (*(short *)(pcVar6 + 0x796) == 0)))))))) {
      cVar9 = cVar1;
    }
    pcVar6 = pcVar6 + 0x10;
    iVar7 = iVar7 + 2;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  bVar3 = false;
  if (cVar9 == '\x01') {
    cVar9 = param_1[0x38e];
    if (cVar9 == '\x01') {
      param_1[0x30a] = '\0';
      pcVar6 = *(char **)(param_1 + 0x300);
      if (pcVar6 == (char *)0x0) {
        param_1[0x38e] = '\0';
      }
      else if ((*pcVar6 == '\0') || (pcVar6[0x18] != '\x01')) {
        param_1[0x38e] = '\0';
      }
      else {
        iVar7 = zz_002590c_((int)pcVar6);
        if (iVar7 == 0) {
          param_1[0x38e] = '\0';
        }
        else {
          bVar3 = true;
          param_1[0x30a] = '\x01';
        }
      }
    }
    else if ((cVar9 < '\x01') && (-1 < cVar9)) {
      iVar7 = 0;
      param_1[0x30a] = '\0';
      pcVar6 = DAT_803c4e84;
      if (param_1[0x58b] != '\0') {
        do {
          if ((((((int)param_1[0x58b] & 1 << iVar7) != 0) && (pcVar6[0x3e6] == '\0')) &&
              (pcVar6[0x88] == param_1[0x88])) &&
             ((*(short *)(pcVar6 + 1000) != 0xf07 &&
              (iVar10 = zz_002590c_((int)pcVar6), iVar10 != 0)))) {
            bVar3 = true;
            param_1[0x30a] = '\x01';
            *(char **)(param_1 + 0x300) = pcVar6;
            param_1[0x38e] = param_1[0x38e] + '\x01';
            break;
          }
          iVar7 = iVar7 + 1;
          pcVar6 = pcVar6 + 0x1e00;
        } while (iVar7 < 6);
      }
      if (!bVar3) {
        iVar7 = 0;
        pcVar6 = DAT_803c4e84;
        do {
          iVar10 = zz_0025cfc_(pcVar6);
          if (((iVar10 != 0) && (param_1 != pcVar6)) &&
             ((pcVar6[0x88] == param_1[0x88] && (iVar10 = zz_00258c0_((int)pcVar6), iVar10 != 0))))
          {
            bVar3 = true;
            param_1[0x30a] = '\x01';
            *(char **)(param_1 + 0x300) = pcVar6;
            param_1[0x38e] = param_1[0x38e] + '\x01';
            break;
          }
          iVar7 = iVar7 + 1;
          pcVar6 = pcVar6 + 0x1e00;
        } while (iVar7 < 6);
      }
    }
  }
  else {
    if (cVar9 < '\x01') {
      if (-1 < cVar9) {
        param_1[0x30a] = '\0';
        goto LAB_800256e4;
      }
    }
    else if (cVar9 < '\x03') {
      iVar7 = 0;
      param_1[0x30a] = '\0';
      pcVar6 = DAT_803c4e84;
      if (param_1[0x37e] != '\0') {
        do {
          iVar10 = zz_0025cfc_(pcVar6);
          if (((iVar10 != 0) && (param_1 != pcVar6)) && (pcVar6[0x88] == param_1[0x88])) {
            param_1[0x30a] = '\x02';
            pcVar6 = FUN_80025944(param_1);
            *(char **)(param_1 + 0x300) = pcVar6;
            bVar3 = true;
            break;
          }
          iVar7 = iVar7 + 1;
          pcVar6 = pcVar6 + 0x1e00;
        } while (iVar7 < 6);
      }
      goto LAB_800256e4;
    }
    param_1[0x30a] = '\0';
  }
LAB_800256e4:
  if (!bVar3) {
    bVar2 = false;
    if (((PTR_DAT_80433930[0x32] == '\0') && (param_1[0x88] == '\x01')) &&
       (uVar4 = zz_00055fc_(), (uVar4 & 7) == 0)) {
      bVar2 = true;
      param_1[0x32a] = '\0';
      param_1[0x32b] = -0x4c;
    }
    cVar9 = param_1[0x352];
    if (cVar9 == '\x04') {
      iVar7 = 0;
      pcVar6 = DAT_803c4e84;
      do {
        iVar10 = zz_0025cfc_(pcVar6);
        if (((iVar10 != 0) && (pcVar6[0x88] != param_1[0x88])) && (pcVar6[0x1ea] != '\0')) {
          *(char **)(param_1 + 0x300) = pcVar6;
          bVar3 = true;
        }
        iVar7 = iVar7 + 1;
        pcVar6 = pcVar6 + 0x1e00;
      } while (iVar7 < 6);
    }
    else if ((cVar9 == '\x06') || (bVar2)) {
      iVar7 = 0;
      pcVar6 = DAT_803c4e84;
      do {
        iVar10 = zz_0025cfc_(pcVar6);
        if (((iVar10 != 0) && (pcVar6[0x3e6] == '\0')) && (pcVar6[0x88] != param_1[0x88])) {
          *(char **)(param_1 + 0x300) = pcVar6;
          bVar3 = true;
        }
        iVar7 = iVar7 + 1;
        pcVar6 = pcVar6 + 0x1e00;
      } while (iVar7 < 6);
    }
    else if (cVar9 == '\a') {
      iVar7 = 0;
      pcVar6 = DAT_803c4e84;
      do {
        iVar10 = zz_0025cfc_(pcVar6);
        if (((iVar10 != 0) && (pcVar6[0x3e6] != '\0')) && (pcVar6[0x88] != param_1[0x88])) {
          *(char **)(param_1 + 0x300) = pcVar6;
          bVar3 = true;
        }
        iVar7 = iVar7 + 1;
        pcVar6 = pcVar6 + 0x1e00;
      } while (iVar7 < 6);
    }
  }
  if (!bVar3) {
    pcVar6 = FUN_80025944(param_1);
    *(char **)(param_1 + 0x300) = pcVar6;
  }
  if (*(int *)(param_1 + 0x304) != *(int *)(param_1 + 0x300)) {
    zz_0023bf4_((int)param_1);
  }
  *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(param_1 + 0x300);
  param_1[0x30f] = '\0';
  FUN_80025a84((int)param_1);
  return;
}



// ==== 800258c0  zz_00258c0_ ====

undefined4 zz_00258c0_(int param_1)

{
  int iVar1;
  
  iVar1 = (int)*(short *)(param_1 + 0x1c6);
  if (((*(short *)(param_1 + 0x1c4) - iVar1 < 100) &&
      (((*(short *)(param_1 + 0x1c4) == iVar1 || (0x32 < iVar1)) &&
       (*(short *)(param_1 + 0x6b8) == 0)))) && (*(short *)(param_1 + 0x6ba) == 0)) {
    return 0;
  }
  return 1;
}



// ==== 8002590c  zz_002590c_ ====

undefined4 zz_002590c_(int param_1)

{
  if (((*(short *)(param_1 + 0x1c4) == *(short *)(param_1 + 0x1c6)) &&
      (*(short *)(param_1 + 0x6b8) == 0)) && (*(short *)(param_1 + 0x6ba) == 0)) {
    return 0;
  }
  return 1;
}



// ==== 80025944  FUN_80025944 ====

/* WARNING: Removing unreachable block (ram,0x800259ec) */
/* WARNING: Removing unreachable block (ram,0x80025954) */

char * FUN_80025944(char *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  double dVar6;
  double dVar7;
  
  dVar7 = (double)FLOAT_80436e88;
  pcVar4 = (char *)0x0;
  iVar3 = 0;
  pcVar5 = DAT_803c4e84;
  do {
    if ((((*pcVar5 != '\0') && (param_1 != pcVar5)) &&
        (uVar1 = zz_0025a14_((int)param_1,(int)pcVar5), uVar1 != 0)) &&
       ((iVar2 = zz_0025cfc_(pcVar5), iVar2 != 0 &&
        (dVar6 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(pcVar5 + 0x20)),
        dVar6 <= dVar7)))) {
      pcVar4 = pcVar5;
      dVar7 = dVar6;
    }
    iVar3 = iVar3 + 1;
    pcVar5 = pcVar5 + 0x1e00;
  } while (iVar3 < 6);
  return pcVar4;
}



// ==== 80025a14  zz_0025a14_ ====

uint zz_0025a14_(int param_1,int param_2)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x30a);
  if (cVar1 == '\0') {
    return (uint)((int)*(char *)(param_1 + 0x88) - (int)*(char *)(param_2 + 0x88) |
                 (int)*(char *)(param_2 + 0x88) - (int)*(char *)(param_1 + 0x88)) >> 0x1f;
  }
  if ((-1 < cVar1) && (cVar1 < '\x03')) {
    if (*(char *)(param_2 + 0x88) == *(char *)(param_1 + 0x88)) {
      return 1;
    }
    return 0;
  }
  return 0;
}



// ==== 80025a84  FUN_80025a84 ====

/* WARNING: Removing unreachable block (ram,0x80025ce0) */
/* WARNING: Removing unreachable block (ram,0x80025a94) */

void FUN_80025a84(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  
  if ('\0' < *(char *)(param_1 + 0x30f)) {
    *(char *)(param_1 + 0x30f) = *(char *)(param_1 + 0x30f) + -1;
  }
  if ((*(int *)(param_1 + 0x300) != 0) && (*(int *)(param_1 + 0x508) != 0)) {
    if ((*(char *)(param_1 + 0x352) == '\n') &&
       ((*(char *)(param_1 + 0x30a) != '\x01' && (*(char *)(param_1 + 0x30a) != '\x02')))) {
      iVar5 = 0;
      dVar8 = (double)FLOAT_80436e88;
      iVar6 = *(int *)(PTR_DAT_80433934 + 0xbc);
      if (iVar6 != 0) {
        iVar3 = 0;
        if (FLOAT_80436e84 <= *(float *)(param_1 + 0x24)) {
          iVar3 = 4;
        }
        iVar4 = 0;
        do {
          iVar2 = *(int *)(iVar6 + (iVar4 + iVar3) * 4 + 0x144);
          if ((iVar2 != 0) &&
             (dVar7 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(iVar2 + 0x20))
             , dVar7 <= dVar8)) {
            iVar5 = iVar2;
            dVar8 = dVar7;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < 4);
      }
      if ((iVar5 == *(int *)(param_1 + 0x508)) || (iVar5 == 0)) {
        if ((*(char *)(param_1 + 0x30a) == '\x01') || (*(char *)(param_1 + 0x30a) == '\x02')) {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x10;
          *(undefined1 *)(param_1 + 0x30f) = 0x1e;
        }
      }
      else {
        cVar1 = *(char *)(param_1 + 0x30a);
        if (cVar1 == '\0') {
          if (((*(uint *)(param_1 + 0x5b8) & 0x20) == 0) && (*(char *)(param_1 + 0x30f) < '\x01')) {
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x20;
            *(undefined1 *)(param_1 + 0x30f) = 0x1e;
          }
        }
        else if ((((-1 < cVar1) && (cVar1 < '\x03')) && ((*(uint *)(param_1 + 0x5b8) & 0x10) == 0))
                && (*(char *)(param_1 + 0x30f) < '\x01')) {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x10;
          *(undefined1 *)(param_1 + 0x30f) = 0x1e;
        }
      }
    }
    else if (*(int *)(param_1 + 0x508) == *(int *)(param_1 + 0x300)) {
      if ((*(char *)(param_1 + 0x30a) == '\x01') || (*(char *)(param_1 + 0x30a) == '\x02')) {
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x10;
        *(undefined1 *)(param_1 + 0x30f) = 0x1e;
      }
    }
    else {
      cVar1 = *(char *)(param_1 + 0x30a);
      if (cVar1 == '\0') {
        if (((*(uint *)(param_1 + 0x5b8) & 0x20) == 0) && (*(char *)(param_1 + 0x30f) < '\x01')) {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x20;
          *(undefined1 *)(param_1 + 0x30f) = 0x1e;
        }
      }
      else if ((((-1 < cVar1) && (cVar1 < '\x03')) && ((*(uint *)(param_1 + 0x5b8) & 0x10) == 0)) &&
              (*(char *)(param_1 + 0x30f) < '\x01')) {
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x10;
        *(undefined1 *)(param_1 + 0x30f) = 0x1e;
      }
    }
  }
  return;
}



// ==== 80025cfc  zz_0025cfc_ ====

undefined4 zz_0025cfc_(char *param_1)

{
  if (param_1 == (char *)0x0) {
    return 0;
  }
  if (param_1[0x83] != '\0') {
    return 1;
  }
  if ((((*param_1 != '\0') && (param_1[0x18] == '\x01')) &&
      ((*(uint *)(param_1 + 0x5e0) & 0x80000000) == 0)) &&
     (((*(float *)(param_1 + 0x720) <= FLOAT_80436dfc && ((*(ushort *)(param_1 + 0x272) & 2) == 0))
      && (*(short *)(param_1 + 1000) != 0xf07)))) {
    return 1;
  }
  return 0;
}



// ==== 80025d74  zz_0025d74_ ====

/* WARNING: Removing unreachable block (ram,0x80025f54) */
/* WARNING: Removing unreachable block (ram,0x80025d84) */

undefined4 zz_0025d74_(char *param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_44;
  float local_40;
  undefined4 local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  pcVar4 = DAT_803c4e84;
  if (param_2 == 0) {
    uVar1 = 1;
  }
  else if (param_1[0x4a0] == '\0') {
    dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_2 + 0x20),(float *)(param_1 + 0x20));
    iVar3 = 0;
    do {
      if ((((*pcVar4 != '\0') && (uVar2 = zz_0025a14_((int)param_1,param_2), uVar2 == 0)) &&
          (pcVar4 != param_1)) && ((*(uint *)(pcVar4 + 0x5e0) & 0x1000000) == 0)) {
        dVar6 = gnt4_PSVECSquareDistance_bl((float *)(pcVar4 + 0x20),(float *)(param_2 + 0x20));
        if ((double)FLOAT_80436dfc < dVar6) {
          dVar7 = 1.0 / SQRT(dVar6);
          dVar7 = DOUBLE_80436e00 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80436e08);
          dVar7 = DOUBLE_80436e00 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80436e08);
          dVar6 = (double)(float)(dVar6 * DOUBLE_80436e00 * dVar7 *
                                          -(dVar6 * dVar7 * dVar7 - DOUBLE_80436e08));
        }
        if ((dVar6 <= (double)FLOAT_80436e9c) &&
           (dVar6 = gnt4_PSVECSquareDistance_bl((float *)(pcVar4 + 0x20),(float *)(param_1 + 0x20)),
           dVar6 < dVar5)) {
          return 1;
        }
      }
      iVar3 = iVar3 + 1;
      pcVar4 = pcVar4 + 0x1e00;
    } while (iVar3 < 6);
    local_44 = *(float *)(param_1 + 0x20);
    local_3c = *(undefined4 *)(param_1 + 0x28);
    local_40 = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x66c);
    local_38 = *(float *)(param_1 + 0x50c);
    local_34 = *(undefined4 *)(param_1 + 0x510);
    local_30 = *(undefined4 *)(param_1 + 0x514);
    if ((param_1[0x30a] == '\x01') || (param_1[0x30a] == '\x02')) {
      iVar3 = FUN_800372e4((int)param_1,&local_44,&local_38,1);
      if (iVar3 != 0) {
        return 1;
      }
    }
    else {
      iVar3 = FUN_800372e4((int)param_1,&local_44,&local_38,0);
      if (iVar3 != 0) {
        return 1;
      }
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80025f7c  FUN_80025f7c ====

/* WARNING: Removing unreachable block (ram,0x80026030) */
/* WARNING: Removing unreachable block (ram,0x80025f8c) */

void FUN_80025f7c(int param_1)

{
  short sVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  
  iVar2 = *(int *)(param_1 + 0x300);
  if (iVar2 != 0) {
    iVar2 = FUN_800452a0((double)(*(float *)(iVar2 + 0x20) - *(float *)(param_1 + 0x20)),
                         (double)(*(float *)(iVar2 + 0x28) - *(float *)(param_1 + 0x28)));
    sVar1 = (short)iVar2 - *(short *)(param_1 + 0x5b0);
    dVar3 = zz_0045204_(sVar1);
    dVar4 = zz_0045238_(sVar1);
    dVar3 = dVar3 * (double)FLOAT_80436e60;
    dVar4 = -dVar4 * (double)FLOAT_80436e60;
    *(char *)(param_1 + 0x337) = (char)(int)dVar3;
    *(char *)(param_1 + 0x338) = (char)(int)dVar4;
    zz_0024d1c_((double)(float)dVar3,(double)(float)dVar4,param_1,1);
  }
  return;
}



// ==== 80026050  zz_0026050_ ====

undefined4 zz_0026050_(char *param_1)

{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  if ((param_1[0x339] & 0x40U) != 0) {
    return 0;
  }
  if ((((param_1[0x364] == '\0') && (param_1[0x6fc] == '\0')) && (param_1[0x4a0] == '\0')) &&
     (param_1[0x4a1] == '\0')) {
    iVar3 = 0;
    iVar4 = 3;
    while (((pcVar1 = *(char **)((int)&DAT_803c6dec + iVar3 + param_1[0x88] * 0x18),
            pcVar1 != (char *)0x0 && (*pcVar1 != '\0')) && (pcVar1[0x18] == '\x01'))) {
      if ((pcVar1 != param_1) && ((pcVar1[0x6fb] != '\0' || (pcVar1[0x4a1] != '\0')))) {
        *(char **)(param_1 + 0x360) = pcVar1;
        param_1[0x364] = '\x01';
        param_1[0x365] = '\0';
        return 1;
      }
      pcVar1 = *(char **)((int)&DAT_803c6df0 + param_1[0x88] * 0x18 + iVar3);
      if (((pcVar1 == (char *)0x0) || (*pcVar1 == '\0')) || (pcVar1[0x18] != '\x01')) break;
      if ((pcVar1 != param_1) && ((pcVar1[0x6fb] != '\0' || (pcVar1[0x4a1] != '\0')))) {
        *(char **)(param_1 + 0x360) = pcVar1;
        param_1[0x364] = '\x01';
        param_1[0x365] = '\0';
        return 1;
      }
      iVar3 = iVar3 + 8;
      iVar4 = iVar4 + -1;
      if (iVar4 == 0) break;
    }
    iVar3 = (int)param_1[0x88];
    if ((PTR_DAT_80433934[iVar3 * 0x3c + 0xf6] == '\0') &&
       (PTR_DAT_80433934[iVar3 * 0x3c + 0x103] != '\0')) {
      puVar2 = &DAT_803c6dec + iVar3 * 6;
      iVar3 = 6;
      do {
        pcVar1 = (char *)*puVar2;
        if (pcVar1 == (char *)0x0) {
          return 0;
        }
        if (*pcVar1 == '\0') {
          return 0;
        }
        if (pcVar1[0x18] != '\x01') {
          return 0;
        }
        if ((pcVar1 != param_1) && (pcVar1[0x3e6] != '\0')) {
          *(char **)(param_1 + 0x360) = pcVar1;
          param_1[0x364] = '\x01';
          param_1[0x365] = '\0';
          *(char **)(pcVar1 + 0x360) = param_1;
          pcVar1[0x364] = '\x01';
          pcVar1[0x365] = '\0';
          return 1;
        }
        puVar2 = puVar2 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  return 0;
}



// ==== 80026250  zz_00262b4_ ====

void zz_00262b4_(int param_1)

{
  char cVar1;
  char *pcVar2;
  
  if (*(int *)(param_1 + 0x360) == 0) {
    *(undefined1 *)(param_1 + 0x364) = 0;
  }
  pcVar2 = *(char **)(param_1 + 0x360);
  if ((*pcVar2 == '\0') || (pcVar2[0x18] != '\x01')) {
    *(undefined1 *)(param_1 + 0x364) = 0;
  }
  cVar1 = *(char *)(param_1 + 0x364);
  if (cVar1 == '\x01') {
    *(undefined1 *)(param_1 + 0x364) = 2;
    return;
  }
  if (cVar1 < '\x01') {
    return;
  }
  if (cVar1 < '\x03') {
    cVar1 = *(char *)(param_1 + 0x365);
    if (cVar1 == '\x01') {
      if ((pcVar2[0x6fb] == '\0') && (pcVar2[0x4a1] == '\0')) {
        *(undefined1 *)(param_1 + 0x364) = 0;
        *(undefined1 *)(param_1 + 0x365) = 0;
      }
    }
    else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
            ((pcVar2[0x6fb] != '\0' || (pcVar2[0x4a1] != '\0')))) {
      *(undefined1 *)(param_1 + 0x365) = 1;
    }
    if (((*(char *)(param_1 + 0x6fc) == '\0') && (*(char *)(param_1 + 0x4a0) == '\0')) &&
       (*(char *)(param_1 + 0x4a1) == '\0')) {
      if ((*(uint *)(param_1 + 0x5b8) & 0x800) == 0) {
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x800;
        return;
      }
      return;
    }
    *(undefined1 *)(param_1 + 0x364) = 0;
    return;
  }
  return;
}



// ==== 80026368  zz_0026368_ ====

undefined4 zz_0026368_(void)

{
  return 0;
}



// ==== 80026370  zz_0026370_ ====

int zz_0026370_(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  if ((*(char *)(param_1 + 0x661) == '\0') || (*(char *)(param_1 + 0x661) == '\x01')) {
    if (*(char *)(param_1 + 0x7cd) == '\x01') {
      uVar1 = zz_00055fc_();
      iVar2 = (int)(char)(&DAT_802cfae4)[uVar1 & 0xf];
    }
    else {
      uVar1 = zz_00055fc_();
      iVar2 = (int)(char)(&DAT_802cfad4)[uVar1 & 0xf];
    }
  }
  return iVar2;
}



// ==== 800263ec  FUN_800263ec ====

void FUN_800263ec(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 != 0xd07) {
    if (sVar1 < 0xd07) {
      if (sVar1 == 0xd01) {
        *(float *)(param_1 + 0x36c) = FLOAT_80436ea8;
        return;
      }
      if (sVar1 < 0xd01) {
        if (sVar1 < 0xd00) {
          return;
        }
        *(float *)(param_1 + 0x36c) = FLOAT_80436e28;
        return;
      }
      if (sVar1 < 0xd04) {
        return;
      }
      *(float *)(param_1 + 0x36c) = FLOAT_80436e28;
      return;
    }
    if (sVar1 != 0xf00) {
      return;
    }
  }
  *(float *)(param_1 + 0x36c) = FLOAT_80436e20;
  return;
}



// ==== 8002645c  FUN_8002645c ====

/* WARNING: Removing unreachable block (ram,0x8002760c) */
/* WARNING: Removing unreachable block (ram,0x8002646c) */

void FUN_8002645c(int param_1)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  short sVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  float local_58;
  float local_54;
  undefined4 local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  float afStack_40 [4];
  undefined4 local_30;
  uint uStack_2c;
  
  sVar6 = *(short *)(param_1 + 1000);
  if (sVar6 == 0x620) {
LAB_8002714c:
    FUN_80027634((double)FLOAT_80436eb8,param_1);
    return;
  }
  if (sVar6 < 0x620) {
    if (sVar6 == 0x505) {
      FUN_80027634((double)FLOAT_80436e28,param_1);
      return;
    }
    if (sVar6 < 0x505) {
      if (sVar6 != 0x203) {
        if (0x202 < sVar6) {
          if (sVar6 == 0x302) {
            if (*(short *)(param_1 + 0x784) < 1) {
              return;
            }
            if (*(char *)(param_1 + 0x146) != '\0') {
              return;
            }
            if ((*(uint *)(param_1 + 0x5b8) & 0x400) != 0) {
              return;
            }
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
            return;
          }
          if (sVar6 < 0x302) {
            if (sVar6 == 0x205) {
              cVar1 = *(char *)(param_1 + 0x366);
              if (cVar1 == '\x01') {
                if (*(short *)(param_1 + 0x368) == 0) {
                  *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
                  *(undefined1 *)(param_1 + 0x366) = 0;
                  return;
                }
                *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
                return;
              }
              if ('\0' < cVar1) {
                return;
              }
              if (cVar1 < '\0') {
                return;
              }
              *(undefined1 *)(param_1 + 0x366) = 1;
              uVar4 = zz_00055fc_();
              *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x7f) + 300;
              return;
            }
            if (sVar6 < 0x205) {
              return;
            }
            if (sVar6 < 0x301) {
              return;
            }
            cVar1 = *(char *)(param_1 + 0x366);
            if (cVar1 == '\x01') {
              if (*(short *)(param_1 + 0x368) != 0) {
                *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
                return;
              }
              *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
              uVar4 = zz_00055fc_();
              if ((uVar4 & 3) == 0) {
                *(undefined1 *)(param_1 + 0x366) = 2;
                *(undefined2 *)(param_1 + 0x368) = 5;
                return;
              }
              *(undefined1 *)(param_1 + 0x366) = 0;
              return;
            }
            if (cVar1 < '\x01') {
              if (cVar1 < '\0') {
                return;
              }
              *(undefined1 *)(param_1 + 0x366) = 1;
              uVar4 = zz_00055fc_();
              *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0x3c;
              return;
            }
            if ('\x02' < cVar1) {
              return;
            }
            if (*(short *)(param_1 + 0x368) == 0) {
              *(undefined1 *)(param_1 + 0x366) = 0;
              *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
              return;
            }
            *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
            return;
          }
          if (sVar6 != 0x501) {
            if (0x500 < sVar6) {
              return;
            }
            if (sVar6 != 0x404) {
              return;
            }
            *(undefined1 *)(param_1 + 0x37e) = 1;
            return;
          }
          goto LAB_80026f28;
        }
        if (sVar6 == 0x106) {
          cVar1 = *(char *)(param_1 + 0x366);
          if (cVar1 == '\x01') {
            if (*(short *)(param_1 + 0x368) == 0) {
              *(undefined1 *)(param_1 + 0x366) = 0;
              *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x200;
              return;
            }
            *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
            return;
          }
          if ('\0' < cVar1) {
            return;
          }
          if (cVar1 < '\0') {
            return;
          }
          *(undefined1 *)(param_1 + 0x366) = 1;
          uVar4 = zz_00055fc_();
          *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0x3c;
          return;
        }
        if (0x105 < sVar6) {
          if (sVar6 == 0x201) {
            bVar2 = *(byte *)(param_1 + 0x71e);
            if (bVar2 == 0) {
              return;
            }
            bVar3 = false;
            iVar7 = 0;
            if ((bVar2 & 1) == 0) {
              iVar7 = 1;
              if ((bVar2 & 2) == 0) {
                iVar7 = 2;
                if ((bVar2 & 4) == 0) {
                  iVar7 = 3;
                  if ((bVar2 & 8) == 0) {
                    iVar7 = 4;
                    if ((bVar2 & 0x10) == 0) {
                      iVar7 = 5;
                      if ((bVar2 & 0x20) == 0) {
                        iVar7 = 6;
                      }
                      else {
                        bVar3 = true;
                      }
                    }
                    else {
                      bVar3 = true;
                    }
                  }
                  else {
                    bVar3 = true;
                  }
                }
                else {
                  bVar3 = true;
                }
              }
              else {
                bVar3 = true;
              }
            }
            else {
              bVar3 = true;
            }
            if (!bVar3) {
              return;
            }
            if (*(char *)(param_1 + 0x88) == *(char *)((&DAT_803c4e84)[iVar7] + 0x88)) {
              if ((*(uint *)(param_1 + 0x5b8) & 0x400) != 0) {
                return;
              }
              *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
              return;
            }
            zz_002337c_(param_1);
            zz_002330c_(param_1);
            if ((*(uint *)((&DAT_803c4e84)[iVar7] + 0x5e0) & 0x1000000) == 0) {
              return;
            }
            if ((*(uint *)((&DAT_803c4e84)[iVar7] + 0x5e0) & 0x2000000) == 0) {
              return;
            }
            if ((*(uint *)(param_1 + 0x5b8) & 0x400) != 0) {
              return;
            }
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
            return;
          }
          if (0x200 < sVar6) {
            return;
          }
          if (0x107 < sVar6) {
            return;
          }
          cVar1 = *(char *)(param_1 + 0x366);
          if (cVar1 != '\x02') {
            if (cVar1 < '\x02') {
              if (cVar1 == '\0') {
                *(undefined1 *)(param_1 + 0x366) = 1;
                uVar4 = zz_00055fc_();
                *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0x3c;
                return;
              }
              if (cVar1 < '\0') {
                return;
              }
              dVar9 = (double)FLOAT_80436eac;
              iVar5 = 0;
              iVar7 = DAT_803c4e84;
              while ((*(char *)(param_1 + 0x88) == *(char *)(iVar7 + 0x88) ||
                     (dVar8 = gnt4_PSVECSquareDistance_bl
                                        ((float *)(param_1 + 0x20),(float *)(iVar7 + 0x20)),
                     dVar9 < dVar8))) {
                iVar5 = iVar5 + 1;
                iVar7 = iVar7 + 0x1e00;
                if (5 < iVar5) {
                  return;
                }
              }
              *(undefined1 *)(param_1 + 0x366) = 2;
              *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x200;
              *(undefined4 *)(param_1 + 0x380) = *(undefined4 *)(param_1 + 0x20);
              *(undefined4 *)(param_1 + 900) = *(undefined4 *)(param_1 + 0x24);
              *(undefined4 *)(param_1 + 0x388) = *(undefined4 *)(param_1 + 0x28);
              *(undefined2 *)(param_1 + 0x368) = 0xb4;
              return;
            }
            if (cVar1 == '\x04') {
              if (*(short *)(param_1 + 0x78e) == *(short *)(param_1 + 0x774)) {
                *(undefined1 *)(param_1 + 0x366) = 0;
                return;
              }
              if ((*(uint *)(param_1 + 0x5b8) & 0x400) != 0) {
                return;
              }
              *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
              return;
            }
            if ('\x03' < cVar1) {
              return;
            }
            dVar9 = (double)FLOAT_80436eb4;
            iVar5 = 0;
            iVar7 = DAT_803c4e84;
            do {
              if ((*(char *)(param_1 + 0x88) != *(char *)(iVar7 + 0x88)) &&
                 (dVar8 = gnt4_PSVECSquareDistance_bl
                                    ((float *)(param_1 + 0x20),(float *)(iVar7 + 0x20)),
                 dVar8 <= dVar9)) {
                *(undefined1 *)(param_1 + 0x366) = 4;
              }
              iVar5 = iVar5 + 1;
              iVar7 = iVar7 + 0x1e00;
            } while (iVar5 < 6);
            *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
            if (0 < *(short *)(param_1 + 0x368)) {
              return;
            }
            *(undefined1 *)(param_1 + 0x366) = 4;
            return;
          }
          *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
          if ((*(short *)(param_1 + 0x774) < 1) || (*(short *)(param_1 + 0x368) < 1)) {
            *(undefined1 *)(param_1 + 0x366) = 3;
            uVar4 = zz_00055fc_();
            *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0x3c;
            return;
          }
          dVar9 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x380));
          if (dVar9 <= (double)FLOAT_80436eb0) {
            return;
          }
          if ((*(uint *)(param_1 + 0x5b8) & 0x200) != 0) {
            return;
          }
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x200;
          *(undefined4 *)(param_1 + 0x380) = *(undefined4 *)(param_1 + 0x20);
          *(undefined4 *)(param_1 + 900) = *(undefined4 *)(param_1 + 0x24);
          *(undefined4 *)(param_1 + 0x388) = *(undefined4 *)(param_1 + 0x28);
          return;
        }
        if (sVar6 != 4) {
          if (3 < sVar6) {
            if (sVar6 != 0x103) {
              return;
            }
            cVar1 = *(char *)(param_1 + 0x366);
            if (cVar1 == '\x01') {
              if (*(short *)(param_1 + 0x368) == 0) {
                *(undefined1 *)(param_1 + 0x366) = 0;
                *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
                return;
              }
              *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
              return;
            }
            if ('\0' < cVar1) {
              return;
            }
            if (cVar1 < '\0') {
              return;
            }
            *(undefined1 *)(param_1 + 0x366) = 1;
            uVar4 = zz_00055fc_();
            *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0x3c;
            return;
          }
          if (sVar6 < 3) {
            return;
          }
          cVar1 = *(char *)(param_1 + 0x366);
          if (cVar1 == '\x02') {
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
            if ((*(byte *)(param_1 + 0x655) & 4) == 0) {
              return;
            }
            *(undefined1 *)(param_1 + 0x366) = 3;
            return;
          }
          if (cVar1 < '\x02') {
            if (cVar1 == '\0') {
              if (*(char *)(param_1 + 0x7c8) != '\0') {
                return;
              }
              *(undefined1 *)(param_1 + 0x366) = 1;
              uVar4 = zz_00055fc_();
              *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x1f) + 0x1e;
              return;
            }
            if (cVar1 < '\0') {
              return;
            }
            if (*(short *)(param_1 + 0x368) == 0) {
              *(undefined1 *)(param_1 + 0x366) = 2;
              return;
            }
            *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
            return;
          }
          if ('\x03' < cVar1) {
            return;
          }
          if (*(char *)(param_1 + 0x7c8) == '\0') {
            return;
          }
          *(undefined1 *)(param_1 + 0x366) = 0;
          return;
        }
      }
      cVar1 = *(char *)(param_1 + 0x366);
      if (cVar1 == '\x01') {
        if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
          *(undefined1 *)(param_1 + 0x366) = 0;
          *(undefined1 *)(param_1 + 0x38d) = 0;
          return;
        }
        *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
        if (*(short *)(param_1 + 0x368) < 1) {
          if ((*(uint *)(param_1 + 0x5b8) & 0x400) != 0) {
            return;
          }
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
          return;
        }
        if (*(short *)(param_1 + 1000) != 4) {
          return;
        }
        if (*(int *)(param_1 + 0x300) != 0) {
          iVar7 = zz_0027704_(param_1,(float *)(*(int *)(param_1 + 0x300) + 0x20));
          sVar6 = (short)iVar7;
          if ((sVar6 < 0) || (sVar6 < 0x4000)) {
            if (0 < sVar6) {
              return;
            }
            if (-0x4000 < sVar6) {
              return;
            }
          }
          if ((*(uint *)(param_1 + 0x5b8) & 0x400) != 0) {
            return;
          }
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
          return;
        }
        if ((*(uint *)(param_1 + 0x5b8) & 0x400) != 0) {
          return;
        }
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
        return;
      }
      if ('\0' < cVar1) {
        return;
      }
      if (cVar1 < '\0') {
        return;
      }
      iVar7 = *(int *)(param_1 + 0x300);
      if (iVar7 == 0) {
        return;
      }
      local_58 = *(float *)(param_1 + 0x20);
      local_50 = *(undefined4 *)(param_1 + 0x28);
      local_4c = *(float *)(iVar7 + 0x20);
      local_44 = *(undefined4 *)(iVar7 + 0x28);
      local_54 = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x66c);
      local_48 = *(float *)(iVar7 + 0x24) + *(float *)(param_1 + 0x66c);
      iVar5 = zz_003f044_(&local_58,&local_4c,afStack_40);
      if (iVar5 != 0) {
        return;
      }
      iVar5 = zz_0027704_(param_1,(float *)(iVar7 + 0x20));
      sVar6 = (short)iVar5;
      if ((sVar6 < 0) || (0xe00 < sVar6)) {
        if (0 < sVar6) {
          return;
        }
        if (sVar6 < -0xe00) {
          return;
        }
      }
      if ((*(uint *)(param_1 + 0x5e0) & 3) != 0) {
        return;
      }
      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
      *(undefined1 *)(param_1 + 0x366) = 1;
      *(undefined2 *)(param_1 + 0x368) = 900;
      *(undefined1 *)(param_1 + 0x38d) = 2;
      zz_0024824_(param_1);
      *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(iVar7 + 0x20);
      *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(iVar7 + 0x28);
      *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(iVar7 + 0x24);
      FUN_800241c0(param_1,iVar7);
      return;
    }
    if (sVar6 == 0x60c) {
      return;
    }
    if (sVar6 < 0x60c) {
      if (sVar6 == 0x603) {
        return;
      }
      if (sVar6 < 0x603) {
        if (sVar6 == 0x511) {
          FUN_80027634((double)FLOAT_80436e20,param_1);
          return;
        }
        if (0x510 < sVar6) {
          return;
        }
        if (sVar6 != 0x50d) {
          return;
        }
LAB_80026f28:
        cVar1 = *(char *)(param_1 + 0x366);
        if (cVar1 == '\x01') {
          if (*(short *)(param_1 + 0x368) == 0) {
            *(undefined1 *)(param_1 + 0x366) = 0;
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
            return;
          }
          *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
          return;
        }
        if ('\0' < cVar1) {
          return;
        }
        if (cVar1 < '\0') {
          return;
        }
        *(undefined1 *)(param_1 + 0x366) = 1;
        uVar4 = zz_00055fc_();
        *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0x78;
        return;
      }
      if (sVar6 != 0x607) {
        if (0x606 < sVar6) {
          return;
        }
        goto LAB_80026fac;
      }
    }
    else if (sVar6 != 0x612) {
      if (sVar6 < 0x612) {
        if (sVar6 == 0x60f) {
          return;
        }
        if (sVar6 < 0x60f) {
          return;
        }
      }
      else {
        if (sVar6 == 0x61b) goto LAB_8002714c;
        if (0x61a < sVar6) {
          return;
        }
        if (0x614 < sVar6) {
          return;
        }
      }
      goto LAB_80026fac;
    }
    goto LAB_80027030;
  }
  if (sVar6 == 0xa05) {
LAB_80027294:
    cVar1 = *(char *)(param_1 + 0x366);
    if (cVar1 == '\x01') {
      if (*(short *)(param_1 + 0x368) == 0) {
        *(undefined1 *)(param_1 + 0x366) = 0;
        return;
      }
      *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
      return;
    }
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(undefined1 *)(param_1 + 0x366) = 1;
    uVar4 = zz_00055fc_();
    *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0xf0;
    uVar4 = zz_00055fc_();
    dVar9 = DOUBLE_80436e18;
    *(float *)(param_1 + 0x36c) = FLOAT_80436e20;
    *(float *)(param_1 + 0x36c) =
         *(float *)(param_1 + 0x36c) +
         (float)((double)CONCAT44(0x43300000,(uVar4 & 3) * 100 ^ 0x80000000) - dVar9);
    return;
  }
  if (0xa04 < sVar6) {
    if (sVar6 != 0xd00) {
      if (sVar6 < 0xd00) {
        if (sVar6 == 0xb06) {
          return;
        }
        if (sVar6 < 0xb06) {
          if (sVar6 == 0xb00) {
            cVar1 = *(char *)(param_1 + 0x366);
            if (cVar1 == '\x01') {
              if (*(short *)(param_1 + 0x368) == 0) {
                *(undefined1 *)(param_1 + 0x366) = 0;
              }
              else {
                *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
              }
            }
            else if ((cVar1 < '\x01') && (-1 < cVar1)) {
              *(undefined1 *)(param_1 + 0x366) = 1;
              uVar4 = zz_00055fc_();
              *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0xf0;
              uVar4 = zz_00055fc_();
              dVar9 = DOUBLE_80436e18;
              local_30 = 0x43300000;
              uStack_2c = (uVar4 & 3) * 100 ^ 0x80000000;
              *(float *)(param_1 + 0x36c) = FLOAT_80436e28;
              *(float *)(param_1 + 0x36c) =
                   *(float *)(param_1 + 0x36c) +
                   (float)((double)CONCAT44(0x43300000,uStack_2c) - dVar9);
            }
            cVar1 = *(char *)(param_1 + 0x367);
            if (cVar1 == '\x01') {
              if (*(short *)(param_1 + 0x36a) == 0) {
                *(undefined1 *)(param_1 + 0x367) = 0;
                *(byte *)(param_1 + 0x37e) = *(byte *)(param_1 + 0x37e) ^ 1;
                return;
              }
              *(short *)(param_1 + 0x36a) = *(short *)(param_1 + 0x36a) + -1;
              return;
            }
            if ('\0' < cVar1) {
              return;
            }
            if (cVar1 < '\0') {
              return;
            }
            *(undefined1 *)(param_1 + 0x367) = 1;
            uVar4 = zz_00055fc_();
            *(ushort *)(param_1 + 0x36a) = ((ushort)uVar4 & 0x3f) + 300;
            return;
          }
          if (sVar6 < 0xb00) {
            if (sVar6 != 0xa0a) {
              if (0xa09 < sVar6) {
                return;
              }
              goto LAB_800271f8;
            }
            goto LAB_80027294;
          }
        }
        else {
          if (sVar6 == 0xc04) {
            cVar1 = *(char *)(param_1 + 0x366);
            if (cVar1 == '\x01') {
              *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
              if (*(int *)(param_1 + 0x300) == 0) {
                return;
              }
              uVar4 = zz_006ab9c_(param_1);
              if (uVar4 == 0) {
                return;
              }
              iVar7 = zz_0027704_(param_1,(float *)(*(int *)(param_1 + 0x300) + 0x20));
              sVar6 = (short)iVar7;
              if ((sVar6 < 0) || (0xc00 < sVar6)) {
                if (0 < sVar6) {
                  return;
                }
                if (sVar6 < -0xc00) {
                  return;
                }
              }
              *(undefined1 *)(param_1 + 0x366) = 2;
              return;
            }
            if ('\0' < cVar1) {
              if ('\x02' < cVar1) {
                return;
              }
              *(undefined1 *)(param_1 + 0x366) = 0;
              return;
            }
            if (cVar1 < '\0') {
              return;
            }
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
            if ((*(byte *)(param_1 + 0x655) & 4) == 0) {
              return;
            }
            *(undefined1 *)(param_1 + 0x366) = 1;
            return;
          }
          if (0xc03 < sVar6) {
            return;
          }
          if (0xb07 < sVar6) {
            return;
          }
        }
        cVar1 = *(char *)(param_1 + 0x366);
        if (cVar1 == '\x01') {
          if (*(short *)(param_1 + 0x368) == 0) {
            *(undefined1 *)(param_1 + 0x366) = 0;
            return;
          }
          *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
          return;
        }
        if ('\0' < cVar1) {
          return;
        }
        if (cVar1 < '\0') {
          return;
        }
        *(undefined1 *)(param_1 + 0x366) = 1;
        uVar4 = zz_00055fc_();
        *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0xf0;
        uVar4 = zz_00055fc_();
        dVar9 = DOUBLE_80436e18;
        *(float *)(param_1 + 0x36c) = FLOAT_80436e28;
        *(float *)(param_1 + 0x36c) =
             *(float *)(param_1 + 0x36c) +
             (float)((double)CONCAT44(0x43300000,(uVar4 & 3) * 100 ^ 0x80000000) - dVar9);
        return;
      }
      if (sVar6 != 0xd05) {
        if (0xd04 < sVar6) {
          if (sVar6 == 0xf00) {
            FUN_80027634((double)FLOAT_80436e20,param_1);
            return;
          }
          if (0xeff < sVar6) {
            return;
          }
          if (0xd07 < sVar6) {
            return;
          }
          if (*(int *)(param_1 + 0x300) == 0) {
            return;
          }
          *(float *)(param_1 + 0x36c) =
               FLOAT_80436ec4 + *(float *)(*(int *)(param_1 + 0x300) + 0x24);
          return;
        }
        if (sVar6 == 0xd03) {
          FUN_80027634((double)FLOAT_80436ebc,param_1);
          return;
        }
        if (0xd02 < sVar6) goto LAB_80027594;
        if (0xd01 < sVar6) {
          if (*(char *)(param_1 + 0x71e) != '\0') {
            FUN_80027634((double)FLOAT_80436e40,param_1);
            return;
          }
          FUN_80027634((double)FLOAT_80436ec0,param_1);
          return;
        }
      }
      FUN_80027634((double)FLOAT_80436ebc,param_1);
      return;
    }
LAB_80027594:
    FUN_80027634((double)FLOAT_80436eb8,param_1);
    return;
  }
  if (sVar6 == 0x809) {
    *(undefined1 *)(param_1 + 0x38d) = 1;
    return;
  }
  if (0x808 < sVar6) {
    if (sVar6 != 0x902) {
      if (sVar6 < 0x902) {
        if (sVar6 == 0x80c) goto LAB_80027184;
        if (0x80b < sVar6) {
          if (0x80e < sVar6) {
            return;
          }
          goto LAB_800271ac;
        }
        if (0x80a < sVar6) {
          return;
        }
        goto LAB_8002715c;
      }
      if (sVar6 != 0x909) {
        if (sVar6 < 0x909) {
          return;
        }
        if (sVar6 < 0xa00) {
          return;
        }
LAB_800271f8:
        cVar1 = *(char *)(param_1 + 0x366);
        if (cVar1 == '\x01') {
          if (*(short *)(param_1 + 0x368) == 0) {
            *(undefined1 *)(param_1 + 0x366) = 0;
            return;
          }
          *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
          return;
        }
        if ('\0' < cVar1) {
          return;
        }
        if (cVar1 < '\0') {
          return;
        }
        *(undefined1 *)(param_1 + 0x366) = 1;
        uVar4 = zz_00055fc_();
        *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0xf0;
        uVar4 = zz_00055fc_();
        dVar9 = DOUBLE_80436e18;
        *(float *)(param_1 + 0x36c) = FLOAT_80436e28;
        *(float *)(param_1 + 0x36c) =
             *(float *)(param_1 + 0x36c) +
             (float)((double)CONCAT44(0x43300000,(uVar4 & 3) * 100 ^ 0x80000000) - dVar9);
        return;
      }
    }
    *(undefined1 *)(param_1 + 0x37e) = 1;
    return;
  }
  if (sVar6 == 0x802) {
LAB_8002715c:
    if (*(short *)(param_1 + 0x784) < 1) {
      return;
    }
    if ((*(uint *)(param_1 + 0x5b8) & 0x400) != 0) {
      return;
    }
    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
    return;
  }
  if (0x801 < sVar6) {
    if (sVar6 == 0x805) {
LAB_800271ac:
      if (*(short *)(param_1 + 0x784) < 1) {
        return;
      }
      if (*(char *)(param_1 + 0x6f4) != '\0') {
        return;
      }
      if ((*(uint *)(param_1 + 0x5b8) & 0x400) != 0) {
        return;
      }
      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
      return;
    }
    if (0x804 < sVar6) {
      return;
    }
    if (sVar6 < 0x804) {
      return;
    }
LAB_80027184:
    if (*(short *)(param_1 + 0x784) < 1) {
      return;
    }
    if ((*(uint *)(param_1 + 0x5b8) & 0x400) != 0) {
      return;
    }
    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
    return;
  }
  if (sVar6 == 0x625) {
LAB_80026fac:
    cVar1 = *(char *)(param_1 + 0x366);
    if (cVar1 == '\x01') {
      if (*(short *)(param_1 + 0x368) == 0) {
        if (((*(uint *)(param_1 + 0x5e0) & 3) == 0) && ((*(uint *)(param_1 + 0x5b8) & 0x400) == 0))
        {
          *(undefined1 *)(param_1 + 0x366) = 0;
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
        }
      }
      else {
        *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
      }
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      *(undefined1 *)(param_1 + 0x366) = 1;
      uVar4 = zz_00055fc_();
      *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0xf0;
    }
  }
  else {
    if (sVar6 < 0x625) {
      if (sVar6 < 0x624) goto LAB_80026fac;
    }
    else if (0x626 < sVar6) {
      return;
    }
LAB_80027030:
    cVar1 = *(char *)(param_1 + 0x366);
    if (cVar1 == '\x01') {
      if (*(short *)(param_1 + 0x368) == 0) {
        if (((*(uint *)(param_1 + 0x5e0) & 3) == 0) && ((*(uint *)(param_1 + 0x5b8) & 0x400) == 0))
        {
          *(undefined1 *)(param_1 + 0x366) = 0;
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
        }
      }
      else {
        *(short *)(param_1 + 0x368) = *(short *)(param_1 + 0x368) + -1;
      }
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      *(undefined1 *)(param_1 + 0x366) = 1;
      uVar4 = zz_00055fc_();
      *(ushort *)(param_1 + 0x368) = ((ushort)uVar4 & 0x3f) + 0xf0;
    }
    cVar1 = *(char *)(param_1 + 0x367);
    if (cVar1 == '\x01') {
      if (*(short *)(param_1 + 0x36a) == 0) {
        *(undefined1 *)(param_1 + 0x367) = 0;
      }
      else {
        *(short *)(param_1 + 0x36a) = *(short *)(param_1 + 0x36a) + -1;
      }
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      *(undefined1 *)(param_1 + 0x367) = 1;
      uVar4 = zz_00055fc_();
      *(ushort *)(param_1 + 0x36a) = ((ushort)uVar4 & 0x3f) + 0x78;
      uVar4 = zz_00055fc_();
      dVar9 = DOUBLE_80436e18;
      *(float *)(param_1 + 0x36c) = FLOAT_80436eb8;
      *(float *)(param_1 + 0x36c) =
           *(float *)(param_1 + 0x36c) +
           (float)((double)CONCAT44(0x43300000,(uVar4 & 3) * 100 ^ 0x80000000) - dVar9);
    }
  }
  return;
}



// ==== 80027634  FUN_80027634 ====

/* WARNING: Removing unreachable block (ram,0x800276e8) */
/* WARNING: Removing unreachable block (ram,0x80027644) */

void FUN_80027634(double param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = *(char *)(param_2 + 0x366);
  if (cVar1 == '\x01') {
    if (*(short *)(param_2 + 0x368) == 0) {
      *(undefined1 *)(param_2 + 0x366) = 0;
    }
    else {
      *(short *)(param_2 + 0x368) = *(short *)(param_2 + 0x368) + -1;
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(undefined1 *)(param_2 + 0x366) = 1;
    uVar2 = zz_00055fc_();
    *(ushort *)(param_2 + 0x368) = ((ushort)uVar2 & 0x3f) + 0xf0;
    *(float *)(param_2 + 0x36c) = (float)param_1;
    uVar2 = zz_00055fc_();
    *(float *)(param_2 + 0x36c) =
         *(float *)(param_2 + 0x36c) +
         (float)((double)CONCAT44(0x43300000,uVar2 & 3) - DOUBLE_80436ec8) * FLOAT_80436e44;
  }
  return;
}



// ==== 80027704  zz_0027704_ ====

int zz_0027704_(int param_1,float *param_2)

{
  int iVar1;
  
  iVar1 = FUN_800452a0((double)(*param_2 - *(float *)(param_1 + 0x20)),
                       (double)(param_2[2] - *(float *)(param_1 + 0x28)));
  return (int)(short)((short)iVar1 - *(short *)(param_1 + 0x72));
}



// ==== 80027760  zz_0027760_ ====

void zz_0027760_(void)

{
  return;
}



// ==== 80027764  zz_0027764_ ====

void zz_0027764_(void)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char cVar5;
  char cVar6;
  int iVar7;
  
  zz_00055fc_();
  cVar5 = '\0';
  cVar6 = '\0';
  *(undefined4 *)(PTR_DAT_80433934 + 300) = DAT_803c4e8c;
  pcVar2 = (char *)0x0;
  pcVar3 = (char *)0x0;
  *(undefined4 *)(PTR_DAT_80433934 + 0x168) = DAT_803c4e88;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1a4) = 0;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1e0) = 0;
  iVar7 = 3;
  pcVar4 = DAT_803c4e84;
  do {
    if (*pcVar4 != '\0') {
      pcVar4[0x335] = '\0';
      pcVar4[0x330] = '\0';
      pcVar4[0x331] = '\0';
      pcVar4[0x332] = '\0';
      pcVar4[0x333] = '\0';
      if (pcVar4[0x88] == '\0') {
        if (cVar5 <= pcVar4[0x334]) {
          pcVar2 = pcVar4;
          cVar5 = pcVar4[0x334];
        }
      }
      else if (pcVar4[0x88] == '\x01') {
        if (cVar6 <= pcVar4[0x334]) {
          pcVar3 = pcVar4;
          cVar6 = pcVar4[0x334];
        }
      }
    }
    pcVar1 = pcVar4 + 0x1e00;
    if (*pcVar1 != '\0') {
      pcVar4[0x2135] = '\0';
      pcVar4[0x2130] = '\0';
      pcVar4[0x2131] = '\0';
      pcVar4[0x2132] = '\0';
      pcVar4[0x2133] = '\0';
      if (pcVar4[0x1e88] == '\0') {
        if (cVar5 <= pcVar4[0x2134]) {
          pcVar2 = pcVar1;
          cVar5 = pcVar4[0x2134];
        }
      }
      else if (pcVar4[0x1e88] == '\x01') {
        if (cVar6 <= pcVar4[0x2134]) {
          pcVar3 = pcVar1;
          cVar6 = pcVar4[0x2134];
        }
      }
    }
    pcVar4 = pcVar4 + 0x3c00;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  if (pcVar2 != (char *)0x0) {
    pcVar2[0x335] = '\x01';
    pcVar4 = DAT_803c4e84;
    if (*DAT_803c4e84 != '\0') {
      if (DAT_803c4e84[0x88] == '\0') {
        *(char **)(DAT_803c4e84 + 0x330) = pcVar2;
      }
    }
    if (pcVar4[0x1e00] != '\0') {
      if (pcVar4[0x1e88] == '\0') {
        *(char **)(pcVar4 + 0x2130) = pcVar2;
      }
    }
    if (pcVar4[0x3c00] != '\0') {
      if (pcVar4[0x3c88] == '\0') {
        *(char **)(pcVar4 + 0x3f30) = pcVar2;
      }
    }
    if (pcVar4[0x5a00] != '\0') {
      if (pcVar4[0x5a88] == '\0') {
        *(char **)(pcVar4 + 0x5d30) = pcVar2;
      }
    }
    if (pcVar4[0x7800] != '\0') {
      if (pcVar4[0x7888] == '\0') {
        *(char **)(pcVar4 + 0x7b30) = pcVar2;
      }
    }
    if ((pcVar4[0x9600] != '\0') && (pcVar4[0x9688] == '\0')) {
      *(char **)(pcVar4 + 0x9930) = pcVar2;
    }
  }
  if (pcVar3 != (char *)0x0) {
    pcVar3[0x335] = '\x01';
    pcVar2 = DAT_803c4e84;
    if (*DAT_803c4e84 != '\0') {
      if (DAT_803c4e84[0x88] == '\x01') {
        *(char **)(DAT_803c4e84 + 0x330) = pcVar3;
      }
    }
    if (pcVar2[0x1e00] != '\0') {
      if (pcVar2[0x1e88] == '\x01') {
        *(char **)(pcVar2 + 0x2130) = pcVar3;
      }
    }
    if (pcVar2[0x3c00] != '\0') {
      if (pcVar2[0x3c88] == '\x01') {
        *(char **)(pcVar2 + 0x3f30) = pcVar3;
      }
    }
    if (pcVar2[0x5a00] != '\0') {
      if (pcVar2[0x5a88] == '\x01') {
        *(char **)(pcVar2 + 0x5d30) = pcVar3;
      }
    }
    if (pcVar2[0x7800] != '\0') {
      if (pcVar2[0x7888] == '\x01') {
        *(char **)(pcVar2 + 0x7b30) = pcVar3;
      }
    }
    if ((pcVar2[0x9600] != '\0') && (pcVar2[0x9688] == '\x01')) {
      *(char **)(pcVar2 + 0x9930) = pcVar3;
    }
  }
  return;
}



// ==== 80027a44  FUN_80027a44 ====

void FUN_80027a44(int param_1)

{
  if (*(char *)(param_1 + 0x3e6) == '\0') {
    *(undefined1 *)(param_1 + 0x334) = 0x20;
    return;
  }
  *(undefined *)(param_1 + 0x334) = (&DAT_802cfaa0)[*(char *)(param_1 + 0x438)];
  return;
}



// ==== 80027a78  zz_0027a78_ ====

void zz_0027a78_(void)

{
  DAT_8043610c = &DAT_803b02c8;
  gnt4_memset(&DAT_803b02c8,0,0xc);
  return;
}



// ==== 80027aac  zz_0027aac_ ====

void zz_0027aac_(undefined4 param_1,undefined2 param_2,undefined1 param_3)

{
  *DAT_8043610c = param_1;
  *(undefined2 *)(DAT_8043610c + 1) = param_2;
  *(undefined2 *)((int)DAT_8043610c + 6) = param_2;
  *(undefined1 *)(DAT_8043610c + 2) = 1;
  *(undefined1 *)((int)DAT_8043610c + 9) = param_3;
  return;
}



// ==== 80027adc  zz_0027adc_ ====

int zz_0027adc_(void)

{
  return (int)*(short *)(DAT_8043610c + 4);
}



// ==== 80027ae8  zz_0027ae8_ ====

void zz_0027ae8_(void)

{
  short sVar1;
  float fVar2;
  
  DAT_80436108 = 0;
  if (*(char *)(DAT_8043610c + 2) != '\0') {
    if (0 < *(short *)(DAT_8043610c + 1)) {
      *(short *)(DAT_8043610c + 1) = *(short *)(DAT_8043610c + 1) + -1;
    }
    sVar1 = *(short *)(DAT_8043610c + 1);
    if ((sVar1 == 0) && (*(char *)((int)DAT_8043610c + 9) == '\0')) {
      *(undefined1 *)(DAT_8043610c + 2) = 0;
      return;
    }
    if (*(char *)((int)DAT_8043610c + 9) == '\0') {
      fVar2 = (float)((double)CONCAT44(0x43300000,(int)sVar1 ^ 0x80000000) - DOUBLE_80436ed8) /
              (float)((double)CONCAT44(0x43300000,
                                       (int)*(short *)((int)DAT_8043610c + 6) ^ 0x80000000) -
                     DOUBLE_80436ed8);
    }
    else {
      fVar2 = (float)((double)CONCAT44(0x43300000,
                                       (int)*(short *)((int)DAT_8043610c + 6) - (int)sVar1 ^
                                       0x80000000) - DOUBLE_80436ed8) /
              (float)((double)CONCAT44(0x43300000,
                                       (int)*(short *)((int)DAT_8043610c + 6) ^ 0x80000000) -
                     DOUBLE_80436ed8);
    }
    fVar2 = FLOAT_80436ed0 * fVar2;
    *DAT_8043610c = *DAT_8043610c & 0xffffff00;
    *DAT_8043610c = *DAT_8043610c | (int)fVar2 & 0xffU;
    DAT_80436108 = 1;
  }
  return;
}



// ==== 80027c1c  zz_0027c1c_ ====

void zz_0027c1c_(void)

{
  *(undefined1 *)(DAT_8043610c + 8) = 0;
  *(undefined2 *)(DAT_8043610c + 4) = 0;
  return;
}



// ==== 80027c34  zz_0027c34_ ====

void zz_0027c34_(void)

{
  undefined4 uVar1;
  float afStack_38 [14];
  
  if ((*(int *)(PTR_DAT_80433930 + 0x38) == 0) && (DAT_80436108 != 0)) {
    gnt4_GXSetCullMode_bl(2);
    gnt4_GXSetBlendMode_bl(1,4,5,0);
    gnt4_GXSetZMode_bl(1,7,0);
    gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
    gnt4_PSMTXIdentity_bl(afStack_38);
    gnt4_GXLoadPosMtxImm_bl(afStack_38,0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9,1);
    gnt4_GXSetVtxDesc_bl(0xb,1);
    gnt4_GXSetVtxAttrFmt_bl(0,9,0,3,0);
    gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
    gnt4_GXSetNumChans_bl(1);
    gnt4_GXSetNumTexGens_bl(0);
    gnt4_GXSetNumTevStages_bl(1);
    gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
    gnt4_GXSetTevOrder_bl(0,0xff,0xff,4);
    gnt4_GXSetTevOp_bl(0,4);
    gnt4_GXBegin_bl(0x80,0,4);
    uVar1 = *DAT_8043610c;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000 = uVar1;
    DAT_cc008000._0_2_ = 0x280;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000 = uVar1;
    DAT_cc008000._0_2_ = 0x280;
    DAT_cc008000._0_2_ = 0x1c0;
    DAT_cc008000 = uVar1;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0x1c0;
    DAT_cc008000 = uVar1;
  }
  return;
}



// ==== 80027dc0  zz_0027dc0_ ====

void zz_0027dc0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  ushort *puVar2;
  double dVar3;
  
  DAT_80436110 = DAT_80436238;
  zz_008bdc8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436238,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  puVar1 = (undefined4 *)cPoseAccumulator__GetNodeMatrix_((int)DAT_80436110,0);
  puVar2 = (ushort *)*puVar1;
  gnt4_GXInitTexObj_bl
            ((uint *)&DAT_803b02d8,*(uint *)(puVar2 + 4),(uint)puVar2[1],(uint)*puVar2,
             *(uint *)(puVar2 + 2),0,0,'\0');
  dVar3 = (double)FLOAT_80436ee0;
  gnt4_GXInitTexObjLOD_bl(dVar3,dVar3,dVar3,(uint *)&DAT_803b02d8,0,0,0,'\0',0);
  DAT_80436114 = 1;
  return;
}



// ==== 80027e54  zz_0027e54_ ====

void zz_0027e54_(void)

{
  DAT_80436114 = 0;
  return;
}



// ==== 80027e60  zz_0027e60_ ====

void zz_0027e60_(void)

{
  float afStack_38 [14];
  
  if (DAT_80436114 != 0) {
    gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
    gnt4_PSMTXIdentity_bl(afStack_38);
    gnt4_GXLoadPosMtxImm_bl(afStack_38,0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXSetCullMode_bl(0);
    gnt4_GXSetZMode_bl(1,7,1);
    gnt4_GXSetNumChans_bl(1);
    gnt4_GXSetChanCtrl_bl(0,0,1,1,0,0,2);
    gnt4_GXSetChanCtrl_bl(2,0,1,1,0,0,2);
    gnt4_GXSetNumTevStages_bl(1);
    gnt4_GXSetTevOp_bl(0,0);
    gnt4_GXSetTevOrder_bl(0,0,0,4);
    gnt4_GXSetBlendMode_bl(1,4,5,0);
    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9,1);
    gnt4_GXSetVtxDesc_bl(0xb,1);
    gnt4_GXSetVtxDesc_bl(0xd,1);
    gnt4_GXSetVtxAttrFmt_bl(0,9,1,3,0);
    gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
    gnt4_GXSetVtxAttrFmt_bl(0,0xd,1,3,0);
    zz_0028094_();
  }
  return;
}



// ==== 80027fc4  zz_0027fc4_ ====

void zz_0027fc4_(short *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  short sVar4;
  short *psVar5;
  uint uVar6;
  
  iVar2 = ((int)*(char *)(param_1 + 2) & 0x7fU) * 8;
  if (DAT_80436114 != 0) {
    uVar6 = *(uint *)(&DAT_802cfc08 + iVar2);
    if (((int)*(char *)(param_1 + 2) & 0x80U) != 0) {
      uVar6 = uVar6 & 0xffffff00 | 0xa0;
    }
    DAT_80436118 = *(short *)(&DAT_802cfc0c + iVar2);
    sVar4 = 0;
    for (psVar5 = param_1 + 3; *(char *)psVar5 != '\0'; psVar5 = (short *)((int)psVar5 + 1)) {
      uVar3 = (uint)*(char *)psVar5;
      if (uVar3 != 0x20) {
        iVar1 = (int)uVar3 >> 0x1f;
        zz_0028154_(*param_1 + sVar4,param_1[1],
                    (short)((iVar1 * 0x10 | uVar3 * 0x10000000 + iVar1 >> 0x1c) - iVar1) * 8,
                    *(short *)(&DAT_802cfc0e + iVar2) + ((ushort)(uVar3 >> 1) & 0x78),uVar6);
      }
      sVar4 = sVar4 + DAT_80436118;
    }
  }
  return;
}



// ==== 80028094  zz_0028094_ ====

void zz_0028094_(void)

{
  undefined4 *puVar1;
  double dVar2;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  puVar1 = (undefined4 *)cPoseAccumulator__GetNodeMatrix_(DAT_80436110,0);
  gnt4_GXLoadTexObj_bl((uint *)&DAT_803b02d8,0);
  local_18 = 0x43300000;
  uStack_14 = (uint)((ushort *)*puVar1)[1];
  uStack_c = (uint)*(ushort *)*puVar1;
  dVar2 = (double)FLOAT_80436ee4;
  local_10 = 0x43300000;
  gnt4_PSMTXScale_bl((double)(float)(dVar2 / (double)(float)((double)CONCAT44(0x43300000,uStack_14)
                                                            - DOUBLE_80436ee8)),
                     (double)(float)(dVar2 / (double)(float)((double)CONCAT44(0x43300000,uStack_c) -
                                                            DOUBLE_80436ee8)),dVar2,afStack_48);
  gnt4_GXLoadTexMtxImm_bl(afStack_48,0x1e,1);
  gnt4_GXSetNumTexGens_bl(1);
  gnt4_GXSetTexCoordGen2_bl(0,1,4,0x1e,0,0x7d);
  return;
}



// ==== 80028154  zz_0028154_ ====

void zz_0028154_(short param_1,short param_2,short param_3,short param_4,undefined4 param_5)

{
  short sVar1;
  short sVar2;
  
  sVar1 = DAT_80436118;
  sVar2 = param_1 + DAT_80436118;
  gnt4_GXBegin_bl(0x80,0,4);
  DAT_cc008000._0_2_ = param_1;
  DAT_cc008000._0_2_ = param_2;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000 = param_5;
  DAT_cc008000._0_2_ = param_3;
  DAT_cc008000._0_2_ = param_4;
  DAT_cc008000._0_2_ = sVar2;
  DAT_cc008000._0_2_ = param_2;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000 = param_5;
  DAT_cc008000._0_2_ = param_3 + 8;
  DAT_cc008000._0_2_ = param_4;
  DAT_cc008000._0_2_ = sVar2;
  DAT_cc008000._0_2_ = param_2 + sVar1;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000 = param_5;
  DAT_cc008000._0_2_ = param_3 + 8;
  DAT_cc008000._0_2_ = param_4 + 8;
  DAT_cc008000._0_2_ = param_1;
  DAT_cc008000._0_2_ = param_2 + sVar1;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000 = param_5;
  DAT_cc008000._0_2_ = param_3;
  DAT_cc008000._0_2_ = param_4 + 8;
  return;
}



// ==== 8002821c  FUN_8002821c ====

void FUN_8002821c(void)

{
  zz_008c098_();
  (*(code *)(&PTR_FUN_802cfdc4)[(char)PTR_DAT_80433930[0x32]])();
  zz_0027ae8_();
  return;
}



// ==== 80028264  zz_0028264_ ====

void zz_0028264_(void)

{
  PTR_DAT_80433930[0x42] = 1;
  (*(code *)(&PTR_FUN_802cfde0)[(char)*PTR_DAT_80433934])();
  *(int *)(PTR_DAT_80433934 + 0xa8) = *(int *)(PTR_DAT_80433934 + 0xa8) + 1;
  return;
}



// ==== 800282c0  zz_00282c0_ ====

void zz_00282c0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_0029c54_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_007fd5c_();
  return;
}



// ==== 800282e4  zz_00282e4_ ====

void zz_00282e4_(void)

{
  char cVar1;
  int iVar2;
  byte local_8;
  byte local_7 [7];
  
  PTR_DAT_80433930[0x33] = 1;
  local_7[0] = PTR_DAT_80433930[2];
  local_8 = PTR_DAT_80433934[0x15d9] & ~local_7[0];
  cVar1 = PTR_DAT_80433930[3];
  if (cVar1 == '\x02') {
    PTR_DAT_80433930[0x29] = 1;
    PTR_DAT_80433930[0x3d] = 1;
  }
  else if ((cVar1 < '\x02') && ('\0' < cVar1)) {
    PTR_DAT_80433930[0x29] = 0;
  }
  else {
    PTR_DAT_80433930[0x29] = 2;
  }
  iVar2 = zz_00283bc_(local_7,&local_8);
  PTR_DAT_80433934[0xc0] = (char)iVar2;
  iVar2 = zz_00283bc_(local_7,&local_8);
  PTR_DAT_80433934[0xc1] = (char)iVar2;
  iVar2 = zz_00283bc_(local_7,&local_8);
  PTR_DAT_80433934[0xc2] = (char)iVar2;
  iVar2 = zz_00283bc_(local_7,&local_8);
  PTR_DAT_80433934[0xc3] = (char)iVar2;
  return;
}



// ==== 800283bc  zz_00283bc_ ====

int zz_00283bc_(byte *param_1,byte *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = -1;
  iVar2 = 0;
  while ((iVar2 < 6 && ((char)iVar3 < '\0'))) {
    uVar1 = 1 << iVar2;
    if ((*param_1 & uVar1) != 0) {
      iVar3 = (int)(char)iVar2;
    }
    iVar2 = iVar2 + 1;
    *param_1 = *param_1 & ~(byte)uVar1;
  }
  if ((char)iVar3 == -1) {
    for (iVar2 = 0; iVar2 < 6; iVar2 = iVar2 + 1) {
      if (-1 < (char)iVar3) {
        return iVar3;
      }
      if (((uint)*param_2 & 1 << iVar2) != 0) {
        iVar3 = (int)(char)iVar2;
      }
      *param_2 = *param_2 & ~(byte)(1 << iVar2);
    }
  }
  return iVar3;
}



// ==== 8002844c  FUN_8002844c ====

void FUN_8002844c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined *puVar6;
  undefined8 uVar7;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  
  PTR_DAT_80433934[0x45] = 1;
  if ((PTR_DAT_80433930[0x40] != '\0') || (PTR_DAT_80433930[0x32] == '\0')) {
    if (PTR_DAT_80433934[1] == '\0') {
      PTR_DAT_80433934[1] = 1;
      uVar7 = zz_002a26c_();
      if (PTR_DAT_80433930[0x40] != '\0') {
        uVar7 = zz_0044228_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            PTR_DAT_80433930,extraout_r4,param_11,param_12,param_13,param_14,
                            param_15,param_16);
      }
      uVar7 = zz_0042454_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      zz_0042690_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      return;
    }
    if ((PTR_DAT_80433934[1] == '\x01') && (iVar1 = zz_000a3c4_(), iVar1 != 0)) {
      return;
    }
  }
  *PTR_DAT_80433934 = *PTR_DAT_80433934 + '\x01';
  PTR_DAT_80433934[1] = 0;
  zz_0197854_(1);
  zz_0088398_(DAT_80436238 + 0xfe800,0xe0000,0);
  zz_00536b0_(DAT_803c71dc);
  zz_0087718_(DAT_803c71e0);
  zz_000bb70_();
  PTR_DAT_80433930[0xf] = 0xff;
  PTR_DAT_80433930[0xe] = 0xff;
  PTR_DAT_80433930[0xd] = 0xff;
  PTR_DAT_80433930[0xc] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x20) = &DAT_803c7380;
  *(undefined **)(PTR_DAT_80433930 + 0x1c) = &DAT_803c7380;
  *(undefined **)(PTR_DAT_80433930 + 0x18) = &DAT_803c7380;
  *(undefined **)(PTR_DAT_80433930 + 0x14) = &DAT_803c7380;
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7380,(float *)&DAT_802cfdf0,(float *)&DAT_802cfdfc,
                      (float *)&DAT_802cfe08);
  zz_0052990_();
  zz_00529dc_();
  zz_00f0a34_();
  zz_00f0a60_();
  puVar6 = PTR_DAT_80433934;
  puVar4 = (undefined *)0x40;
  uVar5 = 0;
  PTR_DAT_80433934[0x1828] = 0;
  zz_002a5f4_(0x40,0x40,0x40,0);
  zz_0029ca4_();
  zz_002a1c0_();
  PTR_DAT_80433934[0xc4] = 0;
  PTR_DAT_80433934[0xc5] = 0;
  PTR_DAT_80433934[0xc6] = 0;
  PTR_DAT_80433934[199] = 0;
  PTR_DAT_80433934[200] = 0;
  PTR_DAT_80433934[0xc9] = 0;
  uVar7 = zz_0040f74_();
  uVar7 = zz_0042394_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1);
  uVar7 = zz_00424cc_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)((ulonglong)uVar7 >> 0x20),(int)uVar7,puVar4,uVar5,puVar6,param_14,
                      param_15,param_16);
  zz_007fd6c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0029c54_,0,puVar4,
              uVar5,puVar6,param_14,param_15,param_16);
  uVar7 = zz_0042748_();
  zz_004279c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0040940_();
  uVar7 = zz_003d4a0_();
  zz_004104c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar7 = spawn_challenge_menu_object_set(3);
  uVar7 = zz_0041288_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0042520_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar7 >> 0x20),(int)uVar7,puVar4,uVar5,puVar6,param_14,param_15,
              param_16);
  uVar7 = zz_0042874_();
  uVar7 = zz_0042878_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar7 = zz_0042fe4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar7 = zz_00439a0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1);
  if (PTR_DAT_80433934[0x15dd] != '\0') {
    if (PTR_DAT_80433934[0x15dd] == '\x02') {
      uVar7 = zz_0044418_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
      uVar7 = zz_0044b80_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,
                          extraout_r4_00,puVar4,uVar5,puVar6,param_14,param_15,param_16);
      uVar3 = extraout_r4_01;
    }
    else {
      uVar7 = zz_00437b0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,4);
      uVar3 = extraout_r4_02;
    }
    uVar2 = zz_01887ec_();
    zz_00444b4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar2,uVar3,puVar4,
                uVar5,puVar6,param_14,param_15,param_16);
  }
  uVar7 = set_global_menu_mode(5);
  zz_00e99c8_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a088,uVar5,
              puVar6,param_14,param_15,param_16);
  return;
}



// ==== 800286d8  FUN_800286d8 ====

void FUN_800286d8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 extraout_f1_01;
  
  PTR_DAT_80433934[0x45] = 1;
  iVar1 = zz_00295e0_(param_1,param_2,param_3);
  if (iVar1 != 0) {
    zz_00f03c0_(0,0x176);
    uVar4 = 0xff;
    uVar5 = zz_002a5f4_(0,0,0,0xff);
    zz_0042d28_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    zz_0027aac_(0,0x20,0);
    puVar3 = (undefined *)0x0;
    *PTR_DAT_80433934 = *PTR_DAT_80433934 + '\x01';
    PTR_DAT_80433934[1] = 0;
    PTR_DAT_80433934[2] = 0;
    PTR_DAT_80433934[3] = 0;
    PTR_DAT_80433934[4] = 0;
    PTR_DAT_80433934[5] = 0;
    PTR_DAT_80433934[6] = 0;
    PTR_DAT_80433934[7] = 0;
    *(short *)(PTR_DAT_80433934 + 0x46) = *(short *)(PTR_DAT_80433934 + 0x46) + 1;
    *(undefined2 *)(PTR_DAT_80433934 + 0x1e6) = 0;
    *(undefined2 *)(PTR_DAT_80433934 + 0x1e4) = 0;
    uVar5 = zz_0042300_();
    uVar5 = zz_00425b8_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar5 >> 0x20),(int)uVar5,puVar3,uVar4,in_r7,in_r8,in_r9,
                        in_r10);
    uVar5 = zz_0042954_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar5 >> 0x20),(int)uVar5,puVar3,uVar4,in_r7,in_r8,in_r9,
                        in_r10);
    zz_0043414_(extraout_f1_01,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)((ulonglong)uVar5 >> 0x20),(int)uVar5,puVar3,uVar4,in_r7,in_r8,in_r9,in_r10);
    zz_008a28c_();
    zz_0027760_();
    zz_0006800_();
    PTR_DAT_80433934[0x1f] = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0xb4) = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0xb8) = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0xbc) = 0;
    PTR_DAT_80433934[0x1834] = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0xac) = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0xb0) = 0;
    PTR_DAT_80433934[0xca] = 0;
    uVar5 = zz_008b198_();
    PTR_DAT_80433934[0x60] = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0x68) = 0;
    PTR_DAT_80433934[0x61] = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0x6c) = 0;
    PTR_DAT_80433934[0x62] = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0x70) = 0;
    PTR_DAT_80433934[99] = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0x74) = 0;
    PTR_DAT_80433934[100] = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0x78) = 0;
    PTR_DAT_80433934[0x65] = 0;
    *(undefined4 *)(PTR_DAT_80433934 + 0x7c) = 0;
    uVar2 = extraout_r4;
    if (PTR_DAT_80433930[0x29] != '\0') {
      uVar5 = zz_002aaac_();
      uVar2 = extraout_r4_00;
    }
    PTR_DAT_80433930[0x33] = 0;
    if (PTR_DAT_80433930[0x32] == '\0') {
      zz_00e99c8_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,
                  *(int *)(&DAT_8031a074 + (char)PTR_DAT_80433934[0x1652] * 4),uVar4,in_r7,in_r8,
                  in_r9,in_r10);
    }
    else if (PTR_DAT_80433930[0x32] == '\x01') {
      zz_00e9d9c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  (int)*(short *)(PTR_DAT_80433934 + 0x46),uVar2,puVar3,uVar4,in_r7,in_r8,in_r9,
                  in_r10);
    }
    else {
      zz_00e9d38_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    zz_00178b4_();
    set_global_menu_mode(1);
  }
  return;
}



// ==== 800288fc  FUN_800288fc ====

void FUN_800288fc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar2;
  int iVar1;
  undefined8 uVar3;
  
  zz_00529fc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  cVar2 = Wiper__CutHasOccured_();
  if (cVar2 == '\0') {
    zz_0029164_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  else {
    iVar1 = zz_0052db4_();
    if (iVar1 < 0) {
      zz_0029c54_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      uVar3 = zz_007fd5c_();
      zz_0009e08_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      PTR_DAT_80433930[0x29] = 0;
      if (PTR_DAT_80433934[0x15dd] == '\0') {
        *PTR_DAT_80433930 = 2;
        PTR_DAT_80433930[1] = 0;
        return;
      }
      *PTR_DAT_80433930 = 1;
      PTR_DAT_80433930[1] = 0;
      return;
    }
  }
  zz_0087814_();
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  zz_008c12c_(FUN_80089f9c);
  zz_008c0dc_(FUN_8008a010);
  zz_008c0dc_(FUN_8008a0a8);
  zz_008c0dc_(FUN_8002a06c);
  if (PTR_DAT_80433930[0x40] != '\0') {
    zz_008c0dc_(FUN_8002a12c);
  }
  return;
}



// ==== 800289fc  FUN_800289fc ====

void FUN_800289fc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  byte bVar1;
  short sVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  undefined **ppuVar6;
  undefined4 extraout_r4;
  int iVar7;
  undefined *puVar8;
  undefined4 uVar9;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  uint uVar10;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar11;
  undefined8 extraout_f1;
  undefined8 uVar12;
  
  PTR_DAT_80433934[0x45] = 5;
  bVar1 = PTR_DAT_80433934[1];
  puVar8 = (undefined *)(uint)bVar1;
  ppuVar6 = &switchD_80028a44::switchdataD_802cfe14;
  switch(bVar1) {
  case 0:
    PTR_DAT_80433934[1] = bVar1 + 1;
    *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x5a;
    PTR_DAT_80433934[0x52] = 0;
    zz_008b010_(1);
    zz_00f07c4_();
    zz_00f0920_(0);
    zz_00f0a4c_();
    zz_0011bcc_();
    param_1 = zz_00e9b60_((double)FLOAT_80436ef8,2,0x20,2);
  case 1:
    sVar2 = *(short *)(PTR_DAT_80433934 + 8);
    *(short *)(PTR_DAT_80433934 + 8) = sVar2 + -1;
    if ((short)(sVar2 + -1) < 1) {
      PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
      *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x1e;
      if (PTR_DAT_80433934[0x1f] == '\x04') {
        param_1 = zz_0011c1c_();
      }
    }
    break;
  case 2:
    sVar2 = *(short *)(PTR_DAT_80433934 + 8);
    *(short *)(PTR_DAT_80433934 + 8) = sVar2 + -1;
    if ((short)(sVar2 + -1) < 1) {
      piVar11 = &DAT_803c4e84;
      iVar5 = 0;
      PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
      *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x3c;
      PTR_DAT_80433934[0x52] = 1;
      PTR_DAT_80433930[0x33] = 1;
      do {
        zz_0010760_(*piVar11,4);
        iVar5 = iVar5 + 1;
        piVar11 = piVar11 + 1;
      } while (iVar5 < 4);
      uVar12 = zz_008b010_(2);
      if ((PTR_DAT_80433934[0x51] == '\0') || (PTR_DAT_80433934[0x51] == '\x02')) {
        iVar7 = 0x11;
        iVar5 = 0;
        iVar4 = 4;
        puVar8 = PTR_DAT_80433934;
        do {
          if (puVar8[0x102] != '\0') {
            if (PTR_DAT_80433934[iVar5 * 0x3c + 0xf6] == '\0') {
              iVar7 = 0x11;
            }
            else {
              iVar7 = 0x10;
            }
            break;
          }
          puVar8 = puVar8 + 0x3c;
          iVar5 = iVar5 + 1;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      else {
        iVar7 = 0x10;
      }
      param_1 = zz_00e99c8_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,
                            *(int *)(&DAT_8031a074 + iVar7 * 4),iVar7,in_r7,in_r8,in_r9,in_r10);
    }
    break;
  case 3:
    iVar5 = zz_000a3c4_();
    if ((iVar5 == 0) &&
       (sVar2 = *(short *)(PTR_DAT_80433934 + 8), *(short *)(PTR_DAT_80433934 + 8) = sVar2 + -1,
       (short)(sVar2 + -1) < 1)) {
      iVar5 = zz_0029bd0_();
      if (iVar5 == 0) {
        PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
        *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x3c;
        PTR_DAT_80433934[0x52] = 2;
      }
      else {
        *(undefined2 *)(PTR_DAT_80433934 + 8) = 0;
      }
    }
    break;
  case 4:
    param_1 = zz_008b010_((int)(-((int)*(short *)(PTR_DAT_80433934 + 8) & 3U) |
                               (int)*(short *)(PTR_DAT_80433934 + 8) & 3U) >> 0x1f & 2);
    sVar2 = *(short *)(PTR_DAT_80433934 + 8);
    *(short *)(PTR_DAT_80433934 + 8) = sVar2 + -1;
    puVar8 = PTR_DAT_80433934;
    if ((short)(sVar2 + -1) < 1) {
      uVar9 = 0x3c;
      PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
      *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x3c;
      PTR_DAT_80433934[0x52] = 3;
      zz_008b010_(0);
      zz_00425f4_();
      uVar12 = zz_00434a0_();
      param_1 = zz_00425f8_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int)((ulonglong)uVar12 >> 0x20),(int)uVar12,uVar9,puVar8,in_r7,in_r8,
                            in_r9,in_r10);
      if (PTR_DAT_80433934[0x15dd] != '\0') {
        param_1 = zz_0043100_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      }
    }
    break;
  case 5:
    iVar5 = *(short *)(PTR_DAT_80433934 + 8) + -1;
    *(short *)(PTR_DAT_80433934 + 8) = (short)iVar5;
    if ((0 < (short)iVar5) || (iVar7 = zz_000a3c4_(), iVar7 != 0)) break;
    uVar12 = zz_00425b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,iVar5,
                         puVar8,in_r6,in_r7,in_r8,in_r9,in_r10);
    if (PTR_DAT_80433934[0x15dd] != '\0') {
      uVar12 = zz_0043414_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           PTR_DAT_80433934,extraout_r4,puVar8,in_r6,in_r7,in_r8,in_r9,in_r10);
    }
    puVar3 = PTR_DAT_80433934;
    PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
    if (PTR_DAT_80433934[0x15dd] != '\0') {
      zz_0045010_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,PTR_DAT_80433934,
                  puVar3,puVar8,in_r6,in_r7,in_r8,in_r9,in_r10);
    }
    if (PTR_DAT_80433934[0x67] != '\x01') {
      *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x78;
      PTR_DAT_80433934[0x52] = 4;
      param_1 = zz_008b010_(2);
      break;
    }
    goto LAB_80028d84;
  case 6:
    sVar2 = *(short *)(PTR_DAT_80433934 + 8);
    *(short *)(PTR_DAT_80433934 + 8) = sVar2 + -1;
    if (0 < (short)(sVar2 + -1)) break;
LAB_80028d84:
    PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
    *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x708;
    PTR_DAT_80433934[0x52] = 5;
    PTR_DAT_80433930[0x33] = 0;
    zz_008b010_(0);
    iVar5 = 0;
    piVar11 = &DAT_803c4e84;
    do {
      zz_0010760_(*piVar11,5);
      iVar5 = iVar5 + 1;
      piVar11 = piVar11 + 1;
    } while (iVar5 < 4);
    zz_00d285c_();
    param_1 = set_global_menu_mode(3);
    break;
  case 7:
    if (0 < *(short *)(PTR_DAT_80433934 + 8)) {
      uVar10 = 0;
      if ((PTR_DAT_80433930[2] & 1) != 0) {
        uVar10 = DAT_803c71fc;
      }
      if ((PTR_DAT_80433930[2] & 2) != 0) {
        uVar10 = uVar10 | DAT_803c721c;
      }
      if ((PTR_DAT_80433930[2] & 4) != 0) {
        uVar10 = uVar10 | DAT_803c723c;
      }
      if ((PTR_DAT_80433930[2] & 8) != 0) {
        uVar10 = uVar10 | DAT_803c725c;
      }
      if (uVar10 != 0) {
        *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x708;
      }
    }
    sVar2 = *(short *)(PTR_DAT_80433934 + 8);
    *(short *)(PTR_DAT_80433934 + 8) = sVar2 + -1;
    if (((short)(sVar2 + -1) < 1) ||
       ((int)(char)PTR_DAT_80433930[2] == (uint)(byte)PTR_DAT_80433934[0xf0])) {
      PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
      PTR_DAT_80433934[0x52] = 6;
      zz_0027aac_(0,0x20,1);
      zz_00e9b60_((double)FLOAT_80436ef8,2,0x20,2);
      zz_00e9b60_((double)FLOAT_80436ef8,0,0x20,2);
      param_1 = zz_00e9b60_((double)FLOAT_80436ef8,1,0x20,2);
    }
    break;
  case 8:
    iVar5 = zz_0027adc_();
    if ((iVar5 == 0) && (iVar5 = zz_000a3c4_(), iVar5 == 0)) {
      zz_0029c54_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,ppuVar6,puVar8,
                  in_r6,in_r7,in_r8,in_r9,in_r10);
      uVar12 = zz_007fd5c_();
      zz_0009e08_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      PTR_DAT_80433930[0x29] = 0;
      *PTR_DAT_80433930 = 1;
      PTR_DAT_80433930[1] = 0;
      return;
    }
    break;
  case 9:
    iVar5 = zz_000a3c4_();
    if (iVar5 != 0) {
      return;
    }
    *PTR_DAT_80433930 = 3;
    PTR_DAT_80433930[1] = 1;
    *PTR_DAT_80433934 = 0;
    PTR_DAT_80433934[1] = 0;
    PTR_DAT_80433934[2] = 0;
    PTR_DAT_80433934[3] = 0;
    PTR_DAT_80433934[4] = 0;
    PTR_DAT_80433934[5] = 0;
    PTR_DAT_80433934[6] = 0;
    PTR_DAT_80433934[7] = 0;
    iVar7 = (char)PTR_DAT_80433934[0x1c] + 0x12;
    iVar5 = iVar7 / 0x11 + (iVar7 >> 0x1f);
    PTR_DAT_80433934[0x1c] = (char)iVar7 + ((char)iVar5 - (char)(iVar5 >> 0x1f)) * -0x11;
    iVar5 = LooseBallAnims__GetDesperationInfo_unsigned((int)(char)PTR_DAT_80433934[0x1c]);
    if (iVar5 == 0) {
      PTR_DAT_80433934[0x1e] = 0;
    }
    else {
      PTR_DAT_80433934[0x1e] =
           (char)((char)PTR_DAT_80433934[0x1e] + iVar5) -
           (char)(((char)PTR_DAT_80433934[0x1e] + iVar5) / iVar5) * (char)iVar5;
    }
    iVar5 = 0;
    for (iVar7 = 0; iVar7 < (char)PTR_DAT_80433934[0x53]; iVar7 = iVar7 + 1) {
      iVar4 = iVar5 + 0x114;
      iVar5 = iVar5 + 0x3c;
      *(undefined4 *)(PTR_DAT_80433934 + iVar4) =
           *(undefined4 *)(&DAT_802cfdb4 + (char)PTR_DAT_80433934[0x15d8] * 4);
    }
    *(undefined4 *)(PTR_DAT_80433934 + 0x4c) = *(undefined4 *)(PTR_DAT_80433934 + 0x48);
    zz_0029fd4_();
    PTR_DAT_80433934[0x15da] = PTR_DAT_80433934[0x15dc];
    zz_000685c_(1);
    zz_00282e4_();
    zz_00064d4_();
    zz_0006abc_();
    zz_0027c1c_();
    return;
  }
  zz_0029434_(param_1,param_2,param_3);
  zz_0029574_();
  zz_0087814_();
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  zz_008c12c_(FUN_80089f9c);
  zz_008c0dc_(FUN_8008a010);
  zz_008c0dc_(FUN_8008a0a8);
  zz_008c0dc_(FUN_8002a06c);
  return;
}



// ==== 80029164  zz_0029164_ ====

void zz_0029164_(undefined8 param_1,double param_2,double param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar2;
  int iVar1;
  undefined8 uVar3;
  
  uVar3 = (*(code *)(&PTR_FUN_802cfe3c)[(char)PTR_DAT_80433934[1]])();
  zz_008b2f0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  cVar2 = zz_008b290_();
  if (cVar2 == '\0') {
    cVar2 = zz_008b480_();
    if (cVar2 != '\0') {
      zz_008b48c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
  }
  else {
    zz_008b1f8_();
  }
  zz_0029b58_();
  zz_0029434_(uVar3,param_2,param_3);
  zz_0029574_();
  iVar1 = zz_00297c8_();
  if (iVar1 != 0) {
    uVar3 = zz_008b29c_();
    zz_008b514_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    *PTR_DAT_80433934 = *PTR_DAT_80433934 + '\x01';
    PTR_DAT_80433934[1] = 0;
  }
  *(int *)(PTR_DAT_80433934 + 0xac) = *(int *)(PTR_DAT_80433934 + 0xac) + 1;
  return;
}



// ==== 80029218  FUN_80029218 ====

void FUN_80029218(void)

{
  int iVar1;
  
  iVar1 = 0;
  PTR_DAT_80433934[0x45] = 3;
  if (*DAT_803c4e84 != '\0') {
    if (DAT_803c4e84[0x743] == '\0') {
      iVar1 = 1;
    }
  }
  if (DAT_803c4e84[0x1e00] != '\0') {
    if (DAT_803c4e84[0x2543] == '\0') {
      iVar1 = iVar1 + 1;
    }
  }
  if (DAT_803c4e84[0x3c00] != '\0') {
    if (DAT_803c4e84[0x4343] == '\0') {
      iVar1 = iVar1 + 1;
    }
  }
  if (DAT_803c4e84[0x5a00] != '\0') {
    if (DAT_803c4e84[0x6143] == '\0') {
      iVar1 = iVar1 + 1;
    }
  }
  if (DAT_803c4e84[0x7800] != '\0') {
    if (DAT_803c4e84[0x7f43] == '\0') {
      iVar1 = iVar1 + 1;
    }
  }
  if ((DAT_803c4e84[0x9600] != '\0') && (DAT_803c4e84[0x9d43] == '\0')) {
    iVar1 = iVar1 + 1;
  }
  if (iVar1 == 0) {
    if (PTR_DAT_80433930[0x40] == '\0') {
      PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
      if (PTR_DAT_80433934[0x15dd] == '\0') {
        *(undefined2 *)(PTR_DAT_80433934 + 8) = 0;
      }
      else {
        *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x78;
        zz_0011c60_();
      }
    }
    else {
      *(undefined2 *)(PTR_DAT_80433934 + 8) = 0;
      PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
      PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
      PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
    }
  }
  return;
}



// ==== 80029388  FUN_80029388 ====

void FUN_80029388(void)

{
  short sVar1;
  
  sVar1 = *(short *)(PTR_DAT_80433934 + 8);
  *(short *)(PTR_DAT_80433934 + 8) = sVar1 + -1;
  if ((short)(sVar1 + -1) < 1) {
    PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
    *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x5a;
    zz_0011b68_();
  }
  return;
}



// ==== 80029408  FUN_80029408 ====

void FUN_80029408(void)

{
  PTR_DAT_80433934[0x45] = 4;
  zz_00529ec_();
  return;
}



// ==== 80029434  zz_0029434_ ====

void zz_0029434_(undefined8 param_1,double param_2,double param_3)

{
  undefined8 uVar1;
  
  zz_008b048_();
  zz_0029d48_();
  if (PTR_DAT_80433934[0x66] == '\0') {
    zz_0053b30_();
    zz_006ae60_();
    zz_0027764_();
  }
  zz_000bef4_();
  if (PTR_DAT_80433934[0x66] == '\0') {
    zz_0089a94_(0x28);
    zz_0089a94_(0x20);
    zz_0053a2c_();
    zz_0087cf0_();
    zz_0089a94_(0);
    zz_0089a94_(0x10);
    zz_0089a94_(8);
    zz_0089a94_(0x18);
    zz_0089898_(0x38);
  }
  zz_0089898_(0x3a);
  zz_0089898_(0x39);
  zz_0089554_();
  *(int *)(PTR_DAT_80433934 + 0xb0) = *(int *)(PTR_DAT_80433934 + 0xb0) + 1;
  if (PTR_DAT_80433934[0x66] == '\0') {
    zz_008a28c_();
    uVar1 = zz_0089aec_();
    battle_frame_target_action_dispatch(uVar1,param_2,param_3);
  }
  FUN_80036e24();
  zz_008972c_();
  zz_0089658_();
  if (PTR_DAT_80433934[0x66] == '\0') {
    zz_0053a94_();
    zz_0089898_(0x3b);
  }
  if (PTR_DAT_80433934[0x66] != '\x01') {
    zz_000bda4_();
  }
  if (PTR_DAT_80433934[0x66] != '\x01') {
    zz_0040b94_();
  }
  zz_00eff30_();
  PTR_DAT_80433934[0xd3] = PTR_DAT_80433934[0xd1];
  PTR_DAT_80433934[0xd4] = PTR_DAT_80433934[0xd2];
  return;
}



// ==== 80029574  zz_0029574_ ====

void zz_0029574_(void)

{
  zz_008a16c_();
  zz_0053928_();
  zz_0089cd0_(0x28);
  zz_0089cd0_(0x20);
  zz_0089cd0_(0);
  zz_0089cd0_(0x10);
  zz_0089cd0_(8);
  zz_0089cd0_(0x18);
  zz_0089c00_(0x3a);
  zz_0089c00_(0x38);
  zz_0089c00_(0x39);
  return;
}



// ==== 800295e0  zz_00295e0_ ====

undefined4 zz_00295e0_(undefined8 param_1,double param_2,double param_3)

{
  undefined4 uVar1;
  undefined8 extraout_f1;
  
  uVar1 = (*(code *)(&PTR_FUN_802cfe4c)[(char)PTR_DAT_80433934[1]])();
  zz_0029708_(extraout_f1,param_2,param_3);
  zz_0029770_();
  *(int *)(PTR_DAT_80433934 + 0xac) = *(int *)(PTR_DAT_80433934 + 0xac) + 1;
  return uVar1;
}



// ==== 80029648  FUN_80029648 ====

undefined4 FUN_80029648(void)

{
  PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
  zz_0027aac_(0,0x20,0);
  return 0;
}



// ==== 80029688  FUN_80029688 ====

undefined4 FUN_80029688(void)

{
  int iVar1;
  
  iVar1 = zz_000a3c4_();
  if (iVar1 == 0) {
    if (PTR_DAT_80433934[0x1653] == '\0') {
      PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
      zz_0027aac_(0,0x20,1);
    }
  }
  return 0;
}



// ==== 800296e0  FUN_800296e0 ====

uint FUN_800296e0(void)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = zz_0027adc_();
  uVar1 = countLeadingZeros(iVar2);
  return uVar1 >> 5;
}



// ==== 80029708  zz_0029708_ ====

void zz_0029708_(undefined8 param_1,double param_2,double param_3)

{
  undefined8 uVar1;
  
  zz_0089a94_(0x28);
  zz_0089898_(0x39);
  zz_0087cf0_();
  zz_0089554_();
  *(int *)(PTR_DAT_80433934 + 0xb0) = *(int *)(PTR_DAT_80433934 + 0xb0) + 1;
  zz_008a28c_();
  uVar1 = zz_0089aec_();
  battle_frame_target_action_dispatch(uVar1,param_2,param_3);
  FUN_80036e24();
  zz_008972c_();
  zz_0089658_();
  zz_0089898_(0x3b);
  zz_0040b94_();
  return;
}



// ==== 80029770  zz_0029770_ ====

void zz_0029770_(void)

{
  zz_008a16c_();
  zz_0089cd0_(0x28);
  zz_0089c00_(0x39);
  zz_0087814_();
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  zz_008c12c_(FUN_80089f9c);
  return;
}



// ==== 800297c8  zz_00297c8_ ====

int zz_00297c8_(void)

{
  int iVar1;
  int iVar2;
  
  if (PTR_DAT_80433930[0x40] != '\0') {
    return 0;
  }
  if (PTR_DAT_80433934[0x1f] == '\0') {
    if (PTR_DAT_80433930[0x32] == '\0') {
      if (PTR_DAT_80433934[0x145] != '\0') {
        if ((char)PTR_DAT_80433934[0x146] < '\x01') {
          PTR_DAT_80433934[0x1f] = 1;
        }
      }
      if (PTR_DAT_80433934[0x109] != '\0') {
        if ((char)PTR_DAT_80433934[0x10a] < '\x01') {
          PTR_DAT_80433934[0x1f] = PTR_DAT_80433934[0x1f] | 2;
        }
      }
      if (PTR_DAT_80433934[0x144] != '\0') {
        if (*(int *)(PTR_DAT_80433934 + 0x154) < 1) {
          PTR_DAT_80433934[0x1f] = PTR_DAT_80433934[0x1f] | 1;
        }
      }
      if (PTR_DAT_80433934[0x108] != '\0') {
        if (*(int *)(PTR_DAT_80433934 + 0x118) < 1) {
          PTR_DAT_80433934[0x1f] = PTR_DAT_80433934[0x1f] | 2;
        }
      }
      if (PTR_DAT_80433934[0x15df] != '\0') {
        if (PTR_DAT_80433934[0x50] == '\0') {
          if (*(int *)(PTR_DAT_80433934 + 0x4c) < 1) {
            if (PTR_DAT_80433934[0x10b] == '\0') {
              PTR_DAT_80433934[0x1f] = PTR_DAT_80433934[0x1f] | 2;
            }
            else {
              PTR_DAT_80433934[0x1f] = PTR_DAT_80433934[0x1f] | 1;
            }
          }
        }
      }
      if ((PTR_DAT_80433934[0x1f] & 1) != 0) {
        *(short *)(PTR_DAT_80433934 + 0x110) = *(short *)(PTR_DAT_80433934 + 0x110) + 1;
      }
      if ((PTR_DAT_80433934[0x1f] & 2) != 0) {
        *(short *)(PTR_DAT_80433934 + 0x14c) = *(short *)(PTR_DAT_80433934 + 0x14c) + 1;
      }
    }
    else {
      if (*(int *)(PTR_DAT_80433934 + 0x154) < 1) {
        PTR_DAT_80433934[0x1f] = 1;
        *(short *)(PTR_DAT_80433934 + 0x110) = *(short *)(PTR_DAT_80433934 + 0x110) + 1;
      }
      if (*(int *)(PTR_DAT_80433934 + 0x118) < 1) {
        PTR_DAT_80433934[0x1f] = PTR_DAT_80433934[0x1f] | 2;
        *(short *)(PTR_DAT_80433934 + 0x14c) = *(short *)(PTR_DAT_80433934 + 0x14c) + 1;
      }
      if (PTR_DAT_80433934[0x1f] == '\0') {
        if (PTR_DAT_80433934[0x50] == '\0') {
          if (*(int *)(PTR_DAT_80433934 + 0x4c) < 1) {
            PTR_DAT_80433934[0x1f] = 4;
          }
        }
      }
    }
  }
  if (PTR_DAT_80433934[0x1f] != '\0') {
    iVar1 = 0;
    iVar2 = 2;
    do {
      if ((int)(char)PTR_DAT_80433934[0x1f] == 1 << (int)(char)PTR_DAT_80433934[iVar1 + 0xcb]) {
        PTR_DAT_80433934[iVar1 + 0xc4] = 1;
      }
      else {
        PTR_DAT_80433934[iVar1 + 0xc4] = 0;
      }
      if ((int)(char)PTR_DAT_80433934[0x1f] == 1 << (int)(char)PTR_DAT_80433934[iVar1 + 0xcc]) {
        PTR_DAT_80433934[iVar1 + 0xc5] = 1;
      }
      else {
        PTR_DAT_80433934[iVar1 + 0xc5] = 0;
      }
      if ((int)(char)PTR_DAT_80433934[0x1f] == 1 << (int)(char)PTR_DAT_80433934[iVar1 + 0xcd]) {
        PTR_DAT_80433934[iVar1 + 0xc6] = 1;
      }
      else {
        PTR_DAT_80433934[iVar1 + 0xc6] = 0;
      }
      iVar1 = iVar1 + 3;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (PTR_DAT_80433934[0x1f] == '\x01') {
      PTR_DAT_80433934[0x102] = 1;
    }
    else {
      PTR_DAT_80433934[0x102] = 0;
    }
    if (PTR_DAT_80433934[0x1f] == '\x02') {
      PTR_DAT_80433934[0x13e] = 1;
    }
    else {
      PTR_DAT_80433934[0x13e] = 0;
    }
    if (PTR_DAT_80433934[0x1f] == '\x04') {
      PTR_DAT_80433934[0x17a] = 1;
    }
    else {
      PTR_DAT_80433934[0x17a] = 0;
    }
    if (PTR_DAT_80433934[0x1f] == '\b') {
      PTR_DAT_80433934[0x1b6] = 1;
    }
    else {
      PTR_DAT_80433934[0x1b6] = 0;
    }
    if (((*(int *)(PTR_DAT_80433934 + 0xb8) == 0) ||
        (*(int *)(PTR_DAT_80433934 + 0xb8) == *(int *)(PTR_DAT_80433934 + 0xb4))) ||
       (*(char *)(*(int *)(PTR_DAT_80433934 + 0xb4) + 0x18) != '\x01')) {
      PTR_DAT_80433934[0x67] = 1;
    }
    else {
      PTR_DAT_80433934[0x67] = 0;
    }
  }
  return (int)(char)PTR_DAT_80433934[0x1f];
}



// ==== 80029b58  zz_0029b58_ ====

undefined4 zz_0029b58_(void)

{
  char cVar2;
  char cVar3;
  int iVar1;
  
  cVar2 = zz_008b480_();
  cVar3 = zz_008b290_();
  if (cVar3 == '\0' && cVar2 == '\0') {
    if (PTR_DAT_80433934[0x45] == '\x04') {
      if (PTR_DAT_80433934[0x50] == '\0') {
        iVar1 = *(int *)(PTR_DAT_80433934 + 0x4c);
        *(int *)(PTR_DAT_80433934 + 0x4c) = iVar1 + -1;
        if (iVar1 + -1 < 1) {
          *(undefined4 *)(PTR_DAT_80433934 + 0x4c) = 0;
        }
      }
    }
  }
  return *(undefined4 *)(PTR_DAT_80433934 + 0x4c);
}



// ==== 80029bd0  zz_0029bd0_ ====

undefined4 zz_0029bd0_(void)

{
  undefined4 uVar1;
  
  if (PTR_DAT_80433934[0x15dd] == '\0') {
    uVar1 = 0;
  }
  else if (*(int *)(PTR_DAT_80433934 + 0xbc) == 0) {
    uVar1 = 0;
  }
  else if (PTR_DAT_80433934[0x1f] == '\x01') {
    zz_01d6ff4_();
    if (PTR_DAT_80433934[0x1834] == '\0') {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
      PTR_DAT_80433934[0x1834] = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80029c54  zz_0029c54_ ====

void zz_0029c54_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined8 uVar1;
  
  zz_0008b58_();
  zz_0008c40_();
  zz_0008cf4_();
  zz_01978d0_();
  zz_0040910_();
  uVar1 = zz_00f0a60_();
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4_00
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,extraout_r4_01,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00f07c4_();
  return;
}



// ==== 80029ca4  zz_0029ca4_ ====

void zz_0029ca4_(void)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = 0;
  do {
    pcVar3 = PTR_DAT_80433934 + iVar4 + 0xf4;
    *pcVar3 = (char)iVar2;
    uVar1 = zz_00055fc_();
    pcVar3[10] = (char)uVar1;
    pcVar3[10] = pcVar3[10] & 3;
    pcVar3[0xb] = pcVar3[10];
    pcVar3[0xe] = '\0';
    pcVar3[0xc] = '\0';
    pcVar3[0xd] = '\0';
    pcVar3[0xf] = '\0';
    pcVar3[0x10] = '\0';
    pcVar3[0x18] = '\0';
    pcVar3[0x19] = '\0';
    pcVar3[0x1a] = '\0';
    pcVar3[0x1b] = '\x01';
    zz_0029e98_(pcVar3);
    iVar2 = iVar2 + 1;
    iVar4 = iVar4 + 0x3c;
  } while (iVar2 < 4);
  return;
}



// ==== 80029d48  zz_0029d48_ ====

void zz_0029d48_(void)

{
  short sVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  char *pcVar5;
  
  iVar4 = 0;
  pcVar5 = PTR_DAT_80433934 + 0xf4;
  do {
    zz_0029e98_(pcVar5);
    if ('\0' < pcVar5[1]) {
      if (pcVar5[0x10] == '\0') {
        if (*(ushort *)(pcVar5 + 0x32) < *(ushort *)(pcVar5 + 0x30)) {
          pcVar5[0xf] = '\0';
        }
        else {
          pcVar5[0xf] = '\x01';
        }
      }
      else {
        pcVar5[0xf] = '\0';
        cVar2 = zz_008b290_();
        if (cVar2 == '\0') {
          bVar3 = zz_008b480_();
          if ((bVar3 == 0) || ((bVar3 & pcVar5[3]) != 0)) {
            sVar1 = *(short *)(pcVar5 + 0x18);
            *(short *)(pcVar5 + 0x18) = sVar1 + -1;
            if ((short)(sVar1 + -1) < 1) {
              pcVar5[0x32] = '\0';
              pcVar5[0x33] = '\0';
              pcVar5[0x10] = '\0';
              pcVar5[0x32] = '\0';
              pcVar5[0x33] = '\0';
            }
            else {
              *(short *)(pcVar5 + 0x32) =
                   (short)(int)((float)((double)CONCAT44(0x43300000,(uint)*(ushort *)(pcVar5 + 0x30)
                                                        ) - DOUBLE_80436f00) *
                               ((float)((double)CONCAT44(0x43300000,
                                                         (int)*(short *)(pcVar5 + 0x18) ^ 0x80000000
                                                        ) - DOUBLE_80436f08) /
                               (float)((double)CONCAT44(0x43300000,
                                                        (int)*(short *)(pcVar5 + 0x1a) ^ 0x80000000)
                                      - DOUBLE_80436f08)));
            }
          }
        }
      }
    }
    iVar4 = iVar4 + 1;
    pcVar5 = pcVar5 + 0x3c;
  } while (iVar4 < 4);
  return;
}



// ==== 80029e98  zz_0029e98_ ====

void zz_0029e98_(char *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  param_1[1] = '\0';
  iVar3 = 0;
  iVar2 = 0;
  param_1[2] = '\0';
  param_1[3] = '\0';
  param_1[4] = -1;
  param_1[5] = -1;
  param_1[6] = -1;
  param_1[7] = -1;
  param_1[8] = -1;
  param_1[9] = -1;
  iVar5 = 3;
  do {
    uVar4 = 1 << iVar2;
    if (((byte)PTR_DAT_80433934[0x15d9] & uVar4) != 0) {
      if (PTR_DAT_80433934[iVar2 + 0xcb] == *param_1) {
        param_1[1] = param_1[1] + '\x01';
        if (((int)(char)PTR_DAT_80433930[2] & uVar4) != 0) {
          param_1[2] = param_1[2] + '\x01';
        }
        iVar1 = iVar3 + 4;
        iVar3 = iVar3 + 1;
        param_1[3] = param_1[3] | (byte)uVar4;
        param_1[iVar1] = (char)iVar2;
      }
    }
    uVar4 = 1 << iVar2 + 1;
    if (((byte)PTR_DAT_80433934[0x15d9] & uVar4) != 0) {
      if (PTR_DAT_80433934[iVar2 + 0xcc] == *param_1) {
        param_1[1] = param_1[1] + '\x01';
        if (((int)(char)PTR_DAT_80433930[2] & uVar4) != 0) {
          param_1[2] = param_1[2] + '\x01';
        }
        iVar1 = iVar3 + 4;
        iVar3 = iVar3 + 1;
        param_1[3] = param_1[3] | (byte)uVar4;
        param_1[iVar1] = (char)(iVar2 + 1);
      }
    }
    iVar2 = iVar2 + 2;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}



// ==== 80029fd4  zz_0029fd4_ ====

void zz_0029fd4_(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = 4;
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar2) != 0) {
      iVar1 = iVar2;
    }
    zz_0098084_(-0x7fc44bc0,iVar2,(&PTR_DAT_802cfda0)[iVar1]);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  gnt4_GXInvalidateTexAll_bl();
  return;
}



// ==== 8002a06c  FUN_8002a06c ====

void FUN_8002a06c(void)

{
  int iVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = DAT_802b0b48;
  local_10 = DAT_802b0b4c;
  local_c = DAT_802b0b50;
  local_18 = DAT_80436f10;
  if (((PTR_DAT_80433930[0x34] == '\0') && (-1 < (char)PTR_DAT_80433930[0x28])) &&
     (iVar1 = (char)PTR_DAT_80433930[0x28] * 0x3e4, (&DAT_803c770b)[iVar1] != '\0')) {
    DAT_803c1150 = iVar1 + -0x7fc388f8;
    DAT_803c1140 = &local_14;
    DAT_803c1154 = &local_18;
    DAT_803c1144 = 0;
    DAT_803c1164 = 3;
    DAT_803c1168 = 0xf;
    DAT_803c1170 = 2;
    FUN_80051998(-0x7fc3eed0);
  }
  return;
}



// ==== 8002a12c  FUN_8002a12c ====

void FUN_8002a12c(void)

{
  if (PTR_DAT_80433930[0x34] == '\0') {
    DAT_803c1140 = &DAT_802cfe58;
    DAT_803c1144 = 0;
    DAT_803c1150 = &DAT_80433678;
    DAT_803c115c = &DAT_80433680;
    DAT_803c113c = 0;
    DAT_803c1174 = FLOAT_80436f14;
    DAT_803c1160 = &DAT_803c00e8;
    DAT_803c1164 = 3;
    DAT_803c1168 = 0xf;
    DAT_803c1170 = 1;
    DAT_803c1173 = 0xff;
    FUN_80051ef4(-0x7fc3eed0);
  }
  return;
}



// ==== 8002a1c0  zz_002a1c0_ ====

void zz_002a1c0_(void)

{
  char cVar1;
  
  cVar1 = PTR_DAT_80433930[3];
  if (cVar1 != '\x02') {
    if ((cVar1 < '\x02') && ('\0' < cVar1)) {
      PTR_DAT_80433934[0x51] = 0;
      return;
    }
    PTR_DAT_80433934[0x51] = 1;
    return;
  }
  cVar1 = PTR_DAT_80433934[0xf6] != '\0';
  if (PTR_DAT_80433934[0x132] != '\0') {
    cVar1 = cVar1 + '\x01';
  }
  if (PTR_DAT_80433934[0x16e] != '\0') {
    cVar1 = cVar1 + '\x01';
  }
  if (PTR_DAT_80433934[0x1aa] != '\0') {
    cVar1 = cVar1 + '\x01';
  }
  if (cVar1 == '\x01') {
    PTR_DAT_80433934[0x51] = 2;
    return;
  }
  PTR_DAT_80433934[0x51] = 1;
  return;
}



// ==== 8002a26c  zz_002a26c_ ====

void zz_002a26c_(void)

{
  int iVar1;
  undefined **ppuVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (PTR_DAT_80433930[0x32] != '\0') {
    iVar4 = 0;
    ppuVar2 = &PTR_s_AAAAAAAAAA_802cfe70;
    iVar3 = 0;
    do {
      iVar6 = 5;
      iVar1 = 0;
      do {
        PTR_DAT_80433934[iVar3 + iVar1 + 0x1654] = (*ppuVar2)[iVar1];
        PTR_DAT_80433934[iVar3 + iVar1 + 0x1655] = (*ppuVar2)[iVar1 + 1];
        PTR_DAT_80433934[iVar3 + iVar1 + 0x1656] = (*ppuVar2)[iVar1 + 2];
        PTR_DAT_80433934[iVar3 + iVar1 + 0x1657] = (*ppuVar2)[iVar1 + 3];
        PTR_DAT_80433934[iVar3 + iVar1 + 0x1658] = (*ppuVar2)[iVar1 + 4];
        PTR_DAT_80433934[iVar3 + iVar1 + 0x1659] = (*ppuVar2)[iVar1 + 5];
        PTR_DAT_80433934[iVar3 + iVar1 + 0x165a] = (*ppuVar2)[iVar1 + 6];
        iVar5 = iVar1 + 8;
        PTR_DAT_80433934[iVar3 + iVar1 + 0x165b] = (*ppuVar2)[iVar1 + 7];
        iVar6 = iVar6 + -1;
        iVar1 = iVar5;
      } while (iVar6 != 0);
      iVar1 = 0x29 - iVar5;
      if (iVar5 < 0x29) {
        do {
          PTR_DAT_80433934[iVar3 + iVar5 + 0x1654] = (*ppuVar2)[iVar5];
          iVar1 = iVar1 + -1;
          iVar5 = iVar5 + 1;
        } while (iVar1 != 0);
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x29;
      ppuVar2 = ppuVar2 + 1;
    } while (iVar4 < 6);
  }
  return;
}



// ==== 8002a3e4  zz_002a3e4_ ====

void zz_002a3e4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 extraout_f1_01;
  undefined8 uVar3;
  
  uVar3 = zz_002a51c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0253a80_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,param_14,
              param_15,param_16);
  gnt4___GXSetIndirectMask_bl(0);
  zz_02103a4_(1);
  zz_0018a80_();
  uVar2 = 0x10;
  iVar1 = 0;
  uVar3 = zz_02278c8_((uint *)&DAT_803aa9b8,(uint *)&DAT_803ca644,0,0x10);
  zz_0246254_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x280,0x1c0,iVar1,uVar2,
              param_13,param_14,param_15,param_16);
  gnt4_HSD_VISetConfigure_bl((undefined4 *)&DAT_803ca644);
  gnt4_VIFlush_bl();
  gnt4_VIWaitForRetrace();
  uVar3 = gnt4_VIWaitForRetrace();
  uVar3 = zz_010d360_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,iVar1,uVar2,param_13,param_14,
                      param_15,param_16);
  zz_021df90_(extraout_f1_01,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,iVar1,uVar2,param_13,param_14,param_15,
              param_16);
  gnt4_OSInitAlarm();
  gnt4_HSD_VISetUserPostRetraceCallback_bl(FUN_8002a598);
  gnt4_HSD_SetZSortMode_bl(1,1);
  return;
}



// ==== 8002a4b0  zz_002a4b0_ ====

void zz_002a4b0_(void)

{
  gnt4_HSD_StartRender_bl(0);
  return;
}



// ==== 8002a4d4  zz_002a4d4_ ====

void zz_002a4d4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar1 = zz_025426c_();
  uVar1 = gnt4_HSD_VICopyXFBASync_bl
                    (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4,
                     param_11,param_12,param_13,param_14,param_15,param_16);
  gnt4_HSD_VISetXFBDrawDone_bl(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  gnt4_VIWaitForRetrace();
  if (DAT_804361c4 != 0) {
    zz_0271224_();
  }
  return;
}



// ==== 8002a51c  zz_002a51c_ ====

void zz_002a51c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar5;
  undefined8 uVar6;
  
  iVar1 = gnt4_OSGetArenaLo_bl();
  uVar2 = gnt4_OSGetArenaHi_bl();
  iVar4 = 2;
  iVar1 = gnt4_OSInitAlloc_bl(iVar1,uVar2,2);
  uVar6 = gnt4_OSSetArenaLo_bl(iVar1);
  uVar2 = iVar1 + 0x1fU & 0xffffffe0;
  uVar5 = uVar2 + 0xed0000;
  uVar3 = uVar5;
  DAT_80436234 = gnt4_OSCreateHeap_bl(uVar2,uVar5);
  gnt4_OSSetCurrentHeap_bl(DAT_80436234);
  DAT_80436230 = gnt4_OSCheckHeap_bl(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     DAT_80436234,uVar3,iVar4,in_r6,in_r7,in_r8,in_r9,in_r10);
  gnt4_OSSetArenaLo_bl(uVar5);
  return;
}



// ==== 8002a598  FUN_8002a598 ====

undefined4 FUN_8002a598(void)

{
  DAT_804361f0 = DAT_804361f0 + 1;
  zz_002a76c_();
  zz_002a704_();
  if ((((int)(char)PTR_DAT_80433930[0x2b] & 0x40U) != 0) &&
     (((int)(char)PTR_DAT_80433930[0x2b] & 0x80U) == 0)) {
    PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | 0x10;
  }
  return 0;
}



// ==== 8002a5f4  zz_002a5f4_ ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zz_002a5f4_(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  _DAT_804362a8 = CONCAT31(CONCAT21(CONCAT11(param_1,param_2),param_3),param_4);
  zz_0253a34_(param_1,param_2,param_3,param_4);
  DAT_803f8ec8 = _DAT_804362a8;
  return;
}



// ==== 8002a638  zz_002a638_ ====

void zz_002a638_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  
  gnt4_memset(PTR_DAT_80433930,0,0x100);
  zz_005042c_();
  uVar3 = zz_00505a8_();
  zz_0088354_();
  uVar1 = 0;
  uVar2 = 0x40;
  gnt4_memset(PTR_DAT_8043394c,0,0x40);
  gnt4_OSSetCurrentHeap_bl(DAT_80436234);
  zz_00ecf60_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x7f,uVar1,uVar2,in_r6,
              in_r7,in_r8,in_r9,in_r10);
  uVar3 = zz_00efd70_();
  zz_002bae8_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar3 = zz_00e9914_();
  DAT_804362ac = &DAT_803f8e80;
  DAT_80436214 = gnt4_HSD_CObjAlloc_bl
                           (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  DAT_80436210 = gnt4_HSD_CObjAlloc_bl
                           (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  DAT_803bb460 = 0;
  DAT_80436208 = 0;
  DAT_8043620c = 0;
  DAT_803bb464 = 0;
  DAT_803bb468 = 0;
  DAT_803bb46c = 0;
  DAT_80436204 = 0;
  uVar3 = zz_008db4c_();
  zz_0009f98_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_008bbd0_(0,0xff);
  gnt4_memset(&DAT_803c0590,0,0x40);
  return;
}



// ==== 8002a704  zz_002a704_ ====

void zz_002a704_(void)

{
  uint uVar1;
  byte bVar2;
  
  bVar2 = 0;
  uVar1 = gnt4_OSGetResetButtonState_bl();
  if (uVar1 == 1) {
    bVar2 = 0x20;
  }
  else if ((PTR_DAT_80433930[0x2b] & 0x20) != 0) {
    bVar2 = 0x40;
  }
  PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | bVar2;
  return;
}



// ==== 8002a76c  zz_002a76c_ ====

void zz_002a76c_(void)

{
  byte bVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  bVar1 = 0;
  uVar4 = (uint)(byte)PTR_DAT_80433930[0x30];
  puVar2 = &DAT_803c727c;
  iVar3 = 0;
  iVar5 = 4;
  do {
    if ((*puVar2 & 0x1600) == 0x1600) {
      if (((char)PTR_DAT_80433930[iVar3 + 0x2c] < '\x1e') && ((uVar4 & 1 << iVar3) == 0)) {
        PTR_DAT_80433930[iVar3 + 0x2c] = PTR_DAT_80433930[iVar3 + 0x2c] + '\x01';
      }
    }
    else {
      uVar4 = uVar4 & ~(1 << iVar3);
      PTR_DAT_80433930[iVar3 + 0x2c] = 0;
    }
    if ('\x1d' < (char)PTR_DAT_80433930[iVar3 + 0x2c]) {
      bVar1 = 0x40;
      uVar4 = uVar4 | 1 << iVar3 & 0xffU;
    }
    puVar2 = puVar2 + 8;
    iVar3 = iVar3 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  PTR_DAT_80433930[0x30] = (char)uVar4;
  PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | bVar1;
  return;
}



// ==== 8002a84c  zz_002a84c_ ====

void zz_002a84c_(void)

{
  PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | 0x48;
  return;
}



// ==== 8002a860  zz_002a860_ ====

void zz_002a860_(int param_1)

{
  gnt4_OSAllocFromHeap_bl(DAT_80436234,param_1);
  return;
}



// ==== 8002a888  zz_002a888_ ====

void zz_002a888_(void)

{
  double dVar1;
  float afStack_88 [12];
  float afStack_58 [16];
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  zz_00058d0_(0,1);
  gnt4_GXSetColorUpdate_bl(0);
  gnt4_GXSetAlphaUpdate_bl(0);
  gnt4_GXSetCullMode_bl(0);
  gnt4_GXSetBlendMode_bl(1,4,5,0);
  gnt4_GXSetZMode_bl(1,7,1);
  dVar1 = (double)FLOAT_80436f18;
  uStack_14 = (uint)*(ushort *)(DAT_804362ac + 6);
  uStack_c = (uint)*(ushort *)(DAT_804362ac + 4);
  local_18 = 0x43300000;
  local_10 = 0x43300000;
  gnt4_C_MTXOrtho_bl(dVar1,(double)(float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80436f30)
                     ,dVar1,(double)(float)((double)CONCAT44(0x43300000,uStack_c) - DOUBLE_80436f30)
                     ,dVar1,(double)FLOAT_80436f1c,afStack_58);
  gnt4_GXSetProjection_bl(afStack_58,1);
  gnt4_PSMTXIdentity_bl(afStack_88);
  gnt4_GXLoadPosMtxImm_bl(afStack_88,0);
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(0xb,1);
  gnt4_GXSetVtxAttrFmt_bl(0,9,1,4,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
  gnt4_GXSetNumChans_bl(1);
  gnt4_GXSetNumTexGens_bl(0);
  gnt4_GXSetNumTevStages_bl(1);
  gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
  gnt4_GXSetTevOrder_bl(0,0xff,0xff,4);
  gnt4_GXSetTevOp_bl(0,4);
  gnt4_GXBegin_bl(0x80,0,4);
  DAT_cc008000 = FLOAT_80436f18;
  DAT_cc008000 = FLOAT_80436f18;
  DAT_cc008000 = FLOAT_80436f20;
  DAT_cc008000 = 0xffffffff;
  DAT_cc008000 = FLOAT_80436f24;
  DAT_cc008000 = FLOAT_80436f18;
  DAT_cc008000 = FLOAT_80436f20;
  DAT_cc008000 = 0xffffffff;
  DAT_cc008000 = FLOAT_80436f24;
  DAT_cc008000 = FLOAT_80436f28;
  DAT_cc008000 = FLOAT_80436f20;
  DAT_cc008000 = 0xffffffff;
  DAT_cc008000 = FLOAT_80436f18;
  DAT_cc008000 = FLOAT_80436f28;
  DAT_cc008000 = FLOAT_80436f20;
  DAT_cc008000 = 0xffffffff;
  gnt4_GXSetColorUpdate_bl(1);
  gnt4_GXSetAlphaUpdate_bl(1);
  gnt4_GXSetZMode_bl(1,3,1);
  return;
}



// ==== 8002aaac  zz_002aaac_ ====

void zz_002aaac_(void)

{
  void *__s;
  double dVar1;
  
  PTR_DAT_80433930[0x31] = 0;
  __s = (void *)(DAT_80436238 + 0xb56c00);
  gnt4_memset(__s,0,0x100000);
  DAT_803c0604 = 0x280;
  DAT_803c0606 = 0xe0;
  DAT_803c05f0 = &DAT_803c05d0;
  DAT_803c0600 = 6;
  gnt4_GXInitTexObj_bl((uint *)&DAT_803c05d0,(uint)__s,0x280,0xe0,6,0,0,'\0');
  dVar1 = (double)FLOAT_80436f18;
  gnt4_GXInitTexObjLOD_bl(dVar1,dVar1,dVar1,(uint *)&DAT_803c05d0,0,0,0,'\0',0);
  return;
}



// ==== 8002ab70  zz_002ab70_ ====

void zz_002ab70_(void)

{
  if ((PTR_DAT_80433930[0x31] & 1) == 0) {
    gnt4_GXSetTexCopySrc_bl(0,0,0x280,0xe0);
  }
  else {
    gnt4_GXSetTexCopySrc_bl(0,0xe0,0x280,0xe0);
  }
  gnt4_GXSetTexCopyDst_bl(0x280,0xe0,6,0);
  gnt4_GXCopyTex_bl(DAT_80436238 + 0xb56c00,0);
  gnt4_GXPixModeSync_bl();
  gnt4_DCFlushRange_bl(DAT_80436238 + 0xb56c00,0x8c000);
  gnt4_GXInvalidateTexAll_bl();
  return;
}



// ==== 8002ac10  zz_002ac10_ ====

void zz_002ac10_(void)

{
  if (DAT_803c0590 != 0) {
    gnt4_GXSetTexCopySrc_bl
              ((uint)DAT_803c05a0,(uint)DAT_803c05a2,(uint)DAT_803c05a4,(uint)DAT_803c05a6);
    gnt4_GXSetTexCopyDst_bl(DAT_803c05a4,DAT_803c05a6,DAT_803c059c,0);
    gnt4_GXCopyTex_bl(DAT_803c0594,0);
    gnt4_GXPixModeSync_bl();
    gnt4_DCFlushRange_bl(DAT_803c0594,DAT_803c05b8);
    gnt4_GXInvalidateTexAll_bl();
    DAT_803c0590 = DAT_803c0590 & 0xffffff7f;
  }
  return;
}



// ==== 8002acd0  zz_002acd0_ ====

void zz_002acd0_(void)

{
  ushort uVar1;
  float afStack_38 [13];
  
  uVar1 = ~-((byte)PTR_DAT_80433930[0x31] & 1) & 0xe0;
  gnt4_GXSetCullMode_bl(2);
  gnt4_GXSetBlendMode_bl(0,0,0,0);
  gnt4_GXSetZMode_bl(1,7,0);
  gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(0xb,1);
  gnt4_GXSetVtxDesc_bl(0xd,1);
  gnt4_GXSetVtxAttrFmt_bl(0,9,0,3,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xd,1,3,0);
  gnt4_GXSetNumChans_bl(1);
  gnt4_GXSetNumTexGens_bl(1);
  gnt4_GXSetNumTevStages_bl(1);
  gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
  gnt4_GXSetTevOp_bl(0,0);
  gnt4_GXSetTevOrder_bl(0,0,0,4);
  gnt4_GXLoadTexObj_bl((uint *)&DAT_803c05d0,0);
  gnt4_PSMTXIdentity_bl(afStack_38);
  gnt4_GXLoadPosMtxImm_bl(afStack_38,0);
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_GXLoadTexMtxImm_bl(afStack_38,0x1e,1);
  gnt4_GXSetTexCoordGen2_bl(0,1,4,0x1e,0,0x7d);
  gnt4_GXBegin_bl(0x80,0,4);
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = uVar1;
  DAT_cc008000 = 0xffffffff;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 0x280;
  DAT_cc008000._0_2_ = uVar1;
  DAT_cc008000 = 0xffffffff;
  DAT_cc008000._0_2_ = 1;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 0x280;
  DAT_cc008000._0_2_ = uVar1 + 0xe0;
  DAT_cc008000 = 0xffffffff;
  DAT_cc008000._0_2_ = 1;
  DAT_cc008000._0_2_ = 1;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = uVar1 + 0xe0;
  DAT_cc008000 = 0xffffffff;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 1;
  return;
}



// ==== 8002aee0  zz_002aee0_ ====

void zz_002aee0_(void *param_1)

{
  double dVar1;
  
  gnt4_memset(&DAT_803c0590,0,0x40);
  gnt4_memcpy(&DAT_803c0590,param_1,0x20);
  DAT_803c0590 = DAT_803c0590 | 0x80;
  DAT_803c0594 = (void *)((int)DAT_803c0594 + DAT_80436238);
  DAT_803c05b8 = gnt4_GXGetTexBufferSize_bl
                           ((uint)DAT_803c05a4,(uint)DAT_803c05a6,DAT_803c059c,'\0',0);
  gnt4_memset(DAT_803c0594,0,DAT_803c05b8);
  DAT_803c05b0 = (uint *)&DAT_803c0570;
  gnt4_GXInitTexObj_bl
            ((uint *)&DAT_803c0570,(uint)DAT_803c0594,(uint)DAT_803c05a4,(uint)DAT_803c05a6,
             DAT_803c059c,0,0,'\0');
  dVar1 = (double)FLOAT_80436f18;
  gnt4_GXInitTexObjLOD_bl(dVar1,dVar1,dVar1,DAT_803c05b0,0,0,0,'\0',0);
  return;
}



// ==== 8002affc  zz_002affc_ ====

void zz_002affc_(void)

{
  DAT_803c0590 = 0;
  return;
}



// ==== 8002b00c  zz_002b00c_ ====

void zz_002b00c_(double param_1)

{
  if (DAT_803c0590 == 0) {
    return;
  }
  DAT_803c0598 = (float)param_1;
  return;
}



// ==== 8002b024  zz_002b024_ ====

uint zz_002b024_(void)

{
  return DAT_803c0590 & 0xffffff7f;
}



// ==== 8002b034  zz_002b034_ ====

void zz_002b034_(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  short sVar5;
  float afStack_48 [13];
  
  if ((DAT_803c0590 & 0x80) == 0) {
    gnt4_GXSetCullMode_bl(2);
    gnt4_GXSetBlendMode_bl(1,4,5,0);
    gnt4_GXSetZMode_bl(1,7,0);
    gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9,1);
    gnt4_GXSetVtxDesc_bl(0xb,1);
    gnt4_GXSetVtxDesc_bl(0xd,1);
    gnt4_GXSetVtxAttrFmt_bl(0,9,0,3,0);
    gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
    gnt4_GXSetVtxAttrFmt_bl(0,0xd,1,3,0);
    gnt4_GXSetNumChans_bl(1);
    gnt4_GXSetNumTexGens_bl(1);
    gnt4_GXSetNumTevStages_bl(1);
    gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
    gnt4_GXSetTevOp_bl(0,0);
    gnt4_GXSetTevOrder_bl(0,0,0,4);
    gnt4_GXLoadTexObj_bl(DAT_803c05b0,0);
    gnt4_PSMTXIdentity_bl(afStack_48);
    gnt4_GXLoadPosMtxImm_bl(afStack_48,0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXLoadTexMtxImm_bl(afStack_48,0x1e,1);
    gnt4_GXSetTexCoordGen2_bl(0,1,4,0x1e,0,0x7d);
    uVar4 = gnt4___cvt_fp2unsigned_bl((double)(FLOAT_80436f38 * DAT_803c0598));
    sVar2 = DAT_803c05aa;
    sVar1 = DAT_803c05a8;
    uVar4 = uVar4 & 0xff | 0xffffff00;
    sVar5 = DAT_803c05a8 + DAT_803c05ac;
    sVar3 = DAT_803c05aa + DAT_803c05ae;
    gnt4_GXBegin_bl(0x80,0,4);
    DAT_cc008000._0_2_ = sVar1;
    DAT_cc008000._0_2_ = sVar2;
    DAT_cc008000 = uVar4;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = sVar5;
    DAT_cc008000._0_2_ = sVar2;
    DAT_cc008000 = uVar4;
    DAT_cc008000._0_2_ = 1;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = sVar5;
    DAT_cc008000._0_2_ = sVar3;
    DAT_cc008000 = uVar4;
    DAT_cc008000._0_2_ = 1;
    DAT_cc008000._0_2_ = 1;
    DAT_cc008000._0_2_ = sVar1;
    DAT_cc008000._0_2_ = sVar3;
    DAT_cc008000 = uVar4;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 1;
  }
  return;
}



// ==== 8002b27c  zz_002b27c_ ====

void zz_002b27c_(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  double dVar2;
  
  DAT_803b0338 = &DAT_803b02f8;
  DAT_803b034c = (undefined2)param_3;
  DAT_803b034e = (undefined2)param_4;
  DAT_803b0348 = 1;
  DAT_803b033c = 0;
  gnt4_GXInitTexObj_bl((uint *)&DAT_803b02f8,param_1,param_3 & 0xffff,param_4 & 0xffff,1,0,0,'\0');
  dVar2 = (double)FLOAT_80436f18;
  gnt4_GXInitTexObjLOD_bl(dVar2,dVar2,dVar2,(uint *)&DAT_803b02f8,0,0,0,'\0',0);
  uVar1 = (int)param_3 / 2 + 0x1fU & 0xffe0;
  DAT_803b0350 = &DAT_803b0318;
  DAT_803b0364 = (undefined2)uVar1;
  DAT_803b0366 = (undefined2)((int)param_4 / 2);
  DAT_803b0360 = 3;
  DAT_803b0354 = 0;
  DAT_80436120 = param_1;
  gnt4_GXInitTexObj_bl((uint *)&DAT_803b0318,param_2,uVar1,(int)param_4 / 2 & 0xffff,3,0,0,'\0');
  dVar2 = (double)FLOAT_80436f18;
  gnt4_GXInitTexObjLOD_bl(dVar2,dVar2,dVar2,(uint *)&DAT_803b0318,0,0,0,'\0',0);
  uRam80436124 = param_2;
  return;
}



// ==== 8002b3e8  FUN_8002b3e8 ====

void FUN_8002b3e8(uint param_1,uint param_2)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  gnt4_GXSetNumTexGens_bl(2);
  gnt4_GXSetTexCoordGen2_bl(0,1,4,0x3c,0,0x7d);
  gnt4_GXSetTexCoordGen2_bl(1,1,4,0x3c,0,0x7d);
  gnt4_GXSetNumTevStages_bl(4);
  gnt4_GXSetTevOrder_bl(0,0,param_2,0xff);
  gnt4_GXSetTevColorIn_bl(0,0xf,8,0xe,2);
  gnt4_GXSetTevColorOp_bl(0,0,0,0,0,0);
  gnt4_GXSetTevAlphaIn_bl(0,7,4,6,1);
  gnt4_GXSetTevAlphaOp_bl(0,1,0,0,0,0);
  gnt4_GXSetTevKColorSel_bl(0,0xc);
  gnt4_GXSetTevKAlphaSel_bl(0,0x1c);
  gnt4_GXSetTevSwapMode_bl(0,0,1);
  gnt4_GXSetTevOrder_bl(1,1,param_1,0xff);
  gnt4_GXSetTevColorIn_bl(1,0xf,8,0xe,0);
  gnt4_GXSetTevColorOp_bl(1,0,0,1,0,0);
  gnt4_GXSetTevAlphaIn_bl(1,7,4,6,0);
  gnt4_GXSetTevAlphaOp_bl(1,0,0,1,0,0);
  gnt4_GXSetTevKColorSel_bl(1,0xd);
  gnt4_GXSetTevKAlphaSel_bl(1,0x1d);
  gnt4_GXSetTevSwapMode_bl(1,0,0);
  gnt4_GXSetTevOrder_bl(2,0,param_2,0xff);
  gnt4_GXSetTevColorIn_bl(2,0xf,8,0xe,0);
  gnt4_GXSetTevColorOp_bl(2,0,0,0,1,0);
  gnt4_GXSetTevAlphaIn_bl(2,7,4,6,0);
  gnt4_GXSetTevAlphaOp_bl(2,1,0,0,1,0);
  gnt4_GXSetTevKColorSel_bl(2,0xe);
  gnt4_GXSetTevKAlphaSel_bl(2,0x1e);
  gnt4_GXSetTevSwapMode_bl(2,0,2);
  gnt4_GXSetTevOrder_bl(3,0xff,0xff,0xff);
  gnt4_GXSetTevColorIn_bl(3,0,1,0xe,0xf);
  gnt4_GXSetTevColorOp_bl(3,0,0,0,1,0);
  gnt4_GXSetTevAlphaIn_bl(3,7,7,7,7);
  gnt4_GXSetTevAlphaOp_bl(3,0,0,0,1,0);
  gnt4_GXSetTevSwapMode_bl(3,0,0);
  gnt4_GXSetTevKColorSel_bl(3,0xf);
  local_18 = DAT_80436f3c;
  local_14 = DAT_80436f40;
  gnt4_GXSetTevColorS10_bl(1,(short *)&local_18);
  local_1c = DAT_80436f44;
  gnt4_GXSetTevKColor_bl(0,(byte *)&local_1c);
  local_20 = DAT_80436f48;
  gnt4_GXSetTevKColor_bl(1,(byte *)&local_20);
  local_24 = DAT_80436f4c;
  gnt4_GXSetTevKColor_bl(2,(byte *)&local_24);
  local_28 = DAT_80436f50;
  gnt4_GXSetTevKColor_bl(3,(byte *)&local_28);
  gnt4_GXSetTevSwapModeTable_bl(0,0,1,2,3);
  gnt4_GXSetTevSwapModeTable_bl(1,0,3,3,3);
  gnt4_GXSetTevSwapModeTable_bl(2,0,0,3,0);
  gnt4_GXSetNumChans_bl(0);
  gnt4_GXSetNumIndStages_bl(0);
  return;
}



// ==== 8002b7ac  FUN_8002b7ac ====

/* WARNING: Removing unreachable block (ram,0x8002bacc) */
/* WARNING: Removing unreachable block (ram,0x8002bac4) */
/* WARNING: Removing unreachable block (ram,0x8002b7c4) */
/* WARNING: Removing unreachable block (ram,0x8002b7bc) */

void FUN_8002b7ac(uint param_1,uint param_2,short param_3,short param_4,short param_5,short param_6)

{
  double dVar1;
  double dVar2;
  uint3 local_98;
  undefined4 local_94;
  float afStack_90 [12];
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  gnt4_GXInvalidateTexAll_bl();
  uStack_5c = param_1 ^ 0x80000000;
  uStack_54 = (uint)DAT_803b034c;
  uStack_4c = param_2 ^ 0x80000000;
  uStack_44 = (uint)DAT_803b034e;
  local_60 = 0x43300000;
  local_58 = 0x43300000;
  local_50 = 0x43300000;
  dVar2 = (double)((float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80436f60) /
                  (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80436f30));
  local_48 = 0x43300000;
  dVar1 = (double)((float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80436f60) /
                  (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80436f30));
  gnt4_GXSetCullMode_bl(0);
  gnt4_GXSetZMode_bl(1,7,0);
  gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
  gnt4_GXLoadTexObj_bl((uint *)&DAT_803b02f8,0);
  gnt4_GXLoadTexObj_bl((uint *)&DAT_803b0318,1);
  FUN_8002b3e8(0,1);
  gnt4_GXSetBlendMode_bl(1,1,0,0);
  gnt4_PSMTXIdentity_bl(afStack_90);
  gnt4_GXLoadTexMtxImm_bl(afStack_90,0x1e,1);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(0xd,1);
  gnt4_GXSetVtxAttrFmt_bl(0,9,1,3,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xd,1,4,0);
  gnt4_GXLoadPosMtxImm_bl(afStack_90,0);
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_GXBegin_bl(0x80,0,4);
  DAT_cc008000._0_2_ = param_3;
  DAT_cc008000._0_2_ = param_4;
  DAT_cc008000._0_2_ = 1;
  DAT_cc008000 = FLOAT_80436f18;
  DAT_cc008000 = FLOAT_80436f18;
  DAT_cc008000._0_2_ = param_3 + param_5;
  DAT_cc008000._0_2_ = param_4;
  DAT_cc008000._0_2_ = 1;
  DAT_cc008000 = (float)dVar2;
  DAT_cc008000 = FLOAT_80436f18;
  DAT_cc008000._0_2_ = param_3 + param_5;
  DAT_cc008000._0_2_ = param_4 + param_6;
  DAT_cc008000._0_2_ = 1;
  DAT_cc008000 = (float)dVar2;
  DAT_cc008000 = (float)dVar1;
  DAT_cc008000._0_2_ = param_3;
  DAT_cc008000._0_2_ = param_4 + param_6;
  DAT_cc008000._0_2_ = 1;
  DAT_cc008000 = FLOAT_80436f18;
  DAT_cc008000 = (float)dVar1;
  local_94 = DAT_8043d500;
  gnt4_GXSetTevSwapMode_bl(0,0,0);
  gnt4_GXSetAlphaCompare_bl(7,0,0,7,0);
  _local_98 = local_94;
  gnt4_GXSetFog_bl((double)FLOAT_80436f18,(double)FLOAT_80436f54,(double)FLOAT_80436f58,
                   (double)FLOAT_80436f54,0,&local_98);
  gnt4_GXSetFogRangeAdj_bl(0,0,(ushort *)0x0);
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
  gnt4_GXSetColorUpdate_bl(1);
  gnt4_GXSetAlphaUpdate_bl(1);
  return;
}



// ==== 8002bae8  zz_002bae8_ ====

void zz_002bae8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined8 uVar1;
  
  uVar1 = zz_0271264_(0);
  zz_0270bd4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(undefined4 *)0x0);
  return;
}



// ==== 8002bb14  battle_frame_target_action_dispatch ====

/* GF_ALIAS: battle_frame_target_action_dispatch
 * Evidence: per-frame active-borg loop over DAT_803c4e84 stride 0x1e00. Resets per-slot
 * target/effect globals (DAT_803b06a8, DAT_8043612c, DAT_80436134/3c/44/4c),
 * runs hit/contact passes, applies the signed param-tier delta through apply_actor_param_tier_delta_63,
 * consumes slot target pointers via react_to_slot_target_object, then dispatches slot action update
 * through dispatch_slot_action_update.
 * Field aliases: actor+0x3e4 active_slot_index; actor+0x88 match_side_from_slot_table;
 * actor+2000 last_enemy_slot; actor+0x7d1 last_enemy_slot_timer.
 */

/* WARNING: Removing unreachable block (ram,0x8002c978) */
/* WARNING: Removing unreachable block (ram,0x8002c970) */
/* WARNING: Removing unreachable block (ram,0x8002c968) */
/* WARNING: Removing unreachable block (ram,0x8002bb34) */
/* WARNING: Removing unreachable block (ram,0x8002bb2c) */
/* WARNING: Removing unreachable block (ram,0x8002bb24) */

void battle_frame_target_action_dispatch(undefined8 param_1,double param_2,double param_3)

{
  bool bVar1;
  float fVar2;
  char cVar3;
  byte bVar4;
  short sVar5;
  float fVar6;
  undefined1 *puVar7;
  uint uVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  undefined *puVar12;
  int iVar13;
  float *pfVar14;
  float *pfVar15;
  int *piVar16;
  float *pfVar17;
  float *pfVar18;
  undefined2 *puVar19;
  int *piVar20;
  int iVar21;
  short *psVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  float fStack_88;
  float local_84;
  float local_7c;
  float local_78;
  undefined4 local_74;
  float local_70 [7];
  
  DAT_803b068c = *(undefined4 *)(PTR_DAT_80433934 + 0x118);
  psVar22 = &DAT_80436154;
  puVar19 = &DAT_803b069c;
  iVar13 = 0;
  DAT_80436154 = 0;
  DAT_803b0690 = *(undefined4 *)(PTR_DAT_80433934 + 0x154);
  uRam80436156 = 0;
  DAT_803b0694 = *(undefined4 *)(PTR_DAT_80433934 + 400);
  uRam80436158 = 0;
  DAT_803b0698 = *(undefined4 *)(PTR_DAT_80433934 + 0x1cc);
  uRam8043615a = 0;
  DAT_80436128 = 0;
  pcVar10 = DAT_803c4e84;
  do {
    if (*pcVar10 != '\0') {
      if (pcVar10[0x7d1] < '\x01') {
        pcVar10[0x7d1] = '\0';
        pcVar10[2000] = -1;
      }
      else {
        pcVar10[0x7d1] = pcVar10[0x7d1] + -1;
      }
      (&DAT_8043614c)[pcVar10[0x3e4]] = 0;
      zz_002cda4_((int)pcVar10);
      *puVar19 = *(undefined2 *)(pcVar10 + 0x1c6);
      if (pcVar10[0x436] != '\0') {
        DAT_80436128 = 1;
      }
      if (*(ushort *)(pcVar10 + 0x4fc) <= *(ushort *)(pcVar10 + 0x4f4)) {
        *(ushort *)(pcVar10 + 0x4fc) = *(ushort *)(pcVar10 + 0x4f4);
      }
      if (*(short *)(pcVar10 + 0x4f8) == 0) {
        pcVar10[0x4f4] = '\0';
        pcVar10[0x4f5] = '\0';
      }
      else {
        *(short *)(pcVar10 + 0x4f8) = *(short *)(pcVar10 + 0x4f8) + -1;
      }
      if (*(ushort *)(pcVar10 + 0x4fe) <= *(ushort *)(pcVar10 + 0x4f6)) {
        *(ushort *)(pcVar10 + 0x4fe) = *(ushort *)(pcVar10 + 0x4f6);
      }
      if (*(short *)(pcVar10 + 0x4fa) == 0) {
        pcVar10[0x4f6] = '\0';
        pcVar10[0x4f7] = '\0';
      }
      else {
        *(short *)(pcVar10 + 0x4fa) = *(short *)(pcVar10 + 0x4fa) + -1;
      }
      pcVar10[0x6fd] = '\0';
      pcVar10[0x70c] = '\0';
      pcVar10[0x70d] = '\0';
      fVar2 = FLOAT_80436f68;
      pcVar10[0x7d4] = '\0';
      fVar6 = FLOAT_80436f6c;
      pcVar10[0x599] = '\0';
      (&DAT_80436144)[pcVar10[0x3e4]] = 0;
      *(undefined4 *)(&DAT_803b06a8 + pcVar10[0x3e4] * 4) = 0;
      (&DAT_8043613c)[pcVar10[0x3e4]] = 0;
      (&DAT_80436134)[pcVar10[0x3e4]] = 0;
      (&DAT_803b0644)[pcVar10[0x3e4]] = fVar2;
      (&DAT_8043612c)[pcVar10[0x3e4]] = 0;
      *(undefined2 *)(&DAT_803b0638 + pcVar10[0x3e4] * 2) = 0;
      *(float *)(&DAT_803b0708 + pcVar10[0x3e4] * 4) = fVar6;
    }
    iVar13 = iVar13 + 1;
    pcVar10 = pcVar10 + 0x1e00;
    puVar19 = puVar19 + 1;
  } while (iVar13 < 6);
  zz_002cc78_(0x28);
  zz_002cc78_(0x20);
  zz_002cc78_(0);
  zz_002cc78_(0x10);
  zz_002cc78_(8);
  zz_002cc78_(0x18);
  iVar13 = 0;
  puVar7 = &DAT_803c73b0;
  do {
    zz_002cda4_((int)puVar7);
    iVar13 = iVar13 + 1;
    puVar7 = puVar7 + 0x3e4;
  } while (iVar13 < 0xc);
  zz_002cf80_();
  zz_002d35c_();
  zz_002d58c_();
  zz_002d198_();
  zz_002e1c8_();
  mutual_actor_contact_mask_update();
  pfVar14 = local_70;
  piVar16 = &DAT_803b0674;
  pfVar15 = (float *)&DAT_803b065c;
  dVar25 = (double)FLOAT_80436f68;
  iVar13 = 0;
  pcVar10 = DAT_803c4e84;
  pfVar17 = pfVar14;
  pfVar18 = pfVar15;
  piVar20 = piVar16;
  do {
    *pfVar18 = (float)dVar25;
    *piVar20 = 0;
    if ((*pcVar10 != '\0') && (pcVar10[0x1dd] != '\0')) {
      dVar23 = FUN_8003d6e4((double)*(float *)(pcVar10 + 0x668),(int)pcVar10,
                            (float *)(pcVar10 + 0x20));
      cVar3 = pcVar10[0x1db];
      *pfVar17 = (float)dVar23;
      param_2 = (double)*pfVar17;
      if ((cVar3 != '\0') && (*(char *)(*(int *)(pcVar10 + 0x1e4) + 0x1dd) != '\0')) {
        param_2 = (double)(float)(param_2 + (double)*(float *)(*(int *)(pcVar10 + 0x1e4) + 0x1d0));
      }
      if (*(float *)(pcVar10 + 0x24) < (float)(param_2 - (double)*(float *)(pcVar10 + 0x6d0))) {
        *piVar20 = 1;
        *pfVar18 = (float)(param_2 - (double)*(float *)(pcVar10 + 0x6d0)) -
                   *(float *)(pcVar10 + 0x24);
        *(float *)(pcVar10 + 0x24) = (float)(param_2 - (double)*(float *)(pcVar10 + 0x6d0));
        dVar23 = gnt4_PSVECSquareMag_bl((float *)(pcVar10 + 0x1cc));
        if (((double)FLOAT_80436f68 < dVar23) &&
           (gnt4_PSVECNormalize_bl((float *)(pcVar10 + 0x1cc),&local_7c), local_78 <= FLOAT_80436f70
           )) {
          pcVar10[0x1df] = '\x02';
        }
      }
    }
    iVar13 = iVar13 + 1;
    pfVar18 = pfVar18 + 1;
    pfVar17 = pfVar17 + 1;
    pcVar10 = pcVar10 + 0x1e00;
    piVar20 = piVar20 + 1;
  } while (iVar13 < 6);
  dVar25 = (double)FLOAT_80436f74;
  pfVar17 = (float *)&DAT_803b0644;
  iVar13 = 0;
  pcVar10 = DAT_803c4e84;
  do {
    *pfVar17 = (float)((double)*pfVar17 * dVar25);
    if ((*pcVar10 != '\0') && ((pcVar10[0x274] & 2U) != 0)) {
      if (*piVar16 == 0) {
        if (pcVar10[0x1db] != '\0') {
          iVar9 = *(int *)(pcVar10 + 0x1e4);
          if (*(char *)(iVar9 + 0x83) == '\0') {
            if ((&DAT_803b0674)[*(char *)(iVar9 + 0x3e4)] == 0) {
              if (((*(char *)(iVar9 + 0x1db) != '\0') &&
                  (iVar21 = *(int *)(iVar9 + 0x1e4), *(char *)(iVar21 + 0x83) == '\0')) &&
                 ((&DAT_803b0674)[*(char *)(iVar21 + 0x3e4)] != 0)) {
                dVar23 = zz_003f320_((double)(*(float *)(pcVar10 + 0x30) +
                                             *(float *)(pcVar10 + 0x6d4)),(float *)(pcVar10 + 0x20))
                ;
                param_3 = (double)(*(float *)(iVar9 + 0x24) + *(float *)(iVar9 + 0x6d0));
                dVar26 = (double)*(float *)(pcVar10 + 0xb4);
                dVar23 = (double)(float)(dVar23 - (double)(*(float *)(pcVar10 + 0x24) +
                                                          *(float *)(pcVar10 + 0x6d0)));
                param_2 = (double)FLOAT_80436f78;
                dVar27 = (double)(float)((double)(*(float *)(pcVar10 + 0x24) +
                                                 *(float *)(pcVar10 + 0x6d0)) - param_3);
                fVar2 = (float)(param_3 -
                               (double)(*(float *)(iVar21 + 0x24) + *(float *)(iVar21 + 0x6d0)));
                if (((dVar26 < param_2) || (param_2 <= (double)*(float *)(iVar9 + 0xb4))) ||
                   (param_2 <= (double)*(float *)(iVar21 + 0xb4))) {
                  param_2 = (double)FLOAT_80436f78;
                  if (((param_2 <= dVar26) || ((double)*(float *)(iVar9 + 0xb4) < param_2)) ||
                     (param_2 <= (double)*(float *)(iVar21 + 0xb4))) {
                    param_2 = (double)FLOAT_80436f78;
                    if (((param_2 <= dVar26) || (param_2 <= (double)*(float *)(iVar9 + 0xb4))) ||
                       ((double)*(float *)(iVar21 + 0xb4) < param_2)) {
                      dVar24 = (double)FLOAT_80436f78;
                      if (((dVar26 < dVar24) || ((double)*(float *)(iVar9 + 0xb4) < dVar24)) ||
                         (dVar24 <= (double)*(float *)(iVar21 + 0xb4))) {
                        dVar24 = (double)FLOAT_80436f78;
                        if (((dVar26 < dVar24) || (dVar24 <= (double)*(float *)(iVar9 + 0xb4))) ||
                           ((double)*(float *)(iVar21 + 0xb4) < dVar24)) {
                          dVar24 = (double)FLOAT_80436f78;
                          if (((dVar24 <= dVar26) || ((double)*(float *)(iVar9 + 0xb4) < dVar24)) ||
                             ((double)*(float *)(iVar21 + 0xb4) < dVar24)) {
                            param_2 = (double)(float)(&DAT_803b065c)[*(char *)(iVar21 + 0x3e4)];
                            dVar26 = (double)(float)(param_2 / (double)FLOAT_80436f80);
                            param_3 = (double)(float)(dVar27 + dVar26);
                            dVar24 = (double)(float)(dVar27 / param_3);
                            dVar27 = (double)(fVar2 / (fVar2 + (float)(param_2 -
                                                                      (double)(float)(dVar26 + 
                                                  dVar26))));
                            zz_002caa8_((double)(float)(dVar23 / (double)(float)(dVar23 + dVar26)),
                                        (int)pcVar10);
                            zz_002caa8_(dVar24,iVar9);
                            zz_002caa8_(dVar27,iVar21);
                          }
                          else {
                            dVar23 = (double)(float)((double)(float)(&DAT_803b065c)
                                                                    [*(char *)(iVar21 + 0x3e4)] *
                                                    (double)FLOAT_80436f7c);
                            param_2 = (double)(float)(dVar27 + dVar23);
                            dVar23 = (double)(fVar2 / (fVar2 + (float)((double)(float)(&DAT_803b065c
                                                                                      )[*(char *)(
                                                  iVar21 + 0x3e4)] - dVar23)));
                            zz_002caa8_((double)(float)(dVar27 / param_2),iVar9);
                            zz_002caa8_(dVar23,iVar21);
                          }
                        }
                        else {
                          param_2 = (double)(float)(&DAT_803b065c)[*(char *)(iVar21 + 0x3e4)];
                          param_3 = (double)(float)(dVar23 + (double)(float)(param_2 *
                                                                            (double)FLOAT_80436f7c))
                          ;
                          dVar26 = (double)(fVar2 / (fVar2 + (float)(param_2 -
                                                                    (double)(float)(param_2 *
                                                                                   (double)
                                                  FLOAT_80436f7c))));
                          zz_002caa8_((double)(float)(dVar23 / param_3),(int)pcVar10);
                          zz_002caa8_(dVar26,iVar21);
                        }
                      }
                      else {
                        param_2 = (double)(float)(&DAT_803b065c)[*(char *)(iVar21 + 0x3e4)];
                        param_3 = (double)(float)(dVar23 + (double)(float)(param_2 *
                                                                          (double)FLOAT_80436f7c));
                        dVar26 = (double)(float)(dVar27 / (double)(float)(dVar27 + (double)(float)(
                                                  param_2 - (double)(float)(param_2 *
                                                                           (double)FLOAT_80436f7c)))
                                                );
                        zz_002caa8_((double)(float)(dVar23 / param_3),(int)pcVar10);
                        zz_002caa8_(dVar26,iVar9);
                      }
                    }
                    else {
                      zz_002caa8_((double)(fVar2 / (fVar2 + (float)(&DAT_803b065c)
                                                                   [*(char *)(iVar21 + 0x3e4)])),
                                  iVar21);
                    }
                  }
                  else {
                    zz_002caa8_((double)(float)(dVar27 / (double)(float)(dVar27 + (double)(float)(&
                                                  DAT_803b065c)[*(char *)(iVar21 + 0x3e4)])),iVar9);
                  }
                }
                else {
                  zz_002caa8_((double)(float)(dVar23 / (double)(float)(dVar23 + (double)(float)(&
                                                  DAT_803b065c)[*(char *)(iVar21 + 0x3e4)])),
                              (int)pcVar10);
                }
              }
            }
            else {
              dVar23 = zz_003f320_((double)(*(float *)(pcVar10 + 0x30) + *(float *)(pcVar10 + 0x6d4)
                                           ),(float *)(pcVar10 + 0x20));
              param_3 = (double)(*(float *)(pcVar10 + 0x24) + *(float *)(pcVar10 + 0x6d0));
              param_2 = (double)FLOAT_80436f78;
              dVar23 = (double)(float)(dVar23 - param_3);
              fVar2 = (float)(param_3 -
                             (double)(*(float *)(iVar9 + 0x24) + *(float *)(iVar9 + 0x6d0)));
              if (((double)*(float *)(pcVar10 + 0xb4) < param_2) ||
                 (param_2 <= (double)*(float *)(iVar9 + 0xb4))) {
                param_2 = (double)FLOAT_80436f78;
                if ((param_2 <= (double)*(float *)(pcVar10 + 0xb4)) ||
                   ((double)*(float *)(iVar9 + 0xb4) < param_2)) {
                  param_2 = (double)(float)(&DAT_803b065c)[*(char *)(iVar9 + 0x3e4)];
                  param_3 = (double)(float)(dVar23 + (double)(float)(param_2 *
                                                                    (double)FLOAT_80436f7c));
                  dVar26 = (double)(fVar2 / (fVar2 + (float)(param_2 -
                                                            (double)(float)(param_2 *
                                                                           (double)FLOAT_80436f7c)))
                                   );
                  zz_002caa8_((double)(float)(dVar23 / param_3),(int)pcVar10);
                  zz_002caa8_(dVar26,iVar9);
                }
                else {
                  zz_002caa8_((double)(fVar2 / (fVar2 + (float)(&DAT_803b065c)
                                                               [*(char *)(iVar9 + 0x3e4)])),iVar9);
                }
              }
              else {
                zz_002caa8_((double)(float)(dVar23 / (double)(float)(dVar23 + (double)(float)(&
                                                  DAT_803b065c)[*(char *)(iVar9 + 0x3e4)])),
                            (int)pcVar10);
              }
            }
          }
          if (*(char *)(iVar9 + 0x83) == '\x16') {
            dVar23 = zz_003f320_((double)(*(float *)(pcVar10 + 0x30) + *(float *)(pcVar10 + 0x6d4)),
                                 (float *)(pcVar10 + 0x20));
            param_2 = (double)*(float *)(pcVar10 + 0x24);
            dVar26 = (double)(float)(dVar23 - (double)(float)(param_2 +
                                                             (double)*(float *)(pcVar10 + 0x6d0)));
            gnt4_PSMTXMultVec_bl
                      (*(float **)(*(int *)(pcVar10 + 0x1e0) + 0x60),(float *)(pcVar10 + 0x1f8),
                       &fStack_88);
            zz_002caa8_((double)(float)((double)(float)(dVar23 - (double)local_84) / dVar26),
                        (int)pcVar10);
          }
        }
      }
      else {
        if (*pfVar15 < *pfVar17) {
          dVar26 = (double)*pfVar14;
          dVar23 = zz_003f320_((double)(*(float *)(pcVar10 + 0x30) + *(float *)(pcVar10 + 0x6d4)),
                               (float *)(pcVar10 + 0x20));
          param_2 = (double)(float)(dVar26 + (double)*(float *)(pcVar10 + 0x6d0));
          fVar2 = (float)(dVar23 - param_2) / ((float)(dVar23 - param_2) + *pfVar17);
        }
        else {
          dVar23 = zz_003f320_((double)(*(float *)(pcVar10 + 0x30) + *(float *)(pcVar10 + 0x6d4)),
                               (float *)(pcVar10 + 0x20));
          param_3 = (double)*(float *)(pcVar10 + 0x24);
          param_2 = (double)(float)(param_3 + (double)*(float *)(pcVar10 + 0x6d0));
          fVar2 = (float)(dVar23 - param_2) / ((float)(dVar23 - param_2) + *pfVar15);
        }
        zz_002caa8_((double)fVar2,(int)pcVar10);
      }
    }
    iVar13 = iVar13 + 1;
    piVar16 = piVar16 + 1;
    pfVar15 = pfVar15 + 1;
    pfVar14 = pfVar14 + 1;
    pcVar10 = pcVar10 + 0x1e00;
    pfVar17 = pfVar17 + 1;
  } while (iVar13 < 6);
  zz_002ce44_();
  collision_hit_pair_pass_active_vs_borgs();
  collision_hit_pair_pass_object_lists();
  dVar25 = (double)collision_hit_pair_pass_active_vs_secondary();
  iVar13 = 0;
  pcVar10 = DAT_803c4e84;
  do {
    if (*pcVar10 != '\0') {
      bVar1 = pcVar10[0x1dd] != '\0';
      if ((pcVar10[0x663] != '\0') && (pcVar10[0x18] == '\x01')) {
        pcVar10[0x1da] = pcVar10[0x1da] | 1;
        pcVar10[0x1c6] = '\0';
        pcVar10[0x1c7] = '\0';
        dVar25 = (double)zz_002f8dc_((int)pcVar10,pcVar10);
      }
      if ((pcVar10[0x1da] & 1U) != 0) {
        if (pcVar10[0x6cb] != '\0') {
          pcVar10[0x6cb] = '\0';
        }
        if (*(short *)(pcVar10 + 0x1c6) < 1) {
          dVar25 = (double)zz_005bbc0_((int)pcVar10);
          iVar9 = 0;
          pcVar11 = DAT_803c4e84;
          do {
            if (((*pcVar11 != '\0') && (0 < *(short *)(pcVar11 + 0x1c6))) &&
               ((*(short *)(pcVar11 + 1000) == 0x701 || (*(short *)(pcVar11 + 1000) == 0x708)))) {
              dVar25 = (double)zz_0159168_(pcVar10,(int)pcVar11);
            }
            iVar9 = iVar9 + 1;
            pcVar11 = pcVar11 + 0x1e00;
          } while (iVar9 < 6);
        }
        else {
          bVar4 = pcVar10[0x1da];
          if ((bVar4 & 2) == 0) {
            if (((bVar4 & 0x20) != 0) || ((bVar4 & 0x40) != 0)) {
              apply_actor_param_tier_delta_63((int)pcVar10,(int)(char)(&DAT_8043612c)[pcVar10[0x3e4]]);
            }
            iVar9 = (int)pcVar10[0x3e4];
            if ((&DAT_8043613c)[iVar9] == '\0') {
              if ((&DAT_80436134)[iVar9] == '\0') {
                if ((pcVar10[0x1da] & 4U) == 0) {
                  if (pcVar10[0x599] == '\0') {
                    if ((*(short *)(pcVar10 + 0x6c6) < 1) ||
                       (((((int)pcVar10[0x6fd] & 2U) != 0 && (((int)pcVar10[0x6fd] & 0x80U) != 0))
                        || ((pcVar10[0x1da] & 0x10U) != 0)))) {
                      zz_003d3e8_((int)pcVar10);
                      dVar25 = (double)zz_005c290_((int)pcVar10);
                    }
                    else {
                      dVar25 = (double)dispatch_slot_action_update((int)pcVar10,0);
                    }
                  }
                  else {
                    dVar25 = (double)zz_005c290_((int)pcVar10);
                  }
                }
                else {
                  start_forced_move_to_point((int)pcVar10,(undefined4 *)(&DAT_803b06c0 + iVar9 * 0xc),2);
                  dVar25 = (double)dispatch_slot_action_update((int)pcVar10,0);
                }
              }
              else {
                start_status_reaction_by_side((int)pcVar10,1);
                dVar25 = (double)dispatch_slot_action_update((int)pcVar10,0);
              }
            }
            else {
              start_status_reaction_by_side((int)pcVar10,0);
              dVar25 = (double)dispatch_slot_action_update((int)pcVar10,0);
            }
          }
          else if (*(short *)(pcVar10 + 0x7dc) < 1) {
            dVar25 = (double)zz_003d444_((int)pcVar10);
            if ((*(short *)(pcVar10 + 1000) != 0x302) && (*(short *)(pcVar10 + 1000) != 0x205)) {
              dVar25 = (double)zz_005c290_((int)pcVar10);
            }
          }
        }
        bVar1 = true;
      }
      if (0 < *(short *)(pcVar10 + 0x1c6)) {
        if (*(int *)(&DAT_803b06a8 + pcVar10[0x3e4] * 4) == 0) {
          if ((pcVar10[0x1d9] & 4U) != 0) {
            dVar25 = (double)start_forced_move_to_point((int)pcVar10,
                                         (undefined4 *)(&DAT_803b06c0 + pcVar10[0x3e4] * 0xc),2);
            bVar1 = true;
          }
        }
        else {
          dVar25 = (double)react_to_slot_target_object((int)pcVar10,*(int *)(&DAT_803b06a8 + pcVar10[0x3e4] * 4));
          bVar1 = true;
        }
        if (((pcVar10[0x274] & 1U) != 0) && ('\x02' < (char)(&DAT_80436144)[pcVar10[0x3e4]])) {
          local_7c = *(float *)(pcVar10 + 0x1cc);
          local_78 = *(float *)(pcVar10 + 0x1d0);
          local_74 = *(undefined4 *)(pcVar10 + 0x1d4);
          dVar25 = gnt4_PSVECSquareMag_bl(&local_7c);
          if ((double)FLOAT_80436f68 < dVar25) {
            gnt4_PSVECNormalize_bl(&local_7c,&local_7c);
            dVar25 = (double)local_78;
            if ((double)FLOAT_80436f84 <= dVar25) {
              pcVar10[0x7d4] = '\x01';
            }
          }
        }
        if ((*(short *)(pcVar10 + 1000) == 0x702) || (*(short *)(pcVar10 + 1000) == 0x70a)) {
          *(short *)(pcVar10 + 0x1c6) =
               *(short *)(pcVar10 + 0x1c6) + *(short *)(&DAT_803b0638 + pcVar10[0x3e4] * 2);
          if (*(short *)(pcVar10 + 0x1c4) <= *(short *)(pcVar10 + 0x1c6)) {
            *(short *)(pcVar10 + 0x1c6) = *(short *)(pcVar10 + 0x1c4);
          }
        }
      }
      uVar8 = FUN_8005a580((int)pcVar10);
      if (uVar8 != 0) {
        bVar1 = true;
      }
      if (bVar1) {
        dVar25 = (double)zz_00466dc_((int)pcVar10);
      }
    }
    iVar13 = iVar13 + 1;
    pcVar10 = pcVar10 + 0x1e00;
  } while (iVar13 < 6);
  iVar13 = 0;
  puVar12 = PTR_DAT_80433934 + 0xf4;
  do {
    if (puVar12[0x10] == '\0') {
      sVar5 = *psVar22;
      if (sVar5 < 0) {
        if ((int)(uint)*(ushort *)(puVar12 + 0x32) < -(int)sVar5) {
          *(undefined2 *)(puVar12 + 0x32) = 0;
        }
        else {
          *(ushort *)(puVar12 + 0x32) = *(ushort *)(puVar12 + 0x32) + sVar5;
          *(short *)(puVar12 + 0x36) = *(short *)(puVar12 + 0x36) + *psVar22;
        }
      }
      else if (0 < sVar5) {
        if ((PTR_DAT_80433930[0x32] == '\0') && (iVar13 == 0)) {
          dVar25 = (double)zz_002c994_(dVar25,param_2,param_3,psVar22);
        }
        *(short *)(puVar12 + 0x32) = *(short *)(puVar12 + 0x32) + *psVar22;
        *(short *)(puVar12 + 0x36) = *(short *)(puVar12 + 0x36) + *psVar22;
        if (*(ushort *)(puVar12 + 0x30) <= *(ushort *)(puVar12 + 0x32)) {
          *(ushort *)(puVar12 + 0x32) = *(ushort *)(puVar12 + 0x30);
        }
      }
    }
    iVar13 = iVar13 + 1;
    puVar12 = puVar12 + 0x3c;
    psVar22 = psVar22 + 1;
  } while (iVar13 < 4);
  return;
}



// ==== 8002c994  zz_002c994_ ====

void zz_002c994_(undefined8 param_1,undefined8 param_2,double param_3,short *param_4)

{
  float fVar1;
  bool bVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  
  bVar2 = false;
  puVar5 = &DAT_803c4e84;
  iVar6 = 0;
  iVar7 = 6;
  puVar4 = PTR_DAT_80433934;
  do {
    if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar6) != 0) {
      if (puVar4[0xcb] == '\0') {
        if (*(char *)*puVar5 != '\0') {
          if (((char *)*puVar5)[0x18] == '\x01') {
            iVar3 = (int)(char)puVar4[0x20];
            if ((0 < iVar3) && (iVar3 < 0xe)) {
              dVar8 = (double)*(float *)(&DAT_802c7da0 + iVar3 * 4);
              if (bVar2) {
                if (param_3 <= dVar8) {
                  param_3 = dVar8;
                }
              }
              else {
                bVar2 = true;
                param_3 = dVar8;
              }
            }
          }
        }
      }
    }
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
    iVar6 = iVar6 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  if (bVar2) {
    fVar1 = (float)((double)(float)((double)CONCAT44(0x43300000,(int)*param_4 ^ 0x80000000) -
                                   DOUBLE_80436f88) * param_3);
    if (fVar1 <= FLOAT_80436f78) {
      fVar1 = FLOAT_80436f78;
    }
    *param_4 = (short)(int)fVar1;
  }
  return;
}



// ==== 8002caa8  zz_002caa8_ ====

void zz_002caa8_(double param_1,int param_2)

{
  float fVar1;
  
  *(float *)(param_2 + 0xb4) = (float)((double)*(float *)(param_2 + 0xb4) * param_1);
  *(undefined4 *)(param_2 + 0x58) = *(undefined4 *)(param_2 + 0xb4);
  *(undefined4 *)(param_2 + 0x5c) = *(undefined4 *)(param_2 + 0xb4);
  *(undefined4 *)(param_2 + 0x60) = *(undefined4 *)(param_2 + 0xb4);
  *(undefined4 *)(param_2 + 0xc0) = *(undefined4 *)(param_2 + 0xb4);
  *(undefined4 *)(param_2 + 0xc4) = *(undefined4 *)(param_2 + 0xb4);
  *(undefined1 *)(param_2 + 0x1e8) = 1;
  zz_00466dc_(param_2);
  fVar1 = FLOAT_80436f68;
  *(float *)(param_2 + 0x1cc) = FLOAT_80436f68;
  *(float *)(param_2 + 0x1d0) = fVar1;
  *(float *)(param_2 + 0x1d4) = fVar1;
  return;
}



// ==== 8002cb20  mutual_actor_contact_mask_update ====

/* GF_ALIAS: mutual_actor_contact_mask_update
 * Evidence: pairwise active-borg scan gated by mutual actor+0x71e and actor+0x71f
 * slot bitmasks before calling zz_0035ca4_ with the other actor motion vector.
 * This is a target/contact eligibility pass, not a CPU-only decision function.
 */

void mutual_actor_contact_mask_update(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = 0;
  pcVar4 = DAT_803c4e84;
  do {
    if (*pcVar4 != '\0') {
      iVar1 = 0;
      pcVar3 = DAT_803c4e84;
      do {
        if (pcVar4 != pcVar3) {
          if (*pcVar3 != '\0') {
            if (((int)pcVar4[0x71e] & 1 << (int)pcVar3[0x3e4]) != 0) {
              if (((int)pcVar3[0x71e] & 1 << (int)pcVar4[0x3e4]) != 0) {
                if (((int)pcVar4[0x71f] & 1 << (int)pcVar3[0x3e4]) != 0) {
                  if (((int)pcVar3[0x71f] & 1 << (int)pcVar4[0x3e4]) != 0) {
                    if (pcVar4[0x1dd] != '\0') {
                      if (pcVar3[0x1dd] != '\0') goto LAB_8002cc38;
                    }
                    if (pcVar4[0x1dd] == '\0') {
                      if ((pcVar3[0x1dd] != '\0') && (*(float *)(pcVar4 + 0x204) < FLOAT_80436f90))
                      {
                        zz_0035ca4_((int)pcVar4,(float *)(pcVar3 + 0x1cc));
                      }
                    }
                    else if (*(float *)(pcVar3 + 0x204) < FLOAT_80436f90) {
                      zz_0035ca4_((int)pcVar3,(float *)(pcVar4 + 0x1cc));
                    }
                  }
                }
              }
            }
          }
        }
LAB_8002cc38:
        iVar1 = iVar1 + 1;
        pcVar3 = pcVar3 + 0x1e00;
      } while (iVar1 < 6);
    }
    iVar2 = iVar2 + 1;
    pcVar4 = pcVar4 + 0x1e00;
    if (5 < iVar2) {
      return;
    }
  } while( true );
}



// ==== 8002cc78  zz_002cc78_ ====

void zz_002cc78_(uint param_1)

{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  
  pcVar1 = (char *)(&DAT_803c706c)[param_1];
  while( true ) {
    if (pcVar1 == (char *)0x0) break;
    if ((*pcVar1 != '\0') && (pcVar1[0x86] != '\0')) {
      zz_002cda4_((int)pcVar1);
    }
    pcVar1 = *(char **)(pcVar1 + 8);
  }
  if (((int)param_1 < 0x38) && ((param_1 & 7) == 0)) {
    iVar3 = 0;
    puVar2 = &DAT_803c4e84;
    do {
      if (*(char *)*puVar2 != '\0') {
        pcVar1 = (char *)(&DAT_803c7070)[param_1 + iVar3];
        while( true ) {
          if (pcVar1 == (char *)0x0) break;
          if ((*pcVar1 != '\0') && (pcVar1[0x86] != '\0')) {
            zz_002cda4_((int)pcVar1);
          }
          pcVar1 = *(char **)(pcVar1 + 8);
        }
      }
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar3 < 6);
    pcVar1 = (char *)(&DAT_803c7088)[param_1];
    while( true ) {
      if (pcVar1 == (char *)0x0) break;
      if ((*pcVar1 != '\0') && (pcVar1[0x86] != '\0')) {
        zz_002cda4_((int)pcVar1);
      }
      pcVar1 = *(char **)(pcVar1 + 8);
    }
  }
  return;
}



// ==== 8002cda4  zz_002cda4_ ====

void zz_002cda4_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80436f68;
  *(float *)(param_1 + 0x1cc) = FLOAT_80436f68;
  *(float *)(param_1 + 0x1d0) = fVar1;
  *(float *)(param_1 + 0x1d4) = fVar1;
  *(undefined1 *)(param_1 + 0x1d9) = 0;
  *(undefined1 *)(param_1 + 0x1da) = 0;
  *(undefined1 *)(param_1 + 0x1de) = *(undefined1 *)(param_1 + 0x1db);
  *(undefined1 *)(param_1 + 0x1db) = 0;
  *(undefined1 *)(param_1 + 0x1dc) = 0;
  *(undefined1 *)(param_1 + 0x1dd) = 0;
  *(undefined1 *)(param_1 + 0x280) = 0;
  *(undefined1 *)(param_1 + 0x275) = *(undefined1 *)(param_1 + 0x274);
  *(undefined1 *)(param_1 + 0x274) = 0;
  if (*(char *)(param_1 + 0x1df) != '\0') {
    *(char *)(param_1 + 0x1df) = *(char *)(param_1 + 0x1df) + -1;
  }
  *(undefined2 *)(param_1 + 0x270) = 0;
  *(undefined2 *)(param_1 + 0x286) = 0;
  if (*(char *)(param_1 + 0x2ae) != '\0') {
    *(char *)(param_1 + 0x2ae) = *(char *)(param_1 + 0x2ae) + -1;
  }
  if (*(char *)(param_1 + 0x2af) != '\0') {
    *(char *)(param_1 + 0x2af) = *(char *)(param_1 + 0x2af) + -1;
  }
  if (*(char *)(param_1 + 0x1e8) == '\0') {
    return;
  }
  *(char *)(param_1 + 0x1e8) = *(char *)(param_1 + 0x1e8) + -1;
  return;
}



// ==== 8002ce44  zz_002ce44_ ====

void zz_002ce44_(void)

{
  int iVar1;
  
  zz_002ce90_(0x30);
  zz_002ce90_(0x37);
  iVar1 = 0;
  do {
    zz_002ce90_(iVar1 + 0x31);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 6);
  return;
}



// ==== 8002ce90  zz_002ce90_ ====

void zz_002ce90_(int param_1)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = (char *)(&DAT_803c706c)[param_1];
  while( true ) {
    if (pcVar2 == (char *)0x0) break;
    if (*pcVar2 != '\0') {
      iVar1 = *(int *)(pcVar2 + 0x20);
      if (*(char *)(iVar1 + 0x1e8) == '\0') {
        if (*(char *)(iVar1 + 0x1dd) != '\0') {
          gnt4_PSVECAdd_bl((float *)(pcVar2 + 100),(float *)(iVar1 + 0x1cc),(float *)(pcVar2 + 100))
          ;
        }
        if ((*(char *)(iVar1 + 0x83) == '\0') && ((&DAT_803b0674)[*(char *)(iVar1 + 0x3e4)] != 0)) {
          *(float *)(pcVar2 + 0x68) =
               *(float *)(pcVar2 + 0x68) + (float)(&DAT_803b065c)[*(char *)(iVar1 + 0x3e4)];
        }
      }
      else {
        (*(code *)(&PTR_FUN_802cfe88)[**(byte **)(pcVar2 + 0x28)])(pcVar2);
      }
    }
    pcVar2 = *(char **)(pcVar2 + 8);
  }
  return;
}



// ==== 8002cf80  zz_002cf80_ ====

void zz_002cf80_(void)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  
  piVar2 = &DAT_803c297c;
  iVar8 = 0;
  do {
    if ((int)(uint)DAT_80436246 <= iVar8) {
      return;
    }
    iVar11 = *piVar2;
    iVar9 = *(int *)(iVar11 + 0x20);
    if (*(char *)(iVar9 + 0x83) == '\0') {
      *(float *)(&DAT_803b0708 + *(char *)(iVar9 + 0x3e4) * 4) =
           *(float *)(iVar11 + 0x68) - *(float *)(iVar11 + 0x88);
    }
    piVar12 = &DAT_803c237c;
    for (iVar7 = 0; iVar7 < (int)(uint)DAT_80436244; iVar7 = iVar7 + 1) {
      iVar10 = *piVar12;
      iVar4 = *(int *)(iVar10 + 0x20);
      if ((*(int *)(iVar11 + 0x20) != iVar4) && (iVar9 != iVar4)) {
        puVar5 = (undefined4 *)(iVar11 + 0x54);
        puVar6 = (undefined4 *)0x803b04cc;
        iVar13 = 0x2d;
        do {
          puVar1 = puVar5 + 1;
          puVar5 = puVar5 + 2;
          uVar3 = *puVar5;
          puVar6[1] = *puVar1;
          puVar6 = puVar6 + 2;
          *puVar6 = uVar3;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
        puVar5 = (undefined4 *)(iVar10 + 0x54);
        puVar6 = (undefined4 *)&DAT_803b0364;
        iVar13 = 0x2d;
        do {
          puVar1 = puVar5 + 1;
          puVar5 = puVar5 + 2;
          uVar3 = *puVar5;
          puVar6[1] = *puVar1;
          puVar6 = puVar6 + 2;
          *puVar6 = uVar3;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
        zz_003a05c_(-0x7fc4fb30,-0x7fc4fc98,iVar9,iVar4);
        if (*(char *)(iVar9 + 0x83) == '\0') {
          *(float *)(&DAT_803b0708 + *(char *)(iVar9 + 0x3e4) * 4) = DAT_803b04e0 - DAT_803b0500;
        }
        iVar13 = zz_0039f6c_(-0x7fc4fb30,-0x7fc4fc98);
        if (iVar13 != 0) {
          if ((*(char *)(iVar9 + 0x1de) != '\0') && (iVar10 == *(int *)(iVar9 + 0x1e0))) {
            if (FLOAT_80436f94 <= *(float *)(iVar9 + 0x48)) {
              if (FLOAT_80436f68 <= *(float *)(iVar9 + 0x48) - *(float *)(iVar4 + 0x48))
              goto LAB_8002d15c;
            }
          }
          zz_0030348_(&DAT_803b04d0,&DAT_803b0368,*(int *)(iVar11 + 0x58),*(int *)(iVar10 + 0x58));
          zz_00303b0_(&DAT_803b04d0,&DAT_803b0368,
                      *(int *)(iVar11 + 0x58) << 3 | *(uint *)(iVar10 + 0x58));
        }
      }
LAB_8002d15c:
      piVar12 = piVar12 + 1;
    }
    iVar8 = iVar8 + 1;
    piVar2 = piVar2 + 1;
  } while( true );
}



// ==== 8002d198  zz_002d198_ ====

void zz_002d198_(void)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  piVar2 = &DAT_803c297c;
  iVar8 = 0;
  do {
    if ((int)(uint)DAT_80436246 <= iVar8) {
      return;
    }
    iVar11 = *piVar2;
    iVar9 = *(int *)(iVar11 + 0x20);
    if ((*(char *)(iVar9 + 0x1db) == '\0') && (*(char *)(iVar9 + 0x1dd) != '\0')) {
      piVar3 = &DAT_803c237c;
      for (iVar7 = 0; iVar7 < (int)(uint)DAT_80436244; iVar7 = iVar7 + 1) {
        iVar10 = *piVar3;
        iVar12 = *(int *)(iVar10 + 0x20);
        if ((*(int *)(iVar11 + 0x20) != iVar12) && (iVar9 != iVar12)) {
          puVar5 = (undefined4 *)(iVar11 + 0x54);
          puVar6 = (undefined4 *)0x803b04cc;
          iVar13 = 0x2d;
          do {
            puVar1 = puVar5 + 1;
            puVar5 = puVar5 + 2;
            uVar4 = *puVar5;
            puVar6[1] = *puVar1;
            puVar6 = puVar6 + 2;
            *puVar6 = uVar4;
            iVar13 = iVar13 + -1;
          } while (iVar13 != 0);
          puVar5 = (undefined4 *)(iVar10 + 0x54);
          puVar6 = (undefined4 *)&DAT_803b0364;
          iVar13 = 0x2d;
          do {
            puVar1 = puVar5 + 1;
            puVar5 = puVar5 + 2;
            uVar4 = *puVar5;
            puVar6[1] = *puVar1;
            puVar6 = puVar6 + 2;
            *puVar6 = uVar4;
            iVar13 = iVar13 + -1;
          } while (iVar13 != 0);
          zz_003a05c_(-0x7fc4fb30,-0x7fc4fc98,iVar9,iVar12);
          iVar13 = zz_0039f6c_(-0x7fc4fb30,-0x7fc4fc98);
          if (iVar13 != 0) {
            if ((*(char *)(iVar9 + 0x1de) != '\0') && (iVar10 == *(int *)(iVar9 + 0x1e0))) {
              if (FLOAT_80436f94 <= *(float *)(iVar9 + 0x48)) {
                if (FLOAT_80436f68 <= *(float *)(iVar9 + 0x48) - *(float *)(iVar12 + 0x48))
                goto LAB_8002d320;
              }
            }
            zz_0030348_(&DAT_803b04d0,&DAT_803b0368,*(int *)(iVar11 + 0x58),*(int *)(iVar10 + 0x58))
            ;
            zz_00303b0_(&DAT_803b04d0,&DAT_803b0368,
                        *(int *)(iVar11 + 0x58) << 3 | *(uint *)(iVar10 + 0x58));
          }
        }
LAB_8002d320:
        piVar3 = piVar3 + 1;
      }
    }
    iVar8 = iVar8 + 1;
    piVar2 = piVar2 + 1;
  } while( true );
}



// ==== 8002d35c  zz_002d35c_ ====

void zz_002d35c_(void)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  
  piVar2 = &DAT_803c3b7c;
  iVar8 = 0;
  do {
    if ((int)(DAT_8043624c - 1) <= iVar8) {
      return;
    }
    iVar11 = *piVar2;
    if ((*(ushort *)(*(int *)(iVar11 + 0x28) + 2) & 0x800) == 0) {
      iVar9 = *(int *)(iVar11 + 0x20);
      if ((*(char *)(iVar9 + 0x281) == '\0') && (*(char *)(iVar9 + 0x83) != '\x17')) {
        iVar6 = iVar8 + 1;
        piVar12 = &DAT_803c3b7c + iVar6;
        for (; iVar6 < (int)(uint)DAT_8043624c; iVar6 = iVar6 + 1) {
          iVar10 = *piVar12;
          iVar4 = *(int *)(iVar10 + 0x20);
          if (*(int *)(iVar11 + 0x20) != iVar4) {
            if ((((*(ushort *)(*(int *)(iVar10 + 0x28) + 2) & 0x800) == 0) &&
                (*(char *)(iVar4 + 0x281) == '\0')) && (*(char *)(iVar4 + 0x83) != '\x17')) {
              if (iVar9 != iVar4) {
                if (*(char *)(iVar9 + 0x1db) != '\0') {
                  if (*(int *)(iVar9 + 0x1e0) == iVar10) goto LAB_8002d54c;
                }
                if ((*(char *)(iVar4 + 0x1db) == '\0') || (*(int *)(iVar4 + 0x1e0) != iVar11)) {
                  puVar5 = (undefined4 *)(iVar11 + 0x54);
                  puVar7 = (undefined4 *)0x803b04cc;
                  iVar13 = 0x2d;
                  do {
                    puVar1 = puVar5 + 1;
                    puVar5 = puVar5 + 2;
                    uVar3 = *puVar5;
                    puVar7[1] = *puVar1;
                    puVar7 = puVar7 + 2;
                    *puVar7 = uVar3;
                    iVar13 = iVar13 + -1;
                  } while (iVar13 != 0);
                  puVar5 = (undefined4 *)(iVar10 + 0x54);
                  puVar7 = (undefined4 *)&DAT_803b0364;
                  iVar13 = 0x2d;
                  do {
                    puVar1 = puVar5 + 1;
                    puVar5 = puVar5 + 2;
                    uVar3 = *puVar5;
                    puVar7[1] = *puVar1;
                    puVar7 = puVar7 + 2;
                    *puVar7 = uVar3;
                    iVar13 = iVar13 + -1;
                  } while (iVar13 != 0);
                  zz_003a05c_(-0x7fc4fb30,-0x7fc4fc98,iVar9,iVar4);
                  iVar13 = zz_0039f6c_(-0x7fc4fb30,-0x7fc4fc98);
                  if (iVar13 != 0) {
                    zz_0030348_(&DAT_803b04d0,&DAT_803b0368,*(int *)(iVar11 + 0x58),
                                *(int *)(iVar10 + 0x58));
                    iVar10 = zz_0030420_(&DAT_803b04d0,&DAT_803b0368,
                                         *(int *)(iVar11 + 0x58) << 3 | *(uint *)(iVar10 + 0x58));
                    if (iVar10 != 0) {
                      if (*(int *)(iVar9 + 0xcc) == iVar4) {
                        *(byte *)(iVar9 + 0x1dd) = *(byte *)(iVar9 + 0x1dd) | 0x80;
                      }
                      if (*(int *)(iVar4 + 0xcc) == iVar9) {
                        *(byte *)(iVar4 + 0x1dd) = *(byte *)(iVar4 + 0x1dd) | 0x80;
                      }
                    }
                  }
                }
              }
            }
          }
LAB_8002d54c:
          piVar12 = piVar12 + 1;
        }
      }
    }
    iVar8 = iVar8 + 1;
    piVar2 = piVar2 + 1;
  } while( true );
}



// ==== 8002d58c  zz_002d58c_ ====

void zz_002d58c_(void)

{
  undefined4 *puVar1;
  char cVar2;
  ushort uVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  int iVar15;
  
  piVar4 = &DAT_803c357c;
  iVar10 = 0;
  do {
    if ((int)(uint)DAT_8043624a <= iVar10) {
      return;
    }
    iVar13 = *piVar4;
    iVar11 = *(int *)(iVar13 + 0x20);
    piVar14 = &DAT_803c3b7c;
    for (iVar9 = 0; iVar9 < (int)(uint)DAT_8043624c; iVar9 = iVar9 + 1) {
      iVar12 = *piVar14;
      iVar6 = *(int *)(iVar12 + 0x20);
      if ((*(int *)(iVar13 + 0x20) != iVar6) &&
         (uVar3 = *(ushort *)(*(int *)(iVar12 + 0x28) + 2), (uVar3 & 0x800) == 0)) {
        if (iVar11 != iVar6) {
          if (*(char *)(iVar11 + 0x1db) != '\0') {
            if (*(int *)(iVar11 + 0x1e0) == iVar12) goto LAB_8002d788;
          }
          if ((*(char *)(iVar6 + 0x1db) == '\0') || (*(int *)(iVar6 + 0x1e0) != iVar13)) {
            cVar2 = *(char *)(iVar6 + 0x83);
            if ((cVar2 != '\x16') && (cVar2 != '\x11')) {
              if (cVar2 != '\x17') {
                if (cVar2 == '\0') {
                  if ((*(char *)(iVar6 + 1000) == '\x0e') && ((uVar3 & 0x20) != 0))
                  goto LAB_8002d668;
                }
                goto LAB_8002d788;
              }
            }
LAB_8002d668:
            puVar7 = (undefined4 *)(iVar13 + 0x54);
            puVar8 = (undefined4 *)0x803b04cc;
            iVar15 = 0x2d;
            do {
              puVar1 = puVar7 + 1;
              puVar7 = puVar7 + 2;
              uVar5 = *puVar7;
              puVar8[1] = *puVar1;
              puVar8 = puVar8 + 2;
              *puVar8 = uVar5;
              iVar15 = iVar15 + -1;
            } while (iVar15 != 0);
            puVar7 = (undefined4 *)(iVar12 + 0x54);
            puVar8 = (undefined4 *)&DAT_803b0364;
            iVar15 = 0x2d;
            do {
              puVar1 = puVar7 + 1;
              puVar7 = puVar7 + 2;
              uVar5 = *puVar7;
              puVar8[1] = *puVar1;
              puVar8 = puVar8 + 2;
              *puVar8 = uVar5;
              iVar15 = iVar15 + -1;
            } while (iVar15 != 0);
            zz_003a05c_(-0x7fc4fb30,-0x7fc4fc98,iVar11,iVar6);
            if (((*(char *)(iVar11 + 0x83) != '\0') ||
                (*(float *)(&DAT_803b0708 + *(char *)(iVar11 + 0x3e4) * 4) <=
                 DAT_803b04e0 - DAT_803b0500)) &&
               (iVar6 = zz_0039f6c_(-0x7fc4fb30,-0x7fc4fc98), iVar6 != 0)) {
              zz_0030348_(&DAT_803b04d0,&DAT_803b0368,*(int *)(iVar13 + 0x58),
                          *(int *)(iVar12 + 0x58));
              iVar6 = zz_0030420_(&DAT_803b04d0,&DAT_803b0368,
                                  *(int *)(iVar13 + 0x58) << 3 | *(uint *)(iVar12 + 0x58));
              if (iVar6 != 0) {
                *(byte *)(iVar11 + 0x280) = *(byte *)(iVar11 + 0x280) | 1;
              }
            }
          }
        }
      }
LAB_8002d788:
      piVar14 = piVar14 + 1;
    }
    iVar10 = iVar10 + 1;
    piVar4 = piVar4 + 1;
  } while( true );
}



// ==== 8002d7c4  collision_hit_pair_pass_active_vs_borgs ====

/* WARNING: Removing unreachable block (ram,0x8002db3c) */
/* WARNING: Removing unreachable block (ram,0x8002d7d4) */

void collision_hit_pair_pass_active_vs_borgs(void)

{
  undefined4 *puVar1;
  ushort uVar2;
  bool bVar3;
  bool bVar4;
  int *piVar5;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int unaff_r31;
  double dVar18;
  double in_f31;
  float afStack_68 [3];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  
  piVar5 = &DAT_803c477c;
  for (iVar12 = 0; iVar12 < (int)(uint)DAT_80436250; iVar12 = iVar12 + 1) {
    iVar17 = *piVar5;
    bVar3 = true;
    bVar4 = false;
    iVar13 = *(int *)(iVar17 + 0x20);
    iVar14 = *(int *)(iVar17 + 0x2c) + (uint)*(byte *)(iVar17 + 0x11) * 0x18;
    uVar2 = *(ushort *)(iVar14 + 0x10);
    if ((uVar2 & 0x800) == 0) {
      if (*(int *)(iVar17 + 0x58) == 2) {
        if ((uVar2 & 1) == 0) {
          bVar3 = false;
          in_f31 = (double)FLOAT_80436f98;
        }
        else {
          bVar3 = true;
        }
      }
      piVar6 = &DAT_803c2f7c;
      for (iVar15 = 0; iVar15 < (int)(uint)DAT_80436248; iVar15 = iVar15 + 1) {
        iVar16 = *piVar6;
        if ((((*(ushort *)(*(int *)(iVar17 + 0x28) + 2) & 0x4000) == 0) ||
            ((*(ushort *)(*(int *)(iVar16 + 0x28) + 2) & 0x2000) != 0)) &&
           (iVar8 = zz_002fd7c_(iVar17,iVar16,0x40), iVar8 != 0)) {
          iVar9 = *(int *)(iVar16 + 0x24);
          iVar8 = *(int *)(iVar17 + 0x24);
          if (((((*(char *)(iVar9 + 0x83) != '\0') || (*(char *)(iVar8 + 0x83) != '\0')) ||
               (*(char *)(iVar9 + 0x88) != *(char *)(iVar8 + 0x88))) ||
              ((((*(char *)(iVar9 + 0x1db) == '\0' || (*(char *)(iVar8 + 1000) == '\x0e')) ||
                (*(int *)(iVar9 + 0x1e4) != iVar8)) &&
               (((*(char *)(iVar8 + 0x1db) == '\0' || (*(char *)(iVar9 + 1000) == '\x0e')) ||
                (*(int *)(iVar8 + 0x1e4) != iVar9)))))) &&
             ((iVar8 = zz_0039f6c_(iVar17 + 0x58,iVar16 + 0x58), iVar8 != 0 &&
              (((*(ushort *)(iVar14 + 0x12) & 0x10) == 0 ||
               (*(char *)(iVar13 + 0x88) != *(char *)(*(int *)(iVar16 + 0x20) + 0x88))))))) {
            puVar10 = (undefined4 *)(iVar17 + 0x54);
            puVar11 = (undefined4 *)0x803b04cc;
            iVar8 = 0x2d;
            do {
              puVar1 = puVar10 + 1;
              puVar10 = puVar10 + 2;
              uVar7 = *puVar10;
              puVar11[1] = *puVar1;
              puVar11 = puVar11 + 2;
              *puVar11 = uVar7;
              iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
            puVar10 = (undefined4 *)(iVar16 + 0x54);
            puVar11 = (undefined4 *)&DAT_803b0364;
            iVar8 = 0x2d;
            do {
              puVar1 = puVar10 + 1;
              puVar10 = puVar10 + 2;
              uVar7 = *puVar10;
              puVar11[1] = *puVar1;
              puVar11 = puVar11 + 2;
              *puVar11 = uVar7;
              iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
            zz_0030348_(&DAT_803b04d0,&DAT_803b0368,*(int *)(iVar17 + 0x58),*(int *)(iVar16 + 0x58))
            ;
            iVar8 = zz_0030490_(&DAT_803b04d0,&DAT_803b0368,
                                *(int *)(iVar17 + 0x58) << 3 | *(uint *)(iVar16 + 0x58));
            if (iVar8 != 0) {
              if (bVar3) {
                resolve_hitbox_target_effects_and_damage(iVar17,iVar16);
              }
              else {
                dVar18 = gnt4_PSVECSquareDistance_bl((float *)&DAT_803b0374,(float *)&DAT_803b0504);
                if (dVar18 <= in_f31) {
                  bVar4 = true;
                  local_5c = DAT_803b0720;
                  local_58 = DAT_803b0724;
                  local_54 = DAT_803b0728;
                  unaff_r31 = iVar16;
                  in_f31 = dVar18;
                }
              }
            }
          }
        }
        piVar6 = piVar6 + 1;
      }
      if ((!bVar3) && (bVar4)) {
        DAT_803b0720 = local_5c;
        DAT_803b0724 = local_58;
        DAT_803b0728 = local_54;
        gnt4_PSVECSubtract_bl((float *)&DAT_803b0720,(float *)(iVar17 + 0x98),afStack_68);
        dVar18 = gnt4_PSVECSquareMag_bl(afStack_68);
        if ((double)FLOAT_80436f68 < dVar18) {
          iVar13 = *(int *)(iVar17 + 0x20);
          gnt4_PSVECAdd_bl((float *)(iVar17 + 0x98),afStack_68,(float *)(iVar17 + 0x98));
          gnt4_PSVECAdd_bl((float *)(iVar13 + 0x20),afStack_68,(float *)(iVar13 + 0x20));
          gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_68,afStack_68);
          gnt4_PSVECAdd_bl((float *)(iVar17 + 100),afStack_68,(float *)(iVar17 + 100));
          if (*(code **)(iVar13 + 0x100) != (code *)0x0) {
            (**(code **)(iVar13 + 0x100))(iVar13);
          }
        }
        resolve_hitbox_target_effects_and_damage(iVar17,unaff_r31);
      }
    }
    piVar5 = piVar5 + 1;
  }
  return;
}



// ==== 8002db58  collision_hit_pair_pass_active_vs_secondary ====

/* WARNING: Removing unreachable block (ram,0x8002deec) */
/* WARNING: Removing unreachable block (ram,0x8002db68) */

void collision_hit_pair_pass_active_vs_secondary(void)

{
  undefined4 *puVar1;
  ushort uVar2;
  ushort uVar3;
  bool bVar4;
  bool bVar5;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int *piVar17;
  int unaff_r31;
  double dVar18;
  double in_f31;
  float afStack_68 [3];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  
  piVar6 = &DAT_803c477c;
  for (iVar14 = 0; iVar14 < (int)(uint)DAT_80436250; iVar14 = iVar14 + 1) {
    iVar16 = *piVar6;
    bVar4 = true;
    bVar5 = false;
    iVar12 = *(int *)(iVar16 + 0x2c) + (uint)*(byte *)(iVar16 + 0x11) * 0x18;
    if (*(int *)(iVar16 + 0x58) == 2) {
      if ((*(ushort *)(iVar12 + 0x10) & 1) == 0) {
        bVar4 = false;
        in_f31 = (double)FLOAT_80436f98;
      }
      else {
        bVar4 = true;
      }
    }
    piVar17 = &DAT_803c417c;
    for (iVar13 = 0; iVar13 < (int)(uint)DAT_8043624e; iVar13 = iVar13 + 1) {
      iVar15 = *piVar17;
      uVar2 = *(ushort *)(*(int *)(iVar15 + 0x28) + 2);
      if ((((((uVar2 & 0x800) == 0) || (((int)*(short *)(iVar12 + 0x12) & 0x8000U) != 0)) &&
           ((uVar3 = *(ushort *)(*(int *)(iVar16 + 0x28) + 2), (uVar3 & 0x1000) != 0 ||
            ((uVar2 & 0x2000) == 0)))) &&
          ((((uVar3 & 0x4000) == 0 || ((uVar2 & 0x2000) != 0)) &&
           ((*(byte *)(*(int *)(iVar15 + 0x20) + 0x1da) & 2) == 0)))) &&
         (iVar8 = zz_002fd7c_(iVar16,iVar15,2), iVar8 != 0)) {
        iVar9 = *(int *)(iVar15 + 0x24);
        iVar8 = *(int *)(iVar16 + 0x24);
        if (((((*(char *)(iVar9 + 0x83) != '\0') || (*(char *)(iVar8 + 0x83) != '\0')) ||
             (*(char *)(iVar9 + 0x88) != *(char *)(iVar8 + 0x88))) ||
            ((((*(char *)(iVar9 + 0x1db) == '\0' || (*(char *)(iVar8 + 1000) == '\x0e')) ||
              (*(int *)(iVar9 + 0x1e4) != iVar8)) &&
             (((*(char *)(iVar8 + 0x1db) == '\0' || (*(char *)(iVar9 + 1000) == '\x0e')) ||
              (*(int *)(iVar8 + 0x1e4) != iVar9)))))) &&
           (iVar8 = zz_0039f6c_(iVar16 + 0x58,iVar15 + 0x58), iVar8 != 0)) {
          puVar10 = (undefined4 *)(iVar16 + 0x54);
          puVar11 = (undefined4 *)0x803b04cc;
          iVar8 = 0x2d;
          do {
            puVar1 = puVar10 + 1;
            puVar10 = puVar10 + 2;
            uVar7 = *puVar10;
            puVar11[1] = *puVar1;
            puVar11 = puVar11 + 2;
            *puVar11 = uVar7;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
          puVar10 = (undefined4 *)(iVar15 + 0x54);
          puVar11 = (undefined4 *)&DAT_803b0364;
          iVar8 = 0x2d;
          do {
            puVar1 = puVar10 + 1;
            puVar10 = puVar10 + 2;
            uVar7 = *puVar10;
            puVar11[1] = *puVar1;
            puVar11 = puVar11 + 2;
            *puVar11 = uVar7;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
          zz_0030348_(&DAT_803b04d0,&DAT_803b0368,*(int *)(iVar16 + 0x58),*(int *)(iVar15 + 0x58));
          iVar8 = zz_0030490_(&DAT_803b04d0,&DAT_803b0368,
                              *(int *)(iVar16 + 0x58) << 3 | *(uint *)(iVar15 + 0x58));
          if (iVar8 != 0) {
            if (bVar4) {
              resolve_hitbox_target_effects_and_damage(iVar16,iVar15);
            }
            else {
              dVar18 = gnt4_PSVECSquareDistance_bl((float *)&DAT_803b0374,(float *)&DAT_803b0504);
              if (dVar18 <= in_f31) {
                bVar5 = true;
                local_5c = DAT_803b0720;
                local_58 = DAT_803b0724;
                local_54 = DAT_803b0728;
                unaff_r31 = iVar15;
                in_f31 = dVar18;
              }
            }
          }
        }
      }
      piVar17 = piVar17 + 1;
    }
    if ((!bVar4) && (bVar5)) {
      DAT_803b0720 = local_5c;
      DAT_803b0724 = local_58;
      DAT_803b0728 = local_54;
      if ((*(ushort *)(*(int *)(unaff_r31 + 0x2c) + (uint)*(byte *)(unaff_r31 + 0x11) * 0x18 + 0x12)
          & 0x3c0) == 0) {
        gnt4_PSVECSubtract_bl((float *)&DAT_803b0720,(float *)(iVar16 + 0x98),afStack_68);
        dVar18 = gnt4_PSVECSquareMag_bl(afStack_68);
        if ((double)FLOAT_80436f68 < dVar18) {
          iVar12 = *(int *)(iVar16 + 0x20);
          gnt4_PSVECAdd_bl((float *)(iVar16 + 0x98),afStack_68,(float *)(iVar16 + 0x98));
          gnt4_PSVECAdd_bl((float *)(iVar12 + 0x20),afStack_68,(float *)(iVar12 + 0x20));
          gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_68,afStack_68);
          gnt4_PSVECAdd_bl((float *)(iVar16 + 100),afStack_68,(float *)(iVar16 + 100));
          if (*(code **)(iVar12 + 0x100) != (code *)0x0) {
            (**(code **)(iVar12 + 0x100))(iVar12);
          }
        }
      }
      resolve_hitbox_target_effects_and_damage(iVar16,unaff_r31);
    }
    piVar6 = piVar6 + 1;
  }
  return;
}



// ==== 8002df08  collision_hit_pair_pass_object_lists ====

/* WARNING: Removing unreachable block (ram,0x8002e1ac) */
/* WARNING: Removing unreachable block (ram,0x8002df18) */

void collision_hit_pair_pass_object_lists(void)

{
  undefined4 *puVar1;
  bool bVar2;
  bool bVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  int unaff_r31;
  double dVar14;
  double in_f31;
  float afStack_58 [3];
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  
  piVar4 = &DAT_803c177c;
  for (iVar10 = 0; iVar10 < (int)(uint)DAT_80436240; iVar10 = iVar10 + 1) {
    iVar12 = *piVar4;
    bVar2 = true;
    bVar3 = false;
    if (*(int *)(iVar12 + 0x58) == 2) {
      if ((*(ushort *)(*(int *)(iVar12 + 0x2c) + (uint)*(byte *)(iVar12 + 0x11) * 0x18 + 0x10) & 1)
          == 0) {
        bVar2 = false;
        in_f31 = (double)FLOAT_80436f98;
      }
      else {
        bVar2 = true;
      }
    }
    piVar13 = &DAT_803c117c;
    for (iVar9 = 0; iVar9 < (int)(uint)DAT_8043623e; iVar9 = iVar9 + 1) {
      iVar11 = *piVar13;
      iVar6 = zz_002fd7c_(iVar12,iVar11,2);
      if ((iVar6 != 0) && (iVar6 = zz_0039f6c_(iVar12 + 0x58,iVar11 + 0x58), iVar6 != 0)) {
        puVar7 = (undefined4 *)(iVar12 + 0x54);
        puVar8 = (undefined4 *)0x803b04cc;
        iVar6 = 0x2d;
        do {
          puVar1 = puVar7 + 1;
          puVar7 = puVar7 + 2;
          uVar5 = *puVar7;
          puVar8[1] = *puVar1;
          puVar8 = puVar8 + 2;
          *puVar8 = uVar5;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        puVar7 = (undefined4 *)(iVar11 + 0x54);
        puVar8 = (undefined4 *)&DAT_803b0364;
        iVar6 = 0x2d;
        do {
          puVar1 = puVar7 + 1;
          puVar7 = puVar7 + 2;
          uVar5 = *puVar7;
          puVar8[1] = *puVar1;
          puVar8 = puVar8 + 2;
          *puVar8 = uVar5;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        zz_0030348_(&DAT_803b04d0,&DAT_803b0368,*(int *)(iVar12 + 0x58),*(int *)(iVar11 + 0x58));
        iVar6 = zz_0030490_(&DAT_803b04d0,&DAT_803b0368,
                            *(int *)(iVar12 + 0x58) << 3 | *(uint *)(iVar11 + 0x58));
        if (iVar6 != 0) {
          if (bVar2) {
            resolve_hitbox_target_effects_and_damage(iVar12,iVar11);
          }
          else {
            dVar14 = gnt4_PSVECSquareDistance_bl((float *)&DAT_803b0374,(float *)&DAT_803b0504);
            if (dVar14 <= in_f31) {
              bVar3 = true;
              local_4c = DAT_803b0720;
              local_48 = DAT_803b0724;
              local_44 = DAT_803b0728;
              unaff_r31 = iVar11;
              in_f31 = dVar14;
            }
          }
        }
      }
      piVar13 = piVar13 + 1;
    }
    if ((!bVar2) && (bVar3)) {
      DAT_803b0720 = local_4c;
      DAT_803b0724 = local_48;
      DAT_803b0728 = local_44;
      gnt4_PSVECSubtract_bl((float *)&DAT_803b0720,(float *)(iVar12 + 0x98),afStack_58);
      dVar14 = gnt4_PSVECSquareMag_bl(afStack_58);
      if ((double)FLOAT_80436f68 < dVar14) {
        iVar9 = *(int *)(iVar12 + 0x20);
        gnt4_PSVECAdd_bl((float *)(iVar12 + 0x98),afStack_58,(float *)(iVar12 + 0x98));
        gnt4_PSVECAdd_bl((float *)(iVar9 + 0x20),afStack_58,(float *)(iVar9 + 0x20));
        gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_58,afStack_58);
        gnt4_PSVECAdd_bl((float *)(iVar12 + 100),afStack_58,(float *)(iVar12 + 100));
        if (*(code **)(iVar9 + 0x100) != (code *)0x0) {
          (**(code **)(iVar9 + 0x100))(iVar9);
        }
      }
      resolve_hitbox_target_effects_and_damage(iVar12,unaff_r31);
    }
    piVar4 = piVar4 + 1;
  }
  return;
}



// ==== 8002e1c8  zz_002e1c8_ ====

void zz_002e1c8_(void)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  piVar2 = &DAT_803c357c;
  for (iVar7 = 0; iVar7 < (int)(uint)DAT_8043624a; iVar7 = iVar7 + 1) {
    iVar6 = *piVar2;
    if (*(int *)(iVar6 + 0x58) == 0) {
      puVar4 = (undefined4 *)(iVar6 + 0x54);
      puVar5 = (undefined4 *)0x803b04cc;
      iVar8 = 0x2d;
      do {
        puVar1 = puVar4 + 1;
        puVar4 = puVar4 + 2;
        uVar3 = *puVar4;
        puVar5[1] = *puVar1;
        puVar5 = puVar5 + 2;
        *puVar5 = uVar3;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      if ((*(char *)(*(int *)(iVar6 + 0x20) + 0x83) != '\0') ||
         (*(float *)(&DAT_803b0708 + *(char *)(*(int *)(iVar6 + 0x20) + 0x3e4) * 4) <=
          DAT_803b04e0 - DAT_803b0500)) {
        FUN_80035e58(-0x7fc4fb30);
      }
    }
    piVar2 = piVar2 + 1;
  }
  return;
}



// ==== 8002e2a8  resolve_hitbox_target_effects_and_damage ====

/* GF_ALIAS: resolve_hitbox_target_effects_and_damage
 * Evidence: called by three hit-pair passes. param_1 owns the hit record table
 * (param_1+0x2c + action_index*0x18); param_2 resolves to the target actor.
 * Writes lock/target reaction fields (actor+0x290, DAT_803b06a8), last-enemy slot
 * marker (target+2000, target+0x7d1=15), effect deltas (DAT_8043612c), damage
 * accounting (actor+0x418/0x42c, target+0x41c), then calls zz_00300bc_,
 * zz_003cd5c_, and zz_003d344_.
 */

void resolve_hitbox_target_effects_and_damage(int param_1,int param_2)

{
  short sVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  char *pcVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  char *pcVar16;
  ushort *puVar17;
  char *pcVar18;
  int iVar19;
  int local_48 [2];
  undefined8 local_40;
  undefined8 local_38;
  
  bVar2 = false;
  iVar19 = *(int *)(param_1 + 0x20);
  pcVar18 = *(char **)(param_2 + 0x20);
  pcVar16 = *(char **)(param_1 + 0x24);
  puVar17 = (ushort *)(*(int *)(param_1 + 0x2c) + (uint)*(byte *)(param_1 + 0x11) * 0x18);
  iVar15 = *(int *)(param_2 + 0x24);
  iVar14 = *(int *)(param_2 + 0x28);
  iVar13 = *(int *)(param_2 + 0x2c) + (uint)*(byte *)(param_2 + 0x11) * 0x18;
  local_48[0] = 0;
  if (pcVar18[0x83] == '\0') {
    if ((puVar17[8] & 0x800) != 0) {
      if ((*(ushort *)(pcVar18 + 0x59c) & 0x800) == 0) {
        pcVar18[0x599] = pcVar18[0x599] | 1;
        pcVar18[0x1da] = pcVar18[0x1da] | 1;
        pcVar18[0x6fd] = pcVar18[0x6fd] | *(byte *)((int)puVar17 + 0xb);
        return;
      }
      zz_002f8d0_(iVar15,pcVar18,local_48);
    }
    if (((puVar17[8] & 2) != 0) && ((*(ushort *)(pcVar18 + 0x59c) & 2) != 0)) {
      return;
    }
  }
  fVar6 = FLOAT_80436fa0;
  if ((((puVar17[8] & 0x800) != 0) && (pcVar18[0x83] == '\x10')) &&
     (*(short *)(iVar15 + 1000) == 0x302)) {
    return;
  }
  if (((puVar17[9] & 0x10) != 0) && (pcVar16[0x88] == *(char *)(iVar15 + 0x88))) {
    bVar2 = true;
  }
  local_40 = (double)CONCAT44(0x43300000,(uint)puVar17[1]);
  iVar12 = (int)((float)(local_40 - DOUBLE_80436fb0) *
                FLOAT_80436f7c * (*(float *)(iVar19 + 0xc4) - FLOAT_80436f78));
  local_38 = (double)(longlong)iVar12;
  iVar12 = iVar12 + (uint)puVar17[1];
  if ((pcVar16[0x83] == '\0') && (pcVar16[0x6fc] != '\0')) {
    local_38 = (double)(CONCAT44(0x43300000,iVar12) ^ 0x80000000);
    iVar12 = (int)((float)(local_38 - DOUBLE_80436f88) * FLOAT_80436f9c);
    local_40 = (double)(longlong)iVar12;
  }
  bVar3 = false;
  if (*(char *)(iVar19 + 0x83) == '\x10') {
    bVar4 = (*(ushort *)(iVar13 + 0x12) & 0x40) != 0;
    if (bVar4) {
      *(byte *)(iVar19 + 0xb1) = *(byte *)(iVar19 + 0xb1) | 1;
      *(float *)(iVar19 + 0xbc) = fVar6 * *(float *)(iVar19 + 0x44);
    }
    fVar6 = FLOAT_80436f7c;
    bVar3 = (*(ushort *)(iVar13 + 0x12) & 0x80) != 0;
    if (bVar3) {
      *(byte *)(iVar19 + 0xb1) = *(byte *)(iVar19 + 0xb1) | 2;
      *(float *)(iVar19 + 0xbc) = fVar6 * *(float *)(iVar19 + 0x44);
    }
    fVar7 = FLOAT_80436fa4;
    fVar6 = FLOAT_80436f9c;
    bVar3 = bVar3 || bVar4;
    if ((*(ushort *)(iVar13 + 0x12) & 0x100) != 0) {
      *(byte *)(iVar19 + 0xb1) = *(byte *)(iVar19 + 0xb1) | 4;
      *(float *)(iVar19 + 0xb8) = fVar6 * *(float *)(iVar19 + 0xb8);
      if (fVar7 <= *(float *)(iVar19 + 0xb8)) {
        *(float *)(iVar19 + 0xb8) = fVar7;
      }
      bVar3 = true;
    }
    fVar7 = FLOAT_80436fa8;
    fVar6 = FLOAT_80436f7c;
    if ((*(ushort *)(iVar13 + 0x12) & 0x200) != 0) {
      *(byte *)(iVar19 + 0xb1) = *(byte *)(iVar19 + 0xb1) | 8;
      *(float *)(iVar19 + 0xb8) = fVar6 * *(float *)(iVar19 + 0xb8);
      if (*(float *)(iVar19 + 0xb8) <= fVar7) {
        *(float *)(iVar19 + 0xb8) = fVar7;
      }
      bVar3 = true;
    }
  }
  if (!bVar3) {
    switch(pcVar18[0x83]) {
    case '\0':
      *(byte *)(iVar19 + 0x1d9) = *(byte *)(iVar19 + 0x1d9) | 0x10;
      break;
    case '\x10':
    case '\x17':
      *(byte *)(iVar19 + 0x1d9) = *(byte *)(iVar19 + 0x1d9) | 0x40;
      break;
    case '\x11':
    case '\x12':
    case '\x14':
    case '\x15':
    case '\x16':
    case '\x19':
    case '\x1a':
      *(byte *)(iVar19 + 0x1d9) = *(byte *)(iVar19 + 0x1d9) | 0x80;
      break;
    case '\x18':
      *(byte *)(iVar19 + 0x1d9) = *(byte *)(iVar19 + 0x1d9) | 0x20;
    }
    *(char **)(iVar19 + 0x290) = pcVar18;
    *(char **)(pcVar16 + 0x290) = pcVar18;
    uVar8 = DAT_803b0724;
    *(undefined4 *)(iVar19 + 0x2a0) = DAT_803b0720;
    *(undefined4 *)(iVar19 + 0x2a4) = uVar8;
    *(undefined4 *)(iVar19 + 0x2a8) = DAT_803b0728;
    uVar8 = DAT_803b0724;
    *(undefined4 *)(pcVar18 + 0x2a0) = DAT_803b0720;
    *(undefined4 *)(pcVar18 + 0x2a4) = uVar8;
    *(undefined4 *)(pcVar18 + 0x2a8) = DAT_803b0728;
  }
  if ((*(byte *)(iVar19 + 0x2ac) & 1) != 0) {
    pcVar16[0x1d9] = pcVar16[0x1d9] | *(byte *)(iVar19 + 0x1d9);
  }
  if (*(char *)(iVar19 + 0x83) == '\0') {
    *(undefined1 *)(iVar19 + 0x703) = *(undefined1 *)(param_1 + 0x11);
    if (*(byte *)(iVar19 + 0x71c) <= *(byte *)(puVar17 + 4)) {
      *(byte *)(iVar19 + 0x71c) = *(byte *)(puVar17 + 4);
    }
  }
  *(undefined2 *)(pcVar18 + (uint)(byte)pcVar18[0x26e] * 2 + 0x20c) =
       *(undefined2 *)(iVar19 + 0x26c);
  pcVar18[0x26e] = pcVar18[0x26e] + '\x01';
  if (0x2f < (byte)pcVar18[0x26e]) {
    pcVar18[0x26e] = '\0';
  }
  if (pcVar18[0x83] == '\0') {
    if ((puVar17[9] & 0xfc0) == 0) {
      pcVar18[0x704] = *(char *)(param_1 + 0x11);
      pcVar18[0x6fd] = pcVar18[0x6fd] | *(byte *)((int)puVar17 + 0xb);
      pcVar18[0x702] = *(char *)((int)puVar17 + 0xd);
      if ((byte)pcVar18[0x71c] <= *(byte *)(puVar17 + 4)) {
        pcVar18[0x71c] = *(byte *)(puVar17 + 4);
      }
      pcVar18[0x71a] = *(char *)(iVar14 + 1);
      pcVar18[0x71a] = pcVar18[0x71a] & 0x3f;
      if (*(uint *)(pcVar18 + 0x5a0) == 0) {
        if ((*(uint *)(pcVar18 + 0x5e0) & 0x20000000) == 0) {
          FUN_800061a8((int)pcVar18,1);
        }
      }
      else if (((*(uint *)(pcVar18 + 0x5a0) & 1 << (int)pcVar18[0x71a]) == 0) &&
              ((*(uint *)(pcVar18 + 0x5e0) & 0x20000000) == 0)) {
        FUN_800061a8((int)pcVar18,1);
      }
    }
    if ((puVar17[9] & 0x400) != 0) {
      if ((*(ushort *)(pcVar18 + 0x59e) & 0x400) != 0) {
        return;
      }
      sVar1 = *(short *)(pcVar18 + 1000);
      if (sVar1 == 0x805) {
        return;
      }
      if (sVar1 == 0x80d) {
        return;
      }
      if (sVar1 == 0x80e) {
        return;
      }
      if (pcVar18[0x6fc] != '\0') {
        return;
      }
      if (pcVar18[0x4a0] != '\0') {
        return;
      }
      if ((int)(uint)*(byte *)((int)puVar17 + 5) < (int)pcVar18[0x70c]) {
        return;
      }
      pcVar18[0x70c] = *(byte *)((int)puVar17 + 5);
      return;
    }
    if ((puVar17[9] & 0x800) != 0) {
      if ((*(ushort *)(pcVar18 + 0x59e) & 0x400) != 0) {
        return;
      }
      pcVar18[0x70d] = '\x01';
      return;
    }
    if (pcVar16[0x83] == '\0') {
      if ((puVar17[8] & 0x10) != 0) {
        if ((*(ushort *)(pcVar18 + 0x59c) & 0x10) == 0) {
          if (((pcVar16[0x1d9] & 4U) == 0) && ((pcVar18[0x1da] & 4U) == 0)) {
            pcVar16[0x1d9] = pcVar16[0x1d9] | 4;
            pcVar18[0x1da] = pcVar18[0x1da] | 4;
            uVar8 = *(undefined4 *)(pcVar18 + 0x24);
            iVar11 = pcVar16[0x3e4] * 0xc;
            *(undefined4 *)(&DAT_803b06c0 + iVar11) = *(undefined4 *)(pcVar18 + 0x20);
            *(undefined4 *)(&DAT_803b06c4 + iVar11) = uVar8;
            *(undefined4 *)(&DAT_803b06c8 + iVar11) = *(undefined4 *)(pcVar18 + 0x28);
            uVar8 = *(undefined4 *)(pcVar16 + 0x24);
            iVar11 = pcVar18[0x3e4] * 0xc;
            *(undefined4 *)(&DAT_803b06c0 + iVar11) = *(undefined4 *)(pcVar16 + 0x20);
            *(undefined4 *)(&DAT_803b06c4 + iVar11) = uVar8;
            *(undefined4 *)(&DAT_803b06c8 + iVar11) = *(undefined4 *)(pcVar16 + 0x28);
            *(float *)(&DAT_803b06c4 + pcVar16[0x3e4] * 0xc) =
                 *(float *)(&DAT_803b06c4 + pcVar16[0x3e4] * 0xc) +
                 (*(float *)(pcVar18 + 0x6d0) - *(float *)(pcVar16 + 0x6d0));
            *(float *)(&DAT_803b06c4 + pcVar18[0x3e4] * 0xc) =
                 *(float *)(&DAT_803b06c4 + pcVar18[0x3e4] * 0xc) +
                 (*(float *)(pcVar16 + 0x6d0) - *(float *)(pcVar18 + 0x6d0));
          }
        }
        else {
          zz_002f8d0_(iVar15,pcVar18,local_48);
        }
      }
      if ((puVar17[9] & 0x1000) == 0) {
        if ((puVar17[8] & 0x200) == 0) {
          if ((puVar17[9] & 0x2000) != 0) {
            if (((*(ushort *)(pcVar18 + 0x59e) & 0x2000) == 0) && (pcVar18[0x4a0] == '\0')) {
              *(char **)(&DAT_803b06a8 + pcVar16[0x3e4] * 4) = pcVar18;
            }
            else {
              zz_002f8d0_(iVar15,pcVar18,local_48);
            }
          }
        }
        else if ((*(ushort *)(pcVar18 + 0x59c) & 0x200) == 0) {
          (&DAT_80436134)[pcVar18[0x3e4]] = 1;
        }
        else {
          zz_002f8d0_(iVar15,pcVar18,local_48);
        }
      }
      else if ((*(ushort *)(pcVar18 + 0x59e) & 0x1000) == 0) {
        (&DAT_8043613c)[pcVar18[0x3e4]] = 1;
      }
      else {
        zz_002f8d0_(iVar15,pcVar18,local_48);
      }
    }
    if ((puVar17[8] & 2) != 0) {
      pcVar18[0x1da] = pcVar18[0x1da] | 0x10;
    }
    if ((puVar17[9] & 1) != 0) {
      if ((*(ushort *)(pcVar18 + 0x59e) & 1) == 0) {
        pcVar18[0x1da] = pcVar18[0x1da] | 0x80;
      }
      else {
        zz_002f8d0_(iVar15,pcVar18,local_48);
      }
    }
    if ((puVar17[8] & 0x400) != 0) {
      if ((*(ushort *)(pcVar18 + 0x59c) & 0x400) == 0) {
        pcVar18[0x1da] = pcVar18[0x1da] | 8;
      }
      else {
        zz_002f8d0_(iVar15,pcVar18,local_48);
      }
    }
    if ((puVar17[8] & 4) == 0) {
      if ((puVar17[8] & 8) != 0) {
        if ((*(ushort *)(pcVar18 + 0x59c) & 8) == 0) {
          if ((pcVar18[0x83] == '\0') && (pcVar18[0x6fc] == '\0')) {
            pcVar18[0x1da] = pcVar18[0x1da] | 0x40;
            (&DAT_8043612c)[pcVar18[0x3e4]] =
                 (&DAT_8043612c)[pcVar18[0x3e4]] - *(char *)((int)puVar17 + 5);
          }
        }
        else {
          zz_002f8d0_(iVar15,pcVar18,local_48);
        }
      }
    }
    else if ((*(ushort *)(pcVar18 + 0x59c) & 4) == 0) {
      pcVar18[0x1da] = pcVar18[0x1da] | 0x20;
      (&DAT_8043612c)[pcVar18[0x3e4]] =
           (&DAT_8043612c)[pcVar18[0x3e4]] + *(char *)((int)puVar17 + 5);
    }
    else {
      zz_002f8d0_(iVar15,pcVar18,local_48);
    }
    if ((pcVar18[0x6fc] == '\0') && (pcVar18[0x4a0] == '\0')) {
      if (((puVar17[9] & 4) != 0) && ((*(ushort *)(pcVar18 + 0x59e) & 4) != 0)) {
        zz_002f8d0_(iVar15,pcVar18,local_48);
      }
      if (((puVar17[8] & 0x100) != 0) && ((*(ushort *)(pcVar18 + 0x59c) & 0x100) != 0)) {
        zz_002f8d0_(iVar15,pcVar18,local_48);
      }
      if (((puVar17[9] & 0x20) != 0) && ((*(ushort *)(pcVar18 + 0x59e) & 0x20) != 0)) {
        zz_002f8d0_(iVar15,pcVar18,local_48);
      }
    }
    if (((puVar17[9] & 8) != 0) && ((*(ushort *)(pcVar18 + 0x59e) & 8) != 0)) {
      zz_002f8d0_(iVar15,pcVar18,local_48);
    }
  }
  pcVar18[0x1da] = pcVar18[0x1da] | 1;
  *(int *)(pcVar18 + 0x290) = iVar19;
  *(int *)(iVar15 + 0x290) = iVar19;
  *(undefined4 *)(pcVar18 + 0x298) = *(undefined4 *)(iVar19 + 0xc4);
  if ((*(ushort *)(iVar14 + 2) & 0x40) != 0) {
    if (pcVar18[0x83] == '\0') {
      if (((*(uint *)(pcVar18 + 0x5e0) & 0x1000000) == 0) ||
         ((*(uint *)(pcVar18 + 0x5e0) & 0x10000000) != 0)) {
        pcVar18[0x1da] = pcVar18[0x1da] | 2;
        *(byte *)(iVar19 + 0x1d9) = *(byte *)(iVar19 + 0x1d9) | 2;
      }
    }
    else if ((*(char *)(iVar15 + 0x83) == '\0') && (!bVar2)) {
      if (((*(uint *)(iVar15 + 0x5e0) & 0x1000000) == 0) ||
         ((*(uint *)(iVar15 + 0x5e0) & 0x10000000) != 0)) {
        pcVar18[0x1da] = pcVar18[0x1da] | 2;
        *(byte *)(iVar19 + 0x1d9) = *(byte *)(iVar19 + 0x1d9) | 2;
      }
      if (((pcVar18[0x2ac] & 2U) != 0) || ((pcVar18[0x2ac] & 8U) != 0)) {
        *(undefined2 *)(iVar15 + (uint)*(byte *)(iVar15 + 0x26e) * 2 + 0x20c) =
             *(undefined2 *)(iVar19 + 0x26c);
        *(char *)(iVar15 + 0x26e) = *(char *)(iVar15 + 0x26e) + '\x01';
        if (0x2f < *(byte *)(iVar15 + 0x26e)) {
          *(undefined1 *)(iVar15 + 0x26e) = 0;
        }
      }
    }
  }
  if ((pcVar18[0x83] == '\0') &&
     (((((*(uint *)(pcVar18 + 0x5e0) & 0x10000000) != 0 || ((pcVar18[0x1da] & 2U) != 0)) &&
       (*(char *)(iVar19 + 0x83) == '\x10')) && (*(char *)(iVar19 + 0x10) == '\n')))) {
    pcVar18[0x1da] = pcVar18[0x1da] | 2;
    *(byte *)(iVar19 + 0x1d9) = *(byte *)(iVar19 + 0x1d9) | 2;
  }
  if ((pcVar18[0x2ac] & 2U) != 0) {
    *(byte *)(iVar15 + 0x1da) = *(byte *)(iVar15 + 0x1da) | pcVar18[0x1da];
    *(undefined4 *)(iVar15 + 0x298) = *(undefined4 *)(pcVar18 + 0x298);
  }
  if (((((puVar17[9] & 0xfc0) == 0) && ((*(ushort *)(iVar13 + 0x12) & 0xfc0) == 0)) &&
      ((pcVar16[0x83] == '\0' && ((pcVar18[0x83] == '\0' && (pcVar16[0x88] != '\x04')))))) &&
     (pcVar18[0x88] != '\x04')) {
    if ((pcVar18[0x1da] & 2U) == 0) {
      if (pcVar16[0x88] == *(char *)(iVar15 + 0x88)) {
        if (!bVar2) {
          if (((int)(char)*(byte *)(iVar19 + 0x2ad) & 1 << (int)pcVar18[0x3e4]) == 0) {
            *(byte *)(iVar19 + 0x2ad) = *(byte *)(iVar19 + 0x2ad) | (byte)(1 << (int)pcVar18[0x3e4])
            ;
            *(int *)(pcVar18 + 0x414) = *(int *)(pcVar18 + 0x414) + 1;
            if (pcVar16 != pcVar18) {
              *(int *)(pcVar16 + 0x428) = *(int *)(pcVar16 + 0x428) + 1;
              pcVar9 = pcVar16 + pcVar16[0x484] * 4 + 0x464;
              pcVar9[0] = '\0';
              pcVar9[1] = '\x02';
              *(short *)(pcVar9 + 2) = (short)pcVar18[0x3e4];
              pcVar16[0x484] = pcVar16[0x484] + '\x01';
              iVar14 = pcVar16[0x484] + 8;
              cVar5 = (char)(iVar14 >> 0x1f);
              pcVar16[0x484] =
                   (cVar5 * '\b' |
                   (byte)((uint)(pcVar16[0x484] * 0x20000000 + (iVar14 >> 0x1f)) >> 0x1d)) - cVar5;
            }
          }
        }
        if (*(ushort *)(pcVar16 + 0x4f6) < 999) {
          *(ushort *)(pcVar16 + 0x4f6) = *(ushort *)(pcVar16 + 0x4f6) + 1;
        }
        else {
          pcVar16[0x4f6] = '\x03';
          pcVar16[0x4f7] = -0x19;
        }
        pcVar16[0x4fa] = '\0';
        pcVar16[0x4fb] = '<';
        if ((pcVar16[0x4a0] == '\x01') && (pcVar16[0x594] != '\0')) {
          iVar14 = *(int *)(pcVar16 + 0x4a4);
          if (*(ushort *)(iVar14 + 0x4f6) < 999) {
            *(ushort *)(iVar14 + 0x4f6) = *(ushort *)(iVar14 + 0x4f6) + 1;
          }
          else {
            *(undefined2 *)(iVar14 + 0x4f6) = 999;
          }
          *(undefined2 *)(iVar14 + 0x4fa) = 0x3c;
        }
      }
      else {
        if (DAT_80436128 == '\0') {
          DAT_80436128 = '\x01';
          pcVar16[0x436] = '\x01';
        }
        if (((int)(char)*(byte *)(iVar19 + 0x2ad) & 1 << (int)pcVar18[0x3e4]) == 0) {
          *(byte *)(iVar19 + 0x2ad) = *(byte *)(iVar19 + 0x2ad) | (byte)(1 << (int)pcVar18[0x3e4]);
          if ((puVar17[8] & 0x20) == 0) {
            *(int *)(pcVar16 + 0x408) = *(int *)(pcVar16 + 0x408) + 1;
            if (*(char **)(iVar19 + 0xcc) == pcVar18) {
              *(int *)(pcVar18 + 0x410) = *(int *)(pcVar18 + 0x410) + 1;
              if (*(uint *)(pcVar18 + 0x40c) < *(uint *)(pcVar18 + 0x410)) {
                *(uint *)(pcVar18 + 0x410) = *(uint *)(pcVar18 + 0x40c);
              }
            }
            else {
              *(int *)(pcVar18 + 0x414) = *(int *)(pcVar18 + 0x414) + 1;
            }
          }
          else {
            *(int *)(pcVar18 + 0x414) = *(int *)(pcVar18 + 0x414) + 1;
          }
          pcVar9 = pcVar16 + pcVar16[0x484] * 4 + 0x464;
          pcVar9[0] = '\0';
          pcVar9[1] = '\x01';
          *(short *)(pcVar9 + 2) = (short)pcVar18[0x3e4];
          pcVar16[0x484] = pcVar16[0x484] + '\x01';
          iVar14 = pcVar16[0x484] + 8;
          cVar5 = (char)(iVar14 >> 0x1f);
          pcVar16[0x484] =
               (cVar5 * '\b' |
               (byte)((uint)(pcVar16[0x484] * 0x20000000 + (iVar14 >> 0x1f)) >> 0x1d)) - cVar5;
          pcVar18[2000] = pcVar16[0x3e4];
          pcVar18[0x7d1] = '\x0f';
        }
        if (*(ushort *)(pcVar16 + 0x4f4) < 999) {
          *(ushort *)(pcVar16 + 0x4f4) = *(ushort *)(pcVar16 + 0x4f4) + 1;
        }
        else {
          pcVar16[0x4f4] = '\x03';
          pcVar16[0x4f5] = -0x19;
        }
        pcVar16[0x4f8] = '\0';
        pcVar16[0x4f9] = '<';
        if ((pcVar16[0x4a0] == '\x01') && (pcVar16[0x594] != '\0')) {
          iVar14 = *(int *)(pcVar16 + 0x4a4);
          if (*(ushort *)(iVar14 + 0x4f4) < 999) {
            *(ushort *)(iVar14 + 0x4f4) = *(ushort *)(iVar14 + 0x4f4) + 1;
          }
          else {
            *(undefined2 *)(iVar14 + 0x4f4) = 999;
          }
          *(undefined2 *)(iVar14 + 0x4f8) = 0x3c;
        }
      }
    }
    if ((puVar17[8] & 0x1000) == 0) {
      local_38 = (double)CONCAT44(0x43300000,(uint)*(byte *)((int)puVar17 + 5));
      iVar14 = (int)((float)(local_38 - DOUBLE_80436fb0) *
                    *(float *)(&DAT_802c7ca0 + pcVar18[0x6ca] * 4));
      local_40 = (double)(longlong)iVar14;
      if (iVar14 < 2) {
        iVar14 = 1;
      }
      (&DAT_80436154)[pcVar16[0x88]] = (&DAT_80436154)[pcVar16[0x88]] + (short)iVar14;
    }
  }
  zz_00300bc_(param_1,param_2,(int)*(char *)(puVar17 + 7));
  if ((puVar17[8] & 2) == 0) {
    if (((pcVar18[0x1da] & 2U) == 0) || (pcVar18[0x83] != '\0')) {
      uVar10 = zz_003cd5c_(puVar17,iVar19,pcVar18);
    }
    else {
      uVar10 = 0;
    }
  }
  else if (pcVar18[0x83] == '\0') {
    uVar10 = -(uint)*puVar17;
    if (pcVar16[0x88] != pcVar18[0x88]) {
      uVar10 = ((int)uVar10 >> 2) + (uint)((int)uVar10 < 0 && (uVar10 & 3) != 0);
    }
    if (*(short *)(pcVar18 + 0x6b8) != 0) {
      pcVar18[0x6b8] = '\0';
      pcVar18[0x6b9] = '\x01';
    }
    if (*(short *)(pcVar18 + 0x6ba) != 0) {
      pcVar18[0x6ba] = '\0';
      pcVar18[0x6bb] = '\x01';
    }
  }
  else {
    uVar10 = 0;
  }
  if ((((pcVar16[0x83] == '\0') && (pcVar18[0x83] == '\0')) && (0 < (int)uVar10)) &&
     (PTR_DAT_80433934[0x1f] == '\0')) {
    if (pcVar16[0x88] == pcVar18[0x88]) {
      if (pcVar16 != pcVar18) {
        *(uint *)(pcVar16 + 0x42c) = *(int *)(pcVar16 + 0x42c) + uVar10;
      }
    }
    else {
      *(uint *)(pcVar16 + 0x418) = *(int *)(pcVar16 + 0x418) + uVar10;
    }
    *(uint *)(pcVar18 + 0x41c) = *(int *)(pcVar18 + 0x41c) + uVar10;
    if ((*(char *)(iVar19 + 0x83) == '\0') &&
       ((*(short *)(iVar19 + 1000) == 0x702 || (*(short *)(iVar19 + 1000) == 0x70a)))) {
      iVar14 = *(char *)(iVar19 + 0x3e4) * 2;
      *(short *)(&DAT_803b0638 + iVar14) =
           *(short *)(&DAT_803b0638 + iVar14) + (short)((int)uVar10 / 2);
    }
  }
  uVar10 = zz_003d344_((int)pcVar18,(short)uVar10);
  fVar6 = FLOAT_80436f78;
  if ((uVar10 == 0) || (PTR_DAT_80433934[0x1f] != '\0')) {
    sVar1 = (short)iVar12;
    if (pcVar18[0x83] == '\0') {
      if (*(short *)(pcVar18 + 0x1c6) != 0) {
        *(float *)(pcVar18 + 0x688) = FLOAT_80436fac;
        local_38 = (double)CONCAT44(0x43300000,(int)*(short *)(pcVar18 + 0x6c4) ^ 0x80000000);
        iVar14 = (int)((float)(local_38 - DOUBLE_80436f88) *
                      FLOAT_80436f7c * (*(float *)(pcVar18 + 0xb4) - fVar6));
        local_40 = (double)(longlong)iVar14;
        if (pcVar18[0x7de] == '\0') {
          if ((*(uint *)(pcVar18 + 0x5e0) & 0x1000000) == 0) {
            *(short *)(pcVar18 + 0x6c6) = *(short *)(pcVar18 + 0x6c6) - sVar1;
          }
          else if (iVar14 + *(short *)(pcVar18 + 0x6c4) <= iVar12) {
            *(short *)(pcVar18 + 0x6c6) = *(short *)(pcVar18 + 0x6c6) - sVar1;
          }
        }
        fVar6 = FLOAT_80436fac;
        *(float *)(pcVar18 + 0x684) = FLOAT_80436fac;
        *(float *)(pcVar18 + 0x68c) = fVar6;
        if (((pcVar18[0x6fd] & 0x80U) == 0) &&
           (*(ushort *)(pcVar18 + 0x6c2) =
                 *(short *)(pcVar18 + 0x6c2) - (ushort)*(byte *)(puVar17 + 2),
           *(short *)(pcVar18 + 0x6c2) < 1)) {
          *(undefined2 *)(pcVar18 + 0x6c2) = *(undefined2 *)(pcVar18 + 0x6be);
          pcVar18[0x6c8] = '\0';
          pcVar18[0x6c9] = '\0';
          pcVar18[0x6ca] = '\0';
          pcVar18[0x6fd] = pcVar18[0x6fd] | 0xa6;
        }
        *(ushort *)(pcVar18 + 0x6c8) =
             *(short *)(pcVar18 + 0x6c8) + (ushort)*(byte *)((int)puVar17 + 5);
        if (99 < *(short *)(pcVar18 + 0x6c8)) {
          pcVar18[0x6c8] = '\0';
          pcVar18[0x6c9] = '\0';
          pcVar18[0x6ca] = pcVar18[0x6ca] + '\x01';
          if ('>' < pcVar18[0x6ca]) {
            pcVar18[0x6ca] = '?';
          }
        }
      }
    }
    else if ((*(char *)(iVar15 + 0x83) == '\0') && ((*(byte *)(iVar15 + 0x1da) & 2) != 0)) {
      *(float *)(iVar15 + 0x7d8) = FLOAT_80436fac;
      local_38 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar15 + 0x7d6) ^ 0x80000000);
      iVar14 = (int)((float)(local_38 - DOUBLE_80436f88) *
                    FLOAT_80436f7c * (*(float *)(iVar15 + 0xb4) - fVar6));
      local_40 = (double)(longlong)iVar14;
      if ((*(uint *)(iVar15 + 0x5e0) & 0x1000000) == 0) {
        *(short *)(iVar15 + 0x7dc) = *(short *)(iVar15 + 0x7dc) - sVar1;
      }
      else if (iVar14 + *(short *)(iVar15 + 0x7d6) <= iVar12) {
        *(short *)(iVar15 + 0x7dc) = *(short *)(iVar15 + 0x7dc) - sVar1;
      }
      *(undefined1 *)(iVar15 + 0x704) = *(undefined1 *)(param_1 + 0x11);
      *(byte *)(iVar15 + 0x6fd) = *(byte *)(iVar15 + 0x6fd) | *(byte *)((int)puVar17 + 0xb);
      *(undefined1 *)(iVar15 + 0x702) = *(undefined1 *)((int)puVar17 + 0xd);
      if (*(byte *)(iVar15 + 0x71c) <= *(byte *)(puVar17 + 4)) {
        *(byte *)(iVar15 + 0x71c) = *(byte *)(puVar17 + 4);
      }
    }
  }
  else {
    zz_002f8dc_((int)pcVar16,pcVar18);
    if (pcVar18[0x4a0] == '\x01') {
      zz_002f8dc_((int)pcVar16,*(char **)(pcVar18 + 0x4a4));
    }
    if ((pcVar18[0x83] == '\0') && (pcVar16[0x88] != pcVar18[0x88])) {
      if (pcVar16[0x3e6] == '\0') {
        if (PTR_DAT_80433930[0x32] == '\0') {
          if (*(short *)(pcVar18 + 0x3ea) == 0x503) {
            zz_018214c_(0x505,(int)pcVar18[0x3ed]);
            zz_018214c_(0x506,(int)pcVar18[0x3ed]);
          }
          else {
            zz_018214c_((int)*(short *)(pcVar18 + 0x3ea),(int)pcVar18[0x3ed]);
            if (pcVar18[0x4a0] == '\x01') {
              zz_018214c_((int)*(short *)(*(int *)(pcVar18 + 0x4a4) + 0x3ea),
                          (int)*(char *)(*(int *)(pcVar18 + 0x4a4) + 0x3ed));
            }
          }
        }
        else if ((PTR_DAT_80433930[0x32] == '\x01') &&
                (zz_0006c24_((int)pcVar16,(int)pcVar18), pcVar18[0x4a0] == '\x01')) {
          zz_0006c24_((int)pcVar16,*(int *)(pcVar18 + 0x4a4));
        }
      }
      if (pcVar16[0x83] == '\0') {
        *(char **)(pcVar18 + 0x5a4) = pcVar16;
      }
    }
  }
  if (pcVar18[0x83] != ' ') {
    if ((bVar3) && ((*(ushort *)(iVar13 + 0x12) & 0x80) == 0)) {
      zz_00db250_((int)pcVar18,&DAT_803b0720,4);
    }
    if (((*(char *)(iVar13 + 9) != -1) || (pcVar18[0x83] != '\x10')) &&
       (*(char *)((int)puVar17 + 9) != -1)) {
      if (((pcVar18[0x1da] & 2U) == 0) && ((*(byte *)(iVar15 + 0x1da) & 2) == 0)) {
        if (local_48[0] == 0) {
          bVar2 = false;
          if (pcVar18[0x83] == '\0') {
            bVar2 = (puVar17[8] & 2) != 0;
            if (bVar2) {
              zz_010e158_((int)pcVar18,1);
              *(ushort *)(pcVar18 + 0x272) = *(ushort *)(pcVar18 + 0x272) | 0x43;
            }
            if ((pcVar18[0x6fc] == '\0') && (pcVar18[0x4a0] == '\0')) {
              if ((puVar17[9] & 4) != 0) {
                sVar1 = *(short *)(pcVar18 + 0x710);
                if (sVar1 == 0) {
                  zz_013f300_((int)pcVar18,0);
                }
                bVar2 = sVar1 == 0 || bVar2;
                pcVar18[0x70e] = '\x02';
                pcVar18[0x710] = '\x03';
                pcVar18[0x711] = -0x7c;
              }
              if ((puVar17[9] & 0x1000) != 0) {
                zz_0176ec0_((int)pcVar18,0,1);
                bVar2 = true;
              }
              if ((puVar17[8] & 0x200) != 0) {
                zz_0176ec0_((int)pcVar18,0,1);
                bVar2 = true;
              }
              if ((puVar17[8] & 8) != 0) {
                zz_0176ec0_((int)pcVar18,2,1);
                bVar2 = true;
              }
              if ((puVar17[8] & 0x100) != 0) {
                if (*(short *)(pcVar18 + 0x6ba) == 0) {
                  zz_01ec1bc_((int)pcVar18);
                  bVar2 = true;
                }
                pcVar18[0x6ba] = '\x02';
                pcVar18[0x6bb] = 'X';
              }
              if ((puVar17[9] & 0x20) != 0) {
                if (*(short *)(pcVar18 + 0x6b8) == 0) {
                  zz_01dff24_((int)pcVar18);
                  bVar2 = true;
                }
                pcVar18[0x6b8] = '\x02';
                pcVar18[0x6b9] = -0x7f;
              }
            }
            if ((puVar17[9] & 8) != 0) {
              if (*(short *)(pcVar18 + 0x712) == 0) {
                zz_013f300_((int)pcVar18,1);
                bVar2 = true;
              }
              pcVar18[0x70f] = '\x02';
              pcVar18[0x712] = '\x03';
              pcVar18[0x713] = -0x7c;
            }
            if ((puVar17[8] & 4) != 0) {
              zz_0176ec0_((int)pcVar18,1,1);
              bVar2 = true;
            }
          }
          if ((!bVar2) && (pcVar18[0x2af] == '\0')) {
            pcVar18[0x2af] = '\x04';
            zz_0019550_(iVar19,&DAT_803b0720,(uint)*(byte *)((int)puVar17 + 9));
          }
          zz_002fc18_(iVar19,(int)pcVar18,(float *)&DAT_803b0720,*(byte *)(puVar17 + 5));
        }
        else {
          zz_00db250_((int)pcVar18,&DAT_803b0720,8);
          zz_002fcbc_(iVar19,(int)pcVar18,(float *)&DAT_803b0720);
        }
      }
      else {
        iVar13 = (int)*(short *)(iVar15 + 1000);
        if (iVar13 == 0x302) {
          zz_00db250_((int)pcVar18,&DAT_803b0720,1);
        }
        else if (((iVar13 == 0x603) || (iVar13 == 0x60b)) ||
                ((iVar13 == 0x60d || (iVar13 == 0x60f)))) {
          switch(iVar13) {
          case 0x603:
            zz_00db250_((int)pcVar18,&DAT_803b0720,3);
            break;
          case 0x60b:
            zz_00db250_((int)pcVar18,&DAT_803b0720,5);
            break;
          case 0x60d:
            zz_00db250_((int)pcVar18,&DAT_803b0720,6);
            break;
          case 0x60f:
            zz_00db250_((int)pcVar18,&DAT_803b0720,7);
          }
        }
        else {
          zz_00db250_((int)pcVar18,&DAT_803b0720,0);
        }
        zz_002fcbc_(iVar19,(int)pcVar18,(float *)&DAT_803b0720);
      }
    }
    if ((pcVar18[0x83] == '\0') && (pcVar18[0x4a0] == '\x01')) {
      *(char *)(*(int *)(pcVar18 + 0x4a4) + 0x1da) = pcVar18[0x1da];
    }
  }
  return;
}



// ==== 8002f8d0  zz_002f8d0_ ====

void zz_002f8d0_(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  *param_3 = 1;
  return;
}



// ==== 8002f8dc  zz_002f8dc_ ====

void zz_002f8dc_(int param_1,char *param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  
  bVar2 = false;
  if (param_2[0x83] != '\0') {
    return;
  }
  iVar3 = (int)*(short *)(param_2 + 0x4aa);
  if (PTR_DAT_80433930[0x32] != '\0') {
    if (PTR_DAT_80433930[0x32] == '\x01') {
      cVar1 = param_2[0x88];
      if ((cVar1 != '\0') || (param_2[0x3e6] == '\0')) {
        *(int *)(PTR_DAT_80433934 + cVar1 * 0x3c + 0x118) =
             *(int *)(PTR_DAT_80433934 + cVar1 * 0x3c + 0x118) - iVar3;
      }
    }
    else {
      cVar1 = param_2[0x88];
      if (PTR_DAT_80433934[cVar1 * 0x3c + 0xf6] == '\0') {
        if (param_2[0x3e6] != '\0') {
          *(int *)(PTR_DAT_80433934 + cVar1 * 0x3c + 0x118) =
               *(int *)(PTR_DAT_80433934 + cVar1 * 0x3c + 0x118) - iVar3;
        }
      }
      else if (param_2[0x3e6] == '\0') {
        *(int *)(PTR_DAT_80433934 + cVar1 * 0x3c + 0x118) =
             *(int *)(PTR_DAT_80433934 + cVar1 * 0x3c + 0x118) - iVar3;
      }
    }
    goto LAB_8002fa4c;
  }
  iVar7 = param_2[0x88] * 0x3c;
  if (PTR_DAT_80433934[iVar7 + 0x108] != '\0') {
    if (param_2[0x88] == '\0') {
      if (param_2[0x3e6] != '\0') goto LAB_8002f944;
    }
    *(int *)(PTR_DAT_80433934 + iVar7 + 0x118) = *(int *)(PTR_DAT_80433934 + iVar7 + 0x118) - iVar3;
  }
LAB_8002f944:
  cVar1 = param_2[0x88];
  if (PTR_DAT_80433934[cVar1 * 0x3c + 0x109] != '\0') {
    if (param_2[0x1ea] != '\0') {
      if ('\0' < (char)PTR_DAT_80433934[cVar1 * 0x3c + 0x10a]) {
        PTR_DAT_80433934[cVar1 * 0x3c + 0x10a] = PTR_DAT_80433934[cVar1 * 0x3c + 0x10a] + -1;
        if (PTR_DAT_80433934[0x1f] == '\0') {
          if (*(char *)(param_1 + 0x83) == '\0') {
            *(int *)(PTR_DAT_80433934 + 0xb4) = param_1;
          }
          bVar2 = true;
          *(char **)(PTR_DAT_80433934 + 0xb8) = param_2;
        }
      }
    }
  }
LAB_8002fa4c:
  if (*(int *)(PTR_DAT_80433934 + param_2[0x88] * 0x3c + 0x118) < 1) {
    *(undefined4 *)(PTR_DAT_80433934 + param_2[0x88] * 0x3c + 0x118) = 0;
    if (PTR_DAT_80433934[0x1f] == '\0') {
      if (!bVar2) {
        if (*(char *)(param_1 + 0x83) == '\0') {
          *(int *)(PTR_DAT_80433934 + 0xb4) = param_1;
        }
        *(char **)(PTR_DAT_80433934 + 0xb8) = param_2;
      }
    }
  }
  param_2[0x435] = param_2[0x435] + '\x01';
  *(int *)(param_2 + 0x424) = *(int *)(param_2 + 0x424) + iVar3;
  if (*(char *)(param_1 + 0x83) == '\0') {
    if (*(char *)(param_1 + 0x88) != param_2[0x88]) {
      *(char *)(param_1 + 0x434) = *(char *)(param_1 + 0x434) + '\x01';
      *(int *)(param_1 + 0x420) = *(int *)(param_1 + 0x420) + iVar3;
      (&DAT_80436154)[*(char *)(param_1 + 0x88)] = (&DAT_80436154)[*(char *)(param_1 + 0x88)] + 100;
    }
  }
  iVar7 = 6;
  pcVar4 = DAT_803c4e84;
  do {
    if (*pcVar4 != '\0') {
      pcVar6 = pcVar4 + pcVar4[0x484] * 4 + 0x464;
      if (pcVar4[0x88] == param_2[0x88]) {
        if (pcVar4 != param_2) {
          pcVar6[0] = '\0';
          pcVar6[1] = '\x04';
          *(short *)(pcVar6 + 2) = (short)param_2[0x3e4];
          pcVar4[0x484] = pcVar4[0x484] + '\x01';
          iVar5 = pcVar4[0x484] + 8;
          cVar1 = (char)(iVar5 >> 0x1f);
          pcVar4[0x484] =
               (cVar1 * '\b' | (byte)((uint)(pcVar4[0x484] * 0x20000000 + (iVar5 >> 0x1f)) >> 0x1d))
               - cVar1;
          pcVar4[0x437] = pcVar4[0x437] + '\x01';
          *(int *)(pcVar4 + 0x430) = *(int *)(pcVar4 + 0x430) + iVar3;
        }
      }
      else {
        pcVar6[0] = '\0';
        pcVar6[1] = '\x03';
        *(short *)(pcVar6 + 2) = (short)param_2[0x3e4];
        pcVar4[0x484] = pcVar4[0x484] + '\x01';
        iVar5 = pcVar4[0x484] + 8;
        cVar1 = (char)(iVar5 >> 0x1f);
        pcVar4[0x484] =
             (cVar1 * '\b' | (byte)((uint)(pcVar4[0x484] * 0x20000000 + (iVar5 >> 0x1f)) >> 0x1d)) -
             cVar1;
      }
    }
    pcVar4 = pcVar4 + 0x1e00;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  return;
}



// ==== 8002fc18  zz_002fc18_ ====

void zz_002fc18_(undefined4 param_1,int param_2,float *param_3,byte param_4)

{
  float fVar1;
  uint uVar2;
  
  uVar2 = (uint)param_4;
  if (*(char *)(param_2 + 0x2ae) == '\0') {
    if (param_4 != 0xff) {
      *(undefined1 *)(param_2 + 0x2ae) = 4;
      if ((param_4 & 0x80) != 0) {
        fVar1 = *(float *)(param_2 + 0x7fc);
        uVar2 = param_4 & 0x7c;
        if (FLOAT_80436fb8 < fVar1) {
          uVar2 = uVar2 + 1;
        }
        if (FLOAT_80436f94 < fVar1) {
          uVar2 = uVar2 + 1;
        }
        if (FLOAT_80436fbc < fVar1) {
          uVar2 = uVar2 + 1;
        }
      }
      zz_00f088c_(uVar2 & 0xff,param_3,param_2);
    }
  }
  return;
}



// ==== 8002fcbc  zz_002fcbc_ ====

void zz_002fcbc_(undefined4 param_1,int param_2,float *param_3)

{
  if (*(char *)(param_2 + 0x2ae) == '\0') {
    *(undefined1 *)(param_2 + 0x2ae) = 4;
    if (*(char *)(param_2 + 0x83) == '\0') {
      if (FLOAT_80436fb8 < *(float *)(param_2 + 0x7fc)) {
        if (FLOAT_80436f94 < *(float *)(param_2 + 0x7fc)) {
          zz_00f04b4_(0x26,param_3,(int)*(char *)(param_2 + 0x96));
        }
        else {
          zz_00f04b4_(0x26,param_3,(int)*(char *)(param_2 + 0x96));
        }
      }
      else {
        zz_00f04b4_(0x26,param_3,(int)*(char *)(param_2 + 0x96));
      }
    }
    else {
      zz_00f04b4_(0x26,param_3,(int)*(char *)(param_2 + 0x96));
    }
  }
  return;
}



// ==== 8002fd7c  zz_002fd7c_ ====

undefined4 zz_002fd7c_(int param_1,int param_2,uint param_3)

{
  short sVar1;
  bool bVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  iVar5 = *(int *)(param_1 + 0x20);
  iVar6 = *(int *)(param_2 + 0x20);
  if (iVar5 == iVar6) {
    return 0;
  }
  iVar7 = *(int *)(param_1 + 0x24);
  iVar8 = *(int *)(param_2 + 0x24);
  iVar9 = *(int *)(param_1 + 0x2c) + (uint)*(byte *)(param_1 + 0x11) * 0x18;
  iVar10 = *(int *)(param_2 + 0x2c) + (uint)*(byte *)(param_2 + 0x11) * 0x18;
  if (iVar7 == iVar8) {
    if ((*(ushort *)(iVar9 + 0x10) & 0x40) == 0) {
      bVar2 = false;
    }
    else if (*(short *)(iVar5 + 0x1c) == 0xff) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    if (!bVar2) {
      if (*(char *)(iVar6 + 0x83) == '\0') {
        return 0;
      }
      if ((*(ushort *)(iVar10 + 0x10) & 0x40) == 0) {
        return 0;
      }
      if (*(short *)(iVar6 + 0x1c) == 0xff) {
        return 0;
      }
    }
  }
  if (((*(ushort *)(iVar9 + 0x10) & 0x80) != 0) &&
     (*(char *)(iVar5 + 0x88) == *(char *)(iVar6 + 0x88))) {
    return 0;
  }
  uVar3 = *(ushort *)(iVar10 + 0x12) & 0x3c0;
  if ((uVar3 != 0) && (*(char *)(iVar5 + 0x83) != '\x10')) {
    return 0;
  }
  if ((((*(ushort *)(iVar9 + 0x12) & 0xc00) == 0) || (*(char *)(iVar6 + 0x83) == '\0')) ||
     (*(char *)(iVar6 + 0x83) == ' ')) {
    iVar11 = 6;
    iVar10 = iVar6;
    do {
      sVar1 = *(short *)(iVar5 + 0x26c);
      if (sVar1 == *(short *)(iVar10 + 0x20c)) {
        return 0;
      }
      if (sVar1 == *(short *)(iVar10 + 0x20e)) {
        return 0;
      }
      if (sVar1 == *(short *)(iVar10 + 0x210)) {
        return 0;
      }
      if (sVar1 == *(short *)(iVar10 + 0x212)) {
        return 0;
      }
      if (sVar1 == *(short *)(iVar10 + 0x214)) {
        return 0;
      }
      if (sVar1 == *(short *)(iVar10 + 0x216)) {
        return 0;
      }
      if (sVar1 == *(short *)(iVar10 + 0x218)) {
        return 0;
      }
      if (sVar1 == *(short *)(iVar10 + 0x21a)) {
        return 0;
      }
      iVar10 = iVar10 + 0x10;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    if ((*(ushort *)(*(int *)(param_2 + 0x28) + 2) & 0x40) != 0) {
      iVar11 = 6;
      iVar10 = iVar8;
      do {
        sVar1 = *(short *)(iVar5 + 0x26c);
        if (sVar1 == *(short *)(iVar10 + 0x20c)) {
          return 0;
        }
        if (sVar1 == *(short *)(iVar10 + 0x20e)) {
          return 0;
        }
        if (sVar1 == *(short *)(iVar10 + 0x210)) {
          return 0;
        }
        if (sVar1 == *(short *)(iVar10 + 0x212)) {
          return 0;
        }
        if (sVar1 == *(short *)(iVar10 + 0x214)) {
          return 0;
        }
        if (sVar1 == *(short *)(iVar10 + 0x216)) {
          return 0;
        }
        if (sVar1 == *(short *)(iVar10 + 0x218)) {
          return 0;
        }
        if (sVar1 == *(short *)(iVar10 + 0x21a)) {
          return 0;
        }
        iVar10 = iVar10 + 0x10;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
    }
    if (((int)*(short *)(iVar6 + 0x272) & param_3) == 0) {
      if ((((*(char *)(iVar7 + 0x83) == '\0') && (*(char *)(iVar8 + 0x83) == '\0')) &&
          ((*(char *)(iVar8 + 0x6fc) != '\0' &&
           ((*(char *)(iVar7 + 0x88) == *(char *)(iVar8 + 0x88) &&
            ((*(ushort *)(iVar9 + 0x12) & 0x10) == 0)))))) && (uVar3 == 0)) {
        return 0;
      }
      uVar4 = 1;
    }
    else {
      uVar4 = 0;
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}



// ==== 800300bc  zz_00300bc_ ====

/* WARNING: Removing unreachable block (ram,0x80030320) */
/* WARNING: Removing unreachable block (ram,0x800300cc) */

void zz_00300bc_(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  float local_38;
  float local_34;
  float local_30;
  
  iVar2 = *(int *)(param_1 + 0x20);
  iVar3 = *(int *)(param_2 + 0x20);
  if (param_3 == 2) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x30),(float *)(param_1 + 0x3c),&local_38);
    dVar4 = gnt4_PSVECMag_bl(&local_38);
    if (dVar4 <= (double)FLOAT_80436f68) {
      local_38 = *(float *)(iVar2 + 0x38);
      local_34 = *(float *)(iVar2 + 0x3c);
      local_30 = *(float *)(iVar2 + 0x40);
    }
  }
  else if (param_3 < 2) {
    if (param_3 == 0) {
      gnt4_PSVECSubtract_bl((float *)(iVar2 + 0x20),(float *)(iVar2 + 0x2c),&local_38);
      dVar4 = gnt4_PSVECMag_bl(&local_38);
      if (dVar4 <= (double)FLOAT_80436f68) {
        local_38 = *(float *)(iVar2 + 0x38);
        local_34 = *(float *)(iVar2 + 0x3c);
        local_30 = *(float *)(iVar2 + 0x40);
      }
    }
    else if (-1 < param_3) {
      gnt4_PSVECSubtract_bl((float *)(iVar3 + 0x20),(float *)(iVar2 + 0x20),&local_38);
    }
  }
  else if (param_3 == 4) {
    if (*(char *)(iVar2 + 0x83) == '\0') {
      local_38 = *(float *)(iVar2 + 0x8dc);
      local_34 = *(float *)(iVar2 + 0x8ec);
      local_30 = *(float *)(iVar2 + 0x8fc);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x24);
      if (*(char *)(iVar1 + 0x83) == '\0') {
        local_38 = *(float *)(iVar1 + 0x8dc);
        local_34 = *(float *)(iVar1 + 0x8ec);
        local_30 = *(float *)(iVar1 + 0x8fc);
      }
      else {
        local_38 = *(float *)(iVar2 + 0x11c);
        local_34 = *(float *)(iVar2 + 300);
        local_30 = *(float *)(iVar2 + 0x13c);
      }
    }
  }
  else if (param_3 < 4) {
    gnt4_PSVECSubtract_bl((float *)(param_2 + 100),(float *)(param_1 + 100),&local_38);
  }
  if (ABS(local_30 * local_30 + local_38 * local_38 + local_34 * local_34) < FLOAT_80436fc0) {
    local_34 = FLOAT_80436f68;
    local_38 = FLOAT_80436f68;
    local_30 = FLOAT_80436f74;
  }
  dVar4 = (double)local_38;
  dVar5 = (double)local_30;
  dVar6 = ABS((double)((float)(dVar4 * dVar4) + (float)(dVar5 * dVar5)));
  iVar2 = FUN_800452a0(dVar4,dVar5);
  *(short *)(iVar3 + 0x284) = (short)iVar2;
  iVar2 = FUN_800452a0((double)local_34,(double)(float)dVar6);
  *(short *)(iVar3 + 0x282) = -(short)iVar2;
  iVar2 = *(int *)(param_1 + 0x2c) + (uint)*(byte *)(param_1 + 0x11) * 0x18;
  *(short *)(iVar3 + 0x284) = *(short *)(iVar3 + 0x284) + *(char *)(iVar2 + 0x14) * -0x100;
  *(short *)(iVar3 + 0x282) = *(short *)(iVar3 + 0x282) + *(char *)(iVar2 + 0x15) * -0x100;
  if (((*(byte *)(iVar3 + 0x1da) & 2) != 0) &&
     (iVar2 = *(int *)(param_2 + 0x24), *(char *)(iVar2 + 0x83) == '\0')) {
    *(undefined2 *)(iVar2 + 0x284) = *(undefined2 *)(iVar3 + 0x284);
    *(undefined2 *)(iVar2 + 0x282) = *(undefined2 *)(iVar3 + 0x282);
  }
  return;
}



// ==== 80030348  zz_0030348_ ====

void zz_0030348_(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  (*(code *)(&PTR_LAB_802cff98)[param_3])();
  (*(code *)(&PTR_LAB_802cff98)[param_4])(param_2);
  return;
}



// ==== 800303b0  zz_00303b0_ ====

undefined4 zz_00303b0_(undefined4 param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  undefined4 uVar2;
  
  bVar1 = (&DAT_802cfeac)[param_3];
  if (bVar1 == 0xff) {
    uVar2 = 0;
  }
  else if ((bVar1 & 0x80) == 0) {
    uVar2 = (*(code *)(&PTR_FUN_802cfea0)[bVar1 & 0x7f])();
  }
  else {
    uVar2 = (*(code *)(&PTR_FUN_802cfea0)[bVar1 & 0x7f])(param_2,param_1);
  }
  return uVar2;
}



// ==== 80030420  zz_0030420_ ====

undefined4 zz_0030420_(undefined4 param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  undefined4 uVar2;
  
  bVar1 = (&DAT_802cfefc)[param_3];
  if (bVar1 == 0xff) {
    uVar2 = 0;
  }
  else if ((bVar1 & 0x80) == 0) {
    uVar2 = (*(code *)(&PTR_FUN_802cfed4)[bVar1 & 0x7f])();
  }
  else {
    uVar2 = (*(code *)(&PTR_FUN_802cfed4)[bVar1 & 0x7f])(param_2,param_1);
  }
  return uVar2;
}



// ==== 80030490  zz_0030490_ ====

undefined4 zz_0030490_(undefined4 param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  undefined4 uVar2;
  
  bVar1 = (&DAT_802cff68)[param_3];
  if (bVar1 == 0xff) {
    uVar2 = 0;
  }
  else if ((bVar1 & 0x80) == 0) {
    uVar2 = (*(code *)(&PTR_FUN_802cff2c)[bVar1 & 0x7f])();
  }
  else {
    uVar2 = (*(code *)(&PTR_FUN_802cff2c)[bVar1 & 0x7f])(param_2,param_1);
  }
  return uVar2;
}



// ==== 80030500  FUN_80030500 ====

undefined4 FUN_80030500(int param_1,int param_2)

{
  undefined4 uVar1;
  double dVar2;
  float afStack_18 [4];
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0xc),afStack_18);
  dVar2 = gnt4_PSVECMag_bl(afStack_18);
  if (dVar2 <= (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30))) {
    dVar2 = gnt4_PSVECSquareMag_bl(afStack_18);
    if ((double)FLOAT_80436f68 < dVar2) {
      gnt4_PSVECNormalize_bl(afStack_18,afStack_18);
      gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x30),afStack_18,afStack_18);
      gnt4_PSVECAdd_bl((float *)(param_2 + 0xc),afStack_18,(float *)&DAT_803b0720);
      uVar1 = 1;
    }
    else {
      DAT_803b0720 = *(undefined4 *)(param_2 + 0xc);
      DAT_803b0724 = *(undefined4 *)(param_2 + 0x10);
      uVar1 = 1;
      DAT_803b0728 = *(undefined4 *)(param_2 + 0x14);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 800305d8  FUN_800305d8 ====

/* WARNING: Removing unreachable block (ram,0x80030a20) */
/* WARNING: Removing unreachable block (ram,0x80030a18) */
/* WARNING: Removing unreachable block (ram,0x800305f0) */
/* WARNING: Removing unreachable block (ram,0x800305e8) */

undefined4 FUN_800305d8(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  int local_108;
  float afStack_104 [3];
  float local_f8;
  float local_f4;
  float local_f0;
  int local_ec;
  int local_e8;
  int local_d4 [6];
  float local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  float local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  float afStack_a4 [12];
  float afStack_74 [15];
  
  iVar6 = *(int *)(*(int *)(param_2 + 4) + 0x20);
  iVar5 = *(int *)(*(int *)(param_2 + 4) + 0x28);
  gnt4_PSMTXCopy_bl(*(float **)(param_2 + 8),afStack_74);
  gnt4_PSMTXTrans_bl((double)*(float *)(iVar5 + 0xc),(double)*(float *)(iVar5 + 0x10),
                     (double)*(float *)(iVar5 + 0x14),afStack_a4);
  gnt4_PSMTXConcat_bl(afStack_74,afStack_a4,afStack_74);
  dVar8 = (double)(FLOAT_80436f78 / *(float *)(iVar6 + 0xc0));
  gnt4_PSMTXScale_bl(dVar8,dVar8,dVar8,afStack_a4);
  gnt4_PSMTXConcat_bl(afStack_74,afStack_a4,afStack_74);
  gnt4_PSMTXInverse_bl(afStack_74,afStack_a4);
  gnt4_PSMTXMultVec_bl(afStack_a4,(float *)(param_1 + 0xc),&local_f8);
  fVar1 = *(float *)(iVar6 + 0xc0);
  fVar2 = *(float *)(param_1 + 0x30);
  fVar3 = fVar2 + *(float *)(iVar5 + 0x18) * fVar1;
  fVar4 = fVar2 + *(float *)(iVar5 + 0x1c) * fVar1;
  fVar2 = fVar2 + *(float *)(iVar5 + 0x20) * fVar1;
  if (((((-fVar3 <= local_f8) && (local_f8 <= fVar3)) && (-fVar4 <= local_f4)) &&
      ((local_f4 <= fVar4 && (-fVar2 <= local_f0)))) && (local_f0 <= fVar2)) {
    piVar7 = local_d4;
    dVar8 = (double)FLOAT_80436fc4;
    dVar10 = (double)FLOAT_80436f68;
    iVar5 = 0;
    iVar6 = 0;
    for (local_108 = 0; local_108 < 6; local_108 = local_108 + 1) {
      gnt4_PSVECSubtract_bl
                ((float *)(param_1 + 0xc),
                 (float *)(param_2 + (char)(&DAT_802cffc8)[local_108 * 4] * 0xc + 0x30),&local_f8);
      dVar9 = gnt4_PSQUATDotProduct_bl(&local_f8,(float *)(param_2 + local_108 * 0x18 + 0x90));
      if ((double)(float)ABS(dVar9) < dVar8) {
        dVar9 = (double)FLOAT_80436f68;
      }
      if ((dVar9 < dVar10) || (*(float *)(param_1 + 0x30) <= (float)ABS(dVar9))) {
        if (dVar9 < (double)FLOAT_80436f68) {
          iVar6 = iVar6 + 1;
        }
      }
      else {
        iVar5 = iVar5 + 1;
        *piVar7 = local_108;
        piVar7 = piVar7 + 1;
      }
    }
    if (iVar5 == 2) {
      iVar5 = zz_0039938_(local_d4,(int)&local_ec);
      if (iVar5 == 0) {
        iVar5 = param_2 + local_ec * 0xc;
        DAT_803b0720 = *(undefined4 *)(iVar5 + 0x30);
        DAT_803b0724 = *(undefined4 *)(iVar5 + 0x34);
        DAT_803b0728 = *(undefined4 *)(iVar5 + 0x38);
      }
      else {
        iVar6 = param_2 + local_ec * 0xc;
        local_bc = *(float *)(iVar6 + 0x30);
        local_b8 = *(undefined4 *)(iVar6 + 0x34);
        iVar5 = param_2 + local_e8 * 0xc;
        local_b4 = *(undefined4 *)(iVar6 + 0x38);
        local_b0 = *(float *)(iVar5 + 0x30);
        local_ac = *(undefined4 *)(iVar5 + 0x34);
        local_a8 = *(undefined4 *)(iVar5 + 0x38);
        gnt4_PSVECSubtract_bl(&local_b0,&local_bc,&local_f8);
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_bc,afStack_104);
        gnt4_PSVECNormalize_bl(&local_f8,&local_f8);
        dVar8 = gnt4_PSQUATDotProduct_bl(afStack_104,&local_f8);
        gnt4_PSQUATScale_bl(dVar8,&local_f8,&local_f8);
        gnt4_PSVECAdd_bl(&local_bc,&local_f8,(float *)&DAT_803b0720);
      }
    }
    else if (iVar5 < 2) {
      if (iVar5 == 0) {
        if (iVar6 != 6) {
          return 0;
        }
        DAT_803b0720 = *(undefined4 *)(param_1 + 0xc);
        DAT_803b0724 = *(undefined4 *)(param_1 + 0x10);
        DAT_803b0728 = *(undefined4 *)(param_1 + 0x14);
      }
      else {
        if (iVar5 < 0) {
          return 0;
        }
        gnt4_PSVECSubtract_bl
                  ((float *)(param_1 + 0xc),
                   (float *)(param_2 + (char)(&DAT_802cffc8)[local_d4[0] * 4] * 0xc + 0x30),
                   &local_f8);
        dVar8 = gnt4_PSQUATDotProduct_bl(&local_f8,(float *)(param_2 + local_d4[0] * 0x18 + 0x90));
        gnt4_PSQUATScale_bl(dVar8,(float *)(param_2 + local_d4[0] * 0x18 + 0x90),&local_f8);
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_f8,(float *)&DAT_803b0720);
      }
    }
    else {
      if (3 < iVar5) {
        return 0;
      }
      iVar5 = zz_0039a48_(local_d4,&local_108);
      if (iVar5 == 0) {
        DAT_803b0720 = *(undefined4 *)(param_1 + 0xc);
        DAT_803b0724 = *(undefined4 *)(param_1 + 0x10);
        DAT_803b0728 = *(undefined4 *)(param_1 + 0x14);
      }
      else {
        iVar5 = param_2 + local_108 * 0xc;
        DAT_803b0720 = *(undefined4 *)(iVar5 + 0x30);
        DAT_803b0724 = *(undefined4 *)(iVar5 + 0x34);
        DAT_803b0728 = *(undefined4 *)(iVar5 + 0x38);
      }
    }
    return 1;
  }
  return 0;
}



// ==== 80030a3c  FUN_80030a3c ====

/* WARNING: Removing unreachable block (ram,0x80030af4) */

undefined4 FUN_80030a3c(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  byte bVar3;
  double dVar4;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float afStack_1c [4];
  
  iVar1 = FUN_80039564((float *)(param_2 + 0x34),param_1,&DAT_803b0720);
  if (iVar1 == 1) {
    uVar2 = 1;
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x34),afStack_1c);
    dVar4 = gnt4_PSQUATDotProduct_bl(afStack_1c,(float *)(param_2 + 100));
    bVar3 = dVar4 < (double)FLOAT_80436f68;
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x40),afStack_1c);
    dVar4 = gnt4_PSQUATDotProduct_bl(afStack_1c,(float *)(param_2 + 0x70));
    if (dVar4 < (double)FLOAT_80436f68) {
      bVar3 = bVar3 | 2;
    }
    if (bVar3 == 2) {
      local_28 = *(float *)(param_2 + 0x40);
      local_24 = *(undefined4 *)(param_2 + 0x44);
      local_20 = *(undefined4 *)(param_2 + 0x48);
    }
    else if (bVar3 < 2) {
      if (bVar3 == 0) {
        gnt4_PSQUATScale_bl(dVar4,(float *)(param_2 + 0x70),&local_28);
        gnt4_PSVECAdd_bl((float *)(param_2 + 0x40),&local_28,&local_28);
      }
      else {
        local_28 = *(float *)(param_2 + 0x34);
        local_24 = *(undefined4 *)(param_2 + 0x38);
        local_20 = *(undefined4 *)(param_2 + 0x3c);
      }
    }
    else if (bVar3 < 4) {
      return 0;
    }
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_28,afStack_1c);
    dVar4 = gnt4_PSVECMag_bl(afStack_1c);
    if ((double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30)) <= dVar4) {
      uVar2 = 0;
    }
    else {
      gnt4_PSVECSubtract_bl(&local_28,(float *)(param_1 + 0xc),afStack_1c);
      dVar4 = gnt4_PSVECMag_bl(afStack_1c);
      if (dVar4 <= (double)FLOAT_80436f68) {
        DAT_803b0720 = local_28;
        DAT_803b0724 = local_24;
        DAT_803b0728 = local_20;
      }
      else {
        gnt4_PSVECNormalize_bl(afStack_1c,afStack_1c);
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x30),afStack_1c,afStack_1c);
        gnt4_PSVECAdd_bl((float *)(param_1 + 0xc),afStack_1c,&DAT_803b0720);
      }
      uVar2 = 1;
    }
  }
  return uVar2;
}



// ==== 80030c30  FUN_80030c30 ====

/* WARNING: Removing unreachable block (ram,0x80030fc4) */
/* WARNING: Removing unreachable block (ram,0x80030fbc) */
/* WARNING: Removing unreachable block (ram,0x80030c48) */
/* WARNING: Removing unreachable block (ram,0x80030c40) */
/* WARNING: Removing unreachable block (ram,0x80030e58) */

undefined4 FUN_80030c30(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float afStack_60 [3];
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  
  iVar8 = 0;
  iVar5 = param_2;
  iVar7 = param_2;
  do {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x4c),afStack_60);
    dVar9 = gnt4_PSQUATDotProduct_bl(afStack_60,(float *)(iVar5 + 0x7c));
    if (((*(ushort *)(*(int *)(*(int *)(param_2 + 4) + 0x28) + 2) & 0x40) != 0) &&
       (dVar9 < (double)FLOAT_80436f68)) {
      return 0;
    }
    if ((float)ABS(dVar9) <= *(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30)) {
      gnt4_PSQUATScale_bl(dVar9,(float *)(iVar5 + 0x7c),afStack_60);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),afStack_60,afStack_60);
      uVar1 = zz_0039aec_(afStack_60,(float *)(iVar7 + 0x34),(float *)(iVar5 + 0x7c));
      if (uVar1 != 0) {
        if (dVar9 < (double)FLOAT_80436f68) {
          dVar9 = -(double)*(float *)(param_2 + 0x30);
        }
        else {
          dVar9 = (double)*(float *)(param_2 + 0x30);
        }
        gnt4_PSQUATScale_bl(dVar9,(float *)(param_2 + iVar8 * 0x18 + 0x7c),&local_6c);
        gnt4_PSVECAdd_bl(afStack_60,&local_6c,&DAT_803b0720);
        return 1;
      }
    }
    iVar8 = iVar8 + 1;
    iVar7 = iVar7 + 0x24;
    iVar5 = iVar5 + 0x18;
  } while (iVar8 < 2);
  dVar9 = (double)FLOAT_80436fc8;
  dVar11 = (double)FLOAT_80436f68;
  pcVar6 = &DAT_80433688;
  iVar5 = 0;
  do {
    pfVar4 = (float *)(param_2 + *pcVar6 * 0xc + 0x34);
    local_54 = *pfVar4;
    local_50 = pfVar4[1];
    pfVar3 = (float *)(param_2 + pcVar6[1] * 0xc + 0x34);
    local_4c = pfVar4[2];
    local_48 = *pfVar3;
    local_44 = pfVar3[1];
    local_40 = pfVar3[2];
    gnt4_PSVECSubtract_bl(&local_48,&local_54,afStack_60);
    gnt4_PSVECNormalize_bl(afStack_60,afStack_60);
    uVar1 = 0;
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_48,&local_6c);
    dVar10 = gnt4_PSQUATDotProduct_bl(&local_6c,afStack_60);
    if (dVar11 < dVar10) {
      uVar1 = 2;
    }
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_54,&local_6c);
    dVar10 = gnt4_PSQUATDotProduct_bl(&local_6c,afStack_60);
    if (dVar10 < dVar11) {
      uVar1 = uVar1 | 1;
    }
    if (uVar1 == 1) {
      local_6c = local_54;
      local_68 = local_50;
      local_64 = local_4c;
    }
    else if (uVar1 == 0) {
      gnt4_PSQUATScale_bl(dVar10,afStack_60,&local_6c);
      gnt4_PSVECAdd_bl(&local_54,&local_6c,&local_6c);
    }
    else {
      if (2 < uVar1) {
        return 0;
      }
      local_6c = local_48;
      local_68 = local_44;
      local_64 = local_40;
    }
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_6c,afStack_60);
    dVar10 = gnt4_PSVECMag_bl(afStack_60);
    if (dVar10 < dVar9) {
      local_78 = local_6c;
      local_74 = local_68;
      local_70 = local_64;
      dVar9 = dVar10;
    }
    iVar5 = iVar5 + 1;
    pcVar6 = pcVar6 + 1;
  } while (iVar5 < 4);
  if (((double)FLOAT_80436fc8 == dVar9) ||
     ((double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30)) <= dVar9)) {
    uVar2 = 0;
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_78,afStack_60);
    dVar9 = gnt4_PSVECSquareMag_bl(afStack_60);
    if ((double)FLOAT_80436f68 < dVar9) {
      gnt4_PSVECNormalize_bl(afStack_60,afStack_60);
      gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x30),afStack_60,afStack_60);
      gnt4_PSVECAdd_bl(&local_78,afStack_60,&DAT_803b0720);
      uVar2 = 1;
    }
    else {
      uVar2 = 1;
      DAT_803b0720 = local_78;
      DAT_803b0724 = local_74;
      DAT_803b0728 = local_70;
    }
  }
  return uVar2;
}



// ==== 80030fe0  FUN_80030fe0 ====

/* WARNING: Removing unreachable block (ram,0x80031140) */
/* WARNING: Removing unreachable block (ram,0x80030ff0) */

undefined4 FUN_80030fe0(int param_1,int param_2)

{
  int iVar1;
  double dVar2;
  double dVar3;
  float afStack_38 [3];
  float afStack_2c [5];
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0xc),afStack_2c);
  dVar2 = gnt4_PSQUATDotProduct_bl(afStack_2c,(float *)(param_2 + 0x30));
  if ((*(ushort *)(*(int *)(*(int *)(param_2 + 4) + 0x28) + 2) & 0x40) != 0) {
    iVar1 = *(int *)(*(int *)(param_1 + 4) + 0x20);
    if (*(char *)(iVar1 + 0x83) == '\0') {
      gnt4_PSVECSubtract_bl((float *)(iVar1 + 0x20),(float *)(param_2 + 0xc),afStack_2c);
      dVar3 = gnt4_PSQUATDotProduct_bl(afStack_2c,(float *)(param_2 + 0x30));
      if (dVar3 < (double)FLOAT_80436f68) {
        return 0;
      }
    }
    else if (dVar2 < (double)FLOAT_80436f68) {
      return 0;
    }
  }
  if ((float)ABS(dVar2) < *(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x48)) {
    gnt4_PSQUATScale_bl(dVar2,(float *)(param_2 + 0x30),afStack_2c);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),afStack_2c,afStack_38);
    gnt4_PSVECSubtract_bl(afStack_38,(float *)(param_2 + 0xc),afStack_2c);
    dVar3 = gnt4_PSVECMag_bl(afStack_2c);
    if (dVar3 <= (double)*(float *)(param_2 + 0x4c)) {
      if (dVar2 < (double)FLOAT_80436f68) {
        dVar2 = -(double)*(float *)(param_2 + 0x48);
      }
      else {
        dVar2 = (double)*(float *)(param_2 + 0x48);
      }
      gnt4_PSQUATScale_bl(dVar2,(float *)(param_2 + 0x30),afStack_2c);
      gnt4_PSVECAdd_bl(afStack_38,afStack_2c,(float *)&DAT_803b0720);
      return 1;
    }
  }
  return 0;
}



