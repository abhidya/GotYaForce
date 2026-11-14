/** Bounded 48648 setup gates, 49e58 dispatch and 49f10 mode0 continuation.
 * Setup source: chunk_0005.c:4232–4257. Actual setup gates retain source
 * order. Optional once-bound mode0 setup must perform real archive and
 * mapping work. Other modes and blocked4a41c refuse. Part1 must complete its
 * actual postamble or refuse after preserved effects; no playback substitution.
 * Source: chunk_0006.c:1–68; mode-table provenance is documented in
 * double-source-owned-dispatch-plan-2026-11-12.md and the recorded retail DOL
 * table inspection in docs/knight-authored-windup.md:8–22. Raw table bytes are
 * not bundled here. The decompiler loses the handler part-number convention;
 * this is bounded semantic reconstruction, not an exact ABI claim. Readiness
 * pointers mean symbolic presence only, without pointee ownership/dereference.
 * This is not linked-mode
 * setup, other modes, source RAM aliasing, original replay or live wiring.
 *
 * Gate pointers precede marker gates, part resolution and snapshots. Snapshots
 * copy finite f32 values (including signed zero), without arithmetic. Mode0
 * advances elapsed then frame, reloading the live actor timestep per addition,
 * before testing linked36. Only then does the real mapping runtime execute
 * animatePart(actor,0,0,partNumber,2). Completion is read back, never synthesized.
 *
 * Additional bindings are copied/sealed; mapping/feedback source records are
 * retained, not cloned. Non-proxy own-data inputs and stable actual runtime
 * getters are required. Runtime methods are fixed with their original receiver.
 * Host limits: four parts; finite f32 RN00/NI0 arithmetic; no RAM aliases or
 * deferred effects. Unsupported paths refuse when reached, preserving all prior
 * writes/effects. Caught same-runtime mutation reentry poisons the outer call.
 */
import type {SourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import type {SourceActorJointMappingRuntime, SourceActorJointMappingHeader, SourceActorJointLayout} from './actor-joint-mapping.js';
import type {SourceJointAnimationFeedbackRuntime, SourceJointAnimationPart} from './joint-animation-feedback.js';

export interface SourceActorAnimationDispatchBinding {
  family1d88: symbol | null;
  shared1d8c: symbol | null;
  marker578: number;
  marker1db3: number;
}
export interface SourceActorAnimationDispatchPartBinding {
  elapsed08: number;
  previous10: number;
  previous14: number;
  linked36: number;
}
/** Actual opcode01 setup arguments, inspected only by a reached setup handler. */
export interface SourceActorAnimationSetupRequest {
  readonly frame: number;
  readonly group: number;
  readonly action: number;
  readonly transition: number;
  readonly mode: number;
}
export interface SourceActorAnimationDispatchRuntime {
  /** Same mapping header bound to this actor, never a snapshot. */
  getSourceActor(actor: symbol): SourceActorJointMappingHeader;
  bindSetupRuntime(setup: Pick<SourceActorAnimationSetupRuntime, 'setupModeZero' | 'finishPartOneSetup'>): void;
  bindActor(actor: symbol, initial: SourceActorAnimationDispatchBinding): void;
  bindPart(part: symbol, initial: SourceActorAnimationDispatchPartBinding): void;
  getActorBinding(actor: symbol): SourceActorAnimationDispatchBinding;
  getPartBinding(part: symbol): SourceActorAnimationDispatchPartBinding;
  setupPart(actor: symbol, partNumber: number, blockedSource: {readonly blockedMask1d9a: number},
    request: SourceActorAnimationSetupRequest): void;
  updatePart(actor: symbol, partNumber: number): number;
}
function fail(reason: string): never {
  throw Error(`[actor-animation-dispatch] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: object, key: string, writable = true): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, max: number, where: string): asserts value is number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max) fail(`${where}: unsigned integer out of range`);
}
function f32(value: unknown, where: string): asserts value is number {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value as number))) fail(`${where}: expected finite source float32`);
}
function link(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: opaque symbol or null required`);
}
function byte(record: object, key: string): number {const value = own(record, key); integer(value, 255, key); return value;}
function readFloat(record: object, key: string): number {const value = own(record, key); f32(value, key); return value;}
function readLink(record: object, key: string): symbol | null {const value = own(record, key); link(value, key); return value;}
function write(record: object, key: string, value: number): void {own(record, key); (record as Record<string, unknown>)[key] = value;}
function method(table: object, key: string): (...args: never[]) => unknown {
  const fn = own(table, key, false); if (typeof fn !== 'function') fail(`${key}: own data-function required`);
  return fn as (...args: never[]) => unknown;
}
export function createSourceActorAnimationDispatchRuntime(mapping: SourceActorJointMappingRuntime,
  feedback: SourceJointAnimationFeedbackRuntime): SourceActorAnimationDispatchRuntime {
  const actorGet = method(mapping, 'getActor'), layoutGet = method(mapping, 'getLayout');
  const mappingPartGet = method(mapping, 'getPartBinding'), animate = method(mapping, 'animatePart');
  const partGet = method(feedback, 'getPart');
  const actors = new Map<symbol, {binding: SourceActorAnimationDispatchBinding; source: SourceActorJointMappingHeader}>();
  const parts = new Map<symbol, {binding: SourceActorAnimationDispatchPartBinding; source: SourceJointAnimationPart}>();
  let readySetup: {table: object; mode0: (...args: never[]) => unknown; post: (...args: never[]) => unknown} | null = null;
  let busy = false, reentered = false;
  const enter = (): void => {if (busy) {reentered = true; fail('same-runtime reentry is unsupported');} busy = true; reentered = false;};
  const invoke = (fn: (...args: never[]) => unknown, receiver: object, args: unknown[]): unknown => {
    const result = Reflect.apply(fn, receiver, args);
    if (reentered) fail('same-runtime reentry was caught inside an adapter');
    return result;
  };
  const actorRecord = (id: symbol) => {const value = actors.get(id); if (!value) fail('unknown/non-owned actor binding'); return value;};
  const partRecord = (id: symbol) => {const value = parts.get(id); if (!value) fail('unknown/non-owned part binding'); return value;};
  return Object.freeze({
    bindSetupRuntime(setup: Pick<SourceActorAnimationSetupRuntime, 'setupModeZero' | 'finishPartOneSetup'>): void {
      enter(); try {
        if (readySetup !== null) fail('ready setup runtime already bound');
        const mode0 = method(setup, 'setupModeZero'), post = method(setup, 'finishPartOneSetup');
        if (reentered) fail('same-runtime reentry was caught inside an adapter');
        readySetup = {table: setup, mode0, post};
      } finally {busy = false;}
    },
    bindActor(id: symbol, initial: SourceActorAnimationDispatchBinding): void {
      enter(); try {
        if (actors.has(id)) fail('actor is already bound');
        const source = invoke(actorGet, mapping, [id]) as SourceActorJointMappingHeader;
        const family1d88 = own(initial, 'family1d88', false); link(family1d88, 'family1d88');
        const shared1d8c = own(initial, 'shared1d8c', false); link(shared1d8c, 'shared1d8c');
        const marker578 = own(initial, 'marker578', false); integer(marker578, 255, 'marker578');
        const marker1db3 = own(initial, 'marker1db3', false); integer(marker1db3, 255, 'marker1db3');
        actors.set(id, {source, binding: Object.seal({family1d88, shared1d8c, marker578, marker1db3})});
      } finally {busy = false;}
    },
    bindPart(id: symbol, initial: SourceActorAnimationDispatchPartBinding): void {
      enter(); try {
        if (parts.has(id)) fail('part is already bound');
        invoke(mappingPartGet, mapping, [id]);
        const source = invoke(partGet, feedback, [id]) as SourceJointAnimationPart;
        const elapsed08 = own(initial, 'elapsed08', false); f32(elapsed08, 'elapsed08');
        const previous10 = own(initial, 'previous10', false); f32(previous10, 'previous10');
        const previous14 = own(initial, 'previous14', false); f32(previous14, 'previous14');
        const linked36 = own(initial, 'linked36', false); integer(linked36, 255, 'linked36');
        parts.set(id, {source, binding: Object.seal({elapsed08, previous10, previous14, linked36})});
      } finally {busy = false;}
    },
    getActorBinding(id: symbol) {return actorRecord(id).binding;},
    getSourceActor(id: symbol) {return actorRecord(id).source;},
    getPartBinding(id: symbol) {return partRecord(id).binding;},
    setupPart(id: symbol, partNumber: number, blockedSource: {readonly blockedMask1d9a: number},
      request: SourceActorAnimationSetupRequest): void {
      enter(); try {
        const gates = actorRecord(id).binding;
        // Setup only reads these operands; do not relax playback's existing
        // writable-field contract. No part/layout/request is read on no-op paths.
        const family = own(gates, 'family1d88', false); link(family, 'family1d88');
        if (family === null) return;
        const shared = own(gates, 'shared1d8c', false); link(shared, 'shared1d8c');
        if (shared === null) return;
        if (partNumber === 1) {
          const first = own(gates, 'marker578', false); integer(first, 255, 'marker578');
          if (first === 1) {
            const second = own(gates, 'marker1db3', false); integer(second, 255, 'marker1db3');
            if (second === 1) return;
          }
        }
        // Retain the stream's actual source record at the call boundary. Its
        // signed byte is reached only after all source no-op gates have passed.
        const blocked = own(blockedSource, 'blockedMask1d9a', false);
        integer(blocked, 255, 'blockedMask1d9a');
        integer(partNumber, 3, 'partNumber');
        if (((blocked << 24 >> 24) & (1 << partNumber)) !== 0) {
          fail('48648 blocked setup requires unsupported 4a41c');
        }
        if (readySetup === null) fail('48648 unblocked setup requires unsupported setup table/4871c');
        const mode = own(request, 'mode', false); integer(mode, 0xffffffff, 'setup mode');
        if (mode !== 0) fail('unsupported setup mode');
        // Archived slot0 is 8004871c. Complete the actual handler before the
        // source part1 postamble; neither path may fabricate a void success.
        const result = invoke(readySetup.mode0, readySetup.table, [id, partNumber, request]);
        if (result !== undefined) fail('setupModeZero must synchronously return undefined');
        if (partNumber === 1) {
          const post = invoke(readySetup.post, readySetup.table, [id]);
          if (post !== undefined) fail('finishPartOneSetup must synchronously return undefined');
        }
      } finally {busy = false;}
    },
    updatePart(id: symbol, partNumber: number): number {
      enter(); try {
        const actor = actorRecord(id), gates = actor.binding;
        if (readLink(gates, 'family1d88') === null) return 1;
        if (readLink(gates, 'shared1d8c') === null) return 1;
        if (partNumber === 1 && byte(gates, 'marker578') === 1 && byte(gates, 'marker1db3') === 1) return 0;
        integer(partNumber, 3, 'partNumber');
        const layout = invoke(layoutGet, mapping, [id]) as SourceActorJointLayout;
        const rows = own(layout, 'parts', false) as object;
        const row = own(rows, '0', false) as object;
        const partId = own(row, String(partNumber), false);
        if (typeof partId !== 'symbol') fail('part: owned identity required');
        const {source: part, binding} = partRecord(partId);
        write(binding, 'previous10', readFloat(binding, 'elapsed08'));
        write(binding, 'previous14', readFloat(part, 'frame0c'));
        const mode = (byte(part, 'mode2f') << 24) >> 24;
        if (mode !== 0) fail(`unsupported signed animation mode ${mode}`);
        const elapsed = Math.fround(readFloat(binding, 'elapsed08') + readFloat(actor.source, 'timestep1dc8'));
        f32(elapsed, 'elapsed08 result'); write(binding, 'elapsed08', elapsed);
        const frame = Math.fround(readFloat(part, 'frame0c') + readFloat(actor.source, 'timestep1dc8'));
        f32(frame, 'frame0c result'); write(part, 'frame0c', frame);
        if (byte(binding, 'linked36') !== 0) fail('linked mode0 continuation is unsupported');
        const result = invoke(animate, mapping, [id, 0, 0, partNumber, 2]);
        if (result !== undefined) fail('animatePart must complete synchronously and return undefined');
        return (byte(part, 'complete2e') << 24) >> 24;
      } finally {busy = false;}
    },
  });
}
