#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
int zz_000b07c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8, int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12, undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16);
undefined4 zz_000b0f8_(undefined4 param_1,undefined4 param_2);
int zz_000b124_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8, int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12, undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16);
int zz_000b1a0_(undefined4 param_1,undefined4 param_2,int param_3);
undefined1 * zz_000b1d4_(undefined4 param_1,undefined4 param_2,int param_3,int param_4);
void zz_000b26c_(undefined1 *param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 5381-5399 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 5403-5410 ==== */
// ==== 8000b0f8  zz_000b0f8_ ====

undefined4 zz_000b0f8_(undefined4 param_1,undefined4 param_2)

{
  zz_000b1d4_(param_1,param_2,0,5);
  return 0;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 5414-5432 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 5436-5443 ==== */
// ==== 8000b1a0  zz_000b1a0_ ====

int zz_000b1a0_(undefined4 param_1,undefined4 param_2,int param_3)

{
  zz_000b1d4_(param_1,param_2,param_3,7);
  return param_3;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 5447-5488 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 5492-5515 ==== */
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
