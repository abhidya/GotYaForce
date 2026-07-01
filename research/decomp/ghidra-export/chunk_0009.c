// ==== 8006965c  FUN_8006965c ====

undefined4 FUN_8006965c(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x661) == '\x02') {
    if ((*(uint *)(param_1 + 0x5e0) & 2) == 0) {
      if ((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) {
        uVar1 = 0;
      }
      else {
        iVar2 = zz_006a750_(param_1,0x16);
        if (iVar2 == 0) {
          uVar1 = 0;
        }
        else {
          uVar1 = 1;
          *(byte *)(param_1 + 0x58f) = (byte)(*(ushort *)(param_1 + 0x5d8) >> 4) & 0xf;
          *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) & 0xff0f;
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



// ==== 800696f4  FUN_800696f4 ====

undefined4 FUN_800696f4(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  if ((*(char *)(param_1 + 0x661) == '\x02') || (*(char *)(param_1 + 0x661) == '\x05')) {
    uVar2 = zz_00694c0_(param_1);
    if (uVar2 == 0) {
      uVar1 = 0;
    }
    else if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
      if ((*(uint *)(param_1 + 0x5d4) & 0x80) == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = zz_006a750_(param_1,0x20);
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



// ==== 80069788  FUN_80069788 ====

undefined4 FUN_80069788(int param_1)

{
  undefined4 uVar1;
  
  if ((*(char *)(param_1 + 0x661) == '\x02') || (*(char *)(param_1 + 0x661) == '\x05')) {
    if (*(char *)(param_1 + 0x588) == '\0') {
      uVar1 = 0;
    }
    else if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
      if ((*(short *)(param_1 + 0x736) < 1) || ((*(uint *)(param_1 + 0x5d4) & 0x80) != 0)) {
        uVar1 = zz_006a750_(param_1,0x22);
      }
      else {
        uVar1 = 0;
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



// ==== 80069814  FUN_80069814 ====

undefined4 FUN_80069814(int param_1)

{
  if (PTR_DAT_80433934[*(char *)(param_1 + 0x88) * 0x3c + 0x103] == '\0') {
    return 0;
  }
  if ((*(uint *)(param_1 + 0x5d4) & 0x200) == 0) {
    return 0;
  }
  *(undefined1 *)(param_1 + 0x6fb) = 6;
  return 0;
}



// ==== 80069860  FUN_80069860 ====

undefined4 FUN_80069860(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 2) == 0) {
    if ((*(uint *)(param_1 + 0x5d4) & 2) == 0) {
      uVar1 = 0;
    }
    else if (*(short *)(param_1 + 0x736) < 1) {
      uVar1 = 0;
    }
    else {
      uVar1 = zz_006a750_(param_1,0x1c);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 800698c0  FUN_800698c0 ====

undefined4 FUN_800698c0(int param_1)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x588) == '\0') {
    uVar1 = 0;
  }
  else if ((*(short *)(param_1 + 0x736) < 1) || ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0)) {
    uVar1 = zz_006a750_(param_1,0x1b);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80069918  FUN_80069918 ====

undefined4 FUN_80069918(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x5b4) & 0xf0000) == 0) {
    if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
      uVar1 = zz_006a750_(param_1,0x1f);
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



// ==== 80069960  FUN_80069960 ====

undefined4 FUN_80069960(int param_1)

{
  undefined4 uVar1;
  
  if (PTR_DAT_80433934[0x1f] == '\0') {
    uVar1 = 0;
  }
  else if (PTR_DAT_80433934[0x52] == '\x05') {
    if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
      if (*(char *)(param_1 + 0x5e4) == '\0') {
        uVar1 = zz_006a750_(param_1,0x2b);
      }
      else {
        uVar1 = 0;
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



// ==== 800699d8  FUN_800699d8 ====

uint FUN_800699d8(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = zz_0069cb0_(param_1);
  if (iVar1 == 0) {
    iVar1 = zz_0069c50_(param_1);
    if (iVar1 == 0) {
      iVar1 = zz_0069bf0_(param_1);
      if (iVar1 == 0) {
        iVar1 = zz_0069b98_(param_1);
        if (iVar1 == 0) {
          iVar1 = zz_0069b10_(param_1);
          if (iVar1 == 0) {
            uVar2 = zz_0069a88_(param_1);
            uVar2 = (-uVar2 | uVar2) >> 0x1f;
          }
          else {
            uVar2 = 1;
          }
        }
        else {
          uVar2 = 1;
        }
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 80069a88  zz_0069a88_ ====

undefined4 zz_0069a88_(int param_1)

{
  undefined4 uVar1;
  
  *(undefined1 *)(param_1 + 0x595) = 0;
  if ((*(uint *)(param_1 + 0x5d4) & 0x20) == 0) {
    uVar1 = 0;
  }
  else {
    if ((*(char *)(param_1 + 0x748) == '\x02') || ((*(byte *)(param_1 + 0x58e) & 1) != 0)) {
      *(undefined1 *)(param_1 + 0x585) = 1;
    }
    else {
      *(undefined1 *)(param_1 + 0x585) = 0;
    }
    if (((uint)*(byte *)(param_1 + 0x58e) & 1 << (int)*(char *)(param_1 + 0x585)) == 0) {
      uVar1 = zz_0069dd0_(param_1);
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}



// ==== 80069b10  zz_0069b10_ ====

undefined4 zz_0069b10_(int param_1)

{
  undefined4 uVar1;
  
  *(undefined1 *)(param_1 + 0x595) = 0;
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) == 0) {
    uVar1 = 0;
  }
  else if (*(char *)(param_1 + 0x748) == '\x01') {
    uVar1 = 0;
  }
  else if ((*(byte *)(param_1 + 0x58e) & 2) == 0) {
    if (((*(byte *)(param_1 + 0x58e) & 1) == 0) && ((*(byte *)(param_1 + 0x7d2) & 8) == 0)) {
      uVar1 = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x585) = 1;
      uVar1 = zz_0069dd0_(param_1);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80069b98  zz_0069b98_ ====

undefined4 zz_0069b98_(int param_1)

{
  undefined4 uVar1;
  
  *(undefined1 *)(param_1 + 0x595) = 0;
  if ((*(byte *)(param_1 + 0x58e) & 4) == 0) {
    if ((*(uint *)(param_1 + 0x5d4) & 0x80) == 0) {
      uVar1 = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x585) = 2;
      uVar1 = zz_0069dd0_(param_1);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80069bf0  zz_0069bf0_ ====

undefined4 zz_0069bf0_(int param_1)

{
  undefined4 uVar1;
  
  *(undefined1 *)(param_1 + 0x595) = 0;
  if ((*(byte *)(param_1 + 0x58e) & 8) == 0) {
    if ((*(uint *)(param_1 + 0x5d4) & 0x400) == 0) {
      uVar1 = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x585) = 3;
      *(undefined1 *)(param_1 + 0x595) = 1;
      uVar1 = zz_0069dd0_(param_1);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80069c50  zz_0069c50_ ====

undefined4 zz_0069c50_(int param_1)

{
  undefined4 uVar1;
  
  *(undefined1 *)(param_1 + 0x595) = 0;
  if ((*(byte *)(param_1 + 0x58e) & 0x20) == 0) {
    if ((*(uint *)(param_1 + 0x5d4) & 0x1000) == 0) {
      uVar1 = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x585) = 5;
      *(undefined1 *)(param_1 + 0x595) = 1;
      uVar1 = zz_0069dd0_(param_1);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80069cb0  zz_0069cb0_ ====

undefined4 zz_0069cb0_(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x595) = 0;
  if (*(char *)(param_1 + 0x4a0) == '\0') {
    return 0;
  }
  if (((*(uint *)(param_1 + 0x5e0) & 2) != 0) && (*(char *)(param_1 + 0x584) == '\x05')) {
    return 0;
  }
  if (*(char *)(param_1 + 0x593) < '\x01') {
    if ((*(byte *)(param_1 + 0x58e) & 0x20) != 0) {
      return 0;
    }
    if ((*(uint *)(param_1 + 0x5d4) & 0x1000) == 0) {
      return 0;
    }
    *(undefined1 *)(param_1 + 0x593) = 6;
  }
  if (*(char *)(param_1 + 0x4a0) == '\x02') {
    uVar1 = 1;
  }
  else if ((*(char *)(*(int *)(param_1 + 0x4a4) + 0x3e6) == '\0') &&
          (*(char *)(*(int *)(param_1 + 0x4a4) + 0x593) < '\x01')) {
    uVar1 = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0x585) = 5;
    *(undefined1 *)(param_1 + 0x595) = 1;
    iVar2 = zz_0069dd0_(param_1);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      iVar2 = *(int *)(param_1 + 0x4a4);
      uVar1 = 1;
      *(undefined1 *)(iVar2 + 0x585) = 5;
      *(undefined1 *)(iVar2 + 0x584) = 5;
      *(uint *)(iVar2 + 0x5e0) = *(uint *)(iVar2 + 0x5e0) | 3;
    }
  }
  return uVar1;
}



// ==== 80069dd0  zz_0069dd0_ ====

undefined4 zz_0069dd0_(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  if (*(char *)(*(int *)(param_1 + 0x4b0) + (int)*(char *)(param_1 + 0x585) + 0xb8) == -1) {
    uVar2 = 0;
  }
  else {
    if ((*(uint *)(param_1 + 0x5e0) & 3) != 0) {
      if (((int)*(char *)(param_1 + 0x57a) & 1 << (int)*(char *)(param_1 + 0x585)) == 0) {
        return 0;
      }
      zz_005c080_(param_1);
      *(undefined1 *)(param_1 + 0x595) = 1;
    }
    cVar1 = *(char *)(*(int *)(param_1 + 0x4b0) + (int)*(char *)(param_1 + 0x585) + 0xb8);
    if (cVar1 == '\x01') {
      uVar2 = zz_0069ea4_(param_1);
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      uVar2 = zz_0069fe0_(param_1);
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}



// ==== 80069ea4  zz_0069ea4_ ====

undefined4 zz_0069ea4_(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  if ((*(char *)(param_1 + 0x595) == '\0') && (FLOAT_8043762c < *(float *)(param_1 + 0x694))) {
    return 0;
  }
  uVar1 = *(uint *)(param_1 + 0x5e0);
  if ((uVar1 & 0x100) == 0) {
    if ((uVar1 & 0x80) == 0) {
      if ((uVar1 & 0x20) == 0) {
        if (((uVar1 & 0x40) == 0) && (*(char *)(param_1 + 0x5e4) != '\x04')) {
          if ((uVar1 & 0x10) == 0) {
            *(undefined1 *)(param_1 + 0x586) = 0;
          }
          else {
            *(undefined1 *)(param_1 + 0x586) = 1;
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x586) = 3;
        }
      }
      else if (*(char *)(param_1 + 0x7cc) == '\0') {
        if ((uVar1 & 0x40) == 0) {
          *(undefined1 *)(param_1 + 0x586) = 0;
        }
        else {
          *(undefined1 *)(param_1 + 0x586) = 3;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x586) = 2;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x586) = 4;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x586) = 5;
  }
  uVar2 = zz_006c674_(param_1);
  *(char *)(param_1 + 0x587) = (char)uVar2;
  uVar2 = zz_006a104_(param_1,(char *)(*(int *)(*(int *)(param_1 + 0x4ec) +
                                               *(char *)(param_1 + 0x585) * 4) +
                                      *(char *)(param_1 + 0x586) * 0x10 +
                                      *(char *)(param_1 + 0x587) * 4));
  return uVar2;
}



// ==== 80069fe0  zz_0069fe0_ ====

undefined4 zz_0069fe0_(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(param_1 + 0x5e0);
  if (FLOAT_8043762c < *(float *)(param_1 + 0x6a4)) {
    *(undefined1 *)(param_1 + 0x586) = 5;
  }
  if ((uVar2 & 0x80) == 0) {
    if ((uVar2 & 0x20) == 0) {
      if ((uVar2 & 0x40) == 0) {
        if (*(char *)(param_1 + 0x5e4) != '\x04') {
          if ((uVar2 & 0x200) == 0) {
            *(undefined1 *)(param_1 + 0x586) = 0;
          }
          else {
            *(undefined1 *)(param_1 + 0x586) = 3;
          }
          goto LAB_8006a09c;
        }
      }
      *(undefined1 *)(param_1 + 0x586) = 2;
    }
    else if (*(char *)(param_1 + 0x7cc) == '\0') {
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        *(undefined1 *)(param_1 + 0x586) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0x586) = 2;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x586) = 1;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x586) = 4;
  }
LAB_8006a09c:
  if (((*(char *)(param_1 + 0x595) != '\0') || (*(float *)(param_1 + 0x694) <= FLOAT_8043762c)) ||
     (*(char *)(param_1 + 0x586) == '\x03')) {
    uVar1 = zz_006a104_(param_1,(char *)(*(int *)(*(int *)(param_1 + 0x4ec) +
                                                 *(char *)(param_1 + 0x585) * 4) +
                                        *(char *)(param_1 + 0x586) * 4));
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8006a104  zz_006a104_ ====

undefined4 zz_006a104_(int param_1,char *param_2)

{
  char cVar1;
  bool bVar2;
  float fVar3;
  undefined4 uVar4;
  int iVar5;
  
  if (*param_2 == -1) {
    uVar4 = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x584) = *(undefined1 *)(param_1 + 0x585);
    zz_006bda8_(param_1);
    if ((*(uint *)(param_1 + 0x5e0) & 3) == 3) {
      if (param_2[1] == '\x01') {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
          zz_006a750_(param_1,0);
          zz_004beb8_((double)FLOAT_8043764c,param_1,2,0,0,0xffffffff,0xffffffff);
        }
        else {
          zz_006a750_(param_1,6);
        }
      }
    }
    fVar3 = FLOAT_8043762c;
    *(char *)(param_1 + 0x580) = param_2[2];
    *(char *)(param_1 + 0x581) = param_2[3];
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | (uint)(byte)param_2[1];
    *(float *)(param_1 + 0x694) = fVar3;
    if (param_2[1] == '\x03') {
      *(undefined1 *)(param_1 + 0x709) = 0;
    }
    *(undefined *)(param_1 + 0x57a) = (&DAT_802d3994)[*(char *)(param_1 + 0x584) * 2];
    *(undefined *)(param_1 + 0x57b) = (&DAT_802d3995)[*(char *)(param_1 + 0x584) * 2];
    *(undefined1 *)(param_1 + 0x1d9a) = 0;
    fVar3 = FLOAT_8043762c;
    if (2 < *(char *)(param_1 + 0x584)) {
      *(float *)(param_1 + *(char *)(param_1 + 0x584) * 4 + 0x630) = FLOAT_8043762c;
      *(float *)(param_1 + *(char *)(param_1 + 0x584) * 4 + 0x63c) = fVar3;
    }
    *(byte *)(DAT_803c4e84 + 0x5e6) = *(byte *)(DAT_803c4e84 + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
    *(byte *)(DAT_803c4e88 + 0x5e6) = *(byte *)(DAT_803c4e88 + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
    *(byte *)(DAT_803c4e8c + 0x5e6) = *(byte *)(DAT_803c4e8c + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
    *(byte *)(DAT_803c4e90 + 0x5e6) = *(byte *)(DAT_803c4e90 + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
    *(byte *)(DAT_803c4e94 + 0x5e6) = *(byte *)(DAT_803c4e94 + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
    *(byte *)(DAT_803c4e98 + 0x5e6) = *(byte *)(DAT_803c4e98 + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
    iVar5 = *(int *)(param_1 + 0xcc);
    if ((iVar5 != 0) && (*(char *)(iVar5 + 0x83) == '\0')) {
      *(byte *)(iVar5 + 0x5e6) = *(byte *)(iVar5 + 0x5e6) | *(byte *)(param_1 + 0x3e5);
    }
    zz_006a6fc_(param_1,(int)*param_2);
    if (param_2[1] == '\x03') {
      zz_006a750_(param_1,(int)*param_2);
    }
    cVar1 = *(char *)(param_1 + 0x584);
    bVar2 = false;
    if ((cVar1 == '\0') || (cVar1 == '\x02')) {
      iVar5 = param_1 + cVar1 * 8;
      if ((*(short *)(iVar5 + 0x78e) != 0) &&
         ((*(short *)(iVar5 + 0x790) != 3 &&
          (iVar5 = zz_006dbe0_(param_1,(int)cVar1,1,0), iVar5 == 0)))) {
        zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),(int)*(char *)(param_1 + 0x584));
        bVar2 = true;
      }
    }
    if (!bVar2) {
      zz_00ea2c8_(param_1,2);
    }
    uVar4 = 1;
  }
  return uVar4;
}



// ==== 8006a3d0  zz_006a3d0_ ====

void zz_006a3d0_(int param_1,char param_2,undefined1 param_3,undefined1 param_4)

{
  *(char *)(param_1 + 0x585) = param_2;
  *(undefined1 *)(param_1 + 0x586) = param_3;
  if (*(char *)(*(int *)(param_1 + 0x4b0) + (int)param_2 + 0xb8) == '\x01') {
    *(undefined1 *)(param_1 + 0x587) = param_4;
    zz_006a104_(param_1,(char *)(*(int *)(*(int *)(param_1 + 0x4ec) + *(char *)(param_1 + 0x585) * 4
                                         ) +
                                *(char *)(param_1 + 0x586) * 0x10 + *(char *)(param_1 + 0x587) * 4))
    ;
  }
  else {
    zz_006a104_(param_1,(char *)(*(int *)(*(int *)(param_1 + 0x4ec) + *(char *)(param_1 + 0x585) * 4
                                         ) + *(char *)(param_1 + 0x586) * 4));
  }
  return;
}



// ==== 8006a474  zz_006a474_ ====

void zz_006a474_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043762c;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xff0003;
  *(float *)(param_1 + 0x1d9c) = fVar1;
  *(undefined1 *)(param_1 + 0x1db2) = 0;
  *(undefined1 *)(param_1 + 0x4a1) = 0;
  *(undefined1 *)(param_1 + 0x71b) = 0;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006a750_(param_1,0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043762c;
  return;
}



// ==== 8006a4f4  zz_006a4f4_ ====

void zz_006a4f4_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043762c;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xff0843;
  *(float *)(param_1 + 0x1d9c) = fVar1;
  *(undefined1 *)(param_1 + 0x71b) = 0;
  zz_006a750_(param_1,0x12);
  return;
}



// ==== 8006a53c  zz_006a53c_ ====

void zz_006a53c_(int param_1,uint param_2)

{
  if (0 < (int)param_2) {
    *(float *)(param_1 + 0x694) =
         (float)((double)CONCAT44(0x43300000,param_2 ^ 0x80000000) - DOUBLE_80437650) +
         *(float *)(param_1 + 0x1dc8);
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a6fc_(param_1,0x1b);
  return;
}



// ==== 8006a5a4  zz_006a5a4_ ====

void zz_006a5a4_(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_8043762c;
  *(undefined1 *)(param_1 + 0x590) = 1;
  *(float *)(param_1 + 0x690) = fVar1;
  *(undefined1 *)(param_1 + 0x71b) = 0;
  uVar2 = *(uint *)(param_1 + 0x5e0);
  if ((uVar2 & 3) == 3) {
    *(uint *)(param_1 + 0x5e0) = uVar2 & 0xff0040;
    if (*(float *)(param_1 + 0x694) <= fVar1) {
      *(float *)(param_1 + 0x694) = FLOAT_80437648;
    }
    zz_005c080_(param_1);
  }
  else {
    *(uint *)(param_1 + 0x5e0) = uVar2 & 0xff0041;
  }
  if (*(char *)(param_1 + 0x1d9b) != '\0') {
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x1db0) + *(short *)(param_1 + 0x72);
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x1dac);
  }
  zz_006a750_(param_1,6);
  return;
}



// ==== 8006a668  zz_006a668_ ====

void zz_006a668_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,uint param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80437650;
  if ((*(uint *)(param_9 + 0x5e0) & 3) != 0) {
    param_3 = (double)*(float *)(param_9 + 0x694);
    param_1 = (double)(float)((double)CONCAT44(0x43300000,param_10 ^ 0x80000000) - DOUBLE_80437650);
    fVar1 = (float)(param_1 + (double)*(float *)(param_9 + 0x1dc8));
    param_2 = dVar2;
    if (param_3 < (double)fVar1) {
      *(float *)(param_9 + 0x694) = fVar1;
    }
  }
  *(float *)(param_9 + 0x1d9c) = FLOAT_8043762c;
  *(undefined1 *)(param_9 + 0x1db2) = 0;
  *(undefined1 *)(param_9 + 0x1db3) = 0;
  zz_0048d54_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_006a6fc_(param_9,(int)*(char *)(param_9 + 0x5e4));
  return;
}



// ==== 8006a6fc  zz_006a6fc_ ====

undefined4 zz_006a6fc_(int param_1,int param_2)

{
  char cVar1;
  
  cVar1 = *(char *)(*(int *)(param_1 + 0x4f0) + param_2 * 2);
  if (cVar1 == -1) {
    return 0;
  }
  *(undefined1 *)(param_1 + 1999) = *(undefined1 *)(param_1 + 0x5e5);
  *(char *)(param_1 + 0x5e5) = (char)param_2;
  *(undefined1 *)(param_1 + 0x5dc) = *(undefined1 *)(param_1 + 0x5da);
  *(char *)(param_1 + 0x5da) = cVar1;
  *(undefined1 *)(param_1 + 0x543) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x540) = 0;
  return 1;
}



// ==== 8006a750  zz_006a750_ ====

undefined4 zz_006a750_(int param_1,int param_2)

{
  char cVar1;
  
  cVar1 = *(char *)(*(int *)(param_1 + 0x4f0) + param_2 * 2 + 1);
  if (cVar1 == -1) {
    return 0;
  }
  *(undefined1 *)(param_1 + 0x7ce) = *(undefined1 *)(param_1 + 0x5e4);
  *(char *)(param_1 + 0x5e4) = (char)param_2;
  *(undefined1 *)(param_1 + 0x5dd) = *(undefined1 *)(param_1 + 0x5db);
  *(char *)(param_1 + 0x5db) = cVar1;
  *(undefined1 *)(param_1 + 0x547) = 0;
  *(undefined1 *)(param_1 + 0x546) = 0;
  *(undefined1 *)(param_1 + 0x545) = 0;
  *(undefined1 *)(param_1 + 0x544) = 0;
  *(undefined1 *)(param_1 + 0x588) = 0;
  *(undefined4 *)(param_1 + 0x754) = 0;
  *(undefined1 *)(param_1 + 0x1db3) = 0;
  return 1;
}



// ==== 8006a7b4  zz_006a7b4_ ====

undefined4 zz_006a7b4_(int param_1,int param_2)

{
  char cVar1;
  
  cVar1 = *(char *)(*(int *)(param_1 + 0x4f0) + param_2 * 2);
  if (cVar1 == -1) {
    return 0;
  }
  *(undefined1 *)(param_1 + 1999) = *(undefined1 *)(param_1 + 0x5e5);
  *(char *)(param_1 + 0x5e5) = (char)param_2;
  *(undefined1 *)(param_1 + 0x5dc) = *(undefined1 *)(param_1 + 0x5da);
  *(char *)(param_1 + 0x5da) = cVar1;
  return 1;
}



// ==== 8006a7f4  zz_006a7f4_ ====

undefined4 zz_006a7f4_(int param_1,int param_2)

{
  char cVar1;
  
  cVar1 = *(char *)(*(int *)(param_1 + 0x4f0) + param_2 * 2 + 1);
  if (cVar1 == -1) {
    return 0;
  }
  *(undefined1 *)(param_1 + 0x7ce) = *(undefined1 *)(param_1 + 0x5e4);
  *(char *)(param_1 + 0x5e4) = (char)param_2;
  *(undefined1 *)(param_1 + 0x5dd) = *(undefined1 *)(param_1 + 0x5db);
  *(char *)(param_1 + 0x5db) = cVar1;
  return 1;
}



// ==== 8006a838  zz_006a838_ ====

void zz_006a838_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x19) = 1;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x443;
  *(undefined1 *)(param_1 + 0x500) = 1;
  return;
}



// ==== 8006a868  zz_006a868_ ====

void zz_006a868_(int param_1,undefined2 param_2,undefined1 param_3)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x19) = 2;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x443;
  *(undefined1 *)(param_1 + 0x490) = 1;
  *(undefined2 *)(param_1 + 0x48c) = param_2;
  *(undefined1 *)(param_1 + 0x48e) = param_3;
  *(undefined2 *)(param_1 + 0x494) = *(undefined2 *)(param_1 + 0x1c6);
  *(undefined2 *)(param_1 + 0x496) = *(undefined2 *)(param_1 + 0x1c4);
  *(undefined2 *)(param_1 + 0x498) = *(undefined2 *)(param_1 + 0x4aa);
  *(undefined1 *)(param_1 + 0x48f) = *(undefined1 *)(param_1 + 0x3ee);
  return;
}



// ==== 8006a8c0  zz_006a8c0_ ====

void zz_006a8c0_(char *param_1,undefined2 param_2)

{
  undefined2 local_18 [10];
  
  *(undefined2 *)(param_1 + 1000) = param_2;
  *(undefined2 *)(param_1 + 0x94) = *(undefined2 *)(param_1 + 1000);
  param_1[0x3f0] = param_1[0x3f0] + '\x01';
  *(char **)(param_1 + 0x8c) = param_1;
  *(char **)(param_1 + 0x90) = param_1;
  *(undefined2 *)(param_1 + 0x94) = *(undefined2 *)(param_1 + 1000);
  param_1[0x96] = param_1[0x3e4];
  param_1[0x97] = param_1[999];
  zz_0056ce0_((int)param_1);
  param_1[0x660] = **(char **)(param_1 + 0x4b0);
  param_1[0x661] = *(char *)(*(int *)(param_1 + 0x4b0) + 1);
  param_1[0x591] = *(char *)(*(int *)(param_1 + 0x4b0) + 4);
  if (PTR_DAT_80433930[0x32] == '\0') {
    local_18[0] = *(undefined2 *)(param_1 + 1000);
    zz_01cb750_(-0x7fc401e0,local_18,(int)param_1[0x3ec]);
  }
  zz_001c80c_(param_1);
  return;
}



// ==== 8006a980  FUN_8006a980 ====

void FUN_8006a980(int param_1)

{
  int iVar1;
  undefined2 local_38 [26];
  
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x19) = 2;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x443;
  *(undefined1 *)(param_1 + 0x490) = 4;
  *(undefined2 *)(param_1 + 0x48c) = *(undefined2 *)(param_1 + 0x3ea);
  *(undefined1 *)(param_1 + 0x48e) = *(undefined1 *)(param_1 + 0x3ed);
  *(undefined1 *)(param_1 + 0x48f) = *(undefined1 *)(param_1 + 0x3ef);
  if (*(char *)(param_1 + 0x4a0) == '\0') {
    *(undefined2 *)(param_1 + 0x494) = *(undefined2 *)(param_1 + 0x1c6);
  }
  else {
    local_38[0] = *(undefined2 *)(param_1 + 0x48c);
    iVar1 = zz_0066198_((char *)local_38,(int)*(char *)(param_1 + 0x48e),
                        (int)*(char *)(param_1 + 0x48f));
    *(short *)(param_1 + 0x494) =
         (short)(int)((float)((double)CONCAT44(0x43300000,(int)(short)iVar1 ^ 0x80000000) -
                             DOUBLE_80437650) *
                     ((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1c6) ^ 0x80000000) -
                             DOUBLE_80437650) /
                     (float)((double)CONCAT44(0x43300000,
                                              (int)*(short *)(param_1 + 0x1c4) ^ 0x80000000) -
                            DOUBLE_80437650)));
    if (*(short *)(param_1 + 0x494) < 1) {
      *(undefined2 *)(param_1 + 0x494) = 1;
    }
  }
  *(undefined2 *)(param_1 + 0x496) = *(undefined2 *)(param_1 + 0x1c4);
  *(undefined1 *)(param_1 + 0x4a1) = 0;
  return;
}



// ==== 8006aab0  FUN_8006aab0 ====

void FUN_8006aab0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x19) = 2;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x443;
  *(undefined1 *)(param_1 + 0x48a) = 4;
  *(undefined1 *)(param_1 + 0x490) = 4;
  *(undefined2 *)(param_1 + 0x48c) = *(undefined2 *)(param_1 + 0x49e);
  *(undefined1 *)(param_1 + 0x48e) = *(undefined1 *)(param_1 + 0x3ed);
  *(undefined2 *)(param_1 + 0x494) = *(undefined2 *)(param_1 + 0x1c6);
  *(undefined2 *)(param_1 + 0x496) = *(undefined2 *)(param_1 + 0x1c4);
  return;
}



// ==== 8006ab04  zz_006ab04_ ====

void zz_006ab04_(int param_1,undefined4 *param_2,undefined1 param_3)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x7c9) == '\0') {
    *(undefined1 *)(param_1 + 0x7c9) = param_3;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x1000;
    uVar1 = param_2[1];
    *(undefined4 *)(param_1 + 0x7bc) = *param_2;
    *(undefined4 *)(param_1 + 0x7c0) = uVar1;
    *(undefined4 *)(param_1 + 0x7c4) = param_2[2];
    *(undefined1 *)(param_1 + 0x71b) = 0;
    *(undefined2 *)(param_1 + 0x272) = 0xffff;
    *(undefined1 *)(param_1 + 0x7ca) = 0;
    *(undefined1 *)(param_1 + 0x7cb) = 0;
    zz_006a7b4_(param_1,0x23);
    zz_006a7f4_(param_1,0x23);
    zz_00f036c_(param_1,0xf2);
  }
  return;
}



// ==== 8006ab9c  zz_006ab9c_ ====

uint zz_006ab9c_(int param_1)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(*(uint *)(param_1 + 0x5e0) & 0x91001003);
  return uVar1 >> 5;
}



// ==== 8006abb8  FUN_8006abb8 ====

uint FUN_8006abb8(int param_1)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(*(uint *)(param_1 + 0x5e0) & 0x91001000);
  return uVar1 >> 5;
}



// ==== 8006abd4  zz_006abd4_ ====

void zz_006abd4_(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x18) < '\x02') {
    if (*(char *)(param_2 + 0x4a0) == '\0') {
      if (*(char *)(param_1 + 0x48a) == '\0') {
        if (*(char *)(param_2 + 0x48a) == '\0') {
          zz_006a868_(param_1,*(undefined2 *)(param_2 + 1000),*(undefined1 *)(param_2 + 0x3ec));
          *(undefined2 *)(param_1 + 0x49a) = 900;
          *(undefined1 *)(param_1 + 0x489) = 1;
        }
        else {
          *(undefined2 *)(param_1 + 0x49e) = *(undefined2 *)(param_1 + 1000);
          if (*(char *)(param_2 + 0x48b) == '\x01') {
            zz_006a868_(param_1,0xf06,*(undefined1 *)(param_1 + 0x3ec));
          }
          else {
            zz_006a868_(param_1,0xf05,*(undefined1 *)(param_1 + 0x3ec));
          }
          *(undefined2 *)(param_1 + 0x49c) = 900;
          *(undefined1 *)(param_1 + 0x48a) = 1;
          *(undefined1 *)(param_1 + 0x48b) = *(undefined1 *)(param_2 + 0x48b);
          *(undefined2 *)(param_1 + 0x49e) = *(undefined2 *)(param_1 + 1000);
          *(undefined1 *)(param_1 + 0x6fb) = 0;
        }
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x80000000;
        *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x443;
        *(undefined4 *)(param_1 + 0x8c4) = 0;
        zz_0176ec0_(param_1,*(undefined1 *)(param_1 + 0x88),1);
      }
    }
  }
  return;
}



// ==== 8006ace8  zz_006ace8_ ====

void zz_006ace8_(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x18) < '\x02') {
    if (*(char *)(param_1 + 0x4a1) == '\0') {
      if ((*(char *)(param_1 + 0x6fc) == '\0') && (*(char *)(param_1 + 0x4a0) == '\0')) {
        if (*(char *)(param_1 + 0x48a) != '\x01') {
          if (*(char *)(param_1 + 0x48a) == '\0') {
            *(undefined2 *)(param_1 + 0x49e) = *(undefined2 *)(param_1 + 1000);
            if (param_2 == 1) {
              zz_006a868_(param_1,0xf06,*(undefined1 *)(param_1 + 0x3ec));
            }
            else {
              zz_006a868_(param_1,0xf05,*(undefined1 *)(param_1 + 0x3ec));
            }
            *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x80000000;
            *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x443;
            *(undefined4 *)(param_1 + 0x8c4) = 0;
            *(undefined1 *)(param_1 + 0x48a) = 1;
            *(undefined2 *)(param_1 + 0x49c) = 900;
            *(undefined1 *)(param_1 + 0x6fb) = 0;
          }
          else if (*(char *)(param_1 + 0x48b) == param_2) {
            *(undefined1 *)(param_1 + 0x48a) = 2;
            if (*(short *)(param_1 + 0x49c) < 0x78) {
              *(undefined2 *)(param_1 + 0x49c) = 0x78;
            }
          }
          else {
            if (param_2 == 1) {
              zz_006a868_(param_1,0xf06,*(undefined1 *)(param_1 + 0x3ec));
            }
            else {
              zz_006a868_(param_1,0xf05,*(undefined1 *)(param_1 + 0x3ec));
            }
            *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x80000000;
            *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x443;
            *(undefined4 *)(param_1 + 0x8c4) = 0;
            *(undefined1 *)(param_1 + 0x48a) = 1;
            *(undefined2 *)(param_1 + 0x49c) = 900;
            *(undefined1 *)(param_1 + 0x6fb) = 0;
          }
          *(char *)(param_1 + 0x48b) = (char)param_2;
          zz_00ea2c8_(param_1,4);
        }
      }
    }
  }
  return;
}



// ==== 8006ae60  zz_006ae60_ ====

void zz_006ae60_(void)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  float *pfVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  
  pcVar9 = DAT_803c4e84;
  if (*DAT_803c4e84 != '\0') {
    DAT_803c4e84[0x58a] = '\0';
    pcVar9[0x58b] = '\0';
    pcVar9[0x58c] = '\0';
    pcVar9[0x58d] = '\0';
    pcVar9[0x7d2] = '\0';
    pcVar9[0x7d3] = '\0';
  }
  if (pcVar9[0x1e00] != '\0') {
    pcVar9[0x238a] = '\0';
    pcVar9[0x238b] = '\0';
    pcVar9[0x238c] = '\0';
    pcVar9[0x238d] = '\0';
    pcVar9[0x25d2] = '\0';
    pcVar9[0x25d3] = '\0';
  }
  if (pcVar9[0x3c00] != '\0') {
    pcVar9[0x418a] = '\0';
    pcVar9[0x418b] = '\0';
    pcVar9[0x418c] = '\0';
    pcVar9[0x418d] = '\0';
    pcVar9[0x43d2] = '\0';
    pcVar9[0x43d3] = '\0';
  }
  if (pcVar9[0x5a00] != '\0') {
    pcVar9[0x5f8a] = '\0';
    pcVar9[0x5f8b] = '\0';
    pcVar9[0x5f8c] = '\0';
    pcVar9[0x5f8d] = '\0';
    pcVar9[0x61d2] = '\0';
    pcVar9[0x61d3] = '\0';
  }
  if (pcVar9[0x7800] != '\0') {
    pcVar9[0x7d8a] = '\0';
    pcVar9[0x7d8b] = '\0';
    pcVar9[0x7d8c] = '\0';
    pcVar9[0x7d8d] = '\0';
    pcVar9[0x7fd2] = '\0';
    pcVar9[0x7fd3] = '\0';
  }
  if (pcVar9[0x9600] != '\0') {
    pcVar9[0x9b8a] = '\0';
    pcVar9[0x9b8b] = '\0';
    pcVar9[0x9b8c] = '\0';
    pcVar9[0x9b8d] = '\0';
    pcVar9[0x9dd2] = '\0';
    pcVar9[0x9dd3] = '\0';
  }
  iVar10 = 0;
  pcVar9 = DAT_803c4e84;
  do {
    if ((*pcVar9 != '\0') && ('\0' < pcVar9[0x18])) {
      zz_006b450_(pcVar9);
      zz_006b7f4_(pcVar9);
      fVar2 = FLOAT_80437678;
      iVar8 = *(int *)(pcVar9 + 0x508);
      if (iVar8 == 0) {
        *(float *)(pcVar9 + 0x75c) = FLOAT_80437678;
        *(float *)(pcVar9 + 0x758) = fVar2;
        dVar12 = zz_0045204_(*(short *)(pcVar9 + 0x72));
        *(float *)(pcVar9 + 0x50c) = (float)((double)*(float *)(pcVar9 + 0x75c) * dVar12);
        *(undefined4 *)(pcVar9 + 0x510) =
             *(undefined4 *)(pcVar9 + *(char *)(*(int *)(pcVar9 + 0x4b0) + 0x10) * 0x30 + 0x8f0);
        dVar12 = zz_0045238_(*(short *)(pcVar9 + 0x72));
        *(float *)(pcVar9 + 0x514) = (float)((double)*(float *)(pcVar9 + 0x75c) * dVar12);
      }
      else {
        iVar5 = *(int *)(pcVar9 + 0x504);
        pfVar7 = (float *)(iVar5 + 100);
        dVar12 = gnt4_PSVECSquareDistance_bl((float *)(pcVar9 + 0x20),pfVar7);
        if ((double)FLOAT_80437658 < dVar12) {
          dVar13 = 1.0 / SQRT(dVar12);
          dVar13 = DOUBLE_80437660 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668);
          dVar13 = DOUBLE_80437660 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668);
          dVar12 = (double)(float)(dVar12 * DOUBLE_80437660 * dVar13 *
                                            -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668));
        }
        *(float *)(pcVar9 + 0x758) = (float)dVar12;
        fVar2 = *(float *)(pcVar9 + 0x20) - *pfVar7;
        fVar3 = *(float *)(pcVar9 + 0x28) - *(float *)(iVar5 + 0x6c);
        dVar12 = (double)(fVar2 * fVar2 + fVar3 * fVar3);
        if ((double)FLOAT_80437658 < dVar12) {
          dVar13 = 1.0 / SQRT(dVar12);
          dVar13 = DOUBLE_80437660 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668);
          dVar13 = DOUBLE_80437660 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668);
          dVar12 = (double)(float)(dVar12 * DOUBLE_80437660 * dVar13 *
                                            -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668));
        }
        *(float *)(pcVar9 + 0x75c) = (float)dVar12;
        zz_006d228_((int)pcVar9,*(int *)(pcVar9 + 0x508),0);
        pcVar9[0x7d2] = pcVar9[0x7d2] | 1;
        bVar1 = pcVar9[0x88] == *(char *)(iVar8 + 0x88);
        if (!bVar1) {
          pcVar9[0x7d2] = pcVar9[0x7d2] | 2;
        }
        if (*(float *)(pcVar9 + 0x758) <= *(float *)(pcVar9 + (uint)bVar1 * 4 + 0x814)) {
          pcVar9[0x7d2] = pcVar9[0x7d2] | 4;
        }
        if ((*(uint *)(pcVar9 + 0x5e0) & 0x80) == 0) {
          if ((*(uint *)(pcVar9 + 0x5e0) & 0x40) == 0) {
            iVar8 = 0;
          }
          else {
            iVar8 = 1;
          }
        }
        else {
          iVar8 = 2;
        }
        fVar2 = *(float *)(pcVar9 + 0xb4);
        fVar3 = *(float *)(pcVar9 + iVar8 * 4 + 0x838);
        if (FLOAT_80437670 <= fVar2) {
          if (FLOAT_80437670 < fVar2) {
            fVar3 = fVar3 * (FLOAT_80437674 * (fVar2 - FLOAT_80437670) + FLOAT_80437670);
          }
        }
        else {
          fVar3 = fVar3 * fVar2;
        }
        if (*(float *)(pcVar9 + 0x758) <= fVar3) {
          pcVar9[0x7d2] = pcVar9[0x7d2] | 8;
        }
      }
      fVar2 = FLOAT_80437678;
      if (*(int *)(pcVar9 + 0xcc) == 0) {
        *(float *)(pcVar9 + 0x764) = FLOAT_80437678;
        *(float *)(pcVar9 + 0x760) = fVar2;
        dVar12 = zz_0045204_(*(short *)(pcVar9 + 0x72));
        *(float *)(pcVar9 + 0x518) = (float)((double)*(float *)(pcVar9 + 0x764) * dVar12);
        *(undefined4 *)(pcVar9 + 0x51c) =
             *(undefined4 *)(pcVar9 + *(char *)(*(int *)(pcVar9 + 0x4b0) + 0x10) * 0x30 + 0x8f0);
        dVar12 = zz_0045238_(*(short *)(pcVar9 + 0x72));
        *(float *)(pcVar9 + 0x520) = (float)((double)*(float *)(pcVar9 + 0x764) * dVar12);
      }
      else {
        iVar8 = *(int *)(pcVar9 + 200);
        uVar4 = *(undefined4 *)(iVar8 + 0x68);
        *(undefined4 *)(pcVar9 + 0x518) = *(undefined4 *)(iVar8 + 100);
        *(undefined4 *)(pcVar9 + 0x51c) = uVar4;
        *(undefined4 *)(pcVar9 + 0x520) = *(undefined4 *)(iVar8 + 0x6c);
        dVar12 = gnt4_PSVECSquareDistance_bl((float *)(pcVar9 + 0x20),(float *)(iVar8 + 100));
        if ((double)FLOAT_80437658 < dVar12) {
          dVar13 = 1.0 / SQRT(dVar12);
          dVar13 = DOUBLE_80437660 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668);
          dVar13 = DOUBLE_80437660 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668);
          dVar12 = (double)(float)(dVar12 * DOUBLE_80437660 * dVar13 *
                                            -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668));
        }
        *(float *)(pcVar9 + 0x760) = (float)dVar12;
        fVar2 = *(float *)(pcVar9 + 0x20) - *(float *)(iVar8 + 100);
        fVar3 = *(float *)(pcVar9 + 0x28) - *(float *)(iVar8 + 0x6c);
        dVar12 = (double)(fVar2 * fVar2 + fVar3 * fVar3);
        if ((double)FLOAT_80437658 < dVar12) {
          dVar13 = 1.0 / SQRT(dVar12);
          dVar13 = DOUBLE_80437660 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668);
          dVar13 = DOUBLE_80437660 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668);
          dVar12 = (double)(float)(dVar12 * DOUBLE_80437660 * dVar13 *
                                            -(dVar12 * dVar13 * dVar13 - DOUBLE_80437668));
        }
        *(float *)(pcVar9 + 0x764) = (float)dVar12;
      }
    }
    iVar10 = iVar10 + 1;
    pcVar9 = pcVar9 + 0x1e00;
  } while (iVar10 < 6);
  iVar10 = 0;
  pcVar9 = DAT_803c4e84;
  do {
    iVar8 = *(int *)(pcVar9 + 0x508);
    if (((((*pcVar9 != '\0') && (iVar8 != 0)) && (*(char *)(iVar8 + 0x83) == '\0')) &&
        (((pcVar9[0x7d3] & 1U) == 0 && (*(char *)(iVar8 + 0x88) != pcVar9[0x88])))) &&
       (*(float *)(pcVar9 + 0x75c) <= *(float *)(pcVar9 + 0x814))) {
      iVar5 = 0;
      iVar11 = 6;
      pcVar6 = DAT_803c4e84;
      do {
        if (((iVar5 != iVar10) && (((int)*(char *)(iVar8 + 0x58a) & 1 << iVar5) != 0)) &&
           (pcVar6[0x88] == pcVar9[0x88])) {
          pcVar9[0x7d3] = pcVar9[0x7d3] | 1;
          pcVar6[0x7d3] = pcVar6[0x7d3] | 1;
          *(byte *)(iVar8 + 0x7d3) = *(byte *)(iVar8 + 0x7d3) | 2;
          break;
        }
        iVar5 = iVar5 + 1;
        pcVar6 = pcVar6 + 0x1e00;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
    }
    iVar10 = iVar10 + 1;
    pcVar9 = pcVar9 + 0x1e00;
    if (5 < iVar10) {
      return;
    }
  } while( true );
}



// ==== 8006b450  zz_006b450_ ====

/* WARNING: Removing unreachable block (ram,0x8006b7d8) */
/* WARNING: Removing unreachable block (ram,0x8006b460) */

void zz_006b450_(char *param_1)

{
  char cVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  char *pcVar8;
  int iVar9;
  char *unaff_r30;
  int unaff_r31;
  double dVar10;
  double dVar11;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  uVar3 = zz_0010514_((int)param_1[0x3e4]);
  if (((uVar3 == 0) && (param_1[0x73f] == '\0')) && (cVar1 = param_1[0x73c], '\x01' < cVar1)) {
    if (cVar1 == '\x04') {
      pcVar8 = *(char **)(param_1 + 0x6e0);
      unaff_r30 = param_1 + 0x73d;
      unaff_r31 = 1;
      if (((pcVar8 != (char *)0x0) && (*pcVar8 != '\0')) &&
         ((pcVar8[0x18] == '\x01' && (pcVar8[0x83] == '\0')))) {
        *(char **)(param_1 + 0x508) = pcVar8;
        param_1[0x502] = '\x02';
        param_1[0x73c] = '\0';
        return;
      }
    }
    else if (cVar1 < '\x04') {
      if (cVar1 == '\x02') {
        unaff_r30 = param_1 + 0x73d;
        unaff_r31 = 1;
      }
      else if ('\x01' < cVar1) {
        unaff_r30 = param_1 + 0x73d;
        unaff_r31 = 2;
      }
    }
    else if (cVar1 < '\x06') {
      unaff_r30 = param_1 + 0x73e;
      unaff_r31 = 0;
      *(undefined4 *)(param_1 + 0x6e0) = *(undefined4 *)(param_1 + 0x508);
      *(undefined4 *)(param_1 + 0x6e4) = *(undefined4 *)(param_1 + 0x504);
    }
    cVar1 = *unaff_r30;
    param_1[0x73c] = '\0';
    piVar4 = &DAT_803c1d7c;
    iVar6 = (int)cVar1;
    DAT_804361a0 = 0;
    iVar5 = DAT_803b2208;
    for (uVar3 = (uint)DAT_80436242; DAT_803b2208 = iVar5, uVar3 != 0; uVar3 = uVar3 - 1) {
      iVar5 = *piVar4;
      if (((iVar5 != 0) && ((*(ushort *)(*(int *)(iVar5 + 0x28) + 2) & 0x200) != 0)) &&
         ((pcVar8 = *(char **)(iVar5 + 0x20), pcVar8 != (char *)0x0 &&
          ((*pcVar8 != '\0' && (param_1 != pcVar8)))))) {
        if (unaff_r31 == 0) {
          if ((param_1[0x88] == pcVar8[0x88]) &&
             ((param_1[0x4a0] == '\0' || (*(char **)(param_1 + 0x4a4) != pcVar8))))
          goto LAB_8006b600;
        }
        else if (param_1[0x88] != pcVar8[0x88]) {
LAB_8006b600:
          if ((pcVar8[0x88] != '\x04') && (pcVar8[0x18] < '\x02')) {
            if (*(int *)(param_1 + 0x504) == iVar5) {
              iVar6 = DAT_804361a0;
            }
            piVar2 = &DAT_803b2208 + DAT_804361a0;
            DAT_804361a0 = DAT_804361a0 + 1;
            *piVar2 = iVar5;
          }
        }
      }
      piVar4 = piVar4 + 1;
      iVar5 = DAT_803b2208;
    }
    if (DAT_804361a0 != 0) {
      if (*(int *)(param_1 + 0x504) == 0) {
        cVar1 = *(char *)(*(int *)(param_1 + 0x4b0) + 0x10);
        local_38 = *(float *)(param_1 + cVar1 * 0x30 + 0x8e0);
        local_34 = *(undefined4 *)(param_1 + cVar1 * 0x30 + 0x8f0);
        local_30 = *(undefined4 *)(param_1 + cVar1 * 0x30 + 0x900);
        dVar10 = gnt4_PSVECSquareDistance_bl(&local_38,(float *)(iVar5 + 100));
        piVar4 = &DAT_803b220c;
        for (iVar6 = 1; iVar6 < DAT_804361a0; iVar6 = iVar6 + 1) {
          iVar9 = *piVar4;
          dVar11 = gnt4_PSVECSquareDistance_bl(&local_38,(float *)(iVar9 + 100));
          if (dVar11 <= dVar10) {
            iVar5 = iVar9;
            dVar10 = dVar11;
          }
          piVar4 = piVar4 + 1;
        }
      }
      else {
        if (unaff_r31 == 2) {
          iVar6 = iVar6 + -1;
        }
        else if ((unaff_r31 < 2) && (-1 < unaff_r31)) {
          iVar6 = iVar6 + 1;
        }
        if (iVar6 < 0) {
          iVar6 = DAT_804361a0 + -1;
        }
        else if (DAT_804361a0 + -1 < iVar6) {
          iVar6 = 0;
        }
        iVar5 = (&DAT_803b2208)[iVar6];
        *unaff_r30 = (char)iVar6;
        if (*(int *)(param_1 + 0x504) == iVar5) {
          return;
        }
      }
      param_1[0x502] = '\x01';
      *(int *)(param_1 + 0x504) = iVar5;
      *(undefined4 *)(param_1 + 0x508) = *(undefined4 *)(iVar5 + 0x20);
      uVar7 = *(undefined4 *)(iVar5 + 0x68);
      *(undefined4 *)(param_1 + 0x50c) = *(undefined4 *)(iVar5 + 100);
      *(undefined4 *)(param_1 + 0x510) = uVar7;
      *(undefined4 *)(param_1 + 0x514) = *(undefined4 *)(iVar5 + 0x6c);
      param_1[0x503] = '\x01';
      param_1[0x73c] = '\x01';
      param_1[0x3f1] = '\x01';
      iVar6 = param_1[0x3e4] * 0x3e4;
      (&DAT_803c7696)[iVar6] = 3;
      (&DAT_803c73cb)[iVar6] = 0;
      (&DAT_803c73ca)[iVar6] = 0;
      (&DAT_803c73c9)[iVar6] = 0;
    }
  }
  return;
}



// ==== 8006b7f4  zz_006b7f4_ ====

void zz_006b7f4_(char *param_1)

{
  if (*param_1 == '\0') {
    param_1[0x502] = '\0';
    param_1[0x508] = '\0';
    param_1[0x509] = '\0';
    param_1[0x50a] = '\0';
    param_1[0x50b] = '\0';
    param_1[0x504] = '\0';
    param_1[0x505] = '\0';
    param_1[0x506] = '\0';
    param_1[0x507] = '\0';
  }
  else {
    (*(code *)(&PTR_FUN_802d39a0)[param_1[0x502]])();
  }
  return;
}



// ==== 8006b850  FUN_8006b850 ====

/* WARNING: Removing unreachable block (ram,0x8006ba44) */
/* WARNING: Removing unreachable block (ram,0x8006b860) */

void FUN_8006b850(char *param_1)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  uint uVar4;
  char *pcVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  if (param_1[0x73f] == '\0') {
    piVar6 = &DAT_803c1d7c;
    DAT_804361a0 = 0;
    iVar7 = DAT_803b2208;
    for (uVar4 = (uint)DAT_80436242; DAT_803b2208 = iVar7, uVar4 != 0; uVar4 = uVar4 - 1) {
      iVar7 = *piVar6;
      if (((((iVar7 != 0) && (pcVar5 = *(char **)(iVar7 + 0x20), pcVar5 != (char *)0x0)) &&
           (*pcVar5 != '\0')) && ((param_1 != pcVar5 && (param_1[0x88] != pcVar5[0x88])))) &&
         ((pcVar5[0x88] != '\x04' && (pcVar5[0x18] < '\x02')))) {
        piVar2 = &DAT_803b2208 + DAT_804361a0;
        DAT_804361a0 = DAT_804361a0 + 1;
        *piVar2 = iVar7;
      }
      piVar6 = piVar6 + 1;
      iVar7 = DAT_803b2208;
    }
    if (DAT_804361a0 != 0) {
      cVar1 = *(char *)(*(int *)(param_1 + 0x4b0) + 0x10);
      local_38 = *(float *)(param_1 + cVar1 * 0x30 + 0x8e0);
      local_34 = *(undefined4 *)(param_1 + cVar1 * 0x30 + 0x8f0);
      local_30 = *(undefined4 *)(param_1 + cVar1 * 0x30 + 0x900);
      dVar10 = gnt4_PSVECSquareDistance_bl(&local_38,(float *)(iVar7 + 100));
      piVar6 = &DAT_803b220c;
      for (iVar8 = 1; iVar8 < DAT_804361a0; iVar8 = iVar8 + 1) {
        iVar9 = *piVar6;
        dVar11 = gnt4_PSVECSquareDistance_bl(&local_38,(float *)(iVar9 + 100));
        if (dVar11 <= dVar10) {
          iVar7 = iVar9;
          dVar10 = dVar11;
        }
        piVar6 = piVar6 + 1;
      }
      iVar8 = iVar7;
      if (((*(int *)(iVar7 + 0x20) != 0) && ((*(ushort *)(*(int *)(iVar7 + 0x28) + 2) & 0x200) == 0)
          ) && (piVar6 = &DAT_803b2208, iVar9 = DAT_804361a0, 0 < DAT_804361a0)) {
        do {
          iVar8 = *piVar6;
          if ((*(int *)(iVar7 + 0x20) == *(int *)(iVar8 + 0x20)) &&
             ((*(ushort *)(*(int *)(iVar8 + 0x28) + 2) & 0x200) != 0)) break;
          piVar6 = piVar6 + 1;
          iVar9 = iVar9 + -1;
          iVar8 = iVar7;
        } while (iVar9 != 0);
      }
      param_1[0x502] = '\x01';
      *(int *)(param_1 + 0x504) = iVar8;
      *(undefined4 *)(param_1 + 0x508) = *(undefined4 *)(iVar8 + 0x20);
      uVar3 = *(undefined4 *)(iVar8 + 0x68);
      *(undefined4 *)(param_1 + 0x50c) = *(undefined4 *)(iVar8 + 100);
      *(undefined4 *)(param_1 + 0x510) = uVar3;
      *(undefined4 *)(param_1 + 0x514) = *(undefined4 *)(iVar8 + 0x6c);
    }
  }
  return;
}



// ==== 8006ba60  FUN_8006ba60 ====

void FUN_8006ba60(int param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  char *pcVar6;
  
  pcVar2 = *(char **)(param_1 + 0x508);
  pcVar6 = *(char **)(param_1 + 0x504);
  if (((*pcVar2 != '\0') && (pcVar2[0x18] < '\x03')) && (*pcVar6 != '\0')) {
    if ((*(int *)(pcVar6 + 0x20) != 0) && ((*(ushort *)(*(int *)(pcVar6 + 0x28) + 2) & 0x200) == 0))
    {
      DAT_804361a0 = 0;
      puVar5 = &DAT_803c1d7c;
      for (iVar4 = 0; iVar4 < (int)(uint)DAT_80436242; iVar4 = iVar4 + 1) {
        pcVar2 = (char *)*puVar5;
        if (((pcVar2 != (char *)0x0) && (pcVar6 != pcVar2)) &&
           ((*(int *)(pcVar6 + 0x20) == *(int *)(pcVar2 + 0x20) &&
            (((*(ushort *)(*(int *)(pcVar2 + 0x28) + 2) & 0x200) != 0 &&
             (iVar3 = zz_006bcf4_(param_1,(int)pcVar2,1), iVar3 != 0)))))) {
          *(char **)(param_1 + 0x504) = pcVar2;
          pcVar6 = pcVar2;
        }
        puVar5 = puVar5 + 1;
      }
    }
    uVar1 = *(undefined4 *)(pcVar6 + 0x68);
    *(undefined4 *)(param_1 + 0x50c) = *(undefined4 *)(pcVar6 + 100);
    *(undefined4 *)(param_1 + 0x510) = uVar1;
    *(undefined4 *)(param_1 + 0x514) = *(undefined4 *)(pcVar6 + 0x6c);
    return;
  }
  if ((pcVar2[0x83] == '\0') && (pcVar2[0x490] != '\0')) {
    *(undefined1 *)(param_1 + 0x502) = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x502) = 0;
    *(undefined4 *)(param_1 + 0x508) = 0;
    *(undefined4 *)(param_1 + 0x504) = 0;
  }
  return;
}



// ==== 8006bc74  zz_006bc74_ ====

undefined4 zz_006bc74_(int param_1,char *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  if ((*param_2 != '\0') && (param_2[0x83] == '\0')) {
    if ((param_2[0x18] == '\x01') && ('\0' < param_2[0x501])) {
      *(undefined1 *)(param_1 + 0x502) = 1;
      *(undefined4 *)(param_1 + 0x504) = *(undefined4 *)(param_2 + 0x530);
      iVar2 = *(int *)(param_2 + 0x530);
      uVar1 = *(undefined4 *)(iVar2 + 0x68);
      *(undefined4 *)(param_1 + 0x50c) = *(undefined4 *)(iVar2 + 100);
      *(undefined4 *)(param_1 + 0x510) = uVar1;
      *(undefined4 *)(param_1 + 0x514) = *(undefined4 *)(iVar2 + 0x6c);
      *(char **)(param_1 + 0x508) = param_2;
      return 1;
    }
  }
  return 0;
}



// ==== 8006bcf4  zz_006bcf4_ ====

undefined4 zz_006bcf4_(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  float local_18;
  float local_14;
  float local_10;
  
  if ((param_3 == 0) && (*(char *)(param_1 + 0x503) == '\x01')) {
    uVar1 = 1;
  }
  else {
    zz_0067d70_((int)*(char *)(param_1 + 0x3e4),(float *)(param_2 + 100),&local_18);
    uVar1 = 0;
    if ((FLOAT_80437658 <= local_18) && (local_18 <= FLOAT_8043767c)) {
      if ((((FLOAT_80437680 <= local_14) && (local_14 <= FLOAT_80437684)) &&
          (FLOAT_80437658 < local_10)) && (local_10 < FLOAT_80437670)) {
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}



// ==== 8006bda8  zz_006bda8_ ====

void zz_006bda8_(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  
  *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_1 + 0x504);
  *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(param_1 + 0x508);
  *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(param_1 + 0x7d2);
  if (*(short *)(param_1 + 0x6b8) != 0) {
    *(undefined4 *)(param_1 + 200) = 0;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined1 *)(param_1 + 0xd0) = 0;
  }
  fVar1 = FLOAT_80437678;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x764) = FLOAT_80437678;
    *(float *)(param_1 + 0x760) = fVar1;
    dVar5 = zz_0045204_(*(short *)(param_1 + 0x72));
    *(float *)(param_1 + 0x518) = (float)((double)*(float *)(param_1 + 0x764) * dVar5);
    *(undefined4 *)(param_1 + 0x51c) =
         *(undefined4 *)(param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30 + 0x8f0);
    dVar5 = zz_0045238_(*(short *)(param_1 + 0x72));
    *(float *)(param_1 + 0x520) = (float)((double)*(float *)(param_1 + 0x764) * dVar5);
  }
  else {
    iVar4 = *(int *)(param_1 + 200);
    uVar3 = *(undefined4 *)(iVar4 + 0x68);
    *(undefined4 *)(param_1 + 0x518) = *(undefined4 *)(iVar4 + 100);
    *(undefined4 *)(param_1 + 0x51c) = uVar3;
    *(undefined4 *)(param_1 + 0x520) = *(undefined4 *)(iVar4 + 0x6c);
    dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(iVar4 + 100));
    if ((double)FLOAT_80437658 < dVar5) {
      dVar6 = 1.0 / SQRT(dVar5);
      dVar6 = DOUBLE_80437660 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80437668);
      dVar6 = DOUBLE_80437660 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80437668);
      dVar5 = (double)(float)(dVar5 * DOUBLE_80437660 * dVar6 *
                                      -(dVar5 * dVar6 * dVar6 - DOUBLE_80437668));
    }
    *(float *)(param_1 + 0x760) = (float)dVar5;
    fVar1 = *(float *)(param_1 + 0x20) - *(float *)(iVar4 + 100);
    fVar2 = *(float *)(param_1 + 0x28) - *(float *)(iVar4 + 0x6c);
    dVar5 = (double)(fVar1 * fVar1 + fVar2 * fVar2);
    if ((double)FLOAT_80437658 < dVar5) {
      dVar6 = 1.0 / SQRT(dVar5);
      dVar6 = DOUBLE_80437660 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80437668);
      dVar6 = DOUBLE_80437660 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80437668);
      dVar5 = (double)(float)(dVar5 * DOUBLE_80437660 * dVar6 *
                                      -(dVar5 * dVar6 * dVar6 - DOUBLE_80437668));
    }
    *(float *)(param_1 + 0x764) = (float)dVar5;
  }
  return;
}



// ==== 8006bf80  zz_006bf80_ ====

void zz_006bf80_(int param_1)

{
  int iVar1;
  
  zz_006bda8_(param_1);
  *(byte *)(DAT_803c4e84 + 0x5e6) = *(byte *)(DAT_803c4e84 + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
  *(byte *)(DAT_803c4e88 + 0x5e6) = *(byte *)(DAT_803c4e88 + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
  *(byte *)(DAT_803c4e8c + 0x5e6) = *(byte *)(DAT_803c4e8c + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
  *(byte *)(DAT_803c4e90 + 0x5e6) = *(byte *)(DAT_803c4e90 + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
  *(byte *)(DAT_803c4e94 + 0x5e6) = *(byte *)(DAT_803c4e94 + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
  *(byte *)(DAT_803c4e98 + 0x5e6) = *(byte *)(DAT_803c4e98 + 0x5e6) & ~*(byte *)(param_1 + 0x3e5);
  iVar1 = *(int *)(param_1 + 0xcc);
  if (iVar1 != 0) {
    if ((*(char *)(iVar1 + 0x83) == '\0') && ((*(uint *)(iVar1 + 0x5e0) & 0x80000000) == 0)) {
      *(byte *)(iVar1 + 0x5e6) = *(byte *)(iVar1 + 0x5e6) | *(byte *)(param_1 + 0x3e5);
    }
  }
  return;
}



// ==== 8006c060  zz_006c060_ ====

int zz_006c060_(char *param_1,float param_2)

{
  int *piVar1;
  uint uVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  float local_28 [4];
  
  piVar4 = &DAT_803c1d7c;
  DAT_804361a0 = 0;
  iVar5 = DAT_803b2208;
  for (uVar2 = (uint)DAT_80436242; DAT_803b2208 = iVar5, uVar2 != 0; uVar2 = uVar2 - 1) {
    iVar5 = *piVar4;
    if ((((iVar5 != 0) && (pcVar3 = *(char **)(iVar5 + 0x20), pcVar3 != (char *)0x0)) &&
        (*pcVar3 != '\0')) &&
       (((param_1 != pcVar3 && (param_1[0x88] != pcVar3[0x88])) &&
        ((pcVar3[0x88] != '\x04' && (pcVar3[0x18] < '\x02')))))) {
      piVar1 = &DAT_803b2208 + DAT_804361a0;
      DAT_804361a0 = DAT_804361a0 + 1;
      *piVar1 = iVar5;
    }
    piVar4 = piVar4 + 1;
    iVar5 = DAT_803b2208;
  }
  if (DAT_804361a0 == 0) {
    iVar5 = 0;
  }
  else {
    local_28[0] = param_2;
    dVar8 = gnt4_PSVECSquareDistance_bl(local_28,(float *)(iVar5 + 100));
    piVar4 = &DAT_803b220c;
    for (iVar7 = 1; iVar7 < DAT_804361a0; iVar7 = iVar7 + 1) {
      iVar6 = *piVar4;
      dVar9 = gnt4_PSVECSquareDistance_bl(local_28,(float *)(iVar6 + 100));
      if (dVar9 <= dVar8) {
        iVar5 = iVar6;
        dVar8 = dVar9;
      }
      piVar4 = piVar4 + 1;
    }
  }
  return iVar5;
}



// ==== 8006c1c8  FUN_8006c1c8 ====

/* WARNING: Removing unreachable block (ram,0x8006c314) */
/* WARNING: Removing unreachable block (ram,0x8006c30c) */
/* WARNING: Removing unreachable block (ram,0x8006c1e0) */
/* WARNING: Removing unreachable block (ram,0x8006c1d8) */

void FUN_8006c1c8(double param_1,int param_2,float *param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  float local_68;
  float local_64;
  float local_60;
  float afStack_5c [13];
  
  gnt4_PSVECNormalize_bl((float *)(param_2 + 0x38),(float *)(param_2 + 0x38));
  gnt4_PSVECSubtract_bl(param_3,(float *)(param_2 + 0x20),&local_68);
  if (FLOAT_80437658 < local_60 * local_60 + local_68 * local_68 + local_64 * local_64) {
    dVar1 = gnt4_PSVECMag_bl(&local_68);
    dVar2 = gnt4_PSQUATDotProduct_bl((float *)(param_2 + 0x38),&local_68);
    dVar2 = (double)(float)(dVar2 / dVar1);
    dVar1 = (double)FLOAT_80437670;
    if ((dVar2 <= dVar1) && (dVar1 = dVar2, dVar2 < (double)FLOAT_80437688)) {
      dVar1 = (double)FLOAT_80437688;
    }
    dVar3 = (double)(float)((double)FLOAT_8043768c * param_1);
    dVar2 = (double)gnt4_acos_bl(dVar1);
    dVar1 = (double)(float)dVar2;
    if (dVar3 < (double)(float)dVar2) {
      dVar1 = dVar3;
    }
    gnt4_PSVECCrossProduct_bl((float *)(param_2 + 0x38),&local_68,&local_68);
    if (local_60 * local_60 + local_68 * local_68 + local_64 * local_64 <= FLOAT_80437658) {
      local_60 = FLOAT_80437658;
      local_68 = FLOAT_80437658;
      local_64 = FLOAT_80437670;
    }
    gnt4_PSMTXRotAxisRad_bl(dVar1,afStack_5c,&local_68);
    gnt4_PSMTXMultVecSR_bl(afStack_5c,(float *)(param_2 + 0x38),(float *)(param_2 + 0x38));
  }
  return;
}



// ==== 8006c334  FUN_8006c334 ====

/* WARNING: Removing unreachable block (ram,0x8006c420) */
/* WARNING: Removing unreachable block (ram,0x8006c418) */
/* WARNING: Removing unreachable block (ram,0x8006c34c) */
/* WARNING: Removing unreachable block (ram,0x8006c344) */

undefined4 FUN_8006c334(double param_1,int param_2,float *param_3)

{
  undefined4 uVar1;
  double dVar2;
  double dVar3;
  float local_38;
  float local_34;
  float local_30;
  
  gnt4_PSVECNormalize_bl((float *)(param_2 + 0x38),(float *)(param_2 + 0x38));
  gnt4_PSVECSubtract_bl(param_3,(float *)(param_2 + 0x20),&local_38);
  if (FLOAT_80437658 < local_30 * local_30 + local_38 * local_38 + local_34 * local_34) {
    dVar2 = gnt4_PSVECMag_bl(&local_38);
    dVar3 = gnt4_PSQUATDotProduct_bl((float *)(param_2 + 0x38),&local_38);
    dVar3 = (double)(float)(dVar3 / dVar2);
    dVar2 = (double)FLOAT_80437670;
    if ((dVar3 <= dVar2) && (dVar2 = dVar3, dVar3 < (double)FLOAT_80437688)) {
      dVar2 = (double)FLOAT_80437688;
    }
    dVar2 = (double)gnt4_acos_bl(dVar2);
    if ((float)dVar2 <= (float)((double)FLOAT_8043768c * param_1)) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 8006c440  zz_006c440_ ====

void zz_006c440_(double param_1,int param_2,float *param_3)

{
  FUN_8006c1c8(param_1,param_2,param_3);
  gnt4_PSVECNormalize_bl((float *)(param_2 + 0x38),(float *)(param_2 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x44),(float *)(param_2 + 0x38),
                      (float *)(param_2 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x38),(float *)(param_2 + 0x20));
  return;
}



// ==== 8006c498  FUN_8006c498 ====

/* WARNING: Removing unreachable block (ram,0x8006c654) */
/* WARNING: Removing unreachable block (ram,0x8006c64c) */
/* WARNING: Removing unreachable block (ram,0x8006c644) */
/* WARNING: Removing unreachable block (ram,0x8006c63c) */
/* WARNING: Removing unreachable block (ram,0x8006c4c0) */
/* WARNING: Removing unreachable block (ram,0x8006c4b8) */
/* WARNING: Removing unreachable block (ram,0x8006c4b0) */
/* WARNING: Removing unreachable block (ram,0x8006c4a8) */

void FUN_8006c498(double param_1,int param_2,float *param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [13];
  
  dVar5 = (double)*(float *)(param_2 + 0x3c);
  *(float *)(param_2 + 0x3c) = FLOAT_80437658;
  dVar2 = gnt4_PSVECMag_bl((float *)(param_2 + 0x38));
  dVar1 = (double)FLOAT_80437690;
  if (dVar2 < dVar1) {
    dVar2 = zz_0045204_(*(short *)(param_2 + 0x72));
    *(float *)(param_2 + 0x38) = (float)((double)FLOAT_80437690 * dVar2);
    dVar2 = zz_0045238_(*(short *)(param_2 + 0x72));
    *(float *)(param_2 + 0x40) = (float)((double)FLOAT_80437690 * dVar2);
    dVar2 = dVar1;
  }
  gnt4_PSVECNormalize_bl((float *)(param_2 + 0x38),(float *)(param_2 + 0x38));
  gnt4_PSVECSubtract_bl(param_3,(float *)(param_2 + 0x20),&local_88);
  local_84 = FLOAT_80437658;
  gnt4_PSVECNormalize_bl(&local_88,&local_88);
  dVar3 = gnt4_PSQUATDotProduct_bl((float *)(param_2 + 0x38),&local_88);
  dVar1 = (double)FLOAT_80437670;
  if ((dVar3 <= dVar1) && (dVar1 = dVar3, dVar3 < (double)FLOAT_80437688)) {
    dVar1 = (double)FLOAT_80437688;
  }
  dVar4 = (double)(float)((double)FLOAT_8043768c * param_1);
  dVar3 = (double)gnt4_acos_bl(dVar1);
  dVar1 = (double)(float)dVar3;
  if (dVar4 < (double)(float)dVar3) {
    dVar1 = dVar4;
  }
  gnt4_PSVECCrossProduct_bl((float *)(param_2 + 0x38),&local_88,&local_88);
  if (local_80 * local_80 + local_88 * local_88 + local_84 * local_84 <= FLOAT_80437658) {
    local_80 = FLOAT_80437658;
    local_88 = FLOAT_80437658;
    local_84 = FLOAT_80437670;
  }
  gnt4_PSMTXRotAxisRad_bl(dVar1,afStack_7c,&local_88);
  gnt4_PSMTXMultVecSR_bl(afStack_7c,(float *)(param_2 + 0x38),(float *)(param_2 + 0x38));
  gnt4_PSQUATScale_bl(dVar2,(float *)(param_2 + 0x38),(float *)(param_2 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x38),(float *)(param_2 + 0x20));
  *(float *)(param_2 + 0x3c) = (float)dVar5;
  return;
}



// ==== 8006c674  zz_006c674_ ====

undefined4 zz_006c674_(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  short sVar3;
  int iVar4;
  float local_18 [2];
  float local_10;
  
  if (*(int *)(param_1 + 0x508) == 0) {
    uVar1 = 0;
  }
  else {
    zz_0066408_(param_1,0,(float *)(param_1 + 0x50c),local_18);
    iVar2 = FUN_800452a0((double)local_18[0],(double)local_10);
    iVar4 = *(int *)(param_1 + 0x4ac);
    sVar3 = (short)iVar2;
    if (*(short *)(iVar4 + 0x15c) < sVar3) {
      uVar1 = 2;
    }
    else if (*(short *)(iVar4 + 0x158) < sVar3) {
      uVar1 = 1;
    }
    else if (sVar3 < *(short *)(iVar4 + 0x15a)) {
      if (sVar3 < *(short *)(iVar4 + 0x15e)) {
        uVar1 = 2;
      }
      else {
        uVar1 = 3;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}



// ==== 8006c728  zz_006c728_ ====

void zz_006c728_(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  short sVar8;
  int iVar9;
  short *psVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
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
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  double local_28;
  
  dVar13 = DOUBLE_804376a0;
  fVar1 = FLOAT_80437694;
  if (*(int *)(param_1 + 0x508) == 0) {
    iVar6 = param_1 + param_3 * 6;
    local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar6 + 0x18d4)) ^ 0x80000000);
    *(short *)(iVar6 + 0x18d4) = (short)(int)((float)(local_58 - DOUBLE_804376a0) * FLOAT_80437694);
    local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar6 + 0x18d6)) ^ 0x80000000);
    *(short *)(iVar6 + 0x18d6) = (short)(int)((float)(local_48 - dVar13) * fVar1);
  }
  else {
    iVar11 = *(int *)(param_1 + 0x4ac);
    iVar9 = param_1 + param_4 * 0x30;
    local_88 = *(float *)(iVar9 + 0x8d4);
    iVar6 = param_1 + param_3 * 0x30;
    psVar10 = (short *)(iVar11 + param_2 * 8 + 0x164);
    local_78 = *(undefined4 *)(iVar9 + 0x8e4);
    local_68 = *(undefined4 *)(iVar9 + 0x8f4);
    local_84 = *(undefined4 *)(iVar9 + 0x8d8);
    local_74 = *(undefined4 *)(iVar9 + 0x8e8);
    local_64 = *(undefined4 *)(iVar9 + 0x8f8);
    local_80 = *(undefined4 *)(iVar9 + 0x8dc);
    local_70 = *(undefined4 *)(iVar9 + 0x8ec);
    local_60 = *(undefined4 *)(iVar9 + 0x8fc);
    local_7c = *(undefined4 *)(iVar6 + 0x8e0);
    local_6c = *(undefined4 *)(iVar6 + 0x8f0);
    local_5c = *(undefined4 *)(iVar6 + 0x900);
    local_94 = *(float *)(iVar6 + 0x8dc);
    local_90 = *(float *)(iVar6 + 0x8ec);
    local_8c = *(float *)(iVar6 + 0x8fc);
    zz_0066454_(param_1,param_4,&local_94,&local_94);
    zz_004516c_(&local_88,(float *)(param_1 + 0x50c),&local_a0);
    dVar13 = (double)(local_94 * local_94 + local_8c * local_8c);
    if ((double)FLOAT_80437658 < dVar13) {
      dVar12 = 1.0 / SQRT(dVar13);
      dVar12 = DOUBLE_80437660 * dVar12 * -(dVar13 * dVar12 * dVar12 - DOUBLE_80437668);
      dVar12 = DOUBLE_80437660 * dVar12 * -(dVar13 * dVar12 * dVar12 - DOUBLE_80437668);
      dVar13 = (double)(float)(dVar13 * DOUBLE_80437660 * dVar12 *
                                        -(dVar13 * dVar12 * dVar12 - DOUBLE_80437668));
    }
    iVar6 = FUN_800452a0((double)local_90,dVar13);
    iVar9 = FUN_800452a0((double)local_94,(double)local_8c);
    dVar13 = (double)(local_a0 * local_a0 + local_98 * local_98);
    if ((double)FLOAT_80437658 < dVar13) {
      dVar12 = 1.0 / SQRT(dVar13);
      dVar12 = DOUBLE_80437660 * dVar12 * -(dVar13 * dVar12 * dVar12 - DOUBLE_80437668);
      dVar12 = DOUBLE_80437660 * dVar12 * -(dVar13 * dVar12 * dVar12 - DOUBLE_80437668);
      dVar13 = (double)(float)(dVar13 * DOUBLE_80437660 * dVar12 *
                                        -(dVar13 * dVar12 * dVar12 - DOUBLE_80437668));
    }
    iVar4 = FUN_800452a0((double)local_9c,dVar13);
    iVar5 = FUN_800452a0((double)local_a0,(double)local_98);
    if ((short)-(short)iVar4 < 1) {
      sVar7 = *(short *)(iVar11 + 0x160);
      sVar8 = psVar10[2];
    }
    else {
      sVar7 = *(short *)(iVar11 + 0x162);
      sVar8 = psVar10[3];
    }
    local_40 = (double)(CONCAT44(0x43300000,(int)(short)-(short)iVar4) ^ 0x80000000);
    local_48 = (double)CONCAT44(0x43300000,(int)sVar7 ^ 0x80000000);
    fVar1 = (float)(local_40 - DOUBLE_804376a0) / (float)(local_48 - DOUBLE_804376a0);
    if (fVar1 < FLOAT_80437658) {
      fVar1 = -fVar1;
    }
    if (FLOAT_80437670 < fVar1) {
      fVar1 = FLOAT_80437670;
    }
    local_50 = (double)(CONCAT44(0x43300000,(int)sVar8) ^ 0x80000000);
    dVar13 = local_50 - DOUBLE_804376a0;
    if ((short)iVar5 < 1) {
      sVar7 = *(short *)(iVar11 + 0x15e);
      sVar8 = psVar10[1];
    }
    else {
      sVar7 = *(short *)(iVar11 + 0x15c);
      sVar8 = *psVar10;
    }
    local_40 = (double)CONCAT44(0x43300000,(int)(short)iVar5 ^ 0x80000000);
    local_48 = (double)CONCAT44(0x43300000,(int)sVar7 ^ 0x80000000);
    fVar2 = (float)(local_40 - DOUBLE_804376a0) / (float)(local_48 - DOUBLE_804376a0);
    if (fVar2 < FLOAT_80437658) {
      fVar2 = -fVar2;
    }
    if (FLOAT_80437670 < fVar2) {
      fVar2 = FLOAT_80437670;
    }
    local_50 = (double)(CONCAT44(0x43300000,(int)sVar8) ^ 0x80000000);
    sVar8 = (short)(int)((float)dVar13 * fVar1) + (short)iVar6;
    sVar7 = (short)(int)((float)(local_50 - DOUBLE_804376a0) * fVar2) - (short)iVar9;
    if (param_5 == 1) {
      local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1af8)) ^ 0x80000000);
      uVar3 = (int)((float)(local_40 - DOUBLE_804376a0) + *(float *)(param_1 + 0x1aec)) & 0xffff;
      fVar1 = FLOAT_80437670;
      if (uVar3 != 0) {
        local_50 = (double)CONCAT44(0x43300000,uVar3);
        fVar1 = *(float *)(param_1 + 0x1adc) / (float)(local_50 - DOUBLE_804376a8);
      }
      local_58 = (double)CONCAT44(0x43300000,(int)sVar7 ^ 0x80000000);
      local_30 = (double)CONCAT44(0x43300000,(int)sVar8 ^ 0x80000000);
      sVar7 = (short)(int)((float)(local_58 - DOUBLE_804376a0) * fVar1);
      sVar8 = (short)(int)((float)(local_30 - DOUBLE_804376a0) * fVar1);
    }
    else if (param_5 == 2) {
      local_28 = (double)(CONCAT44(0x43300000,(int)sVar8) ^ 0x80000000);
      local_38 = (double)CONCAT44(0x43300000,(int)sVar7 ^ 0x80000000);
      sVar8 = (short)(int)((float)(local_28 - DOUBLE_804376a0) * FLOAT_80437698);
      sVar7 = (short)(int)((float)(local_38 - DOUBLE_804376a0) * FLOAT_80437698);
    }
    else if (param_5 == 3) {
      local_28 = (double)(CONCAT44(0x43300000,(int)sVar8) ^ 0x80000000);
      local_38 = (double)CONCAT44(0x43300000,(int)sVar7 ^ 0x80000000);
      sVar8 = (short)(int)((float)(local_28 - DOUBLE_804376a0) * FLOAT_8043769c);
      sVar7 = (short)(int)((float)(local_38 - DOUBLE_804376a0) * FLOAT_8043769c);
    }
    iVar6 = param_1 + param_3 * 6;
    *(short *)(iVar6 + 0x18d4) = *(short *)(iVar6 + 0x18d4) + sVar8;
    *(short *)(iVar6 + 0x18d6) = *(short *)(iVar6 + 0x18d6) + sVar7;
  }
  return;
}



// ==== 8006cc90  FUN_8006cc90 ====

/* WARNING: Removing unreachable block (ram,0x8006d0c0) */
/* WARNING: Removing unreachable block (ram,0x8006cca0) */

undefined4 FUN_8006cc90(double param_1,int param_2,int param_3,int param_4,short *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  short sVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  short sVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
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
  double local_38;
  undefined8 local_30;
  
  fVar3 = FLOAT_804376b0;
  dVar12 = DOUBLE_804376a0;
  fVar2 = FLOAT_80437694;
  fVar1 = FLOAT_80437670;
  if (*(int *)(param_2 + 0xcc) == 0) {
    uVar5 = 1;
    iVar8 = param_2 + param_3 * 6;
    *(short *)(iVar8 + 0x18d4) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(iVar8 + 0x18d4) ^ 0x80000000) -
                             DOUBLE_804376a0) *
                     (FLOAT_804376b0 * (FLOAT_80437670 - *(float *)(param_2 + 0x1dc8)) +
                     FLOAT_80437694));
    local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x18d6)) ^ 0x80000000);
    *(short *)(iVar8 + 0x18d6) =
         (short)(int)((float)(local_38 - dVar12) *
                     (fVar3 * (fVar1 - *(float *)(param_2 + 0x1dc8)) + fVar2));
  }
  else {
    iVar10 = param_2 + param_4 * 0x30;
    local_78 = *(float *)(iVar10 + 0x8d4);
    iVar8 = param_2 + param_3 * 0x30;
    local_68 = *(undefined4 *)(iVar10 + 0x8e4);
    local_58 = *(undefined4 *)(iVar10 + 0x8f4);
    local_74 = *(undefined4 *)(iVar10 + 0x8d8);
    local_64 = *(undefined4 *)(iVar10 + 0x8e8);
    local_54 = *(undefined4 *)(iVar10 + 0x8f8);
    local_70 = *(undefined4 *)(iVar10 + 0x8dc);
    local_60 = *(undefined4 *)(iVar10 + 0x8ec);
    local_50 = *(undefined4 *)(iVar10 + 0x8fc);
    local_6c = *(undefined4 *)(iVar8 + 0x8e0);
    local_5c = *(undefined4 *)(iVar8 + 0x8f0);
    local_4c = *(undefined4 *)(iVar8 + 0x900);
    local_84 = *(float *)(iVar8 + 0x8dc);
    local_80 = *(float *)(iVar8 + 0x8ec);
    local_7c = *(float *)(iVar8 + 0x8fc);
    zz_0066454_(param_2,param_4,&local_84,&local_84);
    zz_004516c_(&local_78,(float *)(param_2 + 0x518),&local_90);
    dVar12 = (double)(local_84 * local_84 + local_7c * local_7c);
    if ((double)FLOAT_80437658 < dVar12) {
      dVar11 = 1.0 / SQRT(dVar12);
      dVar11 = DOUBLE_80437660 * dVar11 * -(dVar12 * dVar11 * dVar11 - DOUBLE_80437668);
      dVar11 = DOUBLE_80437660 * dVar11 * -(dVar12 * dVar11 * dVar11 - DOUBLE_80437668);
      dVar12 = (double)(float)(dVar12 * DOUBLE_80437660 * dVar11 *
                                        -(dVar12 * dVar11 * dVar11 - DOUBLE_80437668));
    }
    iVar8 = FUN_800452a0((double)local_80,dVar12);
    iVar10 = FUN_800452a0((double)local_84,(double)local_7c);
    dVar12 = (double)(local_90 * local_90 + local_88 * local_88);
    if ((double)FLOAT_80437658 < dVar12) {
      dVar11 = 1.0 / SQRT(dVar12);
      dVar11 = DOUBLE_80437660 * dVar11 * -(dVar12 * dVar11 * dVar11 - DOUBLE_80437668);
      dVar11 = DOUBLE_80437660 * dVar11 * -(dVar12 * dVar11 * dVar11 - DOUBLE_80437668);
      dVar12 = (double)(float)(dVar12 * DOUBLE_80437660 * dVar11 *
                                        -(dVar12 * dVar11 * dVar11 - DOUBLE_80437668));
    }
    iVar6 = FUN_800452a0((double)local_8c,dVar12);
    sVar4 = -(short)iVar6;
    iVar6 = FUN_800452a0((double)local_90,(double)local_88);
    sVar9 = (short)iVar6;
    if (sVar4 < 1) {
      if (sVar4 <= param_5[2]) {
        sVar4 = param_5[2];
      }
    }
    else if (param_5[3] <= sVar4) {
      sVar4 = param_5[3];
    }
    if (sVar9 < 1) {
      if (sVar9 <= param_5[1]) {
        sVar9 = param_5[1];
      }
    }
    else if (*param_5 <= sVar9) {
      sVar9 = *param_5;
    }
    dVar12 = (double)FLOAT_80437670;
    if ((param_1 <= dVar12) && (dVar12 = param_1, param_1 < (double)FLOAT_80437658)) {
      dVar12 = (double)FLOAT_80437658;
    }
    fVar1 = (float)((double)*(float *)(param_2 + 0x1dc8) * dVar12);
    local_30 = (double)(CONCAT44(0x43300000,(int)sVar4 - (int)(short)-(short)iVar8) ^ 0x80000000);
    dVar12 = local_30 - DOUBLE_804376a0;
    if ((param_5[1] == -0x7fff) && (*param_5 == 0x7fff)) {
      uVar7 = (int)sVar9 - (int)(short)iVar10;
      if ((int)uVar7 < 0x8001) {
        if ((int)uVar7 < -0x8000) {
          uVar7 = uVar7 + 0x10000;
        }
      }
      else {
        uVar7 = uVar7 - 0x10000;
      }
      local_30 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
      sVar4 = (short)(int)((float)(local_30 - DOUBLE_804376a0) * fVar1);
    }
    else {
      local_30 = (double)(CONCAT44(0x43300000,(int)sVar9 - (int)(short)iVar10) ^ 0x80000000);
      sVar4 = (short)(int)(fVar1 * (float)(local_30 - DOUBLE_804376a0));
    }
    sVar9 = (short)(int)(fVar1 * (float)dVar12);
    iVar8 = param_2 + param_3 * 6;
    *(short *)(iVar8 + 0x18d4) = *(short *)(iVar8 + 0x18d4) + sVar9;
    *(short *)(iVar8 + 0x18d6) = *(short *)(iVar8 + 0x18d6) + sVar4;
    if ((sVar9 == 0) && (sVar4 == 0)) {
      uVar5 = 1;
    }
    else {
      uVar5 = 0;
    }
  }
  return uVar5;
}



// ==== 8006d0dc  zz_006d0dc_ ====

void zz_006d0dc_(int param_1,uint param_2,short param_3)

{
  zz_006660c_(param_1);
  if (*(int *)(param_1 + 0xcc) != 0) {
    *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) - param_3;
  }
  FUN_800669d0(param_1,param_2);
  return;
}



// ==== 8006d144  zz_006d144_ ====

void zz_006d144_(int param_1,uint param_2)

{
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5ac) - *(short *)(param_1 + 0x72);
  }
  else {
    zz_006660c_(param_1);
  }
  FUN_800669d0(param_1,param_2);
  return;
}



// ==== 8006d1a8  zz_006d1a8_ ====

void zz_006d1a8_(int param_1,uint param_2,float *param_3)

{
  int iVar1;
  float local_28 [2];
  float local_20;
  
  zz_006660c_(param_1);
  gnt4_PSVECSubtract_bl(param_3,(float *)(param_1 + 0x20),local_28);
  iVar1 = FUN_800452a0((double)local_28[0],(double)local_20);
  *(short *)(param_1 + 0x5ac) = (short)iVar1;
  *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5ac) - *(short *)(param_1 + 0x72);
  FUN_800669d0(param_1,param_2);
  return;
}



// ==== 8006d228  zz_006d228_ ====

/* WARNING: Removing unreachable block (ram,0x8006d4f8) */
/* WARNING: Removing unreachable block (ram,0x8006d4f0) */
/* WARNING: Removing unreachable block (ram,0x8006d240) */
/* WARNING: Removing unreachable block (ram,0x8006d238) */

void zz_006d228_(int param_1,int param_2,uint param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float afStack_48 [3];
  float local_3c;
  float local_38;
  float local_34;
  
  if (param_2 == 0) {
    return;
  }
  if ('\x01' < *(char *)(param_1 + 0x18)) {
    return;
  }
  if (*(char *)(param_2 + 0x4a0) == '\x01') {
    zz_006d228_(param_1,*(int *)(param_2 + 0x4a4),param_3);
  }
  if ((param_3 & 0x80) == 0) {
    if (param_3 == 1) {
      gnt4_PSVECSubtract_bl((float *)(param_2 + 0x20),(float *)(param_1 + 0x20),afStack_48);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_3c);
      if (local_34 * local_34 + local_3c * local_3c + local_38 * local_38 <= FLOAT_804376b4) {
        local_3c = *(float *)(param_1 + 0x38);
        local_38 = *(float *)(param_1 + 0x3c);
        local_34 = *(float *)(param_1 + 0x40);
        if (local_34 * local_34 + local_3c * local_3c + local_38 * local_38 <= FLOAT_804376b4) {
          return;
        }
      }
      dVar5 = gnt4_cos_bl(DOUBLE_804376b8);
      dVar7 = (double)(float)dVar5;
      dVar5 = gnt4_PSVECMag_bl(afStack_48);
      dVar6 = gnt4_PSVECMag_bl(&local_3c);
      dVar6 = (double)(float)(dVar6 * dVar5);
      dVar5 = gnt4_PSQUATDotProduct_bl(&local_3c,afStack_48);
      if ((double)(float)(dVar5 / dVar6) < dVar7) {
        return;
      }
    }
    else if ((param_3 == 0) && (*(char *)(param_1 + 0x88) == *(char *)(param_2 + 0x88))) {
      if (*(char *)(param_1 + 0x83) != '\0') {
        return;
      }
      *(byte *)(param_2 + 0x58a) = *(byte *)(param_2 + 0x58a) | *(byte *)(param_1 + 0x3e5);
      *(byte *)(param_2 + 0x58b) = *(byte *)(param_2 + 0x58b) | *(byte *)(param_1 + 0x3e5);
      return;
    }
  }
  else {
    param_3 = param_3 & 0x7f;
  }
  iVar2 = (int)*(char *)(param_2 + 0x3e4);
  iVar3 = FUN_800452a0((double)(*(float *)(param_1 + 0x20) - *(float *)(param_2 + 0x20)),
                       (double)(*(float *)(param_1 + 0x28) - *(float *)(param_2 + 0x28)));
  sVar1 = (short)iVar3 - (&DAT_803c7422)[iVar2 * 0x1f2];
  FUN_800452a0((double)(*(float *)(param_1 + 0x20) - (float)(&DAT_803c7698)[iVar2 * 0xf9]),
               (double)(*(float *)(param_1 + 0x28) - (float)(&DAT_803c76a0)[iVar2 * 0xf9]));
  if ((sVar1 < 0x2801) && (-0x2801 < sVar1)) {
    bVar4 = 1;
  }
  else if ((sVar1 < 0x5801) && (-1 < sVar1)) {
    bVar4 = 2;
  }
  else if ((sVar1 < 0) && (-0x5801 < sVar1)) {
    bVar4 = 8;
  }
  else {
    bVar4 = 4;
  }
  if (*(short *)(param_2 + 0x6b8) != 0) {
    if (bVar4 == 2) {
      bVar4 = 8;
    }
    else if (bVar4 == 8) {
      bVar4 = 2;
    }
  }
  if (param_3 == 1) {
    *(byte *)(param_2 + 0x58d) = *(byte *)(param_2 + 0x58d) | bVar4;
  }
  else {
    *(byte *)(param_2 + 0x58c) = *(byte *)(param_2 + 0x58c) | bVar4;
    if ((*(char *)(param_1 + 0x83) == '\0') &&
       (*(byte *)(param_2 + 0x58a) = *(byte *)(param_2 + 0x58a) | *(byte *)(param_1 + 0x3e5),
       *(char *)(param_1 + 0x88) == *(char *)(param_2 + 0x88))) {
      *(byte *)(param_2 + 0x58b) = *(byte *)(param_2 + 0x58b) | *(byte *)(param_1 + 0x3e5);
    }
  }
  return;
}



// ==== 8006d520  zz_006d520_ ====

void zz_006d520_(int param_1,float *param_2)

{
  float fVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  short sVar8;
  double dVar9;
  double dVar10;
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
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float afStack_48 [13];
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x20000000) != 0) {
    return;
  }
  if (((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) && (*(char *)(param_1 + 0x1db) == '\0')) {
    gnt4_PSMTXCopy_bl((float *)(param_1 + 0x8d4),afStack_48);
    local_78 = *param_2;
    local_74 = param_2[1];
    local_70 = param_2[2];
    local_6c = param_2[3];
    local_68 = param_2[4];
    local_64 = param_2[5];
    local_60 = param_2[6];
    local_5c = param_2[7];
    local_58 = param_2[8];
    local_54 = param_2[9];
    local_50 = param_2[10];
    local_4c = param_2[0xb];
    gnt4_PSMTXMultVec_bl(afStack_48,&local_78,&local_78);
    gnt4_PSMTXMultVec_bl(afStack_48,&local_6c,&local_6c);
    gnt4_PSMTXMultVec_bl(afStack_48,&local_60,&local_60);
    gnt4_PSMTXMultVec_bl(afStack_48,&local_54,&local_54);
    dVar9 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,&local_78);
    local_74 = (float)dVar9;
    dVar9 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,&local_6c);
    local_68 = (float)dVar9;
    dVar9 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,&local_60);
    local_5c = (float)dVar9;
    dVar9 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,&local_54);
    local_50 = (float)dVar9;
    fVar1 = *(float *)(param_1 + 0x668);
    fVar4 = -fVar1;
    if ((fVar4 < local_74 - local_68) && (local_74 - local_68 < fVar1)) {
      fVar3 = local_5c - (float)dVar9;
      if ((fVar4 < fVar3) &&
         ((((fVar3 < fVar1 && (fVar4 < local_74 - local_5c)) && (local_74 - local_5c < fVar1)) &&
          ((fVar3 = local_68 - (float)dVar9, fVar4 < fVar3 && (fVar3 < fVar1)))))) {
        gnt4_PSVECSubtract_bl(&local_78,&local_6c,&local_84);
        dVar9 = (double)(local_84 * local_84 + local_7c * local_7c);
        if (dVar9 <= DOUBLE_804376c0) {
          dVar10 = DOUBLE_804376c0;
          if (DOUBLE_804376c0 != dVar9) {
            if (dVar9 == DOUBLE_804376c0) {
              dVar10 = (double)DAT_80435dcc;
            }
            else {
              dVar10 = (double)DAT_80435dc8;
            }
          }
        }
        else {
          dVar10 = 1.0 / SQRT(dVar9);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = dVar9 * DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
        }
        local_84 = (float)dVar10;
        iVar5 = FUN_800452a0((double)local_80,(double)local_84);
        gnt4_PSVECSubtract_bl(&local_60,&local_54,&local_84);
        dVar9 = (double)(local_84 * local_84 + local_7c * local_7c);
        if (dVar9 <= DOUBLE_804376c0) {
          dVar10 = DOUBLE_804376c0;
          if (DOUBLE_804376c0 != dVar9) {
            if (dVar9 == DOUBLE_804376c0) {
              dVar10 = (double)DAT_80435dcc;
            }
            else {
              dVar10 = (double)DAT_80435dc8;
            }
          }
        }
        else {
          dVar10 = 1.0 / SQRT(dVar9);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = dVar9 * DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
        }
        local_84 = (float)dVar10;
        iVar6 = FUN_800452a0((double)local_80,(double)local_84);
        sVar8 = (short)(((int)(short)iVar5 + (int)(short)iVar6) / 2);
        gnt4_PSVECSubtract_bl(&local_78,&local_60,&local_84);
        dVar9 = (double)(local_84 * local_84 + local_7c * local_7c);
        if (dVar9 <= DOUBLE_804376c0) {
          dVar10 = DOUBLE_804376c0;
          if (DOUBLE_804376c0 != dVar9) {
            if (dVar9 == DOUBLE_804376c0) {
              dVar10 = (double)DAT_80435dcc;
            }
            else {
              dVar10 = (double)DAT_80435dc8;
            }
          }
        }
        else {
          dVar10 = 1.0 / SQRT(dVar9);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = dVar9 * DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
        }
        local_7c = (float)dVar10;
        iVar5 = FUN_800452a0((double)local_80,(double)local_7c);
        gnt4_PSVECSubtract_bl(&local_6c,&local_54,&local_84);
        dVar9 = (double)(local_84 * local_84 + local_7c * local_7c);
        if (dVar9 <= DOUBLE_804376c0) {
          dVar10 = DOUBLE_804376c0;
          if (DOUBLE_804376c0 != dVar9) {
            if (dVar9 == DOUBLE_804376c0) {
              dVar10 = (double)DAT_80435dcc;
            }
            else {
              dVar10 = (double)DAT_80435dc8;
            }
          }
        }
        else {
          dVar10 = 1.0 / SQRT(dVar9);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
          dVar10 = dVar9 * DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
        }
        local_7c = (float)dVar10;
        iVar6 = FUN_800452a0((double)local_80,(double)local_7c);
        sVar7 = (short)(((int)(short)-(short)iVar5 + (int)(short)-(short)iVar6) / 2);
        goto LAB_8006dafc;
      }
    }
    sVar8 = 0;
    sVar7 = 0;
  }
  else if (*(char *)(param_1 + 0x1db) == '\0') {
    sVar7 = 0;
    sVar8 = 0;
  }
  else {
    zz_00451b8_((float *)(param_1 + 0x8d4),(float *)(param_1 + 0x1ec),&local_84);
    dVar9 = (double)(local_84 * local_84 + local_80 * local_80);
    if ((double)FLOAT_80437658 < dVar9) {
      dVar10 = 1.0 / SQRT(dVar9);
      dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
      dVar10 = DOUBLE_80437660 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668);
      dVar9 = (double)(float)(dVar9 * DOUBLE_80437660 * dVar10 *
                                      -(dVar9 * dVar10 * dVar10 - DOUBLE_80437668));
    }
    iVar5 = FUN_800452a0((double)local_7c,dVar9);
    sVar7 = (short)iVar5;
    iVar5 = FUN_800452a0(-(double)local_84,(double)local_80);
    sVar8 = (short)iVar5;
  }
LAB_8006dafc:
  if (sVar7 < 0x1800) {
    if (sVar7 < -0x17ff) {
      sVar7 = -0x1800;
    }
  }
  else {
    sVar7 = 0x1800;
  }
  if (sVar8 < 0x1800) {
    if (sVar8 < -0x17ff) {
      sVar8 = -0x1800;
    }
  }
  else {
    sVar8 = 0x1800;
  }
  sVar2 = *(short *)(param_1 + 0x1d64);
  if (sVar7 < sVar2) {
    *(short *)(param_1 + 0x1d64) = sVar2 + -0x400;
    if (*(short *)(param_1 + 0x1d64) <= sVar7) {
      *(short *)(param_1 + 0x1d64) = sVar7;
    }
  }
  else if ((sVar2 < sVar7) &&
          (*(short *)(param_1 + 0x1d64) = sVar2 + 0x400, sVar7 <= *(short *)(param_1 + 0x1d64))) {
    *(short *)(param_1 + 0x1d64) = sVar7;
  }
  sVar7 = *(short *)(param_1 + 0x1d68);
  if (sVar8 < sVar7) {
    *(short *)(param_1 + 0x1d68) = sVar7 + -0x400;
    if (*(short *)(param_1 + 0x1d68) <= sVar8) {
      *(short *)(param_1 + 0x1d68) = sVar8;
    }
  }
  else if ((sVar7 < sVar8) &&
          (*(short *)(param_1 + 0x1d68) = sVar7 + 0x400, sVar8 <= *(short *)(param_1 + 0x1d68))) {
    *(short *)(param_1 + 0x1d68) = sVar8;
  }
  return;
}



// ==== 8006dbe0  zz_006dbe0_ ====

undefined4 zz_006dbe0_(int param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = param_1 + param_2 * 8;
  if (*(short *)(iVar3 + 0x774) < param_3) {
    uVar2 = 0;
  }
  else if (param_4 == 0) {
    uVar2 = 1;
  }
  else {
    *(short *)(iVar3 + 0x776) = *(short *)(iVar3 + 0x774);
    *(short *)(iVar3 + 0x774) = *(short *)(iVar3 + 0x774) - (short)param_3;
    sVar1 = *(short *)(iVar3 + 0x790);
    if (sVar1 == 1) {
      *(float *)(iVar3 + 0x778) =
           *(float *)(iVar3 + 0x778) +
           (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x792) ^ 0x80000000) -
                  DOUBLE_804376a0);
    }
    else if (sVar1 < 1) {
      if ((-1 < sVar1) && (*(short *)(iVar3 + 0x774) == 0)) {
        *(float *)(iVar3 + 0x778) =
             (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x792) ^ 0x80000000) -
                    DOUBLE_804376a0);
      }
    }
    else if (sVar1 < 4) {
      *(float *)(iVar3 + 0x778) = FLOAT_80437658;
    }
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 8006dcc0  zz_006dcc0_ ====

void zz_006dcc0_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  short sVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  fVar1 = *(float *)(param_1 + 0x768);
  if (*(char *)(param_1 + 0x6fc) != '\0') {
    fVar1 = fVar1 * FLOAT_804376c8;
  }
  psVar5 = (short *)(param_1 + 0x774);
  iVar6 = param_1 + 0x78c;
  iVar7 = 0;
  iVar8 = 3;
  do {
    if ((((int)*(char *)(param_1 + 0x597) & 1 << iVar7) == 0) &&
       (fVar2 = *(float *)(psVar5 + 2), FLOAT_80437658 < fVar2)) {
      sVar4 = *(short *)(iVar6 + 4);
      if (sVar4 == 1) {
        if (FLOAT_80437658 < fVar2) {
          *(float *)(psVar5 + 2) = fVar2 - fVar1;
        }
        if (*(float *)(psVar5 + 2) <= FLOAT_80437658) {
          *psVar5 = *(short *)(iVar6 + 2);
          psVar5[1] = *(short *)(iVar6 + 2);
        }
        else {
          iVar3 = (int)*(short *)(iVar6 + 2) -
                  ((int)(*(float *)(psVar5 + 2) /
                        (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar6 + 6) ^ 0x80000000)
                               - DOUBLE_804376a0)) + 1);
          if (*psVar5 != iVar3) {
            sVar4 = (short)iVar3;
            *psVar5 = sVar4;
            psVar5[1] = sVar4;
          }
        }
      }
      else if ((sVar4 < 1) && (-1 < sVar4)) {
        if (FLOAT_80437658 < fVar2) {
          *(float *)(psVar5 + 2) = fVar2 - fVar1;
        }
        fVar2 = FLOAT_80437658;
        if (*(float *)(psVar5 + 2) <= FLOAT_80437658) {
          *psVar5 = *(short *)(iVar6 + 2);
          psVar5[1] = *(short *)(iVar6 + 2);
          *(float *)(psVar5 + 2) = fVar2;
        }
      }
    }
    iVar7 = iVar7 + 1;
    psVar5 = psVar5 + 4;
    iVar6 = iVar6 + 8;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  return;
}



// ==== 8006de10  zz_006de10_ ====

void zz_006de10_(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_1 + param_2 * 8;
  *(short *)(iVar1 + 0x774) = *(short *)(iVar1 + 0x774) + 1;
  if (*(short *)(iVar1 + 0x78e) <= *(short *)(iVar1 + 0x774)) {
    *(short *)(iVar1 + 0x774) = *(short *)(iVar1 + 0x78e);
  }
  *(undefined2 *)(iVar1 + 0x776) = *(undefined2 *)(iVar1 + 0x774);
  return;
}



// ==== 8006de44  zz_006de44_ ====

int zz_006de44_(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = 0;
  uVar2 = *(uint *)(param_1 + 0x5bc) & param_2;
  iVar3 = 4;
  do {
    if ((uVar2 & 1) != 0) {
      iVar1 = iVar1 + 1;
    }
    if (((int)uVar2 >> 1 & 1U) != 0) {
      iVar1 = iVar1 + 1;
    }
    if (((int)uVar2 >> 2 & 1U) != 0) {
      iVar1 = iVar1 + 1;
    }
    if (((int)uVar2 >> 3 & 1U) != 0) {
      iVar1 = iVar1 + 1;
    }
    if (((int)uVar2 >> 4 & 1U) != 0) {
      iVar1 = iVar1 + 1;
    }
    if (((int)uVar2 >> 5 & 1U) != 0) {
      iVar1 = iVar1 + 1;
    }
    if (((int)uVar2 >> 6 & 1U) != 0) {
      iVar1 = iVar1 + 1;
    }
    if (((int)uVar2 >> 7 & 1U) != 0) {
      iVar1 = iVar1 + 1;
    }
    uVar2 = (int)uVar2 >> 8;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return iVar1;
}



// ==== 8006dee8  zz_006dee8_ ====

undefined4 zz_006dee8_(int param_1,int param_2)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = zz_006672c_(param_1);
  sVar2 = (short)iVar3 - *(short *)(param_1 + 0x72);
  if ((sVar2 < 0x4801) && (-0x4801 < sVar2)) {
    *(undefined1 *)(param_1 + 0x587) = 0;
    if (0x4000 < sVar2) {
      sVar2 = 0x4000;
    }
    if (sVar2 < -0x4000) {
      sVar2 = -0x4000;
    }
    sVar1 = *(short *)(param_1 + 0x1dfc);
    if ((int)sVar2 - (int)sVar1 < 0x801) {
      if ((int)sVar2 - (int)sVar1 < -0x800) {
        uVar4 = 0;
        *(short *)(param_1 + 0x1dfc) = sVar1 + -0x800;
      }
      else {
        *(short *)(param_1 + 0x1dfc) = sVar2;
        uVar4 = 0x8444;
      }
    }
    else {
      uVar4 = 0;
      *(short *)(param_1 + 0x1dfc) = sVar1 + 0x800;
    }
  }
  else {
    if (param_2 == 0) {
      *(short *)(param_1 + 0x1dfc) =
           (short)(int)(((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1dfc) ^ 0x80000000)
                        - DOUBLE_804376a0) * DOUBLE_804376d0);
      *(undefined1 *)(param_1 + 0x587) = 2;
      *(undefined4 *)(param_1 + 0xcc) = 0;
      *(undefined4 *)(param_1 + 200) = 0;
    }
    uVar4 = 0xffffffff;
  }
  return uVar4;
}



// ==== 8006e004  zz_006e004_ ====

uint zz_006e004_(int param_1)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = zz_006672c_(param_1);
  sVar1 = (short)iVar2 - *(short *)(param_1 + 0x72);
  if ((sVar1 < 0x4801) && (-0x4801 < sVar1)) {
    if (0x4000 < sVar1) {
      sVar1 = 0x4000;
    }
    if (sVar1 < -0x4000) {
      sVar1 = -0x4000;
    }
    uVar3 = (int)sVar1 - (int)*(short *)(param_1 + 0x1dfc);
    if ((int)uVar3 < 0x801) {
      uVar3 = ~(1 - ((uint)(uVar3 < 0xfffff800) - ((int)uVar3 >> 0x1f))) & 0x8444;
    }
    else {
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 0xffffffff;
  }
  return uVar3;
}



// ==== 8006e0ac  FUN_8006e0ac ====

int FUN_8006e0ac(int param_1,short param_2)

{
  short sVar1;
  int iVar2;
  short sVar3;
  int iVar4;
  
  iVar2 = zz_006672c_(param_1);
  iVar4 = 0;
  sVar3 = (short)iVar2 - *(short *)(param_1 + 0x72);
  iVar2 = (int)sVar3;
  if (((short)(param_2 + 0x800) < iVar2) || (iVar2 < -(int)(short)(param_2 + 0x800))) {
    iVar4 = -1;
  }
  *(undefined1 *)(param_1 + 0x587) = 0;
  if (param_2 < iVar2) {
    sVar3 = param_2;
  }
  if ((int)sVar3 < -(int)param_2) {
    sVar3 = (short)-(int)param_2;
  }
  sVar1 = *(short *)(param_1 + 0x1dfc);
  if ((int)sVar3 - (int)sVar1 < 0x801) {
    if ((int)sVar3 - (int)sVar1 < -0x800) {
      *(short *)(param_1 + 0x1dfc) = sVar1 + -0x800;
      if (-1 < iVar4) {
        iVar4 = 0;
      }
    }
    else {
      *(short *)(param_1 + 0x1dfc) = sVar3;
      if (-1 < iVar4) {
        iVar4 = 1;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x1dfc) = sVar1 + 0x800;
    if (-1 < iVar4) {
      iVar4 = 0;
    }
  }
  return iVar4;
}



// ==== 8006e1ac  zz_006e1ac_ ====

void zz_006e1ac_(int param_1,uint param_2,int param_3)

{
  zz_006e1d0_(param_1,param_2,param_3,0x4000);
  return;
}



// ==== 8006e1d0  zz_006e1d0_ ====

/* WARNING: Removing unreachable block (ram,0x8006e374) */
/* WARNING: Removing unreachable block (ram,0x8006e1e0) */

undefined4 zz_006e1d0_(int param_1,uint param_2,int param_3,short param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  short sVar5;
  undefined4 uVar4;
  int iVar6;
  double dVar7;
  double dVar8;
  float local_48;
  float local_44;
  undefined4 local_40;
  double local_38;
  double local_30;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    uVar4 = 0xffffffff;
    iVar3 = param_1 + param_3 * 6;
    local_30 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x18d4)) ^ 0x80000000);
    *(short *)(iVar3 + 0x18d4) = (short)(int)((float)(local_30 - DOUBLE_804376a0) * FLOAT_804376d8);
  }
  else {
    local_38 = (double)(CONCAT44(0x43300000,
                                 (int)*(short *)(*(int *)(param_1 + 0x4ac) + (param_2 & 0xf) * 2 +
                                                0xac)) ^ 0x80000000);
    iVar6 = param_1 + param_3 * 0x30;
    local_48 = *(float *)(iVar6 + 0x8e0);
    local_44 = *(float *)(iVar6 + 0x8f0);
    iVar3 = (int)((float)(local_38 - DOUBLE_804376a0) * *(float *)(param_1 + 0x768));
    local_30 = (double)(longlong)iVar3;
    local_40 = *(undefined4 *)(iVar6 + 0x900);
    sVar2 = (short)iVar3;
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_48,&local_48);
    dVar8 = (double)local_44;
    local_44 = FLOAT_80437658;
    dVar7 = gnt4_PSVECMag_bl(&local_48);
    iVar3 = FUN_800452a0(dVar8,dVar7);
    sVar5 = -*(short *)(param_1 + 0x70) - (short)iVar3;
    if (param_4 < sVar5) {
      sVar5 = param_4;
    }
    if ((int)sVar5 < -(int)param_4) {
      sVar5 = (short)-(int)param_4;
    }
    iVar6 = param_1 + param_3 * 6;
    sVar1 = sVar5 - *(short *)(iVar6 + 0x18d4);
    iVar3 = (int)sVar1;
    if (iVar3 < 0) {
      iVar3 = -iVar3;
    }
    if (sVar2 < iVar3) {
      if (sVar1 < 0) {
        sVar2 = -sVar2;
      }
      uVar4 = 0;
      *(short *)(iVar6 + 0x18d4) = *(short *)(iVar6 + 0x18d4) + sVar2;
    }
    else {
      *(short *)(iVar6 + 0x18d4) = sVar5;
      uVar4 = 1;
    }
  }
  return uVar4;
}



// ==== 8006e39c  zz_006e39c_ ====

/* WARNING: Removing unreachable block (ram,0x8006e4ec) */
/* WARNING: Removing unreachable block (ram,0x8006e3ac) */

undefined4 zz_006e39c_(int param_1,uint param_2,int param_3,short param_4,float *param_5)

{
  short sVar1;
  short sVar2;
  int iVar3;
  short sVar5;
  undefined4 uVar4;
  int iVar6;
  double dVar7;
  double dVar8;
  float local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_38;
  uint uStack_34;
  longlong local_30;
  
  local_38 = 0x43300000;
  uStack_34 = (int)*(short *)(*(int *)(param_1 + 0x4ac) + (param_2 & 0xf) * 2 + 0xac) ^ 0x80000000;
  iVar6 = param_1 + param_3 * 0x30;
  local_48 = *(float *)(iVar6 + 0x8e0);
  local_44 = *(float *)(iVar6 + 0x8f0);
  iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_804376a0) *
               *(float *)(param_1 + 0x1dc8));
  local_30 = (longlong)iVar3;
  local_40 = *(undefined4 *)(iVar6 + 0x900);
  sVar2 = (short)iVar3;
  gnt4_PSVECSubtract_bl(param_5,&local_48,&local_48);
  dVar8 = (double)local_44;
  local_44 = FLOAT_80437658;
  dVar7 = gnt4_PSVECMag_bl(&local_48);
  iVar3 = FUN_800452a0(dVar8,dVar7);
  sVar5 = -*(short *)(param_1 + 0x70) - (short)iVar3;
  if (param_4 < sVar5) {
    sVar5 = param_4;
  }
  if ((int)sVar5 < -(int)param_4) {
    sVar5 = (short)-(int)param_4;
  }
  iVar6 = param_1 + param_3 * 6;
  sVar1 = sVar5 - *(short *)(iVar6 + 0x18d4);
  iVar3 = (int)sVar1;
  if (iVar3 < 0) {
    iVar3 = -iVar3;
  }
  if (sVar2 < iVar3) {
    if (sVar1 < 0) {
      sVar2 = -sVar2;
    }
    uVar4 = 0;
    *(short *)(iVar6 + 0x18d4) = *(short *)(iVar6 + 0x18d4) + sVar2;
  }
  else {
    *(short *)(iVar6 + 0x18d4) = sVar5;
    uVar4 = 1;
  }
  return uVar4;
}



// ==== 8006e514  zz_006e514_ ====

/* WARNING: Removing unreachable block (ram,0x8006e6a0) */
/* WARNING: Removing unreachable block (ram,0x8006e524) */

undefined4 zz_006e514_(int param_1,uint param_2,short *param_3)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  float local_48;
  float local_44;
  undefined4 local_40;
  double local_38;
  double local_30;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    uVar4 = 0xffffffff;
    local_30 = (double)(CONCAT44(0x43300000,(int)*param_3) ^ 0x80000000);
    *param_3 = (short)(int)((float)(local_30 - DOUBLE_804376a0) * FLOAT_804376d8);
  }
  else {
    local_38 = (double)(CONCAT44(0x43300000,
                                 (int)*(short *)(*(int *)(param_1 + 0x4ac) + (param_2 & 0xf) * 2 +
                                                0xac)) ^ 0x80000000);
    iVar5 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_48 = *(float *)(iVar5 + 0x8e0);
    local_44 = *(float *)(iVar5 + 0x8f0);
    iVar3 = (int)((float)(local_38 - DOUBLE_804376a0) * *(float *)(param_1 + 0x1dc8));
    local_30 = (double)(longlong)iVar3;
    local_40 = *(undefined4 *)(iVar5 + 0x900);
    sVar2 = (short)iVar3;
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_48,&local_48);
    dVar7 = (double)local_44;
    local_44 = FLOAT_80437658;
    dVar6 = gnt4_PSVECMag_bl(&local_48);
    iVar3 = FUN_800452a0(dVar7,dVar6);
    sVar1 = -*(short *)(param_1 + 0x70) - (short)iVar3;
    if (0x4000 < sVar1) {
      sVar1 = 0x4000;
    }
    if (sVar1 < -0x4000) {
      sVar1 = -0x4000;
    }
    iVar3 = (int)(short)(sVar1 - *param_3);
    if (iVar3 < 0) {
      iVar3 = -iVar3;
    }
    if (sVar2 < iVar3) {
      if ((short)(sVar1 - *param_3) < 0) {
        sVar2 = -sVar2;
      }
      uVar4 = 0;
      *param_3 = *param_3 + sVar2;
    }
    else {
      *param_3 = sVar1;
      uVar4 = 1;
    }
  }
  return uVar4;
}



// ==== 8006e6c4  zz_006e6c4_ ====

/* WARNING: Removing unreachable block (ram,0x8006e7fc) */
/* WARNING: Removing unreachable block (ram,0x8006e6d4) */

undefined4 zz_006e6c4_(int param_1,uint param_2,short *param_3,float *param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  double dVar5;
  double dVar6;
  float local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_38;
  uint uStack_34;
  longlong local_30;
  
  local_38 = 0x43300000;
  uStack_34 = (int)*(short *)(*(int *)(param_1 + 0x4ac) + (param_2 & 0xf) * 2 + 0xac) ^ 0x80000000;
  local_48 = *(float *)(param_1 + 0x910);
  local_44 = *(float *)(param_1 + 0x920);
  local_40 = *(undefined4 *)(param_1 + 0x930);
  iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_804376a0) *
               *(float *)(param_1 + 0x1dc8));
  local_30 = (longlong)iVar3;
  dVar5 = (double)(local_44 - *(float *)(param_1 + 0x24));
  sVar2 = (short)iVar3;
  gnt4_PSVECSubtract_bl(param_4,&local_48,&local_48);
  dVar6 = (double)(float)((double)local_44 - dVar5);
  local_44 = FLOAT_80437658;
  dVar5 = gnt4_PSVECMag_bl(&local_48);
  iVar3 = FUN_800452a0(dVar6,dVar5);
  sVar1 = -*(short *)(param_1 + 0x70) - (short)iVar3;
  if (0x4000 < sVar1) {
    sVar1 = 0x4000;
  }
  if (sVar1 < -0x4000) {
    sVar1 = -0x4000;
  }
  iVar3 = (int)(short)(sVar1 - *param_3);
  if (iVar3 < 0) {
    iVar3 = -iVar3;
  }
  if (sVar2 < iVar3) {
    if ((short)(sVar1 - *param_3) < 0) {
      sVar2 = -sVar2;
    }
    uVar4 = 0;
    *param_3 = *param_3 + sVar2;
  }
  else {
    *param_3 = sVar1;
    uVar4 = 1;
  }
  return uVar4;
}



// ==== 8006e820  zz_006e820_ ====

void zz_006e820_(int param_1)

{
  zz_006e848_(param_1,(short *)(param_1 + 0x18e0),0);
  return;
}



// ==== 8006e848  zz_006e848_ ====

undefined4 zz_006e848_(int param_1,short *param_2,int param_3)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    sVar2 = (short)(int)((float)((double)CONCAT44(0x43300000,
                                                  (int)*(short *)(*(int *)(param_1 + 0x4ac) + 0xae)
                                                  ^ 0x80000000) - DOUBLE_804376a0) *
                        *(float *)(param_1 + 0x1dc8));
    iVar4 = FUN_800667a0(param_1);
    sVar1 = -*(short *)(param_1 + 0x70) - (short)iVar4;
    if (param_3 != 0) {
      sVar1 = -sVar1;
    }
    if (0x2000 < sVar1) {
      sVar1 = 0x2000;
    }
    if (sVar1 < -0x2000) {
      sVar1 = -0x2000;
    }
    iVar4 = (int)(short)(sVar1 - *param_2);
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }
    if (sVar2 < iVar4) {
      if ((short)(sVar1 - *param_2) < 0) {
        sVar2 = -sVar2;
      }
      uVar3 = 0;
      *param_2 = *param_2 + sVar2;
    }
    else {
      *param_2 = sVar1;
      uVar3 = 1;
    }
  }
  return uVar3;
}



// ==== 8006e970  zz_006e970_ ====

void zz_006e970_(int param_1)

{
  zz_006e998_(param_1,(short *)(param_1 + 0x18e2),0);
  return;
}



// ==== 8006e998  zz_006e998_ ====

undefined4 zz_006e998_(int param_1,short *param_2,int param_3)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    sVar2 = (short)(int)((float)((double)CONCAT44(0x43300000,
                                                  (int)*(short *)(*(int *)(param_1 + 0x4ac) + 0xae)
                                                  ^ 0x80000000) - DOUBLE_804376a0) *
                        *(float *)(param_1 + 0x1dc8));
    iVar4 = zz_006672c_(param_1);
    sVar1 = (short)iVar4 - *(short *)(param_1 + 0x72);
    if (param_3 != 0) {
      sVar1 = -sVar1;
    }
    iVar4 = (int)(short)(sVar1 - *param_2);
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }
    if (sVar2 < iVar4) {
      if ((short)(sVar1 - *param_2) < 0) {
        sVar2 = -sVar2;
      }
      uVar3 = 0;
      *param_2 = *param_2 + sVar2;
    }
    else {
      *param_2 = sVar1;
      uVar3 = 1;
    }
  }
  return uVar3;
}



// ==== 8006ea9c  zz_006ea9c_ ====

uint zz_006ea9c_(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = zz_006e970_(param_1);
  uVar2 = zz_006e820_(param_1);
  return uVar2 & uVar1;
}



// ==== 8006eae0  zz_006eae0_ ====

uint zz_006eae0_(int param_1,short *param_2,short *param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = zz_006e998_(param_1,param_3,param_4 & 1);
  uVar2 = zz_006e848_(param_1,param_2,param_4 & 2);
  return uVar2 & uVar1;
}



// ==== 8006eb4c  zz_006eb4c_ ====

void zz_006eb4c_(float *param_1,float *param_2)

{
  float fVar1;
  double dVar2;
  
  dVar2 = gnt4_PSVECMag_bl(param_1);
  fVar1 = FLOAT_80437658;
  if ((double)FLOAT_80437658 < dVar2) {
    gnt4_PSVECNormalize_bl(param_1,param_2);
  }
  else {
    *param_2 = FLOAT_80437670;
    param_2[1] = fVar1;
    param_2[2] = fVar1;
  }
  return;
}



// ==== 8006ebb4  zz_006ebb4_ ====

void zz_006ebb4_(float *param_1,float *param_2)

{
  float fVar1;
  double dVar2;
  
  dVar2 = gnt4_PSVECMag_bl(param_1);
  fVar1 = FLOAT_80437658;
  if ((double)FLOAT_80437658 < dVar2) {
    gnt4_PSVECNormalize_bl(param_1,param_2);
  }
  else {
    *param_2 = FLOAT_80437658;
    param_2[1] = FLOAT_80437670;
    param_2[2] = fVar1;
  }
  return;
}



// ==== 8006ec1c  zz_006ec1c_ ====

void zz_006ec1c_(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  dVar3 = gnt4_PSVECMag_bl(param_1);
  fVar1 = FLOAT_80437658;
  if ((double)FLOAT_80437658 < dVar3) {
    gnt4_PSVECNormalize_bl(param_1,param_2);
  }
  else {
    *param_2 = FLOAT_80437658;
    fVar2 = FLOAT_80437670;
    param_2[1] = fVar1;
    param_2[2] = fVar2;
  }
  return;
}



// ==== 8006ec84  zz_006ec84_ ====

undefined4 zz_006ec84_(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 200) == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0xcc);
  if (iVar1 == 0) {
    return 0;
  }
  if ((*(char *)(iVar1 + 0x83) == '\0') &&
     ((*(byte *)(iVar1 + 0x5e6) & *(byte *)(param_1 + 0x3e5)) == 0)) {
    return 0;
  }
  return 0x8444;
}



// ==== 8006ece4  FUN_8006ece4 ====

void FUN_8006ece4(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    iVar1 = 0x26;
    *(undefined2 *)(param_1 + 0x272) = 0xffff;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
      iVar1 = 0x27;
    }
    zz_004beb8_((double)FLOAT_80437688,param_1,0xf,0,iVar1,0xffffffff,0xffffffff);
    FUN_800061a8(param_1,0xb);
  }
  zz_004cd24_(param_1,0xf);
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    zz_006a838_(param_1);
  }
  return;
}



// ==== 8006ed8c  zz_006ed8c_ ====

void zz_006ed8c_(double param_1,int param_2)

{
  float fVar1;
  
  if ((double)FLOAT_80437670 == (double)*(float *)(param_2 + 0x1dc8)) {
    *(float *)(param_2 + 0x44) = (float)((double)*(float *)(param_2 + 0x44) * param_1);
    *(float *)(param_2 + 0x48) = (float)((double)*(float *)(param_2 + 0x48) * param_1);
    return;
  }
  fVar1 = (float)((double)(float)((double)FLOAT_80437670 - param_1) *
                 (double)*(float *)(param_2 + 0x1dc8));
  *(float *)(param_2 + 0x44) = -(*(float *)(param_2 + 0x44) * fVar1 - *(float *)(param_2 + 0x44));
  *(float *)(param_2 + 0x48) = -(*(float *)(param_2 + 0x48) * fVar1 - *(float *)(param_2 + 0x48));
  return;
}



// ==== 8006eddc  zz_006eddc_ ====

void zz_006eddc_(double param_1,int param_2,float *param_3)

{
  if ((double)FLOAT_80437670 == (double)*(float *)(param_2 + 0x1dc8)) {
    *param_3 = (float)((double)*param_3 * param_1);
    return;
  }
  *param_3 = -(float)((double)*(float *)(param_2 + 0x1dc8) *
                      (double)(float)((double)*param_3 *
                                     (double)(float)((double)FLOAT_80437670 - param_1)) -
                     (double)*param_3);
  return;
}



// ==== 8006ee14  zz_006ee14_ ====

void zz_006ee14_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  double dVar7;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  iVar6 = *(int *)(param_1 + 0x90);
  if ((-1 < (char)(&DAT_802d3ab4)[*(byte *)(iVar6 + 0x3e9)]) &&
     (puVar2 = zz_0088aa0_(iVar6,3,8,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x83] = 0x10;
    puVar2[0x10] = 0xe;
    puVar2[0x11] = param_2;
    *(code **)(puVar2 + 0xc) = FUN_8006f0cc;
    *(code **)(puVar2 + 0x10c) = FUN_8006f4b8;
    *(int *)(puVar2 + 0x8c) = iVar6;
    *(undefined4 *)(puVar2 + 0x90) = *(undefined4 *)(iVar6 + 0x90);
    *(undefined2 *)(puVar2 + 0x94) = *(undefined2 *)(iVar6 + 0x94);
    puVar2[0x96] = *(undefined1 *)(iVar6 + 0x96);
    puVar2[0x97] = *(undefined1 *)(iVar6 + 0x97);
    puVar2[0x88] = *(undefined1 *)(iVar6 + 0x88);
    *(undefined4 *)(puVar2 + 200) = *(undefined4 *)(iVar6 + 200);
    *(undefined4 *)(puVar2 + 0xcc) = *(undefined4 *)(iVar6 + 0xcc);
    *(undefined4 *)(puVar2 + 0xb8) = *(undefined4 *)(iVar6 + 0xb8);
    *(undefined4 *)(puVar2 + 0xb4) = *(undefined4 *)(iVar6 + 0xb4);
    *(undefined4 *)(puVar2 + 0x58) = *(undefined4 *)(iVar6 + 0xb4);
    *(undefined4 *)(puVar2 + 0x5c) = *(undefined4 *)(iVar6 + 0xb4);
    *(undefined4 *)(puVar2 + 0x60) = *(undefined4 *)(iVar6 + 0xb4);
    *(undefined4 *)(puVar2 + 0xc0) = *(undefined4 *)(iVar6 + 0xc0);
    *(undefined4 *)(puVar2 + 0xc4) = *(undefined4 *)(iVar6 + 0xc4);
    puVar2[0xd0] = *(undefined1 *)(iVar6 + 0xd0);
    iVar3 = (uint)(byte)puVar2[0x11] * 0x34;
    if ((char)(&DAT_802d39b2)[iVar3] < '\0') {
      pfVar5 = (float *)(param_1 + 0x114);
    }
    else {
      pfVar5 = (float *)(iVar6 + (char)(&DAT_802d39b2)[iVar3] * 0x30 + 0x8d4);
    }
    gnt4_PSMTXMultVec_bl(pfVar5,(float *)(iVar3 + -0x7fd2c64c),(float *)(puVar2 + 0x20));
    if (puVar2[0x11] == '\x02') {
      gnt4_PSVECAdd_bl((float *)(puVar2 + 0x20),(float *)(iVar6 + 0x7b0),(float *)(puVar2 + 0x20));
    }
    sVar1 = *(short *)(&DAT_802d39dc + iVar3);
    if (sVar1 == 1) {
      *(float *)(puVar2 + 0x38) = pfVar5[1];
      *(float *)(puVar2 + 0x3c) = pfVar5[5];
      *(float *)(puVar2 + 0x40) = pfVar5[9];
    }
    else if (sVar1 < 1) {
      if (-1 < sVar1) {
        *(float *)(puVar2 + 0x38) = *pfVar5;
        *(float *)(puVar2 + 0x3c) = pfVar5[4];
        *(float *)(puVar2 + 0x40) = pfVar5[8];
      }
    }
    else if (sVar1 < 3) {
      *(float *)(puVar2 + 0x38) = pfVar5[2];
      *(float *)(puVar2 + 0x3c) = pfVar5[6];
      *(float *)(puVar2 + 0x40) = pfVar5[10];
    }
    if (*(short *)(&DAT_802d39de + iVar3) == 1) {
      gnt4_PSQUATScale_bl((double)FLOAT_804376e0,(float *)(puVar2 + 0x38),(float *)(puVar2 + 0x38));
    }
    if ((*(int *)(iVar6 + 200) == 0) ||
       (iVar4 = FUN_8006c334((double)*(float *)(&DAT_802d39e0 + iVar3),(int)puVar2,
                             (float *)(iVar6 + 0x518)), iVar4 == 0)) {
      *(undefined4 *)(puVar2 + 200) = 0;
      *(undefined4 *)(puVar2 + 0x38) = *(undefined4 *)(param_1 + 0x11c);
      *(undefined4 *)(puVar2 + 0x3c) = *(undefined4 *)(param_1 + 300);
      *(undefined4 *)(puVar2 + 0x40) = *(undefined4 *)(param_1 + 0x13c);
      gnt4_PSVECNormalize_bl((float *)(puVar2 + 0x38),&local_28);
      local_24 = FLOAT_804376e4;
      dVar7 = gnt4_PSVECMag_bl(&local_28);
      if ((double)FLOAT_804376e4 < dVar7) {
        *(float *)(puVar2 + 0x38) = local_28;
        *(float *)(puVar2 + 0x3c) = local_24;
        *(undefined4 *)(puVar2 + 0x40) = local_20;
      }
    }
    else {
      zz_0083d60_((int)puVar2,iVar6,(byte)(&DAT_802d39b2)[iVar3] & 0x7f);
    }
    zz_00f036c_(param_1,8);
  }
  return;
}



// ==== 8006f0cc  FUN_8006f0cc ====

void FUN_8006f0cc(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_802d3ac4)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8006f11c  FUN_8006f11c ====

void FUN_8006f11c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x34;
  *(code **)(param_9 + 0x100) = FUN_8006f448;
  iVar5 = iVar4;
  zz_0089100_(param_9,1,1);
  *(undefined1 *)(param_9 + 0x98) = 5;
  fVar1 = FLOAT_804376e4;
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  fVar2 = FLOAT_804376e8;
  *(float *)(param_9 + 0xa4) = fVar1;
  *(float *)(param_9 + 0x9c) = fVar1;
  *(float *)(param_9 + 0xa0) = fVar2;
  uVar6 = zz_0048288_(param_9);
  *(undefined2 *)(param_9 + 0x1c) = 600;
  iVar3 = zz_008ac80_(param_9,(int)(char)(&DAT_802d39b3)[iVar4]);
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar3 = zz_0006f78_(param_9);
    zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                *(int *)(param_9 + 0xe0),
                (float *)(int)(char)(&DAT_802d3ab4)[*(byte *)(param_9 + 0x95)],
                (int)*(char *)(param_9 + 0x88),iVar5,in_r8,in_r9,in_r10);
    if (*(short *)(param_9 + 0x94) == 7) {
      zz_001ac80_(param_9,4);
    }
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802d39c0 + iVar4),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802d39c0 + iVar4);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_802d39c4 + iVar4);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    *(undefined2 *)(param_9 + 0x72) = 0;
    zz_006f268_(param_9);
  }
  return;
}



// ==== 8006f268  zz_006f268_ ====

void zz_006f268_(int param_1)

{
  int iVar1;
  undefined4 auStack_28 [3];
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x1000;
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    iVar1 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar1 == 0) {
      if (*(char *)(param_1 + 0x1d9) == '\0') {
        iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x34;
        FUN_80083874((double)*(float *)(&DAT_802d39cc + iVar1),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_802d39c8 + iVar1),param_1,
                     (char)*(undefined4 *)(&DAT_802d39c4 + iVar1));
        zz_00833ec_(param_1);
        zz_0083524_(param_1);
        iVar1 = zz_0083714_(param_1);
        if (iVar1 == 0) {
          iVar1 = zz_003ecb8_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_1c,
                              auStack_28);
          if (iVar1 != 0) {
            *(float *)(param_1 + 0x20) = local_1c;
            *(undefined4 *)(param_1 + 0x24) = local_18;
            *(undefined4 *)(param_1 + 0x28) = local_14;
            FUN_8001b9ac((double)*(float *)(param_1 + 0xb4),&local_1c,auStack_28);
            zz_0019550_(param_1,&local_1c,0);
            *(undefined1 *)(param_1 + 0x18) = 2;
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x18) = 2;
          zz_008aff0_(param_1);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 8006f3ec  FUN_8006f3ec ====

void FUN_8006f3ec(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8006f428  FUN_8006f428 ====

void FUN_8006f428(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8006f448  FUN_8006f448 ====

void FUN_8006f448(int param_1)

{
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  zz_0048288_(param_1);
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_1 + 0x72) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_804376ec *
                              (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_804376f0)),
                      afStack_48,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x114));
  return;
}



// ==== 8006f4b8  FUN_8006f4b8 ====

void FUN_8006f4b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x47);
  return;
}



// ==== 8006f708  FUN_8006f708 ====

void FUN_8006f708(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 3) {
    zz_004d6dc_(param_1,2);
    zz_004d6dc_(param_1,3);
    zz_004d6dc_(param_1,4);
    zz_004d6dc_(param_1,5);
    zz_0141a40_(param_1,0);
  }
  else if (sVar1 < 3) {
    if (sVar1 == 0) {
      zz_004d6dc_(param_1,0);
      zz_004d6dc_(param_1,1);
    }
  }
  else if (sVar1 == 10) {
    zz_004d6dc_(param_1,6);
    zz_004d6dc_(param_1,7);
  }
  return;
}



// ==== 8006f7c0  FUN_8006f7c0 ====

void FUN_8006f7c0(int param_1)

{
  if (*(short *)(param_1 + 1000) == 3) {
    *(undefined1 *)(param_1 + 0x582) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0x582) = 0;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(undefined2 *)(param_1 + 0x1dfc) = 0;
    *(undefined1 *)(param_1 + 0x6ee) = 0;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x1000) == 0) {
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfffb;
  }
  *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xdf;
  if ((*(short *)(param_1 + 1000) == 3) && (*(char *)(param_1 + 0x7c8) != '\0')) {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 0x20;
    zz_004538c_((float *)(param_1 + 0x7b0),(float *)(param_1 + 0x7b0));
    gnt4_PSQUATScale_bl((double)(FLOAT_804376f8 * *(float *)(param_1 + 0xb4)),
                        (float *)(param_1 + 0x7b0),(float *)(param_1 + 0x7b0));
  }
  return;
}



// ==== 8006f8d4  FUN_8006f8d4 ====

void FUN_8006f8d4(int param_1)

{
  double dVar1;
  
  if ((*(short *)(param_1 + 1000) == 3) && (*(char *)(param_1 + 0x7c8) != '\0')) {
    *(undefined1 *)(param_1 + 0x7c8) = 1;
    dVar1 = gnt4_PSVECSquareMag_bl((float *)(param_1 + 0x7b0));
    if (dVar1 < (double)FLOAT_804376fc) {
      zz_004538c_((float *)(param_1 + 0x7b0),(float *)(param_1 + 0x7b0));
      gnt4_PSQUATScale_bl((double)FLOAT_804376f8,(float *)(param_1 + 0x7b0),
                          (float *)(param_1 + 0x7b0));
    }
  }
  return;
}



// ==== 8006f95c  FUN_8006f95c ====

void FUN_8006f95c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_802d3b54)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8006f99c  FUN_8006f99c ====

void FUN_8006f99c(int param_1,int param_2)

{
  short sVar1;
  undefined4 local_18;
  undefined2 local_14;
  
  sVar1 = *(short *)(param_1 + 1000);
  local_18 = DAT_80437700;
  local_14 = DAT_80437704;
  if (sVar1 == 0) {
    zz_0099e70_(param_1,*(undefined1 *)((int)&local_18 + param_2 * 3));
  }
  else if (sVar1 == 3) {
    zz_0099e70_(param_1,*(undefined1 *)((int)&local_18 + param_2 * 3));
    if (*(char *)(param_1 + 0x7c8) != '\0') {
      zz_0099e70_(param_1,*(undefined1 *)((int)&local_18 + param_2 * 3 + 1));
    }
  }
  else if (sVar1 == 10) {
    zz_0099e70_(param_1,*(undefined1 *)((int)&local_18 + param_2 * 3 + 2));
  }
  return;
}



// ==== 8006fa5c  FUN_8006fa5c ====

void FUN_8006fa5c(int param_1)

{
  short sVar1;
  
  *(undefined1 *)(param_1 + 0xaf) = 1;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0) {
    zz_001ab6c_(param_1,3);
  }
  else if (sVar1 == 3) {
    zz_001ab6c_(param_1,9);
  }
  else if (sVar1 == 10) {
    zz_001ab6c_(param_1,0x4c);
  }
  return;
}



// ==== 8006facc  FUN_8006facc ====

void FUN_8006facc(int param_1)

{
  (*(code *)(&PTR_FUN_802d3b68)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8006fb08  FUN_8006fb08 ====

void FUN_8006fb08(int param_1)

{
  (*(code *)(&PTR_FUN_802d3b7c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8006fb44  FUN_8006fb44 ====

void FUN_8006fb44(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_802d3ba4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8006fb8c  FUN_8006fb8c ====

void FUN_8006fb8c(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_804376e0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,1,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  zz_004beb8_((double)FLOAT_804376e0,param_1,2,2,9,0xffffffff,0xffffffff);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  zz_0070530_(param_1);
  fVar1 = FLOAT_804376e4;
  *(float *)(param_1 + 0x4c) = FLOAT_804376e4;
  *(float *)(param_1 + 0x44) = fVar1;
  return;
}



// ==== 8006fc24  FUN_8006fc24 ====

void FUN_8006fc24(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_804376e4;
  if ((iVar3 == 0) &&
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
    return;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0070558_(param_1);
  }
  return;
}



// ==== 8006fcb8  FUN_8006fcb8 ====

void FUN_8006fcb8(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(uint *)(param_1 + 0x5b4) & 0x200) == 0) {
    if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
       (*(char *)(param_1 + 0x1cee) == '\0')) {
      return;
    }
  }
  else {
    iVar1 = zz_006dbe0_(param_1,0,1,0);
    if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
        zz_006a3d0_(param_1,'\0',3,0);
        return;
      }
      zz_006bf80_(param_1);
      dVar2 = (double)FLOAT_804376e0;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
      zz_004beb8_(dVar2,param_1,1,2,1,0xffffffff,0xffffffff);
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8006fdb8  FUN_8006fdb8 ====

void FUN_8006fdb8(int param_1)

{
  (*(code *)(&PTR_FUN_802d3bb0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8006fdf4  FUN_8006fdf4 ====

void FUN_8006fdf4(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_804376e0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar1,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,0xffffffff);
  zz_0070530_(param_1);
  return;
}



// ==== 8006fe54  FUN_8006fe54 ====

void FUN_8006fe54(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_804376e4;
  if (iVar3 < 0) {
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else {
    if ((iVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if (*(char *)(param_1 + 0x1cef) != '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_0070558_(param_1);
    }
  }
  return;
}



// ==== 8006ff00  FUN_8006ff00 ====

void FUN_8006ff00(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  if ((*(uint *)(param_9 + 0x5b4) & 0x200) == 0) {
    if ((*(ushort *)(param_9 + 0x5d8) & 0xf0) != 0) goto LAB_8006fff0;
  }
  else {
    param_11 = 1;
    param_12 = 0;
    iVar1 = zz_006dbe0_(param_9,0,1,0);
    if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
      if (((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
        if ((*(uint *)(param_9 + 0x5e0) & 0x10) != 0) {
          zz_006bf80_(param_9);
          dVar2 = (double)FLOAT_804376e0;
          *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
          zz_004beb8_(dVar2,param_9,1,2,7,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      zz_006a3d0_(param_9,'\0',3,2);
      return;
    }
  }
  if (*(char *)(param_9 + 0x1cee) == '\0') {
    return;
  }
LAB_8006fff0:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80070024  FUN_80070024 ====

void FUN_80070024(int param_1)

{
  (*(code *)(&PTR_FUN_802d3bbc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80070060  FUN_80070060 ====

void FUN_80070060(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_804376e0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar1,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,0xffffffff);
  if ((*(uint *)(param_1 + 0x5e0) & 0x80) != 0) {
    zz_006a5a4_(param_1);
    zz_004beb8_((double)FLOAT_804376e0,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  zz_0070530_(param_1);
  return;
}



// ==== 800700f4  FUN_800700f4 ====

void FUN_800700f4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_804376e4;
  if ((iVar3 < 1) &&
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
    return;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0070558_(param_1);
  }
  return;
}



// ==== 80070188  FUN_80070188 ====

void FUN_80070188(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  zz_004cd24_(param_9,1);
  if ((*(uint *)(param_9 + 0x5b4) & 0x200) == 0) {
    if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
      return;
    }
  }
  else {
    param_11 = 1;
    param_12 = 0;
    iVar1 = zz_006dbe0_(param_9,0,1,0);
    if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
      zz_006bf80_(param_9);
      *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
      if ((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) {
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      zz_004beb8_((double)FLOAT_804376e0,param_9,1,2,7,0xffffffff,0xffffffff);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80070280  FUN_80070280 ====

void FUN_80070280(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_802d3bc8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800702c8  FUN_800702c8 ====

void FUN_800702c8(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_804376e8;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804376e0,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_804376e0,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  zz_0070530_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804376e4;
  return;
}



// ==== 8007039c  FUN_8007039c ====

void FUN_8007039c(int param_1)

{
  zz_006d0dc_(param_1,0x81,0);
  FUN_80067310((double)FLOAT_804376e8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0070558_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80070430  FUN_80070430 ====

void FUN_80070430(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  if ((*(uint *)(param_9 + 0x5b4) & 0x200) == 0) {
    if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
      return;
    }
  }
  else {
    param_11 = 1;
    param_12 = 0;
    iVar1 = zz_006dbe0_(param_9,0,1,0);
    if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
      if ((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) {
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      zz_006bf80_(param_9);
      dVar2 = (double)FLOAT_804376e0;
      *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
      *(undefined1 *)(param_9 + 0x581) = 3;
      zz_004beb8_(dVar2,param_9,1,2,7,0xffffffff,0xffffffff);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80070530  zz_0070530_ ====

void zz_0070530_(int param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x6ee) == '\0') {
    *(undefined1 *)(param_1 + 0x6ef) = 5;
  }
  fVar1 = FLOAT_80437708;
  *(undefined1 *)(param_1 + 0x6ee) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  return;
}



// ==== 80070558  zz_0070558_ ====

void zz_0070558_(int param_1)

{
  int iVar1;
  
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    if (*(short *)(param_1 + 1000) == 10) {
      zz_006ee14_(param_1,4);
    }
    else if (*(short *)(param_1 + 1000) == 3) {
      zz_006ee14_(param_1,0);
      if (*(char *)(param_1 + 0x7c8) != '\0') {
        zz_006ee14_(param_1,2);
      }
    }
    else {
      zz_006ee14_(param_1,0);
    }
  }
  return;
}



// ==== 80070604  FUN_80070604 ====

void FUN_80070604(int param_1)

{
  if (*(short *)(param_1 + 1000) == 10) {
    (*(code *)(&PTR_FUN_802d3be8)[*(char *)(param_1 + 0x581)])();
  }
  else {
    (*(code *)(&PTR_FUN_802d3bd4)[*(char *)(param_1 + 0x581)])();
  }
  return;
}



// ==== 80070670  FUN_80070670 ====

void FUN_80070670(int param_1)

{
  zz_00fed6c_(param_1);
  return;
}



// ==== 80070698  zz_0070698_ ====

void zz_0070698_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_00706e8__802d3c14)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800706e8  zz_00706e8_ ====

void zz_00706e8_(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_8043770c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar1 = FLOAT_804376e4;
  *(float *)(param_1 + 0x50) = FLOAT_804376e4;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  zz_00707b8_(param_1);
  return;
}



// ==== 800707b8  zz_00707b8_ ====

void zz_00707b8_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  double dVar6;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80437710,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804376e4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar5 = zz_006d144_(param_1,0xc0), iVar5 != 0)) {
    fVar1 = FLOAT_80437708;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x48) = FLOAT_80437718;
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / fVar1;
    }
    else {
      iVar5 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
      local_1c = *(float *)(iVar5 + 0x8e0);
      local_18 = *(float *)(iVar5 + 0x8f0);
      local_14 = *(undefined4 *)(iVar5 + 0x900);
      local_28 = *(float *)(param_1 + 0x518);
      local_20 = *(undefined4 *)(param_1 + 0x520);
      local_24 = FLOAT_80437714 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
      gnt4_PSVECSubtract_bl(&local_28,&local_1c,&local_1c);
      fVar1 = FLOAT_804376e4;
      *(float *)(param_1 + 0x48) = local_18 / FLOAT_80437708;
      local_18 = fVar1;
      dVar6 = gnt4_PSVECMag_bl(&local_1c);
      *(float *)(param_1 + 0x44) = (float)(dVar6 / (double)FLOAT_80437708);
    }
    fVar4 = FLOAT_8043772c;
    fVar3 = FLOAT_80437728;
    fVar2 = FLOAT_80437708;
    fVar1 = FLOAT_804376e4;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_80437720);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar3 * (-*(float *)(param_1 + 0x48) / fVar2);
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x44);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x50);
    if (fVar4 < *(float *)(param_1 + 0x760)) {
      zz_0092dcc_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_804376e0,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800709b8  zz_00709b8_ ====

void zz_00709b8_(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_804376e8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(float *)(param_1 + 0x48) < FLOAT_80437728) {
    dVar1 = (double)FLOAT_804376e0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar1,param_1,0xf,3,6,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80070a48  zz_0070a48_ ====

void zz_0070a48_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  fVar1 = FLOAT_80437730;
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) = (float)(DOUBLE_80437738 * (double)*(float *)(param_1 + 0x38));
    }
    else {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / FLOAT_80437708;
    }
    *(float *)(param_1 + 0x48) = FLOAT_80437740;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 80070aec  zz_0070aec_ ====

void zz_0070aec_(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  uVar2 = FUN_80066838((double)FLOAT_804376f8,param_1);
  fVar1 = FLOAT_804376e4;
  if (0 < (int)uVar2) {
    *(float *)(param_1 + 0x4c) = FLOAT_804376e4;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_006eddc_((double)FLOAT_80437744,param_1,(float *)(param_1 + 0x44));
  FUN_80067310((double)FLOAT_804376e8,param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = FLOAT_804376e4;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (fVar1 <= *(float *)(param_1 + 0x558)) {
    iVar3 = zz_00677b0_(param_1);
    fVar1 = FLOAT_80437748;
    if (iVar3 != 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar1;
      zz_0066530_(param_1,0x2c);
      zz_004beb8_((double)FLOAT_804376e0,param_1,0xf,3,7,0xffffffff,0xffffffff);
      zz_00b2190_(param_1,2);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80070c04  zz_0070c04_ ====

void zz_0070c04_(int param_1)

{
  if (*(float *)(param_1 + 0x558) <= FLOAT_804376e4) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80070c7c  zz_0070c7c_ ====

void zz_0070c7c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_0070ccc__802d3c2c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80070ccc  zz_0070ccc_ ====

void zz_0070ccc_(int param_1)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043770c;
  zz_006d144_(param_1,0xc0);
  fVar1 = FLOAT_804376e4;
  *(float *)(param_1 + 0x50) = FLOAT_804376e4;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80437710,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804376e0,param_1,0xf,3,3,0xffffffff,0xffffffff);
  return;
}



// ==== 80070de4  zz_0070de4_ ====

void zz_0070de4_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80437710,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804376e4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_80437708;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_804376f8;
    fVar2 = FLOAT_804376e4;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80437708;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    *(float *)(param_1 + 0x80c) = FLOAT_804376e4;
  }
  return;
}



// ==== 80070f18  zz_0070f18_ ====

void zz_0070f18_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_804376e4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_804376f8,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_8043774c;
    dVar4 = (double)FLOAT_804376e0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0xff;
    *(float *)(param_1 + 0x558) = fVar1;
    zz_004beb8_(dVar4,param_1,0xf,3,4,0xffffffff,0xffffffff);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80070fd8  zz_0070fd8_ ====

void zz_0070fd8_(int param_1)

{
  double dVar1;
  float fVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 4;
  }
  fVar2 = FLOAT_80437750;
  dVar1 = DOUBLE_804376f0;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    if (FLOAT_804376e4 < *(float *)(param_1 + 0x558)) {
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      *(short *)(param_1 + 0x72) =
           (short)(int)(fVar2 * *(float *)(param_1 + 0x1dc8) +
                       (float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(param_1 + 0x72) ^ 0x80000000) -
                              dVar1));
    }
  }
  zz_006ed8c_((double)FLOAT_80437754,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfffb;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800710d8  zz_00710d8_ ====

void zz_00710d8_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_0071128__802d3c3c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80071128  zz_0071128_ ====

void zz_0071128_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  double dVar6;
  
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    iVar5 = FUN_800667a0(param_1);
    if ((float)((double)CONCAT44(0x43300000,(int)(short)iVar5 ^ 0x80000000) - DOUBLE_804376f0) <
        FLOAT_80437758) {
      *(undefined1 *)(param_1 + 0x581) = 4;
      zz_0070698_(param_1);
      return;
    }
  }
  fVar3 = FLOAT_8043774c;
  fVar2 = FLOAT_804376e4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(float *)(param_1 + 0x558) = fVar3;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  zz_0092dcc_(param_1,0);
  *(undefined1 *)(param_1 + 0x6ea) = 8;
  if (*(short *)(param_1 + 1000) == 10) {
    *(undefined1 *)(param_1 + 0x6ea) = 9;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar6 = (double)FLOAT_804376e0;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar6,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80071288  zz_0071288_ ====

void zz_0071288_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  zz_006d144_(param_1,0xc0);
  iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
  local_18 = *(float *)(iVar4 + 0x8e0);
  local_14 = *(undefined4 *)(iVar4 + 0x8f0);
  local_10 = *(undefined4 *)(iVar4 + 0x900);
  gnt4_PSVECSubtract_bl(&local_18,(float *)(param_1 + 0x518),&local_18);
  zz_006ec1c_(&local_18,&local_18);
  gnt4_PSQUATScale_bl((double)(FLOAT_8043775c * *(float *)(param_1 + 0xb4)),&local_18,&local_18);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x518),&local_18,&local_18);
  zz_006e6c4_(param_1,0xc0,(short *)(param_1 + 0x54e),&local_18);
  dVar5 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80437708 * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar6 = (double)FLOAT_804376e8;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80437708 * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804376e4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_80437760,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_80437730;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 800713e0  zz_00713e0_ ====

void zz_00713e0_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_804376e4;
  if ((*(short *)(param_1 + 1000) == 10) && ((*(byte *)(param_1 + 0x1d9) & 0x30) != 0)) {
    *(float *)(param_1 + 0x44) = FLOAT_80437764;
    fVar1 = FLOAT_8043774c;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x745) = 1;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
    *(undefined1 *)(param_1 + 0x1d10) = 0;
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  fVar2 = FLOAT_804376e4;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar2 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar2;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_80437744,param_1);
  FUN_80067310((double)FLOAT_804376e8,param_1,*(short *)(param_1 + 0x5ac));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_804376e4;
  if ((iVar3 == 0) || (-1 < *(char *)(param_1 + 0x1cef))) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) {
      if (*(char *)(param_1 + 0x745) != '\0') {
        return;
      }
      if (*(char *)(param_1 + 0x1cee) == '\0') {
        return;
      }
    }
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_804376e8 + *(float *)(param_1 + 0x1dc8);
  }
  else {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804376e8 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80071598  zz_0071598_ ====

void zz_0071598_(int param_1)

{
  (*(code *)(&PTR_zz_00715d4__802d3c48)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800715d4  zz_00715d4_ ====

void zz_00715d4_(int param_1)

{
  zz_00ff2bc_(param_1);
  return;
}



// ==== 800715f8  zz_00715f8_ ====

void zz_00715f8_(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  
  fVar5 = FLOAT_80437768;
  fVar4 = FLOAT_80437748;
  fVar3 = FLOAT_804376e4;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    fVar2 = FLOAT_804376e0;
    *(float *)(param_1 + 0x44) = fVar4;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x48) = fVar5;
    *(float *)(param_1 + 0x50) = fVar2;
  }
  iVar6 = zz_006dbe0_(param_1,2,1,1);
  if (iVar6 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0) {
      zz_007db5c_(param_1,0);
    }
    else if (sVar1 == 3) {
      zz_007db5c_(param_1,1);
      if (*(char *)(param_1 + 0x7c8) != '\0') {
        zz_007db5c_(param_1,2);
      }
    }
    else if (sVar1 == 10) {
      zz_007db5c_(param_1,3);
    }
  }
  return;
}



// ==== 800716d8  zz_00716d8_ ====

void zz_00716d8_(int param_1)

{
  (*(code *)(&PTR_zz_0071714__802d3c5c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80071714  zz_0071714_ ====

void zz_0071714_(int param_1)

{
  (*(code *)(&PTR_zz_0071750__802d3c70)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80071750  zz_0071750_ ====

void zz_0071750_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_80437768;
  fVar1 = FLOAT_804376e4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  if (*(char *)(param_1 + 0x7c8) == '\x01') {
    *(undefined1 *)(param_1 + 0x7c8) = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x7c8) = 0;
    *(float *)(param_1 + 0x7b0) = fVar1;
    *(float *)(param_1 + 0x7b4) = fVar1;
    *(float *)(param_1 + 0x7b8) = fVar1;
  }
  fVar1 = FLOAT_804376e4;
  *(float *)(param_1 + 0x50) = FLOAT_804376e4;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80437744,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  iVar3 = 2;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    iVar3 = 3;
  }
  zz_004beb8_((double)FLOAT_804376e0,param_1,0xf,4,iVar3,0xffffffff,0xffffffff);
  zz_0071858_(param_1);
  return;
}



// ==== 80071858  zz_0071858_ ====

void zz_0071858_(int param_1)

{
  float fVar1;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043776c,(float *)(param_1 + 0x7b0),(float *)(param_1 + 0x7b0));
  gnt4_PSQUATScale_bl((double)FLOAT_80437744,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if (FLOAT_804376e4 == *(float *)(param_1 + 0x560)) {
      *(float *)(param_1 + 0x560) = FLOAT_80437748;
      FUN_800061a8(param_1,5);
    }
    fVar1 = FLOAT_804376e4;
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    if (*(float *)(param_1 + 0x560) <= fVar1) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x7c8) = 0;
      *(float *)(param_1 + 0x7b0) = fVar1;
      *(float *)(param_1 + 0x7b4) = fVar1;
      *(float *)(param_1 + 0x7b8) = fVar1;
    }
  }
  return;
}



// ==== 80071938  zz_0071938_ ====

void zz_0071938_(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80437744,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  fVar2 = FLOAT_804376f8;
  fVar1 = FLOAT_804376e4;
  if (*(float *)(param_1 + 0x558) <= FLOAT_804376e4) {
    *(undefined1 *)(param_1 + 0x7c8) = 1;
    *(float *)(param_1 + 0x55c) = fVar2;
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
        zz_006a5a4_(param_1);
        return;
      }
      zz_006a474_(param_1);
      return;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (*(float *)(param_1 + 0x558) <= fVar1) {
      *(float *)(param_1 + 0x558) = fVar1;
      zz_004cff4_(param_1,0xf);
    }
    fVar1 = FLOAT_80437768;
    *(undefined1 *)(param_1 + 0x7c8) = 2;
    dVar3 = zz_0045238_((short)(int)(FLOAT_80437770 * (*(float *)(param_1 + 0x558) / fVar1)));
    *(float *)(param_1 + 0x55c) = (float)((double)FLOAT_804376f8 * dVar3);
  }
  *(undefined4 *)(param_1 + 0x7b0) = *(undefined4 *)(param_1 + 0x8d4);
  *(undefined4 *)(param_1 + 0x7b4) = *(undefined4 *)(param_1 + 0x8e4);
  *(undefined4 *)(param_1 + 0x7b8) = *(undefined4 *)(param_1 + 0x8f4);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x55c),(float *)(param_1 + 0x7b0),
                      (float *)(param_1 + 0x7b0));
  return;
}



// ==== 80071a84  zz_0071a84_ ====

void zz_0071a84_(int param_1)

{
  (*(code *)(&PTR_zz_0071ac0__802d3c7c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80071ac0  zz_0071ac0_ ====

void zz_0071ac0_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_0071b10__802d3c90)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80071b10  zz_0071b10_ ====

void zz_0071b10_(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_804376e4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x564) = fVar1;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if ((*(int *)(param_1 + 0xcc) == 0) &&
     (*(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72),
     (*(uint *)(param_1 + 0x5e0) & 0x20) != 0)) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  fVar1 = FLOAT_804376e4;
  *(float *)(param_1 + 0x50) = FLOAT_804376e4;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80437744,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804376e0,param_1,0xf,4,4,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804376e4;
  return;
}



// ==== 80071c50  zz_0071c50_ ====

void zz_0071c50_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80437744,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804376e4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043774c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar2 = FLOAT_804376e4;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043774c;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00b2190_(param_1,0);
  }
  return;
}



