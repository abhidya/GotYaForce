/** Bounded offline HSD_TObjAnimAll (8023e690), chunk_0069.c:6953–6976.
 * Each texture interprets AObj+64 with that texture as owner and its resolved
 * class-info+48 callback, then follows current next+08. Binding offsets differ
 * from the superficially similar PObj list. The source C call expression does
 * not establish relative AObj/callback load order; host samples callback first.
 *
 * Bindings share identities with the actual bounded texture scalar receiver.
 * classUpdate48 is a resolved class selector, not TObj+48 or class memory. No
 * image/palette/color receiver, texture upload, matrix rebuild or live adapter
 * is implied. Use real synchronous interpretation with the enclosing tree's
 * actual AObj counters or explicitly refuse unsupported work. No counter reset
 * or completion callback is performed here. Null targets reach the interpreter;
 * a null list bypasses validation.
 *
 * Non-proxy own-data bindings/effects, copied scalar records, per-access field
 * checks, static interpreter snapshot and original-table this match the other
 * bounded dispatchers. No scalar-header or whole-list preflight is added to
 * animation: scalar validation belongs to the receiver when a callback uses it.
 * Consumed fields are not reread. Cycles/revisits, excess visits, non-undefined
 * results and caught same-runtime animation reentry are host refusals. Scalar
 * updates during interpretation are allowed. Effects must not schedule deferred
 * JS mutations; failures retain completed effects and cannot cancel that work.
 */
import {createSourceTObjScalarRuntime, type SourceTObjScalarHeader,
  type SourceTObjScalarRuntime} from './tobj-update.js';
export interface SourceTObjAnimationBinding {
  next08: symbol | null;
  aobj64: symbol | null;
  classUpdate48: symbol | null;
}
export interface SourceTObjAnimationEffects {
  interpretAObj(aobj: symbol | null, owner: symbol, callback: symbol | null): void;
}
export interface SourceTObjAnimationRuntime extends Omit<SourceTObjScalarRuntime, 'createTexture'> {
  createTexture(initial: SourceTObjScalarHeader, binding: SourceTObjAnimationBinding): symbol;
  getBinding(identity: symbol): SourceTObjAnimationBinding;
  animateAll(identity: symbol | null, effects: SourceTObjAnimationEffects): void;
}
const keys = ['next08', 'aobj64', 'classUpdate48'] as const;
function fail(reason: string): never {
  throw Error(`[tobj-animation] ${reason}; offline execution aborted, prior effects are not rolled back`);
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
export function createSourceTObjAnimationRuntime(maxNodes = 4096): SourceTObjAnimationRuntime {
  if (!Number.isSafeInteger(maxNodes) || maxNodes < 1) fail('maxNodes must be a positive safe integer');
  const scalar = createSourceTObjScalarRuntime();
  const bindings = new Map<symbol, SourceTObjAnimationBinding>();
  let busy = false, reentered = false;
  const getBinding = (id: symbol): SourceTObjAnimationBinding => {
    const binding = bindings.get(id);
    if (!binding) fail('unknown/non-owned TObj identity');
    return binding;
  };
  const read = (binding: SourceTObjAnimationBinding, key: keyof SourceTObjAnimationBinding): symbol | null => {
    const value = ownValue(binding, key, true); identity(value, key); return value;
  };
  return Object.freeze({
    getTexture: scalar.getTexture,
    updateScalar: scalar.updateScalar,
    createTexture(initial: SourceTObjScalarHeader, values: SourceTObjAnimationBinding): symbol {
      if (values === null || typeof values !== 'object') fail('initial binding data record required');
      const copied: Partial<SourceTObjAnimationBinding> = {};
      for (const key of keys) {
        const value = ownValue(values, key, false); identity(value, key);
        Object.defineProperty(copied, key, {value, writable: true, enumerable: true});
      }
      const id = scalar.createTexture(initial);
      bindings.set(id, Object.seal(copied) as SourceTObjAnimationBinding); return id;
    },
    getBinding,
    animateAll(id: symbol | null, effects: SourceTObjAnimationEffects): void {
      if (id === null) return;
      if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
      if (effects === null || typeof effects !== 'object') fail('effect data table required');
      const interpret = ownValue(effects, 'interpretAObj', false);
      if (typeof interpret !== 'function') fail('interpretAObj: own data-function required');
      busy = true; reentered = false;
      try {
        const seen = new Set<symbol>(); let current: symbol | null = id;
        while (current !== null) {
          identity(current, 'TObj list');
          if (seen.has(current)) fail('cycle/revisited TObj is unsupported');
          if (seen.size >= maxNodes) fail('TObj visit budget exhausted');
          const binding = getBinding(current); seen.add(current);
          const callback = read(binding, 'classUpdate48'), aobj = read(binding, 'aobj64');
          let result: unknown;
          try {result = Reflect.apply(interpret, effects, [aobj, current, callback]);}
          catch (error) {fail(`interpretAObj: effect threw (${String(error)})`);}
          if (result !== undefined) fail('interpretAObj: effect must complete synchronously and return undefined');
          if (reentered) fail('same-runtime reentry was caught inside an effect');
          current = read(binding, 'next08');
        }
      } finally {busy = false;}
    },
  });
}
