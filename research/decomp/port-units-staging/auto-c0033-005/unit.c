#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80123254(int param_1);
void FUN_80123318(int param_1);
void FUN_80123390(int param_1);
void FUN_801233cc(int param_1);
void FUN_80123534(int param_1);
void FUN_801235d0(int param_1);
void FUN_80123730(int param_1);
void FUN_80123854(int param_1,char param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1503-1524 ==== */
// ==== 80123254  FUN_80123254 ====

void FUN_80123254(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_80439b78);
    *(undefined1 *)(param_1 + 0x541) = 0xff;
  }
  FUN_80067310((double)FLOAT_80439b64,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0066530_(param_1,0x2c);
    zz_004beb8_((double)FLOAT_80439b58,param_1,0xf,3,8,0xffffffff,0xffffffff);
    *(float *)(param_1 + 0x80c) = FLOAT_80439b10;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1528-1543 ==== */
// ==== 80123318  FUN_80123318 ====

void FUN_80123318(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80439b20,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1547-1554 ==== */
// ==== 80123390  FUN_80123390 ====

void FUN_80123390(int param_1)

{
  (*(code *)(&PTR_FUN_8032c800)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1558-1565 ==== */
// ==== 801233cc  FUN_801233cc ====

void FUN_801233cc(int param_1)

{
  zz_0149708_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1569-1596 ==== */
// ==== 80123534  FUN_80123534 ====

void FUN_80123534(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = -1;
  *(undefined1 *)(param_1 + 0x144) = 0;
  *(undefined1 *)(param_1 + 0x145) = 0;
  *(undefined1 **)(param_1 + 0x4d4) = &LAB_80123808;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  if (*(short *)(param_1 + 1000) == 0x202) {
    iVar1 = 0;
  }
  if (*(short *)(param_1 + 1000) == 0x20b) {
    iVar1 = 1;
  }
  if (-1 < iVar1) {
    iVar2 = 0;
    do {
      zz_012b59c_(param_1,(char)iVar2,(char)iVar1);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 8);
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0033.c 1600-1655 ==== */
// ==== 801235d0  FUN_801235d0 ====

void FUN_801235d0(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(short *)(param_1 + 1000) == 0x202) {
    if (*(short *)(param_1 + 0x774) < 1) {
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
    }
    else {
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xfe;
    }
    if ((*(uint *)(param_1 + 0x5e0) & 0x81000000) == 0) {
      if (*(char *)(param_1 + 0x5da) != '/') {
        if (*(char *)(param_1 + 0x145) == '\0') {
          *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfffd;
        }
        else {
          *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
        }
      }
    }
  }
  else if (*(short *)(param_1 + 1000) == 0x20b) {
    if (*(char *)(param_1 + 0x145) == '\0') {
      *(undefined1 *)(param_1 + 0x748) = 0;
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xfd;
    }
    else {
      *(undefined1 *)(param_1 + 0x748) = 1;
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 2;
    }
    if ((*(uint *)(param_1 + 0x5e0) & 0x81000000) == 0) {
      if (*(char *)(param_1 + 0x5da) != '/') {
        *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfffd;
      }
    }
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    dVar2 = DOUBLE_80439b88;
    fVar1 = FLOAT_80439b80;
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             DOUBLE_80439b88) * FLOAT_80439b80);
    *(short *)(param_1 + 0x18e2) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000)) -
                             dVar2) * fVar1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1659-1689 ==== */
// ==== 80123730  FUN_80123730 ====

void FUN_80123730(int param_1)

{
  char cVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_00b241c_(param_1);
  }
  cVar1 = *(char *)(param_1 + 0x6e8);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  else if ((cVar1 < '\x02') && ('\0' < cVar1)) {
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    *(undefined1 *)(param_1 + 0xaf) = 1;
    if (*(short *)(param_1 + 1000) == 0x202) {
      zz_001ab6c_(param_1,0xc);
    }
    else if (*(short *)(param_1 + 1000) == 0x20b) {
      zz_001ab6c_(param_1,0x5e);
    }
  }
  if (((*(char *)(param_1 + 0x145) == '\x03') && (*(char *)(param_1 + 0x5db) != '\x01')) &&
     (*(char *)(param_1 + 0x5db) != '<')) {
    *(undefined1 *)(param_1 + 0x145) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1693-1709 ==== */
// ==== 80123854  FUN_80123854 ====

void FUN_80123854(int param_1,char param_2)

{
  if (param_2 == '\x01') {
    if (*(short *)(param_1 + 1000) == 0x20b) {
      zz_00f036c_(param_1,9);
    }
  }
  else if ((param_2 < '\x01') && (-1 < param_2)) {
    *(undefined1 *)(param_1 + 0x145) = 3;
    *(undefined1 *)(param_1 + 0x6f7) = 1;
    zz_00f036c_(param_1,0xd8);
  }
  return;
}
