// =============================================================================
// disc.ts — the disc the DVD HLE host reads from, and the GameCube FST.
//
// THE CENTRAL CONSTRAINT OF THE DVD HALF, stated here because it shapes every
// decision in this directory:
//
//   THIS REPOSITORY CONTAINS NO DISC BYTES. `research/disc/` holds one
//   `.gitkeep`; `.gitignore` excludes `*.iso`, `*.gcm`, `*.ciso` and
//   `research/disc/*/`. Every extractor in `scripts/` reads from an
//   UNTRACKED, owner-supplied `user-data/GG4E/disc/` tree that does not exist
//   in a clean checkout. There is no `afs_data.afs`, no `boot.dol`, no FST
//   dump, and no name->offset index anywhere in the tree.
//
// So the host cannot be "backed by the extracted disc data the repo already
// has", because there is none. It is backed by a DISC PROVIDER interface with
// two implementations:
//
//   * `SyntheticDisc` — a disc BUILT IN MEMORY from named byte blobs, laying
//     files out on 2 KiB boundaries and synthesizing a REAL GameCube FST for
//     them. Evidence class "synthetic": the FST format is real, the bytes in
//     it are ours. This is what the tests and the browser proof run on, and it
//     is the only thing that runs without an owner-supplied disc.
//
//   * `ImageDisc` — a real GameCube disc image. Its FST is PARSED, not
//     synthesized, by `parseGcFst` below. Evidence class "synthetic" too,
//     because parsing real bytes correctly is still not a comparison against
//     console behaviour (see docs/audio-dvd-hle-host.md §1). Nothing in this
//     repo can construct one today; `scripts/build-disc-index.mjs` is the
//     entry point for an owner who has the disc.
//
// FST FORMAT PROVENANCE. The 12-byte record layout is normally cited from the
// GameCube SDK, but this host does not have to take it on trust: the ROM's own
// `gnt4_DVDOpen_bl` @0x8020d1ec and `gnt4_entryToPath_bl` @0x8020d2d8 read it
// field by field in the decompiled corpus, and the comments below cite those
// reads. Where a fact comes from the ROM it is marked [CORPUS]; where it comes
// from the GameCube SDK's documented behaviour it is marked [SDK].
// =============================================================================

/** Bytes per FST record. [CORPUS] `gnt4_DVDOpen_bl` indexes `uVar1 * 0xc`. */
export const FST_ENTRY_BYTES = 12;

/**
 * Disc sector size, and the alignment DVD reads must satisfy.
 * [CORPUS] The ROM's own file layer sets its record size to 0x800
 * (`FUN_802754ec` writes `*(u32 *)(handle + 0x10) = 0x800`), and rounds every
 * read length up with `len + 0x1f & 0xffffffe0`. [SDK] The drive itself reads
 * in 32 KiB blocks but the API contract is 32-byte alignment on the
 * destination address and length, and 4-byte alignment on the disc offset.
 */
export const DVD_SECTOR_BYTES = 0x800;

/** [SDK] DVD reads require a 32-byte-aligned length and destination. */
export const DVD_READ_ALIGN = 0x20;

/** Thrown when the disc model is asked for something it cannot answer. */
export class DvdDiscError extends Error {
  constructor(message: string) {
    super(`DVD disc: ${message}`);
    this.name = "DvdDiscError";
  }
}

/** One parsed FST record. */
export interface GcFstEntry {
  /** Index into the FST — this is the ENTRYNUM the SDK's API traffics in. */
  readonly index: number;
  /** Leaf name from the string table. */
  readonly name: string;
  /** Absolute "/"-rooted path. The root itself is "/". */
  readonly path: string;
  readonly isDir: boolean;
  /** Files: byte offset of the file's first byte on the disc. Dirs: 0. */
  readonly startAddr: number;
  /** Files: length in bytes. Dirs: 0. */
  readonly length: number;
  /** Dirs: parent entry index. Files: the containing directory's index. */
  readonly parent: number;
  /** Dirs: one past the last entry contained in this directory. Files: 0. */
  readonly next: number;
}

/**
 * What the DVD adapters read from. Deliberately narrow: an entrynum lookup, an
 * entry accessor, and a byte read. Everything else the SDK exposes is derived.
 */
export interface DiscImage {
  /** Human-readable provenance, quoted verbatim into adapter evidence. */
  readonly id: string;
  /** Every FST record, index-ordered; entry 0 is the root directory. */
  readonly fst: readonly GcFstEntry[];
  /** Total size of the addressable disc, in bytes. */
  readonly byteLength: number;
  /**
   * [SDK] `DVDConvertPathToEntrynum` semantics: resolve a "/"-rooted path to
   * an entrynum, or -1. Case-insensitive, because the SDK's own comparison is.
   */
  entrynumForPath(path: string): number;
  /** Raw disc bytes. MUST throw rather than short-read: a short read here is
   *  a corrupted asset that looks like a working one. */
  read(offset: number, length: number): Uint8Array;
}

// =============================================================================
// FST parsing
// =============================================================================

function readCString(bytes: Uint8Array, at: number): string {
  let end = at;
  while (end < bytes.length && bytes[end] !== 0) end += 1;
  if (end >= bytes.length) {
    throw new DvdDiscError(`unterminated FST name string at 0x${at.toString(16)}`);
  }
  return new TextDecoder("latin1").decode(bytes.subarray(at, end));
}

/**
 * Parse a GameCube FST blob into records.
 *
 * BYTE ORDER: the FST is BIG-endian, because it is disc data written by the
 * console's tools — unlike the shared arena, which is little-endian wasm32
 * linear memory. `docs/gx-hle-host.md` §4.2 makes the same distinction for the
 * GX half; the rule is identical here and it is deliberate in both directions:
 * anything that came off the disc is big-endian, anything that lives in the
 * module's memory is little-endian.
 *
 * [CORPUS] Field meanings are exactly the reads `gnt4_DVDOpen_bl` and
 * `gnt4_entryToPath_bl` perform:
 *   word0 & 0xff000000  -> nonzero means DIRECTORY (DVDOpen refuses those)
 *   word0 & 0x00ffffff  -> byte offset of the name in the string table
 *   word1               -> file: startAddr;  dir: parent entrynum
 *   word2               -> file: length;     dir: `next` (one past last child)
 * [SDK] Entry 0 is the root directory and its word2 is the TOTAL entry count,
 * which is how the string table's start is located.
 */
export function parseGcFst(fst: Uint8Array): GcFstEntry[] {
  if (fst.length < FST_ENTRY_BYTES) {
    throw new DvdDiscError(`FST is ${fst.length} bytes — too short to hold even the root entry`);
  }
  const dv = new DataView(fst.buffer, fst.byteOffset, fst.byteLength);
  const count = dv.getUint32(8, false);
  if (count < 1 || count * FST_ENTRY_BYTES > fst.length) {
    throw new DvdDiscError(
      `FST root claims ${count} entries, which needs ${count * FST_ENTRY_BYTES} bytes of a ${fst.length}-byte FST`,
    );
  }
  const stringTableAt = count * FST_ENTRY_BYTES;

  // Pass one: raw fields.
  const raw: Array<{ isDir: boolean; nameOffset: number; w1: number; w2: number }> = [];
  for (let i = 0; i < count; i++) {
    const w0 = dv.getUint32(i * FST_ENTRY_BYTES + 0, false);
    raw.push({
      isDir: (w0 & 0xff000000) !== 0,
      nameOffset: w0 & 0x00ffffff,
      w1: dv.getUint32(i * FST_ENTRY_BYTES + 4, false),
      w2: dv.getUint32(i * FST_ENTRY_BYTES + 8, false),
    });
  }

  // Pass two: names and paths. Directory extents are a half-open [i+1, next)
  // range, so a single walk with a directory stack yields every path without
  // recursion. [SDK] this is the same walk `DVDConvertPathToEntrynum` does.
  const entries: GcFstEntry[] = [];
  const stack: Array<{ index: number; path: string; end: number }> = [];
  for (let i = 0; i < count; i++) {
    const r = raw[i] as (typeof raw)[number];
    while (stack.length > 0 && i >= (stack[stack.length - 1] as { end: number }).end) stack.pop();
    const parentFrame = stack[stack.length - 1];
    const name = i === 0 ? "" : readCString(fst, stringTableAt + r.nameOffset);
    const parentPath = parentFrame ? parentFrame.path : "";
    const path = i === 0 ? "/" : `${parentPath}/${name}`;
    entries.push({
      index: i,
      name,
      path,
      isDir: i === 0 ? true : r.isDir,
      startAddr: r.isDir || i === 0 ? 0 : r.w1,
      length: r.isDir || i === 0 ? 0 : r.w2,
      parent: i === 0 ? 0 : (parentFrame?.index ?? 0),
      next: r.isDir || i === 0 ? r.w2 : 0,
    });
    if (r.isDir || i === 0) {
      stack.push({ index: i, path: i === 0 ? "" : path, end: r.w2 });
    }
  }
  return entries;
}

/** Serialize records back into a GameCube FST blob. Used by `SyntheticDisc`
 *  so the synthesized disc is parsed by the SAME code that parses a real one —
 *  a format bug cannot hide behind a hand-built object graph. */
export function buildGcFst(files: ReadonlyArray<{ path: string; startAddr: number; length: number }>): Uint8Array {
  // Build the directory tree implied by the paths.
  interface Node {
    name: string;
    children: Map<string, Node>;
    file: { startAddr: number; length: number } | null;
  }
  const root: Node = { name: "", children: new Map(), file: null };
  for (const f of files) {
    const parts = f.path.split("/").filter((p) => p.length > 0);
    if (parts.length === 0) throw new DvdDiscError(`cannot place a file at the disc root path ${f.path}`);
    let node = root;
    for (let i = 0; i < parts.length - 1; i++) {
      const part = parts[i] as string;
      let child = node.children.get(part.toLowerCase());
      if (!child) {
        child = { name: part, children: new Map(), file: null };
        node.children.set(part.toLowerCase(), child);
      }
      node = child;
    }
    const leaf = parts[parts.length - 1] as string;
    if (node.children.has(leaf.toLowerCase())) {
      throw new DvdDiscError(`duplicate disc path ${f.path}`);
    }
    node.children.set(leaf.toLowerCase(), {
      name: leaf,
      children: new Map(),
      file: { startAddr: f.startAddr, length: f.length },
    });
  }

  // Flatten depth-first, which is the order an FST stores entries in.
  interface Flat {
    node: Node;
    parent: number;
    isDir: boolean;
  }
  const flat: Flat[] = [{ node: root, parent: 0, isDir: true }];
  const nextOf = new Map<number, number>();
  const walk = (node: Node, selfIndex: number): void => {
    // Directories before files is not required by the format; sorted order is
    // chosen so the output is deterministic.
    const kids = [...node.children.values()].sort((a, b) => a.name.localeCompare(b.name));
    for (const kid of kids) {
      const index = flat.length;
      flat.push({ node: kid, parent: selfIndex, isDir: kid.file === null });
      if (kid.file === null) walk(kid, index);
    }
    nextOf.set(selfIndex, flat.length);
  };
  walk(root, 0);

  const names: number[] = [];
  const stringBytes: number[] = [];
  for (const f of flat) {
    names.push(stringBytes.length);
    if (f.node !== root) {
      for (const ch of f.node.name) stringBytes.push(ch.charCodeAt(0) & 0xff);
      stringBytes.push(0);
    }
  }

  const out = new Uint8Array(flat.length * FST_ENTRY_BYTES + stringBytes.length);
  const dv = new DataView(out.buffer);
  for (let i = 0; i < flat.length; i++) {
    const f = flat[i] as Flat;
    const at = i * FST_ENTRY_BYTES;
    dv.setUint32(at + 0, ((f.isDir ? 1 : 0) << 24) | ((names[i] as number) & 0x00ffffff), false);
    if (f.isDir) {
      dv.setUint32(at + 4, i === 0 ? 0 : f.parent, false);
      dv.setUint32(at + 8, i === 0 ? flat.length : (nextOf.get(i) ?? flat.length), false);
    } else {
      const file = f.node.file as { startAddr: number; length: number };
      dv.setUint32(at + 4, file.startAddr, false);
      dv.setUint32(at + 8, file.length, false);
    }
  }
  out.set(Uint8Array.from(stringBytes), flat.length * FST_ENTRY_BYTES);
  return out;
}

// =============================================================================
// Disc implementations
// =============================================================================

/** Shared path lookup: [SDK] DVDConvertPathToEntrynum is case-insensitive. */
function lookup(fst: readonly GcFstEntry[], path: string): number {
  const wanted = path.replace(/\\/g, "/").replace(/\/+/g, "/");
  const normalized = wanted.startsWith("/") ? wanted : `/${wanted}`;
  const key = normalized.replace(/\/$/, "").toLowerCase() || "/";
  for (const entry of fst) {
    if (entry.path.toLowerCase() === key) return entry.index;
  }
  return -1;
}

/**
 * A disc assembled in memory from named blobs.
 *
 * Layout: files are placed at increasing 2 KiB-aligned offsets starting after
 * a reserved 0x8000-byte header region, which is where a real GameCube disc
 * keeps boot.bin / bi2.bin / the apploader. Nothing reads that region here, so
 * it is zero-filled — and it is reserved rather than reclaimed so that a file
 * offset from this disc is in the same numeric range a real one would be.
 */
export class SyntheticDisc implements DiscImage {
  readonly id: string;
  readonly fst: readonly GcFstEntry[];
  readonly bytes: Uint8Array;

  /** [SDK] The system region a real GameCube disc reserves before user data. */
  static readonly SYSTEM_REGION_BYTES = 0x8000;

  constructor(files: ReadonlyArray<{ path: string; bytes: Uint8Array }>, id = "SyntheticDisc (in-memory)") {
    this.id = id;
    let cursor = SyntheticDisc.SYSTEM_REGION_BYTES;
    const placed: Array<{ path: string; startAddr: number; length: number; bytes: Uint8Array }> = [];
    for (const f of files) {
      placed.push({ path: f.path, startAddr: cursor, length: f.bytes.length, bytes: f.bytes });
      cursor += Math.ceil(Math.max(f.bytes.length, 1) / DVD_SECTOR_BYTES) * DVD_SECTOR_BYTES;
    }
    this.bytes = new Uint8Array(cursor);
    for (const p of placed) this.bytes.set(p.bytes, p.startAddr);
    // Round-trip through the real serializer/parser so the synthesized FST is
    // held to the same format rules a disc's own FST is.
    this.fst = parseGcFst(buildGcFst(placed));
  }

  get byteLength(): number {
    return this.bytes.length;
  }

  entrynumForPath(path: string): number {
    return lookup(this.fst, path);
  }

  read(offset: number, length: number): Uint8Array {
    if (offset < 0 || length < 0 || offset + length > this.bytes.length) {
      throw new DvdDiscError(
        `read [0x${offset.toString(16)}, +${length}) is outside the ${this.bytes.length}-byte disc — ` +
          `refusing to short-read, because a short read produces a corrupt asset that looks loaded`,
      );
    }
    return this.bytes.slice(offset, offset + length);
  }
}

/**
 * A real GameCube disc image, or any byte source shaped like one.
 *
 * `fstOffset`/`fstSize` come from boot.bin (0x0424 / 0x0428, big-endian) on a
 * real image. They are constructor parameters rather than being read here so
 * that a caller with only the FST — the shape `scripts/build-disc-index.mjs`
 * emits — can still use this class.
 */
export class ImageDisc implements DiscImage {
  readonly id: string;
  readonly fst: readonly GcFstEntry[];
  readonly #read: (offset: number, length: number) => Uint8Array;
  readonly #byteLength: number;

  constructor(options: {
    id: string;
    fstBytes: Uint8Array;
    byteLength: number;
    read: (offset: number, length: number) => Uint8Array;
  }) {
    this.id = options.id;
    this.fst = parseGcFst(options.fstBytes);
    this.#read = options.read;
    this.#byteLength = options.byteLength;
  }

  /** Read boot.bin's FST pointer out of a whole disc image. [SDK] boot.bin
   *  keeps fstOffset at 0x0424 and fstSize at 0x0428, both big-endian. */
  static fromImage(image: Uint8Array, id: string): ImageDisc {
    if (image.length < 0x0440) throw new DvdDiscError(`disc image is only ${image.length} bytes — no boot.bin`);
    const dv = new DataView(image.buffer, image.byteOffset, image.byteLength);
    const fstOffset = dv.getUint32(0x0424, false);
    const fstSize = dv.getUint32(0x0428, false);
    if (fstOffset + fstSize > image.length) {
      throw new DvdDiscError(
        `boot.bin points the FST at 0x${fstOffset.toString(16)}+${fstSize}, past the ${image.length}-byte image`,
      );
    }
    return new ImageDisc({
      id,
      fstBytes: image.subarray(fstOffset, fstOffset + fstSize),
      byteLength: image.length,
      read: (offset, length) => {
        if (offset < 0 || length < 0 || offset + length > image.length) {
          throw new DvdDiscError(`read [0x${offset.toString(16)}, +${length}) is outside the disc image`);
        }
        return image.slice(offset, offset + length);
      },
    });
  }

  get byteLength(): number {
    return this.#byteLength;
  }

  entrynumForPath(path: string): number {
    return lookup(this.fst, path);
  }

  read(offset: number, length: number): Uint8Array {
    return this.#read(offset, length);
  }
}
