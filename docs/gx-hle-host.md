# The GX HLE host — the browser standing in for the GameCube's graphics hardware

Status: **SCAFFOLDING, unverified.** The seam is proven; the pixels are not.
Date: 2026-08-29. Design authority: `docs/playable-port-design.md` (V2 F2 "Stage D — SDK
seam", V3 non-fatal note 1's claim bar, V4 H2's bridge, V5 I1's adapter contract).

---

## 0. What this is, in one paragraph

`docs/playable-port-design.md` names the browser as the HLE host behind the SDK seam: the
composed ROM module executes the game's own code, and everything the GameCube SDK used to
do — graphics, audio, OS, DVD — is provided by the host. This document covers the
graphics half. It describes a `packages/rom-runtime`-side GX adapter set that receives the
ROM module's GX calls through the existing H2 Atomics bridge, tracks the GX pipeline
state, decodes the write-gather-pipe traffic the ROM uses to submit vertices, and
rasterizes the result through WebGL2. It is a **foundation**, not a renderer, and the
distinction is made structurally rather than by promise: every adapter is registered with
`evidenceClass: "synthetic"`, so the adapter registry refuses the whole set unless a host
explicitly opts in to pilot work.

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
   and from the ROM's decompiled call sites.
3. **What the ceiling is, even after verification exists.** The design's own words:
   **"framebuffer-equivalent, never pixel-identical"** (V3 non-fatal note 1). WebGL
   rasterization cannot match Flipper. The TEV combiner, EFB copy semantics, GameCube
   fixed-point rasterization rules, the 24-bit depth comparison and the texture filter
   kernels all differ. No document, log line or test name may quietly upgrade this.

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
| 4 | `GXSetTevOrder_bl` | 0x8022a14c | 18 | 15 | 25.3% | latched |
| 5 | `GXClearVtxDesc_bl` | 0x802261ac | 18 | 18 | 28.9% | translated |
| 6 | `GXSetProjection_bl` | 0x8022bce8 | 18 | 16 | 32.5% | translated |
| 7 | `GXSetZMode_bl` | 0x8022a8b4 | 18 | 15 | 36.1% | translated |
| 8 | `GXEnableTexOffsets_bl` | 0x802277e4 | 16 | 2 | 39.2% | — |
| 9 | `GXLoadPosMtxImm_bl` | 0x8022be60 | 16 | 15 | 42.4% | translated |
| 10 | `GXSetChanCtrl_bl` | 0x80228898 | 16 | 14 | 45.6% | translated |
| 11 | `GXSetCurrentMtx_bl` | 0x8022bf00 | 15 | 15 | 48.6% | translated |
| 12 | `GXSetNumChans_bl` | 0x8022885c | 15 | 15 | 51.6% | latched |
| 13 | `GXSetNumTevStages_bl` | 0x8022a2e8 | 15 | 15 | 54.6% | latched |
| 14 | `GXSetNumTexGens_bl` | 0x80226d6c | 15 | 15 | 57.6% | latched |
| 15 | `GXSetCullMode_bl` | 0x8022782c | 14 | 14 | 60.4% | translated |
| 16 | `GXSetTevOp_bl` | 0x80229bac | 13 | 13 | 62.9% | latched |
| 17 | `GXSetTexCoordGen2_bl` | 0x80226aec | 9 | 8 | 64.7% | — |
| 18 | `GXLoadTexObj_bl` | 0x80229108 | 9 | 8 | 66.5% | latched |
| 19 | `GXSetTevKColor_bl` | 0x80229e88 | 9 | 4 | 68.3% | — |
| 20 | `GXLoadTexMtxImm_bl` | 0x8022bf34 | 8 | 8 | 69.9% | latched |
| 21 | `GXSetBlendMode_bl` | 0x8022a808 | 8 | 8 | 71.5% | translated |
| 22 | `GXInitTexObjLOD_bl` | 0x80228e08 | 8 | 6 | 73.1% | — |
| 23 | `GXSetTevKColorSel_bl` | 0x80229efc | 7 | 4 | 74.5% | — |
| 24 | `GXSetTevAlphaOp_bl` | 0x80229d28 | 7 | 4 | 75.9% | — |
| 25 | `GXSetTevColorIn_bl` | 0x80229c38 | 7 | 4 | 77.3% | — |
| 26 | `GXSetTevColorOp_bl` | 0x80229cc0 | 7 | 4 | 78.7% | — |
| 27 | `GXInvalidateTexAll_bl` | 0x80229358 | 6 | 6 | 79.9% | declared-nop |
| 28 | `GXSetTevSwapMode_bl` | 0x80229fb4 | 5 | 2 | 80.9% | — |
| 29 | `GXSetTevColor_bl` | 0x80229d90 | 5 | 3 | 81.9% | — |
| 30 | `GXSetTevAlphaIn_bl` | 0x80229c7c | 5 | 2 | 82.9% | — |
| 31 | `GXSetArray` | 0x80226a50 | 4 | 2 | 83.7% | translated |
| 32 | `GXSetAlphaUpdate_bl` | 0x8022a888 | 4 | 3 | 84.5% | translated |
| 33 | `GXSetColorUpdate_bl` | 0x8022a85c | 4 | 3 | 85.3% | translated |
| 34 | `GXSetTevSwapModeTable_bl` | 0x80229ffc | 3 | 1 | 85.9% | — |
| 35 | `GXInitTexObj_bl` | 0x80228b74 | 3 | 2 | 86.5% | latched |
| 36 | `GXSetTevKAlphaSel_bl` | 0x80229f58 | 3 | 1 | 87.1% | — |
| 37 | `GXLoadTlut_bl` | 0x80229194 | 3 | 3 | 87.6% | — |
| 38 | `GXSetVtxAttrFmtv_bl` | 0x80226440 | 3 | 3 | 88.2% | — |
| 39 | `GXProject_bl` | 0x8022bb74 | 3 | 3 | 88.8% | — |
| 40 | `GXSetCPUFifo_bl` | 0x80225378 | 3 | 2 | 89.4% | — |
| 41 | `GXSetGPFifo_bl` | 0x802254a0 | 3 | 2 | 90.0% | — |
| 42 | `__GXFlushTextureState_bl` | 0x80229b88 | 2 | 1 | 90.4% | declared-nop |
| 43 | `GXPixModeSync_bl` | 0x80227240 | 2 | 2 | 90.8% | declared-nop |
| 44 | `GXSetChanMatColor_bl` | 0x8022876c | 2 | 1 | 91.2% | — |
| 45 | `GXSetFog_bl` | 0x8022a310 | 2 | 2 | 91.6% | — |
| 46 | `GXSetFogRangeAdj_bl` | 0x8022a6e4 | 2 | 2 | 92.0% | — |
| 47 | `GXInvalidateVtxCache_bl` | 0x80226adc | 2 | 2 | 92.4% | declared-nop |
| 48 | `GXSetAlphaCompare_bl` | 0x8022a07c | 2 | 2 | 92.8% | — |
| 49 | `GXGetGPFifo_bl` | 0x8022588c | 2 | 2 | 93.2% | — |
| 50 | `GXGetProjectionv_bl` | 0x8022be18 | 2 | 1 | 93.6% | translated |
| 51 | `GXSetLineWidth_bl` | 0x80227764 | 2 | 2 | 94.0% | — |
| 52 | `GXSetPointSize_bl` | 0x802277a4 | 2 | 2 | 94.4% | — |
| 53 | `GXCopyTex_bl` | 0x80228188 | 2 | 2 | 94.8% | — |
| 54 | `GXInitTlutRegion_bl` | 0x80229320 | 2 | 1 | 95.2% | — |
| 55 | `GXSetTexCopyDst_bl` | 0x80227b14 | 2 | 2 | 95.6% | — |
| 56 | `GXSetTexCopySrc_bl` | 0x80227a64 | 2 | 1 | 96.0% | — |
| 57 | `GXInitLightColor_bl` | 0x802285f4 | 1 | 1 | 96.2% | — |
| 58 | `GXInitLightPos_bl` | 0x802285c8 | 1 | 1 | 96.4% | — |
| 59 | `GXLoadNrmMtxImm_bl` | 0x8022beb0 | 1 | 1 | 96.6% | latched |
| 60 | `GXLoadLightObjImm_bl` | 0x80228600 | 1 | 1 | 96.8% | — |
| 61 | `GXInitLightDistAttn_bl` | 0x802284f8 | 1 | 1 | 97.0% | — |
| 62 | `GXSetChanAmbColor_bl` | 0x8022867c | 1 | 1 | 97.2% | — |
| 63 | `GXSetScissor_bl` | 0x8022c13c | 1 | 1 | 97.4% | latched |
| 64 | `GXGetViewportv_bl` | 0x8022c118 | 1 | 1 | 97.6% | translated |
| 65 | `GXInitLightSpot_bl` | 0x80228368 | 1 | 1 | 97.8% | — |
| 66 | `GXInitTlutObj_bl` | 0x8022915c | 1 | 1 | 98.0% | — |
| 67 | `GXSetCopyFilter_bl` | 0x80227e04 | 1 | 1 | 98.2% | — |
| 68 | `GXSetNumIndStages_bl` | 0x80229ae8 | 1 | 1 | 98.4% | — |
| 69 | `GXSetTevColorS10_bl` | 0x80229e0c | 1 | 1 | 98.6% | — |
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
| `translated` (changes the frame) | 16 | 21.1% | 247 | **49.2%** |
| `+ latched` (accepted, not acted on) | 26 | 34.2% | 345 | 68.7% |
| `+ declared-nop` (correctly inert) | 30 | 39.5% | 357 | 71.1% |
| **not implemented — fails loudly** | **46** | **60.5%** | 145 | 28.9% |

The honest headline is the first row: **49.2% of the ROM's static GX call sites reach an
entry point that changes what is drawn.** The other rows are reported next to it rather
than merged into it, because collapsing them into one "implemented" figure is exactly how
a graphics seam talks itself into sounding finished.

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

**Consequence, still open (top blocker, §7.1):** `0xCC008000` is hardware MMIO, and the
composed module's linear memory is `0x807A0000` bytes. `0xCC008000` is past the end, so a
literal store there traps. Lowering `DAT_cc008000` stores to the `__gf_gx_wgpipe_*` imports
this decoder consumes is a **required assembly-gate amendment that does not exist yet**.
Until it lands, no real ROM unit can submit geometry through this path.

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
| `state.ts` | the latched GX pipeline state — VCD, the 8 VAT slots, projection, matrix memory, raster state, texture objects — plus the per-draw snapshot |
| `fifo.ts` | the write-gather-pipe decoder and vertex assembly (§3) |
| `backend.ts` | the `GxBackend` interface and the headless recording backend the decode-side assertions run against |
| `webgl.ts` | the WebGL2 rasterizer, and the `diagnostics` list where every approximation names itself |
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

### 4.2 Two byte orders, both deliberate

This bit the implementation once and is worth stating plainly:

* **The arena is LITTLE-endian.** It is byte-swapped to wasm-native order when it is built
  from the DOL. Verified rather than assumed: `apps/game/public/rom/arena.json` stores the
  `1.0f` constant at `0x80436f78` as `00 00 80 3f`. Matrix and indexed-array reads use it.
* **The FIFO stream is BIG-endian.** It is register-order data that never lived in memory,
  so it keeps the console's order. Corroborated by the display-list interpreter's
  `DAT_cc008000._0_2_ = CONCAT11(hi, lo)` INDEX16 write.

The unresolved corner is §7.4: a byte-wise attribute (an RGBA8 colour) in a DOL-derived
array is only in console order if the arena builder did *not* word-swap it. The self-test
fixture writes its colour array as explicit bytes for exactly this reason, with the
reasoning recorded at the definition site.

### 4.3 Loudness

Every one of the 76 measured entry points has an adapter. The 46 that are not implemented
get one that **throws**, naming the symbol, its ROM address, its static call-site count and
its number of distinct callers. That surfaces as a declared servicing error in the
bridged-call ledger and fails the frame. There is no silent no-op anywhere in the surface:
a silent no-op in a graphics seam produces a frame that renders and is wrong, which is
strictly worse than a frame that fails.

The four `declared-nop` entry points are the one legitimate exception — cache invalidation
and pipe synchronization genuinely have no host-visible effect — and they are tiered
separately so they can never be confused with the other two categories.

The WebGL backend adds a second loudness channel for things a *call-level* check cannot
catch: at draw time it reports per-vertex position matrices it did not apply, a TEV texmap
selection it did not sample, lighting it did not evaluate, extra TEV stages it did not
combine, a logic-op blend it could not express, and any primitive it could not draw.

---

## 5. The end-to-end proof

`scripts/smoke-gx-host-phase.mjs`, opt-in with `GF_SMOKE_GX_HOST=1`, appended to
`scripts/smoke-browser-game.mjs` as a single self-contained import block at the end of the
file. It owns its own bundle, server, browser and CDP session, exactly like
`scripts/smoke-rom-runtime-phase.mjs`.

**What it runs.** A purpose-built ROM-side wasm draw module
(`packages/rom-runtime/test/fixtures/gx-selftest/`, compiled with the repo's pinned emsdk,
binary committed) whose three draw functions reproduce — call for call and store for
store — three of the ROM's own immediate-mode draw paths:

| fixture export | reproduces | vertex layout |
|---|---|---|
| `gx_draw_fullscreen_quad` | `zz_0027c34_` (chunk_0003.c:3285-3328) | `GX_QUADS`, POS DIRECT S16 XY + CLR0 DIRECT RGBA8 |
| `gx_draw_strip` | `zz_0050f80_` (chunk_0006.c:4865-4924) | `GX_TRIANGLESTRIP`, POS DIRECT F32 XYZ + CLR0 RGBA8 |
| `gx_draw_indexed` | `zz_0050bf4_` (chunk_0006.c:4760-4797) | primitive `0xb0`, POS + CLR0 INDEX8 through `GXSetArray` |
| `gx_call_unimplemented` | — | calls `GXSetFog`, which the host does not implement |

It runs on the real composed-module runtime: worker-owned shared `WebAssembly.Memory`
under COOP/COEP isolation, the H2 Atomics RPC bridge, and signature-accurate per-import
trampolines — so the module's GX calls arrive exactly as a composed ROM module's would.

**Measured result (2026-08-29, headless Chrome + SwiftShader):**

```
GX HLE-host phase PASS (seam only, NO behavioural claim):
{"checks":32,"bridgedCalls":95,"primitives":3,"droppedFifoBytes":0,
 "unimplementedHits":["gnt4_GXSetFog_bl"],
 "coverage":{"translated":"16/76 entry points, 49.2% of ROM call sites",
             "translatedAndLatched":"26/76 entry points, 68.7% of ROM call sites"},
 "verified":false,"evidence":".tmp\\gx-host-smoke\\evidence"}
```

32 in-page checks, all passing, covering: 95 GX crossings recorded in the bridged-call
ledger; three primitives assembled with **zero dropped FIFO bytes** and none left buffered;
the S16 corner `(0,0)` and the RGBA8 colour the ROM wrote decoded exactly; the F32 vertex
`(160,112,0)` decoded exactly; the INDEX8 path resolving both positions and colours through
`GXSetArray`; both projection branches latching the right coefficients; readPixels
confirming the strip's green at the centre and the quad's blue at the corner; and
`GXSetFog` rejecting with `ADAPTER_THREW`, named in the ledger.

**Evidence.** `.tmp/gx-host-smoke/evidence/` holds `gx-framebuffer.png` (the GX framebuffer
itself), `gx-selftest.png` (the full page with the results table), `console.log`, and
`gx-selftest-results.json` (checks + ledger + adapter roster).

**What the smoke phase additionally refuses.** It fails if any GX adapter reports
`evidenceClass: "verified"`, and it fails if the page's payload or the adapter roster stops
stating that it carries no behavioural claim. The honesty is a gate, not a comment.

**What a green run means and does not mean.** It means the seam works: ROM-shaped GX calls
reach the adapters, decode correctly, and rasterize. It means nothing about whether these
frames match the GameCube — see §1.

---

## 6. What is NOT implemented

### 6.1 Entry points (46 of 76, 28.9% of static call sites)

Grouped by what they would unlock, highest-value first:

* **TEV combiner** — `GXSetTevColorIn/ColorOp/AlphaIn/AlphaOp`, `GXSetTevKColor`,
  `GXSetTevKColorSel`, `GXSetTevKAlphaSel`, `GXSetTevSwapMode(Table)`, `GXSetTevColor`,
  `GXSetTevColorS10`, `GXSetTevDirect/Indirect`, `GXSetNumIndStages`. Together with the
  `latched` `GXSetTevOrder`/`GXSetTevOp`/`GXSetNumTevStages`, this is the fragment shader
  the game actually programs. Nothing textured or multi-stage can look right without it.
* **Texture pipeline** — `GXSetTexCoordGen2`, `GXEnableTexOffsets`, `GXInitTexObjLOD`,
  `GXLoadTlut`, `GXInitTlutObj/Region`, plus decoding the GameCube texture formats and
  uploading them. `GXInitTexObj`/`GXLoadTexObj` currently record and bind but never sample.
* **Lighting** — `GXInitLightColor/Pos/DistAttn/Spot`, `GXLoadLightObjImm`,
  `GXSetChanMatColor`, `GXSetChanAmbColor`. Note `GXSetChanMatColor`'s signature is
  genuinely ambiguous: the corpus call site passes a POINTER (`&local_24`) while the SDK
  passes `GXColor` by value. It was left unimplemented rather than guessed.
* **Framebuffer / EFB** — `GXCopyTex`, `GXSetTexCopySrc/Dst`, `GXSetCopyFilter`,
  `GXSetPixelFmt`. Render-to-texture effects.
* **Fixed-function raster extras** — `GXSetFog`, `GXSetFogRangeAdj`, `GXSetAlphaCompare`,
  `GXSetLineWidth`, `GXSetPointSize`.
* **FIFO / init plumbing** — `__GXInitGX`, `__GXFifoInit`, `GXInitFifoBase`,
  `GXSetCPUFifo/GPFifo`, `GXGetGPFifo`, `__GXPEInit`, `__GXSetTmemConfig`,
  `__GXSetIndirectMask`, `GXSetMisc`. Mostly one-time boot calls; an HLE host will
  probably declare most of these inert, but only after deciding so deliberately.
* **`GXProject`** — real math already exists in
  `research/decomp/generated/pi-port/sdk-shims/gx_stubs.c` and should be ported over.
* **`GXSetVtxAttrFmtv`** — deliberately left unimplemented: its `GXVtxAttrFmtList` struct
  layout could not be confirmed from the corpus, and guessing a struct layout in a decoder
  that then mis-sizes the FIFO is the exact failure mode §3 exists to avoid.

### 6.2 Rendering features

* **No texture sampling.** No GameCube texture format is decoded; nothing is uploaded.
* **No TEV translation.** The fragment shader is `vertexColor * materialColor`.
* **No lighting.** Normals are decoded and normal matrices are stored, and neither is used.
* **No texgen.** Texture matrices are stored and never applied to a texcoord.
* **No per-vertex position matrices.** `GX_VA_PNMTXIDX` is decoded but every vertex uses
  the `GXSetCurrentMtx` matrix, so skinned geometry would be wrong. Reported per draw.
* **No scissor.** Latched, not applied.
* **No EFB model.** No copy, no framebuffer formats, no depth-buffer readback.
* **No batching.** One draw call per GX primitive.
* **Depth remap.** GX clips z to `[-1, 0]`; the projection's third row is rewritten as
  `2*row2 + row3` to reach GL's `[-1, 1]`. Visible ordering is preserved; depth precision
  distribution is not the console's.
* **Quad expansion.** GL has no quads, so each is split into two triangles on a fixed
  diagonal. Exact for planar convex quads; a non-planar quad rasterizes differently than
  Flipper's own split.

### 6.3 Verification

There is none. No GX trace capture exists, no reference framebuffer exists, and no
comparison has been made. This is the single largest gap and §7.2 is the way out.

---

## 7. What the next agent should do, in order

### 7.1 Lower `DAT_cc008000` in the assembly gate — the top blocker

Nothing downstream matters until a real ROM unit can submit a vertex. The gate must
recognize stores to `0xCC008000` (and `0xCC008004`) and lower them to the
`__gf_gx_wgpipe_u8/u16/u32/f32` imports, preserving store width. The host side already
exists and is registered (`registerWgPipeAdapters`), so this is one change in
`OGhidra src/port_dispatch_companion.py`-adjacent codegen plus a rebuild. Gate: a composed
window containing one of the ROM's own draw functions (`zz_0027c34_` is the smallest)
produces a primitive through the existing GX host.

### 7.2 Get a GX trace oracle

The Stage-B Dolphin GDB machinery already exists. Breakpointing the GX entry points and
recording `(args, referenced memory)` per call yields a call-sequence corpus that can be
replayed against these adapters — which is what would let individual adapters move from
`evidenceClass: "synthetic"` to `"verified"`. A framebuffer dump at the same trace points
gives the framebuffer-equivalence comparison the claim bar actually names. Until then §1's
claim 2 stands unchanged.

### 7.3 Implement the TEV combiner

It is the largest single block of unimplemented entry points and the one most responsible
for the frame looking wrong rather than empty. It needs a shader generator, not more
adapters — the adapters are the easy half.

### 7.4 Settle the arena byte order for non-float data

§4.2. Determine whether the arena builder word-swaps *all* four-byte quantities or only
typed floats. If it swaps everything, DOL-derived colour arrays are in `A,B,G,R` order in
the arena and the indexed colour fetch needs a compensating swap. This is a one-hour
investigation that will otherwise surface as an inexplicable colour bug.

### 7.5 Move rendering to an OffscreenCanvas in the worker

The adapters currently run on the main thread, which is where `RomRuntimeHost` services
bridged calls, so a main-thread canvas is correct today. Design G1 wants the worker-side GX
shim submitting through an OffscreenCanvas, and design E2's dual-canvas compositor governs
the hybrid period where `packages/render/`'s three.js canvas and the GX canvas coexist.
Neither is built.

---

## 8. Reproducing everything here

```bash
node scripts/gx-call-inventory.mjs          # re-measure the call surface
GF_SMOKE_GX_HOST=1 node scripts/smoke-browser-game.mjs   # full route + GX phase
node scripts/smoke-gx-host-phase.mjs        # the GX phase alone
packages/rom-runtime/test/fixtures/gx-selftest/build.sh  # rebuild the fixture wasm
```

The GX phase is opt-in and does not run in the default smoke route. `pnpm typecheck`,
`pnpm --filter game build` and the default `node scripts/smoke-browser-game.mjs` are
unaffected by this work.
