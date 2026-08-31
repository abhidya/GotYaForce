/* rom.c -- REAL ROM CODE for the audio and DVD HLE host's browser proof.
 *
 * Every function below is the verbatim Ghidra decompilation from
 * research/decomp/ghidra-export, with the rewrites listed in build.sh applied
 * and NOTHING else. Each carries its ROM address and its source location.
 */
#include "gf_hw_mmio.h"
#include "gnt4_shim.h"

/* ============================================================================
 * AUDIO -- the DAC's DMA engine, as the ROM itself drives it.
 * research/decomp/ghidra-export/chunk_0065.c
 * ==========================================================================*/

/* ==== 80214634  AIInitDMA ====                          chunk_0065.c:1227 */

void AIInitDMA(undefined4 param_1,uint param_2)

{
  ushort uVar1;

  gnt4_OSDisableInterrupts_bl();
  uVar1 = GF_MMIO_R16(0xcc005030);
  GF_MMIO_W16(0xcc005030, (uVar1 & 0xfc00 | (ushort)((uint)param_1 >> 0x10)));
  uVar1 = GF_MMIO_R16(0xcc005032);
  GF_MMIO_W16(0xcc005032, (uVar1 & 0x1f | (ushort)param_1));
  uVar1 = GF_MMIO_R16(0xcc005036);
  GF_MMIO_W16(0xcc005036, (uVar1 & 0x8000 | (ushort)(param_2 >> 5)));
  gnt4_OSRestoreInterrupts_bl(0);
  return;
}

/* ==== 802146bc  AIStartDMA ====                         chunk_0065.c:1247 */

void AIStartDMA(void)

{
  ushort uVar1;

  uVar1 = GF_MMIO_R16(0xcc005036);
  GF_MMIO_W16(0xcc005036, (uVar1 | 0x8000));
  return;
}

/* ==== 80214994  zz_0214994_ ====                        chunk_0065.c:1417
 * The REAL AISetStreamVolLeft: it writes AIVR bits 0-7. The symbol the corpus
 * calls `AISetStreamVolLeft` (0x802149c0) writes bits 8-15 and is the RIGHT
 * setter -- see AI_SYMBOL_NAME_CORRECTIONS in
 * packages/rom-runtime/src/audio/registers.ts. */

void zz_0214994_(uint param_1)

{
  uint uVar1;

  uVar1 = GF_MMIO_R32(0xcc006c04);
  GF_MMIO_W32(0xcc006c04, (param_1 & 0xff | uVar1 & 0xffffff00));
  return;
}

/* ==== 802149c0  AISetStreamVolLeft ====                 chunk_0065.c:1442
 * Misnamed in the corpus; the body writes AIVR bits 8-15, i.e. the RIGHT
 * channel. Kept under its corpus name so the fixture is greppable against the
 * export. */

void AISetStreamVolLeft(uint param_1)

{
  uint uVar1;

  uVar1 = GF_MMIO_R32(0xcc006c04);
  GF_MMIO_W32(0xcc006c04, ((param_1 & 0xff) << 8 | uVar1 & 0xffff00ff));
  return;
}

/* ==== 802147ac  zz_02147ac_ ====                        chunk_0065.c:1301
 * The REAL AIGetStreamPlayState: AICR bit 0. */

uint zz_02147ac_(void)

{
  uint uVar1;

  uVar1 = GF_MMIO_R32(0xcc006c00);
  return uVar1 & 1;
}

/* ============================================================================
 * DVD -- the game's own "how big is this file" helper, which is the shortest
 * ROM path that exercises DVDOpen's FST lookup end to end.
 * research/decomp/ghidra-export/chunk_0075.c
 * ==========================================================================*/

/* ==== 80238c90  zz_0238c90_ ====     chunk_0069.c:2688 (this is the ROM's
 * own strcat; in-window code, unlowered, unmodified). */

void zz_0238c90_(int param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;

  pcVar3 = (char *)(param_2 + -1);
  pcVar2 = (char *)(param_1 + -1);
  do {
    pcVar4 = pcVar2;
    pcVar2 = pcVar4 + 1;
  } while (pcVar4[1] != '\0');
  do {
    pcVar3 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar4 = pcVar4 + 1;
    *pcVar4 = cVar1;
  } while (cVar1 != '\0');
  return;
}

/* ==== 802756fc  FUN_802756fc ====                       chunk_0075.c:1
 * The error strings name it: gcCiGetFileSize. It builds a path from the base
 * directory the game set at 0x8040c178, opens it, reads the DVDFileInfo's
 * length word at +0x34 (= aiStack_148[13]), closes, and returns the size. */

uint FUN_802756fc(uint param_1,uint param_2,uint param_3,uint param_4,
                 uint param_5,uint param_6,uint param_7,uint param_8,
                 int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  size_t sVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  int aiStack_148 [16];              /* [rewrite 4] see build.sh */
  char local_10c [260];

  if (param_9 == 0) {
    if (DAT_8040b1d0 != (void (*)(int, const char *, int))0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092901_fname_is_null__gcCiGetF_802b77ec,0);
    }
    uVar1 = 0;
  }
  else {
    strcpy(local_10c,&DAT_8040c178);
    zz_0238c90_((int)local_10c,param_9);
    uVar5 = 0;                                  /* [rewrite 3] see build.sh */
    sVar2 = strlen(local_10c);
    pcVar4 = local_10c;
    for (; sVar2 != 0; sVar2 = sVar2 - 1) {
      if (*pcVar4 == '\\') {
        *pcVar4 = '/';
      }
      pcVar4 = pcVar4 + 1;
    }
    iVar3 = gnt4_DVDOpen_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_10c,
                            (int)aiStack_148,param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar3 == 0) {
      if (DAT_8040b1d0 != (void (*)(int, const char *, int))0x0) {
        (*DAT_8040b1d0)(DAT_8040b1cc,s_E0040201_can_t_open_a_file__gcCi_802b7818,0);
      }
      uVar1 = 0;
    }
    else {
      uVar1 = aiStack_148[13];            /* [rewrite 4] */
      if (((uint)aiStack_148[13] & 0x80000000) != 0) {
        uVar1 = 0x7fffffff;
      }
      iVar3 = gnt4_DVDClose_bl(aiStack_148);
      if (iVar3 == 0) {
        if (DAT_8040b1d0 != (void (*)(int, const char *, int))0x0) {
          (*DAT_8040b1d0)(DAT_8040b1cc,s_E0040202_can_t_close_a_file__gcC_802b7848,0);
        }
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}
