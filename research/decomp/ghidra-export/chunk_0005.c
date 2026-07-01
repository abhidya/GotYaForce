// ==== 80042690  zz_0042690_ ====

void zz_0042690_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar2;
  
  *(undefined4 *)(PTR_DAT_80433954 + 0x18) = 0;
  *(undefined4 *)(PTR_DAT_80433954 + 0x1c) = 0;
  iVar1 = (int)(char)PTR_DAT_80433934[0x1e];
  if ((iVar1 != 0x10) &&
     ((&PTR_DAT_802d07a0)[(char)PTR_DAT_80433934[0x1c] * 3 + (int)(char)PTR_DAT_80433934[0x1d]] !=
      (undefined *)0x0)) {
    iVar2 = DAT_80436238 + 0x655400;
    iVar1 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)((&PTR_DAT_802d07a0)
                                 [(char)PTR_DAT_80433934[0x1c] * 3 +
                                  (int)(char)PTR_DAT_80433934[0x1d]] + iVar1 * 4),iVar2,iVar1,
                        PTR_DAT_80433934,in_r7,in_r8,in_r9,in_r10);
    *(int *)(PTR_DAT_80433954 + 0x1c) = iVar1;
    zz_000b1a0_(iVar2,0xbb4800,*(int *)(PTR_DAT_80433954 + 0x1c));
  }
  return;
}



// ==== 80042748  zz_0042748_ ====

void zz_0042748_(void)

{
  uint uVar1;
  
  if (*(int *)(PTR_DAT_80433954 + 0x1c) != 0) {
    uVar1 = DAT_80436238 + 0x77fc00;
    *(uint *)(PTR_DAT_80433954 + 0x18) = uVar1;
    zz_00f19f8_(uVar1,0xbb4800,*(int *)(PTR_DAT_80433954 + 0x1c),1);
  }
  return;
}



// ==== 8004279c  zz_004279c_ ====

void zz_004279c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  
  piVar4 = *(int **)(PTR_DAT_80433954 + 0x18);
  if (piVar4 != (int *)0x0) {
    iVar7 = *piVar4;
    piVar8 = piVar4 + 2;
    *(int **)(PTR_DAT_80433954 + 0x18) = piVar4 + 0x200;
    iVar6 = 0;
    piVar5 = piVar4 + 0x200 + piVar4[1] * 0x200;
    do {
      uVar3 = 8;
      gnt4_memset(&DAT_803bb32c + (iVar6 + 0xc) * 2,0,8);
      iVar6 = iVar6 + 1;
    } while (iVar6 < 8);
    for (iVar6 = 0; iVar6 < iVar7 + -1; iVar6 = iVar6 + 1) {
      iVar1 = (iVar6 + 0xc) * 8;
      piVar2 = zz_0197a0c_(1);
      (&DAT_803bb32c)[(iVar6 + 0xc) * 2] = piVar2;
      *(int **)(&DAT_803bb330 + iVar1) = piVar5;
      param_1 = zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (&DAT_803bb32c)[(iVar6 + 0xc) * 2],*(uint **)(&DAT_803bb330 + iVar1),
                            uVar3,piVar4,in_r7,in_r8,in_r9,in_r10);
      iVar1 = *piVar8;
      piVar8 = piVar8 + 1;
      piVar5 = piVar5 + iVar1 * 0x200;
    }
  }
  return;
}



// ==== 80042874  zz_0042874_ ====

void zz_0042874_(void)

{
  return;
}



// ==== 80042878  zz_0042878_ ====

void zz_0042878_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  
  DAT_803b0768 = -0x10000000;
  DAT_803b0760 = DAT_80436238 + 0x7a3c00;
  iVar3 = DAT_80436238 + 0x7ac400;
  DAT_803b0764 = -0x10000000;
  iVar1 = iVar3;
  if (PTR_DAT_80433930[0x29] == '\0') {
    DAT_803b0764 = iVar3;
    iVar1 = DAT_803b0768;
  }
  DAT_803b0768 = iVar1;
  uVar2 = 8;
  gnt4_memset(&DAT_803bb374,0,8);
  DAT_803bb378 = iVar3;
  zz_000b07c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x2b9,&DAT_803b0760,
              uVar2,in_r6,in_r7,in_r8,in_r9,in_r10);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_008bed8_,4,
              DAT_803b0760,&DAT_803c0634,&DAT_803c0614,&DAT_803c0608,&DAT_803b0760,in_r10);
  return;
}



// ==== 80042954  zz_0042954_ ====

void zz_0042954_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  DAT_803bb374 = zz_0197a0c_(1);
  zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803bb374,
              DAT_803bb378,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80042994  zz_0042994_ ====

void zz_0042994_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_80436238 + 0xfe800;
  iVar1 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_802d0608,
                      iVar2,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_000b1a0_(iVar2,0x90d000,iVar1);
  return;
}



// ==== 800429ec  zz_00429ec_ ====

void zz_00429ec_(void)

{
  DAT_803b078c = DAT_80436238 + 0x81c400;
  DAT_803b0790 = DAT_80436238 + 0x70fc00;
  DAT_803b0794 = 0;
  DAT_803b0798 = 0;
  zz_00188d4_(0x90d000,&DAT_803b078c);
  zz_0042324_(&DAT_803b078c);
  return;
}



// ==== 80042a58  zz_0042a58_ ====

void zz_0042a58_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  iVar5 = DAT_80436238 + 0x8cc400;
  do {
    iVar1 = iVar4 + 0xc;
    uVar3 = 8;
    gnt4_memset(&DAT_803bb32c + iVar1 * 2,0,8);
    iVar2 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        iVar4 + 0xa86,iVar5,uVar3,in_r6,in_r7,in_r8,in_r9,in_r10);
    iVar4 = iVar4 + 1;
    *(int *)(&DAT_803bb330 + iVar1 * 8) = iVar5;
    iVar5 = iVar5 + iVar2;
  } while (iVar4 < 10);
  uVar3 = 8;
  gnt4_memset(&DAT_803bb3f4,0,8);
  iVar4 = DAT_80436238 + 0x8d1400;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xaa6,iVar4,uVar3,
              in_r6,in_r7,in_r8,in_r9,in_r10);
  DAT_803bb3f8 = iVar4;
  return;
}



// ==== 80042b20  zz_0042b20_ ====

void zz_0042b20_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  int iVar1;
  
  iVar1 = 0;
  do {
    param_1 = zz_0040edc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803bb32c + (iVar1 + 0xc) * 2,param_10,param_11,param_12,param_13,
                          param_14,param_15,param_16);
    iVar1 = iVar1 + 1;
    param_10 = extraout_r4;
  } while (iVar1 < 10);
  zz_0040edc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803bb3f4,
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80042b94  zz_0042b94_ ====

undefined4
zz_0042b94_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9)

{
  undefined4 uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r9;
  int iVar5;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  
  if (PTR_DAT_80433930[0x32] == '\0') {
    if ((char)PTR_DAT_80433934[0x45] < '\x05') {
      if (PTR_DAT_80433934[(char)PTR_DAT_80433934[param_9 + 0xcb] * 0x3c + 0xf6] == '\0') {
        uVar1 = 0;
      }
      else {
        iVar7 = (int)(char)PTR_DAT_80433934[param_9 + 0x20];
        if (iVar7 < 0) {
          uVar1 = 0;
        }
        else if (iVar7 < 0xe) {
          if (*(short *)(PTR_DAT_80433934 + param_9 * 2 + 0x10) < 0) {
            uVar1 = 0;
          }
          else {
            PTR_DAT_80433934[param_9 + 0x38] = 0xff;
            iVar5 = DAT_80436238;
            iVar6 = param_9 * 0x1c800 + DAT_80436238;
            (&DAT_803c02c0)[param_9 * 6] = 0;
            iVar6 = iVar6 + 0xb85c00;
            puVar2 = (&PTR_DAT_802d0958)[iVar7];
            (&DAT_803c02c4)[param_9 * 6] = 0;
            zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)*(short *)(puVar2 + 0xe),iVar6,iVar5,&DAT_803c02c0,0,param_9 * 0x18,
                        in_r9,in_r10);
            iVar5 = param_9 * 0x20;
            iVar3 = iVar5 + -0x7fc3fe00;
            iVar4 = param_9 * 0xc + -0x7fc3fe60;
            uVar8 = zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                zz_008bed8_,4,iVar6,&DAT_803c02c0 + param_9 * 6,iVar3,iVar4,iVar5,
                                in_r10);
            zz_000a154_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&LAB_80042b84,
                        2,param_9,iVar7,iVar3,iVar4,iVar5,in_r10);
            uVar1 = 1;
          }
        }
        else {
          uVar1 = 0;
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



// ==== 80042d28  zz_0042d28_ ====

void zz_0042d28_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  
  PTR_DAT_80433934[0x38] = 0xff;
  DAT_803c02c0 = 0;
  DAT_803c02c4 = 0;
  PTR_DAT_80433934[0x39] = 0xff;
  DAT_803c02d8 = 0;
  DAT_803c02dc = 0;
  PTR_DAT_80433934[0x3a] = 0xff;
  DAT_803c02f0 = 0;
  DAT_803c02f4 = 0;
  PTR_DAT_80433934[0x3b] = 0xff;
  DAT_803c0308 = 0;
  DAT_803c030c = 0;
  PTR_DAT_80433934[0x3c] = 0xff;
  DAT_803c0320 = 0;
  DAT_803c0324 = 0;
  PTR_DAT_80433934[0x3d] = 0xff;
  DAT_803c0338 = 0;
  DAT_803c033c = 0;
  if (PTR_DAT_80433930[0x32] == '\0') {
    pcVar5 = (char *)0x0;
    iVar4 = 0;
    iVar1 = (int)(char)PTR_DAT_80433934[0x53];
    puVar2 = PTR_DAT_80433934;
    if (0 < iVar1) {
      do {
        if (puVar2[0xf6] != '\0') {
          pcVar5 = PTR_DAT_80433934 + iVar4 * 0x3c + 0xf4;
          break;
        }
        puVar2 = puVar2 + 0x3c;
        iVar4 = iVar4 + 1;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    iVar1 = 0;
    iVar4 = 0;
    while ((iVar4 < 6 && (iVar1 < 6))) {
      if ((*pcVar5 == PTR_DAT_80433934[iVar4 + 0xcb]) &&
         (iVar3 = zz_0042b94_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4)
         , iVar3 != 0)) {
        iVar1 = iVar1 + 1;
      }
      iVar4 = iVar4 + 1;
    }
  }
  return;
}



// ==== 80042e78  FUN_80042e78 ====

void FUN_80042e78(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9)

{
  undefined *puVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  puVar1 = PTR_DAT_80433934 + param_9;
  puVar1[0x2c] = puVar1[0x20];
  zz_0040edc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              &DAT_803bb32c + (param_9 + 0x14) * 2,0x803c0000,(uint)(byte)puVar1[0x20],puVar1,in_r7,
              in_r8,in_r9,in_r10);
  return;
}



// ==== 80042ebc  zz_0042ebc_ ====

void zz_0042ebc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  
  if ((PTR_DAT_80433930[0x32] == '\0') && ((char)PTR_DAT_80433934[0x45] < '\x05')) {
    piVar2 = (int *)(&DAT_803bb32c)[(param_9 + 0x14) * 2];
    if (piVar2 != (int *)0x0) {
      param_1 = zz_0197ad8_(piVar2);
    }
    gnt4_memset(&DAT_803bb32c + (param_9 + 0x14) * 2,0,8);
    PTR_DAT_80433934[param_9 + 0x2c] = 0xff;
    cVar1 = PTR_DAT_80433934[param_9 + 0x20];
    if ((((cVar1 < 0xe) && (-1 < cVar1)) && (-1 < *(short *)(PTR_DAT_80433934 + param_9 * 2 + 0x10))
        ) && (-1 < *(short *)((&PTR_DAT_802d0958)[cVar1] + 4))) {
      iVar3 = param_9 * 0x5000 + DAT_80436238 + 0xc30c00;
      zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  (int)*(short *)((&PTR_DAT_802d0958)[cVar1] + 4),iVar3,DAT_80436238,param_12,
                  param_13,param_14,param_15,param_16);
      zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80042e78,1,
                  param_9,param_12,param_13,param_14,param_15,param_16);
      *(int *)(&DAT_803bb330 + (param_9 + 0x14) * 8) = iVar3;
    }
  }
  return;
}



// ==== 80042fe4  zz_0042fe4_ ====

void zz_0042fe4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  do {
    uVar2 = 8;
    gnt4_memset(&DAT_803bb32c + (iVar3 + 0x14) * 2,0,8);
    iVar1 = iVar3 + 0x2c;
    iVar3 = iVar3 + 1;
    PTR_DAT_80433934[iVar1] = 0xff;
  } while (iVar3 < 6);
  if (PTR_DAT_80433930[0x32] == '\0') {
    iVar5 = 0;
    iVar1 = 0;
    iVar3 = 0xc30c00;
    do {
      if (((-1 < *(short *)(PTR_DAT_80433934 + iVar1 + 0x10)) &&
          ((char)PTR_DAT_80433934[iVar5 + 0x20] < 0xe)) &&
         (-1 < *(short *)((&PTR_DAT_802d0958)[(char)PTR_DAT_80433934[iVar5 + 0x20]] + 4))) {
        iVar4 = DAT_80436238 + iVar3;
        zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    (int)*(short *)((&PTR_DAT_802d0958)[(char)PTR_DAT_80433934[iVar5 + 0x20]] + 4),
                    iVar4,uVar2,in_r6,in_r7,in_r8,in_r9,in_r10);
        *(int *)(&DAT_803bb330 + (iVar5 + 0x14) * 8) = iVar4;
      }
      iVar5 = iVar5 + 1;
      iVar3 = iVar3 + 0x5000;
      iVar1 = iVar1 + 2;
    } while (iVar5 < 6);
  }
  return;
}



// ==== 80043100  zz_0043100_ ====

void zz_0043100_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  undefined *puVar5;
  int in_r7;
  int in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  
  iVar6 = 0;
  do {
    gnt4_memset(&DAT_803bb32c + (iVar6 + 0x14) * 2,0,8);
    iVar6 = iVar6 + 1;
  } while (iVar6 < 6);
  if (PTR_DAT_80433930[0x32] == '\0') {
    pcVar8 = (char *)0x0;
    pcVar9 = (char *)0x0;
    iVar6 = (int)(char)PTR_DAT_80433934[0x53];
    puVar4 = PTR_DAT_80433934;
    if (0 < iVar6) {
      do {
        if (puVar4[0xf6] == '\0') {
          pcVar8 = puVar4 + 0xf4;
        }
        else {
          pcVar9 = puVar4 + 0xf4;
        }
        puVar4 = puVar4 + 0x3c;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    if (pcVar9 != (char *)0x0) {
      iVar6 = 0;
      in_r8 = -1;
      iVar12 = 2;
      puVar4 = PTR_DAT_80433934;
      puVar5 = PTR_DAT_80433934;
      do {
        if ((((puVar4[0xcb] == *pcVar9) && (-1 < *(short *)(puVar5 + 0x10))) &&
            ('\0' < (char)puVar4[0x20])) && ((char)puVar4[0x20] < '\x0e')) {
          in_r8 = (int)(char)PTR_DAT_80433934[iVar6 + 0x20];
          break;
        }
        if (((puVar4[0xcc] == *pcVar9) && (-1 < *(short *)(puVar5 + 0x12))) &&
           (('\0' < (char)puVar4[0x21] && ((char)puVar4[0x21] < '\x0e')))) {
          in_r8 = (int)(char)PTR_DAT_80433934[iVar6 + 0x21];
          break;
        }
        if (((puVar4[0xcd] == *pcVar9) && (-1 < *(short *)(puVar5 + 0x14))) &&
           (('\0' < (char)puVar4[0x22] && ((char)puVar4[0x22] < '\x0e')))) {
          in_r8 = (int)(char)PTR_DAT_80433934[iVar6 + 0x22];
          break;
        }
        puVar4 = puVar4 + 3;
        puVar5 = puVar5 + 6;
        iVar6 = iVar6 + 3;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
      if (in_r8 < 0) {
        in_r8 = 0;
      }
      iVar6 = DAT_80436238 + 0xb85c00;
      in_r7 = DAT_80436238;
      if (-1 < *(short *)((&PTR_DAT_802d0958)[in_r8] +
                         (((-(int)pcVar9[0xe] | (int)pcVar9[0xe]) >> 0x1f) + 4) * 2)) {
        zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    (int)*(short *)((&PTR_DAT_802d0958)[in_r8] +
                                   (((-(int)pcVar9[0xe] | (int)pcVar9[0xe]) >> 0x1f) + 4) * 2),iVar6
                    ,in_r8 * 4,0x803c0000,DAT_80436238,in_r8,in_r9,in_r10);
        DAT_803bb3d0 = iVar6;
      }
    }
    if (pcVar8 != (char *)0x0) {
      cVar1 = pcVar9[0xe];
      iVar12 = 0;
      iVar11 = 0;
      iVar10 = 0xbb5c00;
      iVar6 = 0;
      while ((iVar12 < 6 && (iVar6 < 2))) {
        if ((PTR_DAT_80433934[iVar12 + 0xcb] == *pcVar8) &&
           (((-1 < *(short *)(PTR_DAT_80433934 + iVar11 + 0x10) &&
             (iVar3 = (int)(char)PTR_DAT_80433934[iVar12 + 0x20], 0 < iVar3)) && (iVar3 < 0xe)))) {
          iVar2 = (iVar6 + 0x15) * 8;
          iVar7 = DAT_80436238 + iVar10;
          if (-1 < *(short *)((&PTR_DAT_802d0958)[iVar3] +
                             ((-(int)cVar1 | (int)cVar1) >> 0x1f & 5U) * 2)) {
            zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)*(short *)((&PTR_DAT_802d0958)[iVar3] +
                                       ((-(int)cVar1 | (int)cVar1) >> 0x1f & 5U) * 2),iVar7,iVar2,
                        DAT_80436238,in_r7,in_r8,in_r9,in_r10);
            *(int *)(&DAT_803bb330 + iVar2) = iVar7;
          }
          iVar10 = iVar10 + 0x10000;
          iVar6 = iVar6 + 1;
        }
        iVar11 = iVar11 + 2;
        iVar12 = iVar12 + 1;
      }
    }
  }
  return;
}



// ==== 80043414  zz_0043414_ ====

void zz_0043414_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    iVar1 = (iVar3 + 0x14) * 8;
    if (*(int *)(&DAT_803bb330 + iVar1) != 0) {
      piVar2 = zz_0197a0c_(1);
      (&DAT_803bb32c)[(iVar3 + 0x14) * 2] = piVar2;
      param_1 = zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (&DAT_803bb32c)[(iVar3 + 0x14) * 2],*(uint **)(&DAT_803bb330 + iVar1),
                            param_11,param_12,param_13,param_14,param_15,param_16);
      PTR_DAT_80433934[iVar3 + 0x2c] = PTR_DAT_80433934[iVar3 + 0x20];
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 6);
  return;
}



// ==== 800434a0  zz_00434a0_ ====

void zz_00434a0_(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_803bb32c;
  iVar1 = 0;
  do {
    if ((int *)puVar2[0x28] != (int *)0x0) {
      zz_0197ad8_((int *)puVar2[0x28]);
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 2;
  } while (iVar1 < 6);
  return;
}



// ==== 800434f8  zz_00434f8_ ====

void zz_00434f8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined *param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  short *psVar10;
  
  iVar8 = DAT_80436238 + 0xb6800;
  iVar7 = DAT_80436238 + 0xfe800;
  if (param_9 == 0) {
    iVar6 = 3;
    iVar2 = 0;
  }
  else {
    iVar6 = 1;
    iVar2 = 3;
  }
  psVar10 = &DAT_802d0bec + iVar2 * 3;
  iVar9 = 0;
  for (iVar2 = 0; iVar2 < iVar6; iVar2 = iVar2 + 1) {
    iVar3 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)*psVar10,iVar8,param_11,param_12,param_13,param_14,param_15,param_16);
    *(int *)(PTR_DAT_80433954 + iVar9 + 0x4c) = iVar8;
    iVar8 = iVar8 + iVar3;
    iVar3 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)psVar10[1],iVar8,param_11,param_12,param_13,param_14,param_15,param_16)
    ;
    puVar1 = PTR_DAT_80433954;
    *(int *)(PTR_DAT_80433954 + iVar9 + 0x58) = iVar8;
    iVar8 = iVar8 + iVar3;
    iVar4 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)psVar10[2],iVar7,puVar1,param_12,param_13,param_14,param_15,param_16);
    param_11 = PTR_DAT_80433954;
    iVar5 = iVar9 + 100;
    iVar3 = iVar9 + 0x70;
    iVar9 = iVar9 + 4;
    *(int *)(PTR_DAT_80433954 + iVar5) = iVar7;
    iVar7 = iVar7 + iVar4;
    psVar10 = psVar10 + 3;
    *(int *)(PTR_DAT_80433954 + iVar3) = iVar4;
  }
  return;
}



// ==== 800435dc  zz_00435dc_ ====

void zz_00435dc_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 1;
  iVar2 = 0;
  if (param_1 == 0) {
    iVar5 = 3;
  }
  iVar4 = 0;
  for (iVar3 = 0; iVar3 < iVar5; iVar3 = iVar3 + 1) {
    zz_00f0e5c_(iVar3,*(int *)(PTR_DAT_80433954 + iVar4 + 0x4c));
    zz_00ef9d4_(iVar3,*(int *)(PTR_DAT_80433954 + iVar4 + 0x58),iVar2);
    zz_00f192c_(*(uint *)(PTR_DAT_80433954 + iVar4 + 100),iVar2,
                *(int *)(PTR_DAT_80433954 + iVar4 + 0x70));
    iVar1 = iVar4 + 0x70;
    iVar4 = iVar4 + 4;
    iVar2 = iVar2 + *(int *)(PTR_DAT_80433954 + iVar1);
  }
  return;
}



// ==== 8004369c  zz_004369c_ ====

void zz_004369c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = countLeadingZeros(param_9);
  iVar2 = DAT_80436238 + 0x208400;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              0x9c3 - (uVar1 >> 5 & 1),iVar2,param_11,param_12,param_13,param_14,param_15,param_16);
  gnt4_memset(&DAT_803bb384,0,8);
  DAT_803bb388 = iVar2;
  return;
}



// ==== 8004370c  zz_004370c_ ====

void zz_004370c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  if (DAT_803bb388 != (uint *)0x0) {
    DAT_803bb384 = zz_0197a0c_(1);
    zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803bb384,
                DAT_803bb388,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80043758  zz_0043758_ ====

void zz_0043758_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_80436238 + 0xfe800;
  iVar1 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xb28,iVar2,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  *(int *)(PTR_DAT_80433954 + 0x90) = iVar1;
  zz_000b1a0_(iVar2,0xa0d000,iVar1);
  return;
}



// ==== 800437b0  zz_00437b0_ ====

void zz_00437b0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  
  iVar1 = *(int *)(PTR_DAT_80433954 + 0x90);
  uVar3 = DAT_80436238 + *(int *)(&DAT_802d0c04 + param_9 * 4);
  uVar2 = 1;
  zz_00f19f8_(uVar3,0xa0d000,iVar1,1);
  uVar5 = zz_0096bc4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar3,
                      uVar3 + *(int *)(PTR_DAT_80433954 + 0x90));
  iVar4 = *(int *)(PTR_DAT_80433954 + 0x90) + uVar3 + 0x4000;
  if (param_9 == 0) {
    zz_000af84_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x12,iVar4,iVar1,uVar2
                ,in_r7,in_r8,in_r9,in_r10);
    gnt4_memset(&DAT_803c0170,0,0x18);
    zz_000a154_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_008bed8_,4,iVar4,
                &DAT_803c0170,&DAT_803c0150,&DAT_803c0144,in_r9,in_r10);
  }
  return;
}



// ==== 80043890  zz_0043890_ ====

void zz_0043890_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = DAT_80436238 + 0xc6800;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xaaa,iVar1,param_11,
              param_12,param_13,param_14,param_15,param_16);
  iRam804361f8 = iVar1;
  DAT_804361f4 = 0;
  return;
}



// ==== 800438dc  zz_00438dc_ ====

void zz_00438dc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 uVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 extraout_f1;
  
  uVar1 = 0x20;
  DAT_804361f4 = &DAT_803bb440;
  gnt4_memset(&DAT_803bb440,0,0x20);
  DAT_803bb449 = 1;
  DAT_803bb44c = zz_002a860_(0x44);
  if (DAT_803bb44c != 0) {
    zz_0040eb4_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)DAT_804361f4,puRam804361f8,uVar1,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  return;
}



// ==== 8004394c  zz_004394c_ ====

void zz_004394c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_80436238 + 0xfe800;
  iVar1 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x9c1,iVar2,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  *(int *)(PTR_DAT_80433954 + 0x28) = iVar1;
  zz_000b1a0_(iVar2,0x700000,iVar1);
  return;
}



// ==== 800439a0  zz_00439a0_ ====

void zz_00439a0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar5;
  int iVar6;
  
  iVar6 = *(int *)(&DAT_802d0a00 + param_9 * 8);
  uVar3 = 1;
  iVar2 = *(int *)(PTR_DAT_80433954 + 0x28);
  uVar5 = DAT_80436238 + *(int *)(&DAT_802d0a04 + param_9 * 8);
  iVar4 = DAT_80436238;
  zz_00f19f8_(uVar5,0x700000,iVar2,1);
  iVar1 = iVar6 * 8;
  *(uint *)(&DAT_803bb330 + iVar1) = uVar5;
  (&DAT_803bb32c)[iVar6 * 2] = 0;
  zz_0040edc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              &DAT_803bb32c + iVar6 * 2,iVar1,iVar2,uVar3,iVar4,in_r8,in_r9,in_r10);
  return;
}



// ==== 80043a24  zz_0043a24_ ====

void zz_0043a24_(int param_1)

{
  zz_0197ad8_((int *)(&DAT_803bb32c)[*(int *)(&DAT_802d0a00 + param_1 * 8) * 2]);
  return;
}



// ==== 80043a64  zz_0043a64_ ====

void zz_0043a64_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = DAT_80436238 + 0xce000;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x16,iVar1,param_11,
              param_12,param_13,param_14,param_15,param_16);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_008bed8_,4,iVar1,
              &DAT_803c012c,&DAT_803c010c,&DAT_803c0100,param_15,param_16);
  return;
}



// ==== 80043ad0  zz_0043ad0_ ====

void zz_0043ad0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 8;
  gnt4_memset(&DAT_803bb384,0,8);
  iVar2 = DAT_80436238 + 0x208c00;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9 + 0x9c7,iVar2,
              uVar1,param_12,param_13,param_14,param_15,param_16);
  DAT_803bb388 = iVar2;
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80043b4c,0,uVar1,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80043b4c  FUN_80043b4c ====

void FUN_80043b4c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  DAT_803bb384 = zz_0197a0c_(1);
  uVar1 = zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)DAT_803bb384,DAT_803bb388,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  zz_0008a94_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803bb384,
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80043b94  zz_0043b94_ ====

void zz_0043b94_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = (int *)(&DAT_803bb32c)[(param_9 + 0xd) * 2];
  if (piVar1 != (int *)0x0) {
    param_1 = zz_0197ad8_(piVar1);
  }
  uVar3 = 8;
  gnt4_memset(&DAT_803bb32c + (param_9 + 0xd) * 2,0,8);
  iVar2 = param_9 * 0x40000 + DAT_80436238 + 0x42bc00;
  *(int *)(&DAT_803bb330 + (param_9 + 0xd) * 8) = iVar2;
  zz_000b000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10 + 0x9d8,iVar2
              ,uVar3,param_12,param_13,param_14,param_15,param_16);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80043c3c,1,param_9
              ,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80043c3c  FUN_80043c3c ====

void FUN_80043c3c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = (param_9 + 0xd) * 8;
  iVar3 = iVar1;
  piVar2 = zz_0197a0c_(1);
  (&DAT_803bb32c)[(param_9 + 0xd) * 2] = piVar2;
  zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (&DAT_803bb32c)[(param_9 + 0xd) * 2],*(uint **)(&DAT_803bb330 + iVar1),iVar3,param_12,
              param_13,param_14,param_15,param_16);
  return;
}



// ==== 80043c8c  zz_0043c8c_ ====

void zz_0043c8c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if (DAT_803bb38c != 0) {
    param_1 = zz_0043d54_();
  }
  uVar1 = 8;
  gnt4_memset(&DAT_803bb38c,0,8);
  DAT_803bb390 = DAT_80436238 + 0x738c00;
  zz_000b000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9 + 0x9cc,
              DAT_803bb390,uVar1,param_12,param_13,param_14,param_15,param_16);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80043d14,0,uVar1,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80043d14  FUN_80043d14 ====

void FUN_80043d14(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  DAT_803bb38c = zz_0197a0c_(1);
  zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803bb38c,
              DAT_803bb390,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80043d54  zz_0043d54_ ====

void zz_0043d54_(void)

{
  if (DAT_803bb38c != (int *)0x0) {
    zz_0197ad8_(DAT_803bb38c);
  }
  DAT_803bb38c = (int *)0x0;
  return;
}



// ==== 80043d98  zz_0043d98_ ====

void zz_0043d98_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if (DAT_803bb3bc != 0) {
    param_1 = zz_0043e60_();
  }
  uVar1 = 8;
  gnt4_memset(&DAT_803bb3bc,0,8);
  DAT_803bb3c0 = DAT_80436238 + 0x778c00;
  zz_000b000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9 + 0xa05,
              DAT_803bb3c0,uVar1,param_12,param_13,param_14,param_15,param_16);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80043e20,0,uVar1,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80043e20  FUN_80043e20 ====

void FUN_80043e20(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  DAT_803bb3bc = zz_0197a0c_(1);
  zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803bb3bc,
              DAT_803bb3c0,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80043e60  zz_0043e60_ ====

void zz_0043e60_(void)

{
  if (DAT_803bb3bc != (int *)0x0) {
    zz_0197ad8_(DAT_803bb3bc);
  }
  DAT_803bb3bc = (int *)0x0;
  return;
}



// ==== 80043ea4  zz_0043ea4_ ====

void zz_0043ea4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if (DAT_803bb3c4 != 0) {
    param_1 = zz_0043f6c_();
  }
  uVar1 = 8;
  gnt4_memset(&DAT_803bb3c4,0,8);
  DAT_803bb3c8 = DAT_80436238 + 0x7b8c00;
  zz_000b000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9 + 0xa13,
              DAT_803bb3c8,uVar1,param_12,param_13,param_14,param_15,param_16);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80043f2c,0,uVar1,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80043f2c  FUN_80043f2c ====

void FUN_80043f2c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  DAT_803bb3c4 = zz_0197a0c_(1);
  zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803bb3c4,
              DAT_803bb3c8,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80043f6c  zz_0043f6c_ ====

void zz_0043f6c_(void)

{
  if (DAT_803bb3c4 != (int *)0x0) {
    zz_0197ad8_(DAT_803bb3c4);
  }
  DAT_803bb3c4 = (int *)0x0;
  return;
}



// ==== 80043fb0  zz_0043fb0_ ====

void zz_0043fb0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if (DAT_803bb3cc != 0) {
    param_1 = zz_0044078_();
  }
  uVar1 = 8;
  gnt4_memset(&DAT_803bb3cc,0,8);
  DAT_803bb3d0 = DAT_80436238 + 0x7bcc00;
  zz_000b000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9 + 0xa24,
              DAT_803bb3d0,uVar1,param_12,param_13,param_14,param_15,param_16);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80044038,0,uVar1,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80044038  FUN_80044038 ====

void FUN_80044038(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  DAT_803bb3cc = zz_0197a0c_(1);
  zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803bb3cc,
              DAT_803bb3d0,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80044078  zz_0044078_ ====

void zz_0044078_(void)

{
  if (DAT_803bb3cc != (int *)0x0) {
    zz_0197ad8_(DAT_803bb3cc);
  }
  DAT_803bb3cc = (int *)0x0;
  return;
}



// ==== 800440bc  zz_00440bc_ ====

void zz_00440bc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 uVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  if (DAT_803bb3d4 != 0) {
    param_1 = zz_0044178_();
  }
  uVar1 = 8;
  gnt4_memset(&DAT_803bb3d4,0,8);
  DAT_803bb3d8 = DAT_80436238 + 0xc9ac00;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x9cb,DAT_803bb3d8,
              uVar1,in_r6,in_r7,in_r8,in_r9,in_r10);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80044138,0,uVar1,
              in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 80044138  FUN_80044138 ====

void FUN_80044138(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  DAT_803bb3d4 = zz_0197a0c_(1);
  zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803bb3d4,
              DAT_803bb3d8,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80044178  zz_0044178_ ====

void zz_0044178_(void)

{
  if (DAT_803bb3d4 != (int *)0x0) {
    zz_0197ad8_(DAT_803bb3d4);
  }
  DAT_803bb3d4 = (int *)0x0;
  return;
}



// ==== 800441bc  zz_00441bc_ ====

void zz_00441bc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = DAT_80436238 + 0xfe800;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x14,iVar1,param_11,
              param_12,param_13,param_14,param_15,param_16);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_008bed8_,4,iVar1,
              &DAT_803c04b0,&DAT_803c03b0,&DAT_803c0350,param_15,param_16);
  return;
}



// ==== 80044228  zz_0044228_ ====

void zz_0044228_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = DAT_80436238 + 0xb51400;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x17,iVar1,param_11,
              param_12,param_13,param_14,param_15,param_16);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_008bed8_,4,iVar1,
              &DAT_803c00e8,&DAT_803c00c8,&DAT_803c00bc,param_15,param_16);
  return;
}



// ==== 80044294  zz_0044294_ ====

void zz_0044294_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  
  uVar2 = 0x802d0000;
  iVar1 = *(int *)(&DAT_802d0a30 + param_9 * 8);
  gnt4_memset(&DAT_803bb32c + iVar1 * 2,0,8);
  iVar3 = DAT_80436238 + *(int *)(&DAT_802d0a34 + param_9 * 8);
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x9c4,iVar3,
              DAT_80436238,uVar2,in_r7,in_r8,in_r9,in_r10);
  *(int *)(&DAT_803bb330 + iVar1 * 8) = iVar3;
  return;
}



// ==== 80044318  zz_0044318_ ====

void zz_0044318_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  undefined4 extraout_r4;
  int *piVar3;
  undefined8 uVar4;
  
  iVar2 = *(int *)(&DAT_802d0a30 + param_9 * 8);
  piVar3 = &DAT_803bb32c + iVar2 * 2;
  piVar1 = zz_0197a0c_(1);
  *piVar3 = (int)piVar1;
  uVar4 = zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar3,
                      *(uint **)(&DAT_803bb330 + iVar2 * 8),param_11,param_12,param_13,param_14,
                      param_15,param_16);
  zz_0008a94_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar3,extraout_r4,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8004437c  zz_004437c_ ====

void zz_004437c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = DAT_80436238 + *(int *)(&DAT_80433698 + param_9 * 4);
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xaa9,iVar1,
              DAT_80436238,param_12,param_13,param_14,param_15,param_16);
  DAT_803bb33c = 0;
  DAT_803bb340 = iVar1;
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0040edc_,1,
              &DAT_803bb33c,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800443ec  zz_00443ec_ ====

void zz_00443ec_(void)

{
  zz_0197ad8_(DAT_803bb33c);
  return;
}



// ==== 80044418  zz_0044418_ ====

void zz_0044418_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  
  uVar2 = 0x802d0000;
  iVar1 = *(int *)(&DAT_802d0a40 + param_9 * 8);
  gnt4_memset(&DAT_803bb32c + iVar1 * 2,0,8);
  iVar3 = DAT_80436238 + *(int *)(&DAT_802d0a44 + param_9 * 8);
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xa2a,iVar3,
              DAT_80436238,uVar2,in_r7,in_r8,in_r9,in_r10);
  *(int *)(&DAT_803bb330 + iVar1 * 8) = iVar3;
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0040edc_,1,
              &DAT_803bb32c + iVar1 * 2,uVar2,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 800444b4  zz_00444b4_ ====

void zz_00444b4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 8;
  gnt4_memset(&DAT_803bb34c,0,8);
  iVar2 = DAT_80436238 + 0xb79c00;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)*(short *)(&DAT_804336a0 + param_9 * 2),iVar2,uVar1,param_12,param_13,param_14,
              param_15,param_16);
  DAT_803bb350 = iVar2;
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0040edc_,1,
              &DAT_803bb34c,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8004453c  zz_004453c_ ====

void zz_004453c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = DAT_80436238 + *(int *)(&DAT_802d0b64 + param_9 * 8);
  DAT_80436160 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x9c5,
                             iVar1,DAT_80436238,param_12,param_13,param_14,param_15,param_16);
  zz_000b1a0_(iVar1,*(undefined4 *)(&DAT_802d0b60 + param_9 * 8),DAT_80436160);
  return;
}



// ==== 800445ac  zz_00445ac_ ====

void zz_00445ac_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_memset(&DAT_803bb354,0,8);
  iVar1 = *(int *)(&DAT_802d0b60 + param_9 * 8);
  uVar3 = 1;
  DAT_803bb358 = DAT_80436238 + *(int *)(&DAT_802d0b64 + param_9 * 8);
  iVar2 = DAT_80436160;
  iVar4 = DAT_80436238;
  zz_00f19f8_(DAT_803bb358,iVar1,DAT_80436160,1);
  zz_0040edc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803bb354,iVar1,
              iVar2,uVar3,iVar4,in_r8,in_r9,in_r10);
  return;
}



// ==== 80044630  zz_0044630_ ====

void zz_0044630_(void)

{
  zz_0197ad8_(DAT_803bb354);
  return;
}



// ==== 8004465c  FUN_8004465c ====

void FUN_8004465c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  *(undefined4 *)(PTR_DAT_80433954 + 0x4c) = DAT_803b076c;
  *(undefined4 *)(PTR_DAT_80433954 + 0x58) = DAT_803b0770;
  *(undefined4 *)(PTR_DAT_80433954 + 100) = DAT_803b0774;
  *(undefined4 *)(PTR_DAT_80433954 + 0x70) = DAT_803c0654;
  zz_00f0e5c_(0,*(int *)(PTR_DAT_80433954 + 0x4c));
  uVar1 = zz_00ef9d4_(0,*(int *)(PTR_DAT_80433954 + 0x58),0);
  zz_00f192c_(*(uint *)(PTR_DAT_80433954 + 100),0,*(int *)(PTR_DAT_80433954 + 0x70));
  zz_00f19f8_(DAT_803b0778,0xa34000,0x2800,0);
  *(undefined4 *)(PTR_DAT_80433954 + 0x94) = DAT_803c065c;
  zz_00f19f8_(DAT_803b077c,0xa22000,*(int *)(PTR_DAT_80433954 + 0x94),0);
  *(undefined4 *)(PTR_DAT_80433954 + 0x98) = DAT_803c0660;
  zz_00f19f8_(DAT_803b0780,0xa28000,*(int *)(PTR_DAT_80433954 + 0x98),0);
  zz_008bed8_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803b0784,
              &DAT_803c00a4,(uint *)&DAT_803c0084,(uint *)&DAT_803c0078,&DAT_803b076c,in_r8,in_r9,
              in_r10);
  return;
}



// ==== 800447a8  zz_00447a8_ ====

void zz_00447a8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  DAT_803b076c = DAT_80436238 + 0xa4cc00;
  iVar6 = DAT_80436238 + 0xfe800;
  iVar5 = DAT_80436238 + 0x87000;
  iVar2 = DAT_80436238 + 0xa5000;
  puVar1 = &DAT_803c00a4;
  DAT_803b0770 = DAT_80436238 + 0xa4bc00;
  iVar4 = DAT_80436238 + 0xa4dc00;
  iVar3 = DAT_80436238 + 0xa53c00;
  DAT_803c00a4 = 0;
  DAT_803b0774 = iVar6;
  DAT_803b0778 = iVar5;
  DAT_803b077c = iVar4;
  DAT_803b0780 = iVar3;
  DAT_803b0784 = iVar2;
  zz_000b07c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x1e3,&DAT_803b076c,
              &DAT_803c00a4,iVar2,iVar3,iVar4,iVar5,iVar6);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_8004465c,0,puVar1,
              iVar2,iVar3,iVar4,iVar5,iVar6);
  return;
}



// ==== 80044848  zz_0044848_ ====

void zz_0044848_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  
  uVar4 = 0x802d0000;
  iVar2 = param_9 * 8;
  uVar3 = 8;
  sVar1 = *(short *)(&DAT_802d0a52 + iVar2);
  iVar5 = iVar2;
  gnt4_memset(&DAT_803bb32c + sVar1 * 2,0,8);
  iVar6 = *(int *)(&DAT_802d0a54 + iVar2) + DAT_80436238;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)*(short *)(&DAT_802d0a50 + iVar2),iVar6,uVar3,uVar4,iVar5,in_r8,in_r9,in_r10);
  *(int *)(&DAT_803bb330 + sVar1 * 8) = iVar6;
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0040edc_,1,
              &DAT_803bb32c + sVar1 * 2,uVar4,iVar5,in_r8,in_r9,in_r10);
  return;
}



// ==== 800448dc  zz_00448dc_ ====

void zz_00448dc_(int param_1)

{
  zz_0197ad8_((int *)(&DAT_803bb32c)[*(short *)(&DAT_802d0a52 + param_1 * 8) * 2]);
  return;
}



// ==== 80044920  zz_0044920_ ====

void zz_0044920_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_9 * 8;
  iVar2 = *(int *)(&DAT_802d0b14 + iVar1) + DAT_80436238;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)*(short *)(&DAT_802d0b10 + iVar1),iVar2,iVar1,param_12,param_13,param_14,param_15
              ,param_16);
  iVar1 = (int)*(short *)(&DAT_802d0b12 + iVar1);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_008bed8_,4,iVar2,
              &DAT_803c04b0 + iVar1 * 0x18,&DAT_803c03b0 + iVar1 * 0x20,&DAT_803c0350 + iVar1 * 0xc,
              iVar1 * 0x18,param_16);
  return;
}



// ==== 800449c0  zz_00449c0_ ====

void zz_00449c0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,DAT_80436238,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800449e8  zz_00449e8_ ====

void zz_00449e8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar5;
  
  zz_00f19f8_(DAT_80436238 + 0x87000,0xa34000,0x2800,1);
  iVar4 = param_9 * 8;
  if (*(int *)(&DAT_802d0c18 + iVar4) != 0) {
    uVar5 = *(int *)(&DAT_802d0c18 + iVar4) + DAT_80436238 + 0x3000;
    zz_00f19f8_(uVar5,0xa28000,*(int *)(PTR_DAT_80433954 + 0x98),1);
    param_1 = zz_0096bc4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar5,
                          DAT_80436238 + *(int *)(&DAT_802d0c18 + iVar4));
  }
  uVar3 = 1;
  uVar5 = DAT_80436238 + *(int *)(&DAT_802d0c1c + iVar4);
  iVar4 = DAT_80436238;
  zz_00f19f8_(uVar5,0xa22000,*(int *)(PTR_DAT_80433954 + 0x94),1);
  uVar1 = 0;
  uVar2 = 8;
  gnt4_memset(&DAT_803bb37c,0,8);
  DAT_803bb380 = uVar5;
  zz_0040edc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803bb37c,uVar1,
              uVar2,uVar3,iVar4,in_r8,in_r9,in_r10);
  return;
}



// ==== 80044af0  zz_0044af0_ ====

void zz_0044af0_(void)

{
  zz_0197ad8_(DAT_803bb37c);
  return;
}



// ==== 80044b1c  zz_0044b1c_ ====

void zz_0044b1c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)*(short *)(&DAT_802d0990 + param_9 * 2),DAT_80436238 + 0x40bc00,0x802d0000,
              param_12,param_13,param_14,param_15,param_16);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0096bc4_,2,
              DAT_80436238 + 0x40bc00,DAT_80436238 + 0x408c00,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80044b80  zz_0044b80_ ====

void zz_0044b80_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = DAT_80436238 + 0xb59c00;
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)*(short *)(&DAT_802d09b0 + param_9 * 2),iVar1,DAT_80436238,param_12,param_13,
              param_14,param_15,param_16);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0096bc4_,2,iVar1,
              DAT_80436238 + 0xb56c00,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80044bec  zz_0044bec_ ====

void zz_0044bec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  iVar2 = param_9 * 0x10;
  piVar1 = (int *)(&DAT_802d09d4 + iVar2);
  uVar4 = *piVar1 + DAT_80436238 + 0x3000;
  if (param_10 == 1) {
    zz_00f19f8_(uVar4,*(int *)(&DAT_802d09d8 + iVar2),*(int *)(&DAT_802d09dc + iVar2),1);
    zz_0096bc4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar4,
                DAT_80436238 + *piVar1);
  }
  else if (param_10 < 1) {
    if (-1 < param_10) {
      zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(&DAT_802d09d0 + iVar2),uVar4,DAT_80436238,param_12,param_13,param_14,
                  param_15,param_16);
      zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0096bc4_,2,
                  uVar4,DAT_80436238 + *piVar1,param_13,param_14,param_15,param_16);
    }
  }
  else if (param_10 < 3) {
    iVar3 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(&DAT_802d09d0 + iVar2),uVar4,DAT_80436238,param_12,param_13,
                        param_14,param_15,param_16);
    *(int *)(&DAT_802d09dc + iVar2) = iVar3;
    zz_000b1a0_(uVar4,*(undefined4 *)(&DAT_802d09d8 + iVar2),*(int *)(&DAT_802d09dc + iVar2));
  }
  return;
}



// ==== 80044cf4  zz_0044cf4_ ====

void zz_0044cf4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,short param_10)

{
  short *psVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  
  gnt4_memset(&DAT_803bb364,0,8);
  iVar4 = 0;
  iVar5 = DAT_80436238 + *(int *)(&DAT_802d0be0 + param_9 * 4);
  for (psVar1 = &DAT_8035b2dc; (iVar2 = 0, *psVar1 != -1 && (iVar2 = iVar4, param_10 != *psVar1));
      psVar1 = psVar1 + 8) {
    if (1 < psVar1[1]) {
      iVar4 = iVar4 + 1;
    }
  }
  iVar3 = DAT_80436238;
  zz_000b000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2 + 0xa2b,iVar5,
              iVar2,DAT_80436238,iVar4,in_r8,in_r9,in_r10);
  DAT_803bb368 = iVar5;
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0040edc_,1,
              &DAT_803bb364,iVar3,iVar4,in_r8,in_r9,in_r10);
  return;
}



// ==== 80044ddc  zz_0044ddc_ ====

void zz_0044ddc_(void)

{
  zz_0197ad8_(DAT_803bb364);
  return;
}



// ==== 80044e08  zz_0044e08_ ====

void zz_0044e08_(void)

{
  return;
}



// ==== 80044e0c  FUN_80044e0c ====

void FUN_80044e0c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  uVar1 = 0x803c0000;
  DAT_803bb360 = (&DAT_803b0730)[param_9];
  uVar2 = zz_0040edc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803bb35c,
                      &DAT_803b0730,0x803c0000,param_12,param_13,param_14,param_15,param_16);
  if (DAT_803b074c != -0x10000000) {
    DAT_803bb370 = DAT_803b074c;
    zz_0040edc_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803bb36c,
                DAT_803b074c,uVar1,param_12,param_13,param_14,param_15,param_16);
  }
  if (DAT_803b0750 != -0x10000000) {
    *(int *)PTR_DAT_80433954 = DAT_803b0750;
    *(undefined4 *)(PTR_DAT_80433954 + 4) = DAT_803b0754;
    *(undefined4 *)(PTR_DAT_80433954 + 8) = DAT_803b0758;
    zz_003d4a0_();
  }
  return;
}



// ==== 80044eb4  zz_0044eb4_ ====

void zz_0044eb4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,int param_11)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  
  iVar2 = DAT_80436238;
  DAT_803b0730 = 0xf0000000;
  DAT_803b0734 = 0xf0000000;
  DAT_803b0738 = 0xf0000000;
  DAT_803b073c = 0xf0000000;
  DAT_803b0740 = 0xf0000000;
  DAT_803b0744 = 0xf0000000;
  DAT_803b0748 = 0xf0000000;
  DAT_803b074c = -0x10000000;
  DAT_803b0750 = -0x10000000;
  DAT_803b0754 = 0xf0000000;
  DAT_803b0758 = 0xf0000000;
  DAT_803b075c = 0xf0000000;
  iVar7 = param_9 * 0x20;
  iVar6 = param_10 * 0x10;
  piVar8 = (int *)(iVar7 + -0x7fd2f3a8 + iVar6 + 4);
  iVar3 = *piVar8;
  iVar5 = param_9 * 4;
  iVar4 = DAT_80436238 + *(int *)(iVar7 + -0x7fd2f3a8 + iVar6);
  (&DAT_803b0730)[param_9] = iVar4;
  if (iVar3 != -0x10000000) {
    DAT_803b074c = iVar2 + *piVar8;
  }
  piVar1 = (int *)(iVar7 + iVar6 + -0x7fd2f3a0);
  if (*piVar1 != -0x10000000) {
    DAT_803b0750 = iVar2 + *piVar1;
    DAT_803b0758 = 0;
    DAT_803b0754 = 0;
  }
  if (param_11 == 0) {
    zz_000b07c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x1e4,&DAT_803b0730,
                0,iVar4,iVar5,iVar6,iVar7,piVar8);
    zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80044e0c,1,
                param_9,iVar4,iVar5,iVar6,iVar7,piVar8);
  }
  else {
    zz_000b0f8_(0xb22800,&DAT_803b0730);
    zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80044e0c,1,
                param_9,iVar4,iVar5,iVar6,iVar7,piVar8);
  }
  return;
}



// ==== 80045010  zz_0045010_ ====

void zz_0045010_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_000b124_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x1e4,0xb22800,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8004503c  FUN_8004503c ====

/* WARNING: Removing unreachable block (ram,0x800450c4) */
/* WARNING: Removing unreachable block (ram,0x8004504c) */

undefined4 FUN_8004503c(double param_1,float *param_2,float *param_3,float *param_4)

{
  undefined4 uVar1;
  double dVar2;
  
  gnt4_PSMTXMultVec_bl(param_2,param_3,param_4);
  dVar2 = (double)param_4[2];
  if (((double)FLOAT_80437070 == dVar2) && ((double)FLOAT_80437070 == param_1)) {
    uVar1 = 0;
  }
  else if (FLOAT_80437070 <= (float)(dVar2 / param_1)) {
    uVar1 = 1;
    *param_4 = (float)((double)(float)((double)*param_4 * param_1) / dVar2);
    param_4[1] = (float)((double)param_4[1] * param_1) / param_4[2];
    param_4[2] = (float)param_1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 800450e0  FUN_800450e0 ====

undefined4 FUN_800450e0(double param_1,double param_2,float *param_3,float *param_4,float *param_5)

{
  undefined4 uVar1;
  float afStack_38 [13];
  
  if (((double)FLOAT_80437070 == param_2) || ((double)FLOAT_80437074 == param_2)) {
    uVar1 = 0;
  }
  else {
    *param_5 = (float)((double)(*param_4 * (float)(param_1 + param_2)) / param_2);
    param_5[1] = (float)((double)(param_4[1] * (float)(param_1 + param_2)) / param_2);
    param_5[2] = (float)param_1;
    gnt4_PSMTXInverse_bl(param_3,afStack_38);
    gnt4_PSMTXMultVec_bl(afStack_38,param_5,param_5);
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 8004516c  zz_004516c_ ====

void zz_004516c_(float *param_1,float *param_2,float *param_3)

{
  float afStack_38 [12];
  
  gnt4_PSMTXInverse_bl(param_1,afStack_38);
  gnt4_PSMTXMultVec_bl(afStack_38,param_2,param_3);
  return;
}



// ==== 800451b8  zz_00451b8_ ====

void zz_00451b8_(float *param_1,float *param_2,float *param_3)

{
  float afStack_38 [12];
  
  gnt4_PSMTXInverse_bl(param_1,afStack_38);
  gnt4_PSMTXMultVecSR_bl(afStack_38,param_2,param_3);
  return;
}



// ==== 80045204  zz_0045204_ ====

/* WARNING: Removing unreachable block (ram,0x80045214) */

double zz_0045204_(short param_1)

{
  double dVar1;
  
  dVar1 = gnt4_sin_bl((double)(float)((double)FLOAT_80437078 *
                                     (double)((longlong)(double)param_1 * 0x3ff0000000000000)));
  return (double)(float)dVar1;
}



// ==== 80045238  zz_0045238_ ====

/* WARNING: Removing unreachable block (ram,0x80045248) */

double zz_0045238_(short param_1)

{
  double dVar1;
  
  dVar1 = gnt4_cos_bl((double)(float)((double)FLOAT_80437078 *
                                     (double)((longlong)(double)param_1 * 0x3ff0000000000000)));
  return (double)(float)dVar1;
}



// ==== 8004526c  zz_004526c_ ====

/* WARNING: Removing unreachable block (ram,0x8004527c) */

double zz_004526c_(short param_1)

{
  double dVar1;
  
  dVar1 = gnt4_tan_bl((double)(float)((double)FLOAT_80437078 *
                                     (double)((longlong)(double)param_1 * 0x3ff0000000000000)));
  return (double)(float)dVar1;
}



// ==== 800452a0  FUN_800452a0 ====

/* WARNING: Removing unreachable block (ram,0x800452cc) */
/* WARNING: Removing unreachable block (ram,0x800452c4) */
/* WARNING: Removing unreachable block (ram,0x800452b0) */

int FUN_800452a0(double param_1,double param_2)

{
  double dVar1;
  
  dVar1 = (double)gnt4_atan2_bl(param_1,param_2);
  return (int)(short)(FLOAT_8043707c * (float)dVar1 * 1.0);
}



// ==== 800452e4  FUN_800452e4 ====

/* WARNING: Removing unreachable block (ram,0x80045370) */
/* WARNING: Removing unreachable block (ram,0x80045338) */
/* WARNING: Removing unreachable block (ram,0x800452f4) */

uint FUN_800452e4(double param_1,float *param_2,short param_3)

{
  float fVar1;
  bool bVar2;
  double dVar3;
  double dVar4;
  
  bVar2 = param_2[2] * param_2[2] + *param_2 * *param_2 + param_2[1] * param_2[1] <=
          (float)(param_1 * param_1);
  if (bVar2) {
    dVar4 = (double)(float)((double)FLOAT_80437078 *
                           (double)((longlong)(double)param_3 * 0x3ff0000000000000));
    dVar3 = gnt4_sin_bl(dVar4);
    fVar1 = FLOAT_80437070;
    *param_2 = (float)dVar3;
    param_2[1] = fVar1;
    dVar3 = gnt4_cos_bl(dVar4);
    param_2[2] = (float)dVar3;
  }
  return (uint)bVar2;
}



// ==== 8004538c  zz_004538c_ ====

bool zz_004538c_(float *param_1,float *param_2)

{
  float fVar1;
  bool bVar2;
  
  bVar2 = FLOAT_80437080 < param_1[2] * param_1[2] + *param_1 * *param_1 + param_1[1] * param_1[1];
  if (bVar2) {
    gnt4_PSVECNormalize_bl(param_1,param_2);
  }
  else {
    fVar1 = param_1[1];
    *param_2 = *param_1;
    param_2[1] = fVar1;
    param_2[2] = param_1[2];
  }
  return !bVar2;
}



// ==== 800453fc  zz_00453fc_ ====

/* WARNING: Removing unreachable block (ram,0x80045420) */

void zz_00453fc_(char param_1,float *param_2,float *param_3,short param_4)

{
  float afStack_44 [15];
  
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437078 *
                                     (double)((longlong)(double)param_4 * 0x3ff0000000000000)),
                      afStack_44,(int)param_1);
  gnt4_PSMTXMultVecSR_bl(afStack_44,param_2,param_3);
  return;
}



// ==== 80045460  FUN_80045460 ====

/* WARNING: Removing unreachable block (ram,0x8004558c) */
/* WARNING: Removing unreachable block (ram,0x80045584) */
/* WARNING: Removing unreachable block (ram,0x80045478) */
/* WARNING: Removing unreachable block (ram,0x80045470) */

bool FUN_80045460(double param_1,float *param_2,float *param_3)

{
  double dVar1;
  double dVar2;
  float local_78;
  float local_74;
  float local_70;
  float afStack_6c [16];
  
  dVar1 = gnt4_PSVECMag_bl(param_3);
  dVar2 = gnt4_PSVECMag_bl(param_2);
  dVar2 = (double)(float)(dVar2 * dVar1);
  dVar1 = gnt4_PSQUATDotProduct_bl(param_2,param_3);
  dVar2 = (double)(float)(dVar1 / dVar2);
  dVar1 = (double)FLOAT_80437084;
  if ((dVar2 <= dVar1) && (dVar1 = dVar2, dVar2 < (double)FLOAT_80437088)) {
    dVar1 = (double)FLOAT_80437088;
  }
  dVar1 = (double)gnt4_acos_bl(dVar1);
  dVar2 = (double)(float)dVar1;
  dVar1 = dVar2;
  if (param_1 < dVar2) {
    dVar1 = param_1;
  }
  gnt4_PSVECCrossProduct_bl(param_2,param_3,&local_78);
  if (local_70 * local_70 + local_78 * local_78 + local_74 * local_74 <= FLOAT_80437080) {
    local_78 = DAT_802b0cb4;
    local_74 = DAT_802b0cb8;
    local_70 = DAT_802b0cbc;
  }
  gnt4_PSMTXRotAxisRad_bl(dVar1,afStack_6c,&local_78);
  gnt4_PSMTXMultVecSR_bl(afStack_6c,param_2,param_2);
  return param_1 < dVar2;
}



// ==== 800455b0  FUN_800455b0 ====

void FUN_800455b0(double param_1,double param_2,double param_3,float *param_4,float *param_5)

{
  float afStack_38 [12];
  
  gnt4_PSMTXTrans_bl(param_1,param_2,param_3,afStack_38);
  gnt4_PSMTXConcat_bl(param_4,afStack_38,param_5);
  return;
}



// ==== 800455fc  zz_00455fc_ ====

void zz_00455fc_(float *param_1,float *param_2,float *param_3)

{
  float afStack_38 [12];
  
  gnt4_PSMTXTrans_bl((double)*param_3,(double)param_3[1],(double)param_3[2],afStack_38);
  gnt4_PSMTXConcat_bl(param_1,afStack_38,param_2);
  return;
}



// ==== 80045654  zz_0045654_ ====

void zz_0045654_(double param_1,double param_2,double param_3,float *param_4,float *param_5)

{
  float afStack_38 [12];
  
  gnt4_PSMTXScale_bl(param_1,param_2,param_3,afStack_38);
  gnt4_PSMTXConcat_bl(param_4,afStack_38,param_5);
  return;
}



// ==== 800456a0  zz_00456a0_ ====

void zz_00456a0_(float *param_1,float *param_2,float *param_3)

{
  float afStack_38 [12];
  
  gnt4_PSMTXScale_bl((double)*param_3,(double)param_3[1],(double)param_3[2],afStack_38);
  gnt4_PSMTXConcat_bl(param_1,afStack_38,param_2);
  return;
}



// ==== 800456f8  zz_00456f8_ ====

void zz_00456f8_(float *param_1)

{
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  
  local_20 = *param_1;
  local_1c = param_1[4];
  local_18 = param_1[8];
  local_2c = param_1[1];
  local_28 = param_1[5];
  local_24 = param_1[9];
  local_38 = param_1[2];
  local_34 = param_1[6];
  local_30 = param_1[10];
  gnt4_PSVECNormalize_bl(&local_20,&local_20);
  gnt4_PSVECNormalize_bl(&local_2c,&local_2c);
  gnt4_PSVECNormalize_bl(&local_38,&local_38);
  *param_1 = local_20;
  param_1[4] = local_1c;
  param_1[8] = local_18;
  param_1[1] = local_2c;
  param_1[5] = local_28;
  param_1[9] = local_24;
  param_1[2] = local_38;
  param_1[6] = local_34;
  param_1[10] = local_30;
  return;
}



// ==== 800457d4  zz_00457d4_ ====

/* WARNING: Removing unreachable block (ram,0x800457f8) */

void zz_00457d4_(char param_1,float *param_2,float *param_3,short param_4)

{
  float afStack_44 [15];
  
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437078 *
                                     (double)((longlong)(double)param_4 * 0x3ff0000000000000)),
                      afStack_44,(int)param_1);
  gnt4_PSMTXConcat_bl(param_2,afStack_44,param_3);
  return;
}



// ==== 80045838  FUN_80045838 ====

/* WARNING: Removing unreachable block (ram,0x800458d8) */
/* WARNING: Removing unreachable block (ram,0x800458a4) */
/* WARNING: Removing unreachable block (ram,0x80045868) */

void FUN_80045838(float *param_1,float *param_2,short param_3,short param_4,short param_5)

{
  float afStack_40 [14];
  
  if (param_5 == 0) {
    gnt4_PSMTXCopy_bl(param_1,param_2);
  }
  else {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437078 *
                                       (double)((longlong)(double)param_5 * 0x3ff0000000000000)),
                        afStack_40,0x7a);
    gnt4_PSMTXConcat_bl(param_1,afStack_40,param_2);
  }
  if (param_4 != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437078 *
                                       (double)((longlong)(double)param_4 * 0x3ff0000000000000)),
                        afStack_40,0x79);
    gnt4_PSMTXConcat_bl(param_2,afStack_40,param_2);
  }
  if (param_3 != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437078 *
                                       (double)((longlong)(double)param_3 * 0x3ff0000000000000)),
                        afStack_40,0x78);
    gnt4_PSMTXConcat_bl(param_2,afStack_40,param_2);
  }
  return;
}



// ==== 80045918  FUN_80045918 ====

/* WARNING: Removing unreachable block (ram,0x80045ba0) */
/* WARNING: Removing unreachable block (ram,0x80045b98) */
/* WARNING: Removing unreachable block (ram,0x80045b90) */
/* WARNING: Removing unreachable block (ram,0x80045938) */
/* WARNING: Removing unreachable block (ram,0x80045930) */
/* WARNING: Removing unreachable block (ram,0x80045928) */

void FUN_80045918(float *param_1,float *param_2,int param_3,uint param_4)

{
  int iVar1;
  bool bVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [15];
  
  local_a0 = *param_1;
  local_9c = param_1[4];
  local_98 = param_1[8];
  local_ac = param_1[1];
  local_a8 = param_1[5];
  local_a4 = param_1[9];
  local_b8 = param_1[2];
  local_b4 = param_1[6];
  local_b0 = param_1[10];
  dVar3 = gnt4_PSVECMag_bl(&local_a0);
  dVar4 = gnt4_PSVECMag_bl(&local_ac);
  dVar5 = gnt4_PSVECMag_bl(&local_b8);
  local_88 = *param_2;
  local_84 = param_2[1];
  iVar1 = ((int)param_4 >> 0x1f ^ param_4) - ((int)param_4 >> 0x1f);
  local_80 = param_2[2];
  if (iVar1 == 2) {
    local_94 = param_1[1];
    local_90 = param_1[5];
    local_8c = param_1[9];
  }
  else if (iVar1 < 2) {
    if (0 < iVar1) {
      local_94 = *param_1;
      local_90 = param_1[4];
      local_8c = param_1[8];
    }
  }
  else if (iVar1 < 4) {
    local_94 = param_1[2];
    local_90 = param_1[6];
    local_8c = param_1[10];
  }
  if (param_3 < 0) {
    gnt4_PSQUATScale_bl((double)FLOAT_80437088,&local_88,&local_88);
    param_3 = -param_3;
  }
  if ((int)param_4 < 0) {
    gnt4_PSQUATScale_bl((double)FLOAT_80437088,&local_94,&local_94);
    param_4 = -param_4;
  }
  bVar2 = zz_0045ef4_(param_1,(int)(char)(&DAT_802d0d34)[param_4 + param_3 * 3],&local_88,&local_94)
  ;
  if (bVar2) {
    iVar1 = param_4 + 1;
    if (3 < iVar1) {
      iVar1 = 1;
    }
    if (iVar1 == 2) {
      local_94 = param_1[1];
      local_90 = param_1[5];
      local_8c = param_1[9];
    }
    else if (iVar1 < 2) {
      if (0 < iVar1) {
        local_94 = *param_1;
        local_90 = param_1[4];
        local_8c = param_1[8];
      }
    }
    else if (iVar1 < 4) {
      local_94 = param_1[2];
      local_90 = param_1[6];
      local_8c = param_1[10];
    }
    zz_0045ef4_(param_1,(int)(char)(&DAT_802d0d34)[iVar1 + param_3 * 3],&local_88,&local_94);
  }
  gnt4_PSMTXScale_bl(dVar3,dVar4,dVar5,afStack_7c);
  gnt4_PSMTXConcat_bl(param_1,afStack_7c,param_1);
  return;
}



// ==== 80045bc8  FUN_80045bc8 ====

/* WARNING: Removing unreachable block (ram,0x80045e54) */
/* WARNING: Removing unreachable block (ram,0x80045e4c) */
/* WARNING: Removing unreachable block (ram,0x80045be0) */
/* WARNING: Removing unreachable block (ram,0x80045bd8) */

void FUN_80045bc8(double param_1,float *param_2,float *param_3,uint param_4)

{
  int iVar1;
  double dVar2;
  double dVar3;
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
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  
  iVar1 = ((int)param_4 >> 0x1f ^ param_4) - ((int)param_4 >> 0x1f);
  if (iVar1 == 2) {
    local_64 = param_2[1];
    local_60 = param_2[5];
    local_5c = param_2[9];
  }
  else if (iVar1 < 2) {
    if (0 < iVar1) {
      local_64 = *param_2;
      local_60 = param_2[4];
      local_5c = param_2[8];
    }
  }
  else if (iVar1 < 4) {
    local_64 = param_2[2];
    local_60 = param_2[6];
    local_5c = param_2[10];
  }
  if ((int)param_4 < 0) {
    gnt4_PSQUATScale_bl((double)FLOAT_80437088,&local_64,&local_64);
  }
  dVar2 = gnt4_PSVECMag_bl(&local_64);
  dVar3 = gnt4_PSVECMag_bl(param_3);
  dVar3 = (double)(float)(dVar3 * dVar2);
  dVar2 = gnt4_PSQUATDotProduct_bl(&local_64,param_3);
  dVar3 = (double)(float)(dVar2 / dVar3);
  dVar2 = (double)FLOAT_80437084;
  if ((dVar3 <= dVar2) && (dVar2 = dVar3, dVar3 < (double)FLOAT_80437088)) {
    dVar2 = (double)FLOAT_80437088;
  }
  dVar3 = (double)gnt4_acos_bl(dVar2);
  dVar2 = (double)(float)dVar3;
  if (param_1 < (double)(float)dVar3) {
    dVar2 = param_1;
  }
  gnt4_PSVECCrossProduct_bl(&local_64,param_3,&local_64);
  if (local_5c * local_5c + local_64 * local_64 + local_60 * local_60 <= FLOAT_80437080) {
    local_64 = DAT_802b0cb4;
    local_60 = DAT_802b0cb8;
    local_5c = DAT_802b0cbc;
  }
  local_70 = *param_2;
  local_6c = param_2[4];
  local_68 = param_2[8];
  local_7c = param_2[1];
  local_78 = param_2[5];
  local_74 = param_2[9];
  local_88 = param_2[2];
  local_84 = param_2[6];
  local_80 = param_2[10];
  gnt4_PSVECNormalize_bl(&local_70,&local_70);
  gnt4_PSVECNormalize_bl(&local_7c,&local_7c);
  gnt4_PSVECNormalize_bl(&local_88,&local_88);
  local_58 = local_70;
  local_48 = local_6c;
  local_38 = local_68;
  local_54 = local_7c;
  local_44 = local_78;
  local_34 = local_74;
  local_50 = local_88;
  local_40 = local_84;
  local_30 = local_80;
  local_4c = FLOAT_80437070;
  local_3c = FLOAT_80437070;
  local_2c = FLOAT_80437070;
  zz_00451b8_(&local_58,&local_64,&local_64);
  gnt4_PSMTXRotAxisRad_bl(dVar2,&local_58,&local_64);
  gnt4_PSMTXConcat_bl(param_2,&local_58,param_2);
  return;
}



// ==== 80045e74  zz_0045e74_ ====

void zz_0045e74_(float *param_1,float *param_2,short param_3)

{
  float afStack_58 [3];
  float afStack_4c [13];
  undefined4 local_18;
  uint uStack_14;
  
  zz_00451b8_(param_1,param_2,afStack_58);
  uStack_14 = (int)param_3 ^ 0x80000000;
  local_18 = 0x43300000;
  gnt4_PSMTXRotAxisRad_bl
            ((double)(FLOAT_80437078 *
                     (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80437090)),afStack_4c,
             afStack_58);
  gnt4_PSMTXConcat_bl(param_1,afStack_4c,param_1);
  return;
}



// ==== 80045ef4  zz_0045ef4_ ====

bool zz_0045ef4_(float *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  
  iVar1 = (*(code *)(&PTR_FUN_802d0d44)[param_2])(param_3,param_4,&local_20,&local_2c,&local_38);
  if (iVar1 == 0) {
    gnt4_PSVECNormalize_bl(&local_20,&local_20);
    gnt4_PSVECNormalize_bl(&local_2c,&local_2c);
    gnt4_PSVECNormalize_bl(&local_38,&local_38);
    *param_1 = local_20;
    param_1[4] = local_1c;
    param_1[8] = local_18;
    param_1[1] = local_2c;
    param_1[5] = local_28;
    param_1[9] = local_24;
    param_1[2] = local_38;
    param_1[6] = local_34;
    param_1[10] = local_30;
  }
  return iVar1 != 0;
}



// ==== 80045fc8  FUN_80045fc8 ====

bool FUN_80045fc8(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  bool bVar2;
  
  fVar1 = param_1[1];
  *param_3 = *param_1;
  param_3[1] = fVar1;
  param_3[2] = param_1[2];
  fVar1 = param_2[1];
  *param_4 = *param_2;
  param_4[1] = fVar1;
  param_4[2] = param_2[2];
  gnt4_PSVECCrossProduct_bl(param_3,param_4,param_5);
  bVar2 = FLOAT_80437080 < param_5[2] * param_5[2] + *param_5 * *param_5 + param_5[1] * param_5[1];
  if (bVar2) {
    gnt4_PSVECCrossProduct_bl(param_5,param_3,param_4);
  }
  return !bVar2;
}



// ==== 80046090  FUN_80046090 ====

bool FUN_80046090(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  bool bVar2;
  
  fVar1 = param_1[1];
  *param_3 = *param_1;
  param_3[1] = fVar1;
  param_3[2] = param_1[2];
  fVar1 = param_2[1];
  *param_5 = *param_2;
  param_5[1] = fVar1;
  param_5[2] = param_2[2];
  gnt4_PSVECCrossProduct_bl(param_5,param_3,param_4);
  bVar2 = FLOAT_80437080 < param_4[2] * param_4[2] + *param_4 * *param_4 + param_4[1] * param_4[1];
  if (bVar2) {
    gnt4_PSVECCrossProduct_bl(param_3,param_4,param_5);
  }
  return !bVar2;
}



// ==== 80046158  FUN_80046158 ====

bool FUN_80046158(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  bool bVar2;
  
  fVar1 = param_1[1];
  *param_4 = *param_1;
  param_4[1] = fVar1;
  param_4[2] = param_1[2];
  fVar1 = param_2[1];
  *param_3 = *param_2;
  param_3[1] = fVar1;
  param_3[2] = param_2[2];
  gnt4_PSVECCrossProduct_bl(param_3,param_4,param_5);
  bVar2 = FLOAT_80437080 < param_5[2] * param_5[2] + *param_5 * *param_5 + param_5[1] * param_5[1];
  if (bVar2) {
    gnt4_PSVECCrossProduct_bl(param_4,param_5,param_3);
  }
  return !bVar2;
}



// ==== 80046220  FUN_80046220 ====

bool FUN_80046220(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  bool bVar2;
  
  fVar1 = param_1[1];
  *param_4 = *param_1;
  param_4[1] = fVar1;
  param_4[2] = param_1[2];
  fVar1 = param_2[1];
  *param_5 = *param_2;
  param_5[1] = fVar1;
  param_5[2] = param_2[2];
  gnt4_PSVECCrossProduct_bl(param_4,param_5,param_3);
  bVar2 = FLOAT_80437080 < param_3[2] * param_3[2] + *param_3 * *param_3 + param_3[1] * param_3[1];
  if (bVar2) {
    gnt4_PSVECCrossProduct_bl(param_3,param_4,param_5);
  }
  return !bVar2;
}



// ==== 800462e4  FUN_800462e4 ====

bool FUN_800462e4(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  bool bVar2;
  
  fVar1 = param_1[1];
  *param_5 = *param_1;
  param_5[1] = fVar1;
  param_5[2] = param_1[2];
  fVar1 = param_2[1];
  *param_3 = *param_2;
  param_3[1] = fVar1;
  param_3[2] = param_2[2];
  gnt4_PSVECCrossProduct_bl(param_5,param_3,param_4);
  bVar2 = FLOAT_80437080 < param_4[2] * param_4[2] + *param_4 * *param_4 + param_4[1] * param_4[1];
  if (bVar2) {
    gnt4_PSVECCrossProduct_bl(param_4,param_5,param_3);
  }
  return !bVar2;
}



// ==== 800463ac  FUN_800463ac ====

bool FUN_800463ac(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  bool bVar2;
  
  fVar1 = param_1[1];
  *param_5 = *param_1;
  param_5[1] = fVar1;
  param_5[2] = param_1[2];
  fVar1 = param_2[1];
  *param_4 = *param_2;
  param_4[1] = fVar1;
  param_4[2] = param_2[2];
  gnt4_PSVECCrossProduct_bl(param_4,param_5,param_3);
  bVar2 = FLOAT_80437080 < param_3[2] * param_3[2] + *param_3 * *param_3 + param_3[1] * param_3[1];
  if (bVar2) {
    gnt4_PSVECCrossProduct_bl(param_5,param_3,param_4);
  }
  return !bVar2;
}



// ==== 80046470  zz_0046470_ ====

void zz_0046470_(float *param_1,float *param_2)

{
  double dVar1;
  float local_18;
  float local_14;
  float local_10;
  
  local_18 = *param_1;
  local_14 = param_1[4];
  local_10 = param_1[8];
  dVar1 = gnt4_PSVECMag_bl(&local_18);
  *param_2 = (float)dVar1;
  local_18 = param_1[1];
  local_14 = param_1[5];
  local_10 = param_1[9];
  dVar1 = gnt4_PSVECMag_bl(&local_18);
  param_2[1] = (float)dVar1;
  local_18 = param_1[2];
  local_14 = param_1[6];
  local_10 = param_1[10];
  dVar1 = gnt4_PSVECMag_bl(&local_18);
  param_2[2] = (float)dVar1;
  return;
}



// ==== 80046510  zz_0046510_ ====

int zz_0046510_(ushort param_1,int param_2)

{
  int iVar1;
  ushort local_8;
  
  if (param_2 == 2) {
    iVar1 = (int)(param_1 + 0x2000 & 0xffff) >> 0xe;
  }
  else if ((param_2 < 2) && (0 < param_2)) {
    local_8 = param_1;
    if ((short)param_1 < 0) {
      local_8 = -param_1;
    }
    iVar1 = (int)(local_8 + 0x1000) >> 0xd;
  }
  else {
    iVar1 = (int)(param_1 + 0x1000 & 0xffff) >> 0xd;
  }
  return iVar1;
}



// ==== 80046588  zz_0046588_ ====

/* WARNING: Removing unreachable block (ram,0x800465dc) */
/* WARNING: Removing unreachable block (ram,0x80046598) */

void zz_0046588_(double param_1,float *param_2,float *param_3,float *param_4)

{
  float afStack_38 [3];
  float afStack_2c [5];
  
  gnt4_PSQUATScale_bl(param_1,param_2,afStack_2c);
  gnt4_PSQUATScale_bl((double)(float)((double)FLOAT_80437084 - param_1),param_3,afStack_38);
  gnt4_PSVECAdd_bl(afStack_2c,afStack_38,param_4);
  return;
}



// ==== 800465fc  zz_00465fc_ ====

void zz_00465fc_(int param_1)

{
  if (*(char *)(param_1 + 0x4a0) != '\x02') {
    zz_0046754_(param_1);
    zz_0046bd0_(param_1,0);
    if (*(char *)(param_1 + 0x661) == '\0') {
      zz_0046e7c_(param_1);
      zz_0046bd0_(param_1,1);
    }
    if ((*(byte *)(param_1 + 0x3e5) & PTR_DAT_80433934[0xd2]) == 0) {
      zz_0047904_(param_1);
    }
    if (*(char *)(param_1 + 0x4a0) == '\x01') {
      zz_0047a2c_(param_1,*(int *)(param_1 + 0x4a4));
    }
  }
  return;
}



// ==== 80046698  zz_0046698_ ====

void zz_0046698_(int param_1)

{
  if (*(char *)(param_1 + 0x4a0) != '\x02') {
    zz_0046754_(param_1);
    zz_0046bd0_(param_1,0);
  }
  return;
}



// ==== 800466dc  zz_00466dc_ ====

void zz_00466dc_(int param_1)

{
  if (*(char *)(param_1 + 0x4a0) != '\x02') {
    zz_00465fc_(param_1);
    zz_00896d0_((int)*(char *)(param_1 + 0x3e4));
  }
  return;
}



// ==== 80046720  zz_0046720_ ====

void zz_0046720_(int param_1)

{
  zz_0046754_(param_1);
  zz_0046d00_(param_1);
  return;
}



// ==== 80046754  zz_0046754_ ====

void zz_0046754_(int param_1)

{
  if ((*(byte *)(param_1 + 0x48a) & 6) == 0) {
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x12e0),(float *)(param_1 + 0x1dbc),
                     (float *)(param_1 + 0x1d54));
  }
  else {
    *(float *)(param_1 + 0x1d58) = FLOAT_80437098;
  }
  return;
}



// ==== 8004679c  zz_004679c_ ====

void zz_004679c_(int param_1,uint param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  float afStack_48 [14];
  char cVar6;
  
  while( true ) {
    uVar5 = param_2;
    cVar6 = (char)uVar5;
    if (cVar6 < '\0') break;
    iVar3 = (int)cVar6;
    if ((*(uint *)(param_1 + 0x1d70) & 1 << iVar3) != 0) {
      if (iVar3 == 1) {
        zz_00457d4_('z',(float *)(param_1 + (char)param_3 * 0x30 + 0x8d4),afStack_48,
                    *(short *)(param_1 + 0x1d68));
        zz_00457d4_('x',afStack_48,afStack_48,*(short *)(param_1 + 0x1d64));
        zz_00457d4_('y',afStack_48,afStack_48,*(short *)(param_1 + 0x1d66));
        iVar3 = (int)cVar6;
        zz_0046dd4_(afStack_48,(float *)(param_1 + iVar3 * 0x30 + 0x8d4),
                    (short *)(param_1 + iVar3 * 6 + 0x18d4),(undefined4 *)(param_1 + 0x1d54),
                    (float *)(param_1 + iVar3 * 0x10 + 0xed4),
                    (float *)(param_1 + iVar3 * 0xc + 0x15d4));
      }
      else {
        iVar2 = param_1 + iVar3 * 0xc;
        zz_0046dd4_((float *)(param_1 + (char)param_3 * 0x30 + 0x8d4),
                    (float *)(param_1 + iVar3 * 0x30 + 0x8d4),
                    (short *)(param_1 + iVar3 * 6 + 0x18d4),(undefined4 *)(iVar2 + 0x12d4),
                    (float *)(param_1 + iVar3 * 0x10 + 0xed4),(float *)(iVar2 + 0x15d4));
      }
    }
    pbVar4 = (byte *)(param_1 + cVar6 * 4 + 0x1994);
    bVar1 = pbVar4[1];
    if (-1 < (char)bVar1) {
      zz_004679c_(param_1,(uint)bVar1,param_3);
    }
    param_2 = (uint)*pbVar4;
    param_3 = uVar5;
  }
  return;
}



// ==== 80046914  zz_0046914_ ====

void zz_0046914_(int param_1,uint param_2,uint param_3)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  char cVar10;
  byte *pbVar11;
  float afStack_48 [13];
  char cVar9;
  
  while( true ) {
    uVar8 = param_2;
    cVar9 = (char)uVar8;
    if (cVar9 < '\0') break;
    iVar4 = (int)cVar9;
    if ((*(uint *)(param_1 + 0x1d70) & 1 << iVar4) == 0) {
      pbVar11 = (byte *)(param_1 + iVar4 * 4 + 0x1994);
      bVar1 = pbVar11[1];
      if (-1 < (char)bVar1) {
        zz_0046914_(param_1,(uint)bVar1,param_3);
      }
      param_2 = (uint)*pbVar11;
      param_3 = uVar8;
    }
    else {
      iVar7 = param_1 + 0x1a14;
      bVar3 = false;
      iVar6 = 0;
      while ((iVar6 < *(char *)(param_1 + 0x1d96) && (!bVar3))) {
        if (iVar4 == *(char *)(iVar7 + 0xc) + -2) {
          bVar3 = true;
        }
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + 0x10;
      }
      iVar4 = (int)cVar9;
      pbVar11 = (byte *)(param_1 + iVar4 * 4 + 0x1994);
      cVar10 = (char)param_3;
      if (bVar3) {
        zz_0047368_(param_1,(int)cVar10,iVar6 + -1,(float *)(param_1 + iVar4 * 0xc + 0x12d4));
        if (-1 < (char)pbVar11[1]) {
          zz_0046914_(param_1,(uint)pbVar11[1],param_3);
        }
        bVar1 = *pbVar11;
        pbVar11 = (byte *)(param_1 + (char)bVar1 * 4 + 0x1994);
        bVar2 = pbVar11[1];
        if (-1 < (char)bVar2) {
          zz_0046914_(param_1,(uint)bVar2,uVar8);
        }
        param_2 = (uint)*pbVar11;
        param_3 = (uint)bVar1;
      }
      else {
        pcVar5 = (char *)(param_1 + 0x1a94);
        bVar3 = false;
        iVar6 = 0;
        while ((iVar6 < *(char *)(param_1 + 0x1d97) && (!bVar3))) {
          if (*pcVar5 == iVar4) {
            bVar3 = true;
          }
          iVar6 = iVar6 + 1;
          pcVar5 = pcVar5 + 4;
        }
        if (bVar3) {
          zz_004784c_(param_1,(int)cVar10,iVar6 + -1,(float *)(param_1 + iVar4 * 0xc + 0x12d4));
        }
        else if (cVar9 == '\x01') {
          zz_00457d4_('z',(float *)(param_1 + cVar10 * 0x30 + 0x8d4),afStack_48,
                      *(short *)(param_1 + 0x1d68));
          zz_00457d4_('x',afStack_48,afStack_48,*(short *)(param_1 + 0x1d64));
          zz_00457d4_('y',afStack_48,afStack_48,*(short *)(param_1 + 0x1d66));
          zz_0046dd4_(afStack_48,(float *)(param_1 + 0x904),(short *)(param_1 + 0x18da),
                      (undefined4 *)(param_1 + 0x1d54),(float *)(param_1 + 0xee4),
                      (float *)(param_1 + 0x15e0));
        }
        else {
          iVar6 = param_1 + iVar4 * 0xc;
          zz_0046dd4_((float *)(param_1 + cVar10 * 0x30 + 0x8d4),
                      (float *)(param_1 + iVar4 * 0x30 + 0x8d4),
                      (short *)(param_1 + iVar4 * 6 + 0x18d4),(undefined4 *)(iVar6 + 0x12d4),
                      (float *)(param_1 + iVar4 * 0x10 + 0xed4),(float *)(iVar6 + 0x15d4));
        }
        if (-1 < (char)pbVar11[1]) {
          zz_0046914_(param_1,(uint)pbVar11[1],param_3);
        }
        param_2 = (uint)*pbVar11;
        param_3 = uVar8;
      }
    }
  }
  return;
}



// ==== 80046bd0  zz_0046bd0_ ====

void zz_0046bd0_(int param_1,int param_2)

{
  float *pfVar1;
  float afStack_48 [15];
  
  pfVar1 = (float *)(param_1 + 0x8d4);
  gnt4_PSMTXIdentity_bl(pfVar1);
  zz_020b4ac_((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
              (double)*(float *)(param_1 + 0x28),pfVar1,pfVar1);
  if (*(char *)(param_1 + 0x4a1) == '\0') {
    if (*(short *)(param_1 + 0x6b8) != 0) {
      FUN_80045838(pfVar1,pfVar1,*(short *)(param_1 + 0x70),
                   *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x6b8) * 0x400,
                   *(short *)(param_1 + 0x74));
      goto LAB_80046c6c;
    }
  }
  FUN_80045838(pfVar1,pfVar1,*(short *)(param_1 + 0x70),*(short *)(param_1 + 0x72),
               *(short *)(param_1 + 0x74));
LAB_80046c6c:
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                     (double)*(float *)(param_1 + 0x60),afStack_48);
  gnt4_PSMTXConcat_bl(pfVar1,afStack_48,pfVar1);
  gnt4_PSMTXCopy_bl(pfVar1,(float *)(param_1 + 0x114));
  gnt4_PSMTXCopy_bl(pfVar1,(float *)(param_1 + 0x1aa4));
  *(float *)(param_1 + 0x1ac0) = *(float *)(param_1 + 0x1ac0) + *(float *)(param_1 + 0x6d0);
  if (param_2 == 0) {
    zz_004679c_(param_1,(uint)*(byte *)(param_1 + 0x1994),0);
  }
  else {
    zz_0046914_(param_1,(uint)*(byte *)(param_1 + 0x1994),0);
  }
  return;
}



// ==== 80046d00  zz_0046d00_ ====

void zz_0046d00_(int param_1)

{
  float *pfVar1;
  float afStack_38 [12];
  
  pfVar1 = (float *)(param_1 + 0x8d4);
  gnt4_PSMTXIdentity_bl(pfVar1);
  zz_020b4ac_((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
              (double)*(float *)(param_1 + 0x28),pfVar1,pfVar1);
  FUN_80045838(pfVar1,pfVar1,*(short *)(param_1 + 0x70),*(short *)(param_1 + 0x72),
               *(short *)(param_1 + 0x74));
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                     (double)*(float *)(param_1 + 0x60),afStack_38);
  gnt4_PSMTXConcat_bl(pfVar1,afStack_38,pfVar1);
  zz_0046dd4_(pfVar1,pfVar1,(short *)(param_1 + 0x18d4),(undefined4 *)(param_1 + 0x12d4),
              (float *)(param_1 + 0xed4),(float *)(param_1 + 0x15d4));
  gnt4_PSMTXCopy_bl(pfVar1,(float *)(param_1 + 0x114));
  gnt4_PSMTXCopy_bl(pfVar1,(float *)(param_1 + 0x1aa4));
  zz_004679c_(param_1,(uint)*(byte *)(param_1 + 0x1994),0);
  return;
}



// ==== 80046dd4  zz_0046dd4_ ====

void zz_0046dd4_(float *param_1,float *param_2,short *param_3,undefined4 *param_4,float *param_5,
                float *param_6)

{
  float afStack_48 [3];
  undefined4 local_3c;
  undefined4 local_2c;
  undefined4 local_1c;
  
  gnt4_PSMTXQuat_bl(afStack_48,param_5);
  local_3c = *param_4;
  local_2c = param_4[1];
  local_1c = param_4[2];
  gnt4_PSMTXConcat_bl(param_1,afStack_48,param_2);
  FUN_80045838(param_2,param_2,*param_3,param_3[1],param_3[2]);
  gnt4_PSMTXScale_bl((double)*param_6,(double)param_6[1],(double)param_6[2],afStack_48);
  gnt4_PSMTXConcat_bl(param_2,afStack_48,param_2);
  return;
}



// ==== 80046e7c  zz_0046e7c_ ====

void zz_0046e7c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x1d96) = 0;
  *(undefined1 *)(param_1 + 0x1d97) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x20000000) == 0) {
    (*(code *)(&PTR_FUN_802d0d60)[*(byte *)(param_1 + 0x1d98) & 0xf])
              (param_1,*(int *)(param_1 + 0x4b0) + 0x22,param_1 + 0x1a14,param_1 + 0x1a94);
  }
  else {
    zz_0046ef4_(param_1);
  }
  return;
}



// ==== 80046ef4  zz_0046ef4_ ====

void zz_0046ef4_(int param_1)

{
  *(float *)(param_1 + 0x1d60) = *(float *)(param_1 + 0x1d60) * FLOAT_8043709c;
  return;
}



// ==== 80046f08  FUN_80046f08 ====

/* WARNING: Removing unreachable block (ram,0x80047148) */
/* WARNING: Removing unreachable block (ram,0x80047140) */
/* WARNING: Removing unreachable block (ram,0x80047138) */
/* WARNING: Removing unreachable block (ram,0x80047130) */
/* WARNING: Removing unreachable block (ram,0x80046f30) */
/* WARNING: Removing unreachable block (ram,0x80046f28) */
/* WARNING: Removing unreachable block (ram,0x80046f20) */
/* WARNING: Removing unreachable block (ram,0x80046f18) */

void FUN_80046f08(int param_1,char *param_2,float *param_3,char *param_4)

{
  float fVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float local_78;
  float local_74;
  float local_70;
  undefined4 local_68;
  uint uStack_64;
  
  local_68 = 0x43300000;
  uStack_64 = *(byte *)(param_1 + 0x1d99) & 0xf ^ 0x80000000;
  dVar5 = (double)*(float *)(param_1 + 0x8f0);
  iVar2 = 0;
  dVar8 = (double)*(float *)(param_1 + 0x670);
  dVar7 = (double)FLOAT_804370a0;
  dVar6 = (double)(FLOAT_804370a4 *
                   (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_804370b8) *
                  *(float *)(param_1 + 0xb4));
  for (; (iVar2 < 4 && (*param_2 != -1)); param_2 = param_2 + 8) {
    if (((int)*(char *)(param_1 + 0x1d99) & 1 << iVar2 + 6) == 0) {
      local_78 = *(float *)(param_1 + *param_2 * 0x30 + 0x8e0);
      local_74 = *(float *)(param_1 + *param_2 * 0x30 + 0x8f0);
      local_70 = *(float *)(param_1 + *param_2 * 0x30 + 0x900);
      if ((double)(float)((double)(float)((double)local_74 - dVar8) - dVar5) <= dVar6) {
        dVar3 = FUN_8003d6e4(dVar8,param_1,&local_78);
        dVar4 = (double)((float)(dVar8 + dVar3) - local_74);
        if (-(double)*(float *)(param_1 + 0x674) <= dVar4) {
          if ((*(char *)(param_1 + 0x1d96) == '\0') || (dVar4 < dVar7)) {
            dVar7 = dVar4;
          }
          *param_3 = local_78;
          param_3[1] = (float)(dVar8 + dVar3);
          param_3[2] = local_70;
          *(char *)(param_3 + 3) = *param_2;
          *(char *)((int)param_3 + 0xd) = param_2[1];
          *(char *)((int)param_3 + 0xe) = param_2[2];
          *(char *)((int)param_3 + 0xf) = param_2[3];
          param_3 = param_3 + 4;
          *(char *)(param_1 + 0x1d96) = *(char *)(param_1 + 0x1d96) + '\x01';
          if (((int)*(char *)(param_1 + 0x1d99) & 1 << iVar2 + 4) == 0) {
            *param_4 = *param_2;
            param_4[1] = param_2[4];
            param_4[2] = param_2[5];
            param_4 = param_4 + 4;
            *(char *)(param_1 + 0x1d97) = *(char *)(param_1 + 0x1d97) + '\x01';
          }
        }
      }
    }
    iVar2 = iVar2 + 1;
  }
  if (dVar7 < -(double)*(float *)(param_1 + 0x674)) {
    dVar7 = -(double)(float)((double)*(float *)(param_1 + 0x674) * (double)FLOAT_804370a8);
  }
  fVar1 = (FLOAT_804370ac * *(float *)(param_1 + 0x1d60) +
          (float)(dVar7 / (double)*(float *)(param_1 + 0xb4))) * FLOAT_804370b0;
  *(float *)(param_1 + 0x1d60) = fVar1;
  *(float *)(param_1 + 0x1d58) = *(float *)(param_1 + 0x1d58) + fVar1;
  return;
}



// ==== 80047164  FUN_80047164 ====

/* WARNING: Removing unreachable block (ram,0x80047328) */
/* WARNING: Removing unreachable block (ram,0x80047320) */
/* WARNING: Removing unreachable block (ram,0x8004717c) */
/* WARNING: Removing unreachable block (ram,0x80047174) */

void FUN_80047164(int param_1,char *param_2,float *param_3,char *param_4)

{
  int iVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float local_58;
  float local_54;
  float local_50;
  undefined4 local_48;
  uint uStack_44;
  
  dVar4 = (double)*(float *)(param_1 + 0x670);
  local_48 = 0x43300000;
  uStack_44 = *(byte *)(param_1 + 0x1d99) & 0xf ^ 0x80000000;
  iVar1 = 0;
  dVar3 = (double)(FLOAT_804370a4 *
                   (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_804370b8) +
                  (float)((double)*(float *)(param_1 + 0x24) + dVar4));
  for (; (iVar1 < 4 && (*param_2 != -1)); param_2 = param_2 + 8) {
    if (((int)*(char *)(param_1 + 0x1d99) & 1 << iVar1 + 6) == 0) {
      local_58 = *(float *)(param_1 + *param_2 * 0x30 + 0x8e0);
      local_54 = *(float *)(param_1 + *param_2 * 0x30 + 0x8f0);
      local_50 = *(float *)(param_1 + *param_2 * 0x30 + 0x900);
      if ((double)local_54 <= dVar3) {
        dVar2 = FUN_8003d6e4(dVar4,param_1,&local_58);
        if (local_54 <= (float)(dVar4 + dVar2)) {
          *param_3 = local_58;
          param_3[1] = (float)(dVar4 + dVar2);
          param_3[2] = local_50;
          *(char *)(param_3 + 3) = *param_2;
          *(char *)((int)param_3 + 0xd) = param_2[1];
          *(char *)((int)param_3 + 0xe) = param_2[2];
          *(char *)((int)param_3 + 0xf) = param_2[3];
          param_3 = param_3 + 4;
          *(char *)(param_1 + 0x1d96) = *(char *)(param_1 + 0x1d96) + '\x01';
          if (((int)*(char *)(param_1 + 0x1d99) & 1 << iVar1 + 4) == 0) {
            *param_4 = *param_2;
            param_4[1] = param_2[4];
            param_4[2] = param_2[5];
            param_4 = param_4 + 4;
            *(char *)(param_1 + 0x1d97) = *(char *)(param_1 + 0x1d97) + '\x01';
          }
        }
      }
    }
    iVar1 = iVar1 + 1;
  }
  *(float *)(param_1 + 0x1d60) = *(float *)(param_1 + 0x1d60) * FLOAT_8043709c;
  *(float *)(param_1 + 0x1d58) = *(float *)(param_1 + 0x1d58) + *(float *)(param_1 + 0x1d60);
  return;
}



// ==== 80047368  zz_0047368_ ====

/* WARNING: Removing unreachable block (ram,0x80047830) */
/* WARNING: Removing unreachable block (ram,0x80047828) */
/* WARNING: Removing unreachable block (ram,0x80047380) */
/* WARNING: Removing unreachable block (ram,0x80047378) */

void zz_0047368_(int param_1,int param_2,int param_3,float *param_4)

{
  float fVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  float *pfVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float afStack_74 [3];
  float local_68;
  float local_58;
  float local_48;
  
  pfVar6 = (float *)(param_1 + param_3 * 0x10 + 0x1a14);
  local_a4 = *param_4;
  local_a0 = param_4[1];
  local_9c = param_4[2];
  pfVar5 = (float *)(param_1 + (*(char *)(pfVar6 + 3) + -2) * 0x30 + 0x8d4);
  fVar4 = param_4[3];
  fVar3 = param_4[4];
  fVar1 = param_4[5];
  local_80 = pfVar5[3];
  local_7c = pfVar5[7];
  local_78 = pfVar5[0xb];
  local_8c = pfVar5[0xf];
  local_88 = pfVar5[0x13];
  local_84 = pfVar5[0x17];
  local_98 = pfVar5[0x1b];
  local_94 = pfVar5[0x1f];
  local_90 = pfVar5[0x23];
  dVar8 = gnt4_PSVECSquareDistance_bl(&local_80,&local_8c);
  if ((double)FLOAT_804370a0 < dVar8) {
    dVar9 = 1.0 / SQRT(dVar8);
    dVar9 = DOUBLE_804370c0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_804370c8);
    dVar9 = DOUBLE_804370c0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_804370c8);
    dVar8 = (double)(float)(dVar8 * DOUBLE_804370c0 * dVar9 *
                                    -(dVar8 * dVar9 * dVar9 - DOUBLE_804370c8));
  }
  dVar9 = gnt4_PSVECSquareDistance_bl(&local_8c,&local_98);
  if ((double)FLOAT_804370a0 < dVar9) {
    dVar10 = 1.0 / SQRT(dVar9);
    dVar10 = DOUBLE_804370c0 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_804370c8);
    dVar10 = DOUBLE_804370c0 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_804370c8);
    dVar9 = (double)(float)(dVar9 * DOUBLE_804370c0 * dVar10 *
                                    -(dVar9 * dVar10 * dVar10 - DOUBLE_804370c8));
  }
  gnt4_PSMTXMultVec_bl((float *)(param_1 + param_2 * 0x30 + 0x8d4),&local_a4,&local_a4);
  pfVar5[3] = local_a4;
  pfVar5[7] = local_a0;
  pfVar5[0xb] = local_9c;
  gnt4_PSVECSubtract_bl(pfVar6,&local_a4,&local_80);
  FUN_80045918(pfVar5,&local_80,(int)*(char *)((int)pfVar6 + 0xd),(int)*(char *)((int)pfVar6 + 0xe))
  ;
  dVar10 = gnt4_PSVECMag_bl(&local_80);
  dVar7 = (double)(FLOAT_804370d0 * (float)(dVar8 + dVar9));
  if (dVar7 < dVar10) {
    dVar10 = dVar7;
  }
  dVar7 = (double)FLOAT_804370d4;
  dVar11 = (double)((((float)(dVar10 * dVar10) + (float)(dVar8 * dVar8)) - (float)(dVar9 * dVar9)) /
                   (float)((double)(float)((double)FLOAT_804370a4 * dVar10) * dVar8));
  dVar8 = (double)(-(((float)(dVar8 * dVar8) + (float)(dVar9 * dVar9)) - (float)(dVar10 * dVar10)) /
                  (float)((double)(float)((double)FLOAT_804370a4 * dVar8) * dVar9));
  if ((dVar11 <= dVar7) && (dVar7 = dVar11, dVar11 < (double)FLOAT_804370d8)) {
    dVar7 = (double)FLOAT_804370d8;
  }
  dVar9 = (double)FLOAT_804370d4;
  if ((dVar8 <= dVar9) && (dVar9 = dVar8, dVar8 < (double)FLOAT_804370d8)) {
    dVar9 = (double)FLOAT_804370d8;
  }
  if (*(char *)((int)pfVar6 + 0xf) < '\0') {
    dVar8 = -(double)(float)(dVar7 * dVar7 - (double)FLOAT_804370d4);
    if ((double)FLOAT_804370a0 < dVar8) {
      dVar10 = 1.0 / SQRT(dVar8);
      dVar10 = DOUBLE_804370c0 * dVar10 * -(dVar8 * dVar10 * dVar10 - DOUBLE_804370c8);
      dVar10 = DOUBLE_804370c0 * dVar10 * -(dVar8 * dVar10 * dVar10 - DOUBLE_804370c8);
      dVar8 = (double)(float)(dVar8 * DOUBLE_804370c0 * dVar10 *
                                      -(dVar8 * dVar10 * dVar10 - DOUBLE_804370c8));
    }
    dVar10 = -(double)(float)(dVar9 * dVar9 - (double)FLOAT_804370d4);
    if ((double)FLOAT_804370a0 < dVar10) {
      dVar11 = 1.0 / SQRT(dVar10);
      dVar11 = DOUBLE_804370c0 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_804370c8);
      dVar11 = DOUBLE_804370c0 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_804370c8);
      dVar10 = (double)(float)(dVar10 * DOUBLE_804370c0 * dVar11 *
                                        -(dVar10 * dVar11 * dVar11 - DOUBLE_804370c8));
    }
    dVar10 = -dVar10;
    cVar2 = (&DAT_804336a8)[-(int)*(char *)((int)pfVar6 + 0xf)];
  }
  else {
    dVar8 = -(double)(float)(dVar7 * dVar7 - (double)FLOAT_804370d4);
    if ((double)FLOAT_804370a0 < dVar8) {
      dVar10 = 1.0 / SQRT(dVar8);
      dVar10 = DOUBLE_804370c0 * dVar10 * -(dVar8 * dVar10 * dVar10 - DOUBLE_804370c8);
      dVar10 = DOUBLE_804370c0 * dVar10 * -(dVar8 * dVar10 * dVar10 - DOUBLE_804370c8);
      dVar8 = (double)(float)(dVar8 * DOUBLE_804370c0 * dVar10 *
                                      -(dVar8 * dVar10 * dVar10 - DOUBLE_804370c8));
    }
    dVar8 = -dVar8;
    dVar10 = -(double)(float)(dVar9 * dVar9 - (double)FLOAT_804370d4);
    if ((double)FLOAT_804370a0 < dVar10) {
      dVar11 = 1.0 / SQRT(dVar10);
      dVar11 = DOUBLE_804370c0 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_804370c8);
      dVar11 = DOUBLE_804370c0 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_804370c8);
      dVar10 = (double)(float)(dVar10 * DOUBLE_804370c0 * dVar11 *
                                        -(dVar10 * dVar11 * dVar11 - DOUBLE_804370c8));
    }
    cVar2 = (&DAT_804336a8)[*(char *)((int)pfVar6 + 0xf)];
  }
  gnt4_PSMTXRotTrig_bl(dVar8,dVar7,afStack_74,(int)cVar2);
  gnt4_PSMTXConcat_bl(pfVar5,afStack_74,pfVar5);
  gnt4_PSMTXRotTrig_bl(dVar10,dVar9,afStack_74,(int)cVar2);
  local_68 = fVar4;
  local_58 = fVar3;
  local_48 = fVar1;
  gnt4_PSMTXConcat_bl(pfVar5,afStack_74,pfVar5 + 0xc);
  return;
}



// ==== 8004784c  zz_004784c_ ====

void zz_004784c_(int param_1,int param_2,int param_3,float *param_4)

{
  char *pcVar1;
  float *pfVar2;
  float afStack_28 [3];
  float local_1c;
  float local_18;
  float local_14;
  
  pcVar1 = (char *)(param_1 + param_3 * 4 + 0x1a94);
  pfVar2 = (float *)(param_1 + *pcVar1 * 0x30 + 0x8d4);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + param_2 * 0x30 + 0x8d4),param_4,&local_1c);
  pfVar2[3] = local_1c;
  pfVar2[7] = local_18;
  pfVar2[0xb] = local_14;
  zz_003de80_((double)*(float *)(param_1 + 0x670),param_1,&local_1c,afStack_28);
  FUN_80045918(pfVar2,afStack_28,(int)pcVar1[1],(int)pcVar1[2]);
  return;
}



// ==== 80047904  zz_0047904_ ====

void zz_0047904_(int param_1)

{
  double dVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  
  if (((*(char *)(param_1 + 0x741) == '\0') && (*(char *)(param_1 + 0x660) == '\0')) &&
     ((*(byte *)(param_1 + 0x1d98) & 0xf0) != 0x10)) {
    if ((*(char *)(param_1 + 0x18) != '\x01') || ((*(uint *)(param_1 + 0x5e0) & 0x1000000) != 0)) {
      *(undefined2 *)(param_1 + 0x191e) = 0;
      *(undefined2 *)(param_1 + 0x191c) = 0;
    }
    iVar4 = zz_0066580_(param_1);
    fVar2 = FLOAT_804370dc;
    dVar1 = DOUBLE_804370b8;
    sVar3 = (short)iVar4 - *(short *)(param_1 + 0x72);
    if (((sVar3 < 0x5000) && (-0x5000 < sVar3)) && ((*(uint *)(param_1 + 0x5e0) & 3) == 0)) {
      zz_006c728_(param_1,0,0xc,3,2);
      return;
    }
    *(short *)(param_1 + 0x191c) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x191c) ^ 0x80000000) -
                             DOUBLE_804370b8) * FLOAT_804370dc);
    *(short *)(param_1 + 0x191e) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x191e) ^ 0x80000000) -
                             dVar1) * fVar2);
  }
  return;
}



// ==== 80047a2c  zz_0047a2c_ ====

void zz_0047a2c_(int param_1,int param_2)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  
  pfVar1 = (float *)(param_2 + 0x8d4);
  pfVar2 = (float *)(param_1 + 0x8d4);
  for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x1d90); iVar3 = iVar3 + 1) {
    gnt4_PSMTXCopy_bl(pfVar2,pfVar1);
    pfVar2 = pfVar2 + 0xc;
    pfVar1 = pfVar1 + 0xc;
  }
  return;
}



// ==== 80047aa4  FUN_80047aa4 ====

/* WARNING: Removing unreachable block (ram,0x80047bcc) */
/* WARNING: Removing unreachable block (ram,0x80047b9c) */
/* WARNING: Removing unreachable block (ram,0x80047b6c) */

void FUN_80047aa4(int param_1)

{
  byte bVar1;
  float afStack_38 [12];
  
  bVar1 = *(byte *)(param_1 + 0x84);
  if ((bVar1 & 0x40) == 0) {
    if ((bVar1 & 0x20) == 0) {
      gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
    }
    else {
      gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x8c) + 0x114),(float *)(param_1 + 0x114));
    }
  }
  else {
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4)
                      ,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 0x80) == 0) {
      *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
    }
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  }
  if ((bVar1 & 8) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_38,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 4) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_38,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 2) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_38,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 0x10) != 0) {
    gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                       (double)*(float *)(param_1 + 0x60),afStack_38);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  return;
}



// ==== 80047c38  FUN_80047c38 ====

/* WARNING: Removing unreachable block (ram,0x80047d60) */
/* WARNING: Removing unreachable block (ram,0x80047d30) */
/* WARNING: Removing unreachable block (ram,0x80047d00) */

void FUN_80047c38(int param_1)

{
  byte bVar1;
  float afStack_38 [12];
  
  bVar1 = *(byte *)(param_1 + 0x84);
  if ((bVar1 & 0x40) == 0) {
    if ((bVar1 & 0x20) == 0) {
      gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
    }
    else {
      gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x8c) + 0x114),(float *)(param_1 + 0x114));
    }
  }
  else {
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4)
                      ,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 0x80) == 0) {
      *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
    }
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  }
  if ((bVar1 & 4) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_38,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 8) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_38,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 2) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_38,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 0x10) != 0) {
    gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                       (double)*(float *)(param_1 + 0x60),afStack_38);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  return;
}



// ==== 80047dcc  FUN_80047dcc ====

/* WARNING: Removing unreachable block (ram,0x80047ef4) */
/* WARNING: Removing unreachable block (ram,0x80047ec4) */
/* WARNING: Removing unreachable block (ram,0x80047e94) */

void FUN_80047dcc(int param_1)

{
  byte bVar1;
  float afStack_38 [12];
  
  bVar1 = *(byte *)(param_1 + 0x84);
  if ((bVar1 & 0x40) == 0) {
    if ((bVar1 & 0x20) == 0) {
      gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
    }
    else {
      gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x8c) + 0x114),(float *)(param_1 + 0x114));
    }
  }
  else {
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4)
                      ,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 0x80) == 0) {
      *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
    }
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  }
  if ((bVar1 & 8) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_38,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 2) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_38,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 4) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_38,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 0x10) != 0) {
    gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                       (double)*(float *)(param_1 + 0x60),afStack_38);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  return;
}



// ==== 80047f60  FUN_80047f60 ====

/* WARNING: Removing unreachable block (ram,0x80048088) */
/* WARNING: Removing unreachable block (ram,0x80048058) */
/* WARNING: Removing unreachable block (ram,0x80048028) */

void FUN_80047f60(int param_1)

{
  byte bVar1;
  float afStack_38 [12];
  
  bVar1 = *(byte *)(param_1 + 0x84);
  if ((bVar1 & 0x40) == 0) {
    if ((bVar1 & 0x20) == 0) {
      gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
    }
    else {
      gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x8c) + 0x114),(float *)(param_1 + 0x114));
    }
  }
  else {
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4)
                      ,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 0x80) == 0) {
      *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
    }
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  }
  if ((bVar1 & 4) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_38,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 2) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_38,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 8) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_38,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 0x10) != 0) {
    gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                       (double)*(float *)(param_1 + 0x60),afStack_38);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  return;
}



// ==== 800480f4  FUN_800480f4 ====

/* WARNING: Removing unreachable block (ram,0x8004821c) */
/* WARNING: Removing unreachable block (ram,0x800481ec) */
/* WARNING: Removing unreachable block (ram,0x800481bc) */

void FUN_800480f4(int param_1)

{
  byte bVar1;
  float afStack_38 [12];
  
  bVar1 = *(byte *)(param_1 + 0x84);
  if ((bVar1 & 0x40) == 0) {
    if ((bVar1 & 0x20) == 0) {
      gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
    }
    else {
      gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x8c) + 0x114),(float *)(param_1 + 0x114));
    }
  }
  else {
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4)
                      ,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 0x80) == 0) {
      *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
    }
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  }
  if ((bVar1 & 2) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_38,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 4) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_38,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 8) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_804370e0 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_38,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 0x10) != 0) {
    gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                       (double)*(float *)(param_1 + 0x60),afStack_38);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  return;
}



// ==== 80048288  zz_0048288_ ====

void zz_0048288_(int param_1)

{
  byte bVar1;
  bool bVar2;
  double dVar3;
  float local_48;
  float local_44;
  float local_40;
  float afStack_3c [13];
  
  bVar1 = *(byte *)(param_1 + 0x84);
  if ((bVar1 & 0x40) == 0) {
    if ((bVar1 & 0x20) == 0) {
      gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
    }
    else {
      gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x8c) + 0x114),(float *)(param_1 + 0x114));
    }
  }
  else {
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4)
                      ,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 0x80) == 0) {
      *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
    }
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  }
  bVar2 = zz_0045ef4_((float *)(param_1 + 0x114),(int)*(char *)(param_1 + 0x98),param_1 + 0x38,
                      param_1 + 0x9c);
  if (bVar2) {
    local_40 = *(float *)(param_1 + 0x9c);
    local_48 = *(float *)(param_1 + 0xa0);
    if ((local_40 == local_48) && (local_44 = *(float *)(param_1 + 0xa4), local_40 == local_44)) {
      local_48 = FLOAT_804370e4 + local_48;
    }
    else {
      local_44 = *(float *)(param_1 + 0xa4);
      local_40 = *(float *)(param_1 + 0x9c);
    }
    bVar2 = zz_0045ef4_((float *)(param_1 + 0x114),(int)*(char *)(param_1 + 0x98),param_1 + 0x38,
                        &local_48);
    if (bVar2) {
      gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
      dVar3 = (double)FLOAT_804370e8;
      gnt4_PSMTXScale_bl(dVar3,dVar3,dVar3,afStack_3c);
      gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
      *(float *)(param_1 + 0x130) = FLOAT_804370ec;
      return;
    }
  }
  if ((bVar1 & 0x10) != 0) {
    gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                       (double)*(float *)(param_1 + 0x60),afStack_3c);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  }
  return;
}



// ==== 8004844c  zz_004844c_ ====

bool zz_004844c_(float *param_1,float *param_2,int param_3)

{
  char cVar1;
  bool bVar2;
  float afStack_28 [6];
  
  cVar1 = PTR_DAT_80433930[0x28];
  gnt4_PSVECSubtract_bl((float *)(&DAT_803c7698 + cVar1 * 0xf9),param_2,afStack_28);
  bVar2 = zz_0045ef4_(param_1,param_3,afStack_28,&DAT_803c76e0 + cVar1 * 0xf9);
  param_1[3] = *param_2;
  param_1[7] = param_2[1];
  param_1[0xb] = param_2[2];
  return bVar2;
}



// ==== 800484e8  zz_00484e8_ ====

bool zz_00484e8_(float *param_1,float *param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  float afStack_28 [6];
  
  gnt4_PSVECSubtract_bl
            ((float *)(&DAT_803c7698 + (char)PTR_DAT_80433930[0x28] * 0xf9),param_2,afStack_28);
  bVar1 = zz_0045ef4_(param_1,param_4,param_3,afStack_28);
  param_1[3] = *param_2;
  param_1[7] = param_2[1];
  param_1[0xb] = param_2[2];
  return bVar1;
}



// ==== 80048588  zz_0048588_ ====

int zz_0048588_(ushort *param_1,ushort *param_2,undefined4 param_3,uint param_4)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  ushort *puVar4;
  uint uVar5;
  ushort *puVar6;
  uint uVar7;
  
  uVar5 = 0;
  puVar6 = param_2;
  do {
    puVar4 = param_1;
    if (uVar5 == 0) {
      param_4 = (uint)(short)*param_1;
      uVar5 = 0x8000;
      puVar4 = param_1 + 1;
    }
    if ((param_4 & uVar5) == 0) {
      param_1 = puVar4 + 1;
      *puVar6 = *puVar4;
      puVar6 = puVar6 + 1;
    }
    else {
      uVar1 = *puVar4;
      uVar3 = (uint)uVar1;
      param_1 = puVar4 + 1;
      uVar2 = uVar1 >> 0xb;
      if (uVar2 == 0) {
        uVar2 = *param_1;
        param_1 = puVar4 + 2;
      }
      else {
        uVar3 = uVar1 & 0x7ff;
      }
      uVar7 = (uint)uVar2;
      if (uVar3 == 0) {
        if (uVar7 == 0) {
          return (int)puVar6 - (int)param_2;
        }
        do {
          uVar7 = uVar7 - 1;
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        } while (uVar7 != 0);
      }
      else {
        puVar4 = puVar6 + -uVar3;
        do {
          uVar1 = *puVar4;
          uVar7 = uVar7 - 1;
          puVar4 = puVar4 + 1;
          *puVar6 = uVar1;
          puVar6 = puVar6 + 1;
        } while (uVar7 != 0);
      }
    }
    uVar5 = (int)uVar5 >> 1;
  } while( true );
}



// ==== 80048648  zz_0048648_ ====

void zz_0048648_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,int param_14,
                undefined4 param_15,undefined4 param_16)

{
  if (((*(int *)(param_9 + 0x1d88) != 0) && (*(int *)(param_9 + 0x1d8c) != 0)) &&
     ((param_10 != 1 ||
      ((*(char *)(param_9 + 0x578) != '\x01' || (*(char *)(param_9 + 0x1db3) != '\x01')))))) {
    if (((int)*(char *)(param_9 + 0x1d9a) & 1 << param_10) == 0) {
      (*(code *)(&PTR_FUN_802d0d70)[param_14])(param_9,param_10);
      if (param_10 == 1) {
        *(float *)(param_9 + 0x6d8) = FLOAT_804370f0;
        zz_004d08c_(param_9);
      }
    }
    else {
      zz_004a41c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_10
                  ,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 8004871c  FUN_8004871c ====

/* WARNING: Removing unreachable block (ram,0x800487d0) */
/* WARNING: Removing unreachable block (ram,0x8004872c) */

void FUN_8004871c(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,uint param_11
                 ,int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  float fVar1;
  undefined1 *puVar2;
  int iVar3;
  
  puVar2 = (undefined1 *)zz_004d1f4_(param_9,param_11,param_12);
  iVar3 = param_9 + param_10 * 0x40 + 0x1ad4;
  *(char *)(iVar3 + 0x28) = (char)param_11;
  *(char *)(iVar3 + 0x29) = (char)param_12;
  zz_004d244_(param_9,param_10,iVar3,puVar2);
  fVar1 = FLOAT_804370f4;
  *(byte *)(iVar3 + 0x31) = *(byte *)(iVar3 + 0x2a) >> 7;
  *(undefined1 *)(iVar3 + 0x2f) = 0;
  *(float *)(iVar3 + 0x20) = fVar1;
  *(float *)(iVar3 + 0x18) = fVar1;
  *(float *)(iVar3 + 0x1c) = fVar1;
  *(undefined1 *)(iVar3 + 0x36) = 0;
  *(float *)(iVar3 + 0x10) = fVar1;
  *(float *)(iVar3 + 0x14) = (float)param_1;
  *(float *)(iVar3 + 8) = fVar1;
  *(float *)(iVar3 + 0xc) = (float)param_1;
  zz_004a754_((double)*(float *)(iVar3 + 0xc),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,0,0,param_10,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800487ec  FUN_800487ec ====

/* WARNING: Removing unreachable block (ram,0x80048910) */
/* WARNING: Removing unreachable block (ram,0x800487fc) */

void FUN_800487ec(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,uint param_11
                 ,int param_12,int param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  float fVar1;
  double dVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  
  if (param_13 == 0) {
    FUN_8004871c(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,0,param_14,param_15,param_16);
  }
  else {
    iVar4 = param_13;
    FUN_8004b94c(param_9,0,param_10,0);
    puVar3 = (undefined1 *)zz_004d1f4_(param_9,param_11,param_12);
    iVar5 = param_9 + param_10 * 0x40 + 0x1ad4;
    *(char *)(iVar5 + 0x28) = (char)param_11;
    *(char *)(iVar5 + 0x29) = (char)param_12;
    zz_004d244_(param_9,param_10,iVar5,puVar3);
    dVar2 = DOUBLE_804370f8;
    *(byte *)(iVar5 + 0x31) = *(byte *)(iVar5 + 0x2a) >> 7;
    dVar6 = (double)FLOAT_804370f0;
    *(undefined1 *)(iVar5 + 0x2f) = 1;
    fVar1 = FLOAT_804370f4;
    *(undefined4 *)(iVar5 + 0x1c) = *(undefined4 *)(param_9 + 0x1dc8);
    *(float *)(iVar5 + 0x18) =
         (float)((double)CONCAT44(0x43300000,param_13 + 1U ^ 0x80000000) - dVar2);
    *(float *)(iVar5 + 0x20) =
         (float)(dVar6 - (double)(float)((double)*(float *)(iVar5 + 0x1c) /
                                        (double)*(float *)(iVar5 + 0x18)));
    *(undefined1 *)(iVar5 + 0x36) = 0;
    *(float *)(iVar5 + 0x10) = fVar1;
    *(float *)(iVar5 + 0x14) = (float)param_1;
    *(float *)(iVar5 + 8) = fVar1;
    *(float *)(iVar5 + 0xc) = (float)param_1;
    zz_004a754_((double)*(float *)(iVar5 + 0xc),(double)*(float *)(iVar5 + 0x1c),dVar6,param_4,
                param_5,param_6,param_7,param_8,param_9,0,0,param_10,iVar4,param_14,param_15,
                param_16);
    FUN_8004a8cc((double)*(float *)(iVar5 + 0x20),param_9,param_10);
  }
  return;
}



// ==== 8004892c  FUN_8004892c ====

/* WARNING: Removing unreachable block (ram,0x80048a50) */
/* WARNING: Removing unreachable block (ram,0x8004893c) */

void FUN_8004892c(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,uint param_11
                 ,int param_12,int param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  float fVar1;
  double dVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  
  if (param_13 == 0) {
    FUN_8004871c(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,0,param_14,param_15,param_16);
  }
  else {
    iVar4 = param_13;
    FUN_8004b94c(param_9,0,param_10,0);
    puVar3 = (undefined1 *)zz_004d1f4_(param_9,param_11,param_12);
    iVar5 = param_9 + param_10 * 0x40 + 0x1ad4;
    *(char *)(iVar5 + 0x28) = (char)param_11;
    *(char *)(iVar5 + 0x29) = (char)param_12;
    zz_004d244_(param_9,param_10,iVar5,puVar3);
    dVar2 = DOUBLE_804370f8;
    *(byte *)(iVar5 + 0x31) = *(byte *)(iVar5 + 0x2a) >> 7;
    dVar6 = (double)FLOAT_804370f0;
    *(undefined1 *)(iVar5 + 0x2f) = 2;
    fVar1 = FLOAT_804370f4;
    *(undefined4 *)(iVar5 + 0x1c) = *(undefined4 *)(param_9 + 0x1dc8);
    *(float *)(iVar5 + 0x18) =
         (float)((double)CONCAT44(0x43300000,param_13 + 1U ^ 0x80000000) - dVar2);
    *(float *)(iVar5 + 0x20) =
         (float)(dVar6 - (double)(float)((double)*(float *)(iVar5 + 0x1c) /
                                        (double)*(float *)(iVar5 + 0x18)));
    *(undefined1 *)(iVar5 + 0x36) = 0;
    *(float *)(iVar5 + 0x10) = fVar1;
    *(float *)(iVar5 + 0x14) = (float)param_1;
    *(float *)(iVar5 + 8) = fVar1;
    *(float *)(iVar5 + 0xc) = (float)param_1;
    zz_004a754_((double)*(float *)(iVar5 + 0xc),(double)*(float *)(iVar5 + 0x1c),dVar6,param_4,
                param_5,param_6,param_7,param_8,param_9,0,0,param_10,iVar4,param_14,param_15,
                param_16);
    FUN_8004a8cc((double)*(float *)(iVar5 + 0x20),param_9,param_10);
  }
  return;
}



// ==== 80048a6c  FUN_80048a6c ====

/* WARNING: Removing unreachable block (ram,0x80048bc4) */
/* WARNING: Removing unreachable block (ram,0x80048a7c) */

void FUN_80048a6c(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,uint param_11
                 ,int param_12,int param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  float fVar1;
  double dVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  
  if (param_13 == 0) {
    FUN_8004871c(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,0,param_14,param_15,param_16);
  }
  else {
    iVar5 = param_9 + param_10 * 0x40 + 0x1ad4;
    *(float *)(iVar5 + 8) = *(float *)(iVar5 + 8) + *(float *)(param_9 + 0x1dc8);
    *(float *)(iVar5 + 0xc) = *(float *)(iVar5 + 0xc) + *(float *)(param_9 + 0x1dc8);
    uVar6 = FUN_8004b94c(param_9,0,param_10,1);
    uVar4 = 1;
    zz_004a830_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,1,param_10,1
                ,param_14,param_15,param_16);
    puVar3 = (undefined1 *)zz_004d1f4_(param_9,param_11,param_12);
    *(char *)(iVar5 + 0x28) = (char)param_11;
    *(char *)(iVar5 + 0x29) = (char)param_12;
    zz_004d244_(param_9,param_10,iVar5,puVar3);
    dVar2 = DOUBLE_804370f8;
    *(byte *)(iVar5 + 0x31) = *(byte *)(iVar5 + 0x2a) >> 7;
    dVar7 = (double)FLOAT_804370f0;
    *(undefined1 *)(iVar5 + 0x2f) = 3;
    fVar1 = FLOAT_804370f4;
    *(undefined4 *)(iVar5 + 0x1c) = *(undefined4 *)(param_9 + 0x1dc8);
    *(float *)(iVar5 + 0x18) =
         (float)((double)CONCAT44(0x43300000,param_13 + 1U ^ 0x80000000) - dVar2);
    *(float *)(iVar5 + 0x20) =
         (float)(dVar7 - (double)(float)((double)*(float *)(iVar5 + 0x1c) /
                                        (double)*(float *)(iVar5 + 0x18)));
    *(undefined1 *)(iVar5 + 0x36) = 0;
    *(float *)(iVar5 + 0x10) = fVar1;
    *(float *)(iVar5 + 0x14) = (float)param_1;
    *(float *)(iVar5 + 8) = fVar1;
    *(float *)(iVar5 + 0xc) = (float)param_1;
    zz_004a754_((double)*(float *)(iVar5 + 8),(double)*(float *)(iVar5 + 0x1c),dVar7,param_4,param_5
                ,param_6,param_7,param_8,param_9,0,0,param_10,uVar4,param_14,param_15,param_16);
    FUN_8004a8cc((double)*(float *)(iVar5 + 0x20),param_9,param_10);
  }
  return;
}



// ==== 80048be0  FUN_80048be0 ====

/* WARNING: Removing unreachable block (ram,0x80048d38) */
/* WARNING: Removing unreachable block (ram,0x80048bf0) */

void FUN_80048be0(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,uint param_11
                 ,int param_12,int param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  float fVar1;
  double dVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  
  if (param_13 == 0) {
    FUN_8004871c(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,0,param_14,param_15,param_16);
  }
  else {
    iVar5 = param_9 + param_10 * 0x40 + 0x1ad4;
    *(float *)(iVar5 + 8) = *(float *)(iVar5 + 8) + *(float *)(param_9 + 0x1dc8);
    *(float *)(iVar5 + 0xc) = *(float *)(iVar5 + 0xc) + *(float *)(param_9 + 0x1dc8);
    uVar6 = FUN_8004b94c(param_9,0,param_10,1);
    uVar4 = 1;
    zz_004a830_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,1,param_10,1
                ,param_14,param_15,param_16);
    puVar3 = (undefined1 *)zz_004d1f4_(param_9,param_11,param_12);
    *(char *)(iVar5 + 0x28) = (char)param_11;
    *(char *)(iVar5 + 0x29) = (char)param_12;
    zz_004d244_(param_9,param_10,iVar5,puVar3);
    dVar2 = DOUBLE_804370f8;
    *(byte *)(iVar5 + 0x31) = *(byte *)(iVar5 + 0x2a) >> 7;
    dVar7 = (double)FLOAT_804370f0;
    *(undefined1 *)(iVar5 + 0x2f) = 4;
    fVar1 = FLOAT_804370f4;
    *(undefined4 *)(iVar5 + 0x1c) = *(undefined4 *)(param_9 + 0x1dc8);
    *(float *)(iVar5 + 0x18) =
         (float)((double)CONCAT44(0x43300000,param_13 + 1U ^ 0x80000000) - dVar2);
    *(float *)(iVar5 + 0x20) =
         (float)(dVar7 - (double)(float)((double)*(float *)(iVar5 + 0x1c) /
                                        (double)*(float *)(iVar5 + 0x18)));
    *(undefined1 *)(iVar5 + 0x36) = 0;
    *(float *)(iVar5 + 0x10) = fVar1;
    *(float *)(iVar5 + 0x14) = (float)param_1;
    *(float *)(iVar5 + 8) = fVar1;
    *(float *)(iVar5 + 0xc) = (float)param_1;
    zz_004a754_((double)*(float *)(iVar5 + 0xc),(double)*(float *)(iVar5 + 0x1c),dVar7,param_4,
                param_5,param_6,param_7,param_8,param_9,0,0,param_10,uVar4,param_14,param_15,
                param_16);
    FUN_8004a8cc((double)*(float *)(iVar5 + 0x20),param_9,param_10);
  }
  return;
}



// ==== 80048d54  zz_0048d54_ ====

void zz_0048d54_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,uint param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  double dVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  undefined8 local_28;
  
  iVar4 = 0;
  *(undefined1 *)(param_9 + 0x1d9a) = 0;
  iVar5 = param_9;
  do {
    if ((iVar4 != 1) && (((int)*(char *)(param_9 + 0x579) & 1 << iVar4) != 0)) {
      if (param_10 == 0) {
        *(undefined1 *)(param_9 + 0x1d9a) = 0;
        if (*(char *)(param_9 + 0x1b43) != '\0') {
          FUN_8004871c((double)*(float *)(param_9 + 0x1b20),param_2,param_3,param_4,param_5,param_6,
                       param_7,param_8,param_9,iVar4,(int)*(char *)(param_9 + 0x1b3c),
                       (int)*(char *)(param_9 + 0x1b3d),0,param_14,param_15,param_16);
          return;
        }
        zz_0048648_((double)*(float *)(param_9 + 0x1b20),param_2,param_3,param_4,param_5,param_6,
                    param_7,param_8,param_9,iVar4,(int)*(char *)(param_9 + 0x1b3c),
                    (int)*(char *)(param_9 + 0x1b3d),
                    (int)(*(float *)(param_9 + 0x1b2c) - *(float *)(param_9 + 0x1b30)),0,param_15,
                    param_16);
        return;
      }
      *(byte *)(param_9 + 0x1d9a) = *(byte *)(param_9 + 0x1d9a) | (byte)(1 << iVar4);
      puVar3 = (undefined1 *)
               zz_004d1f4_(param_9,(int)*(char *)(param_9 + 0x1b3c),(int)*(char *)(param_9 + 0x1b3d)
                          );
      fVar1 = FLOAT_804370f4;
      *(undefined1 *)(iVar5 + 0x1c05) = *(undefined1 *)(param_9 + 0x1b45);
      *(undefined1 *)(iVar5 + 0x1bfc) = *(undefined1 *)(param_9 + 0x1b3c);
      *(undefined1 *)(iVar5 + 0x1bfd) = *(undefined1 *)(param_9 + 0x1b3d);
      *(undefined1 *)(iVar5 + 0x1c04) = *(undefined1 *)(param_9 + 0x1b44);
      *(float *)(iVar5 + 0x1be4) = fVar1;
      *(undefined4 *)(iVar5 + 0x1be8) = *(undefined4 *)(param_9 + 0x1b28);
      *(float *)(iVar5 + 0x1bdc) = fVar1;
      *(undefined4 *)(iVar5 + 0x1be0) = *(undefined4 *)(param_9 + 0x1b20);
      if (*(char *)(param_9 + 0x1b43) != '\0') {
        param_3 = (double)*(float *)(param_9 + 0x1b2c);
        local_28 = (double)CONCAT44(0x43300000,param_10 ^ 0x80000000);
        param_2 = (double)(float)(param_3 - (double)*(float *)(param_9 + 0x1b30));
        if ((double)(float)(local_28 - DOUBLE_804370f8) < param_2) {
          param_10 = (uint)((double)FLOAT_804370f0 + param_2);
        }
      }
      zz_004d244_(param_9,iVar4,iVar5 + 0x1bd4,puVar3);
      zz_004a754_((double)*(float *)(iVar5 + 0x1be0),param_2,param_3,param_4,param_5,param_6,param_7
                  ,param_8,param_9,1,1,iVar4,param_13,param_14,param_15,param_16);
      dVar2 = DOUBLE_804370f8;
      fVar1 = FLOAT_804370f4;
      local_28 = (double)CONCAT44(0x43300000,param_10 + 1 ^ 0x80000000);
      *(undefined1 *)(iVar5 + 0x1b03) = 5;
      param_3 = (double)*(float *)(param_9 + 0x1dc8);
      *(float *)(iVar5 + 0x1af0) = *(float *)(param_9 + 0x1dc8);
      *(float *)(iVar5 + 0x1aec) = (float)(local_28 - dVar2);
      param_2 = (double)*(float *)(iVar5 + 0x1af0);
      *(float *)(iVar5 + 0x1af4) = (float)(param_2 / (double)*(float *)(iVar5 + 0x1aec));
      *(undefined1 *)(iVar5 + 0x1b0a) = 0;
      *(float *)(iVar5 + 0x1ae4) = fVar1;
      *(float *)(iVar5 + 0x1ae8) = fVar1;
      *(float *)(iVar5 + 0x1adc) = fVar1;
      *(float *)(iVar5 + 0x1ae0) = fVar1;
      *(undefined1 *)(iVar5 + 0x1b0b) = 0xff;
      FUN_8004a8cc((double)*(float *)(iVar5 + 0x1af4),param_9,iVar4);
    }
    iVar4 = iVar4 + 1;
    iVar5 = iVar5 + 0x40;
  } while (iVar4 < 4);
  return;
}



// ==== 80048f9c  FUN_80048f9c ====

/* WARNING: Removing unreachable block (ram,0x80049160) */
/* WARNING: Removing unreachable block (ram,0x80048fac) */

void FUN_80048f9c(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,int param_11)

{
  float fVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  float *pfVar5;
  undefined4 *in_r10;
  double dVar6;
  char local_38;
  char local_37 [3];
  char local_34;
  char local_33 [3];
  float local_30 [2];
  undefined4 local_28;
  uint uStack_24;
  
  if (param_11 == 0) {
    pfVar5 = local_30;
    zz_0049184_(param_9,param_10,&local_34,&local_38,local_33,local_37,pfVar5);
    fVar1 = FLOAT_804370f4;
    iVar4 = param_9 + param_10 * 0x40 + 0x1ad4;
    *(char *)(iVar4 + 0x28) = local_34;
    *(char *)(iVar4 + 0x29) = local_38;
    *(undefined1 *)(iVar4 + 0x2f) = 0;
    *(float *)(iVar4 + 0x20) = fVar1;
    *(float *)(iVar4 + 0x18) = fVar1;
    *(float *)(iVar4 + 0x1c) = fVar1;
    *(undefined1 *)(iVar4 + 0x36) = 1;
    *(float *)(iVar4 + 0x10) = fVar1;
    *(float *)(iVar4 + 0x14) = (float)param_1;
    *(float *)(iVar4 + 8) = fVar1;
    *(float *)(iVar4 + 0xc) = (float)param_1;
    zz_0049b98_((double)local_30[0],param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                param_10,(int)local_34,(int)local_38,(int)local_33[0],(int)local_37[0],pfVar5,in_r10
               );
  }
  else {
    FUN_8004b94c(param_9,0,param_10,0);
    zz_0049184_(param_9,param_10,&local_34,&local_38,local_33,local_37,local_30);
    iVar4 = param_9 + param_10 * 0x40 + 0x1ad4;
    uStack_24 = param_11 + 1U ^ 0x80000000;
    *(char *)(iVar4 + 0x28) = local_34;
    dVar3 = DOUBLE_804370f8;
    dVar6 = (double)FLOAT_804370f0;
    *(char *)(iVar4 + 0x29) = local_38;
    fVar2 = FLOAT_804370f4;
    local_28 = 0x43300000;
    *(undefined1 *)(iVar4 + 0x2f) = 6;
    fVar1 = *(float *)(param_9 + 0x1dc8);
    *(float *)(iVar4 + 0x1c) = fVar1;
    *(float *)(iVar4 + 0x18) = (float)((double)CONCAT44(0x43300000,uStack_24) - dVar3);
    *(float *)(iVar4 + 0x20) =
         (float)(dVar6 - (double)(float)((double)*(float *)(iVar4 + 0x1c) /
                                        (double)*(float *)(iVar4 + 0x18)));
    *(undefined1 *)(iVar4 + 0x36) = 1;
    *(float *)(iVar4 + 0x10) = fVar2;
    *(float *)(iVar4 + 0x14) = (float)param_1;
    *(float *)(iVar4 + 8) = fVar2;
    *(float *)(iVar4 + 0xc) = (float)param_1;
    FUN_80049210((double)local_30[0],(double)*(float *)(iVar4 + 0x1c),dVar6,(double)fVar1,param_5,
                 param_6,param_7,param_8,param_9,0,param_10,(int)local_34,(int)local_38,
                 (int)local_33[0],(undefined4 *)(int)local_37[0],in_r10);
    FUN_8004a8cc((double)*(float *)(iVar4 + 0x20),param_9,param_10);
  }
  return;
}



// ==== 80049184  zz_0049184_ ====

/* WARNING: Removing unreachable block (ram,0x80049188) */

void zz_0049184_(int param_1,int param_2,undefined1 *param_3,undefined1 *param_4,undefined1 *param_5
                ,undefined1 *param_6,float *param_7)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 + 0x1de4;
  *param_7 = (float)(double)((longlong)(double)*(short *)(param_1 + 0x1dfc) * 0x3ff0000000000000);
  if (*(short *)(param_1 + 0x1dfc) < 0) {
    iVar1 = iVar2 + param_2 * 6;
    *param_7 = -(*param_7 / FLOAT_80437100);
    *param_5 = *(undefined1 *)(iVar1 + 2);
    *param_6 = *(undefined1 *)(iVar1 + 5);
  }
  else {
    *param_7 = *param_7 / FLOAT_80437100;
    *param_5 = *(undefined1 *)(iVar2 + param_2 * 6);
    *param_6 = *(undefined1 *)(iVar2 + param_2 * 6 + 3);
  }
  iVar2 = iVar2 + param_2 * 6;
  *param_3 = *(undefined1 *)(iVar2 + 1);
  *param_4 = *(undefined1 *)(iVar2 + 4);
  return;
}



// ==== 80049210  FUN_80049210 ====

/* WARNING: Removing unreachable block (ram,0x800496bc) */
/* WARNING: Removing unreachable block (ram,0x800496b4) */
/* WARNING: Removing unreachable block (ram,0x80049228) */
/* WARNING: Removing unreachable block (ram,0x80049220) */

void FUN_80049210(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                 uint param_12,int param_13,uint param_14,undefined4 *param_15,undefined4 *param_16)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined *puVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  float *pfVar14;
  int iVar15;
  uint uVar16;
  double dVar17;
  int local_88;
  undefined4 *local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float afStack_60 [3];
  float afStack_54 [4];
  
  iVar5 = param_9 + param_11 * 0x40;
  *(undefined4 *)(iVar5 + 0x1bdc) = *(undefined4 *)(iVar5 + 0x1adc);
  *(undefined4 *)(iVar5 + 0x1be0) = *(undefined4 *)(iVar5 + 0x1ae0);
  *(undefined4 *)(iVar5 + 0x1be4) = *(undefined4 *)(iVar5 + 0x1ae4);
  *(undefined4 *)(iVar5 + 0x1be8) = *(undefined4 *)(iVar5 + 0x1ae8);
  iVar3 = param_13;
  uVar4 = param_14;
  puVar8 = param_15;
  puVar1 = (undefined1 *)zz_004d1f4_(param_9,param_14,(int)param_15);
  *(char *)(iVar5 + 0x1bfc) = (char)param_14;
  *(char *)(iVar5 + 0x1bfd) = (char)param_15;
  zz_004d244_(param_9,param_11,iVar5 + 0x1bd4,puVar1);
  *(byte *)(iVar5 + 0x1c05) = *(byte *)(iVar5 + 0x1bfe) >> 7;
  zz_004a754_((double)*(float *)(iVar5 + 0x1be0),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,1,param_10,param_11,iVar3,uVar4,puVar8,param_16);
  if (param_11 == 0) {
    iVar3 = param_9 + param_10 * 2;
    DAT_80436168 = *(undefined1 *)(iVar3 + 0x1d74);
    uRam80436169 = *(undefined1 *)(iVar3 + 0x1d75);
  }
  zz_004b8f4_(param_9,param_11,&local_88);
  iVar3 = param_9 + param_10 * 0x200;
  iVar15 = param_9 + param_10 * 0x180;
  puVar10 = &DAT_803b0900;
  uVar4 = (int)local_84 - local_88;
  puVar11 = local_84;
  if (local_88 < (int)local_84) {
    uVar16 = uVar4 >> 1;
    iVar2 = local_88;
    if (uVar16 != 0) {
      do {
        iVar12 = iVar2 + 0x8c;
        iVar13 = iVar2 + 0x8d;
        iVar2 = iVar2 + 2;
        iVar7 = (int)*(char *)(*(int *)(param_9 + 0x4b0) + iVar12);
        iVar12 = iVar7 * 0x10;
        puVar11 = (undefined4 *)(iVar3 + iVar12 + 0xed4);
        iVar7 = iVar7 * 0xc;
        uVar6 = puVar11[1];
        *(undefined4 *)(&DAT_803b0a80 + iVar12) = *puVar11;
        puVar8 = (undefined4 *)(iVar15 + iVar7 + 0x12d4);
        *(undefined4 *)(&DAT_803b0a84 + iVar12) = uVar6;
        uVar6 = puVar11[3];
        *(undefined4 *)(&DAT_803b0a88 + iVar12) = puVar11[2];
        *(undefined4 *)(&DAT_803b0a8c + iVar12) = uVar6;
        uVar6 = puVar8[1];
        *(undefined4 *)(&DAT_803b0900 + iVar7) = *puVar8;
        *(undefined4 *)(&DAT_803b0904 + iVar7) = uVar6;
        *(undefined4 *)(&DAT_803b0908 + iVar7) = puVar8[2];
        iVar7 = (int)*(char *)(*(int *)(param_9 + 0x4b0) + iVar13);
        iVar12 = iVar7 * 0x10;
        puVar8 = (undefined4 *)(iVar3 + iVar12 + 0xed4);
        param_16 = (undefined4 *)(&DAT_803b0a80 + iVar12);
        iVar7 = iVar7 * 0xc;
        uVar6 = puVar8[1];
        *param_16 = *puVar8;
        puVar9 = (undefined4 *)(iVar15 + iVar7 + 0x12d4);
        puVar11 = (undefined4 *)(&DAT_803b0900 + iVar7);
        *(undefined4 *)(&DAT_803b0a84 + iVar12) = uVar6;
        uVar6 = puVar8[3];
        *(undefined4 *)(&DAT_803b0a88 + iVar12) = puVar8[2];
        *(undefined4 *)(&DAT_803b0a8c + iVar12) = uVar6;
        uVar6 = puVar9[1];
        *puVar11 = *puVar9;
        *(undefined4 *)(&DAT_803b0904 + iVar7) = uVar6;
        *(undefined4 *)(&DAT_803b0908 + iVar7) = puVar9[2];
        uVar16 = uVar16 - 1;
      } while (uVar16 != 0);
      uVar4 = uVar4 & 1;
      if (uVar4 == 0) goto LAB_80049494;
    }
    do {
      iVar7 = (int)*(char *)(*(int *)(param_9 + 0x4b0) + iVar2 + 0x8c);
      iVar12 = iVar7 * 0x10;
      puVar8 = (undefined4 *)(iVar3 + iVar12 + 0xed4);
      param_16 = (undefined4 *)(&DAT_803b0a80 + iVar12);
      iVar7 = iVar7 * 0xc;
      uVar6 = puVar8[1];
      *param_16 = *puVar8;
      puVar9 = (undefined4 *)(iVar15 + iVar7 + 0x12d4);
      puVar11 = (undefined4 *)(&DAT_803b0900 + iVar7);
      *(undefined4 *)(&DAT_803b0a84 + iVar12) = uVar6;
      uVar6 = puVar8[3];
      *(undefined4 *)(&DAT_803b0a88 + iVar12) = puVar8[2];
      *(undefined4 *)(&DAT_803b0a8c + iVar12) = uVar6;
      uVar6 = puVar9[1];
      *puVar11 = *puVar9;
      *(undefined4 *)(&DAT_803b0904 + iVar7) = uVar6;
      *(undefined4 *)(&DAT_803b0908 + iVar7) = puVar9[2];
      uVar4 = uVar4 - 1;
      iVar2 = iVar2 + 1;
    } while (uVar4 != 0);
  }
LAB_80049494:
  puVar1 = (undefined1 *)zz_004d1f4_(param_9,param_12,param_13);
  *(char *)(iVar5 + 0x1afc) = (char)param_12;
  *(char *)(iVar5 + 0x1afd) = (char)param_13;
  zz_004d244_(param_9,param_11,iVar5 + 0x1ad4,puVar1);
  *(byte *)(iVar5 + 0x1b05) = *(byte *)(iVar5 + 0x1afe) >> 7;
  zz_004a754_((double)*(float *)(iVar5 + 0x1ae0),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,0,param_10,param_11,puVar11,puVar10,puVar8,param_16);
  dVar17 = (double)(float)((double)FLOAT_804370f0 - param_1);
  iVar5 = local_88;
  do {
    if ((int)local_84 <= iVar5) {
      return;
    }
    iVar7 = (int)*(char *)(*(int *)(param_9 + 0x4b0) + iVar5 + 0x8c);
    gnt4_PSQUATScale_bl(param_1,(float *)(&DAT_803b0900 + iVar7 * 0xc),afStack_54);
    pfVar14 = (float *)(iVar15 + iVar7 * 0xc + 0x12d4);
    gnt4_PSQUATScale_bl(dVar17,pfVar14,afStack_60);
    gnt4_PSVECAdd_bl(afStack_54,afStack_60,pfVar14);
    iVar2 = iVar7 * 0x10;
    local_70 = *(float *)(&DAT_803b0a80 + iVar2);
    iVar12 = iVar3 + iVar2;
    local_6c = *(float *)(&DAT_803b0a84 + iVar2);
    local_68 = *(float *)(&DAT_803b0a88 + iVar2);
    local_64 = *(float *)(&DAT_803b0a8c + iVar2);
    local_80 = *(float *)(iVar12 + 0xed4);
    local_7c = *(float *)(iVar12 + 0xed8);
    local_78 = *(float *)(iVar12 + 0xedc);
    local_74 = *(float *)(iVar12 + 0xee0);
    if ((local_64 + local_74) * (local_64 + local_74) +
        (local_68 + local_78) * (local_68 + local_78) +
        (local_70 + local_80) * (local_70 + local_80) +
        (local_6c + local_7c) * (local_6c + local_7c) <
        (local_64 - local_74) * (local_64 - local_74) +
        (local_68 - local_78) * (local_68 - local_78) +
        (local_70 - local_80) * (local_70 - local_80) +
        (local_6c - local_7c) * (local_6c - local_7c)) {
      local_80 = -local_80;
      local_7c = -local_7c;
      local_78 = -local_78;
      local_74 = -local_74;
    }
    C_QUATSlerp(dVar17,&local_70,&local_80,(float *)(iVar12 + 0xed4));
    iVar2 = 0;
    iVar12 = 2;
    do {
      if (*(char *)(*(int *)(param_9 + 0x4b0) + iVar2 + 0x42) == iVar7) {
        if ((double)FLOAT_80437104 < dVar17) {
          *(undefined1 *)(param_9 + param_10 * 2 + iVar2 + 0x1d74) = (&DAT_80436168)[iVar2];
        }
        break;
      }
      iVar2 = iVar2 + 1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
    iVar5 = iVar5 + 1;
  } while( true );
}



// ==== 800496d8  zz_00496d8_ ====

/* WARNING: Removing unreachable block (ram,0x80049b7c) */
/* WARNING: Removing unreachable block (ram,0x80049b74) */
/* WARNING: Removing unreachable block (ram,0x800496f0) */
/* WARNING: Removing unreachable block (ram,0x800496e8) */

void zz_00496d8_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                undefined4 param_12,undefined4 param_13,uint param_14,undefined4 *param_15,
                undefined4 *param_16)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  float *pfVar11;
  int iVar12;
  uint uVar13;
  undefined8 uVar14;
  double dVar15;
  int local_88;
  int local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float afStack_60 [3];
  float afStack_54 [4];
  
  iVar4 = param_9 + param_11 * 0x40;
  *(undefined4 *)(iVar4 + 0x1bdc) = *(undefined4 *)(iVar4 + 0x1adc);
  *(undefined4 *)(iVar4 + 0x1be0) = *(undefined4 *)(iVar4 + 0x1ae0);
  *(undefined4 *)(iVar4 + 0x1be4) = *(undefined4 *)(iVar4 + 0x1ae4);
  *(undefined4 *)(iVar4 + 0x1be8) = *(undefined4 *)(iVar4 + 0x1ae8);
  if (((int)*(char *)(iVar4 + 0x1bfc) == param_14) &&
     ((undefined4 *)(int)*(char *)(iVar4 + 0x1bfd) == param_15)) {
    zz_004a830_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,
                (char)param_10,param_11,0,param_14,param_15,param_16);
  }
  else {
    uVar3 = param_14;
    puVar7 = param_15;
    puVar1 = (undefined1 *)zz_004d1f4_(param_9,param_14,(int)param_15);
    *(char *)(iVar4 + 0x1bfc) = (char)param_14;
    *(char *)(iVar4 + 0x1bfd) = (char)param_15;
    zz_004d244_(param_9,param_11,iVar4 + 0x1bd4,puVar1);
    *(byte *)(iVar4 + 0x1c05) = *(byte *)(iVar4 + 0x1bfe) >> 7;
    zz_004a754_((double)*(float *)(iVar4 + 0x1be0),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,param_9,1,param_10,param_11,param_13,uVar3,puVar7,param_16);
    param_15 = puVar7;
  }
  if (param_11 == 0) {
    iVar4 = param_9 + param_10 * 2;
    DAT_80436168 = *(undefined1 *)(iVar4 + 0x1d74);
    uRam80436169 = *(undefined1 *)(iVar4 + 0x1d75);
  }
  uVar14 = zz_004b8f4_(param_9,param_11,&local_88);
  iVar4 = param_9 + param_10 * 0x200;
  iVar12 = param_9 + param_10 * 0x180;
  uVar3 = local_84 - local_88;
  if (local_88 < local_84) {
    uVar13 = uVar3 >> 1;
    iVar2 = local_88;
    if (uVar13 != 0) {
      do {
        iVar9 = iVar2 + 0x8c;
        iVar10 = iVar2 + 0x8d;
        iVar2 = iVar2 + 2;
        iVar6 = (int)*(char *)(*(int *)(param_9 + 0x4b0) + iVar9);
        iVar9 = iVar6 * 0x10;
        puVar8 = (undefined4 *)(iVar4 + iVar9 + 0xed4);
        iVar6 = iVar6 * 0xc;
        uVar5 = puVar8[1];
        *(undefined4 *)(&DAT_803b0a80 + iVar9) = *puVar8;
        puVar7 = (undefined4 *)(iVar12 + iVar6 + 0x12d4);
        *(undefined4 *)(&DAT_803b0a84 + iVar9) = uVar5;
        uVar5 = puVar8[3];
        *(undefined4 *)(&DAT_803b0a88 + iVar9) = puVar8[2];
        *(undefined4 *)(&DAT_803b0a8c + iVar9) = uVar5;
        uVar5 = puVar7[1];
        *(undefined4 *)(&DAT_803b0900 + iVar6) = *puVar7;
        *(undefined4 *)(&DAT_803b0904 + iVar6) = uVar5;
        *(undefined4 *)(&DAT_803b0908 + iVar6) = puVar7[2];
        iVar6 = (int)*(char *)(*(int *)(param_9 + 0x4b0) + iVar10);
        iVar9 = iVar6 * 0x10;
        param_15 = (undefined4 *)(iVar4 + iVar9 + 0xed4);
        param_16 = (undefined4 *)(&DAT_803b0a80 + iVar9);
        iVar6 = iVar6 * 0xc;
        uVar5 = param_15[1];
        *param_16 = *param_15;
        puVar7 = (undefined4 *)(iVar12 + iVar6 + 0x12d4);
        *(undefined4 *)(&DAT_803b0a84 + iVar9) = uVar5;
        uVar5 = param_15[3];
        *(undefined4 *)(&DAT_803b0a88 + iVar9) = param_15[2];
        *(undefined4 *)(&DAT_803b0a8c + iVar9) = uVar5;
        uVar5 = puVar7[1];
        *(undefined4 *)(&DAT_803b0900 + iVar6) = *puVar7;
        *(undefined4 *)(&DAT_803b0904 + iVar6) = uVar5;
        *(undefined4 *)(&DAT_803b0908 + iVar6) = puVar7[2];
        uVar13 = uVar13 - 1;
      } while (uVar13 != 0);
      uVar3 = uVar3 & 1;
      if (uVar3 == 0) goto LAB_8004998c;
    }
    do {
      iVar6 = (int)*(char *)(*(int *)(param_9 + 0x4b0) + iVar2 + 0x8c);
      iVar9 = iVar6 * 0x10;
      param_15 = (undefined4 *)(iVar4 + iVar9 + 0xed4);
      param_16 = (undefined4 *)(&DAT_803b0a80 + iVar9);
      iVar6 = iVar6 * 0xc;
      uVar5 = param_15[1];
      *param_16 = *param_15;
      puVar7 = (undefined4 *)(iVar12 + iVar6 + 0x12d4);
      *(undefined4 *)(&DAT_803b0a84 + iVar9) = uVar5;
      uVar5 = param_15[3];
      *(undefined4 *)(&DAT_803b0a88 + iVar9) = param_15[2];
      *(undefined4 *)(&DAT_803b0a8c + iVar9) = uVar5;
      uVar5 = puVar7[1];
      *(undefined4 *)(&DAT_803b0900 + iVar6) = *puVar7;
      *(undefined4 *)(&DAT_803b0904 + iVar6) = uVar5;
      *(undefined4 *)(&DAT_803b0908 + iVar6) = puVar7[2];
      uVar3 = uVar3 - 1;
      iVar2 = iVar2 + 1;
    } while (uVar3 != 0);
  }
LAB_8004998c:
  zz_004a830_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
              (char)param_10,param_11,0,&DAT_803b0900,param_15,param_16);
  dVar15 = (double)(float)((double)FLOAT_804370f0 - param_1);
  iVar2 = local_88;
  do {
    if (local_84 <= iVar2) {
      return;
    }
    iVar10 = (int)*(char *)(*(int *)(param_9 + 0x4b0) + iVar2 + 0x8c);
    gnt4_PSQUATScale_bl(param_1,(float *)(&DAT_803b0900 + iVar10 * 0xc),afStack_54);
    pfVar11 = (float *)(iVar12 + iVar10 * 0xc + 0x12d4);
    gnt4_PSQUATScale_bl(dVar15,pfVar11,afStack_60);
    gnt4_PSVECAdd_bl(afStack_54,afStack_60,pfVar11);
    iVar9 = iVar10 * 0x10;
    local_70 = *(float *)(&DAT_803b0a80 + iVar9);
    iVar6 = iVar4 + iVar9;
    local_6c = *(float *)(&DAT_803b0a84 + iVar9);
    local_68 = *(float *)(&DAT_803b0a88 + iVar9);
    local_64 = *(float *)(&DAT_803b0a8c + iVar9);
    local_80 = *(float *)(iVar6 + 0xed4);
    local_7c = *(float *)(iVar6 + 0xed8);
    local_78 = *(float *)(iVar6 + 0xedc);
    local_74 = *(float *)(iVar6 + 0xee0);
    if ((local_64 + local_74) * (local_64 + local_74) +
        (local_68 + local_78) * (local_68 + local_78) +
        (local_70 + local_80) * (local_70 + local_80) +
        (local_6c + local_7c) * (local_6c + local_7c) <
        (local_64 - local_74) * (local_64 - local_74) +
        (local_68 - local_78) * (local_68 - local_78) +
        (local_70 - local_80) * (local_70 - local_80) +
        (local_6c - local_7c) * (local_6c - local_7c)) {
      local_80 = -local_80;
      local_7c = -local_7c;
      local_78 = -local_78;
      local_74 = -local_74;
    }
    C_QUATSlerp(dVar15,&local_70,&local_80,(float *)(iVar6 + 0xed4));
    iVar9 = 0;
    iVar6 = 2;
    do {
      if (*(char *)(*(int *)(param_9 + 0x4b0) + iVar9 + 0x42) == iVar10) {
        if ((double)FLOAT_80437104 < dVar15) {
          *(undefined1 *)(param_9 + param_10 * 2 + iVar9 + 0x1d74) = (&DAT_80436168)[iVar9];
        }
        break;
      }
      iVar9 = iVar9 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    iVar2 = iVar2 + 1;
  } while( true );
}



// ==== 80049b98  zz_0049b98_ ====

/* WARNING: Removing unreachable block (ram,0x80049ca8) */
/* WARNING: Removing unreachable block (ram,0x80049ba8) */

void zz_0049b98_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,uint param_11,
                int param_12,uint param_13,int param_14,undefined4 param_15,undefined4 param_16)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = param_9 + param_10 * 0x40;
  *(undefined4 *)(iVar2 + 0x1bdc) = *(undefined4 *)(iVar2 + 0x1adc);
  *(undefined4 *)(iVar2 + 0x1be0) = *(undefined4 *)(iVar2 + 0x1ae0);
  *(undefined4 *)(iVar2 + 0x1be4) = *(undefined4 *)(iVar2 + 0x1ae4);
  *(undefined4 *)(iVar2 + 0x1be8) = *(undefined4 *)(iVar2 + 0x1ae8);
  uVar3 = param_13;
  iVar4 = param_14;
  puVar1 = (undefined1 *)zz_004d1f4_(param_9,param_11,param_12);
  *(char *)(iVar2 + 0x1afc) = (char)param_11;
  *(char *)(iVar2 + 0x1afd) = (char)param_12;
  zz_004d244_(param_9,param_10,iVar2 + 0x1ad4,puVar1);
  *(byte *)(iVar2 + 0x1b05) = *(byte *)(iVar2 + 0x1afe) >> 7;
  zz_004a754_((double)*(float *)(iVar2 + 0x1ae0),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,0,0,param_10,uVar3,iVar4,param_15,param_16);
  puVar1 = (undefined1 *)zz_004d1f4_(param_9,param_13,param_14);
  *(char *)(iVar2 + 0x1bfc) = (char)param_13;
  *(char *)(iVar2 + 0x1bfd) = (char)param_14;
  zz_004d244_(param_9,param_10,iVar2 + 0x1bd4,puVar1);
  *(byte *)(iVar2 + 0x1c05) = *(byte *)(iVar2 + 0x1bfe) >> 7;
  zz_004a754_((double)*(float *)(iVar2 + 0x1be0),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,1,1,param_10,uVar3,iVar4,param_15,param_16);
  FUN_8004a8cc(param_1,param_9,param_10);
  return;
}



// ==== 80049cc4  FUN_80049cc4 ====

/* WARNING: Removing unreachable block (ram,0x80049d90) */
/* WARNING: Removing unreachable block (ram,0x80049cd4) */

void FUN_80049cc4(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,uint param_11
                 ,int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_9 + param_10 * 0x40;
  *(undefined4 *)(iVar3 + 0x1bdc) = *(undefined4 *)(iVar3 + 0x1adc);
  uVar2 = 2;
  *(undefined4 *)(iVar3 + 0x1be0) = *(undefined4 *)(iVar3 + 0x1ae0);
  *(undefined4 *)(iVar3 + 0x1be4) = *(undefined4 *)(iVar3 + 0x1ae4);
  *(undefined4 *)(iVar3 + 0x1be8) = *(undefined4 *)(iVar3 + 0x1ae8);
  iVar4 = iVar3;
  zz_004a830_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,0,param_10,2
              ,iVar3,param_15,param_16);
  puVar1 = (undefined1 *)zz_004d1f4_(param_9,param_11,param_12);
  *(char *)(iVar3 + 0x1bfc) = (char)param_11;
  *(char *)(iVar3 + 0x1bfd) = (char)param_12;
  zz_004d244_(param_9,param_10,iVar3 + 0x1bd4,puVar1);
  *(byte *)(iVar3 + 0x1c05) = *(byte *)(iVar3 + 0x1bfe) >> 7;
  zz_004a754_((double)*(float *)(iVar3 + 0x1be0),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,1,1,param_10,uVar2,iVar4,param_15,param_16);
  FUN_8004a8cc(param_1,param_9,param_10);
  return;
}



// ==== 80049dac  FUN_80049dac ====

/* WARNING: Removing unreachable block (ram,0x80049e38) */
/* WARNING: Removing unreachable block (ram,0x80049dbc) */

void FUN_80049dac(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10)

{
  int iVar1;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar2;
  
  iVar1 = param_9 + param_10 * 0x40;
  *(undefined4 *)(iVar1 + 0x1bdc) = *(undefined4 *)(iVar1 + 0x1adc);
  *(undefined4 *)(iVar1 + 0x1be0) = *(undefined4 *)(iVar1 + 0x1ae0);
  *(undefined4 *)(iVar1 + 0x1be4) = *(undefined4 *)(iVar1 + 0x1ae4);
  *(undefined4 *)(iVar1 + 0x1be8) = *(undefined4 *)(iVar1 + 0x1ae8);
  uVar2 = zz_004a830_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,0,
                      param_10,2,iVar1,in_r9,in_r10);
  zz_004a830_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,1,param_10,2,
              iVar1,in_r9,in_r10);
  FUN_8004a8cc(param_1,param_9,param_10);
  return;
}



