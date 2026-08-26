#!/usr/bin/env bash
# build.sh — rebuild the bridge self-test wasm fixture with the repo's pinned
# emsdk (research/tools/emsdk), mirroring the spine-synth fixture's compile
# method (research/decomp/oracle-harness/tests/fixtures/spine-synth/build.sh).
# The compiled .wasm is COMMITTED so the rom-runtime smoke phase runs on a
# clean checkout without the toolchain; rerun this only when the .c changes,
# and commit the rebuilt binary with it.
#
# Windows (no bash/emsdk_env): invoke emcc.py under the bundled python:
#   research/tools/emsdk/python/3.13.3_64bit/python.exe \
#     research/tools/emsdk/upstream/emscripten/emcc.py <same args>
set -e
cd "$(dirname "$0")"
source ../../../../../research/tools/emsdk/emsdk_env.sh >/dev/null 2>&1

EXPORTS=_selftest_roundtrip,_reentry_target,_selftest_reentrant,_overflow_probe,_selftest_async,_selftest_tracedelta,_selftest_apply_hp,_selftest_lookup_type,_selftest_i64ret,_selftest_retclass,_selftest_noadapter

# Threads-target shape (the step-8/step-9 shape): -sSHARED_MEMORY=1
# -sIMPORTED_MEMORY=1 gives threads codegen with a shared IMPORTED env.memory
# and no pthread JS runtime. 16MB fixed (max == initial) keeps the committed
# fixture cheap; the synthetic arena lives around 0x104000-0x1055ff.
emcc bridge_selftest.c \
  -O1 -fno-strict-aliasing --no-entry \
  -sERROR_ON_UNDEFINED_SYMBOLS=0 \
  -sINITIAL_MEMORY=16777216 -sALLOW_MEMORY_GROWTH=0 \
  -sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1 \
  -sEXPORTED_FUNCTIONS=$EXPORTS \
  -o bridge_selftest.threads.wasm

ls -la ./*.wasm
