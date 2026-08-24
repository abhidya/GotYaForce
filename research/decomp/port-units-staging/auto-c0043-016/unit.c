#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801718b8(int param_1);
void FUN_80171954(undefined1 *param_1);
void FUN_80171b78(int param_1);
void FUN_80171c14(undefined1 *param_1);
void FUN_80171f58(int param_1);
void FUN_80171f94(int param_1);
void FUN_80172044(int param_1);
void FUN_80172108(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7195-7202 ==== */
// ==== 801718b8  FUN_801718b8 ====

void FUN_801718b8(int param_1)

{
  (*(code *)(&PTR_LAB_8035179c)[*(char *)(param_1 + 1)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7206-7276 ==== */
// ==== 80171954  FUN_80171954 ====

void FUN_80171954(undefined1 *param_1)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  
  if (*(short *)(param_1 + 4) == 0) {
    iVar5 = (int)(char)param_1[0x66];
    if ((*(ushort *)(param_1 + 8) & 1) == 0) {
      if ((*(ushort *)(param_1 + 8) & 2) != 0) {
        for (iVar5 = iVar5 + 1; (char)PTR_DAT_80433944[0x90] <= iVar5;
            iVar5 = iVar5 - (char)PTR_DAT_80433944[0x90]) {
        }
        param_1[0x67] = 2;
      }
    }
    else {
      for (iVar5 = iVar5 + -1; iVar5 < 0; iVar5 = iVar5 + (char)PTR_DAT_80433944[0x90]) {
      }
      param_1[0x67] = 1;
    }
    if (iVar5 != (char)param_1[0x66]) {
      cVar6 = '\0';
      param_1[0x61] = 0;
      puVar2 = PTR_DAT_80433944;
      iVar3 = 0x14;
      iVar4 = 0;
      param_1[0x66] = (char)iVar5;
      *(undefined4 *)(param_1 + 0x40) = (&DAT_803bfe00)[(char)puVar2[(char)iVar5 + 0x88]];
      param_1[0x60] = 0;
      do {
        if (*(char *)(*(int *)(param_1 + 0x40) + iVar4 + 0x29) != '\0') {
          cVar1 = param_1[0x60];
          param_1[0x60] = cVar1 + '\x01';
          param_1[cVar1 + 0x4c] = cVar6;
        }
        iVar4 = iVar4 + 0x6c;
        cVar6 = cVar6 + '\x01';
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
      param_1[1] = param_1[1] + '\x01';
      param_1[0x3e] = param_1[0x3e] & 0xfd;
      param_1[0x3f] = param_1[0x3f] | 2;
      *(undefined2 *)(param_1 + 4) = 0x10;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[0x3d] = param_1[0x3d] & 0xfd;
    param_1[0x3e] = param_1[0x3e] & 0xfd;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7280-7287 ==== */
// ==== 80171b78  FUN_80171b78 ====

void FUN_80171b78(int param_1)

{
  (*(code *)(&PTR_LAB_803517ac)[*(char *)(param_1 + 1)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7291-7396 ==== */
// ==== 80171c14  FUN_80171c14 ====

void FUN_80171c14(undefined1 *param_1)

{
  ushort uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar3 = (int)(char)param_1[0x61];
  if ((*(ushort *)(param_1 + 0xc) & 1) == 0) {
    if ((*(ushort *)(param_1 + 0xc) & 2) != 0) {
      for (iVar3 = iVar3 + 1; (char)param_1[0x60] <= iVar3;
          iVar3 = iVar3 - ((char)param_1[0x60] + 1)) {
      }
    }
  }
  else {
    for (iVar3 = iVar3 + -1; iVar3 < -1; iVar3 = (char)param_1[0x60] + iVar3 + 1) {
    }
  }
  if (iVar3 != (char)param_1[0x61]) {
    param_1[0x61] = (char)iVar3;
    zz_00f0468_(0,0x77,0);
  }
  uVar1 = *(ushort *)(param_1 + 0xe);
  if ((uVar1 & 0x200) == 0) {
    if ((uVar1 & 0x10) == 0) {
      if ((uVar1 & 0x800) == 0) {
        if ((uVar1 & 0x400) == 0) {
          if ((uVar1 & 0x180) != 0) {
            if ((((char)param_1[0x61] < '\0') ||
                (iVar3 = zz_01cce38_(*(int *)(param_1 + 0x40),
                                     (int)(char)param_1[(char)param_1[0x61] + 0x4c],
                                     *(int *)(PTR_DAT_80433934 +
                                             ((byte)PTR_DAT_80433944[(byte)param_1[0x3c] + 0x28] & 1
                                             ) * 0x3c + 0x120),0), iVar3 == 0)) &&
               (param_1[0x61] != -1)) {
              zz_00f0468_(0,0x7d,0);
            }
            else {
              param_1[1] = param_1[1] + '\x01';
              param_1[0x3e] = param_1[0x3e] & 0xfb;
              param_1[0x3f] = param_1[0x3f] | 4;
              *(undefined2 *)(param_1 + 4) = 0x10;
              zz_00f0468_(0,0x7a,0);
            }
          }
        }
        else {
          iVar4 = 0;
          iVar3 = 4;
          uVar5 = 0;
          puVar2 = PTR_DAT_80433944;
          do {
            if ((puVar2[0x20] & 0xc0) == 0x80) {
              uVar5 = uVar5 | 1 << iVar4;
            }
            puVar2 = puVar2 + 1;
            iVar4 = iVar4 + 1;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
          if ((uVar5 == 0) || (-1 < (char)PTR_DAT_80433944[0x84])) {
            zz_00f0468_(0,0x7d,0);
          }
          else {
            *param_1 = 4;
            param_1[1] = 0;
            param_1[0x3e] = param_1[0x3e] & 0xfb;
            PTR_DAT_80433944[0x84] = param_1[0x3c];
            zz_00f0468_(0,0x7a,0);
          }
        }
      }
      else {
        PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] | 8;
        zz_00f0468_(0,0x7a,0);
      }
    }
    else if ((char)param_1[0x61] < '\0') {
      zz_00f0468_(0,0x7d,0);
    }
    else {
      *param_1 = 3;
      param_1[1] = 0;
      param_1[0x3d] = param_1[0x3d] & 0xfb;
      param_1[0x3e] = param_1[0x3e] & 0xfb;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    if ((char)PTR_DAT_80433944[0x90] < '\x02') {
      *param_1 = 0;
    }
    else {
      *param_1 = 1;
    }
    param_1[1] = 0;
    param_1[0x3d] = param_1[0x3d] & 0xfb;
    param_1[0x3e] = param_1[0x3e] & 0xfb;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7400-7407 ==== */
// ==== 80171f58  FUN_80171f58 ====

void FUN_80171f58(int param_1)

{
  (*(code *)(&PTR_FUN_803517bc)[*(char *)(param_1 + 1)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7411-7432 ==== */
// ==== 80171f94  FUN_80171f94 ====

void FUN_80171f94(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
  *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) | 8;
  *(undefined2 *)(param_1 + 4) = 4;
  *(short *)(param_1 + 6) =
       (short)*(char *)(*(int *)(param_1 + 0x40) +
                        *(char *)(param_1 + *(char *)(param_1 + 0x61) + 0x4c) * 0x6c + 0x29);
  *(undefined1 *)(param_1 + 100) = 0;
  *(char *)(param_1 + 0x65) = (char)*(undefined2 *)(param_1 + 6) + '\x02';
  do {
    zz_0167334_(*(undefined1 *)(param_1 + 0x3c),10,(char)iVar1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 5);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7436-7466 ==== */
// ==== 80172044  FUN_80172044 ====

void FUN_80172044(int param_1)

{
  char cVar1;
  short sVar2;
  
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    sVar2 = *(short *)(param_1 + 4) + -1;
    *(short *)(param_1 + 4) = sVar2;
    if (sVar2 < 1) {
      cVar1 = *(char *)(param_1 + 0x65) + -1;
      *(char *)(param_1 + 0x65) = cVar1;
      if (cVar1 <= *(char *)(param_1 + 100)) {
        *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
        *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) | 8;
        *(byte *)(param_1 + 0x3f) = *(byte *)(param_1 + 0x3f) & 0xf7;
        *(undefined1 *)(param_1 + 0x65) = *(undefined1 *)(param_1 + 100);
      }
      *(undefined2 *)(param_1 + 4) = 4;
    }
  }
  else {
    *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x02';
    *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xf7;
    *(undefined2 *)(param_1 + 4) = 4;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0043.c 7470-7516 ==== */
// ==== 80172108  FUN_80172108 ====

void FUN_80172108(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(short *)(param_1 + 4) == 0) {
    iVar2 = (int)*(char *)(param_1 + 100);
    if ((*(ushort *)(param_1 + 8) & 8) == 0) {
      iVar3 = iVar2;
      if ((*(ushort *)(param_1 + 8) & 4) != 0) {
        iVar1 = *(short *)(param_1 + 6) + -1;
        iVar3 = iVar2 + 1;
        if (iVar1 < iVar2 + 1) {
          iVar3 = iVar1;
        }
      }
    }
    else {
      iVar3 = iVar2 + -1;
      if (iVar2 + -1 < 0) {
        iVar3 = 0;
      }
    }
    if (iVar3 != *(char *)(param_1 + 100)) {
      *(char *)(param_1 + 0x65) = (char)iVar3;
      *(char *)(param_1 + 100) = (char)iVar3;
      *(undefined2 *)(param_1 + 4) = 7;
      zz_00f0468_(0,0x77,0);
    }
  }
  else {
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + -1;
  }
  if ((*(ushort *)(param_1 + 0xe) & 0x200) != 0) {
    *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
    *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xf7;
    *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xf7;
    *(undefined1 *)(param_1 + 0x65) = *(undefined1 *)(param_1 + 100);
    *(undefined2 *)(param_1 + 4) = 4;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}
