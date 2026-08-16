#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_00107a0_(int param_1,undefined1 param_2);
void zz_001080c_(double param_1,int param_2,undefined4 param_3,undefined1 param_4,undefined2 param_5 ,undefined1 param_6);
void FUN_800108c8(int param_1);
void FUN_80010924(int param_1);
void zz_0010980_(int param_1);
void zz_0010b50_(void);
void zz_0010b64_(void);
void zz_0010c7c_(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 3244-3258 ==== */
// ==== 800107a0  zz_00107a0_ ====

void zz_00107a0_(int param_1,undefined1 param_2)

{
  uint uVar1;
  
  uVar1 = zz_0010514_((int)*(char *)(param_1 + 0x3e4));
  if (((uVar1 & 0x20) == 0) && (PTR_DAT_80433934[0x1f] == '\0')) {
    *(undefined1 *)(param_1 + 0x43d) = 0x81;
    *(undefined1 *)(param_1 + 0x6f8) = param_2;
    *(undefined1 *)(param_1 + 0x6f9) = 0xff;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 3262-3284 ==== */
// ==== 8001080c  zz_001080c_ ====

void zz_001080c_(double param_1,int param_2,undefined4 param_3,undefined1 param_4,undefined2 param_5
                ,undefined1 param_6)

{
  uint uVar1;
  char cVar3;
  int iVar2;
  
  uVar1 = zz_0010514_((int)*(char *)(param_2 + 0x3e4));
  if (((((uVar1 & 1) == 0) && (cVar3 = zz_008b480_(), cVar3 == '\0')) &&
      (cVar3 = zz_008b290_(), cVar3 == '\0')) && (PTR_DAT_80433934[0x1f] == '\0')) {
    *(undefined1 *)(param_2 + 0x43d) = 0x87;
    iVar2 = (*(char *)(param_2 + 0x3e4) + 6) * 0x3e4;
    (&DAT_803c7439)[iVar2] = param_4;
    *(float *)(&DAT_803c73f4 + iVar2) = (float)param_1;
    *(undefined4 *)(&DAT_803c747c + iVar2) = param_3;
    *(undefined2 *)(&DAT_803c73ce + iVar2) = param_5;
    (&DAT_803c73c2)[iVar2] = param_6;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 3288-3301 ==== */
// ==== 800108c8  FUN_800108c8 ====

void FUN_800108c8(int param_1)

{
  char cVar1;
  
  cVar1 = zz_008b480_();
  if (((cVar1 == '\0') && (cVar1 = zz_008b290_(), cVar1 == '\0')) &&
     (PTR_DAT_80433934[0x1f] == '\0')) {
    *(undefined1 *)(param_1 + 0x43d) = 0x88;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 3305-3318 ==== */
// ==== 80010924  FUN_80010924 ====

void FUN_80010924(int param_1)

{
  char cVar1;
  
  cVar1 = zz_008b480_();
  if (((cVar1 == '\0') && (cVar1 = zz_008b290_(), cVar1 == '\0')) &&
     (PTR_DAT_80433934[0x1f] == '\0')) {
    *(undefined1 *)(param_1 + 0x43d) = 0x89;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 3322-3398 ==== */
// ==== 80010980  zz_0010980_ ====

void zz_0010980_(int param_1)

{
  char cVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x1da) == '\0') {
    *(char *)(param_1 + 0x35b) =
         (char)(int)((float)((double)CONCAT44(0x43300000,(uint)*(byte *)(param_1 + 0x35b)) -
                            DOUBLE_80436b88) * FLOAT_80436ae4);
  }
  else {
    iVar2 = *(int *)(param_1 + 0x290);
    cVar1 = *(char *)(iVar2 + 0x10);
    if (cVar1 == '\a') {
      *(undefined1 *)(param_1 + 0x358) = 0;
      *(undefined1 *)(param_1 + 0x359) = 0;
      *(undefined1 *)(param_1 + 0x35a) = 0;
      *(undefined1 *)(param_1 + 0x35b) = 0xc0;
    }
    else if ((cVar1 == 'I') || (cVar1 == '\v')) {
      *(undefined1 *)(param_1 + 0x358) = 0xff;
      *(undefined1 *)(param_1 + 0x359) = 0xff;
      *(undefined1 *)(param_1 + 0x35a) = 0xff;
      *(undefined1 *)(param_1 + 0x35b) = 0xc0;
    }
    else if (cVar1 == ':') {
      cVar1 = *(char *)(iVar2 + 0x11);
      if (cVar1 == '\x01') {
        *(undefined1 *)(param_1 + 0x358) = 0xff;
        *(undefined1 *)(param_1 + 0x359) = 0;
        *(undefined1 *)(param_1 + 0x35a) = 0x66;
        *(undefined1 *)(param_1 + 0x35b) = 0x33;
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(undefined1 *)(param_1 + 0x358) = 0;
          *(undefined1 *)(param_1 + 0x359) = 0;
          *(undefined1 *)(param_1 + 0x35a) = 0xff;
          *(undefined1 *)(param_1 + 0x35b) = 0x33;
        }
      }
      else if (cVar1 < '\x03') {
        *(undefined1 *)(param_1 + 0x358) = 0;
        *(undefined1 *)(param_1 + 0x359) = 0;
        *(undefined1 *)(param_1 + 0x35a) = 0x33;
        *(undefined1 *)(param_1 + 0x35b) = 0x33;
      }
    }
    else if (cVar1 == '\x03') {
      cVar1 = *(char *)(iVar2 + 0x11);
      if (cVar1 == '\x01') {
        *(undefined1 *)(param_1 + 0x358) = 0;
        *(undefined1 *)(param_1 + 0x359) = 0xff;
        *(undefined1 *)(param_1 + 0x35a) = 0;
        *(undefined1 *)(param_1 + 0x35b) = 0x33;
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(undefined1 *)(param_1 + 0x358) = 0xff;
          *(undefined1 *)(param_1 + 0x359) = 0;
          *(undefined1 *)(param_1 + 0x35a) = 0;
          *(undefined1 *)(param_1 + 0x35b) = 0x33;
        }
      }
      else if (cVar1 < '\x03') {
        *(undefined1 *)(param_1 + 0x358) = 0;
        *(undefined1 *)(param_1 + 0x359) = 0;
        *(undefined1 *)(param_1 + 0x35a) = 0xff;
        *(undefined1 *)(param_1 + 0x35b) = 0x33;
      }
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 3402-3411 ==== */
// ==== 80010b50  zz_0010b50_ ====

void zz_0010b50_(void)

{
  DAT_804360dc = 0;
  DAT_804360da = 0;
  DAT_804360d8 = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 3415-3459 ==== */
// ==== 80010b64  zz_0010b64_ ====

void zz_0010b64_(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  
  DAT_804360d8 = DAT_804360d8 + -1;
  if (DAT_804360d8 < 1) {
    iVar2 = 0;
    iVar5 = 5;
    do {
      if (iVar2 == 0) {
        pcVar3 = *(char **)((&DAT_803c4e84)[DAT_804360dc] + 0xcc);
        if (pcVar3 != (char *)0x0) {
          if (pcVar3[0x83] == '\0') {
            DAT_804360dc = pcVar3[0x3e4];
            goto LAB_80010c10;
          }
        }
      }
      else {
        iVar4 = DAT_804360dc + 1;
        cVar1 = (char)(iVar4 >> 0x1f);
        DAT_804360dc = (cVar1 * '\x04' |
                       (byte)((uint)(iVar4 * 0x40000000 + (iVar4 >> 0x1f)) >> 0x1e)) - cVar1;
        pcVar3 = (char *)(&DAT_803c4e84)[DAT_804360dc];
LAB_80010c10:
        if ((((*pcVar3 != '\0') && (pcVar3[1000] != '\x0e')) && (pcVar3[0x18] == '\x01')) &&
           (pcVar3[0x19] == '\x02')) break;
      }
      iVar2 = iVar2 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    DAT_804360d8 = 300;
    DAT_804360db = 1;
    DAT_803ca278 = 0;
  }
  zz_0010c7c_();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 3463-3520 ==== */
// ==== 80010c7c  zz_0010c7c_ ====

void zz_0010c7c_(void)

{
  uint uVar1;
  int iVar2;
  
  DAT_803ca260 = 1;
  iVar2 = (&DAT_803c4e84)[DAT_804360dc];
  DAT_803ca554 = DAT_803ca548;
  DAT_803ca558 = DAT_803ca54c;
  DAT_803ca55c = DAT_803ca550;
  DAT_803ca56c = DAT_803ca560;
  DAT_803ca570 = DAT_803ca564;
  DAT_803ca574 = DAT_803ca568;
  DAT_803ca5b4 = *(undefined4 *)(iVar2 + 0xb4);
  if (DAT_803ca278 != '\x01') {
    if (('\0' < DAT_803ca278) || (DAT_803ca278 < '\0')) {
      if (((DAT_803ca271 == -1) || (DAT_804360db == '\x01')) || ('\x02' < *(char *)(iVar2 + 0x18)))
      {
        DAT_803ca260 = 1;
        DAT_803ca554 = DAT_803ca548;
        DAT_803ca558 = DAT_803ca54c;
        DAT_803ca55c = DAT_803ca550;
        DAT_803ca56c = DAT_803ca560;
        DAT_803ca570 = DAT_803ca564;
        DAT_803ca574 = DAT_803ca568;
        DAT_804360d8 = 1;
        return;
      }
      (*(code *)(&PTR_FUN_802c3970)[DAT_803ca271])(&DAT_803ca260,iVar2);
      goto LAB_80010e2c;
    }
    DAT_803ca278 = DAT_803ca278 + '\x01';
    DAT_803ca27a = 0;
    DAT_803ca279 = 0;
    DAT_803ca27c = 10;
    DAT_803ca545 = *(undefined1 *)(iVar2 + 0x3e4);
    uVar1 = zz_00055fc_();
    DAT_804360db = '\0';
    DAT_803ca271 = (&DAT_802c3960)[uVar1 & 0xf];
  }
  DAT_803ca27c = DAT_803ca27c + -1;
  if (DAT_803ca27c < 1) {
    DAT_803ca278 = DAT_803ca278 + '\x01';
  }
  if (((DAT_803ca271 == -1) || (DAT_804360db == '\x01')) || ('\x02' < *(char *)(iVar2 + 0x18))) {
    DAT_804360d8 = 1;
    return;
  }
  (*(code *)(&PTR_FUN_802c3970)[DAT_803ca271])(&DAT_803ca260,iVar2);
LAB_80010e2c:
  if (DAT_804360db == '\0') {
    FUN_8000c314(-0x7fc35da0);
  }
  return;
}
