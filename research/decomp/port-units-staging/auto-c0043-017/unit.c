#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80172258(int param_1);
void FUN_80172294(int param_1);
void FUN_801723a8(int param_1);
void FUN_8017265c(int param_1);
void FUN_80172724(int param_1,int param_2);
void FUN_80172a14(int param_1);
void FUN_80172adc(int param_1,int param_2);
void FUN_80172e24(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7520-7527 ==== */
// ==== 80172258  FUN_80172258 ====

void FUN_80172258(int param_1)

{
  (*(code *)(&PTR_FUN_803517cc)[*(char *)(param_1 + 1)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7531-7557 ==== */
// ==== 80172294  FUN_80172294 ====

void FUN_80172294(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = 4;
  *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
  *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xfb;
  *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) | 0x10;
  *(undefined2 *)(param_1 + 4) = 0x20;
  *(undefined *)(param_1 + 100) = PTR_DAT_80433944[*(byte *)(param_1 + 0x3c) + 0x28];
  *(undefined1 *)(param_1 + 0x65) = 0;
  do {
    if ((iVar2 == (char)PTR_DAT_80433944[*(byte *)(param_1 + 0x3c) + 0x28]) ||
       ((PTR_DAT_80433944[iVar2 + 0x20] & 0xc0) == 0x80)) {
      *(byte *)(param_1 + 0x65) = *(byte *)(param_1 + 0x65) | (byte)(1 << iVar2);
    }
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  zz_011c648_(0x10,*(undefined1 *)(param_1 + 0x3c));
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7561-7665 ==== */
// ==== 801723a8  FUN_801723a8 ====

void FUN_801723a8(int param_1)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  char cVar8;
  
  uVar2 = *(ushort *)(param_1 + 8);
  uVar6 = (uint)*(char *)(param_1 + 100);
  if ((uVar2 & 8) == 0) {
    if ((uVar2 & 4) != 0) {
      uVar6 = uVar6 | 2;
    }
  }
  else {
    uVar6 = uVar6 & 0xfffffffd;
  }
  if ((uVar2 & 1) == 0) {
    if ((uVar2 & 2) != 0) {
      uVar6 = uVar6 | 1;
    }
  }
  else {
    uVar6 = uVar6 & 0xfffffffe;
  }
  if ((int)uVar6 < 4) {
    uVar6 = uVar6 & ~((int)uVar6 >> 0x1f);
  }
  else {
    uVar6 = 3;
  }
  if ((((int)*(char *)(param_1 + 0x65) & 1 << uVar6) != 0) &&
     (uVar6 != (int)*(char *)(param_1 + 100))) {
    *(char *)(param_1 + 100) = (char)uVar6;
    zz_00f0468_(0,0x77,0);
  }
  puVar4 = PTR_DAT_80433944;
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    if ((*(ushort *)(param_1 + 0xe) & 0x180) != 0) {
      if ((int)*(char *)(param_1 + 100) ==
          (int)(char)PTR_DAT_80433944[*(byte *)(param_1 + 0x3c) + 0x28]) {
        *(undefined1 *)(param_1 + 1) = 6;
        *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xef;
        *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xef;
        *(undefined2 *)(param_1 + 4) = 4;
        zz_00f0468_(0,0x7a,0);
      }
      else {
        iVar3 = ((byte)PTR_DAT_80433944[*(char *)(param_1 + 100) + 0x20] & 0xf) * 0x80;
        PTR_DAT_80433944[0x85] = PTR_DAT_80433944[iVar3 + 0x166];
        PTR_DAT_80433944[0x86] = puVar4[iVar3 + 0x161];
        PTR_DAT_80433944[0x87] = puVar4[iVar3 + 0x13f];
        if ((PTR_DAT_80433944[0x87] & 4) == 0) {
          if ((char)PTR_DAT_80433944[0x90] < '\x02') {
            *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x02';
          }
          else {
            *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
          }
          cVar8 = '\0';
          puVar4[iVar3 + 0x161] = 0;
          iVar5 = 0x14;
          iVar7 = 0;
          puVar4[iVar3 + 0x166] = *(undefined1 *)(param_1 + 0x66);
          *(undefined4 *)(puVar4 + iVar3 + 0x140) =
               (&DAT_803bfe00)[(char)PTR_DAT_80433944[(char)puVar4[iVar3 + 0x166] + 0x88]];
          puVar4[iVar3 + 0x160] = 0;
          do {
            if (*(char *)(*(int *)(puVar4 + iVar3 + 0x140) + iVar7 + 0x29) != '\0') {
              cVar1 = puVar4[iVar3 + 0x160];
              puVar4[iVar3 + 0x160] = cVar1 + '\x01';
              puVar4[(int)cVar1 + iVar3 + 0x14c] = cVar8;
            }
            iVar7 = iVar7 + 0x6c;
            cVar8 = cVar8 + '\x01';
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
        }
        else {
          *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x02';
        }
        *(undefined1 *)(param_1 + 2) = 0;
        *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xef;
        *(byte *)(param_1 + 0x3f) = *(byte *)(param_1 + 0x3f) | 0x10;
        *(undefined2 *)(param_1 + 4) = 4;
        zz_00f0468_(0,0x7b,0);
      }
    }
  }
  else {
    *(undefined1 *)(param_1 + 1) = 6;
    *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xef;
    *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xef;
    *(undefined2 *)(param_1 + 4) = 4;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7669-7679 ==== */
// ==== 8017265c  FUN_8017265c ====

void FUN_8017265c(int param_1)

{
  (*(code *)(&PTR_LAB_803517e8)[*(char *)(param_1 + 2)])
            (param_1,PTR_DAT_80433944 +
                     ((byte)PTR_DAT_80433944[*(char *)(param_1 + 100) + 0x20] & 0xf) * 0x80 + 0x100)
  ;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7683-7773 ==== */
// ==== 80172724  FUN_80172724 ====

void FUN_80172724(int param_1,int param_2)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  
  if (*(short *)(param_1 + 4) == 0) {
    iVar6 = (int)*(char *)(param_2 + 0x66);
    if ((*(ushort *)(param_1 + 8) & 1) == 0) {
      if ((*(ushort *)(param_1 + 8) & 2) != 0) {
        for (iVar6 = iVar6 + 1; (char)PTR_DAT_80433944[0x90] <= iVar6;
            iVar6 = iVar6 - (char)PTR_DAT_80433944[0x90]) {
        }
        *(undefined1 *)(param_2 + 0x67) = 2;
      }
    }
    else {
      for (iVar6 = iVar6 + -1; iVar6 < 0; iVar6 = iVar6 + (char)PTR_DAT_80433944[0x90]) {
      }
      *(undefined1 *)(param_2 + 0x67) = 1;
    }
    if (iVar6 != *(char *)(param_2 + 0x66)) {
      cVar5 = '\0';
      *(undefined1 *)(param_2 + 0x61) = 0;
      puVar2 = PTR_DAT_80433944;
      iVar3 = 0x14;
      iVar4 = 0;
      *(char *)(param_2 + 0x66) = (char)iVar6;
      *(undefined4 *)(param_2 + 0x40) = (&DAT_803bfe00)[(char)puVar2[(char)iVar6 + 0x88]];
      *(undefined1 *)(param_2 + 0x60) = 0;
      do {
        if (*(char *)(*(int *)(param_2 + 0x40) + iVar4 + 0x29) != '\0') {
          cVar1 = *(char *)(param_2 + 0x60);
          *(char *)(param_2 + 0x60) = cVar1 + '\x01';
          *(char *)(param_2 + cVar1 + 0x4c) = cVar5;
        }
        iVar4 = iVar4 + 0x6c;
        cVar5 = cVar5 + '\x01';
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      *(undefined2 *)(param_1 + 4) = 9;
      zz_00f0468_(0,0x77,0);
    }
  }
  else {
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + -1;
  }
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    if ((*(ushort *)(param_1 + 0xe) & 0x180) != 0) {
      *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
      *(undefined2 *)(param_1 + 4) = 0x10;
      *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xfd;
      *(byte *)(param_2 + 0x3f) = *(byte *)(param_2 + 0x3f) | 2;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    cVar5 = '\0';
    iVar6 = 0x14;
    *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + -2;
    iVar3 = 0;
    *(undefined1 *)(param_1 + 2) = 0;
    *(undefined2 *)(param_1 + 4) = 2;
    *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0xfd;
    *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xfd;
    *(undefined *)(param_2 + 0x66) = PTR_DAT_80433944[0x85];
    *(undefined *)(param_2 + 0x61) = PTR_DAT_80433944[0x86];
    *(undefined *)(param_2 + 0x3f) = PTR_DAT_80433944[0x87];
    *(undefined4 *)(param_2 + 0x40) =
         (&DAT_803bfe00)[(char)PTR_DAT_80433944[*(char *)(param_2 + 0x66) + 0x88]];
    *(undefined1 *)(param_2 + 0x60) = 0;
    do {
      if (*(char *)(*(int *)(param_2 + 0x40) + iVar3 + 0x29) != '\0') {
        cVar1 = *(char *)(param_2 + 0x60);
        *(char *)(param_2 + 0x60) = cVar1 + '\x01';
        *(char *)(param_2 + cVar1 + 0x4c) = cVar5;
      }
      iVar3 = iVar3 + 0x6c;
      cVar5 = cVar5 + '\x01';
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7777-7787 ==== */
// ==== 80172a14  FUN_80172a14 ====

void FUN_80172a14(int param_1)

{
  (*(code *)(&PTR_LAB_803517f8)[*(char *)(param_1 + 2)])
            (param_1,PTR_DAT_80433944 +
                     ((byte)PTR_DAT_80433944[*(char *)(param_1 + 100) + 0x20] & 0xf) * 0x80 + 0x100)
  ;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7791-7885 ==== */
// ==== 80172adc  FUN_80172adc ====

void FUN_80172adc(int param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  char cVar4;
  int iVar5;
  
  iVar5 = (int)*(char *)(param_2 + 0x61);
  if ((*(ushort *)(param_1 + 0xc) & 1) == 0) {
    if ((*(ushort *)(param_1 + 0xc) & 2) != 0) {
      for (iVar5 = iVar5 + 1; *(char *)(param_2 + 0x60) <= iVar5;
          iVar5 = iVar5 - (*(char *)(param_2 + 0x60) + 1)) {
      }
    }
  }
  else {
    for (iVar5 = iVar5 + -1; iVar5 < -1; iVar5 = *(char *)(param_2 + 0x60) + iVar5 + 1) {
    }
  }
  if (iVar5 != *(char *)(param_2 + 0x61)) {
    *(char *)(param_2 + 0x61) = (char)iVar5;
    zz_00f0468_(0,0x77,0);
  }
  uVar2 = *(ushort *)(param_1 + 0xe);
  if ((uVar2 & 0x200) == 0) {
    if ((uVar2 & 0x10) == 0) {
      if ((uVar2 & 0x180) != 0) {
        if (((*(char *)(param_2 + 0x61) < '\0') ||
            (iVar5 = zz_01cce38_(*(int *)(param_2 + 0x40),
                                 (int)*(char *)(param_2 + *(char *)(param_2 + 0x61) + 0x4c),
                                 *(int *)(PTR_DAT_80433934 +
                                         ((byte)PTR_DAT_80433944[*(byte *)(param_2 + 0x3c) + 0x28] &
                                         1) * 0x3c + 0x120),1), iVar5 == 0)) &&
           (*(char *)(param_2 + 0x61) != -1)) {
          zz_00f0468_(0,0x7d,0);
        }
        else {
          *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
          *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xfb;
          *(byte *)(param_2 + 0x3f) = *(byte *)(param_2 + 0x3f) | 4;
          *(undefined2 *)(param_1 + 4) = 0x10;
          zz_00f0468_(0,0x7a,0);
        }
      }
    }
    else if (*(char *)(param_2 + 0x61) < '\0') {
      zz_00f0468_(0,0x7d,0);
    }
    else {
      *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
      *(undefined1 *)(param_1 + 2) = 0;
      *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0xfb;
      *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xfb;
      *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) | 0x80;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    if ((char)PTR_DAT_80433944[0x90] < '\x02') {
      cVar4 = '\0';
      iVar5 = 0x14;
      *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + -3;
      iVar3 = 0;
      *(undefined *)(param_2 + 0x66) = PTR_DAT_80433944[0x85];
      *(undefined *)(param_2 + 0x61) = PTR_DAT_80433944[0x86];
      *(undefined *)(param_2 + 0x3f) = PTR_DAT_80433944[0x87];
      *(undefined4 *)(param_2 + 0x40) =
           (&DAT_803bfe00)[(char)PTR_DAT_80433944[*(char *)(param_2 + 0x66) + 0x88]];
      *(undefined1 *)(param_2 + 0x60) = 0;
      do {
        if (*(char *)(*(int *)(param_2 + 0x40) + iVar3 + 0x29) != '\0') {
          cVar1 = *(char *)(param_2 + 0x60);
          *(char *)(param_2 + 0x60) = cVar1 + '\x01';
          *(char *)(param_2 + cVar1 + 0x4c) = cVar4;
        }
        iVar3 = iVar3 + 0x6c;
        cVar4 = cVar4 + '\x01';
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    else {
      *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + -1;
      *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) | 0x80;
    }
    *(undefined1 *)(param_1 + 2) = 0;
    *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0xfb;
    *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xfb;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7889-7899 ==== */
// ==== 80172e24  FUN_80172e24 ====

void FUN_80172e24(int param_1)

{
  (*(code *)(&PTR_FUN_80351808)[*(char *)(param_1 + 2)])
            (param_1,PTR_DAT_80433944 +
                     ((byte)PTR_DAT_80433944[*(char *)(param_1 + 100) + 0x20] & 0xf) * 0x80 + 0x100)
  ;
  return;
}
