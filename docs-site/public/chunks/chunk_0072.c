// ==== 80256dd8  gnt4-HSD_MtxAlloc-bl ====

undefined4 *
gnt4_HSD_MtxAlloc_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  
  puVar1 = gnt4_HSD_ObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_803fa4ac,param_10,param_11,param_12,param_13,param_14,param_15,
                             param_16);
  if (puVar1 == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435f68,
                     0x3ab,&DAT_80435f74,param_12,param_13,param_14,param_15,param_16);
  }
  return puVar1;
}



// ==== 80256e24  gnt4-HSD_MtxFree-bl ====

void gnt4_HSD_MtxFree_bl(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    gnt4_HSD_ObjFree(-0x7fc05b54,param_1);
  }
  return;
}



// ==== 80256e58  gnt4-HSD_VecInitAllocData-bl ====

void gnt4_HSD_VecInitAllocData_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_HSD_ObjAllocInit_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803fa480,0xc,4,
             in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 80256e88  gnt4-HSD_MtxInitAllocData-bl ====

void gnt4_HSD_MtxInitAllocData_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_HSD_ObjAllocInit_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803fa4ac,0x30,4,
             in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 80256eb8  gnt4-HSD_MulColor-bl ====

void gnt4_HSD_MulColor_bl(byte *param_1,byte *param_2,undefined1 *param_3)

{
  *param_3 = (char)(((uint)*param_1 * (uint)*param_2) / 0xff);
  param_3[1] = (char)(((uint)param_1[1] * (uint)param_2[1]) / 0xff);
  param_3[2] = (char)(((uint)param_1[2] * (uint)param_2[2]) / 0xff);
  param_3[3] = (char)(((uint)param_1[3] * (uint)param_2[3]) / 0xff);
  return;
}



// ==== 80256f24  gnt4-HSD_GetNbBits-bl ====

int gnt4_HSD_GetNbBits_bl(uint param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = 0;
  iVar2 = 0;
  iVar3 = 4;
  do {
    if ((param_1 & 1 << iVar2) != 0) {
      iVar1 = iVar1 + 1;
    }
    if ((param_1 & 1 << iVar2 + 1) != 0) {
      iVar1 = iVar1 + 1;
    }
    if ((param_1 & 1 << iVar2 + 2) != 0) {
      iVar1 = iVar1 + 1;
    }
    if ((param_1 & 1 << iVar2 + 3) != 0) {
      iVar1 = iVar1 + 1;
    }
    if ((param_1 & 1 << iVar2 + 4) != 0) {
      iVar1 = iVar1 + 1;
    }
    if ((param_1 & 1 << iVar2 + 5) != 0) {
      iVar1 = iVar1 + 1;
    }
    if ((param_1 & 1 << iVar2 + 6) != 0) {
      iVar1 = iVar1 + 1;
    }
    if ((param_1 & 1 << iVar2 + 7) != 0) {
      iVar1 = iVar1 + 1;
    }
    iVar2 = iVar2 + 8;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return iVar1;
}



// ==== 80256fe4  gnt4-HSD_Index2PosNrmMtx-bl ====

undefined4
gnt4_HSD_Index2PosNrmMtx_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  switch(param_9) {
  case 0:
    uVar1 = 0;
    break;
  case 1:
    uVar1 = 3;
    break;
  case 2:
    uVar1 = 6;
    break;
  case 3:
    uVar1 = 9;
    break;
  case 4:
    uVar1 = 0xc;
    break;
  case 5:
    uVar1 = 0xf;
    break;
  case 6:
    uVar1 = 0x12;
    break;
  case 7:
    uVar1 = 0x15;
    break;
  case 8:
    uVar1 = 0x18;
    break;
  case 9:
    uVar1 = 0x1b;
    break;
  default:
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435f78,
                     0x84,&DAT_80435f80,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80257084  gnt4-HSD_ObjSetHeap ====

void gnt4_HSD_ObjSetHeap(undefined4 param_1,undefined4 param_2)

{
  DAT_803ad14c = param_2;
  DAT_803ad148 = param_2;
  DAT_803ad154 = param_1;
  DAT_803ad150 = param_1;
  return;
}



// ==== 802570a0  gnt4-HSD_ObjAllocAddFree ====

uint gnt4_HSD_ObjAllocAddFree
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,uint param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  if (param_9 == 0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_objalloc_c_803ad158,0xee,&DAT_80435f88,param_12,param_13,param_14,param_15,
                     param_16);
  }
  uVar7 = *(uint *)(param_9 + 0x20);
  uVar2 = uVar7 * param_10;
  if (DAT_803ad148 == 0) {
    uVar5 = gnt4__HSD_MemAlloc_bl();
    if (uVar5 == 0) {
      return 0;
    }
  }
  else {
    uVar5 = *(int *)(param_9 + 0x24) - 1;
    uVar8 = DAT_803ad148 + DAT_803ad150;
    uVar5 = DAT_803ad14c + uVar5 & ~uVar5;
    if (uVar8 < uVar5) {
      return 0;
    }
    if (uVar8 - uVar5 < uVar2) {
      uVar2 = ((uVar8 - uVar5) / uVar7) * uVar7;
    }
    param_10 = uVar2 / uVar7;
    if (param_10 == 0) {
      return 0;
    }
    DAT_803ad14c = uVar5 + uVar2;
    DAT_803ad154 = uVar8 - DAT_803ad14c;
  }
  uVar2 = 0;
  if (param_10 != 1) {
    if ((8 < param_10 - 1) && (uVar7 = param_10 - 2 >> 3, param_10 != 9)) {
      do {
        iVar10 = uVar2 + 1;
        iVar11 = uVar2 + 2;
        iVar12 = uVar2 + 3;
        iVar13 = uVar2 + 4;
        iVar1 = uVar2 + 5;
        iVar3 = uVar2 + 6;
        iVar4 = uVar2 + 7;
        iVar6 = uVar2 + 8;
        iVar9 = *(int *)(param_9 + 0x20) * uVar2;
        uVar2 = uVar2 + 8;
        *(uint *)(uVar5 + iVar9) = uVar5 + *(int *)(param_9 + 0x20) * iVar10;
        *(uint *)(uVar5 + *(int *)(param_9 + 0x20) * iVar10) =
             uVar5 + *(int *)(param_9 + 0x20) * iVar11;
        *(uint *)(uVar5 + *(int *)(param_9 + 0x20) * iVar11) =
             uVar5 + *(int *)(param_9 + 0x20) * iVar12;
        *(uint *)(uVar5 + *(int *)(param_9 + 0x20) * iVar12) =
             uVar5 + *(int *)(param_9 + 0x20) * iVar13;
        *(uint *)(uVar5 + *(int *)(param_9 + 0x20) * iVar13) =
             uVar5 + *(int *)(param_9 + 0x20) * iVar1;
        *(uint *)(uVar5 + *(int *)(param_9 + 0x20) * iVar1) =
             uVar5 + *(int *)(param_9 + 0x20) * iVar3;
        *(uint *)(uVar5 + *(int *)(param_9 + 0x20) * iVar3) =
             uVar5 + *(int *)(param_9 + 0x20) * iVar4;
        *(uint *)(uVar5 + *(int *)(param_9 + 0x20) * iVar4) =
             uVar5 + *(int *)(param_9 + 0x20) * iVar6;
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
    }
    iVar1 = (param_10 - 1) - uVar2;
    if (uVar2 < param_10 - 1) {
      do {
        iVar3 = uVar2 + 1;
        iVar4 = *(int *)(param_9 + 0x20) * uVar2;
        uVar2 = uVar2 + 1;
        *(uint *)(uVar5 + iVar4) = uVar5 + *(int *)(param_9 + 0x20) * iVar3;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  *(undefined4 *)(uVar5 + *(int *)(param_9 + 0x20) * uVar2) = *(undefined4 *)(param_9 + 4);
  *(uint *)(param_9 + 4) = uVar5;
  *(uint *)(param_9 + 0xc) = *(int *)(param_9 + 0xc) + param_10;
  return param_10;
}



// ==== 802572f0  gnt4-HSD_ObjAlloc ====

undefined4 *
gnt4_HSD_ObjAlloc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,byte *param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  
  if (((char)*param_9 < '\0') && (*(uint *)(param_9 + 0x14) <= *(uint *)(param_9 + 8))) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    if ((*param_9 >> 6 & 1) != 0) {
      if (*(int *)(param_9 + 0x1c) == -1) {
        uVar2 = DAT_803ad154;
        if (DAT_803ad148 == 0) {
          uVar2 = gnt4__HSD_MemGetRemain_bl();
          param_1 = extraout_f1;
        }
        if (uVar2 <= *(uint *)(param_9 + 0x18)) {
          *(int *)(param_9 + 0x1c) = *(int *)(param_9 + 8) + *(int *)(param_9 + 0xc);
        }
      }
      else {
        uVar2 = DAT_803ad154;
        if (DAT_803ad148 == 0) {
          uVar2 = gnt4__HSD_MemGetRemain_bl();
          param_1 = extraout_f1_00;
        }
        if (*(uint *)(param_9 + 0x18) < uVar2) {
          param_9[0x1c] = 0xff;
          param_9[0x1d] = 0xff;
          param_9[0x1e] = 0xff;
          param_9[0x1f] = 0xff;
        }
      }
      if (*(uint *)(param_9 + 0x1c) <= *(uint *)(param_9 + 8)) {
        return (undefined4 *)0x0;
      }
    }
    if ((*(int *)(param_9 + 0xc) == 0) &&
       (gnt4_HSD_ObjAllocAddFree
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,1,
                   param_11,param_12,param_13,param_14,param_15,param_16),
       *(int *)(param_9 + 0xc) == 0)) {
      puVar1 = (undefined4 *)0x0;
    }
    else {
      puVar1 = *(undefined4 **)(param_9 + 4);
      *(undefined4 *)(param_9 + 4) = *puVar1;
      *(int *)(param_9 + 8) = *(int *)(param_9 + 8) + 1;
      *(int *)(param_9 + 0xc) = *(int *)(param_9 + 0xc) + -1;
      if (*(uint *)(param_9 + 0x10) < *(uint *)(param_9 + 8)) {
        *(uint *)(param_9 + 0x10) = *(uint *)(param_9 + 8);
      }
    }
  }
  return puVar1;
}



// ==== 80257440  gnt4-HSD_ObjFree ====

void gnt4_HSD_ObjFree(int param_1,undefined4 *param_2)

{
  *param_2 = *(undefined4 *)(param_1 + 4);
  *(undefined4 **)(param_1 + 4) = param_2;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  return;
}



// ==== 80257468  gnt4-HSD_ObjAllocInit-bl ====

void gnt4_HSD_ObjAllocInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,void *param_9,int param_10,uint param_11
               ,undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  void *pvVar4;
  
  if (param_9 == (void *)0x0) {
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_objalloc_c_803ad158,0x182,&DAT_80435f88,param_12,param_13,param_14,
                               param_15,param_16);
    DAT_804369f0 = (void *)0x0;
  }
  else {
    puVar1 = &DAT_804369f0;
    while (pvVar4 = (void *)*puVar1, pvVar4 != (void *)0x0) {
      if (pvVar4 == param_9) {
        *puVar1 = *(undefined4 *)((int)pvVar4 + 0x28);
      }
      else {
        puVar1 = (undefined4 *)((int)pvVar4 + 0x28);
      }
    }
  }
  gnt4_memset(param_9,0,0x2c);
  *(undefined4 *)((int)param_9 + 0x14) = 0xffffffff;
  *(undefined4 *)((int)param_9 + 0x18) = 0;
  *(undefined4 *)((int)param_9 + 0x1c) = 0xffffffff;
  if (0x20 < param_11) {
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_objalloc_c_803ad158,0x18d,s_align_<__32_803ad164,param_12,param_13,
                               param_14,param_15,param_16);
  }
  iVar2 = gnt4_HSD_GetNbBits_bl(param_11);
  if (iVar2 != 1) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_objalloc_c_803ad158,0x18e,s_HSD_GetNbBits_align_____1_803ad170,param_12,
                     param_13,param_14,param_15,param_16);
  }
  *(uint *)((int)param_9 + 0x24) = param_11;
  uVar3 = *(int *)((int)param_9 + 0x24) - 1;
  *(uint *)((int)param_9 + 0x20) = param_10 + uVar3 & ~uVar3;
  *(void **)((int)param_9 + 0x28) = DAT_804369f0;
  DAT_804369f0 = param_9;
  return;
}



// ==== 80257598  gnt4-HSD_RObjInitAllocData-bl ====

void gnt4_HSD_RObjInitAllocData_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  uVar1 = gnt4_HSD_ObjAllocInit_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803fa4d8,
                     0x1c,4,in_r6,in_r7,in_r8,in_r9,in_r10);
  gnt4_HSD_ObjAllocInit_bl
            (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803fa504,0xc,4,in_r6
             ,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 802575dc  gnt4-HSD_RObjGetByType-bl ====

undefined4 * gnt4_HSD_RObjGetByType_bl(undefined4 *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  if (param_1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  do {
    if (param_1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    uVar1 = param_1[1];
    if (((int)uVar1 < 0) && ((uVar1 & 0x70000000) == param_2)) {
      if (param_3 == 0) {
        return param_1;
      }
      if (param_3 == (uVar1 & 0xfffffff)) {
        return param_1;
      }
    }
    param_1 = (undefined4 *)*param_1;
  } while( true );
}



// ==== 80257634  gnt4-RObjUpdateFunc-bl ====

void gnt4_RObjUpdateFunc_bl(int param_1,int param_2,float *param_3)

{
  if (param_1 == 0) {
    return;
  }
  if (param_2 != 1) {
    return;
  }
  if (DOUBLE_8043d418 <= (double)*param_3) {
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 0x80000000;
    return;
  }
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0x7fffffff;
  return;
}



// ==== 80257678  gnt4-HSD_RObjAnimAll-bl ====

void gnt4_HSD_RObjAnimAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  if (param_9 != (undefined4 *)0x0) {
    for (; param_9 != (undefined4 *)0x0; param_9 = (undefined4 *)*param_9) {
      if (param_9 != (undefined4 *)0x0) {
        param_1 = gnt4_HSD_AObjInterpretAnim
                            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             (uint *)param_9[6],(uint)param_9,(float *)gnt4_RObjUpdateFunc_bl,
                             param_12,param_13,param_14,param_15,param_16);
      }
    }
  }
  return;
}



// ==== 802576e0  zz_02576e0_ ====

void zz_02576e0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 *param_9,uint param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint extraout_r4;
  
  if (param_9 != (undefined4 *)0x0) {
    uVar1 = param_10 & 0x80;
    for (; param_9 != (undefined4 *)0x0; param_9 = (undefined4 *)*param_9) {
      if (((param_9 != (undefined4 *)0x0) && ((undefined4 *)param_9[6] != (undefined4 *)0x0)) &&
         (uVar1 != 0)) {
        param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                      param_8,(undefined4 *)param_9[6],param_10,param_11,param_12,
                                      param_13,param_14,param_15,param_16);
        param_9[6] = 0;
        param_10 = extraout_r4;
      }
    }
  }
  return;
}



// ==== 80257764  zz_0257764_ ====

void zz_0257764_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10
                ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  
  if (param_9 != (undefined4 *)0x0) {
    for (; param_9 != (undefined4 *)0x0; param_9 = (undefined4 *)*param_9) {
      if ((param_9 != (undefined4 *)0x0) && ((undefined4 *)param_9[6] != (undefined4 *)0x0)) {
        param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                      param_8,(undefined4 *)param_9[6],param_10,param_11,param_12,
                                      param_13,param_14,param_15,param_16);
        param_9[6] = 0;
        param_10 = extraout_r4;
      }
    }
  }
  return;
}



// ==== 802577d0  gnt4-HSD_RObjReqAnimAllByFlags-bl ====

void gnt4_HSD_RObjReqAnimAllByFlags_bl(double param_1,undefined4 *param_2,uint param_3)

{
  if (param_2 != (undefined4 *)0x0) {
    for (; param_2 != (undefined4 *)0x0; param_2 = (undefined4 *)*param_2) {
      if (((param_2 != (undefined4 *)0x0) && ((uint *)param_2[6] != (uint *)0x0)) &&
         ((param_3 & 0x80) != 0)) {
        gnt4_HSD_AObjReqAnim(param_1,(uint *)param_2[6]);
      }
    }
  }
  return;
}



// ==== 80257854  gnt4-HSD_RObjReqAnimAll-bl ====

void gnt4_HSD_RObjReqAnimAll_bl(double param_1,undefined4 *param_2)

{
  if (param_2 != (undefined4 *)0x0) {
    for (; param_2 != (undefined4 *)0x0; param_2 = (undefined4 *)*param_2) {
      if ((param_2 != (undefined4 *)0x0) && ((uint *)param_2[6] != (uint *)0x0)) {
        gnt4_HSD_AObjReqAnim(param_1,(uint *)param_2[6]);
      }
    }
  }
  return;
}



// ==== 802578c0  gnt4-HSD_RObjAddAnimAll-bl ====

void gnt4_HSD_RObjAddAnimAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 *param_10
               ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint *puVar1;
  undefined4 *extraout_r4;
  undefined4 *puVar2;
  
  if ((param_9 != (undefined4 *)0x0) && (puVar2 = param_10, param_10 != (undefined4 *)0x0)) {
    for (; (param_9 != (undefined4 *)0x0 && (puVar2 != (undefined4 *)0x0));
        puVar2 = (undefined4 *)*puVar2) {
      if ((param_9 != (undefined4 *)0x0) && (puVar2 != (undefined4 *)0x0)) {
        if ((undefined4 *)param_9[6] != (undefined4 *)0x0) {
          param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,(undefined4 *)param_9[6],param_10,param_11,param_12,
                                        param_13,param_14,param_15,param_16);
          param_10 = extraout_r4;
        }
        puVar1 = gnt4_HSD_AObjLoadDesc
                           (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (uint *)puVar2[1],param_10,param_11,param_12,param_13,param_14,param_15,
                            param_16);
        param_9[6] = puVar1;
      }
      param_9 = (undefined4 *)*param_9;
    }
  }
  return;
}



// ==== 80257950  gnt4-HSD_RObjGetGlobalPosition-bl ====

/* WARNING: Removing unreachable block (ram,0x80257a18) */

void gnt4_HSD_RObjGetGlobalPosition_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  float fVar6;
  undefined4 *puVar7;
  int *piVar8;
  uint uVar9;
  undefined4 *puVar10;
  double extraout_f1;
  double dVar11;
  undefined8 uVar12;
  float local_38;
  float local_34;
  float local_30;
  
  uVar12 = gnt4__savegpr_26_bl();
  puVar10 = (undefined4 *)((ulonglong)uVar12 >> 0x20);
  puVar7 = &DAT_802b5270;
  uVar9 = 0;
  local_38 = DAT_802b5270;
  local_34 = DAT_802b5274;
  local_30 = DAT_802b5278;
  pcVar5 = (char *)param_11;
  fVar6 = DAT_802b5270;
  dVar11 = extraout_f1;
  if (puVar10 != (undefined4 *)0x0) {
    for (; puVar10 != (undefined4 *)0x0; puVar10 = (undefined4 *)*puVar10) {
      uVar4 = puVar10[1];
      uVar2 = countLeadingZeros(0x10000000 - (uVar4 & 0x70000000));
      if (((uVar2 >> 5 != 0) && ((uVar4 & 0x80000000) != 0)) &&
         (uVar2 = countLeadingZeros(puVar10),
         (uint)uVar12 == (uVar4 & 0xfffffff & ~-(uVar2 >> 5 & 1)))) {
        if (puVar10[2] == 0) {
          pcVar5 = s_rp_>u_jobj_803ad190;
          dVar11 = (double)gnt4___assert_bl(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,&DAT_80435f90,0x1f2,s_rp_>u_jobj_803ad190,fVar6,
                                            puVar7,param_14,param_15,param_16);
        }
        piVar8 = (int *)puVar10[2];
        if (piVar8 != (int *)0x0) {
          uVar2 = piVar8[5];
          bVar1 = false;
          if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (bVar1) {
            gnt4_HSD_JObjSetupMatrixSub_bl
                      (dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar8,uVar2,
                       pcVar5,fVar6,puVar7,param_14,param_15,param_16);
          }
        }
        iVar3 = puVar10[2];
        uVar9 = uVar9 + 1;
        param_3 = (double)local_34;
        local_38 = local_38 + *(float *)(iVar3 + 0x50);
        param_4 = (double)local_38;
        dVar11 = (double)local_30;
        local_34 = (float)(param_3 + (double)*(float *)(iVar3 + 0x60));
        param_2 = (double)local_34;
        local_30 = (float)(dVar11 + (double)*(float *)(iVar3 + 0x70));
      }
    }
    if (uVar9 != 0) {
      fVar6 = FLOAT_8043d420 /
              (float)((double)CONCAT44(0x43300000,uVar9 ^ 0x80000000) - DOUBLE_8043d428);
      *param_11 = fVar6 * local_38;
      param_11[1] = fVar6 * local_34;
      param_11[2] = fVar6 * local_30;
    }
  }
  gnt4__restgpr_26_bl();
  return;
}



// ==== 80257b04  gnt4-resolveCnsDirUp-bl ====

/* WARNING: Removing unreachable block (ram,0x80257bf8) */
/* WARNING: Removing unreachable block (ram,0x80257d98) */

void gnt4_resolveCnsDirUp_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined *param_11)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  float *pfVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int *piVar13;
  undefined4 *puVar14;
  uint uVar15;
  undefined4 *puVar16;
  double extraout_f1;
  double dVar17;
  double dVar18;
  undefined8 uVar19;
  float local_90;
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
  undefined4 local_5c;
  undefined4 local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  char *local_40;
  float local_3c;
  float local_38;
  float local_34;
  undefined4 local_30;
  uint uStack_2c;
  
  uVar19 = gnt4__savegpr_24_bl();
  puVar16 = (undefined4 *)((ulonglong)uVar19 >> 0x20);
  iVar4 = (int)uVar19;
  uVar15 = 0;
  local_3c = DAT_802b527c;
  local_38 = DAT_802b5280;
  local_34 = DAT_802b5284;
  local_48 = DAT_802b5288;
  local_44 = DAT_802b528c;
  local_40 = DAT_802b5290;
  local_6c = DAT_802b5270;
  local_68 = DAT_802b5274;
  local_64 = DAT_802b5278;
  pcVar6 = DAT_802b5290;
  fVar8 = DAT_802b528c;
  fVar9 = DAT_802b5288;
  fVar10 = DAT_802b5284;
  fVar11 = DAT_802b5280;
  fVar12 = DAT_802b527c;
  puVar14 = puVar16;
  dVar17 = extraout_f1;
  if (puVar16 != (undefined4 *)0x0) {
    for (; puVar14 != (undefined4 *)0x0; puVar14 = (undefined4 *)*puVar14) {
      uVar5 = puVar14[1];
      uVar2 = countLeadingZeros(0x10000000 - (uVar5 & 0x70000000));
      if (((uVar2 >> 5 != 0) && ((uVar5 & 0x80000000) != 0)) &&
         (uVar2 = countLeadingZeros(puVar14), (uVar5 & 0xfffffff & ~-(uVar2 >> 5 & 1)) == 2)) {
        if (puVar14[2] == 0) {
          pcVar6 = s_rp_>u_jobj_803ad190;
          dVar17 = (double)gnt4___assert_bl(dVar17,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,&DAT_80435f90,0x1f2,s_rp_>u_jobj_803ad190,fVar8,
                                            fVar9,fVar10,fVar11,fVar12);
        }
        piVar13 = (int *)puVar14[2];
        if (piVar13 != (int *)0x0) {
          uVar2 = piVar13[5];
          bVar1 = false;
          if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (bVar1) {
            gnt4_HSD_JObjSetupMatrixSub_bl
                      (dVar17,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar13,uVar2,
                       pcVar6,fVar8,fVar9,fVar10,fVar11,fVar12);
          }
        }
        iVar3 = puVar14[2];
        uVar15 = uVar15 + 1;
        param_3 = (double)local_68;
        local_6c = local_6c + *(float *)(iVar3 + 0x50);
        param_4 = (double)local_6c;
        dVar17 = (double)local_64;
        local_68 = (float)(param_3 + (double)*(float *)(iVar3 + 0x60));
        param_2 = (double)local_68;
        local_64 = (float)(dVar17 + (double)*(float *)(iVar3 + 0x70));
      }
    }
    if (uVar15 != 0) {
      uStack_2c = uVar15 ^ 0x80000000;
      local_30 = 0x43300000;
      param_4 = (double)FLOAT_8043d420;
      param_3 = (double)(float)(param_4 /
                               (double)(float)((double)CONCAT44(0x43300000,uStack_2c) -
                                              DOUBLE_8043d428));
      local_54 = (float)(param_3 * (double)local_6c);
      param_2 = (double)local_54;
      local_50 = (float)(param_3 * (double)local_68);
      local_4c = (float)(param_3 * (double)local_64);
    }
  }
  if (uVar15 != 0) {
    local_60 = *(float *)(iVar4 + 0x50);
    pcVar6 = (char *)&local_54;
    local_5c = *(undefined4 *)(iVar4 + 0x60);
    local_58 = *(undefined4 *)(iVar4 + 0x70);
    dVar17 = (double)gnt4_PSVECSubtract_bl((float *)pcVar6,&local_60,(float *)pcVar6);
    uVar15 = 0;
    local_78 = DAT_802b5270;
    local_74 = DAT_802b5274;
    local_70 = DAT_802b5278;
    if (puVar16 != (undefined4 *)0x0) {
      for (; puVar16 != (undefined4 *)0x0; puVar16 = (undefined4 *)*puVar16) {
        uVar5 = puVar16[1];
        uVar2 = countLeadingZeros(0x10000000 - (uVar5 & 0x70000000));
        if (((uVar2 >> 5 != 0) && ((uVar5 & 0x80000000) != 0)) &&
           (uVar2 = countLeadingZeros(puVar16), (uVar5 & 0xfffffff & ~-(uVar2 >> 5 & 1)) == 3)) {
          if (puVar16[2] == 0) {
            pcVar6 = s_rp_>u_jobj_803ad190;
            dVar17 = (double)gnt4___assert_bl(dVar17,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,&DAT_80435f90,0x1f2,s_rp_>u_jobj_803ad190,
                                              fVar8,fVar9,fVar10,fVar11,fVar12);
          }
          piVar13 = (int *)puVar16[2];
          if (piVar13 != (int *)0x0) {
            uVar2 = piVar13[5];
            bVar1 = false;
            if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
              bVar1 = true;
            }
            if (bVar1) {
              gnt4_HSD_JObjSetupMatrixSub_bl
                        (dVar17,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar13,
                         uVar2,pcVar6,fVar8,fVar9,fVar10,fVar11,fVar12);
            }
          }
          iVar3 = puVar16[2];
          uVar15 = uVar15 + 1;
          param_3 = (double)local_74;
          local_78 = local_78 + *(float *)(iVar3 + 0x50);
          param_4 = (double)local_78;
          dVar17 = (double)local_70;
          local_74 = (float)(param_3 + (double)*(float *)(iVar3 + 0x60));
          param_2 = (double)local_74;
          local_70 = (float)(dVar17 + (double)*(float *)(iVar3 + 0x70));
        }
      }
      if (uVar15 != 0) {
        uStack_2c = uVar15 ^ 0x80000000;
        local_30 = 0x43300000;
        fVar8 = FLOAT_8043d420 / (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8043d428);
        local_48 = fVar8 * local_78;
        local_44 = fVar8 * local_74;
        local_40 = (char *)(fVar8 * local_70);
      }
    }
    if (uVar15 == 0) {
      dVar17 = gnt4_PSQUATDotProduct_bl(&local_54,&local_48);
      if (ABS((double)(float)((double)FLOAT_8043d420 - dVar17)) < DOUBLE_8043d440) {
        local_40 = (char *)FLOAT_8043d420;
        local_48 = FLOAT_8043d434;
        local_44 = FLOAT_8043d434;
      }
    }
    else {
      gnt4_PSVECSubtract_bl(&local_48,&local_60,&local_48);
    }
    pfVar7 = *(float **)(iVar4 + 0x74);
    if (pfVar7 != (float *)0x0) {
      local_3c = *pfVar7;
      local_38 = pfVar7[1];
      local_34 = pfVar7[2];
    }
    gnt4_PSVECCrossProduct_bl(&local_54,&local_48,&local_90);
    dVar17 = gnt4_PSQUATDotProduct_bl(&local_54,&local_54);
    dVar17 = (double)(FLOAT_8043d420 / (float)((double)FLOAT_8043d430 + dVar17));
    if ((double)FLOAT_8043d434 < dVar17) {
      dVar18 = 1.0 / SQRT(dVar17);
      dVar18 = DOUBLE_8043d418 * dVar18 * -(dVar17 * dVar18 * dVar18 - DOUBLE_8043d438);
      dVar18 = DOUBLE_8043d418 * dVar18 * -(dVar17 * dVar18 * dVar18 - DOUBLE_8043d438);
      dVar17 = (double)(float)(dVar17 * DOUBLE_8043d418 * dVar18 *
                                        -(dVar17 * dVar18 * dVar18 - DOUBLE_8043d438));
    }
    gnt4_PSQUATScale_bl(dVar17,&local_54,&local_54);
    dVar17 = gnt4_PSQUATDotProduct_bl(&local_90,&local_90);
    dVar17 = (double)(FLOAT_8043d420 / (float)((double)FLOAT_8043d430 + dVar17));
    if ((double)FLOAT_8043d434 < dVar17) {
      dVar18 = 1.0 / SQRT(dVar17);
      dVar18 = DOUBLE_8043d418 * dVar18 * -(dVar17 * dVar18 * dVar18 - DOUBLE_8043d438);
      dVar18 = DOUBLE_8043d418 * dVar18 * -(dVar17 * dVar18 * dVar18 - DOUBLE_8043d438);
      dVar17 = (double)(float)(dVar17 * DOUBLE_8043d418 * dVar18 *
                                        -(dVar17 * dVar18 * dVar18 - DOUBLE_8043d438));
    }
    gnt4_PSQUATScale_bl(dVar17,&local_90,&local_90);
    gnt4_PSVECCrossProduct_bl(&local_90,&local_54,&local_48);
    local_84 = local_54 * local_3c;
    local_80 = local_50 * local_3c;
    local_7c = local_4c * local_3c;
    (*(code *)param_11)(iVar4,0x32,&local_84);
    local_84 = local_48 * local_38;
    local_80 = local_44 * local_38;
    local_7c = (float)local_40 * local_38;
    (*(code *)param_11)(iVar4,0x33,&local_84);
    local_84 = local_90 * local_34;
    local_80 = local_8c * local_34;
    local_7c = local_88 * local_34;
    (*(code *)param_11)(iVar4,0x34,&local_84);
    (*(code *)param_11)(iVar4,0x37,0);
  }
  gnt4__restgpr_24_bl();
  return;
}



// ==== 802580ec  gnt4-resolveLimits-bl ====

void gnt4_resolveLimits_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,int param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  bVar1 = false;
  puVar3 = param_9;
  if (param_10 == 0) {
    param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80435f90,0x29e,&DAT_80435fa0,param_12,param_13,
                                       param_14,param_15,param_16);
  }
  for (; (puVar3 != (undefined4 *)0x0 && ((puVar3[1] & 0x70000000) != 0x20000000));
      puVar3 = (undefined4 *)*puVar3) {
  }
  if (puVar3 != (undefined4 *)0x0) {
    for (; param_9 != (undefined4 *)0x0; param_9 = (undefined4 *)*param_9) {
      uVar2 = countLeadingZeros(0x20000000 - (param_9[1] & 0x70000000));
      if (uVar2 >> 5 != 0) {
        switch(param_9[1] & 0xfffffff) {
        default:
          goto def_80258198;
        case 1:
          param_1 = (double)(float)param_9[2];
          if ((double)*(float *)(param_10 + 0x1c) < param_1) {
            *(undefined4 *)(param_10 + 0x1c) = param_9[2];
          }
          break;
        case 2:
          param_1 = (double)(float)param_9[2];
          if (param_1 < (double)*(float *)(param_10 + 0x1c)) {
            *(undefined4 *)(param_10 + 0x1c) = param_9[2];
          }
          break;
        case 3:
          param_1 = (double)(float)param_9[2];
          if ((double)*(float *)(param_10 + 0x20) < param_1) {
            *(undefined4 *)(param_10 + 0x20) = param_9[2];
          }
          break;
        case 4:
          param_1 = (double)(float)param_9[2];
          if (param_1 < (double)*(float *)(param_10 + 0x20)) {
            *(undefined4 *)(param_10 + 0x20) = param_9[2];
          }
          break;
        case 5:
          param_1 = (double)(float)param_9[2];
          if ((double)*(float *)(param_10 + 0x24) < param_1) {
            *(undefined4 *)(param_10 + 0x24) = param_9[2];
          }
          break;
        case 6:
          param_1 = (double)(float)param_9[2];
          if (param_1 < (double)*(float *)(param_10 + 0x24)) {
            *(undefined4 *)(param_10 + 0x24) = param_9[2];
          }
          break;
        case 7:
          param_1 = (double)(float)param_9[2];
          if ((double)*(float *)(param_10 + 0x38) < param_1) {
            *(undefined4 *)(param_10 + 0x38) = param_9[2];
          }
          break;
        case 8:
          param_1 = (double)(float)param_9[2];
          if (param_1 < (double)*(float *)(param_10 + 0x38)) {
            *(undefined4 *)(param_10 + 0x38) = param_9[2];
          }
          break;
        case 9:
          param_1 = (double)(float)param_9[2];
          if ((double)*(float *)(param_10 + 0x3c) < param_1) {
            *(undefined4 *)(param_10 + 0x3c) = param_9[2];
          }
          break;
        case 10:
          param_1 = (double)(float)param_9[2];
          if (param_1 < (double)*(float *)(param_10 + 0x3c)) {
            *(undefined4 *)(param_10 + 0x3c) = param_9[2];
          }
          break;
        case 0xb:
          param_1 = (double)(float)param_9[2];
          if ((double)*(float *)(param_10 + 0x3c) < param_1) {
            *(undefined4 *)(param_10 + 0x3c) = param_9[2];
          }
          break;
        case 0xc:
          param_1 = (double)(float)param_9[2];
          if (param_1 < (double)*(float *)(param_10 + 0x3c)) {
            *(undefined4 *)(param_10 + 0x3c) = param_9[2];
          }
        }
        bVar1 = true;
      }
def_80258198:
    }
    if (bVar1) {
      gnt4_HSD_JObjMakeMatrix
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,0x20000000
                 ,(undefined *)0x0,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 802582f4  gnt4-HSD_RObjUpdateAll-bl ====

/* WARNING: Removing unreachable block (ram,0x80258758) */
/* WARNING: Removing unreachable block (ram,0x80258750) */
/* WARNING: Removing unreachable block (ram,0x8025830c) */
/* WARNING: Removing unreachable block (ram,0x80258304) */
/* WARNING: Removing unreachable block (ram,0x802583cc) */
/* WARNING: Removing unreachable block (ram,0x80258580) */
/* WARNING: Removing unreachable block (ram,0x80258350) */

void gnt4_HSD_RObjUpdateAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  char *pcVar8;
  code *pcVar9;
  float *pfVar10;
  undefined4 *puVar11;
  int *piVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  double extraout_f1;
  double dVar16;
  double dVar17;
  double dVar18;
  double in_f30;
  double in_f31;
  double dVar19;
  double in_ps30_1;
  double in_ps31_1;
  undefined8 uVar20;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80 [4];
  float local_70 [4];
  float local_60 [4];
  undefined4 local_50;
  uint uStack_4c;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  uVar20 = gnt4__savegpr_25_bl();
  puVar11 = (undefined4 *)((ulonglong)uVar20 >> 0x20);
  iVar4 = (int)uVar20;
  if (puVar11 != (undefined4 *)0x0) {
    uVar14 = 0;
    pcVar8 = (char *)&DAT_802b5270;
    local_a4 = DAT_802b5270;
    local_a0 = DAT_802b5274;
    local_9c = DAT_802b5278;
    dVar16 = extraout_f1;
    for (puVar6 = puVar11; puVar6 != (undefined4 *)0x0; puVar6 = (undefined4 *)*puVar6) {
      uVar5 = puVar6[1];
      uVar7 = countLeadingZeros(0x10000000 - (uVar5 & 0x70000000));
      if (((uVar7 >> 5 != 0) && ((uVar5 & 0x80000000) != 0)) &&
         (uVar7 = countLeadingZeros(puVar6), (uVar5 & 0xfffffff & ~-(uVar7 >> 5 & 1)) == 1)) {
        if (puVar6[2] == 0) {
          pcVar8 = s_rp_>u_jobj_803ad190;
          dVar16 = (double)gnt4___assert_bl(dVar16,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,&DAT_80435f90,0x1f2,s_rp_>u_jobj_803ad190,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        piVar12 = (int *)puVar6[2];
        if (piVar12 != (int *)0x0) {
          uVar7 = piVar12[5];
          bVar2 = false;
          if (((uVar7 & 0x800000) == 0) && ((uVar7 & 0x40) != 0)) {
            bVar2 = true;
          }
          if (bVar2) {
            gnt4_HSD_JObjSetupMatrixSub_bl
                      (dVar16,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar12,uVar7,
                       pcVar8,param_12,param_13,param_14,param_15,param_16);
          }
        }
        iVar13 = puVar6[2];
        uVar14 = uVar14 + 1;
        param_3 = (double)local_a0;
        local_a4 = local_a4 + *(float *)(iVar13 + 0x50);
        param_4 = (double)local_a4;
        dVar16 = (double)local_9c;
        local_a0 = (float)(param_3 + (double)*(float *)(iVar13 + 0x60));
        param_2 = (double)local_a0;
        local_9c = (float)(dVar16 + (double)*(float *)(iVar13 + 0x70));
      }
    }
    if (uVar14 != 0) {
      uStack_4c = uVar14 ^ 0x80000000;
      local_50 = 0x43300000;
      param_4 = (double)FLOAT_8043d420;
      param_3 = (double)(float)(param_4 /
                               (double)(float)((double)CONCAT44(0x43300000,uStack_4c) -
                                              DOUBLE_8043d428));
      local_8c = (float)(param_3 * (double)local_a4);
      param_2 = (double)local_8c;
      local_88 = (float)(param_3 * (double)local_a0);
      local_84 = (float)(param_3 * (double)local_9c);
      (*(code *)param_11)(iVar4,0x35,&local_8c);
      dVar16 = (double)(*(code *)param_11)(iVar4,0x38,0);
    }
    pcVar9 = (code *)param_11;
    dVar16 = (double)gnt4_resolveCnsDirUp_bl
                               (dVar16,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                puVar11,iVar4,param_11);
    if (iVar4 == 0) {
      pcVar9 = (code *)&DAT_80435fa8;
      dVar16 = (double)gnt4___assert_bl(dVar16,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,&DAT_80435f90,0x276,&DAT_80435fa8,param_12,param_13,
                                        param_14,param_15,param_16);
    }
    puVar6 = puVar11;
    if (puVar11 == (undefined4 *)0x0) {
      puVar6 = (undefined4 *)0x0;
    }
    else {
      for (; puVar6 != (undefined4 *)0x0; puVar6 = (undefined4 *)*puVar6) {
        pcVar9 = (code *)puVar6[1];
        if ((((int)pcVar9 < 0) && (((uint)pcVar9 & 0x70000000) == 0x10000000)) &&
           (((uint)pcVar9 & 0xfffffff) == 4)) goto LAB_80258550;
      }
      puVar6 = (undefined4 *)0x0;
    }
LAB_80258550:
    if (puVar6 != (undefined4 *)0x0) {
      piVar12 = (int *)puVar6[2];
      if (piVar12 == (int *)0x0) {
        gnt4___assert_bl(dVar16,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435f98,0x47c,&DAT_80435fa0,param_12,param_13,param_14,param_15,
                         param_16);
      }
      else {
        uVar14 = piVar12[5];
        bVar2 = false;
        if (((uVar14 & 0x800000) == 0) && ((uVar14 & 0x40) != 0)) {
          bVar2 = true;
        }
        if (bVar2) {
          gnt4_HSD_JObjSetupMatrixSub_bl
                    (dVar16,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar12,uVar14,
                     pcVar9,param_12,param_13,param_14,param_15,param_16);
        }
      }
      gnt4_PSMTXCopy_bl((float *)(piVar12 + 0x11),local_80);
      iVar13 = 0;
      dVar16 = (double)FLOAT_8043d430;
      puVar6 = &DAT_803ad19c;
      dVar19 = (double)FLOAT_8043d434;
      iVar15 = 0;
      pfVar10 = local_80;
      do {
        local_98 = *pfVar10;
        local_94 = pfVar10[4];
        local_90 = pfVar10[8];
        dVar17 = gnt4_PSVECMag_bl(&local_98);
        if (dVar16 < dVar17) {
          dVar17 = (double)(float)((double)FLOAT_8043d420 / dVar17);
        }
        iVar3 = iVar4 + iVar15;
        param_5 = (double)(*(float *)(iVar3 + 100) * *(float *)(iVar3 + 100) +
                          *(float *)(iVar3 + 0x54) * *(float *)(iVar3 + 0x54) +
                          *(float *)(iVar3 + 0x44) * *(float *)(iVar3 + 0x44));
        if (dVar19 < param_5) {
          dVar18 = 1.0 / SQRT(param_5);
          dVar18 = DOUBLE_8043d418 * dVar18 * -(param_5 * dVar18 * dVar18 - DOUBLE_8043d438);
          dVar18 = DOUBLE_8043d418 * dVar18 * -(param_5 * dVar18 * dVar18 - DOUBLE_8043d438);
          param_5 = (double)(float)(param_5 *
                                   DOUBLE_8043d418 * dVar18 *
                                   -(param_5 * dVar18 * dVar18 - DOUBLE_8043d438));
          param_4 = DOUBLE_8043d418;
        }
        fVar1 = (float)(dVar17 * param_5);
        local_98 = local_98 * fVar1;
        param_3 = (double)local_98;
        local_94 = local_94 * fVar1;
        param_2 = (double)local_94;
        local_90 = local_90 * fVar1;
        (*(code *)param_11)(iVar4,*puVar6,&local_98);
        iVar13 = iVar13 + 1;
        iVar15 = iVar15 + 4;
        puVar6 = puVar6 + 1;
        pfVar10 = pfVar10 + 1;
      } while (iVar13 < 3);
      dVar16 = (double)(*(code *)param_11)(iVar4,0x37,0);
    }
    uVar20 = gnt4_resolveLimits_bl
                       (dVar16,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar11,iVar4
                        ,param_11,param_12,param_13,param_14,param_15,param_16);
    for (; puVar11 != (undefined4 *)0x0; puVar11 = (undefined4 *)*puVar11) {
      uVar7 = puVar11[1];
      uVar14 = countLeadingZeros(uVar7 & 0x70000000);
      if ((uVar14 >> 5 != 0) && ((uVar7 & 0x80000000) != 0)) {
        uVar20 = gnt4_expEvaluate_bl(uVar20,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     puVar11 + 2,uVar7 & 0xfffffff,iVar4,param_11,param_13,param_14,
                                     param_15,param_16);
      }
    }
  }
  gnt4__restgpr_25_bl();
  return;
}



// ==== 80258778  gnt4-HSD_RObjResolveRefsAll-bl ====

void gnt4_HSD_RObjResolveRefsAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 *param_10
               ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  
  pcVar4 = (char *)0x803b0000;
  for (; (param_9 != (undefined4 *)0x0 && (param_10 != (undefined4 *)0x0));
      param_10 = (undefined4 *)*param_10) {
    if ((param_9 != (undefined4 *)0x0) && (param_10 != (undefined4 *)0x0)) {
      uVar1 = param_9[1] & 0x70000000;
      if (uVar1 == 0x10000000) {
        param_1 = gnt4_HSD_JObjUnrefThis((int *)param_9[2]);
        pcVar4 = (char *)0x0;
        uVar2 = gnt4_HSD_IDGetDataFromTable_bl((undefined *)0x0,param_10[2],(undefined4 *)0x0);
        param_9[2] = uVar2;
        if (param_9[2] == 0) {
          pcVar4 = s_robj_>u_jobj_803ad1dc;
          param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,&DAT_80435f90,0x330,s_robj_>u_jobj_803ad1dc,param_12,param_13,
                                     param_14,param_15,param_16);
        }
        iVar3 = param_9[2];
        if ((iVar3 != 0) &&
           (*(short *)(iVar3 + 6) = *(short *)(iVar3 + 6) + 1, *(short *)(iVar3 + 6) == 0)) {
          pcVar4 = s_HSD_OBJ_o__>ref_count_individual_803ad1f8;
          param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,s_object_h_803ad1ec,0x9e,
                                     s_HSD_OBJ_o__>ref_count_individual_803ad1f8,param_12,param_13,
                                     param_14,param_15,param_16);
        }
      }
      else if ((uVar1 < 0x10000000) && (uVar1 == 0)) {
        param_1 = gnt4_HSD_RvalueResolveRefsAll_bl
                            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             (undefined4 *)param_9[3],*(int *)(param_10[2] + 4),pcVar4,param_12,
                             param_13,param_14,param_15,param_16);
      }
    }
    param_9 = (undefined4 *)*param_9;
  }
  return;
}



// ==== 8025888c  gnt4-HSD_RObjLoadDesc-bl ====

void gnt4_HSD_RObjLoadDesc_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  double extraout_f1;
  double extraout_f1_00;
  double dVar11;
  undefined8 uVar12;
  
  uVar12 = gnt4__savegpr_24_bl();
  puVar2 = (undefined4 *)((ulonglong)uVar12 >> 0x20);
  uVar7 = (undefined4)uVar12;
  if (puVar2 == (undefined4 *)0x0) goto LAB_80258ce8;
  dVar11 = extraout_f1;
  puVar3 = gnt4_HSD_RObjAlloc_bl
                     (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar2,
                      uVar7,param_11,param_12,param_13,param_14,param_15,param_16);
  puVar10 = (undefined4 *)*puVar2;
  if (puVar10 == (undefined4 *)0x0) {
    puVar4 = (undefined4 *)0x0;
  }
  else {
    puVar4 = gnt4_HSD_RObjAlloc_bl
                       (dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar3,uVar7,
                        param_11,param_12,param_13,param_14,param_15,param_16);
    puVar9 = (undefined4 *)*puVar10;
    if (puVar9 == (undefined4 *)0x0) {
      puVar5 = (undefined4 *)0x0;
    }
    else {
      puVar5 = gnt4_HSD_RObjAlloc_bl
                         (dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar4,
                          uVar7,param_11,param_12,param_13,param_14,param_15,param_16);
      puVar8 = (undefined4 *)*puVar9;
      if (puVar8 == (undefined4 *)0x0) {
        puVar6 = (undefined4 *)0x0;
      }
      else {
        puVar6 = gnt4_HSD_RObjAlloc_bl
                           (dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar5,
                            uVar7,param_11,param_12,param_13,param_14,param_15,param_16);
        uVar7 = gnt4_HSD_RObjLoadDesc_bl
                          (dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*puVar8,
                           uVar7,param_11,param_12,param_13,param_14,param_15,param_16);
        *puVar6 = uVar7;
        puVar6[1] = puVar8[1];
        uVar1 = puVar6[1] & 0x70000000;
        dVar11 = extraout_f1_00;
        if (uVar1 == 0x20000000) {
          uVar1 = puVar6[1] & 0xfffffff;
          if ((uVar1 < 7) && (uVar1 != 0)) {
            dVar11 = (double)FLOAT_8043d448;
            puVar6[2] = (float)(dVar11 * (double)(float)puVar8[2]);
          }
          else {
            puVar6[2] = puVar8[2];
          }
        }
        else if (uVar1 < 0x20000000) {
          if (uVar1 != 0x10000000) {
            if ((uVar1 < 0x10000000) && (uVar1 == 0)) {
              dVar11 = (double)gnt4_expLoadDesc_bl(extraout_f1_00,param_2,param_3,param_4,param_5,
                                                   param_6,param_7,param_8);
            }
            else {
LAB_802589d4:
              dVar11 = (double)gnt4_HSD_Panic_bl(extraout_f1_00,param_2,param_3,param_4,param_5,
                                                 param_6,param_7,param_8,&DAT_80435f90,0x37d,
                                                 s_unexpected_type_of_robj__803ad220,param_12,
                                                 param_13,param_14,param_15,param_16);
            }
          }
        }
        else if (uVar1 == 0x40000000) {
          puVar6[2] = *(undefined4 *)puVar8[2];
          puVar6[3] = *(undefined4 *)(puVar8[2] + 4);
        }
        else {
          if ((0x3fffffff < uVar1) || (uVar1 != 0x30000000)) goto LAB_802589d4;
          dVar11 = (double)gnt4_bcexpLoadDesc_bl
                                     (extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7
                                      ,param_8);
          puVar6[1] = puVar6[1] & 0x8fffffff;
        }
      }
      *puVar5 = puVar6;
      puVar5[1] = puVar9[1];
      uVar1 = puVar5[1] & 0x70000000;
      if (uVar1 == 0x20000000) {
        uVar1 = puVar5[1] & 0xfffffff;
        if ((uVar1 < 7) && (uVar1 != 0)) {
          dVar11 = (double)FLOAT_8043d448;
          puVar5[2] = (float)(dVar11 * (double)(float)puVar9[2]);
        }
        else {
          puVar5[2] = puVar9[2];
        }
      }
      else if (uVar1 < 0x20000000) {
        if (uVar1 != 0x10000000) {
          if ((uVar1 < 0x10000000) && (uVar1 == 0)) {
            dVar11 = (double)gnt4_expLoadDesc_bl(dVar11,param_2,param_3,param_4,param_5,param_6,
                                                 param_7,param_8);
          }
          else {
LAB_80258ad0:
            dVar11 = (double)gnt4_HSD_Panic_bl(dVar11,param_2,param_3,param_4,param_5,param_6,
                                               param_7,param_8,&DAT_80435f90,0x37d,
                                               s_unexpected_type_of_robj__803ad220,param_12,param_13
                                               ,param_14,param_15,param_16);
          }
        }
      }
      else if (uVar1 == 0x40000000) {
        puVar5[2] = *(undefined4 *)puVar9[2];
        puVar5[3] = *(undefined4 *)(puVar9[2] + 4);
      }
      else {
        if ((0x3fffffff < uVar1) || (uVar1 != 0x30000000)) goto LAB_80258ad0;
        dVar11 = (double)gnt4_bcexpLoadDesc_bl
                                   (dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        puVar5[1] = puVar5[1] & 0x8fffffff;
      }
    }
    *puVar4 = puVar5;
    puVar4[1] = puVar10[1];
    uVar1 = puVar4[1] & 0x70000000;
    if (uVar1 == 0x20000000) {
      uVar1 = puVar4[1] & 0xfffffff;
      if ((uVar1 < 7) && (uVar1 != 0)) {
        dVar11 = (double)FLOAT_8043d448;
        puVar4[2] = (float)(dVar11 * (double)(float)puVar10[2]);
      }
      else {
        puVar4[2] = puVar10[2];
      }
    }
    else if (uVar1 < 0x20000000) {
      if (uVar1 != 0x10000000) {
        if ((uVar1 < 0x10000000) && (uVar1 == 0)) {
          dVar11 = (double)gnt4_expLoadDesc_bl(dVar11,param_2,param_3,param_4,param_5,param_6,
                                               param_7,param_8);
        }
        else {
LAB_80258bcc:
          dVar11 = (double)gnt4_HSD_Panic_bl(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,
                                             param_8,&DAT_80435f90,0x37d,
                                             s_unexpected_type_of_robj__803ad220,param_12,param_13,
                                             param_14,param_15,param_16);
        }
      }
    }
    else if (uVar1 == 0x40000000) {
      puVar4[2] = *(undefined4 *)puVar10[2];
      puVar4[3] = *(undefined4 *)(puVar10[2] + 4);
    }
    else {
      if ((0x3fffffff < uVar1) || (uVar1 != 0x30000000)) goto LAB_80258bcc;
      dVar11 = (double)gnt4_bcexpLoadDesc_bl
                                 (dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      puVar4[1] = puVar4[1] & 0x8fffffff;
    }
  }
  *puVar3 = puVar4;
  puVar3[1] = puVar2[1];
  uVar1 = puVar3[1] & 0x70000000;
  if (uVar1 == 0x20000000) {
    uVar1 = puVar3[1] & 0xfffffff;
    if ((uVar1 < 7) && (uVar1 != 0)) {
      puVar3[2] = FLOAT_8043d448 * (float)puVar2[2];
    }
    else {
      puVar3[2] = puVar2[2];
    }
    goto LAB_80258ce8;
  }
  if (uVar1 < 0x20000000) {
    if (uVar1 == 0x10000000) goto LAB_80258ce8;
    if ((uVar1 < 0x10000000) && (uVar1 == 0)) {
      gnt4_expLoadDesc_bl(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      goto LAB_80258ce8;
    }
  }
  else {
    if (uVar1 == 0x40000000) {
      puVar3[2] = *(undefined4 *)puVar2[2];
      puVar3[3] = *(undefined4 *)(puVar2[2] + 4);
      goto LAB_80258ce8;
    }
    if ((uVar1 < 0x40000000) && (uVar1 == 0x30000000)) {
      gnt4_bcexpLoadDesc_bl(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      puVar3[1] = puVar3[1] & 0x8fffffff;
      goto LAB_80258ce8;
    }
  }
  gnt4_HSD_Panic_bl(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435f90,
                    0x37d,s_unexpected_type_of_robj__803ad220,param_12,param_13,param_14,param_15,
                    param_16);
LAB_80258ce8:
  gnt4__restgpr_24_bl();
  return;
}



// ==== 80258d00  gnt4-HSD_RObjRemoveAll-bl ====

void gnt4_HSD_RObjRemoveAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 *puVar2;
  
  while (puVar2 = param_9, puVar2 != (undefined4 *)0x0) {
    param_9 = (undefined4 *)*puVar2;
    if (puVar2 != (undefined4 *)0x0) {
      uVar1 = puVar2[1] & 0x70000000;
      if (uVar1 == 0x10000000) {
        param_1 = gnt4_HSD_JObjUnrefThis((int *)puVar2[2]);
        param_10 = extraout_r4;
      }
      else if ((uVar1 < 0x10000000) && (uVar1 == 0)) {
        param_1 = gnt4_HSD_RvalueRemoveAll_bl((undefined4 *)puVar2[3]);
        param_10 = extraout_r4_00;
      }
      gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (undefined4 *)puVar2[6],param_10,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      param_1 = gnt4_HSD_RObjFree_bl(puVar2);
      param_10 = extraout_r4_01;
    }
  }
  return;
}



// ==== 80258d9c  gnt4-HSD_RObjAlloc-bl ====

undefined4 *
gnt4_HSD_RObjAlloc_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 *__s;
  
  __s = gnt4_HSD_ObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803fa4d8,param_10,param_11,param_12,param_13,param_14,param_15,
                          param_16);
  if (__s == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435f90,
                     0x3c5,&DAT_80435fac,param_12,param_13,param_14,param_15,param_16);
  }
  gnt4_memset(__s,0,0x1c);
  return __s;
}



// ==== 80258df8  gnt4-HSD_RObjFree-bl ====

void gnt4_HSD_RObjFree_bl(undefined4 *param_1)

{
  gnt4_HSD_ObjFree(-0x7fc05b28,param_1);
  return;
}



// ==== 80258e24  gnt4-expEvaluate-bl ====

/* WARNING: Removing unreachable block (ram,0x80258f18) */

void gnt4_expEvaluate_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8,
                        undefined4 param_9,undefined4 param_10,undefined4 param_11,
                        undefined *param_12,undefined4 param_13,undefined4 param_14,
                        undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined *puVar7;
  code *pcVar8;
  int iVar9;
  undefined4 *puVar10;
  int *piVar11;
  float *pfVar12;
  double extraout_f1;
  double extraout_f1_00;
  double dVar13;
  undefined8 uVar14;
  float local_48 [3];
  float local_3c;
  float local_38;
  float local_34;
  float local_2c;
  float local_28;
  float local_24;
  
  uVar14 = gnt4__savegpr_24_bl();
  puVar2 = (undefined4 *)((ulonglong)uVar14 >> 0x20);
  iVar5 = (int)uVar14;
  pcVar8 = (code *)param_12;
  dVar13 = extraout_f1;
  if (puVar2[2] == -1) {
    iVar9 = 0;
    for (puVar10 = (undefined4 *)puVar2[1]; puVar10 != (undefined4 *)0x0;
        puVar10 = (undefined4 *)*puVar10) {
      iVar3 = gnt4_HSD_GetNbBits_bl(puVar10[1]);
      iVar9 = iVar9 + iVar3;
    }
    puVar2[2] = iVar9;
  }
  if (DAT_804369f8 == (float *)0x0) {
    if (DAT_804369fc == (undefined *)0x0) {
      DAT_804369fc = (undefined *)0x64;
    }
    DAT_804369f8 = (float *)gnt4_HSD_Alloc_bl((int)DAT_804369fc << 2);
    dVar13 = extraout_f1_00;
  }
  puVar7 = DAT_804369fc;
  if (DAT_804369fc < (undefined *)puVar2[2]) {
    dVar13 = (double)gnt4_OSReport_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,s_Number_of_argment_of_expression_e_803ad254,
                                      (undefined *)puVar2[2],DAT_804369fc,pcVar8,param_13,param_14,
                                      param_15,param_16);
    puVar7 = &DAT_80435fb0;
    dVar13 = (double)gnt4_HSD_Panic_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80435f90,0x41b,&DAT_80435fb0,pcVar8,param_13,
                                       param_14,param_15,param_16);
  }
  pfVar12 = DAT_804369f8;
  for (puVar10 = (undefined4 *)puVar2[1]; puVar10 != (undefined4 *)0x0;
      puVar10 = (undefined4 *)*puVar10) {
    iVar9 = puVar10[2];
    if (iVar9 == 0) {
      puVar7 = &DAT_80435fa0;
      dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,&DAT_80435f90,0x424,&DAT_80435fa0,pcVar8,param_13,
                                        param_14,param_15,param_16);
    }
    piVar11 = (int *)puVar10[2];
    if (piVar11 != (int *)0x0) {
      uVar6 = piVar11[5];
      bVar1 = false;
      if (((uVar6 & 0x800000) == 0) && ((uVar6 & 0x40) != 0)) {
        bVar1 = true;
      }
      if (bVar1) {
        dVar13 = (double)gnt4_HSD_JObjSetupMatrixSub_bl
                                   (dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    piVar11,uVar6,puVar7,pcVar8,param_13,param_14,param_15,param_16)
        ;
      }
    }
    for (uVar6 = 1; (uVar6 != 0 && (uVar6 <= (uint)puVar10[1])); uVar6 = uVar6 << 1) {
      uVar4 = puVar10[1] & uVar6;
      if (uVar4 != 0x400) {
        if ((int)uVar4 < 0x400) {
          if (uVar4 == 0x20) {
            *pfVar12 = *(float *)(iVar9 + 0x3c);
            pfVar12 = pfVar12 + 1;
          }
          else if ((int)uVar4 < 0x20) {
            if (uVar4 == 4) {
              dVar13 = (double)FLOAT_8043d44c;
              *pfVar12 = (float)(dVar13 * (double)*(float *)(iVar9 + 0x24));
              pfVar12 = pfVar12 + 1;
            }
            else if ((int)uVar4 < 4) {
              if (uVar4 == 2) {
                dVar13 = (double)FLOAT_8043d44c;
                *pfVar12 = (float)(dVar13 * (double)*(float *)(iVar9 + 0x20));
                pfVar12 = pfVar12 + 1;
              }
              else if (((int)uVar4 < 2) && (0 < (int)uVar4)) {
                dVar13 = (double)FLOAT_8043d44c;
                *pfVar12 = (float)(dVar13 * (double)*(float *)(iVar9 + 0x1c));
                pfVar12 = pfVar12 + 1;
              }
            }
            else if (uVar4 == 0x10) {
              *pfVar12 = *(float *)(iVar9 + 0x38);
              pfVar12 = pfVar12 + 1;
            }
          }
          else if (uVar4 == 0x100) {
            *pfVar12 = *(float *)(iVar9 + 0x30);
            pfVar12 = pfVar12 + 1;
          }
          else if ((int)uVar4 < 0x100) {
            if (uVar4 == 0x80) {
              *pfVar12 = *(float *)(iVar9 + 0x2c);
              pfVar12 = pfVar12 + 1;
            }
            else if (((int)uVar4 < 0x80) && (uVar4 == 0x40)) {
              *pfVar12 = *(float *)(iVar9 + 0x40);
              pfVar12 = pfVar12 + 1;
            }
          }
          else if (uVar4 == 0x200) {
            *pfVar12 = *(float *)(iVar9 + 0x34);
            pfVar12 = pfVar12 + 1;
          }
        }
        else if (uVar4 == 0x200000) {
          *pfVar12 = *(float *)(iVar9 + 0x60);
          pfVar12 = pfVar12 + 1;
        }
        else if ((int)uVar4 < 0x200000) {
          if (uVar4 == 0x20000) {
            gnt4_HSD_MtxGetRotation_bl((float *)(iVar9 + 0x44),&local_3c);
            dVar13 = (double)FLOAT_8043d44c;
            *pfVar12 = (float)(dVar13 * (double)local_38);
            pfVar12 = pfVar12 + 1;
          }
          else if ((int)uVar4 < 0x20000) {
            if (uVar4 == 0x10000) {
              gnt4_HSD_MtxGetRotation_bl((float *)(iVar9 + 0x44),&local_3c);
              dVar13 = (double)FLOAT_8043d44c;
              *pfVar12 = (float)(dVar13 * (double)local_3c);
              pfVar12 = pfVar12 + 1;
            }
          }
          else if (uVar4 == 0x100000) {
            *pfVar12 = *(float *)(iVar9 + 0x50);
            pfVar12 = pfVar12 + 1;
          }
          else if (((int)uVar4 < 0x100000) && (uVar4 == 0x40000)) {
            gnt4_HSD_MtxGetRotation_bl((float *)(iVar9 + 0x44),&local_3c);
            dVar13 = (double)FLOAT_8043d44c;
            *pfVar12 = (float)(dVar13 * (double)local_34);
            pfVar12 = pfVar12 + 1;
          }
        }
        else if (uVar4 == 0x1000000) {
          dVar13 = (double)gnt4_HSD_MtxGetScale_bl((float *)(iVar9 + 0x44),&local_2c);
          *pfVar12 = local_28;
          pfVar12 = pfVar12 + 1;
        }
        else if ((int)uVar4 < 0x1000000) {
          if (uVar4 == 0x800000) {
            dVar13 = (double)gnt4_HSD_MtxGetScale_bl((float *)(iVar9 + 0x44),&local_2c);
            *pfVar12 = local_2c;
            pfVar12 = pfVar12 + 1;
          }
          else if (((int)uVar4 < 0x800000) && (uVar4 == 0x400000)) {
            *pfVar12 = *(float *)(iVar9 + 0x70);
            pfVar12 = pfVar12 + 1;
          }
        }
        else if (uVar4 == 0x2000000) {
          dVar13 = (double)gnt4_HSD_MtxGetScale_bl((float *)(iVar9 + 0x44),&local_2c);
          *pfVar12 = local_24;
          pfVar12 = pfVar12 + 1;
        }
      }
    }
  }
  if (*(char *)(puVar2 + 3) == '\0') {
    dVar13 = (double)(*(code *)*puVar2)(DAT_804369f8);
  }
  else {
    dVar13 = (double)gnt4_HSD_ByteCodeEval_bl
                               (dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                *puVar2,DAT_804369f8,(char *)puVar2[2],pcVar8,param_13,param_14,
                                param_15,param_16);
  }
  local_48[0] = (float)dVar13;
  if ((iVar5 - 1U < 2) || (iVar5 == 3)) {
    local_48[0] = FLOAT_8043d448 * local_48[0];
  }
  (*(code *)param_12)(param_11,iVar5,local_48);
  gnt4__restgpr_24_bl();
  return;
}



// ==== 802592c8  gnt4-HSD_RvalueRemoveAll-bl ====

void gnt4_HSD_RvalueRemoveAll_bl(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  while (puVar1 = param_1, puVar1 != (undefined4 *)0x0) {
    param_1 = (undefined4 *)*puVar1;
    if (puVar1 != (undefined4 *)0x0) {
      gnt4_HSD_JObjUnrefThis((int *)puVar1[2]);
      gnt4_HSD_ObjFree(-0x7fc05afc,puVar1);
    }
  }
  return;
}



// ==== 80259338  gnt4-expLoadDesc-bl ====

void gnt4_expLoadDesc_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8)

{
  int *__s;
  undefined4 *__s_00;
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined4 *puVar3;
  int *piVar4;
  undefined8 extraout_f1;
  undefined8 uVar5;
  int local_28 [10];
  
  uVar5 = gnt4__savegpr_27_bl();
  __s = (int *)((ulonglong)uVar5 >> 0x20);
  piVar4 = (int *)uVar5;
  uVar1 = 0;
  uVar2 = 0x10;
  uVar5 = extraout_f1;
  gnt4_memset(__s,0,0x10);
  if (piVar4 != (int *)0x0) {
    if (*piVar4 == 0) {
      *__s = (int)&LAB_802592c0;
    }
    else {
      *__s = *piVar4;
    }
    puVar3 = (undefined4 *)piVar4[1];
    piVar4 = local_28;
    local_28[0] = 0;
    if (puVar3 != (undefined4 *)0x0) {
      for (; puVar3[1] != 0; puVar3 = puVar3 + 2) {
        __s_00 = gnt4_HSD_ObjAlloc(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_803fa504,uVar1,uVar2,in_r6,in_r7,in_r8,in_r9,in_r10);
        if (__s_00 == (undefined4 *)0x0) {
          uVar5 = gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_80435f90,0x485,s_rvalue_80435fb4,in_r6,in_r7,in_r8,in_r9,
                                   in_r10);
        }
        uVar1 = 0;
        uVar2 = 0xc;
        gnt4_memset(__s_00,0,0xc);
        *piVar4 = (int)__s_00;
        *(undefined4 *)(*piVar4 + 4) = *puVar3;
        piVar4 = (int *)*piVar4;
      }
    }
    __s[1] = local_28[0];
    __s[2] = -1;
  }
  gnt4__restgpr_27_bl();
  return;
}



// ==== 8025942c  gnt4-bcexpLoadDesc-bl ====

void gnt4_bcexpLoadDesc_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  int *__s;
  undefined4 *__s_00;
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined4 *puVar3;
  int *piVar4;
  undefined8 extraout_f1;
  undefined8 uVar5;
  int local_28 [10];
  
  uVar5 = gnt4__savegpr_27_bl();
  __s = (int *)((ulonglong)uVar5 >> 0x20);
  piVar4 = (int *)uVar5;
  uVar1 = 0;
  uVar2 = 0x10;
  uVar5 = extraout_f1;
  gnt4_memset(__s,0,0x10);
  if (piVar4 != (int *)0x0) {
    if (*piVar4 == 0) {
      *__s = 0;
    }
    else {
      *__s = *piVar4;
    }
    puVar3 = (undefined4 *)piVar4[1];
    piVar4 = local_28;
    local_28[0] = 0;
    if (puVar3 != (undefined4 *)0x0) {
      for (; puVar3[1] != 0; puVar3 = puVar3 + 2) {
        __s_00 = gnt4_HSD_ObjAlloc(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_803fa504,uVar1,uVar2,in_r6,in_r7,in_r8,in_r9,in_r10);
        if (__s_00 == (undefined4 *)0x0) {
          uVar5 = gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_80435f90,0x485,s_rvalue_80435fb4,in_r6,in_r7,in_r8,in_r9,
                                   in_r10);
        }
        uVar1 = 0;
        uVar2 = 0xc;
        gnt4_memset(__s_00,0,0xc);
        *piVar4 = (int)__s_00;
        *(undefined4 *)(*piVar4 + 4) = *puVar3;
        piVar4 = (int *)*piVar4;
      }
    }
    __s[1] = local_28[0];
    __s[2] = -1;
    *(undefined1 *)(__s + 3) = 1;
  }
  gnt4__restgpr_27_bl();
  return;
}



// ==== 80259524  gnt4-HSD_RvalueResolveRefsAll-bl ====

void gnt4_HSD_RvalueResolveRefsAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,int param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  if (param_10 != 0) {
    for (; (param_9 != (undefined4 *)0x0 && (*(int *)(param_10 + 4) != 0)); param_10 = param_10 + 8)
    {
      if ((param_9 != (undefined4 *)0x0) && (param_10 != 0)) {
        uVar3 = gnt4_HSD_JObjUnrefThis((int *)param_9[2]);
        uVar1 = gnt4_HSD_IDGetDataFromTable_bl
                          ((undefined *)0x0,*(uint *)(param_10 + 4),(undefined4 *)0x0);
        param_9[2] = uVar1;
        if (param_9[2] == 0) {
          uVar3 = gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_80435f90,0x4f2,s_rvalue_>jobj_803ad2c0,param_12,param_13,
                                   param_14,param_15,param_16);
        }
        iVar2 = param_9[2];
        if ((iVar2 != 0) &&
           (*(short *)(iVar2 + 6) = *(short *)(iVar2 + 6) + 1, *(short *)(iVar2 + 6) == 0)) {
          gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_object_h_803ad1ec,0x9e,s_HSD_OBJ_o__>ref_count_individual_803ad1f8,
                           param_12,param_13,param_14,param_15,param_16);
        }
      }
      param_9 = (undefined4 *)*param_9;
    }
  }
  return;
}



// ==== 8025960c  zz_025960c_ ====

void zz_025960c_(void)

{
  int iVar1;
  
  iVar1 = gnt4__HSD_MemCheckOwn_bl();
  if (iVar1 != 0) {
    DAT_804369f8 = 0;
    DAT_804369fc = 0;
  }
  return;
}



// ==== 80259644  gnt4-HSD_IDInitAllocData-bl ====

void gnt4_HSD_IDInitAllocData_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_HSD_ObjAllocInit_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803fa530,0xc,4,
             in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 80259674  gnt4-HSD_IDSetup-bl ====

void gnt4_HSD_IDSetup_bl(void)

{
  gnt4_memset(&DAT_803fa55c,0,0x194);
  return;
}



// ==== 802596a4  gnt4-HSD_IDInsertToTable-bl ====

void gnt4_HSD_IDInsertToTable_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined *puVar4;
  undefined8 extraout_f1;
  undefined8 uVar5;
  
  uVar5 = gnt4__savegpr_27_bl();
  puVar4 = (undefined *)((ulonglong)uVar5 >> 0x20);
  uVar3 = (uint)uVar5;
  if (puVar4 == (undefined *)0x0) {
    puVar4 = &DAT_803fa55c;
  }
  iVar1 = (uVar3 % 0x65) * 4;
  for (puVar2 = *(undefined4 **)(puVar4 + iVar1);
      (puVar2 != (undefined4 *)0x0 && (puVar2[1] != uVar3)); puVar2 = (undefined4 *)*puVar2) {
  }
  if (puVar2 == (undefined4 *)0x0) {
    uVar5 = extraout_f1;
    puVar2 = gnt4_HSD_ObjAlloc(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_803fa530,uVar3,param_11,param_12,param_13,param_14,param_15,
                               param_16);
    if (puVar2 == (undefined4 *)0x0) {
      gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435fc0,
                       0x43,s_entry_80435fc8,param_12,param_13,param_14,param_15,param_16);
    }
    gnt4_memset(puVar2,0,0xc);
    puVar2[1] = uVar3;
    puVar2[2] = param_11;
    *puVar2 = *(undefined4 *)(puVar4 + iVar1);
    *(undefined4 **)(puVar4 + iVar1) = puVar2;
  }
  else {
    puVar2[1] = uVar3;
    puVar2[2] = param_11;
  }
  gnt4__restgpr_27_bl();
  return;
}



// ==== 80259790  gnt4-HSD_IDRemoveByIDFromTable-bl ====

void gnt4_HSD_IDRemoveByIDFromTable_bl(undefined *param_1,uint param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (param_1 == (undefined *)0x0) {
    param_1 = &DAT_803fa55c;
  }
  iVar1 = (param_2 % 0x65) * 4;
  puVar2 = *(undefined4 **)(param_1 + iVar1);
  puVar4 = (undefined4 *)0x0;
  while( true ) {
    puVar3 = puVar2;
    if (puVar3 == (undefined4 *)0x0) {
      return;
    }
    if (puVar3[1] == param_2) break;
    puVar2 = (undefined4 *)*puVar3;
    puVar4 = puVar3;
  }
  if (puVar4 == (undefined4 *)0x0) {
    *(undefined4 *)(param_1 + iVar1) = *puVar3;
  }
  else {
    *puVar4 = *puVar3;
  }
  gnt4_HSD_ObjFree(-0x7fc05ad0,puVar3);
  return;
}



// ==== 8025983c  gnt4-HSD_IDGetDataFromTable-bl ====

undefined4 gnt4_HSD_IDGetDataFromTable_bl(undefined *param_1,uint param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  
  if (param_1 == (undefined *)0x0) {
    param_1 = &DAT_803fa55c;
  }
  puVar1 = *(undefined4 **)(param_1 + (param_2 % 0x65) * 4);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      if (param_3 != (undefined4 *)0x0) {
        *param_3 = 0;
      }
      return 0;
    }
    if (puVar1[1] == param_2) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = 1;
  }
  return puVar1[2];
}



// ==== 802598c4  zz_02598c4_ ====

void zz_02598c4_(void)

{
  gnt4_memset(&DAT_803fa55c,0,0x194);
  return;
}



// ==== 802598f4  zz_02598f4_ ====

void zz_02598f4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  if (param_9 != 0) {
    uVar1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                *(undefined4 **)(param_9 + 0x18),param_10,param_11,param_12,param_13
                                ,param_14,param_15,param_16);
    *(undefined4 *)(param_9 + 0x18) = 0;
    zz_0257764_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(undefined4 **)(param_9 + 0x1c),extraout_r4,param_11,param_12,param_13,param_14,
                param_15,param_16);
  }
  return;
}



// ==== 80259938  gnt4-HSD_WObjReqAnim-bl ====

void gnt4_HSD_WObjReqAnim_bl(double param_1,int param_2)

{
  if (param_2 != 0) {
    gnt4_HSD_AObjReqAnim(param_1,*(uint **)(param_2 + 0x18));
    gnt4_HSD_RObjReqAnimAll_bl(param_1,*(undefined4 **)(param_2 + 0x1c));
  }
  return;
}



// ==== 80259984  gnt4-HSD_WObjAddAnim-bl ====

void gnt4_HSD_WObjAddAnim_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint *puVar1;
  undefined4 *extraout_r4;
  undefined4 *puVar2;
  
  if ((param_9 != 0) && (param_10 != (undefined4 *)0x0)) {
    puVar2 = param_10;
    if (*(undefined4 **)(param_9 + 0x18) != (undefined4 *)0x0) {
      param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(undefined4 **)(param_9 + 0x18),param_10,param_11,param_12,
                                    param_13,param_14,param_15,param_16);
      puVar2 = extraout_r4;
    }
    puVar1 = gnt4_HSD_AObjLoadDesc
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (uint *)*param_10,puVar2,param_11,param_12,param_13,param_14,param_15,
                        param_16);
    *(uint **)(param_9 + 0x18) = puVar1;
    gnt4_HSD_RObjAddAnimAll_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(undefined4 **)(param_9 + 0x1c),(undefined4 *)param_10[1],param_11,param_12,param_13
               ,param_14,param_15,param_16);
  }
  return;
}



// ==== 802599ec  gnt4-WObjUpdateFunc-bl ====

void gnt4_WObjUpdateFunc_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10,float *param_11
               ,undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  int iVar1;
  double dVar2;
  float afStack_28 [7];
  
  if (param_9 != 0) {
    if (param_10 == 6) {
      gnt4_HSD_WObjSetPositionY_bl
                ((double)*param_11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,6
                 ,(undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
    }
    else if (param_10 < 6) {
      if (param_10 == 4) {
        if ((double)*param_11 < DOUBLE_8043d450) {
          *param_11 = FLOAT_8043d458;
        }
        dVar2 = DOUBLE_8043d460;
        if (DOUBLE_8043d460 < (double)*param_11) {
          *param_11 = FLOAT_8043d468;
        }
        if (*(int *)(param_9 + 0x18) == 0) {
          dVar2 = (double)gnt4___assert_bl(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,
                                           param_8,&DAT_80435fd0,0x98,s_wobj_>aobj_803ad33c,param_12
                                           ,param_13,param_14,param_15,param_16);
        }
        iVar1 = *(int *)(*(int *)(param_9 + 0x18) + 0x18);
        if (iVar1 == 0) {
          dVar2 = (double)gnt4___assert_bl(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,
                                           param_8,&DAT_80435fd0,0x9a,&DAT_80435fd8,param_12,
                                           param_13,param_14,param_15,param_16);
        }
        if (*(int *)(iVar1 + 0x18) == 0) {
          gnt4___assert_bl(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80435fd0,0x9b,s_jp_>u_spline_803ad348,param_12,param_13,param_14,
                           param_15,param_16);
        }
        gnt4_splArcLengthPoint_bl((double)*param_11,afStack_28,*(byte **)(iVar1 + 0x18));
        gnt4_HSD_WObjSetPosition_bl(param_9,afStack_28);
        *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) | 1;
      }
      else if (3 < param_10) {
        gnt4_HSD_WObjSetPositionX_bl
                  ((double)*param_11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9
                   ,param_10,(undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      }
    }
    else if (param_10 < 8) {
      gnt4_HSD_WObjSetPositionZ_bl
                ((double)*param_11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                 param_10,(undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80259b30  gnt4-HSD_WObjInterpretAnim-bl ====

void gnt4_HSD_WObjInterpretAnim_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  float *pfVar1;
  undefined8 uVar2;
  
  if (param_9 != (int *)0x0) {
    pfVar1 = *(float **)(*param_9 + 0x40);
    uVar2 = gnt4_HSD_AObjInterpretAnim
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       (uint *)param_9[6],(uint)param_9,pfVar1,param_12,param_13,param_14,param_15,
                       param_16);
    gnt4_HSD_RObjAnimAll_bl
              (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               (undefined4 *)param_9[7],extraout_r4,pfVar1,param_12,param_13,param_14,param_15,
               param_16);
  }
  return;
}



// ==== 80259b78  gnt4-WObjLoad-bl ====

undefined4
gnt4_WObjLoad_bl(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar2;
  undefined8 extraout_f1;
  
  uVar2 = gnt4_HSD_WObjSetPosition_bl(param_9,(undefined4 *)(param_10 + 4));
  uVar1 = extraout_r4;
  if (*(undefined4 **)(param_9 + 0x1c) != (undefined4 *)0x0) {
    uVar2 = gnt4_HSD_RObjRemoveAll_bl
                      (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(undefined4 **)(param_9 + 0x1c),extraout_r4,param_11,param_12,param_13,
                       param_14,param_15,param_16);
    uVar1 = extraout_r4_00;
  }
  uVar1 = gnt4_HSD_RObjLoadDesc_bl
                    (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     *(undefined4 *)(param_10 + 0x10),uVar1,param_11,param_12,param_13,param_14,
                     param_15,param_16);
  *(undefined4 *)(param_9 + 0x1c) = uVar1;
  gnt4_HSD_RObjResolveRefsAll_bl
            (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
             *(undefined4 **)(param_9 + 0x1c),*(undefined4 **)(param_10 + 0x10),param_11,param_12,
             param_13,param_14,param_15,param_16);
  return 0;
}



// ==== 80259be0  gnt4-HSD_WObjInit-bl ====

void gnt4_HSD_WObjInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar2;
  undefined8 extraout_f1;
  
  if ((param_9 != 0) && (param_10 != 0)) {
    uVar2 = gnt4_HSD_WObjSetPosition_bl(param_9,(undefined4 *)(param_10 + 4));
    uVar1 = extraout_r4;
    if (*(undefined4 **)(param_9 + 0x1c) != (undefined4 *)0x0) {
      uVar2 = gnt4_HSD_RObjRemoveAll_bl
                        (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         *(undefined4 **)(param_9 + 0x1c),extraout_r4,param_11,param_12,param_13,
                         param_14,param_15,param_16);
      uVar1 = extraout_r4_00;
    }
    uVar1 = gnt4_HSD_RObjLoadDesc_bl
                      (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(undefined4 *)(param_10 + 0x10),uVar1,param_11,param_12,param_13,param_14,
                       param_15,param_16);
    *(undefined4 *)(param_9 + 0x1c) = uVar1;
    gnt4_HSD_RObjResolveRefsAll_bl
              (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(undefined4 **)(param_9 + 0x1c),*(undefined4 **)(param_10 + 0x10),param_11,param_12,
               param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80259c54  gnt4-HSD_WObjLoadDesc-bl ====

int * gnt4_HSD_WObjLoadDesc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int *piVar2;
  
  if (param_9 != (int *)0x0) {
    if ((*param_9 == 0) ||
       (puVar1 = (undefined4 *)
                 gnt4_hsdSearchClassInfo_bl
                           (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*param_9
                            ,param_10,param_11,param_12,param_13,param_14,param_15,param_16),
       puVar1 == (undefined4 *)0x0)) {
      piVar2 = gnt4_HSD_WObjAlloc_bl
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else {
      piVar2 = gnt4_hsdNew_bl(puVar1);
      if (piVar2 == (int *)0x0) {
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435fd0,0x104,&DAT_80435fdc,param_12,param_13,param_14,param_15,
                         param_16);
      }
    }
    (**(code **)(*piVar2 + 0x3c))(piVar2,param_9);
    return piVar2;
  }
  return (int *)0x0;
}



// ==== 80259cec  gnt4-HSD_WObjSetPosition-bl ====

void gnt4_HSD_WObjSetPosition_bl(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    return;
  }
  if (param_2 == (undefined4 *)0x0) {
    return;
  }
  uVar1 = param_2[1];
  *(undefined4 *)(param_1 + 0xc) = *param_2;
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  *(undefined4 *)(param_1 + 0x14) = param_2[2];
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 2;
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xfffffffe;
  return;
}



// ==== 80259d34  gnt4-HSD_WObjSetPositionX-bl ====

/* WARNING: Removing unreachable block (ram,0x80259d84) */

void gnt4_HSD_WObjSetPositionX_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int *piVar3;
  
  if (param_9 != 0) {
    if ((*(uint *)(param_9 + 8) & 1) != 0) {
      if ((*(int *)(param_9 + 0x18) != 0) &&
         (piVar3 = *(int **)(*(int *)(param_9 + 0x18) + 0x18), piVar3 != (int *)0x0)) {
        uVar2 = piVar3[5];
        bVar1 = false;
        if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          gnt4_HSD_JObjSetupMatrixSub_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,uVar2,
                     param_11,param_12,param_13,param_14,param_15,param_16);
        }
        gnt4_PSMTXMultVec_bl
                  ((float *)(piVar3 + 0x11),(float *)(param_9 + 0xc),(float *)(param_9 + 0xc));
      }
      *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) & 0xfffffffe;
    }
    *(float *)(param_9 + 0xc) = (float)param_1;
    *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) | 2;
  }
  return;
}



// ==== 80259e08  gnt4-HSD_WObjSetPositionY-bl ====

/* WARNING: Removing unreachable block (ram,0x80259e58) */

void gnt4_HSD_WObjSetPositionY_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int *piVar3;
  
  if (param_9 != 0) {
    if ((*(uint *)(param_9 + 8) & 1) != 0) {
      if ((*(int *)(param_9 + 0x18) != 0) &&
         (piVar3 = *(int **)(*(int *)(param_9 + 0x18) + 0x18), piVar3 != (int *)0x0)) {
        uVar2 = piVar3[5];
        bVar1 = false;
        if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          gnt4_HSD_JObjSetupMatrixSub_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,uVar2,
                     param_11,param_12,param_13,param_14,param_15,param_16);
        }
        gnt4_PSMTXMultVec_bl
                  ((float *)(piVar3 + 0x11),(float *)(param_9 + 0xc),(float *)(param_9 + 0xc));
      }
      *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) & 0xfffffffe;
    }
    *(float *)(param_9 + 0x10) = (float)param_1;
    *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) | 2;
  }
  return;
}



// ==== 80259edc  gnt4-HSD_WObjSetPositionZ-bl ====

/* WARNING: Removing unreachable block (ram,0x80259f2c) */

void gnt4_HSD_WObjSetPositionZ_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int *piVar3;
  
  if (param_9 != 0) {
    if ((*(uint *)(param_9 + 8) & 1) != 0) {
      if ((*(int *)(param_9 + 0x18) != 0) &&
         (piVar3 = *(int **)(*(int *)(param_9 + 0x18) + 0x18), piVar3 != (int *)0x0)) {
        uVar2 = piVar3[5];
        bVar1 = false;
        if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          gnt4_HSD_JObjSetupMatrixSub_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,uVar2,
                     param_11,param_12,param_13,param_14,param_15,param_16);
        }
        gnt4_PSMTXMultVec_bl
                  ((float *)(piVar3 + 0x11),(float *)(param_9 + 0xc),(float *)(param_9 + 0xc));
      }
      *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) & 0xfffffffe;
    }
    *(float *)(param_9 + 0x14) = (float)param_1;
    *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) | 2;
  }
  return;
}



// ==== 80259fb0  gnt4-HSD_WObjGetPosition-bl ====

/* WARNING: Removing unreachable block (ram,0x8025a00c) */

void gnt4_HSD_WObjGetPosition_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  
  if ((param_9 != 0) && (param_10 != (undefined4 *)0x0)) {
    if ((*(uint *)(param_9 + 8) & 1) != 0) {
      if ((*(int *)(param_9 + 0x18) != 0) &&
         (piVar4 = *(int **)(*(int *)(param_9 + 0x18) + 0x18), piVar4 != (int *)0x0)) {
        uVar3 = piVar4[5];
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          gnt4_HSD_JObjSetupMatrixSub_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar4,uVar3,
                     param_11,param_12,param_13,param_14,param_15,param_16);
        }
        gnt4_PSMTXMultVec_bl
                  ((float *)(piVar4 + 0x11),(float *)(param_9 + 0xc),(float *)(param_9 + 0xc));
      }
      *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) & 0xfffffffe;
    }
    uVar2 = *(undefined4 *)(param_9 + 0x10);
    *param_10 = *(undefined4 *)(param_9 + 0xc);
    param_10[1] = uVar2;
    param_10[2] = *(undefined4 *)(param_9 + 0x14);
  }
  return;
}



// ==== 8025a098  gnt4-HSD_WObjAlloc-bl ====

int * gnt4_HSD_WObjAlloc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int *piVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined **ppuVar2;
  
  ppuVar2 = DAT_80436a00;
  if (DAT_80436a00 == (undefined **)0x0) {
    ppuVar2 = &PTR_gnt4_WObjInfoInit_bl_803ad2f8;
  }
  piVar1 = gnt4_hsdNew_bl(ppuVar2);
  if (piVar1 == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435fd0,
                     599,&DAT_80435fdc,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  return piVar1;
}



// ==== 8025a0f4  gnt4-WObjRelease-bl ====

void gnt4_WObjRelease_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8,int param_9,
                        undefined4 param_10,undefined4 param_11,undefined4 param_12,
                        undefined4 param_13,undefined4 param_14,undefined4 param_15,
                        undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  uVar1 = gnt4_HSD_RObjRemoveAll_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     *(undefined4 **)(param_9 + 0x1c),param_10,param_11,param_12,param_13,param_14,
                     param_15,param_16);
  gnt4_HSD_AObjRemove(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(undefined4 **)(param_9 + 0x18),extraout_r4,param_11,param_12,param_13,
                      param_14,param_15,param_16);
  (**(code **)(DAT_803ad30c + 0x30))(param_9);
  return;
}



// ==== 8025a148  gnt4-WObjAmnesia-bl ====

void gnt4_WObjAmnesia_bl(int param_1)

{
  if (param_1 == DAT_80436a00) {
    DAT_80436a00 = 0;
  }
  (**(code **)(DAT_803ad30c + 0x38))();
  return;
}



// ==== 8025a190  gnt4-WObjInfoInit-bl ====

void gnt4_WObjInfoInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc52d08,
             &PTR_zz_025acb8__803ad548,s_sysdolphin_base_library_803ad37c,s_had_wobj_803ad394,0x44,
             0x20,in_r9,in_r10);
  DAT_803ad328 = gnt4_WObjRelease_bl;
  DAT_803ad330 = gnt4_WObjAmnesia_bl;
  DAT_803ad334 = gnt4_WObjLoad_bl;
  DAT_803ad338 = gnt4_WObjUpdateFunc_bl;
  return;
}



// ==== 8025a210  gnt4-HSD_FogSet-bl ====

/* WARNING: Removing unreachable block (ram,0x8025a4a4) */
/* WARNING: Removing unreachable block (ram,0x8025a220) */

void gnt4_HSD_FogSet_bl(double param_1,double param_2,double param_3,double param_4,double param_5,
                       double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                       undefined4 param_11,undefined4 param_12,undefined4 param_13,
                       undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  float *__s;
  double dVar6;
  double dVar7;
  uint3 local_d8;
  uint3 local_d4;
  float local_d0;
  float local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  float local_b4 [2];
  float local_ac;
  ushort auStack_9c [10];
  float local_88 [2];
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_60;
  undefined4 local_5c;
  float local_50;
  float local_4c;
  undefined4 local_48;
  uint uStack_44;
  longlong local_40;
  longlong local_38;
  longlong local_30;
  
  if (param_9 == 0) {
    dVar6 = (double)FLOAT_8043d470;
    _local_d4 = DAT_8043d518;
    gnt4_GXSetFog_bl(dVar6,dVar6,dVar6,dVar6,0,&local_d4);
  }
  else {
    iVar1 = gnt4_HSD_CObjGetCurrent();
    if (iVar1 == 0) {
      gnt4_HSD_Panic_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        &DAT_80435ff8,0x58,s_You_must_specify_CObj_first__803ad41c,param_12,param_13
                        ,param_14,param_15,param_16);
    }
    _local_d8 = *(undefined4 *)(param_9 + 0x18);
    dVar6 = gnt4_HSD_CObjGetFar_bl(iVar1);
    dVar7 = gnt4_HSD_CObjGetNear_bl(iVar1);
    gnt4_GXSetFog_bl((double)*(float *)(param_9 + 0x10),(double)*(float *)(param_9 + 0x14),dVar7,
                     dVar6,*(uint *)(param_9 + 8),&local_d8);
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 0xc);
    }
    uVar2 = gnt4_HSD_FogAdjGetFlags_bl(iVar1);
    if ((iVar1 == 0) || ((uVar2 & 7) == 0)) {
      gnt4_GXSetFogRangeAdj_bl(0,0,(ushort *)0x0);
    }
    else {
      gnt4_GXGetViewportv_bl(local_b4);
      if ((uVar2 & 1) == 0) {
        uVar5 = (uint)(local_ac * FLOAT_8043d478 + local_b4[0]);
        local_38 = (longlong)(int)uVar5;
      }
      else {
        if (iVar1 == 0) {
          iVar3 = -1;
        }
        else {
          iVar3 = (int)*(short *)(iVar1 + 0xc);
        }
        uStack_44 = iVar3 + 0x140U ^ 0x80000000;
        local_48 = 0x43300000;
        uVar5 = (uint)(local_b4[0] +
                      (local_ac * (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8043d488))
                      / FLOAT_8043d474);
        local_40 = (longlong)(int)uVar5;
      }
      if ((uVar2 & 2) == 0) {
        uVar4 = (uint)local_ac;
        local_30 = (longlong)(int)uVar4;
      }
      else if (iVar1 == 0) {
        uVar4 = 0xffffffff;
      }
      else {
        uVar4 = (uint)*(ushort *)(iVar1 + 0xe);
      }
      if ((uVar2 & 4) == 0) {
        __s = local_88;
        gnt4_memset(__s,0,0x40);
        gnt4_GXGetProjectionv_bl(&local_d0);
        local_30 = (longlong)(int)local_d0;
        if ((int)local_d0 == 0) {
          local_88[0] = local_cc;
          local_80 = local_c8;
          local_74 = local_c4;
          local_70 = local_c0;
          local_60 = local_bc;
          local_5c = local_b8;
          local_50 = FLOAT_8043d47c;
        }
        else {
          local_88[0] = local_cc;
          local_7c = local_c8;
          local_74 = local_c4;
          local_6c = local_c0;
          local_60 = local_bc;
          local_5c = local_b8;
          local_4c = FLOAT_8043d480;
        }
      }
      else if (iVar1 == 0) {
        __s = (float *)0x0;
      }
      else {
        __s = (float *)(iVar1 + 0x10);
      }
      gnt4_GXInitFogAdjTable_bl(auStack_9c,uVar4 & 0xffff,__s);
      gnt4_GXSetFogRangeAdj_bl(1,uVar5 & 0xffff,auStack_9c);
    }
  }
  return;
}



// ==== 8025a4cc  gnt4-HSD_FogLoadDesc-bl ====

int * gnt4_HSD_FogLoadDesc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10
                ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int *piVar2;
  undefined4 extraout_r4;
  undefined8 uVar3;
  
  piVar1 = gnt4_hsdNew_bl(&PTR_gnt4_FogInfoInit_bl_803ad3a0);
  if (piVar1 == (int *)0x0) {
    uVar3 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80435ff8,0xa1,&DAT_80436000,param_12,param_13,param_14,param_15,
                             param_16);
    param_11 = &DAT_80436000;
    gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ff8,
                     0xae,&DAT_80436000,param_12,param_13,param_14,param_15,param_16);
  }
  uVar3 = gnt4_HSD_FogInit_bl((int)piVar1,param_9);
  if ((undefined4 *)param_9[1] != (undefined4 *)0x0) {
    piVar2 = gnt4_HSD_FogAdjLoadDesc_bl
                       (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (undefined4 *)param_9[1],extraout_r4,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    piVar1[3] = (int)piVar2;
  }
  return piVar1;
}



// ==== 8025a55c  gnt4-HSD_FogInit-bl ====

void gnt4_HSD_FogInit_bl(int param_1,undefined4 *param_2)

{
  float afStack_28 [4];
  undefined4 local_18;
  undefined4 local_14;
  
  if (param_1 != 0) {
    if (param_2 == (undefined4 *)0x0) {
      gnt4_GXGetViewportv_bl(afStack_28);
      *(undefined4 *)(param_1 + 8) = 2;
      *(undefined4 *)(param_1 + 0x10) = local_18;
      *(undefined4 *)(param_1 + 0x14) = local_14;
      *(undefined1 *)(param_1 + 0x18) = 0xff;
      *(undefined1 *)(param_1 + 0x19) = 0xff;
      *(undefined1 *)(param_1 + 0x1a) = 0xff;
      *(undefined1 *)(param_1 + 0x1b) = 0xff;
    }
    else {
      *(undefined4 *)(param_1 + 8) = *param_2;
      *(undefined4 *)(param_1 + 0x10) = param_2[2];
      *(undefined4 *)(param_1 + 0x14) = param_2[3];
      *(undefined4 *)(param_1 + 0x18) = param_2[4];
    }
  }
  return;
}



// ==== 8025a5e8  gnt4-HSD_FogAdjLoadDesc-bl ====

int * gnt4_HSD_FogAdjLoadDesc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10
                ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  undefined8 uVar2;
  
  piVar1 = gnt4_hsdNew_bl(&PTR_gnt4_FogAdjInfoInit_bl_803ad3e0);
  if (piVar1 == (int *)0x0) {
    uVar2 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80435ff8,0xf9,&DAT_80436004,param_12,param_13,param_14,param_15,
                             param_16);
    gnt4___assert_bl(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ff8,
                     0x109,&DAT_80436004,param_12,param_13,param_14,param_15,param_16);
  }
  gnt4_HSD_FogAdjInit_bl((int)piVar1,param_9);
  return piVar1;
}



// ==== 8025a664  gnt4-HSD_FogAdjInit-bl ====

void gnt4_HSD_FogAdjInit_bl(int param_1,undefined4 *param_2)

{
  if (param_1 != 0) {
    if (param_2 == (undefined4 *)0x0) {
      *(undefined4 *)(param_1 + 8) = 0;
      *(undefined2 *)(param_1 + 0xe) = 0;
      *(undefined2 *)(param_1 + 0xc) = 0;
      gnt4_memset((void *)(param_1 + 0x10),0,0x40);
    }
    else {
      *(undefined4 *)(param_1 + 8) = *param_2;
      *(undefined2 *)(param_1 + 0xe) = *(undefined2 *)((int)param_2 + 6);
      *(undefined2 *)(param_1 + 0xc) = *(undefined2 *)(param_2 + 1);
      gnt4_memcpy((void *)(param_1 + 0x10),param_2 + 2,0x40);
    }
  }
  return;
}



// ==== 8025a6e0  gnt4-HSD_FogAdjGetFlags-bl ====

undefined4 gnt4_HSD_FogAdjGetFlags_bl(int param_1)

{
  if (param_1 != 0) {
    return *(undefined4 *)(param_1 + 8);
  }
  return 0;
}



// ==== 8025a6f8  gnt4-FogUpdateFunc-bl ====

void gnt4_FogUpdateFunc_bl(int param_1,undefined4 param_2,float *param_3)

{
  int iVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (param_1 != 0) {
    switch(param_2) {
    case 1:
      *(float *)(param_1 + 0x10) = *param_3;
      break;
    case 2:
      *(float *)(param_1 + 0x14) = *param_3;
      break;
    case 5:
      fVar2 = *param_3;
      fVar3 = FLOAT_8043d470;
      if ((FLOAT_8043d470 < fVar2) && (fVar3 = fVar2, FLOAT_8043d480 <= fVar2)) {
        fVar3 = FLOAT_8043d480;
      }
      *(char *)(param_1 + 0x18) = (char)(int)(FLOAT_8043d490 * fVar3);
      break;
    case 6:
      fVar2 = *param_3;
      fVar3 = FLOAT_8043d470;
      if ((FLOAT_8043d470 < fVar2) && (fVar3 = fVar2, FLOAT_8043d480 <= fVar2)) {
        fVar3 = FLOAT_8043d480;
      }
      *(char *)(param_1 + 0x19) = (char)(int)(FLOAT_8043d490 * fVar3);
      break;
    case 7:
      fVar2 = *param_3;
      fVar3 = FLOAT_8043d470;
      if ((FLOAT_8043d470 < fVar2) && (fVar3 = fVar2, FLOAT_8043d480 <= fVar2)) {
        fVar3 = FLOAT_8043d480;
      }
      *(char *)(param_1 + 0x1a) = (char)(int)(FLOAT_8043d490 * fVar3);
      break;
    case 8:
      fVar2 = *param_3;
      fVar3 = FLOAT_8043d470;
      if ((FLOAT_8043d470 < fVar2) && (fVar3 = fVar2, FLOAT_8043d480 <= fVar2)) {
        fVar3 = FLOAT_8043d480;
      }
      *(char *)(param_1 + 0x1b) = (char)(int)(FLOAT_8043d490 * fVar3);
      break;
    case 0x14:
      iVar1 = (int)*param_3;
      if (param_1 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = *(int *)(param_1 + 0xc);
      }
      if (iVar4 != 0) {
        if (iVar1 < -0x13f) {
          *(undefined2 *)(iVar4 + 0xc) = 0xfec0;
        }
        else if (iVar1 < 0x140) {
          *(short *)(iVar4 + 0xc) = (short)iVar1;
        }
        else {
          *(undefined2 *)(iVar4 + 0xc) = 0x140;
        }
      }
      break;
    case 0x15:
      iVar1 = (int)*param_3;
      if (param_1 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = *(int *)(param_1 + 0xc);
      }
      if (iVar4 != 0) {
        if (iVar1 < 1) {
          *(undefined2 *)(iVar4 + 0xe) = 0;
        }
        else if (iVar1 < 0x280) {
          *(short *)(iVar4 + 0xe) = (short)iVar1;
        }
        else {
          *(undefined2 *)(iVar4 + 0xe) = 0x280;
        }
      }
    }
  }
  return;
}



// ==== 8025a928  gnt4-FogRelease-bl ====

void gnt4_FogRelease_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                       double param_5,double param_6,double param_7,double param_8,int param_9,
                       uint param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
                       undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint extraout_r4;
  int *piVar2;
  
  piVar2 = *(int **)(param_9 + 0xc);
  if (piVar2 != (int *)0x0) {
    param_10 = (uint)*(ushort *)(piVar2 + 1);
    uVar1 = countLeadingZeros(0xffff - param_10);
    uVar1 = uVar1 >> 5;
    if (uVar1 == 0) {
      uVar1 = countLeadingZeros(param_10);
      *(ushort *)(piVar2 + 1) = *(ushort *)(piVar2 + 1) - 1;
      uVar1 = uVar1 >> 5;
    }
    if ((uVar1 != 0) && (piVar2 != (int *)0x0)) {
      (**(code **)(*piVar2 + 0x30))(piVar2);
      param_1 = (**(code **)(*piVar2 + 0x34))(piVar2);
      param_10 = extraout_r4;
    }
  }
  gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(undefined4 **)(param_9 + 0x1c),param_10,param_11,param_12,param_13,param_14,
                      param_15,param_16);
  (**(code **)(DAT_803ad3b4 + 0x30))(param_9);
  return;
}



// ==== 8025a9f4  gnt4-FogInfoInit-bl ====

void gnt4_FogInfoInit_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc52c60,
             &PTR_zz_025acb8__803ad548,s_sysdolphin_base_library_803ad494,&DAT_80436008,0x40,0x20,
             in_r9,in_r10);
  DAT_803ad3d0 = gnt4_FogRelease_bl;
  DAT_803ad3dc = gnt4_FogUpdateFunc_bl;
  return;
}



// ==== 8025aa58  gnt4-FogAdjInfoInit-bl ====

void gnt4_FogAdjInfoInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc52c20,
             &PTR_zz_025acb8__803ad548,s_sysdolphin_base_library_803ad494,s_hsd_fogadj_803ad4ac,0x3c
             ,0x54,in_r9,in_r10);
  return;
}



// ==== 8025aa9c  gnt4-HSD_PerfCountEnvelopeBlending-bl ====

void gnt4_HSD_PerfCountEnvelopeBlending_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  if (0x1f < param_9) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436010,
                     0xa4,&DAT_80436018,param_12,param_13,param_14,param_15,param_16);
  }
  *(int *)(&DAT_803ad4c8 + param_9 * 4) = *(int *)(&DAT_803ad4c8 + param_9 * 4) + 1;
  return;
}



// ==== 8025aaf8  gnt4-HSD_ListInitAllocData-bl ====

void gnt4_HSD_ListInitAllocData_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  uVar1 = gnt4_HSD_ObjAllocInit_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803fa6f0,8
                     ,4,in_r6,in_r7,in_r8,in_r9,in_r10);
  gnt4_HSD_ObjAllocInit_bl
            (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803fa71c,0xc,4,in_r6
             ,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 8025ab3c  gnt4-HSD_SListAlloc-bl ====

undefined4 *
gnt4_HSD_SListAlloc_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 *__s;
  
  __s = gnt4_HSD_ObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803fa6f0,param_10,param_11,param_12,param_13,param_14,param_15,
                          param_16);
  if (__s == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_list_c_80436020,0x4c,&DAT_80436028,param_12,param_13,param_14,param_15,
                     param_16);
  }
  gnt4_memset(__s,0,8);
  return __s;
}



// ==== 8025ab98  gnt4-HSD_SListPrepend-bl ====

void gnt4_HSD_SListPrepend_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 *__s;
  undefined4 uVar1;
  
  __s = gnt4_HSD_ObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803fa6f0,param_10,0x80400000,param_12,param_13,param_14,param_15,
                          param_16);
  if (__s == (undefined4 *)0x0) {
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_list_c_80436020,0x4c,&DAT_80436028,param_12,param_13,param_14,
                               param_15,param_16);
  }
  uVar1 = 8;
  gnt4_memset(__s,0,8);
  __s[1] = param_10;
  gnt4_HSD_SListPrependList_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,__s,uVar1,
             param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8025ac18  gnt4-HSD_SListPrependList-bl ====

undefined4 *
gnt4_HSD_SListPrependList_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 *param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  if (param_10 == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_list_c_80436020,0xca,&DAT_80436030,param_12,param_13,param_14,param_15,
                     param_16);
  }
  *param_10 = param_9;
  return param_10;
}



// ==== 8025ac68  gnt4-HSD_SListRemove-bl ====

undefined4 gnt4_HSD_SListRemove_bl(undefined4 *param_1)

{
  undefined4 uVar1;
  
  if (param_1 == (undefined4 *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *param_1;
    gnt4_HSD_ObjFree(-0x7fc05910,param_1);
  }
  return uVar1;
}



// ==== 8025acb8  zz_025acb8_ ====

void zz_025acb8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc52ab8,
             &PTR_gnt4__hsdClassInfoInit_bl_803ad6b0,s_sysdolphin_base_library_803ad584,
             &DAT_80436038,0x3c,8,in_r9,in_r10);
  return;
}



// ==== 8025acfc  FUN_8025acfc ====

/* WARNING: Removing unreachable block (ram,0x8025ae24) */
/* WARNING: Removing unreachable block (ram,0x8025ae1c) */
/* WARNING: Removing unreachable block (ram,0x8025ae14) */
/* WARNING: Removing unreachable block (ram,0x8025ae0c) */
/* WARNING: Removing unreachable block (ram,0x8025ae04) */
/* WARNING: Removing unreachable block (ram,0x8025ad2c) */
/* WARNING: Removing unreachable block (ram,0x8025ad24) */
/* WARNING: Removing unreachable block (ram,0x8025ad1c) */
/* WARNING: Removing unreachable block (ram,0x8025ad14) */
/* WARNING: Removing unreachable block (ram,0x8025ad0c) */

undefined4 FUN_8025acfc(float *param_1,float *param_2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  dVar1 = gnt4_cos_bl((double)(FLOAT_8043d498 * *param_1));
  dVar6 = (double)(float)dVar1;
  dVar1 = gnt4_cos_bl((double)(FLOAT_8043d498 * param_1[1]));
  dVar5 = (double)(float)dVar1;
  dVar1 = gnt4_cos_bl((double)(FLOAT_8043d498 * param_1[2]));
  dVar4 = (double)(float)dVar1;
  dVar1 = gnt4_sin_bl((double)(FLOAT_8043d498 * *param_1));
  dVar3 = (double)(float)dVar1;
  dVar1 = gnt4_sin_bl((double)(FLOAT_8043d498 * param_1[1]));
  dVar2 = (double)(float)dVar1;
  dVar1 = gnt4_sin_bl((double)(FLOAT_8043d498 * param_1[2]));
  dVar1 = (double)(float)dVar1;
  param_2[3] = (float)(dVar6 * (double)(float)(dVar5 * dVar4) +
                      (double)(float)(dVar3 * (double)(float)(dVar2 * dVar1)));
  *param_2 = (float)(dVar3 * (double)(float)(dVar5 * dVar4) -
                    (double)(float)(dVar6 * (double)(float)(dVar2 * dVar1)));
  param_2[1] = (float)(dVar4 * (double)(float)(dVar6 * dVar2) +
                      (double)(float)(dVar1 * (double)(float)(dVar3 * dVar5)));
  param_2[2] = (float)(dVar1 * (double)(float)(dVar6 * dVar5) -
                      (double)(float)(dVar4 * (double)(float)(dVar3 * dVar2)));
  return 1;
}



// ==== 8025ae44  gnt4-_HSD_MemSetCallbacks-bl ====

void gnt4__HSD_MemSetCallbacks_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,int param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  if (param_10 != 0x14) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_memory_c_803ad5a0,0x14,s_size____sizeof___mem_cb__803ad5ac,param_12,param_13,
                     param_14,param_15,param_16);
  }
  DAT_803fa748 = *param_9;
  DAT_803fa74c = param_9[1];
  DAT_803fa750 = param_9[2];
  DAT_803fa754 = param_9[3];
  DAT_803fa758 = param_9[4];
  return;
}



// ==== 8025aeb8  gnt4-_HSD_MemAlloc-bl ====

void gnt4__HSD_MemAlloc_bl(void)

{
  (*DAT_803fa748)();
  return;
}



// ==== 8025aee4  gnt4-_HSD_MemGetRemain-bl ====

void gnt4__HSD_MemGetRemain_bl(void)

{
  (*DAT_803fa754)();
  return;
}



// ==== 8025af14  zz_025af14_ ====

void zz_025af14_(void)

{
  (*DAT_803fa750)();
  return;
}



// ==== 8025af44  gnt4-_HSD_MemCheckOwn-bl ====

void gnt4__HSD_MemCheckOwn_bl(void)

{
  (*DAT_803fa758)();
  return;
}



// ==== 8025af74  gnt4-HSD_Free-bl ====

void gnt4_HSD_Free_bl(void)

{
  (*DAT_803fa74c)();
  return;
}



// ==== 8025afa4  gnt4-HSD_Alloc-bl ====

void gnt4_HSD_Alloc_bl(undefined4 param_1)

{
  (*DAT_803fa748)(param_1,0x20,0);
  return;
}



// ==== 8025afdc  gnt4-HSD_ShadowInitAllocData-bl ====

void gnt4_HSD_ShadowInitAllocData_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_HSD_ObjAllocInit_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803fa760,0x28,4,
             in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 8025b00c  gnt4-HSD_ArchiveParse-bl ====

undefined4
gnt4_HSD_ArchiveParse_bl
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,uint *param_9,
          void *param_10,uint param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  undefined4 uVar2;
  uint uVar3;
  void *pvVar4;
  int iVar5;
  uint uVar6;
  
  if (param_9 == (uint *)0x0) {
    uVar2 = 0xffffffff;
  }
  else {
    gnt4_memset(param_9,0,0x44);
    uVar2 = 0x20;
    param_9[0xf] = param_9[0xf] | 1;
    pvVar4 = param_10;
    gnt4_memcpy(param_9,param_10,0x20);
    if (*param_9 == param_11) {
      uVar3 = 0x20;
      if (param_9[1] != 0) {
        param_9[8] = (int)param_10 + 0x20;
        uVar3 = param_9[1] + 0x20;
      }
      if (param_9[2] != 0) {
        param_9[9] = (int)param_10 + uVar3;
        uVar3 = uVar3 + param_9[2] * 4;
      }
      if (param_9[3] != 0) {
        param_9[10] = (int)param_10 + uVar3;
        uVar3 = uVar3 + param_9[3] * 8;
      }
      if (param_9[4] != 0) {
        param_9[0xb] = (int)param_10 + uVar3;
        uVar3 = uVar3 + param_9[4] * 8;
      }
      if (uVar3 < *param_9) {
        param_9[0xc] = (int)param_10 + uVar3;
      }
      param_9[0x10] = (uint)param_10;
      iVar5 = 0;
      for (uVar3 = 0; uVar3 < param_9[2]; uVar3 = uVar3 + 1) {
        uVar6 = param_9[8];
        piVar1 = (int *)(param_9[9] + iVar5);
        iVar5 = iVar5 + 4;
        *(uint *)(uVar6 + *piVar1) = *(int *)(uVar6 + *piVar1) + uVar6;
      }
      uVar2 = 0;
    }
    else {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_HSD_ArchiveParse__byte_order_mis_803ad5c8,pvVar4,uVar2,param_12,param_13,
                       param_14,param_15,param_16);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}



// ==== 8025b178  zz_025b178_ ====

int zz_025b178_(int param_1,uint param_2)

{
  if ((-1 < (int)param_2) && (param_2 < *(uint *)(param_1 + 0xc))) {
    return *(int *)(param_1 + 0x30) + *(int *)(*(int *)(param_1 + 0x28) + param_2 * 8 + 4);
  }
  return 0;
}



// ==== 8025b1b0  gnt4-HSD_ArchiveGetPublicAddress-bl ====

int gnt4_HSD_ArchiveGetPublicAddress_bl(int param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  uVar2 = 0;
  while( true ) {
    if (*(uint *)(param_1 + 0xc) <= uVar2) {
      return 0;
    }
    iVar1 = gnt4_strcmp((char *)(*(int *)(param_1 + 0x30) +
                                *(int *)(*(int *)(param_1 + 0x28) + iVar3 + 4)),param_2);
    if (iVar1 == 0) break;
    iVar3 = iVar3 + 8;
    uVar2 = uVar2 + 1;
  }
  return *(int *)(param_1 + 0x20) + *(int *)(*(int *)(param_1 + 0x28) + uVar2 * 8);
}



// ==== 8025b254  gnt4-HSD_ArchiveFree-bl ====

void gnt4_HSD_ArchiveFree_bl(int param_1)

{
  if (param_1 != 0) {
    if ((*(uint *)(param_1 + 0x3c) & 1) == 0) {
      if (*(int *)(param_1 + 0x20) != 0) {
        gnt4_HSD_Free_bl();
      }
      if (*(int *)(param_1 + 0x24) != 0) {
        gnt4_HSD_Free_bl();
      }
      if (*(int *)(param_1 + 0x28) != 0) {
        gnt4_HSD_Free_bl();
      }
      if (*(int *)(param_1 + 0x2c) != 0) {
        gnt4_HSD_Free_bl();
      }
      if (*(int *)(param_1 + 0x30) != 0) {
        gnt4_HSD_Free_bl();
      }
      if (*(int *)(param_1 + 0x38) != 0) {
        gnt4_HSD_Free_bl();
      }
    }
    gnt4_HSD_Free_bl();
  }
  return;
}



// ==== 8025b2f4  gnt4-HSD_Randf-bl ====

double gnt4_HSD_Randf_bl(void)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8043d4a8;
  fVar1 = FLOAT_8043d4a0;
  *DAT_80436044 = *DAT_80436044 * 0x343fd + 0x269ec3;
  return (double)((float)((double)CONCAT44(0x43300000,*DAT_80436044 >> 0x10) - dVar2) / fVar1);
}



// ==== 8025b34c  gnt4-HSD_Randi-bl ====

int gnt4_HSD_Randi_bl(int param_1)

{
  uint uVar1;
  
  *DAT_80436044 = *DAT_80436044 * 0x343fd + 0x269ec3;
  uVar1 = param_1 * (*DAT_80436044 >> 0x10);
  return ((int)uVar1 >> 0x10) + (uint)((int)uVar1 < 0 && (uVar1 & 0xffff) != 0);
}



// ==== 8025b388  zz_025b388_ ====

void zz_025b388_(void)

{
  int iVar1;
  
  iVar1 = gnt4__HSD_MemCheckOwn_bl();
  if (iVar1 != 0) {
    DAT_80436044 = &DAT_80436040;
  }
  return;
}



// ==== 8025b3bc  gnt4-HSD_ByteCodeEval-bl ====

/* WARNING: Removing unreachable block (ram,0x8025b5e4) */

void gnt4_HSD_ByteCodeEval_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  char *pcVar6;
  char *pcVar7;
  uint uVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  byte *pbVar12;
  char *unaff_r29;
  uint unaff_r30;
  double extraout_f1;
  double extraout_f1_00;
  double extraout_f1_01;
  double extraout_f1_02;
  double dVar13;
  double dVar14;
  undefined8 uVar15;
  double local_38;
  
  uVar15 = gnt4__savegpr_22_bl();
  pbVar12 = (byte *)((ulonglong)uVar15 >> 0x20);
  piVar10 = (int *)0x0;
  iVar11 = 0;
  pcVar6 = param_11;
  dVar13 = extraout_f1;
  if (pbVar12 == (byte *)0x0) {
LAB_8025c96c:
    gnt4__restgpr_22_bl();
    return;
  }
LAB_8025b3f8:
  if (0 < iVar11) {
    bVar1 = *pbVar12;
    iVar11 = iVar11 + -1;
    pbVar12 = pbVar12 + 1;
    unaff_r29 = (char *)((uint)bVar1 | (int)unaff_r29 << 8);
    if (iVar11 == 0) {
      if (unaff_r30 != 6) {
        if ((int)unaff_r30 < 6) {
          if (unaff_r30 == 3) {
            if (piVar10 == (int *)0x0) {
              pcVar6 = s_stack_8043604c;
              dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,
                                                param_7,param_8,s_bytecode_c_803ad610,0x133,
                                                s_stack_8043604c,param_12,param_13,param_14,param_15
                                                ,param_16);
            }
            if (piVar10[1] != 0) {
              pbVar12 = pbVar12 + (int)unaff_r29;
            }
            piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
            goto LAB_8025b3f8;
          }
          if (2 < (int)unaff_r30) {
            if ((int)unaff_r30 < 5) {
              pbVar12 = pbVar12 + (int)unaff_r29;
            }
            else {
              for (pcVar7 = (char *)0x0; pcVar7 < unaff_r29; pcVar7 = pcVar7 + 1) {
                piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
              }
            }
            goto LAB_8025b3f8;
          }
          if (1 < (int)unaff_r30) {
            if (param_11 <= unaff_r29) {
              pcVar6 = s_operand_<_nb_args_803ad61c;
              dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,
                                                param_7,param_8,s_bytecode_c_803ad610,0x119,
                                                s_operand_<_nb_args_803ad61c,param_12,param_13,
                                                param_14,param_15,param_16);
            }
            piVar10 = (int *)gnt4_HSD_SListPrepend_bl
                                       (dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,piVar10,
                                        *(undefined4 *)((int)uVar15 + (int)unaff_r29 * 4),pcVar6,
                                        param_12,param_13,param_14,param_15,param_16);
            dVar13 = extraout_f1_00;
            goto LAB_8025b3f8;
          }
        }
        else if (unaff_r30 == 0xff) {
          dVar13 = (double)gnt4_HSD_Panic_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                             param_8,s_bytecode_c_803ad610,0x143,
                                             s_not_yet_implemented__803ad658,param_12,param_13,
                                             param_14,param_15,param_16);
        }
        else if (((int)unaff_r30 < 0xff) && (unaff_r30 == 0x3c)) {
          piVar5 = piVar10;
          for (pcVar7 = (char *)0x0; (piVar5 != (int *)0x0 && (pcVar7 < unaff_r29));
              pcVar7 = pcVar7 + 1) {
            piVar5 = (int *)*piVar5;
          }
          if (piVar5 == (int *)0x0) {
            dVar13 = (double)gnt4_OSReport_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_specified_stack_doesn_t_exist____803ad630,
                                              unaff_r29,pcVar6,param_12,param_13,param_14,param_15,
                                              param_16);
            pcVar6 = &DAT_80436048;
            dVar13 = (double)gnt4_HSD_Panic_bl(dVar13,param_2,param_3,param_4,param_5,param_6,
                                               param_7,param_8,s_bytecode_c_803ad610,299,
                                               &DAT_80436048,param_12,param_13,param_14,param_15,
                                               param_16);
          }
          else {
            piVar10 = (int *)gnt4_HSD_SListPrepend_bl
                                       (dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,piVar10,piVar5[1],pcVar6,param_12,param_13,param_14,
                                        param_15,param_16);
            dVar13 = extraout_f1_01;
          }
          goto LAB_8025b3f8;
        }
        pcVar6 = s_unexpected_byte_code__803ad670;
        dVar13 = (double)gnt4_HSD_Panic_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                           param_8,s_bytecode_c_803ad610,0x146,
                                           s_unexpected_byte_code__803ad670,param_12,param_13,
                                           param_14,param_15,param_16);
        goto LAB_8025b3f8;
      }
      piVar10 = (int *)gnt4_HSD_SListPrepend_bl
                                 (dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  piVar10,unaff_r29,pcVar6,param_12,param_13,param_14,param_15,
                                  param_16);
      dVar13 = extraout_f1_02;
    }
    goto LAB_8025b3f8;
  }
  unaff_r30 = (uint)*pbVar12;
  pbVar12 = pbVar12 + 1;
  if (unaff_r30 == 0x20) {
    if (piVar10 == (int *)0x0) {
      pcVar6 = s_stack_8043604c;
      dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,s_bytecode_c_803ad610,0x227,s_stack_8043604c,
                                        param_12,param_13,param_14,param_15,param_16);
    }
    if (*piVar10 == 0) {
      pcVar6 = s_stack_>next_803ad688;
      dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,s_bytecode_c_803ad610,0x227,s_stack_>next_803ad688,
                                        param_12,param_13,param_14,param_15,param_16);
    }
    iVar4 = piVar10[1];
    piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
    piVar10[1] = piVar10[1] - (piVar10[1] / iVar4) * iVar4;
    goto LAB_8025b3f8;
  }
  if (unaff_r30 < 0x20) {
    if (unaff_r30 == 0x10) {
      if (piVar10 == (int *)0x0) {
        pcVar6 = s_stack_8043604c;
        gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         s_bytecode_c_803ad610,0x1ad,s_stack_8043604c,param_12,param_13,param_14,
                         param_15,param_16);
      }
      dVar13 = (double)gnt4_asin_bl((double)(float)piVar10[1],param_2);
      dVar13 = (double)(float)dVar13;
      piVar10[1] = (int)(float)(DOUBLE_8043d4c0 * dVar13);
      goto LAB_8025b3f8;
    }
    if (0xf < unaff_r30) {
      if (unaff_r30 == 0x18) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x1fb,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_bytecode_c_803ad610,0x1fb,s_stack_>next_803ad688,param_12,param_13,
                           param_14,param_15,param_16);
        }
        fVar2 = (float)piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        dVar13 = (double)(float)piVar10[1];
        piVar10[1] = (int)(float)(dVar13 - (double)fVar2);
      }
      else if (unaff_r30 < 0x18) {
        if (unaff_r30 == 0x14) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_bytecode_c_803ad610,0x1c5,s_stack_8043604c,param_12,param_13,param_14
                             ,param_15,param_16);
          }
          dVar13 = (double)gnt4_exp_bl((double)(float)piVar10[1]);
          piVar10[1] = (int)(float)dVar13;
        }
        else if (unaff_r30 < 0x14) {
          if (unaff_r30 == 0x12) {
            if (piVar10 == (int *)0x0) {
              pcVar6 = s_stack_8043604c;
              gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_bytecode_c_803ad610,0x1b9,s_stack_8043604c,param_12,param_13,
                               param_14,param_15,param_16);
            }
            dVar13 = gnt4_atan((double)(float)piVar10[1]);
            dVar13 = (double)(float)dVar13;
            piVar10[1] = (int)(float)(DOUBLE_8043d4c0 * dVar13);
          }
          else if (unaff_r30 < 0x12) {
            if (piVar10 == (int *)0x0) {
              pcVar6 = s_stack_8043604c;
              gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_bytecode_c_803ad610,0x1b3,s_stack_8043604c,param_12,param_13,
                               param_14,param_15,param_16);
            }
            dVar13 = (double)gnt4_acos_bl((double)(float)piVar10[1]);
            dVar13 = (double)(float)dVar13;
            piVar10[1] = (int)(float)(DOUBLE_8043d4c0 * dVar13);
          }
          else {
            if (piVar10 == (int *)0x0) {
              pcVar6 = s_stack_8043604c;
              gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_bytecode_c_803ad610,0x1bf,s_stack_8043604c,param_12,param_13,
                               param_14,param_15,param_16);
            }
            dVar13 = (double)gnt4_log_bl((double)(float)piVar10[1]);
            piVar10[1] = (int)(float)dVar13;
          }
        }
        else if (unaff_r30 == 0x16) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x1da,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          param_4 = (double)(float)piVar10[1];
          if ((double)FLOAT_8043d4b0 < param_4) {
            dVar13 = 1.0 / SQRT(param_4);
            dVar13 = DOUBLE_8043d4c8 * dVar13 * -(param_4 * dVar13 * dVar13 - DOUBLE_8043d4d0);
            dVar14 = DOUBLE_8043d4c8 * dVar13 * -(param_4 * dVar13 * dVar13 - DOUBLE_8043d4d0);
            dVar13 = DOUBLE_8043d4c8 * dVar14;
            param_4 = (double)(float)(param_4 *
                                     dVar13 * -(param_4 * dVar14 * dVar14 - DOUBLE_8043d4d0));
            param_2 = DOUBLE_8043d4d0;
            param_3 = DOUBLE_8043d4c8;
          }
          piVar10[1] = (int)(float)param_4;
        }
        else if (unaff_r30 < 0x16) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_bytecode_c_803ad610,0x1cb,s_stack_8043604c,param_12,param_13,param_14
                             ,param_15,param_16);
          }
          dVar13 = (double)(float)piVar10[1];
          if (dVar13 < (double)FLOAT_8043d4b0) {
            piVar10[1] = (int)(float)-dVar13;
          }
        }
        else {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x1f5,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_bytecode_c_803ad610,0x1f5,s_stack_>next_803ad688,param_12,param_13,
                             param_14,param_15,param_16);
          }
          fVar2 = (float)piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          dVar13 = (double)(float)piVar10[1];
          piVar10[1] = (int)(float)(dVar13 + (double)fVar2);
        }
      }
      else if (unaff_r30 == 0x1c) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x213,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x213,
                                            s_stack_>next_803ad688,param_12,param_13,param_14,
                                            param_15,param_16);
        }
        iVar4 = piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        piVar10[1] = piVar10[1] + iVar4;
      }
      else if (unaff_r30 < 0x1c) {
        if (unaff_r30 == 0x1a) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x207,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_bytecode_c_803ad610,0x207,s_stack_>next_803ad688,param_12,param_13,
                             param_14,param_15,param_16);
          }
          fVar2 = (float)piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          dVar13 = (double)(float)piVar10[1];
          piVar10[1] = (int)(float)(dVar13 / (double)fVar2);
        }
        else if (unaff_r30 < 0x1a) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x201,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_bytecode_c_803ad610,0x201,s_stack_>next_803ad688,param_12,param_13,
                             param_14,param_15,param_16);
          }
          fVar2 = (float)piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          dVar13 = (double)(float)piVar10[1];
          piVar10[1] = (int)(float)(dVar13 * (double)fVar2);
        }
        else {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x20d,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_bytecode_c_803ad610,0x20d,s_stack_>next_803ad688,param_12,param_13,
                             param_14,param_15,param_16);
          }
          fVar2 = (float)piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          param_2 = (double)fVar2;
          dVar13 = (double)gnt4_fmod_bl((double)(float)piVar10[1],param_2);
          piVar10[1] = (int)(float)dVar13;
        }
      }
      else if (unaff_r30 == 0x1e) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x21d,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x21d,
                                            s_stack_>next_803ad688,param_12,param_13,param_14,
                                            param_15,param_16);
        }
        iVar4 = piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        piVar10[1] = piVar10[1] * iVar4;
      }
      else if (unaff_r30 < 0x1e) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x218,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x218,
                                            s_stack_>next_803ad688,param_12,param_13,param_14,
                                            param_15,param_16);
        }
        iVar4 = piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        piVar10[1] = piVar10[1] - iVar4;
      }
      else {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x222,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x222,
                                            s_stack_>next_803ad688,param_12,param_13,param_14,
                                            param_15,param_16);
        }
        iVar4 = piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        piVar10[1] = piVar10[1] / iVar4;
      }
      goto LAB_8025b3f8;
    }
    if (unaff_r30 == 8) {
      if (piVar10 == (int *)0x0) {
        pcVar6 = s_stack_8043604c;
        gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         s_bytecode_c_803ad610,0x17d,s_stack_8043604c,param_12,param_13,param_14,
                         param_15,param_16);
      }
      dVar13 = DOUBLE_8043d4e0;
      local_38 = (double)(CONCAT44(0x43300000,piVar10[1]) ^ 0x80000000);
      piVar10[1] = (int)(float)(local_38 - DOUBLE_8043d4e0);
      goto LAB_8025b3f8;
    }
    if (7 < unaff_r30) {
      if (unaff_r30 == 0xc) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_bytecode_c_803ad610,0x195,s_stack_8043604c,param_12,param_13,param_14,
                           param_15,param_16);
        }
        dVar13 = gnt4_HSD_Randf_bl();
        piVar10[1] = (int)(float)dVar13;
      }
      else if (unaff_r30 < 0xc) {
        if (unaff_r30 == 10) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x189,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          piVar10[1] = -piVar10[1];
        }
        else if (unaff_r30 < 10) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x183,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          piVar10[1] = (int)-(float)piVar10[1];
        }
        else {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,399,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          iVar4 = gnt4_HSD_Randi_bl(2);
          piVar10[1] = iVar4;
        }
      }
      else if (unaff_r30 == 0xe) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_bytecode_c_803ad610,0x1a1,s_stack_8043604c,param_12,param_13,param_14,
                           param_15,param_16);
        }
        dVar13 = gnt4_cos_bl((double)(float)(DOUBLE_8043d4b8 * (double)(float)piVar10[1]));
        piVar10[1] = (int)(float)dVar13;
      }
      else if (unaff_r30 < 0xe) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_bytecode_c_803ad610,0x19b,s_stack_8043604c,param_12,param_13,param_14,
                           param_15,param_16);
        }
        dVar13 = gnt4_sin_bl((double)(float)(DOUBLE_8043d4b8 * (double)(float)piVar10[1]));
        piVar10[1] = (int)(float)dVar13;
      }
      else {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_bytecode_c_803ad610,0x1a7,s_stack_8043604c,param_12,param_13,param_14,
                           param_15,param_16);
        }
        dVar13 = gnt4_tan_bl((double)(float)(DOUBLE_8043d4b8 * (double)(float)piVar10[1]));
        piVar10[1] = (int)(float)dVar13;
      }
      goto LAB_8025b3f8;
    }
    if (unaff_r30 != 5) {
      if (4 < unaff_r30) {
        if (unaff_r30 < 7) {
          iVar11 = 4;
          unaff_r29 = (char *)0x0;
        }
        else {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x178,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          piVar10[1] = (int)(float)piVar10[1];
        }
        goto LAB_8025b3f8;
      }
      if (unaff_r30 != 1) {
        if (unaff_r30 != 0) {
          iVar11 = 2;
          unaff_r29 = (char *)0x0;
        }
        goto LAB_8025b3f8;
      }
      if (piVar10 == (int *)0x0) {
        gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         s_bytecode_c_803ad610,0x153,s_stack_8043604c,param_12,param_13,param_14,
                         param_15,param_16);
      }
      for (; piVar10 != (int *)0x0; piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10)) {
      }
      goto LAB_8025c96c;
    }
  }
  else {
    if (unaff_r30 == 0x30) {
      if (piVar10 == (int *)0x0) {
        pcVar6 = s_stack_8043604c;
        dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,s_bytecode_c_803ad610,0x295,s_stack_8043604c,
                                          param_12,param_13,param_14,param_15,param_16);
      }
      if (*piVar10 == 0) {
        pcVar6 = s_stack_>next_803ad688;
        dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,s_bytecode_c_803ad610,0x295,s_stack_>next_803ad688
                                          ,param_12,param_13,param_14,param_15,param_16);
      }
      iVar9 = piVar10[1];
      piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
      iVar4 = 0;
      if ((piVar10[1] != 0) || (iVar9 != 0)) {
        iVar4 = 1;
      }
      piVar10[1] = iVar4;
      goto LAB_8025b3f8;
    }
    if (unaff_r30 < 0x30) {
      if (unaff_r30 == 0x28) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x1d3,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (piVar10[1] < 0) {
          piVar10[1] = -piVar10[1];
        }
      }
      else if (unaff_r30 < 0x28) {
        if (unaff_r30 == 0x24) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x240,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x240,
                                              s_stack_>next_803ad688,param_12,param_13,param_14,
                                              param_15,param_16);
          }
          iVar4 = piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          if (iVar4 < piVar10[1]) {
            piVar10[1] = iVar4;
          }
        }
        else if (unaff_r30 < 0x24) {
          if (unaff_r30 == 0x22) {
            if (piVar10 == (int *)0x0) {
              pcVar6 = s_stack_8043604c;
              dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,
                                                param_7,param_8,s_bytecode_c_803ad610,0x232,
                                                s_stack_8043604c,param_12,param_13,param_14,param_15
                                                ,param_16);
            }
            if (*piVar10 == 0) {
              pcVar6 = s_stack_>next_803ad688;
              gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_bytecode_c_803ad610,0x232,s_stack_>next_803ad688,param_12,param_13,
                               param_14,param_15,param_16);
            }
            fVar2 = (float)piVar10[1];
            piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
            dVar13 = (double)(float)piVar10[1];
            if ((double)fVar2 < dVar13) {
              piVar10[1] = (int)fVar2;
            }
          }
          else if (unaff_r30 < 0x22) {
            if (piVar10 == (int *)0x0) {
              pcVar6 = s_stack_8043604c;
              dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,
                                                param_7,param_8,s_bytecode_c_803ad610,0x22c,
                                                s_stack_8043604c,param_12,param_13,param_14,param_15
                                                ,param_16);
            }
            if (*piVar10 == 0) {
              pcVar6 = s_stack_>next_803ad688;
              gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_bytecode_c_803ad610,0x22c,s_stack_>next_803ad688,param_12,param_13,
                               param_14,param_15,param_16);
            }
            fVar2 = (float)piVar10[1];
            piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
            param_2 = (double)fVar2;
            dVar13 = (double)gnt4_pow_bl((double)(float)piVar10[1],param_2);
            piVar10[1] = (int)(float)dVar13;
          }
          else {
            if (piVar10 == (int *)0x0) {
              pcVar6 = s_stack_8043604c;
              dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,
                                                param_7,param_8,s_bytecode_c_803ad610,0x239,
                                                s_stack_8043604c,param_12,param_13,param_14,param_15
                                                ,param_16);
            }
            if (*piVar10 == 0) {
              pcVar6 = s_stack_>next_803ad688;
              gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_bytecode_c_803ad610,0x239,s_stack_>next_803ad688,param_12,param_13,
                               param_14,param_15,param_16);
            }
            fVar2 = (float)piVar10[1];
            piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
            dVar13 = (double)(float)piVar10[1];
            if (dVar13 < (double)fVar2) {
              piVar10[1] = (int)fVar2;
            }
          }
        }
        else if (unaff_r30 == 0x26) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x24e,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_bytecode_c_803ad610,0x24e,s_stack_>next_803ad688,param_12,param_13,
                             param_14,param_15,param_16);
          }
          fVar2 = (float)piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          param_2 = (double)fVar2;
          if ((double)FLOAT_8043d4b0 == param_2) {
            if ((double)(float)piVar10[1] < (double)FLOAT_8043d4b0) {
              dVar13 = (double)FLOAT_8043d4dc;
            }
            else {
              dVar13 = (double)FLOAT_8043d4d8;
            }
          }
          else {
            dVar13 = (double)gnt4_atan2_bl((double)(float)piVar10[1],param_2);
            dVar13 = (double)(float)dVar13;
          }
          piVar10[1] = (int)(float)(DOUBLE_8043d4c0 * dVar13);
        }
        else if (unaff_r30 < 0x26) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x247,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x247,
                                              s_stack_>next_803ad688,param_12,param_13,param_14,
                                              param_15,param_16);
          }
          iVar4 = piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          if (piVar10[1] < iVar4) {
            piVar10[1] = iVar4;
          }
        }
        else {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x2af,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x2af,
                                              s_stack_>next_803ad688,param_12,param_13,param_14,
                                              param_15,param_16);
          }
          iVar4 = piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          iVar9 = piVar10[1];
          iVar4 = gnt4_HSD_Randi_bl((iVar4 - iVar9) + 1);
          piVar10[1] = iVar9 + iVar4;
        }
      }
      else if (unaff_r30 == 0x2c) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x281,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x281,
                                            s_stack_>next_803ad688,param_12,param_13,param_14,
                                            param_15,param_16);
        }
        uVar3 = piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        piVar10[1] = (piVar10[1] >> 0x1f) +
                     ((uint)(uVar3 <= (uint)piVar10[1]) - ((int)uVar3 >> 0x1f));
      }
      else if (unaff_r30 < 0x2c) {
        if (unaff_r30 == 0x2a) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x277,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x277,
                                              s_stack_>next_803ad688,param_12,param_13,param_14,
                                              param_15,param_16);
          }
          uVar3 = piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          uVar3 = piVar10[1] ^ uVar3;
          piVar10[1] = ((int)uVar3 >> 1) - (uVar3 & piVar10[1]) >> 0x1f;
        }
        else if (unaff_r30 < 0x2a) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x272,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x272,
                                              s_stack_>next_803ad688,param_12,param_13,param_14,
                                              param_15,param_16);
          }
          uVar8 = piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          uVar3 = uVar8 ^ piVar10[1];
          piVar10[1] = ((int)uVar3 >> 1) - (uVar3 & uVar8) >> 0x1f;
        }
        else {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x27c,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x27c,
                                              s_stack_>next_803ad688,param_12,param_13,param_14,
                                              param_15,param_16);
          }
          uVar3 = piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          piVar10[1] = ((int)uVar3 >> 0x1f) +
                       ((uint)((uint)piVar10[1] <= uVar3) - (piVar10[1] >> 0x1f));
        }
      }
      else if (unaff_r30 == 0x2e) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x28b,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x28b,
                                            s_stack_>next_803ad688,param_12,param_13,param_14,
                                            param_15,param_16);
        }
        iVar4 = piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        piVar10[1] = (uint)(iVar4 - piVar10[1] | piVar10[1] - iVar4) >> 0x1f;
      }
      else if (unaff_r30 < 0x2e) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x286,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x286,
                                            s_stack_>next_803ad688,param_12,param_13,param_14,
                                            param_15,param_16);
        }
        iVar4 = piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        uVar3 = countLeadingZeros(iVar4 - piVar10[1]);
        piVar10[1] = uVar3 >> 5;
      }
      else {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x290,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x290,
                                            s_stack_>next_803ad688,param_12,param_13,param_14,
                                            param_15,param_16);
        }
        iVar9 = piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        iVar4 = 0;
        if ((piVar10[1] != 0) && (iVar9 != 0)) {
          iVar4 = 1;
        }
        piVar10[1] = iVar4;
      }
      goto LAB_8025b3f8;
    }
    if (unaff_r30 == 0x38) {
      if (piVar10 == (int *)0x0) {
        pcVar6 = s_stack_8043604c;
        dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,s_bytecode_c_803ad610,0x26d,s_stack_8043604c,
                                          param_12,param_13,param_14,param_15,param_16);
      }
      if (*piVar10 == 0) {
        pcVar6 = s_stack_>next_803ad688;
        gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         s_bytecode_c_803ad610,0x26d,s_stack_>next_803ad688,param_12,param_13,
                         param_14,param_15,param_16);
      }
      fVar2 = (float)piVar10[1];
      piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
      dVar13 = (double)(float)piVar10[1];
      piVar10[1] = dVar13 == (double)fVar2 ^ 1;
      goto LAB_8025b3f8;
    }
    if (unaff_r30 < 0x38) {
      if (unaff_r30 == 0x34) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x259,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_bytecode_c_803ad610,0x259,s_stack_>next_803ad688,param_12,param_13,
                           param_14,param_15,param_16);
        }
        fVar2 = (float)piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        dVar13 = (double)(float)piVar10[1];
        piVar10[1] = (uint)((double)fVar2 < dVar13);
      }
      else if (unaff_r30 < 0x34) {
        if (unaff_r30 == 0x32) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x29a,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x29a,
                                              s_stack_>next_803ad688,param_12,param_13,param_14,
                                              param_15,param_16);
          }
          iVar9 = piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          iVar4 = 0;
          if (((piVar10[1] == 0) && (iVar9 != 0)) || ((piVar10[1] != 0 && (iVar9 == 0)))) {
            iVar4 = 1;
          }
          piVar10[1] = iVar4;
        }
        else if (unaff_r30 < 0x32) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x1e0,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          uVar3 = countLeadingZeros(piVar10[1]);
          piVar10[1] = uVar3 >> 5;
        }
        else {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x254,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_bytecode_c_803ad610,0x254,s_stack_>next_803ad688,param_12,param_13,
                             param_14,param_15,param_16);
          }
          fVar2 = (float)piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          dVar13 = (double)(float)piVar10[1];
          piVar10[1] = (uint)(dVar13 < (double)fVar2);
        }
      }
      else if (unaff_r30 == 0x36) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x263,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_bytecode_c_803ad610,0x263,s_stack_>next_803ad688,param_12,param_13,
                           param_14,param_15,param_16);
        }
        fVar2 = (float)piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        dVar13 = (double)(float)piVar10[1];
        piVar10[1] = (uint)((double)fVar2 <= dVar13);
      }
      else if (unaff_r30 < 0x36) {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x25e,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_bytecode_c_803ad610,0x25e,s_stack_>next_803ad688,param_12,param_13,
                           param_14,param_15,param_16);
        }
        fVar2 = (float)piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        dVar13 = (double)(float)piVar10[1];
        piVar10[1] = (uint)(dVar13 <= (double)fVar2);
      }
      else {
        if (piVar10 == (int *)0x0) {
          pcVar6 = s_stack_8043604c;
          dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_bytecode_c_803ad610,0x268,s_stack_8043604c,
                                            param_12,param_13,param_14,param_15,param_16);
        }
        if (*piVar10 == 0) {
          pcVar6 = s_stack_>next_803ad688;
          gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_bytecode_c_803ad610,0x268,s_stack_>next_803ad688,param_12,param_13,
                           param_14,param_15,param_16);
        }
        fVar2 = (float)piVar10[1];
        piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
        dVar13 = (double)(float)piVar10[1];
        piVar10[1] = (uint)(dVar13 == (double)fVar2);
      }
      goto LAB_8025b3f8;
    }
    if (unaff_r30 != 0x3c) {
      if (unaff_r30 < 0x3c) {
        if (unaff_r30 == 0x3a) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x2a4,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x2a4,
                                              s_stack_>next_803ad688,param_12,param_13,param_14,
                                              param_15,param_16);
          }
          uVar3 = piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          piVar10[1] = piVar10[1] | uVar3;
        }
        else if (unaff_r30 < 0x3a) {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x29f,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x29f,
                                              s_stack_>next_803ad688,param_12,param_13,param_14,
                                              param_15,param_16);
          }
          uVar3 = piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          piVar10[1] = piVar10[1] & uVar3;
        }
        else {
          if (piVar10 == (int *)0x0) {
            pcVar6 = s_stack_8043604c;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x2a9,s_stack_8043604c,
                                              param_12,param_13,param_14,param_15,param_16);
          }
          if (*piVar10 == 0) {
            pcVar6 = s_stack_>next_803ad688;
            dVar13 = (double)gnt4___assert_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,s_bytecode_c_803ad610,0x2a9,
                                              s_stack_>next_803ad688,param_12,param_13,param_14,
                                              param_15,param_16);
          }
          uVar3 = piVar10[1];
          piVar10 = (int *)gnt4_HSD_SListRemove_bl(piVar10);
          piVar10[1] = piVar10[1] ^ uVar3;
        }
        goto LAB_8025b3f8;
      }
      if (unaff_r30 != 0xff) {
        dVar13 = (double)gnt4_OSReport_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,s_unexpected_opcode_0x_x__803ad694,unaff_r30,
                                          pcVar6,param_12,param_13,param_14,param_15,param_16);
        pcVar6 = &DAT_80436048;
        dVar13 = (double)gnt4_HSD_Panic_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                           param_8,s_bytecode_c_803ad610,0x2b5,&DAT_80436048,
                                           param_12,param_13,param_14,param_15,param_16);
        goto LAB_8025b3f8;
      }
    }
  }
  iVar11 = 1;
  unaff_r29 = (char *)0x0;
  goto LAB_8025b3f8;
}



// ==== 8025c984  gnt4-hsdInitClassInfo-bl ====

void gnt4_hsdInitClassInfo_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  *(undefined4 *)(param_9 + 4) = 1;
  *(undefined4 *)(param_9 + 8) = param_11;
  *(undefined4 *)(param_9 + 0xc) = param_12;
  *(short *)(param_9 + 0x10) = (short)param_14;
  *(short *)(param_9 + 0x12) = (short)param_13;
  *(undefined4 **)(param_9 + 0x14) = param_10;
  *(undefined4 *)(param_9 + 0x1c) = 0;
  *(undefined4 *)(param_9 + 0x18) = 0;
  *(undefined4 *)(param_9 + 0x20) = 0;
  *(undefined4 *)(param_9 + 0x24) = 0;
  if (param_10 != (undefined4 *)0x0) {
    if ((param_10[1] & 1) == 0) {
      param_1 = (*(code *)*param_10)();
    }
    if (*(short *)(param_9 + 0x10) < *(short *)(param_10 + 4)) {
      param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 s_class_c_80436058,0x5f,s_class_info_>head_obj_size_>__par_803ad6ec
                                 ,param_12,param_13,param_14,param_15,param_16);
    }
    if (*(short *)(param_9 + 0x12) < *(short *)((int)param_10 + 0x12)) {
      gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_class_c_80436058,0x60,s_class_info_>head_info_size_>__pa_803ad724,param_12,
                       param_13,param_14,param_15,param_16);
    }
    gnt4_memcpy((void *)(param_9 + 0x28),param_10 + 10,(int)*(short *)((int)param_10 + 0x12) - 0x28)
    ;
    *(undefined4 *)(param_9 + 0x18) = param_10[7];
    param_10[7] = param_9;
  }
  return;
}



// ==== 8025ca6c  gnt4-GetMemoryEntry-bl ====

undefined4
gnt4_GetMemoryEntry_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *__dest;
  int *__s;
  int *piVar4;
  size_t __n;
  int iVar5;
  uint uVar6;
  undefined8 extraout_f1;
  undefined8 uVar7;
  
  if (param_9 < 0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_class_c_80436058,0xae,s_idx_>__0_803ad7b8,param_12,param_13,param_14,param_15
                     ,param_16);
  }
  if ((int)DAT_80436a0c <= param_9) {
    uVar6 = DAT_80436a0c;
    if (DAT_80436a0c == 0) {
      for (uVar6 = 0x20; (int)uVar6 <= param_9; uVar6 = uVar6 << 1) {
      }
      DAT_80436a08 = (undefined4 *)gnt4__HSD_MemAlloc_bl();
      if (DAT_80436a08 == (undefined4 *)0x0) {
        return 0;
      }
      gnt4_memset(DAT_80436a08,0,uVar6 << 2);
      DAT_80436a0c = uVar6;
    }
    else {
      do {
        uVar6 = uVar6 * 2;
      } while ((int)uVar6 <= param_9);
      __dest = (undefined4 *)gnt4__HSD_MemAlloc_bl();
      if (__dest == (undefined4 *)0x0) {
        return 0;
      }
      uVar7 = extraout_f1;
      gnt4_memcpy(__dest,DAT_80436a08,DAT_80436a0c << 2);
      __n = (uVar6 - DAT_80436a0c) * 4;
      gnt4_memset(__dest + DAT_80436a0c,0,__n);
      puVar2 = DAT_80436a08;
      iVar3 = (DAT_80436a0c & 0x3ffffff8) * 4;
      DAT_80436a08 = __dest;
      DAT_80436a0c = uVar6;
      gnt4_hsdFreeMemPiece_bl
                (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar2,iVar3,__n,
                 param_12,param_13,param_14,param_15,param_16);
      iVar3 = *(int *)((int)DAT_80436a08 + ((iVar3 + 0x1fU >> 3 & 0x1ffffffc) - 4));
      *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
    }
  }
  if (DAT_80436a08[param_9] == 0) {
    __s = (int *)gnt4__HSD_MemAlloc_bl();
    if (__s == (int *)0x0) {
      return 0;
    }
    gnt4_memset(__s,0,0x14);
    iVar5 = param_9 + -1;
    bVar1 = false;
    *__s = (param_9 + 1) * 0x20;
    DAT_80436a08[param_9] = __s;
    piVar4 = DAT_80436a08 + iVar5;
    iVar3 = param_9;
    if (-1 < iVar5) {
      do {
        if (*piVar4 != 0) {
          bVar1 = true;
          __s[4] = *(int *)(DAT_80436a08[iVar5] + 0x10);
          *(int **)(DAT_80436a08[iVar5] + 0x10) = __s;
          break;
        }
        piVar4 = piVar4 + -1;
        iVar5 = iVar5 + -1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    if (!bVar1) {
      iVar5 = param_9 + 1;
      iVar3 = DAT_80436a0c - iVar5;
      piVar4 = DAT_80436a08 + iVar5;
      if (iVar5 < (int)DAT_80436a0c) {
        do {
          if (*piVar4 != 0) {
            __s[4] = DAT_80436a08[iVar5];
            break;
          }
          piVar4 = piVar4 + 1;
          iVar5 = iVar5 + 1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
  }
  return DAT_80436a08[param_9];
}



// ==== 8025ccd0  gnt4-hsdAllocMemPiece-bl ====

int * gnt4_hsdAllocMemPiece_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int unaff_r30;
  
  uVar1 = param_9 + 0x1f;
  iVar6 = ((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0) + -1;
  piVar2 = (int *)gnt4_GetMemoryEntry_bl
                            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                             param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  if (piVar2 == (int *)0x0) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = (int *)piVar2[3];
    if (piVar3 == (int *)0x0) {
      for (piVar3 = (int *)piVar2[4]; piVar3 != (int *)0x0; piVar3 = (int *)piVar3[4]) {
        if (piVar3[3] != 0) {
          uVar1 = (*piVar3 - *piVar2) + 0x1f;
          iVar6 = gnt4_GetMemoryEntry_bl
                            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             ((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0) + -1,
                             param_10,param_11,param_12,param_13,param_14,param_15,param_16);
          if (iVar6 == 0) {
            return (int *)0x0;
          }
          piVar5 = (int *)piVar3[3];
          piVar3[3] = *piVar5;
          piVar3[2] = piVar3[2] + -1;
          piVar3[1] = piVar3[1] + -1;
          iVar4 = *piVar2;
          *(undefined4 *)((int)piVar5 + iVar4) = *(undefined4 *)(iVar6 + 0xc);
          *(undefined4 **)(iVar6 + 0xc) = (undefined4 *)((int)piVar5 + iVar4);
          *(int *)(iVar6 + 4) = *(int *)(iVar6 + 4) + 1;
          *(int *)(iVar6 + 8) = *(int *)(iVar6 + 8) + 1;
          piVar2[1] = piVar2[1] + 1;
          return piVar5;
        }
      }
      iVar6 = (DAT_80436a0c - iVar6) + -2;
      if ((iVar6 < 0) ||
         (unaff_r30 = gnt4_GetMemoryEntry_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 iVar6,param_10,param_11,param_12,param_13,param_14,param_15,
                                 param_16), unaff_r30 != 0)) {
        piVar3 = (int *)gnt4__HSD_MemAlloc_bl();
        if (piVar3 == (int *)0x0) {
          piVar3 = (int *)0x0;
        }
        else {
          if (-1 < iVar6) {
            iVar6 = *piVar2;
            *(undefined4 *)((int)piVar3 + iVar6) = *(undefined4 *)(unaff_r30 + 0xc);
            *(undefined4 **)(unaff_r30 + 0xc) = (undefined4 *)((int)piVar3 + iVar6);
            *(int *)(unaff_r30 + 4) = *(int *)(unaff_r30 + 4) + 1;
            *(int *)(unaff_r30 + 8) = *(int *)(unaff_r30 + 8) + 1;
          }
          piVar2[1] = piVar2[1] + 1;
        }
      }
      else {
        piVar3 = (int *)0x0;
      }
    }
    else {
      piVar2[3] = *piVar3;
      piVar2[2] = piVar2[2] + -1;
    }
  }
  return piVar3;
}



// ==== 8025ce98  gnt4-hsdFreeMemPiece-bl ====

void gnt4_hsdFreeMemPiece_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,int param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  if (param_9 != (undefined4 *)0x0) {
    uVar1 = param_10 + 0x1f;
    iVar2 = gnt4_GetMemoryEntry_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       ((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0) + -1,
                       param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    *param_9 = *(undefined4 *)(iVar2 + 0xc);
    *(undefined4 **)(iVar2 + 0xc) = param_9;
    *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + 1;
  }
  return;
}



// ==== 8025cef0  gnt4-_hsdClassAlloc-bl ====

void gnt4__hsdClassAlloc_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  
  piVar1 = gnt4_hsdAllocMemPiece_bl
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)*(short *)(param_9 + 0x10),param_10,param_11,param_12,param_13,param_14,
                      param_15,param_16);
  if (piVar1 != (int *)0x0) {
    *(int *)(param_9 + 0x20) = *(int *)(param_9 + 0x20) + 1;
    if (*(uint *)(param_9 + 0x24) < *(uint *)(param_9 + 0x20)) {
      *(uint *)(param_9 + 0x24) = *(uint *)(param_9 + 0x20);
    }
  }
  return;
}



// ==== 8025cf48  gnt4-_hsdClassInit-bl ====

undefined4 gnt4__hsdClassInit_bl(void)

{
  return 0;
}



// ==== 8025cf50  gnt4-_hsdClassRelease-bl ====

void gnt4__hsdClassRelease_bl(void)

{
  return;
}



// ==== 8025cf54  gnt4-_hsdClassDestroy-bl ====

void gnt4__hsdClassDestroy_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *param_9;
  *(int *)(iVar2 + 0x20) = *(int *)(iVar2 + 0x20) + -1;
  if (param_9 != (int *)0x0) {
    uVar1 = (int)*(short *)(iVar2 + 0x10) + 0x1f;
    iVar2 = gnt4_GetMemoryEntry_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       ((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0) + -1,iVar2,
                       param_11,param_12,param_13,param_14,param_15,param_16);
    *param_9 = *(int *)(iVar2 + 0xc);
    *(int **)(iVar2 + 0xc) = param_9;
    *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + 1;
  }
  return;
}



// ==== 8025cfc0  gnt4-_hsdClassAmnesia-bl ====

void gnt4__hsdClassAmnesia_bl(undefined **param_1)

{
  param_1[8] = (undefined *)0x0;
  param_1[9] = (undefined *)0x0;
  if (param_1 != &PTR_gnt4__hsdClassInfoInit_bl_803ad6b0) {
    return;
  }
  DAT_80436a0c = 0;
  DAT_80436a08 = 0;
  DAT_80436a10 = 0;
  return;
}



// ==== 8025cfec  gnt4-_hsdClassInfoInit-bl ====

void gnt4__hsdClassInfoInit_bl(void)

{
  DAT_803ad6b4 = 1;
  DAT_803ad6b8 = s_sysdolphin_base_library_803ad7c4;
  DAT_803ad6bc = s_hsd_class_803ad7dc;
  DAT_803ad6c0 = 4;
  DAT_803ad6c2 = 0x3c;
  DAT_803ad6c4 = 0;
  DAT_803ad6cc = 0;
  DAT_803ad6c8 = 0;
  DAT_803ad6d0 = 0;
  DAT_803ad6d4 = 0;
  DAT_803ad6d8 = gnt4__hsdClassAlloc_bl;
  DAT_803ad6dc = gnt4__hsdClassInit_bl;
  DAT_803ad6e0 = gnt4__hsdClassRelease_bl;
  DAT_803ad6e4 = gnt4__hsdClassDestroy_bl;
  DAT_803ad6e8 = gnt4__hsdClassAmnesia_bl;
  return;
}



// ==== 8025d088  gnt4-hsdNew-bl ====

int * gnt4_hsdNew_bl(undefined4 *param_1)

{
  int *__s;
  int iVar1;
  
  if ((param_1[1] & 1) == 0) {
    (*(code *)*param_1)();
  }
  __s = (int *)(*(code *)param_1[10])(param_1);
  if (__s == (int *)0x0) {
    __s = (int *)0x0;
  }
  else {
    if ((param_1[1] & 1) == 0) {
      (*(code *)*param_1)();
    }
    gnt4_memset(__s,0,(int)*(short *)(param_1 + 4));
    *__s = (int)param_1;
    iVar1 = (*(code *)param_1[0xb])(__s);
    if (iVar1 < 0) {
      (*(code *)param_1[0xd])(__s);
      __s = (int *)0x0;
    }
  }
  return __s;
}



// ==== 8025d150  zz_025d150_ ====

undefined4 zz_025d150_(undefined4 *param_1,undefined4 *param_2)

{
  if ((param_1 != (undefined4 *)0x0) && (param_2 != (undefined4 *)0x0)) {
    if ((param_1[1] & 1) == 0) {
      (*(code *)*param_1)();
    }
    if ((param_2[1] & 1) == 0) {
      (*(code *)*param_2)();
    }
    while( true ) {
      if (param_1 == (undefined4 *)0x0) {
        return 0;
      }
      if (param_1 == param_2) break;
      param_1 = (undefined4 *)param_1[5];
    }
    return 1;
  }
  return 0;
}



// ==== 8025d1f0  zz_025d1f0_ ====

void zz_025d1f0_(int param_1,uint param_2,uint param_3)

{
  *(uint *)(param_1 + 4) = param_2 | *(uint *)(param_1 + 4) & ~param_3;
  return;
}



// ==== 8025d204  zz_025d204_ ====

void zz_025d204_(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  iVar1 = gnt4__savegpr_19_bl();
  iVar11 = *(int *)(iVar1 + 0x1c);
  while (iVar11 != 0) {
    iVar10 = *(int *)(iVar11 + 0x18);
    *(undefined4 *)(iVar11 + 0x18) = 0;
    iVar12 = *(int *)(iVar11 + 0x1c);
    while (iVar12 != 0) {
      iVar13 = *(int *)(iVar12 + 0x18);
      *(undefined4 *)(iVar12 + 0x18) = 0;
      iVar8 = *(int *)(iVar12 + 0x1c);
      while (iVar8 != 0) {
        iVar9 = *(int *)(iVar8 + 0x18);
        *(undefined4 *)(iVar8 + 0x18) = 0;
        iVar6 = *(int *)(iVar8 + 0x1c);
        while (iVar6 != 0) {
          iVar7 = *(int *)(iVar6 + 0x18);
          *(undefined4 *)(iVar6 + 0x18) = 0;
          iVar4 = *(int *)(iVar6 + 0x1c);
          while (iVar4 != 0) {
            iVar5 = *(int *)(iVar4 + 0x18);
            *(undefined4 *)(iVar4 + 0x18) = 0;
            iVar2 = *(int *)(iVar4 + 0x1c);
            while (iVar2 != 0) {
              iVar3 = *(int *)(iVar2 + 0x18);
              *(undefined4 *)(iVar2 + 0x18) = 0;
              zz_025d204_();
              iVar2 = iVar3;
            }
            (**(code **)(iVar4 + 0x38))(iVar4);
            *(undefined4 *)(iVar4 + 0x1c) = 0;
            *(undefined4 *)(iVar4 + 0x14) = 0;
            zz_025d1f0_(iVar4,0,1);
            iVar4 = iVar5;
          }
          (**(code **)(iVar6 + 0x38))(iVar6);
          *(undefined4 *)(iVar6 + 0x1c) = 0;
          *(undefined4 *)(iVar6 + 0x14) = 0;
          *(uint *)(iVar6 + 4) = *(uint *)(iVar6 + 4) & 0xfffffffe;
          iVar6 = iVar7;
        }
        (**(code **)(iVar8 + 0x38))(iVar8);
        *(undefined4 *)(iVar8 + 0x1c) = 0;
        *(undefined4 *)(iVar8 + 0x14) = 0;
        *(uint *)(iVar8 + 4) = *(uint *)(iVar8 + 4) & 0xfffffffe;
        iVar8 = iVar9;
      }
      (**(code **)(iVar12 + 0x38))(iVar12);
      *(undefined4 *)(iVar12 + 0x1c) = 0;
      *(undefined4 *)(iVar12 + 0x14) = 0;
      *(uint *)(iVar12 + 4) = *(uint *)(iVar12 + 4) & 0xfffffffe;
      iVar12 = iVar13;
    }
    (**(code **)(iVar11 + 0x38))(iVar11);
    *(undefined4 *)(iVar11 + 0x1c) = 0;
    *(undefined4 *)(iVar11 + 0x14) = 0;
    *(uint *)(iVar11 + 4) = *(uint *)(iVar11 + 4) & 0xfffffffe;
    iVar11 = iVar10;
  }
  (**(code **)(iVar1 + 0x38))(iVar1);
  *(undefined4 *)(iVar1 + 0x1c) = 0;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xfffffffe;
  gnt4__restgpr_19_bl();
  return;
}



// ==== 8025d3e8  zz_025d3e8_ ====

void zz_025d3e8_(char *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_2 + 0x1c);
  while (*piVar2 != 0) {
    iVar1 = gnt4_strcmp(param_1,*(char **)(*piVar2 + 8));
    if (iVar1 == 0) {
      zz_025d204_();
      *piVar2 = *(int *)(*piVar2 + 0x18);
    }
    else {
      piVar2 = (int *)(*piVar2 + 0x18);
    }
  }
  return;
}



// ==== 8025d460  zz_025d460_ ====

void zz_025d460_(char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    param_1 = s_sysdolphin_base_library_803ad7c4;
  }
  if ((DAT_803ad6b4 & 1) != 0) {
    iVar1 = gnt4_strcmp(param_1,DAT_803ad6b8);
    if (iVar1 == 0) {
      DAT_80436a10 = 0;
      zz_025d204_();
    }
    else {
      zz_025d3e8_(param_1,-0x7fc52950);
    }
  }
  return;
}



// ==== 8025d4e8  gnt4-hsdSearchClassInfo-bl ====

undefined4
gnt4_hsdSearchClassInfo_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if (DAT_80436a10 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = gnt4_HSD_HashSearch_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436a10,
                       param_9,(uint *)0x0,param_12,param_13,param_14,param_15,param_16);
  }
  return uVar1;
}



// ==== 8025d528  gnt4-HSD_HashSearch-bl ====

undefined4
gnt4_HSD_HashSearch_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
          uint *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined8 extraout_f1;
  
  iVar3 = *param_9;
  uVar1 = (**(code **)(iVar3 + 0x3c))();
  if ((uint)param_9[2] <= uVar1) {
    gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     &DAT_80436060,0x71,s_idx_<_hash_>table_size_803ad840,iVar3,param_13,param_14,
                     param_15,param_16);
  }
  puVar4 = *(undefined4 **)(param_9[1] + uVar1 * 4);
  if (puVar4 == (undefined4 *)0x0) {
    puVar4 = (undefined4 *)0x0;
  }
  else {
    for (; puVar4 != (undefined4 *)0x0; puVar4 = (undefined4 *)*puVar4) {
      iVar3 = (**(code **)(*param_9 + 0x40))(param_9,puVar4[1],param_10);
      if (iVar3 == 0) goto LAB_8025d5dc;
    }
    puVar4 = (undefined4 *)0x0;
  }
LAB_8025d5dc:
  if (param_11 != (uint *)0x0) {
    *param_11 = (-(int)puVar4 | (uint)puVar4) >> 0x1f;
  }
  if (puVar4 == (undefined4 *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = puVar4[2];
  }
  return uVar2;
}



// ==== 8025d628  gnt4-HSD_TExpGetType-bl ====

undefined4 gnt4_HSD_TExpGetType_bl(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    return 0;
  }
  if (param_1 == (undefined4 *)0xffffffff) {
    return 2;
  }
  if (param_1 == (undefined4 *)0xfffffffe) {
    return 3;
  }
  return *param_1;
}



// ==== 8025d664  gnt4-HSD_TExpRef-bl ====

void gnt4_HSD_TExpRef_bl(int *param_1,char param_2)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    iVar1 = 0;
  }
  else if (param_1 == (int *)0xffffffff) {
    iVar1 = 2;
  }
  else if (param_1 == (int *)0xfffffffe) {
    iVar1 = 3;
  }
  else {
    iVar1 = *param_1;
  }
  if (iVar1 == 4) {
    *(char *)(param_1 + 4) = *(char *)(param_1 + 4) + '\x01';
    return;
  }
  if (3 < iVar1) {
    return;
  }
  if (iVar1 != 1) {
    return;
  }
  if (param_2 == '\x01') {
    param_1[2] = param_1[2] + 1;
    return;
  }
  param_1[5] = param_1[5] + 1;
  return;
}



// ==== 8025d6ec  gnt4-HSD_TExpUnref-bl ====

void gnt4_HSD_TExpUnref_bl(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  int *piVar7;
  undefined8 uVar8;
  
  uVar8 = gnt4__savegpr_26_bl();
  piVar6 = (int *)((ulonglong)uVar8 >> 0x20);
  if (piVar6 == (int *)0x0) {
    iVar2 = 0;
  }
  else if (piVar6 == (int *)0xffffffff) {
    iVar2 = 2;
  }
  else if (piVar6 == (int *)0xfffffffe) {
    iVar2 = 3;
  }
  else {
    iVar2 = *piVar6;
  }
  if (iVar2 == 4) {
    if (*(char *)(piVar6 + 4) != '\0') {
      *(char *)(piVar6 + 4) = *(char *)(piVar6 + 4) + -1;
    }
  }
  else if ((iVar2 < 4) && (iVar2 == 1)) {
    if (((uint)uVar8 & 0xff) == 1) {
      if (piVar6[2] != 0) {
        piVar6[2] = piVar6[2] + -1;
      }
    }
    else if (piVar6[5] != 0) {
      piVar6[5] = piVar6[5] + -1;
    }
    if ((piVar6[2] == 0) && (piVar6[5] == 0)) {
      iVar2 = 0;
      do {
        piVar7 = (int *)piVar6[10];
        if (piVar7 == (int *)0x0) {
          iVar3 = 0;
        }
        else if (piVar7 == (int *)0xffffffff) {
          iVar3 = 2;
        }
        else if (piVar7 == (int *)0xfffffffe) {
          iVar3 = 3;
        }
        else {
          iVar3 = *piVar7;
        }
        if (iVar3 == 4) {
          if (*(char *)(piVar7 + 4) != '\0') {
            *(char *)(piVar7 + 4) = *(char *)(piVar7 + 4) + -1;
          }
        }
        else if ((iVar3 < 4) && (iVar3 == 1)) {
          if (*(char *)((int)piVar6 + 0x25) == '\x01') {
            if (piVar7[2] != 0) {
              piVar7[2] = piVar7[2] + -1;
            }
          }
          else if (piVar7[5] != 0) {
            piVar7[5] = piVar7[5] + -1;
          }
          if ((piVar7[2] == 0) && (piVar7[5] == 0)) {
            iVar3 = 0;
            do {
              puVar5 = (undefined4 *)piVar7[10];
              cVar1 = *(char *)((int)piVar7 + 0x25);
              iVar4 = gnt4_HSD_TExpGetType_bl(puVar5);
              if (iVar4 == 4) {
                if (*(char *)(puVar5 + 4) != '\0') {
                  *(char *)(puVar5 + 4) = *(char *)(puVar5 + 4) + -1;
                }
              }
              else if ((iVar4 < 4) && (iVar4 == 1)) {
                if (cVar1 == '\x01') {
                  if (puVar5[2] != 0) {
                    puVar5[2] = puVar5[2] + -1;
                  }
                }
                else if (puVar5[5] != 0) {
                  puVar5[5] = puVar5[5] + -1;
                }
                if ((puVar5[2] == 0) && (puVar5[5] == 0)) {
                  iVar4 = 0;
                  do {
                    gnt4_HSD_TExpUnref_bl();
                    gnt4_HSD_TExpUnref_bl();
                    iVar4 = iVar4 + 1;
                  } while (iVar4 < 4);
                }
              }
              puVar5 = (undefined4 *)piVar7[0x12];
              cVar1 = *(char *)((int)piVar7 + 0x45);
              iVar4 = gnt4_HSD_TExpGetType_bl(puVar5);
              if (iVar4 == 4) {
                if (*(char *)(puVar5 + 4) != '\0') {
                  *(char *)(puVar5 + 4) = *(char *)(puVar5 + 4) + -1;
                }
              }
              else if ((iVar4 < 4) && (iVar4 == 1)) {
                if (cVar1 == '\x01') {
                  if (puVar5[2] != 0) {
                    puVar5[2] = puVar5[2] + -1;
                  }
                }
                else if (puVar5[5] != 0) {
                  puVar5[5] = puVar5[5] + -1;
                }
                if ((puVar5[2] == 0) && (puVar5[5] == 0)) {
                  iVar4 = 0;
                  do {
                    gnt4_HSD_TExpUnref_bl();
                    gnt4_HSD_TExpUnref_bl();
                    iVar4 = iVar4 + 1;
                  } while (iVar4 < 4);
                }
              }
              iVar3 = iVar3 + 1;
              piVar7 = piVar7 + 2;
            } while (iVar3 < 4);
          }
        }
        piVar7 = (int *)piVar6[0x12];
        if (piVar7 == (int *)0x0) {
          iVar3 = 0;
        }
        else if (piVar7 == (int *)0xffffffff) {
          iVar3 = 2;
        }
        else if (piVar7 == (int *)0xfffffffe) {
          iVar3 = 3;
        }
        else {
          iVar3 = *piVar7;
        }
        if (iVar3 == 4) {
          if (*(char *)(piVar7 + 4) != '\0') {
            *(char *)(piVar7 + 4) = *(char *)(piVar7 + 4) + -1;
          }
        }
        else if ((iVar3 < 4) && (iVar3 == 1)) {
          if (*(char *)((int)piVar6 + 0x45) == '\x01') {
            if (piVar7[2] != 0) {
              piVar7[2] = piVar7[2] + -1;
            }
          }
          else if (piVar7[5] != 0) {
            piVar7[5] = piVar7[5] + -1;
          }
          if ((piVar7[2] == 0) && (piVar7[5] == 0)) {
            iVar3 = 0;
            do {
              puVar5 = (undefined4 *)piVar7[10];
              cVar1 = *(char *)((int)piVar7 + 0x25);
              iVar4 = gnt4_HSD_TExpGetType_bl(puVar5);
              if (iVar4 == 4) {
                if (*(char *)(puVar5 + 4) != '\0') {
                  *(char *)(puVar5 + 4) = *(char *)(puVar5 + 4) + -1;
                }
              }
              else if ((iVar4 < 4) && (iVar4 == 1)) {
                if (cVar1 == '\x01') {
                  if (puVar5[2] != 0) {
                    puVar5[2] = puVar5[2] + -1;
                  }
                }
                else if (puVar5[5] != 0) {
                  puVar5[5] = puVar5[5] + -1;
                }
                if ((puVar5[2] == 0) && (puVar5[5] == 0)) {
                  iVar4 = 0;
                  do {
                    gnt4_HSD_TExpUnref_bl();
                    gnt4_HSD_TExpUnref_bl();
                    iVar4 = iVar4 + 1;
                  } while (iVar4 < 4);
                }
              }
              puVar5 = (undefined4 *)piVar7[0x12];
              cVar1 = *(char *)((int)piVar7 + 0x45);
              iVar4 = gnt4_HSD_TExpGetType_bl(puVar5);
              if (iVar4 == 4) {
                if (*(char *)(puVar5 + 4) != '\0') {
                  *(char *)(puVar5 + 4) = *(char *)(puVar5 + 4) + -1;
                }
              }
              else if ((iVar4 < 4) && (iVar4 == 1)) {
                if (cVar1 == '\x01') {
                  if (puVar5[2] != 0) {
                    puVar5[2] = puVar5[2] + -1;
                  }
                }
                else if (puVar5[5] != 0) {
                  puVar5[5] = puVar5[5] + -1;
                }
                if ((puVar5[2] == 0) && (puVar5[5] == 0)) {
                  iVar4 = 0;
                  do {
                    gnt4_HSD_TExpUnref_bl();
                    gnt4_HSD_TExpUnref_bl();
                    iVar4 = iVar4 + 1;
                  } while (iVar4 < 4);
                }
              }
              iVar3 = iVar3 + 1;
              piVar7 = piVar7 + 2;
            } while (iVar3 < 4);
          }
        }
        iVar2 = iVar2 + 1;
        piVar6 = piVar6 + 2;
      } while (iVar2 < 4);
    }
  }
  gnt4__restgpr_26_bl();
  return;
}



// ==== 8025dc68  gnt4-HSD_TExpFreeList-bl ====

int * gnt4_HSD_TExpFreeList_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int *param_9,int param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  int *piVar5;
  int **ppiVar6;
  int *local_18 [3];
  
  ppiVar6 = local_18;
  local_18[0] = param_9;
  if (param_11 == (undefined *)0x0) {
    puVar4 = (undefined *)0x0;
    if ((param_10 == 7) || (param_10 == 1)) {
      for (; param_9 != (int *)0x0; param_9 = (int *)param_9[1]) {
        if ((*param_9 == 1) && (param_9[2] == 0)) {
          gnt4_HSD_TExpUnref_bl();
          param_1 = gnt4_HSD_TExpUnref_bl();
        }
      }
    }
    while (piVar1 = *ppiVar6, piVar1 != (int *)0x0) {
      if ((param_10 == 7) || (param_10 == *piVar1)) {
        iVar2 = *piVar1;
        if (iVar2 == 4) {
          if (*(char *)(piVar1 + 4) != '\0') goto LAB_8025df54;
          piVar5 = (int *)piVar1[1];
          if (piVar1 == (int *)0x0) {
            uVar3 = 0;
          }
          else if (piVar1 == (int *)0xffffffff) {
            uVar3 = 2;
          }
          else {
            uVar3 = 4;
            if (piVar1 == (int *)0xfffffffe) {
              uVar3 = 3;
            }
          }
          if (uVar3 == 4) {
            param_1 = gnt4_hsdFreeMemPiece_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 piVar1,0x14,puVar4,param_12,param_13,param_14,param_15,param_16);
          }
          else if ((uVar3 < 4) && (uVar3 == 1)) {
            param_1 = gnt4_hsdFreeMemPiece_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 piVar1,0x6c,puVar4,param_12,param_13,param_14,param_15,param_16);
          }
          *ppiVar6 = piVar5;
        }
        else {
          if ((3 < iVar2) || (iVar2 != 1)) {
            puVar4 = &DAT_80436078;
            param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80436068,0x10c,&DAT_80436078,param_12,param_13,
                                       param_14,param_15,param_16);
            goto LAB_8025df54;
          }
          if ((piVar1[2] != 0) || (piVar1[5] != 0)) goto LAB_8025df54;
          piVar5 = (int *)piVar1[1];
          if (piVar1 == (int *)0x0) {
            uVar3 = 0;
          }
          else if (piVar1 == (int *)0xffffffff) {
            uVar3 = 2;
          }
          else {
            uVar3 = 1;
            if (piVar1 == (int *)0xfffffffe) {
              uVar3 = 3;
            }
          }
          if (uVar3 == 4) {
            param_1 = gnt4_hsdFreeMemPiece_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 piVar1,0x14,puVar4,param_12,param_13,param_14,param_15,param_16);
          }
          else if ((uVar3 < 4) && (uVar3 == 1)) {
            param_1 = gnt4_hsdFreeMemPiece_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 piVar1,0x6c,puVar4,param_12,param_13,param_14,param_15,param_16);
          }
          *ppiVar6 = piVar5;
        }
      }
      else {
LAB_8025df54:
        ppiVar6 = (int **)(*ppiVar6 + 1);
      }
    }
  }
  else {
    while (piVar1 = *ppiVar6, piVar1 != (int *)0x0) {
      if ((param_10 == 7) || (param_10 == *piVar1)) {
        iVar2 = *piVar1;
        if (iVar2 == 4) {
          piVar5 = (int *)piVar1[1];
          if (piVar1 == (int *)0x0) {
            uVar3 = 0;
          }
          else if (piVar1 == (int *)0xffffffff) {
            uVar3 = 2;
          }
          else {
            uVar3 = 4;
            if (piVar1 == (int *)0xfffffffe) {
              uVar3 = 3;
            }
          }
          if (uVar3 == 4) {
            param_1 = gnt4_hsdFreeMemPiece_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 piVar1,0x14,param_11,param_12,param_13,param_14,param_15,param_16);
          }
          else if ((uVar3 < 4) && (uVar3 == 1)) {
            param_1 = gnt4_hsdFreeMemPiece_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 piVar1,0x6c,param_11,param_12,param_13,param_14,param_15,param_16);
          }
          *ppiVar6 = piVar5;
        }
        else {
          if ((3 < iVar2) || (iVar2 != 1)) {
            param_11 = &DAT_80436078;
            param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80436068,0xdc,&DAT_80436078,param_12,param_13,
                                       param_14,param_15,param_16);
            goto LAB_8025dda8;
          }
          piVar5 = (int *)piVar1[1];
          if (piVar1 == (int *)0x0) {
            uVar3 = 0;
          }
          else if (piVar1 == (int *)0xffffffff) {
            uVar3 = 2;
          }
          else {
            uVar3 = 1;
            if (piVar1 == (int *)0xfffffffe) {
              uVar3 = 3;
            }
          }
          if (uVar3 == 4) {
            param_1 = gnt4_hsdFreeMemPiece_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 piVar1,0x14,param_11,param_12,param_13,param_14,param_15,param_16);
          }
          else if ((uVar3 < 4) && (uVar3 == 1)) {
            param_1 = gnt4_hsdFreeMemPiece_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 piVar1,0x6c,param_11,param_12,param_13,param_14,param_15,param_16);
          }
          *ppiVar6 = piVar5;
        }
      }
      else {
LAB_8025dda8:
        ppiVar6 = (int **)(*ppiVar6 + 1);
      }
    }
  }
  return local_18[0];
}



// ==== 8025df88  gnt4-HSD_TExpTev-bl ====

int * gnt4_HSD_TExpTev_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                         double param_5,double param_6,double param_7,double param_8,int *param_9,
                         undefined4 param_10,char *param_11,undefined4 param_12,undefined4 param_13,
                         undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int *__s;
  undefined4 extraout_r4;
  
  if (param_9 == (int *)0x0) {
    param_11 = s_texp_list_803ad858;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436068,0x127,s_texp_list_803ad858,param_12,param_13,param_14,
                               param_15,param_16);
    param_10 = extraout_r4;
  }
  __s = gnt4_hsdAllocMemPiece_bl
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x6c,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
  if (__s == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436068,
                     0x3f,&DAT_80436070,param_12,param_13,param_14,param_15,param_16);
  }
  gnt4_memset(__s,0xff,0x6c);
  *__s = 1;
  __s[1] = *param_9;
  *param_9 = (int)__s;
  __s[2] = 0;
  __s[5] = 0;
  __s[0x19] = 0;
  __s[10] = 0;
  __s[0x12] = 0;
  __s[0xc] = 0;
  __s[0x14] = 0;
  __s[0xe] = 0;
  __s[0x16] = 0;
  __s[0x10] = 0;
  __s[0x18] = 0;
  return __s;
}



// ==== 8025e048  gnt4-HSD_TExpCnst-bl ====

void gnt4_HSD_TExpCnst_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               char *param_11,int *param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  uint extraout_r4;
  uint uVar3;
  char *pcVar4;
  int *piVar5;
  int *piVar6;
  undefined8 extraout_f1;
  undefined8 uVar7;
  undefined8 uVar8;
  
  uVar8 = gnt4__savegpr_27_bl();
  iVar1 = (int)((ulonglong)uVar8 >> 0x20);
  uVar2 = (uint)uVar8;
  uVar3 = uVar2;
  pcVar4 = param_11;
  piVar5 = param_12;
  uVar7 = extraout_f1;
  if (param_12 == (int *)0x0) {
    pcVar4 = s_texp_list_803ad858;
    uVar7 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x16a,s_texp_list_803ad858,0,param_13,param_14,param_15,
                             param_16);
    uVar3 = extraout_r4;
  }
  piVar6 = (int *)*param_12;
  do {
    if (piVar6 == (int *)0x0) {
      if (uVar2 != 7) {
        piVar6 = gnt4_hsdAllocMemPiece_bl
                           (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x14,uVar3
                            ,pcVar4,piVar5,param_13,param_14,param_15,param_16);
        if (piVar6 == (int *)0x0) {
          gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80436068,0x47,&DAT_80436070,piVar5,param_13,param_14,param_15,
                           param_16);
        }
        *piVar6 = 4;
        piVar6[1] = *param_12;
        *param_12 = (int)piVar6;
        *(undefined1 *)(piVar6 + 4) = 0;
        piVar6[2] = iVar1;
        *(char *)(piVar6 + 3) = (char)uVar8;
        *(char *)((int)piVar6 + 0xd) = (char)param_11;
        *(undefined1 *)((int)piVar6 + 0xe) = 0xff;
        *(undefined1 *)((int)piVar6 + 0xf) = 0xff;
        *(undefined1 *)((int)piVar6 + 0x11) = 0;
      }
LAB_8025e150:
      gnt4__restgpr_27_bl();
      return;
    }
    if (((*piVar6 == 4) && (piVar6[2] == iVar1)) && (*(byte *)(piVar6 + 3) == uVar2)) {
      if ((char *)(uint)*(byte *)((int)piVar6 + 0xd) != param_11) {
        gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436068
                         ,0x171,s_texp_>cnst_ctype____type_803ad864,piVar5,param_13,param_14,
                         param_15,param_16);
      }
      goto LAB_8025e150;
    }
    piVar6 = (int *)piVar6[1];
  } while( true );
}



// ==== 8025e168  gnt4-HSD_TExpColorOp-bl ====

void gnt4_HSD_TExpColorOp_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined1 param_11,undefined4 param_12,uint param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined8 extraout_f1;
  undefined8 uVar5;
  undefined8 uVar6;
  
  uVar6 = gnt4__savegpr_27_bl();
  piVar2 = (int *)((ulonglong)uVar6 >> 0x20);
  uVar3 = param_12;
  uVar4 = param_13;
  if (piVar2 == (int *)0x0) {
    uVar5 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x19a,&DAT_80436070,param_12,param_13,param_14,param_15,
                             param_16);
    iVar1 = 0;
  }
  else {
    uVar5 = extraout_f1;
    if (piVar2 == (int *)0xffffffff) {
      iVar1 = 2;
    }
    else if (piVar2 == (int *)0xfffffffe) {
      iVar1 = 3;
    }
    else {
      iVar1 = *piVar2;
    }
  }
  if (iVar1 != 1) {
    gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436068,
                     0x19b,s_HSD_TExpGetType_texp_____HSD_TE__803ad880,uVar3,uVar4,param_14,param_15
                     ,param_16);
  }
  *(char *)((int)piVar2 + 0xd) = (char)uVar6;
  *(byte *)((int)piVar2 + 0xe) = (byte)(-(param_13 & 0xff) >> 0x1f);
  if (((int)uVar6 == 0) || ((int)uVar6 == 1)) {
    *(undefined1 *)((int)piVar2 + 0xf) = param_11;
    *(char *)(piVar2 + 4) = (char)param_12;
  }
  else {
    *(undefined1 *)((int)piVar2 + 0xf) = 0;
    *(undefined1 *)(piVar2 + 4) = 0;
  }
  gnt4__restgpr_27_bl();
  return;
}



// ==== 8025e250  gnt4-HSD_TExpAlphaOp-bl ====

void gnt4_HSD_TExpAlphaOp_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined1 param_11,undefined4 param_12,uint param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined8 extraout_f1;
  undefined8 uVar5;
  undefined8 uVar6;
  
  uVar6 = gnt4__savegpr_27_bl();
  piVar2 = (int *)((ulonglong)uVar6 >> 0x20);
  uVar3 = param_12;
  uVar4 = param_13;
  if (piVar2 == (int *)0x0) {
    uVar5 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x1b4,&DAT_80436070,param_12,param_13,param_14,param_15,
                             param_16);
    iVar1 = 0;
  }
  else {
    uVar5 = extraout_f1;
    if (piVar2 == (int *)0xffffffff) {
      iVar1 = 2;
    }
    else if (piVar2 == (int *)0xfffffffe) {
      iVar1 = 3;
    }
    else {
      iVar1 = *piVar2;
    }
  }
  if (iVar1 != 1) {
    gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436068,
                     0x1b5,s_HSD_TExpGetType_texp_____HSD_TE__803ad880,uVar3,uVar4,param_14,param_15
                     ,param_16);
  }
  *(char *)((int)piVar2 + 0x19) = (char)uVar6;
  *(byte *)((int)piVar2 + 0x1a) = (byte)(-(param_13 & 0xff) >> 0x1f);
  if (((int)uVar6 == 0) || ((int)uVar6 == 1)) {
    *(undefined1 *)((int)piVar2 + 0x1b) = param_11;
    *(char *)(piVar2 + 7) = (char)param_12;
  }
  else {
    *(undefined1 *)((int)piVar2 + 0x1b) = 0;
    *(undefined1 *)(piVar2 + 7) = 0;
  }
  gnt4__restgpr_27_bl();
  return;
}



// ==== 8025e338  gnt4-HSD_TExpColorInSub-bl ====

/* WARNING: Removing unreachable block (ram,0x8025e50c) */

void gnt4_HSD_TExpColorInSub_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 *param_11,int param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  bool bVar2;
  undefined1 uVar4;
  int iVar3;
  int iVar5;
  int iVar6;
  int *piVar7;
  char cVar8;
  char unaff_r28;
  int iVar9;
  int iVar10;
  double extraout_f1;
  double dVar11;
  undefined8 uVar12;
  
  uVar12 = gnt4__savegpr_24_bl();
  iVar5 = (int)((ulonglong)uVar12 >> 0x20);
  iVar6 = (int)uVar12;
  iVar3 = param_12 * 8;
  iVar10 = iVar5 + iVar3;
  if (param_11 == (undefined4 *)0x0) {
    uVar4 = 0;
  }
  else if (param_11 == (undefined4 *)0xffffffff) {
    uVar4 = 2;
  }
  else if (param_11 == (undefined4 *)0xfffffffe) {
    uVar4 = 3;
  }
  else {
    uVar4 = (undefined1)*param_11;
  }
  *(undefined1 *)(iVar10 + 0x24) = uVar4;
  iVar9 = iVar5 + iVar3;
  *(char *)(iVar9 + 0x25) = (char)uVar12;
  *(undefined4 **)(iVar9 + 0x28) = param_11;
  *(undefined1 *)(iVar9 + 0x26) = 0xff;
  if (iVar6 == 0xc) {
    *(undefined1 *)(iVar9 + 0x26) = 0xd;
    *(undefined1 *)(iVar10 + 0x24) = 5;
    *(undefined4 *)(iVar9 + 0x28) = 0;
    goto LAB_8025e8cc;
  }
  if (iVar6 < 0xc) {
    if (iVar6 == 8) {
      *(undefined1 *)(iVar9 + 0x26) = 0xc;
      *(undefined1 *)(iVar10 + 0x24) = 5;
      *(undefined4 *)(iVar9 + 0x28) = 0;
      goto LAB_8025e8cc;
    }
    if (7 < iVar6) goto LAB_8025e448;
    if (6 < iVar6) {
      *(undefined1 *)(iVar9 + 0x26) = 0xf;
      *(undefined1 *)(iVar10 + 0x24) = 0;
      *(undefined4 *)(iVar9 + 0x28) = 0;
      goto LAB_8025e8cc;
    }
  }
  else if (iVar6 < 0x10) {
LAB_8025e448:
    *(undefined1 *)(iVar9 + 0x26) = 0xe;
    dVar11 = extraout_f1;
    switch(iVar6) {
    case 9:
      unaff_r28 = '\a';
      break;
    case 10:
      unaff_r28 = '\x06';
      break;
    case 0xb:
      unaff_r28 = '\x05';
      break;
    default:
      dVar11 = (double)gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,&DAT_80436068,500,&DAT_80436078,iVar3,param_13,
                                        param_14,param_15,param_16);
      break;
    case 0xd:
      unaff_r28 = '\x03';
      break;
    case 0xe:
      unaff_r28 = '\x02';
      break;
    case 0xf:
      unaff_r28 = '\x01';
    }
    if (*(char *)(iVar5 + 0x20) == -1) {
      *(char *)(iVar5 + 0x20) = unaff_r28;
    }
    else if (*(char *)(iVar5 + 0x20) == unaff_r28) {
      gnt4_HSD_Panic_bl(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436068
                        ,0x1f9,s_tev_can_t_select_multiple_konst_i_803ad8a4,iVar3,param_13,param_14,
                        param_15,param_16);
    }
    *(undefined1 *)(iVar10 + 0x24) = 6;
    goto LAB_8025e8cc;
  }
  bVar1 = *(byte *)(iVar10 + 0x24);
  if (bVar1 != 2) {
    if (bVar1 < 2) {
      if (bVar1 == 0) {
        *(undefined1 *)(iVar10 + 0x24) = 0;
        *(undefined1 *)(iVar9 + 0x25) = 7;
        *(undefined1 *)(iVar9 + 0x26) = 0xf;
      }
      else {
        bVar2 = false;
        if ((iVar6 == 1) || (iVar6 == 5)) {
          bVar2 = true;
        }
        dVar11 = extraout_f1;
        if (!bVar2) {
          dVar11 = (double)gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,
                                            param_7,param_8,&DAT_80436068,0x209,
                                            s_sel____HSD_TE_RGB____sel____HSD__803ad8cc,iVar3,
                                            param_13,param_14,param_15,param_16);
        }
        bVar2 = false;
        if (((param_12 == 3) || (iVar6 != 1)) || (*(char *)((int)param_11 + 0xe) != '\0')) {
          bVar2 = true;
        }
        if (!bVar2) {
          dVar11 = (double)gnt4___assert_bl(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,&DAT_80436068,0x20b,
                                            s_idx____3____sel____HSD_TE_RGB____803ad8f4,iVar3,
                                            param_13,param_14,param_15,param_16);
        }
        bVar2 = false;
        if (((param_12 == 3) || (iVar6 != 5)) || (*(char *)((int)param_11 + 0x1a) != '\0')) {
          bVar2 = true;
        }
        if (!bVar2) {
          gnt4___assert_bl(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80436068,0x20c,s_idx____3____sel____HSD_TE_A____e_803ad928,iVar3,
                           param_13,param_14,param_15,param_16);
        }
        piVar7 = *(int **)(iVar9 + 0x28);
        if (piVar7 == (int *)0x0) {
          iVar3 = 0;
        }
        else if (piVar7 == (int *)0xffffffff) {
          iVar3 = 2;
        }
        else if (piVar7 == (int *)0xfffffffe) {
          iVar3 = 3;
        }
        else {
          iVar3 = *piVar7;
        }
        if (iVar3 == 4) {
          *(char *)(piVar7 + 4) = *(char *)(piVar7 + 4) + '\x01';
        }
        else if ((iVar3 < 4) && (iVar3 == 1)) {
          if (*(char *)(iVar9 + 0x25) == '\x01') {
            piVar7[2] = piVar7[2] + 1;
          }
          else {
            piVar7[5] = piVar7[5] + 1;
          }
        }
      }
      goto LAB_8025e8cc;
    }
    if (bVar1 == 4) {
      *(undefined1 *)(iVar9 + 0x25) = *(undefined1 *)(param_11 + 3);
      piVar7 = *(int **)(iVar9 + 0x28);
      if (piVar7 == (int *)0x0) {
        iVar3 = 0;
      }
      else if (piVar7 == (int *)0xffffffff) {
        iVar3 = 2;
      }
      else if (piVar7 == (int *)0xfffffffe) {
        iVar3 = 3;
      }
      else {
        iVar3 = *piVar7;
      }
      if (iVar3 == 4) {
        *(char *)(piVar7 + 4) = *(char *)(piVar7 + 4) + '\x01';
      }
      else if ((iVar3 < 4) && (iVar3 == 1)) {
        if (*(char *)(iVar9 + 0x25) == '\x01') {
          piVar7[2] = piVar7[2] + 1;
        }
        else {
          piVar7[5] = piVar7[5] + 1;
        }
      }
      goto LAB_8025e8cc;
    }
    if (3 < bVar1) {
      gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       &DAT_80436068,0x276,&DAT_80436078,iVar3,param_13,param_14,param_15,param_16);
      goto LAB_8025e8cc;
    }
    cVar8 = -1;
    dVar11 = extraout_f1;
    if (iVar6 == 3) {
      cVar8 = '\x02';
      *(undefined1 *)(iVar9 + 0x26) = 10;
    }
    else if (iVar6 < 3) {
      if (iVar6 == 1) {
        cVar8 = '\0';
        *(undefined1 *)(iVar9 + 0x26) = 10;
      }
      else if (iVar6 < 1) {
LAB_8025e860:
        dVar11 = (double)gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,
                                          param_7,param_8,&DAT_80436068,0x25f,&DAT_80436078,iVar3,
                                          param_13,param_14,param_15,param_16);
      }
      else {
        cVar8 = '\x01';
        *(undefined1 *)(iVar9 + 0x26) = 10;
      }
    }
    else if (iVar6 == 5) {
      *(undefined1 *)(iVar9 + 0x26) = 0xb;
    }
    else {
      if (4 < iVar6) goto LAB_8025e860;
      cVar8 = '\x03';
      *(undefined1 *)(iVar9 + 0x26) = 10;
    }
    if (*(char *)(iVar5 + 0x1f) == -1) {
      *(char *)(iVar5 + 0x1f) = cVar8;
    }
    else {
      bVar2 = false;
      if ((cVar8 == -1) || (*(char *)(iVar5 + 0x1f) == cVar8)) {
        bVar2 = true;
      }
      if (!bVar2) {
        gnt4___assert_bl(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80436068,0x264,s_swap____HSD_TE_UNDEF____tev_>ras_803ad988,iVar3,
                         param_13,param_14,param_15,param_16);
      }
    }
    goto LAB_8025e8cc;
  }
  cVar8 = -1;
  dVar11 = extraout_f1;
  if (iVar6 == 3) {
    cVar8 = '\x02';
    *(undefined1 *)(iVar9 + 0x26) = 8;
  }
  else if (iVar6 < 3) {
    if (iVar6 == 1) {
      cVar8 = '\0';
      *(undefined1 *)(iVar9 + 0x26) = 8;
    }
    else if (iVar6 < 1) {
LAB_8025e788:
      dVar11 = (double)gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,&DAT_80436068,0x22f,&DAT_80436078,iVar3,param_13,
                                        param_14,param_15,param_16);
    }
    else {
      cVar8 = '\x01';
      *(undefined1 *)(iVar9 + 0x26) = 8;
    }
  }
  else if (iVar6 == 5) {
    *(undefined1 *)(iVar9 + 0x26) = 9;
  }
  else {
    if (4 < iVar6) goto LAB_8025e788;
    cVar8 = '\x03';
    *(undefined1 *)(iVar9 + 0x26) = 8;
  }
  if (*(char *)(iVar5 + 0x1e) == -1) {
    *(char *)(iVar5 + 0x1e) = cVar8;
  }
  else {
    bVar2 = false;
    if ((cVar8 == -1) || (*(char *)(iVar5 + 0x1e) == cVar8)) {
      bVar2 = true;
    }
    if (!bVar2) {
      gnt4___assert_bl(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436068,
                       0x234,s_swap____HSD_TE_UNDEF____tev_>tex_803ad958,iVar3,param_13,param_14,
                       param_15,param_16);
    }
  }
LAB_8025e8cc:
  gnt4_HSD_TExpUnref_bl();
  gnt4__restgpr_24_bl();
  return;
}



// ==== 8025e8f0  gnt4-HSD_TExpColorIn-bl ====

void gnt4_HSD_TExpColorIn_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 *param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14,
               undefined4 *param_15,undefined4 param_16,undefined4 *param_17)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined8 extraout_f1;
  undefined8 uVar8;
  undefined8 uVar9;
  
  uVar9 = gnt4__savegpr_23_bl();
  piVar2 = (int *)((ulonglong)uVar9 >> 0x20);
  uVar3 = param_12;
  puVar4 = param_13;
  uVar5 = param_14;
  puVar6 = param_15;
  uVar7 = param_16;
  if (piVar2 == (int *)0x0) {
    uVar8 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x2b5,&DAT_80436070,param_12,param_13,param_14,param_15,
                             param_16);
    iVar1 = 0;
  }
  else {
    uVar8 = extraout_f1;
    if (piVar2 == (int *)0xffffffff) {
      iVar1 = 2;
    }
    else if (piVar2 == (int *)0xfffffffe) {
      iVar1 = 3;
    }
    else {
      iVar1 = *piVar2;
    }
  }
  if (iVar1 != 1) {
    uVar8 = gnt4___assert_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x2b6,s_HSD_TExpGetType_texp_____HSD_TE__803ad880,uVar3,
                             puVar4,uVar5,puVar6,uVar7);
  }
  uVar9 = gnt4_HSD_TExpColorInSub_bl
                    (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,(int)uVar9
                     ,param_11,0,puVar4,uVar5,puVar6,uVar7);
  uVar9 = gnt4_HSD_TExpColorInSub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,param_12,
                     param_13,1,puVar4,uVar5,puVar6,uVar7);
  uVar9 = gnt4_HSD_TExpColorInSub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,param_14,
                     param_15,2,puVar4,uVar5,puVar6,uVar7);
  gnt4_HSD_TExpColorInSub_bl
            (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,param_16,param_17,
             3,puVar4,uVar5,puVar6,uVar7);
  gnt4__restgpr_23_bl();
  return;
}



// ==== 8025e9f8  gnt4-HSD_TExpAlphaInSub-bl ====

/* WARNING: Removing unreachable block (ram,0x8025eb78) */

void gnt4_HSD_TExpAlphaInSub_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 *param_11,int param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  bool bVar2;
  undefined1 uVar4;
  char cVar5;
  int iVar3;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  undefined8 extraout_f1;
  undefined8 uVar12;
  
  uVar12 = gnt4__savegpr_27_bl();
  iVar6 = (int)((ulonglong)uVar12 >> 0x20);
  iVar7 = (int)uVar12;
  iVar3 = param_12 * 8;
  iVar11 = iVar6 + iVar3;
  uVar9 = 0x803b0000;
  *(char *)(iVar11 + 0x45) = (char)uVar12;
  *(undefined4 **)(iVar11 + 0x48) = param_11;
  if (param_11 == (undefined4 *)0x0) {
    uVar4 = 0;
  }
  else if (param_11 == (undefined4 *)0xffffffff) {
    uVar4 = 2;
  }
  else if (param_11 == (undefined4 *)0xfffffffe) {
    uVar4 = 3;
  }
  else {
    uVar4 = (undefined1)*param_11;
  }
  *(undefined1 *)(iVar11 + 0x44) = uVar4;
  iVar10 = iVar6 + iVar3;
  *(undefined1 *)(iVar10 + 0x46) = 0xff;
  if (iVar7 == 7) {
    *(undefined1 *)(iVar11 + 0x44) = 0;
    *(undefined1 *)(iVar10 + 0x46) = 7;
    *(undefined4 *)(iVar11 + 0x48) = 0;
  }
  else if ((iVar7 < 7) || (0xf < iVar7)) {
    bVar1 = *(byte *)(iVar11 + 0x44);
    if (bVar1 == 2) {
      if (iVar7 != 5) {
        gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80436068,0x310,s_sel____HSD_TE_A_803ad9e8,0x803b0000,iVar3,param_14,
                         param_15,param_16);
      }
      *(undefined1 *)(iVar10 + 0x46) = 4;
    }
    else if (bVar1 < 2) {
      if (bVar1 == 0) {
        *(undefined4 *)(iVar11 + 0x48) = 0;
        *(undefined1 *)(iVar11 + 0x44) = 0;
        *(undefined1 *)(iVar11 + 0x45) = 7;
        *(undefined1 *)(iVar10 + 0x46) = 7;
      }
      else {
        uVar12 = extraout_f1;
        if (iVar7 != 5) {
          uVar12 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,
                                    param_8,&DAT_80436068,0x305,s_sel____HSD_TE_A_803ad9e8,
                                    0x803b0000,iVar3,param_14,param_15,param_16);
        }
        bVar2 = false;
        if ((param_12 == 3) || (*(char *)((int)param_11 + 0x1a) != '\0')) {
          bVar2 = true;
        }
        if (!bVar2) {
          gnt4___assert_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80436068,0x306,s_idx____3____exp_>tev_a_clamp_803ad9f8,uVar9,iVar3,
                           param_14,param_15,param_16);
        }
        piVar8 = *(int **)(iVar11 + 0x48);
        if (piVar8 == (int *)0x0) {
          iVar3 = 0;
        }
        else if (piVar8 == (int *)0xffffffff) {
          iVar3 = 2;
        }
        else if (piVar8 == (int *)0xfffffffe) {
          iVar3 = 3;
        }
        else {
          iVar3 = *piVar8;
        }
        if (iVar3 == 4) {
          *(char *)(piVar8 + 4) = *(char *)(piVar8 + 4) + '\x01';
        }
        else if ((iVar3 < 4) && (iVar3 == 1)) {
          if (*(char *)(iVar11 + 0x45) == '\x01') {
            piVar8[2] = piVar8[2] + 1;
          }
          else {
            piVar8[5] = piVar8[5] + 1;
          }
        }
      }
    }
    else if (bVar1 == 4) {
      uVar12 = extraout_f1;
      if (-1 < (int)((~(iVar7 - 5U) | 1) - (1 - (iVar7 - 5U) >> 1))) {
        uVar12 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,
                                  param_8,&DAT_80436068,0x30a,
                                  s_sel____HSD_TE_A____sel____HSD_TE_803ada18,0x803b0000,iVar3,
                                  param_14,param_15,param_16);
      }
      if (*(char *)(param_11 + 3) != '\x06') {
        gnt4___assert_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80436068,0x30b,s_exp_>cnst_comp____HSD_TE_X_803ada3c,uVar9,iVar3,
                         param_14,param_15,param_16);
      }
      *(undefined1 *)(iVar11 + 0x45) = 6;
      piVar8 = *(int **)(iVar11 + 0x48);
      if (piVar8 == (int *)0x0) {
        iVar3 = 0;
      }
      else if (piVar8 == (int *)0xffffffff) {
        iVar3 = 2;
      }
      else if (piVar8 == (int *)0xfffffffe) {
        iVar3 = 3;
      }
      else {
        iVar3 = *piVar8;
      }
      if (iVar3 == 4) {
        *(char *)(piVar8 + 4) = *(char *)(piVar8 + 4) + '\x01';
      }
      else if ((iVar3 < 4) && (iVar3 == 1)) {
        if (*(char *)(iVar11 + 0x45) == '\x01') {
          piVar8[2] = piVar8[2] + 1;
        }
        else {
          piVar8[5] = piVar8[5] + 1;
        }
      }
    }
    else if (bVar1 < 4) {
      if (iVar7 != 5) {
        gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80436068,0x314,s_sel____HSD_TE_A_803ad9e8,0x803b0000,iVar3,param_14,
                         param_15,param_16);
      }
      *(undefined1 *)(iVar10 + 0x46) = 5;
    }
    else {
      gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       &DAT_80436068,0x318,&DAT_80436078,0x803b0000,iVar3,param_14,param_15,param_16
                      );
    }
  }
  else {
    *(undefined4 *)(iVar11 + 0x48) = 0;
    *(undefined1 *)(iVar10 + 0x46) = 6;
    switch(iVar7) {
    case 9:
      cVar5 = '\a';
      break;
    case 10:
      cVar5 = '\x06';
      break;
    case 0xb:
      cVar5 = '\x05';
      break;
    case 0xc:
      cVar5 = '\x04';
      break;
    case 0xd:
      cVar5 = '\x03';
      break;
    case 0xe:
      cVar5 = '\x02';
      break;
    case 0xf:
      cVar5 = '\x01';
      break;
    default:
      cVar5 = '\0';
    }
    if (*(char *)(iVar6 + 0x21) == -1) {
      *(char *)(iVar6 + 0x21) = cVar5;
    }
    else if (*(char *)(iVar6 + 0x21) != cVar5) {
      gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       &DAT_80436068,0x2ee,s_tev_>kasel____ksel_803ad9d4,0x803b0000,iVar3,param_14,
                       param_15,param_16);
    }
    *(undefined1 *)(iVar11 + 0x44) = 6;
  }
  gnt4_HSD_TExpUnref_bl();
  gnt4__restgpr_27_bl();
  return;
}



// ==== 8025edf0  gnt4-HSD_TExpAlphaIn-bl ====

void gnt4_HSD_TExpAlphaIn_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 *param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14,
               undefined4 *param_15,undefined4 param_16,undefined4 *param_17)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined8 extraout_f1;
  undefined8 uVar8;
  undefined8 uVar9;
  
  uVar9 = gnt4__savegpr_23_bl();
  piVar2 = (int *)((ulonglong)uVar9 >> 0x20);
  uVar3 = param_12;
  puVar4 = param_13;
  uVar5 = param_14;
  puVar6 = param_15;
  uVar7 = param_16;
  if (piVar2 == (int *)0x0) {
    uVar8 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x337,&DAT_80436070,param_12,param_13,param_14,param_15,
                             param_16);
    iVar1 = 0;
  }
  else {
    uVar8 = extraout_f1;
    if (piVar2 == (int *)0xffffffff) {
      iVar1 = 2;
    }
    else if (piVar2 == (int *)0xfffffffe) {
      iVar1 = 3;
    }
    else {
      iVar1 = *piVar2;
    }
  }
  if (iVar1 != 1) {
    uVar8 = gnt4___assert_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x338,s_HSD_TExpGetType_texp_____HSD_TE__803ad880,uVar3,
                             puVar4,uVar5,puVar6,uVar7);
  }
  uVar9 = gnt4_HSD_TExpAlphaInSub_bl
                    (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,(int)uVar9
                     ,param_11,0,puVar4,uVar5,puVar6,uVar7);
  uVar9 = gnt4_HSD_TExpAlphaInSub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,param_12,
                     param_13,1,puVar4,uVar5,puVar6,uVar7);
  uVar9 = gnt4_HSD_TExpAlphaInSub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,param_14,
                     param_15,2,puVar4,uVar5,puVar6,uVar7);
  gnt4_HSD_TExpAlphaInSub_bl
            (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,param_16,param_17,
             3,puVar4,uVar5,puVar6,uVar7);
  gnt4__restgpr_23_bl();
  return;
}



// ==== 8025eef8  gnt4-HSD_TExpOrder-bl ====

void gnt4_HSD_TExpOrder_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,int param_10,int param_11,
               undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == (int *)0x0) {
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436068,0x347,&DAT_80436070,param_12,param_13,param_14,param_15
                               ,param_16);
    iVar1 = 0;
  }
  else if (param_9 == (int *)0xffffffff) {
    iVar1 = 2;
  }
  else if (param_9 == (int *)0xfffffffe) {
    iVar1 = 3;
  }
  else {
    iVar1 = *param_9;
  }
  if (iVar1 != 1) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436068,
                     0x348,s_HSD_TExpGetType_texp_____HSD_TE__803ad880,param_12,param_13,param_14,
                     param_15,param_16);
  }
  param_9[0x19] = param_10;
  if (param_11 == 0xff) {
    *(undefined1 *)(param_9 + 0x1a) = 0xff;
  }
  else {
    *(char *)(param_9 + 0x1a) = (char)param_11;
  }
  return;
}



// ==== 8025efbc  gnt4-AssignColorReg-bl ====

undefined4 gnt4_AssignColorReg_bl(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = param_2 * 8;
  iVar3 = param_1 + iVar1;
  iVar2 = *(int *)(iVar3 + 0x28);
  if (*(byte *)(iVar2 + 0xe) == 0xff) {
    if (*(char *)(iVar2 + 0xc) == '\x06') {
      iVar3 = param_3 + 8;
      iVar4 = 4;
      iVar5 = 4;
      do {
        if (*(char *)(iVar3 + 0xd) == '\0') {
          *(undefined1 *)(param_3 + iVar4 * 2 + 0xd) = 1;
          *(char *)(iVar2 + 0xe) = (char)iVar4;
          *(undefined1 *)(iVar2 + 0xf) = 3;
          *(undefined1 *)(param_1 + iVar1 + 0x24) = 5;
          *(char *)(param_1 + iVar1 + 0x26) = (char)(&PTR_caseD_c_803ada64)[iVar4];
          return 0;
        }
        iVar3 = iVar3 + 2;
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    else {
      iVar3 = param_3 + 8;
      iVar4 = 4;
      iVar5 = 4;
      do {
        if (*(char *)(iVar3 + 0xc) == '\0') {
          *(undefined1 *)(param_3 + iVar4 * 2 + 0xc) = 3;
          *(char *)(iVar2 + 0xe) = (char)iVar4;
          *(undefined1 *)(iVar2 + 0xf) = 0;
          *(undefined1 *)(param_1 + iVar1 + 0x24) = 5;
          *(char *)(param_1 + iVar1 + 0x26) = (char)(&DAT_803ada74)[iVar4];
          return 0;
        }
        iVar3 = iVar3 + 2;
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    return 0xffffffff;
  }
  if (3 < *(byte *)(iVar2 + 0xe)) {
    *(undefined1 *)(iVar3 + 0x24) = 5;
    if (*(char *)(iVar2 + 0xc) == '\x06') {
      *(char *)(iVar3 + 0x26) = (char)(&PTR_caseD_c_803ada64)[*(byte *)(iVar2 + 0xe)];
    }
    else {
      *(char *)(iVar3 + 0x26) = (char)(&DAT_803ada74)[*(byte *)(iVar2 + 0xe)];
    }
    return 0;
  }
  return 0xffffffff;
}



// ==== 8025f134  gnt4-AssignColorKonst-bl ====

undefined4 gnt4_AssignColorKonst_bl(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = param_2 * 8;
  iVar5 = param_1 + iVar2;
  iVar3 = *(int *)(iVar5 + 0x28);
  uVar4 = (uint)*(byte *)(iVar3 + 0xe);
  if (uVar4 == 0xff) {
    if (*(char *)(iVar3 + 0xc) == '\x06') {
      iVar6 = 1;
      iVar7 = 3;
      iVar5 = param_3;
      do {
        if (*(char *)(iVar5 + 0xf) == '\0') {
          *(undefined1 *)(param_3 + iVar6 * 2 + 0xd) = 1;
          *(char *)(iVar3 + 0xe) = (char)iVar6;
          *(undefined1 *)(iVar3 + 0xf) = 3;
          *(char *)(param_1 + 0x20) =
               (char)*(undefined4 *)
                      ((uint)*(byte *)(iVar3 + 0xe) * 0x10 + -0x7fc5255c +
                      (uint)*(byte *)(iVar3 + 0xf) * 4);
          *(undefined1 *)(param_1 + iVar2 + 0x24) = 6;
          *(undefined1 *)(param_1 + iVar2 + 0x26) = 0xe;
          return 0;
        }
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + -1;
        iVar5 = iVar5 + 2;
      } while (iVar7 != 0);
      iVar6 = 0;
      iVar7 = 4;
      iVar5 = param_3;
      do {
        if (*(byte *)(iVar5 + 0xc) < 3) {
          *(char *)(iVar3 + 0xe) = (char)iVar6;
          iVar5 = param_3 + iVar6 * 2;
          cVar1 = *(char *)(iVar5 + 0xc);
          *(char *)(iVar5 + 0xc) = cVar1 + '\x01';
          *(char *)(iVar3 + 0xf) = cVar1;
          *(char *)(param_1 + 0x20) =
               (char)*(undefined4 *)
                      ((uint)*(byte *)(iVar3 + 0xe) * 0x10 + -0x7fc5255c +
                      (uint)*(byte *)(iVar3 + 0xf) * 4);
          *(undefined1 *)(param_1 + iVar2 + 0x24) = 6;
          *(undefined1 *)(param_1 + iVar2 + 0x26) = 0xe;
          return 0;
        }
        iVar5 = iVar5 + 2;
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    else {
      iVar6 = 0;
      iVar7 = 4;
      iVar5 = param_3;
      do {
        if (*(char *)(iVar5 + 0xc) == '\0') {
          *(undefined1 *)(param_3 + iVar6 * 2 + 0xc) = 3;
          *(char *)(iVar3 + 0xe) = (char)iVar6;
          *(undefined1 *)(iVar3 + 0xf) = 0;
          *(char *)(param_1 + 0x20) =
               (char)*(undefined4 *)(&DAT_803adae4 + (uint)*(byte *)(iVar3 + 0xe) * 4);
          *(undefined1 *)(param_1 + iVar2 + 0x24) = 6;
          *(undefined1 *)(param_1 + iVar2 + 0x26) = 0xe;
          return 0;
        }
        iVar5 = iVar5 + 2;
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    return 0xffffffff;
  }
  if (uVar4 < 4) {
    if (*(char *)(iVar3 + 0xc) == '\x06') {
      *(char *)(param_1 + 0x20) =
           (char)*(undefined4 *)(uVar4 * 0x10 + -0x7fc5255c + (uint)*(byte *)(iVar3 + 0xf) * 4);
      *(undefined1 *)(iVar5 + 0x24) = 6;
      *(undefined1 *)(iVar5 + 0x26) = 0xe;
    }
    else {
      *(char *)(param_1 + 0x20) = (char)*(undefined4 *)(&DAT_803adae4 + uVar4 * 4);
      *(undefined1 *)(iVar5 + 0x24) = 6;
      *(undefined1 *)(iVar5 + 0x26) = 0xe;
    }
    return 0;
  }
  return 0xffffffff;
}



// ==== 8025f360  gnt4-AssignAlphaKonst-bl ====

undefined4 gnt4_AssignAlphaKonst_bl(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = param_2 * 8;
  iVar5 = param_1 + iVar2;
  iVar4 = *(int *)(iVar5 + 0x48);
  uVar3 = (uint)*(byte *)(iVar4 + 0xe);
  if (uVar3 == 0xff) {
    iVar6 = 1;
    iVar7 = 3;
    iVar5 = param_3;
    do {
      if (*(char *)(iVar5 + 0xf) == '\0') {
        *(undefined1 *)(param_3 + iVar6 * 2 + 0xd) = 1;
        *(char *)(iVar4 + 0xe) = (char)iVar6;
        *(undefined1 *)(iVar4 + 0xf) = 3;
        *(char *)(param_1 + 0x21) =
             (char)*(undefined4 *)
                    ((uint)*(byte *)(iVar4 + 0xe) * 0x10 + -0x7fc5250c +
                    (uint)*(byte *)(iVar4 + 0xf) * 4);
        *(undefined1 *)(param_1 + iVar2 + 0x44) = 6;
        *(undefined1 *)(param_1 + iVar2 + 0x46) = 6;
        return 0;
      }
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + -1;
      iVar5 = iVar5 + 2;
    } while (iVar7 != 0);
    iVar6 = 0;
    iVar7 = 4;
    iVar5 = param_3;
    do {
      if (*(byte *)(iVar5 + 0xc) < 3) {
        *(char *)(iVar4 + 0xe) = (char)iVar6;
        iVar5 = param_3 + iVar6 * 2;
        cVar1 = *(char *)(iVar5 + 0xc);
        *(char *)(iVar5 + 0xc) = cVar1 + '\x01';
        *(char *)(iVar4 + 0xf) = cVar1;
        *(char *)(param_1 + 0x21) =
             (char)*(undefined4 *)
                    ((uint)*(byte *)(iVar4 + 0xe) * 0x10 + -0x7fc5250c +
                    (uint)*(byte *)(iVar4 + 0xf) * 4);
        *(undefined1 *)(param_1 + iVar2 + 0x44) = 6;
        *(undefined1 *)(param_1 + iVar2 + 0x46) = 6;
        return 0;
      }
      iVar5 = iVar5 + 2;
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    return 0xffffffff;
  }
  if (3 < uVar3) {
    return 0xffffffff;
  }
  *(char *)(param_1 + 0x21) =
       (char)*(undefined4 *)(uVar3 * 0x10 + -0x7fc5250c + (uint)*(byte *)(iVar4 + 0xf) * 4);
  *(undefined1 *)(iVar5 + 0x44) = 6;
  *(undefined1 *)(iVar5 + 0x46) = 6;
  return 0;
}



// ==== 8025f4c4  gnt4-TExpAssignReg-bl ====

void gnt4_TExpAssignReg_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int in_r6;
  int in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  int iVar4;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 extraout_f1;
  undefined8 uVar9;
  
  uVar9 = gnt4__savegpr_27_bl();
  iVar4 = (int)((ulonglong)uVar9 >> 0x20);
  iVar3 = (int)uVar9;
  uVar9 = extraout_f1;
  if (0 < *(int *)(iVar4 + 8)) {
    if (*(char *)(iVar4 + 0x20) == -1) {
      bVar1 = false;
      if ((((*(char *)(iVar4 + 0xd) == '\0') && (*(char *)(iVar4 + 0x25) == '\a')) &&
          (*(char *)(iVar4 + 0x2d) == '\a')) &&
         ((*(char *)(iVar4 + 0xf) == '\0' && (*(char *)(iVar4 + 0x10) == '\0')))) {
        bVar1 = true;
      }
      if ((bVar1) && (*(char *)(iVar4 + 0x3c) == '\x04')) {
        iVar5 = gnt4_AssignColorReg_bl(iVar4,3,iVar3);
        if ((iVar5 < 0) && (iVar5 = gnt4_AssignColorKonst_bl(iVar4,3,iVar3), iVar5 < 0)) {
          gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80436068,0x489,s_val_>__0_803adb34,in_r6,in_r7,in_r8,in_r9,in_r10);
          goto LAB_8025fb78;
        }
      }
      else {
        iVar6 = 0;
        iVar5 = iVar4;
        do {
          if (((*(char *)(iVar5 + 0x24) == '\x04') &&
              (iVar2 = gnt4_AssignColorKonst_bl(iVar4,iVar6,iVar3), iVar2 < 0)) &&
             (iVar2 = gnt4_AssignColorReg_bl(iVar4,iVar6,iVar3), iVar2 < 0)) {
            gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x496,s_val_>__0_803adb34,in_r6,in_r7,in_r8,in_r9,in_r10)
            ;
            goto LAB_8025fb78;
          }
          iVar6 = iVar6 + 1;
          iVar5 = iVar5 + 8;
        } while (iVar6 < 4);
        iVar5 = iVar4 + iVar6 * 8;
        for (; iVar6 < 4; iVar6 = iVar6 + 1) {
          if ((*(char *)(iVar5 + 0x24) == '\x04') &&
             (iVar2 = gnt4_AssignColorReg_bl(iVar4,iVar6,iVar3), iVar2 < 0)) {
            gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x49f,s_val_>__0_803adb34,in_r6,in_r7,in_r8,in_r9,in_r10)
            ;
            goto LAB_8025fb78;
          }
          iVar5 = iVar5 + 8;
        }
      }
    }
    else {
      iVar6 = 0;
      iVar5 = iVar4;
      do {
        if ((*(char *)(iVar5 + 0x24) == '\x04') &&
           (iVar2 = gnt4_AssignColorReg_bl(iVar4,iVar6,iVar3), iVar2 < 0)) {
          gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80436068,0x47d,s_val_>__0_803adb34,in_r6,in_r7,in_r8,in_r9,in_r10);
          goto LAB_8025fb78;
        }
        iVar6 = iVar6 + 1;
        iVar5 = iVar5 + 8;
      } while (iVar6 < 4);
    }
  }
  if (0 < *(int *)(iVar4 + 0x14)) {
    if (*(char *)(iVar4 + 0x21) == -1) {
      bVar1 = false;
      if ((((*(char *)(iVar4 + 0x19) == '\0') && (*(char *)(iVar4 + 0x45) == '\a')) &&
          (*(char *)(iVar4 + 0x4d) == '\a')) &&
         ((*(char *)(iVar4 + 0x1b) == '\0' && (*(char *)(iVar4 + 0x1c) == '\0')))) {
        bVar1 = true;
      }
      if ((bVar1) && (*(char *)(iVar4 + 0x5c) == '\x04')) {
        iVar5 = *(int *)(iVar4 + 0x60);
        if (*(byte *)(iVar5 + 0xe) == 0xff) {
          iVar6 = iVar3 + 8;
          in_r6 = 4;
          iVar2 = 4;
          do {
            if (*(char *)(iVar6 + 0xd) == '\0') {
              *(undefined1 *)(iVar3 + in_r6 * 2 + 0xd) = 1;
              *(char *)(iVar5 + 0xe) = (char)in_r6;
              *(undefined1 *)(iVar5 + 0xf) = 3;
              iVar6 = 0;
              *(undefined1 *)(iVar4 + 0x5c) = 5;
              *(char *)(iVar4 + 0x5e) = (char)(&DAT_803ada84)[in_r6];
              goto LAB_8025f908;
            }
            iVar6 = iVar6 + 2;
            in_r6 = in_r6 + 1;
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
          iVar6 = -1;
        }
        else if (*(byte *)(iVar5 + 0xe) < 4) {
          iVar6 = -1;
        }
        else {
          *(undefined1 *)(iVar4 + 0x5c) = 5;
          iVar6 = 0;
          *(char *)(iVar4 + 0x5e) = (char)(&DAT_803ada84)[*(byte *)(iVar5 + 0xe)];
        }
LAB_8025f908:
        if ((iVar6 < 0) && (iVar4 = gnt4_AssignAlphaKonst_bl(iVar4,3,iVar3), iVar4 < 0)) {
          gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80436068,0x4bb,s_val_>__0_803adb34,in_r6,iVar5,in_r8,in_r9,in_r10);
        }
      }
      else {
        iVar6 = 0;
        iVar5 = iVar4;
        do {
          if ((*(char *)(iVar5 + 0x44) == '\x04') &&
             (iVar2 = gnt4_AssignAlphaKonst_bl(iVar4,iVar6,iVar3), iVar2 < 0)) {
            iVar2 = *(int *)(iVar5 + 0x48);
            if (*(byte *)(iVar2 + 0xe) == 0xff) {
              iVar7 = iVar3 + 8;
              in_r7 = 4;
              iVar8 = 4;
              do {
                if (*(char *)(iVar7 + 0xd) == '\0') {
                  in_r6 = 3;
                  *(undefined1 *)(iVar3 + in_r7 * 2 + 0xd) = 1;
                  iVar7 = 0;
                  *(char *)(iVar2 + 0xe) = (char)in_r7;
                  *(undefined1 *)(iVar2 + 0xf) = 3;
                  *(undefined1 *)(iVar5 + 0x44) = 5;
                  *(char *)(iVar5 + 0x46) = (char)(&DAT_803ada84)[in_r7];
                  goto LAB_8025fa30;
                }
                iVar7 = iVar7 + 2;
                in_r7 = in_r7 + 1;
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
              iVar7 = -1;
            }
            else if (*(byte *)(iVar2 + 0xe) < 4) {
              iVar7 = -1;
            }
            else {
              *(undefined1 *)(iVar5 + 0x44) = 5;
              iVar7 = 0;
              *(char *)(iVar5 + 0x46) = (char)(&DAT_803ada84)[*(byte *)(iVar2 + 0xe)];
            }
LAB_8025fa30:
            if (iVar7 < 0) {
              gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436068,0x4c8,s_val_>__0_803adb34,in_r6,in_r7,iVar2,in_r9,
                               in_r10);
              goto LAB_8025fb78;
            }
          }
          iVar6 = iVar6 + 1;
          iVar5 = iVar5 + 8;
        } while (iVar6 < 4);
        iVar4 = iVar4 + iVar6 * 8;
        for (; iVar6 < 4; iVar6 = iVar6 + 1) {
          if (*(char *)(iVar4 + 0x44) == '\x04') {
            iVar5 = *(int *)(iVar4 + 0x48);
            if (*(byte *)(iVar5 + 0xe) == 0xff) {
              iVar2 = iVar3 + 8;
              in_r7 = 4;
              iVar7 = 4;
              do {
                if (*(char *)(iVar2 + 0xd) == '\0') {
                  in_r6 = 3;
                  *(undefined1 *)(iVar3 + in_r7 * 2 + 0xd) = 1;
                  iVar2 = 0;
                  *(char *)(iVar5 + 0xe) = (char)in_r7;
                  *(undefined1 *)(iVar5 + 0xf) = 3;
                  *(undefined1 *)(iVar4 + 0x44) = 5;
                  *(char *)(iVar4 + 0x46) = (char)(&DAT_803ada84)[in_r7];
                  goto LAB_8025fb3c;
                }
                iVar2 = iVar2 + 2;
                in_r7 = in_r7 + 1;
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
              iVar2 = -1;
            }
            else if (*(byte *)(iVar5 + 0xe) < 4) {
              iVar2 = -1;
            }
            else {
              *(undefined1 *)(iVar4 + 0x44) = 5;
              iVar2 = 0;
              *(char *)(iVar4 + 0x46) = (char)(&DAT_803ada84)[*(byte *)(iVar5 + 0xe)];
            }
LAB_8025fb3c:
            if (iVar2 < 0) {
              gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436068,0x4d1,s_val_>__0_803adb34,in_r6,in_r7,iVar5,iVar4,
                               in_r10);
              break;
            }
          }
          iVar4 = iVar4 + 8;
        }
      }
    }
    else {
      iVar5 = 0;
      do {
        if (*(char *)(iVar4 + 0x44) == '\x04') {
          iVar6 = *(int *)(iVar4 + 0x48);
          if (*(byte *)(iVar6 + 0xe) == 0xff) {
            in_r7 = 4;
            iVar2 = iVar3 + 8;
            iVar7 = 4;
            do {
              if (*(char *)(iVar2 + 0xd) == '\0') {
                in_r6 = 3;
                *(undefined1 *)(iVar3 + in_r7 * 2 + 0xd) = 1;
                iVar2 = 0;
                *(char *)(iVar6 + 0xe) = (char)in_r7;
                *(undefined1 *)(iVar6 + 0xf) = 3;
                *(undefined1 *)(iVar4 + 0x44) = 5;
                *(char *)(iVar4 + 0x46) = (char)(&DAT_803ada84)[in_r7];
                goto LAB_8025f7b8;
              }
              iVar2 = iVar2 + 2;
              in_r7 = in_r7 + 1;
              iVar7 = iVar7 + -1;
            } while (iVar7 != 0);
            iVar2 = -1;
          }
          else if (*(byte *)(iVar6 + 0xe) < 4) {
            iVar2 = -1;
          }
          else {
            *(undefined1 *)(iVar4 + 0x44) = 5;
            iVar2 = 0;
            *(char *)(iVar4 + 0x46) = (char)(&DAT_803ada84)[*(byte *)(iVar6 + 0xe)];
          }
LAB_8025f7b8:
          if (iVar2 < 0) {
            gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x4af,s_val_>__0_803adb34,in_r6,in_r7,iVar6,iVar4,iVar5);
            break;
          }
        }
        iVar5 = iVar5 + 1;
        iVar4 = iVar4 + 8;
      } while (iVar5 < 4);
    }
  }
LAB_8025fb78:
  gnt4__restgpr_27_bl();
  return;
}



// ==== 8025fb90  gnt4-TExp2TevDesc-bl ====

void gnt4_TExp2TevDesc_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               int *param_11,int *param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined8 extraout_f1;
  undefined8 uVar7;
  
  uVar7 = gnt4__savegpr_27_bl();
  piVar4 = (int *)((ulonglong)uVar7 >> 0x20);
  puVar5 = (undefined4 *)uVar7;
  piVar6 = param_12;
  uVar7 = extraout_f1;
  if (piVar4 == (int *)0x0) {
    uVar7 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x509,&DAT_80436070,param_12,param_13,param_14,param_15,
                             param_16);
  }
  if (puVar5 == (undefined4 *)0x0) {
    uVar7 = gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x50a,&DAT_8043607c,piVar6,param_13,param_14,param_15,
                             param_16);
  }
  if (piVar4 == (int *)0x0) {
    iVar2 = 0;
  }
  else if (piVar4 == (int *)0xffffffff) {
    iVar2 = 2;
  }
  else if (piVar4 == (int *)0xfffffffe) {
    iVar2 = 3;
  }
  else {
    iVar2 = *piVar4;
  }
  if (iVar2 != 1) {
    uVar7 = gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x50b,s_HSD_TExpGetType_texp_____HSD_TE__803ad880,piVar6,
                             param_13,param_14,param_15,param_16);
  }
  *puVar5 = 0;
  puVar5[1] = 1;
  puVar5[0x1d] = piVar4[0x19];
  if (piVar4[0x19] == 0) {
    puVar5[3] = 0xff;
    puVar5[4] = 0xff;
  }
  uVar3 = (uint)*(byte *)(piVar4 + 0x1a);
  if (uVar3 == 0xff) {
    uVar3 = 0xff;
  }
  puVar5[5] = uVar3;
  uVar3 = (uint)*(byte *)((int)piVar4 + 0x1f);
  if (uVar3 == 0xff) {
    uVar3 = 0;
  }
  puVar5[0x19] = uVar3;
  uVar3 = (uint)*(byte *)((int)piVar4 + 0x1e);
  if (uVar3 == 0xff) {
    uVar3 = 0;
  }
  puVar5[0x1a] = uVar3;
  uVar3 = (uint)*(byte *)(piVar4 + 8);
  if (uVar3 == 0xff) {
    uVar3 = 0;
  }
  puVar5[0x1b] = uVar3;
  uVar3 = (uint)*(byte *)((int)piVar4 + 0x21);
  if (uVar3 == 0xff) {
    uVar3 = 0;
  }
  puVar5[0x1c] = uVar3;
  if ((*(byte *)((int)piVar4 + 0xd) == 0xff) ||
     (((((piVar4[2] == 0 && (cVar1 = *(char *)((int)piVar4 + 0x19), cVar1 != '\b')) &&
        (cVar1 != '\t')) && ((cVar1 != '\n' && (cVar1 != '\v')))) &&
      ((cVar1 != '\f' && (cVar1 != '\r')))))) {
    puVar5[6] = 0;
    puVar5[7] = 0xf;
    puVar5[8] = 0xf;
    puVar5[9] = 0xf;
    if (*param_11 == 0) {
      puVar5[10] = 0;
    }
    else {
      *param_11 = 0;
      puVar5[10] = 0xf;
    }
    puVar5[0xb] = 0;
    puVar5[0xc] = 0;
    *(undefined1 *)(puVar5 + 0xd) = 0;
    puVar5[0xe] = 0;
  }
  else {
    puVar5[6] = (uint)*(byte *)((int)piVar4 + 0xd);
    uVar3 = (uint)*(byte *)((int)piVar4 + 0x26);
    if (uVar3 == 0xff) {
      uVar3 = 0xf;
    }
    puVar5[7] = uVar3;
    uVar3 = (uint)*(byte *)((int)piVar4 + 0x2e);
    if (uVar3 == 0xff) {
      uVar3 = 0xf;
    }
    puVar5[8] = uVar3;
    uVar3 = (uint)*(byte *)((int)piVar4 + 0x36);
    if (uVar3 == 0xff) {
      uVar3 = 0xf;
    }
    puVar5[9] = uVar3;
    uVar3 = (uint)*(byte *)((int)piVar4 + 0x3e);
    if (uVar3 == 0xff) {
      uVar3 = 0xf;
    }
    puVar5[10] = uVar3;
    uVar3 = (uint)*(byte *)(piVar4 + 4);
    if (uVar3 == 0xff) {
      uVar3 = 0;
    }
    puVar5[0xb] = uVar3;
    uVar3 = (uint)*(byte *)((int)piVar4 + 0xf);
    if (uVar3 == 0xff) {
      uVar3 = 0;
    }
    puVar5[0xc] = uVar3;
    *(byte *)(puVar5 + 0xd) = (byte)(-(uint)*(byte *)((int)piVar4 + 0xe) >> 0x1f);
    if (*(char *)(piVar4 + 3) == -1) {
      uVar7 = gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436068,0x54a,s_tev_>c_dst____HSD_TE_UNDEF_803adb50,piVar6,
                               param_13,param_14,param_15,param_16);
    }
    puVar5[0xe] = *(undefined4 *)(&DAT_803adb40 + (uint)*(byte *)(piVar4 + 3) * 4);
    if (puVar5[0xe] == 0) {
      *param_11 = 0;
    }
  }
  if ((*(byte *)((int)piVar4 + 0x19) == 0xff) || (piVar4[5] == 0)) {
    puVar5[0xf] = 0;
    puVar5[0x10] = 7;
    puVar5[0x11] = 7;
    puVar5[0x12] = 7;
    if (*param_12 == 0) {
      puVar5[0x13] = 0;
    }
    else {
      *param_12 = 0;
      puVar5[0x13] = 7;
    }
    puVar5[0x14] = 0;
    puVar5[0x15] = 0;
    *(undefined1 *)(puVar5 + 0x16) = 0;
    puVar5[0x17] = 0;
  }
  else {
    puVar5[0xf] = (uint)*(byte *)((int)piVar4 + 0x19);
    uVar3 = (uint)*(byte *)((int)piVar4 + 0x46);
    if (uVar3 == 0xff) {
      uVar3 = 7;
    }
    puVar5[0x10] = uVar3;
    uVar3 = (uint)*(byte *)((int)piVar4 + 0x4e);
    if (uVar3 == 0xff) {
      uVar3 = 7;
    }
    puVar5[0x11] = uVar3;
    uVar3 = (uint)*(byte *)((int)piVar4 + 0x56);
    if (uVar3 == 0xff) {
      uVar3 = 7;
    }
    puVar5[0x12] = uVar3;
    uVar3 = (uint)*(byte *)((int)piVar4 + 0x5e);
    if (uVar3 == 0xff) {
      uVar3 = 7;
    }
    puVar5[0x13] = uVar3;
    uVar3 = (uint)*(byte *)(piVar4 + 7);
    if (uVar3 == 0xff) {
      uVar3 = 0;
    }
    puVar5[0x14] = uVar3;
    uVar3 = (uint)*(byte *)((int)piVar4 + 0x1b);
    if (uVar3 == 0xff) {
      uVar3 = 0;
    }
    puVar5[0x15] = uVar3;
    *(byte *)(puVar5 + 0x16) = (byte)(-(uint)*(byte *)((int)piVar4 + 0x1a) >> 0x1f);
    if (*(char *)(piVar4 + 6) == -1) {
      gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436068,
                       0x56e,s_tev_>a_dst____HSD_TE_UNDEF_803adb6c,piVar6,param_13,param_14,param_15
                       ,param_16);
    }
    puVar5[0x17] = *(undefined4 *)(&DAT_803adb40 + (uint)*(byte *)(piVar4 + 6) * 4);
    if (puVar5[0x17] == 0) {
      *param_12 = 0;
    }
  }
  puVar5[0x18] = 0;
  gnt4__restgpr_27_bl();
  return;
}



// ==== 8025ff90  gnt4-HSD_TExpSetReg-bl ====

/* WARNING: Removing unreachable block (ram,0x80260010) */
/* WARNING: Removing unreachable block (ram,0x80260224) */
/* WARNING: Removing unreachable block (ram,0x80260324) */

void gnt4_HSD_TExpSetReg_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  byte bVar1;
  char *pcVar2;
  int *piVar3;
  uint uVar4;
  float *pfVar5;
  double *pdVar6;
  ushort *puVar7;
  uint uVar8;
  byte bVar9;
  uint in_r6;
  uint in_r7;
  uint *puVar10;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar11;
  undefined4 *puVar12;
  byte *pbVar13;
  uint uVar14;
  double extraout_f1;
  double dVar15;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  byte local_5c [16];
  undefined4 local_4c [5];
  double local_38;
  double local_30;
  double local_28;
  
  piVar3 = (int *)gnt4__savegpr_26_bl();
  uVar14 = 0;
  dVar15 = extraout_f1;
  do {
    if (piVar3 == (int *)0x0) {
      if (uVar14 != 0) {
        gnt4_GXPixModeSync_bl();
        pbVar13 = local_5c;
        piVar3 = &DAT_803adb88;
        iVar11 = 0;
        do {
          if ((uVar14 & 1 << iVar11) != 0) {
            local_64 = *(undefined4 *)pbVar13;
            gnt4_GXSetTevKColor_bl(*piVar3,(byte *)&local_64);
          }
          iVar11 = iVar11 + 1;
          piVar3 = piVar3 + 1;
          pbVar13 = pbVar13 + 4;
        } while (iVar11 < 4);
        puVar12 = local_4c;
        iVar11 = 4;
        pcVar2 = s_clist_>type____HSD_TE_CNST_803adba4;
        do {
          if ((uVar14 & 1 << iVar11) != 0) {
            local_68 = *puVar12;
            gnt4_GXSetTevColor_bl(*(int *)(pcVar2 + -0xc),(byte *)&local_68);
          }
          iVar11 = iVar11 + 1;
          puVar12 = puVar12 + 1;
          pcVar2 = pcVar2 + 4;
        } while (iVar11 < 7);
        gnt4_HSD_StateInvalidate_bl(0x10);
        gnt4_GXPixModeSync_bl();
      }
      gnt4__restgpr_26_bl();
      return;
    }
    if (*piVar3 != 4) {
      dVar15 = (double)gnt4___assert_bl(dVar15,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,&DAT_80436068,0x586,
                                        s_clist_>type____HSD_TE_CNST_803adba4,in_r6,in_r7,in_r8,
                                        in_r9,in_r10);
    }
    in_r6 = (uint)*(byte *)((int)piVar3 + 0xe);
    if (in_r6 < 8) {
      uVar14 = uVar14 | 1 << in_r6;
      if (*(char *)(piVar3 + 3) == '\x01') {
        bVar9 = *(byte *)((int)piVar3 + 0xd);
        if (bVar9 == 1) {
LAB_802600c4:
          if (bVar9 == 2) {
LAB_80260144:
            pdVar6 = (double *)piVar3[2];
            uVar4 = (uint)(DOUBLE_8043d4f0 * *pdVar6);
            param_2 = (double)(longlong)(int)uVar4;
            uVar8 = (uint)(DOUBLE_8043d4f0 * pdVar6[1]);
            dVar15 = (double)(longlong)(int)uVar8;
            in_r7 = (uint)(DOUBLE_8043d4f0 * pdVar6[2]);
            local_28 = param_2;
            local_30 = dVar15;
            local_38 = (double)(longlong)(int)in_r7;
            param_3 = DOUBLE_8043d4f0;
          }
          else if (bVar9 < 2) {
            if (bVar9 == 0) goto LAB_80260144;
            puVar7 = (ushort *)piVar3[2];
            uVar4 = (uint)*puVar7;
            uVar8 = (uint)puVar7[1];
            in_r7 = (uint)puVar7[2];
          }
          else {
            if (3 < bVar9) goto LAB_80260144;
            pfVar5 = (float *)piVar3[2];
            param_3 = (double)FLOAT_8043d4e8;
            uVar4 = (uint)(param_3 * (double)*pfVar5);
            param_2 = (double)(longlong)(int)uVar4;
            uVar8 = (uint)(param_3 * (double)pfVar5[1]);
            dVar15 = (double)(longlong)(int)uVar8;
            in_r7 = (uint)(param_3 * (double)pfVar5[2]);
            local_38 = param_2;
            local_30 = dVar15;
            local_28 = (double)(longlong)(int)in_r7;
          }
          if ((int)uVar4 < 0x100) {
            bVar9 = (byte)uVar4 & ~(byte)((int)uVar4 >> 0x1f);
          }
          else {
            bVar9 = 0xff;
          }
          local_5c[in_r6 * 4] = bVar9;
          if ((int)uVar8 < 0x100) {
            bVar9 = (byte)uVar8 & ~(byte)((int)uVar8 >> 0x1f);
          }
          else {
            bVar9 = 0xff;
          }
          local_5c[(uint)*(byte *)((int)piVar3 + 0xe) * 4 + 1] = bVar9;
          if ((int)in_r7 < 0x100) {
            bVar9 = (byte)in_r7 & ~(byte)((int)in_r7 >> 0x1f);
          }
          else {
            bVar9 = 0xff;
          }
          local_5c[(uint)*(byte *)((int)piVar3 + 0xe) * 4 + 2] = bVar9;
        }
        else if (bVar9 == 0) {
          local_60 = CONCAT31((int3)((uint)*(undefined4 *)piVar3[2] >> 8),local_5c[in_r6 * 4 + 3]);
          *(undefined4 *)(local_5c + in_r6 * 4) = local_60;
        }
        else {
          if (2 < bVar9) goto LAB_802600c4;
          puVar10 = (uint *)piVar3[2];
          uVar4 = 0xff;
          if (*puVar10 < 0x100) {
            uVar4 = *puVar10;
          }
          uVar8 = puVar10[1];
          local_5c[in_r6 * 4] = (byte)uVar4;
          in_r6 = 0xff;
          if (uVar8 < 0x100) {
            in_r6 = uVar8;
          }
          in_r7 = puVar10[2];
          local_5c[(uint)*(byte *)((int)piVar3 + 0xe) * 4 + 1] = (byte)in_r6;
          uVar4 = 0xff;
          if (in_r7 < 0x100) {
            uVar4 = in_r7;
          }
          local_5c[(uint)*(byte *)((int)piVar3 + 0xe) * 4 + 2] = (byte)uVar4;
        }
      }
      else {
        bVar9 = *(byte *)((int)piVar3 + 0xd);
        if (bVar9 == 2) {
          in_r7 = *(uint *)piVar3[2];
          if ((int)in_r7 < 0x100) {
            in_r7 = in_r7 & ~((int)in_r7 >> 0x1f);
          }
          else {
            in_r7 = 0xff;
          }
          in_r7 = in_r7 & 0xff;
        }
        else if (bVar9 < 2) {
          if (bVar9 == 0) {
            in_r7 = (uint)*(byte *)piVar3[2];
          }
          else {
            in_r7 = (uint)*(ushort *)piVar3[2];
            if (0xff < in_r7) {
              in_r7 = 0xff;
            }
            in_r7 = in_r7 & 0xff;
          }
        }
        else if (bVar9 < 4) {
          dVar15 = (double)FLOAT_8043d4e8;
          in_r7 = (uint)(dVar15 * (double)*(float *)piVar3[2]);
          local_28 = (double)(longlong)(int)in_r7;
          if ((int)in_r7 < 0x100) {
            in_r7 = in_r7 & ~((int)in_r7 >> 0x1f);
          }
          else {
            in_r7 = 0xff;
          }
          in_r7 = in_r7 & 0xff;
        }
        else {
          in_r7 = (uint)(DOUBLE_8043d4f0 * *(double *)piVar3[2]);
          local_28 = (double)(longlong)(int)in_r7;
          if ((int)in_r7 < 0x100) {
            in_r7 = in_r7 & ~((int)in_r7 >> 0x1f);
          }
          else {
            in_r7 = 0xff;
          }
          in_r7 = in_r7 & 0xff;
          dVar15 = DOUBLE_8043d4f0;
        }
        bVar9 = (byte)in_r7;
        if (in_r6 < 4) {
          bVar1 = *(byte *)((int)piVar3 + 0xf);
          if (bVar1 == 1) {
            local_5c[in_r6 * 4 + 1] = bVar9;
          }
          else if (bVar1 == 0) {
            local_5c[in_r6 * 4] = bVar9;
          }
          else if (bVar1 < 3) {
            local_5c[in_r6 * 4 + 2] = bVar9;
          }
          else {
            local_5c[in_r6 * 4 + 3] = bVar9;
          }
        }
        else if (*(char *)((int)piVar3 + 0xf) == '\x03') {
          local_5c[in_r6 * 4 + 3] = bVar9;
        }
        else {
          iVar11 = (uint)*(byte *)((int)piVar3 + 0xe) * 4;
          local_5c[in_r6 * 4] = bVar9;
          local_5c[iVar11 + 1] = bVar9;
          local_5c[iVar11 + 2] = bVar9;
        }
      }
    }
    piVar3 = (int *)piVar3[1];
  } while( true );
}



// ==== 8026048c  gnt4-HSD_TExpSetupTev-bl ====

void gnt4_HSD_TExpSetupTev_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  undefined8 uVar3;
  
  uVar3 = gnt4_HSD_TExpSetReg_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar2 = extraout_r4;
  for (; param_9 != (undefined4 *)0x0; param_9 = (undefined4 *)*param_9) {
    iVar1 = 0;
    if (param_9[0x1d] != 0) {
      param_9[4] = *(undefined4 *)(param_9[0x1d] + 0xc);
      iVar1 = param_9[0x1d];
      param_9[3] = *(undefined4 *)(iVar1 + 0xa4);
    }
    gnt4_HSD_StateAssignTev_bl
              (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,uVar2,param_11,
               param_12,param_13,param_14,param_15,param_16);
    uVar3 = gnt4_HSD_SetupTevStage_bl((int)param_9);
    uVar2 = extraout_r4_00;
  }
  return;
}



// ==== 802604f8  gnt4-HSD_TExpCompile-bl ====

void gnt4_HSD_TExpCompile_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  undefined4 extraout_r4;
  undefined4 uVar6;
  undefined4 extraout_r4_00;
  int *piVar7;
  int iVar8;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 uVar9;
  int local_5d8 [12];
  int aiStack_5a8 [33];
  undefined1 auStack_524 [1316];
  
  uVar9 = gnt4__savegpr_25_bl();
  piVar4 = (int *)((ulonglong)uVar9 >> 0x20);
  piVar5 = (int *)uVar9;
  local_5d8[1] = 1;
  local_5d8[0] = 1;
  uVar9 = extraout_f1;
  if (piVar5 == (int *)0x0) {
    uVar9 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x650,&DAT_80436084,param_12,param_13,param_14,param_15,
                             param_16);
  }
  if (param_11 == (undefined4 *)0x0) {
    uVar9 = gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80436068,0x651,s_texp_list_803ad858,param_12,param_13,param_14,
                             param_15,param_16);
  }
  gnt4_memset(local_5d8 + 2,0,0x2c);
  if (piVar4 == (int *)0x0) {
    iVar1 = 0;
  }
  else if (piVar4 == (int *)0xffffffff) {
    iVar1 = 2;
  }
  else if (piVar4 == (int *)0xfffffffe) {
    iVar1 = 3;
  }
  else {
    iVar1 = *piVar4;
  }
  if (iVar1 == 4) {
    *(char *)(piVar4 + 4) = *(char *)(piVar4 + 4) + '\x01';
  }
  else if ((iVar1 < 4) && (iVar1 == 1)) {
    piVar4[2] = piVar4[2] + 1;
  }
  if (piVar4 == (int *)0x0) {
    iVar1 = 0;
  }
  else if (piVar4 == (int *)0xffffffff) {
    iVar1 = 2;
  }
  else if (piVar4 == (int *)0xfffffffe) {
    iVar1 = 3;
  }
  else {
    iVar1 = *piVar4;
  }
  if (iVar1 == 4) {
    *(char *)(piVar4 + 4) = *(char *)(piVar4 + 4) + '\x01';
  }
  else if ((iVar1 < 4) && (iVar1 == 1)) {
    piVar4[5] = piVar4[5] + 1;
  }
  gnt4_HSD_TExpSimplify_bl(piVar4);
  iVar1 = gnt4_HSD_TExpMakeDag_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  piVar4 = local_5d8 + 2;
  uVar9 = gnt4_HSD_TExpSchedule_bl(iVar1,auStack_524,aiStack_5a8 + 1,(int)piVar4);
  for (iVar8 = 0; iVar8 < iVar1; iVar8 = iVar8 + 1) {
    iVar3 = gnt4_TExpAssignReg_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    uVar9 = extraout_f1_00;
    if (iVar3 < 0) {
      uVar9 = gnt4___assert_bl(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,
                               param_8,&DAT_80436068,0x671,s_val_>__0_803adb34,piVar4,param_13,
                               param_14,param_15,param_16);
    }
  }
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    uVar9 = gnt4_HSD_TExpSimplify2_bl();
  }
  iVar1 = gnt4_HSD_TExpMakeDag_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  piVar4 = aiStack_5a8 + 1;
  piVar7 = local_5d8 + 2;
  uVar9 = gnt4_HSD_TExpSchedule_bl(iVar1,auStack_524,piVar4,(int)piVar7);
  *piVar5 = 0;
  uVar6 = extraout_r4;
  for (iVar8 = 0; iVar8 < iVar1; iVar8 = iVar8 + 1) {
    piVar2 = gnt4_hsdAllocMemPiece_bl
                       (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x78,uVar6,
                        piVar4,piVar7,param_13,param_14,param_15,param_16);
    iVar3 = gnt4_HSD_Index2TevStage_bl
                      (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,uVar6,
                       piVar4,piVar7,param_13,param_14,param_15,param_16);
    piVar2[2] = iVar3;
    piVar4 = local_5d8 + 1;
    piVar7 = local_5d8;
    uVar9 = gnt4_TExp2TevDesc_bl
                      (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       aiStack_5a8[iVar1 - iVar8],piVar2,piVar4,piVar7,param_13,param_14,param_15,
                       param_16);
    *piVar2 = *piVar5;
    *piVar5 = (int)piVar2;
    uVar6 = extraout_r4_00;
  }
  piVar4 = gnt4_HSD_TExpFreeList_bl
                     (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*param_11
                      ,1,(undefined *)0x1,piVar7,param_13,param_14,param_15,param_16);
  *param_11 = piVar4;
  piVar4 = gnt4_HSD_TExpFreeList_bl
                     (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*param_11
                      ,4,(undefined *)0x0,piVar7,param_13,param_14,param_15,param_16);
  *param_11 = piVar4;
  gnt4__restgpr_25_bl();
  return;
}



// ==== 802607a0  gnt4-HSD_TExpFreeTevDesc-bl ====

void gnt4_HSD_TExpFreeTevDesc_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  
  while (param_9 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*param_9;
    param_1 = gnt4_hsdFreeMemPiece_bl
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         0x78,param_11,param_12,param_13,param_14,param_15,param_16);
    param_9 = puVar1;
  }
  return;
}



// ==== 802607e0  gnt4-assign_reg-bl ====

void gnt4_assign_reg_bl(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  undefined4 local_28;
  undefined4 local_24;
  
  iVar2 = gnt4__savegpr_24_bl();
  iVar2 = iVar2 + -1;
  local_24 = DAT_8043d520;
  piVar9 = (int *)(param_4 + iVar2 * 4);
  iVar7 = 4;
  local_28 = DAT_8043d524;
  iVar6 = 4;
  do {
    if (iVar2 < 0) {
      gnt4__restgpr_24_bl();
      return;
    }
    iVar1 = *piVar9;
    iVar8 = 0;
    iVar10 = *(int *)(param_3 + iVar1 * 0x28);
    do {
      iVar3 = gnt4_HSD_TExpGetType_bl(*(undefined4 **)(iVar10 + 0x28));
      if (iVar3 == 1) {
        if (*(char *)(iVar10 + 0x25) == '\x01') {
          uVar5 = (uint)*(byte *)(*(int *)(iVar10 + 0x28) + 0xc);
          *(char *)((int)&local_24 + uVar5) = *(char *)((int)&local_24 + uVar5) + -1;
        }
        else {
          uVar5 = (uint)*(byte *)(*(int *)(iVar10 + 0x28) + 0x18);
          *(char *)((int)&local_28 + uVar5) = *(char *)((int)&local_28 + uVar5) + -1;
        }
      }
      iVar3 = gnt4_HSD_TExpGetType_bl(*(undefined4 **)(iVar10 + 0x48));
      if (iVar3 == 1) {
        uVar5 = (uint)*(byte *)(*(int *)(iVar10 + 0x48) + 0x18);
        *(char *)((int)&local_28 + uVar5) = *(char *)((int)&local_28 + uVar5) + -1;
      }
      iVar8 = iVar8 + 1;
      iVar10 = iVar10 + 8;
    } while (iVar8 < 4);
    iVar1 = *(int *)(param_3 + iVar1 * 0x28);
    if (0 < *(int *)(iVar1 + 8)) {
      pcVar4 = (char *)((int)&local_24 + 3);
      iVar8 = 3;
      iVar10 = 4;
      do {
        if (*pcVar4 == '\0') {
          *(char *)((int)&local_24 + iVar8) = (char)*(int *)(iVar1 + 8);
          *(char *)(iVar1 + 0xc) = (char)iVar8;
          if (iVar8 < iVar7) {
            iVar7 = iVar8;
          }
          break;
        }
        pcVar4 = pcVar4 + -1;
        iVar8 = iVar8 + -1;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
    }
    if (0 < *(int *)(iVar1 + 0x14)) {
      pcVar4 = (char *)((int)&local_28 + 3);
      iVar8 = 3;
      iVar10 = 4;
      do {
        if (*pcVar4 == '\0') {
          *(char *)((int)&local_28 + iVar8) = (char)*(int *)(iVar1 + 0x14);
          *(char *)(iVar1 + 0x18) = (char)iVar8;
          if (iVar8 < iVar6) {
            iVar6 = iVar8;
          }
          break;
        }
        pcVar4 = pcVar4 + -1;
        iVar8 = iVar8 + -1;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
    }
    piVar9 = piVar9 + -1;
    iVar2 = iVar2 + -1;
  } while( true );
}



// ==== 80260990  gnt4-order_dag-bl ====

void gnt4_order_dag_bl(undefined4 param_1,undefined4 param_2,uint *param_3,int param_4,int param_5,
                      uint param_6,uint param_7,uint param_8,undefined4 *param_9,int *param_10,
                      undefined4 *param_11)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  longlong lVar15;
  
  lVar15 = gnt4__savegpr_20_bl();
  iVar3 = (int)((ulonglong)lVar15 >> 0x20);
  iVar4 = (int)lVar15;
  iVar12 = param_5 + 1;
  param_9[param_5] = param_6 & 0xff;
  uVar13 = param_7 | 1 << param_6;
  if (iVar12 == iVar3) {
    iVar4 = gnt4_assign_reg_bl(iVar3,iVar4,param_4,(int)param_9);
    if (iVar4 < *param_10) {
      *param_10 = iVar4;
      iVar4 = 0;
      if (0xffffffff < lVar15) {
        if ((0x8ffffffff < lVar15) &&
           (uVar13 = iVar3 - 1U >> 3, puVar5 = param_9, puVar7 = param_11, 0 < iVar3 + -8)) {
          do {
            iVar4 = iVar4 + 8;
            *puVar7 = *puVar5;
            puVar7[1] = puVar5[1];
            puVar7[2] = puVar5[2];
            puVar7[3] = puVar5[3];
            puVar7[4] = puVar5[4];
            puVar7[5] = puVar5[5];
            puVar7[6] = puVar5[6];
            puVar1 = puVar5 + 7;
            puVar5 = puVar5 + 8;
            puVar7[7] = *puVar1;
            puVar7 = puVar7 + 8;
            uVar13 = uVar13 - 1;
          } while (uVar13 != 0);
        }
        iVar12 = iVar3 - iVar4;
        puVar5 = param_9 + iVar4;
        puVar7 = param_11 + iVar4;
        if (iVar4 < iVar3) {
          do {
            uVar2 = *puVar5;
            puVar5 = puVar5 + 1;
            *puVar7 = uVar2;
            puVar7 = puVar7 + 1;
            iVar12 = iVar12 + -1;
          } while (iVar12 != 0);
        }
      }
    }
  }
  else {
    uVar8 = *(uint *)(iVar4 + param_6 * 4);
    uVar11 = 0;
    iVar9 = 0;
    uVar10 = param_8 & ~(1 << param_6) | uVar8;
    puVar6 = param_3;
    iVar14 = iVar3;
    if (0xffffffff < lVar15) {
      do {
        if ((uVar10 & 1 << iVar9) != 0) {
          uVar11 = uVar11 | *puVar6;
        }
        puVar6 = puVar6 + 1;
        iVar9 = iVar9 + 1;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
    }
    uVar10 = uVar10 & ~uVar11;
    iVar14 = param_4 + param_6 * 0x28;
    if ((*(char *)(iVar14 + 5) == '\x01') && ((uVar10 & uVar8) != 0)) {
      gnt4_order_dag_bl(iVar3,iVar4,param_3,param_4,iVar12,(uint)*(byte *)(*(int *)(iVar14 + 8) + 4)
                        ,uVar13,uVar10,param_9,param_10,param_11);
    }
    else {
      for (uVar8 = 0; (int)uVar8 < iVar3; uVar8 = uVar8 + 1) {
        if ((uVar10 & 1 << uVar8) != 0) {
          gnt4_order_dag_bl(iVar3,iVar4,param_3,param_4,iVar12,uVar8,uVar13,uVar10,param_9,param_10,
                            param_11);
        }
      }
    }
  }
  gnt4__restgpr_20_bl();
  return;
}



// ==== 80260bc8  gnt4-CalcDistance-bl ====

void gnt4_CalcDistance_bl(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  
  uVar10 = gnt4__savegpr_22_bl();
  piVar1 = (int *)((ulonglong)uVar10 >> 0x20);
  iVar3 = (int)uVar10;
  iVar4 = 0;
  piVar2 = piVar1;
  iVar8 = param_4;
  if (0 < param_4) {
    do {
      if (*piVar2 == param_3) {
        if (*(int *)(iVar3 + iVar4 * 4) < param_5) {
          *(int *)(iVar3 + iVar4 * 4) = param_5;
          iVar8 = 0;
          do {
            if (*(char *)(param_3 + 0x24) == '\x01') {
              iVar9 = *(int *)(param_3 + 0x28);
              iVar5 = 0;
              piVar2 = piVar1;
              iVar4 = param_4;
              if (0 < param_4) {
                do {
                  if (*piVar2 == iVar9) {
                    if (*(int *)(iVar3 + iVar5 * 4) < param_5 + 1) {
                      *(int *)(iVar3 + iVar5 * 4) = param_5 + 1;
                      iVar4 = 0;
                      do {
                        if (*(char *)(iVar9 + 0x24) == '\x01') {
                          iVar7 = *(int *)(iVar9 + 0x28);
                          iVar6 = 0;
                          piVar2 = piVar1;
                          iVar5 = param_4;
                          if (0 < param_4) {
                            do {
                              if (*piVar2 == iVar7) {
                                if (*(int *)(iVar3 + iVar6 * 4) < param_5 + 2) {
                                  *(int *)(iVar3 + iVar6 * 4) = param_5 + 2;
                                  iVar5 = 0;
                                  do {
                                    if (*(char *)(iVar7 + 0x24) == '\x01') {
                                      gnt4_CalcDistance_bl
                                                (piVar1,iVar3,*(int *)(iVar7 + 0x28),param_4,
                                                 param_5 + 3);
                                    }
                                    if (*(char *)(iVar7 + 0x44) == '\x01') {
                                      gnt4_CalcDistance_bl
                                                (piVar1,iVar3,*(int *)(iVar7 + 0x48),param_4,
                                                 param_5 + 3);
                                    }
                                    iVar5 = iVar5 + 1;
                                    iVar7 = iVar7 + 8;
                                  } while (iVar5 < 4);
                                }
                                break;
                              }
                              piVar2 = piVar2 + 1;
                              iVar6 = iVar6 + 1;
                              iVar5 = iVar5 + -1;
                            } while (iVar5 != 0);
                          }
                        }
                        if (*(char *)(iVar9 + 0x44) == '\x01') {
                          iVar7 = *(int *)(iVar9 + 0x48);
                          iVar6 = 0;
                          piVar2 = piVar1;
                          iVar5 = param_4;
                          if (0 < param_4) {
                            do {
                              if (*piVar2 == iVar7) {
                                if (*(int *)(iVar3 + iVar6 * 4) < param_5 + 2) {
                                  *(int *)(iVar3 + iVar6 * 4) = param_5 + 2;
                                  iVar5 = 0;
                                  do {
                                    if (*(char *)(iVar7 + 0x24) == '\x01') {
                                      gnt4_CalcDistance_bl
                                                (piVar1,iVar3,*(int *)(iVar7 + 0x28),param_4,
                                                 param_5 + 3);
                                    }
                                    if (*(char *)(iVar7 + 0x44) == '\x01') {
                                      gnt4_CalcDistance_bl
                                                (piVar1,iVar3,*(int *)(iVar7 + 0x48),param_4,
                                                 param_5 + 3);
                                    }
                                    iVar5 = iVar5 + 1;
                                    iVar7 = iVar7 + 8;
                                  } while (iVar5 < 4);
                                }
                                break;
                              }
                              piVar2 = piVar2 + 1;
                              iVar6 = iVar6 + 1;
                              iVar5 = iVar5 + -1;
                            } while (iVar5 != 0);
                          }
                        }
                        iVar4 = iVar4 + 1;
                        iVar9 = iVar9 + 8;
                      } while (iVar4 < 4);
                    }
                    break;
                  }
                  piVar2 = piVar2 + 1;
                  iVar5 = iVar5 + 1;
                  iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
              }
            }
            if (*(char *)(param_3 + 0x44) == '\x01') {
              iVar9 = *(int *)(param_3 + 0x48);
              iVar5 = 0;
              piVar2 = piVar1;
              iVar4 = param_4;
              if (0 < param_4) {
                do {
                  if (*piVar2 == iVar9) {
                    if (*(int *)(iVar3 + iVar5 * 4) < param_5 + 1) {
                      *(int *)(iVar3 + iVar5 * 4) = param_5 + 1;
                      iVar4 = 0;
                      do {
                        if (*(char *)(iVar9 + 0x24) == '\x01') {
                          iVar7 = *(int *)(iVar9 + 0x28);
                          iVar6 = 0;
                          piVar2 = piVar1;
                          iVar5 = param_4;
                          if (0 < param_4) {
                            do {
                              if (*piVar2 == iVar7) {
                                if (*(int *)(iVar3 + iVar6 * 4) < param_5 + 2) {
                                  *(int *)(iVar3 + iVar6 * 4) = param_5 + 2;
                                  iVar5 = 0;
                                  do {
                                    if (*(char *)(iVar7 + 0x24) == '\x01') {
                                      gnt4_CalcDistance_bl
                                                (piVar1,iVar3,*(int *)(iVar7 + 0x28),param_4,
                                                 param_5 + 3);
                                    }
                                    if (*(char *)(iVar7 + 0x44) == '\x01') {
                                      gnt4_CalcDistance_bl
                                                (piVar1,iVar3,*(int *)(iVar7 + 0x48),param_4,
                                                 param_5 + 3);
                                    }
                                    iVar5 = iVar5 + 1;
                                    iVar7 = iVar7 + 8;
                                  } while (iVar5 < 4);
                                }
                                break;
                              }
                              piVar2 = piVar2 + 1;
                              iVar6 = iVar6 + 1;
                              iVar5 = iVar5 + -1;
                            } while (iVar5 != 0);
                          }
                        }
                        if (*(char *)(iVar9 + 0x44) == '\x01') {
                          iVar7 = *(int *)(iVar9 + 0x48);
                          iVar6 = 0;
                          piVar2 = piVar1;
                          iVar5 = param_4;
                          if (0 < param_4) {
                            do {
                              if (*piVar2 == iVar7) {
                                if (*(int *)(iVar3 + iVar6 * 4) < param_5 + 2) {
                                  *(int *)(iVar3 + iVar6 * 4) = param_5 + 2;
                                  iVar5 = 0;
                                  do {
                                    if (*(char *)(iVar7 + 0x24) == '\x01') {
                                      gnt4_CalcDistance_bl
                                                (piVar1,iVar3,*(int *)(iVar7 + 0x28),param_4,
                                                 param_5 + 3);
                                    }
                                    if (*(char *)(iVar7 + 0x44) == '\x01') {
                                      gnt4_CalcDistance_bl
                                                (piVar1,iVar3,*(int *)(iVar7 + 0x48),param_4,
                                                 param_5 + 3);
                                    }
                                    iVar5 = iVar5 + 1;
                                    iVar7 = iVar7 + 8;
                                  } while (iVar5 < 4);
                                }
                                break;
                              }
                              piVar2 = piVar2 + 1;
                              iVar6 = iVar6 + 1;
                              iVar5 = iVar5 + -1;
                            } while (iVar5 != 0);
                          }
                        }
                        iVar4 = iVar4 + 1;
                        iVar9 = iVar9 + 8;
                      } while (iVar4 < 4);
                    }
                    break;
                  }
                  piVar2 = piVar2 + 1;
                  iVar5 = iVar5 + 1;
                  iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
              }
            }
            iVar8 = iVar8 + 1;
            param_3 = param_3 + 8;
          } while (iVar8 < 4);
        }
        break;
      }
      piVar2 = piVar2 + 1;
      iVar4 = iVar4 + 1;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  gnt4__restgpr_22_bl();
  return;
}



// ==== 80261000  gnt4-HSD_TExpMakeDag-bl ====

void gnt4_HSD_TExpMakeDag_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  undefined4 **ppuVar10;
  int iVar11;
  undefined4 *in_r6;
  undefined4 **ppuVar12;
  int in_r7;
  int in_r8;
  undefined4 *in_r9;
  undefined4 in_r10;
  undefined4 *puVar13;
  undefined4 **ppuVar14;
  int iVar15;
  int iVar16;
  undefined4 *puVar17;
  undefined4 **ppuVar18;
  uint uVar19;
  undefined8 extraout_f1;
  undefined8 uVar20;
  int local_128 [32];
  undefined4 *local_a8 [42];
  
  uVar20 = gnt4__savegpr_22_bl();
  puVar17 = (undefined4 *)((ulonglong)uVar20 >> 0x20);
  iVar7 = (int)uVar20;
  uVar20 = extraout_f1;
  iVar4 = gnt4_HSD_TExpGetType_bl(puVar17);
  if (iVar4 != 1) {
    uVar20 = gnt4___assert_bl(uVar20,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_texpdag_c_803adbc0,0xee,s_HSD_TExpGetType_root_____HSD_TE__803adbcc,
                              in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  local_a8[0] = puVar17;
  ppuVar14 = (undefined4 **)0x1;
  ppuVar12 = local_a8;
  for (iVar4 = 0; iVar4 < (int)ppuVar14; iVar4 = iVar4 + 1) {
    if (0x1f < iVar4) {
      uVar20 = gnt4___assert_bl(uVar20,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                s_texpdag_c_803adbc0,0xf6,s_j<HSD_TEXP_MAX_NUM_803adbf0,in_r6,in_r7,
                                in_r8,in_r9,in_r10);
    }
    in_r9 = *ppuVar12;
    iVar2 = (int)ppuVar14 << 2;
    iVar16 = 0;
    puVar17 = in_r9;
    do {
      if (*(char *)(puVar17 + 9) == '\x01') {
        in_r8 = 0;
        ppuVar10 = local_a8;
        ppuVar18 = ppuVar14;
        if (0 < (int)ppuVar14) {
          do {
            if (*ppuVar10 == (undefined4 *)puVar17[10]) break;
            ppuVar10 = ppuVar10 + 1;
            in_r8 = in_r8 + 1;
            ppuVar18 = (undefined4 **)((int)ppuVar18 + -1);
          } while (ppuVar18 != (undefined4 **)0x0);
        }
        if ((int)ppuVar14 <= in_r8) {
          ppuVar14 = (undefined4 **)((int)ppuVar14 + 1);
          *(undefined4 *)((int)local_a8 + iVar2) = puVar17[10];
          iVar2 = iVar2 + 4;
        }
      }
      iVar16 = iVar16 + 1;
      puVar17 = puVar17 + 2;
    } while (iVar16 < 4);
    iVar2 = (int)ppuVar14 << 2;
    in_r7 = 0;
    in_r6 = in_r9;
    do {
      if (*(char *)(in_r6 + 0x11) == '\x01') {
        in_r8 = 0;
        ppuVar10 = local_a8;
        ppuVar18 = ppuVar14;
        if (0 < (int)ppuVar14) {
          do {
            if (*ppuVar10 == (undefined4 *)in_r6[0x12]) break;
            ppuVar10 = ppuVar10 + 1;
            in_r8 = in_r8 + 1;
            ppuVar18 = (undefined4 **)((int)ppuVar18 + -1);
          } while (ppuVar18 != (undefined4 **)0x0);
        }
        if ((int)ppuVar14 <= in_r8) {
          ppuVar14 = (undefined4 **)((int)ppuVar14 + 1);
          *(undefined4 *)((int)local_a8 + iVar2) = in_r6[0x12];
          iVar2 = iVar2 + 4;
        }
      }
      in_r7 = in_r7 + 1;
      in_r6 = in_r6 + 2;
    } while (in_r7 < 4);
    ppuVar12 = ppuVar12 + 1;
  }
  iVar4 = 0;
  if (0 < (int)ppuVar14) {
    if (8 < (int)ppuVar14) {
      piVar9 = local_128;
      uVar19 = (int)ppuVar14 - 1U >> 3;
      if (0 < (int)(ppuVar14 + -2)) {
        do {
          *piVar9 = -1;
          iVar4 = iVar4 + 8;
          piVar9[1] = -1;
          piVar9[2] = -1;
          piVar9[3] = -1;
          piVar9[4] = -1;
          piVar9[5] = -1;
          piVar9[6] = -1;
          piVar9[7] = -1;
          piVar9 = piVar9 + 8;
          uVar19 = uVar19 - 1;
        } while (uVar19 != 0);
      }
    }
    iVar2 = (int)ppuVar14 - iVar4;
    piVar9 = local_128 + iVar4;
    if (iVar4 < (int)ppuVar14) {
      do {
        *piVar9 = -1;
        piVar9 = piVar9 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  ppuVar12 = ppuVar14;
  uVar20 = gnt4_CalcDistance_bl(local_a8,local_128,(int)local_a8[0],(int)ppuVar14,0);
  for (iVar4 = 0; iVar4 < (int)ppuVar14; iVar4 = iVar4 + 1) {
    in_r8 = iVar4 + 1;
    iVar2 = (int)ppuVar14 - in_r8;
    piVar9 = local_128 + in_r8;
    ppuVar12 = local_a8 + in_r8;
    if (in_r8 < (int)ppuVar14) {
      do {
        iVar16 = piVar9[-1];
        if (*piVar9 < iVar16) {
          in_r9 = ppuVar12[-1];
          puVar17 = *ppuVar12;
          piVar9[-1] = *piVar9;
          ppuVar12[-1] = puVar17;
          *ppuVar12 = in_r9;
          *piVar9 = iVar16;
        }
        piVar9 = piVar9 + 1;
        ppuVar12 = ppuVar12 + 1;
        in_r8 = in_r8 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  iVar16 = (int)ppuVar14 + -1;
  iVar2 = iVar16 * 4;
  ppuVar10 = local_a8 + iVar16;
  puVar17 = (undefined4 *)(iVar7 + iVar16 * 0x28);
LAB_8026148c:
  if (iVar16 < 0) {
    gnt4__restgpr_22_bl();
    return;
  }
  puVar13 = *ppuVar10;
  iVar15 = 0;
  *(char *)(puVar17 + 1) = (char)iVar16;
  *(undefined1 *)((int)puVar17 + 6) = 0;
  *(undefined1 *)((int)puVar17 + 5) = 0;
  *puVar17 = puVar13;
  puVar6 = puVar13;
LAB_802612cc:
  if (*(char *)(puVar6 + 9) == '\x01') {
    iVar3 = (int)ppuVar14 - iVar16;
    piVar9 = (int *)((int)local_a8 + iVar2);
    iVar11 = iVar16;
    if (iVar16 < (int)ppuVar14) {
      do {
        if (puVar6[10] == *piVar9) {
          iVar3 = iVar11 * 0x28;
          uVar8 = (uint)*(byte *)((int)puVar17 + 5);
          iVar11 = 0;
          ppuVar12 = (undefined4 **)(iVar7 + iVar3);
          puVar5 = puVar17;
          uVar19 = uVar8;
          if (uVar8 != 0) goto LAB_80261324;
          goto LAB_8026133c;
        }
        piVar9 = piVar9 + 1;
        iVar11 = iVar11 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    goto LAB_80261378;
  }
  goto LAB_80261390;
  while( true ) {
    puVar5 = puVar5 + 1;
    iVar11 = iVar11 + 1;
    uVar19 = uVar19 - 1;
    if (uVar19 == 0) break;
LAB_80261324:
    if ((undefined4 **)puVar5[2] == ppuVar12) break;
  }
LAB_8026133c:
  if ((int)uVar8 <= iVar11) {
    bVar1 = *(byte *)((int)puVar17 + 5);
    *(byte *)((int)puVar17 + 5) = bVar1 + 1;
    puVar17[bVar1 + 2] = ppuVar12;
    *(char *)((int)ppuVar12 + 6) = *(char *)((int)ppuVar12 + 6) + '\x01';
  }
LAB_80261378:
  if ((int)ppuVar14 <= iVar11) {
    uVar20 = gnt4___assert_bl(uVar20,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_texpdag_c_803adbc0,0x145,&DAT_80436090,ppuVar12,iVar4,in_r8,in_r9,
                              in_r10);
  }
LAB_80261390:
  iVar15 = iVar15 + 1;
  puVar6 = puVar6 + 2;
  if (3 < iVar15) goto code_r0x802613a0;
  goto LAB_802612cc;
code_r0x802613a0:
  iVar15 = 0;
LAB_802613a8:
  if (*(char *)(puVar13 + 0x11) == '\x01') {
    iVar3 = (int)ppuVar14 - iVar16;
    piVar9 = (int *)((int)local_a8 + iVar2);
    iVar11 = iVar16;
    if (iVar16 < (int)ppuVar14) {
      do {
        if (puVar13[0x12] == *piVar9) {
          iVar3 = iVar11 * 0x28;
          uVar8 = (uint)*(byte *)((int)puVar17 + 5);
          iVar11 = 0;
          ppuVar12 = (undefined4 **)(iVar7 + iVar3);
          puVar6 = puVar17;
          uVar19 = uVar8;
          if (uVar8 != 0) goto LAB_80261400;
          goto LAB_80261418;
        }
        piVar9 = piVar9 + 1;
        iVar11 = iVar11 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    goto LAB_80261454;
  }
  goto LAB_8026146c;
  while( true ) {
    puVar6 = puVar6 + 1;
    iVar11 = iVar11 + 1;
    uVar19 = uVar19 - 1;
    if (uVar19 == 0) break;
LAB_80261400:
    if ((undefined4 **)puVar6[2] == ppuVar12) break;
  }
LAB_80261418:
  if ((int)uVar8 <= iVar11) {
    bVar1 = *(byte *)((int)puVar17 + 5);
    *(byte *)((int)puVar17 + 5) = bVar1 + 1;
    puVar17[bVar1 + 2] = ppuVar12;
    *(char *)((int)ppuVar12 + 6) = *(char *)((int)ppuVar12 + 6) + '\x01';
  }
LAB_80261454:
  if ((int)ppuVar14 <= iVar11) {
    uVar20 = gnt4___assert_bl(uVar20,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_texpdag_c_803adbc0,0x15b,&DAT_80436090,ppuVar12,iVar4,in_r8,in_r9,
                              in_r10);
  }
LAB_8026146c:
  iVar15 = iVar15 + 1;
  puVar13 = puVar13 + 2;
  if (3 < iVar15) goto code_r0x8026147c;
  goto LAB_802613a8;
code_r0x8026147c:
  puVar17 = puVar17 + -10;
  ppuVar10 = ppuVar10 + -1;
  iVar16 = iVar16 + -1;
  iVar2 = iVar2 + -4;
  goto LAB_8026148c;
}



// ==== 802614b0  gnt4-HSD_TExpSchedule-bl ====

void gnt4_HSD_TExpSchedule_bl(undefined4 param_1,undefined4 param_2,int *param_3,int param_4)

{
  bool bVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  longlong lVar14;
  int local_238;
  int local_234 [32];
  undefined4 auStack_1b4 [32];
  uint local_134 [32];
  uint local_b4 [45];
  
  lVar14 = gnt4__savegpr_22_bl();
  iVar4 = (int)((ulonglong)lVar14 >> 0x20);
  local_238 = 5;
  gnt4_memset(local_234,0,0x80);
  puVar5 = local_b4;
  puVar6 = puVar5;
  lVar2 = lVar14;
  if (0xffffffff < lVar14) {
    do {
      iVar11 = (int)lVar2;
      *puVar6 = 0;
      iVar12 = iVar11;
      for (iVar9 = 0; iVar9 < (int)(uint)*(byte *)(iVar11 + 5); iVar9 = iVar9 + 1) {
        piVar10 = (int *)(iVar12 + 8);
        iVar12 = iVar12 + 4;
        *puVar6 = *puVar6 | 1 << (uint)*(byte *)(*piVar10 + 4);
      }
      puVar6 = puVar6 + 1;
      iVar12 = (int)((ulonglong)lVar2 >> 0x20) + -1;
      lVar2 = CONCAT44(iVar12,iVar11 + 0x28);
    } while (iVar12 != 0);
  }
  iVar12 = 0;
  if (0xffffffff < lVar14) {
    if (0x8ffffffff < lVar14) {
      puVar6 = local_134;
      uVar13 = iVar4 - 1U >> 3;
      if (0 < iVar4 + -8) {
        do {
          iVar12 = iVar12 + 8;
          uVar3 = puVar5[1];
          *puVar6 = *puVar5;
          uVar8 = puVar5[2];
          puVar6[1] = uVar3;
          uVar3 = puVar5[3];
          puVar6[2] = uVar8;
          uVar8 = puVar5[4];
          puVar6[3] = uVar3;
          uVar3 = puVar5[5];
          puVar6[4] = uVar8;
          uVar8 = puVar5[6];
          puVar6[5] = uVar3;
          uVar3 = puVar5[7];
          puVar5 = puVar5 + 8;
          puVar6[6] = uVar8;
          puVar6[7] = uVar3;
          puVar6 = puVar6 + 8;
          uVar13 = uVar13 - 1;
        } while (uVar13 != 0);
      }
    }
    iVar9 = iVar4 - iVar12;
    puVar6 = local_b4 + iVar12;
    puVar5 = local_134 + iVar12;
    if (iVar12 < iVar4) {
      do {
        uVar13 = *puVar6;
        puVar6 = puVar6 + 1;
        *puVar5 = uVar13;
        puVar5 = puVar5 + 1;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
    }
  }
  do {
    bVar1 = false;
    puVar6 = local_134;
    for (iVar12 = 0; iVar12 < iVar4; iVar12 = iVar12 + 1) {
      uVar13 = *puVar6;
      puVar5 = local_134;
      iVar9 = iVar4;
      if (0xffffffff < lVar14) {
        do {
          uVar3 = *puVar5;
          if ((1 << iVar12 & uVar3) != 0) {
            *puVar5 = uVar3 | uVar13;
            if (uVar3 != *puVar5) {
              bVar1 = true;
            }
          }
          puVar5 = puVar5 + 1;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
      puVar6 = puVar6 + 1;
    }
  } while (bVar1);
  gnt4_order_dag_bl(iVar4,local_b4,local_134,(int)lVar14,0,0,0,0,auStack_1b4,&local_238,local_234);
  piVar10 = local_234;
  for (iVar12 = 0; iVar12 < iVar4; iVar12 = iVar12 + 1) {
    *param_3 = *(int *)((int)lVar14 + *piVar10 * 0x28);
    if (*(byte *)(*param_3 + 0xc) != 0xff) {
      iVar9 = 0;
      *(undefined1 *)(param_4 + (uint)*(byte *)(*param_3 + 0xc) * 2 + 0x14) = 3;
      iVar11 = 0;
      do {
        iVar7 = gnt4_HSD_TExpGetType_bl(*(undefined4 **)(*param_3 + iVar11 + 0x28));
        if (iVar7 == 1) {
          iVar7 = *param_3 + iVar11;
          if (*(char *)(iVar7 + 0x25) == '\x01') {
            *(char *)(iVar7 + 0x26) =
                 (char)*(undefined4 *)
                        (&DAT_803adc04 + (uint)*(byte *)(*(int *)(iVar7 + 0x28) + 0xc) * 4);
          }
          else {
            *(char *)(iVar7 + 0x26) =
                 (char)*(undefined4 *)
                        (&DAT_803adc14 + (uint)*(byte *)(*(int *)(iVar7 + 0x28) + 0x18) * 4);
          }
        }
        iVar9 = iVar9 + 1;
        iVar11 = iVar11 + 8;
      } while (iVar9 < 4);
    }
    if (*(byte *)(*param_3 + 0x18) != 0xff) {
      iVar11 = 0;
      *(undefined1 *)(param_4 + (uint)*(byte *)(*param_3 + 0x18) * 2 + 0x15) = 1;
      iVar9 = 0;
      do {
        iVar7 = gnt4_HSD_TExpGetType_bl(*(undefined4 **)(*param_3 + iVar9 + 0x48));
        if (iVar7 == 1) {
          *(char *)(*param_3 + iVar9 + 0x46) =
               (char)*(undefined4 *)
                      (&DAT_803adc24 + (uint)*(byte *)(*(int *)(*param_3 + iVar9 + 0x48) + 0x18) * 4
                      );
        }
        iVar11 = iVar11 + 1;
        iVar9 = iVar9 + 8;
      } while (iVar11 < 4);
    }
    piVar10 = piVar10 + 1;
    param_3 = param_3 + 1;
  }
  gnt4__restgpr_22_bl();
  return;
}



// ==== 80261818  gnt4-SimplifySrc-bl ====

void gnt4_SimplifySrc_bl(void)

{
  char cVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  
  iVar4 = gnt4__savegpr_26_bl();
  iVar6 = 0;
  iVar7 = iVar4;
  do {
    if (*(char *)(iVar7 + 0x24) == '\x01') {
      puVar5 = *(undefined4 **)(iVar7 + 0x28);
      cVar1 = *(char *)(iVar7 + 0x25);
      gnt4_HSD_TExpSimplify_bl(puVar5);
      if (cVar1 == '\x01') {
        cVar1 = *(char *)((int)puVar5 + 0xd);
        if (cVar1 == -1) {
          gnt4_HSD_TExpUnref_bl();
          uVar3 = DAT_8043609c;
          *(undefined4 *)(iVar7 + 0x24) = DAT_80436098;
          *(undefined4 *)(iVar7 + 0x28) = uVar3;
        }
        else if ((((cVar1 != -1) && (cVar1 == '\0')) && (*(char *)((int)puVar5 + 0x25) == '\a')) &&
                (((*(char *)((int)puVar5 + 0x2d) == '\a' && (*(char *)((int)puVar5 + 0xf) == '\0'))
                 && (*(char *)(puVar5 + 4) == '\0')))) {
          bVar2 = *(byte *)(puVar5 + 0xf);
          if (bVar2 == 3) {
            if (((*(char *)(iVar4 + 0x68) == -1) ||
                (*(char *)(iVar4 + 0x68) == *(char *)(puVar5 + 0x1a))) &&
               ((*(char *)(iVar4 + 0x1f) == -1 ||
                ((*(char *)((int)puVar5 + 0x1f) == -1 ||
                 (*(char *)(iVar4 + 0x1f) == *(char *)((int)puVar5 + 0x1f))))))) {
              uVar3 = puVar5[0x10];
              *(undefined4 *)(iVar7 + 0x24) = puVar5[0xf];
              *(undefined4 *)(iVar7 + 0x28) = uVar3;
              *(undefined1 *)(iVar4 + 0x68) = *(undefined1 *)(puVar5 + 0x1a);
              if (*(char *)(iVar4 + 0x1f) == -1) {
                *(undefined1 *)(iVar4 + 0x1f) = *(undefined1 *)((int)puVar5 + 0x1f);
              }
              gnt4_HSD_TExpUnref_bl();
            }
          }
          else if (bVar2 < 3) {
            if (bVar2 == 1) {
              if (((iVar6 != 3) || (*(char *)((int)puVar5 + 0xe) == '\0')) ||
                 (*(char *)((int)puVar5 + 0x11) != '\x01')) {
                uVar3 = puVar5[0x10];
                *(undefined4 *)(iVar7 + 0x24) = puVar5[0xf];
                *(undefined4 *)(iVar7 + 0x28) = uVar3;
                gnt4_HSD_TExpRef_bl(*(int **)(iVar7 + 0x28),*(char *)(iVar7 + 0x25));
                gnt4_HSD_TExpUnref_bl();
              }
            }
            else if (((bVar2 != 0) &&
                     ((*(int *)(iVar4 + 100) == 0 || (*(int *)(iVar4 + 100) == puVar5[0x19])))) &&
                    ((*(char *)(iVar4 + 0x1e) == -1 ||
                     ((*(char *)((int)puVar5 + 0x1e) == -1 ||
                      (*(char *)(iVar4 + 0x1e) == *(char *)((int)puVar5 + 0x1e))))))) {
              uVar3 = puVar5[0x10];
              *(undefined4 *)(iVar7 + 0x24) = puVar5[0xf];
              *(undefined4 *)(iVar7 + 0x28) = uVar3;
              *(undefined4 *)(iVar4 + 100) = puVar5[0x19];
              if (*(char *)(iVar4 + 0x1e) == -1) {
                *(undefined1 *)(iVar4 + 0x1e) = *(undefined1 *)((int)puVar5 + 0x1e);
              }
              gnt4_HSD_TExpUnref_bl();
            }
          }
          else if (bVar2 == 5) {
            uVar3 = puVar5[0x10];
            *(undefined4 *)(iVar7 + 0x24) = puVar5[0xf];
            *(undefined4 *)(iVar7 + 0x28) = uVar3;
            gnt4_HSD_TExpRef_bl(*(int **)(iVar7 + 0x28),*(char *)(iVar7 + 0x25));
            gnt4_HSD_TExpUnref_bl();
          }
        }
      }
      else if (*(char *)((int)puVar5 + 0x19) == -1) {
        gnt4_HSD_TExpUnref_bl();
        uVar3 = DAT_8043609c;
        *(undefined4 *)(iVar7 + 0x24) = DAT_80436098;
        *(undefined4 *)(iVar7 + 0x28) = uVar3;
      }
    }
    iVar6 = iVar6 + 1;
    iVar7 = iVar7 + 8;
  } while (iVar6 < 4);
  iVar6 = 0;
  iVar7 = iVar4;
  do {
    if (*(char *)(iVar7 + 0x44) == '\x01') {
      puVar5 = *(undefined4 **)(iVar7 + 0x48);
      gnt4_HSD_TExpSimplify_bl(puVar5);
      cVar1 = *(char *)((int)puVar5 + 0x19);
      if (cVar1 == -1) {
        gnt4_HSD_TExpUnref_bl();
        uVar3 = DAT_8043609c;
        *(undefined4 *)(iVar7 + 0x44) = DAT_80436098;
        *(undefined4 *)(iVar7 + 0x48) = uVar3;
      }
      else if (((((cVar1 != -1) && (cVar1 == '\0')) && (*(char *)((int)puVar5 + 0x45) == '\a')) &&
               ((*(char *)((int)puVar5 + 0x4d) == '\a' && (*(char *)((int)puVar5 + 0x1b) == '\0'))))
              && (*(char *)(puVar5 + 7) == '\0')) {
        bVar2 = *(byte *)(puVar5 + 0x17);
        if (bVar2 == 3) {
          if ((*(char *)(iVar4 + 0x68) == -1) ||
             (*(char *)(iVar4 + 0x68) == *(char *)(puVar5 + 0x1a))) {
            uVar3 = puVar5[0x18];
            *(undefined4 *)(iVar7 + 0x44) = puVar5[0x17];
            *(undefined4 *)(iVar7 + 0x48) = uVar3;
            *(undefined1 *)(iVar4 + 0x68) = *(undefined1 *)(puVar5 + 0x1a);
            gnt4_HSD_TExpUnref_bl();
          }
        }
        else if (bVar2 < 3) {
          if (bVar2 == 1) {
LAB_80261bb0:
            if (((iVar6 != 3) || (*(char *)((int)puVar5 + 0x1a) == '\0')) ||
               (*(char *)((int)puVar5 + 0x1d) != '\x01')) {
              uVar3 = puVar5[0x18];
              *(undefined4 *)(iVar7 + 0x44) = puVar5[0x17];
              *(undefined4 *)(iVar7 + 0x48) = uVar3;
              gnt4_HSD_TExpRef_bl(*(int **)(iVar7 + 0x48),*(char *)(iVar7 + 0x45));
              gnt4_HSD_TExpUnref_bl();
            }
          }
          else if ((bVar2 != 0) &&
                  ((*(int *)(iVar4 + 100) == 0 || (*(int *)(iVar4 + 100) == puVar5[0x19])))) {
            uVar3 = puVar5[0x18];
            *(undefined4 *)(iVar7 + 0x44) = puVar5[0x17];
            *(undefined4 *)(iVar7 + 0x48) = uVar3;
            *(undefined4 *)(iVar4 + 100) = puVar5[0x19];
            gnt4_HSD_TExpUnref_bl();
          }
        }
        else if (bVar2 == 5) {
          uVar3 = puVar5[0x18];
          *(undefined4 *)(iVar7 + 0x44) = puVar5[0x17];
          *(undefined4 *)(iVar7 + 0x48) = uVar3;
          gnt4_HSD_TExpRef_bl(*(int **)(iVar7 + 0x48),*(char *)(iVar7 + 0x45));
          gnt4_HSD_TExpUnref_bl();
          goto LAB_80261bb0;
        }
      }
    }
    iVar6 = iVar6 + 1;
    iVar7 = iVar7 + 8;
    if (3 < iVar6) {
      gnt4__restgpr_26_bl();
      return;
    }
  } while( true );
}



// ==== 80261cb0  gnt4-SimplifyThis-bl ====

/* WARNING: Removing unreachable block (ram,0x802621e4) */

undefined4 gnt4_SimplifyThis_bl(int param_1)

{
  byte bVar1;
  char cVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined4 uVar16;
  int iVar17;
  
  uVar16 = 0;
  while( true ) {
    iVar8 = -1;
    iVar10 = -1;
    iVar12 = -1;
    iVar14 = -1;
    iVar6 = 0;
    iVar17 = 2;
    iVar5 = param_1;
    do {
      bVar1 = *(byte *)(iVar5 + 0x24);
      iVar9 = iVar8;
      iVar13 = iVar6;
      if (((bVar1 != 3) && (iVar13 = iVar12, bVar1 < 3)) && (iVar9 = iVar6, bVar1 < 2)) {
        iVar9 = iVar8;
      }
      bVar1 = *(byte *)(iVar5 + 0x44);
      iVar11 = iVar10;
      iVar15 = iVar6;
      if (((bVar1 != 3) && (iVar15 = iVar14, bVar1 < 3)) && (iVar11 = iVar6, bVar1 < 2)) {
        iVar11 = iVar10;
      }
      bVar1 = *(byte *)(iVar5 + 0x2c);
      iVar7 = iVar6 + 1;
      iVar8 = iVar9;
      iVar12 = iVar7;
      if (((bVar1 != 3) && (iVar12 = iVar13, bVar1 < 3)) && (iVar8 = iVar7, bVar1 < 2)) {
        iVar8 = iVar9;
      }
      bVar1 = *(byte *)(iVar5 + 0x4c);
      iVar10 = iVar11;
      iVar14 = iVar7;
      if (((bVar1 != 3) && (iVar14 = iVar15, bVar1 < 3)) && (iVar10 = iVar7, bVar1 < 2)) {
        iVar10 = iVar11;
      }
      iVar5 = iVar5 + 0x10;
      iVar6 = iVar6 + 2;
      iVar17 = iVar17 + -1;
    } while (iVar17 != 0);
    if ((iVar8 == -1) && (iVar10 == -1)) {
      *(undefined4 *)(param_1 + 100) = 0;
      *(undefined1 *)(param_1 + 0x1e) = 0xff;
    }
    if ((iVar12 == -1) && (iVar14 == -1)) {
      *(undefined1 *)(param_1 + 0x68) = 0xff;
      *(undefined1 *)(param_1 + 0x1f) = 0xff;
    }
    cVar2 = *(char *)(param_1 + 0x19);
    bVar3 = false;
    if ((((cVar2 == -1) || ((byte)(cVar2 - 0xeU) < 2)) || (cVar2 == '\0')) || (cVar2 == '\x01')) {
      if ((*(char *)(param_1 + 0xd) != -1) && (*(int *)(param_1 + 8) == 0)) {
        *(undefined1 *)(param_1 + 0xd) = 0xff;
        iVar8 = 0;
        iVar5 = param_1;
        do {
          gnt4_HSD_TExpUnref_bl();
          uVar4 = DAT_8043609c;
          iVar8 = iVar8 + 1;
          *(undefined4 *)(iVar5 + 0x24) = DAT_80436098;
          *(undefined4 *)(iVar5 + 0x28) = uVar4;
          iVar5 = iVar5 + 8;
        } while (iVar8 < 4);
        bVar3 = true;
      }
      switch(*(undefined1 *)(param_1 + 0xd)) {
      case 0:
      case 1:
        if (*(char *)(param_1 + 0x35) == '\a') {
          if (*(char *)(param_1 + 0x2d) != '\a') {
            gnt4_HSD_TExpUnref_bl();
            uVar4 = DAT_8043609c;
            bVar3 = true;
            *(undefined4 *)(param_1 + 0x2c) = DAT_80436098;
            *(undefined4 *)(param_1 + 0x30) = uVar4;
          }
          if ((*(char *)(param_1 + 0xd) == '\0') && (*(char *)(param_1 + 0x3d) == '\a')) {
            bVar3 = true;
            *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x24);
            *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x28);
            uVar4 = DAT_8043609c;
            *(undefined4 *)(param_1 + 0x24) = DAT_80436098;
            *(undefined4 *)(param_1 + 0x28) = uVar4;
            *(undefined1 *)(param_1 + 0xe) = 1;
          }
        }
        if (*(char *)(param_1 + 0x35) == '\b') {
          if (*(char *)(param_1 + 0x25) != '\a') {
            gnt4_HSD_TExpUnref_bl();
            uVar4 = DAT_8043609c;
            bVar3 = true;
            *(undefined4 *)(param_1 + 0x24) = DAT_80436098;
            *(undefined4 *)(param_1 + 0x28) = uVar4;
          }
          if ((*(char *)(param_1 + 0xd) == '\0') && (*(char *)(param_1 + 0x3d) == '\a')) {
            bVar3 = true;
            *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x2c);
            *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x30);
            uVar4 = DAT_8043609c;
            *(undefined4 *)(param_1 + 0x2c) = DAT_80436098;
            *(undefined4 *)(param_1 + 0x30) = uVar4;
            uVar4 = DAT_8043609c;
            *(undefined4 *)(param_1 + 0x34) = DAT_80436098;
            *(undefined4 *)(param_1 + 0x38) = uVar4;
          }
        }
        if ((*(char *)(param_1 + 0x25) == '\a') && (*(char *)(param_1 + 0x2d) == '\b')) {
          bVar3 = true;
          *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x34);
          *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x38);
          uVar4 = DAT_8043609c;
          *(undefined4 *)(param_1 + 0x2c) = DAT_80436098;
          *(undefined4 *)(param_1 + 0x30) = uVar4;
          uVar4 = DAT_8043609c;
          *(undefined4 *)(param_1 + 0x34) = DAT_80436098;
          *(undefined4 *)(param_1 + 0x38) = uVar4;
        }
        if ((((*(char *)(param_1 + 0x25) == '\a') && (*(char *)(param_1 + 0x2d) == '\a')) &&
            (*(char *)(param_1 + 0x3d) == '\a')) && (*(char *)(param_1 + 0xf) == '\0')) {
          *(undefined1 *)(param_1 + 0xd) = 0xff;
          gnt4_HSD_TExpUnref_bl();
          uVar4 = DAT_8043609c;
          bVar3 = true;
          *(undefined4 *)(param_1 + 0x34) = DAT_80436098;
          *(undefined4 *)(param_1 + 0x38) = uVar4;
        }
        break;
      case 8:
      case 10:
      case 0xc:
      case 0xe:
        if (*(char *)(param_1 + 0x35) == '\a') {
          *(undefined1 *)(param_1 + 0xd) = 0;
          gnt4_HSD_TExpUnref_bl();
          uVar4 = DAT_8043609c;
          *(undefined4 *)(param_1 + 0x24) = DAT_80436098;
          *(undefined4 *)(param_1 + 0x28) = uVar4;
          gnt4_HSD_TExpUnref_bl();
          uVar4 = DAT_8043609c;
          bVar3 = true;
          *(undefined4 *)(param_1 + 0x2c) = DAT_80436098;
          *(undefined4 *)(param_1 + 0x30) = uVar4;
        }
        else if (*(char *)(param_1 + 0x25) == '\a') {
          *(undefined1 *)(param_1 + 0xd) = 0;
          gnt4_HSD_TExpUnref_bl();
          uVar4 = DAT_8043609c;
          *(undefined4 *)(param_1 + 0x2c) = DAT_80436098;
          *(undefined4 *)(param_1 + 0x30) = uVar4;
          gnt4_HSD_TExpUnref_bl();
          uVar4 = DAT_8043609c;
          bVar3 = true;
          *(undefined4 *)(param_1 + 0x34) = DAT_80436098;
          *(undefined4 *)(param_1 + 0x38) = uVar4;
        }
        break;
      case 9:
      case 0xb:
      case 0xd:
      case 0xf:
        if (*(char *)(param_1 + 0x35) == '\a') {
          *(undefined1 *)(param_1 + 0xd) = 0;
          gnt4_HSD_TExpUnref_bl();
          uVar4 = DAT_8043609c;
          *(undefined4 *)(param_1 + 0x24) = DAT_80436098;
          *(undefined4 *)(param_1 + 0x28) = uVar4;
          gnt4_HSD_TExpUnref_bl();
          uVar4 = DAT_8043609c;
          bVar3 = true;
          *(undefined4 *)(param_1 + 0x2c) = DAT_80436098;
          *(undefined4 *)(param_1 + 0x30) = uVar4;
        }
        else if ((*(char *)(param_1 + 0x25) == '\a') && (*(char *)(param_1 + 0x2d) == '\a')) {
          bVar3 = true;
          *(undefined1 *)(param_1 + 0xd) = 0;
          *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x34);
          *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x38);
          uVar4 = DAT_8043609c;
          *(undefined4 *)(param_1 + 0x34) = DAT_80436098;
          *(undefined4 *)(param_1 + 0x38) = uVar4;
        }
      }
    }
    if ((*(char *)(param_1 + 0x19) != -1) && (*(int *)(param_1 + 0x14) == 0)) {
      *(undefined1 *)(param_1 + 0x19) = 0xff;
      iVar8 = 0;
      iVar5 = param_1;
      do {
        gnt4_HSD_TExpUnref_bl();
        uVar4 = DAT_8043609c;
        iVar8 = iVar8 + 1;
        *(undefined4 *)(iVar5 + 0x44) = DAT_80436098;
        *(undefined4 *)(iVar5 + 0x48) = uVar4;
        iVar5 = iVar5 + 8;
      } while (iVar8 < 4);
      bVar3 = true;
    }
    bVar1 = *(byte *)(param_1 + 0x19);
    if (bVar1 == 0xe) {
      if (*(char *)(param_1 + 0x55) == '\a') {
        *(undefined1 *)(param_1 + 0x19) = 0;
        gnt4_HSD_TExpUnref_bl();
        uVar4 = DAT_8043609c;
        *(undefined4 *)(param_1 + 0x44) = DAT_80436098;
        *(undefined4 *)(param_1 + 0x48) = uVar4;
        gnt4_HSD_TExpUnref_bl();
        uVar4 = DAT_8043609c;
        bVar3 = true;
        *(undefined4 *)(param_1 + 0x4c) = DAT_80436098;
        *(undefined4 *)(param_1 + 0x50) = uVar4;
      }
      else if (*(char *)(param_1 + 0x45) == '\a') {
        *(undefined1 *)(param_1 + 0x19) = 0;
        gnt4_HSD_TExpUnref_bl();
        uVar4 = DAT_8043609c;
        *(undefined4 *)(param_1 + 0x4c) = DAT_80436098;
        *(undefined4 *)(param_1 + 0x50) = uVar4;
        gnt4_HSD_TExpUnref_bl();
        uVar4 = DAT_8043609c;
        bVar3 = true;
        *(undefined4 *)(param_1 + 0x54) = DAT_80436098;
        *(undefined4 *)(param_1 + 0x58) = uVar4;
      }
    }
    else if (bVar1 < 0xe) {
      if (bVar1 < 2) {
        if (*(char *)(param_1 + 0x55) == '\a') {
          if (*(char *)(param_1 + 0x4d) != '\a') {
            gnt4_HSD_TExpUnref_bl();
            uVar4 = DAT_8043609c;
            bVar3 = true;
            *(undefined4 *)(param_1 + 0x4c) = DAT_80436098;
            *(undefined4 *)(param_1 + 0x50) = uVar4;
          }
          if ((*(char *)(param_1 + 0x19) == '\0') && (*(char *)(param_1 + 0x5d) == '\a')) {
            bVar3 = true;
            *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x44);
            *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x48);
            uVar4 = DAT_8043609c;
            *(undefined4 *)(param_1 + 0x44) = DAT_80436098;
            *(undefined4 *)(param_1 + 0x48) = uVar4;
          }
        }
        if (*(char *)(param_1 + 0x55) == '\b') {
          if (*(char *)(param_1 + 0x45) != '\a') {
            gnt4_HSD_TExpUnref_bl();
            uVar4 = DAT_8043609c;
            bVar3 = true;
            *(undefined4 *)(param_1 + 0x44) = DAT_80436098;
            *(undefined4 *)(param_1 + 0x48) = uVar4;
          }
          if ((*(char *)(param_1 + 0x19) == '\0') && (*(char *)(param_1 + 0x5d) == '\a')) {
            bVar3 = true;
            *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x4c);
            *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x50);
            uVar4 = DAT_8043609c;
            *(undefined4 *)(param_1 + 0x4c) = DAT_80436098;
            *(undefined4 *)(param_1 + 0x50) = uVar4;
            uVar4 = DAT_8043609c;
            *(undefined4 *)(param_1 + 0x54) = DAT_80436098;
            *(undefined4 *)(param_1 + 0x58) = uVar4;
          }
        }
        if (((*(char *)(param_1 + 0x45) == '\a') && (*(char *)(param_1 + 0x4d) == '\a')) &&
           (*(char *)(param_1 + 0x5d) == '\a')) {
          bVar3 = true;
          *(undefined1 *)(param_1 + 0x19) = 0xff;
        }
      }
      else if ((7 < bVar1) && (*(char *)(param_1 + 0x55) == '\a')) {
        *(undefined1 *)(param_1 + 0x19) = 0;
        gnt4_HSD_TExpUnref_bl();
        uVar4 = DAT_8043609c;
        *(undefined4 *)(param_1 + 0x44) = DAT_80436098;
        *(undefined4 *)(param_1 + 0x48) = uVar4;
        gnt4_HSD_TExpUnref_bl();
        uVar4 = DAT_8043609c;
        bVar3 = true;
        *(undefined4 *)(param_1 + 0x4c) = DAT_80436098;
        *(undefined4 *)(param_1 + 0x50) = uVar4;
      }
    }
    else if (bVar1 < 0x10) {
      if (*(char *)(param_1 + 0x55) == '\a') {
        *(undefined1 *)(param_1 + 0x19) = 0;
        gnt4_HSD_TExpUnref_bl();
        uVar4 = DAT_8043609c;
        *(undefined4 *)(param_1 + 0x44) = DAT_80436098;
        *(undefined4 *)(param_1 + 0x48) = uVar4;
        gnt4_HSD_TExpUnref_bl();
        uVar4 = DAT_8043609c;
        bVar3 = true;
        *(undefined4 *)(param_1 + 0x4c) = DAT_80436098;
        *(undefined4 *)(param_1 + 0x50) = uVar4;
      }
      else if ((*(char *)(param_1 + 0x45) == '\a') && (*(char *)(param_1 + 0x4d) == '\a')) {
        bVar3 = true;
        *(undefined1 *)(param_1 + 0x19) = 0;
        *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x54);
        *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x58);
        uVar4 = DAT_8043609c;
        *(undefined4 *)(param_1 + 0x54) = DAT_80436098;
        *(undefined4 *)(param_1 + 0x58) = uVar4;
      }
    }
    if (!bVar3) break;
    uVar16 = 1;
  }
  return uVar16;
}



// ==== 802624f0  gnt4-SimplifyByMerge-bl ====

/* WARNING: Removing unreachable block (ram,0x80262be4) */
/* WARNING: Removing unreachable block (ram,0x80262f6c) */
/* WARNING: Removing unreachable block (ram,0x80263490) */
/* WARNING: Removing unreachable block (ram,0x802628c8) */
/* WARNING: Removing unreachable block (ram,0x80262f20) */
/* WARNING: Removing unreachable block (ram,0x802637a4) */
/* WARNING: Removing unreachable block (ram,0x802637f0) */
/* WARNING: Removing unreachable block (ram,0x80262914) */
/* WARNING: Removing unreachable block (ram,0x80262c30) */
/* WARNING: Removing unreachable block (ram,0x802634dc) */
/* WARNING: Removing unreachable block (ram,0x80263a98) */
/* WARNING: Removing unreachable block (ram,0x80263ae4) */

void gnt4_SimplifyByMerge_bl(void)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  bool bVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  undefined1 unaff_r28;
  undefined1 unaff_r29;
  int iVar14;
  
  iVar8 = gnt4__savegpr_20_bl();
  do {
    cVar1 = *(char *)(iVar8 + 0xd);
    bVar6 = false;
    if (((cVar1 == '\0') || (cVar1 == '\x01')) && (*(char *)(iVar8 + 0x35) == '\a')) {
      cVar2 = *(char *)(iVar8 + 0x24);
      iVar9 = *(int *)(iVar8 + 0x28);
      if (((cVar2 == '\x01') && (*(char *)(iVar8 + 0x25) == '\x01')) &&
         ((*(char *)(iVar9 + 0x11) == '\0' && (*(char *)(iVar9 + 0x3d) == '\a')))) {
        if (((*(int *)(iVar8 + 100) == 0) || (*(int *)(iVar9 + 100) == 0)) ||
           (*(int *)(iVar8 + 100) == *(int *)(iVar9 + 100))) {
          if (((*(char *)(iVar8 + 0x68) == -1) || (*(char *)(iVar9 + 0x68) == -1)) ||
             (*(char *)(iVar8 + 0x68) == *(char *)(iVar9 + 0x68))) {
            bVar5 = false;
          }
          else {
            bVar5 = true;
          }
        }
        else {
          bVar5 = true;
        }
        if (bVar5) goto LAB_80262644;
        bVar5 = false;
        if (((*(char *)(iVar8 + 0x2c) == '\x04') || (*(char *)(iVar8 + 0x34) == '\x04')) ||
           (*(char *)(iVar8 + 0x3c) == '\x04')) {
          bVar5 = true;
        }
        iVar13 = iVar9;
        if (bVar5) {
          bVar5 = false;
          if (((*(char *)(iVar9 + 0x24) == '\x04') || (*(char *)(iVar9 + 0x2c) == '\x04')) ||
             ((*(char *)(iVar9 + 0x34) == '\x04' || (*(char *)(iVar9 + 0x3c) == '\x04')))) {
            bVar5 = true;
          }
          if (bVar5) goto LAB_80262644;
        }
LAB_802627c4:
        bVar3 = *(byte *)(iVar13 + 0x10);
        if (bVar3 == 0) {
          bVar3 = *(byte *)(iVar13 + 0xf);
          bVar4 = *(byte *)(iVar8 + 0xf);
          if (bVar3 == 2) {
            iVar9 = -1;
          }
          else if ((bVar3 < 2) && (bVar3 != 0)) {
            iVar9 = 1;
          }
          else {
            iVar9 = 0;
          }
          if (*(char *)(iVar8 + 0xd) == '\x01') {
            iVar9 = -iVar9;
          }
          if (bVar4 == 2) {
            iVar9 = iVar9 + -1;
          }
          else if ((bVar4 < 2) && (bVar4 != 0)) {
            iVar9 = iVar9 + 1;
          }
          if (iVar9 == 0) {
            unaff_r29 = 0;
            bVar5 = true;
          }
          else if (iVar9 < 0) {
            if (iVar9 < -1) {
LAB_80262880:
              bVar5 = false;
            }
            else {
              unaff_r29 = 2;
              bVar5 = true;
            }
          }
          else {
            if (1 < iVar9) goto LAB_80262880;
            unaff_r29 = 1;
            bVar5 = true;
          }
          if (!bVar5) goto LAB_80262a8c;
          unaff_r28 = *(undefined1 *)(iVar8 + 0x10);
        }
        else {
          if ((*(char *)(iVar8 + 0x3d) != '\a') || (*(char *)(iVar8 + 0xf) != '\0'))
          goto LAB_80262a8c;
          bVar4 = *(byte *)(iVar8 + 0x10);
          if (bVar4 == 2) {
            iVar9 = 8;
          }
          else if (bVar4 < 2) {
            if (bVar4 == 0) {
              iVar9 = 2;
            }
            else {
              iVar9 = 4;
            }
          }
          else if (bVar4 < 4) {
            iVar9 = 1;
          }
          else {
            iVar9 = 2;
          }
          if (bVar3 == 2) {
            iVar14 = 8;
          }
          else if (bVar3 < 2) {
            if (bVar3 == 0) {
              iVar14 = 2;
            }
            else {
              iVar14 = 4;
            }
          }
          else if (bVar3 < 4) {
            iVar14 = 1;
          }
          else {
            iVar14 = 2;
          }
          uVar7 = iVar9 * iVar14 >> 1;
          if (uVar7 == 4) {
            unaff_r28 = 1;
LAB_802629b0:
            bVar5 = true;
          }
          else {
            if (uVar7 < 4) {
              if (uVar7 == 2) {
                unaff_r28 = 0;
              }
              else {
                if ((1 < uVar7) || (uVar7 == 0)) goto LAB_802629a8;
                unaff_r28 = 3;
              }
              goto LAB_802629b0;
            }
            if (uVar7 == 8) {
              unaff_r28 = 2;
              goto LAB_802629b0;
            }
LAB_802629a8:
            bVar5 = false;
          }
          if (!bVar5) goto LAB_80262a8c;
          unaff_r29 = *(undefined1 *)(iVar13 + 0xf);
        }
        if (*(char *)(iVar8 + 0xd) == '\x01') {
          uVar7 = countLeadingZeros((uint)*(byte *)(iVar13 + 0xd));
          *(char *)(iVar8 + 0xd) = (char)(uVar7 >> 5);
        }
        else {
          *(undefined1 *)(iVar8 + 0xd) = *(undefined1 *)(iVar13 + 0xd);
        }
        iVar12 = 0;
        iVar9 = iVar8;
        iVar14 = iVar13;
        do {
          uVar10 = *(undefined4 *)(iVar14 + 0x28);
          *(undefined4 *)(iVar9 + 0x24) = *(undefined4 *)(iVar14 + 0x24);
          *(undefined4 *)(iVar9 + 0x28) = uVar10;
          gnt4_HSD_TExpRef_bl(*(int **)(iVar9 + 0x28),*(char *)(iVar9 + 0x25));
          iVar12 = iVar12 + 1;
          iVar9 = iVar9 + 8;
          iVar14 = iVar14 + 8;
        } while (iVar12 < 3);
        *(undefined1 *)(iVar8 + 0xf) = unaff_r29;
        *(undefined1 *)(iVar8 + 0x10) = unaff_r28;
        gnt4_HSD_TExpUnref_bl();
        if (*(int *)(iVar8 + 100) == 0) {
          *(undefined4 *)(iVar8 + 100) = *(undefined4 *)(iVar13 + 100);
        }
        if (*(char *)(iVar8 + 0x68) == -1) {
          *(undefined1 *)(iVar8 + 0x68) = *(undefined1 *)(iVar13 + 0x68);
        }
        if (*(char *)(iVar8 + 0x1e) == -1) {
          *(undefined1 *)(iVar8 + 0x1e) = *(undefined1 *)(iVar13 + 0x1e);
        }
        if (*(char *)(iVar8 + 0x1f) == -1) {
          *(undefined1 *)(iVar8 + 0x1f) = *(undefined1 *)(iVar13 + 0x1f);
        }
        bVar6 = true;
      }
      else {
LAB_80262644:
        iVar13 = *(int *)(iVar8 + 0x40);
        if ((((cVar1 == '\0') && (*(char *)(iVar8 + 0x3c) == '\x01')) &&
            (*(char *)(iVar8 + 0x3d) == '\x01')) &&
           ((*(char *)(iVar13 + 0x11) == '\0' && (*(char *)(iVar13 + 0x3d) == '\a')))) {
          if ((*(int *)(iVar8 + 100) == 0) ||
             ((*(int *)(iVar13 + 100) == 0 || (*(int *)(iVar8 + 100) == *(int *)(iVar13 + 100))))) {
            if ((*(char *)(iVar8 + 0x68) == -1) ||
               ((*(char *)(iVar13 + 0x68) == -1 ||
                (*(char *)(iVar8 + 0x68) == *(char *)(iVar13 + 0x68))))) {
              bVar5 = false;
            }
            else {
              bVar5 = true;
            }
          }
          else {
            bVar5 = true;
          }
          if (!bVar5) {
            bVar5 = false;
            if (((cVar2 == '\x04') || (*(char *)(iVar8 + 0x2c) == '\x04')) ||
               (*(char *)(iVar8 + 0x34) == '\x04')) {
              bVar5 = true;
            }
            if (bVar5) {
              bVar5 = false;
              if (((*(char *)(iVar13 + 0x24) == '\x04') || (*(char *)(iVar13 + 0x2c) == '\x04')) ||
                 ((*(char *)(iVar13 + 0x34) == '\x04' || (*(char *)(iVar13 + 0x3c) == '\x04')))) {
                bVar5 = true;
              }
              if (bVar5) goto LAB_80262a8c;
            }
            if (cVar2 == '\x01') {
              if (*(char *)(iVar8 + 0x25) == '\x01') {
                if (*(char *)(iVar9 + 0x11) != '\0') {
                  cVar1 = *(char *)(iVar9 + 0xe);
joined_r0x80262798:
                  if (cVar1 != '\x01') goto LAB_80262a8c;
                }
              }
              else if (*(char *)(iVar9 + 0x1d) != '\0') {
                cVar1 = *(char *)(iVar9 + 0x1a);
                goto joined_r0x80262798;
              }
            }
            uVar11 = *(undefined4 *)(iVar8 + 0x24);
            uVar10 = *(undefined4 *)(iVar8 + 0x28);
            *(undefined4 *)(iVar8 + 0x24) = *(undefined4 *)(iVar8 + 0x3c);
            *(undefined4 *)(iVar8 + 0x28) = *(undefined4 *)(iVar8 + 0x40);
            *(undefined4 *)(iVar8 + 0x3c) = uVar11;
            *(undefined4 *)(iVar8 + 0x40) = uVar10;
            goto LAB_802627c4;
          }
        }
      }
    }
LAB_80262a8c:
    iVar9 = *(int *)(iVar8 + 0x40);
    if ((*(char *)(iVar8 + 0x3c) == '\x01') && (*(char *)(iVar8 + 0x3d) == '\x01')) {
      if ((*(int *)(iVar8 + 100) == 0) ||
         ((*(int *)(iVar9 + 100) == 0 || (*(int *)(iVar8 + 100) == *(int *)(iVar9 + 100))))) {
        if ((*(char *)(iVar8 + 0x68) == -1) ||
           ((*(char *)(iVar9 + 0x68) == -1 || (*(char *)(iVar8 + 0x68) == *(char *)(iVar9 + 0x68))))
           ) {
          bVar5 = false;
        }
        else {
          bVar5 = true;
        }
      }
      else {
        bVar5 = true;
      }
      if (!bVar5) {
        bVar5 = false;
        if (((*(char *)(iVar8 + 0x24) == '\x04') || (*(char *)(iVar8 + 0x2c) == '\x04')) ||
           (*(char *)(iVar8 + 0x34) == '\x04')) {
          bVar5 = true;
        }
        if (bVar5) {
          bVar5 = false;
          if (((*(char *)(iVar9 + 0x24) == '\x04') || (*(char *)(iVar9 + 0x2c) == '\x04')) ||
             ((*(char *)(iVar9 + 0x34) == '\x04' || (*(char *)(iVar9 + 0x3c) == '\x04')))) {
            bVar5 = true;
          }
          if (bVar5) goto LAB_80263110;
        }
        if ((*(char *)(iVar9 + 0x11) == '\0') || (*(char *)(iVar9 + 0xe) != '\x01')) {
          bVar3 = *(byte *)(iVar8 + 0x19);
          if (((bVar3 != 0xff) && ((1 < (byte)(bVar3 - 0xe) && (1 < bVar3)))) &&
             ((*(char *)(iVar9 + 0x25) != '\a' ||
              ((*(char *)(iVar9 + 0x2d) != '\a' || (*(char *)(iVar9 + 0x35) != '\a'))))))
          goto LAB_80263110;
          bVar3 = *(byte *)(iVar9 + 0x10);
          if (bVar3 == 0) {
            if (((*(char *)(iVar8 + 0x25) == '\a') && (*(char *)(iVar8 + 0x35) == '\a')) ||
               ((*(char *)(iVar9 + 0x25) == '\a' && (*(char *)(iVar9 + 0x35) == '\a')))) {
              bVar3 = *(byte *)(iVar9 + 0xf);
              bVar4 = *(byte *)(iVar8 + 0xf);
              if (bVar3 == 2) {
                iVar13 = -1;
              }
              else if ((bVar3 < 2) && (bVar3 != 0)) {
                iVar13 = 1;
              }
              else {
                iVar13 = 0;
              }
              if (bVar4 == 2) {
                iVar13 = iVar13 + -1;
              }
              else if ((bVar4 < 2) && (bVar4 != 0)) {
                iVar13 = iVar13 + 1;
              }
              if (iVar13 == 0) {
                unaff_r29 = 0;
                bVar5 = true;
              }
              else if (iVar13 < 0) {
                if (iVar13 < -1) {
LAB_80262ec0:
                  bVar5 = false;
                }
                else {
                  unaff_r29 = 2;
                  bVar5 = true;
                }
              }
              else {
                if (1 < iVar13) goto LAB_80262ec0;
                unaff_r29 = 1;
                bVar5 = true;
              }
              if (bVar5) {
                unaff_r28 = *(undefined1 *)(iVar8 + 0x10);
                goto LAB_80263018;
              }
            }
          }
          else {
            if ((((*(char *)(iVar8 + 0x25) != '\a') || (*(char *)(iVar8 + 0x2d) != '\a')) ||
                (*(char *)(iVar8 + 0x35) != '\a')) || (*(char *)(iVar8 + 0xf) != '\0'))
            goto LAB_80263110;
            bVar4 = *(byte *)(iVar8 + 0x10);
            if (bVar4 == 2) {
              iVar13 = 8;
            }
            else if (bVar4 < 2) {
              if (bVar4 == 0) {
                iVar13 = 2;
              }
              else {
                iVar13 = 4;
              }
            }
            else if (bVar4 < 4) {
              iVar13 = 1;
            }
            else {
              iVar13 = 2;
            }
            if (bVar3 == 2) {
              iVar14 = 8;
            }
            else if (bVar3 < 2) {
              if (bVar3 == 0) {
                iVar14 = 2;
              }
              else {
                iVar14 = 4;
              }
            }
            else if (bVar3 < 4) {
              iVar14 = 1;
            }
            else {
              iVar14 = 2;
            }
            uVar7 = iVar13 * iVar14 >> 1;
            if (uVar7 == 4) {
              unaff_r28 = 1;
LAB_80263008:
              bVar5 = true;
            }
            else {
              if (uVar7 < 4) {
                if (uVar7 == 2) {
                  unaff_r28 = 0;
                }
                else {
                  if ((1 < uVar7) || (uVar7 == 0)) goto LAB_80263000;
                  unaff_r28 = 3;
                }
                goto LAB_80263008;
              }
              if (uVar7 == 8) {
                unaff_r28 = 2;
                goto LAB_80263008;
              }
LAB_80263000:
              bVar5 = false;
            }
            if (bVar5) {
              unaff_r29 = *(undefined1 *)(iVar9 + 0xf);
LAB_80263018:
              bVar6 = true;
              uVar10 = *(undefined4 *)(iVar9 + 0x40);
              *(undefined4 *)(iVar8 + 0x3c) = *(undefined4 *)(iVar9 + 0x3c);
              *(undefined4 *)(iVar8 + 0x40) = uVar10;
              gnt4_HSD_TExpRef_bl(*(int **)(iVar8 + 0x40),*(char *)(iVar8 + 0x3d));
              *(undefined1 *)(iVar8 + 0xf) = unaff_r29;
              *(undefined1 *)(iVar8 + 0x10) = unaff_r28;
              if (*(int *)(iVar8 + 100) == 0) {
                *(undefined4 *)(iVar8 + 100) = *(undefined4 *)(iVar9 + 100);
              }
              if (*(char *)(iVar8 + 0x68) == -1) {
                *(undefined1 *)(iVar8 + 0x68) = *(undefined1 *)(iVar9 + 0x68);
              }
              if (*(char *)(iVar8 + 0x1e) == -1) {
                *(undefined1 *)(iVar8 + 0x1e) = *(undefined1 *)(iVar9 + 0x1e);
              }
              if (*(char *)(iVar8 + 0x1f) == -1) {
                *(undefined1 *)(iVar8 + 0x1f) = *(undefined1 *)(iVar9 + 0x1f);
              }
              if (((*(char *)(iVar9 + 0x25) != '\a') || (*(char *)(iVar9 + 0x2d) != '\a')) ||
                 (*(char *)(iVar9 + 0x35) != '\a')) {
                iVar14 = 0;
                iVar13 = iVar8;
                do {
                  uVar10 = *(undefined4 *)(iVar9 + 0x28);
                  *(undefined4 *)(iVar13 + 0x24) = *(undefined4 *)(iVar9 + 0x24);
                  *(undefined4 *)(iVar13 + 0x28) = uVar10;
                  gnt4_HSD_TExpRef_bl(*(int **)(iVar13 + 0x28),*(char *)(iVar13 + 0x25));
                  gnt4_HSD_TExpUnref_bl();
                  iVar14 = iVar14 + 1;
                  iVar9 = iVar9 + 8;
                  iVar13 = iVar13 + 8;
                } while (iVar14 < 3);
              }
              gnt4_HSD_TExpUnref_bl();
            }
          }
        }
        else {
          if (((*(char *)(iVar8 + 0x25) != '\a') || (*(char *)(iVar8 + 0x35) != '\a')) ||
             ((*(char *)(iVar8 + 0xf) != '\0' || (bVar3 = *(byte *)(iVar8 + 0x10), bVar3 == 3))))
          goto LAB_80263110;
          bVar4 = *(byte *)(iVar9 + 0x10);
          if (bVar3 == 2) {
            iVar13 = 8;
          }
          else if (bVar3 < 2) {
            if (bVar3 == 0) {
              iVar13 = 2;
            }
            else {
              iVar13 = 4;
            }
          }
          else if (bVar3 < 4) {
            iVar13 = 1;
          }
          else {
            iVar13 = 2;
          }
          if (bVar4 == 2) {
            iVar14 = 8;
          }
          else if (bVar4 < 2) {
            if (bVar4 == 0) {
              iVar14 = 2;
            }
            else {
              iVar14 = 4;
            }
          }
          else if (bVar4 < 4) {
            iVar14 = 1;
          }
          else {
            iVar14 = 2;
          }
          uVar7 = iVar13 * iVar14 >> 1;
          if (uVar7 == 4) {
            unaff_r28 = 1;
LAB_80262ccc:
            bVar5 = true;
          }
          else {
            if (uVar7 < 4) {
              if (uVar7 == 2) {
                unaff_r28 = 0;
              }
              else {
                if ((1 < uVar7) || (uVar7 == 0)) goto LAB_80262cc4;
                unaff_r28 = 3;
              }
              goto LAB_80262ccc;
            }
            if (uVar7 == 8) {
              unaff_r28 = 2;
              goto LAB_80262ccc;
            }
LAB_80262cc4:
            bVar5 = false;
          }
          if (bVar5) {
            bVar6 = true;
            *(undefined1 *)(iVar8 + 0xf) = *(undefined1 *)(iVar9 + 0xf);
            *(undefined1 *)(iVar8 + 0x10) = unaff_r28;
            if (*(char *)(iVar8 + 0xe) != '\x01') {
              *(undefined1 *)(iVar8 + 0xe) = *(undefined1 *)(iVar9 + 0xe);
            }
            if (*(int *)(iVar8 + 100) == 0) {
              *(undefined4 *)(iVar8 + 100) = *(undefined4 *)(iVar9 + 100);
            }
            if (*(char *)(iVar8 + 0x68) == -1) {
              *(undefined1 *)(iVar8 + 0x68) = *(undefined1 *)(iVar9 + 0x68);
            }
            if (*(char *)(iVar8 + 0x1e) == -1) {
              *(undefined1 *)(iVar8 + 0x1e) = *(undefined1 *)(iVar9 + 0x1e);
            }
            if (*(char *)(iVar8 + 0x1f) == -1) {
              *(undefined1 *)(iVar8 + 0x1f) = *(undefined1 *)(iVar9 + 0x1f);
            }
            iVar14 = 0;
            iVar13 = iVar8;
            do {
              uVar10 = *(undefined4 *)(iVar9 + 0x28);
              *(undefined4 *)(iVar13 + 0x24) = *(undefined4 *)(iVar9 + 0x24);
              *(undefined4 *)(iVar13 + 0x28) = uVar10;
              gnt4_HSD_TExpRef_bl(*(int **)(iVar13 + 0x28),*(char *)(iVar13 + 0x25));
              gnt4_HSD_TExpUnref_bl();
              iVar14 = iVar14 + 1;
              iVar9 = iVar9 + 8;
              iVar13 = iVar13 + 8;
            } while (iVar14 < 4);
          }
        }
      }
    }
LAB_80263110:
    cVar1 = *(char *)(iVar8 + 0x19);
    if (((cVar1 == '\0') || (cVar1 == '\x01')) && (*(char *)(iVar8 + 0x55) == '\a')) {
      iVar9 = *(int *)(iVar8 + 0x48);
      if (((*(char *)(iVar8 + 0x44) == '\x01') && (*(char *)(iVar9 + 0x1d) == '\0')) &&
         (*(char *)(iVar9 + 0x5d) == '\a')) {
        if (((*(int *)(iVar8 + 100) == 0) || (*(int *)(iVar9 + 100) == 0)) ||
           (*(int *)(iVar8 + 100) == *(int *)(iVar9 + 100))) {
          if (((*(char *)(iVar8 + 0x68) == -1) || (*(char *)(iVar9 + 0x68) == -1)) ||
             (*(char *)(iVar8 + 0x68) == *(char *)(iVar9 + 0x68))) {
            bVar5 = false;
          }
          else {
            bVar5 = true;
          }
        }
        else {
          bVar5 = true;
        }
        if (bVar5) goto LAB_80263238;
        bVar5 = false;
        if (((*(char *)(iVar8 + 0x4c) == '\x04') || (*(char *)(iVar8 + 0x54) == '\x04')) ||
           (*(char *)(iVar8 + 0x5c) == '\x04')) {
          bVar5 = true;
        }
        iVar13 = iVar9;
        if (bVar5) {
          bVar5 = false;
          if (((*(char *)(iVar9 + 0x44) == '\x04') || (*(char *)(iVar9 + 0x4c) == '\x04')) ||
             ((*(char *)(iVar9 + 0x54) == '\x04' || (*(char *)(iVar9 + 0x5c) == '\x04')))) {
            bVar5 = true;
          }
          if (bVar5) goto LAB_80263238;
        }
LAB_8026338c:
        bVar3 = *(byte *)(iVar13 + 0x1c);
        if (bVar3 == 0) {
          bVar3 = *(byte *)(iVar13 + 0x1b);
          bVar4 = *(byte *)(iVar8 + 0x1b);
          if (bVar3 == 2) {
            iVar9 = -1;
          }
          else if ((bVar3 < 2) && (bVar3 != 0)) {
            iVar9 = 1;
          }
          else {
            iVar9 = 0;
          }
          if (*(char *)(iVar8 + 0x19) == '\x01') {
            iVar9 = -iVar9;
          }
          if (bVar4 == 2) {
            iVar9 = iVar9 + -1;
          }
          else if ((bVar4 < 2) && (bVar4 != 0)) {
            iVar9 = iVar9 + 1;
          }
          if (iVar9 == 0) {
            unaff_r29 = 0;
            bVar5 = true;
          }
          else if (iVar9 < 0) {
            if (iVar9 < -1) {
LAB_80263448:
              bVar5 = false;
            }
            else {
              unaff_r29 = 2;
              bVar5 = true;
            }
          }
          else {
            if (1 < iVar9) goto LAB_80263448;
            unaff_r29 = 1;
            bVar5 = true;
          }
          if (!bVar5) goto LAB_80263654;
          unaff_r28 = *(undefined1 *)(iVar8 + 0x1c);
        }
        else {
          if ((*(char *)(iVar8 + 0x5d) != '\a') || (*(char *)(iVar8 + 0x1b) != '\0'))
          goto LAB_80263654;
          bVar4 = *(byte *)(iVar8 + 0x1c);
          if (bVar4 == 2) {
            iVar9 = 8;
          }
          else if (bVar4 < 2) {
            if (bVar4 == 0) {
              iVar9 = 2;
            }
            else {
              iVar9 = 4;
            }
          }
          else if (bVar4 < 4) {
            iVar9 = 1;
          }
          else {
            iVar9 = 2;
          }
          if (bVar3 == 2) {
            iVar14 = 8;
          }
          else if (bVar3 < 2) {
            if (bVar3 == 0) {
              iVar14 = 2;
            }
            else {
              iVar14 = 4;
            }
          }
          else if (bVar3 < 4) {
            iVar14 = 1;
          }
          else {
            iVar14 = 2;
          }
          uVar7 = iVar9 * iVar14 >> 1;
          if (uVar7 == 4) {
            unaff_r28 = 1;
LAB_80263578:
            bVar5 = true;
          }
          else {
            if (uVar7 < 4) {
              if (uVar7 == 2) {
                unaff_r28 = 0;
              }
              else {
                if ((1 < uVar7) || (uVar7 == 0)) goto LAB_80263570;
                unaff_r28 = 3;
              }
              goto LAB_80263578;
            }
            if (uVar7 == 8) {
              unaff_r28 = 2;
              goto LAB_80263578;
            }
LAB_80263570:
            bVar5 = false;
          }
          if (!bVar5) goto LAB_80263654;
          unaff_r29 = *(undefined1 *)(iVar13 + 0x1b);
        }
        if (*(char *)(iVar8 + 0x19) == '\x01') {
          uVar7 = countLeadingZeros((uint)*(byte *)(iVar13 + 0x19));
          *(char *)(iVar8 + 0x19) = (char)(uVar7 >> 5);
        }
        else {
          *(undefined1 *)(iVar8 + 0x19) = *(undefined1 *)(iVar13 + 0x19);
        }
        iVar12 = 0;
        iVar9 = iVar13;
        iVar14 = iVar8;
        do {
          uVar10 = *(undefined4 *)(iVar9 + 0x48);
          *(undefined4 *)(iVar14 + 0x44) = *(undefined4 *)(iVar9 + 0x44);
          *(undefined4 *)(iVar14 + 0x48) = uVar10;
          gnt4_HSD_TExpRef_bl(*(int **)(iVar14 + 0x48),*(char *)(iVar14 + 0x45));
          iVar12 = iVar12 + 1;
          iVar14 = iVar14 + 8;
          iVar9 = iVar9 + 8;
        } while (iVar12 < 3);
        *(undefined1 *)(iVar8 + 0x1b) = unaff_r29;
        *(undefined1 *)(iVar8 + 0x1c) = unaff_r28;
        gnt4_HSD_TExpUnref_bl();
        if (*(int *)(iVar8 + 100) == 0) {
          *(undefined4 *)(iVar8 + 100) = *(undefined4 *)(iVar13 + 100);
        }
        if (*(char *)(iVar8 + 0x68) == -1) {
          *(undefined1 *)(iVar8 + 0x68) = *(undefined1 *)(iVar13 + 0x68);
        }
        if (*(char *)(iVar8 + 0x1e) == -1) {
          *(undefined1 *)(iVar8 + 0x1e) = *(undefined1 *)(iVar13 + 0x1e);
        }
        if (*(char *)(iVar8 + 0x1f) == -1) {
          *(undefined1 *)(iVar8 + 0x1f) = *(undefined1 *)(iVar13 + 0x1f);
        }
        bVar6 = true;
      }
      else {
LAB_80263238:
        iVar13 = *(int *)(iVar8 + 0x60);
        if ((((cVar1 == '\0') && (*(char *)(iVar8 + 0x5c) == '\x01')) &&
            (*(char *)(iVar13 + 0x1d) == '\0')) && (*(char *)(iVar13 + 0x5d) == '\a')) {
          if (((*(int *)(iVar8 + 100) == 0) || (*(int *)(iVar13 + 100) == 0)) ||
             (*(int *)(iVar8 + 100) == *(int *)(iVar13 + 100))) {
            if (((*(char *)(iVar8 + 0x68) == -1) || (*(char *)(iVar13 + 0x68) == -1)) ||
               (*(char *)(iVar8 + 0x68) == *(char *)(iVar13 + 0x68))) {
              bVar5 = false;
            }
            else {
              bVar5 = true;
            }
          }
          else {
            bVar5 = true;
          }
          if (!bVar5) {
            bVar5 = false;
            if ((((*(char *)(iVar13 + 0x44) == '\x04') || (*(char *)(iVar13 + 0x4c) == '\x04')) ||
                (*(char *)(iVar13 + 0x54) == '\x04')) || (*(char *)(iVar13 + 0x5c) == '\x04')) {
              bVar5 = true;
            }
            if (bVar5) {
              bVar5 = false;
              if (((*(char *)(iVar13 + 0x44) == '\x04') || (*(char *)(iVar13 + 0x4c) == '\x04')) ||
                 ((*(char *)(iVar13 + 0x54) == '\x04' || (*(char *)(iVar13 + 0x5c) == '\x04')))) {
                bVar5 = true;
              }
              if (bVar5) goto LAB_80263654;
            }
            if (((*(char *)(iVar8 + 0x44) != '\x01') || (*(char *)(iVar9 + 0x1d) == '\0')) ||
               (*(char *)(iVar9 + 0x1a) == '\x01')) {
              uVar11 = *(undefined4 *)(iVar8 + 0x44);
              uVar10 = *(undefined4 *)(iVar8 + 0x48);
              *(undefined4 *)(iVar8 + 0x44) = *(undefined4 *)(iVar8 + 0x5c);
              *(undefined4 *)(iVar8 + 0x48) = *(undefined4 *)(iVar8 + 0x60);
              *(undefined4 *)(iVar8 + 0x5c) = uVar11;
              *(undefined4 *)(iVar8 + 0x60) = uVar10;
              goto LAB_8026338c;
            }
          }
        }
      }
    }
LAB_80263654:
    iVar9 = *(int *)(iVar8 + 0x60);
    if (*(char *)(iVar8 + 0x5c) == '\x01') {
      if (((*(int *)(iVar8 + 100) == 0) || (*(int *)(iVar9 + 100) == 0)) ||
         (*(int *)(iVar8 + 100) == *(int *)(iVar9 + 100))) {
        if (((*(char *)(iVar8 + 0x68) == -1) || (*(char *)(iVar9 + 0x68) == -1)) ||
           (*(char *)(iVar8 + 0x68) == *(char *)(iVar9 + 0x68))) {
          bVar5 = false;
        }
        else {
          bVar5 = true;
        }
      }
      else {
        bVar5 = true;
      }
      if (!bVar5) {
        bVar5 = false;
        if (((*(char *)(iVar8 + 0x44) == '\x04') || (*(char *)(iVar8 + 0x4c) == '\x04')) ||
           (*(char *)(iVar8 + 0x54) == '\x04')) {
          bVar5 = true;
        }
        if (bVar5) {
          bVar5 = false;
          if ((((*(char *)(iVar9 + 0x44) == '\x04') || (*(char *)(iVar9 + 0x4c) == '\x04')) ||
              (*(char *)(iVar9 + 0x54) == '\x04')) || (*(char *)(iVar9 + 0x5c) == '\x04')) {
            bVar5 = true;
          }
          if (bVar5) goto LAB_80263c88;
        }
        if ((*(char *)(iVar9 + 0x1d) == '\0') || (*(char *)(iVar9 + 0x1a) != '\x01')) {
          bVar3 = *(byte *)(iVar9 + 0x1c);
          if (bVar3 == 0) {
            if (((*(char *)(iVar8 + 0x45) == '\a') && (*(char *)(iVar8 + 0x55) == '\a')) ||
               ((*(char *)(iVar9 + 0x45) == '\a' && (*(char *)(iVar9 + 0x55) == '\a')))) {
              bVar3 = *(byte *)(iVar9 + 0x1b);
              bVar4 = *(byte *)(iVar8 + 0x1b);
              if (bVar3 == 2) {
                iVar13 = -1;
              }
              else if ((bVar3 < 2) && (bVar3 != 0)) {
                iVar13 = 1;
              }
              else {
                iVar13 = 0;
              }
              if (bVar4 == 2) {
                iVar13 = iVar13 + -1;
              }
              else if ((bVar4 < 2) && (bVar4 != 0)) {
                iVar13 = iVar13 + 1;
              }
              if (iVar13 == 0) {
                unaff_r29 = 0;
                bVar5 = true;
              }
              else if (iVar13 < 0) {
                if (iVar13 < -1) {
LAB_80263a38:
                  bVar5 = false;
                }
                else {
                  unaff_r29 = 2;
                  bVar5 = true;
                }
              }
              else {
                if (1 < iVar13) goto LAB_80263a38;
                unaff_r29 = 1;
                bVar5 = true;
              }
              if (bVar5) {
                unaff_r28 = *(undefined1 *)(iVar8 + 0x1c);
                goto LAB_80263b90;
              }
            }
          }
          else {
            if (((*(char *)(iVar8 + 0x45) != '\a') || (*(char *)(iVar8 + 0x4d) != '\a')) ||
               ((*(char *)(iVar8 + 0x55) != '\a' || (*(char *)(iVar8 + 0x1b) != '\0'))))
            goto LAB_80263c88;
            bVar4 = *(byte *)(iVar8 + 0x1c);
            if (bVar4 == 2) {
              iVar13 = 8;
            }
            else if (bVar4 < 2) {
              if (bVar4 == 0) {
                iVar13 = 2;
              }
              else {
                iVar13 = 4;
              }
            }
            else if (bVar4 < 4) {
              iVar13 = 1;
            }
            else {
              iVar13 = 2;
            }
            if (bVar3 == 2) {
              iVar14 = 8;
            }
            else if (bVar3 < 2) {
              if (bVar3 == 0) {
                iVar14 = 2;
              }
              else {
                iVar14 = 4;
              }
            }
            else if (bVar3 < 4) {
              iVar14 = 1;
            }
            else {
              iVar14 = 2;
            }
            uVar7 = iVar13 * iVar14 >> 1;
            if (uVar7 == 4) {
              unaff_r28 = 1;
LAB_80263b80:
              bVar5 = true;
            }
            else {
              if (uVar7 < 4) {
                if (uVar7 == 2) {
                  unaff_r28 = 0;
                }
                else {
                  if ((1 < uVar7) || (uVar7 == 0)) goto LAB_80263b78;
                  unaff_r28 = 3;
                }
                goto LAB_80263b80;
              }
              if (uVar7 == 8) {
                unaff_r28 = 2;
                goto LAB_80263b80;
              }
LAB_80263b78:
              bVar5 = false;
            }
            if (bVar5) {
              unaff_r29 = *(undefined1 *)(iVar9 + 0x1b);
LAB_80263b90:
              bVar6 = true;
              uVar10 = *(undefined4 *)(iVar9 + 0x60);
              *(undefined4 *)(iVar8 + 0x5c) = *(undefined4 *)(iVar9 + 0x5c);
              *(undefined4 *)(iVar8 + 0x60) = uVar10;
              gnt4_HSD_TExpRef_bl(*(int **)(iVar8 + 0x60),*(char *)(iVar8 + 0x5d));
              *(undefined1 *)(iVar8 + 0x1b) = unaff_r29;
              *(undefined1 *)(iVar8 + 0x1c) = unaff_r28;
              if (*(int *)(iVar8 + 100) == 0) {
                *(undefined4 *)(iVar8 + 100) = *(undefined4 *)(iVar9 + 100);
              }
              if (*(char *)(iVar8 + 0x68) == -1) {
                *(undefined1 *)(iVar8 + 0x68) = *(undefined1 *)(iVar9 + 0x68);
              }
              if (*(char *)(iVar8 + 0x1e) == -1) {
                *(undefined1 *)(iVar8 + 0x1e) = *(undefined1 *)(iVar9 + 0x1e);
              }
              if (*(char *)(iVar8 + 0x1f) == -1) {
                *(undefined1 *)(iVar8 + 0x1f) = *(undefined1 *)(iVar9 + 0x1f);
              }
              if (((*(char *)(iVar9 + 0x45) != '\a') || (*(char *)(iVar9 + 0x4d) != '\a')) ||
                 (*(char *)(iVar9 + 0x55) != '\a')) {
                iVar14 = 0;
                iVar13 = iVar8;
                do {
                  uVar10 = *(undefined4 *)(iVar9 + 0x48);
                  *(undefined4 *)(iVar13 + 0x44) = *(undefined4 *)(iVar9 + 0x44);
                  *(undefined4 *)(iVar13 + 0x48) = uVar10;
                  gnt4_HSD_TExpRef_bl(*(int **)(iVar13 + 0x48),*(char *)(iVar13 + 0x45));
                  gnt4_HSD_TExpUnref_bl();
                  iVar14 = iVar14 + 1;
                  iVar9 = iVar9 + 8;
                  iVar13 = iVar13 + 8;
                } while (iVar14 < 3);
              }
              gnt4_HSD_TExpUnref_bl();
            }
          }
        }
        else {
          if (((*(char *)(iVar8 + 0x45) != '\a') || (*(char *)(iVar8 + 0x55) != '\a')) ||
             ((*(char *)(iVar8 + 0x1b) != '\0' || (bVar3 = *(byte *)(iVar8 + 0x1c), bVar3 == 3))))
          goto LAB_80263c88;
          bVar4 = *(byte *)(iVar9 + 0x1c);
          if (bVar3 == 2) {
            iVar13 = 8;
          }
          else if (bVar3 < 2) {
            if (bVar3 == 0) {
              iVar13 = 2;
            }
            else {
              iVar13 = 4;
            }
          }
          else if (bVar3 < 4) {
            iVar13 = 1;
          }
          else {
            iVar13 = 2;
          }
          if (bVar4 == 2) {
            iVar14 = 8;
          }
          else if (bVar4 < 2) {
            if (bVar4 == 0) {
              iVar14 = 2;
            }
            else {
              iVar14 = 4;
            }
          }
          else if (bVar4 < 4) {
            iVar14 = 1;
          }
          else {
            iVar14 = 2;
          }
          uVar7 = iVar13 * iVar14 >> 1;
          if (uVar7 == 4) {
            unaff_r28 = 1;
LAB_8026388c:
            bVar5 = true;
          }
          else {
            if (uVar7 < 4) {
              if (uVar7 == 2) {
                unaff_r28 = 0;
              }
              else {
                if ((1 < uVar7) || (uVar7 == 0)) goto LAB_80263884;
                unaff_r28 = 3;
              }
              goto LAB_8026388c;
            }
            if (uVar7 == 8) {
              unaff_r28 = 2;
              goto LAB_8026388c;
            }
LAB_80263884:
            bVar5 = false;
          }
          if (bVar5) {
            bVar6 = true;
            *(undefined1 *)(iVar8 + 0x1b) = *(undefined1 *)(iVar9 + 0x1b);
            *(undefined1 *)(iVar8 + 0x1c) = unaff_r28;
            if (*(char *)(iVar8 + 0x1a) != '\x01') {
              *(undefined1 *)(iVar8 + 0x1a) = *(undefined1 *)(iVar9 + 0x1a);
            }
            if (*(int *)(iVar8 + 100) == 0) {
              *(undefined4 *)(iVar8 + 100) = *(undefined4 *)(iVar9 + 100);
            }
            if (*(char *)(iVar8 + 0x68) == -1) {
              *(undefined1 *)(iVar8 + 0x68) = *(undefined1 *)(iVar9 + 0x68);
            }
            if (*(char *)(iVar8 + 0x1e) == -1) {
              *(undefined1 *)(iVar8 + 0x1e) = *(undefined1 *)(iVar9 + 0x1e);
            }
            if (*(char *)(iVar8 + 0x1f) == -1) {
              *(undefined1 *)(iVar8 + 0x1f) = *(undefined1 *)(iVar9 + 0x1f);
            }
            iVar14 = 0;
            iVar13 = iVar8;
            do {
              uVar10 = *(undefined4 *)(iVar9 + 0x48);
              *(undefined4 *)(iVar13 + 0x44) = *(undefined4 *)(iVar9 + 0x44);
              *(undefined4 *)(iVar13 + 0x48) = uVar10;
              gnt4_HSD_TExpRef_bl(*(int **)(iVar13 + 0x48),*(char *)(iVar13 + 0x45));
              gnt4_HSD_TExpUnref_bl();
              iVar14 = iVar14 + 1;
              iVar9 = iVar9 + 8;
              iVar13 = iVar13 + 8;
            } while (iVar14 < 4);
          }
        }
      }
    }
LAB_80263c88:
    if (!bVar6) {
      gnt4__restgpr_20_bl();
      return;
    }
  } while( true );
}



// ==== 80263cb8  gnt4-CalcTevRange-bl ====

void gnt4_CalcTevRange_bl(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = 0;
  if (*(char *)(param_1 + 0x3d) != '\a') {
    iVar2 = gnt4_HSD_TExpGetType_bl(*(undefined4 **)(param_1 + 0x40));
    if (iVar2 == 1) {
      if (*(char *)(param_1 + 0x3d) == '\x01') {
        if ((*(char *)(*(int *)(param_1 + 0x40) + 0xe) != '\x01') &&
           (*(char *)(*(int *)(param_1 + 0x40) + 0x11) == '\x01')) {
          *(undefined1 *)(param_1 + 0x11) = 1;
          goto LAB_80263e30;
        }
        uVar3 = 0x100;
      }
      else {
        if ((*(char *)(*(int *)(param_1 + 0x40) + 0x1a) != '\x01') &&
           (*(char *)(*(int *)(param_1 + 0x40) + 0x1d) == '\x01')) {
          *(undefined1 *)(param_1 + 0x11) = 1;
          goto LAB_80263e30;
        }
        uVar3 = 0x100;
      }
    }
    else {
      uVar3 = 0x100;
    }
  }
  iVar4 = 3;
  iVar2 = param_1;
  do {
    if (*(char *)(iVar2 + 0x25) != '\a') {
      if (*(char *)(param_1 + 0xd) == '\x01') {
        *(undefined1 *)(param_1 + 0x11) = 1;
        goto LAB_80263e30;
      }
      uVar3 = uVar3 + 0x100;
      break;
    }
    iVar2 = iVar2 + 8;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  bVar1 = *(byte *)(param_1 + 0xf);
  if (bVar1 == 2) {
    *(undefined1 *)(param_1 + 0x11) = 1;
  }
  else {
    if ((bVar1 < 2) && (bVar1 != 0)) {
      uVar3 = uVar3 + 0x80;
    }
    bVar1 = *(byte *)(param_1 + 0x10);
    if (bVar1 == 2) {
      uVar3 = uVar3 << 2;
    }
    else if (bVar1 < 2) {
      if (bVar1 != 0) {
        uVar3 = uVar3 << 1;
      }
    }
    else if (bVar1 < 4) {
      uVar3 = (int)uVar3 >> 1;
    }
    *(byte *)(param_1 + 0x11) =
         (byte)(((int)(uVar3 ^ 0x100) >> 1) - ((uVar3 ^ 0x100) & uVar3) >> 0x1f);
  }
LAB_80263e30:
  uVar3 = 0;
  if (*(char *)(param_1 + 0x5d) != '\a') {
    iVar2 = gnt4_HSD_TExpGetType_bl(*(undefined4 **)(param_1 + 0x60));
    if (iVar2 == 1) {
      if ((*(char *)(*(int *)(param_1 + 0x60) + 0x1a) != '\x01') &&
         (*(char *)(*(int *)(param_1 + 0x60) + 0x1d) == '\x01')) {
        *(undefined1 *)(param_1 + 0x1d) = 1;
        return;
      }
      uVar3 = 0x100;
    }
    else {
      uVar3 = 0x100;
    }
  }
  iVar4 = 3;
  iVar2 = param_1;
  do {
    if (*(char *)(iVar2 + 0x45) != '\a') {
      if (*(char *)(param_1 + 0x19) == '\x01') {
        *(undefined1 *)(param_1 + 0x1d) = 1;
        return;
      }
      uVar3 = uVar3 + 0x100;
      break;
    }
    iVar2 = iVar2 + 8;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  bVar1 = *(byte *)(param_1 + 0x1b);
  if (bVar1 == 2) {
    *(undefined1 *)(param_1 + 0x1d) = 1;
  }
  else {
    if ((bVar1 < 2) && (bVar1 != 0)) {
      uVar3 = uVar3 + 0x80;
    }
    bVar1 = *(byte *)(param_1 + 0x1c);
    if (bVar1 == 2) {
      uVar3 = uVar3 << 2;
    }
    else if (bVar1 < 2) {
      if (bVar1 != 0) {
        uVar3 = uVar3 << 1;
      }
    }
    else if (bVar1 < 4) {
      uVar3 = (int)uVar3 >> 1;
    }
    *(byte *)(param_1 + 0x1d) =
         (byte)(((int)(uVar3 ^ 0x100) >> 1) - ((uVar3 ^ 0x100) & uVar3) >> 0x1f);
  }
  return;
}



// ==== 80263f6c  gnt4-HSD_TExpSimplify-bl ====

bool gnt4_HSD_TExpSimplify_bl(undefined4 *param_1)

{
  int iVar1;
  bool bVar4;
  int iVar2;
  int iVar3;
  
  iVar1 = gnt4_HSD_TExpGetType_bl(param_1);
  if (iVar1 == 1) {
    iVar1 = gnt4_SimplifySrc_bl();
    iVar2 = gnt4_SimplifyThis_bl((int)param_1);
    iVar3 = gnt4_SimplifyByMerge_bl();
    bVar4 = iVar3 != 0 || (iVar2 != 0 || iVar1 != 0);
    gnt4_CalcTevRange_bl((int)param_1);
  }
  else {
    bVar4 = false;
  }
  return bVar4;
}



// ==== 80263ffc  gnt4-HSD_TExpSimplify2-bl ====

void gnt4_HSD_TExpSimplify2_bl(void)

{
  byte bVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar4 = gnt4__savegpr_27_bl();
  iVar7 = 0;
  iVar6 = iVar4;
  do {
    iVar5 = *(int *)(iVar6 + 0x28);
    if ((*(char *)(iVar6 + 0x24) == '\x01') && (*(char *)(iVar6 + 0x25) == '\x01')) {
      bVar2 = false;
      if ((*(char *)(iVar5 + 0xd) == '\0') &&
         ((((*(char *)(iVar5 + 0x25) == '\a' && (*(char *)(iVar5 + 0x2d) == '\a')) &&
           (*(char *)(iVar5 + 0xf) == '\0')) && (*(char *)(iVar5 + 0x10) == '\0')))) {
        bVar2 = true;
      }
      if (bVar2) {
        bVar1 = *(byte *)(iVar5 + 0x3c);
        if (bVar1 == 6) {
          if (*(char *)(iVar4 + 0x20) == -1) {
            *(undefined1 *)(iVar4 + 0x20) = *(undefined1 *)(iVar5 + 0x20);
          }
          else if (*(char *)(iVar4 + 0x20) != *(char *)(iVar5 + 0x20)) goto LAB_802640ec;
        }
        else if ((5 < bVar1) || (bVar1 < 5)) goto LAB_802640ec;
        uVar3 = *(undefined4 *)(iVar5 + 0x40);
        *(undefined4 *)(iVar6 + 0x24) = *(undefined4 *)(iVar5 + 0x3c);
        *(undefined4 *)(iVar6 + 0x28) = uVar3;
        gnt4_HSD_TExpRef_bl(*(int **)(iVar6 + 0x28),*(char *)(iVar6 + 0x25));
        gnt4_HSD_TExpUnref_bl();
      }
    }
LAB_802640ec:
    iVar7 = iVar7 + 1;
    iVar6 = iVar6 + 8;
  } while (iVar7 < 4);
  iVar7 = 0;
  iVar6 = iVar4;
  do {
    iVar5 = *(int *)(iVar6 + 0x48);
    if (*(char *)(iVar6 + 0x44) == '\x01') {
      bVar2 = false;
      if (((*(char *)(iVar5 + 0x19) == '\0') && (*(char *)(iVar5 + 0x45) == '\a')) &&
         ((*(char *)(iVar5 + 0x4d) == '\a' &&
          ((*(char *)(iVar5 + 0x1b) == '\0' && (*(char *)(iVar5 + 0x1c) == '\0')))))) {
        bVar2 = true;
      }
      if (bVar2) {
        bVar1 = *(byte *)(iVar5 + 0x5c);
        if (bVar1 == 6) {
          if (*(char *)(iVar4 + 0x21) == -1) {
            *(undefined1 *)(iVar4 + 0x21) = *(undefined1 *)(iVar5 + 0x21);
          }
          else if (*(char *)(iVar4 + 0x21) != *(char *)(iVar5 + 0x21)) goto LAB_802641cc;
        }
        else if ((5 < bVar1) || (bVar1 < 5)) goto LAB_802641cc;
        uVar3 = *(undefined4 *)(iVar5 + 0x60);
        *(undefined4 *)(iVar6 + 0x44) = *(undefined4 *)(iVar5 + 0x5c);
        *(undefined4 *)(iVar6 + 0x48) = uVar3;
        gnt4_HSD_TExpRef_bl(*(int **)(iVar6 + 0x48),*(char *)(iVar6 + 0x45));
        gnt4_HSD_TExpUnref_bl();
      }
    }
LAB_802641cc:
    iVar7 = iVar7 + 1;
    iVar6 = iVar6 + 8;
    if (3 < iVar7) {
      gnt4__restgpr_27_bl();
      return;
    }
  } while( true );
}



// ==== 802641f8  gnt4-HSD_SaveContext-bl ====

void gnt4_HSD_SaveContext_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 in_r0;
  undefined4 in_r11;
  undefined4 in_r12;
  undefined4 unaff_r14;
  undefined4 unaff_r15;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  undefined4 unaff_r19;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  undefined4 unaff_r22;
  undefined4 unaff_r23;
  undefined4 unaff_r24;
  undefined4 unaff_r25;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  undefined4 in_XER;
  undefined4 in_LR;
  undefined4 in_CTR;
  undefined4 in_SRR0;
  undefined4 in_SRR1;
  
  DAT_803fa798 = &DAT_8043ea20;
  DAT_803fa7c4 = &FLOAT_8043b5a0;
  DAT_803fa934 = 0;
  DAT_803fa938 = 0;
  DAT_803fa93c = 0x40004;
  DAT_803fa940 = 0x50005;
  DAT_803fa944 = 0x60006;
  DAT_803fa948 = 0x70007;
  DAT_803fa94c = 0;
  DAT_803fa950 = 0;
  DAT_803fa810 = (uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
                 (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 |
                 (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
                 (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf);
  DAT_803fa932 = DAT_803fa932 | 1;
  DAT_803fa790 = in_r0;
  DAT_803fa794 = (undefined1 *)register0x00000004;
  DAT_803fa79c = param_9;
  DAT_803fa7a0 = param_10;
  DAT_803fa7a4 = param_11;
  DAT_803fa7a8 = param_12;
  DAT_803fa7ac = param_13;
  DAT_803fa7b0 = param_14;
  DAT_803fa7b4 = param_15;
  DAT_803fa7b8 = param_16;
  DAT_803fa7bc = in_r11;
  DAT_803fa7c0 = in_r12;
  DAT_803fa7c8 = unaff_r14;
  DAT_803fa7cc = unaff_r15;
  DAT_803fa7d0 = unaff_r16;
  DAT_803fa7d4 = unaff_r17;
  DAT_803fa7d8 = unaff_r18;
  DAT_803fa7dc = unaff_r19;
  DAT_803fa7e0 = unaff_r20;
  DAT_803fa7e4 = unaff_r21;
  DAT_803fa7e8 = unaff_r22;
  DAT_803fa7ec = unaff_r23;
  DAT_803fa7f0 = unaff_r24;
  DAT_803fa7f4 = unaff_r25;
  DAT_803fa7f8 = unaff_r26;
  DAT_803fa7fc = unaff_r27;
  DAT_803fa800 = unaff_r28;
  DAT_803fa804 = unaff_r29;
  DAT_803fa808 = unaff_r30;
  DAT_803fa80c = unaff_r31;
  DAT_803fa814 = in_LR;
  DAT_803fa818 = in_CTR;
  DAT_803fa81c = in_XER;
  DAT_803fa928 = in_SRR0;
  DAT_803fa92c = in_SRR1;
  gnt4_OSFillFPUContext_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc05870);
  return;
}



// ==== 80264290  gnt4-__assert-bl ====

void gnt4___assert_bl(undefined8 param_1,double param_2,double param_3,double param_4,double param_5
                     ,double param_6,double param_7,double param_8,undefined4 param_9,
                     undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                     ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  double dVar2;
  
  uVar1 = 0x803b0000;
  dVar2 = (double)gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   s_assertion___s__failed_803adc78,param_11,param_11,0x803b0000,
                                   param_13,param_14,param_15,param_16);
  gnt4_HSD_Panic_bl(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                    &DAT_804360a0,uVar1,param_13,param_14,param_15,param_16);
  return;
}



// ==== 802642ec  gnt4-HSD_Panic-bl ====

void gnt4_HSD_Panic_bl(double param_1,double param_2,double param_3,double param_4,double param_5,
                      double param_6,double param_7,double param_8,undefined4 param_9,
                      undefined4 param_10,char *param_11,undefined4 param_12,undefined4 param_13,
                      undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  if (DAT_80436a18 != (code *)0x0) {
    uVar1 = gnt4_HSD_SaveContext_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    param_12 = param_10;
    gnt4_OSReport_bl(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s__s_in__s_on_line__d__803adc90,param_11,param_9,param_10,param_13,param_14,
                     param_15,param_16);
    param_1 = (double)(*DAT_80436a18)(&DAT_803fa790);
  }
  gnt4_OSPanic(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80264384  zz_0264384_ ====

void zz_0264384_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  undefined8 extraout_f1;
  
  DAT_803faa58 = DAT_803faa58 + -1;
  if (DAT_803faa58 == 0) {
    uVar1 = zz_0271598_();
    zz_0271ee0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    uVar1 = zz_026e0a8_();
    zz_0276410_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
                param_15,param_16);
    uVar1 = zz_026960c_();
    uVar1 = zz_02782d0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,1);
    uVar1 = zz_02782d0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,4,DAT_803faa64
                       );
    zz_02782d0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5,DAT_803faa60);
    zz_0277b44_();
    zz_02653b0_();
    zz_026a2d8_();
    zz_0276d5c_();
    zz_0277670_();
    uVar1 = zz_027771c_();
    zz_02695d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 80264414  zz_0264414_ ====

void zz_0264414_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  uint uVar1;
  undefined4 in_r6;
  undefined4 uVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  
  if (DAT_803faa58 == 0) {
    zz_0269650_();
    zz_026960c_();
    zz_0277764_();
    zz_02776b8_();
    zz_0276da4_();
    zz_026a320_();
    zz_026e0ac_();
    zz_02653e0_();
    zz_0271f7c_();
    zz_02715b8_();
    zz_02764b4_();
    zz_0277bec_();
    zz_0271578_(FUN_8026460c,0);
    uVar3 = zz_0275b24_(-0x7fd9ba18,0);
    gnt4_memset(&DAT_803faa6c,0,0xc00);
    uVar1 = zz_0270bb8_();
    if ((uVar1 == 1) && (DAT_803adca8 == 1)) {
      uVar2 = 0;
      uVar3 = zz_027811c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,1,
                          -0x7fd9ba8c,0,in_r7,in_r8,in_r9,in_r10);
      DAT_803faa64 = zz_0278418_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,4,
                                 -0x7fd9bab0,0,uVar2,in_r7,in_r8,in_r9,in_r10);
      DAT_803faa60 = zz_0278418_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5,
                                 -0x7fd9ba3c,0,uVar2,in_r7,in_r8,in_r9,in_r10);
    }
    else {
      DAT_803faa60 = zz_0278418_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5,
                                 -0x7fd9ba68,0,in_r6,in_r7,in_r8,in_r9,in_r10);
    }
    DAT_803faa68 = 0;
    zz_02695d4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  DAT_803faa58 = DAT_803faa58 + 1;
  return;
}



// ==== 80264550  FUN_80264550 ====

undefined4
FUN_80264550(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_026a368_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return 0;
}



