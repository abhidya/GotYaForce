# `dispatch-wrong-index` — a DELIBERATELY WRONG port, kept as a negative control

> [!WARNING]
> **`unit.wasm` in this directory is not a port of anything and must never be
> promoted, loaded by the game, counted as inventory, or copied into
> `research/decomp/port-units-staging/` or `port-units-dispatch/`.** It exists
> to be caught.

## What it is

`auto-c0011-005` rebuilt by
`research/tools/OGhidra/tools/build_dispatch_unit.py` from a **modified** copy of
the staged `unit.c`, with exactly one character changed in `FUN_80079ab8`:

```diff
- (*(code *)(&PTR_FUN_802d65d0)[*(char *)(param_1 + 0x540)])();
+ (*(code *)(&PTR_FUN_802d65d0)[*(char *)(param_1 + 0x541)])();
```

The vtable index is read from the wrong byte of the actor. Everything else —
the lowering, the companion, the thunk table, the emcc flags — is identical to
the real build, and the emitted dispatch table is *correct*, so the table audit
passes and the module is entirely self-consistent.

## Why it is here

Every other negative control for `dispatch_green` mutates the **capture**, which
tests the comparator. This one mutates the **port**, which tests the thing the
standard actually exists to claim: that a module whose dispatch selects the
wrong table entry cannot pass.

It is the answer to the standing objection that a thunk-level transcript
observes the gate's own lowering and could therefore agree with itself. Replayed
against the committed console capture
`corpora/auto-c0011-005.FUN_80079ab8.dispatch.jsonl`, this module fails at
case 1:

```
DISPATCH TARGET divergence in case n=1 at i=0 (site 80079ab8:0):
the console's bctrl at 0x80079ae8 jumped to 0x80079ba8 (FUN_80079ba8),
the port dispatched to 0x80079b08
```

The console's own `bctrl` target is what catches it, which is the whole point of
recording CTR at the branch.

## Reproducing it

```sh
# copy the staged unit, change 0x540 -> 0x541 in FUN_80079ab8, then:
python research/tools/OGhidra/tools/build_dispatch_unit.py \
  --repo-root <the copy's root> --unit auto-c0011-005 --out <scratch>
```

`auto-c0011-005.c` here is the lowered source the build produced, kept so the
one-character difference is auditable without rebuilding anything.
