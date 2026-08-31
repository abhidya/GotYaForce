// =============================================================================
// adpcm.ts — Nintendo DSP-ADPCM decode, in TypeScript, for the first time.
//
// WHY THIS FILE IS NEW CODE, stated the way docs/gx-hle-host.md §4.5 had to
// state the same thing about texture decoding:
//
//   The brief for this work assumed a TypeScript ADPCM decoder already existed
//   in the repo to reuse. IT DOES NOT. A repo-wide search for `adpcm` finds
//   exactly one decoder, `decode_dsp_adpcm` in scripts/export-combat-se.py
//   (line 216), which is PYTHON and runs OFFLINE — it is the tool that turned
//   the disc's soundbanks into the OGG files apps/game ships. There is no
//   TypeScript, C#, or WebAssembly decoder anywhere, and there is no ADX
//   decoder either (scripts/export-audio-assets.mjs shells out to ffmpeg).
//   `packages/audio` decodes nothing at all: it constructs HTMLAudioElements
//   over pre-decoded OGGs.
//
// So this is a PORT of that Python function, not a wrapper around an existing
// one, and it is written to be checkable against it rather than merely
// believed: packages/rom-runtime/test/fixtures/adpcm/ holds a vector emitted
// by running the PYTHON decoder, and the unit test decodes the same input here
// and compares sample for sample. That is the strongest form of evidence
// available without console capture — an independent second implementation
// that already produced shipped assets — and it is still not console capture.
//
// ARITHMETIC NOTE, and it matters. The Python reference computes
//     sample = (nibble*scale*2048 + c1*hist1 + c2*hist2 + 1024) >> 11
// where `>>` on a Python int is an ARITHMETIC shift over unbounded precision.
// The intermediate can exceed 2^31 (nibble*scale*2048 alone reaches 2^29 and
// c1*hist1 reaches 2^30), so JavaScript's `>>` — which truncates its operand
// to int32 first — would silently produce different samples for loud input.
// `Math.floor(x / 2048)` is exact for |x| < 2^53 and floors negatives the same
// way an arithmetic shift does, so that is what this file uses. A `>>` here
// would be a real bug that only shows up on loud samples.
// =============================================================================

/** [SDK] One ADPCM frame is a 1-byte header followed by 7 bytes of nibbles. */
export const ADPCM_FRAME_BYTES = 8;
/** [SDK] Those 7 bytes hold 14 4-bit samples. */
export const ADPCM_SAMPLES_PER_FRAME = 14;
/** [SDK] A DSPADPCM (.dsp) header carries 8 coefficient PAIRS = 16 s16. */
export const ADPCM_COEF_COUNT = 16;

export class AdpcmError extends Error {
  constructor(message: string) {
    super(`DSP-ADPCM: ${message}`);
    this.name = "AdpcmError";
  }
}

/** The per-sample decode state the format threads through frames. */
export interface AdpcmState {
  /** Previous sample. [SDK] `yn1` in the DSPADPCM header. */
  hist1: number;
  /** The one before that. [SDK] `yn2`. */
  hist2: number;
}

export interface AdpcmDecodeRequest {
  /** The packed ADPCM bytes (a .dpk member, or a .dsp body). */
  readonly data: Uint8Array;
  /** Byte offset of the first frame header within `data`. */
  readonly offset: number;
  /** How many PCM samples to produce. */
  readonly numSamples: number;
  /** How many 4-bit nibbles the stream holds; bounds the read. */
  readonly numNibbles: number;
  /** The 16 s16 coefficients from the DSPADPCM header, in header order. */
  readonly coefs: ReadonlyArray<number> | Int16Array;
  /** Initial history. Defaults to silence, which is what a sample start is. */
  readonly state?: AdpcmState;
}

/**
 * Decode DSP-ADPCM to signed 16-bit mono PCM.
 *
 * PORTED VERBATIM from `decode_dsp_adpcm` in scripts/export-combat-se.py:216 —
 * same frame walk, same nibble order (high nibble first), same sign extension
 * at 8, same rounding constant 1024, same clamp, same history update. The one
 * intentional difference is `Math.floor(x / 2048)` in place of `>> 11`, for
 * the reason in the file header.
 */
export function decodeDspAdpcm(request: AdpcmDecodeRequest): Int16Array {
  const { data, offset, numSamples, numNibbles, coefs } = request;
  if (coefs.length < ADPCM_COEF_COUNT) {
    throw new AdpcmError(`need ${ADPCM_COEF_COUNT} coefficients, got ${coefs.length}`);
  }
  if (offset < 0 || offset > data.length) {
    throw new AdpcmError(`offset 0x${offset.toString(16)} is outside the ${data.length}-byte stream`);
  }
  const out = new Int16Array(Math.max(0, numSamples));
  let produced = 0;
  let hist1 = request.state?.hist1 ?? 0;
  let hist2 = request.state?.hist2 ?? 0;
  let pos = offset;
  const end = offset + ((numNibbles + 1) >> 1);
  if (end > data.length) {
    throw new AdpcmError(
      `stream claims ${numNibbles} nibbles from 0x${offset.toString(16)}, which runs ` +
        `${end - data.length} bytes past the ${data.length}-byte buffer`,
    );
  }

  while (produced < numSamples && pos < end) {
    const header = data[pos] as number;
    pos += 1;
    const scale = 1 << (header & 0x0f);
    const coefIndex = (header >> 4) * 2;
    if (coefIndex + 1 >= coefs.length) {
      // [SDK] the predictor field selects one of EIGHT coefficient pairs, so a
      // valid stream never encodes 8..15 there. The Python reference throws an
      // IndexError on this input; throwing here keeps the two implementations
      // in agreement about what is NOT decodable, which matters as much as
      // agreeing about what is. Reading past the array would yield NaN and
      // then silently clamp to a plausible-looking sample.
      throw new AdpcmError(
        `frame header 0x${header.toString(16)} selects coefficient pair ${header >> 4}, but only ` +
          `${coefs.length >> 1} pairs exist. This is not a DSP-ADPCM stream, or the offset is wrong.`,
      );
    }
    const c1 = coefs[coefIndex] as number;
    const c2 = coefs[coefIndex + 1] as number;
    for (let i = 0; i < ADPCM_SAMPLES_PER_FRAME; i++) {
      if (produced >= numSamples || pos >= end) break;
      const byte = data[pos] as number;
      let nibble = i % 2 === 0 ? byte >> 4 : byte & 0x0f;
      if (i % 2 === 1) pos += 1;
      if (nibble >= 8) nibble -= 16;
      // Math.floor, not `>>`: see the arithmetic note in the file header.
      let sample = Math.floor((nibble * scale * 2048 + c1 * hist1 + c2 * hist2 + 1024) / 2048);
      if (sample < -32768) sample = -32768;
      else if (sample > 32767) sample = 32767;
      out[produced] = sample;
      produced += 1;
      hist2 = hist1;
      hist1 = sample;
    }
  }
  return produced === out.length ? out : out.subarray(0, produced);
}

/**
 * Read the 16 coefficients out of a 96-byte DSPADPCM header.
 *
 * [SDK] The header is big-endian: numSamples(u32) numNibbles(u32) sampleRate(u32)
 * loopFlag(u16) format(u16) loopStart/End/ca(u32 x3) coef[16](s16) ...
 * [CORPUS-adjacent] scripts/export-combat-se.py reads the same 96-byte block
 * out of a CHD `Dspi` record, at +4 past a u32 dpk byte offset.
 */
export function readDspAdpcmHeader(bytes: Uint8Array, at = 0): {
  numSamples: number;
  numNibbles: number;
  sampleRate: number;
  loopFlag: number;
  format: number;
  coefs: Int16Array;
} {
  if (at + 0x40 > bytes.length) {
    throw new AdpcmError(`DSPADPCM header at 0x${at.toString(16)} needs 64 bytes, buffer has ${bytes.length - at}`);
  }
  const dv = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
  const coefs = new Int16Array(ADPCM_COEF_COUNT);
  for (let i = 0; i < ADPCM_COEF_COUNT; i++) coefs[i] = dv.getInt16(at + 0x1c + i * 2, false);
  return {
    numSamples: dv.getUint32(at + 0x00, false),
    numNibbles: dv.getUint32(at + 0x04, false),
    sampleRate: dv.getUint32(at + 0x08, false),
    loopFlag: dv.getUint16(at + 0x0c, false),
    format: dv.getUint16(at + 0x0e, false),
    coefs,
  };
}

/**
 * Interleave mono PCM into the stereo, BIG-ENDIAN s16 layout the GameCube's
 * audio DMA reads out of main memory.
 *
 * BYTE ORDER, and it is deliberate in both directions — the same distinction
 * docs/gx-hle-host.md §4.2 draws for GX. The DMA buffer is CONSOLE data: the
 * AI hardware fetches it as big-endian s16 pairs. The shared arena is wasm32
 * LINEAR MEMORY: little-endian. So a decoder that produced Int16Array (host
 * order) must be serialized explicitly, never memcpy'd.
 */
export function pcmToAiDmaBytes(left: Int16Array, right: Int16Array = left): Uint8Array {
  const frames = Math.min(left.length, right.length);
  const out = new Uint8Array(frames * 4);
  const dv = new DataView(out.buffer);
  for (let i = 0; i < frames; i++) {
    dv.setInt16(i * 4 + 0, left[i] as number, false);
    dv.setInt16(i * 4 + 2, right[i] as number, false);
  }
  return out;
}

/** The inverse: read an AI DMA block back out as interleaved stereo s16. */
export function aiDmaBytesToPcm(bytes: Uint8Array): { left: Int16Array; right: Int16Array } {
  const frames = bytes.length >> 2;
  const left = new Int16Array(frames);
  const right = new Int16Array(frames);
  const dv = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
  for (let i = 0; i < frames; i++) {
    left[i] = dv.getInt16(i * 4 + 0, false);
    right[i] = dv.getInt16(i * 4 + 2, false);
  }
  return { left, right };
}
