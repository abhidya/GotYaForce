// tpl.ts — TPL standard GameCube texture-palette metadata parser.
//
// This module intentionally stops at container/image metadata. Pixel decode still belongs to
// offline tooling until the runtime needs RGBA. Keeping header parsing here gives scripts and
// audits one shared interface for the binary layout instead of each script re-reading the TPL
// table by hand.

export const TPL_MAGIC = 0x0020af30;

export const TPL_FORMATS = new Map<number, string>([
  [0, "I4"],
  [1, "I8"],
  [2, "IA4"],
  [3, "IA8"],
  [4, "RGB565"],
  [5, "RGB5A3"],
  [6, "RGBA8"],
  [8, "C4"],
  [9, "C8"],
  [10, "C14X2"],
  [14, "CMPR"],
]);

export const TPL_BYTES_PER_PIXEL = new Map<number, number>([
  [0, 0.5],
  [1, 1],
  [2, 1],
  [3, 2],
  [4, 2],
  [5, 2],
  [6, 4],
  [8, 0.5],
  [9, 1],
  [10, 2],
  [14, 0.5],
]);

export interface TplImageMetadata {
  index: number;
  width?: number;
  height?: number;
  formatCode?: number;
  format?: string;
  dataOffset?: number;
  textureHeaderOffset?: number;
  paletteHeaderOffset?: number | null;
  estimatedPayloadBytes?: number | null;
  parseStatus?: string;
  entryOffset?: number;
}

export interface TplMetadata {
  parseStatus: "ok" | "partial" | "too small for TPL header" | string;
  magic?: "0x0020af30" | string;
  imageCount?: number;
  imageTableOffset?: number;
  images: TplImageMetadata[];
  exactBytes: number | null;
  paddingBytes?: number | null;
}

export interface ParseTplMetadataOptions {
  maxImages?: number;
  includePaddingBytes?: boolean;
}

export function parseMetadata(
  input: Uint8Array | ArrayBuffer,
  options: ParseTplMetadataOptions = {},
): TplMetadata {
  const bytes = asBytes(input);
  if (bytes.byteLength < 12) {
    return {
      parseStatus: "too small for TPL header",
      images: [],
      exactBytes: null,
      ...(options.includePaddingBytes ? { paddingBytes: null } : {}),
    };
  }

  const view = viewOf(bytes);
  const magic = view.getUint32(0, false);
  if (magic !== TPL_MAGIC) {
    return {
      parseStatus: `unexpected magic ${hex(magic)}`,
      magic: hex(magic),
      images: [],
      exactBytes: null,
      ...(options.includePaddingBytes ? { paddingBytes: null } : {}),
    };
  }

  const imageCount = view.getUint32(4, false);
  const imageTableOffset = view.getUint32(8, false);
  const maxImages = Math.min(imageCount, options.maxImages ?? 64);
  const images: TplImageMetadata[] = [];

  for (let i = 0; i < maxImages; i += 1) {
    const entryOffset = imageTableOffset + i * 8;
    if (entryOffset + 8 > bytes.byteLength) {
      images.push({ index: i, parseStatus: "image table entry outside file", entryOffset });
      break;
    }

    const textureHeaderOffset = view.getUint32(entryOffset, false);
    const paletteHeaderOffsetRaw = view.getUint32(entryOffset + 4, false);
    const paletteHeaderOffset = paletteHeaderOffsetRaw || null;
    if (textureHeaderOffset + 12 > bytes.byteLength) {
      images.push({
        index: i,
        parseStatus: "texture header outside file",
        textureHeaderOffset,
        paletteHeaderOffset,
      });
      continue;
    }

    const height = view.getUint16(textureHeaderOffset, false);
    const width = view.getUint16(textureHeaderOffset + 2, false);
    const formatCode = view.getUint32(textureHeaderOffset + 4, false);
    const dataOffset = view.getUint32(textureHeaderOffset + 8, false);
    const bytesPerPixel = TPL_BYTES_PER_PIXEL.get(formatCode);
    images.push({
      index: i,
      width,
      height,
      formatCode,
      format: TPL_FORMATS.get(formatCode) ?? `unknown(${formatCode})`,
      dataOffset,
      textureHeaderOffset,
      paletteHeaderOffset,
      estimatedPayloadBytes: bytesPerPixel === undefined ? null : Math.ceil(width * height * bytesPerPixel),
    });
  }

  const exactBytes = exactTplBytes(images);
  return {
    parseStatus: images.length === imageCount ? "ok" : "partial",
    magic: "0x0020af30",
    imageCount,
    imageTableOffset,
    images,
    exactBytes,
    ...(options.includePaddingBytes ? { paddingBytes: exactBytes === null ? null : bytes.byteLength - exactBytes } : {}),
  };
}

export const parseTplMetadata = parseMetadata;

function exactTplBytes(images: readonly TplImageMetadata[]): number | null {
  const ends = images
    .map((image) =>
      Number.isInteger(image.dataOffset) && Number.isInteger(image.estimatedPayloadBytes)
        ? (image.dataOffset as number) + (image.estimatedPayloadBytes as number)
        : null,
    )
    .filter((value): value is number => value !== null);
  return ends.length === images.length && ends.length > 0 ? Math.max(...ends) : null;
}

function asBytes(input: Uint8Array | ArrayBuffer): Uint8Array {
  return input instanceof Uint8Array ? input : new Uint8Array(input);
}

function viewOf(bytes: Uint8Array): DataView {
  return new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
}

function hex(value: number): string {
  return `0x${value.toString(16).padStart(8, "0")}`;
}
