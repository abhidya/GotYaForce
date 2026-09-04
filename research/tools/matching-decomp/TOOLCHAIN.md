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

### Install health

```
cargo test --release --workspace --exclude mwcc-oracle
    1,984 passed, 1 failed
```

The one failure is upstream and pre-existing at this commit:
`inline_expansion::tests::composes_zero_argument_embedded_asm_at_a_nested_call_site`,
which concerns inline embedded assembly at a nested call site. Nothing in `src-match/`
touches that path. Recorded so a future run does not mistake it for local damage.

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
| **`AND` with a 32-bit constant that is not an `rlwinm` mask** | **refused**: `a general register was requested for a non-leaf expression: IntegerLiteral(...)`. `OR`/`XOR`/`ADD` with the same constant are fine. |
| **Load/store with update (`lbzu`, `lwzu`)** | not generated |
| **`&param` on a by-reference struct parameter** | compiles, but spills the incoming pointer to a stack home and reloads it; real MWCC uses the register directly |
| **`*(u32 *)&struct.member`** | **refused**: `pointer leaf access needs a pointer variable (roadmap)` |
| **Routing an index computation through the scratch register `r0`** | not reproduced — see `zz_0298b20_` in `matched.json` |
| Comparison of a value against a large constant | **refused**: `this comparison needs the branchless compare idioms (roadmap)` |

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

### The other half of the same bug, and its fix

That fix covered `R_PPC_REL24` only, because a linked DOL has no data symbol table — so a
candidate whose match rested on a **data** relocation (`R_PPC_ADDR16_HA/LO/HI`,
`R_PPC_ADDR32`, `R_PPC_EMB_SDA21`) had that operand masked and never checked, and would
have matched **any global in the game**.

[`datareloc.py`](datareloc.py) closes it, and does so without weakening anything:

* the **retail encoding** names one absolute address — `d(r13)` against `_SDA_BASE_`, or a
  `lis`/`addi` pair — and `datareloc.retail_data_addresses` reads it out of the bytes;
* the **candidate's** relocation symbol names one absolute address, resolved from the link
  map, the address encoded in the name (`DAT_80436498`, `PTR_DAT_8043393c`), or
  `research/decomp/data/oracle-registry.json`;
* `objdiff.compare` requires them to be **equal**. Different → `MISMATCH`. Either side
  unresolvable → `MATCH_UNVERIFIED`, never `MATCH`.

The two small-data bases are derived twice and cross-checked — from the ROM's own
`__init_registers` and from the DOL section table (`.sdata`/`.sdata2` start + 0x8000) — and
`datareloc` refuses to produce them at all if the derivations disagree. Run
`python research/tools/matching-decomp/datareloc.py --bases` to see both, or add a function
name to list every data reference in it.

Regressions: selftest **T8/T8b/T8c/T8d** (compiler-free, synthetic `EMB_SDA21` object) and
five compiler-driven `DATA_RELOC_CONTROLS` in `src-match/verify.py --control`. The
`zz_000a144_` control naming `DAT_804360c8`/`DAT_804360c4` instead of
`DAT_804360cc`/`DAT_804360c8` reported `MATCH 100.00%` before this existed.

`sda_recover.py` is the recovery driver that used it: it re-derives C for the 104 functions
`loop.seed_leaf` refuses for r2/r13 access and records the 76 that match. `loop.py`'s own
seeders are untouched; a seeder lifts its refusal by calling `datareloc.global_symbol`,
`global_decl` and `sda_bases`.

---

## 4. Still missing

| | |
| --- | --- |
| **`mwcceppc.exe`** | Still absent, still proprietary, still not obtained. Every `src-match/` result is *mwcc-rs-exact*, not *MWCC-exact*; they coincide only where mwcc-rs is right. |
| **`objdiff-cli`** | Not installed. `objdiff.py` remains the oracle. Worth adding for whole-project reports. |
| **`decomp-toolkit` (`dtk`)** | Not installed. It is what turns per-function matching into per-translation-unit matching, and there is no substitute. |
| **A GC/1.2.5n-capable compiler** | Needed for Calibration A (the SDK objects). mwcc-rs's `1.2.5n` is experimental and incomplete. |
