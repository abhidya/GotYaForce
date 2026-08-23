#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01a1d5c_(int param_1);
void zz_01a1e70_(int param_1);
void zz_01a1f68_(int param_1);
void zz_01a2110_(int param_1);
void zz_01a22c8_(int param_1);
void zz_01a22fc_(int param_1);
void zz_01a234c_(int param_1);
void zz_01a241c_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 181-213 ==== */
// ==== 801a1d5c  zz_01a1d5c_ ====

void zz_01a1d5c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043b590;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           FLOAT_8043b5b0 *
           (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar1);
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_8043b5b0 * *(float *)(param_1 + 0x764)) / fVar1;
    }
    fVar1 = FLOAT_8043b5b4;
    *(float *)(param_1 + 0x4c) = FLOAT_8043b594;
    if (fVar1 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,3,2,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 217-254 ==== */
// ==== 801a1e70  zz_01a1e70_ ====

void zz_01a1e70_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\x04') {
    if (*(char *)(param_1 + 0x1cf0) == '\x01') goto LAB_801a1ea8;
  }
  zz_004cd24_(param_1,0xf);
LAB_801a1ea8:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    zz_006ed8c_((double)FLOAT_8043b59c,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_80066838((double)FLOAT_8043b5b4,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_8043b5bc;
    fVar1 = FLOAT_8043b5b8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 258-315 ==== */
// ==== 801a1f68  zz_01a1f68_ ====

void zz_01a1f68_(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  iVar2 = zz_004cd24_(param_1,0xf);
  if (iVar2 == 1) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
  }
  else {
    if (*(char *)(param_1 + 0x542) == '\0') {
      if ((*(char *)(param_1 + 0x1cef) == '\x04') && (*(char *)(param_1 + 0x1cf0) == '\x02')) {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      if (((*(char *)(param_1 + 0x1cef) != '\x04') || (*(char *)(param_1 + 0x1cf0) != '\x03')) &&
         ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0)) {
        *(undefined1 *)(param_1 + 0x745) = 1;
      }
      if (((*(char *)(param_1 + 0x543) == '\x01') && (*(char *)(param_1 + 0x745) == '\x01')) ||
         ((*(char *)(param_1 + 0x1cef) == '\x04' && (*(char *)(param_1 + 0x1cf0) == '\x03')))) {
        if (*(char *)(param_1 + 0x745) == '\x01') {
          *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
          *(undefined1 *)(param_1 + 0x542) = 0;
          fVar1 = FLOAT_8043b5c0;
          if (*(char *)(param_1 + 0x541) == '\0') {
            if (*(int *)(param_1 + 0xcc) == 0) {
              *(undefined1 *)(param_1 + 0x541) = 1;
            }
            else {
              *(float *)(param_1 + 0x558) = FLOAT_8043b590;
              *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / fVar1;
            }
          }
          if (*(char *)(param_1 + 0x541) == '\x01') {
            *(float *)(param_1 + 0x558) = FLOAT_8043b5c4;
          }
          dVar3 = (double)FLOAT_8043b598;
          *(float *)(param_1 + 0x4c) = FLOAT_8043b594;
          zz_004beb8_(dVar3,param_1,0xf,3,3,0xffffffff,0xffffffff);
        }
        else {
          *(undefined1 *)(param_1 + 0x542) = 99;
        }
      }
    }
    zz_006d144_(param_1,0xc0);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 != 0) {
      zz_00b22f4_(param_1);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 319-378 ==== */
// ==== 801a2110  zz_01a2110_ ====

void zz_01a2110_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x02') {
    zz_004cd24_(param_1,0xf);
    if ((*(char *)(param_1 + 0x1cef) == '\x02') && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x4c) = FLOAT_8043b598;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x1cef) != '\x02') || (*(char *)(param_1 + 0x1cf0) != '\x04')) {
        zz_004cd24_(param_1,0xf);
      }
      fVar3 = FLOAT_8043b594;
      fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      *(float *)(param_1 + 0x558) = fVar2;
      if ((fVar2 <= fVar3) || (uVar4 = FUN_80066838((double)FLOAT_8043b5b4,param_1), 0 < (int)uVar4)
         ) {
        fVar3 = FLOAT_8043b5c8;
        fVar2 = FLOAT_8043b5bc;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar3;
        *(float *)(param_1 + 0x4c) = fVar2;
      }
    }
    else if (((-1 < cVar1) &&
             (zz_004cd24_(param_1,0xf), fVar2 = FLOAT_8043b594,
             *(char *)(param_1 + 0x1cef) == '\x02')) && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b5cc;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(undefined1 *)(param_1 + 0x541) = 1;
      *(undefined4 *)(param_1 + 0xcc) = 0;
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
    }
  }
  else if ((cVar1 < '\x04') && (iVar5 = zz_004cd24_(param_1,0xf), iVar5 == 1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    return;
  }
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar5 = zz_00677b0_(param_1);
  if (iVar5 != 0) {
    zz_00b22f4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 382-391 ==== */
// ==== 801a22c8  zz_01a22c8_ ====

void zz_01a22c8_(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 395-405 ==== */
// ==== 801a22fc  zz_01a22fc_ ====

void zz_01a22fc_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a234c__8037875c)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 409-435 ==== */
// ==== 801a234c  zz_01a234c_ ====

void zz_01a234c_(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x54e);
  }
  dVar2 = (double)FLOAT_8043b5d0;
  *(float *)(param_1 + 0x558) = FLOAT_8043b5ac;
  zz_006ed8c_(dVar2,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b594;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 439-474 ==== */
// ==== 801a241c  zz_01a241c_ ====

void zz_01a241c_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043b5d4,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    fVar2 = FLOAT_8043b594;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_8043b590;
    *(float *)(param_1 + 0x558) = FLOAT_8043b590;
    fVar3 = FLOAT_8043b5b4;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,3,5,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  return;
}
