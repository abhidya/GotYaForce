import {createSourceActorAnimationDispatchRuntime, type SourceActorAnimationDispatchBinding,
  type SourceActorAnimationDispatchPartBinding, type SourceActorAnimationSetupRequest} from './actor-animation-dispatch.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
function check(value: boolean, message: string): void {if (!value) throw Error(`[actor-animation-dispatch-test] ${message}`);}
function rejects(run: () => unknown, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
function fixture(count = 0) {
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  // No JObjs in this unit fixture. Null part-descriptor completion below is the
  // real mapping behavior; any attempted animation/conversion refuses.
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
  const hooks: {layout?: () => void; animate?: () => unknown} = {};
  let calls = 0, layouts = 0;
  // Explicit synthetic fault adapters. Normal calls forward to real owned
  // mapping/feedback; injected hooks test refusal boundaries, not game effects.
  const adapter = {...mapping,
    getActor(id: symbol) {check(this === adapter, 'actor receiver'); return mapping.getActor(id);},
    getPartBinding(id: symbol) {check(this === adapter, 'part receiver'); return mapping.getPartBinding(id);},
    getLayout(id: symbol) {check(this === adapter, 'layout receiver'); layouts++; hooks.layout?.(); return mapping.getLayout(id);},
    animatePart(...args: Parameters<typeof mapping.animatePart>) {
      check(this === adapter, 'animate receiver');
      check(args[0] === actor && args[1] === 0 && args[2] === 0 && args[4] === 2, 'exact source mapping call');
      calls++; mapping.animatePart(...args); return hooks.animate?.();
    },
  };
  const feedbackAdapter = {...feedback, getPart(id: symbol) {
    check(this === feedbackAdapter, 'feedback receiver'); return feedback.getPart(id);
  }};
  const runtime = createSourceActorAnimationDispatchRuntime(adapter, feedbackAdapter);
  const actorInput: SourceActorAnimationDispatchBinding = {family1d88: Symbol('family presence'),
    shared1d8c: Symbol('shared presence'), marker578: 0, marker1db3: 0};
  const partInput: SourceActorAnimationDispatchPartBinding = {elapsed08: 2, previous10: 10, previous14: 11, linked36: 0};
  runtime.bindActor(actor, actorInput);
  for (const id of parts.flat()) runtime.bindPart(id, partInput);
  const id = parts[0]![0]!, part = feedback.getPart(id), binding = runtime.getPartBinding(id);
  return {mapping, feedback, adapter, feedbackAdapter, runtime, actor, id, parts, part, binding, hooks, actorInput, partInput,
    gates: runtime.getActorBinding(actor), header: mapping.getActor(actor), calls: () => calls, layouts: () => layouts,
    update: (number = 0) => runtime.updatePart(actor, number)};
}
export function runActorAnimationDispatchSelfTest(): void {
  const request: SourceActorAnimationSetupRequest = Object.freeze({frame: 0, group: 1, action: 2, transition: 3, mode: 0});
  // Poison operands prove no-op paths do not eagerly validate/copy the stream
  // record or request. Accessors are rejected without invoking them when reached.
  const skippedSource = Object.defineProperty({}, 'blockedMask1d9a', {
    get() {throw Error('blocked getter must never run');},
  }) as {blockedMask1d9a: number};
  const skippedRequest = Object.defineProperty({}, 'frame', {
    get() {throw Error('request getter must never run');},
  }) as SourceActorAnimationSetupRequest;
  const unchangedSetup = (x: ReturnType<typeof fixture>): void => {
    check(x.layouts() === 0 && x.calls() === 0 && x.binding.elapsed08 === 2 &&
      x.binding.previous10 === 10 && x.binding.previous14 === 11 && x.part.frame0c === 4 &&
      x.part.complete2e === 0 && x.mapping.getPartBinding(x.id).poseBuffer35 === 1,
    'setup does not resolve layouts, snapshot clocks, advance frames, animate or latch completion');
  };
  {
    const x = fixture(); x.gates.family1d88 = null;
    (x.gates as unknown as Record<string, unknown>).shared1d8c = 'malformed';
    x.gates.marker578 = NaN; x.gates.marker1db3 = NaN;
    check(x.runtime.setupPart(x.actor, NaN, skippedSource, skippedRequest) === undefined,
      'family null is a void no-op before shared, index, blocked or request reads');
    Object.defineProperty(x.gates, 'family1d88', {writable: false});
    x.runtime.setupPart(x.actor, -1, null as unknown as typeof skippedSource, null as unknown as SourceActorAnimationSetupRequest);
    unchangedSetup(x);
  }
  {
    const x = fixture(); x.gates.shared1d8c = null; x.gates.marker578 = NaN;
    Object.freeze(x.gates);
    x.runtime.setupPart(x.actor, 1, skippedSource, skippedRequest);
    x.runtime.setupPart(x.actor, 99, skippedSource, skippedRequest);
    unchangedSetup(x);
  }
  {
    const x = fixture(); x.gates.marker578 = 1; x.gates.marker1db3 = 1; Object.freeze(x.gates);
    x.part.frame0c = NaN; x.binding.elapsed08 = NaN;
    x.runtime.setupPart(x.actor, 1, skippedSource, skippedRequest);
    check(x.layouts() === 0 && x.calls() === 0 && x.binding.previous10 === 10 && x.binding.previous14 === 11,
      'exact marker no-op reads no playback fields, even malformed clocks');
  }
  for (const [first, second] of [[0, NaN], [2, NaN], [255, NaN], [1, 0], [1, 2], [1, 255]]) {
    const x = fixture(); x.gates.marker578 = first!; x.gates.marker1db3 = second!;
    Object.freeze(x.gates);
    rejects(() => x.runtime.setupPart(x.actor, 1, Object.freeze({blockedMask1d9a: 0}), skippedRequest), 'setup table/4871c');
    unchangedSetup(x);
  }
  for (const number of [0, 1, 2, 3]) {
    // Include high-bit bytes to exercise signed-char promotion with the selected
    // source bit, not truthiness of the complete mask or unsigned sign guesses.
    for (const mask of [0, 1, 2, 4, 8, 127, 128, 129, 130, 132, 136, 255]) {
      const x = fixture(); if (number !== 1) {x.gates.marker578 = NaN; x.gates.marker1db3 = NaN;}
      Object.freeze(x.gates);
      const blocked = Object.freeze({blockedMask1d9a: mask});
      rejects(() => x.runtime.setupPart(x.actor, number, blocked, request),
        (mask & (1 << number)) !== 0 ? 'blocked setup requires unsupported 4a41c' : 'unblocked setup requires unsupported setup table/4871c');
      unchangedSetup(x);
    }
  }
  {
    const x = fixture(), blocked = {blockedMask1d9a: 0};
    rejects(() => x.runtime.setupPart(x.actor, 0, blocked, skippedRequest), 'setup table/4871c');
    blocked.blockedMask1d9a = 1;
    rejects(() => x.runtime.setupPart(x.actor, 0, blocked, skippedRequest), 'unsupported 4a41c');
    rejects(() => x.runtime.setupPart(x.actor, 0, skippedSource, request), 'blockedMask1d9a: own data property');
    for (const mask of [-1, 256, NaN, 0.5]) {
      rejects(() => x.runtime.setupPart(x.actor, 0, {blockedMask1d9a: mask}, request), 'blockedMask1d9a');
    }
    for (const number of [-1, 4, NaN, 0.5]) {
      rejects(() => x.runtime.setupPart(x.actor, number, blocked, request), 'partNumber');
    }
    rejects(() => x.runtime.setupPart(Symbol('foreign'), 0, blocked, request), 'unknown/non-owned actor');
    unchangedSetup(x);
    check(x.update() === 0, 'setup refusal releases busy guard for independent playback');
  }
  {
    const x = fixture(); x.gates.marker578 = 1; x.gates.marker1db3 = NaN;
    rejects(() => x.runtime.setupPart(x.actor, 1, skippedSource, request), 'marker1db3');
    x.gates.marker578 = NaN;
    rejects(() => x.runtime.setupPart(x.actor, 1, skippedSource, request), 'marker578');
    (x.gates as unknown as Record<string, unknown>).shared1d8c = 0;
    rejects(() => x.runtime.setupPart(x.actor, 1, skippedSource, request), 'shared1d8c');
    (x.gates as unknown as Record<string, unknown>).family1d88 = 0;
    rejects(() => x.runtime.setupPart(x.actor, 1, skippedSource, request), 'family1d88');
    unchangedSetup(x);
  }
  {
    const x = fixture(); x.gates.marker578 = 1; x.gates.marker1db3 = 1;
    x.hooks.layout = () => {try {x.runtime.setupPart(x.actor, 1, skippedSource, skippedRequest);} catch { /* caught reentry */ }};
    rejects(x.update, 'reentry was caught');
    check(x.calls() === 0 && x.binding.previous10 === 10, 'setup no-op cannot evade same-runtime mutation reentry guard');
    delete x.hooks.layout;
    x.runtime.setupPart(x.actor, 1, skippedSource, skippedRequest);
    check(x.update() === 0, 'later setup/playback recover after caught reentry');
  }
  {
    const x = fixture(); x.actorInput.family1d88 = null; x.partInput.elapsed08 = 99;
    check(Object.isSealed(x.gates) && Object.isSealed(x.binding), 'bindings sealed');
    check(x.update() === 0 && x.calls() === 1 && x.binding.elapsed08 === 2.5 && x.part.frame0c === 4.5,
      'real zero-range continuation advances clocks without fabricating completion');
    check(x.binding.previous10 === 2 && x.binding.previous14 === 4, 'snapshots use prior clocks');
    for (const value of [1, 127, 128, 255]) {
      x.part.complete2e = value; check(x.update() === (value << 24 >> 24), 'live signed completion, no clear or early skip');
    }
    check(x.calls() === 5, 'completed parts still animate');
    rejects(() => x.runtime.bindActor(x.actor, x.actorInput), 'already bound');
    rejects(() => x.runtime.bindPart(x.id, x.partInput), 'already bound');
    rejects(() => x.runtime.bindPart(Symbol('foreign'), x.partInput), 'unknown/non-owned');
  }
  {
    const x = fixture(1); check(x.update() === 1 && x.part.complete2e === 1, 'actual null-descriptor mapper latches completion');
    check(x.mapping.getPartBinding(x.id).poseBuffer35 === 0, 'actual mapper receives pose bank zero');
  }
  for (const number of [1, 2, 3]) {
    const x = fixture(), id = x.parts[0]![number]!, selected = x.runtime.getPartBinding(id);
    x.gates.marker578 = 1; x.gates.marker1db3 = 2;
    check(x.update(number) === 0 && selected.elapsed08 === 2.5 && selected.previous10 === 2 &&
      x.feedback.getPart(id).frame0c === 4.5 && x.binding.elapsed08 === 2 && x.part.frame0c === 4 &&
      x.mapping.getPartBinding(id).poseBuffer35 === 0 && x.mapping.getPartBinding(x.id).poseBuffer35 === 1,
    'selected part number is retained; freeze requires exactly1 in both marker bytes');
  }
  {
    const x = fixture(); x.gates.family1d88 = null;
    (x.gates as unknown as Record<string, unknown>).shared1d8c = 'malformed'; x.part.frame0c = NaN;
    check(x.update(NaN) === 1 && x.layouts() === 0 && x.binding.previous10 === 10, 'first null skips shared, part index and source fields');
    x.gates.family1d88 = Symbol(); x.gates.shared1d8c = null; x.gates.marker578 = NaN;
    check(x.update(1) === 1 && x.layouts() === 0, 'second null skips marker and part access');
    x.gates.shared1d8c = Symbol(); x.gates.marker578 = 1; x.gates.marker1db3 = 1;
    check(x.update(1) === 0 && x.layouts() === 0, 'marker conjunction skips layout/snapshots');
    x.gates.marker578 = 0; x.gates.marker1db3 = NaN;
    check(x.update(1) === 0 && x.layouts() === 1, 'false first marker skips second marker');
  }
  for (const mode of [1, 2, 127, 128, 255]) {
    const x = fixture(); x.part.mode2f = mode;
    rejects(x.update, `unsupported signed animation mode ${mode << 24 >> 24}`);
    check(x.binding.previous10 === 2 && x.binding.previous14 === 4 && x.binding.elapsed08 === 2 && x.calls() === 0,
      'unsupported mode refuses after snapshots but before clocks');
  }
  {
    const x = fixture(); x.binding.elapsed08 = -0; x.part.frame0c = -0; x.part.mode2f = 2;
    rejects(x.update, 'unsupported signed');
    check(Object.is(x.binding.previous10, -0) && Object.is(x.binding.previous14, -0), 'undefined4 snapshots preserve negative zero');
  }
  {
    const x = fixture(); x.binding.linked36 = 255; rejects(x.update, 'linked mode0');
    check(x.binding.elapsed08 === 2.5 && x.part.frame0c === 4.5 && x.calls() === 0, 'linked refusal retains both increments');
  }
  {
    const x = fixture(); x.part.frame0c = NaN; rejects(x.update, 'frame0c');
    check(x.binding.previous10 === 2 && x.binding.previous14 === 11, 'bad frame retains first snapshot only');
  }
  {
    const x = fixture(); Object.defineProperty(x.binding, 'previous14', {writable: false});
    rejects(x.update, 'previous14'); check(x.binding.previous10 === 2 && x.binding.elapsed08 === 2, 'snapshot store boundary');
  }
  {
    const x = fixture(); x.header.timestep1dc8 = Math.fround(3.4028234663852886e38); x.part.frame0c = x.header.timestep1dc8;
    rejects(x.update, 'frame0c result');
    check(x.binding.elapsed08 === x.header.timestep1dc8 && x.calls() === 0, 'second overflow preserves first increment');
  }
  {
    const x = fixture(); x.header.timestep1dc8 = Math.fround(3.4028234663852886e38);
    x.binding.elapsed08 = x.header.timestep1dc8;
    rejects(x.update, 'elapsed08 result');
    check(x.binding.previous10 === x.header.timestep1dc8 && x.binding.previous14 === 4 &&
      x.binding.elapsed08 === x.header.timestep1dc8 && x.part.frame0c === 4 && x.calls() === 0,
    'first overflow retains both snapshots but no increment or mapping');
  }
  {
    const x = fixture(); x.header.timestep1dc8 = 1; x.binding.elapsed08 = 16777216; x.part.frame0c = 16777218;
    x.update(); check(x.binding.elapsed08 === 16777216 && x.part.frame0c === 16777220,
      'both binary32 tie directions round once to nearest even');
  }
  {
    const x = fixture(); Object.defineProperty(x.binding, 'previous10', {writable: false});
    rejects(x.update, 'previous10');
    check(x.binding.previous14 === 11 && x.binding.elapsed08 === 2 && x.calls() === 0, 'first snapshot write refuses before second');
  }
  {
    const x = fixture(); x.header.timestep1dc8 = 2 ** -149; x.binding.elapsed08 = 0; x.part.frame0c = 0;
    x.update(); check(x.binding.elapsed08 === 2 ** -149 && x.part.frame0c === 2 ** -149, 'NI0 subnormal addition');
  }
  {
    const x = fixture(); x.adapter.animatePart = () => {throw Error('replaced method');};
    x.adapter.getLayout = () => {throw Error('replaced getter');}; x.feedbackAdapter.getPart = () => {throw Error('replaced feedback');};
    check(x.update() === 0 && x.calls() === 1, 'fixed adapters and retained shared source records');
  }
  for (const stage of ['layout', 'animate'] as const) {
    const x = fixture(); x.hooks[stage] = () => {try {x.update();} catch { /* injected caught reentry */ }};
    rejects(x.update, 'reentry was caught');
    check(x.calls() === (stage === 'animate' ? 1 : 0), 'reentry poisons at adapter return boundary');
    delete x.hooks[stage]; check(x.update() === 0, 'later independent call recovers after caught reentry');
  }
  {
    const x = fixture(); x.hooks.animate = () => 7; rejects(x.update, 'return undefined');
    check(x.binding.elapsed08 === 2.5 && x.calls() === 1, 'nonvoid adapter retains completed writes/effect');
  }
  {
    const x = fixture(); x.hooks.animate = () => {x.part.complete2e = 255;};
    check(x.update() === -1, 'completion is reloaded after mapping rather than cached');
  }
  {
    const x = fixture(); x.hooks.animate = () => {try {x.runtime.bindPart(x.id, x.partInput);} catch { /* fault injection */ }};
    rejects(x.update, 'reentry was caught');
  }
  {
    const x = fixture(); x.gates.marker578 = NaN; x.gates.marker1db3 = NaN;
    check(x.update() === 0, 'non-part1 skips both markers'); rejects(() => x.update(4), 'partNumber');
  }
}
