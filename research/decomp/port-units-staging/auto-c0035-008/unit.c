#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_0133f68_(int param_1);
void zz_0133fa0_(int param_1);
void FUN_801341c8(int param_1);
void FUN_8013427c(int param_1);
void FUN_801342ec(int param_1);
void FUN_801344a8(int param_1);
void FUN_801344d4(int param_1);
void FUN_801344f4(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2251-2259 ==== */
// ==== 80133f68  zz_0133f68_ ====

void zz_0133f68_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2263-2285 ==== */
// ==== 80133fa0  zz_0133fa0_ ====

void zz_0133fa0_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcc93d8,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcc9378,3,pfVar2 + 9,afStack_18);
    zz_00e5184_(param_1,-0x7fcc93d8,2,pfVar2 + 3,pfVar2 + 0x21);
    zz_00e5184_(param_1,-0x7fcc9378,3,pfVar2 + 9,pfVar2 + 0x27);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2289-2313 ==== */
// ==== 801341c8  FUN_801341c8 ====

void FUN_801341c8(int param_1)

{
  int iVar1;
  
  if (*(short *)(param_1 + 1000) == 0x304) {
    zz_00cbb00_(param_1,0);
    iVar1 = 0;
    do {
      zz_01390a4_(param_1,(char)iVar1,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
    zz_00c74ec_(param_1,8);
  }
  else if (*(short *)(param_1 + 1000) == 0x308) {
    zz_00cbb00_(param_1,1);
    zz_01390a4_(param_1,2,1);
    zz_01390a4_(param_1,3,1);
  }
  zz_0133df4_(param_1);
  *(undefined1 *)(param_1 + 0x144) = 2;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2317-2332 ==== */
// ==== 8013427c  FUN_8013427c ====

void FUN_8013427c(int param_1)

{
  zz_010a4ac_(param_1);
  if (*(short *)(param_1 + 1000) == 0x308) {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
    *(undefined1 *)(param_1 + 0x748) = 2;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
    *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2336-2415 ==== */
// ==== 801342ec  FUN_801342ec ====

void FUN_801342ec(int param_1)

{
  bool bVar1;
  char cVar2;
  
  switch(*(undefined1 *)(param_1 + 0x6e8)) {
  case 1:
    *(undefined1 *)(param_1 + 0x144) = 1;
    cVar2 = *(char *)(param_1 + 0x6e9);
    if (cVar2 != '\x03') {
      if (cVar2 < '\x03') {
        if (cVar2 == '\x01') {
          *(undefined1 *)(param_1 + 0x145) = 3;
          *(undefined1 *)(param_1 + 0xaf) = 1;
          zz_001ab6c_(param_1,0x11);
          break;
        }
        if ('\0' < cVar2) {
          *(undefined1 *)(param_1 + 0xaf) = 0xff;
          break;
        }
      }
      else if (cVar2 < '\x05') {
        *(undefined1 *)(param_1 + 0x145) = 4;
        break;
      }
    }
    *(undefined1 *)(param_1 + 0x145) = 3;
    break;
  case 2:
    *(undefined1 *)(param_1 + 0x144) = 2;
    break;
  case 3:
    bVar1 = *(char *)(param_1 + 0x144) != '\x03';
    *(undefined1 *)(param_1 + 0x144) = 3;
    cVar2 = *(char *)(param_1 + 0x6e9);
    if (cVar2 == '\x02') {
      *(undefined1 *)(param_1 + 0x145) = 2;
    }
    else if (cVar2 < '\x02') {
      if ('\0' < cVar2) {
        if (bVar1) {
          *(undefined1 *)(param_1 + 0x145) = 2;
        }
        else {
          *(undefined1 *)(param_1 + 0x145) = 1;
        }
      }
    }
    else if (cVar2 < '\x04') {
      if (bVar1) {
        *(undefined1 *)(param_1 + 0x145) = 3;
      }
      else {
        *(undefined1 *)(param_1 + 0x145) = 1;
      }
    }
    break;
  case 5:
    *(undefined1 *)(param_1 + 0x144) = 5;
    *(undefined1 *)(param_1 + 0x145) = *(undefined1 *)(param_1 + 0x6e9);
    break;
  case 0xff:
    if (*(char *)(param_1 + 0x144) == '\x05') {
      *(undefined1 *)(param_1 + 0x144) = 2;
    }
  }
  *(undefined1 *)(param_1 + 0x6e8) = 0;
  *(undefined1 *)(param_1 + 0x6e9) = 0;
  if (*(char *)(param_1 + 0x144) == '\x01') {
    *(undefined1 *)(param_1 + 0x1d94) = 0;
  }
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(char *)(param_1 + 0x6f7) = *(char *)(param_1 + 0x6f7) + -1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2419-2426 ==== */
// ==== 801344a8  FUN_801344a8 ====

void FUN_801344a8(int param_1)

{
  zz_0133e90_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2430-2437 ==== */
// ==== 801344d4  FUN_801344d4 ====

void FUN_801344d4(int param_1)

{
  zz_0133f68_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2441-2448 ==== */
// ==== 801344f4  FUN_801344f4 ====

void FUN_801344f4(int param_1)

{
  zz_0133fa0_(param_1);
  return;
}
