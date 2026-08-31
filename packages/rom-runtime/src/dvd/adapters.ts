// =============================================================================
// adapters.ts — the DVD entry points as bridged-callee host adapters.
//
// This is the SDK seam for disc access (design V2 F2 / step 11). The whole
// gnt4_* family is excluded from porting, so EVERY DVD call a composed module
// makes is an out-of-window call that crosses the H2 bridge and lands here.
// The measurement in inventory.generated.ts says so precisely: all 41 static
// game-code DVD call sites are `bridged` and none is `in-window`, which makes
// the DVD half a pure call surface — unlike GX (write-gather pipe) and unlike
// audio (AI/DSP registers), both of which also have an MMIO seam.
//
// EVIDENCE CLASS: every adapter here is "synthetic".
// The command-block and file-info field offsets below are read out of the
// ROM's own decompiled bodies, which is the strongest evidence available in
// this repo — and it is still not a comparison against console behaviour. No
// DVD trace has been captured, no read has been checked against what the drive
// actually returned, and the timing model (§ below) is knowingly wrong. The
// AdapterRegistry therefore refuses these unless the host was explicitly
// opened for pilot work.
//
// LOUDNESS RULE (task-normative, copied from the GX host): an entry point this
// host does not implement gets an adapter that THROWS, naming the symbol, its
// ROM address and its rank in the measured inventory. It never returns
// quietly. A silent no-op in an asset-loading seam produces a buffer full of
// zeroes that the game then parses as a model, which is strictly worse than a
// failed load.
//
// THE TIMING MODEL IS DELIBERATELY, LOUDLY WRONG. A real DVD read takes
// milliseconds and the ROM spins on `DVDGetCommandBlockStatus` while it does.
// This host completes every read INSIDE the adapter call and leaves the
// command block already in state 0, so those spin loops exit on their first
// iteration. That is a real behavioural divergence — any ROM code that uses
// the wait as a frame-pacing device will run differently — and it is reported
// as the `DVD_READS_COMPLETE_SYNCHRONOUSLY` diagnostic on every report rather
// than being left for a reader to discover.
// =============================================================================

import { defineAdapter, type BridgedCallContext, type BridgedCalleeAdapter } from "../adapters.js";
import { gcAddressForSymbol } from "../composed.js";
import { FrameValueClass } from "../frame.js";
import type { GcMemory } from "../memory.js";
import { DVD_READ_ALIGN, DvdDiscError, type DiscImage } from "./disc.js";
import { DVD_CALL_INVENTORY, dvdCoverage, dvdInventoryEntry } from "./inventory.generated.js";

/** The evidence string every DVD adapter carries. One shared, unflattering
 *  sentence on purpose: per-adapter prose would let one of them read as if
 *  something had been verified. */
const DVD_EVIDENCE =
  "DVD API semantics + decompiled ROM bodies (research/decomp/ghidra-export). " +
  "NO trace capture, NO comparison against a real drive, and reads complete synchronously — " +
  "scaffolding, see docs/audio-dvd-hle-host.md";

/** Repeated verbatim everywhere this host reports anything. */
export const DVD_NO_BEHAVIOURAL_CLAIM =
  "NONE. Every DVD adapter is a synthetic stand-in written from the SDK's semantics and the ROM's own " +
  "decompiled bodies; no read this path performs has ever been compared against a real GameCube drive, " +
  "the disc it reads is not the game's disc unless an owner supplies one, and its timing model is known " +
  "to be wrong (reads complete inside the call). This is scaffolding — see docs/audio-dvd-hle-host.md.";

// =============================================================================
// The structures the ROM and the host share, field by field, from the corpus
// =============================================================================

/**
 * DVDCommandBlock, 0x30 bytes.
 *
 * [CORPUS] Every offset here is a read or a write performed by the ROM's own
 * decompiled SDK, indexed as `param_1[N]` (word N) in
 * `gnt4_DVDReadAbsAsyncPrio_bl` @0x8020f380 and read back in
 * `gnt4_DVDGetCommandBlockStatus_bl` @0x8020f7d0 and `zz_020d728_` @0x8020d728.
 */
export const DVD_CB = {
  /** word 0/1: the waiting-queue links. Host writes zero; nothing reads them. */
  NEXT: 0x00,
  PREV: 0x04,
  /** word 2: command. [CORPUS] DVDReadAbsAsyncPrio writes 1, ...ForBS writes 4. */
  COMMAND: 0x08,
  /** word 3: state. [CORPUS] DVDGetCommandBlockStatus returns this word. */
  STATE: 0x0c,
  /** word 4: disc offset. [CORPUS] `param_1[4] = param_4`. */
  OFFSET: 0x10,
  /** word 5: length. [CORPUS] `param_1[5] = param_3`. */
  LENGTH: 0x14,
  /** word 6: destination address in GC memory. [CORPUS] `param_1[6] = param_2`. */
  ADDR: 0x18,
  /** word 7: current transfer size. [CORPUS] read by `zz_020d728_`. */
  CURR_TRANSFER: 0x1c,
  /** word 8: transferred size. [CORPUS] DVDReadPrio RETURNS `param_9[8]`. */
  TRANSFERRED: 0x20,
  /** word 9: DVDDiskID pointer for the id commands. */
  ID: 0x24,
  /** word 10: completion callback. [CORPUS] `param_1[10] = param_5`. */
  CALLBACK: 0x28,
  /** word 11: tail padding to 0x30. */
  RESERVED: 0x2c,
  BYTES: 0x30,
} as const;

/**
 * DVDFileInfo = { DVDCommandBlock cb; u32 startAddr; u32 length; u32 callback; }
 *
 * [CORPUS] `gnt4_DVDOpen_bl` @0x8020d1ec writes +0x30, +0x34 and +0x38 of its
 * fileInfo argument, and `gnt4_DVDReadPrio_bl` @0x8020d5ec reads them back as
 * `param_9[0xc]` (startAddr) and `param_9[0xd]` (length). The ROM's own file
 * layer confirms the same two offsets from the other side: `FUN_802754ec`
 * reads `handle + 0x5c` (= fileInfo + 0x34) as the file's size.
 */
export const DVD_FILEINFO = {
  START_ADDR: 0x30,
  LENGTH: 0x34,
  CALLBACK: 0x38,
  BYTES: 0x3c,
} as const;

/**
 * Command-block states.
 *
 * [CORPUS] The values are pinned by two independent readers in the corpus:
 * `gnt4_DVDReadPrio_bl` treats `!= 0` as still-running, `-1` as fatal and `10`
 * as canceled; `gnt4_DVDGetCommandBlockStatus_bl` maps 3 to 1; and the game's
 * own file driver `zz_0274dd4_` @0x80274dd4 branches on exactly `0` (success),
 * `< 0` (error) and `== 10` (short/canceled).
 */
export const DVD_STATE = {
  END: 0,
  BUSY: 1,
  WAITING: 2,
  /** Mapped to BUSY by DVDGetCommandBlockStatus. [CORPUS] */
  COVER_CLOSED: 3,
  CANCELED: 10,
  FATAL_ERROR: -1,
} as const;

/** [CORPUS] `gnt4_DVDGetCurrentDiskID_bl` @0x8020fc74 returns the constant
 *  0x80000000 — the disk ID lives at the very start of main memory, where the
 *  apploader put it. Nothing here fabricates an ID; the host only has to make
 *  that address readable. */
export const DVD_DISK_ID_ADDR = 0x80000000;

// =============================================================================
// The host
// =============================================================================

/** What each implemented entry point does to the frame. Same vocabulary as the
 *  GX host so a reader who knows one knows both. */
export type DvdImplTier = "translated" | "latched" | "declared-nop";

/** One completion callback the ROM registered, waiting to be delivered. */
export interface DvdPendingCallback {
  /** The ROM function pointer the SDK would have called. */
  readonly callbackAddr: number;
  /** First argument: the read's result (bytes transferred, or a negative error). */
  readonly result: number;
  /** Second argument: the command block the callback belongs to. */
  readonly blockAddr: number;
  /** Which entry point queued it. */
  readonly source: string;
}

/** One completed read, for assertions and evidence. */
export interface DvdReadRecord {
  symbol: string;
  blockAddr: number;
  discOffset: number;
  length: number;
  destAddr: number;
  transferred: number;
  /** FNV-1a of the bytes delivered — a cheap identity for the evidence file. */
  digest: string;
}

function fnv1a(bytes: Uint8Array): string {
  let h = 0x811c9dc5;
  for (const b of bytes) {
    h ^= b;
    h = Math.imul(h, 0x01000193) >>> 0;
  }
  return `fnv1a:${h.toString(16).padStart(8, "0")}`;
}

/**
 * The DVD host: a disc, the reads it has performed, and the completion
 * callbacks it owes the ROM.
 */
export class DvdHost {
  readonly disc: DiscImage;
  readonly reads: DvdReadRecord[] = [];
  readonly diagnostics: string[] = [];
  /** Entry points that were called but are not implemented, in call order. */
  readonly unimplementedHits: string[] = [];
  /** Every DVD call this host serviced, symbol -> count. */
  readonly callCounts = new Map<string, number>();
  /** Completions queued by async reads, oldest first. */
  readonly pending: DvdPendingCallback[] = [];
  /** Files the ROM asked for that the disc does not have. */
  readonly missingPaths: string[] = [];
  /** [CORPUS] `gnt4_DVDSetAutoInvalidation` @0x8020f8c8 is a plain setter over
   *  DAT_80435cbc, and the ROM reads it back before every read to decide
   *  whether to DCInvalidateRange. The host has no D-cache, so the flag is
   *  recorded and returned faithfully and acted on not at all. */
  autoInvalidation = 0;
  #mem: GcMemory | null;

  constructor(disc: DiscImage, mem: GcMemory | null = null) {
    this.disc = disc;
    this.#mem = mem;
    this.diagnostics.push(
      "DVD_READS_COMPLETE_SYNCHRONOUSLY: every read finishes inside its adapter call and the command " +
        "block is already in state END when the ROM first polls it. Real hardware takes milliseconds. " +
        "ROM code that uses the wait as pacing will run differently here.",
    );
    this.diagnostics.push(`DVD_DISC_PROVENANCE: ${disc.id}`);
  }

  /** Bind the arena after the worker reports `ready`. */
  attachMemory(mem: GcMemory): void {
    this.#mem = mem;
  }

  get mem(): GcMemory {
    if (!this.#mem) {
      throw new DvdDiscError("no GC arena bound — call DvdHost.attachMemory before servicing DVD calls");
    }
    return this.#mem;
  }

  record(symbol: string): void {
    this.callCounts.set(symbol, (this.callCounts.get(symbol) ?? 0) + 1);
  }

  /** Read a NUL-terminated latin-1 path out of the arena. */
  readPath(addr: number): string {
    const mem = this.mem;
    let end = addr >>> 0;
    // A path this long is a mis-marshalled pointer, not a path.
    const limit = (addr >>> 0) + 512;
    while (end < limit && mem.readU8(end) !== 0) end += 1;
    if (end >= limit) {
      throw new DvdDiscError(
        `path argument at 0x${(addr >>> 0).toString(16)} has no NUL in 512 bytes — ` +
          `this is a mis-marshalled pointer, not a filename`,
      );
    }
    return new TextDecoder("latin1").decode(mem.readBytes(addr >>> 0, end - (addr >>> 0)));
  }

  /** Zero a command block and put it in the WAITING state the SDK's async
   *  entry points leave it in before the drive picks it up. */
  initBlock(blockAddr: number, command: number, offset: number, length: number, dest: number, callback: number): void {
    const mem = this.mem;
    mem.writeU32(blockAddr + DVD_CB.NEXT, 0);
    mem.writeU32(blockAddr + DVD_CB.PREV, 0);
    mem.writeU32(blockAddr + DVD_CB.COMMAND, command);
    mem.writeI32(blockAddr + DVD_CB.STATE, DVD_STATE.WAITING);
    mem.writeU32(blockAddr + DVD_CB.OFFSET, offset);
    mem.writeU32(blockAddr + DVD_CB.LENGTH, length);
    mem.writeU32(blockAddr + DVD_CB.ADDR, dest);
    mem.writeU32(blockAddr + DVD_CB.CURR_TRANSFER, 0);
    mem.writeU32(blockAddr + DVD_CB.TRANSFERRED, 0);
    mem.writeU32(blockAddr + DVD_CB.CALLBACK, callback);
  }

  /**
   * Perform one disc read into the arena and complete its command block.
   *
   * Returns the byte count transferred, or a negative SDK error. The read is
   * performed here rather than queued: see the timing note at the top of this
   * file, which is also emitted as a diagnostic.
   */
  completeRead(symbol: string, blockAddr: number, dest: number, length: number, discOffset: number): number {
    const mem = this.mem;
    if ((length & (DVD_READ_ALIGN - 1)) !== 0) {
      // [SDK] the API contract is a 32-byte-aligned length. The ROM's own file
      // driver rounds up before every call (`len + 0x1f & 0xffffffe0`), so an
      // unaligned length reaching here means the caller is not the driver and
      // the assumption should be re-examined, not papered over.
      this.diagnostics.push(
        `DVD_UNALIGNED_LENGTH: ${symbol} asked for ${length} bytes, which is not a multiple of ` +
          `${DVD_READ_ALIGN}. The SDK requires 32-byte alignment; serving it anyway.`,
      );
    }
    const available = Math.max(0, Math.min(length, this.disc.byteLength - discOffset));
    let bytes: Uint8Array;
    try {
      bytes = this.disc.read(discOffset, available);
    } catch (error) {
      mem.writeI32(blockAddr + DVD_CB.STATE, DVD_STATE.FATAL_ERROR);
      this.diagnostics.push(`DVD_READ_FAILED: ${symbol} @0x${discOffset.toString(16)}+${length}: ${String(error)}`);
      return -1;
    }
    mem.writeBytes(dest, bytes);
    if (available < length) {
      // The SDK zero-fills nothing; the ROM's driver does it itself
      // ([CORPUS] `zz_0274dd4_` memsets the tail past the file's end). Leaving
      // the tail untouched here is what the drive does, so it is what we do —
      // but say so, because a partly-filled buffer is exactly the failure this
      // host must not hide.
      this.diagnostics.push(
        `DVD_SHORT_READ: ${symbol} wanted ${length} bytes at 0x${discOffset.toString(16)} but the disc ` +
          `has ${available}. The tail of the destination buffer was left untouched, as the drive would.`,
      );
    }
    mem.writeU32(blockAddr + DVD_CB.CURR_TRANSFER, available);
    mem.writeU32(blockAddr + DVD_CB.TRANSFERRED, available);
    mem.writeI32(blockAddr + DVD_CB.STATE, DVD_STATE.END);
    this.reads.push({
      symbol,
      blockAddr: blockAddr >>> 0,
      discOffset,
      length,
      destAddr: dest >>> 0,
      transferred: available,
      digest: fnv1a(bytes),
    });
    const callback = mem.readU32(blockAddr + DVD_CB.CALLBACK);
    if (callback !== 0) {
      this.pending.push({ callbackAddr: callback, result: available, blockAddr: blockAddr >>> 0, source: symbol });
    }
    return available;
  }

  /**
   * Hand every queued completion callback to a deliverer and clear the queue.
   *
   * DELIVERY SHAPE (design R3, and the same mechanism `RomRuntimeHost.postEvent`
   * exists for): a GameCube DVD completion arrives as an INTERRUPT, so it must
   * not be delivered from inside the adapter that queued it — the ROM is on the
   * stack there. It is delivered at a worker PARK POINT as an invoke-request,
   * which is what `postEvent` publishes. This method is the seam between the
   * two: the host owns the queue, the caller owns the transport.
   */
  drainCallbacks(deliver: (pending: DvdPendingCallback) => void): number {
    const n = this.pending.length;
    while (this.pending.length > 0) deliver(this.pending.shift() as DvdPendingCallback);
    return n;
  }

  coverage(): ReturnType<typeof dvdTieredCoverage> {
    return dvdTieredCoverage();
  }

  report(): {
    behaviouralClaim: string;
    verified: false;
    disc: string;
    coverage: ReturnType<typeof dvdTieredCoverage>;
    calls: Array<{ symbol: string; count: number }>;
    reads: DvdReadRecord[];
    pendingCallbacks: number;
    missingPaths: string[];
    unimplementedHits: string[];
    diagnostics: string[];
  } {
    return {
      behaviouralClaim: DVD_NO_BEHAVIOURAL_CLAIM,
      verified: false,
      disc: this.disc.id,
      coverage: this.coverage(),
      calls: [...this.callCounts.entries()].sort((a, b) => b[1] - a[1]).map(([symbol, count]) => ({ symbol, count })),
      reads: [...this.reads],
      pendingCallbacks: this.pending.length,
      missingPaths: [...this.missingPaths],
      unimplementedHits: [...this.unimplementedHits],
      diagnostics: [...this.diagnostics],
    };
  }
}

// =============================================================================
// Adapter specs
// =============================================================================

interface DvdAdapterSpec {
  symbol: string;
  tier: DvdImplTier;
  retClass: FrameValueClass;
  /** What it does, and how much of it. Read next to the tier, never instead. */
  effect: string;
  service: (dvd: DvdHost, ctx: BridgedCallContext) => number;
}

/**
 * ARGUMENT INDICES AND THE GHOST FLOAT SLOTS.
 *
 * Ghidra renders these SDK entry points with eight leading `undefined8`
 * parameters — `param_1`..`param_8`. Those are not real arguments: they are
 * the decompiler's record of the PowerPC EABI's f1..f8 float-register slots,
 * which a varargs-shaped prototype makes visible. The REAL arguments start at
 * `param_9`. Every call site in the corpus agrees:
 *
 *   [CORPUS] `gnt4_DVDOpen_bl(uVar6, p2..p8, local_118, (int)(__s + 0x28), ...)`
 *            — the path is param_9, the fileInfo is param_10.
 *
 * The ROM-unit fixture keeps the decompiled prototype verbatim so the wasm
 * import signature is the ROM's, which means the frame really does carry eight
 * i64 slots before the first useful argument. `A9`/`A10` name that offset once,
 * here, instead of a bare `8` appearing in a dozen adapters.
 *
 * Entry points the corpus shows with a NARROW prototype (`DVDClose(int *)`,
 * `DVDGetCommandBlockStatus(int)`, `DVDReadAbsAsyncPrio(...6 args)`) take
 * their arguments from slot 0 — those are noted per adapter.
 */
const A9 = 8;
const A10 = 9;

const SPECS: DvdAdapterSpec[] = [
  {
    // [CORPUS] `gnt4_DVDGetCommandBlockStatus_bl` @0x8020f7d0 is
    // `{ int s = *(int *)(cb + 0xc); if (s == 3) s = 1; return s; }` — a
    // narrow one-argument function; the block pointer is slot 0.
    symbol: "gnt4_DVDGetCommandBlockStatus_bl",
    tier: "translated",
    retClass: FrameValueClass.I32,
    effect:
      "returns the command block's state word (cb+0x0c), mapping COVER_CLOSED(3) to BUSY(1) exactly as " +
      "the ROM's own body does. Because this host completes reads inside the read call, the state is " +
      "already END(0) the first time the ROM polls — the divergence named in DVD_READS_COMPLETE_SYNCHRONOUSLY",
    service(dvd, ctx) {
      const block = ctx.frame.u32Arg(0) >>> 0;
      const state = dvd.mem.readI32(block + DVD_CB.STATE);
      return ctx.frame.setRetI32(state === DVD_STATE.COVER_CLOSED ? DVD_STATE.BUSY : state);
    },
  },
  {
    // [CORPUS] `gnt4_DVDGetDriveStatus_bl` @0x8020f81c returns 0 when no
    // command is in flight, 8 when paused, -1 when fatal, and otherwise the
    // current block's state. The host has no drive state machine, so it
    // reports the only condition it can ever be in: idle.
    symbol: "gnt4_DVDGetDriveStatus_bl",
    tier: "translated",
    retClass: FrameValueClass.I32,
    effect:
      "returns DVD_STATE_END(0) — 'drive idle, nothing queued'. This host never has a command in flight " +
      "when the ROM asks, because reads complete inside their own call, so 0 is the accurate answer to " +
      "the question the ROM is asking rather than a placeholder",
    service: (_dvd, ctx) => ctx.frame.setRetI32(DVD_STATE.END),
  },
  {
    // [CORPUS] `gnt4_DVDCheckDisk_bl` @0x8020fc7c returns 1 when the drive is
    // idle-or-paused AND the DI status register shows no cover-open / no
    // error. A host disc is never ejected.
    symbol: "gnt4_DVDCheckDisk_bl",
    tier: "translated",
    retClass: FrameValueClass.I32,
    effect: "returns 1 (a disc is present and readable). The host's disc cannot be ejected or fail",
    service: (_dvd, ctx) => ctx.frame.setRetI32(1),
  },
  {
    symbol: "gnt4_DVDInit_bl",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect:
      "brings up the drive's interrupt handler, waiting queues and FST pointers. The host has no drive " +
      "and holds its FST as parsed objects rather than at DAT_80436524/8, so there is nothing to " +
      "initialize. A nop BY MODEL, declared as one, not a gap",
    service: (_dvd, ctx) => ctx.frame.setRetVoid(),
  },
  {
    symbol: "gnt4_HSD_DVDInit",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect: "HAL's wrapper over DVDInit; same reasoning",
    service: (_dvd, ctx) => ctx.frame.setRetVoid(),
  },
  {
    symbol: "gnt4_DVDOpen_bl",
    tier: "translated",
    retClass: FrameValueClass.I32,
    effect:
      "resolves the path against the disc's FST and writes startAddr(+0x30), length(+0x34) and " +
      "callback(+0x38) into the caller's DVDFileInfo, returning 1 on success and 0 on a missing path " +
      "or a directory — the ROM's own body, field for field",
    service(dvd, ctx) {
      const pathAddr = ctx.frame.u32Arg(A9);
      const fileInfo = ctx.frame.u32Arg(A10) >>> 0;
      const path = dvd.readPath(pathAddr);
      const entrynum = dvd.disc.entrynumForPath(path);
      if (entrynum < 0) {
        dvd.missingPaths.push(path);
        // [CORPUS] the ROM's DVDOpen OSReports a warning and returns 0 here.
        // Returning 0 (rather than throwing) is the ROM's OWN contract, and
        // the caller checks it — so this is not a silent failure: the path is
        // recorded, reported, and the ROM takes its own error branch.
        return ctx.frame.setRetI32(0);
      }
      const entry = dvd.disc.fst[entrynum];
      if (!entry || entry.isDir) {
        dvd.missingPaths.push(`${path} (directory)`);
        return ctx.frame.setRetI32(0);
      }
      const mem = dvd.mem;
      mem.writeU32(fileInfo + DVD_FILEINFO.START_ADDR, entry.startAddr);
      mem.writeU32(fileInfo + DVD_FILEINFO.LENGTH, entry.length);
      mem.writeU32(fileInfo + DVD_FILEINFO.CALLBACK, 0);
      // [CORPUS] DVDOpen also clears the command block's state word (+0x0c).
      mem.writeI32(fileInfo + DVD_CB.STATE, DVD_STATE.END);
      return ctx.frame.setRetI32(1);
    },
  },
  {
    // [CORPUS] `gnt4_DVDClose_bl` @0x8020d2b4 is literally
    // `{ gnt4_DVDCancel_bl(param_1); return 1; }` — narrow, one argument.
    symbol: "gnt4_DVDClose_bl",
    tier: "translated",
    retClass: FrameValueClass.I32,
    effect:
      "cancels any in-flight command on the file's block and returns 1, exactly as the ROM's two-line " +
      "body does. Nothing is 'closed': a DVDFileInfo is caller-owned memory",
    service(dvd, ctx) {
      const fileInfo = ctx.frame.u32Arg(0) >>> 0;
      dvd.mem.writeI32(fileInfo + DVD_CB.STATE, DVD_STATE.END);
      return ctx.frame.setRetI32(1);
    },
  },
  {
    symbol: "gnt4_DVDCancel_bl",
    tier: "translated",
    retClass: FrameValueClass.I32,
    effect:
      "puts the block in state END and returns 1. Nothing can be in flight to cancel, because reads " +
      "complete inside their own call",
    service(dvd, ctx) {
      const block = ctx.frame.u32Arg(0) >>> 0;
      dvd.mem.writeI32(block + DVD_CB.STATE, DVD_STATE.END);
      return ctx.frame.setRetI32(1);
    },
  },
  {
    symbol: "gnt4_DVDReadPrio_bl",
    tier: "translated",
    retClass: FrameValueClass.I32,
    effect:
      "the SYNCHRONOUS file read. Bounds-checks (offset, length) against the file's own length the way " +
      "the ROM's body does, reads from startAddr+offset into GC memory, and returns the transferred " +
      "byte count from cb+0x20 — which is the word the ROM's own body returns (`param_9[8]`)",
    service(dvd, ctx) {
      const fileInfo = ctx.frame.u32Arg(A9) >>> 0;
      const dest = ctx.frame.u32Arg(A10) >>> 0;
      const length = ctx.frame.i32Arg(A10 + 1);
      const offset = ctx.frame.i32Arg(A10 + 2);
      const mem = dvd.mem;
      const fileLength = mem.readU32(fileInfo + DVD_FILEINFO.LENGTH);
      const startAddr = mem.readU32(fileInfo + DVD_FILEINFO.START_ADDR);
      // [CORPUS] the ROM panics on (offset < 0 || offset >= length) and on
      // (offset+length < 0 || offset+length >= length + 0x20). Throwing is the
      // host's equivalent of the panic: refusing is the point.
      if (offset < 0 || offset >= fileLength || length < 0 || offset + length >= fileLength + 0x20) {
        throw new DvdDiscError(
          `DVDRead(): specified area is out of the file — offset ${offset}, length ${length}, ` +
            `file length ${fileLength}. The ROM's own body OSPanics here (gnt4_DVDReadPrio_bl @0x8020d5ec)`,
        );
      }
      dvd.initBlock(fileInfo, 1, startAddr + offset, length, dest, 0);
      const n = dvd.completeRead("gnt4_DVDReadPrio_bl", fileInfo, dest, length, startAddr + offset);
      return ctx.frame.setRetI32(n);
    },
  },
  {
    // [CORPUS] `gnt4_DVDReadAbsAsyncPrio_bl` @0x8020f380 has a NARROW
    // six-argument prototype: (block, addr, length, offset, callback, prio).
    symbol: "gnt4_DVDReadAbsAsyncPrio_bl",
    tier: "translated",
    retClass: FrameValueClass.I32,
    effect:
      "the ABSOLUTE async read: fills the command block's command/addr/length/offset/callback words " +
      "with the same six writes the ROM's body performs, performs the read, and QUEUES the completion " +
      "callback for delivery at a worker park point (DvdHost.drainCallbacks). Returns 1 (queued)",
    service(dvd, ctx) {
      const block = ctx.frame.u32Arg(0) >>> 0;
      const dest = ctx.frame.u32Arg(1) >>> 0;
      const length = ctx.frame.i32Arg(2);
      const offset = ctx.frame.u32Arg(3) >>> 0;
      const callback = ctx.frame.u32Arg(4) >>> 0;
      dvd.initBlock(block, 1, offset, length, dest, callback);
      dvd.completeRead("gnt4_DVDReadAbsAsyncPrio_bl", block, dest, length, offset);
      return ctx.frame.setRetI32(1);
    },
  },
  {
    symbol: "gnt4_DVDSetAutoInvalidation",
    tier: "latched",
    retClass: FrameValueClass.I32,
    effect:
      "records the flag and returns the previous value, which is all the ROM's own one-line body does. " +
      "LATCHED, not translated: the flag decides whether the SDK invalidates the D-cache before a read, " +
      "and this host has no D-cache to invalidate, so the value is stored and never acted on",
    service(dvd, ctx) {
      const previous = dvd.autoInvalidation;
      dvd.autoInvalidation = ctx.frame.i32Arg(0);
      return ctx.frame.setRetI32(previous);
    },
  },
  {
    symbol: "gnt4_DVDGetCurrentDiskID_bl",
    tier: "translated",
    retClass: FrameValueClass.I32,
    effect:
      "returns 0x80000000, the constant the ROM's own body returns — the disk ID the apploader left at " +
      "the base of main memory. The host does not fabricate an ID; a caller that dereferences this gets " +
      "whatever is in the arena there, which is what a caller would get on console before boot wrote it",
    service: (_dvd, ctx) => ctx.frame.setRetI32(DVD_DISK_ID_ADDR | 0),
  },
  {
    symbol: "gnt4_DVDResume_bl",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect: "un-pauses the drive's command queue. There is no queue to un-pause",
    service: (_dvd, ctx) => ctx.frame.setRetVoid(),
  },
];

/** Symbols this host implements — the numerator of the coverage figure. */
export const DVD_IMPLEMENTED_SYMBOLS: readonly string[] = SPECS.map((s) => s.symbol);

/** What each implemented entry point actually does, and how much. */
export const DVD_IMPLEMENTED_EFFECTS: ReadonlyArray<{ symbol: string; tier: DvdImplTier; effect: string }> = SPECS.map(
  (s) => ({ symbol: s.symbol, tier: s.tier, effect: s.effect }),
);

/**
 * Coverage split by tier. The honest headline is `translated`. `latched` and
 * `declared-nop` are reported NEXT TO it, never merged into it — collapsing
 * them into one "implemented" number is exactly how a seam talks itself into
 * sounding finished.
 */
export function dvdTieredCoverage(): {
  translated: ReturnType<typeof dvdCoverage>;
  translatedAndLatched: ReturnType<typeof dvdCoverage>;
  all: ReturnType<typeof dvdCoverage>;
  byTier: Record<DvdImplTier, number>;
} {
  const of = (tiers: DvdImplTier[]): string[] => SPECS.filter((s) => tiers.includes(s.tier)).map((s) => s.symbol);
  const byTier = { translated: 0, latched: 0, "declared-nop": 0 } as Record<DvdImplTier, number>;
  for (const s of SPECS) byTier[s.tier] += 1;
  return {
    translated: dvdCoverage(of(["translated"])),
    translatedAndLatched: dvdCoverage(of(["translated", "latched"])),
    all: dvdCoverage(of(["translated", "latched", "declared-nop"])),
    byTier,
  };
}

// =============================================================================
// Registration
// =============================================================================

function adapterFor(dvd: DvdHost, spec: DvdAdapterSpec, gcAddr: number): BridgedCalleeAdapter {
  const entry = dvdInventoryEntry(spec.symbol);
  return defineAdapter({
    gcAddr,
    name: spec.symbol,
    evidence: `${DVD_EVIDENCE} [rank by game call sites: ${entry?.gameCalls ?? 0}]`,
    evidenceClass: "synthetic",
    retClass: spec.retClass,
    service(ctx) {
      dvd.record(spec.symbol);
      return spec.service(dvd, ctx);
    },
  });
}

function unimplementedAdapter(dvd: DvdHost, symbol: string, gcAddr: number): BridgedCalleeAdapter {
  const entry = dvdInventoryEntry(symbol);
  return defineAdapter({
    gcAddr,
    name: `${symbol} [UNIMPLEMENTED]`,
    evidence: `not implemented by the DVD HLE host; ${entry?.gameCalls ?? 0} static ROM call sites`,
    evidenceClass: "synthetic",
    retClass: FrameValueClass.VOID,
    service(_ctx) {
      dvd.unimplementedHits.push(symbol);
      throw new Error(
        `DVD entry point ${symbol} is NOT IMPLEMENTED by the HLE host ` +
          `(ROM address 0x${(entry?.romAddr ?? 0).toString(16)}, ${entry?.gameCalls ?? 0} static ROM call sites, ` +
          `${entry?.distinctGameCallers ?? 0} distinct callers). ` +
          `Refusing to no-op: a silent no-op here hands the game a buffer of zeroes it will parse as an ` +
          `asset. Implement it in packages/rom-runtime/src/dvd/adapters.ts or accept the failed load.`,
      );
    },
  });
}

/**
 * Register the whole measured DVD surface on a host.
 *
 * EVERY entry point in the inventory gets an adapter — implemented ones do
 * their work, the rest throw with their name and rank. Nothing in the DVD
 * surface can be hit without the ledger and the console saying so.
 *
 * Each adapter is bound at TWO keys, for the same reason the GX host does it:
 * the SYNTHETIC key `gcAddressForSymbol` produces (the direct-import bridge
 * edge for an address-less `gnt4_*` symbol) and the symbol's REAL GameCube
 * address (what a table-miss edge carries if the ROM ever dispatches a DVD
 * function through a stored pointer).
 */
export function registerDvdAdapters(
  host: { registerAdapter(adapter: BridgedCalleeAdapter): void },
  dvd: DvdHost,
): { implemented: number; unimplemented: number; registrations: number } {
  let registrations = 0;
  const bind = (adapter: BridgedCalleeAdapter, symbol: string): void => {
    host.registerAdapter(adapter);
    registrations += 1;
    const romAddr = dvdInventoryEntry(symbol)?.romAddr;
    if (romAddr && romAddr !== adapter.gcAddr) {
      host.registerAdapter({ ...adapter, gcAddr: romAddr >>> 0 });
      registrations += 1;
    }
  };

  const implemented = new Set(DVD_IMPLEMENTED_SYMBOLS);
  for (const spec of SPECS) {
    bind(adapterFor(dvd, spec, gcAddressForSymbol(spec.symbol).gcAddr), spec.symbol);
  }
  let unimplemented = 0;
  for (const entry of DVD_CALL_INVENTORY) {
    if (implemented.has(entry.symbol)) continue;
    unimplemented += 1;
    bind(unimplementedAdapter(dvd, entry.symbol, gcAddressForSymbol(entry.symbol).gcAddr), entry.symbol);
  }
  return { implemented: SPECS.length, unimplemented, registrations };
}
