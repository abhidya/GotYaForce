/** Bounded source8005913c and its first genuine helper80068df8.
 * Evidence: actor-cue0-lifecycle-evidence-2026-11-14.md and authenticated archived
 * instruction reader. Movement3 performs actual6a750(1b), then6a6fc(1b),
 * ignoring both native0/1 results. Other movement reaches genuine68df8 and
 * optionally continues genuine699d8 input testers. Native1 returns; native0
 * reaches either the optional genuine69814/696f4/69038/69354/68f9c tail or
 * its historical69814 boundary. Without testers the699d8 refusal remains. No no-op substitute,
 * arbitrary callback, host floor contract, hydration or live tick is supplied.
 *
 * Actual3d6e4 writes the returned ground height before732/674 reads. Uphill
 * rollback preserves the source raw-word load/store order. Ledge correction
 * restores originalY before exact fsubs/fmuls/fmadds, then refuses positive
 * frsqrte. Zero norm has an exact zero-numerator fdivs subset, retaining speed
 * or slope stores before unsupported452a0/6a5a4. No path fabricates return1.
 *
 * Existing actual/world/movement/attribute/history/cue owners stay canonical;
 * only previously absent732 has explicit partial storage. Finite exact f32,
 * RN00/NI0, stable synchronous non-proxy own-data owners are admission bounds,
 * not original-game parity. Methods/receivers and distinct vectors are retained,
 * actor claims permanent, and reached failures preserve previous writes.
 * Host-only incomplete-call poison prevents edited flags/cues bypassing them.
 */
import type {RomActor} from './actor.js';
import {isSourceActorCue0TailRuntime, hasIncompleteSourceActorCue0Tail,
  type SourceActorCue0TailRuntime} from './actor-cue0-tail.js';
import {isSourceActorInputChargeRuntime} from './actor-input-charge.js';
import {isSourceActorInputTestersRuntime, hasIncompleteSourceActorInputTesters,
  type SourceActorInputTestersRuntime} from './actor-input-testers.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorMovementFollowupRuntime, SourceActorMovementFollowupBinding} from './actor-movement-followup.js';
import type {SourceActorAttributeRefreshRuntime, SourceActorAttributeRefreshBinding} from './actor-attribute-refresh.js';
import type {SourceActorTransformHistoryBinding} from './actor-transform-history.js';
import {isSourceActorTerrainQueryRuntime, type SourceActorTerrainQueryRuntime,
  type SourceActorTerrainGlobals} from './actor-terrain-query.js';
import {isSourceActorCueResetRuntime, type SourceActorCueResetRuntime,
  type SourceActorCueResetBinding} from './actor-cue-reset.js';
import type {SourceActorAnimationDispatchBinding} from './actor-animation-dispatch.js';
import type {SourceJointVector} from './joint-animation-feedback.js';
import {addSourceFloat32, fusedMultiplyAddSourceFloat32} from './source-float.js';

export interface SourceActorCue0LifecycleBinding {byte732: number}
export interface SourceActorCue0LifecycleSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding' | 'getMappingActor'>;
  movement: Pick<SourceActorMovementFollowupRuntime, 'getActualActor' | 'getActorBinding'>;
  attribute: Pick<SourceActorAttributeRefreshRuntime, 'getActualActor' | 'getActorBinding'>;
  terrain: SourceActorTerrainQueryRuntime;
  cues: SourceActorCueResetRuntime;
  /** Genuine ordered699d8 helpers; absence preserves the historical boundary. */
  inputTesters?: SourceActorInputTestersRuntime;
  /** Genuine remaining ordered cue0 helpers; absence retains the69814 boundary. */
  tail?: SourceActorCue0TailRuntime;
}
export interface SourceActorCue0LifecycleRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorCue0LifecycleBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getMappingActor(identity: symbol): object;
  getMovementBinding(identity: symbol): SourceActorMovementFollowupBinding;
  getAttributeBinding(identity: symbol): Partial<SourceActorAttributeRefreshBinding>;
  getActorBinding(identity: symbol): Partial<SourceActorCue0LifecycleBinding>;
  getTerrainRuntime(): SourceActorTerrainQueryRuntime;
  getTerrainGlobals(): SourceActorTerrainGlobals;
  getHistoryBinding(identity: symbol): SourceActorTransformHistoryBinding;
  getCueRuntime(): SourceActorCueResetRuntime;
  getInputTestersRuntime(): SourceActorInputTestersRuntime | undefined;
  getTailRuntime(): SourceActorCue0TailRuntime | undefined;
  getCueBinding(identity: symbol): Partial<SourceActorCueResetBinding>;
  getDispatchBinding(identity: symbol): SourceActorAnimationDispatchBinding;
  /** Retained additional owners and vectors, no scalar copies or synthetic owner. */
  getSourceOwners(identity: symbol): readonly object[];
  /** Host-only assertion, with no source scalar reads. */
  assertActorComplete(identity: symbol): void;
  updateTerrain(identity: symbol): 0 | 1;
  dispatchCue0(identity: symbol): void;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
const incomplete = new WeakSet<object>();
export function isSourceActorCue0LifecycleRuntime(value: unknown): value is SourceActorCue0LifecycleRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
export function hasIncompleteSourceActorCue0Lifecycle(actual: object): boolean {return incomplete.has(actual);}
function fail(reason: string): never {
  throw Error(`[actor-cue0-lifecycle] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(value: unknown, key: string, writable = false): unknown {
  if (value === null || typeof value !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(value, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, key: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max)
    fail(`${key}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
function float(value: unknown, key: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${key}: finite exact source float32 required`);
  return value;
}
const sub32 = (a: number, b: number): number => addSourceFloat32(a, -b);
// Exact binary32 product fits binary64's significand before this one rounding.
const mul32 = (a: number, b: number): number => float(Math.fround(a * b), 'fmuls result');
export function createSourceActorCue0LifecycleRuntime(sources: SourceActorCue0LifecycleSources): SourceActorCue0LifecycleRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (owner: unknown, key: string): unknown => {const result = own(owner, key); check(); return result;};
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const capture = (name: keyof SourceActorCue0LifecycleSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const result = Reflect.apply(method, receiver, args); check(); return result;};
  };
  const terrainRuntime = read(sources, 'terrain'), cueRuntime = read(sources, 'cues');
  if (!isSourceActorTerrainQueryRuntime(terrainRuntime)) fail('terrain requires genuine source runtime');
  if (!isSourceActorCueResetRuntime(cueRuntime)) fail('cues requires genuine source runtime');
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const worldMapping = capture('world', 'getMappingActor');
  const movementActor = capture('movement', 'getActualActor'), movementBinding = capture('movement', 'getActorBinding');
  const attributeActor = capture('attribute', 'getActualActor'), attributeBinding = capture('attribute', 'getActorBinding');
  const terrainActor = capture('terrain', 'getActualActor'), terrainGlobals = capture('terrain', 'getTerrainGlobals');
  const terrainHistory = capture('terrain', 'getHistoryBinding'), groundQuery = capture('terrain', 'query8003d6e4');
  const cueActor = capture('cues', 'getActualActor'), cueMapping = capture('cues', 'getMappingActor');
  const cueBinding = capture('cues', 'getActorBinding'), cueDispatch = capture('cues', 'getDispatchBinding');
  const upperCue = capture('cues', 'dispatchUpperBodyCue'), fullCue = capture('cues', 'dispatchFullBodyCue');
  const testersOption = Object.getOwnPropertyDescriptor(sources, 'inputTesters');
  const testers = testersOption === undefined ? undefined : read(sources, 'inputTesters');
  if (testersOption !== undefined && !isSourceActorInputTestersRuntime(testers))
    fail('inputTesters requires genuine source runtime');
  const testerActor = testers === undefined ? undefined : capture('inputTesters', 'getActualActor');
  const testerWorld = testers === undefined ? undefined : capture('inputTesters', 'getWorldBinding');
  const testerMapping = testers === undefined ? undefined : capture('inputTesters', 'getMappingActor');
  const testerAttribute = testers === undefined ? undefined : capture('inputTesters', 'getAttributeBinding');
  const testerStatus = testers === undefined ? undefined : capture('inputTesters', 'getStatusBinding');
  const testerOwners = testers === undefined ? undefined : capture('inputTesters', 'getSourceOwners');
  const testerDescriptors = testers === undefined ? undefined : capture('inputTesters', 'getKnownDescriptorRecords');
  const runTesters = testers === undefined ? undefined : capture('inputTesters', 'updateActor');
  const testerCharge = testers === undefined ? undefined : capture('inputTesters', 'getChargeRuntime');
  const testerChargeBinding = testers === undefined ? undefined : capture('inputTesters', 'getChargeBinding');
  const tailOption = Object.getOwnPropertyDescriptor(sources, 'tail');
  const tail = tailOption === undefined ? undefined : read(sources, 'tail');
  if (tailOption !== undefined && !isSourceActorCue0TailRuntime(tail)) fail('tail requires genuine source runtime');
  const tailActor = tail === undefined ? undefined : capture('tail', 'getActualActor');
  const tailWorld = tail === undefined ? undefined : capture('tail', 'getWorldBinding');
  const tailMapping = tail === undefined ? undefined : capture('tail', 'getMappingActor');
  const tailMovement = tail === undefined ? undefined : capture('tail', 'getMovementBinding');
  const tailStatus = tail === undefined ? undefined : capture('tail', 'getStatusBinding');
  const tailBorg = tail === undefined ? undefined : capture('tail', 'getActualBorg');
  const tailCharge = tail === undefined ? undefined : capture('tail', 'getChargeRuntime');
  const tailChargeBinding = tail === undefined ? undefined : capture('tail', 'getChargeBinding');
  const tailGlobal = tail === undefined ? undefined : capture('tail', 'getGlobal');
  const tailCues = tail === undefined ? undefined : capture('tail', 'getCueRuntime');
  const tailCue = tail === undefined ? undefined : capture('tail', 'getCueBinding');
  const tailDispatch = tail === undefined ? undefined : capture('tail', 'getDispatchBinding');
  const tailBinding = tail === undefined ? undefined : capture('tail', 'getActorBinding');
  const tailOwners = tail === undefined ? undefined : capture('tail', 'getSourceOwners');
  const tailTeams = tail === undefined ? undefined : capture('tail', 'getKnownTeamStorageOwners');
  const runTail = tail === undefined ? undefined : capture('tail', 'updateActor');
  const charge = tailCharge?.();
  if (tail !== undefined && !isSourceActorInputChargeRuntime(charge)) fail('tail charge requires genuine source runtime');
  const captureCharge = (key: 'getGlobal' | 'getData' | 'getAttributeBinding' | 'getKnownDescriptorRecords') => {
    if (charge === undefined) return undefined;
    const method = read(charge, key);
    if (typeof method !== 'function') fail(`tail charge ${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const result = Reflect.apply(method, charge, args); check(); return result;};
  };
  const chargeGlobal = captureCharge('getGlobal'), chargeDescriptors = captureCharge('getKnownDescriptorRecords');
  const global = tailGlobal === undefined ? undefined : record(tailGlobal(), 'tail match globals');
  const chargeData = captureCharge('getData'), chargeAttribute = captureCharge('getAttributeBinding');
  const data = chargeData === undefined ? undefined : record(chargeData(), 'tail charge data');
  const ownerList = (value: unknown, where: string): object[] => {
    if (!Array.isArray(value)) fail(`${where}: actual owner array required`);
    return value.map(owner => record(owner, where));
  };
  const terrain = record(terrainGlobals(), 'terrain globals8043625c') as SourceActorTerrainGlobals;
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const byte = (owner: unknown, key: string): number => integer(read(owner, key), 0, 255, key);
  const signedByte = (owner: unknown, key: string): number => byte(owner, key) << 24 >> 24;
  const f = (owner: unknown, key: string): number => float(read(owner, key), key);
  interface Entry {
    actual: RomActor; position: SourceJointVector; savedPosition: SourceJointVector;
    world: SourceActorWorldMatrixBinding; mapping: object; movement: SourceActorMovementFollowupBinding;
    attribute: Partial<SourceActorAttributeRefreshBinding>; history: SourceActorTransformHistoryBinding;
    cue: Partial<SourceActorCueResetBinding>; dispatch: SourceActorAnimationDispatchBinding;
    binding: Partial<SourceActorCue0LifecycleBinding>; extras: readonly object[];
    historyVectors: ReadonlyArray<readonly [string, object]>;
    testerOwners?: readonly object[]; testerStatus?: object;
    tailOwners?: readonly object[]; tailBinding?: object; tailStatus?: object; tailBorg?: object; tailCharge?: object;
  }
  const owners = (e: Entry): object[] => [e.actual, e.position, e.savedPosition, e.world, e.mapping,
    e.movement, e.attribute, e.history, e.cue, e.dispatch, e.binding, ...e.historyVectors.map(([, owner]) => owner),
    ...(e.testerOwners ?? []), ...(e.testerStatus === undefined ? [] : [e.testerStatus]),
    ...(e.tailOwners ?? []), ...(e.tailBorg === undefined ? [] : [e.tailBorg]),
    // Only these recognized canonical records may occur in both children.
    ...(e.tailStatus === undefined || e.testerStatus !== undefined ? [] : [e.tailStatus]),
    ...(e.tailCharge === undefined || e.testerOwners !== undefined ? [] : [e.tailCharge])];
  const teamOwners = (): object[] => tailTeams === undefined ? [] : ownerList(tailTeams(), 'known tail team storage');
  const assertTeamOwners = (e: Entry): void => {
    if (global === undefined) return;
    const records = owners(e), descriptors = ownerList(chargeDescriptors!(), 'known charge descriptors');
    const forbidden = (owner: object): boolean => owner === terrain || records.includes(owner) || assigned.has(owner);
    if (global === data || forbidden(global) || forbidden(data!) ||
        descriptors.some(owner => owner === global || owner === data || forbidden(owner)))
      fail('tail global/data/descriptor aliases a cue0 source owner');
    if (teamOwners().some(owner => owner === global || owner === data || forbidden(owner) || descriptors.includes(owner)))
      fail('tail team storage aliases a cue0 source owner or charge descriptor');
  };
  const noShadows = (e: Entry): void => {
    const canonical = new Map<string, object>([
      ['controlWord', e.actual], ['pos', e.actual], ['savedGroundPos', e.actual],
      ['hoverOffset668', e.actual], ['tierScale', e.actual], ['hSpeed', e.actual],
      ['lockYaw', e.actual], ['slopeMode698', e.actual], ['byte661', e.movement],
      ['mode4a0', e.world], ['field674', e.attribute], ['byte732', e.binding],
      ['previousStepHeight6d4', e.history], ['ubCue', e.actual], ['fbCue', e.actual],
    ]);
    const aliases = ['word5e0', 'flags5e0', 'field5e0', 'field4a0', 'actorMode4a0',
      'field661', 'move661', 'field668', 'hover668', 'field674Alias', 'stepThreshold674',
      'field732', 'flags732', 'ledge732', 'field5f8', 'scale5f8', 'field44', 'speed44',
      'field5ae', 'yaw5ae', 'field698', 'field20', 'field24', 'field28', 'field2c', 'field30', 'field34',
      'positionY24', 'savedY30'];
    for (const owner of [...owners(e), terrain, ...(global === undefined ? [] : [global, data!]), ...teamOwners()]) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing cue0-lifecycle storage on another owner`);
        check();
      }
      for (const key of aliases) {
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing cue0-lifecycle storage alias`);
        check();
      }
    }
  };
  const admit = (id: symbol, e: Entry): void => {
    stable(worldActor(id), e.actual, 'world actor'); stable(worldBinding(id), e.world, 'world binding');
    stable(worldMapping(id), e.mapping, 'world mapping');
    stable(movementActor(id), e.actual, 'movement actor'); stable(movementBinding(id), e.movement, 'movement binding');
    stable(attributeActor(id), e.actual, 'attribute actor'); stable(attributeBinding(id), e.attribute, 'attribute binding');
    stable(terrainActor(id), e.actual, 'terrain actor'); stable(terrainGlobals(), terrain, 'terrain globals');
    stable(terrainHistory(id), e.history, 'terrain history');
    stable(cueActor(id), e.actual, 'cue actor'); stable(cueMapping(id), e.mapping, 'cue mapping');
    stable(cueBinding(id), e.cue, 'cue binding'); stable(cueDispatch(id), e.dispatch, 'cue dispatch');
    stable(read(e.actual, 'pos'), e.position, 'actual position');
    stable(read(e.actual, 'savedGroundPos'), e.savedPosition, 'actual saved position');
    for (const [key, owner] of e.historyVectors) stable(read(e.history, key), owner, `history ${key}`);
    if (testerActor) {
      stable(testerActor(id), e.actual, 'input tester actor'); stable(testerWorld!(id), e.world, 'input tester world');
      stable(testerMapping!(id), e.mapping, 'input tester mapping');
      stable(testerAttribute!(id), e.attribute, 'input tester attribute');
      stable(testerStatus!(id), e.testerStatus!, 'input tester status');
      const current = ownerList(testerOwners!(id), 'input tester source owners');
      if (current.length !== e.testerOwners!.length || current.some((owner, i) => owner !== e.testerOwners![i]))
        fail('input tester source owners changed');
      if (ownerList(testerDescriptors!(), 'known input tester descriptors').some(owner => owners(e).includes(owner) || owner === terrain))
        fail('input tester descriptor aliases a cue0 source owner');
    }
    if (tailActor) {
      stable(tailActor(id), e.actual, 'tail actor'); stable(tailWorld!(id), e.world, 'tail world');
      stable(tailMapping!(id), e.mapping, 'tail mapping'); stable(tailMovement!(id), e.movement, 'tail movement');
      stable(tailStatus!(id), e.tailStatus!, 'tail status'); stable(tailBorg!(id), e.tailBorg!, 'tail Borg');
      stable(tailBinding!(id), e.tailBinding!, 'tail binding'); stable(tailChargeBinding!(id), e.tailCharge!, 'tail charge binding');
      stable(chargeAttribute!(id), e.attribute, 'tail charge/cue0 attribute');
      if (tailCharge!() !== charge || chargeGlobal!() !== global || tailGlobal!() !== global || chargeData!() !== data)
        fail('tail must retain the same genuine charge runtime and match global');
      if (tailCues!() !== cueRuntime || tailCue!(id) !== e.cue || tailDispatch!(id) !== e.dispatch)
        fail('tail/cue0 must share the same genuine cue runtime and records');
      if (testerStatus && (e.tailStatus !== e.testerStatus || testerCharge!() !== charge || testerChargeBinding!(id) !== e.tailCharge))
        fail('tail/input testers must share canonical status and charge owners');
      const current = ownerList(tailOwners!(id), 'tail source owners');
      if (current.length !== 1 || current[0] !== e.tailBinding || e.tailOwners!.length !== 1 || e.tailOwners![0] !== e.tailBinding)
        fail('tail source owners must retain only the new tail binding');
      assertTeamOwners(e);
    }
    noShadows(e);
  };
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {
    const e = actors.get(id); if (!e) fail('unknown/non-owned cue0-lifecycle actor'); return e;
  };
  const assertComplete = (actual: object): void => {
    if (hasIncompleteSourceActorCue0Tail(actual))
      fail('actual actor has a known incomplete cue0 tail; source continuation is unsupported');
    if (hasIncompleteSourceActorInputTesters(actual))
      fail('actual actor has known incomplete input testers; source continuation is unsupported');
    if (incomplete.has(actual)) fail('actual actor has a known incomplete cue0 lifecycle; source continuation is unsupported');
  };
  const write = (e: Entry, owner: object, key: string, value: number): void => {
    own(owner, key, true); check(); (owner as Record<string, unknown>)[key] = value;
    incomplete.add(e.actual); check();
  };
  const updateTerrain = (id: symbol, e: Entry): 0 | 1 => {
    if ((integer(read(e.actual, 'controlWord'), 0, 0xffffffff, 'controlWord') & 0x40) !== 0) return 0;
    if (byte(e.world, 'mode4a0') === 2) return 0;
    const oldY = f(e.position, 'y'); // 68e3c retained f31, before clearance668.
    const clearance = f(e.actual, 'hoverOffset668');
    const ground = float(groundQuery(id, e.position, clearance), 'genuine3d6e4 return');
    write(e, e.position, 'y', ground); // 68e4c precedes every732/674 load.
    const flag732 = signedByte(e.binding, 'byte732'); // 68e54/68e60.
    const currentY = f(e.position, 'y'), savedY = f(e.savedPosition, 'y');
    const threshold = f(e.attribute, 'field674'); // 68e64 before68e68 fsubs.
    const deltaY = sub32(currentY, savedY), negativeThreshold = -threshold;
    if (deltaY < negativeThreshold || flag732 !== 0) {
      write(e, e.position, 'y', oldY); // 68e88 before any X/Z arithmetic.
      const z = f(e.position, 'z'), savedZ = f(e.savedPosition, 'z'), x = f(e.position, 'x');
      const dz = sub32(z, savedZ), savedX = f(e.savedPosition, 'x'), dx = sub32(x, savedX);
      const zSquared = mul32(dz, dz), squared = fusedMultiplyAddSourceFloat32(dx, dx, zSquared);
      if (squared > 0) fail('80068eb8 reached unsupported frsqrte after restoring positionY');
      const scale = f(e.actual, 'tierScale'), speed = f(e.actual, 'hSpeed'); // 68f04,68f08.
      // Only the reached zero-numerator subset. ±0 / finite nonzero f32 is
      // exactly representable with XOR sign, requiring no reciprocal or sqrt.
      if (scale === 0) fail('80068f0c fdivs zero divisor outside finite domain');
      const nextSpeed = squared / scale;
      if (nextSpeed > speed) {
        write(e, e.actual, 'hSpeed', nextSpeed);
        fail('80068f1c reached unsupported source atan call800452a0 after hSpeed store');
      }
      write(e, e.actual, 'slopeMode698', 30); // 80437648 bits41f00000,68f2c.
      fail('80068f30 reached unsupported source call8006a5a4 after slopeMode698 store');
    }
    if (deltaY > threshold) {
      const x = f(e.position, 'x'), savedX = f(e.savedPosition, 'x');
      let changed = x !== savedX;
      if (!changed) changed = f(e.position, 'z') !== f(e.savedPosition, 'z');
      if (changed) {
        // Raw lwz/lwz/stw/stw/lwz/stw: do not prevalidate the later Z copy or
        // all destinations. Within the finite-f32 host domain, copying a
        // number preserves its exact source word, including either zero sign.
        const rawX = f(e.savedPosition, 'x'), rawY = f(e.savedPosition, 'y');
        write(e, e.position, 'x', rawX); write(e, e.position, 'y', rawY);
        const rawZ = f(e.savedPosition, 'z'); write(e, e.position, 'z', rawZ);
      }
    }
    return 0;
  };
  const dispatch = (id: symbol, e: Entry): void => {
    if (byte(e.movement, 'byte661') === 3) {
      incomplete.add(e.actual);
      const upper = upperCue(id, 0x1b);
      if (upper !== 0 && upper !== 1) fail('genuine upper-body cue returned asynchronously or unexpectedly');
      const full = fullCue(id, 0x1b);
      if (full !== 0 && full !== 1) fail('genuine full-body cue returned asynchronously or unexpectedly');
      return;
    }
    if (updateTerrain(id, e) !== 0) return;
    if (!runTesters) fail('80059184 reached unsupported source call800699d8 after genuine80068df8 returned0');
    // The nested helper may finish its own six-store sequence, but this caller
    // still owes later source calls. Keep caller poison across native0 return.
    incomplete.add(e.actual);
    const result = runTesters(id);
    if (result !== 0 && result !== 1) fail('genuine input testers returned asynchronously or unexpectedly');
    if (result === 1) return;
    if (!runTail) fail('80059194 reached unsupported source call80069814 after genuine800699d8 returned0');
    if (runTail(id) !== undefined) fail('genuine cue0 tail returned asynchronously or unexpectedly');
    assertTeamOwners(e);
  };
  const runtime: SourceActorCue0LifecycleRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'actual actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source cue0-lifecycle runtime');
      const binding: Partial<SourceActorCue0LifecycleBinding> = {};
      const e: Entry = {actual, position: record(read(actual, 'pos'), 'actual position') as SourceJointVector,
        savedPosition: record(read(actual, 'savedGroundPos'), 'actual saved position') as SourceJointVector,
        world: record(worldBinding(id), 'world binding') as Entry['world'], mapping: record(worldMapping(id), 'world mapping'),
        movement: record(movementBinding(id), 'movement binding') as Entry['movement'],
        attribute: record(attributeBinding(id), 'attribute binding') as Entry['attribute'],
        history: record(terrainHistory(id), 'terrain history') as Entry['history'],
        cue: record(cueBinding(id), 'cue binding') as Entry['cue'], dispatch: record(cueDispatch(id), 'cue dispatch') as Entry['dispatch'],
        binding, extras: [], historyVectors: []};
      const historyVectors: Array<readonly [string, object]> = [];
      for (const key of ['rotation76', 'preRotation1d6a', 'aimOrigin524']) {
        if (Object.getOwnPropertyDescriptor(e.history, key) !== undefined)
          historyVectors.push([key, record(read(e.history, key), `history ${key}`)]);
      }
      e.historyVectors = Object.freeze(historyVectors);
      if (testerOwners) {
        e.testerOwners = ownerList(testerOwners(id), 'input tester source owners');
        e.testerStatus = record(testerStatus!(id), 'input tester status');
      }
      if (tailOwners) {
        e.tailOwners = ownerList(tailOwners(id), 'tail source owners');
        e.tailBinding = record(tailBinding!(id), 'tail binding');
        e.tailStatus = record(tailStatus!(id), 'tail status'); e.tailBorg = record(tailBorg!(id), 'tail Borg');
        e.tailCharge = record(tailChargeBinding!(id), 'tail charge binding');
      }
      admit(id, e);
      const records = owners(e);
      if (new Set([...records, terrain]).size !== records.length + 1 || records.some(owner => assigned.has(owner)))
        fail('source owner alias: distinct actual/position/saved/world/mapping/movement/attribute/history/cue/dispatch/732/terrain required');
      record(initial, 'initial cue0 binding'); noShadows({...e, binding: initial});
      if (Object.getOwnPropertyDescriptor(initial, 'byte732') !== undefined) binding.byte732 = byte(initial, 'byte732');
      Object.seal(binding); e.extras = Object.freeze([binding, e.attribute, e.history, e.position, e.savedPosition,
        ...e.historyVectors.map(([, owner]) => owner), ...(e.testerOwners ?? []), ...(e.tailOwners ?? [])]); check();
      actors.set(id, e); records.forEach(owner => assigned.add(owner)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getWorldBinding(id) {return entry(id).world;},
    getMappingActor(id) {return entry(id).mapping;},
    getMovementBinding(id) {return entry(id).movement;},
    getAttributeBinding(id) {return entry(id).attribute;},
    getActorBinding(id) {return entry(id).binding;},
    getTerrainRuntime() {return terrainRuntime;},
    getTerrainGlobals() {return terrain;},
    getHistoryBinding(id) {return entry(id).history;},
    getCueRuntime() {return cueRuntime;},
    getInputTestersRuntime() {return testers as SourceActorInputTestersRuntime | undefined;},
    getTailRuntime() {return tail as SourceActorCue0TailRuntime | undefined;},
    getCueBinding(id) {return entry(id).cue;},
    getDispatchBinding(id) {return entry(id).dispatch;},
    getSourceOwners(id) {return entry(id).extras;},
    assertActorComplete(id) {assertComplete(entry(id).actual);},
    updateTerrain(id) {return guard(() => {
      const e = entry(id); assertComplete(e.actual); admit(id, e);
      const result = updateTerrain(id, e); check(); incomplete.delete(e.actual); return result;
    });},
    dispatchCue0(id) {guard(() => {
      const e = entry(id); assertComplete(e.actual); admit(id, e);
      dispatch(id, e); check(); incomplete.delete(e.actual);
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
