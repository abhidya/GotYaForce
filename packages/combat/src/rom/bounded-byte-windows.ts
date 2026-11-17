/** Internal host storage, not a source pointer or scalar owner. Explicit decoded
 * windows are copied without filling gaps. Non-proxy own-data inputs and native,
 * unmodified platform intrinsics are the supported contract. Consumers retain
 * their own genuine identities and reentry guards. No archive access occurs.
 */
export interface SourceDecodedByteWindow {readonly offset: number; readonly bytes: Uint8Array}
export interface SourceDecodedByteWindowLimits {maxWindows?: number; maxBytes?: number}
export interface OwnedDecodedByteWindow {readonly offset: number; readonly bytes: Uint8Array}
const BYTE_CAP = 16 * 1024 * 1024, WINDOW_CAP = 4096;

export function copyDecodedByteWindows(
  input: readonly SourceDecodedByteWindow[], limits: SourceDecodedByteWindowLimits,
  fail: (reason: string) => never, check: () => void,
): readonly OwnedDecodedByteWindow[] {
  const own = (record: unknown, key: string): unknown => {
    if (record === null || typeof record !== 'object') fail(`${key}: own-data record required`);
    const p = Object.getOwnPropertyDescriptor(record, key); check();
    if (!p || !('value' in p)) fail(`${key}: own data property required`);
    return p.value;
  };
  const uint = (value: unknown, label: string): number => {
    if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 0xffffffff)
      fail(`${label}: uint32 required`);
    return value === 0 ? 0 : value;
  };
  if (limits === null || typeof limits !== 'object') fail('window limits: own-data record required');
  const budget = (key: keyof SourceDecodedByteWindowLimits, ceiling: number): number => {
    const p = Object.getOwnPropertyDescriptor(limits, key); check();
    if (p === undefined) return ceiling;
    if (!('value' in p)) fail(`${key}: own data property required`);
    const value = uint(p.value, key);
    if (value < 1 || value > ceiling) fail(`${key}: expected 1..${ceiling}`);
    return value;
  };
  const maxWindows = budget('maxWindows', WINDOW_CAP), maxBytes = budget('maxBytes', BYTE_CAP);
  if (!Array.isArray(input)) fail('explicit decoded window array required');
  const count = uint(own(input, 'length'), 'window count');
  if (count > maxWindows) fail('window count budget exceeded');
  const result: OwnedDecodedByteWindow[] = [];
  let total = 0;
  for (let index = 0; index < count; index++) {
    const window = own(input, String(index));
    const offset = uint(own(window, 'offset'), 'window offset'), bytes = own(window, 'bytes');
    const typed = Object.getPrototypeOf(Uint8Array.prototype) as object;
    const tag = Reflect.apply(Object.getOwnPropertyDescriptor(typed, Symbol.toStringTag)!.get!, bytes, []); check();
    if (tag !== 'Uint8Array') fail('non-shared Uint8Array window required');
    const buffer = Reflect.apply(Object.getOwnPropertyDescriptor(typed, 'buffer')!.get!, bytes, []); check();
    try {Reflect.apply(Object.getOwnPropertyDescriptor(ArrayBuffer.prototype, 'byteLength')!.get!, buffer, []);}
    catch {fail('non-shared Uint8Array window required');}
    check();
    const length = Reflect.apply(Object.getOwnPropertyDescriptor(typed, 'length')!.get!, bytes, []) as number; check();
    if (length === 0) fail('nonempty decoded byte window required');
    if (offset + length > 0x100000000) fail('window extent overflows uint32 coordinates');
    total += length;
    if (total > maxBytes) fail('aggregate copied byte budget exceeded');
    const copy = new Uint8Array(length);
    try {Reflect.apply(Uint8Array.prototype.set, copy, [bytes]);}
    catch {fail('detached Uint8Array window unsupported');}
    check(); result.push({offset, bytes: copy});
  }
  result.sort((a, b) => a.offset - b.offset);
  for (let index = 1; index < result.length; index++) {
    const previous = result[index - 1]!, current = result[index]!;
    if (previous.offset + previous.bytes.length > current.offset) fail('overlapping decoded byte windows');
  }
  return result;
}

/** The caller validates the coordinate. Only this reached byte is looked up;
 * missing intervals never become synthetic zero bytes. */
export function readDecodedByteWindow(windows: readonly OwnedDecodedByteWindow[], at: number): number | undefined {
  let low = 0, high = windows.length;
  while (low < high) {
    const middle = (low + high) >>> 1, window = windows[middle]!;
    if (at < window.offset) high = middle;
    else if (at >= window.offset + window.bytes.length) low = middle + 1;
    else return window.bytes[at - window.offset]!;
  }
  return undefined;
}
