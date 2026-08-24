#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80172e80(int param_1,int param_2);
void FUN_80172f3c(int param_1,int param_2);
void FUN_80173000(int param_1,int param_2);
void FUN_801731ac(int param_1);
void FUN_80173250(undefined1 *param_1);
void FUN_80173464(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7903-7925 ==== */
// ==== 80172e80  FUN_80172e80 ====

void FUN_80172e80(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
  *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0x7f;
  *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) | 8;
  *(undefined2 *)(param_1 + 4) = 4;
  *(short *)(param_2 + 6) =
       (short)*(char *)(*(int *)(param_2 + 0x40) +
                        *(char *)(param_2 + *(char *)(param_2 + 0x61) + 0x4c) * 0x6c + 0x29);
  *(undefined1 *)(param_2 + 100) = 0;
  *(char *)(param_2 + 0x65) = (char)*(undefined2 *)(param_2 + 6) + '\x02';
  do {
    zz_0167334_(*(undefined1 *)(param_2 + 0x3c),10,(char)iVar1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 5);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7929-7959 ==== */
// ==== 80172f3c  FUN_80172f3c ====

void FUN_80172f3c(int param_1,int param_2)

{
  char cVar1;
  short sVar2;
  
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    sVar2 = *(short *)(param_1 + 4) + -1;
    *(short *)(param_1 + 4) = sVar2;
    if (sVar2 < 1) {
      cVar1 = *(char *)(param_2 + 0x65) + -1;
      *(char *)(param_2 + 0x65) = cVar1;
      if (cVar1 <= *(char *)(param_2 + 100)) {
        *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
        *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) | 8;
        *(byte *)(param_2 + 0x3f) = *(byte *)(param_2 + 0x3f) & 0xf7;
        *(undefined1 *)(param_2 + 0x65) = *(undefined1 *)(param_2 + 100);
      }
      *(undefined2 *)(param_1 + 4) = 4;
    }
  }
  else {
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x02';
    *(undefined2 *)(param_1 + 4) = 4;
    *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0xf7;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7963-8010 ==== */
// ==== 80173000  FUN_80173000 ====

void FUN_80173000(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(short *)(param_1 + 4) == 0) {
    iVar2 = (int)*(char *)(param_2 + 100);
    if ((*(ushort *)(param_1 + 8) & 8) == 0) {
      iVar3 = iVar2;
      if ((*(ushort *)(param_1 + 8) & 4) != 0) {
        iVar1 = *(short *)(param_2 + 6) + -1;
        iVar3 = iVar2 + 1;
        if (iVar1 < iVar2 + 1) {
          iVar3 = iVar1;
        }
      }
    }
    else {
      iVar3 = iVar2 + -1;
      if (iVar2 + -1 < 0) {
        iVar3 = 0;
      }
    }
    if (iVar3 != *(char *)(param_2 + 100)) {
      *(char *)(param_2 + 0x65) = (char)iVar3;
      *(char *)(param_2 + 100) = (char)iVar3;
      *(undefined2 *)(param_1 + 4) = 7;
      zz_00f0468_(0,0x77,0);
    }
  }
  else {
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + -1;
  }
  if ((*(ushort *)(param_1 + 0xe) & 0x200) != 0) {
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
    *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0xf7;
    *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xf7;
    *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) | 0x80;
    *(undefined1 *)(param_2 + 0x65) = *(undefined1 *)(param_2 + 100);
    *(undefined2 *)(param_1 + 4) = 4;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 8014-8022 ==== */
// ==== 801731ac  FUN_801731ac ====

void FUN_801731ac(int param_1)

{
  *(undefined1 *)(param_1 + 99) = 0;
  (*(code *)(&PTR_LAB_80351818)[*(char *)(param_1 + 1)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 8026-8079 ==== */
// ==== 80173250  FUN_80173250 ====

void FUN_80173250(undefined1 *param_1)

{
  int iVar1;
  
  if (*(short *)(param_1 + 4) == 0) {
    iVar1 = (int)(char)param_1[0x62];
    if ((*(ushort *)(param_1 + 8) & 1) == 0) {
      if ((*(ushort *)(param_1 + 8) & 2) != 0) {
        for (iVar1 = iVar1 + 1; (char)PTR_DAT_80433944[0x6a] <= iVar1;
            iVar1 = iVar1 - (char)PTR_DAT_80433944[0x6a]) {
        }
      }
    }
    else {
      for (iVar1 = iVar1 + -1; iVar1 < 0; iVar1 = iVar1 + (char)PTR_DAT_80433944[0x6a]) {
      }
    }
    if (iVar1 != (char)param_1[0x62]) {
      param_1[0x62] = (char)iVar1;
      *(undefined2 *)(param_1 + 4) = 9;
      zz_00f0468_(0,0x77,0);
    }
  }
  else {
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + -1;
  }
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    if ((*(ushort *)(param_1 + 0xe) & 0x180) != 0) {
      param_1[0x3f] = param_1[0x3f] | 0x20;
      if (*(short *)(PTR_DAT_80433944 + (char)param_1[0x62] * 2 + 0x30) < 999) {
        *(short *)(PTR_DAT_80433944 + (char)param_1[0x62] * 2 + 0x30) =
             *(short *)(PTR_DAT_80433944 + (char)param_1[0x62] * 2 + 0x30) + 1;
      }
      param_1[99] = param_1[99] + '\x01';
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *param_1 = 2;
    param_1[1] = 0;
    param_1[0x3d] = param_1[0x3d] & 0xdf;
    param_1[0x3f] = param_1[0x3f] & 0xdf;
    param_1[0x3e] = param_1[0x3e] & 0xdf;
    PTR_DAT_80433944[0x2f] = PTR_DAT_80433944[0x2f] & ~(byte)(1 << (uint)(byte)param_1[0x3c]);
    zz_00f0468_(0,0x7b,0);
  }
  if ((param_1[0x3f] & 0x20) != 0) {
    PTR_DAT_80433944[0x2f] = PTR_DAT_80433944[0x2f] | (byte)(1 << (uint)(byte)param_1[0x3c]);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 8083-8090 ==== */
// ==== 80173464  FUN_80173464 ====

void FUN_80173464(void)

{
  (*(code *)(&PTR_FUN_804347a0)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}
