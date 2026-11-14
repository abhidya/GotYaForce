import {createSourceJointAnimationFeedbackRuntime, type SourceJointAnimationPart,
  type SourceJointPoseEffects} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {AOBJ_LOOP, AOBJ_STOPPED, AOBJ_WRAPPED, interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[joint-feedback-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
const partInitial = (patch: Partial<SourceJointAnimationPart> = {}): SourceJointAnimationPart =>
  ({frame0c: 123, duration24: 3, segment2d: 9, complete2e: 0, mode2f: 0, mirror30: 0, ...patch});
const poseInitial = () => ({translation: {x: -1, y: -2, z: -3}, quaternion: {x: 4, y: 5, z: 6, w: 7}});
// Explicit synthetic zero-angle backend. It computes the analytic zero-Euler
// quaternion and refuses every nonzero angle. It is not a source trig backend,
// not installed by the runtime, and not evidence for general quaternion parity.
const zeroEuler: SourceJointPoseEffects = {convertEulerToQuaternion(rotation, output) {
  check(Object.isFrozen(rotation), 'rotation snapshot is immutable');
  if (![rotation.x, rotation.y, rotation.z].every(v => Object.is(v, 0))) throw Error('fixture supports positive zero Euler only');
  output.w = 1; output.x = 0; output.y = 0; output.z = 0;
}};
function fixture(patch: Partial<SourceJointAnimationPart> = {}) {
  const j = createSourceJObjAnimationRuntime(), r = createSourceJointAnimationFeedbackRuntime(j);
  const joint = j.createJoint({sibling08: null, child10: null, flags14: 0, rotation1c: 0, rotation20: 0, rotation24: 0,
    scale2c: 1, scale30: 1, scale34: 1, translation38: 0, translation3c: 2, translation40: 3},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const f = createSourceFObjScalarCallbackRuntime(joint), data = f.createData(Uint8Array.from([2, 10, 4, 2, 18]));
  const node = f.createNode({next00: null, cursor04: data, base08: data, length0c: 5, flags10: 1,
    byte11: 0, byte12: 0, track13: 5, format14: 0x80, format15: 0x80,
    half16: 0, offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0});
  const aobj = r.createAObj({flags: 0, frame: 0, rewind: 0, end: 3, rate: 1, fobjs: node});
  const a = r.getAObj(aobj), binding = j.getBinding(joint); binding.aobj7c = aobj; binding.classUpdate50 = f.createCallback(j.updateScalar);
  const part = r.createPart(partInitial(patch)), state = r.getPart(part), pose = r.createPose(poseInitial()), output = r.getPose(pose);
  const events: string[] = [];
  const effects: SourceJObjAnimationEffects = {
    interpretAObj(id, owner, callback) {check(owner === joint, 'real interpreter gets exact joint owner');
      interpretSourceAObj(id === null ? null : r.getAObj(id), callback, f.effects, j.endCallbacks.counts); events.push('a');},
    animateRObjs(list) {if (list !== null) throw Error('unsupported RObj'); events.push('r');},
    animateDObjs(list) {if (list !== null) throw Error('unsupported DObj'); events.push('d');},
  };
  const advance = (dt: number, flags = 2) => r.advanceExistingJoint(part, joint, dt, flags, effects);
  const capture = (e = zeroEuler) => r.capturePoseAndFrame(part, joint, pose, e);
  requestSourceAObj(a, 0, f.effects);
  return {j, r, joint, f, node, aobj, a, binding, part, state, pose, output, events, effects, advance, capture};
}
export function runJointAnimationFeedbackSelfTest(): void {
  {
    const x = fixture(); let endCalls = 0;
    x.j.endCallbacks.counts.running = 5; x.j.endCallbacks.counts.stopped = 6;
    x.j.endCallbacks.state.head28 = x.j.endCallbacks.createNode({next00: null,
      callback04: x.j.endCallbacks.createCallback(() => {endCalls++;})});
    x.advance(2); check(x.state.frame0c === 123 && x.state.segment2d === 0 && x.a.rate === 2, 'continuation writes segment, not part frame');
    x.capture(); check(x.state.frame0c === 0 && x.state.complete2e === 0 && x.output.translation.x === 10,
      'request suppresses first actual AObj advance; pose and frame come from actual callbacks');
    x.advance(2); x.capture(); check(x.state.frame0c === 2 && x.output.translation.x === 14 && x.state.complete2e === 0, 'normal real advance');
    x.advance(2); x.capture(); check(x.state.frame0c === 4 && x.output.translation.x === 18 && x.state.complete2e === 1,
      'non-loop overshoot remains unclamped and latches part completion');
    check(x.j.endCallbacks.counts.running === 7 && x.j.endCallbacks.counts.stopped === 7 && endCalls === 0,
      'one JObjAnim per continuation, no global counter reset or callback invocation');
    check(x.events.join() === 'a,r,d,a,r,d,a,r,d' && x.output.translation.y === 2 && x.output.translation.z === 3 &&
      x.output.quaternion.x === 0 && x.output.quaternion.y === 0 && x.output.quaternion.z === 0 && x.output.quaternion.w === 1,
    'complete source single-joint effects and actual pose output, not an event-only fixture');
  }
  {
    const x = fixture({duration24: 39}); x.a.end = 39; requestSourceAObj(x.a, 38, x.f.effects);
    x.advance(2); x.capture(); x.advance(2); x.capture();
    check(x.state.frame0c === 40 && x.state.complete2e === 1 && x.state.duration24 === 39,
      'source-shaped end39/frame38/rate2 reaches frame40 without inventing a clamp');
  }
  {
    const x = fixture({duration24: 30}); x.a.flags |= AOBJ_LOOP; x.a.end = 30; requestSourceAObj(x.a, 28.5, x.f.effects);
    x.advance(1.5); x.capture(); x.advance(1.5); x.capture();
    check(x.a.frame === 0 && x.state.frame0c === 0 && x.state.segment2d === 1 && x.state.complete2e === 0 && x.output.translation.x === 10,
      'actual loop wrap supplies part frame0 and segment1 with real FObj request');
    x.advance(1.5); x.capture(); check(x.state.frame0c === 1.5 && x.state.segment2d === 0, 'subsequent non-wrapping continuation clears segment');
  }
  for (const duration of [-32768, -1, 0, 2, 32767]) {
    const x = fixture({duration24: duration}); x.a.end = 100; x.advance(1); x.capture();
    check(x.state.complete2e === (duration <= 0 ? 1 : 0) && x.state.duration24 === duration,
      'signed initialized duration, not AObj end or counters, drives completion');
  }
  {
    const x = fixture({complete2e: 1, mode2f: 2}); x.state.duration24 = NaN;
    Object.defineProperty(x.state, 'duration24', {writable: false}); x.advance(1); x.capture();
    check(x.state.frame0c === 0 && x.state.complete2e === 1, 'nonzero mode still copies frame and neither reads duration nor clears latch');
  }
  {
    const x = fixture({duration24: 5}); x.a.flags = AOBJ_STOPPED | AOBJ_WRAPPED; x.a.frame = 8;
    x.advance(3); x.capture(); check(x.a.rate === 3 && x.state.frame0c === 8 && x.state.segment2d === 1 && x.state.complete2e === 1,
      'stopped AObj still receives rate and its retained WRAPPED bit is copied');
    const second = x.j.createJoint({...x.j.getJoint(x.joint), translation38: 99},
      {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
    const secondA = x.r.createAObj({flags: AOBJ_STOPPED, frame: 1, rewind: 0, end: 20, rate: 0, fobjs: null});
    x.j.getBinding(second).aobj7c = secondA;
    x.r.advanceExistingJoint(x.part, second, 2, 2, {...x.effects, interpretAObj(id, _owner, callback) {
      interpretSourceAObj(x.r.getAObj(id!), callback, x.f.effects, x.j.endCallbacks.counts);
    }});
    x.r.capturePoseAndFrame(x.part, second, x.pose, zeroEuler);
    check(x.state.frame0c === 1 && x.state.segment2d === 0 && x.state.complete2e === 1 && x.output.translation.x === 99,
      'last processed frame/segment overwrite, while earlier joint completion stays latched');
  }
  {
    const x = fixture(), replacement = x.r.createAObj({flags: AOBJ_WRAPPED, frame: 50, rewind: 0, end: 100, rate: 7, fobjs: null});
    x.r.advanceExistingJoint(x.part, x.joint, 2, 2, {...x.effects, animateDObjs() {x.binding.aobj7c = replacement;}});
    x.capture(); check(x.a.rate === 2 && x.r.getAObj(replacement).rate === 7 && x.state.segment2d === 1 && x.state.frame0c === 50,
      'rate targets pre-call AObj, segment/frame feedback reload replacement after complete JObj effects');
  }
  {
    const x = fixture(); x.binding.aobj7c = null;
    x.r.advanceExistingJoint(Symbol('ignored part'), x.joint, NaN, 2, undefined as unknown as SourceJObjAnimationEffects);
    x.capture(); check(x.state.frame0c === 123 && x.state.segment2d === 9 && x.output.translation.y === 2,
      'null AObj skips continuation but not pose extraction or mandatory conversion');
    x.r.advanceExistingJoint(Symbol('ignored'), null, NaN, 0, undefined as unknown as SourceJObjAnimationEffects);
    for (const flags of [1, 3, 0xffffffff]) rejects(() => x.r.advanceExistingJoint(x.part, x.joint, 5, flags, x.effects), 'setup branch');
    for (const flags of [-1, 1.5, NaN]) rejects(() => x.r.advanceExistingJoint(x.part, x.joint, 5, flags, x.effects), 'operationFlags');
  }
  for (const stage of ['r', 'd']) {
    const x = fixture(), effects = {...x.effects};
    effects[stage === 'r' ? 'animateRObjs' : 'animateDObjs'] = () => {throw Error('required effect refusal');};
    rejects(() => x.r.advanceExistingJoint(x.part, x.joint, 2, 2, effects), 'required effect refusal');
    check(x.a.rate === 2 && x.j.getJoint(x.joint).translation38 === 10 && x.state.segment2d === 9 && x.state.frame0c === 123,
      'RObj/DObj refusal preserves prior rate/AObj/scalar work but precedes segment feedback');
    x.advance(1);
  }
  {
    const x = fixture(); x.advance(1);
    rejects(() => x.capture({convertEulerToQuaternion(_rotation, q) {q.w = 9; throw Error('missing source quaternion backend');}}), 'missing source quaternion backend');
    check(x.state.segment2d === 0 && x.state.frame0c === 123 && x.state.complete2e === 0 && x.output.translation.x === 10 && x.output.quaternion.w === 9,
      'pose refusal preserves earlier continuation, translation and partial quaternion, suppressing frame/completion');
    x.capture();
  }
  for (const result of [1, Promise.resolve()]) {
    const x = fixture(); x.advance(1);
    rejects(() => x.capture({convertEulerToQuaternion() {return result;}} as unknown as SourceJointPoseEffects), 'synchronously');
    check(x.output.translation.x === 10 && x.state.frame0c === 123, 'non-undefined converter return stops before frame write');
  }
  {
    const x = fixture(); x.state.mirror30 = 1;
    rejects(() => x.capture(), 'mirrored pose'); check(x.output.translation.x === -1 && x.state.frame0c === 123, 'unsupported mirror refuses before extraction');
    x.state.mirror30 = 0; let called = false;
    const getter = Object.defineProperty({}, 'convertEulerToQuaternion', {get() {called = true; return () => {};}});
    rejects(() => x.capture(getter as SourceJointPoseEffects), 'own data property'); check(!called, 'converter getter not invoked');
    rejects(() => x.capture(Object.create(zeroEuler) as SourceJointPoseEffects), 'own data property');
  }
  {
    const x = fixture(); Object.defineProperty(x.output.translation, 'y', {writable: false});
    rejects(() => x.capture(), 'y: non-writable');
    check(x.output.translation.x === 0 && x.output.translation.y === -2 && x.output.translation.z === -3 && x.state.frame0c === 123,
      'translation field failure retains only completed store prefix');
  }
  {
    const x = fixture(); Object.defineProperty(x.state, 'segment2d', {writable: false});
    rejects(() => x.advance(2), 'segment2d: non-writable');
    check(x.a.rate === 2 && x.a.frame === 0 && x.j.getJoint(x.joint).translation38 === 10 &&
      x.events.join() === 'a,r,d' && x.state.segment2d === 9 && x.state.frame0c === 123,
    'segment write refusal happens after all actual single-joint effects');
  }
  {
    const x = fixture(); x.advance(1); Object.defineProperty(x.state, 'frame0c', {writable: false});
    rejects(() => x.capture(), 'frame0c: non-writable');
    check(x.output.translation.x === 10 && x.output.quaternion.w === 1 && x.state.frame0c === 123 && x.state.complete2e === 0,
      'frame write refusal retains complete pose but stops before completion');
  }
  {
    const x = fixture(); x.state.mode2f = NaN; x.advance(1);
    rejects(() => x.capture(), 'mode2f'); check(x.state.frame0c === 0 && x.state.complete2e === 0, 'mode refusal happens after frame copy');
  }
  {
    const x = fixture(); x.a.flags = AOBJ_STOPPED; x.a.frame = 10;
    Object.defineProperty(x.state, 'complete2e', {writable: false});
    rejects(() => x.capture(), 'complete2e: non-writable'); check(x.state.frame0c === 10 && x.output.quaternion.w === 1, 'latch write failure retains pose/frame');
  }
  for (const caught of [false, true]) {
    const x = fixture();
    rejects(() => x.r.advanceExistingJoint(x.part, x.joint, 1, 2, {...x.effects, animateRObjs() {
      if (caught) {try {x.capture();} catch { /* outer pass still refuses */ }} else x.capture();
    }}), 'reentry');
    check(x.state.segment2d === 9, 'caught or uncaught reentry prevents final segment'); x.advance(1);
    rejects(() => x.capture({convertEulerToQuaternion() {try {x.advance(1);} catch { /* outer conversion still refuses */ }}}), 'reentry');
    x.capture();
  }
  {
    const x = fixture();
    rejects(() => x.r.advanceExistingJoint(x.part, x.joint, 0.1, 2, x.effects), 'timestep1dc8');
    check(x.a.rate === 1, 'non-source-f32 timestep refuses before rate mutation');
    x.r.advanceExistingJoint(x.part, x.joint, -0, 2, x.effects); check(Object.is(x.a.rate, -0), 'source timestep signed zero preserved');
    rejects(() => x.r.advanceExistingJoint(x.part, x.joint, 1, 2, {...x.effects, animateDObjs() {x.binding.aobj7c = null;}}), 'became null');
    check(x.state.segment2d === 0, 'late null binding failure preserves preceding segment value');
  }
  {
    const x = fixture(); x.state.segment2d = NaN; x.state.frame0c = NaN; x.state.complete2e = NaN;
    x.state.duration24 = -1; x.advance(1); x.capture();
    check(x.state.segment2d === 0 && x.state.frame0c === 0 && x.state.complete2e === 1,
      'stores overwrite invalid old segment/frame/latch values without reading them');
    x.a.rate = NaN; Object.defineProperty(x.a, 'rate', {writable: false});
    x.a.flags = NaN; Object.defineProperty(x.a, 'flags', {writable: false});
    x.capture(); check(x.state.frame0c === 0, 'pose/frame extraction ignores unrelated AObj flags and rate');
  }
  {
    const x = fixture(); x.j.getJoint(x.joint).translation3c = NaN;
    rejects(() => x.capture(), 'translation3c');
    check(x.output.translation.x === -1 && x.output.translation.y === -2,
      'source y is sampled before the first x store');
  }
  {
    const x = fixture(); x.a.frame = NaN;
    rejects(() => x.capture(), 'frame: expected');
    check(x.output.translation.y === 2 && x.output.quaternion.w === 1 && x.state.frame0c === 123,
      'AObj frame validation follows pose conversion, not a preflight');
  }
  {
    const x = fixture(); x.j.getJoint(x.joint).rotation20 = 1;
    rejects(() => x.capture(), 'fixture supports positive zero');
    check(x.output.translation.y === 2 && x.output.quaternion.w === 7 && x.state.frame0c === 123,
      'explicit analytic test backend refuses nonzero Euler instead of claiming a general conversion');
  }
  {
    const x = fixture();
    const poseEffects: SourceJointPoseEffects = {convertEulerToQuaternion(rotation, output) {
      check(this === poseEffects, 'converter retains its original effect-table receiver');
      zeroEuler.convertEulerToQuaternion(rotation, output);
    }};
    x.capture(poseEffects);
    rejects(() => x.capture({convertEulerToQuaternion(_rotation, output) {output.x = NaN;}}), 'x: expected');
    check(x.state.frame0c === 0 && x.output.translation.y === 2 && Number.isNaN(x.output.quaternion.x),
      'invalid converter result retains its output and stops before feedback');
    x.capture();
    Object.defineProperty(x.output.quaternion, 'z', {writable: false});
    rejects(() => x.capture({convertEulerToQuaternion() {}}), 'z: non-writable');
  }
  {
    const x = fixture(), bad = partInitial(); let read = false;
    Object.defineProperty(bad, 'frame0c', {get() {read = true; return 0;}});
    rejects(() => x.r.createPart(bad), 'own data property'); check(!read, 'part factory ignores getters');
    rejects(() => x.r.createPart(partInitial({duration24: 32768})), 'duration24');
    rejects(() => x.r.getPart(Symbol('foreign')), 'non-owned part');
    rejects(() => x.r.getPose(Symbol('foreign')), 'non-owned pose');
    rejects(() => x.r.getAObj(Symbol('foreign')), 'non-owned AObj');
    const initial = poseInitial(), id = x.r.createPose(initial); initial.translation.x = 999;
    check(x.r.getPose(id).translation.x === -1 && Object.isFrozen(x.r.getPose(id)), 'pose vectors copied into independent owned records');
    const badA = {flags: 0, frame: 0, rewind: 0, end: 1, rate: 1, fobjs: null};
    Object.defineProperty(badA, 'rate', {get() {read = true; return 1;}});
    rejects(() => x.r.createAObj(badA), 'own data property'); check(!read, 'AObj registry factory does not invoke getters');
  }
  console.log('[joint-feedback] PASS: actual existing-joint continuation, pose stores and part frame/wrap/latch feedback; explicit zero-angle fixture backend, no full actor mode or original replay');
}
