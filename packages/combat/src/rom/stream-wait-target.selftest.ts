import {createSourceStreamWaitTargetRuntime, type SourceStreamWaitTargetPart} from './stream-wait-target.js';
import {createSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
function check(value: boolean, message: string): void {if (!value) throw Error(`[stream-wait-target-test] ${message}`);}
function rejects(run: () => unknown, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
function fixture(synthetic = false, count = 0) {
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const mapping = createSourceActorJointMappingRuntime(joints, feedback, {
    interpretAObj() {throw Error('unexpected AObj');}, animateRObjs() {throw Error('unexpected RObj');},
    animateDObjs() {throw Error('unexpected DObj');},
  }, {convertEulerToQuaternion() {throw Error('unexpected conversion');}});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 4, duration24: 9, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 255, jointBank33: 0, poseBuffer35: 1})));
  const actor = mapping.createActor({descriptor4b0: mapping.createDescriptor([0]), jointCount1d90: count,
    boundary1d91: count, boundary1d92: count, boundary1d93: count,
    jointBank1db4: null, jointBank1db8: null, timestep1dc8: 0.5}, {parts, poses: [[], []]});
  const dispatch = createSourceActorAnimationDispatchRuntime(mapping, feedback);
  dispatch.bindActor(actor, {family1d88: Symbol('presence'), shared1d8c: Symbol('presence'), marker578: 0, marker1db3: 0});
  for (const id of parts.flat()) dispatch.bindPart(id, {elapsed08: 2, previous10: 10, previous14: 11, linked36: 0});
  const hooks: {actor?: () => void; update?: () => void; layout?: () => void; part?: () => void} = {};
  let calls = 0;
  // Explicit synthetic fault wrappers, only used by fixture(true). They forward
  // real owned runtime calls and inject boundary failures, never pretend playback.
  const mappingAdapter = {...mapping,
    getActor(id: symbol) {check(this === mappingAdapter, 'actor this'); hooks.actor?.(); return mapping.getActor(id);},
    getLayout(id: symbol) {check(this === mappingAdapter, 'layout this'); hooks.layout?.(); return mapping.getLayout(id);},
  };
  const feedbackAdapter = {...feedback, getPart(id: symbol) {
    check(this === feedbackAdapter, 'part this'); hooks.part?.(); return feedback.getPart(id);
  }};
  const dispatchAdapter = {...dispatch, updatePart(id: symbol, index: number) {
    check(this === dispatchAdapter, 'update this'); check(id === actor, 'exact actor'); calls++;
    const result = dispatch.updatePart(id, index); hooks.update?.(); return result;
  }};
  const runtime = createSourceStreamWaitTargetRuntime(synthetic ? mappingAdapter : mapping,
    synthetic ? feedbackAdapter : feedback, synthetic ? dispatchAdapter : dispatch);
  const input: SourceStreamWaitTargetPart[] = Array.from({length: 4}, (_, i) => ({target08: 10 + i, previous0c: 99, accumulator10: 2}));
  runtime.bindActor(actor, input);
  const stream = runtime.getStreamPart(actor, 0), id = parts[0]![0]!, part = feedback.getPart(id);
  return {runtime, mapping, feedback, dispatch, actor, parts, stream, part, input, hooks,
    mappingAdapter, feedbackAdapter, dispatchAdapter, calls: () => calls,
    gates: dispatch.getActorBinding(actor), header: mapping.getActor(actor), binding: dispatch.getPartBinding(id),
    run: (index = 0) => runtime.continueUnmetNonCountdownWait(actor, index)};
}
export function runStreamWaitTargetSelfTest(): void {
  {
    const x = fixture(); x.input[0]!.target08 = 999; x.input[0]!.accumulator10 = 999;
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.stream), 'owned sealed copied binding');
    check(x.run() === undefined && x.stream.previous0c === 10 && x.stream.target08 === 6.5 &&
      x.stream.accumulator10 === 2 && x.part.frame0c === 4.5 && x.binding.elapsed08 === 2.5,
    'real dispatch advances shared frame before target and copies source target');
    check(x.runtime.getStreamPart(x.actor, 0) === x.stream, 'stable owned stream record');
    for (const completion of [1, 127, 128, 255]) {
      const previous = x.stream.target08; x.part.complete2e = completion; x.run();
      check(x.stream.previous0c === previous && x.stream.target08 === 2 + x.part.frame0c, 'signed completion is ignored');
    }
    rejects(() => x.runtime.bindActor(x.actor, x.input), 'already bound');
    rejects(() => x.runtime.bindActor(Symbol('foreign'), x.input), 'unknown/non-owned');
    rejects(() => x.runtime.getStreamPart(Symbol('foreign'), 0), 'unknown/non-owned');
    rejects(() => x.runtime.continueUnmetNonCountdownWait(Symbol('foreign'), 0), 'unknown/non-owned');
  }
  for (const index of [0, 1, 2, 3]) {
    const x = fixture(), selected = x.runtime.getStreamPart(x.actor, index), id = x.parts[0]![index]!;
    x.run(index);
    check(selected.previous0c === 10 + index && selected.target08 === 6.5 && x.feedback.getPart(id).frame0c === 4.5,
      'four host parts select bank0 and corresponding stream');
    check(x.feedback.getPart(x.parts[1]![index]!).frame0c === 4, 'other bank remains unchanged');
    if (index !== 0) check(x.stream.previous0c === 99 && x.part.frame0c === 4, 'unselected stream/part remain unchanged');
  }
  {
    const x = fixture(false, 1); x.run();
    check(x.part.complete2e === 1 && x.stream.target08 === 6.5 &&
      x.mapping.getPartBinding(x.parts[0]![0]!).poseBuffer35 === 0, 'actual mapping completion does not skip target');
  }
  for (const gate of ['family', 'shared', 'freeze'] as const) {
    const x = fixture(); let index = 0;
    if (gate === 'family') x.gates.family1d88 = null;
    else if (gate === 'shared') x.gates.shared1d8c = null;
    else {index = 1; x.gates.marker578 = 1; x.gates.marker1db3 = 1;}
    const stream = x.runtime.getStreamPart(x.actor, index), part = x.feedback.getPart(x.parts[0]![index]!);
    x.run(index); check(part.frame0c === 4 && stream.target08 === 6 && stream.previous0c === 10 + index,
      'readiness/freeze skips playback but not stream target');
  }
  for (const segment of [1, 128, 255]) for (const duration of [-32768, -1, 0, 1, 32767]) {
    const x = fixture(); x.part.segment2d = segment; x.part.duration24 = duration; x.run();
    check(x.stream.previous0c === 10 && x.stream.accumulator10 === 2 + duration &&
      x.stream.target08 === 6.5 + duration && x.part.frame0c === 4.5 && x.binding.elapsed08 === 2.5,
    'every nonzero byte sign uses signed duration after real dispatch');
  }
  {
    const x = fixture(); x.part.duration24 = NaN; x.run();
    check(x.stream.target08 === 6.5, 'zero segment never consumes duration');
  }
  for (const duration of [NaN, Infinity, -Infinity, -32769, 32768, 0.5, undefined, null, '1', {}]) {
    const x = fixture(); x.part.segment2d = 1; x.part.duration24 = duration as number;
    x.stream.accumulator10 = NaN; x.part.frame0c = NaN; x.gates.family1d88 = null;
    rejects(x.run, 'duration24: signed integer out of range');
    check(x.stream.previous0c === 10 && x.stream.target08 === 10 && Number.isNaN(x.stream.accumulator10),
      'malformed duration precedes invalid accumulator/frame by host admission order, not proven source instruction order');
  }
  {
    const x = fixture(); x.part.segment2d = 1; x.part.duration24 = 1; x.stream.accumulator10 = NaN;
    rejects(x.run, 'accumulator10: expected finite');
    check(x.stream.previous0c === 10 && x.part.frame0c === 4.5 && x.stream.target08 === 10,
      'valid duration then malformed accumulator preserves copy and dispatch');
  }
  {
    const x = fixture(); x.part.segment2d = 1;
    Object.defineProperty(x.part, 'duration24', {writable: false}); x.run();
    check(x.stream.accumulator10 === 11 && x.stream.target08 === 15.5, 'readonly signed duration is readable');
  }
  for (const duration of [0, 1]) {
    const x = fixture(); x.part.segment2d = 1; x.part.duration24 = duration;
    Object.defineProperty(x.stream, 'accumulator10', {writable: false});
    rejects(x.run, 'accumulator10: non-writable');
    check(x.stream.previous0c === 10 && x.stream.accumulator10 === 2 && x.stream.target08 === 10 && x.part.frame0c === 4.5,
      'wrapped accumulator store requires writable field even with duration zero');
  }
  for (const invalid of ['duration', 'accumulator'] as const) {
    const x = fixture(); x.part.segment2d = 1; x.part.duration24 = invalid === 'duration' ? NaN : 0;
    x.stream.accumulator10 = NaN; Object.defineProperty(x.stream, 'accumulator10', {writable: false});
    rejects(x.run, invalid === 'duration' ? 'duration24: signed integer' : 'accumulator10: expected finite');
    check(x.stream.previous0c === 10 && x.stream.target08 === 10 && x.part.frame0c === 4.5,
      'operand admission precedes writability check at the reached accumulator store');
  }
  for (const fault of ['frame', 'target'] as const) {
    const x = fixture(true); x.part.segment2d = 1;
    if (fault === 'frame') x.hooks.update = () => {x.part.frame0c = NaN;};
    else Object.defineProperty(x.stream, 'target08', {writable: false});
    rejects(x.run, fault === 'frame' ? 'frame0c' : 'target08: non-writable');
    check(x.stream.accumulator10 === 11 && x.stream.previous0c === 10 && x.stream.target08 === 10 && x.binding.elapsed08 === 2.5,
      'later invalid frame/readonly target retains successful wrapped accumulator store');
  }
  for (const [accumulator, duration, frame, expectedAccumulator, expectedTarget] of [
    [16777216, 1, 1, 16777216, 16777216],
    [-0, 0, -0, 0, 0], [-0, -0, -0, 0, 0],
    [-1, 1, -0, 0, 0], [2 ** -149, 0, 2 ** -149, 2 ** -149, 2 ** -148],
    [-(2 ** -149), 0, -0, -(2 ** -149), -(2 ** -149)],
  ]) {
    const x = fixture(); x.gates.family1d88 = null; x.stream.target08 = -0;
    x.part.segment2d = 128; x.part.duration24 = duration!; x.stream.accumulator10 = accumulator!;
    x.part.frame0c = frame!; x.run();
    check(Object.is(x.stream.previous0c, -0) && Object.is(x.stream.accumulator10, expectedAccumulator) &&
      Object.is(x.stream.target08, expectedTarget), 'separate RN00 stores, source integer zero and NI0 subnormals');
  }
  {
    const x = fixture(); x.gates.family1d88 = null; x.part.segment2d = 255; x.part.duration24 = 32767;
    x.stream.accumulator10 = Math.fround(3.4028234663852886e38); x.part.frame0c = x.stream.accumulator10;
    rejects(x.run, 'target08 result');
    check(x.stream.previous0c === 10 && x.stream.target08 === 10 && x.stream.accumulator10 === x.part.frame0c,
      'target overflow retains reached finite wrapped accumulator');
  }
  {
    const x = fixture(true); x.hooks.update = () => {x.stream.accumulator10 = 20; x.part.frame0c = 8;};
    x.run(); check(x.stream.target08 === 28, 'accumulator and frame read live after dispatch');
  }
  for (const stage of ['update', 'layout', 'part'] as const) {
    const x = fixture(true); x.hooks[stage] = () => {
      x.part.segment2d = 255; x.part.duration24 = -7; x.stream.accumulator10 = 20; x.part.frame0c = 8;
    };
    x.run(); check(x.stream.accumulator10 === 13 && x.stream.target08 === 21 && x.binding.elapsed08 === 2.5,
      'segment, signed duration, accumulator and frame read live after explicit synthetic boundary mutation');
  }
  for (const index of [-1, 4, 0.5, NaN]) {
    const x = fixture(); rejects(() => x.run(index), 'index'); check(x.stream.previous0c === 99, 'bad index before copy');
  }
  for (const key of ['target08', 'accumulator10'] as const) {
    const x = fixture(); x.stream[key] = NaN; rejects(x.run, key);
    check(x.stream.previous0c === (key === 'target08' ? 99 : 10) && x.part.frame0c === (key === 'target08' ? 4 : 4.5),
      'malformed operand checked at reached boundary');
  }
  {
    const x = fixture(); Object.defineProperty(x.stream, 'previous0c', {writable: false});
    rejects(x.run, 'previous0c'); check(x.part.frame0c === 4 && x.stream.target08 === 10, 'readonly copy destination before update');
  }
  {
    const x = fixture(); Object.defineProperty(x.stream, 'target08', {writable: false});
    rejects(x.run, 'target08: non-writable'); check(x.stream.previous0c === 10 && x.part.frame0c === 4.5,
      'readonly target remains readable for copy and refuses only after dispatch');
  }
  {
    const x = fixture(); x.gates.family1d88 = null;
    for (const key of ['frame0c', 'segment2d'] as const) Object.defineProperty(x.part, key, {writable: false});
    Object.defineProperty(x.stream, 'accumulator10', {writable: false}); x.run();
    check(x.stream.target08 === 6, 'readonly operands accepted when dispatch bypasses writes');
  }
  for (const [accumulator, frame, expected] of [[-0, -0, -0], [-0, 0, 0], [1, 16777216, 16777216],
    [1, 16777218, 16777220], [2 ** -149, 0, 2 ** -149]]) {
    const x = fixture(); x.gates.family1d88 = null; x.stream.target08 = -0;
    x.stream.accumulator10 = accumulator!; x.part.frame0c = frame!; x.run();
    check(Object.is(x.stream.previous0c, -0) && Object.is(x.stream.target08, expected), 'signed zero, RN00 ties, NI0 subnormals');
  }
  {
    const x = fixture(); x.gates.family1d88 = null; x.stream.accumulator10 = Math.fround(3.4028234663852886e38);
    x.part.frame0c = x.stream.accumulator10; rejects(x.run, 'target08 result');
    check(x.stream.previous0c === 10 && x.stream.target08 === 10, 'overflow preserves copied prefix');
  }
  {
    const x = fixture(); x.gates.family1d88 = null; x.part.frame0c = 0.1;
    rejects(x.run, 'frame0c'); check(x.stream.previous0c === 10, 'non-f32 frame refused after copy');
  }
  {
    const x = fixture(); x.part.segment2d = 256;
    rejects(x.run, 'segment2d'); check(x.stream.previous0c === 10 && x.part.frame0c === 4.5, 'byte admission after playback');
  }
  {
    const x = fixture(); x.part.mode2f = 2; rejects(x.run, 'unsupported signed animation mode');
    check(x.stream.previous0c === 10 && x.binding.previous14 === 4 && x.stream.target08 === 10,
      'dispatch failure preserves both runtime prefixes');
  }
  for (const stage of ['layout', 'part'] as const) {
    const x = fixture(true); x.hooks[stage] = () => {throw Error(`synthetic ${stage} failure`);};
    rejects(x.run, `synthetic ${stage} failure`);
    check(x.stream.previous0c === 10 && x.stream.target08 === 10 && x.part.frame0c === 4.5, 'mapping/feedback getter failure after effects');
  }
  {
    const x = fixture(true);
    x.mappingAdapter.getLayout = () => {throw Error('replaced layout');};
    x.feedbackAdapter.getPart = () => {throw Error('replaced part');};
    x.dispatchAdapter.updatePart = () => {throw Error('replaced update');};
    x.run(); check(x.stream.target08 === 6.5 && x.calls() === 1, 'fixed own functions with original receiver');
  }
  for (const stage of ['update', 'layout', 'part'] as const) {
    const x = fixture(true); x.hooks[stage] = () => {try {x.run();} catch { /* injected caught reentry */ }};
    rejects(x.run, 'reentry was caught');
    check(x.stream.previous0c === 10 && x.stream.target08 === 10 && x.part.frame0c === 4.5, 'caught reentry poisons outer call after completed effect');
    delete x.hooks[stage]; x.run(); check(x.stream.target08 === 7, 'independent call recovers');
  }
  {
    const x = fixture(true); x.hooks.update = () => {try {x.runtime.bindActor(x.actor, x.input);} catch { /* injected caught reentry */ }};
    rejects(x.run, 'reentry was caught');
  }
  for (const result of [undefined, null, {}, Promise.resolve(0), 0.5, NaN, 128, -129]) {
    const x = fixture();
    // Synthetic return-contract failure; actual dispatch effects still happen.
    const adapter = {...x.dispatch, updatePart(id: symbol, index: number): number {
      x.dispatch.updatePart(id, index); return result as number;
    }};
    const runtime = createSourceStreamWaitTargetRuntime(x.mapping, x.feedback, adapter);
    runtime.bindActor(x.actor, x.input);
    rejects(() => runtime.continueUnmetNonCountdownWait(x.actor, 0), 'complete synchronously');
    const stream = runtime.getStreamPart(x.actor, 0);
    check(stream.previous0c === 10 && stream.target08 === 10 && x.part.frame0c === 4.5,
      'invalid/async return refuses after real effects before target calculation');
  }
  {
    const x = fixture(), otherFeedback = createSourceJointAnimationFeedbackRuntime(createSourceJObjAnimationRuntime());
    const runtime = createSourceStreamWaitTargetRuntime(x.mapping, otherFeedback, x.dispatch);
    runtime.bindActor(x.actor, x.input);
    rejects(() => runtime.continueUnmetNonCountdownWait(x.actor, 0), 'unknown/non-owned part');
    check(runtime.getStreamPart(x.actor, 0).previous0c === 10 && x.part.frame0c === 4.5,
      'foreign feedback ownership refuses after snapshot and actual dispatch');
  }
  {
    const x = fixture();
    // Synthetic malformed layout adapter: a valid dispatch still runs first.
    const adapter = {...x.mapping, getLayout() {return {parts: [[Symbol('foreign part')]], poses: [[], []]};}};
    const runtime = createSourceStreamWaitTargetRuntime(adapter, x.feedback, x.dispatch);
    runtime.bindActor(x.actor, x.input);
    rejects(() => runtime.continueUnmetNonCountdownWait(x.actor, 0), 'unknown/non-owned part');
    check(runtime.getStreamPart(x.actor, 0).previous0c === 10 && x.part.frame0c === 4.5, 'foreign layout part refusal prefix');
  }
  {
    const x = fixture(true);
    const fresh = createSourceStreamWaitTargetRuntime(x.mappingAdapter, x.feedback, x.dispatch);
    x.hooks.actor = () => {try {fresh.bindActor(x.actor, x.input);} catch { /* injected caught binding reentry */ }};
    rejects(() => fresh.bindActor(x.actor, x.input), 'reentry was caught');
    rejects(() => fresh.getStreamPart(x.actor, 0), 'unknown/non-owned');
    delete x.hooks.actor; fresh.bindActor(x.actor, x.input);
    check(fresh.getStreamPart(x.actor, 0).previous0c === 99, 'failed binding does not publish records');
  }
  {
    const x = fixture();
    const fresh = createSourceStreamWaitTargetRuntime(x.mapping, x.feedback, x.dispatch);
    rejects(() => fresh.bindActor(x.actor, x.input.slice(1)), 'exactly four');
    const initial = Object.freeze(x.input.map(record => Object.freeze({...record})));
    fresh.bindActor(x.actor, initial); check(fresh.getStreamPart(x.actor, 0).target08 === 10, 'readonly input copied');
    const accessor = Object.create(x.mapping);
    rejects(() => createSourceStreamWaitTargetRuntime(accessor, x.feedback, x.dispatch), 'own data property');
  }
}
