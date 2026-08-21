#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
bool FUN_801b804c(int param_1);
void FUN_801b8074(int param_1);
void FUN_801b80b0(int param_1);
void FUN_801b8110(int param_1);
void FUN_801b8140(int param_1);
void FUN_801b8170(int param_1);
void FUN_801b81d0(int param_1);
void FUN_801b822c(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2379-2388 ==== */
// ==== 801b804c  FUN_801b804c ====

bool FUN_801b804c(int param_1)

{
  bool bVar1;
  
  bVar1 = zz_0183730_(param_1,1,0xff);
  return bVar1;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2392-2399 ==== */
// ==== 801b8074  FUN_801b8074 ====

void FUN_801b8074(int param_1)

{
  (*(code *)(&PTR_FUN_803821e0)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2403-2412 ==== */
// ==== 801b80b0  FUN_801b80b0 ====

void FUN_801b80b0(int param_1)

{
  zz_00660b8_(param_1,2);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_803821f0)[*(char *)(param_1 + 0x581)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2416-2424 ==== */
// ==== 801b8110  FUN_801b8110 ====

void FUN_801b8110(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0158688_(param_1,4);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2428-2436 ==== */
// ==== 801b8140  FUN_801b8140 ====

void FUN_801b8140(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0158a94_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2440-2449 ==== */
// ==== 801b8170  FUN_801b8170 ====

void FUN_801b8170(int param_1)

{
  zz_00660b8_(param_1,4);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80382204)[*(char *)(param_1 + 0x581)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2453-2464 ==== */
// ==== 801b81d0  FUN_801b81d0 ====

void FUN_801b81d0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80382218)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2468-2502 ==== */
// ==== 801b822c  FUN_801b822c ====

void FUN_801b822c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffd5f;
  *(undefined1 *)(param_1 + 0x6ea) = 0xb;
  if (*(char *)(param_1 + 0x584) == '\x02') {
    *(undefined1 *)(param_1 + 0x6ea) = 0;
  }
  uVar3 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043ba2c;
  *(float *)(param_1 + 0x558) = FLOAT_8043ba28;
  dVar4 = (double)FLOAT_8043ba30;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(float *)(param_1 + 0x3c) = fVar2;
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,5,1);
  return;
}
