import {createSourceObjectAllocationRuntime, isSourceObjectAllocationRuntime,
  type SourceAllocationBytes, type SourceObjectAllocationActorBinding,
  type SourceObjectAllocationSources, type SourceObjectInteriorTarget} from './source-object-allocation.js';
import {createRomActor} from './actor.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[source-object-allocation-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment) && message.includes('offline execution aborted'), `expected ${fragment}, got ${message || 'success'}`);
}
function bytes(size: number, initial = 0xa5): SourceAllocationBytes {
  return Object.fromEntries(Array.from({length: size}, (_, index) => [index, initial]));
}
/** Explicit synthetic live pool setup. Sizes/type/callback/group8 match the
 * independently authenticated source metadata. Counts/list identities are test
 * inputs, not a claim of retail heap initialization. */
function fixture(options: {objects?: number; descriptors?: number; deferred?: boolean; hit?: boolean} = {}) {
  const poolIndex = options.hit ? 4 : 3, objectSize = options.hit ? 0x1c0 : 0x2e4, groupIndex = options.hit ? 48 : 8;
  const actorId = Symbol('actor'), caller = Symbol('allocator caller'), actual = createRomActor(); actual.slot = 0;
  const objectA = Symbol('object A'), objectB = Symbol('object B'), descriptorA = Symbol('descriptor A'), descriptorB = Symbol('descriptor B');
  const objectBytesA = bytes(objectSize), objectBytesB = bytes(objectSize), descriptorBytesA = bytes(0x2c), descriptorBytesB = bytes(0x2c);
  const hooks: {getActor?: () => typeof actual} = {};
  const world = {getActualActor(id: symbol) {
    check(this === world && id === actorId, 'actual actor owner uses captured receiver/identity');
    return hooks.getActor ? hooks.getActor() : actual;
  }};
  const objectPool = {head: objectA as symbol | null, tail: objectB as symbol | null, count: options.objects ?? 2};
  const descriptorPool = {freeHead: descriptorA as symbol | null, activeHead: null as symbol | null,
    count: options.descriptors ?? 2, initCallback14: 0x80006f60};
  const group = {head: null as symbol | null, tail: null as symbol | null};
  const sources: SourceObjectAllocationSources = {world, objectPools: {[poolIndex]: objectPool}, descriptorPools: {0: descriptorPool},
    groups: {[groupIndex]: group}, typeSizes: {[poolIndex]: objectSize}, groupEligibility: {[groupIndex]: options.hit ? 26 : 16}};
  const runtime = createSourceObjectAllocationRuntime(sources);
  for (const [id, raw] of [[objectA, objectBytesA], [objectB, objectBytesB]] as const) runtime.registerObject(id, raw);
  for (const [id, raw] of [[descriptorA, descriptorBytesA], [descriptorB, descriptorBytesB]] as const) runtime.registerDescriptor(id, raw);
  runtime.writeU8(objectA, 2, poolIndex); runtime.writeU8(objectB, 2, poolIndex);
  runtime.writePointer(objectA, 4, objectB); runtime.writePointer(objectB, 4, null);
  runtime.writePointer(descriptorA, 0, descriptorB); runtime.writePointer(descriptorB, 0, null);
  const initial: Partial<SourceObjectAllocationActorBinding> = {byte83: 1};
  const bind = () => {runtime.bindActor(actorId, initial); runtime.claimActor(actorId, caller);};
  if (!options.deferred) bind();
  return {actorId, caller, actual, objectA, objectB, descriptorA, descriptorB, objectBytesA, objectBytesB,
    descriptorBytesA, descriptorBytesB, hooks, world, objectPool, descriptorPool, group, sources, runtime, initial, bind,
    run: () => options.hit ? runtime.allocateProjectileHit(actorId, caller) : runtime.allocateProjectile(actorId, caller)};
}
export function runSourceObjectAllocationSelfTests(): void {
  {
    const x = fixture();
    check(isSourceObjectAllocationRuntime(x.runtime) && Object.isFrozen(x.runtime), 'genuine frozen runtime');
    for (const forged of [{...x.runtime}, Object.create(x.runtime), null, {}, undefined])
      check(!isSourceObjectAllocationRuntime(forged), 'runtime brand cannot be forged');
    equal(x.runtime.getObject(x.objectA), x.objectBytesA, 'object backing is not copied');
    equal(x.runtime.getDescriptor(x.descriptorA), x.descriptorBytesA, 'descriptor backing is not copied');
    equal(x.runtime.getPointerTarget(x.actorId), x.actual, 'actor pointer resolves canonical actual');
    equal(x.runtime.getPointerIdentity(x.actual), x.actorId, 'actual pointer resolves same identity');
    equal(x.runtime.getActualActor(x.actorId), x.actual, 'same source actor');
    equal(x.runtime.getActorBinding(x.actorId).byte83, 1, 'only explicit missing83 storage');
    check(Object.isSealed(x.runtime.getActorBinding(x.actorId)), 'new missing actor field sealed');
    x.initial.byte83 = 0; equal(x.runtime.getActorBinding(x.actorId).byte83, 1, 'initial83 is not live');
    rejects(() => x.runtime.claimActor(x.actorId, Symbol()), 'already claimed');
    rejects(() => x.runtime.allocateProjectile(x.actorId, Symbol()), 'exclusive actor caller capability');
    equal(x.objectPool.count, 2, 'forged caller has no effects');
    rejects(() => x.runtime.registerExternal(Symbol(), x.actual), 'different identity');
    rejects(() => x.runtime.registerObject(Symbol(), x.objectBytesA), 'owner aliases');
    rejects(() => x.runtime.getPointerIdentity({}), 'has not been registered');
  }
  {
    const x = fixture();
    equal(x.run(), x.objectA, 'real nonnull source callback completes positive allocation');
    equal(x.objectPool.count, 1, 'actual object count decremented');
    equal(x.objectPool.head, x.objectB, 'actual free head popped');
    equal(x.objectPool.tail, x.objectB, 'nonempty free tail retained');
    equal(x.group.head, x.objectA, 'same allocated object inserted at group head');
    equal(x.group.tail, x.objectA, 'empty group tail inserted');
    equal(x.runtime.readU8(x.objectA, 2), 3, 'source type restored after memset');
    equal(x.runtime.readU8(x.objectA, 3), 3, 'source pool byte restored');
    equal(x.runtime.readU8(x.objectA, 1), 8, 'source group byte');
    equal(x.runtime.readU8(x.objectA, 0x83), 16, 'source group classification');
    equal(x.runtime.readU8(x.objectA, 0x85), 255, 'source sentinel');
    equal(x.runtime.readPointer(x.objectA, 4), null, 'group previous null');
    equal(x.runtime.readPointer(x.objectA, 8), null, 'group next null');
    equal(x.runtime.readU32(x.objectA, 0x2e0), 0, 'real memset includes last supplied source-size bytes');
    equal(x.runtime.readU8(x.objectB, 0x2e3), 0xa5, 'unallocated record never zeroed');
    equal(x.descriptorPool.count, 1, 'descriptor count decremented');
    equal(x.descriptorPool.freeHead, x.descriptorB, 'descriptor free list popped');
    equal(x.descriptorPool.activeHead, x.descriptorA, 'descriptor inserted into active list');
    equal(x.runtime.readPointer(x.descriptorA, 0), null, 'active next null');
    equal(x.runtime.readPointer(x.descriptorA, 4), null, 'active previous null');
    equal(x.runtime.readU8(x.descriptorA, 9), 1, 'descriptor marked active');
    equal(x.runtime.readU8(x.descriptorA, 10), 0, 'descriptor secondary byte cleared');
    equal(x.runtime.readU32(x.descriptorA, 0xc), 0, '06d4c +c store executes after actual callback return');
    for (const offset of [0x20, 0x24, 0x28])
      equal(x.runtime.readU32(x.descriptorA, offset), 0, 'real06f60 initializer clears each source word');
    equal(x.runtime.readU32(x.descriptorA, 0x1c), 0xa5a5a5a5, 'callback does not fake descriptor-wide memset');
    equal(x.runtime.readPointer(x.objectA, 0xe0), x.descriptorA, 'same actual descriptor attached after callback returns');
    for (let offset = 0xe4; offset <= 0xfc; offset += 4)
      equal(x.runtime.readPointer(x.objectA, offset), null, 'remaining seven source descriptor slots cleared');
    equal(x.runtime.readU8(x.objectA, 0x99), 1, 'descriptor count byte written last');
    equal(x.runtime.assertActorComplete(x.actorId), undefined, 'completed allocation leaves actual owner usable');
    equal(x.run(), x.objectB, 'second real allocation consumes remaining records');
    equal(x.run(), null, 'next source count gate fails honestly after real consumption');
    equal(x.objectPool.count, 0, 'two successful source object pops');
    equal(x.group.head, x.objectB, 'second object now group head');
    equal(x.group.tail, x.objectA, 'first object remains group tail');
    equal(x.runtime.readPointer(x.objectA, 4), x.objectB, 'first object back-link changed');
  }
  {
    for (const rawCount of [0, 0x8000, 0x8001, 0xffff]) {
      const x = fixture({descriptors: rawCount});
      Object.defineProperty(x.sources, 'objectPools', {get() {throw Error('unreached object pool');}});
      Object.defineProperty(x.actual, 'slot', {get() {throw Error('unreached slot');}});
      equal(x.run(), null, `signed descriptor count gate ${rawCount}`);
      equal(x.objectPool.count, 2, 'count gate leaves object pool alone');
      equal(x.descriptorPool.count, rawCount, 'gate does not rewrite count');
    }
    const x = fixture(); x.objectPool.head = null;
    Object.defineProperty(x.objectPool, 'count', {get() {throw Error('unreached object count');}});
    Object.defineProperty(x.sources, 'typeSizes', {get() {throw Error('unreached type table');}});
    equal(x.run(), null, 'null free object head without count/type/actor83 loads');
    equal(x.descriptorPool.count, 2, 'null object never pops descriptor');
  }
  {
    const x = fixture({objects: 0}); x.runtime.writePointer(x.objectA, 4, null);
    equal(x.run(), x.objectA, 'actual initializer executes');
    equal(x.objectPool.count, 0xffff, 'object count uses unsigned16 wrap, never host capacity veto');
    equal(x.objectPool.head, null, 'last free head null'); equal(x.objectPool.tail, null, 'last free tail cleared');
    const y = fixture(); y.objectPool.head = Symbol('unknown source head');
    rejects(y.run, 'unknown/non-owned object identity');
    equal(y.objectPool.count, 1, 'count store precedes unknown node dereference');
    equal(y.objectPool.tail, y.objectB, 'unknown head does not clear tail');
  }
  {
    const x = fixture(); x.group.head = x.objectB; x.group.tail = x.objectB;
    x.runtime.writePointer(x.objectA, 4, null); x.objectPool.tail = x.objectA;
    x.descriptorPool.activeHead = x.descriptorB; x.runtime.writePointer(x.descriptorA, 0, null);
    equal(x.run(), x.objectA, 'actual initializer executes');
    equal(x.group.head, x.objectA, 'nonempty group front updated'); equal(x.group.tail, x.objectB, 'nonempty group tail retained');
    equal(x.runtime.readPointer(x.objectA, 8), x.objectB, 'new group next retains same prior object');
    equal(x.runtime.readPointer(x.objectB, 4), x.objectA, 'previous group head back-link updated');
    equal(x.descriptorPool.activeHead, x.descriptorA, 'new descriptor active head');
    equal(x.runtime.readPointer(x.descriptorA, 4), x.descriptorB, 'new descriptor previous active head');
    equal(x.runtime.readPointer(x.descriptorB, 0), x.descriptorA, 'old descriptor forward link updated');
  }
  {
    const x = fixture();
    Object.defineProperty(x.objectPool, 'count', {value: 2, writable: false});
    rejects(x.run, 'count: non-writable'); equal(x.objectPool.head, x.objectA, 'count fault before head load/store');
    equal(x.runtime.readU8(x.objectA, 0x100), 0xa5, 'count fault before memset');
    const y = fixture(); Object.defineProperty(y.objectBytesA, '4', {get() {throw Error('no getter execution');}});
    rejects(y.run, '4: own data property'); equal(y.objectPool.count, 1, 'node read fault retains count decrement');
    equal(y.objectPool.head, y.objectA, 'head not replaced before successful node next read');
    const z = fixture(); delete z.objectBytesA[0x100];
    rejects(z.run, '256: own data property');
    equal(z.objectPool.head, z.objectB, 'memset fault retains real pop');
    equal(z.runtime.readU8(z.objectA, 0xff), 0, 'host bounded byte memset earlier effects retained');
    equal(z.runtime.readU8(z.objectA, 0x101), 0xa5, 'host memset stops at missing byte');
    equal(z.runtime.readU8(z.objectA, 2), 0, 'source type restoration waits until memset returns');
    equal(z.descriptorPool.count, 2, 'memset failure never reaches descriptor allocation');
  }
  {
    const x = fixture({deferred: true}); delete x.initial.byte83; x.bind();
    rejects(x.run, 'byte83: own data property'); equal(x.objectPool.count, 1, 'lazy83 fault after object pop');
    equal(x.runtime.readU8(x.objectA, 0x85), 255, 'lazy83 fault after sentinel store');
    equal(x.group.head, null, 'lazy83 fault before group insertion');
    const y = fixture(); y.runtime.getActorBinding(y.actorId).byte83 = 0; y.actual.slot = 255;
    equal(y.run(), y.objectA, 'actual initializer executes after remap');
    equal(y.runtime.readU8(y.objectA, 1), 8, 'rawff slot sign-extends to minus1 and remaps to8');
    const z = fixture(); z.runtime.getActorBinding(z.actorId).byte83 = 0; z.actual.slot = 128;
    rejects(z.run, '-119: own data property');
    equal(z.runtime.readU8(z.objectA, 1), 137, 'signed slot remap stored as raw byte before missing group lookup');
    equal(z.group.head, null, 'missing actual negative group does not fall back to8');
  }
  {
    for (let slot = 0; slot <= 5; slot++) {
      const x = fixture(); x.runtime.getActorBinding(x.actorId).byte83 = 0; x.actual.slot = slot;
      Object.defineProperty(x.sources, 'groups', {value: {[slot + 9]: x.group}});
      Object.defineProperty(x.sources, 'groupEligibility', {value: {[slot + 9]: 16}});
      equal(x.run(), x.objectA, 'all six authenticated ordinary actor remap slots');
      equal(x.runtime.readU8(x.objectA, 1), slot + 9, 'actual slot selects exact group9..14');
      equal(x.group.head, x.objectA, 'remapped real group holds same object');
    }
    for (const byte83 of [1, 127, 128, 255]) {
      const x = fixture(); x.runtime.getActorBinding(x.actorId).byte83 = byte83;
      Object.defineProperty(x.actual, 'slot', {get() {throw Error('nonzero83 must not read slot');}});
      equal(x.run(), x.objectA, 'signed nonzero83 bypasses slot read');
      equal(x.runtime.readU8(x.objectA, 1), 8, 'nonzero83 keeps original group8');
    }
    const x = fixture(); Object.defineProperty(x.sources, 'typeSizes', {value: {3: 0x2e0}});
    rejects(x.run, 'only authenticated object pool3 type3 size0x2e4');
    equal(x.objectPool.count, 1, 'size admission refuses after actual pop');
    equal(x.runtime.readU8(x.objectA, 0x100), 0xa5, 'wrong size never causes shortened fake memset');
    const y = fixture(); Object.defineProperty(y.sources, 'groupEligibility', {value: {8: 0}});
    rejects(y.run, 'only authenticated group8..14 classification16');
    equal(y.runtime.readU8(y.objectA, 0x83), 0, 'wrong classification not fabricated');
    equal(y.runtime.readU8(y.objectA, 0x85), 255, 'classification validation occurs after source sentinel');
    const signed = fixture(); signed.runtime.writeU8(signed.objectA, 2, 128);
    rejects(signed.run, '-128: own data property');
    equal(signed.objectPool.count, 1, 'type sign extension follows real free-pop effects');
    equal(signed.runtime.readU8(signed.objectA, 2), 128, 'missing signed type table faults before memset');
    const z = fixture(); z.objectBytesA[0x2e4] = 0x7f;
    equal(z.run(), z.objectA, 'explicit backing may contain bytes beyond selected type size');
    equal(z.objectBytesA[0x2e4], 0x7f, 'memset stops at exact authenticated size');
  }
  {
    for (const callback of [0, 0x80006f64, 0xffffffff]) {
      const x = fixture(); x.descriptorPool.initCallback14 = callback;
      rejects(x.run, 'outside authenticated80006f60 metadata');
      equal(x.group.head, x.objectA, 'callback metadata failure retains real allocated group node');
      equal(x.descriptorPool.activeHead, x.descriptorA, 'callback metadata failure retains descriptor active insert');
      equal(x.runtime.readU32(x.descriptorA, 0xc), 0xa5a5a5a5, '06d4c not reached on callback refusal');
      equal(x.runtime.readPointer(x.objectA, 0xe0), null, 'descriptor not attached across refused callback');
      equal(x.runtime.readU8(x.objectA, 0x99), 0, 'descriptor count not fabricated after callback refusal');
      rejects(x.run, 'permanently incomplete allocation owner');
      rejects(() => x.runtime.writeU8(x.objectA, 0, 1), 'permanently incomplete allocation owner');
    }
    const x = fixture(); Object.defineProperty(x.descriptorBytesA, '36', {value: 0xa5, writable: false});
    rejects(x.run, '36: non-writable');
    equal(x.runtime.readU32(x.descriptorA, 0x20), 0, 'callback first word store retained');
    equal(x.runtime.readU32(x.descriptorA, 0x24), 0xa5a5a5a5, 'callback second store preflight atomic');
    equal(x.runtime.readU32(x.descriptorA, 0x28), 0xa5a5a5a5, 'callback third store not reached');
    equal(x.runtime.readU32(x.descriptorA, 0x0c), 0xa5a5a5a5, 'wrapper store awaits callback completion');
    equal(x.descriptorPool.count, 1, 'descriptor pop never rolled back');
  }
  {
    const x = fixture();
    const old = x.runtime.readU32(x.objectA, 0x100);
    Object.defineProperty(x.objectBytesA, '258', {value: 0xa5, writable: false});
    rejects(() => x.runtime.writeU32(x.objectA, 0x100, 0x12345678), '258: non-writable');
    equal(x.runtime.readU32(x.objectA, 0x100), old, 'source scalar width preflight is atomic');
    x.runtime.writeU16(x.objectA, 0x120, 0xffff); equal(x.runtime.readS16(x.objectA, 0x120), -1, 'BE signed16');
    x.runtime.writeU8(x.objectA, 0x123, 128); equal(x.runtime.readS8(x.objectA, 0x123), -128, 'signed8');
    x.runtime.writeF32(x.objectA, 0x124, -0); equal(x.runtime.readF32(x.objectA, 0x124), -0, 'float negative zero preserved');
    equal(x.runtime.readU32(x.objectA, 0x124), 0x80000000, 'canonical float byte bits');
    const external = {}, externalId = Symbol('external'); x.runtime.registerExternal(externalId, external);
    x.runtime.writePointer(x.objectA, 0xc8, externalId);
    equal(x.runtime.readPointer(x.objectA, 0xc8), externalId, 'external pointer same opaque identity');
    equal(x.runtime.getPointerTarget(externalId), external, 'external pointer exact canonical object');
    rejects(() => x.runtime.writeU16(x.objectA, 1, 0), 'unaligned');
    rejects(() => x.runtime.writeU32(x.objectA, 0xffff, 0), 'byte range');
    rejects(() => x.runtime.writeF32(x.objectA, 0x124, 0.1), 'finite exact source float32');
    x.runtime.writeU32(x.objectA, 0x128, 0x7f800000); rejects(() => x.runtime.readF32(x.objectA, 0x128), 'finite exact');
  }
  {
    const x = fixture(); x.hooks.getActor = () => {try {x.run();} catch {} return x.actual;};
    rejects(x.run, 'caught same-runtime reentry');
    equal(x.objectPool.count, 2, 'caught owner reentry before first allocation effect');
    const y = fixture();
    Object.defineProperty(y.sources, 'typeSizes', {value: new Proxy(y.sources.typeSizes, {
      getOwnPropertyDescriptor(target, key) {
        if (key === '3') {try {y.run();} catch {}}
        return Reflect.getOwnPropertyDescriptor(target, key);
      },
    })});
    // Proxies are outside admitted inputs; caught descriptor reentry cannot
    // evade the poison check even if such a value is presented adversarially.
    rejects(y.run, 'caught same-runtime reentry');
    equal(y.objectPool.count, 1, 'caught later reentry retains count store');
    equal(y.objectPool.head, y.objectB, 'caught later reentry retains free head store');
    equal(y.runtime.readU8(y.objectA, 2), 3, 'type-size hook precedes memset');
    rejects(y.run, 'permanently incomplete allocation owner');
  }
  {
    const x = fixture({descriptors: 0}); equal(x.run(), null, 'initial source gate claims actual pool owner');
    Object.defineProperty(x.sources, 'descriptorPools', {value: {0: {count: 0}}});
    rejects(x.run, 'owner changed its actual record');
    equal(x.objectPool.count, 2, 'replaced pool owner cannot synthesize capacity');
    const y = fixture(); y.hooks.getActor = () => createRomActor();
    rejects(y.run, 'world actor owner changed its actual record');
    equal(y.objectPool.count, 2, 'replacement actual actor has no allocation effect');
    const z = fixture({descriptors: 0}); equal(z.run(), null, 'claim shared descriptor pool');
    const otherActual = createRomActor(), otherId = Symbol(), caller = Symbol();
    const other = createSourceObjectAllocationRuntime({...z.sources, world: {getActualActor: () => otherActual}});
    other.bindActor(otherId, {byte83: 1}); other.claimActor(otherId, caller);
    rejects(() => other.allocateProjectile(otherId, caller), 'already claimed allocation storage');
    equal(z.descriptorPool.count, 0, 'shared pool cannot be owned by another runtime');
  }
  {
    const x = fixture(); Object.defineProperty(x.group, 'head', {value: null, writable: false});
    rejects(x.run, 'head: non-writable');
    equal(x.objectPool.count, 1, 'readonly group head retains pool pop');
    equal(x.runtime.readU8(x.objectA, 0x83), 16, 'group head failure follows classification store');
    equal(x.descriptorPool.count, 2, 'group head failure precedes descriptor allocation');
    const y = fixture(); Object.defineProperty(y.descriptorPool, 'count', {value: 2, writable: false});
    rejects(y.run, 'count: non-writable');
    equal(y.group.head, y.objectA, 'readonly descriptor count follows actual group insertion');
    equal(y.descriptorPool.freeHead, y.descriptorA, 'descriptor free pop waits for count store');
    const z = fixture(); Object.defineProperty(z.descriptorBytesA, '9', {value: 0xa5, writable: false});
    rejects(z.run, '9: non-writable');
    equal(z.descriptorPool.count, 1, 'descriptor9 failure retains count decrement');
    equal(z.descriptorPool.freeHead, z.descriptorB, 'descriptor9 failure retains free pop');
    equal(z.runtime.readPointer(z.descriptorA, 0), null, 'descriptor9 failure retains node0 zero');
    equal(z.descriptorPool.activeHead, null, 'descriptor9 failure precedes active insertion');
  }
  {
    const x = fixture(); x.runtime.markActorIncomplete(x.actorId, x.caller);
    equal(x.runtime.markActorIncomplete(x.actorId, x.caller), undefined, 'incomplete marking idempotent');
    rejects(x.run, 'permanently incomplete allocation owner');
    equal(x.objectPool.count, 2, 'parent spawn failure prevents standalone reallocations');
    const other = createSourceObjectAllocationRuntime({...x.sources, world: {...x.world}});
    rejects(() => other.registerObject(Symbol(), x.objectBytesA), 'already claimed allocation storage');
    const y = fixture({deferred: true}); Object.defineProperty(y.actual, 'byte83', {value: 1});
    rejects(y.bind, 'competing source actor storage');
  }
  {
    const x = fixture({hit: true, descriptors: 0});
    // Only the signed availability count is reached for requested descriptor0.
    Object.defineProperty(x.descriptorPool, 'count', {value: 0, writable: false});
    for (const key of ['freeHead', 'activeHead', 'initCallback14'])
      Object.defineProperty(x.descriptorPool, key, {get() {throw Error(`unreached HIT descriptor ${key}`);}});
    x.objectBytesA[0x1c0] = 0x7f;
    equal(x.run(), x.objectA, 'HIT allocation succeeds with actual descriptor count zero');
    equal(x.runtime.getObject(x.objectA), x.objectBytesA, 'HIT retains exact canonical record');
    equal(x.objectPool.count, 1, 'real pool4 count decremented');
    equal(x.objectPool.head, x.objectB, 'real pool4 head popped');
    equal(x.objectPool.tail, x.objectB, 'nonempty pool4 tail retained');
    equal(x.runtime.readU8(x.objectA, 2), 4, 'HIT actual type restored');
    equal(x.runtime.readU8(x.objectA, 3), 4, 'HIT actual pool byte restored');
    equal(x.runtime.readU8(x.objectA, 1), 48, 'HIT requested group48');
    equal(x.runtime.readU8(x.objectA, 0x83), 26, 'HIT group classification26');
    equal(x.runtime.readU8(x.objectA, 0x85), 255, 'HIT sentinel retained');
    equal(x.runtime.readU32(x.objectA, 0x1bc), 0, 'HIT memset reaches exact type4 end');
    equal(x.objectBytesA[0x1c0], 0x7f, 'HIT memset does not clear byte beyond1c0');
    equal(x.runtime.readU8(x.objectB, 0x1bf), 0xa5, 'other free HIT storage never reset');
    equal(x.group.head, x.objectA, 'HIT group canonical head');
    equal(x.group.tail, x.objectA, 'HIT empty group canonical tail');
    equal(x.runtime.readPointer(x.objectA, 4), null, 'HIT previous link zero');
    equal(x.runtime.readPointer(x.objectA, 8), null, 'HIT next link zero');
    equal(x.descriptorPool.count, 0, 'HIT descriptor availability not consumed');
    equal(x.runtime.readU8(x.objectA, 0x99), 0, 'HIT descriptor byte only memset, never fabricated count1');
    equal(x.runtime.readU32(x.descriptorA, 0x20), 0xa5a5a5a5, 'HIT never executes descriptor initializer');
    equal(x.run(), x.objectB, 'same zero descriptor count permits second real HIT allocation');
    equal(x.runtime.readPointer(x.objectB, 8), x.objectA, 'HIT nonempty new next link');
    equal(x.runtime.readPointer(x.objectA, 4), x.objectB, 'HIT nonempty prior previous link');
    equal(x.group.tail, x.objectA, 'HIT nonempty tail unchanged');
    equal(x.objectPool.head, null, 'last HIT pop clears free head');
    equal(x.objectPool.tail, null, 'last HIT pop clears free tail');
    equal(x.run(), null, 'HIT real exhausted head returns null');
    equal(x.runtime.assertActorComplete(x.actorId), undefined, 'successful HIT allocations leave owner complete');
  }
  {
    for (const rawCount of [0x8000, 0x8001, 0xffff]) {
      const x = fixture({hit: true, descriptors: rawCount});
      Object.defineProperty(x.sources, 'objectPools', {get() {throw Error('unreached HIT pool');}});
      equal(x.run(), null, 'HIT negative signed descriptor count returns null before pool access');
      equal(x.descriptorPool.count, rawCount, 'HIT negative count not rewritten');
      equal(x.objectPool.count, 2, 'HIT negative count has no pool effects');
    }
    for (const rawCount of [1, 0x7fff]) {
      const x = fixture({hit: true, descriptors: rawCount});
      equal(x.run(), x.objectA, 'HIT positive signed availability succeeds');
      equal(x.descriptorPool.count, rawCount, 'HIT positive descriptor availability remains unconsumed');
      equal(x.descriptorPool.freeHead, x.descriptorA, 'HIT descriptor free head untouched');
      equal(x.descriptorPool.activeHead, null, 'HIT descriptor active head untouched');
    }
    const x = fixture({hit: true, descriptors: 0}); x.objectPool.head = null;
    Object.defineProperty(x.objectPool, 'count', {get() {throw Error('unreached HIT count');}});
    Object.defineProperty(x.sources, 'typeSizes', {get() {throw Error('unreached HIT size');}});
    equal(x.run(), null, 'HIT null head does not reach count or size');
    const y = fixture({hit: true, objects: 0, descriptors: 0});
    equal(y.run(), y.objectA, 'HIT nonnull head overrides zero unsigned pool count');
    equal(y.objectPool.count, 0xffff, 'HIT count wraps16 without invented capacity veto');
    const z = fixture({hit: true, descriptors: 0x10000});
    rejects(z.run, 'count: unsigned integer out of bounds');
    equal(z.objectPool.count, 2, 'invalid descriptor width fails before HIT pop');
  }
  {
    for (const slot of [255, 0, 1, 2, 3, 4, 5]) {
      const x = fixture({hit: true}); x.runtime.getActorBinding(x.actorId).byte83 = 0; x.actual.slot = slot;
      const group = (slot << 24 >> 24) + 49;
      Object.defineProperty(x.sources, 'groups', {value: {[group]: x.group}});
      Object.defineProperty(x.sources, 'groupEligibility', {value: {[group]: 26}});
      equal(x.run(), x.objectA, 'HIT signed actor slot remap succeeds for authenticated48..54');
      equal(x.runtime.readU8(x.objectA, 1), group, 'HIT stores exact signed slot+49');
      equal(x.group.head, x.objectA, 'HIT inserted only into selected actual group');
    }
    const x = fixture({hit: true}); x.runtime.getActorBinding(x.actorId).byte83 = 128;
    Object.defineProperty(x.actual, 'slot', {get() {throw Error('unreached HIT slot');}});
    equal(x.run(), x.objectA, 'HIT nonzero genuine83 skips actor slot');
    for (const slot of [6, 254, 128]) {
      const y = fixture({hit: true}); y.runtime.getActorBinding(y.actorId).byte83 = 0; y.actual.slot = slot;
      const group = (slot << 24 >> 24) + 49;
      Object.defineProperty(y.sources, 'groupEligibility', {value: {[group]: 26}});
      rejects(y.run, 'only authenticated group48..54 classification26');
      equal(y.runtime.readU8(y.objectA, 1), group & 255, 'unsupported HIT group retains preceding raw group byte');
      equal(y.group.head, null, 'unsupported HIT group fails before group insertion');
      rejects(y.run, 'permanently incomplete allocation owner');
    }
    const y = fixture({hit: true}); Object.defineProperty(y.sources, 'groupEligibility', {value: {48: 16}});
    rejects(y.run, 'only authenticated group48..54 classification26');
    equal(y.runtime.readU8(y.objectA, 0x83), 0, 'HIT cannot borrow projectile classification16');
    const z = fixture({hit: true, deferred: true}); delete z.initial.byte83; z.bind();
    rejects(z.run, 'byte83: own data property');
    equal(z.runtime.readU8(z.objectA, 0x85), 255, 'missing HIT83 fails lazily after real pop and sentinel');
  }
  {
    for (const [type, size] of [[3, 0x2e4], [4, 0x1bc], [128, 0x1c0]] as const) {
      const x = fixture({hit: true}); x.runtime.writeU8(x.objectA, 2, type);
      Object.defineProperty(x.sources, 'typeSizes', {value: {[type << 24 >> 24]: size}});
      rejects(x.run, 'only authenticated object pool4 type4 size0x1c0');
      equal(x.objectPool.count, 1, 'HIT type/size refusal follows count decrement');
      equal(x.objectPool.head, x.objectB, 'HIT type/size refusal follows actual next pop');
      equal(x.runtime.readU8(x.objectA, 2), type, 'HIT type/size refusal precedes memset');
      equal(x.runtime.readU8(x.objectA, 0x100), 0xa5, 'HIT wrong type/size never shortens or enlarges memset');
    }
    const x = fixture({hit: true}); delete x.objectBytesA[0x100];
    rejects(x.run, '256: own data property');
    equal(x.runtime.readU8(x.objectA, 0xff), 0, 'HIT partial byte memset prior effect retained');
    equal(x.runtime.readU8(x.objectA, 0x101), 0xa5, 'HIT partial memset does not invent missing backing');
    equal(x.runtime.readU8(x.objectA, 2), 0, 'HIT type restore waits for full memset');
    const y = fixture({hit: true}); y.group.head = y.objectB; y.group.tail = y.objectB;
    y.runtime.writePointer(y.objectA, 4, null); y.runtime.writePointer(y.objectB, 4, null);
    Object.defineProperty(y.objectBytesB, '6', {value: 0, writable: false});
    rejects(y.run, '6: non-writable');
    equal(y.group.head, y.objectA, 'HIT list-width fault retains group head insertion');
    equal(y.runtime.readPointer(y.objectA, 8), y.objectB, 'HIT list-width fault retains new next link');
    equal(y.runtime.readPointer(y.objectB, 4), null, 'HIT old previous pointer store is source-width atomic');
    equal(y.descriptorPool.count, 2, 'HIT list-width fault never consumes descriptor');
    rejects(() => y.runtime.allocateProjectile(y.actorId, y.caller), 'permanently incomplete allocation owner');
    const z = fixture({hit: true}); z.objectPool.head = Symbol('unknown HIT');
    rejects(z.run, 'unknown/non-owned object identity');
    equal(z.objectPool.count, 1, 'HIT invalid actual node retains preceding count store');
  }
  {
    const x = fixture(), hit = Symbol('HIT'), hitBytes = bytes(0x1c0);
    x.runtime.registerObject(hit, hitBytes); x.runtime.writeU8(hit, 2, 4); x.runtime.writePointer(hit, 4, null);
    const hitPool = {head: hit as symbol | null, tail: hit as symbol | null, count: 1};
    const hitGroup = {head: null as symbol | null, tail: null as symbol | null};
    Object.defineProperty(x.sources, 'objectPools', {value: {3: x.objectPool, 4: hitPool}});
    Object.defineProperty(x.sources, 'groups', {value: {8: x.group, 48: hitGroup}});
    Object.defineProperty(x.sources, 'typeSizes', {value: {3: 0x2e4, 4: 0x1c0}});
    Object.defineProperty(x.sources, 'groupEligibility', {value: {8: 16, 48: 26}});
    rejects(() => x.runtime.allocateProjectileHit(x.actorId, Symbol()), 'exclusive actor caller capability');
    equal(hitPool.count, 1, 'HIT wrong caller cannot mutate shared allocator');
    equal(x.run(), x.objectA, 'ordinary projectile still uses real shared descriptor allocator');
    equal(x.runtime.allocateProjectileHit(x.actorId, x.caller), hit, 'same exclusive actor caller allocates real HIT');
    equal(x.descriptorPool.count, 1, 'HIT preserves prior projectile descriptor consumption');
    equal(x.descriptorPool.activeHead, x.descriptorA, 'HIT preserves actual active descriptor list');
    equal(x.group.head, x.objectA, 'HIT retains actual projectile group');
    equal(hitGroup.head, hit, 'HIT enters distinct canonical group');
    equal(x.runtime.getPointerTarget(hit), hitBytes, 'HIT shares canonical pointer registry');
  }
  {
    const x = fixture(), external = {marker: 1}, base = Symbol('raw HIT table');
    Object.defineProperty(external, '0', {get() {throw Error('pointer arithmetic must not dereference source');}});
    x.runtime.registerExternal(base, external);
    const interior = x.runtime.getInteriorPointer(base, 0x34), view = x.runtime.getPointerTarget(interior) as SourceObjectInteriorTarget;
    equal(x.runtime.getInteriorPointer(base, 0), base, 'zero interior displacement is original base');
    equal(x.runtime.getInteriorAddress(base), null, 'ordinary external base has no interior address');
    equal(x.runtime.getInteriorPointer(base, 0x34), interior, 'same base and offset intern exact identity');
    equal(x.runtime.getInteriorPointer(interior, 0), interior, 'zero displacement preserves interior identity');
    equal(x.runtime.getInteriorPointer(x.runtime.getInteriorPointer(base, 0x30), 4), interior, 'nested alias normalizes to exact original base');
    equal(view.base, external, 'interior target retains original target object reference');
    equal(view.byteOffset, 0x34, 'interior target retains exact byte offset');
    check(Object.isFrozen(view), 'interior target metadata immutable');
    external.marker = 2; equal((view.base as typeof external).marker, 2, 'interior retains live base rather than copying its fields');
    const address = x.runtime.getInteriorAddress(interior);
    check(address !== null && Object.isFrozen(address), 'interior address metadata immutable');
    equal(address?.base, base, 'interior address records original owned symbol');
    equal(address?.byteOffset, 0x34, 'interior address records byte displacement');
    equal(x.runtime.getPointerIdentity(view), interior, 'interior view resolves only registered exact identity');
    rejects(() => x.runtime.getPointerIdentity({...view}), 'has not been registered');
    const childPosition = x.runtime.getInteriorPointer(x.objectA, 0x114);
    equal((x.runtime.getPointerTarget(childPosition) as SourceObjectInteriorTarget).base, x.objectBytesA, 'object interior retains actual canonical byte record');
    x.runtime.writePointer(x.objectB, 0x28, interior); x.runtime.writePointer(x.objectB, 0x60, childPosition);
    equal(x.runtime.readPointer(x.objectB, 0x28), interior, 'canonical word stores preserve table interior identity');
    equal(x.runtime.readPointer(x.objectB, 0x60), childPosition, 'canonical word stores preserve child+114 identity');
    equal(x.runtime.getInteriorAddress(childPosition)?.byteOffset, 0x114, 'child position offset retained');
    rejects(() => x.runtime.readU8(interior, 0), 'unknown/non-owned memory identity');
    rejects(() => x.runtime.writeU8(childPosition, 0, 1), 'unknown/non-owned memory identity');
    equal(x.runtime.readU8(x.objectA, 0x114), 0xa5, 'interior formation supplies no source bytes');
    for (const offset of [-1, 0.5, NaN, Infinity, 0x10000, 0x80000000])
      rejects(() => x.runtime.getInteriorPointer(base, offset), 'interior byte offset: unsigned integer out of bounds');
    const end = x.runtime.getInteriorPointer(base, 0xffff);
    equal(x.runtime.getInteriorAddress(end)?.byteOffset, 0xffff, 'symbolic formation does not require source extent');
    rejects(() => x.runtime.getInteriorPointer(end, 1), 'interior byte offset: unsigned integer out of bounds');
    rejects(() => x.runtime.getInteriorPointer(Symbol('foreign base'), 0), 'unknown/non-owned pointer identity');
    rejects(() => x.runtime.getInteriorAddress(Symbol('foreign interior')), 'unknown/non-owned pointer identity');
    const y = fixture();
    rejects(() => y.runtime.getInteriorPointer(base, 4), 'unknown/non-owned pointer identity');
    rejects(() => y.runtime.writePointer(y.objectA, 0x28, interior), 'no owned opaque identity');
    x.runtime.markActorIncomplete(x.actorId, x.caller);
    rejects(() => x.runtime.getInteriorPointer(base, 0x34), 'permanently incomplete allocation owner');
    equal(x.runtime.getInteriorAddress(interior), address, 'closed allocator retains diagnostic address metadata');
  }
  {
    for (const operation of ['form', 'inspect'] as const) {
      const x = fixture({hit: true}), interior = x.runtime.getInteriorPointer(x.objectA, 0x114);
      x.hooks.getActor = () => {
        try {
          if (operation === 'form') x.runtime.getInteriorPointer(x.objectA, 0x28);
          else x.runtime.getInteriorAddress(interior);
        } catch {}
        return x.actual;
      };
      rejects(x.run, 'caught same-runtime reentry');
      equal(x.objectPool.count, 2, 'interior API reentry poisons even when owner catches it');
      equal(x.group.head, null, 'interior API reentry prevents HIT allocation effects');
    }
  }
}
