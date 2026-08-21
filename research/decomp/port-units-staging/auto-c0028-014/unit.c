#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80102974(int param_1);
void FUN_801029f4(int param_1);
void FUN_80102a30(int param_1);
void FUN_80102ab0(int param_1);
void FUN_80102af8(int param_1);
void FUN_80102bf8(int param_1);
void FUN_80102cf8(int param_1);
void FUN_80102e84(int param_1);

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0028.c 3954-3974 ==== */
// ==== 80102974  FUN_80102974 ====

void FUN_80102974(int param_1)

{
  double dVar1;
  
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(char *)(param_1 + 0x6f7) = *(char *)(param_1 + 0x6f7) + -1;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    dVar1 = DOUBLE_804393a0;
    *(undefined2 *)(param_1 + 0x1918) = 0;
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             dVar1) * FLOAT_80439398);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 3978-3985 ==== */
// ==== 801029f4  FUN_801029f4 ====

void FUN_801029f4(int param_1)

{
  (*(code *)(&PTR_FUN_80321610)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0028.c 3989-4001 ==== */
// ==== 80102a30  FUN_80102a30 ====

void FUN_80102a30(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000)) -
                           DOUBLE_804393a0) * FLOAT_804393a8);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80321620)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4005-4013 ==== */
// ==== 80102ab0  FUN_80102ab0 ====

void FUN_80102ab0(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80321634)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4017-4047 ==== */
// ==== 80102af8  FUN_80102af8 ====

void FUN_80102af8(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_804393ac;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,1,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  zz_004beb8_((double)FLOAT_804393ac,param_1,2,0,0,0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  zz_01033f8_(param_1);
  fVar1 = FLOAT_804393b0;
  *(float *)(param_1 + 0x50) = FLOAT_804393b0;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804393b0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4051-4087 ==== */
// ==== 80102bf8  FUN_80102bf8 ====

/* WARNING: Removing unreachable block (ram,0x80102cdc) */
/* WARNING: Removing unreachable block (ram,0x80102c08) */

void FUN_80102bf8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804393b0;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_804393b0;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_80103428(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_804393b8 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4091-4143 ==== */
// ==== 80102cf8  FUN_80102cf8 ====

void FUN_80102cf8(int param_1)

{
  int iVar1;
  double dVar2;
  
  if (*(float *)(param_1 + 0x55c) <= FLOAT_804393b0) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(float *)(param_1 + 0x558) <= FLOAT_804393b0) {
    if ((*(uint *)(param_1 + 0x5d4) & 0x20) != 0) {
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_1,'\0',3,0);
          return;
        }
        zz_006bf80_(param_1);
        dVar2 = (double)FLOAT_804393ac;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        zz_004beb8_(dVar2,param_1,0xf,2,1,0xffffffff,0xffffffff);
        return;
      }
      goto LAB_80102e0c;
    }
    *(float *)(param_1 + 0x55c) = FLOAT_804393b0;
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if (dVar2 <= (double)FLOAT_804393b8) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_80102e0c:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4147-4154 ==== */
// ==== 80102e84  FUN_80102e84 ====

void FUN_80102e84(int param_1)

{
  (*(code *)(&PTR_FUN_80321640)[*(char *)(param_1 + 0x540)])();
  return;
}
