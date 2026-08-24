#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800c05bc(int param_1);
void FUN_800c064c(int param_1);
void FUN_800c066c(int param_1);
void FUN_800c0800(undefined4 param_1,char param_2,char param_3);
void FUN_800c086c(int param_1);
void FUN_800c08a8(int param_1);
void FUN_800c08f0(int param_1);
void FUN_800c0914(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4200-4220 ==== */
// ==== 800c05bc  FUN_800c05bc ====

void FUN_800c05bc(int param_1)

{
  short sVar1;
  
  *(undefined1 *)(param_1 + 0x144) = 2;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x30b) {
    FUN_8004e580(param_1,1);
    FUN_800fb83c(param_1,1);
    zz_00c74ec_(param_1,4);
  }
  else if ((sVar1 < 0x30b) && (sVar1 == 0x300)) {
    FUN_8004e580(param_1,0);
    FUN_800fb83c(param_1,0);
    zz_00c74ec_(param_1,4);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4224-4231 ==== */
// ==== 800c064c  FUN_800c064c ====

void FUN_800c064c(int param_1)

{
  zz_010a4ac_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4235-4299 ==== */
// ==== 800c066c  FUN_800c066c ====

void FUN_800c066c(int param_1)

{
  bool bVar1;
  char cVar2;
  
  if ((*(short *)(param_1 + 1000) == 0x300) || (*(short *)(param_1 + 1000) == 0x30b)) {
    cVar2 = *(char *)(param_1 + 0x6e8);
    if (cVar2 == '\x03') {
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
    }
    else if (cVar2 < '\x03') {
      if (cVar2 == '\x01') {
        *(undefined1 *)(param_1 + 0x144) = 1;
        cVar2 = *(char *)(param_1 + 0x6e9);
        if (cVar2 == '\x02') {
          *(undefined1 *)(param_1 + 0xaf) = 0xff;
        }
        else if ((cVar2 < '\x02') && ('\0' < cVar2)) {
          *(undefined1 *)(param_1 + 0xaf) = 1;
          if (*(short *)(param_1 + 1000) == 0x300) {
            zz_001ab6c_(param_1,0x10);
          }
          else if (*(short *)(param_1 + 1000) == 0x30b) {
            zz_001ab6c_(param_1,0x4e);
          }
        }
      }
      else if ('\0' < cVar2) {
        *(undefined1 *)(param_1 + 0x144) = 2;
      }
    }
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    *(undefined1 *)(param_1 + 0x6e9) = 0;
    if (*(char *)(param_1 + 0x144) == '\x01') {
      *(undefined1 *)(param_1 + 0x1d94) = 0;
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4303-4310 ==== */
// ==== 800c0800  FUN_800c0800 ====

void FUN_800c0800(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80433b10)[param_2])(param_1,(int)param_3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4314-4321 ==== */
// ==== 800c086c  FUN_800c086c ====

void FUN_800c086c(int param_1)

{
  (*(code *)(&PTR_FUN_80302988)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4325-4333 ==== */
// ==== 800c08a8  FUN_800c08a8 ====

void FUN_800c08a8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80302994)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4337-4344 ==== */
// ==== 800c08f0  FUN_800c08f0 ====

void FUN_800c08f0(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4348-4355 ==== */
// ==== 800c0914  FUN_800c0914 ====

void FUN_800c0914(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}
