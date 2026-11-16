/** Canonical bounded decoded storage for the existing actual soundEventTable
 * (+4e8) pointer. This is not a second actor owner, selector, archive resolver,
 * decoder or provenance claim. Callers provide known windows at their actual
 * logical offsets; unknown gaps refuse only on a reached read. No zero padding.
 *
 * Factory inputs are copied non-shared Uint8Array views in explicit own-data
 * records. Empty coverage is allowed; individual windows must be nonempty and
 * disjoint (adjacency is allowed). Host budgets are 4096 windows and 16MiB in
 * aggregate, independently of uint32 logical coordinates. Original records,
 * arrays and views cannot mutate a returned owner. The frozen public object
 * exposes no backing arrays. Non-proxy inputs and unmodified platform intrinsics
 * are the contract; caught reentry poisons the current factory/read operation.
 * Historical complete Uint8Array tables retain reached own-data byte reads.
 */
import {copyDecodedByteWindows, readDecodedByteWindow, type OwnedDecodedByteWindow,
  type SourceDecodedByteWindow, type SourceDecodedByteWindowLimits} from './bounded-byte-windows.js';

declare const soundTableBrand: unique symbol;
export interface SourceActorSoundTable {
  readonly [soundTableBrand]: true;
  readByte(offset: number): number;
}
export type SourceActorSoundEventTable = Uint8Array | SourceActorSoundTable;
export type SourceActorSoundByteWindow = SourceDecodedByteWindow;
export type SourceActorSoundTableLimits = SourceDecodedByteWindowLimits;
const backing = new WeakMap<object, readonly OwnedDecodedByteWindow[]>();
let busy = false, poisoned = false;
function fail(reason: string): never {throw Error(`[actor-sound-table] ${reason}; offline byte read/import aborted`);}
function check(): void {if (poisoned) fail('caught same-runtime reentry');}
function guard<T>(run: () => T): T {
  if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
  busy = true; poisoned = false;
  try {const result = run(); check(); return result;} finally {busy = false;}
}
export function isSourceActorSoundTable(value: unknown): value is SourceActorSoundTable {
  return value !== null && typeof value === 'object' && backing.has(value);
}
function readByte(table: unknown, offset: number): number {
  if (typeof offset !== 'number' || !Number.isInteger(offset) || offset < 0 || offset > 0xffffffff)
    fail('byte offset: uint32 required');
  if (isSourceActorSoundTable(table)) {
    const value = readDecodedByteWindow(backing.get(table)!, offset);
    if (value === undefined) fail(`byte${offset}: uncovered decoded byte window`);
    return value;
  }
  // Native view validation rejects prototype-only impostors and proxy wrappers.
  // The value is still read through its own descriptor, never an indexed getter.
  if (!ArrayBuffer.isView(table) || !(table instanceof Uint8Array))
    fail('explicit Uint8Array or genuine source sound table required');
  const p = Object.getOwnPropertyDescriptor(table, String(offset)); check();
  if (!p || !('value' in p)) fail(`${offset}: own data property required`);
  const value: unknown = p.value;
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 255)
    fail(`${offset}: byte integer out of bounds`);
  return value;
}
export function createSourceActorSoundTable(
  windows: readonly SourceActorSoundByteWindow[], limits: SourceActorSoundTableLimits = {},
): SourceActorSoundTable {
  return guard(() => {
    const copies = copyDecodedByteWindows(windows, limits, fail, check);
    const table = Object.freeze({readByte(this: SourceActorSoundTable, offset: number): number {return guard(() => {
      // A copied/borrowed method does not authenticate an arbitrary receiver.
      if (!isSourceActorSoundTable(this)) fail('genuine source sound table receiver required');
      return readByte(this, offset);
    });}}) as SourceActorSoundTable;
    backing.set(table, copies); return table;
  });
}
export function readSourceActorSoundTableByte(table: unknown, offset: number): number {
  return guard(() => readByte(table, offset));
}
