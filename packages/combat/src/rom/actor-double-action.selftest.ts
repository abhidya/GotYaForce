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
    action, sources, processor, hooks, capture, run, ground, gauges, terrain, streams, parameterState: attributes.getParameterDescriptor(parameter)};
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
  console.log('[double-action-test] genuine dispatch, saved selectors, canonical owners, signed yaw, vector order and permanent partial refusal passed');
}
