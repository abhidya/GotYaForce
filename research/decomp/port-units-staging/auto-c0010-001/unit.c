#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800722f8(int param_1);
void FUN_80072334(int param_1);
void FUN_800723e0(int param_1);
void zz_0072438_(int param_1);
void zz_00724c8_(int param_1,int param_2);
void zz_0072578_(int param_1,int param_2);
void zz_00725f8_(int param_1,int param_2);
void zz_00726ac_(int param_1,int param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 211-218 ==== */
// ==== 800722f8  FUN_800722f8 ====

void FUN_800722f8(int param_1)

{
  (*(code *)(&PTR_FUN_802d42dc)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0010.c 222-243 ==== */
// ==== 80072334  FUN_80072334 ====

void FUN_80072334(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80437788;
  fVar1 = FLOAT_80437784;
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000)) -
                           DOUBLE_80437788) * FLOAT_80437784);
  *(short *)(param_1 + 0x1918) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1918) ^ 0x80000000)) - dVar2
                           ) * fVar1);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_zz_00729b0__802d42e8)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 247-258 ==== */
// ==== 800723e0  FUN_800723e0 ====

void FUN_800723e0(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_zz_0072438__802d4300)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 262-289 ==== */
// ==== 80072438  zz_0072438_ ====

void zz_0072438_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_80437794;
  fVar1 = FLOAT_80437790;
  iVar3 = 0;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  if (*(short *)(param_1 + 1000) == 0x108) {
    if (*(char *)(param_1 + 0x581) == '\0') {
      iVar3 = 1;
    }
  }
  *(char *)(param_1 + 0x1b04) = *(char *)(param_1 + 0x1b44);
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    iVar3 = iVar3 + 0x11;
  }
  (*(code *)(&PTR_zz_00724c8__802d430c)[*(char *)(param_1 + 0x581)])(param_1,iVar3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 293-311 ==== */
// ==== 800724c8  zz_00724c8_ ====

void zz_00724c8_(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(short *)(param_1 + 1000) == 0x108) {
    iVar1 = 0xe;
  }
  iVar1 = iVar1 + param_2;
  zz_004beb8_((double)FLOAT_80437780,param_1,1,2,iVar1,0xffffffff,0xffffffff);
  if (((*(short *)(param_1 + 1000) == 0x108) || (*(char *)(param_1 + 0x1d0c) != '\x02')) ||
     (*(char *)(param_1 + 0x1d0d) != iVar1)) {
    zz_004beb8_((double)FLOAT_80437780,param_1,2,2,iVar1,4,2);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 315-334 ==== */
// ==== 80072578  zz_0072578_ ====

void zz_0072578_(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x543) < '\0') {
    *(undefined1 *)(param_1 + 0x581) = 0;
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else {
    iVar1 = 3;
    if ((*(char *)(param_1 + 0x5db) == '\x02') && (*(short *)(param_1 + 1000) != 0x108)) {
      iVar1 = 0;
    }
    zz_004beb8_((double)FLOAT_80437780,param_1,1,2,iVar1 + param_2,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 338-355 ==== */
// ==== 800725f8  zz_00725f8_ ====

void zz_00725f8_(int param_1,int param_2)

{
  if ((*(char *)(param_1 + 0x543) < '\0') && ((*(uint *)(param_1 + 0x5e0) & 0x80) != 0)) {
    *(undefined1 *)(param_1 + 0x581) = 4;
    zz_006a3d0_(param_1,'\0',4,2);
  }
  else {
    zz_004beb8_((double)FLOAT_80437780,param_1,1,2,param_2 + 6,0xffffffff,0xffffffff);
    if ((((int)(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x9f) <= (int)*(char *)(param_1 + 0x747))
        || ((*(uint *)(param_1 + 0x5e0) & 0x20) != 0)) && ((*(uint *)(param_1 + 0x5e0) & 2) == 0)) {
      zz_006a5a4_(param_1);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 359-369 ==== */
// ==== 800726ac  zz_00726ac_ ====

void zz_00726ac_(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80437780,param_1,1,2,param_2 + 9,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_80437780,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  return;
}
