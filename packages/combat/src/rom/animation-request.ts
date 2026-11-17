/** Bounded offline HSD request-by-flags dispatch, not descriptor setup or playback.
 * Source: JObj 8024d838 (chunk_0071.c:3800–3818), DObj 8023d8e8
 * (chunk_0069.c:6291–6305), PObj 8024a5ec (chunk_0071.c:1476–1489),
 * MObj 802423a4 (chunk_0070.c:1235–1247), TObj 8023e050
 * (chunk_0069.c:6734–6747), RObj 802577d0 (chunk_0072.c:602–616).
 *
 * JObj requests its AObj on bit1, reloads flags14 for the 0x4020 display gate,
 * requests DObjs, then RObjs. DObj requests PObjs then MObj, never its own AObj.
 * PObj/MObj/TObj/RObj request bits are 8/4/0x10/0x80. Lists always traverse,
 * even for mask0; RObj reads its AObj and tests null before testing its mask.
 * MObj always visits its TObj list. Every next link is read after nested work.
 * Tree requests follow JObj 8024d8c0 (chunk_0071.c:3822–3938): preorder,
 * post-request 0x1000 child pruning, and no root sibling. The source unroll
 * ends in recursion, not a depth limit. Its export loses head/frame/recursive
 * arguments: this is structured-decompilation evidence, not instruction/ABI
 * parity. No dependency checks, interpretation, counters or end callbacks.
 *
 * Source/runtime/effect tables must be non-proxy own-data objects. Getter and
 * request methods are captured at construction and retain their original this.
 * Existing runtime getters enforce ownership; only minimal request-only RObj
 * records are owned here. No RObj animation receiver is implied. Fields are
 * checked when consumed, not by scalar/header/whole-list preflight. Adapters
 * must return the corresponding stable owned record synchronously. Synthetic
 * adapter mutations test host boundary order, not source callbacks: AObj request
 * has no user callback. The mandatory requestAObj adapter must perform actual
 * synchronous requestSourceAObj work or refuse, and return undefined. It must
 * not schedule deferred mutations. A null AObj is forwarded (except RObj's
 * source null guard); the adapter must honor the source null no-op.
 *
 * Frame is forwarded unchanged: the source takes a double, stores float32 in
 * AObj and forwards the ORIGINAL double to FObj. Numeric admission belongs to
 * the actual AObj adapter, after its null guard, not this dispatch layer.
 * uint32 request flags, writable consumed fields, per-list visit budgets/cycle
 * checks and same-runtime non-null request reentry refusal are host bounds.
 * Caught reentry poisons the pass immediately after each external getter or
 * effect. Public null targets bypass flags/reentry/record validation. Separate
 * list invocations have separate budgets, so sharing a chain is legitimate.
 * Trees have a separate per-pass global visited set and maxTreeNodes budget.
 * Failures preserve completed effects and cannot cancel deferred JS work.
 * No full setup, original-game replay or NI=1 arithmetic parity is claimed.
 */
import type {SourceJObjAnimationRuntime} from './jobj-animation.js';
import type {SourceDObjAnimationRuntime} from './dobj-animation.js';
import type {SourcePObjAnimationRuntime} from './pobj-animation.js';
import type {SourceMObjAnimationRuntime} from './mobj-animation.js';
import type {SourceTObjAnimationRuntime} from './tobj-animation.js';

export interface SourceAnimationRequestSources {
  joints: Pick<SourceJObjAnimationRuntime, 'getJoint' | 'getBinding'>;
  dobjs: Pick<SourceDObjAnimationRuntime, 'getDObj'>;
  pobjs: Pick<SourcePObjAnimationRuntime, 'getPObj'>;
  mobjs: Pick<SourceMObjAnimationRuntime, 'getMObj'>;
  tobjs: Pick<SourceTObjAnimationRuntime, 'getBinding'>;
}
export interface SourceAnimationRequestEffects {
  requestAObj(aobj: symbol | null, frame: number): void;
}
export interface SourceRObjRequestBinding {
  next00: symbol | null;
  aobj18: symbol | null;
}
export interface SourceAnimationRequestRuntime {
  createRObj(initial: SourceRObjRequestBinding): symbol;
  getRObj(identity: symbol): SourceRObjRequestBinding;
  requestJointTree(identity: symbol | null, frame: number, flags: number): void;
  requestJoint(identity: symbol | null, frame: number, flags: number): void;
  requestDObjs(identity: symbol | null, frame: number, flags: number): void;
  requestPObjs(identity: symbol | null, frame: number, flags: number): void;
  requestMObj(identity: symbol | null, frame: number, flags: number): void;
  requestTObjs(identity: symbol | null, frame: number, flags: number): void;
  requestRObjs(identity: symbol | null, frame: number, flags: number): void;
}
function fail(reason: string): never {
  throw Error(`[animation-request] ${reason}; offline execution aborted, prior effects are not rolled back`);
}
function own(record: unknown, key: string, writable = true): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function identity(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: expected opaque symbol or null`);
}
function uint32(value: unknown, where: string): asserts value is number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 0xffffffff) fail(`${where}: expected uint32`);
}
function readLink(record: unknown, key: string): symbol | null {
  const value = own(record, key); identity(value, key); return value;
}
function method(table: unknown, key: string): (...args: never[]) => unknown {
  const value = own(table, key, false);
  if (typeof value !== 'function') fail(`${key}: own data-function required`);
  return value as (...args: never[]) => unknown;
}
export function createSourceAnimationRequestRuntime(sources: SourceAnimationRequestSources,
  effects: SourceAnimationRequestEffects, maxNodes = 4096, maxTreeNodes = 4096): SourceAnimationRequestRuntime {
  if (!Number.isSafeInteger(maxNodes) || maxNodes < 1) fail('maxNodes must be a positive safe integer');
  if (!Number.isSafeInteger(maxTreeNodes) || maxTreeNodes < 1) fail('maxTreeNodes must be a positive safe integer');
  const joints = own(sources, 'joints', false), dobjs = own(sources, 'dobjs', false);
  const pobjs = own(sources, 'pobjs', false), mobjs = own(sources, 'mobjs', false), tobjs = own(sources, 'tobjs', false);
  const getJoint = method(joints, 'getJoint'), getJointBinding = method(joints, 'getBinding');
  const getDObj = method(dobjs, 'getDObj'), getPObj = method(pobjs, 'getPObj');
  const getMObj = method(mobjs, 'getMObj'), getTObj = method(tobjs, 'getBinding');
  const requestAObj = method(effects, 'requestAObj');
  const robjs = new Map<symbol, SourceRObjRequestBinding>();
  let busy = false, reentered = false;
  const checkReentry = (): void => {if (reentered) fail('same-runtime reentry was caught inside an adapter');};
  const resolve = (table: unknown, get: (...args: never[]) => unknown, id: symbol): unknown => {
    const record = Reflect.apply(get, table, [id]);
    checkReentry(); // Refuse before reading any field or invoking another adapter.
    return record;
  };
  const getRObj = (id: symbol): SourceRObjRequestBinding => {
    const value = robjs.get(id); if (!value) fail('unknown/non-owned RObj identity'); return value;
  };
  const request = (aobj: symbol | null, frame: number): void => {
    let result: unknown;
    try {result = Reflect.apply(requestAObj, effects, [aobj, frame]);}
    catch (error) {fail(`requestAObj: effect threw (${String(error)})`);}
    checkReentry();
    if (result !== undefined) fail('requestAObj: effect must complete synchronously and return undefined');
  };
  const list = (id: symbol | null, name: string, next: string, get: (id: symbol) => unknown,
    visit: (record: unknown) => void): void => {
    const seen = new Set<symbol>(); let current = id;
    while (current !== null) {
      identity(current, `${name} list`);
      if (seen.has(current)) fail(`cycle/revisited ${name} is unsupported`);
      if (seen.size >= maxNodes) fail(`${name} visit budget exhausted`);
      const record = get(current); seen.add(current);
      visit(record);
      current = readLink(record, next);
    }
  };
  const requestPObjs = (id: symbol | null, frame: number, flags: number): void => {
    list(id, 'PObj', 'next04', current => resolve(pobjs, getPObj, current), record => {
      if ((flags & 8) !== 0) request(readLink(record, 'aobj18'), frame);
    });
  };
  const requestTObjs = (id: symbol | null, frame: number, flags: number): void => {
    list(id, 'TObj', 'next08', current => resolve(tobjs, getTObj, current), record => {
      if ((flags & 0x10) !== 0) request(readLink(record, 'aobj64'), frame);
    });
  };
  const requestMObj = (id: symbol | null, frame: number, flags: number): void => {
    if (id === null) return;
    identity(id, 'MObj');
    const record = resolve(mobjs, getMObj, id);
    if ((flags & 4) !== 0) request(readLink(record, 'aobj14'), frame);
    requestTObjs(readLink(record, 'tobj08'), frame, flags);
  };
  const requestDObjs = (id: symbol | null, frame: number, flags: number): void => {
    list(id, 'DObj', 'next04', current => resolve(dobjs, getDObj, current), record => {
      requestPObjs(readLink(record, 'pobj0c'), frame, flags);
      requestMObj(readLink(record, 'mobj08'), frame, flags);
    });
  };
  const requestRObjs = (id: symbol | null, frame: number, flags: number): void => {
    list(id, 'RObj', 'next00', getRObj, record => {
      const aobj = readLink(record, 'aobj18');
      if (aobj !== null && (flags & 0x80) !== 0) request(aobj, frame);
    });
  };
  const requestJoint = (id: symbol | null, frame: number, flags: number): void => {
    if (id === null) return;
    identity(id, 'JObj');
    if ((flags & 1) !== 0) request(readLink(resolve(joints, getJointBinding, id), 'aobj7c'), frame);
    const jointFlags = own(resolve(joints, getJoint, id), 'flags14'); uint32(jointFlags, 'flags14');
    if ((jointFlags & 0x4020) === 0) {
      requestDObjs(readLink(resolve(joints, getJointBinding, id), 'dobj18'), frame, flags);
    }
    requestRObjs(readLink(resolve(joints, getJointBinding, id), 'robj80'), frame, flags);
  };
  const requestJointTree = (id: symbol | null, frame: number, flags: number): void => {
    if (id === null) return;
    const seen = new Set<symbol>();
    const visit = (current: symbol): unknown => {
      identity(current, 'tree JObj');
      if (seen.has(current)) fail('tree cycle/revisited JObj is unsupported');
      if (seen.size >= maxTreeNodes) fail('tree visit budget exhausted');
      seen.add(current);
      requestJoint(current, frame, flags);
      return resolve(joints, getJoint, current);
    };
    const child = (record: unknown): symbol | null => {
      const jointFlags = own(record, 'flags14'); uint32(jointFlags, 'flags14');
      return (jointFlags & 0x1000) === 0 ? readLink(record, 'child10') : null;
    };
    const root = visit(id);
    let current = child(root);
    // Retain entered records, never future links. Pop only after the entire
    // subtree returns, then consume that child's live sibling. Exclude root.
    const ancestors: unknown[] = [];
    for (;;) {
      if (current === null) {
        if (ancestors.length === 0) return;
        current = readLink(ancestors.pop(), 'sibling08');
      } else {
        const record = visit(current);
        ancestors.push(record);
        current = child(record);
      }
    }
  };
  const entry = (run: (id: symbol | null, frame: number, flags: number) => void) =>
    (id: symbol | null, frame: number, flags: number): void => {
      if (id === null) return;
      if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
      busy = true; reentered = false;
      try {uint32(flags, 'request flags'); run(id, frame, flags);}
      finally {busy = false;}
    };
  return Object.freeze({
    createRObj(initial: SourceRObjRequestBinding): symbol {
      const next00 = own(initial, 'next00', false), aobj18 = own(initial, 'aobj18', false);
      identity(next00, 'next00'); identity(aobj18, 'aobj18');
      const id = Symbol('owned RObj request binding'); robjs.set(id, Object.seal({next00, aobj18})); return id;
    },
    getRObj,
    requestJointTree: entry(requestJointTree), requestJoint: entry(requestJoint), requestDObjs: entry(requestDObjs), requestPObjs: entry(requestPObjs),
    requestMObj: entry(requestMObj), requestTObjs: entry(requestTObjs), requestRObjs: entry(requestRObjs),
  });
}
