// ==== 802484cc  gnt4-CObjRelease-bl ====

void gnt4_CObjRelease_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8,int param_9,
                        undefined4 param_10,undefined4 param_11,undefined4 param_12,
                        undefined4 param_13,undefined4 param_14,undefined4 param_15,
                        undefined4 param_16)

{
  ushort uVar1;
  uint uVar2;
  int *piVar3;
  undefined8 uVar4;
  
  uVar4 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(undefined4 **)(param_9 + 0x84),param_10,param_11,param_12,param_13,
                              param_14,param_15,param_16);
  if (param_9 == 0) {
    uVar4 = gnt4___assert_bl(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80435e98,0x2d4,&DAT_80435ea0,param_12,param_13,param_14,param_15,
                             param_16);
  }
  piVar3 = *(int **)(param_9 + 0x24);
  if (piVar3 != (int *)0x0) {
    uVar1 = *(ushort *)(piVar3 + 1);
    uVar2 = countLeadingZeros(0xffff - (uint)uVar1);
    uVar2 = uVar2 >> 5;
    if (uVar2 == 0) {
      uVar2 = countLeadingZeros((uint)uVar1);
      *(ushort *)(piVar3 + 1) = uVar1 - 1;
      uVar2 = uVar2 >> 5;
    }
    if ((uVar2 != 0) && (piVar3 != (int *)0x0)) {
      (**(code **)(*piVar3 + 0x30))(piVar3);
      uVar4 = (**(code **)(*piVar3 + 0x34))(piVar3);
    }
  }
  if (param_9 == 0) {
    gnt4___assert_bl(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e98,700
                     ,&DAT_80435ea0,param_12,param_13,param_14,param_15,param_16);
  }
  piVar3 = *(int **)(param_9 + 0x28);
  if (piVar3 != (int *)0x0) {
    uVar1 = *(ushort *)(piVar3 + 1);
    uVar2 = countLeadingZeros(0xffff - (uint)uVar1);
    uVar2 = uVar2 >> 5;
    if (uVar2 == 0) {
      uVar2 = countLeadingZeros((uint)uVar1);
      *(ushort *)(piVar3 + 1) = uVar1 - 1;
      uVar2 = uVar2 >> 5;
    }
    if ((uVar2 != 0) && (piVar3 != (int *)0x0)) {
      (**(code **)(*piVar3 + 0x30))(piVar3);
      (**(code **)(*piVar3 + 0x34))(piVar3);
    }
  }
  if (*(undefined4 **)(param_9 + 0x88) != (undefined4 *)0x0) {
    gnt4_HSD_MtxFree_bl(*(undefined4 **)(param_9 + 0x88));
  }
  (**(code **)(DAT_803ac744 + 0x30))(param_9);
  return;
}



// ==== 80248650  gnt4-CObjAmnesia-bl ====

void gnt4_CObjAmnesia_bl(undefined **param_1)

{
  if (param_1 == DAT_80436958) {
    DAT_80436958 = (undefined **)0x0;
  }
  if (param_1 == &PTR_gnt4_CObjInfoInit_bl_803ac730) {
    DAT_8043695c = 0;
  }
  (**(code **)(DAT_803ac744 + 0x38))();
  return;
}



// ==== 802486b0  gnt4-CObjInfoInit-bl ====

void gnt4_CObjInfoInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc538d0,
             &PTR_zz_025acb8__803ad548,s_sysdolphin_base_library_803ac864,s_hsd_cobj_803ac87c,0x44,
             0x8c,in_r9,in_r10);
  DAT_803ac75c = gnt4_CObjInit_bl;
  DAT_803ac760 = gnt4_CObjRelease_bl;
  DAT_803ac768 = gnt4_CObjAmnesia_bl;
  DAT_803ac76c = gnt4_CObjLoad_bl;
  DAT_803ac770 = gnt4_CObjUpdateFunc_bl;
  return;
}



// ==== 8024873c  gnt4-HSD_FObjInitAllocData ====

void gnt4_HSD_FObjInitAllocData
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_HSD_ObjAllocInit_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803f8de8,0x30,4,
             in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 8024876c  gnt4-HSD_FObjRemove ====

void gnt4_HSD_FObjRemove(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    gnt4_HSD_FObjFree(param_1);
  }
  return;
}



// ==== 80248794  gnt4-HSD_FObjRemoveAll ====

void gnt4_HSD_FObjRemoveAll(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  
  puVar1 = (undefined4 *)gnt4__savegpr_23_bl();
  if (puVar1 != (undefined4 *)0x0) {
    puVar9 = (undefined4 *)*puVar1;
    if (puVar9 != (undefined4 *)0x0) {
      puVar8 = (undefined4 *)*puVar9;
      if (puVar8 != (undefined4 *)0x0) {
        puVar7 = (undefined4 *)*puVar8;
        if (puVar7 != (undefined4 *)0x0) {
          puVar6 = (undefined4 *)*puVar7;
          if (puVar6 != (undefined4 *)0x0) {
            puVar5 = (undefined4 *)*puVar6;
            if (puVar5 != (undefined4 *)0x0) {
              puVar4 = (undefined4 *)*puVar5;
              if (puVar4 != (undefined4 *)0x0) {
                puVar3 = (undefined4 *)*puVar4;
                if (puVar3 != (undefined4 *)0x0) {
                  puVar2 = (undefined4 *)*puVar3;
                  if (puVar2 != (undefined4 *)0x0) {
                    gnt4_HSD_FObjRemoveAll();
                    gnt4_HSD_FObjRemove(puVar2);
                  }
                  if (puVar3 != (undefined4 *)0x0) {
                    gnt4_HSD_FObjFree(puVar3);
                  }
                }
                if (puVar4 != (undefined4 *)0x0) {
                  gnt4_HSD_FObjFree(puVar4);
                }
              }
              if (puVar5 != (undefined4 *)0x0) {
                gnt4_HSD_FObjFree(puVar5);
              }
            }
            if (puVar6 != (undefined4 *)0x0) {
              gnt4_HSD_FObjFree(puVar6);
            }
          }
          if (puVar7 != (undefined4 *)0x0) {
            gnt4_HSD_FObjFree(puVar7);
          }
        }
        if (puVar8 != (undefined4 *)0x0) {
          gnt4_HSD_FObjFree(puVar8);
        }
      }
      if (puVar9 != (undefined4 *)0x0) {
        gnt4_HSD_FObjFree(puVar9);
      }
    }
    if (puVar1 != (undefined4 *)0x0) {
      gnt4_HSD_FObjFree(puVar1);
    }
  }
  gnt4__restgpr_23_bl();
  return;
}



// ==== 802488b8  gnt4-HSD_FObjReqAnimAll ====

void gnt4_HSD_FObjReqAnimAll(double param_1,undefined4 *param_2)

{
  float fVar1;
  double dVar2;
  
  if (param_2 != (undefined4 *)0x0) {
    for (; dVar2 = DOUBLE_8043d2a0, param_2 != (undefined4 *)0x0; param_2 = (undefined4 *)*param_2)
    {
      if (param_2 != (undefined4 *)0x0) {
        param_2[1] = param_2[2];
        fVar1 = FLOAT_8043d298;
        param_2[7] = (float)((double)(float)((double)CONCAT44(0x43300000,
                                                              (int)*(short *)(param_2 + 6) ^
                                                              0x80000000) - dVar2) + param_1);
        *(undefined1 *)((int)param_2 + 0x11) = 0;
        *(undefined1 *)((int)param_2 + 0x12) = 0;
        *(byte *)(param_2 + 4) = *(byte *)(param_2 + 4) & 0xbf;
        *(undefined2 *)((int)param_2 + 0x16) = 0;
        *(undefined2 *)((int)param_2 + 0x1a) = 0;
        param_2[8] = fVar1;
        param_2[9] = fVar1;
        param_2[10] = fVar1;
        param_2[0xb] = fVar1;
        *(byte *)(param_2 + 4) = *(byte *)(param_2 + 4) & 0xf0 | 1;
      }
    }
  }
  return;
}



// ==== 8024895c  gnt4-HSD_FObjStopAnimAll ====

void gnt4_HSD_FObjStopAnimAll
               (double param_1,undefined8 param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,uint param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  for (; param_9 != (undefined4 *)0x0; param_9 = (undefined4 *)*param_9) {
    if (param_9 != (undefined4 *)0x0) {
      if (*(char *)((int)param_9 + 0x12) == '\x06') {
        gnt4_HSD_FObjInterpretAnim_bl
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
                   param_10,param_11,param_12,param_13,param_14,param_15,param_16);
      }
      if (param_9 != (undefined4 *)0x0) {
        *(byte *)(param_9 + 4) = *(byte *)(param_9 + 4) & 0xf0;
      }
    }
  }
  return;
}



// ==== 802489f4  gnt4-FObjLoadData ====

uint gnt4_FObjLoadData(undefined8 param_1,double param_2,double param_3,double param_4,
                      double param_5,double param_6,double param_7,double param_8,int param_9,
                      undefined4 param_10,undefined4 param_11,undefined4 param_12,
                      undefined4 param_13,undefined4 param_14,undefined4 param_15,
                      undefined4 param_16)

{
  float fVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  char cVar6;
  double dVar7;
  double dVar8;
  int iVar9;
  byte bVar10;
  byte *pbVar11;
  undefined1 *puVar12;
  int iVar13;
  undefined1 *puVar14;
  int iVar15;
  uint uVar17;
  undefined2 uVar16;
  
  if (*(uint *)(param_9 + 0xc) <= (uint)(*(int *)(param_9 + 4) - *(int *)(param_9 + 8))) {
    return 6;
  }
  *(undefined1 *)(param_9 + 0x12) = *(undefined1 *)(param_9 + 0x11);
  if (*(short *)(param_9 + 0x16) == 0) {
    iVar13 = 3;
    *(byte *)(param_9 + 0x11) = **(byte **)(param_9 + 4) & 0xf;
    pbVar11 = *(byte **)(param_9 + 4);
    *(byte **)(param_9 + 4) = pbVar11 + 1;
    bVar2 = *pbVar11;
    iVar15 = (bVar2 >> 4 & 7) + 1;
    uVar16 = (undefined2)iVar15;
    while ((bVar2 & 0x80) != 0) {
      pbVar11 = *(byte **)(param_9 + 4);
      *(byte **)(param_9 + 4) = pbVar11 + 1;
      bVar2 = *pbVar11;
      iVar9 = (bVar2 & 0x7f) << iVar13;
      iVar13 = iVar13 + 7;
      iVar15 = iVar15 + iVar9;
      uVar16 = (undefined2)iVar15;
    }
    *(undefined2 *)(param_9 + 0x16) = uVar16;
  }
  *(short *)(param_9 + 0x16) = *(short *)(param_9 + 0x16) + -1;
  bVar2 = *(byte *)(param_9 + 0x11);
  if (bVar2 != 4) {
    if (3 < bVar2) {
      if (bVar2 != 6) {
        if (5 < bVar2) {
          return 0;
        }
        if (param_9 == 0) {
          uVar17 = 0;
        }
        else {
          uVar17 = *(byte *)(param_9 + 0x10) & 0xf;
        }
        if (-1 < (int)((~(uVar17 - 1) | 1) - (1 - (uVar17 - 1) >> 1))) {
          gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80435eb0,0x1cc,s_st____FOBJ_LOAD_DATA0____st____F_803ac8a0,param_12,
                           param_13,param_14,param_15,param_16);
        }
        *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x2c);
        dVar8 = DOUBLE_8043d2a8;
        dVar7 = DOUBLE_8043d2a0;
        bVar2 = *(byte *)(param_9 + 0x15);
        if (bVar2 == 0) {
          puVar12 = *(undefined1 **)(param_9 + 4);
          *(undefined1 **)(param_9 + 4) = puVar12 + 1;
          puVar14 = *(undefined1 **)(param_9 + 4);
          uVar3 = *puVar12;
          *(undefined1 **)(param_9 + 4) = puVar14 + 1;
          puVar12 = *(undefined1 **)(param_9 + 4);
          uVar4 = *puVar14;
          *(undefined1 **)(param_9 + 4) = puVar12 + 1;
          uVar5 = *puVar12;
          puVar12 = *(undefined1 **)(param_9 + 4);
          *(undefined1 **)(param_9 + 4) = puVar12 + 1;
          fVar1 = (float)CONCAT13(*puVar12,CONCAT12(uVar5,CONCAT11(uVar4,uVar3)));
        }
        else {
          bVar10 = bVar2 & 0xe0;
          if (bVar10 == 0x60) {
            cVar6 = **(char **)(param_9 + 4);
            *(char **)(param_9 + 4) = *(char **)(param_9 + 4) + 1;
            fVar1 = (float)((double)CONCAT44(0x43300000,(int)cVar6 ^ 0x80000000) - dVar7);
          }
          else {
            fVar1 = FLOAT_8043d298;
            if (bVar10 < 0x60) {
              if (bVar10 == 0x40) {
                puVar12 = *(undefined1 **)(param_9 + 4);
                uVar3 = puVar12[1];
                uVar4 = *puVar12;
                *(undefined1 **)(param_9 + 4) = puVar12 + 2;
                fVar1 = (float)((double)CONCAT44(0x43300000,CONCAT11(uVar3,uVar4) ^ 0x80000000) -
                               dVar7);
              }
              else {
                if ((0x3f < bVar10) || (bVar10 != 0x20)) goto LAB_8024980c;
                puVar12 = *(undefined1 **)(param_9 + 4);
                uVar3 = puVar12[1];
                uVar4 = *puVar12;
                *(undefined1 **)(param_9 + 4) = puVar12 + 2;
                fVar1 = (float)((double)CONCAT44(0x43300000,(int)CONCAT11(uVar3,uVar4) ^ 0x80000000)
                               - dVar7);
              }
            }
            else {
              if (bVar10 != 0x80) goto LAB_8024980c;
              bVar10 = **(byte **)(param_9 + 4);
              *(byte **)(param_9 + 4) = *(byte **)(param_9 + 4) + 1;
              fVar1 = (float)((double)CONCAT44(0x43300000,(uint)bVar10) - dVar8);
            }
          }
          fVar1 = fVar1 / (float)((double)CONCAT44(0x43300000,1 << (bVar2 & 0x1f) ^ 0x80000000) -
                                 DOUBLE_8043d2a0);
        }
LAB_8024980c:
        *(float *)(param_9 + 0x2c) = fVar1;
        if (param_9 != 0) {
          return *(byte *)(param_9 + 0x10) & 0xf;
        }
        return 0;
      }
      if (param_9 == 0) {
        uVar17 = 0;
      }
      else {
        uVar17 = *(byte *)(param_9 + 0x10) & 0xf;
      }
      if (-1 < (int)((~(uVar17 - 1) | 1) - (1 - (uVar17 - 1) >> 1))) {
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435eb0,0x1e9,s_st____FOBJ_LOAD_DATA0____st____F_803ac8a0,param_12,
                         param_13,param_14,param_15,param_16);
      }
      if ((*(byte *)(param_9 + 0x10) & 0x40) != 0) {
        *(undefined1 *)(param_9 + 0x12) = *(undefined1 *)(param_9 + 0x11);
        *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xbf;
        *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) | 0x80;
        *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x24);
      }
      dVar8 = DOUBLE_8043d2a8;
      dVar7 = DOUBLE_8043d2a0;
      bVar2 = *(byte *)(param_9 + 0x14);
      if (bVar2 == 0) {
        puVar12 = *(undefined1 **)(param_9 + 4);
        *(undefined1 **)(param_9 + 4) = puVar12 + 1;
        puVar14 = *(undefined1 **)(param_9 + 4);
        uVar3 = *puVar12;
        *(undefined1 **)(param_9 + 4) = puVar14 + 1;
        puVar12 = *(undefined1 **)(param_9 + 4);
        uVar4 = *puVar14;
        *(undefined1 **)(param_9 + 4) = puVar12 + 1;
        uVar5 = *puVar12;
        puVar12 = *(undefined1 **)(param_9 + 4);
        *(undefined1 **)(param_9 + 4) = puVar12 + 1;
        fVar1 = (float)CONCAT13(*puVar12,CONCAT12(uVar5,CONCAT11(uVar4,uVar3)));
      }
      else {
        bVar10 = bVar2 & 0xe0;
        if (bVar10 == 0x60) {
          cVar6 = **(char **)(param_9 + 4);
          *(char **)(param_9 + 4) = *(char **)(param_9 + 4) + 1;
          fVar1 = (float)((double)CONCAT44(0x43300000,(int)cVar6 ^ 0x80000000) - dVar7);
        }
        else {
          fVar1 = FLOAT_8043d298;
          if (bVar10 < 0x60) {
            if (bVar10 == 0x40) {
              puVar12 = *(undefined1 **)(param_9 + 4);
              uVar3 = puVar12[1];
              uVar4 = *puVar12;
              *(undefined1 **)(param_9 + 4) = puVar12 + 2;
              fVar1 = (float)((double)CONCAT44(0x43300000,CONCAT11(uVar3,uVar4) ^ 0x80000000) -
                             dVar7);
            }
            else {
              if ((0x3f < bVar10) || (bVar10 != 0x20)) goto LAB_80249a68;
              puVar12 = *(undefined1 **)(param_9 + 4);
              uVar3 = puVar12[1];
              uVar4 = *puVar12;
              *(undefined1 **)(param_9 + 4) = puVar12 + 2;
              fVar1 = (float)((double)CONCAT44(0x43300000,(int)CONCAT11(uVar3,uVar4) ^ 0x80000000) -
                             dVar7);
            }
          }
          else {
            if (bVar10 != 0x80) goto LAB_80249a68;
            bVar10 = **(byte **)(param_9 + 4);
            *(byte **)(param_9 + 4) = *(byte **)(param_9 + 4) + 1;
            fVar1 = (float)((double)CONCAT44(0x43300000,(uint)bVar10) - dVar8);
          }
        }
        fVar1 = fVar1 / (float)((double)CONCAT44(0x43300000,1 << (bVar2 & 0x1f) ^ 0x80000000) -
                               DOUBLE_8043d2a0);
      }
LAB_80249a68:
      *(float *)(param_9 + 0x24) = fVar1;
      *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) | 0x40;
      uVar17 = ((int)~(uVar17 - 1 | 1 - uVar17) >> 0x1f) + 4;
      if (param_9 != 0) {
        *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xf0 | (byte)uVar17 & 0xf;
        return uVar17;
      }
      return uVar17;
    }
    if (bVar2 != 2) {
      if (bVar2 < 2) {
        if (bVar2 == 0) {
          return 0;
        }
        if (param_9 == 0) {
          uVar17 = 0;
        }
        else {
          uVar17 = *(byte *)(param_9 + 0x10) & 0xf;
        }
        if (-1 < (int)((~(uVar17 - 1) | 1) - (1 - (uVar17 - 1) >> 1))) {
          gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80435eb0,0x17f,s_st____FOBJ_LOAD_DATA0____st____F_803ac8a0,param_12,
                           param_13,param_14,param_15,param_16);
        }
        *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x24);
        dVar8 = DOUBLE_8043d2a8;
        dVar7 = DOUBLE_8043d2a0;
        bVar2 = *(byte *)(param_9 + 0x14);
        if (bVar2 == 0) {
          puVar12 = *(undefined1 **)(param_9 + 4);
          *(undefined1 **)(param_9 + 4) = puVar12 + 1;
          puVar14 = *(undefined1 **)(param_9 + 4);
          uVar3 = *puVar12;
          *(undefined1 **)(param_9 + 4) = puVar14 + 1;
          puVar12 = *(undefined1 **)(param_9 + 4);
          uVar4 = *puVar14;
          *(undefined1 **)(param_9 + 4) = puVar12 + 1;
          uVar5 = *puVar12;
          puVar12 = *(undefined1 **)(param_9 + 4);
          *(undefined1 **)(param_9 + 4) = puVar12 + 1;
          fVar1 = (float)CONCAT13(*puVar12,CONCAT12(uVar5,CONCAT11(uVar4,uVar3)));
        }
        else {
          bVar10 = bVar2 & 0xe0;
          if (bVar10 == 0x60) {
            cVar6 = **(char **)(param_9 + 4);
            *(char **)(param_9 + 4) = *(char **)(param_9 + 4) + 1;
            fVar1 = (float)((double)CONCAT44(0x43300000,(int)cVar6 ^ 0x80000000) - dVar7);
          }
          else {
            fVar1 = FLOAT_8043d298;
            if (bVar10 < 0x60) {
              if (bVar10 == 0x40) {
                puVar12 = *(undefined1 **)(param_9 + 4);
                uVar3 = puVar12[1];
                uVar4 = *puVar12;
                *(undefined1 **)(param_9 + 4) = puVar12 + 2;
                fVar1 = (float)((double)CONCAT44(0x43300000,CONCAT11(uVar3,uVar4) ^ 0x80000000) -
                               dVar7);
              }
              else {
                if ((0x3f < bVar10) || (bVar10 != 0x20)) goto LAB_80248cf8;
                puVar12 = *(undefined1 **)(param_9 + 4);
                uVar3 = puVar12[1];
                uVar4 = *puVar12;
                *(undefined1 **)(param_9 + 4) = puVar12 + 2;
                fVar1 = (float)((double)CONCAT44(0x43300000,(int)CONCAT11(uVar3,uVar4) ^ 0x80000000)
                               - dVar7);
              }
            }
            else {
              if (bVar10 != 0x80) goto LAB_80248cf8;
              bVar10 = **(byte **)(param_9 + 4);
              *(byte **)(param_9 + 4) = *(byte **)(param_9 + 4) + 1;
              fVar1 = (float)((double)CONCAT44(0x43300000,(uint)bVar10) - dVar8);
            }
          }
          fVar1 = fVar1 / (float)((double)CONCAT44(0x43300000,1 << (bVar2 & 0x1f) ^ 0x80000000) -
                                 DOUBLE_8043d2a0);
        }
LAB_80248cf8:
        *(float *)(param_9 + 0x24) = fVar1;
        fVar1 = FLOAT_8043d298;
        if (*(char *)(param_9 + 0x12) != '\x05') {
          *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x2c);
          *(float *)(param_9 + 0x2c) = fVar1;
        }
        uVar17 = ((int)~(uVar17 - 1 | 1 - uVar17) >> 0x1f) + 4;
        if (param_9 != 0) {
          *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xf0 | (byte)uVar17 & 0xf;
          return uVar17;
        }
        return uVar17;
      }
      if (param_9 == 0) {
        uVar17 = 0;
      }
      else {
        uVar17 = *(byte *)(param_9 + 0x10) & 0xf;
      }
      if (-1 < (int)((~(uVar17 - 1) | 1) - (1 - (uVar17 - 1) >> 1))) {
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435eb0,0x1a7,s_st____FOBJ_LOAD_DATA0____st____F_803ac8a0,param_12,
                         param_13,param_14,param_15,param_16);
      }
      *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x24);
      *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x2c);
      dVar8 = DOUBLE_8043d2a8;
      dVar7 = DOUBLE_8043d2a0;
      bVar2 = *(byte *)(param_9 + 0x14);
      if (bVar2 == 0) {
        puVar12 = *(undefined1 **)(param_9 + 4);
        *(undefined1 **)(param_9 + 4) = puVar12 + 1;
        puVar14 = *(undefined1 **)(param_9 + 4);
        uVar3 = *puVar12;
        *(undefined1 **)(param_9 + 4) = puVar14 + 1;
        puVar12 = *(undefined1 **)(param_9 + 4);
        uVar4 = *puVar14;
        *(undefined1 **)(param_9 + 4) = puVar12 + 1;
        uVar5 = *puVar12;
        puVar12 = *(undefined1 **)(param_9 + 4);
        *(undefined1 **)(param_9 + 4) = puVar12 + 1;
        fVar1 = (float)CONCAT13(*puVar12,CONCAT12(uVar5,CONCAT11(uVar4,uVar3)));
      }
      else {
        bVar10 = bVar2 & 0xe0;
        if (bVar10 == 0x60) {
          cVar6 = **(char **)(param_9 + 4);
          *(char **)(param_9 + 4) = *(char **)(param_9 + 4) + 1;
          fVar1 = (float)((double)CONCAT44(0x43300000,(int)cVar6 ^ 0x80000000) - dVar7);
        }
        else {
          fVar1 = FLOAT_8043d298;
          if (bVar10 < 0x60) {
            if (bVar10 == 0x40) {
              puVar12 = *(undefined1 **)(param_9 + 4);
              uVar3 = puVar12[1];
              uVar4 = *puVar12;
              *(undefined1 **)(param_9 + 4) = puVar12 + 2;
              fVar1 = (float)((double)CONCAT44(0x43300000,CONCAT11(uVar3,uVar4) ^ 0x80000000) -
                             dVar7);
            }
            else {
              if ((0x3f < bVar10) || (bVar10 != 0x20)) goto LAB_802491c0;
              puVar12 = *(undefined1 **)(param_9 + 4);
              uVar3 = puVar12[1];
              uVar4 = *puVar12;
              *(undefined1 **)(param_9 + 4) = puVar12 + 2;
              fVar1 = (float)((double)CONCAT44(0x43300000,(int)CONCAT11(uVar3,uVar4) ^ 0x80000000) -
                             dVar7);
            }
          }
          else {
            if (bVar10 != 0x80) goto LAB_802491c0;
            bVar10 = **(byte **)(param_9 + 4);
            *(byte **)(param_9 + 4) = *(byte **)(param_9 + 4) + 1;
            fVar1 = (float)((double)CONCAT44(0x43300000,(uint)bVar10) - dVar8);
          }
        }
        fVar1 = fVar1 / (float)((double)CONCAT44(0x43300000,1 << (bVar2 & 0x1f) ^ 0x80000000) -
                               DOUBLE_8043d2a0);
      }
LAB_802491c0:
      *(float *)(param_9 + 0x24) = fVar1;
      *(float *)(param_9 + 0x2c) = FLOAT_8043d298;
      uVar17 = ((int)~(uVar17 - 1 | 1 - uVar17) >> 0x1f) + 4;
      if (param_9 != 0) {
        *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xf0 | (byte)uVar17 & 0xf;
        return uVar17;
      }
      return uVar17;
    }
    if (param_9 == 0) {
      uVar17 = 0;
    }
    else {
      uVar17 = *(byte *)(param_9 + 0x10) & 0xf;
    }
    if (-1 < (int)((~(uVar17 - 1) | 1) - (1 - (uVar17 - 1) >> 1))) {
      gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435eb0
                       ,0x193,s_st____FOBJ_LOAD_DATA0____st____F_803ac8a0,param_12,param_13,param_14
                       ,param_15,param_16);
    }
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x24);
    dVar8 = DOUBLE_8043d2a8;
    dVar7 = DOUBLE_8043d2a0;
    bVar2 = *(byte *)(param_9 + 0x14);
    if (bVar2 == 0) {
      puVar12 = *(undefined1 **)(param_9 + 4);
      *(undefined1 **)(param_9 + 4) = puVar12 + 1;
      puVar14 = *(undefined1 **)(param_9 + 4);
      uVar3 = *puVar12;
      *(undefined1 **)(param_9 + 4) = puVar14 + 1;
      puVar12 = *(undefined1 **)(param_9 + 4);
      uVar4 = *puVar14;
      *(undefined1 **)(param_9 + 4) = puVar12 + 1;
      uVar5 = *puVar12;
      puVar12 = *(undefined1 **)(param_9 + 4);
      *(undefined1 **)(param_9 + 4) = puVar12 + 1;
      fVar1 = (float)CONCAT13(*puVar12,CONCAT12(uVar5,CONCAT11(uVar4,uVar3)));
    }
    else {
      bVar10 = bVar2 & 0xe0;
      if (bVar10 == 0x60) {
        cVar6 = **(char **)(param_9 + 4);
        *(char **)(param_9 + 4) = *(char **)(param_9 + 4) + 1;
        fVar1 = (float)((double)CONCAT44(0x43300000,(int)cVar6 ^ 0x80000000) - dVar7);
      }
      else {
        fVar1 = FLOAT_8043d298;
        if (bVar10 < 0x60) {
          if (bVar10 == 0x40) {
            puVar12 = *(undefined1 **)(param_9 + 4);
            uVar3 = puVar12[1];
            uVar4 = *puVar12;
            *(undefined1 **)(param_9 + 4) = puVar12 + 2;
            fVar1 = (float)((double)CONCAT44(0x43300000,CONCAT11(uVar3,uVar4) ^ 0x80000000) - dVar7)
            ;
          }
          else {
            if ((0x3f < bVar10) || (bVar10 != 0x20)) goto LAB_80248f58;
            puVar12 = *(undefined1 **)(param_9 + 4);
            uVar3 = puVar12[1];
            uVar4 = *puVar12;
            *(undefined1 **)(param_9 + 4) = puVar12 + 2;
            fVar1 = (float)((double)CONCAT44(0x43300000,(int)CONCAT11(uVar3,uVar4) ^ 0x80000000) -
                           dVar7);
          }
        }
        else {
          if (bVar10 != 0x80) goto LAB_80248f58;
          bVar10 = **(byte **)(param_9 + 4);
          *(byte **)(param_9 + 4) = *(byte **)(param_9 + 4) + 1;
          fVar1 = (float)((double)CONCAT44(0x43300000,(uint)bVar10) - dVar8);
        }
      }
      fVar1 = fVar1 / (float)((double)CONCAT44(0x43300000,1 << (bVar2 & 0x1f) ^ 0x80000000) -
                             DOUBLE_8043d2a0);
    }
LAB_80248f58:
    *(float *)(param_9 + 0x24) = fVar1;
    fVar1 = FLOAT_8043d298;
    if (*(char *)(param_9 + 0x12) != '\x05') {
      *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x2c);
      *(float *)(param_9 + 0x2c) = fVar1;
    }
    uVar17 = ((int)~(uVar17 - 1 | 1 - uVar17) >> 0x1f) + 4;
    if (param_9 != 0) {
      *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xf0 | (byte)uVar17 & 0xf;
      return uVar17;
    }
    return uVar17;
  }
  if (param_9 == 0) {
    uVar17 = 0;
  }
  else {
    uVar17 = *(byte *)(param_9 + 0x10) & 0xf;
  }
  if (-1 < (int)((~(uVar17 - 1) | 1) - (1 - (uVar17 - 1) >> 1))) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435eb0,
                     0x1b9,s_st____FOBJ_LOAD_DATA0____st____F_803ac8a0,param_12,param_13,param_14,
                     param_15,param_16);
  }
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x24);
  dVar8 = DOUBLE_8043d2a8;
  dVar7 = DOUBLE_8043d2a0;
  bVar2 = *(byte *)(param_9 + 0x14);
  if (bVar2 == 0) {
    puVar12 = *(undefined1 **)(param_9 + 4);
    *(undefined1 **)(param_9 + 4) = puVar12 + 1;
    puVar14 = *(undefined1 **)(param_9 + 4);
    uVar3 = *puVar12;
    *(undefined1 **)(param_9 + 4) = puVar14 + 1;
    puVar12 = *(undefined1 **)(param_9 + 4);
    uVar4 = *puVar14;
    *(undefined1 **)(param_9 + 4) = puVar12 + 1;
    uVar5 = *puVar12;
    puVar12 = *(undefined1 **)(param_9 + 4);
    *(undefined1 **)(param_9 + 4) = puVar12 + 1;
    fVar1 = (float)CONCAT13(*puVar12,CONCAT12(uVar5,CONCAT11(uVar4,uVar3)));
  }
  else {
    bVar10 = bVar2 & 0xe0;
    if (bVar10 == 0x60) {
      cVar6 = **(char **)(param_9 + 4);
      *(char **)(param_9 + 4) = *(char **)(param_9 + 4) + 1;
      fVar1 = (float)((double)CONCAT44(0x43300000,(int)cVar6 ^ 0x80000000) - dVar7);
    }
    else {
      fVar1 = FLOAT_8043d298;
      if (bVar10 < 0x60) {
        if (bVar10 == 0x40) {
          puVar12 = *(undefined1 **)(param_9 + 4);
          uVar3 = puVar12[1];
          uVar4 = *puVar12;
          *(undefined1 **)(param_9 + 4) = puVar12 + 2;
          fVar1 = (float)((double)CONCAT44(0x43300000,CONCAT11(uVar3,uVar4) ^ 0x80000000) - dVar7);
        }
        else {
          if ((0x3f < bVar10) || (bVar10 != 0x20)) goto LAB_8024940c;
          puVar12 = *(undefined1 **)(param_9 + 4);
          uVar3 = puVar12[1];
          uVar4 = *puVar12;
          *(undefined1 **)(param_9 + 4) = puVar12 + 2;
          fVar1 = (float)((double)CONCAT44(0x43300000,(int)CONCAT11(uVar3,uVar4) ^ 0x80000000) -
                         dVar7);
        }
      }
      else {
        if (bVar10 != 0x80) goto LAB_8024940c;
        bVar10 = **(byte **)(param_9 + 4);
        *(byte **)(param_9 + 4) = *(byte **)(param_9 + 4) + 1;
        fVar1 = (float)((double)CONCAT44(0x43300000,(uint)bVar10) - dVar8);
      }
    }
    fVar1 = fVar1 / (float)((double)CONCAT44(0x43300000,1 << (bVar2 & 0x1f) ^ 0x80000000) -
                           DOUBLE_8043d2a0);
  }
LAB_8024940c:
  *(float *)(param_9 + 0x24) = fVar1;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x2c);
  dVar8 = DOUBLE_8043d2a8;
  dVar7 = DOUBLE_8043d2a0;
  bVar2 = *(byte *)(param_9 + 0x15);
  if (bVar2 == 0) {
    puVar12 = *(undefined1 **)(param_9 + 4);
    *(undefined1 **)(param_9 + 4) = puVar12 + 1;
    puVar14 = *(undefined1 **)(param_9 + 4);
    uVar3 = *puVar12;
    *(undefined1 **)(param_9 + 4) = puVar14 + 1;
    puVar12 = *(undefined1 **)(param_9 + 4);
    uVar4 = *puVar14;
    *(undefined1 **)(param_9 + 4) = puVar12 + 1;
    uVar5 = *puVar12;
    puVar12 = *(undefined1 **)(param_9 + 4);
    *(undefined1 **)(param_9 + 4) = puVar12 + 1;
    fVar1 = (float)CONCAT13(*puVar12,CONCAT12(uVar5,CONCAT11(uVar4,uVar3)));
  }
  else {
    bVar10 = bVar2 & 0xe0;
    if (bVar10 == 0x60) {
      cVar6 = **(char **)(param_9 + 4);
      *(char **)(param_9 + 4) = *(char **)(param_9 + 4) + 1;
      fVar1 = (float)((double)CONCAT44(0x43300000,(int)cVar6 ^ 0x80000000) - dVar7);
    }
    else {
      fVar1 = FLOAT_8043d298;
      if (bVar10 < 0x60) {
        if (bVar10 == 0x40) {
          puVar12 = *(undefined1 **)(param_9 + 4);
          uVar3 = puVar12[1];
          uVar4 = *puVar12;
          *(undefined1 **)(param_9 + 4) = puVar12 + 2;
          fVar1 = (float)((double)CONCAT44(0x43300000,CONCAT11(uVar3,uVar4) ^ 0x80000000) - dVar7);
        }
        else {
          if ((0x3f < bVar10) || (bVar10 != 0x20)) goto LAB_802495c8;
          puVar12 = *(undefined1 **)(param_9 + 4);
          uVar3 = puVar12[1];
          uVar4 = *puVar12;
          *(undefined1 **)(param_9 + 4) = puVar12 + 2;
          fVar1 = (float)((double)CONCAT44(0x43300000,(int)CONCAT11(uVar3,uVar4) ^ 0x80000000) -
                         dVar7);
        }
      }
      else {
        if (bVar10 != 0x80) goto LAB_802495c8;
        bVar10 = **(byte **)(param_9 + 4);
        *(byte **)(param_9 + 4) = *(byte **)(param_9 + 4) + 1;
        fVar1 = (float)((double)CONCAT44(0x43300000,(uint)bVar10) - dVar8);
      }
    }
    fVar1 = fVar1 / (float)((double)CONCAT44(0x43300000,1 << (bVar2 & 0x1f) ^ 0x80000000) -
                           DOUBLE_8043d2a0);
  }
LAB_802495c8:
  *(float *)(param_9 + 0x2c) = fVar1;
  uVar17 = ((int)~(uVar17 - 1 | 1 - uVar17) >> 0x1f) + 4;
  if (param_9 != 0) {
    *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xf0 | (byte)uVar17 & 0xf;
  }
  return uVar17;
}



// ==== 80249ac4  gnt4-HSD_FObjInterpretAnim-bl ====

/* WARNING: Removing unreachable block (ram,0x8024a174) */
/* WARNING: Removing unreachable block (ram,0x80249ad4) */
/* WARNING: Removing unreachable block (ram,0x80249afc) */

void gnt4_HSD_FObjInterpretAnim_bl
               (double param_1,undefined8 param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,uint param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  float *pfVar4;
  byte *pbVar5;
  uint uVar6;
  char *pcVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  float local_58 [3];
  float local_4c [3];
  float local_40 [4];
  undefined4 local_30;
  float *pfStack_2c;
  undefined4 local_28;
  float *pfStack_24;
  
  dVar9 = DOUBLE_8043d2b8;
  dVar11 = (double)FLOAT_8043d298;
  if (param_9 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = *(byte *)(param_9 + 0x10) & 0xf;
  }
  if (uVar3 != 0) {
    dVar10 = (double)*(float *)(param_9 + 0x1c);
    *(float *)(param_9 + 0x1c) = (float)(dVar10 + param_1);
    dVar8 = (double)*(float *)(param_9 + 0x1c);
    uVar6 = param_10;
    pcVar7 = (char *)param_11;
    if (dVar9 <= dVar8) {
LAB_80249b3c:
      while (dVar9 = DOUBLE_8043d2a8, uVar3 != 4) {
        if ((int)uVar3 < 4) {
          if (uVar3 == 0) {
            return;
          }
          if (-1 < (int)uVar3) {
            if ((int)uVar3 < 3) {
              uVar3 = gnt4_FObjLoadData(dVar8,dVar10,param_3,param_4,param_5,param_6,param_7,param_8
                                        ,param_9,uVar6,pcVar7,param_12,param_13,param_14,param_15,
                                        param_16);
            }
            else {
              bVar2 = *(byte *)(param_9 + 0x10);
              if (((bVar2 & 0x80) != 0) && (param_11 != (float *)0x0)) {
                bVar1 = *(byte *)(param_9 + 0x12);
                if (bVar1 == 2) {
                  if ((bVar2 & 0x20) != 0) {
                    *(byte *)(param_9 + 0x10) = bVar2 & 0xdf;
                    pfVar4 = (float *)(uint)*(ushort *)(param_9 + 0x1a);
                    if (pfVar4 == (float *)0x0) {
                      *(float *)(param_9 + 0x28) = FLOAT_8043d298;
                      *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x24);
                    }
                    else {
                      param_3 = (double)*(float *)(param_9 + 0x24);
                      local_30 = 0x43300000;
                      *(float *)(param_9 + 0x28) =
                           (float)(param_3 - (double)*(float *)(param_9 + 0x20)) /
                           (float)((double)CONCAT44(0x43300000,pfVar4) - DOUBLE_8043d2a8);
                      pfStack_2c = pfVar4;
                    }
                  }
                  dVar10 = (double)*(float *)(param_9 + 0x28);
                  local_4c[0] = (float)(dVar10 * (double)*(float *)(param_9 + 0x1c) +
                                       (double)*(float *)(param_9 + 0x20));
                }
                else if (bVar1 < 2) {
                  if (bVar1 != 0) {
                    pfStack_2c = (float *)(uint)*(ushort *)(param_9 + 0x1a);
                    local_30 = 0x43300000;
                    dVar10 = (double)*(float *)(param_9 + 0x1c);
                    if (dVar10 < (double)(float)((double)CONCAT44(0x43300000,pfStack_2c) -
                                                DOUBLE_8043d2a8)) {
                      local_4c[0] = *(float *)(param_9 + 0x20);
                    }
                    else {
                      local_4c[0] = *(float *)(param_9 + 0x24);
                    }
                  }
                }
                else if (bVar1 == 6) {
                  if ((bVar2 & 0x80) == 0) goto LAB_80249ebc;
                  local_4c[0] = *(float *)(param_9 + 0x20);
                  *(byte *)(param_9 + 0x10) = bVar2 & 0x7f;
                }
                else if (bVar1 < 6) {
                  pfVar4 = (float *)(uint)*(ushort *)(param_9 + 0x1a);
                  if (pfVar4 == (float *)0x0) {
                    local_4c[0] = *(float *)(param_9 + 0x24);
                  }
                  else {
                    local_30 = 0x43300000;
                    dVar10 = (double)*(float *)(param_9 + 0x1c);
                    param_3 = (double)*(float *)(param_9 + 0x20);
                    param_4 = (double)*(float *)(param_9 + 0x24);
                    param_5 = (double)*(float *)(param_9 + 0x28);
                    param_6 = (double)*(float *)(param_9 + 0x2c);
                    pfStack_2c = pfVar4;
                    dVar9 = gnt4_splGetHelmite_bl
                                      ((double)(float)(DOUBLE_8043d2b0 /
                                                      ((double)CONCAT44(0x43300000,pfVar4) -
                                                      DOUBLE_8043d2a8)),dVar10,param_3,param_4,
                                       param_5,param_6);
                    local_4c[0] = (float)dVar9;
                  }
                }
                pcVar7 = (char *)local_4c;
                dVar8 = (double)(*(code *)param_11)(param_10,*(undefined1 *)(param_9 + 0x13));
              }
LAB_80249ebc:
              if (param_9 == 0) {
                bVar2 = 0;
              }
              else {
                bVar2 = *(byte *)(param_9 + 0x10) & 0xf;
              }
              if (bVar2 != 3) {
                pcVar7 = s_st____FOBJ_LOAD_WAIT_803ac888;
                dVar8 = (double)gnt4___assert_bl(dVar8,dVar10,param_3,param_4,param_5,param_6,
                                                 param_7,param_8,&DAT_80435eb0,0x16c,
                                                 s_st____FOBJ_LOAD_WAIT_803ac888,param_12,param_13,
                                                 param_14,param_15,param_16);
              }
              uVar6 = *(uint *)(param_9 + 8);
              if (*(int *)(param_9 + 4) - uVar6 < *(uint *)(param_9 + 0xc)) {
                pcVar7 = (char *)0x0;
                uVar6 = 0;
                do {
                  pbVar5 = *(byte **)(param_9 + 4);
                  *(byte **)(param_9 + 4) = pbVar5 + 1;
                  bVar2 = *pbVar5;
                  uVar3 = (bVar2 & 0x7f) << uVar6;
                  uVar6 = uVar6 + 7;
                  pcVar7 = (char *)((uint)pcVar7 | uVar3);
                } while ((bVar2 & 0x80) != 0);
                *(short *)(param_9 + 0x1a) = (short)pcVar7;
                *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) | 0x20;
                if (param_9 != 0) {
                  *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xf0 | 2;
                }
                uVar3 = 2;
              }
              else {
                uVar3 = 6;
              }
            }
          }
        }
        else {
          if (uVar3 == 6) {
            *(float *)(param_9 + 0x1c) = (float)((double)*(float *)(param_9 + 0x1c) + dVar11);
            if ((*(byte *)(param_9 + 0x10) & 0x40) != 0) {
              *(undefined1 *)(param_9 + 0x12) = *(undefined1 *)(param_9 + 0x11);
              *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xbf;
              *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) | 0x80;
              *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x24);
            }
            if (param_11 != (float *)0x0) {
              bVar2 = *(byte *)(param_9 + 0x12);
              if (bVar2 == 2) {
                if ((*(byte *)(param_9 + 0x10) & 0x20) != 0) {
                  *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xdf;
                  pfVar4 = (float *)(uint)*(ushort *)(param_9 + 0x1a);
                  if (pfVar4 == (float *)0x0) {
                    *(float *)(param_9 + 0x28) = FLOAT_8043d298;
                    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x24);
                  }
                  else {
                    local_30 = 0x43300000;
                    *(float *)(param_9 + 0x28) =
                         (*(float *)(param_9 + 0x24) - *(float *)(param_9 + 0x20)) /
                         (float)((double)CONCAT44(0x43300000,pfVar4) - DOUBLE_8043d2a8);
                    pfStack_2c = pfVar4;
                  }
                }
                local_40[0] = *(float *)(param_9 + 0x28) * *(float *)(param_9 + 0x1c) +
                              *(float *)(param_9 + 0x20);
              }
              else if (bVar2 < 2) {
                if (bVar2 != 0) {
                  pfStack_2c = (float *)(uint)*(ushort *)(param_9 + 0x1a);
                  local_30 = 0x43300000;
                  if (*(float *)(param_9 + 0x1c) <
                      (float)((double)CONCAT44(0x43300000,pfStack_2c) - DOUBLE_8043d2a8)) {
                    local_40[0] = *(float *)(param_9 + 0x20);
                  }
                  else {
                    local_40[0] = *(float *)(param_9 + 0x24);
                  }
                }
              }
              else if (bVar2 == 6) {
                if ((*(byte *)(param_9 + 0x10) & 0x80) == 0) {
                  return;
                }
                local_40[0] = *(float *)(param_9 + 0x20);
                *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0x7f;
              }
              else if (bVar2 < 6) {
                pfVar4 = (float *)(uint)*(ushort *)(param_9 + 0x1a);
                if (pfVar4 == (float *)0x0) {
                  local_40[0] = *(float *)(param_9 + 0x24);
                }
                else {
                  local_30 = 0x43300000;
                  pfStack_2c = pfVar4;
                  dVar9 = gnt4_splGetHelmite_bl
                                    ((double)(float)(DOUBLE_8043d2b0 /
                                                    ((double)CONCAT44(0x43300000,pfVar4) -
                                                    DOUBLE_8043d2a8)),
                                     (double)*(float *)(param_9 + 0x1c),
                                     (double)*(float *)(param_9 + 0x20),
                                     (double)*(float *)(param_9 + 0x24),
                                     (double)*(float *)(param_9 + 0x28),
                                     (double)*(float *)(param_9 + 0x2c));
                  local_40[0] = (float)dVar9;
                }
              }
              (*(code *)param_11)(param_10,*(undefined1 *)(param_9 + 0x13),local_40);
              return;
            }
            return;
          }
          if (((int)uVar3 < 6) && (uVar3 = 4, param_9 != 0)) {
            uVar6 = (uint)*(byte *)(param_9 + 0x10);
            *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xf0 | 4;
          }
        }
      }
      pcVar7 = (char *)(uint)*(ushort *)(param_9 + 0x1a);
      uVar6 = 0x43300000;
      local_30 = 0x43300000;
      dVar10 = (double)*(float *)(param_9 + 0x1c);
      pfStack_2c = (float *)pcVar7;
      if ((double)(float)((double)CONCAT44(0x43300000,pcVar7) - DOUBLE_8043d2a8) <= dVar10) {
        uVar3 = 3;
        local_28 = 0x43300000;
        local_30 = 0x43300000;
        dVar8 = (double)CONCAT44(0x43300000,pcVar7);
        dVar11 = (double)(float)(dVar8 - DOUBLE_8043d2a8);
        *(float *)(param_9 + 0x1c) =
             (float)(dVar10 - (double)(float)((double)CONCAT44(0x43300000,pcVar7) - DOUBLE_8043d2a8)
                    );
        param_5 = dVar9;
        pfStack_24 = (float *)pcVar7;
        if (param_9 != 0) {
          uVar6 = (uint)*(byte *)(param_9 + 0x10);
          *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xf0 | 3;
        }
        goto LAB_80249b3c;
      }
      if (param_11 != (float *)0x0) {
        bVar2 = *(byte *)(param_9 + 0x12);
        if (bVar2 == 2) {
          if ((*(byte *)(param_9 + 0x10) & 0x20) != 0) {
            *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xdf;
            pfVar4 = (float *)(uint)*(ushort *)(param_9 + 0x1a);
            if (pfVar4 == (float *)0x0) {
              *(float *)(param_9 + 0x28) = FLOAT_8043d298;
              *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x24);
            }
            else {
              local_28 = 0x43300000;
              *(float *)(param_9 + 0x28) =
                   (*(float *)(param_9 + 0x24) - *(float *)(param_9 + 0x20)) /
                   (float)((double)CONCAT44(0x43300000,pfVar4) - dVar9);
              pfStack_24 = pfVar4;
            }
          }
          local_58[0] = *(float *)(param_9 + 0x28) * *(float *)(param_9 + 0x1c) +
                        *(float *)(param_9 + 0x20);
        }
        else if (bVar2 < 2) {
          if (bVar2 != 0) {
            local_28 = 0x43300000;
            if (dVar10 < (double)(float)((double)CONCAT44(0x43300000,pcVar7) - DOUBLE_8043d2a8)) {
              local_58[0] = *(float *)(param_9 + 0x20);
              pfStack_24 = (float *)pcVar7;
            }
            else {
              local_58[0] = *(float *)(param_9 + 0x24);
              pfStack_24 = (float *)pcVar7;
            }
          }
        }
        else if (bVar2 == 6) {
          if ((*(byte *)(param_9 + 0x10) & 0x80) == 0) goto LAB_8024a138;
          local_58[0] = *(float *)(param_9 + 0x20);
          *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0x7f;
        }
        else if (bVar2 < 6) {
          if ((float *)pcVar7 == (float *)0x0) {
            local_58[0] = *(float *)(param_9 + 0x24);
          }
          else {
            local_28 = 0x43300000;
            pfStack_24 = (float *)pcVar7;
            dVar9 = gnt4_splGetHelmite_bl
                              ((double)(float)(DOUBLE_8043d2b0 /
                                              ((double)CONCAT44(0x43300000,pcVar7) - DOUBLE_8043d2a8
                                              )),dVar10,(double)*(float *)(param_9 + 0x20),
                               (double)*(float *)(param_9 + 0x24),(double)*(float *)(param_9 + 0x28)
                               ,(double)*(float *)(param_9 + 0x2c));
            local_58[0] = (float)dVar9;
          }
        }
        (*(code *)param_11)(param_10,*(undefined1 *)(param_9 + 0x13),local_58);
      }
LAB_8024a138:
      if (param_9 == 0) {
        return;
      }
      *(byte *)(param_9 + 0x10) = *(byte *)(param_9 + 0x10) & 0xf0 | 5;
      return;
    }
  }
  return;
}



// ==== 8024a198  gnt4-HSD_FObjInterpretAnimAll ====

void gnt4_HSD_FObjInterpretAnimAll
               (double param_1,undefined8 param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,uint param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  for (; param_9 != (undefined4 *)0x0; param_9 = (undefined4 *)*param_9) {
    gnt4_HSD_FObjInterpretAnim_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,param_10
               ,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8024a208  gnt4-HSD_FObjLoadDesc ====

void gnt4_HSD_FObjLoadDesc
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  undefined8 extraout_f1;
  undefined8 uVar12;
  
  uVar12 = gnt4__savegpr_22_bl();
  puVar1 = (undefined4 *)((ulonglong)uVar12 >> 0x20);
  uVar7 = (undefined4)uVar12;
  if (puVar1 != (undefined4 *)0x0) {
    uVar12 = extraout_f1;
    puVar2 = gnt4_HSD_FObjAlloc(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                puVar1,uVar7,param_11,param_12,param_13,param_14,param_15,param_16);
    puVar11 = (undefined4 *)*puVar1;
    if (puVar11 == (undefined4 *)0x0) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      puVar3 = gnt4_HSD_FObjAlloc(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  puVar2,uVar7,param_11,param_12,param_13,param_14,param_15,param_16
                                 );
      puVar10 = (undefined4 *)*puVar11;
      if (puVar10 == (undefined4 *)0x0) {
        puVar4 = (undefined4 *)0x0;
      }
      else {
        puVar4 = gnt4_HSD_FObjAlloc(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    puVar3,uVar7,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
        puVar9 = (undefined4 *)*puVar10;
        if (puVar9 == (undefined4 *)0x0) {
          puVar5 = (undefined4 *)0x0;
        }
        else {
          puVar5 = gnt4_HSD_FObjAlloc(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,puVar4,uVar7,param_11,param_12,param_13,param_14,param_15,
                                      param_16);
          puVar8 = (undefined4 *)*puVar9;
          if (puVar8 == (undefined4 *)0x0) {
            puVar6 = (undefined4 *)0x0;
          }
          else {
            puVar6 = gnt4_HSD_FObjAlloc(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,puVar5,uVar7,param_11,param_12,param_13,param_14,
                                        param_15,param_16);
            uVar7 = gnt4_HSD_FObjLoadDesc
                              (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               *puVar8,uVar7,param_11,param_12,param_13,param_14,param_15,param_16);
            *puVar6 = uVar7;
            *(short *)(puVar6 + 6) = (short)(int)(float)puVar8[2];
            *(undefined1 *)((int)puVar6 + 0x13) = *(undefined1 *)(puVar8 + 3);
            *(undefined1 *)(puVar6 + 5) = *(undefined1 *)((int)puVar8 + 0xd);
            *(undefined1 *)((int)puVar6 + 0x15) = *(undefined1 *)((int)puVar8 + 0xe);
            puVar6[2] = puVar8[4];
            puVar6[3] = puVar8[1];
            *(undefined1 *)(puVar6 + 4) = 0;
          }
          *puVar5 = puVar6;
          *(short *)(puVar5 + 6) = (short)(int)(float)puVar9[2];
          *(undefined1 *)((int)puVar5 + 0x13) = *(undefined1 *)(puVar9 + 3);
          *(undefined1 *)(puVar5 + 5) = *(undefined1 *)((int)puVar9 + 0xd);
          *(undefined1 *)((int)puVar5 + 0x15) = *(undefined1 *)((int)puVar9 + 0xe);
          puVar5[2] = puVar9[4];
          puVar5[3] = puVar9[1];
          *(undefined1 *)(puVar5 + 4) = 0;
        }
        *puVar4 = puVar5;
        *(short *)(puVar4 + 6) = (short)(int)(float)puVar10[2];
        *(undefined1 *)((int)puVar4 + 0x13) = *(undefined1 *)(puVar10 + 3);
        *(undefined1 *)(puVar4 + 5) = *(undefined1 *)((int)puVar10 + 0xd);
        *(undefined1 *)((int)puVar4 + 0x15) = *(undefined1 *)((int)puVar10 + 0xe);
        puVar4[2] = puVar10[4];
        puVar4[3] = puVar10[1];
        *(undefined1 *)(puVar4 + 4) = 0;
      }
      *puVar3 = puVar4;
      *(short *)(puVar3 + 6) = (short)(int)(float)puVar11[2];
      *(undefined1 *)((int)puVar3 + 0x13) = *(undefined1 *)(puVar11 + 3);
      *(undefined1 *)(puVar3 + 5) = *(undefined1 *)((int)puVar11 + 0xd);
      *(undefined1 *)((int)puVar3 + 0x15) = *(undefined1 *)((int)puVar11 + 0xe);
      puVar3[2] = puVar11[4];
      puVar3[3] = puVar11[1];
      *(undefined1 *)(puVar3 + 4) = 0;
    }
    *puVar2 = puVar3;
    *(short *)(puVar2 + 6) = (short)(int)(float)puVar1[2];
    *(undefined1 *)((int)puVar2 + 0x13) = *(undefined1 *)(puVar1 + 3);
    *(undefined1 *)(puVar2 + 5) = *(undefined1 *)((int)puVar1 + 0xd);
    *(undefined1 *)((int)puVar2 + 0x15) = *(undefined1 *)((int)puVar1 + 0xe);
    puVar2[2] = puVar1[4];
    puVar2[3] = puVar1[1];
    *(undefined1 *)(puVar2 + 4) = 0;
  }
  gnt4__restgpr_22_bl();
  return;
}



// ==== 8024a430  gnt4-HSD_FObjAlloc ====

undefined4 *
gnt4_HSD_FObjAlloc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                  double param_6,double param_7,double param_8,undefined4 param_9,
                  undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
                  undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 *__s;
  
  __s = gnt4_HSD_ObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803f8de8,param_10,param_11,param_12,param_13,param_14,param_15,
                          param_16);
  if (__s == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435eb0,
                     0x2f3,&DAT_80435eb8,param_12,param_13,param_14,param_15,param_16);
  }
  gnt4_memset(__s,0,0x30);
  return __s;
}



// ==== 8024a48c  gnt4-HSD_FObjFree ====

void gnt4_HSD_FObjFree(undefined4 *param_1)

{
  gnt4_HSD_ObjFree(-0x7fc07218,param_1);
  return;
}



// ==== 8024a4b8  zz_024a4b8_ ====

void zz_024a4b8_(int param_1,ushort param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) | param_2;
  return;
}



// ==== 8024a4d0  zz_024a4d0_ ====

void zz_024a4d0_(int param_1,ushort param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) & ~param_2;
  return;
}



// ==== 8024a4e8  zz_024a4e8_ ====

void zz_024a4e8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,uint param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint extraout_r4;
  
  if (param_9 != 0) {
    uVar1 = param_10 & 8;
    for (; param_9 != 0; param_9 = *(int *)(param_9 + 4)) {
      if ((param_9 != 0) && (uVar1 != 0)) {
        param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                      param_8,*(undefined4 **)(param_9 + 0x18),param_10,param_11,
                                      param_12,param_13,param_14,param_15,param_16);
        *(undefined4 *)(param_9 + 0x18) = 0;
        param_10 = extraout_r4;
      }
    }
  }
  return;
}



// ==== 8024a55c  gnt4-HSD_PObjRemoveAnimAll-bl ====

void gnt4_HSD_PObjRemoveAnimAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint *puVar1;
  undefined4 *extraout_r4;
  undefined4 *puVar2;
  
  if ((param_9 != 0) && (puVar2 = param_10, param_10 != (undefined4 *)0x0)) {
    while (param_9 != 0) {
      if (param_9 != 0) {
        if (*(undefined4 **)(param_9 + 0x18) != (undefined4 *)0x0) {
          param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,*(undefined4 **)(param_9 + 0x18),param_10,param_11,
                                        param_12,param_13,param_14,param_15,param_16);
          param_10 = extraout_r4;
        }
        puVar1 = gnt4_HSD_AObjLoadDesc
                           (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (uint *)puVar2[1],param_10,param_11,param_12,param_13,param_14,param_15,
                            param_16);
        *(uint **)(param_9 + 0x18) = puVar1;
      }
      param_9 = *(int *)(param_9 + 4);
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        puVar2 = (undefined4 *)*puVar2;
      }
    }
  }
  return;
}



// ==== 8024a5ec  gnt4-HSD_PObjReqAnimAllByFlags-bl ====

void gnt4_HSD_PObjReqAnimAllByFlags_bl(double param_1,int param_2,uint param_3)

{
  if (param_2 != 0) {
    for (; param_2 != 0; param_2 = *(int *)(param_2 + 4)) {
      if ((param_2 != 0) && ((param_3 & 8) != 0)) {
        gnt4_HSD_AObjReqAnim(param_1,*(uint **)(param_2 + 0x18));
      }
    }
  }
  return;
}



// ==== 8024a660  gnt4-PObjUpdateFunc-bl ====

void gnt4_PObjUpdateFunc_bl(int param_1,int param_2,undefined4 *param_3)

{
  ushort *puVar1;
  
  if (param_1 == 0) {
    return;
  }
  if ((*(ushort *)(param_1 + 0xc) & 0x3000) != 0x1000) {
    return;
  }
  puVar1 = *(ushort **)(param_1 + 0x14);
  if ((*puVar1 & 2) != 0) {
    *(undefined4 *)(*(int *)(puVar1 + 0xe) + param_2 * 4 + -8) = *param_3;
    return;
  }
  *(undefined4 *)(puVar1 + 0xe) = *param_3;
  return;
}



// ==== 8024a6ac  gnt4-HSD_PObjAnimAll-bl ====

void gnt4_HSD_PObjAnimAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  if (param_9 != (int *)0x0) {
    for (; param_9 != (int *)0x0; param_9 = (int *)param_9[1]) {
      if (param_9 != (int *)0x0) {
        param_1 = gnt4_HSD_AObjInterpretAnim
                            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             (uint *)param_9[6],(uint)param_9,*(float **)(*param_9 + 0x48),param_12,
                             param_13,param_14,param_15,param_16);
      }
    }
  }
  return;
}



// ==== 8024a708  gnt4-PObjLoad-bl ====

void gnt4_PObjLoad_bl(undefined8 param_1,double param_2,double param_3,double param_4,double param_5
                     ,double param_6,double param_7,double param_8,undefined4 param_9,
                     undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                     ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  ushort uVar2;
  int iVar3;
  int *piVar4;
  ushort *__s;
  undefined4 *puVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined4 *puVar10;
  int *piVar11;
  ushort *puVar12;
  int *piVar13;
  double extraout_f1;
  double dVar14;
  undefined8 uVar15;
  undefined4 local_28;
  int local_24 [9];
  
  uVar15 = gnt4__savegpr_25_bl();
  iVar3 = (int)((ulonglong)uVar15 >> 0x20);
  iVar7 = (int)uVar15;
  uVar6 = 0x803b0000;
  dVar14 = extraout_f1;
  piVar4 = gnt4_HSD_PObjLoadDesc_bl
                     (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int **)(iVar7 + 4),0x803b0000,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  *(int **)(iVar3 + 4) = piVar4;
  *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(iVar7 + 8);
  *(undefined2 *)(iVar3 + 0xc) = *(undefined2 *)(iVar7 + 0xc);
  *(undefined2 *)(iVar3 + 0xe) = *(undefined2 *)(iVar7 + 0xe);
  *(undefined4 *)(iVar3 + 0x10) = *(undefined4 *)(iVar7 + 0x10);
  uVar2 = *(ushort *)(iVar3 + 0xc) & 0x3000;
  if (uVar2 == 0x1000) {
    puVar12 = *(ushort **)(iVar7 + 0x14);
    __s = (ushort *)
          gnt4_hsdAllocMemPiece_bl
                    (dVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x20,uVar6,
                     param_11,param_12,param_13,param_14,param_15,param_16);
    if (__s == (ushort *)0x0) {
      gnt4___assert_bl(dVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ec0,
                       0x1e2,s_shape_set_803ac928,param_12,param_13,param_14,param_15,param_16);
    }
    gnt4_memset(__s,0,0x20);
    *__s = *puVar12;
    __s[1] = puVar12[1];
    *(undefined4 *)(__s + 2) = *(undefined4 *)(puVar12 + 2);
    *(undefined4 *)(__s + 4) = *(undefined4 *)(puVar12 + 4);
    *(undefined4 *)(__s + 6) = *(undefined4 *)(puVar12 + 6);
    *(undefined4 *)(__s + 8) = *(undefined4 *)(puVar12 + 8);
    *(undefined4 *)(__s + 10) = *(undefined4 *)(puVar12 + 10);
    *(undefined4 *)(__s + 0xc) = *(undefined4 *)(puVar12 + 0xc);
    if ((*__s & 2) == 0) {
      *(float *)(__s + 0xe) = FLOAT_8043d2c0;
    }
    else {
      uVar6 = gnt4_HSD_Alloc_bl((uint)__s[1] << 2);
      *(undefined4 *)(__s + 0xe) = uVar6;
      fVar1 = FLOAT_8043d2c0;
      iVar8 = 0;
      for (iVar7 = 0; iVar7 < (int)(uint)__s[1]; iVar7 = iVar7 + 1) {
        *(float *)(*(int *)(__s + 0xe) + iVar8) = fVar1;
        iVar8 = iVar8 + 4;
      }
    }
    *(ushort **)(iVar3 + 0x14) = __s;
  }
  else {
    if (uVar2 < 0x1000) {
      if ((*(ushort *)(iVar3 + 0xc) & 0x3000) == 0) goto LAB_8024a920;
    }
    else if (uVar2 == 0x2000) {
      piVar9 = *(int **)(iVar7 + 0x14);
      puVar10 = &local_28;
      local_28 = 0;
      if (piVar9 != (int *)0x0) {
        for (; *piVar9 != 0; piVar9 = piVar9 + 1) {
          piVar11 = local_24;
          local_24[0] = 0;
          for (piVar13 = (int *)*piVar9; *piVar13 != 0; piVar13 = piVar13 + 2) {
            piVar4 = gnt4_hsdAllocMemPiece_bl
                               (dVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xc,
                                uVar6,param_11,param_12,param_13,param_14,param_15,param_16);
            if (piVar4 == (int *)0x0) {
              dVar14 = (double)gnt4___assert_bl(dVar14,param_2,param_3,param_4,param_5,param_6,
                                                param_7,param_8,&DAT_80435ec0,0x1a9,
                                                s_envelope_803ac91c,param_12,param_13,param_14,
                                                param_15,param_16);
            }
            uVar6 = 0;
            param_11 = 0xc;
            gnt4_memset(piVar4,0,0xc);
            *piVar11 = (int)piVar4;
            piVar4 = (int *)*piVar11;
            piVar4[2] = piVar13[1];
            piVar11 = (int *)*piVar11;
          }
          puVar5 = gnt4_HSD_SListAlloc_bl
                             (dVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar4,
                              uVar6,param_11,param_12,param_13,param_14,param_15,param_16);
          *puVar10 = puVar5;
          piVar4 = (int *)*puVar10;
          piVar4[1] = local_24[0];
          puVar10 = (undefined4 *)*puVar10;
        }
      }
      *(undefined4 *)(iVar3 + 0x14) = local_28;
      goto LAB_8024a920;
    }
    gnt4_HSD_Panic_bl(dVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ec0,
                      0x22a,s_pobj__unexected_type__803ac934,param_12,param_13,param_14,param_15,
                      param_16);
  }
LAB_8024a920:
  gnt4__HSD_NeedCacheInvalidate_bl(1);
  gnt4__restgpr_25_bl();
  return;
}



// ==== 8024a944  gnt4-HSD_PObjLoadDesc-bl ====

int * gnt4_HSD_PObjLoadDesc_bl
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
      piVar2 = gnt4_HSD_PObjAlloc_bl
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else {
      piVar2 = gnt4_hsdNew_bl(puVar1);
      if (piVar2 == (int *)0x0) {
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435ec0,0x247,&DAT_80435ec8,param_12,param_13,param_14,param_15,
                         param_16);
      }
    }
    (**(code **)(*piVar2 + 0x44))(piVar2,param_9);
    return piVar2;
  }
  return (int *)0x0;
}



// ==== 8024a9dc  gnt4-HSD_PObjRemoveAll-bl ====

void gnt4_HSD_PObjRemoveAll_bl(int *param_1)

{
  int *piVar1;
  
  while (piVar1 = param_1, piVar1 != (int *)0x0) {
    param_1 = (int *)piVar1[1];
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x30))(piVar1);
      (**(code **)(*piVar1 + 0x34))(piVar1);
    }
  }
  return;
}



// ==== 8024aa50  gnt4-HSD_PObjAlloc-bl ====

int * gnt4_HSD_PObjAlloc_bl
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
  
  ppuVar2 = DAT_80436960;
  if (DAT_80436960 == (undefined **)0x0) {
    ppuVar2 = &PTR_gnt4_PObjInfoInit_bl_803ac8d0;
  }
  piVar1 = gnt4_hsdNew_bl(ppuVar2);
  if (piVar1 == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ec0,
                     0x2a9,&DAT_80435ec8,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  return piVar1;
}



// ==== 8024aaac  gnt4-HSD_PObjResolveRefsAll-bl ====

void gnt4_HSD_PObjResolveRefsAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  
  uVar10 = gnt4__savegpr_25_bl();
  while( true ) {
    iVar8 = (int)((ulonglong)uVar10 >> 0x20);
    iVar9 = (int)uVar10;
    if ((iVar8 == 0) || (iVar9 == 0)) break;
    if ((iVar8 != 0) && (iVar9 != 0)) {
      uVar1 = *(ushort *)(iVar8 + 0xc) & 0x3000;
      if (uVar1 == 0x2000) {
        puVar6 = *(undefined4 **)(iVar8 + 0x14);
        puVar5 = *(undefined4 **)(iVar9 + 0x14);
        if ((puVar6 != (undefined4 *)0x0) && (puVar5 != (undefined4 *)0x0)) {
          for (; (puVar6 != (undefined4 *)0x0 && (puVar4 = (uint *)*puVar5, puVar4 != (uint *)0x0));
              puVar5 = puVar5 + 1) {
            puVar7 = (undefined4 *)puVar6[1];
            for (; (puVar7 != (undefined4 *)0x0 && (*puVar4 != 0)); puVar4 = puVar4 + 2) {
              uVar10 = gnt4_HSD_JObjUnrefThis((int *)puVar7[1]);
              uVar2 = gnt4_HSD_IDGetDataFromTable_bl((undefined *)0x0,*puVar4,(undefined4 *)0x0);
              puVar7[1] = uVar2;
              if (puVar7[1] == 0) {
                uVar10 = gnt4___assert_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,&DAT_80435ec0,0x2ca,s_env_>jobj_803ac970,in_r6,
                                          in_r7,in_r8,in_r9,in_r10);
              }
              iVar3 = puVar7[1];
              if ((iVar3 != 0) &&
                 (*(short *)(iVar3 + 6) = *(short *)(iVar3 + 6) + 1, *(short *)(iVar3 + 6) == 0)) {
                gnt4___assert_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 s_object_h_803ac97c,0x9e,
                                 s_HSD_OBJ_o__>ref_count_individual_803ac988,in_r6,in_r7,in_r8,in_r9
                                 ,in_r10);
              }
              puVar7 = (undefined4 *)*puVar7;
            }
            puVar6 = (undefined4 *)*puVar6;
          }
        }
      }
      else if ((uVar1 < 0x2000) && ((*(ushort *)(iVar8 + 0xc) & 0x3000) == 0)) {
        uVar10 = gnt4_HSD_JObjUnrefThis(*(int **)(iVar8 + 0x14));
        *(undefined4 *)(iVar8 + 0x14) = 0;
        if (*(uint *)(iVar9 + 0x14) != 0) {
          uVar2 = gnt4_HSD_IDGetDataFromTable_bl
                            ((undefined *)0x0,*(uint *)(iVar9 + 0x14),(undefined4 *)0x0);
          *(undefined4 *)(iVar8 + 0x14) = uVar2;
          if (*(int *)(iVar8 + 0x14) == 0) {
            uVar10 = gnt4___assert_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,&DAT_80435ec0,0x2e5,s_pobj_>u_jobj_803ac9b0,in_r6,in_r7,in_r8
                                      ,in_r9,in_r10);
          }
          iVar3 = *(int *)(iVar8 + 0x14);
          if ((iVar3 != 0) &&
             (*(short *)(iVar3 + 6) = *(short *)(iVar3 + 6) + 1, *(short *)(iVar3 + 6) == 0)) {
            gnt4___assert_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_object_h_803ac97c,0x9e,s_HSD_OBJ_o__>ref_count_individual_803ac988,
                             in_r6,in_r7,in_r8,in_r9,in_r10);
          }
        }
      }
    }
    uVar10 = CONCAT44(*(undefined4 *)(iVar8 + 4),*(undefined4 *)(iVar9 + 4));
  }
  gnt4__restgpr_25_bl();
  return;
}



// ==== 8024ac80  gnt4-HSD_ClearVtxDesc-bl ====

void gnt4_HSD_ClearVtxDesc_bl(void)

{
  gnt4_GXClearVtxDesc_bl();
  DAT_80436974 = 0;
  DAT_80436978 = 0;
  return;
}



// ==== 8024acac  gnt4-get_shape_vertex_xyz-bl ====

void gnt4_get_shape_vertex_xyz_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
               float *param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  double dVar1;
  double dVar2;
  int iVar3;
  ushort *__src;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = *(int *)(param_9 + 8);
  iVar3 = *(int *)(*(int *)(param_9 + 0xc) + param_10 * 4);
  if (*(int *)(iVar5 + 4) == 3) {
    uVar6 = (uint)*(byte *)(iVar3 + param_11 * 2) * 0x100 +
            (uint)*(byte *)(iVar3 + param_11 * 2 + 1);
  }
  else {
    uVar6 = (uint)*(byte *)(iVar3 + param_11);
  }
  if (*(int *)(iVar5 + 8) != 1) {
    param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80435ec0,0x43a,
                                       s_shape_set_>vertex_desc_>comp_cnt_803ac9c0,param_12,iVar5,
                                       param_14,param_15,param_16);
  }
  dVar2 = DOUBLE_8043d2d0;
  dVar1 = DOUBLE_8043d2c8;
  iVar3 = *(int *)(param_9 + 8);
  iVar4 = *(int *)(iVar3 + 0xc);
  __src = (ushort *)(*(int *)(iVar3 + 0x14) + uVar6 * *(ushort *)(iVar3 + 0x12));
  if (iVar4 == 4) {
    gnt4_memcpy(param_12,__src,0xc);
  }
  else {
    uVar6 = 1 << (uint)*(byte *)(iVar3 + 0x10);
    if (iVar4 == 2) {
      uVar6 = uVar6 ^ 0x80000000;
      *param_12 = (float)((double)CONCAT44(0x43300000,(uint)*__src) - DOUBLE_8043d2c8) /
                  (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_8043d2d0);
      param_12[1] = (float)((double)CONCAT44(0x43300000,(uint)__src[1]) - dVar1) /
                    (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
      param_12[2] = (float)((double)CONCAT44(0x43300000,(uint)__src[2]) - dVar1) /
                    (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
    }
    else {
      if (iVar4 < 2) {
        if (iVar4 == 0) {
          uVar6 = uVar6 ^ 0x80000000;
          *param_12 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)__src) - DOUBLE_8043d2c8) /
                      (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_8043d2d0);
          param_12[1] = (float)((double)CONCAT44(0x43300000,(uint)(byte)*__src) - dVar1) /
                        (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
          param_12[2] = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(__src + 1)) - dVar1) /
                        (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
          return;
        }
        if (-1 < iVar4) {
          uVar6 = uVar6 ^ 0x80000000;
          *param_12 = (float)((double)CONCAT44(0x43300000,(int)(char)*(byte *)__src ^ 0x80000000) -
                             DOUBLE_8043d2d0) /
                      (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_8043d2d0);
          param_12[1] = (float)((double)CONCAT44(0x43300000,(int)(char)(byte)*__src ^ 0x80000000) -
                               dVar2) / (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
          param_12[2] = (float)((double)CONCAT44(0x43300000,
                                                 (int)(char)*(byte *)(__src + 1) ^ 0x80000000) -
                               dVar2) / (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
          return;
        }
      }
      else if (iVar4 < 4) {
        uVar6 = uVar6 ^ 0x80000000;
        *param_12 = (float)((double)CONCAT44(0x43300000,(int)(short)*__src ^ 0x80000000) -
                           DOUBLE_8043d2d0) /
                    (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_8043d2d0);
        param_12[1] = (float)((double)CONCAT44(0x43300000,(int)(short)__src[1] ^ 0x80000000) - dVar2
                             ) / (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
        param_12[2] = (float)((double)CONCAT44(0x43300000,(int)(short)__src[2] ^ 0x80000000) - dVar2
                             ) / (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
        return;
      }
      gnt4_HSD_Panic_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        &DAT_80435ec0,0x465,s_unexpected_vertex_type__803ac9f0,iVar4,iVar5,param_14,
                        param_15,param_16);
    }
  }
  return;
}



// ==== 8024b038  gnt4-get_shape_normal_xyz-bl ====

void gnt4_get_shape_normal_xyz_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
               float *param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  double dVar1;
  double dVar2;
  int iVar3;
  ushort *__src;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = *(int *)(param_9 + 0x14);
  iVar3 = *(int *)(*(int *)(param_9 + 0x18) + param_10 * 4);
  if (*(int *)(iVar5 + 4) == 3) {
    uVar6 = (uint)*(byte *)(iVar3 + param_11 * 2) * 0x100 +
            (uint)*(byte *)(iVar3 + param_11 * 2 + 1);
  }
  else {
    uVar6 = (uint)*(byte *)(iVar3 + param_11);
  }
  if (*(int *)(iVar5 + 8) != 0) {
    param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80435ec0,0x479,
                                       s_shape_set_>normal_desc_>comp_cnt_803aca0c,param_12,iVar5,
                                       param_14,param_15,param_16);
  }
  dVar2 = DOUBLE_8043d2d0;
  dVar1 = DOUBLE_8043d2c8;
  iVar3 = *(int *)(param_9 + 0x14);
  iVar4 = *(int *)(iVar3 + 0xc);
  __src = (ushort *)(*(int *)(iVar3 + 0x14) + uVar6 * *(ushort *)(iVar3 + 0x12));
  if (iVar4 == 4) {
    gnt4_memcpy(param_12,__src,0xc);
  }
  else {
    uVar6 = 1 << (uint)*(byte *)(iVar3 + 0x10);
    if (iVar4 == 2) {
      uVar6 = uVar6 ^ 0x80000000;
      *param_12 = (float)((double)CONCAT44(0x43300000,(uint)*__src) - DOUBLE_8043d2c8) /
                  (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_8043d2d0);
      param_12[1] = (float)((double)CONCAT44(0x43300000,(uint)__src[1]) - dVar1) /
                    (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
      param_12[2] = (float)((double)CONCAT44(0x43300000,(uint)__src[2]) - dVar1) /
                    (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
    }
    else {
      if (iVar4 < 2) {
        if (iVar4 == 0) {
          uVar6 = uVar6 ^ 0x80000000;
          *param_12 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)__src) - DOUBLE_8043d2c8) /
                      (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_8043d2d0);
          param_12[1] = (float)((double)CONCAT44(0x43300000,(uint)(byte)*__src) - dVar1) /
                        (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
          param_12[2] = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(__src + 1)) - dVar1) /
                        (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
          return;
        }
        if (-1 < iVar4) {
          uVar6 = uVar6 ^ 0x80000000;
          *param_12 = (float)((double)CONCAT44(0x43300000,(int)(char)*(byte *)__src ^ 0x80000000) -
                             DOUBLE_8043d2d0) /
                      (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_8043d2d0);
          param_12[1] = (float)((double)CONCAT44(0x43300000,(int)(char)(byte)*__src ^ 0x80000000) -
                               dVar2) / (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
          param_12[2] = (float)((double)CONCAT44(0x43300000,
                                                 (int)(char)*(byte *)(__src + 1) ^ 0x80000000) -
                               dVar2) / (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
          return;
        }
      }
      else if (iVar4 < 4) {
        uVar6 = uVar6 ^ 0x80000000;
        *param_12 = (float)((double)CONCAT44(0x43300000,(int)(short)*__src ^ 0x80000000) -
                           DOUBLE_8043d2d0) /
                    (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_8043d2d0);
        param_12[1] = (float)((double)CONCAT44(0x43300000,(int)(short)__src[1] ^ 0x80000000) - dVar2
                             ) / (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
        param_12[2] = (float)((double)CONCAT44(0x43300000,(int)(short)__src[2] ^ 0x80000000) - dVar2
                             ) / (float)((double)CONCAT44(0x43300000,uVar6) - dVar2);
        return;
      }
      gnt4_HSD_Panic_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        &DAT_80435ec0,0x4a4,s_unexpected_normal_type__803aca3c,iVar4,iVar5,param_14,
                        param_15,param_16);
    }
  }
  return;
}



// ==== 8024b3c4  gnt4-get_shape_nbt_xyz-bl ====

void gnt4_get_shape_nbt_xyz_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               int param_11,float *param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  ushort *puVar1;
  double dVar2;
  double dVar3;
  ushort *__src;
  int iVar4;
  float *pfVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  double extraout_f1;
  double dVar10;
  undefined8 uVar11;
  
  uVar11 = gnt4__savegpr_27_bl();
  iVar4 = (int)((ulonglong)uVar11 >> 0x20);
  uVar7 = 0x803b0000;
  iVar6 = *(int *)(iVar4 + 0x18);
  iVar8 = *(int *)(iVar6 + (int)uVar11 * 4);
  pfVar5 = param_12;
  dVar10 = extraout_f1;
  if (**(int **)(iVar4 + 0x14) != 0x19) {
    dVar10 = (double)gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,
                                      param_8,&DAT_80435ec0,0x4b1,
                                      s_shape_set_>normal_desc_>attr____G_803aca54,param_12,iVar6,
                                      0x803b0000,param_15,param_16);
  }
  if (*(int *)(*(int *)(iVar4 + 0x14) + 4) == 3) {
    uVar9 = (uint)*(byte *)(iVar8 + param_11 * 2) * 0x100 +
            (uint)*(byte *)(iVar8 + param_11 * 2 + 1);
  }
  else {
    uVar9 = (uint)*(byte *)(iVar8 + param_11);
  }
  if (*(int *)(*(int *)(iVar4 + 0x14) + 8) != 0) {
    dVar10 = (double)gnt4___assert_bl(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,&DAT_80435ec0,0x4ba,
                                      s_shape_set_>normal_desc_>comp_cnt_803aca0c,pfVar5,iVar6,uVar7
                                      ,param_15,param_16);
  }
  dVar3 = DOUBLE_8043d2d0;
  dVar2 = DOUBLE_8043d2c8;
  iVar4 = *(int *)(iVar4 + 0x14);
  iVar8 = *(int *)(iVar4 + 0xc);
  __src = (ushort *)(*(int *)(iVar4 + 0x14) + uVar9 * *(ushort *)(iVar4 + 0x12));
  if (iVar8 == 4) {
    gnt4_memcpy(param_12,__src,0x24);
  }
  else {
    uVar9 = 1 << (uint)*(byte *)(iVar4 + 0x10);
    if (iVar8 == 2) {
      uVar9 = uVar9 ^ 0x80000000;
      iVar4 = 3;
      do {
        *param_12 = (float)((double)CONCAT44(0x43300000,(uint)*__src) - dVar2) /
                    (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
        param_12[1] = (float)((double)CONCAT44(0x43300000,(uint)__src[1]) - dVar2) /
                      (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
        puVar1 = __src + 2;
        __src = __src + 3;
        param_12[2] = (float)((double)CONCAT44(0x43300000,(uint)*puVar1) - dVar2) /
                      (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
        param_12 = param_12 + 3;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    else {
      if (iVar8 < 2) {
        if (iVar8 == 0) {
          uVar9 = uVar9 ^ 0x80000000;
          iVar4 = 3;
          do {
            *param_12 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)__src) - dVar2) /
                        (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
            param_12[1] = (float)((double)CONCAT44(0x43300000,(uint)(byte)*__src) - dVar2) /
                          (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
            puVar1 = __src + 1;
            __src = (ushort *)((int)__src + 3);
            param_12[2] = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)puVar1) - dVar2) /
                          (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
            param_12 = param_12 + 3;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
          goto LAB_8024b7b4;
        }
        if (-1 < iVar8) {
          uVar9 = uVar9 ^ 0x80000000;
          iVar4 = 3;
          do {
            *param_12 = (float)((double)CONCAT44(0x43300000,(int)(char)*(byte *)__src ^ 0x80000000)
                               - dVar3) / (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
            param_12[1] = (float)((double)CONCAT44(0x43300000,(int)(char)(byte)*__src ^ 0x80000000)
                                 - dVar3) / (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
            puVar1 = __src + 1;
            __src = (ushort *)((int)__src + 3);
            param_12[2] = (float)((double)CONCAT44(0x43300000,
                                                   (int)(char)*(byte *)puVar1 ^ 0x80000000) - dVar3)
                          / (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
            param_12 = param_12 + 3;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
          goto LAB_8024b7b4;
        }
      }
      else if (iVar8 < 4) {
        uVar9 = uVar9 ^ 0x80000000;
        iVar4 = 3;
        do {
          *param_12 = (float)((double)CONCAT44(0x43300000,(int)(short)*__src ^ 0x80000000) - dVar3)
                      / (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
          param_12[1] = (float)((double)CONCAT44(0x43300000,(int)(short)__src[1] ^ 0x80000000) -
                               dVar3) / (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
          puVar1 = __src + 2;
          __src = __src + 3;
          param_12[2] = (float)((double)CONCAT44(0x43300000,(int)(short)*puVar1 ^ 0x80000000) -
                               dVar3) / (float)((double)CONCAT44(0x43300000,uVar9) - dVar3);
          param_12 = param_12 + 3;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        goto LAB_8024b7b4;
      }
      gnt4_HSD_Panic_bl(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ec0
                        ,0x4d9,s_unexpected_normal_type__803aca3c,iVar8,iVar6,uVar7,param_15,
                        param_16);
    }
  }
LAB_8024b7b4:
  gnt4__restgpr_27_bl();
  return;
}



// ==== 8024b7cc  gnt4-interpretShapeAnimDisplayList-bl ====

void gnt4_interpretShapeAnimDisplayList_bl
               (undefined8 param_1,double param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               undefined4 param_9,undefined4 param_10,int param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  byte *pbVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  byte *pbVar14;
  int iVar15;
  double dVar16;
  undefined8 uVar17;
  
  uVar17 = gnt4__savegpr_22_bl();
  iVar5 = (int)((ulonglong)uVar17 >> 0x20);
  uVar2 = *(ushort *)(iVar5 + 0xe);
  pbVar14 = *(byte **)(iVar5 + 0x10);
  for (iVar13 = 0; iVar13 + 3 < (int)((uint)uVar2 << 5); iVar13 = iVar13 + iVar11) {
    bVar1 = *pbVar14;
    iVar11 = 3;
    uVar3 = *(ushort *)(pbVar14 + 1);
    if ((bVar1 & 0xf8) == 0) break;
    dVar16 = (double)gnt4_GXBegin_bl(bVar1 & 0xf8,bVar1 & 7,uVar3);
    for (iVar10 = 0; iVar10 < (int)(uint)uVar3; iVar10 = iVar10 + 1) {
      iVar15 = 0;
      while( true ) {
        piVar9 = (int *)(*(int *)(iVar5 + 8) + iVar15);
        iVar6 = *piVar9;
        if (iVar6 == 0xff) break;
        bVar1 = pbVar14[iVar11];
        uVar4 = (uint)bVar1;
        iVar12 = iVar11 + 1;
        switch(iVar6) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
          DAT_cc008000._0_1_ = bVar1;
          break;
        case 9:
          if (piVar9[1] == 3) {
            pbVar8 = pbVar14 + iVar12;
            iVar12 = iVar11 + 2;
            uVar4 = (uint)CONCAT11(bVar1,*pbVar8);
          }
          puVar7 = (undefined4 *)((int)uVar17 + uVar4 * 0xc);
          param_2 = (double)(float)puVar7[2];
          dVar16 = (double)(float)puVar7[1];
          DAT_cc008000 = *puVar7;
          DAT_cc008000 = puVar7[1];
          DAT_cc008000 = puVar7[2];
          break;
        case 10:
          if (piVar9[1] == 3) {
            pbVar8 = pbVar14 + iVar12;
            iVar12 = iVar11 + 2;
            uVar4 = (uint)CONCAT11(bVar1,*pbVar8);
          }
          puVar7 = (undefined4 *)(param_11 + uVar4 * 0xc);
          param_2 = (double)(float)puVar7[2];
          dVar16 = (double)(float)puVar7[1];
          DAT_cc008000 = *puVar7;
          DAT_cc008000 = puVar7[1];
          DAT_cc008000 = puVar7[2];
          break;
        case 0xb:
        case 0xc:
          if (piVar9[1] == 3) {
            pbVar8 = pbVar14 + iVar12;
            iVar12 = iVar11 + 2;
            DAT_cc008000._0_2_ = CONCAT11(bVar1,*pbVar8);
          }
          else if (piVar9[1] == 2) {
            DAT_cc008000._0_1_ = bVar1;
          }
          else {
            iVar6 = piVar9[3];
            if (iVar6 == 3) {
LAB_8024ba28:
              pbVar8 = pbVar14 + iVar12;
              iVar12 = iVar11 + 2;
              DAT_cc008000._0_2_ = CONCAT11(bVar1,*pbVar8);
            }
            else {
              if (iVar6 < 3) {
                if (iVar6 != 1) {
                  if (0 < iVar6) goto LAB_8024ba64;
                  if (iVar6 < 0) break;
                  goto LAB_8024ba28;
                }
              }
              else {
                if (iVar6 == 5) {
LAB_8024ba64:
                  pbVar8 = pbVar14 + iVar12;
                  iVar12 = iVar11 + 4;
                  DAT_cc008000._0_1_ = bVar1;
                  DAT_cc008000._0_1_ = *pbVar8;
                  DAT_cc008000._0_1_ = pbVar8[1];
                  DAT_cc008000._0_1_ = pbVar8[2];
                  break;
                }
                if (4 < iVar6) break;
              }
              pbVar8 = pbVar14 + iVar12;
              iVar12 = iVar11 + 3;
              DAT_cc008000._0_1_ = bVar1;
              DAT_cc008000._0_1_ = *pbVar8;
              DAT_cc008000._0_1_ = pbVar8[1];
            }
          }
          break;
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
          if (piVar9[1] == 3) {
            pbVar8 = pbVar14 + iVar12;
            iVar12 = iVar11 + 2;
            DAT_cc008000._0_2_ = CONCAT11(bVar1,*pbVar8);
          }
          else {
            DAT_cc008000._0_1_ = bVar1;
          }
          break;
        default:
          if (piVar9[1] == 3) {
            iVar12 = iVar11 + 2;
          }
          dVar16 = (double)gnt4_OSReport_bl(dVar16,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,s_attr__d__is_not_supported_by_sys_803aca80,
                                            iVar6,&switchD_8024b86c::switchdataD_803acaac,piVar9,
                                            param_13,param_14,param_15,param_16);
          break;
        case 0x19:
          if (piVar9[1] == 3) {
            pbVar8 = pbVar14 + iVar12;
            iVar12 = iVar11 + 2;
            uVar4 = (uint)CONCAT11(bVar1,*pbVar8);
          }
          puVar7 = (undefined4 *)(param_11 + (uVar4 * 3 & 0xffff) * 0xc);
          DAT_cc008000 = *puVar7;
          DAT_cc008000 = puVar7[1];
          DAT_cc008000 = puVar7[2];
          DAT_cc008000 = puVar7[3];
          DAT_cc008000 = puVar7[4];
          DAT_cc008000 = puVar7[5];
          param_2 = (double)(float)puVar7[8];
          dVar16 = (double)(float)puVar7[7];
          DAT_cc008000 = puVar7[6];
          DAT_cc008000 = puVar7[7];
          DAT_cc008000 = puVar7[8];
        }
        iVar15 = iVar15 + 0x18;
        iVar11 = iVar12;
      }
    }
    pbVar14 = pbVar14 + iVar11;
  }
  gnt4__restgpr_22_bl();
  return;
}



// ==== 8024baf0  gnt4-drawShapeAnim-bl ====

/* WARNING: Removing unreachable block (ram,0x8024c20c) */
/* WARNING: Removing unreachable block (ram,0x8024c204) */
/* WARNING: Removing unreachable block (ram,0x8024bb08) */
/* WARNING: Removing unreachable block (ram,0x8024bb00) */

void gnt4_drawShapeAnim_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  float *in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  ushort *puVar7;
  int unaff_r29;
  uint uVar8;
  float *pfVar9;
  int iVar10;
  int iVar11;
  double extraout_f1;
  double extraout_f1_00;
  double dVar12;
  double extraout_f1_01;
  undefined8 uVar13;
  double in_f30;
  double dVar14;
  double in_f31;
  double dVar15;
  double in_ps30_1;
  double in_ps31_1;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c [9];
  float local_78 [10];
  longlong local_50;
  undefined4 local_48;
  uint uStack_44;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  iVar2 = gnt4__savegpr_24_bl();
  puVar7 = *(ushort **)(iVar2 + 0x14);
  dVar12 = extraout_f1;
  if (DAT_8043696c == 0) {
    DAT_8043696c = 2000;
    DAT_80436964 = gnt4_HSD_Alloc_bl(24000);
    dVar12 = extraout_f1_00;
  }
  if (DAT_8043696c < *(uint *)(puVar7 + 2)) {
    dVar12 = (double)gnt4___assert_bl(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,&DAT_80435ec0,0x56b,
                                      s_vertex_buffer_size_>__shape_set__803acb14,in_r6,in_r7,in_r8,
                                      in_r9,in_r10);
  }
  if ((*(int *)(puVar7 + 10) != 0) && (DAT_80436970 == 0)) {
    DAT_80436970 = 2000;
    DAT_80436968 = gnt4_HSD_Alloc_bl(24000);
    dVar12 = extraout_f1_01;
  }
  if (*(int **)(puVar7 + 10) != (int *)0x0) {
    if (**(int **)(puVar7 + 10) == 10) {
      if (DAT_80436970 < *(uint *)(puVar7 + 8)) {
        dVar12 = (double)gnt4___assert_bl(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,&DAT_80435ec0,0x574,
                                          s_normal_buffer_size_>__shape_set__803acb48,in_r6,in_r7,
                                          in_r8,in_r9,in_r10);
      }
      unaff_r29 = 0;
    }
    else {
      if (DAT_80436970 < (uint)(*(int *)(puVar7 + 8) * 3)) {
        dVar12 = (double)gnt4___assert_bl(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,&DAT_80435ec0,0x577,
                                          s_normal_buffer_size_>__shape_set__803acb7c,in_r6,in_r7,
                                          in_r8,in_r9,in_r10);
      }
      unaff_r29 = 1;
    }
  }
  if ((*puVar7 & 1) == 0) {
    pfVar9 = *(float **)(puVar7 + 0xe);
    iVar10 = 0;
    dVar15 = DOUBLE_8043d2d8;
    for (iVar6 = 0; iVar6 < *(int *)(puVar7 + 2); iVar6 = iVar6 + 1) {
      in_r6 = (float *)(DAT_80436964 + iVar10);
      dVar12 = (double)gnt4_get_shape_vertex_xyz_bl
                                 (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  (int)puVar7,0,iVar6,in_r6,in_r7,in_r8,in_r9,in_r10);
      pfVar4 = pfVar9;
      for (iVar11 = 0; iVar11 < (int)(uint)puVar7[1]; iVar11 = iVar11 + 1) {
        dVar14 = (double)*pfVar4;
        if ((double)*pfVar4 < dVar15) {
          dVar14 = dVar15;
        }
        dVar14 = (double)(float)dVar14;
        in_r6 = &local_fc;
        gnt4_get_shape_vertex_xyz_bl
                  (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)puVar7,
                   iVar11 + 1,iVar6,in_r6,in_r7,in_r8,in_r9,in_r10);
        pfVar4 = pfVar4 + 1;
        *(float *)(iVar10 + DAT_80436964) =
             (float)((double)local_fc * dVar14 + (double)*(float *)(iVar10 + DAT_80436964));
        *(float *)(iVar10 + DAT_80436964 + 4) =
             (float)((double)local_f8 * dVar14 + (double)*(float *)(iVar10 + DAT_80436964 + 4));
        dVar12 = (double)local_f4;
        *(float *)(iVar10 + DAT_80436964 + 8) =
             (float)(dVar12 * dVar14 + (double)*(float *)(iVar10 + DAT_80436964 + 8));
      }
      iVar10 = iVar10 + 0xc;
    }
    if (*(int *)(puVar7 + 8) != 0) {
      if (unaff_r29 == 0) {
        iVar6 = 0;
        dVar15 = DOUBLE_8043d2d8;
        for (iVar10 = 0; iVar10 < *(int *)(puVar7 + 8); iVar10 = iVar10 + 1) {
          in_r6 = (float *)(DAT_80436968 + iVar6);
          dVar12 = (double)gnt4_get_shape_normal_xyz_bl
                                     (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,(int)puVar7,0,iVar10,in_r6,in_r7,in_r8,in_r9,in_r10);
          pfVar4 = pfVar9;
          for (iVar11 = 0; iVar11 < (int)(uint)puVar7[1]; iVar11 = iVar11 + 1) {
            dVar14 = (double)*pfVar4;
            if ((double)*pfVar4 < dVar15) {
              dVar14 = dVar15;
            }
            dVar14 = (double)(float)dVar14;
            in_r6 = &local_108;
            gnt4_get_shape_normal_xyz_bl
                      (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)puVar7,
                       iVar11 + 1,iVar10,in_r6,in_r7,in_r8,in_r9,in_r10);
            pfVar4 = pfVar4 + 1;
            *(float *)(iVar6 + DAT_80436968) =
                 (float)((double)local_108 * dVar14 + (double)*(float *)(iVar6 + DAT_80436968));
            *(float *)(iVar6 + DAT_80436968 + 4) =
                 (float)((double)local_104 * dVar14 + (double)*(float *)(iVar6 + DAT_80436968 + 4));
            dVar12 = (double)local_100;
            *(float *)(iVar6 + DAT_80436968 + 8) =
                 (float)(dVar12 * dVar14 + (double)*(float *)(iVar6 + DAT_80436968 + 8));
          }
          iVar6 = iVar6 + 0xc;
        }
      }
      else {
        iVar6 = 0;
        dVar15 = DOUBLE_8043d2d8;
        for (iVar10 = 0; iVar10 < *(int *)(puVar7 + 8); iVar10 = iVar10 + 1) {
          in_r6 = (float *)(DAT_80436968 + iVar6);
          dVar12 = (double)gnt4_get_shape_nbt_xyz_bl
                                     (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,puVar7,0,iVar10,in_r6,in_r7,in_r8,in_r9,in_r10);
          pfVar4 = pfVar9;
          for (iVar11 = 0; iVar11 < (int)(uint)puVar7[1]; iVar11 = iVar11 + 1) {
            dVar14 = (double)*pfVar4;
            if ((double)*pfVar4 < dVar15) {
              dVar14 = dVar15;
            }
            dVar14 = (double)(float)dVar14;
            in_r6 = &local_c0;
            gnt4_get_shape_nbt_xyz_bl
                      (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar7,
                       iVar11 + 1,iVar10,in_r6,in_r7,in_r8,in_r9,in_r10);
            pfVar4 = pfVar4 + 1;
            *(float *)(iVar6 + DAT_80436968) =
                 (float)(dVar14 * (double)local_c0 + (double)*(float *)(iVar6 + DAT_80436968));
            *(float *)(iVar6 + DAT_80436968 + 4) =
                 (float)(dVar14 * (double)local_bc + (double)*(float *)(iVar6 + DAT_80436968 + 4));
            *(float *)(iVar6 + DAT_80436968 + 8) =
                 (float)(dVar14 * (double)local_b8 + (double)*(float *)(iVar6 + DAT_80436968 + 8));
            *(float *)(iVar6 + DAT_80436968 + 0xc) =
                 (float)(dVar14 * (double)local_b4 + (double)*(float *)(iVar6 + DAT_80436968 + 0xc))
            ;
            *(float *)(iVar6 + DAT_80436968 + 0x10) =
                 (float)(dVar14 * (double)local_b0 + (double)*(float *)(iVar6 + DAT_80436968 + 0x10)
                        );
            *(float *)(iVar6 + DAT_80436968 + 0x14) =
                 (float)(dVar14 * (double)local_ac + (double)*(float *)(iVar6 + DAT_80436968 + 0x14)
                        );
            *(float *)(iVar6 + DAT_80436968 + 0x18) =
                 (float)(dVar14 * (double)local_a8 + (double)*(float *)(iVar6 + DAT_80436968 + 0x18)
                        );
            *(float *)(iVar6 + DAT_80436968 + 0x1c) =
                 (float)(dVar14 * (double)local_a4 + (double)*(float *)(iVar6 + DAT_80436968 + 0x1c)
                        );
            dVar12 = (double)local_a0;
            *(float *)(iVar6 + DAT_80436968 + 0x20) =
                 (float)(dVar14 * dVar12 + (double)*(float *)(iVar6 + DAT_80436968 + 0x20));
          }
          iVar6 = iVar6 + 0x24;
        }
      }
    }
  }
  else {
    param_3 = (double)*(float *)(puVar7 + 0xe);
    in_r6 = (float *)(int)*(float *)(puVar7 + 0xe);
    local_50 = (longlong)(int)in_r6;
    uVar8 = puVar7[1] - 1;
    if ((int)((uint)in_r6 & ~((int)in_r6 >> 0x1f)) < (int)uVar8) {
      uVar8 = (uint)in_r6 & ~((int)in_r6 >> 0x1f);
    }
    uStack_44 = uVar8 ^ 0x80000000;
    local_48 = 0x43300000;
    dVar12 = (double)(float)(param_3 -
                            (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8043d2d0
                                           ));
    param_2 = dVar12;
    if (dVar12 < DOUBLE_8043d2d8) {
      param_2 = DOUBLE_8043d2d8;
    }
    dVar15 = DOUBLE_8043d2e0;
    if ((param_2 < DOUBLE_8043d2e0) && (dVar15 = dVar12, dVar12 < DOUBLE_8043d2d8)) {
      dVar15 = DOUBLE_8043d2d8;
    }
    dVar15 = (double)(float)dVar15;
    iVar10 = 0;
    dVar12 = DOUBLE_8043d2d0;
    for (iVar6 = 0; iVar6 < *(int *)(puVar7 + 2); iVar6 = iVar6 + 1) {
      dVar12 = (double)gnt4_get_shape_vertex_xyz_bl
                                 (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  (int)puVar7,uVar8,iVar6,&local_cc,in_r7,in_r8,in_r9,in_r10);
      iVar11 = puVar7[1] - 1;
      if ((int)(uVar8 + 1) < (int)(puVar7[1] - 1)) {
        iVar11 = uVar8 + 1;
      }
      in_r6 = &local_d8;
      gnt4_get_shape_vertex_xyz_bl
                (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)puVar7,iVar11,
                 iVar6,in_r6,in_r7,in_r8,in_r9,in_r10);
      iVar3 = iVar10 + 4;
      iVar11 = iVar10 + 8;
      *(float *)(DAT_80436964 + iVar10) =
           (float)(dVar15 * (double)(float)((double)local_d8 - (double)local_cc) + (double)local_cc)
      ;
      iVar10 = iVar10 + 0xc;
      *(float *)(DAT_80436964 + iVar3) =
           (float)(dVar15 * (double)(float)((double)local_d4 - (double)local_c8) + (double)local_c8)
      ;
      dVar12 = (double)local_c4;
      *(float *)(DAT_80436964 + iVar11) =
           (float)(dVar15 * (double)(float)((double)local_d0 - dVar12) + dVar12);
    }
    if (*(int *)(puVar7 + 8) != 0) {
      if (unaff_r29 == 0) {
        iVar10 = 0;
        for (iVar6 = 0; iVar6 < *(int *)(puVar7 + 8); iVar6 = iVar6 + 1) {
          dVar12 = (double)gnt4_get_shape_normal_xyz_bl
                                     (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,(int)puVar7,uVar8,iVar6,&local_e4,in_r7,in_r8,in_r9,in_r10);
          iVar11 = puVar7[1] - 1;
          if ((int)(uVar8 + 1) < (int)(puVar7[1] - 1)) {
            iVar11 = uVar8 + 1;
          }
          in_r6 = &local_f0;
          gnt4_get_shape_normal_xyz_bl
                    (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)puVar7,
                     iVar11,iVar6,in_r6,in_r7,in_r8,in_r9,in_r10);
          iVar3 = iVar10 + 4;
          iVar11 = iVar10 + 8;
          *(float *)(DAT_80436968 + iVar10) =
               (float)(dVar15 * (double)(float)((double)local_f0 - (double)local_e4) +
                      (double)local_e4);
          iVar10 = iVar10 + 0xc;
          *(float *)(DAT_80436968 + iVar3) =
               (float)(dVar15 * (double)(float)((double)local_ec - (double)local_e0) +
                      (double)local_e0);
          dVar12 = (double)local_dc;
          *(float *)(DAT_80436968 + iVar11) =
               (float)(dVar15 * (double)(float)((double)local_e8 - dVar12) + dVar12);
        }
      }
      else {
        iVar6 = 0;
        for (iVar10 = 0; iVar10 < *(int *)(puVar7 + 8); iVar10 = iVar10 + 1) {
          uVar13 = gnt4_get_shape_nbt_xyz_bl
                             (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar7,
                              uVar8,iVar10,local_78,in_r7,in_r8,in_r9,in_r10);
          iVar11 = puVar7[1] - 1;
          if ((int)(uVar8 + 1) < (int)(puVar7[1] - 1)) {
            iVar11 = uVar8 + 1;
          }
          gnt4_get_shape_nbt_xyz_bl
                    (uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar7,iVar11,
                     iVar10,local_9c,in_r7,in_r8,in_r9,in_r10);
          pfVar4 = local_78;
          pfVar5 = local_9c;
          iVar11 = 3;
          pfVar9 = (float *)0x0;
          do {
            *(float *)((int)pfVar9 + iVar6 + DAT_80436968) =
                 (float)(dVar15 * (double)(float)((double)*pfVar5 - (double)*pfVar4) +
                        (double)*pfVar4);
            *(float *)((int)pfVar9 + iVar6 + DAT_80436968 + 4) =
                 (float)(dVar15 * (double)(float)((double)pfVar5[1] - (double)pfVar4[1]) +
                        (double)pfVar4[1]);
            dVar12 = (double)pfVar4[2];
            pfVar4 = pfVar4 + 3;
            pfVar1 = pfVar5 + 2;
            pfVar5 = pfVar5 + 3;
            in_r6 = pfVar9 + 3;
            *(float *)((int)pfVar9 + iVar6 + DAT_80436968 + 8) =
                 (float)(dVar15 * (double)(float)((double)*pfVar1 - dVar12) + dVar12);
            iVar11 = iVar11 + -1;
            pfVar9 = in_r6;
          } while (iVar11 != 0);
          iVar6 = iVar6 + 0x24;
        }
      }
    }
  }
  gnt4_interpretShapeAnimDisplayList_bl
            (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,DAT_80436964,
             DAT_80436968,in_r6,in_r7,in_r8,in_r9,in_r10);
  gnt4__restgpr_24_bl();
  return;
}



// ==== 8024c22c  gnt4-HSD_PObjClearMtxMark-bl ====

void gnt4_HSD_PObjClearMtxMark_bl(undefined4 param_1,undefined4 param_2)

{
  DAT_803f8e18 = param_1;
  DAT_803f8e1c = param_2;
  DAT_803f8e20 = param_1;
  DAT_803f8e24 = param_2;
  return;
}



// ==== 8024c244  gnt4-SetupRigidModelMtx-bl ====

/* WARNING: Removing unreachable block (ram,0x8024c3cc) */

void gnt4_SetupRigidModelMtx_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  float *pfVar6;
  byte bVar8;
  int *piVar7;
  byte bVar9;
  undefined8 extraout_f1;
  undefined8 uVar10;
  undefined8 uVar11;
  float afStack_a8 [12];
  float afStack_78 [12];
  float afStack_48 [18];
  
  uVar11 = gnt4__savegpr_26_bl();
  iVar4 = (int)((ulonglong)uVar11 >> 0x20);
  bVar9 = 0;
  pfVar6 = param_11;
  uVar10 = extraout_f1;
  iVar2 = gnt4_HSD_JObjGetCurrent();
  if ((DAT_803f8e18 != iVar2) && (DAT_803f8e1c != 1)) {
    bVar9 = 1;
  }
  if ((DAT_803f8e20 != *(int *)(iVar4 + 0x14)) && (DAT_803f8e24 != 1)) {
    bVar9 = bVar9 | 2;
  }
  if (bVar9 != 0) {
    bVar8 = (*(uint *)(iVar2 + 0x14) & 0x80) != 0;
    iVar3 = gnt4__HSD_TObjGetCurrentByType_bl(0,1);
    if (iVar3 != 0) {
      bVar8 = 3;
    }
    iVar3 = gnt4__HSD_TObjGetCurrentByType_bl(0,2);
    if (iVar3 != 0) {
      bVar8 = bVar8 | 5;
    }
    bVar9 = bVar9 | bVar8;
    if ((bVar9 | 1) != 0) {
      gnt4_GXSetCurrentMtx_bl(0);
      uVar10 = gnt4_GXLoadPosMtxImm_bl(param_11,0);
      DAT_803ad4c4 = DAT_803ad4c4 + 1;
      if ((bVar9 & 1) != 0) {
        iVar3 = gnt4_PSMTXInvXpose_bl(param_11,afStack_48);
        if (iVar3 == 0) {
          uVar10 = gnt4_PSMTXCopy_bl(param_11,afStack_48);
        }
        if ((*(uint *)(iVar2 + 0x14) & 0x80) != 0) {
          uVar10 = gnt4_GXLoadNrmMtxImm_bl(afStack_48,0);
          DAT_803ad4c4 = DAT_803ad4c4 + 1;
        }
        if ((bVar9 & 6) != 0) {
          pfVar6 = (float *)0x0;
          uVar10 = gnt4_GXLoadTexMtxImm_bl(afStack_48,0x1e,0);
          DAT_803ad4c4 = DAT_803ad4c4 + 1;
        }
      }
    }
    if ((bVar9 | 2) != 0) {
      piVar7 = *(int **)(iVar4 + 0x14);
      if (piVar7 != (int *)0x0) {
        uVar5 = piVar7[5];
        bVar1 = false;
        if (((uVar5 & 0x800000) == 0) && ((uVar5 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          gnt4_HSD_JObjSetupMatrixSub_bl
                    (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar7,uVar5,
                     pfVar6,param_12,param_13,param_14,param_15,param_16);
        }
      }
      gnt4_PSMTXConcat_bl((float *)uVar11,(float *)(*(int *)(iVar4 + 0x14) + 0x44),afStack_a8);
      gnt4_GXLoadPosMtxImm_bl(afStack_a8,3);
      DAT_803ad4c4 = DAT_803ad4c4 + 1;
      if ((bVar9 & 1) != 0) {
        iVar4 = gnt4_PSMTXInvXpose_bl(afStack_a8,afStack_78);
        if (iVar4 == 0) {
          gnt4_PSMTXCopy_bl(afStack_a8,afStack_78);
        }
        if ((*(uint *)(iVar2 + 0x14) & 0x80) != 0) {
          gnt4_GXLoadNrmMtxImm_bl(afStack_78,3);
          DAT_803ad4c4 = DAT_803ad4c4 + 1;
        }
        if ((bVar9 & 6) != 0) {
          gnt4_GXLoadTexMtxImm_bl(afStack_78,0x21,0);
          DAT_803ad4c4 = DAT_803ad4c4 + 1;
        }
      }
    }
  }
  gnt4__restgpr_26_bl();
  return;
}



// ==== 8024c4c4  gnt4-SetupSharedVtxModelMtx-bl ====

/* WARNING: Removing unreachable block (ram,0x8024c824) */
/* WARNING: Removing unreachable block (ram,0x8024c4d4) */
/* WARNING: Removing unreachable block (ram,0x8024c6a0) */
/* WARNING: Removing unreachable block (ram,0x8024c5d0) */

void gnt4_SetupSharedVtxModelMtx_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  uint uVar8;
  float *pfVar9;
  float *extraout_r4;
  float *extraout_r4_00;
  float *extraout_r4_01;
  float *extraout_r4_02;
  float *extraout_r4_03;
  float *extraout_r4_04;
  float *extraout_r4_05;
  float *extraout_r4_06;
  char *pcVar10;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar11;
  int *piVar12;
  float *pfVar13;
  int iVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  int iVar17;
  undefined8 extraout_f1;
  undefined8 uVar18;
  double in_f31;
  double dVar19;
  double in_ps31_1;
  undefined8 uVar20;
  float afStack_d8 [12];
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
  float local_7c;
  float afStack_78 [28];
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  uVar20 = gnt4__savegpr_19_bl();
  pcVar10 = (char *)0x803b0000;
  uVar18 = extraout_f1;
  iVar3 = gnt4_HSD_JObjGetCurrent();
  DAT_803f8e18 = 0;
  DAT_803f8e1c = 2;
  DAT_803f8e20 = 0;
  DAT_803f8e24 = 2;
  uVar2 = *(uint *)(iVar3 + 0x14);
  uVar11 = 0;
  iVar4 = gnt4__HSD_TObjGetCurrentByType_bl(0,1);
  if (iVar4 != 0) {
    uVar11 = 3;
  }
  iVar5 = gnt4__HSD_TObjGetCurrentByType_bl(0,2);
  if (iVar5 != 0) {
    uVar11 = uVar11 | 5;
  }
  pfVar6 = gnt4__HSD_mkEnvelopeModelNodeMtx_bl
                     (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                      afStack_78,pcVar10,in_r6,in_r7,in_r8,in_r9,in_r10);
  pfVar9 = (float *)0x803b0000;
  dVar19 = (double)FLOAT_8043d2e8;
  iVar17 = 0;
  for (puVar16 = *(undefined4 **)((int)((ulonglong)uVar20 >> 0x20) + 0x14);
      (iVar17 < 10 && (puVar16 != (undefined4 *)0x0)); puVar16 = (undefined4 *)*puVar16) {
    puVar15 = (undefined4 *)puVar16[1];
    iVar7 = gnt4_HSD_Index2PosNrmMtx_bl
                      (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar17,pfVar9,
                       pcVar10,in_r6,in_r7,in_r8,in_r9,in_r10);
    iVar14 = 0;
    if (puVar15 == (undefined4 *)0x0) {
      pcVar10 = s_envelope_803ac91c;
      uVar18 = gnt4___assert_bl(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                &DAT_80435ec0,0x719,s_envelope_803ac91c,in_r6,in_r7,in_r8,in_r9,
                                in_r10);
      pfVar9 = extraout_r4;
    }
    if ((double)(float)puVar15[2] < dVar19) {
      local_7c = FLOAT_8043d2c0;
      local_80 = FLOAT_8043d2c0;
      local_84 = FLOAT_8043d2c0;
      local_88 = FLOAT_8043d2c0;
      local_8c = FLOAT_8043d2c0;
      local_90 = FLOAT_8043d2c0;
      local_94 = FLOAT_8043d2c0;
      local_98 = FLOAT_8043d2c0;
      local_9c = FLOAT_8043d2c0;
      local_a0 = FLOAT_8043d2c0;
      local_a4 = FLOAT_8043d2c0;
      local_a8 = FLOAT_8043d2c0;
      for (; puVar15 != (undefined4 *)0x0; puVar15 = (undefined4 *)*puVar15) {
        if (puVar15[1] == 0) {
          pcVar10 = s_envelope_>jobj_803acbb4;
          uVar18 = gnt4___assert_bl(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80435ec0,0x72d,s_envelope_>jobj_803acbb4,in_r6,in_r7,in_r8,
                                    in_r9,in_r10);
        }
        piVar12 = (int *)puVar15[1];
        if (piVar12 != (int *)0x0) {
          uVar8 = piVar12[5];
          bVar1 = false;
          if (((uVar8 & 0x800000) == 0) && ((uVar8 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (bVar1) {
            uVar18 = gnt4_HSD_JObjSetupMatrixSub_bl
                               (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                piVar12,uVar8,pcVar10,in_r6,in_r7,in_r8,in_r9,in_r10);
          }
        }
        if (piVar12 == (int *)0xffffffbc) {
          uVar18 = gnt4___assert_bl(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80435ec0,0x730,&DAT_80435ee0,in_r6,in_r7,in_r8,in_r9,in_r10
                                   );
        }
        if (piVar12[0x1e] == 0) {
          gnt4___assert_bl(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80435ec0,0x731,s_jp_>envelopemtx_803acbc4,in_r6,in_r7,in_r8,in_r9,
                           in_r10);
        }
        gnt4_PSMTXConcat_bl((float *)(piVar12 + 0x11),(float *)piVar12[0x1e],afStack_d8);
        pcVar10 = (char *)&local_a8;
        uVar18 = gnt4_HSD_MtxScaledAdd_bl
                           ((double)(float)puVar15[2],afStack_d8,(float *)pcVar10,(float *)pcVar10);
        iVar14 = iVar14 + 1;
        pfVar9 = extraout_r4_02;
      }
      pfVar13 = &local_a8;
    }
    else {
      piVar12 = (int *)puVar15[1];
      if (piVar12 != (int *)0x0) {
        pfVar9 = (float *)piVar12[5];
        bVar1 = false;
        if ((((uint)pfVar9 & 0x800000) == 0) && (((uint)pfVar9 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar18 = gnt4_HSD_JObjSetupMatrixSub_bl
                             (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar12
                              ,pfVar9,pcVar10,in_r6,in_r7,in_r8,in_r9,in_r10);
          pfVar9 = extraout_r4_00;
        }
      }
      if (pfVar6 == (float *)0x0) {
        pfVar13 = (float *)(puVar15[1] + 0x44);
      }
      else {
        pcVar10 = (char *)&local_a8;
        uVar18 = gnt4_PSMTXConcat_bl((float *)(puVar15[1] + 0x44),*(float **)(puVar15[1] + 0x78),
                                     (float *)pcVar10);
        pfVar13 = &local_a8;
        pfVar9 = extraout_r4_01;
      }
    }
    gnt4_HSD_PerfCountEnvelopeBlending_bl
              (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar14,pfVar9,pcVar10,
               in_r6,in_r7,in_r8,in_r9,in_r10);
    if (pfVar6 != (float *)0x0) {
      gnt4_PSMTXConcat_bl(pfVar13,pfVar6,&local_a8);
    }
    pcVar10 = (char *)afStack_d8;
    gnt4_PSMTXConcat_bl((float *)uVar20,pfVar13,(float *)pcVar10);
    uVar18 = gnt4_GXLoadPosMtxImm_bl(afStack_d8,iVar7);
    DAT_803ad4c4 = DAT_803ad4c4 + 1;
    pfVar9 = extraout_r4_03;
    if (iVar5 != 0 || (iVar4 != 0 || (uVar2 & 0x80) != 0)) {
      pfVar9 = &local_a8;
      iVar14 = gnt4_PSMTXInvXpose_bl(afStack_d8,pfVar9);
      if (iVar14 == 0) {
        uVar18 = gnt4_PSMTXCopy_bl(afStack_d8,&local_a8);
        pfVar9 = extraout_r4_04;
      }
      if ((*(uint *)(iVar3 + 0x14) & 0x80) != 0) {
        uVar18 = gnt4_GXLoadNrmMtxImm_bl(&local_a8,iVar7);
        DAT_803ad4c4 = DAT_803ad4c4 + 1;
        pfVar9 = extraout_r4_05;
      }
      if ((uVar11 & 6) != 0) {
        uVar8 = gnt4_HSD_Index2TexMtx_bl
                          (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar17,
                           pfVar9,pcVar10,in_r6,in_r7,in_r8,in_r9,in_r10);
        pcVar10 = (char *)0x0;
        uVar18 = gnt4_GXLoadTexMtxImm_bl(&local_a8,uVar8,0);
        DAT_803ad4c4 = DAT_803ad4c4 + 1;
        pfVar9 = extraout_r4_06;
      }
    }
    iVar17 = iVar17 + 1;
  }
  gnt4__restgpr_19_bl();
  return;
}



// ==== 8024c844  gnt4-SetupEnvelopeModelMtx-bl ====

void gnt4_SetupEnvelopeModelMtx_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  float afStack_78 [12];
  float afStack_48 [14];
  
  uVar2 = *(ushort *)(param_9 + 0xc) & 0x3000;
  if (uVar2 == 0x1000) {
    iVar3 = gnt4_HSD_JObjGetCurrent();
    if ((DAT_803f8e18 != iVar3) || (DAT_803f8e1c != 1)) {
      gnt4_GXSetCurrentMtx_bl(0);
      gnt4_GXLoadPosMtxImm_bl(param_11,0);
      DAT_803ad4c4 = DAT_803ad4c4 + 1;
      bVar1 = (*(uint *)(iVar3 + 0x14) & 0x80) != 0;
      iVar4 = gnt4__HSD_TObjGetCurrentByType_bl(0,1);
      bVar6 = bVar1;
      if (iVar4 != 0) {
        bVar6 = 3;
      }
      iVar5 = gnt4__HSD_TObjGetCurrentByType_bl(0,2);
      if (iVar5 != 0) {
        bVar6 = bVar6 | 5;
      }
      if (iVar5 != 0 || (iVar4 != 0 || bVar1)) {
        iVar4 = gnt4_PSMTXInvXpose_bl(param_11,afStack_78);
        if (iVar4 == 0) {
          gnt4_PSMTXCopy_bl(param_11,afStack_78);
        }
        if ((*(uint *)(iVar3 + 0x14) & 0x80) != 0) {
          gnt4_GXLoadNrmMtxImm_bl(afStack_78,0);
          DAT_803ad4c4 = DAT_803ad4c4 + 1;
        }
        if ((bVar6 & 6) != 0) {
          gnt4_GXLoadTexMtxImm_bl(afStack_78,0x1e,0);
          DAT_803ad4c4 = DAT_803ad4c4 + 1;
        }
      }
    }
  }
  else if (uVar2 < 0x1000) {
    if ((*(ushort *)(param_9 + 0xc) & 0x3000) == 0) {
      if (*(int *)(param_9 + 0x14) == 0) {
        iVar3 = gnt4_HSD_JObjGetCurrent();
        if ((DAT_803f8e18 != iVar3) || (DAT_803f8e1c != 1)) {
          gnt4_GXSetCurrentMtx_bl(0);
          gnt4_GXLoadPosMtxImm_bl(param_11,0);
          DAT_803ad4c4 = DAT_803ad4c4 + 1;
          bVar1 = (*(uint *)(iVar3 + 0x14) & 0x80) != 0;
          iVar4 = gnt4__HSD_TObjGetCurrentByType_bl(0,1);
          bVar6 = bVar1;
          if (iVar4 != 0) {
            bVar6 = 3;
          }
          iVar5 = gnt4__HSD_TObjGetCurrentByType_bl(0,2);
          if (iVar5 != 0) {
            bVar6 = bVar6 | 5;
          }
          if (iVar5 != 0 || (iVar4 != 0 || bVar1)) {
            iVar4 = gnt4_PSMTXInvXpose_bl(param_11,afStack_48);
            if (iVar4 == 0) {
              gnt4_PSMTXCopy_bl(param_11,afStack_48);
            }
            if ((*(uint *)(iVar3 + 0x14) & 0x80) != 0) {
              gnt4_GXLoadNrmMtxImm_bl(afStack_48,0);
              DAT_803ad4c4 = DAT_803ad4c4 + 1;
            }
            if ((bVar6 & 6) != 0) {
              gnt4_GXLoadTexMtxImm_bl(afStack_48,0x1e,0);
              DAT_803ad4c4 = DAT_803ad4c4 + 1;
            }
          }
        }
      }
      else {
        gnt4_SetupRigidModelMtx_bl
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      }
    }
  }
  else if (uVar2 == 0x2000) {
    gnt4_SetupSharedVtxModelMtx_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 8024cad8  gnt4-HSD_PObjDisp-bl ====

void gnt4_HSD_PObjDisp_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined4 param_11,uint param_12,uint param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  ushort uVar1;
  int *piVar2;
  int iVar3;
  ushort uVar4;
  int *piVar5;
  int *piVar6;
  undefined8 uVar7;
  
  uVar1 = *(ushort *)(param_9 + 3);
  if ((uVar1 & 0x800) == 0) {
    uVar4 = uVar1 & 0xc000;
    if (uVar4 == 0x8000) {
      gnt4_HSD_StateSetCullMode_bl(2);
    }
    else if (uVar4 < 0x8000) {
      if (uVar4 == 0x4000) {
        gnt4_HSD_StateSetCullMode_bl(1);
      }
      else if ((uVar4 < 0x4000) && ((uVar1 & 0xc000) == 0)) {
        gnt4_HSD_StateSetCullMode_bl(0);
      }
    }
    else if (uVar4 == 0xc000) {
      return;
    }
    (**(code **)(*param_9 + 0x40))(param_9,param_10,param_11);
    if ((*(ushort *)(param_9 + 3) & 0x3000) == 0x1000) {
      for (piVar6 = (int *)param_9[2]; iVar3 = *piVar6, iVar3 != 0xff; piVar6 = piVar6 + 6) {
        if (((piVar6[1] != 1) && (iVar3 != 0x19)) &&
           ((0x18 < iVar3 || ((10 < iVar3 || (iVar3 < 9)))))) {
          gnt4_GXSetArray(*piVar6,piVar6[5],*(ushort *)((int)piVar6 + 0x12) & 0xff);
        }
      }
      DAT_80436974 = (int *)0x0;
      uVar7 = gnt4_GXClearVtxDesc_bl();
      for (piVar6 = (int *)param_9[2]; iVar3 = *piVar6, iVar3 != 0xff; piVar6 = piVar6 + 6) {
        if (iVar3 < 0xb) {
          if (iVar3 < 9) {
            if (iVar3 < 0) goto LAB_8024cc70;
            uVar7 = gnt4_GXSetVtxDesc_bl(*piVar6,piVar6[1]);
          }
          else {
LAB_8024cc38:
            gnt4_GXSetVtxDesc_bl(*piVar6,1);
            param_12 = 4;
            param_13 = 0;
            uVar7 = gnt4_GXSetVtxAttrFmt_bl(0,*piVar6,piVar6[2],4,0);
          }
        }
        else {
          if (iVar3 == 0x19) goto LAB_8024cc38;
LAB_8024cc70:
          gnt4_GXSetVtxDesc_bl(*piVar6,piVar6[1]);
          param_12 = piVar6[3];
          param_13 = (uint)*(byte *)(piVar6 + 4);
          uVar7 = gnt4_GXSetVtxAttrFmt_bl(0,*piVar6,piVar6[2],param_12,param_13);
        }
      }
      DAT_80436978 = 0;
      if (param_9[5] == 0) {
        uVar7 = gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ec0,0x77a,s_pobj_>u_shape_set_803acbd4,param_12,param_13,
                                 param_14,param_15,param_16);
      }
      gnt4_drawShapeAnim_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else {
      piVar5 = (int *)param_9[2];
      piVar6 = piVar5;
      piVar2 = DAT_80436974;
      if (DAT_80436974 != piVar5) {
        for (; piVar2 = piVar5, *piVar6 != 0xff; piVar6 = piVar6 + 6) {
          if (piVar6[1] != 1) {
            gnt4_GXSetArray(*piVar6,piVar6[5],*(ushort *)((int)piVar6 + 0x12) & 0xff);
          }
        }
      }
      DAT_80436974 = piVar2;
      if (DAT_80436978 != param_9[2]) {
        gnt4_GXClearVtxDesc_bl();
        for (piVar6 = (int *)param_9[2]; *piVar6 != 0xff; piVar6 = piVar6 + 6) {
          gnt4_GXSetVtxDesc_bl(*piVar6,piVar6[1]);
          if ((8 < *piVar6) || (*piVar6 < 0)) {
            gnt4_GXSetVtxAttrFmt_bl(0,*piVar6,piVar6[2],piVar6[3],(uint)*(byte *)(piVar6 + 4));
          }
        }
        DAT_80436978 = param_9[2];
      }
      gnt4_GXCallDisplayList_bl(param_9[4],(uint)*(ushort *)((int)param_9 + 0xe) << 5);
    }
  }
  return;
}



// ==== 8024cf98  gnt4-PObjInfoInit-bl ====

void gnt4_PObjInfoInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc53730,
             &PTR_gnt4__hsdClassInfoInit_bl_803ad6b0,s_sysdolphin_base_library_803acbe8,
             s_hsd_pobj_803acc00,0x4c,0x1c,in_r9,in_r10);
  DAT_803ac900 = 0x8024cdc0;
  DAT_803ac908 = 0x8024ceec;
  DAT_803ac90c = gnt4_HSD_PObjDisp_bl;
  DAT_803ac910 = gnt4_SetupEnvelopeModelMtx_bl;
  DAT_803ac914 = gnt4_PObjLoad_bl;
  DAT_803ac918 = gnt4_PObjUpdateFunc_bl;
  return;
}



// ==== 8024d030  gnt4-HSD_JObjCheckDepend ====

/* WARNING: Removing unreachable block (ram,0x8024d0a8) */

void gnt4_HSD_JObjCheckDepend
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  
  if (param_9 != 0) {
    if (param_9 == 0) {
      gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ee8
                       ,0x25d,&DAT_80435ef0,param_12,param_13,param_14,param_15,param_16);
    }
    uVar2 = *(uint *)(param_9 + 0x14);
    bVar1 = false;
    if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      if ((uVar2 & 0x800000) == 0) {
        if (((((*(int *)(param_9 + 0xc) != 0) &&
              ((*(uint *)(*(int *)(param_9 + 0xc) + 0x14) & 0x40) != 0)) ||
             (uVar2 = uVar2 & 0x600000, uVar2 == 0x200000)) ||
            ((uVar2 == 0x400000 || (uVar2 == 0x600000)))) || (*(int *)(param_9 + 0x80) != 0)) {
          *(uint *)(param_9 + 0x14) = *(uint *)(param_9 + 0x14) | 0x40;
        }
      }
      else if (((uVar2 & 0x1000000) == 0) && (*(int *)(param_9 + 0xc) != 0)) {
        uVar2 = *(uint *)(*(int *)(param_9 + 0xc) + 0x14);
        bVar1 = false;
        if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          *(uint *)(param_9 + 0x14) = *(uint *)(param_9 + 0x14) | 0x40;
        }
      }
    }
  }
  return;
}



// ==== 8024d15c  gnt4-HSD_JObjMtxIsDirty ====

undefined4
gnt4_HSD_JObjMtxIsDirty
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if (param_9 == 0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ee8,
                     0x25d,&DAT_80435ef0,param_12,param_13,param_14,param_15,param_16);
  }
  uVar1 = 0;
  if (((*(uint *)(param_9 + 0x14) & 0x800000) == 0) && ((*(uint *)(param_9 + 0x14) & 0x40) != 0)) {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 8024d1b4  gnt4-HSD_JObjSetMtxDirty ====

void gnt4_HSD_JObjSetMtxDirty
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  
  if (param_9 != 0) {
    if (param_9 == 0) {
      param_11 = &DAT_80435ef0;
      param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ee8,0x25d,&DAT_80435ef0,param_12,param_13,param_14,
                                 param_15,param_16);
    }
    uVar2 = *(uint *)(param_9 + 0x14);
    bVar1 = false;
    if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      gnt4_HSD_JObjSetMtxDirtySub_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar2,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 8024d224  gnt4-HSD_JObjMakeMatrix ====

/* WARNING: Removing unreachable block (ram,0x8024d24c) */
/* WARNING: Removing unreachable block (ram,0x8024d478) */

void gnt4_HSD_JObjMakeMatrix
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  bool bVar4;
  int iVar2;
  undefined4 *puVar3;
  uint uVar5;
  undefined4 *puVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  int *piVar10;
  undefined8 extraout_f1;
  undefined8 uVar11;
  ulonglong uVar12;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  uVar12 = CONCAT44(param_9,param_10);
  piVar10 = *(int **)(param_9 + 0xc);
  if (piVar10 != (int *)0x0) {
    uVar5 = piVar10[5];
    bVar4 = false;
    if (((uVar5 & 0x800000) == 0) && ((uVar5 & 0x40) != 0)) {
      bVar4 = true;
    }
    uVar12 = (ulonglong)uVar5;
    if (bVar4) {
      uVar12 = gnt4_HSD_JObjSetupMatrixSub_bl
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,
                          uVar5,param_11,param_12,param_13,param_14,param_15,param_16);
      param_1 = extraout_f1;
    }
  }
  if ((*(uint *)(param_9 + 0x14) & 8) == 0) {
    if (*(int *)(param_9 + 0x74) == 0) {
      puVar3 = gnt4_HSD_VecAlloc_bl
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int)(uVar12 >> 0x20),(int)uVar12,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      *(undefined4 **)(param_9 + 0x74) = puVar3;
    }
    if ((*(int *)(param_9 + 0xc) == 0) ||
       (pfVar9 = *(float **)(*(int *)(param_9 + 0xc) + 0x74), pfVar9 == (float *)0x0)) {
      puVar3 = *(undefined4 **)(param_9 + 0x74);
      uVar1 = *(undefined4 *)(param_9 + 0x30);
      *puVar3 = *(undefined4 *)(param_9 + 0x2c);
      puVar3[1] = uVar1;
      puVar3[2] = *(undefined4 *)(param_9 + 0x34);
    }
    else {
      **(float **)(param_9 + 0x74) = *(float *)(param_9 + 0x2c) * *pfVar9;
      *(float *)(*(int *)(param_9 + 0x74) + 4) =
           *(float *)(param_9 + 0x30) * *(float *)(*(int *)(*(int *)(param_9 + 0xc) + 0x74) + 4);
      *(float *)(*(int *)(param_9 + 0x74) + 8) =
           *(float *)(param_9 + 0x34) * *(float *)(*(int *)(*(int *)(param_9 + 0xc) + 0x74) + 8);
    }
  }
  else {
    iVar2 = *(int *)(param_9 + 0xc);
    if ((iVar2 == 0) || (*(int *)(iVar2 + 0x74) == 0)) {
      if (*(undefined4 **)(param_9 + 0x74) != (undefined4 *)0x0) {
        gnt4_HSD_VecFree_bl(*(undefined4 **)(param_9 + 0x74));
        *(undefined4 *)(param_9 + 0x74) = 0;
      }
    }
    else {
      if (*(int *)(param_9 + 0x74) == 0) {
        puVar3 = gnt4_HSD_VecAlloc_bl
                           (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                            (int)uVar12,param_11,param_12,param_13,param_14,param_15,param_16);
        *(undefined4 **)(param_9 + 0x74) = puVar3;
      }
      puVar3 = *(undefined4 **)(param_9 + 0x74);
      puVar6 = *(undefined4 **)(*(int *)(param_9 + 0xc) + 0x74);
      uVar1 = puVar6[1];
      *puVar3 = *puVar6;
      puVar3[1] = uVar1;
      puVar3[2] = puVar6[2];
    }
  }
  if ((*(uint *)(param_9 + 0x14) & 0x20000) == 0) {
    iVar2 = *(int *)(param_9 + 0xc);
    bVar4 = false;
    if ((iVar2 != 0) && (*(int *)(iVar2 + 0x74) != 0)) {
      bVar4 = true;
    }
    if (bVar4) {
      pfVar9 = *(float **)(iVar2 + 0x74);
    }
    else {
      pfVar9 = (float *)0x0;
    }
    pfVar7 = (float *)(param_9 + 0x1c);
    pfVar8 = (float *)(param_9 + 0x38);
    uVar11 = gnt4_HSD_MtxSRT_bl(param_9 + 0x44,param_9 + 0x2c,pfVar7,pfVar8,pfVar9);
  }
  else {
    iVar2 = *(int *)(param_9 + 0xc);
    bVar4 = false;
    if ((iVar2 != 0) && (*(int *)(iVar2 + 0x74) != 0)) {
      bVar4 = true;
    }
    if (bVar4) {
      pfVar9 = *(float **)(iVar2 + 0x74);
    }
    else {
      pfVar9 = (float *)0x0;
    }
    pfVar7 = (float *)(param_9 + 0x1c);
    pfVar8 = (float *)(param_9 + 0x38);
    uVar11 = gnt4_HSD_MtxSRTQuat_bl
                       ((float *)(param_9 + 0x44),(float *)(param_9 + 0x2c),pfVar7,pfVar8,pfVar9);
  }
  if (*(int *)(param_9 + 0xc) != 0) {
    pfVar7 = (float *)(param_9 + 0x44);
    uVar11 = gnt4_PSMTXConcat_bl((float *)(*(int *)(param_9 + 0xc) + 0x44),pfVar7,pfVar7);
  }
  if ((*(int *)(param_9 + 0x7c) != 0) &&
     (piVar10 = *(int **)(*(int *)(param_9 + 0x7c) + 0x18), piVar10 != (int *)0x0)) {
    uVar5 = piVar10[5];
    bVar4 = false;
    if (((uVar5 & 0x800000) == 0) && ((uVar5 & 0x40) != 0)) {
      bVar4 = true;
    }
    if (bVar4) {
      gnt4_HSD_JObjSetupMatrixSub_bl
                (uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,uVar5,pfVar7
                 ,pfVar8,pfVar9,param_14,param_15,param_16);
    }
    gnt4_PSMTXMultVec_bl((float *)(piVar10 + 0x11),(float *)(param_9 + 0x38),&local_18);
    *(float *)(param_9 + 0x50) = local_18;
    *(undefined4 *)(param_9 + 0x60) = local_14;
    *(undefined4 *)(param_9 + 0x70) = local_10;
  }
  return;
}



// ==== 8024d4f4  zz_024d4f4_ ====

void zz_024d4f4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,uint param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  
  if (param_9 != 0) {
    if ((param_10 & 1) != 0) {
      param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(undefined4 **)(param_9 + 0x7c),param_10,param_11,param_12,
                                    param_13,param_14,param_15,param_16);
      *(undefined4 *)(param_9 + 0x7c) = 0;
    }
    uVar1 = countLeadingZeros(*(uint *)(param_9 + 0x14) & 0x4020);
    if (uVar1 >> 5 != 0) {
      param_1 = zz_023d7a0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 0x18),param_10,param_11,param_12,param_13,param_14,
                            param_15,param_16);
    }
    zz_02576e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(undefined4 **)(param_9 + 0x80),param_10,param_11,param_12,param_13,param_14,
                param_15,param_16);
  }
  return;
}



// ==== 8024d570  zz_024d570_ ====

void zz_024d570_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint uVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 extraout_f1;
  undefined8 uVar10;
  ulonglong uVar11;
  
  uVar11 = gnt4__savegpr_24_bl();
  iVar7 = (int)(uVar11 >> 0x20);
  uVar2 = (uint)uVar11;
  if (iVar7 != 0) {
    uVar10 = extraout_f1;
    if ((uVar11 & 1) != 0) {
      uVar10 = gnt4_HSD_AObjRemove(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,
                                   param_8,*(undefined4 **)(iVar7 + 0x7c),uVar2,param_11,param_12,
                                   param_13,param_14,param_15,param_16);
      *(undefined4 *)(iVar7 + 0x7c) = 0;
    }
    uVar1 = countLeadingZeros(*(uint *)(iVar7 + 0x14) & 0x4020);
    if (uVar1 >> 5 != 0) {
      uVar10 = zz_023d7a0_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(iVar7 + 0x18),uVar2,param_11,param_12,param_13,param_14,param_15
                           ,param_16);
    }
    uVar10 = zz_02576e0_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         *(undefined4 **)(iVar7 + 0x80),uVar2,param_11,param_12,param_13,param_14,
                         param_15,param_16);
    if ((*(uint *)(iVar7 + 0x14) & 0x1000) == 0) {
      uVar3 = extraout_r4;
      for (iVar7 = *(int *)(iVar7 + 0x10); iVar7 != 0; iVar7 = *(int *)(iVar7 + 8)) {
        if (iVar7 != 0) {
          if ((uVar11 & 1) != 0) {
            uVar10 = gnt4_HSD_AObjRemove(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                         param_8,*(undefined4 **)(iVar7 + 0x7c),uVar3,param_11,
                                         param_12,param_13,param_14,param_15,param_16);
            *(undefined4 *)(iVar7 + 0x7c) = 0;
          }
          uVar1 = countLeadingZeros(*(uint *)(iVar7 + 0x14) & 0x4020);
          if (uVar1 >> 5 != 0) {
            uVar10 = zz_023d7a0_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int *)(iVar7 + 0x18),uVar2,param_11,param_12,param_13,param_14,
                                 param_15,param_16);
          }
          uVar10 = zz_02576e0_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               *(undefined4 **)(iVar7 + 0x80),uVar2,param_11,param_12,param_13,
                               param_14,param_15,param_16);
          uVar3 = extraout_r4_00;
          if ((*(uint *)(iVar7 + 0x14) & 0x1000) == 0) {
            for (iVar9 = *(int *)(iVar7 + 0x10); iVar9 != 0; iVar9 = *(int *)(iVar9 + 8)) {
              if (iVar9 != 0) {
                if ((uVar11 & 1) != 0) {
                  uVar10 = gnt4_HSD_AObjRemove(uVar10,param_2,param_3,param_4,param_5,param_6,
                                               param_7,param_8,*(undefined4 **)(iVar9 + 0x7c),uVar3,
                                               param_11,param_12,param_13,param_14,param_15,param_16
                                              );
                  *(undefined4 *)(iVar9 + 0x7c) = 0;
                }
                uVar1 = countLeadingZeros(*(uint *)(iVar9 + 0x14) & 0x4020);
                if (uVar1 >> 5 != 0) {
                  uVar10 = zz_023d7a0_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,*(int *)(iVar9 + 0x18),uVar2,param_11,param_12,
                                       param_13,param_14,param_15,param_16);
                }
                uVar10 = zz_02576e0_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     *(undefined4 **)(iVar9 + 0x80),uVar2,param_11,param_12,param_13
                                     ,param_14,param_15,param_16);
                uVar3 = extraout_r4_01;
                if ((*(uint *)(iVar9 + 0x14) & 0x1000) == 0) {
                  for (iVar8 = *(int *)(iVar9 + 0x10); iVar8 != 0; iVar8 = *(int *)(iVar8 + 8)) {
                    if (iVar8 != 0) {
                      if ((uVar11 & 1) != 0) {
                        uVar10 = gnt4_HSD_AObjRemove(uVar10,param_2,param_3,param_4,param_5,param_6,
                                                     param_7,param_8,*(undefined4 **)(iVar8 + 0x7c),
                                                     uVar3,param_11,param_12,param_13,param_14,
                                                     param_15,param_16);
                        *(undefined4 *)(iVar8 + 0x7c) = 0;
                      }
                      uVar1 = countLeadingZeros(*(uint *)(iVar8 + 0x14) & 0x4020);
                      if (uVar1 >> 5 != 0) {
                        uVar10 = zz_023d7a0_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                             param_8,*(int *)(iVar8 + 0x18),uVar2,param_11,param_12,
                                             param_13,param_14,param_15,param_16);
                      }
                      uVar10 = zz_02576e0_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                           param_8,*(undefined4 **)(iVar8 + 0x80),uVar2,param_11,
                                           param_12,param_13,param_14,param_15,param_16);
                      uVar3 = extraout_r4_02;
                      if ((*(uint *)(iVar8 + 0x14) & 0x1000) == 0) {
                        for (iVar6 = *(int *)(iVar8 + 0x10); iVar6 != 0; iVar6 = *(int *)(iVar6 + 8)
                            ) {
                          if (iVar6 != 0) {
                            if ((uVar11 & 1) != 0) {
                              uVar10 = gnt4_HSD_AObjRemove(uVar10,param_2,param_3,param_4,param_5,
                                                           param_6,param_7,param_8,
                                                           *(undefined4 **)(iVar6 + 0x7c),uVar3,
                                                           param_11,param_12,param_13,param_14,
                                                           param_15,param_16);
                              *(undefined4 *)(iVar6 + 0x7c) = 0;
                            }
                            uVar1 = countLeadingZeros(*(uint *)(iVar6 + 0x14) & 0x4020);
                            if (uVar1 >> 5 != 0) {
                              uVar10 = zz_023d7a0_(uVar10,param_2,param_3,param_4,param_5,param_6,
                                                   param_7,param_8,*(int *)(iVar6 + 0x18),uVar2,
                                                   param_11,param_12,param_13,param_14,param_15,
                                                   param_16);
                            }
                            uVar10 = zz_02576e0_(uVar10,param_2,param_3,param_4,param_5,param_6,
                                                 param_7,param_8,*(undefined4 **)(iVar6 + 0x80),
                                                 uVar2,param_11,param_12,param_13,param_14,param_15,
                                                 param_16);
                            uVar3 = extraout_r4_03;
                            if ((*(uint *)(iVar6 + 0x14) & 0x1000) == 0) {
                              for (iVar5 = *(int *)(iVar6 + 0x10); iVar5 != 0;
                                  iVar5 = *(int *)(iVar5 + 8)) {
                                if ((iVar5 != 0) &&
                                   (uVar10 = zz_024d4f4_(uVar10,param_2,param_3,param_4,param_5,
                                                         param_6,param_7,param_8,iVar5,uVar2,
                                                         param_11,param_12,param_13,param_14,
                                                         param_15,param_16), uVar3 = extraout_r4_04,
                                   (*(uint *)(iVar5 + 0x14) & 0x1000) == 0)) {
                                  for (iVar4 = *(int *)(iVar5 + 0x10); iVar4 != 0;
                                      iVar4 = *(int *)(iVar4 + 8)) {
                                    uVar10 = zz_024d570_(uVar10,param_2,param_3,param_4,param_5,
                                                         param_6,param_7,param_8,iVar4,uVar2,
                                                         param_11,param_12,param_13,param_14,
                                                         param_15,param_16);
                                    uVar3 = extraout_r4_05;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  gnt4__restgpr_24_bl();
  return;
}



// ==== 8024d814  zz_024d814_ ====

void zz_024d814_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_024d570_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x7ff,param_11
              ,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8024d838  gnt4-HSD_JObjReqAnimByFlags ====

void gnt4_HSD_JObjReqAnimByFlags(double param_1,int param_2,uint param_3)

{
  uint uVar1;
  
  if (param_2 != 0) {
    if ((param_3 & 1) != 0) {
      gnt4_HSD_AObjReqAnim(param_1,*(uint **)(param_2 + 0x7c));
    }
    uVar1 = countLeadingZeros(*(uint *)(param_2 + 0x14) & 0x4020);
    if (uVar1 >> 5 != 0) {
      gnt4_HSD_DObjReqAnimAllByFlags_bl(param_1,*(int *)(param_2 + 0x18),param_3);
    }
    gnt4_HSD_RObjReqAnimAllByFlags_bl(param_1,*(undefined4 **)(param_2 + 0x80),param_3);
  }
  return;
}



// ==== 8024d8c0  gnt4-HSD_JObjReqAnimAllByFlags ====

void gnt4_HSD_JObjReqAnimAllByFlags(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  double extraout_f1;
  double dVar9;
  ulonglong uVar10;
  
  uVar10 = gnt4__savegpr_24_bl();
  iVar6 = (int)(uVar10 >> 0x20);
  uVar2 = (uint)uVar10;
  if (iVar6 != 0) {
    dVar9 = extraout_f1;
    if ((uVar10 & 1) != 0) {
      gnt4_HSD_AObjReqAnim(extraout_f1,*(uint **)(iVar6 + 0x7c));
    }
    uVar1 = countLeadingZeros(*(uint *)(iVar6 + 0x14) & 0x4020);
    if (uVar1 >> 5 != 0) {
      gnt4_HSD_DObjReqAnimAllByFlags_bl(dVar9,*(int *)(iVar6 + 0x18),uVar2);
    }
    gnt4_HSD_RObjReqAnimAllByFlags_bl(dVar9,*(undefined4 **)(iVar6 + 0x80),uVar2);
    if ((*(uint *)(iVar6 + 0x14) & 0x1000) == 0) {
      for (iVar6 = *(int *)(iVar6 + 0x10); iVar6 != 0; iVar6 = *(int *)(iVar6 + 8)) {
        if (iVar6 != 0) {
          if ((uVar10 & 1) != 0) {
            gnt4_HSD_AObjReqAnim(dVar9,*(uint **)(iVar6 + 0x7c));
          }
          uVar1 = countLeadingZeros(*(uint *)(iVar6 + 0x14) & 0x4020);
          if (uVar1 >> 5 != 0) {
            gnt4_HSD_DObjReqAnimAllByFlags_bl(dVar9,*(int *)(iVar6 + 0x18),uVar2);
          }
          gnt4_HSD_RObjReqAnimAllByFlags_bl(dVar9,*(undefined4 **)(iVar6 + 0x80),uVar2);
          if ((*(uint *)(iVar6 + 0x14) & 0x1000) == 0) {
            for (iVar8 = *(int *)(iVar6 + 0x10); iVar8 != 0; iVar8 = *(int *)(iVar8 + 8)) {
              if (iVar8 != 0) {
                if ((uVar10 & 1) != 0) {
                  gnt4_HSD_AObjReqAnim(dVar9,*(uint **)(iVar8 + 0x7c));
                }
                uVar1 = countLeadingZeros(*(uint *)(iVar8 + 0x14) & 0x4020);
                if (uVar1 >> 5 != 0) {
                  gnt4_HSD_DObjReqAnimAllByFlags_bl(dVar9,*(int *)(iVar8 + 0x18),uVar2);
                }
                gnt4_HSD_RObjReqAnimAllByFlags_bl(dVar9,*(undefined4 **)(iVar8 + 0x80),uVar2);
                if ((*(uint *)(iVar8 + 0x14) & 0x1000) == 0) {
                  for (iVar7 = *(int *)(iVar8 + 0x10); iVar7 != 0; iVar7 = *(int *)(iVar7 + 8)) {
                    if (iVar7 != 0) {
                      if ((uVar10 & 1) != 0) {
                        gnt4_HSD_AObjReqAnim(dVar9,*(uint **)(iVar7 + 0x7c));
                      }
                      uVar1 = countLeadingZeros(*(uint *)(iVar7 + 0x14) & 0x4020);
                      if (uVar1 >> 5 != 0) {
                        gnt4_HSD_DObjReqAnimAllByFlags_bl(dVar9,*(int *)(iVar7 + 0x18),uVar2);
                      }
                      gnt4_HSD_RObjReqAnimAllByFlags_bl(dVar9,*(undefined4 **)(iVar7 + 0x80),uVar2);
                      if ((*(uint *)(iVar7 + 0x14) & 0x1000) == 0) {
                        for (iVar5 = *(int *)(iVar7 + 0x10); iVar5 != 0; iVar5 = *(int *)(iVar5 + 8)
                            ) {
                          if (iVar5 != 0) {
                            if ((uVar10 & 1) != 0) {
                              gnt4_HSD_AObjReqAnim(dVar9,*(uint **)(iVar5 + 0x7c));
                            }
                            uVar1 = countLeadingZeros(*(uint *)(iVar5 + 0x14) & 0x4020);
                            if (uVar1 >> 5 != 0) {
                              gnt4_HSD_DObjReqAnimAllByFlags_bl(dVar9,*(int *)(iVar5 + 0x18),uVar2);
                            }
                            gnt4_HSD_RObjReqAnimAllByFlags_bl
                                      (dVar9,*(undefined4 **)(iVar5 + 0x80),uVar2);
                            if ((*(uint *)(iVar5 + 0x14) & 0x1000) == 0) {
                              for (iVar4 = *(int *)(iVar5 + 0x10); iVar4 != 0;
                                  iVar4 = *(int *)(iVar4 + 8)) {
                                if ((iVar4 != 0) &&
                                   (gnt4_HSD_JObjReqAnimByFlags(dVar9,iVar4,uVar2),
                                   (*(uint *)(iVar4 + 0x14) & 0x1000) == 0)) {
                                  for (iVar3 = *(int *)(iVar4 + 0x10); iVar3 != 0;
                                      iVar3 = *(int *)(iVar3 + 8)) {
                                    gnt4_HSD_JObjReqAnimAllByFlags();
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  gnt4__restgpr_24_bl();
  return;
}



// ==== 8024db88  gnt4-HSD_JObjReqAnimAll ====

void gnt4_HSD_JObjReqAnimAll(void)

{
  gnt4_HSD_JObjReqAnimAllByFlags();
  return;
}



// ==== 8024dbac  gnt4-JObjSortAnim ====

void gnt4_JObjSortAnim(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  if (param_1 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0x14) != 0) {
    puVar1 = (undefined4 *)(param_1 + 0x14);
    do {
      puVar2 = puVar1;
      puVar1 = (undefined4 *)*puVar2;
      if (puVar1 == (undefined4 *)0x0) {
        return;
      }
    } while (*(char *)((int)puVar1 + 0x13) != '\f');
    *puVar2 = *puVar1;
    *puVar1 = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 **)(param_1 + 0x14) = puVar1;
    return;
  }
  return;
}



// ==== 8024dc04  gnt4-HSD_JObjAddAnim ====

void gnt4_HSD_JObjAddAnim
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10,
               undefined4 *param_11,int param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint *puVar2;
  int extraout_r4;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined8 uVar7;
  
  if (param_9 != 0) {
    iVar6 = param_12;
    if (param_10 != 0) {
      iVar3 = param_10;
      puVar5 = param_11;
      if (*(undefined4 **)(param_9 + 0x7c) != (undefined4 *)0x0) {
        param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                      param_8,*(undefined4 **)(param_9 + 0x7c),param_10,param_11,
                                      param_12,param_13,param_14,param_15,param_16);
        iVar3 = extraout_r4;
      }
      puVar2 = gnt4_HSD_AObjLoadDesc
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(uint **)(param_10 + 8),iVar3,puVar5,iVar6,param_13,param_14,param_15,
                          param_16);
      *(uint **)(param_9 + 0x7c) = puVar2;
      iVar3 = *(int *)(param_9 + 0x7c);
      if ((iVar3 != 0) && (*(int *)(iVar3 + 0x14) != 0)) {
        puVar5 = (undefined4 *)(iVar3 + 0x14);
        do {
          puVar4 = puVar5;
          puVar5 = (undefined4 *)*puVar4;
          if (puVar5 == (undefined4 *)0x0) goto LAB_8024dcac;
        } while (*(char *)((int)puVar5 + 0x13) != '\f');
        *puVar4 = *puVar5;
        *puVar5 = *(undefined4 *)(iVar3 + 0x14);
        *(undefined4 **)(iVar3 + 0x14) = puVar5;
      }
LAB_8024dcac:
      uVar7 = gnt4_HSD_RObjAddAnimAll_bl
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         *(undefined4 **)(param_9 + 0x80),*(undefined4 **)(param_10 + 0xc),puVar5,
                         iVar6,param_13,param_14,param_15,param_16);
      if ((*(uint *)(param_10 + 0x10) & 1) == 0) {
        param_1 = gnt4_HSD_JObjClearFlags
                            (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,8
                             ,(undefined *)puVar5,iVar6,param_13,param_14,param_15,param_16);
      }
      else {
        param_1 = gnt4_HSD_JObjSetFlags
                            (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,8
                             ,(undefined *)puVar5,iVar6,param_13,param_14,param_15,param_16);
      }
    }
    uVar1 = countLeadingZeros(*(uint *)(param_9 + 0x14) & 0x4020);
    if (uVar1 >> 5 != 0) {
      if (param_12 == 0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        puVar5 = *(undefined4 **)(param_12 + 8);
      }
      if (param_11 == (undefined4 *)0x0) {
        puVar4 = (undefined4 *)0x0;
      }
      else {
        puVar4 = (undefined4 *)param_11[2];
      }
      gnt4_HSD_DObjAddAnimAll_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                 *(int *)(param_9 + 0x18),puVar4,puVar5,iVar6,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 8024dd44  gnt4-HSD_JObjAddAnimAll ====

void gnt4_HSD_JObjAddAnimAll
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 *param_11,undefined4 *param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint *puVar2;
  undefined4 *extraout_r4;
  int iVar3;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 *puVar4;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 *puVar5;
  undefined4 extraout_r4_06;
  undefined4 extraout_r4_07;
  undefined4 extraout_r4_08;
  undefined4 uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  int *piVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  int iVar17;
  undefined8 extraout_f1;
  undefined8 uVar18;
  
  uVar18 = gnt4__savegpr_20_bl();
  iVar17 = (int)((ulonglong)uVar18 >> 0x20);
  puVar16 = (undefined4 *)uVar18;
  if (iVar17 != 0) {
    uVar6 = 0;
    puVar7 = param_11;
    puVar8 = param_12;
    uVar18 = extraout_f1;
    if (puVar16 != (undefined4 *)0x0) {
      puVar4 = puVar16;
      if (*(undefined4 **)(iVar17 + 0x7c) != (undefined4 *)0x0) {
        uVar18 = gnt4_HSD_AObjRemove(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,
                                     param_8,*(undefined4 **)(iVar17 + 0x7c),puVar16,param_11,
                                     param_12,param_13,param_14,param_15,param_16);
        puVar4 = extraout_r4;
      }
      puVar2 = gnt4_HSD_AObjLoadDesc
                         (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (uint *)puVar16[2],puVar4,puVar7,puVar8,param_13,param_14,param_15,
                          param_16);
      *(uint **)(iVar17 + 0x7c) = puVar2;
      iVar3 = *(int *)(iVar17 + 0x7c);
      if ((iVar3 != 0) && (*(int *)(iVar3 + 0x14) != 0)) {
        puVar7 = (undefined4 *)(iVar3 + 0x14);
        do {
          puVar4 = puVar7;
          puVar7 = (undefined4 *)*puVar4;
          if (puVar7 == (undefined4 *)0x0) goto LAB_8024dde8;
        } while (*(char *)((int)puVar7 + 0x13) != '\f');
        *puVar4 = *puVar7;
        *puVar7 = *(undefined4 *)(iVar3 + 0x14);
        *(undefined4 **)(iVar3 + 0x14) = puVar7;
      }
LAB_8024dde8:
      uVar18 = gnt4_HSD_RObjAddAnimAll_bl
                         (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(undefined4 **)(iVar17 + 0x80),(undefined4 *)puVar16[3],puVar7,puVar8,
                          param_13,param_14,param_15,param_16);
      if ((puVar16[4] & 1) == 0) {
        uVar18 = gnt4_HSD_JObjClearFlags
                           (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar17,8,
                            (undefined *)puVar7,puVar8,param_13,param_14,param_15,param_16);
        uVar6 = extraout_r4_01;
      }
      else {
        uVar18 = gnt4_HSD_JObjSetFlags
                           (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar17,8,
                            (undefined *)puVar7,puVar8,param_13,param_14,param_15,param_16);
        uVar6 = extraout_r4_00;
      }
    }
    uVar1 = countLeadingZeros(*(uint *)(iVar17 + 0x14) & 0x4020);
    if (uVar1 >> 5 != 0) {
      if (param_12 == (undefined4 *)0x0) {
        puVar7 = (undefined4 *)0x0;
      }
      else {
        puVar7 = (undefined4 *)param_12[2];
      }
      if (param_11 == (undefined4 *)0x0) {
        puVar4 = (undefined4 *)0x0;
      }
      else {
        puVar4 = (undefined4 *)param_11[2];
      }
      uVar18 = gnt4_HSD_DObjAddAnimAll_bl
                         (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar17 + 0x18),puVar4,puVar7,puVar8,param_13,param_14,param_15,
                          param_16);
      uVar6 = extraout_r4_02;
    }
    if ((*(uint *)(iVar17 + 0x14) & 0x1000) == 0) {
      iVar17 = *(int *)(iVar17 + 0x10);
      if (puVar16 == (undefined4 *)0x0) {
        puVar16 = (undefined4 *)0x0;
      }
      else {
        puVar16 = (undefined4 *)*puVar16;
      }
      if (param_11 == (undefined4 *)0x0) {
        puVar4 = (undefined4 *)0x0;
      }
      else {
        puVar4 = (undefined4 *)*param_11;
      }
      if (param_12 == (undefined4 *)0x0) {
        puVar15 = (undefined4 *)0x0;
      }
      else {
        puVar15 = (undefined4 *)*param_12;
      }
      while (iVar17 != 0) {
        if (iVar17 != 0) {
          if (puVar16 != (undefined4 *)0x0) {
            if (*(undefined4 **)(iVar17 + 0x7c) != (undefined4 *)0x0) {
              uVar18 = gnt4_HSD_AObjRemove(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,
                                           param_8,*(undefined4 **)(iVar17 + 0x7c),uVar6,puVar7,
                                           puVar8,param_13,param_14,param_15,param_16);
              uVar6 = extraout_r4_03;
            }
            puVar2 = gnt4_HSD_AObjLoadDesc
                               (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                (uint *)puVar16[2],uVar6,puVar7,puVar8,param_13,param_14,param_15,
                                param_16);
            *(uint **)(iVar17 + 0x7c) = puVar2;
            uVar18 = gnt4_JObjSortAnim(*(int *)(iVar17 + 0x7c));
            uVar18 = gnt4_HSD_RObjAddAnimAll_bl
                               (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                *(undefined4 **)(iVar17 + 0x80),(undefined4 *)puVar16[3],puVar7,
                                puVar8,param_13,param_14,param_15,param_16);
            if ((puVar16[4] & 1) == 0) {
              uVar18 = gnt4_HSD_JObjClearFlags
                                 (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  iVar17,8,(undefined *)puVar7,puVar8,param_13,param_14,param_15,
                                  param_16);
              uVar6 = extraout_r4_05;
            }
            else {
              uVar18 = gnt4_HSD_JObjSetFlags
                                 (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  iVar17,8,(undefined *)puVar7,puVar8,param_13,param_14,param_15,
                                  param_16);
              uVar6 = extraout_r4_04;
            }
          }
          uVar1 = countLeadingZeros(*(uint *)(iVar17 + 0x14) & 0x4020);
          if (uVar1 >> 5 != 0) {
            if (puVar15 == (undefined4 *)0x0) {
              puVar7 = (undefined4 *)0x0;
            }
            else {
              puVar7 = (undefined4 *)puVar15[2];
            }
            if (puVar4 == (undefined4 *)0x0) {
              puVar5 = (undefined4 *)0x0;
            }
            else {
              puVar5 = (undefined4 *)puVar4[2];
            }
            uVar18 = gnt4_HSD_DObjAddAnimAll_bl
                               (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                *(int *)(iVar17 + 0x18),puVar5,puVar7,puVar8,param_13,param_14,
                                param_15,param_16);
            uVar6 = extraout_r4_06;
          }
          if ((*(uint *)(iVar17 + 0x14) & 0x1000) == 0) {
            iVar3 = *(int *)(iVar17 + 0x10);
            if (puVar16 == (undefined4 *)0x0) {
              piVar13 = (int *)0x0;
            }
            else {
              piVar13 = (int *)*puVar16;
            }
            if (puVar4 == (undefined4 *)0x0) {
              puVar5 = (undefined4 *)0x0;
            }
            else {
              puVar5 = (undefined4 *)*puVar4;
            }
            if (puVar15 == (undefined4 *)0x0) {
              puVar14 = (undefined4 *)0x0;
            }
            else {
              puVar14 = (undefined4 *)*puVar15;
            }
            while (iVar3 != 0) {
              if ((iVar3 != 0) &&
                 (puVar7 = puVar5, puVar8 = puVar14,
                 uVar18 = gnt4_HSD_JObjAddAnim
                                    (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     iVar3,(int)piVar13,puVar5,(int)puVar14,param_13,param_14,
                                     param_15,param_16), uVar6 = extraout_r4_07,
                 (*(uint *)(iVar3 + 0x14) & 0x1000) == 0)) {
                iVar9 = *(int *)(iVar3 + 0x10);
                if (piVar13 == (int *)0x0) {
                  iVar10 = 0;
                }
                else {
                  iVar10 = *piVar13;
                }
                if (puVar5 == (undefined4 *)0x0) {
                  puVar11 = (undefined4 *)0x0;
                }
                else {
                  puVar11 = (undefined4 *)*puVar5;
                }
                if (puVar14 == (undefined4 *)0x0) {
                  puVar12 = (undefined4 *)0x0;
                }
                else {
                  puVar12 = (undefined4 *)*puVar14;
                }
                while (iVar9 != 0) {
                  puVar7 = puVar11;
                  puVar8 = puVar12;
                  uVar18 = gnt4_HSD_JObjAddAnimAll
                                     (uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,iVar9,iVar10,puVar11,puVar12,param_13,param_14,param_15,
                                      param_16);
                  iVar9 = *(int *)(iVar9 + 8);
                  if (iVar10 == 0) {
                    iVar10 = 0;
                  }
                  else {
                    iVar10 = *(int *)(iVar10 + 4);
                  }
                  if (puVar11 == (undefined4 *)0x0) {
                    puVar11 = (undefined4 *)0x0;
                  }
                  else {
                    puVar11 = (undefined4 *)puVar11[1];
                  }
                  uVar6 = extraout_r4_08;
                  if (puVar12 == (undefined4 *)0x0) {
                    puVar12 = (undefined4 *)0x0;
                  }
                  else {
                    puVar12 = (undefined4 *)puVar12[1];
                  }
                }
              }
              iVar3 = *(int *)(iVar3 + 8);
              if (piVar13 == (int *)0x0) {
                piVar13 = (int *)0x0;
              }
              else {
                piVar13 = (int *)piVar13[1];
              }
              if (puVar5 == (undefined4 *)0x0) {
                puVar5 = (undefined4 *)0x0;
              }
              else {
                puVar5 = (undefined4 *)puVar5[1];
              }
              if (puVar14 == (undefined4 *)0x0) {
                puVar14 = (undefined4 *)0x0;
              }
              else {
                puVar14 = (undefined4 *)puVar14[1];
              }
            }
          }
        }
        iVar17 = *(int *)(iVar17 + 8);
        if (puVar16 == (undefined4 *)0x0) {
          puVar16 = (undefined4 *)0x0;
        }
        else {
          puVar16 = (undefined4 *)puVar16[1];
        }
        if (puVar4 == (undefined4 *)0x0) {
          puVar4 = (undefined4 *)0x0;
        }
        else {
          puVar4 = (undefined4 *)puVar4[1];
        }
        if (puVar15 == (undefined4 *)0x0) {
          puVar15 = (undefined4 *)0x0;
        }
        else {
          puVar15 = (undefined4 *)puVar15[1];
        }
      }
    }
  }
  gnt4__restgpr_20_bl();
  return;
}



// ==== 8024e120  gnt4-JObjUpdateFunc ====

/* WARNING: Removing unreachable block (ram,0x8024ea44) */
/* WARNING: Removing unreachable block (ram,0x8024e130) */
/* WARNING: Removing unreachable block (ram,0x8024e480) */
/* WARNING: Removing unreachable block (ram,0x8024e32c) */
/* WARNING: Removing unreachable block (ram,0x8024e244) */
/* WARNING: Removing unreachable block (ram,0x8024e2b8) */
/* WARNING: Removing unreachable block (ram,0x8024e604) */
/* WARNING: Removing unreachable block (ram,0x8024e6f4) */
/* WARNING: Removing unreachable block (ram,0x8024e76c) */
/* WARNING: Removing unreachable block (ram,0x8024e67c) */
/* WARNING: Removing unreachable block (ram,0x8024e58c) */
/* WARNING: Removing unreachable block (ram,0x8024e514) */
/* WARNING: Removing unreachable block (ram,0x8024e3ec) */
/* WARNING: Removing unreachable block (ram,0x8024e7e4) */

void gnt4_JObjUpdateFunc(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8,
                        undefined4 param_9,undefined4 param_10,char *param_11,undefined4 param_12,
                        undefined4 param_13,undefined4 param_14,undefined4 param_15,
                        undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined8 extraout_f1;
  double dVar8;
  double in_f31;
  double in_ps31_1;
  undefined8 uVar9;
  float local_78;
  float local_74;
  float local_70;
  float afStack_6c [13];
  undefined4 local_38;
  float fStack_34;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  uVar9 = gnt4__savegpr_27_bl();
  iVar2 = (int)((ulonglong)uVar9 >> 0x20);
  iVar6 = (int)uVar9;
  uVar5 = 0x803b0000;
  if (iVar2 != 0) {
    switch(iVar6) {
    case 1:
      pcVar4 = param_11;
      uVar9 = extraout_f1;
      if ((*(uint *)(iVar2 + 0x14) & 0x200000) != 0) {
        pcVar4 = (char *)0x0;
        puVar7 = gnt4_HSD_RObjGetByType_bl(*(undefined4 **)(iVar2 + 0x80),0x40000000,0);
        if (puVar7 != (undefined4 *)0x0) {
          puVar7[3] = *(float *)param_11;
        }
      }
      dVar8 = (double)*(float *)param_11;
      if (iVar2 == 0) {
        pcVar4 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ee8,0x2a4,&DAT_80435ef0,uVar5,param_13,param_14,param_15,
                                 param_16);
      }
      if ((*(uint *)(iVar2 + 0x14) & 0x20000) != 0) {
        pcVar4 = s___jobj_>flags___JOBJ_USE_QUATERN_803acc90;
        uVar9 = gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ee8,0x2a5,s___jobj_>flags___JOBJ_USE_QUATERN_803acc90,
                                 uVar5,param_13,param_14,param_15,param_16);
      }
      *(float *)(iVar2 + 0x1c) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                     pcVar4,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      break;
    case 2:
      dVar8 = (double)*(float *)param_11;
      uVar9 = extraout_f1;
      if (iVar2 == 0) {
        param_11 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                 ,&DAT_80435ee8,0x2b8,&DAT_80435ef0,0x803b0000,param_13,param_14,
                                 param_15,param_16);
      }
      if ((*(uint *)(iVar2 + 0x14) & 0x20000) != 0) {
        param_11 = s___jobj_>flags___JOBJ_USE_QUATERN_803acc90;
        uVar9 = gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ee8,0x2b9,s___jobj_>flags___JOBJ_USE_QUATERN_803acc90,
                                 uVar5,param_13,param_14,param_15,param_16);
      }
      *(float *)(iVar2 + 0x20) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                     param_11,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      break;
    case 3:
      dVar8 = (double)*(float *)param_11;
      uVar9 = extraout_f1;
      if (iVar2 == 0) {
        param_11 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                 ,&DAT_80435ee8,0x2cc,&DAT_80435ef0,0x803b0000,param_13,param_14,
                                 param_15,param_16);
      }
      if ((*(uint *)(iVar2 + 0x14) & 0x20000) != 0) {
        param_11 = s___jobj_>flags___JOBJ_USE_QUATERN_803acc90;
        uVar9 = gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ee8,0x2cd,s___jobj_>flags___JOBJ_USE_QUATERN_803acc90,
                                 uVar5,param_13,param_14,param_15,param_16);
      }
      *(float *)(iVar2 + 0x24) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                     param_11,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      break;
    case 4:
      if ((double)*(float *)param_11 < DOUBLE_8043d2f0) {
        *(float *)param_11 = FLOAT_8043d2f8;
      }
      dVar8 = DOUBLE_8043d300;
      if (DOUBLE_8043d300 < (double)*(float *)param_11) {
        *(float *)param_11 = FLOAT_8043d308;
      }
      pcVar4 = param_11;
      if (*(int *)(iVar2 + 0x7c) == 0) {
        pcVar4 = s_jobj_>aobj_803acc74;
        dVar8 = (double)gnt4___assert_bl(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,
                                         param_8,&DAT_80435ef8,0x24e,s_jobj_>aobj_803acc74,
                                         0x803b0000,param_13,param_14,param_15,param_16);
      }
      iVar6 = *(int *)(*(int *)(iVar2 + 0x7c) + 0x18);
      if (iVar6 == 0) {
        pcVar4 = &DAT_80435f00;
        dVar8 = (double)gnt4___assert_bl(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,
                                         param_8,&DAT_80435ef8,0x250,&DAT_80435f00,uVar5,param_13,
                                         param_14,param_15,param_16);
      }
      if (*(int *)(iVar6 + 0x18) == 0) {
        pcVar4 = s_jp_>u_spline_803acc80;
        gnt4___assert_bl(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ef8
                         ,0x251,s_jp_>u_spline_803acc80,uVar5,param_13,param_14,param_15,param_16);
      }
      uVar9 = gnt4_splArcLengthPoint_bl
                        ((double)*(float *)param_11,&local_78,*(byte **)(iVar6 + 0x18));
      dVar8 = (double)local_78;
      if (iVar2 == 0) {
        pcVar4 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ee8,0x3b8,&DAT_80435ef0,uVar5,param_13,param_14,param_15,
                                 param_16);
      }
      *(float *)(iVar2 + 0x38) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          uVar9 = gnt4_HSD_JObjSetMtxDirtySub_bl
                            (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                             uVar3,pcVar4,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      dVar8 = (double)local_74;
      if (iVar2 == 0) {
        pcVar4 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ee8,0x3c6,&DAT_80435ef0,uVar5,param_13,param_14,param_15,
                                 param_16);
      }
      *(float *)(iVar2 + 0x3c) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          uVar9 = gnt4_HSD_JObjSetMtxDirtySub_bl
                            (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                             uVar3,pcVar4,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      dVar8 = (double)local_70;
      if (iVar2 == 0) {
        pcVar4 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ee8,0x3d4,&DAT_80435ef0,uVar5,param_13,param_14,param_15,
                                 param_16);
      }
      *(float *)(iVar2 + 0x40) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                     pcVar4,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      break;
    case 5:
      dVar8 = (double)*(float *)param_11;
      uVar9 = extraout_f1;
      if (iVar2 == 0) {
        param_11 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                 ,&DAT_80435ee8,0x3b8,&DAT_80435ef0,0x803b0000,param_13,param_14,
                                 param_15,param_16);
      }
      *(float *)(iVar2 + 0x38) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                     param_11,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      break;
    case 6:
      dVar8 = (double)*(float *)param_11;
      uVar9 = extraout_f1;
      if (iVar2 == 0) {
        param_11 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                 ,&DAT_80435ee8,0x3c6,&DAT_80435ef0,0x803b0000,param_13,param_14,
                                 param_15,param_16);
      }
      *(float *)(iVar2 + 0x3c) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                     param_11,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      break;
    case 7:
      dVar8 = (double)*(float *)param_11;
      uVar9 = extraout_f1;
      if (iVar2 == 0) {
        param_11 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                 ,&DAT_80435ee8,0x3d4,&DAT_80435ef0,0x803b0000,param_13,param_14,
                                 param_15,param_16);
      }
      *(float *)(iVar2 + 0x40) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                     param_11,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      break;
    case 8:
      dVar8 = (double)*(float *)param_11;
      uVar9 = extraout_f1;
      if (iVar2 == 0) {
        param_11 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                 ,&DAT_80435ee8,0x325,&DAT_80435ef0,0x803b0000,param_13,param_14,
                                 param_15,param_16);
      }
      *(float *)(iVar2 + 0x2c) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                     param_11,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      break;
    case 9:
      dVar8 = (double)*(float *)param_11;
      uVar9 = extraout_f1;
      if (iVar2 == 0) {
        param_11 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                 ,&DAT_80435ee8,0x333,&DAT_80435ef0,0x803b0000,param_13,param_14,
                                 param_15,param_16);
      }
      *(float *)(iVar2 + 0x30) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                     param_11,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      break;
    case 10:
      dVar8 = (double)*(float *)param_11;
      uVar9 = extraout_f1;
      if (iVar2 == 0) {
        param_11 = &DAT_80435ef0;
        uVar9 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                 ,&DAT_80435ee8,0x341,&DAT_80435ef0,0x803b0000,param_13,param_14,
                                 param_15,param_16);
      }
      *(float *)(iVar2 + 0x34) = (float)dVar8;
      if (((*(uint *)(iVar2 + 0x14) & 0x2000000) == 0) && (iVar2 != 0)) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                     param_11,uVar5,param_13,param_14,param_15,param_16);
        }
      }
      break;
    case 0xb:
      dVar8 = (double)*(float *)param_11;
      if (dVar8 <= DOUBLE_8043d310) {
        gnt4_HSD_JObjSetFlags
                  (dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,param_11
                   ,0x803b0000,param_13,param_14,param_15,param_16);
      }
      else {
        gnt4_HSD_JObjClearFlags
                  (dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,param_11
                   ,0x803b0000,param_13,param_14,param_15,param_16);
      }
      break;
    case 0xc:
      dVar8 = (double)*(float *)param_11;
      if (dVar8 <= DOUBLE_8043d310) {
        gnt4_HSD_JObjSetFlagsAll
                  (dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,param_11
                   ,0x803b0000,param_13,param_14,param_15,param_16);
      }
      else {
        gnt4_HSD_JObjClearFlagsAll
                  (dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,param_11
                   ,0x803b0000,param_13,param_14,param_15,param_16);
      }
      break;
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      dVar8 = DOUBLE_8043d318;
      for (puVar7 = DAT_80436984; puVar7 != (undefined4 *)0x0; puVar7 = (undefined4 *)*puVar7) {
        local_38 = 0x43300000;
        fStack_34 = -*(float *)param_11;
        (*(code *)puVar7[1])
                  ((double)(float)((double)CONCAT44(0x43300000,fStack_34) - dVar8),iVar2,iVar6);
      }
      break;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
      for (puVar7 = DAT_80436984; puVar7 != (undefined4 *)0x0; puVar7 = (undefined4 *)*puVar7) {
        (*(code *)puVar7[1])((double)*(float *)param_11,iVar2,iVar6);
      }
      break;
    case 0x28:
      if (DAT_80436988 != (code *)0x0) {
        (*DAT_80436988)(0,(uint)*(float *)param_11 & 0x3f,(uint)*(float *)param_11 >> 6 & 0xffffff,
                        iVar2);
      }
      break;
    case 0x29:
      if (DAT_8043698c != (code *)0x0) {
        (*DAT_8043698c)(*(float *)param_11);
      }
      break;
    case 0x2a:
      if (DAT_80436990 != (code *)0x0) {
        (*DAT_80436990)(iVar2,*(float *)param_11);
      }
      break;
    case 0x32:
      *(float *)(iVar2 + 0x44) = *(float *)param_11;
      *(float *)(iVar2 + 0x54) = *(float *)((int)param_11 + 4);
      *(float *)(iVar2 + 100) = *(float *)((int)param_11 + 8);
      break;
    case 0x33:
      *(float *)(iVar2 + 0x48) = *(float *)param_11;
      *(float *)(iVar2 + 0x58) = *(float *)((int)param_11 + 4);
      *(float *)(iVar2 + 0x68) = *(float *)((int)param_11 + 8);
      break;
    case 0x34:
      *(float *)(iVar2 + 0x4c) = *(float *)param_11;
      *(float *)(iVar2 + 0x5c) = *(float *)((int)param_11 + 4);
      *(float *)(iVar2 + 0x6c) = *(float *)((int)param_11 + 8);
      break;
    case 0x35:
      *(float *)(iVar2 + 0x50) = *(float *)param_11;
      *(float *)(iVar2 + 0x60) = *(float *)((int)param_11 + 4);
      *(float *)(iVar2 + 0x70) = *(float *)((int)param_11 + 8);
      break;
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
      if (*(int *)(iVar2 + 0xc) == 0) {
        gnt4_PSMTXCopy_bl((float *)(iVar2 + 0x44),afStack_6c);
      }
      else {
        gnt4_HSD_MtxInverseConcat_bl
                  ((float *)(*(int *)(iVar2 + 0xc) + 0x44),(float *)(iVar2 + 0x44),afStack_6c);
      }
      if ((iVar6 == 0x36) || (iVar6 == 0x38)) {
        gnt4_HSD_MtxGetTranslate_bl((int)afStack_6c,(undefined4 *)(iVar2 + 0x38));
      }
      if ((iVar6 == 0x36) || (iVar6 == 0x37)) {
        gnt4_HSD_MtxGetRotation_bl(afStack_6c,(float *)(iVar2 + 0x1c));
      }
      if ((iVar6 == 0x36) || (iVar6 == 0x39)) {
        gnt4_HSD_MtxGetScale_bl(afStack_6c,(float *)(iVar2 + 0x2c));
      }
    }
  }
  gnt4__restgpr_27_bl();
  return;
}



// ==== 8024ea64  gnt4-HSD_JObjAnim ====

/* WARNING: Removing unreachable block (ram,0x8024eadc) */
/* WARNING: Removing unreachable block (ram,0x8024ea88) */

void gnt4_HSD_JObjAnim(undefined8 param_1,double param_2,double param_3,double param_4,
                      double param_5,double param_6,double param_7,double param_8,int *param_9,
                      undefined4 param_10,undefined4 param_11,undefined4 param_12,
                      undefined4 param_13,undefined4 param_14,undefined4 param_15,
                      undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar3;
  undefined8 uVar4;
  
  if (param_9 != (int *)0x0) {
    uVar2 = param_9[5];
    bVar1 = false;
    if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      if ((uVar2 & 0x800000) == 0) {
        if (((((param_9[3] != 0) && ((*(uint *)(param_9[3] + 0x14) & 0x40) != 0)) ||
             (uVar2 = uVar2 & 0x600000, uVar2 == 0x200000)) ||
            ((uVar2 == 0x400000 || (uVar2 == 0x600000)))) || (param_9[0x20] != 0)) {
          param_9[5] = param_9[5] | 0x40;
        }
      }
      else if (((uVar2 & 0x1000000) == 0) && (param_9[3] != 0)) {
        uVar2 = *(uint *)(param_9[3] + 0x14);
        bVar1 = false;
        if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          param_9[5] = param_9[5] | 0x40;
        }
      }
    }
    pfVar3 = *(float **)(*param_9 + 0x50);
    uVar4 = gnt4_HSD_AObjInterpretAnim
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       (uint *)param_9[0x1f],(uint)param_9,pfVar3,param_12,param_13,param_14,
                       param_15,param_16);
    uVar4 = gnt4_HSD_RObjAnimAll_bl
                      (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       (undefined4 *)param_9[0x20],extraout_r4,pfVar3,param_12,param_13,param_14,
                       param_15,param_16);
    uVar2 = countLeadingZeros(param_9[5] & 0x4020);
    if (uVar2 >> 5 != 0) {
      gnt4_HSD_DObjAnimAll_bl
                (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)param_9[6],
                 extraout_r4_00,pfVar3,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 8024ebc8  gnt4-JObjAnimAll ====

/* WARNING: Removing unreachable block (ram,0x8024ec4c) */
/* WARNING: Removing unreachable block (ram,0x8024ebf8) */

void gnt4_JObjAnimAll(undefined8 param_1,double param_2,double param_3,double param_4,double param_5
                     ,double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
                     float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                     undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar4;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 extraout_r4_06;
  undefined4 extraout_r4_07;
  undefined4 extraout_r4_08;
  undefined4 extraout_r4_09;
  float *pfVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  undefined8 uVar10;
  
  if (param_9 != (int *)0x0) {
    uVar3 = param_9[5];
    bVar1 = false;
    if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      if ((uVar3 & 0x800000) == 0) {
        if (((((param_9[3] != 0) && ((*(uint *)(param_9[3] + 0x14) & 0x40) != 0)) ||
             (uVar3 = uVar3 & 0x600000, uVar3 == 0x200000)) ||
            ((uVar3 == 0x400000 || (uVar3 == 0x600000)))) || (param_9[0x20] != 0)) {
          param_9[5] = param_9[5] | 0x40;
        }
      }
      else if (((uVar3 & 0x1000000) == 0) && (param_9[3] != 0)) {
        uVar3 = *(uint *)(param_9[3] + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          param_9[5] = param_9[5] | 0x40;
        }
      }
    }
    pfVar5 = *(float **)(*param_9 + 0x50);
    uVar10 = gnt4_HSD_AObjInterpretAnim
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (uint *)param_9[0x1f],(uint)param_9,pfVar5,param_12,param_13,param_14,
                        param_15,param_16);
    uVar10 = gnt4_HSD_RObjAnimAll_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (undefined4 *)param_9[0x20],extraout_r4,pfVar5,param_12,param_13,param_14,
                        param_15,param_16);
    uVar3 = countLeadingZeros(param_9[5] & 0x4020);
    uVar4 = extraout_r4_00;
    if (uVar3 >> 5 != 0) {
      uVar10 = gnt4_HSD_DObjAnimAll_bl
                         (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int *)param_9[6],extraout_r4_00,pfVar5,param_12,param_13,param_14,
                          param_15,param_16);
      uVar4 = extraout_r4_01;
    }
    if ((param_9[5] & 0x1000U) == 0) {
      for (piVar9 = (int *)param_9[4]; piVar9 != (int *)0x0; piVar9 = (int *)piVar9[2]) {
        if (piVar9 != (int *)0x0) {
          iVar2 = gnt4_HSD_JObjMtxIsDirty
                            (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             (int)piVar9,uVar4,pfVar5,param_12,param_13,param_14,param_15,param_16);
          if (iVar2 == 0) {
            uVar3 = piVar9[5];
            if ((uVar3 & 0x800000) == 0) {
              if ((((piVar9[3] != 0) && ((*(uint *)(piVar9[3] + 0x14) & 0x40) != 0)) ||
                  (uVar3 = uVar3 & 0x600000, uVar3 == 0x200000)) ||
                 (((uVar3 == 0x400000 || (uVar3 == 0x600000)) || (piVar9[0x20] != 0)))) {
                piVar9[5] = piVar9[5] | 0x40;
              }
            }
            else if ((((uVar3 & 0x1000000) == 0) && (piVar9[3] != 0)) &&
                    (iVar2 = gnt4_HSD_JObjMtxIsDirty
                                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,piVar9[3],uVar4,pfVar5,param_12,param_13,param_14,
                                        param_15,param_16), iVar2 != 0)) {
              piVar9[5] = piVar9[5] | 0x40;
            }
          }
          pfVar5 = *(float **)(*piVar9 + 0x50);
          uVar10 = gnt4_HSD_AObjInterpretAnim
                             (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (uint *)piVar9[0x1f],(uint)piVar9,pfVar5,param_12,param_13,param_14,
                              param_15,param_16);
          uVar10 = gnt4_HSD_RObjAnimAll_bl
                             (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (undefined4 *)piVar9[0x20],extraout_r4_02,pfVar5,param_12,param_13,
                              param_14,param_15,param_16);
          uVar3 = countLeadingZeros(piVar9[5] & 0x4020);
          uVar4 = extraout_r4_03;
          if (uVar3 >> 5 != 0) {
            uVar10 = gnt4_HSD_DObjAnimAll_bl
                               (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                (int *)piVar9[6],extraout_r4_03,pfVar5,param_12,param_13,param_14,
                                param_15,param_16);
            uVar4 = extraout_r4_04;
          }
          if ((piVar9[5] & 0x1000U) == 0) {
            for (piVar8 = (int *)piVar9[4]; piVar8 != (int *)0x0; piVar8 = (int *)piVar8[2]) {
              if (piVar8 != (int *)0x0) {
                uVar10 = gnt4_HSD_JObjCheckDepend
                                   (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    (int)piVar8,uVar4,pfVar5,param_12,param_13,param_14,param_15,
                                    param_16);
                pfVar5 = *(float **)(*piVar8 + 0x50);
                uVar10 = gnt4_HSD_AObjInterpretAnim
                                   (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    (uint *)piVar8[0x1f],(uint)piVar8,pfVar5,param_12,param_13,
                                    param_14,param_15,param_16);
                uVar10 = gnt4_HSD_RObjAnimAll_bl
                                   (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    (undefined4 *)piVar8[0x20],extraout_r4_05,pfVar5,param_12,
                                    param_13,param_14,param_15,param_16);
                uVar3 = countLeadingZeros(piVar8[5] & 0x4020);
                uVar4 = extraout_r4_06;
                if (uVar3 >> 5 != 0) {
                  uVar10 = gnt4_HSD_DObjAnimAll_bl
                                     (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,(int *)piVar8[6],extraout_r4_06,pfVar5,param_12,param_13,
                                      param_14,param_15,param_16);
                  uVar4 = extraout_r4_07;
                }
                if ((piVar8[5] & 0x1000U) == 0) {
                  for (piVar7 = (int *)piVar8[4]; piVar7 != (int *)0x0; piVar7 = (int *)piVar7[2]) {
                    if ((piVar7 != (int *)0x0) &&
                       (uVar10 = gnt4_HSD_JObjAnim(uVar10,param_2,param_3,param_4,param_5,param_6,
                                                   param_7,param_8,piVar7,uVar4,pfVar5,param_12,
                                                   param_13,param_14,param_15,param_16),
                       uVar4 = extraout_r4_08, (piVar7[5] & 0x1000U) == 0)) {
                      for (piVar6 = (int *)piVar7[4]; piVar6 != (int *)0x0;
                          piVar6 = (int *)piVar6[2]) {
                        uVar10 = gnt4_JObjAnimAll(uVar10,param_2,param_3,param_4,param_5,param_6,
                                                  param_7,param_8,piVar6,uVar4,pfVar5,param_12,
                                                  param_13,param_14,param_15,param_16);
                        uVar4 = extraout_r4_09;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}



// ==== 8024ef10  gnt4-HSD_JObjAnimAll ====

void gnt4_HSD_JObjAnimAll
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  if (param_9 != (int *)0x0) {
    uVar1 = gnt4_HSD_AObjInitEndCallBack();
    gnt4_JObjAnimAll(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                     extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
    gnt4_HSD_AObjInvokeCallBacks();
  }
  return;
}



// ==== 8024ef4c  gnt4-setupInstanceMtx ====

/* WARNING: Removing unreachable block (ram,0x8024efc8) */

void gnt4_setupInstanceMtx
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,float *param_9,int *param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int *piVar5;
  
  pfVar4 = param_11;
  if (param_10 != (int *)0x0) {
    if (param_10 == (int *)0x0) {
      pfVar4 = (float *)&DAT_80435ef0;
      param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ee8,0x25d,&DAT_80435ef0,param_12,param_13,param_14,
                                 param_15,param_16);
    }
    uVar3 = param_10[5];
    bVar1 = false;
    if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (bVar1) {
      param_1 = gnt4_HSD_JObjSetupMatrixSub_bl
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                           uVar3,pfVar4,param_12,param_13,param_14,param_15,param_16);
    }
  }
  piVar5 = (int *)param_10[4];
  if (piVar5 != (int *)0x0) {
    uVar3 = piVar5[5];
    bVar1 = false;
    if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (bVar1) {
      gnt4_HSD_JObjSetupMatrixSub_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar5,uVar3,pfVar4
                 ,param_12,param_13,param_14,param_15,param_16);
    }
  }
  gnt4_PSMTXInverse_bl((float *)(param_10[4] + 0x44),param_11);
  gnt4_PSMTXConcat_bl((float *)(param_10 + 0x11),param_11,param_11);
  if (param_9 == (float *)0x0) {
    iVar2 = gnt4_HSD_CObjGetCurrent();
    if (iVar2 != 0) {
      gnt4_PSMTXConcat_bl((float *)(iVar2 + 0x54),param_11,param_11);
    }
  }
  else {
    gnt4_PSMTXConcat_bl(param_9,param_11,param_11);
  }
  return;
}



// ==== 8024f07c  gnt4-HSD_JObjDispAll ====

/* WARNING: Removing unreachable block (ram,0x8024f0c4) */
/* WARNING: Removing unreachable block (ram,0x8024f110) */

void gnt4_HSD_JObjDispAll
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               float *param_11,float param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  float *pfVar4;
  float *pfVar5;
  uint uVar6;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar7;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  float *extraout_r4_03;
  undefined4 extraout_r4_04;
  float *extraout_r4_05;
  float *extraout_r4_06;
  float *extraout_r4_07;
  float *extraout_r4_08;
  float *extraout_r4_09;
  float *extraout_r4_10;
  float *extraout_r4_11;
  float *extraout_r4_12;
  float *extraout_r4_13;
  float *extraout_r4_14;
  float *pfVar8;
  float fVar9;
  uint uVar10;
  int iVar11;
  int *piVar12;
  int *piVar13;
  undefined8 extraout_f1;
  undefined8 uVar14;
  float afStack_178 [12];
  float afStack_148 [12];
  float afStack_118 [12];
  float afStack_e8 [12];
  float afStack_b8 [12];
  float afStack_88 [12];
  float afStack_58 [22];
  
  uVar14 = gnt4__savegpr_24_bl();
  piVar12 = (int *)((ulonglong)uVar14 >> 0x20);
  pfVar5 = (float *)uVar14;
  if (piVar12 != (int *)0x0) {
    uVar10 = piVar12[5];
    if ((uVar10 & 0x1000) == 0) {
      uVar6 = (int)param_11 << 0x12;
      pfVar4 = pfVar5;
      pfVar8 = param_11;
      fVar9 = param_12;
      uVar14 = extraout_f1;
      if ((uVar10 & uVar6) != 0) {
        uVar14 = gnt4_HSD_JObjDisp_bl
                           (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int)piVar12,pfVar5,(undefined *)param_11,param_12,uVar10,param_14,
                            param_15,param_16);
        pfVar4 = extraout_r4_03;
      }
      uVar1 = (int)param_11 << 0x1c;
      if ((piVar12[5] & uVar1) != 0) {
        for (piVar12 = (int *)piVar12[4]; piVar12 != (int *)0x0; piVar12 = (int *)piVar12[2]) {
          if (piVar12 != (int *)0x0) {
            uVar3 = piVar12[5];
            if ((uVar3 & 0x1000) == 0) {
              if ((uVar3 & uVar6) != 0) {
                pfVar8 = param_11;
                fVar9 = param_12;
                uVar14 = gnt4_HSD_JObjDisp_bl
                                   (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    (int)piVar12,pfVar5,(undefined *)param_11,param_12,uVar10,
                                    param_14,param_15,param_16);
                pfVar4 = extraout_r4_11;
              }
              if ((piVar12[5] & uVar1) != 0) {
                for (piVar13 = (int *)piVar12[4]; piVar13 != (int *)0x0; piVar13 = (int *)piVar13[2]
                    ) {
                  if (piVar13 != (int *)0x0) {
                    uVar3 = piVar13[5];
                    if ((uVar3 & 0x1000) == 0) {
                      if ((uVar3 & uVar6) != 0) {
                        pfVar8 = param_11;
                        fVar9 = param_12;
                        uVar14 = gnt4_HSD_JObjDisp_bl
                                           (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,(int)piVar13,pfVar5,(undefined *)param_11,
                                            param_12,uVar10,param_14,param_15,param_16);
                        pfVar4 = extraout_r4_13;
                      }
                      if ((piVar13[5] & uVar1) != 0) {
                        for (iVar11 = piVar13[4]; iVar11 != 0; iVar11 = *(int *)(iVar11 + 8)) {
                          pfVar8 = param_11;
                          fVar9 = param_12;
                          uVar14 = gnt4_HSD_JObjDispAll
                                             (uVar14,param_2,param_3,param_4,param_5,param_6,param_7
                                              ,param_8,iVar11,pfVar5,param_11,param_12,uVar10,
                                              param_14,param_15,param_16);
                          pfVar4 = extraout_r4_14;
                        }
                      }
                    }
                    else if ((uVar3 & 0x10) == 0) {
                      uVar14 = gnt4_setupInstanceMtx
                                         (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,pfVar5,piVar13,afStack_178,fVar9,uVar10,param_14,
                                          param_15,param_16);
                      pfVar8 = param_11;
                      fVar9 = param_12;
                      uVar14 = gnt4_HSD_JObjDispAll
                                         (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,piVar13[4],afStack_178,param_11,param_12,uVar10,
                                          param_14,param_15,param_16);
                      pfVar4 = extraout_r4_12;
                    }
                  }
                }
              }
            }
            else if ((uVar3 & 0x10) == 0) {
              uVar14 = gnt4_HSD_JObjSetupMatrix_
                                 (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  piVar12,pfVar4,(undefined *)pfVar8,fVar9,uVar10,param_14,param_15,
                                  param_16);
              gnt4_HSD_JObjSetupMatrix_
                        (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         (int *)piVar12[4],extraout_r4_04,(undefined *)pfVar8,fVar9,uVar10,param_14,
                         param_15,param_16);
              gnt4_PSMTXInverse_bl((float *)(piVar12[4] + 0x44),afStack_b8);
              pfVar8 = afStack_b8;
              uVar14 = gnt4_PSMTXConcat_bl((float *)(piVar12 + 0x11),pfVar8,pfVar8);
              if (pfVar5 == (float *)0x0) {
                pfVar4 = extraout_r4_05;
                iVar11 = gnt4_HSD_CObjGetCurrent();
                if (iVar11 != 0) {
                  pfVar4 = (float *)gnt4_HSD_CObjGetViewingMtxPtrDirect_bl(iVar11);
                  pfVar8 = afStack_b8;
                  uVar14 = gnt4_PSMTXConcat_bl(pfVar4,pfVar8,pfVar8);
                  pfVar4 = extraout_r4_07;
                }
              }
              else {
                pfVar8 = afStack_b8;
                uVar14 = gnt4_PSMTXConcat_bl(pfVar5,pfVar8,pfVar8);
                pfVar4 = extraout_r4_06;
              }
              piVar13 = (int *)piVar12[4];
              if (piVar13 != (int *)0x0) {
                uVar3 = piVar13[5];
                if ((uVar3 & 0x1000) == 0) {
                  if ((uVar3 & uVar6) != 0) {
                    pfVar8 = param_11;
                    fVar9 = param_12;
                    uVar14 = gnt4_HSD_JObjDisp_bl
                                       (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,(int)piVar13,afStack_b8,(undefined *)param_11,
                                        param_12,uVar10,param_14,param_15,param_16);
                    pfVar4 = extraout_r4_09;
                  }
                  if ((piVar13[5] & uVar1) != 0) {
                    for (iVar11 = piVar13[4]; iVar11 != 0; iVar11 = *(int *)(iVar11 + 8)) {
                      pfVar8 = param_11;
                      fVar9 = param_12;
                      uVar14 = gnt4_HSD_JObjDispAll
                                         (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,iVar11,afStack_b8,param_11,param_12,uVar10,
                                          param_14,param_15,param_16);
                      pfVar4 = extraout_r4_10;
                    }
                  }
                }
                else if ((uVar3 & 0x10) == 0) {
                  uVar14 = gnt4_setupInstanceMtx
                                     (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,afStack_b8,piVar13,afStack_148,fVar9,uVar10,param_14,param_15
                                      ,param_16);
                  pfVar8 = param_11;
                  fVar9 = param_12;
                  uVar14 = gnt4_HSD_JObjDispAll
                                     (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,piVar13[4],afStack_148,param_11,param_12,uVar10,param_14,
                                      param_15,param_16);
                  pfVar4 = extraout_r4_08;
                }
              }
            }
          }
        }
      }
    }
    else if ((uVar10 & 0x10) == 0) {
      pfVar4 = param_11;
      fVar9 = param_12;
      uVar14 = extraout_f1;
      if (piVar12 != (int *)0x0) {
        uVar6 = piVar12[5];
        bVar2 = false;
        if (((uVar6 & 0x800000) == 0) && ((uVar6 & 0x40) != 0)) {
          bVar2 = true;
        }
        if (bVar2) {
          uVar14 = gnt4_HSD_JObjSetupMatrixSub_bl
                             (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              piVar12,uVar6,param_11,param_12,uVar10,param_14,param_15,param_16);
        }
      }
      piVar13 = (int *)piVar12[4];
      if (piVar13 != (int *)0x0) {
        uVar6 = piVar13[5];
        bVar2 = false;
        if (((uVar6 & 0x800000) == 0) && ((uVar6 & 0x40) != 0)) {
          bVar2 = true;
        }
        if (bVar2) {
          gnt4_HSD_JObjSetupMatrixSub_bl
                    (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar13,uVar6,
                     pfVar4,fVar9,uVar10,param_14,param_15,param_16);
        }
      }
      gnt4_PSMTXInverse_bl((float *)(piVar12[4] + 0x44),afStack_58);
      pfVar4 = afStack_58;
      uVar14 = gnt4_PSMTXConcat_bl((float *)(piVar12 + 0x11),pfVar4,pfVar4);
      if (pfVar5 == (float *)0x0) {
        uVar7 = extraout_r4;
        iVar11 = gnt4_HSD_CObjGetCurrent();
        if (iVar11 != 0) {
          pfVar4 = afStack_58;
          uVar14 = gnt4_PSMTXConcat_bl((float *)(iVar11 + 0x54),pfVar4,pfVar4);
          uVar7 = extraout_r4_01;
        }
      }
      else {
        pfVar4 = afStack_58;
        uVar14 = gnt4_PSMTXConcat_bl(pfVar5,pfVar4,pfVar4);
        uVar7 = extraout_r4_00;
      }
      piVar12 = (int *)piVar12[4];
      if (piVar12 != (int *)0x0) {
        uVar6 = piVar12[5];
        if ((uVar6 & 0x1000) == 0) {
          if ((uVar6 & (int)param_11 << 0x12) != 0) {
            fVar9 = param_12;
            uVar14 = gnt4_HSD_JObjDisp_bl
                               (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                (int)piVar12,afStack_58,(undefined *)param_11,param_12,uVar10,
                                param_14,param_15,param_16);
          }
          if ((piVar12[5] & (int)param_11 << 0x1c) != 0) {
            for (piVar12 = (int *)piVar12[4]; piVar12 != (int *)0x0; piVar12 = (int *)piVar12[2]) {
              if (piVar12 != (int *)0x0) {
                uVar6 = piVar12[5];
                if ((uVar6 & 0x1000) == 0) {
                  if ((uVar6 & (int)param_11 << 0x12) != 0) {
                    fVar9 = param_12;
                    uVar14 = gnt4_HSD_JObjDisp_bl
                                       (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,(int)piVar12,afStack_58,(undefined *)param_11,
                                        param_12,uVar10,param_14,param_15,param_16);
                  }
                  if ((piVar12[5] & (int)param_11 << 0x1c) != 0) {
                    for (iVar11 = piVar12[4]; iVar11 != 0; iVar11 = *(int *)(iVar11 + 8)) {
                      fVar9 = param_12;
                      uVar14 = gnt4_HSD_JObjDispAll
                                         (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,iVar11,afStack_58,param_11,param_12,uVar10,
                                          param_14,param_15,param_16);
                    }
                  }
                }
                else if ((uVar6 & 0x10) == 0) {
                  uVar14 = gnt4_setupInstanceMtx
                                     (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,afStack_58,piVar12,afStack_118,fVar9,uVar10,param_14,param_15
                                      ,param_16);
                  fVar9 = param_12;
                  uVar14 = gnt4_HSD_JObjDispAll
                                     (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,piVar12[4],afStack_118,param_11,param_12,uVar10,param_14,
                                      param_15,param_16);
                }
              }
            }
          }
        }
        else if ((uVar6 & 0x10) == 0) {
          uVar14 = gnt4_HSD_JObjSetupMatrix_
                             (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar12
                              ,uVar7,(undefined *)pfVar4,fVar9,uVar10,param_14,param_15,param_16);
          gnt4_HSD_JObjSetupMatrix_
                    (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     (int *)piVar12[4],extraout_r4_02,(undefined *)pfVar4,fVar9,uVar10,param_14,
                     param_15,param_16);
          gnt4_PSMTXInverse_bl((float *)(piVar12[4] + 0x44),afStack_88);
          gnt4_PSMTXConcat_bl((float *)(piVar12 + 0x11),afStack_88,afStack_88);
          uVar14 = gnt4_PSMTXConcat_bl(afStack_58,afStack_88,afStack_88);
          piVar12 = (int *)piVar12[4];
          if (piVar12 != (int *)0x0) {
            uVar6 = piVar12[5];
            if ((uVar6 & 0x1000) == 0) {
              if ((uVar6 & (int)param_11 << 0x12) != 0) {
                uVar14 = gnt4_HSD_JObjDisp_bl
                                   (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    (int)piVar12,afStack_88,(undefined *)param_11,param_12,uVar10,
                                    param_14,param_15,param_16);
              }
              if ((piVar12[5] & (int)param_11 << 0x1c) != 0) {
                for (iVar11 = piVar12[4]; iVar11 != 0; iVar11 = *(int *)(iVar11 + 8)) {
                  uVar14 = gnt4_HSD_JObjDispAll
                                     (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,iVar11,afStack_88,param_11,param_12,uVar10,param_14,param_15,
                                      param_16);
                }
              }
            }
            else if ((uVar6 & 0x10) == 0) {
              uVar14 = gnt4_setupInstanceMtx
                                 (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  afStack_88,piVar12,afStack_e8,fVar9,uVar10,param_14,param_15,
                                  param_16);
              gnt4_HSD_JObjDispAll
                        (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar12[4],
                         afStack_e8,param_11,param_12,uVar10,param_14,param_15,param_16);
            }
          }
        }
      }
    }
  }
  gnt4__restgpr_24_bl();
  return;
}



// ==== 8024f5c0  gnt4-HSD_CObjGetViewingMtxPtrDirect-bl ====

int gnt4_HSD_CObjGetViewingMtxPtrDirect_bl(int param_1)

{
  return param_1 + 0x54;
}



// ==== 8024f5c8  gnt4-HSD_JObjSetupMatrix_ ====

void gnt4_HSD_JObjSetupMatrix_
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  
  if (param_9 != (int *)0x0) {
    if (param_9 == (int *)0x0) {
      param_11 = &DAT_80435ef0;
      param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ee8,0x25d,&DAT_80435ef0,param_12,param_13,param_14,
                                 param_15,param_16);
    }
    uVar2 = param_9[5];
    bVar1 = false;
    if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (bVar1) {
      gnt4_HSD_JObjSetupMatrixSub_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar2,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 8024f638  gnt4-JObjLoad ====

undefined4
gnt4_JObjLoad(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
             double param_6,double param_7,double param_8,char *param_9,int param_10,
             undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
             undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  char *pcVar4;
  int *piVar5;
  int *piVar6;
  undefined8 extraout_f1;
  undefined8 uVar7;
  undefined8 uVar8;
  
  param_9[0x10] = '\0';
  param_9[0x11] = '\0';
  param_9[0x12] = '\0';
  param_9[0x13] = '\0';
  param_9[8] = '\0';
  param_9[9] = '\0';
  param_9[10] = '\0';
  param_9[0xb] = '\0';
  param_9[0xc] = '\0';
  param_9[0xd] = '\0';
  param_9[0xe] = '\0';
  param_9[0xf] = '\0';
  *(uint *)(param_9 + 0x14) = *(uint *)(param_9 + 0x14) | *(uint *)(param_10 + 4);
  iVar3 = param_10;
  if ((*(uint *)(param_9 + 0x14) >> 0xe & 1) == 0) {
    if ((*(uint *)(param_9 + 0x14) & 0x20) == 0) {
      piVar5 = gnt4_HSD_DObjLoadDesc_bl
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int **)(param_10 + 0x10),param_10,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      *(int **)(param_9 + 0x18) = piVar5;
    }
    else {
      *(undefined4 *)(param_9 + 0x18) = *(undefined4 *)(param_10 + 0x10);
      for (puVar2 = *(undefined4 **)(param_10 + 0x10); puVar2 != (undefined4 *)0x0;
          puVar2 = (undefined4 *)*puVar2) {
        puVar2[1] = puVar2[1] | 0x80000000;
      }
    }
  }
  else {
    *(undefined4 *)(param_9 + 0x18) = *(undefined4 *)(param_10 + 0x10);
  }
  uVar1 = gnt4_HSD_RObjLoadDesc_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     *(undefined4 *)(param_10 + 0x3c),iVar3,param_11,param_12,param_13,param_14,
                     param_15,param_16);
  *(undefined4 *)(param_9 + 0x80) = uVar1;
  *(undefined4 *)(param_9 + 0x1c) = *(undefined4 *)(param_10 + 0x14);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_10 + 0x18);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_10 + 0x1c);
  uVar1 = *(undefined4 *)(param_10 + 0x24);
  *(undefined4 *)(param_9 + 0x2c) = *(undefined4 *)(param_10 + 0x20);
  *(undefined4 *)(param_9 + 0x30) = uVar1;
  *(undefined4 *)(param_9 + 0x34) = *(undefined4 *)(param_10 + 0x28);
  uVar1 = *(undefined4 *)(param_10 + 0x30);
  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_10 + 0x2c);
  *(undefined4 *)(param_9 + 0x3c) = uVar1;
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_10 + 0x34);
  uVar8 = gnt4_PSMTXIdentity_bl((float *)(param_9 + 0x44));
  param_9[0x74] = '\0';
  param_9[0x75] = '\0';
  param_9[0x76] = '\0';
  param_9[0x77] = '\0';
  uVar7 = extraout_f1;
  if (*(int *)(param_10 + 0x38) != 0) {
    puVar2 = gnt4_HSD_MtxAlloc_bl
                       (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar8 >> 0x20),(int)uVar8,param_11,param_12,param_13,
                        param_14,param_15,param_16);
    *(undefined4 **)(param_9 + 0x78) = puVar2;
    gnt4_memcpy(*(void **)(param_9 + 0x78),*(void **)(param_10 + 0x38),0x30);
  }
  pcVar4 = param_9;
  uVar7 = gnt4_HSD_IDInsertToTable_bl
                    (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,param_10,
                     param_9,param_12,param_13,param_14,param_15,param_16);
  *(int *)(param_9 + 0x84) = param_10;
  if ((*(uint *)(param_10 + 4) & 0x1000) == 0) {
    uVar1 = extraout_r4;
    for (piVar5 = *(int **)(param_10 + 8); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[3]) {
      if (piVar5 == (int *)0x0) {
        piVar6 = (int *)0x0;
      }
      else {
        if ((*piVar5 == 0) ||
           (puVar2 = (undefined4 *)
                     gnt4_hsdSearchClassInfo_bl
                               (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                *piVar5,uVar1,pcVar4,param_12,param_13,param_14,param_15,param_16),
           puVar2 == (undefined4 *)0x0)) {
          piVar6 = gnt4_HSD_JObjAlloc(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8)
          ;
        }
        else {
          piVar6 = gnt4_hsdNew_bl(puVar2);
          if (piVar6 == (int *)0x0) {
            gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80435ef8,0x3d5,&DAT_80435ef0,param_12,param_13,param_14,param_15,
                             param_16);
          }
        }
        param_12 = *piVar6;
        pcVar4 = param_9;
        uVar7 = (**(code **)(param_12 + 0x3c))(piVar6,piVar5);
      }
      if (piVar6 == (int *)0x0) {
        return 0xffffffff;
      }
      uVar7 = gnt4_HSD_JObjAddChild
                        (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
                         (int)piVar6,pcVar4,param_12,param_13,param_14,param_15,param_16);
      uVar1 = extraout_r4_00;
    }
  }
  return 0;
}



// ==== 8024f834  gnt4-HSD_JObjLoadJoint ====

int * gnt4_HSD_JObjLoadJoint
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int *piVar2;
  
  if (param_9 == (int *)0x0) {
    piVar2 = (int *)0x0;
    goto LAB_8024f8b4;
  }
  if (*param_9 == 0) {
LAB_8024f870:
    piVar2 = gnt4_HSD_JObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  else {
    puVar1 = (undefined4 *)
             gnt4_hsdSearchClassInfo_bl
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*param_9,
                        param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    if (puVar1 == (undefined4 *)0x0) goto LAB_8024f870;
    piVar2 = gnt4_hsdNew_bl(puVar1);
    if (piVar2 == (int *)0x0) {
      gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ef8
                       ,0x3d5,&DAT_80435ef0,param_12,param_13,param_14,param_15,param_16);
    }
  }
  param_1 = (**(code **)(*piVar2 + 0x3c))(piVar2,param_9,0);
LAB_8024f8b4:
  gnt4_HSD_JObjResolveRefsAll(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return piVar2;
}



// ==== 8024f8dc  gnt4-HSD_JObjResolveRefs ====

void gnt4_HSD_JObjResolveRefs
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  undefined8 uVar4;
  
  if ((param_9 != 0) && (param_10 != 0)) {
    uVar4 = gnt4_HSD_RObjResolveRefsAll_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(undefined4 **)(param_9 + 0x80),*(undefined4 **)(param_10 + 0x3c),param_11,
                       param_12,param_13,param_14,param_15,param_16);
    if ((*(uint *)(param_9 + 0x14) & 0x1000) != 0) {
      uVar4 = gnt4_HSD_JObjUnref(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_9 + 0x10),extraout_r4,param_11,param_12,param_13,
                                 param_14,param_15,param_16);
      uVar2 = gnt4_HSD_IDGetDataFromTable_bl
                        ((undefined *)0x0,*(uint *)(param_10 + 8),(undefined4 *)0x0);
      *(undefined4 *)(param_9 + 0x10) = uVar2;
      if (*(int *)(param_9 + 0x10) == 0) {
        uVar4 = gnt4___assert_bl(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ef8,0x45f,s_jobj_>child_803acde4,param_12,param_13,
                                 param_14,param_15,param_16);
      }
      iVar3 = *(int *)(param_9 + 0x10);
      if ((iVar3 != 0) &&
         (*(short *)(iVar3 + 4) = *(short *)(iVar3 + 4) + 1, *(short *)(iVar3 + 4) == -1)) {
        uVar4 = gnt4___assert_bl(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 s_object_h_803acdf0,0x5d,
                                 s_HSD_OBJ_o__>ref_count____HSD_OBJ_803acdfc,param_12,param_13,
                                 param_14,param_15,param_16);
      }
    }
    uVar1 = countLeadingZeros(*(uint *)(param_9 + 0x14) & 0x4020);
    if (uVar1 >> 5 != 0) {
      gnt4_HSD_DObjResolveRefsAll_bl
                (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                 *(int *)(param_9 + 0x18),*(int *)(param_10 + 0x10));
    }
  }
  return;
}



// ==== 8024f9d4  gnt4-HSD_JObjResolveRefsAll ====

void gnt4_HSD_JObjResolveRefsAll
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  undefined4 extraout_r4_00;
  uint extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  char *pcVar4;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined8 extraout_f1;
  undefined8 uVar12;
  undefined8 extraout_f1_00;
  undefined8 uVar13;
  
  uVar13 = gnt4__savegpr_23_bl();
  pcVar4 = (char *)0x803b0000;
  uVar12 = extraout_f1;
  while ((iVar9 = (int)((ulonglong)uVar13 >> 0x20), iVar10 = (int)uVar13, iVar9 != 0 &&
         (iVar10 != 0))) {
    if ((iVar9 != 0) && (iVar10 != 0)) {
      uVar12 = gnt4_HSD_RObjResolveRefsAll_bl
                         (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(undefined4 **)(iVar9 + 0x80),*(undefined4 **)(iVar10 + 0x3c),pcVar4,
                          in_r6,in_r7,in_r8,in_r9,in_r10);
      if ((*(uint *)(iVar9 + 0x14) & 0x1000) != 0) {
        uVar12 = gnt4_HSD_JObjUnref(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(int **)(iVar9 + 0x10),extraout_r4,pcVar4,in_r6,in_r7,in_r8,
                                    in_r9,in_r10);
        pcVar4 = (char *)0x0;
        uVar2 = gnt4_HSD_IDGetDataFromTable_bl
                          ((undefined *)0x0,*(uint *)(iVar10 + 8),(undefined4 *)0x0);
        *(undefined4 *)(iVar9 + 0x10) = uVar2;
        if (*(int *)(iVar9 + 0x10) == 0) {
          pcVar4 = s_jobj_>child_803acde4;
          uVar12 = gnt4___assert_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80435ef8,0x45f,s_jobj_>child_803acde4,in_r6,in_r7,in_r8,
                                    in_r9,in_r10);
        }
        iVar3 = *(int *)(iVar9 + 0x10);
        if (iVar3 != 0) {
          *(short *)(iVar3 + 4) = *(short *)(iVar3 + 4) + 1;
          if (*(short *)(iVar3 + 4) == -1) {
            pcVar4 = s_HSD_OBJ_o__>ref_count____HSD_OBJ_803acdfc;
            uVar12 = gnt4___assert_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,s_object_h_803acdf0,0x5d,
                                      s_HSD_OBJ_o__>ref_count____HSD_OBJ_803acdfc,in_r6,in_r7,in_r8,
                                      in_r9,in_r10);
          }
        }
      }
      uVar1 = countLeadingZeros(*(uint *)(iVar9 + 0x14) & 0x4020);
      if (uVar1 >> 5 != 0) {
        uVar12 = gnt4_HSD_DObjResolveRefsAll_bl
                           (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(iVar9 + 0x18),*(int *)(iVar10 + 0x10));
      }
    }
    if ((*(uint *)(iVar9 + 0x14) & 0x1000) == 0) {
      iVar11 = *(int *)(iVar9 + 0x10);
      for (iVar3 = *(int *)(iVar10 + 8); (iVar11 != 0 && (iVar3 != 0));
          iVar3 = *(int *)(iVar3 + 0xc)) {
        if ((iVar11 != 0) && (iVar3 != 0)) {
          uVar12 = gnt4_HSD_RObjResolveRefsAll_bl
                             (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(undefined4 **)(iVar11 + 0x80),*(undefined4 **)(iVar3 + 0x3c),pcVar4,
                              in_r6,in_r7,in_r8,in_r9,in_r10);
          if ((*(uint *)(iVar11 + 0x14) & 0x1000) != 0) {
            uVar12 = gnt4_HSD_JObjUnref(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,*(int **)(iVar11 + 0x10),extraout_r4_00,pcVar4,in_r6
                                        ,in_r7,in_r8,in_r9,in_r10);
            uVar1 = *(uint *)(iVar3 + 8);
            pcVar4 = (char *)0x0;
            uVar2 = gnt4_HSD_IDGetDataFromTable_bl((undefined *)0x0,uVar1,(undefined4 *)0x0);
            *(undefined4 *)(iVar11 + 0x10) = uVar2;
            if (*(int *)(iVar11 + 0x10) == 0) {
              pcVar4 = s_jobj_>child_803acde4;
              uVar12 = gnt4___assert_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,&DAT_80435ef8,0x45f,s_jobj_>child_803acde4,in_r6,
                                        in_r7,in_r8,in_r9,in_r10);
              uVar1 = extraout_r4_01;
            }
            if (*(int *)(iVar11 + 0x10) != 0) {
              uVar12 = gnt4_ref_INC(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(int *)(iVar11 + 0x10),uVar1,pcVar4,in_r6,in_r7,in_r8,in_r9,
                                    in_r10);
            }
          }
          uVar1 = countLeadingZeros(*(uint *)(iVar11 + 0x14) & 0x4020);
          if (uVar1 >> 5 != 0) {
            uVar12 = gnt4_HSD_DObjResolveRefsAll_bl
                               (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                *(int *)(iVar11 + 0x18),*(int *)(iVar3 + 0x10));
          }
        }
        if ((*(uint *)(iVar11 + 0x14) & 0x1000) == 0) {
          iVar8 = *(int *)(iVar11 + 0x10);
          for (iVar7 = *(int *)(iVar3 + 8); (iVar8 != 0 && (iVar7 != 0));
              iVar7 = *(int *)(iVar7 + 0xc)) {
            if ((iVar8 != 0) && (iVar7 != 0)) {
              uVar12 = gnt4_HSD_RObjResolveRefsAll_bl
                                 (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  *(undefined4 **)(iVar8 + 0x80),*(undefined4 **)(iVar7 + 0x3c),
                                  pcVar4,in_r6,in_r7,in_r8,in_r9,in_r10);
              if ((*(uint *)(iVar8 + 0x14) & 0x1000) != 0) {
                gnt4_HSD_JObjUnref(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   *(int **)(iVar8 + 0x10),extraout_r4_02,pcVar4,in_r6,in_r7,in_r8,
                                   in_r9,in_r10);
                uVar13 = gnt4_HSD_IDGetData(*(uint *)(iVar7 + 8),(undefined4 *)0x0);
                uVar2 = (undefined4)uVar13;
                *(int *)(iVar8 + 0x10) = (int)((ulonglong)uVar13 >> 0x20);
                uVar13 = extraout_f1_00;
                if (*(int *)(iVar8 + 0x10) == 0) {
                  pcVar4 = s_jobj_>child_803acde4;
                  uVar13 = gnt4___assert_bl(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,
                                            param_7,param_8,&DAT_80435ef8,0x45f,
                                            s_jobj_>child_803acde4,in_r6,in_r7,in_r8,in_r9,in_r10);
                  uVar2 = extraout_r4_03;
                }
                uVar12 = gnt4_HSD_JObjRef(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,*(int *)(iVar8 + 0x10),uVar2,pcVar4,in_r6,in_r7,
                                          in_r8,in_r9,in_r10);
              }
              uVar1 = countLeadingZeros(*(uint *)(iVar8 + 0x14) & 0x4020);
              if (uVar1 >> 5 != 0) {
                uVar12 = gnt4_HSD_DObjResolveRefsAll_bl
                                   (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(int *)(iVar8 + 0x18),*(int *)(iVar7 + 0x10));
              }
            }
            if ((*(uint *)(iVar8 + 0x14) & 0x1000) == 0) {
              iVar6 = *(int *)(iVar8 + 0x10);
              for (iVar5 = *(int *)(iVar7 + 8); (iVar6 != 0 && (iVar5 != 0));
                  iVar5 = *(int *)(iVar5 + 0xc)) {
                uVar12 = gnt4_HSD_JObjResolveRefs
                                   (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    iVar6,iVar5,pcVar4,in_r6,in_r7,in_r8,in_r9,in_r10);
                if ((*(uint *)(iVar6 + 0x14) & 0x1000) == 0) {
                  uVar12 = gnt4_HSD_JObjResolveRefsAll
                                     (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     );
                }
                iVar6 = *(int *)(iVar6 + 8);
              }
            }
            iVar8 = *(int *)(iVar8 + 8);
          }
        }
        iVar11 = *(int *)(iVar11 + 8);
      }
    }
    uVar13 = CONCAT44(*(undefined4 *)(iVar9 + 8),*(undefined4 *)(iVar10 + 0xc));
  }
  gnt4__restgpr_23_bl();
  return;
}



// ==== 8024fca8  gnt4-HSD_JObjRef ====

void gnt4_HSD_JObjRef(undefined8 param_1,double param_2,double param_3,double param_4,double param_5
                     ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                     undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14
                     ,undefined4 param_15,undefined4 param_16)

{
  if ((param_9 != 0) &&
     (*(short *)(param_9 + 4) = *(short *)(param_9 + 4) + 1, *(short *)(param_9 + 4) == -1)) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_object_h_803acdf0,0x5d,s_HSD_OBJ_o__>ref_count____HSD_OBJ_803acdfc,param_12,
                     param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8024fcfc  gnt4-HSD_IDGetData ====

void gnt4_HSD_IDGetData(uint param_1,undefined4 *param_2)

{
  gnt4_HSD_IDGetDataFromTable_bl((undefined *)0x0,param_1,param_2);
  return;
}



// ==== 8024fd28  gnt4-ref_INC ====

void gnt4_ref_INC(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 4) = *(short *)(param_9 + 4) + 1;
  if (*(short *)(param_9 + 4) == -1) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_object_h_803acdf0,0x5d,s_HSD_OBJ_o__>ref_count____HSD_OBJ_803acdfc,param_12,
                     param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8024fd74  gnt4-HSD_JObjUnref ====

void gnt4_HSD_JObjUnref(undefined8 param_1,double param_2,double param_3,double param_4,
                       double param_5,double param_6,double param_7,double param_8,int *param_9,
                       undefined4 param_10,undefined4 param_11,undefined4 param_12,
                       undefined4 param_13,undefined4 param_14,undefined4 param_15,
                       undefined4 param_16)

{
  ushort uVar1;
  uint uVar2;
  
  if (param_9 != (int *)0x0) {
    uVar1 = *(ushort *)(param_9 + 1);
    uVar2 = countLeadingZeros(0xffff - (uint)uVar1);
    uVar2 = uVar2 >> 5;
    if (uVar2 == 0) {
      uVar2 = countLeadingZeros((uint)uVar1);
      *(ushort *)(param_9 + 1) = uVar1 - 1;
      uVar2 = uVar2 >> 5;
    }
    if (uVar2 != 0) {
      if ((int)(*(ushort *)((int)param_9 + 6) - 1) < 0) {
        if (param_9 != (int *)0x0) {
          (**(code **)(*param_9 + 0x30))(param_9);
          (**(code **)(*param_9 + 0x34))(param_9);
        }
      }
      else {
        *(ushort *)((int)param_9 + 6) = *(ushort *)((int)param_9 + 6) + 1;
        if (*(short *)((int)param_9 + 6) == 0) {
          gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_object_h_803acdf0,0x9e,s_HSD_OBJ_o__>ref_count_individual_803ace24,
                           param_12,param_13,param_14,param_15,param_16);
        }
        (**(code **)(*param_9 + 0x4c))(param_9);
        uVar2 = countLeadingZeros((uint)*(ushort *)((int)param_9 + 6));
        uVar2 = uVar2 >> 5;
        if (uVar2 == 0) {
          *(ushort *)((int)param_9 + 6) = *(ushort *)((int)param_9 + 6) - 1;
          uVar2 = countLeadingZeros((uint)*(ushort *)((int)param_9 + 6));
          uVar2 = uVar2 >> 5;
        }
        if ((uVar2 != 0) && (param_9 != (int *)0x0)) {
          (**(code **)(*param_9 + 0x30))(param_9);
          (**(code **)(*param_9 + 0x34))(param_9);
        }
      }
    }
  }
  return;
}



// ==== 8024febc  gnt4-HSD_JObjUnrefThis ====

void gnt4_HSD_JObjUnrefThis(int *param_1)

{
  uint uVar1;
  
  if (param_1 != (int *)0x0) {
    uVar1 = countLeadingZeros((uint)*(ushort *)((int)param_1 + 6));
    uVar1 = uVar1 >> 5;
    if (uVar1 == 0) {
      *(ushort *)((int)param_1 + 6) = *(ushort *)((int)param_1 + 6) - 1;
      uVar1 = countLeadingZeros((uint)*(ushort *)((int)param_1 + 6));
      uVar1 = uVar1 >> 5;
    }
    if (uVar1 != 0) {
      uVar1 = 0xffffffff;
      if (*(ushort *)(param_1 + 1) != 0xffff) {
        uVar1 = (uint)*(ushort *)(param_1 + 1);
      }
      if (((int)uVar1 < 0) && (param_1 != (int *)0x0)) {
        (**(code **)(*param_1 + 0x30))(param_1);
        (**(code **)(*param_1 + 0x34))(param_1);
      }
    }
  }
  return;
}



// ==== 8024ff64  gnt4-HSD_JObjAddChild ====

void gnt4_HSD_JObjAddChild
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10,char *param_11,
               undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  uint uVar1;
  int extraout_r4;
  int iVar2;
  undefined8 uVar3;
  
  if ((param_9 != 0) && (param_10 != 0)) {
    iVar2 = param_10;
    if (*(int *)(param_10 + 0xc) != 0) {
      uVar3 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_child_should_be_a_orphan__803ace60,param_10,param_11,param_12,
                               param_13,param_14,param_15,param_16);
      param_11 = s_child_>parent____NULL_803ace7c;
      param_1 = gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ef8,0x549,s_child_>parent____NULL_803ace7c,param_12,
                                 param_13,param_14,param_15,param_16);
      iVar2 = extraout_r4;
    }
    if (*(int *)(param_10 + 8) != 0) {
      uVar3 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_child_should_not_have_siblings_803ace94,iVar2,param_11,param_12,
                               param_13,param_14,param_15,param_16);
      param_1 = gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435ef8,0x54a,s_child_>next____NULL_803ace4c,param_12,
                                 param_13,param_14,param_15,param_16);
    }
    if (*(int *)(param_9 + 0x10) == 0) {
      *(int *)(param_9 + 0x10) = param_10;
    }
    else {
      if ((*(uint *)(param_9 + 0x14) & 0x1000) != 0) {
        param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_80435ef8,0x550,s___jobj_>flags___JOBJ_INSTANCE__803aceb4,
                                   param_12,param_13,param_14,param_15,param_16);
      }
      for (iVar2 = *(int *)(param_9 + 0x10); *(int *)(iVar2 + 8) != 0; iVar2 = *(int *)(iVar2 + 8))
      {
        if (iVar2 == param_10) {
          param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,&DAT_80435ef8,0x553,s_last____child_803aced4,param_12,param_13
                                     ,param_14,param_15,param_16);
        }
      }
      *(int *)(iVar2 + 8) = param_10;
    }
    *(int *)(param_10 + 0xc) = param_9;
    uVar1 = (*(uint *)(param_10 + 0x14) | *(uint *)(param_10 + 0x14) << 10) & 0x70000000;
    while ((param_9 != 0 && ((uVar1 & ~*(uint *)(param_9 + 0x14)) != 0))) {
      *(uint *)(param_9 + 0x14) = *(uint *)(param_9 + 0x14) | uVar1;
      param_9 = *(int *)(param_9 + 0xc);
    }
  }
  return;
}



// ==== 802500b0  zz_02500b0_ ====

void zz_02500b0_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  if ((param_9 != 0) && (param_10 != 0)) {
    iVar1 = *(int *)(param_10 + 0xc);
    uVar4 = *(undefined4 *)(param_10 + 8);
    if (iVar1 != 0) {
      if (*(int *)(iVar1 + 0x10) == param_10) {
        *(undefined4 *)(iVar1 + 0x10) = uVar4;
      }
      else {
        iVar1 = gnt4_HSD_JObjGetPrev
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                           param_10,param_11,param_12,param_13,param_14,param_15,param_16);
        if (iVar1 == 0) {
          gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80435ef8,0x572,&DAT_80435f04,param_12,param_13,param_14,param_15,
                           param_16);
        }
        *(undefined4 *)(iVar1 + 8) = uVar4;
      }
      for (iVar1 = *(int *)(param_10 + 0xc); iVar1 != 0; iVar1 = *(int *)(iVar1 + 8)) {
        uVar3 = 0x8fffffff;
        for (iVar2 = *(int *)(iVar1 + 0x10); iVar2 != 0; iVar2 = *(int *)(iVar2 + 8)) {
          uVar3 = uVar3 | (*(uint *)(iVar2 + 0x14) | *(uint *)(iVar2 + 0x14) << 10) & 0x70000000;
        }
        if ((*(uint *)(iVar1 + 0x14) & ~uVar3) == 0) break;
        *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & uVar3;
      }
      *(undefined4 *)(param_10 + 0xc) = 0;
    }
    *(undefined4 *)(param_10 + 8) = 0;
    *(undefined4 *)(param_10 + 0xc) = *(undefined4 *)(param_9 + 0xc);
    *(undefined4 *)(param_10 + 8) = *(undefined4 *)(param_9 + 8);
    *(int *)(param_9 + 8) = param_10;
    iVar1 = *(int *)(param_9 + 0xc);
    if (iVar1 != 0) {
      uVar3 = (*(uint *)(param_10 + 0x14) | *(uint *)(param_10 + 0x14) << 10) & 0x70000000;
      while ((iVar1 != 0 && ((uVar3 & ~*(uint *)(iVar1 + 0x14)) != 0))) {
        *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | uVar3;
        iVar1 = *(int *)(iVar1 + 0xc);
      }
    }
  }
  return;
}



// ==== 8025020c  gnt4-HSD_JObjGetPrev ====

int gnt4_HSD_JObjGetPrev
              (double param_1,double param_2,double param_3,double param_4,double param_5,
              double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
              undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
              undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  if ((param_9 == 0) || (*(int *)(param_9 + 0xc) == 0)) {
    iVar2 = 0;
  }
  else {
    iVar1 = *(int *)(*(int *)(param_9 + 0xc) + 0x10);
    if (param_9 == iVar1) {
      iVar2 = 0;
    }
    else {
      do {
        iVar2 = iVar1;
        if (iVar2 == 0) {
          gnt4_HSD_Panic_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            &DAT_80435ef8,0x5ef,s_can_not_find_specified_jobj__may_803acee4,param_12
                            ,param_13,param_14,param_15,param_16);
          return 0;
        }
        iVar1 = *(int *)(iVar2 + 8);
      } while (*(int *)(iVar2 + 8) != param_9);
    }
  }
  return iVar2;
}



// ==== 80250298  gnt4-HSD_JObjGetDObj ====

undefined4 gnt4_HSD_JObjGetDObj(int param_1)

{
  uint uVar1;
  
  if (param_1 != 0) {
    uVar1 = countLeadingZeros(*(uint *)(param_1 + 0x14) & 0x4020);
    if (uVar1 >> 5 != 0) {
      return *(undefined4 *)(param_1 + 0x18);
    }
  }
  return 0;
}



// ==== 802502c4  zz_02502c4_ ====

undefined4 zz_02502c4_(int param_1)

{
  if (param_1 != 0) {
    return *(undefined4 *)(param_1 + 0x14);
  }
  return 0;
}



// ==== 802502dc  gnt4-HSD_JObjSetFlags ====

/* WARNING: Removing unreachable block (ram,0x80250318) */

void gnt4_HSD_JObjSetFlags
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,uint param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  
  if (param_9 != 0) {
    if ((((*(uint *)(param_9 + 0x14) ^ param_10) & 8) != 0) && (param_9 != 0)) {
      uVar2 = *(uint *)(param_9 + 0x14);
      bVar1 = false;
      if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
        bVar1 = true;
      }
      if (!bVar1) {
        gnt4_HSD_JObjSetMtxDirtySub_bl
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar2,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      }
    }
    *(uint *)(param_9 + 0x14) = *(uint *)(param_9 + 0x14) | param_10;
  }
  return;
}



// ==== 80250378  gnt4-HSD_JObjSetFlagsAll ====

/* WARNING: Removing unreachable block (ram,0x802503b8) */
/* WARNING: Removing unreachable block (ram,0x8025043c) */
/* WARNING: Removing unreachable block (ram,0x802504c0) */

void gnt4_HSD_JObjSetFlagsAll
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint extraout_r4;
  uint extraout_r4_00;
  uint extraout_r4_01;
  uint extraout_r4_02;
  uint extraout_r4_03;
  uint extraout_r4_04;
  uint extraout_r4_05;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 extraout_f1;
  undefined8 uVar10;
  
  uVar10 = gnt4__savegpr_25_bl();
  iVar7 = (int)((ulonglong)uVar10 >> 0x20);
  uVar3 = (uint)uVar10;
  if (iVar7 != 0) {
    uVar4 = uVar3;
    uVar10 = extraout_f1;
    if ((((*(uint *)(iVar7 + 0x14) ^ uVar3) & 8) != 0) && (iVar7 != 0)) {
      uVar4 = *(uint *)(iVar7 + 0x14);
      bVar1 = false;
      if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
        bVar1 = true;
      }
      if (!bVar1) {
        uVar10 = gnt4_HSD_JObjSetMtxDirtySub_bl
                           (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            iVar7,uVar4,param_11,param_12,param_13,param_14,param_15,param_16);
        uVar4 = extraout_r4;
      }
    }
    *(uint *)(iVar7 + 0x14) = *(uint *)(iVar7 + 0x14) | uVar3;
    if ((*(uint *)(iVar7 + 0x14) & 0x1000) == 0) {
      for (iVar7 = *(int *)(iVar7 + 0x10); iVar7 != 0; iVar7 = *(int *)(iVar7 + 8)) {
        if (iVar7 != 0) {
          if ((((*(uint *)(iVar7 + 0x14) ^ uVar3) & 8) != 0) && (iVar7 != 0)) {
            uVar4 = *(uint *)(iVar7 + 0x14);
            bVar1 = false;
            if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
              bVar1 = true;
            }
            if (!bVar1) {
              uVar10 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                 (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  iVar7,uVar4,param_11,param_12,param_13,param_14,param_15,param_16)
              ;
              uVar4 = extraout_r4_00;
            }
          }
          *(uint *)(iVar7 + 0x14) = *(uint *)(iVar7 + 0x14) | uVar3;
          if ((*(uint *)(iVar7 + 0x14) & 0x1000) == 0) {
            for (iVar9 = *(int *)(iVar7 + 0x10); iVar9 != 0; iVar9 = *(int *)(iVar9 + 8)) {
              if (iVar9 != 0) {
                if ((((*(uint *)(iVar9 + 0x14) ^ uVar3) & 8) != 0) && (iVar9 != 0)) {
                  uVar4 = *(uint *)(iVar9 + 0x14);
                  bVar1 = false;
                  if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
                    bVar1 = true;
                  }
                  if (!bVar1) {
                    uVar10 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,iVar9,uVar4,param_11,param_12,param_13,param_14,
                                        param_15,param_16);
                    uVar4 = extraout_r4_01;
                  }
                }
                *(uint *)(iVar9 + 0x14) = *(uint *)(iVar9 + 0x14) | uVar3;
                if ((*(uint *)(iVar9 + 0x14) & 0x1000) == 0) {
                  for (iVar8 = *(int *)(iVar9 + 0x10); iVar8 != 0; iVar8 = *(int *)(iVar8 + 8)) {
                    if (iVar8 != 0) {
                      if (((((*(uint *)(iVar8 + 0x14) ^ uVar3) & 8) != 0) && (iVar8 != 0)) &&
                         (iVar2 = gnt4_HSD_JObjMtxIsDirty
                                            (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                             param_8,iVar8,uVar4,param_11,param_12,param_13,param_14
                                             ,param_15,param_16), iVar2 == 0)) {
                        uVar10 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                           (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,iVar8,uVar4,param_11,param_12,param_13,param_14,
                                            param_15,param_16);
                        uVar4 = extraout_r4_02;
                      }
                      *(uint *)(iVar8 + 0x14) = *(uint *)(iVar8 + 0x14) | uVar3;
                      if ((*(uint *)(iVar8 + 0x14) & 0x1000) == 0) {
                        for (iVar2 = *(int *)(iVar8 + 0x10); iVar2 != 0; iVar2 = *(int *)(iVar2 + 8)
                            ) {
                          if (iVar2 != 0) {
                            if (((*(uint *)(iVar2 + 0x14) ^ uVar3) & 8) != 0) {
                              uVar10 = gnt4_HSD_JObjSetMtxDirty
                                                 (uVar10,param_2,param_3,param_4,param_5,param_6,
                                                  param_7,param_8,iVar2,uVar4,param_11,param_12,
                                                  param_13,param_14,param_15,param_16);
                              uVar4 = extraout_r4_03;
                            }
                            *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | uVar3;
                            if ((*(uint *)(iVar2 + 0x14) & 0x1000) == 0) {
                              for (iVar6 = *(int *)(iVar2 + 0x10); iVar6 != 0;
                                  iVar6 = *(int *)(iVar6 + 8)) {
                                if ((iVar6 != 0) &&
                                   (uVar10 = gnt4_HSD_JObjSetFlags
                                                       (uVar10,param_2,param_3,param_4,param_5,
                                                        param_6,param_7,param_8,iVar6,uVar3,param_11
                                                        ,param_12,param_13,param_14,param_15,
                                                        param_16), uVar4 = extraout_r4_04,
                                   (*(uint *)(iVar6 + 0x14) & 0x1000) == 0)) {
                                  for (iVar5 = *(int *)(iVar6 + 0x10); iVar5 != 0;
                                      iVar5 = *(int *)(iVar5 + 8)) {
                                    uVar10 = gnt4_HSD_JObjSetFlagsAll
                                                       (uVar10,param_2,param_3,param_4,param_5,
                                                        param_6,param_7,param_8,iVar5,uVar3,param_11
                                                        ,param_12,param_13,param_14,param_15,
                                                        param_16);
                                    uVar4 = extraout_r4_05;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  gnt4__restgpr_25_bl();
  return;
}



// ==== 80250650  gnt4-HSD_JObjClearFlags ====

/* WARNING: Removing unreachable block (ram,0x8025068c) */

void gnt4_HSD_JObjClearFlags
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,uint param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  
  if (param_9 != 0) {
    if ((((*(uint *)(param_9 + 0x14) ^ param_10) & 8) != 0) && (param_9 != 0)) {
      uVar2 = *(uint *)(param_9 + 0x14);
      bVar1 = false;
      if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
        bVar1 = true;
      }
      if (!bVar1) {
        gnt4_HSD_JObjSetMtxDirtySub_bl
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar2,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      }
    }
    *(uint *)(param_9 + 0x14) = *(uint *)(param_9 + 0x14) & ~param_10;
  }
  return;
}



// ==== 802506ec  gnt4-HSD_JObjClearFlagsAll ====

/* WARNING: Removing unreachable block (ram,0x8025072c) */
/* WARNING: Removing unreachable block (ram,0x802507b4) */
/* WARNING: Removing unreachable block (ram,0x80250838) */

void gnt4_HSD_JObjClearFlagsAll
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint extraout_r4;
  uint extraout_r4_00;
  uint extraout_r4_01;
  uint extraout_r4_02;
  uint extraout_r4_03;
  uint extraout_r4_04;
  uint extraout_r4_05;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined8 extraout_f1;
  undefined8 uVar11;
  
  uVar11 = gnt4__savegpr_24_bl();
  iVar7 = (int)((ulonglong)uVar11 >> 0x20);
  uVar3 = (uint)uVar11;
  if (iVar7 != 0) {
    uVar4 = uVar3;
    uVar11 = extraout_f1;
    if ((((*(uint *)(iVar7 + 0x14) ^ uVar3) & 8) != 0) && (iVar7 != 0)) {
      uVar4 = *(uint *)(iVar7 + 0x14);
      bVar1 = false;
      if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
        bVar1 = true;
      }
      if (!bVar1) {
        uVar11 = gnt4_HSD_JObjSetMtxDirtySub_bl
                           (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            iVar7,uVar4,param_11,param_12,param_13,param_14,param_15,param_16);
        uVar4 = extraout_r4;
      }
    }
    *(uint *)(iVar7 + 0x14) = *(uint *)(iVar7 + 0x14) & ~uVar3;
    if ((*(uint *)(iVar7 + 0x14) & 0x1000) == 0) {
      uVar8 = ~uVar3;
      for (iVar7 = *(int *)(iVar7 + 0x10); iVar7 != 0; iVar7 = *(int *)(iVar7 + 8)) {
        if (iVar7 != 0) {
          if ((((*(uint *)(iVar7 + 0x14) ^ uVar3) & 8) != 0) && (iVar7 != 0)) {
            uVar4 = *(uint *)(iVar7 + 0x14);
            bVar1 = false;
            if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
              bVar1 = true;
            }
            if (!bVar1) {
              uVar11 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                 (uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  iVar7,uVar4,param_11,param_12,param_13,param_14,param_15,param_16)
              ;
              uVar4 = extraout_r4_00;
            }
          }
          *(uint *)(iVar7 + 0x14) = *(uint *)(iVar7 + 0x14) & uVar8;
          if ((*(uint *)(iVar7 + 0x14) & 0x1000) == 0) {
            for (iVar10 = *(int *)(iVar7 + 0x10); iVar10 != 0; iVar10 = *(int *)(iVar10 + 8)) {
              if (iVar10 != 0) {
                if ((((*(uint *)(iVar10 + 0x14) ^ uVar3) & 8) != 0) && (iVar10 != 0)) {
                  uVar4 = *(uint *)(iVar10 + 0x14);
                  bVar1 = false;
                  if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
                    bVar1 = true;
                  }
                  if (!bVar1) {
                    uVar11 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                       (uVar11,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,iVar10,uVar4,param_11,param_12,param_13,param_14,
                                        param_15,param_16);
                    uVar4 = extraout_r4_01;
                  }
                }
                *(uint *)(iVar10 + 0x14) = *(uint *)(iVar10 + 0x14) & uVar8;
                if ((*(uint *)(iVar10 + 0x14) & 0x1000) == 0) {
                  for (iVar9 = *(int *)(iVar10 + 0x10); iVar9 != 0; iVar9 = *(int *)(iVar9 + 8)) {
                    if (iVar9 != 0) {
                      if (((((*(uint *)(iVar9 + 0x14) ^ uVar3) & 8) != 0) && (iVar9 != 0)) &&
                         (iVar2 = gnt4_HSD_JObjMtxIsDirty
                                            (uVar11,param_2,param_3,param_4,param_5,param_6,param_7,
                                             param_8,iVar9,uVar4,param_11,param_12,param_13,param_14
                                             ,param_15,param_16), iVar2 == 0)) {
                        uVar11 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                           (uVar11,param_2,param_3,param_4,param_5,param_6,param_7,
                                            param_8,iVar9,uVar4,param_11,param_12,param_13,param_14,
                                            param_15,param_16);
                        uVar4 = extraout_r4_02;
                      }
                      *(uint *)(iVar9 + 0x14) = *(uint *)(iVar9 + 0x14) & uVar8;
                      if ((*(uint *)(iVar9 + 0x14) & 0x1000) == 0) {
                        for (iVar2 = *(int *)(iVar9 + 0x10); iVar2 != 0; iVar2 = *(int *)(iVar2 + 8)
                            ) {
                          if (iVar2 != 0) {
                            if (((*(uint *)(iVar2 + 0x14) ^ uVar3) & 8) != 0) {
                              uVar11 = gnt4_HSD_JObjSetMtxDirty
                                                 (uVar11,param_2,param_3,param_4,param_5,param_6,
                                                  param_7,param_8,iVar2,uVar4,param_11,param_12,
                                                  param_13,param_14,param_15,param_16);
                              uVar4 = extraout_r4_03;
                            }
                            *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) & uVar8;
                            if ((*(uint *)(iVar2 + 0x14) & 0x1000) == 0) {
                              for (iVar6 = *(int *)(iVar2 + 0x10); iVar6 != 0;
                                  iVar6 = *(int *)(iVar6 + 8)) {
                                if ((iVar6 != 0) &&
                                   (uVar11 = gnt4_HSD_JObjClearFlags
                                                       (uVar11,param_2,param_3,param_4,param_5,
                                                        param_6,param_7,param_8,iVar6,uVar3,param_11
                                                        ,param_12,param_13,param_14,param_15,
                                                        param_16), uVar4 = extraout_r4_04,
                                   (*(uint *)(iVar6 + 0x14) & 0x1000) == 0)) {
                                  for (iVar5 = *(int *)(iVar6 + 0x10); iVar5 != 0;
                                      iVar5 = *(int *)(iVar5 + 8)) {
                                    uVar11 = gnt4_HSD_JObjClearFlagsAll
                                                       (uVar11,param_2,param_3,param_4,param_5,
                                                        param_6,param_7,param_8,iVar5,uVar3,param_11
                                                        ,param_12,param_13,param_14,param_15,
                                                        param_16);
                                    uVar4 = extraout_r4_05;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  gnt4__restgpr_24_bl();
  return;
}



// ==== 802509c8  gnt4-HSD_JObjAlloc ====

int * gnt4_HSD_JObjAlloc(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8)

{
  int *piVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined **ppuVar2;
  
  ppuVar2 = DAT_80436980;
  if (DAT_80436980 == (undefined **)0x0) {
    ppuVar2 = &PTR_gnt4_JObjInfoInit_bl_803acc10;
  }
  piVar1 = gnt4_hsdNew_bl(ppuVar2);
  if (piVar1 == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ef8,
                     0x7d6,&DAT_80435ef0,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  return piVar1;
}



// ==== 80250a24  gnt4-HSD_JObjSetCurrent ====

void gnt4_HSD_JObjSetCurrent
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  ushort uVar1;
  int *piVar2;
  uint uVar3;
  
  if ((param_9 != 0) &&
     (*(short *)(param_9 + 4) = *(short *)(param_9 + 4) + 1, *(short *)(param_9 + 4) == -1)) {
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_object_h_803acdf0,0x5d,s_HSD_OBJ_o__>ref_count____HSD_OBJ_803acdfc,
                               param_12,param_13,param_14,param_15,param_16);
  }
  piVar2 = DAT_80436994;
  if (DAT_80436994 != (int *)0x0) {
    uVar1 = *(ushort *)(DAT_80436994 + 1);
    uVar3 = countLeadingZeros(0xffff - (uint)uVar1);
    uVar3 = uVar3 >> 5;
    if (uVar3 == 0) {
      uVar3 = countLeadingZeros((uint)uVar1);
      *(ushort *)(DAT_80436994 + 1) = uVar1 - 1;
      uVar3 = uVar3 >> 5;
    }
    if (uVar3 != 0) {
      if ((int)(*(ushort *)((int)piVar2 + 6) - 1) < 0) {
        if (piVar2 != (int *)0x0) {
          (**(code **)(*piVar2 + 0x30))(piVar2);
          (**(code **)(*piVar2 + 0x34))(piVar2);
        }
      }
      else {
        *(ushort *)((int)piVar2 + 6) = *(ushort *)((int)piVar2 + 6) + 1;
        if (*(short *)((int)piVar2 + 6) == 0) {
          gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_object_h_803acdf0,0x9e,s_HSD_OBJ_o__>ref_count_individual_803ace24,
                           param_12,param_13,param_14,param_15,param_16);
        }
        (**(code **)(*piVar2 + 0x4c))(piVar2);
        uVar3 = countLeadingZeros((uint)*(ushort *)((int)piVar2 + 6));
        uVar3 = uVar3 >> 5;
        if (uVar3 == 0) {
          *(ushort *)((int)piVar2 + 6) = *(ushort *)((int)piVar2 + 6) - 1;
          uVar3 = countLeadingZeros((uint)*(ushort *)((int)piVar2 + 6));
          uVar3 = uVar3 >> 5;
        }
        if ((uVar3 != 0) && (piVar2 != (int *)0x0)) {
          (**(code **)(*piVar2 + 0x30))(piVar2);
          (**(code **)(*piVar2 + 0x34))(piVar2);
        }
      }
    }
  }
  DAT_80436994 = (int *)param_9;
  return;
}



// ==== 80250bb4  gnt4-HSD_JObjGetCurrent ====

undefined4 gnt4_HSD_JObjGetCurrent(void)

{
  return DAT_80436994;
}



// ==== 80250bbc  gnt4-resolveIKJoint1-bl ====

/* WARNING: Removing unreachable block (ram,0x80251384) */
/* WARNING: Removing unreachable block (ram,0x8025137c) */
/* WARNING: Removing unreachable block (ram,0x80251374) */
/* WARNING: Removing unreachable block (ram,0x8025136c) */
/* WARNING: Removing unreachable block (ram,0x80251364) */
/* WARNING: Removing unreachable block (ram,0x8025135c) */
/* WARNING: Removing unreachable block (ram,0x80250bf4) */
/* WARNING: Removing unreachable block (ram,0x80250bec) */
/* WARNING: Removing unreachable block (ram,0x80250be4) */
/* WARNING: Removing unreachable block (ram,0x80250bdc) */
/* WARNING: Removing unreachable block (ram,0x80250bd4) */
/* WARNING: Removing unreachable block (ram,0x80250bcc) */

void gnt4_resolveIKJoint1_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  bool bVar2;
  undefined4 *puVar3;
  float *pfVar4;
  uint uVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double in_f27;
  double in_f28;
  double dVar10;
  double dVar11;
  float local_114;
  int local_110;
  int local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  float afStack_f0 [3];
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  int local_bc;
  int local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float afStack_a8 [14];
  
  dVar10 = (double)FLOAT_8043d2f8;
  uVar5 = 0;
  local_b4 = DAT_802b5218;
  iVar6 = param_9[4];
  local_b0 = DAT_802b521c;
  local_ac = DAT_802b5220;
  for (; iVar6 != 0; iVar6 = *(int *)(iVar6 + 8)) {
    if ((*(uint *)(iVar6 + 0x14) & 0x600000) == 0x400000) goto LAB_80250c64;
  }
  iVar6 = 0;
LAB_80250c64:
  local_c0 = DAT_802b5224;
  local_bc = DAT_802b5228;
  local_b8 = DAT_802b522c;
  pfVar4 = (float *)param_9[0x1d];
  if (pfVar4 != (float *)0x0) {
    local_b4 = *pfVar4;
    local_b0 = pfVar4[1];
    local_ac = pfVar4[2];
  }
  puVar3 = gnt4_HSD_RObjGetByType_bl((undefined4 *)param_9[0x20],0x40000000,0);
  if (puVar3 == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ef8,
                     0x853,&DAT_80435f10,param_12,param_13,param_14,param_15,param_16);
  }
  dVar7 = (double)(float)puVar3[2];
  dVar9 = (double)(float)puVar3[3];
  dVar11 = (double)(float)(dVar7 * (double)local_b4);
  if (iVar6 == 0) {
    for (iVar6 = param_9[4]; iVar6 != 0; iVar6 = *(int *)(iVar6 + 8)) {
      if ((*(uint *)(iVar6 + 0x14) & 0x600000) == 0x600000) goto LAB_80250dc8;
    }
    iVar6 = 0;
LAB_80250dc8:
    if (iVar6 == 0) {
      dVar7 = (double)gnt4___assert_bl(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                       ,&DAT_80435ef8,0x824,&DAT_80435f0c,param_12,param_13,param_14
                                       ,param_15,param_16);
    }
    puVar3 = gnt4_HSD_RObjGetByType_bl(*(undefined4 **)(iVar6 + 0x80),0x10000000,1);
    if (puVar3 == (undefined4 *)0x0) {
      iVar6 = 0;
    }
  }
  else {
    puVar3 = gnt4_HSD_RObjGetByType_bl(*(undefined4 **)(iVar6 + 0x80),0x40000000,0);
    if (puVar3 == (undefined4 *)0x0) {
      gnt4___assert_bl(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ef8,
                       0x85e,&DAT_80435f10,param_12,param_13,param_14,param_15,param_16);
    }
    dVar7 = (double)local_b4;
    uVar5 = (uint)puVar3[1] >> 2 & 1;
    dVar10 = (double)(float)(dVar7 * (double)((float)puVar3[2] * *(float *)(iVar6 + 0x2c)));
    for (iVar6 = *(int *)(iVar6 + 0x10); iVar6 != 0; iVar6 = *(int *)(iVar6 + 8)) {
      if ((*(uint *)(iVar6 + 0x14) & 0x600000) == 0x600000) goto LAB_80250d5c;
    }
    iVar6 = 0;
LAB_80250d5c:
    if (iVar6 == 0) {
      dVar7 = (double)gnt4___assert_bl(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                       ,&DAT_80435ef8,0x824,&DAT_80435f0c,param_12,param_13,param_14
                                       ,param_15,param_16);
    }
    puVar3 = gnt4_HSD_RObjGetByType_bl(*(undefined4 **)(iVar6 + 0x80),0x10000000,1);
    if (puVar3 == (undefined4 *)0x0) {
      iVar6 = 0;
    }
  }
  if (iVar6 != 0) {
    puVar3 = gnt4_HSD_RObjGetByType_bl((undefined4 *)param_9[0x20],0x10000000,3);
    if (((puVar3 == (undefined4 *)0x0) && (param_9 != (int *)0x0)) && (param_9[0x20] != 0)) {
      dVar7 = (double)gnt4_HSD_RObjUpdateAll_bl
                                (dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 param_9[0x20],param_9,*(undefined **)(*param_9 + 0x50),param_12,
                                 param_13,param_14,param_15,param_16);
      if (param_9 == (int *)0x0) {
        dVar7 = (double)gnt4___assert_bl(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,
                                         param_8,&DAT_80435ee8,0x25d,&DAT_80435ef0,param_12,param_13
                                         ,param_14,param_15,param_16);
      }
      bVar2 = false;
      if (((param_9[5] & 0x800000U) == 0) && ((param_9[5] & 0x40U) != 0)) {
        bVar2 = true;
      }
      if (bVar2) {
        dVar7 = (double)(**(code **)(*param_9 + 0x40))(param_9);
        param_9[5] = param_9[5] & 0xffffffbf;
      }
    }
    if (param_9[3] != 0) {
      dVar7 = (double)gnt4_HSD_MtxGetTranslate_bl(param_9[3] + 0x44,&local_c0);
    }
    gnt4_HSD_RObjGetGlobalPosition_bl
              (dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(undefined4 *)(iVar6 + 0x80),1,(float *)(iVar6 + 0x38),param_12,param_13,param_14,
               param_15,param_16);
    gnt4_PSVECSubtract_bl((float *)(iVar6 + 0x38),&local_c0,&local_d8);
    dVar7 = gnt4_PSQUATDotProduct_bl(&local_d8,&local_d8);
    fVar1 = FLOAT_8043d2f8;
    if ((double)FLOAT_8043d320 < dVar7) {
      local_fc = local_d8;
      local_f8 = local_d4;
      local_f4 = local_d0;
      iVar6 = gnt4_HSD_RObjGetGlobalPosition_bl
                        (dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9[0x20]
                         ,3,&local_108,local_d8,param_13,param_14,param_15,param_16);
      if (iVar6 == 0) {
        local_114 = (float)param_9[0x13];
        local_110 = param_9[0x17];
        local_10c = param_9[0x1b];
        gnt4_PSVECCrossProduct_bl(&local_114,&local_fc,&local_108);
        gnt4_PSVECCrossProduct_bl(&local_fc,&local_108,&local_114);
      }
      else {
        gnt4_PSVECSubtract_bl(&local_108,&local_c0,&local_108);
        if ((double)FLOAT_8043d2f8 != dVar9) {
          gnt4_PSMTXRotAxisRad_bl(dVar9,afStack_a8,&local_fc);
          gnt4_PSMTXMultVec_bl(afStack_a8,&local_108,&local_108);
        }
        gnt4_PSVECCrossProduct_bl(&local_fc,&local_108,&local_114);
        gnt4_PSVECCrossProduct_bl(&local_114,&local_fc,&local_108);
      }
      dVar9 = gnt4_PSQUATDotProduct_bl(&local_114,&local_114);
      dVar9 = (double)(FLOAT_8043d308 / (float)((double)FLOAT_8043d324 + dVar9));
      if ((double)FLOAT_8043d2f8 < dVar9) {
        dVar8 = 1.0 / SQRT(dVar9);
        dVar8 = DOUBLE_8043d310 * dVar8 * -(dVar9 * dVar8 * dVar8 - DOUBLE_8043d328);
        dVar8 = DOUBLE_8043d310 * dVar8 * -(dVar9 * dVar8 * dVar8 - DOUBLE_8043d328);
        dVar9 = (double)(float)(dVar9 * DOUBLE_8043d310 * dVar8 *
                                        -(dVar9 * dVar8 * dVar8 - DOUBLE_8043d328));
      }
      gnt4_PSQUATScale_bl(dVar9,&local_114,&local_e4);
      dVar9 = gnt4_PSQUATDotProduct_bl(&local_108,&local_108);
      dVar9 = (double)(FLOAT_8043d308 / (float)((double)FLOAT_8043d324 + dVar9));
      if ((double)FLOAT_8043d2f8 < dVar9) {
        dVar8 = 1.0 / SQRT(dVar9);
        dVar8 = DOUBLE_8043d310 * dVar8 * -(dVar9 * dVar8 * dVar8 - DOUBLE_8043d328);
        dVar8 = DOUBLE_8043d310 * dVar8 * -(dVar9 * dVar8 * dVar8 - DOUBLE_8043d328);
        dVar9 = (double)(float)(dVar9 * DOUBLE_8043d310 * dVar8 *
                                        -(dVar9 * dVar8 * dVar8 - DOUBLE_8043d328));
      }
      gnt4_PSQUATScale_bl(dVar9,&local_108,afStack_f0);
      dVar9 = (double)(float)(dVar11 * dVar11);
      in_f28 = (double)(float)(dVar10 * dVar10);
      in_f27 = (double)(FLOAT_8043d330 *
                       ((float)((double)FLOAT_8043d334 * (double)(float)(dVar9 + in_f28) - dVar7) -
                       (float)((double)((float)(dVar9 - in_f28) * (float)(dVar9 - in_f28)) / dVar7))
                       );
      if (in_f27 < (double)FLOAT_8043d2f8) {
        in_f27 = (double)FLOAT_8043d2f8;
      }
      dVar9 = (double)(float)((double)(float)(dVar9 - in_f27) / dVar7);
      dVar10 = (double)(FLOAT_8043d308 / (float)((double)FLOAT_8043d324 + dVar9));
      if ((double)FLOAT_8043d2f8 < dVar10) {
        dVar11 = 1.0 / SQRT(dVar10);
        dVar11 = DOUBLE_8043d310 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_8043d328);
        dVar11 = DOUBLE_8043d310 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_8043d328);
        dVar10 = (double)(float)(dVar10 * DOUBLE_8043d310 * dVar11 *
                                          -(dVar10 * dVar11 * dVar11 - DOUBLE_8043d328));
      }
      dVar11 = (double)(FLOAT_8043d308 / (float)((double)FLOAT_8043d324 + in_f27));
      if ((double)FLOAT_8043d2f8 < dVar11) {
        dVar8 = 1.0 / SQRT(dVar11);
        dVar8 = DOUBLE_8043d310 * dVar8 * -(dVar11 * dVar8 * dVar8 - DOUBLE_8043d328);
        dVar8 = DOUBLE_8043d310 * dVar8 * -(dVar11 * dVar8 * dVar8 - DOUBLE_8043d328);
        dVar11 = (double)(float)(dVar11 * DOUBLE_8043d310 * dVar8 *
                                          -(dVar11 * dVar8 * dVar8 - DOUBLE_8043d328));
      }
      dVar11 = (double)(float)(in_f27 * dVar11);
      fVar1 = (float)(dVar9 * dVar10);
    }
    if (uVar5 != 0) {
      dVar11 = -dVar11;
    }
    if (dVar7 <= (double)(float)(in_f28 - in_f27)) {
      gnt4_PSQUATScale_bl(-(double)fVar1,&local_d8,&local_cc);
    }
    else {
      gnt4_PSQUATScale_bl((double)fVar1,&local_d8,&local_cc);
    }
    gnt4_PSQUATScale_bl(dVar11,afStack_f0,&local_108);
    gnt4_PSVECAdd_bl(&local_cc,&local_108,&local_cc);
    dVar10 = gnt4_PSQUATDotProduct_bl(&local_cc,&local_cc);
    dVar10 = (double)(FLOAT_8043d308 / (float)((double)FLOAT_8043d324 + dVar10));
    if ((double)FLOAT_8043d2f8 < dVar10) {
      dVar7 = 1.0 / SQRT(dVar10);
      dVar7 = DOUBLE_8043d310 * dVar7 * -(dVar10 * dVar7 * dVar7 - DOUBLE_8043d328);
      dVar7 = DOUBLE_8043d310 * dVar7 * -(dVar10 * dVar7 * dVar7 - DOUBLE_8043d328);
      dVar10 = (double)(float)(dVar10 * DOUBLE_8043d310 * dVar7 *
                                        -(dVar10 * dVar7 * dVar7 - DOUBLE_8043d328));
    }
    gnt4_PSQUATScale_bl(dVar10,&local_cc,&local_cc);
    param_9[0x11] = (int)(local_cc * local_b4);
    param_9[0x15] = (int)(local_c8 * local_b4);
    param_9[0x19] = (int)(local_c4 * local_b4);
    gnt4_PSVECCrossProduct_bl(&local_e4,&local_cc,&local_108);
    param_9[0x12] = (int)(local_108 * local_b0);
    param_9[0x16] = (int)(local_104 * local_b0);
    param_9[0x1a] = (int)(local_100 * local_b0);
    param_9[0x13] = (int)(local_e4 * local_ac);
    param_9[0x17] = (int)(local_e0 * local_ac);
    param_9[0x1b] = (int)(local_dc * local_ac);
    param_9[0x14] = (int)local_c0;
    param_9[0x18] = local_bc;
    param_9[0x1c] = local_b8;
  }
  return;
}



// ==== 802513ac  gnt4-resolveIKJoint2-bl ====

/* WARNING: Removing unreachable block (ram,0x802518e8) */
/* WARNING: Removing unreachable block (ram,0x802513bc) */

void gnt4_resolveIKJoint2_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  float *pfVar7;
  int iVar8;
  undefined4 in_r6;
  int iVar9;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar10;
  undefined8 extraout_f1;
  double dVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double in_f31;
  double dVar15;
  double in_ps31_1;
  float local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  float local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
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
  undefined4 local_7c;
  undefined4 local_78;
  float local_74;
  undefined4 local_70;
  undefined4 local_6c;
  float local_68;
  float local_64;
  float local_60;
  float afStack_5c [21];
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  iVar3 = gnt4__savegpr_27_bl();
  dVar15 = (double)FLOAT_8043d308;
  local_68 = DAT_802b5230;
  iVar10 = *(int *)(iVar3 + 0x10);
  local_64 = DAT_802b5234;
  local_60 = DAT_802b5238;
  for (; iVar10 != 0; iVar10 = *(int *)(iVar10 + 8)) {
    if ((*(uint *)(iVar10 + 0x14) & 0x600000) == 0x600000) goto LAB_80251420;
  }
  iVar10 = 0;
LAB_80251420:
  if (iVar10 == 0) {
    gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     &DAT_80435ef8,0x824,&DAT_80435f0c,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  puVar4 = gnt4_HSD_RObjGetByType_bl(*(undefined4 **)(iVar10 + 0x80),0x10000000,1);
  if (puVar4 == (undefined4 *)0x0) {
    iVar10 = 0;
  }
  if ((iVar10 != 0) && (iVar9 = *(int *)(iVar3 + 0xc), iVar9 != 0)) {
    pfVar7 = *(float **)(iVar3 + 0x74);
    if (pfVar7 != (float *)0x0) {
      local_68 = *pfVar7;
      local_64 = pfVar7[1];
      local_60 = pfVar7[2];
    }
    local_80 = *(float *)(iVar9 + 0x50);
    local_7c = *(undefined4 *)(iVar9 + 0x60);
    local_78 = *(undefined4 *)(iVar9 + 0x70);
    iVar8 = *(int *)(iVar3 + 0xc);
    local_8c = *(float *)(iVar8 + 0x44);
    local_88 = *(float *)(iVar8 + 0x54);
    local_84 = *(float *)(iVar8 + 100);
    dVar11 = gnt4_PSQUATDotProduct_bl(&local_8c,&local_8c);
    dVar13 = (double)FLOAT_8043d308;
    dVar11 = (double)(float)(dVar13 / (double)(float)((double)FLOAT_8043d324 + dVar11));
    if ((double)FLOAT_8043d2f8 < dVar11) {
      dVar13 = 1.0 / SQRT(dVar11);
      dVar13 = DOUBLE_8043d310 * dVar13 * -(dVar11 * dVar13 * dVar13 - DOUBLE_8043d328);
      dVar14 = DOUBLE_8043d310 * dVar13 * -(dVar11 * dVar13 * dVar13 - DOUBLE_8043d328);
      dVar13 = DOUBLE_8043d310 * dVar14;
      dVar11 = (double)(float)(dVar11 * dVar13 * -(dVar11 * dVar14 * dVar14 - DOUBLE_8043d328));
      param_3 = DOUBLE_8043d328;
      param_4 = DOUBLE_8043d310;
    }
    uVar12 = gnt4_PSQUATScale_bl(dVar11,&local_8c,&local_8c);
    pfVar7 = *(float **)(*(int *)(iVar3 + 0xc) + 0x74);
    if (pfVar7 != (float *)0x0) {
      dVar15 = (double)*pfVar7;
    }
    puVar4 = gnt4_HSD_RObjGetByType_bl(*(undefined4 **)(*(int *)(iVar3 + 0xc) + 0x80),0x40000000,0);
    if (puVar4 == (undefined4 *)0x0) {
      gnt4___assert_bl(uVar12,dVar13,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ef8,
                       0x8fc,&DAT_80435f10,iVar9,in_r7,in_r8,in_r9,in_r10);
    }
    gnt4_PSQUATScale_bl((double)(float)((double)(float)puVar4[2] * dVar15),&local_8c,&local_8c);
    gnt4_PSVECAdd_bl(&local_80,&local_8c,&local_74);
    gnt4_PSVECSubtract_bl((float *)(iVar10 + 0x38),&local_74,&local_8c);
    dVar15 = gnt4_PSQUATDotProduct_bl(&local_8c,&local_8c);
    dVar11 = (double)FLOAT_8043d308;
    dVar15 = (double)(float)(dVar11 / (double)(float)((double)FLOAT_8043d324 + dVar15));
    if ((double)FLOAT_8043d2f8 < dVar15) {
      dVar11 = 1.0 / SQRT(dVar15);
      dVar11 = DOUBLE_8043d310 * dVar11 * -(dVar15 * dVar11 * dVar11 - DOUBLE_8043d328);
      dVar13 = DOUBLE_8043d310 * dVar11 * -(dVar15 * dVar11 * dVar11 - DOUBLE_8043d328);
      dVar11 = DOUBLE_8043d310 * dVar13;
      dVar15 = (double)(float)(dVar15 * dVar11 * -(dVar15 * dVar13 * dVar13 - DOUBLE_8043d328));
      param_3 = DOUBLE_8043d328;
      param_4 = DOUBLE_8043d310;
    }
    uVar12 = gnt4_PSQUATScale_bl(dVar15,&local_8c,&local_8c);
    puVar4 = gnt4_HSD_RObjGetByType_bl(*(undefined4 **)(iVar3 + 0x80),0x20000000,5);
    puVar5 = gnt4_HSD_RObjGetByType_bl(*(undefined4 **)(iVar3 + 0x80),0x20000000,6);
    if ((puVar4 != (undefined4 *)0x0) || (puVar5 != (undefined4 *)0x0)) {
      bVar1 = false;
      puVar6 = gnt4_HSD_RObjGetByType_bl(*(undefined4 **)(iVar3 + 0x80),0x40000000,0);
      if (puVar6 == (undefined4 *)0x0) {
        gnt4___assert_bl(uVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ef8
                         ,0x91e,&DAT_80435f10,iVar9,in_r7,in_r8,in_r9,in_r10);
      }
      iVar10 = *(int *)(iVar3 + 0xc);
      uVar2 = puVar6[1];
      local_b0 = *(float *)(iVar10 + 0x44);
      local_ac = *(undefined4 *)(iVar10 + 0x54);
      local_a8 = *(undefined4 *)(iVar10 + 100);
      gnt4_PSVECNormalize_bl(&local_b0,&local_b0);
      dVar15 = gnt4_PSQUATDotProduct_bl(&local_b0,&local_8c);
      if (dVar15 < (double)FLOAT_8043d308) {
        if ((double)FLOAT_8043d338 < dVar15) {
          dVar15 = (double)gnt4_acos_bl(dVar15);
          dVar15 = (double)(float)dVar15;
        }
        else {
          dVar15 = (double)FLOAT_8043d33c;
        }
      }
      else {
        dVar15 = (double)FLOAT_8043d2f8;
      }
      if ((uVar2 >> 2 & 1) == 0) {
        dVar15 = -dVar15;
      }
      if ((puVar4 == (undefined4 *)0x0) || ((double)(float)puVar4[2] <= dVar15)) {
        if ((puVar5 != (undefined4 *)0x0) && ((double)(float)puVar5[2] < dVar15)) {
          bVar1 = true;
          dVar15 = (double)(float)puVar5[2];
        }
      }
      else {
        bVar1 = true;
        dVar15 = (double)(float)puVar4[2];
      }
      if (bVar1) {
        iVar10 = *(int *)(iVar3 + 0xc);
        local_bc = *(float *)(iVar10 + 0x4c);
        local_b8 = *(undefined4 *)(iVar10 + 0x5c);
        local_b4 = *(undefined4 *)(iVar10 + 0x6c);
        gnt4_PSMTXRotAxisRad_bl(dVar15,afStack_5c,&local_bc);
        gnt4_PSMTXMultVec_bl(afStack_5c,&local_b0,&local_8c);
      }
    }
    iVar10 = *(int *)(iVar3 + 0xc);
    local_a4 = *(float *)(iVar10 + 0x4c);
    local_a0 = *(float *)(iVar10 + 0x5c);
    local_9c = *(float *)(iVar10 + 0x6c);
    gnt4_PSVECCrossProduct_bl(&local_a4,&local_8c,&local_98);
    dVar15 = gnt4_PSQUATDotProduct_bl(&local_98,&local_98);
    dVar15 = (double)(FLOAT_8043d308 / (float)((double)FLOAT_8043d324 + dVar15));
    if ((double)FLOAT_8043d2f8 < dVar15) {
      dVar11 = 1.0 / SQRT(dVar15);
      dVar11 = DOUBLE_8043d310 * dVar11 * -(dVar15 * dVar11 * dVar11 - DOUBLE_8043d328);
      dVar11 = DOUBLE_8043d310 * dVar11 * -(dVar15 * dVar11 * dVar11 - DOUBLE_8043d328);
      dVar15 = (double)(float)(dVar15 * DOUBLE_8043d310 * dVar11 *
                                        -(dVar15 * dVar11 * dVar11 - DOUBLE_8043d328));
    }
    gnt4_PSQUATScale_bl(dVar15,&local_98,&local_98);
    gnt4_PSVECCrossProduct_bl(&local_8c,&local_98,&local_a4);
    *(float *)(iVar3 + 0x44) = local_8c * local_68;
    *(float *)(iVar3 + 0x54) = local_88 * local_68;
    *(float *)(iVar3 + 100) = local_84 * local_68;
    *(float *)(iVar3 + 0x48) = local_98 * local_64;
    *(float *)(iVar3 + 0x58) = local_94 * local_64;
    *(float *)(iVar3 + 0x68) = local_90 * local_64;
    *(float *)(iVar3 + 0x4c) = local_a4 * local_60;
    *(float *)(iVar3 + 0x5c) = local_a0 * local_60;
    *(float *)(iVar3 + 0x6c) = local_9c * local_60;
    *(float *)(iVar3 + 0x50) = local_74;
    *(undefined4 *)(iVar3 + 0x60) = local_70;
    *(undefined4 *)(iVar3 + 0x70) = local_6c;
  }
  gnt4__restgpr_27_bl();
  return;
}



// ==== 80251908  gnt4-HSD_JObjSetupMatrixSub-bl ====

/* WARNING: Removing unreachable block (ram,0x80251b5c) */
/* WARNING: Removing unreachable block (ram,0x80251918) */

void gnt4_HSD_JObjSetupMatrixSub_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  int local_28;
  int local_24;
  
  uVar5 = (**(code **)(*param_9 + 0x40))();
  param_9[5] = param_9[5] & 0xffffffbf;
  if ((param_9[5] & 0x800000U) != 0) {
    return;
  }
  uVar2 = param_9[5] & 0x600000;
  if (uVar2 == 0x400000) {
    gnt4_resolveIKJoint2_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  else {
    if (uVar2 < 0x400000) {
      if (uVar2 == 0x200000) {
        gnt4_resolveIKJoint1_bl
                  (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4
                   ,param_11,param_12,param_13,param_14,param_15,param_16);
        goto LAB_80251b50;
      }
    }
    else if (uVar2 == 0x600000) {
      iVar4 = param_9[3];
      dVar8 = (double)FLOAT_8043d308;
      if ((iVar4 != 0) &&
         (puVar3 = gnt4_HSD_RObjGetByType_bl(*(undefined4 **)(iVar4 + 0x80),0x40000000,0),
         puVar3 != (undefined4 *)0x0)) {
        local_38 = *(float *)(iVar4 + 0x50);
        local_34 = *(undefined4 *)(iVar4 + 0x60);
        local_30 = *(undefined4 *)(iVar4 + 0x70);
        local_44 = *(float *)(iVar4 + 0x44);
        local_40 = *(undefined4 *)(iVar4 + 0x54);
        local_3c = *(undefined4 *)(iVar4 + 100);
        dVar6 = gnt4_PSQUATDotProduct_bl(&local_44,&local_44);
        dVar6 = (double)(FLOAT_8043d308 / (float)((double)FLOAT_8043d324 + dVar6));
        if ((double)FLOAT_8043d2f8 < dVar6) {
          dVar7 = 1.0 / SQRT(dVar6);
          dVar7 = DOUBLE_8043d310 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_8043d328);
          dVar7 = DOUBLE_8043d310 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_8043d328);
          dVar6 = (double)(float)(dVar6 * DOUBLE_8043d310 * dVar7 *
                                          -(dVar6 * dVar7 * dVar7 - DOUBLE_8043d328));
        }
        gnt4_PSQUATScale_bl(dVar6,&local_44,&local_44);
        if (*(float **)(iVar4 + 0x74) != (float *)0x0) {
          dVar8 = (double)**(float **)(iVar4 + 0x74);
        }
        gnt4_PSQUATScale_bl((double)(float)((double)(float)puVar3[2] * dVar8),&local_44,&local_44);
        gnt4_PSVECAdd_bl(&local_38,&local_44,&local_2c);
        param_9[0x14] = (int)local_2c;
        param_9[0x18] = local_28;
        param_9[0x1c] = local_24;
      }
      goto LAB_80251b50;
    }
    iVar4 = param_9[0x20];
    if (((iVar4 != 0) && (param_9 != (int *)0x0)) && (iVar4 != 0)) {
      uVar5 = gnt4_HSD_RObjUpdateAll_bl
                        (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,param_9
                         ,*(undefined **)(*param_9 + 0x50),param_12,param_13,param_14,param_15,
                         param_16);
      if (param_9 == (int *)0x0) {
        gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435ee8
                         ,0x25d,&DAT_80435ef0,param_12,param_13,param_14,param_15,param_16);
      }
      bVar1 = false;
      if (((param_9[5] & 0x800000U) == 0) && ((param_9[5] & 0x40U) != 0)) {
        bVar1 = true;
      }
      if (bVar1) {
        (**(code **)(*param_9 + 0x40))(param_9);
        param_9[5] = param_9[5] & 0xffffffbf;
      }
    }
  }
LAB_80251b50:
  param_9[5] = param_9[5] & 0xffffffbf;
  return;
}



// ==== 80251b80  gnt4-HSD_JObjSetMtxDirtySub-bl ====

void gnt4_HSD_JObjSetMtxDirtySub_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint extraout_r4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined8 extraout_f1;
  undefined8 uVar11;
  
  iVar2 = gnt4__savegpr_25_bl();
  *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x40;
  if ((*(uint *)(iVar2 + 0x14) & 0x1000) == 0) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = extraout_f1;
    while( true ) {
      if (iVar2 == 0) break;
      if ((*(uint *)(iVar2 + 0x14) & 0x1000000) == 0) {
        if (iVar2 == 0) {
          param_11 = &DAT_80435ef0;
          uVar11 = gnt4___assert_bl(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80435ee8,0x25d,&DAT_80435ef0,param_12,param_13,param_14,
                                    param_15,param_16);
        }
        bVar1 = false;
        if (((*(uint *)(iVar2 + 0x14) & 0x800000) == 0) && ((*(uint *)(iVar2 + 0x14) & 0x40) != 0))
        {
          bVar1 = true;
        }
        if ((!bVar1) &&
           (*(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x40,
           (*(uint *)(iVar2 + 0x14) & 0x1000) == 0)) {
          iVar10 = *(int *)(iVar2 + 0x10);
          while( true ) {
            if (iVar10 == 0) break;
            if ((*(uint *)(iVar10 + 0x14) & 0x1000000) == 0) {
              if (iVar10 == 0) {
                param_11 = &DAT_80435ef0;
                uVar11 = gnt4___assert_bl(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,&DAT_80435ee8,0x25d,&DAT_80435ef0,param_12,
                                          param_13,param_14,param_15,param_16);
              }
              bVar1 = false;
              if (((*(uint *)(iVar10 + 0x14) & 0x800000) == 0) &&
                 ((*(uint *)(iVar10 + 0x14) & 0x40) != 0)) {
                bVar1 = true;
              }
              if ((!bVar1) &&
                 (*(uint *)(iVar10 + 0x14) = *(uint *)(iVar10 + 0x14) | 0x40,
                 (*(uint *)(iVar10 + 0x14) & 0x1000) == 0)) {
                iVar9 = *(int *)(iVar10 + 0x10);
                while( true ) {
                  if (iVar9 == 0) break;
                  if ((*(uint *)(iVar9 + 0x14) & 0x1000000) == 0) {
                    if (iVar9 == 0) {
                      param_11 = &DAT_80435ef0;
                      uVar11 = gnt4___assert_bl(uVar11,param_2,param_3,param_4,param_5,param_6,
                                                param_7,param_8,&DAT_80435ee8,0x25d,&DAT_80435ef0,
                                                param_12,param_13,param_14,param_15,param_16);
                    }
                    bVar1 = false;
                    if (((*(uint *)(iVar9 + 0x14) & 0x800000) == 0) &&
                       ((*(uint *)(iVar9 + 0x14) & 0x40) != 0)) {
                      bVar1 = true;
                    }
                    if ((!bVar1) &&
                       (*(uint *)(iVar9 + 0x14) = *(uint *)(iVar9 + 0x14) | 0x40,
                       (*(uint *)(iVar9 + 0x14) & 0x1000) == 0)) {
                      iVar8 = *(int *)(iVar9 + 0x10);
                      while( true ) {
                        if (iVar8 == 0) break;
                        if ((*(uint *)(iVar8 + 0x14) & 0x1000000) == 0) {
                          if (iVar8 == 0) {
                            param_11 = &DAT_80435ef0;
                            uVar11 = gnt4___assert_bl(uVar11,param_2,param_3,param_4,param_5,param_6
                                                      ,param_7,param_8,&DAT_80435ee8,0x25d,
                                                      &DAT_80435ef0,param_12,param_13,param_14,
                                                      param_15,param_16);
                          }
                          bVar1 = false;
                          if (((*(uint *)(iVar8 + 0x14) & 0x800000) == 0) &&
                             ((*(uint *)(iVar8 + 0x14) & 0x40) != 0)) {
                            bVar1 = true;
                          }
                          if ((!bVar1) &&
                             (*(uint *)(iVar8 + 0x14) = *(uint *)(iVar8 + 0x14) | 0x40,
                             (*(uint *)(iVar8 + 0x14) & 0x1000) == 0)) {
                            iVar7 = *(int *)(iVar8 + 0x10);
                            while( true ) {
                              if (iVar7 == 0) break;
                              if ((*(uint *)(iVar7 + 0x14) & 0x1000000) == 0) {
                                if (iVar7 == 0) {
                                  param_11 = &DAT_80435ef0;
                                  uVar11 = gnt4___assert_bl(uVar11,param_2,param_3,param_4,param_5,
                                                            param_6,param_7,param_8,&DAT_80435ee8,
                                                            0x25d,&DAT_80435ef0,param_12,param_13,
                                                            param_14,param_15,param_16);
                                }
                                bVar1 = false;
                                if (((*(uint *)(iVar7 + 0x14) & 0x800000) == 0) &&
                                   ((*(uint *)(iVar7 + 0x14) & 0x40) != 0)) {
                                  bVar1 = true;
                                }
                                if ((!bVar1) &&
                                   (*(uint *)(iVar7 + 0x14) = *(uint *)(iVar7 + 0x14) | 0x40,
                                   (*(uint *)(iVar7 + 0x14) & 0x1000) == 0)) {
                                  iVar6 = *(int *)(iVar7 + 0x10);
                                  while( true ) {
                                    if (iVar6 == 0) break;
                                    if ((*(uint *)(iVar6 + 0x14) & 0x1000000) == 0) {
                                      if (iVar6 == 0) {
                                        param_11 = &DAT_80435ef0;
                                        uVar11 = gnt4___assert_bl(uVar11,param_2,param_3,param_4,
                                                                  param_5,param_6,param_7,param_8,
                                                                  &DAT_80435ee8,0x25d,&DAT_80435ef0,
                                                                  param_12,param_13,param_14,
                                                                  param_15,param_16);
                                      }
                                      uVar4 = *(uint *)(iVar6 + 0x14);
                                      bVar1 = false;
                                      if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
                                        bVar1 = true;
                                      }
                                      if ((!bVar1) &&
                                         (*(uint *)(iVar6 + 0x14) = *(uint *)(iVar6 + 0x14) | 0x40,
                                         (*(uint *)(iVar6 + 0x14) & 0x1000) == 0)) {
                                        iVar5 = *(int *)(iVar6 + 0x10);
                                        while( true ) {
                                          if (iVar5 == 0) break;
                                          if (((*(uint *)(iVar5 + 0x14) & 0x1000000) == 0) &&
                                             (iVar3 = gnt4_HSD_JObjMtxIsDirty
                                                                (uVar11,param_2,param_3,param_4,
                                                                 param_5,param_6,param_7,param_8,
                                                                 iVar5,uVar4,param_11,param_12,
                                                                 param_13,param_14,param_15,param_16
                                                                ), iVar3 == 0)) {
                                            uVar11 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                                               (uVar11,param_2,param_3,param_4,
                                                                param_5,param_6,param_7,param_8,
                                                                iVar5,uVar4,param_11,param_12,
                                                                param_13,param_14,param_15,param_16)
                                            ;
                                            uVar4 = extraout_r4;
                                          }
                                          iVar5 = *(int *)(iVar5 + 8);
                                        }
                                      }
                                    }
                                    iVar6 = *(int *)(iVar6 + 8);
                                  }
                                }
                              }
                              iVar7 = *(int *)(iVar7 + 8);
                            }
                          }
                        }
                        iVar8 = *(int *)(iVar8 + 8);
                      }
                    }
                  }
                  iVar9 = *(int *)(iVar9 + 8);
                }
              }
            }
            iVar10 = *(int *)(iVar10 + 8);
          }
        }
      }
      iVar2 = *(int *)(iVar2 + 8);
    }
  }
  gnt4__restgpr_25_bl();
  return;
}



// ==== 80251eb4  gnt4-JObjInit-bl ====

int gnt4_JObjInit_bl(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = (**(code **)(DAT_803acc24 + 0x2c))();
  fVar1 = FLOAT_8043d308;
  if (-1 < iVar2) {
    *(undefined4 *)(param_1 + 0x14) = 0x40;
    iVar2 = 0;
    *(float *)(param_1 + 0x2c) = fVar1;
    *(float *)(param_1 + 0x30) = fVar1;
    *(float *)(param_1 + 0x34) = fVar1;
  }
  return iVar2;
}



// ==== 80251f18  gnt4-JObjReleaseChild-bl ====

void gnt4_JObjReleaseChild_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int *param_10,char *param_11
               ,int param_12,uint param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int *extraout_r4;
  int *extraout_r4_00;
  int *extraout_r4_01;
  int *extraout_r4_02;
  int *extraout_r4_03;
  int *extraout_r4_04;
  int *extraout_r4_05;
  int *extraout_r4_06;
  int *extraout_r4_07;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  
  piVar6 = *(int **)(param_9 + 0x10);
  if (piVar6 != (int *)0x0) {
    if ((*(uint *)(param_9 + 0x14) & 0x1000) == 0) {
      piVar6[3] = 0;
      piVar6 = *(int **)(param_9 + 0x10);
      if (piVar6 != (int *)0x0) {
        param_10 = (int *)piVar6[3];
        if (param_10 != (int *)0x0) {
          if ((piVar6 == (int *)0x0) || (param_10 == (int *)0x0)) {
            piVar4 = (int *)0x0;
          }
          else {
            piVar4 = (int *)0x0;
            piVar2 = (int *)param_10[4];
            param_10 = (int *)param_10[4];
            while (piVar1 = piVar2, piVar6 != piVar1) {
              if (piVar1 == (int *)0x0) {
                param_11 = s_can_not_find_specified_jobj__may_803acee4;
                param_1 = (double)gnt4_HSD_Panic_bl(param_1,param_2,param_3,param_4,param_5,param_6,
                                                    param_7,param_8,&DAT_80435ef8,0x5ef,
                                                    s_can_not_find_specified_jobj__may_803acee4,
                                                    param_12,param_13,param_14,param_15,param_16);
                piVar4 = (int *)0x0;
                param_10 = extraout_r4_02;
                break;
              }
              piVar4 = piVar1;
              param_10 = piVar1;
              piVar2 = (int *)piVar1[2];
            }
          }
          if (piVar4 == (int *)0x0) {
            *(undefined4 *)(piVar6[3] + 0x10) = 0;
          }
          else {
            piVar4[2] = 0;
          }
        }
        while (piVar4 = piVar6, piVar4 != (int *)0x0) {
          piVar6 = (int *)piVar4[2];
          piVar4[3] = 0;
          piVar4[2] = 0;
          if (piVar4 != (int *)0x0) {
            param_10 = (int *)(uint)*(ushort *)(piVar4 + 1);
            uVar3 = countLeadingZeros(0xffff - (int)param_10);
            uVar3 = uVar3 >> 5;
            if (uVar3 == 0) {
              uVar3 = countLeadingZeros(param_10);
              *(ushort *)(piVar4 + 1) = *(ushort *)(piVar4 + 1) - 1;
              uVar3 = uVar3 >> 5;
            }
            if (uVar3 != 0) {
              if ((int)(*(ushort *)((int)piVar4 + 6) - 1) < 0) {
                if (piVar4 != (int *)0x0) {
                  (**(code **)(*piVar4 + 0x30))(piVar4);
                  param_1 = (double)(**(code **)(*piVar4 + 0x34))(piVar4);
                  param_10 = extraout_r4_03;
                }
              }
              else {
                *(ushort *)((int)piVar4 + 6) = *(ushort *)((int)piVar4 + 6) + 1;
                if (*(short *)((int)piVar4 + 6) == 0) {
                  param_11 = s_HSD_OBJ_o__>ref_count_individual_803ace24;
                  gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   s_object_h_803acdf0,0x9e,
                                   s_HSD_OBJ_o__>ref_count_individual_803ace24,param_12,param_13,
                                   param_14,param_15,param_16);
                }
                param_1 = (double)(**(code **)(*piVar4 + 0x4c))(piVar4);
                uVar3 = countLeadingZeros((uint)*(ushort *)((int)piVar4 + 6));
                uVar3 = uVar3 >> 5;
                if (uVar3 == 0) {
                  *(ushort *)((int)piVar4 + 6) = *(ushort *)((int)piVar4 + 6) - 1;
                  uVar3 = countLeadingZeros((uint)*(ushort *)((int)piVar4 + 6));
                  uVar3 = uVar3 >> 5;
                }
                param_10 = extraout_r4_04;
                if ((uVar3 != 0) && (piVar4 != (int *)0x0)) {
                  (**(code **)(*piVar4 + 0x30))(piVar4);
                  param_1 = (double)(**(code **)(*piVar4 + 0x34))(piVar4);
                  param_10 = extraout_r4_05;
                }
              }
            }
          }
        }
      }
    }
    else if (piVar6 != (int *)0x0) {
      param_10 = (int *)(uint)*(ushort *)(piVar6 + 1);
      uVar3 = countLeadingZeros(0xffff - (int)param_10);
      uVar3 = uVar3 >> 5;
      if (uVar3 == 0) {
        uVar3 = countLeadingZeros(param_10);
        *(ushort *)(piVar6 + 1) = *(ushort *)(piVar6 + 1) - 1;
        uVar3 = uVar3 >> 5;
      }
      if (uVar3 != 0) {
        if ((int)(*(ushort *)((int)piVar6 + 6) - 1) < 0) {
          if (piVar6 != (int *)0x0) {
            (**(code **)(*piVar6 + 0x30))(piVar6);
            param_1 = (double)(**(code **)(*piVar6 + 0x34))(piVar6);
            param_10 = extraout_r4;
          }
        }
        else {
          *(ushort *)((int)piVar6 + 6) = *(ushort *)((int)piVar6 + 6) + 1;
          if (*(short *)((int)piVar6 + 6) == 0) {
            param_11 = s_HSD_OBJ_o__>ref_count_individual_803ace24;
            gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_object_h_803acdf0,0x9e,s_HSD_OBJ_o__>ref_count_individual_803ace24,
                             param_12,param_13,param_14,param_15,param_16);
          }
          param_1 = (double)(**(code **)(*piVar6 + 0x4c))(piVar6);
          uVar3 = countLeadingZeros((uint)*(ushort *)((int)piVar6 + 6));
          uVar3 = uVar3 >> 5;
          if (uVar3 == 0) {
            *(ushort *)((int)piVar6 + 6) = *(ushort *)((int)piVar6 + 6) - 1;
            uVar3 = countLeadingZeros((uint)*(ushort *)((int)piVar6 + 6));
            uVar3 = uVar3 >> 5;
          }
          param_10 = extraout_r4_00;
          if ((uVar3 != 0) && (piVar6 != (int *)0x0)) {
            (**(code **)(*piVar6 + 0x30))(piVar6);
            param_1 = (double)(**(code **)(*piVar6 + 0x34))(piVar6);
            param_10 = extraout_r4_01;
          }
        }
      }
    }
    *(undefined4 *)(param_9 + 0x10) = 0;
  }
  iVar5 = *(int *)(param_9 + 0xc);
  if ((iVar5 != 0) && (param_9 != 0)) {
    uVar7 = *(undefined4 *)(param_9 + 8);
    if (iVar5 != 0) {
      iVar8 = *(int *)(iVar5 + 0x10);
      if (iVar8 == param_9) {
        *(undefined4 *)(iVar5 + 0x10) = uVar7;
      }
      else {
        if ((param_9 == 0) || (iVar5 == 0)) {
          iVar5 = 0;
        }
        else if (param_9 == iVar8) {
          iVar5 = 0;
        }
        else {
          do {
            iVar5 = iVar8;
            if (iVar5 == 0) {
              param_11 = s_can_not_find_specified_jobj__may_803acee4;
              param_1 = (double)gnt4_HSD_Panic_bl(param_1,param_2,param_3,param_4,param_5,param_6,
                                                  param_7,param_8,&DAT_80435ef8,0x5ef,
                                                  s_can_not_find_specified_jobj__may_803acee4,
                                                  param_12,param_13,param_14,param_15,param_16);
              iVar5 = 0;
              break;
            }
            iVar8 = *(int *)(iVar5 + 8);
          } while (*(int *)(iVar5 + 8) != param_9);
        }
        if (iVar5 == 0) {
          param_11 = &DAT_80435f04;
          param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7
                                             ,param_8,&DAT_80435ef8,0x572,&DAT_80435f04,param_12,
                                             param_13,param_14,param_15,param_16);
        }
        *(undefined4 *)(iVar5 + 8) = uVar7;
      }
      param_10 = (int *)0x90000000;
      for (param_12 = *(int *)(param_9 + 0xc); param_12 != 0; param_12 = *(int *)(param_12 + 8)) {
        param_11 = (char *)0x8fffffff;
        for (iVar5 = *(int *)(param_12 + 0x10); iVar5 != 0; iVar5 = *(int *)(iVar5 + 8)) {
          param_13 = *(uint *)(iVar5 + 0x14);
          param_11 = (char *)((uint)param_11 | (param_13 | param_13 << 10) & 0x70000000);
        }
        if ((*(uint *)(param_12 + 0x14) & ~(uint)param_11) == 0) break;
        *(uint *)(param_12 + 0x14) = *(uint *)(param_12 + 0x14) & (uint)param_11;
      }
      *(undefined4 *)(param_9 + 0xc) = 0;
    }
    *(undefined4 *)(param_9 + 8) = 0;
  }
  uVar3 = countLeadingZeros(*(uint *)(param_9 + 0x14) & 0x4020);
  if ((uVar3 >> 5 != 0) && (*(int **)(param_9 + 0x18) != (int *)0x0)) {
    param_1 = (double)gnt4_HSD_DObjRemoveAll_bl(*(int **)(param_9 + 0x18));
    *(undefined4 *)(param_9 + 0x18) = 0;
    param_10 = extraout_r4_06;
  }
  if (*(undefined4 **)(param_9 + 0x80) != (undefined4 *)0x0) {
    param_1 = (double)gnt4_HSD_RObjRemoveAll_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(undefined4 **)(param_9 + 0x80),param_10,param_11,param_12,
                                 param_13,param_14,param_15,param_16);
    *(undefined4 *)(param_9 + 0x80) = 0;
    param_10 = extraout_r4_07;
  }
  if (*(undefined4 **)(param_9 + 0x7c) != (undefined4 *)0x0) {
    gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(undefined4 **)(param_9 + 0x7c),param_10,param_11,param_12,param_13,
                        param_14,param_15,param_16);
    *(undefined4 *)(param_9 + 0x7c) = 0;
  }
  return;
}



// ==== 802523ec  gnt4-JObjRelease-bl ====

void gnt4_JObjRelease_bl(int *param_1)

{
  int *piVar1;
  
  (**(code **)(*param_1 + 0x4c))();
  piVar1 = (int *)gnt4_HSD_IDGetDataFromTable_bl((undefined *)0x0,param_1[0x21],(undefined4 *)0x0);
  if (piVar1 == param_1) {
    gnt4_HSD_IDRemoveByIDFromTable_bl((undefined *)0x0,param_1[0x21]);
  }
  if ((undefined4 *)param_1[0x1d] != (undefined4 *)0x0) {
    gnt4_HSD_VecFree_bl((undefined4 *)param_1[0x1d]);
  }
  if ((undefined4 *)param_1[0x1e] != (undefined4 *)0x0) {
    gnt4_HSD_MtxFree_bl((undefined4 *)param_1[0x1e]);
  }
  (**(code **)(DAT_803acc24 + 0x30))(param_1);
  return;
}



// ==== 80252484  gnt4-JObjAmnesia-bl ====

void gnt4_JObjAmnesia_bl(undefined **param_1)

{
  if (param_1 == DAT_80436980) {
    DAT_80436980 = (undefined **)0x0;
  }
  if (param_1 == &PTR_gnt4_JObjInfoInit_bl_803acc10) {
    DAT_80436984 = 0;
    DAT_80436994 = 0;
  }
  (**(code **)(DAT_803acc24 + 0x38))();
  return;
}



// ==== 802524e8  gnt4-JObjInfoInit-bl ====

void gnt4_JObjInfoInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc533f0,
             &PTR_zz_025acb8__803ad548,s_sysdolphin_base_library_803acfac,s_hsd_jobj_803acfc4,0x54,
             0x88,in_r9,in_r10);
  DAT_803acc3c = gnt4_JObjInit_bl;
  DAT_803acc40 = gnt4_JObjRelease_bl;
  DAT_803acc48 = gnt4_JObjAmnesia_bl;
  DAT_803acc50 = gnt4_HSD_JObjMakeMatrix;
  DAT_803acc54 = gnt4_HSD_JObjMakePositionMtx_bl;
  DAT_803acc58 = gnt4_HSD_JObjDispSub_bl;
  DAT_803acc4c = gnt4_JObjLoad;
  DAT_803acc5c = gnt4_JObjReleaseChild_bl;
  DAT_803acc60 = gnt4_JObjUpdateFunc;
  return;
}



// ==== 802525a4  gnt4-HSD_ZListInitAllocData-bl ====

void gnt4_HSD_ZListInitAllocData_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_HSD_ObjAllocInit_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803f8e28,0x48,4,
             in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 802525d4  gnt4-mkVBillBoardMtx-bl ====

/* WARNING: Removing unreachable block (ram,0x8025288c) */
/* WARNING: Removing unreachable block (ram,0x80252884) */
/* WARNING: Removing unreachable block (ram,0x802525ec) */
/* WARNING: Removing unreachable block (ram,0x802525e4) */

void gnt4_mkVBillBoardMtx_bl(int param_1,float *param_2,float *param_3)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  float local_80;
  undefined4 local_7c;
  undefined4 local_78;
  float afStack_74 [3];
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
  
  local_44 = param_2[3];
  local_40 = param_2[7];
  local_3c = param_2[0xb];
  local_5c = param_2[1];
  local_58 = param_2[5];
  local_54 = param_2[9];
  dVar2 = gnt4_PSVECMag_bl(&local_5c);
  gnt4_PSQUATScale_bl((double)(FLOAT_8043d340 / (float)((double)FLOAT_8043d344 + dVar2)),&local_5c,
                      afStack_74);
  dVar2 = (double)(param_2[8] * param_2[8] + param_2[4] * param_2[4] + *param_2 * *param_2);
  if ((double)FLOAT_8043d348 < dVar2) {
    dVar3 = 1.0 / SQRT(dVar2);
    dVar3 = DOUBLE_8043d350 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d358);
    dVar3 = DOUBLE_8043d350 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d358);
    dVar2 = (double)(float)(dVar2 * DOUBLE_8043d350 * dVar3 *
                                    -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d358));
  }
  dVar3 = (double)(param_2[10] * param_2[10] + param_2[6] * param_2[6] + param_2[2] * param_2[2]);
  if ((double)FLOAT_8043d348 < dVar3) {
    dVar4 = 1.0 / SQRT(dVar3);
    dVar4 = DOUBLE_8043d350 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358);
    dVar4 = DOUBLE_8043d350 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358);
    dVar3 = (double)(float)(dVar3 * DOUBLE_8043d350 * dVar4 *
                                    -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358));
  }
  if ((*(uint *)(param_1 + 0x14) & 0x2000) == 0) {
    local_80 = DAT_802b5240;
    local_7c = DAT_802b5244;
    local_78 = DAT_802b5248;
    gnt4_PSVECCrossProduct_bl(afStack_74,&local_80,&local_50);
  }
  else {
    dVar4 = gnt4_PSVECMag_bl(&local_44);
    gnt4_PSQUATScale_bl((double)(FLOAT_8043d360 / (float)((double)FLOAT_8043d344 + dVar4)),&local_44
                        ,&local_68);
    gnt4_PSVECCrossProduct_bl(afStack_74,&local_68,&local_50);
  }
  dVar4 = gnt4_PSVECMag_bl(&local_50);
  if (dVar4 < (double)FLOAT_8043d344) {
    gnt4_PSMTXCopy_bl(param_2,param_3);
  }
  else {
    dVar5 = (double)(float)(dVar2 / dVar4);
    gnt4_PSVECCrossProduct_bl(&local_50,afStack_74,&local_68);
    dVar2 = gnt4_PSVECMag_bl(&local_68);
    dVar4 = (double)FLOAT_8043d344;
    *param_3 = (float)(dVar5 * (double)local_50);
    fVar1 = (float)(dVar3 / (double)(float)(dVar4 + dVar2));
    param_3[4] = (float)(dVar5 * (double)local_4c);
    param_3[8] = (float)(dVar5 * (double)local_48);
    param_3[1] = local_5c;
    param_3[5] = local_58;
    param_3[9] = local_54;
    param_3[2] = fVar1 * local_68;
    param_3[6] = fVar1 * local_64;
    param_3[10] = fVar1 * local_60;
    param_3[3] = local_44;
    param_3[7] = local_40;
    param_3[0xb] = local_3c;
  }
  return;
}



// ==== 802528b0  gnt4-mkHBillBoardMtx-bl ====

/* WARNING: Removing unreachable block (ram,0x80252bd0) */
/* WARNING: Removing unreachable block (ram,0x80252bc8) */
/* WARNING: Removing unreachable block (ram,0x80252bc0) */
/* WARNING: Removing unreachable block (ram,0x80252bb8) */
/* WARNING: Removing unreachable block (ram,0x80252bb0) */
/* WARNING: Removing unreachable block (ram,0x802528e0) */
/* WARNING: Removing unreachable block (ram,0x802528d8) */
/* WARNING: Removing unreachable block (ram,0x802528d0) */
/* WARNING: Removing unreachable block (ram,0x802528c8) */
/* WARNING: Removing unreachable block (ram,0x802528c0) */

void gnt4_mkHBillBoardMtx_bl(int param_1,float *param_2,float *param_3)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float afStack_9c [3];
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  
  dVar8 = (double)param_2[3];
  dVar7 = (double)param_2[7];
  dVar6 = (double)param_2[0xb];
  local_78 = *param_2;
  local_74 = param_2[4];
  local_70 = param_2[8];
  dVar2 = gnt4_PSVECMag_bl(&local_78);
  gnt4_PSQUATScale_bl((double)(FLOAT_8043d340 / (float)((double)FLOAT_8043d344 + dVar2)),&local_78,
                      afStack_9c);
  dVar2 = (double)(param_2[9] * param_2[9] + param_2[5] * param_2[5] + param_2[1] * param_2[1]);
  if ((double)FLOAT_8043d348 < dVar2) {
    dVar3 = 1.0 / SQRT(dVar2);
    dVar3 = DOUBLE_8043d350 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d358);
    dVar3 = DOUBLE_8043d350 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d358);
    dVar2 = (double)(float)(dVar2 * DOUBLE_8043d350 * dVar3 *
                                    -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d358));
  }
  dVar3 = (double)(param_2[10] * param_2[10] + param_2[6] * param_2[6] + param_2[2] * param_2[2]);
  if ((double)FLOAT_8043d348 < dVar3) {
    dVar4 = 1.0 / SQRT(dVar3);
    dVar4 = DOUBLE_8043d350 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358);
    dVar4 = DOUBLE_8043d350 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358);
    dVar3 = (double)(float)(dVar3 * DOUBLE_8043d350 * dVar4 *
                                    -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358));
  }
  if ((*(uint *)(param_1 + 0x14) & 0x2000) == 0) {
    local_84 = FLOAT_8043d348;
    local_80 = FLOAT_8043d340;
    local_7c = FLOAT_8043d348;
  }
  else {
    dVar4 = (double)(float)(dVar8 * dVar8 + (double)(float)(dVar6 * dVar6));
    if ((double)FLOAT_8043d348 < dVar4) {
      dVar5 = 1.0 / SQRT(dVar4);
      dVar5 = DOUBLE_8043d350 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_8043d358);
      dVar5 = DOUBLE_8043d350 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_8043d358);
      dVar4 = (double)(float)(dVar4 * DOUBLE_8043d350 * dVar5 *
                                      -(dVar4 * dVar5 * dVar5 - DOUBLE_8043d358));
    }
    local_80 = (float)((double)FLOAT_8043d344 + dVar4);
    local_84 = (float)(dVar8 * (double)(float)(-dVar7 / (double)local_80));
    local_7c = (float)(dVar6 * (double)(float)(-dVar7 / (double)local_80));
    gnt4_PSVECNormalize_bl(&local_84,&local_84);
  }
  gnt4_PSVECCrossProduct_bl(afStack_9c,&local_84,&local_90);
  dVar4 = gnt4_PSVECMag_bl(&local_90);
  if (dVar4 < (double)FLOAT_8043d344) {
    gnt4_PSMTXCopy_bl(param_2,param_3);
  }
  else {
    dVar5 = (double)(float)(dVar3 / dVar4);
    gnt4_PSVECCrossProduct_bl(&local_90,afStack_9c,&local_84);
    dVar3 = gnt4_PSVECMag_bl(&local_84);
    dVar4 = (double)FLOAT_8043d344;
    *param_3 = local_78;
    fVar1 = (float)(dVar2 / (double)(float)(dVar4 + dVar3));
    param_3[4] = local_74;
    param_3[8] = local_70;
    param_3[1] = fVar1 * local_84;
    param_3[5] = fVar1 * local_80;
    param_3[9] = fVar1 * local_7c;
    param_3[2] = (float)(dVar5 * (double)local_90);
    param_3[6] = (float)(dVar5 * (double)local_8c);
    param_3[10] = (float)(dVar5 * (double)local_88);
    param_3[3] = (float)dVar8;
    param_3[7] = (float)dVar7;
    param_3[0xb] = (float)dVar6;
  }
  return;
}



// ==== 80252bf4  gnt4-mkBillBoardMtx-bl ====

/* WARNING: Removing unreachable block (ram,0x80252f68) */
/* WARNING: Removing unreachable block (ram,0x80252f60) */
/* WARNING: Removing unreachable block (ram,0x80252f58) */
/* WARNING: Removing unreachable block (ram,0x80252c14) */
/* WARNING: Removing unreachable block (ram,0x80252c0c) */
/* WARNING: Removing unreachable block (ram,0x80252c04) */

void gnt4_mkBillBoardMtx_bl(int param_1,float *param_2,float *param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
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
  
  dVar5 = (double)(param_2[8] * param_2[8] + param_2[4] * param_2[4] + *param_2 * *param_2);
  if ((double)FLOAT_8043d348 < dVar5) {
    dVar1 = 1.0 / SQRT(dVar5);
    dVar1 = DOUBLE_8043d350 * dVar1 * -(dVar5 * dVar1 * dVar1 - DOUBLE_8043d358);
    dVar1 = DOUBLE_8043d350 * dVar1 * -(dVar5 * dVar1 * dVar1 - DOUBLE_8043d358);
    dVar5 = (double)(float)(dVar5 * DOUBLE_8043d350 * dVar1 *
                                    -(dVar5 * dVar1 * dVar1 - DOUBLE_8043d358));
  }
  dVar1 = (double)(param_2[10] * param_2[10] + param_2[6] * param_2[6] + param_2[2] * param_2[2]);
  if ((double)FLOAT_8043d348 < dVar1) {
    dVar2 = 1.0 / SQRT(dVar1);
    dVar2 = DOUBLE_8043d350 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d358);
    dVar2 = DOUBLE_8043d350 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d358);
    dVar1 = (double)(float)(dVar1 * DOUBLE_8043d350 * dVar2 *
                                    -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d358));
  }
  local_64 = param_2[1];
  local_60 = param_2[5];
  local_5c = param_2[9];
  dVar2 = gnt4_PSVECMag_bl(&local_64);
  local_7c = param_2[3];
  local_78 = param_2[7];
  local_74 = param_2[0xb];
  if ((*(uint *)(param_1 + 0x14) & 0x2000) == 0) {
    local_70 = FLOAT_8043d348;
    local_6c = FLOAT_8043d348;
    local_68 = FLOAT_8043d340;
  }
  else {
    dVar3 = gnt4_PSVECMag_bl(&local_7c);
    gnt4_PSQUATScale_bl((double)(FLOAT_8043d360 / (float)((double)FLOAT_8043d344 + dVar3)),&local_7c
                        ,&local_70);
  }
  gnt4_PSQUATScale_bl((double)(FLOAT_8043d340 / (float)((double)FLOAT_8043d344 + dVar2)),&local_64,
                      &local_64);
  gnt4_PSVECCrossProduct_bl(&local_64,&local_70,&local_58);
  dVar3 = gnt4_PSVECMag_bl(&local_58);
  if (dVar3 < (double)FLOAT_8043d344) {
    dVar3 = (double)(local_70 * local_70 + local_68 * local_68);
    if ((double)FLOAT_8043d348 < dVar3) {
      dVar4 = 1.0 / SQRT(dVar3);
      dVar4 = DOUBLE_8043d350 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358);
      dVar4 = DOUBLE_8043d350 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358);
      dVar3 = (double)(float)(dVar3 * DOUBLE_8043d350 * dVar4 *
                                      -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358));
    }
    local_60 = (float)((double)FLOAT_8043d344 + dVar3);
    local_64 = local_70 * (-local_6c / local_60);
    local_5c = local_68 * (-local_6c / local_60);
    gnt4_PSVECCrossProduct_bl(&local_64,&local_70,&local_58);
    dVar3 = gnt4_PSVECMag_bl(&local_58);
    dVar5 = (double)(float)(dVar5 / (double)(float)((double)FLOAT_8043d344 + dVar3));
  }
  else {
    dVar5 = (double)(float)(dVar5 / dVar3);
    gnt4_PSVECCrossProduct_bl(&local_70,&local_58,&local_64);
    dVar3 = gnt4_PSVECMag_bl(&local_64);
    dVar2 = (double)(float)(dVar2 / (double)(float)((double)FLOAT_8043d344 + dVar3));
  }
  *param_3 = (float)(dVar5 * (double)local_58);
  param_3[4] = (float)(dVar5 * (double)local_54);
  param_3[8] = (float)(dVar5 * (double)local_50);
  param_3[1] = (float)(dVar2 * (double)local_64);
  param_3[5] = (float)(dVar2 * (double)local_60);
  param_3[9] = (float)(dVar2 * (double)local_5c);
  param_3[2] = (float)(dVar1 * (double)local_70);
  param_3[6] = (float)(dVar1 * (double)local_6c);
  param_3[10] = (float)(dVar1 * (double)local_68);
  param_3[3] = local_7c;
  param_3[7] = local_78;
  param_3[0xb] = local_74;
  return;
}



// ==== 80252f8c  gnt4-mkRBillBoardMtx ====

void gnt4_mkRBillBoardMtx(int param_1,float *param_2,float *param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float afStack_7c [12];
  float afStack_4c [3];
  float local_40;
  float local_30;
  float local_20;
  
  dVar1 = (double)(param_2[8] * param_2[8] + param_2[4] * param_2[4] + *param_2 * *param_2);
  if ((double)FLOAT_8043d348 < dVar1) {
    dVar2 = 1.0 / SQRT(dVar1);
    dVar2 = DOUBLE_8043d350 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d358);
    dVar2 = DOUBLE_8043d350 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d358);
    dVar1 = (double)(float)(dVar1 * DOUBLE_8043d350 * dVar2 *
                                    -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d358));
  }
  dVar2 = (double)(param_2[9] * param_2[9] + param_2[5] * param_2[5] + param_2[1] * param_2[1]);
  if ((double)FLOAT_8043d348 < dVar2) {
    dVar3 = 1.0 / SQRT(dVar2);
    dVar3 = DOUBLE_8043d350 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d358);
    dVar3 = DOUBLE_8043d350 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d358);
    dVar2 = (double)(float)(dVar2 * DOUBLE_8043d350 * dVar3 *
                                    -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d358));
  }
  dVar3 = (double)(param_2[10] * param_2[10] + param_2[6] * param_2[6] + param_2[2] * param_2[2]);
  if ((double)FLOAT_8043d348 < dVar3) {
    dVar4 = 1.0 / SQRT(dVar3);
    dVar4 = DOUBLE_8043d350 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358);
    dVar4 = DOUBLE_8043d350 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358);
    dVar3 = (double)(float)(dVar3 * DOUBLE_8043d350 * dVar4 *
                                    -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d358));
  }
  gnt4_PSMTXScale_bl(dVar1,dVar2,dVar3,afStack_7c);
  gnt4_PSMTXRotRad_bl((double)*(float *)(param_1 + 0x24),afStack_4c,0x7a);
  local_40 = param_2[3];
  local_30 = param_2[7];
  local_20 = param_2[0xb];
  gnt4_PSMTXConcat_bl(afStack_4c,afStack_7c,param_3);
  return;
}



// ==== 80253174  gnt4-HSD_JObjMakePositionMtx-bl ====

void gnt4_HSD_JObjMakePositionMtx_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,float *param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  double dVar2;
  float afStack_38 [12];
  
  if ((*(uint *)(param_9 + 0x14) & 0xe00) == 0) {
    gnt4_PSMTXConcat_bl(param_10,(float *)(param_9 + 0x44),param_11);
  }
  else {
    dVar2 = (double)gnt4_PSMTXConcat_bl(param_10,(float *)(param_9 + 0x44),afStack_38);
    uVar1 = *(uint *)(param_9 + 0x14) & 0xe00;
    if (uVar1 == 0x600) {
      gnt4_mkHBillBoardMtx_bl(param_9,afStack_38,param_11);
    }
    else {
      if (uVar1 < 0x600) {
        if (uVar1 == 0x400) {
          gnt4_mkVBillBoardMtx_bl(param_9,afStack_38,param_11);
          return;
        }
        if ((uVar1 < 0x400) && (uVar1 == 0x200)) {
          gnt4_mkBillBoardMtx_bl(param_9,afStack_38,param_11);
          return;
        }
      }
      else if (uVar1 == 0x800) {
        gnt4_mkRBillBoardMtx(param_9,afStack_38,param_11);
        return;
      }
      gnt4_HSD_Panic_bl(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        s_displayfunc_c_803acfe0,0x170,s_unkown_type_of_billboard__803acff0,param_12
                        ,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80253274  gnt4-_HSD_mkEnvelopeModelNodeMtx-bl ====

float * gnt4__HSD_mkEnvelopeModelNodeMtx_bl
                  (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                  double param_6,double param_7,double param_8,int param_9,float *param_10,
                  undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                  undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float afStack_48 [15];
  
  if ((*(uint *)(param_9 + 0x14) & 2) == 0) {
    iVar1 = param_9;
    if (param_9 == 0) {
      param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 s_displayfunc_c_803acfe0,0x184,&DAT_80435f28,param_12,param_13,
                                 param_14,param_15,param_16);
    }
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
      if ((*(uint *)(iVar1 + 0x14) & 3) != 0) goto LAB_802532ec;
    }
    iVar1 = 0;
LAB_802532ec:
    if (iVar1 == 0) {
      gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_displayfunc_c_803acfe0,0x1d4,&DAT_80435f30,param_12,param_13,param_14,
                       param_15,param_16);
    }
    if (iVar1 == param_9) {
      gnt4_PSMTXInverse_bl(*(float **)(iVar1 + 0x78),param_10);
    }
    else if ((*(uint *)(iVar1 + 0x14) & 2) == 0) {
      gnt4_PSMTXConcat_bl((float *)(iVar1 + 0x44),*(float **)(iVar1 + 0x78),afStack_48);
      gnt4_HSD_MtxInverseConcat_bl(afStack_48,(float *)(param_9 + 0x44),param_10);
    }
    else {
      gnt4_HSD_MtxInverseConcat_bl((float *)(iVar1 + 0x44),(float *)(param_9 + 0x44),param_10);
    }
  }
  else {
    param_10 = (float *)0x0;
  }
  return param_10;
}



// ==== 80253380  gnt4-HSD_JObjDispSub-bl ====

void gnt4_HSD_JObjDispSub_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               int param_11,uint param_12,uint param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  undefined8 extraout_f1;
  undefined8 uVar6;
  undefined8 uVar7;
  
  uVar7 = gnt4__savegpr_27_bl();
  iVar1 = (int)((ulonglong)uVar7 >> 0x20);
  iVar2 = param_11;
  uVar3 = param_12;
  uVar4 = param_13;
  uVar6 = gnt4_HSD_JObjSetCurrent
                    (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                     (int)uVar7,param_11,param_12,param_13,param_14,param_15,param_16);
  if (((param_13 & 0x4000000) == 0) && ((*(uint *)(iVar1 + 0x14) & 0x10000) != 0)) {
    gnt4_HSD_LObjSetupSpecularInit_bl
              (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_11,extraout_r4,
               iVar2,uVar3,uVar4,param_14,param_15,param_16);
  }
  gnt4_HSD_PObjClearMtxMark_bl(0,0);
  piVar5 = *(int **)(iVar1 + 0x18);
  while( true ) {
    if (piVar5 == (int *)0x0) break;
    if (((piVar5[5] & 1U) == 0) && ((piVar5[5] & param_12 << 1) != 0)) {
      gnt4_HSD_DObjSetCurrent_bl(piVar5);
      iVar2 = param_11;
      uVar3 = param_13;
      (**(code **)(*piVar5 + 0x3c))(piVar5,(int)uVar7);
    }
    piVar5 = (int *)piVar5[1];
  }
  uVar6 = gnt4_HSD_DObjSetCurrent_bl(0);
  gnt4_HSD_JObjSetCurrent
            (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4_00,iVar2,
             uVar3,uVar4,param_14,param_15,param_16);
  gnt4__restgpr_27_bl();
  return;
}



// ==== 80253450  gnt4-HSD_JObjDispDObj-bl ====

/* WARNING: Removing unreachable block (ram,0x80253494) */

void gnt4_HSD_JObjDispDObj_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined *param_11,float param_12,float param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  float *pfVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar7;
  float *pfVar8;
  uint uVar9;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 uVar10;
  float afStack_48 [18];
  
  uVar10 = gnt4__savegpr_27_bl();
  piVar2 = (int *)((ulonglong)uVar10 >> 0x20);
  pfVar8 = (float *)uVar10;
  if (((piVar2[5] & 0x10U) == 0) && (uVar9 = piVar2[5] & (int)param_11 << 0x12, uVar9 != 0)) {
    if (piVar2 != (int *)0x0) {
      uVar6 = piVar2[5];
      bVar1 = false;
      if (((uVar6 & 0x800000) == 0) && ((uVar6 & 0x40) != 0)) {
        bVar1 = true;
      }
      if (bVar1) {
        gnt4_HSD_JObjSetupMatrixSub_bl
                  (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,uVar6,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      }
    }
    if (pfVar8 == (float *)0x0) {
      iVar3 = gnt4_HSD_CObjGetCurrent();
      pfVar8 = (float *)(iVar3 + 0x54);
    }
    iVar3 = *piVar2;
    pfVar4 = afStack_48;
    uVar10 = (**(code **)(iVar3 + 0x44))(piVar2,pfVar8);
    uVar7 = extraout_r4;
    if ((uVar9 & 0x40000) != 0) {
      pfVar4 = afStack_48;
      iVar3 = 1;
      param_13 = param_12;
      uVar10 = (**(code **)(*piVar2 + 0x48))(piVar2,pfVar8);
      uVar7 = extraout_r4_00;
    }
    if (DAT_8043699c == 0) {
      if ((uVar9 & 0x100000) != 0) {
        (**(code **)(*piVar2 + 0x48))(piVar2,pfVar8,afStack_48,4,param_12);
      }
      if ((uVar9 & 0x80000) != 0) {
        (**(code **)(*piVar2 + 0x48))(piVar2,pfVar8,afStack_48,2,param_12);
      }
    }
    else if ((uVar9 & 0x180000) != 0) {
      pfVar4 = (float *)gnt4_HSD_ObjAlloc(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,&DAT_803f8e28,uVar7,pfVar4,iVar3,param_13,param_14
                                          ,param_15,param_16);
      uVar7 = 0x18;
      gnt4_memset(pfVar4 + 0xc,0,0x18);
      uVar10 = gnt4_PSMTXCopy_bl(afStack_48,pfVar4);
      if (pfVar8 != (float *)0x0) {
        puVar5 = gnt4_HSD_MtxAlloc_bl
                           (extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int)((ulonglong)uVar10 >> 0x20),(int)uVar10,uVar7,iVar3,param_13,
                            param_14,param_15,param_16);
        pfVar4[0xc] = (float)puVar5;
        gnt4_PSMTXCopy_bl(pfVar8,(float *)pfVar4[0xc]);
      }
      pfVar4[0xd] = (float)piVar2;
      pfVar4[0xe] = param_12;
      *DAT_80435f1c = (float)pfVar4;
      DAT_80435f1c = pfVar4 + 0x11;
      if ((uVar9 & 0x100000) != 0) {
        *DAT_80435f20 = (float)pfVar4;
        DAT_804369ac = DAT_804369ac + 1;
        DAT_80435f20 = pfVar4 + 0xf;
      }
      if ((uVar9 & 0x80000) != 0) {
        *DAT_80435f24 = (float)pfVar4;
        DAT_804369b4 = DAT_804369b4 + 1;
        DAT_80435f24 = pfVar4 + 0x10;
      }
    }
  }
  gnt4__restgpr_27_bl();
  return;
}



// ==== 80253658  gnt4-zlist_sort-bl ====

int gnt4_zlist_sort_bl(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int local_18 [3];
  
  local_18[0] = param_1;
  if (param_2 < 2) {
    if (param_1 != 0) {
      *(undefined4 *)(param_1 + param_3) = 0;
    }
  }
  else {
    iVar4 = 0;
    iVar3 = param_2 / 2;
    iVar5 = param_1;
    if (0 < iVar3) {
      if ((8 < iVar3) && (uVar6 = iVar3 - 1U >> 3, 0 < iVar3 + -8)) {
        do {
          iVar4 = iVar4 + 8;
          iVar5 = *(int *)(*(int *)(*(int *)(*(int *)(*(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 
                                                  param_3) + param_3) + param_3) + param_3) +
                                                  param_3) + param_3) + param_3) + param_3);
          uVar6 = uVar6 - 1;
        } while (uVar6 != 0);
      }
      iVar1 = iVar3 - iVar4;
      if (iVar4 < iVar3) {
        do {
          iVar5 = *(int *)(iVar5 + param_3);
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
    }
    iVar4 = gnt4_zlist_sort_bl(param_1,iVar3,param_3);
    iVar5 = gnt4_zlist_sort_bl(iVar5,param_2 - iVar3,param_3);
    piVar2 = local_18;
    local_18[0] = 0;
    while ((iVar4 != 0 && (iVar5 != 0))) {
      if (*(float *)(iVar5 + 0x2c) < *(float *)(iVar4 + 0x2c)) {
        *piVar2 = iVar5;
        iVar5 = *(int *)(iVar5 + param_3);
      }
      else {
        *piVar2 = iVar4;
        iVar4 = *(int *)(iVar4 + param_3);
      }
      piVar2 = (int *)(*piVar2 + param_3);
    }
    if (iVar4 == 0) {
      if (iVar5 != 0) {
        *piVar2 = iVar5;
      }
    }
    else {
      *piVar2 = iVar4;
    }
  }
  return local_18[0];
}



// ==== 802537c4  gnt4-_HSD_ZListSort-bl ====

void gnt4__HSD_ZListSort_bl(void)

{
  if (DAT_804369a0 != 0) {
    DAT_804369a8 = gnt4_zlist_sort_bl(DAT_804369a8,DAT_804369ac,0x3c);
    DAT_804369b0 = gnt4_zlist_sort_bl(DAT_804369b0,DAT_804369b4,0x40);
  }
  return;
}



// ==== 80253814  gnt4-_HSD_ZListDisp-bl ====

void gnt4__HSD_ZListDisp_bl(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = gnt4_HSD_CObjGetCurrent();
  for (iVar3 = DAT_804369a8; iVar2 = DAT_804369b0, iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x3c)) {
    iVar2 = iVar1 + 0x54;
    if (*(int *)(iVar3 + 0x30) != 0) {
      iVar2 = *(int *)(iVar3 + 0x30);
    }
    (**(code **)(**(int **)(iVar3 + 0x34) + 0x48))
              (*(int **)(iVar3 + 0x34),iVar2,iVar3,4,*(undefined4 *)(iVar3 + 0x38));
  }
  for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x40)) {
    iVar3 = iVar1 + 0x54;
    if (*(int *)(iVar2 + 0x30) != 0) {
      iVar3 = *(int *)(iVar2 + 0x30);
    }
    (**(code **)(**(int **)(iVar2 + 0x34) + 0x48))
              (*(int **)(iVar2 + 0x34),iVar3,iVar2,2,*(undefined4 *)(iVar2 + 0x38));
  }
  gnt4__HSD_ZListClear_bl();
  return;
}



// ==== 802538dc  gnt4-_HSD_ZListClear-bl ====

void gnt4__HSD_ZListClear_bl(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = DAT_804369a4;
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)puVar2[0x11];
    if ((undefined4 *)puVar2[0xc] != (undefined4 *)0x0) {
      gnt4_HSD_MtxFree_bl((undefined4 *)puVar2[0xc]);
    }
    gnt4_HSD_ObjFree(-0x7fc071d8,puVar2);
    puVar2 = puVar1;
  }
  DAT_804369a4 = (undefined4 *)0x0;
  DAT_80435f1c = &DAT_804369a4;
  DAT_804369a8 = 0;
  DAT_80435f20 = &DAT_804369a8;
  DAT_804369ac = 0;
  DAT_804369b0 = 0;
  DAT_80435f24 = &DAT_804369b0;
  DAT_804369b4 = 0;
  return;
}



// ==== 8025397c  gnt4-HSD_SetZSortMode-bl ====

void gnt4_HSD_SetZSortMode_bl(undefined4 param_1,undefined4 param_2)

{
  DAT_8043699c = param_1;
  DAT_804369a0 = param_2;
  return;
}



// ==== 80253988  gnt4-HSD_JObjDisp-bl ====

void gnt4_HSD_JObjDisp_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined *param_11,float param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  float fVar2;
  undefined4 *puVar3;
  
  if (param_9 != 0) {
    fVar2 = *(float *)(param_9 + 0x14);
    uVar1 = countLeadingZeros((uint)fVar2 & 0x4020);
    if (uVar1 >> 5 == 0) {
      if ((((uint)fVar2 & 0x20) != 0) && (DAT_80436998 != (code *)0x0)) {
        puVar3 = *(undefined4 **)(param_9 + 0x18);
        while( true ) {
          if (puVar3 == (undefined4 *)0x0) break;
          uVar1 = puVar3[1];
          if ((uVar1 & 0x80000000) != 0) {
            (*DAT_80436998)(0,uVar1 & 0x3f,uVar1 >> 6 & 0xffffff,param_9);
          }
          puVar3[1] = puVar3[1] & 0x7fffffff;
          puVar3 = (undefined4 *)*puVar3;
        }
      }
    }
    else {
      gnt4_HSD_JObjDispDObj_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,fVar2,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80253a34  zz_0253a34_ ====

void zz_0253a34_(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  DAT_80435f18 = param_1;
  uRam80435f19 = param_2;
  uRam80435f1a = param_3;
  uRam80435f1b = param_4;
  return;
}



// ==== 80253a4c  zz_0253a4c_ ====

void zz_0253a4c_(void)

{
  DAT_804369a4 = 0;
  DAT_80435f1c = &DAT_804369a4;
  DAT_804369a8 = 0;
  DAT_80435f20 = &DAT_804369a8;
  DAT_804369ac = 0;
  DAT_804369b0 = 0;
  DAT_80435f24 = &DAT_804369b0;
  DAT_804369b4 = 0;
  return;
}



// ==== 80253a80  zz_0253a80_ ====

void zz_0253a80_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 extraout_r4;
  undefined8 uVar2;
  double dVar3;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  
  uVar2 = gnt4_DVDInit_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  dVar3 = (double)gnt4_HSD_AllocateXFB_bl
                            (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = gnt4_HSD_AllocateFIFO_bl
                    (dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435f4c,
                     extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  DAT_804369c8 = zz_0224094_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar1,
                             DAT_80435f4c,param_11,param_12,param_13,param_14,param_15,param_16);
  DAT_803f8e70 = DAT_80435f4c;
  uVar2 = gnt4_HSD_OSInit_bl(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  local_58 = *DAT_80435f44;
  local_54 = DAT_80435f44[1];
  local_50 = DAT_80435f44[2];
  local_4c = DAT_80435f44[3];
  local_48 = DAT_80435f44[4];
  local_44 = DAT_80435f44[5];
  local_40 = DAT_80435f44[6];
  local_3c = DAT_80435f44[7];
  local_38 = DAT_80435f44[8];
  local_34 = DAT_80435f44[9];
  local_30 = DAT_80435f44[10];
  local_2c = DAT_80435f44[0xb];
  local_28 = DAT_80435f44[0xc];
  local_24 = DAT_80435f44[0xd];
  local_20 = DAT_80435f44[0xe];
  local_1c = 1;
  local_18 = 1;
  local_14 = 0;
  local_10 = DAT_8043d510;
  local_c = 0xffffff;
  local_8 = 1;
  local_7 = 1;
  local_6 = 1;
  gnt4_HSD_VIInit_bl(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)&local_58,
                     DAT_803f8e58,DAT_803f8e5c,DAT_803f8e60,DAT_8043d510,0,1,local_20);
  gnt4_HSD_GXInit_bl();
  gnt4_HSD_DVDInit();
  gnt4_HSD_IDSetup_bl();
  uVar2 = gnt4_VIWaitForRetrace();
  gnt4_HSD_ObjInit_bl(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  DAT_804369d0 = 1;
  return;
}



// ==== 80253bbc  gnt4-HSD_DVDInit ====

void gnt4_HSD_DVDInit(void)

{
  return;
}



// ==== 80253bc0  gnt4-HSD_AllocateXFB-bl ====

void gnt4_HSD_AllocateXFB_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  double extraout_f1;
  double dVar9;
  longlong lVar10;
  
  lVar10 = gnt4__savegpr_26_bl();
  iVar1 = (int)((ulonglong)lVar10 >> 0x20);
  iVar2 = (int)lVar10;
  if (iVar2 != 0) {
    uVar5 = *(ushort *)(iVar2 + 4) + 0xf;
    puVar7 = &DAT_803f8e58;
    uVar4 = 0x80400000;
    iVar2 = (uVar5 & 0xfff0) * (uint)*(ushort *)(iVar2 + 8) * 2;
    DAT_803f8e6c = iVar2 * iVar1;
    dVar9 = extraout_f1;
    for (iVar6 = 0; iVar6 < iVar1; iVar6 = iVar6 + 1) {
      uVar8 = gnt4_OSAllocFromArenaLo_bl(iVar2,0x20);
      *puVar7 = uVar8;
      if (uVar8 == 0) {
        dVar9 = (double)gnt4_HSD_Panic_bl(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,s_initialize_c_803ad010,0xf0,
                                          s_No_memory_space_remains_for_XFB__803ad020,uVar4,uVar5,
                                          in_r8,in_r9,in_r10);
      }
      puVar7 = puVar7 + 1;
    }
    uVar5 = 3 - iVar1;
    puVar3 = &DAT_803f8e58 + iVar1;
    if (lVar10 < 0x300000000) {
      uVar8 = uVar5 >> 3;
      if (uVar8 != 0) {
        do {
          *puVar3 = 0;
          puVar3[1] = 0;
          puVar3[2] = 0;
          puVar3[3] = 0;
          puVar3[4] = 0;
          puVar3[5] = 0;
          puVar3[6] = 0;
          puVar3[7] = 0;
          puVar3 = puVar3 + 8;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
        uVar5 = uVar5 & 7;
        if (uVar5 == 0) goto LAB_80253cdc;
      }
      do {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
  }
LAB_80253cdc:
  gnt4__restgpr_26_bl();
  return;
}



// ==== 80253cf4  gnt4-HSD_AllocateFIFO-bl ====

uint gnt4_HSD_AllocateFIFO_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  
  uVar1 = gnt4_OSAllocFromArenaLo_bl(param_9,0x20);
  if (uVar1 == 0) {
    gnt4_HSD_Panic_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      s_initialize_c_803ad010,0x103,s_no_space_remains_for_gx_fifo__803ad044,
                      param_12,param_13,param_14,param_15,param_16);
  }
  return uVar1;
}



// ==== 80253d44  gnt4-HSD_GXInit-bl ====

void gnt4_HSD_GXInit_bl(void)

{
  undefined4 uVar1;
  int iVar2;
  double dVar3;
  undefined4 local_58;
  undefined1 auStack_54 [80];
  
  gnt4_GXInitLightPos_bl
            ((double)FLOAT_8043d368,(double)FLOAT_8043d36c,(double)FLOAT_8043d36c,(int)auStack_54);
  gnt4_GXInitLightDir_bl
            ((double)FLOAT_8043d368,(double)FLOAT_8043d36c,(double)FLOAT_8043d36c,(int)auStack_54);
  dVar3 = (double)FLOAT_8043d36c;
  gnt4_GXInitLightAttn_bl
            ((double)FLOAT_8043d368,dVar3,dVar3,(double)FLOAT_8043d368,dVar3,dVar3,(int)auStack_54);
  local_58 = DAT_80435f54;
  gnt4_GXInitLightColor_bl((int)auStack_54,&local_58);
  iVar2 = 0;
  do {
    uVar1 = gnt4_HSD_Index2LightID_bl(iVar2);
    gnt4_GXLoadLightObjImm_bl((int)auStack_54,uVar1);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 8);
  gnt4_HSD_StateInvalidate_bl(0xffffffff);
  return;
}



// ==== 80253df0  gnt4-HSD_OSInit-bl ====

void gnt4_HSD_OSInit_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                       double param_5,double param_6,double param_7,double param_8)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  code *local_28;
  code *local_24;
  code *local_20;
  code *local_1c;
  code *local_18;
  
  gnt4_OSGetArenaLo_bl();
  gnt4_OSGetArenaHi_bl();
  DAT_803f8e64 = gnt4_OSGetPhysicalMemSize_bl();
  iVar3 = gnt4_OSGetArenaLo_bl();
  iVar4 = gnt4_OSGetArenaHi_bl();
  DAT_803f8e68 = (((DAT_803f8e64 - iVar4) + iVar3) - DAT_803f8e6c) - DAT_803f8e70;
  if (DAT_804369d8 == 0) {
    local_28 = gnt4__HSD_MemAllocDefaultCB_bl;
    local_24 = gnt4__HSD_MemFreeDefaultCB_bl;
    local_1c = gnt4__HSD_MemGetRemainDefaultCB_bl;
    local_20 = gnt4__HSD_MemClearDefaultCB_bl;
    local_18 = gnt4__HSD_MemCheckOwnDefaultCB_bl;
    gnt4__HSD_MemSetCallbacks_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_28,0x14,
               gnt4__HSD_MemClearDefaultCB_bl,gnt4__HSD_MemGetRemainDefaultCB_bl,
               gnt4__HSD_MemFreeDefaultCB_bl,gnt4__HSD_MemAllocDefaultCB_bl,in_r9,in_r10);
    uVar2 = DAT_804369c4;
    uVar1 = DAT_804369c0;
    if ((DAT_804369c0 == 0) || (DAT_804369c4 == 0)) {
      iVar3 = gnt4_OSGetArenaLo_bl();
      uVar1 = iVar3 + 0x1fU & 0xffffffe0;
      uVar5 = gnt4_OSGetArenaHi_bl();
      uVar2 = uVar5;
      if ((0 < DAT_804369d4) && (uVar2 = uVar1 + DAT_804369d4, uVar5 < uVar1 + DAT_804369d4)) {
        uVar2 = uVar5;
      }
      DAT_804369bc = uVar2 & 0xffffffe0;
      DAT_804369b8 = uVar1;
      DAT_80435f40 = gnt4_OSCreateHeap_bl(uVar1,DAT_804369bc);
      gnt4_OSSetCurrentHeap_bl(DAT_80435f40);
      DAT_803f8e74 = DAT_804369bc - DAT_804369b8;
      gnt4_HSD_ObjSetHeap(DAT_803f8e74,0);
      gnt4_OSSetArenaLo_bl(DAT_804369bc);
    }
    else {
      DAT_804369b8 = DAT_804369c0;
      DAT_804369bc = DAT_804369c4;
      DAT_804369c0 = 0;
      DAT_804369c4 = 0;
      DAT_80435f40 = gnt4_OSCreateHeap_bl(uVar1,uVar2);
      gnt4_OSSetCurrentHeap_bl(DAT_80435f40);
      DAT_803f8e74 = DAT_804369bc - DAT_804369b8;
      gnt4_HSD_ObjSetHeap(DAT_803f8e74,0);
    }
  }
  return;
}



// ==== 80253f94  gnt4-_HSD_MemAllocDefaultCB-bl ====

int * gnt4__HSD_MemAllocDefaultCB_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  
  if (param_9 == 0) {
    piVar1 = (int *)0x0;
  }
  else {
    iVar2 = gnt4_HSD_GetHeap_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    piVar1 = gnt4_OSAllocFromHeap_bl(iVar2,param_9);
    if (piVar1 == (int *)0x0) {
      gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_initialize_c_803ad010,0x179,&DAT_80435f58,param_12,param_13,param_14,
                       param_15,param_16);
    }
  }
  return piVar1;
}



// ==== 80253ff4  gnt4-_HSD_MemFreeDefaultCB-bl ====

void gnt4__HSD_MemFreeDefaultCB_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  
  iVar1 = gnt4_HSD_GetHeap_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  gnt4_OSFreeToHeap_bl(iVar1,param_9);
  return;
}



// ==== 80254028  gnt4-_HSD_MemGetRemainDefaultCB-bl ====

void gnt4__HSD_MemGetRemainDefaultCB_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               int param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = gnt4_HSD_GetHeap_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  gnt4_OSCheckHeap_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,param_10
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8025404c  gnt4-_HSD_MemClearDefaultCB-bl ====

void gnt4__HSD_MemClearDefaultCB_bl(void)

{
  gnt4_OSDestroyHeap_bl(DAT_80435f40);
  if ((DAT_804369c0 != 0) && (DAT_804369c4 != 0)) {
    DAT_804369b8 = DAT_804369c0;
    DAT_804369bc = DAT_804369c4;
    DAT_804369c0 = 0;
    DAT_804369c4 = 0;
  }
  DAT_80435f40 = gnt4_OSCreateHeap_bl(DAT_804369b8,DAT_804369bc);
  gnt4_OSSetCurrentHeap_bl(DAT_80435f40);
  return;
}



// ==== 802540b0  gnt4-_HSD_MemCheckOwnDefaultCB-bl ====

undefined4 gnt4__HSD_MemCheckOwnDefaultCB_bl(uint param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((DAT_804369b8 <= param_1) && (param_1 < DAT_804369bc)) {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 802540d8  gnt4-HSD_GetHeap-bl ====

undefined4
gnt4_HSD_GetHeap_bl(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                   double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  if (DAT_804369d8 != 0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_initialize_c_803ad010,0x1b5,s__iparam_memory_callbacks_803ad064,in_r6,in_r7,
                     in_r8,in_r9,in_r10);
  }
  return DAT_80435f40;
}



// ==== 8025411c  zz_025411c_ ====

void zz_025411c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  undefined **ppuVar1;
  undefined8 uVar2;
  undefined *local_28 [4];
  undefined *local_18;
  undefined *local_14;
  undefined4 local_10;
  
  local_28[0] = PTR_zz_0243ff0__802b5250;
  local_28[1] = PTR_zz_0253a4c__802b5254;
  local_28[2] = PTR_zz_02598c4__802b5258;
  local_28[3] = PTR_LAB_802b525c;
  local_18 = PTR_zz_025b388__802b5260;
  local_14 = PTR_zz_025960c__802b5264;
  local_10 = DAT_802b5268;
  uVar2 = zz_025d460_(s_sysdolphin_base_library_803ad080);
  for (ppuVar1 = local_28; (code *)*ppuVar1 != (code *)0x0; ppuVar1 = ppuVar1 + 1) {
    uVar2 = (*(code *)*ppuVar1)();
  }
  gnt4_HSD_ObjInit_bl(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_025af14_();
  DAT_803f8e74 = gnt4__HSD_MemGetRemain_bl();
  return;
}



// ==== 802541c4  gnt4-HSD_SetCurrentRenderPass-bl ====

undefined4 gnt4_HSD_SetCurrentRenderPass_bl(void)

{
  return DAT_804369e0;
}



// ==== 802541cc  gnt4-HSD_StartRender-bl ====

void gnt4_HSD_StartRender_bl(undefined4 param_1)

{
  DAT_804369e0 = param_1;
  if (DAT_803f8e99 == '\0') {
    gnt4_GXSetPixelFmt_bl(DAT_804369cc,0);
  }
  else {
    gnt4_GXSetPixelFmt_bl(2,DAT_80435f48);
  }
  gnt4_GXSetFieldMode_bl((uint)DAT_803f8e98,(uint)DAT_803f8e88 - (uint)DAT_803f8e90 >> 0x1f);
  if (DAT_804369dc != 0) {
    if ((DAT_804369dc & 1) != 0) {
      gnt4_GXInvalidateVtxCache_bl();
    }
    if ((DAT_804369dc & 2) != 0) {
      gnt4_GXInvalidateTexAll_bl();
    }
    DAT_804369dc = 0;
  }
  return;
}



// ==== 8025426c  zz_025426c_ ====

void zz_025426c_(void)

{
  return;
}



// ==== 80254278  gnt4-_HSD_NeedCacheInvalidate-bl ====

void gnt4__HSD_NeedCacheInvalidate_bl(uint param_1)

{
  DAT_804369dc = DAT_804369dc | param_1;
  return;
}



// ==== 80254288  gnt4-HSD_ObjInit-bl ====

void gnt4_HSD_ObjInit_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8)

{
  undefined8 uVar1;
  
  uVar1 = gnt4_HSD_ListInitAllocData_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = gnt4_HSD_AObjInitAllocData(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = gnt4_HSD_FObjInitAllocData(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = gnt4_HSD_IDInitAllocData_bl(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8)
  ;
  uVar1 = gnt4_HSD_VecInitAllocData_bl
                    (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = gnt4_HSD_MtxInitAllocData_bl
                    (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = gnt4_HSD_RObjInitAllocData_bl
                    (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = gnt4_HSD_RenderInitAllocData_bl
                    (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = gnt4_HSD_ShadowInitAllocData_bl
                    (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  gnt4_HSD_ZListInitAllocData_bl(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 802542cc  gnt4-HSD_VISetUserPostRetraceCallback-bl ====

undefined4 gnt4_HSD_VISetUserPostRetraceCallback_bl(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_803f905c;
  gnt4_OSDisableInterrupts_bl();
  DAT_803f905c = param_1;
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 80254320  gnt4-HSD_VIPreRetraceCB-bl ====

void gnt4_HSD_VIPreRetraceCB_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  undefined4 extraout_r4;
  int iVar3;
  undefined8 uVar4;
  
  iVar3 = 0;
  bVar1 = false;
  if (DAT_803f8edc == 6) {
    iVar2 = 0;
  }
  else if (DAT_803f8f3c == 6) {
    iVar2 = 1;
  }
  else if (DAT_803f8f9c == 6) {
    iVar2 = 2;
  }
  else {
    iVar2 = -1;
  }
  if (iVar2 == -1) {
    if ((DAT_803f9054 == 1) && (DAT_803f8ff8 == 1)) {
      if (DAT_803f8edc == 7) {
        iVar2 = 0;
      }
      else if (DAT_803f8f3c == 7) {
        iVar2 = 1;
      }
      else if (DAT_803f8f9c == 7) {
        iVar2 = 2;
      }
      else {
        iVar2 = -1;
      }
      if (iVar2 == -1) {
        if (DAT_803f8edc == 2) {
          iVar2 = 0;
        }
        else if (DAT_803f8f3c == 2) {
          iVar2 = 1;
        }
        else if (DAT_803f8f9c == 2) {
          iVar2 = 2;
        }
        else {
          iVar2 = -1;
        }
        if (iVar2 == -1) {
          gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80435f60,0xfc,s_idx_____1_803ad098,0,param_13,param_14,param_15,
                           param_16);
        }
        param_1 = gnt4_VISetNextFrameBuffer((&DAT_803f8ed8)[iVar2 * 0x18]);
        iVar3 = 1;
      }
      (&DAT_803f8edc)[iVar2 * 0x18] = 8;
      if (DAT_803f9050 != '\0') {
        gnt4_VIConfigure_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            &DAT_803f8ffc,&DAT_803f8e80,8,iVar3,param_13,param_14,param_15,param_16)
        ;
        gnt4_VISetBlack(DAT_803f9038);
        iVar3 = 1;
      }
      bVar1 = true;
    }
  }
  else {
    uVar4 = gnt4_VISetNextFrameBuffer((&DAT_803f8ed8)[iVar2 * 0x18]);
    if ((&DAT_803f8f34)[iVar2 * 0x60] != '\0') {
      gnt4_VIConfigure_bl(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803f8ee0 + iVar2 * 0x18,extraout_r4,param_11,iVar3,param_13,param_14,
                          param_15,param_16);
      gnt4_VISetBlack((&DAT_803f8f1c)[iVar2 * 0x18]);
    }
    iVar3 = 1;
    bVar1 = true;
  }
  if (iVar3 != 0) {
    gnt4_VIFlush_bl();
  }
  if (bVar1) {
    DAT_804369ec = DAT_804369ec + 1;
  }
  DAT_804369e8 = DAT_804369e8 + 1;
  if (DAT_803f906c <= DAT_804369e8) {
    DAT_804369e8 = 0;
    DAT_803f9070 = DAT_804369ec;
    DAT_804369ec = 0;
  }
  if (DAT_803f9058 != (code *)0x0) {
    (*DAT_803f9058)(param_9);
  }
  return;
}



// ==== 80254590  gnt4-HSD_VIPostRetraceCB-bl ====

void gnt4_HSD_VIPostRetraceCB_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9)

{
  int iVar1;
  int iVar2;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  if (DAT_803f8edc == 6) {
    iVar2 = 0;
  }
  else if (DAT_803f8f3c == 6) {
    iVar2 = 1;
  }
  else if (DAT_803f8f9c == 6) {
    iVar2 = 2;
  }
  else {
    iVar2 = -1;
  }
  if (iVar2 == -1) {
    if (DAT_803f8edc == 8) {
      iVar2 = 0;
    }
    else if (DAT_803f8f3c == 8) {
      iVar2 = 1;
    }
    else if (DAT_803f8f9c == 8) {
      iVar2 = 2;
    }
    else {
      iVar2 = -1;
    }
    if (iVar2 != -1) {
      gnt4_HSD_VICopyEFB2XFBPtr_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc07004,
                 (&DAT_803f8ed8)[iVar2 * 0x18],0,&DAT_803f8e80,0xffffffff,in_r8,in_r9,in_r10);
      (&DAT_803f8edc)[iVar2 * 0x18] = 7;
      DAT_803f8ff8 = 0;
    }
  }
  else {
    if (DAT_803f8edc == 7) {
      iVar1 = 0;
    }
    else if (DAT_803f8f3c == 7) {
      iVar1 = 1;
    }
    else if (DAT_803f8f9c == 7) {
      iVar1 = 2;
    }
    else {
      iVar1 = -1;
    }
    if (iVar1 != -1) {
      (&DAT_803f8edc)[iVar1 * 0x18] = 2;
    }
    (&DAT_803f8edc)[iVar2 * 0x18] = 7;
    if (DAT_803f8edc == 5) {
      iVar2 = 0;
    }
    else if (DAT_803f8f3c == 5) {
      iVar2 = 1;
    }
    else if (DAT_803f8f9c == 5) {
      iVar2 = 2;
    }
    else {
      iVar2 = -1;
    }
    if (iVar2 != -1) {
      (&DAT_803f8edc)[iVar2 * 0x18] = 6;
    }
  }
  if (DAT_803f905c != (code *)0x0) {
    (*DAT_803f905c)(param_9);
  }
  return;
}



// ==== 8025479c  gnt4-HSD_VIGXDrawDoneCB-bl ====

void gnt4_HSD_VIGXDrawDoneCB_bl(void)

{
  DAT_803f9060 = 0;
  if (DAT_803f9068 != (code *)0x0) {
    (*DAT_803f9068)(DAT_803f9064);
  }
  return;
}



// ==== 802547e0  gnt4-HSD_VIGetDrawDoneWaitingFlag-bl ====

undefined4 gnt4_HSD_VIGetDrawDoneWaitingFlag_bl(void)

{
  return DAT_803f9060;
}



// ==== 802547f0  gnt4-HSD_VICopyEFB2XFBPtr-bl ====

void gnt4_HSD_VICopyEFB2XFBPtr_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,uint param_10,int param_11,
               undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  uint uVar1;
  byte *pbVar2;
  double dVar3;
  undefined4 local_28 [2];
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  pbVar2 = (byte *)(param_9 + 0x32);
  gnt4_GXSetCopyFilter_bl
            (*(char *)(param_9 + 0x19),(byte *)(param_9 + 0x1a),*(char *)(param_9 + 0x40),pbVar2);
  gnt4_GXSetDispCopyGamma_bl(*(uint *)(param_9 + 0x44));
  gnt4_HSD_StateSetColorUpdate_bl((uint)*(byte *)(param_9 + 0x50));
  gnt4_HSD_StateSetAlphaUpdate_bl((uint)*(byte *)(param_9 + 0x51));
  gnt4_HSD_StateSetZMode_bl((uint)*(byte *)(param_9 + 0x52),3,1);
  local_28[0] = *(undefined4 *)(param_9 + 0x48);
  dVar3 = (double)gnt4_GXSetCopyClear_bl((undefined1 *)local_28,*(uint *)(param_9 + 0x4c));
  if (param_11 == 1) {
    gnt4_GXSetDispCopySrc_bl
              (0,0,(uint)*(ushort *)(param_9 + 4),*(ushort *)(param_9 + 6) - 4 & 0xffff);
    gnt4_GXSetDispCopyYScale_bl((double)FLOAT_8043d370);
    gnt4_GXSetDispCopyDst_bl((uint)*(ushort *)(param_9 + 4));
    gnt4_GXSetCopyClamp_bl(1);
    gnt4_GXSetDispCopySrc_bl
              (0,0,(uint)*(ushort *)(param_9 + 4),*(ushort *)(param_9 + 6) - 4 & 0xffff);
    gnt4_GXCopyDisp_bl(param_10,1);
    gnt4_GXPixModeSync_bl();
    return;
  }
  if (param_11 < 1) {
    if (-1 < param_11) {
      gnt4_GXSetCopyClamp_bl(3);
      gnt4_GXSetDispCopySrc_bl(0,0,(uint)*(ushort *)(param_9 + 4),(uint)*(ushort *)(param_9 + 6));
      uStack_1c = (uint)*(ushort *)(param_9 + 8);
      uStack_14 = (uint)*(ushort *)(param_9 + 6);
      local_20 = 0x43300000;
      local_18 = 0x43300000;
      gnt4_GXSetDispCopyYScale_bl
                ((double)((float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043d378) /
                         (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8043d378)));
      gnt4_GXSetDispCopyDst_bl((uint)*(ushort *)(param_9 + 4));
      gnt4_GXCopyDisp_bl(param_10,1);
      goto LAB_80254a28;
    }
  }
  else if (param_11 < 3) {
    gnt4_GXSetDispCopySrc_bl
              (0,0,(uint)*(ushort *)(param_9 + 4),*(ushort *)(param_9 + 6) - 4 & 0xffff);
    gnt4_GXSetDispCopyYScale_bl((double)FLOAT_8043d370);
    gnt4_GXSetDispCopyDst_bl((uint)*(ushort *)(param_9 + 4));
    gnt4_GXSetCopyClamp_bl(2);
    uVar1 = *(ushort *)(param_9 + 6) - 4 & 0xffff;
    gnt4_GXSetDispCopySrc_bl(0,4,(uint)*(ushort *)(param_9 + 4),uVar1);
    gnt4_GXCopyDisp_bl(param_10 + (*(ushort *)(param_9 + 4) + 0xf & 0xfff0) * uVar1 * 2,1);
    gnt4_GXSetDispCopySrc_bl(0,0,(uint)*(ushort *)(param_9 + 4),4);
    gnt4_GXSetCopyClamp_bl(3);
    gnt4_GXCopyDisp_bl(0x803f9080,1);
    goto LAB_80254a28;
  }
  gnt4_HSD_Panic_bl(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435f60,
                    0x207,s_unexpected_type_of_render_pass__803ad0a4,pbVar2,param_13,param_14,
                    param_15,param_16);
LAB_80254a28:
  gnt4_GXPixModeSync_bl();
  return;
}



// ==== 80254a48  gnt4-HSD_VICopyXFBASync-bl ====

void gnt4_HSD_VICopyXFBASync_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  if (1 < DAT_803f9054) {
    while( true ) {
      iVar2 = -1;
      if (1 < DAT_803f9054) {
        gnt4_OSDisableInterrupts_bl();
        if (DAT_803f8edc == 3) {
          iVar2 = 0;
        }
        else if (DAT_803f8f3c == 3) {
          iVar2 = 1;
        }
        else if (DAT_803f8f9c == 3) {
          iVar2 = 2;
        }
        else {
          iVar2 = -1;
        }
        if (iVar2 == -1) {
          if (DAT_803f8edc == 2) {
            iVar2 = 0;
          }
          else if (DAT_803f8f3c == 2) {
            iVar2 = 1;
          }
          else if (DAT_803f8f9c == 2) {
            iVar2 = 2;
          }
          else {
            iVar2 = -1;
          }
          if (iVar2 != -1) {
            param_12 = 3;
            (&DAT_803f8edc)[iVar2 * 0x18] = 3;
          }
        }
        gnt4_OSRestoreInterrupts_bl();
      }
      if (iVar2 != -1) break;
      param_1 = gnt4_VIWaitForRetrace();
    }
    gnt4_HSD_VICopyEFB2XFBPtr_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc07180,
               (&DAT_803f8ed8)[iVar2 * 0x18],param_9,param_12,param_13,param_14,param_15,param_16);
    while (iVar1 = gnt4_HSD_VIGetDrawDoneWaitingFlag_bl(), iVar1 != 0) {
      gnt4_GXWaitDrawDone_bl();
    }
    DAT_803f9060 = 1;
    DAT_803f9064 = iVar2;
    gnt4_GXDrawDone_bl();
  }
  return;
}



// ==== 80254bc4  gnt4-HSD_VISetXFBDrawDone-bl ====

void gnt4_HSD_VISetXFBDrawDone_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int *piVar7;
  undefined8 uVar8;
  
  uVar8 = gnt4__savegpr_26_bl();
  if (1 < DAT_803f9054) {
    gnt4_OSDisableInterrupts_bl();
    if (DAT_803f8edc == 3) {
      iVar6 = 0;
    }
    else if (DAT_803f8f3c == 3) {
      iVar6 = 1;
    }
    else if (DAT_803f8f9c == 3) {
      iVar6 = 2;
    }
    else {
      iVar6 = -1;
    }
    if (iVar6 == -1) {
      uVar8 = gnt4___assert_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435f60,0x2fb,s_idx_____1_803ad098,in_r6,in_r7,in_r8,in_r9,
                               in_r10);
    }
    gnt4_OSDisableInterrupts_bl();
    piVar7 = &DAT_803f8edc + iVar6 * 0x18;
    if ((&DAT_803f8edc)[iVar6 * 0x18] != 3) {
      uVar8 = gnt4___assert_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435f60,0x24e,s__p_>xfb_idx__status____HSD_VI_XF_803ad0c8,in_r6
                               ,in_r7,in_r8,in_r9,in_r10);
    }
    *piVar7 = 4;
    puVar5 = &DAT_803f8edc + iVar6 * 0x18;
    puVar4 = &DAT_803f8e7c;
    iVar6 = 0xb;
    do {
      puVar1 = puVar4 + 1;
      puVar4 = puVar4 + 2;
      uVar2 = *puVar4;
      puVar5[1] = *puVar1;
      puVar5 = puVar5 + 2;
      *puVar5 = uVar2;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    DAT_803f8ed4 = 0;
    gnt4_OSRestoreInterrupts_bl();
    gnt4_OSDisableInterrupts_bl();
    if (*piVar7 != 4) {
      gnt4___assert_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435f60,
                       0x2d2,s__p_>xfb_idx__status____HSD_VI_XF_803ad0f4,in_r6,in_r7,in_r8,in_r9,
                       in_r10);
    }
    if (DAT_803f8edc == 6) {
      iVar6 = 0;
    }
    else if (DAT_803f8f3c == 6) {
      iVar6 = 1;
    }
    else if (DAT_803f8f9c == 6) {
      iVar6 = 2;
    }
    else {
      iVar6 = -1;
    }
    iVar3 = 6;
    if (iVar6 != -1) {
      iVar3 = 5;
    }
    *piVar7 = iVar3;
    gnt4_OSRestoreInterrupts_bl();
    gnt4_OSRestoreInterrupts_bl();
  }
  gnt4__restgpr_26_bl();
  return;
}



// ==== 80254d88  gnt4-HSD_VISetConfigure-bl ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void gnt4_HSD_VISetConfigure_bl(undefined4 *param_1)

{
  DAT_803f8e80 = *param_1;
  DAT_803f8e84 = param_1[1];
  _DAT_803f8e88 = param_1[2];
  DAT_803f8e8c = param_1[3];
  _DAT_803f8e90 = param_1[4];
  DAT_803f8e94 = param_1[5];
  _DAT_803f8e98 = param_1[6];
  DAT_803f8e9c = param_1[7];
  DAT_803f8ea0 = param_1[8];
  DAT_803f8ea4 = param_1[9];
  DAT_803f8ea8 = param_1[10];
  DAT_803f8eac = param_1[0xb];
  DAT_803f8eb0 = param_1[0xc];
  DAT_803f8eb4 = param_1[0xd];
  DAT_803f8eb8 = param_1[0xe];
  DAT_803f8ed4 = 1;
  return;
}



// ==== 80254e10  gnt4-HSD_VISetBlack-bl ====

void gnt4_HSD_VISetBlack_bl(undefined4 param_1)

{
  DAT_803f8ebc = param_1;
  DAT_803f8ed4 = 1;
  return;
}



// ==== 80254e28  gnt4-HSD_VIInit-bl ====

void gnt4_HSD_VIInit_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                       double param_5,double param_6,double param_7,double param_8,int param_9,
                       undefined4 param_10,undefined4 param_11,undefined4 param_12,
                       undefined4 param_13,undefined4 param_14,undefined4 param_15,
                       undefined4 param_16)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  undefined8 uVar11;
  
  uVar11 = gnt4_VIInit_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  iVar9 = 10;
  puVar8 = (undefined4 *)(param_9 + -4);
  puVar5 = &DAT_803f8e7c;
  do {
    puVar4 = puVar5;
    puVar7 = puVar8;
    uVar2 = puVar7[2];
    puVar4[1] = puVar7[1];
    puVar4[2] = uVar2;
    iVar9 = iVar9 + -1;
    puVar8 = puVar7 + 2;
    puVar5 = puVar4 + 2;
  } while (iVar9 != 0);
  puVar8 = &DAT_803f8e80;
  uVar2 = 0;
  puVar4[3] = puVar7[3];
  iVar9 = 0;
  DAT_803f9054 = 0;
  DAT_803f8ed4 = 0;
  DAT_803f8ed8 = param_10;
  DAT_803f8f38 = param_11;
  DAT_803f8f98 = param_12;
  do {
    puVar7 = puVar8 + 0x17;
    puVar5 = &DAT_803f8e7c;
    iVar10 = 0xb;
    do {
      puVar4 = puVar5 + 1;
      puVar5 = puVar5 + 2;
      uVar3 = *puVar5;
      puVar7[1] = *puVar4;
      puVar7 = puVar7 + 2;
      *puVar7 = uVar3;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    if (puVar8[0x16] == 0) {
      puVar8[0x17] = 0;
    }
    else {
      puVar8[0x17] = 2;
      DAT_803f9054 = DAT_803f9054 + 1;
    }
    iVar9 = iVar9 + 1;
    puVar8 = puVar8 + 0x18;
  } while (iVar9 < 3);
  puVar6 = &DAT_803f8e80;
  puVar4 = &DAT_803f8ff8;
  puVar5 = &DAT_803f8e7c;
  DAT_803f8ff8 = 0;
  iVar10 = 0xb;
  do {
    puVar1 = puVar5 + 1;
    puVar5 = puVar5 + 2;
    uVar3 = *puVar5;
    puVar4[1] = *puVar1;
    puVar4 = puVar4 + 2;
    *puVar4 = uVar3;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  gnt4_VISetPreRetraceCallback(gnt4_HSD_VIPreRetraceCB_bl);
  gnt4_VISetPostRetraceCallback(gnt4_HSD_VIPostRetraceCB_bl);
  DAT_803f9058 = 0;
  DAT_803f905c = 0;
  DAT_803f9060 = 0;
  DAT_803f9064 = 0;
  gnt4_GXSetDrawDoneCallback_bl(gnt4_HSD_VIGXDrawDoneCB_bl);
  DAT_803f9068 = 0;
  iVar10 = gnt4_VIGetTvFormat();
  DAT_803f906c = 0x32;
  if (iVar10 == 0) {
    DAT_803f906c = 0x3c;
  }
  DAT_803f9070 = 0;
  gnt4_VIConfigure_bl(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803f8e80,
                      DAT_803f906c,puVar4,puVar6,puVar7,uVar2,puVar8,iVar9);
  gnt4_VISetBlack(DAT_803f8ebc);
  uVar11 = gnt4_VIFlush_bl();
  if (DAT_803f8edc == 2) {
    iVar10 = 0;
  }
  else if (DAT_803f8f3c == 2) {
    iVar10 = 1;
  }
  else if (DAT_803f8f9c == 2) {
    iVar10 = 2;
  }
  else {
    iVar10 = -1;
  }
  gnt4_HSD_VICopyEFB2XFBPtr_bl
            (uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc07180,
             (&DAT_803f8ed8)[iVar10 * 0x18],0,puVar6,puVar7,uVar2,puVar8,iVar9);
  return;
}



// ==== 80255050  gnt4-splGetHelmite-bl ====

double gnt4_splGetHelmite_bl
                 (double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6)

{
  float fVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  
  dVar5 = (double)(float)(param_2 * param_2);
  dVar3 = (double)((float)(param_1 * param_1) * (float)(dVar5 * param_2));
  fVar2 = (float)((double)FLOAT_8043d384 * dVar5) * (float)(param_1 * param_1);
  dVar4 = (double)(float)(dVar3 - (double)(float)(dVar5 * param_1));
  fVar1 = (float)((double)(float)((double)FLOAT_8043d380 * dVar3) * param_1);
  return (double)(float)(param_6 * dVar4 +
                        (double)(float)(param_5 * (double)(float)(param_2 +
                                                                 (double)(float)(dVar4 - (double)(
                                                  float)(dVar5 * param_1))) +
                                       (double)(float)(param_3 * (double)(FLOAT_8043d388 +
                                                                         (fVar1 - fVar2)) +
                                                      (double)(float)(param_4 *
                                                                     (double)(-fVar1 + fVar2)))));
}



// ==== 802550b0  gnt4-splGetSplinePoint-bl ====

/* WARNING: Removing unreachable block (ram,0x80255530) */
/* WARNING: Removing unreachable block (ram,0x8025540c) */
/* WARNING: Removing unreachable block (ram,0x802550b8) */
/* WARNING: Removing unreachable block (ram,0x80255148) */

void gnt4_splGetSplinePoint_bl(double param_1,float *param_2,byte *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  byte bVar4;
  float fVar5;
  float *pfVar6;
  int iVar7;
  uint uVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  
  fVar5 = FLOAT_8043d38c;
  dVar10 = (double)FLOAT_8043d398;
  if (dVar10 <= param_1) {
    dVar9 = (double)FLOAT_8043d388;
    if (param_1 <= dVar9) {
      if (dVar9 <= param_1) {
        bVar4 = *param_3;
        iVar7 = (int)(short)(*(short *)(param_3 + 2) + -1);
        if (bVar4 == 2) {
          pfVar6 = (float *)(*(int *)(param_3 + 8) + iVar7 * 0xc + -0xc);
          fVar3 = FLOAT_8043d38c *
                  (float)((double)FLOAT_8043d384 *
                          (double)(float)(dVar9 + (double)(float)(-dVar9 + dVar9)) + dVar9);
          *param_2 = pfVar6[9] * FLOAT_8043d38c +
                     pfVar6[6] * fVar3 +
                     (float)((double)*pfVar6 * dVar10 + (double)(pfVar6[3] * FLOAT_8043d38c));
          param_2[1] = pfVar6[10] * fVar5 +
                       pfVar6[7] * fVar3 +
                       (float)((double)pfVar6[1] * dVar10 + (double)(pfVar6[4] * fVar5));
          param_2[2] = pfVar6[0xb] * fVar5 +
                       pfVar6[8] * fVar3 +
                       (float)((double)pfVar6[2] * dVar10 + (double)(pfVar6[5] * fVar5));
        }
        else if (bVar4 < 2) {
          if (bVar4 == 0) {
            pfVar6 = (float *)(*(int *)(param_3 + 8) + iVar7 * 0xc);
            fVar5 = pfVar6[1];
            *param_2 = *pfVar6;
            param_2[1] = fVar5;
            param_2[2] = pfVar6[2];
          }
          else {
            pfVar6 = (float *)(*(int *)(param_3 + 8) + iVar7 * 0x24);
            fVar5 = pfVar6[1];
            *param_2 = *pfVar6;
            param_2[1] = fVar5;
            param_2[2] = pfVar6[2];
          }
        }
        else if (bVar4 < 4) {
          pfVar6 = (float *)(*(int *)(param_3 + 8) + iVar7 * 0xc + 0xc);
          fVar5 = pfVar6[1];
          *param_2 = *pfVar6;
          param_2[1] = fVar5;
          param_2[2] = pfVar6[2];
        }
      }
      else {
        bVar4 = *param_3;
        dVar10 = param_1 * (double)(float)((double)CONCAT44(0x43300000,
                                                            (int)*(short *)(param_3 + 2) - 1U ^
                                                            0x80000000) - DOUBLE_8043d3a0);
        uVar8 = (uint)(short)(int)dVar10;
        dVar10 = (double)((float)dVar10 -
                         (float)((double)CONCAT44(0x43300000,uVar8 ^ 0x80000000) - DOUBLE_8043d3a0))
        ;
        if (bVar4 == 2) {
          dVar14 = (double)(float)(dVar10 * dVar10);
          dVar12 = (double)(float)(dVar9 - dVar10);
          dVar11 = (double)FLOAT_8043d38c;
          dVar13 = (double)(float)(dVar14 * dVar10);
          pfVar6 = (float *)(*(int *)(param_3 + 8) + uVar8 * 0xc);
          fVar5 = (float)(dVar12 * (double)(float)(dVar12 * (double)(float)(dVar11 * dVar12)));
          fVar3 = (float)(dVar11 * (double)(FLOAT_8043d390 +
                                           (float)((double)FLOAT_8043d384 * dVar13 -
                                                  (double)(float)((double)FLOAT_8043d394 * dVar14)))
                         );
          fVar1 = (float)(dVar11 * dVar13);
          fVar2 = (float)(dVar11 * (double)(float)((double)FLOAT_8043d384 *
                                                   (double)(float)(dVar10 + (double)(float)(-dVar13 
                                                  + dVar14)) + dVar9));
          *param_2 = pfVar6[9] * fVar1 + pfVar6[6] * fVar2 + *pfVar6 * fVar5 + pfVar6[3] * fVar3;
          param_2[1] = pfVar6[10] * fVar1 +
                       pfVar6[7] * fVar2 + pfVar6[1] * fVar5 + pfVar6[4] * fVar3;
          param_2[2] = pfVar6[0xb] * fVar1 +
                       pfVar6[8] * fVar2 + pfVar6[2] * fVar5 + pfVar6[5] * fVar3;
        }
        else if (bVar4 < 2) {
          if (bVar4 == 0) {
            pfVar6 = (float *)(*(int *)(param_3 + 8) + uVar8 * 0xc);
            *param_2 = (float)(dVar10 * (double)(float)((double)pfVar6[3] - (double)*pfVar6) +
                              (double)*pfVar6);
            param_2[1] = (float)(dVar10 * (double)(float)((double)pfVar6[4] - (double)pfVar6[1]) +
                                (double)pfVar6[1]);
            param_2[2] = (float)(dVar10 * (double)(float)((double)pfVar6[5] - (double)pfVar6[2]) +
                                (double)pfVar6[2]);
          }
          else {
            fVar3 = (float)(dVar9 - dVar10);
            pfVar6 = (float *)(*(int *)(param_3 + 8) + uVar8 * 0x24);
            fVar5 = (float)((double)(float)(dVar10 * dVar10) * dVar10);
            fVar2 = (float)((double)FLOAT_8043d384 * dVar10) * fVar3 * fVar3;
            fVar1 = fVar3 * fVar3 * fVar3;
            fVar3 = (float)((double)FLOAT_8043d384 * (double)(float)(dVar10 * dVar10)) * fVar3;
            *param_2 = pfVar6[9] * fVar5 + pfVar6[6] * fVar3 + *pfVar6 * fVar1 + pfVar6[3] * fVar2;
            param_2[1] = pfVar6[10] * fVar5 +
                         pfVar6[7] * fVar3 + pfVar6[1] * fVar1 + pfVar6[4] * fVar2;
            param_2[2] = pfVar6[0xb] * fVar5 +
                         pfVar6[8] * fVar3 + pfVar6[2] * fVar1 + pfVar6[5] * fVar2;
          }
        }
        else if (bVar4 < 4) {
          dVar13 = (double)(float)(dVar10 * dVar10);
          dVar14 = (double)*(float *)(param_3 + 4);
          dVar11 = (double)FLOAT_8043d380;
          dVar12 = (double)(float)(dVar13 * dVar10);
          pfVar6 = (float *)(*(int *)(param_3 + 8) + uVar8 * 0xc);
          fVar5 = (float)(dVar9 + (double)(float)((double)(float)(dVar11 - dVar14) * dVar12 +
                                                 (double)(float)((double)(float)(dVar14 - (double)
                                                  FLOAT_8043d384) * dVar13)));
          fVar1 = (float)(dVar14 * (double)(float)((double)(float)(dVar11 * dVar13 + -dVar12) -
                                                  dVar10));
          fVar2 = (float)(dVar14 * (double)(float)(dVar12 - dVar13));
          fVar3 = (float)(dVar14 * dVar10 +
                         (double)(float)((double)(float)(dVar14 - dVar11) * dVar12 +
                                        (double)(float)(-(double)(float)(dVar11 * dVar14 -
                                                                        (double)FLOAT_8043d384) *
                                                       dVar13)));
          *param_2 = pfVar6[9] * fVar2 + pfVar6[6] * fVar3 + *pfVar6 * fVar1 + pfVar6[3] * fVar5;
          param_2[1] = pfVar6[10] * fVar2 +
                       pfVar6[7] * fVar3 + pfVar6[1] * fVar1 + pfVar6[4] * fVar5;
          param_2[2] = pfVar6[0xb] * fVar2 +
                       pfVar6[8] * fVar3 + pfVar6[2] * fVar1 + pfVar6[5] * fVar5;
        }
      }
    }
  }
  return;
}



// ==== 80255540  gnt4-splArcLength-bl ====

double gnt4_splArcLength_bl(double param_1,double param_2,float *param_3)

{
  bool bVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  dVar5 = (double)FLOAT_8043d398;
  bVar1 = false;
  dVar4 = (double)((float)(param_2 - param_1) * FLOAT_8043d3c0);
  iVar2 = 7;
  dVar3 = param_1;
  do {
    dVar3 = (double)(float)(dVar3 + dVar4);
    if (bVar1) {
      dVar7 = (double)(float)((double)(float)(dVar3 * dVar3) * dVar3);
      dVar7 = (double)(param_3[4] +
                      (float)((double)param_3[3] * dVar3 +
                             (double)(float)((double)param_3[2] * (double)(float)(dVar3 * dVar3) +
                                            (double)(*param_3 * (float)(dVar7 * dVar3) +
                                                    (float)((double)param_3[1] * dVar7)))));
      if ((dVar7 < (double)FLOAT_8043d398) && ((double)FLOAT_8043d3a8 < dVar7)) {
        dVar7 = (double)FLOAT_8043d398;
      }
      if ((double)FLOAT_8043d398 < dVar7) {
        dVar6 = 1.0 / SQRT(dVar7);
        dVar6 = DOUBLE_8043d3b0 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_8043d3b8);
        dVar6 = DOUBLE_8043d3b0 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_8043d3b8);
        dVar7 = (double)(float)(dVar7 * DOUBLE_8043d3b0 * dVar6 *
                                        -(dVar7 * dVar6 * dVar6 - DOUBLE_8043d3b8));
      }
      dVar7 = (double)FLOAT_8043d380 * dVar7;
    }
    else {
      dVar7 = (double)(float)((double)(float)(dVar3 * dVar3) * dVar3);
      dVar7 = (double)(param_3[4] +
                      (float)((double)param_3[3] * dVar3 +
                             (double)(float)((double)param_3[2] * (double)(float)(dVar3 * dVar3) +
                                            (double)(*param_3 * (float)(dVar7 * dVar3) +
                                                    (float)((double)param_3[1] * dVar7)))));
      if ((dVar7 < (double)FLOAT_8043d398) && ((double)FLOAT_8043d3a8 < dVar7)) {
        dVar7 = (double)FLOAT_8043d398;
      }
      if ((double)FLOAT_8043d398 < dVar7) {
        dVar6 = 1.0 / SQRT(dVar7);
        dVar6 = DOUBLE_8043d3b0 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_8043d3b8);
        dVar6 = DOUBLE_8043d3b0 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_8043d3b8);
        dVar7 = (double)(float)(dVar7 * DOUBLE_8043d3b0 * dVar6 *
                                        -(dVar7 * dVar6 * dVar6 - DOUBLE_8043d3b8));
      }
      dVar7 = (double)FLOAT_8043d390 * dVar7;
    }
    dVar5 = (double)(float)(dVar7 + dVar5);
    bVar1 = (bool)(bVar1 ^ 1);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  dVar3 = (double)(float)((double)(float)(param_1 * param_1) * param_1);
  dVar3 = (double)(param_3[4] +
                  (float)((double)param_3[3] * param_1 +
                         (double)(float)((double)param_3[2] * (double)(float)(param_1 * param_1) +
                                        (double)(*param_3 * (float)(dVar3 * param_1) +
                                                (float)((double)param_3[1] * dVar3)))));
  if ((dVar3 < (double)FLOAT_8043d398) && ((double)FLOAT_8043d3a8 < dVar3)) {
    dVar3 = (double)FLOAT_8043d398;
  }
  if ((double)FLOAT_8043d398 < dVar3) {
    dVar7 = 1.0 / SQRT(dVar3);
    dVar7 = DOUBLE_8043d3b0 * dVar7 * -(dVar3 * dVar7 * dVar7 - DOUBLE_8043d3b8);
    dVar7 = DOUBLE_8043d3b0 * dVar7 * -(dVar3 * dVar7 * dVar7 - DOUBLE_8043d3b8);
    dVar3 = (double)(float)(dVar3 * DOUBLE_8043d3b0 * dVar7 *
                                    -(dVar3 * dVar7 * dVar7 - DOUBLE_8043d3b8));
  }
  dVar7 = (double)(float)((double)(float)(param_2 * param_2) * param_2);
  dVar7 = (double)(param_3[4] +
                  (float)((double)param_3[3] * param_2 +
                         (double)(float)((double)param_3[2] * (double)(float)(param_2 * param_2) +
                                        (double)(*param_3 * (float)(dVar7 * param_2) +
                                                (float)((double)param_3[1] * dVar7)))));
  if ((dVar7 < (double)FLOAT_8043d398) && ((double)FLOAT_8043d3a8 < dVar7)) {
    dVar7 = (double)FLOAT_8043d398;
  }
  if ((double)FLOAT_8043d398 < dVar7) {
    dVar6 = 1.0 / SQRT(dVar7);
    dVar6 = DOUBLE_8043d3b0 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_8043d3b8);
    dVar6 = DOUBLE_8043d3b0 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_8043d3b8);
    dVar7 = (double)(float)(dVar7 * DOUBLE_8043d3b0 * dVar6 *
                                    -(dVar7 * dVar6 * dVar6 - DOUBLE_8043d3b8));
  }
  return (double)((float)(dVar4 * (double)(float)((double)(float)(dVar5 + dVar3) + dVar7)) /
                 FLOAT_8043d384);
}



// ==== 80255848  gnt4-splArcLengthGetParameter-bl ====

/* WARNING: Removing unreachable block (ram,0x80255a24) */
/* WARNING: Removing unreachable block (ram,0x80255a1c) */
/* WARNING: Removing unreachable block (ram,0x80255a14) */
/* WARNING: Removing unreachable block (ram,0x80255a0c) */
/* WARNING: Removing unreachable block (ram,0x80255a04) */
/* WARNING: Removing unreachable block (ram,0x802559fc) */
/* WARNING: Removing unreachable block (ram,0x802559f4) */
/* WARNING: Removing unreachable block (ram,0x80255888) */
/* WARNING: Removing unreachable block (ram,0x80255880) */
/* WARNING: Removing unreachable block (ram,0x80255878) */
/* WARNING: Removing unreachable block (ram,0x80255870) */
/* WARNING: Removing unreachable block (ram,0x80255868) */
/* WARNING: Removing unreachable block (ram,0x80255860) */
/* WARNING: Removing unreachable block (ram,0x80255858) */

double gnt4_splArcLengthGetParameter_bl(double param_1,byte *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  double in_f26;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  
  dVar8 = (double)FLOAT_8043d398;
  dVar6 = (double)FLOAT_8043d388;
  uVar3 = 0;
  dVar5 = dVar8;
  if ((dVar8 < param_1) && (dVar5 = dVar6, param_1 < dVar6)) {
    iVar2 = *(int *)(param_2 + 0x10);
    for (iVar1 = iVar2; (double)*(float *)(iVar1 + 4) < param_1; iVar1 = iVar1 + 4) {
      uVar3 = uVar3 + 1;
    }
    if (*param_2 == 0) {
      dVar5 = (double)*(float *)(iVar2 + uVar3 * 4);
      in_f26 = (double)((float)(param_1 - dVar5) /
                       (float)((double)*(float *)(iVar2 + uVar3 * 4 + 4) - dVar5));
    }
    else if (*param_2 < 4) {
      dVar11 = (double)FLOAT_8043d3c8;
      dVar9 = (double)FLOAT_8043d3c4;
      dVar10 = (double)FLOAT_8043d398;
      dVar5 = (double)(*(float *)(param_2 + 0xc) *
                      (float)(param_1 - (double)*(float *)(iVar2 + uVar3 * 4)));
      while( true ) {
        dVar7 = dVar6;
        dVar6 = (double)(float)(dVar8 - dVar7);
        if (dVar6 < dVar10) {
          dVar6 = -dVar6;
        }
        if (dVar6 < dVar11) break;
        in_f26 = (double)(float)((double)(float)(dVar8 + dVar7) * dVar9);
        dVar4 = gnt4_splArcLength_bl
                          (dVar8,in_f26,(float *)(*(int *)(param_2 + 0x14) + uVar3 * 0x14));
        dVar6 = in_f26;
        if ((double)(float)(dVar11 + dVar4) <= dVar5) {
          dVar5 = (double)(float)(dVar5 - dVar4);
          dVar6 = dVar7;
          dVar8 = in_f26;
        }
      }
    }
    dVar5 = (double)((float)(in_f26 + (double)(float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000
                                                                      ) - DOUBLE_8043d3a0)) /
                    ((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 2) ^ 0x80000000)
                            - DOUBLE_8043d3a0) - FLOAT_8043d388));
  }
  return dVar5;
}



// ==== 80255a48  gnt4-splArcLengthPoint-bl ====

void gnt4_splArcLengthPoint_bl(double param_1,float *param_2,byte *param_3)

{
  double dVar1;
  
  dVar1 = gnt4_splArcLengthGetParameter_bl(param_1,param_3);
  gnt4_splGetSplinePoint_bl(dVar1,param_2,param_3);
  return;
}



// ==== 80255a90  gnt4-HSD_MtxInverseConcat-bl ====

/* WARNING: Removing unreachable block (ram,0x80255ea8) */
/* WARNING: Removing unreachable block (ram,0x80255ea0) */
/* WARNING: Removing unreachable block (ram,0x80255e98) */
/* WARNING: Removing unreachable block (ram,0x80255e90) */
/* WARNING: Removing unreachable block (ram,0x80255e88) */
/* WARNING: Removing unreachable block (ram,0x80255e80) */
/* WARNING: Removing unreachable block (ram,0x80255e78) */
/* WARNING: Removing unreachable block (ram,0x80255e70) */
/* WARNING: Removing unreachable block (ram,0x80255e68) */
/* WARNING: Removing unreachable block (ram,0x80255ae0) */
/* WARNING: Removing unreachable block (ram,0x80255ad8) */
/* WARNING: Removing unreachable block (ram,0x80255ad0) */
/* WARNING: Removing unreachable block (ram,0x80255ac8) */
/* WARNING: Removing unreachable block (ram,0x80255ac0) */
/* WARNING: Removing unreachable block (ram,0x80255ab8) */
/* WARNING: Removing unreachable block (ram,0x80255ab0) */
/* WARNING: Removing unreachable block (ram,0x80255aa8) */
/* WARNING: Removing unreachable block (ram,0x80255aa0) */

undefined4 gnt4_HSD_MtxInverseConcat_bl(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined4 uVar18;
  double in_f23;
  double in_f24;
  double in_f25;
  double in_f26;
  double in_f27;
  double in_f28;
  double in_f29;
  double in_f30;
  double in_f31;
  double in_ps23_1;
  double in_ps24_1;
  double in_ps25_1;
  double in_ps26_1;
  double in_ps27_1;
  double in_ps28_1;
  double in_ps29_1;
  double in_ps30_1;
  double in_ps31_1;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_88;
  float fStack_84;
  float local_78;
  float fStack_74;
  float local_68;
  float fStack_64;
  float local_58;
  float fStack_54;
  float local_48;
  float fStack_44;
  float local_38;
  float fStack_34;
  float local_28;
  float fStack_24;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  local_28 = (float)in_f29;
  fStack_24 = (float)in_ps29_1;
  local_38 = (float)in_f28;
  fStack_34 = (float)in_ps28_1;
  local_48 = (float)in_f27;
  fStack_44 = (float)in_ps27_1;
  local_58 = (float)in_f26;
  fStack_54 = (float)in_ps26_1;
  local_68 = (float)in_f25;
  fStack_64 = (float)in_ps25_1;
  local_78 = (float)in_f24;
  fStack_74 = (float)in_ps24_1;
  local_88 = (float)in_f23;
  fStack_84 = (float)in_ps23_1;
  fVar1 = param_1[6];
  fVar2 = param_1[1];
  fVar3 = param_1[4];
  fVar4 = param_1[8];
  fVar5 = param_1[5];
  fVar6 = *param_1;
  fVar7 = param_1[2];
  fVar8 = param_1[10];
  fVar9 = param_1[9];
  fVar13 = -(fVar1 * fVar6 * fVar9 -
            -(fVar8 * fVar3 * fVar2 -
             -(fVar7 * fVar4 * fVar5 -
              (fVar9 * fVar7 * fVar3 + fVar8 * fVar6 * fVar5 + fVar4 * fVar2 * fVar1))));
  if (FLOAT_8043d3d0 == fVar13) {
    uVar18 = 0;
  }
  else {
    fVar10 = param_1[7];
    fVar13 = FLOAT_8043d3d4 / fVar13;
    fVar11 = param_1[3];
    fVar12 = param_1[0xb];
    fVar14 = fVar13 * (fVar5 * fVar8 - fVar9 * fVar1);
    fVar15 = fVar13 * -(fVar2 * fVar8 - fVar9 * fVar7);
    fVar16 = fVar13 * -(fVar3 * fVar8 - fVar4 * fVar1);
    fVar8 = fVar13 * (fVar6 * fVar8 - fVar4 * fVar7);
    fVar17 = fVar13 * (fVar3 * fVar9 - fVar4 * fVar5);
    fVar4 = fVar13 * --(fVar4 * fVar2 - fVar6 * fVar9);
    fVar9 = fVar13 * -(fVar5 * fVar7 - fVar2 * fVar1);
    fVar1 = fVar13 * -(fVar6 * fVar1 - fVar7 * fVar3);
    fVar13 = fVar13 * (fVar6 * fVar5 - fVar3 * fVar2);
    local_bc = -(fVar9 * fVar12 - (-fVar14 * fVar11 - fVar15 * fVar10));
    local_ac = -(fVar1 * fVar12 - (-fVar16 * fVar11 - fVar8 * fVar10));
    local_9c = -(fVar13 * fVar12 - (-fVar17 * fVar11 - fVar4 * fVar10));
    if ((param_1 == param_3) || (param_2 == param_3)) {
      fVar2 = param_2[4];
      fVar3 = *param_2;
      fVar5 = param_2[8];
      local_c8 = fVar9 * fVar5 + fVar14 * fVar3 + fVar15 * fVar2;
      local_b8 = fVar1 * fVar5 + fVar16 * fVar3 + fVar8 * fVar2;
      local_a8 = fVar13 * fVar5 + fVar17 * fVar3 + fVar4 * fVar2;
      fVar2 = param_2[5];
      fVar3 = param_2[1];
      fVar5 = param_2[9];
      local_c4 = fVar9 * fVar5 + fVar14 * fVar3 + fVar15 * fVar2;
      local_b4 = fVar1 * fVar5 + fVar16 * fVar3 + fVar8 * fVar2;
      local_a4 = fVar13 * fVar5 + fVar17 * fVar3 + fVar4 * fVar2;
      fVar2 = param_2[6];
      fVar3 = param_2[2];
      fVar5 = param_2[10];
      local_c0 = fVar9 * fVar5 + fVar14 * fVar3 + fVar15 * fVar2;
      local_b0 = fVar1 * fVar5 + fVar16 * fVar3 + fVar8 * fVar2;
      local_a0 = fVar13 * fVar5 + fVar17 * fVar3 + fVar4 * fVar2;
      fVar2 = param_2[7];
      fVar3 = param_2[3];
      fVar5 = param_2[0xb];
      local_bc = local_bc + fVar9 * fVar5 + fVar14 * fVar3 + fVar15 * fVar2;
      local_ac = local_ac + fVar1 * fVar5 + fVar16 * fVar3 + fVar8 * fVar2;
      local_9c = local_9c + fVar13 * fVar5 + fVar17 * fVar3 + fVar4 * fVar2;
      gnt4_PSMTXCopy_bl(&local_c8,param_3);
    }
    else {
      *param_3 = fVar9 * param_2[8] + fVar14 * *param_2 + fVar15 * param_2[4];
      param_3[1] = fVar9 * param_2[9] + fVar14 * param_2[1] + fVar15 * param_2[5];
      param_3[2] = fVar9 * param_2[10] + fVar14 * param_2[2] + fVar15 * param_2[6];
      param_3[3] = local_bc + fVar9 * param_2[0xb] + fVar14 * param_2[3] + fVar15 * param_2[7];
      param_3[4] = fVar1 * param_2[8] + fVar16 * *param_2 + fVar8 * param_2[4];
      param_3[5] = fVar1 * param_2[9] + fVar16 * param_2[1] + fVar8 * param_2[5];
      param_3[6] = fVar1 * param_2[10] + fVar16 * param_2[2] + fVar8 * param_2[6];
      param_3[7] = local_ac + fVar1 * param_2[0xb] + fVar16 * param_2[3] + fVar8 * param_2[7];
      param_3[8] = fVar13 * param_2[8] + fVar17 * *param_2 + fVar4 * param_2[4];
      param_3[9] = fVar13 * param_2[9] + fVar17 * param_2[1] + fVar4 * param_2[5];
      param_3[10] = fVar13 * param_2[10] + fVar17 * param_2[2] + fVar4 * param_2[6];
      param_3[0xb] = local_9c + fVar13 * param_2[0xb] + fVar17 * param_2[3] + fVar4 * param_2[7];
    }
    uVar18 = 1;
  }
  return uVar18;
}



// ==== 80255ec0  gnt4-HSD_MtxGetRotation-bl ====

/* WARNING: Removing unreachable block (ram,0x802561c0) */
/* WARNING: Removing unreachable block (ram,0x802561b8) */
/* WARNING: Removing unreachable block (ram,0x80255ed8) */
/* WARNING: Removing unreachable block (ram,0x80255ed0) */

void gnt4_HSD_MtxGetRotation_bl(float *param_1,float *param_2)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  
  fVar1 = FLOAT_8043d3d0;
  dVar2 = (double)(param_1[8] * param_1[8] + *param_1 * *param_1 + param_1[4] * param_1[4]);
  if ((double)FLOAT_8043d3d0 < dVar2) {
    dVar3 = 1.0 / SQRT(dVar2);
    dVar3 = DOUBLE_8043d3d8 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d3e0);
    dVar3 = DOUBLE_8043d3d8 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d3e0);
    dVar2 = (double)(float)(dVar2 * DOUBLE_8043d3d8 * dVar3 *
                                    -(dVar2 * dVar3 * dVar3 - DOUBLE_8043d3e0));
  }
  if ((double)FLOAT_8043d3e8 <= dVar2) {
    dVar3 = (double)(param_1[9] * param_1[9] + param_1[1] * param_1[1] + param_1[5] * param_1[5]);
    if ((double)FLOAT_8043d3d0 < dVar3) {
      dVar4 = 1.0 / SQRT(dVar3);
      dVar4 = DOUBLE_8043d3d8 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d3e0);
      dVar4 = DOUBLE_8043d3d8 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d3e0);
      dVar3 = (double)(float)(dVar3 * DOUBLE_8043d3d8 * dVar4 *
                                      -(dVar3 * dVar4 * dVar4 - DOUBLE_8043d3e0));
    }
    if ((double)FLOAT_8043d3e8 <= dVar3) {
      dVar4 = (double)(param_1[10] * param_1[10] + param_1[2] * param_1[2] + param_1[6] * param_1[6]
                      );
      if ((double)FLOAT_8043d3d0 < dVar4) {
        dVar5 = 1.0 / SQRT(dVar4);
        dVar5 = DOUBLE_8043d3d8 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_8043d3e0);
        dVar5 = DOUBLE_8043d3d8 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_8043d3e0);
        dVar4 = (double)(float)(dVar4 * DOUBLE_8043d3d8 * dVar5 *
                                        -(dVar4 * dVar5 * dVar5 - DOUBLE_8043d3e0));
      }
      if ((double)FLOAT_8043d3e8 <= dVar4) {
        dVar2 = (double)(float)(-(double)param_1[8] / dVar2);
        fVar1 = FLOAT_8043d3ec;
        if ((dVar2 < (double)FLOAT_8043d3d4) &&
           (fVar1 = FLOAT_8043d3f4, (double)FLOAT_8043d3f0 < dVar2)) {
          dVar2 = (double)gnt4_asin_bl(dVar2,(double)FLOAT_8043d3d4);
          fVar1 = (float)dVar2;
        }
        param_2[1] = fVar1;
        dVar2 = gnt4_cos_bl((double)param_2[1]);
        if (FLOAT_8043d3e8 <= (float)dVar2) {
          if ((double)FLOAT_8043d3d0 == (double)(float)((double)param_1[10] / dVar4)) {
            fVar1 = FLOAT_8043d3f4;
            if ((double)FLOAT_8043d3d0 <= (double)(float)((double)param_1[9] / dVar3)) {
              fVar1 = FLOAT_8043d3ec;
            }
          }
          else {
            dVar2 = (double)gnt4_atan2_bl((double)(float)((double)param_1[9] / dVar3),
                                          (double)(float)((double)param_1[10] / dVar4));
            fVar1 = (float)dVar2;
          }
          *param_2 = fVar1;
          if ((double)FLOAT_8043d3d0 == (double)*param_1) {
            fVar1 = FLOAT_8043d3f4;
            if ((double)FLOAT_8043d3d0 <= (double)param_1[4]) {
              fVar1 = FLOAT_8043d3ec;
            }
          }
          else {
            dVar2 = (double)gnt4_atan2_bl((double)param_1[4],(double)*param_1);
            fVar1 = (float)dVar2;
          }
          param_2[2] = fVar1;
          return;
        }
        if ((double)FLOAT_8043d3d0 == (double)param_1[5]) {
          fVar1 = FLOAT_8043d3f4;
          if ((double)FLOAT_8043d3d0 <= (double)param_1[1]) {
            fVar1 = FLOAT_8043d3ec;
          }
        }
        else {
          dVar2 = (double)gnt4_atan2_bl((double)param_1[1],(double)param_1[5]);
          fVar1 = (float)dVar2;
        }
        *param_2 = fVar1;
        param_2[2] = FLOAT_8043d3d0;
        return;
      }
    }
  }
  *param_2 = FLOAT_8043d3d0;
  param_2[1] = fVar1;
  param_2[2] = fVar1;
  return;
}



// ==== 802561e0  gnt4-HSD_MtxGetTranslate-bl ====

void gnt4_HSD_MtxGetTranslate_bl(int param_1,undefined4 *param_2)

{
  *param_2 = *(undefined4 *)(param_1 + 0xc);
  param_2[1] = *(undefined4 *)(param_1 + 0x1c);
  param_2[2] = *(undefined4 *)(param_1 + 0x2c);
  return;
}



// ==== 802561fc  gnt4-HSD_MtxGetScale-bl ====

void gnt4_HSD_MtxGetScale_bl(float *param_1,float *param_2)

{
  double dVar1;
  double dVar2;
  float afStack_44 [3];
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
  dVar1 = gnt4_PSVECSquareMag_bl(&local_20);
  if (dVar1 <= (double)FLOAT_8043d3f8) {
    *param_2 = FLOAT_8043d3d0;
    local_2c = param_1[1];
    local_28 = param_1[5];
    local_24 = param_1[9];
    dVar1 = gnt4_PSVECSquareMag_bl(&local_2c);
    if (dVar1 <= (double)FLOAT_8043d3f8) {
      param_2[1] = FLOAT_8043d3d0;
      local_38 = param_1[2];
      local_34 = param_1[6];
      local_30 = param_1[10];
      dVar1 = gnt4_PSVECMag_bl(&local_38);
      param_2[2] = (float)dVar1;
    }
    else {
      dVar1 = (double)(float)((double)FLOAT_8043d3d4 / dVar1);
      if ((double)FLOAT_8043d3d0 < dVar1) {
        dVar2 = 1.0 / SQRT(dVar1);
        dVar2 = DOUBLE_8043d3d8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0);
        dVar2 = DOUBLE_8043d3d8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0);
        dVar1 = (double)(float)(dVar1 * DOUBLE_8043d3d8 * dVar2 *
                                        -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0));
      }
      param_2[1] = (float)((double)FLOAT_8043d3d4 / dVar1);
      gnt4_PSQUATScale_bl(dVar1,&local_2c,&local_2c);
      local_38 = param_1[2];
      local_34 = param_1[6];
      local_30 = param_1[10];
      dVar1 = gnt4_PSQUATDotProduct_bl(&local_2c,&local_38);
      gnt4_PSQUATScale_bl(dVar1,&local_2c,afStack_44);
      gnt4_PSVECSubtract_bl(&local_38,afStack_44,&local_38);
      dVar1 = gnt4_PSVECMag_bl(&local_38);
      param_2[2] = (float)dVar1;
    }
  }
  else {
    dVar1 = (double)(float)((double)FLOAT_8043d3d4 / dVar1);
    if ((double)FLOAT_8043d3d0 < dVar1) {
      dVar2 = 1.0 / SQRT(dVar1);
      dVar2 = DOUBLE_8043d3d8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0);
      dVar2 = DOUBLE_8043d3d8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0);
      dVar1 = (double)(float)(dVar1 * DOUBLE_8043d3d8 * dVar2 *
                                      -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0));
    }
    *param_2 = (float)((double)FLOAT_8043d3d4 / dVar1);
    gnt4_PSQUATScale_bl(dVar1,&local_20,&local_20);
    local_2c = param_1[1];
    local_28 = param_1[5];
    local_24 = param_1[9];
    dVar1 = gnt4_PSQUATDotProduct_bl(&local_20,&local_2c);
    gnt4_PSQUATScale_bl(dVar1,&local_20,afStack_44);
    gnt4_PSVECSubtract_bl(&local_2c,afStack_44,&local_2c);
    dVar1 = gnt4_PSVECSquareMag_bl(&local_2c);
    if (dVar1 <= (double)FLOAT_8043d3f8) {
      param_2[1] = FLOAT_8043d3d0;
      local_38 = param_1[2];
      local_34 = param_1[6];
      local_30 = param_1[10];
      dVar1 = gnt4_PSQUATDotProduct_bl(&local_20,&local_38);
      gnt4_PSQUATScale_bl(dVar1,&local_20,afStack_44);
      gnt4_PSVECSubtract_bl(&local_38,afStack_44,&local_38);
      dVar1 = gnt4_PSVECSquareMag_bl(&local_38);
      if (dVar1 <= (double)FLOAT_8043d3f8) {
        param_2[2] = FLOAT_8043d3d0;
      }
      else {
        if ((double)FLOAT_8043d3d0 < dVar1) {
          dVar2 = 1.0 / SQRT(dVar1);
          dVar2 = DOUBLE_8043d3d8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0);
          dVar2 = DOUBLE_8043d3d8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0);
          dVar1 = (double)(float)(dVar1 * DOUBLE_8043d3d8 * dVar2 *
                                          -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0));
        }
        param_2[2] = (float)dVar1;
      }
    }
    else {
      dVar1 = (double)(float)((double)FLOAT_8043d3d4 / dVar1);
      if ((double)FLOAT_8043d3d0 < dVar1) {
        dVar2 = 1.0 / SQRT(dVar1);
        dVar2 = DOUBLE_8043d3d8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0);
        dVar2 = DOUBLE_8043d3d8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0);
        dVar1 = (double)(float)(dVar1 * DOUBLE_8043d3d8 * dVar2 *
                                        -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0));
      }
      param_2[1] = (float)((double)FLOAT_8043d3d4 / dVar1);
      gnt4_PSQUATScale_bl(dVar1,&local_2c,&local_2c);
      local_38 = param_1[2];
      local_34 = param_1[6];
      local_30 = param_1[10];
      dVar1 = gnt4_PSQUATDotProduct_bl(&local_2c,&local_38);
      gnt4_PSQUATScale_bl(dVar1,&local_2c,afStack_44);
      gnt4_PSVECSubtract_bl(&local_38,afStack_44,&local_38);
      dVar1 = gnt4_PSQUATDotProduct_bl(&local_20,&local_38);
      gnt4_PSQUATScale_bl(dVar1,&local_20,afStack_44);
      gnt4_PSVECSubtract_bl(&local_38,afStack_44,&local_38);
      dVar1 = gnt4_PSVECSquareMag_bl(&local_38);
      if (dVar1 <= (double)FLOAT_8043d3f8) {
        param_2[2] = FLOAT_8043d3d0;
      }
      else {
        if ((double)FLOAT_8043d3d0 < dVar1) {
          dVar2 = 1.0 / SQRT(dVar1);
          dVar2 = DOUBLE_8043d3d8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0);
          dVar2 = DOUBLE_8043d3d8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0);
          dVar1 = (double)(float)(dVar1 * DOUBLE_8043d3d8 * dVar2 *
                                          -(dVar1 * dVar2 * dVar2 - DOUBLE_8043d3e0));
        }
        param_2[2] = (float)dVar1;
        gnt4_PSVECCrossProduct_bl(&local_2c,&local_38,afStack_44);
        dVar2 = gnt4_PSQUATDotProduct_bl(&local_20,afStack_44);
        dVar1 = DOUBLE_8043d408;
        if (dVar2 < DOUBLE_8043d400) {
          *param_2 = (float)((double)*param_2 * DOUBLE_8043d408);
          param_2[1] = (float)((double)param_2[1] * dVar1);
          param_2[2] = (float)((double)param_2[2] * dVar1);
        }
      }
    }
  }
  return;
}



// ==== 802566d4  gnt4-HSD_MkRotationMtx-bl ====

/* WARNING: Removing unreachable block (ram,0x802567f0) */
/* WARNING: Removing unreachable block (ram,0x802567e8) */
/* WARNING: Removing unreachable block (ram,0x802567e0) */
/* WARNING: Removing unreachable block (ram,0x802567d8) */
/* WARNING: Removing unreachable block (ram,0x802567d0) */
/* WARNING: Removing unreachable block (ram,0x80256704) */
/* WARNING: Removing unreachable block (ram,0x802566fc) */
/* WARNING: Removing unreachable block (ram,0x802566f4) */
/* WARNING: Removing unreachable block (ram,0x802566ec) */
/* WARNING: Removing unreachable block (ram,0x802566e4) */

void gnt4_HSD_MkRotationMtx_bl(float *param_1,float *param_2)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  dVar2 = gnt4_sin_bl((double)*param_2);
  dVar7 = (double)(float)dVar2;
  dVar2 = gnt4_cos_bl((double)*param_2);
  dVar6 = (double)(float)dVar2;
  dVar2 = gnt4_sin_bl((double)param_2[1]);
  dVar5 = (double)(float)dVar2;
  dVar2 = gnt4_cos_bl((double)param_2[1]);
  dVar4 = (double)(float)dVar2;
  dVar2 = gnt4_sin_bl((double)param_2[2]);
  dVar3 = (double)(float)dVar2;
  dVar2 = gnt4_cos_bl((double)param_2[2]);
  fVar1 = FLOAT_8043d3d0;
  dVar2 = (double)(float)dVar2;
  *param_1 = (float)(dVar4 * dVar2);
  param_1[4] = (float)(dVar4 * dVar3);
  param_1[8] = (float)-dVar5;
  param_1[1] = (float)(dVar2 * (double)(float)(dVar7 * dVar5) - (double)(float)(dVar6 * dVar3));
  param_1[5] = (float)(dVar3 * (double)(float)(dVar7 * dVar5) + (double)(float)(dVar6 * dVar2));
  param_1[9] = (float)(dVar7 * dVar4);
  param_1[2] = (float)(dVar2 * (double)(float)(dVar6 * dVar5) + (double)(float)(dVar7 * dVar3));
  param_1[6] = (float)(dVar3 * (double)(float)(dVar6 * dVar5) - (double)(float)(dVar7 * dVar2));
  param_1[10] = (float)(dVar6 * dVar4);
  param_1[3] = fVar1;
  param_1[7] = fVar1;
  param_1[0xb] = fVar1;
  return;
}



// ==== 80256810  gnt4-HSD_MtxSRT-bl ====

/* WARNING: Removing unreachable block (ram,0x80256ac8) */
/* WARNING: Removing unreachable block (ram,0x80256ac0) */
/* WARNING: Removing unreachable block (ram,0x80256ab8) */
/* WARNING: Removing unreachable block (ram,0x80256ab0) */
/* WARNING: Removing unreachable block (ram,0x80256aa8) */
/* WARNING: Removing unreachable block (ram,0x80256aa0) */
/* WARNING: Removing unreachable block (ram,0x80256a98) */
/* WARNING: Removing unreachable block (ram,0x80256a90) */
/* WARNING: Removing unreachable block (ram,0x80256a88) */
/* WARNING: Removing unreachable block (ram,0x80256a80) */
/* WARNING: Removing unreachable block (ram,0x80256a78) */
/* WARNING: Removing unreachable block (ram,0x80256870) */
/* WARNING: Removing unreachable block (ram,0x80256868) */
/* WARNING: Removing unreachable block (ram,0x80256860) */
/* WARNING: Removing unreachable block (ram,0x80256858) */
/* WARNING: Removing unreachable block (ram,0x80256850) */
/* WARNING: Removing unreachable block (ram,0x80256848) */
/* WARNING: Removing unreachable block (ram,0x80256840) */
/* WARNING: Removing unreachable block (ram,0x80256838) */
/* WARNING: Removing unreachable block (ram,0x80256830) */
/* WARNING: Removing unreachable block (ram,0x80256828) */
/* WARNING: Removing unreachable block (ram,0x80256820) */

void gnt4_HSD_MtxSRT_bl(undefined4 param_1,undefined4 param_2,float *param_3,float *param_4,
                       float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  float *pfVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  undefined8 uVar24;
  
  uVar24 = gnt4__savegpr_27_bl();
  pfVar7 = (float *)((ulonglong)uVar24 >> 0x20);
  pfVar8 = (float *)uVar24;
  dVar9 = gnt4_sin_bl((double)*param_3);
  dVar23 = (double)(float)dVar9;
  dVar9 = gnt4_cos_bl((double)*param_3);
  dVar22 = (double)(float)dVar9;
  dVar9 = gnt4_sin_bl((double)param_3[1]);
  dVar21 = (double)(float)dVar9;
  dVar9 = gnt4_cos_bl((double)param_3[1]);
  dVar20 = (double)(float)dVar9;
  dVar9 = gnt4_sin_bl((double)param_3[2]);
  dVar19 = (double)(float)dVar9;
  dVar9 = gnt4_cos_bl((double)param_3[2]);
  dVar14 = (double)*pfVar8;
  dVar16 = (double)pfVar8[1];
  dVar10 = (double)(float)dVar9;
  dVar18 = (double)pfVar8[2];
  dVar9 = dVar16;
  dVar11 = dVar18;
  dVar12 = dVar14;
  dVar13 = dVar18;
  dVar15 = dVar14;
  dVar17 = dVar16;
  if (param_5 != (float *)0x0) {
    fVar1 = *param_5;
    if (fVar1 < FLOAT_8043d3d0) {
      fVar4 = fVar1 - FLOAT_8043d410;
    }
    else {
      fVar4 = FLOAT_8043d410 + fVar1;
    }
    fVar2 = param_5[1];
    if (fVar2 < FLOAT_8043d3d0) {
      fVar5 = fVar2 - FLOAT_8043d410;
    }
    else {
      fVar5 = FLOAT_8043d410 + fVar2;
    }
    fVar3 = param_5[2];
    if (fVar3 < FLOAT_8043d3d0) {
      fVar6 = fVar3 - FLOAT_8043d410;
    }
    else {
      fVar6 = FLOAT_8043d410 + fVar3;
    }
    dVar9 = (double)(float)(dVar16 * (double)(fVar2 * (FLOAT_8043d3d4 / fVar4)));
    dVar11 = (double)(float)(dVar18 * (double)(fVar3 * (FLOAT_8043d3d4 / fVar4)));
    dVar12 = (double)(float)(dVar14 * (double)(fVar1 * (FLOAT_8043d3d4 / fVar5)));
    dVar13 = (double)(float)(dVar18 * (double)(fVar3 * (FLOAT_8043d3d4 / fVar5)));
    dVar15 = (double)(float)(dVar14 * (double)(fVar1 * (FLOAT_8043d3d4 / fVar6)));
    dVar17 = (double)(float)(dVar16 * (double)(fVar2 * (FLOAT_8043d3d4 / fVar6)));
  }
  *pfVar7 = (float)(dVar10 * (double)(float)(dVar14 * dVar20));
  pfVar7[4] = (float)(dVar19 * (double)(float)(dVar12 * dVar20));
  pfVar7[8] = (float)(-dVar15 * dVar21);
  pfVar7[1] = (float)(dVar9 * (double)(float)(dVar10 * (double)(float)(dVar23 * dVar21) -
                                             (double)(float)(dVar22 * dVar19)));
  pfVar7[5] = (float)(dVar16 * (double)(float)(dVar19 * (double)(float)(dVar23 * dVar21) +
                                              (double)(float)(dVar22 * dVar10)));
  pfVar7[9] = (float)(dVar20 * (double)(float)(dVar17 * dVar23));
  pfVar7[2] = (float)(dVar11 * (double)(float)(dVar10 * (double)(float)(dVar22 * dVar21) +
                                              (double)(float)(dVar23 * dVar19)));
  pfVar7[6] = (float)(dVar13 * (double)(float)(dVar19 * (double)(float)(dVar22 * dVar21) -
                                              (double)(float)(dVar23 * dVar10)));
  pfVar7[10] = (float)(dVar20 * (double)(float)(dVar18 * dVar22));
  pfVar7[3] = *param_4;
  pfVar7[7] = param_4[1];
  pfVar7[0xb] = param_4[2];
  gnt4__restgpr_27_bl();
  return;
}



// ==== 80256ae8  gnt4-HSD_MtxSRTQuat-bl ====

void gnt4_HSD_MtxSRTQuat_bl
               (float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fStack_48;
  float local_44;
  float local_40;
  float local_38;
  float local_30;
  float local_28;
  float local_24;
  
  gnt4_PSMTXScale_bl((double)*param_2,(double)param_2[1],(double)param_2[2],param_1);
  gnt4_PSMTXQuat_bl(&fStack_48,param_3);
  if (param_5 != (float *)0x0) {
    fVar1 = *param_5;
    if (fVar1 < FLOAT_8043d3d0) {
      fVar1 = fVar1 - FLOAT_8043d410;
    }
    else {
      fVar1 = FLOAT_8043d410 + fVar1;
    }
    fVar2 = param_5[1];
    if (fVar2 < FLOAT_8043d3d0) {
      fVar4 = fVar2 - FLOAT_8043d410;
    }
    else {
      fVar4 = FLOAT_8043d410 + fVar2;
    }
    fVar3 = param_5[2];
    if (fVar3 < FLOAT_8043d3d0) {
      fVar3 = fVar3 - FLOAT_8043d410;
    }
    else {
      fVar3 = FLOAT_8043d410 + fVar3;
    }
    local_44 = local_44 * fVar2 * (FLOAT_8043d3d4 / fVar1);
    local_40 = local_40 * param_5[1] * (FLOAT_8043d3d4 / fVar1);
    local_24 = local_24 * param_5[1] * (FLOAT_8043d3d4 / fVar3);
    local_38 = local_38 * *param_5 * (FLOAT_8043d3d4 / fVar4);
    local_28 = local_28 * *param_5 * (FLOAT_8043d3d4 / fVar3);
    local_30 = local_30 * param_5[2] * (FLOAT_8043d3d4 / fVar4);
  }
  gnt4_PSMTXConcat_bl(&fStack_48,param_1,param_1);
  param_1[3] = *param_4;
  param_1[7] = param_4[1];
  param_1[0xb] = param_4[2];
  return;
}



// ==== 80256c94  gnt4-HSD_MtxScaledAdd-bl ====

void gnt4_HSD_MtxScaledAdd_bl(double param_1,float *param_2,float *param_3,float *param_4)

{
  *param_4 = (float)(param_1 * (double)*param_2 + (double)*param_3);
  param_4[1] = (float)(param_1 * (double)param_2[1] + (double)param_3[1]);
  param_4[2] = (float)(param_1 * (double)param_2[2] + (double)param_3[2]);
  param_4[3] = (float)(param_1 * (double)param_2[3] + (double)param_3[3]);
  param_4[4] = (float)(param_1 * (double)param_2[4] + (double)param_3[4]);
  param_4[5] = (float)(param_1 * (double)param_2[5] + (double)param_3[5]);
  param_4[6] = (float)(param_1 * (double)param_2[6] + (double)param_3[6]);
  param_4[7] = (float)(param_1 * (double)param_2[7] + (double)param_3[7]);
  param_4[8] = (float)(param_1 * (double)param_2[8] + (double)param_3[8]);
  param_4[9] = (float)(param_1 * (double)param_2[9] + (double)param_3[9]);
  param_4[10] = (float)(param_1 * (double)param_2[10] + (double)param_3[10]);
  param_4[0xb] = (float)(param_1 * (double)param_2[0xb] + (double)param_3[0xb]);
  return;
}



// ==== 80256d58  gnt4-HSD_VecAlloc-bl ====

undefined4 *
gnt4_HSD_VecAlloc_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  
  puVar1 = gnt4_HSD_ObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_803fa480,param_10,param_11,param_12,param_13,param_14,param_15,
                             param_16);
  if (puVar1 == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435f68,
                     0x38c,&DAT_80435f70,param_12,param_13,param_14,param_15,param_16);
  }
  return puVar1;
}



// ==== 80256da4  gnt4-HSD_VecFree-bl ====

void gnt4_HSD_VecFree_bl(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    gnt4_HSD_ObjFree(-0x7fc05b80,param_1);
  }
  return;
}



