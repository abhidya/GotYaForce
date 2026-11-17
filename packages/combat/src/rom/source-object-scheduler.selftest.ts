import {hasIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {prepareSourceProjectileScheduledRoot, invokeSourceProjectileScheduledRoot,
  markIncompleteSourceProjectileScheduledRoot} from './projectile-root-lifecycle.js';
import {createSourceObjectSchedulerRuntime, isSourceObjectSchedulerRuntime,
  requireSourceObjectSchedulerInvocation, requireSourceObjectSchedulerSnapshot,
  type SourceObjectSchedulerRuntime, type SourceObjectSchedulerSources} from './source-object-scheduler.js';
import type {SourceAllocationBytes} from './source-object-allocation.js';
import type {SourceProjectileCleanupTestFixture} from './projectile-cleanup.selftest.js';

/** The supplied factory completes a real standalone spawn and root binding.
 * Slot pointers, active bytes, masks, exceptional words and fault mutations are
 * explicit synthetic offline inputs. These checks establish the bounded source
 * scheduler composition, not retail hydration, an outer frame join, estimates,
 * JObjUnref, original-console execution, or browser activation. */
export interface SourceObjectSchedulerTestFixture extends SourceProjectileCleanupTestFixture {
  schedulerSources: SourceObjectSchedulerSources;
  matchGlobals: {maskD1: number; maskD2: number};
  actorSlots: Record<number, symbol | null>;
  slotTargets: {active0?: number}[];
}
type Fixture = SourceObjectSchedulerTestFixture;
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[source-object-scheduler-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment), `expected ${fragment}, got ${message || 'success'}`);
}
/** Observe actual record loads and scalar-store preflights, never inject a
 * successful callback or replace a production helper. The after hook runs only
 * after capturing the descriptor returned to the real source implementation. */
function observe(run: () => void, before: (owner: object, key: PropertyKey) => void,
  after?: (owner: object, key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object, key: PropertyKey) => {
    before(owner, key); const descriptor = original(owner, key); after?.(owner, key); return descriptor;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
function retained(...records: object[]): () => void {
  const before = records.map(record => Object.getOwnPropertyDescriptors(record));
  return () => records.forEach((record, index) => {
    const saved = before[index]!, actual = Object.getOwnPropertyDescriptors(record);
    equal(Reflect.ownKeys(actual).length, Reflect.ownKeys(saved).length, 'retained own-property count');
    for (const key of Reflect.ownKeys(saved)) {
      const a = Reflect.get(actual, key) as PropertyDescriptor | undefined, b = Reflect.get(saved, key) as PropertyDescriptor;
      check(a !== undefined && Object.is(a.value, b.value) && a.get === b.get && a.set === b.set &&
        a.writable === b.writable && a.configurable === b.configurable && a.enumerable === b.enumerable,
      `retained descriptor ${String(key)}`);
    }
  });
}
function records(x: Fixture): object[] {
  return [...new Set([...x.allocator.getSourceOwners(x.actor), x.objectBytes, x.nextObjectBytes,
    x.drawList, x.objectPool, x.descriptorPool, x.descriptorBytes, x.nextDescriptorBytes,
    x.hitPool, ...x.hitBytes, ...Object.values(x.groups), x.hitBinding.pointer3fc, x.hitBinding.pointer27c,
    x.schedulerSources, x.actorSlots, ...x.slotTargets, x.matchGlobals])];
}
function closed(x: Fixture, scheduler: SourceObjectSchedulerRuntime, hitBoundary?: string): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'failure closes the same actual Double owner');
  const keep = retained(...records(x));
  for (const run of [() => scheduler.runGroup(9), () => scheduler.runSlots(8), () => scheduler.runWrapper(8)])
    rejects(run, 'incomplete');
  rejects(() => x.root.dispatchStoredRoot(x.child), 'exclusively owned');
  rejects(() => x.projectiles.spawn(x.actor, 1), 'incomplete');
  rejects(() => x.allocator.writeU8(x.nextChild, 0, 1), 'incomplete');
  let completed = true; try {x.projectiles.getSpawnOwnerIdentity(x.child);} catch {completed = false;}
  rejects(() => x.hits.registerHit(x.child, 1), hitBoundary ?? (completed ? 'incomplete' : 'completed genuine spawn'));
  keep();
}
function byte(x: Fixture, offset: number): number {return x.allocator.readU8(x.child, offset);}
function raw(bytes: SourceAllocationBytes, offset: number, width = 4): number {
  let value = 0; for (let i = 0; i < width; i++) value = value * 256 + bytes[offset + i]!; return value;
}
function putRaw(bytes: SourceAllocationBytes, offset: number, value: number, width = 4): void {
  for (let i = 0; i < width; i++) bytes[offset + i] = Math.floor(value / 2 ** (8 * (width - 1 - i))) % 256;
}
function word(offset: number, width = 4): string[] {
  return Array.from({length: width}, (_, i) => (offset + i).toString(16));
}
const SNAPSHOT = ['0', ...word(0x20), ...word(0x24), ...word(0x2c), ...word(0x30),
  ...word(0x28), ...word(0x34), ...word(0x70), ...word(0x76), ...word(0x74, 2), ...word(0x7a, 2), ...word(0xc)];
function initial(x: Fixture, scheduler: SourceObjectSchedulerRuntime): void {
  x.hitBinding.pointer3fc[0xa24] = 255;
  scheduler.runWrapper(8);
  equal(byte(x, 0x18), 2, 'genuine first callback reaches HIT-zero and returns state2');
  equal(byte(x, 0), 1, 'first callback does not inline retirement or cleanup');
}
function ready(x: Fixture, scheduler: SourceObjectSchedulerRuntime): void {
  initial(x, scheduler); scheduler.runWrapper(8);
  equal(byte(x, 0x18), 3, 'separate second invocation returns state3');
  equal(byte(x, 0), 1, 'second callback does not inline cleanup');
}
function emptyGroups(x: Fixture): void {
  for (const group of Object.values(x.groups)) {group.head = null; group.tail = null;}
}
function activateSlots(x: Fixture): void {for (const target of x.slotTargets) target.active0 = 1;}
function observedGroups(x: Fixture, run: () => void): string {
  const events: string[] = [];
  observe(run, (owner, key) => {if (owner === x.groups) events.push(String(key));});
  return events.join(',');
}

export function runObjectSchedulerSelfTests(make: () => SourceObjectSchedulerTestFixture): void {
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources);
    check(isSourceObjectSchedulerRuntime(scheduler) && Object.isFrozen(scheduler), 'genuine frozen scheduler');
    equal(scheduler.getRootRuntime(), x.root, 'same root'); equal(scheduler.getAllocatorRuntime(), x.allocator, 'same allocator');
    equal(scheduler.getMatchGlobals(), x.projectiles.getMatchGlobals(), 'same retained80433934, not copied masks');
    equal(scheduler.getMatchGlobals(), x.matchGlobals, 'factory exposes actual shared80433934');
    equal(x.allocator.getPointerTarget(x.actorSlots[0]!), x.sourceActor, 'slot0 points at actual source actor');
    const keep = retained(...records(x));
    rejects(() => createSourceObjectSchedulerRuntime(x.schedulerSources), 'already has a source scheduler');
    rejects(() => x.root.dispatchStoredRoot(x.child), 'exclusively owned'); keep();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'idle direct-root refusal does not poison scheduler');
    ready(x, scheduler); scheduler.runWrapper(8);
    equal(byte(x, 0), 0, 'separate third genuine callback returns original object to pool');
    equal(x.groups[9]!.head, null, 'actual cleanup removes group9 node');
    equal(x.drawList.head, null, 'actual cleanup removes draw node');
    equal(x.objectPool.tail, x.child, 'actual cleanup appends original object');
    equal(x.allocator.getObject(x.child), x.objectBytes, 'cleanup retains canonical backing');
    rejects(() => x.projectiles.getSpawnOwnerIdentity(x.child), 'completed');
    scheduler.runWrapper(8);
    equal(x.projectiles.spawn(x.actor, 1), x.nextChild, 'older free object allocated first');
    x.root.bindProjectile(x.nextChild);
    equal(x.projectiles.spawn(x.actor, 1), x.child, 'real allocator reuses the same freed object');
    equal(x.allocator.getObject(x.child), x.objectBytes, 'same backing survives reuse');
    x.root.bindProjectile(x.child);
    ready(x, scheduler); scheduler.runWrapper(8);
    equal(byte(x, 0), 0, 'explicit rebind allows second full lifetime');
    equal(x.nextObjectBytes[0], 0, 'same wrapper also completes independently bound second projectile');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'successful scheduler lifetimes leave source owner usable');
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); ready(x, scheduler); scheduler.runWrapper(8);
    equal(x.projectiles.spawn(x.actor, 1), x.nextChild, 'reuse guard allocates older queue member first');
    equal(x.projectiles.spawn(x.actor, 1), x.child, 'reuse guard obtains same released bytes');
    x.groups[9]!.head = x.child; x.allocator.writePointer(x.child, 8, null);
    const keep = retained(...records(x)), reads: string[] = [];
    observe(() => rejects(() => scheduler.runGroup(9), 'released projectile'), (owner, key) => {
      if (owner === x.objectBytes) reads.push(Number(key).toString(16));
    });
    equal(reads.join(','), '0', 'new completed spawn cannot revive stale root lifetime without explicit rebind');
    keep(); closed(x, scheduler);
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources);
    initial(x, scheduler);
    const values = [0x7fc12345, 0xff800000, 0x80000000, 0x89abcdef];
    for (const [index, offset] of [0x20, 0x24, 0x28, 0x70].entries()) x.allocator.writeU32(x.child, offset, values[index]!);
    x.allocator.writeU16(x.child, 0x74, 0xfedc); x.objectBytes[0x86] = 255; x.objectBytes[0x1ca] = 0x5a;
    const events: string[] = []; let captured = false, callback = false;
    observe(() => scheduler.runGroup(9), (owner, key) => {
      if (owner === x.objectBytes && Number.isInteger(Number(key))) events.push(Number(key).toString(16));
      if (owner === x.rootSources && key === 'retirementState2') {events.push('callback'); callback = true;}
      if (!captured && owner === x.objectBytes && key === '44') {
        captured = true; putRaw(x.objectBytes, 0x20, 0x01020304); putRaw(x.objectBytes, 0x24, 0x05060708);
      }
      if (owner === x.objectBytes && key === '134') check(callback, 'post-callback86 is read after actual state2 handler');
    });
    equal(events.join(','), [...SNAPSHOT, '18', ...word(0x90), '18', 'callback', '18', '2', '1d8', '82', '86', '1ca', ...word(8)].join(','),
      'exact source snapshot, sole0c, actual callback and post-callback86/1ca/live8 order');
    equal(raw(x.objectBytes, 0x2c), values[0], 'NaN payload20 captured before stores, without float conversion');
    equal(raw(x.objectBytes, 0x30), values[1], 'negative infinity24 captured before first store');
    equal(raw(x.objectBytes, 0x34), values[2], 'negative-zero28 bits preserved');
    equal(raw(x.objectBytes, 0x76), values[3], 'one unaligned stw76 copies all raw rotation70 bits');
    equal(raw(x.objectBytes, 0x7a, 2), 0xfedc, 'lhz74/sth7a preserves exact halfword');
    equal(byte(x, 0x1ca), 0, 'signed negative86 is nonzero and clears1ca');
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); initial(x, scheduler);
    let z = false, rotation = false, roll = false;
    observe(() => scheduler.runGroup(9), (owner, key) => {
      if (owner !== x.objectBytes) return;
      if (key === '48' && !z) {z = true; putRaw(x.objectBytes, 0x28, 0xffcabcde);}
      if (key === '52' && !rotation) {rotation = true; putRaw(x.objectBytes, 0x70, 0x7fa12345);}
      if (key === '118' && !roll) {roll = true; putRaw(x.objectBytes, 0x74, 0xdead, 2);}
    });
    check(z && rotation && roll, 'freshness mutations reached real preceding scalar stores');
    equal(raw(x.objectBytes, 0x34), 0xffcabcde, '28 loaded only after2c/30 stores');
    equal(raw(x.objectBytes, 0x76), 0x7fa12345, '70 loaded only after34 store');
    equal(raw(x.objectBytes, 0x7a, 2), 0xdead, '74 loaded freshly after complete unaligned76 store');
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); initial(x, scheduler);
    x.objectBytes[0x86] = 0; delete x.objectBytes[0x1ca];
    scheduler.runGroup(9); equal(byte(x, 0x18), 3, 'zero86 skips absent1ca without looking ahead');
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); ready(x, scheduler);
    x.objectBytes[0x86] = 128; x.objectBytes[0x1ca] = 0x73;
    x.nextObjectBytes[0] = 0; x.allocator.writePointer(x.nextChild, 8, null);
    x.allocator.writePointer(x.nextChild, 0x20, x.nextChild); const encoded = word(0x20).map((_, i) => x.nextObjectBytes[0x20 + i]!);
    delete x.nextObjectBytes[0xc]; delete x.nextObjectBytes[0x24];
    const tail: string[] = []; let after = false;
    observe(() => scheduler.runGroup(9), (owner, key) => {
      if (owner === x.objectBytes && key === '134') {
        equal(x.objectBytes[0], 0, 'post-callback86 is reached even after cleanup cleared active0');
        after = true; encoded.forEach((value, i) => {x.objectBytes[8 + i] = value;});
      }
      if (after && owner === x.objectBytes && Number.isInteger(Number(key))) tail.push(`c${Number(key).toString(16)}`);
      if (after && owner === x.nextObjectBytes && Number.isInteger(Number(key))) tail.push(`n${Number(key).toString(16)}`);
    });
    equal(tail.join(','), ['c86', 'c1ca', ...word(8).map(v => `c${v}`), 'n0', ...word(8).map(v => `n${v}`)].join(','),
      'cleanup still performs86/1ca and reloads live next8 rather than captured pre-callback link');
    equal(x.objectBytes[0x1ca], 0, 'post-cleanup signed86 clear committed');
  }
  for (const active of [0, 1, 128, 255]) {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources);
    x.groups[9]!.head = x.nextChild; x.nextObjectBytes[0] = active; x.allocator.writePointer(x.nextChild, 8, null);
    delete x.nextObjectBytes[0x20]; delete x.nextObjectBytes[0xc];
    const keep = retained(...records(x)), reads: string[] = [];
    observe(() => active === 0 ? scheduler.runGroup(9) : rejects(() => scheduler.runGroup(9), 'unknown/non-owned projectile'),
      (owner, key) => {if (owner === x.nextObjectBytes) reads.push(Number(key).toString(16));});
    equal(reads.join(','), active === 0 ? ['0', ...word(8)].join(',') : '0', 'inactive reads only0/8; active unbound fails before source snapshots');
    keep(); if (active !== 0) closed(x, scheduler);
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources);
    x.allocator.writeU32(x.child, 0xc, 0x8008a65c); x.allocator.writeU32(x.child, 0x20, 0x7f800001);
    const reads: string[] = []; const draw = retained(x.drawList, x.objectPool, x.descriptorPool);
    observe(() => rejects(() => scheduler.runGroup(9), 'unsupported stored object callback'), (owner, key) => {
      if (owner === x.objectBytes) reads.push(Number(key).toString(16));
    });
    equal(reads.join(','), SNAPSHOT.join(','), 'bound callback mismatch snapshots completely, then reads sole0c and refuses');
    equal(raw(x.objectBytes, 0x2c), 0x7f800001, 'callback refusal preserves prior raw snapshot writes'); draw(); closed(x, scheduler);
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); let changed = false;
    observe(() => rejects(() => scheduler.runGroup(9), 'unsupported stored object callback'), (owner, key) => {
      if (!changed && owner === x.objectBytes && key === '122') {changed = true; putRaw(x.objectBytes, 0xc, 0x8008a65c);}
    });
    check(changed, 'callback identity changed during final snapshot store');
    equal(byte(x, 0x18), 0, 'scheduler reads fresh actual0c after snapshot rather than cached binding callback'); closed(x, scheduler);
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x); activateSlots(x);
    equal(observedGroups(x, () => scheduler.runWrapper(8)), '9,10,11,12,13,14,8,15', 'aligned wrapper runs six slots, base, base+7');
    equal(observedGroups(x, () => scheduler.runWrapper(9)), '9', 'unaligned wrapper performs only group walker');
    for (let i = 0; i < 6; i++) {
      x.matchGlobals.maskD1 = 1 << i;
      equal(observedGroups(x, () => scheduler.runSlots(8)), [9, 10, 11, 12, 13, 14].filter((_, j) => j !== i).join(','), 'each fresh slot mask bit blocks only its own group');
    }
    x.matchGlobals.maskD1 = 0x80;
    equal(observedGroups(x, () => scheduler.runWrapper(8)), '9,10,11,12,13,14,15', 'pause80 blocks base but not slots or low3=7 exception');
  }
  for (const [bits, expectedMask, paused] of [[0, 'maskD2', true], [7, '', false], [8, 'maskD1', true],
    [55, '', false], [56, '', false], [0x80000008, 'maskD2', true], [0xfffffff8, 'maskD2', true], [0xffffffff, '', false]] as const) {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x);
    const effective = bits & 0x3fffffff; if (!x.groups[effective]) x.groups[effective] = {head: null, tail: null};
    x.matchGlobals.maskD1 = 0x80; x.matchGlobals.maskD2 = 0x80; const masks: string[] = [], groups: string[] = [];
    observe(() => scheduler.runGroup(bits), (owner, key) => {
      if (owner === x.matchGlobals && String(key).startsWith('mask')) masks.push(String(key));
      if (owner === x.groups) groups.push(String(key));
    });
    equal(masks.join(','), expectedMask, 'signed32 comparison and low3bit7 exception select exact pause source');
    equal(groups.join(','), paused ? '' : String(effective), 'group address uses low32 scaled effective index');
    if (paused) {
      x.matchGlobals[expectedMask as 'maskD1' | 'maskD2'] = 0;
      equal(observedGroups(x, () => scheduler.runGroup(bits)), String(effective), 'unpaused signed negative groups retain low32 effective address');
    }
  }
  for (const bits of [0, 0x80000000, 0xfffffff8]) {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x); activateSlots(x);
    for (let i = 0; i < 8; i++) {const index = ((bits + i) >>> 0) & 0x3fffffff; if (!x.groups[index]) x.groups[index] = {head: null, tail: null};}
    const order = [1, 2, 3, 4, 5, 6, 0, 7].map(i => ((bits + i) >>> 0) & 0x3fffffff);
    equal(observedGroups(x, () => scheduler.runWrapper(bits)), order.join(','), 'signed eligible aligned wrapper preserves low32 address arithmetic');
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x); activateSlots(x);
    const bits = 0xfffffffc, expected = [0x3ffffffd, 0x3ffffffe, 0x3fffffff, 0, 1, 2];
    for (const index of expected) x.groups[index] = {head: null, tail: null};
    x.matchGlobals.maskD1 = 255; x.matchGlobals.maskD2 = 0;
    equal(observedGroups(x, () => scheduler.runSlots(bits)), expected.join(','), 'slot index arithmetic wraps low32 while signed base choosesD2');
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x);
    for (const target of x.slotTargets) target.active0 = 0;
    delete (x.matchGlobals as Partial<Fixture['matchGlobals']>).maskD1;
    equal(observedGroups(x, () => scheduler.runSlots(8)), '', 'all inactive slots skip missing pause byte entirely');
  }
  for (const malformed of ['missing', 'accessor', 'out-of-range'] as const) {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x); let getter = false;
    if (malformed === 'missing') delete (x.matchGlobals as Partial<Fixture['matchGlobals']>).maskD1;
    else if (malformed === 'accessor') Object.defineProperty(x.matchGlobals, 'maskD1', {get() {getter = true; return 0;}, configurable: true});
    else x.matchGlobals.maskD1 = 256;
    const groups: string[] = [];
    observe(() => rejects(() => scheduler.runGroup(8), malformed === 'out-of-range' ? 'unsigned source integer' : 'own data property'),
      (owner, key) => {if (owner === x.groups) groups.push(String(key));});
    equal(groups.join(','), '', 'reached malformed mask refuses before group-head load');
    check(!getter, 'mask accessor is not invoked'); closed(x, scheduler);
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x);
    delete x.schedulerSources.actorSlots; delete (x.matchGlobals as Partial<Fixture['matchGlobals']>).maskD1;
    x.groups[56] = {head: null, tail: null};
    scheduler.runSlots(56); equal(observedGroups(x, () => scheduler.runWrapper(56)), '56', 'signed base56 skips slots and masks without accessing absent fields');
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x); activateSlots(x);
    const events: string[] = []; let maskReads = 0;
    observe(() => scheduler.runWrapper(8), (owner, key) => {
      if (owner === x.actorSlots) events.push(`slot${String(key)}`);
      const slot = x.slotTargets.indexOf(owner as {active0?: number});
      if (slot >= 0 && key === 'active0') events.push(`active${slot}`);
      if (owner === x.matchGlobals && key === 'maskD1') {
        events.push('mask'); x.matchGlobals.maskD1 = ++maskReads === 1 ? 0 : 0x82;
      }
      if (owner === x.groups) events.push(`group${String(key)}`);
    });
    equal(events.join(','), ['slot0', 'active0', 'mask', 'group9', 'slot1', 'active1', 'mask',
      'slot2', 'active2', 'mask', 'group11', 'slot3', 'active3', 'mask', 'group12',
      'slot4', 'active4', 'mask', 'group13', 'slot5', 'active5', 'mask', 'group14', 'mask', 'group15'].join(','),
      'actual slot pointer, signed active0, fresh per-slot mask, and fresh base pause are loaded in source order');
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x);
    const replacement = {active0: 255}, replacementId = Symbol('explicit later live actor-slot pointer');
    x.allocator.registerExternal(replacementId, replacement);
    let changed = false;
    observe(() => equal(observedGroups(x, () => scheduler.runSlots(8)), '9,10', 'later slot uses actual newly stored pointer'), (owner, key) => {
      if (!changed && owner === x.groups && key === '9') {changed = true; x.actorSlots[1] = replacementId;}
    });
    check(changed, 'source pointer replacement happened after first slot');
  }
  for (const kind of ['null', 'missing', 'accessor', 'missing-active', 'raw-active-alias'] as const) {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x);
    let getter = false;
    if (kind === 'null') x.actorSlots[1] = null;
    if (kind === 'missing') delete x.actorSlots[1];
    if (kind === 'accessor') Object.defineProperty(x.actorSlots, '1', {get() {getter = true; return x.actor;}, configurable: true});
    if (kind === 'missing-active') delete x.slotTargets[1]!.active0;
    if (kind === 'raw-active-alias') Object.defineProperty(x.slotTargets[1]!, '0', {value: 0, configurable: true});
    const groups: string[] = [];
    observe(() => rejects(() => scheduler.runSlots(8), kind === 'null' ? 'null source actor slot' : kind === 'raw-active-alias' ? 'competing raw byte0' : 'own data property'),
      (owner, key) => {if (owner === x.groups) groups.push(String(key));});
    equal(groups.join(','), '9', 'reached bad slot fails after prior slot, never null-skips or invents active byte');
    check(!getter, 'slot accessor is rejected without execution'); closed(x, scheduler);
  }
  for (const kind of ['globals', 'draw', 'replace-table', 'replace-root'] as const) {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x);
    if (kind === 'globals' || kind === 'draw')
      x.schedulerSources.actorSlots = (kind === 'globals' ? x.matchGlobals : x.drawList) as unknown as Record<number, symbol | null>;
    else if (kind === 'replace-table') {scheduler.runSlots(8); x.schedulerSources.actorSlots = {...x.actorSlots};}
    else x.schedulerSources.root = {...x.root};
    const keep = retained(...records(x));
    rejects(() => scheduler.runSlots(8), kind === 'globals' || kind === 'draw' ? 'alias' : 'owner changed'); keep(); closed(x, scheduler);
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x);
    x.groups[15] = x.groups[9]!;
    const keep = retained(...records(x));
    rejects(() => scheduler.runWrapper(8), 'owner aliases'); keep(); closed(x, scheduler);
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); emptyGroups(x);
    let changed = false;
    observe(() => rejects(() => scheduler.runSlots(8), 'table owner changed'), (owner, key) => {
      if (!changed && owner === x.groups && key === '9') {changed = true; x.schedulerSources.actorSlots = {...x.actorSlots};}
    });
    check(changed, 'table replacement occurs between actual slot iterations'); closed(x, scheduler);
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources), keep = retained(...records(x));
    for (const fake of [{...scheduler}, Object.create(scheduler), {}, null]) {
      check(!isSourceObjectSchedulerRuntime(fake), 'copied scheduler methods cannot forge identity');
      rejects(() => requireSourceObjectSchedulerSnapshot(fake as SourceObjectSchedulerRuntime, x.allocator, x.child), 'private active');
    }
    for (const fake of [{...x.root}, Object.create(x.root), {}, null])
      rejects(() => createSourceObjectSchedulerRuntime({root: fake as Fixture['root']}), 'genuine projectile root');
    for (const run of [
      () => requireSourceObjectSchedulerInvocation(scheduler, x.root, x.child, 'prepare'),
      () => requireSourceObjectSchedulerInvocation(scheduler, x.root, x.child, 'callback', Symbol('forged lifetime')),
      () => requireSourceObjectSchedulerSnapshot(scheduler, x.allocator, x.child),
      () => prepareSourceProjectileScheduledRoot(x.root, scheduler, x.child),
      () => invokeSourceProjectileScheduledRoot(x.root, scheduler, x.child),
      () => markIncompleteSourceProjectileScheduledRoot(x.root, scheduler),
      () => x.allocator.writeSchedulerRotation76(x.child, 0x12345678, scheduler),
    ]) rejects(run, 'private active');
    rejects(() => x.allocator.writeU32(x.child, 0x76, 0x12345678), 'unaligned'); keep();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'idle private-helper refusals do not poison source owner');
    initial(x, scheduler);
  }
  for (const offset of [0x21, 0x27, 0x2a, 0x73, 0x75, 0xf]) {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources);
    x.allocator.writeU32(x.child, 0x20, 0x12345678); x.allocator.writeU32(x.child, 0x24, 0xabcdef01);
    x.allocator.writeU32(x.child, 0x28, 0x76543210); x.allocator.writeU32(x.child, 0x70, 0x87654321);
    for (const at of [0x2c, 0x30, 0x34]) x.allocator.writeU32(x.child, at, 0xa5a5a5a5);
    putRaw(x.objectBytes, 0x76, 0xa5a5a5a5); putRaw(x.objectBytes, 0x7a, 0x5a5a, 2);
    delete x.objectBytes[offset]; rejects(() => scheduler.runGroup(9), `${offset}: own data property`);
    equal(raw(x.objectBytes, 0x2c), offset >= 0x28 || offset === 0xf ? 0x12345678 : 0xa5a5a5a5, 'late read retains only completed x snapshot');
    equal(raw(x.objectBytes, 0x30), offset >= 0x28 || offset === 0xf ? 0xabcdef01 : 0xa5a5a5a5, '20 and24 both captured before any stores');
    equal(raw(x.objectBytes, 0x34), offset >= 0x70 || offset === 0xf ? 0x76543210 : 0xa5a5a5a5, 'z store waits for whole source28');
    equal(raw(x.objectBytes, 0x76), offset === 0x75 || offset === 0xf ? 0x87654321 : 0xa5a5a5a5, 'rotation stw completes only after whole70 load');
    equal(raw(x.objectBytes, 0x7a, 2), offset === 0xf ? 0 : 0x5a5a, 'roll store completes only after whole74 load'); closed(x, scheduler);
  }
  for (const [start, width] of [[0x2c, 4], [0x30, 4], [0x34, 4], [0x76, 4], [0x7a, 2]] as const) {
    for (const missing of [false, true]) {
      const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources);
      for (const [at, value] of [[0x20, 0x12345678], [0x24, 0xabcdef01], [0x28, 0x76543210], [0x70, 0x87654321]] as const)
        x.allocator.writeU32(x.child, at, value);
      x.allocator.writeU16(x.child, 0x74, 0xbeef);
      for (let i = 0; i < width; i++) x.objectBytes[start + i] = 0xa5;
      const last = start + width - 1;
      if (missing) delete x.objectBytes[last]; else Object.defineProperty(x.objectBytes, String(last), {writable: false});
      rejects(() => scheduler.runGroup(9), missing ? `${last}: own data property` : `${last}: non-writable`);
      for (let i = 0; i < width - 1; i++) equal(x.objectBytes[start + i], 0xa5, 'whole scalar preflight prevents partial byte writes, including unaligned76');
      if (start > 0x2c) equal(raw(x.objectBytes, 0x2c), 0x12345678, 'earlier completed source snapshot is not rolled back');
      equal(byte(x, 0x18), 0, 'snapshot-store failure precedes actual callback'); closed(x, scheduler);
    }
  }
  for (const point of ['86', '1ca', '8'] as const) {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); ready(x, scheduler);
    x.objectBytes[0x86] = 255; x.objectBytes[0x1ca] = 0x5a; let changed = false;
    if (point === '86') delete x.objectBytes[0x86];
    if (point === '1ca') Object.defineProperty(x.objectBytes, String(0x1ca), {writable: false});
    observe(() => rejects(() => scheduler.runGroup(9), point === '86' ? '134: own data property' : point === '1ca' ? '458: non-writable' : '11: own data property'),
      (owner, key) => {
        if (point === '8' && !changed && owner === x.objectBytes && key === '134') {changed = true; delete x.objectBytes[11];}
      });
    equal(byte(x, 0), 0, 'post-callback failure retains completed cleanup active0 clear');
    equal(x.objectPool.count, 2, 'post-callback failure retains returned object queue');
    equal(x.descriptorPool.count, 2, 'post-callback failure retains completed descriptor release');
    rejects(() => x.projectiles.getSpawnOwnerIdentity(x.child), 'completed');
    if (point === '8') equal(byte(x, 0x1ca), 0, 'post-callback1ca clear precedes live next8 failure');
    closed(x, scheduler);
  }
  for (const bits of [-1, 0x100000000, 1.5, NaN, Infinity]) {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources), keep = retained(...records(x));
    rejects(() => scheduler.runGroup(bits), 'unsigned source integer'); keep();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'invalid host register rejected before active source invocation');
    initial(x, scheduler);
  }
  for (const reenter of ['scheduler', 'allocator', 'root'] as const) {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); initial(x, scheduler);
    let attempted = false;
    observe(() => rejects(() => scheduler.runGroup(9), 'reentry'), (owner, key) => {
      const reached = reenter === 'root' ? owner === x.rootSources && key === 'retirementState2' : owner === x.objectBytes && key === '44';
      if (!attempted && reached) {
        attempted = true;
        try {
          if (reenter === 'scheduler') scheduler.runSlots(8);
          else if (reenter === 'allocator') x.allocator.readU8(x.child, 0);
          else x.root.dispatchStoredRoot(x.child);
        } catch {/* Caught inner refusals must still poison the active invocation. */}
      }
    });
    check(attempted, 'same-runtime reentry occurred at actual reached source field'); closed(x, scheduler);
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); x.frame.bindActor(x.actor);
    const keep = retained(...records(x)), reads: string[] = [];
    observe(() => rejects(() => scheduler.runGroup(9), 'frame-owned actor'), (owner, key) => {
      if (owner === x.objectBytes) reads.push(Number(key).toString(16));
    });
    equal(reads.join(','), '0', 'frame-owned actor admission refuses before first snapshot word'); keep(); closed(x, scheduler, 'frame-owned actor');
  }
  console.log('[source-object-scheduler-test] PASS: genuine standalone spawn, source wrapper8, separate HIT-zero/state2/cleanup invocations, original-byte reuse and explicit rebind; raw ordered snapshots, live lists/slots/masks, signed effective groups, private authority, atomic faults and permanent closure; bounded synthetic offline composition, no outer frame/estimate/Unref/retail/browser claim');
}
