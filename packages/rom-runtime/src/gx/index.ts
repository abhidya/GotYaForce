// =============================================================================
// gx/index.ts — the GX half of the HLE host.
//
// STATUS: SCAFFOLDING, not a renderer. Read docs/gx-hle-host.md before relying
// on anything here. Summary of what that document says at length:
//   - every adapter is evidence-class "synthetic": written from GX semantics
//     and decompiled ROM call sites, never compared against a captured frame;
//   - the claim ceiling for this path even once verified is
//     "framebuffer-equivalent, never pixel-identical";
//   - the ROM's real vertex submission goes through the write-gather pipe at
//     0xCC008000, and the assembly gate does not lower those stores yet, so no
//     real ROM unit can submit geometry through this path today.
// =============================================================================

export {
  GXAttr,
  GXAttrType,
  GXBlendFactor,
  GXBlendMode,
  GXChannelID,
  GXColorCompType,
  GXColorSrc,
  GXCompCnt,
  GXCompType,
  GXCompare,
  GXCullMode,
  GXPrimitive,
  GXProjectionType,
  GX_DUALMTX_BASE,
  GX_IDENTITY_MTX,
  GX_MAX_PNMTX_ID,
  GX_MAX_TEXMAP,
  GX_PNMTX_STRIDE,
  GX_TEXMAP_NULL,
  GX_TEXMTX0,
  GX_TEX_DISABLE,
  attrName,
  directComponentBytes,
  primitiveName,
} from "./enums.js";

export {
  GxState,
  type GxArrayBinding,
  type GxDrawState,
  type GxTexObj,
  type GxVatEntry,
} from "./state.js";

export { GxFifo, GxFifoError, type GxPrimitive as GxPrimitiveData, type GxPrimitiveSink } from "./fifo.js";

export { GxRecordingBackend, type GxBackend, type GxPrimitiveRecord } from "./backend.js";

export { GxWebglBackend, gxMtx3x4ToGl, gxProjectionToGl } from "./webgl.js";

export {
  GxHost,
  GX_NO_BEHAVIOURAL_CLAIM,
  IMPLEMENTED_EFFECTS,
  IMPLEMENTED_SYMBOLS,
  WGPIPE_SYMBOLS,
  gxTieredCoverage,
  registerGxAdapters,
  registerWgPipeAdapters,
  type GxImplTier,
} from "./adapters.js";

export {
  GX_CALL_INVENTORY,
  GX_GAME_CALL_SITES,
  gxCoverage,
  gxInventoryEntry,
  type GxInventoryEntry,
} from "./inventory.generated.js";
