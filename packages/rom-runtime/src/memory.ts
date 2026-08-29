// =============================================================================
// memory.ts — main-thread view over the worker-owned shared module memory.
//
// Design I1: bridged-callee adapters OWN their marshalling — arguments are
// read out of GC memory (GC-pointer args dereferenced in the shared arena)
// and results AND side-effects are written back to GC memory at the original
// addresses, the same observable behavior a linked callee would have. This
// class is the adapters' only handle on that arena: byte-level accessors over
// the shared WebAssembly.Memory buffer, little-endian (the composed module's
// linear-memory order, identical to the verified seam's view in
// packages/combat/src/rom/wasmDamageCore.ts).
//
// The HP-mirror / energy accessors model the exact bss live-state rows the
// damage seam already encodes (wasmDamageCore.ts HP_MIRROR/ENERGY): the
// canonical GC addresses are the defaults, and both are constructor-
// parameterizable so the browser self-test can exercise the SAME adapter
// logic inside a small synthetic-arena test module.
// =============================================================================

/** bss s16[slot] HP mirror the damage formula reads (wasmDamageCore.ts:35). */
export const GC_HP_MIRROR_ADDR = 0x803b069c;
/** bss i32[team] force-energy rows the damage formula reads (wasmDamageCore.ts:36). */
export const GC_ENERGY_ADDR = 0x803b068c;

export interface GcMemoryOptions {
  /** Base of the s16[slot] HP mirror. Default: the ROM's 0x803b069c. */
  hpMirrorAddr?: number;
  /** Base of the i32[team] energy rows. Default: the ROM's 0x803b068c. */
  energyAddr?: number;
}

export class GcMemory {
  readonly memory: WebAssembly.Memory;
  readonly u8: Uint8Array;
  readonly dv: DataView;
  readonly hpMirrorAddr: number;
  readonly energyAddr: number;

  constructor(memory: WebAssembly.Memory, options: GcMemoryOptions = {}) {
    this.memory = memory;
    // Growth is disabled on the composed-module memory (max == initial), so
    // these views never detach.
    this.u8 = new Uint8Array(memory.buffer as ArrayBuffer);
    this.dv = new DataView(memory.buffer as ArrayBuffer);
    this.hpMirrorAddr = (options.hpMirrorAddr ?? GC_HP_MIRROR_ADDR) >>> 0;
    this.energyAddr = (options.energyAddr ?? GC_ENERGY_ADDR) >>> 0;
  }

  /**
   * Fail on an address outside the arena instead of pretending it read/wrote.
   *
   * The DataView accessors below already throw RangeError of their own accord; the
   * Uint8Array ones do not — an out-of-range `u8[addr]` yields `undefined` and an
   * out-of-range `u8[addr] = v` is a silent no-op. Both used to pass straight through here
   * (`?? 0` on the read), which turns the single most likely adapter bug — a mis-marshalled
   * GC pointer — into "the arena happened to be zero there". `assertRegionClear` in the
   * composed pilot is built on exactly these reads, so a region outside the arena would have
   * been certified CLEAR by reading nothing at all.
   */
  #assertInBounds(addr: number, length: number, op: string): void {
    if (addr < 0 || length < 0 || addr + length > this.u8.length) {
      throw new RangeError(
        `GcMemory.${op}: [0x${(addr >>> 0).toString(16)}, +${length}) is outside the ${this.u8.length}-byte arena`,
      );
    }
  }

  readU8(addr: number): number {
    const a = addr >>> 0;
    this.#assertInBounds(a, 1, "readU8");
    return this.u8[a] as number;
  }
  writeU8(addr: number, value: number): void {
    const a = addr >>> 0;
    this.#assertInBounds(a, 1, "writeU8");
    this.u8[a] = value & 0xff;
  }
  readU16(addr: number): number {
    return this.dv.getUint16(addr >>> 0, true);
  }
  readI16(addr: number): number {
    return this.dv.getInt16(addr >>> 0, true);
  }
  writeU16(addr: number, value: number): void {
    this.dv.setUint16(addr >>> 0, value & 0xffff, true);
  }
  writeI16(addr: number, value: number): void {
    this.dv.setInt16(addr >>> 0, value | 0, true);
  }
  readU32(addr: number): number {
    return this.dv.getUint32(addr >>> 0, true);
  }
  readI32(addr: number): number {
    return this.dv.getInt32(addr >>> 0, true);
  }
  writeU32(addr: number, value: number): void {
    this.dv.setUint32(addr >>> 0, value >>> 0, true);
  }
  writeI32(addr: number, value: number): void {
    this.dv.setInt32(addr >>> 0, value | 0, true);
  }
  readF32(addr: number): number {
    return this.dv.getFloat32(addr >>> 0, true);
  }
  writeF32(addr: number, value: number): void {
    this.dv.setFloat32(addr >>> 0, value, true);
  }
  readBytes(addr: number, length: number): Uint8Array {
    const a = addr >>> 0;
    // Bounds-checked rather than clamped: `slice` past the end returns a SHORT array, and
    // every caller that scans `bytes.length` (assertRegionClear) would then find nothing
    // wrong with a region it never actually looked at.
    this.#assertInBounds(a, length, "readBytes");
    return this.u8.slice(a, a + length);
  }
  writeBytes(addr: number, bytes: Uint8Array): void {
    const a = addr >>> 0;
    this.#assertInBounds(a, bytes.length, "writeBytes");
    this.u8.set(bytes, a);
  }

  // --- bss live-state accessors the damage seam models -----------------------

  /** s16 HP mirror by actor slot (HP_MIRROR + slot*2). */
  readHpMirror(slot: number): number {
    return this.readI16(this.hpMirrorAddr + slot * 2);
  }
  writeHpMirror(slot: number, hp: number): void {
    this.writeI16(this.hpMirrorAddr + slot * 2, hp);
  }

  /** i32 force-energy row by team (ENERGY + team*4). */
  readEnergy(team: number): number {
    return this.readI32(this.energyAddr + team * 4);
  }
  writeEnergy(team: number, energy: number): void {
    this.writeI32(this.energyAddr + team * 4, energy);
  }
}
