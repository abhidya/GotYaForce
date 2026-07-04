// afs.ts - AFS top-level CRI archive parser.
//
// Gotcha Force audio archives use CRI AFS (`AFS\0`). The TOC is little-endian:
// u32 member count, then count pairs of { u32 offset, u32 size }. Some AFS files carry
// an optional filename/timestamp table described by one extra offset/size pair after the
// member TOC; this parser exposes that metadata when it is present, but pack() deliberately
// emits the simple data-only archive shape used by extraction/repack smoke tests.

export const AFS_MAGIC = "AFS\0";
export const AFS_DEFAULT_ALIGNMENT = 0x800;
export const AFS_NAME_RECORD_BYTES = 0x30;

export interface AfsTimestamp {
  year: number;
  month: number;
  day: number;
  hour: number;
  minute: number;
  second: number;
}

export interface AfsMember {
  index: number;
  offset: number;
  size: number;
  data: Uint8Array;
  name?: string;
  timestamp?: AfsTimestamp;
}

export interface AfsArchive {
  memberCount: number;
  tocOffset: number;
  tocBytes: number;
  dataStartOffset: number;
  nameTableOffset: number | null;
  nameTableSize: number | null;
  members: AfsMember[];
}

export interface AfsUnpackOptions {
  /** Defaults to true; AFS TOCs are normally little-endian even on GameCube discs. */
  littleEndian?: boolean;
  /** Parse the optional filename/timestamp table when a plausible table pointer exists. */
  parseNameTable?: boolean;
}

export interface AfsPackMember {
  data: Uint8Array | ArrayBuffer;
}

export interface AfsPackOptions {
  /** Data alignment in bytes. Defaults to 0x800, matching the common disc/archive layout. */
  alignment?: number;
  /** Defaults to true; exposed for tests and oddball archives. */
  littleEndian?: boolean;
}

export function unpack(input: Uint8Array | ArrayBuffer, options: AfsUnpackOptions = {}): AfsArchive {
  const bytes = asBytes(input);
  const view = viewOf(bytes);
  const littleEndian = options.littleEndian ?? true;
  if (bytes.byteLength < 8) throw new RangeError(`AFS archive too small: ${bytes.byteLength} bytes`);
  if (magicOf(bytes) !== AFS_MAGIC) throw new Error(`unexpected AFS magic: ${JSON.stringify(magicOf(bytes))}`);

  const memberCount = view.getUint32(4, littleEndian);
  const tocOffset = 8;
  const tocBytes = memberCount * 8;
  if (memberCount > 0xffff) throw new Error(`implausible AFS member count: ${memberCount}`);
  if (tocOffset + tocBytes > bytes.byteLength) {
    throw new Error(`AFS TOC extends beyond archive: tocEnd=${tocOffset + tocBytes}, size=${bytes.byteLength}`);
  }

  const entries: Array<{ offset: number; size: number }> = [];
  for (let index = 0; index < memberCount; index += 1) {
    const entryOffset = tocOffset + index * 8;
    entries.push({
      offset: view.getUint32(entryOffset, littleEndian),
      size: view.getUint32(entryOffset + 4, littleEndian),
    });
  }

  const nameTable = (options.parseNameTable ?? true) ? detectNameTable(bytes, view, littleEndian, tocOffset + tocBytes, memberCount) : null;
  const names = nameTable ? parseNameTable(bytes.subarray(nameTable.offset, nameTable.offset + nameTable.size), memberCount, littleEndian) : [];

  const members = entries.map((entry, index): AfsMember => {
    const end = entry.offset + entry.size;
    if (entry.offset < tocOffset + tocBytes || end > bytes.byteLength || end < entry.offset) {
      throw new Error(`AFS member ${index} extends beyond archive: offset=${entry.offset}, size=${entry.size}, fileSize=${bytes.byteLength}`);
    }
    const named = names[index];
    return {
      index,
      offset: entry.offset,
      size: entry.size,
      data: bytes.slice(entry.offset, end),
      ...(named?.name ? { name: named.name } : {}),
      ...(named?.timestamp ? { timestamp: named.timestamp } : {}),
    };
  });

  return {
    memberCount,
    tocOffset,
    tocBytes,
    dataStartOffset: members.length > 0 ? Math.min(...members.map((member) => member.offset)) : tocOffset + tocBytes,
    nameTableOffset: nameTable?.offset ?? null,
    nameTableSize: nameTable?.size ?? null,
    members,
  };
}

export function pack(members: readonly AfsPackMember[], options: AfsPackOptions = {}): Uint8Array {
  const littleEndian = options.littleEndian ?? true;
  const alignment = options.alignment ?? AFS_DEFAULT_ALIGNMENT;
  if (!Number.isInteger(alignment) || alignment <= 0) throw new RangeError(`invalid AFS alignment: ${alignment}`);
  if (members.length > 0xffff) throw new RangeError(`too many AFS members: ${members.length}`);

  const payloads = members.map((member) => asBytes(member.data));
  const tocEnd = 8 + payloads.length * 8;
  let cursor = align(tocEnd, alignment);
  const entries = payloads.map((payload) => {
    const offset = cursor;
    cursor += payload.byteLength;
    cursor = align(cursor, alignment);
    return { offset, size: payload.byteLength };
  });

  const out = new Uint8Array(cursor);
  const view = viewOf(out);
  out[0] = 0x41; // A
  out[1] = 0x46; // F
  out[2] = 0x53; // S
  out[3] = 0x00;
  view.setUint32(4, payloads.length, littleEndian);

  for (let index = 0; index < payloads.length; index += 1) {
    const entry = entries[index];
    if (!entry) throw new Error(`missing generated AFS TOC entry ${index}`);
    const entryOffset = 8 + index * 8;
    view.setUint32(entryOffset, entry.offset, littleEndian);
    view.setUint32(entryOffset + 4, entry.size, littleEndian);
    out.set(payloads[index] ?? new Uint8Array(), entry.offset);
  }

  return out;
}

export const repack = pack;

export function memberByIndex(archive: AfsArchive, index: number): AfsMember {
  const member = archive.members[index];
  if (member === undefined) throw new RangeError(`AFS member ${index} is outside archive`);
  return member;
}

function detectNameTable(
  bytes: Uint8Array,
  view: DataView,
  littleEndian: boolean,
  pointerOffset: number,
  memberCount: number,
): { offset: number; size: number } | null {
  if (pointerOffset + 8 > bytes.byteLength || memberCount === 0) return null;
  const offset = view.getUint32(pointerOffset, littleEndian);
  const size = view.getUint32(pointerOffset + 4, littleEndian);
  const minSize = memberCount * AFS_NAME_RECORD_BYTES;
  if (size < minSize || offset < pointerOffset + 8 || offset + size > bytes.byteLength || offset + size < offset) {
    return null;
  }
  return { offset, size };
}

function parseNameTable(bytes: Uint8Array, memberCount: number, littleEndian: boolean): Array<{ name: string; timestamp?: AfsTimestamp }> {
  const view = viewOf(bytes);
  const names: Array<{ name: string; timestamp?: AfsTimestamp }> = [];
  for (let index = 0; index < memberCount; index += 1) {
    const offset = index * AFS_NAME_RECORD_BYTES;
    if (offset + AFS_NAME_RECORD_BYTES > bytes.byteLength) break;
    const nameBytes = bytes.subarray(offset, offset + 0x20);
    const zero = nameBytes.indexOf(0);
    const name = decodeAscii(nameBytes.subarray(0, zero >= 0 ? zero : nameBytes.length));
    const timestampOffset = offset + 0x20;
    const timestamp = {
      year: view.getUint16(timestampOffset, littleEndian),
      month: view.getUint16(timestampOffset + 2, littleEndian),
      day: view.getUint16(timestampOffset + 4, littleEndian),
      hour: view.getUint16(timestampOffset + 6, littleEndian),
      minute: view.getUint16(timestampOffset + 8, littleEndian),
      second: view.getUint16(timestampOffset + 10, littleEndian),
    };
    names.push({ name, timestamp });
  }
  return names;
}

function align(value: number, alignment: number): number {
  return Math.ceil(value / alignment) * alignment;
}

function asBytes(input: Uint8Array | ArrayBuffer): Uint8Array {
  return input instanceof Uint8Array ? input : new Uint8Array(input);
}

function viewOf(bytes: Uint8Array): DataView {
  return new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
}

function magicOf(bytes: Uint8Array): string {
  return String.fromCharCode(bytes[0] ?? 0, bytes[1] ?? 0, bytes[2] ?? 0, bytes[3] ?? 0);
}

function decodeAscii(bytes: Uint8Array): string {
  return [...bytes].map((byte) => String.fromCharCode(byte)).join("").trim();
}
