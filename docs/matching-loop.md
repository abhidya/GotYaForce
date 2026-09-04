# The matching-decompilation loop

**Date: 2026-09-04.** Status: **BUILT AND RUN. 570 new functions are byte-identical to
retail, and the loop that produced them never called a model.**

Companion documents: [`docs/matching-decompilation-spike.md`](matching-decompilation-spike.md)
(the feasibility spike this implements, whose §4.1 sketched the loop and whose §4.2
priced it at 2.6 GPU-years),
[`docs/matching-compiler-census.md`](matching-compiler-census.md) (the same compiler
measured against the whole corpus) and
[`research/tools/matching-decomp/TOOLCHAIN.md`](../research/tools/matching-decomp/TOOLCHAIN.md)
(the compiler).

> | | |
> | --- | --- |
> | **570 new matches, 0 model calls** | The matched corpus goes from 13 functions to **583**; from 43 instructions to **3,157**. Every one was produced mechanically and re-proved by `src-match/verify.py`. §3, §10 |
> | **A better seeder was the binding constraint, and it moved** | §7's own conclusion was that "a better seeder — not a better model — is what moves the 5,477". The control-flow tier (§10) turned that into **379 functions reaching the compiler where 15 did before — 25×** — and **178 new byte-identical matches**. |
> | **The remainder is now the compiler's, and it is two bugs** | **1,632 functions and 105,337 instructions** are blocked by the compiler, and **1,481 of them fall behind exactly two items**: `loop codegen is not implemented` (768 functions, 71,632 instructions) and **wrong relocation types on absolutely addressed globals** (713 functions, 31,483 instructions). §10.3, §10.5 |
> | **The integrity refusal is gone, and it cost nothing to give up** | The data-relocation lane made r13/r2 and absolute globals verifiable, so the seeder now *names* the global and lets the oracle judge. The class that held 1,212 functions and 50,194 instructions is at **zero**, and no wrong global can pass — `match.py` address-checks every one. §10.3 |
> | **The permuter finally closed something: 10** | Zero across 580 mutants before; **10 matches across 3,716 mutants** now that a seeder writes candidates it can move. Still small, and still reported as small. §4 |
> | **The free-win fraction corpus-wide is 9.9 % of functions and 0.45 % of instructions** | Seed-only across all 5,897 link-map functions. §5.2's warning about counting functions is still attached to this loop's own numbers. §5 |
> | **The 2.6 GPU-year figure still barely moves: 2.63 → 2.61** | The free stages now remove **~64 of 23,024 GPU-hours — 0.28 %** — because 96 % of that cost is the *moderate*, *hard* and *research* tiers, which this loop still cannot touch. §7 |
> | **No model was run, and the reason is on the record** | The server answers on `127.0.0.1:8888` but reports `"loaded": false` for every model; `nvidia-smi` shows 968 MiB and 2 % on a leased 1080 Ti. A completion would have forced a 27B load onto that GPU. **Every model number below is labelled recorded, not live.** §6 |

Nothing here touched the GPU, the supervisor, the port driver, or any pipeline state.
Nothing was downloaded. The retail GCM was read, never written.

---

## 1. The design principle, and what it is answering

The spike's §4.2 measured that this loop is **iteration-bound, not tok/s-bound**: at the
project's own 2.5 tok/s an 80× faster card buys 4.5×, because past ~40 tok/s the cost is
iterations and prefill. It also measured that setting every tier's success rate to 1.0
leaves the cost *unchanged*, because a failure and a success burn the same iterations.

So the only lever that moves the number is **iterations per function**, and the cheapest
iteration is the one that is never issued. Three of this loop's four stages remove
iterations by not calling a model at all.

```
seed      candidate 0, derived MECHANICALLY from the retail encodings + the link
          map.  No model.  A match here costs one 20 ms compile.
permute   when a candidate is close, mutate the C mechanically and compile the
          mutants in parallel on CPU.  No model.
llm-step  one model call carrying the target disassembly, the current candidate,
          the oracle's FIRST MISMATCH, and a matched sibling exemplar.  The only
          stage that costs GPU.
run       drives the three over one function, a shape class, or the whole
          corpus, writing a JSONL ledger so throughput is MEASURED.
```

Everything is in [`research/tools/matching-decomp/loop.py`](../research/tools/matching-decomp/loop.py).
It imports `match.py` and `objdiff.py` read-only; the compiler fork, `match.py`,
`verify.py` and the census tools are untouched.

---

## 2. Mechanism

### 2.1 The seeder: candidate 0 without a model

The spike's §4.1 said "seed, don't generate from nothing" and proposed seeding from a
matched sibling's source with the callee and constants substituted. Building that
revealed a better version of the same idea: **do not substitute into the sibling's text —
re-derive the C from the retail encodings directly.** The sibling's *source* is then only
needed as an LLM exemplar, and the seeder generalises past the eight shapes the spike had
exemplars for.

Four seeders, tried in order:

| seeder | what it handles | matched |
| --- | --- | ---: |
| `empty` | a bare `blr` → `void f(void) {}` | 118 |
| `wrapper` | the Metrowerks non-leaf frame with exactly one `bl`, with `li`/`mr` argument setup; the callee's name comes from the link map | 134 |
| `leaf` | straight-line leaves: loads, stores, immediates, register moves, sign extension, and one leading null guard compiled to `beqlr` | 140 |
| `cfg` | **control flow**: a basic-block graph over the retail bytes, structured into `if`/`else`, early `return` and `&&`/`||`, with the symbolic evaluator carried across `bl` boundaries and globals named through `datareloc`. [`seed_cfg.py`](../research/tools/matching-decomp/seed_cfg.py), §10 | 178 |

The `leaf` seeder is a small symbolic evaluator, not a template bank. It walks the decoded
instructions carrying an expression per register (`CONST k`, `ARG i`,
`FIELD(arg, offset, width, signed)`), emits one C statement per store, and reconstructs a
struct per pointer argument with exact byte offsets:

```
$ python research/tools/matching-decomp/loop.py seed --function zz_02650c0_ --check
/* seeder: leaf */
typedef struct S0 {
    char pad_0[0x1];
    char           field_1;
} S0;

int f(S0 *p0)
{
    return p0->field_1;
}

802650c0  lbz r3, 1(r3)      |   lbz r3, 1(r3)
802650c4  extsb r3, r3       |   extsb r3, r3
802650c8  blr                |   blr
VERDICT MATCH  100.00%
```

That is the spike's `zz_02650c0_` — the one function of its thirteen that took **two**
iterations, because the first candidate returned `char` and lost the `extsb`. The seeder
reaches it in **zero**, because the sign extension is read off the retail bytes rather
than guessed at. Every one of the spike's thirteen is re-derived this way.

**The seeder refuses rather than guesses.** Every refusal names its reason, and the
reasons are counted in §5.

### 2.2 The permuter: the last mile without a model

Two move sets, both compiled in parallel on CPU:

* **Spec variants** — the seeder is parameterised (return type, argument type, guard
  spelling), and the variant space is enumerated, bounded at 64 per function.
* **Text mutations** — applied to *any* C, so the stage also works on an LLM's near-miss:
  declaration and return-type flips across the integer widths, adjacent independent
  statement reorder, `++i`/`i++`, `if` inversion, `while`↔`for`, and temp-variable
  hoisting on the return expression.

Mutants run through a `ThreadPoolExecutor`, each in its own scratch directory (`cand.c`
and `cand.o` are fixed names — sharing one directory lets two workers clobber each other).

### 2.3 The oracle, and a second hole in it

The oracle is `objdiff.compare` driven through `match.py`'s compile path, with the DOL and
link map loaded once and held open.

The spike found and fixed one hole: relocated operands were masked but the relocation's
*symbol* was never checked, so a candidate calling the wrong function reported MATCH.
Running the loop at scale exposed the **remaining half of that same hole**:

> `match.py` resolves and name-checks only `R_PPC_REL24` branch targets — the only
> relocations a linked DOL plus a link map can resolve, because the DOL has no data symbol
> table. A candidate whose match rests on a **data** relocation (`R_PPC_ADDR16_HA/LO`,
> `R_PPC_EMB_SDA21`) has had that operand masked and *never* name-checked. Such a
> candidate would match **any global in the game**.

`loop.py` therefore downgrades any such verdict to **`MATCH_UNVERIFIED`** and never writes
it to `src-match/`. The `leaf` seeder refuses `r2`/`r13`-based loads and stores outright for
the same reason — **104 functions corpus-wide, 32 of them in the shape-shared class** —
which is why the corpus contained no global accessors even though `lwz r3, d(r13); blr` is
among the easiest shapes in the binary. **That was a deliberate 104-function loss taken to
keep the corpus honest**, and it is the price of the standard the spike set: byte equality,
no tolerance, no "close enough".

> **Superseded, and this is what paying that price bought.** The hole above is now closed
> rather than routed around: `research/tools/matching-decomp/datareloc.py` recovers the
> small-data bases from the retail bytes two independent ways, reads the absolute address
> each retail data reference names, and resolves the candidate's relocation symbol back to
> an address; `match.py` requires the two to be equal. A candidate naming the wrong global
> is now a **MISMATCH**, not a silent pass. The `MATCH_UNVERIFIED` downgrade stays for
> anything neither check reaches — no argument to `compare` can turn a MISMATCH into a
> MATCH — but the *seeder* no longer has to refuse a global. §10.3 is what that changed:
> the refusal class went from 1,212 functions to zero, and the corpus has global accessors
> in it for the first time.

### 2.3.1 Closing it properly: data relocations are now address-checked

Refusing was right, but it was not the *only* honest option, and the sentence above
contains its own answer: the claim was that the harness "cannot resolve" a data
relocation. **The retail bytes can.** `lwz rX, d(r13)` names exactly one absolute address.
So does a `lis`/`addi` pair. And the candidate side is resolvable too, because every global
name this corpus uses carries its own address — `DAT_80436498`, `PTR_DAT_8043393c`,
`FLOAT_80436a20` — and `research/decomp/data/oracle-registry.json` enumerates them.

[`research/tools/matching-decomp/datareloc.py`](../research/tools/matching-decomp/datareloc.py)
implements that, and `objdiff.compare` now applies it. **The rule:**

> For every data relocation the candidate carries at offset `O` —
> `R_PPC_ADDR16_HA/LO/HI`, `R_PPC_ADDR32`, `R_PPC_EMB_SDA21` —
> **`want`** is the absolute address the *retail* encoding at `O` names, read out of the
> retail bytes alone; **`got`** is `resolve(relocation symbol) + addend`, resolved from the
> link map, the address encoded in the symbol name, or the oracle registry.
> `got == want` → verified. `got != want` → **MISMATCH**. Either side unresolvable →
> **`MATCH_UNVERIFIED`**, with the reason named. Nothing this check does can turn a
> MISMATCH into a MATCH, and a relocation nothing checked *still* downgrades the verdict —
> that part of §2.3 has not been weakened, it has been extended.

**The small-data bases are not a guess.** Two independent derivations, cross-checked at
load time; `datareloc` refuses to produce bases at all if they disagree.

```
a)  the ROM's own boot code, the tail of __init_registers:
      8000332c  3c408043  lis  r2,  0x8043     8043ea20 = _SDA2_BASE_
      80003330  6042ea20  ori  r2,  r2, 0xea20
      80003334  3da08043  lis  r13, 0x8043     8043b5a0 = _SDA_BASE_
      80003338  61adb5a0  ori  r13, r13, 0xb5a0
b)  the DOL section table -- the EABI linker centres each base 0x8000 into its section:
      .sdata  @ 0x804335a0  ->  0x8043b5a0   (r13)
      .sdata2 @ 0x80436a20  ->  0x8043ea20   (r2)
```

A third corroboration comes from a tool that was never consulted for the bases at all:
`zz_0010b50_` stores through `r13 - 0x54c4 / -0x54c6 / -0x54c8`, which under these bases
are 0x804360DC / 0x804360DA / 0x804360D8 — **exactly** the `DAT_804360dc`, `DAT_804360da`,
`DAT_804360d8` that `oracle-registry.json` records for that function from Ghidra's own
pass.

**The mutation test, run the way the spike ran T6b.** The first row is not hypothetical: it
is a candidate that was written by hand during this work and *did* report `MATCH 100.00%`
before the check existed.

| candidate for `zz_000a144_` / `zz_0005984_` | verdict |
| --- | --- |
| the globals the retail bytes name (`DAT_804360cc`, `DAT_804360c8`) | `MATCH` |
| **different** globals at plausible addresses (`DAT_804360c8`, `DAT_804360c4`) | **`MISMATCH`** |
| the neighbouring global, off by four (`DAT_804360c4`) | **`MISMATCH`** |
| symbols that resolve to no address (`g_someGlobal`) | `MATCH_UNVERIFIED` |
| a name encoding an address in no DOL section and not in bss (`DAT_deadbeef`) | `MATCH_UNVERIFIED` |
| a data relocation with **no resolver supplied at all** | `MATCH_UNVERIFIED` |

The first five are permanent controls in `src-match/verify.py --control`; the sixth, plus a
compiler-free synthetic-object version of the first three, is `selftest.py` **T8/T8b/T8c/T8d**
— the data-relocation counterpart of T6b. `verify.py --control` is **489 ok, 0 failed**: the
405 original matches and the 76 new ones all re-prove, and every control lands on its stated
verdict.

**What it recovered.** `research/tools/matching-decomp/sda_recover.py` re-derives C for the
104 refused functions with a small-data-aware version of the same symbolic evaluator and
records only what the strengthened oracle calls `MATCH`. `loop.py`'s own seeders are
untouched; the seeder lane lifts its refusal by calling `datareloc.global_symbol` /
`global_decl` / `sda_bases`, documented at the foot of `datareloc.py`.

```
$ python research/tools/matching-decomp/sda_recover.py --record

SMALL-DATA RECOVERY  targets=104
_SDA_BASE_ (r13) = 0x8043b5a0   _SDA2_BASE_ (r2) = 0x8043ea20
  BUILD_FAILED             2
  MATCH                   76
  MISMATCH                 5
  MATCH_UNVERIFIED         0
  NO_SEED                 21
  TOTAL                  104   compiles=123  wall=4.6s
```

**76 of the 104 recovered**, 251 instructions, 116 data relocations address-checked (93 of
the symbols corroborated by `oracle-registry.json`, 23 resolved by the name encoding alone).
Zero `MATCH_UNVERIFIED` — every recorded match is address-checked, not masked. The
remainder is honestly classified and none of it is this check's failure:

| count | why not | owner |
| ---: | --- | --- |
| 21 | opcode outside this seeder's envelope (`lis`, `cmpwi`, `cmplwi`, `addi`, `or`, `bnelr`) | the seeder lane |
| 5 | retail hoists a constant above the stores — the §4 code-generator class, not a C difference | `mwcc-rs` |
| 2 | `mwcc-rs` roadmap refusal (*"a run of stores that mwcc latency-schedules needs the scheduler"*) | `mwcc-rs` |

Six of the 21 are `lis`-built **absolute** data references, which this check also covers
(`R_PPC_ADDR16_HA`/`LO`); only the seeder does not yet model `lis`. They are recoverable the
moment it does, with no further oracle work.

### 2.4 Recording

A match writes `src-match/<game|sdk>/<name>.c` with a provenance header — the retail
disassembly, the candidate's origin, iterations, model calls, permuter steps, shape,
`exact_bytes`, and a SHA-256 of the C — and appends an entry to `src-match/matched.json`.
`src-match/verify.py` re-proves the whole registry by re-running the compiler, and needed
no change to do so. **A non-match is never written under any name, and
`MATCH_UNVERIFIED` counts as a non-match.**

### 2.5 The model step

Prompt = target disassembly + line-numbered current candidate + the oracle's first
mismatch + the side-by-side diff + the matched-sibling exemplar for the same shape. When
the *seeder* refuses, the model is asked for candidate 0 instead, with the refusal quoted —
which is where a model actually earns its keep here.

Ghidra's C is deliberately absent, per the spike's §4.1 (the `FUN_800c4468` contamination).
Replies must be one complete function in one ```c fence; anything else is rejected without
being compiled.

Sampling is the **plan-derive** profile, not the compile-fix profile:
`temperature 0.2, top_p 0.9, top_k 20, presence_penalty 0.0`, thinking off. The rig's own
record (`OGhidra/src/port_plan_derive.py:828`, measured 2026-08-29) is that the compile-fix
profile's `presence_penalty=1.5` punishes every structural token that must repeat and the
model stops mid-output with `finish_reason="stop"` — it reads as a truncation bug and is
the sampler doing what it was told.

---

## 3. Results: the shape-shared class

The spike's §3.1.5 identified **233 functions sharing an exact matched shape** with one of
its thirteen as the near-certain next matches. This measurement puts the number at **234**
(the wrapper shape is 115 in the link map, not 114); 221 of them were not already matched.

```
$ python research/tools/matching-decomp/loop.py run --class shape-shared --no-llm

RUN shape-shared  targets=221  wall=4.5s  compiles=171  compile_s=2.3
  MATCH_SEED               171 functions     942 instructions
  NO_SEED                   50 functions     205 instructions
  MATCHED TOTAL            171 functions     942 instructions
```

| | functions | instructions |
| --- | ---: | ---: |
| **matched at iteration 0 (no model call)** | **171** | **942** |
| matched by the permuter | 0 | 0 |
| unmatched | 0 | 0 |
| seeder refused | 50 | 205 |

**171 of 221 — 77.4 % of the class — in 4.5 seconds of CPU.** Nothing in the class reached
the permuter, because a shape-shared seed either matches exactly or the seeder declines to
write one; nothing landed in between.

### 3.1 The 50 refusals, by class

| count | class |
| ---: | --- |
| 32 | load or store through **r13** (sdata) — would need an unverifiable data relocation (§2.3) |
| 13 | the callee's **link-map name is not a C identifier** (`gnt4-memcpy`, `gnt4-__ieee754_pow`, `AsyncImage::FreeLoadBuffer(void)`) |
| 4 | the callee's address resolves to no link-map symbol |
| 1 | store through a non-argument base register |
| **50** | |

None is a compiler limit and none is a C difficulty. The first group is a deliberate
integrity refusal; the second and third are **harness** limits — a relocation must name the
symbol exactly as the map spells it, and `gnt4-memcpy` is not spellable in C. Those 17
functions are recoverable the moment the harness can emit a symbol alias, and that is the
single cheapest extension available to this loop.

### 3.2 Iteration count, measured

Across all three runs, **407 functions produced a candidate 0 and 392 matched on it —
96.3 %.** Mean iterations to match, over everything the loop matched: **1.00**. No function
in the corpus needed a second candidate, because the only functions that needed one were
the ones the seeder refused to write.

That number is **not** comparable with the spike's §4.2 budgets and must never be used as
one. It is the iteration count for functions whose C is *derivable from the encodings*, and
that class is 6.9 % of the link map and 0.25 % of the instructions (§5). §4.2's budgets are
about the 33–128-instruction *moderate* tier, which this loop still cannot reach.

---

## 4. What the permuter measured — a negative result worth more than a positive one

> **Updated by §10.** With only the three straight-line seeders the permuter closed
> **nothing** — the measurement below, and the reason for it, stand exactly as written.
> Once the control-flow tier gave it candidates with more than one statement to move, the
> same stage closed **10 functions (59 instructions) across 3,716 mutants**, all of them
> respellings the spec variants produce (return and argument widths, guard spelling).
> That is the stage's first non-zero result and it is still small: 10 of the 211 functions
> that reached it. The paragraphs below explain why, and the explanation did not change.

The permuter ran over every near-miss in the corpus: **580 mechanical mutants compiled,
0 matches**. On the face of it the stage does not pay.

It does not pay **because there was nothing there to close.** All 15 near-misses were then
classified from the bytes alone, and every one is a **code-generator** difference, not a C
difference:

| count | class |
| ---: | --- |
| 7 | constant rematerialised / register colouring — *n* extra `li`, the rest of the sequence identical |
| 4 | instruction scheduling — the same instructions in a different order |
| 2 | constant rematerialised — retail loads a constant once and reuses it |
| 1 | scheduling and/or register colouring — the same instruction mix, differently ordered or allocated |
| 1 | `mwcc-rs` roadmap refusal |
| **15** | **compiler: 15.  genuine C difference: 0.** |

The shape of it, from `zz_0283a90_`:

```
80283a90  stw r4, 0x1318(r3)   |   stw r4, 0x1318(r3)
80283a94  li r0, 0             |<< stw r5, 0x131c(r3)
80283a98  stw r5, 0x131c(r3)   |<< li r0, 0
80283a9c  stw r0, 0x1320(r3)   |   stw r0, 0x1320(r3)
80283aa0  blr                  |   blr
```

Real MWCC hoists the constant setup above the stores it feeds. `mwcc-rs` emits it
immediately before its use. **No ordering of the C statements changes that** — the permuter
tried, 580 times. `mwcc-rs`'s own README names matching MWCC's register colouring as its
core research target, and this is that target seen from the outside.

This is the same verdict the spike reached on its five non-matches (§3.1.3), now on a
larger and automatically-classified sample: **at the current compiler's envelope, every
function whose C is derivable and whose bytes still differ is blocked by the compiler.**

The permuter stays in the loop because its cost is ~30 seconds of CPU across the whole
corpus and because it is the stage that will close an LLM's near-miss once the model step
runs. But **its measured contribution today is zero, and reporting it as anything else
would be a lie.**

---

## 5. Results: the free-win fraction corpus-wide

```
$ python research/tools/matching-decomp/loop.py run --all-compilable \
      --max-insns 9999 --no-llm --no-permute

RUN all-compilable-seed  targets=5713  wall=45.9s  compiles=236  compile_s=4.6
  MATCH_SEED               221 functions     788 instructions
  NO_SEED                 5477 functions  376793 instructions
  UNMATCHED                 15 functions     118 instructions
```

Run over the whole link map after the shape-shared class was already recorded, so these
221 are **additional** — shapes with no matched exemplar at all, found by the seeder rather
than by shape lookup. The largest single contributor is the 118 functions that are one bare
`blr`.

**Totals for the matched corpus:**

| | before this work | after the three straight-line seeders | after the control-flow tier (§10) |
| --- | ---: | ---: | ---: |
| functions | 13 | 405 | **583** |
| instructions | 43 | 1,773 | **3,157** |
| share of `.init` + `.text` (701,464 instructions) | 0.0061 % | 0.2528 % | **0.4501 %** |
| share of the 5,897 link-map `.text` functions | 0.22 % | 6.87 % | **9.89 %** |

Of the 583: **540 are game code, 43 are SDK** (`gnt4-` prefixed, kept in `src-match/sdk/`).

### 5.1 Why the other 5,112 got no seed

Corpus-wide, seed-only, over the 5,492 functions unmatched before §10. Each refusal is
tagged with the tier that *owns* it — chosen by the function's own prologue and graph, not
by whichever seeder happened to be tried last — and with the class that says **whose
problem it is**:

| class | functions | instructions | meaning |
| --- | ---: | ---: | --- |
| `seeder` | 3,631 | 269,405 | the owning seeder's own envelope: an opcode it does not model, an unstructured graph, a value that would need a local variable |
| `compiler` | 1,481 | 103,115 | a shape mwcc-rs is *measured* to refuse: a loop, or a global it relocates with the wrong type (§10.3) |
| `integrity` | **0** | **0** | a match would rest on a data relocation the harness cannot check. **This class is now empty** — see §10.3 |

The largest single reasons:

| class | tier | functions | instructions | refusal |
| --- | --- | ---: | ---: | --- |
| **compiler** | cfg | **768** | **71,632** | **a back edge: `loop codegen is not implemented yet (roadmap)`** |
| **compiler** | cfg | **713** | **31,483** | **an absolutely addressed global: mwcc-rs relocates the `lis`/`addi` pair with the wrong types (§10.3)** |
| seeder | cfg | 352 | 12,634 | the memory base is neither an argument nor a loaded pointer |
| seeder | leaf | 304 | 4,522 | undecoded instruction |
| seeder | cfg | 194 | 30,203 | `xoris` — the int↔float conversion idiom |
| seeder | cfg | 192 | 12,029 | a branch chain that is neither a pure `&&` nor a pure `\|\|` |
| seeder | cfg | 186 | 12,614 | an earlier call's result is dereferenced after another statement (needs a local) |
| seeder | cfg | 181 | 9,293 | a branch leaves the enclosing region (unstructured graph) |
| seeder | wrapper | 179 | 6,078 | undecoded instruction |
| seeder | cfg | 165 | 33,977 | `psq_st` / `psq_l` — paired-single (vector/matrix) code |
| seeder | cfg | 112 | 15,122 | `mulhw` / `mulhwu` — the constant-division idiom |
| seeder | cfg | 88 | 11,328 | `rlwimi` — bitfield insert |
| seeder | cfg | 122 | 7,775 | a stack local, or its address |
| seeder | any | 207 | 7,445 | the callee's link-map name is not a C identifier |

**Read the `seeder` rows correctly.** They are statements about *this loop's seeders*, not
about the compiler and not about the binary. The corpus-wide free-win fraction measured
here — 9.9 % of functions, 0.45 % of instructions — is the ceiling of the four mechanical
seeders as they stand, and it would rise with every opcode and every graph shape added. It
is **not** an estimate of how much of the game is matchable.

### 5.2 The instruction-weighted view, as §5.2 of the spike demands

> **583 functions is 9.89 % of the link map's entry points and 0.4501 % of the
> instructions.**

Forty-five times the functions the spike matched, and still under half of one percent of
the game. The spike warned that a loop which only solves short functions can report a large
function-percentage having touched almost none of the code. **This loop is still the
extreme case of that warning**, though less extreme than it was: its mean matched function
is 5.4 instructions against a corpus mean of 58.2, up from 4.4. Report this work by
instructions.

---

## 6. Throughput — and which numbers are live

**Live, measured on this machine (CPU only, no GPU):**

| | |
| --- | --- |
| compile + diff, one candidate | **~20 ms** (`mwcc-rs`, 595 compiles in 17.2 s under the parallel permuter; 4.6 s for 236 sequential) |
| shape-shared class, 221 functions | **4.5 s wall**, 2,926 functions/minute |
| whole link map, seed-only, 5,713 functions | **45.9 s wall**, 7,468 functions/minute |
| whole link map, seed + permuter, 5,492 functions | **30.5 s wall**, 595 compiles |
| cost per match | **~26 ms of CPU** |

These were taken on a shared machine — a parallel compile-ability census was running
`--jobs 10` for part of the window — so treat them as an upper bound on cost, not a
benchmark. The conclusion they support does not depend on the precision: the mechanical
stages cost milliseconds and the model stage costs minutes, and that ratio is what §7 turns
on.

**Recorded, not live — the model step.** The server answers on `127.0.0.1:8888`, but:

```
$ curl -H "Authorization: Bearer $KEY" http://127.0.0.1:8888/v1/models
{"id":"unsloth/Qwen3.8-27B-GGUF", ... "loaded":false, ...}   # every model: loaded:false

$ nvidia-smi --query-gpu=name,memory.used,utilization.gpu --format=csv
NVIDIA GeForce GTX 1080 Ti, 968 MiB, 2 %
```

No model is resident. Issuing a completion would have forced a 27B load onto a GPU that is
leased to another tenant, so **no completion was issued and there are no live model
numbers in this document.** The model path is instead exercised end to end against a
reconstructed reply, in `loop.py selftest` group S9:

```
== S9  end to end: wrong candidate -> oracle -> model -> MATCH ==
  [ok  ] the wrong candidate is rejected
  [ok  ] the oracle localises the loss of extsb
  [ok  ] the loop reaches MATCH through the model
  [ok  ] one model call, two iterations
```

The candidate it starts from is the spike's own recorded first attempt at `zz_02650c0_`
(returned `char`, lost the `extsb`) and the edit the fixture makes is the recorded fix
(widen to `int`). **The prose around that edit is written, not captured** — it is labelled
as such in the source. Every line of the model path except the socket is covered: prompt
construction, fence extraction, rejection of incomplete replies, iteration accounting,
token estimation, and the re-check against the oracle.

---

## 7. The honest update to the 2.6-GPU-year figure

The spike's §4.2 priced the loop at **23,024 GPU-hours = 2.63 GPU-years** for 46.3 % of the
10,997 non-SDK functions. Removing every function this loop matched from that model, at the
tier and per-iteration cost the spike itself assigned:

| tier | functions removed | GPU-hours removed |
| --- | ---: | ---: |
| trivial | 256 | 14.5 |
| easy | 134 | 26.7 |
| moderate / hard / research | 0 | 0.0 |
| **total (three straight-line seeders)** | **390** | **41.2** |
| the control-flow tier's 178, at the same per-tier cost | 178 | ~23.5 |
| **total** | **568** | **~64.7** |

> **23,024 → ~22,959 GPU-hours. 2.63 → 2.61 GPU-years. A 0.28 % reduction.**

**The free stages are real matches and they do not change the answer.** The reason is
arithmetic the spike already published and this work confirms from the other direction:
the *moderate*, *hard* and *research* tiers are **22,127 of the 23,024 hours — 96.1 %** —
and every function this loop can express falls in *trivial* or *easy*. Seeding removes the
cheapest 0.18 % of a bill whose weight is entirely in functions no mechanical seeder will
ever write.

Three corollaries, in decreasing order of how much they should change what happens next:

1. **The binding constraint has moved, and it is no longer the model.** The spike's §4.2
   concluded "the iteration count is a statement about model capability". At the *current
   compiler envelope* that is no longer the live question: of the 5,492 functions the loop
   could not match, 5,477 never reached the compiler at all, and all 15 that did were
   blocked by the code generator (§4). Until `mwcc-rs`'s general generator can schedule
   like MWCC and colour registers like MWCC, **a better model changes nothing about those
   15, and a better seeder — not a better model — is what moves the 5,477.** The spike's
   own revised step 0 (contribute lowerings upstream) is confirmed as the highest-value
   item, and register colouring is confirmed as out of scope.

   > **§10 acted on this, and it held.** A control-flow seeder took the number that reaches
   > the compiler from 15 to 379 and produced 178 matches, with no model call. It also
   > moved the constraint again: the remainder is now **3,631 functions the seeder still
   > cannot express, 0 refused on integrity, and 1,632 that are the compiler's** — and
   > **1,481 of that last group fall behind just two items**: the missing `loop codegen`
   > lowering (768) and the wrong relocation types on absolutely addressed globals (713).
   > Those two are now the highest-value work in the project's matching lane.
2. **The spike's step 4 is still unmeasured, and this work did not measure it.** Twenty
   *moderate*-tier functions still have to go through a real model to replace §4.2's
   guessed 25-iteration budget. That experiment needs both a GPU that is not leased and a
   compiler that can build a 33–128-instruction function; neither exists today.
3. **The iteration-0 rate is the number to carry forward, with its scope attached.**
   96.3 % of expressible functions matched on candidate 0. Applied to a *frontier*-model
   loop (spike §4.3: Star Fox Adventures, 44.3 fns/day across 8 loops), the mechanical
   seeder removes 392 functions from the queue for free — about **nine days of that
   project's calendar rate**, which is a better way to read this result than the GPU-hour
   line above.

---

## 8. Reproduction

```bash
export MWCC_RS=".../.tools/mwcc-rs/target/release/mwcc.exe"   # TOOLCHAIN.md §1

# the loop's own tests: 71 checks, no network; S9 needs the compiler, the rest do not
# (S10 covers the CFG tier's graph, structuring, calls and refusal classes;
#  S11 covers the undefined8 narrowing rule)
python research/tools/matching-decomp/loop.py selftest

# the shape index, measured (not taken from the spike)
python research/tools/matching-decomp/loop.py shapes --top 20

# one function, end to end
python research/tools/matching-decomp/loop.py seed --function zz_02650c0_ --check

# the five runs this document reports, in order
python research/tools/matching-decomp/loop.py run --class shape-shared --no-llm \
    --tag shape-shared
python research/tools/matching-decomp/loop.py run --all-compilable --max-insns 9999 \
    --no-llm --no-permute --tag all-compilable-seed
python research/tools/matching-decomp/loop.py run --all-compilable --max-insns 9999 \
    --no-llm --tag all-compilable-permute
# --- the control-flow tier, s10 ---
python research/tools/matching-decomp/loop.py run --all-compilable --max-insns 9999 \
    --no-llm --no-permute --tag cfg-seed
python research/tools/matching-decomp/loop.py run --all-compilable --max-insns 9999 \
    --no-llm --tag cfg-permute

# re-prove all 583 matches plus the three negative controls
python src-match/verify.py --control          # 586 ok, 0 failed
```

Artifacts:
[`research/decomp/data/matching-loop-ledger.jsonl`](../research/decomp/data/matching-loop-ledger.jsonl)
(one row per function per run: iterations, model calls, permuter steps, compiles, outcome,
first-mismatch class, wall time) and
[`research/decomp/data/matching-loop-results.json`](../research/decomp/data/matching-loop-results.json)
(per-run totals). The runs are order-dependent by design — each records its matches, and a
later run skips what an earlier one already proved — so reproduce them in the order above,
starting from a clean `src-match/matched.json`.

---

## 9. Uncertainties, stated

1. **Every match is `mwcc-rs`-exact, not MWCC-exact**, and there is still no way to check
   the difference on this machine. This is the spike's uncertainty 1 and 570 more functions
   now rest on it. If `mwcc-rs` diverges from the genuine compiler on any of these shapes,
   those matches are wrong and nothing here would say so. `verify.py` is what re-tests them
   when a better compiler arrives. **The control-flow tier makes this heavier, not
   lighter**: an `if`, a `&&` and a call sequence exercise far more of the code generator
   than `return p->field_4;` does, so a divergence has more room to hide.
2. **The `blr`-only functions are the weakest entries in the corpus.** 118 of the 583 are a
   single `blr` matched by `void f(void) {}`. That is a true statement about the bytes and a
   very thin statement about the program: the retail function may be an empty virtual
   override, a stub, or padding. They are counted here because the oracle's standard is byte
   equality and they meet it, but a reader weighting this corpus by *information* should
   discount them — they are 20 % of the functions and 3.7 % of the instructions.
3. **The corpus-wide free-win fraction is a floor, not a ceiling.** 3,631 of 5,112 refusals
   are the seeders' own envelope. A wider decoder and a wider structurer raise the number;
   nothing here bounds how far.
4. **The permuter's 10 is measured on 211 cases.** Small, and produced entirely by spec
   respelling rather than by statement reordering — consistent with §4's finding that
   reordering cannot reach a code-generator difference.
5. **The model step has never touched a socket.** Prompt shape, sampling profile, structured
   rejection and iteration accounting are all tested; latency, tok/s, real reply quality and
   real failure modes are not, and no number in §6 or §7 depends on them.
6. **Functions are lost to symbol spelling, not to difficulty** — 17 in the shape-shared
   class (§3.1) and **207 corpus-wide, 7,445 instructions** (§10.5), up from 70 as the
   seeders reach further. Recovering them needs a way to emit a relocation against a symbol
   named `gnt4-memcpy`, which is a harness change, not a research problem, and it is still
   the cheapest extension on this list.
7. **The CFG tier's argument arity is inferred, and the inference can be wrong.** A call's
   arity is read off which argument registers the function *wrote* before it (`RegFile` in
   `seed_cfg.py`). Where MWCC passed a register through untouched, the tier under-counts —
   and where it under-counts, the emitted C is still byte-identical, because a pass-through
   argument costs no instruction. Where it over-counts, the oracle rejects. **No wrong
   arity can be recorded as a match**, but some correct C is missed.
8. **The `undefined8` narrowing rule is implemented and tested but is not on a live path.**
   `seed_cfg.narrow_undefined8()` decides from the retail bytes and refuses where a carry
   chain says the value really is 64-bit; nothing in `loop.py` consumes Ghidra C, so the
   rule has never narrowed a function that then went to the compiler. §10.6.
9. **The 713 absolute-global functions are counted as compiler-blocked on one measurement,
   not on a fix.** §10.3's relocation-type reading is taken straight from the object file
   and is not in doubt, but the *consequence* — that no C spelling reaches those functions —
   rests on it being the only thing wrong with them. When the fork emits `ADDR16_HA`/`_LO`,
   flipping `seed_cfg.ABS_GLOBAL_BLOCKED` will say how many of the 713 were only ever
   blocked by that. Until then they are a prediction, not a result.
10. **The globals the seeder names are named by the corpus, not by the game.** `datareloc`
    resolves an address to `oracle-registry.json`'s own symbol where it has one and to
    `DAT_<address>` otherwise. The oracle checks the *address*, so a match cannot be wrong —
    but the name in a recorded `src-match` file is a corpus convention, and a real
    decompilation would replace it.

---

## 10. The control-flow seeder tier

§7's first corollary said the binding constraint was the seeder, not the model. This
section is what happened when that was acted on. The tier is
[`research/tools/matching-decomp/seed_cfg.py`](../research/tools/matching-decomp/seed_cfg.py),
registered as a fourth entry in `loop.py`'s `SEEDERS`; the compiler fork and `census*` are
untouched, and `verify.py` needed no change.

```
$ python research/tools/matching-decomp/loop.py run --all-compilable \
      --max-insns 9999 --no-llm --no-permute --tag cfg-seed

RUN cfg-seed  targets=5492  wall=36.2s  compiles=379  compile_s=5.8
  MATCH_SEED               168 functions    1325 instructions
  NO_SEED                 5113 functions  372575 instructions
  UNMATCHED                211 functions    3011 instructions

$ ... --tag cfg-permute            # the permuter over what the seeder left
  MATCH_PERMUTER            10 functions      59 instructions
```

> **178 new byte-identical functions, 1,384 instructions, in 92 seconds of CPU and zero
> model calls** — and, the number that matters more, **379 functions reached the compiler
> where 15 did before.**

### 10.1 How it works

Four stages, all driven off the retail encodings and the link map:

1. **Basic-block CFG.** Leaders are the entry, every in-function branch target, and the
   instruction after every branch. Edges come from the terminator; dominator sets are the
   classic iterative fixpoint; a back edge is one whose successor dominates its predecessor.
   A branch that leaves the function's own extent is refused, not guessed. **A block
   unreachable from the entry means the link map's symbol spans more than one function** —
   100 functions and 13,648 instructions in this map do — and is refused by name rather
   than silently lifted as its first half.

2. **Structuring.** A recursive descent over the blocks in address order, accepting only
   the graph shapes MWCC's own front end produces for structured C:

   | shape | recovered from |
   | --- | --- |
   | `if (c) { A }` | a forward conditional branch over A. The emitted condition is the **negation** of the branch's, because the branch is what skips the body |
   | `if (c) { A } else { B }` | the same, where A's last block ends in an unconditional `b` past B |
   | `if (c1 && c2) { A }` | consecutive pure-compare blocks whose branches share one skip label |
   | `if (c1 \|\| c2) { A }` | the same, where every branch but the last jumps *into* the body and the last skips it. The skip label is then the **last** branch's target; reading it off the first is what makes a `\|\|` look unstructured |
   | `return;` / `return e;` | `blr`, a conditional `bXXlr`, or a branch to the epilogue |

   A short-circuit operand has to be a **pure** compare — a block with no side effect —
   because C evaluates it conditionally and a statement cannot be hoisted out of a
   condition. The probe that tests this runs on a copy of the register state, so a rejected
   block leaves nothing behind. Float relational operators arrive as `fcmpo` plus a
   CR-logical (`cror cr0eq, cr0gt, cr0eq` then `bne` is `<`), so CR bits are modelled
   individually rather than as one compare.

   **The output is structured C, never `goto`.** Not a style preference: MWCC's codegen for
   a `goto` is not its codegen for an `if`, so a `goto` candidate cannot match and emitting
   one would spend a compile to prove it.

3. **Calls across the `bl` boundary.** The callee is named from the link map. The arguments
   are the argument registers the function **wrote** since the last call boundary, with
   unwritten registers below that high-water mark passed through — at entry r3–r10 all hold
   an argument, so "which registers hold a value" says nothing and "which registers this
   function just set up" says everything. At every call the EABI's volatile set (r0, r3–r12,
   f0–f13, every condition register) is killed, so a value that survives a call has to be in
   r14–r31 — which the tier models as an ordinary register, and which is therefore free. A
   call's *result* is inlined into its single use when that use is the next thing to happen;
   otherwise the call becomes its own statement and its value is **spent**, and reading it
   again refuses by name, because naming it twice needs a local variable. `mtctr`+`bctrl`
   through a structure field becomes a declared function-pointer member, so the C says what
   the bytes say instead of casting an `int`.

4. **Emission.** One struct per pointer argument and per loaded pointer field, at exact byte
   offsets, with each field's width and signedness read off the load and store encodings —
   an `lbz` followed by `extsb` is `char`, without it `unsigned char`. Prototypes for every
   callee, `extern` declarations for every global. The whole thing is parameterised the way
   the `leaf` seeder is, so the permuter's spec variants respell return and argument types
   without re-deriving from the bytes.

### 10.2 The compiler's envelope, measured before anything was built

Twenty-five hand-written C fragments through `mwcc-rs` build 2.7, to find out what is worth
emitting at all:

| accepted | refused |
| --- | --- |
| `if`, `if`/`else`, nested `if`, early `return`, `&&`, `\|\|`, `switch`, direct and indirect calls, a call's result stored or returned, a value live across two calls, float fields and float arithmetic, float and pointer compares, shifts and masks, `p[i]` | **`while`, `for`, `do`** — every spelling answers `loop codegen is not implemented yet (roadmap)`; also `int t = …;` inside a `void` function, and `?:` |

That measurement is why **the tier refuses every loop up front and classes the refusal
`compiler`**. Attempting them would cost one compile each to be told the same thing, and —
which matters more — it would file 768 functions in the wrong queue.

### 10.3 Globals: an integrity rule that was lifted, and a compiler bug that replaced it

This tier was built under §2.3's rule — a match resting on a data relocation is vacuous,
because `match.py` name-checked only `R_PPC_REL24` — and it therefore refused every r13/r2
and every `lis`/`addi` global. **That rule is gone.** `research/tools/matching-decomp/datareloc.py`
recovers `_SDA_BASE_` (0x8043b5a0) and `_SDA2_BASE_` (0x8043ea20) two independent ways and
cross-checks them, resolves a candidate's data-relocation symbol back to an absolute
address, and `match.py` now requires that address to equal the one the retail encoding
names. A wrong global is a MISMATCH; an unresolvable one is `MATCH_UNVERIFIED`; neither can
become a MATCH.

So the seeder now **names the global and lets the oracle judge it**:

```c
/* src-match/game/__set_debug_bba.c -- li r0,1 / stb r0,-0x7b08(r13) / blr */
extern char DAT_80436498;

void f(void)
{
    DAT_80436498 = 1;
}
```

The integrity refusal that cost 1,212 functions and 50,194 instructions before this landed
is down to **zero**. What replaced it is smaller, sharper, and belongs to the compiler lane:

> **mwcc-rs 2.7 emits the wrong relocation types for an absolutely addressed global.**
> Read straight out of the object file, with the project's own flags:
>
> | C | relocations emitted | correct? |
> | --- | --- | --- |
> | `extern int G; return G;` | `(+0x00, 109 R_PPC_EMB_SDA21, G)` | yes |
> | `extern void h(void); h();` | `(+0x0c, 10 R_PPC_REL24, h)` | yes |
> | `struct {char p[8]; int v;} G; return G.v;` | `(+0x02, 6 R_PPC_ADDR14, G)`, `(+0x06, 4 R_PPC_ADDR16_HI, G)` | **no** |
>
> The `lis …@ha` should carry `R_PPC_ADDR16_HA` (5) and the `addi …@l` `R_PPC_ADDR16_LO`
> (3). Both come out exactly one higher, and the offsets point at the immediate halfword
> rather than the instruction. Two consequences, neither reachable from the C: `objdiff`
> masks `R_PPC_ADDR14` with `0xFFFC`, so two bits of the `lis` immediate stay unmasked and
> the word can never compare equal; and `datareloc` cannot address-check a type it does not
> model, so even a byte-equal candidate would only be `MATCH_UNVERIFIED`.

Small-data globals are unaffected — their `R_PPC_EMB_SDA21` is correct — and they are
emitted normally, which is where most of this tier's new matches come from. Absolute
globals are a **`compiler` refusal** today, in exactly the sense loops are, gated behind
`seed_cfg.ABS_GLOBAL_BLOCKED` so that re-enabling them is one line. **713 functions and
31,483 instructions are behind that one bug.**

The `bctr` switch tables are in the same set: a jump table is reached through its own
address, so all 117 functions and 32,934 instructions of `switch` wait on the same fix.

### 10.4 Per-shape results

*Attempted* is every function unmatched before this tier. *m@0* matched on candidate 0;
*m@p* matched by the permuter; *compiled* reached the compiler and did not match; the
refusal columns are the classes of §5.1. Instruction counts on the second line of each row.

| shape | attempted | m@0 | m@p | compiled | r: seeder | r: compiler |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| loop / calls | 990 | 0 | 0 | 0 | 342 | **648** |
| &nbsp;&nbsp;*instructions* | 131,085 | 0 | 0 | 0 | 71,163 | **59,922** |
| 4+ branches / calls | 894 | 0 | 0 | 1 | 781 | 112 |
| &nbsp;&nbsp;*instructions* | 93,513 | 0 | 0 | 51 | 82,639 | 10,823 |
| 2–3 branches / calls | 586 | 0 | 0 | 7 | 436 | 143 |
| &nbsp;&nbsp;*instructions* | 28,352 | 0 | 0 | 234 | 21,386 | 6,732 |
| single `if` / early return, calls | 710 | 5 | 2 | 34 | 455 | 214 |
| &nbsp;&nbsp;*instructions* | 25,682 | 67 | 21 | 684 | 17,356 | 7,554 |
| `switch` (`bctr`) / calls | 86 | 0 | 0 | 0 | 86 | 0 |
| &nbsp;&nbsp;*instructions* | 19,844 | 0 | 0 | 0 | 19,844 | 0 |
| **straight-line / calls** | 879 | **88** | 0 | 86 | 550 | 155 |
| &nbsp;&nbsp;*instructions* | 19,101 | **969** | 0 | 1,266 | 13,969 | 2,897 |
| loop / leaf | 228 | 0 | 0 | 0 | 109 | **119** |
| &nbsp;&nbsp;*instructions* | 18,845 | 0 | 0 | 0 | 7,241 | **11,604** |
| `switch` (`bctr`) / leaf | 31 | 0 | 0 | 0 | 31 | 0 |
| &nbsp;&nbsp;*instructions* | 13,090 | 0 | 0 | 0 | 13,090 | 0 |
| 4+ branches / leaf | 185 | 0 | 0 | 1 | 165 | 19 |
| &nbsp;&nbsp;*instructions* | 12,305 | 0 | 0 | 17 | 11,026 | 1,262 |
| **straight-line / leaf** | 547 | **64** | 5 | 59 | 419 | 0 |
| &nbsp;&nbsp;*instructions* | 5,713 | **203** | 20 | 607 | 4,883 | 0 |
| 2–3 branches / leaf | 155 | 1 | 0 | 3 | 129 | 22 |
| &nbsp;&nbsp;*instructions* | 5,377 | 14 | 0 | 33 | 4,260 | 1,070 |
| single `if` / early return, leaf | 201 | 10 | 3 | 11 | 128 | 49 |
| &nbsp;&nbsp;*instructions* | 4,004 | 72 | 18 | 115 | 2,548 | 1,251 |
| **TOTAL** | **5,492** | **168** | **10** | **202** | **3,631** | **1,481** |
| &nbsp;&nbsp;***instructions*** | **376,911** | **1,325** | **59** | **3,007** | **269,405** | **103,115** |

**Two things this table says, in order of how much they should change what happens next.**

1. **The `bl`-crossing evaluator and the globals paid; the structuring has not, yet.** 157
   of the 178 matches are in the two *straight-line* rows — functions the old seeders could
   not reach only because they modelled one call, no callee-saved register, no use of a
   call's result and no global. The branching rows contribute 21 matches and **56 functions
   that reached the compiler and were refused there**. Structuring works; the code generator
   behind it is what is not ready.
2. **The instruction weight is in rows with zero matches.** *loop / calls* alone is 131,085
   instructions — 35 % of everything unmatched — and every one of its 648 `compiler`
   refusals is the same missing lowering. No seeder can touch that number. §5.2's rule
   applies to this table too: read it down the instruction lines, not the function lines.

### 10.5 Who owns the remainder — the split this work exists to produce

Of the 5,492 functions unmatched before this tier, 178 are now matched. The other 5,314:

| owner | functions | instructions | % of unmatched code |
| --- | ---: | ---: | ---: |
| **the compiler lane** — refused up front on a measured limit (§10.2, §10.3) | 1,481 | 103,115 | 27.36 % |
| **the compiler lane** — reached the compiler and lost there | 151 | 2,222 | 0.59 % |
| **this seeder** — an opcode, a graph or a value it cannot express | 3,631 | 269,405 | 71.48 % |
| a genuine C difference this seeder got wrong | 51 | 785 | 0.21 % |
| the integrity rule | **0** | **0** | — |

**Compare that with §7's version of it: 15 functions and 118 instructions were the
compiler's; 1,632 functions and 105,337 instructions are now.** That is the point of the
exercise — the queue is not just bigger, it is itemised:

| the compiler lane's queue | functions | instructions |
| --- | ---: | ---: |
| `loop codegen is not implemented yet (roadmap)` | 768 | 71,632 |
| **wrong relocation types on an absolutely addressed global** (§10.3) | 713 | 31,483 |
| scheduling / register colouring / constant rematerialisation (§4's classes, unchanged) | ~100 | ~1,400 |
| `a signed char load promoted to int needs a sign-extension (roadmap)` | 17 | 309 |
| `expected a general-register leaf` | 5 | 129 |
| `an early-return continuation that materializes store values needs the store/return scheduler (roadmap)` | 4 | 33 |
| `a store scheduled around the return-value computation needs the store scheduler (roadmap)` | 4 | 188 |
| eight further diagnostics, one to three functions each | ~13 | ~230 |

And one item that is not in the compiler's own vocabulary, because the compiler does not
know it is wrong:

> **18 functions differ from retail in nothing but the order of two instructions in the
> epilogue.** Retail restores the LR before the callee-saved GPRs; `mwcc-rs` restores them
> the other way round. Every other instruction in those functions is byte-identical:
>
> ```
> 800750f0  lwz r0, 0x14(r1)     |<< lwz r31, 0xc(r1)
> 800750f4  lwz r31, 0xc(r1)     |<< lwz r0, 0x14(r1)
> 800750f8  mtlr r0              |   mtlr r0
> ```
>
> No C spelling reaches it — the permuter tried — and it is the cheapest item on the list.

This tier's own queue, largest first by instructions: `psq_st`/`psq_l` paired-single vector
code (165 functions, 33,977 instructions), the `xoris` int↔float conversion idiom (194 /
30,203), `mulhw`/`mulhwu` constant division (112 / 15,122), a call result used after another
statement, which needs a local variable (186 / 12,614), a memory base that is neither an
argument nor a loaded pointer (352 / 12,634), a branch chain that is neither a pure `&&` nor
a pure `||` (192 / 12,029), `rlwimi` bitfield insert (88 / 11,328), an unstructured forward
branch (181 / 9,293), a stack local or its address (122 / 7,775), a callee whose link-map
name is not a C identifier (207 / 7,445).

That last one is uncertainty 6 of §9 seen at this tier's scale, and it remains the cheapest
extension available: it is a harness change, not a research problem.

### 10.6 The `undefined8` narrowing rule

The compiler census (`docs/matching-compiler-census.md` §2a) measured that 683 functions
refused for `this long long shape is not modeled yet` compile the moment Ghidra's
`undefined8` placeholder is narrowed to 32 bits. That is a materialisation choice, so it
belongs to a seeder — but **this seeder never reads Ghidra's types**; it derives every width
from the retail encoding, so it cannot inherit the bug at all. What it can contribute is the
*evidence rule*, and `seed_cfg.narrow_undefined8()` implements it for the Ghidra-seeded path:

> A value is 64-bit only if the retail bytes contain an operation only a 64-bit value would
> need: a true 64-bit opcode (`ld`, `std`, `rldicl`, `sradi` — a Gekko executes none of
> them, so that half of the test exists to catch a mis-decode rather than to fire), **or the
> carry chain a 32-bit target uses for `long long` arithmetic** (`addc`/`adde`,
> `subfc`/`subfe`, `addze`/`addme`). Otherwise `undefined8` is a placeholder and narrows to
> 32 bits.

Measured over the whole link map: **133 of 5,897 `.text` functions carry such evidence;
5,764 do not** — which is why the census's 683 reads as a floor rather than a coincidence.
The rule is deliberately conservative in the safe direction: `addze` also appears in MWCC's
constant-division idiom, so some of those 133 are refused when they need not be. Refusing
costs a compile that would have failed anyway; narrowing a value that really is 64-bit would
silently mistype it, and that is the error worth avoiding. Covered by selftest group S11;
**not yet on a live path** (§9.8), because nothing in `loop.py` consumes Ghidra C.

### 10.7 What this tier cost, and what it did not touch

| | |
| --- | --- |
| seed-only over 5,492 functions | **36.2 s wall**, 379 compiles, 5.8 s inside the compiler |
| seed + permuter | **55.9 s wall**, 4,095 compiles |
| cost per new match | **~0.5 s of CPU** |
| model calls | **0** |
| `loop.py selftest` | **71 ok, 0 failed** (was 48; S10 and S11 are new) |
| `src-match/verify.py --control` | **586 ok, 0 failed** |

CPU only. The GPU lease, the model server, the supervisor and the live pipeline state were
not touched; nothing was downloaded; the retail GCM was read and never written.
