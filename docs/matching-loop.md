# The matching-decompilation loop

**Date: 2026-09-04.** Status: **BUILT AND RUN. 392 new functions are byte-identical to
retail, and the loop that produced them never called a model.**

Companion documents: [`docs/matching-decompilation-spike.md`](matching-decompilation-spike.md)
(the feasibility spike this implements, whose §4.1 sketched the loop and whose §4.2
priced it at 2.6 GPU-years) and
[`research/tools/matching-decomp/TOOLCHAIN.md`](../research/tools/matching-decomp/TOOLCHAIN.md)
(the compiler).

> | | |
> | --- | --- |
> | **392 new matches, 0 model calls** | The matched corpus goes from 13 functions to **405**; from 43 instructions to **1,773**. Every one was produced mechanically and re-proved by `src-match/verify.py`. §3 |
> | **96.3 % matched at iteration 0** | Of the 407 functions the seeder could express, **392 matched on candidate 0** — one 20 ms compile each, no model, no iteration. §3.2 |
> | **The permuter closed nothing — and that is the finding** | 580 mechanical mutants across 15 near-misses, **0 matches**. Every one of the 15 was then shown to be a *compiler* limit, not a C difference, so no C spelling could have closed them. §4 |
> | **The free-win fraction corpus-wide is 6.9 % of functions and 0.25 % of instructions** | Seed-only across all 5,897 link-map functions. §5.2's warning about counting functions is now attached to this loop's own numbers. §5 |
> | **The 2.6 GPU-year figure barely moves: 2.63 → 2.62** | The free stages remove **41 of 23,024 GPU-hours — 0.18 %** — because 96 % of that cost is the *moderate*, *hard* and *research* tiers, which this loop cannot touch. §7 |
> | **The oracle had a second hole, and it is now closed** | A candidate whose match rests on a data relocation has that operand *masked and never name-checked* — it would accept any global in the game. Such verdicts are now `MATCH_UNVERIFIED` and are never recorded. §2.3 |
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

Three seeders, tried in order:

| seeder | what it handles | matched |
| --- | --- | ---: |
| `empty` | a bare `blr` → `void f(void) {}` | 118 |
| `wrapper` | the Metrowerks non-leaf frame with exactly one `bl`, with `li`/`mr` argument setup; the callee's name comes from the link map | 134 |
| `leaf` | straight-line leaves: loads, stores, immediates, register moves, sign extension, and one leading null guard compiled to `beqlr` | 140 |

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
which is why the corpus contains no global accessors even though `lwz r3, d(r13); blr` is
among the easiest shapes in the binary. **That is a deliberate 104-function loss taken to
keep the corpus honest**, and it is the price of the standard the spike set: byte equality,
no tolerance, no "close enough".

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

| | before this work | after |
| --- | ---: | ---: |
| functions | 13 | **405** |
| instructions | 43 | **1,773** |
| share of `.init` + `.text` (701,464 instructions) | 0.0061 % | **0.2528 %** |
| share of the 5,897 link-map `.text` functions | 0.22 % | **6.87 %** |

Of the 405: **390 are game code, 15 are SDK** (`gnt4-` prefixed, kept in `src-match/sdk/`).

### 5.1 Why the other 5,477 got no seed

| count | refusal |
| ---: | --- |
| **4,721** | **undecoded instruction** — the seeder's decoder models about two dozen opcode forms; these functions use others |
| 176 | a decoded instruction the leaf seeder does not model (`lis`, `lfs`, `stfs`, `or`, `addi`, …) |
| 174 | more than one `bl` (2 calls: 82, 3: 35, 4: 14, 5+: 43) |
| 132 | argument setup the wrapper seeder does not model (`lis`, `lwz`, `addi`, `li`) |
| 104 | r13/r2 small-data access — the integrity refusal of §2.3 |
| 70 | the callee's name is not a C identifier, or its address is in no map symbol |
| 57 | no single LR spill (a different frame shape) |
| 43 | other (no `blr` terminator, non-Metrowerks prologue/epilogue, base register not an argument) |
| **5,477** | |

**Read that first row correctly.** It is a statement about *this loop's seeder*, not about
the compiler and not about the binary. The corpus-wide free-win fraction measured here —
6.9 % of functions, 0.25 % of instructions — is the ceiling of a mechanical seeder that
models 21 opcode forms, and it would rise with every form added. It is **not** an estimate
of how much of the game is matchable.

### 5.2 The instruction-weighted view, as §5.2 of the spike demands

> **405 functions is 6.87 % of the link map's entry points and 0.2528 % of the
> instructions.**

Thirty-one times the functions the spike matched, and still a quarter of one percent of the
game. The spike warned that a loop which only solves short functions can report a large
function-percentage having touched almost none of the code. **This loop is the extreme case
of that warning**: its mean matched function is 4.4 instructions against a corpus mean of
58.2. Report this work by instructions.

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
| **total** | **390** | **41.2** |

> **23,024 → 22,983 GPU-hours. 2.63 → 2.62 GPU-years. A 0.18 % reduction.**

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
cd D:/GotYaForce/.claude/worktrees/agent-a20c7a247b0f7f0bc
export MWCC_RS=".../.tools/mwcc-rs/target/release/mwcc.exe"   # TOOLCHAIN.md §1

# the loop's own tests: 48 checks, no network; S9 needs the compiler, the rest do not
python research/tools/matching-decomp/loop.py selftest

# the shape index, measured (not taken from the spike)
python research/tools/matching-decomp/loop.py shapes --top 20

# one function, end to end
python research/tools/matching-decomp/loop.py seed --function zz_02650c0_ --check

# the three runs this document reports, in order
python research/tools/matching-decomp/loop.py run --class shape-shared --no-llm \
    --tag shape-shared
python research/tools/matching-decomp/loop.py run --all-compilable --max-insns 9999 \
    --no-llm --no-permute --tag all-compilable-seed
python research/tools/matching-decomp/loop.py run --all-compilable --max-insns 9999 \
    --no-llm --tag all-compilable-permute

# re-prove all 405 matches plus the three negative controls
python src-match/verify.py --control          # 408 ok, 0 failed
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
   the difference on this machine. This is the spike's uncertainty 1 and 392 more functions
   now rest on it. If `mwcc-rs` diverges from the genuine compiler on any of these shapes,
   those matches are wrong and nothing here would say so. `verify.py` is what re-tests them
   when a better compiler arrives.
2. **The `blr`-only functions are the weakest entries in the corpus.** 118 of the 405 are a
   single `blr` matched by `void f(void) {}`. That is a true statement about the bytes and a
   very thin statement about the program: the retail function may be an empty virtual
   override, a stub, or padding. They are counted here because the oracle's standard is byte
   equality and they meet it, but a reader weighting this corpus by *information* should
   discount them — they are 29 % of the functions and 6.7 % of the instructions.
3. **The corpus-wide free-win fraction is a floor, not a ceiling.** 4,721 of 5,477 refusals
   are the seeder's own decoder coverage. A wider decoder raises the number; nothing here
   bounds how far.
4. **The permuter's zero is measured on 15 cases.** That is enough to say the stage adds
   nothing *today* and not enough to say it never will — its intended customer is an LLM
   near-miss, and no LLM has run.
5. **The model step has never touched a socket.** Prompt shape, sampling profile, structured
   rejection and iteration accounting are all tested; latency, tok/s, real reply quality and
   real failure modes are not, and no number in §6 or §7 depends on them.
6. **Functions are lost to symbol spelling, not to difficulty** — 17 in the shape-shared
   class (§3.1) and **70 corpus-wide** (§5.1). Recovering them needs a way to emit a
   relocation against a symbol named `gnt4-memcpy`, which is a harness change, not a
   research problem, and it is the cheapest extension on this list.
