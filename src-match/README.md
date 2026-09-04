# `src-match/` — the matched corpus

**This is the project's first real source code.** Every `.c` file here has been compiled
and proved **byte-identical** against the retail GameCube image. A file in this tree is
not *argued* to be the original function; within the limits recorded below, it **is** the
original function.

Created 2026-09-03 by the matching-decompilation spike's decisive test with 13 entries.
Grown to **405** on 2026-09-04 by
[`research/tools/matching-decomp/loop.py`](../research/tools/matching-decomp/loop.py),
which derives candidate 0 mechanically from the retail encodings — see
[`docs/matching-loop.md`](../docs/matching-loop.md) — and to **481** the same day, once
data relocations became verifiable and the small-data refusal could be lifted behind that
verification (`docs/matching-loop.md` §2.3.1,
[`research/tools/matching-decomp/datareloc.py`](../research/tools/matching-decomp/datareloc.py)).
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

`verify.py` re-runs the compiler; it never trusts the registry. All 481 entries match, all
3 negative controls are correctly rejected, and all 5 data-relocation controls land on their
stated verdict — **489 ok, 0 failed**. The controls matter more than the matches: a wrong
structure offset, a **wrong callee behind a correct-looking `bl`**, a
behaviourally-identical-but-differently-encoded rewrite, and a candidate naming a
**different global** behind a correct-looking data relocation are each rejected. The
behavioural ones would pass every behavioural standard this project currently has; the last
one reported `MATCH 100.00%` until 2026-09-04.

## What a match here does and does not claim

| | |
| --- | --- |
| **Does claim** | The bytes are identical to retail after masking relocated operand fields; every branch relocation names the symbol the retail `bl` resolves to; and every **data** relocation names a symbol whose address equals the address the retail encoding itself carries. No threshold, no similarity score. A relocation nothing could check is `MATCH_UNVERIFIED` and is never recorded here. |
| **Does not claim** | That the *original* C looked like this. Several distinct sources compile to the same bytes; matching pins the code, not the authorship. |
| **Does not claim** | That the genuine Metrowerks compiler agrees. These are `mwcc-rs`-exact. Where mwcc-rs diverges from real MWCC, a match here would be wrong — and there is currently no way to check that on this machine. |
| **Does not claim** | Anything about the compiler *version*. 11 of the 13 entries match under all 42 (build × `-O` level) combinations. Only the two signed-`char` accessors discriminate, and all they establish is that the game was **not** built with GC/1.3. |

## Scale, stated plainly

**481 functions, 2,024 instructions.** The census counts **12,062 entry points and
701,464 instructions**, so this corpus is **0.2885 % of the code** — up from 0.0061 % when
it held thirteen. It is 8.16 % of the 5,897 functions the link map names, which is exactly
the divergence the spike warned about: report this work **by instructions, never by
function count** (spike doc §5.2).

Provenance of the 481: 13 hand-written by the spike, **392 produced mechanically by
`loop.py` with zero model calls** — 140 by its leaf seeder, 134 by its wrapper seeder, and
118 by the trivial `blr` seeder — and **76 by `sda_recover.py`**, the small-data globals
that were refused while their data relocations were unverifiable. 444 are game code, 37 are
SDK.

Two honest discounts a reader should apply:

* **118 of the 481 are a single `blr`** matched by `void f(void) {}`. True about the bytes,
  thin about the program — 25 % of the functions and 5.8 % of the instructions here.
* **The global accessors are in now, and they are the newest entries.** Until 2026-09-04 a
  candidate for one carried a data relocation whose operand the oracle masked and could not
  name-check, so it would have matched *any* global, and 104 such functions were refused on
  purpose. The retail encoding names the address and the candidate's symbol name encodes
  one; the oracle now requires them to be equal, and 76 of the 104 are matched
  (`docs/matching-loop.md` §2.3.1). Each of their headers carries the address every data
  relocation was checked against. The other 28 are not a verification failure: 21 use
  opcodes this seeder does not model, 7 are `mwcc-rs` code-generator limits.
