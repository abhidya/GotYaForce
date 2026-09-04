# Matching-decompilation compiler census

**Generated `2026-09-04T04:56:55Z`.** The question this answers: the matching-decompilation spike
(`docs/matching-decompilation-spike.md`) matched 13 functions and named five compiler
blockers, all of them found by hand. This measures the same compiler against **the
whole corpus** -- every one of the 12,062 entry points and 701,464 instructions -- so the
project's throughput and scope estimates rest on a number instead of a vendor claim.

Every count below carries **both** a function count and an instruction share, because
spike doc sec 5.2 is the standing rule here: half the functions are a tenth of the code, and a
function-weighted number is a lie by construction.

## Reproduction

```bash
# one command; CPU only, no model, no network
MWCC_RS=<path to mwcc-rs>/target/release/mwcc.exe \
  python research/tools/matching-decomp/census.py

# drift check: re-derives everything, writes nothing, exit 1 if stale
python research/tools/matching-decomp/census.py --check
```

### Inputs, digested

| input | identity |
| --- | --- |
| Ghidra corpus index | `research/decomp/ghidra-export/_index.tsv` sha256 `e258682e1e7e2abf` |
| Ghidra chunks (80 files) | rolled sha256 `49290dfe313f15ba` |
| oracle registry | `research/decomp/data/oracle-registry.json` sha256 `8bbdaa7091aa8964` |
| link map | `research/symbols/GG4E-CSM-20220412.map` sha256 `b1da161c17220017` |
| retail `.text` | sha256 `d9368f59a2d0413c` |
| compiler | mwcc-rs build 2.7, exe sha256 `6d6597dc4ebaf791` |
| compiler commit | `7c093483f9c6c5775eb856a1a343a5dc6671233b` |
| shim header | `census_shim.h` sha256 `8a327d48d888578f`, derived from `research/decomp/generated/finish-game-port/gnt4_shim_seed.h` sha256 `5b17e2304eaaa13c` |
| flags | `-proc gekko -fp hardware -O4,p -enum int -nodefaults -inline auto -sdata 8 -sdata2 8 -str reuse -func_align 4` |

## 1. Compile-ability

Each entry point's **verbatim** Ghidra C, sliced out of the export and materialised as a
single translation unit the way the port driver does: the `gnt4_shim` typedef block, `code`
for indirect dispatch, `extern` declarations for callees and address-named globals.
Nothing in the function body is rewritten. This does not ask whether the bytes match --
it asks whether the compiler can ingest the **shape** of this game's code.

The exact recipe, because it bounds every number below:

| step | rule |
| --- | --- |
| callee declarations | unprototyped, return type from the callee's own Ghidra signature |
| global declarations | extern, width from Ghidra's naming prefix (FLOAT_/DOUBLE_/PTR_/s_), else int |
| missing type names | declared opaque (`typedef struct X_census_opaque X;`) when a declaration names a class the export never defines |
| adaptive rounds | up to 12 -- while the diagnostic names something the harness failed to declare, declare it and retry, so a missing `extern` is never counted as a compiler limit |
| shim delivery | **inlined**, not `#include`d: mwcc-rs will not accept a typedef that arrived through an include as a file-scope function's return type, and Ghidra returns a placeholder type constantly |

| status | functions | % of functions | instructions | % of code | meaning |
| --- | ---: | ---: | ---: | ---: | --- |
| CODEGEN_UNSUPPORTED | 6,214 | 51.52% | 446,126 | **63.60%** | parsed, then refused to lower -- a compiler capability gap |
| FRONT_END_REFUSAL | 2,710 | 22.47% | 165,217 | **23.55%** | refused at parse/typecheck |
| **COMPILES** | 2,858 | 23.69% | 70,639 | **10.07%** | mwcc-rs produced an object |
| HARNESS_SHIM_GAP | 169 | 1.40% | 12,579 | **1.79%** | this tool's translation unit was incomplete, not a compiler limit |
| NO_GHIDRA_SOURCE | 90 | 0.75% | 5,248 | **0.75%** | the entry point has no block in the Ghidra export |
| SOURCE_NOT_C | 21 | 0.17% | 1,655 | **0.24%** | the Ghidra export emitted something that is not C |

Rolled up by who is at fault:

| class | functions | % of functions | instructions | % of code |  |
| --- | ---: | ---: | ---: | ---: | --- |
| codegen | 6,214 | 51.52% | 446,126 | 63.60% | COMPILER: parsed and could not lower |
| frontend | 2,710 | 22.47% | 165,217 | 23.55% | COMPILER: refused to parse or typecheck |
| ok | 2,858 | 23.69% | 70,639 | 10.07% | compiled |
| harness | 169 | 1.40% | 12,579 | 1.79% | HARNESS: this tool's fault, not the compiler's |
| no_source | 90 | 0.75% | 5,248 | 0.75% | no input to compile |
| corpus | 21 | 0.17% | 1,655 | 0.24% | CORPUS: the decompiled C is defective, nobody's compiler could take it |

> **2,858 of 12,062 entry points compile -- 23.69% of the functions and 10.07% of the instructions.**
>
> The `harness` class (12,579 instructions, 1.79% of the code) is this tool's own floor and
> is **not** charged to the compiler: a translation unit assembled by regex from one
> decompiled function is not the original translation unit. `corpus` and `no_source` are
> not the compiler's either. The compiler-capability number is `codegen` + `frontend` +
> `panic` and nothing else.

## 2. What stops the rest, ranked by instructions blocked

The compiler roadmap. A construct high in this table is worth a lowering; one low in it
is not, however many functions it touches.

| construct (the compiler's own diagnostic) | class | functions | %fn | instructions | %code | example |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| this long long shape is not modeled yet (roadmap; function 'X') | codegen | 2,210 | 18.32% | 150,293 | 21.43% | `__check_pad3 @ 0x80003100` |
| expected an expression, found ParenClose at token N (line N, column N) | frontend | 2,535 | 21.02% | 138,420 | 19.73% | `zz_0008cf4_ @ 0x80008cf4` |
| a signed char load promoted to int needs a sign-extension (roadmap) | codegen | 1,296 | 10.74% | 81,022 | 11.55% | `zz_0006f98_ @ 0x80006f98` |
| pointer leaf access needs a pointer variable (roadmap) | codegen | 1,086 | 9.00% | 77,044 | 10.98% | `zz_00058d0_ @ 0x800058d0` |
| local reassignment mixed with stores/calls is not supported yet (roadmap) | codegen | 218 | 1.81% | 31,223 | 4.45% | `zz_000598c_ @ 0x8000598c` |
| expression needs the full register allocator (roadmap M1) | codegen | 186 | 1.54% | 17,725 | 2.53% | `zz_0006abc_ @ 0x80006abc` |
| expected Semicolon, found Comma at token N (line N, column N) | frontend | 82 | 0.68% | 15,035 | 2.14% | `zz_0003340_ @ 0x80003340` |
| a commutative op with a constant-shift left operand orders operands differently (roadmap) | codegen | 179 | 1.48% | 14,023 | 2.00% | `zz_0006dc8_ @ 0x80006dc8` |
| a global read in both an if-condition and its body needs value reuse across the branch (roadmap; | codegen | 129 | 1.07% | 13,148 | 1.87% | `zz_0005fe0_ @ 0x80005fe0` |
| struct member on a global this tool could only declare as int | harness | 103 | 0.85% | 8,969 | 1.28% | `zz_0027c34_ @ 0x80027c34` |
| AND/arith against a constant that is not an rlwinm mask | codegen | 115 | 0.95% | 8,507 | 1.21% | `zz_0005668_ @ 0x80005668` |
| a float add/multiply with a negated operand needs fnmsubs / operand-order modeling (roadmap) | codegen | 82 | 0.68% | 7,984 | 1.14% | `zz_001fef0_ @ 0x8001fef0` |
| a value live across a call needs the callee-saved register allocator (roadmap; function 'X') | codegen | 66 | 0.55% | 7,885 | 1.12% | `zz_0008d9c_ @ 0x80008d9c` |
| a mixed narrow comparison needs both operands extended (roadmap) | codegen | 91 | 0.75% | 5,980 | 0.85% | `FUN_80019950 @ 0x80019950` |
| member 'X' on a non-struct-pointer base | frontend | 24 | 0.20% | 5,498 | 0.78% | `zz_0005630_ @ 0x80005630` |
| general if-statement codegen is not implemented yet (roadmap; function 'X') | codegen | 42 | 0.35% | 5,278 | 0.75% | `FUN_8000c988 @ 0x8000c988` |
| identifier the harness failed to declare | harness | 66 | 0.55% | 3,610 | 0.52% | `zz_000a3c4_ @ 0x8000a3c4` |
| a repeated common sub-expression needs the register allocator's CSE (roadmap) | codegen | 38 | 0.32% | 2,421 | 0.34% | `FUN_80045918 @ 0x80045918` |
| pointer access needs a pointer variable (roadmap) | codegen | 35 | 0.29% | 2,228 | 0.32% | `zz_0007f5c_ @ 0x80007f5c` |
| a binary over two compound-load operands needs the allocator (roadmap) | codegen | 23 | 0.19% | 2,104 | 0.30% | `mutual_actor_contact_mask_update @ 0x8002cb20` |
| pointer arithmetic on a global's address needs offset scaling (roadmap) | codegen | 28 | 0.23% | 1,971 | 0.28% | `FUN_8001b308 @ 0x8001b308` |
| argument N to 'X' would clobber r3, which later argument N still needs (roadmap) | codegen | 43 | 0.36% | 1,874 | 0.27% | `FUN_8000cdc0 @ 0x8000cdc0` |
| the Ghidra export emits a C++ template name that is not a C identifier | corpus | 21 | 0.17% | 1,655 | 0.24% | `nlQSort<20AnimAudioEventLookup>(AnimAudioEventLookup @ 0x801a7640` |
| value tracking for a void function is not supported yet (roadmap) | codegen | 84 | 0.70% | 1,595 | 0.23% | `zz_00061f0_ @ 0x800061f0` |
| a constant-divide operand alongside another complex operand needs the register allocator (roadma | codegen | 10 | 0.08% | 1,526 | 0.22% | `FUN_800bee1c @ 0x800bee1c` |
| 'X' is not a pointer | frontend | 12 | 0.10% | 1,424 | 0.20% | `zz_000a07c_ @ 0x8000a07c` |
| an early-return continuation that materializes store values needs the store/return scheduler (ro | codegen | 56 | 0.46% | 1,275 | 0.18% | `zz_0006c24_ @ 0x80006c24` |
| a constant argument after a global load needs the LR-store-latency schedule (roadmap) | codegen | 10 | 0.08% | 1,273 | 0.18% | `zz_002aee0_ @ 0x8002aee0` |
| a computed add comparison did not end in a recordable add | frontend | 6 | 0.05% | 878 | 0.12% | `FUN_80005af4 @ 0x80005af4` |
| this floating-point == comparison needs the value register allocator (roadmap) | codegen | 11 | 0.09% | 853 | 0.12% | `zz_0023b18_ @ 0x80023b18` |
| a run of pointer stores whose last value mwcc latency-hoists needs the scheduler (roadmap) | codegen | 24 | 0.20% | 776 | 0.11% | `FUN_8001c294 @ 0x8001c294` |
| argument N to 'X' would clobber r4, which later argument N still needs (roadmap) | codegen | 25 | 0.21% | 704 | 0.10% | `zz_002fcbc_ @ 0x8002fcbc` |
| a comma operand in this expression is not supported yet (roadmap): left=Binary { operator: NotEq | codegen | 4 | 0.03% | 646 | 0.09% | `FUN_80025944 @ 0x80025944` |
| float-to-narrow-unsigned conversion is not modeled (roadmap) | codegen | 5 | 0.04% | 635 | 0.09% | `gnt4-__ieee754_acos @ 0x80239410` |
| a multi-level pointer declarator list is not supported yet (roadmap) | codegen | 1 | 0.01% | 627 | 0.09% | `gnt4-MObjMakeTExp-bl @ 0x80242a9c` |
| store target must be `*p`, `p[i]`, a member, or a global | frontend | 11 | 0.09% | 619 | 0.09% | `zz_0011abc_ @ 0x80011abc` |
| a comma operand in this expression is not supported yet (roadmap): left=Binary { operator: Equal | codegen | 7 | 0.06% | 590 | 0.08% | `zz_0083714_ @ 0x80083714` |
| dereference combined with this operand needs the full allocator (roadmap) | codegen | 14 | 0.12% | 568 | 0.08% | `zz_0040f74_ @ 0x80040f74` |
| expected a general-register leaf | frontend | 8 | 0.07% | 499 | 0.07% | `zz_000314c_ @ 0x8000314c` |
| a run of stores that mwcc latency-schedules needs the scheduler (roadmap) | codegen | 14 | 0.12% | 483 | 0.07% | `zz_0018270_ @ 0x80018270` |

*(58 further constructs, each below the fortieth; the full list is in the JSON.)*

Where the diagnostic points at a line, the line it points at:

- **expected an expression, found ParenClose at token N (line N, column N)** (2,535 functions) --
  ```c
  (**(code **)(*piVar2 + 0x30))(piVar2);
  ```
- **expected Semicolon, found Comma at token N (line N, column N)** (82 functions) --
  ```c
  for (ppuVar1 = &PTR___check_pad3_80005544; __n = ppuVar1[2], __n != (undefined *)0x0;
  ```

### 2a. One sensitivity check, because the top bucket is ambiguous

Ghidra types the EABI argument registers it cannot resolve as `undefined8`, and the
port's shim contract makes that a 64-bit integer. The compiler then refuses the function
for a long-long shape the retail code does not contain. Re-compiling exactly those
functions with `undefined8` narrowed to 32 bits -- semantically wrong, and used for
nothing but this diagnostic -- separates *the compiler needs 64-bit lowering* from *the
corpus needs argument types*:

|  | functions | instructions |
| --- | ---: | ---: |
| refused for a long-long shape | 2,210 | 150,293 |
| of those, compile with `undefined8` = 32-bit | 683 | 13,628 |

What the rest hit instead, once the long-long shape is out of the way:

| next construct | instructions |
| --- | ---: |
| a value live across a call needs the callee-saved register allocator (roadmap; f | 38,597 |
| local reassignment mixed with stores/calls is not supported yet (roadmap) | 28,077 |
| pointer leaf access needs a pointer variable (roadmap) | 19,772 |
| this long long shape is not modeled yet (roadmap; function 'X') | 10,157 |
| general if-statement codegen is not implemented yet (roadmap; function 'X') | 7,182 |
| general argument N to 'X' needs an unreserved outgoing stack slot | 5,559 |
| AND/arith against a constant that is not an rlwinm mask | 3,701 |
| a signed char load promoted to int needs a sign-extension (roadmap) | 3,503 |

## 3. Near-match probe: how far verbatim Ghidra C gets on its own

Every function that compiled, run once through the same oracle `match.py` uses, against
the retail bytes. **One shot** -- no iteration, no rewriting. This is the floor the LLM
loop starts from, not what it can reach.

| first-try match | functions | instructions |
| --- | ---: | ---: |
| =100% | 666 | 4,257 |
| >=90% and <99.999% | 33 | 645 |
| >=75% and <90% | 115 | 1,961 |
| >=50% and <75% | 200 | 3,599 |
| >=25% and <50% | 406 | 8,275 |
| >=0% and <25% | 1,438 | 51,902 |

The retail extent comes from the link map for 1,599 of these and from the census's own
next-entry-point cap for the other 1,259. The cap can swallow inter-function alignment
padding, and objdiff requires equal lengths for a MATCH -- so that half of the sample can
only ever *lose* matches. The count below is a floor.

> **699 of the 2,858 probed match >= 90% on the first try, and 666 of those are byte-exact.**
> That is the LLM loop's cheapest class -- and it is 4,902 instructions, **0.699% of the game**.
> Spike doc sec 5.2, again, with fresh numbers: 5.8% of the entry points, well under one
> percent of the code.

The best of them:

| function | address | insns | first-try match | verdict |
| --- | --- | ---: | ---: | --- |
| `zz_021c50c_` | 0x8021c50c | 69 | 91.30% | MISMATCH |
| `gnt4-HSD_SetupTevStage-bl` | 0x80241ec4 | 62 | 96.77% | MISMATCH |
| `zz_0029574_` | 0x80029574 | 27 | 100.00% | MATCH |
| `gnt4-HSD_Index2LightID-bl` | 0x802457f8 | 26 | 96.43% | MISMATCH |
| `zz_01b1758_` | 0x801b1758 | 25 | 92.00% | MISMATCH |
| `zz_01b1a40_` | 0x801b1a40 | 25 | 92.00% | MISMATCH |
| `zz_01b1c60_` | 0x801b1c60 | 25 | 92.00% | MISMATCH |
| `zz_01b1da4_` | 0x801b1da4 | 25 | 92.00% | MISMATCH |
| `zz_01b1eac_` | 0x801b1eac | 25 | 92.00% | MISMATCH |
| `zz_01cada4_` | 0x801cada4 | 24 | 100.00% | MATCH |
| `zz_00d53fc_` | 0x800d53fc | 24 | 91.67% | MISMATCH |
| `FUN_80062b1c` | 0x80062b1c | 23 | 100.00% | MATCH |
| `FUN_80062b98` | 0x80062b98 | 23 | 91.30% | MISMATCH |
| `zz_01a71b0_` | 0x801a71b0 | 22 | 100.00% | MATCH |
| `zz_00528b4_` | 0x800528b4 | 20 | 100.00% | MATCH |
| `FUN_801cde10` | 0x801cde10 | 20 | 90.00% | MISMATCH |
| `FUN_800757f4` | 0x800757f4 | 19 | 100.00% | MATCH |
| `zz_0105240_` | 0x80105240 | 19 | 100.00% | MATCH |
| `zz_01b0ee8_` | 0x801b0ee8 | 19 | 100.00% | MATCH |
| `zz_0268c30_` | 0x80268c30 | 19 | 94.74% | MISMATCH |
| `zz_00729f8_` | 0x800729f8 | 18 | 100.00% | MATCH |
| `FUN_8011d1f0` | 0x8011d1f0 | 18 | 100.00% | MATCH |
| `FUN_8013550c` | 0x8013550c | 18 | 100.00% | MATCH |
| `FUN_801666e0` | 0x801666e0 | 18 | 100.00% | MATCH |
| `FUN_80198e50` | 0x80198e50 | 18 | 100.00% | MATCH |

## 4. Shape sharing: the real 'free wins' number

A *shape* is a function's ordered mnemonic sequence with registers, immediates and branch
targets dropped. Two functions of the same shape differ only in operands, so a matched
function is a worked example for every other function sharing its shape. Spike doc sec 3.1.5
counted this for the thirteen matched functions over functions of <= 16 instructions; this is
the same measurement over the whole corpus.

|  | value |
| --- | ---: |
| distinct shapes | 8,090 |
| shapes seen exactly once | 7,200 |
| functions | 12,062 |
| instructions | 701,464 |

| to cover this share | distinct shapes (of functions) | distinct shapes (of instructions) |
| --- | ---: | ---: |
| 50% | 2,059 | 1,403 |
| 80% | 5,678 | 3,882 |
| 95% | 7,487 | 6,229 |

Read that carefully. Ranked by **instructions**, the head of the distribution is not
reuse -- it is the biggest functions, each with a shape of its own. The reuse that
actually pays is in the tail:

|  | shapes | functions in them | **followers** (one exemplar each solved) | follower instructions |
| --- | ---: | ---: | ---: | ---: |
| shapes shared by at least 2 functions | 890 | 4,862 | 3,972 | 89,860 |
| shapes shared by at least 5 functions | 153 | 3,086 | 2,933 | 50,005 |
| shapes shared by at least 10 functions | 52 | 2,462 | 2,410 | 33,767 |
| shapes shared by at least 25 functions | 22 | 2,029 | 2,007 | 24,918 |

And the number that is actually actionable today -- shapes this census already has a
**byte-exact worked example** for:

|  | value |
| --- | ---: |
| shapes with a matched exemplar | 104 |
| functions already matched in them | 666 |
| **follower functions** (same shape, not yet matched) | **514** |
| follower instructions | **4,336** (0.618% of the game) |

| followers | instructions | matched exemplar | shape |
| ---: | ---: | --- | --- |
| 294 | 2,352 | `zz_00122c8_` | `stwu mflr stw bl lwz mtlr addi blr` |
| 101 | 909 | `FUN_800061a8` | `stwu mflr li stw bl lwz mtlr addi blr` |
| 64 | 640 | `zz_0012e4c_` | `stwu mflr lis stw addi bl lwz mtlr addi blr` |
| 7 | 63 | `zz_0007cd0_` | `stwu mflr stw lwz bl lwz mtlr addi blr` |
| 6 | 54 | `zz_022ce50_` | `stwu mflr stw bl lwz li mtlr addi blr` |
| 5 | 45 | `zz_0094e20_` | `stwu mflr stw bl bl lwz mtlr addi blr` |
| 4 | 36 | `FUN_800de490` | `stwu mflr addi stw bl lwz mtlr addi blr` |
| 4 | 12 | `zz_007f88c_` | `li stb blr` |
| 3 | 39 | `zz_0046720_` | `stwu mflr stw stw mr bl mr bl lwz lwz mtlr addi blr` |
| 3 | 30 | `zz_0090cdc_` | `stwu mflr li li stw bl lwz mtlr addi blr` |
| 3 | 30 | `zz_002a860_` | `stwu mflr mr stw lwz bl lwz mtlr addi blr` |
| 3 | 6 | `gnt4-HSD_CObjGetViewingMtxPtrDirect-bl` | `addi blr` |
| 2 | 24 | `MWEnterCriticalSection` | `stwu mflr stw stw mr bl stw lwz lwz mtlr addi blr` |
| 2 | 22 | `FUN_80157294` | `stwu mflr stw lha srawi sth bl lwz mtlr addi blr` |
| 2 | 10 | `zz_029aa40_` | `li stw stw stw blr` |

The commonest shapes:

| functions | instructions | len | shape | example |
| ---: | ---: | ---: | --- | --- |
| 424 | 6,360 | 15 | `stwu mflr lis stw addi lbz extsb slwi lwzx mtctr bctrl lwz mtlr addi blr` | `FUN_800196d0` |
| 397 | 3,176 | 8 | `stwu mflr stw bl lwz mtlr addi blr` | `zz_00122c8_` |
| 153 | 1,377 | 9 | `stwu mflr li stw bl lwz mtlr addi blr` | `FUN_800061a8` |
| 142 | 2,840 | 20 | `stwu mflr stw lbz extsb. beq li stw lbz lis addi extsb slwi lwzx mtctr bctrl lwz mtlr addi blr` | `zz_0070698_` |
| 104 | 104 | 1 | `blr` | `zz_00156a8_` |
| 97 | 2,037 | 21 | `stwu mflr stw stw mr lwz bl lbz lis addi mr extsb slwi lwzx mtctr bctrl lwz lwz mtlr addi blr` | `FUN_8004d7fc` |
| 84 | 840 | 10 | `stwu mflr lis stw addi bl lwz mtlr addi blr` | `zz_0012e4c_` |
| 76 | 1,368 | 18 | `stwu mflr lis stw addi lha srawi sth lbz extsb slwi lwzx mtctr bctrl lwz mtlr addi blr` | `FUN_8006fb44` |
| 64 | 896 | 14 | `stwu mflr addi stw lbz extsb slwi lwzx mtctr bctrl lwz mtlr addi blr` | `FUN_8000e28c` |
| 53 | 954 | 18 | `stwu mflr stw stw mr lwz cmplwi beq bl li stw mr bl lwz lwz mtlr addi blr` | `zz_0006d80_` |
| 47 | 94 | 2 | `lwz blr` | `zz_008017c_` |
| 46 | 230 | 5 | `li li stb stb blr` | `FUN_800120b0` |
| 40 | 520 | 13 | `stwu mflr lis stw addi lha srawi sth bl lwz mtlr addi blr` | `FUN_80074d08` |
| 40 | 360 | 9 | `stwu mflr stw lwz bl lwz mtlr addi blr` | `zz_0007c30_` |
| 38 | 608 | 16 | `stwu mflr stw stw mr addi lwz bl lwz li bl lwz lwz mtlr addi blr` | `FUN_800199d4` |
| 36 | 108 | 3 | `li stb blr` | `__set_debug_bba` |
| 35 | 525 | 15 | `stwu mflr stw li stw mr stb bl li stb lwz lwz mtlr addi blr` | `FUN_8006f3ec` |
| 34 | 544 | 16 | `stwu mflr lis stw extsb extsb addi slwi lwzx mtctr bctrl lwz mtlr addi blr blr` | `FUN_8006f95c` |
| 33 | 1,254 | 38 | `stwu mflr stw stw mr lbz lwz extsb cmpwi bge lbz extsb cmpwi bge lha lha cmpw beq li mr stb bl li stb lbz lis addi mr extsb slwi lwzx mtctr bctrl lwz lwz mtlr addi blr` | `FUN_8007dcec` |
| 32 | 640 | 20 | `stwu mflr stw stw mr bl lbz lis addi mr extsb slwi lwzx mtctr bctrl lwz lwz mtlr addi blr` | `FUN_8006f0cc` |

## 5. What this does to the spike's estimates

Read against `docs/matching-decompilation-spike.md` sec 3.1.3, sec 4.2 and sec 5.2.

| the spike said | the census measures |
| --- | --- |
| five compiler blockers, found by hand on five functions | **98 distinct diagnostics.** Three of the five are refusals and are all here (`rlwinm`-mask AND, pointer leaf access, loop codegen) -- together **85,606 instructions, 12.2%** of the game. The other two (`r0` index routing, `lbzu`) are MISMATCH classes, not build failures, so no compile-ability pass can see them. |
| "it could not compile the moderate tier at all" | 10.07% of the corpus's instructions compile. The compiler's own limits block **87.2%** of the code (63.6% codegen, 23.6% front end); the harness's own floor is 1.79%. |
| 13 matched functions, 43 instructions, 14 iterations | **666 byte-exact on the FIRST try from verbatim Ghidra C, no iteration at all** -- 4,257 instructions, 0.607% of the game |
| 233 functions share a shape with the 13 (sec 3.1.5) | 514 follower functions share a shape with something already matched (4,336 instructions); across the whole corpus 890 shapes are shared by at least two functions, covering 89,860 follower instructions |
| mwcc-rs "fails honestly" | confirmed at corpus scale: **0 panics and 0 timeouts** across the 11,972 functions attempted. Every refusal was a diagnostic, never plausible-but-wrong bytes. |

**The single most valuable lowering** is `this long long shape is not modeled yet (roadmap; function 'X')` -- 2,210 functions and 150,293 instructions, 21.43% of the game, behind one diagnostic.

Three things this census does **not** establish, stated so they are not read into it:

1. **A compile is not a match.** 10.07% of instructions compile; 0.607% match. The gap
   between them is the LLM loop's actual job, and this measurement says nothing about
   how many iterations it takes to close.
2. **These are mwcc-rs-exact, not MWCC-exact.** `mwcceppc.exe` is still absent. Where
   mwcc-rs diverges from real Metrowerks, a match here would be wrong, and nothing on
   this machine can check that (`TOOLCHAIN.md` sec 4).
3. **The materialisation is a floor, not a ceiling.** A translation unit assembled by
   regex from one decompiled function, with globals declared `extern int` and callees
   left unprototyped, is strictly worse input than a real translation unit would be.
   Every number here moves up, never down, as the input improves.

---

*Artifact: `research/decomp/data/matching-compiler-census.json` (schema `matching-compiler-census/1`). This document is generated; edit the tool, not the page.*
