import {flatHalfPrimaryMode0, flatHalfPrimaryWitnesses} from './actor-primary-flat-half-witness.selftest.js';
import {slopedPrimaryWitnesses, slopedPrimaryOrientation} from './actor-primary-sloped-witness.selftest.js';
import {hitBin, sourceTerrainGrid} from '@gf/formats';
import {createRomActor} from './actor.js';
import {createSourceActorWorldMatrixRuntime, type SourceActorWorldMatrixBinding,
  type SourceActorWorldMatrixStorage, type SourceActorCorrectedTraversalState} from './actor-world-matrix.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import {createSourceActorTerrainQueryRuntime} from './actor-terrain-query.js';
import {createSourceActorTransformHistoryRuntime} from './actor-transform-history.js';
import {createSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
import {createSourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-world-matrix-test] ${why}`);}
function rejects(run: () => void, text: string): void {
  let message = ''; try {run();} catch (e) {message = String(e);}
  check(message.includes(text), `expected ${text}, got ${message}`);
}
const zero = () => ({x: 0, y: 0, z: 0}), unit = () => ({x: 1, y: 1, z: 1});
function fixture(count = 6, maxVisits = 4096) {
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const unexpected = (): never => {throw Error('fixture does not animate or convert poses during matrix refresh');};
  const mapping = createSourceActorJointMappingRuntime(joints, feedback,
    {interpretAObj: unexpected, animateRObjs: unexpected, animateDObjs: unexpected}, {convertEulerToQuaternion: unexpected});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0})));
  // Explicit fixture poses, not inferred from a renderer/JObj or initialized by
  // the producer. The parent integration separately exercises captured poses.
  const poses = Array.from({length: 2}, (_, bank) => Array.from({length: count}, (_, j) => feedback.createPose({
    translation: {x: j + 100 * bank, y: 2 * j + 100 * bank, z: 3 * j + 100 * bank},
    quaternion: {x: 0, y: 0, z: 0, w: 1},
  })));
  const id = mapping.createActor({descriptor4b0: null, jointCount1d90: count, boundary1d91: 0,
    boundary1d92: 0, boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses});
  const matrices = createSourceActorJointMatrixRuntime(feedback), actual = createRomActor();
  actual.pos.x = 10; actual.pos.y = 20; actual.pos.z = 30; actual.stepHeight = 7;
  const matrixIds = Array.from({length: count}, (_, j) => matrices.createMatrix(
    [1, 0, 0, -10 - j, 0, 1, 0, -20 - j, 0, 0, 1, -30 - j]));
  const copy114 = matrices.createMatrix(Array(12).fill(91)), copy1aa4 = matrices.createMatrix(Array(12).fill(92));
  const scratch = matrices.createMatrix(Array(12).fill(93));
  const input: SourceActorWorldMatrixBinding = {mode4a0: 0, mode4a1: 0, flags48a: 0, mask1d70: 0xffffffff,
    roll74: 0, yawOffset6b8: 0, scale58: unit(), offset1dbc: {x: 4, y: 5, z: 6},
    adjusted1d54: {x: 81, y: 82, z: 83}, preRotation1d64: zero()};
  const rows = Array.from({length: count}, () => [255, 255, 87, 88]);
  if (count >= 6) {
    rows[0]![0] = 1; rows[1]![0] = 2; rows[1]![1] = 3;
    rows[3]![0] = 4; rows[2]![1] = 5;
  }
  const storageInput: SourceActorWorldMatrixStorage = {matrices8d4: matrixIds, copy114, copy1aa4, scratch,
    topology1994: rows, corrections18d4: Array.from({length: count}, zero), scales15d4: Array.from({length: count}, unit)};
  const events: string[] = [], hooks: {pose?: () => void; matrix?: (matrix: symbol) => void; effect?: () => unknown; mapping?: () => void;
    composed?: (destination: symbol) => unknown; copied?: () => unknown; transformed?: () => unknown; oriented?: () => unknown;
    placed?: (destination: symbol) => unknown} = {};
  const mappingAdapter = {
    getActor(actor: symbol) {check(this === mappingAdapter, 'mapping receiver'); hooks.mapping?.(); return mapping.getActor(actor);},
    getLayout(actor: symbol) {check(this === mappingAdapter, 'layout receiver'); return mapping.getLayout(actor);},
  };
  const feedbackAdapter = {getPose(pose: symbol) {
    check(this === feedbackAdapter, 'feedback receiver'); hooks.pose?.(); return feedback.getPose(pose);
  }};
  const matrixAdapter = {...matrices,
    getMatrix(matrix: symbol) {check(this === matrixAdapter, 'matrix receiver'); hooks.matrix?.(matrix); return matrices.getMatrix(matrix);},
    identity(matrix: symbol) {check(this === matrixAdapter, 'identity receiver'); events.push('identity'); matrices.identity(matrix); return hooks.effect?.() as void;},
    translate(...args: Parameters<typeof matrices.translate>) {check(this === matrixAdapter, 'translate receiver'); events.push('translate'); matrices.translate(...args);},
    correctShort(...args: Parameters<typeof matrices.correctShort>) {check(this === matrixAdapter, 'correct receiver'); events.push('correct'); matrices.correctShort(...args);},
    scale(...args: Parameters<typeof matrices.scale>) {check(this === matrixAdapter, 'scale receiver'); events.push('scale'); matrices.scale(...args);},
    copy(...args: Parameters<typeof matrices.copy>) {check(this === matrixAdapter, 'copy receiver'); events.push(args[1] === copy114 ? 'copy114' : args[1] === copy1aa4 ? 'copy1aa4' : `copy:${matrixIds.indexOf(args[0])}`); matrices.copy(...args); return hooks.copied?.() as void;},
    rotateShort(...args: Parameters<typeof matrices.rotateShort>) {check(this === matrixAdapter, 'rotate receiver'); events.push(`rotate:${args[0]}`); matrices.rotateShort(...args);},
    composePose(...args: Parameters<typeof matrices.composePose>) {
      check(this === matrixAdapter, 'composePose receiver');
      events.push(`joint:${matrixIds.indexOf(args[1])}:${args[0] === scratch ? 'scratch' : matrixIds.indexOf(args[0])}`);
      matrices.composePose(...args); return hooks.composed?.(args[1]) as void;
    },
    transformPoint(...args: Parameters<typeof matrices.transformPoint>) {
      check(this === matrixAdapter, 'transformPoint receiver'); events.push(`transform:${matrixIds.indexOf(args[0])}`);
      matrices.transformPoint(...args); return hooks.transformed?.() as void;
    },
    orientTerrainMatrix(...args: Parameters<typeof matrices.orientTerrainMatrix>) {
      check(this === matrixAdapter, 'orientTerrainMatrix receiver'); events.push(`orient:${matrixIds.indexOf(args[0])}:${args[2]}:${args[3]}`);
      matrices.orientTerrainMatrix(...args); return hooks.oriented?.() as void;
    },
    primaryFoldedPlacement(...args: Parameters<typeof matrices.primaryFoldedPlacement>) {
      check(this === matrixAdapter, 'primaryFoldedPlacement receiver');
      events.push(`primary:${matrixIds.indexOf(args[1])}:${matrixIds.indexOf(args[0])}`);
      matrices.primaryFoldedPlacement(...args); return hooks.placed?.(args[1]) as void;
    },
    composeJoint(...args: Parameters<typeof matrices.composeJoint>) {
      check(this === matrixAdapter, 'compose receiver');
      events.push(`joint:${matrixIds.indexOf(args[1])}:${args[0] === scratch ? 'scratch' : matrixIds.indexOf(args[0])}`);
      matrices.composeJoint(...args);
    },
  };
  const sources = {mapping: mappingAdapter, feedback: feedbackAdapter, matrices: matrixAdapter};
  const runtime = createSourceActorWorldMatrixRuntime(sources, maxVisits);
  runtime.bindActor(id, actual, input, storageInput);
  const state = runtime.getActorBinding(id), storage = runtime.getStorage(id);
  const topology = (index: number): number[] => storage.topology1994[index] as number[];
  const output = (index: number): number[] => matrices.getMatrix(matrixIds[index]!);
  const pose = (index: number, bank = 0) => feedback.getPose(poses[bank]![index]!);
  return {runtime, matrices, mapping, feedback, actual, id, input, storageInput, state, storage, topology, output, pose,
    matrixIds, poses, events, hooks, sources, mappingAdapter, feedbackAdapter, matrixAdapter,
    update: () => runtime.updateActor(id)};
}
// A copy target deliberately has no poses, topology, correction or scale slots.
// 47a2c must never try to prepare or rebuild it.
function copyTarget(f: ReturnType<typeof fixture>, count = 6) {
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => f.mapping.createPart(
    {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0})));
  const id = f.mapping.createActor({...f.mapping.getActor(f.id), jointCount1d90: 0}, {parts, poses: [[], []]});
  const slots = Array.from({length: count}, () => f.matrices.createMatrix(Array(12).fill(51)));
  const storage: SourceActorWorldMatrixStorage = {matrices8d4: slots,
    copy114: f.matrices.createMatrix(Array(12).fill(52)), copy1aa4: f.matrices.createMatrix(Array(12).fill(53)),
    scratch: f.matrices.createMatrix(Array(12).fill(54)), topology1994: [], corrections18d4: [], scales15d4: []};
  f.runtime.bindActor(id, createRomActor(), f.input, storage);
  return {id, storage, output: (i: number) => f.matrices.getMatrix(slots[i]!)};
}
// Explicit source cells, including one actual flat floor triangle. The helper
// owns synthetic source bytes; no StageCollision or normal-success callback.
function correctionLayer(offset: sourceTerrainGrid.SourceTerrainLayerOffset, floor: boolean, normal = {x: 0, y: 1, z: 0}) {
  const recordBase = 0x54, bytes = new Uint8Array(recordBase + (floor ? 0x38 : 0));
  const view = new DataView(bytes.buffer), word = (at: number, value: number) => view.setUint32(at, value, false);
  word(0, 0x53544948); word(4, bytes.length); word(8, 500); word(12, 500); word(16, 2); word(20, 2);
  word(0x20, 0x20); word(0x24, recordBase - 8);
  for (let i = 0; i < 4; i++) word(0x28 + i * 4, (floor && i === 0 ? 0x38 : 0x3c) - 8);
  word(0x38, floor ? 0 : 0xffffffff); word(0x3c, 0xffffffff);
  if (floor) {
    word(recordBase, 7);
    [0, 0, 0, 0, -500 * normal.z / normal.y, 500, 500, -500 * normal.x / normal.y, 0, normal.x, normal.y, normal.z, NaN].forEach((value, i) => view.setFloat32(recordBase + 4 + i * 4, value, false));
  }
  return sourceTerrainGrid.createSourceTerrainGrid(bytes, hitBin.parseStageHitGrid(bytes), offset);
}
function terrainCorrectionFixture(f: ReturnType<typeof fixture>, bind = true, normal = {x: 0, y: 1, z: 0}) {
  const unsupported = (): never => {throw Error('unrelated animation/setup effect was reached');};
  const dispatch = createSourceActorAnimationDispatchRuntime(f.mapping, f.feedback);
  dispatch.bindActor(f.id, {family1d88: null, shared1d8c: null, marker578: 0, marker1db3: 0});
  const targets = createSourceStreamWaitTargetRuntime(f.mapping, f.feedback, dispatch);
  targets.bindActor(f.id, Array.from({length: 4}, () => ({target08: 0, previous0c: 0, accumulator10: 0})));
  const waits = createSourceStreamWaitRuntime({mapping: f.mapping, feedback: f.feedback, dispatch, targets});
  waits.bindActor(f.id, {activeMask579: 0, blockedMask1d9a: 0, marker71d: 0},
    Array.from({length: 4}, () => ({current00: null, wait14: 0, finished1a: 0, event1e: 0})));
  waits.bindStartActor(f.id, {familyBank1d80: null, sharedBank1d84: null, defaultSelector582: 0, marker709: 0});
  const setup = createSourceActorAnimationSetupRuntime({mapping: f.mapping, feedback: f.feedback, dispatch,
    descriptors: createSourceAnimationDescriptorBankRuntime(), starts: waits,
    metadata: {getPartBinding: unsupported, applyMetadata: unsupported}, archiveBanks: {resolveArchive: unsupported}});
  setup.bindActor(f.id, {familyBank1d78: null, sharedBank1d7c: null, movement6d8: 1});
  const movement = createSourceActorMovementFollowupRuntime({mapping: f.mapping, waits, setup, matrixOwner: f.matrices});
  movement.bindActor(f.id, f.actual, {byte661: 0, field66c: 0, field670: 0});
  movement.bindWorldMatrices(f.id, f.matrixIds);
  const history = createSourceActorTransformHistoryRuntime({world: f.runtime});
  history.bindActor(f.id, {rotation76: zero(), preRotation1d6a: zero(), previousStepHeight6d4: 0, aimOrigin524: zero()});
  const terrain = createSourceActorTerrainQueryRuntime({world: f.runtime, history,
    terrain: {floor1c: correctionLayer(0x1c, true, normal), ceiling20: correctionLayer(0x20, false),
      ceiling24: correctionLayer(0x24, false), upper34: 100, lower68: -100}});
  terrain.bindActor(f.id);
  const hooks: {movement?: () => void; normal?: () => void; replaceMovement?: boolean; result?: unknown} = {};
  const movementAdapter = {getActorBinding(id: symbol) {
    check(this === movementAdapter, 'terrain movement receiver'); f.events.push('movement'); hooks.movement?.();
    const actual = movement.getActorBinding(id); return hooks.replaceMovement ? {...actual} : actual;
  }};
  const terrainAdapter = {queryNormal8003de80(...args: Parameters<typeof terrain.queryNormal8003de80>): 0 | 1 {
    check(this === terrainAdapter, 'terrain normal receiver'); f.events.push(`normal:${args[2]}`);
    const result = terrain.queryNormal8003de80(...args); hooks.normal?.();
    return (hooks.result === undefined ? result : hooks.result) as 0 | 1;
  }};
  const sources = {movement: movementAdapter, terrain: terrainAdapter};
  if (bind) f.runtime.bindTerrainCorrectionSources(f.id, sources);
  f.events.length = 0;
  return {movement, history, terrain, sources, movementAdapter, terrainAdapter, hooks, state: movement.getActorBinding(f.id)};
}
const primarySlot = (joint0c: number) => ({x: NaN, y: NaN, z: NaN, joint0c, axis0d: NaN, axis0e: NaN, bend0f: NaN});
const secondarySlot = (joint00: number, axis01 = 2, axis02 = 1) => ({joint00, axis01, axis02, padding03: NaN});
function bindSecondary(f: ReturnType<typeof fixture>, joint = 1) {
  const counts = {count1d96: 0, count1d97: 1, secondary1a94: [secondarySlot(joint)]};
  f.runtime.bindCorrectedTraversalState(f.id, counts); return counts;
}
// Start with an actual mode0 rebuild: raw joint1Y10 plus offset-2 gives
// retained positions28,30,30.5. Mode1 raw transform instead produces30; the
// explicit primary target31 therefore supplies precisely +Y1. The two old
// lengths are2/.5. No orientation or placement success is fabricated here.
function primaryFixture(maxVisits = 4096) {
  const f = fixture(8, maxVisits);
  Object.assign(f.state.offset1dbc, {x: 0, y: -2, z: 0});
  for (let i = 0; i < 8; i++) {
    Object.assign(f.pose(i).translation, {x: 0, y: i, z: 0});
    f.topology(i)[0] = 255; f.topology(i)[1] = 255;
  }
  f.pose(1).translation.y = 10; f.pose(2).translation.y = 2; f.pose(3).translation.y = 0.5;
  f.topology(0)[0] = 1; f.topology(1)[0] = 2; f.topology(1)[1] = 4;
  f.topology(2)[0] = 3; f.topology(2)[1] = 6;
  f.topology(4)[0] = 5; f.topology(6)[0] = 7;
  f.runtime.prepareActor(f.id); f.runtime.rebuildActor(f.id, 0);
  const counts = {count1d96: 1, count1d97: 0,
    primary1a14: [{x: 10, y: 31, z: 30, joint0c: 3, axis0d: 2, axis0e: 1, bend0f: 1}]};
  f.runtime.bindCorrectedTraversalState(f.id, counts); f.events.length = 0;
  return {...f, counts, placement: counts.primary1a14[0]!};
}
export function runActorWorldMatrixSelfTests(): void {
  runActorWorldSlopedPrimaryPlacementSelfTests();
  runActorWorldFlatHalfPrimaryPlacementSelfTests();
  runActorWorldSlopedTerrainContinuationSelfTests();
  {
    const f = fixture();
    check(f.runtime.getWorldMatrix(f.id, 0) === f.output(0), 'world lookup returns actual full record without copying');
    f.output(0)[3] = NaN;
    check(f.runtime.getWorldMatrix(f.id, 0) === f.output(0) && f.events.length === 0, 'world lookup does not eagerly read elements or rebuild');
    rejects(() => f.runtime.getWorldMatrix(f.id, -1), 'addressing outside');
    rejects(() => f.runtime.getWorldMatrix(f.id, 6), 'addressing outside');
    f.hooks.matrix = () => {try {f.runtime.getWorldMatrix(f.id, 0);} catch { /* caught reentry */ }};
    rejects(() => f.runtime.getWorldMatrix(f.id, 0), 'caught same-runtime reentry');
  }

  {
    const f = fixture(); f.update();
    check(f.events.join(',') === 'identity,translate,correct,scale,copy114,copy1aa4,rotate:z,rotate:x,rotate:y,joint:1:scratch,correct,scale,joint:3:0,joint:4:3,joint:2:1,joint:5:1',
      'source root order, mandatory joint1 wrappers, recursive incoming parent and continuation current parent');
    check(f.output(0)[3] === 10 && f.output(0)[7] === 20 && f.output(0)[11] === 30, 'root actual position');
    check(f.output(1)[3] === 15 && f.output(1)[7] === 27 && f.output(1)[11] === 39, 'joint1 special translation');
    check(f.output(3)[7] === 26 && f.output(4)[7] === 34 && f.output(2)[7] === 31 && f.output(5)[7] === 37, 'actual multi-branch matrix results');
    check(f.matrices.getMatrix(f.storage.copy114)[7] === 20 && f.matrices.getMatrix(f.storage.copy1aa4)[7] === 27, 'root copy then separate lifted copy');
    check(f.actual.stepHeight === 7, 'producer consumes, does not change movement height');
  }
  {
    const f = fixture();
    f.state.scale58.x = 2; f.state.scale58.y = 3; f.state.scale58.z = 4;
    f.storage.scales15d4[1]!.y = 2; f.update();
    check(f.output(0)[0] === 2 && f.output(0)[5] === 3 && f.output(0)[10] === 4, 'source root scale');
    check(f.output(1)[3] === 20 && f.output(1)[7] === 41 && f.output(1)[11] === 66 && f.output(1)[5] === 6,
      'root scaled translation with separate joint scale');
  }
  {
    const f = fixture(); f.state.mask1d70 = 0xfffffffd; f.update();
    check(!f.events.some(v => v.startsWith('rotate:')) && !f.events.some(v => v.startsWith('joint:1:')), 'mask disables matrix update only');
    check(f.output(1)[7] === -21 && f.output(3)[7] === 26 && f.output(4)[7] === 34 && f.output(2)[7] === -17 && f.output(5)[7] === -11,
      'disabled joint still visits branch and continuation; continuation consumes stale disabled-parent matrix');
  }
  {
    const f = fixture(); f.update();
    f.actual.pos.y = 40; f.actual.stepHeight = -5; f.pose(1).translation.y = 9; f.pose(1, 1).translation.y = 999;
    check(f.output(1)[7] === 27, 'pose mutation never auto-refreshes');
    f.events.length = 0; f.update();
    check(f.output(0)[7] === 40 && f.output(1)[7] === 54 && f.matrices.getMatrix(f.storage.copy1aa4)[7] === 35, 'actual fields and bank-zero pose remain live');
    check(f.events.filter(v => v === 'identity').length === 1, 'repeat explicit refresh is not deduplicated');
  }
  {
    const f = fixture(); f.state.mode4a0 = 2; f.state.flags48a = NaN;
    f.actual.pos.y = NaN; f.actual.heading = NaN; f.actual.stepHeight = NaN; f.pose(1).translation.y = NaN;
    f.hooks.matrix = () => {throw Error('gate must not touch matrix owner');};
    f.hooks.pose = () => {throw Error('gate must not touch feedback');}; f.update();
    check(f.state.adjusted1d54.y === 82 && f.events.length === 0 && f.output(0)[7] === -20, 'mode2 gates all work and unrelated reads');
  }
  for (const sentinel of [128, 255]) {
    const f = fixture(1); f.state.flags48a = 4; f.state.mask1d70 = NaN; f.topology(0)[0] = sentinel;
    f.state.offset1dbc.x = NaN; f.state.adjusted1d54.x = NaN; f.update();
    check(Number.isNaN(f.state.adjusted1d54.x) && f.state.adjusted1d54.y === 20 && f.state.adjusted1d54.z === 83,
      'flags alternate branch writes only20Y without pose1 or offset access');
    check(!f.events.some(v => v.startsWith('joint:')), 'all negative signed-byte entries terminate before mask');
  }
  {
    const f = fixture(); f.state.flags48a = 2; f.state.adjusted1d54.x = 7; f.state.adjusted1d54.z = 8;
    f.pose(1).translation.x = NaN; f.pose(1).translation.y = NaN; f.pose(1).translation.z = NaN; f.update();
    check(f.output(1)[3] === 17 && f.output(1)[7] === 40 && f.output(1)[11] === 38, 'joint1 ignores unused ordinary translation in alternate path');
  }
  {
    const f = fixture(); f.pose(1).translation.z = NaN;
    rejects(f.update, 'finite source float32');
    check(f.state.adjusted1d54.x === 5 && f.state.adjusted1d54.y === 7 && f.state.adjusted1d54.z === 83,
      'PSVECAdd retains XY stores on late Z refusal');
    check(f.output(0)[7] === -20 && f.events.length === 0, 'prep refusal precedes root identity');
  }
  {
    const f = fixture(); Object.defineProperty(f.state.adjusted1d54, 'y', {writable: false});
    rejects(f.update, 'non-writable');
    check(f.state.adjusted1d54.x === 5 && f.state.adjusted1d54.y === 82 && f.state.adjusted1d54.z === 83, 'XY pair store writable checks preserve X prefix');
  }
  {
    const f = fixture(); f.pose(1).translation.x = -0; f.state.offset1dbc.x = -0;
    f.pose(1).translation.y = Math.fround(2 ** -149); f.state.offset1dbc.y = Math.fround(2 ** -149);
    f.update(); check(Object.is(f.state.adjusted1d54.x, -0) && f.state.adjusted1d54.y === 2 ** -148, 'paired add preserves signed zero and gradual underflow');
  }
  {
    const f = fixture(); f.actual.heading = 0xfc00; f.state.yawOffset6b8 = 1;
    f.update(); check(f.output(1)[7] === 27, 'unsigned BAM heading sign-extends before zero effective yaw');
    f.state.yawOffset6b8 = 64; f.actual.heading = 0; f.update();
    check(f.output(1)[7] === 27, 'combined correction truncates signed16 before zero domain admission');
    f.state.mode4a1 = 1; f.state.yawOffset6b8 = NaN; f.update();
    check(f.output(1)[7] === 27, 'nonzero mode skips yaw-offset load');
  }
  {
    const f = fixture(); f.actual.bodyPitch = 0xffff;
    rejects(f.update, 'nonzero short correction');
    check(f.output(0)[7] === 20 && f.matrices.getMatrix(f.storage.copy114)[7] === 91, 'signed body pitch refusal after root translation, before copies');
    check(f.state.adjusted1d54.y === 7, 'prep retained before root correction refusal');
  }
  {
    const f = fixture(); f.state.scale58.y = NaN;
    rejects(f.update, 'scale.y');
    check(f.output(0)[0] === 1 && f.output(0)[7] === 20 && f.matrices.getMatrix(f.storage.copy114)[7] === 91, 'scale refusal retains translated/corrected root');
  }
  {
    const f = fixture(); f.actual.stepHeight = NaN;
    rejects(f.update, 'stepHeight');
    check(f.matrices.getMatrix(f.storage.copy114)[7] === 20 && f.matrices.getMatrix(f.storage.copy1aa4)[7] === 20 && f.output(1)[7] === -21,
      'height failure retains both root copies and precedes topology');
  }
  {
    const f = fixture(); f.state.preRotation1d64.x = 1;
    rejects(f.update, 'nonzero short rotation');
    check(f.events.slice(-2).join(',') === 'rotate:z,rotate:x', 'joint1 mandatory wrapper order before refusal');
    check(f.matrices.getMatrix(f.storage.scratch)[7] === 20 && f.output(1)[7] === -21, 'Z concat scratch prefix retained; joint1 not yet composed');
  }
  {
    const f = fixture(); f.storage.corrections18d4[3]!.x = 1;
    rejects(f.update, 'nonzero short correction');
    check(f.output(1)[7] === 27 && f.output(3)[7] === 26 && f.output(4)[7] === -24 && f.output(2)[7] === -22,
      'late branch failure retains earlier joint and failing firstConcat but skips continuation');
  }
  {
    const f = fixture(); f.pose(3).quaternion.x = -0;
    rejects(f.update, 'exact (+0,+0,+0,1)');
    check(f.output(1)[7] === 27 && f.output(3)[7] === -23 && f.output(2)[7] === -22, 'nonidentity quaternion refuses at reached branch after completed joint1');
  }
  {
    const f = fixture(); f.storage.scales15d4[4]!.z = NaN;
    rejects(f.update, 'scale.z');
    check(f.output(3)[7] === 26 && f.output(4)[7] === 34 && f.output(2)[7] === -22, 'late scale validation retains firstConcat and prior branches');
  }
  {
    const f = fixture(); f.topology(0)[0] = 2; f.topology(2)[0] = 3; f.topology(2)[1] = 3; f.topology(3)[0] = 255;
    f.update();
    check(f.events.filter(v => v.startsWith('joint:')).join(',') === 'joint:2:0,joint:3:0,joint:3:2', 'repeated nodes execute with each source parent');
    check(f.output(3)[7] === 30, 'repeat overwrite uses last source traversal');
  }
  {
    const f = fixture(6, 3); f.topology(0)[0] = 2; f.topology(2)[0] = 2; f.topology(2)[1] = 255;
    rejects(f.update, 'visit budget');
    check(f.output(2)[7] === 32 && f.events.filter(v => v.startsWith('joint:')).length === 3, 'cycle bounded after repeated prefixes, no eager rejection');
  }
  {
    const f = fixture(6, 3); f.topology(0)[0] = 2; f.topology(2)[1] = 2; f.state.mask1d70 = 0;
    rejects(f.update, 'visit budget');
    check(f.output(0)[7] === 20 && f.output(2)[7] === -22, 'iterative recursion is bounded even for disabled-node cycles');
  }
  {
    const f = fixture(); f.topology(2)[0] = 32;
    rejects(f.update, '32-joint domain');
    check(f.output(2)[7] === 31 && f.output(5)[7] === 37, 'out-of-domain continuation refuses only after complete recursive branch');
  }
  {
    const f = fixture(2); f.topology(0)[0] = 1; f.topology(1)[0] = 3; f.state.mask1d70 = 0;
    rejects(f.update, 'topology: addressing outside');
    check(f.output(0)[7] === 20 && f.output(1)[7] === -21, 'disabled missing topology refuses when reached');
  }
  {
    const f = fixture(); f.topology(0)[1] = 127; f.topology(0)[2] = NaN; f.topology(1)[2] = NaN; f.topology(1)[3] = NaN;
    f.update(); check(f.output(5)[7] === 37, 'root branch and all byte2/byte3 fields are unused by source caller');
  }
  {
    const f = fixture(); f.input.scale58.y = 9; f.input.adjusted1d54.y = 999;
    (f.storageInput.topology1994[0] as number[])[0] = 255; f.storageInput.corrections18d4[1]!.x = 1;
    f.update(); check(f.output(1)[7] === 27 && f.state.scale58.y === 1, 'explicit missing fields and topology are owned copies');
    check(f.runtime.getActorBinding(f.id) === f.state && Object.isSealed(f.state) && Object.isSealed(f.state.adjusted1d54), 'stable sealed owned records');
    check(f.runtime.getStorage(f.id) === f.storage && Object.isFrozen(f.storage.matrices8d4), 'stable fixed matrix identities');
  }
  {
    const f = fixture();
    f.mappingAdapter.getActor = () => {throw Error('replacement mapping method');};
    f.mappingAdapter.getLayout = () => {throw Error('replacement layout method');};
    f.feedbackAdapter.getPose = () => {throw Error('replacement feedback method');};
    f.matrixAdapter.identity = () => {throw Error('replacement matrix method');};
    f.matrixAdapter.getMatrix = () => {throw Error('replacement matrix getter');};
    f.matrixAdapter.composePose = () => {throw Error('replacement composePose method');};
    f.update(); check(f.output(1)[7] === 27, 'all adapter functions and original receivers captured');
  }
  {
    const f = fixture(); f.hooks.pose = () => {try {f.update();} catch { /* deliberate faulty adapter */ }};
    rejects(f.update, 'caught same-runtime reentry');
    check(f.state.adjusted1d54.y === 82 && f.output(0)[7] === -20, 'caught feedback reentry poisons enclosing operation');
    delete f.hooks.pose; f.update(); check(f.output(1)[7] === 27, 'runtime usable after bounded refusal');
  }
  {
    const f = fixture(); f.hooks.effect = () => {try {f.update();} catch { /* deliberate faulty adapter */ }};
    rejects(f.update, 'caught same-runtime reentry');
    check(f.output(0)[7] === 0 && f.state.adjusted1d54.y === 7 && f.events.join(',') === 'identity', 'caught effect reentry preserves completed identity and prep');
  }
  {
    const f = fixture(); f.hooks.effect = () => Promise.resolve();
    rejects(f.update, 'synchronously');
    check(f.output(0)[7] === 0 && f.events.join(',') === 'identity', 'nonvoid/deferred matrix effect refuses after completed prefix');
  }
  {
    const f = fixture(); Object.defineProperty(f.output(0), '4', {writable: false});
    rejects(f.update, 'non-writable');
    check(f.output(0)[3] === 0 && f.output(0)[7] === 0 && f.output(0)[11] === -30, 'identity destination store prefix remains actual owner behavior');
  }
  {
    const f = fixture(),original=f.actual.pos;
    check(f.runtime.getPositionOwner(f.id)===original,'position query returns the already bound canonical owner');
    const actors=f.runtime.getRetainedActorOwners();
    check(Object.isFrozen(actors) && actors.includes(f.actual),'actor inventory retains actual actor identities without scalar reads');
    f.actual.pos = {x: 1, y: 2, z: 3};
    check(f.runtime.getPositionOwner(f.id)===original,'position ownership query never adopts a replacement');
    rejects(f.update, 'position record changed'); check(f.output(0)[7] === 0, 'replacement of fixed position record refuses after identity');
  }
  {
    const f = fixture(); let changed = false;
    const provider = {...f.sources.matrices, getMatrix(id: symbol) {
      const original = f.matrices.getMatrix(id); return changed ? original.slice() : original;
    }};
    const runtime = createSourceActorWorldMatrixRuntime({...f.sources, matrices: provider});
    runtime.bindActor(f.id, f.actual, f.input, f.storageInput); changed = true;
    rejects(() => runtime.getWorldMatrix(f.id, 0), 'matrix owner changed');
    rejects(() => runtime.updateActor(f.id), 'matrix owner changed');
    check(runtime.getActorBinding(f.id).adjusted1d54.y === 7 && f.output(0)[7] === -20, 'unstable matrix record refuses after prep, before identity');
  }
  {
    const f = fixture(); let changed = false;
    const provider = {getPose(id: symbol) {const original = f.feedback.getPose(id); return changed ? {...original} : original;}};
    const runtime = createSourceActorWorldMatrixRuntime({...f.sources, feedback: provider});
    runtime.bindActor(f.id, f.actual, f.input, f.storageInput); changed = true;
    rejects(() => runtime.updateActor(f.id), 'pose owner changed');
    check(runtime.getActorBinding(f.id).adjusted1d54.y === 82 && f.output(0)[7] === -20, 'unstable pose refuses before prep writes');
  }
  {
    const f = fixture(); let changed = false;
    const provider = {getActor: f.mapping.getActor, getLayout(id: symbol) {
      const original = f.mapping.getLayout(id); return changed ? {...original} : original;
    }};
    const runtime = createSourceActorWorldMatrixRuntime({...f.sources, mapping: provider});
    runtime.bindActor(f.id, f.actual, f.input, f.storageInput); changed = true;
    rejects(() => runtime.updateActor(f.id), 'mapping owner changed');
    check(runtime.getActorBinding(f.id).adjusted1d54.y === 82, 'unstable mapping layout cannot silently redirect poses');
  }
  {
    const f = fixture(); const runtime = createSourceActorWorldMatrixRuntime(f.sources);
    runtime.bindActor(f.id, f.actual, f.input, {...f.storageInput, matrices8d4: []});
    rejects(() => runtime.updateActor(f.id), 'world matrix: addressing outside');
    check(runtime.getActorBinding(f.id).adjusted1d54.y === 7, 'missing root storage refuses after reached prep prefix');
  }
  {
    const f = fixture(); const runtime = createSourceActorWorldMatrixRuntime(f.sources);
    runtime.bindActor(f.id, f.actual, f.input, {...f.storageInput, corrections18d4: []});
    rejects(() => runtime.updateActor(f.id), 'joint correction: addressing outside');
    check(f.matrices.getMatrix(f.storage.copy1aa4)[7] === 27 && f.matrices.getMatrix(f.storage.scratch)[7] === 20 && f.output(1)[7] === -21,
      'missing joint storage refuses after actual root and mandatory wrappers');
  }
  {
    const f = fixture(); const runtime = createSourceActorWorldMatrixRuntime(f.sources);
    runtime.bindActor(f.id, f.actual, {...f.input, mode4a0: 2}, {...f.storageInput, topology1994: []});
    runtime.updateActor(f.id); check(f.output(0)[7] === -20, 'gate does not require missing graph storage');
    runtime.getActorBinding(f.id).mode4a0 = 0;
    rejects(() => runtime.updateActor(f.id), 'topology: addressing outside');
    check(f.matrices.getMatrix(f.storage.copy1aa4)[7] === 27, 'missing initial topology refuses only after lifted copy');
  }
  {
    const f = fixture(); const another = Symbol('not a mapped actor');
    rejects(() => f.runtime.bindActor(another, f.actual, f.input, f.storageInput), 'actual RomActor already bound');
    const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => f.mapping.createPart(
      {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
      {descriptor00: null, scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0})));
    const poses = Array.from({length: 2}, () => Array.from({length: 2}, () => f.feedback.createPose(
      {translation: zero(), quaternion: {x: 0, y: 0, z: 0, w: 1}})));
    const id = f.mapping.createActor({descriptor4b0: null, jointCount1d90: 2, boundary1d91: 0, boundary1d92: 0,
      boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses});
    rejects(() => f.runtime.bindActor(id, createRomActor(), f.input, f.storageInput), 'aliased matrix storage');
  }
  {
    const f = fixture(); rejects(() => f.runtime.updateActor(Symbol()), 'unknown/non-owned');
    rejects(() => f.runtime.bindActor(f.id, f.actual, f.input, f.storageInput), 'already bound');
    rejects(() => createSourceActorWorldMatrixRuntime(f.sources, 0), 'positive safe');
    const missing = {...f.input} as Partial<SourceActorWorldMatrixBinding>; delete missing.roll74;
    const another = createSourceActorWorldMatrixRuntime(f.sources);
    rejects(() => another.bindActor(f.id, f.actual, missing as SourceActorWorldMatrixBinding, f.storageInput), 'own data');
    rejects(() => another.bindActor(f.id, f.actual, {...f.input, roll74: 65535}, f.storageInput), 'integer out of bounds');
    rejects(() => another.bindActor(f.id, f.actual, f.input, {...f.storageInput, copy114: f.matrixIds[0]!}), 'aliased matrix');
    rejects(() => another.bindActor(f.id, f.actual, f.input, {...f.storageInput, scratch: Symbol()}), 'unknown/non-owned matrix');
    const getter = {...f.input}; Object.defineProperty(getter, 'mode4a0', {get() {throw Error('must not execute getter');}});
    rejects(() => another.bindActor(f.id, f.actual, getter, f.storageInput), 'own data');
  }
  {
    const f = fixture(32); f.topology(0)[0] = 31; f.state.mask1d70 = 0x80000000; f.update();
    check(f.output(31)[7] === 82, 'unsigned high mask bit updates joint31 without signed-mask confusion');
  }
  {
    const f = fixture(); f.topology(0)[0] = 255; f.state.flags48a = 4;
    f.actual.pos.y = (2 - 2 ** -23) * 2 ** 127; f.actual.stepHeight = f.actual.pos.y;
    rejects(f.update, 'overflow float32');
    check(f.matrices.getMatrix(f.storage.copy114)[7] === f.actual.pos.y && f.matrices.getMatrix(f.storage.copy1aa4)[7] === f.actual.pos.y,
      'height overflow is bounded host refusal after both copies, not source FP behavior');
  }
  {
    const f = fixture();
    check(f.runtime.getActualActor(f.id) === f.actual, 'getActualActor returns the actual shared record');
    f.state.mode4a0 = NaN; f.actual.pos.y = NaN;
    f.runtime.prepareActor(f.id);
    check(f.state.adjusted1d54.y === 7 && f.events.length === 0, 'ungated prep never reads mode or root fields');
    f.actual.pos.y = 20; f.state.flags48a = NaN; f.pose(1).translation.y = NaN;
    f.runtime.rebuildActor(f.id, 0);
    check(f.output(1)[7] === 27 && f.state.adjusted1d54.y === 7, 'ungated rebuild uses prepared state without repeating prep');
    f.state.adjusted1d54.y = 9;
    f.runtime.bindCorrectedTraversalState(f.id, {count1d96: 0, count1d97: 0});
    f.runtime.rebuildActor(f.id, 1);
    check(f.output(1)[7] === 29 && f.state.adjusted1d54.y === 9, 'second pass consumes caller-modified adjusted translation');
    rejects(() => f.runtime.rebuildActor(f.id, 2 as 0), 'mode must be 0 or 1');
    rejects(() => f.runtime.prepareActor(Symbol()), 'unknown/non-owned');
    rejects(() => f.runtime.getActualActor(Symbol()), 'unknown/non-owned');
  }
  {
    const f = fixture(); f.hooks.effect = () => {f.state.mode4a0 = NaN;};
    f.update();
    check(f.output(5)[7] === 37 && f.events.filter(v => v === 'identity').length === 1,
      '46698 reads mode4a0 exactly once and uses private ungated stages');
  }
  for (const first of [0, 128, 255]) for (const second of [0, 128, 255]) {
    const f = fixture(), counts = {count1d96: first, count1d97: second};
    f.runtime.bindCorrectedTraversalState(f.id, counts);
    f.runtime.prepareActor(f.id); f.runtime.rebuildActor(f.id, 1);
    check(f.output(5)[7] === 37 && f.events.filter(v => v.startsWith('joint:')).join(',') ===
      'joint:1:scratch,joint:3:0,joint:4:3,joint:2:1,joint:5:1', 'nonpositive signed raw counts use ordinary traversal in mode1');
  }
  {
    const f = fixture(); f.state.mask1d70 = 0;
    f.runtime.rebuildActor(f.id, 1);
    check(f.output(0)[7] === 20 && f.output(1)[7] === -21, 'disabled mode1 graph never resolves missing corrected owner');
    f.topology(0)[0] = 255; f.state.mask1d70 = NaN;
    f.runtime.rebuildActor(f.id, 1);
    check(f.matrices.getMatrix(f.storage.copy1aa4)[7] === 27, 'negative initial index never reads mask or corrected owner');
  }
  {
    const f = fixture(); f.runtime.prepareActor(f.id);
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'actual corrected traversal state is not bound');
    check(f.output(0)[7] === 20 && f.matrices.getMatrix(f.storage.copy1aa4)[7] === 27 && f.output(1)[7] === -21,
      'missing mode1 owner refuses only at first active node after complete root/copy prefix');
  }
  {
    const f = fixture(), counts = {count1d96: 0, count1d97: 0};
    f.runtime.bindCorrectedTraversalState(f.id, counts);
    Object.defineProperty(counts, 'count1d96', {get() {throw Error('must not call count getter');}});
    Object.defineProperty(counts, 'count1d97', {get() {throw Error('must not call count getter');}});
    f.state.mask1d70 = 0; f.runtime.rebuildActor(f.id, 1);
    f.state.mask1d70 = 8;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'count1d96: own data');
    check(f.output(3)[7] === -23 && !f.events.some(v => v.startsWith('joint:')),
      'disabled nodes follow links without count reads; first enabled branch validates count1d96');
  }
  for (const key of ['count1d96', 'count1d97'] as const) {
    const f = fixture(), counts = {count1d96: 0, count1d97: 0};
    f.runtime.bindCorrectedTraversalState(f.id, counts); counts[key] = 1;
    if (key === 'count1d96') Object.defineProperty(counts, 'count1d97', {get() {throw Error('second scan must not be read');}});
    f.runtime.prepareActor(f.id);
    rejects(() => f.runtime.rebuildActor(f.id, 1), `positive ${key} IK scan`);
    check(f.output(0)[7] === 20 && f.matrices.getMatrix(f.storage.copy1aa4)[7] === 27 && f.output(1)[7] === -21 &&
      !f.events.some(v => v.startsWith('rotate:')), 'first reached positive scan refuses after root copies, before joint operations');
  }
  for (const key of ['count1d96', 'count1d97'] as const) {
    const f = fixture(), counts = {count1d96: 0, count1d97: 0};
    f.runtime.bindCorrectedTraversalState(f.id, counts); f.runtime.prepareActor(f.id);
    f.hooks.composed = () => {counts[key] = 1;};
    rejects(() => f.runtime.rebuildActor(f.id, 1), `positive ${key} IK scan`);
    check(f.output(1)[7] === 27 && f.output(3)[7] === -23 && f.events.slice(-2).join(',') === 'correct,scale',
      'counts are retained and freshly read per enabled node; prior joint is fully completed');
    delete f.hooks.composed; counts[key] = 0;
    f.runtime.rebuildActor(f.id, 1); check(f.output(5)[7] === 37, 'real owner clearing counts enables next explicit rebuild');
  }
  {
    const f = fixture(), counts = {count1d96: 0, count1d97: 0};
    f.runtime.bindCorrectedTraversalState(f.id, counts);
    rejects(() => f.runtime.bindCorrectedTraversalState(f.id, counts), 'already bound');
    const target = copyTarget(f);
    rejects(() => f.runtime.bindCorrectedTraversalState(target.id, counts), 'another actor');
    rejects(() => f.runtime.bindCorrectedTraversalState(target.id, {count1d96: -1, count1d97: 0}), 'integer out of bounds');
    const getter = {get count1d96(): number {throw Error('getter must not run');}, count1d97: 0};
    rejects(() => f.runtime.bindCorrectedTraversalState(target.id, getter), 'own data');
    f.runtime.bindCorrectedTraversalState(target.id, {count1d96: 0, count1d97: 0});
    counts.count1d96 = NaN; f.update(); check(f.output(5)[7] === 37, '46698 mode0 never reads corrected counts');
  }
  {
    const f = fixture(), counts = {count1d96: 3, count1d97: 2,
      primary1a14: [primarySlot(255), primarySlot(128), primarySlot(2)],
      secondary1a94: [secondarySlot(255, NaN, NaN), secondarySlot(128, NaN, NaN)]};
    f.runtime.bindCorrectedTraversalState(f.id, counts); f.runtime.prepareActor(f.id); f.runtime.rebuildActor(f.id, 1);
    check(f.output(5)[7] === 37 && f.events.filter(v => v.startsWith('joint:')).length === 5,
      'positive primary/secondary misses sign-extend joint bytes, ignore unused payloads, and genuinely rebuild every enabled joint');
  }
  {
    const f = fixture(), counts: SourceActorCorrectedTraversalState = {count1d96: 128, count1d97: 255};
    Object.defineProperty(counts, 'primary1a14', {get() {throw Error('negative count must skip primary storage');}});
    Object.defineProperty(counts, 'secondary1a94', {get() {throw Error('negative count must skip secondary storage');}});
    f.runtime.bindCorrectedTraversalState(f.id, counts); f.runtime.prepareActor(f.id); f.runtime.rebuildActor(f.id, 1);
    check(f.output(5)[7] === 37, 'nonpositive signed counts do not resolve even invalid slot owners');
  }
  {
    const f = primaryFixture();
    f.state.adjusted1d54.x = NaN; f.state.preRotation1d64.z = NaN;
    f.actual.steerYaw = NaN; f.storage.corrections18d4[1]!.y = NaN;
    f.storage.scales15d4[1]!.x = NaN; f.pose(1).quaternion.x = NaN;
    f.storage.corrections18d4[2]!.x = NaN; f.storage.scales15d4[2]!.x = NaN;
    f.pose(2).quaternion.x = NaN;
    f.runtime.rebuildActor(f.id, 1);
    const coefficient = 1 - 2 ** -23;
    check(f.output(1)[3] === 10 && f.output(1)[7] === 30 && f.output(1)[11] === 30 && f.output(1)[5] === coefficient,
      'genuine47368 uses raw pose1, retained lengths and actual45918 before real rotation Concats');
    check(f.output(2)[7] === 32 && f.output(2)[5] === -coefficient && f.output(3)[7] === 31.5,
      'real second rotated matrix and resumed distal composition are not target snapping or an endpoint-success claim');
    check(f.events.join(',') === 'identity,translate,correct,scale,copy114,copy1aa4,primary:1:0,joint:4:0,joint:5:4,joint:6:1,joint:7:6,joint:3:2',
      'primary current branch uses incoming parent; skipped branch uses current parent; continuation uses skipped parent without ordinary skipped work');
  }
  {
    const f = primaryFixture();
    f.topology(0)[0] = 4; f.topology(4)[0] = 1;
    f.topology(1)[1] = 255; f.topology(2)[1] = 255;
    // Rebuild this changed topology before placement, retaining the genuine
    // lengths2/.5 atY32,34,34.5 under ordinary nonroot parent4 atY24.
    f.runtime.prepareActor(f.id); f.runtime.rebuildActor(f.id, 0);
    f.placement.y = 35; f.events.length = 0;
    f.runtime.rebuildActor(f.id, 1);
    check(f.events.join(',') === 'identity,translate,correct,scale,copy114,copy1aa4,joint:4:0,primary:1:4,joint:3:2',
      'primary receives the actual nonroot incoming parent, not an assumed root');
    check(f.output(4)[7] === 24 && f.output(1)[7] === 34 && f.output(2)[7] === 36 && f.output(3)[7] === 35.5,
      'nonroot parent translation participates in actual raw-pose transform and folded-placement outputs');
  }
  {
    const f = primaryFixture(); f.state.mask1d70 = 2; f.counts.count1d96 = 3;
    Object.defineProperty(f.counts, 'count1d97', {get() {throw Error('primary match must skip secondary count');}});
    Object.defineProperty(f.counts.primary1a14, '1', {get() {throw Error('primary match must stop before later slot');}});
    f.runtime.rebuildActor(f.id, 1);
    check(f.output(1)[7] === 30 && f.output(2)[7] === 32 && f.output(3)[7] === 30.5 &&
      f.events.at(-1) === 'primary:1:0', 'first primary match stops before later duplicate/missing slot and secondary count; disabled branches retain matrix values');
  }
  {
    const f = primaryFixture(); f.state.mask1d70 = 2;
    const selected = f.placement;
    f.counts.primary1a14.unshift(primarySlot(255), primarySlot(128)); f.counts.count1d96 = 3;
    f.runtime.rebuildActor(f.id, 1);
    check(f.counts.primary1a14[2] === selected && f.output(2)[5] === -(1 - 2 ** -23),
      'nonzero primary match uses its actual live payload after signed misses');
  }
  {
    const f = primaryFixture(); f.state.mask1d70 = 0xfffffffd;
    f.placement.x = NaN; f.placement.axis0d = NaN; f.placement.bend0f = NaN;
    f.runtime.rebuildActor(f.id, 1);
    check(!f.events.some(event => event.startsWith('primary:')) && f.events.includes('joint:2:1'),
      'disabled matched joint skips correction scans and follows ordinary links, never the primary skip path');
  }
  {
    const f = primaryFixture(); f.topology(2)[1] = 4; f.topology(4)[0] = 255;
    f.runtime.rebuildActor(f.id, 1);
    check(f.events.filter(event => event.startsWith('joint:4:')).join(',') === 'joint:4:0,joint:4:1',
      'repeated branch node executes twice with distinct source parent contexts');
  }
  for (const stopped of [128, 255]) {
    const f = primaryFixture(); f.topology(1)[0] = stopped;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'topology: addressing outside');
    check(f.output(2)[7] === 32 && f.events.slice(-2).join(',') === 'joint:4:0,joint:5:4',
      'negative skipped node refuses after primary and current-side branch, not a fabricated terminal return');
  }
  {
    const f = primaryFixture(); f.topology(1)[0] = 9;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'topology: addressing outside');
    check(f.events.at(-1) === 'joint:5:4' && f.output(2)[7] === 32, 'missing skipped node preserves both completed prefixes');
  }
  {
    const f = primaryFixture();
    f.hooks.placed = () => {f.topology(1)[1] = 255; f.topology(1)[0] = 2; f.topology(2)[1] = 255; f.topology(2)[0] = 255;};
    f.runtime.rebuildActor(f.id, 1);
    check(f.events.at(-1) === 'primary:1:0', 'primary topology bytes are read after real placement rather than cached before it');
  }
  {
    const f = primaryFixture();
    f.hooks.matrix = matrix => {
      // This read occurs only after current byte1 recursion enters joint4.
      if (matrix === f.matrixIds[4]) f.topology(1)[0] = 7;
    };
    f.topology(7)[1] = 255; f.topology(7)[0] = 255;
    f.runtime.rebuildActor(f.id, 1);
    check(!f.events.includes('joint:6:1') && !f.events.includes('joint:3:2'),
      'current byte0 is freshly loaded only after current-side branch returns');
  }
  {
    const f = primaryFixture();
    f.hooks.matrix = matrix => {if (matrix === f.matrixIds[6]) f.topology(2)[0] = 255;};
    f.runtime.rebuildActor(f.id, 1);
    check(f.events.at(-1) === 'joint:7:6' && !f.events.includes('joint:3:2'),
      'skipped byte0 is freshly loaded only after skipped-side branch returns');
  }
  {
    const f = primaryFixture();
    f.hooks.placed = () => {f.counts.count1d96 = 0;};
    Object.defineProperty(f.counts.primary1a14, '1', {get() {throw Error('unreached row');}});
    f.runtime.rebuildActor(f.id, 1);
    check(f.output(3)[7] === 31.5 && f.events.includes('joint:6:1'), 'real count owner is reloaded by later enabled branches after completed primary');
  }
  for (const stage of ['reentry', 'promise'] as const) {
    const f = primaryFixture();
    f.hooks.placed = () => {
      if (stage === 'promise') return Promise.resolve();
      try {f.runtime.rebuildActor(f.id, 1);} catch { /* deliberately caught */ }
      return undefined;
    };
    rejects(() => f.runtime.rebuildActor(f.id, 1), stage === 'reentry' ? 'caught same-runtime reentry' : 'synchronously');
    check(f.output(2)[7] === 32 && f.events.at(-1) === 'primary:1:0',
      'captured primary effect checks synchronous completion/reentry after real writes and before topology');
  }
  {
    const f = primaryFixture();
    f.matrixAdapter.primaryFoldedPlacement = () => {throw Error('replacement primary method');};
    f.runtime.rebuildActor(f.id, 1);
    check(f.output(2)[7] === 32, 'primary method is captured once with its actual receiver');
  }
  {
    const f = primaryFixture(); f.state.mask1d70 = 2;
    for (const [index, y] of [[2, 28], [3, 30], [4, 30.5]]) {
      f.output(index!).splice(0, 12, 1, 0, 0, 10, 0, 1, 0, y!, 0, 0, 1, 30);
    }
    let changed = false;
    f.hooks.pose = () => {if (!changed) {changed = true; f.placement.joint0c = 4;}};
    f.runtime.rebuildActor(f.id, 1);
    check(changed && f.events.at(-1) === 'primary:2:0' && f.output(1)[7] === 28 && f.output(2)[7] === 30 && f.output(3)[7] === 32,
      'helper freshly reloads record joint for physical matrix base but still consumes traversal current/current+1 raw poses');
  }
  for (const invalid of ['x', 'y'] as const) {
    const f = primaryFixture(); f.pose(1).translation[invalid] = NaN;
    f.hooks.pose = () => {f.placement.joint0c = NaN;};
    rejects(() => f.runtime.rebuildActor(f.id, 1), invalid === 'x' ? 'x: finite source float32' : 'joint0c: integer out of bounds');
    check(f.output(1)[7] === 28 && !f.events.some(event => event.startsWith('primary:')),
      'source currentX precedes fresh joint byte and currentY follows it before any placement write');
  }
  {
    const f = primaryFixture(); f.pose(2).translation.z = NaN;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'finite source float32');
    check(f.output(1)[7] === 28 && f.output(2)[7] === 30,
      'adjacent raw pose is consumed before retained-length and translation output work');
  }
  {
    const f = primaryFixture(); f.placement.x = NaN;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'finite source float32');
    check(f.output(1)[7] === 30 && f.output(2)[7] === 30 && f.events.at(-1) === 'primary:1:0',
      'reached invalid target keeps translated base prefix and leaves next matrix untouched');
  }
  for (const index of [3, 7, 11]) {
    const f = primaryFixture(); Object.defineProperty(f.output(1), String(index), {writable: false});
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'non-writable');
    check(f.output(1)[7] === (index <= 7 ? 28 : 30) && f.output(2)[7] === 30,
      'primary translation write refusal preserves only completed stores and never enters topology');
  }
  for (const key of ['primary1a14', 'secondary1a94'] as const) {
    const f = fixture(), counts = {count1d96: key === 'primary1a14' ? 2 : 0, count1d97: key === 'secondary1a94' ? 2 : 0,
      primary1a14: [primarySlot(255)], secondary1a94: [secondarySlot(255)]};
    f.runtime.bindCorrectedTraversalState(f.id, counts);
    rejects(() => f.runtime.rebuildActor(f.id, 1), `${key}: addressing outside`);
    check(f.output(1)[7] === -21 && f.output(0)[7] === 20, 'positive scan fails only when it reaches an absent explicit row');
  }
  {
    const f = fixture(), counts = {count1d96: 1, count1d97: 0, primary1a14: [primarySlot(255)]};
    f.runtime.bindCorrectedTraversalState(f.id, counts); f.runtime.prepareActor(f.id); f.runtime.rebuildActor(f.id, 1);
    counts.primary1a14[0] = primarySlot(255);
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'correction slot owner changed');
  }
  {
    const f = fixture(), counts = {count1d96: 0, count1d97: 1, secondary1a94: [secondarySlot(255)]};
    f.runtime.bindCorrectedTraversalState(f.id, counts); f.runtime.prepareActor(f.id); f.runtime.rebuildActor(f.id, 1);
    counts.secondary1a94 = [secondarySlot(255)];
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'correction storage owner changed');
  }
  {
    const f = fixture(), g = terrainCorrectionFixture(f), counts = bindSecondary(f);
    // 4784c must use raw pose1 rather than the invalid adjusted, short, scale
    // and quaternion fields that only the ordinary joint1 path would consume.
    f.state.adjusted1d54.x = NaN; f.state.preRotation1d64.z = NaN;
    f.actual.steerYaw = NaN; f.storage.corrections18d4[1]!.y = NaN;
    f.storage.scales15d4[1]!.x = NaN; f.pose(1).quaternion.x = NaN;
    g.state.field670 = 9; f.runtime.rebuildActor(f.id, 1);
    const coefficient = 1 - 2 ** -23;
    check(f.output(1)[3] === 11 && f.output(1)[7] === 22 && f.output(1)[11] === 33,
      'genuine4784c transforms raw bank-zero pose with incoming parent, bypassing adjusted joint1 translation');
    check(f.output(1)[0] === coefficient && f.output(1)[5] === coefficient && f.output(1)[10] === coefficient,
      'real45918 orientation produces audited nonideal diagonal, not an identity/normal callback shortcut');
    check(f.events.join(',') === 'identity,translate,correct,scale,copy114,copy1aa4,transform:0,movement,normal:9,orient:1:2:1,joint:3:0,joint:4:3,joint:2:1,joint:5:1',
      'real secondary effect completes before ordinary incoming-parent branch and corrected-current continuation');
    check(f.output(3)[7] === 26 && f.output(4)[7] === 34 && f.output(2)[7] === Math.fround(22 + Math.fround(4 * coefficient)),
      'branch uses incoming parent while continuation consumes actual oriented matrix');
    check(counts.secondary1a94[0]!.padding03 !== counts.secondary1a94[0]!.padding03,
      'unused secondary padding is not validated or changed');
  }
  {
    const f = fixture(); terrainCorrectionFixture(f);
    f.state.mask1d70 = 2; const counts = {count1d96: 0, count1d97: 3,
      secondary1a94: [secondarySlot(1), secondarySlot(1, NaN, NaN)]};
    f.runtime.bindCorrectedTraversalState(f.id, counts);
    Object.defineProperty(counts.secondary1a94, '1', {get() {throw Error('first match must end secondary scan');}});
    f.runtime.rebuildActor(f.id, 1);
    check(f.events.filter(v => v.startsWith('orient:')).length === 1 && f.output(1)[7] === 22,
      'first secondary match stops before duplicate, missing later slot and disabled descendants');
  }
  {
    const f = fixture(); terrainCorrectionFixture(f); f.state.mask1d70 = 2;
    const counts = {count1d96: 0, count1d97: 4, secondary1a94:
      [secondarySlot(255, NaN, NaN), secondarySlot(128, NaN, NaN), secondarySlot(1), secondarySlot(1, NaN, NaN)]};
    f.runtime.bindCorrectedTraversalState(f.id, counts);
    Object.defineProperty(counts.secondary1a94, '3', {get() {throw Error('slot2 match must end scan');}});
    f.runtime.rebuildActor(f.id, 1);
    check(f.output(1)[3] === 11 && f.output(1)[7] === 22 && f.output(1)[11] === 33 && f.output(1)[0] === 1 - 2 ** -23,
      'secondary scan passes the actual matched slot2 into genuine4784c, skipping two signed misses and later duplicate');
    check(f.events.filter(v => v.startsWith('orient:')).join(',') === 'orient:1:2:1',
      'nonzero matched slot supplies its own axes rather than slot0 payload');
  }
  {
    const f = fixture(); terrainCorrectionFixture(f); bindSecondary(f, 4);
    f.state.mask1d70 = (1 << 3) | (1 << 4);
    Object.assign(f.storage.scales15d4[3]!, {x: 2, y: 3, z: 4});
    f.runtime.rebuildActor(f.id, 1);
    check(f.output(3)[3] === 13 && f.output(3)[7] === 26 && f.output(3)[11] === 39,
      'ordinary branch builds the actual nonroot incoming parent before secondary continuation');
    check(f.output(4)[3] === 21 && f.output(4)[7] === 50 && f.output(4)[11] === 87 && f.output(4)[0] === 1 - 2 ** -23,
      'genuine4784c uses nonroot parent3 translation and scale, not root0');
    check(f.events.filter(v => v.startsWith('transform:')).join(',') === 'transform:3',
      'secondary continuation passes incoming parent3 to actual MultVec');
  }
  {
    const f = fixture(); terrainCorrectionFixture(f); const counts = bindSecondary(f);
    f.state.mask1d70 = 2; let changed = false;
    f.hooks.matrix = matrix => {
      if (matrix === f.matrixIds[1] && !changed) {changed = true; counts.secondary1a94[0]!.joint00 = 2;}
    };
    // The adapter returns the real matrix. Its synchronous mutation happens
    // after destination1 was selected, before the current joint's pose lookup.
    f.runtime.rebuildActor(f.id, 1);
    check(changed && counts.secondary1a94[0]!.joint00 === 2 && f.output(1)[0] === 1 - 2 ** -23,
      'selected record may change after destination capture without redirecting the captured target');
    check(f.output(1)[3] === 11 && f.output(1)[7] === 22 && f.output(1)[11] === 33,
      '4784c raw translation remains traversal pose1, not the selected record later joint2');
    check(f.output(2)[3] === -12 && f.output(2)[7] === -22 && f.output(2)[11] === -32,
      'late joint-byte mutation does not write the disabled joint2 matrix');
  }
  {
    const f = fixture(); bindSecondary(f);
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'actual terrain correction sources are not bound');
    check(f.output(1)[3] === 11 && f.output(1)[7] === 22 && f.output(1)[11] === 33 && f.output(1)[0] === 1,
      'missing actual terrain sources refuses only after transform and sequential translation prefix');
  }
  for (const index of [3, 7, 11]) {
    const f = fixture(); const g = terrainCorrectionFixture(f); bindSecondary(f);
    Object.defineProperty(f.output(1), String(index), {writable: false}); g.state.field670 = NaN;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'non-writable');
    check(f.output(1)[3] === (index === 3 ? -11 : 11) && f.output(1)[7] === (index <= 7 ? -21 : 22) && f.output(1)[11] === -31,
      'translation refusal retains only earlier individual4784c stores');
    check(!f.events.includes('movement'), 'translation store failure precedes movement670 read');
  }
  {
    const f = fixture(), g = terrainCorrectionFixture(f); bindSecondary(f); g.state.field670 = NaN;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'field670');
    check(f.output(1)[11] === 33 && !f.events.some(v => v.startsWith('normal:')), 'late actual clearance failure retains complete translation without calling normal');
  }
  {
    const f = fixture(), g = terrainCorrectionFixture(f), counts = bindSecondary(f);
    counts.secondary1a94[0]!.axis01 = NaN; counts.secondary1a94[0]!.axis02 = NaN;
    g.hooks.normal = () => {counts.secondary1a94[0]!.axis01 = 2; counts.secondary1a94[0]!.axis02 = 1;};
    f.hooks.transformed = () => {g.state.field670 = 11;};
    f.runtime.rebuildActor(f.id, 1);
    check(f.events.includes('normal:11') && f.output(1)[0] === 1 - 2 ** -23,
      'clearance reads after real transform and axes read after real normal effect, never eagerly snapshotted');
  }
  {
    const f = fixture(), g = terrainCorrectionFixture(f), counts = bindSecondary(f);
    g.hooks.normal = () => {counts.secondary1a94[0]!.axis01 = 255;};
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'terrain axes');
    check(f.events.includes('orient:1:-1:1') && f.output(1)[11] === 33 && f.output(1)[0] === 1,
      'fresh signed-axis refusal occurs at genuine backend after normal and translation');
  }
  {
    const f = fixture(), g = terrainCorrectionFixture(f); bindSecondary(f);
    g.hooks.replaceMovement = true;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'movement owner changed');
    check(f.output(1)[11] === 33 && !f.events.some(v => v.startsWith('normal:')), 'actual movement owner identity is retained, not replaced by copied field670');
  }
  {
    const f = fixture(), g = terrainCorrectionFixture(f); bindSecondary(f);
    g.movementAdapter.getActorBinding = () => {throw Error('replacement movement method');};
    g.terrainAdapter.queryNormal8003de80 = () => {throw Error('replacement normal method');};
    f.matrixAdapter.transformPoint = () => {throw Error('replacement transform method');};
    f.matrixAdapter.orientTerrainMatrix = () => {throw Error('replacement orientation method');};
    f.runtime.rebuildActor(f.id, 1);
    check(f.output(1)[0] === 1 - 2 ** -23, 'captured movement, normal, transform and orientation methods keep real receivers');
    rejects(() => f.runtime.bindTerrainCorrectionSources(f.id, g.sources), 'already bound');
  }
  for (const stage of ['transform', 'movement', 'normal', 'orientation'] as const) {
    const f = fixture(), g = terrainCorrectionFixture(f); bindSecondary(f);
    const reentry = () => {try {f.runtime.rebuildActor(f.id, 1);} catch { /* deliberately caught */ }};
    if (stage === 'transform') f.hooks.transformed = reentry;
    if (stage === 'movement') g.hooks.movement = reentry;
    if (stage === 'normal') g.hooks.normal = reentry;
    if (stage === 'orientation') f.hooks.oriented = reentry;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'caught same-runtime reentry');
    check(f.output(1)[7] === (stage === 'transform' ? -21 : 22), 'caught reentry poisons at reached secondary adapter boundary without rolling back prefix');
    check(f.output(1)[0] === (stage === 'orientation' ? 1 - 2 ** -23 : 1), 'only completed genuine orientation retains oriented basis');
    check(f.output(3)[7] === -23, 'poison prevents subsequent topology continuation');
  }
  for (const stage of ['transform', 'normal', 'orientation'] as const) {
    const f = fixture(), g = terrainCorrectionFixture(f); bindSecondary(f);
    if (stage === 'transform') f.hooks.transformed = () => Promise.resolve();
    if (stage === 'normal') g.hooks.result = Promise.resolve(1);
    if (stage === 'orientation') f.hooks.oriented = () => Promise.resolve();
    rejects(() => f.runtime.rebuildActor(f.id, 1), stage === 'normal' ? 'normal query synchronous return' : 'synchronously');
    check(f.output(1)[7] === (stage === 'transform' ? -21 : 22), 'non-synchronous genuine-effect return retains only completed source prefix');
  }
  {
    const f = fixture(), g = terrainCorrectionFixture(f); bindSecondary(f);
    g.hooks.normal = () => {f.topology(1)[1] = 255; f.topology(1)[0] = 255;};
    f.runtime.rebuildActor(f.id, 1);
    check(f.output(3)[7] === -23 && f.output(2)[7] === -22, 'topology is freshly read after completed secondary effect');
  }
  {
    const f = fixture(), g = terrainCorrectionFixture(f); bindSecondary(f);
    f.actual.pos.x = 8000; g.state.field670 = 0;
    f.runtime.rebuildActor(f.id, 1);
    check(f.output(1)[3] === 8001 && f.output(1)[0] === 1 - 2 ** -23,
      'source ignores real normal-query return0 and orients with its actual initialized default normal');
  }
  {
    const f = fixture();
    check(!Object.hasOwn(f.storage.corrections18d4[1]!, 'x'), 'joint1 stores only Y/Z, never a shadow steerYaw');
    const storage = {...f.storageInput, corrections18d4: f.storageInput.corrections18d4.map(v => ({...v}))};
    Object.defineProperty(storage.corrections18d4[1], 'x', {get() {throw Error('unused caller X getter');}});
    const runtime = createSourceActorWorldMatrixRuntime(f.sources);
    runtime.bindActor(f.id, f.actual, f.input, storage); runtime.updateActor(f.id);
    check(f.output(1)[7] === 27 && !Object.hasOwn(runtime.getStorage(f.id).corrections18d4[1]!, 'x'),
      'binding ignores even accessor X at index1; actual steerYaw is sole authority');
    const missing = {...f.storageInput, corrections18d4: [{y: 0, z: 0}]};
    rejects(() => createSourceActorWorldMatrixRuntime(f.sources).bindActor(f.id, f.actual, f.input, missing), 'x: own data');
  }
  {
    const f = fixture(); f.actual.steerYaw = NaN;
    rejects(f.update, 'steerYaw: integer out of bounds');
    check(f.output(1)[7] === 27 && f.output(3)[7] === -23 && f.events.at(-1) === 'joint:1:scratch',
      'invalid actual steerYaw is read only after joint1 firstConcat');
  }
  {
    const f = fixture(); f.hooks.composed = () => {f.actual.steerYaw = 65535;};
    rejects(f.update, 'nonzero short correction');
    check(f.output(1)[7] === 27 && f.events.at(-1) === 'correct', 'late live steerYaw uses unsigned BAM bits sign-extended to signed16');
    delete f.hooks.composed; f.actual.steerYaw = 0; f.storage.corrections18d4[1]!.y = 1;
    rejects(f.update, 'nonzero short correction'); check(f.output(1)[7] === 27, 'owned Y correction remains live after firstConcat');
  }
  {
    const f = fixture(); f.actual.steerYaw = NaN; f.state.mask1d70 = 0xfffffffd;
    f.update(); check(f.output(2)[7] === -17, 'disabled joint1 never reads steerYaw alias');
  }
  for (const count of [0, 128, 255]) {
    const f = fixture(); f.mapping.getActor(f.id).jointCount1d90 = count;
    f.state.mode4a0 = NaN; f.hooks.matrix = () => {throw Error('zero copies must not resolve matrix');};
    f.hooks.pose = () => {throw Error('copy never reads poses');};
    f.runtime.copyActorMatrices(f.id, null); f.runtime.copyActorMatrices(f.id, Symbol('unowned target'));
    check(f.events.length === 0 && f.output(0)[7] === -20, 'nonpositive signed source count ignores target and all matrix storage');
  }
  {
    const f = fixture(), target = copyTarget(f);
    f.mapping.getActor(target.id).jointCount1d90 = NaN; f.runtime.getActorBinding(target.id).mode4a0 = NaN;
    f.state.mode4a0 = NaN; f.state.flags48a = NaN; f.pose(1).quaternion.x = 3; f.actual.pos.y = NaN;
    f.hooks.pose = () => {throw Error('copy never reads poses');};
    f.output(0)[1] = -0; f.runtime.copyActorMatrices(f.id, target.id);
    check(f.events.join(',') === 'copy:0,copy:1,copy:2,copy:3,copy:4,copy:5', '47a2c copies source world slots to same target indices in order');
    check(target.output(5)[7] === -25 && Object.is(target.output(0)[1], -0), 'copy preserves actual bits without rebuilding source or target');
    check(f.matrices.getMatrix(target.storage.copy114)[0] === 52 && f.matrices.getMatrix(target.storage.copy1aa4)[0] === 53 &&
      f.matrices.getMatrix(target.storage.scratch)[0] === 54, 'copy does not touch auxiliary target matrices');
  }
  {
    const f = fixture(), target = copyTarget(f); f.mapping.getActor(f.id).jointCount1d90 = 1;
    let copied = 0, conditions = 0; f.hooks.mapping = () => {conditions++;};
    f.hooks.copied = () => {copied++; f.mapping.getActor(f.id).jointCount1d90 = copied === 1 ? 3 : 128;};
    f.runtime.copyActorMatrices(f.id, target.id);
    check(copied === 2 && conditions === 3 && target.output(1)[7] === -21 && target.output(2)[7] === 51,
      'signed source count reloads each condition, including final stop, never snapshots initial count');
  }
  {
    const f = fixture(), target = copyTarget(f, 1); f.mapping.getActor(f.id).jointCount1d90 = 2;
    rejects(() => f.runtime.copyActorMatrices(f.id, target.id), 'world matrix: addressing outside');
    check(target.output(0)[7] === -20 && f.events.join(',') === 'copy:0', 'missing later target slot preserves completed earlier copy');
    rejects(() => f.runtime.copyActorMatrices(f.id, null), 'matrix-copy target');
  }
  {
    const f = fixture(), target = copyTarget(f, 2); f.mapping.getActor(f.id).jointCount1d90 = 2;
    f.output(1)[4] = NaN;
    rejects(() => f.runtime.copyActorMatrices(f.id, target.id), 'matrix[4]');
    check(target.output(0)[7] === -20 && target.output(1)[3] === -11 && target.output(1)[4] === 51,
      'later real Copy failure preserves prior matrix and completed pairs');
  }
  {
    const f = fixture(); f.mapping.getActor(f.id).jointCount1d90 = 2; f.output(0)[1] = -0;
    f.runtime.copyActorMatrices(f.id, f.id);
    check(Object.is(f.output(0)[1], -0) && f.output(1)[7] === -21 && f.events.join(',') === 'copy:0,copy:1',
      'source equals target uses actual pairwise alias-safe Copy');
    f.mapping.getActor(f.id).jointCount1d90 = NaN;
    rejects(() => f.runtime.copyActorMatrices(f.id, null), 'jointCount1d90: integer out of bounds');
  }
  {
    const f = fixture(); let changed = false;
    const provider = {getActor(id: symbol) {
      const actual = f.mapping.getActor(id); return changed ? {...actual} : actual;
    }, getLayout: f.mapping.getLayout};
    const runtime = createSourceActorWorldMatrixRuntime({...f.sources, mapping: provider});
    runtime.bindActor(f.id, f.actual, f.input, f.storageInput); changed = true;
    rejects(() => runtime.copyActorMatrices(f.id, f.id), 'mapping owner changed');
    check(f.events.length === 0, 'copy refuses replaced actual source mapping record before matrix work');
  }
  {
    const f = fixture(), target = copyTarget(f, 1); f.mapping.getActor(f.id).jointCount1d90 = 1;
    f.matrixAdapter.copy = () => {throw Error('replacement copy must not run');};
    f.runtime.copyActorMatrices(f.id, target.id);
    check(target.output(0)[7] === -20, 'copy method and original receiver are captured');
    f.hooks.copied = () => Promise.resolve();
    rejects(() => f.runtime.copyActorMatrices(f.id, target.id), 'synchronously');
    check(target.output(0)[7] === -20, 'nonvoid Copy result refuses after completed real copy');
  }
  for (const operation of ['prepare', 'rebuild', 'copy', 'bind', 'getWorldMatrix'] as const) {
    const f = fixture(); f.hooks.effect = () => {
      try {
        if (operation === 'getWorldMatrix') f.runtime.getWorldMatrix(f.id, 0);
        else if (operation === 'prepare') f.runtime.prepareActor(f.id);
        else if (operation === 'rebuild') f.runtime.rebuildActor(f.id, 0);
        else if (operation === 'copy') f.runtime.copyActorMatrices(f.id, f.id);
        else f.runtime.bindCorrectedTraversalState(f.id, {count1d96: 0, count1d97: 0});
      } catch { /* intentionally swallowed adapter reentry */ }
    };
    rejects(() => f.runtime.rebuildActor(f.id, 0), 'caught same-runtime reentry');
    check(f.output(0)[7] === 0 && f.events.join(',') === 'identity', 'every new guarded world method poisons caught reentry');
  }
  {
    const f = fixture(), target = copyTarget(f, 1); f.mapping.getActor(f.id).jointCount1d90 = 1;
    f.hooks.copied = () => {try {f.runtime.prepareActor(f.id);} catch { /* caught reentry */ }};
    rejects(() => f.runtime.copyActorMatrices(f.id, target.id), 'caught same-runtime reentry');
    check(target.output(0)[7] === -20 && f.state.adjusted1d54.y === 82, 'outer copy keeps completed copy and blocks nested preparation');
    delete f.hooks.copied; f.runtime.copyActorMatrices(f.id, target.id);
  }
}


/** Compatibility entry point for callers of the former flat-only boundary suite. */
export function runActorWorldNonflatTerrainBoundarySelfTests(): void {
  runActorWorldSlopedTerrainContinuationSelfTests();
}

/** Genuine 4784c -> 3de80 -> 45918 and its descendant continuation. These are
 * synthetic, explicit source cells, not retail hydration or a normal callback. */
export function runActorWorldSlopedTerrainContinuationSelfTests(): void {
  const word = new DataView(new ArrayBuffer(4));
  const fromBits = (bits: number): number => {word.setUint32(0, bits); return word.getFloat32(0);};
  const bits = (value: number): number => {word.setFloat32(0, value); return word.getUint32(0);};
  const normal = {x: 0, y: fromBits(0x3f199999), z: fromBits(0x3f4ccccd)};
  const prefix = 'identity,translate,correct,scale,copy114,copy1aa4,transform:0,movement,normal:0,orient:1:2:1';
  const suffix = ',joint:3:0,joint:4:3,joint:2:1,joint:5:1';
  const finalBits = [0x3f7ffffe, 0, 0, 0x41300000, 0, 0x3f199997, 0xbf4ccccb, 0x41b00000,
    0, 0x3f4ccccb, 0x3f199997, 0x42040000];
  const normalizedBits = [0x3f7fffff, 0, 0, 0x41300000, 0x80000000, 0x3f199998, 0xbf4ccccc, 0x41b00000,
    0x80000000, 0x3f4ccccc, 0x3f199998, 0x42040000];
  const sameBits = (matrix: number[], expected: number[]): boolean => matrix.every((v, i) => bits(v) === expected[i]);
  const translated = (initial: number[]): number[] => initial.map((v, i) => i === 3 ? 11 : i === 7 ? 22 : i === 11 ? 33 : v);
  const unchanged = (a: number[], b: number[]): boolean => a.every((v, i) => Object.is(v, b[i]));
  {
    const f = fixture(), g = terrainCorrectionFixture(f, true, normal); bindSecondary(f);
    const matrix = f.output(1), globals = g.terrain.getTerrainGlobals();
    const queried = {x: 71, y: 72, z: 73};
    check(g.terrain.queryNormal8003de80(f.id, {x: 11, y: 22, z: 33}, 0, queried) === 1 &&
      bits(queried.x) === 0 && bits(queried.y) === 0x3f199999 && bits(queried.z) === 0x3f4ccccd,
      'genuine 3de80 loads the viable raw slope from the owned triangle');
    f.events.length = 0; f.runtime.rebuildActor(f.id, 1);
    check(sameBits(matrix, finalBits), 'sloped secondary final basis, translation and Concat zero signs match independent bit witness');
    check(f.events.join(',') === prefix + suffix, 'sloped secondary completes exactly once before both genuine descendant branches');
    check(f.output(3)[3] === 13 && f.output(3)[7] === 26 && f.output(3)[11] === 39 && f.output(4)[7] === 34,
      'sloped current does not replace incoming parent for the side branch');
    check(sameBits(f.output(2), [0x3f7ffffe, 0, 0, 0x41500000, 0, 0x3f199997, 0xbf4ccccb, 0x419ccccd,
      0, 0x3f4ccccb, 0x3f199997, 0x421f3333]) &&
      sameBits(f.output(5), [0x3f7ffffe, 0, 0, 0x41800000, 0, 0x3f199997, 0xbf4ccccb, 0x41800000,
        0, 0x3f4ccccb, 0x3f199997, 0x4247ffff]),
      'both continuation matrices consume the actual slope with independently rounded descendant bit witnesses');
    check(f.runtime.getWorldMatrix(f.id, 1) === matrix && f.runtime.getActualActor(f.id) === f.actual &&
      g.terrain.getTerrainGlobals() === globals, 'sloped continuation retains actual world, actor, matrix and terrain owners');
    const before = matrix.slice(), descendants = [f.output(2).slice(), f.output(3).slice()];
    f.events.length = 0;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'finite estimate proof domain');
    check(unchanged(matrix, before) && unchanged(f.output(2), descendants[0]!) && unchanged(f.output(3), descendants[1]!) &&
      f.events.join(',') === prefix, 'a second orientation refuses its reached shrunken incoming norm without replaying descendants');
  }
  let accepted = 0;
  for (const sy of [-1, 1]) for (const sz of [-1, 1]) for (const scale of [0.5, 1, 2, 4, 8]) {
    const f = fixture(); terrainCorrectionFixture(f, true, {x: 0, y: sy * normal.y, z: sz * normal.z}); bindSecondary(f);
    f.actual.pos.y = 100; // Keep all signed planes below the real normal-query point.
    f.output(1)[0] = scale; f.output(1)[5] = scale; f.output(1)[10] = scale;
    f.runtime.rebuildActor(f.id, 1);
    const expected = finalBits.map(fromBits); expected[7] = 102;
    expected[0] = fromBits(0x3f7ffffe) * scale;
    expected[5] = sy * fromBits(0x3f199997) * scale; expected[6] = -sz * fromBits(0x3f4ccccb) * scale;
    expected[9] = sz * fromBits(0x3f4ccccb) * scale; expected[10] = sy * fromBits(0x3f199997) * scale;
    check(unchanged(f.output(1), expected) && f.events.join(',') === prefix + suffix,
      `signed sloped normal and incoming scale ${sy}/${sz}/${scale} retain genuine continuation`);
    accepted++;
  }
  check(accepted === 20, 'all four slope signs and five positive incoming scales were executed');
  for (const doubled of [false, true]) {
    const f = fixture(); terrainCorrectionFixture(f, true, doubled ? {x: 0, y: 2 * normal.y, z: 2 * normal.z} : normal); bindSecondary(f);
    if (!doubled) {f.output(1)[0] = -1; f.output(1)[5] = -1; f.output(1)[10] = -1;}
    f.runtime.rebuildActor(f.id, 1);
    const expected = finalBits.slice();
    if (!doubled) {expected[0] = 0xbf7ffffe; expected[6] = 0x3f4ccccb; expected[10] = 0xbf199997;}
    check(sameBits(f.output(1), expected) && f.events.join(',') === prefix + suffix,
      doubled ? 'doubled raw normal reaches norms 16/4/4 and real descendants' : 'negative incoming basis restores actual positive magnitudes and reference sign');
  }
  for (const rejected of [{x: 0, y: Math.fround(0.6), z: Math.fround(0.8)},
    {x: 1 / 64, y: 1, z: 0}, {x: 0, y: -2, z: 1 / 32},
    {x: 0, y: normal.y / 2, z: normal.z / 2}, {x: 0, y: normal.y * 4, z: normal.z * 4}]) {
    const f = fixture(), g = terrainCorrectionFixture(f, true, rejected); bindSecondary(f);
    const before = translated(f.output(1)), descendant = f.output(3).slice(), globals = g.terrain.getTerrainGlobals();
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'finite estimate proof domain');
    check(unchanged(f.output(1), before) && unchanged(f.output(3), descendant) && f.events.join(',') === prefix,
      'unsupported actual computed normalization norm preserves translation only, without guessed normalization or replay');
    check(g.terrain.getTerrainGlobals() === globals && f.runtime.getActualActor(f.id) === f.actual,
      'unsupported sloped norm retains actual terrain and actor owners');
  }
  {
    const f = fixture(); terrainCorrectionFixture(f, true, normal); bindSecondary(f);
    // A retained reference parallel to the raw nonflat normal reaches a
    // near-zero first cross below the authenticated constructor threshold.
    f.output(1)[0] = 0; f.output(1)[4] = normal.y; f.output(1)[8] = normal.z;
    const before = translated(f.output(1));
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'fallback construction');
    check(unchanged(f.output(1), before) && f.events.join(',') === prefix,
      'degenerate first construction retains only translation and never synthesizes another reference');
  }
  {
    const f = fixture(); terrainCorrectionFixture(f, true, {x: 0, y: normal.y * 2 ** 65, z: normal.z * 2 ** 65}); bindSecondary(f);
    const before = translated(f.output(1));
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'single product: expected finite source float32');
    check(unchanged(f.output(1), before) && f.events.join(',') === prefix,
      'constructor arithmetic overflow is lazy after genuine terrain and translation, with no basis or descendant output');
  }
  const order = [0, 4, 8, 1, 5, 9, 2, 6, 10];
  for (let stop = 0; stop < order.length; stop++) {
    const f = fixture(); terrainCorrectionFixture(f, true, normal); bindSecondary(f);
    const expected = translated(f.output(1));
    Object.defineProperty(f.output(1), String(order[stop]), {writable: false});
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'non-writable');
    for (const index of order.slice(0, stop)) expected[index] = fromBits(normalizedBits[index]!);
    check(unchanged(f.output(1), expected) && f.events.join(',') === prefix && f.output(3)[7] === -23,
      `sloped secondary non-writable basis store ${stop} retains exactly its signed-zero column-major prefix`);
  }
  for (const index of [3, 7, 11]) {
    const f = fixture(); terrainCorrectionFixture(f, true, normal); bindSecondary(f);
    Object.defineProperty(f.output(1), String(index), {writable: false});
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'non-writable');
    check(f.output(1)[3] === (index === 3 ? -11 : 11) && f.output(1)[7] === (index <= 7 ? -21 : 22) &&
      f.output(1)[11] === -31 && !f.events.includes('movement'),
      'sloped secondary translation refusal stops before terrain query and retains only earlier stores');
  }
  {
    const f = fixture(); terrainCorrectionFixture(f, true, normal); bindSecondary(f);
    f.hooks.oriented = () => {try {f.runtime.rebuildActor(f.id, 1);} catch { /* deliberately caught */ }};
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'caught same-runtime reentry');
    check(sameBits(f.output(1), finalBits) && f.events.join(',') === prefix && f.output(3)[7] === -23,
      'completed real sloped orientation remains visible while reentry poison prevents any descendant replay');
  }
}

// Zero origin is deliberate: RN32(target - MultVec(parent, rawPose)) is the
// exact independent witness, with no assumed reversibility of target+offset.
function slopedPrimaryFixture(firstLength = 2) {
  const f = primaryFixture(), secondLength = firstLength === 2 ? .5 : 1;
  Object.assign(f.actual.pos, zero()); Object.assign(f.state.offset1dbc, zero());
  Object.assign(f.pose(1).translation, zero());
  f.pose(2).translation.y = firstLength; f.pose(3).translation.y = secondLength;
  f.runtime.prepareActor(f.id); f.runtime.rebuildActor(f.id, 0);
  // Verify mode0 produced the exact incoming basis too; no fixture reseeding
  // hides quaternion/Concat signed zeros or substitutes retained world data.
  for (const i of [1, 2, 3]) {
    const matrix = f.output(i);
    check(matrix[3] === 0 && matrix[7] === (i === 1 ? 0 : i === 2 ? firstLength : firstLength + secondLength) && matrix[11] === 0,
      'real mode0 retained positions provide the measured bone pair');
    for (const k of [0, 1, 2, 4, 5, 6, 8, 9, 10]) check(Object.is(matrix[k], k % 5 === 0 ? 1 : 0),
      'mode0 retained basis matches exact independent incoming identity');
  }
  const word = new DataView(new ArrayBuffer(4));
  word.setUint32(0, 0x3f199999); f.placement.y = word.getFloat32(0);
  word.setUint32(0, 0x3f4ccccd); f.placement.z = word.getFloat32(0); f.placement.x = 0;
  f.events.length = 0;
  return f;
}
export function runActorWorldSlopedPrimaryPlacementSelfTests(): void {
  const word = new DataView(new ArrayBuffer(4));
  const bits = (v: number): number => {word.setFloat32(0, v); return word.getUint32(0);};
  const same = (matrix: readonly number[], words: readonly number[]) => matrix.every((v, i) => bits(v) === words[i]);
  const prefix = 'identity,translate,correct,scale,copy114,copy1aa4,primary:1:0';
  const suffix = ',joint:4:0,joint:5:4,joint:6:1,joint:7:6,joint:3:2';
  for (const witness of slopedPrimaryWitnesses) {
    const f = slopedPrimaryFixture(witness.firstLength); f.placement.bend0f = witness.bend;
    const ownedCurrent = f.runtime.getWorldMatrix(f.id, 1), ownedNext = f.output(2), ownedEnd = f.output(3);
    let placementCalls = 0;
    f.hooks.placed = () => {
      placementCalls++;
      check(same(ownedCurrent, witness.current) && same(ownedNext, witness.adjacent), 'real world placement exact two Concat matrices');
      check(same(ownedEnd, witness.retainedEnd), 'retained end unchanged at placement boundary');
    };
    f.runtime.rebuildActor(f.id, 1);
    check(placementCalls === 1 && f.events.join(',') === prefix + suffix, 'sloped primary completes once before genuine branches and skipped-next continuation');
    check(f.runtime.getWorldMatrix(f.id, 1) === ownedCurrent && f.output(2) === ownedNext && f.output(3) === ownedEnd,
      'actual live matrix records and handles remain owned');
    check(f.output(4)[7] === 4 && f.output(5)[7] === 9, 'current side branch retains incoming root parent');
    check(!same(ownedEnd, witness.retainedEnd), 'later ordinary end traversal really writes end, unlike placement boundary');
  }
  {
    const f = slopedPrimaryFixture();
    // Physical adjacent matrix2 remains the placement destination, even though
    // current byte0 selects a different skipped node and raw pose4 is invalid.
    f.topology(1)[0] = 4; f.topology(1)[1] = 255;
    f.topology(4)[0] = 255; f.topology(4)[1] = 255;
    f.pose(4).translation.y = NaN;
    f.runtime.rebuildActor(f.id, 1);
    check(f.events.join(',') === prefix && same(f.output(2), slopedPrimaryWitnesses[3]!.adjacent),
      'physical current+0x30 and raw pose current+1 are independent of topology-selected skipped node');
  }
  {
    const f = slopedPrimaryFixture(1), witness = slopedPrimaryWitnesses.find(w => w.firstLength === 1 && w.bend === 254)!;
    let changed = false;
    f.placement.axis0d = 0; f.placement.axis0e = 0; f.placement.bend0f = 0;
    f.hooks.matrix = id => {
      if (!changed && id === f.matrixIds[1]) {
        changed = true;
        // Current raw pose was captured before destination lookup. Adjacent raw
        // pose and axes/bend are later live reads, never cached during scan.
        f.pose(1).translation.y = 99; f.pose(2).translation.y = 1;
        f.placement.axis0d = 2; f.placement.axis0e = 1; f.placement.bend0f = 254;
      }
    };
    f.hooks.placed = () => {
      check(same(f.output(1), witness.current) && same(f.output(2), witness.adjacent), 'captured current raw pose and fresh axes/bend survive live callback mutation');
      f.counts.count1d96 = 0; f.topology(1)[1] = 255; f.topology(2)[0] = 255; f.topology(2)[1] = 255;
    };
    f.runtime.rebuildActor(f.id, 1);
    check(changed && f.events.join(',') === prefix, 'post-placement topology and correction counts are read live');
  }
  {
    const f = slopedPrimaryFixture();
    f.hooks.matrix = id => {if (id === f.matrixIds[1]) f.pose(2).translation.z = NaN;};
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'primary next.z');
    check(f.output(1)[0] === 1 && f.output(2)[7] === 2, 'adjacent raw pose failure precedes current translation and basis work');
  }
  for (const stop of [0, 4, 8, 1, 5, 9, 2, 6, 10]) {
    const f = slopedPrimaryFixture(); Object.defineProperty(f.output(1), String(stop), {writable: false});
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'non-writable');
    check(f.events.join(',') === prefix && f.output(2)[7] === 2, 'world orientation partial-store refusal does not traverse later branches');
  }
  {
    const f = slopedPrimaryFixture(); f.placement.y = Math.fround(.6);
    f.output(1)[3] = f.output(2)[3] = f.output(3)[3] = 9;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'finite estimate proof domain');
    check(f.output(1)[3] === 0 && f.output(1)[5] === 1 && f.output(2)[3] === 9 && f.events.join(',') === prefix,
      'literal .6/.8 refuses reached normalization after raw translation, before basis or traversal');
    // Standalone world retry is allowed, but restore valid explicit retained
    // geometry rather than pretending a failed call rolls its stores back.
    f.output(2)[3] = f.output(3)[3] = 0; word.setUint32(0, 0x3f199999); f.placement.y = word.getFloat32(0);
    f.events.length = 0; f.runtime.rebuildActor(f.id, 1);
    check(f.events.join(',') === prefix + suffix, 'fresh world call retries after input repair, without invented frame poison');
  }
  for (const stage of ['reentry', 'promise'] as const) {
    const f = slopedPrimaryFixture();
    f.hooks.placed = () => {
      if (stage === 'promise') return Promise.resolve();
      try {f.runtime.rebuildActor(f.id, 1);} catch { /* deliberately swallowed */ }
      return undefined;
    };
    rejects(() => f.runtime.rebuildActor(f.id, 1), stage === 'reentry' ? 'caught same-runtime reentry' : 'synchronously');
    check(same(f.output(1), slopedPrimaryOrientation) && same(f.output(2), slopedPrimaryWitnesses[3]!.adjacent) &&
      same(f.output(3), slopedPrimaryWitnesses[3]!.retainedEnd) && f.events.join(',') === prefix,
      'same-call poison preserves real completed placement and blocks traversal');
  }
  for (const change of ['array', 'record'] as const) {
    const f = slopedPrimaryFixture(); f.runtime.rebuildActor(f.id, 1);
    if (change === 'array') f.counts.primary1a14 = [f.placement];
    else f.counts.primary1a14[0] = {...f.placement};
    f.events.length = 0;
    rejects(() => f.runtime.rebuildActor(f.id, 1), change === 'array' ? 'correction storage owner changed' : 'correction slot owner changed');
    check(!f.events.some(e => e.startsWith('primary:')), 'replaced live correction owner cannot enter placement');
  }
  {
    const f = slopedPrimaryFixture(); f.counts.count1d96 = 2; f.counts.primary1a14.push(f.placement); f.placement.joint0c = 255;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'aliased correction slots');
    check(!f.events.some(e => e.startsWith('primary:')), 'duplicate record aliases refuse at reached scan slot');
  }
  for (const owner of ['mapping', 'pose', 'matrix'] as const) {
    const f = slopedPrimaryFixture(); let changed = false;
    const sources = {...f.sources};
    if (owner === 'mapping') sources.mapping = {getActor: f.mapping.getActor, getLayout(id: symbol) {
      const original = f.mapping.getLayout(id); return changed ? {...original} : original;
    }};
    if (owner === 'pose') sources.feedback = {getPose(id: symbol) {
      const original = f.feedback.getPose(id); return changed ? {...original} : original;
    }};
    if (owner === 'matrix') sources.matrices = {...f.sources.matrices, getMatrix(id: symbol) {
      const original = f.matrices.getMatrix(id); return changed ? original.slice() : original;
    }};
    const runtime = createSourceActorWorldMatrixRuntime(sources);
    runtime.bindActor(f.id, f.actual, f.state, f.storageInput); runtime.bindCorrectedTraversalState(f.id, f.counts);
    changed = true;
    rejects(() => runtime.rebuildActor(f.id, 1), `${owner} owner changed`);
    check(!f.events.some(e => e.startsWith('primary:')), 'mapping/pose/matrix identity refusal precedes sloped placement');
  }
}

function flatHalfPrimaryFixture() {
  const f = primaryFixture();
  // The owned mode0 scale produces the basis. Never reseed any matrix.
  (f.storage.scales15d4[1] as {x: number}).x = 2;
  f.runtime.prepareActor(f.id); f.runtime.rebuildActor(f.id, 0);
  const word = new DataView(new ArrayBuffer(4));
  for (const i of [1, 2, 3]) check(f.output(i).every((v, k) => {
    word.setFloat32(0, v); return word.getUint32(0) === flatHalfPrimaryMode0[i - 1]![k];
  }), 'owned X2 mode0 produces exact retained basis/translations without reseeding');
  check(f.state.adjusted1d54.y === 8 && f.pose(1).translation.y === 10 && f.state.flags48a === 0,
    'adjusted1d54 differs from raw bank-zero pose with flags48a&6 clear');
  f.placement.y = 30.5; f.events.length = 0; return f;
}
export function runActorWorldFlatHalfPrimaryPlacementSelfTests(): void {
  const word = new DataView(new ArrayBuffer(4));
  const bits = (v: number) => {word.setFloat32(0, v); return word.getUint32(0);};
  const same = (m: readonly number[], w: readonly number[]) => m.every((v, i) => bits(v) === w[i]);
  const prefix = 'identity,translate,correct,scale,copy114,copy1aa4,primary:1:0';
  const suffix = ',joint:4:0,joint:5:4,joint:6:1,joint:7:6,joint:3:2';
  for (const witness of flatHalfPrimaryWitnesses) {
    const f = flatHalfPrimaryFixture(); f.placement.bend0f = witness.bend;
    const owned = [f.output(1), f.output(2), f.output(3)]; let calls = 0;
    f.hooks.placed = () => {
      calls++;
      check(same(f.output(1), witness.current) && same(f.output(2), witness.adjacent) && same(f.output(3), witness.retainedEnd),
        'genuine half world mode0-to-mode1 six-bend exact placement boundary');
    };
    f.runtime.rebuildActor(f.id, 1);
    check(calls === 1 && f.events.join(',') === prefix + suffix, 'half placement followed once by genuine world continuation');
    check(owned.every((m, i) => m === f.output(i + 1)) && !same(f.output(3), witness.retainedEnd),
      'world owners persist but continuation really rebuilds end after placement');
  }
  {
    const f = flatHalfPrimaryFixture(); f.topology(1)[0] = 4; f.topology(1)[1] = 255;
    f.topology(4)[0] = 255; f.topology(4)[1] = 255; f.pose(4).translation.y = NaN;
    f.runtime.rebuildActor(f.id, 1);
    check(f.events.join(',') === prefix && same(f.output(2), flatHalfPrimaryWitnesses[3]!.adjacent),
      'half uses physical adjacency and raw pose2, not skipped topology node4');
  }
  {
    const f = flatHalfPrimaryFixture(); let changed = false;
    f.placement.axis0d = 0; f.placement.axis0e = 0; f.placement.bend0f = 0; f.placement.y = 99;
    f.hooks.matrix = id => {if (!changed && id === f.matrixIds[1]) {
      changed = true; f.pose(1).translation.y = 99;
      Object.assign(f.placement, {axis0d: 2, axis0e: 1, bend0f: 254, y: 30.5});
    }};
    f.hooks.placed = () => {
      const witness = flatHalfPrimaryWitnesses[1]!;
      check(same(f.output(1), witness.current) && same(f.output(2), witness.adjacent), 'captured raw current and fresh correction survive late observer mutation');
      f.counts.count1d96 = 0; f.topology(1)[1] = 255; f.topology(2)[0] = 255; f.topology(2)[1] = 255;
    };
    f.runtime.rebuildActor(f.id, 1); check(changed && f.events.join(',') === prefix, 'post-placement topology/counts remain live');
  }
  for (const stage of ['reentry', 'promise'] as const) {
    const f = flatHalfPrimaryFixture();
    f.hooks.placed = () => {if (stage === 'promise') return Promise.resolve();
      try {f.runtime.rebuildActor(f.id, 1);} catch { /* deliberately swallowed */ } return undefined;};
    rejects(() => f.runtime.rebuildActor(f.id, 1), stage === 'reentry' ? 'caught same-runtime reentry' : 'synchronously');
    check(f.events.join(',') === prefix && same(f.output(1), flatHalfPrimaryWitnesses[3]!.current) &&
      same(f.output(2), flatHalfPrimaryWitnesses[3]!.adjacent) && same(f.output(3), flatHalfPrimaryMode0[2]!),
      'half observer poison retains completed placement but prevents continuation');
    // Fresh genuine mode0 rebuild explicitly restores retained operands.
    delete f.hooks.placed; f.runtime.rebuildActor(f.id, 0); f.events.length = 0;
    f.runtime.rebuildActor(f.id, 1); check(f.events.join(',') === prefix + suffix, 'fresh mode0 rebuild supports explicit retry, not frame closure');
  }
  for (const scale of [1, 2]) {
    const f = flatHalfPrimaryFixture();
    if (scale === 1) {(f.storage.scales15d4[1] as {x: number}).x = 1; f.runtime.rebuildActor(f.id, 0);}
    else f.placement.y = 32;
    f.events.length = 0;
    rejects(() => f.runtime.rebuildActor(f.id, 1), scale === 1 ? 'finite estimate proof domain' : 'positive sine square');
    check(f.events.join(',') === prefix && f.output(1)[7] === 30 && f.output(2)[7] === 30 && f.output(3)[7] === 30.5,
      'half negative witnesses stop at reached operation after translation without continuation');
    check(bits(f.output(1)[0]!) === (scale === 1 ? 0x3f800000 : 0x3ffffffe), 'identity fails before basis while Y2 preserves completed basis');
  }
  for (const stop of [0, 4, 8, 1, 5, 9, 2, 6, 10]) {
    const f = flatHalfPrimaryFixture(); Object.defineProperty(f.output(1), String(stop), {writable: false});
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'non-writable');
    check(f.events.join(',') === prefix && same(f.output(2), flatHalfPrimaryMode0[1]!), 'half world basis fault blocks next/traversal');
  }
  for (const change of ['array', 'record'] as const) {
    const f = flatHalfPrimaryFixture(); f.runtime.rebuildActor(f.id, 1);
    if (change === 'array') f.counts.primary1a14 = [f.placement]; else f.counts.primary1a14[0] = {...f.placement};
    f.events.length = 0;
    rejects(() => f.runtime.rebuildActor(f.id, 1), change === 'array' ? 'correction storage owner changed' : 'correction slot owner changed');
    check(!f.events.some(e => e.startsWith('primary:')), 'half replacement correction owner refuses before placement');
  }
  {
    const f = flatHalfPrimaryFixture(); f.counts.count1d96 = 2; f.counts.primary1a14.push(f.placement); f.placement.joint0c = 255;
    rejects(() => f.runtime.rebuildActor(f.id, 1), 'aliased correction slots');
  }
  for (const owner of ['mapping', 'pose', 'matrix'] as const) {
    const f = flatHalfPrimaryFixture(); let changed = false; const sources = {...f.sources};
    if (owner === 'mapping') sources.mapping = {getActor: f.mapping.getActor, getLayout(id: symbol) {
      const original = f.mapping.getLayout(id); return changed ? {...original} : original;}};
    if (owner === 'pose') sources.feedback = {getPose(id: symbol) {
      const original = f.feedback.getPose(id); return changed ? {...original} : original;}};
    if (owner === 'matrix') sources.matrices = {...f.sources.matrices, getMatrix(id: symbol) {
      const original = f.matrices.getMatrix(id); return changed ? original.slice() : original;}};
    const runtime = createSourceActorWorldMatrixRuntime(sources);
    runtime.bindActor(f.id, f.actual, f.state, f.storageInput); runtime.bindCorrectedTraversalState(f.id, f.counts); changed = true;
    rejects(() => runtime.rebuildActor(f.id, 1), `${owner} owner changed`);
    check(!f.events.some(e => e.startsWith('primary:')), 'half ownership identity failure before placement');
  }
}
