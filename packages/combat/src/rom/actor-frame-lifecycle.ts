/** Bounded actual80055568 prefix, never a completed actor frame.
 * Fixed source schedule: marker578=2; genuine55dcc; genuine5568c; genuine59068;
 * snapshot actual position20/24/28; optionally run genuine Double4bc, capture
 * upper5db then full5da, store marker1/dispatch upper, marker0/dispatch full,
 * then marker2 before the actual4c0 boundary.
 * Missing family owners retain the historical4bc refusal. An admitted Double
 * action still stops at its next unsupported callee, never skips to a suffix.
 * No hook/state/posthook/flag/sound call is skipped and no extra465fc is added.
 *
 * Explicit decoded raw distances are HOST ingress before the first55568 write,
 * not a source producer or a mutation inserted after55dcc. The source59068
 * operation only consumes those canonical actual fields. Epochs remain consumed
 * on failed ingress. A previously incomplete frame refuses before a new epoch.
 * Once source execution begins, the frame is permanently
 * incomplete; another frame or direct tick ingress cannot bypass that prefix.
 * This is offline only: no production routing, full55568, complete attack or clone claim.
 */
import type {RomActor} from './actor.js';
import {isSourceActorAttributeRefreshRuntime, type SourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {isSourceActorStatusTimersRuntime, type SourceActorStatusTimersRuntime} from './actor-status-timers.js';
import {isSourceActorAnimationDispatchRuntime, type SourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {isSourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import {requireCompleteSourceActorAnimationTransition} from './actor-animation-transition.js';
import {isSourceActorDoublePrehookRuntime, requireCompleteSourceActorDoubleLifecycle, markIncompleteSourceActorDoubleLifecycle,
  type SourceActorDoublePrehookRuntime} from './actor-double-prehook.js';
import {isSourceActorDoubleActionRuntime, type SourceActorDoubleActionRuntime} from './actor-double-action.js';
import {claimSourceActorTickFrame, isSourceActorTickPrefixRuntime, hasIncompleteSourceActorFrame,
  type SourceActorTickPrefixRuntime, type SourceActorFrameRawDistances,
  type SourceActorTickFrameCapability, type SourceActorTickFrameOwners} from './actor-tick-prefix.js';

export {hasIncompleteSourceActorFrame} from './actor-tick-prefix.js';
export type {SourceActorFrameRawDistances} from './actor-tick-prefix.js';
export interface SourceActorFrameLifecycleSources {
  attributes: SourceActorAttributeRefreshRuntime;
  status: SourceActorStatusTimersRuntime;
  tick: SourceActorTickPrefixRuntime;
  dispatch: SourceActorAnimationDispatchRuntime;
  prehook?: SourceActorDoublePrehookRuntime;
  action?: SourceActorDoubleActionRuntime;
}
export interface SourceActorFrameLifecycleRuntime {
  bindActor(identity: symbol): void;
  getActualActor(identity: symbol): RomActor;
  /** No source-frame field copies are created. This is the existing578 owner. */
  getDispatchBinding(identity: symbol): object;
  /** Always refuses at the first unsupported source call, retaining all effects. */
  ingestRawDistancesAndRun(identity: symbol, epoch: number, raw: SourceActorFrameRawDistances): void;
}
const genuineRuntimes = new WeakSet<object>();
// The join is callable only during this module's synchronous bind transaction,
// with its exact private owner record. A genuine runtime alone is not authority
// to manufacture a raw/body capability outside the55568 implementation.
const pendingClaims = new WeakMap<object, {id: symbol; owners: SourceActorTickFrameOwners}>();
export function isPendingSourceActorFrameClaim(frame: unknown, id: symbol, owners: SourceActorTickFrameOwners): boolean {
  if (frame === null || typeof frame !== 'object' || !genuineRuntimes.has(frame)) return false;
  const pending = pendingClaims.get(frame);
  return pending?.id === id && pending.owners === owners;
}

export function isSourceActorFrameLifecycleRuntime(value: unknown): value is SourceActorFrameLifecycleRuntime {
  return value !== null && typeof value === 'object' && genuineRuntimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-frame-lifecycle] ${reason}; offline execution aborted, prior writes/effects and consumed epoch are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const descriptor = Object.getOwnPropertyDescriptor(record, key);
  if (!descriptor || !('value' in descriptor)) fail(`${key}: own data property required`);
  if (writable && !descriptor.writable) fail(`${key}: non-writable field is unsupported`);
  return descriptor.value;
}
function record(value: unknown, where: string): object {
  if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
  return value;
}
function f32(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
export function createSourceActorFrameLifecycleRuntime(sources: SourceActorFrameLifecycleSources): SourceActorFrameLifecycleRuntime {
  const attributes = own(sources, 'attributes'), status = own(sources, 'status');
  const tick = own(sources, 'tick'), dispatch = own(sources, 'dispatch');
  if (!isSourceActorAttributeRefreshRuntime(attributes)) fail('55dcc requires genuine source attribute runtime');
  if (!isSourceActorStatusTimersRuntime(status)) fail('5568c requires genuine source status runtime');
  if (!isSourceActorTickPrefixRuntime(tick)) fail('59068 requires genuine source tick runtime');
  if (!isSourceActorAnimationDispatchRuntime(dispatch)) fail('marker578 requires genuine source animation dispatch');
  const optional = (key: string): unknown => Object.getOwnPropertyDescriptor(sources, key) === undefined ? undefined : own(sources, key);
  const prehook = optional('prehook'), action = optional('action');
  if (prehook !== undefined && !isSourceActorDoublePrehookRuntime(prehook)) fail('4bc requires genuine source Double prehook');
  if (action !== undefined && (!isSourceActorDoubleActionRuntime(action) || prehook === undefined || action.getPrehookRuntime() !== prehook))
    fail('state dispatch requires genuine matched source Double action');
  const movement = attributes.getMovementRuntime();
  if (!isSourceActorMovementFollowupRuntime(movement)) fail('55dcc child4d08c requires genuine source movement runtime');
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (value: unknown, key: string, writable = false): unknown => {const result = own(value, key, writable); check(); return result;};
  const invoke = <T>(run: () => T): T => {const result = run(); check(); return result;};
  interface Entry {
    actual: RomActor; borg: object; world: object; mapping: object; attribute: object;
    status: object; start: object; movement: object; dispatch: object; pos: object;
    capability: SourceActorTickFrameCapability;
    familyOwners: readonly object[];
  }
  const actors = new Map<symbol, Entry>(), owned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const value = actors.get(id); if (!value) fail('unknown/non-owned frame actor'); return value;};
  const same = (value: unknown, expected: object, where: string): void => {check(); if (value !== expected) fail(`${where}: canonical source owner changed or differs`);};
  const familyOwners = (id: symbol): object[] => {
    const records: object[] = [];
    for (const runtime of [prehook, action]) {
      if (runtime === undefined) continue;
      const values = invoke(() => runtime.getSourceOwners(id));
      if (!Array.isArray(values)) fail('Double source owner array required');
      for (const value of values) records.push(record(value, 'Double source owner'));
    }
    return [...new Set(records)];
  };
  const owners = (id: symbol, e: Omit<Entry, 'capability' | 'familyOwners'> & {familyOwners?: readonly object[]}): void => {
    requireCompleteSourceActorDoubleLifecycle(e.actual); check();
    requireCompleteSourceActorAnimationTransition(e.mapping); check();
    for (const key of ['rootAction', 'preState', 'postState'])
      if (read(e.actual, key) !== null) fail(`legacy callable ${key} conflicts with exclusive source frame ownership`);
    same(invoke(() => attributes.getActualActor(id)), e.actual, 'attribute actual');
    same(invoke(() => status.getActualActor(id)), e.actual, 'status actual');
    same(invoke(() => tick.getActualActor(id)), e.actual, 'tick actual');
    same(invoke(() => movement.getActualActor(id)), e.actual, 'movement actual');
    same(invoke(() => status.getActualBorg(id)), e.borg, 'status Borg');
    same(invoke(() => tick.getActualBorg(id)), e.borg, 'tick Borg');
    same(invoke(() => status.getWorldBinding(id)), e.world, 'status world');
    same(invoke(() => status.getMappingActor(id)), e.mapping, 'status mapping');
    same(invoke(() => attributes.getMappingActor(id)), e.mapping, 'attribute mapping');
    same(invoke(() => dispatch.getSourceActor(id)), e.mapping, 'animation mapping');
    same(invoke(() => attributes.getActorBinding(id)), e.attribute, 'attribute binding');
    same(invoke(() => status.getAttributeBinding(id)), e.attribute, 'status attribute');
    same(invoke(() => status.getActorBinding(id)), e.status, 'status binding');
    same(invoke(() => status.getStartBinding(id)), e.start, 'stream start');
    same(invoke(() => movement.getActorBinding(id)), e.movement, 'movement binding');
    same(invoke(() => attributes.getMovementBinding(id)), e.movement, 'attribute movement');
    same(invoke(() => status.getMovementBinding(id)), e.movement, 'status movement');
    same(invoke(() => dispatch.getActorBinding(id)), e.dispatch, 'marker578 binding');
    same(read(e.actual, 'pos'), e.pos, 'position20');
    if (prehook !== undefined) {
      if (invoke(() => prehook.assertActorComplete(id)) !== undefined) fail('Double completion assertion returned unexpectedly');
      for (const [key, expected] of [
        ['getActualActor', e.actual], ['getMappingActor', e.mapping], ['getWorldBinding', e.world],
        ['getAttributeBinding', e.attribute], ['getStartBinding', e.start], ['getStatusBinding', e.status],
      ] as const) same(invoke(() => prehook[key](id)), expected, `Double prehook ${key}`);
    }
    if (action !== undefined) {
      same(invoke(() => action.getActualActor(id)), e.actual, 'Double action actual');
      same(invoke(() => action.getMappingActor(id)), e.mapping, 'Double action mapping');
      same(invoke(() => action.getAttributeBinding(id)), e.attribute, 'Double action attributes');
      same(invoke(() => action.getDispatchBinding(id)), e.dispatch, 'Double action dispatch marker');
      same(invoke(() => action.getPrehookBinding(id)), invoke(() => prehook!.getActorBinding(id)), 'Double action prehook');
      const ground = invoke(() => action.getGroundRuntime());
      if (ground !== undefined) {
        same(invoke(() => ground.getActualActor(id)), e.actual, 'Double ground actual');
        same(invoke(() => ground.getActualBorg(id)), e.borg, 'Double ground Borg');
        same(invoke(() => ground.getWorldBinding(id)), e.world, 'Double ground world');
        same(invoke(() => ground.getStatusBinding(id)), e.status, 'Double ground status');
      }
    }
    if (e.familyOwners !== undefined) {
      const current = familyOwners(id);
      // The action runtime can discover another existing parameter descriptor
      // lazily. All retained owners must remain, but that registry may grow.
      if (e.familyOwners.some(value => !current.includes(value)))
        fail('Double canonical source owners changed');
    }
  };
  const runtime: SourceActorFrameLifecycleRuntime = {
    bindActor(id: symbol): void {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(invoke(() => attributes.getActualActor(id)), 'actual actor') as RomActor;
      if (owned.has(actual) || hasIncompleteSourceActorFrame(actual)) fail('actual actor already owned or incomplete');
      const initial = {actual, borg: record(invoke(() => status.getActualBorg(id)), 'Borg'),
        world: record(invoke(() => status.getWorldBinding(id)), 'world'),
        mapping: record(invoke(() => attributes.getMappingActor(id)), 'mapping'),
        attribute: record(invoke(() => attributes.getActorBinding(id)), 'attributes'),
        status: record(invoke(() => status.getActorBinding(id)), 'status'),
        start: record(invoke(() => status.getStartBinding(id)), 'stream start'),
        movement: record(invoke(() => attributes.getMovementBinding(id)), 'movement'),
        dispatch: record(invoke(() => dispatch.getActorBinding(id)), 'dispatch'),
        pos: record(read(actual, 'pos'), 'position20')};
      owners(id, initial);
      const baseRecords = Object.values(initial), family = Object.freeze(familyOwners(id));
      // Shared decoded dispatch tables/parameter records are not per-actor
      // storage claims. Their genuine owners enforce their own alias rules.
      if (new Set(baseRecords).size !== baseRecords.length || baseRecords.some(value => owned.has(value))) fail('source frame storage owner alias');
      // No parallel numeric4b4/4bc/4c0 cells or callable family owners are admitted.
      // Null legacy placeholders are not interpreted as source no-op pointers.
      const ground = action?.getGroundRuntime();
      const join: SourceActorTickFrameOwners = ground === undefined ? initial : {...initial, ground: {
        gauge: invoke(() => ground.getGaugeBinding(id)), terrain: invoke(() => ground.getTerrainGlobals()),
        history: invoke(() => ground.getHistoryBinding(id))}};
      pendingClaims.set(runtime, {id, owners: join});
      let capability: SourceActorTickFrameCapability;
      try {capability = invoke(() => claimSourceActorTickFrame(runtime, tick, id, join));}
      finally {pendingClaims.delete(runtime);}
      actors.set(id, {...initial, capability, familyOwners: family}); baseRecords.forEach(value => owned.add(value));
    });},
    getActualActor(id: symbol) {return entry(id).actual;},
    getDispatchBinding(id: symbol) {return entry(id).dispatch;},
    ingestRawDistancesAndRun(id: symbol, epoch: number, raw: SourceActorFrameRawDistances): void {guard(() => {
      const e = entry(id);
      invoke(() => e.capability.beginHostIngress(epoch)); owners(id, e);
      if (Object.values(e).includes(raw) || familyOwners(id).includes(raw)) fail('raw input must not alias a source frame owner');
      // The tag describes a host boundary; it is not evidence of original producer provenance.
      invoke(() => e.capability.ingestRawDistances(raw));
      invoke(() => e.capability.beginSourceFrame());
      try {
        read(e.dispatch, 'marker578', true); (e.dispatch as {marker578: number}).marker578 = 2; check();
        if (invoke(() => attributes.refreshActor(id)) !== undefined) fail('genuine55dcc returned unexpectedly');
        owners(id, e);
        if (invoke(() => status.updateActor(id)) !== undefined) fail('genuine5568c returned unexpectedly');
        owners(id, e);
        if (invoke(() => e.capability.runActor()) !== undefined) fail('genuine59068 returned unexpectedly');
        owners(id, e);
        // Source lwz snapshots preserve values without arithmetic. These locals are
        // deliberately not actor/history storage and do not refresh savedGroundPos.
        const x = f32(read(e.pos, 'x'), 'position20'), y = f32(read(e.pos, 'y'), 'position24'), z = f32(read(e.pos, 'z'), 'position28');
        void x; void y; void z;
        if (prehook === undefined) fail('80055568 reached unsupported actual4bc family prehook after position20/24/28 snapshot');
        if (invoke(() => prehook.runActor(id)) !== undefined) fail('genuine4bc returned unexpectedly');
        owners(id, e);
        // Both signed selectors are captured before marker1. In particular the
        // full selector is not reloaded after upper-body dispatch returns.
        const saved = action === undefined ? undefined : invoke(() => action.captureStateSelectors(id));
        if (action === undefined) {
          for (const key of ['ubState', 'fbState'] as const) {
            const value = read(e.actual, key);
            if (typeof value !== 'number' || !Number.isInteger(value) || value < -128 || value > 127)
              fail(`${key}: canonical signed source byte required`);
          }
        }
        read(e.dispatch, 'marker578', true); (e.dispatch as {marker578: number}).marker578 = 1; check();
        if (action === undefined || saved === undefined) fail('80055568 reached unsupported saved upper state dispatch after actual4bc and marker1');
        if (invoke(() => action.dispatchUpper(id, saved)) !== undefined) fail('genuine upper state returned unexpectedly');
        read(e.dispatch, 'marker578', true); (e.dispatch as {marker578: number}).marker578 = 0; check();
        if (invoke(() => action.dispatchFull(id, saved)) !== undefined) fail('genuine full state returned unexpectedly');
        read(e.dispatch, 'marker578', true); (e.dispatch as {marker578: number}).marker578 = 2; check();
        fail('80055568 reached unsupported actual4c0 posthook after saved upper/full dispatch');
      } catch (error) {
        // A completed inner action cannot make an unfinished outer frame
        // replayable through its public prehook/action/ground entry points.
        // Host ingress errors remain outside this source-effect latch.
        markIncompleteSourceActorDoubleLifecycle(e.actual);
        throw error;
      }
    });},
  };
  genuineRuntimes.add(runtime); return Object.freeze(runtime);
}
