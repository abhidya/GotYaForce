import {AOBJ_LOOP, AOBJ_STOPPED, createSourceAObj, createSourceAObjCounters, freeSourceAObj,
  interpretSourceAObj, requestSourceAObj, setSourceAObjRate, setSourceAObjFlags,
  type SourceAObj} from './aobj-clock.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceFObjRuntime} from './fobj-list.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceAllocatedAObjDescriptorRuntime} from './allocated-aobj-descriptor.js';
import {createSourceAObjLifecycleRuntime, type SourceAObjLifecycleRuntime} from './aobj-lifecycle.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[aobj-lifecycle-test] ${why}`);}
function rejects(fn: () => unknown, text: string): void {
  let message = ''; try {fn();} catch (e) {message = String(e);}
  check(message.includes(text), `expected ${text}, got ${message || 'success'}`);
}
function fixture() {
  const owner = createSourceJointAnimationFeedbackRuntime(createSourceJObjAnimationRuntime());
  const real = createSourceFObjRuntime(() => {throw Error('unexpected interpreter');});
  const loader = createSourceFObjDescriptorRuntime(real), ids: symbol[] = [], events: string[] = [];
  const hooks: {allocate?: () => void; remove?: () => void; load?: () => void; result?: unknown; override?: boolean} = {};
  const feedback = {
    allocateAObj(): symbol {
      check(this === feedback, 'allocator receiver'); events.push('allocate');
      const id = owner.allocateAObj(); ids.push(id); hooks.allocate?.(); return id;
    },
    getAObj(id: symbol): SourceAObj {check(this === feedback, 'resolver receiver'); events.push('get'); return owner.getAObj(id);},
    freeAObj(id: symbol | null): void {check(this === feedback, 'free receiver'); events.push('free'); owner.freeAObj(id);},
  };
  const allocated = createSourceAllocatedAObjDescriptorRuntime({feedback: owner, fobjs: loader, removal: real});
  const fobjs = {removeAll(id: symbol | null): void {
    check(this === fobjs, 'removal receiver'); events.push('remove'); real.removeAll(id); hooks.remove?.();
  }};
  const descriptors = {continueAllocatedLoad(id: symbol | null, descriptor: symbol | null): symbol | null {
    check(this === descriptors, 'continuation receiver'); events.push('load');
    const result = allocated.continueAllocatedLoad(id, descriptor); hooks.load?.();
    return hooks.override ? hooks.result as symbol | null : result;
  }};
  const runtime = createSourceAObjLifecycleRuntime({feedback, fobjs, descriptors});
  const tail = loader.createDescriptor({next00: null, length04: 2, start08: -3, track0c: 9, format0d: 0, format0e: 0, data10: null});
  const head = loader.createDescriptor({next00: tail, length04: 4, start08: 2, track0c: 3, format0d: 0, format0e: 0, data10: null});
  const descriptor = allocated.createDescriptor({flags00: AOBJ_LOOP, end04: 9, fobj08: head, joint0c: null});
  const load = (): symbol => {const id = runtime.loadDescriptor(descriptor); check(typeof id === 'symbol', 'load identity'); return id!;};
  return {owner, real, loader, ids, events, hooks, feedback, fobjs, allocated, descriptors, runtime, descriptor, head, load};
}
export function runAObjLifecycleSelfTest(): void {
  {
    const f = fixture();
    f.runtime.removeAObj(null); check(f.runtime.loadDescriptor(null) === null && !f.events.length, 'null bypass all adapters');
    f.owner.freeAObj(null); freeSourceAObj(null);
    const id = f.runtime.allocateAObj(), second = f.runtime.allocateAObj(), a = f.owner.getAObj(id);
    check(id !== second && Object.isSealed(a) && Object.isFrozen(f.runtime), 'separate actual owned allocations');
    check(a.flags === AOBJ_STOPPED && a.rate === 1 && a.fobjs === null && a.joint18 === null &&
      [a.frame, a.rewind, a.end].every(v => Object.is(v, 0)), 'source successful allocation defaults');
    a.flags = 0x123; a.frame = 7; f.runtime.removeAObj(id);
    check(a.flags === 0x123 && a.frame === 7, 'logical free does not erase retained record');
    rejects(() => f.owner.getAObj(id), 'unknown/non-owned');
    rejects(() => f.runtime.removeAObj(id), 'unknown/non-owned');
    rejects(() => setSourceAObjRate(a, 2), 'factory-created');
    rejects(() => setSourceAObjFlags(a, 0), 'factory-created');
    rejects(() => requestSourceAObj(a, 0, f.real.effects), 'factory-created');
    rejects(() => interpretSourceAObj(a, null, f.real.effects, createSourceAObjCounters()), 'factory-created');
    check(f.owner.getAObj(second).rate === 1, 'other allocation remains valid');
  }
  {
    const f = fixture(), id = f.load(), a = f.owner.getAObj(id), head = a.fobjs!, tail = f.real.getNode(head).next00!;
    check(a.flags === (AOBJ_STOPPED | AOBJ_LOOP) && a.end === 9 && a.rate === 1 && a.rewind === 0, 'real descriptor writes source allocation');
    check(f.real.getNode(head).offset18 === 2 && f.real.getNode(tail).offset18 === -3, 'real FObj descriptor allocation');
    const other = f.load(); check(other !== id && f.owner.getAObj(other).fobjs !== head, 'repeat load allocates separate actual graph');
    f.events.length = 0; f.runtime.removeAObj(id);
    check(f.events.join() === 'get,remove,free' && a.fobjs === null && a.joint18 === null, 'source removal order');
    rejects(() => f.real.getNode(head), 'unknown/non-owned'); rejects(() => f.real.getNode(tail), 'unknown/non-owned');
  }
  {
    const f = fixture(); rejects(() => f.runtime.loadDescriptor(Symbol('foreign descriptor')), 'unknown/non-owned descriptor');
    check(f.ids.length === 1 && f.owner.getAObj(f.ids[0]!).flags === AOBJ_STOPPED, 'unknown descriptor retains earlier actual allocation');
    rejects(() => f.runtime.loadDescriptor(Promise.resolve(null) as unknown as symbol), 'descriptor identity');
    check(f.ids.length === 2, 'invalid descriptor type refuses only after allocation');
    f.allocated.getDescriptor(f.descriptor).joint0c = Symbol('unsupported');
    rejects(f.load, 'joint ID');
    check(f.owner.getAObj(f.ids[2]!).end === 9 && f.owner.getAObj(f.ids[2]!).fobjs !== null, 'failed continuation keeps allocation and source prefix');
  }
  {
    const f = fixture(), id = f.load(), a = f.owner.getAObj(id), head = a.fobjs!;
    a.joint18 = Symbol('joint ref'); Object.defineProperty(a, 'joint18', {writable: false});
    rejects(() => f.runtime.removeAObj(id), 'unref');
    check(a.fobjs === null && f.owner.getAObj(id) === a, 'joint refusal after release and fobjs null store, before free');
    rejects(() => f.real.getNode(head), 'unknown/non-owned');
  }
  for (const field of ['fobjs', 'joint18'] as const) {
    const f = fixture(), id = f.load(), a = f.owner.getAObj(id), head = a.fobjs!;
    Object.defineProperty(a, field, {writable: false});
    rejects(() => f.runtime.removeAObj(id), `non-writable field`);
    rejects(() => f.real.getNode(head), 'unknown/non-owned');
    check(f.owner.getAObj(id) === a && a.fobjs === (field === 'fobjs' ? head : null), `${field} failure preserves reached source prefix`);
  }
  {
    const f = fixture(), id = f.load(), a = f.owner.getAObj(id), head = a.fobjs!, tail = f.real.getNode(head).next00!;
    f.real.getNode(tail).next00 = Symbol('bad tail');
    rejects(() => f.runtime.removeAObj(id), 'unknown/non-owned');
    check(a.fobjs === head && f.real.getNode(head).next00 === tail && f.owner.getAObj(id) === a, 'malformed descent preserves real remover no-release behavior');
  }
  {
    const f = fixture(), id = f.runtime.allocateAObj(), a = f.owner.getAObj(id);
    a.flags = NaN; Object.defineProperty(a, 'flags', {writable: false});
    f.runtime.removeAObj(id); rejects(() => f.owner.getAObj(id), 'unknown/non-owned');
    check(Number.isNaN(a.flags), 'free does not inspect unused scalar fields');
    const reference = Symbol('ref');
    const copy = f.owner.createAObj({flags: 0, frame: 0, rewind: 0, end: 0, rate: 1, fobjs: null, joint18: reference});
    check(f.owner.getAObj(copy).joint18 === reference, 'createAObj preserves supplied joint18');
  }
  {
    const f = fixture();
    f.feedback.allocateAObj = () => {throw Error('replacement allocator');};
    f.feedback.getAObj = () => {throw Error('replacement resolver');};
    f.feedback.freeAObj = () => {throw Error('replacement free');};
    f.fobjs.removeAll = () => {throw Error('replacement removal');};
    f.descriptors.continueAllocatedLoad = () => {throw Error('replacement continuation');};
    const id = f.load(); f.runtime.removeAObj(id);
    check(f.events.join() === 'allocate,load,get,remove,free', 'fixed methods and original receivers');
  }
  for (const point of ['allocate', 'remove', 'load'] as const) {
    const f = fixture();
    f.hooks[point] = () => {
      f.runtime.removeAObj(null); check(f.runtime.loadDescriptor(null) === null, 'null nested operations bypass guard');
      rejects(() => f.runtime.allocateAObj(), 'reentry');
    };
    if (point === 'remove') {
      const id = f.load(), a = f.owner.getAObj(id), head = a.fobjs!;
      rejects(() => f.runtime.removeAObj(id), 'caught inside');
      check(a.fobjs === head, 'caught reentry aborts before next null store'); rejects(() => f.real.getNode(head), 'unknown/non-owned');
    } else {
      rejects(f.load, 'caught inside'); check(f.ids.length === 1, 'caught reentry retains actual allocated record');
      check(f.owner.getAObj(f.ids[0]!).fobjs === null || point === 'load', 'allocator poison precedes continuation');
    }
  }
  for (const result of [null, Symbol('foreign'), Promise.resolve(null)]) {
    const f = fixture(); f.hooks.override = true; f.hooks.result = result;
    rejects(f.load, 'allocated identity'); check(f.owner.getAObj(f.ids[0]!).end === 9, 'invalid continuation result retains actual source prefix');
  }
  {
    const f = fixture(), id = f.runtime.allocateAObj(), a = f.owner.getAObj(id);
    requestSourceAObj(a, 0, {requestAll() {
      rejects(() => f.owner.freeAObj(id), 'busy request/interpret');
    }, stopAll() {throw Error('unexpected stop');}, interpretAll() {throw Error('unexpected interpret');}});
    check(f.owner.getAObj(id) === a, 'busy request free refused before owner-map deletion');
    f.owner.freeAObj(id); rejects(() => setSourceAObjRate(a, 2), 'factory-created');
    const standalone = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: 1, rate: 1, fobjs: null});
    check(standalone.joint18 === null, 'existing standalone creation compatible');
    freeSourceAObj(standalone); rejects(() => freeSourceAObj(standalone), 'factory-created');
    rejects(() => freeSourceAObj({...standalone}), 'factory-created');
  }
  {
    const f = fixture(), id = f.runtime.allocateAObj(), a = f.owner.getAObj(id);
    a.flags = 0; a.end = 9;
    interpretSourceAObj(a, null, {requestAll() {throw Error('unexpected request');},
      stopAll() {throw Error('unexpected stop');}, interpretAll() {
        rejects(() => f.owner.freeAObj(id), 'busy request/interpret');
      }}, createSourceAObjCounters());
    check(f.owner.getAObj(id) === a && a.frame === 1, 'busy interpreter free refused without invalidation');
  }
  {
    const f = fixture(), id = f.load(), a = f.owner.getAObj(id), head = a.fobjs!;
    Object.defineProperty(f.real.getNode(head), 'next00', {writable: false});
    a.joint18 = 7 as unknown as symbol;
    rejects(() => f.runtime.removeAObj(id), 'joint18: opaque');
    check(a.fobjs === null && f.owner.getAObj(id) === a, 'malformed joint consumed after real readonly-link release and null store');
    rejects(() => f.real.getNode(head), 'unknown/non-owned');
  }
  {
    const f = fixture();
    const bad = {...f.feedback, allocateAObj: () => Promise.resolve(Symbol('not sync')) as unknown as symbol};
    const runtime: SourceAObjLifecycleRuntime = createSourceAObjLifecycleRuntime({feedback: bad, fobjs: f.real, descriptors: f.allocated});
    rejects(() => runtime.allocateAObj(), 'synchronously');
    rejects(() => f.runtime.removeAObj(Promise.resolve(null) as unknown as symbol), 'opaque symbol');
    rejects(() => f.runtime.removeAObj(Symbol('foreign owner')), 'unknown/non-owned');
  }
  {
    const f = fixture(), id = f.owner.allocateAObj(), a = f.owner.getAObj(id);
    a.frame = NaN; Object.defineProperty(a, 'rate', {writable: false});
    check(f.owner.getAObj(id) === a, 'ownership-only resolution ignores unrelated scalar and writable admission');
    freeSourceAObj(a);
    rejects(() => f.owner.getAObj(id), 'unknown/non-owned');
    rejects(() => f.owner.freeAObj(id), 'unknown/non-owned');
    rejects(() => f.runtime.removeAObj(id), 'unknown/non-owned');
    rejects(() => setSourceAObjFlags(a, 0), 'factory-created');
  }
  for (const point of ['remove', 'free'] as const) {
    const f = fixture(), id = f.load(), a = f.owner.getAObj(id), head = a.fobjs!;
    const runtime = createSourceAObjLifecycleRuntime({
      feedback: {...f.owner, freeAObj(value) {
        f.owner.freeAObj(value); return (point === 'free' ? Promise.resolve() : undefined) as unknown as void;
      }},
      fobjs: {removeAll(value) {
        f.real.removeAll(value); return (point === 'remove' ? Promise.resolve() : undefined) as unknown as void;
      }}, descriptors: f.allocated,
    });
    rejects(() => runtime.removeAObj(id), 'synchronously return undefined');
    rejects(() => f.real.getNode(head), 'unknown/non-owned');
    if (point === 'remove') check(f.owner.getAObj(id) === a && a.fobjs === head, 'async removal rejection retains released-list pointer before null store');
    else {check(a.fobjs === null && a.joint18 === null, 'async free refusal retains completed stores'); rejects(() => f.owner.getAObj(id), 'unknown/non-owned');}
  }
  console.log('[aobj-lifecycle] PASS: actual owned allocation, descriptor composition, ordered release and stale-record refusal; no physical pool or joint unref');
}
