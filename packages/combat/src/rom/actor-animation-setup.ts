/** Bounded 8004871c and 8004a754, chunk_0005.c:4261–4301 and
 * chunk_0006.c:347–386. Actual owned records retain all existing fields.
 * Only missing actor banks/movement and part bytes/floats have sidecars.
 * Decoded banks, finite exact-f32 inputs, four channels, non-proxy own-data
 * records and synchronous stable adapters are host bounds, not RAM emulation.
 * Methods/receivers are captured. Readonly operands are allowed; destination
 * writability is checked at each reached store. Refusals preserve prior effects.
 * No transition/mode reads, substitute playback, implicit readiness or guessed
 * 4d08c effects. Part1 stores movement then requires a real bound follow-up.
 */
import type {SourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import type {SourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import type {SourceActorAnimationDispatchRuntime, SourceActorAnimationSetupRequest} from './actor-animation-dispatch.js';
import type {SourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import type {SourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import type {SourceAnimationArchiveBankRuntime} from './animation-archive-bank.js';
import type {SourceStreamWaitRuntime} from './stream-wait.js';
export interface SourceActorAnimationSetupBinding {familyBank1d78: symbol | null; sharedBank1d7c: symbol | null; movement6d8: number}
export interface SourceActorAnimationSetupPartBinding {group28: number; action29: number; bank31: number; status38: number; field18: number; field1c: number; field20: number}
export interface SourceActorAnimationSetupSources {
  mapping: Pick<SourceActorJointMappingRuntime, 'getLayout' | 'getPartBinding' | 'mapPreparedPart'>;
  feedback: Pick<SourceJointAnimationFeedbackRuntime, 'getPart'>;
  dispatch: Pick<SourceActorAnimationDispatchRuntime, 'getActorBinding' | 'getPartBinding'>;
  descriptors: Pick<SourceAnimationDescriptorBankRuntime, 'resolveDescriptor'>;
  metadata: Pick<SourceAnimationSetupMetadataRuntime, 'getPartBinding' | 'applyMetadata'>;
  archiveBanks: Pick<SourceAnimationArchiveBankRuntime, 'resolveArchive'>;
  starts: Pick<SourceStreamWaitRuntime, 'getStartActorBinding'>;
}
export interface SourceActorAnimationSetupRuntime {
  bindMovementRuntime(runtime: Pick<SourceActorMovementFollowupRuntime, 'updateActor'>): void;
  bindActor(actor: symbol, initial: SourceActorAnimationSetupBinding): void;
  getActorBinding(actor: symbol): SourceActorAnimationSetupBinding;
  bindPart(part: symbol, initial: SourceActorAnimationSetupPartBinding): void;
  getPartBinding(part: symbol): SourceActorAnimationSetupPartBinding;
  setupModeZero(actor: symbol, channel: number, request: SourceActorAnimationSetupRequest): void;
  finishPartOneSetup(actor: symbol): void;
}
function fail(reason: string): never {throw Error(`[actor-animation-setup] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, key: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${key}: integer out of bounds`); return value;
}
function float(value: unknown, key: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${key}: finite exact source float32 required`); return value;
}
function link(value: unknown, key: string): symbol | null {if (value !== null && typeof value !== 'symbol') fail(`${key}: decoded symbol or null required`); return value;}
export function createSourceActorAnimationSetupRuntime(sources: SourceActorAnimationSetupSources): SourceActorAnimationSetupRuntime {
  let busy = false, poisoned = false;
  let movement: ((id: symbol) => unknown) | undefined;
  const capture = (name: string, key: string) => {
    const receiver = own(sources, name), fn = own(receiver, key);
    if (typeof fn !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {
      const result = Reflect.apply(fn, receiver, args);
      if (poisoned) fail('caught same-runtime reentry');
      if (result instanceof Promise) fail('adapter must complete synchronously');
      return result;
    };
  };
  const getLayout = capture('mapping', 'getLayout'), getMapping = capture('mapping', 'getPartBinding');
  const map = capture('mapping', 'mapPreparedPart'), getFeedback = capture('feedback', 'getPart');
  const getGates = capture('dispatch', 'getActorBinding'), getDispatch = capture('dispatch', 'getPartBinding');
  const descriptor = capture('descriptors', 'resolveDescriptor'), getMetadata = capture('metadata', 'getPartBinding');
  const metadata = capture('metadata', 'applyMetadata'), archive = capture('archiveBanks', 'resolveArchive');
  const getStart = capture('starts', 'getStartActorBinding');
  const actors = new Map<symbol, {binding: SourceActorAnimationSetupBinding; gates: unknown; start: unknown}>();
  const parts = new Map<symbol, {binding: SourceActorAnimationSetupPartBinding; mapping: unknown; feedback: unknown; dispatch: unknown; metadata: unknown}>();
  const actorEntry = (id: symbol) => {const entry = actors.get(id); if (!entry) fail('unknown/non-owned setup actor'); return entry;};
  const partEntry = (id: symbol) => {const entry = parts.get(id); if (!entry) fail('unknown/non-owned setup part'); return entry;};
  const read = (record: unknown, key: string): unknown => {const result = own(record, key); if (poisoned) fail('caught same-runtime reentry'); return result;};
  const write = (record: unknown, key: string, value: unknown): void => {
    own(record, key, true); if (poisoned) fail('caught same-runtime reentry');
    (record as Record<string, unknown>)[key] = value;
  };
  const guarded = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); if (poisoned) fail('caught same-runtime reentry');} finally {busy = false;}
  };
  const voidResult = (result: unknown): void => {if (result !== undefined) fail('effect adapter must return synchronous undefined');};
  return Object.freeze({
    bindMovementRuntime(runtime: Pick<SourceActorMovementFollowupRuntime, 'updateActor'>): void {guarded(() => {
      if (movement !== undefined) fail('movement follow-up runtime already bound');
      const fn = own(runtime, 'updateActor');
      if (typeof fn !== 'function') fail('movement updateActor: own data-function required');
      movement = (id: symbol): unknown => {
        const result = Reflect.apply(fn, runtime, [id]);
        if (poisoned) fail('caught same-runtime reentry');
        return result;
      };
    });},
    bindActor(id: symbol, initial: SourceActorAnimationSetupBinding): void {guarded(() => {
      if (actors.has(id)) fail('actor already bound');
      const gates = getGates(id), start = getStart(id);
      const familyBank1d78 = link(read(initial, 'familyBank1d78'), 'familyBank1d78');
      const sharedBank1d7c = link(read(initial, 'sharedBank1d7c'), 'sharedBank1d7c');
      const movement6d8 = float(read(initial, 'movement6d8'), 'movement6d8');
      actors.set(id, {gates, start, binding: Object.seal({familyBank1d78, sharedBank1d7c, movement6d8})});
    });},
    getActorBinding(id: symbol) {return actorEntry(id).binding;},
    bindPart(id: symbol, initial: SourceActorAnimationSetupPartBinding): void {guarded(() => {
      if (parts.has(id)) fail('part already bound');
      const mapping = getMapping(id), feedback = getFeedback(id), dispatch = getDispatch(id), metadata = getMetadata(id);
      const binding = {} as SourceActorAnimationSetupPartBinding;
      for (const key of ['group28', 'action29', 'bank31', 'status38'] as const) binding[key] = integer(read(initial, key), 0, 255, key);
      for (const key of ['field18', 'field1c', 'field20'] as const) binding[key] = float(read(initial, key), key);
      parts.set(id, {mapping, feedback, dispatch, metadata, binding: Object.seal(binding)});
    });},
    getPartBinding(id: symbol) {return partEntry(id).binding;},
    setupModeZero(id: symbol, channel: number, request: SourceActorAnimationSetupRequest): void {guarded(() => {
      // Snapshot ABI inputs before effects, but admit float only at its first store.
      const group = read(request, 'group'), action = read(request, 'action'), frame = read(request, 'frame');
      const actor = actorEntry(id);
      const cursor = descriptor(actor.gates, actor.start, group, action);
      if (typeof cursor !== 'symbol') fail('descriptor adapter must return owned cursor');
      integer(channel, 0, 3, 'channel (four-part host bound)');
      const layout = getLayout(id), row = read(read(layout, 'parts'), '0');
      const partId = read(row, String(channel)); if (typeof partId !== 'symbol') fail('owned part identity required');
      const part = partEntry(partId);
      write(part.binding, 'group28', integer(group, 0, 0xffffffff, 'group') & 255);
      write(part.binding, 'action29', integer(action, -0x80000000, 0xffffffff, 'action') & 255);
      voidResult(metadata(id, partId, channel, cursor));
      const selector = integer(read(part.metadata, 'selector2a'), 0, 255, 'selector2a');
      write(part.binding, 'bank31', selector >> 7);
      write(part.feedback, 'mode2f', 0);
      write(part.binding, 'field20', 0); write(part.binding, 'field18', 0); write(part.binding, 'field1c', 0);
      write(part.dispatch, 'linked36', 0); write(part.dispatch, 'previous10', 0);
      write(part.dispatch, 'previous14', float(frame, 'request frame'));
      write(part.dispatch, 'elapsed08', 0); write(part.feedback, 'frame0c', float(frame, 'request frame'));
      float(read(part.feedback, 'frame0c'), 'live frame0c'); // 4a754 ABI argument, consumed even if no joints.
      write(part.mapping, 'poseBuffer35', 0);
      const bank = integer(read(part.binding, 'bank31'), 0, 255, 'bank31');
      write(part.mapping, 'descriptor00', link(read(actor.binding, bank === 0 ? 'familyBank1d78' : 'sharedBank1d7c'), 'archive bank'));
      write(part.feedback, 'complete2e', 0);
      const result = integer(archive(partId), -1, 1, 'archive result');
      write(part.binding, 'status38', result & 255);
      if ((result & 255) !== 0) write(part.feedback, 'complete2e', 1);
      voidResult(map(id, 0, channel, 1));
    });},
    finishPartOneSetup(id: symbol): void {guarded(() => {
      write(actorEntry(id).binding, 'movement6d8', 1);
      if (movement === undefined) fail('part1 postamble requires unsupported 4d08c');
      voidResult(movement(id));
    });},
  });
}
