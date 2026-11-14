/** Bounded offline HSD_PObjAnimAll (8024a6ac), chunk_0071.c:1517–1540.
 * Each polygon object interprets its AObj at +18 with the same object as owner
 * and its resolved class-info+48 callback, then reads the current next+04.
 * No geometry/shape receiver, class reconstruction or live adapter is supplied.
 * classUpdate48 is a resolved selector, not a PObj+48 field. The decompiled
 * call gives no separate statement ordering the AObj and callback loads; both
 * are sampled before the call here. No instruction-level load-order claim.
 *
 * Symbolic bindings are owned, sealed data records. Non-proxy own-data inputs
 * are copied without calling getters. The required interpreter is captured once
 * per list and invoked with its original effect-table receiver, even for null
 * AObj/callback targets. Null PObj lists bypass all validation. Effects must run
 * real synchronous interpretation or explicitly refuse unsupported work, use
 * the enclosing tree's actual AObj counters, and return undefined. This helper
 * never resets counters or invokes global completion callbacks.
 *
 * Host writable/type checks occur per accessed field, not by whole-list or
 * post-effect preflight. Consumed fields and excluded nodes are not reread.
 * Cycles/revisits, visit-budget excess and same-runtime non-null reentry are
 * refused; caught reentry still aborts the outer pass. Failures keep completed
 * effects, with no rollback. Deferred JS must not be scheduled: rejecting a
 * Promise cannot cancel previously scheduled work. No game parity is claimed.
 */
export interface SourcePObjAnimationBinding {
  next04: symbol | null;
  aobj18: symbol | null;
  classUpdate48: symbol | null;
}
export interface SourcePObjAnimationEffects {
  interpretAObj(aobj: symbol | null, owner: symbol, callback: symbol | null): void;
}
export interface SourcePObjAnimationRuntime {
  createPObj(initial: SourcePObjAnimationBinding): symbol;
  getPObj(identity: symbol): SourcePObjAnimationBinding;
  animateAll(identity: symbol | null, effects: SourcePObjAnimationEffects): void;
}
const keys = ['next04', 'aobj18', 'classUpdate48'] as const;
function fail(reason: string): never {
  throw Error(`[pobj-animation] ${reason}; offline execution aborted, prior effects are not rolled back`);
}
function identity(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: expected opaque symbol or null`);
}
function ownValue(record: object, key: string, writable: boolean): unknown {
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
export function createSourcePObjAnimationRuntime(maxNodes = 4096): SourcePObjAnimationRuntime {
  if (!Number.isSafeInteger(maxNodes) || maxNodes < 1) fail('maxNodes must be a positive safe integer');
  const objects = new Map<symbol, SourcePObjAnimationBinding>();
  let busy = false, reentered = false;
  const getPObj = (id: symbol): SourcePObjAnimationBinding => {
    const object = objects.get(id);
    if (!object) fail('unknown/non-owned PObj identity');
    return object;
  };
  const read = (object: SourcePObjAnimationBinding, key: keyof SourcePObjAnimationBinding): symbol | null => {
    const value = ownValue(object, key, true); identity(value, key); return value;
  };
  return Object.freeze({
    createPObj(initial: SourcePObjAnimationBinding): symbol {
      if (initial === null || typeof initial !== 'object') fail('initial binding data record required');
      const copied: Partial<SourcePObjAnimationBinding> = {};
      for (const key of keys) {
        const value = ownValue(initial, key, false); identity(value, key);
        Object.defineProperty(copied, key, {value, writable: true, enumerable: true});
      }
      const id = Symbol('owned PObj animation binding');
      objects.set(id, Object.seal(copied) as SourcePObjAnimationBinding); return id;
    },
    getPObj,
    animateAll(id: symbol | null, effects: SourcePObjAnimationEffects): void {
      if (id === null) return;
      if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
      if (effects === null || typeof effects !== 'object') fail('effect data table required');
      const interpret = ownValue(effects, 'interpretAObj', false);
      if (typeof interpret !== 'function') fail('interpretAObj: own data-function required');
      busy = true; reentered = false;
      try {
        const seen = new Set<symbol>(); let current: symbol | null = id;
        while (current !== null) {
          identity(current, 'PObj list');
          if (seen.has(current)) fail('cycle/revisited PObj is unsupported');
          if (seen.size >= maxNodes) fail('PObj visit budget exhausted');
          const object = getPObj(current); seen.add(current);
          const callback = read(object, 'classUpdate48'), aobj = read(object, 'aobj18');
          let result: unknown;
          try {result = Reflect.apply(interpret, effects, [aobj, current, callback]);}
          catch (error) {fail(`interpretAObj: effect threw (${String(error)})`);}
          if (result !== undefined) fail('interpretAObj: effect must complete synchronously and return undefined');
          if (reentered) fail('same-runtime reentry was caught inside an effect');
          current = read(object, 'next04');
        }
      } finally {busy = false;}
    },
  });
}
