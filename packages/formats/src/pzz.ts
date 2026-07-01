// pzz.ts - Gotcha Force PZZ archive and PZZP/ARZ stream parser.
//
// PZZ archives are a 0x800-byte member table followed by 0x800-byte padded
// payload blocks. Compressed members use the same big-endian 16-bit LZ stream
// also seen in direct ARZ files.

export const PZZ_BLOCK_SIZE = 0x800;
export const PZZ_COMPRESSED_FLAG = 0x40000000;
export const PZZ_BLOCK_COUNT_MASK = 0x3fffffff;

export interface PzzDecompressionMeta {
  algorithm: "pzzp/arzip big-endian 16-bit LZ stream";
  sourceBytes: number;
  producedBytes: number;
  consumedBytes: number;
  trailingBytes: number;
  terminated: boolean;
  terminatorOffset: number | null;
  tokenCount: number;
  literalPairs: number;
  backRefs: number;
  longBackRefs: number;
  firstControlWord: number | null;
}

export interface PzzDecompressionResult {
  payload: Uint8Array;
  meta: PzzDecompressionMeta;
}

export interface PzzMember {
  index: number;
  memberId: string;
  tableOffset: number;
  tableWord: number;
  compressed: boolean;
  unknownHighBit: boolean;
  blockCount: number;
  paddedBytes: number;
  dataOffset: number;
  dataEnd: number;
  rawPayload: Uint8Array;
  payload: Uint8Array;
  compression: PzzDecompressionMeta | null;
}

export interface PzzArchive {
  memberCount: number;
  tableBytes: number;
  dataStartOffset: number;
  expectedSizeFromTable: number;
  validatesAgainstFileSize: boolean;
  members: PzzMember[];
}

export interface PzzUnpackOptions {
  /** Decompress compressed members. Defaults to true. */
  decompress?: boolean;
}

class GrowBuffer {
  private buffer: Uint8Array;
  length = 0;

  constructor(initialSize: number) {
    this.buffer = new Uint8Array(Math.max(0x1000, initialSize));
  }

  pushPair(a: number, b: number): void {
    this.ensure(2);
    this.buffer[this.length] = a;
    this.buffer[this.length + 1] = b;
    this.length += 2;
  }

  copyFromSelf(distance: number, count: number): void {
    const start = this.length - distance;
    if (start < 0) {
      throw new Error(`invalid PZZP back-reference distance ${distance} at output ${this.length}`);
    }
    this.ensure(count);
    for (let i = 0; i < count; i += 1) {
      this.buffer[this.length] = this.buffer[start + i] ?? 0;
      this.length += 1;
    }
  }

  toUint8Array(): Uint8Array {
    return this.buffer.slice(0, this.length);
  }

  private ensure(extraBytes: number): void {
    const needed = this.length + extraBytes;
    if (needed <= this.buffer.length) return;
    let nextLength = this.buffer.length;
    while (nextLength < needed) nextLength *= 2;
    const next = new Uint8Array(nextLength);
    next.set(this.buffer.subarray(0, this.length));
    this.buffer = next;
  }
}

export function unpack(input: Uint8Array | ArrayBuffer, options: PzzUnpackOptions = {}): PzzArchive {
  const bytes = asBytes(input);
  const view = viewOf(bytes);
  if (bytes.byteLength < PZZ_BLOCK_SIZE) {
    throw new RangeError(`PZZ archive too small: ${bytes.byteLength} bytes`);
  }

  const memberCount = view.getUint32(0, false);
  const tableBytes = 4 + memberCount * 4;
  if (memberCount <= 0 || memberCount > 512 || tableBytes > PZZ_BLOCK_SIZE) {
    throw new Error(`invalid PZZ member table: count=${memberCount}, tableBytes=${tableBytes}`);
  }

  const members: PzzMember[] = [];
  let cursor = PZZ_BLOCK_SIZE;
  let summedBlocks = 0;
  const shouldDecompress = options.decompress ?? true;

  for (let index = 0; index < memberCount; index += 1) {
    const tableOffset = 4 + index * 4;
    const tableWord = view.getUint32(tableOffset, false);
    const compressed = (tableWord & PZZ_COMPRESSED_FLAG) !== 0;
    const unknownHighBit = (tableWord & 0x80000000) !== 0;
    const blockCount = tableWord & PZZ_BLOCK_COUNT_MASK;
    const paddedBytes = blockCount * PZZ_BLOCK_SIZE;
    const dataOffset = cursor;
    const dataEnd = dataOffset + paddedBytes;
    if (dataEnd > bytes.byteLength) {
      throw new Error(`PZZ member ${index} extends beyond archive: end=${dataEnd}, size=${bytes.byteLength}`);
    }

    const rawPayload = bytes.slice(dataOffset, dataEnd);
    const decompressed =
      shouldDecompress && compressed && rawPayload.byteLength > 0 ? decompressPzzpStream(rawPayload) : null;

    members.push({
      index,
      memberId: String(index).padStart(3, "0"),
      tableOffset,
      tableWord,
      compressed,
      unknownHighBit,
      blockCount,
      paddedBytes,
      dataOffset,
      dataEnd,
      rawPayload,
      payload: decompressed?.payload ?? rawPayload,
      compression: decompressed?.meta ?? null,
    });

    cursor = dataEnd;
    summedBlocks += blockCount;
  }

  const expectedSizeFromTable = (summedBlocks + 1) * PZZ_BLOCK_SIZE;
  return {
    memberCount,
    tableBytes,
    dataStartOffset: PZZ_BLOCK_SIZE,
    expectedSizeFromTable,
    validatesAgainstFileSize: expectedSizeFromTable === bytes.byteLength,
    members,
  };
}

export function decompressPzzpStream(input: Uint8Array | ArrayBuffer): PzzDecompressionResult {
  const bytes = asBytes(input);
  const view = viewOf(bytes);
  const writer = new GrowBuffer(Math.max(bytes.byteLength * 3, 0x1000));
  const evenLength = bytes.byteLength & ~1;
  let cursor = 0;
  let control = 0;
  let bit = -1;
  let tokenCount = 0;
  let literalPairs = 0;
  let backRefs = 0;
  let longBackRefs = 0;
  let terminatorOffset: number | null = null;
  const firstControlWord = evenLength >= 2 ? view.getUint16(0, false) : null;

  while (cursor + 2 <= evenLength) {
    if (bit < 0) {
      control = view.getUint16(cursor, false);
      cursor += 2;
      bit = 15;
      continue;
    }

    tokenCount += 1;
    const compressedToken = (control & (1 << bit)) !== 0;
    bit -= 1;

    if (!compressedToken) {
      writer.pushPair(bytes[cursor] ?? 0, bytes[cursor + 1] ?? 0);
      cursor += 2;
      literalPairs += 1;
      continue;
    }

    const tokenOffset = cursor;
    const token = view.getUint16(cursor, false);
    const distance = (token & 0x7ff) * 2;
    if (distance === 0) {
      terminatorOffset = tokenOffset;
      cursor += 2;
      break;
    }

    let byteCount = (token >> 11) * 2;
    cursor += 2;
    if (byteCount === 0) {
      if (cursor + 2 > evenLength) throw new Error("PZZP long back-reference is missing its extension word");
      byteCount = view.getUint16(cursor, false) * 2;
      cursor += 2;
      longBackRefs += 1;
    }

    writer.copyFromSelf(distance, byteCount);
    backRefs += 1;
  }

  const payload = writer.toUint8Array();
  return {
    payload,
    meta: {
      algorithm: "pzzp/arzip big-endian 16-bit LZ stream",
      sourceBytes: bytes.byteLength,
      producedBytes: payload.byteLength,
      consumedBytes: cursor,
      trailingBytes: bytes.byteLength - cursor,
      terminated: terminatorOffset !== null,
      terminatorOffset,
      tokenCount,
      literalPairs,
      backRefs,
      longBackRefs,
      firstControlWord,
    },
  };
}

export function memberByIndex(archive: PzzArchive, index: number): PzzMember {
  const member = archive.members[index];
  if (member === undefined) throw new RangeError(`PZZ member ${index} is outside archive`);
  return member;
}

function asBytes(input: Uint8Array | ArrayBuffer): Uint8Array {
  return input instanceof Uint8Array ? input : new Uint8Array(input);
}

function viewOf(bytes: Uint8Array): DataView {
  return new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
}
