/** Shared memory-shaped runtime contracts for translated GameCube execution units. */

export const GC_MEM1_BASE = 0x8000_0000;
export const GC_MEM1_SIZE = 24 * 1024 * 1024;

export function f32(value: number): number {
  return Math.fround(value);
}

export function u8(value: number): number {
  return value & 0xff;
}

export function s8(value: number): number {
  return (value << 24) >> 24;
}

export function u16(value: number): number {
  return value & 0xffff;
}

export function s16(value: number): number {
  return (value << 16) >> 16;
}

export function u32(value: number): number {
  return value >>> 0;
}

export function s32(value: number): number {
  return value | 0;
}

export class GcMemory {
  readonly buffer: ArrayBuffer;
  readonly view: DataView;

  constructor(
    readonly baseAddress = GC_MEM1_BASE,
    readonly byteLength = GC_MEM1_SIZE,
    buffer?: ArrayBuffer,
  ) {
    if (!Number.isInteger(baseAddress) || !Number.isInteger(byteLength) || byteLength <= 0) {
      throw new RangeError("GcMemory requires an integer base address and positive byte length");
    }
    if (buffer && buffer.byteLength !== byteLength) {
      throw new RangeError(`GcMemory buffer is ${buffer.byteLength} bytes; expected ${byteLength}`);
    }
    this.buffer = buffer ?? new ArrayBuffer(byteLength);
    this.view = new DataView(this.buffer);
  }

  contains(address: number, width = 1): boolean {
    if (!Number.isInteger(address) || !Number.isInteger(width) || width < 0) return false;
    const offset = u32(address) - u32(this.baseAddress);
    return offset >= 0 && offset + width <= this.byteLength;
  }

  offset(address: number, width = 1): number {
    if (!this.contains(address, width)) {
      throw new RangeError(
        `GameCube address 0x${u32(address).toString(16).padStart(8, "0")} ` +
          `(${width} bytes) is outside this memory region`,
      );
    }
    return u32(address) - u32(this.baseAddress);
  }

  load(address: number, bytes: Uint8Array): void {
    new Uint8Array(this.buffer, this.offset(address, bytes.byteLength), bytes.byteLength).set(bytes);
  }

  bytes(address: number, length: number): Uint8Array {
    return new Uint8Array(this.buffer, this.offset(address, length), length);
  }

  readU8(address: number): number { return this.view.getUint8(this.offset(address)); }
  readS8(address: number): number { return this.view.getInt8(this.offset(address)); }
  readU16(address: number): number { return this.view.getUint16(this.offset(address, 2), false); }
  readS16(address: number): number { return this.view.getInt16(this.offset(address, 2), false); }
  readU32(address: number): number { return this.view.getUint32(this.offset(address, 4), false); }
  readS32(address: number): number { return this.view.getInt32(this.offset(address, 4), false); }
  readF32(address: number): number { return this.view.getFloat32(this.offset(address, 4), false); }

  writeU8(address: number, value: number): void { this.view.setUint8(this.offset(address), value); }
  writeS8(address: number, value: number): void { this.view.setInt8(this.offset(address), value); }
  writeU16(address: number, value: number): void {
    this.view.setUint16(this.offset(address, 2), value, false);
  }
  writeS16(address: number, value: number): void {
    this.view.setInt16(this.offset(address, 2), value, false);
  }
  writeU32(address: number, value: number): void {
    this.view.setUint32(this.offset(address, 4), value, false);
  }
  writeS32(address: number, value: number): void {
    this.view.setInt32(this.offset(address, 4), value, false);
  }
  writeF32(address: number, value: number): void {
    this.view.setFloat32(this.offset(address, 4), f32(value), false);
  }
}

export interface GcControllerState {
  buttons: number;
  stickX: number;
  stickY: number;
  cStickX: number;
  cStickY: number;
  triggerL: number;
  triggerR: number;
}

export interface GcDrawSubmission {
  kind: string;
  objectAddress: number;
  payload?: unknown;
}

export interface GcHost {
  loadModel(archiveAddress: number, symbolAddress: number): number;
  playSound(soundId: number, volume?: number, pan?: number): void;
  submitDraw(submission: GcDrawSubmission): void;
  readController(port: number): GcControllerState;
  readArchive(path: string): Promise<Uint8Array>;
}

export interface GcRuntime {
  memory: GcMemory;
  functions: GcFunctionRegistry;
  host: GcHost;
}

export type GcTranslatedFunction = (
  runtime: GcRuntime,
  ...args: number[]
) => number | void;

export class GcFunctionRegistry {
  private readonly implementations = new Map<number, GcTranslatedFunction>();
  private readonly aliases = new Map<number, number>();

  register(address: number, implementation: GcTranslatedFunction): void {
    const key = u32(address);
    if (this.implementations.has(key) || this.aliases.has(key)) {
      throw new Error(`GameCube function address already registered: 0x${key.toString(16)}`);
    }
    this.implementations.set(key, implementation);
  }

  alias(aliasAddress: number, targetAddress: number): void {
    const alias = u32(aliasAddress);
    const target = u32(targetAddress);
    if (alias === target || this.implementations.has(alias) || this.aliases.has(alias)) {
      throw new Error(`Invalid or duplicate GameCube function alias: 0x${alias.toString(16)}`);
    }
    this.resolve(target);
    this.aliases.set(alias, target);
  }

  has(address: number): boolean {
    try {
      this.resolve(address);
      return true;
    } catch {
      return false;
    }
  }

  resolve(address: number): GcTranslatedFunction {
    let key = u32(address);
    const seen = new Set<number>();
    while (this.aliases.has(key)) {
      if (seen.has(key)) throw new Error(`GameCube function alias cycle at 0x${key.toString(16)}`);
      seen.add(key);
      key = this.aliases.get(key)!;
    }
    const implementation = this.implementations.get(key);
    if (!implementation) {
      throw new Error(`Unregistered GameCube function address: 0x${key.toString(16)}`);
    }
    return implementation;
  }

  call(runtime: GcRuntime, address: number, ...args: number[]): number {
    return this.resolve(address)(runtime, ...args) ?? 0;
  }
}
