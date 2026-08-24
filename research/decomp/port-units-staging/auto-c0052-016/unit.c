#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01b3e3c_(int param_1);
void zz_01b3f94_(int param_1);
void zz_01b3fcc_(int param_1);
void zz_01b4114_(int param_1);
void zz_01b4190_(int param_1);
void zz_01b419c_(int param_1);
void zz_01b41bc_(void);
void zz_01b41c0_(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4755-4787 ==== */
// ==== 801b3e3c  zz_01b3e3c_ ====

void zz_01b3e3c_(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      FUN_800e43e0(param_1,(float *)&DAT_80381530,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x1b),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80381590,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x21),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_803815f0,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x27)
                   ,(int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80381650,2,(float *)(puVar2 + 0x15),
                   (float *)(puVar2 + 0x2d),(int *)0x0);
    }
    else {
      FUN_800e4f9c(param_1,-0x7fc7ead0,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x33));
      FUN_800e4f9c(param_1,-0x7fc7ea70,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x39));
      FUN_800e4f9c(param_1,-0x7fc7ea10,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x3f));
      FUN_800e4f9c(param_1,-0x7fc7e9b0,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x45));
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4791-4799 ==== */
// ==== 801b3f94  zz_01b3f94_ ====

void zz_01b3f94_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4803-4829 ==== */
// ==== 801b3fcc  zz_01b3fcc_ ====

void zz_01b3fcc_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fc7ead0,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fc7ea70,2,pfVar2 + 9,afStack_18);
    zz_00e4ec4_(param_1,-0x7fc7ea10,2,pfVar2 + 0xf,afStack_18);
    zz_00e4ec4_(param_1,-0x7fc7e9b0,2,pfVar2 + 0x15,afStack_18);
    zz_00e5184_(param_1,-0x7fc7ead0,2,pfVar2 + 3,pfVar2 + 0x33);
    zz_00e5184_(param_1,-0x7fc7ea70,2,pfVar2 + 9,pfVar2 + 0x39);
    zz_00e5184_(param_1,-0x7fc7ea10,2,pfVar2 + 0xf,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fc7e9b0,2,pfVar2 + 0x15,pfVar2 + 0x45);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4833-4849 ==== */
// ==== 801b4114  zz_01b4114_ ====

void zz_01b4114_(int param_1)

{
  short sVar1;
  
  zz_01b3d68_(param_1);
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x90c) {
    zz_0162f78_(param_1,3);
  }
  else if ((sVar1 < 0x90c) && (sVar1 == 0x907)) {
    zz_0162f78_(param_1,1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4853-4860 ==== */
// ==== 801b4190  zz_01b4190_ ====

void zz_01b4190_(int param_1)

{
  *(undefined1 *)(param_1 + 0x144) = *(undefined1 *)(param_1 + 0x6e8);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4864-4871 ==== */
// ==== 801b419c  zz_01b419c_ ====

void zz_01b419c_(int param_1)

{
  zz_01b3e3c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4875-4881 ==== */
// ==== 801b41bc  zz_01b41bc_ ====

void zz_01b41bc_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4885-4891 ==== */
// ==== 801b41c0  zz_01b41c0_ ====

void zz_01b41c0_(void)

{
  return;
}
