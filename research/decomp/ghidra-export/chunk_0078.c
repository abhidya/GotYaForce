// ==== 802a1008  zz_02a1008_ ====

void zz_02a1008_(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x960) = 0;
    zz_02a5408_(param_1,6,0xc,param_2,0);
  }
  else {
    zz_029abec_(0,-0xfffec9);
  }
  return;
}



// ==== 802a107c  zz_02a107c_ ====

void zz_02a107c_(int param_1,int *param_2)

{
  int iVar1;
  
  *param_2 = 0;
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    zz_02a5408_(param_1,6,0xb,param_2,0);
    if (*param_2 != 0) {
      *(undefined4 *)(param_1 + 0x960) = 1;
    }
  }
  else {
    zz_029abec_(0,-0xfffeca);
  }
  return;
}



// ==== 802a1104  zz_02a1104_ ====

int zz_02a1104_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    zz_0298b30_(param_1,*(int *)(param_1 + 0x1ab4),1);
    iVar1 = 0;
    *(undefined4 *)(param_1 + 0x44) = 1;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffecb);
  }
  return iVar1;
}



// ==== 802a1168  zz_02a1168_ ====

undefined4 zz_02a1168_(void)

{
  return DAT_8041d428;
}



// ==== 802a1178  zz_02a1178_ ====

int zz_02a1178_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined8 uVar9;
  undefined1 auStack_204 [20];
  undefined4 local_1f0;
  undefined4 uStack_1ec;
  undefined4 local_1e8 [17];
  undefined1 auStack_1a4 [404];
  
  if (*(int *)(param_9 + 0x48) == 1) {
    return 0;
  }
  if ((*(int *)(param_9 + 0x48) != 4) || (iVar4 = zz_02a5408_(param_9,7,7,0,0), iVar4 == 0)) {
    iVar4 = 0;
    *(undefined4 *)(param_9 + 0x48) = 1;
    *(undefined4 *)(param_9 + 0x4c) = 1;
  }
  if (iVar4 != 0) {
    return iVar4;
  }
  zz_029aac8_();
  DAT_8041d428 = 1;
  iVar4 = 8;
  puVar1 = (undefined4 *)(param_9 + -4);
  puVar2 = &uStack_1ec;
  do {
    puVar8 = puVar2;
    puVar7 = puVar1;
    uVar3 = puVar7[2];
    puVar8[1] = puVar7[1];
    puVar8[2] = uVar3;
    iVar4 = iVar4 + -1;
    puVar1 = puVar7 + 2;
    puVar2 = puVar8 + 2;
  } while (iVar4 != 0);
  puVar8[3] = puVar7[3];
  iVar4 = *(int *)(param_9 + 0x9c0);
  uVar3 = 0;
  if (iVar4 != 0) {
    iVar5 = zz_029aaf4_(param_9);
    if (iVar5 == 0) {
      zz_02a5408_(param_9,0,9,auStack_204,0);
      uVar3 = local_1f0;
    }
    else {
      zz_029abec_(0,-0xfffecc);
      uVar3 = local_1f0;
    }
  }
  zz_029aa40_((undefined4 *)(param_9 + 0x78));
  uVar9 = zz_0299678_(param_9);
  *(undefined4 *)(param_9 + 0x48) = 0;
  *(undefined4 *)(param_9 + 0x4c) = 0;
  iVar5 = zz_02a545c_(param_9,4);
  if (iVar5 == 0) {
    uVar9 = zz_027c990_(auStack_1a4,(void *)(param_9 + 0xb30),400);
    uVar6 = zz_02a1bc4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_1e8);
    if (uVar6 == 0) {
      iVar5 = zz_029abec_(0,-0xfffdfe);
    }
    else {
      zz_027c990_((void *)(uVar6 + 0x9a0),auStack_1a4,400);
      uVar9 = zz_027c990_((void *)(uVar6 + 0xb30),auStack_1a4,400);
      if (iVar4 != 0) {
        iVar4 = zz_029aaf4_(uVar6);
        if (iVar4 == 0) {
          iVar5 = zz_02a5408_(uVar6,0,9,auStack_204,0);
        }
        else {
          iVar5 = zz_029abec_(0,-0xfffecc);
        }
        if (iVar5 != 0) goto LAB_802a13fc;
        iVar4 = zz_029aaf4_(uVar6);
        if (iVar4 == 0) {
          iVar5 = zz_02a5408_(uVar6,0,10,uVar3,local_1f0);
        }
        else {
          iVar5 = zz_029abec_(0,-0xfffecb);
        }
        if (iVar5 != 0) goto LAB_802a13fc;
        iVar4 = zz_029aaf4_(uVar6);
        if (iVar4 == 0) {
          uVar9 = zz_0298b30_(uVar6,*(int *)(uVar6 + 0x1ab4),1);
          *(undefined4 *)(uVar6 + 0x44) = 1;
        }
        else {
          zz_029abec_(0,-0xfffecb);
        }
      }
      iVar5 = 0;
    }
  }
LAB_802a13fc:
  DAT_8041d428 = 0;
  zz_029aa9c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  iVar4 = 0;
  if (iVar5 != 0) {
    iVar4 = iVar5;
  }
  return iVar4;
}



// ==== 802a143c  zz_02a143c_ ====

int zz_02a143c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined8 uVar9;
  undefined1 auStack_214 [20];
  undefined4 local_200;
  undefined4 uStack_1fc;
  undefined4 local_1f8 [17];
  undefined1 auStack_1b4 [416];
  
  iVar4 = zz_029aaf4_(param_9);
  if (iVar4 != 0) {
    iVar4 = zz_029abec_(0,-0xfffecd);
    return iVar4;
  }
  if (*(int *)(param_9 + 0x48) == 1) {
    iVar4 = 0;
    goto LAB_802a16fc;
  }
  if ((*(int *)(param_9 + 0x48) != 4) || (iVar4 = zz_02a5408_(param_9,7,7,0,0), iVar4 == 0)) {
    iVar4 = 0;
    *(undefined4 *)(param_9 + 0x48) = 1;
    *(undefined4 *)(param_9 + 0x4c) = 1;
  }
  if (iVar4 != 0) goto LAB_802a16fc;
  zz_029aac8_();
  DAT_8041d428 = 1;
  iVar4 = 8;
  puVar1 = (undefined4 *)(param_9 + -4);
  puVar2 = &uStack_1fc;
  do {
    puVar7 = puVar2;
    puVar6 = puVar1;
    uVar3 = puVar6[2];
    puVar7[1] = puVar6[1];
    puVar7[2] = uVar3;
    iVar4 = iVar4 + -1;
    puVar1 = puVar6 + 2;
    puVar2 = puVar7 + 2;
  } while (iVar4 != 0);
  puVar7[3] = puVar6[3];
  iVar8 = *(int *)(param_9 + 0x9c0);
  uVar3 = 0;
  if (iVar8 != 0) {
    iVar4 = zz_029aaf4_(param_9);
    if (iVar4 == 0) {
      zz_02a5408_(param_9,0,9,auStack_214,0);
      uVar3 = local_200;
    }
    else {
      zz_029abec_(0,-0xfffecc);
      uVar3 = local_200;
    }
  }
  zz_029aa40_((undefined4 *)(param_9 + 0x78));
  uVar9 = zz_0299678_(param_9);
  *(undefined4 *)(param_9 + 0x48) = 0;
  *(undefined4 *)(param_9 + 0x4c) = 0;
  iVar4 = zz_02a545c_(param_9,4);
  if (iVar4 == 0) {
    uVar9 = zz_027c990_(auStack_1b4,(void *)(param_9 + 0xb30),400);
    uVar5 = zz_02a1bc4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_1f8);
    if (uVar5 == 0) {
      iVar4 = zz_029abec_(0,-0xfffdfe);
    }
    else {
      zz_027c990_((void *)(uVar5 + 0x9a0),auStack_1b4,400);
      uVar9 = zz_027c990_((void *)(uVar5 + 0xb30),auStack_1b4,400);
      if (iVar8 == 0) {
LAB_802a16d4:
        iVar4 = 0;
      }
      else {
        iVar4 = zz_029aaf4_(uVar5);
        if (iVar4 == 0) {
          iVar4 = zz_02a5408_(uVar5,0,9,auStack_214,0);
        }
        else {
          iVar4 = zz_029abec_(0,-0xfffecc);
        }
        if (iVar4 == 0) {
          iVar4 = zz_029aaf4_(uVar5);
          if (iVar4 == 0) {
            iVar4 = zz_02a5408_(uVar5,0,10,uVar3,local_200);
          }
          else {
            iVar4 = zz_029abec_(0,-0xfffecb);
          }
          if (iVar4 == 0) {
            iVar4 = zz_029aaf4_(uVar5);
            if (iVar4 == 0) {
              uVar9 = zz_0298b30_(uVar5,*(int *)(uVar5 + 0x1ab4),1);
              *(undefined4 *)(uVar5 + 0x44) = 1;
            }
            else {
              zz_029abec_(0,-0xfffecb);
            }
            goto LAB_802a16d4;
          }
        }
      }
    }
  }
  DAT_8041d428 = 0;
  zz_029aa9c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  if (iVar4 == 0) {
    iVar4 = 0;
  }
LAB_802a16fc:
  *(undefined4 *)(param_9 + 0x44) = 1;
  return iVar4;
}



// ==== 802a1718  zz_02a1718_ ====

int zz_02a1718_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    iVar1 = cTeam__GetPlayer_int_(param_1,0x2f);
    if (iVar1 == 1) {
      iVar1 = MWInitializeMutex(param_1);
    }
    else {
      iVar1 = 0;
      *(undefined4 *)(param_1 + 0x4c) = 4;
    }
    *(undefined4 *)(param_1 + 0x44) = 1;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffece);
  }
  return iVar1;
}



// ==== 802a1794  zz_02a1794_ ====

void zz_02a1794_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined8 uVar9;
  undefined1 auStack_214 [20];
  undefined4 local_200;
  undefined4 uStack_1fc;
  undefined4 local_1f8 [17];
  undefined1 auStack_1b4 [416];
  
  iVar4 = zz_029aaf4_(param_9);
  if (iVar4 == 0) {
    if (*(int *)(param_9 + 0x48) != 1) {
      if ((*(int *)(param_9 + 0x48) != 4) || (iVar4 = zz_02a5408_(param_9,7,7,0,0), iVar4 == 0)) {
        iVar4 = 0;
        *(undefined4 *)(param_9 + 0x48) = 1;
        *(undefined4 *)(param_9 + 0x4c) = 1;
      }
      if (iVar4 == 0) {
        zz_029aac8_();
        DAT_8041d428 = 1;
        iVar4 = 8;
        puVar1 = (undefined4 *)(param_9 + -4);
        puVar2 = &uStack_1fc;
        do {
          puVar8 = puVar2;
          puVar7 = puVar1;
          uVar3 = puVar7[2];
          puVar8[1] = puVar7[1];
          puVar8[2] = uVar3;
          iVar4 = iVar4 + -1;
          puVar1 = puVar7 + 2;
          puVar2 = puVar8 + 2;
        } while (iVar4 != 0);
        puVar8[3] = puVar7[3];
        iVar4 = *(int *)(param_9 + 0x9c0);
        uVar3 = 0;
        if (iVar4 != 0) {
          iVar5 = zz_029aaf4_(param_9);
          if (iVar5 == 0) {
            zz_02a5408_(param_9,0,9,auStack_214,0);
            uVar3 = local_200;
          }
          else {
            zz_029abec_(0,-0xfffecc);
            uVar3 = local_200;
          }
        }
        zz_029aa40_((undefined4 *)(param_9 + 0x78));
        uVar9 = zz_0299678_(param_9);
        *(undefined4 *)(param_9 + 0x48) = 0;
        *(undefined4 *)(param_9 + 0x4c) = 0;
        iVar5 = zz_02a545c_(param_9,4);
        if (iVar5 == 0) {
          uVar9 = zz_027c990_(auStack_1b4,(void *)(param_9 + 0xb30),400);
          uVar6 = zz_02a1bc4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              local_1f8);
          if (uVar6 == 0) {
            zz_029abec_(0,-0xfffdfe);
          }
          else {
            zz_027c990_((void *)(uVar6 + 0x9a0),auStack_1b4,400);
            uVar9 = zz_027c990_((void *)(uVar6 + 0xb30),auStack_1b4,400);
            if (iVar4 != 0) {
              iVar4 = zz_029aaf4_(uVar6);
              if (iVar4 == 0) {
                iVar4 = zz_02a5408_(uVar6,0,9,auStack_214,0);
              }
              else {
                iVar4 = zz_029abec_(0,-0xfffecc);
              }
              if (iVar4 == 0) {
                iVar4 = zz_029aaf4_(uVar6);
                if (iVar4 == 0) {
                  iVar4 = zz_02a5408_(uVar6,0,10,uVar3,local_200);
                }
                else {
                  iVar4 = zz_029abec_(0,-0xfffecb);
                }
                if (iVar4 == 0) {
                  iVar4 = zz_029aaf4_(uVar6);
                  if (iVar4 == 0) {
                    uVar9 = zz_0298b30_(uVar6,*(int *)(uVar6 + 0x1ab4),1);
                    *(undefined4 *)(uVar6 + 0x44) = 1;
                  }
                  else {
                    zz_029abec_(0,-0xfffecb);
                  }
                }
              }
            }
          }
        }
        DAT_8041d428 = 0;
        zz_029aa9c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      }
    }
    zz_029aa40_((undefined4 *)(param_9 + 0x78));
    zz_0299678_(param_9);
    *(undefined4 *)(param_9 + 0x48) = 0;
    *(undefined4 *)(param_9 + 0x4c) = 0;
    zz_02a545c_(param_9,4);
    if (DAT_8041d430 == param_9) {
      DAT_8041d430 = 0;
    }
    if (DAT_8041d434 == param_9) {
      DAT_8041d434 = 0;
    }
    if (DAT_8041d438 == param_9) {
      DAT_8041d438 = 0;
    }
    if (DAT_8041d43c == param_9) {
      DAT_8041d43c = 0;
    }
    if (DAT_8041d440 == param_9) {
      DAT_8041d440 = 0;
    }
    if (DAT_8041d444 == param_9) {
      DAT_8041d444 = 0;
    }
    if (DAT_8041d448 == param_9) {
      DAT_8041d448 = 0;
    }
    if (DAT_8041d44c == param_9) {
      DAT_8041d44c = 0;
    }
  }
  else {
    zz_029abec_(0,-0xfffecf);
  }
  return;
}



// ==== 802a1adc  zz_02a1adc_ ====

void zz_02a1adc_(int param_1,int param_2,undefined4 param_3)

{
  code *pcVar1;
  
  *(int *)(param_1 + 0x950) = *(int *)(param_1 + 0x950) + param_2;
  pcVar1 = (code *)cTeam__GetPlayer_int_(param_1,0x25);
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)(param_1,param_3,param_1 + 0x94c);
  }
  return;
}



// ==== 802a1b50  zz_02a1b50_ ====

void zz_02a1b50_(int param_1,int param_2,undefined4 param_3)

{
  code *pcVar1;
  
  *(int *)(param_1 + 0x94c) = *(int *)(param_1 + 0x94c) + param_2;
  pcVar1 = (code *)cTeam__GetPlayer_int_(param_1,0x24);
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)(param_1,param_3,param_1 + 0x94c);
  }
  return;
}



// ==== 802a1bc4  zz_02a1bc4_ ====

uint zz_02a1bc4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 *param_9)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  
  iVar6 = param_9[0xf];
  zz_02a94c4_(iVar6,0,(uint)param_9[0x10] >> 2);
  uVar3 = iVar6 + 0x1fU & 0xffffffe0;
  *(undefined4 *)(uVar3 + 0x4c) = 0;
  *(undefined4 *)(uVar3 + 0x48) = 0;
  param_9[1] = param_9[1] + 0x1f & 0xffffffe0;
  iVar6 = 8;
  puVar7 = param_9 + -1;
  puVar1 = (undefined4 *)(uVar3 - 4);
  do {
    puVar5 = puVar1;
    puVar4 = puVar7;
    uVar2 = puVar4[2];
    puVar5[1] = puVar4[1];
    puVar5[2] = uVar2;
    iVar6 = iVar6 + -1;
    puVar7 = puVar4 + 2;
    puVar1 = puVar5 + 2;
  } while (iVar6 != 0);
  puVar5[3] = puVar4[3];
  *(undefined4 *)(uVar3 + 0x44) = 1;
  *(undefined4 *)(uVar3 + 0x50) = 0;
  *(undefined4 *)(uVar3 + 0x54) = 0;
  zz_029aa54_((undefined4 *)(uVar3 + 0x78));
  zz_02a94c4_(uVar3 + 0x90c,0,0x10);
  *(undefined4 *)(uVar3 + 0x90c) = 0;
  *(undefined4 *)(uVar3 + 0x910) = 0;
  *(undefined4 *)(uVar3 + 0x914) = 0;
  *(undefined4 *)(uVar3 + 0x918) = 0;
  *(undefined4 *)(uVar3 + 0x91c) = 0;
  *(undefined4 *)(uVar3 + 0x920) = 0;
  *(undefined4 *)(uVar3 + 0x924) = 0;
  *(undefined4 *)(uVar3 + 0x928) = 1;
  *(undefined4 *)(uVar3 + 0x92c) = 0;
  *(undefined4 *)(uVar3 + 0x930) = 0xffffffff;
  *(undefined4 *)(uVar3 + 0x934) = 0xffffffff;
  *(undefined4 *)(uVar3 + 0x938) = 0xffffffff;
  zz_02a94c4_(uVar3 + 0x94c,0,0x10);
  *(undefined4 *)(uVar3 + 0x94c) = 0;
  *(undefined4 *)(uVar3 + 0x950) = 0;
  *(undefined4 *)(uVar3 + 0x954) = 0;
  *(undefined4 *)(uVar3 + 0x958) = 0;
  *(undefined4 *)(uVar3 + 0x95c) = 0;
  *(undefined4 *)(uVar3 + 0x960) = 0;
  *(undefined4 *)(uVar3 + 0x964) = 0;
  *(undefined4 *)(uVar3 + 0x968) = 0;
  *(undefined4 *)(uVar3 + 0x96c) = 0;
  *(undefined4 *)(uVar3 + 0x970) = 0;
  zz_02a94c4_(uVar3 + 0x28a8,0,0x30);
  iVar6 = 0;
  puVar7 = (undefined4 *)(uVar3 + 0x28a8);
  do {
    zz_02a5fac_(puVar7);
    iVar6 = iVar6 + 1;
    puVar7 = puVar7 + 8;
  } while (iVar6 < 5);
  zz_02a5fac_((undefined4 *)(uVar3 + 0x2948));
  zz_029acc8_((undefined4 *)(uVar3 + 0x98c));
  zz_027c990_((void *)(uVar3 + 0x9a0),&DAT_8041d22c,400);
  zz_027c990_((void *)(uVar3 + 0xb30),&DAT_8041d22c,400);
  uVar8 = zz_02a5078_(uVar3,uVar3 + 0xcc0);
  iVar6 = zz_0299744_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar3,
                      (undefined4 *)(uVar3 + 0x1140),(int)param_9);
  if (iVar6 == 0) {
    zz_02a5834_(uVar3,(undefined4 *)(uVar3 + 0x1aa0),param_9);
    zz_02a3724_((undefined4 *)(uVar3 + 0x2898));
    iVar6 = zz_02a545c_(uVar3,3);
    if (iVar6 == 0) {
      *(undefined4 *)(uVar3 + 0x4c) = 1;
      *(undefined4 *)(uVar3 + 0x48) = 1;
    }
    else {
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 802a1dd8  zz_02a1dd8_ ====

uint zz_02a1dd8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 *param_9)

{
  int iVar1;
  uint uVar2;
  
  if (param_9[1] == 0) {
    iVar1 = -1;
  }
  else if ((uint)param_9[0x10] < 0x2988) {
    iVar1 = -1;
  }
  else {
    iVar1 = 0;
  }
  if (iVar1 == 0) {
    if (DAT_8041d430 == 0) {
      iVar1 = 0;
    }
    else if (DAT_8041d434 == 0) {
      iVar1 = 1;
    }
    else if (DAT_8041d438 == 0) {
      iVar1 = 2;
    }
    else if (DAT_8041d43c == 0) {
      iVar1 = 3;
    }
    else if (DAT_8041d440 == 0) {
      iVar1 = 4;
    }
    else if (DAT_8041d444 == 0) {
      iVar1 = 5;
    }
    else if (DAT_8041d448 == 0) {
      iVar1 = 6;
    }
    else if (DAT_8041d44c == 0) {
      iVar1 = 7;
    }
    else {
      iVar1 = -1;
    }
    if (iVar1 == -1) {
      uVar2 = 0;
    }
    else {
      uVar2 = zz_02a1bc4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      (&DAT_8041d430)[iVar1] = uVar2;
    }
  }
  else {
    zz_029abec_(0,-0xfffdfd);
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 802a1f20  zz_02a1f20_ ====

uint zz_02a1f20_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  bool bVar5;
  uint uVar6;
  undefined8 extraout_f1;
  undefined8 uVar7;
  uint local_18;
  uint local_14 [3];
  
  iVar1 = cTeam__GetPlayer_int_(param_9,0x43);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else if (*(int *)(param_9 + 0x50) == 0) {
    if (*(int *)(param_9 + 0x48) == 4) {
      iVar1 = cTeam__GetPlayer_int_(param_9,5);
      if ((iVar1 == 0) || (iVar1 = zz_02a53c8_(param_9,6), iVar1 == 0)) {
        iVar1 = cTeam__GetPlayer_int_(param_9,6);
        if ((iVar1 == 0) || (iVar1 = zz_02a53c8_(param_9,7), iVar1 == 0)) {
          iVar1 = 0;
          do {
            iVar4 = zz_0298b20_(param_9,iVar1);
            if (iVar4 != 0) {
              bVar5 = true;
              goto LAB_802a2008;
            }
            iVar1 = iVar1 + 1;
          } while (iVar1 < 8);
          bVar5 = false;
        }
        else {
          bVar5 = true;
        }
      }
      else {
        bVar5 = true;
      }
LAB_802a2008:
      if (bVar5) {
        uVar2 = 0;
      }
      else {
        iVar1 = cTeam__GetPlayer_int_(param_9,5);
        if ((iVar1 == 1) && (*(int *)(param_9 + 0x96c) == 0)) {
          uVar2 = 0;
        }
        else {
          iVar1 = cTeam__GetPlayer_int_(param_9,6);
          if ((iVar1 == 1) &&
             (iVar1 = zz_02989f0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_9,2), 0 < iVar1)) {
            uVar2 = 0;
          }
          else {
            uVar2 = zz_02a53ac_(param_9,1);
            if ((uVar2 == 0) ||
               (iVar1 = zz_02989f0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,0), iVar1 < 1)) {
              iVar1 = param_9 + *(int *)(param_9 + 0x1b38) * 0x74 + 0x1150;
              piVar3 = *(int **)(iVar1 + 4);
              iVar4 = (**(code **)(*piVar3 + 0x24))(piVar3,1);
              iVar1 = *(int *)(iVar1 + 0xc) * 0x50;
              iVar1 = iVar1 / 100 + (iVar1 >> 0x1f);
              uVar7 = extraout_f1;
              if ((iVar4 < iVar1 - (iVar1 >> 0x1f)) &&
                 (iVar1 = cTeam__GetPlayer_int_(param_9,0x46), iVar4 < iVar1)) {
                bVar5 = false;
              }
              else {
                bVar5 = true;
              }
              if (bVar5) {
                uVar2 = 0;
              }
              else {
                zz_02a4910_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                            (int *)local_14,&local_18);
                iVar4 = *(int *)(param_9 + 0xf00);
                uVar6 = *(uint *)(param_9 + 0xf04);
                uVar2 = cTeam__GetPlayer_int_(param_9,0x44);
                iVar1 = zz_02a953c_(uVar2,uVar6,1000000);
                uVar2 = iVar4 - iVar1;
                if (((int)local_14[0] < 1) || ((int)uVar2 < 1)) {
                  uVar2 = 0;
                }
                else {
                  bVar5 = zz_02a4628_(local_14[0],local_18,uVar2,uVar6);
                  uVar2 = countLeadingZeros((uint)bVar5);
                  uVar2 = uVar2 >> 5;
                }
              }
            }
            else {
              uVar2 = 0;
            }
          }
        }
      }
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 802a21ac  zz_02a21ac_ ====

undefined4
zz_02a21ac_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  bool bVar7;
  uint uVar8;
  uint uVar9;
  undefined8 uVar10;
  undefined8 extraout_f1;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24 [5];
  
  uVar9 = *(uint *)(param_9 + 0x9f0);
  uVar8 = *(uint *)(param_9 + 0x9f4);
  if (uVar9 == 0xfffffffc) {
    bVar7 = false;
  }
  else {
    zz_02a4910_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                (int *)&local_28,local_24);
    if ((int)local_28 < 0) {
      bVar7 = false;
    }
    else {
      bVar7 = zz_02a9378_(local_28,local_24[0],uVar9,uVar8);
      if (bVar7) {
        bVar7 = false;
      }
      else {
        bVar7 = true;
      }
    }
  }
  if (!bVar7) {
    if ((*(int *)(param_9 + 0x9b8) == 0) && (*(int *)(param_9 + 0x9b4) == 0)) {
      uVar8 = 1;
    }
    else {
      uVar9 = zz_02a53c8_(param_9,6);
      uVar1 = zz_02a53c8_(param_9,7);
      iVar2 = cTeam__GetPlayer_int_(param_9,0x19);
      uVar8 = uVar9;
      if (iVar2 != 2) {
        if (iVar2 < 2) {
          if (iVar2 == 0) {
            uVar8 = uVar1 & uVar9;
          }
          else {
            uVar8 = uVar1;
            if (iVar2 < 0) {
              uVar8 = 0;
            }
          }
        }
        else {
          uVar8 = 0;
          if (iVar2 < 4) {
            uVar8 = uVar1 | uVar9;
          }
        }
      }
    }
    if (uVar8 == 0) {
      if (((*(int *)(param_9 + 0x48) == 4) && (*(int *)(param_9 + 0x50) != 1)) &&
         (*(int *)(param_9 + 0x964) != 1)) {
        bVar7 = zz_02a4cc0_(param_9);
        if (bVar7) {
          bVar7 = true;
        }
        else {
          bVar7 = false;
        }
      }
      else {
        bVar7 = false;
      }
      if (!bVar7) {
        if (((*(int *)(param_9 + 0x48) == 4) && (*(int *)(param_9 + 0x50) != 1)) &&
           (*(int *)(param_9 + 0x964) != 1)) {
          iVar2 = zz_02a49c4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              param_9,(int *)&local_30,&local_2c);
          if (iVar2 == 0) {
            if ((int)local_30 < 0) {
              bVar7 = false;
            }
            else {
              uVar8 = cTeam__GetPlayer_int_(param_9,0x36);
              bVar7 = zz_02a4628_(uVar8,1000,local_30,local_2c);
              if (bVar7) {
                bVar7 = true;
              }
              else {
                bVar7 = false;
              }
            }
          }
          else {
            bVar7 = false;
          }
        }
        else {
          bVar7 = false;
        }
        if (!bVar7) {
          iVar2 = 0;
          goto LAB_802a2414;
        }
      }
    }
  }
  if ((*(int *)(param_9 + 0x48) != 4) || (iVar2 = zz_02a5408_(param_9,7,7,0,0), iVar2 == 0)) {
    iVar2 = 0;
    *(undefined4 *)(param_9 + 0x48) = 1;
    *(undefined4 *)(param_9 + 0x4c) = 1;
  }
  if (iVar2 == 0) {
    iVar2 = 0;
    *(undefined4 *)(param_9 + 0x4c) = 6;
  }
LAB_802a2414:
  if (iVar2 == 0) {
    uVar10 = zz_029aac8_();
    iVar2 = 0;
    if (*(int *)(param_9 + 0x964) == 0) {
      uVar8 = zz_02a1f20_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      if (uVar8 != 0) {
        *(undefined4 *)(param_9 + 0x964) = 1;
        *(int *)(param_9 + 0x968) = *(int *)(param_9 + 0x968) + 1;
        iVar2 = zz_02a0c4c_(param_9,1);
      }
    }
    else {
      iVar4 = cTeam__GetPlayer_int_(param_9,5);
      if ((iVar4 == 0) || (iVar4 = zz_02a53c8_(param_9,6), iVar4 == 0)) {
        iVar4 = cTeam__GetPlayer_int_(param_9,6);
        if ((iVar4 == 0) || (iVar4 = zz_02a53c8_(param_9,7), iVar4 == 0)) {
          iVar4 = 0;
          do {
            iVar6 = zz_0298b20_(param_9,iVar4);
            if (iVar6 != 0) {
              bVar7 = true;
              goto LAB_802a2504;
            }
            iVar4 = iVar4 + 1;
          } while (iVar4 < 8);
          bVar7 = false;
        }
        else {
          bVar7 = true;
        }
      }
      else {
        bVar7 = true;
      }
LAB_802a2504:
      if (bVar7) {
        bVar7 = true;
      }
      else {
        iVar4 = param_9 + *(int *)(param_9 + 0x1b38) * 0x74 + 0x1150;
        piVar5 = *(int **)(iVar4 + 4);
        iVar6 = (**(code **)(*piVar5 + 0x24))(piVar5,1);
        iVar4 = *(int *)(iVar4 + 0xc) * 0x50;
        iVar4 = iVar4 / 100 + (iVar4 >> 0x1f);
        uVar10 = extraout_f1;
        if ((iVar6 < iVar4 - (iVar4 >> 0x1f)) &&
           (iVar4 = cTeam__GetPlayer_int_(param_9,0x46), iVar6 < iVar4)) {
          bVar7 = false;
        }
        else {
          bVar7 = true;
        }
        if (bVar7) {
          bVar7 = true;
        }
        else {
          zz_02a4910_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      (int *)&local_38,&local_34);
          iVar6 = *(int *)(param_9 + 0xf00);
          uVar9 = *(uint *)(param_9 + 0xf04);
          uVar8 = cTeam__GetPlayer_int_(param_9,0x45);
          iVar4 = zz_02a953c_(uVar8,uVar9,1000000);
          bVar7 = zz_02a4628_(local_38,local_34,iVar6 - iVar4,uVar9);
          if (bVar7) {
            bVar7 = true;
          }
          else {
            bVar7 = false;
          }
        }
      }
      if (bVar7) {
        *(undefined4 *)(param_9 + 0x964) = 0;
        iVar2 = zz_02a0c4c_(param_9,0);
      }
    }
    zz_029aa9c_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    if (iVar2 == 0) {
      iVar2 = *(int *)(param_9 + 0x4c);
      uVar3 = *(undefined4 *)(param_9 + 0x48);
      if (((iVar2 != 5) && (4 < iVar2)) && (iVar2 < 7)) {
        uVar3 = 6;
      }
    }
    else {
      uVar3 = *(undefined4 *)(param_9 + 0x48);
    }
  }
  else {
    uVar3 = *(undefined4 *)(param_9 + 0x48);
  }
  return uVar3;
}



// ==== 802a2674  zz_02a2674_ ====

undefined4
zz_02a2674_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  byte bVar5;
  uint uVar4;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  
  uVar7 = *(undefined4 *)(param_9 + 0x48);
  iVar8 = *(int *)(param_9 + 0x4c);
  iVar3 = cTeam__GetPlayer_int_(param_9,5);
  if (iVar3 == 0) {
    uVar6 = 1;
  }
  else {
    uVar6 = zz_02a53e8_(param_9,6);
    uVar2 = zz_02a53c8_(param_9,6);
    uVar6 = uVar6 | uVar2;
  }
  iVar3 = cTeam__GetPlayer_int_(param_9,6);
  if (iVar3 == 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = zz_02a53e8_(param_9,7);
    uVar4 = zz_02a53c8_(param_9,7);
    uVar2 = uVar2 | uVar4;
  }
  if ((uVar6 == 0) || (uVar2 == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (!bVar1) {
    return uVar7;
  }
  if (((*(int *)(param_9 + 0x9b4) == 1) &&
      (iVar3 = zz_0298c84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1
                          ), iVar3 == 0)) && (iVar3 = zz_0298d18_(param_9,1), iVar3 == 0)) {
    *(undefined4 *)(param_9 + 0x9b4) = 0;
  }
  if (((*(int *)(param_9 + 0x9b8) == 1) &&
      (iVar3 = zz_0298c84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,2
                          ), iVar3 == 0)) && (iVar3 = zz_0298d18_(param_9,2), iVar3 == 0)) {
    *(undefined4 *)(param_9 + 0x9b8) = 0;
  }
  zz_02a3698_(param_9,*(undefined4 *)(param_9 + 0x9b4),*(undefined4 *)(param_9 + 0x9b8));
  if ((*(int *)(param_9 + 0x9b8) == 0) && (*(int *)(param_9 + 0x9dc) == 2)) {
    zz_02a39d8_(param_9,0xf,1);
  }
  if ((*(int *)(param_9 + 0x9b4) == 0) && (*(int *)(param_9 + 0x9dc) == 1)) {
    zz_02a39d8_(param_9,0xf,2);
  }
  bVar5 = *(int *)(param_9 + 0x9b8) == 1;
  if (*(int *)(param_9 + 0x9b4) == 1) {
    bVar5 = bVar5 | 2;
  }
  if (bVar5 == 2) {
    iVar3 = 2;
  }
  else {
    if (bVar5 < 2) {
      if (bVar5 != 0) {
        iVar3 = 1;
        goto LAB_802a2878;
      }
    }
    else if (bVar5 < 4) {
      iVar3 = cTeam__GetPlayer_int_(param_9,0x19);
      goto LAB_802a2878;
    }
    iVar3 = 3;
  }
LAB_802a2878:
  zz_02a39d8_(param_9,0x19,iVar3);
  if (iVar8 != 4) {
    if (iVar8 < 4) {
      if (iVar8 == 2) {
        return 2;
      }
      if (iVar8 < 2) {
        return uVar7;
      }
      return 3;
    }
    if (iVar8 != 6) {
      return uVar7;
    }
  }
  if (*(int *)(param_9 + 0x9d8) == 0) {
    bVar1 = true;
  }
  else if (*(int *)(param_9 + 0x9b4) == 0) {
    bVar1 = true;
  }
  else if (*(int *)(param_9 + 0xf2c) == 0) {
    if (*(int *)(param_9 + 0xf48) < *(int *)(param_9 + 0xa54)) {
      if ((*(int *)(param_9 + 0x9b8) == 0) && (*(int *)(param_9 + 0x9b4) == 0)) {
        uVar6 = 1;
      }
      else {
        uVar2 = zz_02a53c8_(param_9,6);
        uVar4 = zz_02a53c8_(param_9,7);
        iVar3 = cTeam__GetPlayer_int_(param_9,0x19);
        uVar6 = uVar2;
        if (iVar3 != 2) {
          if (iVar3 < 2) {
            if (iVar3 == 0) {
              uVar6 = uVar4 & uVar2;
            }
            else {
              uVar6 = uVar4;
              if (iVar3 < 0) {
                uVar6 = 0;
              }
            }
          }
          else {
            uVar6 = 0;
            if (iVar3 < 4) {
              uVar6 = uVar4 | uVar2;
            }
          }
        }
      }
      if (uVar6 == 0) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    }
    else {
      bVar1 = true;
    }
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    zz_02a5408_(param_9,7,6,0,0);
    uVar7 = 4;
  }
  else {
    uVar7 = 3;
  }
  return uVar7;
}



// ==== 802a29f8  zz_02a29f8_ ====

void zz_02a29f8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined8 extraout_f1;
  undefined8 uVar7;
  undefined8 uVar8;
  
  iVar5 = *(int *)(param_9 + 0x48);
  if (3 < iVar5 - 1U) {
    return;
  }
  if (*(int *)(param_9 + 0x44) == 0) {
    return;
  }
  *(undefined4 *)(param_9 + 0x44) = 0;
  uVar8 = zz_02a9654_();
  if ((iVar5 - 2U < 2) || (uVar7 = extraout_f1, iVar5 == 4)) {
    zz_02a545c_(param_9,2);
    uVar7 = zz_02a3500_(param_9);
  }
  uVar2 = *(undefined4 *)(param_9 + 0x48);
  switch(uVar2) {
  case 1:
    iVar5 = *(int *)(param_9 + 0x4c);
    if (iVar5 != 5) {
      if (iVar5 < 5) {
        if (iVar5 < 2) break;
      }
      else if (6 < iVar5) break;
      uVar2 = 2;
    }
    break;
  case 2:
    uVar2 = zz_02a2674_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 3:
    iVar5 = *(int *)(param_9 + 0x4c);
    if (iVar5 != 4) {
      if (iVar5 < 4) {
        if (iVar5 == 2) {
          uVar2 = 2;
        }
        else if (1 < iVar5) {
          uVar2 = 3;
        }
        break;
      }
      if (iVar5 != 6) break;
    }
    if (*(int *)(param_9 + 0x9d8) == 0) {
      bVar1 = true;
    }
    else if (*(int *)(param_9 + 0x9b4) == 0) {
      bVar1 = true;
    }
    else if (*(int *)(param_9 + 0xf2c) == 0) {
      if (*(int *)(param_9 + 0xf48) < *(int *)(param_9 + 0xa54)) {
        if ((*(int *)(param_9 + 0x9b8) == 0) && (*(int *)(param_9 + 0x9b4) == 0)) {
          uVar6 = 1;
        }
        else {
          uVar3 = zz_02a53c8_(param_9,6);
          uVar4 = zz_02a53c8_(param_9,7);
          iVar5 = cTeam__GetPlayer_int_(param_9,0x19);
          uVar6 = uVar3;
          if (iVar5 != 2) {
            if (iVar5 < 2) {
              if (iVar5 == 0) {
                uVar6 = uVar4 & uVar3;
              }
              else {
                uVar6 = uVar4;
                if (iVar5 < 0) {
                  uVar6 = 0;
                }
              }
            }
            else {
              uVar6 = 0;
              if (iVar5 < 4) {
                uVar6 = uVar4 | uVar3;
              }
            }
          }
        }
        if (uVar6 == 0) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
      }
      else {
        bVar1 = true;
      }
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      zz_02a5408_(param_9,7,6,0,0);
      uVar2 = 4;
    }
    break;
  case 4:
    uVar2 = zz_02a21ac_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  *(undefined4 *)(param_9 + 0x48) = uVar2;
  uVar7 = zz_02a9654_();
  uVar6 = (uint)uVar7;
  zz_02a5f18_((int *)(param_9 + 0x2948),uVar6,
              (int)((ulonglong)uVar7 >> 0x20) -
              ((uint)(uVar6 < (uint)uVar8) + (int)((ulonglong)uVar8 >> 0x20)),uVar6 - (uint)uVar8);
  return;
}



// ==== 802a2c58  zz_02a2c58_ ====

int zz_02a2c58_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_9);
  if (iVar1 == 0) {
    *(undefined4 *)(param_9 + 0x44) = 1;
    zz_02a29f8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    iVar1 = 0;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffec8);
  }
  return iVar1;
}



// ==== 802a2cb4  zz_02a2cb4_ ====

undefined4 zz_02a2cb4_(void)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  piVar2 = &DAT_8041d430;
  iVar4 = 4;
  do {
    iVar3 = *piVar2;
    if (iVar3 != 0) {
      if (*(int *)(iVar3 + 0x48) - 1U < 4) {
        if (*(int *)(iVar3 + 0x44) == 0) {
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
      }
      else {
        bVar1 = true;
      }
      if (!bVar1) {
        return 0;
      }
    }
    iVar3 = piVar2[1];
    if (iVar3 != 0) {
      if (*(int *)(iVar3 + 0x48) - 1U < 4) {
        if (*(int *)(iVar3 + 0x44) == 0) {
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
      }
      else {
        bVar1 = true;
      }
      if (!bVar1) {
        return 0;
      }
    }
    piVar2 = piVar2 + 2;
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      return 1;
    }
  } while( true );
}



// ==== 802a2d78  zz_02a2d78_ ====

uint zz_02a2d78_(int param_1)

{
  uint uVar1;
  
  if (3 < *(int *)(param_1 + 0x48) - 1U) {
    return 1;
  }
  uVar1 = countLeadingZeros(*(undefined4 *)(param_1 + 0x44));
  return uVar1 >> 5;
}



// ==== 802a2da0  zz_02a2da0_ ====

uint zz_02a2da0_(void)

{
  return (-DAT_80430cf8 & ~DAT_80430cf8) >> 0x1f;
}



// ==== 802a2dbc  zz_02a2dbc_ ====

void zz_02a2dbc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  DAT_80430cf8 = DAT_80430cf8 + 1;
  zz_02a4da8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  DAT_80430cf8 = DAT_80430cf8 + -1;
  return;
}



// ==== 802a2e04  zz_02a2e04_ ====

void zz_02a2e04_(void)

{
  if (DAT_802b8d60 != 0x5a5a5a5a) {
    zz_029abec_(0,-0xfffdff);
  }
  DAT_80430cf8 = 0;
  return;
}



// ==== 802a2e54  zz_02a2e54_ ====

undefined4 zz_02a2e54_(int param_1,int param_2,uint param_3,undefined4 *param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  
  iVar7 = param_1 + param_2 * 0x74;
  *param_4 = 0xffffffff;
  iVar11 = *(int *)(iVar7 + 0x115c);
  if (*(int *)(iVar7 + 0x1178) != 0) {
    uVar10 = *(uint *)(iVar7 + 0x1158) + iVar11;
    if (uVar10 <= param_3) {
      param_3 = param_3 - iVar11;
    }
    iVar1 = *(int *)(iVar7 + 0x1180);
    if (iVar1 != 0) {
      iVar8 = 0;
      iVar12 = *(int *)(iVar7 + 0x117c);
      iVar5 = *(int *)(iVar7 + 0x1188);
      if (0 < iVar1) {
        do {
          iVar9 = *(int *)(iVar7 + 0x1178) + iVar5 * 0xc;
          uVar4 = *(uint *)(iVar9 + 4);
          uVar2 = uVar4 + *(int *)(iVar9 + 8);
          if (uVar10 < uVar2) {
            if ((uVar4 <= param_3) && (param_3 < uVar10)) goto LAB_802a2f3c;
            if (*(uint *)(iVar7 + 0x1158) <= param_3) {
              uVar2 = uVar2 - iVar11;
              goto joined_r0x802a2f14;
            }
          }
          else if (uVar4 <= param_3) {
joined_r0x802a2f14:
            if (param_3 < uVar2) goto LAB_802a2f3c;
          }
          iVar9 = iVar5 + 1;
          iVar5 = iVar9 - iVar12;
          if (iVar9 < iVar12) {
            iVar5 = iVar9;
          }
          iVar8 = iVar8 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
      iVar8 = -1;
LAB_802a2f3c:
      if (iVar8 != -1) {
        iVar1 = *(int *)(iVar7 + 0x1188) + iVar8;
        iVar11 = iVar1 - iVar12;
        if (iVar1 < iVar12) {
          iVar11 = iVar1;
        }
        *(int *)(iVar7 + 0x1180) = *(int *)(iVar7 + 0x1180) - iVar8;
        *(int *)(iVar7 + 0x1188) = iVar11;
        puVar6 = (undefined4 *)(*(int *)(iVar7 + 0x1178) + iVar11 * 0xc);
        uVar3 = puVar6[1];
        *param_4 = *puVar6;
        param_4[1] = uVar3;
        param_4[2] = puVar6[2];
      }
    }
  }
  return 0;
}



// ==== 802a2fa4  zz_02a2fa4_ ====

int zz_02a2fa4_(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  if (*param_3 < 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = param_1 + param_2 * 0x74;
    if (*(int *)(iVar1 + 0x1178) == 0) {
      iVar1 = 0;
    }
    else {
      if (*(int *)(iVar1 + 0x1180) == *(int *)(iVar1 + 0x117c)) {
        iVar3 = -1;
      }
      else {
        iVar2 = param_3[1];
        iVar3 = *(int *)(iVar1 + 0x1184) + 1;
        piVar4 = (int *)(*(int *)(iVar1 + 0x1178) + *(int *)(iVar1 + 0x1184) * 0xc);
        *piVar4 = *param_3;
        piVar4[1] = iVar2;
        piVar4[2] = param_3[2];
        iVar2 = iVar3 - *(int *)(iVar1 + 0x117c);
        if (iVar3 < *(int *)(iVar1 + 0x117c)) {
          iVar2 = iVar3;
        }
        iVar3 = 0;
        *(int *)(iVar1 + 0x1180) = *(int *)(iVar1 + 0x1180) + 1;
        *(int *)(iVar1 + 0x1184) = iVar2;
      }
      if (iVar3 == -1) {
        iVar1 = zz_029abec_(param_1,-0xfffbdf);
      }
      else {
        iVar1 = 0;
      }
    }
  }
  return iVar1;
}



// ==== 802a3070  zz_02a3070_ ====

void zz_02a3070_(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  return;
}



// ==== 802a308c  zz_02a308c_ ====

int zz_02a308c_(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x2898) == 0) {
      iVar1 = 0;
    }
    else {
      *(undefined4 *)(*(int *)(param_1 + 0x2898) + 0xdb0) = param_2;
      iVar1 = *(int *)(param_1 + 0x2898);
      if (*(int *)(iVar1 + 0xdbc) < 1) {
        uVar2 = *(uint *)(iVar1 + 0xdb0);
        uVar5 = *(uint *)(iVar1 + 0xdb4);
        uVar4 = *(uint *)(iVar1 + 0xdb8);
        if (((int)uVar2 < 1) || ((int)uVar5 < 1)) {
          if (*(int *)(iVar1 + 4) < 1) {
            if ((int)uVar2 < 1) {
              uVar2 = *(uint *)(iVar1 + 0xd98);
            }
            if ((int)uVar5 < 1) {
              uVar5 = *(uint *)(iVar1 + 0xd9c);
              uVar4 = *(uint *)(iVar1 + 0xda0);
            }
            if (((int)uVar2 < 1) || ((int)uVar5 < 1)) {
              *(undefined4 *)(iVar1 + 0xd94) = *(undefined4 *)(iVar1 + 4);
            }
            else {
              iVar3 = zz_02a953c_(uVar2,uVar4,uVar5);
              *(int *)(iVar1 + 0xd94) = iVar3;
            }
          }
          else {
            *(int *)(iVar1 + 0xd94) = *(int *)(iVar1 + 4);
          }
        }
        else {
          iVar3 = zz_02a953c_(uVar2,uVar4,uVar5);
          *(int *)(iVar1 + 0xd94) = iVar3;
        }
      }
      else {
        *(int *)(iVar1 + 0xd94) = *(int *)(iVar1 + 0xdbc);
      }
      iVar1 = 0;
    }
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffea7);
  }
  return iVar1;
}



// ==== 802a3190  zz_02a3190_ ====

int zz_02a3190_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 *param_10)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = zz_029aaf4_(param_9);
  if (iVar2 == 0) {
    iVar2 = *(int *)(param_9 + 0x2898);
    if (iVar2 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = zz_02a1178_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      if (iVar3 == 0) {
        zz_02a39d8_(param_9,0x2f,0);
        if (*(int *)(iVar2 + 0xda4) == 0) {
          zz_02a39d8_(param_9,5,0);
        }
        if (*(int *)(iVar2 + 0xda8) == 0) {
          zz_02a39d8_(param_9,6,0);
        }
        uVar1 = param_10[1];
        *(undefined4 *)(param_9 + 0x289c) = *param_10;
        *(undefined4 *)(param_9 + 0x28a0) = uVar1;
        *(undefined4 *)(param_9 + 0x28a4) = param_10[2];
        iVar3 = zz_02a545c_(param_9,0xd);
      }
    }
  }
  else {
    iVar3 = zz_029abec_(0,-0xfffea8);
  }
  return iVar3;
}



// ==== 802a3280  zz_02a3280_ ====

void zz_02a3280_(int param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  
  piVar9 = *(int **)(param_1 + 0x2898);
  if (*piVar9 == 0) {
    uVar4 = zz_02a53ac_(param_1,3);
    if ((uVar4 == 0) || (iVar5 = cTeam__GetPlayer_int_(param_1,6), iVar5 != 1)) {
      bVar3 = false;
      bVar1 = false;
    }
    else {
      bVar3 = true;
      if (piVar9[0x33f] == 0) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
    }
    if (!bVar1) {
      uVar4 = zz_02a53ac_(param_1,2);
      if ((uVar4 == 0) || (iVar5 = cTeam__GetPlayer_int_(param_1,5), iVar5 != 1)) {
        bVar2 = false;
        bVar1 = false;
      }
      else {
        bVar2 = true;
        if (piVar9[0x2b1] == 0) {
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
      }
      if (!bVar1) {
        uVar4 = zz_02a53ac_(param_1,1);
        if ((int)(-uVar4 | uVar4) < 0) {
          piVar9[0x228] = 1;
          if ((piVar9[3] == 0) || (piVar9[6] < 1)) {
            if ((piVar9[3] == 0) || (iVar5 = zz_029a0fc_(param_1), 0x6b < iVar5)) {
              iVar5 = piVar9[0x229];
            }
            else {
              uVar4 = piVar9[0x229] << 0xb;
              iVar5 = (int)uVar4 / 0x7e2 + ((int)(uVar4 | (uint)piVar9[0x229] >> 0x15) >> 0x1f);
              iVar5 = iVar5 - (iVar5 >> 0x1f);
            }
          }
          else if ((piVar9[0x36c] < 1) || (piVar9[0x10] < 1)) {
            iVar5 = piVar9[6];
          }
          else {
            iVar5 = zz_02a953c_(piVar9[0x36c],1000,piVar9[0x10]);
          }
          iVar6 = piVar9[0x22a];
        }
        else if (bVar2) {
          iVar5 = piVar9[0x2b2];
          iVar6 = piVar9[0x2b3];
        }
        else {
          if (!bVar3) {
            return;
          }
          iVar5 = piVar9[0x340];
          iVar6 = piVar9[0x341];
        }
        piVar9[1] = iVar5;
        piVar9[2] = iVar6;
        *piVar9 = 1;
        iVar5 = *(int *)(param_1 + 0x2898);
        if (*(int *)(iVar5 + 0xdbc) < 1) {
          uVar4 = *(uint *)(iVar5 + 0xdb0);
          uVar8 = *(uint *)(iVar5 + 0xdb4);
          uVar7 = *(uint *)(iVar5 + 0xdb8);
          if (((int)uVar4 < 1) || ((int)uVar8 < 1)) {
            if (*(int *)(iVar5 + 4) < 1) {
              if ((int)uVar4 < 1) {
                uVar4 = *(uint *)(iVar5 + 0xd98);
              }
              if ((int)uVar8 < 1) {
                uVar8 = *(uint *)(iVar5 + 0xd9c);
                uVar7 = *(uint *)(iVar5 + 0xda0);
              }
              if (((int)uVar4 < 1) || ((int)uVar8 < 1)) {
                *(undefined4 *)(iVar5 + 0xd94) = *(undefined4 *)(iVar5 + 4);
              }
              else {
                iVar6 = zz_02a953c_(uVar4,uVar7,uVar8);
                *(int *)(iVar5 + 0xd94) = iVar6;
              }
            }
            else {
              *(int *)(iVar5 + 0xd94) = *(int *)(iVar5 + 4);
            }
          }
          else {
            iVar6 = zz_02a953c_(uVar4,uVar7,uVar8);
            *(int *)(iVar5 + 0xd94) = iVar6;
          }
        }
        else {
          *(int *)(iVar5 + 0xd94) = *(int *)(iVar5 + 0xdbc);
        }
      }
    }
  }
  return;
}



// ==== 802a3500  zz_02a3500_ ====

void zz_02a3500_(int param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  if (*(int *)(param_1 + 0x2898) != 0) {
    zz_02a3280_(param_1);
    iVar8 = *(int *)(param_1 + 0x2898);
    uVar3 = zz_029a03c_(param_1);
    if (uVar3 == 0) {
      bVar1 = false;
      if (*(int *)(iVar8 + 0xd98) < 1) {
        if (*(int *)(param_1 + 0x28a0) == -3) {
          iVar5 = 0;
        }
        else {
          iVar5 = *(int *)(iVar8 + 0xdc0);
        }
        if (-1 < iVar5) {
          iVar4 = *(int *)(param_1 +
                          *(int *)(param_1 + *(int *)(param_1 + 0x1ab4) * 0x74 + 0x1190) * 0x44 +
                          0x1ac0);
          iVar2 = -1;
          if (-1 < iVar4) {
            iVar2 = iVar4;
          }
          if (iVar2 != -1) {
            bVar1 = true;
            *(int *)(iVar8 + 0xd98) = iVar5 + iVar2;
          }
        }
      }
      if ((*(int *)(iVar8 + 0xd9c) < 1) && (0 < *(int *)(param_1 + 0xd4c))) {
        *(int *)(iVar8 + 0xd9c) = *(int *)(param_1 + 0xd4c);
        bVar1 = true;
        *(undefined4 *)(iVar8 + 0xda0) = *(undefined4 *)(param_1 + 0xd50);
      }
      if (bVar1) {
        iVar8 = *(int *)(param_1 + 0x2898);
        if (*(int *)(iVar8 + 0xdbc) < 1) {
          uVar3 = *(uint *)(iVar8 + 0xdb0);
          uVar7 = *(uint *)(iVar8 + 0xdb4);
          uVar6 = *(uint *)(iVar8 + 0xdb8);
          if (((int)uVar3 < 1) || ((int)uVar7 < 1)) {
            if (*(int *)(iVar8 + 4) < 1) {
              if ((int)uVar3 < 1) {
                uVar3 = *(uint *)(iVar8 + 0xd98);
              }
              if ((int)uVar7 < 1) {
                uVar7 = *(uint *)(iVar8 + 0xd9c);
                uVar6 = *(uint *)(iVar8 + 0xda0);
              }
              if (((int)uVar3 < 1) || ((int)uVar7 < 1)) {
                *(undefined4 *)(iVar8 + 0xd94) = *(undefined4 *)(iVar8 + 4);
              }
              else {
                iVar5 = zz_02a953c_(uVar3,uVar6,uVar7);
                *(int *)(iVar8 + 0xd94) = iVar5;
              }
            }
            else {
              *(int *)(iVar8 + 0xd94) = *(int *)(iVar8 + 4);
            }
          }
          else {
            iVar5 = zz_02a953c_(uVar3,uVar6,uVar7);
            *(int *)(iVar8 + 0xd94) = iVar5;
          }
        }
        else {
          *(int *)(iVar8 + 0xd94) = *(int *)(iVar8 + 0xdbc);
        }
      }
    }
  }
  return;
}



// ==== 802a3698  zz_02a3698_ ====

void zz_02a3698_(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x2898);
  if (iVar1 == 0) {
    return;
  }
  if (*(int *)(iVar1 + 0xda4) < 0) {
    *(undefined4 *)(iVar1 + 0xda4) = param_2;
  }
  if (-1 < *(int *)(iVar1 + 0xda8)) {
    return;
  }
  *(undefined4 *)(iVar1 + 0xda8) = param_3;
  return;
}



// ==== 802a36c8  zz_02a36c8_ ====

int zz_02a36c8_(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x2898) = param_2;
    iVar1 = 0;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffeaf);
  }
  return iVar1;
}



// ==== 802a3724  zz_02a3724_ ====

void zz_02a3724_(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0xfffffffd;
  param_1[3] = 1;
  return;
}



// ==== 802a3744  zz_02a3744_ ====

int zz_02a3744_(int param_1,int *param_2,undefined4 *param_3)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x78) == 0) {
      *param_2 = 0;
      *param_3 = 0;
    }
    else {
      *param_2 = param_1 + 0x10c;
      *param_3 = *(undefined4 *)(param_1 + 0x108);
    }
    iVar1 = 0;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffee4);
  }
  return iVar1;
}



// ==== 802a37d4  zz_02a37d4_ ====

int zz_02a37d4_(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    puVar2 = *(undefined4 **)(param_1 + param_2 * 0x44 + 0x1aa8);
    if (puVar2 == (undefined4 *)0x0) {
      *param_3 = 0;
    }
    else {
      *param_3 = *puVar2;
    }
    iVar1 = 0;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffee9);
  }
  return iVar1;
}



// ==== 802a3860  zz_02a3860_ ====

int zz_02a3860_(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = zz_029aaf4_(param_1);
  if (iVar2 == 0) {
    iVar2 = 0;
    uVar1 = *(undefined4 *)(param_1 + 0x950);
    *param_2 = *(undefined4 *)(param_1 + 0x94c);
    param_2[1] = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x958);
    param_2[2] = *(undefined4 *)(param_1 + 0x954);
    param_2[3] = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x960);
    param_2[4] = *(undefined4 *)(param_1 + 0x95c);
    param_2[5] = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x968);
    param_2[6] = *(undefined4 *)(param_1 + 0x964);
    param_2[7] = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x970);
    param_2[8] = *(undefined4 *)(param_1 + 0x96c);
    param_2[9] = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x978);
    param_2[10] = *(undefined4 *)(param_1 + 0x974);
    param_2[0xb] = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x980);
    param_2[0xc] = *(undefined4 *)(param_1 + 0x97c);
    param_2[0xd] = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x988);
    param_2[0xe] = *(undefined4 *)(param_1 + 0x984);
    param_2[0xf] = uVar1;
  }
  else {
    iVar2 = zz_029abec_(0,-0xfffee7);
  }
  return iVar2;
}



// ==== 802a3938  cTeam::GetPlayer(int) ====

undefined4 cTeam__GetPlayer_int_(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + param_2 * 4 + 0x9a0);
}



// ==== 802a3948  zz_02a3948_ ====

int zz_02a3948_(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  
  if (param_1 == 0) {
    *param_3 = *(undefined4 *)(&DAT_8041d22c + param_2 * 4);
  }
  else {
    iVar1 = zz_029aaf4_(param_1);
    if (iVar1 != 0) {
      iVar1 = zz_029abec_(0,-0xfffeed);
      return iVar1;
    }
    *param_3 = *(undefined4 *)(param_1 + param_2 * 4 + 0x9a0);
  }
  return 0;
}



// ==== 802a39d8  zz_02a39d8_ ====

void zz_02a39d8_(int param_1,int param_2,int param_3)

{
  bool bVar1;
  uint uVar2;
  
  if (((param_2 == 6) && (param_3 == 1)) && (uVar2 = zz_02a53ac_(param_1,3), uVar2 == 0)) {
    bVar1 = false;
  }
  else if (((param_2 == 5) && (param_3 == 1)) && (uVar2 = zz_02a53ac_(param_1,2), uVar2 == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    *(int *)(param_1 + param_2 * 4 + 0x9a0) = param_3;
  }
  return;
}



// ==== 802a3a84  zz_02a3a84_ ====

int zz_02a3a84_(int param_1,int param_2,int param_3)

{
  bool bVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  if (param_1 == 0) {
    iVar4 = 0;
    piVar3 = &DAT_8041d430;
    do {
      iVar5 = *piVar3;
      if (iVar5 != 0) {
        if (((param_2 == 6) && (param_3 == 1)) && (uVar2 = zz_02a53ac_(iVar5,3), uVar2 == 0)) {
          bVar1 = false;
        }
        else if (((param_2 == 5) && (param_3 == 1)) && (uVar2 = zz_02a53ac_(iVar5,2), uVar2 == 0)) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        if (bVar1) {
          *(int *)(param_2 * 4 + iVar5 + 0x9a0) = param_3;
        }
      }
      iVar4 = iVar4 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar4 < 8);
    *(int *)(&DAT_8041d22c + param_2 * 4) = param_3;
  }
  else {
    iVar4 = zz_029aaf4_(param_1);
    if (iVar4 != 0) {
      iVar4 = zz_029abec_(0,-0xfffeee);
      return iVar4;
    }
    if (((param_2 == 6) && (param_3 == 1)) && (uVar2 = zz_02a53ac_(param_1,3), uVar2 == 0)) {
      bVar1 = false;
    }
    else if (((param_2 == 5) && (param_3 == 1)) && (uVar2 = zz_02a53ac_(param_1,2), uVar2 == 0)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      *(int *)(param_1 + param_2 * 4 + 0x9a0) = param_3;
    }
    if (((param_2 == 6) && (param_3 == 1)) && (uVar2 = zz_02a53ac_(param_1,3), uVar2 == 0)) {
      bVar1 = false;
    }
    else if (((param_2 == 5) && (param_3 == 1)) && (uVar2 = zz_02a53ac_(param_1,2), uVar2 == 0)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      *(int *)(param_1 + param_2 * 4 + 0xb30) = param_3;
    }
  }
  return 0;
}



// ==== 802a3c68  zz_02a3c68_ ====

undefined4 zz_02a3c68_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 != 0) {
    zz_029abec_(0,-0xfffeef);
  }
  return *(undefined4 *)(param_1 + 0x48);
}



// ==== 802a3cb0  zz_02a3cb0_ ====

undefined4 zz_02a3cb0_(int param_1)

{
  return *(undefined4 *)(param_1 + 0xf28);
}



// ==== 802a3cb8  zz_02a3cb8_ ====

undefined4
zz_02a3cb8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  code *pcVar4;
  uint uVar5;
  int iVar6;
  undefined8 uVar7;
  uint local_24;
  uint local_20 [5];
  
  iVar6 = *(int *)(param_9 + 0xef8);
  uVar5 = *(uint *)(param_9 + 0xefc);
  if (*(int *)(param_9 + 0x94c) == 0) {
    uVar1 = 1;
  }
  else if (iVar6 == -5) {
    uVar1 = 0;
  }
  else {
    if (*(uint *)(param_9 + 0xf08) == 0xfffffffb) {
      zz_029aac8_();
      iVar2 = cTeam__GetPlayer_int_(param_9,0xf);
      pcVar4 = *(code **)(param_9 + iVar2 * 4 + 0xcc0);
      if (pcVar4 == (code *)0x0) {
        pcVar4 = FUN_802a48a8;
      }
      uVar7 = (*pcVar4)(param_9,local_20,&local_24);
      zz_029aa9c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else {
      local_24 = *(uint *)(param_9 + 0xf0c);
      local_20[0] = *(uint *)(param_9 + 0xf08);
    }
    iVar2 = uVar5 * 2000;
    iVar2 = iVar2 / 0xea24 + (iVar2 >> 0x1f);
    bVar3 = zz_02a9378_(iVar6 + (iVar2 - (iVar2 >> 0x1f)),uVar5,local_20[0],local_24);
    if (bVar3) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}



// ==== 802a3dd0  zz_02a3dd0_ ====

void zz_02a3dd0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,uint param_10,uint param_11,undefined4 *param_12,int param_13)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  bool bVar5;
  code *pcVar6;
  undefined8 uVar7;
  uint local_44;
  int local_40 [10];
  
  if (*(int *)(param_9 + 0xf08) == -5) {
    zz_029aac8_();
    iVar4 = cTeam__GetPlayer_int_(param_9,0xf);
    pcVar6 = *(code **)(param_9 + iVar4 * 4 + 0xcc0);
    if (pcVar6 == (code *)0x0) {
      pcVar6 = FUN_802a48a8;
    }
    uVar7 = (*pcVar6)(param_9,local_40,&local_44);
    zz_029aa9c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  else {
    local_44 = *(uint *)(param_9 + 0xf0c);
    local_40[0] = *(int *)(param_9 + 0xf08);
  }
  if (local_44 == 1) {
    if (local_40[0] == -2) {
      *param_12 = 1;
    }
    else if (*(int *)(param_9 + 0xf48) < 0) {
      *(undefined4 *)(param_9 + 0xf48) = 0;
      *param_12 = 1;
    }
    else {
      bVar5 = zz_02a9378_(param_10,param_11,*(uint *)(param_9 + 0xf48),DAT_8041d3e4);
      if (bVar5) {
        *param_12 = 1;
      }
      else {
        *param_12 = 0;
      }
    }
  }
  else {
    fVar2 = (DAT_802b8e50 *
            (float)((double)CONCAT44(0x43300000,param_10 ^ 0x80000000) - DAT_802b8e48)) /
            (float)((double)CONCAT44(0x43300000,param_11 ^ 0x80000000) - DAT_802b8e48);
    fVar3 = (DAT_802b8e50 *
            (float)((double)CONCAT44(0x43300000,
                                     local_40[0] + (int)(local_44 * param_13) / (int)DAT_8041d3e4 ^
                                     0x80000000) - DAT_802b8e48)) /
            (float)((double)CONCAT44(0x43300000,local_44 ^ 0x80000000) - DAT_802b8e48);
    if (*(int *)(param_9 + 0x9dc) == 1) {
      if (fVar3 < fVar2) {
        *param_12 = 0;
      }
      else {
        *param_12 = 1;
      }
    }
    else {
      fVar1 = (float)((double)CONCAT44(0x43300000,*(uint *)(param_9 + 0xa58) ^ 0x80000000) -
                     DAT_802b8e48);
      if (fVar2 <= fVar3 + fVar1) {
        if (fVar3 - fVar1 < fVar2) {
          iVar4 = 0;
          if (((DAT_8041d3e4 == 0xea24) && (*(int *)(param_9 + 0x920) < 3)) &&
             (*(int *)(param_9 + 0xf28) == 1000)) {
            iVar4 = 1;
          }
          if ((int)((uint)-iVar4 >> 0x1f) < *(int *)(param_9 + 0xf38)) {
            if (fVar2 <= fVar3) {
              *param_12 = 1;
            }
            else {
              *param_12 = 0;
            }
          }
          else {
            *param_12 = *(undefined4 *)(param_9 + 0xf40);
          }
          *(undefined4 *)(param_9 + 0xf38) = 0;
          *(undefined4 *)(param_9 + 0xf40) = *param_12;
          *(float *)(param_9 + 0xf44) = fVar2;
        }
        else {
          *param_12 = 1;
          if ((*(float *)(param_9 + 0xf44) != fVar2) && (*(float *)(param_9 + 0xf3c) != fVar2)) {
            *(float *)(param_9 + 0xf3c) = fVar2;
            *(int *)(param_9 + 0xf38) = *(int *)(param_9 + 0xf38) + 1;
          }
        }
      }
      else {
        *param_12 = 0;
      }
    }
  }
  return;
}



// ==== 802a40ac  zz_02a40ac_ ====

undefined4
zz_02a40ac_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           uint param_10,uint param_11)

{
  undefined4 local_8 [2];
  
  if (*(int *)(param_9 + 0x9d8) == 0) {
    zz_02a3dd0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,local_8,*(int *)(param_9 + 0xa50));
  }
  else {
    local_8[0] = 1;
  }
  return local_8[0];
}



// ==== 802a40ec  zz_02a40ec_ ====

undefined4
zz_02a40ec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           int param_10)

{
  undefined4 uVar1;
  
  if (param_10 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = zz_02a40ac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        *(uint *)(param_10 + 0x14),*(uint *)(param_10 + 0x18));
  }
  return uVar1;
}



// ==== 802a4124  zz_02a4124_ ====

int zz_02a4124_(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  *param_2 = 0xffffffff;
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x920) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = 0;
      *param_2 = *(undefined4 *)(&DAT_802b8dd8 + *(int *)(param_1 + 0x920) * 4);
    }
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffee5);
  }
  return iVar1;
}



// ==== 802a41ac  zz_02a41ac_ ====

void zz_02a41ac_(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x920);
  if (iVar1 == 0) {
    *param_2 = 0;
    *param_3 = 0x7512;
    return;
  }
  *param_2 = 1000;
  *param_3 = *(undefined4 *)(&DAT_802b8dd8 + iVar1 * 4);
  return;
}



// ==== 802a41ec  zz_02a41ec_ ====

void zz_02a41ec_(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_2 == 2) {
    if (*(int *)(param_1 + 0x920) == 0) {
      uVar3 = 0;
      uVar2 = 0x7512;
    }
    else {
      uVar3 = 1000;
      uVar2 = *(uint *)(&DAT_802b8dd8 + *(int *)(param_1 + 0x920) * 4);
    }
    iVar1 = zz_02a953c_(DAT_8041d3e4,uVar3,uVar2);
    *(int *)(param_1 + 0xf24) = *(int *)(param_1 + 0xf24) + iVar1;
    *(int *)(param_1 + 0xf48) = *(int *)(param_1 + 0xf48) + iVar1;
    iVar1 = zz_02a953c_(*(uint *)(param_1 + 0xf5c),uVar3,uVar2);
    *(int *)(param_1 + 0xf58) = *(int *)(param_1 + 0xf58) + iVar1;
  }
  return;
}



// ==== 802a42ac  FUN_802a42ac ====

void FUN_802a42ac(undefined4 param_1,int param_2,int *param_3,undefined4 *param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 0xc);
  iVar1 = iVar2 / 10 + (iVar2 >> 0x1f);
  *param_3 = (*(int *)(param_2 + 0x14) +
             *(int *)(param_2 + 8) * 0x34b54 +
             iVar2 * 0xe0e + (iVar1 - (iVar1 >> 0x1f)) * 2 + *(int *)(param_2 + 0x10) * 0x3c +
             *(int *)(param_2 + 0x18)) * 1000;
  *param_4 = param_1;
  return;
}



// ==== 802a4324  FUN_802a4324 ====

void FUN_802a4324(undefined4 param_1,int param_2,int *param_3,undefined4 *param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 0xc);
  iVar1 = iVar2 / 10 + (iVar2 >> 0x1f);
  *param_3 = (*(int *)(param_2 + 0x14) +
             *(int *)(param_2 + 8) * 0x1a574 +
             iVar2 * 0x706 + (iVar1 - (iVar1 >> 0x1f)) * 2 + *(int *)(param_2 + 0x10) * 0x1e +
             *(int *)(param_2 + 0x18)) * 1000;
  *param_4 = param_1;
  return;
}



// ==== 802a439c  FUN_802a439c ====

void FUN_802a439c(undefined4 param_1,int param_2,int *param_3,undefined4 *param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 0xc);
  iVar1 = iVar2 / 10 + (iVar2 >> 0x1f);
  *param_3 = (*(int *)(param_2 + 0x14) +
             *(int *)(param_2 + 8) * 0x15114 +
             iVar2 * 0x59e + (iVar1 - (iVar1 >> 0x1f)) * 2 + *(int *)(param_2 + 0x10) * 0x18 +
             *(int *)(param_2 + 0x18)) * 1000;
  *param_4 = param_1;
  return;
}



// ==== 802a4414  FUN_802a4414 ====

void FUN_802a4414(undefined4 param_1,int param_2,int *param_3,undefined4 *param_4)

{
  *param_3 = *(int *)(param_2 + 0xc) * 3600000 +
             *(int *)(param_2 + 8) * 216000000 + *(int *)(param_2 + 0x10) * 60000 +
             (*(int *)(param_2 + 0x14) + *(int *)(param_2 + 0x18)) * 1000;
  *param_4 = 60000;
  *param_4 = param_1;
  return;
}



// ==== 802a4570  zz_02a4570_ ====

void zz_02a4570_(int *param_1,undefined4 *param_2,undefined4 *param_3)

{
  code *pcVar1;
  
  pcVar1 = *(code **)(*param_1 * 8 + -0x7fd47204 + param_1[1] * 4);
  if (pcVar1 == (code *)0x0) {
    zz_029abec_(0,-0xfffddf);
    *param_2 = 0;
    *param_3 = 1;
  }
  else {
    (*pcVar1)(*(undefined4 *)(&DAT_802b8dd8 + *param_1 * 4),param_1,param_2,param_3);
  }
  return;
}



// ==== 802a4618  zz_02a4618_ ====

void zz_02a4618_(int param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_1 + param_3 * 4 + 0xcc0) = param_2;
  return;
}



// ==== 802a4628  zz_02a4628_ ====

bool zz_02a4628_(uint param_1,uint param_2,uint param_3,uint param_4)

{
  bool bVar1;
  
  bVar1 = zz_02a9378_(param_1,param_2,param_3,param_4);
  return bVar1;
}



// ==== 802a4648  zz_02a4648_ ====

undefined4 zz_02a4648_(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x48);
  if ((((iVar1 != 4) && (iVar1 != -4)) && (iVar1 != 6)) && (iVar1 != -6)) {
    *param_2 = 0xffffffff;
    *param_3 = 1;
    return 0;
  }
  return 1;
}



// ==== 802a468c  FUN_802a468c ====

undefined4 FUN_802a468c(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_18;
  int local_14 [2];
  
  iVar2 = *(int *)(param_1 + 0x48);
  if ((((iVar2 == 4) || (iVar2 == -4)) || (iVar2 == 6)) || (iVar2 == -6)) {
    bVar1 = true;
  }
  else {
    *param_2 = 0xffffffff;
    bVar1 = false;
    *param_3 = 1;
  }
  if (bVar1) {
    if (*(code **)(param_1 + 0xf50) == (code *)0x0) {
      *param_2 = 0xfffffffe;
      uVar3 = 0;
      *param_3 = 1;
    }
    else {
      uVar3 = (**(code **)(param_1 + 0xf50))(param_1,local_14,&local_18);
      if (*(int *)(param_1 + 0x48) == 4) {
        if (*(int *)(param_1 + 0x50) == 0) {
          if (*(int *)(param_1 + 0x964) == 0) {
            bVar1 = true;
          }
          else {
            bVar1 = false;
          }
        }
        else {
          bVar1 = false;
        }
      }
      else {
        bVar1 = false;
      }
      if ((bVar1) && (*(int *)(param_1 + 0xf54) != -5)) {
        *(int *)(param_1 + 0xf58) =
             *(int *)(param_1 + 0xf58) + (local_14[0] - *(int *)(param_1 + 0xf54));
      }
      *(int *)(param_1 + 0xf54) = local_14[0];
      *(undefined4 *)(param_1 + 0xf5c) = local_18;
      *param_2 = *(undefined4 *)(param_1 + 0xf58);
      *param_3 = *(undefined4 *)(param_1 + 0xf5c);
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 802a48a8  FUN_802a48a8 ====

undefined4 FUN_802a48a8(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x48);
  if ((((iVar2 == 4) || (iVar2 == -4)) || (iVar2 == 6)) || (iVar2 == -6)) {
    bVar1 = true;
  }
  else {
    *param_2 = 0xffffffff;
    bVar1 = false;
    *param_3 = 1;
  }
  if (!bVar1) {
    return 0;
  }
  *param_2 = 0xfffffffe;
  *param_3 = 1;
  return 0;
}



// ==== 802a4910  zz_02a4910_ ====

undefined4
zz_02a4910_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           int *param_10,undefined4 *param_11)

{
  int iVar1;
  undefined4 uVar2;
  code *pcVar3;
  undefined8 extraout_f1;
  
  if (*(int *)(param_9 + 0xf08) == -5) {
    zz_029aac8_();
    iVar1 = cTeam__GetPlayer_int_(param_9,0xf);
    pcVar3 = *(code **)(param_9 + iVar1 * 4 + 0xcc0);
    if (pcVar3 == (code *)0x0) {
      pcVar3 = FUN_802a48a8;
    }
    uVar2 = (*pcVar3)(param_9,param_10,param_11);
    zz_029aa9c_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  else {
    *param_10 = *(int *)(param_9 + 0xf08);
    uVar2 = 0;
    *param_11 = *(undefined4 *)(param_9 + 0xf0c);
  }
  return uVar2;
}



// ==== 802a49c4  zz_02a49c4_ ====

undefined4
zz_02a49c4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           int *param_10,uint *param_11)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  code *pcVar4;
  undefined8 extraout_f1;
  
  if (*(int *)(param_9 + 0xf08) == -5) {
    zz_029aac8_();
    iVar1 = cTeam__GetPlayer_int_(param_9,0xf);
    pcVar4 = *(code **)(param_9 + iVar1 * 4 + 0xcc0);
    if (pcVar4 == (code *)0x0) {
      pcVar4 = FUN_802a48a8;
    }
    uVar2 = (*pcVar4)(param_9,param_10,param_11);
    zz_029aa9c_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  else {
    *param_10 = *(int *)(param_9 + 0xf08);
    uVar2 = 0;
    *param_11 = *(uint *)(param_9 + 0xf0c);
  }
  uVar3 = *param_11;
  if (uVar3 != 1) {
    if (uVar3 == *(uint *)(param_9 + 0xdd0)) {
      *param_10 = *param_10 + *(int *)(param_9 + 0xdcc);
    }
    else if (*(int *)(param_9 + 0xda4) != 0) {
      iVar1 = zz_02a953c_(*(uint *)(param_9 + 0xdc4),uVar3,*(uint *)(param_9 + 0xdc8));
      *param_10 = *param_10 + iVar1;
    }
  }
  return uVar2;
}



// ==== 802a4ac4  zz_02a4ac4_ ====

int zz_02a4ac4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int *param_10,uint *param_11)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  code *pcVar4;
  undefined8 extraout_f1;
  
  iVar1 = zz_029aaf4_(param_9);
  if (iVar1 == 0) {
    if (*(int *)(param_9 + 0xf08) == -5) {
      zz_029aac8_();
      iVar1 = cTeam__GetPlayer_int_(param_9,0xf);
      pcVar4 = *(code **)(param_9 + iVar1 * 4 + 0xcc0);
      if (pcVar4 == (code *)0x0) {
        pcVar4 = FUN_802a48a8;
      }
      iVar1 = (*pcVar4)(param_9,param_10,param_11);
      zz_029aa9c_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else {
      *param_10 = *(int *)(param_9 + 0xf08);
      iVar1 = 0;
      *param_11 = *(uint *)(param_9 + 0xf0c);
    }
    uVar3 = *param_11;
    if (uVar3 != 1) {
      if (uVar3 == *(uint *)(param_9 + 0xdd0)) {
        *param_10 = *param_10 + *(int *)(param_9 + 0xdcc);
      }
      else if (*(int *)(param_9 + 0xda4) != 0) {
        iVar2 = zz_02a953c_(*(uint *)(param_9 + 0xdc4),uVar3,*(uint *)(param_9 + 0xdc8));
        *param_10 = *param_10 + iVar2;
      }
    }
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffedf);
  }
  return iVar1;
}



// ==== 802a4be0  zz_02a4be0_ ====

void zz_02a4be0_(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x10c) = param_2;
  *(undefined4 *)(param_1 + 0x110) = param_3;
  return;
}



// ==== 802a4bec  zz_02a4bec_ ====

int zz_02a4bec_(int param_1,uint param_2,int *param_3)

{
  uint uVar1;
  uint uVar2;
  
  *param_3 = *(int *)(param_1 + 0xe4);
  if (*param_3 == 0) {
    uVar2 = *(uint *)(param_1 + 0xdc);
    if ((int)uVar2 < 0) {
      return -1;
    }
    uVar1 = *(uint *)(param_1 + 0xe0);
  }
  else {
    uVar2 = *(uint *)(param_1 + 0x104);
    uVar1 = *(uint *)(param_1 + 0x108);
  }
  DAT_80430d00 = zz_02a953c_(uVar2,param_2,uVar1);
  DAT_80430d04 = uVar2;
  return DAT_80430d00;
}



// ==== 802a4c68  zz_02a4c68_ ====

int zz_02a4c68_(int param_1,uint param_2)

{
  int iVar1;
  
  if ((int)*(uint *)(param_1 + 0x118) < 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = zz_02a953c_(*(uint *)(param_1 + 0x118),param_2,0x57e4);
    DAT_80430d0c = *(undefined4 *)(param_1 + 0x118);
    DAT_80430d08 = iVar1;
  }
  return iVar1;
}



// ==== 802a4cc0  zz_02a4cc0_ ====

bool zz_02a4cc0_(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = cTeam__GetPlayer_int_(param_1,6);
  if (iVar3 == 0) {
    bVar1 = false;
  }
  else {
    iVar3 = cTeam__GetPlayer_int_(param_1,0x33);
    if (iVar3 == 0) {
      bVar1 = false;
    }
    else {
      iVar4 = cTeam__GetPlayer_int_(param_1,0x47);
      if (iVar4 == 1) {
        iVar2 = *(int *)(param_1 + 0xf24) - *(int *)(param_1 + 0xf4c);
        iVar4 = DAT_8041d3e4;
      }
      else {
        iVar4 = *(int *)(param_1 + 0xf5c);
        iVar2 = *(int *)(param_1 + 0xf58) - *(int *)(param_1 + 0xf4c);
      }
      if (iVar3 < iVar2 / iVar4) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
    }
  }
  if (bVar1) {
    zz_029abec_(param_1,-0xfffdde);
  }
  return bVar1;
}



// ==== 802a4da8  zz_02a4da8_ ====

void zz_02a4da8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  bool bVar1;
  int iVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined8 uVar7;
  int local_24;
  int local_20 [5];
  
  piVar6 = &DAT_8041d430;
  iVar5 = 0;
  DAT_8041d3dc = DAT_8041d3dc + 1;
  do {
    iVar4 = *piVar6;
    if (iVar4 != 0) {
      if (*(int *)(iVar4 + 0x48) == 4) {
        if (*(int *)(iVar4 + 0x50) == 0) {
          if (*(int *)(iVar4 + 0x964) == 0) {
            bVar1 = true;
          }
          else {
            bVar1 = false;
          }
        }
        else {
          bVar1 = false;
        }
      }
      else {
        bVar1 = false;
      }
      if (bVar1) {
        *(int *)(iVar4 + 0xf24) = *(int *)(iVar4 + 0xf24) + *(int *)(iVar4 + 0xf28);
      }
      if (*(int *)(iVar4 + 0xf48) == -1) {
        bVar1 = false;
      }
      else if (*(int *)(iVar4 + 0x4c) == 4) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (bVar1) {
        *(int *)(iVar4 + 0xf48) = *(int *)(iVar4 + 0xf48) + *(int *)(iVar4 + 0xf28);
      }
      iVar2 = cTeam__GetPlayer_int_(iVar4,0x47);
      if (iVar2 == 1) {
        zz_029aac8_();
        iVar2 = cTeam__GetPlayer_int_(iVar4,0xf);
        pcVar3 = *(code **)(iVar4 + iVar2 * 4 + 0xcc0);
        if (pcVar3 == (code *)0x0) {
          pcVar3 = FUN_802a48a8;
        }
        uVar7 = (*pcVar3)(iVar4,&local_24,local_20);
        zz_029aa9c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        if ((*(int *)(iVar4 + 0xf08) != local_24) || (*(int *)(iVar4 + 0xf0c) != local_20[0])) {
          iVar2 = cTeam__GetPlayer_int_(iVar4,0x47);
          if (iVar2 == 1) {
            *(undefined4 *)(iVar4 + 0xf4c) = *(undefined4 *)(iVar4 + 0xf24);
          }
          else {
            *(undefined4 *)(iVar4 + 0xf4c) = *(undefined4 *)(iVar4 + 0xf58);
          }
          *(int *)(iVar4 + 0xf08) = local_24;
          *(int *)(iVar4 + 0xf0c) = local_20[0];
        }
        *(undefined4 *)(iVar4 + 0x44) = 1;
      }
    }
    iVar5 = iVar5 + 1;
    piVar6 = piVar6 + 1;
  } while (iVar5 < 8);
  return;
}



// ==== 802a4f70  zz_02a4f70_ ====

int zz_02a4f70_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x250) + *(int *)(param_1 + 0x254);
  iVar1 = *(int *)(param_1 + 0x250) + *(int *)(param_1 + 600);
  if (param_2 < iVar2) {
    return iVar2;
  }
  if (param_2 < iVar1) {
    return iVar1;
  }
  return 0x7fffffff;
}



// ==== 802a4fa8  zz_02a4fa8_ ====

void zz_02a4fa8_(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0x250) == -5) {
    *(int *)(param_1 + 0x250) = param_2;
    return;
  }
  iVar4 = param_2 - *(int *)(param_1 + 0x250);
  if (iVar4 == 0) {
    return;
  }
  *(int *)(param_1 + 0x250) = param_2;
  iVar3 = iVar4;
  if (iVar4 < *(int *)(param_1 + 600)) {
    iVar3 = *(int *)(param_1 + 600);
  }
  *(int *)(param_1 + 600) = iVar3;
  iVar3 = iVar4;
  if (*(int *)(param_1 + 0x25c) < iVar4) {
    iVar3 = *(int *)(param_1 + 0x25c);
  }
  *(int *)(param_1 + 0x25c) = iVar3;
  iVar3 = *(int *)(param_1 + 0x254);
  if (iVar3 == 0x7fffffff) {
    *(int *)(param_1 + 0x254) = iVar4;
    return;
  }
  if (iVar3 <= iVar4) {
    *(int *)(param_1 + 0x254) = iVar4;
    return;
  }
  uVar1 = iVar3 - iVar4;
  iVar2 = ((int)uVar1 >> 3) + (uint)((int)uVar1 < 0 && (uVar1 & 7) != 0);
  if (iVar2 != 0) {
    *(int *)(param_1 + 0x254) = iVar3 - iVar2;
    return;
  }
  *(int *)(param_1 + 0x254) = iVar4;
  return;
}



// ==== 802a5044  zz_02a5044_ ====

void zz_02a5044_(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = param_2;
  param_1[9] = 1;
  return;
}



// ==== 802a5078  zz_02a5078_ ====

void zz_02a5078_(int param_1,int param_2)

{
  undefined4 uVar1;
  
  *(code **)(param_1 + 0xcc0) = FUN_802a48a8;
  *(undefined1 **)(param_1 + 0xcc4) = &LAB_802a4838;
  *(undefined4 *)(param_1 + 0xcc8) = 0;
  *(undefined1 **)(param_1 + 0xccc) = &LAB_802a47e0;
  *(undefined4 *)(param_1 + 0xcd0) = 0;
  *(code **)(param_1 + 0xcd4) = FUN_802a468c;
  *(undefined4 *)(param_2 + 0x18) = 0;
  *(undefined4 *)(param_2 + 0x94) = 0;
  *(undefined4 *)(param_2 + 0x98) = 0;
  *(undefined4 *)(param_2 + 0x9c) = 0;
  *(undefined4 *)(param_2 + 0xa0) = 0;
  *(undefined4 *)(param_2 + 0xa4) = 0;
  *(undefined4 *)(param_2 + 0xa8) = 0;
  *(undefined4 *)(param_2 + 0xac) = 0;
  *(undefined4 *)(param_2 + 0xb0) = 0;
  *(undefined4 *)(param_2 + 0xb4) = 0;
  *(undefined4 *)(param_2 + 0xb8) = 1;
  *(undefined4 *)(param_2 + 0x1c) = 0;
  *(undefined4 *)(param_2 + 0x20) = 0;
  *(undefined4 *)(param_2 + 0x24) = 0;
  *(undefined4 *)(param_2 + 0x28) = 0;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined4 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x38) = 0;
  *(undefined4 *)(param_2 + 0x3c) = 0x7fffffff;
  *(undefined4 *)(param_2 + 0x40) = 1;
  *(undefined4 *)(param_2 + 0x44) = 0;
  *(undefined4 *)(param_2 + 0x48) = 0;
  *(undefined4 *)(param_2 + 0x4c) = 0;
  *(undefined4 *)(param_2 + 0x50) = 0;
  *(undefined4 *)(param_2 + 0x54) = 0;
  *(undefined4 *)(param_2 + 0x58) = 0;
  *(undefined4 *)(param_2 + 0x5c) = 0;
  *(undefined4 *)(param_2 + 0x60) = 0;
  *(undefined4 *)(param_2 + 100) = 0xffffffff;
  *(undefined4 *)(param_2 + 0x68) = 1;
  *(undefined4 *)(param_2 + 0x6c) = 0;
  *(undefined4 *)(param_2 + 0x70) = 0;
  *(undefined4 *)(param_2 + 0x74) = 0;
  *(undefined4 *)(param_2 + 0x78) = 0;
  *(undefined4 *)(param_2 + 0x7c) = 0;
  *(undefined4 *)(param_2 + 0x80) = 0;
  *(undefined4 *)(param_2 + 0x84) = 0;
  *(undefined4 *)(param_2 + 0x88) = 0;
  *(undefined4 *)(param_2 + 0x8c) = 0xffffffff;
  *(undefined4 *)(param_2 + 0x90) = 1;
  *(undefined4 *)(param_2 + 0xbc) = 0;
  *(undefined4 *)(param_2 + 0xc0) = 0;
  *(undefined4 *)(param_2 + 0xc4) = 0;
  *(undefined4 *)(param_2 + 200) = 0;
  *(undefined4 *)(param_2 + 0xcc) = 0;
  *(undefined4 *)(param_2 + 0xd0) = 0;
  *(undefined4 *)(param_2 + 0xd4) = 0;
  *(undefined4 *)(param_2 + 0xd8) = 0;
  *(undefined4 *)(param_2 + 0xdc) = 0xffffffff;
  *(undefined4 *)(param_2 + 0xe0) = 1;
  *(undefined4 *)(param_2 + 0xe4) = 0;
  *(undefined4 *)(param_2 + 0xe8) = 0;
  *(undefined4 *)(param_2 + 0xec) = 0;
  *(undefined4 *)(param_2 + 0xf0) = 0;
  *(undefined4 *)(param_2 + 0xf4) = 0;
  *(undefined4 *)(param_2 + 0xf8) = 0;
  *(undefined4 *)(param_2 + 0xfc) = 0;
  *(undefined4 *)(param_2 + 0x100) = 0;
  *(undefined4 *)(param_2 + 0x104) = 0x7fffffff;
  *(undefined4 *)(param_2 + 0x108) = 1;
  *(undefined4 *)(param_2 + 0x10c) = 0;
  *(undefined4 *)(param_2 + 0x110) = 0;
  *(undefined4 *)(param_2 + 0x114) = 0xffffffff;
  *(undefined4 *)(param_2 + 0x118) = 0xffffffff;
  *(undefined4 *)(param_2 + 0x11c) = 0;
  *(undefined4 *)(param_2 + 0x120) = 0;
  *(undefined4 *)(param_2 + 0x124) = 0;
  *(undefined4 *)(param_2 + 0x128) = 0;
  *(undefined4 *)(param_2 + 300) = 0;
  *(undefined4 *)(param_2 + 0x130) = 0;
  *(undefined4 *)(param_2 + 0x134) = 0;
  *(undefined4 *)(param_2 + 0x138) = 0;
  *(undefined4 *)(param_2 + 0x13c) = 0;
  *(undefined4 *)(param_2 + 0x140) = 0;
  *(undefined4 *)(param_2 + 0x144) = 0;
  *(undefined4 *)(param_2 + 0x148) = 0;
  *(undefined4 *)(param_2 + 0x14c) = 0;
  *(undefined4 *)(param_2 + 0x150) = 0;
  *(undefined4 *)(param_2 + 0x154) = 0;
  *(undefined4 *)(param_2 + 0x158) = 0;
  *(undefined4 *)(param_2 + 0x15c) = 0;
  *(undefined4 *)(param_2 + 0x160) = 0;
  *(undefined4 *)(param_2 + 0x164) = 0;
  *(undefined4 *)(param_2 + 0x168) = 0;
  *(undefined4 *)(param_2 + 0x16c) = 0;
  *(undefined4 *)(param_2 + 0x170) = 0;
  *(undefined4 *)(param_2 + 0x174) = 0;
  *(undefined4 *)(param_2 + 0x178) = 0;
  *(undefined4 *)(param_2 + 0x17c) = 0;
  *(undefined4 *)(param_2 + 0x180) = 0;
  *(undefined4 *)(param_2 + 0x184) = 0;
  *(undefined4 *)(param_2 + 0x188) = 0;
  *(undefined4 *)(param_2 + 0x18c) = 0;
  *(undefined4 *)(param_2 + 400) = 0;
  *(undefined4 *)(param_2 + 0x194) = 0;
  *(undefined4 *)(param_2 + 0x198) = 0;
  *(undefined4 *)(param_2 + 0x19c) = 0;
  *(undefined4 *)(param_2 + 0x1a0) = 0;
  *(undefined4 *)(param_2 + 0x1a4) = 0;
  *(undefined4 *)(param_2 + 0x1a8) = 1;
  *(undefined4 *)(param_2 + 0x1ac) = 0;
  *(undefined4 *)(param_2 + 0x1b0) = 0;
  *(undefined4 *)(param_2 + 0x1b4) = 0;
  *(undefined4 *)(param_2 + 0x1b8) = 0;
  *(undefined4 *)(param_2 + 0x1bc) = 0;
  *(undefined4 *)(param_2 + 0x1c0) = 0;
  *(undefined4 *)(param_2 + 0x1c4) = 0;
  *(undefined4 *)(param_2 + 0x1c8) = 0;
  *(undefined4 *)(param_2 + 0x1cc) = 0;
  *(undefined4 *)(param_2 + 0x1d0) = 0;
  *(undefined4 *)(param_2 + 0x1d4) = 0;
  *(undefined4 *)(param_2 + 0x1d8) = 0;
  *(undefined4 *)(param_2 + 0x1dc) = 0;
  *(undefined4 *)(param_2 + 0x1e0) = 0;
  *(undefined4 *)(param_2 + 0x1e4) = 0;
  *(undefined4 *)(param_2 + 0x1e8) = 0;
  *(undefined4 *)(param_2 + 0x1ec) = 0;
  *(undefined4 *)(param_2 + 0x1f0) = 0;
  *(undefined4 *)(param_2 + 500) = 0;
  *(undefined4 *)(param_2 + 0x1f8) = 0;
  *(undefined4 *)(param_2 + 0x1fc) = 0;
  *(undefined4 *)(param_2 + 0x200) = 0;
  *(undefined4 *)(param_2 + 0x204) = 0;
  *(undefined4 *)(param_2 + 0x208) = 0;
  *(undefined4 *)(param_2 + 0x20c) = 0;
  *(undefined4 *)(param_2 + 0x210) = 0;
  *(undefined4 *)(param_2 + 0x214) = 0;
  *(undefined4 *)(param_2 + 0x218) = 0;
  *(undefined4 *)(param_2 + 0x21c) = 0;
  *(undefined4 *)(param_2 + 0x220) = 0;
  *(undefined4 *)(param_2 + 0x224) = 0;
  *(undefined4 *)(param_2 + 0x228) = 0;
  *(undefined4 *)(param_2 + 0x22c) = 0;
  *(undefined4 *)(param_2 + 0x230) = 0;
  *(undefined4 *)(param_2 + 0x234) = 0;
  *(undefined4 *)(param_2 + 0x238) = 0xfffffffb;
  *(undefined4 *)(param_2 + 0x23c) = 1;
  *(undefined4 *)(param_2 + 0x240) = 0xfffffffb;
  uVar1 = DAT_802b8e54;
  *(undefined4 *)(param_2 + 0x244) = 1;
  *(undefined4 *)(param_2 + 0x248) = 0xfffffffb;
  *(undefined4 *)(param_2 + 0x24c) = 1;
  *(undefined4 *)(param_2 + 0x250) = 0xfffffffb;
  *(undefined4 *)(param_2 + 0x254) = 0x7fffffff;
  *(undefined4 *)(param_2 + 600) = 0;
  *(undefined4 *)(param_2 + 0x25c) = 0x7fffffff;
  *(undefined4 *)(param_2 + 0x260) = 0;
  *(undefined4 *)(param_2 + 0x264) = 0;
  *(undefined4 *)(param_2 + 0x268) = 1000;
  *(undefined4 *)(param_2 + 0x26c) = 0;
  *(undefined4 *)(param_2 + 0x270) = 0;
  *(undefined4 *)(param_2 + 0x274) = 1;
  *(undefined4 *)(param_2 + 0x278) = 100;
  *(undefined4 *)(param_2 + 0x27c) = uVar1;
  *(undefined4 *)(param_2 + 0x280) = 0;
  *(undefined4 *)(param_2 + 0x284) = uVar1;
  *(undefined4 *)(param_2 + 0x288) = 0xffffffff;
  *(undefined4 *)(param_2 + 0x28c) = *(undefined4 *)(param_2 + 0x264);
  *(undefined4 *)(param_2 + 0x290) = 0;
  *(undefined4 *)(param_2 + 0x294) = 0xfffffffb;
  *(undefined4 *)(param_2 + 0x298) = 0;
  *(undefined4 *)(param_2 + 0x29c) = 1;
  return;
}



// ==== 802a5398  zz_02a5398_ ====

void zz_02a5398_(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = param_2;
  return;
}



// ==== 802a53ac  zz_02a53ac_ ====

uint zz_02a53ac_(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + param_2 * 0x44 + 0x1aac);
  return (-uVar1 | uVar1) >> 0x1f;
}



// ==== 802a53c8  zz_02a53c8_ ====

undefined4 zz_02a53c8_(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + param_2 * 0x44 + 0x1aa4);
}



// ==== 802a53d8  zz_02a53d8_ ====

void zz_02a53d8_(int param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + param_2 * 0x44 + 0x1aa4) = param_3;
  return;
}



// ==== 802a53e8  zz_02a53e8_ ====

undefined4 zz_02a53e8_(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + param_2 * 0x44 + 0x1aa0);
}



// ==== 802a53f8  zz_02a53f8_ ====

void zz_02a53f8_(int param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + param_2 * 0x44 + 0x1aa0) = param_3;
  return;
}



// ==== 802a5408  zz_02a5408_ ====

undefined4 zz_02a5408_(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + param_2 * 0x44 + 0x1aac);
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = (**(code **)(iVar2 + param_3 * 4))(param_1,param_4,param_5,0);
  }
  return uVar1;
}



// ==== 802a545c  zz_02a545c_ ====

int zz_02a545c_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = param_1 + 0x1aa0;
  iVar1 = 0;
  while ((*(int *)(iVar2 + 0xc) == 0 ||
         (iVar1 = (**(code **)(param_2 * 4 + *(int *)(iVar2 + 0xc)))(param_1,0,0,0), iVar1 == 0))) {
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 0x44;
    if (8 < iVar3) {
      return iVar1;
    }
  }
  return iVar1;
}



// ==== 802a54ec  zz_02a54ec_ ====

void zz_02a54ec_(int param_1,int param_2)

{
  *(undefined4 *)(param_1 + 0x1190) = 1;
  *(undefined4 *)(param_1 + 0x1af4) = 0;
  if (*(int *)(param_2 + 8) == 0) {
    zz_02a39d8_(param_1,5,0);
    *(undefined4 *)(param_1 + 0xb44) = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0x1af8) = 1;
    *(undefined4 *)(param_1 + 0x1200) = 1;
    *(undefined4 *)(param_1 + 0x1204) = 2;
    *(undefined4 *)(param_1 + 0x1b38) = 1;
    *(undefined4 *)(param_1 + 0x1b3c) = 3;
    *(undefined4 *)(param_1 + 0x12e8) = 2;
    if (*(int *)(param_2 + 0x10) == 0) {
      *(undefined4 *)(param_1 + 0x12ec) = 6;
      *(undefined4 *)(param_1 + 0x1c48) = 3;
    }
    else {
      *(undefined4 *)(param_1 + 0x12ec) = 4;
      *(undefined4 *)(param_1 + 0x1bc0) = 3;
      *(undefined4 *)(param_1 + 0x1bc4) = 5;
      *(undefined4 *)(param_1 + 0x13d0) = 4;
      *(undefined4 *)(param_1 + 0x13d4) = 6;
      *(undefined4 *)(param_1 + 0x1c48) = 5;
    }
  }
  if (*(int *)(param_2 + 0xc) == 0) {
    zz_02a39d8_(param_1,6,0);
    *(undefined4 *)(param_1 + 0xb48) = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0x1afc) = 2;
    *(undefined4 *)(param_1 + 0x1274) = 1;
    *(undefined4 *)(param_1 + 0x1278) = 3;
    *(undefined4 *)(param_1 + 0x1b7c) = 2;
    *(undefined4 *)(param_1 + 0x1b80) = 4;
    *(undefined4 *)(param_1 + 0x135c) = 3;
    if (*(int *)(param_2 + 0x14) == 0) {
      *(undefined4 *)(param_1 + 0x1360) = 7;
      *(undefined4 *)(param_1 + 0x1c8c) = 4;
    }
    else {
      *(undefined4 *)(param_1 + 0x1360) = 5;
      *(undefined4 *)(param_1 + 0x1c04) = 4;
      *(undefined4 *)(param_1 + 0x1c08) = 6;
      *(undefined4 *)(param_1 + 0x1444) = 5;
      *(undefined4 *)(param_1 + 0x1448) = 7;
      *(undefined4 *)(param_1 + 0x1c8c) = 6;
    }
  }
  if (*(int *)(param_2 + 0x20) != 0) {
    *(undefined4 *)(param_1 + 0x1b00) = 7;
    *(undefined4 *)(param_1 + 0x14b8) = 1;
    *(undefined4 *)(param_1 + 0x14bc) = 8;
    *(undefined4 *)(param_1 + 0x1cd0) = 7;
  }
  return;
}



// ==== 802a566c  zz_02a566c_ ====

undefined4 zz_02a566c_(int param_1,int param_2)

{
  if (*(int *)(param_2 + 4) == 0) {
    if (*(int *)(param_2 + 8) == 0) {
      if (*(int *)(param_2 + 0xc) == 0) {
        if (*(int *)(param_2 + 0x20) == 0) {
          return 0xffffffff;
        }
        *(undefined4 *)(param_1 + 0x1ab4) = 7;
        *(undefined4 *)(param_1 + 0x14b8) = 0;
        *(undefined4 *)(param_1 + 0x14bc) = 8;
        *(undefined4 *)(param_1 + 0x1cd0) = 7;
        zz_02a39d8_(param_1,6,0);
        zz_02a39d8_(param_1,5,0);
        *(undefined4 *)(param_1 + 0xb48) = 0;
        *(undefined4 *)(param_1 + 0xb44) = 0;
      }
      else {
        *(undefined4 *)(param_1 + 0x1ab4) = 2;
        *(undefined4 *)(param_1 + 0x1274) = 0;
        *(undefined4 *)(param_1 + 0x1278) = 3;
        *(undefined4 *)(param_1 + 0x1b7c) = 2;
        *(undefined4 *)(param_1 + 0x1b80) = 4;
        *(undefined4 *)(param_1 + 0x135c) = 3;
        if (*(int *)(param_2 + 0x14) == 0) {
          *(undefined4 *)(param_1 + 0x1360) = 7;
          *(undefined4 *)(param_1 + 0x1c8c) = 4;
        }
        else {
          *(undefined4 *)(param_1 + 0x1360) = 5;
          *(undefined4 *)(param_1 + 0x1c04) = 4;
          *(undefined4 *)(param_1 + 0x1c08) = 6;
          *(undefined4 *)(param_1 + 0x1444) = 5;
          *(undefined4 *)(param_1 + 0x1448) = 7;
          *(undefined4 *)(param_1 + 0x1c8c) = 6;
        }
        zz_02a39d8_(param_1,5,0);
        *(undefined4 *)(param_1 + 0xb44) = 0;
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x1ab4) = 1;
      *(undefined4 *)(param_1 + 0x1200) = 0;
      *(undefined4 *)(param_1 + 0x1204) = 2;
      *(undefined4 *)(param_1 + 0x1b38) = 1;
      *(undefined4 *)(param_1 + 0x1b3c) = 3;
      *(undefined4 *)(param_1 + 0x12e8) = 2;
      if (*(int *)(param_2 + 0x10) == 0) {
        *(undefined4 *)(param_1 + 0x12ec) = 6;
        *(undefined4 *)(param_1 + 0x1c48) = 3;
      }
      else {
        *(undefined4 *)(param_1 + 0x12ec) = 4;
        *(undefined4 *)(param_1 + 0x1bc0) = 3;
        *(undefined4 *)(param_1 + 0x1bc4) = 5;
        *(undefined4 *)(param_1 + 0x13d0) = 4;
        *(undefined4 *)(param_1 + 0x13d4) = 6;
        *(undefined4 *)(param_1 + 0x1c48) = 5;
      }
      zz_02a39d8_(param_1,6,0);
      *(undefined4 *)(param_1 + 0xb48) = 0;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x1ab4) = 0;
    *(undefined4 *)(param_1 + 0x118c) = 0;
    zz_02a54ec_(param_1,param_2);
  }
  return 0;
}



// ==== 802a5834  zz_02a5834_ ====

int zz_02a5834_(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  puVar3 = (undefined4 *)*param_3;
  iVar4 = 3;
  puVar2 = puVar3;
  do {
    param_2[2] = 0;
    uVar1 = *puVar2;
    param_2[1] = 0;
    *param_2 = 0;
    param_2[3] = uVar1;
    param_2[4] = 8;
    param_2[5] = 8;
    param_2[6] = 8;
    param_2[7] = 8;
    param_2[8] = 0xffffffff;
    param_2[0x13] = 0;
    uVar1 = puVar2[1];
    param_2[0x12] = 0;
    param_2[0x11] = 0;
    param_2[0x14] = uVar1;
    param_2[0x15] = 8;
    param_2[0x16] = 8;
    param_2[0x17] = 8;
    param_2[0x18] = 8;
    param_2[0x19] = 0xffffffff;
    param_2[0x24] = 0;
    uVar1 = puVar2[2];
    puVar2 = puVar2 + 3;
    param_2[0x23] = 0;
    param_2[0x22] = 0;
    param_2[0x25] = uVar1;
    param_2[0x26] = 8;
    param_2[0x27] = 8;
    param_2[0x28] = 8;
    param_2[0x29] = 8;
    param_2[0x2a] = 0xffffffff;
    param_2 = param_2 + 0x33;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar4 = zz_02a566c_(param_1,(int)puVar3);
  if (iVar4 == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = zz_029abec_(param_1,-0xfffcfe);
  }
  return iVar4;
}



// ==== 802a5928  zz_02a5928_ ====

int zz_02a5928_(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = param_2[1];
  *param_1 = *param_2;
  param_1[1] = iVar1;
  iVar1 = param_2[3];
  param_1[2] = param_2[2];
  param_1[3] = iVar1;
  iVar1 = param_2[5];
  param_1[4] = param_2[4];
  param_1[5] = iVar1;
  iVar1 = param_2[7];
  param_1[6] = param_2[6];
  param_1[7] = iVar1;
  iVar1 = param_2[9];
  param_1[8] = param_2[8];
  param_1[9] = iVar1;
  iVar1 = param_2[0xb];
  param_1[10] = param_2[10];
  param_1[0xb] = iVar1;
  iVar1 = param_2[0xd];
  param_1[0xc] = param_2[0xc];
  param_1[0xd] = iVar1;
  param_1[0xe] = param_2[0xe];
  while( true ) {
    if ((undefined4 *)*param_2 == (undefined4 *)0x0) {
      return 0;
    }
    iVar1 = (**(code **)*param_2)(0,0,0,0);
    if (iVar1 != 0) break;
    iVar2 = iVar2 + 1;
    param_2 = param_2 + 1;
    if (0xe < iVar2) {
      return 0;
    }
  }
  return iVar1;
}



// ==== 802a5a24  FUN_802a5a24 ====

void FUN_802a5a24(int param_1)

{
  zz_029abec_(param_1,-0xfff9ff);
  return;
}



// ==== 802a5a4c  FUN_802a5a4c ====

void FUN_802a5a4c(int param_1)

{
  zz_029abec_(param_1,-0xfff9ff);
  return;
}



// ==== 802a5a74  FUN_802a5a74 ====

void FUN_802a5a74(int param_1)

{
  zz_029abec_(param_1,-0xfff9ff);
  return;
}



// ==== 802a5a9c  FUN_802a5a9c ====

void FUN_802a5a9c(int param_1)

{
  zz_029abec_(param_1,-0xfff9ff);
  return;
}



// ==== 802a5aec  FUN_802a5aec ====

undefined4 FUN_802a5aec(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_1 + 0x2864;
  iVar3 = 0;
  *(int *)(param_1 + 0x1cc8) = iVar2;
  iVar1 = *(int *)(param_1 + 0x1cd0);
  *(undefined4 *)(param_1 + 0x2864) = 0;
  do {
    *(undefined4 *)(iVar2 + 4) = 0;
    *(undefined4 *)(iVar2 + 8) = 0;
    *(undefined4 *)(iVar2 + 0xc) = 0;
    *(undefined4 *)(iVar2 + 0x10) = 0;
    zz_029948c_(param_1,iVar1,iVar3,(undefined4 *)(iVar2 + 4));
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 0x10;
  } while (iVar3 < 3);
  return 0;
}



// ==== 802a5b64  FUN_802a5b64 ====

undefined4 FUN_802a5b64(int param_1)

{
  int iVar1;
  
  iVar1 = zz_02a53c8_(param_1,8);
  if ((iVar1 != 1) && (iVar1 = zz_0298b20_(param_1,*(int *)(param_1 + 0x1cd0)), iVar1 == 1)) {
    zz_02a53d8_(param_1,8,1);
  }
  iVar1 = zz_02a53e8_(param_1,8);
  if ((iVar1 != 1) && (iVar1 = zz_0298b40_(param_1,*(int *)(param_1 + 0x1cd0)), iVar1 == 1)) {
    zz_02a53f8_(param_1,8,1);
  }
  return 0;
}



// ==== 802a5c0c  zz_02a5c0c_ ====

int zz_02a5c0c_(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    iVar1 = *(int *)(param_1 + 0x1cd0);
    iVar3 = *(int *)(param_1 + 0x1cc8);
    if (iVar1 == 8) {
      iVar1 = zz_029abec_(param_1,-0xfff9fe);
    }
    else {
      iVar2 = iVar3 + param_2 * 0x10;
      *(undefined4 *)(iVar2 + 4) = param_3;
      *(undefined4 *)(iVar2 + 8) = param_4;
      *(undefined4 *)(iVar2 + 0xc) = 0;
      *(undefined4 *)(iVar2 + 0x10) = 0;
      zz_029948c_(param_1,iVar1,param_2,(undefined4 *)(iVar3 + param_2 * 0x10 + 4));
      iVar1 = 0;
    }
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffe6f);
  }
  return iVar1;
}



// ==== 802a5cd8  FUN_802a5cd8 ====

void FUN_802a5cd8(int param_1,undefined4 param_2)

{
  zz_0298b60_(param_1,*(int *)(param_1 + 0x1c48),param_2);
  return;
}



// ==== 802a5d00  FUN_802a5d00 ====

int FUN_802a5d00(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int *param_10)

{
  int iVar1;
  
  if (*(int *)(param_9 + 0x48) - 3U < 2) {
    iVar1 = zz_0298bc4_(param_9,*(int *)(param_9 + 0x1c48),param_10);
    if (iVar1 == 0) {
      iVar1 = zz_02a40ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          *param_10);
      if (iVar1 == 0) {
        iVar1 = 0;
        *param_10 = 0;
      }
      else {
        iVar1 = 0;
      }
    }
  }
  else {
    iVar1 = 0;
    *param_10 = 0;
  }
  return iVar1;
}



// ==== 802a5d94  FUN_802a5d94 ====

void FUN_802a5d94(int param_1)

{
  zz_029abec_(param_1,-0xfff8ff);
  return;
}



// ==== 802a5dbc  FUN_802a5dbc ====

void FUN_802a5dbc(int param_1)

{
  zz_029abec_(param_1,-0xfff8ff);
  return;
}



// ==== 802a5e14  FUN_802a5e14 ====

undefined4
FUN_802a5e14(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = cTeam__GetPlayer_int_(param_9,5);
  if (iVar2 != 0) {
    iVar2 = zz_02a53c8_(param_9,6);
    if ((iVar2 != 1) && (iVar2 = zz_0298b20_(param_9,*(int *)(param_9 + 0x1c48)), iVar2 == 1)) {
      iVar2 = cTeam__GetPlayer_int_(param_9,0xf);
      if (iVar2 == 0) {
        bVar1 = true;
      }
      else {
        iVar2 = zz_02a3cb8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9)
        ;
        if (iVar2 == 0) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
      }
      if (bVar1) {
        zz_02a53d8_(param_9,6,1);
      }
    }
    iVar2 = zz_02a53e8_(param_9,6);
    if ((iVar2 != 1) && (iVar2 = zz_0298b40_(param_9,*(int *)(param_9 + 0x1c48)), iVar2 == 1)) {
      zz_02a53f8_(param_9,6,1);
    }
  }
  return 0;
}



// ==== 802a5f18  zz_02a5f18_ ====

void zz_02a5f18_(int *param_1,undefined4 param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 + param_4;
  *param_1 = *param_1 + param_3 + CARRY4(uVar1,param_4);
  uVar1 = param_1[2];
  uVar2 = param_1[3];
  if ((param_3 ^ 0x80000000) < (uint)(param_4 < (uint)param_1[3]) + (param_1[2] ^ 0x80000000U)) {
    uVar1 = param_3;
    uVar2 = param_4;
  }
  param_1[3] = uVar2;
  param_1[2] = uVar1;
  uVar1 = param_1[4];
  uVar2 = param_1[5];
  if ((uVar1 ^ 0x80000000) < (uint)(uVar2 < param_4) + (param_3 ^ 0x80000000)) {
    uVar1 = param_3;
    uVar2 = param_4;
  }
  param_1[5] = uVar2;
  param_1[4] = uVar1;
  param_1[6] = param_1[6] + 1;
  return;
}



// ==== 802a5fac  zz_02a5fac_ ====

void zz_02a5fac_(undefined4 *param_1)

{
  param_1[1] = 0;
  *param_1 = 0;
  param_1[3] = 0xffffffff;
  param_1[2] = 0x7fffffff;
  param_1[5] = 0;
  param_1[4] = 0;
  param_1[6] = 0;
  return;
}



// ==== 802a5fdc  zz_02a5fdc_ ====

void zz_02a5fdc_(int *param_1,uint *param_2,int *param_3,uint *param_4)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  ulonglong uVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  undefined8 uVar21;
  double dVar22;
  double dVar23;
  longlong lVar24;
  longlong lVar25;
  longlong lVar26;
  char acStack_158 [256];
  longlong local_58;
  undefined4 local_50;
  uint uStack_4c;
  longlong local_48;
  longlong local_40;
  
  if (param_3[3] == 1 && param_3[2] == 0) {
    uVar21 = *(undefined8 *)(param_2 + 2);
    *(undefined8 *)param_4 = *(undefined8 *)param_2;
    *(undefined8 *)(param_4 + 2) = uVar21;
  }
  else {
    uVar13 = *param_2;
    uVar14 = param_2[1];
    if ((uVar13 ^ 0x80000000) < (uint)(uVar14 < (uint)param_1[99]) + (param_1[0x62] ^ 0x80000000U))
    {
      uVar13 = param_1[0x62];
      uVar14 = param_1[99];
    }
    param_2[1] = uVar14;
    *param_2 = uVar13;
    if (*param_1 == 1) {
      param_1[1] = 0;
    }
    else if (param_1[1] == 0) {
      if ((param_1[0x62] ^ 0x80000000U) <
          (uint)((uint)param_1[99] < param_2[1]) + (*param_2 ^ 0x80000000)) {
        param_1[1] = 1;
        if (param_1[0x5f] == -1 && param_1[0x5e] == -1) {
          uVar14 = param_2[3];
          uVar13 = param_1[0x57];
          lVar26 = gnt4___div2i((int)((ulonglong)uVar14 * (ulonglong)uVar13 >> 0x20) +
                                param_2[2] * uVar13 + uVar14 * param_1[0x56],uVar14 * uVar13,
                                param_1[0x58],param_1[0x59]);
        }
        else {
          uVar14 = param_2[3];
          uVar13 = param_1[0x5b];
          lVar26 = gnt4___div2i((int)((ulonglong)uVar14 * (ulonglong)uVar13 >> 0x20) +
                                param_2[2] * uVar13 + uVar14 * param_1[0x5a],uVar14 * uVar13,
                                param_1[0x5c],param_1[0x5d]);
        }
        iVar10 = *param_3;
        param_1[0x5f] = param_3[1];
        param_1[0x5e] = iVar10;
        *(longlong *)(param_1 + 0x60) = lVar26 + *(longlong *)param_2;
        gnt4_memset(param_1 + 5,0,0xf0);
        param_1[4] = 0;
        param_1[0x67] = param_1[0x67] + 1;
      }
      else if (param_1[2] == 0) {
        param_1[1] = 1;
      }
    }
    uVar13 = *param_2;
    uVar14 = param_2[1];
    if ((uVar13 ^ 0x80000000) < (uint)(uVar14 < (uint)param_1[99]) + (param_1[0x62] ^ 0x80000000U))
    {
      uVar13 = param_1[0x62];
      uVar14 = param_1[99];
    }
    param_1[99] = uVar14;
    param_1[0x62] = uVar13;
    uVar13 = param_1[0x5f];
    if (uVar13 == 0xffffffff && param_1[0x5e] == -1) {
      lVar26 = 0;
    }
    else {
      uVar16 = param_2[3];
      uVar14 = param_3[1] - uVar13;
      lVar26 = gnt4___div2i((int)((ulonglong)uVar16 * (ulonglong)uVar14 >> 0x20) +
                            param_2[2] * uVar14 +
                            uVar16 * (*param_3 - ((uint)((uint)param_3[1] < uVar13) + param_1[0x5e])
                                     ),uVar16 * uVar14,param_3[2],param_3[3]);
      lVar26 = lVar26 + *(longlong *)(param_1 + 0x60);
    }
    uVar13 = (uint)((ulonglong)lVar26 >> 0x20);
    uVar14 = (uint)lVar26;
    if (param_1[1] == 0) {
      if ((param_1[0x62] ^ 0x80000000U) < (uint)((uint)param_1[99] < uVar14) + (uVar13 ^ 0x80000000)
         ) {
        if (param_1[2] == 0) {
          iVar10 = *param_3;
          param_1[0x5f] = param_3[1];
          param_1[0x5e] = iVar10;
          param_1[0x61] = param_1[0x4b];
          param_1[0x60] = param_1[0x4a];
        }
        else {
          iVar10 = *param_3;
          param_1[0x5f] = param_3[1];
          param_1[0x5e] = iVar10;
          param_1[0x61] = param_1[99];
          param_1[0x60] = param_1[0x62];
        }
        param_1[100] = param_1[100] + 1;
      }
    }
    else if (param_1[2] == 1) {
      uVar16 = param_2[1] - uVar14;
      uVar14 = *param_2 - ((param_2[1] < uVar14) + uVar13);
      uVar13 = uVar16;
      if ((uVar14 ^ 0x80000000) < 0x80000000) {
        uVar14 = -((uVar16 != 0) + uVar14);
        uVar13 = -uVar16;
      }
      uVar18 = param_2[3];
      uVar17 = param_1[0x53];
      uVar21 = gnt4___div2i((int)((ulonglong)uVar18 * (ulonglong)uVar17 >> 0x20) +
                            param_2[2] * uVar17 + uVar18 * param_1[0x52],uVar18 * uVar17,
                            param_1[0x54],param_1[0x55]);
      if (((uint)((ulonglong)uVar21 >> 0x20) ^ 0x80000000) <
          (uint)((uint)uVar21 < uVar13) + (uVar14 ^ 0x80000000)) {
        iVar10 = *param_3;
        param_1[0x5f] = param_3[1];
        param_1[0x5e] = iVar10;
        uVar13 = *param_2;
        param_1[0x61] = param_2[1];
        param_1[0x60] = uVar13;
        gnt4_memset(param_1 + 5,0,0xf0);
        param_1[4] = 0;
        param_1[0x67] = param_1[0x67] + 1;
        param_1[0x68] = param_1[0x68] + 1;
      }
      else {
        iVar20 = param_1[4];
        iVar10 = 0;
        iVar19 = 0;
        param_1[4] = iVar20 + 1;
        param_1[(iVar20 - (iVar20 / param_1[3]) * param_1[3]) + 5] = uVar16;
        iVar20 = param_1[3];
        if (0 < iVar20) {
          if ((8 < iVar20) && (uVar13 = iVar20 - 1U >> 3, piVar11 = param_1, 0 < iVar20 + -8)) {
            do {
              piVar1 = piVar11 + 5;
              iVar19 = iVar19 + 8;
              piVar2 = piVar11 + 6;
              piVar3 = piVar11 + 7;
              piVar4 = piVar11 + 8;
              piVar5 = piVar11 + 9;
              piVar6 = piVar11 + 10;
              piVar7 = piVar11 + 0xb;
              piVar8 = piVar11 + 0xc;
              piVar11 = piVar11 + 8;
              iVar10 = iVar10 + *piVar1 + *piVar2 + *piVar3 + *piVar4 + *piVar5 + *piVar6 + *piVar7
                       + *piVar8;
              uVar13 = uVar13 - 1;
            } while (uVar13 != 0);
          }
          iVar12 = iVar20 - iVar19;
          piVar11 = param_1 + iVar19;
          if (iVar19 < iVar20) {
            do {
              piVar1 = piVar11 + 5;
              piVar11 = piVar11 + 1;
              iVar10 = iVar10 + *piVar1;
              iVar12 = iVar12 + -1;
            } while (iVar12 != 0);
          }
        }
        uVar16 = iVar10 / iVar20;
        param_1[0x69] = uVar16;
        uVar15 = (int)uVar16 >> 0x1f;
        param_1[0x6a] = uVar16;
        uVar14 = param_2[3];
        uVar13 = param_1[0x4f];
        lVar24 = gnt4___div2i((int)((ulonglong)uVar14 * (ulonglong)uVar13 >> 0x20) +
                              param_2[2] * uVar13 + uVar14 * param_1[0x4e],uVar14 * uVar13,
                              param_1[0x50],param_1[0x51]);
        uVar17 = (uint)((ulonglong)lVar24 >> 0x20);
        uVar18 = (uint)lVar24;
        uVar13 = uVar15;
        uVar14 = uVar16;
        if ((uVar15 ^ 0x80000000) < 0x80000000) {
          uVar13 = -((uVar16 != 0) + uVar15);
          uVar14 = -uVar16;
        }
        if ((uVar17 ^ 0x80000000) < (uint)(uVar18 < uVar14) + (uVar13 ^ 0x80000000)) {
          if ((uVar17 ^ 0x80000000) < (uint)(uVar18 < uVar16) + (uVar15 ^ 0x80000000)) {
            lVar25 = gnt4___div2i(uVar16 >> 0x1f | uVar15 << 1,uVar16 << 1,uVar17,uVar18);
            lVar25 = lVar25 + -1;
            param_1[0x65] = param_1[0x65] + (int)lVar25;
          }
          else {
            lVar25 = gnt4___div2i(uVar16 >> 0x1f | uVar15 << 1,uVar16 << 1,uVar17,uVar18);
            lVar25 = lVar25 + 1;
            param_1[0x66] = param_1[0x66] - (int)lVar25;
          }
          iVar10 = *param_3;
          param_1[0x5f] = param_3[1];
          param_1[0x5e] = iVar10;
          uVar9 = lVar24 * lVar25;
          uVar13 = (uint)(uVar9 & 0xfffffffe00000001);
          uVar14 = uVar13 | (uint)((uVar9 & 0xfffffffe00000001) >> 0x20);
          uVar16 = (int)(uVar9 >> 0x20) << 0x1f | (uint)uVar9 >> 1;
          uVar13 = (uint)((int)uVar14 < 0 && uVar13 != 0);
          iVar10 = uVar16 + uVar13;
          *(longlong *)(param_1 + 0x60) =
               lVar26 + CONCAT44(((int)uVar14 >> 1) + (uint)CARRY4(uVar16,uVar13),iVar10);
          piVar11 = param_1;
          for (iVar19 = 0; iVar20 = param_1[3], iVar19 < iVar20; iVar19 = iVar19 + 1) {
            piVar11[5] = piVar11[5] - iVar10;
            piVar11 = piVar11 + 1;
          }
          iVar10 = 0;
          iVar19 = 0;
          if (0 < iVar20) {
            if ((8 < iVar20) && (uVar13 = iVar20 - 1U >> 3, piVar11 = param_1, 0 < iVar20 + -8)) {
              do {
                piVar1 = piVar11 + 5;
                iVar19 = iVar19 + 8;
                piVar2 = piVar11 + 6;
                piVar3 = piVar11 + 7;
                piVar4 = piVar11 + 8;
                piVar5 = piVar11 + 9;
                piVar6 = piVar11 + 10;
                piVar7 = piVar11 + 0xb;
                piVar8 = piVar11 + 0xc;
                piVar11 = piVar11 + 8;
                iVar10 = iVar10 + *piVar1 + *piVar2 + *piVar3 + *piVar4 + *piVar5 + *piVar6 +
                         *piVar7 + *piVar8;
                uVar13 = uVar13 - 1;
              } while (uVar13 != 0);
            }
            iVar12 = iVar20 - iVar19;
            piVar11 = param_1 + iVar19;
            if (iVar19 < iVar20) {
              do {
                piVar1 = piVar11 + 5;
                piVar11 = piVar11 + 1;
                iVar10 = iVar10 + *piVar1;
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
            }
          }
          param_1[0x6a] = iVar10 / iVar20;
        }
      }
    }
    uVar13 = param_1[0x5f];
    if (uVar13 == 0xffffffff && param_1[0x5e] == -1) {
      lVar26 = 0;
    }
    else {
      uVar16 = param_2[3];
      uVar14 = param_3[1] - uVar13;
      lVar26 = gnt4___div2i((int)((ulonglong)uVar16 * (ulonglong)uVar14 >> 0x20) +
                            param_2[2] * uVar14 +
                            uVar16 * (*param_3 - ((uint)((uint)param_3[1] < uVar13) + param_1[0x5e])
                                     ),uVar16 * uVar14,param_3[2],param_3[3]);
      lVar26 = lVar26 + *(longlong *)(param_1 + 0x60);
    }
    *(longlong *)param_4 = lVar26;
    uVar13 = param_2[2];
    param_4[3] = param_2[3];
    param_4[2] = uVar13;
    if ((*param_4 ^ 0x80000000) <
        (uint)(param_4[1] < (uint)param_1[0x4b]) + (param_1[0x4a] ^ 0x80000000U)) {
      uVar21 = *(undefined8 *)(param_1 + 0x4c);
      *(undefined8 *)param_4 = *(undefined8 *)(param_1 + 0x4a);
      *(undefined8 *)(param_4 + 2) = uVar21;
    }
    uVar21 = *(undefined8 *)(param_2 + 2);
    *(undefined8 *)(param_1 + 0x42) = *(undefined8 *)param_2;
    *(undefined8 *)(param_1 + 0x44) = uVar21;
    uVar21 = *(undefined8 *)(param_3 + 2);
    *(undefined8 *)(param_1 + 0x46) = *(undefined8 *)param_3;
    *(undefined8 *)(param_1 + 0x48) = uVar21;
    uVar21 = *(undefined8 *)(param_4 + 2);
    *(undefined8 *)(param_1 + 0x4a) = *(undefined8 *)param_4;
    *(undefined8 *)(param_1 + 0x4c) = uVar21;
    iVar10 = param_2[1] - param_4[1];
    if (param_1[1] == 0) {
      iVar19 = iVar10;
      if (iVar10 < param_1[0x6b]) {
        iVar19 = param_1[0x6b];
      }
      param_1[0x6b] = iVar19;
      if (param_1[0x6c] < iVar10) {
        iVar10 = param_1[0x6c];
      }
      param_1[0x6c] = iVar10;
    }
    else {
      iVar19 = iVar10;
      if (iVar10 < param_1[0x6d]) {
        iVar19 = param_1[0x6d];
      }
      param_1[0x6d] = iVar19;
      if (param_1[0x6e] < iVar10) {
        iVar10 = param_1[0x6e];
      }
      param_1[0x6e] = iVar10;
    }
    DAT_80430d20 = param_1;
    if (DAT_80430d14 != 0) {
      uVar17 = param_1[0x48];
      uVar18 = param_1[0x49];
      dVar22 = (double)zz_0232f90_(uVar17,uVar18);
      uVar14 = param_1[0x46];
      uVar16 = param_1[0x47];
      dVar23 = (double)zz_0232f90_(uVar14,uVar16);
      local_50 = 0x43300000;
      dVar22 = DAT_802b8fe8 * (dVar23 / dVar22) + DAT_802b8fe0;
      uVar13 = (uint)dVar22;
      local_58 = (longlong)(int)uVar13;
      uStack_4c = uVar13 ^ 0x80000000;
      lVar26 = local_58;
      if (dVar22 < (double)CONCAT44(0x43300000,uStack_4c) - DAT_802b9068) {
        uVar13 = uVar13 - 1;
        local_48 = local_58;
        lVar26 = local_40;
      }
      local_40 = lVar26;
      iVar19 = param_1[0x4b];
      iVar10 = param_1[0x43];
      iVar20 = param_1[99];
      uVar21 = gnt4___div2i(uVar14,uVar16,uVar17,uVar18);
      iVar10 = sprintf(acStack_158,s__08X___d___d___08X_08X___d___d____802b8ff0,param_1,(int)uVar21,
                       uVar13,uVar14,uVar16,uVar16 & 0x7fffffff,iVar20,iVar10,iVar19,iVar10 - iVar19
                       ,iVar20 - iVar19,param_1[0x6b],param_1[0x6c],param_1[0x6d],param_1[0x6e],
                       *param_1,param_1[1],param_1[0x67],param_1[0x68],param_1[100],param_1[0x65],
                       param_1[0x66],param_1[0x69],param_1[0x6a],DAT_8041cff0);
      strcpy(DAT_80430d1c,acStack_158);
      DAT_80430d1c = DAT_80430d1c + iVar10;
      if ((char *)(DAT_80430d14 + DAT_80430d10 + -0x400) <= DAT_80430d1c) {
        DAT_80430d1c = DAT_80430d18;
      }
    }
  }
  return;
}



// ==== 802a6aa0  zz_02a6aa0_ ====

void zz_02a6aa0_(int param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  longlong lVar3;
  
  if (*(int *)(param_1 + 8) == 0) {
    uVar2 = *(uint *)(param_1 + 0x134);
    uVar1 = param_2[1];
    lVar3 = gnt4___div2i((int)((ulonglong)uVar2 * (ulonglong)uVar1 >> 0x20) +
                         *(int *)(param_1 + 0x130) * uVar1 + uVar2 * *param_2,uVar2 * uVar1,
                         param_2[2],param_2[3]);
    *(longlong *)(param_1 + 0x128) = lVar3 + *(longlong *)(param_1 + 0x128);
  }
  return;
}



// ==== 802a6b20  zz_02a6b20_ ====

void zz_02a6b20_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 8) = param_2;
  return;
}



// ==== 802a6b28  zz_02a6b28_ ====

void zz_02a6b28_(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = param_2;
  return;
}



// ==== 802a6b30  zz_02a6b30_ ====

void zz_02a6b30_(int param_1,int param_2)

{
  if (param_2 < 1) {
    return;
  }
  *(int *)(param_1 + 0xc) = param_2;
  return;
}



// ==== 802a6b40  zz_02a6b40_ ====

void zz_02a6b40_(int param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  uVar1 = param_2[1];
  *(undefined8 *)(param_1 + 0x168) = *param_2;
  *(undefined8 *)(param_1 + 0x170) = uVar1;
  return;
}



// ==== 802a6b54  zz_02a6b54_ ====

void zz_02a6b54_(int param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  uVar1 = param_2[1];
  *(undefined8 *)(param_1 + 0x158) = *param_2;
  *(undefined8 *)(param_1 + 0x160) = uVar1;
  return;
}



// ==== 802a6b68  zz_02a6b68_ ====

void zz_02a6b68_(int param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  uVar1 = param_2[1];
  *(undefined8 *)(param_1 + 0x148) = *param_2;
  *(undefined8 *)(param_1 + 0x150) = uVar1;
  return;
}



// ==== 802a6b7c  zz_02a6b7c_ ====

void zz_02a6b7c_(int param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  uVar1 = param_2[1];
  *(undefined8 *)(param_1 + 0x138) = *param_2;
  *(undefined8 *)(param_1 + 0x140) = uVar1;
  return;
}



// ==== 802a6b90  zz_02a6b90_ ====

void zz_02a6b90_(undefined4 *param_1)

{
  undefined **ppuVar1;
  undefined4 *puVar2;
  undefined *puVar3;
  size_t sVar4;
  undefined **ppuVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 uStack_12c;
  char local_128 [4];
  undefined4 local_124;
  undefined2 auStack_120 [140];
  
  gnt4_memset(param_1,0,0x1c0);
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 1;
  param_1[3] = 10;
  gnt4_memset(param_1 + 5,0,0xf0);
  param_1[4] = 0;
  param_1[0x67] = param_1[0x67] + 1;
  param_1[0x43] = 0;
  param_1[0x42] = 0;
  param_1[0x45] = 1;
  param_1[0x44] = 0;
  param_1[0x47] = 0;
  param_1[0x46] = 0;
  param_1[0x49] = 1;
  param_1[0x48] = 0;
  param_1[0x4b] = 0;
  param_1[0x4a] = 0;
  param_1[0x4d] = 1;
  param_1[0x4c] = 0;
  param_1[0x4f] = 0x412b;
  param_1[0x4e] = 0;
  param_1[0x51] = 1000000;
  param_1[0x50] = 0;
  param_1[0x53] = 200000;
  param_1[0x52] = 0;
  param_1[0x55] = 1000000;
  param_1[0x54] = 0;
  param_1[0x57] = 0xffffbed5;
  param_1[0x56] = 0xffffffff;
  param_1[0x59] = 1000000;
  param_1[0x58] = 0;
  param_1[0x5b] = 0xffffbed5;
  param_1[0x5a] = 0xffffffff;
  param_1[0x5d] = 1000000;
  param_1[0x5c] = 0;
  param_1[0x5f] = 0xffffffff;
  param_1[0x5e] = 0xffffffff;
  param_1[0x61] = 0;
  param_1[0x60] = 0;
  param_1[99] = 0;
  param_1[0x62] = 0;
  param_1[100] = 0;
  param_1[0x65] = 0;
  param_1[0x66] = 0;
  param_1[0x67] = 0;
  param_1[0x68] = 0;
  param_1[0x69] = 0;
  param_1[0x6a] = 0;
  param_1[0x6b] = 0;
  param_1[0x6c] = 0;
  param_1[0x6d] = 0;
  param_1[0x6e] = 0;
  iVar7 = 0x22;
  ppuVar1 = &PTR_LAB_802b8ec4;
  puVar2 = &uStack_12c;
  do {
    puVar6 = puVar2;
    ppuVar5 = ppuVar1;
    puVar3 = ppuVar5[2];
    puVar6[1] = ppuVar5[1];
    puVar6[2] = puVar3;
    iVar7 = iVar7 + -1;
    ppuVar1 = ppuVar5 + 2;
    puVar2 = puVar6 + 2;
  } while (iVar7 != 0);
  *(undefined2 *)(puVar6 + 3) = *(undefined2 *)(ppuVar5 + 3);
  if (DAT_80430d14 != (char *)0x0) {
    gnt4_memset(DAT_80430d14,0,DAT_80430d10);
    DAT_80430d1c = DAT_80430d14;
    strcpy(DAT_80430d14,local_128);
    sVar4 = strlen(local_128);
    DAT_80430d18 = DAT_80430d1c + sVar4;
    DAT_80430d1c = DAT_80430d18;
  }
  return;
}



// ==== 802a6d5c  zz_02a6d5c_ ====

undefined4 zz_02a6d5c_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xe0) {
    if (*(byte *)(iVar2 + 0x20) < 2) {
      if (*(byte *)(iVar2 + 0x20) == 0) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_3 = (uint)*(byte *)(iVar2 + 0x26);
    if (0x3f < (int)*param_3) {
      *param_3 = 0xffffffff;
    }
    return 1;
  }
  return 0;
}



// ==== 802a6ef0  zz_02a6ef0_ ====

undefined4 zz_02a6ef0_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xe0) {
    if (*(byte *)(iVar2 + 0x20) < 2) {
      if (*(byte *)(iVar2 + 0x20) == 0) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_3 = (uint)*(byte *)(iVar2 + 0x25);
    if (0x3f < (int)*param_3) {
      *param_3 = 0xffffffff;
    }
    return 1;
  }
  return 0;
}



// ==== 802a7084  zz_02a7084_ ====

undefined4 zz_02a7084_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xe0) {
    if (*(byte *)(iVar2 + 0x20) < 2) {
      if (*(byte *)(iVar2 + 0x20) == 0) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_3 = (uint)*(byte *)(iVar2 + 0x24);
    return 1;
  }
  return 0;
}



// ==== 802a7204  zz_02a7204_ ====

undefined4 zz_02a7204_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xe0) {
    if (*(byte *)(iVar2 + 0x20) < 2) {
      if (*(byte *)(iVar2 + 0x20) == 0) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_3 = *(byte *)(iVar2 + 0x23) >> 4 & 1;
    return 1;
  }
  return 0;
}



// ==== 802a7388  zz_02a7388_ ====

undefined4 zz_02a7388_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xe0) {
    if (*(byte *)(iVar2 + 0x20) < 2) {
      if (*(byte *)(iVar2 + 0x20) == 0) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_3 = *(byte *)(iVar2 + 0x23) & 1;
    return 1;
  }
  return 0;
}



// ==== 802a750c  zz_02a750c_ ====

undefined4 zz_02a750c_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xe0) {
    if (*(byte *)(iVar2 + 0x20) < 2) {
      if (*(byte *)(iVar2 + 0x20) == 0) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_3 = (uint)*(byte *)(iVar2 + 0x22);
    return 1;
  }
  return 0;
}



// ==== 802a768c  zz_02a768c_ ====

undefined4 zz_02a768c_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xe0) {
    if (*(byte *)(iVar2 + 0x20) < 2) {
      if (*(byte *)(iVar2 + 0x20) == 0) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_3 = (uint)*(byte *)(iVar2 + 0x21);
    return 1;
  }
  return 0;
}



// ==== 802a780c  zz_02a780c_ ====

undefined4 zz_02a780c_(int *param_1,byte param_2,undefined4 *param_3)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar5 = 0xd;
    do {
      iVar3 = iVar4 + 0x180;
      if ((*(byte *)(iVar4 + 0x198) == param_2) ||
         (iVar3 = iVar4 + 0x1c0, *(byte *)(iVar4 + 0x1d8) == param_2)) break;
      iVar4 = iVar4 + 0x80;
      iVar5 = iVar5 + -1;
      iVar3 = 0;
    } while (iVar5 != 0);
  }
  else {
    iVar3 = 0;
  }
  if (iVar3 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar4 = 0xbd;
      }
      else {
        iVar4 = 0;
      }
    }
    else {
      iVar4 = 0xe0;
    }
  }
  else {
    iVar4 = 0xc0;
  }
  if (iVar4 == 0xe0) {
    switch(*(undefined1 *)(iVar3 + 0x1f)) {
    default:
      uVar2 = 0;
      break;
    case 1:
      uVar2 = 0x5da8;
      break;
    case 2:
      uVar2 = 24000;
      break;
    case 3:
      uVar2 = 25000;
      break;
    case 4:
      uVar2 = 0x7512;
      break;
    case 5:
      uVar2 = 30000;
      break;
    case 6:
      uVar2 = 50000;
      break;
    case 7:
      uVar2 = 0xea24;
      break;
    case 8:
      uVar2 = 60000;
    }
    *param_3 = uVar2;
    return 1;
  }
  return 0;
}



// ==== 802a79c4  zz_02a79c4_ ====

undefined4 zz_02a79c4_(int *param_1,byte param_2,uint *param_3,uint *param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xe0) {
    *param_3 = (uint)*(byte *)(iVar2 + 0x1c);
    *param_3 = *param_3 << 4 | (uint)(*(byte *)(iVar2 + 0x1d) >> 4);
    *param_3 = *param_3 & 0xfff;
    *param_4 = (uint)*(byte *)(iVar2 + 0x1d);
    *param_4 = *param_4 << 8 | (uint)*(byte *)(iVar2 + 0x1e);
    *param_4 = *param_4 & 0xfff;
    return 1;
  }
  return 0;
}



// ==== 802a7b50  zz_02a7b50_ ====

undefined4 zz_02a7b50_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar5 = 0xd;
    do {
      iVar3 = iVar4 + 0x180;
      if ((*(byte *)(iVar4 + 0x198) == param_2) ||
         (iVar3 = iVar4 + 0x1c0, *(byte *)(iVar4 + 0x1d8) == param_2)) break;
      iVar4 = iVar4 + 0x80;
      iVar5 = iVar5 + -1;
      iVar3 = 0;
    } while (iVar5 != 0);
  }
  else {
    iVar3 = 0;
  }
  if (iVar3 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar4 = 0xbd;
      }
      else {
        iVar4 = 0;
      }
    }
    else {
      iVar4 = 0xe0;
    }
  }
  else {
    iVar4 = 0xc0;
  }
  if (iVar4 == 0xe0) {
    uVar2 = (uint)*(ushort *)(iVar3 + 0x1a);
    if (uVar2 == 0xffff) {
      uVar2 = 0;
    }
    *param_3 = uVar2;
    return 1;
  }
  return 0;
}



// ==== 802a7ca8  zz_02a7ca8_ ====

undefined4 zz_02a7ca8_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xe0) {
    *param_3 = (uint)*(byte *)(iVar2 + 0x19);
    return 1;
  }
  return 0;
}



// ==== 802a7df0  zz_02a7df0_ ====

undefined4 zz_02a7df0_(int *param_1,byte param_2,undefined4 *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xc0) {
    *param_3 = *(undefined4 *)(iVar2 + 0x1c);
    return 1;
  }
  return 0;
}



// ==== 802a7f38  zz_02a7f38_ ====

undefined4 zz_02a7f38_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xc0) {
    *param_3 = (uint)*(byte *)(iVar2 + 0x1b);
    return 1;
  }
  return 0;
}



// ==== 802a8080  zz_02a8080_ ====

undefined4 zz_02a8080_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xc0) {
    if (*(char *)(iVar2 + 0x19) == '\x01') {
      *param_3 = (uint)*(byte *)(iVar2 + 0x1a);
      return 1;
    }
    return 0;
  }
  return 0;
}



// ==== 802a81dc  zz_02a81dc_ ====

undefined4 zz_02a81dc_(int *param_1,byte param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    iVar4 = 0xd;
    do {
      iVar2 = iVar3 + 0x180;
      if ((*(byte *)(iVar3 + 0x198) == param_2) ||
         (iVar2 = iVar3 + 0x1c0, *(byte *)(iVar3 + 0x1d8) == param_2)) break;
      iVar3 = iVar3 + 0x80;
      iVar4 = iVar4 + -1;
      iVar2 = 0;
    } while (iVar4 != 0);
  }
  else {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        iVar3 = 0xbd;
      }
      else {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0xe0;
    }
  }
  else {
    iVar3 = 0xc0;
  }
  if (iVar3 == 0xc0) {
    *param_3 = (uint)*(byte *)(iVar2 + 0x19);
    return 1;
  }
  return 0;
}



// ==== 802a8324  zz_02a8324_ ====

undefined4 zz_02a8324_(int *param_1,undefined4 *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = *(undefined4 *)(param_1[1] + 0xc0);
    return 1;
  }
  return 0;
}



// ==== 802a83ac  zz_02a83ac_ ====

undefined4 zz_02a83ac_(int *param_1,undefined4 *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = *(undefined4 *)(param_1[1] + 0xbc);
    return 1;
  }
  return 0;
}



// ==== 802a8434  zz_02a8434_ ====

undefined4 zz_02a8434_(int *param_1,undefined4 *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = *(undefined4 *)(param_1[1] + 0xb8);
    return 1;
  }
  return 0;
}



// ==== 802a84bc  zz_02a84bc_ ====

undefined4 zz_02a84bc_(int *param_1,undefined4 *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (0x6d < param_1[3]) {
      *param_2 = *(undefined4 *)(param_1[1] + 0xb4);
      return 1;
    }
    return 0;
  }
  return 0;
}



// ==== 802a8558  zz_02a8558_ ====

undefined4 zz_02a8558_(int *param_1,uint *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = (uint)*(byte *)(param_1[1] + 0xb3);
    return 1;
  }
  return 0;
}



// ==== 802a85e0  zz_02a85e0_ ====

undefined4 zz_02a85e0_(int *param_1,uint *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = (uint)*(byte *)(param_1[1] + 0xb2);
    return 1;
  }
  return 0;
}



// ==== 802a8668  zz_02a8668_ ====

undefined4 zz_02a8668_(int *param_1,uint *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = (uint)*(byte *)(param_1[1] + 0xb1);
    return 1;
  }
  return 0;
}



// ==== 802a86f0  zz_02a86f0_ ====

undefined4 zz_02a86f0_(int *param_1,uint *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = (uint)*(byte *)(param_1[1] + 0xb0);
    return 1;
  }
  return 0;
}



// ==== 802a8778  zz_02a8778_ ====

undefined4 zz_02a8778_(int *param_1,undefined4 *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = *(undefined4 *)(param_1[1] + 0x8c);
    return 1;
  }
  return 0;
}



// ==== 802a8800  zz_02a8800_ ====

undefined4 zz_02a8800_(int *param_1,int *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = (int)*(short *)(param_1[1] + 0x88);
    return 1;
  }
  return 0;
}



// ==== 802a8888  zz_02a8888_ ====

undefined4 zz_02a8888_(int *param_1,uint *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = (uint)*(byte *)(param_1[1] + 0x84);
    return 1;
  }
  return 0;
}



// ==== 802a8910  zz_02a8910_ ====

undefined4 zz_02a8910_(int *param_1,undefined4 *param_2)

{
  bool bVar1;
  
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *param_2 = *(undefined4 *)(param_1[1] + 0x80);
    return 1;
  }
  return 0;
}



// ==== 802a8998  zz_02a8998_ ====

undefined4 zz_02a8998_(int *param_1,int *param_2,int *param_3)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  char acStack_38 [44];
  
  iVar2 = param_1[1];
  if ((*param_1 < 2) && (-2 < *param_1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    gnt4_memset(acStack_38,0,0x21);
    gnt4_memcpy(acStack_38,(void *)(iVar2 + 0x60),0x20);
    pcVar4 = strstr(acStack_38,&DAT_802b90a4);
    if (pcVar4 == (char *)0x0) {
      bVar1 = false;
    }
    else {
      iVar2 = 0;
      for (pcVar4 = pcVar4 + 4;
          ((iVar5 = (int)*pcVar4, iVar5 != 0x2e && (iVar5 != 0x20)) && (iVar5 != 0));
          pcVar4 = pcVar4 + 1) {
        bVar1 = false;
        if ((0x2f < iVar5) && (iVar5 < 0x3a)) {
          bVar1 = true;
        }
        if (!bVar1) break;
        iVar2 = iVar5 + iVar2 * 10 + -0x30;
      }
      *param_2 = iVar2;
      iVar2 = 0;
      while( true ) {
        pcVar4 = pcVar4 + 1;
        iVar5 = (int)*pcVar4;
        if (((iVar5 == 0x2e) || (iVar5 == 0x20)) || (iVar5 == 0)) break;
        bVar1 = false;
        if ((0x2f < iVar5) && (iVar5 < 0x3a)) {
          bVar1 = true;
        }
        if (!bVar1) break;
        iVar2 = iVar5 + iVar2 * 10 + -0x30;
      }
      *param_3 = iVar2;
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 802a8b3c  zz_02a8e80_ ====

undefined4 zz_02a8e80_(int *param_1,byte param_2,undefined4 *param_3)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (param_1[3] < 0x6e) {
    return 0;
  }
  if ((param_2 < 0xc0) || (0xdf < param_2)) {
    if ((param_2 < 0xe0) || (0xef < param_2)) {
      if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
        uVar3 = 0xbd;
      }
      else {
        uVar3 = 0;
      }
    }
    else {
      uVar3 = 0xe0;
    }
  }
  else {
    uVar3 = 0xc0;
  }
  if (uVar3 == 0xe0) {
    iVar5 = param_1[1];
    if ((*param_1 < 2) && (-2 < *param_1)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = false;
      if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
        bVar1 = true;
      }
      if (bVar1) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      iVar6 = 0xd;
      do {
        iVar4 = iVar5 + 0x180;
        if ((*(byte *)(iVar5 + 0x198) == param_2) ||
           (iVar4 = iVar5 + 0x1c0, *(byte *)(iVar5 + 0x1d8) == param_2)) break;
        iVar5 = iVar5 + 0x80;
        iVar6 = iVar6 + -1;
        iVar4 = 0;
      } while (iVar6 != 0);
    }
    else {
      iVar4 = 0;
    }
    if (iVar4 == 0) {
      return 0;
    }
    if ((param_2 < 0xc0) || (0xdf < param_2)) {
      if ((param_2 < 0xe0) || (0xef < param_2)) {
        if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
          iVar5 = 0xbd;
        }
        else {
          iVar5 = 0;
        }
      }
      else {
        iVar5 = 0xe0;
      }
    }
    else {
      iVar5 = 0xc0;
    }
    if (iVar5 == 0xe0) {
      if (*(byte *)(iVar4 + 0x20) < 2) {
        if (*(byte *)(iVar4 + 0x20) == 0) {
          uVar2 = 0;
        }
        else {
          uVar2 = 1;
        }
      }
      else {
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0;
    }
    *param_3 = uVar2;
  }
  else {
    if ((0xdf < uVar3) || (uVar3 != 0xc0)) {
      return 0;
    }
    iVar5 = param_1[1];
    if ((*param_1 < 2) && (-2 < *param_1)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = false;
      if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
        bVar1 = true;
      }
      if (bVar1) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      iVar6 = 0xd;
      do {
        iVar4 = iVar5 + 0x180;
        if ((*(byte *)(iVar5 + 0x198) == param_2) ||
           (iVar4 = iVar5 + 0x1c0, *(byte *)(iVar5 + 0x1d8) == param_2)) break;
        iVar5 = iVar5 + 0x80;
        iVar6 = iVar6 + -1;
        iVar4 = 0;
      } while (iVar6 != 0);
    }
    else {
      iVar4 = 0;
    }
    if (iVar4 == 0) {
      return 0;
    }
    if ((param_2 < 0xc0) || (0xdf < param_2)) {
      if ((param_2 < 0xe0) || (0xef < param_2)) {
        if ((param_2 == 0xbd) || (param_2 == 0xbf)) {
          iVar5 = 0xbd;
        }
        else {
          iVar5 = 0;
        }
      }
      else {
        iVar5 = 0xe0;
      }
    }
    else {
      iVar5 = 0xc0;
    }
    if (iVar5 == 0xc0) {
      if (*(byte *)(iVar4 + 0x20) < 2) {
        if (*(byte *)(iVar4 + 0x20) == 0) {
          uVar2 = 0;
        }
        else {
          uVar2 = 1;
        }
      }
      else {
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0;
    }
    *param_3 = uVar2;
  }
  return 1;
}



// ==== 802a8e88  zz_02a8e88_ ====

undefined4 zz_02a8e88_(int *param_1,char param_2,undefined4 *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  bVar1 = false;
  *param_3 = 0;
  iVar3 = param_1[1];
  if ((1 < *param_1) || (*param_1 < -1)) {
    bVar1 = true;
  }
  if (bVar1) {
    bVar1 = false;
    if ((param_1[3] == 0x6b) || (0x6d < param_1[3])) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (!bVar1) {
    return 0;
  }
  iVar4 = 0xd;
  do {
    iVar2 = iVar3 + 0x180;
    if ((*(char *)(iVar3 + 0x198) == param_2) ||
       (iVar2 = iVar3 + 0x1c0, *(char *)(iVar3 + 0x1d8) == param_2)) break;
    iVar3 = iVar3 + 0x80;
    iVar4 = iVar4 + -1;
    iVar2 = 0;
  } while (iVar4 != 0);
  if (iVar2 == 0) {
    *param_3 = 0;
  }
  else {
    *param_3 = 1;
  }
  return 1;
}



// ==== 802a8f78  zz_02a8f78_ ====

undefined4 zz_02a8f78_(int *param_1,undefined4 *param_2)

{
  bool bVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  int unaff_r30;
  int unaff_r31;
  char acStack_48 [52];
  
  *param_2 = 0;
  uVar2 = countLeadingZeros(*param_1);
  if (uVar2 >> 5 == 1) {
    uVar3 = 0;
  }
  else if ((uint)param_1[2] < 0x800) {
    uVar3 = 0;
    *param_1 = -1;
  }
  else {
    iVar4 = gnt4_memcmp((void *)(param_1[1] + 0x20),s_SofdecStream_802b90ac,0x18);
    if (iVar4 == 0) {
      *param_1 = 2;
      iVar4 = param_1[1];
      if ((*param_1 < 2) && (-2 < *param_1)) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      if (bVar1) {
        gnt4_memset(acStack_48,0,0x21);
        gnt4_memcpy(acStack_48,(void *)(iVar4 + 0x60),0x20);
        pcVar5 = strstr(acStack_48,&DAT_802b90a4);
        if (pcVar5 == (char *)0x0) {
          bVar1 = false;
        }
        else {
          unaff_r31 = 0;
          for (pcVar5 = pcVar5 + 4;
              ((iVar4 = (int)*pcVar5, iVar4 != 0x2e && (iVar4 != 0x20)) && (iVar4 != 0));
              pcVar5 = pcVar5 + 1) {
            bVar1 = false;
            if ((0x2f < iVar4) && (iVar4 < 0x3a)) {
              bVar1 = true;
            }
            if (!bVar1) break;
            unaff_r31 = iVar4 + unaff_r31 * 10 + -0x30;
          }
          unaff_r30 = 0;
          while( true ) {
            pcVar5 = pcVar5 + 1;
            iVar4 = (int)*pcVar5;
            if (((iVar4 == 0x2e) || (iVar4 == 0x20)) || (iVar4 == 0)) break;
            bVar1 = false;
            if ((0x2f < iVar4) && (iVar4 < 0x3a)) {
              bVar1 = true;
            }
            if (!bVar1) break;
            unaff_r30 = iVar4 + unaff_r30 * 10 + -0x30;
          }
          bVar1 = true;
        }
        if (bVar1) {
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
      }
      else {
        bVar1 = false;
      }
      if (bVar1) {
        uVar3 = 1;
        param_1[3] = unaff_r30 + unaff_r31 * 100;
        *param_2 = 1;
      }
      else {
        uVar3 = 0;
      }
    }
    else {
      uVar3 = 0;
      *param_1 = -1;
    }
  }
  return uVar3;
}



// ==== 802a91ac  zz_02a91ac_ ====

void zz_02a91ac_(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  DAT_80430d30 = DAT_80430d30 + -1;
  return;
}



// ==== 802a91d8  zz_02a91d8_ ====

int * zz_02a91d8_(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)0x0;
  if (DAT_80430d2c <= DAT_80430d30) {
    return (int *)0x0;
  }
  piVar1 = DAT_80430d34;
  iVar3 = DAT_80430d2c;
  if (0 < DAT_80430d2c) {
    do {
      piVar2 = piVar1;
      if (*piVar2 == 0) break;
      iVar3 = iVar3 + -1;
      piVar1 = piVar2 + 4;
    } while (iVar3 != 0);
  }
  *piVar2 = 1;
  piVar2[1] = param_1;
  piVar2[2] = param_2;
  DAT_80430d30 = DAT_80430d30 + 1;
  return piVar2;
}



// ==== 802a9244  zz_02a9244_ ====

void zz_02a9244_(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  if (0 < DAT_80430d28) {
    return;
  }
  DAT_80430d28 = DAT_80430d28 + 1;
  iVar2 = 0;
  DAT_80430d38 = s_CRI_SFH_GC_Ver_1_12_Build_Feb_6_2_802b9070;
  if (0 < param_1) {
    if ((8 < param_1) && (uVar4 = param_1 - 1U >> 3, puVar3 = param_2, 0 < param_1 + -8)) {
      do {
        iVar2 = iVar2 + 8;
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
        puVar3[0x10] = 0;
        puVar3[0x11] = 0;
        puVar3[0x12] = 0;
        puVar3[0x13] = 0;
        puVar3[0x14] = 0;
        puVar3[0x15] = 0;
        puVar3[0x16] = 0;
        puVar3[0x17] = 0;
        puVar3[0x18] = 0;
        puVar3[0x19] = 0;
        puVar3[0x1a] = 0;
        puVar3[0x1b] = 0;
        puVar3[0x1c] = 0;
        puVar3[0x1d] = 0;
        puVar3[0x1e] = 0;
        puVar3[0x1f] = 0;
        puVar3 = puVar3 + 0x20;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
    iVar1 = param_1 - iVar2;
    puVar3 = param_2 + iVar2 * 4;
    if (iVar2 < param_1) {
      do {
        *puVar3 = 0;
        puVar3[1] = 0;
        puVar3[2] = 0;
        puVar3[3] = 0;
        puVar3 = puVar3 + 4;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  DAT_80430d2c = param_1;
  DAT_80430d30 = 0;
  DAT_80430d34 = param_2;
  return;
}



// ==== 802a9378  zz_02a9378_ ====

bool zz_02a9378_(uint param_1,uint param_2,uint param_3,uint param_4)

{
  return ((double)CONCAT44(0x43300000,param_1 ^ 0x80000000) - DAT_802b90c8) *
         ((double)CONCAT44(0x43300000,param_4 ^ 0x80000000) - DAT_802b90c8) <=
         ((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DAT_802b90c8) *
         ((double)CONCAT44(0x43300000,param_2 ^ 0x80000000) - DAT_802b90c8);
}



// ==== 802a9400  zz_02a9400_ ====

void zz_02a9400_(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  iVar3 = (param_3 & 0xf) + 1;
  while( true ) {
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) break;
    uVar2 = *param_2;
    param_2 = param_2 + 1;
    *param_1 = uVar2;
    param_1 = param_1 + 1;
  }
  iVar3 = (param_3 >> 4) + 1;
  while( true ) {
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) break;
    uVar2 = param_2[1];
    uVar4 = param_2[2];
    uVar5 = param_2[3];
    *param_1 = *param_2;
    param_1[1] = uVar2;
    param_1[2] = uVar4;
    param_1[3] = uVar5;
    uVar2 = param_2[5];
    uVar4 = param_2[6];
    uVar5 = param_2[7];
    param_1[4] = param_2[4];
    param_1[5] = uVar2;
    param_1[6] = uVar4;
    param_1[7] = uVar5;
    uVar2 = param_2[9];
    uVar4 = param_2[10];
    uVar5 = param_2[0xb];
    param_1[8] = param_2[8];
    param_1[9] = uVar2;
    param_1[10] = uVar4;
    param_1[0xb] = uVar5;
    puVar1 = param_2 + 0xc;
    uVar2 = param_2[0xd];
    uVar4 = param_2[0xe];
    uVar5 = param_2[0xf];
    param_2 = param_2 + 0x10;
    param_1[0xc] = *puVar1;
    param_1[0xd] = uVar2;
    param_1[0xe] = uVar4;
    param_1[0xf] = uVar5;
    param_1 = param_1 + 0x10;
  }
  return;
}



// ==== 802a94c4  zz_02a94c4_ ====

void zz_02a94c4_(int param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(param_1 + param_3 * 4);
  iVar1 = (param_3 & 0xf) + 1;
  while( true ) {
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) break;
    puVar2 = puVar2 + -1;
    *puVar2 = param_2;
  }
  iVar1 = (param_3 >> 4) + 1;
  while( true ) {
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) break;
    puVar2[-1] = param_2;
    puVar2[-2] = param_2;
    puVar2[-3] = param_2;
    puVar2[-4] = param_2;
    puVar2[-5] = param_2;
    puVar2[-6] = param_2;
    puVar2[-7] = param_2;
    puVar2[-8] = param_2;
    puVar2[-9] = param_2;
    puVar2[-10] = param_2;
    puVar2[-0xb] = param_2;
    puVar2[-0xc] = param_2;
    puVar2[-0xd] = param_2;
    puVar2[-0xe] = param_2;
    puVar2[-0xf] = param_2;
    puVar2 = puVar2 + -0x10;
    *puVar2 = param_2;
  }
  return;
}



// ==== 802a953c  zz_02a953c_ ====

int zz_02a953c_(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  undefined8 uVar2;
  
  if (param_3 == 0) {
    iVar1 = 0x7fffffff - ((int)(param_1 ^ param_2) >> 0x1f);
  }
  else {
    uVar2 = gnt4___div2i((uint)((ulonglong)((longlong)(int)param_1 * (longlong)(int)param_2) >> 0x20
                               ),param_1 * param_2,(int)param_3 >> 0x1f,param_3);
    iVar1 = (int)uVar2;
  }
  return iVar1;
}



// ==== 802a9598  zz_02a9598_ ====

int zz_02a9598_(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  double dVar2;
  
  if (param_3 == 0) {
    iVar1 = 0x7fffffff - ((int)(param_1 ^ param_2) >> 0x1f);
  }
  else {
    dVar2 = floor(DAT_802b90d0 +
                  (((double)CONCAT44(0x43300000,param_1 ^ 0x80000000) - DAT_802b90d8) *
                  ((double)CONCAT44(0x43300000,param_2 ^ 0x80000000) - DAT_802b90d8)) /
                  ((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DAT_802b90d8));
    iVar1 = (int)dVar2;
  }
  return iVar1;
}



// ==== 802a9640  glGetCurrentTextureState(void) ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 glGetCurrentTextureState_void_(void)

{
  return _DAT_80430d48;
}



// ==== 802a9654  zz_02a9654_ ====

void zz_02a9654_(void)

{
  return;
}



// ==== 802a966c  zz_02a966c_ ====

void zz_02a966c_(void)

{
  if (DAT_80430d40 != 0) {
    return;
  }
  DAT_80430d40 = 1;
  DAT_80430d48 = 0;
  DAT_80430d4c = DAT_800000f8 >> 2;
  return;
}



// ==== 802a96a8  zz_02a96a8_ ====

undefined8 zz_02a96a8_(int param_1)

{
  return CONCAT44(*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0xc));
}



// ==== 802a96dc  zz_02a96dc_ ====

void zz_02a96dc_(int param_1)

{
  *(undefined4 *)(param_1 + 8) = 0x40004;
  *(undefined4 *)(param_1 + 0xc) = 0x50005;
  *(undefined4 *)(param_1 + 0x10) = 0x60006;
  *(undefined4 *)(param_1 + 0x14) = 0x70007;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return;
}



