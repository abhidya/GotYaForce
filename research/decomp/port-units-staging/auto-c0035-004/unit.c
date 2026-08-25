#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801322dc(int param_1);
void FUN_8013237c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5 ,double param_6,double param_7,double param_8,int param_9);
void FUN_80132674(int param_1);
void FUN_801326d8(int param_1);
void zz_0132734_(int param_1);
void FUN_801327ac(int param_1);
void FUN_80132974(int param_1);
void FUN_80132a00(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1090-1105 ==== */
// ==== 801322dc  FUN_801322dc ====

void FUN_801322dc(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_01330b4_(param_1);
  }
  (*(code *)(&PTR_FUN_80336b54)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0035.c 1109-1226 ==== */
// ==== 8013237c  FUN_8013237c ====

void FUN_8013237c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  float *pfVar9;
  int iVar10;
  double dVar11;
  undefined8 uVar12;
  float local_a8;
  float local_a4;
  float local_a0;
  float afStack_9c [12];
  float fStack_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  puVar7 = &DAT_80336908;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar10 = *(int *)(param_9 + 0x90);
  iVar5 = *(char *)(param_9 + 0x11) * 0x24;
  iVar8 = (int)*(char *)(param_9 + 0x12);
  *(undefined1 *)(param_9 + 0x84) = 0x16;
  uVar3 = (uint)(byte)(&DAT_80336561)[iVar5];
  iVar4 = iVar8 * 0x28;
  *(undefined *)(param_9 + 0x89) = (&DAT_80336561)[iVar5];
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar2 = iVar4;
  iVar6 = iVar5;
  zz_0089100_(param_9,0,1);
  pfVar9 = (float *)(iVar10 + (char)(&DAT_80336561)[iVar5] * 0x30 + 0x8d4);
  gnt4_PSMTXCopy_bl(pfVar9,(float *)(param_9 + 0x114));
  gnt4_PSMTXMultVec_bl(pfVar9,(float *)(iVar5 + -0x7fcc9a9c),(float *)(param_9 + 0x20));
  local_38 = 0x43300000;
  uStack_34 = (int)*(short *)(&DAT_80336580 + iVar5) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uStack_34)) - DOUBLE_80439ee8)),
                      afStack_9c,0x7a);
  gnt4_PSMTXConcat_bl(pfVar9,afStack_9c,&fStack_6c);
  local_30 = 0x43300000;
  uStack_2c = (int)*(short *)(&DAT_8033657e + iVar5) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uStack_2c)) - DOUBLE_80439ee8)),
                      afStack_9c,0x79);
  gnt4_PSMTXConcat_bl(&fStack_6c,afStack_9c,&fStack_6c);
  local_28 = 0x43300000;
  uStack_24 = (int)*(short *)(&DAT_8033657c + iVar5) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uStack_24)) - DOUBLE_80439ee8)),
                      afStack_9c,0x78);
  gnt4_PSMTXConcat_bl(&fStack_6c,afStack_9c,&fStack_6c);
  dVar11 = (double)FLOAT_80439edc;
  *(undefined4 *)(param_9 + 0x9c) = local_68;
  *(undefined4 *)(param_9 + 0xa0) = local_58;
  *(undefined4 *)(param_9 + 0xa4) = local_48;
  gnt4_PSQUATScale_bl(dVar11,(float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
  local_a4 = FLOAT_80439ee0;
  *(undefined4 *)(param_9 + 0x38) = local_64;
  *(undefined4 *)(param_9 + 0x3c) = local_54;
  *(undefined4 *)(param_9 + 0x40) = local_44;
  local_a8 = *(float *)(param_9 + 0x38);
  local_a0 = *(float *)(param_9 + 0x40);
  dVar11 = gnt4_PSVECMag_bl(&local_a8);
  iVar1 = FUN_800452a0(-(double)*(float *)(param_9 + 0x3c),dVar11);
  *(short *)(param_9 + 0x70) = (short)iVar1;
  dVar11 = (double)local_a0;
  iVar1 = FUN_800452a0((double)local_a8,dVar11);
  *(short *)(param_9 + 0x72) = (short)iVar1;
  *(undefined2 *)(param_9 + 0x74) = 0;
  uVar12 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80336918 + iVar4),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80336918 + iVar4);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8033690c + iVar4);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8033690e + iVar4);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  iVar1 = zz_0006f98_(iVar10);
  zz_0006fb4_(uVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0x600),
              *(int *)(param_9 + 0xe0),(int)(char)(&DAT_80336560)[iVar5],uVar3,iVar2,iVar6,puVar7,
              iVar8);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_80336908)[iVar4]);
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
    zz_01330b4_(param_9);
  }
  else {
    if (-1 < (char)(&DAT_80336562)[iVar5]) {
      *(undefined1 *)(param_9 + 0xa8) = 1;
      zz_00c74ec_(param_9,(int)(char)(&DAT_80336562)[iVar5]);
    }
    if (-1 < (char)(&DAT_8033692c)[iVar4]) {
      zz_01df908_(param_9,(&DAT_8033692c)[iVar4]);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1230-1243 ==== */
// ==== 80132674  FUN_80132674 ====

void FUN_80132674(int param_1)

{
  if ('\0' < *(char *)(param_1 + 0x169)) {
    *(char *)(param_1 + 0x169) = *(char *)(param_1 + 0x169) + -1;
  }
  if ('\0' < *(char *)(param_1 + 0x16a)) {
    *(char *)(param_1 + 0x16a) = *(char *)(param_1 + 0x16a) + -1;
  }
  (*(code *)(&PTR_FUN_80336b64)[*(char *)(param_1 + 0x19)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1247-1258 ==== */
// ==== 801326d8  FUN_801326d8 ====

void FUN_801326d8(int param_1)

{
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined1 *)(param_1 + 0x1a) = 0xff;
  *(undefined *)(param_1 + 0x1b) = (&DAT_80336909)[*(char *)(param_1 + 0x12) * 0x28];
  *(undefined2 *)(param_1 + 0x1c) = 0x14;
  zz_0132734_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1262-1279 ==== */
// ==== 80132734  zz_0132734_ ====

void zz_0132734_(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x12);
  zz_01330cc_(param_1,1);
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(&DAT_8033690a + cVar1 * 0x28);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1283-1341 ==== */
// ==== 801327ac  FUN_801327ac ====

void FUN_801327ac(int param_1)

{
  float fVar1;
  short sVar3;
  int iVar2;
  char cVar4;
  int iVar5;
  int iVar6;
  float afStack_28 [7];
  
  iVar5 = *(char *)(param_1 + 0x12) * 0x28;
  zz_0132f30_(param_1);
  sVar3 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar3;
  if ((0 < sVar3) && (*(int *)(param_1 + 0xcc) != 0)) {
    iVar6 = *(int *)(param_1 + 200);
    if ((iVar6 != 0) &&
       ((((*(byte *)(param_1 + 0xd0) & 4) != 0 && (0 < *(short *)(param_1 + 0x1c6))) &&
        (iVar2 = zz_0083244_((float *)(param_1 + 0x20)), iVar2 == 0)))) {
      *(float *)(param_1 + 0x44) =
           *(float *)(&DAT_80336920 + iVar5) * *(float *)(param_1 + 0xb4) +
           *(float *)(param_1 + 0x44);
      fVar1 = *(float *)(&DAT_8033691c + iVar5) * *(float *)(param_1 + 0xb4);
      if (fVar1 < *(float *)(param_1 + 0x44)) {
        *(float *)(param_1 + 0x44) = fVar1;
      }
      zz_006ebb4_((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      cVar4 = *(char *)(param_1 + 0x1cb) + -1;
      *(char *)(param_1 + 0x1cb) = cVar4;
      if (cVar4 < '\x01') {
        *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_8033690c + iVar5);
        gnt4_PSVECSubtract_bl((float *)(iVar6 + 100),(float *)(param_1 + 0x20),afStack_28);
        zz_006ebb4_(afStack_28,afStack_28);
        gnt4_PSQUATScale_bl((double)FLOAT_80439ef0,afStack_28,afStack_28);
        gnt4_PSQUATScale_bl((double)FLOAT_80439ef0,(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x38),afStack_28,(float *)(param_1 + 0x38));
      }
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),afStack_28);
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),afStack_28,(float *)(param_1 + 0x20));
      iVar5 = FUN_80083874((double)(*(float *)(&DAT_80336914 + iVar5) * *(float *)(param_1 + 0xb4)),
                           param_1);
      if (iVar5 != 0) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(undefined2 *)(param_1 + 0x1c) = 0x14;
        zz_006d228_(param_1,*(int *)(param_1 + 0xcc),0);
        zz_01332dc_(param_1);
      }
      goto LAB_80132950;
    }
  }
  *(undefined1 *)(param_1 + 0x19) = 6;
LAB_80132950:
  zz_0132f9c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1345-1362 ==== */
// ==== 80132974  FUN_80132974 ====

void FUN_80132974(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x12);
  zz_0132f30_(param_1);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  FUN_80133358((double)*(float *)(&DAT_80336924 + cVar1 * 0x28),param_1);
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 10;
  }
  zz_0132f9c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1366-1432 ==== */
// ==== 80132a00  FUN_80132a00 ====

void FUN_80132a00(int param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  float afStack_28 [5];
  
  iVar4 = *(int *)(param_1 + 0x90);
  iVar3 = *(char *)(param_1 + 0x12) * 0x28;
  zz_0132f30_(param_1);
  if (*(short *)(param_1 + 0x1c6) < 1) {
    *(undefined1 *)(param_1 + 0x19) = 6;
  }
  else {
    sVar2 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (sVar2 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      cVar1 = (&DAT_8033692a)[iVar3];
      if (cVar1 == '\x01') {
        *(undefined2 *)(param_1 + 0x1c) = 0x1e;
        iVar4 = zz_006dbe0_(iVar4,0,1,1);
        if (iVar4 == 0) {
          *(undefined1 *)(param_1 + 0x1b) = 0;
        }
        else {
          zz_00c3be0_(param_1,(&DAT_8033692b)[iVar3]);
        }
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(undefined2 *)(param_1 + 0x1c) = 0x1e;
          iVar4 = zz_006dbe0_(iVar4,2,1,1);
          if (iVar4 == 0) {
            *(undefined1 *)(param_1 + 0x1b) = 0;
          }
          else {
            zz_00c3be0_(param_1,(&DAT_8033692b)[iVar3]);
          }
        }
      }
      else if (cVar1 < '\x03') {
        *(undefined2 *)(param_1 + 0x1c) = 0x7d;
        iVar3 = zz_006dbe0_(iVar4,0,1,1);
        if (iVar3 != 0) {
          *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(iVar4 + 0xa60);
          *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(iVar4 + 0xa70);
          *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(iVar4 + 0xa80);
          gnt4_PSVECSubtract_bl((float *)(iVar4 + 0x524),(float *)(param_1 + 0x20),afStack_28);
          zz_006ec1c_(afStack_28,afStack_28);
          gnt4_PSQUATScale_bl((double)*(float *)(iVar4 + 0x814),afStack_28,afStack_28);
          gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),afStack_28,(float *)(param_1 + 0x158));
          *(undefined1 *)(param_1 + 0x169) = 0x41;
          *(undefined1 *)(param_1 + 0x16a) = 0x41;
          zz_01deb68_(iVar4,1,param_1 + 0x14c,param_1 + 0x20,param_1 + 0x169);
          zz_01deb68_(iVar4,4,param_1 + 0x20,(float *)(param_1 + 0x158),param_1 + 0x16a);
        }
      }
    }
  }
  zz_0132f9c_(param_1);
  return;
}
