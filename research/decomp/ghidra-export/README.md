# Ghidra bulk-decompile export — the "source of truth" corpus

Generated 2026-07-01 via a Ghidra script (`DumpAllDecompiledJ.java`, run from inside the
`GotchaForce` Ghidra project against `user-data/GG4E/disc/sys/boot.dol`, using the community
`GG4E-CSM-20220412.map` symbol map). This is a full-coverage decompiled-C snapshot of **every**
function Ghidra found in the binary — not byte-matched against a compiler (that would need the
proprietary Metrowerks CodeWarrior toolchain, out of scope — see `research/tools/re-tooling-guide.md`),
but a real decompiler pass over the whole program, persisted to disk so future questions about
"what does the ROM actually do here" are a grep, not a new live-debugging or manual-Ghidra-click
session.

## Contents

- `_index.tsv` — one row per function: `address<TAB>name<TAB>chunk_file`. 11,972 functions total.
- `chunk_NNNN.c` — 80 files, ~150 functions each, each function preceded by a
  `// ==== <address>  <name> ====` header. Decompiled with Ghidra's default decompiler settings
  (30s timeout per function); a small number of functions may show `// DECOMPILE FAILED` or
  `// EXCEPTION` instead of code (pathological/huge functions, or ones Ghidra's decompiler
  couldn't resolve stack layout for) — rerun `DumpAllDecompiledJ.java` after manually fixing
  those specific functions in the GUI if they matter later.

## How to use it

Find a function by name or address:
```
grep -n "zz_003d344_" _index.tsv          # -> chunk file it lives in
grep -n "^8003d344" _index.tsv            # same, by address
```
Then pull its body out of that chunk (each function is delimited by its own `// ==== ... ====`
header and a blank line before the next one):
```
awk '/\/\/ ==== 8003d344  zz_003d344_ ====/{f=1} f{print} /\/\/ ==== 8003/{if(f && !/8003d344/)exit}' chunk_0000.c
```
Function names follow the community `GG4E-CSM-20220412.map` where it had a real symbol
(`gnt4_*`, `PSVEC*`, etc. — many of the underlying math/HSD-engine functions are shared with
other HAL/AM2-lineage titles, hence the borrowed GNT4 map covering them at all); everything else
is Ghidra's auto-generated `zz_<addr>_`/`FUN_<addr>` fallback name.

## What's been cross-referenced against the TS port so far (2026-07-01)

All addresses below are cited in `research/decomp/behavior-notes.md` sections (h)/(i)/(j)/(k)
with the reasoning; this is just the quick index:

| Address | Name | What it does | TS port location |
|---|---|---|---|
| `0x8003d344` | `zz_003d344_` | HP subtract-and-clamp, "linked object" HP mirror, isDead via countLeadingZeros | `packages/combat/src/combat.ts` applyHit()/mitigate() |
| `0x8002e2a8` | `zz_002e2a8_` | Per-borg update; contains an `object+0x88` mismatch branch and `+0x42c` damage accumulator. Later export review shows `+0x88` is match slot/team state, not `borgs.json.type` | `constants.ts` documents DAMAGE.TYPE_MISMATCH_DIVISOR; not wired from display type |
| `0x8003cd5c` | `zz_003cd5c_` | Real base-damage formula: base-power float, HP-ratio-based scaling (0x1c4 field), an elemental category+index table lookup (via `zz_0066298_`) keyed off a 2-byte field at `object+1000`, and further sub-object-gated multipliers | Not yet ported — `MELEE.DMG_BASE`/`DMG_PER_STAT`/`SHOT.*` remain the TUNED linear stand-in |
| `0x80066298` | `zz_0066298_` | `return table[param_1[0]][param_1[1]]` — a real 2D short lookup table (category row, index column), the actual subtle type/category mechanic keyed through `object+1000`; **not** the same field as the `+0x88` slot/team byte | Not ported — no TS equivalent exists yet |
| `0x800300bc` | `zz_00300bc_` | Computes a launch/knockback *direction* (yaw/pitch as shorts) from one of 5 vector-source modes selected by a mode parameter (relative position, camera-relative, "linked object" position, etc.) — NOT a magnitude/hitstun value as originally guessed | Not ported — `MELEE.KNOCKBACK`/`HITSTUN` etc. remain TUNED flat constants; the real game computes knockback as a full 3D direction, not a flat scalar |

## Honest scope note

This corpus covers the whole binary (SDK/OS/math library internals included), so most of its
11,972 entries are irrelevant to gameplay porting (DVD/OS calls, GX graphics primitives, libc).
The valuable move going forward is targeted grepping — pull the specific systems relevant to
whatever's being fixed (UI/HUD, a specific mechanic, map/stage data, asset IDs) out of this
corpus, rather than trying to "read all of it." Treat this as a searchable reference library, not
required reading.
