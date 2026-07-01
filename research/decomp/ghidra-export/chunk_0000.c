// ==== 80003100  __check_pad3 ====

uint __check_pad3(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = 0x80000000;
  if ((DAT_800030e4 & 0xeef) == 0xeef) {
    bVar2 = zz_02048b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0);
    uVar1 = (uint)bVar2;
  }
  return uVar1;
}



// ==== 80003140  __set_debug_bba ====

void __set_debug_bba(void)

{
  DAT_80436498 = 1;
  return;
}



// ==== 8000314c  zz_000314c_ ====

undefined1 zz_000314c_(void)

{
  return DAT_80436498;
}



// ==== 80003154  start ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void start(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8)

{
  uint uVar1;
  char cVar2;
  ushort *puVar3;
  undefined4 *puVar4;
  uint *puVar5;
  undefined4 **ppuVar6;
  uint in_r7;
  undefined *in_r8;
  uint in_r9;
  int in_r10;
  undefined4 *puVar7;
  undefined4 **ppuVar8;
  undefined4 *puVar9;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 uVar10;
  
  __init_registers();
  gnt4___init_hardware_bl();
  uVar10 = zz_0003340_();
  DAT_80000044 = 0;
  if (DAT_800000f4 == (undefined4 *)0x0) {
    uVar1 = _DAT_800030e8;
    if (DAT_80000034 != 0) goto LAB_800031bc;
  }
  else {
    uVar1 = DAT_800000f4[3];
LAB_800031bc:
    in_r7 = uVar1;
    puVar4 = (undefined4 *)0x0;
    if ((in_r7 == 2) || (puVar4 = (undefined4 *)0x1, in_r7 == 3)) {
      FUN_80231370(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                   (int)((ulonglong)uVar10 >> 0x20),(int)uVar10,puVar4,FUN_80231370,in_r7,in_r8,
                   in_r9,in_r10);
    }
    else if (in_r7 == 4) {
      __set_debug_bba();
    }
  }
  puVar4 = DAT_800000f4;
  ppuVar6 = &DAT_800000f4;
  if ((DAT_800000f4 != (undefined4 *)0x0) &&
     (ppuVar6 = (undefined4 **)DAT_800000f4[2], ppuVar6 != (undefined4 **)0x0)) {
    ppuVar6 = (undefined4 **)((int)DAT_800000f4 + (int)ppuVar6);
    puVar7 = *ppuVar6;
    if (puVar7 != (undefined4 *)0x0) {
      ppuVar8 = ppuVar6 + 1;
      puVar9 = puVar7;
      do {
        ppuVar6 = ppuVar6 + 1;
        *ppuVar6 = (undefined4 *)((int)*ppuVar6 + (int)puVar4);
        puVar9 = (undefined4 *)((int)puVar9 + -1);
      } while (puVar9 != (undefined4 *)0x0);
      puVar5 = &DAT_80000034;
      in_r7 = (uint)ppuVar8 & 0xffffffe0;
      DAT_80000034 = in_r7;
      goto LAB_80003260;
    }
  }
  puVar7 = (undefined4 *)0x0;
  ppuVar8 = (undefined4 **)0x0;
  puVar5 = DAT_800000f4;
LAB_80003260:
  uVar10 = zz_020ae10_();
  uVar10 = zz_01feda4_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       (int)((ulonglong)uVar10 >> 0x20),(int)uVar10,puVar5,(uint)ppuVar6,in_r7,in_r8
                       ,in_r9,in_r10);
  puVar3 = &DAT_800030e6;
  puVar4 = (undefined4 *)(DAT_800030e6 & 0x8000);
  if (((DAT_800030e6 & 0x8000) == 0) || ((DAT_800030e6 & 0x7fff) == 1)) {
    __check_pad3(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  cVar2 = zz_000314c_();
  if (cVar2 == '\x01') {
    InitMetroTRK_BBA(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,puVar3,puVar4,
                     ppuVar6,in_r7,in_r8,in_r9,in_r10);
  }
  uVar10 = gnt4___init_user_bl();
  zz_00527d8_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar7,ppuVar8,
              (int)puVar4,(undefined *)ppuVar6,in_r7,in_r8,in_r9,in_r10);
  FUN_802331c4();
  return;
}



// ==== 800032b0  __init_registers ====

undefined8 __init_registers(void)

{
  return 0;
}



// ==== 80003340  zz_0003340_ ====

void zz_0003340_(void)

{
  undefined **ppuVar1;
  undefined *__n;
  undefined *__dest;
  
  for (ppuVar1 = &PTR___check_pad3_80005544; __n = ppuVar1[2], __n != (undefined *)0x0;
      ppuVar1 = ppuVar1 + 3) {
    __dest = ppuVar1[1];
    if (__dest != *ppuVar1) {
      gnt4_memcpy(__dest,*ppuVar1,(size_t)__n);
      zz_0003424_((uint)__dest,(int)__n);
    }
  }
  for (ppuVar1 = &PTR_DAT_800055b0; ppuVar1[1] != (undefined *)0x0; ppuVar1 = ppuVar1 + 2) {
    gnt4_memset(*ppuVar1,0,(size_t)ppuVar1[1]);
  }
  return;
}



// ==== 80003400  gnt4-__init_hardware-bl ====

void gnt4___init_hardware_bl(void)

{
  gnt4___OSPSInit_bl();
  gnt4___OSFPRInit_bl();
  gnt4___OSCacheInit_bl();
  return;
}



// ==== 80003424  zz_0003424_ ====

void zz_0003424_(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_1 & 0xfffffff1;
  iVar1 = param_2 + (param_1 - uVar2);
  do {
    dataCacheBlockStore(uVar2);
    sync(0);
    instructionCacheBlockInvalidate(uVar2);
    uVar2 = uVar2 + 8;
    iVar1 = iVar1 + -8;
  } while (-1 < iVar1);
  instructionSynchronize();
  return;
}



// ==== 80003458  TRK_memset ====

int TRK_memset(int param_1,byte param_2,uint param_3)

{
  TRK_fill_mem(param_1,param_2,param_3);
  return param_1;
}



// ==== 80003488  TRK_memcpy ====

void TRK_memcpy(int param_1,int param_2,int param_3)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  
  puVar1 = (undefined1 *)(param_2 + -1);
  puVar3 = (undefined1 *)(param_1 + -1);
  iVar2 = param_3 + 1;
  while( true ) {
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) break;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
    *puVar3 = *puVar1;
  }
  return;
}



// ==== 800053e0  __TRK_reset ====

bool __TRK_reset(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  bool bVar1;
  
  bVar1 = zz_02048b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0);
  return bVar1;
}



// ==== 8000540c  gnt4-memset ====

void * gnt4_memset(void *__s,int __c,size_t __n)

{
  gnt4___fill_mem_bl((int)__s,(byte)__c,__n);
  return __s;
}



// ==== 8000543c  gnt4-__fill_mem-bl ====

void gnt4___fill_mem_bl(int param_1,byte param_2,uint param_3)

{
  uint uVar1;
  uint *puVar2;
  byte *pbVar3;
  uint uVar4;
  
  uVar4 = (uint)param_2;
  pbVar3 = (byte *)(param_1 + -1);
  if (0x1f < param_3) {
    uVar1 = ~(uint)pbVar3 & 3;
    if (uVar1 != 0) {
      param_3 = param_3 - uVar1;
      do {
        uVar1 = uVar1 - 1;
        pbVar3 = pbVar3 + 1;
        *pbVar3 = param_2;
      } while (uVar1 != 0);
    }
    if (param_2 != 0) {
      uVar4 = uVar4 | uVar4 << 8 | (uint)param_2 << 0x18 | uVar4 << 0x10;
    }
    puVar2 = (uint *)(pbVar3 + -3);
    for (uVar1 = param_3 >> 5; uVar1 != 0; uVar1 = uVar1 - 1) {
      puVar2[1] = uVar4;
      puVar2[2] = uVar4;
      puVar2[3] = uVar4;
      puVar2[4] = uVar4;
      puVar2[5] = uVar4;
      puVar2[6] = uVar4;
      puVar2[7] = uVar4;
      puVar2 = puVar2 + 8;
      *puVar2 = uVar4;
    }
    for (uVar1 = param_3 >> 2 & 7; uVar1 != 0; uVar1 = uVar1 - 1) {
      puVar2 = puVar2 + 1;
      *puVar2 = uVar4;
    }
    pbVar3 = (byte *)((int)puVar2 + 3);
    param_3 = param_3 & 3;
  }
  if (param_3 != 0) {
    do {
      param_3 = param_3 - 1;
      pbVar3 = pbVar3 + 1;
      *pbVar3 = (byte)uVar4;
    } while (param_3 != 0);
    return;
  }
  return;
}



// ==== 800054f4  gnt4-memcpy ====

void * gnt4_memcpy(void *__dest,void *__src,size_t __n)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  
  if (__dest <= __src) {
    puVar1 = (undefined1 *)((int)__src + -1);
    puVar3 = (undefined1 *)((int)__dest + -1);
    iVar2 = __n + 1;
    while( true ) {
      iVar2 = iVar2 + -1;
      if (iVar2 == 0) break;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
      *puVar3 = *puVar1;
    }
    return __dest;
  }
  puVar1 = (undefined1 *)((int)__src + __n);
  puVar3 = (undefined1 *)((int)__dest + __n);
  iVar2 = __n + 1;
  while( true ) {
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) break;
    puVar1 = puVar1 + -1;
    puVar3 = puVar3 + -1;
    *puVar3 = *puVar1;
  }
  return __dest;
}



// ==== 800055e0  zz_00055e0_ ====

void zz_00055e0_(void)

{
  DAT_804360c7 = 1;
  DAT_804360c6 = 0xc3;
  DAT_804360c4 = 0x1c3;
  return;
}



// ==== 800055fc  zz_00055fc_ ====

uint zz_00055fc_(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = ((uint)DAT_804360c7 * 0x100 + (uint)DAT_804360c6) * 3;
  DAT_804360c7 = (char)((uint)iVar1 >> 8);
  uVar2 = (uint)DAT_804360c6 + (iVar1 >> 8 & 0xffU);
  DAT_804360c6 = (char)uVar2;
  return uVar2 & 0xff;
}



// ==== 80005630  zz_0005630_ ====

void zz_0005630_(void)

{
  undefined1 local_8;
  undefined2 local_4;
  
  local_4._1_1_ = (char)DAT_804360c4;
  local_8 = (char)((ushort)(DAT_804360c4 * 3) >> 8);
  local_4 = CONCAT11(local_8,(char)local_4 + local_8);
  DAT_804360c4 = local_4;
  return;
}



// ==== 80005668  zz_0005668_ ====

void zz_0005668_(int param_1)

{
  float *pfVar1;
  double dVar2;
  
  pfVar1 = (float *)((&PTR_DAT_804335a0)[DAT_804360c0] + param_1 * 0x10);
  gnt4_C_MTXPerspective_bl
            ((double)*pfVar1,(double)pfVar1[1],(double)pfVar1[2],(double)pfVar1[3],
             (float *)&DAT_803c0f80);
  gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f80,0);
  gnt4_GXGetProjectionv_bl((float *)&DAT_803c1098);
  gnt4_GXGetProjectionv_bl((float *)(param_1 * 0x1c + -0x7fc3f00c));
  dVar2 = (double)FLOAT_80436a20;
  gnt4_C_MTXOrtho_bl(dVar2,(double)(float)((double)CONCAT44(0x43300000,
                                                            (uint)*(ushort *)(DAT_804362ac + 6)) -
                                          DOUBLE_80436a28),dVar2,
                     (double)(float)((double)CONCAT44(0x43300000,(uint)*(ushort *)(DAT_804362ac + 4)
                                                     ) - DOUBLE_80436a28),dVar2,
                     (double)FLOAT_80436a24,(float *)&DAT_803c0f40);
  return;
}



// ==== 80005744  zz_0005744_ ====

double zz_0005744_(float *param_1,float *param_2,float *param_3)

{
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  if (param_1 == (float *)0x0) {
    local_1c = *param_2;
    local_18 = param_2[1];
    local_14 = param_2[2];
  }
  else {
    gnt4_PSMTXMultVec_bl(param_1,param_2,&local_1c);
  }
  gnt4_GXProject_bl((double)local_1c,(double)local_18,(double)local_14,(float *)&DAT_803c1100,
                    (float *)&DAT_803c1098,(float *)&DAT_803c1080,&local_28,&local_24,&local_20);
  if (param_3 != (float *)0x0) {
    *param_3 = local_28;
    param_3[1] = local_24;
    param_3[2] = local_20;
  }
  return (double)local_20;
}



// ==== 800057f0  zz_00057f0_ ====

void zz_00057f0_(float *param_1,float *param_2)

{
  float local_18;
  float local_14;
  float local_10;
  
  local_18 = *param_1;
  local_14 = param_1[1];
  local_10 = param_1[2];
  zz_0005744_((float *)0x0,&local_18,param_2);
  param_2[1] = -param_2[1];
  return;
}



// ==== 8000584c  zz_000584c_ ====

void zz_000584c_(void)

{
  undefined4 local_8 [2];
  
  local_8[0] = DAT_804335a8;
  gnt4_GXInitLightColor_bl(-0x7fc3ef4c,local_8);
  gnt4_GXInitLightSpot_bl((double)FLOAT_80436a20,-0x7fc3ef4c,0);
  gnt4_GXInitLightDistAttn_bl((double)FLOAT_80436a20,(double)FLOAT_80436a20,-0x7fc3ef4c,0);
  DAT_803c10f4 = DAT_802c3470;
  DAT_803c10f8 = DAT_802c3474;
  DAT_803c10fc = DAT_802c3478;
  return;
}



// ==== 800058d0  zz_00058d0_ ====

void zz_00058d0_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = param_1 * 0x18;
  gnt4_GXSetViewport_bl
            ((double)*(float *)(&DAT_802c32e0 + iVar4),(double)*(float *)(&DAT_802c32e4 + iVar4),
             (double)*(float *)(&DAT_802c32e8 + iVar4),(double)*(float *)(&DAT_802c32ec + iVar4),
             (double)*(float *)(&DAT_802c32f0 + iVar4),(double)*(float *)(&DAT_802c32f4 + iVar4));
  if (param_2 != 0) {
    iVar1 = gnt4___cvt_fp2unsigned_bl((double)*(float *)(&DAT_802c32ec + iVar4));
    iVar2 = gnt4___cvt_fp2unsigned_bl((double)*(float *)(&DAT_802c32e8 + iVar4));
    iVar3 = gnt4___cvt_fp2unsigned_bl((double)*(float *)(&DAT_802c32e4 + iVar4));
    iVar4 = gnt4___cvt_fp2unsigned_bl((double)*(float *)(&DAT_802c32e0 + iVar4));
    gnt4_GXSetScissor_bl(iVar4,iVar3,iVar2,iVar1);
  }
  gnt4_GXGetViewportv_bl((float *)&DAT_803c1080);
  return;
}



// ==== 80005984  zz_0005984_ ====

void zz_0005984_(undefined4 param_1)

{
  DAT_804360c0 = param_1;
  return;
}



// ==== 8000598c  zz_000598c_ ====

undefined * zz_000598c_(int param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)0x0;
  if (DAT_804360c0 != 0) {
    puVar1 = (&PTR_DAT_804335a0)[DAT_804360c0] + param_1 * 0x10;
  }
  return puVar1;
}



// ==== 800059b8  zz_00059b8_ ====

void zz_00059b8_(void)

{
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  local_20 = DAT_802b01a0;
  local_1c = DAT_802b01a4;
  local_18 = DAT_802b01a8;
  local_2c = DAT_802b01ac;
  local_28 = DAT_802b01b0;
  local_24 = DAT_802b01b4;
  local_38 = DAT_802b01b8;
  local_34 = DAT_802b01bc;
  local_30 = DAT_802b01c0;
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7380,&local_20,&local_2c,&local_38);
  *(undefined **)(PTR_DAT_80433930 + 0x20) = &DAT_803c7380;
  *(undefined **)(PTR_DAT_80433930 + 0x1c) = &DAT_803c7380;
  *(undefined **)(PTR_DAT_80433930 + 0x18) = &DAT_803c7380;
  *(undefined **)(PTR_DAT_80433930 + 0x14) = &DAT_803c7380;
  PTR_DAT_80433930[0xf] = 0xff;
  PTR_DAT_80433930[0xe] = 0xff;
  PTR_DAT_80433930[0xd] = 0xff;
  PTR_DAT_80433930[0xc] = 0xff;
  PTR_DAT_80433930[0x29] = 0;
  PTR_DAT_80433930[0x33] = 1;
  zz_0005984_(0);
  zz_0005668_(0);
  zz_00058d0_(0,0);
  zz_002a5f4_(0,0,0,0xff);
  return;
}



// ==== 80005af4  FUN_80005af4 ====

/* WARNING: Removing unreachable block (ram,0x80005fc4) */
/* WARNING: Removing unreachable block (ram,0x80005fbc) */
/* WARNING: Removing unreachable block (ram,0x80005b0c) */
/* WARNING: Removing unreachable block (ram,0x80005b04) */

void FUN_80005af4(float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  uint uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  float local_2b8 [14];
  float afStack_280 [16];
  float afStack_240 [16];
  float afStack_200 [17];
  float local_1bc [16];
  float local_17c [16];
  float local_13c [15];
  float afStack_100 [16];
  float afStack_c0 [16];
  float afStack_80 [18];
  
  iVar7 = 0;
  if (0 < param_3 + -1) {
    if (8 < param_3 + -1) {
      pfVar5 = local_2b8;
      uVar12 = param_3 - 2U >> 3;
      if (0 < param_3 + -9) {
        do {
          *pfVar5 = FLOAT_80436a30;
          iVar7 = iVar7 + 8;
          pfVar5[1] = FLOAT_80436a30;
          pfVar5[2] = FLOAT_80436a30;
          pfVar5[3] = FLOAT_80436a30;
          pfVar5[4] = FLOAT_80436a30;
          pfVar5[5] = FLOAT_80436a30;
          pfVar5[6] = FLOAT_80436a30;
          pfVar5[7] = FLOAT_80436a30;
          pfVar5 = pfVar5 + 8;
          uVar12 = uVar12 - 1;
        } while (uVar12 != 0);
      }
    }
    iVar4 = (param_3 + -1) - iVar7;
    pfVar5 = local_2b8 + iVar7;
    if (iVar7 < param_3 + -1) {
      do {
        *pfVar5 = FLOAT_80436a30;
        pfVar5 = pfVar5 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  iVar7 = param_3 + -2;
  afStack_280[1] = local_2b8[0];
  afStack_200[1] = FLOAT_80436a20;
  pfVar11 = local_2b8;
  afStack_240[1] = FLOAT_80436a34 * local_2b8[0];
  pfVar6 = afStack_200 + 2;
  pfVar8 = afStack_240 + 2;
  pfVar9 = afStack_280 + 2;
  pfVar10 = afStack_100 + 2;
  afStack_100[1] = FLOAT_80436a38 * (param_1[3] - *param_1);
  afStack_c0[1] = FLOAT_80436a38 * (param_1[4] - param_1[1]);
  afStack_80[1] = FLOAT_80436a38 * (param_1[5] - param_1[2]);
  pfVar5 = param_1;
  if (1 < param_3 + -1) {
    do {
      pfVar11 = pfVar11 + 1;
      fVar1 = *pfVar11;
      fVar2 = pfVar11[-1];
      *pfVar6 = fVar1;
      pfVar6 = pfVar6 + 1;
      *pfVar9 = fVar2;
      pfVar9 = pfVar9 + 1;
      *pfVar8 = FLOAT_80436a34 * (fVar2 + fVar1);
      pfVar8 = pfVar8 + 1;
      fVar3 = pfVar5[3];
      *pfVar10 = FLOAT_80436a38 *
                 ((fVar1 * (fVar3 - *pfVar5)) / fVar2 + (fVar2 * (pfVar5[6] - fVar3)) / fVar1);
      pfVar10[0x10] =
           FLOAT_80436a38 *
           ((fVar1 * (pfVar5[4] - pfVar5[1])) / fVar2 + (fVar2 * (pfVar5[7] - pfVar5[4])) / fVar1);
      pfVar10[0x20] =
           FLOAT_80436a38 *
           ((fVar1 * (pfVar5[5] - pfVar5[2])) / fVar2 + (fVar2 * (pfVar5[8] - pfVar5[5])) / fVar1);
      pfVar10 = pfVar10 + 1;
      iVar7 = iVar7 + -1;
      pfVar5 = pfVar5 + 3;
    } while (iVar7 != 0);
  }
  fVar1 = local_2b8[param_3 + -2];
  afStack_200[param_3] = fVar1;
  afStack_240[param_3] = FLOAT_80436a34 * fVar1;
  afStack_280[param_3] = FLOAT_80436a20;
  afStack_100[param_3] = FLOAT_80436a38 * (param_1[param_3 * 3 + -3] - param_1[param_3 * 3 + -6]);
  afStack_c0[param_3] = FLOAT_80436a38 * (param_1[param_3 * 3 + -2] - param_1[param_3 * 3 + -5]);
  afStack_80[param_3] = FLOAT_80436a38 * (param_1[param_3 * 3 + -1] - param_1[param_3 * 3 + -4]);
  zz_0005fe0_(afStack_200 + 1,afStack_240 + 1,afStack_280 + 1,afStack_100 + 1,local_1bc,param_3);
  zz_0005fe0_(afStack_200 + 1,afStack_240 + 1,afStack_280 + 1,afStack_c0 + 1,local_17c,param_3);
  zz_0005fe0_(afStack_200 + 1,afStack_240 + 1,afStack_280 + 1,afStack_80 + 1,local_13c,param_3);
  dVar15 = (double)FLOAT_80436a34;
  dVar16 = (double)FLOAT_80436a38;
  pfVar5 = local_2b8;
  pfVar11 = local_1bc;
  for (iVar7 = 0; iVar7 < param_3 + -1; iVar7 = iVar7 + 1) {
    dVar13 = (double)gnt4_pow_bl((double)*pfVar5,DOUBLE_80436a40);
    dVar14 = DOUBLE_80436a40;
    *param_2 = (float)(dVar15 * (double)(*param_1 - param_1[3])) / (float)dVar13 +
               (*pfVar11 + pfVar11[1]) / (*pfVar5 * *pfVar5);
    fVar1 = *pfVar5;
    param_2[3] = (float)(dVar16 * (double)(param_1[3] - *param_1)) / (fVar1 * fVar1) -
                 (float)(dVar15 * (double)*pfVar11 + (double)pfVar11[1]) / fVar1;
    param_2[6] = *pfVar11;
    param_2[9] = *param_1;
    dVar13 = (double)gnt4_pow_bl((double)*pfVar5,dVar14);
    dVar14 = DOUBLE_80436a40;
    param_2[1] = (pfVar11[0x10] + pfVar11[0x11]) / (*pfVar5 * *pfVar5) +
                 (float)(dVar15 * (double)(param_1[1] - param_1[4])) / (float)dVar13;
    fVar1 = *pfVar5;
    param_2[4] = (float)(dVar16 * (double)(param_1[4] - param_1[1])) / (fVar1 * fVar1) -
                 (float)(dVar15 * (double)pfVar11[0x10] + (double)pfVar11[0x11]) / fVar1;
    param_2[7] = pfVar11[0x10];
    param_2[10] = param_1[1];
    dVar14 = (double)gnt4_pow_bl((double)*pfVar5,dVar14);
    param_2[2] = (pfVar11[0x20] + pfVar11[0x21]) / (*pfVar5 * *pfVar5) +
                 (float)(dVar15 * (double)(param_1[2] - param_1[5])) / (float)dVar14;
    fVar1 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    param_2[5] = (float)(dVar16 * (double)(param_1[5] - param_1[2])) / (fVar1 * fVar1) -
                 (float)(dVar15 * (double)pfVar11[0x20] + (double)pfVar11[0x21]) / fVar1;
    pfVar6 = pfVar11 + 0x20;
    pfVar11 = pfVar11 + 1;
    param_2[8] = *pfVar6;
    pfVar6 = param_1 + 2;
    param_1 = param_1 + 3;
    param_2[0xb] = *pfVar6;
    param_2 = param_2 + 0xc;
  }
  return;
}



// ==== 80005fe0  zz_0005fe0_ ====

void zz_0005fe0_(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                int param_6)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  float *pfVar5;
  float *pfVar6;
  undefined1 *puVar7;
  uint uVar8;
  float local_48;
  undefined1 local_44 [68];
  
  fVar1 = *param_2;
  if (FLOAT_80436a20 == fVar1) {
    *param_5 = FLOAT_80436a20;
  }
  else {
    *param_5 = *param_4 / fVar1;
  }
  fVar2 = FLOAT_80436a20;
  iVar3 = param_6 + -1;
  puVar7 = local_44;
  pfVar5 = param_5;
  if (1 < param_6) {
    do {
      pfVar6 = pfVar5 + 1;
      param_4 = param_4 + 1;
      param_2 = param_2 + 1;
      param_1 = param_1 + 1;
      if (fVar2 == fVar1) {
        *(float *)(puVar7 + -4) = fVar2;
      }
      else {
        *(float *)(puVar7 + -4) = *param_3 / fVar1;
      }
      fVar1 = -(*param_1 * *(float *)(puVar7 + -4) - *param_2);
      if (fVar2 == fVar1) {
        *pfVar6 = fVar2;
      }
      else {
        *pfVar6 = -(*param_1 * *pfVar5 - *param_4) / fVar1;
      }
      puVar7 = puVar7 + 4;
      iVar3 = iVar3 + -1;
      param_3 = param_3 + 1;
      pfVar5 = pfVar6;
    } while (iVar3 != 0);
  }
  iVar3 = param_6 + -2;
  uVar4 = param_6 - 1;
  pfVar5 = param_5 + iVar3;
  pfVar6 = (float *)(local_44 + iVar3 * 4 + -4);
  if (-1 < iVar3) {
    uVar8 = uVar4 >> 3;
    if (uVar8 != 0) {
      do {
        fVar1 = pfVar6[-1];
        *pfVar5 = -(*pfVar6 * pfVar5[1] - *pfVar5);
        fVar2 = pfVar6[-2];
        pfVar5[-1] = -(fVar1 * *pfVar5 - pfVar5[-1]);
        fVar1 = pfVar6[-3];
        pfVar5[-2] = -(fVar2 * pfVar5[-1] - pfVar5[-2]);
        fVar2 = pfVar6[-4];
        pfVar5[-3] = -(fVar1 * pfVar5[-2] - pfVar5[-3]);
        fVar1 = pfVar6[-5];
        pfVar5[-4] = -(fVar2 * pfVar5[-3] - pfVar5[-4]);
        fVar2 = pfVar6[-6];
        pfVar5[-5] = -(fVar1 * pfVar5[-4] - pfVar5[-5]);
        fVar1 = pfVar6[-7];
        pfVar6 = pfVar6 + -8;
        pfVar5[-6] = -(fVar2 * pfVar5[-5] - pfVar5[-6]);
        pfVar5[-7] = -(fVar1 * pfVar5[-6] - pfVar5[-7]);
        pfVar5 = pfVar5 + -8;
        uVar8 = uVar8 - 1;
      } while (uVar8 != 0);
      uVar4 = uVar4 & 7;
      if (uVar4 == 0) {
        return;
      }
    }
    do {
      fVar1 = *pfVar6;
      pfVar6 = pfVar6 + -1;
      *pfVar5 = -(fVar1 * pfVar5[1] - *pfVar5);
      pfVar5 = pfVar5 + -1;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  return;
}



// ==== 800061a8  FUN_800061a8 ====

void FUN_800061a8(int param_1,int param_2)

{
  zz_00061f0_(param_1,param_2,1);
  return;
}



// ==== 800061cc  glxCopyMatrix(float ====

void glxCopyMatrix_float(int param_1,int param_2)

{
  zz_00061f0_(param_1,param_2,0);
  return;
}



// ==== 800061f0  zz_00061f0_ ====

void zz_00061f0_(int param_1,int param_2,int param_3)

{
  float fVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + param_3 + 0x7df) = 0;
  fVar1 = FLOAT_80436a20;
  iVar2 = param_1 + param_3 * 4;
  *(undefined **)(iVar2 + 0x7ec) = (&PTR_DAT_802c3770)[param_2];
  *(float *)(iVar2 + 0x7e4) = fVar1;
  *(undefined1 *)(iVar2 + 0x7f7) = 0xff;
  *(undefined1 *)(iVar2 + 0x7f4) = 0;
  *(undefined1 *)(iVar2 + 0x7f5) = 0;
  *(undefined1 *)(iVar2 + 0x7f6) = 0;
  return;
}



// ==== 80006238  zz_0006238_ ====

void zz_0006238_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_0006f98_(param_1);
  *(undefined1 *)(iVar1 + 0xc28) = 0;
  *(undefined1 *)(iVar1 + 0xc29) = 0;
  *(undefined1 *)(iVar1 + 0xc2a) = 0;
  *(undefined1 *)(iVar1 + 0xc2b) = 0xff;
  *(undefined4 *)(param_1 + 0x7ec) = 0;
  *(undefined4 *)(param_1 + 0x7f0) = 0;
  return;
}



// ==== 80006284  zz_0006284_ ====

void zz_0006284_(int param_1)

{
  double dVar1;
  double dVar2;
  double dVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  uint uVar9;
  int iVar10;
  float *pfVar11;
  uint uVar12;
  int iVar13;
  float *pfVar14;
  int iVar15;
  int iVar16;
  undefined4 local_58;
  
  iVar10 = 0;
  iVar15 = 0;
  iVar16 = 2;
  iVar13 = param_1;
  do {
    pfVar11 = *(float **)(iVar13 + 0x7ec);
    if (pfVar11 != (float *)0x0) {
      iVar15 = iVar10 + 0x7df;
      while( true ) {
        pfVar14 = (float *)0x0;
        if (*(float *)(iVar13 + 0x7e4) < *pfVar11) break;
        if (((uint)pfVar11[2] & 0xf0000000) == 0) {
          pfVar11 = pfVar11 + 3;
        }
        else {
          uVar9 = (uint)pfVar11[2] & 0xff;
          pfVar14 = pfVar11;
          if (uVar9 == 0) {
            *(float *)(iVar13 + 0x7e4) = *pfVar11;
            break;
          }
          *(char *)(param_1 + iVar15) = *(char *)(param_1 + iVar15) + '\x01';
          uVar12 = (uint)pfVar11[2] >> 8 & 0xff;
          if ((uVar12 != 0) && (uVar12 <= *(byte *)(param_1 + iVar15))) {
            *(float *)(iVar13 + 0x7e4) = *pfVar11;
            break;
          }
          fVar4 = *pfVar11;
          pfVar11 = pfVar11 + uVar9 * -3;
          *(float *)(iVar13 + 0x7e4) = *(float *)(iVar13 + 0x7e4) - fVar4;
          *(float *)(iVar13 + 0x7e4) = *(float *)(iVar13 + 0x7e4) + *pfVar11;
        }
      }
      if (pfVar14 == (float *)0x0) {
        pfVar14 = pfVar11 + -3;
      }
      fVar4 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(pfVar14 + 1)) - DOUBLE_80436a28);
      fVar7 = *pfVar11 - *pfVar14;
      fVar8 = *(float *)(iVar13 + 0x7e4) - *pfVar14;
      dVar1 = (double)CONCAT44(0x43300000,(uint)*(byte *)(pfVar11 + 1)) - DOUBLE_80436a28;
      fVar5 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)((int)pfVar14 + 5)) -
                     DOUBLE_80436a28);
      dVar2 = (double)CONCAT44(0x43300000,(uint)*(byte *)((int)pfVar11 + 5)) - DOUBLE_80436a28;
      fVar6 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)((int)pfVar14 + 6)) -
                     DOUBLE_80436a28);
      dVar3 = (double)CONCAT44(0x43300000,(uint)*(byte *)((int)pfVar11 + 6)) - DOUBLE_80436a28;
      *(float *)(iVar13 + 0x7e4) = *(float *)(iVar13 + 0x7e4) + *(float *)(param_1 + 0x1dc8);
      local_58 = CONCAT13((char)(int)(fVar8 * (((float)dVar1 - fVar4) / fVar7) + fVar4),
                          CONCAT12((char)(int)(fVar8 * (((float)dVar2 - fVar5) / fVar7) + fVar5),
                                   0xff));
      local_58._2_2_ = CONCAT11((char)(int)(fVar8 * (((float)dVar3 - fVar6) / fVar7) + fVar6),0xff);
      if (pfVar14 == pfVar11) {
        *(undefined4 *)(iVar13 + 0x7ec) = 0;
      }
      iVar15 = iVar10 + 1;
      *(undefined4 *)(iVar13 + 0x7f4) = local_58;
    }
    iVar13 = iVar13 + 4;
    iVar10 = iVar10 + 1;
    iVar16 = iVar16 + -1;
    if (iVar16 == 0) {
      if (iVar15 != 0) {
        iVar13 = zz_0006f98_(param_1);
        *(undefined4 *)(iVar13 + 0xc28) = *(undefined4 *)(param_1 + iVar15 * 4 + 0x7f0);
      }
      return;
    }
  } while( true );
}



// ==== 800064d4  zz_00064d4_ ====

void zz_00064d4_(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int local_28 [7];
  
  if ((PTR_DAT_80433930[0x32] == '\x02') || (PTR_DAT_80433930[0x32] == '\x01')) {
    iVar3 = 0;
    piVar5 = local_28;
    iVar6 = 0;
    while( true ) {
      if ((char)PTR_DAT_80433934[0x53] <= iVar6) break;
      iVar2 = iVar3 + 0x114;
      *piVar5 = 0;
      iVar6 = iVar6 + 1;
      iVar3 = iVar3 + 0x3c;
      *(undefined4 *)(PTR_DAT_80433934 + iVar2) = 0;
      piVar5 = piVar5 + 1;
    }
    if ((PTR_DAT_80433930[2] & 1) != 0) {
      local_28[(char)PTR_DAT_80433934[0xcb]] = local_28[(char)PTR_DAT_80433934[0xcb]] + 1;
    }
    if ((PTR_DAT_80433930[2] & 2) != 0) {
      local_28[(char)PTR_DAT_80433934[0xcc]] = local_28[(char)PTR_DAT_80433934[0xcc]] + 1;
    }
    if ((PTR_DAT_80433930[2] & 4) != 0) {
      local_28[(char)PTR_DAT_80433934[0xcd]] = local_28[(char)PTR_DAT_80433934[0xcd]] + 1;
    }
    if ((PTR_DAT_80433930[2] & 8) != 0) {
      local_28[(char)PTR_DAT_80433934[0xce]] = local_28[(char)PTR_DAT_80433934[0xce]] + 1;
    }
    iVar3 = 0;
    do {
      puVar1 = PTR_DAT_80433934;
      iVar6 = (char)PTR_DAT_80433934[iVar3 + 0xcb] * 0x3c;
      if (local_28[(char)PTR_DAT_80433934[iVar3 + 0xcb]] == 0) {
        if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar3) != 0) {
          iVar2 = zz_000673c_(iVar3);
          *(int *)(puVar1 + iVar6 + 0x114) = *(int *)(puVar1 + iVar6 + 0x114) + iVar2;
        }
      }
      else if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar3) != 0) {
        iVar2 = zz_000673c_(iVar3);
        *(int *)(puVar1 + iVar6 + 0x114) = *(int *)(puVar1 + iVar6 + 0x114) + iVar2;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 4);
  }
  iVar3 = 0;
  for (iVar6 = 0; puVar1 = PTR_DAT_80433934, iVar6 < (char)PTR_DAT_80433934[0x53]; iVar6 = iVar6 + 1
      ) {
    iVar4 = *(int *)(PTR_DAT_80433934 + iVar3 + 0x114);
    iVar2 = iVar4 / 10 + (iVar4 >> 0x1f);
    *(int *)(PTR_DAT_80433934 + iVar3 + 0x114) =
         iVar4 - (short)((short)iVar4 + ((short)iVar2 - (short)(iVar2 >> 0x1f)) * -10);
    *(undefined4 *)(puVar1 + iVar3 + 0x11c) = *(undefined4 *)(puVar1 + iVar3 + 0x114);
    *(undefined4 *)(puVar1 + iVar3 + 0x118) = *(undefined4 *)(puVar1 + iVar3 + 0x114);
    iVar3 = iVar3 + 0x3c;
  }
  return;
}



// ==== 8000673c  zz_000673c_ ====

int zz_000673c_(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined2 local_28 [8];
  
  iVar4 = 0;
  iVar5 = 0;
  for (iVar3 = 0; iVar3 < (char)PTR_DAT_80433934[param_1 + 0x5a]; iVar3 = iVar3 + 1) {
    iVar1 = param_1 * 0x348 + iVar5;
    if (-1 < *(short *)(PTR_DAT_80433934 + iVar1 + 0x1e8)) {
      local_28[0] = *(undefined2 *)(PTR_DAT_80433934 + iVar1 + 0x1e8);
      uVar2 = zz_0066168_((char *)local_28,(int)(char)PTR_DAT_80433934[iVar1 + 0x1ea]);
      if (((int)(char)PTR_DAT_80433930[2] & 1 << param_1) == 0) {
        uVar2 = (int)(uVar2 * 2) / 3 + ((int)(uVar2 * 2) >> 0x1f) + ((uVar2 & 0x7fffffff) >> 0x1e);
      }
      iVar4 = iVar4 + uVar2;
    }
    iVar5 = iVar5 + 0x1c;
  }
  return iVar4;
}



// ==== 80006800  zz_0006800_ ====

void zz_0006800_(void)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_80433934;
  *(undefined2 *)(PTR_DAT_80433934 + 0x124) = 3000;
  *(undefined2 *)(puVar1 + 0x126) = 0;
  *(undefined2 *)(puVar1 + 0x128) = 0;
  *(undefined2 *)(puVar1 + 0x12a) = 0;
  puVar1 = PTR_DAT_80433934;
  *(undefined2 *)(PTR_DAT_80433934 + 0x160) = 3000;
  *(undefined2 *)(puVar1 + 0x162) = 0;
  *(undefined2 *)(puVar1 + 0x164) = 0;
  *(undefined2 *)(puVar1 + 0x166) = 0;
  puVar1 = PTR_DAT_80433934;
  *(undefined2 *)(PTR_DAT_80433934 + 0x19c) = 3000;
  *(undefined2 *)(puVar1 + 0x19e) = 0;
  *(undefined2 *)(puVar1 + 0x1a0) = 0;
  *(undefined2 *)(puVar1 + 0x1a2) = 0;
  puVar1 = PTR_DAT_80433934;
  *(undefined2 *)(PTR_DAT_80433934 + 0x1d8) = 3000;
  *(undefined2 *)(puVar1 + 0x1da) = 0;
  *(undefined2 *)(puVar1 + 0x1dc) = 0;
  *(undefined2 *)(puVar1 + 0x1de) = 0;
  return;
}



// ==== 8000685c  zz_000685c_ ====

void zz_000685c_(int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  if ('\x06' < (char)PTR_DAT_80433934[0x15da]) {
    PTR_DAT_80433934[0x15da] = 6;
  }
  if ((char)PTR_DAT_80433934[0x15da] < (char)PTR_DAT_80433930[3]) {
    PTR_DAT_80433934[0x15da] = PTR_DAT_80433930[3];
  }
  if ((param_1 != 0) &&
     (PTR_DAT_80433934[0x15d9] = PTR_DAT_80433930[2],
     (char)PTR_DAT_80433930[3] < (char)PTR_DAT_80433934[0x15da])) {
    iVar4 = 0;
    iVar5 = 0;
    while( true ) {
      if ((int)(char)PTR_DAT_80433934[0x15da] - (int)(char)PTR_DAT_80433930[3] <= iVar5) break;
      if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar4) == 0) {
        iVar5 = iVar5 + 1;
        PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] | (byte)(1 << iVar4);
      }
      iVar4 = iVar4 + 1;
    }
  }
  iVar4 = 0;
  iVar8 = 0;
  iVar7 = 0;
  iVar5 = 0;
  PTR_DAT_80433934[0x15db] = PTR_DAT_80433934[0x15d9];
  PTR_DAT_80433934[0x15dc] = PTR_DAT_80433934[0x15da];
  do {
    iVar3 = 0;
    iVar6 = 0;
    PTR_DAT_80433934[iVar4 + 0x15ce] = 0;
    while( true ) {
      puVar1 = PTR_DAT_80433934;
      if ((char)PTR_DAT_80433934[iVar4 + 0x5a] <= iVar6) break;
      iVar2 = iVar8 + iVar3;
      PTR_DAT_80433934[iVar2 + 0x1fe] = 0;
      puVar1[iVar2 + 0x200] = 0;
      if (iVar6 == (char)PTR_DAT_80433934[iVar4 + 0x5a] + -1) {
        PTR_DAT_80433934[iVar4 + 0x15ce] = (char)iVar6;
        puVar1[iVar2 + 0x1ff] = 0;
      }
      else {
        puVar1[iVar2 + 0x1ff] = 1;
      }
      iVar3 = iVar3 + 0x1c;
      iVar6 = iVar6 + 1;
    }
    if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar4) == 0) {
      PTR_DAT_80433934[iVar4 + 0x54] = 0;
      PTR_DAT_80433934[iVar4 + 0x15c8] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar5 + 0x10) = 0xffff;
      PTR_DAT_80433934[iVar4 + 0x5a] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar7 + 0x159e) = 0;
    }
    else {
      PTR_DAT_80433934[iVar4 + 0x54] = 0;
      PTR_DAT_80433934[iVar4 + 0x15c8] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar7 + 0x159e) = 1;
      zz_0068424_(iVar4,(undefined2 *)(PTR_DAT_80433934 + iVar5 + 0x10),
                  PTR_DAT_80433934 + iVar4 + 0xa0);
    }
    iVar4 = iVar4 + 1;
    iVar7 = iVar7 + 8;
    iVar5 = iVar5 + 2;
    iVar8 = iVar8 + 0x348;
  } while (iVar4 < 6);
  return;
}



// ==== 80006abc  zz_0006abc_ ====

void zz_0006abc_(void)

{
  char cVar1;
  
  cVar1 = PTR_DAT_80433930[0x32];
  if (cVar1 == '\x01') {
    *PTR_DAT_80433950 = 0;
    PTR_DAT_80433950[1] = 0x1f;
    *PTR_DAT_80433950 = *PTR_DAT_80433950 + (char)*(undefined2 *)(PTR_DAT_80433934 + 0x46);
    *PTR_DAT_80433950 = *PTR_DAT_80433950 & 0x1f;
    PTR_DAT_80433950[1] = PTR_DAT_80433950[1] - (char)*(undefined2 *)(PTR_DAT_80433934 + 0x46);
    PTR_DAT_80433950[1] = PTR_DAT_80433950[1] & 0x1f;
    return;
  }
  if (cVar1 < '\x01') {
    return;
  }
  if ('\x02' < cVar1) {
    return;
  }
  *PTR_DAT_80433950 = 7;
  PTR_DAT_80433950[1] = 7;
  PTR_DAT_80433950[2] = 7;
  PTR_DAT_80433950[3] = 7;
  return;
}



// ==== 80006b74  zz_0006b74_ ====

void zz_0006b74_(void)

{
  *(int *)(PTR_DAT_80433934 + 0x17f8) = DAT_80436238 + 0xd6800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1810) = 0;
  *(int *)(PTR_DAT_80433934 + 0x17fc) = DAT_80436238 + 0xd9800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1814) = 0;
  *(int *)(PTR_DAT_80433934 + 0x1800) = DAT_80436238 + 0xdc800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1818) = 0;
  *(int *)(PTR_DAT_80433934 + 0x1804) = DAT_80436238 + 0xdf800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x181c) = 0;
  *(int *)(PTR_DAT_80433934 + 0x1808) = DAT_80436238 + 0xe2800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1820) = 0;
  *(int *)(PTR_DAT_80433934 + 0x180c) = DAT_80436238 + 0xe5800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1824) = 0;
  return;
}



// ==== 80006c24  zz_0006c24_ ====

void zz_0006c24_(int param_1,int param_2)

{
  if (PTR_DAT_80433930[0x32] != '\x01') {
    return;
  }
  if (0xfff < *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 4 + 0x1810)) {
    return;
  }
  *(undefined2 *)
   (*(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 4 + 0x17f8) +
   *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 4 + 0x1810) * 2) =
       *(undefined2 *)(param_2 + 0x3ea);
  *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 4 + 0x1810) =
       *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 4 + 0x1810) + 1;
  return;
}



// ==== 80006c88  zz_0006c88_ ====

void zz_0006c88_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,void *param_10,uint param_11,undefined4 param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  char cVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  short sVar6;
  char cVar7;
  
  gnt4_HSD_ArchiveParse_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
             *(uint **)(param_9 + 0xc),param_10,param_11,param_12,param_13,param_14,param_15,
             param_16);
  pcVar3 = (char *)zz_025b178_(*(int *)(param_9 + 0xc),0);
  piVar4 = (int *)gnt4_HSD_ArchiveGetPublicAddress_bl(*(int *)(param_9 + 0xc),pcVar3);
  *(int **)(param_9 + 0x10) = piVar4;
  sVar6 = 0;
  for (iVar5 = 0; *(int *)(*piVar4 + iVar5) != 0; iVar5 = iVar5 + 4) {
    sVar1 = sVar6 + 1;
    sVar6 = sVar6 + 1;
    *(short *)(param_9 + 0x1a) = sVar1;
  }
  cVar7 = '\0';
  for (iVar5 = 0; *(int *)(piVar4[2] + iVar5) != 0; iVar5 = iVar5 + 4) {
    cVar2 = cVar7 + '\x01';
    cVar7 = cVar7 + '\x01';
    *(char *)(param_9 + 0x18) = cVar2;
  }
  if (piVar4[3] != 0) {
    *(undefined1 *)(param_9 + 0x19) = 1;
  }
  *(undefined1 *)(param_9 + 10) = 1;
  return;
}



// ==== 80006d4c  zz_0006d4c_ ====

void zz_0006d4c_(void)

{
  int *piVar1;
  
  piVar1 = zz_0197a0c_(0);
  if (piVar1 != (int *)0x0) {
    piVar1[3] = 0;
  }
  return;
}



// ==== 80006d80  zz_0006d80_ ====

void zz_0006d80_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if ((int *)param_9[3] != (int *)0x0) {
    gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       (int *)param_9[3],param_10,param_11,param_12,param_13,param_14,param_15,
                       param_16);
    param_9[3] = 0;
  }
  zz_0197ad8_(param_9);
  return;
}



// ==== 80006dc8  zz_0006dc8_ ====

int * zz_0006dc8_(int param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = zz_0197a0c_(3);
  if (piVar2 != (int *)0x0) {
    uVar1 = param_1 + 0x1f;
    iVar3 = gnt4_HSD_Alloc_bl((((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0)) *
                              0x20);
    piVar2[3] = iVar3;
    if (iVar3 == 0) {
      zz_0197ad8_(piVar2);
      piVar2 = (int *)0x0;
    }
  }
  return piVar2;
}



// ==== 80006e3c  zz_0006e3c_ ====

undefined4 zz_0006e3c_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = gnt4_HSD_Alloc_bl(0x44);
  *(int *)(param_1 + 0xc) = iVar1;
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
    *(undefined1 *)(param_1 + 10) = 0;
  }
  return uVar2;
}



// ==== 80006e8c  zz_0006e8c_ ====

undefined4 zz_0006e8c_(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    if (*(char *)(param_1 + 10) == '\0') {
      gnt4_HSD_Free_bl();
    }
    else {
      gnt4_HSD_ArchiveFree_bl(*(int *)(param_1 + 0xc));
    }
  }
  return 0;
}



// ==== 80006ed8  zz_0006ed8_ ====

undefined4
zz_0006ed8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
           double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
           undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
           undefined4 param_15,undefined4 param_16)

{
  if (*(int **)(param_9 + 0xc) != (int *)0x0) {
    gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int **)(param_9 + 0xc),param_10,param_11,param_12,param_13,param_14,
                       param_15,param_16);
    *(undefined4 *)(param_9 + 0xc) = 0;
  }
  return 0;
}



// ==== 80006f1c  zz_0006f1c_ ====

undefined4 zz_0006f1c_(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    gnt4_HSD_Free_bl();
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  return 0;
}



// ==== 80006f78  zz_0006f78_ ====

undefined4 zz_0006f78_(int param_1)

{
  return *(undefined4 *)(&DAT_803bbac0 + *(char *)(param_1 + 0x97) * 0xc30);
}



// ==== 80006f98  zz_0006f98_ ====

int zz_0006f98_(int param_1)

{
  return *(char *)(param_1 + 0x97) * 0xc30 + -0x7fc44b40;
}



// ==== 80006fb4  zz_0006fb4_ ====

void zz_0006fb4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  int extraout_r4;
  int iVar3;
  undefined4 *puVar4;
  
  iVar2 = **(int **)(param_9 + 0x10);
  puVar4 = *(undefined4 **)(iVar2 + param_11 * 4);
  iVar3 = param_11;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),iVar2,param_11,param_12,param_13,param_14
                                 ,param_15,param_16);
    iVar2 = extraout_r4;
  }
  piVar1 = gnt4_HSD_JObjLoadJoint
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar4
                      ,iVar2,iVar3,param_12,param_13,param_14,param_15,param_16);
  *(int **)(param_10 + 0xc) = piVar1;
  *(int *)(param_10 + 0x14) = param_11;
  *(undefined1 *)(param_10 + 0xb) = 0;
  *(undefined1 *)(param_10 + 0x10) = 1;
  return;
}



// ==== 80007030  zz_0007030_ ====

void zz_0007030_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  undefined **ppuVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  
  puVar7 = *(undefined4 **)(**(int **)(param_9 + 0x10) + param_11 * 4);
  iVar5 = param_11;
  iVar6 = param_12;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,
                                 param_12,param_13,param_14,param_15,param_16);
  }
  ppuVar1 = zz_02429e4_();
  uVar8 = zz_024298c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      &PTR_zz_008da7c__802da7f0,0x802e0000,iVar5,iVar6,param_13,param_14,param_15,
                      param_16);
  if (param_12 == 0) {
    param_12 = param_10 + 0x18;
  }
  uVar4 = extraout_r4;
  uVar2 = zz_008d714_(param_12);
  piVar3 = gnt4_HSD_JObjLoadJoint
                     (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar7,
                      uVar4,iVar5,iVar6,param_13,param_14,param_15,param_16);
  *(int **)(param_10 + 0xc) = piVar3;
  zz_024298c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppuVar1,uVar4,iVar5,
              iVar6,param_13,param_14,param_15,param_16);
  zz_008d714_(uVar2);
  *(int *)(param_10 + 0x14) = param_11;
  *(undefined1 *)(param_10 + 0xb) = 0;
  *(undefined1 *)(param_10 + 0x10) = 1;
  return;
}



// ==== 800070e4  zz_00070e4_ ====

void zz_00070e4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  undefined **ppuVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  
  puVar7 = *(undefined4 **)(**(int **)(param_9 + 0x10) + param_11 * 4);
  iVar5 = param_11;
  iVar6 = param_12;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,
                                 param_12,param_13,param_14,param_15,param_16);
  }
  ppuVar1 = zz_02429e4_();
  uVar8 = zz_024298c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      &PTR_zz_008dae4__802da844,0x802e0000,iVar5,iVar6,param_13,param_14,param_15,
                      param_16);
  if (param_12 == 0) {
    param_12 = param_10 + 0x18;
  }
  uVar4 = extraout_r4;
  uVar2 = zz_008d780_(param_12);
  piVar3 = gnt4_HSD_JObjLoadJoint
                     (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar7,
                      uVar4,iVar5,iVar6,param_13,param_14,param_15,param_16);
  *(int **)(param_10 + 0xc) = piVar3;
  zz_024298c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppuVar1,uVar4,iVar5,
              iVar6,param_13,param_14,param_15,param_16);
  zz_008d780_(uVar2);
  *(int *)(param_10 + 0x14) = param_11;
  *(undefined1 *)(param_10 + 0xb) = 0;
  *(undefined1 *)(param_10 + 0x10) = 1;
  return;
}



// ==== 80007198  zz_0007198_ ====

void zz_0007198_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,char *param_11
                ,int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  int *piVar1;
  int *piVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  
  puVar6 = *(undefined4 **)(**(int **)(param_9 + 0x10) + (int)param_11 * 4);
  pcVar4 = param_11;
  iVar5 = param_12;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,
                                 param_12,param_13,param_14,param_15,param_16);
  }
  piVar1 = gnt4_HSD_JObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  *(int **)(param_10 + 0xc) = piVar1;
  if (*(int *)(param_10 + 0xc) != 0) {
    uVar8 = gnt4_HSD_JObjSetFlags
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)piVar1,
                       0x10,pcVar4,iVar5,param_13,param_14,param_15,param_16);
    piVar2 = gnt4_HSD_JObjLoadJoint
                       (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar6
                        ,extraout_r4,pcVar4,iVar5,param_13,param_14,param_15,param_16);
    if (piVar2 != (int *)0x0) {
      dVar9 = (double)gnt4_HSD_JObjAddChild
                                (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 (int)piVar1,(int)piVar2,pcVar4,iVar5,param_13,param_14,param_15,
                                 param_16);
      iVar7 = 1;
      uVar3 = extraout_r4_00;
      while ((iVar7 < param_12 &&
             (piVar1 = gnt4_HSD_JObjLoadJoint
                                 (dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  (int *)*puVar6,uVar3,pcVar4,iVar5,param_13,param_14,param_15,
                                  param_16), piVar1 != (int *)0x0))) {
        dVar9 = (double)zz_02500b0_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    (int)piVar2,(int)piVar1,pcVar4,iVar5,param_13,param_14,param_15,
                                    param_16);
        iVar7 = iVar7 + 1;
        uVar3 = extraout_r4_01;
        piVar2 = piVar1;
      }
      *(char **)(param_10 + 0x14) = param_11;
      *(undefined1 *)(param_10 + 0xb) = 0;
      *(undefined1 *)(param_10 + 0x10) = 1;
    }
  }
  return;
}



// ==== 8000726c  zz_000726c_ ====

void zz_000726c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  int extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined8 uVar6;
  
  iVar2 = **(int **)(param_9 + 0x10);
  puVar5 = *(undefined4 **)(iVar2 + (int)param_11 * 4);
  pfVar3 = param_11;
  uVar4 = param_12;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),iVar2,param_11,param_12,param_13,param_14
                                 ,param_15,param_16);
    iVar2 = extraout_r4;
  }
  piVar1 = gnt4_HSD_JObjLoadJoint
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar5
                      ,iVar2,pfVar3,uVar4,param_13,param_14,param_15,param_16);
  *(int **)(param_10 + 0xc) = piVar1;
  if (*(int *)(param_10 + 0xc) != 0) {
    *(float **)(param_10 + 0x14) = param_11;
    *(undefined1 *)(param_10 + 0xb) = 0;
    *(undefined1 *)(param_10 + 0x10) = 1;
    if (PTR_DAT_80433934[0x51] == '\x03') {
      param_12 = 0;
    }
    uVar6 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,param_12 ^ 0x80000000) -
                                       DOUBLE_80436a48),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,param_9,param_10,pfVar3,uVar4,param_13,param_14,param_15,
                        param_16);
    uVar6 = zz_0007c30_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                        extraout_r4_00,pfVar3,uVar4,param_13,param_14,param_15,param_16);
    zz_0007d40_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                extraout_r4_01,pfVar3,uVar4,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80007338  zz_0007338_ ====

void zz_0007338_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,int param_12,uint param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  undefined **ppuVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined8 uVar9;
  
  puVar8 = *(undefined4 **)(**(int **)(param_9 + 0x10) + (int)param_11 * 4);
  pfVar5 = param_11;
  iVar6 = param_12;
  uVar7 = param_13;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,
                                 param_12,param_13,param_14,param_15,param_16);
  }
  ppuVar1 = zz_02429e4_();
  uVar9 = zz_024298c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      &PTR_zz_008da7c__802da7f0,0x802e0000,pfVar5,iVar6,uVar7,param_14,param_15,
                      param_16);
  if (param_12 == 0) {
    param_12 = param_10 + 0x18;
  }
  uVar4 = extraout_r4;
  uVar2 = zz_008d714_(param_12);
  piVar3 = gnt4_HSD_JObjLoadJoint
                     (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar8,
                      uVar4,pfVar5,iVar6,uVar7,param_14,param_15,param_16);
  *(int **)(param_10 + 0xc) = piVar3;
  if (*(int *)(param_10 + 0xc) != 0) {
    zz_024298c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppuVar1,uVar4,pfVar5,
                iVar6,uVar7,param_14,param_15,param_16);
    zz_008d714_(uVar2);
    *(float **)(param_10 + 0x14) = param_11;
    *(undefined1 *)(param_10 + 0xb) = 0;
    *(undefined1 *)(param_10 + 0x10) = 1;
    if (PTR_DAT_80433934[0x51] == '\x03') {
      param_13 = 0;
    }
    uVar9 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,param_13 ^ 0x80000000) -
                                       DOUBLE_80436a48),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,param_9,param_10,pfVar5,iVar6,uVar7,param_14,param_15,
                        param_16);
    uVar9 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                        extraout_r4_00,pfVar5,iVar6,uVar7,param_14,param_15,param_16);
    zz_0007d40_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                extraout_r4_01,pfVar5,iVar6,uVar7,param_14,param_15,param_16);
  }
  return;
}



// ==== 8000744c  zz_000744c_ ====

void zz_000744c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,int param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int *piVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar3;
  undefined4 extraout_r4_02;
  float *pfVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  double dVar9;
  
  puVar7 = *(undefined4 **)(**(int **)(param_9 + 0x10) + (int)param_11 * 4);
  pfVar4 = param_11;
  iVar5 = param_12;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,
                                 param_12,param_13,param_14,param_15,param_16);
  }
  piVar1 = gnt4_HSD_JObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  *(int **)(param_10 + 0xc) = piVar1;
  if (*(int *)(param_10 + 0xc) != 0) {
    uVar8 = gnt4_HSD_JObjSetFlags
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)piVar1,
                       0x10,(undefined *)pfVar4,iVar5,param_13,param_14,param_15,param_16);
    piVar2 = gnt4_HSD_JObjLoadJoint
                       (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar7
                        ,extraout_r4,pfVar4,iVar5,param_13,param_14,param_15,param_16);
    if (piVar2 != (int *)0x0) {
      if ((undefined4 *)puVar7[2] != (undefined4 *)0x0) {
        pfVar4 = *(float **)puVar7[2];
        iVar5 = 0;
        gnt4_HSD_JObjAddAnimAll
                  (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,0,pfVar4,
                   (undefined4 *)0x0,param_13,param_14,param_15,param_16);
        uVar8 = gnt4_HSD_JObjReqAnimAll();
      }
      dVar9 = (double)gnt4_HSD_JObjAddChild
                                (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 (int)piVar1,(int)piVar2,(char *)pfVar4,iVar5,param_13,param_14,
                                 param_15,param_16);
      uVar3 = extraout_r4_00;
      for (iVar6 = 1; iVar6 < param_12; iVar6 = iVar6 + 1) {
        piVar1 = gnt4_HSD_JObjLoadJoint
                           (dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int *)*puVar7,uVar3,pfVar4,iVar5,param_13,param_14,param_15,param_16);
        if (piVar1 == (int *)0x0) {
          return;
        }
        if ((undefined4 *)puVar7[2] != (undefined4 *)0x0) {
          pfVar4 = *(float **)puVar7[2];
          iVar5 = 0;
          gnt4_HSD_JObjAddAnimAll
                    (dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar1,0,pfVar4,
                     (undefined4 *)0x0,param_13,param_14,param_15,param_16);
          dVar9 = (double)gnt4_HSD_JObjReqAnimAll();
        }
        dVar9 = (double)zz_02500b0_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    (int)piVar2,(int)piVar1,pfVar4,iVar5,param_13,param_14,param_15,
                                    param_16);
        uVar3 = extraout_r4_01;
        piVar2 = piVar1;
      }
      uVar8 = zz_0007c30_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                          uVar3,pfVar4,iVar5,param_13,param_14,param_15,param_16);
      zz_0007d40_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                  extraout_r4_02,pfVar4,iVar5,param_13,param_14,param_15,param_16);
      *(float **)(param_10 + 0x14) = param_11;
      *(undefined1 *)(param_10 + 0xb) = 0;
      *(undefined1 *)(param_10 + 0x10) = 1;
    }
  }
  return;
}



// ==== 800075cc  zz_00075cc_ ====

void zz_00075cc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,char *param_11
                ,undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  int *piVar1;
  
  piVar1 = gnt4_HSD_JObjLoadJoint
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int *)**(undefined4 **)(**(int **)(param_9 + 0x10) + (int)param_11 * 4),
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  if (piVar1 != (int *)0x0) {
    gnt4_HSD_JObjAddChild
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(int *)(param_10 + 0xc),(int)piVar1,param_11,param_12,param_13,param_14,param_15,
               param_16);
  }
  return;
}



// ==== 8000761c  zz_000761c_ ====

void zz_000761c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,char *param_11
                ,int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  undefined **ppuVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined8 uVar7;
  
  puVar6 = *(undefined4 **)(**(int **)(param_9 + 0x10) + (int)param_11 * 4);
  iVar5 = param_12;
  ppuVar1 = zz_02429e4_();
  uVar7 = zz_024298c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      &PTR_zz_008dae4__802da844,0x802e0000,param_11,iVar5,param_13,param_14,param_15
                      ,param_16);
  if (param_12 == 0) {
    param_12 = param_10 + 0x18;
  }
  uVar4 = extraout_r4;
  uVar2 = zz_008d780_(param_12);
  piVar3 = gnt4_HSD_JObjLoadJoint
                     (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar6,
                      uVar4,param_11,iVar5,param_13,param_14,param_15,param_16);
  if (piVar3 != (int *)0x0) {
    uVar7 = zz_024298c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppuVar1,uVar4,
                        param_11,iVar5,param_13,param_14,param_15,param_16);
    zz_008d780_(uVar2);
    gnt4_HSD_JObjAddChild
              (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(int *)(param_10 + 0xc),(int)piVar3,param_11,iVar5,param_13,param_14,param_15,
               param_16);
  }
  return;
}



// ==== 800076d0  zz_00076d0_ ====

/* WARNING: Removing unreachable block (ram,0x80007740) */

void zz_00076d0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,float *param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  
  iVar3 = *(int *)(param_9 + 0xc);
  if (iVar3 == 0) {
    param_11 = &DAT_80436a58;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x495,&DAT_80436a58,param_12,param_13,param_14,param_15
                               ,param_16);
  }
  if (param_10 == (float *)0x0) {
    param_11 = &DAT_80436a60;
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436a50,
                     0x496,&DAT_80436a60,param_12,param_13,param_14,param_15,param_16);
  }
  uVar4 = gnt4_PSMTXCopy_bl(param_10,(float *)(iVar3 + 0x44));
  *(uint *)(iVar3 + 0x14) = *(uint *)(iVar3 + 0x14) | 0x3800000;
  if (iVar3 != 0) {
    uVar2 = *(uint *)(iVar3 + 0x14);
    bVar1 = false;
    if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      gnt4_HSD_JObjSetMtxDirtySub_bl
                (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,uVar2,param_11,
                 param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80007794  zz_0007794_ ====

/* WARNING: Removing unreachable block (ram,0x800077d4) */

void zz_0007794_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,float *param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int *piVar3;
  
  piVar3 = *(int **)(param_9 + 0xc);
  if (piVar3 == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436a50,
                     0x47c,&DAT_80436a58,param_12,param_13,param_14,param_15,param_16);
  }
  else {
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
  }
  gnt4_PSMTXCopy_bl((float *)(piVar3 + 0x11),param_10);
  return;
}



// ==== 80007834  zz_0007834_ ====

/* WARNING: Removing unreachable block (ram,0x800078b4) */

void zz_0007834_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
                char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_9 + 0xc);
  if (iVar4 == 0) {
    param_11 = &DAT_80436a58;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x3a9,&DAT_80436a58,param_12,param_13,param_14,param_15
                               ,param_16);
  }
  if (param_10 == (undefined4 *)0x0) {
    param_11 = s_translate_802b01c8;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x3aa,s_translate_802b01c8,param_12,param_13,param_14,
                               param_15,param_16);
  }
  uVar2 = param_10[1];
  *(undefined4 *)(iVar4 + 0x38) = *param_10;
  *(undefined4 *)(iVar4 + 0x3c) = uVar2;
  *(undefined4 *)(iVar4 + 0x40) = param_10[2];
  if (((*(uint *)(iVar4 + 0x14) & 0x2000000) == 0) && (iVar4 != 0)) {
    uVar3 = *(uint *)(iVar4 + 0x14);
    bVar1 = false;
    if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      gnt4_HSD_JObjSetMtxDirtySub_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,uVar3,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80007908  zz_0007908_ ====

void zz_0007908_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0xc);
  if (iVar2 == 0) {
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x3e4,&DAT_80436a58,param_12,param_13,param_14,param_15
                               ,param_16);
  }
  if (param_10 == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436a50,
                     0x3e5,s_translate_802b01c8,param_12,param_13,param_14,param_15,param_16);
  }
  uVar1 = *(undefined4 *)(iVar2 + 0x3c);
  *param_10 = *(undefined4 *)(iVar2 + 0x38);
  param_10[1] = uVar1;
  param_10[2] = *(undefined4 *)(iVar2 + 0x40);
  return;
}



// ==== 80007988  zz_0007988_ ====

/* WARNING: Removing unreachable block (ram,0x80007a0c) */

void zz_0007988_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
                char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_9 + 0xc);
  if (iVar4 == 0) {
    param_11 = &DAT_80436a58;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x290,&DAT_80436a58,param_12,param_13,param_14,param_15
                               ,param_16);
  }
  if (param_10 == (undefined4 *)0x0) {
    param_11 = s_rotate_80436a64;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x291,s_rotate_80436a64,param_12,param_13,param_14,
                               param_15,param_16);
  }
  uVar2 = param_10[1];
  *(undefined4 *)(iVar4 + 0x1c) = *param_10;
  *(undefined4 *)(iVar4 + 0x20) = uVar2;
  uVar2 = param_10[3];
  *(undefined4 *)(iVar4 + 0x24) = param_10[2];
  *(undefined4 *)(iVar4 + 0x28) = uVar2;
  if (((*(uint *)(iVar4 + 0x14) & 0x2000000) == 0) && (iVar4 != 0)) {
    uVar3 = *(uint *)(iVar4 + 0x14);
    bVar1 = false;
    if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      gnt4_HSD_JObjSetMtxDirtySub_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,uVar3,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80007a60  zz_0007a60_ ====

void zz_0007a60_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0xc);
  if (iVar2 == 0) {
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x2dd,&DAT_80436a58,param_12,param_13,param_14,param_15
                               ,param_16);
  }
  if (param_10 == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436a50,
                     0x2de,s_rotate_80436a64,param_12,param_13,param_14,param_15,param_16);
  }
  uVar1 = *(undefined4 *)(iVar2 + 0x20);
  *param_10 = *(undefined4 *)(iVar2 + 0x1c);
  param_10[1] = uVar1;
  uVar1 = *(undefined4 *)(iVar2 + 0x28);
  param_10[2] = *(undefined4 *)(iVar2 + 0x24);
  param_10[3] = uVar1;
  return;
}



// ==== 80007ae4  zz_0007ae4_ ====

/* WARNING: Removing unreachable block (ram,0x80007b60) */

void zz_0007ae4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
                char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_9 + 0xc);
  if (iVar4 == 0) {
    param_11 = &DAT_80436a58;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x316,&DAT_80436a58,param_12,param_13,param_14,param_15
                               ,param_16);
  }
  if (param_10 == (undefined4 *)0x0) {
    param_11 = s_scale_80436a6c;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x317,s_scale_80436a6c,param_12,param_13,param_14,
                               param_15,param_16);
  }
  uVar2 = param_10[1];
  *(undefined4 *)(iVar4 + 0x2c) = *param_10;
  *(undefined4 *)(iVar4 + 0x30) = uVar2;
  *(undefined4 *)(iVar4 + 0x34) = param_10[2];
  if (((*(uint *)(iVar4 + 0x14) & 0x2000000) == 0) && (iVar4 != 0)) {
    uVar3 = *(uint *)(iVar4 + 0x14);
    bVar1 = false;
    if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      gnt4_HSD_JObjSetMtxDirtySub_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,uVar3,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80007bb4  zz_0007bb4_ ====

void zz_0007bb4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0xc);
  if (iVar2 == 0) {
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x351,&DAT_80436a58,param_12,param_13,param_14,param_15
                               ,param_16);
  }
  if (param_10 == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436a50,
                     0x352,s_scale_80436a6c,param_12,param_13,param_14,param_15,param_16);
  }
  uVar1 = *(undefined4 *)(iVar2 + 0x30);
  *param_10 = *(undefined4 *)(iVar2 + 0x2c);
  param_10[1] = uVar1;
  param_10[2] = *(undefined4 *)(iVar2 + 0x34);
  return;
}



// ==== 80007c30  zz_0007c30_ ====

void zz_0007c30_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  gnt4_HSD_JObjAnimAll
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
             *(int **)(param_9 + 0xc),param_10,param_11,param_12,param_13,param_14,param_15,param_16
            );
  return;
}



// ==== 80007c54  zz_0007c54_ ====

void zz_0007c54_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0008f18_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xc),0x60002001,(char *)0x400a,param_12,param_13,param_14,param_15,
              param_16);
  return;
}



// ==== 80007c84  zz_0007c84_ ====

void zz_0007c84_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                char *param_11,byte *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0009068_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xc),0,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80007cac  zz_0007cac_ ====

void zz_0007cac_(double param_1,int param_2)

{
  zz_00091e4_(param_1,*(int *)(param_2 + 0xc));
  return;
}



// ==== 80007cd0  zz_0007cd0_ ====

void zz_0007cd0_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  zz_00094b8_(*(int *)(param_1 + 0xc),param_2,param_3,param_4);
  return;
}



// ==== 80007cf4  zz_0007cf4_ ====

void zz_0007cf4_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  zz_00093d8_(*(int *)(param_1 + 0xc),param_2,param_3,param_4);
  return;
}



// ==== 80007d18  zz_0007d18_ ====

void zz_0007d18_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_024d570_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(undefined4 *)(param_9 + 0xc),8,param_11,param_12,param_13,param_14,param_15,param_16
             );
  return;
}



// ==== 80007d40  zz_0007d40_ ====

void zz_0007d40_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_024d570_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(undefined4 *)(param_9 + 0xc),0x14,param_11,param_12,param_13,param_14,param_15,
              param_16);
  return;
}



// ==== 80007d68  zz_0007d68_ ====

void zz_0007d68_(int param_1,int param_2)

{
  zz_00092bc_(*(int *)(param_1 + 0xc),param_2);
  return;
}



// ==== 80007d8c  zz_0007d8c_ ====

void zz_0007d8c_(int param_1,int param_2)

{
  zz_0009690_(*(int *)(param_1 + 0xc),param_2);
  return;
}



// ==== 80007db0  FUN_80007db0 ====

/* WARNING: Removing unreachable block (ram,0x80007e20) */

void FUN_80007db0(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  
  iVar3 = *(int *)(param_9 + 0xc);
  dVar4 = param_1;
  if (iVar3 == 0) {
    param_11 = &DAT_80436a58;
    param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80436a50,0x2b8,&DAT_80436a58,param_12,param_13,
                                       param_14,param_15,param_16);
  }
  if ((*(uint *)(iVar3 + 0x14) & 0x20000) != 0) {
    param_11 = s___jobj_>flags___JOBJ_USE_QUATERN_802b01d4;
    param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80436a50,0x2b9,
                                       s___jobj_>flags___JOBJ_USE_QUATERN_802b01d4,param_12,param_13
                                       ,param_14,param_15,param_16);
  }
  *(float *)(iVar3 + 0x20) = (float)dVar4;
  if (((*(uint *)(iVar3 + 0x14) & 0x2000000) == 0) && (iVar3 != 0)) {
    uVar2 = *(uint *)(iVar3 + 0x14);
    bVar1 = false;
    if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      gnt4_HSD_JObjSetMtxDirtySub_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,uVar2,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80007e74  zz_0007e74_ ====

/* WARNING: Removing unreachable block (ram,0x80007ee4) */

void zz_0007e74_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  
  iVar3 = *(int *)(param_9 + 0xc);
  dVar4 = param_1;
  if (iVar3 == 0) {
    param_11 = &DAT_80436a58;
    param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80436a50,0x2cc,&DAT_80436a58,param_12,param_13,
                                       param_14,param_15,param_16);
  }
  if ((*(uint *)(iVar3 + 0x14) & 0x20000) != 0) {
    param_11 = s___jobj_>flags___JOBJ_USE_QUATERN_802b01d4;
    param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80436a50,0x2cd,
                                       s___jobj_>flags___JOBJ_USE_QUATERN_802b01d4,param_12,param_13
                                       ,param_14,param_15,param_16);
  }
  *(float *)(iVar3 + 0x24) = (float)dVar4;
  if (((*(uint *)(iVar3 + 0x14) & 0x2000000) == 0) && (iVar3 != 0)) {
    uVar2 = *(uint *)(iVar3 + 0x14);
    bVar1 = false;
    if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      gnt4_HSD_JObjSetMtxDirtySub_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,uVar2,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80007f38  zz_0007f38_ ====

void zz_0007f38_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0009598_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xc),param_10,param_11,param_12,param_13,param_14,param_15,param_16
             );
  return;
}



// ==== 80007f5c  zz_0007f5c_ ====

void zz_0007f5c_(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = gnt4_HSD_JObjGetDObj(param_1);
  while (iVar1 != 0) {
    if (iVar1 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar1 + 8);
    }
    if (iVar2 != 0) {
      for (iVar2 = gnt4_HSD_MObjGetTObj_bl(iVar2); iVar2 != 0; iVar2 = zz_0240c28_(iVar2)) {
        if ((*(int **)(iVar2 + 0x58) != (int *)0x0) && (**(int **)(iVar2 + 0x58) != 0)) {
          *(undefined4 *)(iVar2 + 0x58) = param_2;
        }
      }
    }
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(iVar1 + 4);
    }
  }
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_1 + 0x10);
  }
  while (iVar1 != 0) {
    zz_0007f5c_(iVar1,param_2);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(iVar1 + 8);
    }
  }
  return;
}



// ==== 8000804c  zz_000804c_ ====

void zz_000804c_(int param_1,int param_2,int *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  bVar1 = false;
  iVar6 = *(int *)(param_1 + 0xc);
  iVar3 = gnt4_HSD_JObjGetDObj(iVar6);
  while ((iVar3 != 0 && (!bVar1))) {
    if (iVar3 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = *(int *)(iVar3 + 8);
    }
    if (iVar4 != 0) {
      iVar4 = gnt4_HSD_MObjGetTObj_bl(iVar4);
      while ((iVar4 != 0 && (!bVar1))) {
        piVar5 = *(int **)(iVar4 + 0x58);
        if ((piVar5 != (int *)0x0) && (*piVar5 != 0)) {
          iVar2 = piVar5[1];
          bVar1 = true;
          *param_3 = *piVar5;
          param_3[1] = iVar2;
          iVar2 = piVar5[3];
          param_3[2] = piVar5[2];
          param_3[3] = iVar2;
          iVar2 = piVar5[5];
          param_3[4] = piVar5[4];
          param_3[5] = iVar2;
        }
        iVar4 = zz_0240c28_(iVar4);
      }
    }
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(iVar3 + 4);
    }
  }
  if (bVar1) {
    *param_3 = param_2;
    zz_0007f5c_(iVar6,param_3);
  }
  return;
}



// ==== 8000814c  zz_000814c_ ====

void zz_000814c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,float *param_10,
                int param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  dVar2 = (double)*param_10;
  if (dVar2 < (double)FLOAT_80436a74) {
    iVar1 = *(int *)(param_9 + 0x7c);
    if (iVar1 == 0) {
      if (param_9 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(param_9 + 0x10);
      }
      while (iVar1 != 0) {
        dVar2 = (double)zz_000814c_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    iVar1,param_10,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
        if (iVar1 == 0) {
          iVar1 = 0;
        }
        else {
          iVar1 = *(int *)(iVar1 + 8);
        }
      }
    }
    else if (param_11 == 0) {
      if (iVar1 == 0) {
        gnt4___assert_bl(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436a78
                         ,0x95,&DAT_80436a80,param_12,param_13,param_14,param_15,param_16);
      }
      *param_10 = *(float *)(iVar1 + 4);
    }
    else {
      if (iVar1 == 0) {
        gnt4___assert_bl(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436a78
                         ,0xab,&DAT_80436a80,param_12,param_13,param_14,param_15,param_16);
      }
      *param_10 = *(float *)(iVar1 + 0xc);
    }
  }
  return;
}



// ==== 80008238  zz_0008238_ ====

void zz_0008238_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,float *param_10,
                int param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*param_10;
  if (dVar4 < (double)FLOAT_80436a74) {
    iVar1 = gnt4_HSD_JObjGetDObj(param_9);
    while (iVar1 != 0) {
      if (iVar1 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar1 + 8);
      }
      if (iVar2 != 0) {
        iVar3 = *(int *)(iVar2 + 0x14);
        if (iVar3 == 0) {
          for (iVar2 = gnt4_HSD_MObjGetTObj_bl(iVar2); iVar2 != 0; iVar2 = zz_0240c28_(iVar2)) {
            iVar3 = *(int *)(iVar2 + 100);
            if (iVar3 != 0) {
              if (param_11 == 0) {
                if (iVar3 == 0) {
                  dVar4 = (double)gnt4___assert_bl(dVar4,param_2,param_3,param_4,param_5,param_6,
                                                   param_7,param_8,&DAT_80436a78,0x95,&DAT_80436a80,
                                                   param_12,param_13,param_14,param_15,param_16);
                }
                *param_10 = *(float *)(iVar3 + 4);
              }
              else {
                if (iVar3 == 0) {
                  dVar4 = (double)gnt4___assert_bl(dVar4,param_2,param_3,param_4,param_5,param_6,
                                                   param_7,param_8,&DAT_80436a78,0xab,&DAT_80436a80,
                                                   param_12,param_13,param_14,param_15,param_16);
                }
                *param_10 = *(float *)(iVar3 + 0xc);
              }
            }
          }
        }
        else if (param_11 == 0) {
          if (iVar3 == 0) {
            dVar4 = (double)gnt4___assert_bl(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,
                                             param_8,&DAT_80436a78,0x95,&DAT_80436a80,param_12,
                                             param_13,param_14,param_15,param_16);
          }
          *param_10 = *(float *)(iVar3 + 4);
        }
        else {
          if (iVar3 == 0) {
            dVar4 = (double)gnt4___assert_bl(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,
                                             param_8,&DAT_80436a78,0xab,&DAT_80436a80,param_12,
                                             param_13,param_14,param_15,param_16);
          }
          *param_10 = *(float *)(iVar3 + 0xc);
        }
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 0x10);
    }
    while (iVar1 != 0) {
      dVar4 = (double)zz_0008238_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  iVar1,param_10,param_11,param_12,param_13,param_14,param_15,
                                  param_16);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 800083d4  zz_00083d4_ ====

void zz_00083d4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,float *param_10,
                int param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*param_10;
  if (dVar4 < (double)FLOAT_80436a74) {
    iVar1 = gnt4_HSD_JObjGetDObj(param_9);
    while (iVar1 != 0) {
      if (iVar1 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar1 + 0xc);
      }
      while (iVar2 != 0) {
        iVar3 = *(int *)(iVar2 + 0x18);
        if (iVar3 != 0) {
          if (param_11 == 0) {
            if (iVar3 == 0) {
              dVar4 = (double)gnt4___assert_bl(dVar4,param_2,param_3,param_4,param_5,param_6,param_7
                                               ,param_8,&DAT_80436a78,0x95,&DAT_80436a80,param_12,
                                               param_13,param_14,param_15,param_16);
            }
            *param_10 = *(float *)(iVar3 + 4);
          }
          else {
            if (iVar3 == 0) {
              dVar4 = (double)gnt4___assert_bl(dVar4,param_2,param_3,param_4,param_5,param_6,param_7
                                               ,param_8,&DAT_80436a78,0xab,&DAT_80436a80,param_12,
                                               param_13,param_14,param_15,param_16);
            }
            *param_10 = *(float *)(iVar3 + 0xc);
          }
        }
        if (iVar2 == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(iVar2 + 4);
        }
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 0x10);
    }
    while (iVar1 != 0) {
      dVar4 = (double)zz_00083d4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  iVar1,param_10,param_11,param_12,param_13,param_14,param_15,
                                  param_16);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 8000850c  zz_000850c_ ====

double zz_000850c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                  double param_6,double param_7,double param_8,int param_9,int param_10,
                  undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                  undefined4 param_15,undefined4 param_16)

{
  float local_8 [2];
  
  local_8[0] = FLOAT_80436a88;
  if (param_10 == 1) {
    zz_0008238_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xc),local_8,1,param_12,param_13,param_14,param_15,param_16);
  }
  else if (param_10 < 1) {
    if (-1 < param_10) {
      zz_000814c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xc),local_8,1,param_12,param_13,param_14,param_15,param_16);
    }
  }
  else if (param_10 < 3) {
    zz_00083d4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xc),local_8,1,param_12,param_13,param_14,param_15,param_16);
  }
  return (double)local_8[0];
}



// ==== 80008590  zz_0008590_ ====

double zz_0008590_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                  double param_6,double param_7,double param_8,int param_9,int param_10,
                  undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                  undefined4 param_15,undefined4 param_16)

{
  float local_8 [2];
  
  local_8[0] = FLOAT_80436a88;
  if (param_10 == 1) {
    zz_0008238_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xc),local_8,0,param_12,param_13,param_14,param_15,param_16);
  }
  else if (param_10 < 1) {
    if (-1 < param_10) {
      zz_000814c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xc),local_8,0,param_12,param_13,param_14,param_15,param_16);
    }
  }
  else if (param_10 < 3) {
    zz_00083d4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xc),local_8,0,param_12,param_13,param_14,param_15,param_16);
  }
  return (double)local_8[0];
}



// ==== 80008614  zz_0008614_ ====

undefined4
zz_0008614_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
           double param_6,double param_7,double param_8,int param_9,int param_10,undefined4 param_11
           ,undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
           undefined4 param_16)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined8 uVar4;
  
  uVar2 = 0;
  iVar3 = *(int *)(**(int **)(param_9 + 0x10) + *(int *)(param_10 + 0x14) * 4);
  if (*(int *)(param_10 + 0xc) != 0) {
    uVar4 = zz_024d570_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_10 + 0xc),8,param_11,param_12,param_13,param_14,param_15,
                        param_16);
    puVar1 = *(undefined4 **)(iVar3 + 0xc);
    if (puVar1 != (undefined4 *)0x0) {
      gnt4_HSD_JObjAddAnimAll
                (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                 *(undefined4 *)(param_10 + 0xc),0,(undefined4 *)0x0,(undefined4 *)*puVar1,param_13,
                 param_14,param_15,param_16);
      gnt4_HSD_JObjReqAnimAll();
      uVar2 = 1;
    }
  }
  return uVar2;
}



// ==== 800086b8  zz_00086b8_ ====

void zz_00086b8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar2 = *(int *)(**(int **)(param_9 + 0x10) + *(int *)(param_10 + 0x14) * 4);
  if (*(int *)(param_10 + 0xc) != 0) {
    uVar3 = zz_0007d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,param_12,
                        param_13,param_14,param_15,param_16);
    puVar1 = *(undefined4 **)(iVar2 + 8);
    if (puVar1 != (undefined4 *)0x0) {
      gnt4_HSD_JObjAddAnimAll
                (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                 *(undefined4 *)(param_10 + 0xc),0,(undefined4 *)*puVar1,(undefined4 *)0x0,param_13,
                 param_14,param_15,param_16);
      gnt4_HSD_JObjReqAnimAll();
    }
  }
  return;
}



// ==== 80008744  zz_0008744_ ====

void zz_0008744_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar2 = *(int *)(**(int **)(param_9 + 0x10) + *(int *)(param_10 + 0x14) * 4);
  if (*(int *)(param_10 + 0xc) != 0) {
    uVar3 = zz_024d570_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_10 + 0xc),1,param_11,param_12,param_13,param_14,param_15,
                        param_16);
    puVar1 = *(undefined4 **)(iVar2 + 4);
    if (puVar1 != (undefined4 *)0x0) {
      gnt4_HSD_JObjAddAnimAll
                (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                 *(undefined4 *)(param_10 + 0xc),*puVar1,(undefined4 *)0x0,(undefined4 *)0x0,
                 param_13,param_14,param_15,param_16);
      gnt4_HSD_JObjReqAnimAll();
    }
  }
  return;
}



// ==== 800087d4  zz_00087d4_ ====

void zz_00087d4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined8 uVar6;
  
  iVar5 = *(int *)(**(int **)(param_9 + 0x10) + *(int *)(param_10 + 0x14) * 4);
  if (*(int *)(param_10 + 0xc) != 0) {
    uVar6 = zz_024d814_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,param_12,
                        param_13,param_14,param_15,param_16);
    puVar1 = *(undefined4 **)(iVar5 + 4);
    if (((puVar1 != (undefined4 *)0x0) || (*(int *)(iVar5 + 8) != 0)) ||
       (*(int *)(iVar5 + 0xc) != 0)) {
      uVar2 = 0;
      puVar3 = (undefined4 *)0x0;
      puVar4 = (undefined4 *)0x0;
      if (puVar1 != (undefined4 *)0x0) {
        uVar2 = *puVar1;
      }
      if (*(undefined4 **)(iVar5 + 8) != (undefined4 *)0x0) {
        puVar3 = (undefined4 *)**(undefined4 **)(iVar5 + 8);
      }
      if (*(undefined4 **)(iVar5 + 0xc) != (undefined4 *)0x0) {
        puVar4 = (undefined4 *)**(undefined4 **)(iVar5 + 0xc);
      }
      gnt4_HSD_JObjAddAnimAll
                (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                 *(undefined4 *)(param_10 + 0xc),uVar2,puVar3,puVar4,param_13,param_14,param_15,
                 param_16);
      gnt4_HSD_JObjReqAnimAll();
    }
  }
  return;
}



// ==== 800088a4  zz_00088a4_ ====

void zz_00088a4_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  int *piVar1;
  undefined8 uVar2;
  
  piVar1 = *(int **)(*(int *)(param_9 + 0x10) + 4);
  if ((*piVar1 != 0) && (*(int *)piVar1[1] != 0)) {
    uVar2 = zz_0248424_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)DAT_80436210,*piVar1,param_11,param_12,param_13,param_14,param_15,
                        param_16);
    zz_024631c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_80436210,
                *(undefined4 **)piVar1[1],param_11,param_12,param_13,param_14,param_15,param_16);
    uVar2 = zz_024652c_(param_1,(int)DAT_80436210);
    zz_02464dc_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436210,
                extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80008924  zz_0008924_ ====

void zz_0008924_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_02462c4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436210,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80008948  zz_0008948_ ====

void zz_0008948_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,float *param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  gnt4_HSD_CObjGetViewingMtx_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436210,param_9,
             param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80008970  zz_0008970_ ====

void zz_0008970_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10
                ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  gnt4_HSD_CObjGetEyePosition_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436210,param_9,
             param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80008998  cCameraManager::HasCamera(cBaseCamera ====

void cCameraManager__HasCamera_cBaseCamera
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  gnt4_HSD_CObjGetInterest_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436210,param_9,
             param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800089c0  zz_00089c0_ ====

void zz_00089c0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,float *param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = gnt4_HSD_CObjGetUpVector_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436210,
                     param_9,param_11,param_12,param_13,param_14,param_15,param_16);
  fVar1 = DAT_802b0cb8;
  if (iVar3 == 0) {
    *param_9 = DAT_802b0cb4;
    fVar2 = DAT_802b0cbc;
    param_9[1] = fVar1;
    param_9[2] = fVar2;
  }
  return;
}



// ==== 80008a1c  zz_0008a1c_ ====

/* WARNING: Removing unreachable block (ram,0x80008a48) */

double zz_0008a1c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                  double param_6,double param_7,double param_8)

{
  float fVar1;
  
  fVar1 = FLOAT_80436a74;
  if (*(int *)(DAT_80436210 + 0x84) != 0) {
    fVar1 = *(float *)(*(int *)(DAT_80436210 + 0x84) + 0xc);
  }
  return (double)fVar1;
}



// ==== 80008a70  SidelineExplodableManager::GetNumExplodables(void) ====

void SidelineExplodableManager__GetNumExplodables_void_(void)

{
  gnt4_HSD_CObjGetFov_bl(DAT_80436210);
  return;
}



// ==== 80008a94  zz_0008a94_ ====

void zz_0008a94_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  undefined4 extraout_r4_00;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  
  uVar7 = zz_0008b58_();
  iVar5 = *(int *)(param_9 + 0x10);
  puVar1 = (undefined4 *)**(int **)(iVar5 + 8);
  if (puVar1 != (undefined4 *)0x0) {
    uVar3 = extraout_r4;
    DAT_8043620c = gnt4_HSD_LObjLoadDesc_bl
                             (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (int *)*puVar1,extraout_r4,(int)param_11,param_12,param_13,param_14,
                              param_15,param_16);
    iVar4 = DAT_8043620c;
    for (iVar6 = 4; puVar1 = *(undefined4 **)(*(int *)(iVar5 + 8) + iVar6),
        puVar1 != (undefined4 *)0x0; iVar6 = iVar6 + 4) {
      iVar2 = gnt4_HSD_LObjLoadDesc_bl
                        (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         (int *)*puVar1,uVar3,(int)param_11,param_12,param_13,param_14,param_15,
                         param_16);
      if ((*(ushort *)(iVar2 + 8) & 3) == 1) {
        DAT_80436208 = iVar2;
      }
      if (iVar4 == 0) {
        param_11 = &DAT_80436a94;
        uVar7 = gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80436a8c,0x12d,&DAT_80436a94,param_12,param_13,param_14,
                                 param_15,param_16);
        uVar3 = extraout_r4_00;
      }
      *(int *)(iVar4 + 0xc) = iVar2;
      iVar4 = iVar2;
    }
  }
  return;
}



// ==== 80008b58  zz_0008b58_ ====

void zz_0008b58_(void)

{
  if (DAT_8043620c != (int *)0x0) {
    gnt4_HSD_LObjRemoveAll_bl(DAT_8043620c);
    DAT_8043620c = (int *)0x0;
    DAT_80436208 = 0;
  }
  return;
}



// ==== 80008b90  zz_0008b90_ ====

void zz_0008b90_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  undefined4 extraout_r4_00;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined8 uVar9;
  
  uVar9 = zz_0008c40_();
  iVar6 = *(int *)(param_9 + 0x10);
  piVar8 = &DAT_803bb460;
  iVar5 = 0;
  iVar7 = 0;
  uVar4 = extraout_r4;
  do {
    puVar1 = (undefined4 *)**(int **)(iVar6 + 8);
    if (puVar1 != (undefined4 *)0x0) {
      iVar2 = gnt4_HSD_LObjLoadDesc_bl
                        (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         (int *)*puVar1,uVar4,(int)param_11,param_12,param_13,param_14,param_15,
                         param_16);
      *piVar8 = iVar2;
      puVar1 = *(undefined4 **)(*(int *)(iVar6 + 8) + iVar7 + 4);
      if (puVar1 != (undefined4 *)0x0) {
        iVar3 = gnt4_HSD_LObjLoadDesc_bl
                          (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           (int *)*puVar1,uVar4,(int)param_11,param_12,param_13,param_14,param_15,
                           param_16);
        if (iVar2 == 0) {
          param_11 = &DAT_80436a94;
          uVar9 = gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_80436a8c,0x12d,&DAT_80436a94,param_12,param_13,param_14,
                                   param_15,param_16);
          uVar4 = extraout_r4_00;
        }
        *(int *)(iVar2 + 0xc) = iVar3;
      }
    }
    iVar5 = iVar5 + 1;
    iVar7 = iVar7 + 4;
    piVar8 = piVar8 + 1;
  } while (iVar5 < 4);
  return;
}



// ==== 80008c40  zz_0008c40_ ====

void zz_0008c40_(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_803bb460;
  iVar1 = 0;
  do {
    if ((int *)*puVar2 != (int *)0x0) {
      gnt4_HSD_LObjRemoveAll_bl((int *)*puVar2);
      *puVar2 = 0;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 4);
  return;
}



// ==== 80008ca8  zz_0008ca8_ ====

void zz_0008ca8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  uVar1 = zz_0008cf4_();
  if (*(char *)(param_9 + 0x19) != '\0') {
    DAT_80436204 = gnt4_HSD_FogLoadDesc_bl
                             (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (undefined4 *)**(undefined4 **)(*(int *)(param_9 + 0x10) + 0xc),
                              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80008cf4  zz_0008cf4_ ====

void zz_0008cf4_(void)

{
  ushort uVar1;
  int *piVar2;
  uint uVar3;
  
  piVar2 = DAT_80436204;
  if (DAT_80436204 != (int *)0x0) {
    uVar1 = *(ushort *)(DAT_80436204 + 1);
    uVar3 = countLeadingZeros(0xffff - (uint)uVar1);
    uVar3 = uVar3 >> 5;
    if (uVar3 == 0) {
      uVar3 = countLeadingZeros((uint)uVar1);
      *(ushort *)(DAT_80436204 + 1) = uVar1 - 1;
      uVar3 = uVar3 >> 5;
    }
    if ((uVar3 != 0) && (piVar2 != (int *)0x0)) {
      (**(code **)(*piVar2 + 0x30))(piVar2);
      (**(code **)(*piVar2 + 0x34))(piVar2);
    }
    DAT_80436204 = (int *)0x0;
  }
  return;
}



// ==== 80008d9c  zz_0008d9c_ ====

/* WARNING: Removing unreachable block (ram,0x80008ecc) */
/* WARNING: Removing unreachable block (ram,0x80008ec4) */
/* WARNING: Removing unreachable block (ram,0x80008ebc) */
/* WARNING: Removing unreachable block (ram,0x80008dbc) */
/* WARNING: Removing unreachable block (ram,0x80008db4) */
/* WARNING: Removing unreachable block (ram,0x80008dac) */

void zz_0008d9c_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  if (param_9 != 0) {
    dVar4 = param_1;
    iVar1 = gnt4_HSD_JObjGetDObj(param_9);
    dVar6 = (double)FLOAT_80436a74;
    while (iVar1 != 0) {
      dVar5 = dVar4;
      if (iVar1 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar1 + 0xc);
      }
      while (iVar2 != 0) {
        iVar3 = *(int *)(iVar2 + 0x18);
        if (iVar3 != 0) {
          if (dVar5 < dVar6) {
            if (iVar3 == 0) {
              param_11 = &DAT_80436a80;
              gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a78,0xab,&DAT_80436a80,param_12,param_13,param_14,param_15,
                               param_16);
            }
            dVar5 = (double)(float)(dVar4 + (double)*(float *)(iVar3 + 0xc));
          }
          param_1 = (double)zz_0243fc0_(dVar5,*(int *)(iVar2 + 0x18));
          param_10 = extraout_r4;
        }
        if (iVar2 == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(iVar2 + 4);
        }
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 0x10);
    }
    while (iVar1 != 0) {
      zz_0008d9c_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      param_10 = extraout_r4_00;
      if (param_9 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(param_9 + 8);
      }
    }
  }
  return;
}



// ==== 80008ef4  FUN_80008ef4 ====

void FUN_80008ef4(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_0008d9c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xc),param_10,param_11,param_12,param_13,param_14,param_15,param_16
             );
  return;
}



// ==== 80008f18  zz_0008f18_ ====

void zz_0008f18_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,uint param_10,
                char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  byte *pbVar2;
  undefined4 extraout_r4_00;
  undefined4 uVar3;
  char *pcVar4;
  int *piVar5;
  undefined8 uVar6;
  
  if ((param_9 != 0) && ((*(uint *)(param_9 + 0x14) & 0x1000) == 0)) {
    pcVar4 = param_11;
    uVar6 = gnt4_HSD_JObjSetFlags
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       0x20080000,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar6 = gnt4_HSD_JObjClearFlags
                      (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       0x50140000,pcVar4,param_12,param_13,param_14,param_15,param_16);
    iVar1 = gnt4_HSD_JObjGetDObj(param_9);
    while (iVar1 != 0) {
      gnt4_HSD_DObjSetFlags_bl(iVar1,4);
      uVar6 = gnt4_HSD_DObjClearFlags_bl(iVar1,10);
      if (iVar1 == 0) {
        piVar5 = (int *)0x0;
      }
      else {
        piVar5 = *(int **)(iVar1 + 8);
      }
      uVar3 = extraout_r4;
      if (piVar5 != (int *)0x0) {
        gnt4_HSD_MObjSetFlags_bl((int)piVar5,param_10);
        uVar6 = zz_02422c4_((int)piVar5,(uint)param_11);
        pbVar2 = (byte *)piVar5[4];
        if (pbVar2 != (byte *)0x0) {
          *pbVar2 = *pbVar2 & 0xdf;
          *(undefined1 *)(piVar5[4] + 9) = 7;
        }
        uVar6 = gnt4_HSD_MObjCompileTev_bl
                          (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar5,
                           pbVar2,pcVar4,param_12,param_13,param_14,param_15,param_16);
        uVar3 = extraout_r4_00;
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        uVar6 = gnt4_HSD_MObjCompileTev_bl
                          (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int **)(iVar1 + 8),uVar3,pcVar4,param_12,param_13,param_14,param_15,
                           param_16);
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 0x10);
    }
    while (iVar1 != 0) {
      uVar6 = zz_0008f18_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                          param_10,param_11,param_12,param_13,param_14,param_15,param_16);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 80009068  zz_0009068_ ====

void zz_0009068_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                char *param_11,byte *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  undefined4 extraout_r4_01;
  int *piVar3;
  undefined8 uVar4;
  
  if ((param_9 != 0) && ((*(uint *)(param_9 + 0x14) & 0x1000) == 0)) {
    uVar4 = gnt4_HSD_JObjSetFlags
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       0x20080000,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar4 = gnt4_HSD_JObjClearFlags
                      (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       0x50140000,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar1 = gnt4_HSD_JObjGetDObj(param_9);
    while (iVar1 != 0) {
      gnt4_HSD_DObjSetFlags_bl(iVar1,4);
      uVar4 = gnt4_HSD_DObjClearFlags_bl(iVar1,10);
      if (iVar1 == 0) {
        piVar3 = (int *)0x0;
      }
      else {
        piVar3 = *(int **)(iVar1 + 8);
      }
      uVar2 = extraout_r4;
      if (piVar3 != (int *)0x0) {
        gnt4_HSD_MObjSetFlags_bl((int)piVar3,0x40002001);
        uVar4 = zz_02422c4_((int)piVar3,0x20004008);
        param_12 = (byte *)piVar3[4];
        uVar2 = extraout_r4_00;
        if (param_12 != (byte *)0x0) {
          param_11 = (char *)0x4;
          uVar2 = 5;
          *param_12 = *param_12 & 0xdf;
          *(undefined1 *)(piVar3[4] + 5) = 4;
          *(undefined1 *)(piVar3[4] + 6) = 5;
          *(undefined1 *)(piVar3[4] + 9) = 7;
        }
        uVar4 = gnt4_HSD_MObjCompileTev_bl
                          (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,
                           uVar2,param_11,param_12,param_13,param_14,param_15,param_16);
        uVar2 = extraout_r4_01;
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        uVar4 = gnt4_HSD_MObjCompileTev_bl
                          (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int **)(iVar1 + 8),uVar2,param_11,param_12,param_13,param_14,param_15,
                           param_16);
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 0x10);
    }
    while (iVar1 != 0) {
      uVar4 = zz_0009068_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                          param_10,param_11,param_12,param_13,param_14,param_15,param_16);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 800091e4  zz_00091e4_ ====

void zz_00091e4_(double param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if ((param_2 != 0) && ((*(uint *)(param_2 + 0x14) & 0x1000) == 0)) {
    iVar1 = gnt4_HSD_JObjGetDObj(param_2);
    while (iVar1 != 0) {
      if (iVar1 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar1 + 8);
      }
      if (iVar2 != 0) {
        zz_02437c8_(param_1,iVar2);
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
    if (param_2 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_2 + 0x10);
    }
    while (iVar1 != 0) {
      zz_00091e4_(param_1,iVar1);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 800092bc  zz_00092bc_ ====

void zz_00092bc_(int param_1,int param_2)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  
  if ((param_1 != 0) && ((*(uint *)(param_1 + 0x14) & 0x1000) == 0)) {
    uVar2 = 0;
    if (param_2 == 0) {
      uVar2 = 0x8000;
    }
    else if (param_2 == 1) {
      uVar2 = 0x4000;
    }
    iVar1 = gnt4_HSD_JObjGetDObj(param_1);
    while (iVar1 != 0) {
      if (iVar1 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar1 + 0xc);
      }
      while (iVar3 != 0) {
        zz_024a4d0_(iVar3,0xc000);
        zz_024a4b8_(iVar3,uVar2);
        if (iVar3 == 0) {
          iVar3 = 0;
        }
        else {
          iVar3 = *(int *)(iVar3 + 4);
        }
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
    if (param_1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_1 + 0x10);
    }
    while (iVar1 != 0) {
      zz_00092bc_(iVar1,param_2);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 800093d8  zz_00093d8_ ====

void zz_00093d8_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if ((param_1 != 0) && ((*(uint *)(param_1 + 0x14) & 0x1000) == 0)) {
    iVar1 = gnt4_HSD_JObjGetDObj(param_1);
    while (iVar1 != 0) {
      if (iVar1 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar1 + 8);
      }
      if (iVar2 != 0) {
        zz_0243768_(iVar2,(char)param_2,(char)param_3,(char)param_4);
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
    if (param_1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_1 + 0x10);
    }
    while (iVar1 != 0) {
      zz_00093d8_(iVar1,param_2,param_3,param_4);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 800094b8  zz_00094b8_ ====

void zz_00094b8_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if ((param_1 != 0) && ((*(uint *)(param_1 + 0x14) & 0x1000) == 0)) {
    iVar1 = gnt4_HSD_JObjGetDObj(param_1);
    while (iVar1 != 0) {
      if (iVar1 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar1 + 8);
      }
      if (iVar2 != 0) {
        zz_0243798_(iVar2,(char)param_2,(char)param_3,(char)param_4);
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
    if (param_1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_1 + 0x10);
    }
    while (iVar1 != 0) {
      zz_00094b8_(iVar1,param_2,param_3,param_4);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 80009598  zz_0009598_ ====

void zz_0009598_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  int *piVar2;
  undefined8 uVar3;
  
  if ((param_9 != 0) && ((*(uint *)(param_9 + 0x14) & 0x1000) == 0)) {
    iVar1 = gnt4_HSD_JObjGetDObj(param_9);
    while (iVar1 != 0) {
      if (iVar1 == 0) {
        piVar2 = (int *)0x0;
      }
      else {
        piVar2 = *(int **)(iVar1 + 8);
      }
      if (piVar2 != (int *)0x0) {
        uVar3 = gnt4_HSD_TObjRemoveAll_bl((int *)piVar2[2]);
        piVar2[2] = 0;
        param_1 = gnt4_HSD_MObjCompileTev_bl
                            (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,
                             extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
        param_10 = extraout_r4_00;
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        param_1 = gnt4_HSD_MObjCompileTev_bl
                            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             *(int **)(iVar1 + 8),param_10,param_11,param_12,param_13,param_14,
                             param_15,param_16);
        iVar1 = *(int *)(iVar1 + 4);
        param_10 = extraout_r4_01;
      }
    }
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 0x10);
    }
    while (iVar1 != 0) {
      param_1 = zz_0009598_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                            param_10,param_11,param_12,param_13,param_14,param_15,param_16);
      param_10 = extraout_r4_02;
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 80009690  zz_0009690_ ====

void zz_0009690_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if ((param_1 != 0) && ((*(uint *)(param_1 + 0x14) & 0x1000) == 0)) {
    iVar1 = gnt4_HSD_JObjGetDObj(param_1);
    while (iVar1 != 0) {
      if (iVar1 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar1 + 8);
      }
      if (iVar2 != 0) {
        if (*(int *)(iVar2 + 0x10) == 0) {
          if (param_2 == 7) {
            gnt4_HSD_MObjSetFlags_bl(iVar2,0x8000000);
          }
          else {
            zz_02422c4_(iVar2,0x8000000);
          }
        }
        else {
          *(char *)(*(int *)(iVar2 + 0x10) + 8) = (char)param_2;
        }
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
    if (param_1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_1 + 0x10);
    }
    while (iVar1 != 0) {
      zz_0009690_(iVar1,param_2);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 80009790  zz_0009790_ ====

void zz_0009790_(void)

{
  DAT_803bb150 = 0;
  DAT_803bb154 = 0;
  DAT_803bb158 = 0;
  DAT_803bb15c = 0;
  DAT_803bb160 = 0;
  DAT_803bb164 = 0;
  return;
}



// ==== 800097b4  zz_00097b4_ ====

void zz_00097b4_(int param_1,uint param_2)

{
  int iVar1;
  
  *(undefined4 *)(param_1 + 0x20) = 0;
  if ((param_2 & 1) != 0) {
    *(int *)(param_1 + 0x20) = DAT_803bb150;
    DAT_803bb150 = param_1;
  }
  *(undefined4 *)(param_1 + 0x24) = 0;
  if ((param_2 & 2) != 0) {
    *(int *)(param_1 + 0x24) = DAT_803bb154;
    DAT_803bb154 = param_1;
  }
  *(undefined4 *)(param_1 + 0x28) = 0;
  if ((param_2 & 0x7c) == 0) {
    return;
  }
  iVar1 = *(int *)(&DAT_802c37c8 + (param_2 >> 2 & 0x3ffffffc));
  *(undefined4 *)(param_1 + 0x28) = (&DAT_803bb158)[iVar1];
  (&DAT_803bb158)[iVar1] = param_1;
  return;
}



// ==== 80009838  zz_0009838_ ====

void zz_0009838_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,float param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  undefined *extraout_r4;
  undefined4 extraout_r4_00;
  undefined *extraout_r4_01;
  undefined *extraout_r4_02;
  undefined *extraout_r4_03;
  undefined *extraout_r4_04;
  float *pfVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  uint uVar6;
  undefined8 uVar7;
  
  uVar6 = 1;
  pfVar2 = (float *)(param_9 * 8);
  puVar1 = &DAT_802c37e8;
  pfVar5 = (float *)pfVar2[-0x1ff4f206];
  fVar3 = pfVar2[-0x1ff4f205];
  if (DAT_80436204 == 0) {
    uVar6 = 0xffffffff;
    param_1 = (double)gnt4_HSD_FogSet_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                         param_8,0,&DAT_802c37e8,pfVar2,param_12,param_13,param_14,
                                         param_15,param_16);
    puVar1 = extraout_r4;
  }
  iVar4 = (&DAT_803bb150)[param_9];
  if ((iVar4 != 0) && (DAT_8043620c != (int *)0x0)) {
    uVar7 = zz_0245398_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_8043620c
                        ,puVar1,(char *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    param_1 = (double)gnt4_HSD_LObjSetupInit_bl
                                (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_80436214,extraout_r4_00,pfVar2,param_12,param_13,param_14,
                                 param_15,param_16);
    puVar1 = extraout_r4_01;
  }
  while( true ) {
    if (iVar4 == 0) break;
    if (*(char *)(iVar4 + 0x10) != '\0') {
      if ((-1 < (int)uVar6) && (uVar6 != *(byte *)(iVar4 + 0xb))) {
        if (*(byte *)(iVar4 + 0xb) == 0) {
          param_1 = (double)gnt4_HSD_FogSet_bl(param_1,param_2,param_3,param_4,param_5,param_6,
                                               param_7,param_8,DAT_80436204,puVar1,pfVar2,param_12,
                                               param_13,param_14,param_15,param_16);
          puVar1 = extraout_r4_02;
        }
        else {
          param_1 = (double)gnt4_HSD_FogSet_bl(param_1,param_2,param_3,param_4,param_5,param_6,
                                               param_7,param_8,0,puVar1,pfVar2,param_12,param_13,
                                               param_14,param_15,param_16);
          puVar1 = extraout_r4_03;
        }
        uVar6 = (uint)*(byte *)(iVar4 + 0xb);
      }
      if (*(int *)(iVar4 + 0xc) != 0) {
        param_12 = 0;
        pfVar2 = pfVar5;
        param_1 = (double)gnt4_HSD_JObjDispAll
                                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,*(int *)(iVar4 + 0xc),0,pfVar5,0.0,param_13,param_14,param_15,
                                     param_16);
        puVar1 = extraout_r4_04;
      }
    }
    iVar4 = *(int *)((int)fVar3 * 4 + iVar4 + 0x20);
  }
  return;
}



// ==== 8000993c  zz_000993c_ ====

void zz_000993c_(void)

{
  DAT_803bb140 = 0;
  DAT_803bb144 = 0;
  DAT_803bb148 = 0;
  DAT_803bb14c = 0;
  return;
}



// ==== 80009958  zz_0009958_ ====

void zz_0009958_(int param_1,int param_2)

{
  *(undefined4 *)(param_1 + 0x20) = (&DAT_803bb140)[param_2];
  (&DAT_803bb140)[param_2] = param_1;
  return;
}



// ==== 80009974  zz_0009974_ ====

void zz_0009974_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,float param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar1;
  undefined8 uVar2;
  
  uVar2 = gnt4_HSD_FogSet_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,
                             param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  if ((int *)(&DAT_803bb460)[param_9] != (int *)0x0) {
    uVar2 = zz_0245398_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int *)(&DAT_803bb460)[param_9],extraout_r4,(char *)param_11,param_12,
                        param_13,param_14,param_15,param_16);
    uVar2 = gnt4_HSD_LObjSetupInit_bl
                      (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                       extraout_r4_00,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  iVar1 = (&DAT_803bb140)[param_9];
  if (iVar1 != 0) {
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x20)) {
      if ((*(char *)(iVar1 + 0x10) != '\0') && (*(int *)(iVar1 + 0xc) != 0)) {
        uVar2 = gnt4_HSD_JObjDispAll
                          (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(iVar1 + 0xc),0,(float *)0x7,0.0,param_13,param_14,param_15,
                           param_16);
      }
    }
  }
  return;
}



// ==== 80009a14  zz_0009a14_ ====

/* WARNING: Removing unreachable block (ram,0x80009a8c) */

void zz_0009a14_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,float *param_10,
                int param_11,int *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  float *pfVar3;
  int *piVar4;
  int iVar5;
  undefined8 uVar6;
  float afStack_48 [15];
  
  pfVar3 = afStack_48;
  piVar4 = param_12;
  uVar6 = gnt4_PSMTXConcat_bl(param_10,(float *)(param_11 + *param_12 * 0x30),pfVar3);
  if (param_9 == 0) {
    pfVar3 = (float *)&DAT_80436a58;
    gnt4___assert_bl(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436a50,
                     0x495,&DAT_80436a58,piVar4,param_13,param_14,param_15,param_16);
  }
  uVar6 = gnt4_PSMTXCopy_bl(afStack_48,(float *)(param_9 + 0x44));
  *(uint *)(param_9 + 0x14) = *(uint *)(param_9 + 0x14) | 0x3800000;
  if (param_9 != 0) {
    uVar2 = *(uint *)(param_9 + 0x14);
    bVar1 = false;
    if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      uVar6 = gnt4_HSD_JObjSetMtxDirtySub_bl
                        (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar2
                         ,(undefined *)pfVar3,piVar4,param_13,param_14,param_15,param_16);
    }
  }
  *param_12 = *param_12 + 1;
  if (param_9 == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = *(int *)(param_9 + 0x10);
  }
  while (iVar5 != 0) {
    uVar6 = zz_0009a14_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                        afStack_48,param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar5 == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = *(int *)(iVar5 + 8);
    }
  }
  return;
}



// ==== 80009b38  zz_0009b38_ ====

void zz_0009b38_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int *param_11,
                undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  int iVar5;
  double dVar6;
  
  pfVar4 = (float *)(param_10 + *param_11 * 0x30);
  if (param_9 == 0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436a50,
                     0x3e4,&DAT_80436a58,param_12,param_13,param_14,param_15,param_16);
  }
  fVar3 = *(float *)(param_9 + 0x38);
  fVar2 = *(float *)(param_9 + 0x3c);
  fVar1 = *(float *)(param_9 + 0x40);
  gnt4_PSMTXIdentity_bl(pfVar4);
  dVar6 = (double)fVar2;
  pfVar4[3] = fVar3;
  pfVar4[7] = fVar2;
  pfVar4[0xb] = fVar1;
  *param_11 = *param_11 + 1;
  if (param_9 == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = *(int *)(param_9 + 0x10);
  }
  while (iVar5 != 0) {
    dVar6 = (double)zz_0009b38_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                                param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar5 == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = *(int *)(iVar5 + 8);
    }
  }
  return;
}



// ==== 80009c28  zz_0009c28_ ====

void zz_0009c28_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x18) = param_2;
  return;
}



// ==== 80009c30  zz_0009c30_ ====

void zz_0009c30_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x1c) = param_2;
  return;
}



// ==== 80009c38  zz_0009c38_ ====

void zz_0009c38_(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                undefined1 param_5)

{
  *(undefined1 *)(param_1 + 0x1c) = param_2;
  *(undefined1 *)(param_1 + 0x1d) = param_3;
  *(undefined1 *)(param_1 + 0x1e) = param_4;
  *(undefined1 *)(param_1 + 0x1f) = param_5;
  return;
}



// ==== 80009c4c  zz_0009c4c_ ====

void zz_0009c4c_(int param_1,int param_2)

{
  float *pfVar1;
  
  pfVar1 = (float *)((&PTR_DAT_804335a0)[DAT_804360c0] + param_2 * 0x10);
  gnt4_HSD_CObjSetPerspective_bl((double)*pfVar1,(double)pfVar1[1],param_1);
  gnt4_HSD_CObjSetNear_bl((double)pfVar1[2],param_1);
  gnt4_HSD_CObjSetFar_bl((double)pfVar1[3],param_1);
  return;
}



// ==== 80009cbc  FUN_80009cbc ====

/* WARNING: Removing unreachable block (ram,0x80009d8c) */
/* WARNING: Removing unreachable block (ram,0x80009d84) */
/* WARNING: Removing unreachable block (ram,0x80009d7c) */
/* WARNING: Removing unreachable block (ram,0x80009d74) */
/* WARNING: Removing unreachable block (ram,0x80009ce4) */
/* WARNING: Removing unreachable block (ram,0x80009cdc) */
/* WARNING: Removing unreachable block (ram,0x80009cd4) */
/* WARNING: Removing unreachable block (ram,0x80009ccc) */

void FUN_80009cbc(int param_1,int param_2,int param_3)

{
  int iVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  
  iVar1 = param_2 * 0x18;
  dVar3 = (double)*(float *)(&DAT_802c32e0 + iVar1);
  dVar2 = (double)*(float *)(&DAT_802c32e4 + iVar1);
  dVar5 = (double)(float)(dVar3 + (double)*(float *)(&DAT_802c32e8 + iVar1));
  dVar4 = (double)(float)(dVar2 + (double)*(float *)(&DAT_802c32ec + iVar1));
  gnt4_HSD_CObjSetViewportfx4_bl(dVar3,dVar5,dVar2,dVar4,param_1);
  if (param_3 != 0) {
    gnt4_HSD_CObjSetScissorx4_bl
              (param_1,(short)(int)dVar3,(short)(int)dVar5,(short)(int)dVar2,(short)(int)dVar4);
  }
  return;
}



// ==== 80009dac  FUN_80009dac ====

void FUN_80009dac(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_2 * 0x10;
  gnt4_HSD_CObjSetOrtho_bl
            ((double)*(float *)(&DAT_802c33d0 + iVar1),(double)*(float *)(&DAT_802c33d4 + iVar1),
             (double)*(float *)(&DAT_802c33d8 + iVar1),(double)*(float *)(&DAT_802c33dc + iVar1),
             DAT_80436214);
  gnt4_HSD_CObjSetNear_bl((double)FLOAT_80436a9c,DAT_80436214);
  gnt4_HSD_CObjSetFar_bl((double)FLOAT_80436aa0,DAT_80436214);
  return;
}



// ==== 80009e08  zz_0009e08_ ====

void zz_0009e08_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  ushort uVar1;
  int *piVar2;
  uint uVar3;
  undefined8 uVar4;
  
  zz_0008b58_();
  zz_0008c40_();
  zz_0008cf4_();
  uVar4 = zz_01978d0_();
  piVar2 = DAT_80436210;
  if (DAT_80436210 != (int *)0x0) {
    uVar1 = *(ushort *)(DAT_80436210 + 1);
    uVar3 = countLeadingZeros(0xffff - (uint)uVar1);
    uVar3 = uVar3 >> 5;
    if (uVar3 == 0) {
      uVar3 = countLeadingZeros((uint)uVar1);
      *(ushort *)(DAT_80436210 + 1) = uVar1 - 1;
      uVar3 = uVar3 >> 5;
    }
    if ((uVar3 != 0) && (piVar2 != (int *)0x0)) {
      (**(code **)(*piVar2 + 0x30))(piVar2);
      uVar4 = (**(code **)(*piVar2 + 0x34))(piVar2);
    }
  }
  piVar2 = DAT_80436214;
  if (DAT_80436214 != (int *)0x0) {
    uVar1 = *(ushort *)(DAT_80436214 + 1);
    uVar3 = countLeadingZeros(0xffff - (uint)uVar1);
    uVar3 = uVar3 >> 5;
    if (uVar3 == 0) {
      uVar3 = countLeadingZeros((uint)uVar1);
      *(ushort *)(DAT_80436214 + 1) = uVar1 - 1;
      uVar3 = uVar3 >> 5;
    }
    if ((uVar3 != 0) && (piVar2 != (int *)0x0)) {
      (**(code **)(*piVar2 + 0x30))(piVar2);
      uVar4 = (**(code **)(*piVar2 + 0x34))(piVar2);
    }
  }
  uVar4 = zz_025411c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  DAT_80436214 = gnt4_HSD_CObjAlloc_bl
                           (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  DAT_80436210 = gnt4_HSD_CObjAlloc_bl
                           (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80009f40  zz_0009f40_ ====

void zz_0009f40_(void)

{
  int iVar1;
  undefined4 *__s;
  
  __s = &DAT_803bb32c;
  iVar1 = 0;
  do {
    gnt4_memset(__s,0,8);
    iVar1 = iVar1 + 1;
    __s = __s + 2;
  } while (iVar1 < 0x20);
  return;
}



// ==== 80009f98  zz_0009f98_ ====

void zz_0009f98_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  DAT_804360d0 = &DAT_803af364;
  gnt4_memset(&DAT_803af364,0,0x44);
  DAT_804360d4 = (void *)(DAT_80436238 + 0xa6800);
  gnt4_memset(DAT_804360d4,0,0x2000);
  if (DAT_804361c0 != (void *)0x0) {
    zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
    DAT_804361c0 = (void *)0x0;
  }
  zz_000a144_();
  return;
}



// ==== 8000a004  zz_000a004_ ====

int zz_000a004_(void)

{
  if (*DAT_804360d0 == '\x01') {
    *(short *)(DAT_804360d0 + 0xe) = *(short *)(DAT_804360d0 + 0xe) + 1;
    (*(code *)(&PTR_FUN_802c3818)[*(char *)(DAT_804360d4 + (uint)(byte)DAT_804360d0[1] * 0x20 + 2)])
              ();
  }
  return (int)*DAT_804360d0;
}



// ==== 8000a07c  zz_000a07c_ ====

undefined4 zz_000a07c_(void)

{
  undefined4 uVar1;
  
  if (*DAT_804360d0 == '\0') {
    uVar1 = 0;
  }
  else if (DAT_804360d0[3] == '\0') {
    if ((*DAT_804360d0 == '\x01') && (DAT_804360d0[0xd] == '\0')) {
      DAT_804360d0[0xd] = '\x01';
    }
    if (DAT_804360d0[0xd] == '\x02') {
      *DAT_804360d0 = '\0';
      DAT_804360d0[1] = '\0';
      DAT_804360d0[2] = '\0';
      DAT_804360d0[0xd] = '\0';
      gnt4_memset(DAT_804360d4,0,0x2000);
      zz_000a144_();
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 8000a134  zz_000a134_ ====

void zz_000a134_(void)

{
  *(undefined1 *)(DAT_804360d0 + 3) = 0;
  return;
}



// ==== 8000a144  zz_000a144_ ====

void zz_000a144_(void)

{
  DAT_804360cc = 0;
  DAT_804360c8 = 0;
  return;
}



// ==== 8000a154  zz_000a154_ ====

void zz_000a154_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,int param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  byte in_cr1;
  undefined4 local_88;
  int local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  char local_28 [4];
  undefined1 *local_24;
  undefined4 *local_20;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_68 = param_1;
    local_60 = param_2;
    local_58 = param_3;
    local_50 = param_4;
    local_48 = param_5;
    local_40 = param_6;
    local_38 = param_7;
    local_30 = param_8;
  }
  local_24 = &stack0x00000008;
  local_20 = &local_88;
  local_28[0] = '\x02';
  local_28[1] = '\0';
  local_28[2] = '\0';
  local_28[3] = '\0';
  local_88 = param_9;
  local_84 = param_10;
  local_80 = param_11;
  local_7c = param_12;
  local_78 = param_13;
  local_74 = param_14;
  local_70 = param_15;
  local_6c = param_16;
  for (iVar3 = 0; iVar3 < param_10; iVar3 = iVar3 + 1) {
    piVar2 = __va_arg(local_28,1);
    iVar1 = DAT_804360cc * 4;
    DAT_804360cc = DAT_804360cc + 1 & 0x7f;
    *(int *)(&DAT_803af164 + iVar1) = *piVar2;
  }
  zz_000b1d4_(param_9,DAT_804360c8,param_10,4);
  return;
}



// ==== 8000a234  FUN_8000a234 ====

void FUN_8000a234(undefined1 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  code *pcVar4;
  undefined4 local_28 [4];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  puVar2 = local_28;
  pcVar4 = *(code **)(param_1 + 0x10);
  for (uVar3 = 0; uVar3 < *(uint *)(param_1 + 4); uVar3 = uVar3 + 1) {
    iVar1 = DAT_804360c8 * 4;
    DAT_804360c8 = DAT_804360c8 + 1 & 0x7f;
    *puVar2 = *(undefined4 *)(&DAT_803af164 + iVar1);
    puVar2 = puVar2 + 1;
  }
  switch(*(uint *)(param_1 + 4)) {
  case 0:
    (*pcVar4)();
    break;
  case 1:
    (*pcVar4)(local_28[0]);
    break;
  case 2:
    (*pcVar4)(local_28[0],local_28[1]);
    break;
  case 3:
    (*pcVar4)(local_28[0],local_28[1],local_28[2]);
    break;
  case 4:
    (*pcVar4)(local_28[0],local_28[1],local_28[2],local_28[3]);
    break;
  case 5:
    (*pcVar4)(local_28[0],local_28[1],local_28[2],local_28[3],local_18);
    break;
  case 6:
    (*pcVar4)(local_28[0],local_28[1],local_28[2],local_28[3],local_18,local_14);
    break;
  case 7:
    (*pcVar4)(local_28[0],local_28[1],local_28[2],local_28[3],local_18,local_14,local_10);
    break;
  case 8:
    (*pcVar4)(local_28[0],local_28[1],local_28[2],local_28[3],local_18,local_14,local_10,local_c);
  }
  zz_000b26c_(param_1);
  return;
}



// ==== 8000a3c4  zz_000a3c4_ ====

int zz_000a3c4_(void)

{
  return (int)*DAT_804360d0;
}



// ==== 8000a3d4  FUN_8000a3d4 ====

void FUN_8000a3d4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined1 *param_9,int param_10,uint param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  cVar1 = param_9[1];
  if (cVar1 == '\0') {
    iVar3 = *(int *)(param_9 + 0x10);
    DAT_804361c0 = zz_0273000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,
                               iVar3);
    if (DAT_804361c0 == (undefined1 *)0x0) {
      param_9[1] = 0xff;
      return;
    }
    param_10 = zz_0272318_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           (int)DAT_804361c0,iVar3,param_11,param_12,param_13,param_14,param_15,
                           param_16);
    *(int *)(param_9 + 4) = param_10 << 0xb;
    param_11 = *(uint *)(param_9 + 0xc);
    zz_02729e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_804361c0,
                param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    param_9[1] = param_9[1] + '\x01';
    *(undefined2 *)(param_9 + 0x1a) = 0;
  }
  else {
    if (cVar1 < '\0') {
      if (cVar1 == -2) {
        iVar3 = zz_02722d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int)DAT_804361c0,param_10,param_11,param_12,param_13,param_14,param_15,
                            param_16);
        if (iVar3 != 1) {
          return;
        }
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        *(undefined1 *)(DAT_804360d0 + 0xd) = 2;
        zz_000b26c_(param_9);
        return;
      }
      if (cVar1 < -2) {
        return;
      }
      param_9[1] = 0;
      return;
    }
    if ('\x01' < cVar1) {
      return;
    }
  }
  iVar3 = zz_02722d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)DAT_804361c0,param_10,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  if (iVar3 == 3) {
    zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
    DAT_804361c0 = (undefined1 *)0x0;
    *(int *)(DAT_804360d0 + 8) = *(int *)(DAT_804360d0 + 8) + *(int *)(param_9 + 4);
    zz_000b26c_(param_9);
  }
  else if (iVar3 < 3) {
    if (iVar3 == 1) {
      sVar2 = *(short *)(param_9 + 0x1a);
      *(short *)(param_9 + 0x1a) = sVar2 + 1;
      if (0x3c < (short)(sVar2 + 1)) {
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        param_9[1] = 0xff;
      }
    }
    else if (0 < iVar3) {
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
  else if (iVar3 < 5) {
    zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
    DAT_804361c0 = (undefined1 *)0x0;
    param_9[1] = 0xff;
  }
  return;
}



// ==== 8000a5a0  FUN_8000a5a0 ====

void FUN_8000a5a0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 byte *param_9,undefined4 param_10,undefined4 *param_11,uint param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  short sVar2;
  undefined4 *puVar3;
  uint *puVar4;
  uint uVar5;
  ushort *puVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  uint uVar12;
  
  bVar1 = param_9[1];
  uVar9 = (uint)bVar1;
  switch(bVar1) {
  case 0:
    param_9[1] = bVar1 + 1;
    *param_9 = *param_9 & 0x7f;
  case 1:
    DAT_804361c0 = zz_0273000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,
                               *(int *)(param_9 + 0x10));
    if (DAT_804361c0 == (undefined1 *)0x0) {
      param_9[1] = 0xff;
      return;
    }
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
    param_9[1] = param_9[1] + 1;
switchD_8000a5ec_caseD_2:
    param_11 = &DAT_803c0740;
    uVar9 = 1;
    zz_02729e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_804361c0,1,
                0x803c0740,param_12,param_13,param_14,param_15,param_16);
    param_9[1] = param_9[1] + 1;
    param_9[0x1a] = 0;
    param_9[0x1b] = 0;
switchD_8000a5ec_caseD_3:
    iVar8 = zz_02722d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)DAT_804361c0,uVar9,param_11,param_12,param_13,param_14,param_15,
                        param_16);
    uVar9 = DAT_803c0740;
    if (iVar8 != 3) {
      if (2 < iVar8) {
        if (4 < iVar8) {
          return;
        }
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        param_9[1] = 0xff;
        return;
      }
      if (iVar8 == 1) {
        sVar2 = *(short *)(param_9 + 0x1a);
        *(short *)(param_9 + 0x1a) = sVar2 + 1;
        if ((short)(sVar2 + 1) < 0x3d) {
          return;
        }
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        param_9[1] = 0xff;
        return;
      }
      if (iVar8 < 1) {
        return;
      }
      if (*(char *)(DAT_804360d0 + 0xd) == '\x01') {
        zz_0272868_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    (int)DAT_804361c0);
        param_9[1] = 0xfe;
        return;
      }
      param_9[0x1a] = 0;
      param_9[0x1b] = 0;
      return;
    }
    if (DAT_803af144 < 0) {
      iVar8 = 0;
      DAT_803af144 = 0;
      puVar11 = &DAT_803c068c;
      DAT_803af148 = &DAT_803c0744;
      DAT_803af140 = DAT_803c0740;
      DAT_803af154 = 0;
      if (0 < (int)DAT_803c0740) {
        uVar12 = DAT_803c0740 >> 3;
        if (uVar12 != 0) {
          do {
            *puVar11 = *(undefined4 *)(*(int *)(param_9 + 0xc) + iVar8);
            puVar11[1] = *(undefined4 *)(*(int *)(param_9 + 0xc) + iVar8 + 4);
            puVar11[2] = *(undefined4 *)(*(int *)(param_9 + 0xc) + iVar8 + 8);
            puVar11[3] = *(undefined4 *)(*(int *)(param_9 + 0xc) + iVar8 + 0xc);
            puVar11[4] = *(undefined4 *)(*(int *)(param_9 + 0xc) + iVar8 + 0x10);
            puVar11[5] = *(undefined4 *)(*(int *)(param_9 + 0xc) + iVar8 + 0x14);
            iVar10 = iVar8 + 0x1c;
            puVar11[6] = *(undefined4 *)(*(int *)(param_9 + 0xc) + iVar8 + 0x18);
            iVar8 = iVar8 + 0x20;
            puVar11[7] = *(undefined4 *)(*(int *)(param_9 + 0xc) + iVar10);
            puVar11 = puVar11 + 8;
            uVar12 = uVar12 - 1;
          } while (uVar12 != 0);
          uVar9 = uVar9 & 7;
          if (uVar9 == 0) goto LAB_8000a8b8;
        }
        do {
          puVar3 = (undefined4 *)(*(int *)(param_9 + 0xc) + iVar8);
          iVar8 = iVar8 + 4;
          *puVar11 = *puVar3;
          puVar11 = puVar11 + 1;
          uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
      }
LAB_8000a8b8:
      *param_9 = *param_9 | 0x80;
    }
    else {
      if ((DAT_803af159 & 0x40) != 0) {
        DAT_803af154 = zz_0048588_((ushort *)(DAT_80436238 + 0x4800),DAT_803af14c,param_11,param_12)
        ;
      }
      gnt4_DCFlushRange_bl((uint)DAT_803af14c,DAT_803af154);
      uVar9 = DAT_803af154 + 0x7ff;
      iVar8 = ((int)uVar9 >> 0xb) + (uint)((int)uVar9 < 0 && (uVar9 & 0x7ff) != 0);
      uVar9 = iVar8 * 0x800;
      DAT_803af154 = uVar9;
      if (-1 < DAT_803af158) {
        iVar10 = (int)DAT_803af158;
        (&DAT_803c06cc)[iVar10] = DAT_803af14c + iVar8 * 0x400;
        (&DAT_803c064c)[iVar10] = uVar9;
      }
    }
    uVar9 = 0;
    while (DAT_803af144 < (int)DAT_803af140) {
      puVar4 = DAT_803af148 + 1;
      uVar5 = *DAT_803af148;
      uVar12 = uVar5 & 0x3fffffff;
      DAT_803af159 = (byte)(uVar5 >> 0x18) & 0xc0;
      DAT_803af148 = puVar4;
      if (uVar12 == 0) {
        puVar6 = *(ushort **)(*(int *)(param_9 + 0xc) + DAT_803af144 * 4);
        if (puVar6 != (ushort *)0x0) {
          DAT_803af158 = DAT_803af158 + '\x01';
          DAT_803af14c = puVar6;
        }
        *(undefined4 *)(*(int *)(param_9 + 0xc) + DAT_803af144 * 4) = 0;
        DAT_803af154 = 0;
        DAT_803af144 = DAT_803af144 + 1;
      }
      else {
        DAT_803af150 = *(uint *)(*(int *)(param_9 + 0xc) + DAT_803af144 * 4);
        if (DAT_803af150 == 0) {
          if (uVar9 == 0) {
            DAT_803af150 = (int)DAT_803af14c + DAT_803af154;
            *(uint *)(*(int *)(param_9 + 0xc) + DAT_803af144 * 4) = DAT_803af150;
LAB_8000aa90:
            DAT_803af14c = (ushort *)DAT_803af150;
            if (DAT_803af159 != 0) {
              DAT_803af150 = DAT_80436238 + 0x4800;
            }
            DAT_803af154 = uVar5 << 0xb;
            DAT_803af144 = DAT_803af144 + 1;
            param_9[1] = param_9[1] + 1;
            return;
          }
          DAT_803af144 = DAT_803af144 + 1;
          uVar9 = uVar9 + uVar12;
        }
        else {
          if ((DAT_803af150 & 0xf0000000) != 0xf0000000) {
            DAT_803af158 = DAT_803af158 + '\x01';
            if (uVar9 != 0) {
              zz_02723b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int)DAT_804361c0,uVar9,1);
            }
            goto LAB_8000aa90;
          }
          DAT_803af144 = DAT_803af144 + 1;
          uVar9 = uVar9 + uVar12;
          DAT_803af158 = DAT_803af158 + '\x01';
        }
      }
    }
    zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
    DAT_804361c0 = (undefined1 *)0x0;
    *(int *)(DAT_804360d0 + 8) = *(int *)(DAT_804360d0 + 8) + *(int *)(param_9 + 4);
    zz_000b26c_(param_9);
    break;
  case 2:
    goto switchD_8000a5ec_caseD_2;
  case 3:
    goto switchD_8000a5ec_caseD_3;
  case 4:
    zz_02729e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_804361c0,
                ((int)DAT_803af154 >> 0xb) +
                (uint)((int)DAT_803af154 < 0 && (DAT_803af154 & 0x7ff) != 0),DAT_803af150,param_12,
                param_13,param_14,param_15,param_16);
    param_9[1] = param_9[1] - 1;
    break;
  case 0xfe:
    iVar8 = zz_02722d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)DAT_804361c0,uVar9,param_11,param_12,param_13,param_14,param_15,
                        param_16);
    if (iVar8 == 1) {
      zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
      DAT_804361c0 = (undefined1 *)0x0;
      *(undefined1 *)(DAT_804360d0 + 0xd) = 2;
      zz_000b26c_(param_9);
    }
    break;
  case 0xff:
    param_9[1] = 1;
    if ((*param_9 & 0x80) != 0) {
      puVar11 = &DAT_803c068c;
      iVar8 = 0;
      for (iVar10 = 0; iVar10 < (int)DAT_803af140; iVar10 = iVar10 + 1) {
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
        *(undefined4 *)(*(int *)(param_9 + 0xc) + iVar8) = uVar7;
        iVar8 = iVar8 + 4;
      }
    }
  }
  return;
}



// ==== 8000ab9c  FUN_8000ab9c ====

void FUN_8000ab9c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined1 *param_9,int param_10,uint param_11,uint param_12,undefined4 param_13,
                 undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  
  cVar1 = param_9[1];
  if (cVar1 == '\0') {
    param_9[1] = 1;
    iVar4 = *(int *)(param_9 + 0x10);
    DAT_804361c0 = zz_0273000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,
                               iVar4);
    if (DAT_804361c0 == (undefined1 *)0x0) {
      param_9[1] = 0xff;
      return;
    }
    param_10 = zz_0272318_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           (int)DAT_804361c0,iVar4,param_11,param_12,param_13,param_14,param_15,
                           param_16);
    *(int *)(param_9 + 4) = param_10;
    param_11 = DAT_80436238 + 0x4800;
    zz_02729e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_804361c0,
                param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    *(undefined2 *)(param_9 + 0x1a) = 0;
  }
  else {
    if (cVar1 < '\0') {
      if (cVar1 == -2) {
        iVar4 = zz_02722d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int)DAT_804361c0,param_10,param_11,param_12,param_13,param_14,param_15,
                            param_16);
        if (iVar4 != 1) {
          return;
        }
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        *(undefined1 *)(DAT_804360d0 + 0xd) = 2;
        zz_000b26c_(param_9);
        return;
      }
      if (cVar1 < -2) {
        return;
      }
      param_9[1] = 0;
      return;
    }
    if ('\x01' < cVar1) {
      return;
    }
  }
  iVar4 = zz_02722d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)DAT_804361c0,param_10,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  if (iVar4 == 3) {
    zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
    iVar4 = DAT_804360d0;
    DAT_804361c0 = (undefined1 *)0x0;
    *(int *)(DAT_804360d0 + 8) = *(int *)(DAT_804360d0 + 8) + *(int *)(param_9 + 4);
    zz_000b26c_(param_9);
    iVar4 = zz_0048588_((ushort *)(DAT_80436238 + 0x4800),*(ushort **)(param_9 + 0xc),iVar4,param_12
                       );
    uVar3 = iVar4 + 0x7ff;
    iVar4 = (((int)uVar3 >> 0xb) + (uint)((int)uVar3 < 0 && (uVar3 & 0x7ff) != 0)) * 0x800;
    gnt4_DCFlushRange_bl(*(uint *)(param_9 + 0xc),iVar4);
    DAT_8043622c = *(int *)(param_9 + 0xc) + iVar4;
  }
  else if (iVar4 < 3) {
    if (iVar4 == 1) {
      sVar2 = *(short *)(param_9 + 0x1a);
      *(short *)(param_9 + 0x1a) = sVar2 + 1;
      if (0x3c < (short)(sVar2 + 1)) {
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        param_9[1] = 0xff;
      }
    }
    else if (0 < iVar4) {
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
  else if (iVar4 < 5) {
    zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
    DAT_804361c0 = (undefined1 *)0x0;
    param_9[1] = 0xff;
  }
  return;
}



// ==== 8000ada4  FUN_8000ada4 ====

void FUN_8000ada4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined1 *param_9,int param_10,uint param_11,uint param_12,undefined4 param_13,
                 undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  ushort *puVar5;
  
  cVar1 = param_9[1];
  if (cVar1 == '\0') {
    param_9[1] = 1;
    iVar4 = *(int *)(param_9 + 0x10);
    DAT_804361c0 = zz_0273000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,
                               iVar4);
    param_10 = zz_0272318_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           (int)DAT_804361c0,iVar4,param_11,param_12,param_13,param_14,param_15,
                           param_16);
    *(int *)(param_9 + 4) = param_10;
    param_11 = DAT_80436238 + 0x4800;
    zz_02729e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_804361c0,
                param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    *(undefined2 *)(param_9 + 0x1a) = 0;
  }
  else {
    if (cVar1 < '\0') {
      if (cVar1 == -2) {
        iVar4 = zz_02722d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int)DAT_804361c0,param_10,param_11,param_12,param_13,param_14,param_15,
                            param_16);
        if (iVar4 != 1) {
          return;
        }
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        *(undefined1 *)(DAT_804360d0 + 0xd) = 2;
        zz_000b26c_(param_9);
        return;
      }
      if (cVar1 < -2) {
        return;
      }
      param_9[1] = 0;
      return;
    }
    if ('\x01' < cVar1) {
      return;
    }
  }
  iVar4 = zz_02722d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)DAT_804361c0,param_10,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  if (iVar4 == 3) {
    zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
    iVar4 = DAT_804360d0;
    DAT_804361c0 = (undefined1 *)0x0;
    *(int *)(DAT_804360d0 + 8) = *(int *)(DAT_804360d0 + 8) + *(int *)(param_9 + 4);
    zz_000b26c_(param_9);
    puVar5 = (ushort *)**(undefined4 **)(param_9 + 0xc);
    iVar4 = zz_0048588_((ushort *)(DAT_80436238 + 0x4800),puVar5,iVar4,param_12);
    uVar3 = iVar4 + 0x7ff;
    DAT_8043622c = puVar5 + (((int)uVar3 >> 0xb) + (uint)((int)uVar3 < 0 && (uVar3 & 0x7ff) != 0)) *
                            0x400;
  }
  else if (iVar4 < 3) {
    if (iVar4 == 1) {
      sVar2 = *(short *)(param_9 + 0x1a);
      *(short *)(param_9 + 0x1a) = sVar2 + 1;
      if (0x3c < (short)(sVar2 + 1)) {
        zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
        DAT_804361c0 = (undefined1 *)0x0;
        param_9[1] = 0xff;
      }
    }
    else if (0 < iVar4) {
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
  else if (iVar4 < 5) {
    zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361c0);
    DAT_804361c0 = (undefined1 *)0x0;
    param_9[1] = 0xff;
  }
  return;
}



// ==== 8000af84  zz_000af84_ ====

int zz_000af84_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = param_9;
  puVar1 = zz_0273000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,param_9);
  iVar2 = zz_0272318_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)puVar1,
                      iVar2,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1);
  zz_000b1d4_(param_9,param_10,iVar2 << 0xb,0);
  return iVar2 << 0xb;
}



// ==== 8000b000  zz_000b000_ ====

int zz_000b000_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = param_9;
  puVar1 = zz_0273000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,param_9);
  iVar2 = zz_0272318_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)puVar1,
                      iVar2,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1);
  zz_000b1d4_(param_9,param_10,iVar2 << 0xb,2);
  return iVar2 << 0xb;
}



// ==== 8000b07c  zz_000b07c_ ====

int zz_000b07c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = param_9;
  puVar1 = zz_0273000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,param_9);
  iVar2 = zz_0272318_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)puVar1,
                      iVar2,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1);
  zz_000b1d4_(param_9,param_10,iVar2 << 0xb,1);
  return iVar2 << 0xb;
}



// ==== 8000b0f8  zz_000b0f8_ ====

undefined4 zz_000b0f8_(undefined4 param_1,undefined4 param_2)

{
  zz_000b1d4_(param_1,param_2,0,5);
  return 0;
}



// ==== 8000b124  zz_000b124_ ====

int zz_000b124_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = param_9;
  puVar1 = zz_0273000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,param_9);
  iVar2 = zz_0272318_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)puVar1,
                      iVar2,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1);
  zz_000b1d4_(param_9,param_10,iVar2 << 0xb,6);
  return iVar2 << 0xb;
}



// ==== 8000b1a0  zz_000b1a0_ ====

int zz_000b1a0_(undefined4 param_1,undefined4 param_2,int param_3)

{
  zz_000b1d4_(param_1,param_2,param_3,7);
  return param_3;
}



// ==== 8000b1d4  zz_000b1d4_ ====

undefined1 * zz_000b1d4_(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  byte bVar1;
  char *pcVar2;
  int iVar3;
  undefined1 *puVar4;
  
  if (*DAT_804360d0 == '\0') {
    *DAT_804360d0 = '\x01';
    pcVar2 = DAT_804360d0;
    pcVar2[4] = '\0';
    pcVar2[5] = '\0';
    pcVar2[6] = '\0';
    pcVar2[7] = '\0';
    pcVar2 = DAT_804360d0;
    pcVar2[8] = '\0';
    pcVar2[9] = '\0';
    pcVar2[10] = '\0';
    pcVar2[0xb] = '\0';
    DAT_804360d0[0xd] = '\0';
    pcVar2 = DAT_804360d0;
    pcVar2[0xe] = '\0';
    pcVar2[0xf] = '\0';
  }
  iVar3 = DAT_804360d4;
  bVar1 = DAT_804360d0[2];
  DAT_804360d0[2] = bVar1 + 1;
  puVar4 = (undefined1 *)(iVar3 + (uint)bVar1 * 0x20);
  *puVar4 = 1;
  puVar4[1] = 0;
  *(undefined4 *)(puVar4 + 0x10) = param_1;
  *(undefined4 *)(puVar4 + 0xc) = param_2;
  *(int *)(puVar4 + 4) = param_3;
  puVar4[2] = (char)param_4;
  if (param_4 != 4) {
    *(int *)(DAT_804360d0 + 4) = *(int *)(DAT_804360d0 + 4) + param_3;
  }
  return puVar4;
}



// ==== 8000b26c  zz_000b26c_ ====

void zz_000b26c_(undefined1 *param_1)

{
  param_1[1] = 0;
  *param_1 = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  zz_000a134_();
  if (DAT_804360d0[0xd] == '\0') {
    DAT_804360d0[1] = DAT_804360d0[1] + '\x01';
    if (DAT_804360d0[1] == DAT_804360d0[2]) {
      *DAT_804360d0 = 0;
      DAT_804360d0[0xd] = 0;
    }
  }
  else {
    if (DAT_804360d0[0xd] == '\x01') {
      DAT_804360d0[0xd] = 2;
    }
    *DAT_804360d0 = 2;
  }
  return;
}



