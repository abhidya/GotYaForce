# Matching decompilation — feasibility spike

**Date: 2026-09-03.** Status: **SPIKE RESULT, then TEST RUN the same day.**

> **SUPERSEDED IN PART, 2026-09-04 — read [`docs/matching-loop.md`](matching-loop.md)
> alongside this.** §4.1's loop was built and run. The matched corpus is now **405
> functions / 1,773 instructions (0.2528 % of the code)**, not 13 / 43, and **392 of the
> new ones were produced with zero model calls** by a mechanical seeder. Three of this
> document's numbers move and one does not:
>
> * §3.1.5's "233 functions share a matched shape" measures as **234**; **171 of the 221
>   not already matched were matched at iteration 0**, in 4.5 seconds of CPU.
> * §3.1's "1.08 iterations per function" becomes **1.00 over 405**, for the class whose C
>   is derivable from the encodings — still not §4.2's *moderate*-tier number.
> * §4.1's permuter idea measures **zero**: 580 mechanical mutants closed nothing, because
>   all 15 near-misses were compiler limits, not C differences — §3.1.3's finding at scale.
> * **§4.2's 2.6 GPU-years does NOT move**: 23,024 → 22,983 GPU-hours, a 0.18 % reduction,
>   because 96 % of that bill is the *moderate*/*hard*/*research* tiers.
>
> §6.2.1's step 0 — contributing lowerings to `mwcc-rs` — is confirmed as the binding item.

> ### The decisive test ran, and thirteen functions of Gotcha Force are matched.
>
> This document was written when there was no PowerPC compiler on the machine. There is
> one now — `zcanann/mwcc-rs`, built from source, provenance in
> [`research/tools/matching-decomp/TOOLCHAIN.md`](../research/tools/matching-decomp/TOOLCHAIN.md).
> **§3.1 has been rewritten from "It could not run" to the result**, and the sections it
> contradicts carry inline corrections. The original text is preserved wherever it was
> replaced. `mwcceppc.exe` is still absent and was not obtained.
>
> | | |
> | --- | --- |
> | **13 functions byte-identical to retail** | 43 instructions, **0.0061 % of the code**. Committed at [`src-match/`](../src-match/) with a registry and a one-command verifier. Includes a call with a real `R_PPC_REL24` and two conditional-return control-flow cases. §3.1 |
> | **1.08 iterations per function** | 14 candidates for 13 matches. **This is not the LLM loop's number** — these are 2-to-8-instruction accessors, not §4.2's *moderate* tier, which remains unmeasured. §3.1 |
> | **The version question is partly unanswerable** | Calibration B returned only *"not GC/1.3"*. GC/2.5, 2.6 and 2.7 are the same code generator and differ only in a `.comment` marker a linked DOL does not preserve. §3.1.2 |
> | **The wall is the compiler, not the C** | All five non-matches were compiler capability limits, including the spike's own first-choice target. §3.1.3 |
> | **`mwcc-rs` is 83 % memorisation** | 558 whole-function captures fire on exact name + AST hash; none covers this game. Only the 28,345-line general generator applies here. §3.1.4 |
> | **The free 9.8 % has a licence problem, and a fix** | `doldecomp/dolsdk2004`, which §5.3 recommended, has **no licence at all**. `zeldaret/tp` is **CC0-1.0** and carries the same SDK tree. §5.3.1 |
> | **233 functions share a matched shape** | The near-certain next matches — 1.93 % of entry points but **0.169 % of instructions**. §5.2's warning, with real numbers. §3.1.5 |
> | **The oracle had a hole** | `match.py` masked relocated operands but never checked the relocation's *symbol* — a candidate calling the wrong function reported MATCH. Fixed, with a permanent negative control. §3.1.1 |

Everything measured below was measured in this worktree today by the tools in
[`research/tools/matching-decomp/`](../research/tools/matching-decomp/), reading the retail
GCM at `D:/GotYaForce/Gotcha Force.iso` and the link map at
[`research/symbols/GG4E-CSM-20220412.map`](../research/symbols/GG4E-CSM-20220412.map).
No pipeline state was touched, no unit was promoted, no driver or supervisor was contacted,
and neither the GPU nor the model server was used — both were unavailable and nothing here
waited on them. Nothing was downloaded.

Sibling spike: [`docs/static-recompilation-spike.md`](static-recompilation-spike.md), whose
DOL-extraction logic is reused. Results here are not comparable with, and must never be
summed with, any wasm-unit verification tier.

---

## 0. The question, and the answer

The owner wants a **compilable, playable, 1:1 reverse engineered game** — real source code,
explicitly *not* an emulator and *not* a mechanical transliteration. Matching decompilation
is the technique that delivers exactly that: write C, compile it with the original
Metrowerks CodeWarrior compiler, diff the object code against the retail binary until it is
byte-identical. A matched function is not *argued* to be the same program; it is the same
program. And because the artifact is ordinary C, it can afterwards be compiled for
*anything* — including wasm.

The brief's premise was that this technique has a **free, exact, automatic oracle** —
compile and diff, definitive yes/no per function, in under a second, with no hand-authored
spec and no Dolphin capture — and that this makes it the highest-leverage use of a local
model. Two separate questions follow, and **they get opposite answers.**

> ### Is matching decompilation the right route? **YES.**
>
> It is the only route that produces what the owner actually asked for, its oracle is
> everything the brief claimed, and — decisively — **the 2026 published record shows an
> LLM-driven matching loop reaching 88.78 % of a same-sized GameCube title in about seven
> months**, where every human-driven project of that scale took three to six years. §5.4

> ### Can the *local* model drive it? **NO, and not close.**
>
> At the decode rate this project has already measured on its own GPU — 2.5 tok/s for a 27B
> model on the GTX 1080 Ti — the loop costs **23,024 GPU-hours = 2.6 GPU-years** to match
> 25 % of the game by code volume. The published successes ran hosted frontier models in
> agent loops. **The difference between 2.6 GPU-years and eight months is the model, not
> the method.** §4

Three findings shape what to do about that:

| | |
| --- | --- |
| **The compiler is not on this machine** — no `mwcceppc`, no PPC compiler of any kind. But an **open-source, MIT-licensed from-scratch reimplementation (`zcanann/mwcc-rs`) reports eight GameCube builds byte-exact, GC/1.3 through GC/2.7**, which is very likely the range this game needs. That is a provenance-clean path that did not exist a year ago. §1 |
| **The compiler version is determinable, and the strongest prior is GC/2.7.** The 996 SDK symbols in this project's map came from the GNT4 decomp — a 2003 title that uses GC/2.7. A correction is also recorded here: the `(0x2301)` in the SDK banners is **not** a version tag. §2 |
| **9.8 % of the DOL is already solved in public.** 1,065 Dolphin SDK / MetroTRK functions, whose sources exist as an open decomp project (`doldecomp/dolsdk2004`). These are exactly the functions the current pipeline cannot handle (gap **H8**). §5.3 |

---

## 1. Toolchain availability

> **SUPERSEDED IN PART, 2026-09-03.** §1.1's survey was accurate when made and is kept
> as written. A compiler has since been installed —
> [`research/tools/matching-decomp/TOOLCHAIN.md`](../research/tools/matching-decomp/TOOLCHAIN.md)
> records exactly what, from where, and what it can do; §3.1 records the result.
> `mwcceppc.exe` is **still absent** and was not obtained.

### 1.1 What is on this machine: nothing

Searched: every `PATH` entry; `D:\GotYaForce` in full including `.tools/`, `tools/`,
`dolphin/`, `ghidra_*`, `node_modules`; `C:\Users\manny` including `AppData`, `Downloads`,
`Documents`; `C:\Program Files`, `C:\Program Files (x86)`, `C:\ProgramData`, `C:\devkitPro`;
and the `E:` and `K:` mirror drives to depth 6. All four filesystem drives on this machine
were covered. Patterns: `mwcceppc*`, `mwldeppc*`, `mwasmeppc*`, `mwcc*.exe`, `objdiff*`,
`dtk.exe`, `powerpc-eabi-*`, `*CodeWarrior*`, `wibo*`. **The only hit anywhere was this
spike's own `objdiff.py`.**

| Tool | Role | Present? |
| --- | --- | :--- |
| **`mwcceppc.exe`** | **the oracle itself** — no compiler, no match test | **NO** |
| `mwldeppc.exe` / `mwasmeppc.exe` | link / assemble | NO |
| CodeWarrior for GameCube, any version | — | NO |
| `objdiff` / `objdiff-cli` | community object differ | NO |
| `decomp-toolkit` (`dtk`) | DOL analysis, splitting, object extraction | NO |
| `ppcdis`, `splat` | PPC disassembly / splitting | NO |
| devkitPPC (`powerpc-eabi-gcc`) | a non-matching PPC compiler; stand-in only | NO |
| Wine / `wibo` | Win32 shim | NO — **and not needed; see §1.3** |
| **Any PowerPC-capable compiler at all** | — | **NO** |

The last row is the finding. The repository's pinned Emscripten LLVM
(`research/tools/emsdk/upstream/bin/clang.exe`, clang 24.0.0git) reports its registered
targets as **`wasm32`, `wasm64`, `x86`, `x86-64`** — the PowerPC backend is not compiled in.
Present and used by the harness: Anaconda Python 3.7.3 with capstone 5.0.1. Also present:
`node`. Absent: `cargo`, `rustc`, `gcc`, `clang`, `zig`, `llvm-mc`.

```
$ python research/tools/matching-decomp/match.py --detect
{ "mwcceppc": null, "objdiff_cli": null, "dtk": null, "devkitppc": null, "wine": null }
exit 3
```

### 1.2 What must be obtained, and the honest position on each

**Nothing was downloaded by this spike, and no acquisition link is reproduced here.** The
options differ sharply in provenance and the owner should decide, not an agent.

**(a) `zcanann/mwcc-rs` — open source, and the reason this section is not a dead end.**
A from-scratch Rust reimplementation of MWCC for embedded PowerPC, MIT-ish licence, created
2026-07-18 and actively developed. Its README states that **eight GameCube builds — GC/1.3
through GC/2.7, including GC/2.0p1 — are byte-exact today**. If this game is GC/2.6 or
GC/2.7 (§2.3 argues it is), this covers the game code with clean provenance and no licensing
question. Two caveats, both real: it **does not yet cover GC/1.2.5n**, which is what the SDK
objects need (§2.4), and "byte-exact" is the project's own claim, verifiable here in an
afternoon with `objdiff.py` and the calibration set in §2.4 — which is exactly the first
thing to do with it.

> **Verified 2026-09-03. Installed, built, and used — §3.1. Three corrections to the
> paragraph above, in descending order of importance.**
>
> 1. **"Byte-exact" rests largely on memorisation.** 143,268 of the code generator's
>    171,613 lines — **83 %** — are 558 whole-function *captures* that fire on an exact
>    function-name and AST-hash match against reference decomp projects. For a binary
>    with nothing in the capture set, only the remaining 28,345-line general generator
>    applies. §3.1.4.
> 2. **"MIT-ish" is right but loose: there is no `LICENSE` file in the repository.**
>    `Cargo.toml` declares `license = "MIT OR Apache-2.0"` and the README says
>    "Dual-licensed under MIT or Apache-2.0". Clear intent, no licence file. It affects
>    redistribution, not local use.
> 3. **GC/1.2.5n now exists as a build identity**, but only behind
>    `MWCC_EXPERIMENTAL_BUILDS` and explicitly incomplete — so §2.4's Calibration A still
>    cannot be run, exactly as this paragraph predicted.

**(b) A licensed copy of CodeWarrior for GameCube.** The genuine article. Realistically
obtainable only via an old development-kit licence. NXP's free "CodeWarrior Special Edition"
does **not** help: it covers ColdFire, DSC, HCS12, Kinetis, Qorivva and MPC55xx/56xx, has no
GameCube or Gekko target, and would not produce matching code even if it built PowerPC.

**(c) The community `compilers_*.zip` bundle** that every `dtk`-based project downloads.
It is redistribution of proprietary Metrowerks binaries by a third party. It is *not* a
licence, and this document does not recommend it. Recorded because the owner will encounter
it and should encounter it labelled.

**Dolphin SDK sources are a separate and much better story.** `doldecomp/dolsdk2004` is an
open decompilation of the 20 April 2004 Dolphin SDK, reporting ~100 % for most libraries.
That is public source for the SDK half of §5.3 — no Nintendo-confidential header set
required.

### 1.3 The ecosystem, and one thing in this machine's favour

`mwcceppc.exe` is a **32-bit Windows console binary**. On 64-bit Windows 10 it runs
**natively under WOW64** — no Wine, no `wibo`, no WSL, no 32-bit VM. The `dtk-template`
documentation is explicit that native Windows tooling is the recommended path and that WSL
and msys2 are not required. **This machine being Windows removes the single most common
setup obstacle**, and it is the one structural advantage this project has here.

The two tools worth adding when a compiler exists, both Rust, both shipping Windows x86-64
binaries:

- **`objdiff-cli`** — the reference object differ, with a genuine non-interactive mode:
  `objdiff-cli diff -1 target.o -2 base.o <symbol> -o - --format json`, plus
  `objdiff-cli report generate` for whole-project measures. It is what powers the public
  progress dashboards. [`objdiff.py`](../research/tools/matching-decomp/objdiff.py) here
  reimplements the comparison rule in ~200 lines so this spike has no external dependency;
  for production, use `objdiff-cli` and keep `objdiff.py` as the reference implementation
  and selftest.
- **`decomp-toolkit` (`dtk`)** — DOL analysis and, critically, **splitting the DOL into
  relocatable objects without an assembler**. This is the piece that makes per-function
  matching into per-translation-unit matching, and there is no substitute for it.

`ppcdis` is deprecated by its own author in favour of `dtk`. `splat` explicitly does not
support GameCube. `decomp.me` is self-hostable via Docker but is a scratchpad, not a loop.

---

## 2. Which compiler version this game needs

The wrong MWCC build never matches, so this must be pinned before any C is written.
Tools: [`fingerprint.py`](../research/tools/matching-decomp/fingerprint.py),
[`banners.py`](../research/tools/matching-decomp/banners.py).

### 2.1 It is Metrowerks, not GCC — and this is not close

Four independent lines over the 701,464 instructions of `.init` + `.text`:

| Evidence | Measurement |
| --- | --- |
| MSL runtime string | `Metrowerks CW runtime library initializing default heap` @ `0x802b4d58` |
| Metrowerks debug stub | `MetroTRK for GAMECUBE v2.0` @ `0x802b44c0`, plus 69 `TRK_*` / `__TRK*` map symbols |
| **Frame-setup order** | **5,357** sites `stwu r1,-N(r1)` → `mflr r0` → `stw r0,N+4(r1)` (Metrowerks). **277** `mflr r0` → `stw r0,4(r1)` → `stwu` (GCC order). **95.1 % : 4.9 %** |
| **32-bit constant idiom** | **2,593** `lis`+`addi` vs **62** `lis`+`ori` — **42 : 1**. MWCC builds constants with `addi`; GCC uses `ori` |

The 4.9 % residue is almost certainly not a second compiler: hand-written SDK assembly
(`OSExceptionVector`, `__OSDBIntegrator`, the `PPCMf*`/`PPCMt*` accessors) and MWCC's own
alternate frame path both produce it. Note also that GNT4's build applies a post-pass called
`-fprologue-fixup=old_stack` for precisely this class of prologue-order discrepancy, so a
residue of this shape is expected rather than alarming.

Corroborating the flag set: **16,055 `r2`-relative and 8,995 `r13`-relative** references say
`-sdata2`/`-sdata` are on; **2,883 paired-single instructions** say `-proc gekko -fp hard`.

### 2.2 A correction: `(0x2301)` is not a version number

Thirteen Dolphin SDK release banners are embedded verbatim in the data sections:

```
0x803a32bf  << Dolphin SDK - OS    release build: Apr 17 2003 12:33:06 (0x2301) >>
0x803a4ba7  << Dolphin SDK - EXI   release build: Apr 17 2003 12:33:17 (0x2301) >>
0x803a4cb8  << Dolphin SDK - SI    release build: Apr 17 2003 12:33:19 (0x2301) >>
0x803a4fe8  << Dolphin SDK - DVD   release build: Apr 22 2003 15:49:00 (0x2301) >>
0x803a5650  << Dolphin SDK - VI    release build: Apr 17 2003 12:33:22 (0x2301) >>
0x803a5a20  << Dolphin SDK - PAD   release build: Apr 17 2003 12:33:44 (0x2301) >>
0x803a5a78  << Dolphin SDK - AI    release build: Apr 17 2003 12:33:54 (0x2301) >>
0x803a5ac0  << Dolphin SDK - AR    release build: Apr 17 2003 12:33:55 (0x2301) >>
0x803a5b08  << Dolphin SDK - ARQ   release build: Apr 17 2003 12:33:56 (0x2301) >>
0x803a5b50  << Dolphin SDK - AX    release build: Apr 17 2003 12:33:57 (0x2301) >>
0x803aa140  << Dolphin SDK - DSP   release build: Apr 17 2003 12:34:16 (0x2301) >>
0x803aa300  << Dolphin SDK - CARD  release build: Apr 17 2003 12:34:19 (0x2301) >>
0x803aa500  << Dolphin SDK - GX    release build: Apr 21 2003 14:55:46 (0x2301) >>
```

My first reading of this was that `0x2301` identified the SDK revision. **That is wrong, and
the correction matters enough to record.** `0x2301` is a hard-coded literal in the SDK's own
`src/os/OS.c` — it appears identically in the decompiled 2004 SDK, and the same constant has
been observed on GameCube titles built in September 2002. It spans at least Sep 2002 →
Apr 2004 and discriminates nothing.

**The build dates are the signal**: OS/EXI/SI/VI/PAD/AI/AR/ARQ/AX/DSP/CARD all
**17 April 2003**, GX **21 April 2003**, DVD **22 April 2003**. So: an SDK cut in late
April 2003, sitting between the two SDKs the community has decompiled (23 May 2001 and
20 April 2004). No public Apr-2003 SDK dump is known to exist. The game's CRI middleware
(ADX 8.57, ADXF 7.01, sofdec/CVFS 2.33, SKG 0.61) is stamped `Build:Feb 6 2003`, bracketing
the game build from below and consistent with the 2003 release.

### 2.3 Best determination: GC/2.7, then GC/2.6

The decomp community's compiler identifiers map to internal MWCC builds as
`GC/2.0` = 2.4.7 build 92, `GC/2.5` = build 105, `GC/2.6` = build 107, `GC/2.7` = build 108,
with the older `GC/1.x` line on 2.3.3 and 2.4.2.

What comparable titles settled on:

| Title | Year | Game-code compiler |
| --- | --- | --- |
| **Naruto: Clash of Ninja 4 (GNT4)** | **2003** | **GC/2.7** |
| Twilight Princess | 2006 | GC/2.7 |
| Mario Kart: Double Dash!! | 2003 | GC/2.6 |
| Pikmin 2 | 2004 | GC/2.6 |
| Paper Mario: TTYD | 2004 | GC/2.6 |
| Battle for Bikini Bottom | 2003 | GC/2.6 (+2.0p1, 1.3.2) |
| Metroid Prime | 2002 | GC/1.3.2 |
| Wind Waker | 2002 | GC/1.3.2 |
| Super Mario Sunshine | 2002 | GC/1.2.5 |
| Melee | 2001 | GC/1.2.5 / 1.2.5n |

**Ranked candidates for Gotcha Force: GC/2.7 first, then GC/2.6, then GC/2.5 and GC/2.0.**

The reason GC/2.7 leads is not the date alone. **This project's 996 SDK symbol names carry a
`gnt4-` prefix**, meaning they were imported from the GNT4 decomp's symbol database — and
GNT4 is a 2003 GameCube title, built on the same Dolphin SDK + MSL + MetroTRK surface, that
uses **GC/2.7**. That is the closest available analogue and it is closer than any date
heuristic. Treat it as the strongest prior, not as a conclusion.

The harness's starting flags, in
[`match.py:DEFAULT_CFLAGS`](../research/tools/matching-decomp/match.py), are modelled on
GNT4's own: `-proc gekko -fp hard -O4,p -nodefaults -Cpp_exceptions off -enum int
-msgstyle gcc -inline auto -sdata 8 -sdata2 8`. `-proc gekko` is not optional — 2,883
paired-single instructions require it.

### 2.4 How to confirm it — mechanically, with no guessing

**Two distinct calibrations, and conflating them is a trap.** Across essentially every
GameCube decomp, Nintendo shipped the SDK as **prebuilt libraries compiled with GC/1.2.5n**,
regardless of which compiler the game itself used. So:

**Calibration A — the SDK compiler (expected: GC/1.2.5n).** Take short SDK functions with
fixed public sources — `OSGetTick`, `PPCMfmsr`, `DCFlushRange`, `memcpy`, `PSMTXIdentity` —
compile with each candidate, diff with `objdiff.py`. This validates the whole harness against
a known answer and settles the SDK half of §5.3. It says **nothing** about the game
compiler.

**Calibration B — the game compiler.** Take a dozen small *game* functions across several
map neighbourhoods (`zz_008bbc0_`, `zz_00660b8_`, `zz_00122c8_` from §3.4 are ready), and
sweep GC/2.7 → 2.6 → 2.5 → 2.0 × `-O4,p` / `-O4` / `-O3` / `-opt level=0`. **Exactly one
(version, flags) combination reproduces the retail bytes across all of them.** That is the
answer, and it is not an opinion.

Both cost minutes of CPU once a compiler exists, need no model, and settle §2.3 outright.
**Nothing downstream should be attempted before Calibration B passes**, because every result
after it is void if the version is wrong.

---

## 3. The decisive test

> **UPDATED 2026-09-03, later the same day.** §3.1 originally read "It could not run."
> A compiler was then installed and **the test ran**. §3.1 below is the result; the
> original statement is preserved at §3.1.0 because the sequence matters. Everything
> from §3.2 onward is unchanged and was written before the compiler existed.

### 3.1.0 The original entry, kept

> The brief's decisive test was: pick a small leaf function, write C, compile with MWCC,
> diff. **`mwcceppc.exe` does not exist on this machine, and no PowerPC compiler of any
> kind does (§1.1). The test could not be run. No function was matched.**

### 3.1 It ran. Thirteen functions are matched.

The owner approved installing `zcanann/mwcc-rs` — the open-source Rust reimplementation
§1.2(a) identified. Rust 1.98.1 and mwcc-rs commit `7c093483` were built from source;
[`research/tools/matching-decomp/TOOLCHAIN.md`](../research/tools/matching-decomp/TOOLCHAIN.md)
records provenance, hashes and the exact build commands. No proprietary binary was
fetched. **`mwcceppc.exe` is still absent and still not obtained.**

**Thirteen functions of Gotcha Force now compile byte-identically to the retail image.**
They live in [`src-match/`](../src-match/) with a registry, per-file headers carrying the
retail disassembly, and a one-command verifier.

```
$ python src-match/verify.py --control
MATCHED CORPUS  backend=mwcc-rs  commit=7c093483f9c6  build=2.7
------------------------------------------------------------------------
[ok  ] zz_0206f8c_                2    insns  MATCH         iters=1  exact=true
[ok  ] zz_00122c8_                8    insns  MATCH         iters=1  exact=false
[ok  ] zz_02650c0_                3    insns  MATCH         iters=2  exact=true
[ok  ] zz_0268460_                3    insns  MATCH         iters=1  exact=true
[ok  ] zz_008b900_                2    insns  MATCH         iters=1  exact=true
[ok  ] zz_0018824_                2    insns  MATCH         iters=1  exact=true
[ok  ] zz_0009c28_                2    insns  MATCH         iters=1  exact=true
[ok  ] zz_0009c30_                2    insns  MATCH         iters=1  exact=true
[ok  ] zz_007f88c_                3    insns  MATCH         iters=1  exact=true
[ok  ] zz_00e199c_                3    insns  MATCH         iters=1  exact=true
[ok  ] zz_02a0a6c_                5    insns  MATCH         iters=1  exact=true
[ok  ] zz_027ac98_                5    insns  MATCH         iters=1  exact=true
[ok  ] gnt4-GXInitLightColor-bl   3    insns  MATCH         iters=1  exact=true

NEGATIVE CONTROLS (each MUST be rejected)
------------------------------------------------------------------------
[ok  ] zz_0206f8c_                rejected=True  (wrong structure offset)
[ok  ] zz_00122c8_                rejected=True  (right shape, WRONG CALLEE)
[ok  ] zz_02a0a6c_                rejected=True  (behaviourally identical, differently encoded)

16 ok, 0 failed
```

**The first match.** `zz_0206f8c_` @ `0x80206f8c`, a member accessor, matched on the
first candidate written:

```
        retail                           candidate
80206f8c  lwz r3, 0x2d4(r3)          |   lwz r3, 0x2d4(r3)
80206f90  blr                        |   blr
VERDICT MATCH  100.00%   exact_bytes: true
```

from

```c
typedef struct S { char pad[0x2d4]; int field_2d4; } S;
int f(S *s) { return s->field_2d4; }
```

**The second, harder one — a call, which is what makes relocations real.** `zz_00122c8_`
@ `0x800122c8`, the canonical Metrowerks non-leaf frame with one `bl`, also on the first
candidate. This is the function §3.3's T6/T7 controls were built around, and it behaves
exactly as they predicted: `exact_bytes` is **false**, because the compiled `bl` operand
is zero before linking, and the match is carried by an `R_PPC_REL24` at `+0x0c` naming
`zz_0012308_` — which is the symbol the retail branch target resolves to through the
link map.

Then a control flow case, `zz_02a0a6c_` @ `0x802a0a6c`, where Metrowerks turns a null
guard into a conditional return:

```
802a0a6c  cmplwi r3, 0     |   cmplwi r3, 0
802a0a70  beqlr            |   beqlr
802a0a74  li r0, 4         |   li r0, 4
802a0a78  stw r0, 0(r3)    |   stw r0, 0(r3)
802a0a7c  blr              |   blr
```

**Iteration counts, which is the number this test existed to produce.** 13 functions,
**14 iterations total — a mean of 1.08.** Twelve of the thirteen matched on the first
candidate. The one that took two was `zz_02650c0_`, where the first candidate returned
`char` and lost the retail's `extsb`; widening the return type to `int` put it back.

**That number is not the LLM loop's iteration count, and must not be used as one.** It
is what a reader who already has the disassembly in front of them spends on functions of
two to eight instructions in shapes that recur across the binary. §4.2's budgets are
about *moderate*-tier functions of 33–128 instructions, which is a different problem, and
nothing here measures those — see §3.1.3.

### 3.1.1 One harness bug, found by running it

`match.py` masked relocated operand fields, per §3.2's rule, but **never passed the
retail's expected symbol to the comparator**. A candidate calling the wrong function
therefore reported MATCH. T6b had always tested the rule; nothing wired it into the real
path. Fixed: branch targets are now resolved through the link map and checked. The
regression is a permanent negative control in `verify.py`. Worth stating plainly —
**the oracle had a hole in it for as long as it was never run.**

### 3.1.2 What the sweep says about the compiler version: much less than hoped

§2.4's Calibration B was to sweep version × flags and find the single combination that
reproduces the retail bytes. `match.py --sweep` implements it. Run across all thirteen:

| function | rows matching | conclusion |
| --- | --- | --- |
| `zz_02650c0_`, `zz_0268460_` | 36 / 42 | **excludes GC/1.3** |
| the other eleven | 42 / 42 | no discrimination whatsoever |

The two that discriminate are the signed-`char` accessors, and they work because plain
`char` is unsigned in GC/1.3 (mwcceppc 2.4.2 build 53) and signed from GC/1.3.2 on. The
retail `extsb` says the game is **not** GC/1.3.

That is the entire mechanical result, and it is much weaker than §2.4 anticipated. Three
reasons, all structural:

1. **`GC/2.5`, `GC/2.6` and `GC/2.7` are the same code generator in mwcc-rs.** They
   differ only in the object's `.comment` marker, and a linked DOL does not preserve
   `.comment`. **No `.text` evidence can ever separate them** — not with mwcc-rs, and, for
   the marker specifically, not with the genuine compiler either.
2. **The functions mwcc-rs can compile are the functions too small to discriminate.**
   Version differences live in register allocation, scheduling and aggregate handling —
   exactly the constructs §3.1.3 lists as out of envelope.
3. **Calibration A cannot be run at all.** It needs GC/1.2.5n; mwcc-rs carries that
   identity only as an incomplete experimental profile.

**So §2.3's ranking is still a prior, not a result.** GC/2.7 remains the working label,
now with GC/1.3 mechanically excluded and 2.5/2.6/2.7 shown to be indistinguishable in
principle. §8's uncertainty 2 stands, narrowed.

### 3.1.3 Where it stops, and why the wall is the compiler

Five functions were attempted and not matched. Every one was blocked by the compiler,
not by the C — recorded in full in [`src-match/matched.json`](../src-match/matched.json).

| target | blocker |
| --- | --- |
| **`zz_008bbc0_`** — §3.4's own first-choice target | `AND` against `0x00FF1F7F`: *"a general register was requested for a non-leaf expression: IntegerLiteral(16719743)"*. mwcc-rs implements only the `rlwinm` mask path; real MWCC materialises the constant with `lis`+`addi`. `OR`/`XOR`/`ADD` with the same constant compile fine — **one missing lowering, not a deep gap.** |
| `zz_0298b20_` — array-of-struct index | Retail `mulli r0, r4, 0x74`; mwcc-rs `mulli r4, r4, 0x74`. Retail routes the scaled index through the scratch `r0`; mwcc-rs reuses the dead input. **Four different C spellings, same divergence** — it is not reachable from the source. mwcc-rs's README names matching MWCC's register colouring as *"the core research target"*. |
| `strlen` | mwcc-rs does not generate the load-with-update form (`lbzu`). |
| `zz_00d1cbc_` — an uncounted pointer walk | *"loop codegen is not implemented yet (roadmap)"*. Counted `for` loops **do** lower to `mtctr`/`bdnz`; `while (a && b)` does not. |
| `zz_02a9654_` | Reads the time base (`mftbu`/`mftb`). Not expressible in C — needs inline asm. Excluded, not failed. |

mwcc-rs keeps a standing rule that it **fails honestly**: every one of those is a
diagnostic, never plausible-but-wrong bytes. That is what makes it safe to use here, and
it means a `BUILD_FAILED` must be read as a statement about the compiler.

### 3.1.4 The correction that matters most: what mwcc-rs is

§1.2(a) took "eight GameCube builds byte-exact" at face value, flagging only that it was
the project's own claim. Reading the source at the pinned commit:

```
crates/pipeline/mwcc-syntax-trees-to-machine-code/src/captures/   143,268 lines
crates/pipeline/mwcc-syntax-trees-to-machine-code/src/ (rest)      28,345 lines
```

**558 whole-function captures — 83 % of the code generator by line count.** Each fires
only when a function's *name* and a hash of its *AST* match a specific function from a
reference decomp project. `captures/ari_abs.rs` fires on a function literally named
`abs`; `acf_two_exp.rs` is 180 KB for one function.

**This is not a criticism.** mwcc-rs exists to get existing decomp projects to green, and
memorising a function whose source you already have is a legitimate way to do that. But
it changes what the parity claim means **for a project like this one**: no Gotcha Force
function is in the capture set, so **only the 28,345-line general generator applies**, and
that generator's envelope is §3.1.3's table. Every result in `src-match/` went through it.

### 3.1.5 What the thirteen unlock — and a fresh illustration of §5.2

A *shape* is a function's ordered tuple of mnemonics. Two functions of the same shape
differ only in operands, so a matched function is a worked example for every other
function that shares its shape — these are the near-certain next matches. Counting
them over the census (all 3,066 functions of ≤ 16 instructions, exact shape match):

| functions | instructions | shape | matched exemplar |
| ---: | ---: | --- | --- |
| **114** | 912 | `stwu mflr stw bl lwz mtlr addi blr` | `zz_00122c8_` |
| 47 | 94 | `lwz blr` | `zz_0206f8c_` |
| 26 | 52 | `li blr` | `zz_008b900_` |
| 22 | 44 | `stw blr` | `zz_0009c28_` |
| 12 | 40 | `li stb blr` | `zz_007f88c_` |
| 5 | 15 | `lwz stw blr` | `gnt4-GXInitLightColor-bl` |
| 4 | 20 | `cmplwi beqlr li stw blr` | `zz_02a0a6c_` |
| 3 | 9 | `lbz extsb blr` | `zz_02650c0_` |
| **233** | **1,186** | **total** | |

The 114-function bucket is the single-call wrapper, and each one needs nothing but its
callee's name — which `match.py --context` already resolves through the link map. **They
are close to free.**

And then the number that matters:

> **233 functions is 1.93 % of the entry points and 0.169 % of the instructions.**

Eighteen times the functions this test matched, and still under a fifth of one percent of
the game. §5.2 warned that a loop which only ever solves short functions can report
"46 % matched" having touched 13 % of the code. **Here is that warning with real numbers
attached, from real matches, on the first day the loop existed.** Report this work by
instructions.

### 3.2 What was built and proven instead

Everything on both sides of the compiler. The harness is complete and tested; the compiler is
a hole in the middle that `match.py` detects and reports rather than papers over.

| File | Role |
| --- | --- |
| [`dolsym.py`](../research/tools/matching-decomp/dolsym.py) | DOL out of the GCM + link map → **exact retail bytes** for any named function |
| [`ppcdis.py`](../research/tools/matching-decomp/ppcdis.py) | Gekko-correct disassembly; overrides capstone on primaries 4/56/57/60/61 and `fcmpo`, which it renders as AltiVec/VSX |
| [`objdiff.py`](../research/tools/matching-decomp/objdiff.py) | **the oracle**: relocation-aware byte comparison, MATCH/MISMATCH, first-difference localisation, JSON verdict, exit code |
| [`ppcasm.py`](../research/tools/matching-decomp/ppcasm.py) | minimal PPC assembler — **stand-in backend only** |
| [`match.py`](../research/tools/matching-decomp/match.py) | loop entry point: function + candidate C → verdict; `--detect`; `--context` |
| [`selftest.py`](../research/tools/matching-decomp/selftest.py) | seven checks, two negative controls, one relocation-symbol control |
| [`leaf_census.py`](../research/tools/matching-decomp/leaf_census.py) | size / shape / difficulty over 12,062 entry points |
| [`throughput.py`](../research/tools/matching-decomp/throughput.py) | §4's arithmetic, reproducibly |

The comparison rule has one subtlety a naive byte compare gets wrong. A freshly compiled
object has **zero** in every branch and address operand, because the linker has not run; each
such field carries a relocation. Comparing those bytes raw reports a difference that is not
one. So each relocated operand field is masked **on both sides** and the relocation's
*symbol* is compared instead. Everything not covered by a relocation must be byte-identical —
no tolerance, no threshold, no "close enough".

### 3.3 The selftest

```
$ python research/tools/matching-decomp/selftest.py
== T1  identity: retail vs retail ==
  [ok] verdict MATCH   [ok] exact bytes   [ok] 100%
== T2  stand-in backend: assemble a candidate, compare ==
  [ok] verdict MATCH   [ok] bytes equal retail 8803057b7c0023789803057b4e800020
== T3  negative control: one word changed ==
  [ok] MISMATCH  [ok] names instruction 1 @ 0x800660bc  [ok] 3 of 4 still match
       first_diff: retail  or r0, r0, r4  /  candidate  or r1, r0, r4
== T4  semantically equivalent, differently encoded ==
  [ok] MISMATCH (retail 4 insns vs candidate 5)
== T5  truncated candidate ==        [ok] MISMATCH, size flagged
== T6  relocated object: the shape mwcceppc actually emits ==
  [ok] reloc is REL24 @ +0x00c   [ok] reloc names callee zz_0012308_
  [ok] verdict MATCH (bl masked by reloc)
  [ok] not exact bytes -- the bl word genuinely differs; the relocation is why that is ok
  [ok] T6b wrong callee symbol -> MISMATCH
== T7  unmasked bl would be a false mismatch (why T6 matters) ==
  [ok] without relocs -> MISMATCH at the bl 0x800122d4

HARNESS SELFTEST PASSED
```

*(The final line of that output originally read "The compiler stage (mwcceppc) is NOT
exercised and NOT present." It now points at `src-match/verify.py --control`, which does
drive a compiler — §3.1. The seven checks themselves are unchanged and still pass.)*

**T2 proves less than it looks like, and the distinction is load-bearing.** It assembles the
same instructions the retail function contains and observes that they are equal — the same
information written twice. Its only claim is that the extractor, encoder and comparator
agree. **It is not evidence that the function is matchable from C**, which is precisely what
cannot be tested here.

**T4 carries the argument.** It rewrites `zz_00660b8_` in a form that is behaviourally
identical — same loads, same OR, same store, same observable effect — and the oracle rejects
it. This project's existing behavioural standards (transcript, callstream) would pass it.
That rejection is the entire value of matching decompilation and, in the same breath, its
entire cost: every extra iteration in §4 is spent closing exactly that gap.

**T6 proves the harness is ready for a real compiler.** It builds a synthetic ELF32
big-endian object with the `bl` unlinked (`0x48000001`) and an `R_PPC_REL24` naming the
callee — the shape `mwcceppc` emits — and the oracle returns MATCH with `exact_bytes` correctly
`false`. T6b flips the relocation's symbol and gets MISMATCH. T7 removes the relocation and
shows the same object would be a **false** MISMATCH without masking.

### 3.4 The targets that were prepared

Three real functions, extracted and given candidate C in
[`research/tools/matching-decomp/scratch/`](../research/tools/matching-decomp/scratch/).
**All three candidates are UNVERIFIED — none has been through a compiler.** They show what
the loop submits and what a first iteration looks like; they are not results.

> **Resolved 2026-09-03 (§3.1).** Two of the three have been through a compiler.
>
> * **`zz_00122c8_` — MATCHED**, first candidate, `exact_bytes` correctly false with the
>   `R_PPC_REL24` naming `zz_0012308_`. Committed at
>   [`src-match/game/zz_00122c8_.c`](../src-match/game/zz_00122c8_.c). T6 predicted this
>   behaviour exactly.
> * **`zz_008bbc0_` — BLOCKED**, and it is the paragraph below that explains why it was a
>   bad first pick. `and r3, r4, r0` against a constant built with `lis`+`addi` is the one
>   arithmetic form mwcc-rs refuses (§3.1.3). The C for it was written in one line and is
>   almost certainly right; the compiler cannot lower it.
> * `zz_00660b8_` was not attempted — T3 and T4 use it as a control and it is more useful
>   left in that role.

**`zz_008bbc0_` @ `0x8008bbc0`** — 4 instructions, leaf, pure arithmetic:

```
8008bbc0  3c6000ff  lis  r3, 0xff
8008bbc4  38031f7f  addi r0, r3, 0x1f7f      ; r0 = 0x00FF1F7F
8008bbc8  7c830038  and  r3, r4, r0          ; return arg2 & 0x00FF1F7F
8008bbcc  4e800020  blr
```

r3 is written but never read, so the incoming r3 is dead — under the EABI that is what a C++
member function looks like when it ignores `this`, and this game is C++ (the map carries
`cCameraManager::HasCamera`, `SidelineExplodableManager::GetNumExplodables`). The constant is
built with `lis`+`addi`: the §2.1 idiom in the wild.

**`zz_00660b8_` @ `0x800660b8`** — 4 instructions, no frame, a byte flag setter; the target
T3 and T4 use.

**`zz_00122c8_` @ `0x800122c8`** — 8 instructions, the canonical MWCC non-leaf frame with a
single `bl`; the target T6 uses, because it exercises relocations.

---

## 4. The LLM loop, and what it would cost

### 4.1 Shape of the loop

The oracle's properties determine the design, and they are unusually good: **free** (no
capture, no spec, no human), **exact** (byte equality, not a threshold), **fast** (compile
well under a second, diff microseconds), **graded** (a match percentage *and a localised
first difference*, not just a boolean), and **permanent** (a matched function is matched
forever).

```
for target in ranked_by_difficulty(census):
    ctx = match.py --context target       # retail disasm, call targets with symbols,
                                          # SDA refs resolved through r2/r13 from the
                                          # ROM's own __init_registers, link neighbours
    cand = model(prompt(ctx))             # -> C source, nothing else
    for attempt in range(budget[tier]):
        v = match.py --function target --src cand --json
        if v.verdict == "MATCH": record(target, cand, version, flags); break
        cand = model(prompt(ctx, cand, v.diff_text, v.first_diff))
```

`match.py --context` already produces the context block with no compiler present:

```
FUNCTION zz_00122c8_ @ 0x800122c8, 32 bytes, 8 instructions
RETAIL DISASSEMBLY (authoritative; Gekko-correct):
  800122c8  9421fff0  stwu r1, -0x10(r1)
  ...
CALL TARGETS (each becomes an R_PPC_REL24 relocation):
  0x800122d4  bl -> 0x80012308  zz_0012308_
NEIGHBOURS IN LINK ORDER (same translation unit, probably):
    0x8001209c def_80012000    384 B
  * 0x800122c8 zz_00122c8_      32 B
    0x800122e8 zz_00122e8_      32 B
```

The checker returns JSON carrying `verdict`, `match_pct`, `first_diff` (address, both
encodings, both mnemonics), the full `diffs` list, the relocations, and `diff_text` — a
side-by-side rendering that goes straight into the next prompt. Exit codes: `0` MATCH,
`1` MISMATCH, `2` build failed (with compiler log), `3` no compiler.

Five design points, four of them borrowed from projects that have actually done this:

- **Feed back the first difference, not the whole diff.** Matching is usually one wrong
  token — an operand order, a cast width, a `<` that should be `<=`. `first_diff` names it.
- **Never let the model see Ghidra's C.** The `FUN_800c4468` finding in the static-recomp
  spike — Ghidra typed a one-pointer-argument function with sixteen parameters, and the
  staged port inherited it into `chunk_0020.c` — is the contamination to avoid. The context
  block is built from encodings and the map, not from a decompiler.
- **Gate on the whole build, not just the target symbol.** The Star Fox Adventures runbook
  makes this explicit and warns specifically against per-translation-unit compiler flag
  overrides, which manufacture a match that the real build cannot reproduce.
- **Schedule by similarity to already-matched functions.** Reported as "highly effective" on
  Snowboard Kids: order the queue by embedding or edit distance to solved neighbours, so the
  model's context carries a worked example of the same idiom.
- **Keep a persistent compiler-quirk memo.** Snowboard Kids used a `DECOMPILATION_LEARNINGS.md`
  accumulating MWCC idioms across the whole project. This is the artifact that makes
  iteration counts fall over time, and it is cheap.

### 4.2 On this GPU: the arithmetic does not close

Tool: [`throughput.py`](../research/tools/matching-decomp/throughput.py). Artifact:
[`research/decomp/data/matching-decomp-throughput.json`](../research/decomp/data/matching-decomp-throughput.json).

The one measured input is the decode rate. From
[`docs/audits/port-pipeline-integrity.md:655`](audits/port-pipeline-integrity.md):
**"The 27B model on the 1080 Ti runs ~2.5 tok/s"** — the same number that audit uses to
explain why raising `COMPILE_FIX_MAX_TOKENS` from 4096 to 6144 would push a worst-case
generation toward 40 minutes. Assumptions (prefill 40 tok/s; prompt ≈ 400 + 14 tokens per
instruction; reply ≈ 120 + 3 per instruction; 0.4 s compile+diff; per-tier iteration budgets
and success rates) are labelled in the tool's docstring. The iteration budgets are the most
uncertain numbers in this spike. SDK/TRK functions are excluded — §5.3 argues they should be
obtained, not derived.

| tier | fns | insns | iters | P(ok) | s/iter | GPU-hours | matched |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| trivial | 656 | 4,010 | 3 | 0.90 | 67.9 | 37 | 590 |
| easy | 4,313 | 86,985 | 8 | 0.70 | 89.7 | 859 | 3,019 |
| moderate | 2,762 | 143,269 | 25 | 0.40 | 138.8 | 2,662 | 1,105 |
| hard | 2,317 | 201,763 | 60 | 0.15 | 193.4 | 7,467 | 348 |
| research | 949 | 196,465 | 120 | 0.03 | 379.3 | 11,998 | 28 |
| **TOTAL** | **10,997** | **632,492** | | | | **23,024** | **5,090** |

> **23,024 GPU-hours = 959 GPU-days = 2.6 GPU-YEARS of continuous compute**, for
> **5,090 of 10,997 functions (46.3 % by count)** — which is **25.0 % of the game by code
> volume**, the way decomp projects actually report progress.

A faster card does not rescue it:

| decode rate | GPU-hours | GPU-years |
| ---: | ---: | ---: |
| 2.5 tok/s (measured, 1080 Ti) | 23,024 | 2.6 |
| 10 tok/s | 9,447 | 1.1 |
| 40 tok/s | 6,053 | 0.7 |
| 200 tok/s (80× measured) | 5,148 | 0.6 |

An 80× faster card buys 4.5×, because past ~40 tok/s the loop is **iteration- and
prefill-bound**, not decode-bound. And the sensitivity runs the other way too: set every
tier's success rate to 1.0 and the cost is still 23,024 GPU-hours, because a failure and a
success burn the same iterations — only the *yield* moves, not the *time*.

**So the binding constraint is the iteration count, which is a statement about model
capability, not about hardware.** A 27B at `iq3_s` reasoning about MWCC codegen idioms is
the weak link. That is the assumption to attack, and §4.3 shows someone already has.

### 4.3 What the same loop achieves on a frontier model

The published 2026 results are not marginal improvements on the table above; they are two to
three orders of magnitude away, on the same task and the same class of binary.

| Project | Binary | Result | Duration | Driver |
| --- | --- | --- | --- | --- |
| **Star Fox Adventures** | GameCube, 2.87 MB code, 9,498 fns | **88.78 % code / 97.96 % functions matched** | repo created 2026-02-10, ~7 months, 8 contributors | `codex exec` agent loop on Windows, objdiff ground truth |
| **Snowboard Kids** | N64, 2,145 fns | **100 % matched** | **84 days** | agent loop, GPT-5.x / Claude; `m2c` alone matched 0.93 % |
| Snowboard Kids 2 | N64 | ~25 % → ~75 % | — | same; large functions the reported wall |
| Klonoa: Empire of Dreams | GBA | 51 % of bytes, 663 fns | — | Claude Code + objdiff |
| Controlled study, 60 fns | GBA + N64 | **74 % mean match, 80 % best run** | — | Sonnet in a sandboxed compile-verify loop |

Applying those calendar rates to this game's 10,997 non-SDK functions:

```
Star Fox Adventures  44.3 fns/day (8 parallel loops) -> 248 days ( 8.2 months)
Snowboard Kids       25.5 fns/day (1 loop)           -> 431 days (14.2 months)
```

**Star Fox Adventures is a near-perfect size match for this game**: 2.87 MB of code against
Gotcha Force's 2.81 MB of `.init` + `.text`, 9,498 functions against 10,997 non-SDK entry
points here. It is the single most informative data point in this spike.

Two honest caveats. Those are *calendar* rates for whole projects and include human review
time — SFA had eight contributors, and roughly 4.8 % of Snowboard Kids' commits needed
expert human help. And the 8-parallel-loops figure is doing a lot of work: at one loop the
same rate implies years, so parallelism is not optional.

**The conclusion is narrow and firm: the method works, the local model is what does not.**

### 4.4 The long tail is real and is not fixed by throughput

The most useful negative result in the published record: on Snowboard Kids 2, the model
*"struggles with large functions and more or less gives up immediately on those exceeding
1,000 instructions."* This project's census has **45 functions of 513+ instructions** and a
**949-function "research" tier**. Those will not fall to any loop, and §5.2 explains why
that costs more than the count suggests.

---

## 5. Honest scope

### 5.1 The shape of the corpus

Tool: [`leaf_census.py`](../research/tools/matching-decomp/leaf_census.py). Artifact:
[`research/decomp/data/matching-decomp-census.json`](../research/decomp/data/matching-decomp-census.json).
12,062 entry points (10,954 registry `functions` + 1,018 `excluded`, unioned with the map's
5,897 `.text` symbols), 701,464 instructions, mean 58.2 per function.

| insns | functions | share | cumulative |
| --- | ---: | ---: | ---: |
| 1–8 | 1,172 | 9.7 % | 9.7 % |
| 9–16 | 1,896 | 15.7 % | 25.4 % |
| 17–32 | 2,543 | 21.1 % | 46.5 % |
| 33–64 | 2,982 | 24.7 % | 71.2 % |
| 65–128 | 2,341 | 19.4 % | 90.6 % |
| 129–256 | 889 | 7.4 % | 98.0 % |
| 257–512 | 194 | 1.6 % | 99.6 % |
| 513+ | 45 | 0.4 % | 100.0 % |

Shape: **14.9 %** leaves; **86.4 %** build a stack frame; **38.4 %** touch floating point;
**5.1 %** use Gekko paired-singles; **15.5 %** contain a loop; **1.1 %** contain a computed
jump (`bctr`); **44.0 %** reference the small data areas.

### 5.2 The trap in "percent of functions"

Restricting to the 10,997 non-SDK functions:

| | functions | % of functions | instructions | **% of code** |
| --- | ---: | ---: | ---: | ---: |
| ≤ 8 insns | 1,020 | 9.3 % | 5,597 | **0.9 %** |
| ≤ 16 insns | 2,757 | 25.1 % | 28,003 | **4.4 %** |
| ≤ 32 insns | 5,047 | 45.9 % | 81,884 | **12.9 %** |
| ≤ 64 insns | 7,802 | 70.9 % | 212,019 | **33.5 %** |
| ≤ 128 insns | 10,012 | 91.0 % | 404,641 | **64.0 %** |

**Half the functions are a tenth of the game.** A loop that only ever solves short functions
can report "46 % matched" having touched 13 % of the code — and the untouched 87 % contains
the combat state machines, the AI, and everything the port needs. Any progress metric this
project adopts for matching decomp must be **instruction- or byte-weighted**, or it will be
a lie by construction. This is also why the published table in §5.4 reports *code* percent
and *function* percent separately, and why the two diverge by 10–25 points on every project.

### 5.3 9.8 % of the DOL is already someone else's solved problem

| Group | Functions | Instructions | Share of `.text` |
| --- | ---: | ---: | ---: |
| Dolphin SDK (`gnt4-` prefixed in the map) | 996 | 63,213 | 9.0 % |
| MetroTRK (`TRK_*`, `__TRK*`) | 69 | 5,759 | 0.8 % |
| **Total** | **1,065** | **68,972** | **9.8 %** |

The SDK names decompose exactly as Dolphin SDK libraries do — 153 `GX*`, 96 `OS*`, 45 `DVD*`,
14 `SI*`, 12 `PPC*`, 11 `VI*`, 10 `EXI*`, 10 `PAD*`, plus `AR`/`ARQ`/`DC`/`IC`/`LC`/`DB`/`MEM`
— and the map carries 128 fully demangled names including `CARDGetXferredBytes`,
`OSGetLanguage`, `VIGetDTVStatus`, `PADClampCircle`, `AIInitDMA`, `ARAlloc`, `__va_arg`.

**These should be obtained, not derived.** `doldecomp/dolsdk2004` is an open decompilation of
the 2004 Dolphin SDK reporting ~100 % for most libraries; GNT4's build tree covers the same
`os gx card dsp ar ai pad vi dvd si exi mtx db musyx TRK_MINNOW_DOLPHIN PPCEABI/MSL_C
PPCEABI/Runtime` surface. The SDK objects are compiled with **GC/1.2.5n** (§2.4), which is
notably the one build `mwcc-rs` does *not* yet cover — so the SDK half may still need a real
`mwcceppc`, or may be satisfiable from sources alone without re-matching.

#### 5.3.1 Provenance, checked — and the recommendation above is wrong

**`doldecomp/dolsdk2004` has no licence at all.** No `LICENSE` file, and the GitHub
licence API returns `null`. Under default copyright that is all-rights-reserved, on top
of it being a decompilation of Nintendo's proprietary SDK. **It must not be vendored,
and this document should not have recommended it without checking.** Checked
2026-09-03; the repository is otherwise as described (created 2024-04-21, 17 stars,
most libraries at 100 %).

**There is a licensed alternative carrying the same content.**

| Repository | Licence | Carries the Dolphin SDK? |
| --- | --- | --- |
| `doldecomp/dolsdk2004` | **none** | yes — but unusable |
| **`zeldaret/tp`** (Twilight Princess) | **CC0-1.0**, root, no carve-out | **yes** — `libs/dolphin/src/{os,gx,card,dvd,si,exi,pad,vi,ar,ai,mtx,db,dsp,…}`, 37 library directories, plus `libs/TRK_MINNOW_DOLPHIN` and `libs/PowerPC_EABI_Support` |
| `doldecomp/ogws` (Wii Sports) | CC0-1.0 | Revolution-era equivalent |

**One honest caveat that no licence can remove:** CC0 dedicates the *contributors'* own
rights. It cannot dedicate rights they never held, and the underlying work is
reconstructed Nintendo SDK source. That is true of every public GameCube decomp, and it
is a matter for the owner, not an agent. What CC0 *does* give is an explicit, auditable,
uniform grant from the people who wrote the files — which is exactly what
`doldecomp/dolsdk2004` does not have.

#### 5.3.2 The free path, tested — and the blocker is the compiler, not the source

One SDK function was taken through the loop end to end: **`GXInitLightColor`**
@ `0x802285f4`, whose CC0 source is in `zeldaret/tp` at
`libs/dolphin/src/gx/GXLight.c`. Retail is three instructions:

```
802285f4  lwz r0, 0(r4)
802285f8  stw r0, 0xc(r3)
802285fc  blr
```

The genuine source body —

```c
obj = (__GXLightObjInt_struct*)lt_obj;
*(u32*)&obj->Color = *(u32*)&color;
```

— **does not compile under mwcc-rs.** Two separate refusals: `*(u32*)&obj->Color` gives
*"pointer leaf access needs a pointer variable (roadmap)"*, and removing that cast
exposes a second problem, where taking `&color` on a by-reference struct parameter makes
mwcc-rs spill the incoming pointer to a stack home and reload it, which real MWCC does
not do. A rewrite that reaches the same three instructions through the implemented subset
**does** match, and is committed at
[`src-match/sdk/GXInitLightColor.c`](../src-match/sdk/GXInitLightColor.c) with that
distinction stated in its header.

**So the 9.8 % is confirmed as real source that exists under a clear grant, and
confirmed as not yet buildable here.** The private struct layouts, offsets and field
types in those sources are the part gap **H8** actually needs — the shim-signature
failure class ends by *having* them, and that does not depend on compiling anything.
Taking the sources is still the highest-value item in this document. Matching them is
blocked behind the same compiler that blocks §3.1.3, plus the GC/1.2.5n problem.

The leverage is larger than 9.8 % because **these are exactly the functions the current
pipeline cannot handle.** Gap **H8** records "no SDK shim ledger; 6 seeded, 17 declared, 6
conflicting including a real f64/i64 split on `gnt4_PSMTXConcat_bl`", and the integrity audit
records the compile-fix loop *mutating* seed declarations because "the header guard rejects
`gnt4_` definitions but not declaration edits". Getting `gnt4_PSMTXConcat_bl`'s return type
wrong silently miscompiles every caller. Real SDK sources end that entire failure class — not
by matching anything, just by *having* them.

### 5.4 Against the published record

Figures from the public decomp progress dashboard, retrieved 2026-09-03. `matched` =
byte-exact against the target; `complete` = fully linked translation units.

| Project | Code | Matched code | Matched fns | Complete | Started | Contributors |
| --- | ---: | ---: | ---: | ---: | --- | ---: |
| Twilight Princess | 11.49 MB | **100.00 %** | 48,107 / 48,107 | 87.13 % | 2020-08 | 65 |
| Melee | 3.88 MB | 95.43 % | 19,762 / 19,829 | 86.80 % | 2020-06 | 113 |
| Pikmin 2 | 4.65 MB | 88.00 % | 24,391 / 24,957 | 57.87 % | 2021-09 | 30 |
| **Star Fox Adventures** | **2.87 MB** | **88.78 %** | **9,304 / 9,498** | 63.92 % | **2026-02** | **8** |
| Wind Waker | 7.81 MB | 75.22 % | 31,777 / 39,324 | 62.08 % | 2023-09 | 61 |
| Mario Kart: Double Dash!! | 3.22 MB | 46.94 % | — | 41.77 % | — | — |
| Super Mario Sunshine | 3.59 MB | 38.62 % | 8,176 / 12,881 | 17.28 % | 2021-05 | 20 |
| Metroid Prime | 4.01 MB | 37.61 % | 10,237 / 16,685 | 19.43 % | 2022-03 | 10 |
| GNT4 | — | *not tracked* | — | — | 2020-08 | 6, dormant since 2022 |
| **Gotcha Force** | **2.81 MB** | — | 0 / ~10,997 | — | — | — |

**Read the Star Fox Adventures row against the others.** Same technique, same platform,
essentially the same binary size as Gotcha Force — and it reached 88.78 % in about seven
months with eight contributors, where Sunshine took five years to reach 38.62 % with twenty
and Metroid Prime four years to reach 37.61 % with ten. The difference is the LLM loop. That
single row is why this spike's verdict is not the "years, not months, and not finishable"
that the human-only record would have supported.

Two cautions against over-reading it. It is one project, self-reported, seven months old, and
its remaining 11 % is the expensive part on every project in that table — note that even
Twilight Princess at 100 % matched is only 87 % *complete*. And GNT4, the closest analogue by
symbol lineage, went dormant in 2022 at six contributors with no published percentage: the
failure mode for a small team is real and has a name here.

---

## 6. Verdict

### 6.1 Matching decompilation is the right route — and the local model is the wrong driver

**On the route: YES.** It is the only technique that produces what the owner asked for.
Static recompilation, the sibling spike's recommendation, is by construction a *mechanical
transliteration* — the thing the brief explicitly excluded. Matching decompilation produces
ordinary C, and the "1:1" is not argued from a behavioural capture, it is proved by byte
equality against the retail image. That C then compiles for **any** target, wasm included, so
it serves the "compilable, playable" half of the goal as well as the "1:1" half. The oracle
is genuinely free, exact, automatic and graded, exactly as the brief supposed, and §3 proves
that oracle works to seven checks including two negative controls.

**On the local model: NO, and the number is not close.** 23,024 GPU-hours — 2.6 GPU-years —
for 25 % of the code, on a GPU that is currently leased away, with the *iteration count*
rather than the hardware as the binding constraint. Every published success ran hosted
frontier models in agent loops. **This is the answer to the brief's actual question, and it
is the one thing in this spike I would not soften:** pointing the 27B on the 1080 Ti at this
loop would consume the machine for years and produce a quarter of a game.

**The gap between those two answers is the plan.** The same agent pipeline this project
already has — worktrees, subagents, an orchestrator — is the shape that Star Fox Adventures
used to reach 88.78 % in seven months. It ran `codex exec` loops on Windows with objdiff as
ground truth. What has to change is which model sits inside the loop, not the loop.

### 6.2 The order of operations

> **Step 1 was executed on 2026-09-03 and its result rewrites steps 1 and 2. Read
> §6.2.1 below before acting on the list.**

1. **Settle the compiler.** Try `mwcc-rs` first — it is open source, it claims GC/1.3 through
   GC/2.7 byte-exact, and GC/2.7 is this game's most likely build (§2.3). Verify that claim
   here with Calibration A, then run **Calibration B** (§2.4) to pin the game's version and
   flags. Until B passes, everything downstream is void. This costs a day and needs no model.
2. **Take the SDK rather than matching it.** `doldecomp/dolsdk2004` plus GNT4's tree covers
   the 1,065 functions in §5.3 — 9.8 % of the DOL, and the exact functions that gap **H8**
   and the shim-signature failure class are stuck on. This is the highest-value single item
   in this document and it is nearly free.
3. **Add `dtk` and `objdiff-cli`.** Both are Rust with Windows binaries. `dtk` splits the DOL
   into relocatable objects, which is what turns per-function matching into per-translation
   -unit matching; there is no substitute. Keep `objdiff.py` as the reference implementation
   and the selftest.
4. **Measure the iteration count before committing.** Take twenty *moderate*-tier functions
   and record how many iterations a real model needs. §4.2's whole result hinges on ~25; the
   published projects imply far fewer. **This experiment costs a day and settles the question
   this spike could only bound.** Do it before scaling anything.
5. **Then run the loop, in parallel worktrees, on a frontier model**, scheduled by similarity
   to solved neighbours, gated on the whole build rather than the target symbol, accumulating
   a persistent compiler-quirk memo. Report progress **by instructions, never by function
   count** (§5.2).

### 6.2.1 Revised after running step 1

**Step 1 is done, and it did not settle the compiler.** A compiler exists and works
(§3.1); Calibration A cannot be run at all and Calibration B returned only "not GC/1.3"
(§3.1.2). The list above assumed a pass/fail on version; the real answer is that the
*version question is partly unanswerable from `.text`* — 2.5, 2.6 and 2.7 are
indistinguishable in principle — and partly blocked behind compiler capability.

**Do not treat "until B passes, everything downstream is void" as a stop.** It was
written expecting B to resolve. Rewritten: the flags and the 2.4.7-family label are the
working assumption, GC/1.3 is excluded, and any function matched under a label that
turns out wrong will be re-verified by `src-match/verify.py` when a better compiler
arrives. That is what the registry and the verifier are for.

**Step 2 changes source.** Take the SDK from **`zeldaret/tp` (CC0-1.0)**, not
`doldecomp/dolsdk2004`, which has **no licence at all** (§5.3.1). The value is in the
headers, struct layouts and signatures — gap **H8** — and that value does not require
compiling anything, so it is available today (§5.3.2).

**The new step 0, and it is cheap.** mwcc-rs is MIT/Apache and *modifiable* — that is
the stated reason it exists. Two of the five blockers in §3.1.3 look like small,
well-isolated additions to its general generator: `AND` against a non-mask 32-bit
constant (`lis`+`addi`+`and` — the sibling `OR`/`XOR`/`ADD` paths already work), and the
load-with-update forms. Each unblocks a recurring shape across the census. **Contributing
those upstream is a better use of a day than anything else on this list**, and it is the
one lever this project has that no amount of model capacity provides. The register
allocator (`zz_0298b20_`) is not in that class — mwcc-rs's own README calls matching
MWCC's colouring the core research target, and it should be treated as out of scope.

**Steps 3, 4 and 5 are unchanged, and step 4 is now the binding one.** §3.1's 1.08
iterations/function measures two-to-eight-instruction accessors, which is not the regime
§4.2's arithmetic depends on. Twenty *moderate*-tier functions still have to be measured
— and until mwcc-rs can compile that class, they cannot be.

### 6.3 What this does not change

Matching decompilation delivers source, not a running browser game. The GX host, the DVD
host, the MusyX mixer and framebuffer equivalence are unchanged and unhelped by any of the
above — they are the same work on every route, and the static-recomp spike's §5.3 already
scopes them. Matching decomp replaces the *front* of the pipeline (what produces the C), not
the *back* (what makes it run). It does, however, replace it with something that has an
oracle: against the current route's 6.0 % auto-speccable functions, 40.7 % vacuous
`oracle_green`, and zero units promoted by the last sweep, a compile-and-diff that answers in
under a second for every function in the binary is not an incremental improvement.

**One immediate use, available the moment a compiler exists and independent of everything
else:** compile the *existing* Ghidra-C corpus with MWCC and record `match_pct` per function.
Almost none will match — Ghidra's C is not the original source — but the distribution is a
graded, exact, automatic correctness signal over all 10,954 functions at under a second each.
A lift that compiles to 85 % matching instructions is probably right; one at 20 % is probably
wrong. That is a better triage signal than anything the pipeline has today, and it is a
by-product of infrastructure that would be built anyway.

---

## 7. Reproduction

```bash
cd D:/GotYaForce/.claude/worktrees/agent-a3f974e3aa4d99836

# §2 compiler fingerprint and SDK banners
python research/tools/matching-decomp/fingerprint.py \
    --iso "D:/GotYaForce/Gotcha Force.iso" \
    --json research/decomp/data/matching-decomp-fingerprint.json
python research/tools/matching-decomp/banners.py --iso "D:/GotYaForce/Gotcha Force.iso"

# §1 toolchain state
python research/tools/matching-decomp/match.py --detect          # exits 3

# §3 the harness, and its negative controls
python research/tools/matching-decomp/selftest.py                # exits 0

# §5 corpus shape
python research/tools/matching-decomp/leaf_census.py \
    --json research/decomp/data/matching-decomp-census.json

# §4 throughput arithmetic, local and published
python research/tools/matching-decomp/throughput.py \
    --json research/decomp/data/matching-decomp-throughput.json

# the loop's prompt block, which works without a compiler
python research/tools/matching-decomp/match.py --function zz_00122c8_
```

Requires Anaconda Python 3.7.3 with capstone 5.0.1 (`C:\ProgramData\Anaconda3\python.exe`),
which is what is on this machine. The retail GCM is read, never written.

### 7.1 Reproducing §3.1 — the test that actually matched functions

Install the toolchain per
[`research/tools/matching-decomp/TOOLCHAIN.md`](../research/tools/matching-decomp/TOOLCHAIN.md)
§1 (Rust + mwcc-rs at commit `7c093483`, ~9 minutes to build), then:

```bash
cd D:/GotYaForce/.claude/worktrees/agent-a2e26395b5343691b

# the compiler is now found
python research/tools/matching-decomp/match.py --detect          # exits 0

# the whole matched corpus + the negative controls          -> 16 ok, 0 failed
python src-match/verify.py --control

# Calibration B across every entry: which builds each one discriminates
python src-match/verify.py --sweep

# one function, the shape an LLM iteration consumes
python research/tools/matching-decomp/match.py \
    --function zz_0206f8c_ --src src-match/game/zz_0206f8c_.c \
    --obj-symbol f --build 2.7 --json v.json

# the harness's own selftest still passes, unchanged
python research/tools/matching-decomp/selftest.py                # exits 0
```

Nothing above touches the GPU, the model server, the driver, the supervisor, or any
pipeline state. The compiler runs on CPU in well under a second per function.

## 8. Uncertainties, stated

> **Items 1–3 were rewritten 2026-09-03 after the test ran. The originals are quoted
> under each.**

1. ~~**No function was matched.**~~ **Thirteen are** (§3.1) — 43 instructions, 0.0061 %
   of the code. The remaining uncertainty moved rather than closed: these are
   *mwcc-rs*-exact, not *MWCC*-exact, and **there is no way to check the difference on
   this machine.** Where mwcc-rs diverges from the genuine compiler, a match here is
   wrong and nothing would say so.
   > *was: "There is no compiler on this machine; §3.1. Every claim about matchability
   > here is inference from other projects, not measurement on this binary."*
2. **The compiler version is still a prior.** Calibration B ran and returned only
   "not GC/1.3" (§3.1.2). GC/2.5, 2.6 and 2.7 are **indistinguishable in principle**
   from a linked image, so this uncertainty is partly permanent rather than pending.
   > *was: "GC/2.7 leads because GNT4 … uses it. Calibration B settles it."*
3. **`mwcc-rs`'s byte-exactness is 83 % memorisation by line count** (§3.1.4), and none
   of those 558 captures covers a Gotcha Force function. GC/1.2.5n is now present as an
   incomplete experimental profile, so Calibration A remains impossible.
   > *was: "the project's own claim, unverified here, and it does not cover GC/1.2.5n."*
4. **How far the general generator gets on real game code is unmeasured.** Thirteen
   matches were found by picking targets from the census's most common short shapes.
   **The selection was deliberately favourable** and says nothing about the 90 % of the
   binary above 16 instructions. §3.1.3's five blockers were hit within twenty attempts,
   which is the more informative number.
5. **The iteration count that §4.2 depends on is still not measured.** 1.08 (§3.1) is for
   two-to-eight-instruction accessors, not the 33–128-instruction *moderate* tier.
4. **§4.2's iteration budgets are guesses** and are the most load-bearing uncertain numbers in
   this document. §6.2 step 4 is how to replace them with measurements.
5. **Whether `mwcceppc.exe` enforces a licence at runtime could not be confirmed.** Evidence
   is circumstantial in both directions.
6. **The Star Fox Adventures figures are self-reported** and the project is seven months old.
   It is one data point, and the one this verdict leans on hardest.
