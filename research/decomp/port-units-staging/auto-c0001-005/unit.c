#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8000f604(int param_1,int param_2);
void FUN_8000f72c(int param_1);
void FUN_8000f764(int param_1,int param_2);
void FUN_8000f7fc(int param_1,int param_2);
void FUN_8000f9e0(double param_1,double param_2,int param_3,int param_4,short param_5);
void FUN_8000fc2c(int param_1,int param_2);
undefined4 FUN_8000fe60(int param_1,int param_2);
undefined4 FUN_8000fffc(int param_1,int param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2517-2565 ==== */
// ==== 8000f604  FUN_8000f604 ====

void FUN_8000f604(int param_1,int param_2)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  double dVar7;
  
  fVar5 = FLOAT_80436b58;
  fVar4 = FLOAT_80436b40;
  fVar3 = FLOAT_80436acc;
  fVar2 = FLOAT_80436ac4;
  iVar6 = *(int *)(param_2 + 0x4ac);
  *(float *)(param_1 + 0x354) =
       FLOAT_80436ae8 * *(float *)(param_2 + 0xb4) +
       FLOAT_80436ac4 * (*(float *)(param_2 + 0xb4) - FLOAT_80436ac0) + FLOAT_80436ac0;
  *(float *)(param_1 + 0x350) = fVar5 * *(float *)(iVar6 + 400) * *(float *)(param_2 + 0xb4);
  *(float *)(param_1 + 0x348) =
       fVar4 * *(float *)(iVar6 + 0x198) * fVar2 * *(float *)(param_1 + 0x354);
  if (*(float *)(param_1 + 0x350) < fVar3) {
    *(float *)(param_1 + 0x350) = fVar3;
  }
  if (*(float *)(param_1 + 0x348) < FLOAT_80436b5c) {
    *(float *)(param_1 + 0x348) = FLOAT_80436b5c;
  }
  uVar1 = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x2e8) = uVar1;
  *(undefined4 *)(param_1 + 0x300) = uVar1;
  uVar1 = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)(param_1 + 0x2ec) = uVar1;
  *(undefined4 *)(param_1 + 0x304) = uVar1;
  uVar1 = *(undefined4 *)(param_2 + 0x28);
  *(undefined4 *)(param_1 + 0x2f0) = uVar1;
  *(undefined4 *)(param_1 + 0x308) = uVar1;
  *(float *)(param_1 + 0x304) = *(float *)(param_1 + 0x304) + *(float *)(param_1 + 0x350);
  dVar7 = zz_0045204_(*(short *)(param_2 + 0x72));
  *(float *)(param_1 + 0x2e8) =
       (float)((double)*(float *)(param_1 + 0x348) * dVar7 + (double)*(float *)(param_1 + 0x2e8));
  *(float *)(param_1 + 0x2ec) = *(float *)(param_1 + 0x2ec) + *(float *)(param_1 + 0x3d0);
  dVar7 = zz_0045238_(*(short *)(param_2 + 0x72));
  *(float *)(param_1 + 0x2f0) =
       (float)((double)*(float *)(param_1 + 0x348) * dVar7 + (double)*(float *)(param_1 + 0x2f0));
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2569-2576 ==== */
// ==== 8000f72c  FUN_8000f72c ====

void FUN_8000f72c(int param_1)

{
  (*(code *)(&PTR_FUN_804335d8)[*(char *)(param_1 + 0x19)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2580-2600 ==== */
// ==== 8000f764  FUN_8000f764 ====

void FUN_8000f764(int param_1,int param_2)

{
  if (*(int *)(PTR_DAT_80433934 + 0xbc) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_2 + 0x43d) = 0;
    *(undefined1 *)(param_2 + 0x6f8) = 0;
  }
  else {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined1 *)(param_1 + 0x1a) = 0;
    FUN_801fe050(0);
    FUN_8000f9e0((double)FLOAT_80436aa8,(double)FLOAT_80436b1c,param_1,param_2,-0x8000);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2604-2673 ==== */
// ==== 8000f7fc  FUN_8000f7fc ====

void FUN_8000f7fc(int param_1,int param_2)

{
  char cVar1;
  short sVar2;
  
  if (((*(byte *)(param_2 + 0x3e5) & PTR_DAT_80433930[2]) != 0) &&
     (((&DAT_803c7204)[*(char *)(param_2 + 0x3e4) * 8] & 0x1000) != 0)) {
    *(undefined1 *)(DAT_803c4e84 + 0x43d) = 0;
    *(undefined1 *)(DAT_803c4e88 + 0x43d) = 0;
    *(undefined1 *)(DAT_803c4e8c + 0x43d) = 0;
    *(undefined1 *)(DAT_803c4e90 + 0x43d) = 0;
    *(undefined1 *)(DAT_803c4e94 + 0x43d) = 0;
    *(undefined1 *)(DAT_803c4e98 + 0x43d) = 0;
    FUN_801fe134();
    return;
  }
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_8000f964;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(undefined2 *)(param_1 + 0x1c) = 0x154;
    }
    else if (cVar1 < '\0') {
      return;
    }
    sVar2 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (0 < sVar2) {
      return;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0x348;
    *(undefined2 *)(param_1 + 0x7e) = 0;
  }
  FUN_8000f9e0((double)FLOAT_80436b60,(double)FLOAT_80436b38,param_1,
               *(int *)(PTR_DAT_80433934 + 0xbc),*(short *)(param_1 + 0x7e) + 0x2000);
  *(short *)(param_1 + 0x7e) = *(short *)(param_1 + 0x7e) + 0x40;
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (0 < sVar2) {
    return;
  }
  *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  *(undefined2 *)(param_1 + 0x1c) = 0x168;
LAB_8000f964:
  FUN_8000f9e0((double)FLOAT_80436b64,(double)FLOAT_80436b44,param_1,
               *(int *)(PTR_DAT_80433934 + 0xbc),*(short *)(param_1 + 0x7e) + 0x2000);
  *(short *)(param_1 + 0x7e) = *(short *)(param_1 + 0x7e) + 0x40;
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_2 + 0x43d) = 0;
    *(undefined1 *)(param_2 + 0x6f8) = 0;
    FUN_801fe134();
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2677-2762 ==== */
// ==== 8000f9e0  FUN_8000f9e0 ====

/* WARNING: Removing unreachable block (ram,0x8000fc10) */
/* WARNING: Removing unreachable block (ram,0x8000f9f0) */

void FUN_8000f9e0(double param_1,double param_2,int param_3,int param_4,short param_5)

{
  float fVar1;
  undefined4 uVar2;
  double dVar3;
  double dVar4;
  float local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  float local_30;
  float local_2c;
  float local_28;
  
  *(float *)(param_3 + 0x348) =
       (float)((double)*(float *)(param_4 + *(char *)(param_4 + 0x582) * 8 + 0x898) * param_2);
  *(float *)(param_3 + 0x350) =
       (float)((double)*(float *)(param_4 + *(char *)(param_4 + 0x582) * 4 + 0x88c) + param_1);
  fVar1 = FLOAT_80436ad4;
  if (((PTR_DAT_80433930[0x29] == '\x01') && (PTR_DAT_80433930[0x3d] == '\0')) ||
     (PTR_DAT_80433930[0x29] == '\x02')) {
    *(float *)(param_3 + 0x348) = *(float *)(param_3 + 0x348) * FLOAT_80436ad0;
    *(float *)(param_3 + 0x350) = *(float *)(param_3 + 0x350) * fVar1;
  }
  uVar2 = *(undefined4 *)(param_4 + 0x20);
  *(undefined4 *)(param_3 + 0x30c) = uVar2;
  *(undefined4 *)(param_3 + 0x300) = uVar2;
  fVar1 = *(float *)(param_4 + 0x6d0) + *(float *)(param_4 + 0x24) + *(float *)(param_3 + 0x350);
  *(float *)(param_3 + 0x310) = fVar1;
  *(float *)(param_3 + 0x304) = fVar1;
  uVar2 = *(undefined4 *)(param_4 + 0x28);
  *(undefined4 *)(param_3 + 0x314) = uVar2;
  *(undefined4 *)(param_3 + 0x308) = uVar2;
  *(undefined2 *)(param_3 + 0x70) = 0x600;
  *(short *)(param_3 + 0x72) = *(short *)(param_4 + 0x72) + param_5;
  *(undefined2 *)(param_3 + 0x74) = 0;
  dVar3 = zz_0045238_(*(short *)(param_3 + 0x70));
  dVar4 = (double)(float)((double)*(float *)(param_3 + 0x348) * dVar3);
  dVar3 = zz_0045204_(*(short *)(param_3 + 0x72));
  fVar1 = (float)(dVar3 * dVar4 + (double)*(float *)(param_3 + 0x300));
  *(float *)(param_3 + 0x2f4) = fVar1;
  *(float *)(param_3 + 0x2e8) = fVar1;
  dVar3 = zz_0045204_(*(short *)(param_3 + 0x70));
  fVar1 = (float)((double)*(float *)(param_3 + 0x348) * dVar3 + (double)*(float *)(param_3 + 0x304))
  ;
  *(float *)(param_3 + 0x2f8) = fVar1;
  *(float *)(param_3 + 0x2ec) = fVar1;
  dVar3 = zz_0045238_(*(short *)(param_3 + 0x70));
  dVar4 = (double)(float)((double)*(float *)(param_3 + 0x348) * dVar3);
  dVar3 = zz_0045238_(*(short *)(param_3 + 0x72));
  fVar1 = (float)(dVar3 * dVar4 + (double)*(float *)(param_3 + 0x308));
  *(float *)(param_3 + 0x2fc) = fVar1;
  *(float *)(param_3 + 0x2f0) = fVar1;
  gnt4_PSVECSubtract_bl((float *)(param_3 + 0x300),(float *)(param_3 + 0x2e8),&local_48);
  local_28 = -local_48;
  local_30 = local_40;
  local_2c = FLOAT_80436aa8;
  gnt4_PSVECCrossProduct_bl(&local_48,&local_30,&local_3c);
  gnt4_PSVECNormalize_bl(&local_30,&local_30);
  gnt4_PSVECNormalize_bl(&local_3c,&local_3c);
  gnt4_PSVECNormalize_bl(&local_48,&local_48);
  *(float *)(param_3 + 0x364) = local_30;
  *(float *)(param_3 + 0x374) = local_2c;
  *(float *)(param_3 + 900) = local_28;
  *(float *)(param_3 + 0x368) = local_30;
  *(float *)(param_3 + 0x378) = local_2c;
  *(float *)(param_3 + 0x388) = local_28;
  *(float *)(param_3 + 0x36c) = local_48;
  *(undefined4 *)(param_3 + 0x37c) = local_44;
  *(float *)(param_3 + 0x38c) = local_40;
  *(undefined4 *)(param_3 + 0x370) = *(undefined4 *)(param_3 + 0x2e8);
  *(undefined4 *)(param_3 + 0x380) = *(undefined4 *)(param_3 + 0x2ec);
  *(undefined4 *)(param_3 + 0x390) = *(undefined4 *)(param_3 + 0x2f0);
  *(float *)(param_3 + 0x330) = local_3c;
  *(undefined4 *)(param_3 + 0x334) = local_38;
  *(undefined4 *)(param_3 + 0x338) = local_34;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2766-2840 ==== */
// ==== 8000fc2c  FUN_8000fc2c ====

void FUN_8000fc2c(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  float fStack_20;
  float local_1c;
  
  fVar1 = FLOAT_80436ac4;
  *(float *)(param_1 + 0x350) =
       (*(float *)(param_2 + *(char *)(param_2 + 0x582) * 4 + 0x88c) * *(float *)(param_1 + 0x354) +
       *(float *)(param_1 + 0x350)) * FLOAT_80436ac4;
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_2 + 0x20);
  *(float *)(param_1 + 0x304) =
       (*(float *)(param_2 + 0x6d0) +
       *(float *)(param_1 + 0x350) + *(float *)(param_1 + 0x310) + *(float *)(param_2 + 0x24)) *
       fVar1;
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_2 + 0x28);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_2 + 0x20),&fStack_20);
  local_1c = FLOAT_80436aa8;
  dVar3 = gnt4_PSVECSquareMag_bl(&fStack_20);
  if (*(char *)(param_2 + 0x582) == '\0') {
    fVar1 = *(float *)(param_2 + 0x898);
    fVar2 = *(float *)(param_2 + 0x894);
  }
  else {
    fVar1 = *(float *)(param_2 + 0x8a0);
    fVar2 = *(float *)(param_2 + 0x89c);
  }
  dVar5 = (double)(fVar1 * *(float *)(param_1 + 0x354));
  dVar4 = (double)(fVar2 * *(float *)(param_1 + 0x354));
  if (((PTR_DAT_80433930[0x29] == '\x01') && (PTR_DAT_80433930[0x3d] == '\0')) ||
     (PTR_DAT_80433930[0x29] == '\x02')) {
    dVar5 = (double)(float)(dVar5 * (double)FLOAT_80436ad0);
    dVar4 = (double)(float)(dVar4 * (double)FLOAT_80436ad0);
  }
  if (dVar3 <= (double)(float)(dVar5 * dVar5)) {
    if ((double)(float)(dVar4 * dVar4) <= dVar3) {
      if ((double)FLOAT_80436aa8 < dVar3) {
        dVar4 = 1.0 / SQRT(dVar3);
        dVar4 = DOUBLE_80436ab0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8);
        dVar4 = DOUBLE_80436ab0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8);
        dVar3 = (double)(float)(dVar3 * DOUBLE_80436ab0 * dVar4 *
                                        -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8));
      }
      *(float *)(param_1 + 0x348) = (float)dVar3;
      *(undefined1 *)(param_1 + 0x35e) = 0;
    }
    else {
      *(float *)(param_1 + 0x348) = (float)dVar4;
      *(undefined1 *)(param_1 + 0x35e) = 0;
    }
  }
  else if ((*(char *)(param_1 + 0x35e) == '\0') && (*(char *)(param_2 + 0x7c9) == '\0')) {
    *(float *)(param_1 + 0x348) = (float)dVar5;
  }
  else {
    if ((double)FLOAT_80436aa8 < dVar3) {
      dVar4 = 1.0 / SQRT(dVar3);
      dVar4 = DOUBLE_80436ab0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8);
      dVar4 = DOUBLE_80436ab0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8);
      dVar3 = (double)(float)(dVar3 * DOUBLE_80436ab0 * dVar4 *
                                      -(dVar3 * dVar4 * dVar4 - DOUBLE_80436ab8));
    }
    *(float *)(param_1 + 0x348) =
         (float)((double)FLOAT_80436b38 * (double)(float)(dVar3 - dVar5) + dVar5);
    *(undefined1 *)(param_1 + 0x35e) = 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2844-2918 ==== */
// ==== 8000fe60  FUN_8000fe60 ====

/* WARNING: Removing unreachable block (ram,0x8000ffdc) */
/* WARNING: Removing unreachable block (ram,0x8000ffd4) */
/* WARNING: Removing unreachable block (ram,0x8000fe78) */
/* WARNING: Removing unreachable block (ram,0x8000fe70) */

undefined4 FUN_8000fe60(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  undefined4 uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  
  uVar5 = 0;
  if (*(int *)(param_2 + 0x508) == 0) {
    local_34 = FLOAT_80436aa8;
    local_3c = FLOAT_80436aa8;
    local_38 = FLOAT_80436b70;
    FUN_800450e0(-(double)(FLOAT_80436b18 * *(float *)(param_1 + 0x348)),(double)FLOAT_80436b6c,
                 (float *)(param_1 + 0x394),&local_3c,(float *)(param_1 + 0x324));
  }
  else {
    if ((*(uint *)(param_2 + 0x5e0) & 0x40) == 0) {
      sVar3 = (short)*(char *)(param_2 + 0x582) << 1;
    }
    else {
      sVar3 = *(char *)(param_2 + 0x582) * 2 + 4;
    }
    if (*(char *)(param_1 + 0x360) == '\0') {
      iVar4 = param_2 + sVar3 * 4;
      fVar1 = *(float *)(iVar4 + 0x8a4);
      fVar2 = *(float *)(iVar4 + 0x8a8);
    }
    else {
      iVar4 = param_2 + sVar3 * 4;
      fVar1 = FLOAT_80436b68 * *(float *)(iVar4 + 0x8a8);
      fVar2 = FLOAT_80436b68 * *(float *)(iVar4 + 0x8a4);
    }
    dVar8 = (double)fVar1;
    dVar7 = (double)fVar2;
    FUN_8004503c((double)FLOAT_80436b6c,(float *)(param_1 + 0x394),(float *)(param_2 + 0x50c),
                 &local_3c);
    dVar6 = (double)local_38;
    if (dVar6 <= dVar8) {
      if (dVar7 <= dVar6) {
        local_44 = FLOAT_80436aa8;
      }
      else {
        local_44 = (float)(dVar6 - dVar7);
        uVar5 = 1;
      }
    }
    else {
      local_44 = (float)(dVar6 - dVar8);
      uVar5 = 1;
    }
    local_48 = local_3c;
    local_40 = FLOAT_80436aa8;
    FUN_800450e0(-(double)(FLOAT_80436b18 * *(float *)(param_1 + 0x348)),(double)FLOAT_80436b6c,
                 (float *)(param_1 + 0x394),&local_48,(float *)(param_1 + 0x324));
  }
  return uVar5;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2922-2990 ==== */
// ==== 8000fffc  FUN_8000fffc ====

undefined4 FUN_8000fffc(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  double dVar4;
  float local_18;
  float local_14;
  float local_10;
  
  if (*(char *)(param_1 + 0x35e) == '\0') {
    if (*(char *)(param_1 + 0x35f) == '\x01') {
      uVar3 = 0;
    }
    else {
      if (*(char *)(param_2 + 0x582) == '\0') {
        fVar1 = *(float *)(param_2 + 0x898);
        fVar2 = *(float *)(param_2 + 0x894);
      }
      else {
        fVar1 = *(float *)(param_2 + 0x8a0);
        fVar2 = *(float *)(param_2 + 0x89c);
      }
      fVar1 = fVar1 * *(float *)(param_1 + 0x354);
      fVar2 = fVar2 * *(float *)(param_1 + 0x354);
      if (((PTR_DAT_80433930[0x29] == '\x01') && (PTR_DAT_80433930[0x3d] == '\0')) ||
         (PTR_DAT_80433930[0x29] == '\x02')) {
        fVar1 = fVar1 * FLOAT_80436ad0;
        fVar2 = fVar2 * FLOAT_80436ad0;
      }
      if (fVar2 <= *(float *)(param_1 + 0x348)) {
        if (*(float *)(param_1 + 0x348) <= fVar1) {
          return 0;
        }
        *(float *)(param_1 + 0x348) = fVar1;
      }
      else {
        *(float *)(param_1 + 0x348) = fVar2;
      }
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),&local_18);
      local_14 = FLOAT_80436aa8;
      gnt4_PSVECNormalize_bl(&local_18,&local_18);
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_18,&local_18);
      local_18 = local_18 + *(float *)(param_1 + 0x300);
      dVar4 = zz_004526c_(*(short *)(param_1 + 0x70));
      fVar2 = FLOAT_80436b74;
      fVar1 = FLOAT_80436b0c;
      local_14 = (float)((double)*(float *)(param_1 + 0x348) * dVar4 +
                        (double)*(float *)(param_1 + 0x304));
      local_10 = local_10 + *(float *)(param_1 + 0x308);
      *(float *)(param_1 + 0x318) =
           (FLOAT_80436b74 * *(float *)(param_1 + 0x318) + local_18) * FLOAT_80436b0c;
      *(float *)(param_1 + 0x31c) = (fVar2 * *(float *)(param_1 + 0x31c) + local_14) * fVar1;
      *(float *)(param_1 + 800) = (fVar2 * *(float *)(param_1 + 800) + local_10) * fVar1;
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x318),(float *)(param_1 + 0x300),&local_18);
      gnt4_PSVECNormalize_bl(&local_18,&local_18);
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_18,&local_18);
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),&local_18,(float *)(param_1 + 0x2e8));
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}
