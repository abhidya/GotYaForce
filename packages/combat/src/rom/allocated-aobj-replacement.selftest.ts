import {createSourceAObj, AOBJ_LOOP} from './aobj-clock.js';
import {createSourceFObjRuntime, type SourceFObjHeader} from './fobj-list.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceAllocatedAObjDescriptorRuntime} from './allocated-aobj-descriptor.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[allocated-aobj-replacement-test] ${why}`);}
function rejects(fn: () => unknown, text: string): void {
  let message = ''; try {fn();} catch (e) {message = String(e);}
  check(message.includes(text), `expected ${text}, got ${message || 'success'}`);
}
function fixture() {
  const real = createSourceFObjRuntime(() => {throw Error('unexpected interpretation');});
  const nodes: symbol[] = [], events: string[] = [];
  const loader = createSourceFObjDescriptorRuntime({createNode(initial) {
    const node = real.createNode(initial); nodes.push(node); return node;
  }, getNode(id) {return real.getNode(id);}});
  const tail = loader.createDescriptor({next00: null, length04: 0, start08: 0, track0c: 7, format0d: 0x80, format0e: 0x80, data10: null});
  const head = loader.createDescriptor({next00: tail, length04: 0, start08: 0, track0c: 5, format0d: 0x80, format0e: 0x80, data10: null});
  const old = loader.loadDescriptors(head)!, oldTail = real.getNode(old).next00!;
  const oldHeaders = [real.getNode(old), real.getNode(oldTail)]; nodes.length = 0;
  const aobj = createSourceAObj({flags: 0x40000000, frame: 9, rewind: -3, end: 99, rate: 4, fobjs: old});
  const aobjId = Symbol('actual preallocated clock');
  const hooks: {load?: () => void; beforeRemove?: () => void; afterRemove?: () => void; result?: unknown} = {};
  const feedback = {getAObj(id: symbol) {check(id === aobjId, 'actual owner'); return aobj;}};
  const fobjs = {loadDescriptors(id: symbol | null) {
    events.push('load'); const loaded = loader.loadDescriptors(id); hooks.load?.(); return loaded;
  }};
  const removal = {removeAll(id: symbol | null): void {
    check(this === removal, 'fixed real remover receiver');
    events.push('remove'); hooks.beforeRemove?.(); real.removeAll(id); hooks.afterRemove?.();
    return hooks.result as undefined;
  }};
  const runtime = createSourceAllocatedAObjDescriptorRuntime({feedback, fobjs, removal});
  const descriptorId = runtime.createDescriptor({flags00: AOBJ_LOOP, end04: 3, fobj08: head, joint0c: null});
  const descriptor = runtime.getDescriptor(descriptorId);
  const run = () => runtime.continueAllocatedLoad(aobjId, descriptorId);
  const alive = (id: symbol) => {real.getNode(id);};
  const released = (id: symbol, header?: SourceFObjHeader) => {
    rejects(() => real.getNode(id), 'unknown/non-owned node identity');
    if (header) rejects(() => real.validateNode(header), 'non-owned header');
  };
  return {real, loader, head, tail, nodes, events, old, oldTail, oldHeaders, aobj, aobjId, hooks,
    removal, runtime, descriptorId, descriptor, run, alive, released};
}
export function runAllocatedAObjReplacementSelfTest(): void {
  {
    const x = fixture();
    x.hooks.beforeRemove = () => {
      check(x.nodes.length === 2 && x.aobj.fobjs === x.old && x.aobj.end === 3 && x.aobj.rewind === 0,
        'actual complete new allocation and clock prefix precede removal, not attachment');
      x.alive(x.nodes[0]!); x.alive(x.oldTail);
    };
    x.removal.removeAll = () => {throw Error('replaced remover');};
    check(x.run() === x.aobjId && x.events.join() === 'load,remove' && x.aobj.fobjs === x.nodes[0],
      'fixed remover called after load and before actual replacement');
    x.released(x.old, x.oldHeaders[0]); x.released(x.oldTail, x.oldHeaders[1]);
    x.alive(x.nodes[0]!); x.alive(x.nodes[1]!);
    check(x.aobj.frame === 9 && x.aobj.rate === 4, 'replacement does not reset unconsumed frame/rate');
  }
  {
    const x = fixture(); x.descriptor.fobj08 = null;
    x.run();
    check(x.nodes.length === 0 && x.aobj.fobjs === null && x.events.join() === 'load,remove', 'null new list still releases old list');
    x.released(x.old); x.released(x.oldTail);
  }
  {
    const x = fixture(); x.aobj.fobjs = null;
    x.run(); check(x.events.join() === 'load' && x.aobj.fobjs === x.nodes[0], 'null old head skips remover');
    x.alive(x.old); x.alive(x.oldTail);
  }
  {
    const x = fixture(); x.hooks.load = () => {x.aobj.fobjs = null;};
    x.run(); check(x.events.join() === 'load', 'live null head after loader'); x.alive(x.old);
  }
  {
    const x = fixture(); const alternative = x.loader.loadDescriptors(x.head)!;
    x.nodes.length = 0; x.hooks.load = () => {x.aobj.fobjs = alternative;};
    x.run(); x.released(alternative); x.alive(x.old); x.alive(x.oldTail);
    check(x.aobj.fobjs === x.nodes[0], 'live replacement old head after loader');
  }
  {
    const x = fixture(); x.loader.getDescriptor(x.tail).start08 = 0.5;
    rejects(x.run, 'integral signed16');
    check(x.nodes.length === 2 && x.events.join() === 'load' && x.aobj.fobjs === x.old && x.aobj.end === 3,
      'real partial loader failure retains new allocations and old owner before release');
    x.alive(x.old); x.alive(x.oldTail); x.alive(x.nodes[0]!); x.alive(x.nodes[1]!);
  }
  for (const successor of [Symbol('foreign tail'), 7]) {
    const x = fixture(); x.real.getNode(x.oldTail).next00 = successor as symbol;
    x.descriptor.joint0c = 7 as unknown as symbol;
    rejects(x.run, typeof successor === 'symbol' ? 'unknown/non-owned node identity' : 'next00');
    check(x.nodes.length === 2 && x.aobj.fobjs === x.old && x.events.join() === 'load,remove', 'release failure retains old attachment and new real allocation before joint read');
    x.alive(x.old); x.alive(x.oldTail); x.alive(x.nodes[0]!);
  }
  {
    const x = fixture(); x.descriptor.joint0c = Symbol('unsupported joint');
    rejects(x.run, 'joint ID'); x.released(x.old); x.released(x.oldTail);
    check(x.aobj.fobjs === x.nodes[0], 'joint refusal follows completed old release and new attachment');
  }
  {
    const x = fixture(); Object.defineProperty(x.aobj, 'fobjs', {writable: false});
    rejects(x.run, 'non-writable'); x.released(x.old); x.released(x.oldTail);
    check(x.aobj.fobjs === x.old && x.nodes.length === 2, 'read-only destination refused only after source release, retaining stale old head and new allocations');
  }
  {
    const x = fixture(); x.hooks.afterRemove = () => {
      x.aobj.fobjs = 7 as unknown as symbol; x.descriptor.joint0c = Symbol('late joint');
      x.aobj.end = NaN; x.descriptor.end04 = NaN;
    };
    rejects(x.run, 'joint ID');
    check(x.aobj.fobjs === x.nodes[0] && Number.isNaN(x.aobj.end), 'final store overwrites live old field without revalidating consumed fields; joint read remains live');
    x.released(x.old);
  }
  for (const result of [null, 7, {}, Promise.resolve()]) {
    const x = fixture(); x.hooks.result = result;
    rejects(x.run, 'removeAll must complete synchronously');
    x.released(x.old); x.released(x.oldTail);
    check(x.aobj.fobjs === x.old && x.nodes.length === 2, 'invalid remover result refuses attachment after real release');
  }
  {
    const x = fixture(); x.hooks.afterRemove = () => {throw Error('after real release');};
    rejects(x.run, 'after real release'); x.released(x.old);
    check(x.aobj.fobjs === x.old && x.nodes.length === 2, 'remover exception keeps actual released prefix');
  }
  {
    const x = fixture(); x.hooks.afterRemove = () => {
      check(x.runtime.continueAllocatedLoad(Symbol('ignored'), null) === null, 'null descriptor bypass while removing');
      rejects(() => x.runtime.continueAllocatedLoad(null, x.descriptorId), 'reentry');
    };
    rejects(x.run, 'reentry was caught'); x.released(x.old);
    check(x.aobj.fobjs === x.old && x.nodes.length === 2, 'caught remover reentry prevents subsequent attachment');
    delete x.hooks.afterRemove; x.aobj.fobjs = null;
    x.run(); check(x.aobj.fobjs === x.nodes[2], 'guard recovers after partial release refusal with explicit valid owner state');
  }
  {
    const x = fixture();
    check(x.runtime.continueAllocatedLoad(null, x.descriptorId) === null && x.nodes.length === 2 &&
      x.events.join() === 'load', 'null target loads but never releases any list'); x.alive(x.old);
    rejects(() => createSourceAllocatedAObjDescriptorRuntime({feedback: {getAObj() {return x.aobj;}},
      fobjs: x.loader, removal: Object.create(x.removal) as typeof x.removal}), 'own data');
  }
}
