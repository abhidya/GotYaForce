The user wants me to fix `gnt4_shim.h` so that the provided C code compiles with emscripten (clang, wasm32).
The compiler error says: `ABS` is undefined and became a wasm import, but it's not an SDK function. It must be defined in `gnt4_shim.h` with correct PowerPC semantics.

Looking at the C code:
```c
  dVar4 = (double)(float)ABS(dVar3);
// ...
  dVar2 = (double)(float)ABS(dVar3);
```
`ABS` is used on `dVar3`, which is a `double`. Wait, in the C code:
`dVar3` is `double`.
`ABS(dVar3)` is called. In Ghidra decompiler output, `ABS` usually maps to the absolute value function. For floats/doubles, it's often `fabs` or just a macro for `fabs`. Since it's used on a `double`, it should be `fabs` or a custom macro that handles doubles.
Actually, Ghidra's `ABS` is typically defined as:
```c
#define ABS(x) ((x) < 0 ? -(x) : (x))
```
or just `fabs`. But to be safe and match PPC semantics exactly without relying on `<math.h>` if not included, I can define it as a macro or inline function.
Wait, the C code uses `ABS(dVar3)` where `dVar3` is `double`.
Let's check standard Ghidra decompiler output for `ABS`. It's often just `ABS`. I will define it as:
```c
#define ABS(x) ((x) < 0 ? -(x) : (x))
```
But wait, `dVar3` is a double. The macro works for any numeric type.
Alternatively, `fabs` from `<math.h>` could be used, but defining a macro is safer and matches Ghidra's typical style. I'll include `<math.h>` just in case, or just define `ABS`.

Let's look at the exact error: `ABS` is undefined.
I will add `#define ABS(x) ((x) < 0 ? -(x) : (x))` to `gnt4_shim.h`.

Wait, is there anything else? The prompt says "these symbols are UNDEFINED ... ABS". That's the only one mentioned.
Let's verify other macros in `gnt4_shim.h`.
`CONCAT44` is defined.
`countLeadingZeros` is defined.
`GC_F32`, etc. are defined.
`PTR_DAT_804335e0`, etc. are defined.
The code uses `ABS(dVar3)`.

I will add:
```c
#include <math.h>
#define ABS(x) ((x) < 0 ? -(x) : (x))
```
Actually, Ghidra's `ABS` is often just a macro. I'll stick to the macro. It's simple and works for doubles.

Wait, let's check if `ABS` in Ghidra sometimes refers to `fabs`. Yes, but the macro covers it.
I'll add `#define ABS(x) ((x) < 0 ? -(x) : (x))` near the top or with other helpers.

Let's double check the C code for any other potential issues.
`local_30 = (double)CONCAT44(0x43300000,(uint)*param_1);` -> `CONCAT44` is defined.
`fVar1 = (float)(local_30 - DOUBLE_80436fb0);` -> `DOUBLE_80436fb0` is defined.
`uVar3 = (uint)(-(int)cVar2 | (int)cVar2) >> 0x1d & 4;` -> standard bitwise.
`iVar5 = (int)(uVar9 << 5) / 200 + ((int)(uVar9 << 5 | uVar9 >> 0x1b) >> 0x1f);` -> standard.
`countLeadingZeros((int)*(short *)(param_1 + 0x1c6));` -> defined.
`ABS(dVar3)` -> needs definition.

Is there any other missing symbol? The error message only mentions `ABS`.
I will add `#define ABS(x) ((x) < 0 ? -(x) : (x))` to the header.

Wait, `dVar3` is a `double`. The macro `(x) < 0 ? -(x) : (x)` works correctly for doubles in C.
I'll also include `<math.h>` just in case other math functions are needed, but it's not strictly necessary. I'll stick to the macro.

Let's review the header carefully.
```c
/* gnt4_shim.h — POC stage-2 "header + arena" scaffold (HANDOFF-2026-08-09 §4).
...
*/
#ifndef GNT4_SHIM_H
#define GNT4_SHIM_H

#include <stdbool.h>

typedef unsigned char undefined;
...
```
I will add `#define ABS(x) ((x) < 0 ? -(x) : (x))` right after the typedefs or with `CONCAT44`.

One minor thing: `ABS` in Ghidra decompiler output for floats/doubles is sometimes just `fabs`. But defining it as a macro is fine. I'll use `#define ABS(x) ((x) < 0 ? -(x) : (x))`.

Wait, the prompt says: "Ghidra decompiler helper idioms like CONCAT44 must behave exactly as the original PPC code did."
PPC `fabs` or absolute value of a double is just clearing the sign bit. The macro does that correctly in IEEE 754 floating point.

Let's check if there's any other issue.
The code uses `PTR_DAT_804335e0`, `PTR_PTR_804335e8`, etc. They are defined as `GC_PTR(...)`.
`GC_PTR(a)` is `(*(char **)(unsigned int)(a))`. That's fine.
`DAT_803b069c` is `GC_S16(0x803b069c)`. Used as `(&DAT_803b069c)[pcVar13[0x3e4]]`. Wait, `&DAT_803b069c` would be the address of the macro expansion? That's a bit weird but macros expand before taking address. Actually, `(&GC_S16(0x803b069c))[...]` expands to `(&(*(short *)(unsigned int)(0x803b069c)))[...]`. The address of a dereferenced pointer is just the pointer itself (as a `short *`). So `(&DAT_803b069c)` becomes `(short *)0x803b069c`. That works.

Wait, `PTR_DAT_804335e0` is used as:
`*(float *)(*(int *)((int)&PTR_DAT_804335e0 + uVar3) + (char)PTR_DAT_80433950[iVar4] * 4))`
`(int)&PTR_DAT_804335e0` -> `(int)&(*(char **)(unsigned int)(0x804335e0))`. This is valid C.

Everything else looks fine. The only missing symbol is `ABS`.

I will add:
```c
/* Ghidra decompiler ABS macro (works for int/float/double) */
#define ABS(x) ((x) < 0 ? -(x) : (x))
```

Let's verify the exact compiler error again:
`link gate: these symbols are UNDEFINED and became wasm imports, but they are not gnt4_* SDK functions, so they must be DEFINED in gnt4_shim.h with correct PowerPC semantics: ABS`

So just defining `ABS` is sufficient.

I will produce the complete corrected `gnt4_shim.h`.

One detail: `#include <math.h>` might be good practice, but not strictly required if I define `ABS`. I'll stick to the macro to avoid linking issues with emscripten if `<math.h>` isn't handled correctly in this pipeline, though it usually is. The macro is safer.

Let's assemble the header.

```c
/* gnt4_shim.h — POC stage-2 "header + arena" scaffold (HANDOFF-2026-08-09 §4).
 *
 * Deterministically generated support header. The ported .c bodies are verbatim
 * sed-extractions from research/decomp/ghidra-export/ (see build.sh) — this header
 * supplies only what Ghidra's decompiler assumes exists:
 *   - typedefs for Ghidra's undefinedN types
 *   - the DAT_/FLOAT_/DOUBLE_/PTR_ globals as macros that dereference the ORIGINAL
 *     GameCube addresses inside wasm linear memory (the "one memory arena at original
 *     addresses" from the design). gen_arena.py populates those addresses from boot.dol
 *     with byte-order converted at generation time (design §4 endianness rule).
 *   - CONCAT44: in every use inside these units it is the PPC int->double bit trick
 *     (0x43300000 magic + subtract 2^52); the (double) cast in Ghidra output denotes
 *     REINTERPRETATION, so it is defined as a union bit-cast, not a value conversion.
 *   - countLeadingZeros: PPC cntlzw semantics (cntlzw(0) == 32; __builtin_clz(0) is UB).
 *   - ABS: Ghidra decompiler absolute-value macro (IEEE 754 sign-bit clear).
 *   - SDK functions (gnt4_PS*) are left as extern declarations -> wasm env imports,
 *     provided by the TS/JS shim layer (design stage 1: SDK is never ported).
 */
#ifndef GNT4_SHIM_H
#define GNT4_SHIM_H

#include <stdbool.h>

typedef unsigned char undefined;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;

/* In these units undefined8 is only ever used as a double (the CONCAT44 fp trick). */
typedef double undefined8;

/* CONCAT44: PPC big-endian bit concatenation. On wasm (LE), we swap array order
 * to preserve the original 64-bit pattern when reinterpreted as double. */
typedef union { uint u[2]; double d; } _concat44_u;
#define CONCAT44(hi, lo) ((_concat44_u){.u = {(lo), (hi)}}).d

/* countLeadingZeros: PPC cntlzw semantics (cntlzw(0) == 32; __builtin_clz(0) is UB). */
static inline uint countLeadingZeros(int x) {
    return x == 0 ? 32 : __builtin_clz((uint)x);
}

/* Ghidra decompiler ABS macro (works for int/float/double, matches PPC fabs semantics) */
#define ABS(x) ((x) < 0 ? -(x) : (x))

/* ---- arena globals: original GC addresses inside wasm linear memory ---- */
#define GC_F32(a)  (*(float *)(unsigned int)(a))
#define GC_F64(a)  (*(double *)(unsigned int)(a))
#define GC_U8(a)   (*(unsigned char *)(unsigned int)(a))
#define GC_S16(a)  (*(short *)(unsigned int)(a))
#define GC_PTR(a)  (*(char **)(unsigned int)(a))
#define GC_IPTR(a) (*(int *)(unsigned int)(a))

/* constants (sec12 .sdata2, DOL-initialized; values verified vs boot.dol) */
#define FLOAT_80436f68  GC_F32(0x80436f68)  /* 0.0  formula gate            */
#define FLOAT_80436f78  GC_F32(0x80436f78)  /* 1.0                          */
#define FLOAT_80436f7c  GC_F32(0x80436f7c)  /* 0.5                          */
#define FLOAT_80436f9c  GC_F32(0x80436f9c)  /* 2.0  attacker pair bonus     */
#define FLOAT_80437024  GC_F32(0x80437024)  /* 0.25 same-team divisor       */
#define FLOAT_80437028  GC_F32(0x80437028)  /* 40.0 guard divisor           */
#define DOUBLE_80436fb0 GC_F64(0x80436fb0)  /* 2^52   uint->double magic    */
#define DOUBLE_80436f88 GC_F64(0x80436f88)  /* 2^52+2^31 int->double magic  */

/* damage-table pointer slots (sec11 .data, DOL-initialized) */
#define PTR_DAT_804335e0 GC_PTR(0x804335e0)
#define PTR_PTR_804335e8 GC_PTR(0x804335e8)
#define PTR_PTR_804335f0 GC_PTR(0x804335f0)
#define PTR_DAT_804335f8 GC_PTR(0x804335f8)
#define PTR_PTR_80433600 GC_PTR(0x80433600)
#define PTR_PTR_80433608 GC_PTR(0x80433608)
#define PTR_PTR_80433610 GC_PTR(0x80433610)
#define PTR_DAT_80433618 GC_PTR(0x80433618)

/* runtime-struct pointers (DOL-initialized to fixed bss structs) */
#define PTR_DAT_80433930 GC_PTR(0x80433930)  /* -> 0x803c6ce0; [0x32] = challenge mode  */
#define PTR_DAT_80433934 GC_PTR(0x80433934)  /* -> 0x803c5420; [team*0x3c+0x114] = energy max */
#define PTR_DAT_80433950 GC_PTR(0x80433950)  /* -> 0x803c4e60; [team] = side-rank byte  */
#define PTR_DAT_80433954 GC_PTR(0x80433954)
#define DAT_8043625c     GC_IPTR(0x8043625c)

/* bss live-state arrays (harness-written per test case) */
#define DAT_803b069c GC_S16(0x803b069c)   /* s16 HP mirror, indexed by slot byte +0x3e4 */
#define DAT_803b068c GC_IPTR(0x803b068c)  /* int side energy, indexed by team byte +0x88 */

/* type-category remap (sec10 .data): (&PTR_DAT_802f2e28)[family] -> s16 row */
#define PTR_DAT_802f2e28 GC_IPTR(0x802f2e28)

/* combo-rank falloff table base (byte-addressed in source: &DAT + rank*4) */
#define DAT_802c7ca0 GC_U8(0x802c7ca0)

/* Unit B (FUN_80031634) data */
#define DAT_802cffc8 GC_U8(0x802cffc8)    /* char table, DOL-initialized, indexed *4 */
#define DAT_803b0720 GC_F32(0x803b0720)   /* bss vec3 out (x; +4 y; +8 z) */

/* ---- SDK seam (design stage 1): never ported, resolved as wasm env imports ---- */
extern void   gnt4_PSVECSubtract_bl(float *a, float *b, float *out);
extern void   gnt4_PSVECAdd_bl(float *a, float *b, float *out);
extern double gnt4_PSQUATDotProduct_bl(float *a, float *b);
extern void   gnt4_PSQUATScale_bl(double s, float *v, float *out);

#endif /* GNT4_SHIM_H */
```

Wait, let's verify `ABS` usage in the code:
`dVar4 = (double)(float)ABS(dVar3);`
`dVar2 = (double)(float)ABS(dVar3);`
`dVar3` is a `double`. The macro `(x) < 0 ? -(x) : (x)` works perfectly for doubles.

Is there any chance `ABS` in Ghidra refers to `fabs` from `<math.h>`? Yes, but the macro is standard and avoids linking issues. I'll keep it as a macro.

One minor point: `#include <math.h>` might be needed if `fabs` is expected, but the prompt says "Ghidra decompiler helper idioms like CONCAT44 must behave exactly as the original PPC code did." Defining `ABS` as a macro is fine. I'll add `#include <math.h>` just to be safe, or leave it out. It doesn't hurt to include it, but the macro covers it. I'll stick to the macro only to keep it minimal and self-contained.

Actually, in C, `(x) < 0 ? -(x) : (x)` for floating point is perfectly valid and matches `fabs`.

Let's double check the exact error message: "link gate: these symbols are UNDEFINED and became wasm imports, but they are not gnt4_* SDK functions, so they must be DEFINED in gnt4_shim.h with correct PowerPC semantics: ABS"
This confirms `ABS` was treated as an external function by the compiler because it wasn't defined. Defining it as a macro will solve it.

I will output the complete corrected header.
One thing: `PTR_DAT_804335e0` etc. are used with `(int)&PTR_DAT_804335e0`. Since `PTR_DAT_804335e0` is a macro expanding to `(*(char **)(unsigned int)(0x804335e0))`, taking its address `&(...)` is valid.
All good.

Final check of the header content matches the request. I will produce it now.
I'll make sure formatting is exact.
No extra text.
Ready. 
One minor adjustment: I'll add `#include <math.h>` just in case, but it's not strictly necessary. I'll skip it to keep it clean, as the macro handles it. Actually, including `<math.h>` is standard C. I'll leave it out unless needed. The macro is safer for wasm32-emscripten if they restrict math lib linking. I'll stick to the macro.

Wait, `ABS` might be a function in some Ghidra outputs? No, it's typically a macro or inline. Defining it as a macro is standard practice for Ghidra ports.

I will generate the response now. 
All steps verified. Output matches request.
Proceeds. 
Output generation. 
```c
/* gnt4_shim.h — POC stage-2 "header + arena" scaffold (HANDOFF-2026-08-09 §4).
...
*/
```
Matches exactly.
Done. 
Self-Correction/Refinement during thought: 
Should I define `ABS` as a static inline function to avoid macro pitfalls? The code uses it on doubles. A macro is fine. Ghidra's decompiler usually outputs `ABS` as a macro or expects the user to provide it. I'll stick with the macro. It's concise and correct.

One detail: `dVar3` is `double`. `(x) < 0 ? -(x) : (x)` works for doubles.
I'll output the header exactly as constructed.
All good. 
Proceeds. 
[Output Generation] -> *Produces the corrected header*
