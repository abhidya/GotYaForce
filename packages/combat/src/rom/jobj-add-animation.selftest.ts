import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourceDisplayAnimationAttachmentRuntime} from './display-animation-attachment.js';
import {createSourceJObjAddAnimationRuntime} from './jobj-add-animation.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceFObjRuntime} from './fobj-list.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceAllocatedAObjDescriptorRuntime} from './allocated-aobj-descriptor.js';
import {createSourceAObjLifecycleRuntime} from './aobj-lifecycle.js';
import {createSourceJObjTrackOrderRuntime} from './jobj-track-order.js';
import {setSourceAObjRate} from './aobj-clock.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[jobj-add-animation-test] ${why}`);}
function rejects(fn: () => unknown, text: string): void {
  let error = ''; try {fn();} catch (e) {error = String(e);}
  check(error.includes(text), `expected ${text}, got ${error || 'success'}`);
}
function fixture() {
  const j = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(j);
  const joint = j.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: 0, translation3c: 0, translation40: 0},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const nodes: symbol[] = [], allocations: symbol[] = [], events: string[] = [];
  const fobjs = createSourceFObjRuntime(() => {throw Error('unexpected interpreter');});
  const loader = createSourceFObjDescriptorRuntime({createNode(initial) {const id = fobjs.createNode(initial); nodes.push(id); return id;}, getNode: fobjs.getNode});
  const descriptors = createSourceAllocatedAObjDescriptorRuntime({feedback, fobjs: loader, removal: fobjs});
  const life = createSourceAObjLifecycleRuntime({feedback: {
    allocateAObj() {const id = feedback.allocateAObj(); allocations.push(id); return id;}, getAObj: feedback.getAObj, freeAObj: feedback.freeAObj,
  }, fobjs, descriptors});
  const track = createSourceJObjTrackOrderRuntime({joints: j, feedback, fobjs: {getFObj(_owner, id) {return fobjs.getNode(id);}}});
  const hooks: Partial<Record<'binding' | 'joint' | 'remove' | 'load' | 'order' | 'set' | 'clear', () => void>> = {};
  const joints = {
    getBinding(id: symbol) {check(this === joints, 'binding receiver'); events.push('binding'); hooks.binding?.(); return j.getBinding(id);},
    getJoint(id: symbol) {check(this === joints, 'joint receiver'); events.push('joint'); hooks.joint?.(); return j.getJoint(id);},
    setFlags(id: symbol | null, mask: number) {check(this === joints, 'set receiver'); events.push('set'); j.setFlags(id, mask); hooks.set?.();},
    clearFlags(id: symbol | null, mask: number) {check(this === joints, 'clear receiver'); events.push('clear'); j.clearFlags(id, mask); hooks.clear?.();},
  };
  const lifecycle = {
    removeAObj(id: symbol | null) {check(this === lifecycle, 'remove receiver'); events.push('remove'); life.removeAObj(id); hooks.remove?.();},
    loadDescriptor(id: symbol | null) {check(this === lifecycle, 'load receiver'); events.push('load'); const result = life.loadDescriptor(id); hooks.load?.(); return result;},
  };
  const order = {promoteFirstTrack12(id: symbol | null) {check(this === order, 'order receiver'); events.push('order'); track.promoteFirstTrack12(id); hooks.order?.();}};
  const runtime = createSourceJObjAddAnimationRuntime({joints, lifecycle, order});
  const tail = loader.createDescriptor({next00: null, length04: 0, start08: 0, track0c: 12, format0d: 0, format0e: 0, data10: null});
  const head = loader.createDescriptor({next00: tail, length04: 0, start08: 0, track0c: 1, format0d: 0, format0e: 0, data10: null});
  const ad = descriptors.createDescriptor({flags00: 0, end04: 5, fobj08: head, joint0c: null});
  const input = {aobj08: ad, robj0c: null, flags10: 1};
  const id = runtime.createDescriptor(input), d = runtime.getDescriptor(id), binding = j.getBinding(joint), scalar = j.getJoint(joint);
  const run = () => runtime.addAnimation(joint, id);
  return {j, feedback, joint, fobjs, loader, descriptors, life, runtime, joints, lifecycle, order, hooks, events, nodes, allocations, input, id, d, ad, binding, scalar, run};
}
export function runJObjAddAnimationSelfTest(): void {
  {const x = fixture(); check(Object.isFrozen(x.runtime) && Object.isSealed(x.d) && x.d !== x.input, 'owned descriptor');
    x.input.aobj08 = Symbol('unused'); x.input.flags10 = 0;
    x.run(); const old = x.binding.aobj7c!, oldRecord = x.feedback.getAObj(old), oldNodes = x.nodes.slice();
    check(oldRecord.fobjs === x.nodes[1] && x.fobjs.getNode(x.nodes[1]!).next00 === x.nodes[0], 'actual first-track12 promotion');
    check(x.scalar.flags14 === 0x48 && oldRecord.rate === 1 && oldRecord.end === 5, 'actual allocation and source flags');
    x.events.length = 0; x.d.flags10 = 0; x.run();
    check(x.binding.aobj7c !== old && x.scalar.flags14 === 0x40 && x.events.indexOf('remove') < x.events.indexOf('load'), 'replacement removes then loads');
    rejects(() => x.feedback.getAObj(old), 'unknown'); rejects(() => setSourceAObjRate(oldRecord, 2), 'factory-created');
    oldNodes.forEach(id => rejects(() => x.fobjs.getNode(id), 'unknown'));
  }
  {const x = fixture(); x.runtime.addAnimation(null, Symbol('unowned')); check(x.events.length === 0, 'null bypass');
    x.binding.aobj7c = Symbol('unresolved'); x.runtime.addAnimation(x.joint, null);
    check(x.events.join() === 'joint,binding', 'null animation skips all attachment fields');
  }
  {const x = fixture(); x.d.aobj08 = null; x.run(); check(x.binding.aobj7c === null && x.allocations.length === 0 && x.events.includes('load') && x.events.includes('order'), 'real null load and reorder forwarded');}
  {const x = fixture(); x.run(); const old = x.binding.aobj7c!, oldNodes = x.nodes.slice();
    x.descriptors.getDescriptor(x.ad).fobj08 = Symbol('bad descriptor');
    rejects(x.run, 'unknown/non-owned descriptor'); check(x.binding.aobj7c === old && x.allocations.length === 2, 'failed load retains dangling old binding and new allocation');
    rejects(() => x.feedback.getAObj(old), 'unknown'); oldNodes.forEach(id => rejects(() => x.fobjs.getNode(id), 'unknown'));
  }
  {const x = fixture(); Object.defineProperty(x.binding, 'aobj7c', {writable: false}); rejects(x.run, 'non-writable');
    check(x.allocations.length === 1 && x.nodes.length === 2 && x.binding.aobj7c === null && !x.events.includes('order'), 'read-only target fails only after actual load');}
  for (const target of [null, Symbol('RObj')]) for (const descriptor of [null, Symbol('RObj descriptor')]) {
    const x = fixture(); x.binding.robj80 = target; x.d.robj0c = descriptor;
    if (target !== null && descriptor !== null) {rejects(x.run, 'non-null RObj'); check(x.binding.aobj7c !== null && x.scalar.flags14 === 0 && x.events.includes('order') && !x.events.includes('set'), 'RObj exact prefix');}
    else {x.run(); check(x.scalar.flags14 === 0x48, 'either-null RObj no-op');}
  }
  {const x = fixture(); x.binding.dobj18 = Symbol('DObj'); rejects(x.run, 'non-null DObj'); check(x.binding.aobj7c !== null && x.scalar.flags14 === 0x48 && x.events.includes('set'), 'DObj refusal after flags');}
  {const x = fixture(); x.binding.dobj18 = Symbol('DObj'); rejects(() => x.runtime.addAnimation(x.joint, null), 'non-null DObj'); check(x.allocations.length === 0, 'null animation still reaches DObj');}
  for (const flag of [0x20, 0x4000, 0x4020]) {const x = fixture(); x.scalar.flags14 = flag; x.binding.dobj18 = 7 as unknown as symbol; x.run(); check(x.scalar.flags14 === (flag | 0x48), 'flags4020 skip malformed DObj');}
  for (const field of ['aobj08', 'robj0c', 'flags10'] as const) {const x = fixture(); x.run(); const old = x.binding.aobj7c!; x.events.length = 0;
    (x.d as unknown as Record<string, unknown>)[field] = NaN; rejects(x.run, field);
    rejects(() => x.feedback.getAObj(old), 'unknown');
    check(x.allocations.length === (field === 'aobj08' ? 1 : 2), `${field} lazy allocation boundary`);
    check(x.events.includes('order') === (field !== 'aobj08') && !x.events.includes('set'), `${field} lazy order boundary`);
  }
  {const x = fixture(); x.hooks.set = () => {x.scalar.flags14 |= 0x20; x.binding.dobj18 = 7 as unknown as symbol;}; x.run(); check((x.scalar.flags14 & 0x20) !== 0, 'fresh flags after effect');}
  {const x = fixture(); x.hooks.order = () => {x.binding.robj80 = Symbol('new RObj'); x.d.robj0c = Symbol('new descriptor');}; rejects(x.run, 'non-null RObj'); check(!x.events.includes('set'), 'fresh RObj arguments after order');}
  for (const key of ['binding', 'joint', 'load', 'order', 'set'] as const) {const x = fixture(); x.hooks[key] = () => {x.runtime.addAnimation(null, null); rejects(x.run, 'same-runtime reentry');};
    rejects(x.run, 'caught inside an adapter'); delete x.hooks[key];
  }
  {const x = fixture(); x.run(); x.hooks.remove = () => rejects(x.run, 'same-runtime reentry'); rejects(x.run, 'caught inside an adapter'); check(x.allocations.length === 1, 'remove poison stops before reload');}
  {const x = fixture(); x.run(); const old = x.binding.aobj7c!;
    rejects(() => x.runtime.addAnimation(x.joint, Symbol('foreign AnimJoint')), 'unknown/non-owned animation descriptor');
    rejects(() => x.feedback.getAObj(old), 'unknown'); check(x.binding.aobj7c === old && x.allocations.length === 1, 'descriptor ownership deferred until after old removal');}
  {const x = fixture(); x.hooks.set = () => {x.scalar.flags14 = NaN;}; rejects(x.run, 'flags14');
    check(x.binding.aobj7c !== null && x.events.at(-1) === 'joint', 'malformed fresh final flags after attachment and set');}
  {const x = fixture(); x.hooks.load = () => {x.binding.aobj7c = 7 as unknown as symbol;}; x.run();
    check(typeof x.binding.aobj7c === 'symbol', 'attachment store does not validate overwritten prior field');}
  {const x = fixture(); x.hooks.binding = () => x.runtime.addAnimation(null, Symbol('ignored')); x.run();
    check(x.binding.aobj7c !== null, 'null nested call never poisons');}
  {const x = fixture(); x.joints.getBinding = () => {throw Error('replaced');}; x.lifecycle.loadDescriptor = () => {throw Error('replaced');}; x.order.promoteFirstTrack12 = () => {throw Error('replaced');}; x.run(); check(x.binding.aobj7c !== null, 'captured functions retain original receivers');}
  {const x = fixture(); Object.freeze(x.d); x.run(); check(x.binding.aobj7c !== null && x.scalar.flags14 === 0x48, 'read-only AnimJoint descriptor fields are consumed without writes');}
  for (const point of ['remove', 'order', 'set'] as const) {
    const x = fixture(); if (point === 'remove') x.run();
    const runtime = createSourceJObjAddAnimationRuntime({joints: {...x.j, setFlags(id, mask) {
      x.j.setFlags(id, mask); return (point === 'set' ? Promise.resolve() : undefined) as unknown as void;
    }}, lifecycle: {...x.life, removeAObj(id) {
      x.life.removeAObj(id); return (point === 'remove' ? Promise.resolve() : undefined) as unknown as void;
    }}, order: {promoteFirstTrack12(id) {
      x.order.promoteFirstTrack12(id); return (point === 'order' ? Promise.resolve() : undefined) as unknown as void;
    }}});
    const old = x.binding.aobj7c, descriptor = runtime.createDescriptor(x.d);
    rejects(() => runtime.addAnimation(x.joint, descriptor), 'synchronously return void');
    if (point === 'remove') {check(x.binding.aobj7c === old && x.allocations.length === 1, 'async removal retains freed binding without new allocation'); rejects(() => x.feedback.getAObj(old!), 'unknown');}
    else check(x.binding.aobj7c !== null && x.scalar.flags14 === (point === 'set' ? 0x48 : 0), 'async later effect keeps actual attachment and completed prefix');
  }
  {const x = fixture(), dobjs = createSourceDObjAnimationRuntime();
    const first = dobjs.createDObj({next04: null, pobj0c: Symbol('PObj'), mobj08: Symbol('MObj'), aobj10: Symbol('display AObj'), classUpdate44: Symbol('callback')});
    const real = createSourceDisplayAnimationAttachmentRuntime(dobjs), calls: (symbol | null)[] = [];
    let hook = () => {};
    const displayAttachment = {attachNullDescriptors(list: symbol | null) {
      check(this === displayAttachment, 'display receiver'); calls.push(list); real.attachNullDescriptors(list); hook();
    }};
    const runtime = createSourceJObjAddAnimationRuntime({joints: x.joints, lifecycle: x.lifecycle, order: x.order, displayAttachment});
    const descriptor = runtime.createDescriptor(x.d);
    x.binding.dobj18 = first; runtime.addAnimation(x.joint, null);
    check(calls.length === 1 && calls[0] === first && x.allocations.length === 0, 'null AnimJoint runs real display tail');
    for (const flag of [0x20, 0x4000, 0x4020]) {x.scalar.flags14 = flag; runtime.addAnimation(x.joint, null);}
    check(calls.length === 1, 'flags4020 skip display tail'); x.scalar.flags14 = 0;
    displayAttachment.attachNullDescriptors = () => {throw Error('replaced');};
    runtime.addAnimation(x.joint, descriptor); const old = x.binding.aobj7c!;
    check(calls.length === 2, 'captured display method');
    x.hooks.set = () => {x.binding.dobj18 = first;}; x.binding.dobj18 = null;
    dobjs.getDObj(first).next04 = Symbol('foreign DObj');
    rejects(() => runtime.addAnimation(x.joint, descriptor), 'unknown/non-owned DObj');
    check(x.binding.aobj7c !== old && x.binding.aobj7c !== null && x.scalar.flags14 === 0x48 && calls.at(-1) === first, 'fresh DObj binding and completed replacement survive late failure');
    rejects(() => x.feedback.getAObj(old), 'unknown'); dobjs.getDObj(first).next04 = null;
    hook = () => rejects(() => runtime.addAnimation(x.joint, null), 'same-runtime reentry');
    rejects(() => runtime.addAnimation(x.joint, null), 'caught inside an adapter');
  }
  {const x = fixture(); const runtime = createSourceJObjAddAnimationRuntime({joints: x.j, lifecycle: x.life, order: x.order,
    displayAttachment: {attachNullDescriptors() {return Promise.resolve() as unknown as void;}}});
    rejects(() => runtime.addAnimation(x.joint, null), 'synchronously return void');
  }

}
