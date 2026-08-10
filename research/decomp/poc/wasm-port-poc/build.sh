#!/usr/bin/env bash
# POC build — HANDOFF-2026-08-09 §5. Unit bodies are verbatim sed-extractions from the
# Ghidra export (provably untouched); only the prelude/header are scaffold-generated.
set -euo pipefail
cd "$(dirname "$0")"
GE=../../ghidra-export

{
  echo '#include "gnt4_shim.h"'
  echo
  echo '/* stage-2 generated prototypes (design: prototypes for all functions from _index.tsv) */'
  echo 'int zz_003cd5c_(ushort *param_1,int param_2,char *param_3);'
  echo 'uint zz_003d344_(int param_1,short param_2);'
  echo 'int zz_0066298_(char *param_1);'
  echo 'bool FUN_80031634(int param_1,int param_2,float *param_3,int *param_4);'
  echo
  echo '/* ==== VERBATIM: chunk_0004.c 6667-6828 (zz_003cd5c_ damage formula) ==== */'
  sed -n '6667,6828p' "$GE/chunk_0004.c"
  echo '/* ==== VERBATIM: chunk_0004.c 6832-6860 (zz_003d344_ hp subtract+clamp) ==== */'
  sed -n '6832,6860p' "$GE/chunk_0004.c"
  echo '/* ==== VERBATIM: chunk_0008.c 2976-2982 (zz_0066298_ type category) ==== */'
  sed -n '2976,2982p' "$GE/chunk_0008.c"
  echo '/* ==== VERBATIM: chunk_0004.c 197-231 (FUN_80031634 — Unit B, SDK seam) ==== */'
  sed -n '197,231p' "$GE/chunk_0004.c"
} > unit_poc.c

source ../../../tools/emsdk/emsdk_env.sh >/dev/null 2>&1

# INITIAL_MEMORY = 0x80710000 (32881 wasm pages): covers all GC data/bss addresses
# plus the harness scratch objects at 0x8060xxxx. Arena addresses ARE the original
# GameCube addresses ("one memory arena at original addresses").
emcc unit_poc.c -O1 -fno-strict-aliasing --no-entry \
  -Wno-implicit-function-declaration -Wno-int-conversion \
  -sERROR_ON_UNDEFINED_SYMBOLS=0 \
  -sINITIAL_MEMORY=2155479040 -sALLOW_MEMORY_GROWTH=0 \
  -sEXPORTED_FUNCTIONS=_zz_003cd5c_,_zz_003d344_,_zz_0066298_,_FUN_80031634 \
  -o unit_poc.wasm
ls -la unit_poc.wasm
