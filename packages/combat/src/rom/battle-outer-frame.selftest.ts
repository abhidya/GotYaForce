import {hasIncompleteSourceActorDoubleLifecycle, isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import {createSourceBattleOuterFrameRuntime, isSourceBattleOuterFrameRuntime,
  isPendingSourceBattleOuterFrameClaim, requireSourceBattleOuterFrameFailure,
  type SourceBattleOuterFrameRuntime, type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {createSourceObjectSchedulerRuntime, claimSourceObjectSchedulerOuterFrame,
  closeSourceObjectSchedulerOuterFrame, requireSourceObjectSchedulerInvocation,
  requireSourceObjectSchedulerSnapshot, type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import type {SourceObjectSchedulerTestFixture} from './source-object-scheduler.selftest.js';

interface TeamRow {
  byte0: number; byte1: number; byte2: number; byte3: number;
  byte4: number; byte5: number; byte6: number; byte7: number; byte8: number; byte9: number;
  byte10: number; threshold30: number; meter: number; charged: boolean;
}
/** Genuine completed spawn/root/scheduler graph, with explicit synthetic cells
 * on its original shared global and team-row owners. No retail hydration or
 * successful outer frame is implied by an expected predecessor exception. */
export interface SourceBattleOuterFrameTestFixture extends SourceObjectSchedulerTestFixture {
  matchGlobals: SourceObjectSchedulerTestFixture['matchGlobals'] & {
    byte15d4: number; byte66: number; halfD6: number; activeMask: number;
    slotTeam: number[]; teamRows103: TeamRow[];
  };
  systemGlobals: {controllerMask: number};
  teamRows103: TeamRow[];
}
type Fixture = SourceBattleOuterFrameTestFixture;
const NORMAL = '80053b30', PAUSED = '8000bef4', BURST = '8008b290';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[battle-outer-frame-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment), `expected ${fragment}, got ${message || 'success'}`);
}
/** Observe actual loads and scalar-store preflights. The optional after hook
 * runs after capturing the real descriptor, without supplying any ROM callee. */
function observe(run: () => void, before: (owner: object, key: PropertyKey) => void,
  after?: (owner: object, key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object, key: PropertyKey) => {
    before(owner, key); const result = original(owner, key); after?.(owner, key); return result;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
function retained(...records: object[]): () => void {
  const snapshots = records.map(record => Object.getOwnPropertyDescriptors(record));
  return () => records.forEach((record, index) => {
    const before = snapshots[index]!, after = Object.getOwnPropertyDescriptors(record);
    equal(Reflect.ownKeys(after).length, Reflect.ownKeys(before).length, 'retained property count');
    for (const key of Reflect.ownKeys(before)) {
      const a = Reflect.get(after, key) as PropertyDescriptor | undefined, b = Reflect.get(before, key) as PropertyDescriptor;
      check(a !== undefined && Object.is(a.value, b.value) && a.get === b.get && a.set === b.set &&
        a.writable === b.writable && a.configurable === b.configurable && a.enumerable === b.enumerable,
      `retained descriptor ${String(key)}`);
    }
  });
}
function graphRecords(x: Fixture): object[] {
  return [...new Set([...x.allocator.getSourceOwners(x.actor), x.objectBytes, x.nextObjectBytes,
    x.drawList, x.objectPool, x.descriptorPool, x.descriptorBytes, x.nextDescriptorBytes,
    x.hitPool, ...x.hitBytes, x.groups, ...Object.values(x.groups), x.hitBinding.pointer3fc,
    x.hitBinding.pointer27c, x.schedulerSources, x.actorSlots, ...x.slotTargets])]
    .filter(record => record !== x.matchGlobals && !x.teamRows103.includes(record as TeamRow));
}
function setup(x: Fixture, supplySystem = true) {
  const scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources);
  const sources: SourceBattleOuterFrameSources = supplySystem ? {scheduler, systemGlobals: x.systemGlobals} : {scheduler};
  const outer = createSourceBattleOuterFrameRuntime(sources);
  return {scheduler, sources, outer};
}
function untouchedScheduler(x: Fixture, run: () => void): void {
  const keep = retained(...graphRecords(x)), claimed = isSourceActorDoubleFrameClaimed(x.sourceActor);
  let schedulerReads = 0;
  observe(run, (owner, key) => {
    if (owner === x.objectBytes || owner === x.nextObjectBytes || owner === x.groups ||
      owner === x.actorSlots || (owner === x.matchGlobals && (key === 'maskD1' || key === 'maskD2')))
      schedulerReads++;
  });
  equal(schedulerReads, 0, 'outer prefix never starts group/slot traversal or object snapshots');
  equal(isSourceActorDoubleFrameClaimed(x.sourceActor), claimed, 'outer prefix never claims an actor frame');
  keep();
}
function closed(x: Fixture, scheduler: SourceObjectSchedulerRuntime, outer: SourceBattleOuterFrameRuntime): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'failure closes retained actual actor lifecycle');
  const keep = retained(...graphRecords(x), x.matchGlobals, x.systemGlobals, x.teamRows103, ...x.teamRows103);
  rejects(() => outer.runFrame(), 'permanently incomplete');
  for (const run of [() => scheduler.runGroup(9), () => scheduler.runSlots(8), () => scheduler.runWrapper(8)])
    rejects(run, 'exclusively owned');
  rejects(() => x.root.dispatchStoredRoot(x.child), 'exclusively owned');
  rejects(() => x.projectiles.spawn(x.actor, 1), 'incomplete');
  rejects(() => x.projectiles.assertActorComplete(x.actor), 'incomplete');
  rejects(() => x.hits.registerHit(x.child, 1), isSourceActorDoubleFrameClaimed(x.sourceActor) ? 'frame-owned actor' : 'incomplete');
  rejects(() => x.allocator.writeU8(x.nextChild, 0, 1), 'incomplete');
  rejects(() => requireSourceObjectSchedulerSnapshot(scheduler, x.allocator, x.child), 'private active');
  rejects(() => requireSourceObjectSchedulerInvocation(scheduler, x.root, x.child, 'prepare'), 'private active');
  rejects(() => closeSourceObjectSchedulerOuterFrame(scheduler, outer), 'private exact active');
  keep();
}
function emptyRow(row: TeamRow, charged: boolean): void {
  equal(row.byte1, 0, 'empty row clears participant count'); equal(row.byte2, 0, 'empty row clears controller count');
  equal(row.byte3, 0, 'empty row clears participant mask');
  for (let i = 4; i <= 9; i++) equal(Reflect.get(row, `byte${i}`), 255, 'empty row clears all six slot entries');
  equal(row.charged, charged, 'empty row retains charged state');
}
function roster(row: TeamRow, slots: readonly number[], controllers: number): void {
  equal(row.byte1, slots.length, 'matched participant count'); equal(row.byte2, controllers, 'matched controller count');
  equal(row.byte3, slots.reduce((mask, slot) => mask | 1 << slot, 0), 'matched participant mask');
  for (let i = 0; i < 6; i++) equal(Reflect.get(row, `byte${4 + i}`), slots[i] ?? 255, 'compact ordered slot roster');
}

export function runBattleOuterFrameSelfTests(make: () => SourceBattleOuterFrameTestFixture): void {
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources);
    const fake = {} as SourceBattleOuterFrameRuntime;
    const keep = retained(...graphRecords(x), x.matchGlobals, ...x.teamRows103);
    rejects(() => claimSourceObjectSchedulerOuterFrame(scheduler, fake), 'private outer-frame claim');
    rejects(() => closeSourceObjectSchedulerOuterFrame(scheduler, fake), 'private active outer failure');
    rejects(() => requireSourceBattleOuterFrameFailure(fake, scheduler), 'private active outer failure');
    for (const counterfeit of [{...scheduler}, Object.create(scheduler), {}, null, () => scheduler])
      rejects(() => createSourceBattleOuterFrameRuntime({scheduler: counterfeit as SourceObjectSchedulerRuntime}), 'genuine source scheduler');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'fake and idle helpers cannot poison an unclaimed graph');
    scheduler.runGroup(15); keep();
    const outer = createSourceBattleOuterFrameRuntime({scheduler, systemGlobals: x.systemGlobals});
    check(isSourceBattleOuterFrameRuntime(outer) && Object.isFrozen(outer), 'genuine frozen outer runtime');
    equal(outer.getSchedulerRuntime(), scheduler, 'retains genuine scheduler identity');
    equal(outer.getMatchGlobals(), x.matchGlobals, 'uses same original shared global owner');
    equal(x.matchGlobals.teamRows103, x.teamRows103, 'retains existing team reference array');
    check(!isPendingSourceBattleOuterFrameClaim(outer, scheduler), 'private claim transaction is no longer pending');
    for (const counterfeit of [{...outer}, Object.create(outer), {}, null, () => outer])
      check(!isSourceBattleOuterFrameRuntime(counterfeit), 'outer brand cannot be forged with copied methods or prototype');
    rejects(() => createSourceBattleOuterFrameRuntime({scheduler}), 'already outer-owned');
    rejects(() => claimSourceObjectSchedulerOuterFrame(scheduler, outer), 'private outer-frame claim');
    rejects(() => closeSourceObjectSchedulerOuterFrame(scheduler, outer), 'private exact active');
    rejects(() => requireSourceBattleOuterFrameFailure(outer, scheduler), 'private exact active');
    for (const run of [() => scheduler.runGroup(9), () => scheduler.runSlots(8), () => scheduler.runWrapper(8)])
      rejects(run, 'exclusively owned');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'idle authority refusals do not poison the claimed graph');
    keep(); untouchedScheduler(x, () => rejects(() => outer.runFrame(), NORMAL)); closed(x, scheduler, outer);
  }
  {
    const x = make(), scheduler = createSourceObjectSchedulerRuntime(x.schedulerSources); let attempted = false;
    observe(() => scheduler.runGroup(15), (owner, key) => {
      if (!attempted && owner === x.groups && key === '15') {
        attempted = true;
        rejects(() => createSourceBattleOuterFrameRuntime({scheduler}), 'already owned, active or incomplete');
      }
    });
    check(attempted && !hasIncompleteSourceActorDoubleLifecycle(x.sourceActor), 'active scheduler rejects an outer claim without poisoning its current call');
    const outer = createSourceBattleOuterFrameRuntime({scheduler});
    rejects(() => outer.runFrame(), NORMAL); closed(x, scheduler, outer);
  }
  {
    const x = make(), {scheduler, outer} = setup(x), y = make();
    const other = createSourceObjectSchedulerRuntime(y.schedulerSources), keep = retained(...graphRecords(y), y.matchGlobals);
    rejects(() => claimSourceObjectSchedulerOuterFrame(other, outer), 'private outer-frame claim');
    rejects(() => closeSourceObjectSchedulerOuterFrame(other, outer), 'private exact active');
    rejects(() => claimSourceObjectSchedulerOuterFrame({...scheduler}, outer), 'genuine scheduler');
    rejects(() => closeSourceObjectSchedulerOuterFrame({...scheduler}, outer), 'genuine scheduler');
    other.runGroup(15); keep();
    check(!hasIncompleteSourceActorDoubleLifecycle(y.sourceActor), 'wrong-scheduler and counterfeit helpers do not poison unrelated graph');
    rejects(() => outer.runFrame(), NORMAL); closed(x, scheduler, outer);
  }
  {
    const x = make(), {outer} = setup(x), events: string[] = [];
    observe(() => rejects(() => outer.runFrame(), NORMAL), (owner, key) => {
      const name = String(key), index = x.teamRows103.indexOf(owner as TeamRow);
      if (owner === x.matchGlobals && ['byte15d4', 'teamRows103', 'activeMask', 'byte66'].includes(name)) events.push(`g.${name}`);
      if (owner === x.teamRows103 && /^[0-3]$/.test(name)) events.push(`table.${name}`);
      if (index >= 0 && /^(byte[0-9]|byte10|meter|threshold30|charged)$/.test(name)) events.push(`r${index}.${name}`);
    });
    const expected = ['g.byte15d4', 'g.byte15d4', 'g.teamRows103'];
    for (let i = 0; i < 4; i++) expected.push('g.teamRows103', `table.${i}`,
      ...Array.from({length: 9}, (_, j) => `r${i}.byte${j + 1}`), ...Array(6).fill('g.activeMask'), `r${i}.byte1`);
    expected.push('g.byte66');
    equal(events.join(','), expected.join(','), 'all four empty rows reset in source order, each with six live mask loads and no burst or charge lookahead');
  }
  for (const mode of [0, 1, 127, 128, 255]) {
    const x = make(); x.matchGlobals.byte66 = mode;
    const {scheduler, outer} = setup(x);
    untouchedScheduler(x, () => rejects(() => outer.runFrame(), mode === 0 ? NORMAL : PAUSED));
    for (const row of x.teamRows103) emptyRow(row, true);
    equal(x.matchGlobals.byte66, mode, 'zero request retains raw mode');
    equal(x.matchGlobals.halfD6, 0x1234, 'zero request retains D6'); closed(x, scheduler, outer);
  }
  for (const [request, mode, clearD6] of [[0, 77, false], [1, 0, true], [2, 1, true],
    [3, 2, false], [127, 126, false], [128, 127, false], [255, 254, false]] as const) {
    const x = make(); x.matchGlobals.byte15d4 = request; x.matchGlobals.byte66 = 77;
    const {scheduler, outer} = setup(x); const order: string[] = [];
    observe(() => rejects(() => outer.runFrame(), mode === 0 ? NORMAL : PAUSED), (owner, key) => {
      if (owner === x.matchGlobals && ['byte15d4', 'byte66', 'halfD6'].includes(String(key))) order.push(String(key));
    });
    equal(order.join(','), ['byte15d4', ...(request === 0 ? [] : ['byte66', ...(clearD6 ? ['halfD6'] : [])]),
      'byte15d4', 'byte66'].join(','), 'signed request load, exact stores, unconditional clear, final mode load');
    equal(x.matchGlobals.byte15d4, 0, 'request is unconditionally consumed');
    equal(x.matchGlobals.byte66, mode, 'signed request minus one stores raw low byte');
    equal(x.matchGlobals.halfD6, clearD6 ? 0 : 0x1234, 'D6 store occurs only for signed results zero or one');
    closed(x, scheduler, outer);
  }
  for (const request of [0, 3, 127, 128, 255]) {
    const x = make(); x.matchGlobals.byte15d4 = request; Reflect.deleteProperty(x.matchGlobals, 'halfD6');
    const {outer} = setup(x); rejects(() => outer.runFrame(), request === 0 ? NORMAL : PAUSED);
    check(!Object.hasOwn(x.matchGlobals, 'halfD6'), 'unreached D6 is neither required nor synthesized');
  }
  for (const request of [1, 2]) {
    const x = make(); x.matchGlobals.byte15d4 = request; Reflect.deleteProperty(x.matchGlobals, 'halfD6');
    const {scheduler, outer} = setup(x); rejects(() => outer.runFrame(), 'halfD6: own data');
    equal(x.matchGlobals.byte66, request - 1, 'mode store survives later missing D6');
    equal(x.matchGlobals.byte15d4, request, 'failed D6 prevents request clear');
    equal(x.teamRows103[0]!.byte1, 91, 'request failure precedes first row write'); closed(x, scheduler, outer);
  }
  for (const request of [0, 2]) {
    const x = make(); x.matchGlobals.byte15d4 = request;
    Object.defineProperty(x.matchGlobals, 'byte15d4', {writable: false});
    const {scheduler, outer} = setup(x); rejects(() => outer.runFrame(), 'byte15d4: non-writable');
    equal(x.matchGlobals.byte15d4, request, 'request clear checks writable destination even when already zero');
    equal(x.matchGlobals.halfD6, request === 2 ? 0 : 0x1234, 'earlier D6 write survives failed request clear');
    equal(x.teamRows103[0]!.byte1, 91, 'no row refresh after failed clear'); closed(x, scheduler, outer);
  }
  {
    const x = make(); x.matchGlobals.byte15d4 = 1;
    Reflect.set(x.matchGlobals, 'byte66', NaN); Reflect.set(x.matchGlobals, 'halfD6', 'old overwritten cell');
    const {outer} = setup(x); rejects(() => outer.runFrame(), NORMAL);
    equal(x.matchGlobals.byte66, 0, 'store preflight does not load the overwritten old mode value');
    equal(x.matchGlobals.halfD6, 0, 'store preflight does not validate the overwritten old D6 value');
  }
  for (const request of [0, 2]) {
    const x = make(); x.matchGlobals.byte15d4 = request;
    Object.defineProperty(x.matchGlobals, 'byte66', {writable: false});
    const {scheduler, outer} = setup(x);
    rejects(() => outer.runFrame(), request === 0 ? NORMAL : 'byte66: non-writable');
    equal(x.matchGlobals.byte15d4, request === 0 ? 0 : 2, 'mode-store failure precedes request clear');
    equal(x.matchGlobals.halfD6, 0x1234, 'mode-store failure precedes D6 store');
    closed(x, scheduler, outer);
  }
  {
    const x = make(); Reflect.deleteProperty(x.matchGlobals, 'byte66'); const {scheduler, outer} = setup(x);
    rejects(() => outer.runFrame(), 'byte66: own data');
    for (const row of x.teamRows103) emptyRow(row, true);
    closed(x, scheduler, outer);
  }
  for (const value of [-1, 256, 0.5, NaN, Infinity, '1', undefined]) {
    const x = make(); Reflect.set(x.matchGlobals, 'byte15d4', value);
    const {scheduler, outer} = setup(x), keep = retained(x.matchGlobals, ...x.teamRows103);
    rejects(() => outer.runFrame(), 'raw unsigned source integer'); keep(); closed(x, scheduler, outer);
  }
  {
    const x = make(); x.matchGlobals.activeMask = 0xc0;
    Reflect.deleteProperty(x.matchGlobals, 'slotTeam');
    for (const row of x.teamRows103) for (const key of ['byte0', 'byte10', 'meter', 'threshold30']) Reflect.deleteProperty(row, key);
    const {outer} = setup(x, false); rejects(() => outer.runFrame(), NORMAL);
    for (const row of x.teamRows103) emptyRow(row, true);
  }
  {
    const x = make(); x.matchGlobals.activeMask = 0x3f; x.systemGlobals.controllerMask = 0x25;
    const {scheduler, outer} = setup(x); untouchedScheduler(x, () => rejects(() => outer.runFrame(), NORMAL));
    roster(x.teamRows103[0]!, [0, 2], 2); roster(x.teamRows103[1]!, [1, 3], 0);
    roster(x.teamRows103[2]!, [4], 0); roster(x.teamRows103[3]!, [5], 1);
    for (const row of x.teamRows103) equal(row.charged, false, 'populated non-burst row clears insufficient charge');
    closed(x, scheduler, outer);
  }
  for (const team of [0, 127, 128, 255]) {
    const x = make(); x.matchGlobals.activeMask = 255; x.matchGlobals.slotTeam.fill(team);
    x.teamRows103[0]!.byte0 = team; x.systemGlobals.controllerMask = 255;
    const {outer} = setup(x); rejects(() => outer.runFrame(), NORMAL);
    roster(x.teamRows103[0]!, [0, 1, 2, 3, 4, 5], 6);
  }
  {
    const x = make(); x.matchGlobals.activeMask = 63; x.matchGlobals.slotTeam.fill(255);
    x.teamRows103[0]!.byte0 = 255; x.systemGlobals.controllerMask = 128;
    const {outer} = setup(x); rejects(() => outer.runFrame(), NORMAL);
    roster(x.teamRows103[0]!, [0, 1, 2, 3, 4, 5], 0);
  }
  {
    const x = make(); x.matchGlobals.slotTeam.fill(0); const {outer} = setup(x); let reads = 0;
    observe(() => rejects(() => outer.runFrame(), NORMAL), (owner, key) => {
      if (owner === x.matchGlobals && key === 'activeMask') x.matchGlobals.activeMask = reads < 6 ? 1 << reads++ : 0;
    });
    equal(reads, 6, 'all six live mask sites were reached'); roster(x.teamRows103[0]!, [0, 1, 2, 3, 4, 5], 0);
  }
  {
    const x = make(); x.matchGlobals.activeMask = 63; x.matchGlobals.slotTeam.fill(1); x.matchGlobals.slotTeam[0] = 0;
    const {outer} = setup(x); let changed = 0;
    observe(() => rejects(() => outer.runFrame(), NORMAL), () => {}, (owner, key) => {
      if (owner === x.matchGlobals.slotTeam && changed < 5 && key === String(changed)) {
        changed++; x.matchGlobals.slotTeam[changed] = 0;
      }
    });
    equal(changed, 5, 'next slot-team cell changes only after prior actual load');
    roster(x.teamRows103[0]!, [0, 1, 2, 3, 4, 5], 0);
  }
  {
    const x = make(); x.matchGlobals.activeMask = 63; x.matchGlobals.slotTeam.fill(0);
    const {outer} = setup(x); let controllers = 0;
    observe(() => rejects(() => outer.runFrame(), NORMAL), (owner, key) => {
      if (owner === x.systemGlobals && key === 'controllerMask') {
        x.systemGlobals.controllerMask = controllers % 2 === 0 ? 1 << controllers : 0; controllers++;
      }
    });
    equal(controllers, 6, 'participant owner is freshly read only after each matching slot');
    roster(x.teamRows103[0]!, [0, 1, 2, 3, 4, 5], 3);
  }
  {
    const x = make(), row = x.teamRows103[0]!; x.matchGlobals.activeMask = 3;
    x.matchGlobals.slotTeam[0] = 0; x.matchGlobals.slotTeam[1] = 1;
    const {outer} = setup(x); let changed = false;
    observe(() => rejects(() => outer.runFrame(), NORMAL), () => {}, (owner, key) => {
      if (!changed && owner === x.matchGlobals.slotTeam && key === '0') {changed = true; row.byte0 = 1;}
    });
    check(changed, 'row team byte changed after first actual slot-team load'); roster(row, [0, 1], 0);
  }
  {
    const x = make(), row = x.teamRows103[0]!; x.matchGlobals.activeMask = 1;
    row.meter = 10; row.threshold30 = 100;
    const {outer} = setup(x); let changed = false;
    observe(() => rejects(() => outer.runFrame(), NORMAL), () => {}, (owner, key) => {
      if (!changed && owner === row && key === 'meter') {changed = true; row.threshold30 = 5; row.meter = 0;}
    });
    check(changed, 'threshold changed after actual meter descriptor capture');
    equal(row.charged, true, 'source keeps captured meter but reads threshold freshly afterward');
  }
  {
    const x = make(), row = x.teamRows103[0]!; x.matchGlobals.activeMask = 1;
    Reflect.deleteProperty(row, 'byte10'); Reflect.deleteProperty(row, 'meter'); Reflect.deleteProperty(row, 'threshold30');
    const {outer} = setup(x); let maskReads = 0;
    observe(() => rejects(() => outer.runFrame(), NORMAL), () => {}, (owner, key) => {
      if (owner === x.matchGlobals && key === 'activeMask' && ++maskReads === 6) row.byte1 = 255;
    });
    equal(row.byte1, 255, 'explicit late mutation supplies raw negative participant count');
    equal(row.charged, true, 'signed nonpositive count skips burst and charge fields after refresh');
  }
  for (const [meter, threshold, charged] of [[0, 0, true], [0, 1, false], [65535, 32768, true],
    [32768, 65535, false], [65535, 65535, true], [32767, 32768, false]] as const) {
    const x = make(), row = x.teamRows103[0]!; x.matchGlobals.activeMask = 1;
    row.meter = meter; row.threshold30 = threshold; row.charged = !charged;
    const {outer} = setup(x); rejects(() => outer.runFrame(), NORMAL);
    equal(row.charged, charged, 'normal charge compares both halfwords unsigned');
    equal(row.meter, meter, 'normal comparison never changes meter');
    equal(row.threshold30, threshold, 'normal comparison never changes threshold');
    for (const empty of x.teamRows103.slice(1)) emptyRow(empty, true);
  }
  for (const burstRow of [0, 1, 2, 3]) for (const activeBurst of [1, 128, 255]) {
    const x = make(); x.matchGlobals.activeMask = 15; x.matchGlobals.slotTeam = [0, 1, 2, 3, 0, 0];
    const row = x.teamRows103[burstRow]!; row.byte10 = activeBurst;
    Reflect.deleteProperty(row, 'meter'); Reflect.deleteProperty(row, 'threshold30');
    const keepLater = retained(...x.teamRows103.slice(burstRow + 1)), {scheduler, outer} = setup(x);
    untouchedScheduler(x, () => rejects(() => outer.runFrame(), BURST));
    equal(row.charged, false, 'burst row clears charged before first mandatory missing callee');
    roster(row, [burstRow], 0); keepLater(); closed(x, scheduler, outer);
  }
  {
    // Source order includes independent load and scalar-store preflight events.
    const x = make(), row = x.teamRows103[0]!; x.matchGlobals.byte15d4 = 2;
    x.matchGlobals.activeMask = 3; x.matchGlobals.slotTeam[1] = 0; x.systemGlobals.controllerMask = 1;
    const {outer} = setup(x), events: string[] = [];
    observe(() => rejects(() => outer.runFrame(), PAUSED), (owner, key) => {
      const name = String(key);
      if (owner === x.matchGlobals && ['byte15d4', 'byte66', 'halfD6', 'activeMask', 'slotTeam'].includes(name)) events.push(`g.${name}`);
      if (owner === row && /^(byte[0-9]|byte10|meter|threshold30|charged)$/.test(name)) events.push(`r.${name}`);
      if (owner === x.matchGlobals.slotTeam && /^[0-5]$/.test(name)) events.push(`s.${name}`);
      if (owner === x.systemGlobals && key === 'controllerMask') events.push('p.controllerMask');
    });
    const begin = ['g.byte15d4', 'g.byte66', 'g.halfD6', 'g.byte15d4',
      ...Array.from({length: 9}, (_, i) => `r.byte${i + 1}`)];
    const slot = (i: number, controller: boolean) => ['g.activeMask', 'r.byte0', 'g.slotTeam', `s.${i}`,
      'r.byte1', 'r.byte1', 'p.controllerMask', ...(controller ? ['r.byte2', 'r.byte2'] : []),
      'r.byte3', 'r.byte3', `r.byte${4 + i}`];
    const expected = [...begin, ...slot(0, true), ...slot(1, false),
      ...Array(4).fill('g.activeMask'), 'r.byte1', 'r.byte10', 'r.meter', 'r.threshold30', 'r.charged', 'r.charged'];
    equal(events.slice(0, expected.length).join(','), expected.join(','),
    'request stores, row reset, matching loads/counts/mask/roster, meter then threshold then charged preflight');
    equal(events.at(-1), 'g.byte66', 'outer mode is loaded only after four team refreshes');
  }
  for (const destination of Array.from({length: 9}, (_, i) => `byte${i + 1}`)) {
    for (const missing of [false, true]) {
      const x = make(), row = x.teamRows103[0]!, stopped = Number(destination.slice(4));
      if (missing) Reflect.deleteProperty(row, destination); else Object.defineProperty(row, destination, {writable: false});
      const {scheduler, outer} = setup(x);
      rejects(() => outer.runFrame(), `${destination}: ${missing ? 'own data' : 'non-writable'}`);
      for (let i = 1; i < stopped; i++) equal(Reflect.get(row, `byte${i}`), i <= 3 ? 0 : 255, 'earlier reset stores survive late scalar refusal');
      for (let i = stopped + 1; i <= 9; i++) equal(Reflect.get(row, `byte${i}`), 90 + i, 'later reset stores remain untouched');
      if (!missing) equal(Reflect.get(row, destination), 90 + stopped, 'failed scalar store is not partially performed');
      equal(x.matchGlobals.byte15d4, 0, 'request clear precedes row-store refusal'); closed(x, scheduler, outer);
    }
  }
  for (const field of ['activeMask', 'slotTeam', 'controllerMask', 'meter', 'threshold30', 'charged'] as const) {
    const x = make(), row = x.teamRows103[0]!; x.matchGlobals.byte15d4 = 2; x.matchGlobals.activeMask = 1;
    const owner = field === 'controllerMask' ? x.systemGlobals : ['activeMask', 'slotTeam'].includes(field) ? x.matchGlobals : row;
    Reflect.deleteProperty(owner, field); const {scheduler, outer} = setup(x);
    rejects(() => outer.runFrame(), `${field}: own data`);
    equal(x.matchGlobals.byte66, 1, 'request mode store survives later missing field');
    equal(x.matchGlobals.halfD6, 0, 'D6 store survives later missing field');
    equal(row.byte1, ['activeMask', 'slotTeam'].includes(field) ? 0 : 1, 'participant increment precedes controller and charge reads');
    equal(row.byte4, ['activeMask', 'slotTeam', 'controllerMask'].includes(field) ? 255 : 0, 'roster store follows controller read');
    closed(x, scheduler, outer);
  }
  for (const field of ['meter', 'threshold30'] as const) for (const invalid of [-1, 65536, 1.5, NaN]) {
    const x = make(), row = x.teamRows103[0]!; x.matchGlobals.activeMask = 1; row[field] = invalid;
    const {scheduler, outer} = setup(x); rejects(() => outer.runFrame(), `${field}: raw unsigned`);
    roster(row, [0], 0); equal(row.charged, true, 'bad halfword refuses before charged store'); closed(x, scheduler, outer);
  }
  for (const activeBurst of [0, 1]) {
    const x = make(), row = x.teamRows103[0]!; x.matchGlobals.activeMask = 1; row.byte10 = activeBurst;
    Object.defineProperty(row, 'charged', {writable: false}); const {scheduler, outer} = setup(x);
    rejects(() => outer.runFrame(), 'charged: non-writable'); roster(row, [0], 0);
    equal(row.charged, true, 'charged scalar preflight prevents store on both branches'); closed(x, scheduler, outer);
  }
  {
    const x = make(); x.matchGlobals.activeMask = 1; x.matchGlobals.slotTeam[0] = 99;
    const {outer} = setup(x, false); rejects(() => outer.runFrame(), NORMAL);
    for (const row of x.teamRows103) emptyRow(row, true);
  }
  {
    const x = make(); x.matchGlobals.activeMask = 1; const {scheduler, outer} = setup(x, false);
    rejects(() => outer.runFrame(), 'systemGlobals: own data');
    equal(x.teamRows103[0]!.byte1, 1, 'missing participant owner is reached after matched count increment');
    equal(x.teamRows103[0]!.byte4, 255, 'missing participant owner precedes compact slot store'); closed(x, scheduler, outer);
  }
  for (const accessor of ['request', 'row', 'controller'] as const) {
    const x = make(); x.matchGlobals.activeMask = 1; let getterCalls = 0;
    const owner = accessor === 'request' ? x.matchGlobals : accessor === 'row' ? x.teamRows103[0]! : x.systemGlobals;
    const key = accessor === 'request' ? 'byte15d4' : accessor === 'row' ? 'byte1' : 'controllerMask';
    Object.defineProperty(owner, key, {get() {getterCalls++; return 0;}, configurable: true});
    const {scheduler, outer} = setup(x); rejects(() => outer.runFrame(), `${key}: own data`);
    equal(getterCalls, 0, 'own-data admission never invokes a getter'); closed(x, scheduler, outer);
  }
  {
    const x = make(); x.frame.bindActor(x.actor);
    check(isSourceActorDoubleFrameClaimed(x.sourceActor), 'fixture explicitly binds actor to its existing frame');
    const {scheduler, outer} = setup(x);
    untouchedScheduler(x, () => rejects(() => outer.runFrame(), NORMAL)); closed(x, scheduler, outer);
  }
  for (const kind of ['table', 'row', 'slots', 'system'] as const) {
    const x = make(); x.matchGlobals.activeMask = 3; x.matchGlobals.slotTeam[1] = 0;
    const {scheduler, sources, outer} = setup(x); let changed = false, rosterStores = 0;
    observe(() => rejects(() => outer.runFrame(), kind === 'row' ? 'source storage alias' : 'canonical owner changed'),
      (owner, key) => {
        if (changed) return;
        if (kind === 'table' && owner === x.teamRows103[0] && key === 'byte1') {
          changed = true; x.matchGlobals.teamRows103 = [...x.teamRows103];
        } else if (kind === 'row' && owner === x.teamRows103[0] && key === 'byte1') {
          changed = true; x.teamRows103[1] = x.teamRows103[0]!;
        } else if (kind === 'slots' && owner === x.teamRows103[0] && key === 'byte4' && ++rosterStores === 2) {
          changed = true; x.matchGlobals.slotTeam = [...x.matchGlobals.slotTeam];
        } else if (kind === 'system' && owner === x.systemGlobals && key === 'controllerMask') {
          changed = true; sources.systemGlobals = {...x.systemGlobals};
        }
      });
    check(changed, 'owner mutation occurred at reached source operation'); closed(x, scheduler, outer);
  }
  for (const alias of ['table', 'row', 'slots', 'system'] as const) {
    const x = make(); x.matchGlobals.activeMask = 1;
    const {scheduler, sources, outer} = setup(x);
    if (alias === 'table') Reflect.set(x.matchGlobals, 'teamRows103', x.objectBytes);
    if (alias === 'row') Reflect.set(x.teamRows103, '0', x.sourceActor);
    if (alias === 'slots') Reflect.set(x.matchGlobals, 'slotTeam', x.teamRows103);
    if (alias === 'system') sources.systemGlobals = x.matchGlobals as unknown as Fixture['systemGlobals'];
    rejects(() => outer.runFrame(), 'source storage alias'); closed(x, scheduler, outer);
  }
  for (const ownerName of ['actorSlots', 'schedulerSources', 'rootSources', 'stageState', 'drawList', 'hitBinding'] as const) {
    const x = make(); x.matchGlobals.activeMask = 1; const {scheduler, sources, outer} = setup(x);
    sources.systemGlobals = x[ownerName] as unknown as Fixture['systemGlobals'];
    rejects(() => outer.runFrame(), 'source storage alias');
    equal(x.teamRows103[0]!.byte1, 1, 'identity-only alias rejection occurs at reached participant-owner access');
    closed(x, scheduler, outer);
  }
  for (const [scope, shadow] of [['global', 'byteD6'], ['global', 'half214'], ['global', 'byte15d9'],
    ['global', 'byteCB'], ['global', 'byte103'], ['global', 'field103'], ['global', '259'],
    ['global', 'byte126'], ['global', 'byte127'], ['global', 'word126'], ['global', '294'], ['global', '295'],
    ['global', 'byte1DA'], ['global', '475'], ['row', 'half30'], ['row', 'byteF'], ['row', 'half32'], ['row', 'word126'],
    ['row', '15'], ['row', 'byte30'], ['row', 'byte31'], ['row', 'byte32'], ['row', 'byte33'],
    ['row', '49'], ['row', '51'], ['global', '215'], ['global', '203'], ['global', '208'],
    ['global', 'bytecb'], ['global', 'byted0'], ['system', 'byte2'], ['system', '2']] as const) {
    const x = make(); x.matchGlobals.activeMask = 1;
    const owner = scope === 'global' ? x.matchGlobals : scope === 'row' ? x.teamRows103[0]! : x.systemGlobals;
    Reflect.set(owner, shadow, 0); const {scheduler, outer} = setup(x);
    rejects(() => outer.runFrame(), 'competing source cell owner'); closed(x, scheduler, outer);
  }
  for (const when of ['request', 'D6', 'row', 'controller', 'charge'] as const) {
    const x = make(); x.matchGlobals.byte15d4 = 2; x.matchGlobals.activeMask = 1;
    const {scheduler, outer} = setup(x); let attempted = false;
    observe(() => rejects(() => outer.runFrame(), 'reentry'), (owner, key) => {
      const reached = when === 'request' ? owner === x.matchGlobals && key === 'byte15d4' :
        when === 'D6' ? owner === x.matchGlobals && key === 'halfD6' :
        when === 'row' ? owner === x.teamRows103[0] && key === 'byte5' :
        when === 'controller' ? owner === x.systemGlobals && key === 'controllerMask' :
        owner === x.teamRows103[0] && key === 'charged';
      if (!attempted && reached) {attempted = true; try {outer.runFrame();} catch {/* Caught reentry still poisons the active prefix. */}}
    });
    check(attempted, 'same outer runtime was reentered at an actual reached operation'); closed(x, scheduler, outer);
  }
  {
    const x = make(), {scheduler, sources, outer} = setup(x);
    sources.scheduler = {...scheduler}; const keep = retained(x.matchGlobals, ...x.teamRows103);
    rejects(() => outer.runFrame(), 'canonical scheduler graph changed'); keep(); closed(x, scheduler, outer);
  }
  console.log('[battle-outer-frame-test] PASS: genuine closure-only scheduler ownership; signed pause request and four live six-slot team refreshes preserve exact ordered writes before mandatory 8b290, 53b30 or bef4 refusal; lazy fields, unsigned charge, scalar faults, owner aliases, mutation and caught reentry permanently close the retained graph; no scheduler snapshots, actor frame, complete battle frame, retail execution or browser claim');
}
