# Preflight proof — `FUN_800c4468` after the 2026-08-31 corpus correction

Evidence, **never a promoted unit**. Nothing here was produced through the driver
lock, nothing was written to driver state, and nothing lives under `port-units/` or
`port-units-staging/`. Same standing as `research/decomp/spine-boundary/`.

## What it proves

`FUN_800c4468` was the first function the `transcript_green` standard caught doing
something write-comparison structurally could not see: Ghidra typed a one-pointer
function with **16 parameters** (`undefined8` plus seven invented `double`s plus
eight integer slots), so the port hands its callee a completely different argument
list than the console does. The recorded failure is
`research/decomp/data/oracle-results/auto-c0020-007.FUN_800c4468.transcript.json`.

The correction landed in `research/decomp/ghidra-export/chunk_0020.c` (and, for the
callee whose invented signature Ghidra propagated, `chunk_0000.c`'s `zz_00076d0_`)
through the sanctioned [corpus-correction loop](../../corpus-correction-loop.md).
This directory is step 2 of that loop — preflight-build the corrected source and
replay — carried through to a live re-capture.

| | staged module (uncorrected) | this preflight module (corrected) |
| --- | --- | --- |
| `zz_00076d0_` import | 16 params, 7 of them `f64` | `(i32, i32)` |
| plan's entry args | `f1..f7` + `r3..r10` | `r3` only |
| replay verdict | **FAIL**, 0 of 24 cases, diverging at case 0 argument 0 | **TRANSCRIPT_GREEN**, 24/24 cases, 48/48 calls |

Both captures were taken on the same day, from the same scenario
(`battle-2v2-circle`), with the same capture tool. The only difference is the
signature.

## Contents

- `unit.c` — `auto-c0020-007`'s staged C with the corrected `FUN_800c4468` block
  substituted verbatim from the corrected `chunk_0020.c`.
- `gnt4_shim.h` — the staged header with `zz_00076d0_`'s prototype corrected to the
  ABI the DOL actually uses. In the real pipeline this prototype is regenerated from
  `oracle-registry.json`, which is itself derived from the chunks; it is edited here
  only because the driver is paused and cannot regenerate it.
- `unit.wasm` — built by the driver's own `emcc_build_unit` (identical flags, the
  unit's recorded `allowed_extra_imports`), import whitelist gate passed.
- `*.transcript.json` / `*.transcript.jsonl` — the plan derived from THIS module and
  the console capture replayed against it.

## Reproduce

```sh
node research/decomp/oracle-harness/run-transcript.mjs \
  --capture research/decomp/transcript-preflight/auto-c0020-007-FUN_800c4468/auto-c0020-007.FUN_800c4468.transcript.jsonl \
  --min-cases 8
```

## What still has to happen

The staged `auto-c0020-007` artifact is unchanged and still carries the wrong ABI.
Steps 3-5 of the correction loop — `revoke-unit`, natural rebuild, re-verify — need
the driver, which is paused (`paused_provider_unavailable`), and `revoke-unit` must
run at a driver boundary. Until then this is a proof about the corrected source, not
about the staged unit.
