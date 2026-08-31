// =============================================================================
// audio/index.ts — the audio half of the HLE host.
//
// STATUS: SCAFFOLDING, and the honest headline is not a coverage number. Read
// docs/audio-dvd-hle-host.md before relying on anything here. Summary:
//   - audio is only 15% a call surface: 6 of 40 static game call sites cross
//     the SDK seam; the other 34 reach hardware through MMIO registers, which
//     the assembly gate does NOT lower yet;
//   - the mixer is MusyX microcode on the GameCube DSP. It is not PowerPC
//     code, it is not in the DOL, and none of it is translated here. This host
//     carries a PCM buffer to the speakers; it cannot fill one;
//   - every adapter is evidence-class "synthetic"; nothing has been compared
//     against console audio.
//
// This is NOT a replacement for `packages/audio`. That package plays the real
// OGGs extracted from the disc and is the TS recreation's own sound path. This
// is the path the COMPOSED ROM MODULE takes when its own code drives the DAC.
// =============================================================================

export {
  ADPCM_COEF_COUNT,
  ADPCM_FRAME_BYTES,
  ADPCM_SAMPLES_PER_FRAME,
  AdpcmError,
  aiDmaBytesToPcm,
  decodeDspAdpcm,
  pcmToAiDmaBytes,
  readDspAdpcmHeader,
  type AdpcmDecodeRequest,
  type AdpcmState,
} from "./adpcm.js";

export {
  AI_AICR,
  AI_AIIT,
  AI_AISCNT,
  AI_AIVR,
  AI_DMA_ADDR_HI,
  AI_DMA_ADDR_LO,
  AI_DMA_CNT,
  AI_DMA_ENABLE,
  AI_DMA_UNIT_BYTES,
  AI_SAMPLE_RATE_32KHZ,
  AI_SAMPLE_RATE_48KHZ,
  AI_SYMBOL_NAME_CORRECTIONS,
  AI_WINDOW,
  AICR_AIINT,
  AICR_AISFR,
  AICR_DSPFR,
  AICR_PSTAT,
  AICR_SCRESET,
  AR_DMA_ARADDR,
  AR_DMA_CNT,
  AR_DMA_MMADDR,
  AudioRegisterError,
  AudioRegisterFile,
  MODELLED_WITH_EFFECT,
  STORAGE_ONLY,
  DSP_CSR,
  DSP_MBOX_IN_HI,
  DSP_MBOX_IN_LO,
  DSP_MBOX_OUT_HI,
  DSP_MBOX_OUT_LO,
  DSP_WINDOW,
  physToGcAddress,
  type RegisterAccess,
} from "./registers.js";

export {
  AudioRecordingBackend,
  WebAudioBackend,
  type AudioBackend,
  type AudioBlockRecord,
  type AudioDmaBlock,
} from "./backend.js";

export {
  AUDIO_IMPLEMENTED_EFFECTS,
  AUDIO_IMPLEMENTED_SYMBOLS,
  AUDIO_NO_BEHAVIOURAL_CLAIM,
  AudioHost,
  MMIO_SYMBOLS,
  audioTieredCoverage,
  registerAudioAdapters,
  registerMmioAdapters,
  type AudioImplTier,
  type AudioPendingInterrupt,
} from "./adapters.js";

export {
  AUDIO_BRIDGED_GAME_CALL_SITES,
  AUDIO_CALL_INVENTORY,
  AUDIO_GAME_CALL_SITES,
  AUDIO_MMIO_INVENTORY,
  audioCoverage,
  audioInventoryEntry,
} from "./inventory.generated.js";
