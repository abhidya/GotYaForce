import {createSourceObjectAllocationRuntime, isSourceObjectAllocationRuntime,
  type SourceAllocationBytes, type SourceObjectAllocationActorBinding,
  type SourceObjectAllocationSources} from './source-object-allocation.js';
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
function fixture(options: {objects?: number; descriptors?: number; deferred?: boolean} = {}) {
  const actorId = Symbol('actor'), caller = Symbol('allocator caller'), actual = createRomActor(); actual.slot = 0;
  const objectA = Symbol('object A'), objectB = Symbol('object B'), descriptorA = Symbol('descriptor A'), descriptorB = Symbol('descriptor B');
  const objectBytesA = bytes(0x2e4), objectBytesB = bytes(0x2e4), descriptorBytesA = bytes(0x2c), descriptorBytesB = bytes(0x2c);
  const hooks: {getActor?: () => typeof actual} = {};
  const world = {getActualActor(id: symbol) {
    check(this === world && id === actorId, 'actual actor owner uses captured receiver/identity');
    return hooks.getActor ? hooks.getActor() : actual;
  }};
  const objectPool = {head: objectA as symbol | null, tail: objectB as symbol | null, count: options.objects ?? 2};
  const descriptorPool = {freeHead: descriptorA as symbol | null, activeHead: null as symbol | null,
    count: options.descriptors ?? 2, initCallback14: 0x80006f60};
  const group = {head: null as symbol | null, tail: null as symbol | null};
  const sources: SourceObjectAllocationSources = {world, objectPools: {3: objectPool}, descriptorPools: {0: descriptorPool},
    groups: {8: group}, typeSizes: {3: 0x2e4}, groupEligibility: {8: 16}};
  const runtime = createSourceObjectAllocationRuntime(sources);
  for (const [id, raw] of [[objectA, objectBytesA], [objectB, objectBytesB]] as const) runtime.registerObject(id, raw);
  for (const [id, raw] of [[descriptorA, descriptorBytesA], [descriptorB, descriptorBytesB]] as const) runtime.registerDescriptor(id, raw);
  runtime.writeU8(objectA, 2, 3); runtime.writeU8(objectB, 2, 3);
  runtime.writePointer(objectA, 4, objectB); runtime.writePointer(objectB, 4, null);
  runtime.writePointer(descriptorA, 0, descriptorB); runtime.writePointer(descriptorB, 0, null);
  const initial: Partial<SourceObjectAllocationActorBinding> = {byte83: 1};
  const bind = () => {runtime.bindActor(actorId, initial); runtime.claimActor(actorId, caller);};
  if (!options.deferred) bind();
  return {actorId, caller, actual, objectA, objectB, descriptorA, descriptorB, objectBytesA, objectBytesB,
    descriptorBytesA, descriptorBytesB, hooks, world, objectPool, descriptorPool, group, sources, runtime, initial, bind,
    run: () => runtime.allocateProjectile(actorId, caller)};
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
}
