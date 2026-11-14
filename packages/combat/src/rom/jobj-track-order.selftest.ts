import {createSourceJObjTrackOrderRuntime} from './jobj-track-order.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import type {SourceFObjHeader} from './fobj-list.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[jobj-track-order-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let message = ''; try {run();} catch (e) {message = String(e);}
  check(message.includes(expected), `expected ${expected}, got ${message || 'success'}`);
}
function fixture(tracks: number[] = [1, 12, 3], maxNodes?: number) {
  const j = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(j);
  const joint = j.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: 0, translation3c: 0, translation40: 0},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const f = createSourceFObjScalarCallbackRuntime(joint);
  const nodes = tracks.map(track13 => f.createNode({next00: null, cursor04: null, base08: null, length0c: 0,
    flags10: 0, byte11: 0, byte12: 0, track13, format14: 0, format15: 0, half16: 0,
    offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0}));
  nodes.forEach((id, i) => {f.getNode(id).next00 = nodes[i + 1] ?? null;});
  const aobj = feedback.createAObj({flags: 0, frame: 0, rewind: 0, end: 1, rate: 1, fobjs: nodes[0] ?? null});
  const a = feedback.getAObj(aobj), binding = j.getBinding(joint); binding.aobj7c = aobj;
  const events: string[] = [];
  const hooks: {binding?: () => void; aobj?: () => void; node?: (id: symbol, node: SourceFObjHeader) => void} = {};
  const joints = {getBinding(id: symbol) {
    check(this === joints, 'joint receiver'); events.push('binding'); const value = j.getBinding(id); hooks.binding?.(); return value;
  }};
  const fb = {getAObj(id: symbol) {
    check(this === fb, 'feedback receiver'); events.push('aobj'); const value = feedback.getAObj(id); hooks.aobj?.(); return value;
  }};
  const fobjs = {getFObj(owner: symbol, id: symbol) {
    check(this === fobjs && owner === aobj, 'fixed FObj receiver and retained owner');
    check(events.length < 12000, 'test getter safety cap');
    events.push(`node${nodes.indexOf(id)}`); const value = f.getNode(id); hooks.node?.(id, value); return value;
  }};
  const sources = {joints, feedback: fb, fobjs}, runtime = createSourceJObjTrackOrderRuntime(sources, maxNodes);
  const run = () => runtime.promoteFirstTrack12(joint);
  const order = () => {const out: symbol[] = []; let id = a.fobjs;
    while (id !== null) {check(!out.includes(id), 'output acyclic'); out.push(id); id = f.getNode(id).next00;} return out;};
  return {j, feedback, joint, f, nodes, aobj, a, binding, hooks, events, sources, runtime, run, order};
}
export function runJObjTrackOrderSelfTest(): void {
  for (const tracks of [[], [12], [12, 1, 2], [1, 12, 3], [1, 2, 12], [1, 2, 3], [1, 12, 12]]) {
    const x = fixture(tracks), before = x.nodes.slice(), index = tracks.indexOf(12);
    const expected = index < 0 ? before : [before[index]!, ...before.filter((_, i) => i !== index)];
    x.run(); check(x.order().every((id, i) => id === expected[i]) && x.order().length === expected.length, `order ${tracks}`);
    check(x.events.length === 2 + (index < 0 ? tracks.length : index + 1), 'no successor lookup after first match');
  }
  {const x = fixture([12, 1]); Object.defineProperty(x.f.getNode(x.nodes[0]!), 'next00', {writable: false});
    rejects(x.run, 'non-writable'); check(x.a.fobjs === x.nodes[1], 'head match detaches before second-store refusal');}
  {const x = fixture(); Object.defineProperty(x.f.getNode(x.nodes[1]!), 'next00', {writable: false});
    rejects(x.run, 'non-writable'); check(x.a.fobjs === x.nodes[0] && x.f.getNode(x.nodes[0]!).next00 === x.nodes[2], 'first store preserved');}
  {const x = fixture(); Object.defineProperty(x.f.getNode(x.nodes[0]!), 'next00', {writable: false});
    rejects(x.run, 'non-writable'); check(x.a.fobjs === x.nodes[0] && x.f.getNode(x.nodes[1]!).next00 === x.nodes[2], 'first-store refusal preserves all links');}
  {const x = fixture(); Object.defineProperty(x.a, 'fobjs', {writable: false});
    rejects(x.run, 'non-writable'); check(x.f.getNode(x.nodes[0]!).next00 === x.nodes[2] && x.f.getNode(x.nodes[1]!).next00 === x.nodes[0], 'two-store prefix preserved');}
  {const x = fixture([1, 2]); Object.defineProperty(x.a, 'fobjs', {writable: false});
    Object.defineProperty(x.binding, 'aobj7c', {writable: false});
    x.nodes.forEach(id => {Object.defineProperty(x.f.getNode(id), 'track13', {writable: false}); Object.defineProperty(x.f.getNode(id), 'next00', {writable: false});});
    x.run(); check(x.order().length === 2, 'read-only reads need no writes without match');}
  {const x = fixture(); x.hooks.node = (id) => {if (id === x.nodes[1]) {x.binding.aobj7c = null; x.a.fobjs = x.nodes[2]!;}};
    x.run(); check(x.a.fobjs === x.nodes[1] && x.f.getNode(x.nodes[1]!).next00 === x.nodes[2], 'retained AObj and live current head');}
  {const x = fixture([1, 2, 12]); x.hooks.node = id => {if (id === x.nodes[0]) x.f.getNode(id).next00 = x.nodes[2]!;};
    x.run(); check(x.events.join(',') === 'binding,aobj,node0,node2', 'live next read after node getter');}
  {const x = fixture([12, 2]); x.f.getNode(x.nodes[1]!).track13 = NaN;
    x.run(); check(x.a.fobjs === x.nodes[0], 'malformed unvisited tail ignored');}
  {const x = fixture([12]); const foreign = Symbol('unresolved successor'); x.f.getNode(x.nodes[0]!).next00 = foreign;
    x.run(); check(x.f.getNode(x.nodes[0]!).next00 === foreign, 'matched successor not resolved');}
  {const x = fixture(); x.runtime.promoteFirstTrack12(null); check(x.events.length === 0, 'null joint bypass');
    x.binding.aobj7c = null; x.run(); check(x.events.join(',') === 'binding', 'null AObj bypass');}
  {const x = fixture([]); x.run(); check(x.events.join(',') === 'binding,aobj', 'null list bypass');}
  for (const where of ['binding', 'aobj', 'node'] as const) {
    const x = fixture(); const reenter = () => {x.runtime.promoteFirstTrack12(null); rejects(x.run, 'same-runtime reentry');};
    x.hooks[where] = reenter; rejects(x.run, 'caught inside an adapter');
    check(x.events.length === (where === 'binding' ? 1 : where === 'aobj' ? 2 : 3), 'poison checked immediately after getter');
    check(x.a.fobjs === x.nodes[0] && x.f.getNode(x.nodes[0]!).next00 === x.nodes[1], 'reentry before any writes');
    delete x.hooks[where]; x.run(); check(x.a.fobjs === x.nodes[1], 'recovery after caught reentry');
  }
  {const x = fixture(); x.hooks.node = () => x.runtime.promoteFirstTrack12(null);
    x.run(); check(x.a.fobjs === x.nodes[1], 'nested null call alone never poisons outer pass');}
  {const x = fixture();
    x.a.flags = NaN; x.a.frame = NaN; x.a.rewind = NaN; x.a.end = NaN; x.a.rate = NaN;
    const joint = x.j.getJoint(x.joint); joint.flags14 = NaN; joint.rotation1c = NaN; joint.translation38 = NaN;
    for (const id of x.nodes) {
      const node = x.f.getNode(id); node.length0c = NaN; node.flags10 = NaN; node.frame1c = NaN;
      node.value20 = NaN; node.offset18 = NaN; node.format14 = NaN;
      (node as unknown as {base08: unknown}).base08 = 'invalid stream';
      (node as unknown as {cursor04: unknown}).cursor04 = 'invalid cursor';
    }
    x.run(); check(x.a.fobjs === x.nodes[1] && Number.isNaN(x.a.flags) && Number.isNaN(joint.flags14),
      'unrelated clocks, flags, transforms, stream metadata and scalars ignored');}
  {const x = fixture([...Array<number>(4096).fill(1), 12]);
    rejects(x.run, 'visit budget'); check(x.events.length === 4098 && x.a.fobjs === x.nodes[0], 'default 4096 cap before node4097');}
  {const x = fixture(); const bad = () => {throw Error('replacement invoked');};
    x.sources.joints.getBinding = bad; x.sources.feedback.getAObj = bad; x.sources.fobjs.getFObj = bad;
    x.sources.joints = {getBinding: bad}; x.run(); check(x.a.fobjs === x.nodes[1], 'captured methods/tables');}
  {const x = fixture(); rejects(() => x.runtime.promoteFirstTrack12(Symbol('foreign joint')), 'unknown');
    x.binding.aobj7c = Symbol('foreign AObj'); rejects(x.run, 'unknown'); x.binding.aobj7c = x.aobj;
    x.a.fobjs = Symbol('foreign FObj'); rejects(x.run, 'unknown');}
  for (const bad of [NaN, Infinity, -1, 256, 1.5, '12']) {
    const x = fixture([1]); (x.f.getNode(x.nodes[0]!) as unknown as {track13: unknown}).track13 = bad;
    rejects(x.run, 'expected byte');
  }
  {const x = fixture(); (x.binding as unknown as {aobj7c: unknown}).aobj7c = 1; rejects(x.run, 'opaque symbol');}
  {const x = fixture(); (x.a as unknown as {fobjs: unknown}).fobjs = undefined; rejects(x.run, 'opaque symbol');}
  {const x = fixture(); (x.f.getNode(x.nodes[0]!) as unknown as {next00: unknown}).next00 = 0; rejects(x.run, 'opaque symbol');}
  {const x = fixture(); x.hooks.node = (_, node) => {node.track13 = NaN; (node as unknown as {next00: unknown}).next00 = 0;};
    rejects(x.run, 'expected byte');}
  {const x = fixture([12]); (x.f.getNode(x.nodes[0]!) as unknown as {next00: unknown}).next00 = 0;
    rejects(x.run, 'opaque symbol'); check(x.a.fobjs === x.nodes[0], 'matched next validation before first store');}
  {const x = fixture([1, 2]); x.f.getNode(x.nodes[1]!).next00 = x.nodes[0]!; rejects(x.run, 'cycle/revisited');}
  {const x = fixture([1, 12], 1); rejects(x.run, 'visit budget'); check(x.events.length === 3, 'budget before next getter');}
  {const x = fixture([1, 2], 2); x.run(); check(x.events.length === 4, 'exact no-match budget allowed');}
  {const x = fixture([1, 12], 2); x.run(); check(x.a.fobjs === x.nodes[1], 'exact match budget allowed');}
  {const x = fixture([12], 1); x.f.getNode(x.nodes[0]!).next00 = x.nodes[0]!; x.run(); check(x.a.fobjs === x.nodes[0], 'no tail cycle preflight after match');}
  {const x = fixture([...Array<number>(10000).fill(1), 12], 10001); x.run(); check(x.a.fobjs === x.nodes[10000] && x.order().length === 10001, 'iterative large list');}
  for (const cap of [0, -1, NaN, Infinity, 1.5]) {
    const x = fixture(); rejects(() => createSourceJObjTrackOrderRuntime(x.sources, cap), 'positive safe integer');
  }
  {const x = fixture(); let read = false;
    const sources = Object.create(x.sources) as typeof x.sources;
    rejects(() => createSourceJObjTrackOrderRuntime(sources), 'own data');
    Object.defineProperty(sources, 'joints', {get() {read = true; return x.sources.joints;}});
    rejects(() => createSourceJObjTrackOrderRuntime(sources), 'own data'); check(!read, 'accessor table never invoked');}
}
