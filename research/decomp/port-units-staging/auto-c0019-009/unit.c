#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800bd074(int param_1);
void FUN_800bd0b0(int param_1);
void FUN_800bd12c(int param_1);
void FUN_800bd220(int param_1);
void FUN_800bd3a8(int param_1);
void FUN_800bd5a4(int param_1);
void zz_00bd5c4_(int param_1);
void FUN_800bd600(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1827-1834 ==== */
// ==== 800bd074  FUN_800bd074 ====

void FUN_800bd074(int param_1)

{
  (*(code *)(&PTR_FUN_803019d0)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1838-1852 ==== */
// ==== 800bd0b0  FUN_800bd0b0 ====

void FUN_800bd0b0(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_803019e4)[*(char *)(param_1 + 0x540)])(param_1);
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(undefined2 *)(param_1 + 0x18fe) = 0xfe80;
    *(undefined2 *)(param_1 + 0x1900) = 0x100;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1856-1888 ==== */
// ==== 800bd12c  FUN_800bd12c ====

void FUN_800bd12c(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar1 = FLOAT_80438574;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0x1e;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  fVar2 = FLOAT_80438578;
  fVar1 = FLOAT_8043852c;
  *(float *)(param_1 + 0x4c) = FLOAT_8043852c;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar3 = (double)FLOAT_80438540;
  *(undefined1 *)(param_1 + 0x6ea) = 2;
  zz_004beb8_(dVar3,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043852c;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1892-1938 ==== */
// ==== 800bd220  FUN_800bd220 ====

void FUN_800bd220(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x6f7) = 2;
    *(undefined1 *)(param_1 + 0x6ea) = 1;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
      *(undefined1 *)(param_1 + 0x6ea) = 3;
    }
    zz_004beb8_((double)FLOAT_80438540,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
                0xffffffff);
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    fVar1 = FLOAT_8043852c;
    if (iVar2 == 0) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      *(undefined1 *)(param_1 + 0x6e8) = 0;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x44) = fVar1;
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        zz_006a474_(param_1);
      }
      else {
        zz_006a5a4_(param_1);
      }
      *(float *)(param_1 + 0x694) = FLOAT_8043857c + *(float *)(param_1 + 0x1dc8);
      return;
    }
    zz_00e19a8_(param_1,0,param_1 + 0x6f7);
  }
  zz_00b22f4_(param_1);
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0019.c 1942-2009 ==== */
// ==== 800bd3a8  FUN_800bd3a8 ====

void FUN_800bd3a8(int param_1)

{
  double dVar1;
  float fVar2;
  uint uVar3;
  
  uVar3 = zz_006de44_(param_1,0xf0f00);
  dVar1 = DOUBLE_80438520;
  if (uVar3 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar3) {
      uVar3 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar3;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uVar3 ^ 0x80000000)) - dVar1);
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
    zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) < '\x01') {
    zz_004cd24_(param_1,0xf);
  }
  else if (*(float *)(param_1 + 0x560) <= FLOAT_8043852c) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined1 *)(param_1 + 0x542) = 1;
    *(undefined1 *)(param_1 + 0x1cef) = 0;
  }
  else {
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             DOUBLE_80438520) * FLOAT_80438518);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  if (*(char *)(param_1 + 0x542) == '\0') {
    *(undefined1 *)(param_1 + 0x6f7) = 2;
  }
  fVar2 = FLOAT_8043852c;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  zz_00b22f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2013-2020 ==== */
// ==== 800bd5a4  FUN_800bd5a4 ====

void FUN_800bd5a4(int param_1)

{
  zz_00bd5c4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2024-2031 ==== */
// ==== 800bd5c4  zz_00bd5c4_ ====

void zz_00bd5c4_(int param_1)

{
  (*(code *)(&PTR_FUN_803019f0)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2035-2072 ==== */
// ==== 800bd600  FUN_800bd600 ====

void FUN_800bd600(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  fVar2 = FLOAT_8043852c;
  *(float *)(param_1 + 0x50) = FLOAT_8043852c;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(undefined1 *)(param_1 + 0x6ea) = 0xf;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 0x10;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80438540;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  return;
}
