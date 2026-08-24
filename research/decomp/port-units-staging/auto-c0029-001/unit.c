#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01049d4_(int param_1);
void zz_0104ae4_(int param_1);
void zz_0104b38_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
void zz_0104c58_(int param_1);
void zz_0104c7c_(int param_1);
void zz_0104cc8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void zz_0104ce8_(int param_1);
void zz_0104e98_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 262-298 ==== */
// ==== 801049d4  zz_01049d4_ ====

void zz_01049d4_(int param_1)

{
  undefined1 *puVar1;
  int *piVar2;
  
  if ((*(short *)(param_1 + 1000) == 0xb03) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = zz_0104ae4_;
    *(code **)(puVar1 + 0x10c) = zz_0104e98_;
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
    piVar2 = zz_0006dc8_(0xf0);
    *(int **)(puVar1 + 0xdc) = piVar2;
    if (piVar2 == (int *)0x0) {
      puVar1[0x18] = 2;
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 302-310 ==== */
// ==== 80104ae4  zz_0104ae4_ ====

void zz_0104ae4_(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_zz_0104b38__80321744)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 314-371 ==== */
// ==== 80104b38  zz_0104b38_ ====

void zz_0104b38_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  double dVar6;
  undefined8 uVar7;
  int local_18 [4];
  
  iVar5 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(code **)(param_9 + 0x100) = zz_0104ce8_;
  zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_804393f0;
  dVar6 = (double)FLOAT_804393f0;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  fVar2 = FLOAT_804393f4;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(undefined1 *)(param_9 + 0x89) = 7;
  *(float *)(param_9 + 100) = fVar2;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar2;
  iVar5 = zz_0006f98_(iVar5);
  uVar7 = zz_0007030_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),9,iVar5 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar4 = iVar5 + 0xc28;
  uVar3 = 9;
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),9,iVar4,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  uVar7 = zz_0007cac_((double)FLOAT_804393f8,*(int *)(param_9 + 0xe4));
  local_18[0] = 0;
  zz_0009b38_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(*(int *)(param_9 + 0xe0) + 0xc),*(int *)(*(int *)(param_9 + 0xdc) + 0xc),
              local_18,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0104f20_(param_9,(float *)(param_9 + 0x144));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0104c58_(param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 375-382 ==== */
// ==== 80104c58  zz_0104c58_ ====

void zz_0104c58_(int param_1)

{
  zz_0104f8c_(param_1,(float *)(param_1 + 0x144));
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 386-397 ==== */
// ==== 80104c7c  zz_0104c7c_ ====

void zz_0104c7c_(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  if (*(int **)(param_1 + 0xdc) != (int *)0x0) {
    zz_0197ad8_(*(int **)(param_1 + 0xdc));
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 401-409 ==== */
// ==== 80104cc8  zz_0104cc8_ ====

void zz_0104cc8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 413-475 ==== */
// ==== 80104ce8  zz_0104ce8_ ====

/* WARNING: Removing unreachable block (ram,0x80104e78) */
/* WARNING: Removing unreachable block (ram,0x80104cf8) */

void zz_0104ce8_(int param_1)

{
  float *pfVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  
  FUN_80047aa4(param_1);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x150),(float *)(param_1 + 0x144),&local_2c);
  local_38 = *(float *)(param_1 + 0x118);
  local_34 = *(undefined4 *)(param_1 + 0x128);
  local_30 = *(undefined4 *)(param_1 + 0x138);
  zz_006ebb4_(&local_38,&local_38);
  dVar3 = gnt4_PSQUATDotProduct_bl(&local_2c,&local_38);
  gnt4_PSQUATScale_bl(dVar3,&local_38,&local_38);
  gnt4_PSVECSubtract_bl(&local_2c,&local_38,&local_2c);
  zz_006ec1c_(&local_2c,&local_2c);
  local_38 = *(float *)(param_1 + 0x11c);
  local_34 = *(undefined4 *)(param_1 + 300);
  local_30 = *(undefined4 *)(param_1 + 0x13c);
  zz_006ec1c_(&local_38,&local_38);
  dVar4 = gnt4_PSQUATDotProduct_bl(&local_2c,&local_38);
  dVar3 = (double)FLOAT_804393f0;
  if ((dVar4 <= dVar3) && (dVar3 = dVar4, dVar4 < (double)FLOAT_804393fc)) {
    dVar3 = (double)FLOAT_804393fc;
  }
  dVar3 = (double)gnt4_acos_bl(dVar3);
  local_38 = *(float *)(param_1 + 0x114);
  local_34 = *(undefined4 *)(param_1 + 0x124);
  dVar4 = (double)(FLOAT_80439400 * (float)dVar3);
  local_30 = *(undefined4 *)(param_1 + 0x134);
  zz_006ec1c_(&local_38,&local_38);
  dVar3 = gnt4_PSQUATDotProduct_bl(&local_2c,&local_38);
  if (dVar3 < (double)FLOAT_804393f4) {
    dVar4 = -dVar4;
  }
  iVar2 = 0;
  pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + 0x60);
  do {
    local_2c = pfVar1[3];
    local_28 = pfVar1[7];
    local_24 = pfVar1[0xb];
    gnt4_PSMTXRotRad_bl(dVar4,pfVar1,0x79);
    iVar2 = iVar2 + 1;
    pfVar1[3] = local_2c;
    pfVar1[7] = local_28;
    pfVar1[0xb] = local_24;
    pfVar1 = pfVar1 + 0xc;
  } while (iVar2 < 3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 479-508 ==== */
// ==== 80104e98  zz_0104e98_ ====

void zz_0104e98_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar1;
  int iVar2;
  int local_18 [4];
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar2 = *(int *)(param_9 + 0xe0);
    uVar1 = 1;
  }
  else {
    iVar2 = *(int *)(param_9 + 0xe4);
    uVar1 = 0x44;
  }
  local_18[0] = 0;
  zz_0009a14_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0xc),
              (float *)(param_9 + 0x114),*(int *)(*(int *)(param_9 + 0xdc) + 0xc),local_18,in_r7,
              in_r8,in_r9,in_r10);
  zz_00097b4_(iVar2,uVar1);
  return;
}
