import {createSourceAObj, AOBJ_LOOP, AOBJ_NO_CALLBACK, type SourceAObj} from './aobj-clock.js';
import {createSourceFObjRuntime} from './fobj-list.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceAllocatedAObjDescriptorRuntime, type SourceAllocatedAObjDescriptor} from './allocated-aobj-descriptor.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[allocated-aobj-descriptor-test] ${why}`);}
function rejects(fn: () => unknown, text: string): void {
  let message = ''; try {fn();} catch (e) {message = String(e);}
  check(message.includes(text), `expected ${text}, got ${message || 'success'}`);
}
function fixture() {
  const aobj = createSourceAObj({flags: 0x40000003, frame: 4, rewind: -2, end: 8, rate: 2, fobjs: null});
  const aobjId = Symbol('already allocated'), nodes: symbol[] = [], events: string[] = [];
  const real = createSourceFObjRuntime(() => {throw Error('unexpected interpreter');});
  const loader = createSourceFObjDescriptorRuntime({createNode(initial) {
    const id = real.createNode(initial); nodes.push(id); return id;
  }, getNode(id) {return real.getNode(id);}});
  const tail = loader.createDescriptor({next00: null, length04: 17, start08: -3, track0c: 9, format0d: 0x20, format0e: 0x40, data10: Symbol('stream')});
  const head = loader.createDescriptor({next00: tail, length04: 2, start08: 7, track0c: 3, format0d: 0, format0e: 0, data10: null});
  const hooks: {resolve?: () => void; load?: () => void; result?: unknown; overrideResult?: boolean} = {};
  const feedback = {getAObj(id: symbol): SourceAObj {
    check(this === feedback, 'resolver receiver retained'); check(id === aobjId, 'supplied identity resolved');
    events.push('resolve'); hooks.resolve?.(); return aobj;
  }};
  const fobjs = {loadDescriptors(id: symbol | null): symbol | null {
    check(this === fobjs, 'loader receiver retained'); events.push('load');
    const value = loader.loadDescriptors(id); hooks.load?.();
    return hooks.overrideResult ? hooks.result as symbol | null : value;
  }};
  const runtime = createSourceAllocatedAObjDescriptorRuntime({feedback, fobjs, removal: real});
  const input: SourceAllocatedAObjDescriptor = {flags00: 0xffffffff, end04: -0, fobj08: head, joint0c: null};
  const id = runtime.createDescriptor(input), descriptor = runtime.getDescriptor(id);
  return {aobj, aobjId, real, loader, nodes, events, hooks, feedback, fobjs, runtime, input, id, descriptor};
}
export function runAllocatedAObjDescriptorSelfTest(): void {
  {
    const f = fixture();
    check(Object.isFrozen(f.runtime) && Object.isSealed(f.descriptor) && f.descriptor !== f.input && f.runtime.getDescriptor(f.id) === f.descriptor, 'fixed table and separately owned stable descriptor');
    f.input.end04 = 77; f.input.fobj08 = null;
    f.feedback.getAObj = () => {throw Error('replacement resolver');};
    f.fobjs.loadDescriptors = () => {throw Error('replacement loader');};
    check(f.runtime.continueAllocatedLoad(f.aobjId, f.id) === f.aobjId, 'return supplied identity');
    check(f.events.join() === 'resolve,load', 'single resolution and actual load');
    check(f.aobj.flags === (0x40000003 | AOBJ_LOOP | AOBJ_NO_CALLBACK) && Object.is(f.aobj.rewind, 0) && Object.is(f.aobj.end, -0), 'masked flags and exact signed-zero setters');
    check(f.aobj.frame === 4 && f.aobj.rate === 2, 'no guessed allocation rate or frame');
    check(f.aobj.fobjs === f.nodes[0] && f.real.getNode(f.nodes[0]!).next00 === f.nodes[1] && f.real.getNode(f.nodes[1]!).offset18 === -3, 'actual two-node FObj loading and attachment');
  }
  {
    const f = fixture();
    check(f.runtime.continueAllocatedLoad(Symbol('unresolved'), null) === null && f.events.length === 0, 'null descriptor bypass');
    f.descriptor.flags00 = NaN; Object.defineProperty(f.descriptor, 'flags00', {writable: false});
    f.descriptor.end04 = NaN;
    check(f.runtime.continueAllocatedLoad(null, f.id) === null && f.nodes.length === 2 && f.events.join() === 'load', 'null target skips flags and numeric end admission but really loads');
    f.descriptor.joint0c = Symbol('joint');
    rejects(() => f.runtime.continueAllocatedLoad(null, f.id), 'joint ID');
    check(f.nodes.length === 4, 'null target joint refusal occurs after new actual allocations');
  }
  {
    const f = fixture(); Object.defineProperty(f.descriptor, 'end04', {writable: false});
    rejects(() => f.runtime.continueAllocatedLoad(null, f.id), 'end04');
    check(f.events.length === 0, 'null target still checks end access');
  }
  for (const field of ['flags00', 'end04', 'fobj08', 'joint0c'] as const) {
    const f = fixture();
    (f.descriptor as unknown as Record<string, unknown>)[field] = field === 'flags00' || field === 'end04' ? NaN : 7;
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), field === 'end04' ? 'set end' : field);
    check(f.aobj.flags === (field === 'flags00' ? 0x40000003 : 0x70000003), `${field} flag prefix`);
    check(f.aobj.rewind === (field === 'flags00' ? -2 : 0), `${field} rewind prefix`);
    check(Object.is(f.aobj.end, field === 'flags00' || field === 'end04' ? 8 : -0), `${field} end prefix`);
    check(f.nodes.length === (field === 'joint0c' ? 2 : 0), `${field} allocation prefix`);
    check(f.aobj.fobjs === (field === 'joint0c' ? f.nodes[0] : null), `${field} attach prefix`);
  }
  {
    const f = fixture(), old = Symbol('old'); f.aobj.fobjs = old;
    f.descriptor.joint0c = 7 as unknown as symbol;
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), 'unknown/non-owned node identity');
    check(f.nodes.length === 2 && f.aobj.fobjs === old && f.real.getNode(f.nodes[1]!).track13 === 9, 'real new list survives refusal before old removal and joint read');
  }
  {
    const f = fixture(); f.descriptor.joint0c = Symbol('joint');
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), 'joint ID');
    check(f.aobj.fobjs === f.nodes[0], 'joint refusal after actual attachment');
  }
  {
    const f = fixture(); f.descriptor.fobj08 = null;
    check(f.runtime.continueAllocatedLoad(f.aobjId, f.id) === f.aobjId && f.nodes.length === 0 && f.aobj.fobjs === null && f.events.join() === 'resolve,load', 'null FObj head still calls the actual null loader');
  }
  {
    const f = fixture();
    const bad = f.loader.createDescriptor({next00: null, length04: 1, start08: 0.5, track0c: 1, format0d: 0, format0e: 0, data10: null});
    f.descriptor.fobj08 = bad;
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), 'integral signed16');
    check(f.nodes.length === 1 && f.aobj.fobjs === null && Object.is(f.aobj.end, -0), 'real loader failure keeps actual partial allocation and AObj prefix');
    f.descriptor.fobj08 = null;
    check(f.runtime.continueAllocatedLoad(f.aobjId, f.id) === f.aobjId, 'recovery after real loader throw');
  }
  {
    const f = fixture(); f.hooks.resolve = () => {throw Error('resolver refusal');};
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), 'resolver refusal');
    check(f.aobj.flags === 0x40000003 && f.nodes.length === 0, 'resolver failure before any stores/load');
  }
  for (const foreign of [false, true]) {
    const f = fixture(), old = Symbol('retained old head'); f.aobj.fobjs = old;
    f.descriptor.fobj08 = foreign ? Symbol('foreign FObj descriptor') : f.loader.createDescriptor({next00: null, length04: 1, start08: 0.5, track0c: 1, format0d: 0, format0e: 0, data10: null});
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), foreign ? 'non-owned descriptor' : 'integral signed16');
    check(f.nodes.length === 1 && f.aobj.fobjs === old && f.aobj.flags === 0x70000003 && Object.is(f.aobj.rewind, 0) && Object.is(f.aobj.end, -0), 'actual loader failure preserves full AObj prefix and old head');
  }
  {
    const f = fixture();
    f.hooks.load = () => {
      f.descriptor.flags00 = NaN; f.descriptor.end04 = NaN;
      f.aobj.flags = NaN; f.aobj.end = NaN;
    };
    check(f.runtime.continueAllocatedLoad(f.aobjId, f.id) === f.aobjId && f.aobj.fobjs === f.nodes[0] && Number.isNaN(f.aobj.flags) && Number.isNaN(f.aobj.end), 'consumed descriptor and target flags/end are not revalidated after loader');
  }
  for (const joint of [Symbol('late joint'), 7]) {
    const f = fixture();
    f.hooks.load = () => {f.descriptor.joint0c = joint as symbol;};
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), typeof joint === 'symbol' ? 'joint ID' : 'joint0c');
    check(f.aobj.fobjs === f.nodes[0] && f.nodes.length === 2, 'live joint field mutation is consumed after attachment');
  }
  {
    const f = fixture(); f.descriptor.joint0c = Symbol('removed by loader');
    f.hooks.load = () => {f.descriptor.joint0c = null;};
    check(f.runtime.continueAllocatedLoad(f.aobjId, f.id) === f.aobjId && f.aobj.fobjs === f.nodes[0], 'joint cleared by actual loader is read live');
  }
  for (const phase of ['resolve', 'load'] as const) {
    const f = fixture();
    f.hooks[phase] = () => {
      check(f.runtime.continueAllocatedLoad(f.aobjId, null) === null, 'null descriptor bypasses busy guard');
      rejects(() => f.runtime.continueAllocatedLoad(null, f.id), 'reentry');
    };
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), 'reentry was caught');
    check(f.aobj.fobjs === null && f.nodes.length === (phase === 'load' ? 2 : 0), 'poisoned reentry stops next stage without rolling back real load');
    check(f.aobj.flags === (phase === 'load' ? 0x70000003 : 0x40000003), 'resolver reentry stops before flags');
    delete f.hooks[phase];
    check(f.runtime.continueAllocatedLoad(f.aobjId, f.id) === f.aobjId, 'guard recovers after refusal');
  }
  for (const result of [undefined, 7, {}, Promise.resolve(null)]) {
    const f = fixture(); f.hooks.overrideResult = true; f.hooks.result = result;
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), 'loadDescriptors result');
    check(f.nodes.length === 2 && f.aobj.fobjs === null, 'invalid/async result refused after actual allocations before attach');
  }
  {
    const f = fixture(); f.aobj.frame = NaN; f.aobj.rate = NaN; f.aobj.end = NaN; f.aobj.rewind = NaN;
    check(f.runtime.continueAllocatedLoad(f.aobjId, f.id) === f.aobjId && Object.is(f.aobj.end, -0), 'unconsumed frame/rate and overwritten old fields are not inspected');
  }
  {
    const f = fixture(); f.hooks.load = () => {f.aobj.fobjs = Symbol('installed during loader');};
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), 'unknown/non-owned node identity');
    check(f.nodes.length === 2, 'old list read is live after loader');
  }
  {
    const f = fixture(); Object.defineProperty(f.aobj, 'fobjs', {writable: false});
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, f.id), 'fobjs');
    check(f.nodes.length === 2 && Object.is(f.aobj.end, -0), 'target attachment writability checked after actual loading');
    rejects(() => f.runtime.continueAllocatedLoad(f.aobjId, Symbol('foreign')), 'non-owned descriptor');
  }
  {
    let called = false;
    const initial = {get flags00() {called = true; return 0;}, end04: 0, fobj08: null, joint0c: null};
    const f = fixture(); rejects(() => f.runtime.createDescriptor(initial), 'own data'); check(!called, 'factory rejects accessor without invoking it');
    rejects(() => createSourceAllocatedAObjDescriptorRuntime({feedback: Object.create(f.feedback) as typeof f.feedback, fobjs: f.fobjs, removal: f.real}), 'own data');
    rejects(() => f.runtime.createDescriptor({...f.input, end04: 0.1}), 'float32');
  }
}
