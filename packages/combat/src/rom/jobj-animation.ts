/** Offline HSD_JObjCheckDepend (8024d030) and one-joint HSD_JObjAnim (8024ea64).
 * Source: chunk_0071.c:3321–3380,4865–5120. Includes bounded JObjAnimAll traversal
 * and its counter/end-callback wrapper; no matrices or live animation adapter.
 *
 * Bindings are separately owned sealed records. classUpdate50 represents the
 * resolved selector at class-info+50, NOT JObj+50 or a reconstructed class object.
 * Parent/AObj/RObj/DObj/callback symbols are explicit identities, never pointers.
 * Parent resolution uses the same scalar runtime, and is lazy. No coherence
 * between parent and child links is invented. CheckDepend only ORs the owner's
 * dirty bit; it does not propagate that bit down a subtree.
 *
 * All effects are mandatory own data-function properties, copied once from a
 * non-proxy table before execution. Supply the real synchronous implementation
 * or throw for unsupported work. Null lists are forwarded to the effects, not
 * silently skipped. Effects may change owned scalar records and bindings; each
 * later argument and the final DObj gate are read at the original boundary.
 * No RObj, DObj or custom-class receiver implementation is supplied.
 * AObj/FObj arithmetic retains its separate domain. Tree effects must use the
 * returned endCallbacks.counts for actual AObj interpretation, including any
 * implemented RObj/DObj animation; counters are not inferred from visits.
 *
 * Header ownership/writability and all transform scalars are host preconditions,
 * checked at entry and after each effect. Binding identity values are validated
 * only when read, including unvisited-parent/DObj exceptions. Same-runtime
 * animation/dependency reentry and async/deferred effects are unsupported.
 * Failures retain earlier dependency writes and completed effect prefixes.
 */
import {createSourceJObjScalarRuntime, type SourceJObjScalarHeader,
  type SourceJObjScalarRuntime} from './jobj-update.js';
import {createSourceAObjEndCallbackRuntime, type SourceAObjEndCallbackRuntime}
  from './aobj-end-callbacks.js';

export interface SourceJObjAnimationBinding {
  parent0c: symbol | null;
  aobj7c: symbol | null;
  robj80: symbol | null;
  dobj18: symbol | null;
  classUpdate50: symbol | null;
}
export interface SourceJObjAnimationEffects {
  interpretAObj(aobj: symbol | null, owner: symbol, callback: symbol | null): void;
  animateRObjs(list: symbol | null): void;
  animateDObjs(list: symbol | null): void;
}
export interface SourceJObjAnimationRuntime extends Omit<SourceJObjScalarRuntime, 'createJoint'> {
  createJoint(initial: SourceJObjScalarHeader, binding: SourceJObjAnimationBinding): symbol;
  getBinding(identity: symbol): SourceJObjAnimationBinding;
  checkDepend(identity: symbol | null): void;
  animateJoint(identity: symbol | null, effects: SourceJObjAnimationEffects): void;
  readonly endCallbacks: SourceAObjEndCallbackRuntime;
  animateTree(identity: symbol | null, effects: SourceJObjAnimationEffects): void;
}
const bindingKeys = ['parent0c', 'aobj7c', 'robj80', 'dobj18', 'classUpdate50'] as const;
const effectKeys = ['interpretAObj', 'animateRObjs', 'animateDObjs'] as const;
function fail(reason: string): never {
  throw Error(`[jobj-animation] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function identity(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: expected opaque symbol or null`);
}
function logicallyDirty(flags: number): boolean {
  return (flags & 0x00800000) === 0 && (flags & 0x40) !== 0;
}
function snapshotEffects(effects: SourceJObjAnimationEffects): SourceJObjAnimationEffects {
  if (effects === null || typeof effects !== 'object') fail('all three own data-function effects are required');
  const copied = {} as SourceJObjAnimationEffects;
  for (const key of effectKeys) {
    const property = Object.getOwnPropertyDescriptor(effects, key);
    if (!property || !('value' in property) || typeof property.value !== 'function') {
      fail(`all three own data-function effects are required: ${key}`);
    }
    Object.defineProperty(copied, key, {value: property.value, enumerable: true});
  }
  return copied;
}
export function createSourceJObjAnimationRuntime(maxDirtyNodes = 4096,
  maxAnimationNodes = 4096, maxEndCallbackNodes = 4096, maxFlagNodes = 4096): SourceJObjAnimationRuntime {
  if (!Number.isSafeInteger(maxAnimationNodes) || maxAnimationNodes < 1) fail('maxAnimationNodes must be a positive safe integer');
  const scalar = createSourceJObjScalarRuntime(maxDirtyNodes, maxFlagNodes);
  const endCallbacks = createSourceAObjEndCallbackRuntime(maxEndCallbackNodes);
  const bindings = new Map<symbol, SourceJObjAnimationBinding>();
  let busy = false;
  const getBinding = (id: symbol): SourceJObjAnimationBinding => {
    const binding = bindings.get(id);
    if (!binding) fail('unknown/non-owned animation binding');
    return binding;
  };
  const validate = (joint: SourceJObjScalarHeader, binding: SourceJObjAnimationBinding): void => {
    scalar.validateJoint(joint);
    for (const key of bindingKeys) {
      if (!Object.getOwnPropertyDescriptor(binding, key)?.writable) fail(`${key}: non-writable binding field`);
    }
  };
  const parentFlags = (id: symbol): number => {
    const parent = scalar.getJoint(id);
    scalar.validateJoint(parent);
    return parent.flags14;
  };
  const depend = (joint: SourceJObjScalarHeader, binding: SourceJObjAnimationBinding): void => {
    const flags = joint.flags14;
    if (logicallyDirty(flags)) return;
    if ((flags & 0x00800000) === 0) {
      identity(binding.parent0c, 'parent0c');
      if (binding.parent0c !== null && (parentFlags(binding.parent0c) & 0x40) !== 0) {
        joint.flags14 = (flags | 0x40) >>> 0;
      } else if ((flags & 0x00600000) !== 0) {
        joint.flags14 = (flags | 0x40) >>> 0;
      } else {
        identity(binding.robj80, 'robj80');
        if (binding.robj80 !== null) joint.flags14 = (flags | 0x40) >>> 0;
      }
    } else if ((flags & 0x01000000) === 0) {
      identity(binding.parent0c, 'parent0c');
      if (binding.parent0c !== null && logicallyDirty(parentFlags(binding.parent0c))) {
        joint.flags14 = (flags | 0x40) >>> 0;
      }
    }
  };
  const resolve = (id: symbol) => {
    const joint = scalar.getJoint(id), binding = getBinding(id);
    validate(joint, binding);
    return {joint, binding};
  };
  const enter = (id: symbol) => {
    if (busy) fail('same-runtime reentry is unsupported');
    return resolve(id);
  };
  const effect = (name: string, invoke: () => unknown,
    joint: SourceJObjScalarHeader, binding: SourceJObjAnimationBinding): void => {
    let result: unknown;
    try { result = invoke(); } catch (error) { fail(`${name}: effect threw (${String(error)})`); }
    if (result !== undefined) fail(`${name}: effect must complete synchronously and return undefined`);
    validate(joint, binding);
  };
  const animate = (id: symbol, joint: SourceJObjScalarHeader, binding: SourceJObjAnimationBinding,
    dispatch: SourceJObjAnimationEffects, effects: SourceJObjAnimationEffects): void => {
    depend(joint, binding);
    // The callback selector is loaded from class-info before AObj dispatch.
    const callback = binding.classUpdate50;
    identity(callback, 'classUpdate50');
    const aobj = binding.aobj7c;
    identity(aobj, 'aobj7c');
    effect('interpretAObj', () => Reflect.apply(dispatch.interpretAObj, effects, [aobj, id, callback]), joint, binding);
    identity(binding.robj80, 'robj80');
    effect('animateRObjs', () => Reflect.apply(dispatch.animateRObjs, effects, [binding.robj80]), joint, binding);
    if ((joint.flags14 & 0x4020) === 0) {
      identity(binding.dobj18, 'dobj18');
      effect('animateDObjs', () => Reflect.apply(dispatch.animateDObjs, effects, [binding.dobj18]), joint, binding);
    }
  };
  return {
    getJoint: scalar.getJoint,
    validateJoint: scalar.validateJoint,
    updateScalar: scalar.updateScalar,
    setFlags: scalar.setFlags,
    clearFlags: scalar.clearFlags,
    setFlagsAll: scalar.setFlagsAll,
    clearFlagsAll: scalar.clearFlagsAll,
    createJoint(initial, values) {
      if (values === null || typeof values !== 'object') fail('initial binding data record required');
      const copied: Partial<SourceJObjAnimationBinding> = {};
      for (const key of bindingKeys) {
        const property = Object.getOwnPropertyDescriptor(values, key);
        if (!property || !('value' in property)) fail(`${key}: initial own data property required`);
        identity(property.value, key);
        Object.defineProperty(copied, key, {value: property.value, writable: true, enumerable: true});
      }
      const binding = Object.seal(copied) as SourceJObjAnimationBinding;
      const id = scalar.createJoint(initial);
      bindings.set(id, binding);
      return id;
    },
    getBinding,
    endCallbacks,
    checkDepend(id) {
      if (id === null) return;
      const {joint, binding} = enter(id);
      busy = true;
      try { depend(joint, binding); } finally { busy = false; }
    },
    animateJoint(id, effects) {
      if (id === null) return;
      const {joint, binding} = enter(id);
      const dispatch = snapshotEffects(effects);
      busy = true;
      try { animate(id, joint, binding, dispatch, effects); } finally { busy = false; }
    },
    animateTree(id, effects) {
      if (id === null) return;
      if (busy) fail('same-runtime reentry is unsupported');
      // Host effect-table validation precedes source counter writes. No graph
      // preflight: non-null-root resolution and node failures occur after init.
      const dispatch = snapshotEffects(effects);
      busy = true;
      try {
        endCallbacks.init();
        const seen = new Set<symbol>();
        const visit = (current: symbol): SourceJObjScalarHeader => {
          identity(current, 'tree joint');
          if (seen.has(current)) fail('tree cycle/revisited joint is unsupported');
          if (seen.size >= maxAnimationNodes) fail('animation-node budget exhausted');
          const {joint, binding} = resolve(current);
          seen.add(current);
          animate(current, joint, binding, dispatch, effects);
          return joint;
        };
        const root = visit(id);
        if ((root.flags14 & 0x1000) === 0) {
          // Entered ancestor records, not cached sibling links. The root is
          // excluded: JObjAnimAll never visits its own sibling. Child/sibling
          // links are read only when followed, after the complete prior call.
          const ancestors: SourceJObjScalarHeader[] = [];
          let current = root.child10;
          for (;;) {
            if (current === null) {
              if (ancestors.length === 0) break;
              current = ancestors.pop()!.sibling08;
              continue;
            }
            const joint = visit(current);
            if ((joint.flags14 & 0x1000) === 0) {
              ancestors.push(joint);
              current = joint.child10;
            } else current = joint.sibling08;
          }
        }
        endCallbacks.invoke();
      } finally { busy = false; }
    },
  };
}
