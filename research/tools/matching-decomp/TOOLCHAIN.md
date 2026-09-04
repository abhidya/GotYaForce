# Matching-decompilation toolchain

**Date: 2026-09-03.** What is installed on this machine, where it came from, how it
was built, and exactly what it can and cannot do. Nothing proprietary was downloaded.

Companion documents: [`docs/matching-decompilation-spike.md`](../../../docs/matching-decompilation-spike.md)
(the spike this toolchain unblocks) and [`src-match/`](../../../src-match/) (the matched
corpus it produced).

---

## 1. What is installed

| Tool | Version | Where | Provenance |
| --- | --- | --- | --- |
| **Rust** | `rustc 1.98.1 (48a229cea 2026-09-01)`, `cargo 1.98.1 (797e8a9bc 2026-08-05)` | `%USERPROFILE%\.cargo` | `rustup-init.exe` from `https://static.rust-lang.org/rustup/dist/x86_64-pc-windows-msvc/rustup-init.exe` — the binary rustup.rs serves for 64-bit Windows. SHA-256 `6f4bef66261261fcb43131be8720bab817d403a09edec7455c371974b90bdb7e`, **verified against the published `rustup-init.exe.sha256` alongside it.** Installed `-y --default-toolchain stable --profile minimal --no-modify-path` — it does **not** modify `PATH`. |
| **mwcc-rs** | commit `7c093483f9c6c5775eb856a1a343a5dc6671233b` (2026-09-01, `main` HEAD at install time) | `.tools/mwcc-rs` | Source tarball of that exact commit from `https://codeload.github.com/zcanann/mwcc-rs/tar.gz/<sha>`. SHA-256 `dd8cc49aeb258a17be50110fe11a5212439979d27636ee8edb0ed2d42702f74c`. |

Pre-existing and used, not installed by this work: **MSVC Build Tools 2022**
(`VC\Tools\MSVC\14.44.35207`, with `cl.exe`/`link.exe`) and **Windows SDK 10.0.26100.0**
— the Rust `x86_64-pc-windows-msvc` toolchain links against them. Anaconda Python 3.7.3
with capstone 5.0.1 runs the harness.

`.tools/` is in `.gitignore`. The compiler is **not vendored** into this repository —
this file is how it is reproduced.

### Reproducing the install

```powershell
# 1. Rust (skip if `cargo --version` already works)
Invoke-WebRequest https://static.rust-lang.org/rustup/dist/x86_64-pc-windows-msvc/rustup-init.exe -OutFile rustup-init.exe
# verify SHA-256 against .../rustup-init.exe.sha256 before running
.\rustup-init.exe -y --default-toolchain stable --profile minimal --no-modify-path

# 2. mwcc-rs at the pinned commit
$sha = "7c093483f9c6c5775eb856a1a343a5dc6671233b"
Invoke-WebRequest "https://codeload.github.com/zcanann/mwcc-rs/tar.gz/$sha" -OutFile mwcc-rs.tar.gz
tar -xzf mwcc-rs.tar.gz -C .tools
Rename-Item ".tools\mwcc-rs-$sha" ".tools\mwcc-rs"

# 3. build (about 9 minutes cold on this machine)
$env:PATH = "$env:USERPROFILE\.cargo\bin;$env:PATH"
cargo build --release -p mwcc --manifest-path .tools\mwcc-rs\Cargo.toml
```

Produces `.tools/mwcc-rs/target/release/mwcc.exe` (~24 MB). `match.py` finds it
automatically; `MWCC_RS=<path>` overrides.

**Step 3.5 — apply this project's fork.** The checkout is no longer the pinned
commit as-is; §5 lists what this project changed and why. One command, idempotent:

```powershell
python research\tools\matching-decomp\mwcc_fork.py --apply   # then rebuild
python research\tools\matching-decomp\mwcc_fork.py --check   # verify, writes nothing
```

### Install health

```
cargo test --release --workspace --exclude mwcc-oracle --no-fail-fast
    2,510 passed, 3 failed        # pinned commit, before this project's fork
    2,514 passed, 3 failed        # with the fork (4 new tests, same 3 failures)
```

**Correction to the original entry, which read "1,984 passed, 1 failed."** That
run was fail-fast: cargo stopped at the first failing crate, so the crates after
it never ran and their tests were never counted. With `--no-fail-fast` the pinned
commit has **three** pre-existing failures, not one:

| test | crate |
| --- | --- |
| `inline_expansion::tests::composes_zero_argument_embedded_asm_at_a_nested_call_site` | `mwcc-syntax-trees-to-machine-code` |
| `tests::recovers_friend_bearing_layouts_and_expression_template_arguments` | `mwcc-tokens-to-syntax-trees` |
| `tests::retains_brace_initialized_aggregate_image_from_discarded_inline` | `mwcc-tokens-to-syntax-trees` |

All three are upstream. The two in `mwcc-tokens-to-syntax-trees` are in a crate
this project's fork does not touch at all, which is how they are known to be
pre-existing rather than damage. Nothing in `src-match/` exercises any of them.
Always use `--no-fail-fast` here: a fail-fast total is not a measurement.

`mwcc-oracle` is excluded because it is the *differential* harness: it compiles each
canary with **both** mwcc-rs and the real `mwcceppc`, and needs a decomp checkout with
`wibo`, the proprietary compiler set, and `powerpc-eabi-objdump`. None of that exists
here and none of it will be obtained. **This project's oracle is the retail DOL, not
`mwcceppc`** — which is a different and, for these purposes, better standard: it is the
actual target, not a proxy for it.

### Licence — a correction to the spike

The spike called mwcc-rs *"MIT-ish"*. Precisely:

* **There is no `LICENSE` file in the repository**, and the GitHub licence API returns
  `null` for it.
* `Cargo.toml` declares `license = "MIT OR Apache-2.0"` at the workspace level, and the
  README ends with "Dual-licensed under MIT or Apache-2.0."

That is a clear statement of intent in two places, but it is **not** the same as a
licence file, and a downstream consumer who needs a clean audit trail should ask the
author to add one. This matters only if mwcc-rs is ever redistributed; building it
locally from source, which is what this project does, is not affected.

---

## 2. What mwcc-rs actually is

The README's headline is that eight GameCube builds — GC/1.3 through GC/2.7 — are
byte-exact. Two things about the codebase qualify that, and both were measured here by
reading the source at the pinned commit.

### 2.1 83 % of the code generator is per-function memorisation

```
crates/pipeline/mwcc-syntax-trees-to-machine-code/src/captures/   143,268 lines
crates/pipeline/mwcc-syntax-trees-to-machine-code/src/ (rest)      28,345 lines
```

`captures/` holds **558 whole-function special cases**. Each fires only when the
function's *name* and a hash of its *AST* match a specific function from a reference
decomp project:

```rust
// captures/ari_abs.rs -- "an exact-match whole-function capture (fire 523)"
if function.name != "abs" || function.return_type != Type::Int
   || function.parameters.len() != 1 || !self.frame_slots.is_empty() { return Ok(false); }
let hash = super::ast_hash(function);
if !ARI_ABS_AST_HASHES.contains(&hash) { ...; return Ok(false); }
```

One of them, `acf_two_exp.rs`, is 180 KB for a single function.

**This is not a criticism of mwcc-rs — its stated purpose is to serve existing decomp
projects, and memorising a function you already have the source of is a legitimate way
to get that project to green.** But it means the parity claim is measured over a corpus
that the captures were built from. For **Gotcha Force, where no function is in the
capture set, only the 28,345-line general code generator applies.** Every result in
`src-match/` went through that general path.

### 2.2 The general generator's envelope, measured on this binary

Probed directly (`-proc gekko -fp hardware -O4,p`, build 2.7). "Works" means it
compiled; whether the bytes match retail is a separate question answered in
`src-match/matched.json`.

| Construct | Status |
| --- | --- |
| Integer/float arithmetic, comparisons, shifts, bitwise | works |
| Pointer loads and stores, struct members, arrays, globals | works |
| Function calls, `R_PPC_REL24` relocations, the non-leaf frame | works |
| `if`/`else`, ternary, conditional return (`beqlr`/`bnelr`) | works |
| Narrow types, sign/zero extension, plain-`char` signedness per build | works |
| Struct parameters passed by hidden pointer (the MWCC ABI) | works |
| Counted `for` loops → `mtctr`/`bdnz` | works |
| **`while (a && b)` pointer walks** | **refused**: `loop codegen is not implemented yet (roadmap)` |
| ~~**`AND` with a 32-bit constant that is not an `rlwinm` mask**~~ | ~~**refused**~~ — **FIXED by this project's fork, §5.1.** Was: `a general register was requested for a non-leaf expression: IntegerLiteral(...)`. |
| **Load/store with update (`lbzu`, `lwzu`)** | not generated |
| ~~**`&param` on a by-reference struct parameter**~~ | ~~spills the incoming pointer to a stack home and reloads it~~ — **FIXED for the `*(T *)&param` form by §5.2.** A bare `&param` in other positions is unchanged. |
| ~~**`*(u32 *)&struct.member`**~~ | ~~**refused**: `pointer leaf access needs a pointer variable (roadmap)`~~ — **FIXED by §5.2.** |
| **Routing an index computation through the scratch register `r0`** | not reproduced — see `zz_0298b20_` in `matched.json` |
| Comparison of a value against a large constant | **refused**: `this comparison needs the branchless compare idioms (roadmap)` |
| ~~**`typedef RET (name)(params);` — a function TYPE alias**~~ | ~~silently unregistered, so `(code **)` did not parse~~ — **FIXED by §5.3.** This is Ghidra's `code` typedef and every virtual dispatch in the export depended on it. |
| An indirect call through a function-pointer variable | works — `mr r12; mtctr r12; bctrl`. **Not** a gap, contrary to the reading of the census's front-end row. |

The project has a standing rule it keeps: **it fails honestly.** Every one of those
refusals is a diagnostic, never plausible-but-wrong bytes. That makes `BUILD_FAILED`
from mwcc-rs a statement about the *compiler*, and it must never be reported as a
failure of the candidate C.

### 2.3 Build labels, and which of them are distinguishable

`--build` accepts, from `crates/foundation/mwcc-versions/src/build.rs`:

| Label | mwcceppc | Codegen profile in mwcc-rs |
| --- | --- | --- |
| `1.3` | 2.4.2 build 53 | `Gc13Build53` — **plain `char` defaults to unsigned** |
| `1.3.2` | 2.4.2 build 81 | `Gc132Build81` — C++ inline-asm symbol retention, `memcpy` word schedule |
| `1.3.2r` | 2.4.2 build 81 (Animal Crossing hack) | same profile as `1.3.2` |
| `2.0` | 2.4.7 build 92 | `Mainline` (the defaults) |
| `2.0p1` | 2.4.7 build 92 patch 1 | `Gc20Patch1` — int→float schedule only |
| `2.5` | 2.4.7 build 105 | `MainlineEarlyAggregateLoads` |
| `2.6` | 2.4.7 build 107 | `MainlineEarlyAggregateLoads` |
| `2.7` | 2.4.7 build 108 | `MainlineEarlyAggregateLoads` |

Experimental, behind `MWCC_EXPERIMENTAL_BUILDS=1`: `1.1`, `1.1p1`, `1.2.5`,
**`1.2.5n`**, `3.0a3`, `3.0a3p1`, `Wii/1.0`. The spike said mwcc-rs "does not yet cover
GC/1.2.5n" — it now carries the identity, but as an explicitly incomplete profile, so
the spike's practical conclusion stands: **the SDK-object calibration (Calibration A)
cannot be run with this compiler.**

**`2.5`, `2.6` and `2.7` are the same code generator here.** They differ only in the
object's `.comment` marker (`0x0b` for 2.7 vs `0x0a` for 2.5/2.6), and a linked DOL does
not preserve `.comment`. **No amount of `.text` matching can separate them.** That is a
structural limit, not a gap to be closed later.

---

## 3. Driving it

```bash
# toolchain state
python research/tools/matching-decomp/match.py --detect

# one candidate against one retail function
python research/tools/matching-decomp/match.py \
    --function zz_0206f8c_ --src src-match/game/zz_0206f8c_.c \
    --obj-symbol f --build 2.7 --json v.json
#   exit 0 MATCH | 1 MISMATCH | 2 BUILD_FAILED | 3 no compiler

# Calibration B: every build x every -O level
python research/tools/matching-decomp/match.py \
    --function zz_02650c0_ --src src-match/game/zz_02650c0_.c \
    --obj-symbol f --sweep

# the whole matched corpus, with negative controls
python src-match/verify.py --control
python src-match/verify.py --sweep
```

`--backend mwcceppc` forces the genuine compiler if one is ever installed; without it
`match.py` prefers `mwcceppc` when present and falls back to `mwcc-rs`.

### One harness bug this work found and fixed

`match.py` masked relocated operand fields but **never checked the relocation's
symbol**, so a candidate that called the *wrong function* still reported MATCH. The
retail branch targets are now resolved through the link map and passed to
`objdiff.compare` as `expected_syms`. `src-match/verify.py --control` includes the
regression: `zz_00122c8_` with `some_other_function()` in place of `zz_0012308_` is
rejected with `reloc_symbol_errors`. Selftest T6b always tested this rule; nothing was
wiring it into the real path.

---

## 4. Still missing

| | |
| --- | --- |
| **`mwcceppc.exe`** | Still absent, still proprietary, still not obtained. Every `src-match/` result is *mwcc-rs-exact*, not *MWCC-exact*; they coincide only where mwcc-rs is right. |
| **`objdiff-cli`** | Not installed. `objdiff.py` remains the oracle. Worth adding for whole-project reports. |
| **`decomp-toolkit` (`dtk`)** | Not installed. It is what turns per-function matching into per-translation-unit matching, and there is no substitute. |
| **A GC/1.2.5n-capable compiler** | Needed for Calibration A (the SDK objects). mwcc-rs's `1.2.5n` is experimental and incomplete. |

---

## 5. This project's fork of the code generator

**The compiler in `.tools/mwcc-rs` is no longer the pinned commit.** It is the
pinned commit plus the changes below. Nothing is vendored: `.tools/` stays
gitignored and what is committed is
[`mwcc_fork.py`](mwcc_fork.py) plus [`mwcc-rs-fork/`](mwcc-rs-fork/), which
together reconstruct the fork from a fresh extract of the pinned tarball.

```powershell
python research\tools\matching-decomp\mwcc_fork.py --check   # writes nothing
python research\tools\matching-decomp\mwcc_fork.py --apply   # then rebuild
python research\tools\matching-decomp\mwcc_fork.py --capture # dev: live tree -> git
```

Whole files this project wrote live under `mwcc-rs-fork/` at their tree-relative
paths and are copied over; every other change is an exact string replacement
anchored on text that occurs **once** in the pinned file, so `--apply` either
reproduces the fork byte for byte or names the anchor that no longer matches.
Verified: extracting the pinned tarball and running `--apply` yields a tree whose
every file hashes equal to the live checkout.

Reading and writing use `newline=""` throughout. Without that, Python's text mode
rewrites the pinned tree's LF endings as CRLF on this Windows host and every
touched file differs from its reference copy for no reason.

### 5.1 `AND` against a constant that is not an `rlwinm` mask

*Files:* `crates/pipeline/mwcc-syntax-trees-to-machine-code/src/expressions/materialized_bitand_constant.rs`
(rewritten), `crates/representations/mwcc-machine-code/src/{instruction,encoding}.rs`
and `crates/representations/mwcc-vreg/src/description.rs` (one line each, adding
`andis.`).

`rlwinm` can only express a mask that is one contiguous run of set bits. The
pinned generator had that path, and a sibling for a negative mask that fits `li`,
and nothing else — so `x & 0x00FF1F7F` was a hard diagnostic while `|`, `^` and
`+` with the same constant compiled. The fork adds the three forms mwcc actually
uses, which `blocker_census.py` identified by counting them in the retail image:

| constant | form | retail sites |
| --- | --- | ---: |
| fits 16 bits | `andi. rA,rS,UIMM` | 144 |
| low half zero | `andis. rA,rS,UIMM` | 16 |
| both halves set | `lis free,ha; addi r0,free,lo; and rA,rS,r0` | 190 |
| negative, fits `li` | `li r0,SIMM; and rA,rS,r0` (already present) | 80 |

The three-instruction form is specified by retail `zz_008bbc0_` @ `0x8008bbc0`
(`lis r3,0xff; addi r0,r3,0x1f7f; and r3,r4,r0`) and corroborated by the
wide-constant `mullw` path already in the pinned tree, which builds its constant
exactly the same way. Only a full-width (32-bit) leaf takes the new paths: a
narrow leaf needs the promotion reasoning the surrounding code deliberately
defers on, and a wrong `andi.` on an un-extended signed byte is a silent
miscompile, which is the one outcome this compiler must never produce.

*Proof:* `src-match/game/zz_008bbc0_.c` matches byte-identically, on the same C
that had been committed under `blocked/`. Four unit tests in the module cover the
three new forms plus a control that a contiguous mask still takes `rlwinm`.

*Measured corpus impact:* re-running `census.py` over all 12,062 entry points with
this fork against the committed baseline moves the diagnostic
"AND/arith against a constant that is not an `rlwinm` mask" from **115 functions /
8,507 instructions** to **104 / 7,635**, and `COMPILES` from 2,858 to 2,866
functions. Eight functions become compilable; three others clear this gap and
stop at the next one. The remaining 104 are outside the leaf/full-width subset
this change covers.

### 5.2 `*(T *)&aggregate` — the Dolphin SDK's type-punning idiom

*Files:* `crates/pipeline/mwcc-syntax-trees-to-machine-code/src/punned_aggregate_access.rs`
(new), `.../src/lib.rs` (declare the module; run the pass at the top of
`lower_function_body`).

Two of the spike's five blockers were the same mistake twice: mwcc-rs read
`*(T *)&X` as an *address computation* when it is only a *re-typing of storage
that already has an address*.

* `*(u32 *)&obj->Color` — refused, `pointer leaf access needs a pointer variable
  (roadmap)`, because the address operand is a `Member`, not a pointer variable.
* `*(u32 *)&color` on a struct parameter the EABI passes **by reference** —
  compiled, but gave the parameter a stack home:
  `stwu; stw r3,8(r1); lwz r3,8(r1); addi r1,r1,16; blr`, a spill and reload of
  a pointer that was already in a register. Real MWCC emits `lwz r3,0(r3); blr`.

The fork normalises the idiom away before lowering. `*(T *)&X`, where `X` is an
aggregate lvalue whose size equals `sizeof(T)`, becomes an ordinary `T`-typed
member access at `X`'s own offset — which every existing load/store path already
handles, folding the offset into the instruction displacement the way retail
does. A `Member` keeps its offset; a struct-valued `Variable` becomes the member
at offset zero, which is exactly what a by-reference parameter is.

Scope is deliberately narrow: only when the punned-through lvalue is a
`Type::Struct` (a `float`→`u32` pun is a different question with its own
lowering in `float/punned.rs`, which this must not steal), only on an exact size
match, and only for a scalar target type. **Every shape it fires on previously
produced a hard diagnostic or the spill above**, so it cannot silently change
code that already compiled — which is the argument that made a whole-function
AST pass safe to add.

*Proof:* `src-match/sdk/GXInitLightColor.c` now carries the **genuine CC0 body**
from `zeldaret/tp` — `*(u32*)&obj->Color = *(u32*)&color;` — and matches the
retail three instructions as written. It had been a rewrite. This is the first
end-to-end confirmation of the spike's §5.3 free-SDK path: the source exists
under a clear grant *and* the compiler can now take it.

*Measured corpus impact on the GAME, honestly: essentially none.* Re-running
`census.py` moves `pointer leaf access needs a pointer variable` from 1,086
functions to 1,088 — it goes **up**, by two functions that this fork's §5.1
change unblocked and which then stop here. Ghidra's C almost never spells the
idiom (a scan of the whole export finds 6 functions with a `*(T *)&` cast), so
the 77,044 instructions behind that diagnostic are a *different* shape —
`*(T *)(p + k)` on a non-pointer variable — which this pass does not touch and
which remains the fourth-largest gap in `docs/matching-compiler-census.md`.

The value of this change is the SDK, not the corpus: it is 9.8 % of the DOL
(1,065 functions) whose sources are public, and the blocker on using them was
this. Reporting it as a corpus win would be a lie by construction.

### 5.3 `typedef RET (name)(params);` was never registered as a type

*File:* `crates/pipeline/mwcc-tokens-to-syntax-trees/src/items/mod.rs` (one new
branch beside the existing function-POINTER typedef branch).

**This is the largest single change in the fork, and it is eleven lines.**

Every Ghidra export opens with `typedef void (code)();` — a function *type*
alias, parenthesized declarator, no `*` — and then spells every C++ virtual
dispatch as `(**(code **)(*this + 0x30))(this)`. The pinned parser handled
`typedef RET (*name)(params);` (function POINTER) and nothing else, so `code`
was silently never registered. `token_starts_type` then said `code` is not a
type, `(code **)` was not recognized as a cast, and the call failed to parse at
its closing paren:

```
mwcc: expected an expression, found ParenClose at token 23 (line 5, column 16)
      (**(code **)(*p + 0x30))(p);
                 ^
```

A function type occupies no storage — only its pointer forms are objects — so
the alias registers as `void`, which makes `code *` a pointer and `code **` a
pointer to one. That is exactly the type the cast needs, and exactly what a
plain `typedef void code;` already produced (which is how the diagnosis was
made: the same body with `code` spelled as `void` parsed and reached codegen).

**Measured, by re-running `census.py` over all 12,062 entry points:**

| | before | after | delta |
| --- | ---: | ---: | ---: |
| `expected an expression, found ParenClose` | 2,535 fns / 138,420 insns | **2 / 44** | −2,533 fns |
| `FRONT_END_REFUSAL` (all causes) | 2,711 fns / 165,399 insns | 227 / 36,335 | −2,484 fns |
| **`COMPILES`** | 2,866 fns / 71,123 insns | **3,110 / 86,001** | **+244 fns** |

244 functions become compilable outright; the other 2,227 move into
`CODEGEN_UNSUPPORTED`, where they land on the gaps that were hiding behind the
parse error. **That re-ranks the roadmap**, and the new ranking is the true one:

| gap | before | after |
| --- | ---: | ---: |
| `this long long shape is not modeled yet` | 2,210 / 150,293 | **2,638 / 196,122** |
| `pointer leaf access needs a pointer variable` | 1,088 / 77,250 | **1,335 / 91,196** |
| `a signed char load promoted to int needs a sign-extension` | 1,296 / 81,022 | **1,333 / 84,687** |
| `local reassignment mixed with stores/calls` | 218 / 31,223 | 245 / 36,157 |
| `expected a general-register leaf` | 9 / 681 | 47 / 6,248 |

**The indirect-call lowering already exists** and is not a gap: a call through a
function-pointer variable compiles today to the correct `mr r12; mtctr r12;
bctrl` sequence, and a `CallThrough` whose target is a pointer variable
(`(**v)(p)`) compiles too. What remains in front of the vtable idiom is
`*(code **)(*this + 0x30)` — the *address* computation — which is the
`pointer leaf access` row above, i.e. the second entry in the new ranking.

### 5.4 Investigated and NOT closed: the scaled-index register choice

`zz_0298b20_` @ `0x80298b20` compiles; the register allocator diverges on the
first instruction and only there:

```
retail    mulli r0, r4, 0x74      add r3,r3,r0   lwz r3,0x114c(r3)   blr
mwcc-rs   mulli r4, r4, 0x74      add r3,r3,r4   lwz r3,0x114c(r3)   blr
```

**Measured on the retail image — this is the finding.**
`python research/tools/matching-decomp/blocker_census.py --scaled-index` counts
every `mulli` and every power-of-two `slwi` whose product is consumed by an
address computation within four instructions — i.e. the value is an *address
temporary*, not a program value — across all 12,062 functions:

| where the scaled index lands | `mulli` sites | `slwi` sites | combined | share |
| --- | ---: | ---: | ---: | ---: |
| **`r0`, the scratch** | 1,413 | 3,293 | **4,706** | **66.4 %** |
| the index's own register (mwcc-rs's default) | 498 | 510 | 1,008 | 14.2 % |
| a third register | 714 | 657 | 1,371 | 19.4 % |
| total | 2,625 | 4,460 | 7,085 | |

> mwcc-rs's default — reuse the index register when its value dies — is the
> choice MWCC makes **14 % of the time**. Two thirds of the corpus stages the
> scaled index through `r0`.

That is not a tie-break to tune; it is the wrong default. But it is also not a
one-line flip, and this was tested rather than assumed. Upstream already has one
special case that forces `r0` here (`MEMBER_ARRAY_CALL_CURSOR_PREFIX`, in
`expressions/members.rs`, `try_emit_embedded_member_array_element_address`).
**Forcing that preference to `GENERAL_SCRATCH` unconditionally, building, and
re-running `zz_0298b20_` changed nothing** — so this function's `mulli` is not
emitted by that path at all, and the divergence is spread across the ~40 sites
that scale an index, each with its own register reasoning. Reverted.

**Class size, and why it is the top of the roadmap.** `blocker_census.py` counts
3,987 functions (325,969 instructions) whose retail code stages *something*
through `r0` as an index, of which 1,424 (112,095 instructions) have no other
known gap. `docs/matching-compiler-census.md` sees the same wall from the
compiler side under several names — `expression needs the full register
allocator (roadmap M1)`, `a value live across a call needs the callee-saved
register allocator`, `a repeated common sub-expression needs the register
allocator's CSE`, and more.

**What a fix would have to be**: a single register-assignment model for address
temporaries, applied at every scaling site at once, not a per-site preference.
mwcc-rs's README already names matching MWCC's register colouring as the core
research target. Treat this as a known ceiling: a candidate that differs *only*
in which register holds a scaled index is not a bad candidate, and an LLM loop
must not be allowed to burn iterations rewriting C against it. `match.py`'s
`first_diff` names the instruction, so the loop can recognise the signature —
same mnemonic, same immediate, different destination register — and stop.
