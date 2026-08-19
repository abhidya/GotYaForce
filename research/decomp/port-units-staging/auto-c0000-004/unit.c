#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_00064d4_(void);
int zz_000673c_(int param_1);
void zz_0006800_(void);
void zz_000685c_(int param_1);
void zz_0006abc_(void);
void zz_0006b74_(void);
void zz_0006c24_(int param_1,int param_2);
void zz_0006c88_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8, int param_9,void *param_10,uint param_11,undefined4 param_12,undefined4 param_13, undefined4 param_14,undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1018-1085 ==== */
// ==== 800064d4  zz_00064d4_ ====

void zz_00064d4_(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int local_28 [7];
  
  if ((PTR_DAT_80433930[0x32] == '\x02') || (PTR_DAT_80433930[0x32] == '\x01')) {
    iVar3 = 0;
    piVar5 = local_28;
    iVar6 = 0;
    while( true ) {
      if ((char)PTR_DAT_80433934[0x53] <= iVar6) break;
      iVar2 = iVar3 + 0x114;
      *piVar5 = 0;
      iVar6 = iVar6 + 1;
      iVar3 = iVar3 + 0x3c;
      *(undefined4 *)(PTR_DAT_80433934 + iVar2) = 0;
      piVar5 = piVar5 + 1;
    }
    if ((PTR_DAT_80433930[2] & 1) != 0) {
      local_28[(char)PTR_DAT_80433934[0xcb]] = local_28[(char)PTR_DAT_80433934[0xcb]] + 1;
    }
    if ((PTR_DAT_80433930[2] & 2) != 0) {
      local_28[(char)PTR_DAT_80433934[0xcc]] = local_28[(char)PTR_DAT_80433934[0xcc]] + 1;
    }
    if ((PTR_DAT_80433930[2] & 4) != 0) {
      local_28[(char)PTR_DAT_80433934[0xcd]] = local_28[(char)PTR_DAT_80433934[0xcd]] + 1;
    }
    if ((PTR_DAT_80433930[2] & 8) != 0) {
      local_28[(char)PTR_DAT_80433934[0xce]] = local_28[(char)PTR_DAT_80433934[0xce]] + 1;
    }
    iVar3 = 0;
    do {
      puVar1 = PTR_DAT_80433934;
      iVar6 = (char)PTR_DAT_80433934[iVar3 + 0xcb] * 0x3c;
      if (local_28[(char)PTR_DAT_80433934[iVar3 + 0xcb]] == 0) {
        if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar3) != 0) {
          iVar2 = zz_000673c_(iVar3);
          *(int *)(puVar1 + iVar6 + 0x114) = *(int *)(puVar1 + iVar6 + 0x114) + iVar2;
        }
      }
      else if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar3) != 0) {
        iVar2 = zz_000673c_(iVar3);
        *(int *)(puVar1 + iVar6 + 0x114) = *(int *)(puVar1 + iVar6 + 0x114) + iVar2;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 4);
  }
  iVar3 = 0;
  for (iVar6 = 0; puVar1 = PTR_DAT_80433934, iVar6 < (char)PTR_DAT_80433934[0x53]; iVar6 = iVar6 + 1
      ) {
    iVar4 = *(int *)(PTR_DAT_80433934 + iVar3 + 0x114);
    iVar2 = iVar4 / 10 + (iVar4 >> 0x1f);
    *(int *)(PTR_DAT_80433934 + iVar3 + 0x114) =
         iVar4 - (short)((short)iVar4 + ((short)iVar2 - (short)(iVar2 >> 0x1f)) * -10);
    *(undefined4 *)(puVar1 + iVar3 + 0x11c) = *(undefined4 *)(puVar1 + iVar3 + 0x114);
    *(undefined4 *)(puVar1 + iVar3 + 0x118) = *(undefined4 *)(puVar1 + iVar3 + 0x114);
    iVar3 = iVar3 + 0x3c;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1089-1116 ==== */
// ==== 8000673c  zz_000673c_ ====

int zz_000673c_(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined2 local_28 [8];
  
  iVar4 = 0;
  iVar5 = 0;
  for (iVar3 = 0; iVar3 < (char)PTR_DAT_80433934[param_1 + 0x5a]; iVar3 = iVar3 + 1) {
    iVar1 = param_1 * 0x348 + iVar5;
    if (-1 < *(short *)(PTR_DAT_80433934 + iVar1 + 0x1e8)) {
      local_28[0] = *(undefined2 *)(PTR_DAT_80433934 + iVar1 + 0x1e8);
      uVar2 = zz_0066168_((char *)local_28,(int)(char)PTR_DAT_80433934[iVar1 + 0x1ea]);
      if (((int)(char)PTR_DAT_80433930[2] & 1 << param_1) == 0) {
        uVar2 = (int)(uVar2 * 2) / 3 + ((int)(uVar2 * 2) >> 0x1f) + ((uVar2 & 0x7fffffff) >> 0x1e);
      }
      iVar4 = iVar4 + uVar2;
    }
    iVar5 = iVar5 + 0x1c;
  }
  return iVar4;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1120-1148 ==== */
// ==== 80006800  zz_0006800_ ====

void zz_0006800_(void)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_80433934;
  *(undefined2 *)(PTR_DAT_80433934 + 0x124) = 3000;
  *(undefined2 *)(puVar1 + 0x126) = 0;
  *(undefined2 *)(puVar1 + 0x128) = 0;
  *(undefined2 *)(puVar1 + 0x12a) = 0;
  puVar1 = PTR_DAT_80433934;
  *(undefined2 *)(PTR_DAT_80433934 + 0x160) = 3000;
  *(undefined2 *)(puVar1 + 0x162) = 0;
  *(undefined2 *)(puVar1 + 0x164) = 0;
  *(undefined2 *)(puVar1 + 0x166) = 0;
  puVar1 = PTR_DAT_80433934;
  *(undefined2 *)(PTR_DAT_80433934 + 0x19c) = 3000;
  *(undefined2 *)(puVar1 + 0x19e) = 0;
  *(undefined2 *)(puVar1 + 0x1a0) = 0;
  *(undefined2 *)(puVar1 + 0x1a2) = 0;
  puVar1 = PTR_DAT_80433934;
  *(undefined2 *)(PTR_DAT_80433934 + 0x1d8) = 3000;
  *(undefined2 *)(puVar1 + 0x1da) = 0;
  *(undefined2 *)(puVar1 + 0x1dc) = 0;
  *(undefined2 *)(puVar1 + 0x1de) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1152-1232 ==== */
// ==== 8000685c  zz_000685c_ ====

void zz_000685c_(int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  if ('\x06' < (char)PTR_DAT_80433934[0x15da]) {
    PTR_DAT_80433934[0x15da] = 6;
  }
  if ((char)PTR_DAT_80433934[0x15da] < (char)PTR_DAT_80433930[3]) {
    PTR_DAT_80433934[0x15da] = PTR_DAT_80433930[3];
  }
  if ((param_1 != 0) &&
     (PTR_DAT_80433934[0x15d9] = PTR_DAT_80433930[2],
     (char)PTR_DAT_80433930[3] < (char)PTR_DAT_80433934[0x15da])) {
    iVar4 = 0;
    iVar5 = 0;
    while( true ) {
      if ((int)(char)PTR_DAT_80433934[0x15da] - (int)(char)PTR_DAT_80433930[3] <= iVar5) break;
      if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar4) == 0) {
        iVar5 = iVar5 + 1;
        PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] | (byte)(1 << iVar4);
      }
      iVar4 = iVar4 + 1;
    }
  }
  iVar4 = 0;
  iVar8 = 0;
  iVar7 = 0;
  iVar5 = 0;
  PTR_DAT_80433934[0x15db] = PTR_DAT_80433934[0x15d9];
  PTR_DAT_80433934[0x15dc] = PTR_DAT_80433934[0x15da];
  do {
    iVar3 = 0;
    iVar6 = 0;
    PTR_DAT_80433934[iVar4 + 0x15ce] = 0;
    while( true ) {
      puVar1 = PTR_DAT_80433934;
      if ((char)PTR_DAT_80433934[iVar4 + 0x5a] <= iVar6) break;
      iVar2 = iVar8 + iVar3;
      PTR_DAT_80433934[iVar2 + 0x1fe] = 0;
      puVar1[iVar2 + 0x200] = 0;
      if (iVar6 == (char)PTR_DAT_80433934[iVar4 + 0x5a] + -1) {
        PTR_DAT_80433934[iVar4 + 0x15ce] = (char)iVar6;
        puVar1[iVar2 + 0x1ff] = 0;
      }
      else {
        puVar1[iVar2 + 0x1ff] = 1;
      }
      iVar3 = iVar3 + 0x1c;
      iVar6 = iVar6 + 1;
    }
    if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar4) == 0) {
      PTR_DAT_80433934[iVar4 + 0x54] = 0;
      PTR_DAT_80433934[iVar4 + 0x15c8] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar5 + 0x10) = 0xffff;
      PTR_DAT_80433934[iVar4 + 0x5a] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar7 + 0x159e) = 0;
    }
    else {
      PTR_DAT_80433934[iVar4 + 0x54] = 0;
      PTR_DAT_80433934[iVar4 + 0x15c8] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar7 + 0x159e) = 1;
      zz_0068424_(iVar4,(undefined2 *)(PTR_DAT_80433934 + iVar5 + 0x10),
                  PTR_DAT_80433934 + iVar4 + 0xa0);
    }
    iVar4 = iVar4 + 1;
    iVar7 = iVar7 + 8;
    iVar5 = iVar5 + 2;
    iVar8 = iVar8 + 0x348;
  } while (iVar4 < 6);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1236-1264 ==== */
// ==== 80006abc  zz_0006abc_ ====

void zz_0006abc_(void)

{
  char cVar1;
  
  cVar1 = PTR_DAT_80433930[0x32];
  if (cVar1 == '\x01') {
    *PTR_DAT_80433950 = 0;
    PTR_DAT_80433950[1] = 0x1f;
    *PTR_DAT_80433950 = *PTR_DAT_80433950 + (char)*(undefined2 *)(PTR_DAT_80433934 + 0x46);
    *PTR_DAT_80433950 = *PTR_DAT_80433950 & 0x1f;
    PTR_DAT_80433950[1] = PTR_DAT_80433950[1] - (char)*(undefined2 *)(PTR_DAT_80433934 + 0x46);
    PTR_DAT_80433950[1] = PTR_DAT_80433950[1] & 0x1f;
    return;
  }
  if (cVar1 < '\x01') {
    return;
  }
  if ('\x02' < cVar1) {
    return;
  }
  *PTR_DAT_80433950 = 7;
  PTR_DAT_80433950[1] = 7;
  PTR_DAT_80433950[2] = 7;
  PTR_DAT_80433950[3] = 7;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1268-1286 ==== */
// ==== 80006b74  zz_0006b74_ ====

void zz_0006b74_(void)

{
  *(int *)(PTR_DAT_80433934 + 0x17f8) = DAT_80436238 + 0xd6800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1810) = 0;
  *(int *)(PTR_DAT_80433934 + 0x17fc) = DAT_80436238 + 0xd9800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1814) = 0;
  *(int *)(PTR_DAT_80433934 + 0x1800) = DAT_80436238 + 0xdc800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1818) = 0;
  *(int *)(PTR_DAT_80433934 + 0x1804) = DAT_80436238 + 0xdf800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x181c) = 0;
  *(int *)(PTR_DAT_80433934 + 0x1808) = DAT_80436238 + 0xe2800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1820) = 0;
  *(int *)(PTR_DAT_80433934 + 0x180c) = DAT_80436238 + 0xe5800;
  *(undefined4 *)(PTR_DAT_80433934 + 0x1824) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1290-1308 ==== */
// ==== 80006c24  zz_0006c24_ ====

void zz_0006c24_(int param_1,int param_2)

{
  if (PTR_DAT_80433930[0x32] != '\x01') {
    return;
  }
  if (0xfff < *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 4 + 0x1810)) {
    return;
  }
  *(undefined2 *)
   (*(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 4 + 0x17f8) +
   *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 4 + 0x1810) * 2) =
       *(undefined2 *)(param_2 + 0x3ea);
  *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 4 + 0x1810) =
       *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 4 + 0x1810) + 1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1312-1352 ==== */
// ==== 80006c88  zz_0006c88_ ====

void zz_0006c88_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,void *param_10,uint param_11,undefined4 param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  char cVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  short sVar6;
  char cVar7;
  
  gnt4_HSD_ArchiveParse_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
             *(uint **)(param_9 + 0xc),param_10,param_11,param_12,param_13,param_14,param_15,
             param_16);
  pcVar3 = (char *)zz_025b178_(*(int *)(param_9 + 0xc),0);
  piVar4 = (int *)gnt4_HSD_ArchiveGetPublicAddress_bl(*(int *)(param_9 + 0xc),pcVar3);
  *(int **)(param_9 + 0x10) = piVar4;
  sVar6 = 0;
  for (iVar5 = 0; *(int *)(*piVar4 + iVar5) != 0; iVar5 = iVar5 + 4) {
    sVar1 = sVar6 + 1;
    sVar6 = sVar6 + 1;
    *(short *)(param_9 + 0x1a) = sVar1;
  }
  cVar7 = '\0';
  for (iVar5 = 0; *(int *)(piVar4[2] + iVar5) != 0; iVar5 = iVar5 + 4) {
    cVar2 = cVar7 + '\x01';
    cVar7 = cVar7 + '\x01';
    *(char *)(param_9 + 0x18) = cVar2;
  }
  if (piVar4[3] != 0) {
    *(undefined1 *)(param_9 + 0x19) = 1;
  }
  *(undefined1 *)(param_9 + 10) = 1;
  return;
}
