# The audio and DVD HLE host — the browser standing in for the GameCube's DAC and disc drive

Status: **UNVERIFIED, and for audio, STRUCTURALLY INCOMPLETE.** The seam is proven for
both halves; nothing on either has been compared against console behaviour; and the audio
half is missing not an adapter but a processor — see §3, which is the most important
section in this document.
Date: 2026-08-31. Design authority: `docs/playable-port-design.md` (V2 F2 "Stage D — SDK
seam", V3 non-fatal note 1's claim bar, V4 H2's bridge, V5 I1's adapter contract, R3's
interrupt delivery). Companion document: `docs/gx-hle-host.md`, whose structure, claim
vocabulary and honesty discipline this one deliberately copies.

---

## 0. What this is, in one paragraph

`docs/playable-port-design.md` names the browser as the HLE host behind the SDK seam: the
composed ROM module executes the game's own code, and everything the GameCube SDK used to
do — graphics, audio, OS, DVD — is provided by the host. `docs/gx-hle-host.md` covers
graphics. This document covers **audio** and **DVD/file access**. It describes two new
`packages/rom-runtime` adapter sets — `src/audio/` and `src/dvd/` — that receive the ROM
module's calls through the existing H2 Atomics bridge, plus an **MMIO seam** for audio
that has no equivalent on the DVD side. The DVD half reads a GameCube FST and delivers
real bytes into GC memory. The audio half models the AI and DSP registers the ROM's own
code drives, reconstructs the DAC's DMA transfers, and plays them through WebAudio — and
does **not mix**, because the mixer is not translatable code (§3).

**This is NOT a replacement for `packages/audio`.** That package plays the real OGGs
extracted from the disc (ADX via ffmpeg, combat SE via `scripts/export-combat-se.py`) and
is the TS recreation's own sound path. This is the path the **composed ROM module** takes
when *its* code drives the DAC. The two coexist for the whole hybrid period (design E2's
dual-path rule). Nothing in `packages/audio`, `apps/game`'s SFX/BGM wiring, or
`packages/combat` was touched.

---

## 1. The claim bar, stated before any numbers

Four claims, in descending order of how much they are worth.

1. **What is proven.** ROM code — including seven verbatim decompiled ROM bodies — crosses
   the real bridge into these adapters; a path resolves against a real GameCube FST and
   the right bytes land in GC memory; an async read's completion callback returns to the
   module as an invoke-request at a worker park point; the ROM's own `AIInitDMA` /
   `AIStartDMA` move DSP-ADPCM-decoded PCM out of the arena into a WebAudio buffer whose
   samples are the decoder's samples. Proof: §6.
2. **What the audio half structurally cannot do.** Gotcha Force mixes audio in **MusyX
   microcode executing on the GameCube DSP**. That microcode is not PowerPC code, is not
   in the DOL's text, and is uploaded to the DSP over a mailbox as a binary blob. There is
   nothing here to translate. This host can carry a PCM buffer to the speakers; it cannot
   fill one. A composed module running today would DMA silence, and the host says so
   (`DSP_MICROCODE_ABSENT`). §3.
3. **What is not even attempted yet.** No read this path performs has been compared
   against a real drive, and no sample against console audio. There is no DVD trace, no
   audio capture, no oracle. Every adapter is a hand-written stand-in derived from the
   SDK's semantics and the ROM's decompiled bodies. The assertions in §6 were predicted
   from the same understanding that produced the implementation, so they are
   self-consistency checks and cannot detect a shared misunderstanding — the one exception
   is the DSP-ADPCM decoder, which is checked against an independent second implementation
   (§5.3).
4. **What the ceiling is, even after verification exists.** Same shape as GX's
   "framebuffer-equivalent, never pixel-identical": WebAudio resamples with its own kernel,
   schedules on a play cursor rather than a 5 ms DMA interrupt, and applies AIVR as a plain
   gain multiply rather than the DAC's attenuation curve. **Sample-equivalent, never
   sample-identical.** On the DVD side the ceiling is different and lower-risk — bytes are
   bytes — but the *timing* model is knowingly wrong and cannot be fixed by accuracy work
   alone (§4.4).

The code says the same thing in the same words. `AUDIO_NO_BEHAVIOURAL_CLAIM` and
`DVD_NO_BEHAVIOURAL_CLAIM` are printed by the self-test page, embedded in its
machine-readable payload, and asserted by the smoke phase — which fails if either host
ever stops declaring them, or if the audio host ever stops reporting
`dspMicrocodeAbsent: true`.

---

## 2. What this repository does NOT have, stated up front

Two absences shaped the whole design, and both were discovered by looking rather than
assumed:

* **There are no disc bytes.** `research/disc/` contains one `.gitkeep`. `.gitignore`
  excludes `*.iso`, `*.gcm`, `*.ciso` and `research/disc/*/`. There is no
  `afs_data.afs`, no `boot.dol`, no FST dump, no apploader, and no name→offset index
  anywhere in the tree. Every extractor in `scripts/` reads an untracked, owner-supplied
  `user-data/GG4E/…` tree that does not exist in a clean checkout. So the DVD host is
  backed by a **disc provider interface** with a real FST parser and an in-memory
  `SyntheticDisc`, and `scripts/build-disc-index.mjs` is the entry point for an owner who
  has the image. §4.1.
* **There is no TypeScript ADPCM decoder.** The brief for this work assumed one existed to
  reuse. The repo-wide search found exactly one decoder — `decode_dsp_adpcm` in
  `scripts/export-combat-se.py`, which is **Python and runs offline**; it is the tool that
  produced the combat-SE OGGs `apps/game` ships. There is no ADX decoder in TS either
  (`scripts/export-audio-assets.mjs` shells out to ffmpeg), and `packages/audio` decodes
  nothing at all — it constructs `HTMLAudioElement`s over pre-decoded OGGs. There is also
  no WebAudio anywhere in the repository before this work. So
  `packages/rom-runtime/src/audio/adpcm.ts` is a **new port**, and §5.3 records how it is
  checked rather than believed. This is the same discovery `docs/gx-hle-host.md` §4.5 had
  to record about texture decoding, and it is recorded here for the same reason: so the
  next agent does not go looking again.

---

## 3. The central finding: audio is not a call surface, and the mixer is not code we have

This is the audio twin of `docs/gx-hle-host.md` §3 ("the ROM does not submit vertices by
calling a function"), and it is more severe.

### 3.1 Only 15% of the audio surface crosses the SDK seam

`scripts/hle-call-inventory.mjs` classifies every measured entry point by **seam**, which
GX never needed because the whole GX API is `gnt4_*`-prefixed:

* **bridged** — the symbol is `gnt4_*`-prefixed, so design V2 F2 excludes it from porting
  and every call is an out-of-window call the host must service;
* **in-window** — the symbol is ordinary ROM code the port compiles into the module. A
  call to it does not cross the seam at all.

For audio the split is **6 bridged call sites out of 40**. `AIInit`, `AIInitDMA`,
`AIStartDMA`, `ARInit`, `ARAlloc`, `__AI_SRC_INIT` and the rest are all in-window: the port
compiles them, and they reach the hardware by storing to memory-mapped registers, which
the decompiler renders as `DAT_cc006c00 = …`. The measurement counts **18 registers, 403
static reads and 342 static writes**. The composed module's linear memory is `0x807A0000`
bytes, so a literal access at `0xCC006C00` is out of bounds and traps — exactly the
situation `0xCC008000` put the GX half in.

**A host that intercepts only audio FUNCTION CALLS therefore never sees a single sample.**

The consequence is the same as GX's: the audio seam needs an assembly-gate **lowering**.
`__gf_mmio_load_u16/u32` and `__gf_mmio_store_u16/u32` are the target, and
`registerMmioAdapters` binds them. Unlike GX, **the gate does not emit them yet**:
OGhidra's `src/port_wgpipe_lowering.py` covers the `0xCC008000` window and only that
window. Teaching it the AI and DSP windows is remainder item 1 (§8). Until then the
ROM-unit fixture applies the same class of rewrite through a hand-written header, and
says so in three places — the header, `build.sh`, and the host's own
`AI_MMIO_NOT_GATE_LOWERED` diagnostic.

### 3.2 The mixer is DSP microcode

The registers above are the DAC's DMA engine and the DSP's mailbox. The actual synthesis —
voices, pitch, panning, ADPCM playback, the whole mixer — runs on the GameCube's DSP. The
corpus shows the ROM doing it, unambiguously:

* `zz_0217dd8_` @`0x80217dd8` writes the command word **`0xBABE0180`** to the DSP mailbox
  (`zz_021c664_` @`0x8021c664` → `DAT_cc005000`/`DAT_cc005002`) and spins until the DSP
  consumes it. `0xBABE` is MusyX's mailbox magic;
* it then hands the DAC the buffer the DSP just filled:
  `AIInitDMA(&DAT_803db100 + n * 0xa0, 0x280)` — a double/triple-buffered ring at
  `0x803DB100`, 0x280 bytes per transfer;
* `0x280` bytes is 160 stereo 16-bit frames, which at the 32 kHz rate the ROM's own
  `AIInit` selects (`AISetDSPSampleRate(0)`) is **5 ms** — the MusyX frame period;
* `sndSeqContinue` @`0x801c7b68` survives as a MusyX API name in the symbol index.

That microcode is a binary blob, not PowerPC text. **It is not in scope for any porting
pipeline this project has**, because porting operates on decompiled PowerPC. Options for
closing the gap are all large, and they are §8's items 4–6.

Until one of them lands: this host models the mailbox as a **null DSP** that accepts every
command word and immediately reports it consumed. That choice is deliberate and is the
lesser of two evils — leaving the busy bit set would hang the module in the ROM's own spin
loop, which is worse than silence. The self-test asserts that the spin loop terminates
(§6, proof 4).

### 3.3 Two symbol names in the corpus are wrong, and the host does not trust them

While reading the AI bodies, four renames turned out to disagree with what the code does.
Two are outright wrong:

| ROM addr | corpus name | what the body actually does |
|---|---|---|
| `0x802149b0` | `AIGetStreamPlayState` | `return AIVR & 0xff` — this is **AIGetStreamVolLeft** |
| `0x802149c0` | `AISetStreamVolLeft` | writes `AIVR` bits 8-15 — this is **AISetStreamVolRight** |
| `0x802147ac` | `zz_02147ac_` | `return AICR & 1` — **this** is `AIGetStreamPlayState` |
| `0x80214994` | `zz_0214994_` | writes `AIVR` bits 0-7 — **this** is `AISetStreamVolLeft` |
| `0x802145f0` | `zz_02145f0_` | stores its argument into `DAT_8043662c`, the pointer the AI DMA interrupt handler calls — **this** is `AIRegisterDMACallback`, the entry point the whole audio path hangs off |

Nothing in the host keys off those names: adapters and register decode key off
**addresses** and off what the body does. The table is exported as
`AI_SYMBOL_NAME_CORRECTIONS` and emitted as a diagnostic on every report, so a reader who
greps for `AISetStreamVolLeft` finds the correction instead of trusting it.

---

## 4. The measured call surfaces

Method: `scripts/hle-call-inventory.mjs` walks `research/decomp/ghidra-export`, attributes
every call site to its enclosing function, and separates **game** call sites (caller is
ROM game code) from **SDK-internal** ones (caller is itself a `gnt4_*` function, so the
call never crosses the seam). It also counts, per hardware register in each family's MMIO
windows, how many static lines read it and how many write it.

Outputs: `research/decomp/data/{audio,dvd}-call-inventory.json` and the generated
`packages/rom-runtime/src/{audio,dvd}/inventory.generated.ts`, which the runtime imports so
that the coverage percentages below are *computed from the measurement* rather than
asserted.

**Honesty note on the ranking.** These are STATIC counts — how many places in the ROM do
the thing — not runtime frequency. A per-frame ranking needs a Dolphin trace and does not
exist. This matters more here than it did for GX: `gnt4_DVDReadPrio_bl` has **one** static
call site and is the single most important entry point on the disc side, because that one
site is the game's own file driver and every asset in the game passes through it.

### 4.1 DVD — the ranked inventory

| | |
|---|---|
| DVD symbols in the DOL | **47** |
| Called by anything | 44 |
| **Called by ROM game code** | **15** |
| **Static game-code call sites** | **41** (all bridged; none in-window) |
| SDK-internal call sites (context only) | 120 |
| DI registers the corpus touches | 10 (27 reads, 57 writes) — all inside the `gnt4_*` SDK, i.e. behind the seam |

`tier`: `translated` = the call does its real work; `latched` = recorded but not acted on;
`declared-nop` = correctly has no host-visible effect; `—` = **not implemented, fails
loudly**.

| # | entry point | ROM addr | game call sites | distinct callers | cumulative | tier |
|---|---|---|---|---|---|---|
| 1 | `DVDGetCommandBlockStatus` | 0x8020f7d0 | 11 | 5 | 26.8% | translated |
| 2 | `DVDGetDriveStatus` | 0x8020f81c | 7 | 5 | 43.9% | translated |
| 3 | `DVDCheckDisk` | 0x8020fc7c | 5 | 2 | 56.1% | translated |
| 4 | `DVDInit` | 0x8020d798 | 3 | 3 | 63.4% | declared-nop |
| 5 | `DVDCancel` | 0x8020fba4 | 2 | 2 | 68.3% | translated |
| 6 | `DVDClose` | 0x8020d2b4 | 2 | 2 | 73.2% | translated |
| 7 | `DVDOpen` | 0x8020d1ec | 2 | 2 | 78.0% | translated |
| 8 | `DVDReadAbsAsyncPrio` | 0x8020f380 | 2 | 1 | 82.9% | translated |
| 9 | `DVDGetCurrentDiskID` | 0x8020fc74 | 1 | 1 | 85.4% | translated |
| 10 | `__DVDPrepareResetAsync` | 0x8020fd74 | 1 | 1 | 87.8% | — |
| 11 | `DVDInquiryAsync` | 0x8020f6bc | 1 | 1 | 90.2% | — |
| 12 | `DVDReadPrio` | 0x8020d5ec | 1 | 1 | 92.7% | translated |
| 13 | `DVDResume` | 0x8020f8d8 | 1 | 1 | 95.1% | declared-nop |
| 14 | `DVDSetAutoInvalidation` | 0x8020f8c8 | 1 | 1 | 97.6% | latched |
| 15 | `HSD_DVDInit` | 0x80253bbc | 1 | 1 | 100.0% | declared-nop |

Three DVD symbols are in the DOL but never appear as a textual call site:
`gnt4_DVDConvertPathToEntrynum_bl`, `gnt4_DVDReadAsyncPrio_bl`,
`gnt4___DVDInterruptHandler_bl`. The first two are definitely reached at runtime —
`DVDOpen`'s body calls the first and the game's file driver `zz_0274dd4_` calls the second
— so this is a limitation of a line-based static count, not evidence of dead code, and it
is one more reason §8 wants a trace.

### 4.2 DVD — coverage

| tier | entry points | share of the 15 | ROM call sites covered | share of the 41 |
|---|---|---|---|---|
| `translated` (does its real work) | 9 | 60.0% | 33 | **80.5%** |
| `+ latched` (accepted, not acted on) | 10 | 66.7% | 34 | 82.9% |
| `+ declared-nop` (correctly inert) | 13 | 86.7% | 39 | 95.1% |
| **not implemented — fails loudly** | **2** | **13.3%** | 2 | 4.9% |

The honest headline is the first row: **80.5% of the ROM's static DVD call sites reach an
entry point that does its real work.** The other rows are reported next to it rather than
merged into it. A coverage figure of 80.5% next to a verification figure of 0% is the
accurate picture, and the two must always be quoted together.

### 4.3 Audio — the ranked inventory

| | |
|---|---|
| Audio symbols in the DOL | **26** |
| Called by anything | 23 |
| **Called by ROM game code** | **20** |
| **Static game-code call sites** | **40** |
| — of which **bridged** (cross the seam) | **6** |
| — of which **in-window** (do not) | **34** |
| SDK-internal call sites (context only) | 11 |
| AI/DSP registers the corpus touches | **18** (403 reads, 342 writes) |

| # | entry point | ROM addr | seam | game call sites | callers | cumulative | tier |
|---|---|---|---|---|---|---|---|
| 1 | `AISetStreamVolLeft` *(really SetVolRight)* | 0x802149c0 | in-window | 10 | 6 | 25.0% | MMIO |
| 2 | `AIInitDMA` | 0x80214634 | in-window | 4 | 3 | 35.0% | MMIO |
| 3 | `__AI_SRC_INIT` | 0x80214cd8 | in-window | 3 | 3 | 42.5% | MMIO |
| 4 | `AIGetStreamPlayState` *(really GetVolLeft)* | 0x802149b0 | in-window | 3 | 3 | 50.0% | MMIO |
| 5 | `ARAlloc` | 0x80214ff0 | in-window | 3 | 3 | 57.5% | MMIO |
| 6 | `AISetStreamPlayState` | 0x802146d4 | in-window | 2 | 2 | 62.5% | MMIO |
| 7 | `__OSStopAudioSystem` | 0x80200518 | **bridged** | 2 | 2 | 67.5% | translated |
| 8 | `__AI_set_stream_sample_rate` | 0x802148b0 | in-window | 1 | 1 | 70.0% | MMIO |
| 9 | `__AICallbackStackSwitch` | 0x80214c80 | in-window | 1 | 1 | 72.5% | — |
| 10 | `__ARChecksize` | 0x80215208 | in-window | 1 | 1 | 75.0% | MMIO (ARAM DMA absent) |
| 11 | `AIGetDSPSampleRate` | 0x8021489c | in-window | 1 | 1 | 77.5% | MMIO |
| 12 | `AIInit` | 0x802149ec | in-window | 1 | 1 | 80.0% | MMIO |
| 13 | `AISetDSPSampleRate` | 0x802147bc | in-window | 1 | 1 | 82.5% | MMIO |
| 14 | `AIStartDMA` | 0x802146bc | in-window | 1 | 1 | 85.0% | MMIO |
| 15 | `ARFree` | 0x80215058 | in-window | 1 | 1 | 87.5% | MMIO |
| 16 | `ARInit` | 0x802150cc | in-window | 1 | 1 | 90.0% | MMIO (ARAM sizing absent) |
| 17 | `__OSInitAudioSystem` | 0x8020035c | **bridged** | 1 | 1 | 92.5% | declared-nop |
| 18 | `ARQInit` | 0x80216bcc | **bridged** | 1 | 1 | 95.0% | declared-nop |
| 19 | `OSGetSoundMode` | 0x80205750 | **bridged** | 1 | 1 | 97.5% | translated |
| 20 | `OSSetSoundMode` | 0x802057d0 | **bridged** | 1 | 1 | 100.0% | latched |

`MMIO` in the tier column means: the port compiles this function into the module, and what
the host provides is the register access underneath it. Whether that function then works
is a question about the registers, not about an adapter — answered in §4.5.

Three ARQ symbols are in the DOL and never appear as a textual call site:
`gnt4_ARQPostRequest_bl`, `gnt4___ARQCallbackHack_bl`,
`gnt4___ARQInterruptServiceRoutine_bl`. `ARQPostRequest` in particular is how samples reach
ARAM, so its absence from the static count is the same line-based limitation noted in §4.1.

### 4.4 Audio — coverage, reported on two denominators because there are two seams

| surface | implemented | total | call sites covered | total call sites |
|---|---|---|---|---|
| **bridged** entry points (what an adapter can cover) | 5 | 5 | 6 | 6 |
| — of those, `translated` | 2 | | 3 | |
| — `latched` | 1 | | 1 | |
| — `declared-nop` | 2 | | 2 | |
| **in-window** entry points (an adapter cannot cover these) | — | 15 | — | 34 |

Quoting a single "audio coverage" number over all 40 sites would either flatter the
adapters (they cannot cover in-window calls) or damn them (they are not supposed to). Both
denominators are reported, always together, by `audioTieredCoverage()`.

### 4.5 Audio — the MMIO surface, which is where the work actually is

Of the **18** registers the corpus touches, this host **acts on 9** and **stores 9**:

| register | block | reads | writes | host |
|---|---|---|---|---|
| `0xCC005028` | DSP | 105 | 107 | **stored only** — ARAM DMA length/enable; no transfer is performed |
| `0xCC00500A` | DSP | 95 | 53 | **stored only** — DSP control/status; reset, halt and interrupt bits inert |
| `0xCC005020` | DSP | 72 | 72 | **stored only** — ARAM DMA main-memory address |
| `0xCC005024` | DSP | 70 | 72 | **stored only** — ARAM DMA ARAM address |
| `0xCC006C00` | AI | 29 | 21 | **acted on** — AICR: SCRESET zeroes the counter, DSPFR selects 32/48 kHz |
| `0xCC006C04` | AI | 6 | 4 | **acted on** — AIVR: decoded into per-channel gain |
| `0xCC005004` | DSP | 6 | 0 | **acted on** — DSP→CPU mailbox; always reads empty (null DSP) |
| `0xCC005036` | DSP | 3 | 3 | **acted on** — AI DMA length + enable; the 0→1 edge starts a transfer |
| `0xCC006C08` | AI | 5 | 0 | **acted on** — AISCNT; advanced by every completed transfer |
| `0xCC005000` | DSP | 1 | 3 | **acted on** — CPU→DSP mailbox high; busy bit reads back clear |
| `0xCC005012` | DSP | 2 | 2 | stored only |
| `0xCC00501A` | DSP | 2 | 1 | **stored only** — ARAM size register; `ARInit` therefore sizes nothing |
| `0xCC005030` | DSP | 2 | 1 | **acted on** — AI DMA address, high half |
| `0xCC005032` | DSP | 2 | 1 | **acted on** — AI DMA address, low half |
| `0xCC005006` | DSP | 2 | 0 | stored only |
| `0xCC005002` | DSP | 0 | 1 | **acted on** — CPU→DSP mailbox low; completes the recorded command word |
| `0xCC005016` | DSP | 1 | 0 | stored only |
| `0xCC006C0C` | AI | 0 | 1 | **stored only** — AIIT; the host's DMA interrupt is not timed |

A "stored only" register still round-trips correctly through the ROM's read-modify-write
sequences, which is why nothing crashes — but its hardware effect does not happen. The
biggest one by far is the **ARAM DMA trio** (`0xCC005020/24/28`, 247 reads and 251 writes
between them, the busiest audio registers in the corpus): ARAM is where MusyX keeps its
sample pool ([CORPUS] `zz_00f18fc_` allocates `0xD00000` of it), and this host performs no
transfer into it. That is reported as `ARAM_DMA_NOT_MODELLED`. It is a gap, not a nop, and
the distinction is the point of §4.5 existing at all.

An access to an address **outside** the AI and DSP windows throws rather than being
invented or swallowed: a register this host does not model is a hardware block it does not
model.

---

## 5. What was built

```
packages/rom-runtime/src/dvd/
  inventory.generated.ts  the measurement, as data the runtime imports
  disc.ts                 GameCube FST parse + serialize; SyntheticDisc; ImageDisc
  adapters.ts             DvdHost, the 13 implemented entry points, loud throws
  index.ts

packages/rom-runtime/src/audio/
  inventory.generated.ts  the measurement, calls AND registers
  adpcm.ts                Nintendo DSP-ADPCM decode, in TypeScript for the first time
  registers.ts            the AI/DSP register file + the naming corrections
  backend.ts              AudioBackend; headless recorder; WebAudio backend
  adapters.ts             AudioHost, the 5 bridged entry points, the MMIO imports
  index.ts

packages/rom-runtime/src/selftest/hleSelftestMain.ts   the browser proof page
packages/rom-runtime/test/browser/hle-index.html
packages/rom-runtime/test/fixtures/hle-selftest/       leg A — hand-written
packages/rom-runtime/test/fixtures/hle-rom-unit/       leg B — verbatim ROM
packages/rom-runtime/test/fixtures/adpcm/              the cross-check vector

scripts/hle-call-inventory.mjs          the measurement
scripts/build-disc-index.mjs            owner-side: real disc image -> FST index
scripts/smoke-audio-dvd-host-phase.mjs  the proof phase
```

### 5.1 Provenance discipline — `[CORPUS]` vs `[SDK]`

Every constant carries one of two labels, exactly as `gx/enums.ts` does:

* **`[CORPUS]`** — the fact is a read or a write the ROM's own decompiled body performs,
  and the citing comment names the function and its address. This is the strong label.
* **`[SDK]`** — the fact comes from the GameCube hardware or SDK's documented layout. This
  is the weak label and it is used only where the corpus does not settle the question.

The DVD half is unusually well served by `[CORPUS]`, because the ROM ships its own copy of
the DVD library and the decompiler recovered it. Every field offset in `DVD_CB` and
`DVD_FILEINFO` is a `param_1[N]` index in `gnt4_DVDReadAbsAsyncPrio_bl` @`0x8020f380` or a
`*(u32 *)(param_10 + 0x30)` store in `gnt4_DVDOpen_bl` @`0x8020d1ec`, and two of them are
confirmed independently from the caller's side (the game's own `gcCiGetFileSize` reads
`handle + 0x5c`, which is `fileInfo + 0x34`, the length). The 12-byte FST record layout is
likewise `[CORPUS]`: `gnt4_DVDOpen_bl` and `gnt4_entryToPath_bl` read it field by field.

The audio half is `[CORPUS]` for the register semantics that matter — the AI DMA address
masking, the length shift, the enable bit, the volume field split, the DSP sample-rate bit
— and `[SDK]` for the bit positions nothing in the ROM exercises.

### 5.2 Byte order — two of them, both deliberate

`docs/gx-hle-host.md` §4.2 draws this distinction for GX; it recurs here with the same
rule and is worth stating because getting it backwards is silent:

* **Anything that came off the disc is BIG-endian.** The FST is disc data written by the
  console's tools, so `parseGcFst` reads it big-endian.
* **The AI DMA buffer is BIG-endian**, because the DAC fetches it as big-endian signed
  16-bit stereo pairs. `pcmToAiDmaBytes` serializes explicitly; a `memcpy` of an
  `Int16Array` would be wrong.
* **Anything that lives in the module's memory is LITTLE-endian**, because that is wasm32
  linear memory. The words `DVDOpen`'s adapter writes into a `DVDFileInfo` are
  little-endian, because ported ROM code reads them with wasm `i32.load`.
* **A hardware register is a NUMBER, not a byte stream.** The MMIO imports carry host-order
  integers. This is the opposite of the write-gather pipe, which is a FIFO and therefore
  big-endian on the wire — the two are different for a real reason, and `gf_hw_mmio.h` says
  so where a reader will hit it.

### 5.3 The DSP-ADPCM decoder is NEW CODE, and here is how it is checked

§2 records that no TypeScript ADPCM decoder existed. `audio/adpcm.ts` is a port of
`decode_dsp_adpcm` in `scripts/export-combat-se.py` — same frame walk, same nibble order,
same sign extension at 8, same rounding constant, same clamp, same history update.

One intentional difference, and it is a real bug if reversed. The Python reference computes
`(nibble*scale*2048 + c1*hist1 + c2*hist2 + 1024) >> 11` where `>>` is an arithmetic shift
over unbounded ints. The intermediate exceeds 2^31 for loud input (`nibble*scale*2048`
alone reaches 2^29 and `c1*hist1` reaches 2^30), and JavaScript's `>>` truncates its
operand to int32 first, so it would silently produce different samples. The port uses
`Math.floor(x / 2048)`, which is exact for |x| < 2^53 and floors negatives the same way.

**A port checked only against itself proves nothing**, so
`test/fixtures/adpcm/gen-vector.py` runs the ORIGINAL Python decoder over four inputs
chosen to hit the arithmetic corners — the coefficient-zero case whose output is
derivable by hand, a realistic signed coefficient table across all eight predictor pairs,
coefficients big enough to saturate both clamps, and scale exponent 15 on every frame —
and writes the expected PCM to `adpcm-vector.json`. The self-test decodes the same inputs
in TypeScript and compares **sample for sample**; all four cases match exactly.

That is an **independent second implementation**, and the one it is checked against is the
implementation that produced shipped assets. It is the strongest evidence available here.
It is still not console capture: both could share a misunderstanding of the format, and
only real DSP output would rule that out.

### 5.4 Loudness

Copied from the GX host without softening:

* an entry point the host does not implement gets an adapter that **THROWS**, naming the
  symbol, its ROM address, its static call-site count and its distinct-caller count. It
  never returns quietly. A silent no-op in an asset-loading seam hands the game a buffer of
  zeroes that it will parse as a model;
* the audio thrower says something extra when the symbol is **in-window**: reaching it at
  all means the module excluded a function it was supposed to port, which is a different
  bug from a missing adapter and deserves a different message;
* an MMIO access outside the AI/DSP windows throws;
* a DVD read past the end of the disc throws rather than short-reading;
* a `DVDReadPrio` whose (offset, length) is outside the file throws — the ROM's own body
  `OSPanic`s there, and refusing is the point;
* a path argument with no NUL in 512 bytes throws, because that is a mis-marshalled
  pointer, not a filename;
* short reads, unaligned lengths, zero-length transfers, out-of-arena DMA and latched
  values all append to `diagnostics`, which the report always carries.

### 5.5 Completion callbacks are delivered as invoke-requests, not called from adapters

A GameCube DVD completion and an AI DMA completion are **interrupts**. `AIInit`
@`0x802149ec` installs `FUN_80214bd4` on interrupt 5 and unmasks `0x4000000`; that handler
calls whatever pointer `AIRegisterDMACallback` stored. Delivering such a callback from
inside the adapter that raised it would run ROM code while the ROM is already on the stack.

So both hosts **queue** completions — `DvdHost.pending`, `AudioHost.pendingInterrupts` —
and expose `drainCallbacks` / `drainInterrupts`. The host owns the queue; the caller owns
the transport. `RomRuntimeHost.postEvent` publishes an invoke-request that the parked
worker runs on its own stack, which is design R3's shape. §6 proof 2 exercises exactly
that: a ROM-side callback function's address goes into a command block, the adapter queues
it, and `postEvent` delivers it — after which the ROM-side callback reports the byte count
it was handed.

---

## 6. The end-to-end proof

`scripts/smoke-audio-dvd-host-phase.mjs`, opt-in behind `GF_SMOKE_AUDIO_DVD_HOST=1`, and
appended to `scripts/smoke-browser-game.mjs` as one import line at the end of the file. It
owns its own bundle, COOP/COEP-isolated static server, headless Chrome and CDP session.
**61 checks, all passing.** Evidence lands in `.tmp/audio-dvd-host-smoke/evidence/`
(`hle-selftest.png`, `console.log`, `hle-selftest-results.json`).

Two legs, and the second one is not hand-written.

### 6.1 Leg A — hand-written ROM-shaped call sequences

`test/fixtures/hle-selftest/hle_selftest.c`, 16 MiB shared memory. A human chose these
sequences, modelling them on the game's own file driver `zz_0274dd4_` and on `AIInit`'s
register order. It proves the seam carries the calls; it says nothing about the game.

1. **Open, read, close.** `DVDOpen` resolves `/borg/bg0001.dat` against a real FST,
   `DVDReadPrio` reads 0x40 bytes, and the bytes in GC memory are asserted to be **the
   disc's bytes**, first sixteen and last one. The `DVDFileInfo`'s length and start
   address words are checked against the FST entry.
2. **The async completion callback.** `hle_callback_ptr()` hands out the address of a
   ROM-side C function. `DVDReadAbsAsyncPrio` is called with it; the adapter queues the
   completion; `drainCallbacks` hands it to `host.postEvent("hle_deliver_callback", …)`,
   which delivers it at a worker park point. The ROM-side callback then reports that it ran
   exactly once, with the transferred byte count and its own command block.
3. **The loud failure.** `gnt4_DVDInquiryAsync_bl` has one static call site and no adapter.
   Calling it rejects with `BridgeStatus.ADAPTER_THREW` and the host names the hit.
4. **The registers and the mailbox.** The bring-up sequence selects the 32 kHz DSP rate;
   `AIVR` bits 0-7 and 8-15 decode as left and right; and `hle_dsp_post(0xBABE0180)` — the
   MusyX command word `zz_0217dd8_` posts before every audio frame — **terminates**,
   proving the null DSP consumes it instead of hanging the module.

### 6.2 Leg B — the VERBATIM ROM UNIT

`test/fixtures/hle-rom-unit/rom.c`, its own worker and its own `0x807A0000`-byte shared
memory. Seven ROM bodies, decompiled verbatim:

| ROM addr | symbol | source |
|---|---|---|
| `0x80214634` | `AIInitDMA` | chunk_0065.c:1227 |
| `0x802146bc` | `AIStartDMA` | chunk_0065.c:1247 |
| `0x80214994` | `zz_0214994_` (the real `AISetStreamVolLeft`) | chunk_0065.c:1417 |
| `0x802149c0` | `AISetStreamVolLeft` (misnamed; sets RIGHT) | chunk_0065.c:1442 |
| `0x802147ac` | `zz_02147ac_` (the real `AIGetStreamPlayState`) | chunk_0065.c:1301 |
| `0x80238c90` | `zz_0238c90_` (the ROM's own `strcat`) | chunk_0069.c:2688 |
| `0x802756fc` | `FUN_802756fc` (`gcCiGetFileSize`) | chunk_0075.c:1 |

**Four rewrites, exhaustively listed** in `build.sh`, and nothing else: (1) the AI/DSP MMIO
lowering; (2) Ghidra's placeholder types given real C types in a decls header, as the GX
fixture does; (3) one dead assignment from a `void` callee dropped — a real PowerPC artifact
where the caller reads `r3` after a callee that never set it, and the value flows only into
a float-register ghost slot no adapter reads; (4) one split stack variable re-joined —
Ghidra renders the `DVDFileInfo` as `int aiStack_148[13]` plus a separate `uint local_114`
that is really the same object's `+0x34` word, and in C those would be two distinct objects,
so the fixture would have returned stack garbage.

**The lowering is NOT gate output**, unlike the GX fixture's. `port_wgpipe_lowering.py`
covers `0xCC008000` and only that window. This is stated in the header, in `build.sh`, and
in the host's runtime diagnostic, and it is remainder item 1.

What leg B proves:

5. **Real ROM code drives the DAC.** A DSP-ADPCM block is decoded to PCM by the TypeScript
   decoder, interleaved into big-endian stereo (right channel inverted, so a host that
   mixed the channels up fails instead of passing by symmetry) and written into the arena.
   Then `AIInitDMA(0x80600000, 0x280)` and `AIStartDMA()` — the ROM's own bodies — run. The
   host asserts that:
   * `AIInitDMA` alone starts **nothing** (it does not set the enable bit),
   * `AIStartDMA` starts **exactly one** transfer,
   * the address the ROM's own masking encoded into two half-registers **decodes back to
     `0x80600000`**,
   * the length decodes back to `0x280` = 160 stereo frames at 32 kHz,
   * the first, last and inverted-channel samples are the decoder's samples,
   * a WebAudio `AudioBuffer` with two channels and 160 frames was handed to the device,
     and its normalized samples match,
   * the DAC's sample counter advanced by 160 and one AI DMA interrupt is owed to the ROM.
6. **Real ROM code drives the disc.** `FUN_802756fc` (`gcCiGetFileSize`) strcpy's the base
   directory the page planted at `0x8040C178`, appends the filename with the ROM's own
   `strcat`, normalizes backslashes, calls `DVDOpen`, reads the length word out of the
   `DVDFileInfo` the adapter filled in, calls `DVDClose`, and **returns the file's real
   length**. No path went missing and no unimplemented entry point was hit.
7. **The ADPCM port matches the Python reference** on all four cross-check cases (§5.3).

### 6.3 What the proof does not show

* Nothing about whether any of this matches a GameCube. §1 claims 3 and 4.
* The disc is one the page **built**. §2.
* Above all: **the PCM in proof 5 was placed there by the page, not produced by the game.**
  A real composed module would DMA silence, because the mixer is absent. The proof shows
  the *transport* is correct, which is worth having and is not the same thing.

---

## 7. What is NOT implemented

### 7.1 DVD entry points (2 of 15, 4.9% of static call sites)

| entry point | ROM addr | call sites | why it is not done |
|---|---|---|---|
| `gnt4___DVDPrepareResetAsync_bl` | 0x8020fd74 | 1 | drive reset sequencing; the host has no drive state machine and no reset to prepare. Needs a decision about what "reset" means for a host disc before it can be a `declared-nop` rather than a gap |
| `gnt4_DVDInquiryAsync_bl` | 0x8020f6bc | 1 | returns the drive's firmware inquiry block. Fabricating one is possible and was deliberately not done: the ROM's boot path branches on it, and inventing firmware bytes is exactly the kind of plausible-looking wrongness this host refuses |

### 7.2 Audio — everything below the registers

The audio half's gaps are not a list of entry points; they are a list of hardware blocks.

| gap | scale | consequence |
|---|---|---|
| **The DSP mixer** (MusyX microcode) | the whole synthesiser | the DMA buffer is silence. §3.2 |
| **ARAM DMA** (`0xCC005020/24/28`) | 247 reads, 251 writes — the busiest audio registers | samples never reach ARAM. §4.5 |
| **ARAM sizing** (`0xCC00501A`) | 3 accesses | `ARInit` sizes nothing; `__ARChecksize` (582 register touches, the biggest single audio body in the corpus) is untested against this host and may not terminate |
| **DSP control/status** (`0xCC00500A`) | 95 reads, 53 writes | DSP reset/halt/interrupt bits are inert |
| **AI interrupt timing** (`0xCC006C0C`) | 1 write | the host's DMA completion is queued, not timed. Nothing paces it at 5 ms |
| **The AI streaming path** | `AISetStreamPlayState`, `__AI_SRC_INIT` | the DVD audio-streaming channel (`DVDLowAudioStream`) is entirely unmodelled |
| **`__AICallbackStackSwitch`** | 1 call site | switches the interrupt callback onto a dedicated stack; meaningless without an interrupt context, and not declared a nop because that judgement has not been made carefully enough to declare |

### 7.3 Verification — zero, and the dominant gap for both halves

There is no DVD trace, no audio capture, no reference. The assertions in §6 were predicted
from the same understanding that produced the implementations. The single exception is the
ADPCM decoder (§5.3), which is checked against an independent implementation — and even
that is not console capture.

Concretely, none of these has ever been done:

* read a file on console and on this host and compare the bytes;
* capture the DVD command-block state sequence a real read produces and compare the timing
  model against it (it will not match — §4.4 — but the *shape* of the mismatch is
  information);
* capture the AI DMA buffer contents on console for one second of gameplay and compare
  against what this host DMAs (it will be silence, which is the point);
* run `decode_dsp_adpcm` and this port against a real `.dpk` from the disc and compare
  both against the DSP's own output.

---

## 8. What the next agent should do, in order

1. **Teach the assembly gate the AI and DSP MMIO windows.** This is the top item because
   nothing else in the audio half can reach a real composed module without it. The pattern
   exists: `research/tools/OGhidra/src/port_wgpipe_lowering.py` lowers `0xCC008000` behind
   `OGHIDRA_PORT_WGPIPE_LOWERING=1` and fails closed on any store it cannot lower.
   Generalize it to an address-window table, add `0xCC005000..0xCC00503F` and
   `0xCC006C00..0xCC006C0F`, and emit `__gf_mmio_load_u16/u32` /
   `__gf_mmio_store_u16/u32` — the imports `registerMmioAdapters` already binds. Delete
   `test/fixtures/hle-rom-unit/gf_hw_mmio.h` when the gate emits its own, and delete the
   `AI_MMIO_NOT_GATE_LOWERED` diagnostic with it. Note the shape difference from the pipe:
   these imports are ADDRESSED, and a register is a number rather than a byte stream.
2. **Get a real disc into the loop.** `scripts/build-disc-index.mjs` turns an
   owner-supplied image into an FST index; `ImageDisc` reads it. What is missing is the
   wiring: a host-side loader that reads the index, a byte source (an HTTP range-request
   reader over a disc image, or a directory of extracted files), and a decision about
   whether the browser is allowed to hold 1.4 GB. Once that exists, the DVD half stops
   being a proof and starts loading real assets — and the force navigator's
   `zz_0041288_ → zz_00410bc_` borg-archive-by-id streaming becomes runnable.
3. **Implement the two remaining DVD entry points** (§7.1), which needs one decision each
   rather than much code.
4. **Decide what to do about the DSP.** The options, in increasing order of cost and
   fidelity: (a) leave it absent and let the ROM's audio path run silently, which is the
   status quo and is at least honest; (b) intercept ABOVE MusyX — the game's own sound
   dispatcher `zz_00efb3c_` @`0x800EFB3C` splits a sound id into `bank = id >> 7` and
   `sample = id & 0x7f`, and `packages/audio`'s `resolveCue` already ports that arithmetic
   and is self-tested, so a cue-level bridge could play the extracted OGGs from the
   composed module without any DSP at all; (c) write a MusyX-shaped software mixer that
   reads the same command stream the microcode does; (d) emulate the GC DSP. Option (b) is
   the cheapest thing that makes the composed module audible and it reuses work that
   already exists — but note what it is: it produces sound, it does not translate the ROM's
   audio path, and the coverage tables here must never be allowed to absorb it.
5. **Model ARAM DMA** (§7.2). Small and self-contained: `0xCC005020/24/28` plus the
   completion interrupt, moving bytes between the arena and `AudioHost.aram`. Pointless
   while the mixer is absent, and a prerequisite for options 4(c) and 4(d).
6. **Pace the DMA.** The host completes a transfer synchronously and queues the interrupt.
   Real hardware fires every 5 ms and the ROM refills the other half of the buffer. Until
   something drives `drainInterrupts` on a clock, a composed module's audio loop will not
   run at the right rate — and this interacts with whatever the frame loop does, so it is
   a design decision, not a patch.
7. **Get an oracle for either half.** In cost order: a Dolphin trace of DVD command blocks
   is the cheapest useful capture and would settle both the field offsets (already
   `[CORPUS]`-confident) and the timing model (knowingly wrong). An AI DMA buffer capture
   is next. Both are the same category of missing thing `docs/gx-hle-host.md` §7.1 names
   for graphics, and all three want the same harness.
8. **Re-run the inventory when the corpus changes.** `node scripts/hle-call-inventory.mjs`
   regenerates both JSON measurements and both generated TypeScript modules. The coverage
   numbers in this document are computed from them, so they move together — and if a
   number here ever disagrees with what the smoke phase prints, the smoke phase is right.

---

## 9. How to run it

```bash
node scripts/hle-call-inventory.mjs              # re-measure both surfaces
python3 packages/rom-runtime/test/fixtures/adpcm/gen-vector.py   # re-emit the cross-check vector
GF_SMOKE_AUDIO_DVD_HOST=1 node scripts/smoke-browser-game.mjs    # full route + this phase
node scripts/smoke-audio-dvd-host-phase.mjs      # this phase alone
bash packages/rom-runtime/test/fixtures/hle-rom-unit/build.sh    # rebuild both wasm fixtures (needs emsdk)
```

Browser smokes flake under load. A failure that does not reproduce on a second run is a
flake; one that does is a regression. Say which.
