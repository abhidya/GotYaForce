/** Bounded offline HSD_MObjAnim (802428a4), not a live material adapter.
 * Source: chunk_0070.c:1396–1424. The material selects its class callback and
 * AObj, interprets that AObj with the same owner, then animates its current
 * TObj list. A null material returns before any effect-table validation.
 *
 * classUpdate4c is the resolved selector at class-info+4c, NOT MObj+4c or a
 * reconstructed class object. All fields are explicit symbolic identities in
 * factory-owned sealed records, never pointers or aliased RAM. TObj animation
 * and custom receivers remain required real synchronous effects or explicit
 * refusal. Null AObj, callback and TObj targets are passed to those effects.
 * Use the enclosing JObj tree's actual endCallbacks.counts in AObj effects.
 * This helper neither resets counters nor invokes completion callbacks.
 *
 * Inputs/effect tables must be non-proxy own-data records. Effect methods are
 * captured once per invocation and retain the original table as this. Identity
 * and writable-data-field checks happen only when each field is read. Consumed
 * fields are not reread after effects. Host ownership and same-runtime reentry
 * refusal are not retail control flow. Reentry caught by an effect still aborts
 * the outer invocation. Effects must return undefined synchronously and must not
 * schedule deferred mutations; rejection cannot undo already scheduled JS work.
 * Failure preserves completed effects; there is no rollback or original parity.
 */
export interface SourceMObjAnimationBinding {
  tobj08: symbol | null;
  aobj14: symbol | null;
  classUpdate4c: symbol | null;
}
export interface SourceMObjAnimationEffects {
  interpretAObj(aobj: symbol | null, owner: symbol, callback: symbol | null): void;
  animateTObjs(list: symbol | null): void;
}
export interface SourceMObjAnimationRuntime {
  createMObj(initial: SourceMObjAnimationBinding): symbol;
  getMObj(identity: symbol): SourceMObjAnimationBinding;
  animate(identity: symbol | null, effects: SourceMObjAnimationEffects): void;
}
const bindingKeys = ['tobj08', 'aobj14', 'classUpdate4c'] as const;
const effectKeys = ['interpretAObj', 'animateTObjs'] as const;
function fail(reason: string): never {
  throw Error(`[mobj-animation] ${reason}; offline execution aborted, prior effects are not rolled back`);
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
function snapshotEffects(effects: SourceMObjAnimationEffects): SourceMObjAnimationEffects {
  if (effects === null || typeof effects !== 'object') fail('effect data table required');
  const copied: Partial<SourceMObjAnimationEffects> = {};
  for (const key of effectKeys) {
    const method = ownValue(effects, key, false);
    if (typeof method !== 'function') fail(`${key}: own data-function required`);
    Object.defineProperty(copied, key, {value: method, enumerable: true});
  }
  return Object.freeze(copied) as SourceMObjAnimationEffects;
}
export function createSourceMObjAnimationRuntime(): SourceMObjAnimationRuntime {
  const objects = new Map<symbol, SourceMObjAnimationBinding>();
  let busy = false, reentered = false;
  const getMObj = (id: symbol): SourceMObjAnimationBinding => {
    const object = objects.get(id);
    if (!object) fail('unknown/non-owned MObj identity');
    return object;
  };
  const read = (object: SourceMObjAnimationBinding, key: keyof SourceMObjAnimationBinding): symbol | null => {
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
    createMObj(initial: SourceMObjAnimationBinding): symbol {
      if (initial === null || typeof initial !== 'object') fail('initial binding data record required');
      const copied: Partial<SourceMObjAnimationBinding> = {};
      for (const key of bindingKeys) {
        const value = ownValue(initial, key, false);
        identity(value, key);
        Object.defineProperty(copied, key, {value, writable: true, enumerable: true});
      }
      const id = Symbol('owned MObj animation binding');
      objects.set(id, Object.seal(copied) as SourceMObjAnimationBinding);
      return id;
    },
    getMObj,
    animate(id: symbol | null, effects: SourceMObjAnimationEffects): void {
      if (id === null) return;
      if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
      const dispatch = snapshotEffects(effects);
      busy = true; reentered = false;
      try {
        identity(id, 'MObj');
        const object = getMObj(id);
        const callback = read(object, 'classUpdate4c');
        const aobj = read(object, 'aobj14');
        effect('interpretAObj', () => Reflect.apply(dispatch.interpretAObj, effects, [aobj, id, callback]));
        const tobj = read(object, 'tobj08');
        effect('animateTObjs', () => Reflect.apply(dispatch.animateTObjs, effects, [tobj]));
      } finally { busy = false; }
    },
  });
}
