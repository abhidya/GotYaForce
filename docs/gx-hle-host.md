# The GX HLE host — the browser standing in for the GameCube's graphics hardware

Status: **PARTIALLY VERIFIED — one seam and one draw, against the console; everything else
is still self-validated.** The seam is proven, the pipeline is mostly translated rather
than mostly stubbed, and as of 2026-08-31 a GX trace oracle exists and one ROM draw has
been compared against real GameCube pixels. **No individual adapter is `verified`** and
none of the coverage figures below is a verification figure.
Date: 2026-08-31 (previous revisions 2026-08-30, 2026-08-29). Design authority:
`docs/playable-port-design.md` (V2 F2 "Stage D — SDK seam", V3 non-fatal note 1's claim
bar, V4 H2's bridge, V5 I1's adapter contract).

**What changed on 2026-08-31** — the previous revision's §7.1, "get a GX trace oracle", is
the whole of it:

* **`gx_callstream_green`** (§6.3.1): the console's own GX call stream and
  write-gather-pipe byte stream for `zz_0027c34_`, captured from the real game and replayed
  through the gate-lowered wasm unit. **4/4 invocations, 124/124 events identical.** It
  verifies the lowering, the call sequence and argument marshalling; it verifies no pixel;
* **`gx_framebuffer_equivalent`** (§6.3.2): two console frames differing only in whether
  that draw ran, compared against the host's own prediction over **286,720 pixels**.
  Touched region matches EXACTLY, 0 pixels changed outside it, per-channel |Δ| p99 = 3/255.
  This **settles the `[SDK]` blend-factor numbering** against the console;
* both harnesses have a **16-test deliberate-red rehearsal** and non-vacuity guards
  (§6.3.3), so neither can pass on nothing;
* the **runtime call-frequency ranking** §2 said did not exist now does (§6.4), and it
  **inverts the static ranking**: 507 calls in 32 s to entry points the host does not
  implement, fog first — which is why §7's order changed;
* §6.5 records the Dolphin rig facts this cost: the stub refuses MMIO, the backend string
  must be exactly `Software Renderer` or the XFB reads back all zero, and a stub session
  lasts about 40 s.

**What changed on 2026-08-30**, kept because a reader of that revision will be looking
for it:

* the **TEV combiner** is implemented as SHADER GENERATION from latched state (§6.1 was
  the largest unimplemented block; it is now the largest *implemented* one) — `tev.ts`;
* **texture sampling** works: GameCube texture formats are decoded out of the arena at the
  GC address the ROM gave and uploaded — `texture.ts`. The brief for that work assumed a
  TypeScript decoder already existed to reuse. It did not, and §4.5 records what is actually
  in the repo so the next agent does not go looking again;
* **texgen** and **per-vertex lighting** are evaluated in a generated vertex shader;
* the **write-gather-pipe blocker (old §7.1) is CLOSED** — the assembly gate lowers those
  stores, and the browser leg now drives the gate's own output for the ROM's own draw
  function instead of a hand-written fixture (§5);
* the **arena byte-order question (old §7.4) is ANSWERED** (§4.2);
* the `GXSetChanMatColor` signature the previous revision called "genuinely ambiguous" is
  resolved, with the evidence recorded at `readColor` in `adapters.ts`;
* coverage moved from **16/76 entry points, 49.2% of ROM call sites** to **49/76, 87.1%**
  — and the verification figure is still exactly **zero**, which is the whole point of
  §1 and of reporting the two side by side.

---

## 0. What this is, in one paragraph

`docs/playable-port-design.md` names the browser as the HLE host behind the SDK seam: the
composed ROM module executes the game's own code, and everything the GameCube SDK used to
do — graphics, audio, OS, DVD — is provided by the host. This document covers the
graphics half. It describes a `packages/rom-runtime`-side GX adapter set that receives the
ROM module's GX calls through the existing H2 Atomics bridge, tracks the GX pipeline
state, decodes the write-gather-pipe traffic the ROM uses to submit vertices, and
rasterizes the result through WebGL2. Most of the pipeline is now translated rather than
stubbed — the TEV combiner, texture sampling, texgen and per-vertex lighting all reach the
framebuffer — but **none of it is verified**, and the distinction is made structurally
rather than by promise: every adapter is registered with `evidenceClass: "synthetic"`, so
the adapter registry refuses the whole set unless a host explicitly opts in to pilot work.

**This is NOT a replacement for `packages/render/`.** That package renders the real
extracted assets (HSD models via glTF/DAE, textures, stage lighting from exported HSD
render state) through three.js, and it is the TS recreation's own rendering path. The GX
host is the path the **composed ROM module** takes when *its* code calls GX. The two
coexist for the whole hybrid period (design E2's dual-canvas rule).

---

## 1. The claim bar, stated before any numbers

Three claims, in descending order of how much they are worth:

1. **What is proven.** ROM-shaped GX call sequences cross the real bridge, decode into the
   right primitives, and rasterize to a framebuffer whose pixels are what the call
   sequence asked for. Proof: §5.
2. **What is not even attempted yet.** No frame this path produces has ever been compared
   against a real GameCube frame. There is no GX trace capture, no reference framebuffer,
   no oracle. Every adapter is a hand-written stand-in derived from the GX API's semantics
   and from the ROM's decompiled call sites. The pixel assertions in §5 are predicted from
   that same understanding, so they are self-consistency checks and cannot detect a shared
   misunderstanding — §6.3 says this at length because it is the easiest thing here to
   read too generously.
3. **What the ceiling is, even after verification exists.** The design's own words:
   **"framebuffer-equivalent, never pixel-identical"** (V3 non-fatal note 1). WebGL
   rasterization cannot match Flipper. EFB copy semantics, GameCube fixed-point
   rasterization rules, the 24-bit depth comparison and the texture filter kernels all
   differ, and the TEV — now translated rather than absent — computes in float here and in
   a signed 10-bit fixed-point space with per-stage rounding there. Translating the
   combiner moved this path closer to the ceiling; it did not raise the ceiling. No
   document, log line or test name may quietly upgrade this.

The code says the same thing in the same words. `GX_NO_BEHAVIOURAL_CLAIM` in
`packages/rom-runtime/src/gx/adapters.ts` is printed by the self-test page, embedded in
the machine-readable self-test payload, and asserted by the smoke phase — which fails if
any GX adapter ever claims `evidenceClass: "verified"`.

---

## 2. The measured call surface

The work was defined by measurement, not by the general GameCube SDK.
`scripts/gx-call-inventory.mjs` walks `research/decomp/ghidra-export`, attributes every
call site to its enclosing function, and separates two populations:

* **game call sites** — the caller is ROM game code (`FUN_*`, `zz_*`). These are the calls
  that will cross the SDK seam, because the entire `gnt4_*` family (996 functions, HSD
  included) is excluded from porting by design.
* **SDK-internal call sites** — the caller is itself a `gnt4_*` SDK or HSD function. Those
  calls happen inside the host's own implementation of the SDK and never cross the seam.

Measured totals:

| | |
|---|---|
| GX symbols present in the DOL | **157** |
| GX symbols called by anything | 143 |
| **GX entry points called by ROM game code** | **76** |
| **Static game-code call sites** | **502** |
| SDK-internal call sites (context only) | 322 |

Outputs: `research/decomp/data/gx-call-inventory.json` and the generated
`packages/rom-runtime/src/gx/inventory.generated.ts`, which the runtime imports so that the
coverage percentage below is *computed from the measurement* rather than asserted.

**Honesty note on the ranking.** These are STATIC call-site counts — how many places in
the ROM call an entry point — not runtime frequency. A per-frame frequency ranking
requires a Dolphin trace and does not exist. The distribution is steep enough that this
matters less than it might: the top 20 entry points account for **69.9%** of all static
call sites.

### 2.1 The ranked inventory

`tier` is what the host does with it: `translated` = the call changes what the backend
draws; `latched` = recorded in `GxState` but not yet acted on; `declared-nop` = correctly
has no host-visible effect; `—` = **not implemented, fails loudly**.

| # | entry point | ROM addr | game call sites | distinct callers | cumulative | tier |
|---|---|---|---|---|---|---|
| 1 | `GXSetVtxDesc_bl` | 0x80225894 | 45 | 18 | 9.0% | translated |
| 2 | `GXSetVtxAttrFmt_bl` | 0x802261e4 | 45 | 18 | 17.9% | translated |
| 3 | `GXBegin_bl` | 0x8022760c | 19 | 17 | 21.7% | translated |
| 4 | `GXSetTevOrder_bl` | 0x8022a14c | 18 | 15 | 25.3% | translated |
| 5 | `GXClearVtxDesc_bl` | 0x802261ac | 18 | 18 | 28.9% | translated |
| 6 | `GXSetProjection_bl` | 0x8022bce8 | 18 | 16 | 32.5% | translated |
| 7 | `GXSetZMode_bl` | 0x8022a8b4 | 18 | 15 | 36.1% | translated |
| 8 | `GXEnableTexOffsets_bl` | 0x802277e4 | 16 | 2 | 39.2% | declared-nop |
| 9 | `GXLoadPosMtxImm_bl` | 0x8022be60 | 16 | 15 | 42.4% | translated |
| 10 | `GXSetChanCtrl_bl` | 0x80228898 | 16 | 14 | 45.6% | translated |
| 11 | `GXSetCurrentMtx_bl` | 0x8022bf00 | 15 | 15 | 48.6% | translated |
| 12 | `GXSetNumChans_bl` | 0x8022885c | 15 | 15 | 51.6% | translated |
| 13 | `GXSetNumTevStages_bl` | 0x8022a2e8 | 15 | 15 | 54.6% | translated |
| 14 | `GXSetNumTexGens_bl` | 0x80226d6c | 15 | 15 | 57.6% | translated |
| 15 | `GXSetCullMode_bl` | 0x8022782c | 14 | 14 | 60.4% | translated |
| 16 | `GXSetTevOp_bl` | 0x80229bac | 13 | 13 | 62.9% | translated |
| 17 | `GXSetTexCoordGen2_bl` | 0x80226aec | 9 | 8 | 64.7% | translated |
| 18 | `GXLoadTexObj_bl` | 0x80229108 | 9 | 8 | 66.5% | translated |
| 19 | `GXSetTevKColor_bl` | 0x80229e88 | 9 | 4 | 68.3% | translated |
| 20 | `GXLoadTexMtxImm_bl` | 0x8022bf34 | 8 | 8 | 69.9% | translated |
| 21 | `GXSetBlendMode_bl` | 0x8022a808 | 8 | 8 | 71.5% | translated |
| 22 | `GXInitTexObjLOD_bl` | 0x80228e08 | 8 | 6 | 73.1% | translated |
| 23 | `GXSetTevKColorSel_bl` | 0x80229efc | 7 | 4 | 74.5% | translated |
| 24 | `GXSetTevAlphaOp_bl` | 0x80229d28 | 7 | 4 | 75.9% | translated |
| 25 | `GXSetTevColorIn_bl` | 0x80229c38 | 7 | 4 | 77.3% | translated |
| 26 | `GXSetTevColorOp_bl` | 0x80229cc0 | 7 | 4 | 78.7% | translated |
| 27 | `GXInvalidateTexAll_bl` | 0x80229358 | 6 | 6 | 79.9% | declared-nop |
| 28 | `GXSetTevSwapMode_bl` | 0x80229fb4 | 5 | 2 | 80.9% | translated |
| 29 | `GXSetTevColor_bl` | 0x80229d90 | 5 | 3 | 81.9% | translated |
| 30 | `GXSetTevAlphaIn_bl` | 0x80229c7c | 5 | 2 | 82.9% | translated |
| 31 | `GXSetArray` | 0x80226a50 | 4 | 2 | 83.7% | translated |
| 32 | `GXSetAlphaUpdate_bl` | 0x8022a888 | 4 | 3 | 84.5% | translated |
| 33 | `GXSetColorUpdate_bl` | 0x8022a85c | 4 | 3 | 85.3% | translated |
| 34 | `GXSetTevSwapModeTable_bl` | 0x80229ffc | 3 | 1 | 85.9% | translated |
| 35 | `GXInitTexObj_bl` | 0x80228b74 | 3 | 2 | 86.5% | translated |
| 36 | `GXSetTevKAlphaSel_bl` | 0x80229f58 | 3 | 1 | 87.1% | translated |
| 37 | `GXLoadTlut_bl` | 0x80229194 | 3 | 3 | 87.6% | translated |
| 38 | `GXSetVtxAttrFmtv_bl` | 0x80226440 | 3 | 3 | 88.2% | — |
| 39 | `GXProject_bl` | 0x8022bb74 | 3 | 3 | 88.8% | translated |
| 40 | `GXSetCPUFifo_bl` | 0x80225378 | 3 | 2 | 89.4% | — |
| 41 | `GXSetGPFifo_bl` | 0x802254a0 | 3 | 2 | 90.0% | — |
| 42 | `__GXFlushTextureState_bl` | 0x80229b88 | 2 | 1 | 90.4% | declared-nop |
| 43 | `GXPixModeSync_bl` | 0x80227240 | 2 | 2 | 90.8% | declared-nop |
| 44 | `GXSetChanMatColor_bl` | 0x8022876c | 2 | 1 | 91.2% | translated |
| 45 | `GXSetFog_bl` | 0x8022a310 | 2 | 2 | 91.6% | — |
| 46 | `GXSetFogRangeAdj_bl` | 0x8022a6e4 | 2 | 2 | 92.0% | — |
| 47 | `GXInvalidateVtxCache_bl` | 0x80226adc | 2 | 2 | 92.4% | declared-nop |
| 48 | `GXSetAlphaCompare_bl` | 0x8022a07c | 2 | 2 | 92.8% | translated |
| 49 | `GXGetGPFifo_bl` | 0x8022588c | 2 | 2 | 93.2% | — |
| 50 | `GXGetProjectionv_bl` | 0x8022be18 | 2 | 1 | 93.6% | translated |
| 51 | `GXSetLineWidth_bl` | 0x80227764 | 2 | 2 | 94.0% | — |
| 52 | `GXSetPointSize_bl` | 0x802277a4 | 2 | 2 | 94.4% | — |
| 53 | `GXCopyTex_bl` | 0x80228188 | 2 | 2 | 94.8% | — |
| 54 | `GXInitTlutRegion_bl` | 0x80229320 | 2 | 1 | 95.2% | declared-nop |
| 55 | `GXSetTexCopyDst_bl` | 0x80227b14 | 2 | 2 | 95.6% | — |
| 56 | `GXSetTexCopySrc_bl` | 0x80227a64 | 2 | 1 | 96.0% | — |
| 57 | `GXInitLightColor_bl` | 0x802285f4 | 1 | 1 | 96.2% | translated |
| 58 | `GXInitLightPos_bl` | 0x802285c8 | 1 | 1 | 96.4% | translated |
| 59 | `GXLoadNrmMtxImm_bl` | 0x8022beb0 | 1 | 1 | 96.6% | translated |
| 60 | `GXLoadLightObjImm_bl` | 0x80228600 | 1 | 1 | 96.8% | translated |
| 61 | `GXInitLightDistAttn_bl` | 0x802284f8 | 1 | 1 | 97.0% | translated |
| 62 | `GXSetChanAmbColor_bl` | 0x8022867c | 1 | 1 | 97.2% | translated |
| 63 | `GXSetScissor_bl` | 0x8022c13c | 1 | 1 | 97.4% | latched |
| 64 | `GXGetViewportv_bl` | 0x8022c118 | 1 | 1 | 97.6% | translated |
| 65 | `GXInitLightSpot_bl` | 0x80228368 | 1 | 1 | 97.8% | translated |
| 66 | `GXInitTlutObj_bl` | 0x8022915c | 1 | 1 | 98.0% | translated |
| 67 | `GXSetCopyFilter_bl` | 0x80227e04 | 1 | 1 | 98.2% | — |
| 68 | `GXSetNumIndStages_bl` | 0x80229ae8 | 1 | 1 | 98.4% | — |
| 69 | `GXSetTevColorS10_bl` | 0x80229e0c | 1 | 1 | 98.6% | translated |
| 70 | `__GXFifoInit_bl` | 0x8022565c | 1 | 1 | 98.8% | — |
| 71 | `__GXInitGX_bl` | 0x80224824 | 1 | 1 | 99.0% | — |
| 72 | `__GXPEInit_bl` | 0x80227518 | 1 | 1 | 99.2% | — |
| 73 | `__GXSetIndirectMask_bl` | 0x80229b58 | 1 | 1 | 99.4% | — |
| 74 | `__GXSetTmemConfig_bl` | 0x802295e4 | 1 | 1 | 99.6% | — |
| 75 | `GXInitFifoBase_bl` | 0x80225290 | 1 | 1 | 99.8% | — |
| 76 | `GXSetMisc_bl` | 0x80226da8 | 1 | 1 | 100.0% | — |

### 2.2 Coverage

| tier | entry points | share of the 76 | ROM call sites covered | share of the 502 |
|---|---|---|---|---|
| `translated` (changes the frame) | 49 | 64.5% | 437 | **87.1%** |
| `+ latched` (accepted, not acted on) | 50 | 65.8% | 438 | 87.3% |
| `+ declared-nop` (correctly inert) | 56 | 73.7% | 468 | 93.2% |
| **not implemented — fails loudly** | **20** | **26.3%** | 34 | 6.8% |

The honest headline is the first row: **87.1% of the ROM's static GX call sites reach an
entry point that changes what is drawn**, up from 49.2%. The other rows are reported next
to it rather than merged into it, because collapsing them into one "implemented" figure is
exactly how a graphics seam talks itself into sounding finished.

**What that number is and is not.** It counts CALL SITES whose entry point does something,
not correctness. Every one of the 49 is still `evidenceClass: "synthetic"`; none has been
compared against a captured frame. A coverage figure of 87% next to a verification figure
of 0% is the accurate picture, and the two must always be quoted together. `latched`
collapsed to a single entry point (`GXSetScissor`) not because scissoring was implemented
but because everything else that was latched is now applied — the one remaining latch is
still a real gap and is still reported at draw time.

**Where the 38-point jump came from**, so it can be audited rather than taken on trust:

| source | entry points | call sites |
|---|---|---|
| TEV combiner newly translated (`GXSetTevColorIn/AlphaIn/ColorOp/AlphaOp/KColor/Color/ColorS10/KColorSel/KAlphaSel/SwapMode/SwapModeTable`, `GXSetAlphaCompare`) | 12 | 57 |
| previously `latched`, now applied (`GXSetTevOrder`, `GXSetTevOp`, `GXSetNumTevStages`, `GXSetNumTexGens`, `GXSetNumChans`, `GXInitTexObj`, `GXLoadTexObj`, `GXLoadTexMtxImm`, `GXLoadNrmMtxImm`) | 9 | 105 |
| texture pipeline newly translated (`GXInitTexObjLOD`, `GXInitTlutObj`, `GXLoadTlut`) | 3 | 12 |
| texgen (`GXSetTexCoordGen2`) | 1 | 9 |
| lighting (`GXInitLightColor/Pos/DistAttn/Spot`, `GXLoadLightObjImm`, `GXSetChanMatColor`, `GXSetChanAmbColor`) | 7 | 7 |
| `GXProject`, ported from the repo's own `gx_stubs.c` | 1 | 3 |
| newly `declared-nop` (`GXEnableTexOffsets` with offsets off, `GXInitTlutRegion`) | 2 | 18 |

---

## 3. The central finding: the ROM does not submit vertices by calling a function

This shaped every design decision in `packages/rom-runtime/src/gx/`, and it is the single
most important thing for the next agent to understand.

Gotcha Force's immediate-mode draw path is:

```c
gnt4_GXBegin_bl(0x80, 0, 4);            /* GX_QUADS, vtxfmt 0, 4 vertices */
DAT_cc008000._0_2_ = 0;                 /* 16-bit store: x */
DAT_cc008000._0_2_ = 0;                 /* 16-bit store: y */
DAT_cc008000       = uVar1;             /* 32-bit store: RGBA8            */
...                                     /* (zz_0027c34_, chunk_0003.c:3312) */
```

`DAT_cc008000` is the GameCube's memory-mapped **write-gather pipe**. The vertex
components are STORES, not calls. There are **1,143** such stores across the export, and
there is no `GXEnd` symbol at all — the SDK's `GXEnd` is an empty macro, so a primitive
ends when its vertex count is satisfied.

**Consequence: a host that intercepts only GX function calls sees `GXBegin` and never sees
a single vertex.** `packages/rom-runtime/src/gx/fifo.ts` is the answer — a byte-oriented
decoder that reassembles the pipe traffic into vertices per the latched VCD/VAT.

**Consequence — CLOSED, 2026-08-29.** `0xCC008000` is hardware MMIO, and the composed
module's linear memory is `0x807A0000` bytes. `0xCC008000` is past the end, so a literal
store there traps. Lowering `DAT_cc008000` stores to the `__gf_gx_wgpipe_*` imports this
decoder consumes was a required assembly-gate amendment, and **it now exists**:

* it lives in the OGhidra checkout, not in this repo —
  `research/tools/OGhidra/src/port_wgpipe_lowering.py` (`lower_source` / `lower_window`),
  driven by `port_assembly_gate.py`'s `_emit_wgpipe_lowering`;
* it is **opt-in and off by default**, behind `OGHIDRA_PORT_WGPIPE_LOWERING=1`;
* it rewrites only DERIVED sources, never the verbatim `unit.c`, and it **fails closed**:
  any surviving mention of the `0xCC008000..0xCC008020` window is a
  `wgpipe_unlowerable_site` refusal, so a lowered source has no un-lowered pipe stores in
  it by construction;
* floatness is decided by `_Generic` on the stored expression's static type in a
  gate-generated `gf_gx_wgpipe.h`, not by the rewriter reading the text — which matters,
  because a 32-bit store of a float and of an integer put different bytes on the wire for
  the same numeric value.

Its output for `zz_0027c34_` is committed at
`packages/rom-runtime/test/fixtures/gx-rom-unit/` and drives this decoder through the H2
bridge in the browser (§5.2). **A real ROM unit now submits geometry through this path.**

Display lists (`GXCallDisplayList`) are used at exactly one site — `gnt4_HSD_PObjDisp_bl`,
inside the HSD library, which is itself host-side. So the ROM↔host GX boundary is the
immediate-mode path, not the display-list path.

---

## 4. What was built

All under `packages/rom-runtime/src/gx/`.

| file | what it is |
|---|---|
| `inventory.generated.ts` | the measured ranked surface, generated by `scripts/gx-call-inventory.mjs`; the denominator of every coverage figure |
| `enums.ts` | the GX constants, each labelled `[CORPUS]` (observable in this game's decompiled SDK) or `[SDK]` (documented value, could not be settled from the corpus) |
| `state.ts` | the latched GX pipeline state — VCD, the 8 VAT slots, projection, matrix memory, raster state, texture and TLUT objects, the 16 TEV stages and their registers, the 8 texgens, the per-channel lighting configuration and the 8 light objects — plus the per-draw snapshot |
| `fifo.ts` | the write-gather-pipe decoder and vertex assembly (§3) |
| `tev.ts` | **the TEV combiner**: stage state, the `GXSetTevOp` expansion, and the fragment-shader generator (§4.4) |
| `texture.ts` | **GameCube texture decoding** out of the arena into RGBA8 (§4.5) |
| `backend.ts` | the `GxBackend` interface and the headless recording backend the decode-side assertions run against |
| `webgl.ts` | the WebGL2 rasterizer: the generated-program cache, texture upload, the texgen/lighting vertex-shader generator, and the `diagnostics` list where every approximation names itself |
| `adapters.ts` | the entry points as bridged-callee host adapters, plus the loud-unimplemented handler |
| `selftest/gxSelftestMain.ts` | the end-to-end browser proof (§5) |

`gx/index.ts` is deliberately **not** re-exported from `packages/rom-runtime/src/index.ts`.
Re-exporting it made the measured call inventory reachable from the game's entry graph, so
rollup kept the table in `apps/game`'s production bundle even though nothing in the game
references it. Import the GX host directly instead.

### 4.1 Provenance discipline in `enums.ts`

The enum values are split by authority, because a wrong one produces a wrong frame rather
than a failure. Settled **from this game's decompiled SDK**: the attribute ids, the
`NONE/DIRECT/INDEX8/INDEX16` descriptor types, the component counts, all six colour
component types, four of the seven primitive types, the cull modes, the blend *modes*, the
projection discriminator, the texmap range and its `0xff`/`0x100` sentinels, the channel
ids, the colour-source values, and the matrix-memory row arithmetic. **Not settled**, and
labelled as such: the depth compare-function numbering (the ROM only ever uses 3 and 7),
the blend *factor* numbering (the field is only masked with 7, and the remaining sets come
from an unreadable table at `DAT_802d2d44`), primitive bytes `0xa8`/`0xb8` (absent from the
export), and whether `0xb0` is a line strip or a line loop.

**Newly settled on 2026-08-30, from the decompiled SDK bodies in `chunk_0067.c`.** These
bodies pack their arguments straight into hardware BP/XF registers, so they expose field
widths, field positions and argument orders directly:

* **`GXTexFmt` — the whole enum, settled.** `gnt4_GXInitTexObj_bl` @0x80228b74 switches on
  the format and writes both a texel-block shift pair and a bytes-per-texel class per
  case. Block geometry plus bit depth identifies every GameCube format uniquely:
  8x8/4-bit → `I4`(0) and `C4`(8); 8x4/8-bit → `I8`(1), `IA4`(2), `C8`(9); 4x4/16-bit →
  `IA8`(3), `RGB565`(4), `RGB5A3`(5), `C14X2`(0xa); 4x4/32-bit → `RGBA8`(6); 8x8/compressed
  → `CMPR`(0xe). `gnt4_GXSetZTexture_bl` independently pins `Z8`=0x11, `Z16`=0x13,
  `Z24X8`=0x16 by their bit depths.
* **`GXTexGenSrc` and `GXTexGenType` — settled.** Read out of
  `gnt4_GXSetTexCoordGen2_bl`'s source switch, which maps the caller's value to the
  hardware's input row, and out of its function dispatch (`func == 0` sets the
  three-component projection bit, `func - 2` indexes the bump light field, `func == 10`
  takes the colour path). The bump branch's `src - 0xc` pins `GX_TG_TEXCOORD0` at 0xc.
* **`GXAttnFn` — settled.** `gnt4_GXSetChanCtrl_bl` derives an enable bit and a select bit
  from one argument and opens with `if (attn_fn == 0) diff_fn = 0`. Only `SPEC`=0,
  `SPOT`=1, `NONE`=2 satisfies all three.
* **`GXTevOp` — ADD=0/SUB=1 and the compare-op ENCODING, settled.**
  `gnt4_GXSetTevColorOp_bl` branches on `op < 2` and, above it, forces the bias field to 3
  and routes `op & 6` into the scale field. Which comparison width each value names is
  still [SDK].
* **Field widths and argument orders, all settled**: TEV colour selectors are 4-bit and
  alpha selectors 3-bit, both in `(stage, a, b, c, d)` order with `a` in the high field;
  `GXSetTevColorOp` is `(stage, op, bias, scale, clamp, out_reg)`; `GXSetTevOrder` is
  `(stage, coord, map, color)` — the coord and map arguments cannot be confused because
  the body strips `0x100` from one and range-tests the other; `GXSetAlphaCompare` is
  `(comp0, ref0, op, comp1, ref1)`; konst selectors are 5-bit and swap-table entries
  2-bit; `GXSetTevOp`'s mode space is exactly 5 wide (the two table pairs are 5 entries
  apart) and its stage-0-vs-later branch is the RASC/CPREV rule.
* **The `GXLightObj` layout — settled.** `gnt4_GXLoadLightObjImm_bl` streams offsets 0x0c
  through 0x3c to XF, and the `GXInitLight*` helpers write colour at 0x0c, angle
  attenuation at 0x10/0x14/0x18, distance attenuation at 0x1c/0x20/0x24, position at
  0x28/0x2c/0x30 and the NEGATED direction at 0x34/0x38/0x3c. The light id is a BITMASK:
  the body derives its XF slot as `31 - clz(id)`.
* **`GXSetChanMatColor`/`GXSetChanAmbColor`/`GXSetTevKColor`/`GXInitLightColor` take a
  POINTER**, which the previous revision called "genuinely ambiguous". The bodies issue
  separate byte loads from a base register and the ROM's call sites pass `&local`; Ghidra
  derives both sides from the actual instructions, so that is what the shipped code does.

**Still [SDK], and still labelled**: the meaning of each TEV selector VALUE (corroborated
but not proved — the ROM's own 4-stage program pairs `ColorIn(0,0xf,8,0xe,2)` with
`AlphaIn(0,7,4,6,1)`, i.e. ZERO/TEXC/KONST/C0 against ZERO/TEXA/KONST/A0 across two enums
of *different* widths, which is a strong coincidence but not evidence); the combiner
EQUATION itself (nothing in this corpus computes it — the silicon does); the three
`GXTevMode` tuples other than MODULATE and PASSCLR (their table contents live at
`DAT_803aad30`/`DAT_803aad58`, not in the C export); every texel BIT LAYOUT in
`texture.ts`; the wrap and filter mode numberings; and the illumination model in the
generated vertex shader.

### 4.2 Two byte orders, both deliberate

This bit the implementation once and is worth stating plainly:

* **The arena is LITTLE-endian.** It is byte-swapped to wasm-native order when it is built
  from the DOL. Verified rather than assumed: `apps/game/public/rom/arena.json` stores the
  `1.0f` constant at `0x80436f78` as `00 00 80 3f`. Matrix and indexed-array reads use it.
* **The FIFO stream is BIG-endian.** It is register-order data that never lived in memory,
  so it keeps the console's order. Corroborated by the display-list interpreter's
  `DAT_cc008000._0_2_ = CONCAT11(hi, lo)` INDEX16 write.

**The corner the previous revision left open (its §7.4) is now ANSWERED**, and the answer
is that the question had a false premise. There is no global "the arena is swapped" rule
to discover. `research/decomp/poc/wasm-port-poc/gen_arena.py` converts **per region, by
declared type**, and says so in its own docstring: `swap4` for u32/f32 regions, `swap2`
for s16 tables, `raw` — no swap at all — for byte tables, plus per-symbol typed pokes for
the mixed-width scalar constants. It already emits at least one region (`DAT_802cffc8`,
the unit-B char table) with `raw`.

So:

* a DOL-derived **byte-typed** region — which is what a texture image and an RGBA8 colour
  array are — is in **console byte order** in the arena and needs no compensation. The
  indexed colour fetch in `fifo.ts` and the texture decoder in `texture.ts` both read it
  as bytes, which is correct;
* a **4-byte-typed** region is swapped, which is what makes `mem.readF32` correct for
  matrices;
* the residual risk is not a decoder bug but an AUTHORING one: a texture or colour region
  emitted into the arena under the wrong type category would be scrambled. That is a
  property of the arena manifest, not of this host, and it fails loudly here — a
  mis-swapped texture does not decode to a plausible image, it decodes to noise.

The one case that still needs care is a ported unit that composes a colour as a single
`u32` store into its own wasm memory: that lands in wasm little-endian order, not console
order. The self-test fixture writes its colour array as explicit bytes for exactly this
reason, with the reasoning recorded at the definition site.

### 4.3 Loudness

Every one of the 76 measured entry points has an adapter. The **20** that are not
implemented get one that **throws**, naming the symbol, its ROM address, its static
call-site count and its number of distinct callers. That surfaces as a declared servicing
error in the bridged-call ledger and fails the frame. There is no silent no-op anywhere in
the surface: a silent no-op in a graphics seam produces a frame that renders and is wrong,
which is strictly worse than a frame that fails.

The **six** `declared-nop` entry points are the one legitimate exception, and each has a
stated reason rather than an absence of one: cache invalidation and pipe synchronization
genuinely have no host-visible effect; `GXInitTlutRegion` allocates inside texture memory,
which this host does not model at all (it keeps palettes as objects and binds them by TLUT
name); and `GXEnableTexOffsets` is a **conditional** nop — it is inert only because all 16
ROM call sites pass both sprite offset generators DISABLED, and the adapter **throws** if
either is ever enabled. They are tiered separately so they can never be confused with the
other two categories.

Two more refusals are worth naming because they cost coverage on purpose:
`GXSetVtxAttrFmtv` stays unimplemented because its `GXVtxAttrFmtList` struct layout could
not be confirmed, and `tevStageFromOp` throws on a `GXSetTevOp` mode outside 0..4 rather
than inventing a sixth combiner program the corpus proves cannot exist.

The WebGL backend adds a second loudness channel for things a *call-level* check cannot
catch. It now reports, per draw: per-vertex position matrices it did not apply; a TEV
stage that selects a texmap with no texture bound, or with a texture that failed to
decode, naming the format and the address; a texgen whose source, function, post-matrix or
normalize flag it did not honour; a texgen naming a texture-matrix row that was never
loaded; a lighting channel enabled on a draw with no normals; a scissor it did not clip
to; a mipmapped texture of which only the base level was uploaded; a konst selector
outside the documented range; a bias field of 3 on a non-compare op; a logic-op blend it
could not express; and any primitive it could not draw. Every one of these names the
specific stage or generator, not just the category.

### 4.4 The TEV combiner is a SHADER GENERATOR, not more adapters

`tev.ts`. The Flipper's fragment stage is a chain of up to 16 stages, each computing

```
out = (d  (+/-)  ((1 - c) * a + c * b)  +  bias) * scale
```

over four selectable inputs, with per-stage konstant selection, per-stage channel and
texture swap tables, four shared colour registers that stages read and write, and an
alternative compare mode. There is no fixed-function GL state that encodes a programmable
combiner, so the only faithful translation is to GENERATE the fragment shader from the
latched state. `generateTevShader` does that; `webgl.ts` caches programs by generated
source, so a ROM that keeps re-programming the same combiner links once.

Details worth knowing before touching it:

* **The reset stage is `GXSetTevOp(stage, GX_PASSCLR)`** — the rasterized colour passed
  straight through. That is deliberately the least flattering safe default available: it
  reproduces exactly what this host drew *before* the combiner existed, so an unprogrammed
  draw cannot change appearance merely because the TEV landed. It is not a claim about
  what `GXInit` leaves behind, which the corpus does not show.
* **Clamp semantics are approximated and say so.** A clamping stage clamps to `[0,1]`. A
  non-clamping stage keeps the value in the signed 10-bit register range, approximated as
  `[-4, 4]`. GX computes in fixed point with per-stage rounding; this is float.
* **`GXSetTevColorS10` is stored unclamped**, because the entire point of the S10 form is
  values outside `[0,255]` and clamping at latch time would discard what the ROM asked for.
* **Alpha compare is a `discard`**, generated only when it is not the always-pass pair;
  the ROM's own two call sites pass `(ALWAYS, 0, AND, ALWAYS, 0)`, which generates nothing.
* **The RGB8 compare op is per-channel** (`mix` over a `bvec3`), not a scalar branch,
  because that is what the hardware does.

### 4.5 Texture decoding is NEW CODE, and here is why

`texture.ts` decodes I4, I8, IA4, IA8, RGB565, RGB5A3, RGBA8, C4, C8, C14X2 and CMPR out
of the arena into RGBA8, block de-tiling included.

The brief for this work asked that the project's existing GameCube texture decoding be
reused rather than duplicated. **There was none to reuse**, and that is worth recording so
the next agent does not go looking again:

* `packages/formats/src/tpl.ts` stops at container metadata on purpose — its own header
  says "Pixel decode still belongs to offline tooling until the runtime needs RGBA". It
  gives width/height/format/dataOffset and a `paletteHeaderOffset` it never follows.
* The only pixel decoder in the repo is a C# `Program.cs` that `scripts/export-ui-assets.mjs`
  writes out at build time and which calls HSDRaw's `GXImageConverter` — and
  `tools/HSDLib`, the project it references, is not present in this worktree.
* `apps/game` consumes the RESULTS of that offline pass as PNGs; the browser never sees
  GameCube-format bytes.
* `scripts/inspect-particle-effects.mjs` carries an explicit TODO asking for exactly this
  decoder.

So the runtime now needs RGBA and this is the first TypeScript implementation. It lives in
`packages/rom-runtime` rather than `@gf/formats` because it decodes raw format bytes at a
GC address rather than a TPL container, and adding a workspace dependency for one consumer
would have been the larger change. If a second consumer appears, this module is the thing
to lift into `@gf/formats` alongside `tpl.ts`.

The block geometry is corpus-settled (§4.1). The bit layout inside a texel is `[SDK]` and
labelled at each function. `decodeTextureBytes` **throws** on a format it cannot size or a
region it cannot read, rather than substituting a plausible image.

---

## 5. The end-to-end proof

`scripts/smoke-gx-host-phase.mjs`, opt-in with `GF_SMOKE_GX_HOST=1`, appended to
`scripts/smoke-browser-game.mjs` as a single self-contained import block at the end of the
file. It owns its own bundle, server, browser and CDP session, exactly like
`scripts/smoke-rom-runtime-phase.mjs`.

The phase has TWO legs now. The second one is the one that changed.

### 5.1 Leg one — ROM-shaped call sequences, hand-written

A purpose-built ROM-side wasm draw module
(`packages/rom-runtime/test/fixtures/gx-selftest/`, compiled with the repo's pinned emsdk,
binary committed). Its first three draw functions reproduce — call for call and store for
store — three of the ROM's own immediate-mode draw paths; the rest exercise the surface
this revision added:

| fixture export | what it proves | expected pixel |
|---|---|---|
| `gx_draw_fullscreen_quad` | `zz_0027c34_` (chunk_0003.c:3285-3328): `GX_QUADS`, POS DIRECT S16 XY + CLR0 DIRECT RGBA8 | the quad's blue at the corner |
| `gx_draw_strip` | `zz_0050f80_` (chunk_0006.c:4865-4924): `GX_TRIANGLESTRIP`, POS DIRECT F32 XYZ | the strip's green at the centre |
| `gx_draw_indexed` | `zz_0050bf4_` (chunk_0006.c:4760-4797): primitive `0xb0`, POS + CLR0 INDEX8 through `GXSetArray` | positions and colours resolved from the arena |
| `gx_draw_tev_konst` | a stage whose only colour input is `GX_CC_KONST` | **exactly `GX_KCOLOR0`** — and explicitly NOT the (different) vertex colour |
| `gx_draw_tev_two_stage` | stage 0 writes `GX_TEVREG0`, stage 1 reads it back as `GX_CC_C0` | exactly `GX_KCOLOR1`, which only a real register chain produces |
| `gx_draw_alpha_compare_discard` | `GXSetAlphaCompare(GX_GREATER, 0x80, ...)` against a failing alpha | the cleared background survives — the fragment is DISCARDED, not merely latched |
| `gx_draw_textured` | a 4x4 `GX_TF_RGBA8` block built in module memory, read back through `GXInitTexObj`'s address, de-tiled, uploaded, sampled through `GXSetTexCoordGen2` and `GX_MODULATE` | exactly the texel colour, including the G and B bytes that live in the block's SECOND 32-byte half |
| `gx_draw_lit` | one light object, `GXSetChanCtrl` with lighting on, `GX_DF_CLAMP`, white material, black ambient | exactly the light's own colour |
| `gx_program_rom_tev` | the ROM's OWN four-stage program, transcribed from chunk_0003.c:5670-5720 — per-stage konstants, per-stage swap modes, a three-row swap table | state assertions: stage 0's `(0xf, 8, 0xe, 2)` colour inputs and mirrored `(7, 4, 6, 1)` alpha inputs, stage 1's `GX_CS_SCALE_2`, stage 2's `K2`/`K2_A`/swap row 2, swap table rows `(0,3,3,3)` and `(0,0,3,0)` |
| `gx_call_tex_offsets_disabled` | `GXEnableTexOffsets(n, 0, 0)` x8, as all 16 ROM call sites pass it | inert, and the adapter still throws if an offset is ever enabled |
| `gx_call_unimplemented` | `GXSetFog`, which the host does not implement | `ADAPTER_THREW`, named in the ledger |

Every predicted-pixel draw deliberately sets the vertex colour to something OTHER than the
expected output, so a combiner that silently fell back to passing the rasterized colour
through fails rather than passing by accident.

### 5.2 Leg two — the GATE-LOWERED REAL ROM UNIT

This is what the previous revision listed as the open browser gap: "the browser leg still
runs a purpose-built fixture rather than a gate-lowered ROM unit."

`packages/rom-runtime/test/fixtures/gx-rom-unit/` holds the **assembly gate's own output**
for the ROM's own draw function `zz_0027c34_` (0x80027c34): the verbatim Ghidra
decompilation with exactly one class of rewrite applied — each `DAT_cc008000 = ...` store
turned into a `GF_WGPIPE_W16`/`GF_WGPIPE_W32` macro that the gate-generated
`gf_gx_wgpipe.h` routes to the `__gf_gx_wgpipe_*` imports. Every GX call, every constant
and every branch in it is the ROM's. The only hand-written file in that directory is
`gnt4_gx_decls.h`, which adds prototypes and nothing else — needed because the gate's
merged shim carries data symbols only, and because an implicitly declared callee would
link as returning `i32` while every host adapter declares `VOID`, which the
signature-accurate trampolines would rightly reject.

It is relinked rather than shipped as the gate's own binary because the gate links for the
node proof, which exports its memory, while the browser runtime needs the threads shape —
a shared, IMPORTED `env.memory`. The memory size is **not** a tuning knob: 0x807A0000
bytes / 32890 pages is the gate's production arena, and it has to be, because the shim
maps GameCube addresses straight to linear-memory offsets and this function reads
0x80433930, 0x80436108, 0x8043610c and 0x803c0f40.
`apps/game/public/rom/composed-rung0.threads.wasm` already imports a shared memory of
exactly that size and runs in the browser smoke route, so this is not a new demand.

The page gives it its own worker, its own memory and its own `GxHost`, pokes the four
arena locations the function reads, and invokes `zz_0027c34_`. It renders into the SAME
WebGL backend the fixture leg just used.

**The pixel assertion is the blended value, not the colour word**, and that is deliberate:
`zz_0027c34_`'s own second call is `GXSetBlendMode(1, 4, 5, 0)` — `GX_BM_BLEND` with
`SRCALPHA`/`INVSRCALPHA` — over a cleared frame, so the framebuffer must hold
`colour * alpha`. A host that ignored `GXSetBlendMode` would produce the brighter raw
colour and fail. (This caught a wrong expectation during development: the host was right
and the test was wrong.)

**Measured result (2026-08-30, headless Chrome + SwiftShader):**

```
GX HLE-host phase PASS (seam only, NO behavioural claim):
{"checks":74,"bridgedCalls":336,"primitives":8,"droppedFifoBytes":0,
 "unimplementedHits":["gnt4_GXSetFog_bl"],
 "gateLoweredRomUnit":{"primitives":1,"droppedFifoBytes":0,"gxCalls":18},
 "coverage":{"translated":"49/76 entry points, 87.1% of ROM call sites",
             "translatedAndLatched":"50/76 entry points, 87.3% of ROM call sites"},
 "verified":false,"evidence":".tmp/gx-host-smoke/evidence"}
```

74 in-page checks, all passing (up from 32), across 336 GX crossings in the bridged-call
ledger and 8 primitives with **zero dropped FIFO bytes** and none left buffered.

**Evidence.** `.tmp/gx-host-smoke/evidence/` holds `gx-framebuffer-fixture.png` (the
fixture frame), `gx-framebuffer-rom-unit.png` (**the frame the gate-lowered ROM function
produced**), `gx-framebuffer.png` (the canvas as the run ended), `gx-selftest.png` (the
full page with the 74-row results table), `console.log`, and `gx-selftest-results.json`
(checks + ledger + adapter roster).

**What the smoke phase additionally refuses.** It fails if any GX adapter reports
`evidenceClass: "verified"`; it fails if the page's payload or the adapter roster stops
stating that it carries no behavioural claim; and it now also fails if the gate-lowered
ROM unit leg did not run, did not produce exactly one primitive, dropped a FIFO byte, or
stopped disclaiming. A green run that quietly skipped the real-ROM leg would be exactly
the kind of false progress this phase exists to prevent.

**What a green run means and does not mean.** It means the seam works and the pipeline is
wired: the ROM's own gate-lowered code, and ROM-shaped call sequences, reach the adapters,
decode correctly, program a generated shader, sample a decoded texture, and rasterize to
pixels the page predicted from the GX semantics. It means **nothing** about whether these
frames match the GameCube. Every predicted pixel was predicted from the same understanding
of GX that produced the implementation, so these are self-consistency checks, not
comparisons — see §1 and §6.3.

---

## 6. What is NOT implemented

### 6.1 Entry points (20 of 76, 6.8% of static call sites)

The full ranked list, since it is short enough to give in full rather than summarise.
`#` is the rank in §2.1.

| # | entry point | sites | callers | what it would unlock |
|---|---|---|---|---|
| 38 | `GXSetVtxAttrFmtv` | 3 | 3 | batched attribute-format setup. **Deliberately refused**: its `GXVtxAttrFmtList` struct layout could not be confirmed from the corpus, and guessing a struct layout in a decoder that then mis-sizes the FIFO is the exact failure mode §3 exists to avoid |
| 40 | `GXSetCPUFifo` | 3 | 2 | FIFO plumbing |
| 41 | `GXSetGPFifo` | 3 | 2 | FIFO plumbing |
| 45 | `GXSetFog` | 2 | 2 | fog |
| 46 | `GXSetFogRangeAdj` | 2 | 2 | fog |
| 49 | `GXGetGPFifo` | 2 | 2 | FIFO plumbing |
| 51 | `GXSetLineWidth` | 2 | 2 | line width |
| 52 | `GXSetPointSize` | 2 | 2 | point size |
| 53 | `GXCopyTex` | 2 | 2 | **EFB — render to texture** |
| 55 | `GXSetTexCopyDst` | 2 | 2 | **EFB** |
| 56 | `GXSetTexCopySrc` | 2 | 1 | **EFB** |
| 67 | `GXSetCopyFilter` | 1 | 1 | **EFB** |
| 68 | `GXSetNumIndStages` | 1 | 1 | indirect texturing |
| 70 | `__GXFifoInit` | 1 | 1 | boot plumbing |
| 71 | `__GXInitGX` | 1 | 1 | boot plumbing |
| 72 | `__GXPEInit` | 1 | 1 | boot plumbing |
| 73 | `__GXSetIndirectMask` | 1 | 1 | indirect texturing |
| 74 | `__GXSetTmemConfig` | 1 | 1 | texture memory layout |
| 75 | `GXInitFifoBase` | 1 | 1 | boot plumbing |
| 76 | `GXSetMisc` | 1 | 1 | miscellaneous mode bits |

Three real groups remain, and one of them matters more than its call count suggests:

* **EFB / render-to-texture** (`GXCopyTex`, `GXSetTexCopySrc/Dst`, `GXSetCopyFilter` — 7
  sites). Only 1.4% of call sites, but it is a whole missing MECHANISM: without it, any
  effect the game builds by copying the framebuffer into a texture is absent, not
  approximated. This is the highest-value remaining block.
* **Fog** (`GXSetFog`, `GXSetFogRangeAdj` — 4 sites). Cheap; it is a per-fragment blend
  toward a colour by a depth curve, and the state is fully readable from the corpus body.
* **FIFO / boot plumbing** (9 entry points, 12 sites). An HLE host that submits
  immediately will probably declare most of these inert, but only after DECIDING so per
  entry point, the way `GXInitTlutRegion` and `GXEnableTexOffsets` were decided. They are
  loud until then.

Note `GXSetTevDirect`/`GXSetTevIndirect` do not appear here: they are not in the measured
inventory, because ROM game code never calls them.

### 6.2 Rendering features still missing or approximated

Was, and now is:

| | before | now |
|---|---|---|
| TEV combiner | not translated; the shader was `vertexColor * materialColor` | **generated per configuration**, up to 16 stages, konstants, registers, swap tables, compare ops, alpha test |
| texture sampling | nothing decoded, nothing uploaded | **11 GameCube formats decoded from the arena and sampled**, palettes included |
| texgen | matrices stored, never applied | **evaluated in the generated vertex shader** for the matrix functions |
| lighting | not evaluated | **evaluated per vertex** for channels 0/1: ambient, per-light diffuse and attenuation |

Still missing or approximated, and each one is reported at draw time rather than silently
tolerated:

* **No EFB model.** No copy, no framebuffer formats, no depth-buffer readback.
* **No indirect texturing.** `GXSetNumIndStages`/`__GXSetIndirectMask` are loud; the
  generated shader has no indirect stage.
* **No fog.**
* **No per-vertex position matrices.** `GX_VA_PNMTXIDX` is decoded but every vertex uses
  the `GXSetCurrentMtx` matrix, so skinned geometry would be wrong. Reported per draw.
* **No scissor.** Latched, not applied. Reported per draw when it is non-trivial.
* **No mipmaps.** Only the base level is decoded and uploaded; LOD, bias and anisotropy
  from `GXInitTexObjLOD` are dropped and both filters collapse to the non-mipmapped pair.
* **Bump and SRTG texgen functions** fall back to the matrix path, reported per generator.
* **Post-transform texture matrices** are not applied; the identity is used, reported.
* **Only TEX0 is assembled by the FIFO decoder**, so a texgen sourcing TEX1..TEX7 reads
  TEX0's coordinates and says so.
* **Paletted textures bind the most recently loaded TLUT.** The SDK names a palette through
  `GXInitTexObjCI`, which this game never calls, so the binding is a GUESS and is reported.
* **No batching.** One draw call per GX primitive; one program link per distinct
  configuration (cached).
* **Depth remap.** GX clips z to `[-1, 0]`; the projection's third row is rewritten as
  `2*row2 + row3` to reach GL's `[-1, 1]`. Visible ordering is preserved; depth precision
  distribution is not the console's.
* **Quad expansion.** GL has no quads, so each is split into two triangles on a fixed
  diagonal. Exact for planar convex quads; a non-planar quad rasterizes differently than
  Flipper's own split.
* **TEV arithmetic is float, not fixed point.** GX combines in a signed 10-bit space with
  per-stage rounding. Even a structurally exact combiner is not bit-exact.

### 6.3 Verification — no longer zero, and here is exactly how much it is

**This section previously read "still zero, and now the dominant gap". That is no longer
true, and the temptation to over-read the change is why the numbers below are given as
four separate rows that must never be collapsed into one percentage.**

Two console-derived standards now exist. Both capture from the real game in the bundled
Dolphin through the existing `research/tools/dolphin-trace/` machinery — `capture_gx.py`
imports `capture_common.py` and `capture_oracle.py` unchanged.

| what is compared against the console | before | now |
|---|---|---|
| GX adapters at `evidenceClass: "verified"` | 0 / 56 | **0 / 56** |
| entry points whose SEAM EMISSION is console-compared | 0 / 76 | **16 / 76 (21.1%)** |
| ROM draw functions whose RASTERIZED RESULT is console-compared | 0 | **1 of the 1 that is ported** |
| console pixels compared against a host prediction | 0 | **286,720 (860,160 channel samples)** |

The first row has not moved and is the one to quote when someone asks whether the host is
verified. Nothing below promotes a single adapter: an adapter is `"verified"` only when
**its own** behaviour has been checked, and neither standard does that for any individual
entry point. The smoke phase still fails if any adapter claims otherwise.

#### 6.3.1 `gx_callstream_green` — the seam, verified against the console

`research/decomp/oracle-harness/run-gx-callstream.mjs`, artifact
`research/decomp/data/oracle-results/gx-rom-unit.zz_0027c34_.gx-callstream.json`.

`capture_gx.py capture` breakpoints the ROM function's entry, its `blr`, every `bl` site
and every store site, and records ONE ORDERED STREAM per invocation: each GX call with its
arguments read out of the PowerPC EABI registers, and each store whose RESOLVED effective
address lands in the write-gather-pipe window, with its width and value. That interleaving
is the shape none of the other three capture tools can see — a pipe store is neither a call
nor a MEM1 write — which is why this is a fourth tool rather than a flag on an existing one.

The harness then runs **the assembly gate's own wasm build of the same ROM function**
against the real GX adapters, seeded with the console's own memory at the addresses the
plan declares, and requires the stream the host receives to be identical.

**Measured 2026-08-31** on `zz_0027c34_` (0x80027c34), from a live 2v2 battle savestate:

```
GX CALLSTREAM TOTAL invocations=4/4 events=124/124 DIVERGENCE: none VERDICT: GX_CALLSTREAM_GREEN
```

4 invocations, **76 GX/SDK calls and 48 write-gather-pipe writes (128 bytes)**, every
event identical in kind, order, arity and value; 336 bytes of console memory seeded. The
19 ROM call sites bind to 17 distinct callees by first-use order, and 16 of those bindings
were **cross-checked against the measured GX inventory's own ROM addresses** before the
capture ran.

The console's own vertex byte stream was additionally pushed through the host's FIFO
decoder — the first time that decoder has been fed bytes it did not also generate. It
consumed all 32 bytes with **0 dropped and 0 pending** and assembled `GX_QUADS`, 4
vertices, at (0,0) (640,0) (640,448) (0,448), colour `00 00 00 07`, with no diagnostics.

**What this verifies**: the write-gather-pipe LOWERING (which store became which
`__gf_gx_wgpipe_*` import, at which width, in which order, carrying which value), the GX
call sequence and its ARGUMENT MARSHALLING, the guard the ROM function evaluates, and the
GameCube-address-to-linear-memory mapping for every static pointer it passes.
**What it does not**: any pixel, and the MEANING of any argument — a 7 is compared as the
number 7, not as a depth-compare function.

One honesty note, carried in the artifact rather than only here: the capture STAGED one
word of game state (`DAT_80436108 = 1`, the ROM's own fade-active flag) at the function's
entry, because the sampled battle state never opens that guard. Every instruction
executed, every call and every pipe byte is the ROM's; the guard's value was not.
`source.state_staging` records it and the harness surfaces it in `does_not_verify`.

#### 6.3.2 `gx_framebuffer_equivalent` — real console pixels, at a declared tolerance

`research/decomp/oracle-harness/run-gx-framebuffer.mjs`, artifact
`research/decomp/data/oracle-results/gx-rom-unit.zz_0027c34_.gx-framebuffer.json`.

A whole-frame comparison is **structurally unreachable**, and the reason is porting
progress rather than tooling: this host renders the output of ONE ROM function while a
console frame is the output of the whole game, so there is no host frame to put beside it.
What is reachable is a DIFFERENTIAL: two console frames from the same savestate at the
same frame index, differing only in whether the ROM's own draw path ran. Their difference
is exactly what Flipper did with the call stream captured above, and the host predicts that
difference from its OWN decoded geometry, its OWN decoded vertex colour and its OWN reading
of the blend enums.

**Measured 2026-08-31** (`--tolerance 4`, declared before the numbers were read and not
moved afterwards):

| | |
|---|---|
| host-predicted touched region, from its decoded vertices | `x [0,640) y [0,448)` |
| region the console actually changed | `x [0,640) y [0,448)` — **exact match** |
| console pixels changed OUTSIDE the host's prediction | **0** |
| per-channel abs delta (8-bit RGB): mean / p50 / p95 / p99 / max | **0.78 / 1 / 2 / 3 / 7** |
| channel samples within 4/255 | **99.80 %** |
| attenuation fitted from the console frames (median, p05–p95) | **0.9706** (0.9604–0.9767) |
| attenuation the host predicts from its blend reading | **0.9725** = 248/255 |

**This settles an `[SDK]` item.** `GXSetBlendMode`'s factor numbering is labelled
"[SDK] — NOT settled from the corpus" in `enums.ts`. The ROM's call is
`GXSetBlendMode(1, 4, 5, 0)` and its vertex colour is `00 00 00 07`. Reading factor 5 as
`INVSRCALPHA` predicts the frame is scaled by 248/255; reading it as `SRCALPHA` predicts a
scale of 7/255, i.e. an almost black frame. The console scaled by 0.9706. The measurement
therefore **discriminates decisively** between the candidate readings and is consistent
only with `4 = SRCALPHA`, `5 = INVSRCALPHA`, `mode 1 = BLEND`. It does **not** settle the
hardware's exact rounding divisor: the fitted 0.9706 sits between 248/255 (0.97255) and
248/256 (0.96875), and the residual p99 of 3/255 is the size of that ambiguity.

Note what the region match is worth on its own. The host derived `x [0,640) y [0,448)`
from the console's own vertex bytes, through its FIFO decoder, and the console painted
exactly that rectangle of a 640x480 XFB and nothing else — 0 pixels changed outside it.
That is the rasterized-coverage comparison, on a real frame.

**Ceiling, unchanged and not raised by any of this**: "framebuffer-equivalent, never
pixel-identical". A p99 of 3/255 over one alpha-blended untextured quad says nothing about
a textured, TEV-programmed, depth-interacting draw, and this measurement creates no GL
context at all — the prediction is evaluated from latched state and the decoded primitive,
so shader generation, texture sampling and depth handling are untouched by it.

#### 6.3.3 Both harnesses are proven able to FAIL

`research/decomp/oracle-harness/tests/gx-callstream-harness.test.mjs`, 16 tests, run by
`pnpm test:oracle`. It drives both harnesses against the committed console captures and
against mutants of them — wrong argument value, wrong pipe VALUE, wrong pipe WIDTH, wrong
call order, an extra event, a stack pointer replaced by a static address, a wrong
blend-factor reading, a wrong decoded quad extent — plus the non-vacuity guards: a capture
whose guard never opened cannot pass, an empty capture cannot pass, header counts that
drift from the records cannot pass, two identical console frames cannot pass, and frames
from different frame indices are refused outright.

#### 6.3.4 What is still self-validated

Everything not named above, which is most of the host: the TEV shader generator, texture
decoding and sampling, texgen, lighting, the depth remap, quad expansion, and every
approximation in §6.2. §5's predicted pixels are still predicted from the same
understanding that wrote the implementation. The circularity is broken **at one seam and
for one draw**, not in general.

### 6.4 The runtime call surface — measured, and it inverts the static ranking

§2's ranking is by STATIC call sites, and §2 says a per-frame frequency ranking "requires a
Dolphin trace and does not exist". It exists now:
`research/decomp/data/gx-surface/battle-2v2.*.gx-surface.json`, produced by
`capture_gx.py surface`, which breakpoints a chosen set of GX entry points in the live game
and records both counts and the DISTINCT ARGUMENT TUPLES the ROM passes.

**The headline is a defect, not a statistic.** Over 32.2 s of a live 2v2 battle the ROM
made **507 calls to entry points this host does not implement** — every one of which the
loud-unimplemented adapter would throw on, failing the frame:

| entry point | calls in 32.2 s | §2.1 rank | static sites |
|---|---:|---:|---:|
| `GXSetFog` | 220 | 45 | 2 |
| `GXSetFogRangeAdj` | 130 | 46 | 2 |
| `GXSetLineWidth` | 69 | 51 | 2 |
| `GXSetPointSize` | 69 | 52 | 2 |
| `GXSetTexCopySrc` | 5 | 56 | 2 |
| `GXSetTexCopyDst` | 5 | 55 | 2 |
| `GXCopyTex` | 5 | 53 | 2 |
| `GXSetCopyFilter` | 4 | 67 | 1 |

Fog is ranked 45th and 46th by static call sites — 4 sites, 0.8 % — and is by a wide margin
the most-called unimplemented entry point at runtime. **Static call-site share is not a
usable proxy for what a frame needs**, and §7's ordering is corrected below because of it.

The EFB block is confirmed LIVE rather than hypothetical, with its real parameters:
`GXSetTexCopySrc(0, 0xe0, 0x280, 0xe0)` and `(0, 0, 0x280, 0xe0)` — the top and bottom
640x224 halves of the EFB — `GXSetTexCopyDst(0x280, 0xe0, 6, 0)` (`GX_TF_RGBA8`, no
mipmap), and `GXCopyTex(0x810341c0, 0)`.

A second 45.2 s sample over 20 enum-critical IMPLEMENTED entry points (720 calls, 18
symbols observed) makes four more measurements the host should be read against:

* **Post-transform texture matrices are the norm, not an edge case.** 20 of 21 observed
  `GXSetTexCoordGen2` calls name post-matrix `0x40` (`GX_PTTEXMTX0`); §6.2 lists
  "post-transform texture matrices are not applied" as a reported approximation. It fires
  on essentially every textured draw in real gameplay.
* **Normalized texgen sources are used.** 5 of 21 calls pass `normalize = 1` with source
  `GX_TG_NRM` and matrix `GX_TEXMTX0` — the environment-mapping shape. Also unapplied, also
  only reported.
* **Every observed texture is `CMPR`.** All 20 `GXInitTexObj` calls pass format `0xe` at
  128x128 or 256x256, `GX_CLAMP` wrap, no mipmaps. `texture.ts` decodes CMPR, so this is
  corroboration rather than a gap — but it means CMPR is the format whose texel bit layout
  (still `[SDK]`) carries essentially all of the risk.
* `GXSetZMode` was observed with compare functions **3 and 7 only** and `GXSetAlphaCompare`
  only as `(7, 0, 0, 7, 0)`, both matching what §4.1 and §4.4 claim statically.
  `GXEnableTexOffsets` was not called at all in the sampled window, so its conditional-nop
  condition remains unexercised by console evidence.

`arg_tuples` records the first 6–8 GPRs verbatim, so an entry point with fewer arguments
carries register residue in the rest; the artifact says so in its own `arg_note`. Both
samples are ONE game state — a live 2v2 battle — and a menu, a stage transition or a
different borg family may call a different set.

### 6.5 Rig facts the next agent needs before touching Dolphin

All measured on this rig on 2026-08-31, all of them things that cost time to rediscover.

* **The GDB stub refuses the hardware window.** `m cc00201c,4` returns `E00`, so the VI
  registers that hold the XFB base are NOT readable. The XFB address comes from the ROM
  instead: `gnt4_VISetNextFrameBuffer` @0x80212284 takes it in `r3` (0x8131D560 /
  0x813B3560 here — double-buffered, 640x480 YUY2).
* **The video backend string is `Software Renderer`, exactly.** With `Null` — and with an
  unrecognised string, which silently falls back — both XFBs read back as **all zero**,
  because Dolphin keeps XFB copies host-side. With `Software Renderer` the same addresses
  hold real YUY2. The software renderer is a CPU rasterizer, so this respects the
  GPU-lease rule exactly as `Null` does.
* **A stub session is short.** Measured repeatedly: the connection is reset by the peer
  after roughly 40 s of wall time or a few hundred breakpoint stops, whichever comes first.
  Both capture paths therefore keep a session to a few seconds of work and record whatever
  completed rather than assuming a long session. A guarded draw path is reached with
  `--arm-on` — run at FULL speed with no breakpoints installed and poll the guard — rather
  than by waiting under a breakpoint loop, which is roughly 15x slower.
* **Port 55555 and `user-data/dolphin-oracle` are shared with other work on this rig.** A
  second tenant launched a `Null`-backend Dolphin onto the same port mid-session. The
  framebuffer captures were re-run on `--port 55600 --user-dir user-data/dolphin-gx` for
  that reason; do the same.

## 7. What the next agent should do, in order

The previous revision's §7.1 (get a GX trace oracle) is **DONE** — see §6.3, §6.4 and §8.
Its §7.2/§7.3/§7.4 ordering was derived from STATIC call-site share, and §6.4 measured that
that share is not a usable proxy for what a frame needs. The order below is re-derived from
the runtime measurement.

### 7.1 Fog — 350 live calls in 32 s, and the host throws on the first of them

`GXSetFog` (220 calls) and `GXSetFogRangeAdj` (130) are the most-called unimplemented entry
points in real gameplay by a wide margin, and they are ranked 45th and 46th by static call
sites, which is why they were last on the previous list. A host that throws on
`GXSetFog` cannot render one frame of a battle.

The console evidence is already captured
(`research/decomp/data/gx-surface/battle-2v2.unimplemented.gx-surface.json`): the ROM
passes fog type `2` with a colour pointer, and type `0` to disable; every observed
`GXSetFogRangeAdj` call passes its enable argument as `0`. The decompiled body of
`gnt4_GXSetFog_bl` packs its arguments straight into the fog BP registers, so the state is
readable from the corpus rather than from the SDK. `GXSetFogRangeAdj` is a candidate for
the `GXEnableTexOffsets` treatment — a CONDITIONAL declared-nop that throws on the
condition the console has never been observed to take — but note that "never observed" is
one 32 s sample of one game state, and the condition must stay loud.

### 7.2 The EFB model and `GXCopyTex` — confirmed live, with its real parameters

`GXCopyTex` fired 5 times in the same 32 s window, so this is a mechanism the game
actually uses rather than a call-site count. §6.4 records the parameters the console
passes, which is most of the specification: source boxes `(0, 224, 640, 224)` and
`(0, 0, 640, 224)`, destination `640x224` in `GX_TF_RGBA8` with no mipmap, destination
address `0x810341c0`, `clear = 0`, and `GXSetCopyFilter(0, ..., 1, ...)`.

### 7.3 Post-transform texture matrices and normalized texgen

Both are listed in §6.2 as reported approximations, and §6.4 measured that the first fires
on 20 of 21 observed texgen calls and the second on 5 of 21. They are not edge cases; they
are what the game's textured draws do. `GX_PTTEXMTX0` (0x40) is the post-matrix the ROM
names, and the normalized case is the environment-mapping shape (`GX_TG_NRM` source,
`GX_TEXMTX0`, `normalize = 1`).

### 7.4 Per-vertex position matrices (skinning)

`GX_VA_PNMTXIDX` is already decoded per vertex and already reported per draw; what is
missing is uploading the position-matrix memory as an array and indexing it in the vertex
shader. Nothing about character geometry can be right until this exists, and it is the
cheapest of the remaining rendering features.

### 7.5 Extend the oracle to a SECOND, harder ROM draw function

§6.3 verifies one function, and that function is the smallest and simplest one: an
untextured, unlit, single-stage, alpha-blended quad. The two harnesses are function-generic
— `capture_gx.py sites` takes any terminating ROM function and binds it to any
single-function wasm build — so the cost of a second one is a gate-lowered unit, not new
tooling. A window containing a TEXTURED or MULTI-STAGE draw is what would put the TEV
shader generator and the texture decoder in front of the console for the first time; today
neither has ever been compared against anything.

The framebuffer differential also generalises, but only to draws that can be switched off
by staging one word of the ROM's own state. Finding that switch is the per-function cost.

### 7.6 Scissor, line width, point size, and the boot-plumbing decisions

Scissor is one call site and one `gl.scissor` away. `GXSetLineWidth` and `GXSetPointSize`
were observed 69 times each, always as `(6, 0)`; they want a deliberate decision rather
than a blanket one. The nine FIFO/boot entry points likewise — the `GXEnableTexOffsets`
treatment (conditional nop, loud on the condition the ROM never exercises) is the pattern
to copy, and the surface capture is how to find out which condition that is.

### 7.7 Batching, and moving rendering to an OffscreenCanvas in the worker

One draw call per primitive is fine for a proof and will not be fine for a frame. The
adapters currently run on the main thread, which is where `RomRuntimeHost` services bridged
calls, so a main-thread canvas is correct today. Design G1 wants the worker-side GX shim
submitting through an OffscreenCanvas, and design E2's dual-canvas compositor governs the
hybrid period where `packages/render/`'s three.js canvas and the GX canvas coexist. Neither
is built.

### 7.8 Widen the surface capture beyond one game state

§6.4's two samples are both a live 2v2 battle. A menu, the attract sequence, a stage
transition and a different borg family will call a different set, and the `scenarios/`
machinery (`force_navigator.py cover`) already exists to stage them. The runtime ranking
should be re-measured across several before it is treated as the ranking.

## 8. Reproducing everything here

```bash
node scripts/gx-call-inventory.mjs          # re-measure the call surface
GF_SMOKE_GX_HOST=1 node scripts/smoke-browser-game.mjs   # full route + GX phase
node scripts/smoke-gx-host-phase.mjs        # the GX phase alone
packages/rom-runtime/test/fixtures/gx-selftest/build.sh  # rebuild the hand-written fixture
packages/rom-runtime/test/fixtures/gx-rom-unit/build.sh  # relink the gate-lowered ROM unit
```

### 8.1 The console oracles (§6.3, §6.4)

Replaying committed evidence needs no emulator and no emsdk:

```bash
pnpm test:oracle                            # includes the 16-test GX rehearsal
node research/decomp/oracle-harness/run-gx-callstream.mjs \
  --capture research/decomp/oracle-harness/corpora/gx-rom-unit.zz_0027c34_.gx-callstream.jsonl
node research/decomp/oracle-harness/run-gx-framebuffer.mjs \
  --control  research/decomp/oracle-harness/corpora/gx-rom-unit.zz_0027c34_.xfb-control.json \
  --treatment research/decomp/oracle-harness/corpora/gx-rom-unit.zz_0027c34_.xfb-treatment.json \
  --capture  research/decomp/oracle-harness/corpora/gx-rom-unit.zz_0027c34_.gx-callstream.jsonl
```

RE-CAPTURING from the console needs Dolphin, and §6.5's rig facts apply — one stub
connection per boot, and relaunch between every attaching step:

```bash
# the plan is derived from the ROM + the built module; no emulator
python research/tools/dolphin-trace/capture_gx.py sites --fn 0x80027c34 \
  --wasm packages/rom-runtime/test/fixtures/gx-rom-unit/gx_rom_unit.threads.wasm \
  --export zz_0027c34_ \
  --reads research/tools/dolphin-trace/plans/gx.zz_0027c34_.reads.json \
  --out research/tools/dolphin-trace/plans/gx.zz_0027c34_.json

# the call stream (Null video is fine here — nothing reads a framebuffer)
python research/tools/dolphin-trace/capture_oracle.py launch \
  --save-state "2v2 gred cotrolled players no cpu.sav" --wait 150
python research/tools/dolphin-trace/capture_gx.py capture \
  --plan research/tools/dolphin-trace/plans/gx.zz_0027c34_.json --n 4 \
  --stage 0x80436108=1 --out <out.jsonl>

# the runtime surface (one boot per sample)
python research/tools/dolphin-trace/capture_gx.py surface --only <symbols> \
  --args 8 --seconds 45 --out <out.json>

# the framebuffer differential: TWO boots, Software Renderer, private port
python research/tools/dolphin-trace/capture_oracle.py launch --port 55600 \
  --user-dir user-data/dolphin-gx --gfx "Software Renderer" \
  --save-state "2v2 gred cotrolled players no cpu.sav" --wait 180
python research/tools/dolphin-trace/capture_gx.py framebuffer --port 55600 \
  --label control --settle 8 --out <control.json>
# ... relaunch identically, then:
python research/tools/dolphin-trace/capture_gx.py framebuffer --port 55600 \
  --label treatment --settle 8 --fn 0x80027c34 --stage 0x80436108=1 --out <treatment.json>
```

The two console frames MUST come from the same savestate at the same `--settle` index; the
harness refuses a pair whose recorded frame indices differ.

Both `build.sh` scripts document the Windows invocation (the pinned emsdk has no
`emsdk_env.sh` path there) in their own headers. `gx-rom-unit/build.sh` also records how
to REGENERATE its sources from the assembly gate rather than trusting the committed copy.

The GX phase is opt-in and does not run in the default smoke route. `pnpm typecheck`,
`pnpm --filter game build` and the default `node scripts/smoke-browser-game.mjs` are
unaffected by this work.
