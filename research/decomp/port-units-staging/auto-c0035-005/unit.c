#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80132bfc(int param_1);
void FUN_80132ce0(int param_1);
void FUN_80132e3c(int param_1);
void FUN_80132e94(int param_1);
void FUN_80132ef4(int param_1);
void zz_0132f30_(int param_1);
void zz_0132f9c_(int param_1);
void FUN_80132fcc(int param_1,float *param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1436-1471 ==== */
// ==== 80132bfc  FUN_80132bfc ====

void FUN_80132bfc(int param_1)

{
  short sVar1;
  char cVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  if ((&DAT_8033692a)[*(char *)(param_1 + 0x12) * 0x28] == '\x02') {
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(iVar3 + 0xa60);
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(iVar3 + 0xa70);
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(iVar3 + 0xa80);
  }
  if (0 < *(short *)(param_1 + 0x1c6)) {
    sVar1 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar1;
    if (0 < sVar1) {
      return;
    }
    cVar2 = *(char *)(param_1 + 0x1b) + -1;
    *(char *)(param_1 + 0x1b) = cVar2;
    if ('\0' < cVar2) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + -2;
      *(undefined2 *)(param_1 + 0x1c) = 0x14;
      zz_006d228_(param_1,*(int *)(param_1 + 0xcc),0);
      zz_01332dc_(param_1);
      return;
    }
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined1 *)(param_1 + 0x169) = 0;
  *(undefined1 *)(param_1 + 0x16a) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1475-1517 ==== */
// ==== 80132ce0  FUN_80132ce0 ====

void FUN_80132ce0(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar2 = *(char *)(param_1 + 0x12) * 0x28;
  iVar3 = *(int *)(param_1 + 0x90);
  *(float *)(param_1 + 0x44) =
       *(float *)(&DAT_80336920 + iVar2) * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x44);
  fVar1 = *(float *)(&DAT_8033691c + iVar2) * *(float *)(param_1 + 0xb4);
  if (fVar1 < *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = fVar1;
  }
  iVar2 = iVar3 + *(char *)(param_1 + 0x89) * 0x30;
  local_18 = *(float *)(iVar2 + 0x8e0);
  local_14 = *(undefined4 *)(iVar2 + 0x8f0);
  local_10 = *(undefined4 *)(iVar2 + 0x900);
  gnt4_PSVECSubtract_bl(&local_18,(float *)(param_1 + 0x20),&local_18);
  dVar4 = gnt4_PSVECMag_bl(&local_18);
  if (dVar4 <= (double)(FLOAT_80439ef4 * *(float *)(param_1 + 0xb4))) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0x14;
  }
  else {
    zz_006ebb4_(&local_18,&local_18);
    gnt4_PSQUATScale_bl((double)FLOAT_80439ef0,&local_18,&local_18);
    zz_006ebb4_((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)FLOAT_80439ef0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x38),&local_18,(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),&local_18);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),&local_18,(float *)(param_1 + 0x20));
  }
  FUN_80132fcc(param_1,(float *)(iVar3 + 0x20));
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1521-1536 ==== */
// ==== 80132e3c  FUN_80132e3c ====

void FUN_80132e3c(int param_1)

{
  short sVar1;
  
  zz_01330cc_(param_1,1);
  sVar1 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (sVar1 < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0x14;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1540-1556 ==== */
// ==== 80132e94  FUN_80132e94 ====

void FUN_80132e94(int param_1)

{
  short sVar1;
  
  zz_01330cc_(param_1,0);
  sVar1 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (sVar1 < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0;
    zz_01330b4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1560-1569 ==== */
// ==== 80132ef4  FUN_80132ef4 ====

void FUN_80132ef4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1573-1593 ==== */
// ==== 80132f30  zz_0132f30_ ====

void zz_0132f30_(int param_1)

{
  char *pcVar1;
  
  pcVar1 = *(char **)(param_1 + 0x148);
  if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
    if ((*(char **)(param_1 + 0x144) != (char *)0x0) &&
       ((**(char **)(param_1 + 0x144) != '\0' && (pcVar1[0x18] < '\x02')))) goto LAB_80132f80;
  }
  *(undefined4 *)(param_1 + 0x144) = 0;
  *(undefined4 *)(param_1 + 0x148) = 0;
  *(undefined1 *)(param_1 + 0x16b) = 0;
LAB_80132f80:
  *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_1 + 0x144);
  *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(param_1 + 0x16b);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1597-1606 ==== */
// ==== 80132f9c  zz_0132f9c_ ====

void zz_0132f9c_(int param_1)

{
  if (*(int *)(param_1 + 200) != 0) {
    FUN_80132fcc(param_1,(float *)(*(int *)(param_1 + 200) + 100));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1610-1650 ==== */
// ==== 80132fcc  FUN_80132fcc ====

/* WARNING: Removing unreachable block (ram,0x80133094) */
/* WARNING: Removing unreachable block (ram,0x80132fdc) */

void FUN_80132fcc(int param_1,float *param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_28;
  float local_24;
  float local_20;
  
  gnt4_PSVECSubtract_bl(param_2,(float *)(param_1 + 0x20),&local_28);
  dVar5 = (double)local_24;
  local_24 = FLOAT_80439ee0;
  dVar4 = gnt4_PSVECMag_bl(&local_28);
  iVar2 = FUN_800452a0(-dVar5,dVar4);
  iVar3 = FUN_800452a0((double)local_28,(double)local_20);
  sVar1 = (short)iVar2 - *(short *)(param_1 + 0x70);
  if (0x800 < sVar1) {
    sVar1 = 0x800;
  }
  if (sVar1 < -0x800) {
    sVar1 = -0x800;
  }
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + sVar1;
  sVar1 = (short)iVar3 - *(short *)(param_1 + 0x72);
  if (0x800 < sVar1) {
    sVar1 = 0x800;
  }
  if (sVar1 < -0x800) {
    sVar1 = -0x800;
  }
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar1;
  return;
}
