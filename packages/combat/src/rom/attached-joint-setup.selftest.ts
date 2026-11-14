import {createSourceAttachedJointSetupRuntime, type SourceAttachedJointSetupBinding} from './attached-joint-setup.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceAnimationRequestRuntime} from './animation-request.js';
import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime} from './mobj-animation.js';
import {createSourceTObjAnimationRuntime} from './tobj-animation.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import type {SourceFObjHeader} from './fobj-list.js';
import {AOBJ_LOOP, AOBJ_STOPPED, AOBJ_REQUEST, AOBJ_WRAPPED, requestSourceAObj, interpretSourceAObj} from './aobj-clock.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[attached-setup-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let message = ''; try {run();} catch (e) {message = String(e);}
  check(message.includes(expected), `expected ${expected}, got ${message || 'success'}`);
}
const required = [1, 2, 3, 5, 6, 7];
function fixture(tracks = required, maxNodes = 4096) {
  const j = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(j);
  const joint = j.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 9, rotation20: 9, rotation24: 9, scale2c: 1, scale30: 1, scale34: 1,
    translation38: -1, translation3c: -2, translation40: -3},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const f = createSourceFObjScalarCallbackRuntime(joint), data = f.createData(Uint8Array.from([2, 10, 4, 2, 18]));
  const nodes = tracks.map(track => f.createNode({next00: null, cursor04: null, base08: data, length0c: 5,
    flags10: 0, byte11: 3, byte12: 4, track13: track, format14: 0x80, format15: 0x80,
    half16: 5, offset18: 0, half1a: 6, frame1c: 99, value20: 1, value24: 2, value28: 3, value2c: 4}));
  for (let i = 0; i + 1 < nodes.length; i++) f.getNode(nodes[i]!).next00 = nodes[i + 1]!;
  const aobj = feedback.createAObj({flags: AOBJ_STOPPED | AOBJ_LOOP | AOBJ_WRAPPED | 0x80,
    frame: 99, rewind: -2, end: 9, rate: 1, fobjs: nodes[0] ?? null});
  const a = feedback.getAObj(aobj), binding = j.getBinding(joint);
  binding.aobj7c = aobj; binding.classUpdate50 = f.createCallback(j.updateScalar);
  const events: string[] = [];
  const hooks: {binding?: () => void; aobj?: () => void; actor?: () => void; part?: () => void;
    node?: (id: symbol, node: symbol, value: SourceFObjHeader) => void;
    beforeRequest?: () => void; afterRequest?: () => void; beforeAnimate?: () => void; afterAnimate?: () => void;
    interpret?: () => void; robj?: () => void; dobj?: () => void} = {};
  const effects: SourceJObjAnimationEffects = {
    interpretAObj(id, owner, callback) {
      check(this === effects && owner === joint, 'real interpreter keeps original receiver/owner');
      interpretSourceAObj(id === null ? null : feedback.getAObj(id), callback, f.effects, j.endCallbacks.counts);
      events.push('interpret'); return hooks.interpret?.();
    },
    animateRObjs(list) {check(this === effects && list === null, 'fixture only supports source null RObj no-op'); events.push('r'); return hooks.robj?.();},
    animateDObjs(list) {check(this === effects && list === null, 'fixture only supports source null DObj no-op'); events.push('d'); return hooks.dobj?.();},
  };
  const actors = createSourceActorJointMappingRuntime(j, feedback, effects, {
    convertEulerToQuaternion() {throw Error('pose conversion must not be reached by setup tail');},
  });
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => actors.createPart(
    {frame0c: 2, duration24: -7, segment2d: 7, complete2e: 1, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0})));
  const actor = actors.createActor({descriptor4b0: null, jointCount1d90: 0, boundary1d91: 0, boundary1d92: 0,
    boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 3}, {parts, poses: [[], []]});
  const partId = parts[0]![0]!, part = feedback.getPart(partId), actorHeader = actors.getActor(actor);
  const requests = createSourceAnimationRequestRuntime({joints: j, dobjs: createSourceDObjAnimationRuntime(),
    pobjs: createSourcePObjAnimationRuntime(), mobjs: createSourceMObjAnimationRuntime(), tobjs: createSourceTObjAnimationRuntime()}, {
    requestAObj(id, frame) {requestSourceAObj(id === null ? null : feedback.getAObj(id), frame, f.effects); events.push('actual-request');},
  });
  const jointAdapter = {
    getBinding(id: symbol) {check(this === jointAdapter, 'joint getter this'); const value = j.getBinding(id); events.push('binding'); hooks.binding?.(); return value;},
    animateJoint(...args: Parameters<typeof j.animateJoint>) {
      check(this === jointAdapter, 'animate this'); events.push('animate'); hooks.beforeAnimate?.(); j.animateJoint(...args); return hooks.afterAnimate?.();
    },
  };
  const feedbackAdapter = {
    getPart(id: symbol) {check(this === feedbackAdapter, 'part getter this'); const value = feedback.getPart(id); hooks.part?.(); return value;},
    getAObj(id: symbol) {check(this === feedbackAdapter, 'AObj getter this'); const value = feedback.getAObj(id); events.push('aobj'); hooks.aobj?.(); return value;},
  };
  const actorAdapter = {getActor(id: symbol) {check(this === actorAdapter, 'actor getter this'); const value = actors.getActor(id); events.push('actor'); hooks.actor?.(); return value;}};
  const requestAdapter = {requestJoint(...args: Parameters<typeof requests.requestJoint>) {
    check(this === requestAdapter && args[0] === joint && args[2] === 1, 'real request receives owned joint and exact mask1');
    events.push('request'); hooks.beforeRequest?.(); requests.requestJoint(...args); return hooks.afterRequest?.();
  }};
  const fobjAdapter = {getFObj(id: symbol, node: symbol) {
    check(this === fobjAdapter && id === aobj, 'scan retains initial AObj identity/receiver');
    const value = f.getNode(node); events.push(`node${value.track13}`); hooks.node?.(id, node, value); return value;
  }};
  const sources = {joints: jointAdapter, feedback: feedbackAdapter, actors: actorAdapter, requests: requestAdapter, fobjs: fobjAdapter};
  const runtime = createSourceAttachedJointSetupRuntime(sources, effects, maxNodes);
  const setupInput = {rewind26: -12, loop2c: 0}; runtime.bindPart(partId, setupInput);
  const setup = runtime.getPartBinding(partId);
  j.endCallbacks.counts.running = 13; j.endCallbacks.counts.stopped = 17;
  let completed = 0;
  j.endCallbacks.state.head28 = j.endCallbacks.createNode({next00: null,
    callback04: j.endCallbacks.createCallback(() => {completed++;})});
  const run = () => runtime.continueAttachedSetupTail(actor, partId, joint);
  return {j, feedback, actors, actor, actorHeader, partId, part, aobj, a, binding, f, data, nodes, joint,
    effects, hooks, events, runtime, setup, setupInput, sources, jointAdapter, feedbackAdapter, actorAdapter, requestAdapter, fobjAdapter,
    run, get completed() {return completed;}};
}
export function runAttachedJointSetupSelfTest(): void {
  for (const loop of [0, 2, 255]) {
    const x = fixture(); x.setup.loop2c = loop; x.setup.rewind26 = NaN; Object.defineProperty(x.setup, 'rewind26', {writable: false});
    for (const key of ['complete2e', 'mode2f', 'mirror30'] as const) {x.part[key] = NaN; Object.defineProperty(x.part, key, {writable: false});}
    x.part.duration24 = NaN; x.run();
    check(x.part.duration24 === 9 && x.part.segment2d === 0 && x.part.frame0c === 2 && Number.isNaN(x.part.complete2e),
      'non-loop raw byte preserves shared frame/other part fields, overwrites duration and clears segment');
    check(x.a.frame === 2 && x.a.rate === 3 && x.a.rewind === -2 && x.a.flags === 0x80 && x.j.getJoint(x.joint).translation38 === 14 &&
      x.f.getNode(x.nodes[0]!).frame1c === 2 && x.f.getNode(x.nodes[0]!).half16 === 0,
    `real request resets FObj and actual packed interpolation updates joint without request-frame advance: ${JSON.stringify(x.a)}, ${JSON.stringify(x.f.getNode(x.nodes[0]!))}, ${x.j.getJoint(x.joint).translation38}`);
    check(x.j.endCallbacks.counts.running === 14 && x.j.endCallbacks.counts.stopped === 17 && x.completed === 0,
      'single real interpretation preserves existing counters and never invokes completion');
    check(x.events.join() === 'binding,aobj,node1,node2,node3,node5,node6,node7,binding,aobj,binding,aobj,request,actual-request,actor,binding,aobj,animate,interpret,r,d',
      'source boundary order and exactly one real request/animation');
  }
  for (let i = 0; i < required.length; i++) {
    const tracks = required.slice(0, i), x = fixture(tracks); x.setup.loop2c = NaN;
    rejects(x.run, `fallback mask 0x${(1 << required[i]!).toString(16)}`);
    check(x.a.flags === (AOBJ_STOPPED | AOBJ_LOOP | AOBJ_WRAPPED | 0x80) && x.part.duration24 === -7 &&
      x.part.segment2d === 7 && !x.events.includes('request'), 'first missing source fallback refuses before writes/loop read');
  }
  for (const track of [32, 33, 63, 255, -1, NaN, .5]) {
    const x = fixture([...required, 0]); const node = x.f.getNode(x.nodes.at(-1)!); node.track13 = track;
    node.next00 = Symbol('invalid next'); Object.defineProperty(node, 'next00', {writable: false});
    rejects(x.run, 'track13'); check(!x.events.includes('request'), 'full mask never ends scan and track is checked before next');
  }
  {
    const x = fixture([...required, 0, 4, 31]); x.setup.loop2c = 1;
    rejects(x.run, 'DOUBLE_804370f8'); check(x.events.filter(e => e.startsWith('node')).length === 9, 'all admitted tracks through31 are scanned');
  }
  for (const loop of [1]) {
    const x = fixture(); x.a.flags &= ~AOBJ_LOOP; x.setup.loop2c = loop; x.a.end = NaN; x.part.frame0c = NaN;
    rejects(x.run, 'DOUBLE_804370f8');
    check(!!(x.a.flags & AOBJ_LOOP) && x.a.rewind === -2 && x.part.duration24 === -7 && x.part.segment2d === 7 &&
      !x.events.includes('request') && !x.events.includes('actor'), 'loop1 sets LOOP then refuses without consuming end/frame or changing rewind');
  }
  for (const rewind of [-32769, 32768, .5, NaN]) {
    const x = fixture(); x.setup.loop2c = 1; x.setup.rewind26 = rewind; x.a.flags &= ~AOBJ_LOOP;
    rejects(x.run, 'rewind26'); check(!!(x.a.flags & AOBJ_LOOP), 'signed rewind validation follows completed flag set');
  }
  {
    const x = fixture(); x.setup.loop2c = 1; x.a.flags &= ~AOBJ_LOOP; Object.defineProperty(x.setup, 'rewind26', {writable: false});
    rejects(x.run, 'rewind26: non-writable'); check(!!(x.a.flags & AOBJ_LOOP), 'rewind writability is lazy after flag set');
  }
  for (const [end, expected] of [[-32768, -32768], [32767, 32767], [-0, 0], [0, 0], [4, 4], [32768, -32768], [65535, -1], [-3.75, -3], [-2147483648, 0], [2147483520, -128]] as const) {
    const x = fixture(); x.a.end = end; x.run();
    check(Object.is(x.part.duration24, expected), 'admitted signed32 truncation/signed-low16 duration conversion including canonical zero');
  }
  for (const end of [2147483648, -2147483904, NaN, Infinity, 1 + 2 ** -25]) {
    const x = fixture(); x.a.end = end; rejects(x.run, Number.isInteger(end) ? 'duration24 conversion' : 'AObj end');
    check(!(x.a.flags & AOBJ_LOOP) && x.part.duration24 === -7 && !x.events.includes('request'), 'bad duration preserves LOOP clear but no duration/request');
  }
  {
    const x = fixture(); Object.defineProperty(x.part, 'duration24', {writable: false}); rejects(x.run, 'duration24: non-writable');
    check(!(x.a.flags & AOBJ_LOOP) && x.part.duration24 === -7, 'readonly duration preserves flag prefix');
  }
  {
    const x = fixture(); Object.defineProperty(x.a, 'end', {writable: false}); rejects(x.run, 'end: non-writable');
    check(!(x.a.flags & AOBJ_LOOP) && x.part.duration24 === -7, 'end field is consumed only after flag clear');
    const y = fixture(); Object.defineProperty(y.a, 'flags', {writable: false}); rejects(y.run, 'non-writable flags');
    check(y.part.duration24 === -7 && !y.events.includes('request'), 'flag write failure precedes duration/request');
    const z = fixture(); z.setup.loop2c = 256; rejects(z.run, 'loop2c');
    check(z.events.filter(e => e.startsWith('node')).length === 6 && !!(z.a.flags & AOBJ_LOOP), 'loop byte checked only after full scan');
  }
  {
    const x = fixture(); x.part.frame0c = NaN; rejects(x.run, 'frame0c');
    check(x.part.duration24 === 9 && !x.events.includes('request'), 'frame checked only after duration store');
  }
  {
    const x = fixture(); x.f.getNode(x.nodes[0]!).frame1c = NaN; rejects(x.run, 'finite source float32');
    check(x.part.duration24 === 9 && x.a.frame === 2 && !!(x.a.flags & AOBJ_REQUEST) && x.a.rate === 1 && x.part.segment2d === 7,
      `real FObj request failure retains duration/AObj request prefix but no rate/segment: ${JSON.stringify(x.a)}, ${x.events.join()}`);
  }
  for (const rate of [NaN, 1 + 2 ** -25]) {
    const x = fixture(); x.actorHeader.timestep1dc8 = rate; rejects(x.run, 'finite source float32');
    check(x.a.frame === 2 && !!(x.a.flags & AOBJ_REQUEST) && x.part.duration24 === 9 && x.a.rate === 1 && !x.events.includes('animate'),
      'rate refuses after completed request before actual animation');
  }
  {
    const x = fixture(); Object.defineProperty(x.a, 'rate', {writable: false});
    // Request itself rejects a frozen AObj, so freeze only after the real request.
    rejects(x.run, 'non-writable rate'); check(x.part.duration24 === 9, 'underlying actual request retains its stricter header checks');
    const y = fixture(); y.hooks.afterRequest = () => {Object.defineProperty(y.a, 'rate', {writable: false});};
    rejects(y.run, 'non-writable rate'); check(y.a.frame === 2 && !y.events.includes('animate'), 'post-request rate refusal prefix');
  }
  {
    const x = fixture(); x.hooks.beforeAnimate = () => {throw Error('animation fault');}; rejects(x.run, 'animation fault');
    check(x.a.rate === 3 && !!(x.a.flags & AOBJ_REQUEST) && x.part.segment2d === 7, 'animation fault keeps request/rate but not segment');
  }
  {
    const x = fixture(); x.hooks.dobj = () => {throw Error('DObj unsupported');}; rejects(x.run, 'DObj unsupported');
    check(x.j.getJoint(x.joint).translation38 === 14 && x.j.endCallbacks.counts.running === 14 && x.part.segment2d === 7,
      'late animation failure preserves actual scalar/count prefix but not final segment');
  }
  {
    const x = fixture(); Object.defineProperty(x.part, 'segment2d', {writable: false}); rejects(x.run, 'segment2d: non-writable');
    check(x.j.getJoint(x.joint).translation38 === 14 && x.events.at(-1) === 'd', 'final write failure retains all animation effects');
  }
  for (const after of ['interpret', 'afterAnimate'] as const) {
    const x = fixture(); x.hooks[after] = () => {x.a.flags |= AOBJ_WRAPPED; x.binding.aobj7c = null;}; x.run();
    check(x.part.segment2d === 0 && !!(x.a.flags & AOBJ_WRAPPED) && x.events.at(-1) === 'd', 'no AObj reload/WRAPPED copy after animation');
  }
  for (const rate of [3, NaN, 1 + 2 ** -25]) {
    const x = fixture(); x.hooks.afterRequest = () => {x.binding.aobj7c = null; x.actorHeader.timestep1dc8 = rate;}; x.run();
    check(x.events.includes('actor') && x.events.includes('animate') && x.a.rate === 1 && x.part.segment2d === 0 &&
      x.j.endCallbacks.counts.running === 13, 'post-request null still loads actor, skips numeric setter admission and actually animates null AObj');
  }
  {
    const x = fixture(); x.hooks.afterRequest = () => {x.binding.aobj7c = null; Object.defineProperty(x.actorHeader, 'timestep1dc8', {writable: false});};
    rejects(x.run, 'timestep1dc8: non-writable'); check(!x.events.includes('animate'), 'null rate target does not bypass actor field access');
  }
  {
    const x = fixture(); const replacement = x.feedback.createAObj({flags: 0, frame: 5, rewind: 0, end: 20, rate: 7, fobjs: null});
    x.hooks.afterRequest = () => {x.binding.aobj7c = replacement; x.actorHeader.timestep1dc8 = 4;}; x.run();
    check(x.a.frame === 2 && x.a.rate === 1 && !!(x.a.flags & AOBJ_REQUEST) && x.feedback.getAObj(replacement).rate === 4 &&
      x.feedback.getAObj(replacement).frame === 9 && x.part.duration24 === 9,
    'post-request reload rates/animates replacement with live actor timestep, without rewriting earlier duration');
  }
  {
    const x = fixture(); const replacement = x.feedback.createAObj({flags: AOBJ_LOOP, frame: 4, rewind: 0, end: 12, rate: 5, fobjs: null});
    let scanned = 0; x.hooks.node = () => {if (++scanned === 1) {x.binding.aobj7c = replacement; x.a.fobjs = null;}}; x.run();
    check(scanned === 6 && x.part.duration24 === 12 && x.a.frame === 99 && !!(x.a.flags & AOBJ_LOOP) &&
      x.feedback.getAObj(replacement).frame === 2 && x.feedback.getAObj(replacement).rate === 3,
    'scan holds initial owner/head while loop/duration/request/rate use live current AObj');
  }
  {
    const x = fixture(); let scanned = 0;
    x.hooks.node = (_id, _node, value) => {if (++scanned === 1) value.next00 = null;};
    rejects(x.run, 'fallback mask 0x4'); check(scanned === 1, 'next link read live after current node resolver');
  }
  {
    const x = fixture(); x.hooks.node = (_id, _node, value) => {value.frame1c = NaN; value.base08 = Symbol('foreign stream');};
    x.setup.loop2c = 1; rejects(x.run, 'DOUBLE_804370f8');
    check(x.events.filter(e => e.startsWith('node')).length === 6, 'scan does not preflight stream/scalar/header state');
  }
  {
    const x = fixture(); x.binding.aobj7c = null; rejects(x.run, 'non-null attached AObj');
    check(x.events.join() === 'binding' && x.part.duration24 === -7, 'initial null refuses before part/scan/effects');
    rejects(() => x.runtime.continueAttachedSetupTail(x.actor, x.partId, null), 'non-null owned joint');
  }
  {
    const x = fixture(); let calls = 0;
    x.hooks.binding = () => {if (++calls === 2) x.binding.aobj7c = null;};
    rejects(x.run, 'non-null AObj required for duration24'); check(!!(x.a.flags & AOBJ_LOOP), 'null flag helper does not alter previous AObj');
    const y = fixture(); y.a.flags &= ~AOBJ_LOOP; y.setup.loop2c = 1; let calls2 = 0;
    y.hooks.binding = () => {if (++calls2 === 2) y.binding.aobj7c = null;};
    rejects(y.run, 'DOUBLE_804370f8'); check(!(y.a.flags & AOBJ_LOOP) && y.part.duration24 === -7,
      'null loop-flag target bypasses set but rewind conversion still refuses');
  }
  {
    const x = fixture(); x.setupInput.loop2c = 1; x.setupInput.rewind26 = 99;
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.setup) && x.setup.loop2c === 0 && x.setup.rewind26 === -12,
      'method table frozen and own setup fields copied, shared part not copied');
    rejects(() => x.runtime.bindPart(x.partId, {rewind26: 0, loop2c: 0}), 'already has');
    rejects(() => x.runtime.bindPart(Symbol('foreign part'), {rewind26: 0, loop2c: 0}), 'non-owned part');
    const bad = Object.defineProperty({loop2c: 0}, 'rewind26', {get() {throw Error('must not invoke getter');}}) as SourceAttachedJointSetupBinding;
    rejects(() => x.runtime.bindPart(Symbol('part'), bad), 'own data property');
  }
  {
    const x = fixture(); const fail = () => {throw Error('replaced method must not run');};
    x.jointAdapter.getBinding = fail; x.jointAdapter.animateJoint = fail; x.feedbackAdapter.getAObj = fail;
    x.actorAdapter.getActor = fail; x.requestAdapter.requestJoint = fail; x.fobjAdapter.getFObj = fail;
    x.effects.interpretAObj = fail; x.effects.animateRObjs = fail; x.effects.animateDObjs = fail; x.run();
    check(x.j.getJoint(x.joint).translation38 === 14, 'methods fixed at construction, retaining all original this receivers');
  }
  for (const hook of ['binding', 'aobj', 'node', 'actor', 'afterRequest', 'afterAnimate', 'interpret', 'robj', 'dobj'] as const) {
    const x = fixture(); let once = true;
    x.hooks[hook] = () => {if (once) {once = false; rejects(x.run, 'reentry');}};
    rejects(x.run, 'reentry');
    if (hook === 'interpret') check(!x.events.includes('r') && x.part.segment2d === 7, 'caught interpreter reentry stops before RObj/segment');
    if (hook === 'robj') check(!x.events.includes('d') && x.part.segment2d === 7, 'caught RObj reentry stops before DObj/segment');
    if (hook === 'node') check(x.events.filter(e => e.startsWith('node')).length === 1, 'caught node getter reentry stops before second getter');
    if (hook === 'binding') check(!x.events.includes('aobj'), 'caught binding getter reentry stops before AObj getter');
    delete x.hooks[hook]; x.run(); check(x.part.segment2d === 0, 'helper recovers after poisoned pass');
  }
  {
    const x = fixture(); const second = x.actors.createPart({frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
      {descriptor00: null, scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0});
    x.hooks.part = () => {rejects(x.run, 'reentry');}; rejects(() => x.runtime.bindPart(second, {rewind26: 0, loop2c: 0}), 'reentry');
    delete x.hooks.part; x.runtime.bindPart(second, {rewind26: 0, loop2c: 0});
    check(x.runtime.getPartBinding(second).loop2c === 0, 'part factory getter poison does not reserve failed identity');
  }
  for (const hook of ['afterRequest', 'afterAnimate', 'interpret', 'robj', 'dobj'] as const) {
    const x = fixture(); x.hooks[hook] = (() => 7) as () => void; rejects(x.run, 'synchronously');
    check(x.part.segment2d === 7, 'nonvoid actual effect wrapper refuses final segment');
  }
  for (const maxNodes of [0, -1, NaN, 1.5, Infinity]) {
    const x = fixture(); rejects(() => createSourceAttachedJointSetupRuntime(x.sources, x.effects, maxNodes), 'maxNodes');
  }
  {
    const x = fixture(required, 5); rejects(x.run, 'budget');
    check(x.events.filter(e => e.startsWith('node')).length === 5 && !x.events.includes('request'), 'budget stops before next external getter');
  }
  for (const length of [4096, 4097, 12001]) {
    const x = fixture([...required, ...Array<number>(length - required.length).fill(0)], length === 12001 ? 12001 : undefined);
    x.setup.loop2c = 1; rejects(x.run, length === 4097 ? 'budget' : 'DOUBLE_804370f8');
    check(x.events.filter(e => e.startsWith('node')).length === Math.min(length, length === 12001 ? 12001 : 4096),
      'default4096 and explicit long-list budgets bound a complete real-node scan');
  }
  {
    const x = fixture(); x.f.getNode(x.nodes.at(-1)!).next00 = x.nodes[0]!;
    let visits = 0; x.hooks.node = () => {check(++visits <= 7, 'cycle guard must bound resolver calls even in mutation control');};
    rejects(x.run, 'cycle'); check(visits === 6 && !x.events.includes('request'), 'cycle after complete mask still refuses without looping');
  }
  console.log('[attached-setup-test] PASS: bounded attached-AObj tail with real request/animation, lazy prefixes, nulls and reentry (not full setup/loop support)');
}
