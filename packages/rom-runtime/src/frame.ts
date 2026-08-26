// =============================================================================
// frame.ts — host-side mirror of the GF uniform dispatch frame ABI, version 1.
//
// The wasm side of this ABI is emitted by the assembly gate's dispatch
// companion (OGhidra src/port_dispatch_companion.py -> gf_dispatch_frame.h,
// design V4 H3): every address-keyed table entry is an adapter thunk with the
// ONE canonical signature (i32 argptr) -> i32, and a table miss is the
// declared import  __gf_dispatch_miss(u32 gc_addr, i32 argptr)  — a bridge
// call, never a trap. `argptr` is the byte address, in the shared linear
// memory, of one frame with this fixed little-endian layout:
//
//   +0x00  u32 arg_count   caller-written; informational/ledger data ONLY —
//                          never gated on (PPC indirect calls are signature-
//                          agnostic; cross-class callers legitimately write
//                          fewer slots than the callee reads).
//   +0x04  u32 ret_class   callee-written FrameValueClass of the return slot.
//   +0x08  slot ret        callee-written return slot (8 bytes).
//   +0x10  slot args[16]   caller-written 8-byte argument slots in callee
//                          parameter order. i32/f32 occupy the LOW 4 bytes;
//                          i64/f64 occupy all 8.
//
//   sizeof(frame) == 0x90, alignment 8.
//
// The constants here are a MIRROR of the companion's — the numbers live in
// exactly two places (the Python emitter + its _Static_assert'd header, and
// this file) and FRAME_ABI_VERSION pins them together.
// =============================================================================

/** Mirrors GF_DISPATCH_FRAME_VERSION in gf_dispatch_frame.h. */
export const FRAME_ABI_VERSION = 1;

export const FRAME_MAX_ARGS = 16;
export const FRAME_SLOT_SIZE = 8;
export const FRAME_ARG_COUNT_OFFSET = 0x00;
export const FRAME_RET_CLASS_OFFSET = 0x04;
export const FRAME_RET_OFFSET = 0x08;
export const FRAME_ARGS_OFFSET = 0x10;
/** sizeof(__gf_dispatch_frame) == 0x90. */
export const FRAME_SIZE = FRAME_ARGS_OFFSET + FRAME_MAX_ARGS * FRAME_SLOT_SIZE;

/** Mirrors GF_DISPATCH_CLASS_* in gf_dispatch_frame.h. */
export enum FrameValueClass {
  VOID = 0,
  I32 = 1,
  I64 = 2,
  F32 = 3,
  F64 = 4,
}

/**
 * A view over ONE dispatch frame at `argptr` in the shared linear memory.
 * Adapters use this to unmarshal their arguments and marshal their return —
 * the same contract the companion's link-time thunks implement wasm-side.
 *
 * All accessors are little-endian (wasm32 linear memory order, matching the
 * thunks' direct struct access).
 */
export class DispatchFrame {
  readonly dv: DataView;
  readonly base: number;

  constructor(dv: DataView, argptr: number) {
    this.dv = dv;
    this.base = argptr >>> 0;
  }

  get argCount(): number {
    return this.dv.getUint32(this.base + FRAME_ARG_COUNT_OFFSET, true);
  }
  set argCount(n: number) {
    this.dv.setUint32(this.base + FRAME_ARG_COUNT_OFFSET, n >>> 0, true);
  }

  get retClass(): number {
    return this.dv.getUint32(this.base + FRAME_RET_CLASS_OFFSET, true);
  }

  #argBase(index: number): number {
    if (index < 0 || index >= FRAME_MAX_ARGS) {
      throw new RangeError(`dispatch frame arg index ${index} out of range 0..${FRAME_MAX_ARGS - 1}`);
    }
    return this.base + FRAME_ARGS_OFFSET + index * FRAME_SLOT_SIZE;
  }

  i32Arg(index: number): number {
    return this.dv.getInt32(this.#argBase(index), true);
  }
  u32Arg(index: number): number {
    return this.dv.getUint32(this.#argBase(index), true);
  }
  i64Arg(index: number): bigint {
    return this.dv.getBigInt64(this.#argBase(index), true);
  }
  f32Arg(index: number): number {
    return this.dv.getFloat32(this.#argBase(index), true);
  }
  f64Arg(index: number): number {
    return this.dv.getFloat64(this.#argBase(index), true);
  }

  /**
   * Write one i32 argument slot. CALLER-EXTENDS contract (companion review):
   * sub-i32 values (u8/s8/u16/s16) must arrive here ALREADY extended to PPC
   * register width — the frame stores exactly what the caller's r3..r10 would
   * have held; callees may read the full 32-bit slot. Use the typed helpers
   * below when marshalling narrow C types so the extension is explicit.
   */
  setI32Arg(index: number, value: number): void {
    const at = this.#argBase(index);
    this.dv.setBigInt64(at, 0n, true);
    this.dv.setInt32(at, value | 0, true);
  }

  /** Sign-extend an s8 to register width, then write the slot. */
  setI8Arg(index: number, value: number): void {
    this.setI32Arg(index, (value << 24) >> 24);
  }
  /** Zero-extend a u8 to register width, then write the slot. */
  setU8Arg(index: number, value: number): void {
    this.setI32Arg(index, value & 0xff);
  }
  /** Sign-extend an s16 to register width, then write the slot. */
  setI16Arg(index: number, value: number): void {
    this.setI32Arg(index, (value << 16) >> 16);
  }
  /** Zero-extend a u16 to register width, then write the slot. */
  setU16Arg(index: number, value: number): void {
    this.setI32Arg(index, value & 0xffff);
  }

  /** Write the void return (ret_class VOID, slot zeroed) and yield the
   *  canonical i32 result (0). */
  setRetVoid(): number {
    this.dv.setUint32(this.base + FRAME_RET_CLASS_OFFSET, FrameValueClass.VOID, true);
    this.dv.setBigInt64(this.base + FRAME_RET_OFFSET, 0n, true);
    return 0;
  }

  /** Write an i32 return and yield its canonical i32 view (the value). */
  setRetI32(value: number): number {
    const v = value | 0;
    this.dv.setUint32(this.base + FRAME_RET_CLASS_OFFSET, FrameValueClass.I32, true);
    this.dv.setBigInt64(this.base + FRAME_RET_OFFSET, 0n, true);
    this.dv.setInt32(this.base + FRAME_RET_OFFSET, v, true);
    return v;
  }

  /**
   * Write an i64 return and yield the PPC-r3 view (the HIGH word). PPC32 EABI
   * returns i64 in r3:r4 with the HIGH word in r3 — a PPC caller consuming a
   * 32-bit result out of an i64-returning callee reads r3. The companion
   * thunk's own i32 wire result is the LOW word (a known mismatch flagged by
   * the dispatch-companion adversarial review); it must never be used as a
   * result — the frame's 8-byte ret slot is the authoritative return channel,
   * and this helper's return matches retPpcR3View().
   */
  setRetI64(value: bigint): number {
    this.dv.setUint32(this.base + FRAME_RET_CLASS_OFFSET, FrameValueClass.I64, true);
    this.dv.setBigInt64(this.base + FRAME_RET_OFFSET, value, true);
    return Number(BigInt.asIntN(32, value >> 32n));
  }

  /** Write an f32 return and yield the canonical i32 view (0). */
  setRetF32(value: number): number {
    this.dv.setUint32(this.base + FRAME_RET_CLASS_OFFSET, FrameValueClass.F32, true);
    this.dv.setBigInt64(this.base + FRAME_RET_OFFSET, 0n, true);
    this.dv.setFloat32(this.base + FRAME_RET_OFFSET, value, true);
    return 0;
  }

  /** Write an f64 return and yield the canonical i32 view (0). */
  setRetF64(value: number): number {
    this.dv.setUint32(this.base + FRAME_RET_CLASS_OFFSET, FrameValueClass.F64, true);
    this.dv.setFloat64(this.base + FRAME_RET_OFFSET, value, true);
    return 0;
  }

  /** The full-width i64 ret slot — the AUTHORITATIVE return channel. */
  retI64(): bigint {
    return this.dv.getBigInt64(this.base + FRAME_RET_OFFSET, true);
  }

  /**
   * The PPC-caller-visible r3 word of whatever return the frame holds:
   * i32 -> the value itself; i64 -> the HIGH word (PPC32 EABI r3=high,
   * r4=low); f32/f64/void -> 0 (float returns live in f1, not r3).
   *
   * NORMATIVE (dispatch-companion adversarial review): the canonical thunk's
   * i32 wire result takes the LOW word for i64 returns and therefore
   * DISAGREES with a real PPC caller's r3 read. Bridge results are always
   * derived from the frame's 8-byte ret slot via THIS view — never from the
   * thunk/adapter i32 wire value.
   */
  retPpcR3View(): number {
    switch (this.retClass) {
      case FrameValueClass.I32:
        return this.dv.getInt32(this.base + FRAME_RET_OFFSET, true);
      case FrameValueClass.I64:
        return Number(BigInt.asIntN(32, this.dv.getBigInt64(this.base + FRAME_RET_OFFSET, true) >> 32n));
      default:
        return 0;
    }
  }
}
