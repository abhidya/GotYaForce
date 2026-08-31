// =============================================================================
// backend.ts — where decoded AI DMA blocks go, and the two backends.
//
// Split for the same reason the GX half is split (gx/backend.ts): the DECODE
// side — registers, DMA reconstruction, ADPCM — must be assertable without an
// audio device, and the OUTPUT side must be swappable. Both backends implement
// `AudioBackend`; the recording backend is what headless assertions read, the
// WebAudio backend is what actually makes a sound.
// =============================================================================

/** One AI DMA block, after the host has pulled it out of the arena. */
export interface AudioDmaBlock {
  /** Sequence number, from 1. */
  readonly index: number;
  /** The PowerPC address the ROM handed the DAC. */
  readonly gcAddr: number;
  /** Length in bytes, as the length register expressed it. */
  readonly byteLength: number;
  /** Stereo frames in the block (byteLength / 4). */
  readonly frames: number;
  /** [CORPUS] 32000 or 48000, from AICR bit 6. */
  readonly sampleRate: number;
  /** De-interleaved, big-endian-decoded s16 PCM. */
  readonly left: Int16Array;
  readonly right: Int16Array;
  /** AIVR volumes at the moment the transfer started, normalized 0..1. */
  readonly volume: { left: number; right: number };
  /** True when every sample in the block is zero — the expected state while
   *  DSP_MICROCODE_ABSENT holds, and worth saying out loud rather than
   *  discovering by listening. */
  readonly silent: boolean;
}

export interface AudioBackend {
  /** Hand the backend one completed DMA block. */
  submit(block: AudioDmaBlock): void;
  /** Release any device resources. */
  dispose(): void;
  /**
   * Anything the backend could not reproduce faithfully. NEVER empty just
   * because something came out of the speakers: every approximation is
   * expected to name itself here, because the difference between audio that is
   * right and audio that merely plays is exactly this list.
   */
  readonly diagnostics: readonly string[];
}

/** A compact record of one submitted block, for assertions and reports. */
export interface AudioBlockRecord {
  index: number;
  gcAddr: string;
  byteLength: number;
  frames: number;
  sampleRate: number;
  silent: boolean;
  peakLeft: number;
  peakRight: number;
  firstFrame: [number, number] | null;
  volume: { left: number; right: number };
}

function peak(samples: Int16Array): number {
  let p = 0;
  for (const s of samples) {
    const a = s < 0 ? -s : s;
    if (a > p) p = a;
  }
  return p;
}

/**
 * Headless backend: records everything, plays nothing.
 *
 * This is the backend the decode-side assertions run against, and it is also
 * what the WebAudio backend delegates its bookkeeping to, so a headless
 * assertion and an audible buffer are provably looking at the same block
 * stream.
 */
export class AudioRecordingBackend implements AudioBackend {
  readonly records: AudioBlockRecord[] = [];
  readonly blocks: AudioDmaBlock[] = [];
  readonly diagnostics: string[] = [];
  totalFrames = 0;
  silentBlocks = 0;

  submit(block: AudioDmaBlock): void {
    this.blocks.push(block);
    this.totalFrames += block.frames;
    if (block.silent) this.silentBlocks += 1;
    this.records.push({
      index: block.index,
      gcAddr: `0x${block.gcAddr.toString(16)}`,
      byteLength: block.byteLength,
      frames: block.frames,
      sampleRate: block.sampleRate,
      silent: block.silent,
      peakLeft: peak(block.left),
      peakRight: peak(block.right),
      firstFrame: block.frames > 0 ? [block.left[0] as number, block.right[0] as number] : null,
      volume: block.volume,
    });
  }

  dispose(): void {
    /* nothing to release */
  }

  /** JSON-safe summary for the smoke phase and window.__gf reporting. */
  summary(): {
    blocks: number;
    frames: number;
    silentBlocks: number;
    seconds: number;
    diagnostics: string[];
  } {
    const rate = this.blocks[0]?.sampleRate ?? 0;
    return {
      blocks: this.records.length,
      frames: this.totalFrames,
      silentBlocks: this.silentBlocks,
      seconds: rate > 0 ? Math.round((this.totalFrames / rate) * 1000) / 1000 : 0,
      diagnostics: [...this.diagnostics],
    };
  }
}

/**
 * WebAudio backend: schedules each DMA block as an AudioBuffer.
 *
 * WHAT THIS IS NOT. It is not a mixer and it is not a resampler. It receives
 * blocks that are already final stereo PCM — on console the DSP produced them,
 * here whatever wrote the buffer produced them — and hands them to the device
 * back to back. Every place where that differs from a GameCube DAC is listed
 * in `diagnostics` rather than smoothed over:
 *
 *  * SAMPLE RATE. The blocks are 32 kHz ([CORPUS] `AIInit` selects DSPFR=0);
 *    an AudioContext runs at the device rate, usually 44.1 or 48 kHz. The
 *    browser resamples with its own kernel, which is not the DAC's.
 *  * SCHEDULING. Real AI DMA fires an interrupt every 5 ms and the ROM refills
 *    the other half of a double buffer. Here blocks are appended to a
 *    play-cursor; an underrun is a gap, not a repeat of the last block, and it
 *    is counted.
 *  * VOLUME. AIVR is applied as a gain multiply, which is not the DAC's
 *    attenuation curve.
 *
 * This class is DOM-dependent and is never constructed by the headless tests.
 */
export class WebAudioBackend implements AudioBackend {
  readonly recorder = new AudioRecordingBackend();
  readonly diagnostics: string[] = [];
  readonly context: AudioContext;
  readonly gain: GainNode;
  /** Blocks dropped because the context was closed. */
  dropped = 0;
  /** Times the play cursor fell behind wall clock — an audible gap. */
  underruns = 0;
  /** The most recent AudioBuffer handed to the device. Kept so a proof can
   *  assert on the samples the browser was actually given, rather than on the
   *  host's own copy of them — the difference between "the decoder produced
   *  this" and "the audio device received this". */
  lastBuffer: AudioBuffer | null = null;
  #cursor = 0;

  constructor(context: AudioContext) {
    this.context = context;
    this.gain = context.createGain();
    this.gain.connect(context.destination);
    this.diagnostics.push(
      `WEBAUDIO_RESAMPLES: DMA blocks are 32000 Hz and this AudioContext runs at ${context.sampleRate} Hz. ` +
        `The browser's resampler is not the GameCube DAC's.`,
    );
    this.diagnostics.push(
      "WEBAUDIO_SCHEDULING_IS_NOT_DMA: blocks are appended to a play cursor rather than being fetched by a " +
        "DMA engine on a 5 ms interrupt. Underruns become silence, not a repeated block.",
    );
  }

  submit(block: AudioDmaBlock): void {
    this.recorder.submit(block);
    if (this.context.state === "closed") {
      this.dropped += 1;
      return;
    }
    if (block.frames === 0) return;
    const buffer = this.context.createBuffer(2, block.frames, block.sampleRate);
    const l = buffer.getChannelData(0);
    const r = buffer.getChannelData(1);
    for (let i = 0; i < block.frames; i++) {
      l[i] = (block.left[i] as number) / 32768;
      r[i] = (block.right[i] as number) / 32768;
    }
    this.lastBuffer = buffer;
    const source = this.context.createBufferSource();
    source.buffer = buffer;
    source.connect(this.gain);
    const now = this.context.currentTime;
    if (this.#cursor < now) {
      if (this.#cursor > 0) this.underruns += 1;
      this.#cursor = now;
    }
    // AIVR as a plain gain multiply — see the class comment.
    this.gain.gain.setValueAtTime(Math.max(block.volume.left, block.volume.right), this.#cursor);
    source.start(this.#cursor);
    this.#cursor += block.frames / block.sampleRate;
  }

  dispose(): void {
    try {
      this.gain.disconnect();
    } catch {
      /* already torn down */
    }
  }

  summary(): ReturnType<AudioRecordingBackend["summary"]> & {
    contextSampleRate: number;
    contextState: string;
    underruns: number;
    dropped: number;
  } {
    return {
      ...this.recorder.summary(),
      diagnostics: [...this.recorder.summary().diagnostics, ...this.diagnostics],
      contextSampleRate: this.context.sampleRate,
      contextState: this.context.state,
      underruns: this.underruns,
      dropped: this.dropped,
    };
  }
}
