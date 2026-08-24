#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
uint zz_01d7134_(int param_1,int param_2);
uint zz_01d7170_(undefined4 param_1,int param_2,int param_3);
void zz_01d71d4_(int param_1,int param_2);
void zz_01d72b8_(int param_1);
void zz_01d72fc_(int param_1);
void zz_01d7340_(int param_1);
void zz_01d7384_(int param_1);
void FUN_801d7564(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0057.c 1691-1705 ==== */
// ==== 801d7134  zz_01d7134_ ====

uint zz_01d7134_(int param_1,int param_2)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x19b) == '\0') {
    uVar1 = zz_01d7170_(param_1,param_1 + 0x144,param_2);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0057.c 1709-1725 ==== */
// ==== 801d7170  zz_01d7170_ ====

uint zz_01d7170_(undefined4 param_1,int param_2,int param_3)

{
  uint uVar1;
  
  if (*(char *)(param_2 + 0x55) < '\0') {
    uVar1 = zz_00ea170_(0x12,0,-1,param_3);
    *(char *)(param_2 + 0x55) = (char)uVar1;
    uVar1 = (uint)(int)*(char *)(param_2 + 0x55) >> 0x1f ^ 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0057.c 1729-1765 ==== */
// ==== 801d71d4  zz_01d71d4_ ====

void zz_01d71d4_(int param_1,int param_2)

{
  char cVar1;
  short sVar3;
  uint uVar2;
  int iVar4;
  
  if (*(char *)(param_2 + 0x54) < '\a') {
    sVar3 = *(short *)(param_2 + 0x44) + -1;
    *(short *)(param_2 + 0x44) = sVar3;
    if (sVar3 < 1) {
      do {
        uVar2 = zz_00055fc_();
        cVar1 = *(char *)(*(char *)(param_2 + 0x54) * 8 + -0x7fc7208c + (uVar2 & 7));
        iVar4 = (int)cVar1;
        if (iVar4 < 0) break;
      } while (iVar4 == *(char *)(param_2 + 0x58));
      if (-1 < iVar4) {
        zz_01d7134_(param_1,iVar4);
      }
      *(char *)(param_2 + 0x58) = cVar1;
      if (iVar4 < 1) {
        *(undefined2 *)(param_2 + 0x44) = 0x1e;
      }
      else {
        *(undefined2 *)(param_2 + 0x44) = 0xf0;
      }
    }
  }
  else {
    *(undefined1 *)(param_2 + 0x57) = 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0057.c 1769-1779 ==== */
// ==== 801d72b8  zz_01d72b8_ ====

void zz_01d72b8_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  zz_01d7134_(param_1,(int)(char)(&DAT_80435ae8)[uVar1 & 1]);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0057.c 1783-1793 ==== */
// ==== 801d72fc  zz_01d72fc_ ====

void zz_01d72fc_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  zz_01d7134_(param_1,(int)(char)(&DAT_80435aec)[uVar1 & 7]);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0057.c 1797-1807 ==== */
// ==== 801d7340  zz_01d7340_ ====

void zz_01d7340_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  zz_01d7134_(param_1,(int)(char)(&DAT_80435af4)[uVar1 & 3]);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0057.c 1811-1821 ==== */
// ==== 801d7384  zz_01d7384_ ====

void zz_01d7384_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  zz_01d7134_(param_1,(int)(char)(&DAT_80435af8)[uVar1 & 7]);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0057.c 1825-1832 ==== */
// ==== 801d7564  FUN_801d7564 ====

void FUN_801d7564(int param_1)

{
  (*(code *)(&PTR_FUN_8038dff8)[*(char *)(param_1 + 0x580)])();
  return;
}
