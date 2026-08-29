/* gnt4_shim.h — boundary_green scaffold for the ROM spine `run_main_game_loop`
 * (0x800527d8, exported as zz_00527d8_).
 *
 * SCOPE: this header supports a SINGLE-FUNCTION module (unit.c = the verbatim
 * chunk_0006.c:5790-5833 extraction and nothing else). That is deliberate and
 * is what the boundary_green standard requires (docs/playable-port-design.md
 * V5 I3): every function the spine calls must leave the module as a wasm
 * import so the harness can stub it with the captured boundary. The eventual
 * FLEET unit auto-c0006-013 bundles the spine with 7 siblings — including
 * zz_0052838_, which the spine calls — and therefore CANNOT be used for
 * boundary_green: that call would be an internal call the harness never sees.
 *
 * Conventions copied verbatim from the staged units' generated shim
 * (research/decomp/port-units-staging/auto-c0001-003/gnt4_shim.h): Ghidra
 * undefinedN typedefs, and DAT_ globals as macros dereferencing the ORIGINAL
 * GameCube address inside the wasm arena.
 */
#ifndef GNT4_SHIM_H
#define GNT4_SHIM_H

#include <stdbool.h>   /* Ghidra emits `true` for the do{}while(true) back edge */

typedef unsigned char       undefined;
typedef unsigned char       undefined1;
typedef unsigned short      undefined2;
typedef unsigned int        undefined4;
typedef unsigned long long  undefined8;   /* an INTEGER, never double */
typedef unsigned char       byte;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;
typedef unsigned long long  ulonglong;
typedef long long           longlong;

#define GC_IPTR(a) (*(int *)(unsigned int)(a))

/* The spine's ONE owned write: `DAT_80436190 = zz_008dbe0_();`
 * (PPC `stw r3, -0x5410(r13)` at 0x80052804 — r13 = 0x8043b5a0). */
#define DAT_80436190 GC_IPTR(0x80436190)

/* Every callee is left UNDECLARED on purpose. Under the driver's production
 * emcc flags (-Wno-implicit-function-declaration) each becomes a wasm import
 * whose signature is induced by the verbatim call site — which is exactly the
 * ABI the boundary capture must bind to. Declaring them here would let a
 * hand-written prototype, rather than the ROM-derived C, decide the boundary. */

#endif /* GNT4_SHIM_H */
