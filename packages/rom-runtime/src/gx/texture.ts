// =============================================================================
// texture.ts — decoding GameCube texture formats out of the shared arena.
//
// WHY THIS IS NEW CODE rather than a reuse. The brief for this work assumed the
// project already decoded GameCube texture formats in TypeScript and asked that
// it be reused. It does not. `packages/formats/src/tpl.ts` deliberately stops
// at container metadata — its own header says "Pixel decode still belongs to
// offline tooling until the runtime needs RGBA" — and the only pixel decoder in
// the repo is a C# `Program.cs` that `scripts/export-ui-assets.mjs` writes out
// and which calls HSDRaw's `GXImageConverter`, a build-time dependency that is
// not even present in this worktree. The runtime now needs RGBA, so this is the
// first TypeScript implementation. `packages/formats/src/tpl.ts` remains the
// right home for TPL *container* parsing and is unchanged; if a second consumer
// ever needs these pixel loops, this module is the thing to lift into
// `@gf/formats`.
//
// WHAT IS SETTLED FROM THE CORPUS. The format numbering and every format's
// texel-block geometry come from this game's own `gnt4_GXInitTexObj_bl`
// (@0x80228b74), which switches on the format and writes both the block-shift
// pair and a bytes-per-texel class for each case — see GXTexFmt in enums.ts.
// So the block sizes below are read off the shipped binary, not from
// documentation.
//
// WHAT IS NOT. The *bit layouts inside* a texel (RGB5A3's two branches, IA4's
// nibble order, CMPR's endpoint and index bit order) are [SDK]: the decompiled
// SDK never touches pixels, because the console's texture units do. Those are
// implemented from the documented GameCube formats and are marked below.
//
// ARENA BYTE ORDER — settled, and it matters here more than anywhere else.
// The arena builder (research/decomp/poc/wasm-port-poc/gen_arena.py) converts
// PER REGION by declared type: `swap4` for u32/f32 regions, `swap2` for s16
// tables, and `raw` — no swap at all — for byte tables (it uses `raw` for the
// unit-B char table today). There is therefore NO global "the arena is
// swapped" rule, which is what docs/gx-hle-host.md §7.4 was asking about:
// four-byte-typed regions are swapped and byte-typed regions are not. Texture
// image data is byte data and MUST be emitted as a `raw` region. This decoder
// reads it as console-order bytes, and `decodeTexture` refuses formats it
// cannot size rather than producing a plausible-looking wrong image.
// =============================================================================

import { GXTexFmt, GXTlutFmt } from "./enums.js";
import type { GcMemory } from "../memory.js";

/** A decoded texture, ready for `texImage2D`. */
export interface GxDecodedTexture {
  width: number;
  height: number;
  /** RGBA8, `width * height * 4` bytes, top row first. */
  rgba: Uint8Array;
  /** GXTexFmt this came from, for reporting. */
  format: number;
  /** Deviations the decode made. Empty means the format was decoded whole. */
  diagnostics: string[];
}

/** Thrown when a texture cannot be decoded. Never swallowed — an undecodable
 *  texture that silently becomes flat colour is a frame that renders wrong. */
export class GxTextureError extends Error {
  constructor(message: string) {
    super(`GX texture: ${message}`);
    this.name = "GxTextureError";
  }
}

/**
 * Texel-block geometry per format. [CORPUS]
 *
 * Straight out of gnt4_GXInitTexObj_bl's switch: the two shifts it computes per
 * case are log2 of the block width and height, and the class byte it stores at
 * the texture object's offset 0x1e is the bytes-per-texel class.
 */
interface BlockGeometry {
  width: number;
  height: number;
  /** Bytes one block occupies in memory. */
  blockBytes: number;
}

const BLOCKS: Partial<Record<number, BlockGeometry>> = {
  [GXTexFmt.I4]: { width: 8, height: 8, blockBytes: 32 },
  [GXTexFmt.I8]: { width: 8, height: 4, blockBytes: 32 },
  [GXTexFmt.IA4]: { width: 8, height: 4, blockBytes: 32 },
  [GXTexFmt.IA8]: { width: 4, height: 4, blockBytes: 32 },
  [GXTexFmt.RGB565]: { width: 4, height: 4, blockBytes: 32 },
  [GXTexFmt.RGB5A3]: { width: 4, height: 4, blockBytes: 32 },
  [GXTexFmt.RGBA8]: { width: 4, height: 4, blockBytes: 64 },
  [GXTexFmt.C4]: { width: 8, height: 8, blockBytes: 32 },
  [GXTexFmt.C8]: { width: 8, height: 4, blockBytes: 32 },
  [GXTexFmt.C14X2]: { width: 4, height: 4, blockBytes: 32 },
  [GXTexFmt.CMPR]: { width: 8, height: 8, blockBytes: 32 },
};

/** Bytes an image of this format and size occupies, block-padded. [CORPUS] —
 *  this is the same arithmetic gnt4_GXGetTexBufferSize_bl performs. */
export function gxImageBytes(format: number, width: number, height: number): number | null {
  const b = BLOCKS[format & 0xff];
  if (!b) return null;
  const bw = Math.ceil(Math.max(width, 1) / b.width);
  const bh = Math.ceil(Math.max(height, 1) / b.height);
  return bw * bh * b.blockBytes;
}

/** Human name for a format value, for diagnostics and loud errors. */
export function texFormatName(format: number): string {
  return GXTexFmt[format & 0xff] ?? `GX_TF_0x${(format & 0xff).toString(16)}`;
}

const expand3 = (v: number): number => (v << 5) | (v << 2) | (v >> 1);
const expand4 = (v: number): number => (v << 4) | v;
const expand5 = (v: number): number => (v << 3) | (v >> 2);
const expand6 = (v: number): number => (v << 2) | (v >> 4);

/** RGB5A3: the MSB picks between opaque RGB555 and RGB444 with 3-bit alpha.
 *  [SDK] — the pixel layout is a property of the texture unit, not of any code
 *  in this corpus. */
function rgb5a3(v: number, out: Uint8Array, o: number): void {
  if (v & 0x8000) {
    out[o] = expand5((v >> 10) & 0x1f);
    out[o + 1] = expand5((v >> 5) & 0x1f);
    out[o + 2] = expand5(v & 0x1f);
    out[o + 3] = 255;
  } else {
    out[o] = expand4((v >> 8) & 0xf);
    out[o + 1] = expand4((v >> 4) & 0xf);
    out[o + 2] = expand4(v & 0xf);
    out[o + 3] = expand3((v >> 12) & 0x7);
  }
}

/** RGB565. [SDK] */
function rgb565(v: number, out: Uint8Array, o: number): void {
  out[o] = expand5((v >> 11) & 0x1f);
  out[o + 1] = expand6((v >> 5) & 0x3f);
  out[o + 2] = expand5(v & 0x1f);
  out[o + 3] = 255;
}

/** Palette entry lookup for the C4/C8/C14X2 formats. [SDK] */
function tlutColor(tlut: Uint8Array | null, fmt: number, index: number, out: Uint8Array, o: number): void {
  if (!tlut || (index + 1) * 2 > tlut.length) {
    out[o] = 0;
    out[o + 1] = 0;
    out[o + 2] = 0;
    out[o + 3] = 0;
    return;
  }
  // TLUT entries are 16-bit, console (big-endian) order.
  const v = ((tlut[index * 2] as number) << 8) | (tlut[index * 2 + 1] as number);
  if (fmt === GXTlutFmt.IA8) {
    out[o] = v & 0xff;
    out[o + 1] = v & 0xff;
    out[o + 2] = v & 0xff;
    out[o + 3] = (v >> 8) & 0xff;
  } else if (fmt === GXTlutFmt.RGB565) {
    rgb565(v, out, o);
  } else {
    rgb5a3(v, out, o);
  }
}

/**
 * Decode one GameCube texture from raw console-order bytes into RGBA8.
 *
 * `src` must be the image data at its GC address, block-padded, exactly
 * `gxImageBytes(format, width, height)` long or longer. Throws rather than
 * guessing on any format, size or palette it cannot handle.
 */
export function decodeTextureBytes(
  src: Uint8Array,
  format: number,
  width: number,
  height: number,
  tlut: Uint8Array | null = null,
  tlutFormat: number = GXTlutFmt.RGB5A3,
): GxDecodedTexture {
  const fmt = format & 0xff;
  const geom = BLOCKS[fmt];
  const needed = gxImageBytes(fmt, width, height);
  if (!geom || needed === null) {
    throw new GxTextureError(
      `${texFormatName(fmt)} (0x${fmt.toString(16)}) is not a format this host decodes. ` +
        `The Z formats and the pre-swizzled cache formats have no browser equivalent here; ` +
        `refusing to substitute a plausible-looking image.`,
    );
  }
  if (width <= 0 || height <= 0 || width > 4096 || height > 4096) {
    throw new GxTextureError(`implausible texture extent ${width}x${height} for ${texFormatName(fmt)}`);
  }
  if (src.length < needed) {
    throw new GxTextureError(
      `${texFormatName(fmt)} ${width}x${height} needs ${needed} bytes of image data but only ${src.length} ` +
        `are readable at that address — the arena does not hold this texture`,
    );
  }
  const diagnostics: string[] = [];
  const rgba = new Uint8Array(width * height * 4);
  const blocksX = Math.ceil(width / geom.width);
  const blocksY = Math.ceil(height / geom.height);

  const put = (x: number, y: number, r: number, g: number, b: number, a: number): void => {
    if (x >= width || y >= height) return; // block padding beyond the image
    const o = (y * width + x) * 4;
    rgba[o] = r;
    rgba[o + 1] = g;
    rgba[o + 2] = b;
    rgba[o + 3] = a;
  };
  const putAt = (x: number, y: number, tmp: Uint8Array): void => {
    put(x, y, tmp[0] as number, tmp[1] as number, tmp[2] as number, tmp[3] as number);
  };
  const tmp = new Uint8Array(4);

  let off = 0;
  for (let by = 0; by < blocksY; by++) {
    for (let bx = 0; bx < blocksX; bx++) {
      const x0 = bx * geom.width;
      const y0 = by * geom.height;
      switch (fmt) {
        case GXTexFmt.I4:
        case GXTexFmt.C4: {
          // 8x8 block, two texels per byte, high nibble first. [SDK layout]
          for (let i = 0; i < 32; i++) {
            const byte = src[off + i] as number;
            const x = x0 + ((i % 4) * 2);
            const y = y0 + Math.floor(i / 4);
            for (let n = 0; n < 2; n++) {
              const v = n === 0 ? (byte >> 4) & 0xf : byte & 0xf;
              if (fmt === GXTexFmt.I4) {
                const e = expand4(v);
                put(x + n, y, e, e, e, e);
              } else {
                tlutColor(tlut, tlutFormat, v, tmp, 0);
                putAt(x + n, y, tmp);
              }
            }
          }
          break;
        }
        case GXTexFmt.I8:
        case GXTexFmt.IA4:
        case GXTexFmt.C8: {
          // 8x4 block, one byte per texel.
          for (let i = 0; i < 32; i++) {
            const byte = src[off + i] as number;
            const x = x0 + (i % 8);
            const y = y0 + Math.floor(i / 8);
            if (fmt === GXTexFmt.I8) put(x, y, byte, byte, byte, byte);
            else if (fmt === GXTexFmt.IA4) {
              // [SDK] high nibble alpha, low nibble intensity.
              const a = expand4((byte >> 4) & 0xf);
              const l = expand4(byte & 0xf);
              put(x, y, l, l, l, a);
            } else {
              tlutColor(tlut, tlutFormat, byte, tmp, 0);
              putAt(x, y, tmp);
            }
          }
          break;
        }
        case GXTexFmt.IA8:
        case GXTexFmt.RGB565:
        case GXTexFmt.RGB5A3:
        case GXTexFmt.C14X2: {
          // 4x4 block, one big-endian 16-bit word per texel.
          for (let i = 0; i < 16; i++) {
            const v = ((src[off + i * 2] as number) << 8) | (src[off + i * 2 + 1] as number);
            const x = x0 + (i % 4);
            const y = y0 + Math.floor(i / 4);
            if (fmt === GXTexFmt.IA8) {
              const a = (v >> 8) & 0xff;
              const l = v & 0xff;
              put(x, y, l, l, l, a);
            } else if (fmt === GXTexFmt.RGB565) {
              rgb565(v, tmp, 0);
              putAt(x, y, tmp);
            } else if (fmt === GXTexFmt.RGB5A3) {
              rgb5a3(v, tmp, 0);
              putAt(x, y, tmp);
            } else {
              tlutColor(tlut, tlutFormat, v & 0x3fff, tmp, 0);
              putAt(x, y, tmp);
            }
          }
          break;
        }
        case GXTexFmt.RGBA8: {
          // 4x4 block in TWO 32-byte halves: AR pairs then GB pairs. [SDK]
          for (let i = 0; i < 16; i++) {
            const x = x0 + (i % 4);
            const y = y0 + Math.floor(i / 4);
            put(
              x,
              y,
              src[off + i * 2 + 1] as number,
              src[off + 32 + i * 2] as number,
              src[off + 32 + i * 2 + 1] as number,
              src[off + i * 2] as number,
            );
          }
          break;
        }
        case GXTexFmt.CMPR: {
          // An 8x8 macroblock of four 4x4 S3TC sub-blocks. Two differences
          // from desktop DXT1, both [SDK]: the endpoints are big-endian, and
          // the 2-bit selectors run MOST significant first within each byte.
          for (let sub = 0; sub < 4; sub++) {
            const so = off + sub * 8;
            const sx = x0 + (sub % 2) * 4;
            const sy = y0 + Math.floor(sub / 2) * 4;
            const c0 = ((src[so] as number) << 8) | (src[so + 1] as number);
            const c1 = ((src[so + 2] as number) << 8) | (src[so + 3] as number);
            const pal = new Uint8Array(16);
            rgb565(c0, pal, 0);
            rgb565(c1, pal, 4);
            if (c0 > c1) {
              for (let k = 0; k < 3; k++) {
                pal[8 + k] = Math.round((2 * (pal[k] as number) + (pal[4 + k] as number)) / 3);
                pal[12 + k] = Math.round(((pal[k] as number) + 2 * (pal[4 + k] as number)) / 3);
              }
              pal[11] = 255;
              pal[15] = 255;
            } else {
              for (let k = 0; k < 3; k++) {
                pal[8 + k] = Math.round(((pal[k] as number) + (pal[4 + k] as number)) / 2);
                pal[12 + k] = 0;
              }
              pal[11] = 255;
              pal[15] = 0; // the transparent selector
            }
            for (let row = 0; row < 4; row++) {
              const bits = src[so + 4 + row] as number;
              for (let col = 0; col < 4; col++) {
                const sel = (bits >> (6 - col * 2)) & 3;
                put(
                  sx + col,
                  sy + row,
                  pal[sel * 4] as number,
                  pal[sel * 4 + 1] as number,
                  pal[sel * 4 + 2] as number,
                  pal[sel * 4 + 3] as number,
                );
              }
            }
          }
          break;
        }
        default:
          throw new GxTextureError(`unreachable: ${texFormatName(fmt)}`);
      }
      off += geom.blockBytes;
    }
  }

  if (fmt === GXTexFmt.C4 || fmt === GXTexFmt.C8 || fmt === GXTexFmt.C14X2) {
    if (!tlut) {
      diagnostics.push(
        `${texFormatName(fmt)} is a paletted format but no TLUT was loaded for it — every texel decoded to transparent black`,
      );
    }
  }

  return { width, height, rgba, format: fmt, diagnostics };
}

/**
 * Decode a texture whose image data lives in the shared GC arena.
 *
 * Reads the bytes at the ORIGINAL GameCube address — the same memory the ROM
 * handed to GXInitTexObj — through `GcMemory.readBytes`, which is a byte-level
 * read and therefore correct for a `raw` arena region (see the byte-order note
 * at the head of this file).
 */
export function decodeTextureFromMemory(
  mem: GcMemory,
  imageAddr: number,
  format: number,
  width: number,
  height: number,
  tlut: Uint8Array | null = null,
  tlutFormat: number = GXTlutFmt.RGB5A3,
): GxDecodedTexture {
  const needed = gxImageBytes(format, width, height);
  if (needed === null) {
    throw new GxTextureError(
      `${texFormatName(format)} (0x${(format & 0xff).toString(16)}) has no known image size — refusing to read the arena blind`,
    );
  }
  let bytes: Uint8Array;
  try {
    bytes = mem.readBytes(imageAddr >>> 0, needed);
  } catch (error) {
    throw new GxTextureError(
      `image data for ${texFormatName(format)} ${width}x${height} at 0x${(imageAddr >>> 0).toString(16)} ` +
        `is not readable in the arena (${needed} bytes): ${error instanceof Error ? error.message : String(error)}`,
    );
  }
  return decodeTextureBytes(bytes, format, width, height, tlut, tlutFormat);
}
