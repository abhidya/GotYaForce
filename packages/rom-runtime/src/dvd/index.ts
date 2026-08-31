// =============================================================================
// dvd/index.ts — the DVD half of the HLE host.
//
// STATUS: SCAFFOLDING. Read docs/audio-dvd-hle-host.md before relying on
// anything here. Summary of what that document says at length:
//   - every adapter is evidence-class "synthetic": written from the SDK's
//     semantics and the ROM's own decompiled bodies, never compared against a
//     real drive;
//   - THIS REPOSITORY HAS NO DISC BYTES, so the default disc is one the host
//     builds in memory. Real disc bytes are owner-supplied and untracked;
//   - reads complete synchronously inside the adapter call, which is a known,
//     reported behavioural divergence from a drive that takes milliseconds.
// =============================================================================

export {
  DVD_SECTOR_BYTES,
  DVD_READ_ALIGN,
  DvdDiscError,
  FST_ENTRY_BYTES,
  ImageDisc,
  SyntheticDisc,
  buildGcFst,
  parseGcFst,
  type DiscImage,
  type GcFstEntry,
} from "./disc.js";

export {
  DVD_CB,
  DVD_DISK_ID_ADDR,
  DVD_FILEINFO,
  DVD_IMPLEMENTED_EFFECTS,
  DVD_IMPLEMENTED_SYMBOLS,
  DVD_NO_BEHAVIOURAL_CLAIM,
  DVD_STATE,
  DvdHost,
  dvdTieredCoverage,
  registerDvdAdapters,
  type DvdImplTier,
  type DvdPendingCallback,
  type DvdReadRecord,
} from "./adapters.js";

export {
  DVD_BRIDGED_GAME_CALL_SITES,
  DVD_CALL_INVENTORY,
  DVD_GAME_CALL_SITES,
  DVD_MMIO_INVENTORY,
  dvdCoverage,
  dvdInventoryEntry,
  type HleInventoryEntry,
  type HleMmioEntry,
} from "./inventory.generated.js";
