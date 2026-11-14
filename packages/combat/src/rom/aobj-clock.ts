/** Offline scalar control for 80243aec / 80243b08 / 80243b90 / 80243bd0 / 80243fc0.
 * Source: chunk_0070.c:2512–2536,2569–2670,2814–2857; DOL arithmetic/order audit in
 * research/decomp/double-source-owned-dispatch-plan-2026-11-12.md.
 *
 * Only factory-created, nonaliased data records are admitted. Clocks and rate-setter
 * arguments must already be finite float32 values (including signed zero); request
 * arguments are finite doubles. JS IEEE round-to-nearest arithmetic is assumed, not arbitrary PPC FP
 * environments. Symbol identities stand for separately owned FObj lists/callbacks,
 * never RAM pointers or overlapping storage. Effects MUST perform the synchronous
 * FObj operation, including callbacks, or throw an unsupported-operation error.
 * Effects must not schedule deferred mutations.
 * There are deliberately no default effects, even for an empty list.
 *
 * Effects may change live AObj fields. Validation happens after each boundary;
 * failure stops the offline scenario but DOES NOT roll back writes or effects
 * already executed. Async effects and request/interpret reentry on the same AObj
 * are unsupported; rate and flag setters remain available during callbacks.
 * Capture05 has no AObj headers and does not dynamically validate this helper.
 */
export const AOBJ_STOPPED = 0x40000000;
export const AOBJ_LOOP = 0x20000000;
export const AOBJ_NO_CALLBACK = 0x10000000;
export const AOBJ_REQUEST = 0x08000000;
export const AOBJ_WRAPPED = 0x04000000;
export type FObjListIdentity = symbol | null;
export type AObjCallbackIdentity = symbol | null;
export interface SourceAObj {
  flags: number;
  frame: number;
  rewind: number;
  end: number;
  rate: number;
  fobjs: FObjListIdentity;
  /** +0x18 reference; absent initial values become null on owned records. */
  joint18?: symbol | null;
}
export interface SourceAObjCounters { running: number; stopped: number }
export interface SourceAObjEffects {
  requestAll(list: FObjListIdentity, frame: number): void;
  stopAll(list: FObjListIdentity, delta: number, callback: AObjCallbackIdentity): void;
  interpretAll(list: FObjListIdentity, delta: number, callback: AObjCallbackIdentity): void;
}
const states = new WeakSet<object>();
const counters = new WeakSet<object>();
const busy = new WeakSet<object>();
function fail(where: string, why: string): never {
  throw new Error(`[aobj-clock] ${where}: ${why}; offline execution aborted, prior writes/effects are not rolled back`);
}
function uint32(value: number, where: string): void {
  if (!Number.isInteger(value) || value < 0 || value > 0xffffffff) fail(where, 'expected uint32');
}
function float32(value: number, where: string): void {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(where, 'expected finite source float32');
}
function rounded(value: number, where: string): number {
  const result = Math.fround(value);
  if (!Number.isFinite(result)) fail(where, 'nonfinite/overflow float32 result');
  return result;
}
function validate(a: SourceAObj, where: string): void {
  if (!states.has(a)) fail(where, 'expected factory-created nonaliased AObj');
  for (const key of ['flags', 'frame', 'rewind', 'end', 'rate', 'fobjs']) {
    if (!Object.getOwnPropertyDescriptor(a, key)?.writable) fail(where, `non-writable ${key} is unsupported`);
  }
  uint32(a.flags, `${where}.flags`);
  for (const key of ['frame', 'rewind', 'end', 'rate'] as const) float32(a[key], `${where}.${key}`);
  if (a.fobjs !== null && typeof a.fobjs !== 'symbol') fail(where, 'FObj list must be an opaque symbol or null');
}
function validateCounters(c: SourceAObjCounters, where: string): void {
  if (!counters.has(c)) fail(where, 'expected factory-created nonaliased counters');
  for (const key of ['running', 'stopped']) {
    if (!Object.getOwnPropertyDescriptor(c, key)?.writable) fail(where, `non-writable counter ${key} is unsupported`);
  }
  uint32(c.running, `${where}.running`);
  uint32(c.stopped, `${where}.stopped`);
}
export function createSourceAObj(initial: SourceAObj): SourceAObj {
  // Copy each scalar into sealed data properties, never retain a backing object.
  const a = Object.seal({flags: initial.flags, frame: initial.frame, rewind: initial.rewind,
    end: initial.end, rate: initial.rate, fobjs: initial.fobjs, joint18: initial.joint18 ?? null});
  states.add(a);
  validate(a, 'create');
  return a;
}
/** Ownership-only query for composed owners. Does not consume any header field. */
export function isLiveSourceAObj(a: SourceAObj): boolean {return states.has(a);}
/** 80243f8c: logical pool release only. No field erasure, physical pool reuse,
 * allocation capacity, or OOM is modeled. Busy request/interpret records cannot
 * be released. Retained references cease to be admitted by all clock operations.
 */
export function freeSourceAObj(a: SourceAObj | null): void {
  if (a === null) return;
  if (!states.has(a)) fail('free', 'expected factory-created nonaliased AObj');
  if (busy.has(a)) fail('free', 'busy request/interpret lifetime is unsupported');
  states.delete(a);
}
export function createSourceAObjCounters(running = 0, stopped = 0): SourceAObjCounters {
  const c = Object.seal({running, stopped});
  counters.add(c);
  validateCounters(c, 'create counters');
  return c;
}
/** zz_0243fc0 (80243fc0), chunk_0070.c:2814–2827: null no-op, then stfs at +0x10.
 * Only already-finite source float32 inputs are admitted. Arbitrary double stfs
 * storage conversion is not modeled as round-to-nearest float32 arithmetic.
 * This store neither reads the old rate nor inspects other AObj/FObj fields.
 * It is allowed during synchronous FObj callbacks, including a busy interpreter.
 */
export function setSourceAObjRate(a: SourceAObj | null, rate: number): void {
  if (a === null) return;
  if (!states.has(a)) fail('set rate', 'expected factory-created nonaliased AObj');
  const property = Object.getOwnPropertyDescriptor(a, 'rate');
  if (!property || !('value' in property) || !property.writable) {
    fail('set rate', 'non-writable rate data property is unsupported');
  }
  float32(rate, 'set rate');
  a.rate = rate;
}
/** 80243fd0, chunk_0070.c:2829–2841: null bypass then stfs at +0x08.
 * Already-finite exact-f32 inputs only; no old field or unrelated state read.
 * Like the rate setter, this remains available during synchronous callbacks.
 */
export function setSourceAObjRewindFrame(a: SourceAObj | null, frame: number): void {
  if (a === null) return;
  if (!states.has(a)) fail('set rewind', 'expected factory-created nonaliased AObj');
  const property = Object.getOwnPropertyDescriptor(a, 'rewind');
  if (!property || !('value' in property) || !property.writable) {
    fail('set rewind', 'non-writable rewind data property is unsupported');
  }
  float32(frame, 'set rewind');
  a.rewind = frame;
}
/** 80243fe0, chunk_0070.c:2845–2857: null bypass then stfs at +0x0c.
 * Exact-f32 admission avoids guessing arbitrary-double storage conversion.
 * Ownership and the written field alone are checked; old end is overwritten.
 */
export function setSourceAObjEndFrame(a: SourceAObj | null, frame: number): void {
  if (a === null) return;
  if (!states.has(a)) fail('set end', 'expected factory-created nonaliased AObj');
  const property = Object.getOwnPropertyDescriptor(a, 'end');
  if (!property || !('value' in property) || !property.writable) {
    fail('set end', 'non-writable end data property is unsupported');
  }
  float32(frame, 'set end');
  a.end = frame;
}
/** 80243aec/80243b08: null bypass, otherwise change only mask bits 0x30000000.
 * Ownership and the consumed flags field are the only header checks. These
 * source helpers remain available during synchronous request/interpret effects.
 */
function changeSourceAObjFlags(a: SourceAObj | null, mask: number, set: boolean): void {
  if (a === null) return;
  const where = set ? 'set flags' : 'clear flags';
  if (!states.has(a)) fail(where, 'expected factory-created nonaliased AObj');
  const property = Object.getOwnPropertyDescriptor(a, 'flags');
  if (!property || !('value' in property) || !property.writable) {
    fail(where, 'non-writable flags data property is unsupported');
  }
  uint32(property.value, `${where}.flags`);
  uint32(mask, `${where}.mask`);
  const selected = mask & 0x30000000;
  a.flags = (set ? property.value | selected : property.value & ~selected) >>> 0;
}
export function setSourceAObjFlags(a: SourceAObj | null, mask: number): void {
  changeSourceAObjFlags(a, mask, true);
}
export function clearSourceAObjFlags(a: SourceAObj | null, mask: number): void {
  changeSourceAObjFlags(a, mask, false);
}
function validateEffects(e: SourceAObjEffects): void {
  if (!e || ['requestAll', 'stopAll', 'interpretAll'].some(key => typeof e[key as keyof SourceAObjEffects] !== 'function')) {
    fail('effects', 'all three synchronous FObj effects are required');
  }
}
function effect(a: SourceAObj, name: string, invoke: () => unknown): void {
  let result: unknown;
  try { result = invoke(); }
  catch (error) { fail(name, `effect threw (${String(error)})`); }
  if (result !== undefined) fail(name, 'effect must complete synchronously and return undefined');
  validate(a, `after ${name}`);
}
export function requestSourceAObj(a: SourceAObj | null, request: number, e: SourceAObjEffects): void {
  if (a === null) return;
  validate(a, 'request entry');
  validateEffects(e);
  if (busy.has(a)) fail('request', 'same-AObj reentry is unsupported');
  if (!Number.isFinite(request)) fail('request', 'expected finite double argument');
  const frame = rounded(request, 'request frame');
  busy.add(a);
  try {
    a.frame = frame;
    a.flags = ((a.flags & ~AOBJ_STOPPED) | AOBJ_REQUEST) >>> 0;
    // The original double is forwarded, not the stored float32 frame.
    effect(a, 'requestAll', () => e.requestAll(a.fobjs, request));
  } finally { busy.delete(a); }
}
export function interpretSourceAObj(a: SourceAObj | null, callback: AObjCallbackIdentity,
  e: SourceAObjEffects, counts: SourceAObjCounters): void {
  if (a === null) return;
  validate(a, 'interpret entry');
  if (a.flags & AOBJ_STOPPED) return; // No effects or accounting for early return.
  validateEffects(e);
  validateCounters(counts, 'interpret counters');
  if (callback !== null && typeof callback !== 'symbol') fail('interpret', 'callback must be an opaque symbol or null');
  if (busy.has(a)) fail('interpret', 'same-AObj reentry is unsupported');
  busy.add(a);
  try {
    let delta = 0; // Positive zero, including a request with a negative-zero rate.
    if (a.flags & AOBJ_REQUEST) a.flags = (a.flags & ~AOBJ_REQUEST) >>> 0;
    else { delta = a.rate; a.frame = rounded(a.frame + delta, 'advance'); }
    if ((a.flags & AOBJ_LOOP) && a.end <= a.frame) {
      if (a.rewind < a.end) {
        effect(a, 'wrap stopAll', () => e.stopAll(a.fobjs, delta, callback));
        // StopAll can run user callbacks. Reload all operands, then the list.
        const numerator = rounded(a.frame - a.rewind, 'wrap frame-rewind');
        const denominator = rounded(a.end - a.rewind, 'wrap end-rewind');
        if (denominator === 0) fail('wrap fmod', 'zero denominator after stopAll');
        const remainder = numerator % denominator; // double fmod, no intermediate frsp
        a.frame = rounded(a.rewind + remainder, 'wrap rewind+fmod');
        effect(a, 'wrap requestAll', () => e.requestAll(a.fobjs, a.frame));
      } else a.frame = a.end;
      a.flags = (a.flags | AOBJ_WRAPPED) >>> 0;
      delta = 0;
    } else a.flags = (a.flags & ~AOBJ_WRAPPED) >>> 0;
    effect(a, 'interpretAll', () => e.interpretAll(a.fobjs, delta,
      (a.flags & AOBJ_NO_CALLBACK) ? null : callback));
    if (!(a.flags & AOBJ_LOOP) && a.end <= a.frame) {
      effect(a, 'end stopAll', () => e.stopAll(a.fobjs, a.rate, callback));
      a.flags = (a.flags | AOBJ_STOPPED) >>> 0;
    }
    // Source global uint32 increments; callbacks may have changed the live flags.
    validateCounters(counts, 'final counters');
    if (a.flags & AOBJ_STOPPED) counts.stopped = (counts.stopped + 1) >>> 0;
    else counts.running = (counts.running + 1) >>> 0;
  } finally { busy.delete(a); }
}
