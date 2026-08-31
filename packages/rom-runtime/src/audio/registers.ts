// =============================================================================
// registers.ts — the AI / DSP hardware registers, and why audio is not a call
// surface.
//
// THE CENTRAL FINDING OF THE AUDIO INVENTORY, stated here because it shapes
// every design decision in this directory. It is the audio twin of the
// write-gather-pipe finding in docs/gx-hle-host.md §3:
//
//   Gotcha Force does not produce audio by calling an SDK function. Of the 40
//   static game-code call sites in the whole audio family, only SIX cross the
//   SDK seam (`gnt4_ARQInit_bl`, `gnt4___OSInitAudioSystem_bl`,
//   `gnt4___OSStopAudioSystem_bl` x2, `gnt4_OSGetSoundMode_bl`,
//   `gnt4_OSSetSoundMode_bl`). The other 34 call AI/AR functions that are
//   COMPILED INTO THE ROM WINDOW — `AIInit`, `AIInitDMA`, `AIStartDMA`,
//   `ARInit`, `ARAlloc` and friends are ordinary ROM code, not gnt4_*-prefixed,
//   so the port compiles them into the module rather than excluding them.
//
//   Those functions reach the hardware by STORING TO MEMORY-MAPPED REGISTERS,
//   which the decompiler renders as `DAT_cc006c00 = ...`. The measurement
//   counts 18 such registers, 403 static reads and 342 static writes. The
//   composed module's linear memory is 0x807A0000 bytes, so a literal store to
//   0xCC006C00 is out of bounds and traps — exactly the situation 0xCC008000
//   put the GX half in.
//
//   A host that intercepts only AUDIO FUNCTION CALLS therefore never sees a
//   single sample.
//
// AND THE PART THAT CANNOT BE FIXED BY MORE ADAPTERS. The registers above are
// the DAC's DMA engine and the DSP's mailbox. The actual MIXING — voices,
// pitch, panning, ADPCM decode, the whole synthesiser — happens inside MusyX
// microcode executing on the GameCube's DSP, which is not PowerPC code and is
// not in the DOL's text at all; it is a binary blob uploaded over the mailbox
// at 0xCC005000. The corpus shows the ROM doing exactly that: `zz_0217dd8_`
// @0x80217dd8 writes the command word 0xBABE0180 to the mailbox and spins
// until the DSP consumes it, then hands the DAC the buffer the DSP just filled
// (`AIInitDMA(&DAT_803db100 + n*0xa0, 0x280)`).
//
//   So this host can carry a buffer of PCM to the speakers faithfully, and it
//   cannot fill that buffer, because there is nothing here to translate. That
//   is reported as `DSP_MICROCODE_ABSENT` on every report, and it is the
//   single largest gap in the audio half — see docs/audio-dvd-hle-host.md.
//
// PROVENANCE. [CORPUS] means the fact is a read or a write the ROM's own
// decompiled body performs, with the function named. [SDK] means it comes from
// the GameCube hardware's documented register layout. Bit positions that carry
// no [CORPUS] citation are [SDK] and the host does nothing with them.
// =============================================================================

/** Every MMIO address this host claims. A store outside these traps loudly. */
export const AI_WINDOW = { lo: 0xcc006c00, hi: 0xcc006c0f } as const;
export const DSP_WINDOW = { lo: 0xcc005000, hi: 0xcc00503f } as const;

/** AI (audio interface) control register.
 *  [CORPUS] read/written 29+21 times, by `AIInit`, `AISetStreamPlayState`,
 *  `AISetDSPSampleRate`, `__AI_SRC_INIT` and the interrupt handlers. */
export const AI_AICR = 0xcc006c00;
/** AI volume register. [CORPUS] `zz_0214994_` writes bits 0-7,
 *  `AISetStreamVolLeft` (see the naming note below) writes bits 8-15. */
export const AI_AIVR = 0xcc006c04;
/** AI sample counter. [CORPUS] `__AI_SRC_INIT` spins on it to measure the
 *  sample clock, and the streaming interrupt handler passes it to the
 *  registered callback. */
export const AI_AISCNT = 0xcc006c08;
/** AI interrupt timing. [CORPUS] `AIInit` zeroes it. */
export const AI_AIIT = 0xcc006c0c;

/** DSP mailbox, CPU -> DSP, high and low halves.
 *  [CORPUS] `zz_021c664_` @0x8021c664 writes the pair as one u32;
 *  `zz_021c62c_` @0x8021c62c reads bit 15 of the high half as "still full". */
export const DSP_MBOX_OUT_HI = 0xcc005000;
export const DSP_MBOX_OUT_LO = 0xcc005002;
/** DSP mailbox, DSP -> CPU. [CORPUS] `zz_021c63c_`/`zz_021c64c_`. */
export const DSP_MBOX_IN_HI = 0xcc005004;
export const DSP_MBOX_IN_LO = 0xcc005006;
/** DSP control/status. [CORPUS] `zz_021c678_` (DSPInit) and the AI DMA
 *  interrupt handler `FUN_80214bd4` both mask bits here. */
export const DSP_CSR = 0xcc00500a;

/** ARAM DMA registers. [CORPUS] `gnt4_ARStartDMA` writes all three. */
export const AR_DMA_MMADDR = 0xcc005020;
export const AR_DMA_ARADDR = 0xcc005024;
export const AR_DMA_CNT = 0xcc005028;

/** AI DMA start address, high and low halves — these live in the DSP block,
 *  not the AI block, which is a real hardware quirk and not a typo.
 *  [CORPUS] `AIInitDMA` @0x80214634:
 *      DAT_cc005030 = old & 0xfc00 | (addr >> 16)
 *      DAT_cc005032 = old & 0x001f | (u16)addr
 *  so the register pair holds a 26-bit PHYSICAL address with the low 5 bits
 *  forced to zero — 32-byte alignment — and the 0x80000000 cached-region bit
 *  of the PowerPC address falls off in the mask. */
export const AI_DMA_ADDR_HI = 0xcc005030;
export const AI_DMA_ADDR_LO = 0xcc005032;
/** AI DMA length, in 32-byte units, with the enable in bit 15.
 *  [CORPUS] `AIInitDMA` writes `old & 0x8000 | (len >> 5)`;
 *  `AIStartDMA` @0x802146bc sets bit 15 and nothing else. */
export const AI_DMA_CNT = 0xcc005036;

/** [CORPUS] `AIInitDMA` masks the high half with 0xfc00, leaving 10 bits. */
export const AI_DMA_ADDR_HI_MASK = 0x03ff;
/** [CORPUS] `AIInitDMA` masks the low half with 0x001f, clearing 5 bits. */
export const AI_DMA_ADDR_LO_MASK = 0xffe0;
/** [CORPUS] `AIStartDMA` sets exactly this bit. */
export const AI_DMA_ENABLE = 0x8000;
/** [SDK] The DMA length register counts 32-byte blocks. Confirmed by the
 *  ROM's own shift: `param_2 >> 5`. */
export const AI_DMA_UNIT_BYTES = 32;

/** [SDK] AICR bit 0: stream (DMA) play state. [CORPUS] `zz_02147ac_` reads it. */
export const AICR_PSTAT = 1 << 0;
/** [SDK] AICR bit 1: stream sample rate, 0 = 32 kHz, 1 = 48 kHz.
 *  [CORPUS] `zz_0214984_` returns `(AICR >> 1) & 1`. */
export const AICR_AISFR = 1 << 1;
/** [SDK] AICR bit 3: write-1-to-clear the AI streaming interrupt.
 *  [CORPUS] the streaming handler `FUN_80214b58` sets exactly this bit. */
export const AICR_AIINT = 1 << 3;
/** [SDK] AICR bit 5: sample-counter reset. [CORPUS] set-and-cleared all over
 *  `__AI_SRC_INIT` and `AIInit` (`old & 0xffffffdf | 0x20`). */
export const AICR_SCRESET = 1 << 5;
/** [SDK] AICR bit 6: DSP sample rate, 0 = 32 kHz, 1 = 48 kHz.
 *  [CORPUS] `AIGetDSPSampleRate` returns `(AICR >> 6) & 1`, and `AIInit`
 *  calls `AISetDSPSampleRate(0)` — so THIS GAME runs the DSP mixer at 32 kHz.
 *  That is a measured fact about Gotcha Force, not an SDK default. */
export const AICR_DSPFR = 1 << 6;

/** [SDK] The two rates AICR selects between. */
export const AI_SAMPLE_RATE_32KHZ = 32000;
export const AI_SAMPLE_RATE_48KHZ = 48000;

/**
 * Which registers this host does something ABOUT, as opposed to merely storing.
 *
 * Reported next to the measured MMIO inventory so the difference is a number
 * rather than a reading exercise. A register that is only stored still
 * round-trips correctly through the ROM's read-modify-write sequences — which
 * is why nothing crashes — but its hardware effect does not happen.
 */
export const MODELLED_WITH_EFFECT: ReadonlyArray<{ register: number; effect: string }> = [
  { register: 0xcc005030, effect: "AI DMA address, high half — reassembled into the transfer address" },
  { register: 0xcc005032, effect: "AI DMA address, low half" },
  { register: 0xcc005036, effect: "AI DMA length + enable — the 0->1 edge STARTS a transfer" },
  { register: 0xcc005000, effect: "DSP mailbox out, high half — busy bit reads back clear (null DSP)" },
  { register: 0xcc005002, effect: "DSP mailbox out, low half — completes the command word, which is recorded" },
  { register: 0xcc005004, effect: "DSP mailbox in — always reads empty, because no DSP ever posts" },
  { register: 0xcc006c00, effect: "AICR — SCRESET zeroes the sample counter; DSPFR selects 32/48 kHz" },
  { register: 0xcc006c04, effect: "AIVR — decoded into the per-channel output gain" },
  { register: 0xcc006c08, effect: "AISCNT — advanced by every completed transfer" },
];

/**
 * Registers the corpus touches that this host STORES AND NOTHING ELSE.
 *
 * The big one is the ARAM DMA trio. ARAM is where MusyX keeps its sample pool
 * ([CORPUS] `zz_00f18fc_` allocates 0xd00000 of it), and 0xCC005020/24/28 are
 * how samples get there. This host models ARAM as a byte array but does not
 * run its DMA engine, so a transfer into it is accepted and does not happen.
 * Nothing here exercises that yet — the mixer that would read those samples is
 * absent anyway — but it is a gap, not a nop, and it is named as one.
 */
export const STORAGE_ONLY: ReadonlyArray<{ register: number; gap: string }> = [
  { register: 0xcc005020, gap: "ARAM DMA main-memory address — transfers are NOT performed" },
  { register: 0xcc005024, gap: "ARAM DMA ARAM address — transfers are NOT performed" },
  { register: 0xcc005028, gap: "ARAM DMA length/enable — transfers are NOT performed" },
  { register: 0xcc00500a, gap: "DSP control/status — reset, halt and interrupt bits have no effect" },
  { register: 0xcc005006, gap: "DSP mailbox in, low half — no DSP writes it" },
  { register: 0xcc005012, gap: "DSP/ARAM size and mode bits, unmodelled" },
  { register: 0xcc005016, gap: "DSP/ARAM size and mode bits, unmodelled" },
  { register: 0xcc00501a, gap: "ARAM size register read by ARInit — unmodelled, so ARInit sizes nothing" },
  { register: 0xcc006c0c, gap: "AIIT interrupt timing — the host's DMA interrupt is not timed" },
];

export class AudioRegisterError extends Error {
  constructor(message: string) {
    super(`AI/DSP registers: ${message}`);
    this.name = "AudioRegisterError";
  }
}

/**
 * THE NAMING TRAP, recorded so the next reader does not walk into it.
 *
 * The corpus symbol names for the AI family come from this project's rename
 * pipeline, and TWO OF THEM ARE DEMONSTRABLY WRONG AGAINST THEIR OWN BODIES:
 *
 *   0x802149b0 `AIGetStreamPlayState`  is  `{ return AIVR & 0xff; }`
 *              — that is AIGetStreamVolLeft. The real play state is
 *                `zz_02147ac_` @0x802147ac, `{ return AICR & 1; }`.
 *   0x802149c0 `AISetStreamVolLeft`    is  `{ AIVR = (v & 0xff) << 8 | ...; }`
 *              — bits 8-15, which is AISetStreamVolRight. The left setter is
 *                `zz_0214994_` @0x80214994.
 *
 * Nothing in this host keys off those names: adapters and register decode key
 * off ADDRESSES and off what the body does. This table exists so a reader who
 * greps for `AISetStreamVolLeft` finds the correction instead of trusting it.
 */
export const AI_SYMBOL_NAME_CORRECTIONS: ReadonlyArray<{
  romAddr: number;
  corpusName: string;
  actualBehaviour: string;
}> = [
  {
    romAddr: 0x802149b0,
    corpusName: "AIGetStreamPlayState",
    actualBehaviour: "reads AIVR bits 0-7 — this is AIGetStreamVolLeft, not a play state",
  },
  {
    romAddr: 0x802149c0,
    corpusName: "AISetStreamVolLeft",
    actualBehaviour: "writes AIVR bits 8-15 — this is AISetStreamVolRight",
  },
  {
    romAddr: 0x802147ac,
    corpusName: "zz_02147ac_",
    actualBehaviour: "reads AICR bit 0 — THIS is AIGetStreamPlayState",
  },
  {
    romAddr: 0x80214994,
    corpusName: "zz_0214994_",
    actualBehaviour: "writes AIVR bits 0-7 — THIS is AISetStreamVolLeft",
  },
  {
    romAddr: 0x802145f0,
    corpusName: "zz_02145f0_",
    actualBehaviour: "stores its argument into DAT_8043662c, the pointer the AI DMA interrupt handler " +
      "calls — this is AIRegisterDMACallback, the entry point the whole audio path hangs off",
  },
];

/** One recorded register access, for the ledger and the evidence file. */
export interface RegisterAccess {
  addr: number;
  width: 16 | 32;
  value: number;
  kind: "load" | "store";
}

/**
 * The register file.
 *
 * It is a plain address->value store PLUS the few side effects the hardware
 * really has: setting the DMA enable bit starts a transfer, clearing SCRESET
 * zeroes the sample counter, and a mailbox write is consumed immediately by a
 * DSP that is not there. Everything else is storage, which is exactly what the
 * ROM's read-modify-write sequences need.
 */
export class AudioRegisterFile {
  /** Register storage, address -> current value (16- or 32-bit as written). */
  readonly cells = new Map<number, number>();
  /** Every access, in order. Bounded so a long run cannot exhaust memory. */
  readonly accesses: RegisterAccess[] = [];
  /** How many accesses were dropped from `accesses` after the cap. */
  droppedAccesses = 0;
  /** Words the ROM sent to a DSP that is not there, in order. */
  readonly dspMailbox: number[] = [];
  /** Raised when the DMA enable bit goes 0 -> 1. */
  onDmaStart: ((physAddr: number, byteLength: number) => void) | null = null;

  static readonly ACCESS_CAP = 4096;

  #dmaWasEnabled = false;

  inWindow(addr: number): boolean {
    const a = addr >>> 0;
    return (a >= AI_WINDOW.lo && a <= AI_WINDOW.hi) || (a >= DSP_WINDOW.lo && a <= DSP_WINDOW.hi);
  }

  #note(access: RegisterAccess): void {
    if (this.accesses.length < AudioRegisterFile.ACCESS_CAP) this.accesses.push(access);
    else this.droppedAccesses += 1;
  }

  /** Read a register. Unknown addresses inside the window read as 0 rather
   *  than throwing, because the ROM legitimately reads registers it never
   *  wrote (read-modify-write); an address OUTSIDE the window throws. */
  load(addr: number, width: 16 | 32): number {
    const a = addr >>> 0;
    if (!this.inWindow(a)) {
      throw new AudioRegisterError(
        `load u${width} from 0x${a.toString(16)} is outside the AI (0x${AI_WINDOW.lo.toString(16)}..) and ` +
          `DSP (0x${DSP_WINDOW.lo.toString(16)}..) windows this host owns. Refusing to invent a value: a ` +
          `register this host does not model is a hardware block it does not model.`,
      );
    }
    let value = this.cells.get(a) ?? 0;
    // [CORPUS] `zz_021c62c_` spins on `(MBOX_OUT_HI >> 15) != 0` waiting for
    // the DSP to consume the command. A DSP that is not there consumes it
    // instantly, so the busy bit reads back clear and the ROM's loop exits.
    // Leaving it set would hang the module — the one failure mode worse than
    // silence.
    if (a === DSP_MBOX_OUT_HI) value &= 0x7fff;
    // [CORPUS] `zz_021c63c_` reads bit 15 of MBOX_IN_HI as "the DSP posted
    // something". It never does, so this stays clear.
    if (a === DSP_MBOX_IN_HI) value &= 0x7fff;
    this.#note({ addr: a, width, value, kind: "load" });
    return width === 16 ? value & 0xffff : value >>> 0;
  }

  /** Write a register, then run whatever the hardware would do about it. */
  store(addr: number, width: 16 | 32, value: number): void {
    const a = addr >>> 0;
    if (!this.inWindow(a)) {
      throw new AudioRegisterError(
        `store u${width} 0x${(value >>> 0).toString(16)} to 0x${a.toString(16)} is outside the AI and DSP ` +
          `windows this host owns. Refusing to swallow it: a store to an unmodelled register is a silent ` +
          `hardware effect, which is the failure this seam exists to prevent.`,
      );
    }
    const masked = width === 16 ? value & 0xffff : value >>> 0;
    this.cells.set(a, masked);
    this.#note({ addr: a, width, value: masked, kind: "store" });

    if (a === DSP_MBOX_OUT_LO || a === DSP_MBOX_OUT_HI) {
      const hi = (this.cells.get(DSP_MBOX_OUT_HI) ?? 0) & 0xffff;
      const lo = (this.cells.get(DSP_MBOX_OUT_LO) ?? 0) & 0xffff;
      // [CORPUS] `zz_021c664_` writes hi then lo; the low write completes the
      // command word, so that is where the (absent) DSP consumes it.
      if (a === DSP_MBOX_OUT_LO) this.dspMailbox.push(((hi << 16) | lo) >>> 0);
    }

    if (a === AI_AICR && (masked & AICR_SCRESET) !== 0) {
      // [SDK] SCRESET zeroes the sample counter. [CORPUS] `__AI_SRC_INIT`
      // relies on the counter advancing after it does this.
      this.cells.set(AI_AISCNT, 0);
    }

    if (a === AI_DMA_CNT) {
      const enabled = (masked & AI_DMA_ENABLE) !== 0;
      if (enabled && !this.#dmaWasEnabled) {
        const hi = (this.cells.get(AI_DMA_ADDR_HI) ?? 0) & AI_DMA_ADDR_HI_MASK;
        const lo = (this.cells.get(AI_DMA_ADDR_LO) ?? 0) & AI_DMA_ADDR_LO_MASK;
        const physAddr = ((hi << 16) | lo) >>> 0;
        const bytes = (masked & 0x7fff) * AI_DMA_UNIT_BYTES;
        this.onDmaStart?.(physAddr, bytes);
      }
      this.#dmaWasEnabled = enabled;
    }
  }

  /** [CORPUS] `AIGetDSPSampleRate` @0x8021489c returns `(AICR >> 6) & 1`, and
   *  the ROM's `AIInit` selects 0. */
  dspSampleRate(): number {
    return ((this.cells.get(AI_AICR) ?? 0) & AICR_DSPFR) !== 0 ? AI_SAMPLE_RATE_48KHZ : AI_SAMPLE_RATE_32KHZ;
  }

  /** [CORPUS] AIVR bits 0-7 are left, bits 8-15 right. Normalized to 0..1. */
  volumes(): { left: number; right: number } {
    const v = this.cells.get(AI_AIVR) ?? 0;
    return { left: (v & 0xff) / 255, right: ((v >> 8) & 0xff) / 255 };
  }

  /** Advance the sample counter the DAC would have advanced. */
  advanceSampleCounter(frames: number): void {
    this.cells.set(AI_AISCNT, (((this.cells.get(AI_AISCNT) ?? 0) + frames) >>> 0) & 0x7fffffff);
  }
}

/**
 * Turn the DMA register pair's 26-bit physical address back into the PowerPC
 * address the ROM passed to `AIInitDMA`.
 *
 * [CORPUS] The ROM calls `AIInitDMA(&DAT_803db100 + n*0xa0, 0x280)`, i.e. a
 * 0x8xxxxxxx cached address, and `AIInitDMA`'s own masking drops the top bits.
 * Re-adding 0x80000000 is therefore not an assumption about where the buffer
 * lives; it is the inverse of a mask the ROM's body performs in front of us.
 */
export function physToGcAddress(physAddr: number): number {
  return (0x80000000 | (physAddr >>> 0)) >>> 0;
}
