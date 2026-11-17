import {createSourceProjectileRootRuntime, isSourceProjectileRootRuntime,
  type SourceProjectileRootRuntime, type SourceProjectileRootSources, type SourceProjectileDrawList} from './projectile-root-lifecycle.js';
import {hasIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import type {SourceActorProjectileSpawnRuntime} from './actor-projectile-spawn.js';
import type {SourceActorStageBoundsRuntime, SourceActorStageBoundsBinding} from './actor-stage-bounds.js';
import type {SourceAllocationBytes, SourceObjectAllocationRuntime, SourceObjectGroup} from './source-object-allocation.js';
import type {RomActor} from './actor.js';

/** Only the genuine attached composition supplies this test-only factory. The
 * child has already completed7db5c and been bound to the real root runtime.
 * These explicit host mutations test source order/faults, not live scheduling,
 * a successful HIT callback, original execution, or retail asset hydration. */
export interface SourceProjectileRootTestFixture {
  actor: symbol; sourceActor: RomActor;
  projectiles: SourceActorProjectileSpawnRuntime;
  allocator: SourceObjectAllocationRuntime;
  stageBounds: SourceActorStageBoundsRuntime;
  stageState: Partial<SourceActorStageBoundsBinding>;
  child: symbol; nextChild: symbol;
  objectBytes: SourceAllocationBytes; nextObjectBytes: SourceAllocationBytes;
  groups: Record<number, SourceObjectGroup>;
  root: SourceProjectileRootRuntime;
  rootSources: SourceProjectileRootSources;
  drawList: SourceProjectileDrawList;
  frame: {bindActor(identity: symbol): void};
}
const HIT = 'actual8008ac80 HIT registration';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[projectile-root-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment), `expected ${fragment}, got ${message || 'success'}`);
}
function observe(run: () => void, onRead: (owner: object, key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object, key: PropertyKey) => {
    onRead(owner, key); return original(owner, key);
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
function dispatch(x: SourceProjectileRootTestFixture, fragment = HIT): void {
  rejects(() => x.root.dispatchStoredRoot(x.child), fragment);
}
function byte(x: SourceProjectileRootTestFixture, offset: number): number {return x.allocator.readU8(x.child, offset);}
function word(x: SourceProjectileRootTestFixture, offset: number): number {return x.allocator.readU32(x.child, offset);}
function pointer(x: SourceProjectileRootTestFixture, offset: number): symbol | null {return x.allocator.readPointer(x.child, offset);}
function snapshot(...records: object[]): () => void {
  const saved = records.map(record => Object.getOwnPropertyDescriptors(record));
  return () => records.forEach((record, i) => {
    const before = saved[i]!, after = Object.getOwnPropertyDescriptors(record);
    equal(Reflect.ownKeys(after).length, Reflect.ownKeys(before).length, 'failed replay preserves property count');
    for (const key of Object.keys(before)) {
      const a = after[key], b = before[key]!;
      check(a !== undefined && Object.is(a.value, b.value) && a.get === b.get && a.set === b.set &&
        a.writable === b.writable && a.configurable === b.configurable && a.enumerable === b.enumerable,
      `failed replay preserves ${key}`);
    }
  });
}
function closed(x: SourceProjectileRootTestFixture): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'root failure closes shared actual Double lifecycle');
  const retained = snapshot(x.objectBytes, x.nextObjectBytes, x.drawList);
  rejects(() => x.root.dispatchStoredRoot(x.child), 'incomplete');
  rejects(() => x.projectiles.spawn(x.actor, 1), 'incomplete');
  rejects(() => x.allocator.writeU8(x.nextChild, 0, 1), 'incomplete');
  retained();
}
function initialized(x: SourceProjectileRootTestFixture, heading: number): void {
  equal(byte(x, 0x18), 1, 'initial handler leaves state1 at the unsupported HIT call');
  equal(word(x, 0x100), 0x80047aa4, 'actual future draw callback word');
  equal(byte(x, 0x85), 0, '89100 stores actual draw class0');
  equal(byte(x, 0x84), 0x14, 'source category store follows real draw registration');
  equal(x.allocator.readU16(x.child, 0x72), heading, 'fresh actual owner heading bits copied');
}
function supplyPriorDrawTopology(x: SourceProjectileRootTestFixture): symbol {
  // A second genuine spawn is NOT a completed initializer. Its prior draw
  // membership is explicitly supplied test input for89100's nonempty branch,
  // never evidence that any earlier initialization returned through8ac80.
  equal(x.projectiles.spawn(x.actor, 1), x.nextChild, 'second genuine spawn supplies old-node byte backing');
  x.drawList.head = x.nextChild; x.drawList.tail = x.nextChild;
  x.allocator.writePointer(x.nextChild, 0x104, null); x.allocator.writePointer(x.nextChild, 0x108, null);
  return x.nextChild;
}
export function runProjectileRootLifecycleSelfTests(make: (matchingMirror?: boolean) => SourceProjectileRootTestFixture): void {
  {
    const x = make(), owners = x.root.getSourceOwners(x.child);
    check(isSourceProjectileRootRuntime(x.root) && Object.isFrozen(x.root), 'genuine frozen root runtime');
    for (const fake of [{...x.root}, Object.create(x.root), {}, null, () => x.root])
      check(!isSourceProjectileRootRuntime(fake), 'copied methods/prototype cannot forge root brand');
    equal(x.root.getObject(x.child), x.objectBytes, 'same completed allocation bytes');
    equal(x.root.getSpawnRuntime(), x.projectiles, 'same genuine completed-spawn owner');
    equal(x.root.getDrawList(), x.drawList, 'separate retained draw-list record');
    check(Object.isFrozen(owners) && owners.length === 6 && new Set(owners).size === 6 &&
      [x.objectBytes, x.sourceActor, x.stageState, x.stageBounds.getWorldBinding(x.actor),
        x.stageBounds.getStatusBinding(x.actor), x.drawList].every(owner => owners.includes(owner)),
    'source identities are retained rather than copied or aliased');
    equal(x.sourceActor.borgNumber, 3, 'genuine owner family');
    equal(x.allocator.readU16(x.child, 0x94), 3, 'positive fixture explicitly supplies matching mirror before spawn');
    rejects(() => x.root.bindProjectile(x.child), 'new projectile identity');
    rejects(() => x.root.bindProjectile(x.nextChild), 'no completed genuine spawn');
    rejects(() => x.root.dispatchStoredRoot(x.nextChild), 'unknown/non-owned projectile');
    const counterfeit = Symbol('registered but never spawned');
    x.allocator.registerObject(counterfeit, {...x.objectBytes});
    rejects(() => x.root.bindProjectile(counterfeit), 'no completed genuine spawn');
    const other = createSourceProjectileRootRuntime({...x.rootSources, drawList0: {head: null, tail: null}});
    rejects(() => other.bindProjectile(x.child), 'already claimed');
    rejects(() => createSourceProjectileRootRuntime(x.rootSources), 'draw list already claimed');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'rejected identities do not execute a child');
    x.sourceActor.heading = 0x8123;
    const oldPosition = [0x20, 0x24, 0x28].map(offset => word(x, offset));
    dispatch(x); initialized(x, 0x8123);
    equal(x.drawList.head, x.child, 'empty draw-list head'); equal(x.drawList.tail, x.child, 'empty draw-list tail');
    equal(pointer(x, 0x104), null, 'empty next draw link'); equal(pointer(x, 0x108), null, 'empty previous draw link');
    equal(x.groups[9]!.head, x.child, 'allocation group head remains separate');
    equal(x.groups[9]!.tail, x.child, 'allocation group tail remains separate');
    equal(pointer(x, 4), null, 'allocation previous4 unchanged'); equal(pointer(x, 8), null, 'allocation next8 unchanged');
    check(oldPosition.every((bits, i) => word(x, [0x20, 0x24, 0x28][i]!) === bits), 'HIT boundary precedes a later position refresh');
    equal(byte(x, 0x1d8), 0, 'no fabricated HIT success or retirement'); closed(x);
  }
  for (const key of ['spawns', 'stage'] as const) {
    const x = make();
    rejects(() => createSourceProjectileRootRuntime({...x.rootSources, drawList0: {head: null, tail: null},
      [key]: {...x.rootSources[key]}}), 'genuine spawn and stage');
  }
  for (const field of ['initialState0', 'row1Hit03'] as const) {
    const x = make();
    rejects(() => createSourceProjectileRootRuntime({...x.rootSources, drawList0: {}, [field]: 0}), 'authenticated evidence');
  }
  for (const list of [[], new Uint8Array(2), Promise.resolve({head: null, tail: null})]) {
    const x = make();
    rejects(() => createSourceProjectileRootRuntime({...x.rootSources, drawList0: list as SourceProjectileDrawList}), 'synchronous draw list');
  }
  {
    const x = make(), source = {...x.rootSources, drawList0: {head: null, tail: null}}; let getterRan = false;
    Object.defineProperty(source, 'spawns', {get() {getterRan = true; return x.projectiles;}});
    rejects(() => createSourceProjectileRootRuntime(source), 'spawns: own data property');
    check(!getterRan, 'constructor never executes a source getter');
  }
  {
    const x = make(), y = make();
    equal(x.projectiles.spawn(x.actor, 1), x.nextChild, 'second real allocation obtains an unclaimed completed child');
    const foreign = createSourceProjectileRootRuntime({...x.rootSources, stage: y.stageBounds, drawList0: {head: null, tail: null}});
    rejects(() => foreign.bindProjectile(x.nextChild), 'unknown/non-owned stage-boundary actor');
    const aliased = createSourceProjectileRootRuntime({...x.rootSources, drawList0: x.groups[9]!});
    rejects(() => aliased.bindProjectile(x.nextChild), 'source owner alias');
    x.root.bindProjectile(x.nextChild);
    equal(x.root.getObject(x.nextChild), x.nextObjectBytes, 'failed foreign/aliased admission never counterfeits a completed identity or claims its bytes');
  }
  {
    const x = make();
    x.rootSources.initialState0 = 0; x.rootSources.row1Hit03 = 0;
    x.rootSources.drawList0 = {head: null, tail: null};
    dispatch(x);
    equal(x.drawList.head, x.child, 'captured list and authenticated cells cannot be replaced through caller sources'); closed(x);
  }
  {
    const x = make(false); x.objectBytes[0x82] = 0x6a;
    equal(x.allocator.readU16(x.child, 0x94), 0, 'ordinary earlier mirror remains zero');
    dispatch(x, 'state2 dispatch');
    equal(byte(x, 0x18), 2, 'real family mismatch retires child');
    equal(byte(x, 0x1d8), 1, 'real type3 invalidation marks1d8'); equal(byte(x, 0x82), 0, 'caller clears82 after invalidation');
    equal(word(x, 0x100), 0, 'retirement never falls back to state0'); equal(x.drawList.head, null, 'no invented draw registration'); closed(x);
  }
  {
    const x = make(); x.allocator.writeU32(x.child, 0xc, 0x8007e698); delete x.objectBytes[0x18];
    dispatch(x, 'unsupported stored projectile root callback');
    check(!Object.hasOwn(x.objectBytes, String(0x18)), 'unimplemented10c callback is never substituted for stored0c');
    equal(word(x, 0x100), 0, 'unknown stored callback never enters initial handler'); closed(x);
  }
  for (const state of [2, 3, 127]) {
    const x = make(); x.objectBytes[0x18] = state;
    x.allocator.writePointer(x.child, 0x90, null); x.stageState.lifecycle18 = Number.NaN;
    x.sourceActor.borgNumber = Number.NaN; delete x.objectBytes[0x94];
    dispatch(x, `state${state} dispatch`);
    equal(byte(x, 0x18), state, 'state>=2 skips all owner dereferences but not pointer90 load');
    equal(byte(x, 0x1d8), 0, 'guard skipped'); closed(x);
  }
  for (const state of [128, 255]) {
    const x = make(); x.objectBytes[0x18] = state; x.stageState.lifecycle18 = 2;
    dispatch(x, 'state2 dispatch'); equal(byte(x, 0x1d8), 1, 'negative signed child state enters owner guard'); closed(x);
  }
  for (const state of [128, 255]) {
    const x = make(); x.objectBytes[0x18] = state;
    dispatch(x, `state${state - 256} dispatch`);
    equal(byte(x, 0x18), state, 'matching owner leaves negative state bits intact');
    equal(word(x, 0x100), 0, 'negative dispatch index never clamps or wraps to authenticated state0'); closed(x);
  }
  for (const life of [0, 1, 128, 255]) {
    const x = make(); x.stageState.lifecycle18 = life;
    dispatch(x); equal(byte(x, 0x18), 1, 'signed parent lifecycle below2 keeps matching child'); closed(x);
  }
  for (const life of [2, 127]) {
    const x = make(); x.stageState.lifecycle18 = life; x.sourceActor.borgNumber = Number.NaN; delete x.objectBytes[0x94];
    let readFamily = false;
    observe(() => dispatch(x, 'state2 dispatch'), (owner, key) => {
      if ((owner === x.sourceActor && key === 'borgNumber') || (owner === x.objectBytes && key === String(0x94))) readFamily = true;
    });
    check(!readFamily, 'parent state>=2 short-circuits both signed family loads'); closed(x);
  }
  for (const life of [-1, 256, Number.NaN]) {
    const x = make(); x.stageState.lifecycle18 = life;
    dispatch(x, 'lifecycle18: unsigned source integer');
    equal(byte(x, 0x18), 0, 'invalid raw parent lifecycle never gets normalized or defaulted'); closed(x);
  }
  for (const family of [0, 0x7fff, 0x8000, 0xffff]) {
    const x = make(); x.sourceActor.borgNumber = family; x.allocator.writeU16(x.child, 0x94, family);
    dispatch(x); equal(byte(x, 0x1d8), 0, 'matching raw signed16 family bits do not retire'); closed(x);
  }
  {
    const x = make(); x.objectBytes[0x18] = 1;
    dispatch(x, 'state1 dispatch'); equal(word(x, 0x100), 0, 'state1 never substitutes authenticated state0'); closed(x);
  }
  {
    const x = make(); delete x.objectBytes[0x18]; delete x.objectBytes[0x90];
    dispatch(x, '24: own data property'); closed(x);
  }
  {
    const x = make(); x.objectBytes[0x18] = 2; delete x.objectBytes[0x90];
    dispatch(x, '144: own data property'); equal(byte(x, 0x18), 2, 'pointer load fault occurs even when owner test would skip'); closed(x);
  }
  {
    const x = make(); x.objectBytes[0x18] = 2; x.stageState.lifecycle18 = 2; let changed = false;
    observe(() => dispatch(x), (owner, key) => {
      if (!changed && owner === x.objectBytes && key === String(0x90)) {changed = true; x.objectBytes[0x18] = 0;}
    });
    check(changed, 'first90 load observed'); equal(byte(x, 0x1d8), 0, 'initial18 captured BEFORE90, signed/tested only after90');
    equal(byte(x, 0x18), 1, 'fresh later18 dispatch observes changed0 without redoing skipped owner guard'); closed(x);
  }
  {
    const x = make(); let changed = false;
    observe(() => dispatch(x, 'state1 dispatch'), (owner, key) => {
      if (!changed && owner === x.objectBytes && key === String(0x94)) {changed = true; x.objectBytes[0x18] = 1;}
    });
    check(changed, 'guard family load observed'); equal(word(x, 0x100), 0, 'dispatch reloads18 after guard rather than caching initial0'); closed(x);
  }
  for (const owner of [null, 'registered-other'] as const) {
    const x = make(); x.allocator.writePointer(x.child, 0x90, owner === null ? null : x.nextChild);
    dispatch(x, owner === null ? 'pointer90 is null' : 'outside the bound genuine');
    equal(pointer(x, 0x8c), x.actor, 'valid8c never substitutes actual90'); equal(byte(x, 0x18), 0, 'failed owner dereference precedes writes'); closed(x);
  }
  for (const type of [0, 1, 2, 3, 4, 127, 128, 255]) {
    const x = make(false); x.objectBytes[2] = type; x.objectBytes[0x82] = 0x6a; x.objectBytes[0x1d8] = 0x5b;
    const touched: string[] = [];
    observe(() => dispatch(x, 'state2 dispatch'), (owner, key) => {
      if (owner !== x.objectBytes) return;
      if (key === '2') {equal(x.objectBytes[0x18], 2, 'state2 store precedes helper type load'); touched.push('type');}
      if (key === String(0x1d8)) {equal(x.objectBytes[0x82], 0x6a, 'helper1d8 precedes caller82'); touched.push('hit');}
      if (key === String(0x82)) touched.push('82');
    });
    equal(byte(x, 0x1d8), type === 0 || type === 3 ? 1 : 0x5b, 'only exact raw type0/3 writes1d8');
    equal(byte(x, 0x82), 0, 'caller82 clears on both genuine helper returns');
    equal(touched.join(','), type === 0 || type === 3 ? 'type,hit,82' : 'type,82', 'helper read/store order and short-circuit'); closed(x);
  }
  for (const target of [0x18, 0x1d8, 0x82]) {
    const x = make(false); x.objectBytes[0x82] = 0x6a;
    Object.defineProperty(x.objectBytes, String(target), {writable: false});
    dispatch(x, 'non-writable');
    equal(byte(x, 0x18), target === 0x18 ? 0 : 2, 'guard source store prefix survives');
    equal(byte(x, 0x1d8), target === 0x82 ? 1 : 0, 'helper store only survives if reached');
    equal(byte(x, 0x82), 0x6a, 'later82 is never cleared past a failed store'); closed(x);
  }
  {
    const x = make(false); delete x.objectBytes[2]; x.objectBytes[0x82] = 0x6a;
    dispatch(x, '2: own data property'); equal(byte(x, 0x18), 2, 'missing helper type leaves prior state2');
    equal(byte(x, 0x82), 0x6a, 'helper failure prevents caller82'); closed(x);
  }
  {
    const x = make(false); x.objectBytes[2] = 255; delete x.objectBytes[0x1d8];
    dispatch(x, 'state2 dispatch');
    check(!Object.hasOwn(x.objectBytes, String(0x1d8)), 'nonzero signed non3 helper return never touches missing1d8');
    equal(byte(x, 0x82), 0, 'caller82 still executes after genuine early helper return'); closed(x);
  }
  for (const variant of [0, 2, 128, 255]) {
    const x = make(); x.objectBytes[0x11] = variant;
    dispatch(x, `row${variant} HIT byte`); initialized(x, x.sourceActor.heading);
    equal(x.drawList.head, x.child, 'unauthenticated unsigned variant stops only at reached row HIT load'); closed(x);
  }
  {
    const x = make(); let loads90 = 0;
    observe(() => dispatch(x), (owner, key) => {
      if (owner === x.objectBytes && key === String(0x90) && ++loads90 === 2) x.objectBytes[0x11] = 255;
    });
    equal(loads90, 2, 'guard and initializer each load actual90');
    equal(byte(x, 0x11), 255, 'explicit mutation at second90 remains visible');
    initialized(x, x.sourceActor.heading); closed(x);
  }
  {
    const x = make(); let variantLoaded = false;
    observe(() => dispatch(x, 'pointer90 is null'), (owner, key) => {
      if (owner === x.objectBytes && key === String(0x11)) {
        variantLoaded = true; for (let offset = 0x90; offset < 0x94; offset++) x.objectBytes[offset] = 0;
      }
    });
    check(variantLoaded, 'initial source variant load reached'); equal(byte(x, 0x18), 1, 'second90 is captured before initialization stores');
    equal(byte(x, 0x84), 0x14, 'null saved initializer owner faults only at later heading dereference');
    equal(x.drawList.head, x.child, 'real draw registration survives late null owner'); closed(x);
  }
  {
    const x = make(); let states = 0;
    observe(() => dispatch(x), (owner, key) => {
      if (owner === x.objectBytes && key === String(0x18) && ++states === 3)
        for (let offset = 0x90; offset < 0x94; offset++) x.objectBytes[offset] = 0;
    });
    equal(states, 3, 'initial18, dispatch18 and initialization18 destination are distinct');
    equal(pointer(x, 0x90), null, 'explicit later pointer mutation remains');
    initialized(x, x.sourceActor.heading); closed(x);
  }
  {
    const x = make(); x.sourceActor.heading = 0x1234; let changed = false;
    observe(() => dispatch(x), (owner, key) => {
      if (!changed && owner === x.objectBytes && key === String(0x84)) {changed = true; x.sourceActor.heading = 0xfedc;}
    });
    check(changed, 'category store reached before actual heading load'); initialized(x, 0xfedc); closed(x);
  }
  {
    const x = make(); Object.defineProperty(x.sourceActor, 'heading', {writable: false});
    dispatch(x); initialized(x, x.sourceActor.heading); closed(x);
  }
  {
    const x = make(); delete x.objectBytes[0x11];
    dispatch(x, '17: own data property'); equal(byte(x, 0x18), 0, 'missing variant prevents all handler writes'); closed(x);
  }
  {
    const x = make(); let pointers = 0;
    observe(() => dispatch(x, '144: own data property'), (owner, key) => {
      if (owner === x.objectBytes && key === String(0x90) && ++pointers === 2) delete x.objectBytes[0x90];
    });
    equal(pointers, 2, 'initializer uses a genuine second90 load');
    equal(byte(x, 0x18), 0, 'missing second90 faults before initial-state store');
    equal(word(x, 0x100), 0, 'missing second90 prevents callback and draw stores'); closed(x);
  }
  for (const target of [0x18, 0x103, 0x85, 0x84, 0x73]) {
    const x = make(); x.sourceActor.heading = 0xabcd;
    Object.defineProperty(x.objectBytes, String(target), {writable: false});
    dispatch(x, 'non-writable');
    equal(byte(x, 0x18), target === 0x18 ? 0 : 1, 'initializer state store order');
    equal(word(x, 0x100), target === 0x18 || target === 0x103 ? 0 : 0x80047aa4, 'whole callback word preflight is atomic');
    equal(byte(x, 0x85), target === 0x18 || target === 0x103 || target === 0x85 ? 255 : 0, 'draw class is not stored early');
    equal(x.drawList.head, target === 0x84 || target === 0x73 ? x.child : null, 'draw registration preserves exactly the reached prefix');
    equal(x.allocator.readU16(x.child, 0x72), 0, 'heading halfword preflights both bytes without partial store'); closed(x);
  }
  {
    const x = make(); (x.sourceActor as unknown as {heading: unknown}).heading = undefined;
    dispatch(x, 'heading: unsigned source integer');
    equal(byte(x, 0x84), 0x14, 'missing heading rejected only after registration and category');
    equal(x.allocator.readU16(x.child, 0x72), 0, 'missing heading never defaulted'); closed(x);
  }
  {
    const x = make(), previous = supplyPriorDrawTopology(x);
    const oldFreeLinks = [4, 8].map(offset => x.allocator.readU32(previous, offset));
    dispatch(x); initialized(x, x.sourceActor.heading);
    equal(x.drawList.head, x.child, 'nonempty draw-list new head'); equal(x.drawList.tail, previous, 'nonempty draw-list tail retained');
    equal(pointer(x, 0x104), previous, 'new104 points to saved previous head'); equal(pointer(x, 0x108), null, 'new108 is null');
    equal(x.allocator.readPointer(previous, 0x108), x.child, 'old108 points to new head');
    equal(x.allocator.readPointer(previous, 0x104), null, 'old104 untouched');
    check(oldFreeLinks.every((v, i) => x.allocator.readU32(previous, [4, 8][i]!) === v), 'draw insertion never uses free/group4/8'); closed(x);
  }
  {
    const x = make(); supplyPriorDrawTopology(x); delete x.drawList.tail;
    dispatch(x); check(!Object.hasOwn(x.drawList, 'tail'), 'nonempty insertion never reads or writes missing tail'); closed(x);
  }
  for (const target of ['head-missing', 'head-readonly', 'tail-readonly', '108-readonly', '104-readonly'] as const) {
    const x = make(); x.allocator.writePointer(x.child, 0x104, x.nextChild); x.allocator.writePointer(x.child, 0x108, x.nextChild);
    if (target === 'head-missing') delete x.drawList.head;
    else if (target === 'head-readonly' || target === 'tail-readonly')
      Object.defineProperty(x.drawList, target === 'head-readonly' ? 'head' : 'tail', {writable: false});
    else Object.defineProperty(x.objectBytes, String(target === '108-readonly' ? 0x10b : 0x107), {writable: false});
    dispatch(x, target === 'head-missing' ? 'head: own data property' : 'non-writable');
    equal(byte(x, 0x85), 0, 'draw class precedes lazy list/destination fault');
    equal(x.drawList.head, target === 'head-missing' ? undefined : target === 'head-readonly' ? null : x.child, 'draw head prefix');
    equal(x.drawList.tail, target === '104-readonly' ? x.child : null, 'empty tail store follows complete108');
    equal(pointer(x, 0x108), target === 'tail-readonly' || target === '104-readonly' ? null : x.nextChild, 'whole108 store preflights four bytes');
    equal(pointer(x, 0x104), x.nextChild, 'later104 untouched or atomically refused');
    equal(byte(x, 0x84), 0, 'category never precedes completed draw registration'); closed(x);
  }
  {
    const x = make(); supplyPriorDrawTopology(x);
    Object.defineProperty(x.nextObjectBytes, String(0x10b), {writable: false});
    dispatch(x, 'non-writable');
    equal(x.drawList.head, x.child, 'old-node backlink fault retains new list head'); equal(pointer(x, 0x104), x.nextChild, 'new104 survives');
    equal(pointer(x, 0x108), null, 'new108 survives'); equal(x.allocator.readPointer(x.nextChild, 0x108), null, 'failed old backlink atomic');
    equal(byte(x, 0x84), 0, 'old backlink must finish before category'); closed(x);
  }
  {
    const x = make(), external = Symbol('not an object byte record');
    x.allocator.registerExternal(external, {}); x.drawList.head = external; x.drawList.tail = external;
    dispatch(x, 'unknown/non-owned object');
    equal(x.drawList.head, x.child, 'invalid old object discovered after head store');
    equal(pointer(x, 0x104), external, 'old pointer store precedes reached old-object dereference');
    equal(pointer(x, 0x108), null, 'new108 survives invalid old target'); equal(byte(x, 0x84), 0, 'no invented old object'); closed(x);
  }
  {
    const x = make(); let callbacks = 0;
    delete x.drawList.head; delete x.drawList.tail; Object.defineProperty(x.objectBytes, String(0x85), {writable: false});
    observe(() => dispatch(x), (owner, key) => {
      if (owner === x.objectBytes && key === String(0x100) && ++callbacks === 2)
        for (let offset = 0x100; offset < 0x104; offset++) x.objectBytes[offset] = 0;
    });
    equal(callbacks, 2, '89100 freshly reads100 after initializer store');
    equal(byte(x, 0x85), 255, 'actual zero-callback return skips even class85 destination');
    equal(byte(x, 0x84), 0x14, 'zero callback returns to real handler prefix');
    check(!Object.hasOwn(x.drawList, 'head') && !Object.hasOwn(x.drawList, 'tail'), 'zero callback never touches absent draw globals'); closed(x);
  }
  for (const reached of ['variant', 'heading'] as const) {
    const x = make(); let injected = false;
    observe(() => dispatch(x, 'reentry'), (owner, key) => {
      if (!injected && (reached === 'variant' ? owner === x.objectBytes && key === String(0x11) : owner === x.sourceActor && key === 'heading')) {
        injected = true;
        try {if (reached === 'variant') x.root.dispatchStoredRoot(x.child); else x.root.bindProjectile(x.nextChild);}
        catch {/* Catching the inner refusal must not repair the outer invocation. */}
      }
    });
    check(injected, 'same-runtime reentry attempted at a reached source read');
    equal(byte(x, 0x18), reached === 'variant' ? 0 : 1, 'reentry preserves only already executed source prefix');
    equal(byte(x, 0x84), reached === 'variant' ? 0 : 0x14, 'late reentry retains genuine draw/category effects'); closed(x);
  }
  for (const key of ['lifecycle18', 'byte18', 'state18']) {
    const x = make(); Object.defineProperty(x.sourceActor, key, {value: 0, configurable: true});
    dispatch(x, `${key}: competing actual actor storage`);
    equal(byte(x, 0x18), 0, 'competing owner storage rejected before root source execution'); closed(x);
  }
  {
    const x = make(); let injected = false;
    observe(() => dispatch(x, 'reentry'), (owner, key) => {
      if (!injected && owner === x.sourceActor && key === 'state18') {
        injected = true; try {x.root.dispatchStoredRoot(x.child);} catch {/* Ownership admission also latches a caught reentry. */}
      }
    });
    check(injected, 'reentry attempted inside bound owner validation');
    equal(byte(x, 0x18), 0, 'owner-admission reentry never enters source prefix'); closed(x);
  }
  {
    const x = make(); x.frame.bindActor(x.actor);
    const retained = snapshot(x.objectBytes, x.nextObjectBytes, x.drawList);
    dispatch(x, 'frame-owned actor'); retained();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'refused direct frame-owned dispatch never invents a scheduler invocation');
  }
  console.log('[projectile-root-test] PASS: genuine completed-spawn identity, signed guards and fresh ordered dispatch, real8aff0/89100 prefixes, separate draw links, lazy atomic faults and shared failure/reentry closure; explicit8ac80 boundary, no successful HIT, scheduler or flight claim');
}
