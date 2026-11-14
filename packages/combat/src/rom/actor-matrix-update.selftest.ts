import {createRomActor} from './actor.js';
import {createSourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateBinding} from './actor-matrix-update.js';
import {createSourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import {createSourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-matrix-update-test] ${why}`);}
function rejects(run: () => unknown, text: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(text), `expected ${text}, got ${message}`);
}
const zero = () => ({x: 0, y: 0, z: 0}), unit = () => ({x: 1, y: 1, z: 1});
function fixture(deferBind = false) {
  const unexpected = (): never => {throw Error('unreached fixture animation/setup operation');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const mapping = createSourceActorJointMappingRuntime(joints, feedback,
    {interpretAObj: unexpected, animateRObjs: unexpected, animateDObjs: unexpected}, {convertEulerToQuaternion: unexpected});
  const matrices = createSourceActorJointMatrixRuntime(feedback), events: string[] = [];
  const hooks: {
    prepare?: () => unknown; beforeRebuild?: (mode: 0 | 1) => void; afterRebuild?: (mode: 0 | 1) => unknown;
    copy?: () => unknown; matrixCopy?: (from: symbol, to: symbol) => void;
    world?: () => void; actual?: () => void; movement?: () => void; metadata?: () => void; mapping?: () => void;
    worldMatrix?: (index: number) => void; descriptor?: () => void; replaceDescriptor?: boolean;
    replaceWorld?: boolean; replaceActual?: boolean; replaceMovement?: boolean; replaceMetadata?: boolean; replaceMapping?: boolean;
  } = {};
  const matrixAdapter = {...matrices, copy(from: symbol, to: symbol) {
    check(this === matrixAdapter, 'matrix copy receiver'); matrices.copy(from, to); hooks.matrixCopy?.(from, to);
  }};
  const world = createSourceActorWorldMatrixRuntime({mapping, feedback, matrices: matrixAdapter});
  function addActor() {
    const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
      {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
      {descriptor00: null, scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0})));
    const poses = Array.from({length: 2}, () => Array.from({length: 3}, (_, index) => feedback.createPose({
      translation: {x: index, y: 2 * index, z: 3 * index}, quaternion: {x: 0, y: 0, z: 0, w: 1},
    })));
    const id = mapping.createActor({descriptor4b0: null, jointCount1d90: 3, boundary1d91: 0, boundary1d92: 0,
      boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses});
    const actual = Object.assign(createRomActor(), {flyer741: 0});
    actual.pos = {x: 10, y: 20, z: 30}; actual.stepHeight = 7; actual.controlWord = 0x20000000;
    const slots = Array.from({length: 3}, (_, i) => matrices.createMatrix([1, 0, 0, -10 - i, 0, 1, 0, -20 - i, 0, 0, 1, -30 - i]));
    const copy114 = matrices.createMatrix(Array(12).fill(91)), copy1aa4 = matrices.createMatrix(Array(12).fill(92));
    const scratch = matrices.createMatrix(Array(12).fill(93));
    world.bindActor(id, actual, {mode4a0: 0, mode4a1: 0, flags48a: 0, mask1d70: 7, roll74: 0, yawOffset6b8: 0,
      scale58: unit(), offset1dbc: {x: 4, y: 5, z: 6}, adjusted1d54: {x: 81, y: 82, z: 83}, preRotation1d64: zero()},
    {matrices8d4: slots, copy114, copy1aa4, scratch, topology1994: [[1, 255, 0, 0], [2, 255, 0, 0], [255, 255, 0, 0]],
      corrections18d4: [zero(), {y: 0, z: 0}, zero()], scales15d4: [unit(), unit(), unit()]});
    return {id, actual, slots, poses, worldState: world.getActorBinding(id), storage: world.getStorage(id),
      output: (index: number) => matrices.getMatrix(slots[index]!), pose: (index: number) => feedback.getPose(poses[0]![index]!)};
  }
  const source = addActor();
  // Real movement/metadata owners retain their own bindings. These fixture
  // prerequisite records are explicit; no movement/setup effect is requested.
  const waitRecord = Object.seal({activeMask579: 0, blockedMask1d9a: 0, marker71d: 0});
  const setupRecord = Object.seal({familyBank1d78: null, sharedBank1d7c: null, movement6d8: 1});
  const movement = createSourceActorMovementFollowupRuntime({mapping,
    waits: {getActorBinding: () => waitRecord}, setup: {getActorBinding: () => setupRecord}, matrixOwner: matrices});
  movement.bindActor(source.id, source.actual, {byte661: 0, field66c: 8, field670: 3});
  movement.bindWorldMatrices(source.id, source.slots);
  const metadata = createSourceAnimationSetupMetadataRuntime({descriptors: createSourceAnimationDescriptorBankRuntime(),
    actors: mapping, feedback, attached: {getPartBinding: unexpected}});
  metadata.bindActor(source.id, {byte1d74: 0, byte1d75: 0, byte1d76: 0, byte1d77: 0, byte1d94: 0,
    byte1d95: 0, byte1d98: 0, byte1d99: 0, byte1d9b: 0});
  const worldAdapter = {
    getWorldMatrix(id: symbol, index: number) {check(this === worldAdapter, 'world matrix receiver');
      hooks.worldMatrix?.(index); return world.getWorldMatrix(id, index);},
    getActualActor(id: symbol) {check(this === worldAdapter, 'actual receiver'); hooks.actual?.();
      const value = world.getActualActor(id); return hooks.replaceActual ? {...value} : value;},
    getActorBinding(id: symbol) {check(this === worldAdapter, 'world receiver'); hooks.world?.();
      const value = world.getActorBinding(id); return hooks.replaceWorld ? {...value} : value;},
    bindCorrectedTraversalState(...args: Parameters<typeof world.bindCorrectedTraversalState>) {
      check(this === worldAdapter, 'bind receiver'); world.bindCorrectedTraversalState(...args);
    },
    prepareActor(id: symbol) {check(this === worldAdapter, 'prepare receiver'); events.push('prepare');
      world.prepareActor(id); return hooks.prepare?.() as void;},
    rebuildActor(id: symbol, mode: 0 | 1) {check(this === worldAdapter, 'rebuild receiver'); events.push(`rebuild:${mode}`);
      hooks.beforeRebuild?.(mode); world.rebuildActor(id, mode); return hooks.afterRebuild?.(mode) as void;},
    copyActorMatrices(...args: Parameters<typeof world.copyActorMatrices>) {check(this === worldAdapter, 'copy receiver');
      events.push('copy'); world.copyActorMatrices(...args); return hooks.copy?.() as void;},
  };
  const movementAdapter = {
    getDescriptorBinding(id: symbol) {check(this === movementAdapter, 'descriptor receiver'); hooks.descriptor?.();
      const value = movement.getDescriptorBinding(id); return hooks.replaceDescriptor ? {...value} : value;},
    getActorBinding(id: symbol) {check(this === movementAdapter, 'movement receiver'); hooks.movement?.();
    const value = movement.getActorBinding(id); return hooks.replaceMovement ? {...value} : value;}};
  const metadataAdapter = {getActorBinding(id: symbol) {check(this === metadataAdapter, 'metadata receiver'); hooks.metadata?.();
    const value = metadata.getActorBinding(id); return hooks.replaceMetadata ? {...value} : value;}};
  const mappingAdapter = {getActor(id: symbol) {check(this === mappingAdapter, 'mapping receiver'); hooks.mapping?.();
    const value = mapping.getActor(id); return hooks.replaceMapping ? {...value} : value;}};
  const globals = {maskD2: 1}, initial: SourceActorMatrixUpdateBinding =
    {count1d96: 7, count1d97: 8, field1d60: 10, byte660: 0, link4a4: null};
  const sources = {world: worldAdapter, movement: movementAdapter, metadata: metadataAdapter, mapping: mappingAdapter, globals};
  const runtime = createSourceActorMatrixUpdateRuntime(sources), bind = () => runtime.bindActor(source.id, initial);
  if (!deferBind) bind();
  return {...source, world, mapping, feedback, matrices, movement, metadata, globals, initial, sources, hooks, events,
    worldAdapter, movementAdapter, metadataAdapter, mappingAdapter, runtime, bind, addActor,
    state: () => runtime.getActorBinding(source.id), update: () => runtime.updateActor(source.id)};
}
export function runActorMatrixUpdateSelfTests(): void {
  {
    const f = fixture(); f.update();
    check(f.events.join(',') === 'prepare,rebuild:0,rebuild:1', 'one preparation and two actual root rebuilds');
    check(f.state().count1d96 === 0 && f.state().count1d97 === 0 && f.state().field1d60 === 8, 'real ordered clears and damping');
    check(f.worldState.adjusted1d54.y === 7 && f.output(0)[7] === 20 && f.output(1)[7] === 27 && f.output(2)[7] === 31,
      'damping never adds to prepared adjustedY; actual root and traversed matrices');
    check(f.matrices.getMatrix(f.storage.copy114)[7] === 20 && f.matrices.getMatrix(f.storage.copy1aa4)[7] === 27,
      'real root copies and actual movement height remain in second pass');
    f.movement.getActorBinding(f.id).byte661 = 1; f.events.length = 0; f.state().count1d96 = 4;
    f.actual.controlWord = NaN; f.state().field1d60 = NaN; f.update();
    check(f.events.join(',') === 'prepare,rebuild:0' && f.state().count1d96 === 4 && Number.isNaN(f.state().field1d60),
      'live movement661 skips count clears, control and damping, not first rebuild');
  }
  for (const selector of [1, 0x11, 0x81, 0xf1]) {
    const f = fixture(); f.actual.controlWord = 0; f.metadata.getActorBinding(f.id).byte1d98 = selector;
    f.mapping.getActor(f.id).descriptor4b0 = Symbol('arithmetic-only unbound descriptor'); f.update();
    check(f.state().field1d60 === 8 && f.events.at(-1) === 'rebuild:1', `actual selector${selector}&15 damping`);
  }
  function terrain(f: ReturnType<typeof fixture>, indices = [255, 255, 255, 255]) {
    f.actual.controlWord = 0; f.metadata.getActorBinding(f.id).byte1d98 = 2;
    const id = f.mapping.createDescriptor([]); f.mapping.getActor(f.id).descriptor4b0 = id;
    f.movement.bindDescriptor(id, {joint0f: 255, joint22: indices[0]!, joint2a: indices[1]!, joint32: indices[2]!, joint3a: indices[3]!});
    return f.movement.getDescriptorBinding(id);
  }
  {
    const f = fixture(); f.actual.controlWord = 0; f.metadata.getActorBinding(f.id).byte1d98 = 3;
    f.metadata.getActorBinding(f.id).byte1d99 = NaN; f.movement.getActorBinding(f.id).field670 = NaN;
    f.mapping.getActor(f.id).descriptor4b0 = Symbol('never dereferenced');
    f.hooks.descriptor = () => {throw Error('unreached descriptor');};
    f.update();
    check(f.state().field1d60 === 8 && f.worldState.adjusted1d54.y === 15 && f.output(1)[7] === 35,
      'selector3 adds actual damped velocity and executes genuine corrected pass');
    check(f.matrices.getMatrix(f.storage.copy114)[7] === 20, 'root copy is not faked by adjustedY addition');
  }
  for (const bad of ['readonly', 'nan'] as const) {
    const f = fixture(); f.actual.controlWord = 0; f.metadata.getActorBinding(f.id).byte1d98 = 3;
    f.hooks.afterRebuild = mode => {if (mode === 0) {
      if (bad === 'readonly') Object.defineProperty(f.worldState.adjusted1d54, 'y', {writable: false});
      else f.worldState.adjusted1d54.y = NaN;
    }};
    rejects(f.update, bad === 'readonly' ? 'non-writable' : 'adjusted1d54.y');
    check(f.state().field1d60 === 8 && f.events.at(-1) === 'rebuild:0', 'late selector3 failure retains damping');
  }
  {
    const f = fixture(), d = terrain(f); d.joint2a = NaN; Object.freeze(d);
    Object.freeze(f.metadata.getActorBinding(f.id)); Object.freeze(f.movement.getActorBinding(f.id));
    f.update(); check(f.worldState.adjusted1d54.y === 15 && f.state().count1d96 === 0 && f.state().count1d97 === 0,
      'immediate sentinel avoids unused bytes and admits readonly operands with caller-owned cleared counts');
  }
  {
    const f = fixture(); terrain(f); f.hooks.afterRebuild = mode => {if (mode === 0) f.actual.pos.y = NaN;};
    rejects(f.update, 'position.y'); check(f.state().field1d60 === 10, 'threshold arithmetic precedes immediate sentinel');
  }
  {
    const f = fixture(); terrain(f, [254, 254, 254, 254]); f.metadata.getActorBinding(f.id).byte1d99 = 0xc0;
    f.hooks.worldMatrix = () => {throw Error('skipped matrices must not be read');}; f.update();
    check(f.worldState.adjusted1d54.y === 15, 'signed c0 skips all four, including bits8 and9');
  }
  {
    const f = fixture(); terrain(f, [254, 255, 255, 255]);
    rejects(f.update, 'addressing outside'); check(f.state().field1d60 === 10, 'negative non-sentinel is not an early exit');
  }
  for (const y of [22, 23, 24]) {
    const f = fixture(); terrain(f, [1, 255, 255, 255]); const seen: number[] = [];
    f.hooks.afterRebuild = mode => {if (mode === 0) f.output(1)[7] = y;};
    f.hooks.worldMatrix = index => {seen.push(index);};
    if (y <= 23) {rejects(f.update, 'terrain query'); check(f.state().field1d60 === 10 && f.events.at(-1) === 'rebuild:0', 'query refuses before tail');}
    else f.update();
    check(seen.join(',') === '1,1,1', 'X Y Z are all reached even above threshold');
  }
  {
    const f = fixture(), d = terrain(f, [0, 255, 255, 255]); const seen: number[] = [];
    f.hooks.worldMatrix = index => {seen.push(index); if (seen.length === 1) d.joint22 = 2;}; f.update();
    check(seen.join(',') === '0,2,2', 'cached first index supplies X; reloaded index supplies Y and Z');
  }
  {
    const f = fixture(); terrain(f, [2, 2, 2, 2]); let reads = 0;
    f.hooks.worldMatrix = () => {reads++;}; f.update(); check(reads === 12, 'four-entry bound has no fifth descriptor read');
  }
  {
    const f = fixture(); terrain(f, [1, 255, 255, 255]); let reads = 0;
    f.hooks.descriptor = () => {if (++reads === 2) f.hooks.replaceDescriptor = true;};
    rejects(f.update, 'descriptor owner changed'); check(f.state().field1d60 === 10, 'descriptor reload requires stable actual owner');
  }
  for (const method of ['worldMatrix', 'descriptor'] as const) {
    const f = fixture(); terrain(f, [2, 255, 255, 255]);
    f.hooks[method] = () => {try {f.update();} catch { /* caught reentry */ }};
    rejects(f.update, 'caught same-runtime reentry');
  }
  {
    const f = fixture(); terrain(f, [2, 255, 255, 255]);
    f.worldAdapter.getWorldMatrix = () => {throw Error('replacement not captured');};
    f.movementAdapter.getDescriptorBinding = () => {throw Error('replacement not captured');}; f.update();
    check(f.state().field1d60 === 8, 'terrain methods retain captured receivers and methods');
  }
  for (const y of [16777218, 16777220]) {
    const f = fixture(); terrain(f, [1, 255, 255, 255]);
    f.metadata.getActorBinding(f.id).byte1d99 = 1;
    f.hooks.afterRebuild = mode => {if (mode === 0) {
      f.actual.pos.y = 16777216; f.movement.getActorBinding(f.id).field670 = 1; f.output(1)[7] = y;
    }};
    f.hooks.descriptor = () => {
      f.metadata.getActorBinding(f.id).byte1d99 = 0;
      f.actual.pos.y = 20; f.movement.getActorBinding(f.id).field670 = 3;
    };
    if (y === 16777218) rejects(f.update, 'terrain query'); else f.update();
    check(f.state().field1d60 === (y === 16777218 ? 10 : 8), 'rounded initial sum then fused nibble threshold remains snapshot');
  }
  {
    const f = fixture(); terrain(f, [1, 255, 255, 255]);
    f.hooks.afterRebuild = mode => {if (mode === 0) {f.output(1)[7] = 23; f.output(1)[11] = NaN;}};
    rejects(f.update, 'world matrix.11'); check(f.state().field1d60 === 10, 'Z validation precedes reached query refusal');
  }
  {
    const f = fixture(), d = terrain(f, [2, 254, 255, 255]); let calls = 0;
    f.hooks.descriptor = () => {if (++calls === 3) f.metadata.getActorBinding(f.id).byte1d99 = 0x80;};
    f.update(); check(d.joint2a === 254 && f.state().field1d60 === 8, 'metadata reload skips later negative entry without a matrix read');
  }
  {
    const f = fixture(); terrain(f);
    f.hooks.afterRebuild = mode => {if (mode === 0) f.actual.pos = {...f.actual.pos};};
    rejects(f.update, 'actual position record changed');
    check(f.state().field1d60 === 10, 'replaced actual position refuses before threshold and tail');
  }
  {
    const f = fixture(); terrain(f, [254, 0, 255, 255]);
    f.metadata.getActorBinding(f.id).byte1d99 = 0x40;
    const seen: number[] = []; f.hooks.worldMatrix = index => {seen.push(index);};
    rejects(f.update, 'terrain query');
    check(seen.join(',') === '0,0,0' && f.state().field1d60 === 10 && f.events.at(-1) === 'rebuild:0',
      'skipped first entry continues to enabled second entry and its query without tail damping');
  }
  for (const selector of [2, 3]) {
    const f = fixture(); terrain(f); f.metadata.getActorBinding(f.id).byte1d98 = selector;
    let changed = false;
    f.hooks.world = () => {
      if (!changed && f.state().field1d60 === 8) {
        check(f.events.join(',') === 'prepare,rebuild:0', 'tail owner read follows damping store before corrected pass');
        f.state().field1d60 = 12; changed = true;
      }
    };
    f.update();
    check(changed && f.state().field1d60 === 12 && f.worldState.adjusted1d54.y === 19 && f.output(1)[7] === 39,
      `selector${selector} tail reloads stored damping after adjusted-Y owner read instead of caching product`);
  }
  const targets = ['80046f08', '80046ef4', '80047164', '80047344', '8004871c', '800487ec', '8004892c', '80048a6c',
    '80048be0', '80049f10', '8004a00c', '8004a0e0', '8004a1cc', '8004a2ec', '8004a41c', '8004a60c'];
  for (const selector of [0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) {
    const f = fixture(); f.actual.controlWord = 0; f.metadata.getActorBinding(f.id).byte1d98 = selector;
    f.globals.maskD2 = NaN; rejects(f.update, `46e7c handler ${targets[selector]}`);
    check(f.state().count1d96 === 0 && f.state().count1d97 === 0 && f.state().field1d60 === 10 && f.output(1)[7] === 27,
      `unsupported selector${selector} preserves first pass and clears, before damping/visibility`);
    check(f.events.join(',') === 'prepare,rebuild:0', 'unsupported handler never fakes second pass');
  }
  {
    const f = fixture(); f.metadata.getActorBinding(f.id).byte1d98 = NaN;
    f.hooks.metadata = () => {throw Error('suppression must not resolve metadata');}; f.update();
    check(f.state().field1d60 === 8, 'suppression and visibility skip metadata entirely');
    f.mapping.getActor(f.id).descriptor4b0 = 3 as unknown as symbol;
    rejects(f.update, 'descriptor4b0'); check(f.state().field1d60 === 8, 'suppression still loads descriptor before damping');
  }
  {
    const f = fixture(); f.actual.controlWord = 0; f.metadata.getActorBinding(f.id).byte1d98 = NaN;
    f.hooks.mapping = () => {throw Error('descriptor must follow metadata');};
    rejects(f.update, 'byte1d98'); check(f.state().count1d97 === 0, 'metadata failure follows both stores and precedes descriptor');
    f.metadata.getActorBinding(f.id).byte1d98 = 0; f.hooks.mapping = () => {throw Error('required descriptor argument read');};
    rejects(f.update, 'required descriptor argument read');
  }
  {
    const f = fixture(); f.worldState.mode4a0 = 2; f.worldState.flags48a = NaN;
    f.hooks.actual = f.hooks.movement = f.hooks.metadata = f.hooks.mapping = () => {throw Error('unreached owner');};
    f.globals.maskD2 = NaN; f.state().field1d60 = NaN; f.update();
    check(f.events.length === 0 && f.output(0)[7] === -20 && f.state().count1d96 === 7, 'mode2 reads only actual world mode');
  }
  for (const value of [-0, 2 ** -149, -(2 ** -149), (2 - 2 ** -23) * 2 ** 127]) {
    const f = fixture(); f.state().field1d60 = value; f.update();
    check(Object.is(f.state().field1d60, Math.fround(value * 0.800000011920929)), 'finite damping signed-zero/subnormal/max-f32 rounding');
  }
  for (const value of [NaN, Infinity, 0.1]) {
    const f = fixture(); f.state().field1d60 = value; rejects(f.update, 'field1d60');
    check(f.state().count1d97 === 0 && f.events.join(',') === 'prepare,rebuild:0', 'invalid damping operand preserves cleared prefix');
  }
  {
    const f = fixture(); Object.defineProperty(f.state(), 'count1d96', {writable: false});
    f.actual.controlWord = NaN; rejects(f.update, 'count1d96: non-writable');
    check(f.state().count1d96 === 7 && f.state().count1d97 === 8 && f.output(1)[7] === 27,
      'first count destination failure skips second count and control after first pass');
  }
  {
    const f = fixture(); Object.defineProperty(f.state(), 'count1d97', {writable: false});
    f.actual.controlWord = NaN; rejects(f.update, 'count1d97: non-writable');
    check(f.state().count1d96 === 0 && f.state().count1d97 === 8 && f.output(1)[7] === 27, 'count97 destination refusal retains count96 and first pass');
  }
  {
    const f = fixture(); Object.defineProperty(f.state(), 'field1d60', {writable: false}); rejects(f.update, 'field1d60: non-writable');
    check(f.state().field1d60 === 10 && f.state().count1d97 === 0, 'readonly damping destination refuses after both clears');
  }
  {
    const f = fixture(); f.state().count1d96 = NaN; f.state().count1d97 = NaN;
    Object.defineProperty(f.actual, 'controlWord', {writable: false}); Object.freeze(f.globals);
    Object.freeze(f.mapping.getActor(f.id)); Object.freeze(f.movement.getActorBinding(f.id)); f.update();
    check(f.state().count1d96 === 0 && f.state().count1d97 === 0, 'stores overwrite stale non-byte values; readonly operands allowed');
  }
  {
    const f = fixture(); f.hooks.prepare = () => {f.pose(1).translation.y = 99;}; f.update();
    check(f.worldState.adjusted1d54.y === 7 && f.output(1)[7] === 27 && f.pose(1).translation.y === 99,
      'second pass does not reprepare or pick up later joint1 translation');
    f.update(); check(f.worldState.adjusted1d54.y === 104 && f.output(1)[7] === 124, 'later explicit update prepares again');
  }
  {
    const f = fixture(); f.hooks.afterRebuild = mode => {if (mode === 0) f.worldState.mode4a0 = 2;}; f.update();
    check(f.events.join(',') === 'prepare,rebuild:0,rebuild:1' && f.state().field1d60 === 8,
      'post-first-pass mode2 does not incorrectly gate ungated second pass');
  }
  {
    const f = fixture(); f.hooks.beforeRebuild = mode => {if (mode === 1) {f.state().count1d96 = 1; f.actual.pos.y = 50;}};
    rejects(f.update, 'positive count1d96');
    check(f.output(0)[7] === 50 && f.output(1)[7] === 27 && f.state().field1d60 === 8,
      'corrected traversal consumes same controller record after second root and damping, not copied zeros');
  }
  {
    const f = fixture(); f.globals.maskD2 = 0; f.actual.flyer741 = 255;
    f.state().byte660 = NaN; f.metadata.getActorBinding(f.id).byte1d98 = NaN; f.update();
    check(f.state().field1d60 === 8, 'flyer guard skips later byte and metadata');
    f.actual.flyer741 = 0; f.state().byte660 = 128; f.update();
    check(f.state().field1d60 === Math.fround(8 * 0.800000011920929), 'byte660 guard skips metadata');
    f.state().byte660 = 0; f.metadata.getActorBinding(f.id).byte1d98 = 0x10; f.update();
    check(f.events.filter(event => event === 'rebuild:1').length === 3, 'metadata high-nibble guard admits real third update');
  }
  {
    const f = fixture(); f.globals.maskD2 = 0; f.metadata.getActorBinding(f.id).byte1d98 = 0x20;
    Object.defineProperty(f.actual, 'lifecycle18', {get: unexpectedLifecycle});
    rejects(f.update, '47904 active body');
    check(f.state().field1d60 === 8 && f.output(2)[7] === 31, 'active47904 refuses after completed corrected pass, before lifecycle read');
    function unexpectedLifecycle(): never {throw Error('must not inspect lifecycle18');}
  }
  {
    const f = fixture(); Reflect.deleteProperty(f.actual, 'flyer741'); f.state().byte660 = 1;
    f.update(); check(f.state().field1d60 === 8, 'visibility skip does not invent or require absent flyer741');
    f.globals.maskD2 = 0; rejects(f.update, 'flyer741: own data');
    check(f.state().field1d60 === Math.fround(8 * 0.800000011920929), 'reached missing flyer refuses only after second pass');
  }
  {
    const f = fixture(); f.actual.visibilityBit = NaN;
    Object.defineProperty(f.globals, 'maskD2', {get() {throw Error('visibility must precede global mask');}});
    rejects(f.update, 'visibilityBit'); check(f.state().field1d60 === 8, 'visibility refusal before mask after completed matrix work');
  }
  {
    const f = fixture(); f.sources.globals = {maskD2: 0}; f.actual.flyer741 = NaN; f.update();
    check(f.state().field1d60 === 8, 'actual global record fixed at construction, not replaced source-table slot');
    f.globals.maskD2 = 0; rejects(f.update, 'flyer741');
  }
  {
    const f = fixture(), target = f.addActor(); f.state().link4a4 = target.id; f.worldState.mode4a0 = 1;
    target.worldState.mode4a0 = NaN; target.actual.pos.y = NaN; f.mapping.getActor(target.id).jointCount1d90 = NaN;
    f.update();
    check(f.events.join(',') === 'prepare,rebuild:0,rebuild:1,copy' && target.output(2).every((value, i) => Object.is(value, f.output(2)[i])),
      'final47a2c copies real source into target without reading target mode/count/pose or rebuilding');
    check(f.matrices.getMatrix(target.storage.copy114)[7] === 91 && target.worldState.adjusted1d54.y === 82,
      'copy touches world slots only, not target lifted/cached matrices or preparation');
  }
  for (const count of [0, 128, 255]) {
    const f = fixture(); f.worldState.mode4a0 = 1; f.mapping.getActor(f.id).jointCount1d90 = count; f.state().link4a4 = null;
    f.update(); check(f.events.at(-1) === 'copy', 'nonpositive signed source count allows null target without eager resolution');
  }
  {
    const f = fixture(); f.worldState.mode4a0 = 1; f.state().link4a4 = Symbol('unbound target');
    rejects(f.update, 'unknown/non-owned world-matrix actor');
    check(f.state().field1d60 === 8 && f.output(2)[7] === 31 && f.events.at(-1) === 'copy', 'target refusal is late after normal work');
  }
  {
    const f = fixture(), target = f.addActor(); f.worldState.mode4a0 = 1; f.state().link4a4 = target.id;
    Object.defineProperty(target.output(1), '4', {writable: false}); rejects(f.update, 'non-writable');
    check(target.output(0)[7] === 20 && target.output(1)[3] === 15 && target.output(1)[7] === -21 && target.output(2)[7] === -22,
      'actual copy preserves complete first matrix and scalar prefix of failing second destination');
  }
  {
    const f = fixture(), target = f.addActor(); f.state().link4a4 = target.id;
    f.hooks.afterRebuild = mode => {if (mode === 1) f.worldState.mode4a0 = 1;};
    f.hooks.matrixCopy = (_from, to) => {if (to === target.slots[0]) f.mapping.getActor(f.id).jointCount1d90 = 1;};
    f.update(); check(target.output(0)[7] === 20 && target.output(1)[7] === -21, 'final mode is reloaded, and copy source count is reloaded after each copy');
  }
  for (const stage of ['world', 'actual', 'movement', 'metadata', 'mapping'] as const) {
    const f = fixture(); f.actual.controlWord = 0; f.metadata.getActorBinding(f.id).byte1d98 = 1;
    if (stage === 'world') f.hooks.replaceWorld = true;
    else if (stage === 'actual') f.hooks.replaceActual = true;
    else if (stage === 'movement') f.hooks.replaceMovement = true;
    else if (stage === 'metadata') f.hooks.replaceMetadata = true;
    else f.hooks.replaceMapping = true;
    rejects(f.update, 'owner changed its actual record');
    check(f.events.length === (stage === 'world' ? 0 : 2), 'changed owner detected at reached load, preserving completed first pass');
  }
  {
    const f = fixture(); f.worldAdapter.prepareActor = f.worldAdapter.rebuildActor = unexpectedReplacement;
    f.worldAdapter.getActualActor = unexpectedReplacement; f.worldAdapter.getActorBinding = unexpectedReplacement;
    f.movementAdapter.getActorBinding = f.metadataAdapter.getActorBinding = f.mappingAdapter.getActor = unexpectedReplacement;
    f.update(); check(f.output(2)[7] === 31 && f.state().field1d60 === 8, 'captured methods and original receivers survive adapter replacement');
    function unexpectedReplacement(): never {throw Error('replacement method must not execute');}
  }
  for (const stage of ['prepare', 'movement', 'metadata'] as const) {
    const f = fixture(); f.actual.controlWord = 0; f.metadata.getActorBinding(f.id).byte1d98 = 1;
    f.hooks[stage] = () => {try {f.update();} catch { /* faulty adapter catches nested entry */ }};
    rejects(f.update, 'caught same-runtime reentry');
    check(f.worldState.adjusted1d54.y === 7 && f.state().field1d60 === 10, 'caught reentry preserves completed prep/first pass only');
    delete f.hooks[stage]; f.update(); check(f.state().field1d60 === 8, 'runtime reusable after bounded caught-reentry refusal');
  }
  {
    const f = fixture(); f.hooks.afterRebuild = mode => mode === 0 ? Promise.resolve() : undefined;
    rejects(f.update, 'synchronously');
    check(f.output(2)[7] === 31 && f.state().count1d96 === 7, 'async/nonvoid real-effect wrapper fails after actual first pass');
  }
  {
    const f = fixture(true); f.initial.count1d96 = 256; rejects(f.bind, 'count1d96'); f.initial.count1d96 = 7;
    Object.defineProperty(f.initial, 'field1d60', {get() {throw Error('must not execute user getter');}});
    rejects(f.bind, 'own data'); rejects(() => f.runtime.getActorBinding(f.id), 'unknown/non-owned');
  }
  {
    const f = fixture(); check(Object.isSealed(f.state()) && f.state() === f.runtime.getActorBinding(f.id), 'stable controller-owned fields');
    f.initial.field1d60 = 99; f.initial.count1d96 = 0; check(f.state().field1d60 === 10 && f.state().count1d96 === 7, 'only missing fields copied at bind');
    rejects(f.bind, 'already bound');
    rejects(() => createSourceActorMatrixUpdateRuntime({...f.sources, globals: undefined as never}), 'actual battle globals');
  }
}
