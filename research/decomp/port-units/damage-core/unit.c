#include "gnt4_shim.h"

/* stage-2 generated prototypes (design: prototypes for all functions from _index.tsv) */
int zz_003cd5c_(ushort *param_1,int param_2,char *param_3);
uint zz_003d344_(int param_1,short param_2);
int zz_0066298_(char *param_1);
bool FUN_80031634(int param_1,int param_2,float *param_3,int *param_4);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0004.c 6667-6828 ==== */
// ==== 8003cd5c  zz_003cd5c_ ====

/* WARNING: Removing unreachable block (ram,0x8003d31c) */
/* WARNING: Removing unreachable block (ram,0x8003cd6c) */

int zz_003cd5c_(ushort *param_1,int param_2,char *param_3)

{
  float fVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  uint uVar9;
  char *pcVar10;
  short sVar12;
  int iVar11;
  char *pcVar13;
  double dVar14;
  undefined2 local_38 [2];
  undefined2 local_34 [2];
  undefined8 local_30;
  
  local_30 = (double)CONCAT44(0x43300000,(uint)*param_1);
  fVar1 = (float)(local_30 - DOUBLE_80436fb0);
  if (FLOAT_80436f68 < fVar1) {
    if (((param_3[0x83] == '\0') && (*(uint *)(param_3 + 0x5a0) != 0)) &&
       ((*(uint *)(param_3 + 0x5a0) & 1 << (int)param_3[0x71a]) != 0)) {
      iVar4 = 0;
    }
    else {
      pcVar13 = *(char **)(param_2 + 0x90);
      dVar14 = (double)(fVar1 + fVar1 * FLOAT_80436f7c *
                                        (*(float *)(param_2 + 0xc4) - FLOAT_80436f78));
      if (((pcVar13[0x83] == '\0') && (*pcVar13 != '\0')) && (pcVar13[0x18] == '\x01')) {
        if (pcVar13[0x6fc] != '\0') {
          dVar14 = (double)(float)(dVar14 * (double)FLOAT_80436f9c);
        }
        cVar2 = pcVar13[0x3e6];
        iVar4 = (int)pcVar13[0x88];
        uVar3 = (uint)(-(int)cVar2 | (int)cVar2) >> 0x1d & 4;
        fVar1 = (float)(dVar14 * (double)*(float *)(*(int *)((int)&PTR_DAT_804335e0 + uVar3) +
                                                   (char)PTR_DAT_80433950[iVar4] * 4));
        if (((PTR_DAT_80433930[0x32] == '\0') || (PTR_DAT_80433930[0x32] == '\x01')) &&
           ((cVar2 != '\0' && (pcVar13[0x88] == '\0')))) {
          fVar1 = FLOAT_80436f7c * fVar1;
        }
        uVar9 = (uint)(short)(&DAT_803b069c)[pcVar13[0x3e4]];
        if ((int)uVar9 < 0xc9) {
          if (*(short *)(pcVar13 + 0x1c4) < 200) {
            iVar5 = (int)(uVar9 << 5) / (int)*(short *)(pcVar13 + 0x1c4);
          }
          else {
            iVar5 = (int)(uVar9 << 5) / 200 + ((int)(uVar9 << 5 | uVar9 >> 0x1b) >> 0x1f);
            iVar5 = iVar5 - (iVar5 >> 0x1f);
          }
          iVar5 = 0x20 - iVar5;
          if (0x1f < iVar5) {
            iVar5 = 0x1f;
          }
          fVar1 = fVar1 * *(float *)(*(int *)(*(int *)((int)&PTR_PTR_804335e8 + uVar3) +
                                             (uint)*(byte *)(param_1 + 3) * 4) + iVar5 * 4);
        }
        iVar4 = 0x20 - (int)((&DAT_803b068c)[iVar4] << 5) /
                       *(int *)(PTR_DAT_80433934 + iVar4 * 0x3c + 0x114);
        if (0x1f < iVar4) {
          iVar4 = 0x1f;
        }
        dVar14 = (double)(fVar1 * *(float *)(*(int *)(*(int *)((int)&PTR_PTR_804335f0 + uVar3) +
                                                     (uint)*(byte *)((int)param_1 + 7) * 4) +
                                            iVar4 * 4) *
                         *(float *)(*(int *)((int)&PTR_DAT_804335f8 + uVar3) + pcVar13[0x43a] * 4));
        if (((param_3[0x83] == '\0') && (*param_3 != '\0')) && (param_3[0x18] == '\x01')) {
          local_34[0] = *(undefined2 *)(pcVar13 + 1000);
          iVar4 = zz_0066298_((char *)local_34);
          local_38[0] = *(undefined2 *)(param_3 + 1000);
          iVar5 = zz_0066298_((char *)local_38);
          dVar14 = (double)(float)(dVar14 * (double)*(float *)(iVar5 * 0x50 + -0x7fd3a2a0 +
                                                              iVar4 * 4));
        }
      }
      pcVar7 = *(char **)(param_3 + 0x90);
      pcVar8 = param_3;
      pcVar10 = param_3;
      if (((pcVar7 != (char *)0x0) && (pcVar8 = pcVar7, param_3[0x83] != '\0')) &&
         (pcVar7[0x83] == '\0')) {
        pcVar10 = pcVar7;
      }
      if (((pcVar10[0x83] == '\0') && (*pcVar10 != '\0')) && (pcVar10[0x18] == '\x01')) {
        cVar2 = pcVar10[0x3e6];
        iVar4 = (-(int)cVar2 | (int)cVar2) >> 0x1f;
        if (pcVar10[0x6fc] != '\0') {
          dVar14 = (double)(float)(dVar14 * (double)FLOAT_80436f7c);
        }
        iVar5 = *(int *)(pcVar10 + 0x4ac);
        iVar6 = (int)pcVar10[0x88];
        fVar1 = (float)(dVar14 * (double)*(float *)(*(int *)((&PTR_PTR_80433600)[-iVar4] +
                                                            (uint)*(byte *)(iVar5 + 0x9c) * 4) +
                                                   (char)PTR_DAT_80433950[iVar6] * 4));
        if ((((PTR_DAT_80433930[0x32] == '\0') || (PTR_DAT_80433930[0x32] == '\x01')) &&
            (cVar2 != '\0')) && (pcVar10[0x88] == '\0')) {
          fVar1 = FLOAT_80436f7c * fVar1;
        }
        sVar12 = (&DAT_803b069c)[pcVar10[0x3e4]] - *param_1;
        fVar1 = fVar1 * (FLOAT_80436f78 /
                        (FLOAT_80436f78 +
                        FLOAT_80436f7c * (*(float *)(pcVar10 + 0xb4) - FLOAT_80436f78)));
        if (sVar12 < 1) {
          sVar12 = 0;
        }
        uVar3 = (uint)sVar12;
        if ((int)uVar3 < 0xc9) {
          if (*(short *)(pcVar10 + 0x1c4) < 200) {
            iVar11 = (int)(uVar3 << 5) / (int)*(short *)(pcVar10 + 0x1c4);
          }
          else {
            iVar11 = (int)(uVar3 << 5) / 200 + ((int)(uVar3 << 5 | uVar3 >> 0x1b) >> 0x1f);
            iVar11 = iVar11 - (iVar11 >> 0x1f);
          }
          iVar11 = 0x20 - iVar11;
          if (0x1f < iVar11) {
            iVar11 = 0x1f;
          }
          fVar1 = fVar1 * *(float *)(*(int *)((&PTR_PTR_80433608)[-iVar4] +
                                             (uint)*(byte *)(iVar5 + 0x9d) * 4) + iVar11 * 4);
        }
        iVar6 = 0x20 - (int)((&DAT_803b068c)[iVar6] << 5) /
                       *(int *)(PTR_DAT_80433934 + iVar6 * 0x3c + 0x114);
        if (0x1f < iVar6) {
          iVar6 = 0x1f;
        }
        dVar14 = (double)(fVar1 * *(float *)(*(int *)((&PTR_PTR_80433610)[-iVar4] +
                                                     (uint)*(byte *)(iVar5 + 0x9e) * 4) + iVar6 * 4)
                         * *(float *)((&PTR_DAT_80433618)[-iVar4] + pcVar10[0x43a] * 4));
        if ((param_1[9] & 0x4000) == 0) {
          dVar14 = (double)(float)(dVar14 * (double)*(float *)(&DAT_802c7ca0 + pcVar10[0x6ca] * 4));
        }
        if ((*(uint *)(pcVar10 + 0x5e0) & 0x4000000) != 0) {
          dVar14 = (double)(float)(dVar14 * (double)FLOAT_80436f7c);
        }
      }
      if ((pcVar13[0x88] == pcVar8[0x88]) && ((param_1[8] & 0x1000) == 0)) {
        dVar14 = (double)(float)(dVar14 * (double)FLOAT_80437024);
      }
      if (((param_3[0x83] == '\0') && ((param_1[8] & 0x1000) != 0)) &&
         ((*(ushort *)(param_3 + 0x59c) & 0x1000) != 0)) {
        dVar14 = (double)(float)(dVar14 / (double)FLOAT_80437028);
      }
      if (dVar14 < (double)FLOAT_80436f78) {
        dVar14 = (double)FLOAT_80436f78;
      }
      iVar4 = (int)dVar14;
    }
  }
  else {
    iVar4 = 0;
  }
  return iVar4;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0004.c 6832-6860 ==== */
// ==== 8003d344  zz_003d344_ ====

uint zz_003d344_(int param_1,short param_2)

{
  uint uVar1;
  
  if (*(short *)(param_1 + 0x1c6) == 0) {
    return 0;
  }
  if (PTR_DAT_80433934[0x1f] != '\0') {
    if (*(char *)(param_1 + 0x83) == '\0') {
      return 0;
    }
  }
  *(short *)(param_1 + 0x1c8) = *(short *)(param_1 + 0x1c6);
  *(short *)(param_1 + 0x1c6) = *(short *)(param_1 + 0x1c6) - param_2;
  if (*(short *)(param_1 + 0x1c6) < 0) {
    *(undefined2 *)(param_1 + 0x1c6) = 0;
  }
  else if (*(short *)(param_1 + 0x1c4) < *(short *)(param_1 + 0x1c6)) {
    *(short *)(param_1 + 0x1c6) = *(short *)(param_1 + 0x1c4);
  }
  if ((*(char *)(param_1 + 0x83) == '\0') && (*(char *)(param_1 + 0x4a0) == '\x01')) {
    *(undefined2 *)(*(int *)(param_1 + 0x4a4) + 0x1c6) = *(undefined2 *)(param_1 + 0x1c6);
  }
  uVar1 = countLeadingZeros((int)*(short *)(param_1 + 0x1c6));
  return uVar1 >> 5;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0008.c 2976-2982 ==== */
// ==== 80066298  zz_0066298_ ====

int zz_0066298_(char *param_1)

{
  return (int)*(short *)((&PTR_DAT_802f2e28)[*param_1] + (uint)(byte)param_1[1] * 2);
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0004.c 197-231 ==== */
// ==== 80031634  FUN_80031634 ====

/* WARNING: Removing unreachable block (ram,0x8003175c) */
/* WARNING: Removing unreachable block (ram,0x80031644) */

bool FUN_80031634(int param_1,int param_2,float *param_3,int *param_4)

{
  bool bVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float afStack_38 [5];
  
  gnt4_PSVECSubtract_bl
            (param_3,(float *)(param_1 + (char)(&DAT_802cffc8)[*param_4 * 4] * 0xc + 0x30),
             afStack_38);
  dVar3 = gnt4_PSQUATDotProduct_bl(afStack_38,(float *)(param_1 + *param_4 * 0x18 + 0x90));
  dVar4 = (double)(float)ABS(dVar3);
  gnt4_PSVECSubtract_bl
            (param_3 + 3,(float *)(param_1 + (char)(&DAT_802cffc8)[*param_4 * 4] * 0xc + 0x30),
             afStack_38);
  dVar3 = gnt4_PSQUATDotProduct_bl(afStack_38,(float *)(param_1 + *param_4 * 0x18 + 0x90));
  dVar2 = (double)(float)ABS(dVar3);
  dVar3 = dVar4;
  if (dVar2 < dVar4) {
    dVar3 = dVar2;
  }
  bVar1 = dVar3 <= (double)*(float *)(param_2 + 0x30);
  if (bVar1) {
    gnt4_PSQUATScale_bl(dVar3,(float *)(param_1 + *param_4 * 0x18 + 0x90),afStack_38);
    gnt4_PSVECSubtract_bl(param_3 + (uint)(dVar2 < dVar4) * 3,afStack_38,(float *)&DAT_803b0720);
  }
  return bVar1;
}
