import {createRomActor, type RomVisibilityTarget} from './actor.js';
import {createSourceActorTransformHistoryRuntime, type SourceActorTransformHistoryBinding} from './actor-transform-history.js';
import {createSourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-transform-history-test] ${why}`);}
function rejects(run: () => unknown, text: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(text), `expected ${text}, got ${message}`);
}
const vec = (x: number, y = x, z = x) => ({x, y, z});
function fixture(deferBind = false) {
  const unexpected = (): never => {throw Error('history must not animate or rebuild matrices');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const mapping = createSourceActorJointMappingRuntime(joints, feedback,
    {interpretAObj: unexpected, animateRObjs: unexpected, animateDObjs: unexpected}, {convertEulerToQuaternion: unexpected});
  const matrices = createSourceActorJointMatrixRuntime(feedback);
  const world = createSourceActorWorldMatrixRuntime({mapping, feedback, matrices});
  function addActor() {
    const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
      {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
      {descriptor00: null, scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0})));
    const id = mapping.createActor({descriptor4b0: null, jointCount1d90: 0, boundary1d91: 0, boundary1d92: 0,
      boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses: [[], []]});
    const actual = createRomActor();
    Object.assign(actual.pos, vec(10, 20, 30)); Object.assign(actual.savedGroundPos, vec(1, 2, 3));
    Object.assign(actual.targetCache5e8, vec(-1, -2, -3)); Object.assign(actual.aimOrigin518, vec(100, 200, 300));
    actual.bodyPitch = 0x8000; actual.heading = 0xffff; actual.stepHeight = 7; actual.visibilityBit = 0x80;
    world.bindActor(id, actual, {mode4a0: 0, mode4a1: 0, flags48a: 0, mask1d70: 0, roll74: 32767, yawOffset6b8: 0,
      scale58: vec(1), offset1dbc: vec(0), adjusted1d54: vec(0), preRotation1d64: vec(-32768, 4, 32767)},
    {matrices8d4: [], copy114: matrices.createMatrix(Array(12).fill(91)), copy1aa4: matrices.createMatrix(Array(12).fill(92)),
      scratch: matrices.createMatrix(Array(12).fill(93)), topology1994: [], corrections18d4: [], scales15d4: []});
    return {id, actual, worldState: world.getActorBinding(id)};
  }
  const actor = addActor();
  const hooks: {actual?: () => void; world?: () => void; replaceActual?: boolean; replaceWorld?: boolean} = {};
  const events: string[] = [];
  const adapter = {
    getActualActor(id: symbol) {check(this === adapter, 'captured actual receiver'); events.push('actual'); hooks.actual?.();
      const value = world.getActualActor(id); return hooks.replaceActual ? {...value} : value;},
    getActorBinding(id: symbol) {check(this === adapter, 'captured world receiver'); events.push('world'); hooks.world?.();
      const value = world.getActorBinding(id); return hooks.replaceWorld ? {...value} : value;},
  };
  const sources = {world: adapter};
  const initial: SourceActorTransformHistoryBinding = {rotation76: vec(101, 102, 103), preRotation1d6a: vec(104, 105, 106),
    previousStepHeight6d4: 107, aimOrigin524: vec(-101, -102, -103)};
  const runtime = createSourceActorTransformHistoryRuntime(sources), bind = () => runtime.bindActor(actor.id, initial);
  if (!deferBind) bind();
  events.length = 0;
  return {...actor, world, mapping, matrices, adapter, sources, runtime, initial, hooks, events, bind, addActor,
    state: () => runtime.getActorBinding(actor.id), snapshot: () => runtime.snapshotActor(actor.id)};
}
function target(eligibility83 = 1, visibilityMask5e6 = 0): RomVisibilityTarget {
  return {eligibility83, visibilityMask5e6, controlWord: NaN};
}
export function runActorTransformHistorySelfTests(): void {
  {
    const f = fixture(), state = f.state();
    const pos = f.actual.pos, old = f.actual.savedGroundPos, older = f.actual.targetCache5e8, aim = f.actual.aimOrigin518;
    check(f.world.getActualActor(f.id) === f.actual && state === f.state(), 'actual actor and history owner identities');
    check(state.rotation76 !== f.initial.rotation76 && state.aimOrigin524 !== f.initial.aimOrigin524 &&
      state.rotation76.x === 101 && state.previousStepHeight6d4 === 107, 'only explicit missing history copied at bind');
    f.initial.rotation76.x = 900; f.initial.aimOrigin524.x = 901;
    f.actual.visibilityTarget = target(); f.snapshot();
    check(f.actual.pos === pos && f.actual.savedGroundPos === old && f.actual.targetCache5e8 === older &&
      f.actual.aimOrigin518 === aim, 'existing vectors are actual shared stores, never replaced');
    check(older.x === 1 && older.y === 2 && older.z === 3 && old.x === 10 && old.y === 20 && old.z === 30,
      'older receives old position before old receives current position');
    check(state.rotation76.x === -32768 && state.rotation76.y === -1 && state.rotation76.z === 32767 &&
      state.preRotation1d6a.x === -32768 && state.preRotation1d6a.y === 4 && state.preRotation1d6a.z === 32767 &&
      state.previousStepHeight6d4 === 7 && state.aimOrigin524.z === 300, 'all current actual fields copied');
    pos.x = 40; pos.y = 50; pos.z = 60; f.actual.bodyPitch = 1; f.actual.heading = 0x8001;
    f.worldState.roll74 = -32768; Object.assign(f.worldState.preRotation1d64, vec(11, 12, 13));
    f.actual.stepHeight = -8; aim.x = 400;
    check(state.rotation76.x === -32768 && old.x === 10 && state.aimOrigin524.x === 100, 'current mutations do not auto-snapshot');
    f.snapshot();
    check(older.x === 10 && older.y === 20 && older.z === 30 && old.x === 40 && old.y === 50 && old.z === 60 &&
      state.rotation76.x === 1 && state.rotation76.y === -32767 && state.rotation76.z === -32768 &&
      state.preRotation1d6a.z === 13 && state.previousStepHeight6d4 === -8 && state.aimOrigin524.x === 400,
      'repeated explicit snapshots consume live actual owners without deduplication');
    f.snapshot(); check(older.x === 40, 'same-state third call still advances history');
    check(!Reflect.set(state, 'rotation76', vec(0)) && !Reflect.set(state, 'preRotation1d6a', vec(0)) &&
      !Reflect.set(state, 'aimOrigin524', vec(0)), 'historical destination records cannot be replaced');
  }
  {
    const f = fixture(), original = f.worldState.preRotation1d64;
    const descriptor = Object.getOwnPropertyDescriptor(f.worldState, 'preRotation1d64');
    check(descriptor?.writable === false && descriptor.configurable === false,
      'actual world owner seals the non-writable pre-rotation record reference');
    check(!Reflect.set(f.worldState, 'preRotation1d64', vec(99)) &&
      !Reflect.defineProperty(f.worldState, 'preRotation1d64', {value: vec(99)}),
      'neither assignment nor property redefinition can replace the actual pre-rotation owner');
    original.y = 123; f.snapshot();
    check(f.worldState.preRotation1d64 === original && f.state().preRotation1d6a.y === 123 &&
      f.state().previousStepHeight6d4 === 7, 'same owned pre-rotation record remains live after blocked replacement');
    // Deleting the history reader's additional pre-rotation identity guard is
    // unreachable through this actual world's supported owner API. Do not
    // fabricate a writable provider merely to claim a mutation kill.
  }
  {
    const f = fixture(); f.worldState.mode4a0 = NaN; f.worldState.mode4a1 = NaN; f.worldState.flags48a = NaN;
    f.actual.visibilityBit = NaN; f.actual.aimOrigin518.x = NaN; f.snapshot();
    check(f.state().previousStepHeight6d4 === 7 && f.state().aimOrigin524.x === -101,
      'null target skips masks/aim after full transform prefix, with no matrix mode gate');
  }
  for (const value of [1, 127, 128, 255]) {
    const f = fixture(); f.actual.visibilityTarget = target(value, NaN); f.actual.visibilityBit = NaN;
    f.snapshot(); check(f.state().aimOrigin524.x === 100, `nonzero signed target83 ${value} skips both masks`);
  }
  for (const [mask, bit, copies] of [[0, 0, false], [1, 2, false], [0x80, 0x80, true], [0xff, 0x80, true], [0x7f, 0x80, false]]) {
    const f = fixture(); f.actual.visibilityTarget = target(0, mask as number); f.actual.visibilityBit = bit as number;
    f.snapshot(); check(f.state().aimOrigin524.x === (copies ? 100 : -101), 'target and source signed-byte mask semantics');
  }
  {
    const f = fixture(); f.actual.visibilityTarget = target(0, 0x80); f.snapshot();
    f.actual.aimOrigin518.x = 500; f.actual.visibilityTarget = target(0, 0x7f); f.snapshot();
    check(f.state().aimOrigin524.x === 100, 'changed target association is read on each call');
    f.actual.visibilityTarget = null; f.actual.aimOrigin518.x = 600; f.snapshot();
    check(f.state().aimOrigin524.x === 100, 'changed association can become null');
    f.actual.visibilityTarget = target(255, 0); f.snapshot();
    check(f.state().aimOrigin524.x === 600, 'new actual target does not require a matrix-owner identity');
  }
  {
    const f = fixture(); let called = false;
    const t = target(); Object.defineProperty(t, 'visibilityMask5e6', {get() {called = true; throw Error('unused mask');}});
    Object.defineProperty(t, 'controlWord', {get() {called = true; throw Error('unused control');}});
    Object.defineProperty(f.actual, 'visibilityBit', {get() {called = true; throw Error('unused bit');}});
    f.actual.visibilityTarget = t; f.snapshot();
    check(!called && f.state().aimOrigin524.z === 300, 'unused fields are not read or validated');
  }
  {
    const f = fixture(); f.actual.visibilityTarget = target(0, 0); let called = false;
    Object.defineProperty(f.actual.aimOrigin518, 'x', {get() {called = true; throw Error('unused aim');}});
    Object.freeze(f.state().aimOrigin524); f.snapshot();
    check(!called && f.state().previousStepHeight6d4 === 7, 'mask miss skips aim source and destination checks');
  }
  for (const value of [-0, 0, 2 ** -149, -(2 ** -149), Math.fround(3.4028235e38), Math.fround(-3.4028235e38), 1.25]) {
    const f = fixture(); Object.assign(f.actual.savedGroundPos, vec(value)); Object.assign(f.actual.pos, vec(value));
    Object.assign(f.actual.aimOrigin518, vec(value)); f.actual.stepHeight = value; f.actual.visibilityTarget = target(); f.snapshot();
    check(Object.is(f.actual.targetCache5e8.x, value) && Object.is(f.actual.savedGroundPos.y, value) &&
      Object.is(f.state().previousStepHeight6d4, value) && Object.is(f.state().aimOrigin524.z, value),
      'raw finite-f32 copies preserve exact bits including signed zero and subnormal');
  }
  for (const [bits, signed] of [[0, 0], [1, 1], [32767, 32767], [32768, -32768], [65535, -1]]) {
    const f = fixture(); f.actual.bodyPitch = bits!; f.actual.heading = bits!; f.worldState.roll74 = signed!;
    Object.assign(f.worldState.preRotation1d64, vec(signed!)); f.snapshot();
    check(f.state().rotation76.x === signed && f.state().rotation76.y === signed && f.state().rotation76.z === signed &&
      f.state().preRotation1d6a.x === signed, 'BAM16 bits and signed-short bounds');
  }
  {
    const f = fixture(true); Object.assign(f.initial.rotation76, vec(-0)); Object.assign(f.initial.preRotation1d6a, vec(-0));
    f.bind(); check(Object.is(f.state().rotation76.x, 0) && Object.is(f.state().preRotation1d6a.y, 0),
      'initial signed-short negative zero normalizes to integer zero');
    f.actual.bodyPitch = -0; f.actual.heading = -0; f.worldState.roll74 = -0;
    Object.assign(f.worldState.preRotation1d64, vec(-0)); f.snapshot();
    check(Object.is(f.state().rotation76.x, 0) && Object.is(f.state().rotation76.y, 0) && Object.is(f.state().rotation76.z, 0) &&
      Object.is(f.state().preRotation1d6a.x, 0) && Object.is(f.state().preRotation1d6a.y, 0) && Object.is(f.state().preRotation1d6a.z, 0),
      'source integer short fields cannot retain floating negative zero');
  }
  for (const bad of [NaN, Infinity, -Infinity, 0.1]) {
    const f = fixture(); f.actual.savedGroundPos.y = bad;
    rejects(f.snapshot, 'finite exact source float32');
    check(f.actual.targetCache5e8.x === -1 && f.actual.targetCache5e8.y === -2,
      'older-position X/Y are both read before either word is stored');
  }
  {
    const f = fixture(); f.actual.savedGroundPos.z = NaN; rejects(f.snapshot, 'finite exact source float32');
    check(f.actual.targetCache5e8.x === 1 && f.actual.targetCache5e8.y === 2 && f.actual.targetCache5e8.z === -3 &&
      f.actual.savedGroundPos.x === 1, 'late older Z failure retains XY and precedes current-position loads');
  }
  {
    const f = fixture(); f.actual.pos.y = NaN; rejects(f.snapshot, 'finite exact source float32');
    check(f.actual.targetCache5e8.z === 3 && f.actual.savedGroundPos.x === 1 && f.state().rotation76.x === 101,
      'current XY source refusal retains all older stores but no saved-position stores');
  }
  {
    const f = fixture(); f.actual.pos.z = NaN; rejects(f.snapshot, 'finite exact source float32');
    check(f.actual.savedGroundPos.x === 10 && f.actual.savedGroundPos.y === 20 && f.actual.savedGroundPos.z === 3,
      'current Z source refusal preserves completed saved XY');
  }
  for (const bad of [-1, 65536, 1.5, NaN]) {
    const f = fixture(); f.actual.heading = bad; rejects(f.snapshot, 'heading: integer');
    check(f.actual.savedGroundPos.z === 30 && f.state().rotation76.x === 101 && f.state().rotation76.y === 102,
      'one rotation word loads both BAM16 halves before stores');
  }
  for (const bad of [-32769, 32768, 0.5, NaN]) {
    const f = fixture(); f.worldState.preRotation1d64.y = bad; rejects(f.snapshot, 'y: integer');
    check(f.state().rotation76.z === 32767 && f.state().preRotation1d6a.x === 104 && f.state().preRotation1d6a.y === 105,
      'one pre-rotation word loads both signed halves before stores');
  }
  for (const field of ['rotation76', 'preRotation1d6a'] as const) {
    const f = fixture(); Object.defineProperty(f.state()[field], 'y', {writable: false});
    rejects(f.snapshot, 'non-writable');
    check(f.state()[field].x === (field === 'rotation76' ? 101 : 104) && f.state()[field].z === (field === 'rotation76' ? 103 : 106),
      'one paired-short stw validates both destination halves before either store');
  }
  for (const field of ['rotation76', 'preRotation1d6a'] as const) {
    const f = fixture(); Object.defineProperty(f.state()[field], 'z', {writable: false});
    rejects(f.snapshot, 'non-writable');
    check(f.state()[field].x === -32768 && f.state()[field].y === (field === 'rotation76' ? -1 : 4) &&
      f.state()[field].z === (field === 'rotation76' ? 103 : 106), 'separate halfword refusal preserves earlier paired-word store');
  }
  {
    const f = fixture(); f.worldState.roll74 = 32768; rejects(f.snapshot, 'roll74: integer');
    check(f.state().rotation76.x === -32768 && f.state().rotation76.y === -1 && f.state().rotation76.z === 103 &&
      f.state().preRotation1d6a.x === 104, 'invalid roll is reached after paired rotation store');
  }
  {
    const f = fixture(); f.worldState.preRotation1d64.z = 32768; rejects(f.snapshot, 'z: integer');
    check(f.state().preRotation1d6a.x === -32768 && f.state().preRotation1d6a.y === 4 && f.state().preRotation1d6a.z === 106 &&
      f.state().previousStepHeight6d4 === 107, 'invalid pre-rotation Z preserves pair and precedes height');
  }
  for (const field of ['targetCache5e8', 'savedGroundPos'] as const) {
    const f = fixture(); Object.defineProperty(f.actual[field], 'y', {writable: false}); rejects(f.snapshot, 'non-writable');
    check(f.actual[field].x === (field === 'targetCache5e8' ? 1 : 10) && f.actual[field].y === (field === 'targetCache5e8' ? -2 : 2) &&
      f.actual[field].z === (field === 'targetCache5e8' ? -3 : 3), 'separate vector stw validates each destination at its store');
  }
  for (const fault of ['source', 'destination'] as const) {
    const f = fixture();
    if (fault === 'source') f.actual.stepHeight = NaN;
    else Object.defineProperty(f.state(), 'previousStepHeight6d4', {writable: false});
    rejects(f.snapshot, fault === 'source' ? 'stepHeight' : 'non-writable');
    check(f.state().preRotation1d6a.z === 32767 && f.state().previousStepHeight6d4 === 107,
      'late height refusal retains all transform stores and does not fabricate a value');
  }
  for (const key of ['eligibility83', 'visibilityMask5e6'] as const) {
    const f = fixture(); const t = target(0, 0x80); t[key] = 256; f.actual.visibilityTarget = t;
    rejects(f.snapshot, `${key}: integer`); check(f.state().previousStepHeight6d4 === 7 && f.state().aimOrigin524.x === -101,
      'visibility refusal comes after entire transform prefix');
  }
  {
    const f = fixture(); f.actual.visibilityTarget = target(0, 0); f.actual.visibilityBit = NaN;
    rejects(f.snapshot, 'visibilityBit: integer'); check(f.state().previousStepHeight6d4 === 7,
      'zero target mask still loads source visibility before and-test');
  }
  {
    const f = fixture(); f.actual.visibilityTarget = target(0, NaN);
    Object.defineProperty(f.actual, 'visibilityBit', {get() {throw Error('must not read accessor');}});
    rejects(f.snapshot, 'visibilityMask5e6: integer'); check(f.state().aimOrigin524.x === -101, 'target mask read precedes source visibility');
  }
  for (const fault of ['source-y', 'source-z', 'destination-y'] as const) {
    const f = fixture(); f.actual.visibilityTarget = target();
    if (fault === 'destination-y') Object.defineProperty(f.state().aimOrigin524, 'y', {writable: false});
    else f.actual.aimOrigin518[fault === 'source-y' ? 'y' : 'z'] = NaN;
    rejects(f.snapshot, fault === 'destination-y' ? 'non-writable' : 'finite exact source float32');
    check(f.state().previousStepHeight6d4 === 7 && f.state().aimOrigin524.x === (fault === 'source-y' ? -101 : 100) &&
      f.state().aimOrigin524.y === (fault === 'source-z' ? 200 : -102) && f.state().aimOrigin524.z === -103,
      'aim paired source reads, separate stores and late Z preserve exact prefix');
  }
  {
    const f = fixture(); Object.freeze(f.actual.savedGroundPos); rejects(f.snapshot, 'non-writable');
    check(f.actual.targetCache5e8.z === 3 && f.actual.savedGroundPos.x === 1, 'readonly source accepted until used as reached destination');
  }
  {
    const f = fixture(); f.actual.pos = vec(99); rejects(f.snapshot, 'pos owner changed');
    check(f.actual.targetCache5e8.z === 3 && f.actual.savedGroundPos.x === 1, 'replaced current vector fails only after older-position copy');
  }
  {
    const f = fixture(); f.actual.aimOrigin518 = vec(99); f.snapshot();
    f.actual.visibilityTarget = target(); rejects(f.snapshot, 'aimOrigin518 owner changed');
    check(f.state().previousStepHeight6d4 === 7 && f.state().aimOrigin524.x === -101, 'replaced aim record is checked only on reached aim branch');
  }
  for (const key of ['savedGroundPos', 'targetCache5e8'] as const) {
    const f = fixture(); const original = f.actual.targetCache5e8; f.actual[key] = vec(99);
    rejects(f.snapshot, `${key} owner changed`); check(original.x === -1 && f.actual.pos.x === 10, 'replaced position-history owner is never silently adopted');
  }
  {
    const f = fixture(); f.hooks.replaceActual = true; rejects(f.snapshot, 'actual RomActor owner changed');
    check(f.actual.targetCache5e8.x === -1, 'changed actual owner fails before writes');
  }
  {
    const f = fixture(); f.hooks.replaceWorld = true; rejects(f.snapshot, 'world owner changed');
    check(f.actual.savedGroundPos.z === 30 && f.state().rotation76.y === -1 && f.state().rotation76.z === 103,
      'world owner is consumed only at roll after earlier completed actual-field stores');
  }
  {
    const f = fixture(); let calls = 0;
    f.hooks.actual = () => {if (++calls === 2) {f.actual.savedGroundPos.y = 99; f.actual.savedGroundPos.z = 88;}};
    f.snapshot(); check(f.actual.targetCache5e8.y === 2 && f.actual.targetCache5e8.z === 88,
      'guarded destination-owner adapter observes XY already loaded and Z not yet loaded');
  }
  {
    const f = fixture(); let calls = 0;
    f.hooks.actual = () => {if (++calls === 3) Object.defineProperty(f.actual.targetCache5e8, 'y', {writable: false});};
    rejects(f.snapshot, 'non-writable'); check(f.actual.targetCache5e8.x === 1 && f.actual.targetCache5e8.y === -2,
      'late destination readonly change at adapter boundary preserves prior word store');
  }
  {
    const f = fixture(); f.adapter.getActualActor = () => {throw Error('must use captured actual method');};
    f.adapter.getActorBinding = () => {throw Error('must use captured world method');};
    f.sources.world = {getActualActor: unexpected, getActorBinding: unexpected};
    function unexpected(): never {throw Error('must use captured source receiver');}
    f.snapshot(); check(f.state().previousStepHeight6d4 === 7, 'source object and methods captured at creation with original receiver');
  }
  {
    const f = fixture(); f.hooks.world = () => {try {f.snapshot();} catch { /* caught hostile adapter reentry */ }};
    rejects(f.snapshot, 'caught same-runtime reentry');
    check(f.state().rotation76.y === -1 && f.state().rotation76.z === 103 && f.state().previousStepHeight6d4 === 107,
      'caught reentry aborts after completed actual prefix, before world field consumption');
    delete f.hooks.world; f.snapshot(); check(f.state().previousStepHeight6d4 === 7, 'later fresh call works after reentry refusal');
  }
  {
    const f = fixture(true); f.hooks.actual = () => {try {f.bind();} catch { /* caught bind reentry */ }};
    rejects(f.bind, 'caught same-runtime reentry'); rejects(f.state, 'unknown/non-owned');
    delete f.hooks.actual; f.bind(); f.snapshot(); check(f.state().previousStepHeight6d4 === 7, 'failed reentrant binding never registers partial owner');
  }
  {
    const f = fixture(); let invoked = false;
    Object.defineProperty(f.actual.savedGroundPos, 'x', {get() {invoked = true; return 1;}});
    rejects(f.snapshot, 'own data property'); check(!invoked && f.actual.targetCache5e8.x === -1, 'accessors rejected without invocation, no fabricated getter/proxy support');
  }
  {
    const f = fixture(true); f.actual.savedGroundPos = f.actual.pos;
    rejects(f.bind, 'aliased transform owner'); rejects(f.state, 'unknown/non-owned');
  }
  {
    const f = fixture(), other = f.addActor(); other.actual.savedGroundPos = f.actual.savedGroundPos;
    rejects(() => f.runtime.bindActor(other.id, f.initial), 'aliased transform owner');
    check(f.state().rotation76.x === 101, 'cross-actor aliases rejected without changing existing state');
  }
  {
    const f = fixture(), other = f.addActor(); f.runtime.bindActor(other.id, f.initial);
    f.runtime.snapshotActor(other.id); check(f.state().rotation76.x === 101 && f.runtime.getActorBinding(other.id).rotation76.x === -32768,
      'independent actor owners keep independent missing history');
    rejects(f.bind, 'already bound'); rejects(() => f.runtime.snapshotActor(Symbol('unknown')), 'unknown/non-owned');
  }
  {
    const f = fixture(true); f.initial.rotation76.x = 32768; rejects(f.bind, 'integer out of bounds');
    rejects(f.state, 'unknown/non-owned'); f.initial.rotation76.x = 101; f.bind();
    check(f.state().rotation76.x === 101, 'initial signed history explicitly required, failed validation not registered');
  }
  {
    const f = fixture(true); f.actual.savedGroundPos.x = NaN; f.actual.bodyPitch = NaN; f.actual.stepHeight = NaN;
    f.bind(); check(f.state().rotation76.x === 101, 'bind captures current owner identities without eager current-value reads');
    rejects(f.snapshot, 'finite exact source float32');
  }
}
