import {createSourceStreamWaitRuntime, isSourceStreamWaitRuntime, type SourceStreamWaitPartInitial} from './stream-wait.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';
import {createSourceActorAnimationDispatchRuntime, type SourceActorAnimationSetupRequest} from './actor-animation-dispatch.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createRomActor, type RomActor} from './actor.js';
import {createSourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import {createSourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import {hasIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
function check(value: boolean, message: string): void {if (!value) throw Error(`[stream-wait-test] ${message}`);}
function rejects(run: () => unknown, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
function fixture(flags = 1, synthetic = false, gqr5?: number, maxCommands?: number, initialState?: {state1b?: number; auxiliary1c?: number}) {
  const count = 0;
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
  const targets = createSourceStreamWaitTargetRuntime(mapping, feedback, dispatch);
  targets.bindActor(actor, Array.from({length: 4}, () => ({target08: 10, previous0c: 99, accumulator10: 2})));
  const hooks: {update?: () => void; target?: () => void; layout?: () => void; part?: () => void; targetGet?: (index: number) => void; setup?: (index: number, request: Readonly<SourceActorAnimationSetupRequest>) => void} = {};
  let calls = 0, targetCalls = 0;
  let dispatchReturn: unknown, targetReturn: unknown, targetGetReturn: unknown, setupReturn: unknown;
  // Explicit synthetic forwarding fault/counter wrappers. The real implementations
  // always execute; these wrappers never simulate animation or predicate results.
  const mappingAdapter = {...mapping, getLayout(id: symbol) {
    check(this === mappingAdapter, 'layout receiver'); hooks.layout?.(); return mapping.getLayout(id);
  }};
  const feedbackAdapter = {...feedback, getPart(id: symbol) {
    check(this === feedbackAdapter, 'feedback receiver'); hooks.part?.(); return feedback.getPart(id);
  }};
  const dispatchAdapter = {...dispatch, getPartBinding(id: symbol) {
    check(this === dispatchAdapter, 'dispatch get receiver'); return dispatch.getPartBinding(id);
  }, setupPart(id: symbol, index: number, blockedSource: {readonly blockedMask1d9a: number}, request: Readonly<SourceActorAnimationSetupRequest>): void {
    check(this === dispatchAdapter, 'setup receiver');
    check(blockedSource === runtime.getActorBinding(id), 'setup receives actual shared blocked source');
    dispatch.setupPart(id, index, blockedSource, request); hooks.setup?.(index, request);
    return setupReturn as undefined;
  }, updatePart(id: symbol, index: number) {
    check(this === dispatchAdapter, 'dispatch receiver'); calls++;
    const result = dispatch.updatePart(id, index); hooks.update?.();
    return (dispatchReturn === undefined ? result : dispatchReturn) as number;
  }};
  const targetAdapter = {...targets, getStreamPart(id: symbol, index: number) {
    check(this === targetAdapter, 'target get receiver'); hooks.targetGet?.(index);
    return (targetGetReturn === undefined ? targets.getStreamPart(id, index) : targetGetReturn) as ReturnType<typeof targets.getStreamPart>;
  }, continueUnmetNonCountdownWait(id: symbol, index: number): void {
    check(this === targetAdapter, 'target receiver'); targetCalls++;
    targets.continueUnmetNonCountdownWait(id, index); hooks.target?.();
    return targetReturn as undefined;
  }};
  const options = {mapping: synthetic ? mappingAdapter : mapping,
    feedback: synthetic ? feedbackAdapter : feedback, dispatch: synthetic ? dispatchAdapter : dispatch,
    targets: synthetic ? targetAdapter : targets, ...(gqr5 === undefined ? {} : {gqr5}), ...(maxCommands === undefined ? {} : {maxCommands})};
  const runtime = createSourceStreamWaitRuntime(options);
  const command = runtime.createCommand({flags01: flags});
  const input: SourceStreamWaitPartInitial[] = Array.from({length: 4}, () => ({current00: command, wait14: 3, finished1a: 0, event1e: 9, ...initialState}));
  runtime.bindActor(actor, {activeMask579: 15, blockedMask1d9a: 0}, input);
  return {runtime, mapping, feedback, dispatch, targets, actor, parts, command, input, hooks, options,
    mappingAdapter, feedbackAdapter, dispatchAdapter, targetAdapter,
    calls: () => calls, targetCalls: () => targetCalls,
    getReturns(value: unknown) {targetGetReturn = value;},
    setupReturns(value: unknown) {setupReturn = value;},
    returns(d: unknown, t: unknown) {dispatchReturn = d; targetReturn = t;},
    gate: runtime.getActorBinding(actor), header: mapping.getActor(actor),
    control: (i = 0) => runtime.getPartBinding(actor, i),
    part: (i = 0) => feedback.getPart(parts[0]![i]!),
    binding: (i = 0) => dispatch.getPartBinding(parts[0]![i]!),
    run: (mask = 1) => runtime.update(actor, mask)};
}
// Real setup/movement retain the same actor, mapping and stream gate owners.
// Unreached metadata/archive dependencies refuse rather than simulate effects.
function stateFixture(actual: RomActor = createRomActor(), deferJoin = false) {
  const x = fixture(), unsupported = (): never => {throw Error('unexpected state-command setup effect');};
  x.runtime.bindStartActor(x.actor, {familyBank1d80: null, sharedBank1d84: null, defaultSelector582: 73, marker709: 19});
  const setup = createSourceActorAnimationSetupRuntime({mapping: x.mapping, feedback: x.feedback, dispatch: x.dispatch,
    descriptors: createSourceAnimationDescriptorBankRuntime(), starts: x.runtime,
    metadata: {getPartBinding: unsupported, applyMetadata: unsupported}, archiveBanks: {resolveArchive: unsupported}});
  setup.bindActor(x.actor, {familyBank1d78: null, sharedBank1d7c: null, movement6d8: 1});
  const movement = createSourceActorMovementFollowupRuntime({mapping: x.mapping, waits: x.runtime, setup});
  movement.bindActor(x.actor, actual, {byte661: 0, field66c: 0, field670: 0});
  if (!deferJoin) x.runtime.bindActualActor(x.actor, movement);
  const parse = (bytes: readonly number[], mask = 3) => {
    const base = x.runtime.createStream(new Uint8Array(bytes));
    x.runtime.parseWaitRecord(x.actor, mask, base); return base;
  };
  return {...x, actual, setup, movement, parse, start: x.runtime.getStartActorBinding(x.actor)};
}
function runStateCommandTests(): void {
  const op2 = [2, 255, 128, 255, 17, 18, 0, 0], op3 = [3, 255, 128, 0, 0, 0, 0xab, 0xcd], wait = [0, 1, 0, 7];
  {
    const x = stateFixture();
    check(x.runtime.hasActualActorBinding(x.actor) && x.runtime.getActualActor(x.actor) === x.actual && x.runtime.getMappingActor(x.actor) === x.header,
      'one-time actual join exposes only the retained canonical actor/mapping');
    check(!Object.hasOwn(x.actual, 'byte6e8') && !Object.hasOwn(x.actual, 'byte6e9') &&
      x.control().state1b === undefined && x.control().auxiliary1c === undefined,
      'new source fields have no fabricated allocation bytes');
    rejects(() => x.runtime.bindActualActor(x.actor, x.movement), 'already bound');
    rejects(() => x.runtime.getActualActor(Symbol()), 'unknown/non-owned');
    rejects(() => x.runtime.bindActor(x.actor, {activeMask579: 15, blockedMask1d9a: 0}, x.input), 'already bound');
    check(Object.isSealed(x.control()) && Object.isFrozen(x.runtime), 'canonical parts and getter methods cannot be replaced');
  }
  for (const field of ['state1b', 'auxiliary1c'] as const) {
    for (const bad of [-1, 256, 0.5, NaN, Infinity])
      rejects(() => fixture(1, false, undefined, undefined, {[field]: bad}), `${field}: unsigned integer`);
    for (const good of [0, 127, 128, 255]) {
      const x = fixture(1, false, undefined, undefined, {[field]: good});
      check(x.control()[field] === good, 'explicit source part initialization retains unsigned byte bits');
    }
  }
  {
    const x = stateFixture(createRomActor(), true);
    check(!x.runtime.hasActualActorBinding(x.actor), 'unjoined stream reports no invented actual owner');
    rejects(() => x.runtime.bindActualActor(x.actor, {...x.movement}), 'genuine mapping and movement');
    const other = stateFixture();
    rejects(() => x.runtime.bindActualActor(x.actor, other.movement), 'unknown/non-owned movement actor');
    const wrongWait = createSourceStreamWaitRuntime(x.options);
    wrongWait.bindActor(x.actor, {activeMask579: 15, blockedMask1d9a: 0}, x.input);
    const wrongMovement = createSourceActorMovementFollowupRuntime({mapping: x.mapping, waits: wrongWait, setup: x.setup});
    wrongMovement.bindActor(x.actor, x.actual, {byte661: 0, field66c: 0, field670: 0});
    rejects(() => x.runtime.bindActualActor(x.actor, wrongMovement), 'matched canonical');
    x.runtime.bindActualActor(x.actor, x.movement);
    check(x.runtime.getActualActor(x.actor) === x.actual, 'rejected owner substitution cannot replace canonical join');
    rejects(() => wrongWait.bindActualActor(x.actor, wrongMovement), 'already assigned to a stream identity');
  }
  for (const mask of [0, 1, 2, 3, 4, 8, 15, 0xfffffff0, 0xffffffff]) {
    const x = stateFixture(); x.actual.prevActionIndex = 197; x.actual.controlWord = 0x87654fed;
    x.actual.contactP0 = 43; x.actual.contactP1 = 44; x.actual.dashStrength1d0f = 45; x.actual.faceGate1d10 = 46;
    x.actual.parts[0]!.stateByte = 47; x.actual.parts[1]!.stateByte = 48;
    x.actual.byte6e8 = NaN; x.actual.byte6e9 = NaN;
    const base = x.parse([...op2, ...op3, ...wait], mask);
    check(x.control().state1b === ((mask & 1) ? 128 : undefined) &&
      x.control().auxiliary1c === ((mask & 1) ? 255 : undefined) &&
      x.control(1).state1b === ((mask & 2) ? 255 : undefined) &&
      x.control(1).auxiliary1c === ((mask & 2) ? 128 : undefined), 'opcode02/03 use fixed parts0/1 and independent mask bits');
    check((mask & 1) ? x.actual.byte6e8 === 17 && x.actual.byte6e9 === 18 : Number.isNaN(x.actual.byte6e8) && Number.isNaN(x.actual.byte6e9),
      'actual byte stores overwrite without stale-value validation only for mask1');
    check(x.actual.controlWord === ((mask & 2) ? 0x87654bcd : 0x87654fed) && x.actual.prevActionIndex === 197 && x.start.defaultSelector582 === 73,
      'opcode03 masks bits4..11, opcode02ff preserves582, neither touches584');
    for (let i = 0; i < 4; i++) if (mask & (1 << i))
      check(x.control(i).current00 === x.runtime.cursorAt(base, 16) && x.control(i).wait14 === 7,
        'both state records advance by8 including mask-skipped records');
    check(x.control(2).state1b === undefined && x.control(3).auxiliary1c === undefined, 'no legacy/per-part-index state fanout');
    check(x.actual.contactP0 === 43 && x.actual.contactP1 === 44 && x.actual.dashStrength1d0f === 45 &&
      x.actual.faceGate1d10 === 46 && x.actual.parts[0]!.stateByte === 47 && x.actual.parts[1]!.stateByte === 48,
      'source state stores never update competing legacy actor/contact/part fields');
  }
  for (let selector = 0; selector <= 255; selector++) {
    const x = stateFixture(); x.start.defaultSelector582 = selector === 254 ? 128 : NaN;
    if (selector === 255) Object.defineProperty(x.start, 'defaultSelector582', {writable: false});
    x.parse([2, selector, 0, 0, 0, 0, 0, 0, ...wait], 1);
    check(selector === 255 ? Number.isNaN(x.start.defaultSelector582) : x.start.defaultSelector582 === (selector === 254 ? 129 : selector),
      'all opcode02 selector bytes preserve ff, XOR fe, or overwrite without old-value validation');
  }
  {
    const x = stateFixture(); x.start.defaultSelector582 = NaN;
    rejects(() => x.parse([2, 254, 128, 255, 17, 18, 0, 0, ...wait], 1), 'defaultSelector582: unsigned');
    check(x.control().state1b === 128 && x.control().auxiliary1c === 255 && x.actual.byte6e8 === 17 && x.actual.byte6e9 === 18,
      'invalid toggle operand refuses after four prior stores');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual), 'canonical partial stream execution permanently poisons caller lifecycle');
    x.start.defaultSelector582 = 0;
    rejects(() => x.parse(wait, 0), 'known incomplete source Double lifecycle');
    rejects(() => x.runtime.startStream(x.actor, 0, 4, 0), 'known incomplete source Double lifecycle');
    rejects(() => x.runtime.update(x.actor, 0), 'known incomplete source Double lifecycle');
  }
  // Selected store admission stays lazy: each earlier write survives the first
  // readonly destination, and none of the later fields/cursor installs changes.
  for (let fault = 0; fault < 5; fault++) {
    const x = stateFixture(); x.actual.byte6e8 = 31; x.actual.byte6e9 = 32;
    x.control().state1b = 11; x.control().auxiliary1c = 12;
    const slots = [[x.control(), 'state1b', 128], [x.control(), 'auxiliary1c', 255],
      [x.actual, 'byte6e8', 17], [x.actual, 'byte6e9', 18], [x.start, 'defaultSelector582', 7]] as const;
    const before = slots.map(([owner, key]) => Object.getOwnPropertyDescriptor(owner, key)!.value);
    Object.defineProperty(slots[fault]![0], slots[fault]![1], {writable: false});
    rejects(() => x.parse([2, 7, ...op2.slice(2), ...wait], 1), `${slots[fault]![1]}: non-writable`);
    for (let i = 0; i < slots.length; i++) {
      const [owner, key, after] = slots[i]!;
      check(Object.is(Object.getOwnPropertyDescriptor(owner, key)!.value, i < fault ? after : before[i]), 'opcode02 exact ordered store prefix');
    }
    check(x.control().current00 === x.command && x.actual.prevActionIndex === 0, 'failed handler installs no wait and preserves584');
  }
  for (let fault = 0; fault < 3; fault++) {
    const x = stateFixture(); x.control(1).state1b = 11; x.control(1).auxiliary1c = 12; x.actual.controlWord = 0x12345fed;
    const slots = [[x.control(1), 'state1b'], [x.control(1), 'auxiliary1c'], [x.actual, 'controlWord']] as const;
    Object.defineProperty(slots[fault]![0], slots[fault]![1], {writable: false});
    rejects(() => x.parse([...op3, ...wait], 2), `${slots[fault]![1]}: non-writable`);
    check(x.control(1).state1b === (fault > 0 ? 255 : 11) && x.control(1).auxiliary1c === (fault > 1 ? 128 : 12) &&
      x.actual.controlWord === 0x12345fed, 'opcode03 states precede control and preserve readonly prefix');
  }
  for (const opcode of [2, 3]) for (let length = 1; length < 8; length++) {
    const x = stateFixture(), record = opcode === 2 ? op2 : op3;
    rejects(() => x.parse(record.slice(0, length), opcode === 2 ? 1 : 2), 'out of bounds');
    if (opcode === 2) check(x.control().state1b === (length > 2 ? 128 : undefined) &&
      x.control().auxiliary1c === (length > 3 ? 255 : undefined) && x.actual.byte6e8 === (length > 4 ? 17 : undefined) &&
      x.actual.byte6e9 === (length > 5 ? 18 : undefined), 'opcode02 reached truncation preserves only preceding byte stores');
    else check(x.control(1).state1b === (length > 1 ? 255 : undefined) && x.control(1).auxiliary1c === (length > 2 ? 128 : undefined) &&
      x.actual.controlWord === 0, 'opcode03 halfword truncation comes after state stores');
    check(x.control().current00 === x.command, 'truncated handler never installs a terminal wait');
  }
  {
    const x = stateFixture(createRomActor(), true);
    rejects(() => x.parse([...op2, ...wait], 1), 'genuine movement actual-actor join required');
    check(x.control().state1b === 128 && x.control().auxiliary1c === 255, 'missing actual owner is reached after prior state stores');
    rejects(() => x.runtime.bindActualActor(x.actor, x.movement), 'incomplete mode1');
    rejects(() => x.parse(wait, 0), 'incomplete mode1');
    rejects(() => x.runtime.startStream(x.actor, 0, 4, 0), 'incomplete mode1');
    rejects(() => x.runtime.update(x.actor, 0), 'incomplete mode1');
  }
  for (const opcode of [2, 3]) {
    const x = fixture(), selection = opcode === 2 ? 2 : 1;
    Object.defineProperty(x.control(opcode - 2), 'state1b', {writable: false});
    const base = x.runtime.createStream(new Uint8Array([opcode, 0, 0, 0, 0, 0, 0, 0, ...wait]));
    x.runtime.parseWaitRecord(x.actor, selection, base);
    check(x.control(opcode - 2).state1b === undefined, 'skipped mask does not demand actual join or readonly destination');
    const truncated = x.runtime.createStream(new Uint8Array([opcode]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, truncated), 'out of bounds');
  }
  {
    const x = stateFixture(createRomActor(), true);
    x.parse([3, 255, 128, 0, 0, 0, 255, 255, ...wait], 2);
    check(x.control(1).state1b === 255 && x.control(1).auxiliary1c === 128, 'opcode03 ffff state stores do not require actual control owner');
  }
  {
    const x = stateFixture(); x.actual.controlWord = NaN; Object.defineProperty(x.actual, 'controlWord', {writable: false});
    x.parse([3, 255, 128, 0, 0, 0, 255, 255, ...wait], 2);
    check(Number.isNaN(x.actual.controlWord), 'ffff never validates or writes actual controlWord');
  }
  {
    const x = stateFixture(); Object.preventExtensions(x.actual);
    rejects(() => x.parse([...op2, ...wait], 1), 'byte6e8: absent actual byte storage is non-extensible');
    check(x.control().state1b === 128 && x.control().auxiliary1c === 255 && !Object.hasOwn(x.actual, 'byte6e8'),
      'non-extensible actual record fails lazily after part stores, without seeded zero slots');
  }
  {
    const x = stateFixture(); x.control().state1b = 128; x.control().auxiliary1c = 255;
    x.control(1).state1b = 254; x.control(1).auxiliary1c = 129;
    x.runtime.startStream(x.actor, 15, 4, 0);
    check(x.control().state1b === 128 && x.control().auxiliary1c === 255 && x.control(1).state1b === 254 &&
      x.control(1).auxiliary1c === 129, '4c020 reset has exactly its existing stores and never resets1b/1c');
  }
  // Adversarial proxy instrumentation is outside the non-proxy host contract;
  // it observes genuine stored fields, never supplies replacement source owners
  // or callbacks. It checks split stores, fresh reads, and caught reentry.
  for (const mode of ['observe', 'mutate', 'readonly-second', 'invalid-reload', 'reentry'] as const) {
    const target = createRomActor(); target.controlWord = 0x87654fed;
    const stores: number[] = [], descriptorReads: number[] = [];
    let x: ReturnType<typeof stateFixture>, armed = false;
    const proxy = new Proxy(target, {
      getOwnPropertyDescriptor(owner, key) {
        if (armed && key === 'controlWord') descriptorReads.push(owner.controlWord);
        return Reflect.getOwnPropertyDescriptor(owner, key);
      },
      set(owner, key, value) {
        const result = Reflect.set(owner, key, value, owner);
        if (armed && key === 'controlWord') {
          stores.push(value as number);
          check(x.control(1).state1b === 255 && x.control(1).auxiliary1c === 128, 'states precede both actual control stores');
          if (stores.length === 1) {
            if (mode === 'mutate') owner.controlWord = 0x80000005;
            if (mode === 'readonly-second') Object.defineProperty(owner, 'controlWord', {writable: false});
            if (mode === 'invalid-reload') owner.controlWord = NaN;
            if (mode === 'reentry') try {x.runtime.update(x.actor, 0);} catch { /* swallowed by adversary */ }
          }
        }
        return result;
      },
    });
    x = stateFixture(proxy); armed = true;
    if (mode === 'readonly-second') rejects(() => x.parse([...op3, ...wait], 2), 'controlWord: non-writable');
    else if (mode === 'invalid-reload') rejects(() => x.parse([...op3, ...wait], 2), 'controlWord: unsigned');
    else if (mode === 'reentry') rejects(() => x.parse([...op3, ...wait], 2), 'reentry');
    else x.parse([...op3, ...wait], 2);
    check(stores[0] === 0x8765400d && stores.length === ((mode === 'observe' || mode === 'mutate') ? 2 : 1),
      'first cleared controlWord store is observable and survives later refusal');
    if (mode === 'observe') check(stores[1] === 0x87654bcd && descriptorReads.join(',') ===
      [0x87654fed, 0x87654fed, 0x8765400d, 0x8765400d].join(','), 'opcode03 two actual reads and two reached writable checks');
    if (mode === 'mutate') check(stores[1] === 0x80000bc5, 'second control operation uses fresh actual current word');
    if (mode === 'reentry') {
      check(target.controlWord === 0x8765400d && hasIncompleteSourceActorDoubleLifecycle(proxy), 'caught store reentry preserves first effect and poisons actor');
      armed = false; rejects(() => x.runtime.update(x.actor, 0), 'known incomplete');
    }
  }
  {
    const x = stateFixture(), bytes = new Uint8Array([...op2, ...op3, ...wait]);
    const base = x.runtime.createStream(bytes); bytes.fill(255);
    x.runtime.parseWaitRecord(x.actor, 3, base);
    check(x.control().state1b === 128 && x.actual.byte6e9 === 18 && x.actual.controlWord === 0xbc0,
      'external input mutations cannot change copied state-command operands');
  }
}
export function runSourceStreamWaitSelfTest(): void {
  runStateCommandTests();
  {
    const x = fixture();
    check(isSourceStreamWaitRuntime(x.runtime) && Object.isFrozen(x.runtime), 'genuine frozen stream runtime is branded');
    for (const value of [undefined, null, {}, {...x.runtime}, Object.create(x.runtime)])
      check(!isSourceStreamWaitRuntime(value), 'copied/inherited stream methods do not confer source runtime ownership');
  }
  {
    const x = fixture(); x.input[0]!.wait14 = 999;
    check(x.control().wait14 === 3 && Object.isSealed(x.control()) && Object.isSealed(x.gate) &&
      Object.isSealed(x.runtime.getCommand(x.command)) && Object.isFrozen(x.runtime), 'copied/sealed own sidecars');
    x.control().current00 = null; x.gate.activeMask579 = 0;
    check(x.run(0) === 1, 'null ignores selection');
    for (let i = 0; i < 4; i++) check(x.control(i).finished1a === 1 && x.control(i).event1e === 9 && x.part(i).frame0c === 4, 'null sets only finished');
  }
  {
    const x = fixture(); x.control().current00 = null;
    Object.defineProperty(x.control(2), 'finished1a', {writable: false});
    rejects(x.run, 'finished1a: non-writable');
    check(x.control(0).finished1a === 1 && x.control(1).finished1a === 1 && x.control(3).finished1a === 0, 'ordered null prefix');
  }
  for (const mask of [0, 1, 2, 4, 8, 15, 0xffffffff]) {
    const x = fixture(); x.gate.activeMask579 = 0x85;
    check(x.run(mask) === 0, 'unmet aggregation');
    for (let i = 0; i < 4; i++) check(x.control(i).event1e === ((mask & 5 & (1 << i)) ? 0 : 9), 'low-four mask intersection');
  }
  {
    const x = fixture(1, true); x.gate.blockedMask1d9a = 1;
    x.control(1).current00 = Symbol('unused foreign'); x.control(1).wait14 = NaN;
    x.hooks.update = () => {x.gate.activeMask579 = 0; x.gate.blockedMask1d9a = 3;};
    check(x.run(3) === 0 && x.calls() === 2 && x.control(1).event1e === 0, 'snapshot active, live blocked, blocked operands lazy');
  }
  for (const linked of [0, 1, 2, 127, 128, 255]) {
    const x = fixture(1, true); x.control().finished1a = 255; x.control().current00 = Symbol('unused');
    x.control().wait14 = NaN; x.binding().linked36 = linked;
    if (linked === 1) {
      rejects(x.run, 'linked mode0');
      check(x.binding().elapsed08 === 2.5 && x.part().frame0c === 4.5 && x.control().event1e === 0, 'real linked failure prefix');
    } else check(x.run() === 1 && x.calls() === 0, 'finished exact linked1 only');
  }
  {
    const x = fixture(); x.part().frame0c = 100; check(x.run() === 0 && x.binding().elapsed08 === 2.5, 'threshold uses elapsed not frame');
    check(x.targets.getStreamPart(x.actor, 0).previous0c === 10 && x.targets.getStreamPart(x.actor, 0).target08 === 102.5, 'actual unmet target effects');
    x.control().wait14 = 2; x.part().frame0c = NaN; x.binding().linked36 = 255;
    check(x.run() === 1 && x.control().finished1a === 1, 'met stop skips frame/linked dispatch');
  }
  for (const complete of [0, 1, 127, 128, 255]) for (const segment of [0, 1, 127, 128, 255]) for (const flags of [0, 1]) {
    const x = fixture(flags); x.control().wait14 = -1; x.part().complete2e = complete; x.part().segment2d = segment;
    x.dispatch.getActorBinding(x.actor).family1d88 = null;
    const met = (complete > 0 && complete < 128) || (flags === 1 && segment > 0 && segment < 128);
    if (met && flags === 0) rejects(x.run, 'zz_004c050_');
    else check(x.run() === (met ? 1 : 0), 'signed positive complete/segment');
  }
  {
    const x = fixture(); x.control().wait14 = -1; x.part().complete2e = 1; x.part().segment2d = NaN;
    check(x.run() === 1, 'positive completion short circuits segment');
  }
  for (const [wait, step, expected] of [[1, .25, .75], [.25, .5, 0], [-1, .5, 0], [-0, 0, 0], [1, -.5, 1.5]]) {
    const x = fixture(15); x.control().wait14 = wait!; x.header.timestep1dc8 = step!;
    check(x.run() === (expected! > 0 ? 0 : 1) && Object.is(x.control().wait14, expected), 'countdown priority, subtraction and +0 clamp');
    check(x.binding().elapsed08 === 2 && x.part().frame0c === 4, 'countdown never animates');
  }
  {
    const x = fixture(8); x.control().wait14 = .25;
    rejects(x.run, 'zz_004c050_'); check(x.control().wait14 === 0 && x.control().event1e === 0 && x.control().finished1a === 0, 'parser cut after countdown stores');
  }
  {
    const x = fixture(9); x.control().wait14 = Math.fround(3.4028234663852886e38); x.header.timestep1dc8 = -x.control().wait14;
    rejects(x.run, 'wait14 result'); check(x.control().wait14 > 0 && x.control().event1e === 0, 'overflow preserves prior event only');
  }
  for (const flags of [2, 4, 6, 7]) {
    const x = fixture(flags); x.control().wait14 = NaN; x.header.timestep1dc8 = NaN; x.binding().elapsed08 = NaN; x.part().frame0c = NaN;
    rejects(x.run, flags & 2 ? 'wait14: expected' : 'GQR5: quantized');
    check(x.control().event1e === 0, 'predicate admission preserves event prefix');
  }
  {
    const x = fixture(9); Object.defineProperty(x.control(), 'wait14', {writable: false});
    rejects(x.run, 'wait14: non-writable'); check(x.control().event1e === 0, 'countdown reached store');
  }
  {
    const x = fixture(); x.control().wait14 = 2;
    for (const [record, key] of [[x.control(), 'wait14'], [x.binding(), 'elapsed08'], [x.runtime.getCommand(x.command), 'flags01']] as const) Object.defineProperty(record, key, {writable: false});
    check(x.run() === 1, 'readonly predicate operands');
  }
  {
    const x = fixture(); Object.defineProperty(x.control(), 'event1e', {writable: false}); x.gate.blockedMask1d9a = 1;
    rejects(x.run, 'event1e: non-writable'); check(x.binding().elapsed08 === 2, 'event store precedes dispatch');
  }
  {
    const x = fixture(); x.control().current00 = Symbol('foreign'); rejects(x.run, 'unknown/non-owned command');
    x.control().current00 = null; check(x.run() === 1, 'null recovery');
    x.control(1).current00 = null; x.control().current00 = x.command; x.control(1).finished1a = 0;
    rejects(() => x.run(2), 'current00: owned');
    rejects(() => x.runtime.getCommand(Symbol()), 'unknown/non-owned');
    rejects(() => x.runtime.update(Symbol(), 1), 'unknown/non-owned');
    rejects(() => x.runtime.getPartBinding(x.actor, 4), 'index');
    rejects(() => x.run(-1), 'mask');
  }
  {
    const x = fixture(1, true); x.gate.blockedMask1d9a = 1;
    x.dispatchAdapter.updatePart = () => {throw Error('replaced method');};
    check(x.run() === 0 && x.calls() === 1, 'fixed method and original receiver');
    x.returns(Promise.resolve(1), undefined); rejects(x.run, 'synchronously');
    check(x.binding().elapsed08 === 3, 'invalid signed return preserves real dispatch');
  }
  {
    const x = fixture(1, true); x.returns(undefined, Promise.resolve()); rejects(x.run, 'synchronously');
    check(x.targets.getStreamPart(x.actor, 0).target08 === 6.5, 'invalid void return after real effects');
  }
  for (const mutate of ['update', 'command', 'bind'] as const) {
    const x = fixture(1, true); x.gate.blockedMask1d9a = 1;
    x.hooks.update = () => {try {
      if (mutate === 'update') x.run();
      else if (mutate === 'command') x.runtime.createCommand({flags01: 1});
      else x.runtime.bindActor(x.actor, x.gate, x.input);
    } catch { /* intentionally swallowed synthetic adapter fault */ }};
    rejects(x.run, 'reentry was caught'); check(x.binding().elapsed08 === 2.5, 'caught reentry preserves real prefix');
    delete x.hooks.update; check(x.run() === 0, 'reentry recovery');
  }
  {
    const x = fixture(1, true); x.control().wait14 = 2;
    x.hooks.layout = () => {x.control().current00 = x.runtime.createCommand({flags01: 0});};
    rejects(x.run, 'same-runtime reentry');
    x.hooks.layout = () => {x.runtime.getCommand(x.command).flags01 = 0;};
    rejects(x.run, 'zz_004c050_'); check(x.control().finished1a === 0, 'met reloads live command flags');
  }
  for (const value of [NaN, 128, -129, .5, null, {}]) {
    const x = fixture(1, true); x.gate.blockedMask1d9a = 1; x.returns(value, undefined);
    rejects(x.run, 'signed byte'); check(x.binding().elapsed08 === 2.5, 'invalid host return after effects');
  }
  {
    const x = fixture(1, true); x.control().wait14 = 2;
    Object.defineProperty(x.control(), 'finished1a', {writable: false});
    rejects(x.run, 'finished1a: non-writable'); check(x.control().event1e === 0 && x.calls() === 0, 'met readonly stop prefix');
  }
  {
    const x = fixture(9); x.control().wait14 = NaN; x.header.timestep1dc8 = NaN;
    rejects(x.run, 'wait14: expected'); x.control().wait14 = 1;
    rejects(x.run, 'timestep1dc8: expected'); check(x.control().wait14 === 1, 'chosen host countdown operand admission order');
  }
  {
    const x = fixture();
    const second = createSourceStreamWaitRuntime({mapping: x.mapping, feedback: x.feedback, dispatch: x.dispatch, targets: x.targets});
    const inputs = x.input.map(v => ({...v})); inputs[3]!.wait14 = NaN;
    rejects(() => second.bindActor(x.actor, x.gate, inputs), 'wait14: expected');
    rejects(() => second.getActorBinding(x.actor), 'unknown/non-owned');
    inputs[3]!.wait14 = 3;
    // These symbols are deliberately foreign to second. Binding must not force
    // command ownership for a later blocked/finished/null route.
    second.bindActor(x.actor, x.gate, inputs);
    second.getActorBinding(x.actor).blockedMask1d9a = 1;
    check(second.update(x.actor, 1) === 0, 'foreign command unused by blocked route');
    second.getActorBinding(x.actor).blockedMask1d9a = 0;
    rejects(() => second.update(x.actor, 1), 'unknown/non-owned command');
    rejects(() => second.bindActor(x.actor, x.gate, inputs), 'already bound');
  }

  for (const mask of [1, 2, 4, 8, 10, 15]) {
    const x = fixture(); check(x.run(mask) === 0, 'selected unmet return');
    for (let i = 0; i < 4; i++) {
      const selected = Boolean(mask & (1 << i)), target = x.targets.getStreamPart(x.actor, i);
      check(x.binding(i).elapsed08 === (selected ? 2.5 : 2) && x.part(i).frame0c === (selected ? 4.5 : 4) &&
        target.previous0c === (selected ? 10 : 99) && target.target08 === (selected ? 6.5 : 10),
      'mask selects actual dispatch/target effects including part3, preserves others');
    }
  }
  {
    const x = fixture(); x.control().current00 = null; x.gate.blockedMask1d9a = NaN;
    for (let i = 0; i < 4; i++) {x.control(i).wait14 = NaN; x.binding(i).linked36 = NaN;}
    x.control(1).current00 = 123 as unknown as symbol;
    check(x.run(15) === 1, 'null fast path ignores blocked/wait/linked/other command fields');
    const y = fixture(); y.control().current00 = null; y.gate.activeMask579 = NaN;
    rejects(y.run, 'activeMask579');
    for (let i = 0; i < 4; i++) check(y.control(i).finished1a === 0, 'active admission precedes null writes');
  }
  {
    const x = fixture(1, true); x.control(0).finished1a = 1; x.control(2).wait14 = 2;
    const order: number[] = [];
    x.hooks.layout = () => {
      // These observations occur at real predicate/finished part resolution.
      if (x.control(3).event1e === 0) order.push(3);
      else if (x.control(2).event1e === 0) order.push(2);
      else if (x.control(1).event1e === 0) order.push(1);
      else order.push(0);
    };
    x.hooks.target = () => {
      if (x.control(3).event1e === 0) check(x.control(2).finished1a === 1, 'met part precedes later target');
      else check(x.control(2).event1e === 9, 'unmet target precedes later event clear');
    };
    check(x.run(15) === 1 && order.join(',') === '0,1,2,3' && x.targetCalls() === 2,
      'mixed finished/unmet/met aggregation and ascending execution');
    check(x.binding(0).elapsed08 === 2 && x.binding(1).elapsed08 === 2.5 &&
      x.binding(2).elapsed08 === 2 && x.binding(3).elapsed08 === 2.5, 'mixed actual animation selection');
  }
  for (const [wait, step, expected] of [[16777216, -1, 16777216], [2 ** -148, 2 ** -149, 2 ** -149]]) {
    const x = fixture(9); x.control().wait14 = wait!; x.header.timestep1dc8 = step!;
    check(x.run() === 0 && Object.is(x.control().wait14, expected), 'RN00 subtraction tie and NI0 subnormal store');
  }
  {
    const x = fixture(1, true), next = x.runtime.createCommand({flags01: 0}); x.control().wait14 = 2;
    x.hooks.layout = () => {x.control().current00 = next;};
    rejects(x.run, 'zz_004c050_');
    check(x.control().current00 === next && x.control().finished1a === 0, 'met rereads current pointer, not cached command');
  }
  {
    const x = fixture(1, true);
    x.mappingAdapter.getLayout = () => {throw Error('replaced layout');};
    x.dispatchAdapter.getPartBinding = () => {throw Error('replaced dispatch getter');};
    x.targetAdapter.continueUnmetNonCountdownWait = () => {throw Error('replaced target');};
    check(x.run() === 0 && x.targetCalls() === 1 && x.binding().elapsed08 === 2.5, 'fixed layout/dispatch getter/target methods');
    x.feedbackAdapter.getPart = () => {throw Error('replaced feedback getter');};
    x.control().wait14 = -1; x.part().complete2e = 1;
    check(x.run() === 1, 'fixed feedback getter with original receiver');
  }

  for (const wait of [0, -0]) for (const elapsed of [0, -0]) {
    const x = fixture(); x.control().wait14 = wait; x.binding().elapsed08 = elapsed;
    x.part().complete2e = NaN; x.part().segment2d = NaN;
    x.part().frame0c = NaN; x.part().duration24 = NaN;
    check(x.run() === 1 && x.control().finished1a === 1 &&
      Object.is(x.control().wait14, wait) && Object.is(x.binding().elapsed08, elapsed),
    'ordinary signed-zero waits use elapsed threshold and leave unused feedback unread');
  }

  // Quantized paths use an explicitly selected startup profile, never a live
  // register assertion. All observations remain on the actual shared runtimes.
  for (const profile of [undefined, NaN, 0, 0x00070007]) for (const wait of [3, 0, -0]) {
    const x = fixture(7, false, profile); x.control().wait14 = wait;
    x.part().duration24 = NaN; x.header.timestep1dc8 = NaN; x.binding().elapsed08 = NaN;
    check(x.run() === 1 && Object.is(x.control().wait14, wait), 'bit2 beats bit4 and nonnegative waits skip profile/duration');
  }
  for (const flags of [3, 5]) for (const profile of [undefined, 0, NaN, 0x00070006, 0x100070007]) {
    const x = fixture(flags, true, profile); x.control().wait14 = -1;
    x.hooks.layout = () => {throw Error('unexpected layout before profile');};
    x.part().duration24 = NaN; x.part().frame0c = NaN;
    rejects(x.run, 'GQR5: quantized duration load requires explicit startup host profile');
    check(x.control().event1e === 0 && x.control().finished1a === 0 && x.control().wait14 === -1,
      'bad profile refuses before resolution with event-only prefix');
  }
  for (const [duration, wait, frame] of [[9, -5, 4], [9, -10, 0], [-32768, -1, 0],
    [32767, -1, 32766], [1, -(2 ** -25), 1], [1, -3 * 2 ** -25, 1 - 2 ** -23], [0, -1, 0], [-0, -1, -0], [2, -2, -0]]) {
    const x = fixture(3, false, 0x00070007); x.control().wait14 = wait!;
    x.part().duration24 = duration!; x.part().frame0c = frame!;
    for (const [record, key] of [[x.control(), 'wait14'], [x.part(), 'duration24'], [x.part(), 'frame0c']] as const)
      Object.defineProperty(record, key, {writable: false});
    check(x.run() === 1 && Object.is(x.control().wait14, wait) && Object.is(x.part().duration24, duration) &&
      Object.is(x.part().frame0c, frame), 'relative signed duration, clamp, tie, readonly inputs');
  }
  for (const flags of [3, 5]) for (const duration of [NaN, Infinity, .5, -32769, 32768]) {
    const x = fixture(flags, false, 0x00070007); x.control().wait14 = -1;
    x.part().duration24 = duration; x.part().frame0c = NaN;
    rejects(x.run, 'duration24: expected signed16 integer');
    check(x.control().event1e === 0 && x.control().finished1a === 0 && x.binding().elapsed08 === 2,
      'duration admission precedes frame and leaves event-only prefix');
  }
  for (const flags of [3, 5]) {
    const x = fixture(flags, false, 0x00070007); x.control().wait14 = -1; x.part().frame0c = NaN;
    rejects(x.run, 'frame0c: expected finite source float32');
  }
  for (const duration of [0, -0]) {
    const x = fixture(5, false, 0x00070007); x.part().duration24 = duration;
    x.part().frame0c = NaN; x.control().wait14 = NaN;
    rejects(x.run, 'frame0c: expected');
    x.part().frame0c = 0; rejects(x.run, 'duration24: zero percentage divisor');
    check(x.control().event1e === 0 && x.part().frame0c === 0 && Object.is(x.part().duration24, duration),
      'percentage reads frame before zero refusal, wait remains lazy, no operand writes');
  }
  for (const [duration, frame, wait] of [[32767, 32767, 100], [-32768, -32768, 100], [-2, 4, -200],
    [2, 2 ** -149, 0], [-2, 2 ** -149, -0], [1, 2 ** -149, 100 * 2 ** -149],
    [-1, 2 ** -149, -100 * 2 ** -149]]) {
    const x = fixture(5, false, 0x00070007); x.part().duration24 = duration!;
    x.part().frame0c = frame!; x.control().wait14 = wait!;
    for (const [record, key] of [[x.control(), 'wait14'], [x.part(), 'duration24'], [x.part(), 'frame0c']] as const)
      Object.defineProperty(record, key, {writable: false});
    check(x.run() === 1 && Object.is(x.part().frame0c, frame) && Object.is(x.control().wait14, wait),
      'percentage signed limits, negative divisor, underflow signed zero/subnormal, readonly');
  }
  {
    const x = fixture(5, false, 0x00070007); x.part().duration24 = 1;
    x.part().frame0c = Math.fround(3.4028234663852886e38); x.control().wait14 = NaN;
    rejects(x.run, 'wait14: expected'); x.control().wait14 = 1;
    rejects(x.run, 'percentage result: expected');
    check(x.control().wait14 === 1 && x.control().finished1a === 0 && x.control().event1e === 0 && x.binding().elapsed08 === 2,
      'percentage overflow after wait admission, preserving event-only prefix');
  }
  for (const flags of [2, 4]) {
    const x = fixture(flags, false, 0x00070007); x.control().wait14 = 1;
    rejects(x.run, 'zz_004c050_');
    check(x.control().wait14 === 1 && x.control().finished1a === 0 && x.part().frame0c === 4,
      'relative/percentage met parser boundary leaves predicate operands untouched');
  }
  for (const flags of [3, 5]) {
    const x = fixture(flags, true, 0x00070007); x.control().wait14 = 200;
    check(x.run() === 0 && x.targetCalls() === 1 && x.binding().elapsed08 === 2.5 && x.part().frame0c === 4.5 &&
      x.targets.getStreamPart(x.actor, 0).previous0c === 10 && x.targets.getStreamPart(x.actor, 0).target08 === 6.5 &&
      x.control().wait14 === 200, 'unmet relative/percentage uses actual shared dispatch and target continuation');
    const y = fixture(flags, true, 0x00070007); y.control().wait14 = 1;
    y.hooks.part = () => {y.runtime.getCommand(y.command).flags01 = 0;};
    rejects(y.run, 'zz_004c050_'); check(y.control().finished1a === 0, 'met relative/percentage reloads flags');
  }

  {
    const x = fixture(5, false, 0x00070007); x.part().frame0c = 1; x.part().duration24 = 3;
    x.control().wait14 = 33.333335876464844; // 0x42055556, independently checked by exact rational arithmetic.
    check(x.run() === 1, 'percentage rounds division then multiplication, not combined or multiplication first');
  }
  {
    const x = fixture(3, true, 0x00070007); x.control().wait14 = -1;
    x.options.gqr5 = 0;
    check(x.run() === 0 && x.targetCalls() === 1 && x.part().frame0c === 4.5 && x.control().wait14 === -1,
      'selected profile is immutable and negative unmet relative invokes real target');
    const y = fixture(5); y.options.gqr5 = 0x00070007;
    rejects(y.run, 'GQR5: quantized');
  }

  for (const [flags, duration, wait, frame] of [[3, 9, -10, -.5], [5, -2, 0, 4]]) {
    const x = fixture(flags!, true, 0x00070007); x.part().duration24 = duration!;
    x.control().wait14 = wait!; x.part().frame0c = frame!;
    x.dispatch.getActorBinding(x.actor).family1d88 = null;
    check(x.run() === 0 && x.targetCalls() === 1 && x.control().finished1a === 0 &&
      x.targets.getStreamPart(x.actor, 0).previous0c === 10 &&
      x.targets.getStreamPart(x.actor, 0).target08 === frame! + 2 &&
      Object.is(x.part().frame0c, frame) && Object.is(x.part().duration24, duration) &&
      Object.is(x.control().wait14, wait),
    'relative clamp and signed percentage divisor discriminate unmet through actual gated target continuation');
  }

  // Byte-backed opcode0 parser: actual target/dispatch runtimes, no handler stubs.
  {
    const x = fixture(), backing = new Uint8Array([99, 98, 0, 1, 0x12, 0x34, 97]);
    const view = backing.subarray(2, 6), base = x.runtime.createStream(view); backing.fill(0);
    x.runtime.parseWaitRecord(x.actor, 1, base);
    check(x.control().wait14 === 0x1234 && x.control().current00 === base &&
      x.runtime.cursorOffset(base, x.control().next04!) === 4, 'copies only the supplied nonzero-offset byte view');
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, x.control().next04!), 'out of bounds');
  }
  {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([0, 0, 0, 17]));
    Object.defineProperty(x.control(2), 'next04', {writable: false});
    rejects(() => x.runtime.parseWaitRecord(x.actor, 15, base), 'next04: non-writable');
    check(x.targetCalls() === 4 && [0, 1].every(i => x.control(i).current00 === base &&
      x.control(i).next04 === x.runtime.cursorAt(base, 4) && x.control(i).wait14 === 17 && x.control(i).finished1a === 0) &&
      x.control(2).current00 === base && x.control(2).next04 === null && x.control(2).wait14 === 3 &&
      x.control(3).current00 === x.command, 'later installation failure preserves earlier complete installations and its own current store');
  }
  for (const value of [-32768, -1, 0, 1, 32767]) {
    const x = fixture(1, true), bytes = new Uint8Array([0, 255, (value >> 8) & 255, value & 255]);
    const base = x.runtime.createStream(bytes); bytes.fill(7);
    x.gate.activeMask579 = 0; x.gate.blockedMask1d9a = 255;
    x.control().finished1a = 255;
    x.runtime.parseWaitRecord(x.actor, 1, base);
    check(x.control().wait14 === value && x.control().current00 === base && x.control().finished1a === 0 &&
      x.control().event1e === 9 && x.targetCalls() === 1 && x.binding().elapsed08 === 2.5,
    'opcode0 signed BE16, copied bytes, ignores actor/finished gates, preserves event, actual fallback');
    check(x.runtime.cursorAt(base, 0) === base && x.runtime.cursorAt(base, 4) === x.control().next04 &&
      x.runtime.cursorOffset(base, x.control().next04!) === 4, 'interned same-backed end pointer');
    rejects(() => x.runtime.getCommand(base), 'unknown/non-owned command');
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, x.control().next04!), 'out of bounds');
  }
  for (const length of [1, 2, 3]) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array(length));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 3, base), 'out of bounds');
    check(x.targetCalls() === 2 && x.control().current00 === base && x.runtime.cursorOffset(base, x.control().next04!) === 4 &&
      x.control().wait14 === 3 && x.control(1).current00 === x.command && x.control(1).next04 === null,
    'truncated record commits all fallbacks then first current/next only');
  }
  for (const mask of [0, 0x10, 0xfffffff0]) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([0]));
    x.runtime.parseWaitRecord(x.actor, mask, base);
    check(x.targetCalls() === 0 && x.control().current00 === x.command, 'zero/high-only mask does not load wait or flags');
    rejects(() => x.runtime.parseWaitRecord(x.actor, mask, x.runtime.createStream(new Uint8Array())), 'out of bounds');
  }
  for (const opcode of [4, 8, 255]) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([opcode]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 15, base), 'unsupported zz_004c050_ opcode');
    check(x.targetCalls() === 0 && x.control().current00 === x.command, 'nonzero opcode refuses before fallback');
  }
  for (const key of ['current00', 'next04', 'wait14', 'finished1a'] as const) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([0, 255, 0x80, 0]));
    x.control().finished1a = 9;
    Object.defineProperty(x.control(), key, {writable: false});
    rejects(() => x.runtime.parseWaitRecord(x.actor, 15, base), `${key}: non-writable`);
    check(x.targetCalls() === 4 && x.control(1).current00 === x.command && x.control().finished1a === 9 &&
      x.control().current00 === (key === 'current00' ? x.command : base) &&
      x.control().next04 === (key === 'current00' || key === 'next04' ? null : x.runtime.cursorAt(base, 4)) &&
      x.control().wait14 === (key === 'finished1a' ? -32768 : 3), 'ordered readonly parser store prefix after all fallbacks');
  }
  {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([0, 0, 0, 7]));
    const order: number[] = [];
    x.hooks.target = () => {
      order.push(x.targetCalls());
      for (let i = 0; i < 4; i++) check(x.control(i).current00 === x.command, 'all fallback calls precede any control store');
    };
    x.targetAdapter.continueUnmetNonCountdownWait = () => {throw Error('replacement must not run');};
    x.runtime.parseWaitRecord(x.actor, 0xffffffff, base);
    check(order.join() === '1,2,3,4' && [0, 1, 2, 3].every(i => x.control(i).wait14 === 7), 'captured target method, ascending low-four mask');
  }
  {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([0, 0, 0, 7]));
    x.returns(undefined, Promise.resolve());
    rejects(() => x.runtime.parseWaitRecord(x.actor, 3, base), 'synchronously');
    check(x.targetCalls() === 1 && x.binding().elapsed08 === 2.5 && x.control().current00 === x.command,
      'synchronous target contract retains first real fallback but installs nothing');
  }
  for (const operation of ['createStream', 'cursorAt', 'parseWaitRecord'] as const) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([0, 0, 0, 7]));
    x.hooks.target = () => {
      try {
        if (operation === 'createStream') x.runtime.createStream(new Uint8Array());
        else if (operation === 'cursorAt') x.runtime.cursorAt(base, 4);
        else x.runtime.parseWaitRecord(x.actor, 0, base);
      } catch { /* A caught mutation still poisons the outer operation. */ }
    };
    rejects(() => x.runtime.parseWaitRecord(x.actor, 3, base), 'reentry was caught');
    check(x.targetCalls() === 1 && x.binding().elapsed08 === 2.5 && x.control().current00 === x.command, 'parser reentry poison prefix');
    delete x.hooks.target;
    x.runtime.parseWaitRecord(x.actor, 1, base);
    check(x.control().wait14 === 7, 'guard released after failed parse');
  }
  {
    const x = fixture(), y = fixture(), base = x.runtime.createStream(new Uint8Array([0, 0, 0, 1]));
    const other = x.runtime.createStream(new Uint8Array([0]));
    rejects(() => x.runtime.cursorOffset(other, base), 'does not belong');
    rejects(() => y.runtime.cursorAt(base, 0), 'owned stream base');
    rejects(() => y.runtime.parseWaitRecord(y.actor, 0, base), 'owned byte cursor');
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, x.command), 'owned byte cursor');
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, 4 as unknown as symbol), 'owned byte cursor');
    for (const offset of [-1, .5, 0x100000000, NaN]) rejects(() => x.runtime.cursorAt(base, offset), 'cursor offset');
    const end = x.runtime.cursorAt(base, 0xffffffff);
    check(x.runtime.cursorOffset(base, end) === 0xffffffff, 'uint32 beyond-end cursor is representable');
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, end), 'out of bounds');
    rejects(() => x.runtime.createStream(new Uint8Array(16 * 1024 * 1024 + 1)), '16MiB');
    rejects(() => x.runtime.createStream(new Uint8Array(new SharedArrayBuffer(4))), 'non-shared');
    rejects(() => x.runtime.createStream(new Proxy(new Uint8Array(4), {})), 'non-shared');
    const hostile = new Uint8Array([0, 0, 0, 12]);
    for (const key of ['length', 'buffer', Symbol.iterator]) Object.defineProperty(hostile, key, {get() {throw Error('caller getter ran');}});
    x.runtime.parseWaitRecord(x.actor, 1, x.runtime.createStream(hostile));
    check(x.control().wait14 === 12, 'native typed-array copy never invokes overridden accessors or iterator');
  }
  for (const flags of [0, 8]) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([0, flags, 0, 0, 0, 1, 0, 1]));
    x.control().current00 = base; x.control().next04 = x.runtime.cursorAt(base, 4); x.control().wait14 = flags === 8 ? .25 : 2;
    check(x.run() === 0 && x.targetCalls() === 1 && x.binding().elapsed08 === 2.5 &&
      x.control().current00 === x.runtime.cursorAt(base, 4) && x.control().next04 === x.runtime.cursorAt(base, 8) &&
      x.control().wait14 === 1 && x.control().finished1a === 0 && x.control().event1e === 0,
    'met byte-backed ordinary/countdown non-stop parses exactly once with actual fallback and no immediate reevaluation');
    check(x.run() === 1 && x.targetCalls() === 1 && x.control().finished1a === 1, 'next update reads installed stop flags from bytes');
  }
  {
    const x = fixture(8, true), base = x.runtime.createStream(new Uint8Array([4]));
    x.control().wait14 = .25; x.control().next04 = base;
    rejects(x.run, 'unsupported zz_004c050_ opcode');
    check(x.control().wait14 === 0 && x.control().event1e === 0 && x.targetCalls() === 0, 'unsupported continuation preserves countdown/event prefix');
  }

  {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([0, 0, 0, 7]));
    Object.defineProperty(x.targets.getStreamPart(x.actor, 1), 'previous0c', {writable: false});
    rejects(() => x.runtime.parseWaitRecord(x.actor, 15, base), 'previous0c: non-writable');
    check(x.targetCalls() === 2 && x.binding().elapsed08 === 2.5 && x.binding(1).elapsed08 === 2 &&
      [0, 1, 2, 3].every(i => x.control(i).current00 === x.command),
    'real second fallback fault retains first target effects but no control installs');
  }
  {
    const x = fixture(), base = x.runtime.createStream(new Uint8Array([0]));
    x.control().current00 = base;
    rejects(x.run, 'out of bounds');
    check(x.control().event1e === 0 && x.control().wait14 === 3, 'update lazily reads actual byte flags after event store');
  }

  // Opcode0x10 operates on actual target/feedback records, before terminal fallback.
  for (const mask of [0, 1, 2, 4, 8, 5, 15, 0xfffffff0, 0xffffffff]) {
    const x = fixture(1, true), order: number[] = [];
    x.dispatch.getActorBinding(x.actor).family1d88 = null;
    x.hooks.targetGet = i => {order.push(i); check(x.control(i).current00 === x.command, 'handler does not install controls');};
    const base = x.runtime.createStream(new Uint8Array([16, 255, 1, 255, 16, 128, 2, 2, 16, 99, 2, 3, 0, 9, 0xff, 0xff]));
    x.runtime.parseWaitRecord(x.actor, mask, base);
    check(order.join() === [0, 1, 2, 3].filter(i => mask & (1 << i)).join(), 'ascending selected handler indexes');
    for (let i = 0; i < 4; i++) {
      const selected = !!(mask & (1 << i)), target = x.targets.getStreamPart(x.actor, i);
      check(target.accumulator10 === (selected ? 255 : 2) && x.part(i).mirror30 === 0 &&
        target.target08 === (selected ? 259 : 10) && x.control(i).wait14 === (selected ? -1 : 3) &&
        x.control(i).current00 === (selected ? x.runtime.cursorAt(base, 12) : x.command) &&
        x.control(i).next04 === (selected ? x.runtime.cursorAt(base, 16) : null), 'mixed chain shared effects and terminal offsets');
    }
    check(x.targetCalls() === order.length, 'fallback exactly once per selected part');
  }
  for (let operand = 0; operand <= 255; operand++) {
    const x = fixture(1, false, 0); x.dispatch.getActorBinding(x.actor).family1d88 = null;
    const base = x.runtime.createStream(new Uint8Array([16, 255, 1, operand, 0, 1, 0, 1]));
    x.runtime.parseWaitRecord(x.actor, 1, base);
    check(Object.is(x.targets.getStreamPart(x.actor, 0).accumulator10, operand), 'all unsigned u8 conversions exact, including positive zero and high bit');
  }
  for (const operand of [0, 1, 2, 3, 4, 127, 128, 255]) for (const before of [0, 1, 128, 255, NaN]) {
    const x = fixture(1, true); x.dispatch.getActorBinding(x.actor).family1d88 = null;
    x.part().mirror30 = before;
    const base = x.runtime.createStream(new Uint8Array([16, 0, 2, operand, 0, 1, 0, 1]));
    if (operand === 3 && Number.isNaN(before)) {
      rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'mirror30: unsigned');
      check(x.targetCalls() === 0 && x.control().current00 === x.command, 'XOR validation before fallback');
    } else {
      x.runtime.parseWaitRecord(x.actor, 1, base);
      const expected = operand === 1 ? 0 : operand === 2 ? 1 : operand === 3 ? before ^ 1 : before;
      check(Object.is(x.part().mirror30, expected), 'mirror operand behavior including high-bit XOR and stale overwrite');
    }
  }
  for (const operand of [0, 4, 255]) {
    const x = fixture(1, true); x.dispatch.getActorBinding(x.actor).family1d88 = null;
    x.hooks.layout = () => {throw Error('ignored mirror must not resolve layout');};
    x.hooks.part = () => {throw Error('ignored mirror must not resolve feedback');};
    Object.defineProperty(x.part(), 'mirror30', {value: NaN, writable: false});
    const base = x.runtime.createStream(new Uint8Array([16, 0, 2, operand, 0, 1, 0, 1]));
    x.runtime.parseWaitRecord(x.actor, 1, base);
    check(x.targetCalls() === 1 && Number.isNaN(x.part().mirror30), 'ignored mirror does not touch malformed readonly state');
  }
  for (const mode of [0, 3, 4, 255]) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([16, 0, mode]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, base), 'unsupported opcode0x10 mode');
    check(x.targetCalls() === 0 && x.control().current00 === x.command, 'unsupported mode before fallback even with no selection');
  }
  for (const mode of [1, 2]) for (const mask of [0, 0xfffffff0, 1]) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([16, 255, mode]));
    // For empty low mask the missing payload is skipped, and next opcode faults instead.
    rejects(() => x.runtime.parseWaitRecord(x.actor, mask, base), 'out of bounds');
    check(x.targetCalls() === 0 && x.control().current00 === x.command, 'truncated chain installs nothing');
    const valid = x.runtime.createStream(new Uint8Array([16, 255, mode, 255, 0]));
    if (mask === 1) rejects(() => x.runtime.parseWaitRecord(x.actor, mask, valid), 'out of bounds');
    else x.runtime.parseWaitRecord(x.actor, mask, valid);
  }
  for (const bytes of [[16], [16, 0], [16, 0, 1], [16, 0, 1, 7], [16, 0, 1, 7, 4], [16, 0, 1, 7, 16, 0, 0]]) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array(bytes));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), bytes.length <= 4 ? 'out of bounds' : 'unsupported');
    check(x.targets.getStreamPart(x.actor, 0).accumulator10 === (bytes.length >= 4 ? 7 : 2) &&
      x.targetCalls() === 0 && x.control().current00 === x.command, 'truncation/unsupported suffix retains handler prefix only');
  }
  for (const mode of [1, 2]) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([16, 0, mode, 2, 0, 1, 0, 1]));
    const record = mode === 1 ? x.targets.getStreamPart(x.actor, 2) : x.part(2), key = mode === 1 ? 'accumulator10' : 'mirror30';
    if (mode === 1) for (let i = 0; i < 4; i++) x.targets.getStreamPart(x.actor, i).accumulator10 = 99;
    Object.defineProperty(record, key, {writable: false});
    rejects(() => x.runtime.parseWaitRecord(x.actor, 15, base), key + ': non-writable');
    for (let i = 0; i < 4; i++) check((mode === 1 ? x.targets.getStreamPart(x.actor, i).accumulator10 : x.part(i).mirror30) ===
      (i < 2 ? (mode === 1 ? 2 : 1) : (mode === 1 ? 99 : 0)), 'ascending readonly handler prefix');
    check(x.targetCalls() === 0 && x.control().current00 === x.command, 'handler store fault precedes all fallback');
  }
  {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([16, 0, 1, 17, 16, 0, 2, 2, 0, 1, 0, 1]));
    Object.defineProperty(x.part(), 'mirror30', {writable: false});
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'mirror30: non-writable');
    check(x.targets.getStreamPart(x.actor, 0).accumulator10 === 17 && x.targetCalls() === 0, 'cross-command readonly prefix');
  }
  for (const maxCommands of [0, -1, 1.5, NaN, Infinity, Number.MAX_SAFE_INTEGER + 1])
    rejects(() => fixture(1, false, undefined, maxCommands), 'maxCommands: positive safe integer');
  {
    const x = fixture(1, true, undefined, 1); x.options.maxCommands = 99;
    const base = x.runtime.createStream(new Uint8Array([16, 0, 1, 7, 16, 0, 1, 9, 0, 1, 0, 1]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'budget exceeded');
    check(x.targets.getStreamPart(x.actor, 0).accumulator10 === 7 && x.targetCalls() === 0 && x.control().current00 === x.command, 'immutable budget refuses before second effect');
    x.runtime.parseWaitRecord(x.actor, 1, x.runtime.cursorAt(base, 4));
    check(x.control().wait14 === 1, 'terminal opcode consumes no budget and each parse resets budget');
  }
  {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([16, 255, 1, 17, 0, 1, 0, 1]));
    x.targetAdapter.getStreamPart = () => {throw Error('replacement getter');};
    x.runtime.parseWaitRecord(x.actor, 1, base);
    check(x.targets.getStreamPart(x.actor, 0).accumulator10 === 17, 'captured target getter and real receiver');
  }
  for (const result of [null, 1, Promise.resolve(), {}, Object.freeze({accumulator10: 2})]) {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([16, 0, 1, 17, 0, 1, 0, 1]));
    x.getReturns(result);
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'accumulator10:');
    check(x.targets.getStreamPart(x.actor, 0).accumulator10 === 2 && x.targetCalls() === 0, 'target getter return-shape failure without invented state');
  }
  {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([16, 0, 1, 17, 0, 1, 0, 1]));
    x.hooks.targetGet = () => {try {x.runtime.parseWaitRecord(x.actor, 0, base);} catch { /* Poison remains. */ }};
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'reentry was caught');
    check(x.targets.getStreamPart(x.actor, 0).accumulator10 === 2 && x.targetCalls() === 0, 'caught target getter reentry refuses before write');
  }
  {
    const x = fixture(8, true), base = x.runtime.createStream(new Uint8Array([16, 255, 1, 128, 16, 255, 2, 1, 0, 1, 0, 0]));
    x.control().wait14 = .25; x.control().next04 = base;
    check(x.run() === 0 && x.control().current00 === x.runtime.cursorAt(base, 8) && x.control().wait14 === 0 &&
      x.control().finished1a === 0 && x.targets.getStreamPart(x.actor, 0).target08 === 132.5 && x.targetCalls() === 1,
      'actual update continuation handles chain once without evaluating terminal wait');
    check(x.run() === 1 && x.targetCalls() === 1, 'next update uses terminal stop flags');
  }

  {
    const x = fixture(1, true), base = x.runtime.createStream(new Uint8Array([16, 0, 2, 2, 0, 1, 0, 1]));
    x.header.boundary1d91 = 1;
    x.mapping.getPartBinding(x.parts[0]![0]!).descriptor00 = Symbol('presence');
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'mirrored joint mapping is unsupported');
    check(x.part().mirror30 === 1 && x.part().frame0c === 4.5 && x.binding().elapsed08 === 2.5 &&
      x.targets.getStreamPart(x.actor, 0).previous0c === 10 && x.targets.getStreamPart(x.actor, 0).target08 === 10 &&
      x.targetCalls() === 1 && x.control().current00 === x.command, 'mirror write reaches real mapping refusal naturally during fallback');
  }
  {
    const x = fixture(1, true), bytes = new Uint8Array(4097 * 4 + 4);
    for (let i = 0; i < 4097; i++) bytes.set([16, 255, 1, i & 255], i * 4);
    const base = x.runtime.createStream(bytes);
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'budget exceeded');
    check(x.targets.getStreamPart(x.actor, 0).accumulator10 === 255 && x.targetCalls() === 0 &&
      x.control().current00 === x.command, 'default host budget admits exactly 4096 handlers');
  }

  // Opcode01 fixtures use the real setup dispatcher gates, never a synthetic
  // successful setup implementation. Hooks observe only after that call returns.
  const setupFixture = () => {
    const x = fixture(1, true);
    x.dispatch.getActorBinding(x.actor).family1d88 = null;
    x.gate.marker71d = 19;
    return x;
  };
  const setupBytes = [1, 7, 8, 9, 10, 0, 0xff, 0xff];
  for (const mask of [0, 0xfffffff0, 1, 2, 4, 8, 15, 0xffffffff]) {
    const x = setupFixture(), seen: number[] = [];
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, 16, 0, 1, 12, 0, 1, 0xff, 0xfe]));
    x.hooks.setup = (i, request) => {
      seen.push(i);
      check(request.frame === 4.5 && request.group === 7 && request.action === 8 && request.mode === 9 && request.transition === 10,
        'opcode01 original defaults and exact signed conversion');
    };
    x.runtime.parseWaitRecord(x.actor, mask, base);
    check(seen.join(',') === [0, 1, 2, 3].filter(i => !!(mask & (1 << i))).join(','), 'ascending low-four setup calls');
    check(x.targetCalls() === 0 && x.gate.marker71d === ((mask & 2) ? 0 : 19), 'completed opcode01 suppresses fallback even after opcode10, clears marker');
    for (let i = 0; i < 4; i++) {
      const selected = !!(mask & (1 << i)), t = x.targets.getStreamPart(x.actor, i);
      check(t.previous0c === (selected ? 10 : 99) && t.target08 === (selected ? 6 : 10) && t.accumulator10 === (selected ? 12 : 2) &&
        x.control(i).status1d === (selected ? 1 : 0) && x.control(i).wait14 === (selected ? -2 : 3), 'selected exact stores and terminal installation');
    }
  }
  for (const gate of ['shared', 'freeze'] as const) {
    const x = fixture(1, true), g = x.dispatch.getActorBinding(x.actor);
    if (gate === 'shared') g.shared1d8c = null;
    else {g.marker578 = 1; g.marker1db3 = 1;}
    x.gate.blockedMask1d9a = 255;
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 3]));
    x.runtime.parseWaitRecord(x.actor, 2, base);
    check(x.control(1).status1d === 1 && x.targets.getStreamPart(x.actor, 1).target08 === 6 && x.targetCalls() === 0,
      'real shared-null/part1 marker gate returns before blocked read and allows handler stores');
  }
  for (const blocked of [0, 1]) {
    const x = fixture(1, true); x.gate.blockedMask1d9a = blocked;
    x.control().status1d = 255;
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 3]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 3, base), blocked ? 'unsupported 4a41c' : 'unsupported setup table/4871c');
    const t = x.targets.getStreamPart(x.actor, 0);
    check(t.previous0c === 10 && t.accumulator10 === 11 && t.target08 === 10 && x.control().status1d === 255 &&
      x.control().current00 === x.command && x.targets.getStreamPart(x.actor, 1).previous0c === 99, 'real refusal retains exact earlier stores only');
  }
  {
    const x = setupFixture(), frames: number[] = [];
    x.part(0).frame0c = -4; x.part(1).frame0c = 8; x.part(2).frame0c = 20;
    x.hooks.setup = (_i, request) => {frames.push(request.frame);};
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, ...setupBytes, 0, 1, 0, 0]));
    x.runtime.parseWaitRecord(x.actor, 7, base);
    check(frames.join(',') === '-3.5,8.5,8.5,-3.5,8.5,8.5', 'mutable negative frame retried, nonnegative reused, each opcode resets context');
    check(x.targets.getStreamPart(x.actor, 2).accumulator10 === 11, 'second opcode accumulates actual signed duration after first status store');
  }
  for (const frame of [-1, -0, 0, 3.25]) for (const override of [-1, -2147483648, 0xffffffff, 0x80000000, 0, 255, 0x7fffffff]) {
    const x = setupFixture(); const b = [...setupBytes]; b[6] = 0x80; b[7] = 0;
    x.hooks.setup = (_i, request) => check(Object.is(request.frame, frame < 0 ? 4.5 : frame) &&
      request.transition === ((override | 0) < 0 ? 10 : override) && request.mode === ((override | 0) < 0 ? 9 : override),
      'signed32/uint32 defaults, explicit overrides and negative zero');
    const base = x.runtime.createStream(new Uint8Array([...b, 0, 1, 0, 0]));
    x.runtime.parseWaitRecord(x.actor, 1, base, frame, override, override);
  }
  {
    const x = setupFixture(), b = [...setupBytes]; b[6] = 0x7f; b[7] = 0xff;
    x.header.timestep1dc8 = NaN;
    x.hooks.setup = (_i, request) => check(request.frame === 32767, 'positive signed halfword frame is exact, timestep unused');
    const base = x.runtime.createStream(new Uint8Array([...b, 0, 1, 0, 0])); x.runtime.parseWaitRecord(x.actor, 1, base);
  }
  for (const mask of [0, 0xfffffff0]) {
    const x = setupFixture(); x.header.timestep1dc8 = NaN; x.gate.blockedMask1d9a = NaN;
    const base = x.runtime.createStream(new Uint8Array([1, 0, 0, 0, 0, 0, 0, 0, 0]));
    x.runtime.parseWaitRecord(x.actor, mask, base, 1, 1, 1);
    check(x.targetCalls() === 0 && x.control().current00 === x.command, 'empty selection skips all part operands and terminal wait bytes');
  }
  for (const value of [NaN, Infinity, 0.1]) {
    const x = setupFixture(), base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 0]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, base, value), 'startFrame');
    const terminal = x.runtime.createStream(new Uint8Array([0]));
    x.runtime.parseWaitRecord(x.actor, 0, terminal, value, NaN, NaN);
  }
  for (const value of [NaN, Infinity, 1.5, -2147483649, 0x100000000]) {
    const x = setupFixture(), base = x.runtime.createStream(new Uint8Array([...setupBytes, 0]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, base, 0, value, 0), 'transition');
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, base, 0, 0, value), 'mode');
  }
  {
    const x = setupFixture(), b = [...setupBytes]; b[5] = 255;
    const base = x.runtime.createStream(new Uint8Array([...b, 0, 1, 0, 0]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 3, base), 'unverified 8043712c');
    check(x.gate.marker71d === 0 && x.control(1).status1d === 1 && x.targets.getStreamPart(x.actor, 1).target08 === 6 &&
      x.control().current00 === x.command && x.targetCalls() === 0, 'byte5 refusal follows all part stores and marker clear, no installation');
  }
  {
    const x = setupFixture(), t = x.targets.getStreamPart(x.actor, 0);
    t.previous0c = NaN; x.gate.marker71d = NaN;
    Object.defineProperty(x.part(), 'frame0c', {writable: false});
    Object.defineProperty(x.header, 'timestep1dc8', {writable: false});
    Object.defineProperty(x.part(), 'duration24', {writable: false});
    x.control().status1d = 1;
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 0]));
    x.runtime.parseWaitRecord(x.actor, 3, base);
    check(t.previous0c === 10 && t.accumulator10 === 11 && t.target08 === 15 && x.gate.marker71d === 0,
      'read-only reached operands allowed, overwritten malformed destination values ignored');
  }
  for (const field of ['previous0c', 'accumulator10', 'target08', 'status1d', 'marker71d'] as const) {
    const x = setupFixture(), t = x.targets.getStreamPart(x.actor, 0);
    x.control().status1d = 2;
    const obj = field === 'status1d' ? x.control() : field === 'marker71d' ? x.gate : t;
    Object.defineProperty(obj, field, {writable: false});
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 0]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 3, base), field + ': non-writable');
    check(t.previous0c === (field === 'previous0c' ? 99 : 10) &&
      t.accumulator10 === (field === 'previous0c' || field === 'accumulator10' ? 2 : 11) &&
      x.control().status1d === (field === 'target08' || field === 'marker71d' ? 1 : 2), 'reached store prefix exact');
  }
  for (const overflow of ['frame', 'target'] as const) {
    const x = setupFixture(), max = Math.fround(3.4028234663852886e38);
    x.part().frame0c = max;
    if (overflow === 'frame') x.header.timestep1dc8 = max;
    else x.targets.getStreamPart(x.actor, 0).accumulator10 = max;
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, 0]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), overflow === 'frame' ? 'startFrame result' : 'target08 result');
    check(x.control().status1d === (overflow === 'frame' ? 0 : 1), 'overflow follows actual store prefix');
  }
  for (const length of [1, 2, 3, 4, 5, 6, 7, 8]) {
    const x = setupFixture(), base = x.runtime.createStream(new Uint8Array(setupBytes.slice(0, length)));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'out of bounds');
    check(x.targets.getStreamPart(x.actor, 0).previous0c === (length === 8 ? 10 : 99), 'signed frame bytes consumed before part prefix');
  }
  {
    const x = setupFixture(), base = x.runtime.createStream(new Uint8Array([1]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, base, 0), 'out of bounds');
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, base, 0, NaN), 'out of bounds'); // mode byte precedes transition admission
    rejects(() => x.runtime.parseWaitRecord(x.actor, 0, base, 0, NaN, 0), 'transition');
  }
  for (const returned of [null, 0, Promise.resolve()]) {
    const x = setupFixture(), base = x.runtime.createStream(new Uint8Array([...setupBytes, 0]));
    x.setupReturns(returned);
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'setupPart must complete synchronously');
    check(x.targets.getStreamPart(x.actor, 0).previous0c === 10 && x.control().status1d === 0, 'nonvoid setup result refuses before status store');
  }
  {
    const x = setupFixture(), base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 0]));
    x.dispatchAdapter.setupPart = () => {throw Error('replacement must not run');};
    x.hooks.setup = () => {try {x.runtime.parseWaitRecord(x.actor, 0, base);} catch { /* poison outer */ }};
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'reentry was caught');
    check(x.control().status1d === 0 && x.targets.getStreamPart(x.actor, 0).previous0c === 10, 'captured setup method and caught reentry prefix');
    delete x.hooks.setup; x.runtime.parseWaitRecord(x.actor, 1, base);
    check(x.control().status1d === 1, 'independent call recovers after reentry');
  }

  {
    const x = setupFixture(), requests: SourceActorAnimationSetupRequest[] = [];
    x.control().status1d = 1; x.part().duration24 = -9;
    x.hooks.setup = (i, request) => {
      requests.push(request);
      if (i === 0) {
        x.part().frame0c = 7; x.targets.getStreamPart(x.actor, 0).accumulator10 = 20;
        x.header.timestep1dc8 = 3;
        x.gate.blockedMask1d9a = 255;
      }
    };
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 0]));
    x.runtime.parseWaitRecord(x.actor, 3, base);
    check(requests[0]!.frame === 4.5 && requests[1]!.frame === 4.5 && x.targets.getStreamPart(x.actor, 0).target08 === 27,
      'signed duration needs no GQR, nonnegative frame reused despite live timestep mutation, target sum reads live post-call values');
  }
  {
    const x = setupFixture(), bytes = new Uint8Array(32);
    bytes.set([0, 8], 2); bytes.set([0, 8], 8);
    bytes.set([...setupBytes, 0, 1, 0, 0], 16);
    const base = x.runtime.createStream(bytes);
    x.runtime.bindStartActor(x.actor, {familyBank1d80: base, sharedBank1d84: null, defaultSelector582: 1, marker709: 0});
    x.hooks.setup = (_i, request) => check(request.frame === 6.25 && request.transition === 31 && request.mode === 32,
      'start forwards actual caller arguments after source resets');
    x.runtime.startStream(x.actor, 1, 1, 0, 6.25, 31, 32);
    check(x.targets.getStreamPart(x.actor, 0).target08 === 4 && x.targets.getStreamPart(x.actor, 0).previous0c === 0,
      'start resets precede opcode01 target prefix');
  }
  {
    const x = setupFixture(), base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 0]));
    x.runtime.getCommand(x.command).flags01 = 8; x.control().wait14 = 0; x.control().next04 = base;
    x.hooks.setup = (_i, request) => check(request.frame === 4.5 && request.transition === 10 && request.mode === 9,
      'source update continuation explicitly supplies negative frame and signed-negative overrides');
    check(x.run() === 0 && x.control().current00 === x.runtime.cursorAt(base, 8) && x.targetCalls() === 0,
      'update continuation preserves setup suppression and terminal install');
  }

  {
    const x = setupFixture(), target = x.targets.getStreamPart(x.actor, 0);
    x.control().status1d = 1; x.part().duration24 = NaN; target.accumulator10 = NaN;
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 0]));
    rejects(() => x.runtime.parseWaitRecord(x.actor, 1, base), 'duration24: expected signed16');
    check(target.previous0c === 10 && target.target08 === 10 && x.control().status1d === 1,
      'duration load fault precedes malformed accumulator after previous target store');
  }
  {
    const x = setupFixture(), target = x.targets.getStreamPart(x.actor, 0);
    x.control().status1d = 1; x.part().duration24 = -9;
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 0]));
    x.runtime.parseWaitRecord(x.actor, 1, base);
    check(target.accumulator10 === -7 && target.target08 === -3 && target.previous0c === 10,
      'negative signed duration decreases live accumulator without observation-hook overwrite');
  }
  for (const [frame, expected] of [[16777216, 16777216], [16777218, 16777220]]) {
    const x = setupFixture(); x.part().frame0c = frame!; x.header.timestep1dc8 = 1;
    let observed: number | undefined;
    x.hooks.setup = (_i, request) => {observed = request.frame;};
    const base = x.runtime.createStream(new Uint8Array([...setupBytes, 0, 1, 0, 0]));
    let error: unknown;
    try {x.runtime.parseWaitRecord(x.actor, 1, base);} catch (caught) {error = caught;}
    check(error === undefined, `valid fallback frame rounds to f32 without refusal: ${String(error)}`);
    check(observed === expected, 'fallback frame addition rounds halfway to even in source float32');
  }

  // Stream-start fixtures are copied synthetic bank bytes, not retail allocation defaults.
  const startFixture = (opcode = 0, synthetic = false) => {
    const x = fixture(1, synthetic);
    const bytes = new Uint8Array(32);
    bytes.set([0, 8], 2); // selector1 -> group8
    bytes.set([0, 8], 8); // action0 -> record16
    bytes.set([opcode, 1, 0, 7], 16);
    const base = x.runtime.createStream(bytes);
    const initial = {familyBank1d80: base, sharedBank1d84: base, defaultSelector582: 1, marker709: 9};
    x.runtime.bindStartActor(x.actor, initial);
    return {...x, base, initial, start: x.runtime.getStartActorBinding(x.actor),
      begin: (mask = 1, selector = 1, action = 0) => x.runtime.startStream(x.actor, mask, selector, action)};
  };
  {
    const x = startFixture(); x.initial.defaultSelector582 = 3;
    check(Object.isSealed(x.start) && x.start.defaultSelector582 === 1 && x.control().group18 === 0 &&
      x.control().action19 === 0 && x.control().status1d === 0, 'start binding copied/sealed and compatibility fixture bytes');
    rejects(() => x.runtime.bindStartActor(x.actor, x.initial), 'already bound');
    rejects(() => x.runtime.getStartActorBinding(Symbol('foreign')), 'start binding');
    const begin = x.runtime.startStream;
    begin(x.actor, 1, 0, 0);
    check(x.control().group18 === 1 && x.control().current00 === x.runtime.cursorAt(x.base, 16) &&
      x.control().wait14 === 7 && x.control().next04 === x.runtime.cursorAt(x.base, 20), 'default start uses real terminal parser');
    check(x.targets.getStreamPart(x.actor, 0).previous0c === 0 && x.targets.getStreamPart(x.actor, 0).accumulator10 === 0 &&
      x.targets.getStreamPart(x.actor, 0).target08 === 4.5 && x.binding().elapsed08 === 2.5,
      'actual reset feeds real target fallback, not separate fake state');
  }
  for (const shared of [false, true]) {
    const x = startFixture();
    if (shared) {x.start.familyBank1d80 = Symbol('unused'); x.start.sharedBank1d84 = null;}
    else {x.start.familyBank1d80 = null; x.start.sharedBank1d84 = Symbol('unused');}
    x.start.defaultSelector582 = NaN;
    for (let i = 0; i < 4; i++) {
      x.control(i).group18 = 91; x.control(i).action19 = 92; x.control(i).status1d = 93;
      x.control(i).wait14 = NaN;
      x.targets.getStreamPart(x.actor, i).previous0c = NaN;
    }
    x.begin(0, shared ? 0x80 : 0);
    for (let i = 0; i < 4; i++) {
      const c = x.control(i), t = x.targets.getStreamPart(x.actor, i);
      check(c.current00 === null && c.next04 === null && Object.is(c.wait14, 0) && c.finished1a === 1 && c.status1d === 0 &&
        c.event1e === 0 && c.group18 === 91 && c.action19 === 92 && Object.is(t.previous0c, 0) &&
        Object.is(t.accumulator10, 0) && Object.is(t.target08, 0) && x.part(i).frame0c === 4, 'null bank resets all four preserving selectors/unrelated fields');
    }
    check(x.start.marker709 === 9, 'zero effective mask leaves marker');
  }
  for (const mask of [0, 1, 2, 4, 8, 15, 0xffffffff]) {
    const x = startFixture(4); x.gate.activeMask579 = 0x85;
    rejects(() => x.begin(mask), 'unsupported zz_004c050_ opcode');
    check(x.start.marker709 === 9, 'marker uses effective bit value2, not original mask');
    for (let i = 0; i < 4; i++) {
      const selected = (mask & 5 & (1 << i)) !== 0;
      check(x.control(i).current00 === (selected ? null : x.command) && x.control(i).group18 === (selected ? 1 : 0),
        'active mask intersection and unsupported opcode retains every selected reset');
    }
  }
  {
    const x = startFixture(0, true); x.gate.activeMask579 = 5;
    x.hooks.target = () => check(x.control(0).current00 === null && x.control(2).current00 === null &&
      x.control(0).group18 === 1 && x.control(2).group18 === 1, 'all selected starts reset before any parser fallback or install');
    x.begin(15);
    for (let i = 0; i < 4; i++) {
      const selected = i === 0 || i === 2;
      check(x.control(i).current00 === (selected ? x.runtime.cursorAt(x.base, 16) : x.command) &&
        x.control(i).wait14 === (selected ? 7 : 3) && x.targets.getStreamPart(x.actor, i).target08 === (selected ? 4.5 : 10),
      'real terminal parser receives effective selection rather than original requested mask');
    }
  }
  {
    const x = startFixture(4, true); x.start.familyBank1d80 = Symbol('foreign');
    rejects(() => x.begin(2), 'owned byte cursor');
    check(x.start.marker709 === 0 && x.control(1).current00 === x.command, 'marker clears before reached foreign bank rejection');
    x.start.familyBank1d80 = x.base; x.start.sharedBank1d84 = Symbol('unused foreign');
    x.start.defaultSelector582 = NaN; x.start.marker709 = NaN;
    rejects(() => x.begin(1), 'unsupported zz_004c050_ opcode');
    check(Number.isNaN(x.start.marker709), 'unused invalid default/marker/shared bank remain lazy');
  }
  {
    const x = startFixture(); x.start.familyBank1d80 = Symbol('unused foreign');
    x.begin(1, 0x181);
    check(x.control().group18 === 0x81 && x.control().wait14 === 7, 'shared selector masks table index but stores original low byte');
  }
  {
    const x = fixture(); const bytes = new Uint8Array(600);
    bytes.set([0xff, 0xf0], 256); // default128 sign extends -128: bank512 -256 -> group496
    bytes.set([0xff, 0xf0], 494); // action-1 at group496-2 -> record480
    bytes.set([0, 1, 0, 11], 480);
    const base = x.runtime.createStream(bytes), bank = x.runtime.cursorAt(base, 512);
    x.runtime.bindStartActor(x.actor, {familyBank1d80: bank, sharedBank1d84: Symbol('unused shared'), defaultSelector582: 128, marker709: 9});
    x.runtime.startStream(x.actor, 1, 0, -1);
    check(x.control().group18 === 128 && x.control().action19 === 255 && x.control().wait14 === 11 &&
      x.control().current00 === x.runtime.cursorAt(base, 480), 'signed default keeps family, nonzero bank, negative group/action/stream displacements');
  }
  {
    const x = startFixture(); const bytes = new Uint8Array(32);
    bytes.set([0, 8], 0); bytes.set([0, 8], 8); bytes.set([0, 1, 0, 5], 16);
    x.start.familyBank1d80 = x.runtime.createStream(bytes);
    x.begin(1, 0x80000000, -0x80000000);
    check(x.control().group18 === 0 && x.control().action19 === 0 && x.control().wait14 === 5,
      'PPC shifted indices wrap their 32-bit integer displacement without invented address wrapping');
  }
  for (const [bytes, expected] of [
    [new Uint8Array(3), 'byte read out of bounds'],
    [new Uint8Array([0, 0, 0, 8]), 'byte read out of bounds'],
    [new Uint8Array([0, 0, 0xff, 0xfc]), 'cursor offset'],
  ] as const) {
    const x = startFixture(); x.start.familyBank1d80 = x.runtime.createStream(bytes);
    rejects(() => x.begin(0), expected);
    check(x.control().current00 === x.command, 'zero mask still resolves both signed tables; early failure leaves controls');
  }
  {
    const x = startFixture(); x.start.familyBank1d80 = x.runtime.createStream(new Uint8Array([0, 0, 0, 4, 0xff, 0xf8]));
    rejects(() => x.begin(1), 'cursor offset');
    check(x.control().current00 === x.command && x.control().wait14 === 3 && x.control().group18 === 0,
      'final stream pointer host underflow fails before selected stores');
  }
  {
    const x = startFixture(4, true); const order: number[] = [];
    x.hooks.targetGet = i => {
      order.push(i);
      if (i === 2) check(x.control(0).current00 === null && x.control(1).current00 === null, 'earlier parts reset before later getter');
      x.gate.activeMask579 = 0;
    };
    rejects(() => x.begin(15), 'unsupported zz_004c050_ opcode');
    check(order.join(',') === '0,1,2,3' && x.control(3).current00 === null, 'snapshot mask, ascending all resets before parser');
  }
  for (let fault = 0; fault < 9; fault++) {
    const x = startFixture(4), target = x.targets.getStreamPart(x.actor, 0), control = x.control();
    control.status1d = 8; control.event1e = 9; control.next04 = x.base; control.finished1a = 7;
    const stores: [object, string, number | symbol | null][] = [
      [target, 'previous0c', 0], [target, 'accumulator10', 0], [target, 'target08', 0],
      [control, 'status1d', 0], [control, 'event1e', 0], [control, 'next04', null],
      [control, 'current00', null], [control, 'wait14', 0], [control, 'finished1a', 0],
    ];
    const before = stores.map(([record, key]) => Object.getOwnPropertyDescriptor(record, key)!.value as unknown);
    const [record, key] = stores[fault]!; Object.defineProperty(record, key, {writable: false});
    rejects(() => x.begin(), `${key}: non-writable`);
    for (let i = 0; i < stores.length; i++) {
      const [record, key, value] = stores[i]!;
      check(Object.is(Object.getOwnPropertyDescriptor(record, key)!.value, i < fault ? value : before[i]),
        `complete reset fault prefix at ${fault} leaves exact store ${i}`);
    }
    check(control.group18 === 1 && control.action19 === 0 && x.control(1).current00 === x.command,
      'ordered reset faults follow selector stamps and precede other parts');
  }
  for (const field of ['previous0c', 'accumulator10', 'target08'] as const) {
    const x = startFixture(4), target = x.targets.getStreamPart(x.actor, 0);
    Object.defineProperty(target, field, {writable: false});
    rejects(() => x.begin(), `${field}: non-writable`);
    check(x.control().group18 === 1 && x.control().current00 === x.command &&
      target.previous0c === (field === 'previous0c' ? 99 : 0) && target.accumulator10 === (field === 'target08' ? 0 : 2), 'target reset store order prefix');
  }
  for (const field of ['group18', 'action19', 'status1d', 'event1e', 'next04', 'current00', 'wait14', 'finished1a'] as const) {
    const x = startFixture(4); x.control().status1d = 8; x.control().finished1a = 9; x.control().next04 = x.base;
    Object.defineProperty(x.control(), field, {writable: false});
    rejects(() => x.begin(), `${field}: non-writable`);
    check(x.control(1).current00 === x.command, 'failure never resets later unselected control');
    const afterTarget = !['group18', 'action19'].includes(field);
    check(x.targets.getStreamPart(x.actor, 0).target08 === (afterTarget ? 0 : 10), 'selector stores precede reset target writes');
    if (field === 'finished1a') check(x.control().current00 === null && x.control().next04 === null && x.control().wait14 === 0, 'last reset store preserves full earlier prefix');
  }
  {
    const x = startFixture(); x.start.familyBank1d80 = null;
    Object.defineProperty(x.control(1), 'status1d', {writable: false});
    rejects(() => x.begin(0), 'status1d: non-writable');
    check(x.control(0).finished1a === 1 && x.control(1).current00 === x.command && x.control(2).current00 === x.command &&
      x.targets.getStreamPart(x.actor, 1).target08 === 0, 'null bank interleaves reset then finished1 per part, preserves fault prefix');
  }
  {
    const x = startFixture(); Object.defineProperty(x.start, 'marker709', {writable: false});
    rejects(() => x.begin(2), 'marker709: non-writable');
    check(x.control(1).current00 === x.command, 'marker store fault before bank resolution');
    x.begin(0); // Readonly marker and every selected control are untouched.
    Object.freeze(x.control(3)); x.control(2).wait14 = NaN;
    Object.freeze(x.targets.getStreamPart(x.actor, 3));
    x.begin(1);
    check(x.control().wait14 === 7 && Number.isNaN(x.control(2).wait14), 'readonly/invalid unselected state is lazy');
  }
  {
    const x = startFixture(0, true);
    x.targetAdapter.getStreamPart = () => {throw Error('replacement target getter');};
    x.begin();
    check(x.control().wait14 === 7 && x.targetCalls() === 1, 'start captures actual target getter receiver and uses real parser once');
  }
  for (const mutation of ['start', 'bind', 'cursor'] as const) {
    const x = startFixture(4, true);
    x.hooks.targetGet = i => {
      if (i !== 1) return;
      try {
        if (mutation === 'start') x.begin(0);
        else if (mutation === 'bind') x.runtime.bindStartActor(x.actor, x.initial);
        else x.runtime.cursorAt(x.base, 0);
      } catch { /* Outer operation must remain poisoned. */ }
    };
    rejects(() => x.begin(3), 'reentry was caught');
    check(x.control(0).current00 === null && x.control(1).current00 === x.command && x.control(1).group18 === 1,
      'caught reentry preserves earlier reset and current selector stores, rejects before target writes');
    delete x.hooks.targetGet;
    rejects(() => x.begin(3), 'unsupported zz_004c050_ opcode');
    check(x.control(1).current00 === null, 'runtime recovers on next independent operation');
  }
  for (const [mask, selector, action, expected] of [
    [-1, 1, 0, 'mask'], [0x100000000, 1, 0, 'mask'], [1, -1, 0, 'selector'],
    [1, 0x100000000, 0, 'selector'], [1, 1, 0x80000000, 'signed32'], [1, 1, -0x80000001, 'signed32'], [1, 1, NaN, 'signed32'],
  ] as const) {
    const x = startFixture(); rejects(() => x.begin(mask, selector, action), expected);
    check(x.start.marker709 === 9 && x.control().current00 === x.command, 'argument domain rejection before source effects');
  }

  {
    const x = startFixture(16, true), bytes = new Uint8Array(32);
    bytes.set([0, 8], 2); bytes.set([0, 8], 8);
    bytes.set([16, 0, 1, 12, 0, 1, 0, 3], 16);
    x.start.familyBank1d80 = x.runtime.createStream(bytes);
    x.hooks.target = () => check(x.control(0).current00 === null && x.control(1).current00 === null,
      'all selected resets precede parser fallbacks');
    x.begin(3);
    check(x.targets.getStreamPart(x.actor, 0).accumulator10 === 12 && x.targets.getStreamPart(x.actor, 1).accumulator10 === 12 &&
      x.control(0).wait14 === 3 && x.control(1).wait14 === 3 && x.targetCalls() === 2 && x.start.marker709 === 0,
      'start feeds existing opcode0x10 chain once, then actual terminal fallbacks');
  }
  for (const active of [0x7f, 0x80, 0x82, 0xff]) {
    const x = startFixture(4); x.gate.activeMask579 = active;
    rejects(() => x.begin(0x80000002), 'unsupported zz_004c050_ opcode');
    check(x.control(1).current00 === ((active & 2) ? null : x.command) && x.start.marker709 === ((active & 2) ? 0 : 9),
      'sign-extended active masks admit high uint32 bits without changing low-four routing');
  }
  {
    const x = fixture();
    rejects(() => x.runtime.startStream(x.actor, 1, 1, 0), 'start binding');
    const initial = {familyBank1d80: Symbol('foreign permitted until dereference'), sharedBank1d84: null, defaultSelector582: 0, marker709: 0};
    rejects(() => x.runtime.bindStartActor(Symbol('unknown'), initial), 'actor binding');
    rejects(() => x.runtime.bindStartActor(x.actor, {...initial, defaultSelector582: 256}), 'defaultSelector582');
    x.runtime.bindStartActor(x.actor, initial);
    rejects(() => x.runtime.startStream(x.actor, 0, 1, 0), 'owned byte cursor');
  }

}
