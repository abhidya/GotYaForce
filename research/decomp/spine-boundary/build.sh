#!/usr/bin/env bash
# build.sh — the boundary_green verification build of the ROM spine
# `run_main_game_loop` (0x800527d8 / export `zz_00527d8_`).
#
# WHAT THIS IS
#   A SINGLE-FUNCTION wasm module: unit.c is `#include "gnt4_shim.h"` plus the
#   VERBATIM chunk_0006.c:5790-5833 extraction and nothing else. Every function
#   the spine calls therefore leaves the module as an `env` import, which is
#   what boundary_green needs — the harness stubs each callee with its captured
#   boundary (docs/playable-port-design.md V5, amendment I3).
#
# WHAT THIS IS NOT
#   It is NOT the fleet unit. The queue's unit for this address is
#   `auto-c0006-013` (research/decomp/generated/finish-game-port/wasm-units.json,
#   queue index 129), which bundles the spine with 7 siblings — including
#   `zz_0052838_`, one of the spine's own 17 loop callees. In that module the
#   call is INTERNAL and the harness would never see it, so auto-c0006-013 can
#   never be a boundary_green target. As of this build auto-c0006-013 is not
#   staged (no research/decomp/port-units-staging/auto-c0006-013), it is
#   `compile_only` tier, and no c0006 unit is staged at all.
#
#   This build is therefore a PREFLIGHT in the sense of
#   research/decomp/corpus-correction-loop.md §2 — the driver's exact emcc
#   invocation, run outside the driver, producing an artifact that is evidence
#   and never a staged/promoted unit. It touches no driver state, takes no
#   driver lock, and writes nothing under port-units/ or port-units-staging/.
#
# FLAGS: byte-identical to `emcc_build_unit` in the driver
# (research/tools/OGhidra/src/port_wasm_units.py), except for the export list.
set -e
cd "$(dirname "$0")"
# emsdk is untracked and lives in the MAIN checkout only, so a git worktree has
# no ../../tools/emsdk. Fall back to the main checkout (git-common-dir's parent)
# so this evidence build is reproducible from a worktree with identical flags.
EMSDK_ENV=../../tools/emsdk/emsdk_env.sh
if [ ! -f "$EMSDK_ENV" ]; then
  EMSDK_ENV="$(dirname "$(git rev-parse --path-format=absolute --git-common-dir)")/research/tools/emsdk/emsdk_env.sh"
fi
source "$EMSDK_ENV" >/dev/null 2>&1

emcc unit.c -O1 -fno-strict-aliasing --no-entry \
  -Wno-implicit-function-declaration -Wno-int-conversion \
  -Wno-deprecated-non-prototype \
  -Wno-incompatible-pointer-types -Wno-pointer-sign \
  -ferror-limit=0 \
  -sERROR_ON_UNDEFINED_SYMBOLS=0 -sINITIAL_MEMORY=2155479040 \
  -sALLOW_MEMORY_GROWTH=0 \
  -sEXPORTED_FUNCTIONS=_zz_00527d8_ \
  -o unit.wasm

ls -la unit.wasm
