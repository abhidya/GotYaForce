#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800bb160(int param_1);
void FUN_800bb220(int param_1);
void FUN_800bb4bc(int param_1);
void FUN_800bb53c(int param_1);
void FUN_800bb5f4(undefined4 param_1,char param_2,char param_3);
void FUN_800bb638(int param_1,int param_2);
void FUN_800bb66c(int param_1);
void FUN_800bb6a8(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 584-609 ==== */
// ==== 800bb160  FUN_800bb160 ====

void FUN_800bb160(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  zz_006d144_(param_1,0xc1);
  fVar1 = FLOAT_804384fc;
  *(float *)(param_1 + 0x50) = FLOAT_804384fc;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438500,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_804384f8,param_1,0xf,4,0,0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 613-658 ==== */
// ==== 800bb220  FUN_800bb220 ====

void FUN_800bb220(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc1);
  }
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      zz_0085638_(param_1,2);
    }
    zz_0066530_(param_1,0x2d);
    fVar1 = FLOAT_804384f8;
    *(float *)(param_1 + 0x44) = FLOAT_80438514;
    fVar2 = FLOAT_8043850c;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438500,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  FUN_80067310((double)FLOAT_80438508,param_1,*(short *)(param_1 + 0x72) + -0x8000);
  iVar3 = zz_00679d0_(param_1);
  if ((iVar3 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438508 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_80438508 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 662-678 ==== */
// ==== 800bb4bc  FUN_800bb4bc ====

void FUN_800bb4bc(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x208) {
    FUN_800be58c(param_1,0);
    FUN_800f1b28(param_1,0);
  }
  else if (*(short *)(param_1 + 1000) == 0x20e) {
    FUN_800be58c(param_1,1);
    FUN_800f1b28(param_1,1);
  }
  *(undefined1 *)(param_1 + 0x144) = 0;
  zz_00c74ec_(param_1,3);
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0019.c 682-702 ==== */
// ==== 800bb53c  FUN_800bb53c ====

void FUN_800bb53c(int param_1)

{
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(char *)(param_1 + 0x6f7) = *(char *)(param_1 + 0x6f7) + -1;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(short *)(param_1 + 0x1dfc) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1dfc) ^ 0x80000000)) -
                             DOUBLE_80438520) * FLOAT_80438518);
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
    *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
    *(short *)(param_1 + 0x1918) = *(short *)(param_1 + 0x1918) >> 1;
    *(short *)(param_1 + 0x18fe) = *(short *)(param_1 + 0x18fe) >> 1;
    *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 706-713 ==== */
// ==== 800bb5f4  FUN_800bb5f4 ====

void FUN_800bb5f4(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803018b0)[param_2])(param_1,(int)param_3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 717-724 ==== */
// ==== 800bb638  FUN_800bb638 ====

void FUN_800bb638(int param_1,int param_2)

{
  zz_0137540_(param_1,(char)*(undefined4 *)(&DAT_80433ae8 + param_2 * 4));
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 728-735 ==== */
// ==== 800bb66c  FUN_800bb66c ====

void FUN_800bb66c(int param_1)

{
  (*(code *)(&PTR_FUN_803018c4)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 739-746 ==== */
// ==== 800bb6a8  FUN_800bb6a8 ====

void FUN_800bb6a8(int param_1)

{
  (*(code *)(&PTR_FUN_803018d0)[*(char *)(param_1 + 0x580)])();
  return;
}
