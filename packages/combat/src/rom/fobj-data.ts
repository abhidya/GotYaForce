/** Bounded offline FObjLoadData (802489f4) and the FObjInterpret wait reader.
 * Evidence: research/decomp/ghidra-export/chunk_0071.c:278–866,1001–1040.
 * Private copied streams and opaque cursors model nonaliasing byte storage, not
 * RAM addresses. Each read must fit BOTH the declared length and the copied
 * stream. No arbitrary pointer subtraction, wrapped address space, or aliasing.
 *
 * Accepted packed counts are 1..65535, at most two continuation bytes after the
 * command (bits 3..9 and 10..16). Addition uses exact integers; encodings that
 * would truncate the halfword or require PPC oversized shifts are unsupported.
 * Failure is an offline diagnostic, NOT retail behavior: earlier stores remain;
 * the failing bounded byte/read does not advance, while earlier consumption
 * remains. Float reads consume four individual bytes in source order. Retail
 * has only an entry length guard; these additional bounds and fault handling
 * deliberately do not reproduce retail fault-write behavior. Nonfinite float payloads
 * consume their bytes but abort before storing the decoded value. Unknown
 * formats abort rather than reproducing the retail fallback zero.
 * Original instruction audit confirms signed LE16 and signed shift31 divisor;
 * ordinary finite integer conversion/fdivs is modeled with Math.fround.
 * loadWait separately implements the bounded state3 duration reader.
 * No decoded-key adapter or interpolation fallback.
 */
import type {SourceFObjHeader} from './fobj-list.js';
interface Cursor { readonly base: symbol; readonly offset: number }
export interface SourceFObjData {
  createData(bytes: Uint8Array): symbol;
  cursorAt(base: symbol, offset: number): symbol;
  cursorOffset(base: symbol, cursor: symbol): number;
  loadData(node: SourceFObjHeader): number;
  loadWait(node: SourceFObjHeader): number;
}
function fail(reason: string): never {
  throw Error(`[fobj-data] ${reason}; offline execution aborted, prior writes are not rolled back`);
}
/** 16 MiB is a host allocation bound, not a source stream-size constant. */
export const SOURCE_FOBJ_MAX_DATA_BYTES = 16 * 1024 * 1024;
/** @internal Runtime implementation helper. The required validator must reject
 * non-owned/non-writable headers and invalid field widths before any reads.
 * Public callers should use createSourceFObjRuntime, not construct this helper. */
export function createSourceFObjData(validateOwnedHeader: (node: SourceFObjHeader) => void): SourceFObjData {
  if (typeof validateOwnedHeader !== 'function') fail('owned-header validator required');
  const streams = new Map<symbol, Uint8Array>();
  const cursors = new Map<symbol, Cursor>();
  const positions = new Map<symbol, Map<number, symbol>>();
  const streamFor = (base: symbol): Uint8Array => {
    const stream = streams.get(base);
    if (!stream) fail('unknown/non-owned stream base');
    return stream;
  };
  const cursorAt = (base: symbol, offset: number): symbol => {
    const stream = streamFor(base);
    if (!Number.isInteger(offset) || offset < 0 || offset > stream.length) fail('cursor outside copied stream');
    const known = positions.get(base)!.get(offset);
    if (known) return known;
    const id = Symbol('owned FObj cursor');
    cursors.set(id, Object.freeze({base, offset}));
    positions.get(base)!.set(offset, id);
    return id;
  };
  const cursorOffset = (base: symbol, cursor: symbol): number => {
    streamFor(base);
    const position = cursors.get(cursor);
    if (!position || position.base !== base) fail('cursor/base provenance mismatch');
    return position.offset;
  };
  return {
    createData(bytes) {
      if (!(bytes instanceof Uint8Array) || bytes.length > SOURCE_FOBJ_MAX_DATA_BYTES ||
        !(bytes.buffer instanceof ArrayBuffer)) fail('expected bounded non-shared Uint8Array');
      const base = Symbol('owned FObj stream');
      streams.set(base, new Uint8Array(bytes));
      cursors.set(base, Object.freeze({base, offset: 0}));
      positions.set(base, new Map([[0, base]]));
      return base;
    },
    cursorAt,
    cursorOffset,
    loadWait(n) {
      validateOwnedHeader(n);
      if ((n.flags10 & 15) !== 3) fail('source assertion: wait state must be 3');
      if (n.base08 === null || n.cursor04 === null) fail('null stream/cursor');
      const base = n.base08, stream = streamFor(base);
      let offset = cursorOffset(base, n.cursor04);
      if (offset >= n.length0c) return 6; // Local state only: do NOT store six.
      let value = 0, shift = 0, byte: number;
      do {
        // Five bytes cover shifts 0..28. Reject a sixth instead of modeling
        // PPC slw's large-shift behavior. Overlong encodings within this bound
        // are accepted; the final source halfword store truncates modulo 65536.
        if (shift > 28) fail('wait requires unsupported oversized encoding');
        if (offset >= n.length0c || offset >= stream.length) fail('truncated wait');
        const previous = offset;
        n.cursor04 = cursorAt(base, ++offset); // Source store precedes byte load.
        byte = stream[previous]!;
        value = (value | ((byte & 127) << shift)) >>> 0;
        shift += 7;
      } while ((byte & 128) !== 0);
      n.half1a = value & 65535;
      n.flags10 |= 0x20;
      n.flags10 = (n.flags10 & 0xf0) | 2;
      return 2;
    },
    loadData(n) {
      validateOwnedHeader(n);
      if (n.base08 === null || n.cursor04 === null) fail('null stream/cursor');
      const base = n.base08;
      const stream = streamFor(base);
      let offset = cursorOffset(base, n.cursor04);
      // Offsets are nonnegative bounded integers, hence exactly the source
      // unsigned cursor-minus-base difference in this supported pointer domain.
      if (offset >= n.length0c) return 6;
      const requireBytes = (count: number): void => {
        if (offset + count > n.length0c || offset + count > stream.length) fail('truncated stream');
      };
      const readByte = (): number => {
        requireBytes(1);
        const value = stream[offset]!;
        n.cursor04 = cursorAt(base, ++offset);
        return value;
      };
      const readValue = (format: number): number => {
        let value: number;
        if (format === 0) {
          // Four separate source byte loads/stores; retain partial advancement
          // when a later byte falls outside the supported buffer.
          const bytes = new Uint8Array(4);
          for (let i = 0; i < 4; i++) bytes[i] = readByte();
          value = new DataView(bytes.buffer).getFloat32(0, true);
        } else {
          const kind = format & 0xe0;
          if (kind === 0x20 || kind === 0x40) {
            requireBytes(2); // Source reads both bytes before its cursor store.
            value = stream[offset]! + stream[offset + 1]! * 256;
            offset += 2; n.cursor04 = cursorAt(base, offset);
            if (kind === 0x20 && value >= 32768) value -= 65536;
          } else if (kind === 0x60 || kind === 0x80) {
            value = readByte();
            if (kind === 0x60 && value >= 128) value -= 256;
          } else fail(`unsupported numeric format 0x${format.toString(16)}`);
          const fractionalBits = format & 31;
          // Signed PPC slw result converted to float: bit31 is NEGATIVE.
          const divisor = fractionalBits === 31 ? -(2 ** 31) : 2 ** fractionalBits;
          value = Math.fround(value / divisor);
        }
        if (!Number.isFinite(value)) fail('nonfinite decoded float32');
        return value;
      };
      n.byte12 = n.byte11;
      if (n.half16 === 0) {
        requireBytes(1);
        n.byte11 = stream[offset]! & 15; // Source opcode store before cursor advance.
        let byte = readByte();
        let count = ((byte >> 4) & 7) + 1;
        let shift = 3;
        while ((byte & 128) !== 0) {
          if (shift > 10) fail('packed count requires unsupported oversized encoding');
          byte = readByte();
          count += (byte & 127) * 2 ** shift;
          if (count > 65535) fail('packed count exceeds supported halfword domain');
          shift += 7;
        }
        n.half16 = count;
      }
      n.half16 = (n.half16 - 1) & 65535;
      const op = n.byte11;
      if (op === 0 || op > 6) return 0;
      const state = n.flags10 & 15;
      if (state !== 1 && state !== 2) fail('source assertion: loading state must be 1 or 2');
      if (op === 5) {
        n.value28 = n.value2c;
        n.value2c = readValue(n.format15);
        return state;
      }
      if (op === 6) {
        if ((n.flags10 & 0x40) !== 0) {
          n.byte12 = n.byte11;
          n.flags10 &= 0xbf;
          n.flags10 |= 0x80;
          n.value20 = n.value24;
        }
        n.value24 = readValue(n.format14);
        n.flags10 |= 0x40;
      } else {
        n.value20 = n.value24;
        if (op === 3) n.value28 = n.value2c;
        n.value24 = readValue(n.format14);
        if (op === 4) {
          n.value28 = n.value2c;
          n.value2c = readValue(n.format15);
        } else if (op === 3 || n.byte12 !== 5) {
          if (op !== 3) n.value28 = n.value2c;
          n.value2c = 0;
        }
      }
      const nextState = state === 1 ? 3 : 4;
      n.flags10 = (n.flags10 & 0xf0) | nextState;
      return nextState;
    },
  };
}
