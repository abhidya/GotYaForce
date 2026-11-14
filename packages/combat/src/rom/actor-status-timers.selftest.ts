import {createSourceActorStatusTimersRuntime, type SourceActorStatusTimersBinding,
  type SourceActorStatusBorgOwner, type SourceActorStatusAmmoSlot} from './actor-status-timers.js';
import {createSourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {createSourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {createSourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import {createRomActor} from './actor.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import {createSourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';
import type {WeaponCell} from '../types.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-status-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
function fixture(defer = false) {
  const unsupported = (): never => {throw Error('unexpected unrelated source operation');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const mapping = createSourceActorJointMappingRuntime(joints, feedback,
    {interpretAObj: unsupported, animateRObjs: unsupported, animateDObjs: unsupported}, {convertEulerToQuaternion: unsupported});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 0, jointBank33: 0, poseBuffer35: 0})));
  const descriptor = mapping.createDescriptor([]);
  const id = mapping.createActor({descriptor4b0: descriptor, jointCount1d90: 0, boundary1d91: 0, boundary1d92: 0,
    boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 2}, {parts, poses: [[], []]});
  const dispatch = createSourceActorAnimationDispatchRuntime(mapping, feedback);
  dispatch.bindActor(id, {family1d88: null, shared1d8c: null, marker578: 0, marker1db3: 0});
  const targets = createSourceStreamWaitTargetRuntime(mapping, feedback, dispatch);
  targets.bindActor(id, Array.from({length: 4}, () => ({target08: 0, previous0c: 0, accumulator10: 0})));
  const streams = createSourceStreamWaitRuntime({mapping, feedback, dispatch, targets});
  streams.bindActor(id, {activeMask579: 0, blockedMask1d9a: 0, marker71d: 0},
    Array.from({length: 4}, () => ({current00: null, wait14: 0, finished1a: 0, event1e: 0})));
  streams.bindStartActor(id, {familyBank1d80: null, sharedBank1d84: null, defaultSelector582: 0, marker709: 63});
  const setup = createSourceActorAnimationSetupRuntime({mapping, feedback, dispatch,
    descriptors: createSourceAnimationDescriptorBankRuntime(), starts: streams,
    metadata: {getPartBinding: unsupported, applyMetadata: unsupported}, archiveBanks: {resolveArchive: unsupported}});
  setup.bindActor(id, {familyBank1d78: null, sharedBank1d7c: null, movement6d8: 1});
  const actual = Object.assign(createRomActor(), {slopeMode698: 2});
  actual.stateTimer = 1; actual.housekeeping73f = 7; actual.aimRateScale = 0.5;
  actual.dt = 99; actual.contactFlags = 0; actual.fbState = 1;
  const matrices = createSourceActorJointMatrixRuntime(feedback);
  const make = () => matrices.createMatrix([1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0]);
  const world = createSourceActorWorldMatrixRuntime({mapping, feedback, matrices});
  world.bindActor(id, actual, {mode4a0: 0, mode4a1: 0, flags48a: 0, mask1d70: 0, roll74: 0, yawOffset6b8: 1,
    scale58: {x: 1, y: 1, z: 1}, offset1dbc: {x: 0, y: 0, z: 0}, adjusted1d54: {x: 0, y: 0, z: 0},
    preRotation1d64: {x: 0, y: 0, z: 0}}, {matrices8d4: [], copy114: make(), copy1aa4: make(), scratch: make(),
    topology1994: [], corrections18d4: [], scales15d4: []});
  const movement = createSourceActorMovementFollowupRuntime({mapping, waits: streams, setup, matrixOwner: matrices});
  movement.bindActor(id, actual, {byte661: 0, field66c: 0, field670: 0});
  const attributes = createSourceActorAttributeRefreshRuntime({world, mapping, movement});
  const parameter = attributes.createParameterDescriptor({field04: 100, field08: 7});
  attributes.bindActor(id, {byte87: 0, parameter4ac: parameter});
  const borg: SourceActorStatusBorgOwner = {hp: 200, hitDrainFrames: 0, balanceGauge: 3, balanceGaugeMax: 45000,
    balanceRefillDelay: 0.25, downResetDelay: 2, comboWindow: 0.5, comboAccum: 9, comboRank: 3,
    invincTimer: 0.25, sourceAmmoRefillPauseMask: 0};
  const cells: WeaponCell[] = Array.from({length: 3}, (_, i) => ({cur: i, max: 5 + i, refillType: 0, refillParam: 2, timer: 0.25 + i * 0.5}));
  const slots: [SourceActorStatusAmmoSlot, SourceActorStatusAmmoSlot, SourceActorStatusAmmoSlot] =
    [0, 1, 2].map(i => ({cell: cells[i]!, mirror776: -1})) as typeof slots;
  const initial: Partial<SourceActorStatusTimersBinding> = {
    field690: 0.25, field69c: 0.5, field6a0: -1, field6a4: -0,
    byte6fc: 0, byte7de: 2, byte71c: 0, byte656: 255, byte593: 1, byte594: 2, byte596: 0,
    byte707: 63, byte708: 63, bytea8: 7, bytea9: 7, byteaa: 7, byteab: 7, byteac: 7, bytead: 7,
    short736: 95, short738: -1, short73a: 0, byte747: 5, field1dcc: 0.5, field7d8: 2,
    short272: 17, childPointers440: Array(8).fill(null), byte7d4: 0, field8c8: 1,
    byte6fd: 0, byte702: 0, short282: 0, short284: 0, short6b6: -22,
  };
  const hooks: {world?: () => unknown; worldBinding?: () => unknown; mapping?: () => unknown;
    movement?: () => unknown; attribute?: () => unknown; parameter?: () => unknown; stream?: () => unknown} = {};
  const worldAdapter = {
    getActualActor(key: symbol) {check(this === worldAdapter, 'world receiver'); return (hooks.world ? hooks.world() : world.getActualActor(key)) as typeof actual;},
    getActorBinding(key: symbol) {check(this === worldAdapter, 'world binding receiver'); return (hooks.worldBinding ? hooks.worldBinding() : world.getActorBinding(key)) as ReturnType<typeof world.getActorBinding>;},
  };
  const mappingAdapter = {getActor(key: symbol) {check(this === mappingAdapter, 'mapping receiver'); return (hooks.mapping ? hooks.mapping() : mapping.getActor(key)) as ReturnType<typeof mapping.getActor>;}};
  const movementAdapter = {
    getActualActor(key: symbol) {return movement.getActualActor(key);},
    getActorBinding(key: symbol) {check(this === movementAdapter, 'movement receiver'); return (hooks.movement ? hooks.movement() : movement.getActorBinding(key)) as ReturnType<typeof movement.getActorBinding>;},
  };
  const attributeAdapter = {
    getActorBinding(key: symbol) {check(this === attributeAdapter, 'attribute receiver'); return (hooks.attribute ? hooks.attribute() : attributes.getActorBinding(key)) as ReturnType<typeof attributes.getActorBinding>;},
    getParameterDescriptor(key: symbol) {check(this === attributeAdapter, 'parameter receiver'); return (hooks.parameter ? hooks.parameter() : attributes.getParameterDescriptor(key)) as ReturnType<typeof attributes.getParameterDescriptor>;},
  };
  const streamAdapter = {getStartActorBinding(key: symbol) {check(this === streamAdapter, 'stream receiver');
    return (hooks.stream ? hooks.stream() : streams.getStartActorBinding(key)) as ReturnType<typeof streams.getStartActorBinding>;}};
  const sources = {world: worldAdapter, mapping: mappingAdapter, movement: movementAdapter, attributes: attributeAdapter, streams: streamAdapter};
  const runtime = createSourceActorStatusTimersRuntime(sources), bind = () => runtime.bindActor(id, borg, initial, slots);
  if (!defer) bind();
  return {id, actual, world, mapping, movement, attributes, parameter, streams, borg, cells, slots, initial, hooks,
    sources, runtime, bind, state: () => runtime.getActorBinding(id), run: () => runtime.updateActor(id)};
}

export function runActorStatusTimersSelfTests(): void {
  {
    const x = fixture(); x.run(); const s = x.state();
    equal(x.actual.stateTimer, 0, 'source timestep expires state timer'); equal(x.actual.dt, 99, 'legacy dt untouched');
    equal(x.actual.housekeeping73f, 0, 'state timer clears housekeeping'); equal(s.field690, 0, 'negative result clamps');
    equal(x.actual.slopeMode698, 1.5, 'actual slope timer'); equal(s.field69c, 0, 'exact zero result');
    equal(s.field6a0, -1, 'negative input untouched'); equal(s.field6a4, -0, 'negative zero untouched');
    equal(s.byte7de, 1, 'arm countdown'); equal(x.world.getActorBinding(x.id).yawOffset6b8, 0, 'actual world yaw timer');
    equal(s.byte656, 254, 'raw signed-byte decrement bits'); equal(s.byte593, 0, 'one byte expires');
    for (const key of ['bytea8', 'bytea9', 'byteaa', 'byteab', 'byteac', 'bytead'] as const) equal(s[key], 1, `${key} fresh stream709`);
    equal(s.short736, 100, 'same4ac refill caps'); equal(s.byte747, 0, 'ordinary class clears747');
    equal(x.borg.balanceGauge, 45000, 'signed source load and short store preserve host u16 bits');
    equal(x.borg.downResetDelay, 1.5, 'positive no-expiry down timer supported'); equal(s.field7d8, 1.5, 'positive no-expiry reset timer');
    equal(x.borg.comboAccum, 0, 'combo accumulator'); equal(x.borg.comboRank, 0, 'combo rank');
    equal(x.borg.invincTimer, 0, 'actual source720'); equal(s.short272, 0, 'invinc expiry flag');
    equal(x.cells[0]!.cur, 5, 'active mode0 current'); equal(x.slots[0].mirror776, 5, 'active mode0 mirror');
    equal(x.cells[0]!.timer, 0, 'mode0 clears negative debt'); equal(x.cells[1]!.timer, 0.25, 'slot1 non-expiry');
    equal(x.cells[2]!.timer, 0.75, 'slot2 independent'); equal(s.field8c8, 1.5, 'fb accumulator');
    x.mapping.getActor(x.id).timestep1dc8 = 0.25; x.actual.stateTimer = 1;
    x.streams.getStartActorBinding(x.id).marker709 = 0; x.actual.contactFlags = 63;
    x.borg.sourceAmmoRefillPauseMask = 6; x.run(); equal(x.actual.stateTimer, 0.75, 'live source timestep');
    equal(x.state().bytea8, 0, 'live stream709 not legacy contactFlags'); equal(x.cells[1]!.timer, 0.25, 'live597 pause');
  }
  {
    const x = fixture(); x.actual.controlWord = 3; x.actual.stateTimer = NaN; x.run();
    check(Number.isNaN(x.actual.stateTimer), 'control3 skips stateTimer entirely');
    const y = fixture(); y.actual.stateTimer = -0; y.mapping.getActor(y.id).timestep1dc8 = NaN; y.run();
    equal(y.actual.stateTimer, -0, 'nonpositive skips invalid dt');
    const z = fixture(); z.actual.stateTimer = 3; Object.defineProperty(z.actual, 'housekeeping73f', {writable: false}); z.run();
    equal(z.actual.stateTimer, 1, 'unreached destination may be readonly');
  }
  {
    const x = fixture(); x.actual.stateTimer = 1; x.mapping.getActor(x.id).timestep1dc8 = -0;
    x.actual.aimRateScale = 2 ** -149; x.state().field690 = 2 ** -149; x.actual.slopeMode698 = 2 ** -148;
    x.run(); equal(x.actual.stateTimer, 1, 'negative zero dt'); equal(x.state().field690, 0, 'subnormal exact cancellation');
    equal(x.actual.slopeMode698, 2 ** -149, 'gradual underflow');
    const y = fixture(); y.actual.stateTimer = 0; y.state().field690 = Math.fround(3.4e38); y.actual.aimRateScale = Math.fround(-3.4e38);
    rejects(y.run, 'overflow'); equal(y.state().field690, Math.fround(3.4e38), 'overflow refuses before store');
  }
  {
    const x = fixture(); x.world.getActorBinding(x.id).yawOffset6b8 = -32768; x.state().short73a = -32768; x.run();
    equal(x.world.getActorBinding(x.id).yawOffset6b8, 32767, 'world signed short wraps');
    equal(x.state().short73a, 32767, 'negative delay wraps rather than expires'); equal(x.state().short736, 95, 'nonzero delay no refill');
    const y = fixture(); y.world.getActorBinding(y.id).mode4a1 = 1; y.state().byte71c = 255; y.run();
    equal(y.world.getActorBinding(y.id).yawOffset6b8, 0, 'mode4a1 resets independent of71c');
    const z = fixture(); z.state().byte71c = 1; z.run(); equal(z.world.getActorBinding(z.id).yawOffset6b8, 1, '71c blocks yaw decrement');
  }
  {
    const x = fixture(); x.state().short736 = 32767; x.attributes.getParameterDescriptor(x.parameter).field08 = 1; x.run();
    equal(x.state().short736, -32768, 'refill wraps before cap comparison');
    const y = fixture(); y.attributes.getParameterDescriptor(y.parameter).field04 = -300; y.run();
    equal(y.state().short736, -300, 'signed cap');
    const z = fixture(); z.movement.getActorBinding(z.id).byte661 = 2; z.run(); equal(z.state().byte747, 5, 'special class leaves747');
    const w = fixture(); w.movement.getActorBinding(w.id).byte661 = 6; w.actual.controlWord = 0x80;
    w.state().short73a = NaN; w.run(); check(Number.isNaN(w.state().short73a), 'special control80 skips refill');
  }
  {
    const x = fixture(true); delete x.initial.short736; delete x.initial.short73a;
    x.attributes.getActorBinding(x.id).byte87 = 1; x.bind(); x.run(); equal(x.state().byte747, 5, 'byte87 skips complete refill branch');
    const y = fixture(); y.attributes.getActorBinding(y.id).parameter4ac = null;
    rejects(y.run, 'parameter4ac'); equal(y.actual.slopeMode698, 1.5, 'late parameter failure retains early timers');
    equal(y.state().bytea8, 1, 'late parameter failure retains counter effects');
  }
  {
    const x = fixture(); x.borg.hitDrainFrames = 1; rejects(x.run, 'poison');
    equal(x.state().byte594, 1, 'poison refusal retains byte prefix'); equal(x.state().bytea8, 7, 'poison stops before counters');
    const y = fixture(); y.state().byte707 = 0; rejects(y.run, '800f0104');
    equal(y.state().bytead, 1, 'FX refusal retains all six counters'); equal(y.state().short736, 95, 'FX stops before refill');
    const z = fixture(); z.borg.downResetDelay = 0.25; rejects(z.run, '8003d3e8');
    equal(z.borg.downResetDelay, 0, 'down expiry clamp retained'); equal(z.borg.balanceGauge, 45000, 'earlier gauge effect retained');
    equal(z.borg.comboWindow, 0.5, 'down call stops before combo');
    const w = fixture(); w.state().field7d8 = 0.25; rejects(w.run, '8003d444');
    equal(w.state().field7d8, 0, '7d8 clamp retained'); equal(w.borg.comboAccum, 9, '7d8 stops before combo');
  }
  {
    const x = fixture(); x.actual.controlWord = 0x01000000;
    x.borg.balanceRefillDelay = NaN; x.borg.downResetDelay = NaN; x.state().field7d8 = NaN; x.borg.comboWindow = NaN;
    x.run(); equal(x.borg.invincTimer, 0, '720 remains outside control gate');
    check(Number.isNaN(x.borg.comboWindow), 'gate skips nonfinite timer read');
    const y = fixture(); (y.state().childPointers440 as (symbol | null)[])[7] = Symbol('child');
    rejects(y.run, 'child lifecycle'); equal(y.borg.invincTimer, 0, 'child refusal keeps timer prefix');
    equal(y.cells[0]!.timer, 0.25, 'child refusal precedes ammo');
  }
  {
    const x = fixture(true); x.borg.sourceAmmoRefillPauseMask = 2;
    delete (x.cells[1] as Partial<WeaponCell>).timer; delete (x.cells[1] as Partial<WeaponCell>).refillType;
    delete x.slots[1].mirror776; x.bind(); x.run(); equal(x.cells[0]!.cur, 5, 'active neighbor of missing paused slot');
    x.borg.sourceAmmoRefillPauseMask = 0; rejects(x.run, 'timer: own data property');
    const y = fixture(true); y.cells[2]!.timer = 0; delete (y.cells[2] as Partial<WeaponCell>).refillType;
    delete (y.cells[2] as Partial<WeaponCell>).max; delete y.slots[2].mirror776; y.bind(); y.run();
    equal(y.cells[2]!.timer, 0, 'nonpositive debt skips mode and descriptors');
  }
  {
    const x = fixture(); x.state().byte6fc = 128; x.run(); equal(x.state().byte7de, 1, 'nonzero raw burst byte arms');
    for (let i = 0; i < 3; i++) {equal(x.cells[i]!.cur, 5 + i, 'burst10 refills distinct slot'); equal(x.slots[i]!.mirror776, 5 + i, 'burst10 writes mirror');}
    const y = fixture(); y.cells[0]!.refillType = 1; y.run(); equal(y.cells[0]!.timer, -0.25, 'mode1 expiry retains negative debt');
    equal(y.slots[0].mirror776, 5, 'mode1 expiry mirror');
    const z = fixture(); z.cells[0]!.refillType = 1; z.cells[0]!.timer = 2;
    rejects(z.run, '8006ddbc'); equal(z.cells[0]!.timer, 1.5, 'mode1 divide refusal preserves debt prefix');
    equal(z.cells[0]!.cur, 0, 'mode1 divide refusal no fabricated cur'); equal(z.cells[1]!.timer, 0.75, 'refusal stops next slot');
    const w = fixture(); w.cells[0]!.refillType = 2; w.cells[0]!.max = NaN; w.run();
    equal(w.cells[0]!.timer, 0.25, 'other mode genuine no-write branch');
  }
  {
    const x = fixture(true); delete x.slots[0].mirror776; x.bind(); rejects(x.run, 'mirror776');
    equal(x.cells[0]!.cur, 5, 'missing mirror retains current store'); equal(x.cells[0]!.timer, -0.25, 'missing mirror retains debt before final clamp');
    const y = fixture(); Object.defineProperty(y.slots[0], 'mirror776', {writable: false}); rejects(y.run, 'non-writable');
    equal(y.cells[0]!.cur, 5, 'readonly late mirror retains cur');
    const z = fixture(); Object.defineProperty(z.cells[0], 'cur', {writable: false}); rejects(z.run, 'non-writable');
    equal(z.cells[0]!.timer, -0.25, 'readonly cur retains debt'); equal(z.slots[0].mirror776, -1, 'mirror not reached');
  }
  {
    const x = fixture(); x.cells[0]!.max = -2; x.run(); equal(x.cells[0]!.cur, -2, 'ammo signed max'); equal(x.slots[0].mirror776, -2, 'signed mirror');
    const y = fixture(); y.cells[0]!.max = 32768; rejects(y.run, 'max: integer out of bounds');
    equal(y.cells[0]!.timer, -0.25, 'late signed max refusal retains timer');
    const z = fixture(); z.cells[0]!.refillType = 1; z.cells[0]!.timer = 2; z.cells[0]!.refillParam = NaN;
    rejects(z.run, 'refillParam'); equal(z.cells[0]!.timer, 1.5, 'mode1 param admission follows debt store');
  }
  {
    const x = fixture(); x.state().byte7d4 = 1; x.attributes.getParameterDescriptor(x.parameter).field04 = -1;
    x.run(); equal(x.state().short738, -1, 'tail4ac cap'); equal(x.state().short736, -1, 'tail same cap');
    const y = fixture(); y.state().byte7d4 = 1; y.actual.controlWord = 0x02000000; y.actual.lockYaw = 0xf000;
    rejects(y.run, '8005c290'); equal(y.state().byte6fd, 38, 'reaction byte prefix'); equal(y.state().byte702, 8, 'reaction702');
    equal(y.state().short282, -10240, 'reaction282 bits'); equal(y.state().short284, 0x1000, 'reaction yaw wrapping');
    equal(y.state().short6b6, -22, 'no fabricated restore after missing reaction call');
    equal(y.cells[0]!.cur, 5, 'reaction refusal preserves ammo'); equal(y.state().field8c8, 1, 'reaction stops before tail');
    const z = fixture(); z.actual.controlWord = 0x80000000; z.state().byte7d4 = NaN; z.run();
    check(Number.isNaN(z.state().byte7d4), 'control high bit skips7d4 read');
  }
  {
    const x = fixture(); x.state().field8c8 = -1; x.run(); equal(x.state().field8c8, -1, 'negative tail accumulator unchanged');
    const y = fixture(); y.state().field8c8 = -0; y.run(); equal(y.state().field8c8, 0.5, 'negative zero tail adds');
    const z = fixture(); z.actual.fbState = -1; z.state().field8c8 = NaN; z.run(); equal(z.state().field8c8, 0, 'non1 fb overwrites without old-value validation');
    const w = fixture(); Object.defineProperty(w.state(), 'field8c8', {writable: false}); rejects(w.run, 'non-writable');
    equal(w.cells[0]!.cur, 5, 'tail readonly failure retains ammo');
  }
  {
    const x = fixture(true); x.slots[1] = {cell: x.cells[0]!, mirror776: 0}; rejects(x.bind, 'source owner alias');
    const y = fixture(true); x.slots[1] = x.slots[0]; y.slots[1] = y.slots[0]; rejects(y.bind, 'source owner alias');
    const z = fixture(); Object.defineProperty(z.slots[1], 'cell', {value: z.cells[0]});
    rejects(z.run, 'cell owner changed'); equal(z.cells[0]!.cur, 5, 'late replaced cell retains previous slot');
    const w = fixture(true); Object.assign(w.actual, {invulnTimer: 1}); rejects(w.bind, 'source720 owner conflict');
    const v = fixture(); Object.assign(v.actual, {invulnTimer: 1}); rejects(v.run, 'source720 owner conflict');
    equal(v.borg.comboAccum, 0, 'late rival720 refusal retains prefix');
  }
  {
    const x = fixture(); let called = 0;
    x.sources.world.getActualActor = () => {called++; throw Error('replacement must not run');};
    x.sources.mapping.getActor = () => {called++; throw Error('replacement must not run');};
    x.run(); equal(called, 0, 'captured methods and receivers');
    const y = fixture(); y.hooks.stream = () => Promise.resolve(y.streams.getStartActorBinding(y.id));
    rejects(y.run, 'asynchronously'); equal(y.state().byte594, 1, 'async late owner refusal prefix');
    const z = fixture(); z.hooks.mapping = () => ({...z.mapping.getActor(z.id)}); rejects(z.run, 'owner changed');
    equal(z.actual.stateTimer, 1, 'mapping snapshot rejected before timer store');
  }
  {
    const x = fixture(); x.hooks.stream = () => {
      try {x.run();} catch { /* Intentionally caught by a hostile adapter. */ }
      return x.streams.getStartActorBinding(x.id);
    };
    rejects(x.run, 'caught same-runtime reentry'); equal(x.state().byte594, 1, 'reentry keeps prior byte writes');
    equal(x.state().bytea8, 7, 'poison blocks further writes');
    delete x.hooks.stream; x.run(); equal(x.state().bytea8, 1, 'independent later call can resume');
  }
  {
    const x = fixture(); let gets = 0;
    Object.defineProperty(x.cells[0], 'max', {get() {gets++; return 5;}}); rejects(x.run, 'own data property');
    equal(gets, 0, 'source accessor never invoked'); equal(x.cells[0]!.timer, -0.25, 'accessor refusal remains lazy');
    const y = fixture(); Object.freeze(y.attributes.getParameterDescriptor(y.parameter)); Object.freeze(y.mapping.getActor(y.id));
    Object.defineProperty(y.actual, 'aimRateScale', {writable: false});
    y.cells[0]!.cur = NaN; y.slots[0].mirror776 = NaN; y.run(); equal(y.cells[0]!.cur, 5, 'stale write-only destination allowed');
    equal(y.slots[0].mirror776, 5, 'stale mirror overwritten');
    const z = fixture(true); delete z.initial.field6a4; z.bind(); rejects(z.run, 'field6a4');
    equal(z.state().field69c, 0, 'missing later float keeps prefix');
  }
  {
    const x = fixture(true); rejects(() => x.attributes.createParameterDescriptor({field04: 32768}), 'signed-short');
    rejects(() => x.attributes.createParameterDescriptor({field08: 0.5}), 'signed-short');
    x.initial.bytea8 = 256; rejects(x.bind, 'integer out of bounds');
    x.initial.bytea8 = 7; x.bind(); rejects(x.bind, 'new symbol');
    rejects(() => x.runtime.updateActor(Symbol('foreign')), 'unknown/non-owned');
  }
  {
    const x = fixture(); let reads = 0;
    x.hooks.parameter = () => {
      reads++;
      if (reads === 2) x.attributes.getParameterDescriptor(x.parameter).field04 = 98;
      return x.attributes.getParameterDescriptor(x.parameter);
    };
    x.run(); equal(reads, 2, 'source4ac reloaded separately for increment and cap');
    equal(x.state().short736, 98, 'second descriptor reads live cap');
    const y = fixture(); let loads = 0;
    y.hooks.parameter = () => {
      loads++; if (loads === 2) return {...y.attributes.getParameterDescriptor(y.parameter)};
      return y.attributes.getParameterDescriptor(y.parameter);
    };
    rejects(y.run, 'parameter4ac owner changed'); equal(y.state().short736, 102, 'changed descriptor refuses after short sum store');
    const z = fixture(); z.hooks.parameter = () => z.borg;
    rejects(z.run, 'parameter4ac aliases'); equal(z.state().short736, 95, 'parameter-owner alias fails before short load/store');
    const w = fixture(); w.run(); const other = w.attributes.createParameterDescriptor({field04: 100, field08: 7});
    w.attributes.getActorBinding(w.id).parameter4ac = other;
    w.hooks.parameter = () => w.attributes.getParameterDescriptor(w.parameter);
    rejects(w.run, 'parameter4ac aliases');
  }
  {
    const x = fixture(true); delete x.initial.bytea8; delete x.initial.bytea9; delete x.initial.byteaa;
    delete x.initial.byteab; delete x.initial.byteac; delete x.initial.bytead; x.initial.byte708 = 0;
    x.bind(); x.run(); equal(x.state().bytea8, undefined, 'inactive counters remain absent');
    const y = fixture(); y.actual.stateTimer = 0; Object.defineProperty(y.actual, 'slopeMode698', {writable: false});
    rejects(y.run, 'non-writable'); equal(y.state().field690, 0, 'late slope destination preserves690');
    equal(y.state().field69c, 0.5, 'slope destination failure stops before69c');
    const z = fixture(); z.state().field8c8 = Math.fround(3.4e38); z.state().field1dcc = Math.fround(3.4e38);
    z.actual.controlWord = 0x01000000; z.borg.invincTimer = 0;
    rejects(z.run, 'overflow'); equal(z.cells[0]!.cur, 5, 'tail arithmetic overflow preserves active ammo');
  }
  {
    // Test-only hostile instrumentation observes individual stores/reloads. It
    // does not expand the runtime's non-proxy input contract to general proxies.
    const x = fixture(true), cell = x.cells[0]!;
    const probe = new Proxy(cell, {set(target, key, value) {
      Reflect.set(target, key, value);
      if (key === 'cur') {target.max = 11; x.actual.aimRateScale = 4; x.borg.sourceAmmoRefillPauseMask = 2;}
      return true;
    }});
    x.slots[0] = {cell: probe, mirror776: -1}; x.bind(); x.run();
    equal(cell.cur, 5, 'first max load feeds current'); equal(x.slots[0].mirror776, 11, 'second max reload feeds mirror');
    equal(x.cells[1]!.timer, 0.75, 'source597 freshly reloaded after previous slot store');
    equal(x.cells[2]!.timer, 0.75, 'ammo rate retained across all three slots despite source768 change');
    const y = fixture(true); y.initial.field690 = 2; y.actual.slopeMode698 = 2;
    let reads = 0;
    // The world getter returns the same actual actor; scalar loads remain live.
    y.hooks.worldBinding = () => {reads++; return y.world.getActorBinding(y.id);};
    y.bind(); y.run(); equal(reads, 2, 'stable bound world record reread at its reached source stage');
  }
}
