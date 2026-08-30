#!/usr/bin/env bash
# build.sh — link the GATE-LOWERED REAL ROM DRAW UNIT for the browser leg.
#
# WHAT THIS FIXTURE IS, and how it differs from ../gx-selftest/.
#
#   ../gx-selftest/gx_selftest.c is HAND-WRITTEN: it reproduces the ROM's draw
#   paths call for call, but a human typed it. This one is not. `rom.c` here is
#   the assembly gate's own output for the ROM's own function `zz_0027c34_`
#   (0x80027c34, decompiled at research/decomp/ghidra-export/chunk_0003.c
#   :3285-3328) — the verbatim Ghidra decompilation with EXACTLY ONE class of
#   rewrite applied: each `DAT_cc008000 = ...` store to the memory-mapped
#   write-gather pipe became a GF_WGPIPE_W16 / GF_WGPIPE_W32 macro call, which
#   `gf_gx_wgpipe.h` (also gate-generated, also unedited) routes to the four
#   `__gf_gx_wgpipe_*` imports the host's FIFO decoder services. Every GX call,
#   every constant, every branch is the ROM's.
#
# PROVENANCE of the three sources in this directory. They were produced by
# OGhidra's assembly gate with the lowering enabled:
#
#     OGHIDRA_PORT_WGPIPE_LOWERING=1
#     research/tools/OGhidra/src/port_wgpipe_lowering.py  (lower_source/lower_window)
#     research/tools/OGhidra/src/port_assembly_gate.py    (_emit_wgpipe_lowering)
#
# and captured on 2026-08-29 from that gate run's window output. The lowering
# is OPT-IN and OFF by default, and it FAILS CLOSED: any surviving mention of
# the 0xCC008000..0xCC008020 window is a `wgpipe_unlowerable_site` refusal, so
# a source that reaches this directory has no un-lowered pipe stores left in
# it. To regenerate rather than trust the copy, re-run that gate window; the
# hermetic pytest pilot
# research/tools/OGhidra/tests/test_port_wgpipe_lowering.py
#   ::test_pilot_the_roms_own_draw_function_submits_a_real_quad
# builds the same thing from scratch and asserts the 12 stores and their
# widths.
#
# WHY WE RELINK RATHER THAN COMMIT THE GATE'S OWN .wasm. The gate links for the
# node proof, which wants a module that EXPORTS its memory. The browser runtime
# needs the threads shape — a SHARED, IMPORTED `env.memory` — because the
# worker owns the memory and the main thread services bridged calls against it
# (design H1/H2). That is a link-time flag difference only; the object code is
# the same lowered source.
#
# MEMORY IS NOT A TUNING KNOB. 0x807A0000 bytes / 32890 pages is the gate's
# production arena size, and it has to be: the shim maps GameCube addresses
# STRAIGHT to linear-memory offsets (`GC_IPTR(a) (*(int*)(unsigned int)(a))`),
# and this function reads 0x80433930, 0x80436108, 0x8043610c and 0x803c0f40.
# Anything smaller traps. apps/game/public/rom/composed-rung0.threads.wasm
# already imports a shared memory of exactly this size and runs in the browser
# smoke route today, so this is not a new demand on the browser.
#
# The compiled .wasm is COMMITTED so the GX smoke phase runs on a clean
# checkout without emsdk. Rerun this only when a source changes, and commit the
# rebuilt binary with it.
#
# Windows (no bash/emsdk_env): invoke emcc.py under the bundled python:
#   research/tools/emsdk/python/3.13.3_64bit/python.exe \
#     research/tools/emsdk/upstream/emscripten/emcc.py <same args>
set -e
cd "$(dirname "$0")"
source ../../../../../research/tools/emsdk/emsdk_env.sh >/dev/null 2>&1

emcc rom.c \
  -include gnt4_gx_decls.h \
  -O1 -fno-strict-aliasing --no-entry \
  -sERROR_ON_UNDEFINED_SYMBOLS=0 \
  -sINITIAL_MEMORY=2155479040 -sALLOW_MEMORY_GROWTH=0 \
  -sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1 \
  -sEXPORTED_FUNCTIONS=_zz_0027c34_ \
  -o gx_rom_unit.threads.wasm

ls -la ./*.wasm
