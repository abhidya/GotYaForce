#!/usr/bin/env bash
# build.sh — link BOTH wasm fixtures for the audio/DVD HLE host smoke phase.
#
#   ../hle-selftest/hle_selftest.c  -> hle_selftest.threads.wasm   (leg one)
#   ./rom.c                          -> hle_rom_unit.threads.wasm   (leg two)
#
# WHAT EACH ONE IS.
#
#   LEG ONE is HAND-WRITTEN. A human chose the call sequences, modelling them
#   on the game's own file driver `zz_0274dd4_` and on `AIInit`'s register
#   order. It proves the seam carries the calls; it says nothing about the ROM.
#
#   LEG TWO is NOT hand-written. `rom.c` is the verbatim Ghidra decompilation
#   of five ROM bodies, with the rewrites listed below and nothing else:
#
#     80214634  AIInitDMA            chunk_0065.c:1227
#     802146bc  AIStartDMA           chunk_0065.c:1247
#     80214994  zz_0214994_          chunk_0065.c:1417  (real AISetStreamVolLeft)
#     802149c0  AISetStreamVolLeft   chunk_0065.c:1442  (misnamed; sets RIGHT)
#     802147ac  zz_02147ac_          chunk_0065.c:1301  (real AIGetStreamPlayState)
#     80238c90  zz_0238c90_          chunk_0069.c:2688  (the ROM's strcat)
#     802756fc  FUN_802756fc         chunk_0075.c:1     (gcCiGetFileSize)
#
# THE REWRITES, exhaustively. Anything not on this list was not done.
#
#   1. MMIO LOWERING. Each `DAT_cc0050xx` / `DAT_cc006cxx` load or store
#      statement became a GF_MMIO_R16/R32/W16/W32 call from gf_hw_mmio.h. This
#      is the audio equivalent of the write-gather-pipe lowering in
#      ../gx-rom-unit/, and the reason it is needed is identical: those
#      addresses are hardware, the module's memory is 0x807A0000 bytes, and a
#      literal access there traps.
#
#      !! UNLIKE THE GX FIXTURE, THIS LOWERING IS NOT GATE OUTPUT.
#      OGhidra's src/port_wgpipe_lowering.py covers the 0xCC008000 window and
#      only that window; nothing in the gate lowers AI or DSP registers today.
#      gf_hw_mmio.h and these rewrites are hand-applied, and the host says so
#      at runtime (the AI_MMIO_NOT_GATE_LOWERED diagnostic). Teaching the gate
#      these two windows is remainder item 1 in docs/audio-dvd-hle-host.md.
#
#   2. GHIDRA PLACEHOLDER TYPES. `undefined4`/`uint`/`ushort` are typedef'd in
#      gnt4_shim.h and the out-of-window callees are declared in gnt4_decls.h,
#      exactly as ../gx-rom-unit/gnt4_gx_decls.h does and for the same reason:
#      an implicit declaration would link every SDK import as `-> i32` and
#      disagree with the adapters' declared return classes.
#
#   3. ONE DEAD ASSIGNMENT DROPPED. `FUN_802756fc` contains
#      `uVar5 = zz_0238c90_(...)`, but `zz_0238c90_` is decompiled `void`.
#      That is a real PowerPC artifact — the caller reads r3 after a callee
#      that never set it — and `uVar5` is passed only into DVDOpen's first
#      GHOST float slot, which no adapter reads. The call is kept verbatim and
#      `uVar5 = 0;` replaces the assignment.
#
#   4. ONE SPLIT STACK VARIABLE RE-JOINED. Ghidra renders the DVDFileInfo as
#      `int aiStack_148[13]` plus a separate `uint local_114` that is really
#      the same object's +0x34 word (its `length` field — [CORPUS]
#      gnt4_DVDOpen_bl writes fileInfo+0x34). In C those would be two distinct
#      objects and DVDOpen's write would never reach `local_114`, so the array
#      is widened to a full DVDFileInfo and `local_114` becomes
#      `aiStack_148[13]`. Without this the fixture would silently return stack
#      garbage — which is precisely the kind of quiet wrongness this host
#      exists to refuse.
#
# MEMORY IS NOT A TUNING KNOB. 0x807A0000 bytes / 32890 pages is the gate's
# production arena size, and it has to be: the shim maps GameCube addresses
# STRAIGHT to linear-memory offsets, and FUN_802756fc reads 0x8040b1d0,
# 0x8040b1cc and 0x8040c178. Anything smaller traps. This is the same size
# ../gx-rom-unit/ and apps/game/public/rom/composed-rung0.threads.wasm already
# import in the browser.
#
# Both .wasm files are COMMITTED so the smoke phase runs on a clean checkout
# without emsdk. Rerun this only when a source changes, and commit the rebuilt
# binaries with it.
#
# Windows (no bash/emsdk_env), which is how these were actually built:
#   research/tools/emsdk/python/3.13.3_64bit/python.exe \
#     research/tools/emsdk/upstream/emscripten/emcc.py <same args>
set -e
cd "$(dirname "$0")"

# Fail closed: a surviving hardware-register mention means the lowering missed
# a site, and an un-lowered store traps at runtime instead of failing here.
if grep -nE 'DAT_cc(0050|006c)' rom.c; then
  echo "rom.c still mentions an AI/DSP register directly — lowering incomplete" >&2
  exit 1
fi

source ../../../../../research/tools/emsdk/emsdk_env.sh >/dev/null 2>&1

COMMON="-O1 -fno-strict-aliasing --no-entry \
  -sERROR_ON_UNDEFINED_SYMBOLS=0 \
  -sALLOW_MEMORY_GROWTH=0 -sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1"

# The ROM unit needs the gate's PRODUCTION arena (0x807A0000 bytes) because the
# shim maps GameCube addresses straight to linear-memory offsets. The
# hand-written selftest addresses nothing above 16 MiB and gets 16 MiB: two
# 2 GiB shared memories on one page is a needless demand on the browser.
emcc rom.c -include gnt4_decls.h $COMMON -sINITIAL_MEMORY=2155479040 \
  -sEXPORTED_FUNCTIONS=_AIInitDMA,_AIStartDMA,_zz_0214994_,_AISetStreamVolLeft,_zz_02147ac_,_FUN_802756fc \
  -o hle_rom_unit.threads.wasm

emcc ../hle-selftest/hle_selftest.c $COMMON -sINITIAL_MEMORY=16777216 \
  -sEXPORTED_FUNCTIONS=_hle_callback_ptr,_hle_callback_hits,_hle_callback_result,_hle_callback_block,_hle_deliver_callback,_hle_dvd_open_read_close,_hle_dvd_abs_read,_hle_dvd_call_unimplemented,_hle_audio_init,_hle_audio_set_volume,_hle_audio_play_state,_hle_audio_sample_counter,_hle_dsp_post,_hle_audio_stop,_hle_sound_mode \
  -o ../hle-selftest/hle_selftest.threads.wasm

ls -la ./*.wasm ../hle-selftest/*.wasm
