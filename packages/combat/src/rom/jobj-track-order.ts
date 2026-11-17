/** Bounded first-track12 promotion inside HSD_JObjAddAnim, 8024dc04.
 * Source: chunk_0071.c:4005–4015 (surrounding setup: 3971–4054).
 * Identical reorder: JObjSortAnim 8024dbac, chunk_0071.c:3943–3964;
 * this joint-bound entry does not claim that standalone AObj ABI.
 * This is ONLY the post-load list reorder: no attach/remove, RObj/DObj setup,
 * request, callback, refcount or new track12 animation receiver is implied.
 *
 * Resolve aobj7c once, retain that AObj and scan its live pointer-to-pointer
 * chain, reading track13 before next00. Stop at the FIRST track12 match without
 * resolving its successor. Perform all three source stores even at the head:
 * predecessor-or-head = matched.next; matched.next = current head; head = match.
 * In particular the head match temporarily detaches itself before reloading
 * the head. Failures preserve completed stores, without rollback.
 *
 * Sources and method tables must be non-proxy own-data objects. Methods are
 * fixed at construction with original this. Getters must synchronously return
 * actual stable owned records (not copied graphs), enforcing their runtime's
 * ownership; getFObj resolves within the supplied AObj's FObj runtime. No
 * portable Proxy detection is claimed. Adapter mutations are host fault tests,
 * not source callbacks. Fields are checked only when consumed; unlike broader
 * helpers, read-only data fields are admitted for reads, and writability is
 * required only at the actual store. Prior store-target values are not checked.
 * Byte track admission, symbols, per-call cycles/visit budgets and poisoned
 * same-runtime non-null reentry are host bounds. Null joint bypasses reentry;
 * null AObj/head bypasses all later fields. No whole-list/tail preflight occurs.
 */
import type {SourceJObjAnimationRuntime} from './jobj-animation.js';
import type {SourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import type {SourceFObjHeader} from './fobj-list.js';
export interface SourceJObjTrackOrderSources {
  joints: Pick<SourceJObjAnimationRuntime, 'getBinding'>;
  feedback: Pick<SourceJointAnimationFeedbackRuntime, 'getAObj'>;
  fobjs: {getFObj(aobjId: symbol, nodeId: symbol): SourceFObjHeader};
}
export interface SourceJObjTrackOrderRuntime {promoteFirstTrack12(joint: symbol | null): void}
function fail(reason: string): never {
  throw Error(`[jobj-track-order] ${reason}; offline execution aborted, prior stores are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable target field is unsupported`);
  return p.value;
}
function identity(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: expected opaque symbol or null`);
}
function link(record: unknown, key: string): symbol | null {
  const value = own(record, key); identity(value, key); return value;
}
function method(table: unknown, key: string): (...args: never[]) => unknown {
  const value = own(table, key); if (typeof value !== 'function') fail(`${key}: own data-function required`);
  return value as (...args: never[]) => unknown;
}
function store(record: unknown, key: string, value: symbol | null): void {
  own(record, key, true); (record as Record<string, unknown>)[key] = value;
}
export function createSourceJObjTrackOrderRuntime(sources: SourceJObjTrackOrderSources,
  maxNodes = 4096): SourceJObjTrackOrderRuntime {
  if (!Number.isSafeInteger(maxNodes) || maxNodes < 1) fail('maxNodes must be a positive safe integer');
  const joints = own(sources, 'joints'), feedback = own(sources, 'feedback'), fobjs = own(sources, 'fobjs');
  const getBinding = method(joints, 'getBinding'), getAObj = method(feedback, 'getAObj'), getFObj = method(fobjs, 'getFObj');
  let busy = false, reentered = false;
  const resolve = (table: unknown, get: (...args: never[]) => unknown, args: symbol[]): unknown => {
    const record = Reflect.apply(get, table, args);
    if (reentered) fail('same-runtime reentry was caught inside an adapter');
    return record;
  };
  return Object.freeze({promoteFirstTrack12(joint: symbol | null): void {
    if (joint === null) return;
    if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
    busy = true; reentered = false;
    try {
      identity(joint, 'JObj');
      const aobjId = link(resolve(joints, getBinding, [joint]), 'aobj7c');
      if (aobjId === null) return;
      const aobj = resolve(feedback, getAObj, [aobjId]);
      let predecessor = aobj, key = 'fobjs', current = link(aobj, key);
      const seen = new Set<symbol>();
      while (current !== null) {
        if (seen.has(current)) fail('cycle/revisited FObj is unsupported');
        if (seen.size >= maxNodes) fail('FObj visit budget exhausted');
        seen.add(current);
        const node = resolve(fobjs, getFObj, [aobjId, current]);
        const track = own(node, 'track13');
        if (typeof track !== 'number' || !Number.isInteger(track) || track < 0 || track > 255) fail('track13: expected byte');
        if (track === 12) {
          store(predecessor, key, link(node, 'next00'));
          store(node, 'next00', link(aobj, 'fobjs'));
          store(aobj, 'fobjs', current);
          return;
        }
        predecessor = node; key = 'next00'; current = link(predecessor, key);
      }
    } finally {busy = false;}
  }});
}
