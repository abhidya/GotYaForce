import {createSourceAnimationSetupMetadataRuntime, type SourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceAttachedJointSetupRuntime} from './attached-joint-setup.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[setup-metadata-test] ${message}`);}
function rejects(run: () => unknown, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);} check(error.includes(expected), `expected ${expected}, got ${error || 'success'}`);
}
function fixture(initial = Array.from({length: 33}, (_, i) => i), bank = 0) {
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const unsupported = (): never => {throw Error('metadata must not animate, request, scan or convert');};
  const effects = {interpretAObj: unsupported, animateRObjs: unsupported, animateDObjs: unsupported};
  const actors = createSourceActorJointMappingRuntime(joints, feedback, effects, {convertEulerToQuaternion: unsupported});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => actors.createPart(
    {frame0c: 2, duration24: -7, segment2d: 7, complete2e: 1, mode2f: 0, mirror30: 0xaa},
    {descriptor00: null, scaleIndex32: 255, jointBank33: bank, poseBuffer35: 0})));
  const descriptor = actors.createDescriptor([]);
  const actor = actors.createActor({descriptor4b0: descriptor, jointCount1d90: 0, boundary1d91: 0, boundary1d92: 0,
    boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 3}, {parts, poses: [[], []]});
  const partId = parts[0]![0]!, actual = feedback.getPart(partId), mapping = actors.getPartBinding(partId);
  const attached = createSourceAttachedJointSetupRuntime({joints, feedback, actors,
    requests: {requestJoint: unsupported}, fobjs: {getFObj: unsupported}}, effects);
  attached.bindPart(partId, {rewind26: -12, loop2c: 8});
  const descriptors = createSourceAnimationDescriptorBankRuntime(), input = Uint8Array.from(initial), cursor = descriptors.createBytes(input);
  const reads: number[] = [], hooks: {read?: (offset: number) => void; descriptor?: () => void} = {};
  const descriptorAdapter = {readByte(id: symbol, offset = 0): number {
    check(this === descriptorAdapter, 'captured byte adapter receiver'); reads.push(offset);
    const value = descriptors.readByte(id, offset); hooks.read?.(offset); return value;
  }};
  const actorAdapter = {...actors, getDescriptor(id: symbol) {
    check(this === actorAdapter, 'captured descriptor adapter receiver'); hooks.descriptor?.(); return actors.getDescriptor(id);
  }};
  const runtime = createSourceAnimationSetupMetadataRuntime({descriptors: descriptorAdapter, actors: actorAdapter, feedback, attached});
  const actorInput = {byte1d74: 41, byte1d75: 42, byte1d76: 43, byte1d77: 44, byte1d94: 45, byte1d95: 46,
    byte1d98: 47, byte1d99: 48, byte1d9b: 49};
  runtime.bindActor(actor, Object.freeze({...actorInput}));
  runtime.bindPart(partId, Object.freeze({selector2a: 51, selector2b: 52, auxiliary37: 53}));
  runtime.bindDescriptorDefaults(descriptor, Object.freeze({bytebe: 61, bytebf: 62}));
  const run = (channel = 0) => runtime.applyMetadata(actor, partId, channel, cursor);
  return {runtime, actors, feedback, actor, actorInput, partId, actual, mapping, attached, descriptors, descriptor, descriptorAdapter,
    actorAdapter, input, cursor, reads, hooks, run, side: runtime.getPartBinding(partId), bytes: runtime.getActorBinding(actor), setup: attached.getPartBinding(partId)};
}
export function runAnimationSetupMetadataSelfTests(): void {
  for (let channel = 0; channel < 4; channel++) for (let flags = 0; flags < 8; flags++) {
    const bytes = Array.from({length: 33}, (_, i) => i), base = 4 + channel * 8;
    bytes[base + 2] = flags; bytes[base + 3] = 255;
    const x = fixture(bytes); x.run(channel);
    check(x.mapping.scaleIndex32 === 0 && x.side.selector2a === base && x.side.selector2b === base + 1 &&
      x.setup.rewind26 === 255 && x.side.auxiliary37 === base + 4, 'real shared stores and zero-extended rewind');
    check(x.actual.mirror30 === [0xaa, 0, 1, 0xab][flags & 3] && x.setup.loop2c === (flags >> 2), 'mirror/loop operations');
    check(x.actual.frame0c === 2 && x.actual.duration24 === -7 && x.actual.complete2e === 1 && x.mapping.poseBuffer35 === 0,
      'unrelated shared state is unchanged');
    const prefix = [0, base, base + 1, base + 3, base + 4, base + 2, base + 2];
    const tail = channel === 0 ? [9, 10] : channel === 1 ? [17, 18, 19] : [];
    check(x.reads.join() === [...prefix, ...tail].join(), 'instruction-backed operand read sequence, no metadata9/10 reread');
    if (channel === 0) check(x.bytes.byte1d74 === 9 && x.bytes.byte1d75 === 10 && x.bytes.byte1d94 === 9 && x.bytes.byte1d95 === 10, 'bank0 stores and copies');
    if (channel === 1) check(x.bytes.byte1d98 === 17 && x.bytes.byte1d99 === 18 && x.bytes.byte1d9b === 19, 'channel1 actor bytes');
  }
  for (const bank of [0, 1]) {
    const data = new Array<number>(33).fill(0); data[9] = 128; data[10] = 255;
    const x = fixture(data, bank), replacement = x.actors.createDescriptor([]);
    x.runtime.bindDescriptorDefaults(replacement, {bytebe: 71, bytebf: 72});
    x.hooks.descriptor = () => {x.actors.getActor(x.actor).descriptor4b0 = replacement; x.mapping.jointBank33 = 1;};
    x.run();
    check(x.bytes[bank === 0 ? 'byte1d74' : 'byte1d76'] === 61 && x.bytes.byte1d77 === 72,
      'fallback snapshots bank before descriptor resolution, reloads actual descriptor and bank for second store');
    check(x.bytes.byte1d94 === 45 && x.bytes.byte1d95 === 46, 'final bank reload skips copies');
  }
  {
    const x = fixture(); x.actors.getActor(x.actor).descriptor4b0 = null;
    Object.defineProperty(x.mapping, 'jointBank33', {writable: false}); x.run();
    check(x.bytes.byte1d74 === 9, 'nonnegative metadata never consumes descriptor; readonly bank operand');
  }
  for (const channel of [-0x80000000, -1, 4, 0x7fffffff]) {
    const x = fixture([88]); x.runtime.applyMetadata(Symbol('unused actor'), x.partId, channel, x.cursor);
    check(x.mapping.scaleIndex32 === 88 && x.reads.join() === '0' && x.side.selector2a === 51, 'out-of-range source channels only store scale');
  }
  for (const channel of [NaN, Infinity, 0.5, -0x80000001, 0x80000000]) {
    const x = fixture(); rejects(() => x.run(channel), 'channel'); check(x.mapping.scaleIndex32 === 255, 'channel admission precedes work');
  }
  for (const bank of [2, 127, 128, 255]) {
    const x = fixture(undefined, bank); rejects(x.run, 'two-bank host bound');
    check(x.side.auxiliary37 === 8 && x.setup.loop2c === 1 && x.bytes.byte1d74 === 41, 'bad signed bank retains part prefix');
  }
  {
    const x = fixture(); x.input.fill(255); x.actorInput.byte1d74 = 0;
    x.descriptorAdapter.readByte = () => {throw Error('replacement must not run');}; x.run();
    check(x.bytes.byte1d74 === 9 && x.side.selector2a === 4, 'copied inputs and captured methods');
    rejects(() => x.runtime.bindPart(x.partId, x.side), 'already bound');
    rejects(() => x.runtime.bindActor(x.actor, x.bytes), 'already bound');
    rejects(() => x.runtime.bindDescriptorDefaults(x.descriptor, {bytebe: 0, bytebf: 0}), 'already bound');
    rejects(() => x.runtime.bindDescriptorDefaults(Symbol(), {bytebe: 0, bytebf: 0}), 'unknown/non-owned descriptor');
  }
  {
    const data = new Array<number>(33).fill(0), x = fixture(data);
    x.actual.mirror30 = NaN; Object.defineProperty(x.actual, 'mirror30', {writable: false});
    x.run(); check(Number.isNaN(x.actual.mirror30), 'flags0 never reads or writes mirror');
    x.mapping.scaleIndex32 = NaN; x.side.selector2a = NaN; x.setup.rewind26 = NaN;
    x.run(); check(x.mapping.scaleIndex32 === 0 && x.side.selector2a === 0 && x.setup.rewind26 === 0, 'stores do not validate overwritten bits');
  }
  for (const [target, field, expectedReads] of [
    ['mapping', 'scaleIndex32', '0'], ['side', 'selector2a', '0,4'], ['side', 'selector2b', '0,4,5'],
    ['setup', 'rewind26', '0,4,5,7'], ['side', 'auxiliary37', '0,4,5,7,8'], ['setup', 'loop2c', '0,4,5,7,8,6,6'],
    ['bytes', 'byte1d74', '0,4,5,7,8,6,6,9'], ['bytes', 'byte1d75', '0,4,5,7,8,6,6,9,10'],
    ['bytes', 'byte1d94', '0,4,5,7,8,6,6,9,10'], ['bytes', 'byte1d95', '0,4,5,7,8,6,6,9,10'],
  ] as const) {
    const x = fixture(); Object.defineProperty(x[target], field, {writable: false}); rejects(x.run, 'non-writable');
    check(x.reads.join() === expectedReads, `store failure ${field} preserves exact read prefix`);
    if (field === 'byte1d75') check(x.bytes.byte1d74 === 9 && x.bytes.byte1d94 === 45, 'second actor store failure preserves first without copies');
    if (field === 'byte1d95') check(x.bytes.byte1d94 === 9, 'second copy failure preserves first copy');
  }
  for (const length of [0, 4, 5, 7, 8, 9, 10]) {
    const x = fixture(Array.from({length}, (_, i) => i)); rejects(x.run, 'out of bounds');
    if (length > 0) check(x.mapping.scaleIndex32 === 0, 'short metadata preserves common scale write');
  }
  {
    const data = new Array<number>(33).fill(0); data[9] = 255; const x = fixture(data);
    x.actors.getActor(x.actor).descriptor4b0 = null; rejects(x.run, 'non-null owned descriptor4b0');
    check(x.side.auxiliary37 === 0 && x.bytes.byte1d74 === 41, 'fallback refuses lazily after common part stores');
  }
  {
    const x = fixture(); let reentered = false;
    x.hooks.read = () => {if (!reentered) {reentered = true; rejects(() => x.run(3), 'reentry');}};
    rejects(x.run, 'reentry was caught'); check(x.mapping.scaleIndex32 === 255, 'caught read adapter reentry poisons before store');
    delete x.hooks.read; x.run(); check(x.mapping.scaleIndex32 === 0, 'runtime releases guard after refusal');
  }
  {
    const x = fixture(); let calls = 0;
    x.hooks.read = offset => {if (offset === 6 && ++calls === 1) x.actual.mirror30 = 255;};
    x.run(); check(x.actual.mirror30 === 1 && calls === 2, 'flags reread after mirror store');
  }
  for (const channel of [2, 3]) {
    const x = fixture(); x.mapping.jointBank33 = NaN;
    x.runtime.applyMetadata(Symbol('unused actor'), x.partId, channel, x.cursor);
    check(x.side.selector2a === 4 + channel * 8, 'channels2/3 never consume actor or joint bank');
  }
  {
    const data = new Array<number>(33).fill(0); data[9] = 255; data[10] = 12;
    const x = fixture(data), defaults = x.runtime.getDescriptorDefaults(x.descriptor);
    defaults.bytebf = NaN; Object.defineProperty(defaults, 'bytebe', {writable: false});
    Object.defineProperty(x.actors.getActor(x.actor), 'descriptor4b0', {writable: false});
    x.run(); check(x.bytes.byte1d74 === 61 && x.bytes.byte1d75 === 12,
      'readonly descriptor and fallback byte are operands, unused fallback byte remains lazy');
  }
  {
    const data = new Array<number>(33).fill(0); data[10] = 255;
    const x = fixture(data); x.runtime.getDescriptorDefaults(x.descriptor).bytebf = NaN;
    rejects(x.run, 'bytebf');
    check(x.bytes.byte1d74 === 0 && x.bytes.byte1d75 === 42 && x.bytes.byte1d94 === 45,
      'second fallback failure preserves first actor store but not copies');
  }
  for (const flags of [1, 2, 3]) {
    const data = new Array<number>(33).fill(0); data[6] = flags;
    const x = fixture(data); Object.defineProperty(x.actual, 'mirror30', {writable: false});
    rejects(x.run, 'non-writable');
    check(x.reads.join() === '0,4,5,7,8,6' && x.setup.loop2c === 8, 'mirror store failure occurs before flags reread/loop store');
  }
  for (const field of ['byte1d98', 'byte1d99', 'byte1d9b'] as const) {
    const x = fixture(); Object.defineProperty(x.bytes, field, {writable: false});
    rejects(() => x.run(1), 'non-writable');
    if (field !== 'byte1d98') check(x.bytes.byte1d98 === 17, 'channel1 prefix retained');
    if (field === 'byte1d9b') check(x.bytes.byte1d99 === 18, 'channel1 second store retained');
  }
  {
    const x = fixture();
    x.hooks.read = offset => {if (offset === 10) x.mapping.jointBank33 = 1;};
    x.run(); check(x.bytes.byte1d74 === 9 && x.bytes.byte1d77 === 10 && x.bytes.byte1d94 === 45,
      'each nonnegative assignment and final copy decision reread actual joint bank');
  }
  {
    const x = fixture(); x.hooks.read = offset => {if (offset === 0) throw Error('injected read failure');};
    rejects(x.run, 'injected read failure'); check(x.mapping.scaleIndex32 === 255, 'throwing byte reader writes nothing');
  }
  // A resolver returning deferred work is rejected, never treated as bytes.
  {
    const x = fixture(), real = x.descriptors.readByte;
    const sources = {descriptors: {readByte: ((id: symbol, offset: number) => Promise.resolve(real(id, offset))) as unknown as typeof real},
      actors: x.actors, feedback: x.feedback, attached: x.attached};
    const runtime: SourceAnimationSetupMetadataRuntime = createSourceAnimationSetupMetadataRuntime(sources);
    runtime.bindPart(x.partId, x.side);
    rejects(() => runtime.applyMetadata(x.actor, x.partId, 4, x.cursor), 'synchronously');
    check(x.mapping.scaleIndex32 === 255, 'async byte cannot write scale');
  }
}
