import {createRomActor} from './actor.js';
import {createSourceActorInputChargeRuntime, type SourceActorInputChargeSources} from './actor-input-charge.js';
import {createSourceActorActionRequestRuntime} from './actor-action-request.js';
import {createSourceActorInputTestersRuntime, isSourceActorInputTestersRuntime, hasIncompleteSourceActorInputTesters,
  type SourceActorInputTestersBinding, type SourceActorInputTestersSources} from './actor-input-testers.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-input-testers-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got${String(actual)}, expected${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment), `expected${fragment}, got${message || 'success'}`);
}
function absent(record: object, key: string): void {delete (record as Record<string, unknown>)[key];}
function readonly(record: object, key: string): void {Object.defineProperty(record, key, {writable: false});}
function fixture(options: {defer?: boolean; action?: boolean; actualProxy?: ProxyHandler<ReturnType<typeof createRomActor>>} = {}) {
  const id = Symbol('input tester actor'), descriptorId = Symbol('descriptor4b0'), otherId = Symbol('alternate descriptor');
  const base = createRomActor(), actual = options.actualProxy ? new Proxy(base, options.actualProxy) : base;
  actual.controlWord = 0; actual.inputEdge5d4 = 0; actual.stateFlagA = 0; actual.prevActionIndex = 0; actual.cmdButton = 19;
  const world = {mode4a0: 0, mode4a1: 0};
  const status = {byte593: 0}, mapping = {descriptor4b0: descriptorId}, attribute = {};
  const descriptor = Array<number>(0xb0).fill(255), otherDescriptor = Array<number>(0xb0).fill(255);
  const hooks: Partial<Record<'world' | 'worldBinding' | 'worldMapping' | 'status' | 'statusActor' | 'statusWorld' |
    'statusMapping' | 'statusAttribute' | 'mapping' | 'descriptor' | 'attributeActor' | 'attribute', () => unknown>> = {};
  const worldSource = {
    getActualActor(key: symbol) {check(key === id, 'world id'); check(this === worldSource, 'world receiver'); return (hooks.world?.() ?? actual) as typeof actual;},
    getActorBinding(key: symbol) {check(key === id, 'world binding id'); return (hooks.worldBinding?.() ?? world) as ReturnType<SourceActorInputTestersSources['world']['getActorBinding']>;},
    getMappingActor(key: symbol) {check(key === id, 'world mapping id'); return (hooks.worldMapping?.() ?? mapping) as object;},
  };
  const statusSource = {
    getActualActor(key: symbol) {check(key === id, 'status actor id'); return (hooks.statusActor?.() ?? actual) as typeof actual;},
    getActorBinding(key: symbol) {check(key === id, 'status id'); return (hooks.status?.() ?? status) as typeof status;},
    getWorldBinding(key: symbol) {check(key === id, 'status world id'); return (hooks.statusWorld?.() ?? world) as object;},
    getMappingActor(key: symbol) {check(key === id, 'status mapping id'); return (hooks.statusMapping?.() ?? mapping) as object;},
    getAttributeBinding(key: symbol) {check(key === id, 'status attribute id'); return (hooks.statusAttribute?.() ?? attribute) as object;},
  };
  let descriptorReads = 0;
  const mappingSource = {
    getActor(key: symbol) {check(key === id, 'mapping id'); return (hooks.mapping?.() ?? mapping) as ReturnType<SourceActorInputChargeSources['mapping']['getActor']>;},
    getDescriptor(key: symbol) {
      check(key === descriptorId || key === otherId, 'descriptor identity'); check(this === mappingSource, 'mapping receiver');
      descriptorReads++; return (hooks.descriptor?.() ?? (key === descriptorId ? descriptor : otherDescriptor)) as number[];
    },
  };
  const chargeSources: SourceActorInputChargeSources = {world: worldSource, status: statusSource, mapping: mappingSource,
    attributes: {
      getActualActor() {return (hooks.attributeActor?.() ?? actual) as typeof actual;},
      getActorBinding() {return (hooks.attribute?.() ?? attribute) as ReturnType<SourceActorInputChargeSources['attributes']['getActorBinding']>;},
      getParameterDescriptor() {throw Error('unreached parameter lookup');},
    }, global: {}, data: {}};
  const charge = createSourceActorInputChargeRuntime(chargeSources); charge.bindActor(id, {byte58e: 0});
  const action = options.action === false ? undefined : createSourceActorActionRequestRuntime({world: worldSource});
  action?.bindActor(id, {byte7d2: 8});
  const sources: SourceActorInputTestersSources = {world: worldSource, status: statusSource, mapping: mappingSource, charge,
    ...(action === undefined ? {} : {actionRequest: action})};
  const initial: Partial<SourceActorInputTestersBinding> = {byte595: 255, byte748: 0};
  const runtime = createSourceActorInputTestersRuntime(sources), bind = () => runtime.bindActor(id, initial);
  if (!options.defer) bind();
  return {id, actual, world, status, mapping, attribute, descriptorId, otherId, descriptor, otherDescriptor, hooks,
    sources, worldSource, mappingSource, chargeSources, initial, charge, action, runtime, bind,
    descriptorReads: () => descriptorReads, binding: () => runtime.getActorBinding(id),
    chargeBinding: () => charge.getActorBinding(id), run: () => runtime.updateActor(id),
    test: () => runtime.testDescriptor(id)};
}
/** Test-only observation of own-data destination checks. No callbacks enter the
 * source runtime; restoration is unconditional, including adversarial failures. */
function watchProperties(run: () => void, observe: (owner: object, key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object, key: PropertyKey) => {
    observe(owner, key); return original(owner, key);
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
export function runActorInputTestersSelfTests(): void {
  {
    const x = fixture({action: false});
    check(isSourceActorInputTestersRuntime(x.runtime) && !isSourceActorInputTestersRuntime({...x.runtime}), 'genuine brand');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()) && x.binding() !== x.initial, 'sealed copied partial binding');
    check(x.runtime.getActualActor(x.id) === x.actual && x.runtime.getWorldBinding(x.id) === x.world &&
      x.runtime.getStatusBinding(x.id) === x.status && x.runtime.getMappingActor(x.id) === x.mapping &&
      x.runtime.getAttributeBinding(x.id) === x.attribute && x.runtime.getChargeRuntime() === x.charge &&
      x.runtime.getChargeBinding(x.id) === x.chargeBinding() && x.runtime.getActionRuntime() === undefined &&
      x.runtime.getActionBinding(x.id) === undefined, 'canonical owner identities');
    equal(x.runtime.getSourceOwners(x.id).length, 2, 'only tester and charge extra owners');
    equal(x.runtime.getKnownDescriptorRecords().length, 0, 'no eager descriptor lookup');
    let stores = 0;
    watchProperties(() => equal(x.run(), 0, 'zero input chain returns native0'), (owner, key) => {
      if (owner !== x.binding() || key !== 'byte595') return;
      equal(x.binding().byte595, stores === 0 ? 255 : 0, 'previous independent595 store occurred');
      x.binding().byte595 = 237; stores++;
    });
    equal(stores, 6, 'all six separate mandatory595 stores'); equal(x.binding().byte595, 0, 'last store really executed');
    equal(x.actual.cmdButton, 19, 'zero chain leaves585 unchanged'); equal(x.descriptorReads(), 0, 'zero chain needs no descriptor');
    check(!hasIncompleteSourceActorInputTesters(x.actual), 'complete zero call clears marker');
  }
  {
    const x = fixture({defer: true, action: false}); delete x.initial.byte748; x.bind();
    absent(x.actual, 'stateFlagA'); absent(x.actual, 'prevActionIndex'); absent(x.actual, 'controlWord');
    absent(x.status, 'byte593'); absent(x.mapping, 'descriptor4b0'); equal(x.run(), 0, 'zero input is lazy except reached58e');
    const y = fixture({defer: true}); delete y.initial.byte595; y.bind(); rejects(y.run, 'byte595');
    check(!hasIncompleteSourceActorInputTesters(y.actual), 'missing first destination produces no marker');
    y.runtime.assertActorComplete(y.id);
  }
  for (const timer of [1, 6, 127]) {
    const x = fixture({defer: true}); delete x.initial.byte748; x.bind(); x.world.mode4a0 = 2; x.status.byte593 = timer;
    x.chargeBinding().byte58e = NaN; absent(x.actual, 'inputEdge5d4'); absent(x.actual, 'prevActionIndex');
    absent(x.mapping, 'descriptor4b0'); equal(x.run(), 1, 'mode2 positive signed593 genuine native1');
    equal(x.status.byte593, timer, 'positive593 unchanged'); equal(x.binding().byte595, 0, 'one clear before native1');
    equal(x.actual.cmdButton, 19, 'mode2 leaves585 unchanged');
  }
  for (const timer of [0, 128, 255]) {
    const x = fixture(); x.world.mode4a0 = 2; x.status.byte593 = timer; x.actual.inputEdge5d4 = 0x1000;
    equal(x.run(), 1, 'signed nonpositive593 reaches native1'); equal(x.status.byte593, 6, '593=6 before mode2 success');
    equal(x.actual.cmdButton, 19, 'first successful helper short circuits later command5');
  }
  {
    const x = fixture(); x.world.mode4a0 = 1; x.actual.inputEdge5d4 = 0x1000;
    rejects(x.run, 'pointer4a4'); equal(x.status.byte593, 6, '593 written before unsupported linked pointer');
    equal(x.actual.cmdButton, 19, 'linked boundary before command5'); equal(x.binding().byte595, 0, 'clear retained before linked boundary');
    x.world.mode4a0 = 0; x.actual.inputEdge5d4 = 0; rejects(x.run, 'known incomplete'); rejects(x.test, 'known incomplete');
    rejects(() => x.runtime.assertActorComplete(x.id), 'known incomplete');
    const another = createSourceActorInputTestersRuntime(x.sources); rejects(() => another.bindActor(Symbol(), {}), 'world id');
    rejects(() => another.bindActor(x.id, {}), 'already claimed');
  }
  {
    const x = fixture(); x.world.mode4a0 = 2; x.actual.controlWord = 2; x.actual.prevActionIndex = 5;
    x.status.byte593 = NaN; equal(x.run(), 0, 'prev584 gate skips593 and full helper falls through');
    const y = fixture(); y.world.mode4a0 = 2; y.actual.controlWord = 2; y.actual.prevActionIndex = 255;
    y.status.byte593 = 1; equal(y.run(), 1, 'signed previous255 is not5');
  }
  for (const [edge, command, charged] of [[0x1000, 5, true], [0x400, 3, true], [0x80, 2, false]] as const) {
    const x = fixture(); x.actual.inputEdge5d4 = edge;
    let observed = false;
    x.hooks.descriptor = () => {
      equal(x.actual.cmdButton, command, 'actual585 precedes descriptor');
      equal(x.binding().byte595, charged ? 1 : 0, 'source595 value at descriptor call'); observed = true; return x.descriptor;
    };
    equal(x.run(), 0, 'enabled action with sentinel naturally falls through'); check(observed, 'actual descriptor reached');
    equal(x.actual.cmdButton, command, 'selected canonical command'); equal(x.binding().byte595, 0, 'later helper clears charged595');
    equal(x.runtime.getKnownDescriptorRecords()[0], x.descriptor, 'same charge-owned descriptor registry');
    const y = fixture(); y.actual.inputEdge5d4 = edge; y.descriptor[0x2c + command] = 0;
    rejects(y.run, '80069fe0'); equal(y.binding().byte595, charged ? 1 : 0, 'active refusal retains exact prefix');
    check(hasIncompleteSourceActorInputTesters(y.actual), 'active refusal permanently marks prefix');
  }
  for (const [mask, edge] of [[0x20, 0x1000], [8, 0x400], [4, 0x80]] as const) {
    const x = fixture(); x.actual.inputEdge5d4 = edge; x.chargeBinding().byte58e = mask;
    equal(x.run(), 0, 'charge mask rejects selected action'); equal(x.actual.cmdButton, 19, 'disabled action has no585 store');
    equal(x.descriptorReads(), 0, 'disabled action skips descriptor');
  }
  for (const near of [0, 1, 2, 128, 255]) for (const disabled of [0, 1, 2, 3]) {
    const x = fixture(); x.actual.inputEdge5d4 = 0x40; x.binding().byte748 = near; x.chargeBinding().byte58e = disabled;
    equal(x.run(), 0, '69b10 sentinel or early0');
    const active = near !== 1 && (disabled & 2) === 0;
    equal(x.actual.cmdButton, active ? 1 : 19, '69b10 proximity and charge masks');
  }
  {
    const x = fixture({action: false}); x.actual.inputEdge5d4 = 0x40; x.chargeBinding().byte58e = 1;
    equal(x.run(), 0, 'retained58e bit1 skips absent7d2'); equal(x.actual.cmdButton, 1, '69b10 command1');
    const y = fixture({action: false}); y.actual.inputEdge5d4 = 0x40; rejects(y.run, 'requires genuine actionRequest');
    equal(y.actual.cmdButton, 19, 'missing7d2 refuses before585');
    const z = fixture(); z.actual.inputEdge5d4 = 0x40; z.action!.getActorBinding(z.id).byte7d2 = 0;
    equal(z.run(), 0, 'real7d2 zero rejects'); equal(z.actual.cmdButton, 19, '7d2 zero no585 store');
  }
  for (const near of [0, 1, 2, 128, 255]) for (const disabled of [0, 1, 2, 3]) {
    const x = fixture(); x.actual.inputEdge5d4 = 0x20; x.binding().byte748 = near; x.chargeBinding().byte58e = disabled;
    equal(x.run(), 0, '69a88 sentinel or mask0'); const command = near === 2 || (disabled & 1) !== 0 ? 1 : 0;
    equal(x.actual.cmdButton, command, '69a88 real contextual selection');
    equal(x.descriptorReads(), (disabled & (1 << command)) !== 0 ? 0 : 1, '69a88 selected58e mask before descriptor');
  }
  // Direct69dd0 has no fabricated0..5 action range. Raw8c coverage is the
  // admission extent; signed negative commands may address an earlier byte.
  for (const command of [0, 5, 6, 31, 32, 63, 64, 127, 212, 224, 255]) {
    const x = fixture(); x.actual.cmdButton = command; equal(x.test(), 0, 'signed descriptor sentinel');
    equal(x.descriptorReads(), 1, 'sentinel is one descriptor read'); equal(x.binding().byte595, 255, 'direct sentinel has no595 store');
    const y = fixture(); y.actual.cmdButton = command; y.descriptor[0x2c + (command << 24 >> 24)] = 2;
    y.actual.controlWord = 1; y.actual.stateFlagA = 128;
    const shift = (command << 24 >> 24) & 63, mask = shift >= 32 ? 0 : (1 << shift) >>> 0;
    if (((128 << 24 >> 24) & mask) !== 0) rejects(y.test, '8005c080');
    else equal(y.test(), 0, 'PPC low6 shift mask rejects');
    equal(y.binding().byte595, 255, '5c080 boundary before595=1');
    check(!hasIncompleteSourceActorInputTesters(y.actual), 'direct no-store refusal has no incomplete marker');
  }
  for (const command of [128, 160, 211]) {
    const x = fixture(); x.actual.cmdButton = command; rejects(x.test, 'outside explicitly owned');
    check(!hasIncompleteSourceActorInputTesters(x.actual), 'bad direct address has no source store');
  }
  for (const type of [2, 127, 128, 254]) {
    const x = fixture(); x.actual.cmdButton = 0; x.descriptor[0x2c] = type;
    equal(x.test(), 0, 'signed non0/non1 descriptor type returns0'); equal(x.descriptorReads(), 2, 'real descriptor reload');
  }
  for (const [type, boundary] of [[0, '80069fe0'], [1, '80069ea4']] as const) {
    const x = fixture(); x.actual.cmdButton = 0; x.descriptor[0x2c] = type; rejects(x.test, boundary);
    equal(x.descriptorReads(), 2, 'active type dispatch after second load');
    const y = fixture(); y.actual.cmdButton = 0; y.descriptor[0x2c] = type; y.actual.controlWord = 1; y.actual.stateFlagA = 0;
    equal(y.test(), 0, 'state57a zero genuinely rejects before active dispatch'); equal(y.descriptorReads(), 1, 'mask rejection skips reload');
  }
  {
    const x = fixture(); x.actual.cmdButton = 0; x.descriptor[0x2c] = 2; x.otherDescriptor[0x2d] = 1;
    x.hooks.descriptor = () => {
      if (x.descriptorReads() === 1) {x.actual.cmdButton = 1; x.mapping.descriptor4b0 = x.otherId; return x.descriptor;}
      return x.otherDescriptor;
    };
    rejects(x.test, '80069ea4'); equal(x.descriptorReads(), 2, 'second585 and pointer really reload');
    equal(x.runtime.getKnownDescriptorRecords().length, 2, 'charge tracks both pointer identities');
  }
  {
    const x = fixture(); x.actual.cmdButton = 0; equal(x.test(), 0, 'establish descriptor identity');
    x.hooks.descriptor = () => [...x.descriptor]; rejects(x.test, 'owner changed');
    const y = fixture(); y.actual.cmdButton = 0; y.mapping.descriptor4b0 = y.otherId;
    y.hooks.descriptor = () => y.descriptor; equal(y.test(), 0, 'first identity adopts array');
    y.mapping.descriptor4b0 = y.descriptorId; rejects(y.test, 'aliases');
    const z = fixture(); z.actual.cmdButton = 0; z.hooks.descriptor = () => Promise.resolve(z.descriptor);
    rejects(z.test, 'synchronous');
  }
  // Reached instruction ordering: the first595 store precedes every source
  // scalar; reads needed by later helpers cannot be hoisted into admission.
  {
    const x = fixture(); absent(x.world, 'mode4a0'); rejects(x.run, 'mode4a0');
    equal(x.binding().byte595, 0, 'first595 survives missingmode');
    const y = fixture(); y.world.mode4a0 = 2; y.status.byte593 = 0; y.actual.inputEdge5d4 = 0x1000;
    readonly(y.status, 'byte593'); rejects(y.run, 'byte593: non-writable'); equal(y.binding().byte595, 0, 'clear before readonly593');
    const z = fixture(); z.actual.inputEdge5d4 = 0x1000; readonly(z.actual, 'cmdButton');
    rejects(z.run, 'cmdButton: non-writable'); equal(z.binding().byte595, 0, 'command store beforecharged595');
  }
  {
    const x = fixture(); x.actual.cmdButton = 0; absent(x.mapping, 'descriptor4b0'); absent(x.actual, 'cmdButton');
    rejects(x.test, 'cmdButton'); equal(x.descriptorReads(), 0, '585 load before pointer');
    const y = fixture(); y.actual.cmdButton = 0; absent(y.actual, 'controlWord'); equal(y.test(), 0, 'sentinel beforecontrol');
    const z = fixture(); z.actual.cmdButton = 0; z.descriptor[0x2c] = 2; z.actual.controlWord = 1; absent(z.actual, 'stateFlagA');
    rejects(z.test, 'stateFlagA'); equal(z.descriptorReads(), 1, '57a before reload');
  }
  {
    const x = fixture(); x.actual.inputEdge5d4 = 0x40; x.binding().byte748 = 1; x.chargeBinding().byte58e = 0;
    // Earlier masked testers must read58e, but69b10 itself rejects748 before its58e read.
    let loads = 0;
    watchProperties(() => equal(x.run(), 0, '748 gate skips69b10 charge read'), (owner, key) => {
      if (owner === x.chargeBinding() && key === 'byte58e') loads++;
    });
    equal(loads, 3, 'only c50/bf0/b98 read58e on748 rejection');
    const y = fixture(); y.actual.inputEdge5d4 = 0x40; y.chargeBinding().byte58e = 1;
    let reads = 0;
    watchProperties(() => equal(y.run(), 0, '69b10 retained load'), (owner, key) => {
      if (owner === y.chargeBinding() && key === 'byte58e') reads++;
    });
    equal(reads, 4, 'three earlier plus one69b10 load, never duplicated58e');
  }
  {
    const x = fixture(); x.actual.inputEdge5d4 = 0x1000;
    let destinations = 0;
    watchProperties(() => rejects(x.run, 'byte595: non-writable'), (owner, key) => {
      if (owner === x.binding() && key === 'byte595' && ++destinations === 3) readonly(owner, key);
    });
    equal(x.actual.cmdButton, 5, '585 store survives readonly charged595');
    equal(x.binding().byte595, 0, 'prior independent clear survives failedcharged595');
    equal(x.descriptorReads(), 0, 'failedcharged595 before descriptor');
    const y = fixture(); y.world.mode4a0 = 2; y.actual.inputEdge5d4 = 0x1000;
    let modeReads = 0;
    watchProperties(() => rejects(y.run, 'pointer4a4'), (owner, key) => {
      if (owner === y.world && key === 'mode4a0' && ++modeReads === 2) y.world.mode4a0 = 1;
    });
    equal(y.status.byte593, 6, 'mode reloaded after actual593 store');
    equal(modeReads, 2, 'two source mode loads');
  }
  for (const near of [0, 2]) {
    const x = fixture(); x.actual.inputEdge5d4 = 0x20; x.binding().byte748 = near;
    let reads = 0;
    watchProperties(() => equal(x.run(), 0, '69a88 lazy first58e'), (owner, key) => {
      if (owner === x.chargeBinding() && key === 'byte58e') reads++;
    });
    equal(reads, near === 2 ? 4 : 5, '748eq2 skips first58e but never final58e reload');
  }
  {
    const x = fixture(); x.actual.cmdButton = 0; x.actual.controlWord = 1; x.actual.stateFlagA = 1;
    x.descriptor[0x2c] = 2;
    x.hooks.descriptor = () => {x.actual.cmdButton = 32; return x.descriptor;};
    rejects(x.test, '8005c080'); equal(x.descriptorReads(), 1, '57a mask uses retained first signed585');
    const y = fixture(); y.actual.cmdButton = 0; y.descriptor.length = 0x2c;
    rejects(y.test, 'outside explicitly owned');
    const z = fixture(); z.actual.cmdButton = 0; delete z.descriptor[0x2c]; rejects(z.test, 'own data property');
    const g = fixture(); g.actual.cmdButton = 0;
    Object.defineProperty(g.descriptor, String(0x2c), {get() {throw Error('array getter invoked');}});
    rejects(g.test, 'own data property');
    const n = fixture(); n.actual.cmdButton = 0; (n.mapping as {descriptor4b0: symbol | null}).descriptor4b0 = null;
    rejects(n.test, 'non-null');
  }
  for (const hook of ['world', 'worldBinding', 'worldMapping', 'status', 'statusActor', 'statusWorld', 'statusMapping',
    'statusAttribute', 'mapping'] as const) {
    const x = fixture(); x.hooks[hook] = () => ({}); rejects(x.run, 'owner changed');
    equal(x.binding().byte595, 255, 'identity refusal before stores');
  }
  for (const key of ['byte595', 'byte748', 'byte58e', 'byte593', 'byte7d2', 'byte585', 'field748', 'flags5e0']) {
    const x = fixture({defer: true}); Object.defineProperty(x.actual, key, {value: undefined}); rejects(x.bind, 'competing');
    const y = fixture(); Object.defineProperty(y.actual, key, {value: undefined}); rejects(y.run, 'competing');
  }
  {
    const x = fixture({defer: true}); (x.initial as Record<string, unknown>).cmdButton = 0; rejects(x.bind, 'competing');
    const y = fixture({defer: true}); y.hooks.statusWorld = () => y.status; rejects(y.bind, 'owner changed');
    const z = fixture(); z.hooks.world = () => {try {z.run();} catch {} return z.actual;};
    rejects(z.run, 'caught same-runtime'); check(!hasIncompleteSourceActorInputTesters(z.actual), 'prestore caught reentry has no marker');
    const q = fixture(); q.actual.inputEdge5d4 = 0x1000;
    q.hooks.descriptor = () => {try {q.run();} catch {} return q.descriptor;};
    rejects(q.run, 'caught same-runtime'); equal(q.actual.cmdButton, 5, 'poststore reentry retains585');
    rejects(q.run, 'known incomplete');
  }
  {
    let callback: (() => void) | undefined;
    const x = fixture({actualProxy: {set(target, key, value) {
      const result = Reflect.set(target, key, value); if (key === 'cmdButton') callback?.(); return result;
    }}});
    callback = () => {try {x.run();} catch {}};
    x.actual.inputEdge5d4 = 0x1000; rejects(x.run, 'caught same-runtime');
    equal(x.actual.cmdButton, 5, 'adversarial set trap completed store');
    check(hasIncompleteSourceActorInputTesters(x.actual), 'marker before caught reentry check');
    callback = undefined; rejects(x.test, 'known incomplete');
  }
  {
    const x = fixture(); const original = x.worldSource.getActualActor;
    x.worldSource.getActualActor = () => {throw Error('replacement must not run');};
    equal(x.run(), 0, 'captured method and receiver retained'); x.worldSource.getActualActor = original;
    const y = fixture(); Object.defineProperty(y.actual, 'inputEdge5d4', {get() {throw Error('getter invoked');}});
    rejects(y.run, 'own data property');
    for (const value of [-1, 256, 0.5, NaN, Infinity]) {
      const z = fixture(); z.binding().byte748 = value; z.actual.inputEdge5d4 = 0x20;
      rejects(z.run, 'byte748: unsigned');
    }
    const bad = fixture({defer: true}); bad.sources.charge = {...bad.charge};
    rejects(() => createSourceActorInputTestersRuntime(bad.sources), 'genuine');
    const action = fixture({defer: true}); action.sources.actionRequest = {...action.action!};
    rejects(() => createSourceActorInputTestersRuntime(action.sources), 'genuine');
  }
}
