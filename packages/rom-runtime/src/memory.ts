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

  readU8(addr: number): number {
    return this.u8[addr >>> 0] ?? 0;
  }
  writeU8(addr: number, value: number): void {
    this.u8[addr >>> 0] = value & 0xff;
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
    return this.u8.slice(a, a + length);
  }
  writeBytes(addr: number, bytes: Uint8Array): void {
    this.u8.set(bytes, addr >>> 0);
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
