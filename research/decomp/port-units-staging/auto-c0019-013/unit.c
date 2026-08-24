#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800be8cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_800be8ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_00be948_(int param_1,undefined1 param_2);
void FUN_800bec20(int param_1);
void FUN_800becb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
uint FUN_800bee1c(int param_1);
void FUN_800bf144(float *param_1);
void FUN_800bf210(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2859-2867 ==== */
// ==== 800be8cc  FUN_800be8cc ====

void FUN_800be8cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2871-2891 ==== */
// ==== 800be8ec  FUN_800be8ec ====

void FUN_800be8ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = *(int *)(param_9 + 0xe0);
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x45);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2895-2976 ==== */
// ==== 800be948  zz_00be948_ ====

void zz_00be948_(int param_1,undefined1 param_2)

{
  char cVar1;
  short sVar2;
  undefined1 *puVar3;
  int iVar4;
  
  sVar2 = *(short *)(param_1 + 1000);
  if (((((sVar2 == 0x500) || (sVar2 == 0x509)) || (sVar2 == 0x50a)) ||
      (((sVar2 == 0x50c || (sVar2 == 0x515)) || (sVar2 == 0x516)))) &&
     (puVar3 = zz_0088aa0_(param_1,3,8,0,6), puVar3 != (undefined1 *)0x0)) {
    *puVar3 = 1;
    puVar3[0x83] = 0x10;
    puVar3[0x10] = 0x2f;
    puVar3[0x11] = param_2;
    *(code **)(puVar3 + 0xc) = FUN_800bec20;
    *(code **)(puVar3 + 0x10c) = FUN_800bf26c;
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
    iVar4 = (uint)(byte)puVar3[0x11] * 0x30;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8d4),
               (float *)(iVar4 + -0x7fcfe514),(float *)(puVar3 + 0x20));
    if (*(char *)(param_1 + 0x587) == '\x02') {
      cVar1 = (&DAT_80301b14)[iVar4];
      if (cVar1 == '\x01') {
        *(undefined4 *)(puVar3 + 0x38) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8d8);
        *(undefined4 *)(puVar3 + 0x3c) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8e8);
        *(undefined4 *)(puVar3 + 0x40) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8f8);
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(undefined4 *)(puVar3 + 0x38) =
               *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8d4);
          *(undefined4 *)(puVar3 + 0x3c) =
               *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8e4);
          *(undefined4 *)(puVar3 + 0x40) =
               *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8f4);
        }
      }
      else if (cVar1 < '\x03') {
        *(undefined4 *)(puVar3 + 0x38) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8dc);
        *(undefined4 *)(puVar3 + 0x3c) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8ec);
        *(undefined4 *)(puVar3 + 0x40) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8fc);
      }
      if ((&DAT_80301b15)[iVar4] == '\x01') {
        gnt4_PSQUATScale_bl((double)FLOAT_80438598,(float *)(puVar3 + 0x38),(float *)(puVar3 + 0x38)
                           );
      }
    }
    else {
      zz_0083d60_((int)puVar3,param_1,0);
    }
    gnt4_PSVECNormalize_bl((float *)(puVar3 + 0x38),(float *)(puVar3 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80301af8 + iVar4),(float *)(puVar3 + 0x38),
                        (float *)(puVar3 + 0x38));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2980-2994 ==== */
// ==== 800bec20  FUN_800bec20 ====

void FUN_800bec20(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80301c08)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2998-3067 ==== */
// ==== 800becb8  FUN_800becb8 ====

void FUN_800becb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  
  puVar5 = &DAT_80301ae8;
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar6 = (uint)*(byte *)(param_9 + 0x11) * 0x30;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar7 = iVar6;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  fVar1 = FLOAT_8043859c;
  *(undefined1 *)(param_9 + 0x98) = 3;
  fVar2 = FLOAT_804385a0;
  *(float *)(param_9 + 0xa0) = fVar1;
  *(float *)(param_9 + 0x9c) = fVar1;
  *(float *)(param_9 + 0xa4) = fVar2;
  uVar9 = zz_0048288_(param_9);
  *(undefined2 *)(param_9 + 0x1c) = 600;
  iVar3 = zz_008ac80_(param_9,(int)(char)(&DAT_80301aeb)[iVar6]);
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar4 = zz_0006f78_(param_9);
    iVar8 = 0;
    iVar3 = param_9;
    do {
      uVar9 = zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                          *(int *)(iVar3 + 0xe0),(uint)(byte)(&DAT_80301ae8)[iVar6],puVar5,iVar7,
                          in_r8,in_r9,in_r10);
      iVar8 = iVar8 + 1;
      iVar3 = iVar3 + 4;
    } while (iVar8 < 5);
    zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                *(int *)(param_9 + 0xf4),(uint)(byte)(&DAT_80301ae9)[iVar6],puVar5,iVar7,in_r8,in_r9
                ,in_r10);
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80301af8 + iVar6),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    fVar1 = FLOAT_8043859c;
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80301af8 + iVar6);
    dVar10 = (double)FLOAT_804385a4;
    *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_80301afc + iVar6);
    *(undefined2 *)(param_9 + 0x72) = 0;
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    *(undefined1 *)(param_9 + 0x144) = 0;
    *(undefined1 *)(param_9 + 0x145) = 0;
    *(float *)(param_9 + 0x148) = fVar1;
    zz_00f061c_(dVar10,param_9,199);
    FUN_800bee1c(param_9);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 3071-3182 ==== */
// ==== 800bee1c  FUN_800bee1c ====

/* WARNING: Removing unreachable block (ram,0x800bf128) */
/* WARNING: Removing unreachable block (ram,0x800bf120) */
/* WARNING: Removing unreachable block (ram,0x800bee34) */
/* WARNING: Removing unreachable block (ram,0x800bee2c) */

uint FUN_800bee1c(int param_1)

{
  float fVar1;
  char cVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  bool bVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x11c);
  iVar4 = (uint)*(byte *)(param_1 + 0x11) * 0x30;
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 300);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x13c);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0xccc;
  if (*(char *)(param_1 + 0x145) != '\0') {
    dVar10 = (double)FLOAT_804385a0;
    dVar11 = (double)FLOAT_804385a8;
    iVar8 = *(char *)(param_1 + 0x144) + 4;
    iVar9 = iVar8 / 5 + (iVar8 >> 0x1f);
    iVar8 = iVar8 + (iVar9 - (iVar9 >> 0x1f)) * -5;
    for (iVar9 = 0; iVar9 < *(char *)(param_1 + 0x145); iVar9 = iVar9 + 1) {
      iVar5 = param_1 + iVar8 * 0x14;
      fVar1 = (float)((double)*(float *)(iVar5 + 0x158) + dVar10);
      *(float *)(iVar5 + 0x158) = fVar1;
      if ((double)fVar1 <= dVar11) {
        FUN_800bf144((float *)(iVar5 + 0x14c));
      }
      else {
        *(char *)(param_1 + 0x145) = *(char *)(param_1 + 0x145) + -1;
      }
      iVar8 = iVar8 + 4;
      iVar5 = iVar8 / 5 + (iVar8 >> 0x1f);
      iVar8 = iVar8 + (iVar5 - (iVar5 >> 0x1f)) * -5;
    }
  }
  fVar3 = FLOAT_8043859c;
  fVar1 = *(float *)(param_1 + 0x148) - FLOAT_804385a0;
  *(float *)(param_1 + 0x148) = fVar1;
  if ((fVar1 <= fVar3) && (*(char *)(param_1 + 0x145) < '\x05')) {
    *(float *)(param_1 + 0x148) = FLOAT_804385ac;
    cVar2 = *(char *)(param_1 + 0x144);
    iVar9 = param_1 + cVar2 * 0x14;
    *(float *)(iVar9 + 0x158) = fVar3;
    uVar6 = zz_00055fc_();
    *(short *)(iVar9 + 0x15c) = (short)(uVar6 << 0xb);
    *(undefined1 *)(iVar9 + 0x15e) = 0;
    FUN_800bf144((float *)(iVar9 + 0x14c));
    iVar8 = cVar2 + 1;
    iVar9 = iVar8 / 5 + (iVar8 >> 0x1f);
    *(char *)(param_1 + 0x144) = (char)iVar8 + ((char)iVar9 - (char)(iVar9 >> 0x1f)) * -5;
    *(char *)(param_1 + 0x145) = *(char *)(param_1 + 0x145) + '\x01';
  }
  if ((0 < *(short *)(param_1 + 0x1c)) &&
     (iVar9 = zz_0083244_((float *)(param_1 + 0x20)), iVar9 == 0)) {
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      FUN_80083874((double)*(float *)(&DAT_80301b04 + iVar4),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_80301b00 + iVar4),param_1,
                   (char)*(undefined4 *)(&DAT_80301afc + iVar4));
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      iVar9 = zz_0083714_(param_1);
      if (iVar9 == 0) {
        iVar9 = zz_0084170_(param_1);
        if (iVar9 == 0) {
          return 0;
        }
        *(undefined1 *)(param_1 + 0x18) = 2;
        uVar6 = zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),(&DAT_80301b16)[iVar4]);
        cVar2 = (&DAT_80301b17)[iVar4];
        if (cVar2 == '\x02') {
          bVar7 = zz_0183730_(param_1,3,0xff);
          return (uint)bVar7;
        }
        if ('\x01' < cVar2) {
          return uVar6;
        }
        if (cVar2 < '\x01') {
          return uVar6;
        }
        bVar7 = zz_0183730_(param_1,2,0xff);
        return (uint)bVar7;
      }
    }
    else {
      zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),(&DAT_80301b16)[iVar4]);
      cVar2 = (&DAT_80301b17)[iVar4];
      if (cVar2 == '\x02') {
        zz_0183730_(param_1,3,0xff);
      }
      else if ((cVar2 < '\x02') && ('\0' < cVar2)) {
        zz_0183730_(param_1,2,0xff);
      }
    }
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  uVar6 = zz_008aff0_(param_1);
  return uVar6;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 3186-3223 ==== */
// ==== 800bf144  FUN_800bf144 ====

void FUN_800bf144(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = FLOAT_804385b0;
  iVar5 = *(char *)((int)param_1 + 0x12) * 0x10;
  fVar4 = *(float *)(&DAT_80301c18 + iVar5);
  fVar1 = *(float *)(&DAT_80301c1c + iVar5);
  fVar2 = *(float *)(&DAT_80301c20 + iVar5);
  fVar3 = *(float *)(&DAT_80301c24 + iVar5);
  if ((param_1[3] == fVar4) || (FLOAT_804385b0 == fVar4)) {
    *param_1 = fVar1;
    param_1[1] = fVar2;
    param_1[2] = fVar3;
    return;
  }
  fVar6 = param_1[3] - fVar4;
  iVar5 = (*(char *)((int)param_1 + 0x12) + 1) * 0x10;
  fVar4 = *(float *)(&DAT_80301c18 + iVar5) - fVar4;
  *param_1 = ((*(float *)(&DAT_80301c1c + iVar5) - fVar1) / fVar4) * fVar6 + fVar1;
  param_1[1] = ((*(float *)(&DAT_80301c20 + iVar5) - fVar2) / fVar4) * fVar6 + fVar2;
  param_1[2] = ((*(float *)(&DAT_80301c24 + iVar5) - fVar3) / fVar4) * fVar6 + fVar3;
  fVar1 = *(float *)(&DAT_80301c18 + iVar5);
  if ((param_1[3] <= fVar1) && (fVar7 != fVar1)) {
    return;
  }
  *(char *)((int)param_1 + 0x12) = *(char *)((int)param_1 + 0x12) + '\x01';
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 3227-3236 ==== */
// ==== 800bf210  FUN_800bf210 ====

void FUN_800bf210(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}
