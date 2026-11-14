import {createSourceActorFrameLifecycleRuntime, isSourceActorFrameLifecycleRuntime,
  hasIncompleteSourceActorFrame, type SourceActorFrameRawDistances} from './actor-frame-lifecycle.js';
import {createSourceActorTickPrefixRuntime, claimSourceActorTickFrame} from './actor-tick-prefix.js';
import {createSourceActorAttributeRefreshRuntime, isSourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {createSourceActorStatusTimersRuntime, isSourceActorStatusTimersRuntime} from './actor-status-timers.js';
import {createSourceActorMovementFollowupRuntime, isSourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import {createSourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';
import {createSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {createRomActor} from './actor.js';
import {markIncompleteSourceActorAnimationTransition} from './actor-animation-transition.js';
import type {SourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import type {SourceStreamWaitRuntime} from './stream-wait.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-frame-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
const raw = (targetDistance760 = 12, horizontalDistance764 = 8): SourceActorFrameRawDistances =>
  ({boundary: 'externally-decoded-pre55568-raw', targetDistance760, horizontalDistance764});

/** These fixtures deliberately stop inside55dcc, before any unknown status or
 * animation body. Movement's unused wait/setup adapters supply only real owned
 * read records, never successful stand-ins for source calls. The attached suite
 * separately composes every genuine child through59068 and the4bc refusal. */
function fixture(bind = true) {
  const unsupported = (): never => {throw Error('unexpected unreached source operation');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const mapping = createSourceActorJointMappingRuntime(joints, feedback,
    {interpretAObj: unsupported, animateRObjs: unsupported, animateDObjs: unsupported}, {convertEulerToQuaternion: unsupported});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 0, jointBank33: 0, poseBuffer35: 0})));
  const descriptor = mapping.createDescriptor([]);
  const id = mapping.createActor({descriptor4b0: descriptor, jointCount1d90: 0, boundary1d91: 0, boundary1d92: 0,
    boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses: [[], []]});
  const dispatch = createSourceActorAnimationDispatchRuntime(mapping, feedback);
  dispatch.bindActor(id, {family1d88: null, shared1d8c: null, marker578: 9, marker1db3: 0});
  const matrices = createSourceActorJointMatrixRuntime(feedback);
  const make = () => matrices.createMatrix([1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0]);
  const actual = Object.assign(createRomActor(), {collisionScale: 2, hoverOffset668: 99});
  actual.modelScale = 2;
  const world = createSourceActorWorldMatrixRuntime({mapping, feedback, matrices});
  world.bindActor(id, actual, {mode4a0: 0, mode4a1: 0, flags48a: 0, mask1d70: 0, roll74: 0, yawOffset6b8: 0,
    scale58: {x: 1, y: 1, z: 1}, offset1dbc: {x: 0, y: 0, z: 0}, adjusted1d54: {x: 0, y: 0, z: 0},
    preRotation1d64: {x: 0, y: 0, z: 0}}, {matrices8d4: [], copy114: make(), copy1aa4: make(), scratch: make(),
    topology1994: [], corrections18d4: [], scales15d4: []});
  const waitRecord = {activeMask579: 0, blockedMask1d9a: 0, marker71d: 0};
  const setupRecord = {familyBank1d78: null, sharedBank1d7c: null, movement6d8: 1};
  const waits: Pick<SourceStreamWaitRuntime, 'getActorBinding'> = {getActorBinding: () => waitRecord};
  const setup: Pick<SourceActorAnimationSetupRuntime, 'getActorBinding'> = {getActorBinding: () => setupRecord};
  const movement = createSourceActorMovementFollowupRuntime({mapping, waits, setup});
  movement.bindActor(id, actual, {byte661: 0, field66c: 0, field670: 0});
  const attributes = createSourceActorAttributeRefreshRuntime({world, mapping, movement});
  attributes.bindActor(id, {byte87: 7}); attributes.bindDescriptor(descriptor, {});
  const start = {familyBank1d80: null, sharedBank1d84: null, defaultSelector582: 0, marker709: 0};
  const borg = {hp: 100, hitDrainFrames: 0, balanceGauge: 10, balanceGaugeMax: 10,
    balanceRefillDelay: 0, downResetDelay: 0, comboWindow: 0, comboAccum: 0, comboRank: 0,
    invincTimer: 0, sourceAmmoRefillPauseMask: 0, downGaugeBase: 100, downGauge: 0,
    paramTier: {tier: 0, deltaAccum: 0, timerFrames: 0}};
  const status = createSourceActorStatusTimersRuntime({world, mapping, movement, attributes,
    streams: {getStartActorBinding: () => start}});
  const slot = () => ({cell: {cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0}, mirror776: 0});
  status.bindActor(id, borg, {}, [slot(), slot(), slot()]);
  const gauges = createSourceActorGaugeScaleRuntime({world, status});
  gauges.bindActor(id, borg, {short7d6: 0, short7dc: 0, targetScaleB8: 2, byte7c9: 0, fieldC4: 2});
  const tick = createSourceActorTickPrefixRuntime({world, gauges}); tick.bindActor(id, borg, {byte598: 17});
  const sources = {attributes, status, tick, dispatch}, frame = createSourceActorFrameLifecycleRuntime(sources);
  if (bind) frame.bindActor(id);
  return {id, actual, borg, world, mapping, movement, attributes, status, tick, dispatch, frame, sources,
    marker: () => dispatch.getActorBinding(id), attribute: () => attributes.getActorBinding(id),
    run: (epoch = 0, input = raw()) => frame.ingestRawDistancesAndRun(id, epoch, input)};
}
export function runActorFrameLifecycleSelfTests(): void {
  {
    const x = fixture();
    check(isSourceActorFrameLifecycleRuntime(x.frame), 'real frame brand');
    check(!isSourceActorFrameLifecycleRuntime({...x.frame}), 'copied frame cannot forge brand');
    for (const [value, predicate] of [[x.attributes, isSourceActorAttributeRefreshRuntime],
      [x.status, isSourceActorStatusTimersRuntime], [x.movement, isSourceActorMovementFollowupRuntime]] as const) {
      check(predicate(value), 'genuine child brand'); check(!predicate({...value}), 'copied child has no brand');
    }
    equal(x.frame.getActualActor(x.id), x.actual, 'same actual actor');
    equal(x.frame.getDispatchBinding(x.id), x.marker(), 'same578 owner');
    rejects(() => x.run(), 'field4c: own data property');
    equal(x.marker().marker578, 2, 'marker precedes real55dcc'); equal(x.attribute().byte87, 0, 'real55dcc prefix retained');
    equal(x.actual.targetDistance760, 12, 'raw host store precedes55568 but no59068 divide');
    equal(x.actual.horizontalDistance764, 8, 'second raw host store retained');
    equal(x.actual.hoverOffset668, 99, 'no later55dcc write manufactured');
    equal(x.tick.getActorBinding(x.id).byte598, 17, '59068 not reached');
    check(hasIncompleteSourceActorFrame(x.actual), 'begun incomplete frame is tracked');
    rejects(() => x.run(1, raw(99, 98)), 'incomplete source frame');
    equal(x.actual.targetDistance760, 12, 'retry refused before raw overwrite');
    rejects(() => x.tick.ingestRawDistancesAndRun(x.id, 1, {boundary: 'externally-decoded-pre59068-raw', targetDistance760: 1, horizontalDistance764: 1}), 'exclusively owned');
  }
  {
    const x = fixture();
    rejects(() => x.run(0, x.marker() as unknown as SourceActorFrameRawDistances), 'must not alias');
    rejects(() => x.run(0), 'epoch already consumed');
    equal(x.marker().marker578, 9, 'alias refusal precedes source'); check(!hasIncompleteSourceActorFrame(x.actual), 'no source frame began');
    rejects(() => x.run(1), 'field4c: own data property');
  }
  {
    const x = fixture();
    const wrong = {...raw(), boundary: 'externally-decoded-pre59068-raw'} as unknown as SourceActorFrameRawDistances;
    rejects(() => x.run(0, wrong), 'pre55568 raw boundary required');
    rejects(() => x.run(0), 'epoch already consumed');
    equal(x.marker().marker578, 9, 'wrong boundary has no source writes');
    rejects(() => x.run(1), 'field4c: own data property');
  }
  {
    const x = fixture(); Object.defineProperty(x.marker(), 'marker578', {writable: false});
    rejects(() => x.run(), 'non-writable'); check(hasIncompleteSourceActorFrame(x.actual), 'source attempt is permanently incomplete before marker store');
    equal(x.attribute().byte87, 7, 'readonly marker prevents55dcc');
  }
  {
    const x = fixture(false);
    const owners = {actual: x.actual, borg: x.borg, world: x.world.getActorBinding(x.id),
      status: x.status.getActorBinding(x.id), mapping: x.mapping.getActor(x.id)};
    rejects(() => claimSourceActorTickFrame(x.frame, x.tick, x.id, owners), 'active genuine frame binding');
    x.frame.bindActor(x.id);
    rejects(() => claimSourceActorTickFrame(x.frame, x.tick, x.id, owners), 'active genuine frame binding');
    rejects(() => x.tick.ingestRawDistancesAndRun(x.id, 0, {boundary: 'externally-decoded-pre59068-raw', targetDistance760: 1, horizontalDistance764: 1}), 'exclusively owned');
  }
  {
    const x = fixture(false); x.actual.preState = () => {throw Error('legacy callback must not run');};
    rejects(() => x.frame.bindActor(x.id), 'legacy callable preState');
    // Failed frame admission does not claim the already genuine standalone tick.
    rejects(() => x.tick.ingestRawDistancesAndRun(x.id, 0, {boundary: 'externally-decoded-pre59068-raw', targetDistance760: 12, horizontalDistance764: 8}), '80059e58');
    equal(x.actual.targetDistance760, 6, 'standalone59068 remains usable after failed bind');
  }
  {
    const x = fixture(false);
    for (const key of ['attributes', 'status', 'tick', 'dispatch'] as const) {
      rejects(() => createSourceActorFrameLifecycleRuntime({...x.sources, [key]: {...x.sources[key]}}), 'genuine');
    }
  }
  {
    const x = fixture();
    markIncompleteSourceActorAnimationTransition(x.mapping.getActor(x.id));
    rejects(() => x.run(), 'incomplete mode1 operation');
    equal(x.marker().marker578, 9, 'mode1 incomplete refuses before55568 source writes');
    check(!Object.hasOwn(x.actual, 'targetDistance760'), 'mode1 incomplete refuses before raw ingress');
    rejects(() => x.run(), 'epoch already consumed');
  }
  console.log('[actor-frame-test] genuine frame admission, explicit pre55568 ingress, partial prefixes and permanent refusal passed');
}
