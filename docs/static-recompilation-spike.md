# Static recompilation — feasibility spike

**Date: 2026-09-02.** Status: **SPIKE RESULT.** Everything below was measured in this
worktree today by the tools in [`research/tools/static-recomp/`](../research/tools/static-recomp/).
Nothing here is a claim about the port: no unit was promoted, no driver state was touched,
no pipeline artifact was modified. The two verification artifacts this spike produced are
labelled `route: static_recompilation` and are not comparable with, and must never be
summed with, any wasm-unit verification tier.

---

## 0. The question, and the answer

[`docs/one-to-one-completion-spec.md`](one-to-one-completion-spec.md) measures a pipeline
that is not converging: 6.0 % of functions are `oracle_green`-eligible, `oracle_green` is
vacuous for 40.7 %, 0 units were promoted by the last sweep, the driver's verification lane
returns `[]` on every pass, and the failure census is dominated by **Ghidra inference
errors** rather than port bugs. Every fix is one instance of an unbounded class, because
Ghidra's C is an *inference about* the machine code.

This spike asked whether translating each PowerPC instruction **mechanically** removes the
inference. Six questions were posed. All six were answered with working code.

**VERDICT: static recompilation is a credible route, and it is a better route than the
current one.** The full argument is §6. The short form:

| | Ghidra-C + LLM route | Static recompilation |
| --- | --- | --- |
| Functions convertible with **zero human input** | 6.0 % auto-speccable; 0 promoted last sweep | **98.5 %** of 11,972 entry points translate whole today (§4.1) |
| Instructions with no mechanical translation | not measurable — inference has no bound | **3,256 of 699,828 = 0.465 %** (§1) |
| Verified against console evidence in this spike | — | **2 of 2 functions attempted, both PASS** (§3) |
| Wasm size | 1 unit + 1 composed artifact today | **36.6 MB raw / 4.0 MB gzip** for the whole DOL (§4.3) |
| Required linear memory | 2,155,479,040 B, growth disabled, "not a tuning knob" | **24 MiB** (§4.4) |
| DVD code overlays (the classic recomp killer) | — | **0 `.rel` modules on the disc** (§4.6) |

What static recompilation does **not** fix: the GX host, the DVD host, the missing MusyX
mixer, and the framebuffer-equivalence ceiling. Those are the same work on either route
and they are §5.3.

---

## 1. Instruction inventory — the go/no-go number

Tool: [`research/tools/static-recomp/dol_inventory.py`](../research/tools/static-recomp/dol_inventory.py).
Artifact: [`research/decomp/data/static-recomp-inventory.json`](../research/decomp/data/static-recomp-inventory.json).
Reads `boot.dol` straight out of the retail GCM at the file offset in the BE u32 at `0x420`
— the same layout logic as `research/tools/dolphin-trace/capture_common.py:Dol`, so the
input is the same ROM the capture stack reads.

### 1.1 The image

| | |
| --- | ---: |
| Text sections | 2 |
| — `.init` @ `0x80003100` | 9,440 B / 2,360 instructions |
| — `.text` @ `0x800055e0` | 2,796,416 B / 699,104 instructions |
| Zero padding words | 1,636 |
| **Total instructions** | **699,828** |
| Data sections | 6, 1,082,816 B |
| `.bss` | `0x803af140`, 582,632 B |
| Entry point | `0x80003154` |
| Distinct **encoding forms** | **169** |

### 1.2 A correction that changes the headline number

capstone 5.0.1 in `CS_ARCH_PPC / CS_MODE_32 | CS_MODE_BIG_ENDIAN` **is wrong about this
CPU in two ways**, and a naive histogram inherits both:

1. **Primary opcodes 4 / 56 / 57 / 60 / 61 are AltiVec and VSX on a 64-bit POWER core and
   are the paired-single unit on Gekko.** capstone renders `psq_st` as `xxsel`, `ps_sel`
   as `vsel`, `ps_add` as `xsaddsp`. **1,087 paired-single instructions** were silently
   classified as ordinary. The first run of this tool reported 1,796 paired-single
   instructions; the correct number is **2,877**.
2. **`fcmpo` (primary 63, XO 32) is rejected outright** — 3,930 instructions, which MWCC
   emits for every ordered float comparison and which is the second most common FP form in
   the DOL.

`dol_inventory.py` now checks the primary opcode **before** believing the disassembler
(`gekko_override`), and `undecoded_probe.py` / `op63_probe.py` are the probes that found
it. This is worth stating plainly because it is the kind of error that would have made a
go/no-go decision on a wrong number.

### 1.3 The histogram

Shares are of the 699,828 real instructions.

| Class | Count | Share | What a translator does with it |
| --- | ---: | ---: | --- |
| `EASY` | 525,020 | 75.02 % | one C expression over the register file |
| `BRANCH` | 65,253 | 9.32 % | `goto` a label |
| `CALL` | 41,349 | 5.91 % | C call through the entry-point table |
| `SPR` | 24,582 | 3.51 % | `mflr`/`mtlr`/`mtctr` are struct fields; the rest is a named host hook |
| `FPU_IEEE` | 20,971 | 3.00 % | C `double` |
| `RETURN` | 14,685 | 2.10 % | `return` |
| **`PAIRED_SINGLE`** | **2,877** | **0.41 %** | **needs a Gekko SIMD model** |
| `INDIRECT` | 2,728 | 0.39 % | table lookup (§4.5) |
| `FMA` | 1,800 | 0.26 % | `__builtin_fma` — one rounding, not two |
| `PADDING` | 1,636 | 0.23 % | — |
| **`FP_NONIEEE`** | **216** | **0.03 %** | **`frsqrte`/`fres`: needs Dolphin's estimate tables** |
| **`SUPERVISOR`** | **148** | **0.02 %** | **`mfmsr`/`mtmsr`/`rfi`/`mtsr` — 59 in `.init`, 89 in `.text`** |
| `CACHE` | 131 | 0.02 % | `dcbz` is semantic (zero 32 B); the rest are no-ops |
| `SYNC` | 53 | 0.01 % | no-op |
| `UNKNOWN` | 12 | 0.00 % | data words inside `.init` |
| **`SYSCALL`** | **3** | **0.00 %** | **`sc` — OS trap** |

> ### **HARD INSTRUCTION COUNT: 3,256 of 699,828 — 0.465 %.**
>
> `PAIRED_SINGLE` + `FP_NONIEEE` + `SUPERVISOR` + `SYSCALL` + `UNKNOWN`.
>
> **ATTENTION count: 29,241 — 4.178 %.** `SPR` + `INDIRECT` + `FMA` + `CACHE`: mechanical,
> but each needs one named decision in the translator rather than a blind table row.

### 1.4 How big the table has to be

Artifact: [`research/decomp/data/static-recomp-forms.json`](../research/decomp/data/static-recomp-forms.json).
Keyed on the **encoding**, not the printed mnemonic, because a recompiler's table does not
care that a disassembler prints `li`, `mr`, `nop`, `slwi` and `clrlwi` for what are three
encodings.

| Coverage of all instructions | Encoding forms needed |
| --- | ---: |
| 90 % | 24 |
| 99 % | 65 |
| 99.9 % | 109 |
| 99.99 % | 147 |
| **100 %** | **169** |

**169 forms is the whole job.** The spike's translator implements 134 of them.

### 1.5 Where the hard instructions live

- **Paired single: 2,877 instructions in 608 of 11,972 functions (5.08 %).** Concentrated,
  and the bulk is load/store (`psq_l` 1,264, `psq_st` 295) rather than arithmetic — the
  quantised load/store forms, whose scale and type come from GQR0..7 (SPR 912–919). The
  spike's register file already models the GQRs for that reason.
- **Supervisor: 59 of 148 are in `.init`** (the OS boot path a high-level-hosted port never
  runs); the other 89 are the SDK's `OSDisableInterrupts`/`OSEnableInterrupts` family, which
  every high-level port stubs.
- **`sc`: 3 sites**, all in the SDK's OS trap wrappers.
- **`UNKNOWN`: 12 words**, all inside `.init` — data in text, at `0x800034ac` and
  `0x8000554c`+.

---

## 2. Translating a real function, mechanically

Tool: [`research/tools/static-recomp/ppc_recomp.py`](../research/tools/static-recomp/ppc_recomp.py) —
721 lines. Runtime: [`rt/ppc_rt.h`](../research/tools/static-recomp/rt/ppc_rt.h) +
[`rt/ppc_rt.c`](../research/tools/static-recomp/rt/ppc_rt.c) — a register file, memory
accessors, and an entry-point table. That is the entire machine model.

**Target: `zz_0027c34_` @ `0x80027c34`** — the project's GX proof draw, 99 instructions,
14 encoding forms, one branch target. Generated source:
[`generated/zz_0027c34_.c`](../research/tools/static-recomp/generated/zz_0027c34_.c).

Every statement carries the address and encoding it came from:

```c
    /* 80027c34  9421ffc0  stwu r1, -0x40(r1) */
    { uint32_t ea = (c->r[1] + (uint32_t)-64); ppc_w32(c, ea, c->r[1]); c->r[1] = ea; }
    /* 80027c40  806d8390  lwz r3, -0x7c70(r13) */
    c->cia = 0x80027c40u; { uint32_t ea = (c->r[13] + (uint32_t)-31856); c->r[3] = ppc_r32(c, ea); }
    /* 80027c4c  40820164  bne 0x80027db0 */
    if ((ppc_crbit(c, 2) == 0)) goto L_80027db0;
```

### 2.1 What the generator is *not* given

No decompiler output. No parameter list, no return type, no struct layout, no `undefined4`,
no `float afStack_38[14]`. A recompiled function is `void fn_80027c34(ppc_ctx *)`;
arguments live in r3.. because the ABI put them there, not because anything decided a
signature.

The one machine-state input the function needs is **r13, the small-data-area base**, and it
comes out of the ROM's own `__init_registers`:

```
8000332c  lis  r2, -0x7fbd      ->  r2  = 0x8043ea20
80003334  lis  r13, -0x7fbd     ->  r13 = 0x8043b5a0
80003338  ori  r13, r13, 0xb5a0
```

`r13 - 0x7c70 = 0x80433930`, `r13 - 0x5498 = 0x80436108`, `r13 - 0x5494 = 0x8043610c` —
the three globals the console capture recorded this function reading. Derived from the
ROM, not from the capture.

### 2.2 Three things the translation gets right *by construction*

1. **The write-gather pipe needs no lowering pass.** The ROM submits vertices with
   `sth r5, -0x8000(r4)` where `r4 = 0xcc010000`. In the Ghidra-C route this is a store to
   a literal address outside the module's linear memory, so it traps; the assembly gate has
   a dedicated opt-in **source-rewriting pass** (`port_wgpipe_lowering.py`) that must
   constant-fold the address, and **fails the whole window closed** when it cannot. In a
   recompiler the store goes through `ppc_w16()`, which range-tests the **resolved** EA.
   One `if`, in one place, for every store in the game.
2. **Float-vs-integer store width is an instruction fact.** `gf_gx_wgpipe.h` has to recover
   "floatness" from the C type Ghidra guessed for the stored expression, using `_Generic`
   and eleven `_Static_assert`s. `stfs` and `stw` are different opcodes.
3. **A stack-local pointer is just a pointer.** `gnt4_PSMTXIdentity_bl(afStack_38)` passes
   `r1 + 8`. The recompiled function has its own PPC stack **inside the arena**, so the
   value it passes is a GameCube address of the same shape the console passed. This is
   gap **E4** — 56 exports across 39 units that can never compare by value — and it does
   not arise here (§3.1 measures it).

---

## 3. Verification against the console

Two different standards, two different capture tools, two different functions. Both replay
existing committed console captures. Neither involved a hand-authored spec.

### 3.1 `gx_callstream_green` — `zz_0027c34_`

Artifact: [`research/decomp/data/oracle-results/static-recomp.zz_0027c34_.gx-callstream.json`](../research/decomp/data/oracle-results/static-recomp.zz_0027c34_.gx-callstream.json).
Capture: `research/decomp/oracle-harness/corpora/gx-rom-unit.zz_0027c34_.gx-callstream.jsonl`
(bundled Dolphin 2606-97, live 2v2 battle savestate, 2026-08-31). Comparator:
[`compare_callstream.py`](../research/tools/static-recomp/compare_callstream.py), rules
transcribed from `research/decomp/oracle-harness/run-gx-callstream.mjs:225-270`.

Built with the pinned emsdk (`research/tools/emsdk`, `-O1 -std=c11`), run under the pinned
node 24.19.0.

> **VERDICT PASS. 4/4 invocations. 76/76 calls. 48/48 write-gather-pipe writes. 8/8
> stack-relative arguments.**

Every call matched on **callee, call-site address, arity and every argument value**; every
pipe write matched on **store-site address, width and value**.

The stack-relative check is real, not an accident: the harness starts the recompiled
function with `r1 = 0x81200000`, which is **deliberately not** the console's
`entry_sp = 0x8044d510`. `gnt4_PSMTXIdentity_bl` therefore receives `0x811fffc8` where the
console passed `0x8044d4c8` — and both are `sp+8`, which is what the standard compares.

**Negative controls.** A verification that cannot fail proves nothing.

| Mutation | Result |
| --- | --- |
| one translated instruction changed (`li r3,2` → `li r3,3` at `0x80027c5c`) | **fail** — `event 0 (gnt4_GXSetCullMode_bl) arg 0: console 0x00000002, port 0x00000003` |
| the seeded guard flag `DAT_80436108` cleared to 0 | **fail** — `console emitted 31 event(s), port emitted 0` |

The second control matters more than it looks: it proves the recompiled code **evaluates
the ROM's guard against seeded memory** rather than having the draw path baked in.

**What was supplied to the host, and nothing else was** (`gen_spike_host.py` docstring
enumerates it): the 17 SDK callee addresses from the capture's own binding map; their
arity from the project's existing hand-written `gnt4_gx_decls.h`; the console's own bytes
at the six addresses it read; and `r13` from the ROM. No signature for the function under
test.

### 3.2 `transcript_green` — `FUN_800c4468`, and what it exposes

Artifact: [`research/decomp/data/oracle-results/static-recomp.FUN_800c4468.transcript.json`](../research/decomp/data/oracle-results/static-recomp.FUN_800c4468.transcript.json).
Capture: the corrected re-capture in
`research/decomp/transcript-preflight/auto-c0020-007-FUN_800c4468/`. Replay contract copied
from `run-transcript.mjs` including `applyDeltas` (the stubbed callee's memory effect is
replayed, not computed).

> **VERDICT PASS. 24/24 cases. 48/48 calls.**
>
> Negative control (`lwz r3, 0xe0(r3)` → `0xe4`): **fail** at case 0 call 0 arg 0.

**This is the spike's most consequential single result**, because of what this function is.
`FUN_800c4468` is 16 instructions:

```
800c4478  mr    r31, r3
800c447c  addi  r4, r31, 0x114
800c4480  lwz   r3, 0xe0(r3)
800c4484  bl    0x800076d0
800c4488  lwz   r3, 0xe0(r31)
800c448c  li    r4, 0x44
800c4490  bl    0x800097b4
```

One pointer argument in r3. Ghidra typed it with **sixteen parameters** — an `undefined8`
plus seven invented `double`s plus eight integer slots — the varargs-assert mis-lift that
gap **E11** measures on **1,514 of 10,954 registry functions**. The consequence in the
staged port's own source is not cosmetic:

```c
/* research/decomp/port-units-staging/auto-c0020-007/unit.c:100 */
zz_00076d0_(param_1, param_2, ..., param_8, *(int *)(param_9 + 0xe0), (float *)(param_9 + 0x114), ...)
```

`param_9` allocates to **r5** under the EABI. The ROM reads `[r3 + 0xe0]`. In the recorded
console state r3 = `0x8065c600` and r5 = `0x803bb150` — **a different object entirely**.
The port was reading the wrong memory and calling its callee with a sixteen-value argument
list the machine never assembled.

Closing that cost the project a full sanctioned **corpus correction**: a source edit in
`chunk_0020.c` *and* in `chunk_0000.c` for the callee whose invented signature Ghidra had
propagated, a preflight build, and a live re-capture — and E7 records that the proven fix
is **still stalled** because the driver cannot rebuild the staged artifact.

The recompiler emitted the correct code on the first pass, from the instruction encodings,
with no human in the loop. It could not be wrong about this, because there is no signature
to be wrong about.

One further finding, recorded because it is load-bearing for how captures are authored:
**the original corpus for this function is not replayable against a faithful execution.**
`research/decomp/oracle-harness/corpora/auto-c0020-007.FUN_800c4468.transcript.jsonl` seeds
three 512-byte windows at `0x803bb150` / `0x803c0000` / `0x803f53a0`, derived from the
mis-lifted argument list; the object the ROM actually dereferences, at `0x8065c600`, is
seeded in none of them. The corrected re-capture seeds exactly one window — `0x8065c600`,
`from_arg: 0` — and declares `params: ["i32"]`. **A capture plan derived from an inferred
signature inherits that signature's errors into its watch set**, which is a class of
false-negative distinct from the three P6 already records.

---

## 4. Measured costs and blockers

### 4.1 How much of the game translates today

Tool: [`batch_recomp.py`](../research/tools/static-recomp/batch_recomp.py). Artifact:
[`research/decomp/data/static-recomp-batch.json`](../research/decomp/data/static-recomp-batch.json).
Every entry point in `oracle-registry.json` (10,954 functions + 1,018 excluded, including
the 996 `gnt4_*` SDK functions) is translated in memory, capped at the next entry point.

| | |
| --- | ---: |
| Entry points attempted | 11,972 |
| **Translated whole, zero human input** | **11,795 (98.5 %)** |
| Instructions translated | 653,423 |
| Blocked | 177 |
| Encoding forms the translator emitted | 134 |

Everything that blocks, and its size:

| Count | Reason | Cost to close |
| ---: | --- | --- |
| 134 | `frsqrte` / `fres` — the GameCube's estimates are table-driven and are **not** `1/sqrt(x)` and `1/x` | port two lookup tables from Dolphin |
| 32 | function-extent walk (a next-entry cap of 4–216 bytes; aliased or mis-registered entries) | boundary discovery, not translation |
| 9 | byte-reversed load/store and segment-register forms not yet in the table (XO 662/534/918/595/210) | one line each |
| 3 | `sc` | HLE |
| 1 | `rfi` | HLE |

The 177 blocked functions are **1.5 %**, and 134 of them are one bounded task. The point is
not that the number is small; it is that **every remaining item is a named, finite table
row**, whereas the current route's failure census is "Ghidra inferred something wrong" and
has no enumeration.

Note the denominator: this includes the **996 `gnt4_*` SDK functions the current corpus
excludes by design**. A recompiler translates the SDK because the SDK is in the DOL. Gap
**H8** — "there is no SDK shim ledger; 6 seeded, 17 declared, 6 conflicting including a real
f64/i64 split on `gnt4_PSMTXConcat_bl`" — does not exist on this route.

### 4.2 Coverage of the text section

653,423 translated instructions against 699,828 in text is **93.4 %**. The residue is text
not covered by any registry entry point. Whole-program recompilation needs its own
boundary-discovery pass (linear sweep + the `bl` target set + the code pointers in §4.5);
the registry is a convenience here, not a dependency.

### 4.3 Wasm size

Tool: [`size_probe.py`](../research/tools/static-recomp/size_probe.py). Artifact:
[`research/decomp/data/static-recomp-size.json`](../research/decomp/data/static-recomp-size.json).
1,500 real ROM functions / 101,229 instructions, emitted, linked with the pinned emsdk at
`-O2`, measured by wasm section.

| | |
| --- | ---: |
| Sample module | 5,294,051 B (code section 5,276,458 B) |
| **Bytes of wasm per PowerPC instruction** | **52.1** |
| gzip | 573,097 B → **5.66 B/instruction** |
| **Projected, whole DOL text (699,828 instructions)** | **36.6 MB raw / 4.0 MB gzip** |

4 MB over the wire is a smaller download than the game's own `opening.bnr`-adjacent assets
and roughly 1 % of `afs_data.afs`. Size is not a blocker.

### 4.4 The memory model — a constraint that disappears

The Ghidra-C route's shim casts GameCube addresses **straight to C pointers**
(`#define GC_IPTR(a) (*(int *)(unsigned int)(a))`), so the module's linear memory must
physically contain address `0x80436108`. That is why the arena is **2,155,479,040 bytes /
32,890 pages, initial == maximum, `ALLOW_MEMORY_GROWTH=0`**, and why
[`docs/composed-pilot.md:154-160`](composed-pilot.md) says "This is not a tuning knob".
Gap **C7** is that this has only ever been proven in headless Chrome on the rig.

A recompiler's memory goes through an accessor, so the translation is arithmetic:
`mem1[ea & 0x03FFFFFF]`, with a range check. The spike's module links with
`-sINITIAL_MEMORY=33554432` — **32 MiB, holding a 24 MiB MEM1** — and runs. That is a
**64x reduction**, and it removes C7 from the blocker list outright.

The spike's arena is **big-endian**: a literal image of console memory, with byte order
settled once inside `ppc_r32`/`ppc_w32`. See §5.2 — this is the one place where the
existing host code would need real work.

### 4.5 Indirect branches

Tool: [`risk_probe.py`](../research/tools/static-recomp/risk_probe.py). Artifact:
[`research/decomp/data/static-recomp-risk.json`](../research/decomp/data/static-recomp-risk.json).

| Form | Sites |
| --- | ---: |
| `bctrl` (indirect **call**) | 2,457 |
| `blrl` (call through LR) | 138 |
| `bctr` (computed **jump**) | 133 |

**`bctrl` and `blrl` are solved and the spike demonstrates it.** `ppc_bl(c, const)` and
`ppc_bctrl(c)` are the *same* `ppc_lookup()` over the entry-point table; only the argument
differs. The corroborating measurement: of **11,539 words in the data sections that point
into text**, **6,914 are known function entries** — the vtables and dispatch tables those
2,457 `bctrl` sites read. This is gap **E2**: 1,602 functions (14.6 %) that the current
route classifies **permanently unverifiable** because their dispatch goes through a ROM
function-pointer table. On this route they are ordinary calls.

**`bctr` is a genuine, bounded piece of extra machinery.** All 133 sites classify as
**compiler switch tables** (`mtctr` fed by an `lwzx` from an indexed table) — the shape
`n64recomp` handles the same way. The remaining **4,625** data words pointing into text are
**all mid-function addresses** (2,839 distinct): case labels, not entry points. So a
recompiler needs, per `bctr`, a per-function label table and a computed `goto` — mechanical
(read the table out of `.data`, emit a `switch` over the case labels already in the
function) but not free. **ESTIMATE: 1–2 agent-sessions.** The spike's translator currently
emits `bctr` as a tail call and would be wrong on all 133; this is named as a gap, not
papered over.

### 4.6 Self-modifying and DVD-overlaid code — the classic killer, checked

Tool: [`gcm_fst.py`](../research/tools/static-recomp/gcm_fst.py). Artifact:
[`research/decomp/data/static-recomp-disc-fst.json`](../research/decomp/data/static-recomp-disc-fst.json).

**The disc contains exactly three files:**

| File | Bytes |
| --- | ---: |
| `afs_data.afs` | 455,866,368 |
| `poq_adx_usa.afs` | 354,742,272 |
| `opening.bnr` | 6,496 |

> **Zero `.rel` modules. Zero `.dol` files besides `boot.dol`. Every PowerPC instruction the
> game will ever execute is in the image this spike disassembled.**

Corroborated from the other side: the whole DOL contains **4 `icbi` instructions** (at
`0x80003440`, `0x800036b4`, `0x802006d8`, `0x8022f4d0`) and **3 `dcbst`**. `icbi` is the
only legal way to execute code written at runtime on PowerPC; four sites is the SDK's own
`ICInvalidateRange` / `__OSCacheInit`, not an overlay loader. There is no relocation
machinery and nothing to relocate.

**The single most common reason static recompilation fails does not apply to this game.**

### 4.7 `mfspr` / `mtspr`

Of 24,582 `SPR`-class instructions, 20,603 are `mflr`/`mtlr` and 3,382 are `mtctr`/`mfctr`
— struct fields. What remains: 259 `mtspr` / 184 `mfspr`, and the register numbers are the
measurable part. GQR0–7 (SPR 912–919) are modelled in the register file because `psq_l`'s
scale and type come from them. Everything else — HID0 (1008), HID2 (920), L2CR (1017), DEC
(22), the BATs — routes to a **named host hook** (`gf_host_mfspr` / `gf_host_mtspr`), which
is an explicit seam, not a guess. All of them are in the OS/cache library that a
high-level-hosted port replaces.

### 4.8 The residue that is genuinely hard

**Paired single, 2,877 instructions in 608 functions (5.08 % of the corpus).** This is the
real cost item, and it is not a table row: it is a Gekko model — the second FPR slot, the
GQR-driven quantised load/store forms with their five scale types, and `ps_res`/`ps_rsqrte`
sharing the non-IEEE estimate tables. Dolphin's `Interpreter_Paired.cpp` is the reference
and the semantics are documented. **ESTIMATE: 2–3 agent-sessions.** The spike's translator
emits a loud abort (`ppc_ps_unsupported`) rather than a guess, so the 608 functions are
enumerable rather than silently wrong.

**`frsqrte` / `fres`, 216 instructions in 134 functions.** Two lookup tables from Dolphin.
Note this is not optional polish: getting them "close enough" with `1/sqrtf(x)` produces a
different float, and float divergence in a physics loop compounds.

**Fused multiply-add, 1,800 instructions.** PowerPC rounds once; C's `a*b+c` rounds twice.
`__builtin_fma` is the correct spelling and the spike uses it. Mechanical, but silently
wrong if spelled wrong — which is precisely the class of error the current route cannot see.

---

## 5. What carries over, and what becomes obsolete

### 5.1 Carries over essentially unchanged

- **The cross-origin-isolation stack.** `apps/game/public/coi-serviceworker.js`,
  `apps/game/vite.config.ts` COI headers, `scripts/smoke-coi-phase.mjs`. Route-independent.
- **The worker / main-thread topology and its control block.**
  `packages/rom-runtime/src/protocol.ts` (SAB control block, `BridgeState` FSM, the rule
  that the worker may `Atomics.wait` and the main thread may not),
  `packages/rom-runtime/src/host.ts`'s service pump, `packages/rom-runtime/src/ledger.ts`.
  A recompiled module is still a wasm module in a worker calling out to a host.
- **The GX host's semantic core.** `packages/rom-runtime/src/gx/fifo.ts` (the FIFO decoder
  and vertex-layout planner), `state.ts`, `tev.ts`, `texture.ts`, `enums.ts`, `webgl.ts`,
  `backend.ts`. 49/76 GX entry points, the TEV shader generator, the texture decoder. This
  is the largest single body of work in the project and it is untouched.
- **The DVD and audio hosts' semantic core.** Command-block layout, FST resolution, AI/DSP
  register meaning, ADPCM decode, the WebAudio backend.
- **The Dolphin capture machinery's console half.** `rsp_client.py`, `capture_oracle.py`'s
  process and breakpoint control, `force_navigator.py` (42 scenarios, roster staging, the
  battle-phase rewind), `capture_common.py:Dol`, `capture_gx.py surface` and its XFB
  framebuffer dump. All of it reads the console; none of it cares how the port was built.
- **The savestates and scenarios.** Owner inputs, unchanged.
- **`packages/combat`, `packages/audio`'s cue resolver, and the whole `apps/game` vertical
  slice.** The recreation is the scaffold either way.

### 5.2 Carries over with bounded, named work

- **Arena endianness.** This is the real integration cost and it should not be minimised.
  The existing arena is **little-endian per element**: `gen_arena.py` and its siblings swap
  per region *by declared type* (`swap4` for u32/f32, `swap2` for s16 tables, none for byte
  tables), `packages/rom-runtime/src/memory.ts`'s `GcMemory` passes `littleEndian = true` on
  every `DataView` accessor, and `gx/fifo.ts` deliberately runs **both** orders — big-endian
  for the FIFO stream, little-endian for `GXSetArray`-bound vertex arrays out of the arena.
  A recompiled module wants a **big-endian whole-DOL image**, which is *simpler* (no
  per-region type partition, no `swap4`/`swap2` decision to get wrong — and that decision is
  itself an inference) but inverts every one of those call sites. **ESTIMATE: 2–3
  agent-sessions**, concentrated in `memory.ts`, `gx/fifo.ts`, `dvd/adapters.ts`,
  `audio/adapters.ts` and the `gen_arena*.py` family.
- **The bridge's ABI layer.** `packages/rom-runtime/src/frame.ts` (dispatch-frame ABI v1),
  `composed.ts` (the `zz_<hex>_` / `FUN_<hex>` / `0x7f000000 | fnv1a(symbol)` address
  convention), and `makeBridgeTrampolines`' signature-accurate per-import trampolines are
  all built around *emcc-induced wasm signatures*. A recompiled module has no per-callee
  signatures — every host call is "here is the register file". That is a **simplification**,
  and gap **C8** ("H3's uniform dispatch ABI converts signature traps into silent
  mis-marshalling, against 88 contested symbols") disappears with it. **ESTIMATE: 1–2
  agent-sessions.**
- **The `gnt4_*` SDK seam becomes optional.** The recompiler translates the SDK bodies
  because they are in the DOL. That opens an architectural choice this project has never
  had: keep the host at the **GX API seam** (where it is today, 87.1 % of static call sites)
  or move it to the **hardware register seam** and let the ROM's own `GXSetFog` run. The
  second is strictly more faithful and strictly more work. Not a decision this spike makes.

### 5.3 Becomes obsolete

Not "improved" — gone, because the thing they manage does not exist on this route.

| Machinery | Why it goes away |
| --- | --- |
| The **1,396-unit queue**, `unit-priority.json`, `red_retryable`, `structural_ineligible` | there are no units. There is one program. |
| The **compile-fix LLM loop** and its GPU budget | nothing needs fixing to compile; the translator either has a table row or it errors |
| **Per-unit specs** (`specs/*.spec.mjs`) and `port_spec_emit.py`'s `human` classification | E5. Nothing to author |
| The **composition ladder** and its rungs | C1, C2, C9. There is no window and no link order |
| The **assembly gate**, `ELIGIBLE_CANONICAL_TIERS`, contested-symbol reconciliation | one program, one symbol table |
| `port_wgpipe_lowering.py` and every `wgpipe_unlowerable_site` refusal | §2.2 item 1 |
| The **2,155,479,040-byte fixed shared memory** | §4.4 |
| **The 1,602 "unverifiable — ROM function-pointer dispatch" functions** | §4.5 |
| **The 56-export stack-local-pointer class (E4)** | §2.2 item 3 |
| **The 1,514-function varargs mis-lift (E11)** | §3.2. There is no signature |
| The **threads-relink re-verification obligation (C6)** | one module, one link |
| `capture_common.py:wasm_signatures` + every `plans/*.json` keyed to a unit/symbol | the ABI is the PowerPC ABI, read off the instructions |

Also worth saying: **the evidence problem does not go away, it changes shape.** Console
captures are still the only ground truth, `force_navigator` is still how coverage is
authored, and E8 (all 33 queued scenarios are battles) and E10 (no replayable DTM exists)
are unaffected. What changes is that a capture now verifies *the ROM's actual code* rather
than a hypothesis about it, and one capture no longer needs a matching hand-authored spec.

---

## 6. Verdict

**Static recompilation is a credible route to a playable 1:1 port of this game, and on
every axis this spike could measure it dominates the current route.** The argument, from
the measurements:

**1. The hard-instruction count is 0.465 %, and it is enumerable.** 3,256 of 699,828, of
which 2,877 are one bounded subsystem (paired single, in 5.08 % of functions) and 216 are
two lookup tables. Compare the current route, whose blocking class is "Ghidra inferred
something wrong" — E11 alone is 1,514 functions and nobody can say what the next class is.
A finite enumerated list beats an unbounded unenumerated one even when the list is longer.

**2. The translation is already 98.5 % complete on a 416-line generator.** 11,795 of 11,972
entry points, including the 996 SDK functions the current corpus excludes by design. That
was one session's work. The current route has promoted 3 units in 17 driver-days and 0 in
the last sweep.

**3. Two of two attempted functions verified against the console.** `gx_callstream_green`
4/4 invocations, 76 calls, 48 pipe writes; `transcript_green` 24/24 cases, 48/48 calls.
Three negative controls red. And the second of those functions is one the current route got
**wrong** — reading a different object through a mis-lifted parameter — and needed a
sanctioned corpus correction, a preflight build and a live re-capture to fix, a fix that
E7 records as **still stalled**. The recompiler was right the first time and could not have
been wrong.

**4. The classic killer is absent.** Zero `.rel` overlays on the disc, four `icbi` sites in
the whole DOL. This is checkable, was checked, and it is the single fact most likely to have
killed the idea.

**5. The costs are small.** 36.6 MB raw / 4.0 MB gzip. 24 MiB of MEM1 instead of 2.1 GB.
CPU-only build, no model server, no GPU.

**6. Nine of the spec's blocking gaps are dissolved rather than worked around** — E2, E4,
E5, E7, E11, C1, C2, C6, C7, C8, C9, H8 — and the ones that survive (H1/H2 GX coverage,
H3 the framebuffer ceiling, H4 the missing MusyX mixer, E8/E10 coverage authorship) are
**exactly the ones that were never about decompilation**. That is the shape you want: the
route change kills the class of problem that is not converging and leaves the class that is
merely unfinished.

### 6.1 What it would cost to build out

In this project's own units. Every figure is an **ESTIMATE**, derived from the spike's
measured work; the anchors are stated.

| Work | Cost | Anchor |
| --- | --- | --- |
| Complete the translation table: 169 forms, from 134 | 1–2 agent-sessions | 134 forms took part of one session |
| Paired-single model (GQRs, quantised load/store, `ps_*`) | 2–3 agent-sessions | 608 functions, Dolphin's `Interpreter_Paired.cpp` is the reference |
| `frsqrte` / `fres` estimate tables | < 1 agent-session | two tables |
| `bctr` switch-table recovery + per-function label tables | 1–2 agent-sessions | 133 sites, 4,625 case labels, all one shape |
| Whole-program function-boundary discovery (the 6.6 % of text outside the registry) | 1 agent-session | §4.2 |
| Whole-program emission + build pipeline + entry-point table | 1–2 agent-sessions | the spike builds 1,500 functions today |
| Big-endian whole-DOL arena + flip the host's arena readers | 2–3 agent-sessions | §5.2 |
| Bridge/ABI re-seam (`frame.ts`, `composed.ts`, trampolines) | 1–2 agent-sessions | §5.2 |
| OS/boot HLE (`.init`, `__start`, `OSDisableInterrupts`, `sc`) | 1–2 agent-sessions | 59 supervisor instructions in `.init`, 89 in the OS library |
| **Subtotal to "the whole ROM is translated, links, and boots into the host"** | **11–18 agent-sessions, 0 GPU-hours, 0 Dolphin-hours** | |

Then the work that is **identical on either route** and is not counted above: GX runtime-
frequency coverage (H1/H2 — the spec's §3.6 Option B, 6–8 mechanisms), DVD timing (H7),
the audio scope decision (H4), and coverage authorship (E8, E10, including the one DTM
§3.3 says is not optional). Those dominate the remaining schedule on either route, which is
the real reason to switch: **the route change is cheap and it moves the project onto the
work that was always going to be the work.**

### 6.2 The honest counter-case

A spike that only argues for its subject is advocacy. The strongest arguments against:

- **The GX/DVD/audio hosts are the actual critical path, and this changes none of them.**
  True. §5.3 says so. But the current route's asymptote is a *no-op promotion pipeline*, and
  a route that is merely neutral on the host while removing the pipeline is still strictly
  better.
- **Recompiled code is slower than ported C.** Almost certainly. A register file in memory
  and per-access byte-swapping is not free, and 699,828 instructions of `goto`-threaded C is
  not what a wasm JIT likes. This spike did **not** measure frame-rate feasibility, and that
  is its largest unmeasured risk. Zelda 64: Recompiled is the existence proof that it can be
  made fast enough on a comparable-era console; that is a precedent, not a measurement of
  this game.
- **The endianness flip touches working, verified code.** True, and `damage-core` is the
  project's one unambiguous end-to-end success. It is a bounded refactor (§5.2) but it is
  not zero-risk.
- **Verification coverage does not improve.** Also true. 98.5 % of functions *translate*;
  a translation is not a verification. What improves is that verification no longer requires
  a hand-authored spec per unit, and that a passing capture now says something about the
  ROM's code rather than about a hypothesis.
- **`bctr` is currently wrong** in the spike's translator (§4.5), and 133 switch statements
  silently taking a wrong branch is exactly the failure mode this route claims to eliminate.
  It is named here so it cannot be forgotten.

### 6.3 Recommendation

Adopt it, and do so in a way that can be killed cheaply. The next increment that would
settle the remaining risk is **not** more translation — it is a **performance probe**:
recompile the `run_main_game_loop` spine plus its 17 loop-body callees, run it under the
existing worker at frame cadence, and measure instructions/second. That is the one number
this spike did not produce and the one that could still make the answer no.

---

## 7. What this spike does not show

Stated in the project's own terms, because a spike that overclaims is worse than no spike.

- **No pixel, no frame, no game.** Two functions ran. Nothing was rendered, nothing was
  played. The GX host is unchanged and still throws on `GXSetFog`.
- **No performance measurement of any kind.** §6.2.
- **The two verifications are bounded by their corpora** — 4 invocations of one draw in one
  battle state, and 24 recorded cases of one function. Both artifacts carry their own
  `does_not_verify` block.
- **Both verifications seed memory from the console.** That is the same contract the
  existing harness runs under, and both artifacts say so.
- **The translator implements 134 of 169 forms** and emits a loud abort for paired single.
  It is a spike, not a recompiler.
- **`bctr` is not correctly translated** (§4.5).
- **Nothing here was promoted, staged, or written to driver state.** No `research/decomp/`
  pipeline artifact was modified; the files added under `research/decomp/data/` are new
  `static-recomp-*` measurements and two new `oracle-results` artifacts labelled
  `route: static_recompilation`.

---

## 8. Reproducing every number

CPU only. No model server, no GPU, no Dolphin.

```bash
cd research/tools/static-recomp
ISO="D:/GotYaForce/Gotcha Force.iso"
EMPY="D:/GotYaForce/research/tools/emsdk/python/3.13.3_64bit/python.exe"
EMCC="D:/GotYaForce/research/tools/emsdk/upstream/emscripten/emcc.py"
NODE="D:/GotYaForce/research/tools/emsdk/node/24.19.0_64bit/node.exe"

# §1  instruction inventory, encoding-form census, capstone-gap probes
python dol_inventory.py   --iso "$ISO" --out ../../decomp/data/static-recomp-inventory.json
python form_census.py     --iso "$ISO" --out ../../decomp/data/static-recomp-forms.json
python undecoded_probe.py --iso "$ISO" --out ../../decomp/data/static-recomp-undecoded.json
python op63_probe.py      --iso "$ISO" --out ../../decomp/data/static-recomp-op63.json

# §4.5-4.6  indirect control flow, code pointers, SMC signals, disc filesystem
python risk_probe.py --iso "$ISO" --registry ../../decomp/data/oracle-registry.json \
                     --out ../../decomp/data/static-recomp-risk.json
python gcm_fst.py    --iso "$ISO" --out ../../decomp/data/static-recomp-disc-fst.json

# §4.1  translate every function in the corpus
python batch_recomp.py --iso "$ISO" --registry ../../decomp/data/oracle-registry.json \
                       --out ../../decomp/data/static-recomp-batch.json

# §4.3  wasm bytes per instruction
python size_probe.py --iso "$ISO" --registry ../../decomp/data/oracle-registry.json \
                     --sample 1500 --emcc "$EMCC" --python "$EMPY" \
                     --workdir build/size --out ../../decomp/data/static-recomp-size.json

# §3.1  gx_callstream_green
python ppc_recomp.py --iso "$ISO" --func 0x80027c34 --name zz_0027c34_ \
    --out generated/zz_0027c34_.c --manifest generated/zz_0027c34_.manifest.json
python gen_spike_host.py \
    --capture ../../decomp/oracle-harness/corpora/gx-rom-unit.zz_0027c34_.gx-callstream.jsonl \
    --decls ../../../packages/rom-runtime/test/fixtures/gx-rom-unit/gnt4_gx_decls.h \
    --manifest generated/zz_0027c34_.manifest.json --out generated/spike_host.c
"$EMPY" "$EMCC" generated/zz_0027c34_.c generated/spike_host.c rt/ppc_rt.c -I rt \
    -O1 -std=c11 -sINITIAL_MEMORY=33554432 -sALLOW_MEMORY_GROWTH=0 -o build/spike.cjs
python compare_callstream.py \
    --capture ../../decomp/oracle-harness/corpora/gx-rom-unit.zz_0027c34_.gx-callstream.jsonl \
    --module build/spike.cjs --node "$NODE" \
    --out ../../decomp/data/oracle-results/static-recomp.zz_0027c34_.gx-callstream.json

# §3.2  transcript_green
python ppc_recomp.py --iso "$ISO" --func 0x800c4468 --name FUN_800c4468 \
    --out generated/FUN_800c4468.c --manifest generated/FUN_800c4468.manifest.json
PF=../../decomp/transcript-preflight/auto-c0020-007-FUN_800c4468
python gen_transcript_host.py --capture $PF/auto-c0020-007.FUN_800c4468.transcript.jsonl \
    --unit-wasm $PF/unit.wasm --manifest generated/FUN_800c4468.manifest.json \
    --out generated/transcript_host_800c4468.c
"$EMPY" "$EMCC" generated/FUN_800c4468.c generated/transcript_host_800c4468.c rt/ppc_rt.c \
    -I rt -O1 -std=c11 -sINITIAL_MEMORY=33554432 -o build/transcript_800c4468.cjs
python compare_transcript.py --capture $PF/auto-c0020-007.FUN_800c4468.transcript.jsonl \
    --module build/transcript_800c4468.cjs --node "$NODE" \
    --out ../../decomp/data/oracle-results/static-recomp.FUN_800c4468.transcript.json
```

Both comparators exit non-zero on divergence. The negative controls in §3 are reproduced by
editing one statement in the generated `.c` and rebuilding; the mutants and their result
artifacts are under `research/tools/static-recomp/build/neg/`.
