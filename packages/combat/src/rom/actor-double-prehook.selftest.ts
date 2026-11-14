import {createRomActor} from './actor.js';
import {bindDoubleNinjaOwnerState, getDoubleNinjaOwnerState, prepareNinjaX, clearNinjaX} from '../ninjaX.js';
import {createSourceActorStatusTimersRuntime, type SourceActorStatusTimersSources} from './actor-status-timers.js';
import {createSourceActorInputChargeRuntime, type SourceActorInputChargeSources} from './actor-input-charge.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';
import {createSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceActorDoublePrehookRuntime, isSourceActorDoublePrehookRuntime,
  hasIncompleteSourceActorDoubleLifecycle, markIncompleteSourceActorDoubleLifecycle,
  requireCompleteSourceActorDoubleLifecycle, type SourceActorDoublePrehookBinding,
  type SourceActorDoublePrehookSources} from './actor-double-prehook.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-double-prehook-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (caught) {error = String(caught);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
function absent(owner: object, key: string): void {delete (owner as Record<string, unknown>)[key];}
function readonly(owner: object, key: string): void {Object.defineProperty(owner, key, {writable: false});}
/** Observation only. All source effects execute the genuine implementation. */
function watch(run: () => void, observe: (owner: object, key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object, key: PropertyKey) => {
    observe(owner, key); return original(owner, key);
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
function fixture(options: {defer?: boolean; clone?: boolean; wrongChargeStatus?: boolean; arm?: number} = {}) {
  const unsupported = (): never => {throw Error('unexpected source body');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const mapping = createSourceActorJointMappingRuntime(joints, feedback,
    {interpretAObj: unsupported, animateRObjs: unsupported, animateDObjs: unsupported}, {convertEulerToQuaternion: unsupported});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 0, jointBank33: 0, poseBuffer35: 0})));
  const id = mapping.createActor({descriptor4b0: mapping.createDescriptor([]), jointCount1d90: 0,
    boundary1d91: 0, boundary1d92: 0, boundary1d93: 0, jointBank1db4: null, jointBank1db8: null,
    timestep1dc8: 1}, {parts, poses: [[], []]});
  const dispatch = createSourceActorAnimationDispatchRuntime(mapping, feedback);
  dispatch.bindActor(id, {family1d88: null, shared1d8c: null, marker578: 0, marker1db3: 0});
  const targets = createSourceStreamWaitTargetRuntime(mapping, feedback, dispatch);
  const streams = createSourceStreamWaitRuntime({mapping, feedback, dispatch, targets});
  streams.bindActor(id, {activeMask579: 0, blockedMask1d9a: 0},
    Array.from({length: 4}, () => ({current00: null, wait14: 0, finished1a: 0, event1e: 0})));
  streams.bindStartActor(id, {familyBank1d80: null, sharedBank1d84: null, defaultSelector582: 9, marker709: 0});
  const actual = createRomActor(); actual.borgNumber = 3; actual.controlWord = 0; actual.aimRoll1dfc = 777;
  const world = {}, movement = {}, attribute = {};
  const worldSource = {getActualActor: () => actual,
    getActorBinding: () => world as ReturnType<SourceActorStatusTimersSources['world']['getActorBinding']>,
    getMappingActor: () => mapping.getActor(id)};
  const attributeSource = {getActualActor: () => actual,
    getActorBinding: () => attribute as ReturnType<SourceActorStatusTimersSources['attributes']['getActorBinding']>,
    getParameterDescriptor: unsupported};
  const status = createSourceActorStatusTimersRuntime({world: worldSource, mapping, attributes: attributeSource, streams,
    movement: {getActualActor: () => actual,
      getActorBinding: () => movement as ReturnType<SourceActorStatusTimersSources['movement']['getActorBinding']>}});
  const borg = {hp: 100, hitDrainFrames: 0, balanceGauge: 10, balanceGaugeMax: 10, balanceRefillDelay: 0,
    downResetDelay: 0, comboWindow: 0, comboAccum: 0, comboRank: 0, invincTimer: 0, sourceAmmoRefillPauseMask: 0};
  const slot = () => ({cell: {cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0}, mirror776: 0});
  status.bindActor(id, borg, {short272: -1}, [slot(), slot(), slot()]);
  const chargeStatus: SourceActorInputChargeSources['status'] = options.wrongChargeStatus
    ? {...status, getActorBinding: () => ({short272: 4})} : status;
  const charge = createSourceActorInputChargeRuntime({world: worldSource, status: chargeStatus,
    mapping, attributes: attributeSource, global: {}, data: {}});
  charge.bindActor(id, {byte58e: 255});
  const clone = {arm7c8: options.arm ?? 0, offset7b0: {x: 9, y: 8, z: 7}};
  if (options.clone !== false) bindDoubleNinjaOwnerState(actual, clone);
  const sources = {status, charge, streams};
  const initial: Partial<SourceActorDoublePrehookBinding> = {
    pointer4b4: 0x8006facc, pointer4bc: 0x8006f7c0, pointer4c0: 0x8006f88c, byte6ee: 88};
  const runtime = createSourceActorDoublePrehookRuntime(sources);
  const bind = (): void => runtime.bindActor(id, initial);
  if (!options.defer) bind();
  return {id, actual, clone, sources, initial, runtime, bind, world, mapping, attribute, status, charge, streams,
    binding: () => runtime.getActorBinding(id), start: () => streams.getStartActorBinding(id),
    statusBinding: () => status.getActorBinding(id), chargeBinding: () => charge.getActorBinding(id),
    run: () => runtime.runActor(id)};
}
export function runActorDoublePrehookSelfTests(): void {
  {
    const x = fixture();
    check(isSourceActorDoublePrehookRuntime(x.runtime), 'genuine prehook brand');
    for (const value of [{...x.runtime}, Object.create(x.runtime), {}, null])
      check(!isSourceActorDoublePrehookRuntime(value), 'copies/inheritance do not forge source ownership');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()) && x.binding() !== x.initial, 'frozen API and copied sealed missing cells');
    equal(x.runtime.getActualActor(x.id), x.actual, 'same actual');
    equal(x.runtime.getStartBinding(x.id), x.start(), 'same582 owner');
    equal(x.runtime.getStatusBinding(x.id), x.statusBinding(), 'same272 owner');
    equal(x.runtime.getChargeBinding(x.id), x.chargeBinding(), 'same58e owner');
    equal(x.runtime.getMappingActor(x.id), x.mapping.getActor(x.id), 'same mapping');
    equal(x.runtime.getWorldBinding(x.id), x.world, 'same world');
    equal(x.runtime.getAttributeBinding(x.id), x.attribute, 'same attribute');
    equal(x.runtime.getCloneOwner(x.id), x.clone, 'same persistent7c8 owner');
    equal(x.runtime.getSourceOwners(x.id).length, 4, 'binding/charge/clone/vector alias exclusions');
    check(x.runtime.getSourceOwners(x.id).includes(x.clone.offset7b0), 'offset identity excluded without component reads');
    equal(x.run(), undefined, 'unarmed Double genuinely returns void');
    equal(x.start().defaultSelector582, 1, 'Double582=1'); equal(x.actual.aimRoll1dfc, 0, 'existing actual1dfc reset');
    equal(x.binding().byte6ee, 0, 'new6ee reset'); equal(x.statusBinding().short272, -5, 'lha272 and sth preserve signed bit pattern');
    equal(x.chargeBinding().byte58e, 223, 'existing58e mask20 clear'); equal(x.clone.arm7c8, 0, 'no posthook/clone write');
    equal(x.clone.offset7b0.x, 9, 'unarmed leaves vector unchanged');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual), 'complete prehook not poisoned');
    x.run(); x.runtime.assertActorComplete(x.id);
  }
  for (const borg of [0, 2, 10, 32767, 32768, 65535]) {
    const x = fixture({clone: false}); x.actual.borgNumber = borg; x.actual.actionIndex = 3;
    equal(x.run(), undefined, 'selected6f7c0 other-family branch genuinely returns');
    equal(x.start().defaultSelector582, 0, '3e8 read, not action580');
    equal(getDoubleNinjaOwnerState(x.actual), undefined, 'no lazy clone default created');
  }
  {
    const x = fixture({defer: true}); delete x.initial.byte6ee; x.bind(); x.actual.controlWord = 0x1001;
    absent(x.actual, 'aimRoll1dfc'); x.statusBinding().short272 = NaN;
    readonly(x.statusBinding(), 'short272'); readonly(x.clone, 'arm7c8');
    Object.defineProperty(x.clone.offset7b0, 'x', {get() {throw Error('unreached clone vector');}});
    equal(x.run(), undefined, 'set control masks skip1dfc/6ee/272 and unarmed skips vector');
    equal(x.binding().byte6ee, undefined, 'no default6ee created');
    equal(x.actual.aimRoll1dfc, undefined, 'no default1dfc created');
  }
  for (const arm of [1, 2, 127, 128, 255]) {
    const x = fixture({arm});
    Object.defineProperty(x.clone, 'offset7b0', {get() {throw Error('vector must not be loaded before4538c');}});
    absent(x.actual, 'modelScale');
    rejects(x.run, 'actual8004538c');
    equal(x.chargeBinding().byte58e, 255, 'armed retainedclear thenOR20 before normalization');
    equal(x.start().defaultSelector582, 1, 'armed retains582'); equal(x.actual.aimRoll1dfc, 0, 'armed retains1dfc');
    equal(x.statusBinding().short272, -5, 'armed retains272'); equal(x.clone.arm7c8, arm, 'no guessed reset');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual), 'armed failure permanently latched');
    x.clone.arm7c8 = 0; rejects(x.run, 'known incomplete'); rejects(() => x.runtime.assertActorComplete(x.id), 'known incomplete');
    rejects(() => requireCompleteSourceActorDoubleLifecycle(x.actual), 'known incomplete');
  }
  {
    const x = fixture({clone: false}); rejects(x.run, 'actual7c8');
    equal(x.chargeBinding().byte58e, 223, 'missing clone fails after58e clear');
    bindDoubleNinjaOwnerState(x.actual, x.clone); rejects(x.run, 'known incomplete');
    const y = fixture({clone: false}); bindDoubleNinjaOwnerState(y.actual, y.clone);
    equal(y.run(), undefined, 'explicit later clone binding before first run is retained');
  }
  {
    const x = fixture({arm: 2}); let reached = false, chargeReads = 0;
    watch(() => rejects(x.run, 'actual8004538c'), (owner, key) => {
      if (owner === x.binding() && key === 'pointer4bc') reached = true;
      if (!reached || owner !== x.chargeBinding() || key !== 'byte58e') return;
      chargeReads++;
      if (chargeReads === 3) {
        equal(x.chargeBinding().byte58e, 223, 'first58e clear completed before armed reload');
        x.chargeBinding().byte58e = 8;
      }
    });
    equal(chargeReads, 4, 'two independent58e loads and stores');
    equal(x.chargeBinding().byte58e, 40, 'armed OR uses fresh58e not stale snapshot');
  }
  for (const key of ['status', 'charge', 'streams'] as const) {
    const x = fixture({defer: true});
    const fake = {...x.sources, [key]: {...x.sources[key]}} as SourceActorDoublePrehookSources;
    rejects(() => createSourceActorDoublePrehookRuntime(fake), 'genuine source runtime');
  }
  {
    const x = fixture({defer: true, wrongChargeStatus: true}); rejects(x.bind, 'charge status');
    const y = fixture(); const second = createSourceActorDoublePrehookRuntime(y.sources);
    rejects(() => second.bindActor(y.id, y.initial), 'already claimed');
    rejects(() => y.runtime.runActor(Symbol()), 'unknown/non-owned');
  }
  for (const hook of ['rootAction', 'preState', 'postState'] as const) {
    const x = fixture({defer: true}); x.actual[hook] = () => {throw Error('legacy callback');};
    rejects(x.bind, `legacy callable ${hook}`);
    equal(x.start().defaultSelector582, 9, 'legacy refusal before any source store');
    x.actual[hook] = null; x.bind(); equal(x.run(), undefined, 'failed admission did not consume clone owner');
  }
  for (const key of ['pointer4bc', 'byte6ee', 'byte58e', 'short272', 'arm7c8', 'field1dfc']) {
    const x = fixture(); Object.assign(x.actual, {[key]: 1}); rejects(x.run, 'competing Double storage');
    equal(x.start().defaultSelector582, 9, 'shadow refused before source');
  }
  {
    const x = fixture({clone: false}); Object.assign(x.actual, {arm7c8: 0});
    rejects(x.run, 'competing Double storage'); equal(x.start().defaultSelector582, 9, 'shadow7c8 cannot substitute absent persistent owner');
    const y = fixture(); Object.assign(y.actual, {aimRoll1dfc: NaN}); y.binding().byte6ee = NaN;
    y.start().defaultSelector582 = NaN; equal(y.run(), undefined, 'source stores do not pre-read overwritten cells');
    equal(y.actual.aimRoll1dfc, 0, '1dfc overwrite uses existing destination without invented input');
  }
  {
    const x = fixture({defer: true}); delete x.initial.pointer4bc; x.bind(); rejects(x.run, 'pointer4bc');
    equal(x.start().defaultSelector582, 9, 'missing4bc no effects'); check(!hasIncompleteSourceActorDoubleLifecycle(x.actual), 'missing4bc no mutation marker');
    const y = fixture(); y.binding().pointer4bc = 0; rejects(y.run, 'unsupported actual4bc');
    y.binding().pointer4bc = 0x8006f7c0; equal(y.run(), undefined, 'unsupported pointer before effects permits explicit repair');
  }
  {
    const x = fixture(); readonly(x.start(), 'defaultSelector582'); rejects(x.run, 'non-writable');
    equal(x.actual.aimRoll1dfc, 777, 'readonly first destination blocks later1dfc');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual), 'no store means no permanent effects latch');
    const y = fixture(); readonly(y.actual, 'aimRoll1dfc'); rejects(y.run, 'non-writable');
    equal(y.start().defaultSelector582, 1, 'readonly1dfc retains582'); equal(y.binding().byte6ee, 88, 'readonly1dfc before6ee');
    check(hasIncompleteSourceActorDoubleLifecycle(y.actual), 'readonly after582 poisons');
  }
  {
    const x = fixture({defer: true}); delete x.initial.byte6ee; x.bind(); rejects(x.run, 'byte6ee');
    equal(x.actual.aimRoll1dfc, 0, 'missing6ee retains earlier1dfc'); equal(x.statusBinding().short272, -1, 'missing6ee before272');
    const y = fixture(); readonly(y.statusBinding(), 'short272'); rejects(y.run, 'non-writable');
    equal(y.binding().byte6ee, 0, 'readonly272 retains6ee'); equal(y.chargeBinding().byte58e, 255, 'readonly272 before58e');
    const z = fixture(); readonly(z.chargeBinding(), 'byte58e'); rejects(z.run, 'non-writable');
    equal(z.statusBinding().short272, -5, 'readonly58e retains272');
  }
  {
    const x = fixture(); absent(x.actual, 'controlWord'); rejects(x.run, 'controlWord');
    equal(x.start().defaultSelector582, 1, 'missing control follows582'); equal(x.actual.aimRoll1dfc, 777, 'missing control before1dfc');
    const y = fixture(); y.statusBinding().short272 = 65535; rejects(y.run, 'short272: integer');
    equal(y.binding().byte6ee, 0, 'unsigned-short owner rejected only after earlier stores');
  }
  {
    const x = fixture(); let reached = false, controls = 0, borgReads = 0, stores58e = 0;
    watch(() => x.run(), (owner, key) => {
      if (owner === x.binding() && key === 'pointer4bc') reached = true;
      if (!reached) return;
      if (owner === x.actual && key === 'borgNumber') {borgReads++; if (borgReads === 2) x.actual.borgNumber = 10;}
      if (owner === x.actual && key === 'controlWord') {
        controls++; if (controls === 2) {equal(x.binding().byte6ee, 0, 'secondcontrol after6ee'); x.actual.controlWord = 0x1000;}
      }
      if (owner === x.chargeBinding() && key === 'byte58e') stores58e++;
    });
    equal(controls, 2, 'fresh control loads'); equal(borgReads, 2, 'fresh3e8 load');
    equal(x.start().defaultSelector582, 1, 'initial3e8 governs582'); equal(x.statusBinding().short272, -1, 'secondcontrol independently skips272');
    equal(stores58e, 2, 'one58e source load plus destination check');
  }
  {
    const x = fixture(); let reached = false, trapped = false;
    watch(() => rejects(x.run, 'caught same-runtime reentry'), (owner, key) => {
      if (owner === x.binding() && key === 'pointer4bc') reached = true;
      if (!reached || trapped || owner !== x.actual || key !== 'controlWord') return;
      trapped = true; rejects(x.run, 'same-runtime reentry');
    });
    equal(x.start().defaultSelector582, 1, 'caught reentry retains earlier582'); equal(x.actual.aimRoll1dfc, 777, 'caught reentry prevents later stores');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual), 'caught reentry poisons permanent lifecycle');
  }
  {
    const x = fixture(); markIncompleteSourceActorDoubleLifecycle(x.actual); rejects(x.run, 'known incomplete');
    equal(x.start().defaultSelector582, 9, 'action poison blocks prehook before source');
    const second = createSourceActorDoublePrehookRuntime(x.sources); rejects(() => second.bindActor(x.id, x.initial), 'known incomplete');
  }
  {
    const x = fixture(); const state = prepareNinjaX(x.actual, null, null);
    equal(state.doubleClone, x.clone, 'ordinaryX adopts same explicit persistent owner'); clearNinjaX(x.actual);
    equal(getDoubleNinjaOwnerState(x.actual), x.clone, 'ordinary action teardown preserves7c8 owner');
    rejects(() => bindDoubleNinjaOwnerState(x.actual, {...x.clone}), 'already bound');
    rejects(() => bindDoubleNinjaOwnerState(createRomActor(), x.clone), 'already assigned');
    rejects(() => bindDoubleNinjaOwnerState(createRomActor(), Object.create(x.clone) as typeof x.clone), 'own-data');
    rejects(() => bindDoubleNinjaOwnerState(createRomActor(), {...x.clone, arm7c8: 256}), 'own-data');
    check(!Object.hasOwn(createRomActor(), 'aimRoll1dfc'), 'no constructor default for source1dfc');
  }
  {
    const actual = createRomActor(), first = {arm7c8: 0, offset7b0: {x: 0, y: 0, z: 0}};
    const second = {arm7c8: 2, offset7b0: {x: 1, y: 2, z: 3}}; let entered = false;
    watch(() => rejects(() => bindDoubleNinjaOwnerState(actual, first), 'already bound'), (owner, key) => {
      if (entered || owner !== first || key !== 'arm7c8') return;
      entered = true; bindDoubleNinjaOwnerState(actual, second);
    });
    equal(getDoubleNinjaOwnerState(actual), second, 'reentrant host ingress cannot replace already retained owner');
  }
}
