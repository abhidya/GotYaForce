# `src-match/` — the matched corpus

**This is the project's first real source code.** Every `.c` file here has been compiled
and proved **byte-identical** against the retail GameCube image. A file in this tree is
not *argued* to be the original function; within the limits recorded below, it **is** the
original function.

Created 2026-09-03 by the matching-decompilation spike's decisive test with 13 entries.
Grown to **405** on 2026-09-04 by
[`research/tools/matching-decomp/loop.py`](../research/tools/matching-decomp/loop.py),
which derives candidate 0 mechanically from the retail encodings — see
[`docs/matching-loop.md`](../docs/matching-loop.md).
See [`docs/matching-decompilation-spike.md`](../docs/matching-decompilation-spike.md) §3
for the original result and [`research/tools/matching-decomp/TOOLCHAIN.md`](../research/tools/matching-decomp/TOOLCHAIN.md)
for the compiler.

## Layout

```
src-match/
  README.md        this file
  matched.json     the registry -- every entry, its address, its iteration count,
                   whether it is exact-bytes or relocation-masked, and the list of
                   functions that were ATTEMPTED AND BLOCKED, with the blocker named
  verify.py        one command that re-proves the whole corpus against the DOL
  game/            matched game functions, one file per function, named for the
                   link-map symbol
  sdk/             matched Dolphin SDK functions -- read the per-file provenance
                   header before reusing anything here
  blocked/         candidates that did NOT match, kept because the reason each
                   one failed is the more useful finding. Every header names the
                   compiler limit that stopped it. These are not results and are
                   not verified by verify.py.
  work/            created and deleted by verify.py --control; not tracked
```

One function per file, and each file's header carries the retail disassembly it
reproduces, the iteration count it took, and anything learned on the way. The exported
symbol is `f` in every file: these are functions extracted from the middle of unknown
translation units, so their real names, linkage and neighbours are not yet established.
Naming them is a later step, and `dtk` is the tool for it.

## Verifying

```bash
python src-match/verify.py --control    # every entry + the negative controls
python src-match/verify.py --sweep      # which compiler builds each one discriminates
```

`verify.py` re-runs the compiler; it never trusts the registry. All 405 entries match and
all 3 controls are correctly rejected — **408 ok, 0 failed**. The controls matter more than the matches: a
wrong structure offset, a **wrong callee behind a correct-looking `bl`**, and a
behaviourally-identical-but-differently-encoded rewrite are each rejected. That last one
would pass every behavioural standard this project currently has.

## What a match here does and does not claim

| | |
| --- | --- |
| **Does claim** | The bytes are identical to retail after masking relocated operand fields, and every relocation names the symbol the retail branch actually resolves to. No threshold, no similarity score. |
| **Does not claim** | That the *original* C looked like this. Several distinct sources compile to the same bytes; matching pins the code, not the authorship. |
| **Does not claim** | That the genuine Metrowerks compiler agrees. These are `mwcc-rs`-exact. Where mwcc-rs diverges from real MWCC, a match here would be wrong — and there is currently no way to check that on this machine. |
| **Does not claim** | Anything about the compiler *version*. 11 of the 13 entries match under all 42 (build × `-O` level) combinations. Only the two signed-`char` accessors discriminate, and all they establish is that the game was **not** built with GC/1.3. |

## Scale, stated plainly

**405 functions, 1,773 instructions.** The census counts **12,062 entry points and
701,464 instructions**, so this corpus is **0.2528 % of the code** — up from 0.0061 % when
it held thirteen. It is 6.87 % of the 5,897 functions the link map names, which is exactly
the divergence the spike warned about: report this work **by instructions, never by
function count** (spike doc §5.2).

Provenance of the 405: 13 hand-written by the spike, **392 produced mechanically by
`loop.py` with zero model calls** — 140 by its leaf seeder, 134 by its wrapper seeder, and
118 by the trivial `blr` seeder. 390 are game code, 15 are SDK.

Two honest discounts a reader should apply:

* **118 of the 405 are a single `blr`** matched by `void f(void) {}`. True about the bytes,
  thin about the program — 29 % of the functions and 6.7 % of the instructions here.
* **No global accessor is in this corpus**, although `lwz r3, d(r13); blr` is one of the
  easiest shapes in the binary. A candidate for one carries a data relocation whose operand
  the oracle masks and cannot name-check, so it would match *any* global. 104 such functions
  were refused on purpose (`docs/matching-loop.md` §2.3).
