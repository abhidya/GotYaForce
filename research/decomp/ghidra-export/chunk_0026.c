// ==== 800ef1e4  zz_00ef1e4_ ====

void zz_00ef1e4_(short param_1)

{
  undefined1 *puVar1;
  uint uVar2;
  short sVar3;
  uint uVar4;
  
  (&DAT_803cfe23)[param_1 * 0x5c] = 1;
  uVar2 = countLeadingZeros(-1 - DAT_803d1522);
  uVar4 = countLeadingZeros(-1 - DAT_803d1520);
  sVar3 = (short)(uVar4 >> 5) + ((ushort)(uVar2 >> 4) & 0xfffe);
  if (sVar3 == 3) {
    DAT_803d1520 = param_1;
    DAT_803d1522 = param_1;
    return;
  }
  if ((sVar3 < 3) && (sVar3 == 0)) {
    (&DAT_803cfe32)[DAT_803d1522 * 0x2e] = param_1;
    (&DAT_803cfe2e)[param_1 * 0x2e] = DAT_803d1522;
    DAT_803d1522 = param_1;
    return;
  }
  puVar1 = &DAT_803d1528 + DAT_803d1524;
  DAT_803d1524 = DAT_803d1524 + 1;
  *puVar1 = (char)param_1;
  return;
}



// ==== 800ef28c  zz_00ef28c_ ====

void zz_00ef28c_(short param_1)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  short sVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = (int)param_1;
  puVar1 = &DAT_803d1528 + DAT_803d1524;
  DAT_803d1524 = DAT_803d1524 + 1;
  *puVar1 = (char)param_1;
  iVar6 = (int)(short)(&DAT_803cfe2e)[iVar2 * 0x2e];
  iVar7 = (int)(short)(&DAT_803cfe32)[iVar2 * 0x2e];
  uVar3 = countLeadingZeros(-1 - iVar7);
  uVar5 = countLeadingZeros(-1 - iVar6);
  sVar4 = (short)(uVar5 >> 5) + ((ushort)(uVar3 >> 4) & 0xfffe);
  if (sVar4 == 2) {
    (&DAT_803cfe32)[iVar6 * 0x2e] = 0xffff;
    DAT_803d1522 = (&DAT_803cfe2e)[iVar2 * 0x2e];
  }
  else if (sVar4 < 2) {
    if (sVar4 == 0) {
      (&DAT_803cfe32)[iVar6 * 0x2e] = (&DAT_803cfe30)[iVar7 * 0x2e];
      (&DAT_803cfe2e)[iVar7 * 0x2e] = (&DAT_803cfe30)[iVar6 * 0x2e];
    }
    else if (-1 < sVar4) {
      (&DAT_803cfe2e)[iVar7 * 0x2e] = 0xffff;
      DAT_803d1520 = (&DAT_803cfe32)[iVar2 * 0x2e];
    }
  }
  else if (sVar4 < 4) {
    DAT_803d1522 = 0xffff;
    DAT_803d1520 = 0xffff;
  }
  (&DAT_803cfe32)[iVar2 * 0x2e] = 0xffff;
  (&DAT_803cfe2e)[iVar2 * 0x2e] = 0xffff;
  (&DAT_803cfe20)[iVar2 * 0x5c] = 0;
  return;
}



// ==== 800ef390  FUN_800ef390 ====

undefined4 FUN_800ef390(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  short sVar10;
  int *piVar11;
  undefined1 *puVar12;
  uint uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  
  uVar14 = zz_0205cb4_(-0x7fc2c550);
  uVar3 = zz_0219d9c_();
  if (DAT_803cf8f4 < uVar3) {
    DAT_803cf8f4 = uVar3;
  }
  zz_00ef878_();
  sVar10 = DAT_803d1520;
  uVar3 = zz_010dbcc_();
  uVar4 = zz_010dc14_();
  do {
    if (sVar10 == -1) {
      zz_021b44c_();
      DAT_803cf910 = DAT_803cf910 + 1;
      uVar15 = zz_0205cb4_(-0x7fc2c550);
      DAT_803d3ae0 = (int)uVar15 - (int)uVar14;
      if (DAT_803d3ae4 < DAT_803d3ae0) {
        DAT_803d3ae4 = DAT_803d3ae0;
      }
      return (int)((ulonglong)uVar15 >> 0x20);
    }
    iVar1 = (int)sVar10;
    iVar2 = iVar1 * 0x5c;
    puVar12 = &DAT_803cfe20 + iVar2;
    if ((&DAT_803cfe23)[iVar2] == '\0') {
      zz_00ee258_((int)puVar12);
      sVar10 = (&DAT_803cfe34)[iVar1 * 0x2e];
      while (sVar10 != -1) {
        iVar5 = (int)sVar10;
        iVar6 = iVar5 * 0x94;
        uVar13 = 0;
        *(undefined2 *)(&DAT_803d15a2 + iVar6) = *(undefined2 *)(&DAT_803cfe4c + iVar2);
        piVar11 = &DAT_803d1568 + iVar5 * 0x25;
        piVar9 = (int *)(&DAT_803d156c + iVar6);
        *(short *)(&DAT_803d15a4 + iVar6) = (short)uVar3;
        *(short *)(&DAT_803d15a6 + iVar6) = (short)DAT_803cf904;
        *(undefined2 *)(&DAT_803d15aa + iVar6) = *(undefined2 *)(&DAT_803cfe4e + iVar2);
        *(short *)(&DAT_803d15ac + iVar6) = (short)uVar4;
        *(short *)(&DAT_803d15ae + iVar6) = (short)DAT_803cf908;
        if ((&DAT_803d158d)[iVar6] != '\0') {
          (&DAT_803d1570)[iVar5 * 0x25] = 6;
          (&DAT_803d158c)[iVar6] = 1;
        }
        switch((&DAT_803d1570)[iVar5 * 0x25]) {
        case 0:
          *(undefined4 *)(&DAT_803d1574 + iVar6) = 0;
          uVar13 = 1;
          *(int *)(&DAT_803d1578 + iVar6) =
               (int)(FLOAT_80439040 *
                    (float)((double)CONCAT44(0x43300000,*(uint *)*piVar9 >> 0xd & 0x3f) -
                           DOUBLE_80439010) * FLOAT_80439044);
          *(undefined4 *)(&DAT_803d157c + iVar6) =
               *(undefined4 *)(&DAT_8031b210 + (*(byte *)*piVar9 & 0xfe) * 2);
          *(undefined4 *)(&DAT_803d1580 + iVar6) =
               *(undefined4 *)(&DAT_8031b210 + (*(ushort *)*piVar9 & 0x1f8));
          *(undefined4 *)(&DAT_803d1584 + iVar6) =
               *(undefined4 *)(&DAT_8031b210 + (*(ushort *)(*piVar9 + 2) >> 3 & 0x1f8));
          *(undefined4 *)(&DAT_803d1588 + iVar6) =
               *(undefined4 *)(&DAT_8031b210 + (*(byte *)(*piVar9 + 3) & 0x3f) * 8);
          (&DAT_803d1570)[iVar5 * 0x25] = 1;
        case 1:
          iVar7 = zz_00ef970_((int)puVar12,piVar11,uVar13);
          if ((iVar7 == 0) &&
             (*(int *)(&DAT_803d1574 + iVar6) =
                   *(int *)(&DAT_803d1574 + iVar6) + *(int *)(&DAT_803d157c + iVar6),
             0x7fffffe < *(int *)(&DAT_803d1574 + iVar6))) {
            *(undefined4 *)(&DAT_803d1574 + iVar6) = 0x7ffffff;
            (&DAT_803d1570)[iVar5 * 0x25] = 2;
          }
          break;
        case 2:
          iVar7 = zz_00ef970_((int)puVar12,piVar11,0);
          if (iVar7 == 0) {
            *(int *)(&DAT_803d1574 + iVar6) =
                 *(int *)(&DAT_803d1574 + iVar6) - *(int *)(&DAT_803d1580 + iVar6);
            if (*(int *)(&DAT_803d1574 + iVar6) <= *(int *)(&DAT_803d1578 + iVar6)) {
              *(int *)(&DAT_803d1574 + iVar6) = *(int *)(&DAT_803d1578 + iVar6);
              (&DAT_803d1570)[iVar5 * 0x25] = 3;
            }
          }
          break;
        case 3:
          iVar7 = zz_00ef970_((int)puVar12,piVar11,0);
          if (iVar7 == 0) {
            if ((*(byte *)(*piVar9 + 2) >> 4 & 1) == 1) {
              *(int *)(&DAT_803d1574 + iVar6) =
                   *(int *)(&DAT_803d1574 + iVar6) + *(int *)(&DAT_803d1584 + iVar6);
              if (0x7ffffff < *(int *)(&DAT_803d1574 + iVar6)) {
                *(undefined4 *)(&DAT_803d1574 + iVar6) = 0x7ffffff;
              }
            }
            else {
              *(int *)(&DAT_803d1574 + iVar6) =
                   *(int *)(&DAT_803d1574 + iVar6) - *(int *)(&DAT_803d1584 + iVar6);
              if (*(int *)(&DAT_803d1574 + iVar6) < 1) {
                *(undefined4 *)(&DAT_803d1574 + iVar6) = 0;
                (&DAT_803d1570)[iVar5 * 0x25] = 4;
                goto switchD_800ef4b4_caseD_4;
              }
            }
          }
          break;
        case 4:
switchD_800ef4b4_caseD_4:
          zz_00ef970_((int)puVar12,piVar11,0);
          *(int *)(&DAT_803d1574 + iVar6) =
               *(int *)(&DAT_803d1574 + iVar6) - *(int *)(&DAT_803d1588 + iVar6);
          if (*(int *)(&DAT_803d1574 + iVar6) < 1) {
            *(undefined4 *)(&DAT_803d1574 + iVar6) = 0;
            uVar13 = 2;
            (&DAT_803d1570)[iVar5 * 0x25] = 6;
          }
          break;
        case 5:
          *(int *)(&DAT_803d1574 + iVar6) = *(int *)(&DAT_803d1574 + iVar6) + -0x1555555;
          if (*(int *)(&DAT_803d1574 + iVar6) < 1) {
            *(undefined4 *)(&DAT_803d1574 + iVar6) = 0;
            uVar13 = 2;
            (&DAT_803d1570)[iVar5 * 0x25] = 6;
          }
          break;
        default:
          uVar13 = 3;
        }
        if (uVar13 < 2) {
          iVar7 = zz_00ee330_((int)puVar12,(uint)(byte)(&DAT_803d159a)[iVar6]);
          (&DAT_803d1596)[iVar6] = (char)iVar7;
          *(int *)(&DAT_803d15b4 + iVar6) = *(int *)(&DAT_803d1574 + iVar6) >> 0xc;
          *(short *)(&DAT_803d15f6 + iVar6) =
               (short)((*(int *)(&DAT_803d15b4 + iVar6) * (uint)(byte)(&DAT_803d1596)[iVar6]) / 0x7f
                      );
          *(undefined2 *)(&DAT_803d15f8 + iVar6) = 0;
          zz_02199ec_(*piVar11,(undefined2 *)(&DAT_803d15f6 + iVar6));
          uVar8 = zz_00ee66c_((int)puVar12,(uint)(byte)(&DAT_803d159b)[iVar6]);
          (&DAT_803d1597)[iVar6] = (char)uVar8;
          zz_00ee3b0_((int)piVar11);
          zz_0219798_(*piVar11,(short *)(iVar6 + -0x7fc2ea2e));
          if ((*(ushort *)(&DAT_803cfe50 + iVar2) & 4) != 0) {
            *(undefined2 *)(&DAT_803d1598 + iVar6) = *(undefined2 *)(&DAT_803cfe4a + iVar2);
            zz_00ee71c_((int)piVar11,(uint)*(ushort *)(&DAT_803d1598 + iVar6));
            zz_0219c90_((double)(*(float *)(&DAT_803d15bc + iVar6) / FLOAT_8043900c),*piVar11);
          }
        }
        if (uVar13 == 2) {
          zz_02196f0_(*piVar11,0);
          zz_0217028_((int *)*piVar11);
          (&DAT_803d158c)[iVar6] = 1;
        }
        else if ((uVar13 < 2) && (uVar13 != 0)) {
          zz_02196f0_(*piVar11,1);
        }
        sVar10 = (&DAT_803d1592)[iVar5 * 0x4a];
      }
      *(undefined2 *)(&DAT_803cfe50 + iVar2) = 0;
      *(undefined2 *)(&DAT_803cfe52 + iVar2) = 0;
    }
    sVar10 = (&DAT_803cfe32)[iVar1 * 0x2e];
  } while( true );
}



// ==== 800ef878  zz_00ef878_ ====

void zz_00ef878_(void)

{
  if (DAT_803cf8e9 == '\0') {
    DAT_803cf8ea = DAT_803cf8ea + 0x2a5;
    if (0x1fc0 < DAT_803cf8ea) {
      DAT_803cf8ea = 0x1fc0;
    }
  }
  else {
    DAT_803cf8ea = DAT_803cf8ea + -0x2a5;
    if (DAT_803cf8ea < 0) {
      DAT_803cf8ea = 0;
    }
  }
  if ((DAT_803cf902 & 1) == 0) {
    DAT_803cf904 = DAT_803cf904 + -0x1555;
    if (DAT_803cf904 < 0) {
      DAT_803cf904 = 0;
    }
  }
  else {
    DAT_803cf904 = DAT_803cf904 + 0x1555;
    if (0x7fff < DAT_803cf904) {
      DAT_803cf904 = 0x7fff;
    }
  }
  if ((DAT_803cf902 & 2) != 0) {
    DAT_803cf908 = DAT_803cf908 + 0x1555;
    if (DAT_803cf908 < 0x8000) {
      return;
    }
    DAT_803cf908 = 0x7fff;
    return;
  }
  DAT_803cf908 = DAT_803cf908 + -0x1555;
  if (-1 < DAT_803cf908) {
    return;
  }
  DAT_803cf908 = 0;
  return;
}



// ==== 800ef970  zz_00ef970_ ====

undefined4 zz_00ef970_(int param_1,int *param_2,int param_3)

{
  if (*(char *)(param_1 + 1) == '\0') {
    if (*(short *)(*param_2 + 0x146) != 0) {
      return 0;
    }
    if (param_3 == 1) {
      return 0;
    }
    param_2[3] = 0;
  }
  if (*(int *)(param_1 + 8) == 0x10) {
    param_2[2] = 5;
  }
  else {
    param_2[2] = 4;
  }
  return 1;
}



// ==== 800ef9d4  zz_00ef9d4_ ====

void zz_00ef9d4_(int param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_1 * 0x98;
  piVar1 = (int *)(&DAT_803cd2e8 + iVar2);
  *piVar1 = param_2;
  *(int *)(&DAT_803cd2ec + iVar2) = param_2 + *(int *)(*piVar1 + 0x14);
  *(int *)(&DAT_803cd2f0 + iVar2) = param_2 + *(int *)(*piVar1 + 0x18);
  *(int *)(&DAT_803cd2f4 + iVar2) = param_2 + *(int *)(*piVar1 + 0x1c);
  *(undefined4 *)(&DAT_803cd2f8 + iVar2) = param_3;
  iVar3 = 4;
  do {
    *(undefined1 *)(piVar1 + 6) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x19) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x1a) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x1b) = 0x7f;
    *(undefined1 *)(piVar1 + 7) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x1d) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x1e) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x1f) = 0x7f;
    *(undefined1 *)(piVar1 + 8) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x21) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x22) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x23) = 0x7f;
    *(undefined1 *)(piVar1 + 9) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x25) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x26) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x27) = 0x7f;
    *(undefined1 *)(piVar1 + 10) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x29) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x2a) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x2b) = 0x7f;
    *(undefined1 *)(piVar1 + 0xb) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x2d) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x2e) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x2f) = 0x7f;
    *(undefined1 *)(piVar1 + 0xc) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x31) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x32) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x33) = 0x7f;
    *(undefined1 *)(piVar1 + 0xd) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x35) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x36) = 0x7f;
    *(undefined1 *)((int)piVar1 + 0x37) = 0x7f;
    piVar1 = piVar1 + 8;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  (&DAT_803cd2ff)[iVar2] = 0x7f;
  return;
}



// ==== 800efac8  zz_00efac8_ ====

uint zz_00efac8_(void)

{
  undefined8 uVar1;
  
  uVar1 = zz_0205cb4_(-0x7fc2c550);
  return (uint)uVar1 & 0xff;
}



// ==== 800efafc  zz_00efafc_ ====

void zz_00efafc_(undefined1 *param_1,undefined4 param_2,int param_3)

{
  if (param_3 == 3) {
LAB_800efb24:
    param_1[2] = (char)((uint)param_2 >> 0x10);
  }
  else {
    if (2 < param_3) {
      if (4 < param_3) goto LAB_800efb34;
      param_1[3] = (char)((uint)param_2 >> 0x18);
      goto LAB_800efb24;
    }
    if (param_3 < 2) goto LAB_800efb34;
  }
  param_1[1] = (char)((uint)param_2 >> 8);
LAB_800efb34:
  *param_1 = (char)param_2;
  return;
}



// ==== 800efb3c  zz_00efb3c_ ====

void zz_00efb3c_(uint param_1,int param_2,uint param_3,uint param_4,int param_5)

{
  int iVar1;
  
  if ((DAT_803d3e3c == '\0') && ((int)param_1 < 0x180)) {
    iVar1 = (int)param_1 >> 0x1f;
    zz_00f0f84_(((int)param_1 >> 7) + (uint)((int)param_1 < 0 && (param_1 & 0x7f) != 0),
                (iVar1 * 0x80 | param_1 * 0x2000000 + iVar1 >> 0x19) - iVar1,param_2 << 3,
                (int)((float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80439048) *
                     *(float *)(&DAT_8031b430 + (char)PTR_DAT_8043394c[0x2d] * 4)),param_4,param_5,
                '\0');
    DAT_803d3e38 = DAT_803d3e38 + 1;
  }
  return;
}



// ==== 800efc04  zz_00efc04_ ====

void zz_00efc04_(uint param_1,int param_2,uint param_3,uint param_4,int param_5)

{
  int iVar1;
  
  if ((int)param_1 < 0x180) {
    iVar1 = (int)param_1 >> 0x1f;
    zz_00f0f84_(((int)param_1 >> 7) + (uint)((int)param_1 < 0 && (param_1 & 0x7f) != 0),
                (iVar1 * 0x80 | param_1 * 0x2000000 + iVar1 >> 0x19) - iVar1,param_2 << 3,
                (int)((float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80439048) *
                     *(float *)(&DAT_8031b430 + (char)PTR_DAT_8043394c[0x2d] * 4)),param_4,param_5,
                '\0');
    DAT_803d3e38 = DAT_803d3e38 + 1;
  }
  return;
}



// ==== 800efcb8  zz_00efcb8_ ====

void zz_00efcb8_(uint param_1,int param_2,uint param_3,int param_4,int param_5)

{
  int iVar1;
  
  if ((DAT_803d3e3c == '\0') && ((int)param_1 < 0x180)) {
    iVar1 = (int)param_1 >> 0x1f;
    zz_00f1238_(((int)param_1 >> 7) + (uint)((int)param_1 < 0 && (param_1 & 0x7f) != 0),
                (iVar1 * 0x80 | param_1 * 0x2000000 + iVar1 >> 0x19) - iVar1,param_2 << 3,
                (int)((float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80439048) *
                     *(float *)(&DAT_8031b430 + (char)PTR_DAT_8043394c[0x2d] * 4)),param_4,param_5,
                '\0',1);
  }
  return;
}



// ==== 800efd70  zz_00efd70_ ====

void zz_00efd70_(void)

{
  gnt4_memset(&DAT_803d3ae8,0,0x358);
  zz_00f0a34_();
  zz_00f0a60_();
  return;
}



// ==== 800efda8  zz_00efda8_ ====

void zz_00efda8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,int param_11,undefined *param_12,
                undefined4 param_13,undefined *param_14,uint param_15,int param_16)

{
  zz_00ed058_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800efdc8  zz_00efdc8_ ====

void zz_00efdc8_(void)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = &DAT_803d3ae8;
  DAT_803d3b36 = 0;
  iVar2 = 3;
  do {
    *(undefined4 *)(puVar1 + 0x5c) = 0;
    *(undefined4 *)(puVar1 + 0x58) = 0;
    *(undefined4 *)(puVar1 + 0x6c) = 0;
    *(undefined4 *)(puVar1 + 0x68) = 0;
    *(undefined4 *)(puVar1 + 0x7c) = 0;
    *(undefined4 *)(puVar1 + 0x78) = 0;
    *(undefined4 *)(puVar1 + 0x8c) = 0;
    *(undefined4 *)(puVar1 + 0x88) = 0;
    *(undefined4 *)(puVar1 + 0x9c) = 0;
    *(undefined4 *)(puVar1 + 0x98) = 0;
    *(undefined4 *)(puVar1 + 0xac) = 0;
    *(undefined4 *)(puVar1 + 0xa8) = 0;
    *(undefined4 *)(puVar1 + 0xbc) = 0;
    *(undefined4 *)(puVar1 + 0xb8) = 0;
    *(undefined4 *)(puVar1 + 0xcc) = 0;
    *(undefined4 *)(puVar1 + 200) = 0;
    *(undefined4 *)(puVar1 + 0xdc) = 0;
    *(undefined4 *)(puVar1 + 0xd8) = 0;
    *(undefined4 *)(puVar1 + 0xec) = 0;
    *(undefined4 *)(puVar1 + 0xe8) = 0;
    *(undefined4 *)(puVar1 + 0xfc) = 0;
    *(undefined4 *)(puVar1 + 0xf8) = 0;
    *(undefined4 *)(puVar1 + 0x10c) = 0;
    *(undefined4 *)(puVar1 + 0x108) = 0;
    *(undefined4 *)(puVar1 + 0x11c) = 0;
    *(undefined4 *)(puVar1 + 0x118) = 0;
    *(undefined4 *)(puVar1 + 300) = 0;
    *(undefined4 *)(puVar1 + 0x128) = 0;
    *(undefined4 *)(puVar1 + 0x13c) = 0;
    *(undefined4 *)(puVar1 + 0x138) = 0;
    *(undefined4 *)(puVar1 + 0x14c) = 0;
    *(undefined4 *)(puVar1 + 0x148) = 0;
    puVar1 = puVar1 + 0x100;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}



// ==== 800efe70  zz_00efe70_ ====

/* WARNING: Removing unreachable block (ram,0x800efed4) */

void zz_00efe70_(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined *puVar6;
  
  puVar5 = &DAT_803d3ae8;
  iVar4 = 0;
  do {
    iVar3 = 0;
    puVar6 = puVar5;
    do {
      iVar2 = *(int *)(puVar6 + 0x58);
      if ((iVar2 != 0) && (uVar1 = (uint)*(short *)(iVar2 + 2), uVar1 != 0xff)) {
        if (*(short *)(iVar2 + 4) == 1) {
          zz_00f036c_(*(int *)(puVar6 + 0x5c),uVar1);
        }
        else if (*(short *)(iVar2 + 4) == 0) {
          zz_00f036c_(*(int *)(puVar6 + 0x5c),uVar1);
        }
      }
      iVar3 = iVar3 + 1;
      puVar6 = puVar6 + 0x10;
    } while (iVar3 < 8);
    iVar4 = iVar4 + 1;
    puVar5 = puVar5 + 0x80;
  } while (iVar4 < 6);
  zz_00efdc8_();
  return;
}



// ==== 800eff30  zz_00eff30_ ====

/* WARNING: Removing unreachable block (ram,0x800f0098) */
/* WARNING: Removing unreachable block (ram,0x800f0054) */

void zz_00eff30_(void)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  
  iVar1 = gnt4_OSGetTick_bl();
  puVar7 = &DAT_803d3ae8;
  iVar6 = 0;
  do {
    piVar4 = (int *)(puVar7 + 0x50);
    iVar5 = 0;
    do {
      if (piVar4[2] != 0) {
        if ((DAT_803d3b36 == '\0') && (iVar2 = piVar4[1], piVar4[1] = iVar2 + -1, iVar2 + -1 < 1)) {
          zz_00f036c_(piVar4[3],(int)*(short *)(piVar4[2] + 2));
          piVar4[3] = 0;
          piVar4[2] = 0;
        }
        else if ((((*(uint *)(piVar4[2] + 8) <=
                    (uint)((iVar1 - *piVar4) * 8) / (DAT_800000f8 / 500000)) &&
                  (DAT_803d3b36 == '\0')) || (DAT_803d3b36 == '\x02')) &&
                (*(int *)(piVar4[2] + 0xc) != -0x10000000)) {
          *piVar4 = iVar1;
          piVar4[2] = piVar4[2] + *(int *)(piVar4[2] + 0xc) * 0x10;
          if (DAT_803d3b36 == '\x02') {
            psVar3 = (short *)piVar4[2];
            if (psVar3[2] == 1) {
              zz_00f06f0_((double)FLOAT_80439050,piVar4[3],(int)*psVar3);
            }
            else if (psVar3[2] == 0) {
              zz_00f0414_(piVar4[3],(int)*psVar3);
            }
          }
          else {
            psVar3 = (short *)piVar4[2];
            if (psVar3[2] == 1) {
              zz_00f06f0_((double)FLOAT_80439050,piVar4[3],(int)*psVar3);
            }
            else if (psVar3[2] == 0) {
              zz_00f0414_(piVar4[3],(int)*psVar3);
            }
          }
        }
      }
      iVar5 = iVar5 + 1;
      piVar4 = piVar4 + 4;
    } while (iVar5 < 8);
    iVar6 = iVar6 + 1;
    puVar7 = puVar7 + 0x80;
  } while (iVar6 < 6);
  if (DAT_803d3b36 == '\x02') {
    DAT_803d3b36 = '\0';
  }
  return;
}



// ==== 800f0104  zz_00f0104_ ====

/* WARNING: Removing unreachable block (ram,0x800f01c8) */

void zz_00f0104_(int param_1,uint param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  short *psVar4;
  
  bVar1 = false;
  iVar2 = (param_3 & 0xff) * 0x10 + *(char *)(param_1 + 0x96) * 0x80;
  psVar4 = *(short **)(&DAT_803d3ae8 + iVar2 + 0x58);
  if (psVar4 == (short *)0x0) {
    bVar1 = true;
  }
  else if (*psVar4 != *(short *)(&PTR_DAT_8031b694)[param_2 & 0xff]) {
    zz_00f02d0_(param_1,param_2,param_3);
    bVar1 = true;
  }
  if (bVar1) {
    *(undefined **)(&DAT_803d3ae8 + iVar2 + 0x58) = (&PTR_DAT_8031b694)[param_2 & 0xff];
    uVar3 = gnt4_OSGetTick_bl();
    *(undefined4 *)(&DAT_803d3ae8 + iVar2 + 0x50) = uVar3;
    psVar4 = *(short **)(&DAT_803d3ae8 + iVar2 + 0x58);
    if (psVar4[2] == 1) {
      zz_00f061c_((double)FLOAT_80439050,param_1,(int)*psVar4);
    }
    else if (psVar4[2] == 0) {
      zz_00f036c_(param_1,(int)*psVar4);
    }
  }
  *(int *)(&DAT_803d3ae8 + iVar2 + 0x5c) = param_1;
  *(undefined4 *)(&DAT_803d3ae8 + iVar2 + 0x54) = 2;
  return;
}



// ==== 800f0214  zz_00f0214_ ====

/* WARNING: Removing unreachable block (ram,0x800f028c) */

void zz_00f0214_(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  short *psVar4;
  
  puVar2 = (&PTR_DAT_8031b694)[param_2 & 0xff];
  iVar1 = (param_3 & 0xff) * 0x10 + *(char *)(param_1 + 0x96) * 0x80;
  *(int *)(&DAT_803d3ae8 + iVar1 + 0x5c) = param_1;
  *(undefined **)(&DAT_803d3ae8 + iVar1 + 0x58) = puVar2;
  uVar3 = gnt4_OSGetTick_bl();
  *(undefined4 *)(&DAT_803d3ae8 + iVar1 + 0x50) = uVar3;
  psVar4 = *(short **)(&DAT_803d3ae8 + iVar1 + 0x58);
  if (psVar4[2] == 1) {
    zz_00f061c_((double)FLOAT_80439050,param_1,(int)*psVar4);
  }
  else if (psVar4[2] == 0) {
    zz_00f036c_(param_1,(int)*psVar4);
  }
  *(undefined4 *)(&DAT_803d3ae8 + iVar1 + 0x54) = 2;
  return;
}



// ==== 800f02d0  zz_00f02d0_ ====

/* WARNING: Removing unreachable block (ram,0x800f0338) */

void zz_00f02d0_(int param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = (param_3 & 0xff) * 0x10 + *(char *)(param_1 + 0x96) * 0x80;
  *(int *)(&DAT_803d3ae8 + iVar1 + 0x5c) = param_1;
  iVar3 = *(int *)(&DAT_803d3ae8 + iVar1 + 0x58);
  if (iVar3 != 0) {
    uVar2 = (uint)*(short *)(iVar3 + 2);
    if (uVar2 != 0xff) {
      if (*(short *)(iVar3 + 4) == 1) {
        zz_00f036c_(param_1,uVar2);
      }
      else if (*(short *)(iVar3 + 4) == 0) {
        zz_00f036c_(param_1,uVar2);
      }
    }
    *(undefined4 *)(&DAT_803d3ae8 + iVar1 + 0x5c) = 0;
    *(undefined4 *)(&DAT_803d3ae8 + iVar1 + 0x50) = 0;
    *(undefined4 *)(&DAT_803d3ae8 + iVar1 + 0x58) = 0;
  }
  return;
}



// ==== 800f036c  zz_00f036c_ ====

void zz_00f036c_(int param_1,uint param_2)

{
  if (param_1 == 0) {
    zz_00efb3c_(param_2,0,0x7f,0x40,0x2000);
  }
  else {
    zz_00f04b4_(param_2,(float *)(param_1 + 0x20),(int)*(char *)(param_1 + 0x96));
  }
  return;
}



// ==== 800f03c0  zz_00f03c0_ ====

void zz_00f03c0_(int param_1,uint param_2)

{
  if (param_1 == 0) {
    zz_00efc04_(param_2,0,0x7f,0x40,0x2000);
  }
  else {
    zz_00f052c_(param_2,(float *)(param_1 + 0x20),(int)*(char *)(param_1 + 0x96));
  }
  return;
}



// ==== 800f0414  zz_00f0414_ ====

void zz_00f0414_(int param_1,uint param_2)

{
  if (param_1 == 0) {
    zz_00efcb8_(param_2,0,0x7f,0x40,0x2000);
  }
  else {
    zz_00f05a4_(param_2,(float *)(param_1 + 0x20),(int)*(char *)(param_1 + 0x96));
  }
  return;
}



// ==== 800f0468  zz_00f0468_ ====

void zz_00f0468_(int param_1,uint param_2,int param_3)

{
  if (param_1 == 0) {
    zz_00efb3c_(param_2,param_3,0x7f,0x40,0x2000);
  }
  else {
    zz_00f04b4_(param_2,(float *)(param_1 + 0x20),param_3);
  }
  return;
}



// ==== 800f04b4  zz_00f04b4_ ====

void zz_00f04b4_(uint param_1,float *param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = zz_00f0a74_(param_2,0x7f);
  uVar2 = zz_00f0c24_(param_2);
  zz_00efb3c_(param_1,param_3,uVar1,uVar2,0x2000);
  return;
}



// ==== 800f052c  zz_00f052c_ ====

void zz_00f052c_(uint param_1,float *param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = zz_00f0a74_(param_2,0x7f);
  uVar2 = zz_00f0c24_(param_2);
  zz_00efc04_(param_1,param_3,uVar1,uVar2,0x2000);
  return;
}



// ==== 800f05a4  zz_00f05a4_ ====

void zz_00f05a4_(uint param_1,float *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = zz_00f0a74_(param_2,0x7f);
  iVar2 = zz_00f0c24_(param_2);
  zz_00efcb8_(param_1,param_3,uVar1,iVar2,0x2000);
  return;
}



// ==== 800f061c  zz_00f061c_ ====

void zz_00f061c_(double param_1,int param_2,uint param_3)

{
  int iVar1;
  float afStack_28 [5];
  
  if (param_2 == 0) {
    zz_00f036c_(0,param_3);
  }
  else {
    iVar1 = (int)(char)PTR_DAT_80433930[0x28];
    if ((&DAT_803c7695)[iVar1 * 0x3e4] == *(char *)(param_2 + 0x96)) {
      gnt4_PSVECSubtract_bl
                ((float *)(&DAT_803c7698 + iVar1 * 0xf9),(float *)(param_2 + 0x20),afStack_28);
      gnt4_PSQUATScale_bl(param_1,afStack_28,afStack_28);
      gnt4_PSVECAdd_bl((float *)(&DAT_803c7698 + iVar1 * 0xf9),afStack_28,afStack_28);
      zz_00f04b4_(param_3,afStack_28,(int)*(char *)(param_2 + 0x96));
    }
    else {
      zz_00f036c_(param_2,param_3);
    }
  }
  return;
}



// ==== 800f06f0  zz_00f06f0_ ====

void zz_00f06f0_(double param_1,int param_2,uint param_3)

{
  int iVar1;
  float afStack_28 [5];
  
  if (param_2 == 0) {
    zz_00f0414_(0,param_3);
  }
  else {
    iVar1 = (int)(char)PTR_DAT_80433930[0x28];
    if ((&DAT_803c7695)[iVar1 * 0x3e4] == *(char *)(param_2 + 0x96)) {
      gnt4_PSVECSubtract_bl
                ((float *)(&DAT_803c7698 + iVar1 * 0xf9),(float *)(param_2 + 0x20),afStack_28);
      gnt4_PSQUATScale_bl(param_1,afStack_28,afStack_28);
      gnt4_PSVECAdd_bl((float *)(&DAT_803c7698 + iVar1 * 0xf9),afStack_28,afStack_28);
      zz_00f05a4_(param_3,afStack_28,(int)*(char *)(param_2 + 0x96));
    }
    else {
      zz_00f0414_(param_2,param_3);
    }
  }
  return;
}



// ==== 800f07c4  zz_00f07c4_ ====

void zz_00f07c4_(void)

{
  zz_00efe70_();
  zz_00f14d4_();
  return;
}



// ==== 800f07e8  zz_00f07e8_ ====

void zz_00f07e8_(int param_1)

{
  byte bVar1;
  
  bVar1 = (&PTR_DAT_8031b7f4)[*(char *)(param_1 + 1000)][*(byte *)(param_1 + 0x3e9)];
  if ((bVar1 & 0x80) == 0) {
    zz_00f036c_(param_1,(int)*(short *)(&DAT_80434410 + (uint)bVar1 * 2));
  }
  else {
    zz_00f061c_((double)FLOAT_80439050,param_1,(int)*(short *)(&DAT_80434410 + (bVar1 & 0x7f) * 2));
  }
  return;
}



// ==== 800f0854  zz_00f0854_ ====

void zz_00f0854_(int param_1)

{
  zz_00f036c_(param_1,*(uint *)(&DAT_8031b834 + *(char *)(param_1 + 1000) * 4));
  return;
}



// ==== 800f088c  zz_00f088c_ ====

void zz_00f088c_(uint param_1,float *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if (*(char *)(param_3 + 0x88) == '\x04') {
    uVar4 = 0xc;
    iVar3 = 0;
    iVar2 = (int)DAT_8031b88c;
  }
  else {
    uVar4 = param_1 & 0xffffff3f;
    iVar2 = (int)*(short *)(&DAT_8031b874 + uVar4 * 2);
    if ((param_1 & 0x40) != 0) {
      uVar4 = uVar4 + 0xc;
      iVar2 = iVar2 + 0x18;
    }
    iVar3 = (int)*(char *)(param_3 + 0x96);
  }
  bVar1 = (&DAT_803d3ae8)[uVar4 + iVar3 * 0xd];
  (&DAT_803d3ae8)[uVar4 + iVar3 * 0xd] = bVar1 + 1;
  zz_00f04b4_(iVar2 + (bVar1 & 1),param_2,iVar3);
  return;
}



// ==== 800f0920  zz_00f0920_ ====

void zz_00f0920_(uint param_1)

{
  zz_00f0f64_(0,1,param_1);
  return;
}



// ==== 800f094c  zz_00f094c_ ====

void zz_00f094c_(int param_1)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  
  if (param_1 == 0) {
    DAT_803d3b37 = DAT_803d3b37 + -1;
    if (DAT_803d3b37 < '\x01') {
      DAT_803d3b37 = '\0';
      DAT_803d3b36 = 2;
    }
  }
  else {
    puVar4 = &DAT_803d3ae8;
    iVar2 = 0;
    DAT_803d3b36 = 1;
    DAT_803d3b37 = DAT_803d3b37 + '\x01';
    do {
      puVar3 = puVar4 + 0x50;
      iVar1 = 0;
      do {
        if (*(short **)(puVar3 + 8) != (short *)0x0) {
          zz_00efcb8_((int)**(short **)(puVar3 + 8),(int)*(char *)(*(int *)(puVar3 + 0xc) + 0x96),0,
                      0x40,0x2000);
        }
        iVar1 = iVar1 + 1;
        puVar3 = puVar3 + 0x10;
      } while (iVar1 < 8);
      iVar2 = iVar2 + 1;
      puVar4 = puVar4 + 0x80;
    } while (iVar2 < 6);
  }
  return;
}



// ==== 800f0a34  zz_00f0a34_ ====

void zz_00f0a34_(void)

{
  DAT_803d3b36 = 0;
  DAT_803d3b37 = 0;
  return;
}



// ==== 800f0a4c  zz_00f0a4c_ ====

void zz_00f0a4c_(void)

{
  DAT_803d3e3c = 1;
  return;
}



// ==== 800f0a60  zz_00f0a60_ ====

void zz_00f0a60_(void)

{
  DAT_803d3e3c = 0;
  return;
}



// ==== 800f0a74  zz_00f0a74_ ====

/* WARNING: Removing unreachable block (ram,0x800f0bfc) */
/* WARNING: Removing unreachable block (ram,0x800f0bf4) */
/* WARNING: Removing unreachable block (ram,0x800f0a8c) */
/* WARNING: Removing unreachable block (ram,0x800f0a84) */

int zz_00f0a74_(float *param_1,int param_2)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_48;
  float local_44;
  float local_40;
  
  if ((char)PTR_DAT_80433930[0xc] < '\0') {
    iVar2 = 0x7f;
  }
  else {
    if ((PTR_DAT_80433930[0x29] == '\0') || (PTR_DAT_80433930[0x33] == '\x01')) {
      iVar2 = 1;
    }
    else if (PTR_DAT_80433930[0x29] == '\x02') {
      iVar2 = 4;
    }
    else {
      iVar2 = 2;
    }
    dVar6 = (double)FLOAT_80439054;
    dVar7 = (double)FLOAT_80439058;
    for (iVar4 = 0; iVar4 < iVar2; iVar4 = iVar4 + 1) {
      uVar3 = zz_00f0d70_(param_1,(int)(char)PTR_DAT_80433930[iVar4 + 0xc]);
      if ((int)uVar3 < 0) {
        dVar5 = (double)FLOAT_80439054;
      }
      else {
        local_48 = *param_1;
        local_44 = param_1[1];
        local_40 = param_1[2];
        gnt4_PSVECSubtract_bl
                  (&local_48,(float *)(&DAT_803c7698 + (char)PTR_DAT_80433930[iVar4 + 0xc] * 0xf9),
                   &local_48);
        dVar5 = gnt4_PSVECMag_bl(&local_48);
      }
      if ((dVar7 < dVar5) && ((dVar5 < dVar6 || (dVar6 < dVar7)))) {
        dVar6 = dVar5;
      }
    }
    if ((double)FLOAT_80439058 <= dVar6) {
      fVar1 = (float)(dVar6 / (double)FLOAT_80439060);
      if (FLOAT_8043905c < (float)(dVar6 / (double)FLOAT_80439060)) {
        fVar1 = FLOAT_8043905c;
      }
      iVar2 = param_2 - (int)fVar1;
      if (iVar2 < 0x20) {
        iVar2 = 0x20;
      }
    }
    else {
      iVar2 = 0x20;
    }
  }
  return iVar2;
}



// ==== 800f0c24  zz_00f0c24_ ====

int zz_00f0c24_(float *param_1)

{
  int iVar1;
  uint uVar2;
  float local_58;
  float fStack_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float afStack_40 [15];
  
  if ((char)PTR_DAT_80433930[0xc] < '\0') {
    iVar1 = 0x40;
  }
  else {
    local_4c = *param_1;
    local_48 = param_1[1];
    local_44 = param_1[2];
    if ((PTR_DAT_80433930[0x29] == '\0') || (PTR_DAT_80433930[0x33] == '\x01')) {
      iVar1 = (char)PTR_DAT_80433930[0xc] * 0x3e4;
      uVar2 = zz_00f0d70_(&local_4c,(int)(char)PTR_DAT_80433930[0xc]);
      if (uVar2 == 1) {
        gnt4_PSMTXInverse_bl((float *)(&DAT_803c7714 + iVar1),afStack_40);
        gnt4_PSMTXMultVec_bl(afStack_40,&local_4c,&local_58);
        local_50 = -local_50;
        gnt4_PSMTXMultVec_bl((float *)(&DAT_803c7714 + iVar1),&local_58,&local_4c);
      }
      gnt4_GXProject_bl((double)local_4c,(double)local_48,(double)local_44,
                        (float *)(&DAT_803c7744 + iVar1),(float *)&DAT_803c0fd8,
                        (float *)&DAT_803c0fc0,&local_58,&fStack_54,&local_50);
      if (FLOAT_80439058 < local_58) {
        if (local_58 < FLOAT_80439064) {
          iVar1 = (int)(local_58 / FLOAT_80439068);
        }
        else {
          iVar1 = 0x7f;
        }
      }
      else {
        iVar1 = 0;
      }
    }
    else {
      iVar1 = 0x40;
    }
  }
  return iVar1;
}



// ==== 800f0d70  zz_00f0d70_ ====

uint zz_00f0d70_(float *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (param_2 < 0) {
    uVar1 = 0xffffffff;
  }
  else {
    iVar2 = param_2 * 0x3e4;
    local_1c = *(float *)(&DAT_803c771c + iVar2);
    local_18 = *(undefined4 *)(&DAT_803c772c + iVar2);
    local_14 = *(undefined4 *)(&DAT_803c773c + iVar2);
    local_28 = (float)(&DAT_803c7720)[param_2 * 0xf9];
    local_24 = (&DAT_803c7730)[param_2 * 0xf9];
    local_20 = (&DAT_803c7740)[param_2 * 0xf9];
    dVar3 = gnt4_PSVECMag_bl(&local_1c);
    if ((dVar3 <= (double)FLOAT_8043906c) ||
       (dVar3 = gnt4_PSVECMag_bl(&local_28), dVar3 <= (double)FLOAT_8043906c)) {
      uVar1 = 0xffffffff;
    }
    else {
      gnt4_PSVECSubtract_bl(param_1,&local_28,&local_28);
      gnt4_PSVECNormalize_bl(&local_1c,&local_1c);
      gnt4_PSVECNormalize_bl(&local_28,&local_28);
      dVar3 = gnt4_PSQUATDotProduct_bl(&local_28,&local_1c);
      uVar1 = (uint)(dVar3 < (double)FLOAT_80439058);
    }
  }
  return uVar1;
}



// ==== 800f0e5c  zz_00f0e5c_ ====

void zz_00f0e5c_(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  zz_00efafc_((undefined1 *)(param_2 + 4),*(undefined4 *)(param_2 + 4),4);
  zz_00efafc_((undefined1 *)(param_2 + 8),*(undefined4 *)(param_2 + 8),4);
  zz_00efafc_((undefined1 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 0xc),4);
  iVar2 = param_2 + 0x10;
  for (uVar1 = 0; uVar1 < *(uint *)(param_2 + 0xc); uVar1 = uVar1 + 1) {
    zz_00efafc_((undefined1 *)(iVar2 + 4),(uint)*(ushort *)(iVar2 + 4),2);
    zz_00efafc_((undefined1 *)(iVar2 + 10),(int)*(short *)(iVar2 + 10),2);
    iVar2 = iVar2 + 0x10;
  }
  *(int *)(&DAT_803d3e40 + param_1 * 8) = param_2;
  *(int *)(&DAT_803d3e44 + param_1 * 8) = param_2 + 0x10;
  return;
}



// ==== 800f0f14  zz_00f0f14_ ====

uint zz_00f0f14_(void)

{
  uint uVar1;
  
  uVar1 = zz_00efac8_();
  return uVar1 & 0xff;
}



// ==== 800f0f38  zz_00f0f38_ ====

void zz_00f0f38_(uint param_1)

{
  if (3 < param_1) {
    param_1 = 1;
  }
  zz_00ed4c4_(param_1);
  return;
}



// ==== 800f0f64  zz_00f0f64_ ====

void zz_00f0f64_(int param_1,int param_2,uint param_3)

{
  zz_00ed5e0_(param_1,param_2,param_3);
  return;
}



// ==== 800f0f84  zz_00f0f84_ ====

/* WARNING: Removing unreachable block (ram,0x800f1008) */

void zz_00f0f84_(uint param_1,uint param_2,int param_3,int param_4,uint param_5,int param_6,
                char param_7)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  uint uVar9;
  uint local_48;
  char local_44;
  char local_43;
  undefined2 local_42;
  undefined1 local_40;
  undefined1 local_3f;
  undefined2 local_3e;
  char local_3c;
  char local_3b;
  
  uVar9 = (param_1 & 0x7f) << 0x10;
  iVar5 = -1;
  do {
    if (0x7f < (int)param_2) {
      return;
    }
    pcVar8 = (char *)(*(int *)(&DAT_803d3e44 + param_1 * 8) + param_2 * 0x10);
    cVar2 = *pcVar8;
    uVar3 = (uint)((byte)pcVar8[6] >> 7);
    uVar4 = ((byte)pcVar8[6] & 0x7f) + param_3 & 0x7f;
    if (cVar2 == '\x01') {
      local_48 = uVar9 | (param_2 & 0x7f) << 8 | uVar3 << 7 | uVar4 | 0x7000000;
      local_44 = pcVar8[2] + param_7;
      local_43 = pcVar8[3];
      iVar5 = zz_00ed684_(&local_48);
    }
    else if (cVar2 == '\0') {
      if (param_5 == 0xffffffff) {
        param_5 = (uint)(byte)pcVar8[9];
        if (param_5 == 0xff) {
          param_5 = 0x40;
        }
      }
      else if ((byte)pcVar8[9] != 0xff) {
        param_5 = ((byte)pcVar8[9] + param_5) - 0x40;
        if ((int)param_5 < 0) {
          param_5 = 0;
        }
        if (0x7f < (int)param_5) {
          param_5 = 0x7f;
        }
      }
      if (pcVar8[0xd] == '\0') {
        iVar5 = (int)*(short *)(pcVar8 + 10);
      }
      else {
        uVar6 = zz_00f0f14_();
        iVar5 = -1;
        if ((uVar6 & 1) != 0) {
          iVar5 = 1;
        }
        uVar6 = zz_00f0f14_();
        iVar5 = (int)*(short *)(pcVar8 + 10) +
                iVar5 * (uVar6 - (uVar6 / (byte)pcVar8[0xd]) * (uint)(byte)pcVar8[0xd]) * 0x20;
      }
      bVar1 = param_6 == -1;
      param_6 = iVar5 + param_6;
      if (bVar1) {
        param_6 = iVar5 + 0x2000;
      }
      if (param_6 < 0) {
        param_6 = 0;
      }
      if (0x3fff < param_6) {
        param_6 = 0x3fff;
      }
      uVar6 = (uint)(byte)pcVar8[8];
      if (uVar6 == 0xff) {
        uVar6 = 0x7f;
      }
      if (pcVar8[0xc] != '\0') {
        uVar7 = zz_00f0f14_();
        iVar5 = -1;
        if ((uVar7 & 1) != 0) {
          iVar5 = 1;
        }
        uVar7 = zz_00f0f14_();
        uVar6 = uVar6 + iVar5 * (uVar7 - (uVar7 / (byte)pcVar8[0xc]) * (uint)(byte)pcVar8[0xc]);
      }
      if (param_4 == -1) {
        param_4 = 0x7f;
      }
      iVar5 = (int)(param_4 * uVar6) / 0x7f + ((int)(param_4 * uVar6) >> 0x1f);
      param_4 = iVar5 - (iVar5 >> 0x1f);
      if (param_4 < 0) {
        param_4 = 0;
      }
      if (0x7f < param_4) {
        param_4 = 0x7f;
      }
      local_48 = uVar9 | (param_2 & 0x7f) << 8 | uVar3 << 7 | uVar4;
      local_44 = pcVar8[2];
      local_43 = pcVar8[3];
      local_42 = *(undefined2 *)(pcVar8 + 4);
      local_3b = pcVar8[7];
      local_40 = (undefined1)param_4;
      local_3f = (undefined1)param_5;
      local_3e = (undefined2)param_6;
      local_3c = param_7;
      iVar5 = zz_00ed614_(&local_48);
    }
    else if (cVar2 == -1) {
      iVar5 = 0;
    }
    if (iVar5 < 0) {
      return;
    }
    param_2 = (uint)(byte)pcVar8[0xf];
    if (param_2 == 0xff) {
      return;
    }
  } while (*pcVar8 != -1);
  return;
}



// ==== 800f1238  zz_00f1238_ ====

/* WARNING: Removing unreachable block (ram,0x800f12c0) */

void zz_00f1238_(uint param_1,uint param_2,int param_3,int param_4,int param_5,int param_6,
                char param_7,int param_8)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  uint uVar8;
  int iVar9;
  uint local_48;
  char local_44;
  char local_43;
  undefined2 local_42;
  undefined1 local_40;
  undefined1 local_3f;
  undefined2 local_3e;
  char local_3c;
  char local_3b;
  
  uVar8 = (param_1 & 0x7f) << 0x10;
  iVar4 = -1;
  do {
    if (0x7f < (int)param_2) {
      return;
    }
    pcVar7 = (char *)(*(int *)(&DAT_803d3e44 + param_1 * 8) + param_2 * 0x10);
    cVar1 = *pcVar7;
    uVar2 = (uint)((byte)pcVar7[6] >> 7);
    uVar3 = ((byte)pcVar7[6] & 0x7f) + param_3 & 0x7f;
    if (cVar1 == '\x01') {
      local_48 = uVar8 | (param_2 & 0x7f) << 8 | uVar2 << 7 | uVar3 | 0x7000000;
      local_44 = pcVar7[2] + param_7;
      local_43 = pcVar7[3];
      iVar4 = zz_00ed684_(&local_48);
    }
    else if (cVar1 == '\0') {
      if ((param_5 != -1) && ((byte)pcVar7[9] != 0xff)) {
        param_5 = (uint)(byte)pcVar7[9] + param_5 + -0x40;
        if (param_5 < 0) {
          param_5 = 0;
        }
        if (0x7f < param_5) {
          param_5 = 0x7f;
        }
      }
      if (param_6 != -1) {
        iVar4 = (int)*(short *)(pcVar7 + 10);
        if (pcVar7[0xd] != '\0') {
          uVar5 = zz_00f0f14_();
          iVar9 = -1;
          if ((uVar5 & 1) != 0) {
            iVar9 = 1;
          }
          uVar5 = zz_00f0f14_();
          iVar4 = iVar4 + iVar9 * (uVar5 - (uVar5 / (byte)pcVar7[0xd]) * (uint)(byte)pcVar7[0xd]) *
                          0x20;
        }
        param_6 = param_6 + iVar4;
        if (param_6 < 0) {
          param_6 = 0;
        }
        if (0x3fff < param_6) {
          param_6 = 0x3fff;
        }
      }
      if (param_4 != -1) {
        uVar5 = (uint)(byte)pcVar7[8];
        if (uVar5 == 0xff) {
          uVar5 = 0x7f;
        }
        if (pcVar7[0xc] != '\0') {
          uVar6 = zz_00f0f14_();
          iVar4 = -1;
          if ((uVar6 & 1) != 0) {
            iVar4 = 1;
          }
          uVar6 = zz_00f0f14_();
          uVar5 = uVar5 + iVar4 * (uVar6 - (uVar6 / (byte)pcVar7[0xc]) * (uint)(byte)pcVar7[0xc]);
        }
        iVar4 = (int)(param_4 * uVar5) / 0x7f + ((int)(param_4 * uVar5) >> 0x1f);
        param_4 = iVar4 - (iVar4 >> 0x1f);
        if (param_4 < 0) {
          param_4 = 0;
        }
        if (0x7f < param_4) {
          param_4 = 0x7f;
        }
      }
      local_40 = (undefined1)param_4;
      local_3f = (undefined1)param_5;
      local_48 = uVar8 | (param_2 & 0x7f) << 8 | uVar2 << 7 | uVar3 | 0x7000000;
      local_3e = (undefined2)param_6;
      local_44 = pcVar7[2];
      local_43 = pcVar7[3];
      local_42 = *(undefined2 *)(pcVar7 + 4);
      local_3b = pcVar7[7];
      local_3c = param_7;
      if (param_8 == 0) {
        iVar4 = zz_00ed6f4_(&local_48);
      }
      else {
        iVar4 = zz_00ed764_(&local_48);
      }
    }
    else if (cVar1 == -1) {
      iVar4 = 0;
    }
    if (iVar4 < 0) {
      return;
    }
    param_2 = (uint)(byte)pcVar7[0xf];
    if (param_2 == 0xff) {
      return;
    }
  } while (*pcVar7 != -1);
  return;
}



// ==== 800f14d4  zz_00f14d4_ ====

void zz_00f14d4_(void)

{
  zz_00ed7d4_(0,0x10,0);
  return;
}



// ==== 800f1500  zz_00f1500_ ====

void zz_00f1500_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = 8;
  uVar1 = ARInit(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803d4280,8,
                 param_11,param_12,param_13,param_14,param_15,param_16);
  gnt4_ARQInit_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar1,uVar2,
                  param_11,param_12,param_13,param_14,param_15,param_16);
  DAT_803d4060 = 0;
  DAT_803d4062 = 0;
  DAT_803d4084 = 0;
  DAT_803d4086 = 0;
  DAT_803d40a8 = 0;
  DAT_803d40aa = 0;
  DAT_803d40cc = 0;
  DAT_803d40ce = 0;
  DAT_803d40f0 = 0;
  DAT_803d40f2 = 0;
  DAT_803d4114 = 0;
  DAT_803d4116 = 0;
  DAT_803d4138 = 0;
  DAT_803d413a = 0;
  DAT_803d415c = 0;
  DAT_803d415e = 0;
  DAT_803d4180 = 0;
  DAT_803d4182 = 0;
  DAT_803d41a4 = 0;
  DAT_803d41a6 = 0;
  DAT_803d41c8 = 0;
  DAT_803d41ca = 0;
  DAT_803d41ec = 0;
  DAT_803d41ee = 0;
  DAT_803d4210 = 0;
  DAT_803d4212 = 0;
  DAT_803d4234 = 0;
  DAT_803d4236 = 0;
  DAT_803d4258 = 0;
  DAT_803d425a = 0;
  DAT_803d427c = 0;
  DAT_803d427e = 0;
  return;
}



// ==== 800f1614  zz_00f1614_ ====

int zz_00f1614_(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  
  gnt4_OSDisableInterrupts_bl();
  puVar1 = &DAT_803d4040;
  iVar2 = 0;
  iVar3 = 0x10;
  do {
    if (puVar1[0x22] == '\0') {
      (&DAT_803d4062)[iVar2 * 0x24] = 1;
      break;
    }
    puVar1 = puVar1 + 0x24;
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  gnt4_OSRestoreInterrupts_bl();
  if (iVar2 == 0x10) {
    iVar2 = -1;
  }
  return iVar2;
}



// ==== 800f169c  zz_00f169c_ ====

undefined8 zz_00f169c_(void)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  puVar1 = &DAT_803d4040;
  uVar3 = 0;
  iVar2 = 0;
  iVar4 = 2;
  do {
    if (*(short *)(puVar1 + 0x20) == 1) {
      uVar3 = uVar3 + 1;
    }
    if (*(short *)(puVar1 + 0x44) == 1) {
      uVar3 = uVar3 + 1;
    }
    if (*(short *)(puVar1 + 0x68) == 1) {
      uVar3 = uVar3 + 1;
    }
    if (*(short *)(puVar1 + 0x8c) == 1) {
      uVar3 = uVar3 + 1;
    }
    if (*(short *)(puVar1 + 0xb0) == 1) {
      uVar3 = uVar3 + 1;
    }
    if (*(short *)(puVar1 + 0xd4) == 1) {
      uVar3 = uVar3 + 1;
    }
    if (*(short *)(puVar1 + 0xf8) == 1) {
      uVar3 = uVar3 + 1;
    }
    if (*(short *)(puVar1 + 0x11c) == 1) {
      uVar3 = uVar3 + 1;
    }
    puVar1 = puVar1 + 0x120;
    iVar2 = iVar2 + 7;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if (uVar3 == 0x10) {
    return CONCAT44(0xffffffff,iVar2);
  }
  return CONCAT44((-uVar3 | uVar3) >> 0x1f,iVar2);
}



// ==== 800f177c  zz_00f177c_ ====

int zz_00f177c_(void)

{
  int iVar1;
  uint uVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  
  iVar1 = zz_00f1614_();
  uVar2 = zz_002a860_(0x100);
  iVar4 = 0;
  iVar5 = 8;
  do {
    puVar3 = (undefined1 *)(uVar2 + iVar4);
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0;
    puVar3 = (undefined1 *)(uVar2 + iVar4 + 8);
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0;
    puVar3 = (undefined1 *)(uVar2 + iVar4 + 0x10);
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0;
    puVar3 = (undefined1 *)(uVar2 + iVar4 + 0x18);
    iVar4 = iVar4 + 0x20;
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  gnt4_DCFlushRange_bl(uVar2,0x100);
  iVar4 = ARAlloc(0x100);
  gnt4_OSDisableInterrupts_bl();
  (&DAT_803d4060)[iVar1 * 0x12] = 1;
  gnt4_ARQPostRequest_bl
            ((undefined4 *)(&DAT_803d4040 + iVar1 * 0x24),0x309,0,1,uVar2,iVar4,0x100,-0x7ff0ea38);
  gnt4_OSRestoreInterrupts_bl();
  do {
    uVar6 = zz_00f169c_();
  } while ((int)((ulonglong)uVar6 >> 0x20) != 0);
  gnt4_OSFreeToHeap_bl(DAT_80435c60,uVar2);
  return iVar4;
}



// ==== 800f18fc  zz_00f18fc_ ====

void zz_00f18fc_(void)

{
  DAT_80436348 = ARAlloc(0xd00000);
  return;
}



// ==== 800f1924  zz_00f1924_ ====

undefined4 zz_00f1924_(void)

{
  return DAT_80436348;
}



// ==== 800f192c  zz_00f192c_ ====

undefined4 zz_00f192c_(uint param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  iVar2 = zz_00f1614_();
  if (iVar2 < 0) {
    uVar3 = 0;
  }
  else {
    gnt4_DCFlushRange_bl(param_1,param_3);
    gnt4_OSDisableInterrupts_bl();
    iVar1 = DAT_80436348;
    (&DAT_803d4060)[iVar2 * 0x12] = 1;
    gnt4_ARQPostRequest_bl
              ((undefined4 *)(&DAT_803d4040 + iVar2 * 0x24),0x309,0,1,param_1,iVar1 + param_2,
               param_3,-0x7ff0ea38);
    gnt4_OSRestoreInterrupts_bl();
    do {
      uVar4 = zz_00f169c_();
    } while ((int)((ulonglong)uVar4 >> 0x20) != 0);
    uVar3 = 1;
  }
  return uVar3;
}



// ==== 800f19f8  zz_00f19f8_ ====

undefined4 zz_00f19f8_(uint param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  iVar2 = zz_00f1614_();
  if (iVar2 < 0) {
    uVar3 = 0;
  }
  else {
    if (param_4 == 1) {
      gnt4_DCInvalidateRange_bl(param_1,param_3);
      gnt4_OSDisableInterrupts_bl();
      iVar1 = DAT_80436348;
      (&DAT_803d4060)[iVar2 * 0x12] = 1;
      gnt4_ARQPostRequest_bl
                ((undefined4 *)(&DAT_803d4040 + iVar2 * 0x24),0x309,1,1,iVar1 + param_2,param_1,
                 param_3,-0x7ff0ea38);
    }
    else if ((param_4 < 1) && (-1 < param_4)) {
      gnt4_DCFlushRange_bl(param_1,param_3);
      gnt4_OSDisableInterrupts_bl();
      iVar1 = DAT_80436348;
      (&DAT_803d4060)[iVar2 * 0x12] = 1;
      gnt4_ARQPostRequest_bl
                ((undefined4 *)(&DAT_803d4040 + iVar2 * 0x24),0x309,0,1,param_1,iVar1 + param_2,
                 param_3,-0x7ff0ea38);
    }
    gnt4_OSRestoreInterrupts_bl();
    do {
      uVar4 = zz_00f169c_();
    } while ((int)((ulonglong)uVar4 >> 0x20) != 0);
    uVar3 = 1;
  }
  return uVar3;
}



// ==== 800f1b28  FUN_800f1b28 ====

void FUN_800f1b28(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x208) || (*(short *)(param_1 + 1000) == 0x20e)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800f1c38;
    *(code **)(puVar1 + 0x10c) = FUN_800f1dc4;
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



// ==== 800f1c38  FUN_800f1c38 ====

void FUN_800f1c38(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8031b890)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800f1c8c  FUN_800f1c8c ====

void FUN_800f1c8c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  int iVar2;
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
  fVar1 = FLOAT_80439070;
  *(undefined1 *)(param_9 + 0x84) = 0xc0;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_80434440)[*(char *)(param_9 + 0x11)],iVar4 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  iVar2 = (int)(char)(&DAT_80434440)[*(char *)(param_9 + 0x11)];
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80439074,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00f1d88_(param_9);
  return;
}



// ==== 800f1d88  zz_00f1d88_ ====

void zz_00f1d88_(int param_1)

{
  *(undefined1 *)(param_1 + 0x89) = 7;
  return;
}



// ==== 800f1da4  FUN_800f1da4 ====

void FUN_800f1da4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f1dc4  FUN_800f1dc4 ====

void FUN_800f1dc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = 0x44;
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar2 = *(int *)(param_9 + 0xe0);
    uVar1 = 0x45;
  }
  else {
    iVar2 = *(int *)(param_9 + 0xe4);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar2,uVar1);
  return;
}



// ==== 800f1e30  zz_00f1e30_ ====

void zz_00f1e30_(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  iVar1 = zz_006ec84_(param_1);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031b8a0)[*(char *)(param_1 + 0x540)])(param_1,param_2);
  return;
}



// ==== 800f1eb8  FUN_800f1eb8 ====

void FUN_800f1eb8(int param_1,undefined2 *param_2)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80439080;
  fVar1 = FLOAT_80439078;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) =
       (float)((double)CONCAT44(0x43300000,(int)(short)param_2[6] ^ 0x80000000) - dVar2);
  *(char *)(param_1 + 0x6ef) = (char)param_2[7];
  *(char *)(param_1 + 0x6f7) = (char)*param_2;
  if (*(short *)(param_1 + (short)param_2[1] * 8 + 0x774) < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  zz_006ea9c_(param_1);
  *(undefined1 *)(param_1 + 0x543) = 1;
  if (*(char *)(param_1 + 0x5db) == '\x01') {
    *(undefined1 *)(param_1 + 0x543) = 0xf;
  }
  zz_004beb8_((double)FLOAT_8043907c,param_1,(int)*(char *)(param_1 + 0x543),2,
              (int)*(char *)(param_1 + 0x6f7),0xffffffff,0xffffffff);
  return;
}



// ==== 800f1f9c  FUN_800f1f9c ====

void FUN_800f1f9c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = zz_006ea9c_(param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800f2008  FUN_800f2008 ====

void FUN_800f2008(int param_1,int param_2)

{
  int iVar1;
  
  zz_004cd24_(param_1,1);
  zz_006ea9c_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    iVar1 = zz_006dbe0_(param_1,(int)*(short *)(param_2 + 2),1,0);
    if (iVar1 == 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
      if (*(char *)(param_1 + 0x5db) != '\x01') {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      zz_004beb8_((double)FLOAT_8043907c,param_1,(int)*(char *)(param_1 + 0x543),2,
                  *(char *)(param_1 + 0x6f7) + 2,0xffffffff,0xffffffff);
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x543) = 1;
      if (*(char *)(param_1 + 0x5db) == '\x01') {
        *(undefined1 *)(param_1 + 0x543) = 0xf;
      }
      zz_004beb8_((double)FLOAT_8043907c,param_1,(int)*(char *)(param_1 + 0x543),2,
                  *(char *)(param_1 + 0x6f7) + 1,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 800f2118  FUN_800f2118 ====

void FUN_800f2118(int param_1,int param_2)

{
  int iVar1;
  
  zz_004cd24_(param_1,1);
  zz_006ea9c_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x542) = 1;
    zz_00665cc_(param_1);
    if (*(code **)(param_2 + 4) != (code *)0x0) {
      (**(code **)(param_2 + 4))(param_1);
    }
  }
  if (((*(char *)(param_1 + 0x541) == '\0') && (*(code **)(param_2 + 8) != (code *)0x0)) &&
     (iVar1 = (**(code **)(param_2 + 8))(param_1), iVar1 != 0)) {
    zz_006bf80_(param_1);
    *(undefined1 *)(param_1 + 0x543) = 1;
    if (*(char *)(param_1 + 0x5db) == '\x01') {
      *(undefined1 *)(param_1 + 0x543) = 0xf;
    }
    zz_004beb8_((double)FLOAT_8043907c,param_1,(int)*(char *)(param_1 + 0x543),2,
                *(char *)(param_1 + 0x6f7) + 1,0xffffffff,0xffffffff);
    return;
  }
  if (((('\0' < *(char *)(param_1 + 0x542)) && ((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0)) ||
      (*(char *)(param_1 + 0x1cee) != '\0')) &&
     ((*(code **)(param_2 + 0x10) == (code *)0x0 ||
      (iVar1 = (**(code **)(param_2 + 0x10))(param_1), iVar1 != 0)))) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(char *)(param_1 + 0x5db) != '\x01') {
      *(undefined1 *)(param_1 + 0x543) = 1;
    }
    zz_004beb8_((double)FLOAT_8043907c,param_1,(int)*(char *)(param_1 + 0x543),2,
                *(char *)(param_1 + 0x6f7) + 2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800f22a8  FUN_800f22a8 ====

void FUN_800f22a8(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  double dVar2;
  double dVar3;
  
  dVar3 = DOUBLE_80439080;
  dVar2 = (double)FLOAT_8043908c;
  uVar1 = (int)*(short *)(param_9 + 0x18e0) ^ 0x80000000;
  *(short *)(param_9 + 0x18e0) =
       (short)(int)((double)(float)((double)CONCAT44(0x43300000,uVar1) - DOUBLE_80439080) * dVar2);
  *(short *)(param_9 + 0x18e2) =
       (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(param_9 + 0x18e2) ^ 0x80000000)
                                   - dVar3) * dVar2);
  zz_004cd24_(param_9,1);
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) != 0) || (*(char *)(param_9 + 0x1cee) != '\0')) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(dVar2,dVar3,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,uVar1,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800f2374  zz_00f2374_ ====

void zz_00f2374_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031b8b4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800f23c4  FUN_800f23c4 ====

void FUN_800f23c4(int param_1,undefined1 param_2)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439090;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  *(undefined1 *)(param_1 + 0x746) = 0;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043907c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439088;
  return;
}



// ==== 800f2498  FUN_800f2498 ====

void FUN_800f2498(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80439094;
    fVar1 = FLOAT_80439088;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar2;
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_80439098 * *(float *)(param_1 + 0x760)) / fVar2;
    }
    if (FLOAT_8043909c < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 800f259c  FUN_800f259c ====

void FUN_800f259c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  fVar3 = FLOAT_80439094;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    fVar2 = FLOAT_80439088;
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar3;
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_80439098 * *(float *)(param_1 + 0x760)) / fVar3;
    }
    if (FLOAT_8043909c < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar4 = (double)FLOAT_8043907c;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xf);
    fVar3 = FLOAT_8043909c;
    if (FLOAT_80439088 < *(float *)(param_1 + 0x558)) {
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      if (*(float *)(param_1 + 0x760) <= fVar3) {
        *(undefined1 *)(param_1 + 0x1d9b) = 0;
      }
      else {
        zz_006ed8c_((double)FLOAT_804390a0,param_1);
        zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
      }
    }
    if ('\0' < *(char *)(param_1 + 0x1d10)) {
      zz_006d144_(param_1,0xc0);
    }
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a474_(param_1);
    }
    if (FLOAT_804390a4 < *(float *)(param_1 + 0x44)) {
      zz_00b22f4_(param_1);
    }
  }
  return;
}



// ==== 800f2764  zz_00f2764_ ====

void zz_00f2764_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031b8c0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800f27b4  FUN_800f27b4 ====

void FUN_800f27b4(int param_1,undefined1 param_2)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    if ((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    }
    else {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
    }
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439090;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804390a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043907c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439088;
  return;
}



// ==== 800f28d8  FUN_800f28d8 ====

void FUN_800f28d8(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804390a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_80439094;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_804390ac;
    fVar2 = FLOAT_80439088;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80439094;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 800f2a04  FUN_800f2a04 ====

void FUN_800f2a04(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_804390a8,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_804390ac,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  if (FLOAT_804390a4 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800f2abc  FUN_800f2abc ====

void FUN_800f2abc(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(undefined1 *)(param_1 + 0x541) = 0xff;
  }
  zz_006d144_(param_1,0xc0);
  if (*(float *)(param_1 + 0x760) <= FLOAT_804390ac) {
    *(undefined1 *)(param_1 + 0x1d9b) = 0;
  }
  else {
    zz_006ed8c_((double)FLOAT_804390a8,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    dVar1 = (double)FLOAT_8043907c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar1,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
  }
  if (FLOAT_804390a4 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800f2b98  FUN_800f2b98 ====

void FUN_800f2b98(int param_1)

{
  if (*(float *)(param_1 + 0x760) <= FLOAT_804390ac) {
    *(undefined1 *)(param_1 + 0x1d9b) = 0;
  }
  else {
    zz_006ed8c_((double)FLOAT_804390b0,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  if (FLOAT_804390a4 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800f2c3c  zz_00f2c3c_ ====

void zz_00f2c3c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031b8d4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800f2c8c  FUN_800f2c8c ====

void FUN_800f2c8c(int param_1,undefined1 param_2)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439090;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804390a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043907c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439088;
  return;
}



// ==== 800f2d98  FUN_800f2d98 ====

void FUN_800f2d98(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804390a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800f2e40  FUN_800f2e40 ====

void FUN_800f2e40(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  gnt4_PSQUATScale_bl((double)FLOAT_804390a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar3 = FLOAT_804390b4;
  fVar1 = FLOAT_80439078;
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_80439088;
    *(float *)(param_1 + 0x558) = fVar1;
    fVar1 = FLOAT_804390ac;
    *(float *)(param_1 + 0x44) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar1 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 800f2ef0  FUN_800f2ef0 ====

void FUN_800f2ef0(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_804390a8,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_80439088;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) goto LAB_800f2f9c;
  }
  else {
    *(float *)(param_1 + 0x4c) = FLOAT_80439088;
    *(float *)(param_1 + 0x44) = fVar2;
  }
  dVar3 = (double)FLOAT_8043907c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
LAB_800f2f9c:
  zz_00b22f4_(param_1);
  return;
}



// ==== 800f2fb8  FUN_800f2fb8 ====

void FUN_800f2fb8(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_804390b0,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800f3028  zz_00f3028_ ====

void zz_00f3028_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031b8e8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800f3078  FUN_800f3078 ====

void FUN_800f3078(int param_1,int param_2)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439090;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_8043907c,param_1,0xf,3,param_2,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439088;
  return;
}



// ==== 800f3148  FUN_800f3148 ====

void FUN_800f3148(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_80439094;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_804390ac;
    fVar2 = FLOAT_80439088;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80439094;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 800f3230  FUN_800f3230 ====

/* WARNING: Removing unreachable block (ram,0x800f3304) */
/* WARNING: Removing unreachable block (ram,0x800f3240) */

void FUN_800f3230(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_804390b0,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  else {
    dVar4 = (double)*(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x1dc8) = (float)(dVar4 * DOUBLE_804390b8);
    zz_004cd24_(param_1,0xf);
    *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  }
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_804390ac,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  if (FLOAT_804390a4 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800f3320  FUN_800f3320 ====

void FUN_800f3320(int param_1)

{
  if ((*(char *)(param_1 + 0x1cef) < '\0') || (*(char *)(param_1 + 0x1d9) != '\0')) {
    *(undefined1 *)(param_1 + 0x541) = 0xff;
  }
  zz_006d144_(param_1,0xc0);
  if (*(float *)(param_1 + 0x760) <= FLOAT_804390ac) {
    *(undefined1 *)(param_1 + 0x1d9b) = 0;
  }
  else {
    zz_006ed8c_((double)FLOAT_804390b0,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  if (FLOAT_804390a4 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800f33f4  zz_00f33f4_ ====

void zz_00f33f4_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031b8f8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800f3444  FUN_800f3444 ====

void FUN_800f3444(int param_1,int param_2)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439090;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_8043907c,param_1,0xf,3,param_2,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439088;
  return;
}



// ==== 800f3514  FUN_800f3514 ====

void FUN_800f3514(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80439078;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar2 = FLOAT_80439088;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = (FLOAT_804390c0 * fVar1) / FLOAT_80439078;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 800f360c  FUN_800f360c ====

void FUN_800f360c(int param_1)

{
  float fVar1;
  float fVar2;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_804390b0,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (-1 < *(char *)(param_1 + 0x1cef)) {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  if (FLOAT_804390a4 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800f36b0  FUN_800f36b0 ====

void FUN_800f36b0(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_804390a0,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  if (FLOAT_804390a4 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800f3738  zz_00f3738_ ====

void zz_00f3738_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031b908)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800f3788  FUN_800f3788 ====

void FUN_800f3788(int param_1,undefined1 param_2)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439090;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804390b0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043907c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800f38a8  FUN_800f38a8 ====

void FUN_800f38a8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804390b0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_804390c4;
    fVar1 = FLOAT_80439090;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < *(float *)(param_1 + 0x760)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}



// ==== 800f3974  FUN_800f3974 ====

void FUN_800f3974(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  fVar2 = FLOAT_80439088;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         (FLOAT_80439098 * *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c)
         ) / FLOAT_80439090;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_1c = *(float *)(iVar4 + 0x8e0);
    local_18 = *(float *)(iVar4 + 0x8f0);
    local_14 = *(undefined4 *)(iVar4 + 0x900);
    local_28 = *(float *)(param_1 + 0x518);
    local_20 = *(undefined4 *)(param_1 + 0x520);
    local_24 = FLOAT_804390c8 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_28,&local_1c,&local_1c);
    fVar2 = FLOAT_80439088;
    *(float *)(param_1 + 0x48) = local_18 / FLOAT_804390cc;
    local_18 = fVar2;
    dVar5 = gnt4_PSVECMag_bl(&local_1c);
    fVar1 = FLOAT_804390d0;
    fVar2 = FLOAT_80439088;
    *(float *)(param_1 + 0x44) = (float)(dVar5 / (double)FLOAT_804390cc);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x50) = fVar2;
  }
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_804390d4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80439088;
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) == 0) {
    uVar3 = FUN_80066838((double)FLOAT_804390d4,param_1);
    fVar2 = FLOAT_80439088;
    if (((int)uVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) {
      return;
    }
  }
  else {
    *(float *)(param_1 + 0x44) = FLOAT_804390d8;
    fVar1 = FLOAT_804390dc;
    *(float *)(param_1 + 0x4c) = fVar2;
    fVar2 = FLOAT_804390e0;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar2;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
  }
  fVar2 = FLOAT_80439090;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  return;
}



// ==== 800f3b7c  FUN_800f3b7c ====

void FUN_800f3b7c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x544) == '\0') {
      if ((*(char *)(param_1 + 0x1cf2) != '\0') || (*(char *)(param_1 + 0x1cee) != '\0')) {
        dVar4 = (double)FLOAT_8043907c;
        *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
        zz_004beb8_(dVar4,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
      }
    }
    FUN_80067310((double)FLOAT_804390d4,param_1,*(short *)(param_1 + 0x5ae));
    fVar2 = FLOAT_80439088;
    if (*(float *)(param_1 + 0x44) < FLOAT_80439088) {
      *(float *)(param_1 + 0x44) = FLOAT_80439088;
      *(float *)(param_1 + 0x4c) = fVar2;
    }
    iVar3 = zz_00677b0_(param_1);
    fVar2 = FLOAT_80439088;
    if (iVar3 == 0) {
      fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      *(float *)(param_1 + 0x558) = fVar1;
      if (fVar1 <= fVar2) {
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a750_(param_1,7);
      *(float *)(param_1 + 0x694) = FLOAT_804390d4 + *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}



// ==== 800f3cb4  zz_00f3cb4_ ====

void zz_00f3cb4_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031b918)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800f3d04  FUN_800f3d04 ====

void FUN_800f3d04(int param_1,undefined1 param_2)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439090;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804390b0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043907c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800f3e3c  FUN_800f3e3c ====

void FUN_800f3e3c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804390b0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80439094;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439078 * dVar4);
    dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
    fVar2 = FLOAT_804390c4;
    fVar1 = FLOAT_80439088;
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439078 * -dVar4);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    if (fVar2 < *(float *)(param_1 + 0x760)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}



// ==== 800f3f50  FUN_800f3f50 ====

void FUN_800f3f50(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar5 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439078 * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar6 = (double)FLOAT_804390d4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439078 * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_80439088;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (uVar4 = FUN_80066838((double)FLOAT_8043909c,param_1), 0 < (int)uVar4)) {
    dVar5 = (double)FLOAT_8043907c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800f404c  FUN_800f404c ====

void FUN_800f404c(int param_1)

{
  float fVar1;
  float fVar2;
  
  zz_006ed8c_((double)FLOAT_804390b0,param_1);
  FUN_80067310((double)FLOAT_804390d4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_80439088;
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) == 0) {
    if (-1 < *(char *)(param_1 + 0x1cef)) {
      return;
    }
  }
  else {
    *(float *)(param_1 + 0x44) = FLOAT_804390d8;
    fVar2 = FLOAT_804390dc;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
  }
  fVar1 = FLOAT_80439090;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  return;
}



// ==== 800f4104  FUN_800f4104 ====

void FUN_800f4104(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804390d4,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_80439088;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804390d4 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800f41c4  zz_00f41c4_ ====

void zz_00f41c4_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031b92c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800f4214  FUN_800f4214 ====

void FUN_800f4214(int param_1,undefined1 param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  double dVar5;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439090;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804390b0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    uVar3 = 0xffffffff;
    uVar4 = 0xffffffff;
  }
  else {
    uVar3 = 10;
    uVar4 = 2;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_8043907c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,uVar3,uVar4);
  return;
}



// ==== 800f4340  FUN_800f4340 ====

void FUN_800f4340(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804390b0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_80439088;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800f43f8  FUN_800f43f8 ====

void FUN_800f43f8(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSQUATScale_bl((double)FLOAT_804390b0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_80439094;
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804390e4 * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x18da));
    fVar2 = FLOAT_804390ac;
    fVar1 = FLOAT_80439088;
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804390e4 * -dVar3);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    if (fVar2 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 800f44e0  FUN_800f44e0 ====

void FUN_800f44e0(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x1d10) = 0;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
    zz_006e1ac_(param_1,0xc0,1);
  }
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804390e4 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_804390d4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804390e4 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_80439088;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    *(float *)(param_1 + 0x558) = fVar3;
    fVar2 = FLOAT_80439090;
    if (*(char *)(param_1 + 0x1b01) != '\0') {
      dVar4 = (double)FLOAT_8043907c;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar2;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 800f4610  FUN_800f4610 ====

void FUN_800f4610(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80439080) * FLOAT_804390a0);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804390d4,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  fVar3 = FLOAT_80439088;
  if (iVar4 == 0) {
    fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar2;
    if (fVar2 <= fVar3) {
      *(float *)(param_1 + 0x4c) = fVar3;
      *(float *)(param_1 + 0x44) = fVar3;
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    dVar5 = (double)FLOAT_8043907c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    zz_0066530_(param_1,0x2c);
    zz_00b2190_(param_1,2);
  }
  return;
}



// ==== 800f4730  FUN_800f4730 ====

void FUN_800f4730(int param_1)

{
  char cVar1;
  double dVar2;
  
  if (*(float *)(param_1 + 0x44) < FLOAT_804390dc) {
    dVar2 = (double)FLOAT_8043907c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar2,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  zz_00f47a4_(param_1);
  return;
}



// ==== 800f47a4  zz_00f47a4_ ====

void zz_00f47a4_(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80439080) * FLOAT_804390a0);
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_804390b0,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(float *)(param_1 + 0x44) < FLOAT_804390e8) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800f4850  zz_00f4850_ ====

void zz_00f4850_(undefined4 param_1,int param_2)

{
  *(undefined2 *)(param_2 + 0x14) = 0;
  *(undefined2 *)(param_2 + 0x12) = 0;
  *(undefined2 *)(param_2 + 0xc) = 0;
  *(undefined2 *)(param_2 + 10) = 0;
  *(undefined1 *)(param_2 + 0x17) = 0;
  *(undefined1 *)(param_2 + 0x16) = 0;
  return;
}



// ==== 800f4870  zz_00f4870_ ====

void zz_00f4870_(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  short sVar3;
  char cVar4;
  
  cVar4 = *(char *)(param_2 + 0x16);
  if (cVar4 == *(char *)(param_2 + 0x17)) {
    sVar1 = *(short *)(param_2 + 0x12);
    sVar3 = *(short *)(param_2 + 10) - *(short *)(param_2 + 0xe);
    if ((int)sVar1 < (int)sVar3) {
      sVar3 = sVar1;
    }
    iVar2 = -(int)sVar1;
    if (sVar3 < iVar2) {
      sVar3 = (short)iVar2;
    }
    *(short *)(param_2 + 0xe) = *(short *)(param_2 + 0xe) + sVar3;
    sVar1 = *(short *)(param_2 + 0x14);
    sVar3 = *(short *)(param_2 + 0xc) - *(short *)(param_2 + 0x10);
    if ((int)sVar1 < (int)sVar3) {
      sVar3 = sVar1;
    }
    iVar2 = -(int)sVar1;
    if (sVar3 < iVar2) {
      sVar3 = (short)iVar2;
    }
    *(short *)(param_2 + 0x10) = *(short *)(param_2 + 0x10) + sVar3;
  }
  else {
    if (cVar4 == '\x01') {
      cVar4 = '\0';
      *(undefined2 *)(param_2 + 0xe) = uRam8031caf8;
      *(undefined2 *)(param_2 + 0x10) = uRam8031cafa;
      *(undefined1 *)(param_2 + 0x16) = 0;
    }
    iVar2 = (int)cVar4;
    *(undefined2 *)(param_2 + 10) = (&DAT_8031caf0)[iVar2 * 4];
    *(undefined2 *)(param_2 + 0xc) = (&DAT_8031caf2)[iVar2 * 4];
    *(undefined2 *)(param_2 + 0x12) = (&DAT_8031caf4)[iVar2 * 4];
    *(undefined2 *)(param_2 + 0x14) = (&DAT_8031caf6)[iVar2 * 4];
  }
  *(undefined1 *)(param_2 + 0x17) = *(undefined1 *)(param_2 + 0x16);
  *(short *)(param_1 + 0x191c) = -*(short *)(param_2 + 0xe);
  *(short *)(param_1 + 0x197c) = *(short *)(param_2 + 0xe) - *(short *)(param_2 + 0x10);
  return;
}



// ==== 800f4a9c  FUN_800f4a9c ====

void FUN_800f4a9c(int param_1)

{
  short sVar1;
  
  *(undefined1 *)(param_1 + 0x6e8) = 0x80;
  *(byte *)(param_1 + 0x6e9) = *(byte *)(param_1 + 0x6e9) | 0x80;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0xa08) {
    zz_00e3408_(param_1,1);
  }
  else if (sVar1 < 0xa08) {
    if (sVar1 == 0xa04) {
      zz_00e3408_(param_1,0);
    }
  }
  else if (sVar1 < 0xa0a) {
    zz_00e3408_(param_1,2);
  }
  *(undefined1 *)(param_1 + 0x15c) = 0;
  zz_00f4850_(param_1,param_1 + 0x144);
  return;
}



// ==== 800f4b38  FUN_800f4b38 ====

void FUN_800f4b38(int param_1)

{
  zz_01485e8_(param_1,(float *)(param_1 + 0x144));
  zz_00f4870_(param_1,param_1 + 0x144);
  if (*(char *)(param_1 + 0x15c) == '\0') {
    *(undefined1 *)(param_1 + 0x748) = 0;
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xfd;
  }
  else {
    *(undefined1 *)(param_1 + 0x748) = 1;
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 2;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_804390f8) * FLOAT_804390f0);
  }
  return;
}



// ==== 800f4c00  FUN_800f4c00 ====

void FUN_800f4c00(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8031cb40)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800f4c40  FUN_800f4c40 ====

void FUN_800f4c40(int param_1)

{
  short sVar1;
  
  if (*(char *)(param_1 + 0x15c) == '\0') {
    zz_0046698_(param_1);
    *(undefined1 *)(param_1 + 0x15c) = 2;
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0xa04) {
      zz_0127600_(param_1,0);
    }
    else if (sVar1 == 0xa08) {
      zz_0127600_(param_1,1);
    }
    else if (sVar1 == 0xa09) {
      zz_0127600_(param_1,2);
    }
  }
  return;
}



// ==== 800f4cc8  FUN_800f4cc8 ====

void FUN_800f4cc8(int param_1)

{
  undefined1 uVar1;
  
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0xa08) {
    uVar1 = 0x4a;
  }
  else if (*(short *)(param_1 + 1000) == 0xa09) {
    uVar1 = 0x4b;
  }
  else {
    uVar1 = 0x17;
  }
  zz_001ab6c_(param_1,uVar1);
  return;
}



// ==== 800f4d24  FUN_800f4d24 ====

void FUN_800f4d24(int param_1)

{
  *(undefined1 *)(param_1 + 0x15a) = 1;
  if (*(short *)(param_1 + 1000) == 0xa04) {
    zz_00ffba8_(param_1,1);
  }
  else if (*(short *)(param_1 + 1000) == 0xa09) {
    zz_00ffba8_(param_1,4);
  }
  return;
}



// ==== 800f4d70  FUN_800f4d70 ====

void FUN_800f4d70(int param_1)

{
  (*(code *)(&PTR_FUN_8031cb54)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800f4dac  FUN_800f4dac ====

void FUN_800f4dac(int param_1)

{
  (*(code *)(&PTR_FUN_8031cb64)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800f4de8  FUN_800f4de8 ====

void FUN_800f4de8(int param_1)

{
  zz_00f51a8_(param_1);
  (*(code *)(&PTR_FUN_80434458)[*(char *)(param_1 + 0x545)])(param_1);
  (*(code *)(&PTR_FUN_80434448)[*(char *)(param_1 + 0x544)])(param_1);
  (*(code *)(&PTR_FUN_80434450)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 800f4e74  FUN_800f4e74 ====

void FUN_800f4e74(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80439108;
  *(char *)(param_1 + 0x545) = *(char *)(param_1 + 0x545) + '\x01';
  zz_004beb8_(dVar1,param_1,4,2,0x1a,8,2);
  return;
}



// ==== 800f4eb8  FUN_800f4eb8 ====

void FUN_800f4eb8(int param_1)

{
  zz_004cd24_(param_1,4);
  return;
}



// ==== 800f4edc  FUN_800f4edc ====

void FUN_800f4edc(int param_1)

{
  if ((*(float *)(param_1 + 0x560) < FLOAT_80439104) || (*(short *)(param_1 + 0x54a) != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00f525c_(param_1);
  }
  return;
}



// ==== 800f4f24  FUN_800f4f24 ====

void FUN_800f4f24(int param_1)

{
  int iVar1;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  if ((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) {
    if (FLOAT_80439104 < *(float *)(param_1 + 0x558)) {
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      return;
    }
    if ('\0' < *(char *)(param_1 + 0x6ec)) {
      zz_006bf80_(param_1);
      zz_00f525c_(param_1);
      return;
    }
    if ((*(char *)(param_1 + 0x745) != '\0') && (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) {
      zz_006bf80_(param_1);
      zz_00f5240_(param_1);
      zz_00f525c_(param_1);
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
    zz_006a4f4_(param_1);
  }
  else {
    zz_006a474_(param_1);
  }
  *(float *)(param_1 + 0x694) = FLOAT_8043910c + *(float *)(param_1 + 0x1dc8);
  return;
}



// ==== 800f5038  FUN_800f5038 ====

void FUN_800f5038(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439110;
  *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0xff;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = 0;
  zz_00f5240_(param_1);
  zz_004beb8_((double)FLOAT_80439108,param_1,3,2,(int)*(char *)(param_1 + 0x6eb),0xc,2);
  zz_00f50b4_(param_1);
  return;
}



// ==== 800f50b4  zz_00f50b4_ ====

void zz_00f50b4_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  
  cVar1 = *(char *)(param_1 + 0x6eb);
  iVar3 = (int)cVar1;
  if (iVar3 == 0) {
    zz_006ed8c_((double)FLOAT_80439114,param_1);
  }
  else {
    fVar2 = *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    if (*(float *)(param_1 + 0x44) < fVar2) {
      *(float *)(param_1 + 0x44) = fVar2;
    }
    *(float *)(param_1 + 0x4c) = FLOAT_80439104;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
  }
  if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
    *(float *)(param_1 + 0x48) = FLOAT_80439108;
  }
  else {
    *(float *)(param_1 + 0x48) = FLOAT_80439104;
  }
  FUN_80067310((double)FLOAT_80439118,param_1,*(short *)(param_1 + 0x5ae));
  zz_0067a28_(param_1);
  if (*(char *)(param_1 + 0x6ea) == iVar3) {
    zz_004cd24_(param_1,3);
  }
  else {
    if (-1 < *(char *)(param_1 + 0x6ea)) {
      zz_004beb8_((double)FLOAT_80439108,param_1,3,2,iVar3,0xc,2);
    }
    *(char *)(param_1 + 0x6ea) = cVar1;
  }
  return;
}



// ==== 800f51a8  zz_00f51a8_ ====

void zz_00f51a8_(int param_1)

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



// ==== 800f5240  zz_00f5240_ ====

void zz_00f5240_(int param_1)

{
  float fVar1;
  
  *(undefined1 *)(param_1 + 0x745) = 0;
  fVar1 = FLOAT_80439100;
  *(undefined1 *)(param_1 + 0x6ec) = 3;
  *(float *)(param_1 + 0x558) = fVar1;
  return;
}



// ==== 800f525c  zz_00f525c_ ====

void zz_00f525c_(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043911c;
  *(char *)(param_1 + 0x6ec) = *(char *)(param_1 + 0x6ec) + -1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x587) = 0;
  iVar3 = zz_006dbe0_(param_1,0,1,1);
  if (iVar3 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0xa04) {
      zz_00ffba8_(param_1,0);
    }
    else if (sVar1 == 0xa08) {
      zz_00ffba8_(param_1,2);
    }
    else if (sVar1 == 0xa09) {
      zz_00ffba8_(param_1,3);
    }
    *(undefined1 *)(param_1 + 0x15a) = 1;
  }
  return;
}



// ==== 800f530c  FUN_800f530c ====

void FUN_800f530c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8031cb78)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800f5354  FUN_800f5354 ====

void FUN_800f5354(int param_1)

{
  zz_0147e34_(param_1);
  return;
}



// ==== 800f5378  FUN_800f5378 ====

void FUN_800f5378(int param_1)

{
  zz_0147e34_(param_1);
  return;
}



// ==== 800f539c  FUN_800f539c ====

void FUN_800f539c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031cb8c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800f53ec  FUN_800f53ec ====

void FUN_800f53ec(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_80439120;
  fVar1 = FLOAT_80439100;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x55c) = fVar2;
  *(undefined2 *)(param_1 + 0x54c) = 0x20;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804390f0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80439108,param_1,0xf,3,4,8,1);
  return;
}



// ==== 800f54f8  FUN_800f54f8 ====

void FUN_800f54f8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804390f0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439104;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80439110;
    fVar1 = FLOAT_80439104;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 800f55d4  FUN_800f55d4 ====

void FUN_800f55d4(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439124 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_80439118;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439124 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439104;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_80439128,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800f56b0  FUN_800f56b0 ====

void FUN_800f56b0(int param_1)

{
  double dVar1;
  float fVar2;
  float fVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_804390f0,param_1);
  if (*(float *)(param_1 + 0x760) < FLOAT_80439128) {
    zz_006ed8c_((double)FLOAT_8043912c,param_1);
  }
  FUN_80067310((double)FLOAT_80439118,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439138;
  dVar1 = DOUBLE_80439130;
  if (*(char *)(param_1 + 0x1cf0) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_8043913c;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar1);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar1);
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar3;
  }
  return;
}



// ==== 800f5778  FUN_800f5778 ====

/* WARNING: Removing unreachable block (ram,0x800f58d4) */
/* WARNING: Removing unreachable block (ram,0x800f5788) */

void FUN_800f5778(int param_1)

{
  float fVar1;
  uint uVar2;
  double dVar3;
  double dVar4;
  
  uVar2 = zz_006de44_(param_1,0xf0f00);
  dVar3 = DOUBLE_804390f8;
  if (uVar2 != 0) {
    if ((int)*(short *)(param_1 + 0x54c) < (int)uVar2) {
      uVar2 = (int)*(short *)(param_1 + 0x54c);
    }
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) - (short)uVar2;
    *(float *)(param_1 + 0x55c) =
         *(float *)(param_1 + 0x55c) +
         (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - dVar3);
  }
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_006d144_(param_1,0xc0);
    FUN_80067310((double)FLOAT_80439118,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    fVar1 = FLOAT_80439104;
    if (*(char *)(param_1 + 0x1cf0) < '\x01') {
      zz_004cd24_(param_1,0xf);
    }
    else {
      dVar3 = (double)FLOAT_80439104;
      dVar4 = (double)*(float *)(param_1 + 0x1dc8);
      if (dVar3 < (double)*(float *)(param_1 + 0x55c)) {
        *(float *)(param_1 + 0x55c) = (float)((double)*(float *)(param_1 + 0x55c) - dVar4);
        if ((double)*(float *)(param_1 + 0x48) < dVar3) {
          *(float *)(param_1 + 0x48) = fVar1;
        }
        dVar3 = DOUBLE_80439130;
        *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + FLOAT_80439118;
        *(float *)(param_1 + 0x1dc8) = (float)((double)*(float *)(param_1 + 0x1dc8) * dVar3);
      }
      zz_004cd24_(param_1,0xf);
      *(float *)(param_1 + 0x1dc8) = (float)dVar4;
    }
    fVar1 = FLOAT_80439140;
    if ((*(char *)(param_1 + 0x1cef) < '\0') || (*(float *)(param_1 + 0x48) < FLOAT_80439104)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x50) = fVar1 * *(float *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
  }
  return;
}



// ==== 800f58f0  FUN_800f58f0 ====

void FUN_800f58f0(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439118,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 != 0) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439118 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800f5970  FUN_800f5970 ====

void FUN_800f5970(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0xa08) {
    zz_0148384_(param_1);
  }
  else {
    zz_0148384_(param_1);
  }
  return;
}



// ==== 800f59ac  zz_00f59ac_ ====

void zz_00f59ac_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0xa01) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800f5aa0;
    *(code **)(puVar1 + 0x10c) = FUN_800f5c2c;
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



// ==== 800f5aa0  FUN_800f5aa0 ====

void FUN_800f5aa0(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8031cbb4)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800f5af4  FUN_800f5af4 ====

void FUN_800f5af4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  fVar1 = FLOAT_80439148;
  *(float *)(param_9 + 0xb4) = FLOAT_80439148;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(undefined1 *)(param_9 + 0x89) = 7;
  *(undefined4 *)(param_9 + 100) = DAT_8031cba8;
  *(undefined4 *)(param_9 + 0x68) = DAT_8031cbac;
  *(undefined4 *)(param_9 + 0x6c) = DAT_8031cbb0;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),7,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  uVar2 = 7;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),7,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043914c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00f5bf8_();
  return;
}



// ==== 800f5bf8  zz_00f5bf8_ ====

void zz_00f5bf8_(void)

{
  return;
}



// ==== 800f5c0c  FUN_800f5c0c ====

void FUN_800f5c0c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f5c2c  FUN_800f5c2c ====

void FUN_800f5c2c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  
  puVar1 = (undefined *)0x0;
  uVar2 = 1;
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) != '\0') ||
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04')) {
    puVar1 = (undefined *)0x1;
    uVar2 = 0x44;
  }
  iVar3 = *(int *)(param_9 + (int)puVar1 * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
              (float *)(param_9 + 0x114),puVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar3,uVar2);
  return;
}



// ==== 800f5ca8  zz_00f5ca8_ ====

void zz_00f5ca8_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  if ((*(short *)(param_1 + 1000) == 0x701) || (*(short *)(param_1 + 1000) == 0x708)) {
    iVar2 = 0;
    do {
      puVar1 = zz_0088aa0_(param_1,2,0,0,2);
      if (puVar1 != (undefined1 *)0x0) {
        *puVar1 = 1;
        puVar1[0x11] = param_2;
        puVar1[0x83] = 0x18;
        *(code **)(puVar1 + 0xc) = FUN_800f5dd4;
        *(code **)(puVar1 + 0x10c) = FUN_800f6028;
        puVar1[0x13] = (char)iVar2;
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
      iVar2 = iVar2 + 1;
    } while (iVar2 < 2);
  }
  return;
}



