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
//     0xCC008000; the assembly gate DOES lower those stores now (opt-in behind
//     OGHIDRA_PORT_WGPIPE_LOWERING=1), and a gate-lowered ROM draw function
//     drives this path in the browser — but that proves the seam, not the
//     pixels.
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
  GXAlphaOp,
  GXAttnFn,
  GXDiffuseFn,
  GXTevAlphaArg,
  GXTevBias,
  GXTevColorArg,
  GXTevColorChan,
  GXTevKColorSel,
  GXTevMode,
  GXTevOp,
  GXTevRegID,
  GXTevScale,
  GXTexFilter,
  GXTexFmt,
  GXTexGenSrc,
  GXTexGenType,
  GXTexWrapMode,
  GXTlutFmt,
  GX_LIGHT_OBJ_BYTES,
  GX_MAX_LIGHT,
  GX_PTIDENTITY,
  GX_PTTEXMTX_BASE,
} from "./enums.js";

export {
  GxState,
  type GxArrayBinding,
  type GxChanCtrl,
  type GxDrawState,
  type GxLight,
  type GxTexGen,
  type GxTexObj,
  type GxTlutObj,
  type GxVatEntry,
} from "./state.js";

export {
  DEFAULT_ALPHA_COMPARE,
  DEFAULT_SWAP_TABLE,
  defaultTevStage,
  generateTevShader,
  tevStageFromOp,
  type GxAlphaCompare,
  type GxSwapRow,
  type GxTevOpState,
  type GxTevShaderConfig,
  type GxTevShaderResult,
  type GxTevStage,
} from "./tev.js";

export {
  GxTextureError,
  decodeTextureBytes,
  decodeTextureFromMemory,
  gxImageBytes,
  texFormatName,
  type GxDecodedTexture,
} from "./texture.js";

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
  registerPsmtxIdentityAdapter,
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
