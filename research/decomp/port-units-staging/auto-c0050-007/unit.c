#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01a4944_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
void zz_01a49e4_(int param_1);
void zz_01a49f8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void zz_01a4a40_(int param_1);
void zz_01a4b18_(int param_1);
void zz_01a4b9c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
int zz_01a4cd4_(int param_1);
void zz_01a4d9c_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1965-1994 ==== */
// ==== 801a4944  zz_01a4944_ ====

void zz_01a4944_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_9 + 0x8c);
  iVar3 = *(int *)(iVar4 + 0x54);
  uVar1 = *(undefined4 *)(iVar3 + 0x24);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(iVar3 + 0x20);
  *(undefined4 *)(param_9 + 0x24) = uVar1;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar3 + 0x28);
  *(undefined4 *)(param_9 + 0xb4) = *(undefined4 *)(iVar3 + 0xb4);
  zz_01a4cd4_(param_9);
  sVar2 = *(short *)(param_9 + 0x1e) + -1;
  *(short *)(param_9 + 0x1e) = sVar2;
  if (sVar2 < 1) {
    zz_01a4b9c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (('\x01' < *(char *)(iVar4 + 0x18)) || (*(short *)(iVar4 + 0x94) != *(short *)(param_9 + 0x94))
     ) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1998-2006 ==== */
// ==== 801a49e4  zz_01a49e4_ ====

void zz_01a49e4_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 2010-2022 ==== */
// ==== 801a49f8  zz_01a49f8_ ====

void zz_01a49f8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 2026-2076 ==== */
// ==== 801a4a40  zz_01a4a40_ ====

void zz_01a4a40_(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_58 [3];
  float afStack_4c [14];
  
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar4) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar4) != 0) {
      iVar3 = *(int *)(param_1 + 0x54) + iVar6;
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(iVar3 + 0x14),afStack_58);
      dVar8 = (double)*(float *)(iVar3 + 0xc);
      dVar9 = (double)*(float *)(iVar3 + 0x10);
      gnt4_PSMTXTrans_bl((double)*(float *)(iVar3 + 8),dVar8,dVar9,afStack_4c);
      zz_00457d4_('y',afStack_4c,afStack_4c,*(short *)(iVar3 + 0x22));
      iVar2 = (int)*(short *)(iVar3 + 0x20);
      zz_00457d4_('x',afStack_4c,afStack_4c,*(short *)(iVar3 + 0x20));
      pfVar1 = afStack_58;
      uVar7 = zz_00456a0_(afStack_4c,afStack_4c,pfVar1);
      zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_4c,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
    }
    iVar6 = iVar6 + 0x28;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 2080-2099 ==== */
// ==== 801a4b18  zz_01a4b18_ ====

void zz_01a4b18_(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar1) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar1) != 0) {
      zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
    }
    iVar2 = iVar2 + 4;
    iVar1 = iVar1 + 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 2103-2152 ==== */
// ==== 801a4b9c  zz_01a4b9c_ ====

void zz_01a4b9c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar6;
  int iVar7;
  undefined8 uVar8;
  
  iVar7 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar7) break;
    if (((int)(short)*(ushort *)(param_9 + 0x1c) & 1 << iVar7) == 0) {
      iVar5 = *(int *)(param_9 + 0x54);
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar7);
      piVar6 = (int *)(iVar5 + iVar7 * 0x28);
      *(undefined2 *)(param_9 + 0x1e) = 3;
      iVar4 = *(char *)(param_9 + 0x11) * 8;
      *(undefined1 *)(piVar6 + 9) = 0;
      *(undefined1 *)((int)piVar6 + 0x25) = *(undefined1 *)(iVar4 + -0x7fbca89d);
      iVar2 = *(int *)(param_9 + 0x24);
      piVar6[2] = *(int *)(param_9 + 0x20);
      piVar6[3] = iVar2;
      piVar6[4] = *(int *)(param_9 + 0x28);
      uVar3 = zz_00055fc_();
      *(short *)(piVar6 + 8) = (short)(uVar3 << 8);
      uVar3 = zz_00055fc_();
      *(short *)((int)piVar6 + 0x22) = (short)(uVar3 << 8);
      uVar8 = zz_0018f88_(piVar6,*(int *)(iVar4 + -0x7fbca89c),(float *)(piVar6 + 5));
      uVar3 = zz_00055fc_();
      cVar1 = (&DAT_80435760)[uVar3 % 3 + iVar4];
      iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
      zz_0006fb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                  *(int *)(param_9 + iVar7 * 4 + 0xe0),(int)cVar1,iVar5,in_r7,in_r8,in_r9,in_r10);
      iVar7 = (int)*(char *)(param_9 + 0x13);
    }
    iVar7 = iVar7 + 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 2156-2184 ==== */
// ==== 801a4cd4  zz_01a4cd4_ ====

int zz_01a4cd4_(int param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar3) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar3) != 0) {
      piVar2 = (int *)(*(int *)(param_1 + 0x54) + iVar4);
      cVar1 = *(char *)(piVar2 + 9);
      *(char *)(piVar2 + 9) = cVar1 + '\x01';
      if (*(char *)((int)piVar2 + 0x25) <= (char)(cVar1 + '\x01')) {
        *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) & ~(ushort)(1 << iVar3);
      }
      piVar2[3] = (int)((float)piVar2[3] + FLOAT_8043b630);
      zz_0018fd8_(piVar2,(int)*(char *)(piVar2 + 9),(float *)(piVar2 + 5));
    }
    iVar4 = iVar4 + 0x28;
    iVar3 = iVar3 + 1;
  }
  return (int)*(short *)(param_1 + 0x1c);
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 2188-2219 ==== */
// ==== 801a4d9c  zz_01a4d9c_ ====

void zz_01a4d9c_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x407) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,4), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = zz_01a4e90_;
    *(code **)(puVar1 + 0x10c) = zz_01a50f8_;
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
