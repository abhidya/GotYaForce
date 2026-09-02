# `port-units-dispatch/` — units rebuilt so their indirect calls can be observed

These are **not** promoted units and **not** staging. They are a third thing, and the
distinction is load-bearing:

| directory | what a unit in it is |
| --- | --- |
| `research/decomp/port-units-staging/` | the driver's `compile_only` inventory — it compiled and linked, and nothing else |
| `research/decomp/port-units/` | promoted units, which production may load |
| **`research/decomp/port-units-dispatch/`** | **a staged unit rebuilt with the assembly gate's indirect-call lowering, so the `dispatch_green` harness can observe what it dispatches to. Evidence apparatus, not a port artifact.** |

Nothing here is loaded by the game, is on the production path, or carries a verification
tier of its own. A directory here means only that a module exists which
`research/decomp/oracle-harness/run-dispatch.mjs` can replay a console capture against.

## Why they have to exist as separate builds

`docs/verification-status.md` §3.1 has the full argument. In short: the ROM's
`(*(code *)...)()` becomes a `call_indirect` on emcc's own table in an ordinary unit
build, which is both wrong (a GameCube address is not a wasm table index) and invisible.
The gate's lowering rewrites each site to go through the address-keyed thunk table the
dispatch companion already emitted, and the companion's trace mode declares two imports
around it. Only such a module can be observed — `run-dispatch.mjs` refuses one built the
ordinary way rather than passing on it.

## Contents of each directory, all derived

    <unit>.c                  the LOWERED translation unit (the verbatim staged unit.c
                              is never modified; this is the gate-owned rewrite)
    gnt4_shim.h               copied unmodified from the staged unit
    gf_dispatch_frame.h       uniform dispatch frame ABI v1
    gf_indirect_lowering.h    the lowering's macros and per-class slot setters
    gf_dispatch_companion.c   thunks + address-keyed table + __gf_dispatch(+_at)
    gf_indirect_sites.json    the site manifest a capture plan binds its bctrls to
    gate-evidence.json        lowering + companion evidence, including the table that
                              run-dispatch.mjs audits against oracle-registry.json
    unit.wasm                 the module

## Rebuilding

Offline, model-free, and with emcc flags byte-identical to the production per-unit build
(`src/port_wasm_units.py:emcc_build_unit`) — a gate that passed under laxer settings than
the production build would prove nothing about the production build:

```sh
python research/tools/OGhidra/tools/build_dispatch_unit.py \
  --repo-root D:/GotYaForce --unit auto-c0011-005 \
  --out research/decomp/port-units-dispatch/auto-c0011-005
```

Requires the OGhidra checkout (not vendored; clone separately) and
`research/tools/emsdk`.
