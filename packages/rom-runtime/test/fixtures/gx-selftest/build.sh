#!/usr/bin/env bash
# build.sh — rebuild the GX self-test wasm fixture with the repo's pinned emsdk
# (research/tools/emsdk), mirroring ../bridge-selftest/build.sh exactly. The
# compiled .wasm is COMMITTED so the GX smoke phase runs on a clean checkout
# without the toolchain; rerun this only when the .c changes, and commit the
# rebuilt binary with it.
#
# Windows (no bash/emsdk_env): invoke emcc.py under the bundled python:
#   research/tools/emsdk/python/3.13.3_64bit/python.exe \
#     research/tools/emsdk/upstream/emscripten/emcc.py <same args>
set -e
cd "$(dirname "$0")"
source ../../../../../research/tools/emsdk/emsdk_env.sh >/dev/null 2>&1

EXPORTS=_gx_draw_fullscreen_quad,_gx_draw_strip,_gx_draw_indexed,_gx_call_unimplemented,_gx_set_perspective

# Threads-target shape, identical to the bridge fixture: -sSHARED_MEMORY=1
# -sIMPORTED_MEMORY=1 gives threads codegen with a shared IMPORTED env.memory
# and no pthread JS runtime. 16MB fixed (max == initial) keeps the committed
# fixture cheap; the host's trampoline frame region is placed at 0x600000,
# well clear of emscripten's static data and stack.
emcc gx_selftest.c \
  -O1 -fno-strict-aliasing --no-entry \
  -sERROR_ON_UNDEFINED_SYMBOLS=0 \
  -sINITIAL_MEMORY=16777216 -sALLOW_MEMORY_GROWTH=0 \
  -sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1 \
  -sEXPORTED_FUNCTIONS=$EXPORTS \
  -o gx_selftest.threads.wasm

ls -la ./*.wasm
