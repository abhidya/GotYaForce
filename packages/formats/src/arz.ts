// arz.ts - direct ARZ/PZZP compressed stream support.
//
// Gotcha Force direct `.arz` files use the same big-endian 16-bit LZ stream as
// compressed PZZ members. Keep this as a small public wrapper so callers do not
// need to know that implementation detail.

import { decompressPzzpStream, type PzzDecompressionMeta } from "./pzz.js";

export interface ArzDecompressionResult {
  payload: Uint8Array;
  meta: PzzDecompressionMeta;
}

export function decompress(input: Uint8Array | ArrayBuffer): Uint8Array {
  return decompressWithMeta(input).payload;
}

export function decompressWithMeta(input: Uint8Array | ArrayBuffer): ArzDecompressionResult {
  return decompressPzzpStream(input);
}
