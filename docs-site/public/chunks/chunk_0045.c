// ==== 8017bc34  FUN_8017bc34 ====

void FUN_8017bc34(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar2 = DAT_80436354;
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x02') {
    iVar2 = zz_0027adc_();
    if (iVar2 == 0) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      *(undefined2 *)(DAT_80436354 + 8) = 0;
      *(undefined **)(DAT_80436354 + 0xa28) = &DAT_80352e20;
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(DAT_80436354 + 2) = 1;
      zz_0181cac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,iVar2,param_11,
                  param_12,param_13,param_14,param_15,param_16);
    }
    else if ((-1 < cVar1) && (iVar2 = zz_000a3c4_(), iVar2 == 0)) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      zz_01e3c04_();
      gnt4_memset((void *)(DAT_80436354 + 0xa0c),0,8);
      uVar3 = zz_0027aac_(0,0x40,0);
      zz_00e99c8_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a0e4,
                  param_12,param_13,param_14,param_15,param_16);
    }
  }
  else if (cVar1 == '\x04') {
    iVar2 = zz_0027adc_();
    if (iVar2 == 0) {
      *(undefined1 *)(DAT_80436354 + 1) = 3;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
      gnt4_memset((void *)(DAT_80436354 + 0xa0c),0,8);
      zz_0181c78_();
      glxSwapWaitDrawDone_void_();
      zz_007fd5c_();
    }
  }
  else if ((cVar1 < '\x04') &&
          ((iVar2 = zz_017bb7c_(), iVar2 != 0 || ((*(uint *)(DAT_80436354 + 0x18) & 0x1000) != 0))))
  {
    *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    zz_0027aac_(0,0x40,1);
    zz_00e9b60_((double)FLOAT_8043ae50,2,0x40,2);
    zz_00e9b60_((double)FLOAT_8043ae50,0,0x40,2);
    zz_00e9b60_((double)FLOAT_8043ae50,1,0x40,2);
  }
  zz_0181dd8_();
  return;
}



// ==== 8017be34  FUN_8017be34 ====

void FUN_8017be34(void)

{
  (*(code *)(&PTR_FUN_80352e64)[*(char *)(DAT_80436354 + 1)])();
  zz_0181dd8_();
  return;
}



// ==== 8017be78  FUN_8017be78 ====

void FUN_8017be78(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 extraout_r4;
  undefined8 uVar4;
  undefined8 extraout_f1;
  
  iVar2 = DAT_80436354;
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    uVar4 = zz_0181cac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,iVar2,
                        param_11,param_12,param_13,param_14,param_15,param_16);
    iVar2 = *(int *)(DAT_80436354 + 0x44);
    if (iVar2 != 2) {
      if (iVar2 < 2) {
        if (0 < iVar2) {
          zz_0181d2c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436354,
                      extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
        }
      }
      else if (iVar2 < 5) {
        uVar4 = zz_0181d2c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            DAT_80436354,extraout_r4,param_11,param_12,param_13,param_14,param_15,
                            param_16);
        zz_0181d60_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    (int)((ulonglong)uVar4 >> 0x20),(int)uVar4,param_11,param_12,param_13,param_14,
                    param_15,param_16);
      }
    }
  }
  iVar2 = zz_000a3c4_();
  if (iVar2 == 0) {
    zz_01a71b0_();
    *(undefined4 *)(DAT_80436354 + 0x9f0) = 0;
    *(undefined1 *)(DAT_80436354 + 0xa0c) = 0xff;
    iVar2 = *(int *)(DAT_80436354 + 0x44);
    if (iVar2 == 2) {
      *(undefined1 *)(DAT_80436354 + 1) = 9;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
      *(undefined4 *)(DAT_80436354 + 0x128) = 2;
      *(undefined4 *)(DAT_80436354 + 0x7c) = 0;
      *(undefined4 *)(DAT_80436354 + 300) = 0;
    }
    else if (iVar2 < 2) {
      if (iVar2 == 0) {
        *(undefined1 *)(DAT_80436354 + 1) = 1;
        *(undefined1 *)(DAT_80436354 + 2) = 0;
        *(undefined4 *)(DAT_80436354 + 0x128) = 0;
        *(undefined4 *)(DAT_80436354 + 0x7c) = 1;
        *(undefined4 *)(DAT_80436354 + 300) = 0;
        *(undefined1 *)(DAT_80436354 + 0xa0c) = 0;
      }
      else if (-1 < iVar2) {
        *(undefined1 *)(DAT_80436354 + 1) = 5;
        *(undefined1 *)(DAT_80436354 + 2) = 0;
        *(undefined4 *)(DAT_80436354 + 0x5c) = 0;
        *(undefined4 *)(DAT_80436354 + 0x128) = 2;
        *(undefined4 *)(DAT_80436354 + 0x7c) = 0;
        *(undefined4 *)(DAT_80436354 + 300) = 1;
        *(undefined4 *)(DAT_80436354 + 0x9cc) = 2;
        *(undefined4 *)(DAT_80436354 + 0xc4) = 0;
        *(undefined4 *)(DAT_80436354 + 0x9c8) = 1;
        *(undefined ***)(DAT_80436354 + 0x9ec) = &PTR_DAT_80358c00;
        zz_017e138_();
        zz_017e4f0_();
        zz_01a9f18_();
      }
    }
    else if (iVar2 == 4) {
      *(undefined1 *)(DAT_80436354 + 1) = 7;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
      *(undefined4 *)(DAT_80436354 + 0x128) = 2;
      *(undefined4 *)(DAT_80436354 + 0x7c) = 2;
      *(undefined4 *)(DAT_80436354 + 300) = 1;
      *(undefined4 *)(DAT_80436354 + 0x9cc) = 2;
      *(undefined4 *)(DAT_80436354 + 0x9f0) = 2;
      *(undefined1 *)(DAT_80436354 + 0xa0c) = 0;
      zz_01a9f18_();
      uVar4 = zz_01aa900_();
      zz_00439a0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3);
      zz_01aba28_();
    }
    else if (iVar2 < 4) {
      *(undefined1 *)(DAT_80436354 + 1) = 6;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
      *(undefined4 *)(DAT_80436354 + 0x128) = 2;
      *(undefined4 *)(DAT_80436354 + 0x7c) = 2;
      *(undefined4 *)(DAT_80436354 + 300) = 1;
      *(undefined4 *)(DAT_80436354 + 0x9cc) = 2;
      *(undefined4 *)(DAT_80436354 + 0x9f0) = 0;
      *(undefined1 *)(DAT_80436354 + 0xa0c) = 0;
      zz_01a9f18_();
      zz_01aa900_();
    }
    uVar3 = zz_0181ab4_();
    if ((uVar3 & 1 << *(int *)(DAT_80436354 + 0x118)) == 0) {
      *(undefined4 *)(DAT_80436354 + 0x120) = 10;
      *(undefined4 *)(DAT_80436354 + 0x11c) = 10;
      *(undefined4 *)(DAT_80436354 + 0x118) = 10;
    }
    *(undefined4 *)(DAT_80436354 + 0x44) = 0;
    zz_0027aac_(0,0x20,0);
  }
  return;
}



// ==== 8017c138  FUN_8017c138 ====

void FUN_8017c138(void)

{
  if (*(char *)(DAT_80436354 + 2) == '\0') {
    zz_017e138_();
    zz_017e4f0_();
    if (*(int *)(DAT_80436354 + 0x9e0) == 0) {
      *(undefined1 *)(DAT_80436354 + 1) = 2;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
      *(undefined4 *)(DAT_80436354 + 0x5c) = *(undefined4 *)(DAT_80436354 + 0x58);
      *(undefined4 *)(DAT_80436354 + 0x7c) = 1;
    }
    else {
      *(undefined1 *)(DAT_80436354 + 1) = 3;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
    }
  }
  return;
}



// ==== 8017c1c4  FUN_8017c1c4 ====

void FUN_8017c1c4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0x128) != 1) {
      *(undefined1 *)(DAT_80436354 + 1) = 3;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
      *(undefined4 *)(DAT_80436354 + 0x9e0) = *(undefined4 *)(DAT_80436354 + 0x9e4);
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if (*(int *)(DAT_80436354 + 0x128) == 0) {
        *(undefined1 *)(DAT_80436354 + 2) = 1;
        *(undefined4 *)(DAT_80436354 + 0x9d0) = 0;
        *(undefined4 *)(DAT_80436354 + 0x9d4) = 0;
      }
    }
    else if (-1 < cVar1) {
      uVar2 = *(uint *)(DAT_80436354 + 0x18);
      if ((uVar2 & 0x100) == 0) {
        if ((uVar2 & 0x1000) == 0) {
          if (((uVar2 & 0x400) == 0) || (iVar3 = zz_0181c70_(), iVar3 == 0)) {
            uVar2 = zz_0181ab4_();
            puVar7 = &DAT_80352e90;
            iVar3 = 0;
            iVar10 = 4;
            do {
              if ((*(uint *)(DAT_80436354 + 0x18) & *puVar7) != 0) {
                iVar5 = (int)(char)(&DAT_8035b21c)[iVar3 + *(int *)(DAT_80436354 + 0x118) * 8];
                iVar9 = iVar5;
                if ((iVar5 == *(int *)(DAT_80436354 + 0x11c)) ||
                   (iVar6 = (int)(char)(&DAT_8035b21c)
                                       [iVar3 + *(int *)(DAT_80436354 + 0x118) * 8 + 4],
                   iVar9 = iVar6, iVar6 == *(int *)(DAT_80436354 + 0x11c))) {
LAB_8017c418:
                  *(undefined4 *)(DAT_80436354 + 0x11c) = *(undefined4 *)(DAT_80436354 + 0x118);
                  *(int *)(DAT_80436354 + 0x118) = iVar9;
                  zz_0181814_();
                  return;
                }
                uVar8 = 0;
                if (((iVar5 < 0) ||
                    ((iVar5 == *(int *)(DAT_80436354 + 0x118) ||
                     (iVar9 = iVar5, (uVar2 & 1 << iVar5) == 0)))) &&
                   ((uVar8 = 1, iVar6 < 0 ||
                    ((iVar6 == *(int *)(DAT_80436354 + 0x118) ||
                     (iVar9 = iVar6, (uVar2 & 1 << iVar6) == 0)))))) {
                  uVar8 = 2;
                  iVar9 = iVar6;
                }
                if (uVar8 < 2) goto LAB_8017c418;
              }
              puVar7 = puVar7 + 1;
              iVar3 = iVar3 + 1;
              iVar10 = iVar10 + -1;
            } while (iVar10 != 0);
          }
          else {
            *(undefined1 *)(DAT_80436354 + 1) = 8;
            *(undefined1 *)(DAT_80436354 + 2) = 0;
            *(undefined2 *)(DAT_80436354 + 10) = 0;
            *(undefined1 *)(DAT_80436354 + 7) = 4;
            *(undefined1 *)(DAT_80436354 + 6) = 3;
            uVar4 = zz_0181c30_();
            *(undefined4 *)(PTR_DAT_80433934 + 0x120) = uVar4;
            zz_018183c_();
          }
        }
        else {
          *(undefined1 *)(DAT_80436354 + 1) = 10;
          *(undefined1 *)(DAT_80436354 + 2) = 0;
          zz_018183c_();
        }
      }
      else {
        if ((*(int *)(DAT_80436354 + 0x9e4) == 0) ||
           (*(int *)(DAT_80436354 + 0x9e8) != *(int *)(DAT_80436354 + 0x118))) {
          iVar3 = DAT_80436354 + *(int *)(DAT_80436354 + 0x118);
          if (*(char *)(iVar3 + 0x574) == '\0') {
            zz_018188c_();
            return;
          }
          zz_0181d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                      DAT_80436354,param_11,param_12,param_13,param_14,param_15,param_16);
          *(undefined1 *)(DAT_80436354 + 2) = 3;
        }
        else {
          *(undefined1 *)(DAT_80436354 + 2) = 2;
        }
        *(undefined4 *)(DAT_80436354 + 0x128) = 1;
        *(undefined4 *)(DAT_80436354 + 0x7c) = 0;
        *(undefined4 *)(DAT_80436354 + 0x120) = *(undefined4 *)(DAT_80436354 + 0x118);
        zz_018183c_();
      }
    }
  }
  else if (((cVar1 < '\x04') && (iVar3 = zz_000a3c4_(), iVar3 == 0)) &&
          (*(int *)(DAT_80436354 + 0x128) != 1)) {
    *(undefined1 *)(DAT_80436354 + 1) = 4;
    *(undefined1 *)(DAT_80436354 + 2) = 0;
    *(undefined4 *)(DAT_80436354 + 0x7c) = 2;
    *(undefined4 *)(DAT_80436354 + 0x9cc) = 0;
    zz_017e138_();
    zz_017e4f0_();
    zz_01a9f18_();
  }
  return;
}



// ==== 8017c4d4  FUN_8017c4d4 ====

void FUN_8017c4d4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar3;
  int iVar2;
  int iVar4;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  iVar4 = *(int *)(DAT_80436354 + 0x9e0);
  if (cVar1 == '\x03') {
    iVar2 = zz_017ca3c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    if (iVar2 == 0) {
      zz_017f4c4_(iVar4);
      zz_017ea70_();
      zz_017e5a0_();
      zz_017ee94_(0);
      if ((*(int *)(DAT_80436354 + 0x9e0) == 0) ||
         (*(int *)(&DAT_8035ac58 + *(int *)(DAT_80436354 + 0x9e0) * 0xc) != 0)) {
        *(undefined1 *)(DAT_80436354 + 1) = 1;
        *(undefined1 *)(DAT_80436354 + 2) = 0;
        if (*(int *)(DAT_80436354 + 0x128) == 2) {
          *(undefined4 *)(DAT_80436354 + 0x128) = 3;
        }
      }
      else {
        *(undefined1 *)(DAT_80436354 + 2) = 0;
      }
    }
  }
  else if (cVar1 < '\x03') {
    if (cVar1 != '\x01') {
      if ('\0' < cVar1) {
        sVar3 = *(short *)(DAT_80436354 + 8) + -1;
        *(short *)(DAT_80436354 + 8) = sVar3;
        if (0 < sVar3) {
          return;
        }
        *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
        return;
      }
      if (cVar1 < '\0') {
        return;
      }
      if ((*(uint *)(DAT_80436354 + 0x128) & 1) != 0) {
        return;
      }
      *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
      *(undefined1 *)(DAT_80436354 + 4) = 0;
      *(undefined **)(DAT_80436354 + 0xa28) = (&PTR_DAT_8035ac5c)[iVar4 * 3];
    }
    iVar4 = zz_017c7e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    if (iVar4 != 1) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      *(undefined2 *)(DAT_80436354 + 8) = 4;
      zz_01ac34c_();
    }
  }
  else if (cVar1 == '(') {
    zz_017d18c_();
  }
  else if (((cVar1 < '(') && (cVar1 == '\x14')) &&
          (iVar4 = zz_017cfec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x14,
                               DAT_80436354,param_11,param_12,param_13,param_14,param_15,param_16),
          iVar4 == 0)) {
    *(undefined1 *)(DAT_80436354 + 2) = 3;
  }
  return;
}



// ==== 8017c684  zz_017c684_ ====

int zz_017c684_(int param_1)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  
  if ((param_1 != 0xe) && (param_1 != 0x11)) {
    return param_1;
  }
  iVar3 = 0x14;
  iVar1 = DAT_80436220;
  do {
    if (((((((*(short *)(iVar1 + 0x870) == 0x629) || (*(short *)(iVar1 + 0x890) == 0x629)) ||
           (*(short *)(iVar1 + 0x8b0) == 0x629)) ||
          ((*(short *)(iVar1 + 0x8d0) == 0x629 || (*(short *)(iVar1 + 0x8f0) == 0x629)))) ||
         ((*(short *)(iVar1 + 0x910) == 0x629 ||
          ((*(short *)(iVar1 + 0x930) == 0x629 || (*(short *)(iVar1 + 0x950) == 0x629)))))) ||
        (*(short *)(iVar1 + 0x970) == 0x629)) || (*(short *)(iVar1 + 0x990) == 0x629))
    goto LAB_8017c7c4;
    iVar1 = iVar1 + 0x140;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar1 = 200;
  psVar2 = DAT_80436224;
  while (((((*psVar2 != 0x629 && (psVar2[8] != 0x629)) && (psVar2[0x10] != 0x629)) &&
          (((psVar2[0x18] != 0x629 && (psVar2[0x20] != 0x629)) &&
           ((psVar2[0x28] != 0x629 && ((psVar2[0x30] != 0x629 && (psVar2[0x38] != 0x629)))))))) &&
         ((psVar2[0x40] != 0x629 && (psVar2[0x48] != 0x629))))) {
    psVar2 = psVar2 + 0x50;
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) {
      return param_1;
    }
  }
LAB_8017c7c4:
  if (param_1 == 0xe) {
    param_1 = 0x2c;
  }
  if (param_1 != 0x11) {
    return param_1;
  }
  return 0x2d;
}



// ==== 8017c7e0  zz_017c7e0_ ====

undefined4
zz_017c7e0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  ushort *puVar7;
  int iVar8;
  
  cVar1 = *(char *)(DAT_80436354 + 4);
  if (cVar1 == '\x02') {
LAB_8017c94c:
    iVar8 = zz_000a3c4_();
    if (iVar8 != 0) {
      return 1;
    }
    uVar5 = 1;
    *(undefined1 *)(DAT_80436354 + 4) = 1;
LAB_8017c984:
    if ((-1 < (char)*(byte *)(DAT_80436354 + 0xa10)) &&
       ((*(byte *)(DAT_80436354 + 0xa10) & 0x40) != 0)) {
      *(byte *)(DAT_80436354 + 0xa10) = *(byte *)(DAT_80436354 + 0xa10) & 0xbf;
    }
    if ((-1 < (char)*(byte *)(DAT_80436354 + 0xa11)) &&
       ((*(byte *)(DAT_80436354 + 0xa11) & 0x40) != 0)) {
      *(byte *)(DAT_80436354 + 0xa11) = *(byte *)(DAT_80436354 + 0xa11) & 0xbf;
    }
    if ((-1 < (char)*(byte *)(DAT_80436354 + 0xa12)) &&
       ((*(byte *)(DAT_80436354 + 0xa12) & 0x40) != 0)) {
      *(byte *)(DAT_80436354 + 0xa12) = *(byte *)(DAT_80436354 + 0xa12) & 0xbf;
    }
    if ((-1 < (char)*(byte *)(DAT_80436354 + 0xa13)) &&
       ((*(byte *)(DAT_80436354 + 0xa13) & 0x40) != 0)) {
      *(byte *)(DAT_80436354 + 0xa13) = *(byte *)(DAT_80436354 + 0xa13) & 0xbf;
    }
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(DAT_80436354 + 4) = 1;
        *(undefined4 *)(DAT_80436354 + 0xa04) = 0;
        *(undefined4 *)(DAT_80436354 + 0xa2c) = *(undefined4 *)(DAT_80436354 + 0xa28);
        gnt4_memset((void *)(DAT_80436354 + 0xa10),0xff,4);
      }
      else if (cVar1 < '\0') goto LAB_8017ca20;
      iVar8 = 0;
      puVar7 = *(ushort **)(DAT_80436354 + 0xa2c);
      do {
        if (*(char *)(DAT_80436354 + iVar8 + 0xa10) < '\0') {
          do {
            while( true ) {
              uVar3 = *puVar7 & 0xff;
              if (uVar3 == 0x2e) {
                *(undefined1 *)(DAT_80436354 + 4) = 3;
                *(undefined4 *)(DAT_80436354 + 0xa2c) = 0;
                goto LAB_8017c974;
              }
              if ((uVar3 < 0x2e) && (uVar3 == 0x18)) break;
              puVar7 = puVar7 + 1 + ((int)(uint)*puVar7 >> 8);
              *(ushort **)(DAT_80436354 + 0xa2c) = puVar7;
            }
            uVar3 = puVar7[1];
            uVar2 = puVar7[2];
            puVar7 = puVar7 + 3;
            *(uint *)(DAT_80436354 + 0xa04) = *(uint *)(DAT_80436354 + 0xa04) | 1;
            *(ushort **)(DAT_80436354 + 0xa2c) = puVar7;
          } while (uVar3 == 0);
          uVar6 = uVar2 | 0x40;
          *(char *)(DAT_80436354 + iVar8 + 0xa10) = (char)uVar6;
          uVar4 = zz_017c684_((uint)uVar2);
          param_1 = zz_0043b94_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                iVar8,uVar4 & 0xffff,uVar6,in_r6,in_r7,in_r8,in_r9,in_r10);
          *(undefined1 *)(DAT_80436354 + 4) = 2;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < 4);
      if (*(char *)(DAT_80436354 + 4) != '\x01') goto LAB_8017c94c;
    }
    else if (cVar1 < '\x04') {
LAB_8017c974:
      iVar8 = zz_000a3c4_();
      if (iVar8 != 0) {
        return 1;
      }
      uVar5 = 0xffffffff;
      goto LAB_8017c984;
    }
LAB_8017ca20:
    uVar5 = 0;
  }
  return uVar5;
}



// ==== 8017ca3c  zz_017ca3c_ ====

undefined4
zz_017ca3c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  ushort uVar4;
  undefined1 uVar5;
  ushort *puVar6;
  ushort *puVar7;
  ushort *puVar8;
  
  zz_017c7e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  if (*(int *)(DAT_80436354 + 0xa30) != 0) {
    return 1;
  }
  puVar6 = *(ushort **)(DAT_80436354 + 0xa28);
LAB_8017ca80:
  puVar7 = puVar6 + 1;
  puVar8 = puVar7;
  switch(*puVar6 & 0xff) {
  case 0x14:
    *(undefined1 *)(DAT_80436354 + 2) = 10;
    *(undefined1 *)(DAT_80436354 + 3) = 0;
    break;
  case 0x15:
    *(undefined1 *)(DAT_80436354 + 2) = 0x14;
    *(undefined1 *)(DAT_80436354 + 3) = 0;
    *(ushort *)(DAT_80436354 + 8) = *puVar7;
    puVar8 = puVar6 + 2;
    break;
  case 0x16:
    *(undefined1 *)(DAT_80436354 + 2) = 0x28;
    *(undefined1 *)(DAT_80436354 + 3) = 0;
    break;
  case 0x17:
    goto switchD_8017caa4_caseD_17;
  case 0x18:
    goto switchD_8017caa4_caseD_18;
  case 0x19:
    while( true ) {
      uVar4 = *puVar7;
      *(undefined1 *)(DAT_80436354 + uVar4 + 0xa0c) = 0xff;
      *(uint *)(DAT_80436354 + 0xa30) = *(uint *)(DAT_80436354 + 0xa30) | 1 << (uint)uVar4;
      puVar8 = puVar7 + 1;
      if ((puVar7[1] & 0xff) != 0x19) break;
      puVar7 = puVar7 + 2;
    }
    break;
  case 0x1a:
    *(undefined4 *)(DAT_80436354 + 0xa04) = 2;
    puVar6 = puVar7;
    goto LAB_8017ca80;
  case 0x1b:
    *(uint *)(DAT_80436354 + 0xa24) = (uint)*puVar7;
    *(undefined4 *)(DAT_80436354 + 0xa30) = 1;
    puVar8 = puVar6 + 2;
    break;
  case 0x1c:
    uVar4 = puVar6[2];
    uVar1 = *puVar7;
    if ((uVar4 & 0x8000) != 0) {
      uVar4 = uVar4 & 0x7fff;
      *(undefined4 *)(DAT_80436354 + 0x50) = 1;
    }
    *(ushort *)(DAT_80436354 + (uint)uVar1 * 2 + 0xa14) = uVar4;
    *(undefined4 *)(DAT_80436354 + 0xa30) = 1;
    puVar8 = puVar6 + 3;
    break;
  case 0x1d:
    while( true ) {
      *(undefined2 *)(DAT_80436354 + (uint)*puVar7 * 2 + 0xa14) = 0xfffe;
      *(undefined4 *)(DAT_80436354 + 0xa30) = 1;
      puVar8 = puVar7 + 1;
      if ((puVar7[1] & 0xff) != 0x1d) break;
      puVar7 = puVar7 + 2;
    }
    break;
  case 0x1e:
    *(uint *)(DAT_80436354 + 0x58) = (uint)*puVar7;
    puVar6 = puVar6 + 2;
    goto LAB_8017ca80;
  case 0x1f:
    *(uint *)(DAT_80436354 + 0x5c) = (uint)*puVar7;
    puVar6 = puVar6 + 2;
    goto LAB_8017ca80;
  case 0x20:
    zz_00ea170_((uint)*puVar7,0,-1,(uint)puVar6[2]);
    puVar8 = puVar6 + 3;
    break;
  case 0x21:
    *(uint *)(DAT_80436354 + 0x114) = *(uint *)(DAT_80436354 + 0x114) | 1 << (uint)*puVar7;
    puVar6 = puVar6 + 2;
    goto LAB_8017ca80;
  case 0x22:
    uVar4 = puVar6[2];
    *(uint *)(DAT_80436354 + 0x90) = *(uint *)(DAT_80436354 + 0x90) | 1 << (uint)*puVar7;
    *(uint *)(DAT_80436354 + 0xa24) = (uint)uVar4;
    *(undefined4 *)(DAT_80436354 + 0xa30) = 1;
    puVar8 = puVar6 + 3;
    break;
  case 0x23:
    *(char *)(DAT_80436354 + *puVar7 + 0x94) = (char)puVar6[2];
    puVar6 = puVar6 + 3;
    goto LAB_8017ca80;
  case 0x24:
    *(char *)(DAT_80436354 + *puVar7 + 0x130) = (char)puVar6[2];
    puVar6 = puVar6 + 3;
    goto LAB_8017ca80;
  case 0x25:
    uVar4 = *puVar7;
    uVar1 = puVar6[2];
    *(undefined1 *)(DAT_80436354 + uVar4 + 0x130) = 6;
    *(char *)(DAT_80436354 + uVar4 + 0x140) = (char)uVar1;
    puVar6 = puVar6 + 3;
    goto LAB_8017ca80;
  case 0x26:
    uVar4 = *puVar7;
    *(undefined1 *)(DAT_80436354 + uVar4 + 0x130) = 0;
    *(undefined1 *)(DAT_80436354 + uVar4 + 0x140) = 0;
    puVar6 = puVar6 + 2;
    goto LAB_8017ca80;
  case 0x27:
    *(undefined1 *)(DAT_80436354 + 2) = 0x1e;
    *(undefined1 *)(DAT_80436354 + 3) = 0;
    *(ushort *)(DAT_80436354 + 0x4520) = *puVar7;
    *(char *)(DAT_80436354 + 0x4522) = (char)puVar6[2];
    *(undefined1 *)(DAT_80436354 + 0x4523) = 0;
    puVar8 = puVar6 + 3;
    break;
  case 0x28:
    *(undefined1 *)(DAT_80436354 + 2) = 0x1e;
    *(undefined1 *)(DAT_80436354 + 3) = 0;
    *(ushort *)(DAT_80436354 + 0x4520) = *puVar7;
    *(char *)(DAT_80436354 + 0x4522) = (char)puVar6[2];
    uVar3 = zz_01cee00_((uint)*(ushort *)(DAT_80436354 + 0x4520));
    uVar3 = uVar3 & 0xffff;
    uVar2 = (uint)puVar6[3];
    if (uVar3 == 1) {
      uVar2 = 0;
    }
    else if (uVar2 == 0) {
      uVar2 = zz_00055fc_();
      uVar2 = (uVar2 - (uVar2 / uVar3) * uVar3) + 1 & 0xffff;
    }
    *(char *)(DAT_80436354 + 0x4523) = (char)uVar2;
    puVar8 = puVar6 + 4;
    break;
  case 0x29:
    *(undefined1 *)(DAT_80436354 + 2) = 0x1e;
    *(undefined1 *)(DAT_80436354 + 3) = 0;
    *(undefined2 *)(DAT_80436354 + 0x4520) = 0;
    *(undefined1 *)(DAT_80436354 + 0x4522) = 0;
    *(undefined1 *)(DAT_80436354 + 0x4523) = 0x20;
    break;
  case 0x2a:
    *(uint *)(DAT_80436354 + 0x74) = (uint)*puVar7;
    puVar6 = puVar6 + 2;
    goto LAB_8017ca80;
  case 0x2b:
    puVar6 = puVar6 + 2;
    if ((*(uint *)(DAT_80436354 + 0x78) < *(uint *)(DAT_80436354 + 0x74)) &&
       (*(uint *)(DAT_80436354 + 0x78) < (uint)*puVar7)) {
      *(uint *)(DAT_80436354 + 0x78) = (uint)*puVar7;
    }
    goto LAB_8017ca80;
  case 0x2c:
    puVar6 = puVar6 + 2;
    *(uint *)(DAT_80436354 + 0x78) = *(int *)(DAT_80436354 + 0x78) + (uint)*puVar7;
    if (*(uint *)(DAT_80436354 + 0x74) < *(uint *)(DAT_80436354 + 0x78)) {
      *(uint *)(DAT_80436354 + 0x78) = *(uint *)(DAT_80436354 + 0x74);
    }
    goto LAB_8017ca80;
  case 0x2d:
    goto switchD_8017caa4_caseD_2d;
  case 0x2e:
    *(undefined4 *)(DAT_80436354 + 0xa28) = 0;
    return 0;
  default:
    *(undefined4 *)(DAT_80436354 + 0xa28) = 0;
    return 0;
  }
LAB_8017cfbc:
  *(ushort **)(DAT_80436354 + 0xa28) = puVar8;
  return 1;
switchD_8017caa4_caseD_2d:
  zz_017f4c4_((uint)*puVar7);
  puVar6 = puVar6 + 2;
  goto LAB_8017ca80;
switchD_8017caa4_caseD_18:
  while( true ) {
    uVar3 = (uint)*puVar7;
    if ((int)*(char *)(DAT_80436354 + uVar3 + 0xa0c) != (uint)puVar7[1]) {
      uVar5 = (undefined1)puVar7[1];
      *(undefined1 *)(DAT_80436354 + uVar3 + 0xa0c) = uVar5;
      *(undefined1 *)(DAT_80436354 + uVar3 + 0xa08) = uVar5;
      *(uint *)(DAT_80436354 + 0xa30) = *(uint *)(DAT_80436354 + 0xa30) | 1 << uVar3;
    }
    puVar8 = puVar7 + 2;
    if ((puVar7[2] & 0xff) != 0x18) break;
    puVar7 = puVar7 + 3;
  }
  goto LAB_8017cfbc;
switchD_8017caa4_caseD_17:
  while( true ) {
    *(char *)(DAT_80436354 + *puVar7 + 0xa08) = (char)puVar7[1];
    puVar8 = puVar7 + 2;
    if ((puVar7[2] & 0xff) != 0x17) break;
    puVar7 = puVar7 + 3;
  }
  goto LAB_8017cfbc;
}



// ==== 8017cfec  zz_017cfec_ ====

undefined4
zz_017cfec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
           undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
           undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  short sVar3;
  
  iVar2 = DAT_80436354;
  cVar1 = *(char *)(DAT_80436354 + 3);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 == '\x04') {
        iVar2 = zz_0027adc_();
        if (iVar2 != 0) {
          return 1;
        }
        return 0;
      }
      if ('\x03' < cVar1) {
        return 1;
      }
      iVar2 = zz_0027adc_();
      if (iVar2 == 0) {
        *(char *)(DAT_80436354 + 3) = *(char *)(DAT_80436354 + 3) + '\x01';
        set_global_menu_mode(4);
        zz_0027aac_(0,0x10,0);
        return 1;
      }
      goto LAB_8017d11c;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(DAT_80436354 + 3) = 1;
      zz_0044920_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(short *)(DAT_80436354 + 8) + 1,iVar2,param_11,param_12,param_13,param_14,
                  param_15,param_16);
      zz_0027aac_(0,0x10,1);
    }
    else if (cVar1 < '\0') {
      return 1;
    }
    iVar2 = zz_000a3c4_();
    if (iVar2 != 0) {
      return 1;
    }
    iVar2 = zz_0027adc_();
    if (iVar2 != 0) {
      return 1;
    }
    *(char *)(DAT_80436354 + 3) = *(char *)(DAT_80436354 + 3) + '\x01';
    *(undefined2 *)(DAT_80436354 + 8) = 600;
    zz_0027c1c_();
    set_global_menu_mode(0);
  }
  if ((*(short *)(DAT_80436354 + 8) < 0x21c) && ((*(uint *)(DAT_80436354 + 0x18) & 0x100) != 0)) {
    *(undefined2 *)(DAT_80436354 + 8) = 1;
  }
  sVar3 = *(short *)(DAT_80436354 + 8) + -1;
  *(short *)(DAT_80436354 + 8) = sVar3;
  if (sVar3 < 1) {
    *(char *)(DAT_80436354 + 3) = *(char *)(DAT_80436354 + 3) + '\x01';
    zz_0027aac_(0,0x40,1);
    zz_00e9b60_((double)FLOAT_8043ae50,0,0x40,2);
    zz_00e9b60_((double)FLOAT_8043ae50,1,0x40,2);
  }
LAB_8017d11c:
  zz_001882c_(&DAT_803c04b0);
  return 1;
}



// ==== 8017d18c  zz_017d18c_ ====

void zz_017d18c_(void)

{
  char cVar1;
  int iVar2;
  
  cVar1 = DAT_80436354[3];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    DAT_80436354[3] = cVar1 + '\x01';
    zz_0027aac_(0,0x78,1);
    zz_00e9b60_((double)FLOAT_8043ae50,2,0x78,2);
  }
  iVar2 = zz_0027adc_();
  if (iVar2 == 0) {
    *DAT_80436354 = 9;
    DAT_80436354[1] = 0;
    DAT_80436354[6] = 3;
    zz_0181c78_();
    glxSwapWaitDrawDone_void_();
    zz_007fd5c_();
  }
  return;
}



// ==== 8017d234  FUN_8017d234 ====

void FUN_8017d234(void)

{
  char cVar1;
  int iVar2;
  uint local_8;
  int local_4;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x01') {
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) {
      if ((*(uint *)(DAT_80436354 + 0x18) & 0x200) == 0) {
        local_4 = *(int *)(DAT_80436354 + 0x9d0);
        local_8 = *(uint *)(DAT_80436354 + 0x9d4);
        iVar2 = zz_017d3e0_(*(uint *)(DAT_80436354 + 0x1c),&local_4,&local_8,
                            *(int *)(DAT_80436354 + 0x9d8),5);
        if (iVar2 != 0) {
          *(int *)(DAT_80436354 + 0x9d0) = local_4;
          *(uint *)(DAT_80436354 + 0x9d4) = local_8;
          *(uint *)(DAT_80436354 + 0x9c8) =
               (uint)*(byte *)(DAT_80436354 + *(int *)(DAT_80436354 + 0x118) * 0x40 + local_4 +
                               local_8 + 0x174);
          zz_0181814_();
        }
      }
      else {
        *(undefined1 *)(DAT_80436354 + 2) = 2;
        *(undefined1 *)(DAT_80436354 + 7) = 2;
        if (*(int *)(DAT_80436354 + 0x128) == 2) {
          *(undefined4 *)(DAT_80436354 + 0x128) = 3;
        }
        *(undefined4 *)(DAT_80436354 + 0x7c) = 1;
        *(undefined4 *)(DAT_80436354 + 0x9cc) = 0xffffffff;
        zz_0181864_();
      }
    }
    else {
      *(undefined1 *)(DAT_80436354 + 2) = 2;
      *(undefined1 *)(DAT_80436354 + 7) = 5;
      *(undefined4 *)(DAT_80436354 + 0x9cc) = 2;
      *(undefined4 *)(DAT_80436354 + 0xc4) = 0;
      *(undefined ***)(DAT_80436354 + 0x9ec) =
           &PTR_DAT_80358be4 + *(int *)(DAT_80436354 + 0x9c8) * 7;
      zz_018183c_();
    }
  }
  else if (cVar1 < '\x01') {
    if ((-1 < cVar1) && (*(int *)(DAT_80436354 + 0x9cc) == 1)) {
      *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    }
  }
  else if ((cVar1 < '\x03') && (*(int *)(DAT_80436354 + 0x9cc) == 3)) {
    *(undefined1 *)(DAT_80436354 + 1) = *(undefined1 *)(DAT_80436354 + 7);
    *(undefined1 *)(DAT_80436354 + 2) = 0;
  }
  return;
}



// ==== 8017d3e0  zz_017d3e0_ ====

undefined4 zz_017d3e0_(uint param_1,int *param_2,uint *param_3,int param_4,uint param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  iVar4 = *param_2;
  uVar5 = *param_3;
  iVar6 = iVar4;
  uVar2 = uVar5;
  if ((param_1 & 0x40004) == 0) {
    if ((param_1 & 0x80008) == 0) {
      if ((param_1 & 0x20002) == 0) {
        if ((param_1 & 0x10001) != 0) {
          if (iVar4 + uVar5 == 0) {
            if ((int)param_5 < param_4) {
              iVar6 = param_4 - param_5;
              uVar2 = param_5 - 1;
            }
            else {
              iVar6 = 0;
              uVar2 = param_4 - 1;
            }
          }
          else if ((int)(iVar4 - param_5) < 0) {
            uVar2 = iVar4 + uVar5;
            iVar6 = 0;
            uVar2 = uVar2 - param_5 &
                    ~(-((uint)(uVar2 < param_5) - ((int)uVar2 >> 0x1f)) - ((int)param_5 >> 0x1f));
          }
          else {
            iVar6 = iVar4 - param_5;
          }
        }
      }
      else if ((int)(iVar4 + uVar5 + 1) < param_4) {
        if ((int)(param_5 + iVar4 + uVar5) < param_4) {
          iVar1 = iVar4 + param_5;
          iVar3 = param_4 - param_5;
          iVar6 = iVar1;
          if (iVar3 < iVar1) {
            iVar6 = iVar3;
            uVar2 = (uVar5 + iVar1) - iVar3;
          }
        }
        else if ((int)param_5 < param_4) {
          iVar6 = param_4 - param_5;
          uVar2 = param_5 - 1;
        }
        else {
          iVar6 = 0;
          uVar2 = param_4 - 1;
        }
      }
      else {
        iVar6 = 0;
        uVar2 = 0;
      }
    }
    else if (iVar4 + uVar5 == 0) {
      if ((int)param_5 < param_4) {
        iVar6 = param_4 - param_5;
        uVar2 = param_5 - 1;
      }
      else {
        uVar2 = param_4 - 1;
      }
    }
    else if (uVar5 == 0) {
      iVar6 = iVar4 + -1;
    }
    else {
      uVar2 = uVar5 - 1;
    }
  }
  else {
    uVar2 = uVar5 + 1;
    if ((int)(iVar4 + uVar2) < param_4) {
      if ((int)(param_5 - 1) <= (int)uVar5) {
        iVar6 = iVar4 + 1;
        uVar2 = uVar5;
      }
    }
    else {
      iVar6 = 0;
      uVar2 = 0;
    }
  }
  if ((iVar6 == iVar4) && (uVar2 == uVar5)) {
    return 0;
  }
  *param_2 = iVar6;
  *param_3 = uVar2;
  return 1;
}



// ==== 8017d594  FUN_8017d594 ====

void FUN_8017d594(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  int iVar2;
  short sVar4;
  int iVar3;
  ushort *in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x02') {
    sVar4 = *(short *)(DAT_80436354 + 8) + -1;
    *(short *)(DAT_80436354 + 8) = sVar4;
    if (0 < sVar4) {
      return;
    }
    *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    return;
  }
  if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined4 *)(DAT_80436354 + 0x150c) = 0;
      *(undefined4 *)(DAT_80436354 + 0x1510) = 0;
      iVar2 = DAT_80436354;
      if (((*(int *)(DAT_80436354 + 0x40) == 2) ||
          (in_r6 = *(ushort **)(*(int *)(DAT_80436354 + 0x9ec) + 0x10), in_r6 == (ushort *)0x0)) ||
         ((*in_r6 & 0xff) == 0x2e)) goto LAB_8017d6a8;
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      *(undefined1 *)(DAT_80436354 + 4) = 0;
      *(ushort **)(DAT_80436354 + 0xa28) = in_r6;
      *(undefined4 *)(DAT_80436354 + 0x5c) = 0;
      *(undefined4 *)(DAT_80436354 + 0x7c) = 0;
    }
    else if (cVar1 < '\0') {
      return;
    }
    iVar2 = zz_017c7e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    if (iVar2 != 1) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      *(undefined2 *)(DAT_80436354 + 8) = 4;
      zz_01ac34c_();
    }
  }
  else {
    if (cVar1 != '\x04') {
      if ('\x03' < cVar1) {
        return;
      }
      iVar2 = DAT_80436354;
      iVar3 = zz_017ca3c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      if (iVar3 != 0) {
        return;
      }
LAB_8017d6a8:
      *(undefined1 *)(DAT_80436354 + 2) = 4;
      iVar3 = DAT_80436354;
      *(undefined1 *)(DAT_80436354 + 0xa0c) = 0;
      zz_0181d60_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,4,iVar2,
                  in_r6,in_r7,in_r8,in_r9,in_r10);
    }
    iVar2 = zz_000a3c4_();
    if (iVar2 == 0) {
      *(undefined1 *)(DAT_80436354 + 1) = 6;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
      *(undefined4 *)(DAT_80436354 + 0x7c) = 2;
      *(undefined4 *)(DAT_80436354 + 0x9f0) = 0;
      zz_01aa900_();
      iVar2 = **(int **)(DAT_80436354 + 0x9ec);
      cVar1 = *(char *)(iVar2 + 0xf);
      if (cVar1 != '\0') {
        *(int *)(DAT_80436354 + 0x8c) = (int)cVar1;
      }
      if (*(int *)(DAT_80436354 + 0x8c) == 0) {
        *(undefined4 *)(DAT_80436354 + 0x8c) = 1;
      }
      if (*(char *)(iVar2 + 0xe) == '\x03') {
        zz_017f628_();
      }
    }
  }
  return;
}



// ==== 8017d758  FUN_8017d758 ====

void FUN_8017d758(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x01') {
    sVar2 = *(short *)(DAT_80436354 + 8) + -1;
    *(short *)(DAT_80436354 + 8) = sVar2;
    if (sVar2 < 1) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    }
  }
  else if (cVar1 < '\x01') {
    if ((-1 < cVar1) && (*(int *)(DAT_80436354 + 0x9f0) == 1)) {
      *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
      *(undefined2 *)(DAT_80436354 + 8) = 0x1e;
    }
  }
  else if (cVar1 < '\x03') {
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) {
      if ((*(uint *)(DAT_80436354 + 0x18) & 0x200) != 0) {
        *(undefined1 *)(DAT_80436354 + 1) = 4;
        *(undefined1 *)(DAT_80436354 + 2) = 0;
        *(undefined4 *)(DAT_80436354 + 300) = 0;
        *(undefined4 *)(DAT_80436354 + 0x9cc) = 4;
        *(undefined4 *)(DAT_80436354 + 0x5c) = *(undefined4 *)(DAT_80436354 + 0x58);
        zz_0181864_();
      }
    }
    else {
      iVar3 = **(int **)(DAT_80436354 + 0x9ec);
      if (*(char *)(iVar3 + 0xe) == '\x03') {
        *(undefined1 *)(DAT_80436354 + 1) = 7;
        *(undefined1 *)(DAT_80436354 + 2) = 0;
        *(undefined4 *)(DAT_80436354 + 0x9f0) = 2;
        zz_00439a0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3);
        zz_017f628_();
        zz_01aba28_();
        zz_018183c_();
      }
      else {
        *(undefined1 *)(DAT_80436354 + 1) = 8;
        *(undefined1 *)(DAT_80436354 + 2) = 0;
        *(undefined2 *)(DAT_80436354 + 10) = 0;
        *(undefined1 *)(DAT_80436354 + 7) = 5;
        *(undefined1 *)(DAT_80436354 + 6) = 6;
        *(int *)(DAT_80436354 + 0xc4) = (int)*(char *)(iVar3 + 0xf);
        *(int *)(DAT_80436354 + 200) = (int)*(char *)(iVar3 + 0x10);
        zz_017f594_();
        zz_018183c_();
      }
    }
  }
  return;
}



// ==== 8017d8e4  FUN_8017d8e4 ====

void FUN_8017d8e4(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  iVar3 = **(int **)(DAT_80436354 + 0x9ec);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      if (*(int *)(DAT_80436354 + 0x9f0) != 1) {
        return;
      }
      *(undefined1 *)(DAT_80436354 + 1) = 6;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
      zz_0043a24_(3);
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(int *)(DAT_80436354 + 0x9f0) != 3) {
      return;
    }
    *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    *(undefined4 *)(DAT_80436354 + 0xc4) = 0;
    *(int *)(DAT_80436354 + 200) = (int)*(char *)(iVar3 + 0x10);
  }
  iVar4 = *(int *)(DAT_80436354 + 0x8c);
  uVar2 = zz_0181b84_();
  if ((int)*(char *)(iVar3 + 0x11) != 0) {
    uVar2 = uVar2 & ~(1 << ((int)*(char *)(iVar3 + 0x11) & 0xfU));
  }
  if ((int)*(char *)(iVar3 + 0x12) != 0) {
    uVar2 = uVar2 & ~(1 << ((int)*(char *)(iVar3 + 0x12) & 0xfU));
  }
  if ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) {
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x200) == 0) {
      if ((*(uint *)(DAT_80436354 + 0x1c) & 0x20002) == 0) {
        if ((*(uint *)(DAT_80436354 + 0x1c) & 0x10001) == 0) {
          return;
        }
        do {
          iVar4 = iVar4 + -1;
          if (iVar4 < 0) {
            iVar4 = 0xd;
          }
        } while ((uVar2 & 1 << iVar4) == 0);
      }
      else {
        do {
          iVar4 = iVar4 + 1;
          if (0xd < iVar4) {
            iVar4 = 0;
          }
        } while ((uVar2 & 1 << iVar4) == 0);
      }
      if (*(int *)(DAT_80436354 + 0x8c) != iVar4) {
        *(int *)(DAT_80436354 + 0x8c) = iVar4;
        zz_017f628_();
        zz_0181814_();
      }
    }
    else {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      *(undefined4 *)(DAT_80436354 + 0x9f0) = 0;
      zz_0181864_();
    }
  }
  else {
    *(undefined1 *)(DAT_80436354 + 1) = 8;
    *(undefined1 *)(DAT_80436354 + 2) = 0;
    *(undefined2 *)(DAT_80436354 + 10) = 0x3c;
    *(undefined1 *)(DAT_80436354 + 7) = 5;
    *(undefined1 *)(DAT_80436354 + 6) = 7;
    *(int *)(DAT_80436354 + 0xc4) = iVar4;
    *(undefined4 *)(DAT_80436354 + 0x9f0) = 4;
    zz_018183c_();
    if (iVar4 != 0) {
      uVar2 = zz_00055fc_();
      zz_00ea170_(iVar4,0,-1,(int)*(short *)(iVar4 * 0x10 + -0x7fca40c4 + (uVar2 & 7) * 2));
    }
  }
  return;
}



// ==== 8017db20  FUN_8017db20 ====

void FUN_8017db20(void)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  cVar1 = DAT_80436354[2];
  if (cVar1 == '\x01') {
    iVar3 = zz_0027adc_();
    if (iVar3 == 0) {
      *DAT_80436354 = DAT_80436354[7];
      DAT_80436354[1] = 0;
      DAT_80436354[3] = 0;
      DAT_80436354[7] = DAT_80436354[6];
      zz_0181c78_();
      glxSwapWaitDrawDone_void_();
      zz_007fd5c_();
    }
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
          (sVar2 = *(short *)(DAT_80436354 + 10), *(short *)(DAT_80436354 + 10) = sVar2 + -1,
          (short)(sVar2 + -1) < 1)) {
    DAT_80436354[2] = DAT_80436354[2] + '\x01';
    zz_0027aac_(0,0x20,1);
    zz_00e9b60_((double)FLOAT_8043ae50,2,0x20,2);
  }
  return;
}



// ==== 8017dbf0  FUN_8017dbf0 ====

void FUN_8017dbf0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  int iVar3;
  ushort *puVar4;
  
  switch(DAT_80436354[2]) {
  case 0:
    if (*(int *)(DAT_80436354 + 0x40) != 2) {
      if (PTR_DAT_80433934[0x15de] == '\0') {
        puVar4 = *(ushort **)(*(int *)(DAT_80436354 + 0x9ec) + 0x18);
      }
      else {
        puVar4 = *(ushort **)(*(int *)(DAT_80436354 + 0x9ec) + 0x14);
      }
      if ((puVar4 != (ushort *)0x0) && ((*puVar4 & 0xff) != 0x2e)) {
        DAT_80436354[2] = DAT_80436354[2] + '\x01';
        DAT_80436354[4] = 0;
        *(ushort **)(DAT_80436354 + 0xa28) = puVar4;
        goto switchD_8017dc24_caseD_1;
      }
    }
    goto LAB_8017dcf4;
  case 1:
switchD_8017dc24_caseD_1:
    iVar3 = zz_017c7e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    if (iVar3 != 1) {
      DAT_80436354[2] = DAT_80436354[2] + '\x01';
      *(undefined2 *)(DAT_80436354 + 8) = 4;
      zz_01ac34c_();
    }
    break;
  case 2:
    sVar2 = *(short *)(DAT_80436354 + 8);
    *(short *)(DAT_80436354 + 8) = sVar2 + -1;
    if ((short)(sVar2 + -1) < 1) {
      DAT_80436354[2] = DAT_80436354[2] + '\x01';
    }
    break;
  case 3:
    iVar3 = zz_017ca3c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    if (iVar3 != 0) {
      return;
    }
LAB_8017dcf4:
    DAT_80436354[1] = 1;
    DAT_80436354[2] = 0;
    if (*(int *)(DAT_80436354 + 0x128) == 2) {
      *(undefined4 *)(DAT_80436354 + 0x128) = 3;
    }
    DAT_80436354[0xa0c] = 0;
    zz_017f744_();
    break;
  case 10:
    cVar1 = DAT_80436354[3];
    if (cVar1 != '\x01') {
      if ('\0' < cVar1) {
        return;
      }
      if (cVar1 < '\0') {
        return;
      }
      DAT_80436354[3] = cVar1 + '\x01';
      param_1 = zz_01c66a0_(0,(char)*(undefined4 *)(DAT_80436354 + 0x3c),DAT_80436354 + 0xa4);
    }
    iVar3 = zz_01c677c_();
    if (iVar3 != 0) {
      DAT_80436354[2] = 3;
      *(undefined4 *)(DAT_80436354 + 0x38) = 1;
      zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,
                  DAT_80436354 + 0xa4,3,param_12,param_13,param_14,param_15,param_16);
      strcpy(&DAT_803bfe20,DAT_80436354 + 0xa4);
      strcpy((char *)(DAT_80436220 + 0x2174),DAT_80436354 + 0xa4);
    }
    break;
  case 0x14:
    iVar3 = zz_017cfec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        &switchD_8017dc24::switchdataD_80352f0c,DAT_80436354,param_11,param_12,
                        param_13,param_14,param_15,param_16);
    if (iVar3 == 0) {
      DAT_80436354[2] = 3;
    }
    break;
  case 0x1e:
    cVar1 = DAT_80436354[3];
    if (cVar1 == '\x02') {
      DAT_80436354[3] = 3;
      zz_0027aac_(0,0x10,0);
    }
    else {
      if (cVar1 < '\x02') {
        if (cVar1 == '\0') {
          DAT_80436354[3] = 1;
          zz_0027aac_(0,0x10,1);
        }
        else if (cVar1 < '\0') {
          return;
        }
        iVar3 = zz_0027adc_();
        if (iVar3 != 0) {
          return;
        }
        *DAT_80436354 = 8;
        DAT_80436354[1] = 0;
        *(undefined4 *)(DAT_80436354 + 0xa04) = 2;
        return;
      }
      if ('\x03' < cVar1) {
        return;
      }
    }
    iVar3 = zz_0027adc_();
    if (iVar3 == 0) {
      DAT_80436354[2] = 3;
    }
    break;
  case 0x28:
    zz_017d18c_();
  }
  return;
}



// ==== 8017deb8  FUN_8017deb8 ====

void FUN_8017deb8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  byte bVar1;
  int iVar2;
  short sVar4;
  int iVar3;
  uint uVar5;
  int in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  bVar1 = *(byte *)(DAT_80436354 + 2);
  uVar5 = (uint)bVar1;
  switch(bVar1) {
  case 0:
    *(byte *)(DAT_80436354 + 2) = bVar1 + 1;
    *(undefined2 *)(DAT_80436354 + 8) = 0x10;
    *(undefined2 *)(DAT_80436354 + 0x24) = 0;
    *(undefined4 *)(DAT_80436354 + 0x10) = 0;
    zz_01d21ac_();
  case 1:
    sVar4 = *(short *)(DAT_80436354 + 8) + -1;
    *(short *)(DAT_80436354 + 8) = sVar4;
    if (sVar4 < 1) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    }
    break;
  case 2:
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) {
      if ((*(uint *)(DAT_80436354 + 0x18) & 0x1200) == 0) {
        iVar2 = (int)*(short *)(DAT_80436354 + 0x24);
        if ((*(uint *)(DAT_80436354 + 0x1c) & 0x40004) == 0) {
          if ((*(uint *)(DAT_80436354 + 0x1c) & 0x80008) == 0) break;
          iVar3 = iVar2 + -1;
          if (iVar3 < 0) {
            iVar3 = 2;
          }
        }
        else {
          iVar3 = iVar2 + 1;
          if (2 < iVar3) {
            iVar3 = 0;
          }
        }
        if (iVar2 != iVar3) {
          *(short *)(DAT_80436354 + 0x24) = (short)iVar3;
          zz_0181814_();
        }
      }
      else {
        *(undefined1 *)(DAT_80436354 + 1) = 2;
        *(undefined1 *)(DAT_80436354 + 2) = 1;
        zz_0181864_();
      }
    }
    else {
      *(undefined1 *)(DAT_80436354 + 2) = 9;
      zz_018183c_();
    }
    break;
  case 9:
    if (0x1e < *(int *)(DAT_80436354 + 0x10)) {
      *(char *)(DAT_80436354 + 2) = (char)*(undefined2 *)(DAT_80436354 + 0x24) * '\n' + '\n';
      *(undefined1 *)(DAT_80436354 + 3) = 0;
    }
    break;
  case 0x14:
    iVar2 = DAT_80436354;
    iVar3 = zz_0181940_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,uVar5,
                        DAT_80436354,in_r6);
    if (iVar3 != 1) {
      zz_0044b1c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,uVar5,iVar2,
                  in_r6,in_r7,in_r8,in_r9,in_r10);
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    }
    break;
  case 0x15:
    *(undefined4 *)(DAT_80436354 + 0x10) = 0;
    iVar2 = zz_000a3c4_();
    if (iVar2 != 0) break;
  case 10:
    *(undefined1 *)(DAT_80436354 + 1) = 2;
    *(undefined1 *)(DAT_80436354 + 2) = 1;
    break;
  case 0x1e:
    iVar2 = zz_0181940_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,uVar5,
                        DAT_80436354,in_r6);
    if (iVar2 != 1) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    }
    break;
  case 0x1f:
    *(byte *)(DAT_80436354 + 2) = bVar1 + 1;
    zz_0027aac_(0,0x20,1);
    zz_00e9b60_((double)FLOAT_8043ae50,2,0x20,2);
    break;
  case 0x20:
    iVar2 = zz_0027adc_();
    if (iVar2 == 0) {
      zz_0181c78_();
      glxSwapWaitDrawDone_void_();
      zz_007fd5c_();
      *PTR_DAT_80433930 = 2;
      PTR_DAT_80433930[1] = 0;
    }
  }
  if (('\b' < *(char *)(DAT_80436354 + 2)) &&
     (iVar2 = *(int *)(DAT_80436354 + 0x10) + 1, *(int *)(DAT_80436354 + 0x10) = iVar2, 0x1f < iVar2
     )) {
    *(undefined4 *)(DAT_80436354 + 0x10) = 0;
  }
  return;
}



// ==== 8017e138  zz_017e138_ ====

void zz_017e138_(void)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined **ppuVar13;
  int iVar14;
  
  if (*(int *)(DAT_80436354 + 0x40) == 2) {
    zz_017e34c_();
  }
  else {
    iVar12 = 0;
    iVar11 = 0;
    iVar14 = 3;
    do {
      *(undefined1 *)(DAT_80436354 + iVar12 + 0x574) = 0;
      iVar10 = iVar12 + 0x575;
      iVar8 = iVar12 + 0x576;
      iVar5 = iVar12 + 0x577;
      iVar9 = iVar11 + 0x156;
      iVar6 = iVar11 + 0x158;
      iVar4 = iVar11 + 0x15a;
      *(undefined2 *)(DAT_80436354 + iVar11 + 0x154) = 0;
      iVar2 = iVar12 + 0x578;
      iVar1 = iVar11 + 0x15c;
      iVar11 = iVar11 + 10;
      iVar12 = iVar12 + 5;
      *(undefined1 *)(DAT_80436354 + iVar10) = 0;
      *(undefined2 *)(DAT_80436354 + iVar9) = 0;
      *(undefined1 *)(DAT_80436354 + iVar8) = 0;
      *(undefined2 *)(DAT_80436354 + iVar6) = 0;
      *(undefined1 *)(DAT_80436354 + iVar5) = 0;
      *(undefined2 *)(DAT_80436354 + iVar4) = 0;
      *(undefined1 *)(DAT_80436354 + iVar2) = 0;
      *(undefined2 *)(DAT_80436354 + iVar1) = 0;
      iVar14 = iVar14 + -1;
    } while (iVar14 != 0);
    iVar11 = 1;
    *(undefined4 *)(DAT_80436354 + 0x150) = 0;
    for (ppuVar13 = &PTR_DAT_80358c00; *ppuVar13 != (undefined *)0x0; ppuVar13 = ppuVar13 + 7) {
      bVar3 = zz_017f3a4_(iVar11);
      if ((bVar3 != 0) && (bVar3 = zz_017f434_(iVar11), bVar3 == 0)) {
        pcVar7 = *ppuVar13;
        iVar1 = (int)*pcVar7;
        iVar14 = iVar1 + 0x574;
        iVar12 = iVar1 * 0x40 + (int)*(char *)(DAT_80436354 + iVar14);
        *(char *)(DAT_80436354 + iVar12 + 0x174) = (char)iVar11;
        *(char *)(DAT_80436354 + iVar12 + 0x584) = pcVar7[3];
        *(char *)(DAT_80436354 + iVar14) = *(char *)(DAT_80436354 + iVar14) + '\x01';
        if ((pcVar7[1] == '\x06') || (pcVar7[1] == '\a')) {
          *(uint *)(DAT_80436354 + 0x150) = *(uint *)(DAT_80436354 + 0x150) | 1 << iVar1;
        }
        iVar12 = iVar1 * 2 + 0x154;
        *(ushort *)(DAT_80436354 + iVar12) =
             *(ushort *)(DAT_80436354 + iVar12) | *(ushort *)(pcVar7 + 4);
      }
      iVar11 = iVar11 + 1;
    }
    *(undefined4 *)(DAT_80436354 + 0x9d0) = 0;
    *(undefined4 *)(DAT_80436354 + 0x9d4) = 0;
    *(int *)(DAT_80436354 + 0x9d8) =
         (int)*(char *)(DAT_80436354 + *(int *)(DAT_80436354 + 0x118) + 0x574);
    *(uint *)(DAT_80436354 + 0x9c8) =
         (uint)*(byte *)(DAT_80436354 + *(int *)(DAT_80436354 + 0x118) * 0x40 + 0x174);
  }
  return;
}



// ==== 8017e34c  zz_017e34c_ ====

void zz_017e34c_(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  char *pcVar13;
  undefined **ppuVar14;
  int iVar15;
  
  iVar12 = 0;
  iVar10 = 0;
  iVar15 = 3;
  do {
    *(undefined1 *)(DAT_80436354 + iVar12 + 0x574) = 0;
    iVar9 = iVar12 + 0x575;
    iVar7 = iVar12 + 0x576;
    iVar5 = iVar12 + 0x577;
    iVar8 = iVar10 + 0x156;
    iVar6 = iVar10 + 0x158;
    iVar4 = iVar10 + 0x15a;
    *(undefined2 *)(DAT_80436354 + iVar10 + 0x154) = 0;
    iVar2 = iVar12 + 0x578;
    iVar1 = iVar10 + 0x15c;
    iVar10 = iVar10 + 10;
    iVar12 = iVar12 + 5;
    *(undefined1 *)(DAT_80436354 + iVar9) = 0;
    *(undefined2 *)(DAT_80436354 + iVar8) = 0;
    *(undefined1 *)(DAT_80436354 + iVar7) = 0;
    *(undefined2 *)(DAT_80436354 + iVar6) = 0;
    *(undefined1 *)(DAT_80436354 + iVar5) = 0;
    *(undefined2 *)(DAT_80436354 + iVar4) = 0;
    *(undefined1 *)(DAT_80436354 + iVar2) = 0;
    *(undefined2 *)(DAT_80436354 + iVar1) = 0;
    iVar15 = iVar15 + -1;
  } while (iVar15 != 0);
  uVar11 = 1;
  *(undefined4 *)(DAT_80436354 + 0x150) = 0;
  for (ppuVar14 = &PTR_DAT_80358c00; pcVar13 = *ppuVar14, pcVar13 != (char *)0x0;
      ppuVar14 = ppuVar14 + 7) {
    uVar3 = zz_017f560_(uVar11);
    if (uVar3 != 0) {
      iVar12 = *pcVar13 + 0x574;
      iVar10 = *pcVar13 * 0x40 + (int)*(char *)(DAT_80436354 + iVar12);
      *(char *)(DAT_80436354 + iVar10 + 0x174) = (char)uVar11;
      *(char *)(DAT_80436354 + iVar10 + 0x584) = pcVar13[3];
      *(char *)(DAT_80436354 + iVar12) = *(char *)(DAT_80436354 + iVar12) + '\x01';
    }
    uVar11 = uVar11 + 1;
  }
  *(undefined4 *)(DAT_80436354 + 0x9d0) = 0;
  *(undefined4 *)(DAT_80436354 + 0x9d4) = 0;
  *(int *)(DAT_80436354 + 0x9d8) =
       (int)*(char *)(DAT_80436354 + *(int *)(DAT_80436354 + 0x118) + 0x574);
  *(uint *)(DAT_80436354 + 0x9c8) =
       (uint)*(byte *)(DAT_80436354 + *(int *)(DAT_80436354 + 0x118) * 0x40 + 0x174);
  return;
}



// ==== 8017e4f0  zz_017e4f0_ ====

void zz_017e4f0_(void)

{
  byte bVar2;
  int iVar1;
  ushort *puVar3;
  undefined **ppuVar4;
  int iVar5;
  
  if (*(int *)(DAT_80436354 + 0x40) != 2) {
    iVar5 = 1;
    for (ppuVar4 = &PTR_DAT_8035ac60; *ppuVar4 != (undefined *)0x0; ppuVar4 = ppuVar4 + 3) {
      bVar2 = zz_017f494_(iVar5);
      if (((bVar2 != 0) && (bVar2 = zz_017f4f4_(iVar5), bVar2 == 0)) &&
         (puVar3 = (ushort *)ppuVar4[1], puVar3 != (ushort *)0x0)) {
        iVar1 = (uint)*puVar3 * 2 + 0x154;
        *(ushort *)(DAT_80436354 + iVar1) = *(ushort *)(DAT_80436354 + iVar1) | puVar3[1];
      }
      iVar5 = iVar5 + 1;
    }
  }
  return;
}



// ==== 8017e5a0  zz_017e5a0_ ====

void zz_017e5a0_(void)

{
  char cVar1;
  byte bVar2;
  undefined **ppuVar3;
  int iVar4;
  int iVar5;
  
  if (*(int *)(DAT_80436354 + 0x40) != 2) {
    iVar4 = 1;
    iVar5 = 8;
    for (ppuVar3 = &PTR_DAT_80358c00; *ppuVar3 != (undefined *)0x0; ppuVar3 = ppuVar3 + 7) {
      if ((ppuVar3[2] != (undefined *)0x0) &&
         (((uint)(byte)(*ppuVar3)[7] & 1 << *(int *)(DAT_80436354 + 100)) != 0)) {
        cVar1 = *(char *)(DAT_80436354 + iVar5 + 0xa38);
        if (cVar1 != '\0') {
          cVar1 = cVar1 + -1;
          *(char *)(DAT_80436354 + iVar5 + 0xa38) = cVar1;
          if (cVar1 != '\0') goto LAB_8017e64c;
          zz_017f374_(iVar4);
        }
        bVar2 = zz_017f3a4_(iVar4);
        if (bVar2 == 0) {
          zz_017e680_(iVar4,(ushort *)ppuVar3[2]);
        }
      }
LAB_8017e64c:
      iVar5 = iVar5 + 8;
      iVar4 = iVar4 + 1;
    }
  }
  return;
}



// ==== 8017e680  zz_017e680_ ====

void zz_017e680_(int param_1,ushort *param_2)

{
  ushort *puVar1;
  ushort uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  byte bVar9;
  byte bVar10;
  uint uVar7;
  int iVar8;
  ushort *puVar11;
  ushort uVar12;
  
  bVar4 = false;
  iVar3 = param_1 * 8;
  bVar5 = false;
  bVar6 = false;
  do {
    puVar11 = param_2 + 1;
    switch(*param_2 & 0xff) {
    case 0:
      puVar1 = param_2 + 2;
      param_2 = param_2 + 3;
      if ((*(uint *)(DAT_80436354 + 0x6c) < (uint)(int)(short)*puVar11) ||
         ((uint)(int)(short)*puVar1 < *(uint *)(DAT_80436354 + 0x6c))) {
        bVar5 = true;
      }
      else {
        bVar4 = true;
      }
      break;
    case 1:
      puVar1 = param_2 + 2;
      param_2 = param_2 + 3;
      if ((*(uint *)(DAT_80436354 + 0x78) < (uint)(int)(short)*puVar11) ||
         ((uint)(int)(short)*puVar1 < *(uint *)(DAT_80436354 + 0x78))) {
        bVar5 = true;
      }
      else {
        bVar4 = true;
      }
      break;
    case 2:
      param_2 = param_2 + 2;
      if (*(char *)(DAT_80436354 + (short)*puVar11 * 8 + 0xa35) == '\0') {
        bVar5 = true;
      }
      else {
        bVar4 = true;
      }
      break;
    case 3:
      param_2 = param_2 + 2;
      if ((*(char *)(DAT_80436354 + (short)*puVar11 * 8 + 0xa35) == '\0') &&
         (bVar9 = zz_017f434_((int)(short)*puVar11), bVar9 != 0)) {
        bVar4 = true;
      }
      else {
        bVar5 = true;
      }
      break;
    case 4:
      param_2 = param_2 + 2;
      bVar9 = zz_017f434_((int)(short)*puVar11);
      if (bVar9 == 0) {
        bVar5 = true;
      }
      else {
        bVar4 = true;
      }
      break;
    case 5:
      param_2 = param_2 + 2;
      bVar9 = zz_017f3a4_((int)(short)*puVar11);
      if (bVar9 == 0) {
        bVar4 = true;
      }
      else {
        bVar5 = true;
      }
      break;
    case 6:
      param_2 = param_2 + 2;
      if (*(char *)(DAT_80436354 + (short)*puVar11 * 8 + 0xa35) == '\0') {
        bVar4 = true;
      }
      else {
        bVar5 = true;
      }
      break;
    case 7:
      param_2 = param_2 + 2;
      bVar9 = zz_017f494_((int)(short)*puVar11);
      if (bVar9 == 0) {
        bVar5 = true;
      }
      else {
        bVar4 = true;
      }
      break;
    case 8:
      param_2 = param_2 + 2;
      bVar9 = zz_017f494_((int)(short)*puVar11);
      if (bVar9 == 0) {
        bVar4 = true;
      }
      else {
        bVar5 = true;
      }
      break;
    case 9:
      uVar12 = param_2[2];
      uVar2 = *puVar11;
      param_2 = param_2 + 3;
      if (uVar12 != 0) {
        uVar12 = uVar12 - 1;
      }
      bVar9 = zz_017f434_(param_1);
      bVar10 = zz_017f3a4_(param_1);
      if (bVar10 == bVar9) {
        bVar9 = *(char *)(iVar3 + DAT_80436354 + 0xa37) + 1;
        *(byte *)(iVar3 + DAT_80436354 + 0xa37) = bVar9;
        if (((uint)bVar9 == ((int)(uint)bVar9 / (int)(short)uVar2) * (int)(short)uVar2) &&
           (uVar7 = zz_00055fc_(), (uVar7 & 0xf) <= (uint)(int)(short)uVar12)) {
          bVar4 = true;
          bVar6 = true;
          *(undefined1 *)(iVar3 + DAT_80436354 + 0xa37) = 0;
        }
        else {
          bVar5 = true;
        }
      }
      break;
    case 10:
      puVar1 = param_2 + 2;
      param_2 = param_2 + 3;
      iVar8 = zz_017f344_((int)(short)*puVar11,(int)(short)*puVar1);
      if (iVar8 == 0) {
        bVar5 = true;
      }
      else {
        bVar4 = true;
      }
      break;
    default:
def_8017E6D0:
      if (((bVar4) && (!bVar5)) && (zz_017f374_(param_1), bVar6)) {
        zz_017f404_(param_1);
      }
      return;
    case 0xc:
      param_2 = param_2 + 2;
      if (*(int *)(DAT_80436354 + 0x124) == (int)(short)*puVar11) {
        bVar4 = true;
      }
      else {
        bVar5 = true;
      }
      break;
    case 0xd:
      param_2 = param_2 + 2;
      if ((bVar4) && (!bVar5)) {
        bVar4 = false;
        bVar5 = true;
        *(char *)(iVar3 + DAT_80436354 + 0xa38) = (char)*puVar11;
      }
      break;
    case 0x11:
      param_2 = param_2 + 2;
      if (*(uint *)(DAT_80436354 + 0x1438) < (uint)(int)(short)*puVar11) {
        bVar4 = true;
      }
      else {
        bVar5 = true;
      }
      break;
    case 0x12:
      param_2 = param_2 + 2;
      if (*(uint *)(DAT_80436354 + 0x1438) < (uint)(int)(short)*puVar11) {
        bVar5 = true;
      }
      else {
        bVar4 = true;
      }
      break;
    case 0x13:
      if ((bVar4) && (!bVar5)) goto def_8017E6D0;
      bVar4 = false;
      bVar5 = false;
      bVar6 = false;
      param_2 = puVar11;
    }
  } while( true );
}



// ==== 8017ea70  zz_017ea70_ ====

void zz_017ea70_(void)

{
  undefined **ppuVar1;
  int iVar2;
  
  if (*(int *)(DAT_80436354 + 0x40) != 2) {
    iVar2 = 1;
    for (ppuVar1 = &PTR_DAT_80358c00; *ppuVar1 != (undefined *)0x0; ppuVar1 = ppuVar1 + 7) {
      if ((ushort *)ppuVar1[3] != (ushort *)0x0) {
        zz_017eae8_(iVar2,(ushort *)ppuVar1[3]);
      }
      iVar2 = iVar2 + 1;
    }
  }
  return;
}



// ==== 8017eae8  zz_017eae8_ ====

void zz_017eae8_(int param_1,ushort *param_2)

{
  ushort *puVar1;
  ushort uVar2;
  bool bVar3;
  byte bVar5;
  int iVar4;
  int iVar6;
  ushort *puVar7;
  
  bVar5 = zz_017f3a4_(param_1);
  if (bVar5 != 0) {
    iVar6 = DAT_80436354 + param_1 * 8;
    *(char *)(iVar6 + 0xa3a) = *(char *)(iVar6 + 0xa3a) + '\x01';
  }
  bVar5 = zz_017f434_(param_1);
  if (bVar5 != 0) {
    iVar6 = DAT_80436354 + param_1 * 8;
    *(char *)(iVar6 + 0xa3b) = *(char *)(iVar6 + 0xa3b) + '\x01';
  }
  iVar6 = param_1 * 8;
  bVar3 = false;
  do {
    puVar7 = param_2 + 1;
    switch(*param_2 & 0xff) {
    case 0:
      param_2 = param_2 + 3;
      if ((int)(short)*puVar7 == *(int *)(DAT_80436354 + 0x6c)) {
        bVar3 = true;
      }
      break;
    case 1:
      puVar1 = param_2 + 2;
      param_2 = param_2 + 3;
      if (((uint)(int)(short)*puVar7 <= *(uint *)(DAT_80436354 + 0x78)) &&
         (*(uint *)(DAT_80436354 + 0x78) <= (uint)(int)(short)*puVar1)) {
        bVar3 = true;
      }
      break;
    case 2:
      uVar2 = *puVar7;
      param_2 = param_2 + 2;
      bVar5 = zz_017f434_((int)(short)uVar2);
      if ((bVar5 != 0) && (*(char *)(DAT_80436354 + (short)uVar2 * 8 + 0xa35) != '\0')) {
        bVar3 = true;
      }
      break;
    case 3:
      uVar2 = *puVar7;
      param_2 = param_2 + 2;
      bVar5 = zz_017f434_((int)(short)uVar2);
      if ((bVar5 != 0) && (*(char *)(DAT_80436354 + (short)uVar2 * 8 + 0xa35) == '\0')) {
        bVar3 = true;
      }
      break;
    case 4:
      param_2 = param_2 + 2;
      bVar5 = zz_017f434_((int)(short)*puVar7);
      if (bVar5 != 0) {
        bVar3 = true;
      }
      break;
    case 5:
      param_2 = param_2 + 2;
      bVar5 = zz_017f3a4_((int)(short)*puVar7);
      if (bVar5 == 0) {
        bVar3 = true;
      }
      break;
    case 6:
      param_2 = param_2 + 2;
      if (*(char *)(DAT_80436354 + (short)*puVar7 * 8 + 0xa35) == '\0') {
        bVar3 = true;
      }
      break;
    case 7:
      param_2 = param_2 + 2;
      bVar5 = zz_017f494_((int)(short)*puVar7);
      if (bVar5 != 0) {
        bVar3 = true;
      }
      break;
    case 8:
      param_2 = param_2 + 2;
      bVar5 = zz_017f494_((int)(short)*puVar7);
      if (bVar5 == 0) {
        bVar3 = true;
      }
      break;
    default:
      goto def_8017EB7C;
    case 10:
      puVar1 = param_2 + 2;
      param_2 = param_2 + 3;
      iVar4 = zz_017f344_((int)(short)*puVar7,(int)(short)*puVar1);
      if (iVar4 != 0) {
        bVar3 = true;
      }
      break;
    case 0xd:
      uVar2 = *puVar7;
      param_2 = param_2 + 2;
      if ((bVar3) || (*(char *)(iVar6 + DAT_80436354 + 0xa39) != '\0')) {
        bVar5 = *(char *)(iVar6 + DAT_80436354 + 0xa39) + 1;
        *(byte *)(iVar6 + DAT_80436354 + 0xa39) = bVar5;
        if ((short)uVar2 < (short)(ushort)bVar5) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
      }
      break;
    case 0xe:
      param_2 = param_2 + 2;
      if ((short)*puVar7 <= (short)(ushort)*(byte *)(iVar6 + DAT_80436354 + 0xa3a)) {
        bVar3 = true;
      }
      break;
    case 0xf:
      uVar2 = *puVar7;
      param_2 = param_2 + 2;
      bVar5 = zz_017f434_((int)(short)uVar2);
      if ((bVar5 != 0) && ((int)(short)uVar2 <= (int)(uint)*(byte *)(iVar6 + DAT_80436354 + 0xa36)))
      {
        bVar3 = true;
      }
      break;
    case 0x10:
      uVar2 = *puVar7;
      param_2 = param_2 + 2;
      bVar5 = zz_017f434_(param_1);
      if ((bVar5 != 0) && ((short)uVar2 < (short)(ushort)*(byte *)(iVar6 + DAT_80436354 + 0xa3b))) {
        *(undefined1 *)(iVar6 + DAT_80436354 + 0xa3b) = 0;
        zz_017f404_(param_1);
      }
      break;
    case 0x11:
      param_2 = param_2 + 2;
      if (*(uint *)(DAT_80436354 + 0x1438) < (uint)(int)(short)*puVar7) {
        bVar3 = true;
      }
      break;
    case 0x12:
      param_2 = param_2 + 2;
      if ((uint)(int)(short)*puVar7 <= *(uint *)(DAT_80436354 + 0x1438)) {
        bVar3 = true;
      }
      break;
    case 0x13:
      param_2 = puVar7;
      if (bVar3) {
def_8017EB7C:
        if (bVar3) {
          zz_017f3d4_(param_1);
        }
        return;
      }
    }
  } while( true );
}



// ==== 8017ee94  zz_017ee94_ ====

undefined4 zz_017ee94_(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  byte bVar3;
  undefined **ppuVar4;
  int iVar5;
  int iVar6;
  
  if (*(int *)(DAT_80436354 + 0x40) == 2) {
    uVar1 = 0;
  }
  else {
    *(undefined4 *)(DAT_80436354 + 0x9e0) = 0;
    iVar5 = 1;
    iVar6 = 2;
    *(undefined4 *)(DAT_80436354 + 0x9e4) = 0;
    *(undefined4 *)(DAT_80436354 + 0x9e8) = 0;
    for (ppuVar4 = &PTR_DAT_8035ac60; (ushort *)*ppuVar4 != (ushort *)0x0; ppuVar4 = ppuVar4 + 3) {
      cVar2 = *(char *)(DAT_80436354 + iVar6 + 0x1235);
      if (cVar2 == '\0') {
        zz_017efd8_(iVar5,(ushort *)*ppuVar4);
LAB_8017ef3c:
        bVar3 = zz_017f494_(iVar5);
        if ((bVar3 != 0) && (bVar3 = zz_017f4f4_(iVar5), bVar3 == 0)) {
          if (ppuVar4[1] == (undefined *)0x0) {
            if (*(int *)(DAT_80436354 + 0x9e0) == 0) {
              *(int *)(DAT_80436354 + 0x9e0) = iVar5;
            }
          }
          else {
            *(int *)(DAT_80436354 + 0x9e4) = iVar5;
            *(uint *)(DAT_80436354 + 0x9e8) = (uint)*(ushort *)ppuVar4[1];
          }
        }
      }
      else if ((param_1 != 0) &&
              (cVar2 = cVar2 + -1, *(char *)(DAT_80436354 + iVar6 + 0x1235) = cVar2, cVar2 == '\0'))
      {
        zz_017f464_(iVar5);
        goto LAB_8017ef3c;
      }
      iVar6 = iVar6 + 2;
      iVar5 = iVar5 + 1;
    }
    uVar1 = *(undefined4 *)(DAT_80436354 + 0x9e0);
  }
  return uVar1;
}



// ==== 8017efd8  zz_017efd8_ ====

void zz_017efd8_(int param_1,ushort *param_2)

{
  ushort *puVar1;
  bool bVar2;
  bool bVar3;
  byte bVar5;
  int iVar4;
  ushort *puVar6;
  
  bVar2 = false;
  bVar3 = false;
  do {
    puVar6 = param_2 + 1;
    switch(*param_2 & 0xff) {
    case 0:
      puVar1 = param_2 + 2;
      param_2 = param_2 + 3;
      if ((*(uint *)(DAT_80436354 + 0x6c) < (uint)(int)(short)*puVar6) ||
         ((uint)(int)(short)*puVar1 < *(uint *)(DAT_80436354 + 0x6c))) {
        bVar3 = true;
      }
      else {
        bVar2 = true;
      }
      break;
    case 1:
      puVar1 = param_2 + 2;
      param_2 = param_2 + 3;
      if ((*(uint *)(DAT_80436354 + 0x78) < (uint)(int)(short)*puVar6) ||
         ((uint)(int)(short)*puVar1 < *(uint *)(DAT_80436354 + 0x78))) {
        bVar3 = true;
      }
      else {
        bVar2 = true;
      }
      break;
    case 2:
      param_2 = param_2 + 2;
      if (*(char *)(DAT_80436354 + (short)*puVar6 * 8 + 0xa35) == '\0') {
        bVar3 = true;
      }
      else {
        bVar2 = true;
      }
      break;
    case 3:
      param_2 = param_2 + 2;
      if ((*(char *)(DAT_80436354 + (short)*puVar6 * 8 + 0xa35) == '\0') &&
         (bVar5 = zz_017f434_((int)(short)*puVar6), bVar5 != 0)) {
        bVar2 = true;
      }
      else {
        bVar3 = true;
      }
      break;
    case 4:
      param_2 = param_2 + 2;
      bVar5 = zz_017f434_((int)(short)*puVar6);
      if (bVar5 == 0) {
        bVar3 = true;
      }
      else {
        bVar2 = true;
      }
      break;
    case 5:
      param_2 = param_2 + 2;
      bVar5 = zz_017f3a4_((int)(short)*puVar6);
      if (bVar5 == 0) {
        bVar2 = true;
      }
      else {
        bVar3 = true;
      }
      break;
    case 6:
      param_2 = param_2 + 2;
      if (*(char *)(DAT_80436354 + (short)*puVar6 * 8 + 0xa35) == '\0') {
        bVar2 = true;
      }
      else {
        bVar3 = true;
      }
      break;
    case 7:
      param_2 = param_2 + 2;
      bVar5 = zz_017f494_((int)(short)*puVar6);
      if (bVar5 == 0) {
        bVar3 = true;
      }
      else {
        bVar2 = true;
      }
      break;
    case 8:
      param_2 = param_2 + 2;
      bVar5 = zz_017f494_((int)(short)*puVar6);
      if (bVar5 == 0) {
        bVar2 = true;
      }
      else {
        bVar3 = true;
      }
      break;
    default:
def_8017F024:
      if ((bVar2) && (!bVar3)) {
        zz_017f464_(param_1);
      }
      return;
    case 10:
      puVar1 = param_2 + 2;
      param_2 = param_2 + 3;
      iVar4 = zz_017f344_((int)(short)*puVar6,(int)(short)*puVar1);
      if (iVar4 == 0) {
        bVar3 = true;
      }
      else {
        bVar2 = true;
      }
      break;
    case 0xb:
      param_2 = param_2 + 2;
      if (*(int *)(DAT_80436354 + 0x118) == (int)(short)*puVar6) {
        bVar2 = true;
      }
      else {
        bVar3 = true;
      }
      break;
    case 0xc:
      param_2 = param_2 + 2;
      if (*(int *)(DAT_80436354 + 0x124) == (int)(short)*puVar6) {
        bVar2 = true;
      }
      else {
        bVar3 = true;
      }
      break;
    case 0xd:
      param_2 = param_2 + 2;
      if ((bVar2) && (!bVar3)) {
        bVar2 = false;
        bVar3 = true;
        *(char *)(param_1 * 2 + DAT_80436354 + 0x1235) = (char)*puVar6;
      }
      break;
    case 0x11:
      param_2 = param_2 + 2;
      if (*(uint *)(DAT_80436354 + 0x1438) < (uint)(int)(short)*puVar6) {
        bVar2 = true;
      }
      else {
        bVar3 = true;
      }
      break;
    case 0x12:
      param_2 = param_2 + 2;
      if (*(uint *)(DAT_80436354 + 0x1438) < (uint)(int)(short)*puVar6) {
        bVar3 = true;
      }
      else {
        bVar2 = true;
      }
      break;
    case 0x13:
      if ((bVar2) && (!bVar3)) goto def_8017F024;
      bVar2 = false;
      bVar3 = false;
      param_2 = puVar6;
    }
  } while( true );
}



// ==== 8017f344  zz_017f344_ ====

void zz_017f344_(int param_1,int param_2)

{
  zz_0182378_(DAT_80436224,DAT_80436220,param_1,param_2);
  return;
}



// ==== 8017f374  zz_017f374_ ====

void zz_017f374_(int param_1)

{
  int iVar1;
  
  if (param_1 < 0) {
    return;
  }
  if (0xff < param_1) {
    return;
  }
  iVar1 = DAT_80436354 + param_1 * 8;
  *(byte *)(iVar1 + 0xa34) = *(byte *)(iVar1 + 0xa34) | 1;
  return;
}



// ==== 8017f3a4  zz_017f3a4_ ====

byte zz_017f3a4_(int param_1)

{
  if ((-1 < param_1) && (param_1 < 0x100)) {
    return *(byte *)(DAT_80436354 + param_1 * 8 + 0xa34) & 1;
  }
  return 0;
}



// ==== 8017f3d4  zz_017f3d4_ ====

void zz_017f3d4_(int param_1)

{
  int iVar1;
  
  if (param_1 < 0) {
    return;
  }
  if (0xff < param_1) {
    return;
  }
  iVar1 = DAT_80436354 + param_1 * 8;
  *(byte *)(iVar1 + 0xa34) = *(byte *)(iVar1 + 0xa34) | 2;
  return;
}



// ==== 8017f404  zz_017f404_ ====

void zz_017f404_(int param_1)

{
  int iVar1;
  
  if (param_1 < 0) {
    return;
  }
  if (0xff < param_1) {
    return;
  }
  iVar1 = DAT_80436354 + param_1 * 8;
  *(byte *)(iVar1 + 0xa34) = *(byte *)(iVar1 + 0xa34) & 0xfd;
  return;
}



// ==== 8017f434  zz_017f434_ ====

byte zz_017f434_(int param_1)

{
  if ((-1 < param_1) && (param_1 < 0x100)) {
    return *(byte *)(DAT_80436354 + param_1 * 8 + 0xa34) & 2;
  }
  return 0;
}



// ==== 8017f464  zz_017f464_ ====

void zz_017f464_(int param_1)

{
  int iVar1;
  
  if (param_1 < 0) {
    return;
  }
  if (0x3f < param_1) {
    return;
  }
  iVar1 = DAT_80436354 + param_1 * 2;
  *(byte *)(iVar1 + 0x1234) = *(byte *)(iVar1 + 0x1234) | 1;
  return;
}



// ==== 8017f494  zz_017f494_ ====

byte zz_017f494_(int param_1)

{
  if ((-1 < param_1) && (param_1 < 0x40)) {
    return *(byte *)(DAT_80436354 + param_1 * 2 + 0x1234) & 1;
  }
  return 0;
}



// ==== 8017f4c4  zz_017f4c4_ ====

void zz_017f4c4_(int param_1)

{
  int iVar1;
  
  if (param_1 < 0) {
    return;
  }
  if (0x3f < param_1) {
    return;
  }
  iVar1 = DAT_80436354 + param_1 * 2;
  *(byte *)(iVar1 + 0x1234) = *(byte *)(iVar1 + 0x1234) | 2;
  return;
}



// ==== 8017f4f4  zz_017f4f4_ ====

byte zz_017f4f4_(int param_1)

{
  if ((-1 < param_1) && (param_1 < 0x40)) {
    return *(byte *)(DAT_80436354 + param_1 * 2 + 0x1234) & 2;
  }
  return 0;
}



// ==== 8017f524  zz_017f524_ ====

void zz_017f524_(void)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = *(uint *)(DAT_80436354 + 0x9c8);
  iVar2 = DAT_80436354 + *(int *)(DAT_80436354 + 100) * 0x20 +
          ((int)uVar1 >> 3) + (uint)((int)uVar1 < 0 && (uVar1 & 7) != 0);
  *(byte *)(iVar2 + 0x4524) = *(byte *)(iVar2 + 0x4524) | (byte)(1 << (uVar1 & 7));
  return;
}



// ==== 8017f560  zz_017f560_ ====

uint zz_017f560_(uint param_1)

{
  return (uint)*(byte *)(DAT_80436354 + *(int *)(DAT_80436354 + 100) * 0x20 +
                         ((int)param_1 >> 3) + (uint)((int)param_1 < 0 && (param_1 & 7) != 0) +
                        0x4524) & 1 << (param_1 & 7);
}



// ==== 8017f594  zz_017f594_ ====

void zz_017f594_(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  undefined *puVar5;
  
  psVar4 = *(short **)(*(int *)(DAT_80436354 + 0x9ec) + 4);
  if (psVar4 == (short *)0x0) {
    puVar5 = (&PTR_PTR_8035b158)[*(int *)(DAT_80436354 + 0xc4)];
    iVar2 = zz_0181bd0_(*(int *)(DAT_80436354 + 0xc4));
    psVar4 = *(short **)(puVar5 + iVar2 * 4);
  }
  iVar3 = 0;
  iVar2 = 0;
  for (; -1 < *psVar4; psVar4 = psVar4 + 1) {
    iVar1 = iVar2 + 0xcc;
    iVar2 = iVar2 + 2;
    iVar3 = iVar3 + 1;
    *(short *)(DAT_80436354 + iVar1) = *psVar4;
  }
  *(int *)(DAT_80436354 + 0x108) = iVar3;
  return;
}



// ==== 8017f628  zz_017f628_ ====

void zz_017f628_(void)

{
  uint uVar1;
  uint uVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  
  iVar6 = *(int *)(DAT_80436354 + 0x8c);
  iVar4 = **(int **)(DAT_80436354 + 0x9ec);
  uVar2 = zz_0181b84_();
  uVar1 = (uint)*(char *)(iVar4 + 0x11);
  if (uVar1 != 0) {
    uVar2 = uVar2 & ~(1 << (uVar1 & 0xf));
  }
  uVar1 = (uint)*(char *)(iVar4 + 0x12);
  if (uVar1 != 0) {
    uVar2 = uVar2 & ~(1 << (uVar1 & 0xf));
  }
  if ((uVar2 & 1 << iVar6) == 0) {
    iVar6 = 1;
  }
  while ((uVar2 & 1 << iVar6) == 0) {
    iVar6 = iVar6 + 1;
    if (0xd < iVar6) {
      iVar6 = 0;
    }
  }
  iVar5 = 0;
  *(int *)(DAT_80436354 + 0x8c) = iVar6;
  iVar4 = *(int *)(DAT_80436354 + 0x8c);
  if (iVar4 != 0) {
    puVar7 = (&PTR_PTR_8035b158)[iVar4];
    iVar4 = zz_0181bd0_(iVar4);
    iVar6 = 0;
    for (psVar3 = *(short **)(puVar7 + iVar4 * 4); -1 < *psVar3; psVar3 = psVar3 + 1) {
      iVar4 = iVar6 + 0xcc;
      iVar6 = iVar6 + 2;
      iVar5 = iVar5 + 1;
      *(short *)(DAT_80436354 + iVar4) = *psVar3;
    }
  }
  *(int *)(DAT_80436354 + 0x108) = iVar5;
  return;
}



// ==== 8017f744  zz_017f744_ ====

void zz_017f744_(void)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_80436354 + 0x124) + 1;
  *(int *)(DAT_80436354 + 0x124) = iVar1;
  *(int *)(DAT_80436354 + 0x124) = iVar1 % 3;
  return;
}



// ==== 8017f77c  FUN_8017f77c ====

void FUN_8017f77c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  int iVar2;
  undefined8 extraout_f1;
  
  cVar1 = DAT_80436354[1];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      *DAT_80436354 = DAT_80436354[6];
      DAT_80436354[1] = 0;
      DAT_80436354[2] = 0;
      *(undefined4 *)(DAT_80436354 + 0x54) = 0;
      if ('\b' < (char)DAT_80436354[6]) {
        return;
      }
      if ((char)DAT_80436354[6] < '\a') {
        return;
      }
      DAT_80436354[2] = 4;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    DAT_80436354[1] = cVar1 + '\x01';
    DAT_80436354[2] = 0;
    gnt4_memset(PTR_DAT_80435a30,0,0x200);
    PTR_DAT_80435a30[0x46] = (char)*(undefined4 *)(DAT_80436354 + 0x3c);
    PTR_DAT_80435a30[0x47] = (char)(1 << (int)(char)PTR_DAT_80435a30[0x46]);
    *(undefined4 *)(PTR_DAT_80435a30 + 0x24) = DAT_80436220;
    *(undefined4 *)(PTR_DAT_80435a30 + 0x28) = DAT_80436224;
    *(undefined1 **)(PTR_DAT_80435a30 + 0x2c) = &DAT_803bfe20;
    PTR_DAT_80435a30[0x40] = (char)*(undefined4 *)(DAT_80436354 + 0x4c);
    PTR_DAT_80435a30[0x149] =
         ((char)((byte)((uint)-(int)(char)DAT_80436354[3] >> 0x18) | (char)DAT_80436354[3] >> 7) >>
         7) + '\x03';
  }
  iVar2 = zz_01ba750_();
  if (iVar2 != 0) {
    DAT_80436354[1] = DAT_80436354[1] + '\x01';
    *(int *)(DAT_80436354 + 0x4c) = (int)(char)PTR_DAT_80435a30[0x40];
  }
  zz_017f8f4_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 8017f8f4  zz_017f8f4_ ====

void zz_017f8f4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  int iVar2;
  short sVar3;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar4;
  
  iVar2 = DAT_80436354;
  if (*(int *)(DAT_80436354 + 0x68) != 0) {
    return;
  }
  if (*(int *)(DAT_80436354 + 0x54) == 0) {
    return;
  }
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      return;
    }
    if (cVar1 == '\0') {
      if (*(short *)(PTR_DAT_80435a30 + 0x12) != 1) {
        return;
      }
      *(undefined1 *)(DAT_80436354 + 2) = 1;
      uVar4 = zz_0044b80_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,0,iVar2,
                          in_r6,in_r7,in_r8,in_r9,in_r10);
      zz_0044418_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1);
      PTR_DAT_80435a30[0x148] = 1;
    }
    else if (cVar1 < '\0') {
      return;
    }
    if (*(short *)(PTR_DAT_80435a30 + 0x10) != 1) {
      return;
    }
    *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    *(undefined2 *)(DAT_80436354 + 8) = 0x28;
  }
  sVar3 = *(short *)(DAT_80436354 + 8) + -1;
  *(short *)(DAT_80436354 + 8) = sVar3;
  if (sVar3 < 1) {
    *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    *(undefined4 *)(DAT_80436354 + 0x84) = 4;
    zz_01d100c_(0);
  }
  return;
}



// ==== 8017f9f4  FUN_8017f9f4 ====

void FUN_8017f9f4(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  cVar1 = DAT_80436354[1];
  if (cVar1 == '\x01') {
LAB_8017fab8:
    uVar3 = zz_01f7e70_();
    if (uVar3 != 0) {
      if ((int)uVar3 < 0) {
        cVar1 = DAT_80436354[7];
        if (cVar1 == '\a') {
          *DAT_80436354 = 3;
          DAT_80436354[1] = 0;
          DAT_80436354[2] = 0;
          *(undefined4 *)(DAT_80436354 + 0x44) = 4;
        }
        else if ((cVar1 < '\a') && ('\x05' < cVar1)) {
          *DAT_80436354 = 3;
          DAT_80436354[1] = 0;
          DAT_80436354[2] = 0;
          *(undefined4 *)(DAT_80436354 + 0x44) = 3;
        }
        else {
          DAT_80436354[1] = 0;
        }
      }
      else if ((uVar3 & 0x8000) == 0) {
        DAT_80436354[1] = DAT_80436354[1] + '\x01';
        *(uint *)(DAT_80436354 + 0x4c) = uVar3 - 1;
      }
      else {
        *DAT_80436354 = 4;
        DAT_80436354[1] = 0;
        DAT_80436354[3] = 0;
        DAT_80436354[6] = 5;
        *(uint *)(DAT_80436354 + 0x4c) = (uVar3 & 0x7fff) - 1;
      }
    }
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return;
      }
      iVar2 = zz_0181c70_();
      if (iVar2 != 0) {
        DAT_80436354[1] = DAT_80436354[1] + '\x01';
        gnt4_memset(PTR_DAT_80433944,0,0x4a0);
        *(undefined4 *)(PTR_DAT_80433944 + *(int *)(DAT_80436354 + 0x3c) * 0x80 + 0x140) =
             DAT_80436220;
        PTR_DAT_80433944[*(int *)(DAT_80436354 + 0x3c) * 0x80 + 0x161] =
             (char)*(undefined4 *)(DAT_80436354 + 0x4c);
        iVar2 = *(int *)(**(int **)(DAT_80436354 + 0x9ec) + 8);
        if (iVar2 < 0) {
          iVar2 = zz_0181c30_();
        }
        *(int *)(PTR_DAT_80433934 + 0x120) = iVar2;
        goto LAB_8017fab8;
      }
    }
    else if ('\x02' < cVar1) {
      return;
    }
    *DAT_80436354 = 6;
    DAT_80436354[1] = 0;
  }
  return;
}



// ==== 8017fbdc  FUN_8017fbdc ====

void FUN_8017fbdc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  cVar1 = DAT_80436354[1];
  if (cVar1 == '\x01') {
LAB_8017fc5c:
    iVar4 = zz_000a3c4_();
    if (iVar4 == 0) {
      DAT_80436354[1] = DAT_80436354[1] + '\x01';
      gnt4_memset(PTR_DAT_80433934,0,0x18b8);
      PTR_DAT_80433934[0x15dd] = (char)*(undefined4 *)(DAT_80436354 + 0x80) + '\x01';
      zz_018014c_();
      zz_01820d4_();
      zz_0181774_();
      zz_0181774_();
      zz_0186964_(*(int *)(DAT_80436354 + 0x9c8));
      zz_0027c1c_();
    }
    return;
  }
  if (cVar1 < '\x01') {
    if (cVar1 < '\0') {
      return;
    }
    DAT_80436354[1] = cVar1 + '\x01';
    *(int *)(DAT_80436354 + 0x84) = (int)*(char *)(**(int **)(DAT_80436354 + 0x9ec) + 0xc);
    *(uint *)(DAT_80436354 + 0x80) =
         (-*(uint *)(DAT_80436354 + 0x84) | *(uint *)(DAT_80436354 + 0x84)) >> 0x1f;
    zz_00437b0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2);
    goto LAB_8017fc5c;
  }
  if ('\x02' < cVar1) {
    return;
  }
  zz_01873a4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0028264_();
  if ((*PTR_DAT_80433934 == '\x02') && (*(int *)(DAT_80436354 + 0x80) != 0)) {
    zz_01d100c_(1);
  }
  if (*PTR_DAT_80433930 != '\x01') {
    return;
  }
  *PTR_DAT_80433930 = 3;
  PTR_DAT_80433930[1] = 1;
  uVar2 = countLeadingZeros(1 - (char)PTR_DAT_80433934[0x1f]);
  uVar2 = uVar2 >> 5;
  zz_01803f0_(uVar2);
  zz_01804fc_(uVar2);
  uVar3 = countLeadingZeros(uVar2);
  zz_01ccf24_(DAT_80436220,*(int *)(DAT_80436354 + 0x3c),uVar3 >> 5);
  PTR_DAT_80433934[0x15de] = (char)uVar2;
  if (uVar2 == 0) {
    zz_0182110_();
    *DAT_80436354 = 3;
    DAT_80436354[1] = 0;
    DAT_80436354[2] = 0;
    *(undefined4 *)(DAT_80436354 + 0x44) = 2;
    goto LAB_8017fe00;
  }
  *DAT_80436354 = 7;
  DAT_80436354[1] = 0;
  DAT_80436354[2] = 0;
  iVar4 = *(int *)(DAT_80436354 + 0x9c8);
  if (iVar4 == 0x89) {
LAB_8017fdb8:
    *(undefined2 *)(DAT_80436354 + 0xe) = 1;
  }
  else {
    if (iVar4 < 0x89) {
      if (iVar4 == 0x16) goto LAB_8017fdb8;
    }
    else if ((iVar4 < 0xa5) && (0xa2 < iVar4)) goto LAB_8017fdb8;
    *(undefined2 *)(DAT_80436354 + 0xe) = 0;
  }
LAB_8017fe00:
  zz_0027c1c_();
  return;
}



// ==== 8017fe18  zz_017fe18_ ====

void zz_017fe18_(int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined2 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined2 *__s;
  undefined2 local_38 [10];
  
  iVar2 = DAT_80436220;
  iVar8 = 0;
  iVar9 = *(int *)(**(int **)(DAT_80436354 + 0x9ec) + 8);
  iVar7 = DAT_80436220 + *(int *)(DAT_80436354 + 0x4c) * 0x6c;
  if (iVar9 < 0) {
    iVar9 = zz_0181c30_();
  }
  puVar1 = PTR_DAT_80433934;
  PTR_DAT_80433934[param_1 + 0x5a] = 0;
  __s = (undefined2 *)(puVar1 + param_1 * 0x348 + 0x1e8);
  iVar3 = zz_0181c70_();
  if (iVar3 == 0) {
    gnt4_memset(__s,0,0x1c);
    iVar9 = zz_017f344_(0x629,-1);
    iVar8 = 0x615;
    if (iVar9 != 0) {
      iVar8 = 0x629;
    }
    uVar5 = zz_017f344_(iVar8,-1);
    if (uVar5 == 0) {
      *__s = (short)iVar8;
      *(undefined4 *)(__s + 6) = 0xffffffff;
      *(undefined4 *)(__s + 4) = 0;
    }
    else {
      if ((int)uVar5 >> 0x10 == 1) {
        puVar6 = (undefined2 *)(iVar2 + (uVar5 & 0xffff) * 0x20 + 0x870);
      }
      else {
        puVar6 = (undefined2 *)(DAT_80436224 + (uVar5 & 0xffff) * 0x10);
      }
      *__s = *puVar6;
      *(undefined1 *)(__s + 1) = *(undefined1 *)(puVar6 + 1);
      *(undefined1 *)((int)__s + 3) = *(undefined1 *)((int)puVar6 + 3);
      *(undefined4 *)(__s + 6) = *(undefined4 *)(puVar6 + 2);
      *(undefined4 *)(__s + 2) = *(undefined4 *)(puVar6 + 4);
      *(undefined4 *)(__s + 4) = 0;
    }
    __s = __s + 0xe;
    PTR_DAT_80433934[param_1 + 0x5a] = PTR_DAT_80433934[param_1 + 0x5a] + '\x01';
  }
  else {
    iVar3 = iVar7;
    for (iVar10 = 0; iVar10 < *(char *)(iVar7 + 0x29); iVar10 = iVar10 + 1) {
      puVar6 = (undefined2 *)(iVar2 + *(short *)(iVar3 + 0x30) * 0x20 + 0x870);
      local_38[0] = *puVar6;
      iVar4 = zz_0066168_((char *)local_38,(int)*(char *)(puVar6 + 1));
      if (iVar9 < iVar8 + iVar4) break;
      iVar8 = iVar8 + iVar4;
      gnt4_memset(__s,0,0x1c);
      iVar3 = iVar3 + 2;
      *__s = *puVar6;
      *(undefined1 *)(__s + 1) = *(undefined1 *)(puVar6 + 1);
      *(undefined1 *)((int)__s + 3) = *(undefined1 *)((int)puVar6 + 3);
      *(undefined4 *)(__s + 6) = *(undefined4 *)(puVar6 + 2);
      *(undefined4 *)(__s + 2) = *(undefined4 *)(puVar6 + 4);
      *(undefined4 *)(__s + 4) = 0;
      __s = __s + 0xe;
      PTR_DAT_80433934[param_1 + 0x5a] = PTR_DAT_80433934[param_1 + 0x5a] + '\x01';
    }
  }
  *__s = 0xffff;
  PTR_DAT_80433934[param_1 + 0x54] = 0;
  PTR_DAT_80433934[param_1 + 0x15c8] = 0;
  zz_0068424_(param_1,(undefined2 *)(PTR_DAT_80433934 + param_1 * 2 + 0x10),
              PTR_DAT_80433934 + param_1 + 0xa0);
  zz_0238cbc_((int)(PTR_DAT_80433934 + param_1 * 0x29 + 0x1654),iVar7,0x28);
  return;
}



// ==== 8018007c  zz_018007c_ ====

void zz_018007c_(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined2 *puVar4;
  undefined2 *__s;
  
  iVar2 = *(int *)(DAT_80436354 + 0x108);
  puVar4 = (undefined2 *)(DAT_80436354 + 0xcc);
  __s = (undefined2 *)(PTR_DAT_80433934 + param_1 * 0x348 + 0x1e8);
  for (iVar3 = 0; iVar3 < iVar2; iVar3 = iVar3 + 1) {
    gnt4_memset(__s,0,0x1c);
    uVar1 = *puVar4;
    puVar4 = puVar4 + 1;
    *__s = uVar1;
    *(undefined1 *)(__s + 1) = 0;
    __s = __s + 0xe;
  }
  *__s = 0xffff;
  PTR_DAT_80433934[param_1 + 0x5a] = (char)iVar2;
  PTR_DAT_80433934[param_1 + 0x54] = 0;
  PTR_DAT_80433934[param_1 + 0x15c8] = 0;
  zz_0068424_(param_1,(undefined2 *)(PTR_DAT_80433934 + param_1 * 2 + 0x10),
              PTR_DAT_80433934 + param_1 + 0xa0);
  return;
}



// ==== 8018014c  zz_018014c_ ====

void zz_018014c_(void)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar5 = **(int **)(DAT_80436354 + 0x9ec);
  PTR_DAT_80433934[0x1c] = *(undefined1 *)(iVar5 + 1);
  PTR_DAT_80433934[0x1d] = (char)*(undefined4 *)(DAT_80436354 + 0x124);
  PTR_DAT_80433934[0x1e] = *(undefined1 *)(iVar5 + 2);
  PTR_DAT_80433934[0xc0] = 0xff;
  *(undefined2 *)(PTR_DAT_80433934 + 0x10) = 0xffff;
  PTR_DAT_80433934[0x20] = 0;
  PTR_DAT_80433934[0x26] = 0;
  *(undefined1 *)(DAT_80436354 + 0x10c) = 0xff;
  PTR_DAT_80433934[0xc1] = 0xff;
  *(undefined2 *)(PTR_DAT_80433934 + 0x12) = 0xffff;
  PTR_DAT_80433934[0x21] = 0;
  PTR_DAT_80433934[0x27] = 0;
  *(undefined1 *)(DAT_80436354 + 0x10d) = 0xff;
  PTR_DAT_80433934[0xc2] = 0xff;
  *(undefined2 *)(PTR_DAT_80433934 + 0x14) = 0xffff;
  PTR_DAT_80433934[0x22] = 0;
  PTR_DAT_80433934[0x28] = 0;
  *(undefined1 *)(DAT_80436354 + 0x10e) = 0xff;
  PTR_DAT_80433934[0xc3] = 0xff;
  *(undefined2 *)(PTR_DAT_80433934 + 0x16) = 0xffff;
  PTR_DAT_80433934[0x23] = 0;
  PTR_DAT_80433934[0x29] = 0;
  *(undefined1 *)(DAT_80436354 + 0x10f) = 0xff;
  PTR_DAT_80433934[0xc4] = 0xff;
  *(undefined2 *)(PTR_DAT_80433934 + 0x18) = 0xffff;
  PTR_DAT_80433934[0x24] = 0;
  PTR_DAT_80433934[0x2a] = 0;
  *(undefined1 *)(DAT_80436354 + 0x110) = 0xff;
  PTR_DAT_80433934[0xc5] = 0xff;
  *(undefined2 *)(PTR_DAT_80433934 + 0x1a) = 0xffff;
  PTR_DAT_80433934[0x25] = 0;
  PTR_DAT_80433934[0x2b] = 0;
  *(undefined1 *)(DAT_80436354 + 0x111) = 0xff;
  iVar6 = *(int *)(DAT_80436354 + 0x3c);
  uVar3 = countLeadingZeros(iVar6);
  PTR_DAT_80433934[iVar6 + 0xcb] = 0;
  uVar3 = uVar3 >> 5;
  PTR_DAT_80433934[iVar6 + 0x20] = 0;
  PTR_DAT_80433934[iVar6 + 0x26] = 0;
  PTR_DAT_80433934[iVar6 + 0x32] = 0xf;
  zz_017fe18_(iVar6);
  *(undefined1 *)(DAT_80436354 + iVar6 + 0x10c) = 0;
  PTR_DAT_80433934[0xc0] = (char)iVar6;
  iVar6 = *(int *)(DAT_80436354 + 0xc4);
  if (0 < iVar6) {
    PTR_DAT_80433934[uVar3 + 0xcb] = 0;
    PTR_DAT_80433934[uVar3 + 0x20] = (char)iVar6;
    PTR_DAT_80433934[uVar3 + 0x26] = 0;
    PTR_DAT_80433934[uVar3 + 0x32] =
         (char)*(undefined4 *)(DAT_80436354 + 200) + (char)*(undefined4 *)(DAT_80436354 + 100);
    zz_018007c_(uVar3);
    *(char *)(DAT_80436354 + uVar3 + 0x10c) = (char)iVar6;
    *(uint *)(DAT_80436354 + 0x150c) = *(uint *)(DAT_80436354 + 0x150c) | 1 << iVar6;
  }
  iVar6 = 0;
  do {
    bVar1 = *(byte *)(iVar5 + iVar6 + 0x11);
    if ((bVar1 & 0xf) != 0) {
      iVar4 = 0;
      iVar7 = 6;
      iVar2 = DAT_80436354;
      do {
        if (*(char *)(iVar2 + 0x10c) < '\0') {
          *(byte *)(DAT_80436354 + iVar4 + 0x10c) = bVar1 & 0xf;
          break;
        }
        iVar2 = iVar2 + 1;
        iVar4 = iVar4 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    iVar6 = iVar6 + 1;
    if (1 < iVar6) {
      PTR_DAT_80433930[0x29] = 0;
      return;
    }
  } while( true );
}



// ==== 801803f0  zz_01803f0_ ====

void zz_01803f0_(int param_1)

{
  int iVar1;
  
  if (*(int *)(DAT_80436354 + 0x40) != 2) {
    *(int *)(DAT_80436354 + 0x6c) = *(int *)(DAT_80436354 + 0x6c) + 1;
    DAT_803bfe74 = DAT_803bfe74 | 1 << (int)(char)PTR_DAT_80433934[0x1c];
    if (param_1 == 0) {
      *(int *)(DAT_80436354 + 0x70) = *(int *)(DAT_80436354 + 0x70) + 1;
      iVar1 = DAT_80436354 + *(int *)(DAT_80436354 + 0x9c8) * 8;
      *(char *)(iVar1 + 0xa36) = *(char *)(iVar1 + 0xa36) + '\x01';
      *(int *)(DAT_80436354 + 0x1438) = *(int *)(DAT_80436354 + 0x1438) + 1;
    }
    else {
      *(int *)(DAT_80436354 + 0x70) = *(int *)(DAT_80436354 + 0x70) + 10;
      iVar1 = DAT_80436354 + *(int *)(DAT_80436354 + 0x9c8) * 8;
      *(char *)(iVar1 + 0xa35) = *(char *)(iVar1 + 0xa35) + '\x01';
      *(int *)(DAT_80436354 + 0x1434) = *(int *)(DAT_80436354 + 0x1434) + 1;
      zz_017f3d4_(*(int *)(DAT_80436354 + 0x9c8));
      zz_017f524_();
    }
    zz_017ea70_();
    zz_017e5a0_();
    zz_017ee94_(1);
  }
  return;
}



// ==== 801804fc  zz_01804fc_ ====

void zz_01804fc_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(DAT_80436354 + 0x40) == 2) {
    return;
  }
  iVar2 = 1;
  iVar1 = 4;
  iVar3 = 0xd;
  do {
    if ((*(uint *)(DAT_80436354 + 0x150c) & 1 << iVar2) != 0) {
      *(int *)(DAT_80436354 + iVar1 + 0x14c4) = *(int *)(DAT_80436354 + iVar1 + 0x14c4) + 1;
    }
    if ((*(uint *)(DAT_80436354 + 0x1510) & 1 << iVar2) != 0) {
      if (param_1 == 0) {
        *(int *)(DAT_80436354 + iVar1 + 0x1484) = *(int *)(DAT_80436354 + iVar1 + 0x1484) + 1;
      }
      else {
        *(int *)(DAT_80436354 + iVar1 + 0x1444) = *(int *)(DAT_80436354 + iVar1 + 0x1444) + 1;
      }
    }
    iVar1 = iVar1 + 4;
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}



// ==== 80180598  FUN_80180598 ====

void FUN_80180598(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  cVar1 = DAT_80436354[1];
  switch(cVar1) {
  case '\0':
    DAT_80436354[1] = cVar1 + '\x01';
    *(undefined2 *)(DAT_80436354 + 0x24) = 0;
    set_global_menu_mode(0);
    zz_0197854_(1);
    zz_0009f40_();
    uVar4 = 0;
    zz_0088398_(DAT_80436238 + 0xfe800,0xe0000,0);
    zz_00059b8_();
    uVar5 = zz_007fd5c_();
    zz_007fd6c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0180820_,0,uVar4,
                in_r6,in_r7,in_r8,in_r9,in_r10);
    if (DAT_80436354[2] != '\0') {
      DAT_80436354[1] = 4;
      *(undefined2 *)(DAT_80436354 + 0x24) = 1;
    }
    break;
  case '\x01':
    iVar2 = zz_0182228_((undefined2 *)(DAT_80436354 + 0x4520),DAT_80436354 + 0x4522,
                        DAT_80436354 + 0x4523);
    if (iVar2 == 0) {
      if (*(short *)(DAT_80436354 + 0xe) != 0) {
        *(undefined2 *)(DAT_80436354 + 0xe) = 0;
        iVar2 = zz_0180850_();
        if (iVar2 != 0) goto LAB_8018066c;
      }
      iVar2 = zz_0180908_();
      if (iVar2 == 0) {
        *DAT_80436354 = 3;
        DAT_80436354[1] = 0;
        DAT_80436354[2] = 0;
        *(undefined4 *)(DAT_80436354 + 0x44) = 2;
        zz_0180820_();
        zz_007fd5c_();
        return;
      }
    }
    goto LAB_8018066c;
  case '\x02':
    DAT_80436354[1] = cVar1 + '\x01';
    uVar5 = zz_0182648_((uint)(byte)DAT_80436354[0x4523]);
    param_1 = zz_01ce174_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803bfe20,DAT_80436224,DAT_80436220,0,
                          (char)*(undefined4 *)(DAT_80436354 + 0x3c),
                          (uint)*(ushort *)(DAT_80436354 + 0x4520),(uint)(byte)DAT_80436354[0x4522],
                          DAT_80436354[0x4523]);
  case '\x03':
    iVar2 = zz_01ce444_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    if (iVar2 != 0) {
      DAT_80436354[1] = DAT_80436354[1] + '\x01';
    }
    break;
  case '\x04':
    iVar2 = zz_01cebe0_();
    if (iVar2 == -1) {
      DAT_80436354[1] = 5;
    }
    else if ((iVar2 < -1) && (-3 < iVar2)) {
      DAT_80436354[1] = 6;
    }
    else {
      DAT_80436354[1] = 10;
    }
    DAT_80436354[2] = 0;
    break;
  case '\x05':
  case '\x06':
    zz_01809fc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    break;
  case '\n':
    DAT_80436354[1] = 1;
    set_global_menu_mode(0);
    if ((199 < *(short *)(DAT_80436220 + 0x2172)) && (1999 < *(short *)(DAT_80436224 + 44000))) {
      return;
    }
    uVar3 = zz_01cee38_(DAT_80436224,(uint)*(ushort *)(DAT_80436354 + 0x4520),
                        (uint)(byte)DAT_80436354[0x4522]);
    if (uVar3 == 0) {
      return;
    }
    DAT_80436354[0x4523] = (byte)uVar3 | 0x10;
    zz_0182648_(0);
LAB_8018066c:
    DAT_80436354[1] = DAT_80436354[1] + '\x01';
  }
  return;
}



// ==== 80180820  zz_0180820_ ====

void zz_0180820_(void)

{
  zz_0008b58_();
  zz_0008cf4_();
  zz_01978d0_();
  zz_0005984_(0);
  return;
}



// ==== 80180850  zz_0180850_ ====

undefined4 zz_0180850_(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  short *psVar5;
  
  if (*(int *)(DAT_80436354 + 0x40) == 2) {
    uVar4 = 0;
  }
  else {
    psVar5 = (short *)(&DAT_80353294 + *(int *)(DAT_80436354 + 100) * 10);
    do {
      sVar1 = *psVar5;
      if (sVar1 < 0) {
        return 0;
      }
      sVar2 = psVar5[1];
      psVar5 = psVar5 + 2;
      iVar3 = zz_017f344_((int)sVar1,(int)sVar2);
    } while (iVar3 != 0);
    *(short *)(DAT_80436354 + 0x4520) = sVar1;
    uVar4 = 1;
    *(char *)(DAT_80436354 + 0x4522) = (char)sVar2;
    *(undefined1 *)(DAT_80436354 + 0x4523) = 0;
  }
  return uVar4;
}



// ==== 80180908  zz_0180908_ ====

undefined4 zz_0180908_(void)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  short *psVar4;
  int iVar5;
  
  psVar4 = &DAT_8035b2dc;
  if ((*(short *)(DAT_80436220 + 0x2172) < 200) ||
     (psVar4 = &DAT_8035b2dc, *(short *)(DAT_80436224 + 44000) < 2000)) {
    while( true ) {
      sVar1 = *psVar4;
      if (sVar1 < 0) break;
      sVar2 = psVar4[1];
      if (1 < sVar2) {
        iVar5 = 0;
        do {
          uVar3 = zz_01cee38_(DAT_80436224,(int)sVar1,iVar5);
          if (uVar3 != 0) {
            *(short *)(DAT_80436354 + 0x4520) = sVar1;
            *(char *)(DAT_80436354 + 0x4522) = (char)iVar5;
            *(byte *)(DAT_80436354 + 0x4523) = (byte)sVar2 | 0x10;
            zz_0182648_(0);
            return 1;
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 6);
      }
      psVar4 = psVar4 + 8;
    }
  }
  return 0;
}



// ==== 801809fc  zz_01809fc_ ====

void zz_01809fc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  cVar1 = DAT_80436354[2];
  if (cVar1 == '\x03') {
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) {
      if ((*(uint *)(DAT_80436354 + 0x1c) & 0xc000c) != 0) {
        *(ushort *)(DAT_80436354 + 0x24) = *(ushort *)(DAT_80436354 + 0x24) ^ 1;
        zz_0181814_();
      }
    }
    else {
      DAT_80436354[2] = 4;
      *(undefined2 *)(DAT_80436354 + 8) = 0x1e;
      zz_018183c_();
    }
    goto LAB_80180bcc;
  }
  if ('\x02' < cVar1) {
    if (cVar1 == '\x05') {
      iVar3 = zz_0027adc_();
      if (iVar3 == 0) {
        zz_0181c78_();
        zz_0044178_();
        if (*(short *)(DAT_80436354 + 0x24) == 0) {
          DAT_80436354[1] = 10;
        }
        else {
          DAT_80436354[6] = *DAT_80436354;
          DAT_80436354[3] = DAT_80436354[1] + -5;
          *DAT_80436354 = 4;
          DAT_80436354[1] = 0;
          zz_0180820_();
          zz_007fd5c_();
        }
        zz_0027c1c_();
        return;
      }
    }
    else if ((cVar1 < '\x05') &&
            (sVar2 = *(short *)(DAT_80436354 + 8), *(short *)(DAT_80436354 + 8) = sVar2 + -1,
            (short)(sVar2 + -1) < 1)) {
      DAT_80436354[2] = DAT_80436354[2] + '\x01';
      zz_0027aac_(0,0x10,1);
    }
    goto LAB_80180bcc;
  }
  if (cVar1 == '\x01') {
LAB_80180a5c:
    iVar3 = zz_000a3c4_();
    if (iVar3 != 0) goto LAB_80180bcc;
    DAT_80436354[2] = DAT_80436354[2] + '\x01';
    *(undefined2 *)(DAT_80436354 + 8) = 0x10;
    *(undefined4 *)(DAT_80436354 + 0x10) = 0;
    zz_01d22d8_((char)DAT_80436354[1] + -5);
    zz_0027c1c_();
  }
  else if (cVar1 < '\x01') {
    if (cVar1 < '\0') goto LAB_80180bcc;
    DAT_80436354[2] = cVar1 + '\x01';
    zz_00440bc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    set_global_menu_mode(4);
    goto LAB_80180a5c;
  }
  sVar2 = *(short *)(DAT_80436354 + 8);
  *(short *)(DAT_80436354 + 8) = sVar2 + -1;
  if ((short)(sVar2 + -1) < 1) {
    DAT_80436354[2] = DAT_80436354[2] + '\x01';
  }
LAB_80180bcc:
  if (('\x03' < (char)DAT_80436354[2]) &&
     (iVar3 = *(int *)(DAT_80436354 + 0x10), *(int *)(DAT_80436354 + 0x10) = iVar3 + 1,
     0x1f < iVar3 + 1)) {
    *(undefined4 *)(DAT_80436354 + 0x10) = 0;
  }
  zz_0181dd8_();
  return;
}



// ==== 80180c14  FUN_80180c14 ====

void FUN_80180c14(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_r4;
  undefined1 *puVar3;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar4;
  
  switch(DAT_80436354[1]) {
  case 0:
    DAT_80436354[1] = DAT_80436354[1] + '\x01';
    set_global_menu_mode(0);
    uVar4 = zz_0027aac_(0,4,0);
    zz_01ce174_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803bfe20,
                DAT_80436224,DAT_80436220,0,(char)*(undefined4 *)(DAT_80436354 + 0x3c),
                (uint)*(ushort *)(DAT_80436354 + 0x4520),(uint)(byte)DAT_80436354[0x4522],
                DAT_80436354[0x4523]);
    param_1 = zz_0182648_((uint)(byte)DAT_80436354[0x4523]);
  case 1:
    iVar1 = zz_01ce444_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    if (iVar1 != 0) {
      DAT_80436354[1] = 4;
    }
    break;
  case 4:
    iVar1 = zz_01cebe0_();
    if (iVar1 == -1) {
      DAT_80436354[1] = 5;
    }
    else if ((iVar1 < -1) && (-3 < iVar1)) {
      DAT_80436354[1] = 6;
    }
    else {
      DAT_80436354[1] = 10;
    }
    DAT_80436354[2] = 0;
    break;
  case 5:
  case 6:
  case 10:
    if ((*(short *)(DAT_80436220 + 0x2172) < 200) ||
       (puVar3 = DAT_80436354, *(short *)(DAT_80436224 + 44000) < 2000)) {
      puVar3 = (undefined1 *)(uint)(byte)DAT_80436354[0x4522];
      uVar2 = zz_01cee38_(DAT_80436224,(uint)*(ushort *)(DAT_80436354 + 0x4520),(int)puVar3);
      if (uVar2 != 0) {
        DAT_80436354[1] = 0;
        DAT_80436354[0x4523] = (byte)uVar2 | 0x10;
        zz_0182648_(0);
        return;
      }
    }
    uVar4 = set_global_menu_mode(4);
    zz_0008a94_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                extraout_r4,puVar3,in_r6,in_r7,in_r8,in_r9,in_r10);
    *DAT_80436354 = 3;
    DAT_80436354[1] = 9;
    DAT_80436354[2] = 0x1e;
    DAT_80436354[3] = 2;
  }
  return;
}



// ==== 80180dd0  FUN_80180dd0 ====

void FUN_80180dd0(void)

{
  (*(code *)(&PTR_LAB_80353310)[*(char *)(DAT_80436354 + 1)])();
  return;
}



// ==== 80180e2c  FUN_80180e2c ====

void FUN_80180e2c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,int param_11,uint param_12,uint param_13,
                 undefined4 ***param_14,undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  
  uVar5 = DAT_80436354;
  bVar1 = *(byte *)(DAT_80436354 + 2);
  uVar2 = (uint)bVar1;
  if (bVar1 == 1) {
    sVar3 = *(short *)(DAT_80436354 + 8) + -1;
    *(short *)(DAT_80436354 + 8) = sVar3;
    if ((0 < sVar3) && (uVar2 = zz_01b79a4_(0), uVar2 == 0)) {
      cVar4 = zz_01b7968_(0);
      uVar2 = 0;
      if ((cVar4 == '\0') || (uVar2 = DAT_80436354, (*(uint *)(DAT_80436354 + 0x18) & 0x1000) == 0))
      goto LAB_80180f6c;
    }
    param_13 = DAT_80436354;
    param_11 = 1;
    param_12 = (uint)*(byte *)(DAT_80436354 + 2);
    *(byte *)(DAT_80436354 + 2) = *(byte *)(DAT_80436354 + 2) + 1;
    zz_0027aac_(0,0x20,1);
    uVar6 = zz_01b7928_(0,0x20);
    uVar2 = (uint)((ulonglong)uVar6 >> 0x20);
    uVar5 = (uint)uVar6;
    param_1 = extraout_f1_00;
  }
  else if ((char)bVar1 < '\x01') {
    if (-1 < (char)bVar1) {
      *(byte *)(DAT_80436354 + 2) = bVar1 + 1;
      uVar6 = set_global_menu_mode(0);
      *(undefined2 *)(DAT_80436354 + 8) = 3000;
      uVar6 = zz_01b7304_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,1,
                          DAT_80436238 + 0x208c00);
      param_11 = 0;
      zz_01b757c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,1,0,param_12,
                  param_13,param_14,param_15,param_16);
      uVar6 = zz_0027c1c_();
      uVar2 = (uint)((ulonglong)uVar6 >> 0x20);
      uVar5 = (uint)uVar6;
      param_1 = extraout_f1;
    }
  }
  else if ((((char)bVar1 < '\x03') && (uVar2 = zz_0027adc_(), uVar2 == 0)) &&
          (uVar2 = zz_0018f5c_(), uVar2 == 0)) {
    *(undefined1 *)(DAT_80436354 + 1) = 2;
    *(undefined1 *)(DAT_80436354 + 2) = 0;
    zz_01b74a8_(0);
    set_global_menu_mode(4);
    return;
  }
LAB_80180f6c:
  zz_01b7b98_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar2,uVar5,param_11,
              param_12,param_13,param_14,param_15,param_16);
  zz_008c0dc_(FUN_801b7bf0);
  return;
}



// ==== 80180f8c  FUN_80180f8c ====

void FUN_80180f8c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  
  iVar3 = DAT_80436354;
  iVar6 = 1;
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ((cVar1 < '\x03') && (iVar3 = zz_0027adc_(), iVar3 == 0)) {
        *(undefined1 *)(DAT_80436354 + 1) = 3;
        *(undefined1 *)(DAT_80436354 + 2) = 0;
      }
      goto LAB_801810ac;
    }
    if (cVar1 < '\0') goto LAB_801810ac;
    *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    uVar8 = zz_0181cac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,iVar3,
                        param_11,param_12,param_13,param_14,param_15,param_16);
    uVar5 = 0;
    iVar4 = 1;
    iVar7 = 0xd;
    iVar3 = DAT_80436354;
    do {
      uVar2 = *(uint *)(iVar3 + 0x14c8);
      if ((uVar5 < uVar2) || ((uVar5 == uVar2 && (iVar4 == 2)))) {
        uVar5 = uVar2;
        iVar6 = iVar4;
      }
      iVar4 = iVar4 + 1;
      iVar7 = iVar7 + -1;
      iVar3 = iVar3 + 4;
    } while (iVar7 != 0);
    zz_0043d98_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,iVar4,uVar5,
                param_12,param_13,param_14,param_15,param_16);
  }
  iVar3 = zz_000a3c4_();
  if (iVar3 == 0) {
    *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    *(undefined2 *)(DAT_80436354 + 0x24) = 0;
    zz_01e9de8_(0);
    uVar8 = zz_0027aac_(0,0x20,0);
    zz_00e99c8_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a0cc,
                param_12,param_13,param_14,param_15,param_16);
  }
LAB_801810ac:
  zz_0181dd8_();
  return;
}



// ==== 801810c4  FUN_801810c4 ====

void FUN_801810c4(void)

{
  char cVar1;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x02') {
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x1100) != 0) {
      *(undefined1 *)(DAT_80436354 + 2) = 3;
      *(undefined2 *)(DAT_80436354 + 0x24) = 0;
      zz_018183c_();
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(DAT_80436354 + 2) = 1;
      *(undefined2 *)(DAT_80436354 + 0x24) = 1;
      zz_01e9de8_(1);
    }
    else if (cVar1 < '\0') goto LAB_80181188;
    if ((*(ushort *)(DAT_80436354 + 0x24) & 0x80) != 0) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    }
  }
  else if ((cVar1 < '\x04') && ((*(ushort *)(DAT_80436354 + 0x24) & 0x80) != 0)) {
    *(undefined1 *)(DAT_80436354 + 1) = 4;
    *(undefined1 *)(DAT_80436354 + 2) = 0;
  }
LAB_80181188:
  zz_0181dd8_();
  return;
}



// ==== 8018119c  FUN_8018119c ====

/* WARNING: Removing unreachable block (ram,0x80181358) */

void FUN_8018119c(void)

{
  char cVar1;
  float fVar2;
  int iVar3;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  switch(cVar1) {
  case '\0':
    *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    fVar2 = FLOAT_8043ae50;
    *(undefined2 *)(DAT_80436354 + 0x24) = 2;
    *(undefined2 *)(DAT_80436354 + 0x26) = 0;
    *(undefined4 *)(DAT_80436354 + 0x10) = 0;
    *(undefined2 *)(DAT_80436354 + 0xc) = 0;
    *(float *)(DAT_80436354 + 0x30) = fVar2;
    zz_01e9de8_(2);
    break;
  case '\x01':
    if (*(short *)(DAT_80436354 + 0x24) != 2) {
      *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    }
    break;
  case '\x02':
    iVar3 = *(int *)(DAT_80436354 + 0x10) + 1;
    *(int *)(DAT_80436354 + 0x10) = iVar3;
    if (0x46 < iVar3) {
      *(undefined4 *)(DAT_80436354 + 0x10) = 0;
    }
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x1100) == 0) {
      if ((*(uint *)(DAT_80436354 + 0x18) & 0x200) == 0) {
        if ((*(short *)(DAT_80436354 + 0x26) < 8) &&
           ((*(uint *)(DAT_80436354 + 0x1c) & 0x40004) != 0)) {
          *(undefined1 *)(DAT_80436354 + 2) = 3;
          *(undefined2 *)(DAT_80436354 + 0xc) = 0;
        }
        else {
          if ((*(short *)(DAT_80436354 + 0x26) < 1) ||
             ((*(uint *)(DAT_80436354 + 0x1c) & 0x80008) == 0)) break;
          *(short *)(DAT_80436354 + 0x26) = *(short *)(DAT_80436354 + 0x26) + -1;
          *(undefined1 *)(DAT_80436354 + 2) = 4;
          *(undefined2 *)(DAT_80436354 + 0xc) = 1;
        }
        fVar2 = FLOAT_8043ae50;
        *(undefined4 *)(DAT_80436354 + 0x10) = 0;
        *(undefined2 *)(DAT_80436354 + 0xe) = 0;
        *(float *)(DAT_80436354 + 0x30) = fVar2;
        zz_0181814_();
      }
      else {
        *(undefined1 *)(DAT_80436354 + 2) = 0xb;
        *(undefined2 *)(DAT_80436354 + 0x24) = 0;
        zz_0181864_();
      }
    }
    else {
      *(undefined1 *)(DAT_80436354 + 1) = 5;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
      *(undefined2 *)(DAT_80436354 + 0x24) = 3;
      zz_018183c_();
    }
    break;
  case '\x03':
  case '\x04':
    iVar3 = zz_0182040_((short *)(DAT_80436354 + 0xe),(float *)(DAT_80436354 + 0x30),0x10);
    if (iVar3 != 0) {
      if (*(char *)(DAT_80436354 + 2) == '\x03') {
        *(short *)(DAT_80436354 + 0x26) = *(short *)(DAT_80436354 + 0x26) + 1;
      }
      fVar2 = FLOAT_8043ae50;
      *(undefined1 *)(DAT_80436354 + 2) = 2;
      *(undefined2 *)(DAT_80436354 + 0xc) = 0;
      *(float *)(DAT_80436354 + 0x30) = fVar2;
    }
    break;
  case '\n':
    if ((*(ushort *)(DAT_80436354 + 0x24) & 0x80) != 0) {
      *(undefined1 *)(DAT_80436354 + 1) = 5;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
    }
    break;
  case '\v':
    if ((*(ushort *)(DAT_80436354 + 0x24) & 0x80) != 0) {
      *(undefined1 *)(DAT_80436354 + 1) = 3;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
    }
  }
  zz_0181dd8_();
  return;
}



// ==== 80181414  FUN_80181414 ====

void FUN_80181414(void)

{
  char cVar1;
  short sVar2;
  double dVar3;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x03') {
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x1100) != 0) {
      *(undefined2 *)(DAT_80436354 + 8) = 0;
    }
    sVar2 = *(short *)(DAT_80436354 + 8) + -1;
    *(short *)(DAT_80436354 + 8) = sVar2;
    if (sVar2 < 1) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      *(undefined2 *)(DAT_80436354 + 0x24) = 3;
    }
  }
  else if (cVar1 < '\x03') {
    if (cVar1 == '\x01') {
      if ((*(uint *)(DAT_80436354 + 0x18) & 0x1100) != 0) {
        *(undefined2 *)(DAT_80436354 + 8) = 0;
      }
      sVar2 = *(short *)(DAT_80436354 + 8) + -1;
      *(short *)(DAT_80436354 + 8) = sVar2;
      if (sVar2 < 1) {
        *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
        *(undefined2 *)(DAT_80436354 + 8) = 0x46;
        *(undefined2 *)(DAT_80436354 + 0x24) = 2;
      }
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
        *(undefined2 *)(DAT_80436354 + 8) = 600;
        *(undefined2 *)(DAT_80436354 + 0x24) = 1;
        zz_01e9de8_(3);
      }
    }
    else {
      sVar2 = *(short *)(DAT_80436354 + 8) + -1;
      *(short *)(DAT_80436354 + 8) = sVar2;
      if (sVar2 < 1) {
        *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
        *(undefined2 *)(DAT_80436354 + 8) = 600;
      }
    }
  }
  else if (cVar1 == '\x05') {
    sVar2 = *(short *)(DAT_80436354 + 8) + -1;
    *(short *)(DAT_80436354 + 8) = sVar2;
    if (sVar2 < 1) {
      *(undefined1 *)(DAT_80436354 + 1) = 6;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
    }
  }
  else if ((cVar1 < '\x05') && (*(short *)(DAT_80436354 + 0x24) != 3)) {
    *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    dVar3 = (double)FLOAT_8043ae50;
    *(undefined2 *)(DAT_80436354 + 8) = 0x1e;
    zz_00e9b60_(dVar3,2,0xb4,2);
  }
  zz_0181dd8_();
  return;
}



// ==== 801815dc  FUN_801815dc ====

void FUN_801815dc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,int param_12)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x02') {
    *(undefined1 *)(DAT_80436354 + 2) = 3;
    zz_0027aac_(0,0x20,1);
    zz_00e9b60_((double)FLOAT_8043ae50,2,0x20,2);
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(DAT_80436354 + 2) = 1;
      *(undefined1 *)(DAT_80436354 + 3) = 0;
      iVar3 = DAT_80436354;
      if (*(uint *)(DAT_80436354 + 100) < 7) {
        uVar2 = *(uint *)(DAT_80436354 + 100) + 1;
        *(uint *)(DAT_80436354 + 100) = uVar2;
        if (*(uint *)(iVar3 + 0x68) < uVar2) {
          *(int *)(DAT_80436354 + 0x68) = *(int *)(DAT_80436354 + 0x68) + 1;
        }
      }
      else {
        *(undefined4 *)(DAT_80436354 + 0x68) = 8;
      }
      *(undefined4 *)(DAT_80436354 + 0x48) = 1;
      iVar3 = DAT_80436354;
      *(uint *)(DAT_80436354 + 0x4624) =
           *(uint *)(DAT_80436354 + 0x4624) | *(uint *)(DAT_80436354 + 0x90);
    }
    else {
      iVar3 = DAT_80436354;
      if (cVar1 < '\0') goto LAB_8018171c;
    }
    iVar3 = zz_0181940_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,iVar3,
                        param_11,param_12);
    if (iVar3 != 1) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    }
  }
  else if ((cVar1 < '\x04') && (iVar3 = zz_0027adc_(), iVar3 == 0)) {
    zz_0181c78_();
    zz_0043e60_();
    glxSwapWaitDrawDone_void_();
    zz_007fd5c_();
    *PTR_DAT_80433930 = 1;
    PTR_DAT_80433930[1] = 0;
    return;
  }
LAB_8018171c:
  zz_0181dd8_();
  return;
}



// ==== 80181730  FUN_80181730 ====

void FUN_80181730(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = zz_0196bc4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  if (iVar1 != 0) {
    *PTR_DAT_80433930 = 1;
    PTR_DAT_80433930[1] = 0;
  }
  return;
}



// ==== 80181774  zz_0181774_ ====

void zz_0181774_(void)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    iVar1 = (int)*(char *)(DAT_80436354 + iVar3 + 0x10c);
    pbVar2 = PTR_DAT_8035b294;
    if ((-1 < iVar1) &&
       ((iVar1 != 0 || (pbVar2 = (byte *)(DAT_80436354 + 0xa4), *(byte *)(DAT_80436354 + 0xa4) == 0)
        ))) {
      pbVar2 = (&PTR_DAT_8035b294)[iVar1];
    }
    zz_0098084_(-0x7fc44bc0,iVar3,pbVar2);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 6);
  gnt4_GXInvalidateTexAll_bl();
  return;
}



// ==== 80181814  zz_0181814_ ====

void zz_0181814_(void)

{
  zz_00f036c_(0,0x77);
  return;
}



// ==== 8018183c  zz_018183c_ ====

void zz_018183c_(void)

{
  zz_00f036c_(0,0x7a);
  return;
}



// ==== 80181864  zz_0181864_ ====

void zz_0181864_(void)

{
  zz_00f036c_(0,0x7b);
  return;
}



// ==== 8018188c  zz_018188c_ ====

void zz_018188c_(void)

{
  zz_00f036c_(0,0x7d);
  return;
}



// ==== 801818b4  zz_01818b4_ ====

int zz_01818b4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  int iVar2;
  int unaff_r31;
  undefined1 auStack_18 [20];
  
  cVar1 = *(char *)((int)DAT_80436354 + 3);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return unaff_r31;
    }
    if (cVar1 < '\0') {
      return unaff_r31;
    }
    *(char *)((int)DAT_80436354 + 3) = cVar1 + '\x01';
    zz_01b0e28_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    set_global_menu_mode(0);
  }
  gnt4_memcpy(auStack_18,DAT_80436354,4);
  iVar2 = zz_01b0ee8_();
  gnt4_memcpy(DAT_80436354,auStack_18,4);
  return iVar2;
}



// ==== 80181940  zz_0181940_ ====

int zz_0181940_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,int param_12)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *(char *)(DAT_80436354 + 3);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return param_12;
    }
    if (cVar1 < '\0') {
      return param_12;
    }
    *(char *)(DAT_80436354 + 3) = cVar1 + '\x01';
    *(undefined2 *)(DAT_80436354 + 0x2a) = 1;
    if (*(int *)(DAT_80436354 + 0x40) != 2) {
      *(undefined4 *)(DAT_80436354 + 0x60) = *(undefined4 *)(DAT_80436354 + 100);
    }
    *(undefined4 *)(DAT_80436354 + 0x20) = 0x65;
    PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | 0x80;
    zz_01b0f34_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  iVar2 = zz_01b1014_();
  if (iVar2 != 1) {
    PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] & 0x7f;
    *(undefined2 *)(DAT_80436354 + 0x2a) = 0;
  }
  return iVar2;
}



// ==== 801819fc  systemCallbackFunc(MCCSysEvent) ====

void systemCallbackFunc_MCCSysEvent_(undefined4 param_1)

{
  *(undefined4 *)(DAT_80436354 + 0x88) = param_1;
  return;
}



// ==== 80181a08  zz_0181a08_ ====

void zz_0181a08_(void)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = 0;
  bVar1 = PTR_DAT_80433930[2];
  if ((bVar1 & 1) == 0) {
    iVar2 = 1;
    if ((bVar1 & 2) == 0) {
      iVar2 = 2;
      if ((bVar1 & 4) == 0) {
        iVar2 = 3;
        if ((bVar1 & 8) == 0) {
          iVar2 = 4;
        }
      }
    }
  }
  if (iVar2 == 4) {
    iVar2 = 0;
  }
  *(int *)(DAT_80436354 + 0x3c) = iVar2;
  return;
}



// ==== 80181a74  zz_0181a74_ ====

int zz_0181a74_(void)

{
  int iVar1;
  
  if (*(int *)(DAT_80436354 + 0x40) == 2) {
    if (*(int *)(DAT_80436354 + 0x68) != 0) {
      return *(int *)(DAT_80436354 + 0x68);
    }
    return 1;
  }
  iVar1 = *(int *)(DAT_80436354 + 0x68) + 1;
  if (iVar1 < 9) {
    return iVar1;
  }
  return 8;
}



// ==== 80181ab4  zz_0181ab4_ ====

undefined4 zz_0181ab4_(void)

{
  if (*(int *)(DAT_80436354 + 0x40) != 2) {
    return *(undefined4 *)(DAT_80436354 + 0x114);
  }
  return 0x7fff;
}



// ==== 80181b84  zz_0181b84_ ====

uint zz_0181b84_(void)

{
  uint uVar1;
  
  if (*(int *)(DAT_80436354 + 0x40) == 2) {
    uVar1 = *(uint *)(DAT_80436354 + 0x4624) | 1;
  }
  else if (*(int *)(DAT_80436354 + 0x68) == 0) {
    uVar1 = *(uint *)(DAT_80436354 + 0x90) & 0xfffffffe;
  }
  else {
    uVar1 = *(uint *)(DAT_80436354 + 0x90) | 1;
  }
  if (uVar1 != 0) {
    return uVar1;
  }
  return 2;
}



// ==== 80181bd0  zz_0181bd0_ ====

int zz_0181bd0_(int param_1)

{
  int iVar1;
  int *piVar2;
  
  if (*(int *)(DAT_80436354 + 0x40) != 2) {
    return (int)*(char *)(DAT_80436354 + param_1 + 0x94);
  }
  iVar1 = -1;
  for (piVar2 = (int *)(&PTR_PTR_8035b158)[param_1]; *piVar2 != 0; piVar2 = piVar2 + 1) {
    iVar1 = iVar1 + 1;
  }
  if (-1 < iVar1) {
    return iVar1;
  }
  return 0;
}



// ==== 80181c30  zz_0181c30_ ====

undefined4 zz_0181c30_(void)

{
  if (*(int *)(DAT_80436354 + 0x40) != 2) {
    return *(undefined4 *)(DAT_80436354 + 0x78);
  }
  return 0x898;
}



// ==== 80181c54  zz_0181c70_ ====

undefined4 zz_0181c70_(void)

{
  if (*(int *)(DAT_80436354 + 0x40) != 2) {
    return *(undefined4 *)(DAT_80436354 + 0x50);
  }
  return 1;
}



// ==== 80181c78  zz_0181c78_ ====

void zz_0181c78_(void)

{
  zz_0088398_(DAT_80436238 + 0xfe800,0x100000,5);
  return;
}



// ==== 80181cac  zz_0181cac_ ====

void zz_0181cac_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar1;
  undefined8 uVar2;
  
  zz_000bb70_();
  zz_00059b8_();
  zz_0197854_(2);
  zz_0009f40_();
  uVar2 = zz_007fd5c_();
  zz_007fd6c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              glxSwapWaitDrawDone_void_,0,param_11,param_12,param_13,param_14,param_15,param_16);
  uVar2 = zz_0181c78_();
  if (-1 < param_9) {
    uVar1 = extraout_r4;
    if (param_9 < 2) {
      uVar2 = zz_0044b1c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,
                          extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
      uVar1 = extraout_r4_00;
    }
    zz_0043ad0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar1,param_11
                ,param_12,param_13,param_14,param_15,param_16);
    set_global_menu_mode(4);
  }
  return;
}



// ==== 80181d2c  zz_0181d2c_ ====

void zz_0181d2c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_80436354 + 0x118);
  if (0xb < iVar1) {
    iVar1 = 0xb;
  }
  zz_0043c8c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80181d60  zz_0181d60_ ====

void zz_0181d60_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = **(int **)(DAT_80436354 + 0x9ec);
  uVar2 = zz_0043ea4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)*(char *)(iVar1 + 1),param_10,param_11,param_12,param_13,param_14,
                      param_15,param_16);
  iVar1 = *(char *)(iVar1 + 0xd) + -3;
  if (-1 < iVar1) {
    zz_0043fb0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,extraout_r4,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80181db0  glxSwapWaitDrawDone(void) ====

void glxSwapWaitDrawDone_void_(void)

{
  zz_01978d0_();
  zz_0008b58_();
  zz_0009f40_();
  return;
}



// ==== 80181dd8  zz_0181dd8_ ====

void zz_0181dd8_(void)

{
  zz_0181dfc_();
  zz_0181e30_();
  return;
}



// ==== 80181dfc  zz_0181dfc_ ====

void zz_0181dfc_(void)

{
  zz_0089898_(0x39);
  zz_0089898_(0x38);
  zz_0089554_();
  zz_0089658_();
  return;
}



// ==== 80181e30  zz_0181e30_ ====

void zz_0181e30_(void)

{
  zz_008a16c_();
  zz_0089c00_(0x39);
  zz_0089c00_(0x38);
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  return;
}



// ==== 80181e78  FUN_80181e78 ====

/* WARNING: Removing unreachable block (ram,0x80181f98) */
/* WARNING: Removing unreachable block (ram,0x80181f90) */
/* WARNING: Removing unreachable block (ram,0x80181f88) */
/* WARNING: Removing unreachable block (ram,0x80181f80) */
/* WARNING: Removing unreachable block (ram,0x80181ea0) */
/* WARNING: Removing unreachable block (ram,0x80181e98) */
/* WARNING: Removing unreachable block (ram,0x80181e90) */
/* WARNING: Removing unreachable block (ram,0x80181e88) */

void FUN_80181e78(void)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  
  pfVar3 = (float *)&DAT_803d4838;
  dVar4 = 1.0 / SQRT(DOUBLE_8043ae58);
  FLOAT_80436350 = FLOAT_8043ae50;
  iVar2 = 0;
  dVar6 = (double)FLOAT_8043ae70;
  dVar4 = DOUBLE_8043ae60 * dVar4 * -(DOUBLE_8043ae58 * dVar4 * dVar4 - DOUBLE_8043ae68);
  dVar4 = DOUBLE_8043ae60 * dVar4 * -(DOUBLE_8043ae58 * dVar4 * dVar4 - DOUBLE_8043ae68);
  dVar4 = DOUBLE_8043ae60 * dVar4 * -(DOUBLE_8043ae58 * dVar4 * dVar4 - DOUBLE_8043ae68);
  dVar7 = DOUBLE_8043ae58 *
          DOUBLE_8043ae60 * dVar4 * -(DOUBLE_8043ae58 * dVar4 * dVar4 - DOUBLE_8043ae68);
  dVar4 = DOUBLE_8043ae80;
  dVar8 = DOUBLE_8043ae60;
  do {
    dVar5 = (double)gnt4_pow_bl((double)(float)((double)(float)((double)CONCAT44(0x43300000,
                                                                                 iVar2 - 0x20U ^
                                                                                 0x80000000) - dVar4
                                                               ) / dVar6),DOUBLE_8043ae78);
    dVar5 = (double)gnt4_exp_bl(-dVar5 * dVar8);
    iVar2 = iVar2 + 1;
    *pfVar3 = (float)(dVar7 * dVar5);
    fVar1 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    FLOAT_80436350 = FLOAT_80436350 + fVar1;
  } while (iVar2 < 0x40);
  return;
}



// ==== 80181fbc  zz_0181fbc_ ====

void zz_0181fbc_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043ae50;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(float *)(param_1 + 0xd8) = fVar1;
  return;
}



// ==== 80181fd0  zz_0181fd0_ ====

undefined4 zz_0181fd0_(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  
  if (param_2 == 0) {
    return 1;
  }
  iVar2 = 0x40 / param_2;
  if (0 < iVar2) {
    do {
      sVar1 = *(short *)(param_1 + 0x1e);
      if ((sVar1 < 0) || (0x3f < sVar1)) {
        return 1;
      }
      *(float *)(param_1 + 0xd8) = *(float *)(param_1 + 0xd8) + (float)(&DAT_803d4838)[sVar1];
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return 0;
}



// ==== 80182040  zz_0182040_ ====

undefined4 zz_0182040_(short *param_1,float *param_2,int param_3)

{
  short sVar1;
  int iVar2;
  
  if (param_3 == 0) {
    return 1;
  }
  iVar2 = 0x40 / param_3;
  if (0 < iVar2) {
    do {
      sVar1 = *param_1;
      if ((sVar1 < 0) || (0x3f < sVar1)) {
        return 1;
      }
      *param_2 = *param_2 + (float)(&DAT_803d4838)[sVar1];
      *param_1 = *param_1 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return 0;
}



// ==== 801820b0  zz_01820b0_ ====

double zz_01820b0_(double param_1,int param_2)

{
  return (double)((float)(param_1 * (double)*(float *)(param_2 + 0xd8)) / FLOAT_80436350);
}



// ==== 801820c4  zz_01820c4_ ====

double zz_01820c4_(double param_1,double param_2)

{
  return (double)((float)(param_2 * param_1) / FLOAT_80436350);
}



// ==== 801820d4  zz_01820d4_ ====

void zz_01820d4_(void)

{
  gnt4_memcpy((void *)(DAT_80436354 + 0x2d1c),(void *)(DAT_80436354 + 0x1518),0x1800);
  *(undefined4 *)(DAT_80436354 + 0x451c) = *(undefined4 *)(DAT_80436354 + 0x2d18);
  return;
}



// ==== 80182110  zz_0182110_ ====

void zz_0182110_(void)

{
  gnt4_memcpy((void *)(DAT_80436354 + 0x1518),(void *)(DAT_80436354 + 0x2d1c),0x1800);
  *(undefined4 *)(DAT_80436354 + 0x2d18) = *(undefined4 *)(DAT_80436354 + 0x451c);
  return;
}



// ==== 8018214c  zz_018214c_ ====

void zz_018214c_(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint unaff_r31;
  uint uVar4;
  
  if (PTR_DAT_80433930[0x32] == '\0') {
    uVar3 = 0;
    uVar1 = param_2 << 0x1c | param_1 << 0x10;
    uVar4 = *(uint *)(DAT_80436354 + 0x2d18);
    iVar2 = DAT_80436354;
    while ((uVar4 != 0 &&
           (unaff_r31 = *(uint *)(iVar2 + 0x1518) ^ 0xffffffff, uVar1 != (unaff_r31 & 0xffff0000))))
    {
      iVar2 = iVar2 + 4;
      uVar3 = uVar3 + 1;
      uVar4 = uVar4 - 1;
    }
    if (*(uint *)(DAT_80436354 + 0x2d18) <= uVar3) {
      *(int *)(DAT_80436354 + 0x2d18) = *(int *)(DAT_80436354 + 0x2d18) + 1;
      unaff_r31 = uVar1;
    }
    uVar4 = zz_00055fc_();
    iVar2 = (uVar4 & 0xf) + 1;
    if ((unaff_r31 & 0xffff) < 0x10000U - iVar2) {
      unaff_r31 = unaff_r31 + iVar2;
    }
    *(uint *)(DAT_80436354 + uVar3 * 4 + 0x1518) = unaff_r31 ^ 0xffffffff;
  }
  return;
}



// ==== 80182228  zz_0182228_ ====

undefined4 zz_0182228_(undefined2 *param_1,byte *param_2,char *param_3)

{
  short sVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  uint uVar8;
  
  iVar6 = 0;
  iVar3 = *(int *)(DAT_80436354 + 0x2d18);
  iVar5 = DAT_80436354;
  do {
    if (iVar3 == 0) {
      return 0;
    }
    uVar4 = *(uint *)(iVar5 + 0x1518) ^ 0xffffffff;
    uVar8 = uVar4 >> 0x10 & 0xfff;
    bVar2 = (byte)(uVar4 >> 0x1c);
    for (psVar7 = &DAT_8035b2dc; -1 < *psVar7; psVar7 = psVar7 + 8) {
      sVar1 = *(short *)((int)psVar7 + (uVar4 >> 0x1b & 0x1e) + 4);
      if (((-1 < sVar1) && ((int)*psVar7 == uVar8)) && ((uint)(int)sVar1 <= (uVar4 & 0xffff))) {
        *(uint *)(DAT_80436354 + iVar6 * 4 + 0x1518) =
             (uVar4 & 0xf0000000 | uVar8 << 0x10) ^ 0xffffffff;
        sVar1 = psVar7[1];
        uVar4 = (uint)sVar1;
        if (uVar4 == 1) {
          *param_1 = (short)uVar8;
          *param_2 = bVar2;
          *param_3 = '\0';
          return 1;
        }
        if (((int)uVar4 < 1) && (-1 < (int)uVar4)) {
          return 0;
        }
        *param_1 = (short)uVar8;
        *param_2 = bVar2;
        uVar8 = zz_00055fc_();
        *param_3 = ((char)(uVar8 >> 4) - (char)((uVar8 >> 4) / uVar4) * (char)sVar1) + '\x01';
        return 1;
      }
    }
    iVar5 = iVar5 + 4;
    iVar6 = iVar6 + 1;
    iVar3 = iVar3 + -1;
  } while( true );
}



// ==== 80182378  zz_0182378_ ====

int zz_0182378_(short *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  
  psVar2 = (short *)(param_2 + 0x870);
  iVar1 = 0;
  iVar3 = 0x28;
  while( true ) {
    if ((*psVar2 == param_3) && ((param_4 < 0 || (param_4 == *(char *)(psVar2 + 1))))) {
      return iVar1 + 0x10000;
    }
    if ((psVar2[0x10] == param_3) && ((param_4 < 0 || (param_4 == *(char *)(psVar2 + 0x11))))) {
      return iVar1 + 0x10001;
    }
    if ((psVar2[0x20] == param_3) && ((param_4 < 0 || (param_4 == *(char *)(psVar2 + 0x21))))) {
      return iVar1 + 0x10002;
    }
    if ((psVar2[0x30] == param_3) && ((param_4 < 0 || (param_4 == *(char *)(psVar2 + 0x31)))))
    break;
    if ((psVar2[0x40] == param_3) && ((param_4 < 0 || (param_4 == *(char *)(psVar2 + 0x41))))) {
      return iVar1 + 0x10004;
    }
    iVar1 = iVar1 + 5;
    psVar2 = psVar2 + 0x50;
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      iVar1 = 0;
      iVar3 = 400;
      while( true ) {
        if ((*param_1 == param_3) && ((param_4 < 0 || (param_4 == *(char *)(param_1 + 1))))) {
          return iVar1 + 0x20000;
        }
        if ((param_1[8] == param_3) && ((param_4 < 0 || (param_4 == *(char *)(param_1 + 9))))) {
          return iVar1 + 0x20001;
        }
        if ((param_1[0x10] == param_3) && ((param_4 < 0 || (param_4 == *(char *)(param_1 + 0x11)))))
        {
          return iVar1 + 0x20002;
        }
        if ((param_1[0x18] == param_3) && ((param_4 < 0 || (param_4 == *(char *)(param_1 + 0x19)))))
        break;
        if ((param_1[0x20] == param_3) && ((param_4 < 0 || (param_4 == *(char *)(param_1 + 0x21)))))
        {
          return iVar1 + 0x20004;
        }
        iVar1 = iVar1 + 5;
        param_1 = param_1 + 0x28;
        iVar3 = iVar3 + -1;
        if (iVar3 == 0) {
          return 0;
        }
      }
      return iVar1 + 0x20003;
    }
  }
  return iVar1 + 0x10003;
}



// ==== 8018258c  zz_018258c_ ====

void zz_018258c_(void)

{
  if (((*(int *)(DAT_80436354 + 0x40) != 2) && ('\x01' < *DAT_80436354)) && (*DAT_80436354 < '\t'))
  {
    zz_01825d8_();
  }
  return;
}



// ==== 801825d8  zz_01825d8_ ====

void zz_01825d8_(void)

{
  uint uVar1;
  
  uVar1 = *(int *)(DAT_80436354 + 0x143c) + 1;
  *(uint *)(DAT_80436354 + 0x143c) = uVar1;
  if (uVar1 < 0xe10) {
    return;
  }
  *(undefined4 *)(DAT_80436354 + 0x143c) = 0;
  *(int *)(DAT_80436354 + 0x1440) = *(int *)(DAT_80436354 + 0x1440) + 1;
  return;
}



// ==== 80182610  zz_0182610_ ====

void zz_0182610_(int param_1)

{
  *(uint *)(DAT_80436354 + 0x150c) = *(uint *)(DAT_80436354 + 0x150c) | 1 << param_1;
  return;
}



// ==== 8018262c  zz_018262c_ ====

void zz_018262c_(int param_1)

{
  *(uint *)(DAT_80436354 + 0x1510) = *(uint *)(DAT_80436354 + 0x1510) | 1 << param_1;
  return;
}



// ==== 80182648  zz_0182648_ ====

void zz_0182648_(int param_1)

{
  if (*(int *)(DAT_80436354 + 0x40) == 2) {
    return;
  }
  if (param_1 != 0) {
    *(int *)(DAT_80436354 + 0x1508) = *(int *)(DAT_80436354 + 0x1508) + 1;
    return;
  }
  *(int *)(DAT_80436354 + 0x1504) = *(int *)(DAT_80436354 + 0x1504) + 1;
  return;
}



// ==== 80182680  zz_0182680_ ====

void zz_0182680_(int param_1,undefined1 param_2,undefined4 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,0x18,0,6);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x38;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80182788;
    *(code **)(puVar1 + 0x10c) = FUN_80182b9c;
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
    *(undefined4 *)(puVar1 + 0x148) = param_3;
  }
  return;
}



// ==== 80182788  FUN_80182788 ====

void FUN_80182788(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8035c140)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80182830  FUN_80182830 ====

void FUN_80182830(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  fVar1 = FLOAT_8043aea0;
  iVar5 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined1 *)(param_9 + 0x13) = 0;
  *(char *)(param_9 + 0x12) = (char)*(undefined4 *)(&DAT_8035c038 + iVar4);
  *(undefined2 *)(param_9 + 0x272) = 0xffff;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xc0) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(undefined *)(param_9 + 0x89) = (&DAT_8035c021)[iVar4];
  uVar2 = *(undefined4 *)(&DAT_8035c02c + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8035c028 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8035c030 + iVar4);
  *(undefined2 *)(param_9 + 0x70) = *(undefined2 *)(&DAT_8035c034 + iVar4);
  *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(&DAT_8035c036 + iVar4);
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(&DAT_8035c024 + iVar4);
  *(undefined *)(param_9 + 0x14c) = (&DAT_8035c020)[iVar4];
  *(byte *)(param_9 + 0x14d) = (&DAT_8035c022)[iVar4] & 0x80;
  *(byte *)(param_9 + 0x14e) = (&DAT_8035c022)[iVar4] & 0x7f;
  *(undefined *)(param_9 + 0x14f) = (&DAT_8035c023)[iVar4];
  if (*(char *)(param_9 + 0x14f) < '\0') {
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar3 = zz_0006dc8_(400);
    *(int **)(param_9 + 0xdc) = piVar3;
  }
  zz_0182e10_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  *(code **)(param_9 + 0x100) = FUN_80182c5c;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  iVar4 = DAT_803bb374;
  if (*(char *)(param_9 + 0x14d) == '\0') {
    iVar4 = zz_0006f78_(iVar5);
  }
  zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
              *(int *)(param_9 + 0xf4),(float *)(int)*(char *)(param_9 + 0x14e),
              (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  return;
}



// ==== 801829ac  FUN_801829ac ====

void FUN_801829ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  float fVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  
  *(undefined2 *)(param_9 + 0x272) = 0xffff;
  if ((*(uint *)(*(int *)(param_9 + 0x8c) + 0x5e0) & 3) != 0) {
    *(undefined2 *)(param_9 + 0x272) = 0;
  }
  sVar4 = *(short *)(param_9 + 0x1c) + 1;
  iVar5 = (int)sVar4;
  *(short *)(param_9 + 0x1c) = sVar4;
  iVar3 = iVar5 / 5 + (iVar5 >> 0x1f);
  if (iVar5 == (iVar3 - (iVar3 >> 0x1f)) * 5) {
    zz_0182e10_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (**(short **)(param_9 + 0x148) < 1) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined2 *)(param_9 + 0x1e) = 0;
    *(undefined1 *)(param_9 + 0x19) = 0;
    zz_008aff0_(param_9);
  }
  else {
    fVar2 = ((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1c) ^ 0x80000000) -
                    DOUBLE_8043aea8) / FLOAT_8043aea4) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0xb4) = fVar2;
    if (*(float *)(param_9 + 0x144) <= fVar2) {
      *(float *)(param_9 + 0xb4) = *(float *)(param_9 + 0x144);
    }
    uVar1 = *(undefined4 *)(param_9 + 0xb4);
    *(undefined4 *)(param_9 + 0xc0) = uVar1;
    *(undefined4 *)(param_9 + 0x60) = uVar1;
    *(undefined4 *)(param_9 + 0x5c) = uVar1;
    *(undefined4 *)(param_9 + 0x58) = uVar1;
  }
  zz_0182f14_(param_9);
  return;
}



// ==== 80182ac4  FUN_80182ac4 ====

void FUN_80182ac4(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar1 = FLOAT_8043aeb0;
  dVar3 = DOUBLE_8043aea8;
  fVar2 = FLOAT_8043aea0;
  *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + 1;
  fVar1 = -(((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
                    dVar3) / fVar1) * *(float *)(param_1 + 0x144) - *(float *)(param_1 + 0xc0));
  *(float *)(param_1 + 0xb4) = fVar1;
  if (fVar1 <= fVar2) {
    *(undefined1 *)(param_1 + 0x18) = 3;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  zz_0182f14_(param_1);
  return;
}



// ==== 80182b54  FUN_80182b54 ====

void FUN_80182b54(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80182b9c  FUN_80182b9c ====

void FUN_80182b9c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *(int *)(param_9 + 0x8c);
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar2 = 0;
    iVar4 = 0;
    iVar3 = param_9;
    do {
      if (((int)*(char *)(param_9 + 0x13) & 1 << iVar2) != 0) {
        zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar3 + 0xe0),
                    (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar4),param_11,param_12,
                    param_13,param_14,param_15,param_16);
        param_1 = zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 4;
      iVar4 = iVar4 + 0x50;
    } while (iVar2 < 5);
  }
  if ((*(char *)(param_9 + 0x12) == '\0') && ((*(uint *)(iVar1 + 0x5e0) & 3) != 0)) {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xf4),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xf4),0x44);
  }
  return;
}



// ==== 80182c5c  FUN_80182c5c ====

void FUN_80182c5c(int param_1)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float local_68;
  float local_64;
  float local_60;
  float afStack_5c [13];
  undefined4 local_28;
  uint uStack_24;
  
  zz_00455fc_((float *)(*(int *)(param_1 + 0x8c) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
              (float *)(param_1 + 0x114),(float *)(param_1 + 100));
  if (*(short *)(param_1 + 0x70) != 0) {
    uStack_24 = (int)*(short *)(param_1 + 0x70) ^ 0x80000000;
    local_28 = 0x43300000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_8043aeb4 *
                                (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043aea8)),
                        afStack_5c,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_5c,(float *)(param_1 + 0x114));
  }
  if (*(short *)(param_1 + 0x72) != 0) {
    uStack_24 = (int)*(short *)(param_1 + 0x72) ^ 0x80000000;
    local_28 = 0x43300000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_8043aeb4 *
                                (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043aea8)),
                        afStack_5c,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_5c,(float *)(param_1 + 0x114));
  }
  if (*(int *)(param_1 + 0xdc) != 0) {
    iVar2 = 0;
    iVar3 = 0;
    do {
      if (((int)*(char *)(param_1 + 0x13) & 1 << iVar2) != 0) {
        pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar3);
        zz_00457d4_('z',(float *)(param_1 + 0x114),pfVar1,*(short *)(pfVar1 + 0x12));
        zz_00456a0_(pfVar1,pfVar1,pfVar1 + 0xe);
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x50;
    } while (iVar2 < 5);
  }
  zz_00455fc_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)&DAT_8035c160);
  local_68 = *(float *)(param_1 + 0x58) *
             *(float *)(&DAT_8035c150 + ((int)*(short *)(param_1 + 0x1c) & 3U) * 4);
  local_64 = *(float *)(param_1 + 0x5c) *
             *(float *)(&DAT_8035c150 + ((int)*(short *)(param_1 + 0x1c) & 3U) * 4);
  local_60 = FLOAT_8043aeb8 * *(float *)(param_1 + 0x60);
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),&local_68);
  return;
}



// ==== 80182e10  zz_0182e10_ ====

void zz_0182e10_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    for (iVar4 = 0; iVar4 < 5; iVar4 = iVar4 + 1) {
      if (((int)(char)*(byte *)(param_9 + 0x13) & 1 << iVar4) == 0) {
        iVar3 = *(int *)(param_9 + 0x90);
        iVar2 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
        *(byte *)(param_9 + 0x13) = *(byte *)(param_9 + 0x13) | (byte)(1 << iVar4);
        iVar2 = iVar2 + iVar4 * 0x50;
        *(undefined2 *)(iVar2 + 0x44) = 0;
        *(undefined2 *)(iVar2 + 0x46) = 0x14;
        uVar1 = zz_00055fc_();
        *(short *)(iVar2 + 0x48) = (short)(uVar1 << 8);
        uVar5 = zz_0018f88_((int *)(iVar2 + 0x30),
                            (int)(&PTR_DAT_8035c134)[*(char *)(param_9 + 0x11)],
                            (float *)(iVar2 + 0x38));
        iVar2 = DAT_803bb374;
        if (*(char *)(param_9 + 0x14d) == '\0') {
          iVar2 = zz_0006f78_(iVar3);
        }
        zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                    *(int *)(param_9 + iVar4 * 4 + 0xe0),(float *)(int)*(char *)(param_9 + 0x14f),
                    (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
        iVar4 = 5;
      }
    }
  }
  return;
}



// ==== 80182f14  zz_0182f14_ ====

void zz_0182f14_(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0xdc) != 0) {
    iVar3 = 0;
    iVar4 = 0;
    do {
      if (((int)*(char *)(param_1 + 0x13) & 1 << iVar3) != 0) {
        iVar2 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar4;
        sVar1 = *(short *)(iVar2 + 0x44) + 1;
        *(short *)(iVar2 + 0x44) = sVar1;
        if (*(short *)(iVar2 + 0x46) <= sVar1) {
          *(byte *)(param_1 + 0x13) = *(byte *)(param_1 + 0x13) & ~(byte)(1 << iVar3);
        }
        zz_0018fd8_((int *)(iVar2 + 0x30),(int)*(short *)(iVar2 + 0x44),(float *)(iVar2 + 0x38));
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0x50;
    } while (iVar3 < 5);
  }
  return;
}



// ==== 80182fcc  zz_0182fcc_ ====

bool zz_0182fcc_(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x11] = param_3;
    puVar1[0x13] = param_2;
    puVar1[0x10] = 0x5c;
    *(code **)(puVar1 + 0xc) = FUN_801830e4;
    *(code **)(puVar1 + 0x10c) = FUN_80183680;
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
  return puVar1 != (undefined1 *)0x0;
}



// ==== 801830e4  FUN_801830e4 ====

void FUN_801830e4(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8035c218)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8018317c  FUN_8018317c ====

void FUN_8018317c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  undefined *puVar8;
  int iVar9;
  undefined8 uVar10;
  
  puVar8 = &DAT_8035c1e0;
  puVar6 = &DAT_8035c170;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar9 = *(int *)(param_9 + 0x90);
  iVar7 = (int)*(char *)(param_9 + 0x13);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x98) = 5;
  iVar3 = iVar7 * 0x1c;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar2 = iVar3;
  iVar5 = iVar4;
  zz_0089100_(param_9,0,1);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar9 + (char)(&DAT_8035c171)[iVar3] * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fca3e88),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)
        (iVar9 + (char)(&DAT_8035c171)[iVar3] * 0x30 + (char)(&DAT_8035c174)[iVar3] * 4 + 0x8d4);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)
        (iVar9 + (char)(&DAT_8035c171)[iVar3] * 0x30 + (char)(&DAT_8035c174)[iVar3] * 4 + 0x8e4);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)
        (iVar9 + (char)(&DAT_8035c171)[iVar3] * 0x30 + (char)(&DAT_8035c174)[iVar3] * 4 + 0x8f4);
  if ((char)(&DAT_8035c175)[iVar3] < '\0') {
    gnt4_PSQUATScale_bl((double)FLOAT_8043aec0,(float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
  }
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)
        (iVar9 + (char)(&DAT_8035c171)[iVar3] * 0x30 + (char)(&DAT_8035c172)[iVar3] * 4 + 0x8d4);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)
        (iVar9 + (char)(&DAT_8035c171)[iVar3] * 0x30 + (char)(&DAT_8035c172)[iVar3] * 4 + 0x8e4);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)
        (iVar9 + (char)(&DAT_8035c171)[iVar3] * 0x30 + (char)(&DAT_8035c172)[iVar3] * 4 + 0x8f4);
  if ((char)(&DAT_8035c173)[iVar3] < '\0') {
    gnt4_PSQUATScale_bl((double)FLOAT_8043aec0,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  }
  uVar10 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8035c1f0 + iVar4),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8035c1f0 + iVar4);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8035c1e2 + iVar4);
  *(undefined2 *)(param_9 + 0x1e) = *(undefined2 *)(&DAT_8035c1e6 + iVar4);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8035c1e4 + iVar4);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar1 = zz_0006f98_(iVar9);
  zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0x600)
              ,*(int *)(param_9 + 0xe0),(int)(char)(&DAT_8035c170)[iVar3],iVar2,iVar5,puVar6,iVar7,
              puVar8);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  *(undefined1 *)(param_9 + 0x146) = 0;
  *(undefined1 *)(param_9 + 0x147) = 0;
  *(undefined2 *)(param_9 + 0x144) = 0;
  *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(&DAT_8035c1f4 + iVar4);
  *(undefined1 *)(param_9 + 0x19) = 0;
  iVar2 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8035c1e0 + iVar4));
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0xa8) = 1;
    zz_0048288_(param_9);
    zz_00aedc0_(iVar9,(float *)(param_9 + 0x114),3,*(undefined1 *)(param_9 + 0x88));
    zz_00f036c_(param_9,0xba);
  }
  return;
}



// ==== 80183454  FUN_80183454 ====

void FUN_80183454(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  
  bVar1 = false;
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    bVar1 = true;
    sVar4 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar4;
    if (sVar4 < 0) {
      zz_01836f4_(param_1);
      return;
    }
  }
  iVar3 = zz_0083244_((float *)(param_1 + 0x20));
  if (iVar3 == 0) {
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
    if (*(short *)(param_1 + 0x1c) < 1) {
      zz_01836f4_(param_1);
    }
    else {
      if (*(char *)(param_1 + 0x19) == '\0') {
        if (*(char *)(param_1 + 0x147) == '\0') {
          if (bVar1) {
            *(undefined1 *)(param_1 + 0x146) = 4;
            *(undefined1 *)(param_1 + 0x19) = 1;
          }
        }
        else {
          *(char *)(param_1 + 0x147) = *(char *)(param_1 + 0x147) + -1;
        }
      }
      else if (*(char *)(param_1 + 0x146) == '\0') {
        *(undefined1 *)(param_1 + 0x19) = 0;
        *(undefined1 *)(param_1 + 0x147) = 1;
      }
      else {
        *(char *)(param_1 + 0x146) = *(char *)(param_1 + 0x146) + -1;
      }
      if (*(char *)(param_1 + 0x146) == '\0') {
        if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x148)) {
          *(float *)(param_1 + 0x44) =
               *(float *)(param_1 + 0x44) + *(float *)(&DAT_8035c1f8 + iVar2);
        }
        else {
          *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x148);
        }
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        FUN_80083874((double)*(float *)(&DAT_8035c1ec + iVar2),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_8035c1e8 + iVar2),param_1,
                     (char)*(undefined2 *)(&DAT_8035c1e4 + iVar2));
        *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
        if (*(char *)(param_1 + 0x13) == '\0') {
          *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x1c00;
        }
        else {
          *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + -0x1c00;
        }
      }
      zz_00833ec_(param_1);
      zz_0083610_(param_1,(float *)(param_1 + 0x148));
      iVar2 = zz_0083714_(param_1);
      if (iVar2 != 0) {
        zz_01836f4_(param_1);
      }
    }
  }
  else {
    zz_01836f4_(param_1);
  }
  return;
}



// ==== 80183654  FUN_80183654 ====

void FUN_80183654(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 80183660  FUN_80183660 ====

void FUN_80183660(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80183680  FUN_80183680 ====

void FUN_80183680(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = 0x44;
  cVar1 = *(char *)(*(int *)(param_9 + 0x90) + 0x3ec);
  if (((cVar1 == '\x02') || (cVar1 == '\x03')) || (cVar1 == '\x05')) {
    uVar2 = 1;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar2);
  return;
}



// ==== 801836f4  zz_01836f4_ ====

void zz_01836f4_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80183730  zz_0183730_ ====

bool zz_0183730_(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x1e;
    *(code **)(puVar1 + 0xc) = FUN_80183980;
    *(undefined4 *)(puVar1 + 0x10c) = 0;
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
    puVar1[0x89] = param_3;
  }
  return puVar1 != (undefined1 *)0x0;
}



// ==== 8018384c  zz_018384c_ ====

bool zz_018384c_(int param_1,undefined1 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x13] = param_2;
    puVar2[0x11] = 1;
    puVar2[0x10] = 0x1e;
    *(code **)(puVar2 + 0xc) = FUN_80183980;
    *(code **)(puVar2 + 0x10c) = FUN_80184210;
    *(int *)(puVar2 + 0x8c) = param_1;
    *(undefined4 *)(puVar2 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar2 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar2[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar2[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar2[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar2 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar2 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar2 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar2 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar2 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar2[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    uVar1 = param_3[1];
    *(undefined4 *)(puVar2 + 0x20) = *param_3;
    *(undefined4 *)(puVar2 + 0x24) = uVar1;
    *(undefined4 *)(puVar2 + 0x28) = param_3[2];
  }
  return puVar2 != (undefined1 *)0x0;
}



// ==== 80183980  FUN_80183980 ====

void FUN_80183980(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8035c2e8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80183a18  FUN_80183a18 ====

void FUN_80183a18(int param_1)

{
  (*(code *)(&PTR_FUN_8035c2f8)[*(char *)(param_1 + 0x13) * 2 + (int)*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 80183a64  FUN_80183a64 ====

void FUN_80183a64(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  
  iVar8 = *(int *)(param_1 + 0x8c);
  iVar7 = *(char *)(param_1 + 0x13) * 0x18;
  iVar5 = zz_008ac80_(param_1,(int)*(short *)(&DAT_8035c288 + iVar7));
  if (iVar5 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
    *(undefined1 *)(param_1 + 0x84) = 0x1e;
    *(code **)(param_1 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_1,0,1);
    if (*(char *)(iVar8 + 0x83) == '\0') {
      if (*(char *)(param_1 + 0x89) < '\0') {
        pfVar6 = (float *)(iVar8 + *(short *)(&DAT_8035c22a + iVar7) * 0x30 + 0x8d4);
      }
      else {
        pfVar6 = (float *)(iVar8 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4);
      }
    }
    else {
      pfVar6 = (float *)(iVar8 + 0x114);
    }
    gnt4_PSMTXMultVec_bl(pfVar6,(float *)(iVar7 + -0x7fca3dd4),(float *)(param_1 + 0x20));
    zz_0083d60_(param_1,*(int *)(iVar8 + 0x90),0);
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8035c298 + iVar7),(float *)(param_1 + 0x38),
                        (float *)(param_1 + 0x38));
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(&DAT_8035c298 + iVar7);
    *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(&DAT_8035c28c + iVar7);
    *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_8035c28e + iVar7);
    *(undefined2 *)(param_1 + 0x1e) = 0;
    fVar4 = FLOAT_8043aed0;
    if ('\x01' < *(char *)(param_1 + 0x13)) {
      fVar1 = FLOAT_8043aec8 * *(float *)(*(int *)(iVar8 + 0x90) + 0x7fc);
      fVar2 = FLOAT_8043aecc * fVar1;
      fVar3 = FLOAT_8043aed4 * fVar1;
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * fVar1;
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * fVar1;
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * fVar1;
      *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xb4) * fVar1;
      *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xc0) * fVar1;
      *(float *)(param_1 + 0x44) = fVar2;
      *(float *)(param_1 + 0x148) = fVar4;
      *(float *)(param_1 + 0x14c) = fVar3;
    }
    zz_00f036c_(param_1,0xa1);
  }
  return;
}



// ==== 80183c4c  FUN_80183c4c ====

void FUN_80183c4c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  iVar5 = *(char *)(param_1 + 0x13) * 0x18;
  iVar3 = zz_008ac80_(param_1,(int)*(short *)(&DAT_8035c28a + iVar5));
  if (iVar3 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
    *(undefined1 *)(param_1 + 0x84) = 0x1e;
    *(code **)(param_1 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_1,0,1);
    *(undefined2 *)(param_1 + 0x1e) = 0xf;
    uVar4 = zz_00055fc_();
    fVar1 = FLOAT_8043aed8;
    *(short *)(param_1 + 0x72) = (short)(uVar4 << 8);
    *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) - fVar1;
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) - fVar1;
    *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) - fVar1;
    uVar4 = zz_00055fc_();
    *(float *)(param_1 + 0x20) =
         *(float *)(param_1 + 0x20) +
         FLOAT_8043aedc * (float)((double)CONCAT44(0x43300000,uVar4 & 0xf) - DOUBLE_8043aee8);
    uVar4 = zz_00055fc_();
    *(float *)(param_1 + 0x24) =
         *(float *)(param_1 + 0x24) +
         FLOAT_8043aedc * (float)((double)CONCAT44(0x43300000,uVar4 & 0xf) - DOUBLE_8043aee8);
    uVar4 = zz_00055fc_();
    fVar2 = FLOAT_8043aee0;
    dVar7 = (double)(float)((double)CONCAT44(0x43300000,uVar4 & 0xf) - DOUBLE_8043aee8);
    dVar6 = (double)(float)((double)FLOAT_8043aedc * dVar7);
    fVar1 = (float)((double)*(float *)(param_1 + 0x28) + dVar6);
    *(float *)(param_1 + 0x28) = fVar1;
    *(float *)(param_1 + 0x144) = fVar2;
    uVar4 = *(uint *)(&DAT_8035c29c + iVar5);
    if ((int)uVar4 < 0) {
      uVar4 = (uint)*(char *)(param_1 + 0x88);
    }
    zz_000726c_((double)fVar1,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb374,
                *(int *)(param_1 + 0xe0),(float *)0x53,uVar4,in_r7,in_r8,in_r9,in_r10);
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  return;
}



// ==== 80183e04  FUN_80183e04 ====

void FUN_80183e04(int param_1)

{
  (*(code *)(&PTR_FUN_8035c318)[*(char *)(param_1 + 0x13) * 2 + (int)*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 80183e50  FUN_80183e50 ====

uint FUN_80183e50(int param_1)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  
  iVar4 = *(char *)(param_1 + 0x13) * 0x18;
  iVar1 = zz_0083244_((float *)(param_1 + 0x20));
  if (iVar1 == 0) {
    if (*(short *)(param_1 + 0x1c) < 1) {
      uVar2 = zz_01841a8_(param_1);
    }
    else {
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      FUN_80083874((double)*(float *)(&DAT_8035c294 + iVar4),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_8035c290 + iVar4),param_1,
                   (char)*(undefined2 *)(&DAT_8035c28e + iVar4));
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      iVar1 = zz_0083714_(param_1);
      if (iVar1 == 0) {
        iVar1 = zz_0084170_(param_1);
        if (iVar1 == 0) {
          uVar2 = (uint)*(short *)(param_1 + 0x1e);
          *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
          if (*(short *)(param_1 + 0x1e) < 1) {
            *(undefined2 *)(param_1 + 0x1e) = 2;
            bVar3 = zz_018384c_(param_1,*(undefined1 *)(param_1 + 0x13),
                                (undefined4 *)(param_1 + 0x20));
            uVar2 = (uint)bVar3;
          }
        }
        else {
          uVar2 = zz_01841a8_(param_1);
        }
      }
      else {
        uVar2 = zz_01841a8_(param_1);
      }
    }
  }
  else {
    uVar2 = zz_01841a8_(param_1);
  }
  return uVar2;
}



// ==== 80183f94  FUN_80183f94 ====

void FUN_80183f94(int param_1)

{
  float fVar1;
  
  *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
  fVar1 = FLOAT_8043aed0;
  if (*(short *)(param_1 + 0x1e) < 6) {
    *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - FLOAT_8043aef0;
    if (*(float *)(param_1 + 0x144) <= fVar1) {
      *(float *)(param_1 + 0x144) = fVar1;
    }
    zz_0007cac_((double)*(float *)(param_1 + 0x144),*(int *)(param_1 + 0xe0));
  }
  if (*(short *)(param_1 + 0x1e) < 1) {
    zz_01841a8_(param_1);
  }
  return;
}



// ==== 8018401c  FUN_8018401c ====

void FUN_8018401c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  float local_58;
  float local_54;
  undefined4 local_50;
  float afStack_4c [3];
  undefined4 local_40;
  undefined4 local_30;
  undefined4 local_20;
  undefined4 local_18;
  uint uStack_14;
  
  iVar3 = zz_0083244_((float *)(param_1 + 0x20));
  if (iVar3 == 0) {
    if (*(short *)(param_1 + 0x1c) < 1) {
      zz_01841a8_(param_1);
    }
    else {
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
      zz_00833ec_(param_1);
      fVar2 = FLOAT_8043aef8;
      fVar1 = FLOAT_8043aef4;
      *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) + *(float *)(param_1 + 0x44);
      *(float *)(param_1 + 0x148) = *(float *)(param_1 + 0x148) + fVar1;
      if (fVar2 < *(float *)(param_1 + 0x148)) {
        *(float *)(param_1 + 0x148) = *(float *)(param_1 + 0x148) - FLOAT_8043aefc;
      }
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
      if (*(short *)(param_1 + 0x1e) < 1) {
        *(undefined2 *)(param_1 + 0x1e) = 1;
        local_18 = 0x43300000;
        uStack_14 = (int)*(char *)(param_1 + 0x1a) ^ 0x80000000;
        dVar4 = (double)(FLOAT_8043af00 *
                         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8043af08) +
                        *(float *)(param_1 + 0x148));
        if ((double)FLOAT_8043aef8 < dVar4) {
          dVar4 = (double)(float)(dVar4 - (double)FLOAT_8043aefc);
        }
        gnt4_PSMTXRotRad_bl(dVar4,afStack_4c,0x79);
        local_40 = *(undefined4 *)(param_1 + 0x20);
        local_30 = *(undefined4 *)(param_1 + 0x24);
        local_20 = *(undefined4 *)(param_1 + 0x28);
        local_58 = FLOAT_8043aed0;
        local_54 = FLOAT_8043aed0;
        local_50 = *(undefined4 *)(param_1 + 0x14c);
        gnt4_PSMTXMultVec_bl(afStack_4c,&local_58,&local_58);
        zz_018384c_(param_1,*(undefined1 *)(param_1 + 0x13),&local_58);
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        if ('\x02' < *(char *)(param_1 + 0x1a)) {
          *(undefined1 *)(param_1 + 0x1a) = 0;
        }
      }
    }
  }
  else {
    zz_01841a8_(param_1);
  }
  return;
}



// ==== 801841a8  zz_01841a8_ ====

void zz_01841a8_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801841e4  FUN_801841e4 ====

void FUN_801841e4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 801841f0  FUN_801841f0 ====

void FUN_801841f0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80184210  FUN_80184210 ====

void FUN_80184210(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 80184250  FUN_80184250 ====

void FUN_80184250(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 5;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80184348;
    *(code **)(puVar1 + 0x10c) = FUN_80184548;
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



// ==== 80184348  FUN_80184348 ====

void FUN_80184348(int param_1)

{
  (*(code *)(&PTR_FUN_8035c3a0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80184384  FUN_80184384 ====

void FUN_80184384(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  
  cVar1 = *(char *)(param_9 + 0x11);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar2 = cVar1 * 0x18;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined2 *)(param_9 + 0x1e) = *(undefined2 *)(&DAT_8035c38a + iVar2);
  gnt4_PSMTXMultVec_bl
            ((float *)(*(int *)(param_9 + 0x8c) + (char)(&DAT_8035c389)[iVar2] * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fca3c74),(float *)(param_9 + 0x20));
  zz_0018f88_((int *)(param_9 + 0x144),(int)(&PTR_DAT_8035c398)[cVar1 * 6],(float *)(param_9 + 0x58)
             );
  zz_0019338_((int *)(param_9 + 0x14c),*(int *)(&DAT_8035c39c + iVar2),(float *)(param_9 + 0x154));
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  zz_000726c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(float *)(int)(char)(&DAT_8035c388)[iVar2],
              (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)*(float *)(param_9 + 0x154),*(int *)(param_9 + 0xe0));
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



// ==== 80184490  FUN_80184490 ====

void FUN_80184490(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (*(short *)(param_1 + 0x1e) <= sVar1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
  zz_0019370_((int *)(param_1 + 0x14c),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x154));
  zz_0007cac_((double)*(float *)(param_1 + 0x154),*(int *)(param_1 + 0xe0));
  return;
}



// ==== 80184528  FUN_80184528 ====

void FUN_80184528(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80184548  FUN_80184548 ====

void FUN_80184548(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 80184588  zz_0184588_ ====

undefined4 zz_0184588_(int param_1,undefined1 param_2,uint param_3,byte *param_4)

{
  short sVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  double dVar4;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0x503) || (sVar1 == 0x506)) || (sVar1 == 0x508)) ||
     (((sVar1 == 0x50f || (sVar1 == 0x512)) || (sVar1 == 0x514)))) {
    puVar3 = zz_0088aa0_(param_1,3,8,0,1);
    if (puVar3 == (undefined1 *)0x0) {
      uVar2 = 0;
    }
    else {
      *puVar3 = 1;
      puVar3[0x13] = (char)param_3;
      dVar4 = (double)FLOAT_8043af10;
      puVar3[0x11] = param_2;
      puVar3[0x10] = 0x33;
      *(code **)(puVar3 + 0xc) = FUN_8018470c;
      *(code **)(puVar3 + 0x10c) = FUN_8018549c;
      *(int *)(puVar3 + 0x8c) = param_1;
      *(undefined4 *)(puVar3 + 0x90) = *(undefined4 *)(param_1 + 0x90);
      *(undefined2 *)(puVar3 + 0x94) = *(undefined2 *)(param_1 + 0x94);
      puVar3[0x96] = *(undefined1 *)(param_1 + 0x96);
      puVar3[0x97] = *(undefined1 *)(param_1 + 0x97);
      puVar3[0x88] = *(undefined1 *)(param_1 + 0x88);
      *(undefined4 *)(puVar3 + 200) = *(undefined4 *)(param_1 + 200);
      *(undefined4 *)(puVar3 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
      *(undefined4 *)(puVar3 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
      *(undefined4 *)(puVar3 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar3 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar3 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar3 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar3 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
      *(undefined4 *)(puVar3 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
      puVar3[0xd0] = *(undefined1 *)(param_1 + 0xd0);
      *(undefined4 *)(puVar3 + 0x148) = *(undefined4 *)(puVar3 + 0xcc);
      *(undefined4 *)(puVar3 + 0x144) = *(undefined4 *)(puVar3 + 200);
      zz_00f061c_(dVar4,param_1,7);
      *(byte **)(puVar3 + 0x164) = param_4;
      uVar2 = 1;
      *param_4 = *param_4 & ~(byte)(1 << (param_3 & 3));
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 8018470c  FUN_8018470c ====

void FUN_8018470c(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_0185044_(param_1);
  }
  (*(code *)(&PTR_FUN_8035c770)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801847ac  FUN_801847ac ====

void FUN_801847ac(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  float *pfVar9;
  int iVar10;
  double dVar11;
  undefined8 uVar12;
  float local_68;
  float local_64;
  float local_60;
  float fStack_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_28;
  uint uStack_24;
  
  puVar7 = &DAT_8035c6b0;
  puVar4 = &DAT_8035c3b0;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar10 = *(int *)(param_9 + 0x90);
  iVar5 = *(char *)(param_9 + 0x13) * 0x30;
  iVar2 = (uint)*(byte *)(param_9 + 0x11) * 0x20;
  *(undefined1 *)(param_9 + 0x84) = 0x16;
  iVar3 = (int)*(short *)(&DAT_8035c3b2 + iVar5);
  *(char *)(param_9 + 0x89) = (char)*(short *)(&DAT_8035c3b2 + iVar5);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar6 = iVar5;
  iVar8 = iVar2;
  zz_0089100_(param_9,0,1);
  pfVar9 = (float *)(iVar10 + *(short *)(&DAT_8035c3b2 + iVar5) * 0x30 + 0x8d4);
  gnt4_PSMTXCopy_bl(pfVar9,(float *)(param_9 + 0x114));
  gnt4_PSMTXMultVec_bl(pfVar9,(float *)(iVar5 + -0x7fca3c4c),(float *)(param_9 + 0x20));
  local_28 = 0x43300000;
  uStack_24 = (int)*(short *)(&DAT_8035c3c0 + iVar5) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_8043af14 *
                              (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043af20)),
                      &fStack_5c,0x78);
  gnt4_PSMTXConcat_bl(pfVar9,&fStack_5c,&fStack_5c);
  dVar11 = (double)FLOAT_8043af18;
  *(undefined4 *)(param_9 + 0x9c) = local_58;
  *(undefined4 *)(param_9 + 0xa0) = local_48;
  *(undefined4 *)(param_9 + 0xa4) = local_38;
  gnt4_PSQUATScale_bl(dVar11,(float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
  local_64 = FLOAT_8043af1c;
  *(undefined4 *)(param_9 + 0x38) = local_54;
  *(undefined4 *)(param_9 + 0x3c) = local_44;
  *(undefined4 *)(param_9 + 0x40) = local_34;
  local_68 = *(float *)(param_9 + 0x38);
  local_60 = *(float *)(param_9 + 0x40);
  dVar11 = gnt4_PSVECMag_bl(&local_68);
  iVar1 = FUN_800452a0(-(double)*(float *)(param_9 + 0x3c),dVar11);
  *(short *)(param_9 + 0x70) = (short)iVar1;
  dVar11 = (double)local_60;
  iVar1 = FUN_800452a0((double)local_68,dVar11);
  *(short *)(param_9 + 0x72) = (short)iVar1;
  *(undefined2 *)(param_9 + 0x74) = 0;
  uVar12 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8035c6c0 + iVar2),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8035c6c0 + iVar2);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8035c6b4 + iVar2);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8035c6b6 + iVar2);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  iVar1 = zz_0006f98_(iVar10);
  zz_0006fb4_(uVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0x600),
              *(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_8035c3b0 + iVar5),iVar3,puVar4,iVar6,
              puVar7,iVar8);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_8035c6b0)[iVar2]);
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
    zz_0185044_(param_9);
  }
  else {
    *(undefined1 *)(param_9 + 0xa8) = 1;
  }
  return;
}



// ==== 801849dc  FUN_801849dc ====

void FUN_801849dc(int param_1)

{
  float fVar1;
  int iVar2;
  char cVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  iVar6 = *(int *)(param_1 + 0x90);
  iVar5 = (uint)*(byte *)(param_1 + 0x11) * 0x20;
  switch(*(char *)(param_1 + 0x19)) {
  case '\0':
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined1 *)(param_1 + 0x1a) = 0xff;
    *(undefined1 *)(param_1 + 0x1b) = 1;
    *(undefined2 *)(param_1 + 0x1c) = 0x14;
  case '\x01':
    FUN_80185068(param_1,1);
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(&DAT_8035c6b2 + iVar5);
    }
    break;
  case '\x02':
    zz_0184ecc_(param_1);
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (((sVar4 < 1) || (iVar6 = *(int *)(param_1 + 200), iVar6 == 0)) ||
       (iVar2 = zz_0083244_((float *)(param_1 + 0x20)), iVar2 != 0)) {
      *(undefined1 *)(param_1 + 0x19) = 6;
    }
    else {
      *(float *)(param_1 + 0x44) =
           *(float *)(&DAT_8035c6c8 + iVar5) * *(float *)(param_1 + 0xb4) +
           *(float *)(param_1 + 0x44);
      fVar1 = *(float *)(&DAT_8035c6c4 + iVar5) * *(float *)(param_1 + 0xb4);
      if (fVar1 < *(float *)(param_1 + 0x44)) {
        *(float *)(param_1 + 0x44) = fVar1;
      }
      zz_006ebb4_((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      cVar3 = *(char *)(param_1 + 0x1cb) + -1;
      *(char *)(param_1 + 0x1cb) = cVar3;
      if (cVar3 < '\x01') {
        *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_8035c6b4 + iVar5);
        gnt4_PSVECSubtract_bl((float *)(iVar6 + 100),(float *)(param_1 + 0x20),&local_28);
        zz_006ebb4_(&local_28,&local_28);
        gnt4_PSQUATScale_bl((double)FLOAT_8043af28,&local_28,&local_28);
        gnt4_PSQUATScale_bl((double)FLOAT_8043af28,(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x38),&local_28,(float *)(param_1 + 0x38));
      }
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),&local_28);
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),&local_28,(float *)(param_1 + 0x20));
      iVar5 = FUN_80083874((double)*(float *)(&DAT_8035c6bc + iVar5),param_1);
      if (iVar5 != 0) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(undefined2 *)(param_1 + 0x1c) = 0x14;
        zz_006d228_(param_1,*(int *)(param_1 + 0xcc),0);
        zz_0185284_(param_1);
      }
    }
    zz_0184f2c_(param_1);
    break;
  case '\x03':
    zz_0184ecc_(param_1);
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
    FUN_80185300((double)*(float *)(&DAT_8035c6cc + iVar5),param_1);
    if (*(short *)(param_1 + 0x1c) < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 10;
    }
    zz_0184f2c_(param_1);
    break;
  case '\x04':
    zz_0184ecc_(param_1);
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0x1e;
      iVar5 = zz_006dbe0_(iVar6,(int)(char)(&DAT_8035c6b1)[iVar5],1,1);
      if (iVar5 == 0) {
        *(undefined1 *)(param_1 + 0x1b) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0x168) = 10;
        zz_00e19a8_(param_1,9,param_1 + 0x168);
      }
    }
    zz_0184f2c_(param_1);
    break;
  case '\x05':
    *(char *)(param_1 + 0x168) = *(char *)(param_1 + 0x168) + -1;
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      cVar3 = *(char *)(param_1 + 0x1b) + -1;
      *(char *)(param_1 + 0x1b) = cVar3;
      if (cVar3 < '\x01') {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
      else {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + -2;
        *(undefined2 *)(param_1 + 0x1c) = 0x14;
        zz_006d228_(param_1,*(int *)(param_1 + 0xcc),0);
        zz_0185284_(param_1);
      }
    }
    break;
  case '\x06':
    *(float *)(param_1 + 0x44) =
         *(float *)(&DAT_8035c6c8 + iVar5) * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x44)
    ;
    fVar1 = *(float *)(&DAT_8035c6c4 + iVar5) * *(float *)(param_1 + 0xb4);
    if (fVar1 < *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = fVar1;
    }
    iVar5 = iVar6 + *(char *)(param_1 + 0x89) * 0x30;
    local_28 = *(float *)(iVar5 + 0x8e0);
    local_24 = *(undefined4 *)(iVar5 + 0x8f0);
    local_20 = *(undefined4 *)(iVar5 + 0x900);
    gnt4_PSVECSubtract_bl(&local_28,(float *)(param_1 + 0x20),&local_28);
    dVar7 = gnt4_PSVECMag_bl(&local_28);
    if (dVar7 <= (double)(FLOAT_8043af2c * *(float *)(param_1 + 0xb4))) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0x14;
    }
    else {
      zz_006ebb4_(&local_28,&local_28);
      gnt4_PSQUATScale_bl((double)FLOAT_8043af28,&local_28,&local_28);
      zz_006ebb4_((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)FLOAT_8043af28,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38)
                         );
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x38),&local_28,(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),&local_28);
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),&local_28,(float *)(param_1 + 0x20));
    }
    FUN_80184f5c(param_1,(float *)(iVar6 + 0x20));
    break;
  case '\a':
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0x14;
    }
    FUN_80185068(param_1,1);
    break;
  case '\b':
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0;
      zz_0185044_(param_1);
    }
    FUN_80185068(param_1,0);
    break;
  case '\t':
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 80184ecc  zz_0184ecc_ ====

void zz_0184ecc_(int param_1)

{
  char *pcVar1;
  
  pcVar1 = *(char **)(param_1 + 0x148);
  if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
    if ((*(char **)(param_1 + 0x144) != (char *)0x0) &&
       ((**(char **)(param_1 + 0x144) != '\0' && (pcVar1[0x18] < '\x02')))) goto LAB_80184f18;
  }
  *(undefined4 *)(param_1 + 0x144) = 0;
  *(undefined4 *)(param_1 + 0x148) = 0;
LAB_80184f18:
  *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_1 + 0x144);
  return;
}



// ==== 80184f2c  zz_0184f2c_ ====

void zz_0184f2c_(int param_1)

{
  if (*(int *)(param_1 + 200) != 0) {
    FUN_80184f5c(param_1,(float *)(*(int *)(param_1 + 200) + 100));
  }
  return;
}



// ==== 80184f5c  FUN_80184f5c ====

/* WARNING: Removing unreachable block (ram,0x80185024) */
/* WARNING: Removing unreachable block (ram,0x80184f6c) */

void FUN_80184f5c(int param_1,float *param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_28;
  float local_24;
  float local_20;
  
  gnt4_PSVECSubtract_bl(param_2,(float *)(param_1 + 0x20),&local_28);
  dVar5 = (double)local_24;
  local_24 = FLOAT_8043af1c;
  dVar4 = gnt4_PSVECMag_bl(&local_28);
  iVar2 = FUN_800452a0(-dVar5,dVar4);
  iVar3 = FUN_800452a0((double)local_28,(double)local_20);
  sVar1 = (short)iVar2 - *(short *)(param_1 + 0x70);
  if (0x800 < sVar1) {
    sVar1 = 0x800;
  }
  if (sVar1 < -0x800) {
    sVar1 = -0x800;
  }
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + sVar1;
  sVar1 = (short)iVar3 - *(short *)(param_1 + 0x72);
  if (0x800 < sVar1) {
    sVar1 = 0x800;
  }
  if (sVar1 < -0x800) {
    sVar1 = -0x800;
  }
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar1;
  return;
}



