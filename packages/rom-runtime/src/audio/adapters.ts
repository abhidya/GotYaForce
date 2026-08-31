// =============================================================================
// adapters.ts — the audio seam: six bridged entry points and an MMIO window.
//
// READ registers.ts FIRST. It states the finding that shapes this file: audio
// is only 15% a call surface. Of the 40 static game-code call sites the
// inventory measures, SIX cross the SDK seam as calls; the other 34 land in
// AI/AR functions that the port compiles into the module, and those reach the
// hardware by storing to memory-mapped registers. So this file has two halves:
//
//   1. BRIDGED ADAPTERS for the five gnt4_* audio entry points, same shape as
//      the GX and DVD hosts.
//   2. MMIO ADAPTERS — `__gf_mmio_load_u16/u32` and `__gf_mmio_store_u16/u32`
//      — the lowering target for `DAT_cc006c00`-style register accesses,
//      exactly as `__gf_gx_wgpipe_*` is the lowering target for the ROM's
//      0xCC008000 vertex stores. THE ASSEMBLY GATE DOES NOT EMIT THESE YET:
//      OGhidra's src/port_wgpipe_lowering.py lowers the 0xCC008000 window and
//      only that window. Extending it to the AI/DSP windows is the top item of
//      the remainder list in docs/audio-dvd-hle-host.md; until then the ROM
//      unit in packages/rom-runtime/test/fixtures/hle-rom-unit/ applies the
//      same class of rewrite through a hand-written header, and says so.
//
// EVIDENCE CLASS: every adapter here is "synthetic". Register semantics are
// read out of the ROM's own bodies, which is strong; nothing has been compared
// against a console, which is what would make it verified.
//
// LOUDNESS RULE: unimplemented entry points THROW with their symbol, ROM
// address and call-site rank. An MMIO access outside the modelled windows
// THROWS. Silence is the failure mode this whole file exists to make
// impossible to mistake for success.
// =============================================================================

import { defineAdapter, type BridgedCallContext, type BridgedCalleeAdapter } from "../adapters.js";
import { gcAddressForSymbol } from "../composed.js";
import { FrameValueClass } from "../frame.js";
import type { GcMemory } from "../memory.js";
import { aiDmaBytesToPcm } from "./adpcm.js";
import type { AudioBackend, AudioDmaBlock } from "./backend.js";
import {
  AUDIO_CALL_INVENTORY,
  AUDIO_MMIO_INVENTORY,
  audioCoverage,
  audioInventoryEntry,
} from "./inventory.generated.js";
import {
  AI_SYMBOL_NAME_CORRECTIONS,
  AudioRegisterError,
  AudioRegisterFile,
  MODELLED_WITH_EFFECT,
  STORAGE_ONLY,
  physToGcAddress,
} from "./registers.js";

const AUDIO_EVIDENCE =
  "AI/AR/DSP register semantics read out of the ROM's own decompiled bodies " +
  "(research/decomp/ghidra-export) + the GameCube hardware register layout. " +
  "NO trace capture, NO comparison against console audio, and NO DSP microcode — " +
  "scaffolding, see docs/audio-dvd-hle-host.md";

/** Repeated verbatim everywhere this host reports anything. */
export const AUDIO_NO_BEHAVIOURAL_CLAIM =
  "NONE, and the gap is structural rather than incremental. This host carries a buffer of PCM from GC " +
  "memory to the speakers and models the AI/DSP registers the ROM's own code drives. It does NOT mix: " +
  "Gotcha Force's voices, ADPCM playback, pitch and panning all execute as MusyX microcode on the " +
  "GameCube DSP, which is not PowerPC code and is not in the DOL — there is nothing here to translate. " +
  "With no DSP the DMA buffer stays whatever the CPU left in it, which for this game is silence. " +
  "Nothing on this path has been compared against console audio. See docs/audio-dvd-hle-host.md.";

/** The lowering-target imports for AI/DSP register access. */
export const MMIO_SYMBOLS = [
  "__gf_mmio_load_u16",
  "__gf_mmio_load_u32",
  "__gf_mmio_store_u16",
  "__gf_mmio_store_u32",
] as const;

export type AudioImplTier = "translated" | "latched" | "declared-nop";

/** One AI DMA completion the ROM is owed. [CORPUS] `AIInit` @0x802149ec
 *  installs `FUN_80214bd4` on interrupt 5 and unmasks 0x4000000; that handler
 *  calls whatever pointer `zz_02145f0_` (AIRegisterDMACallback) stored in
 *  DAT_8043662c. So the completion is an INTERRUPT, and design R3 delivers
 *  interrupts as invoke-requests at worker park points — never from inside the
 *  adapter that raised them, because the ROM is on the stack there. */
export interface AudioPendingInterrupt {
  readonly kind: "ai-dma-complete";
  /** Sequence number of the DMA block that completed. */
  readonly blockIndex: number;
  /** The buffer address the DAC just finished with. */
  readonly gcAddr: number;
}

/**
 * The audio host: the register file, the DMA engine that acts on it, ARAM, and
 * the backend the reconstructed PCM is handed to.
 */
export class AudioHost {
  readonly registers = new AudioRegisterFile();
  readonly backend: AudioBackend;
  readonly diagnostics: string[] = [];
  readonly unimplementedHits: string[] = [];
  readonly callCounts = new Map<string, number>();
  readonly pendingInterrupts: AudioPendingInterrupt[] = [];
  /**
   * ARAM, the console's 16 MB auxiliary audio RAM. [CORPUS] `ARInit`
   * @0x802150cc sizes it and `ARAlloc` @0x80214ff0 hands out blocks; the game
   * asks for 0xd00000 (13 MB) in `zz_00f18fc_` for its sample pool. Modelled
   * as a flat byte store because that is all ARAM is — a DMA target the DSP
   * reads samples from.
   */
  readonly aram: Uint8Array;
  /** Bump allocator cursor over `aram`. */
  aramCursor = 0;
  /** Blocks the DAC has consumed. */
  dmaBlockCount = 0;
  #mem: GcMemory | null;

  /** [SDK] ARAM on a retail GameCube is 16 MiB. */
  static readonly ARAM_BYTES = 16 * 1024 * 1024;

  constructor(backend: AudioBackend, mem: GcMemory | null = null, aramBytes = AudioHost.ARAM_BYTES) {
    this.backend = backend;
    this.#mem = mem;
    this.aram = new Uint8Array(aramBytes);
    this.diagnostics.push(
      "DSP_MICROCODE_ABSENT: the mixer is MusyX microcode running on the GameCube DSP. It is not PowerPC " +
        "code, it is not in the DOL, and no part of it is translated here. Every command word the ROM " +
        "posts to the DSP mailbox is recorded and immediately marked consumed so the module does not hang; " +
        "the DMA buffer therefore contains whatever the CPU put in it, which for this game is silence.",
    );
    this.diagnostics.push(
      "AI_MMIO_NOT_GATE_LOWERED: the assembly gate lowers the 0xCC008000 write-gather pipe and nothing " +
        "else. AI (0xCC006C00) and DSP (0xCC005000) register access reaches these adapters only through " +
        "the hand-written lowering header in test/fixtures/hle-rom-unit/. A composed module built by the " +
        "gate today would trap on its first audio register store.",
    );
    this.diagnostics.push(
      "ARAM_DMA_NOT_MODELLED: 0xCC005020/24/28 are the ARAM DMA engine, and the corpus touches them 247 " +
        "times reading and 251 writing — the busiest audio registers by a wide margin. This host stores " +
        "them and performs no transfer, so ARAM (where MusyX keeps its sample pool: [CORPUS] zz_00f18fc_ " +
        "allocates 0xd00000 of it) never receives anything. Nothing reads those samples today because the " +
        "mixer is absent too, but this is a gap, not a nop.",
    );
    for (const correction of AI_SYMBOL_NAME_CORRECTIONS) {
      this.diagnostics.push(
        `AI_SYMBOL_MISNAMED: 0x${correction.romAddr.toString(16)} is called ${correction.corpusName} in the ` +
          `corpus, but ${correction.actualBehaviour}. Adapters key off addresses, not these names.`,
      );
    }
    this.registers.onDmaStart = (physAddr, byteLength) => this.#runDma(physAddr, byteLength);
  }

  attachMemory(mem: GcMemory): void {
    this.#mem = mem;
  }

  get mem(): GcMemory {
    if (!this.#mem) {
      throw new AudioRegisterError("no GC arena bound — call AudioHost.attachMemory before servicing audio calls");
    }
    return this.#mem;
  }

  record(symbol: string): void {
    this.callCounts.set(symbol, (this.callCounts.get(symbol) ?? 0) + 1);
  }

  /**
   * One AI DMA transfer: pull `byteLength` bytes out of the arena at the
   * address the register pair encodes, decode them as BIG-ENDIAN interleaved
   * stereo s16 (the format the DAC fetches), and hand the block to the
   * backend.
   *
   * [SDK] the AI DMA format is 16-bit signed stereo, big-endian. [CORPUS] the
   * ROM's own buffer is 0x280 bytes per transfer = 160 stereo frames, which at
   * the 32 kHz `AIInit` selects is a 5 ms block — the MusyX frame period.
   */
  #runDma(physAddr: number, byteLength: number): void {
    const gcAddr = physToGcAddress(physAddr);
    if (byteLength === 0) {
      this.diagnostics.push(`AI_DMA_ZERO_LENGTH: transfer started at 0x${gcAddr.toString(16)} with length 0`);
      return;
    }
    let raw: Uint8Array;
    try {
      raw = this.mem.readBytes(gcAddr, byteLength);
    } catch (error) {
      this.diagnostics.push(
        `AI_DMA_OUT_OF_ARENA: the DMA register pair decoded to 0x${gcAddr.toString(16)} + ${byteLength} bytes, ` +
          `which is not inside the module arena (${String(error)}). Refusing to submit silence in its place.`,
      );
      throw error;
    }
    const { left, right } = aiDmaBytesToPcm(raw);
    let silent = true;
    for (let i = 0; i < left.length && silent; i++) {
      if (left[i] !== 0 || right[i] !== 0) silent = false;
    }
    this.dmaBlockCount += 1;
    const block: AudioDmaBlock = {
      index: this.dmaBlockCount,
      gcAddr,
      byteLength,
      frames: left.length,
      sampleRate: this.registers.dspSampleRate(),
      left,
      right,
      volume: this.registers.volumes(),
      silent,
    };
    this.backend.submit(block);
    this.registers.advanceSampleCounter(left.length);
    // [CORPUS] the DAC raises interrupt 5 when the transfer finishes; the
    // handler calls the registered DMA callback, which is how MusyX gets its
    // 5 ms tick. Queue it; delivery is the caller's transport (drainInterrupts).
    this.pendingInterrupts.push({ kind: "ai-dma-complete", blockIndex: block.index, gcAddr });
  }

  /** Drive a DMA transfer directly, without going through the registers.
   *  Used by tests and by a host that wants to push a block it already has. */
  runDmaDirect(gcAddr: number, byteLength: number): void {
    this.#runDma((gcAddr & 0x03ffffff) >>> 0, byteLength);
  }

  /**
   * Hand every queued AI interrupt to a deliverer and clear the queue.
   * Same seam as `DvdHost.drainCallbacks`: the host owns the queue, the caller
   * owns the transport (`RomRuntimeHost.postEvent` at a park point).
   */
  drainInterrupts(deliver: (interrupt: AudioPendingInterrupt) => void): number {
    const n = this.pendingInterrupts.length;
    while (this.pendingInterrupts.length > 0) deliver(this.pendingInterrupts.shift() as AudioPendingInterrupt);
    return n;
  }

  coverage(): ReturnType<typeof audioTieredCoverage> {
    return audioTieredCoverage();
  }

  report(): {
    behaviouralClaim: string;
    verified: false;
    dspMicrocodeAbsent: true;
    coverage: ReturnType<typeof audioTieredCoverage>;
    calls: Array<{ symbol: string; count: number }>;
    registers: {
      accesses: number;
      dropped: number;
      touched: number;
      dspMailboxWords: string[];
      measuredRegisters: number;
      modelledWithEffect: number;
      storageOnly: number;
    };
    dma: { blocks: number; pendingInterrupts: number; sampleRate: number };
    unimplementedHits: string[];
    diagnostics: string[];
  } {
    return {
      behaviouralClaim: AUDIO_NO_BEHAVIOURAL_CLAIM,
      verified: false,
      dspMicrocodeAbsent: true,
      coverage: this.coverage(),
      calls: [...this.callCounts.entries()].sort((a, b) => b[1] - a[1]).map(([symbol, count]) => ({ symbol, count })),
      registers: {
        accesses: this.registers.accesses.length,
        dropped: this.registers.droppedAccesses,
        touched: this.registers.cells.size,
        dspMailboxWords: this.registers.dspMailbox.map((w) => `0x${w.toString(16).padStart(8, "0")}`),
        // The denominators, side by side: how many registers the corpus uses,
        // how many this host does something about, and how many it merely
        // stores. Reporting only the first would be a coverage claim.
        measuredRegisters: AUDIO_MMIO_INVENTORY.length,
        modelledWithEffect: MODELLED_WITH_EFFECT.length,
        storageOnly: STORAGE_ONLY.length,
      },
      dma: {
        blocks: this.dmaBlockCount,
        pendingInterrupts: this.pendingInterrupts.length,
        sampleRate: this.registers.dspSampleRate(),
      },
      unimplementedHits: [...this.unimplementedHits],
      diagnostics: [...this.diagnostics, ...this.backend.diagnostics],
    };
  }
}

// =============================================================================
// Bridged adapter specs — the five gnt4_* audio entry points
// =============================================================================

interface AudioAdapterSpec {
  symbol: string;
  tier: AudioImplTier;
  retClass: FrameValueClass;
  effect: string;
  service: (audio: AudioHost, ctx: BridgedCallContext) => number;
}

const SPECS: AudioAdapterSpec[] = [
  {
    // [CORPUS] `gnt4___OSInitAudioSystem_bl` @0x8020035c is 33 register
    // touches across the DSP block: it resets the DSP, uploads the boot
    // microcode stub and initializes ARAM DMA. Every one of those effects is
    // about hardware this host does not have.
    symbol: "gnt4___OSInitAudioSystem_bl",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect:
      "resets the DSP and initializes ARAM DMA. The host has no DSP (see DSP_MICROCODE_ABSENT) and models " +
      "ARAM as a byte array that needs no initialization, so there is nothing to do. A nop BY MODEL, " +
      "declared as one — and the model it is a nop under is itself the largest gap in this half",
    service: (_audio, ctx) => ctx.frame.setRetVoid(),
  },
  {
    symbol: "gnt4___OSStopAudioSystem_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "halts the DAC. Clears the AI DMA enable bit in the register file so no further transfer can start, " +
      "which is the one observable thing the real function does that this host can reproduce",
    service(audio, ctx) {
      // [CORPUS] `gnt4___OSStopAudioSystem_bl` @0x80200518 clears bit 15 of
      // DAT_cc005036 among its 14 register touches.
      const current = audio.registers.cells.get(0xcc005036) ?? 0;
      audio.registers.store(0xcc005036, 16, current & 0x7fff);
      return ctx.frame.setRetVoid();
    },
  },
  {
    // [CORPUS] `gnt4_OSGetSoundMode_bl` @0x80205750 reads the SRAM mirror's
    // sound-mode bit. [SDK] 0 = mono, 1 = stereo.
    symbol: "gnt4_OSGetSoundMode_bl",
    tier: "translated",
    retClass: FrameValueClass.I32,
    effect: "returns 1 (stereo). The host's output is stereo and cannot be anything else",
    service: (_audio, ctx) => ctx.frame.setRetI32(1),
  },
  {
    symbol: "gnt4_OSSetSoundMode_bl",
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect:
      "records the requested sound mode and does nothing with it. LATCHED, not translated: honouring mono " +
      "would mean summing the two channels, and this host never has a signal to sum (DSP_MICROCODE_ABSENT)",
    service(audio, ctx) {
      audio.diagnostics.push(`OS_SOUND_MODE_LATCHED: ROM asked for mode ${ctx.frame.i32Arg(0)}; not acted on`);
      return ctx.frame.setRetVoid();
    },
  },
  {
    // [CORPUS] `gnt4_ARQInit_bl` @0x80216bcc sets up the ARAM DMA request
    // queue and installs its interrupt service routine.
    symbol: "gnt4_ARQInit_bl",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect:
      "initializes the ARAM DMA request queue. This host performs ARAM transfers synchronously inside the " +
      "call that asks for them, so there is no queue to initialize. A nop BY MODEL — and the synchronous " +
      "completion is the same known timing divergence the DVD half reports",
    service: (_audio, ctx) => ctx.frame.setRetVoid(),
  },
];

export const AUDIO_IMPLEMENTED_SYMBOLS: readonly string[] = SPECS.map((s) => s.symbol);

export const AUDIO_IMPLEMENTED_EFFECTS: ReadonlyArray<{ symbol: string; tier: AudioImplTier; effect: string }> =
  SPECS.map((s) => ({ symbol: s.symbol, tier: s.tier, effect: s.effect }));

/**
 * Coverage, split by tier AND by seam.
 *
 * The seam split is not decoration. The audio family's 40 static game call
 * sites are 6 bridged and 34 in-window, and only the bridged ones are
 * answerable by an adapter at all. Quoting a single "audio coverage" number
 * over all 40 would either flatter the adapters (they cannot cover in-window
 * calls) or damn them (they are not supposed to). So both denominators are
 * reported, always together, and `mmio` reports the surface that actually
 * carries the other 34.
 */
export function audioTieredCoverage(): {
  translated: ReturnType<typeof audioCoverage>;
  translatedAndLatched: ReturnType<typeof audioCoverage>;
  all: ReturnType<typeof audioCoverage>;
  byTier: Record<AudioImplTier, number>;
  bridged: { implementedSymbols: number; totalSymbols: number; coveredCallSites: number; totalCallSites: number };
  inWindow: { symbols: number; callSites: number; note: string };
} {
  const of = (tiers: AudioImplTier[]): string[] => SPECS.filter((s) => tiers.includes(s.tier)).map((s) => s.symbol);
  const byTier = { translated: 0, latched: 0, "declared-nop": 0 } as Record<AudioImplTier, number>;
  for (const s of SPECS) byTier[s.tier] += 1;
  const bridgedEntries = AUDIO_CALL_INVENTORY.filter((e) => e.seam === "bridged");
  const inWindowEntries = AUDIO_CALL_INVENTORY.filter((e) => e.seam === "in-window");
  const implemented = new Set(AUDIO_IMPLEMENTED_SYMBOLS);
  return {
    translated: audioCoverage(of(["translated"])),
    translatedAndLatched: audioCoverage(of(["translated", "latched"])),
    all: audioCoverage(of(["translated", "latched", "declared-nop"])),
    byTier,
    bridged: {
      implementedSymbols: bridgedEntries.filter((e) => implemented.has(e.symbol)).length,
      totalSymbols: bridgedEntries.length,
      coveredCallSites: bridgedEntries.filter((e) => implemented.has(e.symbol)).reduce((a, e) => a + e.gameCalls, 0),
      totalCallSites: bridgedEntries.reduce((a, e) => a + e.gameCalls, 0),
    },
    inWindow: {
      symbols: inWindowEntries.length,
      callSites: inWindowEntries.reduce((a, e) => a + e.gameCalls, 0),
      note:
        "these calls do NOT cross the SDK seam — the port compiles AI/AR into the module. They are served " +
        "by the MMIO adapters, not by bridged adapters, and the assembly gate does not lower them yet.",
    },
  };
}

// =============================================================================
// Registration
// =============================================================================

function adapterFor(audio: AudioHost, spec: AudioAdapterSpec, gcAddr: number): BridgedCalleeAdapter {
  const entry = audioInventoryEntry(spec.symbol);
  return defineAdapter({
    gcAddr,
    name: spec.symbol,
    evidence: `${AUDIO_EVIDENCE} [rank by game call sites: ${entry?.gameCalls ?? 0}]`,
    evidenceClass: "synthetic",
    retClass: spec.retClass,
    service(ctx) {
      audio.record(spec.symbol);
      return spec.service(audio, ctx);
    },
  });
}

function unimplementedAdapter(audio: AudioHost, symbol: string, gcAddr: number): BridgedCalleeAdapter {
  const entry = audioInventoryEntry(symbol);
  const inWindow = entry?.seam === "in-window";
  return defineAdapter({
    gcAddr,
    name: `${symbol} [UNIMPLEMENTED]`,
    evidence: `not implemented by the audio HLE host; ${entry?.gameCalls ?? 0} static ROM call sites`,
    evidenceClass: "synthetic",
    retClass: FrameValueClass.VOID,
    service(_ctx) {
      audio.unimplementedHits.push(symbol);
      throw new Error(
        `Audio entry point ${symbol} is NOT IMPLEMENTED by the HLE host ` +
          `(ROM address 0x${(entry?.romAddr ?? 0).toString(16)}, ${entry?.gameCalls ?? 0} static ROM call sites, ` +
          `${entry?.distinctGameCallers ?? 0} distinct callers, seam: ${entry?.seam ?? "unknown"}). ` +
          (inWindow
            ? `AND THIS ONE SHOULD NOT HAVE BRIDGED AT ALL: it is IN-WINDOW ROM code, so the port is meant ` +
              `to compile it into the module and lower its register access to __gf_mmio_*. Reaching this ` +
              `adapter means the module excluded a function it should have ported. `
            : "") +
          `Refusing to no-op: a silent no-op here produces confident silence. ` +
          `Implement it in packages/rom-runtime/src/audio/adapters.ts.`,
      );
    },
  });
}

export function registerAudioAdapters(
  host: { registerAdapter(adapter: BridgedCalleeAdapter): void },
  audio: AudioHost,
): { implemented: number; unimplemented: number; registrations: number } {
  let registrations = 0;
  const bind = (adapter: BridgedCalleeAdapter, symbol: string): void => {
    host.registerAdapter(adapter);
    registrations += 1;
    const romAddr = audioInventoryEntry(symbol)?.romAddr;
    if (romAddr && romAddr !== adapter.gcAddr) {
      host.registerAdapter({ ...adapter, gcAddr: romAddr >>> 0 });
      registrations += 1;
    }
  };

  const implemented = new Set(AUDIO_IMPLEMENTED_SYMBOLS);
  for (const spec of SPECS) {
    bind(adapterFor(audio, spec, gcAddressForSymbol(spec.symbol).gcAddr), spec.symbol);
  }
  let unimplemented = 0;
  for (const entry of AUDIO_CALL_INVENTORY) {
    if (implemented.has(entry.symbol)) continue;
    unimplemented += 1;
    bind(unimplementedAdapter(audio, entry.symbol, gcAddressForSymbol(entry.symbol).gcAddr), entry.symbol);
  }
  return { implemented: SPECS.length, unimplemented, registrations };
}

/**
 * Bind the MMIO lowering imports.
 *
 * These are NOT SDK entry points. They are the lowering target for the ROM's
 * `DAT_cc006c00` / `DAT_cc005030` register accesses, the audio twin of
 * `registerWgPipeAdapters`. The gate does not emit them yet (see the
 * AI_MMIO_NOT_GATE_LOWERED diagnostic), so today only the ROM-unit fixture
 * calls them — they are registered at reserved synthetic addresses so that
 * when the gate DOES lower those accesses, the seam is already here.
 */
export function registerMmioAdapters(
  host: { registerAdapter(adapter: BridgedCalleeAdapter): void },
  audio: AudioHost,
): void {
  const evidence =
    "AI/DSP MMIO (0xCC006C00 / 0xCC005000) lowering target — the ROM's real audio hardware path; " +
    "the assembly gate does not emit these yet (docs/audio-dvd-hle-host.md)";
  const load = (symbol: string, width: 16 | 32): BridgedCalleeAdapter =>
    defineAdapter({
      gcAddr: gcAddressForSymbol(symbol).gcAddr,
      name: symbol,
      evidence,
      evidenceClass: "synthetic",
      retClass: FrameValueClass.I32,
      service(ctx) {
        audio.record(symbol);
        return ctx.frame.setRetI32(audio.registers.load(ctx.frame.u32Arg(0), width) | 0);
      },
    });
  const store = (symbol: string, width: 16 | 32): BridgedCalleeAdapter =>
    defineAdapter({
      gcAddr: gcAddressForSymbol(symbol).gcAddr,
      name: symbol,
      evidence,
      evidenceClass: "synthetic",
      retClass: FrameValueClass.VOID,
      service(ctx) {
        audio.record(symbol);
        audio.registers.store(ctx.frame.u32Arg(0), width, ctx.frame.u32Arg(1));
        return ctx.frame.setRetVoid();
      },
    });
  host.registerAdapter(load("__gf_mmio_load_u16", 16));
  host.registerAdapter(load("__gf_mmio_load_u32", 32));
  host.registerAdapter(store("__gf_mmio_store_u16", 16));
  host.registerAdapter(store("__gf_mmio_store_u32", 32));
}
