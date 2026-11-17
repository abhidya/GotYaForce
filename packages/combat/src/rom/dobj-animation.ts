/** Bounded offline HSD_DObjAnimAll (8023d968), not a live display adapter.
 * Source: chunk_0069.c:6308–6341. Each display object selects its class callback
 * and AObj, interprets that AObj with the same owner, animates the current PObj
 * list, animates the current MObj, then follows its current next link.
 *
 * classUpdate44 is the resolved selector at class-info+44, NOT DObj+44 or a
 * reconstructed class object. All fields are explicit symbolic identities in
 * factory-owned sealed records, never pointers or aliased RAM. No flags are
 * invented for this unconditional dispatch loop. PObj/MObj animation and custom
 * receivers remain required real synchronous effects or explicit refusal.
 * Null targets are passed to those effects; a null DObj list bypasses all validation.
 * Use the enclosing JObj tree's actual endCallbacks.counts in any AObj effects.
 * This helper neither resets counters nor invokes completion callbacks.
 *
 * Inputs/effect tables must be non-proxy own-data records. Effect methods are
 * captured once per list and retain the original table as this. Identity and
 * writable-data-field checks happen only when each field is read. Consumed
 * fields are not reread after effects. Unvisited records are not preflighted.
 * Host ownership, finite visit budgets, cycle/revisit and same-runtime reentry
 * refusal are not retail control flow. Reentry caught by an effect still aborts
 * the outer traversal. Effects must return undefined synchronously and must not
 * schedule deferred mutations; rejection cannot undo already scheduled JS work.
 * Failure preserves completed effects; there is no rollback or original parity.
 */
export interface SourceDObjAnimationBinding {
  next04: symbol | null;
  mobj08: symbol | null;
  pobj0c: symbol | null;
  aobj10: symbol | null;
  classUpdate44: symbol | null;
}
export interface SourceDObjAnimationEffects {
  interpretAObj(aobj: symbol | null, owner: symbol, callback: symbol | null): void;
  animatePObjs(list: symbol | null): void;
  animateMObj(object: symbol | null): void;
}
export interface SourceDObjAnimationRuntime {
  createDObj(initial: SourceDObjAnimationBinding): symbol;
  getDObj(identity: symbol): SourceDObjAnimationBinding;
  animateAll(identity: symbol | null, effects: SourceDObjAnimationEffects): void;
}
const bindingKeys = ['next04', 'mobj08', 'pobj0c', 'aobj10', 'classUpdate44'] as const;
const effectKeys = ['interpretAObj', 'animatePObjs', 'animateMObj'] as const;
function fail(reason: string): never {
  throw Error(`[dobj-animation] ${reason}; offline execution aborted, prior effects are not rolled back`);
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
function snapshotEffects(effects: SourceDObjAnimationEffects): SourceDObjAnimationEffects {
  if (effects === null || typeof effects !== 'object') fail('effect data table required');
  const copied: Partial<SourceDObjAnimationEffects> = {};
  for (const key of effectKeys) {
    const method = ownValue(effects, key, false);
    if (typeof method !== 'function') fail(`${key}: own data-function required`);
    Object.defineProperty(copied, key, {value: method, enumerable: true});
  }
  return Object.freeze(copied) as SourceDObjAnimationEffects;
}
export function createSourceDObjAnimationRuntime(maxNodes = 4096): SourceDObjAnimationRuntime {
  if (!Number.isSafeInteger(maxNodes) || maxNodes < 1) fail('maxNodes must be a positive safe integer');
  const objects = new Map<symbol, SourceDObjAnimationBinding>();
  let busy = false, reentered = false;
  const getDObj = (id: symbol): SourceDObjAnimationBinding => {
    const object = objects.get(id);
    if (!object) fail('unknown/non-owned DObj identity');
    return object;
  };
  const read = (object: SourceDObjAnimationBinding, key: keyof SourceDObjAnimationBinding): symbol | null => {
    const value = ownValue(object, key, true);
    identity(value, key);
    return value;
  };
  const effect = (name: string, invoke: () => unknown): void => {
    let result: unknown;
    try { result = invoke(); }
    catch (error) { fail(`${name}: effect threw (${String(error)})`); }
    if (result !== undefined) fail(`${name}: effect must complete synchronously and return undefined`);
    if (reentered) fail('same-runtime reentry was caught inside an effect');
  };
  return Object.freeze({
    createDObj(initial: SourceDObjAnimationBinding): symbol {
      if (initial === null || typeof initial !== 'object') fail('initial binding data record required');
      const copied: Partial<SourceDObjAnimationBinding> = {};
      for (const key of bindingKeys) {
        const value = ownValue(initial, key, false);
        identity(value, key);
        Object.defineProperty(copied, key, {value, writable: true, enumerable: true});
      }
      const id = Symbol('owned DObj animation binding');
      objects.set(id, Object.seal(copied) as SourceDObjAnimationBinding);
      return id;
    },
    getDObj,
    animateAll(id: symbol | null, effects: SourceDObjAnimationEffects): void {
      if (id === null) return;
      if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
      const dispatch = snapshotEffects(effects);
      busy = true; reentered = false;
      try {
        const seen = new Set<symbol>();
        let current: symbol | null = id;
        while (current !== null) {
          identity(current, 'DObj list');
          if (seen.has(current)) fail('cycle/revisited DObj is unsupported');
          if (seen.size >= maxNodes) fail('DObj visit budget exhausted');
          const object = getDObj(current);
          seen.add(current);
          const callback = read(object, 'classUpdate44');
          const aobj = read(object, 'aobj10');
          effect('interpretAObj', () => Reflect.apply(dispatch.interpretAObj, effects, [aobj, current, callback]));
          const pobj = read(object, 'pobj0c');
          effect('animatePObjs', () => Reflect.apply(dispatch.animatePObjs, effects, [pobj]));
          const mobj = read(object, 'mobj08');
          effect('animateMObj', () => Reflect.apply(dispatch.animateMObj, effects, [mobj]));
          current = read(object, 'next04');
        }
      } finally { busy = false; }
    },
  });
}
