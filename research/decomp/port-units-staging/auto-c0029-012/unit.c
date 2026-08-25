#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80107510(int param_1);
void FUN_80107590(int param_1);
void FUN_80107734(int param_1);
void FUN_801077e4(int param_1);
void FUN_80107978(int param_1);
void FUN_80107dfc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_80107e1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_80107f9c(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2306-2323 ==== */
// ==== 80107510  FUN_80107510 ====

void FUN_80107510(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  iVar1 = zz_00840b8_(param_1);
  if (iVar1 != 0) {
    *(undefined1 *)(iVar2 + 0x146) = 0;
    zz_006de10_(iVar2,2);
  }
  (*(code *)(&PTR_FUN_80323310)[*(char *)(param_1 + 0x18)])(param_1);
  *(undefined1 *)(param_1 + 0x22d) = *(undefined1 *)(iVar2 + 0x148);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2327-2400 ==== */
// ==== 80107590  FUN_80107590 ====

void FUN_80107590(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  uVar3 = 0x80320000;
  iVar6 = *(int *)(param_1 + 0x90);
  *(undefined1 *)(param_1 + 0x18) = 1;
  iVar4 = *(char *)(param_1 + 0x13) * 0x18;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  iVar5 = iVar4;
  zz_0089100_(param_1,0,1);
  *(undefined1 *)(param_1 + 0x84) = 0x1e;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar6 + *(short *)(&DAT_803232fa + iVar4) * 0x30 + 0x8d4),
             (float *)(iVar4 + -0x7fcdcd04),(float *)(param_1 + 0x20));
  dVar7 = FUN_8003db9c((float *)(param_1 + 0x20));
  dVar8 = (double)FLOAT_804394b8;
  dVar9 = (double)*(float *)(param_1 + 0x24);
  fVar1 = (float)(dVar8 * (double)*(float *)(iVar6 + 0xb4) + dVar7);
  if (dVar9 < (double)fVar1) {
    *(float *)(param_1 + 0x24) = fVar1;
  }
  zz_008458c_((float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(iVar6 + 0x70);
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar6 + 0x74);
  iVar2 = zz_0006f98_(iVar6);
  zz_0006fb4_(dVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar2 + 0x600),
              *(int *)(param_1 + 0xe0),(int)*(short *)(&DAT_803232f8 + iVar4),uVar3,iVar5,in_r8,
              in_r9,in_r10);
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + '1';
  *(undefined1 *)(param_1 + 0x86) = 0;
  *(undefined1 *)(param_1 + 0x224) = 0;
  *(undefined1 *)(param_1 + 0x225) = 0;
  *(undefined1 *)(param_1 + 0x226) = 0;
  *(undefined1 *)(param_1 + 0x227) = 0;
  *(undefined1 *)(param_1 + 0x228) = 0;
  *(undefined1 *)(param_1 + 0x229) = 0;
  *(undefined1 *)(param_1 + 0x22a) = 0;
  *(undefined1 *)(param_1 + 0x22b) = 0;
  *(undefined4 *)(param_1 + 0x1c4) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x1c8) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x1cc) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x1d0) = *(undefined4 *)(param_1 + 0x1c4);
  *(undefined4 *)(param_1 + 0x1d4) = *(undefined4 *)(param_1 + 0x1c8);
  *(undefined4 *)(param_1 + 0x1d8) = *(undefined4 *)(param_1 + 0x1cc);
  *(undefined1 *)(param_1 + 0x224) = 1;
  *(undefined1 *)(param_1 + 0x225) = 1;
  *(undefined1 *)(param_1 + 0x22c) = 1;
  zz_00a2bf8_(iVar6,param_1,(undefined4 *)(param_1 + 0x1c4),(undefined4 *)(param_1 + 0x1d0),3,0);
  *(undefined4 *)(param_1 + 0x230) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x234) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(param_1 + 0x28);
  zz_0117ed4_(param_1,param_1 + 0x230,0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2404-2433 ==== */
// ==== 80107734  FUN_80107734 ====

void FUN_80107734(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  cVar1 = *(char *)(param_1 + 0x19);
  iVar4 = *(int *)(param_1 + 0x90);
  if (cVar1 == '\x01') {
    FUN_80107978(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    FUN_801077e4(param_1);
  }
  iVar3 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
  uVar2 = *(undefined4 *)(iVar3 + 0x1c8);
  *(undefined4 *)(param_1 + 0x230) = *(undefined4 *)(iVar3 + 0x1c4);
  *(undefined4 *)(param_1 + 0x234) = uVar2;
  *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(iVar3 + 0x1cc);
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar4 + 0xb4);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2437-2478 ==== */
// ==== 801077e4  FUN_801077e4 ====

void FUN_801077e4(int param_1)

{
  float fVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  
  iVar5 = *(int *)(param_1 + 0x90);
  iVar4 = *(char *)(param_1 + 0x13) * 0x18;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar5 + *(short *)(&DAT_803232fa + iVar4) * 0x30 + 0x8d4),
             (float *)(iVar4 + -0x7fcdcd04),
             (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
  if (*(char *)(iVar5 + 0x146) == '\x02') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined1 *)(param_1 + 0x22e) = 0;
  }
  else if (*(char *)(param_1 + 0x22d) != *(char *)(iVar5 + 0x148)) {
    dVar6 = FUN_8003db9c((float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    fVar1 = (float)((double)FLOAT_804394b8 * (double)*(float *)(iVar5 + 0xb4) + dVar6);
    iVar3 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
    if (*(float *)(iVar3 + 0x1c8) < fVar1) {
      *(float *)(iVar3 + 0x1c8) = fVar1;
    }
    cVar2 = *(char *)(param_1 + 0x22c);
    zz_00a2bf8_(iVar5,param_1,(undefined4 *)(param_1 + cVar2 * 0xc + 0x1c4),
                (undefined4 *)(param_1 + (cVar2 + 1) * 0xc + 0x1c4),3,cVar2);
    *(char *)(param_1 + 0x22c) = *(char *)(param_1 + 0x22c) + '\x01';
    *(undefined1 *)(param_1 + *(char *)(param_1 + 0x22c) + 0x224) = 1;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar5 + *(short *)(&DAT_803232fa + iVar4) * 0x30 + 0x8d4),
               (float *)(iVar4 + -0x7fcdcd04),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    zz_008458c_((float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2482-2618 ==== */
// ==== 80107978  FUN_80107978 ====

/* WARNING: Removing unreachable block (ram,0x80107dcc) */
/* WARNING: Removing unreachable block (ram,0x80107988) */

void FUN_80107978(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  float fStack_34;
  float local_30;
  
  iVar7 = *(int *)(param_1 + 0x90);
  iVar5 = *(char *)(param_1 + 0x13) * 0x18;
  dVar8 = gnt4_PSVECSquareDistance_bl((float *)(iVar7 + 0x2c),(float *)(iVar7 + 0x5e8));
  if ((double)FLOAT_804394bc < dVar8) {
    dVar9 = 1.0 / SQRT(dVar8);
    dVar9 = DOUBLE_804394c0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_804394c8);
    dVar9 = DOUBLE_804394c0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_804394c8);
    dVar8 = (double)(float)(dVar8 * DOUBLE_804394c0 * dVar9 *
                                    -(dVar8 * dVar9 * dVar9 - DOUBLE_804394c8));
  }
  if ((double)(FLOAT_804394d0 * *(float *)(iVar7 + 0xb4)) < dVar8) {
    *(undefined1 *)(param_1 + 0x22e) = 0;
  }
  else {
    *(char *)(param_1 + 0x22e) = *(char *)(param_1 + 0x22e) + '\x01';
  }
  if ((((*(char *)(iVar7 + 0x146) == '\x03') || ((*(uint *)(iVar7 + 0x5e0) & 0x1000) != 0)) ||
      (*(char *)(iVar7 + 0x18) != '\x01')) ||
     ((*(char *)(iVar7 + 0x6cb) != '\0' || (',' < *(char *)(param_1 + 0x22e))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(iVar7 + 0x146) = 0;
    *(undefined2 *)(iVar7 + 0x784) = *(undefined2 *)(iVar7 + 0x79e);
    *(undefined2 *)(iVar7 + 0x786) = *(undefined2 *)(iVar7 + 0x79e);
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar7 + *(short *)(&DAT_803232fa + iVar5) * 0x30 + 0x8d4),
               (float *)(iVar5 + -0x7fcdcd04),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + (*(char *)(param_1 + 0x22c) + -1) * 0xc + 0x1c4),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4),&fStack_34);
    dVar8 = gnt4_PSVECMag_bl(&fStack_34);
    if (dVar8 <= (double)(FLOAT_804394d4 * *(float *)(param_1 + 0xb4))) {
      zz_006de10_(iVar7,2);
      if (*(char *)(param_1 + 0x22c) == 1) {
        *(undefined1 *)(param_1 + 0x18) = 2;
        *(undefined1 *)(iVar7 + 0x146) = 0;
        zz_00f036c_(iVar7,0xc3);
        return;
      }
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x22c) + 0x224) = 0;
      *(char *)(param_1 + 0x22c) = *(char *)(param_1 + 0x22c) + -1;
      *(char *)(iVar7 + 0x148) = *(char *)(iVar7 + 0x148) + -1;
      zz_00f0214_(iVar7,4,3);
    }
    gnt4_PSVECNormalize_bl(&fStack_34,&fStack_34);
    fVar1 = FLOAT_804394bc;
    if (*(char *)(iVar7 + 0x87) == '\0') {
      fVar1 = FLOAT_804394d4 * *(float *)(param_1 + 0xb4);
      iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
      fVar2 = *(float *)(iVar4 + 0x1bc) - *(float *)(iVar4 + 0x1c8);
      if (((fVar1 <= fVar2) || (fVar2 <= -fVar1)) && (FLOAT_804394d8 <= local_30)) {
        *(float *)(iVar7 + 0x48) = FLOAT_804394bc;
        *(byte *)(iVar7 + 0x732) = *(byte *)(iVar7 + 0x732) | 0x10;
      }
    }
    else if ((FLOAT_804394bc < local_30) &&
            (*(byte *)(iVar7 + 0x732) = *(byte *)(iVar7 + 0x732) | 0x10,
            *(float *)(iVar7 + 0x48) <= fVar1)) {
      *(float *)(iVar7 + 0x48) = fVar1;
    }
    dVar9 = (double)(FLOAT_804394d4 * *(float *)(param_1 + 0xb4));
    if ((double)(float)((double)FLOAT_804394dc * dVar9) < dVar8) {
      dVar8 = (double)(FLOAT_804394e0 * *(float *)(param_1 + 0xb4));
      if (*(char *)(iVar7 + 0x70c) != '\0') {
        dVar8 = (double)(float)(dVar8 * (double)*(float *)(iVar7 + 0x768));
      }
      gnt4_PSQUATScale_bl(dVar8,&fStack_34,&fStack_34);
    }
    else {
      gnt4_PSQUATScale_bl(dVar9,&fStack_34,&fStack_34);
    }
    zz_0084498_(iVar7,&fStack_34);
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar7 + *(short *)(&DAT_803232fa + iVar5) * 0x30 + 0x8d4),
               (float *)(iVar5 + -0x7fcdcd04),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    puVar6 = (undefined4 *)(param_1 + 0x1c4);
    iVar5 = 0;
    iVar7 = 2;
    do {
      if (*(char *)(param_1 + 0x22c) < iVar5) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        *puVar6 = *(undefined4 *)(iVar4 + 0x1c4);
        puVar6[1] = uVar3;
        puVar6[2] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      if ((int)*(char *)(param_1 + 0x22c) < iVar5 + 1) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        puVar6[3] = *(undefined4 *)(iVar4 + 0x1c4);
        puVar6[4] = uVar3;
        puVar6[5] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      if ((int)*(char *)(param_1 + 0x22c) < iVar5 + 2) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        puVar6[6] = *(undefined4 *)(iVar4 + 0x1c4);
        puVar6[7] = uVar3;
        puVar6[8] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      if ((int)*(char *)(param_1 + 0x22c) < iVar5 + 3) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        puVar6[9] = *(undefined4 *)(iVar4 + 0x1c4);
        puVar6[10] = uVar3;
        puVar6[0xb] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      puVar6 = puVar6 + 0xc;
      iVar5 = iVar5 + 4;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2622-2630 ==== */
// ==== 80107dfc  FUN_80107dfc ====

void FUN_80107dfc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2634-2653 ==== */
// ==== 80107e1c  FUN_80107e1c ====

void FUN_80107e1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  
  uVar1 = 1;
  if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2657-2675 ==== */
// ==== 80107f9c  FUN_80107f9c ====

void FUN_80107f9c(int param_1)

{
  short sVar1;
  
  *(undefined1 *)(param_1 + 0x6e8) = 2;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x306) {
    zz_013358c_(param_1,1);
    zz_00c74ec_(param_1,6);
  }
  else if ((sVar1 < 0x306) && (sVar1 == 0x302)) {
    zz_013358c_(param_1,0);
    zz_00c74ec_(param_1,6);
  }
  return;
}
