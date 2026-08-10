#include "gnt4_shim.h"

/* stage-2 generated prototypes */
int FUN_800452a0(double param_1,double param_2);
void zz_005ec20_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0005.c 2191-2204 ==== */
// ==== 800452a0  FUN_800452a0 ====

/* WARNING: Removing unreachable block (ram,0x800452cc) */
/* WARNING: Removing unreachable block (ram,0x800452c4) */
/* WARNING: Removing unreachable block (ram,0x800452b0) */

int FUN_800452a0(double param_1,double param_2)

{
  double dVar1;
  
  dVar1 = (double)gnt4_atan2_bl(param_1,param_2);
  return (int)(short)(FLOAT_8043707c * (float)dVar1 * 1.0);
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0007.c 5544-5574 ==== */
// ==== 8005ec20  zz_005ec20_ ====

void zz_005ec20_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  
  cVar5 = *(char *)(param_1 + 0x702);
  if (cVar5 < '\0') {
    cVar5 = -cVar5;
  }
  fVar1 = *(float *)(param_1 + 0x298) / *(float *)(param_1 + 0xc4);
  if ('\x0f' < cVar5) {
    cVar5 = '\x0f';
  }
  *(undefined1 *)(param_1 + 0x1d9b) = 0;
  fVar2 = FLOAT_80437440;
  *(undefined1 *)(param_1 + 0x1db2) = 1;
  fVar4 = FLOAT_80437490;
  fVar3 = FLOAT_80437444;
  *(float *)(param_1 + 0x44) = fVar1 * *(float *)(&DAT_802dd8a0 + cVar5 * 4);
  *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) / fVar4;
  *(float *)(param_1 + 0x1d9c) = fVar1 - fVar2;
  *(float *)(param_1 + 0x50) = fVar3;
  *(float *)(param_1 + 0x48) = fVar3;
  return;
}
