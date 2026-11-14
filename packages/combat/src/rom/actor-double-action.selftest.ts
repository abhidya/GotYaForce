import {createSourceActorGroundProbeRuntime, isSourceActorGroundProbeRuntime} from './actor-ground-probe.js';
import {createSourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';
import {createSourceActorTerrainQueryRuntime, type SourceActorTerrainGlobals} from './actor-terrain-query.js';
import type {SourceActorTransformHistoryBinding} from './actor-transform-history.js';
import {createSourceActorDoubleActionRuntime, isSourceActorDoubleActionRuntime,
  bindSourceActorDoubleActionFrame, type SourceActorDoubleActionTables, type SourceActorDoubleStateSelectors} from './actor-double-action.js';
import {createSourceActorDoublePrehookRuntime, hasIncompleteSourceActorDoubleLifecycle, claimSourceActorDoubleFrame, isSourceActorDoubleFrameAccess} from './actor-double-prehook.js';
import {createSourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {createSourceActorStatusTimersRuntime} from './actor-status-timers.js';
import {createSourceActorInputChargeRuntime} from './actor-input-charge.js';
import {createSourceActorCueResetRuntime} from './actor-cue-reset.js';
import {createSourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import {createSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {createSourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';
import {createRomActor} from './actor.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[double-action-test] ${why}`);}
function equal(a: unknown, b: unknown, why: string): void {check(Object.is(a, b), `${why}: got ${String(a)}, expected ${String(b)}`);}
function rejects(run: () => unknown, text: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(text), `expected ${text}, got ${error || 'success'}`);
}
/** Genuine upper owners. Unreached lower setup adapters expose owned records only;
 * all executable unimplemented adapters throw, never synthesize source success. */
function fixture(bind = true, profile = true, withGround = false) {
  const unsupported = (): never => {throw Error('unexpected unrelated source operation');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const mapping = createSourceActorJointMappingRuntime(joints, feedback,
    {interpretAObj: unsupported, animateRObjs: unsupported, animateDObjs: unsupported}, {convertEulerToQuaternion: unsupported});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 0, jointBank33: 0, poseBuffer35: 0})));
  const descriptor = mapping.createDescriptor([]);
  const id = mapping.createActor({descriptor4b0: descriptor, jointCount1d90: 0, boundary1d91: 0, boundary1d92: 0,
    boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses: [[], []]});
  const animation = createSourceActorAnimationDispatchRuntime(mapping, feedback);
  animation.bindActor(id, {family1d88: null, shared1d8c: null, marker578: 2, marker1db3: 0});
  const targets = createSourceStreamWaitTargetRuntime(mapping, feedback, animation);
  targets.bindActor(id, Array.from({length: 4}, () => ({target08: 0, previous0c: 0, accumulator10: 0})));
  const streams = createSourceStreamWaitRuntime({mapping, feedback, dispatch: animation, targets});
  streams.bindActor(id, {activeMask579: 0, blockedMask1d9a: 0, marker71d: 0},
    Array.from({length: 4}, () => ({current00: null, wait14: 0, finished1a: 0, event1e: 0})));
  streams.bindStartActor(id, {familyBank1d80: null, sharedBank1d84: null, defaultSelector582: 0, marker709: 0});
  const hooks: {read?: (key: string) => void; store?: (key: string) => void; table?: (key: string) => void} = {};
  const raw = createRomActor();
  // Explicit source fixture admission removes the three competing legacy owners;
  // production never silently migrates them. Genuine cue-reset enforces absence.
  for (const key of ['fbPhaseSlots','shotByte1db3','animState']) delete (raw as unknown as Record<string, unknown>)[key];
  Object.assign(raw, {ubState: 0, fbState: 61, actionIndex: 2, variantIndex: 0, fbPhase: 0,
    heading: 0x1234, activeYaw: 1, turnErrorYaw: 2, lockYaw: 3, hSpeed: 7, yVel: 8, hDecel: 9, gravityCoeff: 10,
    poseAccum80: 5, poseAccum7e: 6, poseAccum7c: 7, accumulator80c: 73,
    pos: {x: 3, y: 5, z: 7}, motion: {x: 91, y: 92, z: 93}, targetCache5e8: {x: 1, y: 2, z: 3}});
  const actual = new Proxy(raw, {
    getOwnPropertyDescriptor(t, key) {if (typeof key === 'string') hooks.read?.(key); return Reflect.getOwnPropertyDescriptor(t, key);},
    set(t, key, value) {const result = Reflect.set(t, key, value); if (typeof key === 'string') hooks.store?.(key); return result;},
  });
  const matrices = createSourceActorJointMatrixRuntime(feedback), make = () => matrices.createMatrix([1,0,0,0,0,1,0,0,0,0,1,0]);
  const world = createSourceActorWorldMatrixRuntime({mapping, feedback, matrices});
  world.bindActor(id, actual, {mode4a0: 0, mode4a1: 0, flags48a: 0, mask1d70: 0, roll74: 0, yawOffset6b8: 0,
    scale58: {x:1,y:1,z:1}, offset1dbc: {x:0,y:0,z:0}, adjusted1d54: {x:0,y:0,z:0}, preRotation1d64: {x:0,y:0,z:0}},
    {matrices8d4: [], copy114: make(), copy1aa4: make(), scratch: make(), topology1994: [], corrections18d4: [], scales15d4: []});
  const setupState = {familyBank1d78: null, sharedBank1d7c: null, movement6d8: 1};
  const movement = createSourceActorMovementFollowupRuntime({mapping, waits: streams, setup: {getActorBinding: () => setupState}});
  movement.bindActor(id, actual, {byte661: 0, field66c: 0, field670: 0});
  const attributes = createSourceActorAttributeRefreshRuntime({world, mapping, movement});
  const parameter = attributes.createParameterDescriptor({fieldAe: 0x800});
  attributes.bindActor(id, {parameter4ac: parameter});
  const status = createSourceActorStatusTimersRuntime({world, mapping, movement, attributes, streams});
  const borg = {downGauge: 0, downGaugeBase: 0, paramTier: {tier: 0, deltaAccum: 0, timerFrames: 0}, hp: 1, hitDrainFrames: 0, balanceGauge: 1, balanceGaugeMax: 1, balanceRefillDelay: 0,
    downResetDelay: 0, comboWindow: 0, comboAccum: 0, comboRank: 0, invincTimer: 0, sourceAmmoRefillPauseMask: 0};
  const slot = () => ({cell: {cur:0,max:0,refillType:0,refillParam:0,timer:0}});
  status.bindActor(id, borg, {}, [slot(),slot(),slot()]);
  const charge = createSourceActorInputChargeRuntime({world, mapping, status, attributes, global: {byte1829: 0}, data: {}});
  charge.bindActor(id, {});
  const prehook = createSourceActorDoublePrehookRuntime({status, charge, streams});
  prehook.bindActor(id, {pointer4b4: 0x8006facc, pointer4bc: 0x8006f7c0, pointer4c0: 0x8006f88c});
  const cues = createSourceActorCueResetRuntime({world, dispatch: animation}); cues.bindActor(id, {byte541: 0, byte544: 44, byte545: 45, byte546: 46, byte547: 47});
  const upper = [0x8005f238], full: number[] = [], actions: number[] = [], variants = [0x800715d4], phases = [0x800ff30c];
  full[61] = 0x80065dfc; actions[2] = 0x80071598;
  const tables: SourceActorDoubleActionTables = {upper37a8: new Proxy(upper, {
    getOwnPropertyDescriptor(t, key) {if (typeof key === 'string' && /^\d+$/.test(key)) hooks.table?.(key); return Reflect.getOwnPropertyDescriptor(t, key);},
  }), full36a8: full, actions3b68: actions, variants3c48: variants, phases1f000: phases};
  // The7c9 skip must not read any terrain scalar or missing hover input.
  // Empty owner records here intentionally cannot support a successful query.
  const historyOwner = {} as SourceActorTransformHistoryBinding;
  const terrain = createSourceActorTerrainQueryRuntime({world, history: {getActorBinding: () => historyOwner},
    terrain: {} as SourceActorTerrainGlobals});
  terrain.bindActor(id);
  const gauges = createSourceActorGaugeScaleRuntime({world, status});
  gauges.bindActor(id, borg, {byte7c9: 1});
  const ground = createSourceActorGroundProbeRuntime({gauges, terrain}); ground.bindActor(id);
  const processor = {gqr0: 0}, sources = {prehook, attributes, cues, tables, ...(profile ? {processor} : {}),
    ...(withGround ? {ground} : {})};
  const action = createSourceActorDoubleActionRuntime(sources);
  if (bind) action.bindActor(id);
  const capture = () => action.captureStateSelectors(id);
  const run = () => {const saved = capture(); action.dispatchUpper(id, saved); action.dispatchFull(id, saved);};
  return {id, actual, raw, mapping, attributes, parameter, prehook, cues, animation, tables, upper, full, actions, variants, phases,
    action, sources, processor, hooks, capture, run, ground, gauges, terrain, streams, movement, setupState, parameterState: attributes.getParameterDescriptor(parameter)};
}
/** Explicit offline action-level phase1 entry, not a demonstrated second55568
 * frame. Ordinary nonzero motion is retained, no input/control/pose bypasses. */
function phaseOneFixture(withGround = true, profile = true) {
  const x = fixture(true, profile, withGround);
  x.streams.bindActualActor(x.id, x.movement);
  x.actual.fbPhase = 1; x.phases[1] = 0x800ff418;
  x.streams.getPartBinding(x.id, 0).state1b = 0;
  return x;
}
function countdown(x: ReturnType<typeof phaseOneFixture>, wait = 2): void {
  x.streams.getActorBinding(x.id).activeMask579 = 15;
  const command = x.streams.createCommand({flags01: 9});
  for (let index = 0; index < 4; index++)
    Object.assign(x.streams.getPartBinding(x.id, index), {current00: command, wait14: wait, event1e: 7});
}
function observeDescriptors(run: () => void, observe: (owner: object, key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object, key: PropertyKey) => {
    observe(owner, key); return original(owner, key);
  }) as typeof Object.getOwnPropertyDescriptor;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
export function runActorDoubleActionSelfTests(): void {
  {
    const x = fixture();
    const frame = {} as Parameters<typeof claimSourceActorDoubleFrame>[0];
    const owners = {actual: x.actual} as Parameters<typeof claimSourceActorDoubleFrame>[2];
    const access = {invoke: <T>(_operation: unknown, _runtime: object, run: () => T): T => run()};
    check(!isSourceActorDoubleFrameAccess(access, x.actual), 'structural frame token cannot grant access');
    rejects(() => claimSourceActorDoubleFrame(frame, x.id, owners), 'active genuine frame binding');
    rejects(() => bindSourceActorDoubleActionFrame(frame, x.action, x.id, owners, access), 'private genuine frame binding');
    rejects(x.run, 'actual800677b0');
  }

  {
    const x = fixture(); check(isSourceActorDoubleActionRuntime(x.action), 'genuine action brand');
    check(!isSourceActorDoubleActionRuntime({...x.action}), 'copied methods cannot forge action brand');
    equal(x.action.getActualActor(x.id), x.actual, 'canonical actual'); equal(x.action.getPrehookRuntime(), x.prehook, 'canonical prehook');
    equal(x.action.getPrehookBinding(x.id), x.prehook.getActorBinding(x.id), 'one4b4 owner');
    equal(x.action.getCueBinding(x.id), x.cues.getActorBinding(x.id), 'one541 owner');
    equal(x.action.getAttributeBinding(x.id), x.attributes.getActorBinding(x.id), 'one4ac owner');
    check(x.action.getSourceOwners(x.id).includes(x.parameterState), 'parameter alias excluded before source4ac dereference');
    rejects(x.run, 'actual800677b0');
    equal(x.actual.fbPhase, 1, 'actual540 advances'); equal(x.actual.activeYaw, 0x1234, 'nullCC active yaw copy');
    equal(x.actual.turnErrorYaw, 0, 'real yaw helper clears error'); equal(x.actual.lockYaw, 0x1234, 'real yaw helper writes lock');
    for (const key of ['hSpeed','yVel','hDecel','gravityCoeff','poseAccum80','poseAccum7e','poseAccum7c'] as const) equal(x.actual[key], 0, key);
    for (const [axis, original, delta] of [['x',3,2],['y',5,3],['z',7,4]] as const) {
      equal(x.actual.motion[axis], Math.fround(delta * Math.fround(.95)), `scaled ${axis}`);
      equal(x.actual.pos[axis], Math.fround(original + x.actual.motion[axis]), `carried ${axis}`);
    }
    equal(x.actual.accumulator80c, 73, 'ground refusal precedes80c');
    for (const [key, value] of [['byte544',44],['byte545',45],['byte546',46],['byte547',47]] as const)
      equal(x.cues.getActorBinding(x.id)[key], value, 'canonical544..547 untouched');
    equal(x.animation.getActorBinding(x.id).marker578, 2, 'action does not own frame marker');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual), 'partial action latches shared lifecycle');
    x.actual.fbPhase = 0; x.actual.fbState = 0;
    rejects(x.capture, 'incomplete'); rejects(() => x.prehook.runActor(x.id), 'incomplete');
    check(x.action.getSourceOwners(x.id).includes(x.parameterState), 'reached parameter owner exposed');
  }
  {
    const x = fixture(), stores: string[] = [];
    x.hooks.store = key => stores.push(key); rejects(x.run, 'actual800677b0');
    equal(stores.join(','), 'fbPhase,activeYaw,turnErrorYaw,turnErrorYaw,lockYaw,heading,gravityCoeff,yVel,hDecel,hSpeed,poseAccum80,poseAccum7e,poseAccum7c', 'actual scalar store order');
    const y = fixture(); let yawWrites = 0;
    y.hooks.store = key => {if (key === 'turnErrorYaw' && ++yawWrites === 2) y.raw.heading = 0x5555;};
    rejects(y.run, 'actual800677b0'); equal(y.actual.heading, 0x1234, '66a30 preserves heading captured before5aa store');
    const z = fixture(); let headingReads = 0, activeReads = 0;
    z.hooks.read = key => {
      if (key === 'heading') headingReads++;
      if (key === 'activeYaw' && ++activeReads === 2) check(headingReads >= 2, '6d144 loads72 before5ac');
    };
    rejects(z.run, 'actual800677b0'); equal(activeReads, 2, '5ac readonly check then one source load');
  }
  {
    const x = fixture(); const reads: string[] = [];
    x.hooks.read = key => {if (key === 'ubState' || key === 'fbState') reads.push(key);};
    const saved = x.capture(); equal(reads.join(','), 'ubState,fbState', 'captured upper then full once');
    x.actual.ubState = 127; x.actual.fbState = 0;
    x.action.dispatchUpper(x.id, saved); rejects(() => x.action.dispatchFull(x.id, saved), 'actual800677b0');
    equal(reads.join(','), 'ubState,fbState', 'dispatch does not reload live selectors');
  }
  {
    const x = fixture(), saved = x.capture();
    rejects(() => x.action.dispatchFull(x.id, saved), 'out of order');
    rejects(() => x.action.dispatchUpper(x.id, {...saved}), 'capability');
    rejects(x.capture, 'not completed');
    x.action.dispatchUpper(x.id, saved); rejects(() => x.action.dispatchUpper(x.id, saved), 'out of order');
    rejects(() => x.action.dispatchFull(x.id, saved), 'actual800677b0');
  }
  {
    const x = fixture(); x.full[0] = 0x8005f238; x.actual.fbState = 0;
    const first = x.capture(); x.action.dispatchUpper(x.id, first); equal(x.action.dispatchFull(x.id, first), undefined, 'two genuine returns');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual), 'genuine returns do not latch');
    rejects(() => x.action.dispatchFull(x.id, first), 'capability'); equal(x.actual.fbPhase, 0, 'return stub writes nothing');
    const second = x.capture(); x.action.dispatchUpper(x.id, second); x.action.dispatchFull(x.id, second);
  }
  for (const key of ['actionIndex','variantIndex','fbPhase'] as const) {
    const x = fixture(); x.actual[key] = 255; rejects(x.run, 'signed selector -1'); equal(x.actual.hSpeed, 7, 'signed selector no phase effects');
  }
  for (const key of ['ubState','fbState'] as const) {
    const x = fixture(); x.actual[key] = -1; rejects(x.run, 'signed selector -1'); equal(x.actual.fbPhase, 0, 'negative state not silently skipped');
  }
  for (const key of ['prehook','attributes','cues'] as const) {
    const x = fixture(); rejects(() => createSourceActorDoubleActionRuntime({...x.sources, [key]: {...x.sources[key]}}), 'genuine');
  }
  {
    const x = fixture(false); Object.assign(x.raw, {byte541: 0}); rejects(() => x.action.bindActor(x.id), 'competing');
    delete (x.raw as unknown as Record<string, unknown>).byte541; x.action.bindActor(x.id);
    Object.assign(x.raw, {byte540: 0}); rejects(x.capture, 'alias');
  }
  {
    const x = fixture(false); Object.assign(x.raw, {fieldAe: 1}); rejects(() => x.action.bindActor(x.id), 'competing parameter4ac');
    delete (x.raw as unknown as Record<string, unknown>).fieldAe;
    Object.assign(x.raw, {fbPhaseSlots: [0,0,0,0]}); rejects(() => x.action.bindActor(x.id), 'fbPhaseSlots');
  }
  {
    const x = fixture(); x.tables.upper37a8 = x.tables.full36a8; rejects(x.capture, 'owner changed');
    const y = fixture(); y.actual.motion = y.actual.pos; rejects(y.capture, 'owner changed');
  }
  {
    const x = fixture(); x.hooks.table = () => {try {x.capture();} catch { /* outer call must remain poisoned */ }};
    const saved = x.capture(); rejects(() => x.action.dispatchUpper(x.id, saved), 'reentry');
    equal(x.actual.fbPhase, 0, 'caught reentry prevents full handler'); check(hasIncompleteSourceActorDoubleLifecycle(x.actual), 'reentry failure latched');
  }
  {
    const x = fixture(); x.actions[2] = 0x12345678;
    const saved = x.capture(); x.action.dispatchUpper(x.id, saved); rejects(() => x.action.dispatchFull(x.id, saved), 'unsupported target0x12345678');
    equal(x.actual.fbPhase, 0, 'unknown action never executes a substitute');
  }
  {
    const x = fixture(); x.actual.visibilityTarget = {} as NonNullable<typeof x.actual.visibilityTarget>;
    rejects(x.run, 'actual8006660c'); equal(x.actual.fbPhase, 1, 'target helper refusal keeps phase increment');
    equal(x.actual.activeYaw, 1, 'nonnull target does not copy heading'); equal(x.actual.hSpeed, 7, 'target refusal before zeros');
    const y = fixture(); y.actual.visibilityTarget = {} as NonNullable<typeof y.actual.visibilityTarget>;
    y.cues.getActorBinding(y.id).byte541 = 255; rejects(y.run, 'actual800677b0'); equal(y.actual.visibilityTarget, null, '541 clears canonicalCC');
  }
  {
    const x = fixture(); const missing = x.attributes.createParameterDescriptor({});
    x.attributes.getActorBinding(x.id).parameter4ac = missing;
    rejects(x.run, 'fieldAe'); equal(x.actual.fbPhase, 1, 'missing rate keeps phase'); equal(x.actual.activeYaw, 0x1234, 'missing rate keeps5ac');
    equal(x.actual.turnErrorYaw, 0, '6d1445aa store precedes missing669d0 rate'); equal(x.actual.lockYaw, 3, 'missing rate before66a30');
    const y = fixture(); y.parameterState.fieldAe = -2; rejects(y.run, 'actual800677b0');
    equal(y.actual.heading, 0x1232, 'negative rate is not clamped or abs-normalized'); equal(y.actual.turnErrorYaw, 2, 'negative step preserves exact residual');
    const z = fixture(); z.parameterState.fieldAe = 32767; z.mapping.getActor(z.id).timestep1dc8 = 2;
    rejects(z.run, 'actual800677b0'); equal(z.actual.heading, 0x1232, 'signed16 conversion follows fctiwz truncation');
  }
  {
    const x = fixture(); x.mapping.getActor(x.id).timestep1dc8 = NaN; x.parameterState.fieldAe = NaN;
    rejects(x.run, 'timestep1dc8'); equal(x.actual.lockYaw, 3, 'timestep read before rate');
    const y = fixture(); y.parameterState.fieldAe = 32767; y.mapping.getActor(y.id).timestep1dc8 = 2 ** 30;
    rejects(y.run, 'signed32'); equal(y.actual.lockYaw, 3, 'invalid conversion refuses before66a30');
  }
  for (const [key, changed] of [['gravityCoeff',[]],['yVel',['gravityCoeff']],['poseAccum7e',['gravityCoeff','yVel','hDecel','hSpeed','poseAccum80']]] as const) {
    const x = fixture(); Object.defineProperty(x.raw, key, {writable: false}); rejects(x.run, 'non-writable');
    for (const previous of changed) equal(x.raw[previous], 0, `earlier ${previous} retained`);
    equal(x.actual.motion.x, 91, 'readonly scalar before vector call');
  }
  {
    const x = fixture(true, false); rejects(x.run, 'explicit GQR0'); equal(x.actual.hSpeed, 0, 'absent processor after zeroing'); equal(x.actual.motion.x, 91, 'absent processor before vector write');
    const y = fixture(); y.processor.gqr0 = 0x10000; rejects(y.run, 'GQR0'); equal(y.actual.motion.x, 91, 'invalid profile refuses vector');
  }
  {
    const x = fixture(); x.actual.targetCache5e8.z = NaN; rejects(x.run, 'float32');
    equal(x.actual.motion.x, 2, 'subtract XY stored before Z load'); equal(x.actual.motion.y, 3, 'subtract paired Y'); equal(x.actual.motion.z, 93, 'badZ keeps priorZ');
    equal(x.actual.pos.x, 3, 'no carry/add after bad subtract');
    const y = fixture(); Object.defineProperty(y.actual.motion, 'y', {writable: false}); rejects(y.run, 'non-writable');
    equal(y.actual.motion.x, 91, 'pairedXY store refuses both whenY readonly');
  }
  {
    const x = fixture(); x.actual.pos.x = -0; x.actual.targetCache5e8.x = 0;
    rejects(x.run, 'actual800677b0'); check(Object.is(x.actual.motion.x, -0) && Object.is(x.actual.pos.x, -0), 'signed zero survives subtract scale add');
  }
  {
    const x = fixture(); let read = false;
    Object.defineProperty(x.raw, 'actionIndex', {get() {read = true; return 2;}});
    const saved = x.capture(); x.action.dispatchUpper(x.id, saved); rejects(() => x.action.dispatchFull(x.id, saved), 'own data');
    check(!read, 'selector accessor refused without invocation');
  }
  {
    const x = fixture(); const saved = x.capture();
    rejects(() => x.action.dispatchUpper(Symbol('foreign'), saved), 'unknown/non-owned');
    rejects(() => x.action.dispatchUpper(x.id, null as unknown as SourceActorDoubleStateSelectors), 'capability');
  }
  {
    const x = fixture(true, true, true);
    check(isSourceActorGroundProbeRuntime(x.ground), 'genuine ground brand');
    check(!isSourceActorGroundProbeRuntime({...x.ground}), 'copied ground methods cannot forge brand');
    equal(x.prehook.getStreamsRuntime(), x.streams, 'same genuine stream runtime');
    equal(x.action.getGroundRuntime(), x.ground, 'same genuine ground runtime');
    equal(x.ground.getActualActor(x.id), x.actual, 'ground canonical actual');
    equal(x.ground.getGaugeBinding(x.id), x.gauges.getActorBinding(x.id), 'canonical7c9 owner');
    (x.actual as unknown as {hoverOffset668: number}).hoverOffset668 = NaN;
    equal(x.ground.runActor(x.id), 0, '7c9 skips query without reading missing terrain or bad hover');
    x.run();
    equal(x.actual.streamSlot, 1, 'fixed ground configuration0 increments before stream');
    equal(x.actual.accumulator80c, 0, 'null-bank genuine return then accumulator clear');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual), 'completed bounded standalone action is not poisoned');
    for (let i = 0; i < 4; i++) equal(x.streams.getPartBinding(x.id, i).finished1a, 1, 'real null-bank resets all parts');
    check(x.action.getSourceOwners(x.id).includes(x.streams.getPartBinding(x.id, 3)), 'raw aliases include unselected stream parts');
  }
  {
    const x = fixture(true, true, true); x.actual.controlWord = 0x40;
    const stores: number[] = []; x.hooks.store = key => {if (key === 'streamSlot') stores.push(x.raw.streamSlot);};
    x.run(); equal(stores.join(','), '0,1,2', 'ground store then air override then increment');
    equal(x.actual.accumulator80c, 0, 'air stream return clears accumulator');
  }
  {
    const x = fixture(true, true, true); x.actual.controlWord = NaN; x.actual.streamSlot = 99;
    rejects(x.run, 'integer out of bounds'); equal(x.actual.streamSlot, 0, 'configuration store precedes failed fresh control read');
    equal(x.actual.accumulator80c, 73, 'no accumulator store before stream return');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual), 'configuration failure poisons actor');
    rejects(() => x.ground.runActor(x.id), 'incomplete source Double lifecycle');
  }
  {
    const x = fixture(true, true, true); Object.defineProperty(x.raw, 'streamSlot', {writable: false});
    rejects(x.run, 'non-writable'); equal(x.actual.fbPhase, 1, 'readonly slot keeps phase');
    equal(x.actual.accumulator80c, 73, 'readonly slot before final accumulator');
    equal(x.streams.getPartBinding(x.id, 0).finished1a, 0, 'readonly slot before stream reset');
  }
  {
    const x = fixture(true, true, true); Object.defineProperty(x.streams.getPartBinding(x.id, 2), 'finished1a', {writable: false});
    rejects(x.run, 'non-writable'); equal(x.actual.streamSlot, 1, 'stream failure keeps increment');
    equal(x.streams.getPartBinding(x.id, 0).finished1a, 1, 'prior stream part reset retained');
    equal(x.actual.accumulator80c, 73, 'stream failure before accumulator');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual), 'stream failure permanently latches');
  }
  {
    const x = fixture(true, true, true); Object.defineProperty(x.raw, 'accumulator80c', {writable: false});
    rejects(x.run, 'non-writable'); equal(x.actual.streamSlot, 1, 'readonly accumulator keeps slot');
    equal(x.streams.getPartBinding(x.id, 3).finished1a, 1, 'all stream effects precede final accumulator store');
  }
  {
    const x = fixture(); x.gauges.getActorBinding(x.id).byte7c9 = 0; (x.actual as unknown as {hoverOffset668: number}).hoverOffset668 = NaN;
    rejects(() => x.ground.runActor(x.id), 'hoverOffset668');
    (x.actual as unknown as Record<string, unknown>).collisionDisabled7c9 = 1;
    rejects(() => x.ground.runActor(x.id), 'competing source storage alias');
    rejects(() => createSourceActorDoubleActionRuntime({...x.sources, ground: {...x.ground}}), 'genuine source ground');
  }
  {
    const x = phaseOneFixture(); countdown(x);
    let yawStores = 0;
    x.hooks.store = key => {
      if (key !== 'turnErrorYaw') return;
      yawStores++;
      for (let index = 0; index < 4; index++) {
        equal(x.streams.getPartBinding(x.id, index).wait14, 1, 'actual4cd24 mask15 countdown precedes yaw');
        equal(x.streams.getPartBinding(x.id, index).event1e, 0, 'real stream event clear precedes yaw');
      }
    };
    rejects(x.run, 'actual8020bb14 motion magnitude at8020bb38');
    equal(yawStores, 2, 'actual6d144 and66a30 both store yaw error');
    equal(x.actual.activeYaw, 1, 'phase1 never copies heading into active yaw');
    equal(x.actual.heading, 0xa34, 'phase1 real negative yaw step');
    equal(x.actual.fbPhase, 1, 'nonpositive part0 state does not increment phase');
    for (const [axis, position, motion] of [['x',3,91],['y',5,92],['z',7,93]] as const) {
      equal(x.actual.motion[axis], Math.fround(motion * Math.fround(.95)), `existing motion ${axis} decays without subtraction`);
      equal(x.actual.pos[axis], Math.fround(position + x.actual.motion[axis]), `phase1 position ${axis} carries`);
    }
    for (const [key,value] of [['hSpeed',7],['yVel',8],['hDecel',9],['gravityCoeff',10],['poseAccum80',5],['poseAccum7e',6],['poseAccum7c',7],['accumulator80c',73]] as const)
      equal(x.actual[key], value, `phase1 preserves ${key}`);
    equal(x.animation.getActorBinding(x.id).marker578, 2, 'isolated action does not manufacture frame markers');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual), 'reached positive-square numerical boundary permanently poisons actual');
    x.actual.fbPhase = 0; x.actual.fbState = 0; x.streams.getPartBinding(x.id, 0).state1b = 1;
    for (const run of [x.capture, () => x.prehook.runActor(x.id), () => x.ground.runActor(x.id), () => x.streams.update(x.id, 15)])
      rejects(run, 'incomplete');
  }
  for (const wait of [1, 2]) {
    const x = phaseOneFixture(); countdown(x, wait);
    rejects(x.run, 'at8020bb38 frsqrte');
    for (let index = 0; index < 4; index++) {
      equal(x.streams.getPartBinding(x.id, index).finished1a, wait === 1 ? 1 : 0, 'source stream0/1 return ignored');
      equal(x.streams.getPartBinding(x.id, index).wait14, wait - 1, 'real countdown retained through numerical refusal');
    }
  }
  for (const state of [0, 1, 127, 128, 255]) {
    const x = phaseOneFixture(), part = x.streams.getPartBinding(x.id, 0);
    part.state1b = state;
    x.streams.getPartBinding(x.id, 1).state1b = 127;
    x.actual.contactP0 = state > 0 && state < 128 ? 0 : 127;
    x.actual.contactP1 = 127; x.actual.dashStrength1d0f = -128; x.actual.faceGate1d10 = 127;
    const positive = state > 0 && state < 128;
    rejects(x.run, positive ? 'actual800715f8 callback from fixed8043386c after phase increment' : 'at8020bb38 frsqrte');
    equal(x.actual.fbPhase, positive ? 2 : 1, 'signed canonical part0 state alone controls phase increment');
    equal(part.state1b, state, 'state remains raw u8, never sign-normalized in storage');
    equal(x.streams.getPartBinding(x.id, 1).state1b, 127, 'part1 state is retained independently');
    equal(x.actual.motion.x, Math.fround(91 * Math.fround(.95)), 'callback refusal retains scale');
    equal(x.actual.pos.x, Math.fround(3 + x.actual.motion.x), 'callback refusal retains add');
  }
  {
    const x = fixture(true, true, true); x.actual.fbPhase = 1; x.phases[1] = 0x800ff418;
    rejects(x.run, 'actual8004cd24 without genuine stream actual-actor join');
    equal(x.streams.getPartBinding(x.id, 0).finished1a, 0, 'missing actual join precedes stream effects');
    equal(x.actual.turnErrorYaw, 2, 'missing actual join precedes yaw');
    equal(x.actual.motion.x, 91, 'missing actual join precedes vector effects');
    const y = phaseOneFixture(); y.phases[1] = 0x12345678;
    rejects(y.run, '800ff2bc phase: unsupported target0x12345678');
    equal(y.streams.getPartBinding(y.id, 0).finished1a, 0, 'selector1 alone does not authorize phase1');
  }
  {
    const x = phaseOneFixture(false);
    x.streams.getPartBinding(x.id, 0).state1b = undefined;
    rejects(x.run, 'actual800677b0');
    equal(x.actual.motion.x, Math.fround(91 * Math.fround(.95)), 'missing ground preserves stream/yaw/scale/add');
    equal(x.actual.fbPhase, 1, 'ground refuses before missing state load');
    const y = phaseOneFixture(); y.streams.getPartBinding(y.id, 0).state1b = undefined;
    let sawGround = false;
    observeDescriptors(() => rejects(y.run, 'state1b: integer out of bounds'), (owner,key) => {
      if (owner === y.gauges.getActorBinding(y.id) && key === 'byte7c9' && y.actual.pos.x !== 3) sawGround = true;
      if (owner === y.streams.getPartBinding(y.id, 0) && key === 'state1b' && y.actual.pos.x !== 3)
        check(sawGround, 'source signed state read follows actual ground call');
    });
    equal(y.actual.fbPhase, 1, 'uninitialized state cannot use legacy contactP0 zero');
    equal(y.actual.pos.x, Math.fround(3 + y.actual.motion.x), 'missing state after add');
  }
  {
    const x = phaseOneFixture(); countdown(x);
    Object.defineProperty(x.streams.getPartBinding(x.id, 1), 'wait14', {writable:false});
    rejects(x.run, 'wait14: non-writable');
    equal(x.streams.getPartBinding(x.id, 0).wait14, 1, 'earlier stream countdown retained');
    equal(x.streams.getPartBinding(x.id, 1).event1e, 0, 'failed countdown retains current event clear');
    equal(x.streams.getPartBinding(x.id, 2).event1e, 7, 'later parts not run after stream failure');
    equal(x.actual.turnErrorYaw, 2, 'stream failure precedes first yaw store');
    equal(x.actual.motion.x, 91, 'stream failure precedes scale');
    rejects(() => x.streams.update(x.id, 15), 'incomplete');
  }
  {
    const x = phaseOneFixture(); x.actual.visibilityTarget = {} as NonNullable<typeof x.actual.visibilityTarget>;
    rejects(x.run, 'actual8006660c');
    equal(x.streams.getPartBinding(x.id, 3).finished1a, 1, 'nonnull target refusal follows all real null-stream resets');
    equal(x.actual.fbPhase, 1, 'phase1 no early phase increment on target failure');
    equal(x.actual.motion.x, 91, 'target refusal before scale');
    const y = phaseOneFixture(true, false); rejects(y.run, 'reached8020ba9c requires explicit GQR0');
    equal(y.actual.heading, 0xa34, 'missing phase1 profile follows real yaw');
    equal(y.actual.motion.x, 91, 'missing phase1 profile before scale store');
  }
  {
    const x = phaseOneFixture(); x.actual.motion.z = NaN;
    rejects(x.run, 'z: finite exact source float32');
    equal(x.actual.motion.x, 91, 'scale captures XYZ before any XY store');
    equal(x.actual.pos.x, 3, 'bad scaleZ before position add');
    const y = phaseOneFixture(); Object.defineProperty(y.actual.motion, 'y', {writable:false});
    rejects(y.run, 'y: non-writable'); equal(y.actual.motion.x, 91, 'paired scale store checks both XY destinations');
    const z = phaseOneFixture(); Object.defineProperty(z.actual.pos, 'z', {writable:false});
    rejects(z.run, 'z: non-writable');
    equal(z.actual.motion.z, Math.fround(93 * Math.fround(.95)), 'all scale stores precede position add');
    equal(z.actual.pos.x, Math.fround(3 + z.actual.motion.x), 'position XY store retained when positionZ readonly');
    equal(z.actual.pos.z, 7, 'readonly positionZ retains old value');
  }
  {
    const x = phaseOneFixture(); x.streams.getPartBinding(x.id, 0).state1b = 1;
    Object.defineProperty(x.raw, 'fbPhase', {writable:false});
    rejects(x.run, 'fbPhase: non-writable');
    equal(x.actual.pos.x, Math.fround(3 + x.actual.motion.x), 'readonly540 tested after add/ground/state');
    equal(x.actual.fbPhase, 1, 'readonly540 does not suppress callback by substituting null');
    const y = phaseOneFixture(); y.streams.getPartBinding(y.id, 0).state1b = 1;
    // Source dispatch captures the selector; an explicit observation mutation
    // after the later ground call proves the increment reloads current540.
    // This does not bypass a source boundary or manufacture a successful frame.
    let changed = false;
    observeDescriptors(() => rejects(y.run, 'actual800715f8'), (owner,key) => {
      if (!changed && owner === y.streams.getPartBinding(y.id, 0) && key === 'state1b' && y.actual.pos.x !== 3) {
        changed = true; y.actual.fbPhase = 255;
      }
    });
    check(changed, 'late source state load observed'); equal(y.actual.fbPhase, 0, 'actual540 increment wraps unsigned byte');
  }
  {
    const x = phaseOneFixture(); countdown(x);
    let reentered = false;
    observeDescriptors(() => rejects(x.run, 'reentry'), (owner,key) => {
      if (!reentered && owner === x.streams.getPartBinding(x.id, 0) && key === 'wait14') {
        reentered = true;
        try {x.capture();} catch { /* swallowed child error cannot unpoison outer action */ }
      }
    });
    check(reentered, 'actual stream wait triggered reentry');
    equal(x.streams.getPartBinding(x.id, 0).wait14, 1, 'real stream writes before outer reentry check are retained');
    equal(x.actual.turnErrorYaw, 2, 'caught stream reentry prevents yaw');
    rejects(x.capture, 'incomplete'); rejects(() => x.streams.update(x.id,15), 'incomplete');
  }
  for (const state of [1, 128]) {
    const x = phaseOneFixture(), part = x.streams.getPartBinding(x.id, 0);
    // Explicit copied test commands, not an original bank/retail schedule.
    const next = x.streams.createStream(new Uint8Array([2,255,state,4,6,7,0,0, 0,9,0,2]));
    Object.assign(part, {current00:x.streams.createCommand({flags01:8}), next04:next, wait14:1});
    x.streams.getActorBinding(x.id).activeMask579 = 1;
    rejects(x.run, state === 1 ? 'actual800715f8' : 'at8020bb38 frsqrte');
    equal(part.state1b,state,'actual4cd24 continuation writes canonical02 state before phase1 reads it');
    equal(part.auxiliary1c,4,'real02 auxiliary store retained');
    equal(x.actual.byte6e8,6,'real02 actual6e8 store retained'); equal(x.actual.byte6e9,7,'real02 actual6e9 store retained');
    equal(part.wait14,2,'real parser installs following wait before yaw/motion');
    equal(x.streams.cursorOffset(next,part.current00!),8,'actual parsed wait cursor retained');
    equal(x.actual.fbPhase,state === 1 ? 2 : 1,'phase tests freshly authored signed state rather than pre-update snapshot');
  }
  {
    const x = phaseOneFixture(), reads: string[] = []; let stateRead = false;
    Object.defineProperty(x.streams.getPartBinding(x.id,0),'state1b',{writable:false});
    observeDescriptors(() => rejects(x.run,'at8020bb38 frsqrte'), (owner,key) => {
      if (owner === x.streams.getPartBinding(x.id,0) && key === 'state1b' && x.actual.pos.x !== 3) stateRead = true;
      if (owner === x.actual.motion && stateRead) reads.push(String(key));
    });
    equal(reads.filter(key=>['x','y','z'].includes(key)).join(','),'x,y,z','actual8020bb14 reads current XYZ after ground/signed state');
    const y = phaseOneFixture(), early: string[] = []; let earlyState = false;
    y.actual.motion.x = Math.fround(1e30);
    observeDescriptors(() => rejects(y.run,'8020bb1c squareX'), (owner,key) => {
      if (owner === y.streams.getPartBinding(y.id,0) && key === 'state1b' && y.actual.pos.x !== 3) earlyState = true;
      if (owner === y.actual.motion && earlyState) early.push(String(key));
    });
    equal(early.filter(key=>['x','y','z'].includes(key)).join(','),'x,y','paired XY product fault precedes numerical Z load');
    equal(y.actual.pos.x,Math.fround(3+y.actual.motion.x),'numerical finite-domain refusal retains prior source add');
    const z = phaseOneFixture(); z.streams.getPartBinding(z.id,0).state1b = 1;
    const unreached: string[] = []; let callbackState = false;
    observeDescriptors(() => rejects(z.run,'actual800715f8'), (owner,key) => {
      if (owner === z.streams.getPartBinding(z.id,0) && key === 'state1b' && z.actual.pos.x !== 3) callbackState = true;
      if (owner === z.actual.motion && callbackState) unreached.push(String(key));
    });
    equal(unreached.filter(key=>['x','y','z'].includes(key)).join(','),'','nonnull callback boundary precedes every magnitude operand load');
  }
  for (const alias of ['byte1cef','state1cef','byte1cf0','byte1d0f','state1d0f','byte1d10']) {
    const x = phaseOneFixture(); (x.actual as unknown as Record<string, unknown>)[alias] = 0;
    rejects(x.capture, 'competing source storage alias');
  }
  {
    const x = fixture(false); (x.actual as unknown as Record<string, unknown>).state1b = 0;
    rejects(() => x.action.bindActor(x.id), 'competing source stream-part storage owner');
    delete (x.actual as unknown as Record<string, unknown>).state1b; x.action.bindActor(x.id);
    for (let index = 0; index < 4; index++) check(x.action.getSourceOwners(x.id).includes(x.streams.getPartBinding(x.id,index)), 'all genuine parts retained even without ground');
    const y = fixture(false), other = createSourceActorMovementFollowupRuntime({mapping:y.mapping, waits:y.streams, setup:{getActorBinding:()=>y.setupState}});
    other.bindActor(y.id, createRomActor(), {byte661:0,field66c:0,field670:0}); y.streams.bindActualActor(y.id,other);
    rejects(() => y.action.bindActor(y.id), 'source stream actual: canonical owner changed');
  }
  {
    const x = phaseOneFixture(); countdown(x);
    const original = x.actual.motion; let changed = false;
    observeDescriptors(() => rejects(x.run, 'motion38: canonical owner changed'), (owner,key) => {
      if (!changed && owner === x.streams.getPartBinding(x.id,0) && key === 'wait14') {
        changed = true; x.actual.motion = {...original};
      }
    });
    equal(original.x,91,'post-stream owner admission prevents stale-motion stores');
    equal(x.actual.turnErrorYaw,2,'post-stream wrong owner refuses before yaw');
    equal(x.streams.getPartBinding(x.id,0).wait14,1,'wrong-owner refusal retains real stream prefix');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual),'late wrong owner permanently poisons actual');
  }
  console.log('[double-action-test] genuine phase0/phase1 dispatch, actual mask15 stream waits, canonical raw states, signed yaw, vector order, callback/numerical boundaries and permanent partial refusal passed');
}
